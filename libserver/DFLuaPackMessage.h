/************************************************************************
* @File			:	DFLuaPackMessage.h
* @Author		:	Sword
* @Description	:
*
*
*
*
************************************************************************/
#ifndef __DFLuaPackMessage_H__
#define __DFLuaPackMessage_H__

#include "DFPrerequisite.h"
#include "DFPackMessage.h"

namespace DF{
	// -----------------------------------------------------------------------
	// @brief Lua打包消息
	class DFExport LuaPackMessage : public PackMessage
	{
	public:
		~LuaPackMessage(void);
		LuaPackMessage(void);
		// -----------------------------------------------------------------------
		// @brief 打包一个复合数据
		virtual void packObject(void);

	protected:
		// -----------------------------------------------------------------------
		// @brief 递归
		void dumpTable(unsigned int uSize);
		// -----------------------------------------------------------------------
		// @brief 获取table里面有多少个
		unsigned int getTableSize(int top);

	protected:
		void*			m_pScript;
	};
}



#endif
