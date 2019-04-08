/*
** Lua binding: DFLuaServerLib
** Generated automatically by tolua++-1.0.6 on 11/02/18 16:22:32.
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */

#include "DFConfig.h"
#include "DFDateTime.h"
#include "DFMessageBase.h"
#include "DFPackMessage.h"
#include "DFUnpackMessage.h"
#include "DFLuaSystem.h"
#include "DFLuaTrigger.h"
#include "DFLuaFunction.h"
#include "DFNetConnect.h"
#include "DFDataBaseMySQL.h"
#include "DFBaseServer.h"
#include "DFDataBaseServer.h"

namespace DF{
/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"DF::Config");
 tolua_usertype(tolua_S,"DF::LuaFunction");
 tolua_usertype(tolua_S,"DF::NetConnect");
 tolua_usertype(tolua_S,"Process");
 tolua_usertype(tolua_S,"DF::DateTime");
 tolua_usertype(tolua_S,"DF::DataBaseMySQL");
 tolua_usertype(tolua_S,"DF::DataBaseServer");
 tolua_usertype(tolua_S,"DF::BaseServer");
 tolua_usertype(tolua_S,"Trigger");
 tolua_usertype(tolua_S,"DF::LuaTrigger");
 tolua_usertype(tolua_S,"DF::MessageBase");
 tolua_usertype(tolua_S,"DF::LuaSystem");
 tolua_usertype(tolua_S,"uint64");
 tolua_usertype(tolua_S,"DF::UnpackMessage");
 tolua_usertype(tolua_S,"int64");
 tolua_usertype(tolua_S,"DF::PackMessage");
}

/* get function: MIN_INT8 of class  DF::Config */
static int tolua_get_DF__Config_MIN_INT8(lua_State* tolua_S)
{
 tolua_pushnumber(tolua_S,(lua_Number)DF::Config::MIN_INT8);
 return 1;
}

/* get function: MAX_INT8 of class  DF::Config */
static int tolua_get_DF__Config_MAX_INT8(lua_State* tolua_S)
{
 tolua_pushnumber(tolua_S,(lua_Number)DF::Config::MAX_INT8);
 return 1;
}

/* get function: MIN_INT16 of class  DF::Config */
static int tolua_get_DF__Config_MIN_INT16(lua_State* tolua_S)
{
 tolua_pushnumber(tolua_S,(lua_Number)DF::Config::MIN_INT16);
 return 1;
}

/* get function: MAX_INT16 of class  DF::Config */
static int tolua_get_DF__Config_MAX_INT16(lua_State* tolua_S)
{
 tolua_pushnumber(tolua_S,(lua_Number)DF::Config::MAX_INT16);
 return 1;
}

/* get function: MIN_INT32 of class  DF::Config */
static int tolua_get_DF__Config_MIN_INT32(lua_State* tolua_S)
{
 tolua_pushnumber(tolua_S,(lua_Number)DF::Config::MIN_INT32);
 return 1;
}

/* get function: MAX_INT32 of class  DF::Config */
static int tolua_get_DF__Config_MAX_INT32(lua_State* tolua_S)
{
 tolua_pushnumber(tolua_S,(lua_Number)DF::Config::MAX_INT32);
 return 1;
}

/* get function: MIN_INT64 of class  DF::Config */
static int tolua_get_DF__Config_MIN_INT64(lua_State* tolua_S)
{
 tolua_pushusertype(tolua_S,(void*)&DF::Config::MIN_INT64,"const int64");
 return 1;
}

/* get function: MAX_INT64 of class  DF::Config */
static int tolua_get_DF__Config_MAX_INT64(lua_State* tolua_S)
{
 tolua_pushusertype(tolua_S,(void*)&DF::Config::MAX_INT64,"const int64");
 return 1;
}

/* get function: MAX_UINT8 of class  DF::Config */
static int tolua_get_DF__Config_unsigned_MAX_UINT8(lua_State* tolua_S)
{
 tolua_pushnumber(tolua_S,(lua_Number)DF::Config::MAX_UINT8);
 return 1;
}

/* get function: MAX_UINT16 of class  DF::Config */
static int tolua_get_DF__Config_unsigned_MAX_UINT16(lua_State* tolua_S)
{
 tolua_pushnumber(tolua_S,(lua_Number)DF::Config::MAX_UINT16);
 return 1;
}

/* get function: MAX_UINT32 of class  DF::Config */
static int tolua_get_DF__Config_unsigned_MAX_UINT32(lua_State* tolua_S)
{
 tolua_pushnumber(tolua_S,(lua_Number)DF::Config::MAX_UINT32);
 return 1;
}

/* get function: MAX_UINT64 of class  DF::Config */
static int tolua_get_DF__Config_MAX_UINT64(lua_State* tolua_S)
{
 tolua_pushusertype(tolua_S,(void*)&DF::Config::MAX_UINT64,"const uint64");
 return 1;
}

/* get function: MIN_FLOAT of class  DF::Config */
static int tolua_get_DF__Config_MIN_FLOAT(lua_State* tolua_S)
{
 tolua_pushnumber(tolua_S,(lua_Number)DF::Config::MIN_FLOAT);
 return 1;
}

/* get function: MAX_FLOAT of class  DF::Config */
static int tolua_get_DF__Config_MAX_FLOAT(lua_State* tolua_S)
{
 tolua_pushnumber(tolua_S,(lua_Number)DF::Config::MAX_FLOAT);
 return 1;
}

/* get function: MIN_DOUBLE of class  DF::Config */
static int tolua_get_DF__Config_MIN_DOUBLE(lua_State* tolua_S)
{
 tolua_pushnumber(tolua_S,(lua_Number)DF::Config::MIN_DOUBLE);
 return 1;
}

/* get function: MAX_DOUBLE of class  DF::Config */
static int tolua_get_DF__Config_MAX_DOUBLE(lua_State* tolua_S)
{
 tolua_pushnumber(tolua_S,(lua_Number)DF::Config::MAX_DOUBLE);
 return 1;
}

/* get function: MAX_STACK_DEEP of class  DF::Config */
static int tolua_get_DF__Config_MAX_STACK_DEEP(lua_State* tolua_S)
{
 tolua_pushnumber(tolua_S,(lua_Number)DF::Config::MAX_STACK_DEEP);
 return 1;
}

/* get function: NONE_FLAG of class  DF::Config */
static int tolua_get_DF__Config_NONE_FLAG(lua_State* tolua_S)
{
 tolua_pushnumber(tolua_S,(lua_Number)DF::Config::NONE_FLAG);
 return 1;
}

/* get function: TRUE_FLAG of class  DF::Config */
static int tolua_get_DF__Config_TRUE_FLAG(lua_State* tolua_S)
{
 tolua_pushnumber(tolua_S,(lua_Number)DF::Config::TRUE_FLAG);
 return 1;
}

/* get function: FALSE_FLAG of class  DF::Config */
static int tolua_get_DF__Config_FALSE_FLAG(lua_State* tolua_S)
{
 tolua_pushnumber(tolua_S,(lua_Number)DF::Config::FALSE_FLAG);
 return 1;
}

/* get function: SMALL_TUPLE_FLAG of class  DF::Config */
static int tolua_get_DF__Config_SMALL_TUPLE_FLAG(lua_State* tolua_S)
{
 tolua_pushnumber(tolua_S,(lua_Number)DF::Config::SMALL_TUPLE_FLAG);
 return 1;
}

/* get function: BIG_TUPLE_FLAG of class  DF::Config */
static int tolua_get_DF__Config_BIG_TUPLE_FLAG(lua_State* tolua_S)
{
 tolua_pushnumber(tolua_S,(lua_Number)DF::Config::BIG_TUPLE_FLAG);
 return 1;
}

/* get function: SMALL_LIST_FLAG of class  DF::Config */
static int tolua_get_DF__Config_SMALL_LIST_FLAG(lua_State* tolua_S)
{
 tolua_pushnumber(tolua_S,(lua_Number)DF::Config::SMALL_LIST_FLAG);
 return 1;
}

/* get function: BIG_LIST_FLAG of class  DF::Config */
static int tolua_get_DF__Config_BIG_LIST_FLAG(lua_State* tolua_S)
{
 tolua_pushnumber(tolua_S,(lua_Number)DF::Config::BIG_LIST_FLAG);
 return 1;
}

/* get function: SMALL_SET_FLAG of class  DF::Config */
static int tolua_get_DF__Config_SMALL_SET_FLAG(lua_State* tolua_S)
{
 tolua_pushnumber(tolua_S,(lua_Number)DF::Config::SMALL_SET_FLAG);
 return 1;
}

/* get function: BIG_SET_FLAG of class  DF::Config */
static int tolua_get_DF__Config_BIG_SET_FLAG(lua_State* tolua_S)
{
 tolua_pushnumber(tolua_S,(lua_Number)DF::Config::BIG_SET_FLAG);
 return 1;
}

/* get function: SMALL_DICT_FLAG of class  DF::Config */
static int tolua_get_DF__Config_SMALL_DICT_FLAG(lua_State* tolua_S)
{
 tolua_pushnumber(tolua_S,(lua_Number)DF::Config::SMALL_DICT_FLAG);
 return 1;
}

/* get function: BIG_DICT_FLAG of class  DF::Config */
static int tolua_get_DF__Config_BIG_DICT_FLAG(lua_State* tolua_S)
{
 tolua_pushnumber(tolua_S,(lua_Number)DF::Config::BIG_DICT_FLAG);
 return 1;
}

/* get function: SMALL_STRING_FLAG of class  DF::Config */
static int tolua_get_DF__Config_SMALL_STRING_FLAG(lua_State* tolua_S)
{
 tolua_pushnumber(tolua_S,(lua_Number)DF::Config::SMALL_STRING_FLAG);
 return 1;
}

/* get function: BIG_STRING_FLAG of class  DF::Config */
static int tolua_get_DF__Config_BIG_STRING_FLAG(lua_State* tolua_S)
{
 tolua_pushnumber(tolua_S,(lua_Number)DF::Config::BIG_STRING_FLAG);
 return 1;
}

/* get function: DATETIME_FLAG of class  DF::Config */
static int tolua_get_DF__Config_DATETIME_FLAG(lua_State* tolua_S)
{
 tolua_pushnumber(tolua_S,(lua_Number)DF::Config::DATETIME_FLAG);
 return 1;
}

/* get function: SIGNED_INT8_FLAG of class  DF::Config */
static int tolua_get_DF__Config_SIGNED_INT8_FLAG(lua_State* tolua_S)
{
 tolua_pushnumber(tolua_S,(lua_Number)DF::Config::SIGNED_INT8_FLAG);
 return 1;
}

/* get function: SIGNED_INT16_FLAG of class  DF::Config */
static int tolua_get_DF__Config_SIGNED_INT16_FLAG(lua_State* tolua_S)
{
 tolua_pushnumber(tolua_S,(lua_Number)DF::Config::SIGNED_INT16_FLAG);
 return 1;
}

/* get function: SIGNED_INT32_FLAG of class  DF::Config */
static int tolua_get_DF__Config_SIGNED_INT32_FLAG(lua_State* tolua_S)
{
 tolua_pushnumber(tolua_S,(lua_Number)DF::Config::SIGNED_INT32_FLAG);
 return 1;
}

/* get function: SIGNED_INT64_FLAG of class  DF::Config */
static int tolua_get_DF__Config_SIGNED_INT64_FLAG(lua_State* tolua_S)
{
 tolua_pushnumber(tolua_S,(lua_Number)DF::Config::SIGNED_INT64_FLAG);
 return 1;
}

/* get function: CLASS_OBJ_FLAG of class  DF::Config */
static int tolua_get_DF__Config_CLASS_OBJ_FLAG(lua_State* tolua_S)
{
 tolua_pushnumber(tolua_S,(lua_Number)DF::Config::CLASS_OBJ_FLAG);
 return 1;
}

/* get function: FLOAT_FLAG of class  DF::Config */
static int tolua_get_DF__Config_FLOAT_FLAG(lua_State* tolua_S)
{
 tolua_pushnumber(tolua_S,(lua_Number)DF::Config::FLOAT_FLAG);
 return 1;
}

/* get function: DOUBLE_FLAG of class  DF::Config */
static int tolua_get_DF__Config_DOUBLE_FLAG(lua_State* tolua_S)
{
 tolua_pushnumber(tolua_S,(lua_Number)DF::Config::DOUBLE_FLAG);
 return 1;
}

/* get function: SEND_BLOCK_SIZE of class  DF::Config */
static int tolua_get_DF__Config_unsigned_SEND_BLOCK_SIZE(lua_State* tolua_S)
{
 tolua_pushnumber(tolua_S,(lua_Number)DF::Config::SEND_BLOCK_SIZE);
 return 1;
}

/* set function: SEND_BLOCK_SIZE of class  DF::Config */
static int tolua_set_DF__Config_unsigned_SEND_BLOCK_SIZE(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  DF::Config::SEND_BLOCK_SIZE = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}

/* get function: SEND_BLOCK_NUM of class  DF::Config */
static int tolua_get_DF__Config_unsigned_SEND_BLOCK_NUM(lua_State* tolua_S)
{
 tolua_pushnumber(tolua_S,(lua_Number)DF::Config::SEND_BLOCK_NUM);
 return 1;
}

/* set function: SEND_BLOCK_NUM of class  DF::Config */
static int tolua_set_DF__Config_unsigned_SEND_BLOCK_NUM(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  DF::Config::SEND_BLOCK_NUM = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}

