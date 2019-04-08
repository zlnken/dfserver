#include "DFLuaTable.h"
#include "DFLuaSystem.h"
#include "DFLuaFunction.h"


extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <tolua++.h>
}
namespace DF{
	// -----------------------------------------------------------------------
	LuaTable::LuaTable(int iTop):
	m_iTableTop(iTop)
	{
		
	}
	// -----------------------------------------------------------------------
	LuaTable::LuaTable(void):
	m_iTableTop(0)
	{
		lua_State* L = static_cast<lua_State*>(m_pScript);
		lua_newtable(L);
		m_iTableTop = lua_gettop(L);
	}
	// -----------------------------------------------------------------------
	void LuaTable::setValue(int index, bool val)
	{
		lua_State* L = static_cast<lua_State*>(m_pScript);
		lua_settop(L, m_iTableTop);
		lua_pushinteger(L, index);
		lua_pushboolean(L, (bool)val);
		lua_settable(L, -3);
	}
	// -----------------------------------------------------------------------
	void LuaTable::setValue(int index, int val)	
	{
		lua_State* L = static_cast<lua_State*>(m_pScript);
		lua_settop(L, m_iTableTop);
		lua_pushinteger(L, index);
		lua_pushinteger(L, (lua_Integer)val);
		lua_settable(L, -3);
	}
	// -----------------------------------------------------------------------
	void LuaTable::setValue(int index, float val)
	{
		lua_State* L = static_cast<lua_State*>(m_pScript);
		lua_settop(L, m_iTableTop);
		lua_pushinteger(L, index);
		lua_pushnumber(L, (lua_Number)val);
		lua_settable(L, -3);
	}
	// -----------------------------------------------------------------------
	void LuaTable::setValue(int index, const std::string& val)
	{
		lua_State* L = static_cast<lua_State*>(m_pScript);
		lua_settop(L, m_iTableTop);
		lua_pushinteger(L, index);
		lua_pushstring(L, val.c_str());
		lua_settable(L, -3);
	}
	// -----------------------------------------------------------------------
	void LuaTable::setValue(int index, void* pObj, std::string& type)
	{
		lua_State* L = static_cast<lua_State*>(m_pScript);
		lua_settop(L, m_iTableTop);
		lua_pushinteger(L, index);
		tolua_pushusertype(L, pObj, type.c_str());
		lua_settable(L, -3);
	}
	// -----------------------------------------------------------------------
	void LuaTable::setValue(const std::string& key, bool val)
	{
		lua_State* L = static_cast<lua_State*>(m_pScript);
		lua_settop(L, m_iTableTop);
		lua_pushstring(L, key.c_str());
		tolua_pushboolean(L, (bool)val);
		lua_settable(L, -3);
	}
	// -----------------------------------------------------------------------
	void LuaTable::setValue(const std::string& key, int val)
	{
		lua_State* L = static_cast<lua_State*>(m_pScript);
		lua_settop(L, m_iTableTop);
		lua_pushstring(L, key.c_str());
		lua_pushinteger(L, val);
		lua_settable(L, -3);
	}
	// -----------------------------------------------------------------------
	void LuaTable::setValue(const std::string& key, unsigned int val)
	{
		lua_State* L = static_cast<lua_State*>(m_pScript);
		lua_settop(L, m_iTableTop);
		lua_pushstring(L, key.c_str());
		lua_pushinteger(L, (lua_Integer)val);
		lua_settable(L, -3);
	}

	// -----------------------------------------------------------------------
	void LuaTable::setValue(const std::string& key, float val)
	{
		lua_State* L = static_cast<lua_State*>(m_pScript);
		lua_settop(L, m_iTableTop);
		lua_pushstring(L, key.c_str());
		lua_pushnumber(L, (lua_Number)val);
		lua_settable(L, -3);
	}
	// -----------------------------------------------------------------------
	void LuaTable::setValue(const std::string& key, const std::string& val)
	{
		lua_State* L = static_cast<lua_State*>(m_pScript);
		lua_settop(L, m_iTableTop);
		lua_pushstring(L, key.c_str());
		lua_pushstring(L, val.c_str());
		lua_settable(L, -3);
	}
	// -----------------------------------------------------------------------
	void LuaTable::setValue(const std::string& key, void* pObj, const std::string& type)
	{
		lua_State* L = static_cast<lua_State*>(m_pScript);
		lua_settop(L, m_iTableTop);
		lua_pushstring(L, key.c_str());
		tolua_pushusertype(L, pObj, type.c_str());
		lua_settable(L, -3);
	}

