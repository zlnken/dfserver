#include "DFLuaTrigger.h"
#include "DFLuaFunction.h"
#include "DFLuaSystem.h"
#include "DFManager.h"
#include "DFMessageBase.h"
namespace DF{

	// -----------------------------------------------------------------------
	LuaTrigger::~LuaTrigger(void)
	{
		LuaFunction* pFunc = m_pFuncArray[LTE_Dtor];
		if (!pFunc)
		{
			return;
		}
		pFunc->commit();
		pFunc->init();
		pFunc->pushObject(this, "DF::LuaTrigger");
		pFunc->callFunction(1, 0);
		pFunc->reduction();

		if (m_sRootTag && m_iRootTag > 0)
		{
			LuaSystem::instancePtr()->commit();
			LuaSystem::instancePtr()->removeValueFromRoot(m_sRootTag, m_iRootTag);
			LuaSystem::instancePtr()->reduction();
		}
	}
	// -----------------------------------------------------------------------
	LuaTrigger::LuaTrigger(void):
	m_sRootTag(NULL),
	m_iRootTag(0),
	m_uId(0)
	{
		memset(m_pFuncArray, 0, sizeof(LuaFunction*)* LTE_MaxCount);
	}
	// -----------------------------------------------------------------------
	void LuaTrigger::clear(void)
	{
		LuaFunction* pFunc = m_pFuncArray[LTE_Clear];
		if (!pFunc)
			return;
		pFunc->commit();
		pFunc->init();
		pFunc->pushObject(this, "DF::LuaTrigger");
		pFunc->callFunction(1, 0);
		pFunc->reduction();
	}
	// -----------------------------------------------------------------------
	void LuaTrigger::triggering(void)
	{
		LuaFunction* pFunc = m_pFuncArray[LTE_TriNone];
		if (!pFunc)
			return;
		pFunc->commit();
		pFunc->init();
		pFunc->pushObject(this, "DF::LuaTrigger");
		pFunc->callFunction(1, 0);
		pFunc->reduction();
	}
	// -----------------------------------------------------------------------
	void LuaTrigger::triggering(MessageBase* pMsg)
	{
		LuaFunction* pFunc = m_pFuncArray[LTE_TriMsg];
		if (!pFunc)
			return;
		pFunc->commit();
		pFunc->init();
		pFunc->pushObject(this, "DF::LuaTrigger");
		pFunc->pushObject(pMsg, "DF::MessageBase");
		pFunc->callFunction(2, 0);
		pFunc->reduction();
	}
	// -----------------------------------------------------------------------
	unsigned int LuaTrigger::getID(void)const
	{
		return m_uId;
	}
	// -----------------------------------------------------------------------
	const char* LuaTrigger::getType(void)
	{
		return m_sRootTag;
	}
	// -----------------------------------------------------------------------
	LuaTrigger* LuaTrigger::screate(void)
	{
		static unsigned int id = 0;
		++id;
		LuaTrigger* pTri = new LuaTrigger;
		pTri->m_uId = id;
		Manager<unsigned int, Trigger>* pMgr = Manager<unsigned int, Trigger>::instancePtr();
		pMgr->push(pTri->m_uId, pTri);
		return pTri;
	}
	// -----------------------------------------------------------------------
	void LuaTrigger::pushFunction(LuaTriggerEnum funcEnum, LuaFunction* pfunc)
	{
		if (m_pFuncArray[funcEnum])
			return;
		m_pFuncArray[funcEnum] = pfunc;
	}
	// -----------------------------------------------------------------------
	void LuaTrigger::addToRootCallBack(const char* sTag, int iTag)
	{
		if (m_sRootTag || m_sRootTag > 0)
			return;
		m_sRootTag = sTag;
		m_iRootTag = iTag;
	}
}