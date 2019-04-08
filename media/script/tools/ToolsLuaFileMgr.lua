------------------------------------------------------------------------
-- @brief Lua文件管理器主要用来加载media/files/lua/目录下的所有文件
------------------------------------------------------------------------
local P = class("ToolsLuaFileMgr")
------------------------------------------------------------------------
-- @brief 构造函数
function P:ctor()
    self._files = {}
    self._rootPath = DF.LuaSystem:instancePtr():getRootPath()
end
------------------------------------------------------------------------
-- @brief 单例
function P.getInstance()
	if not P.instance then
		P.instance = P.new()
	end
	return P.instance
end
------------------------------------------------------------------------
-- @brief 读取一个文件
-- @param[path] 文件名
function P:loadFile(path, file)
	-- 检查是否是空的
	if not path then
		warning("LUA <FilesManager:loadFile> path is nil.")
		return
	end
	-- 检查是否是字符串
	if type(path) ~= "string" then
		warning("LUA <FilesManager:loadFile> path is not string type.")
		return
	end

	if not file then
		warning("LUA <FilesManager:loadFile> file is nil.")
		return
	end
	-- 检查是否是字符串
	if type(file) ~= "string" then
		warning("LUA <FilesManager:loadFile> file is not string type.")
		return
	end

	-- 读取文件数据
	local file_path = self._rootPath .. path .. file
	local f = io.open(file_path, "r")
	if not f then
        file_path = self._rootPath .. "../../../" .. path .. file
        f = io.open(file_path, "r")
        if not f then
		    warning(string.format("LUA <FilesManager:loadFile> can not found %s file.", path))
		return
        end
	end
    local data = {}
    while true do
        local d = f:read(6400)
        if not d then
            break
        end
        table.insert(data, d)
    end

	-- 解压
	-- 关闭文件流
	f:close()
    local name = string.split(file, ".")[1]
    name = string.gsub(name, "/", ".")
	self._files[name] = data
    printInfo("load file [" .. name .. "]")
end
------------------------------------------------------------------------
-- @brief 读取所有文件
-- @param[rootPath] 路径
function P:loadAllFiles(rootPath)
    printInfo("==========================load lua files==============================")
    self._files = {}
    local files = DF.LuaSystem:instancePtr():loadAllFiles(rootPath, "")
    self:dumpAllFiles(rootPath, "", files)
    printInfo("==========================load lua files==============================")
end
------------------------------------------------------------------------
-- @brief 递归所有文件
-- @param[rootPath] 路径
function P:dumpAllFiles(rootPath, path, files)
    for k, v in pairs(files) do
        if type(v) == "table" then
            self:dumpAllFiles(rootPath, k, v)
        else
            self:loadFile(rootPath, path .. v)
        end        
    end
end
------------------------------------------------------------------------
-- @brief 清空
function P:getFileByName(path)
	-- 检查是否是空的
	if not path then
		warning("LUA <FilesManager:loadFile> path is nil.")
		return
	end
	-- 检查是否是字符串
	if type(path) ~= "string" then
		warning("LUA <FilesManager:loadFile> path is not string type.")
		return
	end
	return self._files[path]
end

------------------------------------------------------------------------
-- @brief 获取文件容器
function P:getFiles()
    return self._files
end
------------------------------------------------------------------------
-- @brief 清空
function P:clear()
	self._files = {}
end


return P