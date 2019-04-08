#encoding=utf-8

MAX_STACK_DEEP = 30
NONE_FLAG = -100
TRUE_FLAG = -101
FALSE_FLAG = -102
SMALL_TUPLE_FLAG = -103
BIG_TUPLE_FLAG = -104
SMALL_LIST_FLAG = -105
BIG_LIST_FLAG = -106
SMALL_SET_FLAG = -107
BIG_SET_FLAG = -108
SMALL_DICT_FLAG = -109
BIG_DICT_FLAG = -110
SMALL_STRING_FLAG = -111
BIG_STRING_FLAG = -112
DATETIME_FLAG = -113
SIGNED_INT8_FLAG = -114
SIGNED_INT16_FLAG = -115
SIGNED_INT32_FLAG = -116
SIGNED_INT64_FLAG = -117
CLASS_OBJ_FLAG = -118
FLOAT_FLAG = -119
DOUBLE_FLAG = -120

# ----------------------------------------------------------------------
#  @brief 消息
# ----------------------------------------------------------------------
# ----------------------------------------------------------------------
Msg_Error = 1
# ----------------------------------------------------------------------
#  @brief 创建一个用户
#  @[recv] [user=string, password=string, role_name=string]
#  @[send] [isOk=bool]
Msg_DBNewUser = 2
# ----------------------------------------------------------------------
#  @brief 登录一个用户
#  @[recv] [user=string, password=string]
#  @[send] [role_id=double]
Msg_DBLoginUser = 3
# ----------------------------------------------------------------------
#  @brief 存储基本数据
#  @[recv] [role_id=double, values=list]
#  @[send] [isOk=bool]
Msg_DBRoleSaveValues = 4
# ----------------------------------------------------------------------
#  @brief 存储复合数据
#  @[recv] [role_id=double, objects=list]
#  @[send] [isOk=bool]
Msg_DBRoleSaveObjects = 5
# ----------------------------------------------------------------------
#  @brief 存储邮件数据(发现没登录角色直接写数据库)
#  @[recv] [role_id=double, mails=map]
#  @[send] [isOk=bool]
Msg_DBRoleSaveMails = 6
# ----------------------------------------------------------------------
#  @brief 读取基本数据
#  @[recv] [role_id=double]
#  @[send] [values=list]
Msg_DBRoleLoadValues = 7
# ----------------------------------------------------------------------
#  @brief 读取符合数据
#  @[recv] [role_id=double]
#  @[send] [objects=list]
Msg_DBRoleLoadObjects = 8
# ----------------------------------------------------------------------
#  @brief 读取邮件数据
#  @[recv] [role_id=double]
#  @[send] [mails=map]
Msg_DBRoleLoadMails = 9
# ----------------------------------------------------------------------
#  @brief 储存全局数据
#  @[recv] [keyName=string, table_length=short, data=list or map]
#  @[send] [isOk=bool]
Msg_DBSaveDBTable = 10
# ----------------------------------------------------------------------
#  @brief 读取全局数据
#  @[recv] [keyName=string]
#  @[send] [data=list or map]
Msg_DBLoadDBTable = 11
# ----------------------------------------------------------------------
#  @brief 给一个角色添加一条日志
#  @[recv] [role_id=double, time=double, role_name=string, type_name=string]
Msg_DBRoleAddNewLog = 12
# ----------------------------------------------------------------------
#  @brief 登录一个角色
#  @[recv] [role_id=double, who=int]
Msg_LoginRole = 13
# ----------------------------------------------------------------------
#  @brief 踢掉一个角色
#  @[recv] [role_id=double]
#  @[send] [role_id=double, [isOk=bool]]
Msg_KickRole = 14
# ----------------------------------------------------------------------
#  @brief 同步基本数据给客户端
#  @[send] [i=v, ...]
Msg_RoleSyncValues = 15
# ----------------------------------------------------------------------
#  @brief 同步复合数据给客户端
#  @[send] [i=v, ...]
Msg_RoleSyncObjects = 16
# ----------------------------------------------------------------------
#  @brief 同步复合数据给客户端
#  @[send] {k=v, ...}
Msg_RoleSyncMails = 17
# ----------------------------------------------------------------------
#  @brief 创建一个用户
#  @[recv] {world_id=short, user=string, password=string, role_name=string}
#  @[send] {world_id=short, user=string, password=string, role_name=string}
Msg_NewUser = 18
# ----------------------------------------------------------------------
#  @brief 创建一个用户
#  @[recv] {world_id=short, user=string, password=string}
#  @[send] {world_id=short, user=string, password=string}
Msg_LoginUser = 19
# ----------------------------------------------------------------------
#  @brief 创建一个用户
#  @[recv] {role_id=double, script_text=string}
#  @[send] {send_string=string, netCurrent=int}
Msg_GMRunScript = 20
# ----------------------------------------------------------------------

# ----------------------------------------------------------------------
#  @brief 角色单一数据规则枚举
# ----------------------------------------------------------------------
# ----------------------------------------------------------------------
# ----------------------------------------------------------------------
# ----------------------------------------------------------------------
#  @brief 注册一个枚举
#  @param[ync] 是否同步给客户端
#  @param[event] 事件
#  @param[isLog] 是否有日志
#  @param[clearTime] 清空时间
# ----------------------------------------------------------------------
Val_RoleID = 1
Val_OffLineTime = 2
Val_LoginTime = 3
Val_Test1 = 4
Val_Test2 = 5
Val_Test3 = 6
# ----------------------------------------------------------------------

# ----------------------------------------------------------------------
#  @brief 角色复合数据规则枚举
# ----------------------------------------------------------------------
# ----------------------------------------------------------------------
# ----------------------------------------------------------------------
# ----------------------------------------------------------------------
#  @brief 注册一个枚举
#  @param[ync] 是否同步给客户端
#  @param[event] 事件
#  @param[isLog] 是否有日志
#  @param[clearTime] 清空时间
# ----------------------------------------------------------------------
Obj_Test0 = 1
Obj_Test1 = 2
# ----------------------------------------------------------------------

#@brief Ip地址列表数据
IpAddrDatas=[
("172.16.80.15:root:world_1","zhenkeluo:172.16.80.15"),
("172.16.80.60:root:world_2","cyl:172.16.80.60"),
("192.168.1.103:990529:world_3","sword:192.168.1.103"),
("192.168.1.105:root:world_4","swordmac:192.168.1.105")
]

#@brief Ip地址列表数据
RoleValues=[
(0, 'Val_None'),
(1, 'Val_RoleID'),
(2, 'Val_OffLineTime'),
(3, 'Val_LoginTime'),
(4, 'Val_Test1'),
(5, 'Val_Test2'),
(6, 'Val_Test3'),
]

#@brief Ip地址列表数据
ObjectValues=[
(0, 'Obj_None'),
(1, 'Obj_Test0'),
(2, 'Obj_Test1'),
]

