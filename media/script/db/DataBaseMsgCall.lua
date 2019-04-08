------------------------------------------------------------------------
-- @brief 数据服回调,主要用来存储数据
--	local m = P.reload("db.DataBaseMsgCall")
--	m.load()
--
------------------------------------------------------------------------
local MessageCall = require("core.MessageCall")
local MsgEnums = require("enum.MessageEnums")
local SafeTableEnums = require("enum.SafeTableEnums")
local sqls = require("db.DataBaseSQLConfig")
local Data = require("db.DataBaseMsgData")
local msgcall = MessageCall.getInstance()
------------------------------------------------------------------------
local P = {}
------------------------------------------------------------------------
-- @brief 初始化数据(主要用来热更新的时候不会重置掉数据)
function P.initData()
	P.dbSelectAllNames()
    P.dbSelectAllUsers()
	P.dbSelectAllGlobalDataNames()
	P.loadGlobalSafeTables()
end
------------------------------------------------------------------------
-- @brief 读取数据
function P.load()
    -- 注册消息
	msgcall:setMessageFunc(MsgEnums.Msg_DBRoleLoadValues,       P.onMsgLoadRoleValues)
	msgcall:setMessageFunc(MsgEnums.Msg_DBRoleLoadObjects,      P.onMsgRoleLoadObjects)
    msgcall:setMessageFunc(MsgEnums.Msg_DBRoleLoadMails,        P.onMsgRoleLoadMails)
	msgcall:setMessageFunc(MsgEnums.Msg_DBRoleSaveValues,       P.onMsgSaveRoleValues)
	msgcall:setMessageFunc(MsgEnums.Msg_DBRoleSaveObjects,      P.onMsgSaveRoleObjects)
	msgcall:setMessageFunc(MsgEnums.Msg_DBRoleSaveMails,        P.onMsgRoleSaveMails)
    msgcall:setMessageFunc(MsgEnums.Msg_DBSaveDBTable,          P.onMsgSaveDBTable)
	msgcall:setMessageFunc(MsgEnums.Msg_DBLoadDBTable,          P.onMsgLoadDBTable)
    msgcall:setMessageFunc(MsgEnums.Msg_DBNewUser,              P.onMsgNewUser)
    msgcall:setMessageFunc(MsgEnums.Msg_DBLoginUser,            P.onMsgLoginUser)
    msgcall:setMessageFunc(MsgEnums.Msg_DBRoleAddNewLog,        P.onMsgRoleAddNewLog)
end
------------------------------------------------------------------------
-- @brief 从数据库读取名字
function P.dbSelectAllNames()
	Data.selectAllNames = {}
	sgPackMsg:packType(0)
	sgDataBaseServer:executeSQL(sqls.tbRoleSelectAllNames)
	sgUnpackMsg:reset(sgPackMsg:getMsg())
	sgUnpackMsg:unpackMsg()
	local obj = sgUnpackMsg:unpackObject()
	for i, v in ipairs(obj) do
		table.insert(Data.selectAllNames, v[1])
	end
end

------------------------------------------------------------------------
-- @brief 从数据库读取用户
function P.dbSelectAllUsers()
	Data.selectAllUser = {}
	sgPackMsg:packType(0)
	sgDataBaseServer:executeSQL(sqls.tbLoginSelectAll)
	sgUnpackMsg:reset(sgPackMsg:getMsg())
	sgUnpackMsg:unpackMsg()
	local obj = sgUnpackMsg:unpackObject()
	for i, v in ipairs(obj) do
        table.insert(Data.selectAllUser, v[1])
	end
end 
------------------------------------------------------------------------
-- @brief 查找一个用户
-- @param[user] 用户
function P.findUser(user)
   	for _, v in ipairs(Data.selectAllUser) do
		if v == user then
			return true
		end
	end
	return false
end
------------------------------------------------------------------------
-- @brief 从数据库里读取全局表
function P.dbSelectAllGlobalDataNames()
	Data.selectGlobalDataNames = {}
	sgPackMsg:packType(0)
	sgDataBaseServer:executeSQL(sqls.tbGlobalDatasSelectKeyName)
	sgUnpackMsg:reset(sgPackMsg:getMsg())
	sgUnpackMsg:unpackMsg()
	local obj = sgUnpackMsg:unpackObject()
	for i, v in ipairs(obj) do
		table.insert(Data.selectGlobalDataNames, v[1])
	end
end
------------------------------------------------------------------------
-- @brief 查找一个角色名
-- @param[name] 名字
function P.findRoleName(name)
	for _, v in ipairs(Data.selectAllNames) do
		if v == name then
			return true
		end
	end
	return false
