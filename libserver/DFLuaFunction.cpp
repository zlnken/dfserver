#include "DFLuaFunction.h"
#include "DFLuaSystem.h"
#include "DFManager.h"
#include "DFCrc32.h"

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <tolua++.h>
}

namespace DF{

	// -----------------------------------------------------------------------
	LuaFunction::~LuaFunction(void)
	{
		lua_State* L = static_cast<lua_State*>(m_pScript);
		if (m_ref != 0)
			luaL_unref(L, LUA_REGISTRYINDEX, m_ref);	
	}
	// -----------------------------------------------------------------------
	LuaFunction::LuaFunction(void) :
	m_pos_err(0),
	m_ref(0),
	m_uId(0)
	{
		m_pos_err = LuaSystem::instancePtr()->getPosErr();
		m_pScript = LuaSystem::instancePtr()->getScript();
		lua_State* L = static_cast<lua_State*>(m_pScript);

		if (lua_isfunction(L, -1))
		{
			m_ref = lua_ref(L, LUA_REGISTRYINDEX);
		}
    }
	// -----------------------------------------------------------------------
	LuaFunction::LuaFunction(int ref) :
	m_pos_err(0),
	m_ref(ref),
	m_uId(0)
	{
		m_pos_err = LuaSystem::instancePtr()->getPosErr();
		m_pScript = LuaSystem::instancePtr()->getScript();
	}

	// -----------------------------------------------------------------------
	LuaFunction::LuaFunction(unsigned int uId) :
	m_pos_err(0),
	m_ref(0),
	m_uId(uId)
	{
		m_pos_err = LuaSystem::instancePtr()->getPosErr();
		m_pScript = LuaSystem::instancePtr()->getScript();

		lua_State* L = static_cast<lua_State*>(m_pScript);
		if (lua_isfunction(L, -1))
		{
			m_ref = lua_ref(L, LUA_REGISTRYINDEX);
		}
	}
	// -----------------------------------------------------------------------
	void LuaFunction::init(void)
	{
		lua_State* L = static_cast<lua_State*>(m_pScript);
		lua_rawgeti(L, LUA_REGISTRYINDEX, m_ref);
	}
	// -----------------------------------------------------------------------
	void LuaFunction::callFunction(int argsCnt, int resultCnt)
	{
		lua_State* L = static_cast<lua_State*>(m_pScript);
		lua_pcall(L, argsCnt, resultCnt, m_pos_err);
	}
	// -----------------------------------------------------------------------
	int LuaFunction::getRef(void)const
	{
		return m_ref;
	}
	// -----------------------------------------------------------------------
	LuaFunction* LuaFunction::screate(void)
	{
		LuaFunction* pfunc = new LuaFunction;
		Manager<int, LuaFunction>* pMgr = Manager<int, LuaFunction>::instancePtr();
		pMgr->push(pfunc->getRef(), pfunc);
		return pfunc;
	}
	// -----------------------------------------------------------------------
	LuaFunction* LuaFunction::screate(int ref)
	{
		LuaFunction* pfunc = new LuaFunction(ref);
		Manager<int, LuaFunction>* pMgr = Manager<int, LuaFunction>::instancePtr();
		pMgr->push(ref, pfunc);
		return pfunc;
	}
	// -----------------------------------------------------------------------
	LuaFunction* LuaFunction::screate(const char* sName)
	{
        unsigned int uId = Crc32::instancePtr()->crcChars(sName);
		Manager<unsigned int, LuaFunction>* pMgr = Manager<unsigned int, LuaFunction>::instancePtr();
		LuaFunction* pfunc = pMgr->find(uId);
		if (pfunc)
			return pfunc;

		pfunc = new LuaFunction(uId);
		pMgr->push(uId, pfunc);
		return pfunc;
	}
	// -----------------------------------------------------------------------
	bool LuaFunction::sremove(int ref)
	{
		Manager<int, LuaFunction>* pMgr = Manager<int, LuaFunction>::instancePtr();
		return pMgr->remove(ref);
	}
	// -----------------------------------------------------------------------
	bool LuaFunction::sremove(LuaFunction* pFunc)
	{
		Manager<int, LuaFunction>* pMgr = Manager<int, LuaFunction>::instancePtr();
		return pMgr->remove(pFunc->getRef());
	}

	// -----------------------------------------------------------------------
	bool LuaFunction::sremove(const char* sName)
	{
		unsigned int uId = Crc32::instancePtr()->crcChars(sName);
		Manager<unsigned int, LuaFunction>* pMgr = Manager<unsigned int, LuaFunction>::instancePtr();
		return pMgr->remove(uId);
	}

}