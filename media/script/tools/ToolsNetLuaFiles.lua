------------------------------------------------------------------------
-- @brief 给客户端发送重新加载的lua文件数据
------------------------------------------------------------------------
local P = class("ToolsNetLuaFiles")
local ToolsLuaFileMgr = require("tools.ToolsLuaFileMgr")
------------------------------------------------------------------------
P._ToolsNetLuaFilesMgr = {}
------------------------------------------------------------------------
-- @brief 构造函数
function P:ctor(seccionID, roleName)
    self._keyQueue = {}
    self._sessionID = seccionID
    self._roleName = roleName
    self._curIndex = 1
    self._curPath = nil
end
------------------------------------------------------------------------
-- @brief 初始化
-- @param[seccionID] 唯一ID标识
function P:init()
    self._keyQueue ={}
    self._curIndex = 1
    self._isCleanData = true
    self._curPath = nil
    local files = ToolsLuaFileMgr.getInstance():getFiles()
    for k, _ in pairs(files) do
        table.insert(self._keyQueue, {path=k, pos=0})
    end   
end
------------------------------------------------------------------------
-- @brief 队列发送客户端
function P:updateLuaFile()
    -- 判断ID
    if not self._sessionID then
        warning(string.format("[ToolsNetLuaFiles:updateLuaFile] self._sessionID is nil"))
        return
    end
    -- 是否有连接
    local server = DF.LuaSystem:instancePtr():getServer()
--    print(self._sessionID)
--    if not server:hasConnect(self._sessionID) then
--        warning(string.format("[ToolsNetLuaFiles:updateLuaFile] not server:disConnect(self._sessionID)"))
--        return
--    end
    
    if self._isCleanData then
        local code = "clean_all_lua_files"
        server:sendBytes(self._sessionID, code, string.len(code))
        self._isCleanData = false
        return
    end
    -- 是否拥有数据
    local key_data = self._keyQueue[1]
    if not key_data then
        print(string.format("finish load all file by role[%s].", self._roleName))
        return
    end
    -- 发送数据前置条件
    local send_data = ToolsLuaFileMgr.getInstance():getFileByName(key_data.path)
    local data = send_data[self._curIndex]
    if not data then
        self._curIndex = 1
        table.remove(self._keyQueue, 1)
        local code = "save_one_lua_file"
        server:sendBytes(self._sessionID, code, string.len(code))
        print(string.format("load %s file by role[%s] end", key_data.path, self._roleName))
        return
    end

    if self._curPath ~= key_data.path then
        self._curPath = key_data.path
        local code = json.encode({mt="set_lua_file_path", text = key_data.path})
        server:sendBytes(self._sessionID, code, string.len(code))
        return
    end
    self._curIndex = self._curIndex + 1
    server:sendBytes(self._sessionID, data, #data)

end
------------------------------------------------------------------------
-- @brief 静态创建
-- @param[str] 代码 
function P:sendLoadString(str)
    -- 判断ID
    if not self._sessionID then
        warning(string.format("[ToolsNetLuaFiles:updateLuaFile] self._sessionID is nil"))
        return
    end
    -- 是否有连接
    local server = DF.LuaSystem:instancePtr():getServer()
    local code = json.encode({mt="tools_on_gm_load_string", text = str})
    server:sendBytes(self._sessionID, code, string.len(code))
end
------------------------------------------------------------------------
-- @brief 静态创建
-- @param[seccionID] 唯一ID标识
function P.screate(seccionID, roleName)
    if not P._ToolsNetLuaFilesMgr then
        P._ToolsNetLuaFilesMgr = {}
    end
    --  创建
    local nlf = P.new(seccionID, roleName)
    nlf:init()
    P._ToolsNetLuaFilesMgr[seccionID] = nlf
end
------------------------------------------------------------------------
-- @brief 查找
-- @param[seccionID] 唯一ID标识
function P.sfind(seccionID)
    return P._ToolsNetLuaFilesMgr[seccionID]
end
------------------------------------------------------------------------
-- @brief 静态创建
-- @param[seccionID] 唯一ID标识
function P.supdate()
    if not P._ToolsNetLuaFilesMgr then
        return
    end
    local server = DF.LuaSystem:instancePtr():getServer()
    local removes = {}
    for k, v in  pairs(P._ToolsNetLuaFilesMgr) do
        if not server:hasConnect(k) then
            print(k, v)
            table.insert(removes, k)
        end
    end
    for _, v in ipairs(removes) do
        P._ToolsNetLuaFilesMgr[v] = nil
    end
end
------------------------------------------------------------------------
-- @brief 队列发送客户端
function P.supdateLuaFile()
    for k, nlf in  pairs(P._ToolsNetLuaFilesMgr) do
        if nlf then
            nlf:init()
            nlf:updateLuaFile()
        end
    end
end

------------------------------------------------------------------------
-- @brief 队列发送客户端
function P.ssendLoadString(str)
    for k, nlf in pairs(P._ToolsNetLuaFilesMgr) do
        if nlf then
            print(nlf)
            nlf:sendLoadString(str)
        end
    end
end

return P