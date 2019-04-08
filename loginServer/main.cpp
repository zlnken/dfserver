/************************************************************************
* @File			:	main.h
* @Author		:	Sword
* @Description	:	登录服务器入口
*
*
*
*
************************************************************************/
#include "LoginServer.h"
#include <DFLuaSystem.h>



// -----------------------------------------------------------------------
// @brief 主函数
// @param[argc] 参数
// @param[argv] 参数
int main(int argc, char *argv[])
{
	// 初始化进程
	LoginServer::instancePtr()->init(argc, argv, DF::Config::LOGIN_PORT, DF::Config::MAX_CONNECT, DF::Config::MAX_THREAD);
	// 脚本逻辑初始化
	DF::LuaSystem::instancePtr()->initServer(LoginServer::instancePtr());
	// 添加脚本路径
	DF::LuaSystem::instancePtr()->addSearchPath("./media/file");
	DF::LuaSystem::instancePtr()->addSearchPath("./media/script");
	DF::LuaSystem::instancePtr()->addSearchPath("/../../../media/file");
	DF::LuaSystem::instancePtr()->addSearchPath("/../../../media/script");
	// 执行主脚本文件
	DF::LuaSystem::instancePtr()->doFile("login.LoginServerCall");
	// 服务器循环运行
	LoginServer::instancePtr()->loop();
	// 服务器结束
	LoginServer::instancePtr()->finish();
	// 服务器释放
	LoginServer::unintance();
	return 0;
}