/* get function: RECV_BLOCK_SIZE of class  DF::Config */
static int tolua_get_DF__Config_unsigned_RECV_BLOCK_SIZE(lua_State* tolua_S)
{
 tolua_pushnumber(tolua_S,(lua_Number)DF::Config::RECV_BLOCK_SIZE);
 return 1;
}

/* set function: RECV_BLOCK_SIZE of class  DF::Config */
static int tolua_set_DF__Config_unsigned_RECV_BLOCK_SIZE(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  DF::Config::RECV_BLOCK_SIZE = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}

/* get function: RECV_BLOCK_NUM of class  DF::Config */
static int tolua_get_DF__Config_unsigned_RECV_BLOCK_NUM(lua_State* tolua_S)
{
 tolua_pushnumber(tolua_S,(lua_Number)DF::Config::RECV_BLOCK_NUM);
 return 1;
}

/* set function: RECV_BLOCK_NUM of class  DF::Config */
static int tolua_set_DF__Config_unsigned_RECV_BLOCK_NUM(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  DF::Config::RECV_BLOCK_NUM = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}

/* get function: MSG_MAX_SIZE of class  DF::Config */
static int tolua_get_DF__Config_unsigned_MSG_MAX_SIZE(lua_State* tolua_S)
{
 tolua_pushnumber(tolua_S,(lua_Number)DF::Config::MSG_MAX_SIZE);
 return 1;
}

/* set function: MSG_MAX_SIZE of class  DF::Config */
static int tolua_set_DF__Config_unsigned_MSG_MAX_SIZE(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  DF::Config::MSG_MAX_SIZE = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}

/* get function: MSG_BASE_SIZE of class  DF::Config */
static int tolua_get_DF__Config_unsigned_MSG_BASE_SIZE(lua_State* tolua_S)
{
 tolua_pushnumber(tolua_S,(lua_Number)DF::Config::MSG_BASE_SIZE);
 return 1;
}

/* set function: MSG_BASE_SIZE of class  DF::Config */
static int tolua_set_DF__Config_unsigned_MSG_BASE_SIZE(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  DF::Config::MSG_BASE_SIZE = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}

/* get function: MAX_PACK_SIZE of class  DF::Config */
static int tolua_get_DF__Config_unsigned_MAX_PACK_SIZE(lua_State* tolua_S)
{
 tolua_pushnumber(tolua_S,(lua_Number)DF::Config::MAX_PACK_SIZE);
 return 1;
}

/* set function: MAX_PACK_SIZE of class  DF::Config */
static int tolua_set_DF__Config_unsigned_MAX_PACK_SIZE(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  DF::Config::MAX_PACK_SIZE = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}

/* get function: MAX_CONNECT of class  DF::Config */
static int tolua_get_DF__Config_unsigned_MAX_CONNECT(lua_State* tolua_S)
{
 tolua_pushnumber(tolua_S,(lua_Number)DF::Config::MAX_CONNECT);
 return 1;
}

/* set function: MAX_CONNECT of class  DF::Config */
static int tolua_set_DF__Config_unsigned_MAX_CONNECT(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  DF::Config::MAX_CONNECT = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}

/* get function: MAX_THREAD of class  DF::Config */
static int tolua_get_DF__Config_unsigned_MAX_THREAD(lua_State* tolua_S)
{
 tolua_pushnumber(tolua_S,(lua_Number)DF::Config::MAX_THREAD);
 return 1;
}

/* set function: MAX_THREAD of class  DF::Config */
static int tolua_set_DF__Config_unsigned_MAX_THREAD(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  DF::Config::MAX_THREAD = ((short)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}

/* get function: DEFAULT_PORT of class  DF::Config */
static int tolua_get_DF__Config_unsigned_DEFAULT_PORT(lua_State* tolua_S)
{
 tolua_pushnumber(tolua_S,(lua_Number)DF::Config::DEFAULT_PORT);
 return 1;
}

/* set function: DEFAULT_PORT of class  DF::Config */
static int tolua_set_DF__Config_unsigned_DEFAULT_PORT(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  DF::Config::DEFAULT_PORT = ((short)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}

/* get function: DATA_BASE_PORT of class  DF::Config */
static int tolua_get_DF__Config_unsigned_DATA_BASE_PORT(lua_State* tolua_S)
{
 tolua_pushnumber(tolua_S,(lua_Number)DF::Config::DATA_BASE_PORT);
 return 1;
}

/* set function: DATA_BASE_PORT of class  DF::Config */
static int tolua_set_DF__Config_unsigned_DATA_BASE_PORT(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  DF::Config::DATA_BASE_PORT = ((short)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}

/* method: year of class  DF::DateTime */
static int tolua_DFLuaServerLib_DF_DateTime_year00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const DF::DateTime",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const DF::DateTime* self = (const DF::DateTime*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'year'",NULL);
#endif
 {
  unsigned int tolua_ret = (unsigned int)  self->year();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'year'.",&tolua_err);
 return 0;
#endif
}

/* method: month of class  DF::DateTime */
static int tolua_DFLuaServerLib_DF_DateTime_month00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const DF::DateTime",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const DF::DateTime* self = (const DF::DateTime*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'month'",NULL);
#endif
 {
  unsigned int tolua_ret = (unsigned int)  self->month();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'month'.",&tolua_err);
 return 0;
#endif
}

/* method: day of class  DF::DateTime */
static int tolua_DFLuaServerLib_DF_DateTime_day00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const DF::DateTime",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const DF::DateTime* self = (const DF::DateTime*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'day'",NULL);
#endif
 {
  unsigned int tolua_ret = (unsigned int)  self->day();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'day'.",&tolua_err);
 return 0;
#endif
}

/* method: hour of class  DF::DateTime */
static int tolua_DFLuaServerLib_DF_DateTime_hour00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const DF::DateTime",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const DF::DateTime* self = (const DF::DateTime*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'hour'",NULL);
#endif
 {
  unsigned int tolua_ret = (unsigned int)  self->hour();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'hour'.",&tolua_err);
 return 0;
#endif
}

/* method: minute of class  DF::DateTime */
static int tolua_DFLuaServerLib_DF_DateTime_minute00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const DF::DateTime",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const DF::DateTime* self = (const DF::DateTime*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'minute'",NULL);
#endif
 {
  unsigned int tolua_ret = (unsigned int)  self->minute();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'minute'.",&tolua_err);
 return 0;
#endif
}

/* method: second of class  DF::DateTime */
static int tolua_DFLuaServerLib_DF_DateTime_second00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const DF::DateTime",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const DF::DateTime* self = (const DF::DateTime*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'second'",NULL);
#endif
 {
  unsigned int tolua_ret = (unsigned int)  self->second();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'second'.",&tolua_err);
 return 0;
#endif
}

/* method: milliseSecond of class  DF::DateTime */
static int tolua_DFLuaServerLib_DF_DateTime_milliseSecond00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const DF::DateTime",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const DF::DateTime* self = (const DF::DateTime*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'milliseSecond'",NULL);
#endif
 {
  unsigned int tolua_ret = (unsigned int)  self->milliseSecond();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'milliseSecond'.",&tolua_err);
 return 0;
#endif
}

/* method: days of class  DF::DateTime */
static int tolua_DFLuaServerLib_DF_DateTime_days00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const DF::DateTime",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const DF::DateTime* self = (const DF::DateTime*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'days'",NULL);
#endif
 {
  unsigned int tolua_ret = (unsigned int)  self->days();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'days'.",&tolua_err);
 return 0;
#endif
}

/* method: weeks of class  DF::DateTime */
static int tolua_DFLuaServerLib_DF_DateTime_weeks00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const DF::DateTime",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const DF::DateTime* self = (const DF::DateTime*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'weeks'",NULL);
#endif
 {
  unsigned int tolua_ret = (unsigned int)  self->weeks();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'weeks'.",&tolua_err);
 return 0;
#endif
}

/* method: months of class  DF::DateTime */
static int tolua_DFLuaServerLib_DF_DateTime_months00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const DF::DateTime",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const DF::DateTime* self = (const DF::DateTime*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'months'",NULL);
#endif
 {
  unsigned int tolua_ret = (unsigned int)  self->months();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'months'.",&tolua_err);
 return 0;
#endif
}

/* method: yearDay of class  DF::DateTime */
static int tolua_DFLuaServerLib_DF_DateTime_yearDay00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const DF::DateTime",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const DF::DateTime* self = (const DF::DateTime*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'yearDay'",NULL);
#endif
 {
  unsigned int tolua_ret = (unsigned int)  self->yearDay();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'yearDay'.",&tolua_err);
 return 0;
#endif
}

/* method: monthDay of class  DF::DateTime */
static int tolua_DFLuaServerLib_DF_DateTime_monthDay00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const DF::DateTime",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const DF::DateTime* self = (const DF::DateTime*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'monthDay'",NULL);
#endif
 {
  unsigned int tolua_ret = (unsigned int)  self->monthDay();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'monthDay'.",&tolua_err);
 return 0;
#endif
}

/* method: weekDay of class  DF::DateTime */
static int tolua_DFLuaServerLib_DF_DateTime_weekDay00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const DF::DateTime",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const DF::DateTime* self = (const DF::DateTime*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'weekDay'",NULL);
#endif
 {
  unsigned int tolua_ret = (unsigned int)  self->weekDay();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'weekDay'.",&tolua_err);
 return 0;
#endif
}

/* method: seconds of class  DF::DateTime */
static int tolua_DFLuaServerLib_DF_DateTime_seconds00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const DF::DateTime",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const DF::DateTime* self = (const DF::DateTime*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'seconds'",NULL);
#endif
 {
  unsigned int tolua_ret = (unsigned int)  self->seconds();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'seconds'.",&tolua_err);
 return 0;
#endif
}

/* method: getUnixTime of class  DF::DateTime */
static int tolua_DFLuaServerLib_DF_DateTime_getUnixTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const DF::DateTime",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const DF::DateTime* self = (const DF::DateTime*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getUnixTime'",NULL);
#endif
 {
  unsigned int tolua_ret = (unsigned int)  self->getUnixTime();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getUnixTime'.",&tolua_err);
 return 0;
#endif
}

/* method: timeZoneSeconds of class  DF::DateTime */
static int tolua_DFLuaServerLib_DF_DateTime_timeZoneSeconds00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"DF::DateTime",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  DF::DateTime* self = (DF::DateTime*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'timeZoneSeconds'",NULL);
#endif
 {
  unsigned int tolua_ret = (unsigned int)  self->timeZoneSeconds();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'timeZoneSeconds'.",&tolua_err);
 return 0;
#endif
}

/* method: setUnixTime of class  DF::DateTime */
static int tolua_DFLuaServerLib_DF_DateTime_setUnixTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"DF::DateTime",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  DF::DateTime* self = (DF::DateTime*)  tolua_tousertype(tolua_S,1,0);
  unsigned int uUnixTime = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setUnixTime'",NULL);
#endif
 {
  self->setUnixTime(uUnixTime);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setUnixTime'.",&tolua_err);
 return 0;
#endif
}

/* method: setTimeSpeed of class  DF::DateTime */
static int tolua_DFLuaServerLib_DF_DateTime_setTimeSpeed00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"DF::DateTime",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  DF::DateTime* self = (DF::DateTime*)  tolua_tousertype(tolua_S,1,0);
  unsigned int uTimeSpeed = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTimeSpeed'",NULL);
#endif
 {
  self->setTimeSpeed(uTimeSpeed);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTimeSpeed'.",&tolua_err);
 return 0;
#endif
}

/* method: getSize of class  DF::MessageBase */
static int tolua_DFLuaServerLib_DF_MessageBase_getSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const DF::MessageBase",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const DF::MessageBase* self = (const DF::MessageBase*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getSize'",NULL);
#endif
 {
  unsigned short tolua_ret = (unsigned short)  self->getSize();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getSize'.",&tolua_err);
 return 0;
#endif
}