	// -----------------------------------------------------------------------
	bool LuaTable::getBoolean(int idx)const
	{
		lua_State* L = static_cast<lua_State*>(m_pScript);
		lua_settop(L, m_iTableTop);
		lua_pushnumber(L, idx);
		lua_gettable(L, -2);
		return toBoolean();
	}
	// -----------------------------------------------------------------------
	int LuaTable::getInt(int idx)const
	{
		lua_State* L = static_cast<lua_State*>(m_pScript);
		lua_settop(L, m_iTableTop);
		lua_pushnumber(L, idx);
		lua_gettable(L, -2);
		return toInteger();
	}
	// -----------------------------------------------------------------------
	unsigned int LuaTable::getUint(int idx)const
	{
		lua_State* L = static_cast<lua_State*>(m_pScript);
		lua_settop(L, m_iTableTop);
		lua_pushnumber(L, idx);
		lua_gettable(L, -2);
		return (unsigned int)(toInteger());
	}
	// -----------------------------------------------------------------------
	float LuaTable::getFloat(int idx)const
	{
		lua_State* L = static_cast<lua_State*>(m_pScript);
		lua_settop(L, m_iTableTop);
		lua_pushnumber(L, idx);
		lua_gettable(L, -2);
		return (float)(toNumber());
	}
	// -----------------------------------------------------------------------
	std::string LuaTable::getString(int idx)const
	{
		lua_State* L = static_cast<lua_State*>(m_pScript);
		lua_settop(L, m_iTableTop);
		lua_pushnumber(L, idx);
		lua_gettable(L, -2);
		return toString();
	}
	// -----------------------------------------------------------------------
	LuaFunction* LuaTable::getFunction(int idx)const
	{
		lua_State* L = static_cast<lua_State*>(m_pScript);
		lua_settop(L, m_iTableTop);
		lua_pushnumber(L, idx);
		lua_gettable(L, -2);
		if (!isFunction())
			return NULL;
		return LuaFunction::screate();
	}
	// -----------------------------------------------------------------------
	LuaTable* LuaTable::getLuaTable(int idx)const
	{
		lua_State* L = static_cast<lua_State*>(m_pScript);
		lua_settop(L, m_iTableTop);
		lua_pushnumber(L, idx);
		lua_gettable(L, -2);
		if (!isTable())
			return NULL;
		return new LuaTable(lua_gettop(L));
	}
	// -----------------------------------------------------------------------
	void* LuaTable::getObject(int idx)const
	{
		lua_State* L = static_cast<lua_State*>(m_pScript);
		lua_settop(L, m_iTableTop);
		lua_pushnumber(L, idx);
		lua_gettable(L, -2);
		return toObject();
	}
	// -----------------------------------------------------------------------
	bool LuaTable::getBoolean(const std::string& key)const
	{
		lua_State* L = static_cast<lua_State*>(m_pScript);
		lua_settop(L, m_iTableTop);
		lua_pushstring(L, key.c_str());
		lua_gettable(L, -2);
		return toBoolean();
	}
	// -----------------------------------------------------------------------
	int LuaTable::getInt(const std::string& key)const
	{
		lua_State* L = static_cast<lua_State*>(m_pScript);
		lua_settop(L, m_iTableTop);
		lua_pushstring(L, key.c_str());
		lua_gettable(L, -2);
		return toInteger();
	}
	// -----------------------------------------------------------------------
	unsigned int LuaTable::getUint(const std::string& key)const
	{
		lua_State* L = static_cast<lua_State*>(m_pScript);
		lua_settop(L, m_iTableTop);
		lua_pushstring(L, key.c_str());
		lua_gettable(L, -2);
		return (unsigned int)(toInteger());
	}
	// -----------------------------------------------------------------------
	float LuaTable::getFloat(const std::string& key)const
	{
		lua_State* L = static_cast<lua_State*>(m_pScript);
		lua_settop(L, m_iTableTop);
		lua_pushstring(L, key.c_str());
		lua_gettable(L, -2);
		return (float)(toNumber());
	}
	// -----------------------------------------------------------------------
	std::string LuaTable::getString(const std::string& key)const
	{
		lua_State* L = static_cast<lua_State*>(m_pScript);
		lua_settop(L, m_iTableTop);
		lua_pushstring(L, key.c_str());
		lua_gettable(L, -2);
		return toString();
	}
	// -----------------------------------------------------------------------
	LuaFunction* LuaTable::getFunction(const std::string& key)const
	{
		lua_State* L = static_cast<lua_State*>(m_pScript);
		lua_settop(L, m_iTableTop);
		lua_pushstring(L, key.c_str());
		lua_gettable(L, -2);
		if (!isFunction())
			return NULL;
		return LuaFunction::screate();
	}
	// -----------------------------------------------------------------------
	LuaTable* LuaTable::getLuaTable(const std::string& key)const
	{
		lua_State* L = static_cast<lua_State*>(m_pScript);
		lua_settop(L, m_iTableTop);
		lua_pushstring(L, key.c_str());
		lua_gettable(L, -2);
		if (!isTable())
			return NULL;
		return new LuaTable(lua_gettop(L));
	}
	// -----------------------------------------------------------------------
	void* LuaTable::getObject(const std::string& key)const
	{
		lua_State* L = static_cast<lua_State*>(m_pScript);
		lua_settop(L, m_iTableTop);
		lua_pushstring(L, key.c_str());
		lua_gettable(L, -2);
		return toObject();
	}
	// -----------------------------------------------------------------------
	void LuaTable::begin(void)
	{
		lua_State* L = static_cast<lua_State*>(m_pScript);
		lua_settop(L, m_iTableTop);
		lua_pushnil(L);
	}
	// -----------------------------------------------------------------------
	bool LuaTable::hasNext(void)const
	{
		lua_State* L = static_cast<lua_State*>(m_pScript);
		return (lua_next(L, m_iTableTop) != 0);
	}
	// -----------------------------------------------------------------------
	void LuaTable::next(void)
	{
		lua_State* L = static_cast<lua_State*>(m_pScript);
		lua_pop(L, 1);
	}
	// -----------------------------------------------------------------------
	int LuaTable::getNextIntKey(void)const
	{
		return (int)(toNumber(-2));
	}
	// -----------------------------------------------------------------------
	std::string LuaTable::getNextStringKey(void)const
	{
		return (toString(-2));
	}
	// -----------------------------------------------------------------------
	bool LuaTable::getNextBoolean(void)const
	{
		return toBoolean();
	}
	// -----------------------------------------------------------------------
	int LuaTable::getNextInt(void)const
	{
		return toInteger();
	}
	// -----------------------------------------------------------------------
	unsigned int LuaTable::getNextUint(void)const
	{
		return (unsigned int)toInteger();
	}
	// -----------------------------------------------------------------------
	float LuaTable::getNextFloat(void)const
	{
		return toNumber();
	}
	// -----------------------------------------------------------------------
	std::string LuaTable::getNextString(void)const
	{
		return toString();
	}
	// -----------------------------------------------------------------------
	LuaFunction* LuaTable::getNextFunction(void)const
	{
		if (!isFunction())
			return NULL;
		//lua_State* L = static_cast<lua_State*>(m_pScript);
		return LuaFunction::screate();
	}
	// -----------------------------------------------------------------------
	LuaTable* LuaTable::getNextLuaTable(void)const
	{
		if (!isFunction())
			return NULL;
		lua_State* L = static_cast<lua_State*>(m_pScript);
		return new LuaTable(lua_gettop(L));
	}
	// -----------------------------------------------------------------------
	void* LuaTable::getNextObject(void)const
	{
		return toObject();
	}
	// -----------------------------------------------------------------------
	bool LuaTable::remove(int key)
	{
		lua_State* L = static_cast<lua_State*>(m_pScript);
		lua_settop(L, m_iTableTop);
		lua_pushnumber(L, key);
		lua_pushnil(L);
		lua_settable(L, -3);
		return true;
	}
	// -----------------------------------------------------------------------
	bool LuaTable::remove(const std::string& key)
	{
		lua_State* L = static_cast<lua_State*>(m_pScript);
		lua_settop(L, m_iTableTop);
		lua_pushstring(L, key.c_str());
		lua_pushnil(L);
		lua_settable(L, -3);
		return true;
	}
	// -----------------------------------------------------------------------
	int LuaTable::getTop(void)const
	{
		return m_iTableTop;
	}
	// -----------------------------------------------------------------------
	int LuaTable::getSize(void)const
	{
		return 0;
	}
	//// -----------------------------------------------------------------------
	//void LuaTable::dumpString(std::string& dumps, const std::string& d)
	//{
	//	const std::string delims = d;
	//	dumps += ("\n" + delims + "{\n");
	//	lua_State* L = static_cast<lua_State*>(m_pScript);
	//	int top = lua_gettop(L);
	//	lua_pushnil(L);
	//	while (lua_next(L, top) != 0)
	//	{
	//		int keyType = lua_type(L, -2);
	//		if (keyType == LUA_TNUMBER)
	//		{
	//			double value = lua_tonumber(L, -2);
	//			dumps += (std::string("\t") + delims + "[" + StringConverter::toString((int)(value)) + "] = ");
	//		}
	//		else if (keyType == LUA_TSTRING)
	//		{
	//			const char*  value = lua_tostring(L, -2);
	//			dumps += (std::string("\t") + delims + "[" + std::string(value) + "] = ");
	//		}
	//		else if (keyType == LUA_TUSERDATA)
	//		{
	//			void* p = tolua_tousertype(L, -1, NULL);
	//			dumps += (std::string("\t") + delims + "[0x" + StringConverter::toString(p) + "] = ");
	//		}
	//		else if (keyType == LUA_TLIGHTUSERDATA)
	//		{
	//			const void* p = lua_topointer(L, -1);
	//			dumps += (std::string("\t") + delims + "[0x" + StringConverter::toString(p) + "] = ");
	//		}
	//		else
	//		{
	//			dumps += "}\n";
	//			return;
	//		}

