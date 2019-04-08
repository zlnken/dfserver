#include "DFGlobalIDAlloc.h"
#include "DFDateTime.h"
#include "DFB2.h"
#include "DFB4.h"
#include "DFB8.h"
namespace DF{
	// -----------------------------------------------------------------------
	GlobalIDAlloc* GlobalIDAlloc::m_pInstance = NULL;

	GlobalIDAlloc::~GlobalIDAlloc(void)
	{
		
	}
	// -----------------------------------------------------------------------
	GlobalIDAlloc::GlobalIDAlloc(void):
	m_iSecAllocID(0),
	m_iLastTime(0),
	m_uWorld(0)
	{
		
	}

	// -----------------------------------------------------------------------
	GlobalIDAlloc* GlobalIDAlloc::instancePtr(void)
	{
		if (!m_pInstance)
			m_pInstance = new GlobalIDAlloc;
		return m_pInstance;
	}
	// -----------------------------------------------------------------------
	GlobalIDAlloc& GlobalIDAlloc::instance(void)
	{
		if (!m_pInstance)
			m_pInstance = new GlobalIDAlloc;
		return *m_pInstance;
	}
	// -----------------------------------------------------------------------
	void GlobalIDAlloc::uninstance(void)
	{
		DF_SAFE_DELETE(m_pInstance);
	}
	// -----------------------------------------------------------------------
	double GlobalIDAlloc::allocID(void)
	{
		DateTime* pDT = DateTime::instancePtr();
		pDT->refresh();
		unsigned int iCurTime = pDT->getUnixTime();
		if (m_iLastTime != iCurTime)
		{
			m_iSecAllocID = 0;
			m_iLastTime = iCurTime;
		}
			
		++m_iSecAllocID;
		B8 b8(0);
		b8.m_ui32[0] = iCurTime;
		b8.m_ui8[4] = m_iSecAllocID & 0xFF;
		b8.m_ui8[5] = m_uWorld & 0xFF;
		
		
		return static_cast<double>(b8.m_i64);
	}
	
	// -----------------------------------------------------------------------
	void GlobalIDAlloc::setWorld(unsigned short uWorld)
	{
		m_uWorld = uWorld;
	}
}