#include "DFConfig.h"

namespace DF{
	
	// -----------------------------------------------------------------------
	// 整数取值范围
	const char					Config::MIN_INT8			= (-127 - 1);
	const char					Config::MAX_INT8			= 127;
	const short					Config::MIN_INT16			= (-32767 - 1);
	const short					Config::MAX_INT16			= 32767;
	const int					Config::MIN_INT32			= (-2147483647 - 1);
	const int					Config::MAX_INT32			= 2147483647;
	const int64					Config::MIN_INT64			= (-9223372036854775807 - 1);
	const int64					Config::MAX_INT64			= 9223372036854775807;
	const unsigned char			Config::MAX_UINT8			= 255U;
	const unsigned short		Config::MAX_UINT16			= 65535U;
	const unsigned int			Config::MAX_UINT32			= 4294967295U;
	const uint64				Config::MAX_UINT64			= 18446744073709551615U;
	const float					Config::MIN_FLOAT			= (-8388608 - 1);
	const float					Config::MAX_FLOAT			= 8388608;
	const double				Config::MIN_DOUBLE			= (-9223372036854775807 - 1);
	const double				Config::MAX_DOUBLE			= 9223372036854775807;

	// -----------------------------------------------------------------------
	const char					Config::MAX_STACK_DEEP		= 30;		
	const char					Config::NONE_FLAG			= -100;			
	const char					Config::TRUE_FLAG			= -101;			
	const char					Config::FALSE_FLAG			= -102;			
	const char					Config::SMALL_TUPLE_FLAG	= -103;	
	const char					Config::BIG_TUPLE_FLAG		= -104;		
	const char					Config::SMALL_LIST_FLAG		= -105;		
	const char					Config::BIG_LIST_FLAG		= -106;		
	const char					Config::SMALL_SET_FLAG		= -107;		
	const char					Config::BIG_SET_FLAG		= -108;		
	const char					Config::SMALL_DICT_FLAG		= -109;		
	const char					Config::BIG_DICT_FLAG		= -110;		
	const char					Config::SMALL_STRING_FLAG	= -111;	
	const char					Config::BIG_STRING_FLAG		= -112;		
	const char					Config::DATETIME_FLAG		= -113;		
	const char					Config::SIGNED_INT8_FLAG	= -114;	
	const char					Config::SIGNED_INT16_FLAG	= -115;	
	const char					Config::SIGNED_INT32_FLAG	= -116;	
	const char					Config::SIGNED_INT64_FLAG	= -117;	
	const char					Config::CLASS_OBJ_FLAG		= -118;
	const char					Config::FLOAT_FLAG			= -119;
	const char					Config::DOUBLE_FLAG			= -120;
	// -----------------------------------------------------------------------
	// 连接的默认参数
	unsigned int			Config::SEND_BLOCK_SIZE = Config::MAX_UINT16;
	unsigned int			Config::SEND_BLOCK_NUM = 1000;
	unsigned int			Config::RECV_BLOCK_SIZE = Config::MAX_UINT16;
	unsigned int			Config::RECV_BLOCK_NUM = 1000;
	// -----------------------------------------------------------------------
	unsigned int			Config::MSG_MAX_SIZE = Config::MAX_UINT16;
	unsigned int			Config::MSG_BASE_SIZE = 4;
	unsigned int			Config::MAX_PACK_SIZE = 500 * 1024 * 1024;
	unsigned int			Config::MAX_CONNECT = 1024;
	unsigned short			Config::MAX_THREAD = 4;
	unsigned short			Config::DEFAULT_PORT = 8080;
	unsigned short			Config::DATA_BASE_PORT = 8000;
	unsigned short			Config::LOGIN_PORT = 4096;
	

}