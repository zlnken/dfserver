/************************************************************************
* @File			:	DFDefine.h
* @Author		:	Sword
* @Description	:
*
*
*
*
************************************************************************/
#ifndef __DFUnPackMessage_H__
#define __DFUnPackMessage_H__
#include "DFPrerequisite.h"

namespace DF{
	// -----------------------------------------------------------------------
	// @brief 解包消息
	class DFExport UnpackMessage
	{
	public:
		// -----------------------------------------------------------------------
		// @brief 析构函数
		virtual ~UnpackMessage(void);
		// -----------------------------------------------------------------------
		// @brief 构造函数
		UnpackMessage(void);
		// -----------------------------------------------------------------------
		// @brief 构造函数
		// @param[pMsg] 消息
		UnpackMessage(MessageBase* pMsg);
		// -----------------------------------------------------------------------
		// @brief 构造函数
		// @param[pHead] 数据头
		// @param[uSize] 数据大小
		UnpackMessage(void* pHead, unsigned int uSize);
		// -----------------------------------------------------------------------
		// @brief 重置
		// @param[pMsg] 消息
		void reset(MessageBase* pMsg);
		// -----------------------------------------------------------------------
		// @brief 重置
		// @param[pUnpackFence] 数据头
		// @param[nSurplusSize] 数据大小
		void reset(char* pUnpackFence, unsigned int nSurplusSize);
		// -----------------------------------------------------------------------
		// @brief 解压一个消息类型
		// @param[uSize] 类型大小
		bool unpackMsg(unsigned int uSize = 4);
		// -----------------------------------------------------------------------
		// @brief 解压一个char
		char unpackInt8(void);
		// -----------------------------------------------------------------------
		// @brief 解压一个short
		short unpackInt16(void);
		// -----------------------------------------------------------------------
		// @brief 解压一个int
		int unpackInt32(void);
		// -----------------------------------------------------------------------
		// @brief 解压一个unsigned char
		unsigned char unpackUint8(void);
		// -----------------------------------------------------------------------
		// @brief 解压一个unsigned short
		unsigned short unpackUint16(void);
		// -----------------------------------------------------------------------
		// @brief 解压一个unsigned int
		unsigned int unpackUint32(void);
		// -----------------------------------------------------------------------
		// @brief 解压一个float
		float unpackFloat(void);
		// -----------------------------------------------------------------------
		// @brief 解压一个double
		double unpackDouble(void);
		// -----------------------------------------------------------------------
		// @brief 解压一个值
		double unpackValue(void);
		// -----------------------------------------------------------------------
		// @brief 解压成二级制数据
		// @param[uSize] 大小
		void* unpackStream(unsigned short uSize);
		// -----------------------------------------------------------------------
		// @brief 解压字符串
		const char* unpackString(void);
		// -----------------------------------------------------------------------
		// @brief 解压一个复合数据对应脚本lua
		virtual void unpackObject(void){}
		// -----------------------------------------------------------------------
		// @brief 获取当前解压数据
		char* getUnpackFence(void);
		// -----------------------------------------------------------------------
		// @brief 获取还剩多少没解压
		unsigned int getSurplusSize(void) { return m_nSurplusSize; }
		// -----------------------------------------------------------------------
		// @brief 获取解压是否成功
		bool getIsOk(void){ return m_bIsOK; }
		

	protected:
		char*				m_pUnpackFence;
		unsigned int		m_nSurplusSize;
		bool				m_bIsOK;
	};


}




#endif