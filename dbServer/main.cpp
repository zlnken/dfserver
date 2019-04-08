/************************************************************************
* @File			:	main.h
* @Author		:	Sword
* @Description	:	数据服务器入口
*
*
*
*
************************************************************************/
#include <DFLuaSystem.h>
#include <DFDataBaseServer.h>

// -----------------------------------------------------------------------
// @brief 主函数
// @param[argc] 参数
// @param[argv] 参数
int main(int argc, char *argv[])
{
	// 初始化进程
	DF::DataBaseServer::instancePtr()->init(argc, argv, DF::Config::DATA_BASE_PORT, DF::Config::MAX_CONNECT, DF::Config::MAX_THREAD);
	// 脚本逻辑初始化
	DF::LuaSystem::instancePtr()->initServer(DF::DataBaseServer::instancePtr());
	// 添加脚本路径
	DF::LuaSystem::instancePtr()->addSearchPath("./media/file");
	DF::LuaSystem::instancePtr()->addSearchPath("./media/script");
	DF::LuaSystem::instancePtr()->addSearchPath("/../../../media/file");
	DF::LuaSystem::instancePtr()->addSearchPath("/../../../media/script");
	// 执行主脚本文件
	DF::LuaSystem::instancePtr()->doFile("db.DataBaseServerCall");
	// 服务器循环运行
	DF::DataBaseServer::instancePtr()->loop();
	// 服务器结束
	DF::DataBaseServer::instancePtr()->finish();
	// 服务器释放
	DF::DataBaseServer::unintance();
	return 0;
}
