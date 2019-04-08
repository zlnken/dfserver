------------------------------------------------------------------------
-- @brief GM工具
--	local m = P.reload("tools.ToolsServerMsg")
--	m.load()
--
------------------------------------------------------------------------
local ToolsLuaFileMgr = require("tools.ToolsLuaFileMgr")
local ToolsNetLuaFiles = require("tools.ToolsNetLuaFiles")
------------------------------------------------------------------------
local P = {}
------------------------------------------------------------------------
-- @brief 重新加载
function P.load()
    -- 在线加载你需要的东西
end
------------------------------------------------------------------------
-- @brief 读取
function P.gmLoadAllLuaFiles()
    ToolsLuaFileMgr:getInstance():loadAllFiles("./media/files/lua/", "")
    ToolsNetLuaFiles.supdateLuaFile()
end
------------------------------------------------------------------------
-- @brief 发送文本GM命令
function P.gmSendLoadString()
    local rootPath = DF.LuaSystem:instancePtr():getRootPath()
    local filepath = "media/script/tools/ToolSendStringFile.lua"
    local fullPath = rootPath .. filepath
    local f = io.open(fullPath)
    if not f then
        fullPath = rootPath .. "../../../" .. filepath
        f = io.open(fullPath)
        if not f then
            warning(string.format("LUA [ToolsServerMsg:gmSendLoadString] can not load [%s] file.", filepath))
            return
        end
    end
    local str = f:read("*a")
    f:close()
    print(str)
    ToolsNetLuaFiles.ssendLoadString(str)
end
------------------------------------------------------------------------
-- @brief 运行GM命令
function P.run()
    --P.gmLoadAllLuaFiles()
    P.gmSendLoadString()
end
------------------------------------------------------------------------
return P