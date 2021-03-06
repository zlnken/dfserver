/************************************************************************
* @File			:	ToolsServer.h
* @Author		:	Sword
* @Description	:
*
*
*
*
************************************************************************/
#ifndef __ToolsServer_H__
#define __ToolsServer_H__
#include "DFPrerequisite.h"
#include "DFBaseServer.h"



// -----------------------------------------------------------------------
// @brief 逻辑服务器
class ToolsServer : public DF::BaseServer
{
public:
	// -----------------------------------------------------------------------
	// @brief 析构函数
	virtual ~ToolsServer(void);
	// -----------------------------------------------------------------------
	// @brief 获取单例
	static ToolsServer* instancePtr(void);
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
	ToolsServer(void);

private:
	static ToolsServer*				m_pInstance;

};

#endif
