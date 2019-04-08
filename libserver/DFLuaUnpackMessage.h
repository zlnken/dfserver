/************************************************************************
* @File			:	DFLuaUnpackMessage.h
* @Author		:	Sword
* @Description	:
*
*
*
*
************************************************************************/
#ifndef __DFLuaUnpackMessage_H__
#define __DFLuaUnpackMessage_H__

#include "DFPrerequisite.h"
#include "DFUnpackMessage.h"

namespace DF{
	// -----------------------------------------------------------------------
	// @brief Lua解包消息
	class DFExport LuaUnpackMessage : public UnpackMessage
	{
	public:
		// -----------------------------------------------------------------------
		// @brief 析构函数
		~LuaUnpackMessage(void);
		// -----------------------------------------------------------------------
		// @brief 构造函数
		LuaUnpackMessage(void);
		// -----------------------------------------------------------------------
		// @brief 构造函数
		// @param[pMsg] 消息
		LuaUnpackMessage(MessageBase* pMsg);
		// -----------------------------------------------------------------------
		// @brief 构造函数
		// @param[pHead] 数据头
		// @param[uSize] 数据大小
		LuaUnpackMessage(void* pHead, unsigned int uSize);
		// -----------------------------------------------------------------------
		// @brief 解压一个复合数据对应脚本lua
		void unpackObject(void);

	protected:
		// -----------------------------------------------------------------------
		// @brief 递归解压
		void dumpTable(unsigned int uSize);


	protected:
		void*			m_pScript;
	};
}



#endif
