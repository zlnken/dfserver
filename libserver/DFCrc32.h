/************************************************************************
* @File			:	DFCrc32.h
* @Author		:	Sword
* @DateTime		:	2014.6.19 
* @Description	:
*
*
*
*
************************************************************************/
#ifndef __DFCrc32_H__ 
#define __DFCrc32_H__
#include "DFPrerequisite.h"


namespace DF
{
	//------------------------------------------------------------------------
	// @brief 对一串字符转换成一个32位整形
	class DFExport Crc32
	{
	public:
		// -----------------------------------------------------------------------
		// @brief 析构函数
		~Crc32(void);
		// -----------------------------------------------------------------------
		// @brief 清空数据
		void clear(void);
		// -----------------------------------------------------------------------
		// @brief 获取单例指针
		static Crc32* instancePtr(void);
		// -----------------------------------------------------------------------
		// @brief 获取单例实体
		static Crc32& instance(void);
		// -----------------------------------------------------------------------
		// @brief 清空单例
		static void unstance(void);
		// -----------------------------------------------------------------------
		// @brief 对字符串转换成无符号整形
		// @param[pBuf] 字符串
		unsigned int crcChars(const char* pBuf);
		// -----------------------------------------------------------------------
		// @brief 添加一个ID对应一个字符串
		void append(unsigned int uId, const char* pStr);
		// -----------------------------------------------------------------------
		// @brief 查找一个字符串
		const char* find(unsigned int uId)const;
		// -----------------------------------------------------------------------
		// @brief 移除一个字符串
		// @param[uId] 查找标识
		bool remove(unsigned int uId);
		// -----------------------------------------------------------------------
		// @brief 遍历
		void begin(void);
		bool hasNext(void)const;
		void get(unsigned int& uKey, std::string& sPath)const;
		void next(void);

	private:
		// -----------------------------------------------------------------------
		// @brief 构造函数
		Crc32(void);
		// -----------------------------------------------------------------------
		// @brief 初始化
		void init(void);	
		
	private:
		typedef boost::unordered_map<unsigned int, std::string> Crc32HashMap;
		typedef Crc32HashMap::iterator Crc32HashMapIt;
		typedef Crc32HashMap::const_iterator Crc32HashMapCIt;

		unsigned int m_uCrcTabel[256];
		static Crc32* m_pInstance;
		Crc32HashMap m_Crc32HashMap;
		Crc32HashMapCIt m_cIt;


	};





}





#endif