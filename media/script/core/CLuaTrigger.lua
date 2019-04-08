------------------------------------------------------------------------
-- @brief 触发器可以从c++回调
------------------------------------------------------------------------
local P = class("CLuaTrigger", function()
    return DF.LuaTrigger:screate()
end)
------------------------------------------------------------------------
-- @brief 析构函数
function P:dtor()
    self.handleArray = {}
end
------------------------------------------------------------------------
-- @brief 构造函数
function P:ctor()
    self.handleArray = {}
    self:pushFunction(DF.LuaTrigger.LTE_Dtor, DF.LuaFunction:screate("CLuaTrigger_dtor", self.dtor))
    self:pushFunction(DF.LuaTrigger.LTE_Clear, DF.LuaFunction:screate("CLuaTrigger_clear", self.clear))
    self:pushFunction(DF.LuaTrigger.LTE_TriMsg, DF.LuaFunction:screate("CLuaTrigger_triggering", self.trigering))
    self:pushFunction(DF.LuaTrigger.LTE_TriNone, DF.LuaFunction:screate("CLuaTrigger_trigerNone", self.trigerNone))
end
------------------------------------------------------------------------
-- @brief 给触发器添加一个回调函数
-- @param[func] 回调函数
function P:push(func)
    local index = #self.handleArray + 1
    table.insert(self.handleArray, index, func)
end
------------------------------------------------------------------------
--  @brief 清空回调函数
function P:clear()
    self.handleArray = {}
end
------------------------------------------------------------------------
-- @brief 触发一个消息
-- @param[msg] 消息数据
function P:trigering(msg)
    for i, func in ipairs(self.handleArray) do
        func(msg)
    end
end
------------------------------------------------------------------------
--  @brief 触发一个无消息回调
function P:trigerNone()
    for i, func in ipairs(self.handleArray) do
        func()
    end
end

return P
