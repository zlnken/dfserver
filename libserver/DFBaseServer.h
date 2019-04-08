/************************************************************************
* @File			:	DFBaseServer.h
* @Author		:	Sword
* @Description	:
*
*
*
*
************************************************************************/
#ifndef __DFBaseServer_H__
#define __DFBaseServer_H__
#include "DFPrerequisite.h"

namespace DF{
	// ------------------------------------------------------------------------
	// @brief 服务器基类
	class DFExport BaseServer
	{

	public:
		//------------------------------------------------------------------------
		// @brief 基类触发枚举
		enum BaseServerTriggerEnum
		{
			// @brief 服务器启动回调
			BSTE_OnStar,
			// @brief 服务器丢失回调
			BSTE_OnLost,
			// @brief 服务器响应消息回调
			BSTE_OnMsg,
			// @brief 每分钟前回调
			BSTE_BeforeNewMinute,
			// @brief 每小时前回调
			BSTE_BeforeNewHour,
			// @brief 每天前回调
			BSTE_BeforeNewDay,
			// @brief 每分钟后回调
			BSTE_AfterNewMinute,
			// @brief 每小时后回调
			BSTE_AfterNewHour,
			// @brief 每天后回调
			BSTE_AfterNewDay,
			// @brief 每秒回调
			BSTE_PerSecond,
			// @brief 键盘按下回调
			BSTE_KeyboardKeyDown,
			// @brief 最大枚举数
			BSTE_MaxCount
		};


	public:
		// -----------------------------------------------------------------------
		// @brief 析构函数
		virtual ~BaseServer(void);
		// -----------------------------------------------------------------------
		// @brief 构造函数
		BaseServer(void);
		// -----------------------------------------------------------------------
		// @brief 初始化
		// @param[argc] 参数个数
		// @param[argv] 值
		// @param[port] 端口号
		// @param[maxConnect] 最大连接数量
		// @param[maxThread] 最大线程数量
		virtual void init(int argc, char *argv[], unsigned short port, unsigned int maxConnect, unsigned short maxThread, bool isBytesMsg=false);
		// -----------------------------------------------------------------------
		// @brief 结束服务器
		virtual void finish(void);
		// -----------------------------------------------------------------------
		// @brief 运行服务器
		virtual void loop(void);
		// -----------------------------------------------------------------------
		// @brief 发送一个打包消息一个[bytes]
		// @param[pHead] 数据
		// @param[uSize] 数据大小
		void sendBytes(unsigned int uSessionID, const void* pHead, unsigned short uSize);
		// -----------------------------------------------------------------------
		// @brief 发送一个打包消息一个[PackMessage]
		// @param[uSessionID] 发送给谁
		void sendPackMsg(unsigned int uSessionID);
		// -----------------------------------------------------------------------
		// @brief 发送一个打包数据,是一个目前只有lua插件所以数据是lua table 
		// @param[uSessionID] 发送给谁
		// @param[uMsgType] 消息类型
		void sendObject(unsigned int uSessionID, unsigned short uMsgType);
		// -----------------------------------------------------------------------
		// @brief 发送一个打包数据到某个服务器[服务器发送数据给服务器]
		// @param[uWho] 发送给谁
		// @param[uMsgType] 消息类型
		void sendWhoPackMsg(unsigned int uWho);
		// -----------------------------------------------------------------------
		// @brief 发送一个打包数据到某个服务器[服务器发送数据给服务器]
		// @param[uWho] 发送给谁
		// @param[uMsgType] 消息类型
		void sendWhoObject(unsigned int uWho, unsigned short uMsgType);
		// -----------------------------------------------------------------------
		// @brief 连接一个ip[]
		// @param[ip] 地址
		// @param[uPort] 端口号
		// @param[uwho] 连接那个服务器
		bool connect(const char* ip, unsigned int uPort, unsigned short uWho);
		// -----------------------------------------------------------------------
		// @brief 断开一个连接
		// @param[uSessionID] 谁
		bool disConnect(unsigned int uSessionID);
		// -----------------------------------------------------------------------
		// @brief 查看是否是连接中
		// @param[uSessionID] 谁
		bool hasConnect(unsigned int uSessionID)const;
		// -----------------------------------------------------------------------
		// @brief 查看是否是已经推送玩消息
		// @param[uSessionID] 谁
		bool isSendOver(unsigned int uSessionID)const;
		// -----------------------------------------------------------------------
		// @brief 获取网络
		NetWork* getNetWork(void);
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
		// -----------------------------------------------------------------------
		// @brief 设置一个世界id
		// @param[uWorld] 服务器id
		void setWorld(unsigned short uWorld);
		// -----------------------------------------------------------------------
		// @brief 分配一个全局id
		double allocGloablID(void);
		// -----------------------------------------------------------------------
		// @brief 获取当前连接
		NetConnect* getCurNetConnect(void)const;
		// -----------------------------------------------------------------------
		// @brief 获取进程
		Process* getProcess(void);
		// -----------------------------------------------------------------------
		// @brief 获取时间
		DateTime* getDateTime(void);
		// -----------------------------------------------------------------------
		// @brief 获取IP地址
		const char* getIP(void)const;
		// -----------------------------------------------------------------------
		// @brief 获取端口号
		unsigned short getProt(void)const;
		// -----------------------------------------------------------------------
		// @brief 设置触发器
		// @param[eType] 触发类型
		// @param[pTrigger] 触发器实体 
		void setTrigger(BaseServerTriggerEnum eType, Trigger* pTrigger);

	protected:
		// -----------------------------------------------------------------------
		// @brief 丢失
		void onLost(void);
		// -----------------------------------------------------------------------
		// @brief 收取消息
		void onMsg(void);
		// -----------------------------------------------------------------------
		// @brief 更新
		void update(void);
		// -----------------------------------------------------------------------
		// @brief 每天前
		void callBeforeNewDay(void);
		// -----------------------------------------------------------------------
		// @brief 每小时前
		void callBeforeNewHour(void);
		// -----------------------------------------------------------------------
		// @brief 每分钟前
		void callBeforeNewMinute(void);
		// -----------------------------------------------------------------------
		// @brief 每秒
		void callPerSecond(void);
		// -----------------------------------------------------------------------
		// @brief 每日后
		void callAfterNewDay(void);
		// -----------------------------------------------------------------------
		// @brief 每小时前
		void callAfterNewHour(void);
		// -----------------------------------------------------------------------
		// @brief 每分钟前
		void callAfterNewMinute(void);
		// -----------------------------------------------------------------------
		// @brief 键盘响应
		void onKeyboardKeyDown(unsigned short keyCode);

	protected:
		NetWork*						m_pNetWork;			// @brief 网络
		PackMessage*					m_pPackMessage;		// @brief 打包
		UnpackMessage*					m_pUnpackMessage;	// @brief 解包
		DateTime*						m_pDateTime;		// @brief 时间
		Process*						m_pProcess;			// @brief 进程
		GlobalIDAlloc*					m_pGlobalIDAlloc;	// @brief 全局ID分配
		Trigger*						m_pTrigger[BSTE_MaxCount]; // @brief 触发器
	};
}
	
#endif