end
------------------------------------------------------------------------
-- @brief 查找一个全局表
-- @param[name] 名字
function P.findGlobalDataName(name)
	for _, v in ipairs(Data.selectGlobalDataNames) do
		if v == name then
			return true
		end
	end
	return false
end
------------------------------------------------------------------------
-- @brief 读取全局表
function P.loadGlobalSafeTables()
	for _, safe_table in  pairs(SafeTableEnums) do
		local keyName = safe_table._keyName
		if keyName and not P.findGlobalDataName(keyName) then
			local sql = string.format(sqls.tbGlobalDatasInsert, 0, keyName)
			sgDataBaseServer:executeSQL(sql)
		end
	end
end
------------------------------------------------------------------------
-- @brief 读取角色单一数据
-- @param[upk] 数据
function P.onMsgLoadRoleValues(upk)
	local role_id = upk:unpackValue()
	if not role_id or type(role_id) ~= "number" then
		warning("<Lua DataBaseMsgCall.onMsgCreateRole> role_id failed")
		return
	end
	
	local sql = string.format(sqls.tbRoleSelectValues, role_id)
	sgPackMsg:packType(MsgEnums.Msg_DBRoleLoadValues)
	sgPackMsg:packValue(role_id)
	local isOk = sgDataBaseServer:executeSQL(sql)
	if not isOk then
		warning("<DataBaseMsgCall.onMsgLoadRoleValues> executeSQL(" .. sql ..") is failed")
		return
	end

	P.sendPackMsg()
end
------------------------------------------------------------------------
-- @brief 读取角色复合数据
-- @param[upk] 数据
function P.onMsgRoleLoadObjects(upk)
	local role_id = upk:unpackValue()
	if not role_id or type(role_id) ~= "number" then
		warning("<Lua DataBaseMsgCall.onMsgCreateRole> role_id failed")
		return
	end

	local sql = string.format(sqls.tbRoleSelectObjects, role_id)
	sgPackMsg:packType(MsgEnums.Msg_DBRoleLoadObjects)
	sgPackMsg:packValue(role_id)
	local isOk = sgDataBaseServer:executeSQL(sql)
	if not isOk then
		warning("<DataBaseMsgCall.onMsgLoadRoleValues> executeSQL(" .. sql ..") is failed")
		return
	end

	P.sendPackMsg()
end

------------------------------------------------------------------------
-- @brief 读取角色邮件数据
-- @param[upk] 数据
function P.onMsgRoleLoadMails(upk)
	local role_id = upk:unpackValue()
	if not role_id or type(role_id) ~= "number" then
		warning("<Lua DataBaseMsgCall.onMsgRoleLoadMails> role_id failed")
		return
	end

	-- 从数据库里面取出
	sgPackMsg:packType(MsgEnums.Msg_DBRoleLoadMails)
	sgPackMsg:packValue(role_id)
	local sql = string.format(sqls.tbRoleSelectMails, role_id)
	local isOk = sgDataBaseServer:executeSQL(sql)
	if not isOk then
		warning("<DataBaseMsgCall.onMsgRoleLoadMails> executeSQL(" .. sql ..") is failed")
		return
	end

	P.sendPackMsg()
end

----------------------------------------------------------------------
-- @brief 存储角色单一数据
-- @param[upk] 数据
function P.onMsgSaveRoleValues(upk)
	local role_id = upk:unpackValue()
	if not role_id or type(role_id) ~= "number" then
		warning("<Lua DataBaseMsgCall.onMsgSaveRoleValues> role_id failed")
		return
	end

	local sql = string.format(sqls.tbRoleUpdateValues, role_id)
	local isOk = sgDataBaseServer:executeStmt(sql, upk)
	if not isOk then
		warning("<DataBaseMsgCall.onMsgSaveRoleValues> executeStmt(" .. sql ..") is failed")
		return
	end

	P.sendObject(MsgEnums.Msg_DBRoleSaveValues, role_id, {isOk})
end
------------------------------------------------------------------------
-- @brief 存储角色复合数据
-- @param[upk] 数据
function P.onMsgSaveRoleObjects(upk)
	local role_id = upk:unpackValue()
	if not role_id or type(role_id) ~= "number" then
		warning("<Lua DataBaseMsgCall.onMsgSaveRoleObjects> role_id failed")
		return
	end

	local sql = string.format(sqls.tbRoleUpdateObjets, role_id)
	local isOk = sgDataBaseServer:executeStmt(sql, upk)
	if not isOk then
		warning("<DataBaseMsgCall.onMsgSaveRoleObjects> executeStmt(" .. sql ..") is failed")
		return
	end

	P.sendObject(MsgEnums.Msg_DBRoleSaveObjects, role_id, {isOk})

