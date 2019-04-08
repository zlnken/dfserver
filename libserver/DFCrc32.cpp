#include "DFCrc32.h"
namespace DF
{
	// -----------------------------------------------------------------------
	Crc32* Crc32::m_pInstance = NULL;
	// -----------------------------------------------------------------------
	Crc32::~Crc32(void)
	{
		clear();
	}
	// -----------------------------------------------------------------------
	Crc32::Crc32(void)
	{
		m_Crc32HashMap.clear();
	}
	// -----------------------------------------------------------------------
	void Crc32::init(void)
	{
		unsigned int c;
		unsigned int i, j;
		for(i=0; i<256; ++i)
		{
			c = i;
			for(j=0;j<8;++j)
			{
				if(c&1)
					c = 0xedb88320L ^ (c >> 1);
				else
					c=c>>1;
			}
			m_uCrcTabel[i] = c;
		}
	}
	// -----------------------------------------------------------------------
	void Crc32::clear(void)
	{
		m_Crc32HashMap.clear();
	}
	// -----------------------------------------------------------------------
	Crc32* Crc32::instancePtr(void)
	{
		if(!m_pInstance)
		{
			m_pInstance = new Crc32;
			m_pInstance->init();
		}
		return m_pInstance;
	}
	// -----------------------------------------------------------------------
	Crc32& Crc32::instance(void)
	{
		if(!m_pInstance)
		{
			m_pInstance = new Crc32;
			m_pInstance->init();
		}
		return *m_pInstance;
	}
	// -----------------------------------------------------------------------
	void Crc32::unstance(void)
	{
		DF_SAFE_DELETE(m_pInstance);
	}
	// -----------------------------------------------------------------------
	unsigned int Crc32::crcChars(const char* pBuf)
	{
        size_t ulen = strlen(pBuf);
		assert((pBuf || ulen <= 0 || ulen >=256) && "<Crc32::crc32> pBuf == NULL or uLen == 0");
		unsigned int ret = 0xFFFFFFFF;
		for(size_t i = 0; i <ulen;++i)
		{
			ret = m_uCrcTabel[((ret & 0xFF) ^ pBuf[i])] ^ (ret >> 8);
		}
		ret = ~ret;
		append(ret, pBuf);
		return ret;
	}
//	// -----------------------------------------------------------------------
//	unsigned int Crc32::crc32(const std::string& str)
//	{
//		return crc32(str.c_str(), static_cast<unsigned int>(str.length()));
//	}
//	// -----------------------------------------------------------------------
//	unsigned int Crc32::crc32(const UString& str)
//	{
//		const std::string utf8_str = str.asUTF8();
//		return crc32(utf8_str.c_str(), static_cast<unsigned int>(utf8_str.length()));
//	}
	// -----------------------------------------------------------------------
	void Crc32::append(unsigned int uId, const char* pStr)
	{
		Crc32HashMapCIt it = m_Crc32HashMap.find(uId);
		if(it == m_Crc32HashMap.end())
		{
			m_Crc32HashMap[uId] = pStr;
		}
		else
		{
			//if(it->second != pStr)
			//{
			//	Log::sCoreError()->logLine("<Crc32::append> crc32(%s)==crc32(%s)", pStr, it->second.c_str());
			//}
		}
	}
	// -----------------------------------------------------------------------
	const char* Crc32::find(unsigned int uId)const
	{
		Crc32HashMapCIt it = m_Crc32HashMap.find(uId);
		if(it != m_Crc32HashMap.end())
		{
			return it->second.c_str();
		}
		return "";
	}
	// -----------------------------------------------------------------------
	bool Crc32::remove(unsigned int uId)
	{
		Crc32HashMapIt it = m_Crc32HashMap.find(uId);
		if(it != m_Crc32HashMap.end())
		{
			m_Crc32HashMap.erase(it);
			return true;
		}
		return false;
	}
//	// -----------------------------------------------------------------------
//	bool Crc32::remove(const std::string& str)
//	{
//		return remove(crc32(str));
//	}
//	// -----------------------------------------------------------------------
//	bool Crc32::remove(const UString& str)
//	{
//		return remove(crc32(str));
//	}
	// -----------------------------------------------------------------------
	void Crc32::begin(void)
	{
		m_cIt = m_Crc32HashMap.begin();
	}
	// -----------------------------------------------------------------------
	bool Crc32::hasNext(void)const
	{
		return (m_cIt != m_Crc32HashMap.end());
	}
	// -----------------------------------------------------------------------
	void Crc32::get(unsigned int& uKey, std::string& sPath)const
	{
		if(m_cIt != m_Crc32HashMap.end())
		{
			uKey = m_cIt->first;
			sPath = m_cIt->second;
		}
	}
	// -----------------------------------------------------------------------
	void Crc32::next(void)
	{
		++m_cIt;
	}
}