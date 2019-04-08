/************************************************************************
* @File			:	DFDefine.h
* @Author		:	Sword
* @DateTime		:	2013.12.9
* @Description	:
*
*
*
*
************************************************************************/
#ifndef __DFDefine_H__
#define __DFDefine_H__


#define DF_PLATFORM_UNKNOW	0		/// 未知平台
#define DF_PLATFORM_WINDOWS 1		/// Windows平台
#define DF_PLATFORM_LINUX   2		/// Linux平台

#define  DF_TARGET_PLATFORM	DF_PLATFORM_UNKNOW

#if defined(_WIN32) || defined(_WIN64)
#	define _WIN32_WINNT 0x0501
#	undef  DF_TARGET_PLATFORM
#	define DF_TARGET_PLATFORM DF_PLATFORM_WINDOWS
#	pragma warning (disable : 4251)
#	pragma warning (disable : 4244)
#	pragma warning (disable : 4305)
#	pragma warning (disable : 4996)
#	pragma warning (disable : 4819)
#	pragma warning (disable : 4717)
#	pragma warning (disable : 4800)
#	pragma warning (disable : 4076)
#else
#	undef  DF_TARGET_PLATFORM
#	define DF_TARGET_PLATFORM DF_PLATFORM_LINUX
#endif


// #if defined(__linux__) || defined(linux) || defined(_LINUX) || defined(__unix__) || defined(unix) || defined(_UNIX) 
// #	undef  DF_TARGET_PLATFORM
// #	define DF_TARGET_PLATFORM DF_PLATFORM_LINUX
// #endif


// 安全删除
#define DF_SAFE_DELETE(p) if(p){delete p; p = 0;}

// 最大值，最小值
#define DF_MAX(a, b) (((a) > (b)) ? (a) : (b))
#define DF_MIN(a, b) (((a) < (b)) ? (a) : (b))

// 断言
#define DF_ASSERT(exp) if(!(exp)){abort();}
#define DF_STATIC_ASSERT static_assert

#define DFExport 
#if defined(DF_STATIC_LIBRARY)
#else
#	if defined(DF_DYNAMIC_LIBRARY)
#		if DF_TARGET_PLATFORM == DF_PLATFORM_WINDOWS
#			undef  DFExport
#			define DFExport __declspec(dllexport)
#		else
#		endif
#	else
#		if DF_TARGET_PLATFORM == DF_PLATFORM_WINDOWS
#			undef  DFExport
#			define DFExport __declspec(dllimport)
#		else
#		endif
#	endif
#endif

// 跨平台整数
namespace DF
{
#if DF_TARGET_PLATFORM == DF_PLATFORM_WINDOWS
	typedef signed __int64		int64;
	typedef unsigned __int64	uint64;
#elif DF_TARGET_PLATFORM == DF_PLATFORM_LINUX
	typedef signed long long	int64;
	typedef unsigned long long	uint64;
#endif
}

#endif