end
------------------------------------------------------------------------
-- @brief 存储角色邮件数据
-- @param[upk] 数据
function P.onMsgRoleSaveMails(upk)
	local role_id = upk:unpackValue()
	local isInLine = upk:unpackValue()
	if not role_id or type(role_id) ~= "number" then
		warning("<Lua DataBaseMsgCall.onMsgSaveRoleObjects> role_id failed")
		return
	end

	local function savefunc(role_id, upk)
		local sql = string.format(sqls.tbRoleUpdateMails, role_id)
		local isOk = sgDataBaseServer:executeStmt(sql, upk)
		if not isOk then
			warning("<DataBaseMsgCall.onMsgRoleSaveMails> executeStmt(" .. sql ..") is failed")
			return
		end
		P.sendObject(MsgEnums.Msg_DBRoleSaveMails, role_id, {isOk})
	end

	-- 判断是否在线
	if isInLine == 1 then
		savefunc(role_id, upk)
		return
	end

	-- 解包
	local saveMails = upk:unpackObject()

	-- 从数据库里面取出
	sgPackMsg:packType(0)
	local sql = string.format(sqls.tbRoleSelectMails, role_id)
	local isOk = sgDataBaseServer:executeSQL(sql)
	if not isOk then
		warning("<DataBaseMsgCall.onMsgRoleSaveMails> executeSQL(" .. sql ..") is failed")
		return
	end

	-- 解包数据库
	sgUnpackMsg:reset(sgPackMsg:getMsg())
	sgUnpackMsg:unpackMsg()
	local selectData = sgUnpackMsg:unpackObject()

	local loadMails = {}
	if selectData[1] then
		loadMails = selectData[1]
	end

	-- 增加新邮件
	for i, v in ipairs(saveMails) do
		table.insert(loadMails, v)	
	end



	-- 重新打包
	sgPackMsg:packType(0)
	sgPackMsg:packObject({loadMails})
	sgUnpackMsg:reset(sgPackMsg:getMsg())
	sgUnpackMsg:unpackMsg()
	
	--写入数据库
	savefunc(role_id, sgUnpackMsg)
end
------------------------------------------------------------------------
-- @brief 存储全局数据
-- @param[upk] 数据
function P.onMsgSaveDBTable(upk)
	local keyName = upk:unpackString()
	local table_length = upk:unpackValue()

	if not keyName or type(keyName) ~= "string" then
		warning("<Lua DataBaseMsgCall.onMsgSaveDBTable> keyName failed")
		return
	end

	if not table_length or type(table_length) ~= "number" then
		warning("<Lua DataBaseMsgCall.onMsgSaveDBTable> table_type failed")
		return
	end

	local sql = string.format(sqls.tbGlobalDatasUpdate, table_length, keyName)
	local isOk = sgDataBaseServer:executeStmt(sql, upk)
	if not isOk then
		warning("<DataBaseMsgCall.onMsgSaveDBTable> executeStmt(" .. sql ..") is failed")
		return
	end
	--P.sendObject(MsgEnums.Msg_DBSaveDBTable, 0, {isOk})
end
------------------------------------------------------------------------
-- @brief 读取全局数据
-- @param[upk] 数据
function P.onMsgLoadDBTable(upk)
	local keyName = upk:unpackString()
	if not keyName or type(keyName) ~= "string" then
		warning("<Lua DataBaseMsgCall.onMsgSaveDBTable> keyName failed")
		return
	end
	sgPackMsg:packType(MsgEnums.Msg_DBLoadDBTable)
	sgPackMsg:packString(keyName)
	local sql = string.format(sqls.tbGlobalDatasSelectData, keyName)
	local isOk = sgDataBaseServer:executeSQL(sql)
	if not isOk then
		warning("<DataBaseMsgCall.onMsgLoadDBTable> executeSQL(" .. sql ..") is failed")
		return
	end
	P.sendPackMsg()
