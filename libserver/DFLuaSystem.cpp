#include "DFLuaSystem.h"
#include "DFIO.h"
#include "DFDateTime.h"
#include "DFCrc32.h"
#include "DFLuaTable.h"
#include "DFLuaStack.h"
#include "DFLuaFunction.h"
#include "DFLuaPackMessage.h"
#include "DFLuaUnpackMessage.h"
#include "DFManager.h"
#include "DFLuaServerLib.h"
#include "DFDataBaseServer.h"
#include "DFBaseServer.h"
extern "C" {
#include <lua.hpp>
#include <tolua++.h>
#include "lua_cjson.h"
}


// -----------------------------------------------------------------------
namespace DF
{
	extern "C"
	{	
		static const size_t MaxStringLen = 16384;
		static WCHAR wszBuf[MaxStringLen + 1] = { 0 };
		static char tempBuf[MaxStringLen + 1] = { 0 };

		int DFExport lua_print_base(lua_State * luastate, int state)
		{
			int nargs = lua_gettop(luastate);
			std::string t;
			for (int i = 1; i <= nargs; i++)
			{
				if (lua_istable(luastate, i))
					t += "table";
				else if (lua_isnone(luastate, i))
					t += "none";
				else if (lua_isnil(luastate, i))
					t += "nil";
				else if (lua_isboolean(luastate, i))
				{
					if (lua_toboolean(luastate, i) != 0)
						t += "true";
					else
						t += "false";
				}
				else if (lua_isfunction(luastate, i))
					t += "function";
				else if (lua_islightuserdata(luastate, i))
					t += "lightuserdata";
				else if (lua_isthread(luastate, i))
					t += "thread";
				else
				{
					const char * str = lua_tostring(luastate, i);
					if (str)
						t += lua_tostring(luastate, i);
					else
						t += lua_typename(luastate, lua_type(luastate, i));
				}
				if (i != nargs)
					t += "\t";
			}

#if DF_TARGET_PLATFORM == DF_PLATFORM_WINDOWS
			size_t len = std::min<size_t>(MaxStringLen, t.size());
			memset(wszBuf, 0, MaxStringLen + 1);
			memset(tempBuf, 0, MaxStringLen + 1);
			memcpy(tempBuf, t.c_str(), len);
			tempBuf[len] = 0;
			MultiByteToWideChar(CP_UTF8, 0, tempBuf, -1, wszBuf, sizeof(wszBuf));
			WideCharToMultiByte(CP_ACP, 0, wszBuf, -1, tempBuf, sizeof(tempBuf), nullptr, FALSE);
			t = tempBuf;
#endif
			if (1 == state)
				DF_OUT << t << DF_END;
			else if ( 2 == state)
				DF_INFO << t << DF_END;
			else if (3 == state)
				DF_EXC << t << DF_END;
			else if (4 == state)
				DF_ERR << t << DF_END;

			if (3 == state)
			{
				lua_getglobal(luastate, "debug");
				lua_getfield(luastate, -1, "traceback");
				lua_call(luastate, 0, 1);
				const char* str = lua_tostring(luastate, -1);
				lua_pop(luastate, 1);
				lua_pop(luastate, 1);
				DF_EXC << str << DF_END;
			}


			if (LuaSystem::instancePtr()->getIsRunScriptMsg())
				LuaSystem::instancePtr()->addRunScirptPrint(t);


			return 1;
		}


		int DFExport lua_print(lua_State * luastate)
		{
			return lua_print_base(luastate, 1);
		}

		int DFExport lua_printInfo(lua_State * luastate)
		{
			return lua_print_base(luastate, 2);
		}

		int DFExport lua_warning(lua_State * luastate)
		{
			return lua_print_base(luastate, 3);
		}



		// -----------------------------------------------------------------------
		int DFExport lua_release_print(lua_State * luastate)
		{
			return 1;
		}

		// -----------------------------------------------------------------------
		int DFExport pcall_callback_err_fun(lua_State* L)
		{
			lua_Debug debug = {};
			int ret = lua_getstack(L, 2, &debug);
			lua_getinfo(L, "Sln", &debug);
			const char* err = lua_tostring(L, -1);
			lua_pop(L, 1);
			if (err)
			{
				DF_ERR << err << DF_END;
				if (LuaSystem::instancePtr()->getIsRunScriptMsg())
					LuaSystem::instancePtr()->addRunScirptPrint(err);
			}

			lua_getglobal(L, "debug");
			lua_getfield(L, -1, "traceback");
			lua_call(L, 0, 1);
			const char* traceback = lua_tostring(L, -1);
			lua_pop(L, 1);
			lua_pop(L, 1);

			if (traceback)
			{
				DF_ERR << traceback << DF_END;

				std::ofstream ifs;
				unsigned int last_unix_time = 0;
				DF::DateTime* pDateTime = DF::DateTime::instancePtr();
				unsigned int unix_time = pDateTime->getUnixTime();

				std::string year = boost::to_string(pDateTime->year());
				std::string month = boost::to_string(pDateTime->month());
				std::string day = boost::to_string(pDateTime->day());
				std::string hour = boost::to_string(pDateTime->hour());
				std::string minute = boost::to_string(pDateTime->minute());
				std::string second = boost::to_string(pDateTime->second());

				if (unix_time - last_unix_time > 86400)
				{
					if (ifs.is_open())
						ifs.close();
					std::string sRootPath = LuaSystem::instancePtr()->getRootPath();

					sRootPath += "log/traceback_" + year + "_" + month + "_" + day + ".log";
					ifs.open(sRootPath.c_str(), std::ios::app);
					last_unix_time = unix_time;
				}
				if (ifs.is_open())
				{
					std::string s = "----------------[" + year + "-" + month + "-" + day + " " + hour + ":" + minute + ":" + second + "]" + "--------------------\n";
					ifs.write(s.c_str(), s.length());

					ifs.write(err, strlen(err));
					ifs.put('\n');

					ifs.write(traceback, strlen(traceback));
					ifs.put('\n');

					ifs.flush();
				}

				if (LuaSystem::instancePtr()->getIsRunScriptMsg())	
					LuaSystem::instancePtr()->addRunScirptPrint(traceback);
			}
			return 0;
		}

		// -----------------------------------------------------------------------
		int DFExport luaScriptLoader(lua_State* L)
		{
			std::string sRootPath = LuaSystem::instancePtr()->getRootPath();
			static const std::string BYTECODE_FILE_EXT = ".lua";
			static const std::string NOT_BYTECODE_FILE_EXT = ".luac";

			std::string filename(luaL_checkstring(L, 1));
			std::string prefilename = filename;

			size_t pos = filename.rfind(BYTECODE_FILE_EXT);
			if (pos != std::string::npos)
			{
				filename = filename.substr(0, pos);
			}
			else
			{
				pos = filename.rfind(NOT_BYTECODE_FILE_EXT);
				if (pos == filename.length() - NOT_BYTECODE_FILE_EXT.length())
				{
					filename = filename.substr(0, pos);
				}
			}

			pos = filename.find_first_of(".");
			while (pos != std::string::npos)
			{
				filename.replace(pos, 1, "/");
				pos = filename.find_first_of(".");
			}

			lua_getglobal(L, "package");
			lua_getfield(L, -1, "path");

			std::string searchpath(lua_tostring(L, -1));
			lua_pop(L, 1);
			size_t begin = 0;
			size_t next = searchpath.find_first_of(";", 0);

			unsigned char* chunk = NULL;
			unsigned int chunkSize = 0;
			std::string chunkName;
			std::ifstream ifs;
			do
			{
				if (next == std::string::npos)
					next = searchpath.length();
				std::string prefix = searchpath.substr(begin, next);
				if (prefix[0] == '.' && prefix[1] == '/')
				{
					prefix = prefix.substr(2);
				}

				pos = prefix.find("?.lua");
				chunkName = prefix.substr(0, pos) + filename + BYTECODE_FILE_EXT;
				ifs.open((sRootPath + chunkName).c_str(), std::ios::binary);
				if (ifs.is_open())
				{
					ifs.seekg(0, std::ios::end);
					chunkSize = ifs.tellg();
					ifs.seekg(0, std::ios::beg);
					chunk = (unsigned char*)malloc(chunkSize);
					ifs.read((char*)chunk, chunkSize);
					break;
				}
				begin = next + 1;
				next = searchpath.find_first_of(";", begin);
			} while (begin < (int)searchpath.length());

			ifs.close();

			if (chunk)
			{
				int r = luaL_loadbuffer(L, (char*)chunk, chunkSize, chunkName.c_str());
				if (r)
				{
					const char* err = lua_tostring(L, -1);
					DF_ERR << err << DF_END;
				}
				free(chunk);
			}
			else
			{
				DF_EXC << "can not require" << chunkName.c_str() << "file." << DF_END;
				return 0;
			}

			return 1;
		}

		// -----------------------------------------------------------------------
		int DFExport lua_release_dump_data(lua_State* L)
		{
			return 1;
		}
	}
	// -----------------------------------------------------------------------
	LuaSystem* LuaSystem::m_pInstance = NULL;
	static lua_State* L = NULL;
	// -----------------------------------------------------------------------
	LuaSystem::~LuaSystem(void)
	{
		Manager<int, LuaFunction>::instancePtr()->clear();
		Manager<unsigned int, LuaFunction>::instancePtr()->clear();
		if (m_pScript)
		{
			lua_settop(L, 0);
			lua_gc(L, LUA_GCCOLLECT, 0);
			lua_close(L);
		}
	}
	// -----------------------------------------------------------------------
	LuaSystem::LuaSystem(void) :
		m_sDebugFile(""),
		m_sRootPath(""),
		m_sPrint(""),
		m_pScript(NULL),
		m_iTop(0),
		m_pos_err(0),
		m_isRunScriptMsg(false)
	{

#if DF_TARGET_PLATFORM == DF_PLATFORM_WINDOWS
		char szFilePath[MAX_PATH];
		GetModuleFileNameA(NULL, szFilePath, MAX_PATH);
		char *p = strrchr(szFilePath, '\\');
		*p = 0x00;
		m_sRootPath = szFilePath;
		m_sRootPath += '/';
#else
		char buf[256];
		getcwd(buf, sizeof(buf));
		m_sRootPath = buf;
		m_sRootPath += '/';
		DF_INFO <<"RootPath: " << m_sRootPath << DF_END;
#endif

#if DF_TARGET_PLATFORM == DF_PLATFORM_WINDOWS
		mkdir((m_sRootPath + "log").c_str());
#else
		mkdir((m_sRootPath + "log").c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
#endif


		
		
		L = lua_open();
		luaL_openlibs(L);
		tolua_DFLuaServerLib_open(L);
		luaopen_cjson(L);
		setDebug(true);
		addLoaderFunction();
		m_pScript = (void*)L;
		doString("package.path = \"\"");
		doString("collectgarbage(\"setpause\", 100)");
		doString("collectgarbage(\"setstepmul\", 5000)");
		
	}
	// -----------------------------------------------------------------------
	void LuaSystem::initServer(BaseServer* pServer)
	{
		if (!pServer)
		{
			DF_EXC <<"<LuaSystem::initServer> pServer is NULL." << DF_END;
			return;
		}
		pServer->setPackMessage(new LuaPackMessage);
		pServer->setUnpackMessage(new LuaUnpackMessage);
		m_pBaseServer = pServer;
	}

	// -----------------------------------------------------------------------
	void LuaSystem::setDebug(bool bDebug)
	{
		if (bDebug)
		{
			const luaL_reg global_functions[] = {
				{ "print", lua_print },
				{ "warning", lua_warning },
				{ "printInfo", lua_printInfo },
				{ NULL, NULL }
			};

			luaL_register(L, "_G", global_functions);
			lua_pushcfunction(L, pcall_callback_err_fun);
			m_pos_err = lua_gettop(L);
			return;
		}

		const luaL_reg global_functions[] = {
			{ "print", lua_release_print },
			{ "warning", lua_warning },
			{ "printInfo", lua_printInfo },
			{ NULL, NULL }
		};

		luaL_register(L, "_G", global_functions);
		lua_settop(L, m_pos_err);
		lua_pushcfunction(L, NULL);
		m_pos_err = 0;
	}

	// -----------------------------------------------------------------------
	void LuaSystem::addLoaderFunction(void)
	{
		// stack content after the invoking of the function
		// get loader table
		lua_getglobal(L, "package");                                  /* L: package */
		lua_getfield(L, -1, "loaders");                               /* L: package, loaders */

		// insert loader into index 2
		lua_pushcfunction(L, luaScriptLoader);                                   /* L: package, loaders, func */
		for (int i = (int)(lua_objlen(L, -2) + 1); i > 2; --i)
		{
			lua_rawgeti(L, -2, i - 1);                                /* L: package, loaders, func, function */
			// we call lua_rawgeti, so the loader table now is at -3
			lua_rawseti(L, -3, i);                                    /* L: package, loaders, func */
		}
		lua_rawseti(L, -2, 2);                                        /* L: package, loaders */

		// set loaders into package
		lua_setfield(L, -2, "loaders");                               /* L: package */

		lua_pop(L, 1);

	}
	// -----------------------------------------------------------------------
	void LuaSystem::addSearchPath(const char* path)
	{
		lua_getglobal(L, "package");                                  /* stack: package */
		lua_getfield(L, -1, "path");                /* get package.path, stack: package path */
		const char* cur_path = lua_tostring(L, -1);
		lua_pop(L, 1);                                                /* stack: package */
		lua_pushfstring(L, "%s;%s/?.lua", cur_path, path);            /* stack: package newpath */
		lua_setfield(L, -2, "path");          /* package.path = newpath, stack: package */
		lua_pop(L, 1);                                                /* stack: - */
	}

	// -----------------------------------------------------------------------
	void LuaSystem::loadBuffer(const char* pBuffer, unsigned int uSize, const std::string& sName)
	{
		if (luaL_loadbuffer(L, pBuffer, uSize, sName.c_str()))
		{
			const char* szLog = lua_tostring(L, -1);
			DF_ERR << "<LuaSystem::loadBuffer>" << "[" << szLog << "] file LUA" << sName.c_str() << "error" << DF_END;
			return;
		}
		else if (lua_pcall(L, 0, 0, m_pos_err))
		{
			const char* szLog = lua_tostring(L, -1);
			DF_ERR << "<LuaSystem::loadBuffer>" << "[" << szLog << "] file LUA" << sName.c_str() << "error" << DF_END;
			return;
		}
	}
	// -----------------------------------------------------------------------
	void LuaSystem::doString(const std::string& str)
	{
		doString(str.c_str());
	}
	// -----------------------------------------------------------------------
	void LuaSystem::doString(const char* pStr)
	{
		if (luaL_dostring(L, pStr))
		{
			const char* szLog = lua_tostring(L, -1);
			DF_ERR << "<LuaSystem::doString>" << "[" << szLog << "]" << DF_END;
			if (LuaSystem::instancePtr()->getIsRunScriptMsg())
				LuaSystem::instancePtr()->addRunScirptPrint(szLog);
		}
	}
	// -----------------------------------------------------------------------
	void LuaSystem::doFile(const std::string& sFileName)
	{
		std::string sCommand("require \"");
		sCommand.append(sFileName);
		sCommand.append("\"");
		doString(sCommand);
	}
	// -----------------------------------------------------------------------
	void LuaSystem::reload(const std::string& sModuleFileName)
	{
		if (sModuleFileName == "")
			return;
		const char* pModuleFileName = sModuleFileName.c_str();
		lua_getglobal(L, "package");                         /* L: package */
		lua_getfield(L, -1, "loaded");                       /* L: package loaded */
		lua_pushstring(L, pModuleFileName);
		lua_gettable(L, -2);                                 /* L:package loaded module */
		if (!lua_isnil(L, -1))
		{
			lua_pushstring(L, pModuleFileName);               /* L:package loaded module name */
			lua_pushnil(L);                                  /* L:package loaded module name nil*/
			lua_settable(L, -4);                             /* L:package loaded module */
		}
		lua_pop(L, 3);
		std::string require = "require \'" + sModuleFileName + "\'";
		return doString(require);
	}

	// -----------------------------------------------------------------------
	void LuaSystem::commit(void)
	{
		m_iTop = lua_gettop(L);
	}
	// -----------------------------------------------------------------------
	void LuaSystem::reduction(void)
	{
		lua_settop(L, m_iTop);
	}
	// -----------------------------------------------------------------------
	LuaFunction* LuaSystem::getGlobalFunction(const std::string& sName)
	{
		lua_getglobal(L, sName.c_str());
		if (!lua_isfunction(L, -1))
		{
			DF_EXC << "<LuaSystem::getGlobalFunction>  can not call [" << sName << "] function" << DF_END;
			return NULL;
		}
		return LuaFunction::screate(sName.c_str());
	}

	// -----------------------------------------------------------------------
	LuaStack LuaSystem::getLuaStack(const std::string& sName)
	{
		lua_getglobal(L, sName.c_str());
		return LuaStack();
	}
	// -----------------------------------------------------------------------
	void LuaSystem::setGlobalName(const char* key)
	{
		//DF_SAFE_RETURN(L);
		lua_setglobal(L, key);
	}
	// -----------------------------------------------------------------------
	void LuaSystem::getGlobalName(const char* key)
	{
		//DF_SAFE_RETURN(L);
		lua_getglobal(L, key);
	}
	// -----------------------------------------------------------------------
	LuaSystem* LuaSystem::instancePtr(void)
	{
		if (NULL == m_pInstance)
			m_pInstance = new LuaSystem;
		return m_pInstance;
	}
	// -----------------------------------------------------------------------
	void LuaSystem::uninstance(void)
	{
		DF_SAFE_DELETE(m_pInstance);
	}
	// -----------------------------------------------------------------------
	void LuaSystem::enableReturn(const char* file)
	{
		if (file)
			m_sDebugFile = file;
	}
	// -----------------------------------------------------------------------
	void LuaSystem::disableReturn(void)
	{
		m_sDebugFile = "";
		lua_sethook(L, NULL, 0, 0);
	}
	// -----------------------------------------------------------------------
	std::string LuaSystem::getDebugFile(void)const
	{
		return m_sDebugFile;
	}
	// -----------------------------------------------------------------------
	void* LuaSystem::getScript(void)
	{
		return m_pScript;
	}
	// -----------------------------------------------------------------------
	int LuaSystem::getPosErr(void)const
	{
		return m_pos_err;
	}
	// -----------------------------------------------------------------------
	int LuaSystem::getTop(void)const
	{
		return lua_gettop(L);
	}
	// -----------------------------------------------------------------------
	void LuaSystem::removeValueFromRoot(const char* sRootTag, int iRootTag)
	{
		lua_getglobal(L, "class_name_table_list");
		if (lua_istable(L, -1))
		{
			lua_pushstring(L, sRootTag);
			lua_gettable(L, -2);
			if (lua_istable(L, -1))
			{
				lua_pushnumber(L, iRootTag);
				lua_pushnil(L);
				lua_settable(L, -3);
				lua_pop(L, 1);
			}
			lua_pop(L, 1);
		}
	}
	// -----------------------------------------------------------------------
	const char* LuaSystem::getRootPath(void)const
	{
		return m_sRootPath.c_str();
	}
	// -----------------------------------------------------------------------
	void LuaSystem::setIsRunScriptMsg(bool isRunScriptMsg)
	{
		m_isRunScriptMsg = isRunScriptMsg;
		if (m_isRunScriptMsg)
			m_sPrint = "";
	}
	// -----------------------------------------------------------------------
	bool LuaSystem::getIsRunScriptMsg(void)
	{
		return m_isRunScriptMsg;
	}
	// -----------------------------------------------------------------------
	const char* LuaSystem::getRunScirptPrint(void)const
	{
		return m_sPrint.c_str();
	}
	// -----------------------------------------------------------------------
	void LuaSystem::addRunScirptPrint(const std::string& sPrint)
	{
		m_sPrint = m_sPrint + sPrint + "\n";
	}
	// -----------------------------------------------------------------------
	void LuaSystem::loadFiles(const std::string& path)
	{
		lua_State* L = static_cast<lua_State*>(m_pScript);
		lua_newtable(L);
		std::string strfind = m_sRootPath + path + "*";
#if DF_TARGET_PLATFORM == DF_PLATFORM_WINDOWS
		_finddata_t fileInfo;
		
		intptr_t handle = _findfirst(strfind.c_str(), &fileInfo);
		if (handle == -1L)
		{
			strfind = m_sRootPath + "../../../" + path + "*";
			handle = _findfirst(strfind.c_str(), &fileInfo);
			if (handle == -1L)
			{
				DF_EXC << "<LuaSystem::loadFiles>  can not found path by[" << path << "]." << DF_END;
				return;
			}	
		}
		do
		{
			if (!(fileInfo.attrib & _A_SUBDIR))
			{
				lua_pushstring(L, fileInfo.name);
				lua_setfield(L, -2, path.c_str());
			}
		} while (_findnext(handle, &fileInfo) == 0);
		_findclose(handle);
#else

		struct dirent* ent = NULL;
		DIR *pDir = NULL;
		pDir = opendir(strFolderPath.c_str());
		if (NULL == pDir)
		{
			strFolderPath = m_sRootPath + "../../../" + path;
			pDir = opendir(strFolderPath.c_str());
			if (NULL == pDir)
			{
				DF_EXC <<"<LuaSystem::loadFiles>  can not found path by["<<path<<"]."<<DF_END;
				return;
			}
		}
		while (NULL != (ent = readdir(pDir)))
		{
			if (8 == ent->d_type)
			{
				lua_pushstring(L, ent->d_name);
				lua_setfield(L, -2, path.c_str());
			}
		}
		closedir(pDir);
#endif
	}
	// -----------------------------------------------------------------------
	void LuaSystem::loadAllFiles(const std::string& strFolderPath, const std::string& curPath)
	{
		int iKey = 1;
		lua_State* L = static_cast<lua_State*>(m_pScript);
		lua_newtable(L);
#if DF_TARGET_PLATFORM == DF_PLATFORM_WINDOWS
		_finddata_t fileInfo;
		std::string strfind = m_sRootPath + strFolderPath + "*";
		intptr_t handle = _findfirst(strfind.c_str(), &fileInfo);
		if (handle == -1L)
		{
			strfind = m_sRootPath + "../../../" + strFolderPath + "*";
			handle = _findfirst(strfind.c_str(), &fileInfo);
			if (handle == -1L)
			{
				DF_EXC << "<LuaSystem::loadAllFiles>  can not found path by[" << strFolderPath << "]." << DF_END;
				return;
			}
		}

		do
		{
			if (fileInfo.attrib & _A_SUBDIR)
			{
				if ((strcmp(fileInfo.name, ".") != 0) && (strcmp(fileInfo.name, "..") != 0))
				{
					std::string newPath = strFolderPath + fileInfo.name + "/";
					std::string newCurPath = curPath + fileInfo.name + "/";
					loadAllFiles(newPath, newCurPath);
				}
			}
			else
			{
				lua_pushstring(L, fileInfo.name);
				lua_rawseti(L, -2, iKey);
				iKey++;
			}

		} while (_findnext(handle, &fileInfo) == 0);
		_findclose(handle);
		if (curPath != "")
			lua_setfield(L, -2, curPath.c_str());

#else
		struct dirent* ent = NULL;
		std::string strfind = m_sRootPath + strFolderPath
		DIR *pDir = NULL;
		pDir = opendir(strfind.c_str());
		if (NULL == pDir)
		{
			strfind = m_sRootPath + "../../../" + strFolderPath;
			pDir = opendir(strfind.c_str());
			if (NULL == pDir)
			{
				DF_EXC << "<LuaSystem::loadAllFiles>  can not found path by[" << strFolderPath << "]." << DF_END;
				return;
			}
		}
		while (NULL != (ent = readdir(pDir)))
		{
			if (8 == ent->d_type)
			{
				lua_pushstring(L, ent->d_name);
				lua_setfield(L, -2, curPath.c_str());
			}
			else
			{
				if ((strcmp(ent->d_name, ".") != 0) && (strcmp(ent->d_name, "..") != 0))
				{
					std::string newPath = strFolderPath + ent->d_name + "/";
					std::string newCurPath = curPath + ent->d_name + "/";
					getFileList(newPath, newCurPath);
				}
			}
		}
		closedir(pDir);
#endif
	}
	// -----------------------------------------------------------------------
	BaseServer* LuaSystem::getServer(void)const
	{
		return m_pBaseServer;
	}
}