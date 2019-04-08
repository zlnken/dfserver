------------------------------------------------------------------------
-- @brief 全局数据表枚举
local SaveTable = require("core.SafeTable")
local ServerConfig = require("core.ServerConfig")
------------------------------------------------------------------------
local P = {}
-- 默认数据库id
local default_who = ServerConfig.default.id
------------------------------------------------------------------------
P.ST_Test1 = SaveTable.new(SaveTable.ST_Array, "ST_Test1", default_who)
P.ST_Test2 = SaveTable.new(SaveTable.ST_Dict, "ST_Test2", default_who)
return P