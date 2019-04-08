------------------------------------------------------------------------
-- @brief 事件触发器
------------------------------------------------------------------------
local P = class("FilesManager")
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
	local f = io.open(file_path, "rb")
	if not f then
		warning(string.format("LUA <FilesManager:loadFile> can not found %s file.", path))
		return
	end

	-- 解压
	local data = json.decode(f:read("*a"))
	
	-- 关闭文件流
	f:close()

	-- 检查json是否正确
	if not data then
		warning(string.format("LUA <FilesManager:loadFile> json error by %s file.", path))
		return
	end

	self._files[file] = data
end
------------------------------------------------------------------------
-- @brief 读取全部
function P:loadAll()
	local files = DF.LuaSystem:instancePtr():loadFiles()
	for path, file in pairs(files) do
		self:loadFile(path, file)
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
-- @brief 清空
function P:clear()
	self._files = {}
end

return P