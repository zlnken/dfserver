------------------------------------------------------------------------
-- @brief 事件触发器
------------------------------------------------------------------------
local P = class("EventTrigger")
------------------------------------------------------------------------
-- @brief 构造函数
function P:ctor()
    self._handleArray = {}
end
------------------------------------------------------------------------
-- @brief 给触发器添加一个回调函数
-- @param[func] 回调函数
function P:push(func)
    table.insert(self._handleArray, func)
end
------------------------------------------------------------------------
-- @brief 给触发器添加一个回调函数
-- @param[func] 回调函数
function P:pushFont(func)
    table.insert(self._handleArray, 1, func)
end
------------------------------------------------------------------------
-- @brief 移除一个回调函数
function P:remove(func)
    local removeIndex = nil
    for i, call in ipairs(self._handleArray) do
        if func == cll then
            table.remove(self._handleArray, i)
            return
        end 
    end
end
------------------------------------------------------------------------
-- @brief 给触发器添加一个回调函数
-- @param[func] 回调函数
function P:insert(index, func)
    if index <= 0 or index >= #self._handleArray then
        warning("LUA <EventTrigger:insert> index of range by " .. index)
        return
    end
    table.insert(self._handleArray, index, func)
end
------------------------------------------------------------------------
--  @brief 清空回调函数
function P:clear()
    self._handleArray = {}
end
------------------------------------------------------------------------
-- @brief 触发一个消息
-- @param[msg] 消息数据
function P:trigerMsg(msg)
    for i, func in ipairs(self._handleArray) do
        func(msg)
    end
end
------------------------------------------------------------------------
--  @brief 触发一个无消息回调
function P:trigerNone()
    for i, func in ipairs(self._handleArray) do
        func()
    end
end
------------------------------------------------------------------------
--  @brief 触发一个回调
function P:trigering(...)
    for i, func in ipairs(self._handleArray) do
        func(...)
    end
end

return P
