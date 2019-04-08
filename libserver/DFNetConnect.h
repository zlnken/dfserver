/************************************************************************
* @File			:	DFNetConnect.h
* @Author		:	Sword
* @Description	:
*
*
*
*
************************************************************************/
#ifndef __DFNetConnect_H__
#define __DFNetConnect_H__
#include "DFPrerequisite.h"
#include "DFNetBuffer.h"
#include "DFNetSendBuffer.h"
#include "DFNetRecvBuffer.h"

namespace DF{
	//------------------------------------------------------------------------
	// @brief 网络连接
	class DFExport NetConnect : public boost::enable_shared_from_this<NetConnect>
	{

	public:
		typedef boost::shared_ptr<NetConnect> ConnectSharedPtr;

	public:
		//------------------------------------------------------------------------
		// @brief 连接状态枚举
		enum NetConnectState
		{
			// @brief 工作状态
			enNetConnect_Work,
			// @brief 关闭状态
			enNetConnect_RemoteClose,
			// @brief 消息错误
			enNetConnect_MsgError,
			// @brief 网关错误
			enNetConnect_TGWError,
			// @brief 发送消息过长
			enNetConnect_SendBufFull,
			// @brief 收取消息过长
			enNetConnect_RecvBufFull,
			// @brief 连接已满
			enNetConnect_ConnectFull,
			// @brief 本地断开连接
			enNetConnect_LocalClose
		};

	public:
		// -----------------------------------------------------------------------
		// @brief 析构函数
		~NetConnect(void);
		// -----------------------------------------------------------------------
		// @brief 构造函数
		// @param[pNetWork] 工作网络
		NetConnect(NetWork* pNetWork);
		// -----------------------------------------------------------------------
		// @brief 开始
		void start(void);
		// -----------------------------------------------------------------------
		// @brief 关闭
		// @param[state] 关闭状态
		void shutdown(NetConnectState state);
		// -----------------------------------------------------------------------
		// @brief 是否关闭
		bool isShutdown(void)const;
		// -----------------------------------------------------------------------
		// @brief 发送数据
		// @param[pHead] 数据
		// @param[uSize] 数据大小
		void sendBytes(const void* pHead, unsigned short uSize);
		// -----------------------------------------------------------------------
		// @brief 发送一个消息
		// @param[pMsg] 消息
		void sendMsg(MessageBase* pMsg);
		// -----------------------------------------------------------------------
		// @brief 读取一个消息
		// @param[pMsg] 消息
		bool readMessage(MessageBase** pMsg);
		// -----------------------------------------------------------------------
		// @brief 是否发送超时
		bool isSendOver(void)const;
		// -----------------------------------------------------------------------
		// @brief 设置连接ID
		void setSessionID(unsigned int uSessionID);
		// -----------------------------------------------------------------------
		// @brief 获取连接ID
		unsigned int getSessionID(void)const;
		// -----------------------------------------------------------------------
		// @brief 获取网络套接字
		BoostSocket& getSocket(void);
		// -----------------------------------------------------------------------
		// @brief 获取连接时间
		unsigned int getConnectTime(void)const;
		void* getBindPoint(void)const;
		void setBindPoint(void* pBindPoint);
		// -----------------------------------------------------------------------
		// @brief 设置绑定服务器ID
		void setWho(unsigned int uWho);
		// -----------------------------------------------------------------------
		// @brief 获取绑定服务器ID
		unsigned int getWho(void)const;
		// -----------------------------------------------------------------------
		// @brief 获取IP地址
		const char* getIP(void)const;
		// -----------------------------------------------------------------------
		// @brief 获取端口号
		unsigned short getPort(void)const;
		
	private:
		// -----------------------------------------------------------------------
		// @brief 异步收取头消息
		void asyncRecvHead(void);
		// -----------------------------------------------------------------------
		// @brief 异步收取实体消息
		void asyncRecvBody(void);
		// -----------------------------------------------------------------------
		// @brief 异步发送数据块
		unsigned short asyncSendBlock(void);
		// -----------------------------------------------------------------------
		// @brief 响应读取头消息
		// @param[errorCode] 错误代码
		// @param[uTransferredBytes] 收取大小
		void handleReadMsgHead(const boost::system::error_code& errorCode, size_t uTransferredBytes);
		// -----------------------------------------------------------------------
		// @brief 响应读取实体消息
		// @param[errorCode] 错误代码
		// @param[uTransferredBytes] 收取大小
		void handleReadMsgBody(const boost::system::error_code& errorCode, size_t uTransferredBytes);
		// -----------------------------------------------------------------------
		// @brief 响应写取消息
		// @param[errorCode] 错误代码
		// @param[uTransferredBytes] 收取大小
		void handleWriteMsg(const boost::system::error_code& errorCode, size_t uTransferredBytes);
		// -----------------------------------------------------------------------
		// @brief 是否收取完成
		bool recvCompletionMsg(void);

		// -----------------------------------------------------------------------
		// @brief 响应读取Bytes消息
		// @param[errorCode] 错误代码
		// @param[uTransferredBytes] 收取大小
		void handleReadBytesMsg(const boost::system::error_code& errorCode, size_t uTransferredBytes);


	protected:
		std::string				m_sIP;
		NetWork*				m_pNetWork;
		unsigned int			m_uSessionID;		//连接SessionID
		unsigned short			m_uWho;				//连接的类型
		unsigned short			m_uPort;			//端口
		NetConnectState			m_eState;			//连接的状态
		void*					m_pBindPoint;		//连接绑定的指针
		unsigned int			m_uConnectTime;		//该连接的创建时间
		BoostSocket				m_BoostSocket;		//连接的boost::socket
		NetSendBuffer			m_SendBuf;			//连接的发送buf
		NetRecvBuffer			m_RecvBuf;			//连接的接收buf
		NetBuffer				m_RecvCache;		//连接的当前消息接收buf
		BoostMutex				m_SendMutex;		//发送buf的线程锁
		BoostMutex				m_RecvMutex;		//接收buf的线程锁
	};
}



#endif