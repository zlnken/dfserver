/************************************************************************
* @File			:	DFDataBaseServer.h
* @Author		:	Sword
* @Description	:
*
*
*
*
************************************************************************/

#ifndef __DFDataBaseServer_H__
#define __DFDataBaseServer_H__

#include "DFPrerequisite.h"
#include "DFBaseServer.h"
namespace DF{
	// -----------------------------------------------------------------------
	// @brief 数据服务器
	class DFExport DataBaseServer : public BaseServer
	{
	public:
		// -----------------------------------------------------------------------
		// @brief 析构函数
		~DataBaseServer(void);
		// -----------------------------------------------------------------------
		// @brief 获取单例
		static DataBaseServer* instancePtr(void);
		// -----------------------------------------------------------------------
		// @brief 移除单例
		static void unintance(void);
		// -----------------------------------------------------------------------
		// @brief 初始化
		void init(int argc, char *argv[], unsigned short port, unsigned int maxConnect, unsigned short maxThread);
		// -----------------------------------------------------------------------
		// @brief 初始化数据
		// @param[host] 地址
		// @param[user] 数据库用户名字
		// @param[passwd] 数据库密码
		// @param[port] 端口号
		// @param[ip] 地址
		bool initDataBase(const char* host, const char* user, const char* passwd, unsigned short port, const char* ip = NULL);
		// -----------------------------------------------------------------------
		// @brief 执行一条数据库指令
		// @param[sql] 指令
		bool executeSQL(const char* sql);
		// -----------------------------------------------------------------------
		// @brief 执行一条数据库指令(用于二级制数据, 可以查看dfserver/media/script/db/DataBaseMsgCall.lua/onMsgRoleSaveMails)
		// @param[sql] 指令
		// @param[unpack] 解压
		bool executeStmt(const char* sql, UnpackMessage* unpack);
		// -----------------------------------------------------------------------
		// @brief 运行数据服
		void loop(void);
		// -----------------------------------------------------------------------
		// @brief 结束数据服
		void finish(void);
		// -----------------------------------------------------------------------
		// @brief 设置触发器
		// @param[pOnMsgTri] 响应消息触发器
		// @param[pOnLostTri] 失去连接触发器
		void setTrigger(Trigger* pOnMsgTri, Trigger* pOnLostTri);
		// -----------------------------------------------------------------------
		// @brief 获取数据库实例
		DataBaseMySQL* getDataBaseMySQL(void)const;
	private:
		// -----------------------------------------------------------------------
		// @brief 构造函数
		DataBaseServer(void);
	private:		
		DataBaseMySQL*					m_pDBSql;
		static DataBaseServer*			m_pInstance;
	};
}


#endif