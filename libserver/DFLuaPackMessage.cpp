#include "DFLuaPackMessage.h"
#include "DFLuaSystem.h"
#include "DFIO.h"
#include "DFDateTime.h"
extern "C" {
#include <lua.hpp>
#include <tolua++.h>
}

namespace DF{

	// -----------------------------------------------------------------------
	LuaPackMessage::LuaPackMessage(void)
	{
		m_pScript = (lua_State*)LuaSystem::instancePtr()->getScript();
	}
	// -----------------------------------------------------------------------
	LuaPackMessage::~LuaPackMessage(void)
	{
	}
	// -----------------------------------------------------------------------
	void LuaPackMessage::packObject(void)
	{
		lua_State* L = static_cast<lua_State*>(m_pScript);
		int saveTop = lua_gettop(L);
		if (lua_isnumber(L, -1))
		{
			double value = lua_tonumber(L, -1);
			packValue(value);
		}
		else if (lua_isstring(L, -1))
		{
			const char* value = lua_tostring(L, -1);
			packString(value);
		}
		else if (lua_isnil(L, -1))
		{
			packInt8(Config::NONE_FLAG);
		}
		else if (lua_isboolean(L, -1))
		{
			int value = lua_toboolean(L, -1);
			packInt8(value > 0 ? Config::TRUE_FLAG : Config::FALSE_FLAG);
		}
		else if (lua_istable(L, -1))
		{
			int top = lua_gettop(L);
			unsigned int uSize = getTableSize(top);
			packDict(uSize);

			lua_settop(L, top);
			dumpTable(uSize);
		}
		else
		{
			DF_EXC << "can not support lua type" << DF_END;
			m_bIsOK = false;
		}
		lua_settop(L, saveTop);
	}
	// -----------------------------------------------------------------------
	unsigned int LuaPackMessage::getTableSize(int top)
	{
		lua_State* L = static_cast<lua_State*>(m_pScript);
		unsigned int uSize = 0;
		lua_pushnil(L);
		while (lua_next(L, top) != 0)
		{
			uSize++;
			lua_pop(L, 1);
		}

		return uSize;
	}
	// -----------------------------------------------------------------------
	void LuaPackMessage::dumpTable(unsigned int uSize)
	{
		lua_State* L = static_cast<lua_State*>(m_pScript);	
		int top = lua_gettop(L);
		lua_pushnil(L);
		while (lua_next(L, top) != 0)
		{	
			int keyType = lua_type(L, -2);
			if (keyType == LUA_TNUMBER)
			{
				double value = static_cast<int>(lua_tonumber(L, -2));
				packValue(value);
			}
			else if (keyType == LUA_TSTRING)
			{
				const char* value = lua_tostring(L, -2);
				packString(value);
			}
			
			int valueType = lua_type(L, -1);
			if (LUA_TNUMBER == valueType)
			{
				double value = static_cast<double>(lua_tonumber(L, -1));
				packValue(value);
			}
			else if (LUA_TSTRING == valueType)
			{
				const char* value = lua_tostring(L, -1);
				packString(value);
			}
			else if (LUA_TBOOLEAN == valueType)
			{
				int value = lua_toboolean(L, -1);
				packInt8(value > 0 ? Config::TRUE_FLAG : Config::FALSE_FLAG);
			}
			else if (LUA_TNIL == valueType)
			{
				packInt8(Config::NONE_FLAG);
			}
			else if (LUA_TTABLE == valueType)
			{
				int top = lua_gettop(L);
				unsigned int uSize = getTableSize(top);
				packDict(uSize);
				lua_settop(L, top);
				dumpTable(uSize);
			}
			lua_pop(L, 1);
		}
	}
}