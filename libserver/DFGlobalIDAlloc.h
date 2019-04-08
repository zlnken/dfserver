/************************************************************************
* @File			:	DFGlobalIDAlloc.h
* @Author		:	Sword
* @Description	:
*
*
*
*
************************************************************************/
#ifndef __DFGlobalIDAlloc_H__
#define __DFGlobalIDAlloc_H__
#include "DFPrerequisite.h"


namespace DF{
	//------------------------------------------------------------------------
	// @brief id分配
	class DFExport GlobalIDAlloc
	{
	public:
		// -----------------------------------------------------------------------
		// @brief 析构函数
		~GlobalIDAlloc(void);
		// -----------------------------------------------------------------------
		// @brief 设置世界ID
		void setWorld(unsigned short uWorld);
		// -----------------------------------------------------------------------
		// @brief 分配一个ID
		double allocID(void);
		// -----------------------------------------------------------------------
		// @brief 获取单例指针
		static GlobalIDAlloc* instancePtr(void);
		// -----------------------------------------------------------------------
		// @brief 获取单例
		static GlobalIDAlloc& instance(void);
		// -----------------------------------------------------------------------
		// @brief 移除单例
		static void uninstance(void);


	protected:
		// -----------------------------------------------------------------------
		// @brief 构造函数
		GlobalIDAlloc(void);
	protected:
		static GlobalIDAlloc*			m_pInstance;
		unsigned int					m_iSecAllocID;
		unsigned int					m_iLastTime;
		unsigned short					m_uWorld;
	};	
}
#endif
