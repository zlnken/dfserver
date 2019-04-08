/************************************************************************
* @File			:	DFNetRecvBuffer.h
* @Author		:	Sword
* @Description	:
*
*
*
*
************************************************************************/
#ifndef __DFNetRecvBuffer_H__
#define __DFNetRecvBuffer_H__

#include "DFPrerequisite.h"


namespace DF{
	// -----------------------------------------------------------------------
	// @brief 网络接收缓冲区
	class DFExport NetRecvBuffer
	{
	public:
		typedef std::queue<NetBuffer*>	BufQueue;

	public:
		// -----------------------------------------------------------------------
		// @brief 析构函数
		~NetRecvBuffer(void);
		// -----------------------------------------------------------------------
		// @brief 构造函数
		// @param[uBlockSize] 缓冲区大小
		// @param[uBlockNum] 缓冲区数量
		NetRecvBuffer(unsigned short uBlockSize, unsigned short uBlockNum);
		// -----------------------------------------------------------------------
		// @brief 写消息进缓冲区
		// @param[pMsg] 消息
		bool writeMessage(MessageBase* pMsg);
		// -----------------------------------------------------------------------
		// @brief 从缓冲区读取消息
		// @param[pMsg] 消息
		bool readMessage(MessageBase** pMsg);		
		// -----------------------------------------------------------------------
		// @brief 获取下一个读buf
		bool moveToNextReadBuf(void);						


	protected:
		NetBuffer*			m_pReadBuf;
		NetBuffer*			m_pWriteBuf;
		unsigned short		m_uBlockNum;
		BufQueue			m_BufQueue;
	};
}

#endif