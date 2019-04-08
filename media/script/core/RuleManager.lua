------------------------------------------------------------------------
-- @brief 角色数据规则
local P = class("RuleManager")
------------------------------------------------------------------------
-- @brief 数据永久不清除
P.notClear = 0
-- @brief 每日清除数据
P.dayClear = 1
-- @brief 每周清除数据
P.weekClear = 2
-- @brief 每月清除数据
P.monthClear = 3
-- @brief 数据取值范围
P.range_int8 = {DF.Config.MIN_INT8, DF.Config.MAX_INT8}
P.range_int16 = {DF.Config.MIN_INT16, DF.Config.MAX_INT16}
P.range_int32 = {DF.Config.MIN_INT32, DF.Config.MAX_INT32}
P.range_uint32 ={0, DF.Config.MAX_UINT32}
P.range_float = {DF.Config.MIN_FLOAT, DF.Config.MAX_FLOAT}
P.range_double = {DF.Config.MIN_DOUBLE, DF.Config.MAX_DOUBLE}

------------------------------------------------------------------------
-- @brief 单例
function P.getInstance()
	if not P.instance then
		P.instance = P.new()
	end
	return P.instance
end
------------------------------------------------------------------------
-- @brief 构造函数
function P:ctor()
    self._valueSize = 0
    self._valueRules = {}
    self._objectSize = 0
    self._objectRules = {}
end
------------------------------------------------------------------------
-- @brief 获取单一数据规则大小
function P:getValueSize()
	return self._valueSize
end
------------------------------------------------------------------------
-- @brief 获取复合数据规则大小
function P:getObjectSize()
	return self._objectSize
end
------------------------------------------------------------------------
-- @brief 获取单一数据规则
function P:getValueRuleArray()
	return self._valueRules
end
------------------------------------------------------------------------
-- @brief 获取复合数据规则
function P:getObjectRuleArray()
	return self._objectRules
end
------------------------------------------------------------------------
-- @brief 获取单一数据规则
-- @param[idx] 下标
function P:getValueRule(idx)
	if idx >= self._valueSize then
		warning("<LUA RoleManager:getValueRule> index out of range")
		return nil
	end
	return self._valueRules[idx]
end
------------------------------------------------------------------------
-- @brief 获取复合数据规则
-- @param[idx] 下标
function P:getObjectRule(idx)
	if idx >= self._objectSize then
		warning("<LUA RoleManager:getObjectRule> index out of range")
		return nil
	end
	return self._objectRules[idx]
end
------------------------------------------------------------------------
-- @brief 初始化单一数据规则大小
-- @param[size] 大小
function P:initValueRuleSize(size)
	if #self._valueRules > 0 then
		warning("<LUA RoleManager:initValueRuleSize> index out of range")
		return
	end
	for i=1, size do
		table.insert(self._valueRules, i, "nil")
	end
end
------------------------------------------------------------------------
-- @brief 初始化复合数据规则大小
-- @param[size] 大小
function P:initObjectRuleSize(size)
	if #self._objectRules > 0 then
		warning("<LUA RoleManager:initValueRuleSize> index out of range")
		return
	end
	for i=1, size do
		table.insert(self._objectRules, i, "nil")
	end
end
------------------------------------------------------------------------
-- @brief 设置一个单一数据规则
-- @param[idx] 下标
-- @param[name] 名字
-- @param[isSyncClient] 是否同步给客户端
-- @param[event] 事件
-- @param[isLog] 是否有日志
-- @param[range] 取值范围
-- @param[clearTime] 清空标志
function P:setValueRule(idx, name, isSyncClient, range, clearTime, isLog, event)
	if idx >= #self._valueRules then
		warning("<LUA RoleManager:setValueRule> index out of range")
		return
	end
	local vr = self._valueRules[idx]
	if vr ~= "nil" then
		warning("<LUA RoleManager:setValueRule> repeat set int(" .. tostring(vr._idx) .. ") rule")
		return
	end
	vr = {}
	vr._idx = idx
	vr._name = name
	vr._isSyncClient = isSyncClient
	vr._event = event
	vr._isLog = isLog
	vr._min = range[1]
	vr._max = range[2]
	vr._clearTime = clearTime
	vr._setCount = 0
	self._valueRules[idx] = vr
	self._valueSize = self._valueSize + 1     
end
------------------------------------------------------------------------
-- @brief 设置一个复合数据规则
-- @param[idx] 下标
-- @param[name] 名字
-- @param[isSyncClient] 是否同步给客户端
-- @param[event] 事件
-- @param[isLog] 是否有日志
-- @param[clearTime] 清空标志
function P:setObjectRule(idx, name, isSyncClient, clearTime, isLog, event)
	if idx >= #self._objectRules then
		warning("<LUA RoleManager:setObjectRule> index out of rang")
		return
	end

	local vr = self._objectRules[idx]
	if vr ~= "nil" then
		warning("<LUA RoleManager:setObjectRule> repeat set int(" .. tostring(vr._idx) .. ") rule")
		return
	end
	vr = {}
	vr._idx = idx
	vr._name = name
	vr._isSyncClient = isSyncClient
	vr._event = event
	vr._isLog = isLog
	vr._clearTime = clearTime
	self._objectRules[idx] = vr
	self._objectSize = self._objectSize + 1 
end
------------------------------------------------------------------------
return P
