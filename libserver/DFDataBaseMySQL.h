/************************************************************************
* @File			:	DFDataBaseMySQL.h
* @Author		:	Sword
* @Description	:
*
*
*
*
************************************************************************/
#ifndef __DFDataBaseMySQL_H__
#define __DFDataBaseMySQL_H__

#include "DFPrerequisite.h"


namespace DF{
	// -----------------------------------------------------------------------
	// @brief 数据库
	class DFExport DataBaseMySQL
	{
	public:
		// -----------------------------------------------------------------------
		// @brief 析构函数
		~DataBaseMySQL(void);
		// -----------------------------------------------------------------------
		// @brief 构造函数
		DataBaseMySQL(void);
		// -----------------------------------------------------------------------
		// @brief 连接一个数据库
		// @param[host] 数据库地址
		// @param[user] 用户名字
		// @param[passwd] 用户密码
		// @param[port] 端口号
		// @param[ip] IP地址
		bool connect(const char* host, const char* user, const char* passwd, unsigned short port, const char* ip = NULL);
		// -----------------------------------------------------------------------
		// @brief 执行一条数据库语句(主要用来读取数据库)
		// @param[sql] 数据库语句
		// @param[pPackMsg] 添加打包数据
		bool execute(const char* sql, PackMessage* pPackMsg = NULL);
		// -----------------------------------------------------------------------
		// @brief 执行一条数据库语句(主要用来写入库数据)
		// @param[sql] 数据库语句
		// @param[unpack] 解包数据
		bool executeStmt(const char* sql, UnpackMessage* unpack);
		// -----------------------------------------------------------------------
		// @brief 初始化(主要用来写入库数据)
		// @param[sql] 数据库语句
		bool initStmt(const char* sql);
		// @brief 添加字符串(主要用来写入库数据)
		void pushString(const char* val);
		// @brief 添加二级制数据(主要用来写入库数据)
		void pushBlob(const char* val, unsigned int len);
		// @brief 添加带类型二级制数据(主要用来写入库数据)
		void pushData(int type, const char* val, unsigned int len = 0);
		// @brief 执行(主要用来写入库数据)
		bool executeStmt(void);
		// -----------------------------------------------------------------------
		// @brief 获取用户名字
		const char* getUser(void)const;
		// -----------------------------------------------------------------------
		// @brief 获取密码
		const char* getPassword(void)const;
		// -----------------------------------------------------------------------
		// @brief 获取地址
		const char* getHost(void)const;
		// -----------------------------------------------------------------------
		// @brief 获取IP
		const char* getIP(void)const;
		// -----------------------------------------------------------------------
		// @brief 获取端口
		unsigned short getPort(void)const;

	protected:
		std::string							m_sUser;
		std::string							m_sPawd;
		std::string							m_sHost;
		std::string							m_sIP;
		unsigned short						m_uPort;
		
	};

}


#endif
