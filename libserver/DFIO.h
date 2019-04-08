/************************************************************************
* @File			:	DFIO.h
* @Author		:	Sword
* @DateTime		:	2013.12.9
* @Description	:
*
*
*
*
************************************************************************/
#ifndef __DFIO_H__
#define __DFIO_H__
#include "DFPrerequisite.h"
#include "DFDateTime.h"

namespace DF{
	class DFExport IO
	{
	public:
		~IO(void);
		IO(void);

		void redirectOutAndErrStream(const char* sFilePath);	
		void afterPrint(const char* pString);
		void onWork();

	private:
		bool					m_bIsAfterPrint;
	};


#if DF_TARGET_PLATFORM == DF_PLATFORM_WINDOWS
	inline std::ostream& blue(std::ostream &s)
	{
		HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hStdout, FOREGROUND_BLUE
			| FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		return s;
	}

	inline std::ostream& red(std::ostream &s)
	{
		HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hStdout,
			FOREGROUND_RED | FOREGROUND_INTENSITY);
		return s;
	}

	inline std::ostream& green(std::ostream &s)
	{
		HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hStdout,
			FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		return s;
	}

	inline std::ostream& yellow(std::ostream &s)
	{
		HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hStdout,
			FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		return s;
	}

	inline std::ostream& white(std::ostream &s)
	{
		HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hStdout,
			FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		return s;
	}
#endif

}

/************************************************************************
DF_IN   是对标准输入流的一个统一的宏
DF_OUT  是对标准输出流的一个统一的宏，标准输出流可被被重定向到文件
DF_EXC  是带特殊标准的标准输出流的一个统一的宏，可做关键字扫描日志文件
DF_END  是对标准结束符的一个统一的宏
************************************************************************/
#if DF_TARGET_PLATFORM == DF_PLATFORM_WINDOWS
#define DF_IN  std::cin
#define DF_OUT std::cout<<DF::white
#define DF_ERR std::cerr<<DF::red
#define DF_INFO std::cout<<DF::green
#define DF_EXC std::cout<<DF::yellow<<DF::DateTime::instancePtr()->hour()<<":"<<DF::DateTime::instancePtr()->minute()<<":"<<DF::DateTime::instancePtr()->second()<<" "
#define DF_END DF::white<<std::endl
#elif DF_TARGET_PLATFORM == DF_PLATFORM_LINUX
#define DF_IN  std::cin
#define DF_OUT std::cout
#define DF_ERR std::cerr
#define DF_INFO std::cout
#define DF_EXC std::cout<<"DF_EXC "<<DF::DateTime::instancePtr()->year()<<"-"<<DF::DateTime::instancePtr()->month()<<"-"<<DF::DateTime::instancePtr()->day()<<" "<<DF::DateTime::instancePtr()->hour()<<":"<<DF::DateTime::instancePtr()->minute()<<":"<<DF::DateTime::instancePtr()->second()<<" "
#define DF_END std::endl
#endif



#endif