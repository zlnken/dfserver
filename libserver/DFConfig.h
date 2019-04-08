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
#ifndef __DFServerConfig_H__
#define __DFServerConfig_H__

#include "DFDefine.h"
#include <string>

namespace DF{
	
	class DFExport Config
	{
	public:
		// @brief 整数取值范围
		static const char					MIN_INT8;
		static const char					MAX_INT8;
		static const short					MIN_INT16;
		static const short					MAX_INT16;
		static const int					MIN_INT32;
		static const int					MAX_INT32;
		static const int64					MIN_INT64;
		static const int64					MAX_INT64;
		static const unsigned char			MAX_UINT8;
		static const unsigned short			MAX_UINT16;
		static const unsigned int			MAX_UINT32;
		static const uint64					MAX_UINT64;
		static const float					MIN_FLOAT;
		static const float					MAX_FLOAT;
		static const double					MIN_DOUBLE;
		static const double					MAX_DOUBLE;

		static const char					MAX_STACK_DEEP;
		static const char					NONE_FLAG;
		static const char					TRUE_FLAG;
		static const char					FALSE_FLAG;
		static const char					SMALL_TUPLE_FLAG;
		static const char					BIG_TUPLE_FLAG;
		static const char					SMALL_LIST_FLAG;
		static const char					BIG_LIST_FLAG;
		static const char					SMALL_SET_FLAG;
		static const char					BIG_SET_FLAG;
		static const char					SMALL_DICT_FLAG;
		static const char					BIG_DICT_FLAG;
		static const char					SMALL_STRING_FLAG;
		static const char					BIG_STRING_FLAG;
		static const char					DATETIME_FLAG;
		static const char					SIGNED_INT8_FLAG;
		static const char					SIGNED_INT16_FLAG;
		static const char					SIGNED_INT32_FLAG;
		static const char					SIGNED_INT64_FLAG;
		static const char					CLASS_OBJ_FLAG;
		static const char					FLOAT_FLAG;
		static const char					DOUBLE_FLAG;
		

		// @brief 连接的默认参数
		static unsigned int					SEND_BLOCK_SIZE;
		static unsigned int					SEND_BLOCK_NUM;
		static unsigned int					RECV_BLOCK_SIZE;
		static unsigned int					RECV_BLOCK_NUM;

		// @brief 网络消息默认参数
		static unsigned int					MSG_MAX_SIZE;
		static unsigned int					MSG_BASE_SIZE;

		// @brief 打包参数
		static unsigned int					MAX_PACK_SIZE;
		
		static unsigned int					MAX_CONNECT;
		static unsigned short				MAX_THREAD;
		static unsigned short				DEFAULT_PORT;
		static unsigned short				DATA_BASE_PORT;
		static unsigned short				LOGIN_PORT;

		
		


	};
}



#endif


