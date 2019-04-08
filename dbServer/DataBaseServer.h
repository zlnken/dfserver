/************************************************************************
* @File			:	DataBaseServer.h
* @Author		:	Sword
* @Description	:
*
*
*
*
************************************************************************/
#ifndef __LogicServer_H__
#define __LogicServer_H__
#include "DFPrerequisite.h"
#include "DFBaseServer.h"

// -----------------------------------------------------------------------
// @brief 逻辑服务器
class DataBaseServer : public DF::BaseServer
{
public:
	// -----------------------------------------------------------------------
	// @brief 析构函数
	virtual ~DataBaseServer(void);
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
	// @brief 运行
	void loop(void);
	// -----------------------------------------------------------------------
	// @brief 结束
	void finish(void);

private:
	// -----------------------------------------------------------------------
	// @brief 构造函数
	DataBaseServer(void);

private:
	static DataBaseServer*				m_pInstance;

};

#endif
