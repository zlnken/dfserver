------------------------------------------------------------------------
-- @brief 角色复合数据规则枚举
local RuleManager = require("core.RuleManager")
local EventEmums = require("enum.EventEnums")
------------------------------------------------------------------------
local P = {}
------------------------------------------------------------------------
if 0 == RuleManager.getInstance():getObjectSize() then
	RuleManager.getInstance():initObjectRuleSize(16)
end
local R = RuleManager.getInstance()
------------------------------------------------------------------------
local syncClient = true             -- 同步给客户端
local notSyncClient = false         -- 不同步给客户端
local hasLog = true                 -- 有日志
local notLog = false                -- 没日志
local index = 0                     -- 默认下标
local notEvent = nil                -- 没有触发事件 
------------------------------------------------------------------------
-- @brief 注册一个枚举
-- @param[ync] 是否同步给客户端
-- @param[event] 事件
-- @param[isLog] 是否有日志
-- @param[clearTime] 清空时间
local function SOR(name, ync, clearTime, isLog, event)
	index = index + 1
	R:setObjectRule(index, name, ync, clearTime, isLog, event)
	return index
end
------------------------------------------------------------------------
P.Obj_Test0 = SOR("Obj_Test0", syncClient, R.notClear, notLog, notEvent)
P.Obj_Test1 = SOR("Obj_Test1", syncClient, R.notClear, notLog, notEvent)
------------------------------------------------------------------------
return P