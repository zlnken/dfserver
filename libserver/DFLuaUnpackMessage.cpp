#include "DFLuaUnpackMessage.h"
#include "DFLuaSystem.h"
#include "DFIO.h"
#include "DFDateTime.h"
extern "C" {
#include <lua.hpp>
#include <tolua++.h>
}

namespace DF{

	// -----------------------------------------------------------------------
	LuaUnpackMessage::~LuaUnpackMessage(void)
	{
	}
	// -----------------------------------------------------------------------
	LuaUnpackMessage::LuaUnpackMessage(void):
	UnpackMessage()
	{
		m_pScript = (lua_State*)LuaSystem::instancePtr()->getScript();
	}
	// -----------------------------------------------------------------------
	LuaUnpackMessage::LuaUnpackMessage(MessageBase* pMsg):
	UnpackMessage(pMsg)
	{
		m_pScript = (lua_State*)LuaSystem::instancePtr()->getScript();

	}
	// -----------------------------------------------------------------------
	LuaUnpackMessage::LuaUnpackMessage(void* pHead, unsigned int uSize):
	UnpackMessage(pHead, uSize)
	{
		m_pScript = (lua_State*)LuaSystem::instancePtr()->getScript();
	}
	// -----------------------------------------------------------------------
	void LuaUnpackMessage::unpackObject(void)
	{
		lua_State* L = static_cast<lua_State*>(m_pScript);
		char t = unpackInt8();
		if (Config::SIGNED_INT8_FLAG == t)
		{
			lua_pushinteger(L, unpackInt8());
		}
		else if (Config::SIGNED_INT16_FLAG == t)
		{
			lua_pushinteger(L, unpackInt16());
		}
		else if (Config::SIGNED_INT32_FLAG == t)
		{
			lua_pushinteger(L, unpackInt32());
		}
		else if (Config::FLOAT_FLAG == t)
		{
			lua_pushnumber(L, unpackFloat());
		}
		else if (Config::DOUBLE_FLAG == t)
		{
			double d = unpackDouble();
			lua_pushnumber(L, d);
		}
		else if (Config::SMALL_STRING_FLAG == t)
		{
			unsigned char uSize = unpackUint8();
			void* data = unpackStream(static_cast<unsigned short>(uSize));
			lua_pushstring(L, reinterpret_cast<const char*>(data));
		}
		else if (Config::BIG_STRING_FLAG == t)
		{
			unsigned short uSize = unpackUint16();
			void* data = unpackStream(uSize);
			lua_pushstring(L, reinterpret_cast<const char*>(data));
		}
		else if (Config::FALSE_FLAG == t)
		{
			lua_pushboolean(L, 0);
		}
		else if (Config::TRUE_FLAG == t)
		{
			lua_pushboolean(L, 1);
		}
		else if (Config::NONE_FLAG == t)
		{
			lua_pushnil(L);
		}
		else if (Config::SMALL_DICT_FLAG == t)
		{
			unsigned char uSize = unpackUint8();
			dumpTable(uSize);
		}
		else if (Config::BIG_DICT_FLAG == t)
		{
			unsigned short uSize = unpackUint16();
			dumpTable(uSize);
		}
		else
		{
			DF_EXC << "can not support lua type" << DF_END;
			m_bIsOK = false;
			lua_pop(L, 1);
			lua_pushnil(L);
		}
	}
	// -----------------------------------------------------------------------
	void LuaUnpackMessage::dumpTable(unsigned int uSize)
	{	
		char keyType = 0;
		const char* skey = NULL;
		int64 iKey = 0;
		lua_State* L = static_cast<lua_State*>(m_pScript);
		lua_newtable(L);
		int top = lua_gettop(L);
		for (unsigned int i = 0; i < uSize; ++i)
		{
			keyType = unpackInt8();
			if (Config::SMALL_STRING_FLAG == keyType)
			{
				unsigned char uSize = unpackUint8();
				skey = reinterpret_cast<const char*>(unpackStream(uSize));
			}
			else if (Config::BIG_STRING_FLAG == keyType)
			{
				unsigned short uSize = unpackUint16();
				skey = reinterpret_cast<const char*>(unpackStream(uSize));
			}
			if (Config::SIGNED_INT8_FLAG == keyType)
			{
				iKey = unpackInt8();
			}
			else if (Config::SIGNED_INT16_FLAG == keyType)
			{
				iKey = unpackInt16();
			}
			else if (Config::SIGNED_INT32_FLAG == keyType)
			{
				iKey = unpackInt32();
			}
			if (skey)
			{
				unpackObject();
				lua_setfield(L, -2, skey);
			}
			else
			{
				unpackObject();
				lua_rawseti(L, -2, iKey);
			}
		}
	}

}