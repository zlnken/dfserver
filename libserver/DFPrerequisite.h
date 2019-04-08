/************************************************************************
* @File			:	DFNetConnect.h
* @Author		:	Sword
* @Description	:
*
*
*
*
************************************************************************/
#ifndef __DFPrerequisite_H__
#define __DFPrerequisite_H__

#include "DFDefine.h"


#include "DFConfig.h"

#include <stdlib.h>
#include <string>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <vector>
#include <set>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/timeb.h>



#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/unordered_map.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/locale.hpp>



#if DF_TARGET_PLATFORM == DF_PLATFORM_WINDOWS
#	include <windows.h>
#	include <libvld/vld.h>
#	include <io.h>
#	include <direct.h>
#	include <fcntl.h>
#else
#include <dirent.h>  
#endif


namespace DF{
	class B2;
	class B4;
	class B8;
	class IO;
	class Process;
	class MessageBase;
	class PackMessage;
	class UnpackMessage;
	class NetBuffer;
	class NetSendBuffer;
	class NetRecvBuffer;
	class NetWork;
	class NetConnect;
	class Trigger;
	class GlobalIDAlloc;
	class DateTime;
	class DataBaseMySQL;
	class DataBaseServer;
	class BaseServer;
	class UString;
	


	class LuaTrigger;
	class LuaStack;
	class LuaFunction;
	


	// boost 自定义如果能单独把asio抽出来就好了
	typedef boost::asio::ip::tcp::socket				BoostSocket;
	typedef boost::asio::io_service						BoostIOService;
	typedef boost::asio::ip::tcp::acceptor				BoostAcceptor;
	typedef boost::thread								BoostThread;
	typedef boost::mutex								BoostMutex;
	typedef boost::asio::ip::tcp::resolver				BoostResolver;
	typedef std::vector<BoostThread*>					BoostThreads;



}

#if DF_PLATFORM_WINDOWS == DF_TARGET_PLATFORM
#	define DF_AS_B2(v) reinterpret_cast<DF::B2&>(v);DF_ASSERT(sizeof(v) == 2);
#	define DF_AS_B4(v) reinterpret_cast<DF::B4&>(v);DF_ASSERT(sizeof(v) == 4);
#	define DF_AS_B8(v) reinterpret_cast<DF::B8&>(v);DF_ASSERT(sizeof(v) == 8);
#elif DF_PLATFORM_LINUX == DF_TARGET_PLATFORM
#	define DF_AS_B2(v) reinterpret_cast<DF::B2&>(v);
#	define DF_AS_B4(v) reinterpret_cast<DF::B4&>(v);
#	define DF_AS_B8(v) reinterpret_cast<DF::B8&>(v);
#endif


#endif 
