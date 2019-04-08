/************************************************************************
* @File			:	main.h
* @Author		:	Sword
* @Description	:	登录服务器入口
*
*
*
*
************************************************************************/
#include <DFLuaSystem.h>
#include "ToolsServer.h"

// -----------------------------------------------------------------------
// @brief 主函数
// @param[argc] 参数
// @param[argv] 参数
int main(int argc, char *argv[])
{
	// 初始化进程
	ToolsServer::instancePtr()->init(argc, argv, 1010, DF::Config::MAX_CONNECT, DF::Config::MAX_THREAD);
	// 脚本逻辑初始化
	DF::LuaSystem::instancePtr()->initServer(ToolsServer::instancePtr());
	// 添加脚本路径
	DF::LuaSystem::instancePtr()->addSearchPath("./media/script");
	DF::LuaSystem::instancePtr()->addSearchPath("/../../../media/script");
	// 执行主脚本文件
	DF::LuaSystem::instancePtr()->doFile("tools.ToolsServerCall");
	// 服务器循环运行
	ToolsServer::instancePtr()->loop();
	// 服务器结束
	ToolsServer::instancePtr()->finish();
	// 服务器释放
	ToolsServer::unintance();
	return 0;
}
