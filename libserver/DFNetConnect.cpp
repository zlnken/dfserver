#include "DFNetConnect.h"
#include "DFConfig.h"
#include "DFNetWork.h"
#include "DFDateTime.h"
#include "DFMessageBase.h"
#include "DFNetBuffer.h"
#include "DFNetSendBuffer.h"
#include "DFNetRecvBuffer.h"
#include "DFIO.h"
#include "DFUnpackMessage.h"
#include "DFPackMessage.h"
namespace DF{
	// -----------------------------------------------------------------------
	NetConnect::~NetConnect(void)
	{
		m_pNetWork = NULL;
		m_uSessionID = Config::MAX_UINT32;
		m_uWho = 0;
		m_pBindPoint = NULL;
	}
	// -----------------------------------------------------------------------
	NetConnect::NetConnect(NetWork* pNetWork) :
		m_pNetWork(pNetWork),
		m_uSessionID(Config::MAX_UINT32),
		m_uWho(0),
		m_eState(enNetConnect_Work),
		m_pBindPoint(NULL),
		m_uConnectTime(0),
		m_BoostSocket(pNetWork->getISO()),
		m_SendBuf(Config::SEND_BLOCK_SIZE, Config::SEND_BLOCK_NUM),
		m_RecvBuf(Config::RECV_BLOCK_SIZE, Config::RECV_BLOCK_NUM),
		m_RecvCache(Config::RECV_BLOCK_SIZE),
		m_SendMutex(),
		m_RecvMutex()
	{
		m_uConnectTime = DateTime::instancePtr()->seconds();
	}

	// -----------------------------------------------------------------------
	void NetConnect::start(void) 
	{
		try
		{
			m_sIP = this->m_BoostSocket.remote_endpoint().address().to_v4().to_string();
			m_uPort = this->m_BoostSocket.remote_endpoint().port();
			DF_INFO << "<NetConnect::NetConnect> New Connect " << m_sIP << ":" << m_uPort << DF_END;
		}
		catch (std::exception& e)
		{
			e.what();
		}
		asyncRecvHead();
	}

