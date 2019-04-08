/************************************************************************
* @File			:	DFNetBuffer.h
* @Author		:	Sword
* @Description	:
*
*
*
*
************************************************************************/
#ifndef __DFNetBuffer_H__
#define __DFNetBuffer_H__

#include "DFPrerequisite.h"

namespace DF{
	//------------------------------------------------------------------------
	// @brief 网络数据
	class DFExport NetBuffer
	{
	public:
		// -----------------------------------------------------------------------
		// @brief 析构函数
		~NetBuffer(void);
		// -----------------------------------------------------------------------
		// @brief 构造函数
		// @param[uMaxSize] 数据最大值
		NetBuffer(unsigned short uMaxSize);
		// -----------------------------------------------------------------------
		// @brief 重置
		// @param[uSize] 重置大小
		void reset(unsigned short uSize = 0);
		// -----------------------------------------------------------------------
		// @brief 获取数据头
		// @param[uSize] 大小
		void* getHeadPtr(unsigned short uSize = 0);
		// -----------------------------------------------------------------------
		// @brief 获取数据大小
		unsigned short getMaxSize(void)const;
		// -----------------------------------------------------------------------
		// @brief 获取数据还能写入大小
		unsigned short getCanWriteSize(void)const;
		// -----------------------------------------------------------------------
		// @brief 获取数据还能读取大小
		unsigned short getCanReadSize(void)const;
		// -----------------------------------------------------------------------
		// @brief 获取数据已读大小
		unsigned short getReadSize(void)const;
		// -----------------------------------------------------------------------
		// @brief 获取数据已写大小
		unsigned short getWriteSize(void)const;
		// -----------------------------------------------------------------------
		// @brief 获取写数据块
		void* getWriteFence();
		// -----------------------------------------------------------------------
		// @brief 写数据
		// @param[pHead] 数据
		// @param[uSize] 大小
		void writeBytes(const void* pHead, unsigned short uSize);
		// -----------------------------------------------------------------------
		// @brief 移动写数据块
		// @param[uSize] 移动大小
		void moveWriteFence(unsigned short uSize);
		// -----------------------------------------------------------------------
		// @brief 获取读数据块
		void* getReadFence(void);
		// -----------------------------------------------------------------------
		// @brief 移动读数据块
		// @param[uSize] 移动大小
		void moveReadFence(unsigned short uSize);
		// -----------------------------------------------------------------------
		// @brief 插入数据
		// @param[pHead] 数据
		// @param[uSize] 大小
		void insertBytes(const void* pHead, unsigned short uSize);


	protected:
		char*						m_pHead;
		unsigned short				m_uReadSize;
		unsigned short				m_uWriteSize;
		unsigned short				m_uMaxSize;

	};
}


#endif