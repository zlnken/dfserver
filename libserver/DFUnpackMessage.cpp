#include "DFUnpackMessage.h"
#include "DFMessageBase.h"
#include "DFIO.h"
#include "DFDateTime.h"
#include "DFUString.h"

namespace DF{

#define UNPACK_VALUE(itype) \
	itype i = 0; \
	unsigned short uSize = sizeof(itype); \
	if (uSize > m_nSurplusSize)	\
	{	\
		m_bIsOK = false;	\
	}	\
	else	\
	{	\
		i = *(reinterpret_cast<itype*>(m_pUnpackFence));	\
		m_pUnpackFence += uSize;	\
		m_nSurplusSize -= uSize;	\
	}	\
	return i;

	
	// -----------------------------------------------------------------------
	UnpackMessage::~UnpackMessage(void)
	{
		//std::socket()
	}
	// -----------------------------------------------------------------------
	UnpackMessage::UnpackMessage(void):
	m_pUnpackFence(NULL),
	m_nSurplusSize(0),
	m_bIsOK(false)
	{
	}
	// -----------------------------------------------------------------------
	UnpackMessage::UnpackMessage(MessageBase* pMsg):
	m_pUnpackFence(reinterpret_cast<char*>(pMsg)),
	m_nSurplusSize(pMsg->getSize()),
	m_bIsOK(true)
	{
		
	}
	// -----------------------------------------------------------------------
	UnpackMessage::UnpackMessage(void* pHead, unsigned int uSize):
	m_pUnpackFence(reinterpret_cast<char*>(pHead)),
	m_nSurplusSize(uSize),
	m_bIsOK(true)
	{
	}
	// -----------------------------------------------------------------------
	void UnpackMessage::reset(MessageBase* pMsg)
	{
		m_pUnpackFence = reinterpret_cast<char*>(pMsg);
		m_nSurplusSize = pMsg->getSize();
		m_bIsOK = true;
	}
	// -----------------------------------------------------------------------
	void UnpackMessage::reset(char* pUnpackFence, unsigned int nSurplusSize)
	{
		m_pUnpackFence = pUnpackFence;
		m_nSurplusSize = nSurplusSize;
		m_bIsOK = true;
	}
	// -----------------------------------------------------------------------
	bool UnpackMessage::unpackMsg(unsigned int uSize)
	{
		if (uSize > m_nSurplusSize)
		{
			m_bIsOK = false;
		}
		else
		{
			m_pUnpackFence += uSize;
			m_nSurplusSize -= uSize;
		}
		return m_bIsOK;
	}
	// -----------------------------------------------------------------------
	char UnpackMessage::unpackInt8(void)
	{
		UNPACK_VALUE(char);
	}
	// -----------------------------------------------------------------------
	short UnpackMessage::unpackInt16(void)
	{
		UNPACK_VALUE(short);
	}
	// -----------------------------------------------------------------------
	int UnpackMessage::unpackInt32(void)
	{
		UNPACK_VALUE(int);
	}
	// -----------------------------------------------------------------------
	unsigned char UnpackMessage::unpackUint8(void)
	{
		UNPACK_VALUE(unsigned char);
	}
	// -----------------------------------------------------------------------
	unsigned short UnpackMessage::unpackUint16(void)
	{
		UNPACK_VALUE(unsigned short);
	}
	// -----------------------------------------------------------------------
	unsigned int UnpackMessage::unpackUint32(void)
	{
		UNPACK_VALUE(unsigned int);
	}
	// -----------------------------------------------------------------------
	float UnpackMessage::unpackFloat(void)
	{
		UNPACK_VALUE(float);
	}
	// -----------------------------------------------------------------------
	double UnpackMessage::unpackDouble(void)
	{
		UNPACK_VALUE(double);
	}
	// -----------------------------------------------------------------------
	char* UnpackMessage::getUnpackFence(void)
	{
		return m_pUnpackFence;
	}
	// -----------------------------------------------------------------------
	void* UnpackMessage::unpackStream(unsigned short uSize)
	{
		if (uSize > m_nSurplusSize)
		{
			m_bIsOK = false;
		}
		else
		{
			void* pHead = m_pUnpackFence;
			m_pUnpackFence += uSize;
			m_nSurplusSize -= uSize;
			return pHead;
		}
		return NULL;
	}
	// -----------------------------------------------------------------------
	const char* UnpackMessage::unpackString(void)
	{
		if (m_nSurplusSize <= 0)
		{
			m_bIsOK = false;
			return NULL;
		}

		char t = unpackInt8();
		if (Config::SMALL_STRING_FLAG == t)
		{
			unsigned char uSize = unpackUint8();
			void* data = unpackStream(static_cast<unsigned short>(uSize));
			//return UString(static_cast<const char*>(data), uSize).asUTF8();
			//return boost::locale::conv::to_utf<char>(static_cast<const char*>(data), "GBK").c_str();
			return static_cast<const char*>(data);
			
		}
		else if (Config::BIG_STRING_FLAG == t)
		{
			unsigned short uSize = unpackUint16();
			void* data = unpackStream(uSize);
			//return UString(static_cast<const char*>(data), uSize).asUTF8();
			//return boost::locale::conv::to_utf<char>(static_cast<const char*>(data), "GBK").c_str();
			return static_cast<const char*>(data);
			//boost::locale::
		}
		else
		{
			DF_EXC << "unpack string error." << DF_END;
			m_bIsOK = false;
		}
		return NULL;
	}

	// -----------------------------------------------------------------------
	double UnpackMessage::unpackValue(void)
	{
		if (m_nSurplusSize <= 0)
		{
			m_bIsOK = false;
			return 0;
		}

		char flag = unpackInt8();
		if (flag == Config::FLOAT_FLAG)
		{
			return static_cast<double>(unpackFloat());
		}
		else if (flag == Config::DOUBLE_FLAG)
		{
			return unpackDouble();
		}
		else if (flag == Config::SIGNED_INT8_FLAG)
		{
			return static_cast<double>(unpackInt8());
		}
		else if (flag == Config::SIGNED_INT16_FLAG)
		{
			return static_cast<double>(unpackInt16());
		}
		else if (flag == Config::SIGNED_INT32_FLAG)
		{
			return static_cast<double>(unpackInt32());
		}
		else
		{
			DF_EXC << "unpack int obj error." << DF_END;
			this->m_bIsOK = false;
		}
		return 0.0;
	}
}