/************************************************************************
* @File			:	DFLuaStack.h
* @Author		:	Sword
* @DateTime		:	2015.3.9
* @Description	:
*
*
*
*
************************************************************************/
#ifndef __DFLuaStack_H__
#define __DFLuaStack_H__

#include "DFPrerequisite.h"

namespace DF{
	// -----------------------------------------------------------------------
	// @brief lua栈
	class DFExport LuaStack
	{
	public:
		// -----------------------------------------------------------------------
		// @brief 析构函数
		~LuaStack(void);
		// -----------------------------------------------------------------------
		// @brief 构造函数
		LuaStack(void);
		// -----------------------------------------------------------------------
		// @brief 保存top值
		void commit(void);
		// -----------------------------------------------------------------------
		// @brief 还原top值
		void reduction(void);
		// -----------------------------------------------------------------------
		// @brief 是否为bool类型数据
		// @param[top] 栈的位置
		bool isBoolean(int top = -1)const;
		// -----------------------------------------------------------------------
		// @brief 是否为double类型数据
		// @param[top] 栈的位置
		bool isNumber(int top = -1)const;
		// -----------------------------------------------------------------------
		// @brief 是否为string类型数据
		// @param[top] 栈的位置
		bool isString(int top = -1)const;
		// -----------------------------------------------------------------------
		// @brief 是否为object类型数据
		// @param[top] 栈的位置
		bool isObject(int top = -1)const;
		// -----------------------------------------------------------------------
		// @brief 是否为function类型数据
		// @param[top] 栈的位置
		bool isFunction(int top = -1)const;
		// -----------------------------------------------------------------------
		// @brief 是否为table类型数据
		// @param[top] 栈的位置
		bool isTable(int top = -1)const;
		// -----------------------------------------------------------------------
		// @brief 添加一个bool类型数据
		void pushBoolean(bool val);
		// -----------------------------------------------------------------------
		// @brief 添加一个int类型数据
		void pushInteger(int val);
		// -----------------------------------------------------------------------
		// @brief 添加一个double类型数据
		void pushNumber(double val);
		// -----------------------------------------------------------------------
		// @brief 添加一个string类型数据
		void pushString(const std::string& val);
		// -----------------------------------------------------------------------
		// @brief 添加一个实体类型数据
		// @param[pObj] 实体对象 
		// @param[type] 实体类别
		void pushObject(void* pObj, const std::string& type);
		// -----------------------------------------------------------------------
		// @brief 添加一个消息类型数据
		// @param[pMsg] 一个消息 
		void pushMessage(MessageBase* pMsg);
		// -----------------------------------------------------------------------
		// @brief 读取一个bool数据类型
		// @param[top] 栈的位置
		bool toBoolean(int top = -1)const;
		// -----------------------------------------------------------------------
		// @brief 读取一个int数据类型
		// @param[top] 栈的位置
		int toInteger(int top = -1)const;
		// -----------------------------------------------------------------------
		// @brief 读取一个double数据类型
		// @param[top] 栈的位置
		double toNumber(int top = -1)const;
		// -----------------------------------------------------------------------
		// @brief 读取一个string数据类型
		// @param[top] 栈的位置
		const char* toString(int top = -1)const;
		// -----------------------------------------------------------------------
		// @brief 读取一个Object数据类型
		// @param[top] 栈的位置
		void* toObject(int top = -1)const;
		// -----------------------------------------------------------------------
		// @brief 读取一个自定义数据类型
		// @param[pType] 类别
		// @param[top] 栈的位置
		void* toUserType(const char* pType, int top = -1)const;
		// -----------------------------------------------------------------------
		// @brief 储存一个全局数据
		void saveToGlobal(const std::string& sName);

	protected:
		void*			m_pScript;
		int				m_iSaveTop;
	};
}

#endif
