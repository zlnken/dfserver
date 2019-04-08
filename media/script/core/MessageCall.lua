------------------------------------------------------------------------
-- @brief 消息定义和分发
local P = class("MessageCall")
function P.getInstance()
	if not P.instance then
		P.instance = P.new()
	end
	return P.instance
end
------------------------------------------------------------------------
-- @brief 构造函数
function P:ctor()
	self._iMsgs = {}	
	self._size = 0
	self._sMsgs = {}
end
------------------------------------------------------------------------
-- @brief 创建一个消息
-- @param[name] 消息名
function P:createMessage(name)
	if self._sMsgs[name] then
		warning("<LUA:MessageCall:setMessage> has msg(" .. name .. ")")
		return
	end

	self._size = self._size + 1 
	local msg = {}
	msg._index = self._size
	msg._name = name
	msg._func = nil

	table.insert(self._iMsgs, msg)
	self._sMsgs[name] = msg
	return self._size
end
------------------------------------------------------------------------
-- @brief 移除一个消息
-- @param[idx] 消息下标
function P:removeMessageFunc(idx)
	if idx > self._size then
		warning("<LUA:MessageCall:removeMessageFunc> can not find idx(" .. tostring(idx) .. ")")
		return
	end
	self._iMsgs[idx]._func = nil	
end
------------------------------------------------------------------------
-- @brief 给一个消息设置回调函数
-- @param[idx] 下标
-- @param[func] 回调函数
function P:setMessageFunc(idx, func)
	if idx > self._size then
		warning("<LUA:MessageCall:setMessageFunc> can not find idx(" .. tostring(idx) .. ")")
		return
	end

	if not func then
		warning("<LUA:MessageCall:setMessageFunc> func is nil by msg(" .. self._iMsgs[idx]._name .. ")")
		return
	end

	self._iMsgs[idx]._func = func
end
------------------------------------------------------------------------
-- @brief 获取一个消息
-- @param[idx] 下标
function P:getMessage(idx)
	if idx > self._size then
		warning("<LUA:MessageCall:setMessageFunc> can not find idx(" .. tostring(idx) .. ")")
		return
	end
	return self._iMsgs[idx]
end
return P