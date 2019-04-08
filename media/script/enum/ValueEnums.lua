------------------------------------------------------------------------
-- @brief 角色单一数据规则枚举
local RuleManager = require("core.RuleManager")
local EventEmums = require("enum.EventEnums")
------------------------------------------------------------------------
local P = {}
------------------------------------------------------------------------
if 0 == RuleManager.getInstance():getValueSize() then
	RuleManager.getInstance():initValueRuleSize(128)
end
local R = RuleManager.getInstance()
------------------------------------------------------------------------
local syncClient = true             -- 同步给客户端
local notSyncClient = false         -- 不同步给客户端
local hasLog = true                 -- 有日志
local notLog = false                -- 没日志
local index = 0                     -- 默认下标
local notEvent = nil                -- 是否有事件
------------------------------------------------------------------------
-- @brief 注册一个枚举
-- @param[ync] 是否同步给客户端
-- @param[event] 事件
-- @param[isLog] 是否有日志
-- @param[clearTime] 清空时间
local function SVR(name, ync, range, clearTime, isLog, event)
	index = index + 1
	R:setValueRule(index, name, ync, range, clearTime, isLog, event)
	return index
end
------------------------------------------------------------------------
P.Val_RoleID = SVR("Val_RoleID", syncClient, R.range_double, R.notClear, notLog, notEvent)
P.Val_OffLineTime= SVR("Val_OffLineTime", syncClient, R.range_double, R.notClear, notLog, notEvent)
P.Val_LoginTime = SVR("Val_LoginTime", syncClient, R.range_double, R.notClear, notLog, notEvent)

P.Val_Test1 = SVR("Val_Test1", syncClient, R.range_int8, R.weekClear, hasLog, notEvent)
P.Val_Test2 = SVR("Val_Test2", syncClient, R.range_int16, R.notClear, notLog, notEvent)
P.Val_Test3 = SVR("Val_Test3", syncClient, R.range_int32, R.notClear, notLog, notEvent)
------------------------------------------------------------------------
return P