	//		int valueType = lua_type(L, -1);
	//		if (LUA_TNIL == valueType)
	//		{
	//			dumps += "nil, \n";
	//		}
	//		else if (LUA_TBOOLEAN == valueType)
	//		{
	//			int value = lua_toboolean(L, -1);
	//			dumps += (StringConverter::toString(bool(value)) + "\n");
	//		}
	//		else if (LUA_TNUMBER == valueType)
	//		{
	//			float value = (float)lua_tonumber(L, -1);
	//			dumps += (StringConverter::toString(value) + "\n");
	//		}
	//		else if (LUA_TSTRING == valueType)
	//		{
	//			std::string value = lua_tostring(L, -1);
	//			dumps += (value + "\n");
	//		}
	//		else if (LUA_TFUNCTION == valueType)
	//		{
	//			const void* p = lua_topointer(L, -1);
	//			dumps += (std::string("function:0x") + StringConverter::toString(p) + "\n");
	//		}
	//		else if (LUA_TUSERDATA == valueType)
	//		{
	//			void* p = tolua_tousertype(L, -1, NULL);
	//			dumps += (std::string("function:0x") + StringConverter::toString(p) + "\n");
	//		}
	//		else if (LUA_TLIGHTUSERDATA == valueType)
	//		{
	//			const void* p = lua_topointer(L, -1);
	//			dumps += (std::string("function:0x") + StringConverter::toString(p) + "\n");
	//		}
	//		else if (LUA_TTABLE == valueType)
	//		{
	//			dumpString(dumps, delims + "\t");
	//		}
	//		lua_pop(L, 1);
	//	}
	//	dumps += (delims + "}\n");
	//}
	// -----------------------------------------------------------------------
	void LuaTable::setTableTop(int top)
	{
		m_iTableTop = top;
	}
}