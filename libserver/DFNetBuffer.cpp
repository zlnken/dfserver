#include "DFNetBuffer.h"

namespace DF{
	// -----------------------------------------------------------------------
	NetBuffer::~NetBuffer(void)
	{
		DF_SAFE_DELETE(m_pHead);
	}
	// -----------------------------------------------------------------------
	NetBuffer::NetBuffer(unsigned short uMaxSize):
	m_pHead(NULL),
	m_uReadSize(0),
	m_uWriteSize(0),
	m_uMaxSize(uMaxSize)
	{
		m_pHead = new char[uMaxSize];
	}
	// -----------------------------------------------------------------------
	void NetBuffer::reset(unsigned short uSize)
	{
		m_uReadSize = uSize; 
		m_uWriteSize = uSize;
	}
	// -----------------------------------------------------------------------
	void* NetBuffer::getHeadPtr(unsigned short uSize)
	{
		return (m_pHead + uSize);
	}
	// -----------------------------------------------------------------------
	unsigned short NetBuffer::getMaxSize(void)const
	{
		return m_uMaxSize;
	}
	// -----------------------------------------------------------------------
	unsigned short NetBuffer::getCanWriteSize(void)const
	{
		return m_uMaxSize - m_uWriteSize;
	}
	// -----------------------------------------------------------------------
	unsigned short NetBuffer::getCanReadSize(void)const
	{
		return m_uWriteSize - m_uReadSize;
	}
	// -----------------------------------------------------------------------
	unsigned short NetBuffer::getReadSize(void)const
	{
		return m_uReadSize;
	}
	// -----------------------------------------------------------------------
	unsigned short NetBuffer::getWriteSize(void)const
	{
		return m_uWriteSize;
	}

	// -----------------------------------------------------------------------
	void* NetBuffer::getWriteFence()
	{
		return m_pHead + m_uWriteSize;
	}
	// -----------------------------------------------------------------------
	void NetBuffer::writeBytes(const void* pHead, unsigned short uSize)
	{
		memcpy((m_pHead + m_uWriteSize), pHead, uSize);
	}
	// -----------------------------------------------------------------------
	void NetBuffer::moveWriteFence(unsigned short uSize)
	{
		m_uWriteSize += uSize;
	}
	// -----------------------------------------------------------------------
	void* NetBuffer::getReadFence(void)
	{
		return (m_pHead + m_uReadSize);
	}
	// -----------------------------------------------------------------------
	void NetBuffer::moveReadFence(unsigned short uSize)
	{
		m_uReadSize += uSize;
	}
	// -----------------------------------------------------------------------
	void NetBuffer::insertBytes(const void* pHead, unsigned short uSize)
	{
		memcpy(m_pHead, pHead, uSize);
	}
}