	// -----------------------------------------------------------------------
	void NetConnect::asyncRecvHead(void)
	{
		if (isShutdown())
		{
			return;
		}
		// 特殊处理兼容无协议发送用来做log输出
		if (m_pNetWork->getIsBytesMsg())
		{
			m_RecvCache.reset();
			m_RecvCache.moveWriteFence(7);
			// 移动4个字节
			m_BoostSocket.async_read_some(boost::asio::buffer(m_RecvCache.getWriteFence(), (size_t)(Config::MAX_UINT16)), //这里注意用正确的头指针和大小)
				boost::bind(&NetConnect::handleReadBytesMsg, shared_from_this(),
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred));
			return;
		}

		// 这里明确的重置当前消息接收buf
		m_RecvCache.reset();
		boost::asio::async_read(m_BoostSocket,
			boost::asio::buffer(m_RecvCache.getHeadPtr(), sizeof(MessageBase)),
			boost::bind(&NetConnect::handleReadMsgHead, shared_from_this(),
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
	}
	// -----------------------------------------------------------------------
	void NetConnect::asyncRecvBody(void)
	{
		if (isShutdown())
		{
			return;
		}

		MessageBase* pMsg = static_cast<MessageBase*>(m_RecvCache.getHeadPtr());
		boost::asio::async_read(m_BoostSocket,
			boost::asio::buffer(m_RecvCache.getWriteFence(), pMsg->getSize() - sizeof(MessageBase)), //这里注意用正确的头指针和大小
			boost::bind(&NetConnect::handleReadMsgBody, shared_from_this(),
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
	}
	// -----------------------------------------------------------------------
	unsigned short NetConnect::asyncSendBlock(void)
	{
		if (isShutdown())
		{
			return 0;
		}
		void* pHead = NULL;
		unsigned short uSize = 0;
		// 对m_SendBuf的操作要加线程锁
		m_SendMutex.lock();
		// 尝试从发送buf中拿出一块数据进行发送
		bool ret = m_SendBuf.holdBlock(&pHead, uSize);
		m_SendMutex.unlock();
		// 如果从发送消息缓冲中hold不出数据，则不发送
		if (!ret)
		{
			return 0;
		}
		// 异步发送消息之
		boost::asio::async_write(m_BoostSocket,
			boost::asio::buffer(pHead, uSize),
			boost::bind(&NetConnect::handleWriteMsg, shared_from_this(),
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
		// 返回发送了多少
		return uSize;
	}

	// -----------------------------------------------------------------------
	void NetConnect::handleReadMsgHead(const boost::system::error_code& errorCode, size_t uTransferredBytes)
	{
		if (isShutdown())
		{
			return;
		}
		if (errorCode)
		{
			shutdown(enNetConnect_RemoteClose);
			return;
		}
		MessageBase* pMsg = static_cast<MessageBase*>(m_RecvCache.getHeadPtr());
		// 消息错误,长度小于
		if (pMsg->getSize() < sizeof(MessageBase) || pMsg->getSize() > m_RecvCache.getCanWriteSize())
		{
#if DF_TARGET_PLATFORM == DF_PLATFORM_WINDOWS
			DF_EXC << "Error Msg Length, Type(" << pMsg->getType() << ") Size(" << pMsg->getSize() << ")" << DF_END;
#endif
			shutdown(enNetConnect_MsgError);
			return;
		}

		// 这里明确说明已经接收了消息头，移动读指针
		m_RecvCache.moveWriteFence(sizeof(MessageBase));
		/*
		如果消息只有消息头，则直接接收完成
		注意，此时的消息肯定是4的倍数
		*/
		if (pMsg->getSize() == sizeof(MessageBase))
		{
			if (recvCompletionMsg())
			{
				shutdown(enNetConnect_RecvBufFull);
				DF_EXC << "session(" << getSessionID() << ") recv msg buf is full." << DF_END;
				return;
			}

			asyncRecvHead();
		}
		else
		{
			asyncRecvBody();
		}
	}
	// -----------------------------------------------------------------------
	void NetConnect::handleReadMsgBody(const boost::system::error_code& errorCode, size_t uTransferredBytes)
	{
		if (isShutdown())
		{
			return;
		}
		if (errorCode)
		{
			shutdown(enNetConnect_RemoteClose);
			return;
		}
		
		MessageBase* pMsg = static_cast<MessageBase*>(m_RecvCache.getHeadPtr());
		// 注意，这里消息长度可能不是字节对齐的，要进行修正
		pMsg->align();

		// 这里明确说明已经接收了消息体，移动读指针
		m_RecvCache.moveWriteFence(pMsg->getSize() - sizeof(MessageBase));

		// 如果不能写入，说明接收消息缓存满了，断开连接
		if (!recvCompletionMsg())
		{
			shutdown(enNetConnect_RecvBufFull);
			DF_EXC << "session(" << getSessionID() << ") recv msg buf is full." << DF_END;
			return;
		}
		// 继续接收消息头
		asyncRecvHead();
	}
	// -----------------------------------------------------------------------
	void NetConnect::handleReadBytesMsg(const boost::system::error_code& errorCode, size_t uTransferredBytes)
	{
		if (isShutdown())
		{
			return;
		}
		if (errorCode)
		{
			shutdown(enNetConnect_RemoteClose);
			return;
		}

		// 添加消息头
		memcpy(m_RecvCache.getHeadPtr(), &MessageBase(static_cast<unsigned short>(uTransferredBytes + 7), Config::MAX_UINT16), 4);
		// 添加string 头
		char st = -112;
		memcpy(m_RecvCache.getHeadPtr(4), (void*)(&st), 1);
		memcpy(m_RecvCache.getHeadPtr(5), (void*)(&uTransferredBytes), 2);
		MessageBase* pMsg = static_cast<MessageBase*>(m_RecvCache.getHeadPtr());
		// 注意，这里消息长度可能不是字节对齐的，要进行修正
		pMsg->align();
		// 这里明确说明已经接收了消息体，移动读指针
		m_RecvCache.moveWriteFence(static_cast<unsigned short>(uTransferredBytes));
		// 如果不能写入，说明接收消息缓存满了，断开连接
		if (!recvCompletionMsg())
		{
			shutdown(enNetConnect_RecvBufFull);
			DF_EXC << "session(" << getSessionID() << ") recv msg buf is full." << DF_END;
			return;
		}
		// 继续接收消息头
		asyncRecvHead();
	}

	// -----------------------------------------------------------------------
	void NetConnect::handleWriteMsg(const boost::system::error_code& errorCode, size_t uTransferredBytes)
	{
		// 对m_SendBuf的操作要加线程锁
		m_SendMutex.lock();
		// 首先要归还hold住的发送字节块
		m_SendBuf.releaseBlock();
		m_SendMutex.unlock();

		if (isShutdown())
		{
			return;
		}
		if (errorCode)
		{
			shutdown(enNetConnect_RemoteClose);
			return;
		}

		asyncSendBlock();

		//if (m_uWho != m_pNetWork->asyncSendWho())
		//{
		//	asyncSendBlock();
		//}
	}
	// -----------------------------------------------------------------------
	bool NetConnect::recvCompletionMsg(void)
	{
		MessageBase* pMsg = static_cast<MessageBase*>(m_RecvCache.getHeadPtr());
		// 对m_RecvBuf的操作要加线程锁
		m_RecvMutex.lock();
		// 尝试将消息些入接收消息buf
		bool ret = m_RecvBuf.writeMessage(pMsg);
		m_RecvMutex.unlock();
		return ret;
	}
	// -----------------------------------------------------------------------
	void NetConnect::shutdown(NetConnect::NetConnectState state)
	{
		if (!isShutdown())
		{
			try
			{

				DF_INFO << "<NetConnect::shutdown> shutdown " << m_sIP << ":" << m_uPort << DF_END;

				// 关闭socket
				m_eState = state;
				m_BoostSocket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
#if DF_TARGET_PLATFORM == DF_PLATFORM_WINDOWS
				m_BoostSocket.close();
#else
				m_BoostSocket.cancel();
#endif
			}
			catch (std::exception& e)
			{
				e.what();
			}
		}
	}
	// -----------------------------------------------------------------------
	bool NetConnect::isShutdown(void)const
	{
		return enNetConnect_Work != m_eState;
	}
	// -----------------------------------------------------------------------
	void NetConnect::sendBytes(const void* pHead, unsigned short uSize)
	{
		if (!pHead)
		{
			DF_EXC << "<NetConnect::sendBytes> shutdown " << "session(" << getSessionID() << ") pHead is NULL." << DF_END;
			return;
		}
		if (isShutdown())
		{
			return;
		}
		// 对m_SendBuf的操作要加线程锁
		m_SendMutex.lock();
		// 向字节块中写入字节
		bool ret = m_SendBuf.writeBytes(pHead, uSize);
		m_SendMutex.unlock();
		// 如果不能再向发送buf中写入数据，说明发送buf满了，断掉这个连接
		if (!ret)
		{
			DF_EXC << "session(" << getSessionID() << ") send msg buf is full." << DF_END;
			shutdown(enNetConnect_SendBufFull);
			return;
		}

		asyncSendBlock();
		//if (m_uWho != m_pNetWork->AsyncSendWho())
		//{
		//	asyncSendBlock();
		//}
	}
	// -----------------------------------------------------------------------
	void NetConnect::sendMsg(MessageBase* pMsg)
	{
		sendBytes(pMsg, pMsg->getSize());
	}
	// -----------------------------------------------------------------------
	bool NetConnect::readMessage(MessageBase** pMsg)
	{
		if (isShutdown())
		{
			return false;
		}
		// 这里readMsg只有逻辑线程会调用，这里不要加锁
		if (m_RecvBuf.readMessage(pMsg))
		{
			return true;
		}
		else
		{
			// MoveToNextReadBuf要加线程锁
			m_RecvMutex.lock();
			bool ret = m_RecvBuf.moveToNextReadBuf();
			m_RecvMutex.unlock();
			if (ret)
			{
				return m_RecvBuf.readMessage(pMsg);
			}
			else
			{
				return false;
			}
		}
		return false;
	}
	// -----------------------------------------------------------------------
	bool NetConnect::isSendOver(void)const
	{
		return m_SendBuf.isEmpty();
	}
	// -----------------------------------------------------------------------
	BoostSocket& NetConnect::getSocket(void)
	{
		return m_BoostSocket;
	}
	// -----------------------------------------------------------------------
	void NetConnect::setSessionID(unsigned int uSessionID)
	{
		m_uSessionID = uSessionID;
	}
	// -----------------------------------------------------------------------
	unsigned int NetConnect::getSessionID(void)const
	{
		return m_uSessionID;
	}
	// -----------------------------------------------------------------------
	unsigned int NetConnect::getConnectTime(void)const
	{
		return m_uConnectTime;
	}
	// -----------------------------------------------------------------------
	void NetConnect::setBindPoint(void* pBindPoint)
	{
		m_pBindPoint = pBindPoint;
	}
	// -----------------------------------------------------------------------
	void* NetConnect::getBindPoint(void)const
	{
		return m_pBindPoint;
	}
	// -----------------------------------------------------------------------
	void NetConnect::setWho(unsigned int uWho)
	{
		m_uWho = uWho;
	}
	// -----------------------------------------------------------------------
	unsigned int NetConnect::getWho(void)const
	{
		return m_uWho;
	}
	// -----------------------------------------------------------------------
	const char* NetConnect::getIP(void)const
	{
		return m_sIP.c_str();
	}
	// -----------------------------------------------------------------------
	unsigned short NetConnect::getPort(void)const
	{
		return m_uPort;
	}
}