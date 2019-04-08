#include "DFLuaStack.h"
#include "DFLuaSystem.h"
#include "DFManager.h"
#include "DFIO.h"
#include "DFDateTime.h"

extern "C" {
#include <lua.hpp>
#include <tolua++.h>
}

namespace DF{

	// -----------------------------------------------------------------------
	LuaStack::~LuaStack(void)
	{
	}

	LuaStack::LuaStack(void):
	m_iSaveTop(0)
	{
		m_pScript = (lua_State*)LuaSystem::instancePtr()->getScript();
	}

	// -----------------------------------------------------------------------
	bool LuaStack::isBoolean(int top)const
	{
		lua_State* L = static_cast<lua_State*>(m_pScript);
		if (!lua_isboolean(L, top))
		{
			DF_OUT << "<LuaStack::isBoolean> is not Boolean" << DF_END;
			return false;
		}
		return true;
	}
	// -----------------------------------------------------------------------
	bool LuaStack::isNumber(int top)const
	{
		lua_State* L = static_cast<lua_State*>(m_pScript);
		if (!lua_isnumber(L, top))
		{
			DF_OUT << "<LuaStack::isNumber> is not Number" << DF_END;
			return false;
		}
		return true;
	}
	// -----------------------------------------------------------------------
	bool LuaStack::isString(int top)const
	{
		lua_State* L = static_cast<lua_State*>(m_pScript);
		if (!lua_isstring(L, top))
		{
			DF_OUT << "<LuaStack::isString> is not String" << DF_END;
			return false;
		}
		return true;
	}
	// -----------------------------------------------------------------------
	bool LuaStack::isObject(int top)const
	{
		lua_State* L = static_cast<lua_State*>(m_pScript);
		if (!tolua_isnoobj(L, top, NULL))
		{
			DF_OUT << "<LuaStack::isString> is not Object" << DF_END;
			return false;
		}
		return true;
	}
	// -----------------------------------------------------------------------
	bool LuaStack::isFunction(int top)const
	{
		lua_State* L = static_cast<lua_State*>(m_pScript);
		if (!lua_isfunction(L, top))
		{
			DF_OUT << "<LuaStack::isFunction> is not Function" << DF_END;
			return false;
		}
		return true;
	}
	// -----------------------------------------------------------------------
	bool LuaStack::isTable(int top)const
	{
		lua_State* L = static_cast<lua_State*>(m_pScript);
		if (!lua_istable(L, top))
		{
			DF_OUT << "<LuaStack::isTable> is not Table" << DF_END;
			return false;
		}
		return true;
	}
	// -----------------------------------------------------------------------
	void LuaStack::commit(void)
	{
		lua_State* L = static_cast<lua_State*>(m_pScript);
		m_iSaveTop = lua_gettop(L);
	}
	// -----------------------------------------------------------------------
	void LuaStack::reduction(void)
	{
		lua_State* L = static_cast<lua_State*>(m_pScript);
		lua_settop(L, m_iSaveTop);
	}
	// -----------------------------------------------------------------------
	void LuaStack::pushBoolean(bool val)
	{
		lua_State* L = static_cast<lua_State*>(m_pScript);
		lua_pushboolean(L, (int)val);
	}
	// -----------------------------------------------------------------------
	void LuaStack::pushInteger(int val)
	{
		lua_State* L = static_cast<lua_State*>(m_pScript);
		lua_pushinteger(L, (lua_Integer)val);
	}
	// -----------------------------------------------------------------------
	void LuaStack::pushNumber(double val)
	{
		lua_State* L = static_cast<lua_State*>(m_pScript);
		lua_pushnumber(L, (lua_Number)val);
	}
	// -----------------------------------------------------------------------
	void LuaStack::pushString(const std::string& val)
	{
		lua_State* L = static_cast<lua_State*>(m_pScript);
		lua_pushstring(L, val.c_str());
	}
	// -----------------------------------------------------------------------
	void LuaStack::pushObject(void* pObj, const std::string& type)
	{
		lua_State* L = static_cast<lua_State*>(m_pScript);
		tolua_pushusertype(L, pObj, type.c_str());
	}


	// -----------------------------------------------------------------------
	bool LuaStack::toBoolean(int top)const
	{
		lua_State* L = static_cast<lua_State*>(m_pScript);
		if (!isBoolean(top))
			return 0;
		return (bool)lua_toboolean(L, top);
	}
	// -----------------------------------------------------------------------
	int LuaStack::toInteger(int top)const
	{
		lua_State* L = static_cast<lua_State*>(m_pScript);
		if (!isNumber(top))
			return 0.0;
		return (int)lua_tointeger(L, top);
	}
	// -----------------------------------------------------------------------
	double LuaStack::toNumber(int top)const
	{
		lua_State* L = static_cast<lua_State*>(m_pScript);
		if (!isNumber(top))
			return 0.0;
		return (double)lua_tonumber(L, top);
	}
	// -----------------------------------------------------------------------
	const char* LuaStack::toString(int top)const
	{
		lua_State* L = static_cast<lua_State*>(m_pScript);
		if (!isString(top))
			return "";
		return lua_tostring(L, top);
	}
	// -----------------------------------------------------------------------
	void* LuaStack::toObject(int top)const
	{
		lua_State* L = static_cast<lua_State*>(m_pScript);
		if (!isObject(top))
			return NULL;
		return tolua_tousertype(L, top, NULL);
	}
	// -----------------------------------------------------------------------
	void* LuaStack::toUserType(const char* pType, int top)const
	{
		lua_State* L = static_cast<lua_State*>(m_pScript);
		if (!tolua_isusertype(L, top, pType, 0, NULL))
			return NULL;
		return tolua_tousertype(L, top, NULL);

		
	}

	// -----------------------------------------------------------------------
	void LuaStack::saveToGlobal(const std::string& sName)
	{
		lua_State* L = static_cast<lua_State*>(m_pScript);
		lua_setglobal(L, sName.c_str());
		lua_pop(L, -1);
	}

}