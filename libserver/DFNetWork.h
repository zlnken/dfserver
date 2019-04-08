/************************************************************************
* @File			:	DFNetWork.h
* @Author		:	Sword
* @Description	:
*
*
*
*
************************************************************************/
#ifndef __DFNetWork_H__
#define __DFNetWork_H__
#include "DFPrerequisite.h"
#include "DFNetConnect.h"
namespace DF{
	// -----------------------------------------------------------------------
	// @brief 网络工作
	class DFExport NetWork
	{
	public:
		typedef boost::unordered_map<unsigned int, NetConnect::ConnectSharedPtr>	NetConnectMap;
		typedef NetConnectMap::iterator												NetConnectMapIt;
		typedef NetConnectMap::const_iterator										NetConnectMapCIt;
		typedef std::set<unsigned int>												FreeAllocIDSet;
		typedef FreeAllocIDSet::iterator											FreeAllocIDSetIt;

	public:
		// -----------------------------------------------------------------------
		// @brief 析构函数
		~NetWork(void);
		// -----------------------------------------------------------------------
		// @brief 构造函数
		// @param[uMaxConnect] 最大连接数量
		// @param[uThread] 最大线程数量
		NetWork(unsigned int uMaxConnect, unsigned short uThread);
		// -----------------------------------------------------------------------
		// @brief 监听一个端口
		// @param[uPort] 端口号
		bool listenPort(unsigned int uPort);
		// -----------------------------------------------------------------------
		// @brief 开始运行
		void start(void);
		// -----------------------------------------------------------------------
		// @brief 停止运行
		void stop(void);
		// -----------------------------------------------------------------------
		// @brief 连接一个IP
		// @param[ip] IP地址
		// @param[uPort] 端口号
		// @param[uWho] 连接那个服务器
		bool connect(const char* ip, unsigned int uPort, unsigned short uWho);
		// -----------------------------------------------------------------------
		// @brief 清空一个连接
		// @param[uSessionID] 连接ID
		bool clearConnect(unsigned int uSessionID);
		// -----------------------------------------------------------------------
		// @brief 断开一个连接
		// @param[uSessionID] 连接ID
		bool disConnect(unsigned int uSessionID);
		// -----------------------------------------------------------------------
		// @brief 是否还连接
		// @param[uSessionID] 连接ID
		bool hasConnect(unsigned int uSessionID)const;
		// -----------------------------------------------------------------------
		// @brief 连接是否超时
		// @param[uSessionID] 连接ID
		bool isSendOver(unsigned int uSessionID)const;
		// -----------------------------------------------------------------------
		// @brief 当前连接是否已关闭
		bool getCurIsClose(void)const;
		// -----------------------------------------------------------------------
		// @brief 移动到下一条消息
		bool moveNextMsg(void);
		// -----------------------------------------------------------------------
		// @brief 获取套接字IOS
		BoostIOService& getISO(void);
		// -----------------------------------------------------------------------
		// @brief 获取是否在运行中
		bool getIsRun(void)const;
		// -----------------------------------------------------------------------
		// @brief 获取是否停止
		bool getIsStop(void)const;
		// -----------------------------------------------------------------------
		// @brief 获取当前消息
		MessageBase* getMessage(void)const;
		// -----------------------------------------------------------------------
		// @brief 获取当前连接
		NetConnect* getCurNetConnect(void)const;
		// -----------------------------------------------------------------------
		// @brief 查找一个连接
		NetConnect* findNetConnect(unsigned int uSessionID);
		// -----------------------------------------------------------------------
		// @brief 查找一个连接(服务器对应服务器)
		NetConnect* findNetConnectByWho(unsigned short uWho);
		// -----------------------------------------------------------------------
		// @brief 获取连接hash容器
		NetConnectMap& getNetConnectMap(void);
		// -----------------------------------------------------------------------
		// @brief 获取端口
		unsigned short getPort(void)const;
		// -----------------------------------------------------------------------
		// @brief 获取IP
		const char* getIP(void)const;
		// -----------------------------------------------------------------------
		// @brief 设置是否Bytes消息
		// @param[isStringMsg] 消息是否为String
		void setIsBytesMsg(bool isBytesMsg);
		// -----------------------------------------------------------------------
		// @brief 获取是否Bytes消息
		bool getIsBytesMsg(void)const;
		// -----------------------------------------------------------------------
		// @brief 获取打包实体
		PackMessage* getPackMessage(void)const;
		// -----------------------------------------------------------------------
		// @brief 获取解包
		UnpackMessage* getUnpackMessage(void)const;
		// -----------------------------------------------------------------------
		// @brief 设置一个打包实体
		// @param[pPackMsg] 实体
		void setPackMessage(PackMessage* pPackMsg);
		// -----------------------------------------------------------------------
		// @brief 设置一个解包实体
		// @param[pUnpackMsg] 实体
		void setUnpackMessage(UnpackMessage* pUnpackMsg);
	private:
		// -----------------------------------------------------------------------
		// @brief 异步接收连接
		void asyncAccept(void);
		// -----------------------------------------------------------------------
		// @brief 运行网络
		void boostAsioRun(void);
		// -----------------------------------------------------------------------
		// @brief 接收回调
		void boostAsyncAccept(NetConnect::ConnectSharedPtr& pNetConnect, const boost::system::error_code& error);
		// -----------------------------------------------------------------------
		// @brief id分配
		unsigned int allocSessionID(void);


	private:
		std::string			m_sIP;
		BoostThreads		m_pNetWorkThreads;
		BoostIOService		m_IOS;
		NetConnectMap		m_NetConnectMap;
		NetConnectMap		m_NetWhoConnectMap;


		FreeAllocIDSet		m_FreeAllocIDSet;
		BoostMutex			m_ConnectMutex;

		unsigned int		m_uMaxConnect;
		unsigned short		m_uMaxThread;
		unsigned short		m_uAsyncSendWho;
		unsigned short		m_uPort;

		BoostAcceptor*		m_pAcceptor;
		BoostThread*		m_pAsyncSendThread;
		NetConnect*			m_pCurConnect;
		MessageBase*		m_pCurMessage;

		bool				m_bIsRun;
		bool				m_bIsStop;
		bool				m_bLastConnectClose;
		bool				m_bIsBytesMsg;
		

	};
}


#endif