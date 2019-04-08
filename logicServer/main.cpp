/************************************************************************
* @File			:	main.h
* @Author		:	Sword
* @Description	:	逻辑服务器入口
* 
*
*
*
************************************************************************/
#include "LogicServer.h"
#include <DFLuaSystem.h>

// -----------------------------------------------------------------------
// @brief 主函数
// @param[argc] 参数
// @param[argv] 参数
int main(int argc, char *argv[])
{	
	// 初始化进程
	LogicServer::instancePtr()->init(argc, argv, DF::Config::DEFAULT_PORT, DF::Config::MAX_CONNECT, DF::Config::MAX_THREAD);
	// 脚本逻辑初始化
	DF::LuaSystem::instancePtr()->initServer(LogicServer::instancePtr());
	// 添加脚本路径
	DF::LuaSystem::instancePtr()->addSearchPath("./media/file");
	DF::LuaSystem::instancePtr()->addSearchPath("./media/script");
	DF::LuaSystem::instancePtr()->addSearchPath("/../../../media/file");
	DF::LuaSystem::instancePtr()->addSearchPath("/../../../media/script");
	// 执行主脚本文件
	DF::LuaSystem::instancePtr()->doFile("logic.LogicServerCall");
	// 服务器循环运行
	LogicServer::instancePtr()->loop();
	// 服务器结束
	LogicServer::instancePtr()->finish();
	// 服务器释放
	LogicServer::unintance();
	return 0;
}
