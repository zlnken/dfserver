/************************************************************************
* @File			:	DFNetSendBuffer.h
* @Author		:	Sword
* @Description	:
*
*
*
*
************************************************************************/
#ifndef __DFNetSendBuffer_H__
#define __DFNetSendBuffer_H__

#include "DFPrerequisite.h"


namespace DF{
	// -----------------------------------------------------------------------
	// @brief 网络发送缓冲区
	class DFExport NetSendBuffer
	{
	public:
		typedef std::queue<NetBuffer*>	BufQueue;

	public:
		// -----------------------------------------------------------------------
		// @brief 析构函数
		~NetSendBuffer(void);
		// -----------------------------------------------------------------------
		// @brief 构造函数
		// @param[uBlockSize] 缓冲区大小
		// @param[uBlockNum] 缓冲区数量
		NetSendBuffer(unsigned short uBlockSize, unsigned short uBlockNum);
		// -----------------------------------------------------------------------
		// @brief 将一段数据写入发送消息缓存区
		// @param[pHead] 数据
		// @param[uSize] 数据大小
		bool writeBytes(const void* pHead, unsigned short uSize);
		// -----------------------------------------------------------------------
		// @brief 上次hold的数据发送完毕，归还这段数据的控制权限
		// @param[pHead] 数据
		// @param[uSize] 数据大小
		bool holdBlock(void** pHead, unsigned short& uSize);			
		// -----------------------------------------------------------------------
		// @brief 释放buf
		void releaseBlock(void);
		// -----------------------------------------------------------------------
		// @brief Buf是否是空的
		bool isEmpty(void)const;										

	protected:
		NetBuffer*				m_pReadBuf;
		NetBuffer*				m_pWriteBuf;
		BufQueue				m_BufQueue;
		bool					m_bIsHoldBlock;
		unsigned short			m_uBlockNum;

	};
}

#endif