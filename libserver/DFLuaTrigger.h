/************************************************************************
* @File			:	DFLuaTrigger.h
* @Author		:	Sword
* @DateTime		:	2015.8.23
* @Version		:	v0.02
* @Description	:
*
*
*
*
************************************************************************/
#ifndef __DFDFLuaTrigger_H__
#define __DFDFLuaTrigger_H__

#include "DFPrerequisite.h"
#include "DFTrigger.h"


namespace DF{
	// -----------------------------------------------------------------------
	// @brief 触发器用来绑定lua函数主要lua继承C++类重载c++函数
	class DFExport LuaTrigger : public Trigger
	{
	public:
		enum LuaTriggerEnum
		{
			// @brief 虚构函数
			LTE_Dtor = 0,
			// @brief 触发消息
			LTE_TriMsg = 1,
			// @brief 触发一个空参数
			LTE_TriNone = 2,
			// @brief 触发一个清空函数
			LTE_Clear = 3,
			// @brief 最大数量
			LTE_MaxCount
		};

	public:
		// -----------------------------------------------------------------------
		// @brief 虚构函数
		virtual ~LuaTrigger(void);
		// -----------------------------------------------------------------------
		// @brief 构造函数
		LuaTrigger(void);
		// -----------------------------------------------------------------------
		// @brief 清空
		void clear(void);
		// -----------------------------------------------------------------------
		// @brief 触发一个空参数
		void triggering(void);
		// -----------------------------------------------------------------------
		// @brief 触发一条消息
		void triggering(MessageBase* pMsg);
		// -----------------------------------------------------------------------
		// @brief 获取ID
		unsigned int getID(void)const;
		// -----------------------------------------------------------------------
		// @brief 获取类型
		const char* getType(void);
		// -----------------------------------------------------------------------
		// @brief 绑定脚本函数
		// @param[funcEnum] 类型
		// @param[pfunc] 函数
		void pushFunction(LuaTriggerEnum funcEnum, LuaFunction* pfunc);
		// -----------------------------------------------------------------------
		// @brief 管理器回收
		// @param[sTag] 字符串标志
		// @param[iTag] 整形标志
		void addToRootCallBack(const char* sTag, int iTag);
		// -----------------------------------------------------------------------
		// @brief 创建一个触发器
		static LuaTrigger* screate(void);

	protected:
		unsigned int		m_uId;
		const char*			m_sRootTag;
		int					m_iRootTag;
		LuaFunction*		m_pFuncArray[LTE_MaxCount];
	};
}
#endif