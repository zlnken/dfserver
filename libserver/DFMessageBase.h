/************************************************************************
* @File			:	DFMsgBase.h
* @Author		:	Sword
* @DateTime		:	2013.12.9
* @Description	:
*
*
*
*
************************************************************************/
#ifndef __DFMsgBase_H__
#define __DFMsgBase_H__
#include "DFPrerequisite.h"

namespace DF{

	class DFExport MessageBase
	{
	public:
		MessageBase(void) : m_uSize(sizeof(MessageBase)), m_uType(0) {}
		MessageBase(unsigned short uType) : m_uSize(sizeof(MessageBase)), m_uType(uType) {}
		MessageBase(unsigned short uSize, unsigned short uType) : m_uSize(uSize), m_uType(uType) {}
		unsigned short getSize(void) const { return m_uSize; }											//消息长度
		void setSize(unsigned short uSize) { m_uSize = uSize; }										//设置消息长度
		void addSize(unsigned short uSize) { m_uSize += uSize; }									//增加消息长度
		unsigned short getType(void) const { return m_uType; }										//消息类型
		void setType(unsigned short uType) { m_uType = uType; }										//设置消息类型
		void* getBody(void) { return (char*)this + sizeof(MessageBase); }								//消息体
		unsigned short getBodySize(void)const { return m_uSize - sizeof(MessageBase); }					//消息体长度

		/*
		将消息长度修正为MSG_BASE_SIZE的倍数
		以方便在存储的时候使得每条消息字节对齐
		*/
		void align(void)
		{
			unsigned short uDiff = this->m_uSize % Config::MSG_BASE_SIZE;
			if (uDiff)
			{
				this->m_uSize = this->m_uSize - uDiff + Config::MSG_BASE_SIZE;
			}
		}

	protected:
		unsigned short m_uSize;
		unsigned short m_uType;
	
	};

	// 确保MsgBase的长度是4的倍数
	DF_STATIC_ASSERT(sizeof(MessageBase) % 4 == 0, "class MsgBase not 4 byte");
}

#endif
