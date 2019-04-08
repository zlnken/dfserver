------------------------------------------------------------------------
-- @brief 邮件回调
--	local m = P.reload("tools.ToolsServerMsg")
--	m.load()
--
------------------------------------------------------------------------
local ToolsLuaFileMgr = require("tools.ToolsLuaFileMgr")
local ToolsNetLuaFiles = require("tools.ToolsNetLuaFiles")
------------------------------------------------------------------------
local P = {}
------------------------------------------------------------------------
-- @brief 初始化数据
function P.onMsg(msg)
    local server = DF.LuaSystem:instancePtr():getServer()
    local curnet = server:getCurNetConnect()
    -- 登录消息
    if msg.mt == "login" then
        ToolsNetLuaFiles.screate(curnet:getSessionID(), msg.text)
        printInfo(msg.text)
    -- 打印消息
    elseif msg.mt == "print" then
        printInfo(msg.text)
    -- 读取文件消息
    elseif msg.mt == "load_lua_files" then
        local nlf = ToolsNetLuaFiles.sfind(curnet:getSessionID())
        if nlf then
            nlf:updateLuaFile()
        end
    end  
end
------------------------------------------------------------------------
return P