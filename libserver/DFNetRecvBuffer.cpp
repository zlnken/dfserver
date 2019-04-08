#include "DFNetRecvBuffer.h"
#include "DFNetBuffer.h"
#include "DFMessageBase.h"
#include "DFIO.h"
#include "DFDateTime.h"
namespace DF{
	// -----------------------------------------------------------------------
	NetRecvBuffer::~NetRecvBuffer(void)
	{
		DF_SAFE_DELETE(m_pReadBuf);
		DF_SAFE_DELETE(m_pWriteBuf);
		while (!m_BufQueue.empty())
		{
			DF_SAFE_DELETE(m_BufQueue.front());
			this->m_BufQueue.pop();
		}
	}
	// -----------------------------------------------------------------------
	NetRecvBuffer::NetRecvBuffer(unsigned short uBlockSize, unsigned short uBlockNum):
	m_pReadBuf(NULL),
	m_pWriteBuf(NULL),
	m_uBlockNum(uBlockNum),
	m_BufQueue()
	{
		m_pReadBuf = new NetBuffer(uBlockSize);
		m_pWriteBuf = new NetBuffer(uBlockSize);
	}
	// -----------------------------------------------------------------------
	bool NetRecvBuffer::writeMessage(MessageBase* pMsg)
	{
		// 断言下长度
#if DF_PLATFORM_WINDOWS == DF_TARGET_PLATFORM
		DF_ASSERT(pMsg->getSize() % 4 == 0);
#endif

		// 要写入的字节数不能超过block的最大大小
		if (m_pWriteBuf->getMaxSize() < pMsg->getSize())
		{
			DF_EXC << "recv a long message(" << pMsg->getType() << "," << pMsg->getSize() << ")" << "rather than block size(" << m_pWriteBuf->getMaxSize() << ")." << DF_END;
			return false;
		}
		// 字节太长
		if (m_pWriteBuf->getCanWriteSize() < pMsg->getSize())
		{
			// 并且此时扩容也不行了，则返回失败
			if (m_BufQueue.size() > m_uBlockNum)
			{
				//DF_EXC << "<NetRecvBuffer::writeMessage> can write message size is full" << DF_END;
				return false;
			}
			
			m_BufQueue.push(m_pWriteBuf);
			m_pWriteBuf = new NetBuffer(m_pWriteBuf->getMaxSize());
		}

		// 将字节写入写buf
		this->m_pWriteBuf->writeBytes(pMsg, pMsg->getSize());
		this->m_pWriteBuf->moveWriteFence(pMsg->getSize());
		return true;
	}
	// -----------------------------------------------------------------------
	bool NetRecvBuffer::readMessage(MessageBase** pMsg)
	{
		// 当前读buf中没消息了
		if (0 == m_pReadBuf->getCanReadSize())
		{
			//DF_EXC << "<NetRecvBuffer::readMessage> can read size is 0" << DF_END;
			return false;
		}

		MessageBase* pReadMsg = static_cast<MessageBase*>(m_pReadBuf->getReadFence());
		DF_ASSERT(pReadMsg->getSize() <= m_pReadBuf->getCanReadSize());
		m_pReadBuf->moveReadFence(pReadMsg->getSize());
		*pMsg = pReadMsg;
		return true;
	}
	// -----------------------------------------------------------------------
	bool NetRecvBuffer::moveToNextReadBuf(void)
	{

#if DF_PLATFORM_WINDOWS == DF_TARGET_PLATFORM
		DF_ASSERT(0 == m_pReadBuf->getCanReadSize());
#endif
		// 如果扩容列表为空，尝试直接交换写buf和读buf
		if (m_BufQueue.empty())
		{
			// 如果写buf里面有数据，则真正的交换两个buf
			if (m_pWriteBuf->getCanReadSize())
			{
				std::swap(m_pReadBuf, m_pWriteBuf);
				// 初始化写buf
				m_pWriteBuf->reset();
			}
			else
			{
				return false;
			}
		}
		else
		{
			delete m_pReadBuf;
			m_pReadBuf = this->m_BufQueue.front();
			m_BufQueue.pop();
		}
		return true;
	}
}