/************************************************************************
* @File			:	DFLuaSystem.h
* @Author		:	Sword
* @DateTime		:	2015.3.9 
* @Description	:
*
*
*
*
************************************************************************/
#ifndef __DFLuaSystem_H__
#define __DFLuaSystem_H__

#include "DFPrerequisite.h"

// -----------------------------------------------------------------------
// @brief lua自动管理释放
//--lua gc
//--collectgarbage("stop")
//--collectgarbage("setpause", 100)
//--collectgarbage("setstepmul", 5000)	

namespace DF{
	// -----------------------------------------------------------------------
	// @brief lua脚本系统
	class DFExport LuaSystem
	{
	public:
		// -----------------------------------------------------------------------
		// @brief 虚构函数
		virtual ~LuaSystem(void);
		// -----------------------------------------------------------------------
		// @brief 获取单例
		static LuaSystem* instancePtr(void);
		// -----------------------------------------------------------------------
		// @brief 释放单例
		static void uninstance(void);
		// -----------------------------------------------------------------------
		// @brief 初始化服务器脚本
		// @param[pServer] 服务器对象 
		void initServer(BaseServer* pServer);
		// -----------------------------------------------------------------------
		// @brief 设置是否为debug脚本
		void setDebug(bool bDebug);
		// -----------------------------------------------------------------------
		// @brief 脚本执行一段代码
		// @param[pStr] 代码 
		void doString(const char* pStr);
		// -----------------------------------------------------------------------
		// @brief 脚本执行一段代码
		// @param[str] 代码 
		void doString(const std::string& str);
		// -----------------------------------------------------------------------
		// @brief 脚本执行一个文件
		// @param[sFileName] 文件名字
		void doFile(const std::string& sFileName);
		// -----------------------------------------------------------------------
		// @brief 脚本重新加载一个模块
		// @param[sModuleFileName] 模块名
		void reload(const std::string& sModuleFileName);		
		// -----------------------------------------------------------------------
		// @brief 打开运行当前文件返回输出
		// @param[file] 文件名
		void enableReturn(const char* file);	
		// -----------------------------------------------------------------------
		// @brief 关闭
		void disableReturn(void);
		// -----------------------------------------------------------------------
		// @brief 添加一个脚本路径查找
		// @param[path] 路径
		void addSearchPath(const char* path);
		// -----------------------------------------------------------------------
		// @brief 添加一个脚本读取方案
		void addLoaderFunction(void);
		// -----------------------------------------------------------------------
		// @brief 从内存中读取
		// @param[pBuffer] 数据
		// @param[uSize] 数据大小
		// @param[sName] 数据名字
		void loadBuffer(const char* pBuffer, unsigned int uSize, const std::string& sName);
		// -----------------------------------------------------------------------
		// @brief 保存top值
		void commit(void);
		// -----------------------------------------------------------------------
		// @brief 还原top值
		void reduction(void);
		// -----------------------------------------------------------------------
		// @brief 设置一个全局名字
		// @param[key] 关键字 
		void setGlobalName(const char* key);
		// -----------------------------------------------------------------------
		// @brief 获取一个全局名字
		// @param[key] 关键字
		void getGlobalName(const char* key);
		// -----------------------------------------------------------------------
		// @brief 获取一个全局函数
		// @param[sName] 函数名字
		LuaFunction* getGlobalFunction(const std::string& sName);
		// -----------------------------------------------------------------------
		// @brief 获取一个LuaSatck
		// @param[sName] 名字
		LuaStack getLuaStack(const std::string& sName);
		// -----------------------------------------------------------------------
		// @brief 从管理中移除主要用处储存lua部分数据不被gc回收掉
		// @param[sRootTag] 名字标签用来快速搜索
		// @param[iRootTag] ID标签来快速搜索
		void removeValueFromRoot(const char* sRootTag, int iRootTag);
		// -----------------------------------------------------------------------
		// @brief 获取调试文件
		std::string getDebugFile(void)const;
		// -----------------------------------------------------------------------
		// @brief 获取配置文件路径
		const char* getRootPath(void)const;
		// -----------------------------------------------------------------------
		// @brief 获取脚本对象Lua_state*
		void* getScript(void);
		// -----------------------------------------------------------------------
		// @brief 获取错误位置
		int getPosErr(void)const;
		// -----------------------------------------------------------------------
		// @brief 获取栈头
		int getTop(void)const;
		// -----------------------------------------------------------------------
		// @brief 是否运行消息调试的时候用来打印消息数据
		bool getIsRunScriptMsg(void);
		// -----------------------------------------------------------------------
		// @brief 添加调试打印行
		// @param[sPrint] 数据
		void addRunScirptPrint(const std::string& sPrint);
		// -----------------------------------------------------------------------
		// @brief 设置是否打开脚本消息
		void setIsRunScriptMsg(bool isRunScriptMsg);
		// -----------------------------------------------------------------------
		// @brief 获取脚本打印数据
		const char* getRunScirptPrint(void)const;
		// -----------------------------------------------------------------------
		// @brief 读取一个文件夹里所有文件返回一个lua table
		void loadFiles(const std::string& path);
		// -----------------------------------------------------------------------
		// @brief 读取一个所有文件夹里所有文件返回一个lua table
		void loadAllFiles(const std::string& strFolderPath, const std::string& curPath);
		// -----------------------------------------------------------------------
		// @brief 获取服务器对象
		BaseServer* getServer(void)const;

	protected:
		LuaSystem(void);

	protected:
		std::string					m_sDebugFile;
		std::string					m_sRootPath;
		std::string					m_sPrint;

		static LuaSystem*			m_pInstance;
		void*						m_pScript;
		BaseServer*					m_pBaseServer;
		int							m_iTop;
		int							m_pos_err;
		bool						m_isRunScriptMsg;
	};
}





#endif