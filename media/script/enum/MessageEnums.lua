------------------------------------------------------------------------
-- @brief 消息
local MessageCall = require("core.MessageCall")
------------------------------------------------------------------------
local P = {}
local MC = MessageCall.getInstance()
local fn = MC.createMessage
------------------------------------------------------------------------
P.Msg_Error 					        = fn(MC, "Msg_Error")
------------------------------------------------------------------------
-- @brief 创建一个用户
-- @[recv] [user=string, password=string, role_name=string]
-- @[send] [isOk=bool]
P.Msg_DBNewUser                         = fn(MC, "Msg_DBNewUser")
------------------------------------------------------------------------
-- @brief 登录一个用户
-- @[recv] [user=string, password=string]
-- @[send] [role_id=double]
P.Msg_DBLoginUser                       = fn(MC, "Msg_DBLoginUser")
------------------------------------------------------------------------
-- @brief 存储基本数据
-- @[recv] [role_id=double, values=list]
-- @[send] [isOk=bool]
P.Msg_DBRoleSaveValues                  = fn(MC, "Msg_DBRoleSaveValues")
------------------------------------------------------------------------
-- @brief 存储复合数据
-- @[recv] [role_id=double, objects=list]
-- @[send] [isOk=bool]
P.Msg_DBRoleSaveObjects                 = fn(MC, "Msg_DBRoleSaveObjects")
------------------------------------------------------------------------
-- @brief 存储邮件数据(发现没登录角色直接写数据库)
-- @[recv] [role_id=double, mails=map]
-- @[send] [isOk=bool]
P.Msg_DBRoleSaveMails				    = fn(MC, "Msg_DBRoleSaveMails")
------------------------------------------------------------------------
-- @brief 读取基本数据
-- @[recv] [role_id=double]
-- @[send] [values=list]
P.Msg_DBRoleLoadValues                  = fn(MC, "Msg_DBRoleLoadValues")
------------------------------------------------------------------------
-- @brief 读取符合数据
-- @[recv] [role_id=double]
-- @[send] [objects=list]
P.Msg_DBRoleLoadObjects                 = fn(MC, "Msg_DBRoleLoadObjects")
------------------------------------------------------------------------
-- @brief 读取邮件数据
-- @[recv] [role_id=double]
-- @[send] [mails=map]
P.Msg_DBRoleLoadMails				    = fn(MC, "Msg_DBRoleLoadMails")
------------------------------------------------------------------------
-- @brief 储存全局数据
-- @[recv] [keyName=string, table_length=short, data=list or map]
-- @[send] [isOk=bool]
P.Msg_DBSaveDBTable				        = fn(MC, "Msg_DBSaveDBTable")
------------------------------------------------------------------------
-- @brief 读取全局数据
-- @[recv] [keyName=string]
-- @[send] [data=list or map]
P.Msg_DBLoadDBTable				        = fn(MC, "Msg_DBLoadDBTable")
------------------------------------------------------------------------
-- @brief 给一个角色添加一条日志
-- @[recv] [role_id=double, time=double, role_name=string, type_name=string]
P.Msg_DBRoleAddNewLog                   = fn(MC, "Msg_RoleAddNewLog")
------------------------------------------------------------------------
-- @brief 登录一个角色
-- @[recv] [role_id=double, who=int]
P.Msg_LoginRole 				        = fn(MC, "Msg_LoginRole")
------------------------------------------------------------------------
-- @brief 踢掉一个角色
-- @[recv] [role_id=double]
-- @[send] [role_id=double, [isOk=bool]]
P.Msg_KickRole 					        = fn(MC, "Msg_KickRole")
------------------------------------------------------------------------
-- @brief 同步基本数据给客户端
-- @[send] [i=v, ...]
P.Msg_RoleSyncValues 			        = fn(MC, "Msg_RoleSyncValues")
------------------------------------------------------------------------
-- @brief 同步复合数据给客户端
-- @[send] [i=v, ...]
P.Msg_RoleSyncObjects 			        = fn(MC, "Msg_RoleSyncObjects")
------------------------------------------------------------------------
-- @brief 同步复合数据给客户端
-- @[send] {k=v, ...}
P.Msg_RoleSyncMails 			        = fn(MC, "Msg_RoleSyncMails")
------------------------------------------------------------------------
-- @brief 创建一个用户
-- @[recv] {world_id=short, user=string, password=string, role_name=string}
-- @[send] {world_id=short, user=string, password=string, role_name=string}
P.Msg_NewUser                           = fn(MC, "Msg_NewUser")
------------------------------------------------------------------------
-- @brief 创建一个用户
-- @[recv] {world_id=short, user=string, password=string}
-- @[send] {world_id=short, user=string, password=string}
P.Msg_LoginUser                         = fn(MC, "Msg_LoginUser")
------------------------------------------------------------------------
-- @brief 创建一个用户
-- @[recv] {role_id=double, script_text=string}
-- @[send] {send_string=string, netCurrent=int}
P.Msg_GMRunScript                       = fn(MC, "Msg_GMRunScript")
------------------------------------------------------------------------
return P