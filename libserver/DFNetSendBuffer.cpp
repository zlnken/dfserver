#include "DFNetSendBuffer.h"
#include "DFNetBuffer.h"
namespace DF{
	// -----------------------------------------------------------------------
	NetSendBuffer::~NetSendBuffer(void)
	{
		DF_SAFE_DELETE(m_pReadBuf);
		DF_SAFE_DELETE(m_pWriteBuf);
		while (!m_BufQueue.empty())
		{
			DF_SAFE_DELETE(m_BufQueue.front());
			this->m_BufQueue.pop();
		}
	}
	// -----------------------------------------------------------------------
	NetSendBuffer::NetSendBuffer(unsigned short uBlockSize, unsigned short uBlockNum) :
	m_pReadBuf(NULL),
	m_pWriteBuf(NULL),
	m_BufQueue(),
	m_bIsHoldBlock(false),
	m_uBlockNum(uBlockNum)
	{
		m_pReadBuf = new NetBuffer(uBlockSize);
		m_pWriteBuf = new NetBuffer(uBlockSize);
	}
	// -----------------------------------------------------------------------
	bool NetSendBuffer::writeBytes(const void* pHead, unsigned short uSize)
	{
		// 写入数据太长
		if (m_pWriteBuf->getCanWriteSize() < uSize)
		{
			// 扩容超过上限
			if (m_BufQueue.size() > m_uBlockNum)
			{
				return false;
			}	
			else
			{
				// 开始扩容		
				unsigned short uL = m_pWriteBuf->getCanWriteSize();
				m_pWriteBuf->writeBytes(pHead, uL);
				m_pWriteBuf->moveWriteFence(uL);
				// 修正要写入头
				pHead = (const char*)pHead + uL;
				m_BufQueue.push(m_pWriteBuf);
				m_pWriteBuf = new NetBuffer(m_pWriteBuf->getMaxSize());
				// 尝试再次写入
				return writeBytes(pHead, uSize);
			}
		}
		else
		{
			m_pWriteBuf->writeBytes(pHead, uSize);
			m_pWriteBuf->moveWriteFence(uSize);
			return true;
		}
	}
	// -----------------------------------------------------------------------
	bool NetSendBuffer::holdBlock(void** pHead, unsigned short& uSize)
	{
		// 如果已经被hold住了直接返回
		if (m_bIsHoldBlock)
		{
			return false;
		}
		// 如果容器列表为空直接交换读写
		if (m_BufQueue.empty())
		{
			// 查看buffer是否可读取
			if (m_pWriteBuf->getCanReadSize())
			{
				std::swap(m_pReadBuf, m_pWriteBuf);
				m_pWriteBuf->reset();
			}
			else
			{
				return false;
			}
			
		}
		else
		{
			// 扩容列表不为空删除当前的读buf，从扩容列表中拿出头部的buf当做读buf
			DF_SAFE_DELETE(m_pReadBuf);
			m_pReadBuf = m_BufQueue.front();
			m_BufQueue.pop();
		}
		// 此时读buf必定是OK的
		// 将读buf带出去，并标识为已经hold
		*pHead = m_pReadBuf->getHeadPtr();
		uSize = m_pReadBuf->getCanReadSize();
		m_bIsHoldBlock = true;
		return true;
	}
	// -----------------------------------------------------------------------
	void NetSendBuffer::releaseBlock(void)
	{
		// 断言此时有Block被外部hold住
		DF_ASSERT(true == m_bIsHoldBlock);
		// 初始化buf
		this->m_pReadBuf->reset();
		// 置标志位
		this->m_bIsHoldBlock = false;
	}
	// -----------------------------------------------------------------------
	bool NetSendBuffer::isEmpty(void)const
	{
		return m_BufQueue.empty() && m_pReadBuf->getCanReadSize() == 0 && m_pWriteBuf->getCanReadSize() == 0;
	}
}