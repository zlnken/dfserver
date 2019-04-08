/************************************************************************
* @File			:	DFPackMessage.h
* @Author		:	Sword
* @Description	:
*
*
*
*
************************************************************************/
#ifndef __DFPackMessage_H__
#define __DFPackMessage_H__
#include "DFPrerequisite.h"


namespace DF{
	// -----------------------------------------------------------------------
	// @brief 打包消息
	class DFExport PackMessage
	{
	public:
		typedef std::queue< char* >	BufQueue;

	public:
		virtual ~PackMessage(void);
		PackMessage(void);
		
		// -----------------------------------------------------------------------
		// @brief 打包一个类型
		// @param[uType] 类型
		void packType(unsigned short uType);
		// -----------------------------------------------------------------------
		// @brief 打包一个类型
		// @param[pMsg] 打包一个消息 
		void packMsg(MessageBase* pMsg);
		// -----------------------------------------------------------------------
		// @brief 打包一个二级制数据
		// @param[pHead] 数据头 
		// @param[uSize] 数据大小
		void packBytes(void* pHead, unsigned short uSize);
		// -----------------------------------------------------------------------
		// @brief 打包一个char
		void packInt8(char i8);
		// -----------------------------------------------------------------------
		// @brief 打包一个short
		void packInt16(short i16);
		// -----------------------------------------------------------------------
		// @brief 打包一个int
		void packInt32(int i32);
		// -----------------------------------------------------------------------
		// @brief 打包一个整形数据
		void packInt(int d);
		// -----------------------------------------------------------------------
		// @brief 打包一个unsigned char
		void packUint8(unsigned char ui8);
		// -----------------------------------------------------------------------
		// @brief 打包一个unsigned short
		void packUint16(unsigned short ui16);
		// -----------------------------------------------------------------------
		// @brief 打包一个unsigned int
		void packUint32(unsigned int ui32);
		// -----------------------------------------------------------------------
		// @brief 打包一个float
		void packFloat(float f);
		// -----------------------------------------------------------------------
		// @brief 打包一个double
		void packDouble(double d);
		// -----------------------------------------------------------------------
		// @brief 打包一个double
		void packValue(double d);
		// -----------------------------------------------------------------------
		// @brief 打包一个字典
		void packDict(unsigned short uSize);
		// -----------------------------------------------------------------------
		// @brief 打包一个字符串
		void packString(const char* v);
		// -----------------------------------------------------------------------
		// @brief 打包一个复合数据
		virtual void packObject(void){}
		// -----------------------------------------------------------------------
		// @brief 获取打包是否成功
		bool getIsOK(void)const{ return m_bIsOK; }
		// -----------------------------------------------------------------------
		// @brief 获取打包数据大小
		unsigned int getTotalBodySize(void)const{ return m_uTotalBodySize; }
		// -----------------------------------------------------------------------
		// @brief 获取剩余大小
		unsigned int getCurrentEmptySize(void)const{ return m_uCurEmptySize; }
		// -----------------------------------------------------------------------
		// @brief 获取消息
		MessageBase* getMsg(void)const;
		// -----------------------------------------------------------------------
		// @brief 获取队列
		BufQueue& getBufQueue(void){ return m_BufQueue; }
		
	protected:
		// -----------------------------------------------------------------------
		// @brief 默认打包字节
		void packByteByNormal(void* pHead, unsigned short uSize);
		
	protected:
		BufQueue					m_BufQueue;
		char*						m_pCurBufHead;
		char*						m_pCurPackFence;
		unsigned short				m_uCurMaxSize;
		unsigned short				m_uCurEmptySize;
		unsigned short				m_uStackDeep;
		unsigned int				m_uTotalBodySize;
		bool						m_bIsOK;
	};


}


#endif
