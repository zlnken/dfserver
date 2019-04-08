------------------------------------------------------------------------
-- @brief 工具服务器回调主要从C++回调
------------------------------------------------------------------------
sgLogServer = DF.LuaSystem:instancePtr():getServer()
sgUnpackMsg = sgLogServer:getUnpackMessage()
sgPackMsg = sgLogServer:getPackMessage()
------------------------------------------------------------------------
require("common.functions")
local CLuaTrigger = require ("core.CLuaTrigger")
local ToolsNetLuaFiles = require("tools.ToolsNetLuaFiles")
------------------------------------------------------------------------
sgToolsServerCall = {}
local P = sgToolsServerCall
------------------------------------------------------------------------
-- @brief 初始化触发器
-- @param[type] 类型
-- @param[func] 触发器回调
function P.initTrigger(type, func)
	local tri = CLuaTrigger:new()
	tri:push(func)
	sgLogServer:setTrigger(type, tri)
end
------------------------------------------------------------------------
function P.initLogServer()
	P.initTrigger(DF.BaseServer.BSTE_OnStar, P.onStar)
	P.initTrigger(DF.BaseServer.BSTE_OnMsg, P.onMsg)
	P.initTrigger(DF.BaseServer.BSTE_OnLost, P.onLost)
	P.initTrigger(DF.BaseServer.BSTE_KeyboardKeyDown, P.callKeyBoardKeyDown)
    P.initTrigger(DF.BaseServer.BSTE_AfterNewMinute, P.callAfterNewMinute)
end
------------------------------------------------------------------------
--  @brief 开始逻辑
function P.onStar()

end
------------------------------------------------------------------------
--  @brief 丢失
function P.onLost()
end
------------------------------------------------------------------------
--  @brief 响应键盘
-- @param[msg] 键盘消息
function P.callKeyBoardKeyDown(msg)
	local keyCode = msg:getType()
	if keyCode == 0x7B then
        printInfo("LogServerCall.callKeyBoardKeyDown runing...")
        package.loaded["tools.ToolsServerGM"] = nil
		local gm = require("tools.ToolsServerGM")
        gm.run()
	end
end
------------------------------------------------------------------------
-- @brief 每分钟回调之后
function P.callAfterNewMinute()
	ToolsNetLuaFiles.supdate()
end
------------------------------------------------------------------------
--  @brief 响应消息
-- @param[msg] 消息
function P.onMsg(msg)
	sgUnpackMsg:reset(msg)
	sgUnpackMsg:unpackMsg()
    local s = sgUnpackMsg:unpackString()
    local bufmsg = json.decode(s)
    package.loaded["tools.ToolsServerMsg"] = nil
    local ToolsServerMsg = require("tools.ToolsServerMsg")
    ToolsServerMsg.onMsg(bufmsg)
end
P.initLogServer()