end
------------------------------------------------------------------------
-- @brief 创建一个用户
-- @param[upk] 数据
function P.onMsgNewUser(upk)
    local user = upk:unpackString()
    local password = upk:unpackString()
    local role_name = upk:unpackString()

	if not user or type(user) ~= "string" then
		warning("<Lua DataBaseMsgCall.onMsgNewUser> onMsgNewUser user failed")
		return
	end

    if not password or type(password) ~= "string" then
		warning("<Lua DataBaseMsgCall.onMsgNewUser> onMsgNewUser password failed")
		return
	end

    if not role_name or type(role_name) ~= "string" then
		warning("<Lua DataBaseMsgCall.onMsgNewUser> onMsgNewUser role_name failed")
		return
	end

    if P.findUser(user) then
        warning(string.format("find user(%s) in data base", user))
        return
    end

    
    if P.findRoleName(role_name) then
        warning(string.format("find role(%s) name in data base", role_name))
        return
    end

    -- 写入tb_login
    local role_id = sgDataBaseServer:allocGloablID()

    local sql = string.format(sqls.tbLoginInsert, user, password, role_name, role_id)
    local isOk = sgDataBaseServer:executeSQL(sql)
	if not isOk then
		warning("<DataBaseMsgCall.onMsgLoadDBTable> executeSQL(" .. sql ..") is failed")
		return
	end

    -- 写入tb_role
	local isOk = sgDataBaseServer:executeSQL(string.format(sqls.tbRoleInsert, role_name, role_id))
    if not isOk then
		warning("<DataBaseMsgCall.onMsgLoadDBTable> executeSQL(" .. sql ..") is failed")
		return
	end

    table.insert(Data.selectAllUser, user)
    table.insert(Data.selectAllNames, role_name)

    P.sendObject(MsgEnums.Msg_DBNewUser, 0, {isOk})
end
------------------------------------------------------------------------
-- @brief 登录一个用户
-- @param[upk] 数据
function P.onMsgLoginUser(upk)
    local user = upk:unpackString()
    local password = upk:unpackString()

	if not user or type(user) ~= "string" then
		warning("<Lua DataBaseMsgCall.onMsgNewUser> onMsgNewUser user failed")
		return
	end

    if not password or type(password) ~= "string" then
		warning("<Lua DataBaseMsgCall.onMsgNewUser> onMsgNewUser password failed")
		return
	end

    sgPackMsg:packType(MsgEnums.Msg_DBLoginUser)
    sgPackMsg:packString(user)
    local sql = string.format(sqls.tbLoginSelect, user, password)
    local isOk = sgDataBaseServer:executeSQL(sql)
	if not isOk then
		warning("<DataBaseMsgCall.onMsgLoadDBTable> executeSQL(" .. sql ..") is failed")
		return
	end
    
    P.sendPackMsg()
end
------------------------------------------------------------------------
-- @brief 给一个角色添加一条日志
-- @param[upk] 数据
function P.onMsgRoleAddNewLog(upk)
    local role_id = upk:unpackValue()
    local time = upk:unpackValue()
    local role_name = upk:unpackString()
    local type_name = upk:unpackString()

    if not role_name or type(role_name) ~= "string" then
		warning("<Lua DataBaseMsgCall.onMsgRoleAddNewLog> role_name failed")
		return
	end

    if not role_id or type(role_id) ~= "number" then
		warning("<Lua DataBaseMsgCall.onMsgRoleAddNewLog>  role_id failed")
		return
	end
    
    if not time or type(time) ~= "number" then
		warning("<Lua DataBaseMsgCall.onMsgRoleAddNewLog>  time failed")
		return
	end

	if not type_name or type(type_name) ~= "string" then
		warning("<Lua DataBaseMsgCall.onMsgRoleAddNewLog>  type_name failed")
		return
	end

    local sql = string.format(sqls.tbLogInsert, role_name, role_id, time, type_name)
    local isOk = sgDataBaseServer:executeStmt(sql, upk)
	if not isOk then
		warning("<DataBaseMsgCall.onMsgRoleAddNewLog> executeStmt(" .. sql ..") is failed")
		return
	end
end

------------------------------------------------------------------------
-- @brief 发送复合数据
-- @param[msgType] 消息类型
-- @param[role_id] 角色ID
-- @param[obj] 数据
function P.sendObject(msgType, role_id, obj)
	local netConnect = sgDataBaseServer:getCurNetConnect()
	if not netConnect then
		warning("<DataBaseMsgCall.sendObject> sendObject netConnect is nil")
		return
	end

	sgPackMsg:packType(msgType)
	sgPackMsg:packValue(role_id)
	sgPackMsg:packObject(obj)
	sgDataBaseServer:sendPackMsg(netConnect:getSessionID())
end
------------------------------------------------------------------------
-- @brief 发送包数据
function P.sendPackMsg()
	local netConnect = sgDataBaseServer:getCurNetConnect()
	if not netConnect then
		return
	end
	local sid = netConnect:getSessionID()
	sgDataBaseServer:sendPackMsg(sid)
end

return P