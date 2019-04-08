------------------------------------------------------------------------
-- @brief 逻辑服回调
sgLogicServer = DF.LuaSystem:instancePtr():getServer()
sgUnpackMsg = sgLogicServer:getUnpackMessage()
sgPackMsg = sgLogicServer:getPackMessage()
------------------------------------------------------------------------
require("common.functions")
local ServerConfig = require("core.ServerConfig")
local MessageCall = require("core.MessageCall")
local RoleManager = require("core.RoleManager")
local SafeTableEnums = require("enum.SafeTableEnums")
local SafeTable = require("core.SafeTable")
local FilesManager = require("core.FilesManager")
local MsgEnums = require("enum.MessageEnums")
local CLuaTrigger = require ("core.CLuaTrigger")
local GameMaster = require("gm.GameMaster")

local msgcall = MessageCall.getInstance()

------------------------------------------------------------------------
sgLogicServerCall = {}
local P = sgLogicServerCall
------------------------------------------------------------------------
-- @brief 初始化数据服一个触发器
-- @param[type] 类型
-- @param[func] 回调函数
function P.initTrigger(type, func)
	local tri = CLuaTrigger:new()
	tri:push(func)
	sgLogicServer:setTrigger(type, tri)
end
------------------------------------------------------------------------
-- @brief 初始化逻辑服回调
function P.initLogicServer()
	P.initTrigger(DF.BaseServer.BSTE_OnStar, P.onStar)
	P.initTrigger(DF.BaseServer.BSTE_OnMsg, P.onMsg)
	P.initTrigger(DF.BaseServer.BSTE_OnLost, P.onLost)
	P.initTrigger(DF.BaseServer.BSTE_BeforeNewMinute, P.callBeforeNewMinute)
	P.initTrigger(DF.BaseServer.BSTE_BeforeNewHour, P.callBeforeNewHour)
	P.initTrigger(DF.BaseServer.BSTE_BeforeNewDay, P.callBeforeNewDay)
	P.initTrigger(DF.BaseServer.BSTE_AfterNewMinute, P.callAfterNewMinute)
	P.initTrigger(DF.BaseServer.BSTE_AfterNewHour, P.callAfterNewHour)
	P.initTrigger(DF.BaseServer.BSTE_AfterNewDay, P.callAfterNewDay)
	P.initTrigger(DF.BaseServer.BSTE_PerSecond, P.callPreScond)
	P.initTrigger(DF.BaseServer.BSTE_KeyboardKeyDown, P.callKeyBoardKeyDown)

    -- 初始化文件系统
    --FilesManager.getInstance():loadAll()

	-- 初始化角色管理
	RoleManager.getInstance()

	-- 全局数据读取
	msgcall:setMessageFunc(MsgEnums.Msg_DBLoadDBTable, P.onMsgLoadSafeTable)

    -- 初始化GM数据
    GameMaster.initData()
    GameMaster.load()

end
------------------------------------------------------------------------
-- @brief 开始
function P.onStar()


	local s = ServerConfig.default
	sgLogicServer:connect(s.ip, s.server_port, s.id)

	P.safe_tables = {}
	for k, sb in pairs(SafeTableEnums) do
		if sb._keyName and sb._who then
			table.insert(P.safe_tables, sb)
		end
	end

	P.loadNextSafeTables()
end
------------------------------------------------------------------------
-- @brief 读取全局数据表
function P.loadNextSafeTables()
	local sb = table.remove(P.safe_tables, 1)
	if sb then
		sb:load()
    else
        printInfo("LUA <sgLogicServerCall.loadNextSafeTables> load global data finish")
	end
end
------------------------------------------------------------------------
-- @brief 断开链接回调
function P.onLost()
	
end
------------------------------------------------------------------------
-- @brief 每天回调之前
function P.callBeforeNewDay()
    printInfo("callBeforeNewDay......")
    
end
------------------------------------------------------------------------
-- @brief 每小时回调之前
function P.callBeforeNewHour()
    printInfo("callBeforeNewHour......")
    for k, sb in pairs(SafeTableEnums) do
        sb:save()
    end
end
------------------------------------------------------------------------
-- @brief 每分钟回调之前
function P.callBeforeNewMinute()
	printInfo("callBeforeNewMinute......")
end
------------------------------------------------------------------------
-- @brief 每天回调之后
function P.callAfterNewDay()
    printInfo("callAfterNewDay......")
    RoleManager.getInstance():callAfterNewDay()
end
------------------------------------------------------------------------
-- @brief 每小时回调之就后
function P.callAfterNewHour()
    printInfo("callAfterNewHour......")
end
------------------------------------------------------------------------
-- @brief 每分钟回调之后
function P.callAfterNewMinute()

end
------------------------------------------------------------------------
-- @brief 每秒回调
function P.callPreScond()
    RoleManager.getInstance():updateSaveRoles()
end
------------------------------------------------------------------------
-- @brief 键盘响应
-- @param[msg] 消息
function P.callKeyBoardKeyDown(msg)
	local keyCode = msg:getType()
	if keyCode == 0x7B then
        printInfo("LogicServerCall.callKeyBoardKeyDown runing...")
		package.loaded["gm.GameMaster"] = nil
		local gm = require("gm.GameMaster")
        gm:load()
        gm:runScript()
	end
end
------------------------------------------------------------------------
-- @brief 消息分发
-- @param[msg] 消息
function P.onMsg(msg)
	local msgType = msg:getType()
	local msgCall = MessageCall.getInstance():getMessage(msgType)

	if not msgCall then
        warning("LUA can not found msgCall._func msg(" .. tostring(msgType) .. ")")
        sgPackMsg:packType(MsgEnums.Msg_Error)
        sgPackMsg:packString("LUA can not found msgCall._func msg(" .. msgCall._name .. ")")
	    sgDataBaseServer:sendPackMsg(sgLoginServer:getCurNetConnect():getSessionID())
		return
	end

	if not msgCall._func then
		warning("LUA can not found msgCall._func msg(" .. msgCall._name .. ")")
		return
	end 
	sgUnpackMsg:reset(msg)
	sgUnpackMsg:unpackMsg()
	msgCall._func(sgUnpackMsg)
end
------------------------------------------------------------------------
-- @brief 全局数据读取回调
-- @param[upk] 数据
function P.onMsgLoadSafeTable(upk)
	local key_name = upk:unpackString()
	local data = upk:unpackObject()[1]
	local table_length = data[1]
	local safe_table_data = data[2] 

	if not safe_table_data then
		P.loadNextSafeTables()
		return
	end

	if not key_name or type(key_name) ~= "string" then
		warning("LUA sgLogicServerCall.onMsgLoadSafeTable key_name is failed")
		P.loadNextSafeTables()
		return
	end 

	if not table_length or type(table_length) ~= "number" then
		warning("LUA sgLogicServerCall.onMsgLoadSafeTable table_type is failed")
		P.loadNextSafeTables()
		return
	end 
	local sb = SafeTableEnums[key_name] 
	sb._length = table_length
	sb._owner = safe_table_data
end

P.initLogicServer()