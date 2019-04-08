/************************************************************************
* @File			:	DFLuaFunction.h
* @Author		:	Sword
* @DateTime		:	2015.3.9
* @Description	:
*
*
*
*
************************************************************************/
#ifndef __DFLuaFunction_H__
#define __DFLuaFunction_H__

#include "DFPrerequisite.h"
#include "DFLuaStack.h"

namespace DF{
	// -----------------------------------------------------------------------
	// @brief lua 函数
	class DFExport LuaFunction : public LuaStack
	{
	public:
		// -----------------------------------------------------------------------
		// @brief 析构函数
		~LuaFunction(void);
		// -----------------------------------------------------------------------
		// @brief 构造函数
		LuaFunction(void);
		// -----------------------------------------------------------------------
		// @brief 构造函数
		// @param[ref] 绑定一个脚本函数
		LuaFunction(int ref);
		// -----------------------------------------------------------------------
		// @brief 构造函数
		// @param[uId] 唯一ID
		LuaFunction(unsigned int uId);
		// -----------------------------------------------------------------------
		// @brief 创建一个函数
		static LuaFunction* screate(void);
		// -----------------------------------------------------------------------
		// @brief 创建一个函数
		// @param[ref] 绑定一个脚本函数
		static LuaFunction* screate(int ref);
		// -----------------------------------------------------------------------
		// @brief 创建一个函数添加到管理器并绑定一个脚本函数
		// @param[sName] 管理器需要一个名字
		static LuaFunction* screate(const char* sName);
		// -----------------------------------------------------------------------
		// @brief 管理器移除
		static bool sremove(int ref);
		// -----------------------------------------------------------------------
		// @brief 管理器移除
		static bool sremove(LuaFunction* pFunc);
		// -----------------------------------------------------------------------
		// @brief 管理器移除
		static bool sremove(const char* sName);
		// -----------------------------------------------------------------------
		// @brief 获取lua function id
		int getRef(void)const;
		// -----------------------------------------------------------------------
		// @brief 初始化
		void init(void);
		// -----------------------------------------------------------------------
		// @brief 执行脚本函数
		// @param[argsCnt] 多少个参数
		// @param[resultCnt] 多少个返回值
		void callFunction(int argsCnt, int resultCnt);

	protected:
		unsigned int	m_uId;
		int				m_pos_err;
		int				m_ref;
	};
}

#endif
