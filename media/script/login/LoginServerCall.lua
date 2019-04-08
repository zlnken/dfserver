sgLoginServer = DF.LuaSystem:instancePtr():getServer()
sgUnpackMsg = sgLoginServer:getUnpackMessage()
sgPackMsg = sgLoginServer:getPackMessage()
------------------------------------------------------------------------
require("common.functions")
local ServerConfig = require("core.ServerConfig")
local MessageCall = require("core.MessageCall")
local RoleManager = require("core.RoleManager")
local SafeTableEnums = require("enum.SafeTableEnums")
local SafeTable = require("core.SafeTable")
local MsgEnums = require("enum.MessageEnums")
local CLuaTrigger = require ("core.CLuaTrigger")
local LoginMsgCall = require ("login.LoginMsgCall")

------------------------------------------------------------------------
sgLoginServerCall = {}
local P = sgLoginServerCall
------------------------------------------------------------------------
-- @brief ��ʼ��������
-- @param[type] ����
-- @param[func] �������ص�
function P.initTrigger(type, func)
	local tri = CLuaTrigger:new()
	tri:push(func)
	sgLoginServer:setTrigger(type, tri)
end
------------------------------------------------------------------------
function P.initLogicServer()
	P.initTrigger(DF.BaseServer.BSTE_OnStar, P.onStar)
	P.initTrigger(DF.BaseServer.BSTE_OnMsg, P.onMsg)
	P.initTrigger(DF.BaseServer.BSTE_OnLost, P.onLost)
	P.initTrigger(DF.BaseServer.BSTE_KeyboardKeyDown, P.callKeyBoardKeyDown)
end
------------------------------------------------------------------------
--  @brief ��ʼ�߼�
function P.onStar()
	local s = ServerConfig.default
	sgLoginServer:connect(s.ip, s.server_port, s.id)

    LoginMsgCall.initData()
    LoginMsgCall.load()
end
------------------------------------------------------------------------
--  @brief ��ʧ
function P.onLost()
end
------------------------------------------------------------------------
--  @brief ��Ӧ����
-- @param[msg] ������Ϣ
function P.callKeyBoardKeyDown(msg)
	local keyCode = msg:getType()
	if keyCode == 0x7B then
        print("LoginServer.callKeyBoardKeyDown runing...")
		package.loaded["gm.GameMaster"] = nil
		require("gm.GameMaster"):runScript()
	end
end
------------------------------------------------------------------------
--  @brief ��Ӧ��Ϣ
-- @param[msg] ��Ϣ
function P.onMsg(msg)
	local msgType = msg:getType()
	local msgCall = MessageCall.getInstance():getMessage(msgType)

	if not msgCall then
		warning("LUA can not found msgCall._func msg(" .. tostring(msgType) .. ")")
		return
	end

	if not msgCall._func then
		warning("LUA can not found msgCall._func msg(" .. msgCall._name .. ")")
        sgPackMsg:packType(MsgEnums.Msg_Error)
        sgPackMsg:packString("LUA can not found msgCall._func msg(" .. msgCall._name .. ")")
	    sgLoginServer:sendPackMsg(sgLoginServer:getCurNetConnect():getSessionID())
		return
	end 
	sgUnpackMsg:reset(msg)
	sgUnpackMsg:unpackMsg()
	msgCall._func(sgUnpackMsg)
end
P.initLogicServer()