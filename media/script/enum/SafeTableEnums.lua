------------------------------------------------------------------------
-- @brief ȫ�����ݱ�ö��
local SaveTable = require("core.SafeTable")
local ServerConfig = require("core.ServerConfig")
------------------------------------------------------------------------
local P = {}
-- Ĭ�����ݿ�id
local default_who = ServerConfig.default.id
------------------------------------------------------------------------
P.ST_Test1 = SaveTable.new(SaveTable.ST_Array, "ST_Test1", default_who)
P.ST_Test2 = SaveTable.new(SaveTable.ST_Dict, "ST_Test2", default_who)
return P