/* method: setSize of class  DF::MessageBase */
static int tolua_DFLuaServerLib_DF_MessageBase_setSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"DF::MessageBase",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  DF::MessageBase* self = (DF::MessageBase*)  tolua_tousertype(tolua_S,1,0);
  unsigned short uSize = ((unsigned short)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setSize'",NULL);
#endif
 {
  self->setSize(uSize);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setSize'.",&tolua_err);
 return 0;
#endif
}

/* method: addSize of class  DF::MessageBase */
static int tolua_DFLuaServerLib_DF_MessageBase_addSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"DF::MessageBase",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  DF::MessageBase* self = (DF::MessageBase*)  tolua_tousertype(tolua_S,1,0);
  unsigned short uSize = ((unsigned short)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addSize'",NULL);
#endif
 {
  self->addSize(uSize);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addSize'.",&tolua_err);
 return 0;
#endif
}

/* method: getType of class  DF::MessageBase */
static int tolua_DFLuaServerLib_DF_MessageBase_getType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const DF::MessageBase",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const DF::MessageBase* self = (const DF::MessageBase*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getType'",NULL);
#endif
 {
  unsigned short tolua_ret = (unsigned short)  self->getType();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getType'.",&tolua_err);
 return 0;
#endif
}

/* method: getBody of class  DF::MessageBase */
static int tolua_DFLuaServerLib_DF_MessageBase_getBody00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"DF::MessageBase",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  DF::MessageBase* self = (DF::MessageBase*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getBody'",NULL);
#endif
 {
  void* tolua_ret = (void*)  self->getBody();
 tolua_pushuserdata(tolua_S,(void*)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getBody'.",&tolua_err);
 return 0;
#endif
}

/* method: getBodySize of class  DF::MessageBase */
static int tolua_DFLuaServerLib_DF_MessageBase_getBodySize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const DF::MessageBase",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const DF::MessageBase* self = (const DF::MessageBase*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getBodySize'",NULL);
#endif
 {
  unsigned short tolua_ret = (unsigned short)  self->getBodySize();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getBodySize'.",&tolua_err);
 return 0;
#endif
}

/* method: align of class  DF::MessageBase */
static int tolua_DFLuaServerLib_DF_MessageBase_align00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"DF::MessageBase",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  DF::MessageBase* self = (DF::MessageBase*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'align'",NULL);
#endif
 {
  self->align();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'align'.",&tolua_err);
 return 0;
#endif
}

/* method: packType of class  DF::PackMessage */
static int tolua_DFLuaServerLib_DF_PackMessage_packType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"DF::PackMessage",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  DF::PackMessage* self = (DF::PackMessage*)  tolua_tousertype(tolua_S,1,0);
  unsigned short uType = ((unsigned short)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'packType'",NULL);
#endif
 {
  self->packType(uType);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'packType'.",&tolua_err);
 return 0;
#endif
}

/* method: packMsg of class  DF::PackMessage */
static int tolua_DFLuaServerLib_DF_PackMessage_packMsg00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"DF::PackMessage",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"DF::MessageBase",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  DF::PackMessage* self = (DF::PackMessage*)  tolua_tousertype(tolua_S,1,0);
  DF::MessageBase* pMsg = ((DF::MessageBase*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'packMsg'",NULL);
#endif
 {
  self->packMsg(pMsg);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'packMsg'.",&tolua_err);
 return 0;
#endif
}

/* method: packBytes of class  DF::PackMessage */
static int tolua_DFLuaServerLib_DF_PackMessage_packBytes00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"DF::PackMessage",0,&tolua_err) ||
 !tolua_isstring(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  DF::PackMessage* self = (DF::PackMessage*)  tolua_tousertype(tolua_S,1,0);
  char* pHead = ((char*)  tolua_tostring(tolua_S,2,0));
  unsigned short uSize = ((unsigned short)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'packBytes'",NULL);
#endif
 {
  self->packBytes(pHead,uSize);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'packBytes'.",&tolua_err);
 return 0;
#endif
}

/* method: packInt8 of class  DF::PackMessage */
static int tolua_DFLuaServerLib_DF_PackMessage_packInt800(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"DF::PackMessage",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  DF::PackMessage* self = (DF::PackMessage*)  tolua_tousertype(tolua_S,1,0);
  char i8 = ((char)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'packInt8'",NULL);
#endif
 {
  self->packInt8(i8);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'packInt8'.",&tolua_err);
 return 0;
#endif
}

/* method: packInt16 of class  DF::PackMessage */
static int tolua_DFLuaServerLib_DF_PackMessage_packInt1600(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"DF::PackMessage",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  DF::PackMessage* self = (DF::PackMessage*)  tolua_tousertype(tolua_S,1,0);
  short i16 = ((short)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'packInt16'",NULL);
#endif
 {
  self->packInt16(i16);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'packInt16'.",&tolua_err);
 return 0;
#endif
}

/* method: packInt32 of class  DF::PackMessage */
static int tolua_DFLuaServerLib_DF_PackMessage_packInt3200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"DF::PackMessage",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  DF::PackMessage* self = (DF::PackMessage*)  tolua_tousertype(tolua_S,1,0);
  int i32 = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'packInt32'",NULL);
#endif
 {
  self->packInt32(i32);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'packInt32'.",&tolua_err);
 return 0;
#endif
}

/* method: packUint8 of class  DF::PackMessage */
static int tolua_DFLuaServerLib_DF_PackMessage_packUint800(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"DF::PackMessage",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  DF::PackMessage* self = (DF::PackMessage*)  tolua_tousertype(tolua_S,1,0);
  unsigned char ui8 = ((unsigned char)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'packUint8'",NULL);
#endif
 {
  self->packUint8(ui8);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'packUint8'.",&tolua_err);
 return 0;
#endif
}

/* method: packUint16 of class  DF::PackMessage */
static int tolua_DFLuaServerLib_DF_PackMessage_packUint1600(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"DF::PackMessage",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  DF::PackMessage* self = (DF::PackMessage*)  tolua_tousertype(tolua_S,1,0);
  unsigned short ui16 = ((unsigned short)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'packUint16'",NULL);
#endif
 {
  self->packUint16(ui16);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'packUint16'.",&tolua_err);
 return 0;
#endif
}

/* method: packUint32 of class  DF::PackMessage */
static int tolua_DFLuaServerLib_DF_PackMessage_packUint3200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"DF::PackMessage",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  DF::PackMessage* self = (DF::PackMessage*)  tolua_tousertype(tolua_S,1,0);
  unsigned int ui32 = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'packUint32'",NULL);
#endif
 {
  self->packUint32(ui32);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'packUint32'.",&tolua_err);
 return 0;
#endif
}

/* method: packFloat of class  DF::PackMessage */
static int tolua_DFLuaServerLib_DF_PackMessage_packFloat00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"DF::PackMessage",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  DF::PackMessage* self = (DF::PackMessage*)  tolua_tousertype(tolua_S,1,0);
  float f = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'packFloat'",NULL);
#endif
 {
  self->packFloat(f);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'packFloat'.",&tolua_err);
 return 0;
#endif
}

/* method: packDouble of class  DF::PackMessage */
static int tolua_DFLuaServerLib_DF_PackMessage_packDouble00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"DF::PackMessage",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  DF::PackMessage* self = (DF::PackMessage*)  tolua_tousertype(tolua_S,1,0);
  double d = ((double)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'packDouble'",NULL);
#endif
 {
  self->packDouble(d);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'packDouble'.",&tolua_err);
 return 0;
#endif
}

/* method: packValue of class  DF::PackMessage */
static int tolua_DFLuaServerLib_DF_PackMessage_packValue00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"DF::PackMessage",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  DF::PackMessage* self = (DF::PackMessage*)  tolua_tousertype(tolua_S,1,0);
  double d = ((double)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'packValue'",NULL);
#endif
 {
  self->packValue(d);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'packValue'.",&tolua_err);
 return 0;
#endif
}

/* method: packInt of class  DF::PackMessage */
static int tolua_DFLuaServerLib_DF_PackMessage_packInt00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"DF::PackMessage",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  DF::PackMessage* self = (DF::PackMessage*)  tolua_tousertype(tolua_S,1,0);
  int d = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'packInt'",NULL);
#endif
 {
  self->packInt(d);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'packInt'.",&tolua_err);
 return 0;
#endif
}

/* method: packDict of class  DF::PackMessage */
static int tolua_DFLuaServerLib_DF_PackMessage_packDict00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"DF::PackMessage",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  DF::PackMessage* self = (DF::PackMessage*)  tolua_tousertype(tolua_S,1,0);
  unsigned short uSize = ((unsigned short)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'packDict'",NULL);
#endif
 {
  self->packDict(uSize);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'packDict'.",&tolua_err);
 return 0;
#endif
}

/* method: packString of class  DF::PackMessage */
static int tolua_DFLuaServerLib_DF_PackMessage_packString00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"DF::PackMessage",0,&tolua_err) ||
 !tolua_isstring(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  DF::PackMessage* self = (DF::PackMessage*)  tolua_tousertype(tolua_S,1,0);
  const char* v = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'packString'",NULL);
#endif
 {
  self->packString(v);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'packString'.",&tolua_err);
 return 0;
#endif
}

/* method: packObject of class  DF::PackMessage */
static int tolua_DFLuaServerLib_DF_PackMessage_packObject00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"DF::PackMessage",0,&tolua_err) ||
!tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  DF::PackMessage* self = (DF::PackMessage*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'packObject'",NULL);
#endif
 {
  self->packObject();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'packObject'.",&tolua_err);
 return 0;
#endif
}

/* method: getIsOK of class  DF::PackMessage */
static int tolua_DFLuaServerLib_DF_PackMessage_getIsOK00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const DF::PackMessage",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const DF::PackMessage* self = (const DF::PackMessage*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getIsOK'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->getIsOK();
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getIsOK'.",&tolua_err);
 return 0;
#endif
}

/* method: getTotalBodySize of class  DF::PackMessage */
static int tolua_DFLuaServerLib_DF_PackMessage_getTotalBodySize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const DF::PackMessage",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const DF::PackMessage* self = (const DF::PackMessage*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTotalBodySize'",NULL);
#endif
 {
  unsigned int tolua_ret = (unsigned int)  self->getTotalBodySize();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTotalBodySize'.",&tolua_err);
 return 0;
#endif
}

/* method: getCurrentEmptySize of class  DF::PackMessage */
static int tolua_DFLuaServerLib_DF_PackMessage_getCurrentEmptySize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const DF::PackMessage",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const DF::PackMessage* self = (const DF::PackMessage*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getCurrentEmptySize'",NULL);
#endif
 {
  unsigned int tolua_ret = (unsigned int)  self->getCurrentEmptySize();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getCurrentEmptySize'.",&tolua_err);
 return 0;
#endif
}

/* method: getMsg of class  DF::PackMessage */
static int tolua_DFLuaServerLib_DF_PackMessage_getMsg00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const DF::PackMessage",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const DF::PackMessage* self = (const DF::PackMessage*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getMsg'",NULL);
#endif
 {
  DF::MessageBase* tolua_ret = (DF::MessageBase*)  self->getMsg();
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"DF::MessageBase");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getMsg'.",&tolua_err);
 return 0;
#endif
}

/* method: reset of class  DF::UnpackMessage */
static int tolua_DFLuaServerLib_DF_UnpackMessage_reset00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"DF::UnpackMessage",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"DF::MessageBase",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  DF::UnpackMessage* self = (DF::UnpackMessage*)  tolua_tousertype(tolua_S,1,0);
  DF::MessageBase* pMsg = ((DF::MessageBase*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'reset'",NULL);
#endif
 {
  self->reset(pMsg);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'reset'.",&tolua_err);
 return 0;
#endif
}

/* method: unpackMsg of class  DF::UnpackMessage */
static int tolua_DFLuaServerLib_DF_UnpackMessage_unpackMsg00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"DF::UnpackMessage",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  DF::UnpackMessage* self = (DF::UnpackMessage*)  tolua_tousertype(tolua_S,1,0);
  unsigned int uSize = ((unsigned int)  tolua_tonumber(tolua_S,2,4));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'unpackMsg'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->unpackMsg(uSize);
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'unpackMsg'.",&tolua_err);
 return 0;
#endif
}

/* method: unpackInt8 of class  DF::UnpackMessage */
static int tolua_DFLuaServerLib_DF_UnpackMessage_unpackInt800(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"DF::UnpackMessage",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  DF::UnpackMessage* self = (DF::UnpackMessage*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'unpackInt8'",NULL);
#endif
 {
  char tolua_ret = (char)  self->unpackInt8();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'unpackInt8'.",&tolua_err);
 return 0;
#endif
}

/* method: unpackInt16 of class  DF::UnpackMessage */
static int tolua_DFLuaServerLib_DF_UnpackMessage_unpackInt1600(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"DF::UnpackMessage",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  DF::UnpackMessage* self = (DF::UnpackMessage*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'unpackInt16'",NULL);
#endif
 {
  short tolua_ret = (short)  self->unpackInt16();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'unpackInt16'.",&tolua_err);
 return 0;
#endif
}

/* method: unpackInt32 of class  DF::UnpackMessage */
static int tolua_DFLuaServerLib_DF_UnpackMessage_unpackInt3200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"DF::UnpackMessage",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  DF::UnpackMessage* self = (DF::UnpackMessage*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'unpackInt32'",NULL);
#endif
 {
  int tolua_ret = (int)  self->unpackInt32();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'unpackInt32'.",&tolua_err);
 return 0;
#endif
}

/* method: unpackUint8 of class  DF::UnpackMessage */
static int tolua_DFLuaServerLib_DF_UnpackMessage_unpackUint800(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"DF::UnpackMessage",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  DF::UnpackMessage* self = (DF::UnpackMessage*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'unpackUint8'",NULL);
#endif
 {
  unsigned char tolua_ret = (unsigned char)  self->unpackUint8();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'unpackUint8'.",&tolua_err);
 return 0;
#endif
}

/* method: unpackUint16 of class  DF::UnpackMessage */
static int tolua_DFLuaServerLib_DF_UnpackMessage_unpackUint1600(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"DF::UnpackMessage",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  DF::UnpackMessage* self = (DF::UnpackMessage*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'unpackUint16'",NULL);
#endif
 {
  unsigned short tolua_ret = (unsigned short)  self->unpackUint16();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'unpackUint16'.",&tolua_err);
 return 0;
#endif
}

/* method: unpackUint32 of class  DF::UnpackMessage */
static int tolua_DFLuaServerLib_DF_UnpackMessage_unpackUint3200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"DF::UnpackMessage",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  DF::UnpackMessage* self = (DF::UnpackMessage*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'unpackUint32'",NULL);
#endif
 {
  unsigned int tolua_ret = (unsigned int)  self->unpackUint32();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'unpackUint32'.",&tolua_err);
 return 0;
#endif
}

/* method: unpackFloat of class  DF::UnpackMessage */
static int tolua_DFLuaServerLib_DF_UnpackMessage_unpackFloat00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"DF::UnpackMessage",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  DF::UnpackMessage* self = (DF::UnpackMessage*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'unpackFloat'",NULL);
#endif
 {
  float tolua_ret = (float)  self->unpackFloat();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'unpackFloat'.",&tolua_err);
 return 0;
#endif
}

/* method: unpackDouble of class  DF::UnpackMessage */
static int tolua_DFLuaServerLib_DF_UnpackMessage_unpackDouble00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"DF::UnpackMessage",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  DF::UnpackMessage* self = (DF::UnpackMessage*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'unpackDouble'",NULL);
#endif
 {
  double tolua_ret = (double)  self->unpackDouble();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'unpackDouble'.",&tolua_err);
 return 0;
#endif
}

/* method: unpackValue of class  DF::UnpackMessage */
static int tolua_DFLuaServerLib_DF_UnpackMessage_unpackValue00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"DF::UnpackMessage",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  DF::UnpackMessage* self = (DF::UnpackMessage*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'unpackValue'",NULL);
#endif
 {
  double tolua_ret = (double)  self->unpackValue();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'unpackValue'.",&tolua_err);
 return 0;
#endif
}

/* method: unpackStream of class  DF::UnpackMessage */
static int tolua_DFLuaServerLib_DF_UnpackMessage_unpackStream00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"DF::UnpackMessage",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  DF::UnpackMessage* self = (DF::UnpackMessage*)  tolua_tousertype(tolua_S,1,0);
  unsigned short uSize = ((unsigned short)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'unpackStream'",NULL);
#endif
 {
  char* tolua_ret = (char*)  self->unpackStream(uSize);
 tolua_pushstring(tolua_S,(const char*)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'unpackStream'.",&tolua_err);
 return 0;
#endif
}

/* method: unpackString of class  DF::UnpackMessage */
static int tolua_DFLuaServerLib_DF_UnpackMessage_unpackString00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"DF::UnpackMessage",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  DF::UnpackMessage* self = (DF::UnpackMessage*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'unpackString'",NULL);
#endif
 {
  const char* tolua_ret = (const char*)  self->unpackString();
 tolua_pushstring(tolua_S,(const char*)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'unpackString'.",&tolua_err);
 return 0;
#endif
}

/* method: getUnpackFence of class  DF::UnpackMessage */
static int tolua_DFLuaServerLib_DF_UnpackMessage_getUnpackFence00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"DF::UnpackMessage",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  DF::UnpackMessage* self = (DF::UnpackMessage*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getUnpackFence'",NULL);
#endif
 {
  char* tolua_ret = (char*)  self->getUnpackFence();
 tolua_pushstring(tolua_S,(const char*)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getUnpackFence'.",&tolua_err);
 return 0;
#endif
}

/* method: getSurplusSize of class  DF::UnpackMessage */
static int tolua_DFLuaServerLib_DF_UnpackMessage_getSurplusSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"DF::UnpackMessage",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  DF::UnpackMessage* self = (DF::UnpackMessage*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getSurplusSize'",NULL);
#endif
 {
  unsigned int tolua_ret = (unsigned int)  self->getSurplusSize();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getSurplusSize'.",&tolua_err);
 return 0;
#endif
}

/* method: getIsOk of class  DF::UnpackMessage */
static int tolua_DFLuaServerLib_DF_UnpackMessage_getIsOk00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"DF::UnpackMessage",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  DF::UnpackMessage* self = (DF::UnpackMessage*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getIsOk'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->getIsOk();
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getIsOk'.",&tolua_err);
 return 0;
#endif
}

/* method: unpackObject of class  DF::UnpackMessage */
static int tolua_DFLuaServerLib_DF_UnpackMessage_unpackObject00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"DF::UnpackMessage",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  DF::UnpackMessage* self = (DF::UnpackMessage*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'unpackObject'",NULL);
#endif
 {
  self->unpackObject();
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'unpackObject'.",&tolua_err);
 return 1;
#endif
}

/* method: instancePtr of class  DF::LuaSystem */
static int tolua_DFLuaServerLib_DF_LuaSystem_instancePtr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"DF::LuaSystem",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
 {
  DF::LuaSystem* tolua_ret = (DF::LuaSystem*)  DF::LuaSystem::instancePtr();
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"DF::LuaSystem");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'instancePtr'.",&tolua_err);
 return 0;
#endif
}

/* method: setDebug of class  DF::LuaSystem */
static int tolua_DFLuaServerLib_DF_LuaSystem_setDebug00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"DF::LuaSystem",0,&tolua_err) ||
 !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  DF::LuaSystem* self = (DF::LuaSystem*)  tolua_tousertype(tolua_S,1,0);
  bool bDebug = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setDebug'",NULL);
#endif
 {
  self->setDebug(bDebug);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setDebug'.",&tolua_err);
 return 0;
#endif
}

/* method: doString of class  DF::LuaSystem */
static int tolua_DFLuaServerLib_DF_LuaSystem_doString00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"DF::LuaSystem",0,&tolua_err) ||
 !tolua_isstring(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  DF::LuaSystem* self = (DF::LuaSystem*)  tolua_tousertype(tolua_S,1,0);
  const char* pStr = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'doString'",NULL);
#endif
 {
  self->doString(pStr);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'doString'.",&tolua_err);
 return 0;
#endif
}

/* method: doFile of class  DF::LuaSystem */
static int tolua_DFLuaServerLib_DF_LuaSystem_doFile00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"DF::LuaSystem",0,&tolua_err) ||
 !tolua_isstring(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  DF::LuaSystem* self = (DF::LuaSystem*)  tolua_tousertype(tolua_S,1,0);
  const char* sFileName = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'doFile'",NULL);
#endif
 {
  self->doFile(sFileName);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'doFile'.",&tolua_err);
 return 0;
#endif
}

/* method: reload of class  DF::LuaSystem */
static int tolua_DFLuaServerLib_DF_LuaSystem_reload00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"DF::LuaSystem",0,&tolua_err) ||
 !tolua_isstring(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  DF::LuaSystem* self = (DF::LuaSystem*)  tolua_tousertype(tolua_S,1,0);
  const char* sModuleFileName = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'reload'",NULL);
#endif
 {
  self->reload(sModuleFileName);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'reload'.",&tolua_err);
 return 0;
#endif
}

/* method: enableReturn of class  DF::LuaSystem */
static int tolua_DFLuaServerLib_DF_LuaSystem_enableReturn00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"DF::LuaSystem",0,&tolua_err) ||
 !tolua_isstring(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  DF::LuaSystem* self = (DF::LuaSystem*)  tolua_tousertype(tolua_S,1,0);
  const char* file = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'enableReturn'",NULL);
#endif
 {
  self->enableReturn(file);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'enableReturn'.",&tolua_err);
 return 0;
#endif
}

/* method: disableReturn of class  DF::LuaSystem */
static int tolua_DFLuaServerLib_DF_LuaSystem_disableReturn00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"DF::LuaSystem",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  DF::LuaSystem* self = (DF::LuaSystem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'disableReturn'",NULL);
#endif
 {
  self->disableReturn();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'disableReturn'.",&tolua_err);
 return 0;
#endif
}

/* method: getRootPath of class  DF::LuaSystem */
static int tolua_DFLuaServerLib_DF_LuaSystem_getRootPath00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const DF::LuaSystem",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const DF::LuaSystem* self = (const DF::LuaSystem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getRootPath'",NULL);
#endif
 {
  const char* tolua_ret = (const char*)  self->getRootPath();
 tolua_pushstring(tolua_S,(const char*)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getRootPath'.",&tolua_err);
 return 0;
#endif
}

/* method: setIsRunScriptMsg of class  DF::LuaSystem */
static int tolua_DFLuaServerLib_DF_LuaSystem_setIsRunScriptMsg00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"DF::LuaSystem",0,&tolua_err) ||
 !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  DF::LuaSystem* self = (DF::LuaSystem*)  tolua_tousertype(tolua_S,1,0);
  bool isRunScriptMsg = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setIsRunScriptMsg'",NULL);
#endif
 {
  self->setIsRunScriptMsg(isRunScriptMsg);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setIsRunScriptMsg'.",&tolua_err);
 return 0;
#endif
}

/* method: getRunScirptPrint of class  DF::LuaSystem */
static int tolua_DFLuaServerLib_DF_LuaSystem_getRunScirptPrint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const DF::LuaSystem",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const DF::LuaSystem* self = (const DF::LuaSystem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getRunScirptPrint'",NULL);
#endif
 {
  const char* tolua_ret = (const char*)  self->getRunScirptPrint();
 tolua_pushstring(tolua_S,(const char*)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getRunScirptPrint'.",&tolua_err);
 return 0;
#endif
}

/* method: loadFiles of class  DF::LuaSystem */
static int tolua_DFLuaServerLib_DF_LuaSystem_loadFiles00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"DF::LuaSystem",0,&tolua_err) ||
 !tolua_isstring(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  DF::LuaSystem* self = (DF::LuaSystem*)  tolua_tousertype(tolua_S,1,0);
  const char* path = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'loadFiles'",NULL);
#endif
 {
  self->loadFiles(path);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'loadFiles'.",&tolua_err);
 return 1;
#endif
}

/* method: loadAllFiles of class  DF::LuaSystem */
static int tolua_DFLuaServerLib_DF_LuaSystem_loadAllFiles00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"DF::LuaSystem",0,&tolua_err) ||
 !tolua_isstring(tolua_S,2,0,&tolua_err) ||
 !tolua_isstring(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  DF::LuaSystem* self = (DF::LuaSystem*)  tolua_tousertype(tolua_S,1,0);
  const char* strFolderPath = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* curPath = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'loadAllFiles'",NULL);
#endif
 {
  self->loadAllFiles(strFolderPath,curPath);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'loadAllFiles'.",&tolua_err);
 return 1;
#endif
}

/* method: getServer of class  DF::LuaSystem */
static int tolua_DFLuaServerLib_DF_LuaSystem_getServer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const DF::LuaSystem",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const DF::LuaSystem* self = (const DF::LuaSystem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getServer'",NULL);
#endif
 {
  DF::BaseServer* tolua_ret = (DF::BaseServer*)  self->getServer();
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"DF::BaseServer");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getServer'.",&tolua_err);
 return 0;
#endif
}

/* method: clear of class  DF::LuaTrigger */
static int tolua_DFLuaServerLib_DF_LuaTrigger_clear00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"DF::LuaTrigger",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  DF::LuaTrigger* self = (DF::LuaTrigger*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'clear'",NULL);
#endif
 {
  self->clear();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'clear'.",&tolua_err);
 return 0;
#endif
}

/* method: triggering of class  DF::LuaTrigger */
static int tolua_DFLuaServerLib_DF_LuaTrigger_triggering00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"DF::LuaTrigger",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  DF::LuaTrigger* self = (DF::LuaTrigger*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'triggering'",NULL);
#endif
 {
  self->triggering();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'triggering'.",&tolua_err);
 return 0;
#endif
}

/* method: triggering of class  DF::LuaTrigger */
static int tolua_DFLuaServerLib_DF_LuaTrigger_triggering01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"DF::LuaTrigger",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"DF::MessageBase",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  DF::LuaTrigger* self = (DF::LuaTrigger*)  tolua_tousertype(tolua_S,1,0);
  DF::MessageBase* pMsg = ((DF::MessageBase*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'triggering'",NULL);
#endif
 {
  self->triggering(pMsg);
 }
 }
 return 0;
tolua_lerror:
 return tolua_DFLuaServerLib_DF_LuaTrigger_triggering00(tolua_S);
}

/* method: getID of class  DF::LuaTrigger */
static int tolua_DFLuaServerLib_DF_LuaTrigger_getID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const DF::LuaTrigger",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const DF::LuaTrigger* self = (const DF::LuaTrigger*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getID'",NULL);
#endif
 {
  unsigned int tolua_ret = (unsigned int)  self->getID();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getID'.",&tolua_err);
 return 0;
#endif
}

/* method: getType of class  DF::LuaTrigger */
static int tolua_DFLuaServerLib_DF_LuaTrigger_getType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"DF::LuaTrigger",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  DF::LuaTrigger* self = (DF::LuaTrigger*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getType'",NULL);
#endif
 {
  const char* tolua_ret = (const char*)  self->getType();
 tolua_pushstring(tolua_S,(const char*)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getType'.",&tolua_err);
 return 0;
#endif
}

/* method: pushFunction of class  DF::LuaTrigger */
static int tolua_DFLuaServerLib_DF_LuaTrigger_pushFunction00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"DF::LuaTrigger",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isusertype(tolua_S,3,"DF::LuaFunction",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  DF::LuaTrigger* self = (DF::LuaTrigger*)  tolua_tousertype(tolua_S,1,0);
  DF::LuaTrigger::LuaTriggerEnum funcEnum = ((DF::LuaTrigger::LuaTriggerEnum) (int)  tolua_tonumber(tolua_S,2,0));
  DF::LuaFunction* pfunc = ((DF::LuaFunction*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'pushFunction'",NULL);
#endif
 {
  self->pushFunction(funcEnum,pfunc);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'pushFunction'.",&tolua_err);
 return 0;
#endif
}

/* method: addToRootCallBack of class  DF::LuaTrigger */
static int tolua_DFLuaServerLib_DF_LuaTrigger_addToRootCallBack00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"DF::LuaTrigger",0,&tolua_err) ||
 !tolua_isstring(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  DF::LuaTrigger* self = (DF::LuaTrigger*)  tolua_tousertype(tolua_S,1,0);
  const char* sTag = ((const char*)  tolua_tostring(tolua_S,2,0));
  int iTag = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addToRootCallBack'",NULL);
#endif
 {
  self->addToRootCallBack(sTag,iTag);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addToRootCallBack'.",&tolua_err);
 return 0;
#endif
}

/* method: screate of class  DF::LuaTrigger */
static int tolua_DFLuaServerLib_DF_LuaTrigger_screate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"DF::LuaTrigger",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
 {
  DF::LuaTrigger* tolua_ret = (DF::LuaTrigger*)  DF::LuaTrigger::screate();
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"DF::LuaTrigger");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'screate'.",&tolua_err);
 return 0;
#endif
}

/* method: screate of class  DF::LuaFunction */
static int tolua_DFLuaServerLib_DF_LuaFunction_screate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"DF::LuaFunction",0,&tolua_err) ||
 !lua_isfunction(tolua_S, 2) ||
!tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
 {
  DF::LuaFunction* tolua_ret = (DF::LuaFunction*)  DF::LuaFunction::screate();
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"DF::LuaFunction");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'screate'.",&tolua_err);
 return 0;
#endif
}

/* method: screate of class  DF::LuaFunction */
static int tolua_DFLuaServerLib_DF_LuaFunction_screate01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"DF::LuaFunction",0,&tolua_err) ||
 !tolua_isstring(tolua_S,2,0,&tolua_err) ||
 !lua_isfunction(tolua_S, 3) ||
!tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  const char* sName = ((const char*)  tolua_tostring(tolua_S,2,0));
 {
  DF::LuaFunction* tolua_ret = (DF::LuaFunction*)  DF::LuaFunction::screate(sName);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"DF::LuaFunction");
 }
 }
 return 1;
tolua_lerror:
 return tolua_DFLuaServerLib_DF_LuaFunction_screate00(tolua_S);
}

/* method: isShutdown of class  DF::NetConnect */
static int tolua_DFLuaServerLib_DF_NetConnect_isShutdown00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const DF::NetConnect",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const DF::NetConnect* self = (const DF::NetConnect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isShutdown'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->isShutdown();
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isShutdown'.",&tolua_err);
 return 0;
#endif
}

/* method: getSessionID of class  DF::NetConnect */
static int tolua_DFLuaServerLib_DF_NetConnect_getSessionID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const DF::NetConnect",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const DF::NetConnect* self = (const DF::NetConnect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getSessionID'",NULL);
#endif
 {
  unsigned int tolua_ret = (unsigned int)  self->getSessionID();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getSessionID'.",&tolua_err);
 return 0;
#endif
}

/* method: getConnectTime of class  DF::NetConnect */
static int tolua_DFLuaServerLib_DF_NetConnect_getConnectTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const DF::NetConnect",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const DF::NetConnect* self = (const DF::NetConnect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getConnectTime'",NULL);
#endif
 {
  unsigned int tolua_ret = (unsigned int)  self->getConnectTime();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getConnectTime'.",&tolua_err);
 return 0;
#endif
}

/* method: getIP of class  DF::NetConnect */
static int tolua_DFLuaServerLib_DF_NetConnect_getIP00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const DF::NetConnect",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const DF::NetConnect* self = (const DF::NetConnect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getIP'",NULL);
#endif
 {
  const char* tolua_ret = (const char*)  self->getIP();
 tolua_pushstring(tolua_S,(const char*)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getIP'.",&tolua_err);
 return 0;
#endif
}

/* method: getPort of class  DF::NetConnect */
static int tolua_DFLuaServerLib_DF_NetConnect_getPort00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const DF::NetConnect",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const DF::NetConnect* self = (const DF::NetConnect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getPort'",NULL);
#endif
 {
  unsigned short tolua_ret = (unsigned short)  self->getPort();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getPort'.",&tolua_err);
 return 0;
#endif
}

/* method: getWho of class  DF::NetConnect */
static int tolua_DFLuaServerLib_DF_NetConnect_getWho00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const DF::NetConnect",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const DF::NetConnect* self = (const DF::NetConnect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getWho'",NULL);
#endif
 {
  unsigned int tolua_ret = (unsigned int)  self->getWho();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getWho'.",&tolua_err);
 return 0;
#endif
}

/* method: sendBytes of class  DF::NetConnect */
static int tolua_DFLuaServerLib_DF_NetConnect_sendBytes00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"DF::NetConnect",0,&tolua_err) ||
 !tolua_isstring(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  DF::NetConnect* self = (DF::NetConnect*)  tolua_tousertype(tolua_S,1,0);
  const char* pHead = ((const char*)  tolua_tostring(tolua_S,2,0));
  unsigned short uSize = ((unsigned short)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'sendBytes'",NULL);
#endif
 {
  self->sendBytes(pHead,uSize);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'sendBytes'.",&tolua_err);
 return 0;
#endif
}

/* method: execute of class  DF::DataBaseMySQL */
static int tolua_DFLuaServerLib_DF_DataBaseMySQL_execute00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"DF::DataBaseMySQL",0,&tolua_err) ||
 !tolua_isstring(tolua_S,2,0,&tolua_err) ||
 !tolua_isusertype(tolua_S,3,"DF::PackMessage",1,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  DF::DataBaseMySQL* self = (DF::DataBaseMySQL*)  tolua_tousertype(tolua_S,1,0);
  const char* sql = ((const char*)  tolua_tostring(tolua_S,2,0));
  DF::PackMessage* pPackMsg = ((DF::PackMessage*)  tolua_tousertype(tolua_S,3,NULL));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'execute'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->execute(sql,pPackMsg);
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'execute'.",&tolua_err);
 return 0;
#endif
}

/* method: executeStmt of class  DF::DataBaseMySQL */
static int tolua_DFLuaServerLib_DF_DataBaseMySQL_executeStmt00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"DF::DataBaseMySQL",0,&tolua_err) ||
 !tolua_isstring(tolua_S,2,0,&tolua_err) ||
 !tolua_isusertype(tolua_S,3,"DF::UnpackMessage",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  DF::DataBaseMySQL* self = (DF::DataBaseMySQL*)  tolua_tousertype(tolua_S,1,0);
  const char* sql = ((const char*)  tolua_tostring(tolua_S,2,0));
  DF::UnpackMessage* unpack = ((DF::UnpackMessage*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'executeStmt'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->executeStmt(sql,unpack);
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'executeStmt'.",&tolua_err);
 return 0;
#endif
}

/* method: initStmt of class  DF::DataBaseMySQL */
static int tolua_DFLuaServerLib_DF_DataBaseMySQL_initStmt00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"DF::DataBaseMySQL",0,&tolua_err) ||
 !tolua_isstring(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  DF::DataBaseMySQL* self = (DF::DataBaseMySQL*)  tolua_tousertype(tolua_S,1,0);
  const char* sql = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'initStmt'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->initStmt(sql);
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'initStmt'.",&tolua_err);
 return 0;
#endif
}

/* method: pushString of class  DF::DataBaseMySQL */
static int tolua_DFLuaServerLib_DF_DataBaseMySQL_pushString00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"DF::DataBaseMySQL",0,&tolua_err) ||
 !tolua_isstring(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  DF::DataBaseMySQL* self = (DF::DataBaseMySQL*)  tolua_tousertype(tolua_S,1,0);
  const char* val = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'pushString'",NULL);
#endif
 {
  self->pushString(val);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'pushString'.",&tolua_err);
 return 0;
#endif
}

/* method: pushBlob of class  DF::DataBaseMySQL */
static int tolua_DFLuaServerLib_DF_DataBaseMySQL_pushBlob00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"DF::DataBaseMySQL",0,&tolua_err) ||
 !tolua_isstring(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  DF::DataBaseMySQL* self = (DF::DataBaseMySQL*)  tolua_tousertype(tolua_S,1,0);
  const char* val = ((const char*)  tolua_tostring(tolua_S,2,0));
  unsigned int len = ((unsigned int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'pushBlob'",NULL);
#endif
 {
  self->pushBlob(val,len);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'pushBlob'.",&tolua_err);
 return 0;
#endif
}

/* method: pushData of class  DF::DataBaseMySQL */
static int tolua_DFLuaServerLib_DF_DataBaseMySQL_pushData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"DF::DataBaseMySQL",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isstring(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  DF::DataBaseMySQL* self = (DF::DataBaseMySQL*)  tolua_tousertype(tolua_S,1,0);
  int type = ((int)  tolua_tonumber(tolua_S,2,0));
  const char* data = ((const char*)  tolua_tostring(tolua_S,3,0));
  unsigned int len = ((unsigned int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'pushData'",NULL);
#endif
 {
  self->pushData(type,data,len);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'pushData'.",&tolua_err);
 return 0;
#endif
}

/* method: executeStmt of class  DF::DataBaseMySQL */
static int tolua_DFLuaServerLib_DF_DataBaseMySQL_executeStmt01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"DF::DataBaseMySQL",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  DF::DataBaseMySQL* self = (DF::DataBaseMySQL*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'executeStmt'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->executeStmt();
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
tolua_lerror:
 return tolua_DFLuaServerLib_DF_DataBaseMySQL_executeStmt00(tolua_S);
}

/* method: getUser of class  DF::DataBaseMySQL */
static int tolua_DFLuaServerLib_DF_DataBaseMySQL_getUser00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const DF::DataBaseMySQL",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const DF::DataBaseMySQL* self = (const DF::DataBaseMySQL*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getUser'",NULL);
#endif
 {
  const char* tolua_ret = (const char*)  self->getUser();
 tolua_pushstring(tolua_S,(const char*)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getUser'.",&tolua_err);
 return 0;
#endif
}

/* method: getPassword of class  DF::DataBaseMySQL */
static int tolua_DFLuaServerLib_DF_DataBaseMySQL_getPassword00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const DF::DataBaseMySQL",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const DF::DataBaseMySQL* self = (const DF::DataBaseMySQL*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getPassword'",NULL);
#endif
 {
  const char* tolua_ret = (const char*)  self->getPassword();
 tolua_pushstring(tolua_S,(const char*)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getPassword'.",&tolua_err);
 return 0;
#endif
}

/* method: getHost of class  DF::DataBaseMySQL */
static int tolua_DFLuaServerLib_DF_DataBaseMySQL_getHost00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const DF::DataBaseMySQL",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const DF::DataBaseMySQL* self = (const DF::DataBaseMySQL*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getHost'",NULL);
#endif
 {
  const char* tolua_ret = (const char*)  self->getHost();
 tolua_pushstring(tolua_S,(const char*)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getHost'.",&tolua_err);
 return 0;
#endif
}

/* method: getIP of class  DF::DataBaseMySQL */
static int tolua_DFLuaServerLib_DF_DataBaseMySQL_getIP00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const DF::DataBaseMySQL",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const DF::DataBaseMySQL* self = (const DF::DataBaseMySQL*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getIP'",NULL);
#endif
 {
  const char* tolua_ret = (const char*)  self->getIP();
 tolua_pushstring(tolua_S,(const char*)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getIP'.",&tolua_err);
 return 0;
#endif
}

/* method: getPort of class  DF::DataBaseMySQL */
static int tolua_DFLuaServerLib_DF_DataBaseMySQL_getPort00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const DF::DataBaseMySQL",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const DF::DataBaseMySQL* self = (const DF::DataBaseMySQL*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getPort'",NULL);
#endif
 {
  unsigned short tolua_ret = (unsigned short)  self->getPort();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getPort'.",&tolua_err);
 return 0;
#endif
}

/* method: sendPackMsg of class  DF::BaseServer */
static int tolua_DFLuaServerLib_DF_BaseServer_sendPackMsg00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"DF::BaseServer",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  DF::BaseServer* self = (DF::BaseServer*)  tolua_tousertype(tolua_S,1,0);
  unsigned int uSessionID = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'sendPackMsg'",NULL);
#endif
 {
  self->sendPackMsg(uSessionID);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'sendPackMsg'.",&tolua_err);
 return 0;
#endif
}

/* method: sendObject of class  DF::BaseServer */
static int tolua_DFLuaServerLib_DF_BaseServer_sendObject00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"DF::BaseServer",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
!tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  DF::BaseServer* self = (DF::BaseServer*)  tolua_tousertype(tolua_S,1,0);
  unsigned int uSessionID = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
  unsigned short uMsgType = ((unsigned short)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'sendObject'",NULL);
#endif
 {
  self->sendObject(uSessionID,uMsgType);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'sendObject'.",&tolua_err);
 return 0;
#endif
}

/* method: sendBytes of class  DF::BaseServer */
static int tolua_DFLuaServerLib_DF_BaseServer_sendBytes00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"DF::BaseServer",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isstring(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  DF::BaseServer* self = (DF::BaseServer*)  tolua_tousertype(tolua_S,1,0);
  unsigned int uSessionID = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
  const char* pHead = ((const char*)  tolua_tostring(tolua_S,3,0));
  unsigned short uSize = ((unsigned short)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'sendBytes'",NULL);
#endif
 {
  self->sendBytes(uSessionID,pHead,uSize);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'sendBytes'.",&tolua_err);
 return 0;
#endif
}

/* method: sendWhoPackMsg of class  DF::BaseServer */
static int tolua_DFLuaServerLib_DF_BaseServer_sendWhoPackMsg00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"DF::BaseServer",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  DF::BaseServer* self = (DF::BaseServer*)  tolua_tousertype(tolua_S,1,0);
  unsigned int uWho = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'sendWhoPackMsg'",NULL);
#endif
 {
  self->sendWhoPackMsg(uWho);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'sendWhoPackMsg'.",&tolua_err);
 return 0;
#endif
}

/* method: sendWhoObject of class  DF::BaseServer */
static int tolua_DFLuaServerLib_DF_BaseServer_sendWhoObject00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"DF::BaseServer",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
!tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  DF::BaseServer* self = (DF::BaseServer*)  tolua_tousertype(tolua_S,1,0);
  unsigned int uWho = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
  unsigned short uMsgType = ((unsigned short)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'sendWhoObject'",NULL);
#endif
 {
  self->sendWhoObject(uWho,uMsgType);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'sendWhoObject'.",&tolua_err);
 return 0;
#endif
}

/* method: connect of class  DF::BaseServer */
static int tolua_DFLuaServerLib_DF_BaseServer_connect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"DF::BaseServer",0,&tolua_err) ||
 !tolua_isstring(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  DF::BaseServer* self = (DF::BaseServer*)  tolua_tousertype(tolua_S,1,0);
  const char* ip = ((const char*)  tolua_tostring(tolua_S,2,0));
  unsigned int uPort = ((unsigned int)  tolua_tonumber(tolua_S,3,0));
  unsigned short uWho = ((unsigned short)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'connect'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->connect(ip,uPort,uWho);
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'connect'.",&tolua_err);
 return 0;
#endif
}

/* method: disConnect of class  DF::BaseServer */
static int tolua_DFLuaServerLib_DF_BaseServer_disConnect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"DF::BaseServer",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  DF::BaseServer* self = (DF::BaseServer*)  tolua_tousertype(tolua_S,1,0);
  unsigned int uSessionID = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'disConnect'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->disConnect(uSessionID);
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'disConnect'.",&tolua_err);
 return 0;
#endif
}

/* method: hasConnect of class  DF::BaseServer */
static int tolua_DFLuaServerLib_DF_BaseServer_hasConnect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const DF::BaseServer",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const DF::BaseServer* self = (const DF::BaseServer*)  tolua_tousertype(tolua_S,1,0);
  unsigned int uSessionID = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'hasConnect'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->hasConnect(uSessionID);
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'hasConnect'.",&tolua_err);
 return 0;
#endif
}

/* method: isSendOver of class  DF::BaseServer */
static int tolua_DFLuaServerLib_DF_BaseServer_isSendOver00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const DF::BaseServer",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const DF::BaseServer* self = (const DF::BaseServer*)  tolua_tousertype(tolua_S,1,0);
  unsigned int uSessionID = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isSendOver'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->isSendOver(uSessionID);
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isSendOver'.",&tolua_err);
 return 0;
#endif
}

/* method: setWorld of class  DF::BaseServer */
static int tolua_DFLuaServerLib_DF_BaseServer_setWorld00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"DF::BaseServer",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  DF::BaseServer* self = (DF::BaseServer*)  tolua_tousertype(tolua_S,1,0);
  unsigned short uWorld = ((unsigned short)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setWorld'",NULL);
#endif
 {
  self->setWorld(uWorld);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setWorld'.",&tolua_err);
 return 0;
#endif
}

/* method: allocGloablID of class  DF::BaseServer */
static int tolua_DFLuaServerLib_DF_BaseServer_allocGloablID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"DF::BaseServer",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  DF::BaseServer* self = (DF::BaseServer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'allocGloablID'",NULL);
#endif
 {
  double tolua_ret = (double)  self->allocGloablID();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'allocGloablID'.",&tolua_err);
 return 0;
#endif
}

/* method: getPackMessage of class  DF::BaseServer */
static int tolua_DFLuaServerLib_DF_BaseServer_getPackMessage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const DF::BaseServer",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const DF::BaseServer* self = (const DF::BaseServer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getPackMessage'",NULL);
#endif
 {
  DF::PackMessage* tolua_ret = (DF::PackMessage*)  self->getPackMessage();
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"DF::PackMessage");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getPackMessage'.",&tolua_err);
 return 0;
#endif
}

/* method: getUnpackMessage of class  DF::BaseServer */
static int tolua_DFLuaServerLib_DF_BaseServer_getUnpackMessage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const DF::BaseServer",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const DF::BaseServer* self = (const DF::BaseServer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getUnpackMessage'",NULL);
#endif
 {
  DF::UnpackMessage* tolua_ret = (DF::UnpackMessage*)  self->getUnpackMessage();
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"DF::UnpackMessage");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getUnpackMessage'.",&tolua_err);
 return 0;
#endif
}

/* method: setPackMessage of class  DF::BaseServer */
static int tolua_DFLuaServerLib_DF_BaseServer_setPackMessage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"DF::BaseServer",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"DF::PackMessage",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  DF::BaseServer* self = (DF::BaseServer*)  tolua_tousertype(tolua_S,1,0);
  DF::PackMessage* pPackMsg = ((DF::PackMessage*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setPackMessage'",NULL);
#endif
 {
  self->setPackMessage(pPackMsg);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setPackMessage'.",&tolua_err);
 return 0;
#endif
}

/* method: setUnpackMessage of class  DF::BaseServer */
static int tolua_DFLuaServerLib_DF_BaseServer_setUnpackMessage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"DF::BaseServer",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"DF::UnpackMessage",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  DF::BaseServer* self = (DF::BaseServer*)  tolua_tousertype(tolua_S,1,0);
  DF::UnpackMessage* pUnpackMsg = ((DF::UnpackMessage*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setUnpackMessage'",NULL);
#endif
 {
  self->setUnpackMessage(pUnpackMsg);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setUnpackMessage'.",&tolua_err);
 return 0;
#endif
}

/* method: getCurNetConnect of class  DF::BaseServer */
static int tolua_DFLuaServerLib_DF_BaseServer_getCurNetConnect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const DF::BaseServer",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const DF::BaseServer* self = (const DF::BaseServer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getCurNetConnect'",NULL);
#endif
 {
  DF::NetConnect* tolua_ret = (DF::NetConnect*)  self->getCurNetConnect();
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"DF::NetConnect");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getCurNetConnect'.",&tolua_err);
 return 0;
#endif
}

/* method: getProcess of class  DF::BaseServer */
static int tolua_DFLuaServerLib_DF_BaseServer_getProcess00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"DF::BaseServer",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  DF::BaseServer* self = (DF::BaseServer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getProcess'",NULL);
#endif
 {
  Process* tolua_ret = (Process*)  self->getProcess();
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"Process");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getProcess'.",&tolua_err);
 return 0;
#endif
}

/* method: getDateTime of class  DF::BaseServer */
static int tolua_DFLuaServerLib_DF_BaseServer_getDateTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"DF::BaseServer",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  DF::BaseServer* self = (DF::BaseServer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDateTime'",NULL);
#endif
 {
  DF::DateTime* tolua_ret = (DF::DateTime*)  self->getDateTime();
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"DF::DateTime");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getDateTime'.",&tolua_err);
 return 0;
#endif
}

/* method: getIP of class  DF::BaseServer */
static int tolua_DFLuaServerLib_DF_BaseServer_getIP00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const DF::BaseServer",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const DF::BaseServer* self = (const DF::BaseServer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getIP'",NULL);
#endif
 {
  const char* tolua_ret = (const char*)  self->getIP();
 tolua_pushstring(tolua_S,(const char*)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getIP'.",&tolua_err);
 return 0;
#endif
}

/* method: getProt of class  DF::BaseServer */
static int tolua_DFLuaServerLib_DF_BaseServer_getProt00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const DF::BaseServer",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const DF::BaseServer* self = (const DF::BaseServer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getProt'",NULL);
#endif
 {
  unsigned short tolua_ret = (unsigned short)  self->getProt();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getProt'.",&tolua_err);
 return 0;
#endif
}

/* method: setTrigger of class  DF::BaseServer */
static int tolua_DFLuaServerLib_DF_BaseServer_setTrigger00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"DF::BaseServer",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isusertype(tolua_S,3,"Trigger",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  DF::BaseServer* self = (DF::BaseServer*)  tolua_tousertype(tolua_S,1,0);
  DF::BaseServer::BaseServerTriggerEnum eType = ((DF::BaseServer::BaseServerTriggerEnum) (int)  tolua_tonumber(tolua_S,2,0));
  Trigger* pTrigger = ((Trigger*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTrigger'",NULL);
#endif
 {
  self->setTrigger(eType,pTrigger);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTrigger'.",&tolua_err);
 return 0;
#endif
}

/* method: instancePtr of class  DF::DataBaseServer */
static int tolua_DFLuaServerLib_DF_DataBaseServer_instancePtr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"DF::DataBaseServer",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
 {
  DF::DataBaseServer* tolua_ret = (DF::DataBaseServer*)  DF::DataBaseServer::instancePtr();
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"DF::DataBaseServer");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'instancePtr'.",&tolua_err);
 return 0;
#endif
}

/* method: unintance of class  DF::DataBaseServer */
static int tolua_DFLuaServerLib_DF_DataBaseServer_unintance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"DF::DataBaseServer",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
 {
  DF::DataBaseServer::unintance();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'unintance'.",&tolua_err);
 return 0;
#endif
}

/* method: initDataBase of class  DF::DataBaseServer */
static int tolua_DFLuaServerLib_DF_DataBaseServer_initDataBase00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"DF::DataBaseServer",0,&tolua_err) ||
 !tolua_isstring(tolua_S,2,0,&tolua_err) ||
 !tolua_isstring(tolua_S,3,0,&tolua_err) ||
 !tolua_isstring(tolua_S,4,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
 !tolua_isstring(tolua_S,6,1,&tolua_err) ||
 !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  DF::DataBaseServer* self = (DF::DataBaseServer*)  tolua_tousertype(tolua_S,1,0);
  const char* host = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* user = ((const char*)  tolua_tostring(tolua_S,3,0));
  const char* passwd = ((const char*)  tolua_tostring(tolua_S,4,0));
  unsigned short port = ((unsigned short)  tolua_tonumber(tolua_S,5,0));
  const char* ip = ((const char*)  tolua_tostring(tolua_S,6,NULL));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'initDataBase'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->initDataBase(host,user,passwd,port,ip);
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'initDataBase'.",&tolua_err);
 return 0;
#endif
}

/* method: executeSQL of class  DF::DataBaseServer */
static int tolua_DFLuaServerLib_DF_DataBaseServer_executeSQL00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"DF::DataBaseServer",0,&tolua_err) ||
 !tolua_isstring(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  DF::DataBaseServer* self = (DF::DataBaseServer*)  tolua_tousertype(tolua_S,1,0);
  const char* sql = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'executeSQL'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->executeSQL(sql);
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'executeSQL'.",&tolua_err);
 return 0;
#endif
}

/* method: executeStmt of class  DF::DataBaseServer */
static int tolua_DFLuaServerLib_DF_DataBaseServer_executeStmt00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"DF::DataBaseServer",0,&tolua_err) ||
 !tolua_isstring(tolua_S,2,0,&tolua_err) ||
 !tolua_isusertype(tolua_S,3,"DF::UnpackMessage",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  DF::DataBaseServer* self = (DF::DataBaseServer*)  tolua_tousertype(tolua_S,1,0);
  const char* sql = ((const char*)  tolua_tostring(tolua_S,2,0));
  DF::UnpackMessage* unpack = ((DF::UnpackMessage*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'executeStmt'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->executeStmt(sql,unpack);
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'executeStmt'.",&tolua_err);
 return 0;
#endif
}

/* method: getDataBaseMySQL of class  DF::DataBaseServer */
static int tolua_DFLuaServerLib_DF_DataBaseServer_getDataBaseMySQL00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const DF::DataBaseServer",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const DF::DataBaseServer* self = (const DF::DataBaseServer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDataBaseMySQL'",NULL);
#endif
 {
  DF::DataBaseMySQL* tolua_ret = (DF::DataBaseMySQL*)  self->getDataBaseMySQL();
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"DF::DataBaseMySQL");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getDataBaseMySQL'.",&tolua_err);
 return 0;
#endif
}

/* Open function */
TOLUA_API int tolua_DFLuaServerLib_open (void* void_tolua_S)
{
 lua_State* tolua_S = static_cast<lua_State*>(void_tolua_S);
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
 tolua_module(tolua_S,"DF",0);
 tolua_beginmodule(tolua_S,"DF");
 tolua_cclass(tolua_S,"Config","DF::Config","",NULL);
 tolua_beginmodule(tolua_S,"Config");
 tolua_variable(tolua_S,"MIN_INT8",tolua_get_DF__Config_MIN_INT8,NULL);
 tolua_variable(tolua_S,"MAX_INT8",tolua_get_DF__Config_MAX_INT8,NULL);
 tolua_variable(tolua_S,"MIN_INT16",tolua_get_DF__Config_MIN_INT16,NULL);
 tolua_variable(tolua_S,"MAX_INT16",tolua_get_DF__Config_MAX_INT16,NULL);
 tolua_variable(tolua_S,"MIN_INT32",tolua_get_DF__Config_MIN_INT32,NULL);
 tolua_variable(tolua_S,"MAX_INT32",tolua_get_DF__Config_MAX_INT32,NULL);
 tolua_variable(tolua_S,"MIN_INT64",tolua_get_DF__Config_MIN_INT64,NULL);
 tolua_variable(tolua_S,"MAX_INT64",tolua_get_DF__Config_MAX_INT64,NULL);
 tolua_variable(tolua_S,"MAX_UINT8",tolua_get_DF__Config_unsigned_MAX_UINT8,NULL);
 tolua_variable(tolua_S,"MAX_UINT16",tolua_get_DF__Config_unsigned_MAX_UINT16,NULL);
 tolua_variable(tolua_S,"MAX_UINT32",tolua_get_DF__Config_unsigned_MAX_UINT32,NULL);
 tolua_variable(tolua_S,"MAX_UINT64",tolua_get_DF__Config_MAX_UINT64,NULL);
 tolua_variable(tolua_S,"MIN_FLOAT",tolua_get_DF__Config_MIN_FLOAT,NULL);
 tolua_variable(tolua_S,"MAX_FLOAT",tolua_get_DF__Config_MAX_FLOAT,NULL);
 tolua_variable(tolua_S,"MIN_DOUBLE",tolua_get_DF__Config_MIN_DOUBLE,NULL);
 tolua_variable(tolua_S,"MAX_DOUBLE",tolua_get_DF__Config_MAX_DOUBLE,NULL);
 tolua_variable(tolua_S,"MAX_STACK_DEEP",tolua_get_DF__Config_MAX_STACK_DEEP,NULL);
 tolua_variable(tolua_S,"NONE_FLAG",tolua_get_DF__Config_NONE_FLAG,NULL);
 tolua_variable(tolua_S,"TRUE_FLAG",tolua_get_DF__Config_TRUE_FLAG,NULL);
 tolua_variable(tolua_S,"FALSE_FLAG",tolua_get_DF__Config_FALSE_FLAG,NULL);
 tolua_variable(tolua_S,"SMALL_TUPLE_FLAG",tolua_get_DF__Config_SMALL_TUPLE_FLAG,NULL);
 tolua_variable(tolua_S,"BIG_TUPLE_FLAG",tolua_get_DF__Config_BIG_TUPLE_FLAG,NULL);
 tolua_variable(tolua_S,"SMALL_LIST_FLAG",tolua_get_DF__Config_SMALL_LIST_FLAG,NULL);
 tolua_variable(tolua_S,"BIG_LIST_FLAG",tolua_get_DF__Config_BIG_LIST_FLAG,NULL);
 tolua_variable(tolua_S,"SMALL_SET_FLAG",tolua_get_DF__Config_SMALL_SET_FLAG,NULL);
 tolua_variable(tolua_S,"BIG_SET_FLAG",tolua_get_DF__Config_BIG_SET_FLAG,NULL);
 tolua_variable(tolua_S,"SMALL_DICT_FLAG",tolua_get_DF__Config_SMALL_DICT_FLAG,NULL);
 tolua_variable(tolua_S,"BIG_DICT_FLAG",tolua_get_DF__Config_BIG_DICT_FLAG,NULL);
 tolua_variable(tolua_S,"SMALL_STRING_FLAG",tolua_get_DF__Config_SMALL_STRING_FLAG,NULL);
 tolua_variable(tolua_S,"BIG_STRING_FLAG",tolua_get_DF__Config_BIG_STRING_FLAG,NULL);
 tolua_variable(tolua_S,"DATETIME_FLAG",tolua_get_DF__Config_DATETIME_FLAG,NULL);
 tolua_variable(tolua_S,"SIGNED_INT8_FLAG",tolua_get_DF__Config_SIGNED_INT8_FLAG,NULL);
 tolua_variable(tolua_S,"SIGNED_INT16_FLAG",tolua_get_DF__Config_SIGNED_INT16_FLAG,NULL);
 tolua_variable(tolua_S,"SIGNED_INT32_FLAG",tolua_get_DF__Config_SIGNED_INT32_FLAG,NULL);
 tolua_variable(tolua_S,"SIGNED_INT64_FLAG",tolua_get_DF__Config_SIGNED_INT64_FLAG,NULL);
 tolua_variable(tolua_S,"CLASS_OBJ_FLAG",tolua_get_DF__Config_CLASS_OBJ_FLAG,NULL);
 tolua_variable(tolua_S,"FLOAT_FLAG",tolua_get_DF__Config_FLOAT_FLAG,NULL);
 tolua_variable(tolua_S,"DOUBLE_FLAG",tolua_get_DF__Config_DOUBLE_FLAG,NULL);
 tolua_variable(tolua_S,"SEND_BLOCK_SIZE",tolua_get_DF__Config_unsigned_SEND_BLOCK_SIZE,tolua_set_DF__Config_unsigned_SEND_BLOCK_SIZE);
 tolua_variable(tolua_S,"SEND_BLOCK_NUM",tolua_get_DF__Config_unsigned_SEND_BLOCK_NUM,tolua_set_DF__Config_unsigned_SEND_BLOCK_NUM);
 tolua_variable(tolua_S,"RECV_BLOCK_SIZE",tolua_get_DF__Config_unsigned_RECV_BLOCK_SIZE,tolua_set_DF__Config_unsigned_RECV_BLOCK_SIZE);
 tolua_variable(tolua_S,"RECV_BLOCK_NUM",tolua_get_DF__Config_unsigned_RECV_BLOCK_NUM,tolua_set_DF__Config_unsigned_RECV_BLOCK_NUM);
 tolua_variable(tolua_S,"MSG_MAX_SIZE",tolua_get_DF__Config_unsigned_MSG_MAX_SIZE,tolua_set_DF__Config_unsigned_MSG_MAX_SIZE);
 tolua_variable(tolua_S,"MSG_BASE_SIZE",tolua_get_DF__Config_unsigned_MSG_BASE_SIZE,tolua_set_DF__Config_unsigned_MSG_BASE_SIZE);
 tolua_variable(tolua_S,"MAX_PACK_SIZE",tolua_get_DF__Config_unsigned_MAX_PACK_SIZE,tolua_set_DF__Config_unsigned_MAX_PACK_SIZE);
 tolua_variable(tolua_S,"MAX_CONNECT",tolua_get_DF__Config_unsigned_MAX_CONNECT,tolua_set_DF__Config_unsigned_MAX_CONNECT);
 tolua_variable(tolua_S,"MAX_THREAD",tolua_get_DF__Config_unsigned_MAX_THREAD,tolua_set_DF__Config_unsigned_MAX_THREAD);
 tolua_variable(tolua_S,"DEFAULT_PORT",tolua_get_DF__Config_unsigned_DEFAULT_PORT,tolua_set_DF__Config_unsigned_DEFAULT_PORT);
 tolua_variable(tolua_S,"DATA_BASE_PORT",tolua_get_DF__Config_unsigned_DATA_BASE_PORT,tolua_set_DF__Config_unsigned_DATA_BASE_PORT);
 tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"DF",0);
 tolua_beginmodule(tolua_S,"DF");
 tolua_cclass(tolua_S,"DateTime","DF::DateTime","",NULL);
 tolua_beginmodule(tolua_S,"DateTime");
 tolua_function(tolua_S,"year",tolua_DFLuaServerLib_DF_DateTime_year00);
 tolua_function(tolua_S,"month",tolua_DFLuaServerLib_DF_DateTime_month00);
 tolua_function(tolua_S,"day",tolua_DFLuaServerLib_DF_DateTime_day00);
 tolua_function(tolua_S,"hour",tolua_DFLuaServerLib_DF_DateTime_hour00);
 tolua_function(tolua_S,"minute",tolua_DFLuaServerLib_DF_DateTime_minute00);
 tolua_function(tolua_S,"second",tolua_DFLuaServerLib_DF_DateTime_second00);
 tolua_function(tolua_S,"milliseSecond",tolua_DFLuaServerLib_DF_DateTime_milliseSecond00);
 tolua_function(tolua_S,"days",tolua_DFLuaServerLib_DF_DateTime_days00);
 tolua_function(tolua_S,"weeks",tolua_DFLuaServerLib_DF_DateTime_weeks00);
 tolua_function(tolua_S,"months",tolua_DFLuaServerLib_DF_DateTime_months00);
 tolua_function(tolua_S,"yearDay",tolua_DFLuaServerLib_DF_DateTime_yearDay00);
 tolua_function(tolua_S,"monthDay",tolua_DFLuaServerLib_DF_DateTime_monthDay00);
 tolua_function(tolua_S,"weekDay",tolua_DFLuaServerLib_DF_DateTime_weekDay00);
 tolua_function(tolua_S,"seconds",tolua_DFLuaServerLib_DF_DateTime_seconds00);
 tolua_function(tolua_S,"getUnixTime",tolua_DFLuaServerLib_DF_DateTime_getUnixTime00);
 tolua_function(tolua_S,"timeZoneSeconds",tolua_DFLuaServerLib_DF_DateTime_timeZoneSeconds00);
 tolua_function(tolua_S,"setUnixTime",tolua_DFLuaServerLib_DF_DateTime_setUnixTime00);
 tolua_function(tolua_S,"setTimeSpeed",tolua_DFLuaServerLib_DF_DateTime_setTimeSpeed00);
 tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"DF",0);
 tolua_beginmodule(tolua_S,"DF");
 tolua_cclass(tolua_S,"MessageBase","DF::MessageBase","",NULL);
 tolua_beginmodule(tolua_S,"MessageBase");
 tolua_function(tolua_S,"getSize",tolua_DFLuaServerLib_DF_MessageBase_getSize00);
 tolua_function(tolua_S,"setSize",tolua_DFLuaServerLib_DF_MessageBase_setSize00);
 tolua_function(tolua_S,"addSize",tolua_DFLuaServerLib_DF_MessageBase_addSize00);
 tolua_function(tolua_S,"getType",tolua_DFLuaServerLib_DF_MessageBase_getType00);
 tolua_function(tolua_S,"getBody",tolua_DFLuaServerLib_DF_MessageBase_getBody00);
 tolua_function(tolua_S,"getBodySize",tolua_DFLuaServerLib_DF_MessageBase_getBodySize00);
 tolua_function(tolua_S,"align",tolua_DFLuaServerLib_DF_MessageBase_align00);
 tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"DF",0);
 tolua_beginmodule(tolua_S,"DF");
 tolua_cclass(tolua_S,"PackMessage","DF::PackMessage","",NULL);
 tolua_beginmodule(tolua_S,"PackMessage");
 tolua_function(tolua_S,"packType",tolua_DFLuaServerLib_DF_PackMessage_packType00);
 tolua_function(tolua_S,"packMsg",tolua_DFLuaServerLib_DF_PackMessage_packMsg00);
 tolua_function(tolua_S,"packBytes",tolua_DFLuaServerLib_DF_PackMessage_packBytes00);
 tolua_function(tolua_S,"packInt8",tolua_DFLuaServerLib_DF_PackMessage_packInt800);
 tolua_function(tolua_S,"packInt16",tolua_DFLuaServerLib_DF_PackMessage_packInt1600);
 tolua_function(tolua_S,"packInt32",tolua_DFLuaServerLib_DF_PackMessage_packInt3200);
 tolua_function(tolua_S,"packUint8",tolua_DFLuaServerLib_DF_PackMessage_packUint800);
 tolua_function(tolua_S,"packUint16",tolua_DFLuaServerLib_DF_PackMessage_packUint1600);
 tolua_function(tolua_S,"packUint32",tolua_DFLuaServerLib_DF_PackMessage_packUint3200);
 tolua_function(tolua_S,"packFloat",tolua_DFLuaServerLib_DF_PackMessage_packFloat00);
 tolua_function(tolua_S,"packDouble",tolua_DFLuaServerLib_DF_PackMessage_packDouble00);
 tolua_function(tolua_S,"packValue",tolua_DFLuaServerLib_DF_PackMessage_packValue00);
 tolua_function(tolua_S,"packInt",tolua_DFLuaServerLib_DF_PackMessage_packInt00);
 tolua_function(tolua_S,"packDict",tolua_DFLuaServerLib_DF_PackMessage_packDict00);
 tolua_function(tolua_S,"packString",tolua_DFLuaServerLib_DF_PackMessage_packString00);
 tolua_function(tolua_S,"packObject",tolua_DFLuaServerLib_DF_PackMessage_packObject00);
 tolua_function(tolua_S,"getIsOK",tolua_DFLuaServerLib_DF_PackMessage_getIsOK00);
 tolua_function(tolua_S,"getTotalBodySize",tolua_DFLuaServerLib_DF_PackMessage_getTotalBodySize00);
 tolua_function(tolua_S,"getCurrentEmptySize",tolua_DFLuaServerLib_DF_PackMessage_getCurrentEmptySize00);
 tolua_function(tolua_S,"getMsg",tolua_DFLuaServerLib_DF_PackMessage_getMsg00);
 tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"DF",0);
 tolua_beginmodule(tolua_S,"DF");
 tolua_cclass(tolua_S,"UnpackMessage","DF::UnpackMessage","",NULL);
 tolua_beginmodule(tolua_S,"UnpackMessage");
 tolua_function(tolua_S,"reset",tolua_DFLuaServerLib_DF_UnpackMessage_reset00);
 tolua_function(tolua_S,"unpackMsg",tolua_DFLuaServerLib_DF_UnpackMessage_unpackMsg00);
 tolua_function(tolua_S,"unpackInt8",tolua_DFLuaServerLib_DF_UnpackMessage_unpackInt800);
 tolua_function(tolua_S,"unpackInt16",tolua_DFLuaServerLib_DF_UnpackMessage_unpackInt1600);
 tolua_function(tolua_S,"unpackInt32",tolua_DFLuaServerLib_DF_UnpackMessage_unpackInt3200);
 tolua_function(tolua_S,"unpackUint8",tolua_DFLuaServerLib_DF_UnpackMessage_unpackUint800);
 tolua_function(tolua_S,"unpackUint16",tolua_DFLuaServerLib_DF_UnpackMessage_unpackUint1600);
 tolua_function(tolua_S,"unpackUint32",tolua_DFLuaServerLib_DF_UnpackMessage_unpackUint3200);
 tolua_function(tolua_S,"unpackFloat",tolua_DFLuaServerLib_DF_UnpackMessage_unpackFloat00);
 tolua_function(tolua_S,"unpackDouble",tolua_DFLuaServerLib_DF_UnpackMessage_unpackDouble00);
 tolua_function(tolua_S,"unpackValue",tolua_DFLuaServerLib_DF_UnpackMessage_unpackValue00);
 tolua_function(tolua_S,"unpackStream",tolua_DFLuaServerLib_DF_UnpackMessage_unpackStream00);
 tolua_function(tolua_S,"unpackString",tolua_DFLuaServerLib_DF_UnpackMessage_unpackString00);
 tolua_function(tolua_S,"getUnpackFence",tolua_DFLuaServerLib_DF_UnpackMessage_getUnpackFence00);
 tolua_function(tolua_S,"getSurplusSize",tolua_DFLuaServerLib_DF_UnpackMessage_getSurplusSize00);
 tolua_function(tolua_S,"getIsOk",tolua_DFLuaServerLib_DF_UnpackMessage_getIsOk00);
 tolua_function(tolua_S,"unpackObject",tolua_DFLuaServerLib_DF_UnpackMessage_unpackObject00);
 tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"DF",0);
 tolua_beginmodule(tolua_S,"DF");
 tolua_cclass(tolua_S,"LuaSystem","DF::LuaSystem","",NULL);
 tolua_beginmodule(tolua_S,"LuaSystem");
 tolua_function(tolua_S,"instancePtr",tolua_DFLuaServerLib_DF_LuaSystem_instancePtr00);
 tolua_function(tolua_S,"setDebug",tolua_DFLuaServerLib_DF_LuaSystem_setDebug00);
 tolua_function(tolua_S,"doString",tolua_DFLuaServerLib_DF_LuaSystem_doString00);
 tolua_function(tolua_S,"doFile",tolua_DFLuaServerLib_DF_LuaSystem_doFile00);
 tolua_function(tolua_S,"reload",tolua_DFLuaServerLib_DF_LuaSystem_reload00);
 tolua_function(tolua_S,"enableReturn",tolua_DFLuaServerLib_DF_LuaSystem_enableReturn00);
 tolua_function(tolua_S,"disableReturn",tolua_DFLuaServerLib_DF_LuaSystem_disableReturn00);
 tolua_function(tolua_S,"getRootPath",tolua_DFLuaServerLib_DF_LuaSystem_getRootPath00);
 tolua_function(tolua_S,"setIsRunScriptMsg",tolua_DFLuaServerLib_DF_LuaSystem_setIsRunScriptMsg00);
 tolua_function(tolua_S,"getRunScirptPrint",tolua_DFLuaServerLib_DF_LuaSystem_getRunScirptPrint00);
 tolua_function(tolua_S,"loadFiles",tolua_DFLuaServerLib_DF_LuaSystem_loadFiles00);
 tolua_function(tolua_S,"loadAllFiles",tolua_DFLuaServerLib_DF_LuaSystem_loadAllFiles00);
 tolua_function(tolua_S,"getServer",tolua_DFLuaServerLib_DF_LuaSystem_getServer00);
 tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"DF",0);
 tolua_beginmodule(tolua_S,"DF");
 tolua_cclass(tolua_S,"LuaTrigger","DF::LuaTrigger","Trigger",NULL);
 tolua_beginmodule(tolua_S,"LuaTrigger");
 tolua_constant(tolua_S,"LTE_Dtor",DF::LuaTrigger::LTE_Dtor);
 tolua_constant(tolua_S,"LTE_TriMsg",DF::LuaTrigger::LTE_TriMsg);
 tolua_constant(tolua_S,"LTE_TriNone",DF::LuaTrigger::LTE_TriNone);
 tolua_constant(tolua_S,"LTE_Clear",DF::LuaTrigger::LTE_Clear);
 tolua_constant(tolua_S,"LTE_MaxCount",DF::LuaTrigger::LTE_MaxCount);
 tolua_function(tolua_S,"clear",tolua_DFLuaServerLib_DF_LuaTrigger_clear00);
 tolua_function(tolua_S,"triggering",tolua_DFLuaServerLib_DF_LuaTrigger_triggering00);
 tolua_function(tolua_S,"triggering",tolua_DFLuaServerLib_DF_LuaTrigger_triggering01);
 tolua_function(tolua_S,"getID",tolua_DFLuaServerLib_DF_LuaTrigger_getID00);
 tolua_function(tolua_S,"getType",tolua_DFLuaServerLib_DF_LuaTrigger_getType00);
 tolua_function(tolua_S,"pushFunction",tolua_DFLuaServerLib_DF_LuaTrigger_pushFunction00);
 tolua_function(tolua_S,"addToRootCallBack",tolua_DFLuaServerLib_DF_LuaTrigger_addToRootCallBack00);
 tolua_function(tolua_S,"screate",tolua_DFLuaServerLib_DF_LuaTrigger_screate00);
 tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"DF",0);
 tolua_beginmodule(tolua_S,"DF");
 tolua_cclass(tolua_S,"LuaFunction","DF::LuaFunction","",NULL);
 tolua_beginmodule(tolua_S,"LuaFunction");
 tolua_function(tolua_S,"screate",tolua_DFLuaServerLib_DF_LuaFunction_screate00);
 tolua_function(tolua_S,"screate",tolua_DFLuaServerLib_DF_LuaFunction_screate01);
 tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"DF",0);
 tolua_beginmodule(tolua_S,"DF");
 tolua_cclass(tolua_S,"NetConnect","DF::NetConnect","",NULL);
 tolua_beginmodule(tolua_S,"NetConnect");
 tolua_function(tolua_S,"isShutdown",tolua_DFLuaServerLib_DF_NetConnect_isShutdown00);
 tolua_function(tolua_S,"getSessionID",tolua_DFLuaServerLib_DF_NetConnect_getSessionID00);
 tolua_function(tolua_S,"getConnectTime",tolua_DFLuaServerLib_DF_NetConnect_getConnectTime00);
 tolua_function(tolua_S,"getIP",tolua_DFLuaServerLib_DF_NetConnect_getIP00);
 tolua_function(tolua_S,"getPort",tolua_DFLuaServerLib_DF_NetConnect_getPort00);
 tolua_function(tolua_S,"getWho",tolua_DFLuaServerLib_DF_NetConnect_getWho00);
 tolua_function(tolua_S,"sendBytes",tolua_DFLuaServerLib_DF_NetConnect_sendBytes00);
 tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"DF",0);
 tolua_beginmodule(tolua_S,"DF");
 tolua_cclass(tolua_S,"DataBaseMySQL","DF::DataBaseMySQL","",NULL);
 tolua_beginmodule(tolua_S,"DataBaseMySQL");
 tolua_function(tolua_S,"execute",tolua_DFLuaServerLib_DF_DataBaseMySQL_execute00);
 tolua_function(tolua_S,"executeStmt",tolua_DFLuaServerLib_DF_DataBaseMySQL_executeStmt00);
 tolua_function(tolua_S,"initStmt",tolua_DFLuaServerLib_DF_DataBaseMySQL_initStmt00);
 tolua_function(tolua_S,"pushString",tolua_DFLuaServerLib_DF_DataBaseMySQL_pushString00);
 tolua_function(tolua_S,"pushBlob",tolua_DFLuaServerLib_DF_DataBaseMySQL_pushBlob00);
 tolua_function(tolua_S,"pushData",tolua_DFLuaServerLib_DF_DataBaseMySQL_pushData00);
 tolua_function(tolua_S,"executeStmt",tolua_DFLuaServerLib_DF_DataBaseMySQL_executeStmt01);
 tolua_function(tolua_S,"getUser",tolua_DFLuaServerLib_DF_DataBaseMySQL_getUser00);
 tolua_function(tolua_S,"getPassword",tolua_DFLuaServerLib_DF_DataBaseMySQL_getPassword00);
 tolua_function(tolua_S,"getHost",tolua_DFLuaServerLib_DF_DataBaseMySQL_getHost00);
 tolua_function(tolua_S,"getIP",tolua_DFLuaServerLib_DF_DataBaseMySQL_getIP00);
 tolua_function(tolua_S,"getPort",tolua_DFLuaServerLib_DF_DataBaseMySQL_getPort00);
 tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"DF",0);
 tolua_beginmodule(tolua_S,"DF");
 tolua_cclass(tolua_S,"BaseServer","DF::BaseServer","",NULL);
 tolua_beginmodule(tolua_S,"BaseServer");
 tolua_constant(tolua_S,"BSTE_OnStar",DF::BaseServer::BSTE_OnStar);
 tolua_constant(tolua_S,"BSTE_OnLost",DF::BaseServer::BSTE_OnLost);
 tolua_constant(tolua_S,"BSTE_OnMsg",DF::BaseServer::BSTE_OnMsg);
 tolua_constant(tolua_S,"BSTE_BeforeNewMinute",DF::BaseServer::BSTE_BeforeNewMinute);
 tolua_constant(tolua_S,"BSTE_BeforeNewHour",DF::BaseServer::BSTE_BeforeNewHour);
 tolua_constant(tolua_S,"BSTE_BeforeNewDay",DF::BaseServer::BSTE_BeforeNewDay);
 tolua_constant(tolua_S,"BSTE_AfterNewMinute",DF::BaseServer::BSTE_AfterNewMinute);
 tolua_constant(tolua_S,"BSTE_AfterNewHour",DF::BaseServer::BSTE_AfterNewHour);
 tolua_constant(tolua_S,"BSTE_AfterNewDay",DF::BaseServer::BSTE_AfterNewDay);
 tolua_constant(tolua_S,"BSTE_PerSecond",DF::BaseServer::BSTE_PerSecond);
 tolua_constant(tolua_S,"BSTE_KeyboardKeyDown",DF::BaseServer::BSTE_KeyboardKeyDown);
 tolua_constant(tolua_S,"BSTE_MaxCount",DF::BaseServer::BSTE_MaxCount);
 tolua_function(tolua_S,"sendPackMsg",tolua_DFLuaServerLib_DF_BaseServer_sendPackMsg00);
 tolua_function(tolua_S,"sendObject",tolua_DFLuaServerLib_DF_BaseServer_sendObject00);
 tolua_function(tolua_S,"sendBytes",tolua_DFLuaServerLib_DF_BaseServer_sendBytes00);
 tolua_function(tolua_S,"sendWhoPackMsg",tolua_DFLuaServerLib_DF_BaseServer_sendWhoPackMsg00);
 tolua_function(tolua_S,"sendWhoObject",tolua_DFLuaServerLib_DF_BaseServer_sendWhoObject00);
 tolua_function(tolua_S,"connect",tolua_DFLuaServerLib_DF_BaseServer_connect00);
 tolua_function(tolua_S,"disConnect",tolua_DFLuaServerLib_DF_BaseServer_disConnect00);
 tolua_function(tolua_S,"hasConnect",tolua_DFLuaServerLib_DF_BaseServer_hasConnect00);
 tolua_function(tolua_S,"isSendOver",tolua_DFLuaServerLib_DF_BaseServer_isSendOver00);
 tolua_function(tolua_S,"setWorld",tolua_DFLuaServerLib_DF_BaseServer_setWorld00);
 tolua_function(tolua_S,"allocGloablID",tolua_DFLuaServerLib_DF_BaseServer_allocGloablID00);
 tolua_function(tolua_S,"getPackMessage",tolua_DFLuaServerLib_DF_BaseServer_getPackMessage00);
 tolua_function(tolua_S,"getUnpackMessage",tolua_DFLuaServerLib_DF_BaseServer_getUnpackMessage00);
 tolua_function(tolua_S,"setPackMessage",tolua_DFLuaServerLib_DF_BaseServer_setPackMessage00);
 tolua_function(tolua_S,"setUnpackMessage",tolua_DFLuaServerLib_DF_BaseServer_setUnpackMessage00);
 tolua_function(tolua_S,"getCurNetConnect",tolua_DFLuaServerLib_DF_BaseServer_getCurNetConnect00);
 tolua_function(tolua_S,"getProcess",tolua_DFLuaServerLib_DF_BaseServer_getProcess00);
 tolua_function(tolua_S,"getDateTime",tolua_DFLuaServerLib_DF_BaseServer_getDateTime00);
 tolua_function(tolua_S,"getIP",tolua_DFLuaServerLib_DF_BaseServer_getIP00);
 tolua_function(tolua_S,"getProt",tolua_DFLuaServerLib_DF_BaseServer_getProt00);
 tolua_function(tolua_S,"setTrigger",tolua_DFLuaServerLib_DF_BaseServer_setTrigger00);
 tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 tolua_module(tolua_S,"DF",0);
 tolua_beginmodule(tolua_S,"DF");
 tolua_cclass(tolua_S,"DataBaseServer","DF::DataBaseServer","DF::BaseServer",NULL);
 tolua_beginmodule(tolua_S,"DataBaseServer");
 tolua_function(tolua_S,"instancePtr",tolua_DFLuaServerLib_DF_DataBaseServer_instancePtr00);
 tolua_function(tolua_S,"unintance",tolua_DFLuaServerLib_DF_DataBaseServer_unintance00);
 tolua_function(tolua_S,"initDataBase",tolua_DFLuaServerLib_DF_DataBaseServer_initDataBase00);
 tolua_function(tolua_S,"executeSQL",tolua_DFLuaServerLib_DF_DataBaseServer_executeSQL00);
 tolua_function(tolua_S,"executeStmt",tolua_DFLuaServerLib_DF_DataBaseServer_executeStmt00);
 tolua_function(tolua_S,"getDataBaseMySQL",tolua_DFLuaServerLib_DF_DataBaseServer_getDataBaseMySQL00);
 tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}
}
