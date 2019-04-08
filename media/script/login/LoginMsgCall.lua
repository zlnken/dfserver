------------------------------------------------------------------------
-- @brief 登录服回调
--	local m = P.reload("login.LoginMsgCall")
--	m.load()
--
------------------------------------------------------------------------
local ServerConfig = require("core.ServerConfig")
local MessageCall = require("core.MessageCall")
local MsgEnums = require("enum.MessageEnums")
local SafeTableEnums = require("enum.SafeTableEnums")
local Data = require("login.LoginMsgData")
local msgcall = MessageCall.getInstance()
------------------------------------------------------------------------
local P = {}
------------------------------------------------------------------------
-- @brief 初始化数据
function P.initData()
    
end
------------------------------------------------------------------------
-- @brief 读取
function P.load()
	msgcall:setMessageFunc(MsgEnums.Msg_NewUser, P.onMsgNewUser)
    msgcall:setMessageFunc(MsgEnums.Msg_LoginUser, P.onMsgLoginUser)
	msgcall:setMessageFunc(MsgEnums.Msg_DBNewUser, P.onMsgNewUserCallBack)
    msgcall:setMessageFunc(MsgEnums.Msg_DBLoginUser, P.onMsgLoginUserCallBack)
end
------------------------------------------------------------------------
-- @brief 新建一个用户
function P.onMsgNewUser(upk)
    local world_id = upk:unpackValue()
    local user = upk:unpackString()
    local password = upk:unpackString()
    local role_name = upk:unpackString()

    if not world_id or type(world_id) ~= "number" then
		warning("<Lua DataBaseMsgCall.onMsgLoginUser> world_id failed")
		return
	end

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

    local netconnect = sgLoginServer:getCurNetConnect()
    if netconnect then
        Data.userConnects[user] = sgLoginServer:getCurNetConnect():getSessionID()
    end

    sgPackMsg:packType(MsgEnums.Msg_DBNewUser)
    sgPackMsg:packString(user)
    sgPackMsg:packString(password)
    sgPackMsg:packString(role_name)
    sgLoginServer:sendWhoPackMsg(world_id)
end
------------------------------------------------------------------------
-- @brief 新建一个用户
-- @param[upk] 数据
function P.onMsgLoginUser(upk)
    local world_id = upk:unpackValue()
    local user = upk:unpackString()
    local password = upk:unpackString()

    if not world_id or type(world_id) ~= "number" then
		warning("<Lua DataBaseMsgCall.onMsgLoginUser> world_id failed")
		return
	end

    if not user or type(user) ~= "string" then
		warning("<Lua DataBaseMsgCall.onMsgLoginUser> user failed")
		return
	end

    if not password or type(password) ~= "string" then
		warning("<Lua DataBaseMsgCall.onMsgLoginUser> password failed")
		return
	end

    local netconnect = sgLoginServer:getCurNetConnect()
    if netconnect then
        Data.userConnects[user] = sgLoginServer:getCurNetConnect():getSessionID()
    end


    sgPackMsg:packType(MsgEnums.Msg_DBLoginUser)
    sgPackMsg:packString(user)
    sgPackMsg:packString(password)
    sgLoginServer:sendWhoPackMsg(world_id)
end
------------------------------------------------------------------------
-- @brief 新建一个用户回调
-- @param[upk] 数据
function P.onMsgNewUserCallBack(upk)
    print("P.onMsgNewUserCallBack")
end

------------------------------------------------------------------------
-- @brief 登录一个用户
-- @param[upk] 数据
function P.onMsgLoginUserCallBack(upk)
    local user = upk:unpackString()
    local obj = upk:unpackObject()
    obj = obj[1]
    
    if not user or type(user) ~= "string" then
		warning("<Lua LoginMsgCall.onMsgNewUser> onMsgLoginUserCallBack user failed")
		return
	end

    if not obj then
        warning("<Lua LoginMsgCall.onMsgNewUser> onMsgLoginUserCallBack data failed")
        return
    end

    local role_id = obj[1]
    if not role_id or type(role_id) ~= "number" then
		warning("<Lua LoginMsgCall.onMsgNewUser> onMsgLoginUserCallBack role_id failed")
		return
	end
    local sessionId =  Data.userConnects[user]
    if sessionId then
        P.sendObject(sessionId, MsgEnums.Msg_LoginUser, role_id)
    end
end
------------------------------------------------------------------------
-- @brief 发送数据
-- @param[who] 数据库id
-- @param[msgType] 消息类型
-- @param[role_id] 角色ID
-- @param[obj] 数据
function P.sendObject(who, msgType, role_id, obj)
	sgPackMsg:packType(msgType)
	sgPackMsg:packValue(role_id)
    if obj then
	    sgPackMsg:packObject(obj)
    end
	sgLoginServer:sendPackMsg(who)
end

return P