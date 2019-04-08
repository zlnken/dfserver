------------------------------------------------------------------------
-- @brief 安全数据表用来储存全局数据表
local MsgEnums = require("enum.MessageEnums")
------------------------------------------------------------------------
local P = class("SafeTable")
------------------------------------------------------------------------
-- @brief 无法确定的数据类型
P.ST_Unknow = 0
-- @brief 数组数据类型
P.ST_Array = 1
-- @brief 表数据类型
P.ST_Dict = 2
------------------------------------------------------------------------
-- @brief 构造函数
-- @param[st] 数据类型
-- @param[keyName] 对应数据库表名字
-- @param[who] 对应数据库ID
function P:ctor(st, keyName, who)
    self._keyName = keyName
    self._who = who
    self._type = st
    self._owner = {}
    self._length = 0
end


------------------------------------------------------------------------
-- @brief 是否是数组数据类型
-- @param[t] 表
function P:isArrayTable(t)
    if type(t) ~= "table" then 
        return false
    end
    local n = #t
    for i,v in pairs(t) do
        if type(i) ~= "number" then 
            return false
        end
        if i > n then  
            return false  
        end   
    end
    return true
end
------------------------------------------------------------------------
-- @brief 设置一个表
-- @param[data] 数据
function P:setTable(data)
    if self:isArrayTable(data) then
        self._owner = data
        self._length = #data
        self._type = P.ST_Array
    else
        self._owner = data
        self._type = P.ST_Dict
        self._length = 0
        for k,v in pairs(self._owner) do
            self._length = self._length + 1
        end
    end
end
------------------------------------------------------------------------
-- @brief 从对应数据库读取数据
function P:load()
    if not self._keyName or tolua.type(self._keyName) ~= "string" then
        warning("LUA <SafeTable:save> self._who is nil")
        return
    end

    if not self._who or tolua.type(self._who) ~= "number" then
        warning("LUA <SafeTable:save> self._who is nil")
        return
    end
    sgPackMsg:packType(MsgEnums.Msg_DBLoadDBTable)
    sgPackMsg:packString(self._keyName)
    sgLogicServer:sendWhoPackMsg(self._who)
end
------------------------------------------------------------------------
-- @brief 储存到对应数据库
function P:save()
    if not self._keyName or tolua.type(self._keyName) ~= "string" then
        warning("LUA <SafeTable:save> self._who is nil")
        return
    end

    if not self._who or tolua.type(self._who) ~= "number" then
        warning("LUA <SafeTable:save> self._who is nil")
        return
    end
    sgPackMsg:packType(MsgEnums.Msg_DBSaveDBTable)
    sgPackMsg:packString(self._keyName)
    sgPackMsg:packValue(self._length)
    sgPackMsg:packObject({self._owner})
    sgLogicServer:sendWhoPackMsg(self._who)
end
------------------------------------------------------------------------
-- @brief 是否字典
function P:getIsDict()
    return self._type == P.ST_Dict 
end
------------------------------------------------------------------------
-- @brief 插入数据(数组专用)
-- @param[index] 下标
-- @param[data] 数据
function P:insert(index, data)
    if type(index) ~= "number" then
        warning("LUA <SafeTable:insert> index type is not number")
        return
    end
    if P.ST_Array ~= self._type then
        warning("LUA <SafeTable:insert> table is not array")
        return
    end
    self._length = self._length + 1
    table.insert(self._owner, index, data)
end
------------------------------------------------------------------------
-- @brief 从最后面插入数据(数组专用)
-- @param[data] 数据
function P:pushBack(data)
    if type(index) ~= "number" then
        warning("LUA <SafeTable:insert> index type is not number")
        return
    end
    if P.ST_Array ~= self._type then
        warning("LUA <SafeTable:insert> table is not array")
        return
    end
    self._length = self._length + 1
    self._owner[self._length] = data
end
------------------------------------------------------------------------
-- @brief 从最前面插入数据(数组专用)
-- @param[data] 数据
function P:pushFront(data)
    self:insert(1, data)
end
------------------------------------------------------------------------
-- @brief 设置数据(表数据专用)
-- @param[key] 钥匙
-- @param[data] 数据
function P:setValue(key, data)
    if P.ST_Dict ~= self._type  then
        warning("LUA <SafeTable:setValue> table is not dict")
        return
    end
    self._length = self._length + 1
    self._owner[key] = data
end
------------------------------------------------------------------------
-- @brief 移除数据(数组数据专用)
-- @param[index] 下标
-- @param[func] 移除前回调
function P:removeByIndex(index, func)
    if type(index) ~= "number" then
        warning("LUA <SafeTable:insert> index type is not number")
        return
    end

    if P.ST_Array ~= self._type then
        warning("LUA <SafeTable:push> table is not array")
        return
    end

    if index >= self._length then
        warning("LUA <SafeTable:push> index(" .. tostring(index) .. ") out of range")
        return
    end

    if func then
        func(self._owner[index])        
    end

    table.remove(self._owner, index)
    self._length = math.max(0, self._length - 1) 
end

------------------------------------------------------------------------
-- @brief 移除数据(表数据专用)
-- @param[index] 钥匙
-- @param[func] 移除前回调
function P:removeByKey(key, func)
    if P.ST_Dict ~= self._type  then
        warning("LUA <SafeTable:setValue> table is not dict ")
        return
    end

    if func then
        func(self._owner[key])        
    end

    self._owner[key] = nil
    self._length = math.max(0, self._length - 1) 
end
------------------------------------------------------------------------
-- @brief 移除数据
-- @param[val] 值
-- @param[func] 移除前回调
function P:removeByValue(val, func)
    if P.ST_Array == self._type then
        for i, v in ipairs(self._owner) do
            if  v == val then
                self:removeByIndex(i, func)
                return
            end
        end
    else
        for k, v in pairs(self._owner) do
            if  v == val then
                self:removeByKey(k, func)
                return
            end
        end 
    end
end
------------------------------------------------------------------------
-- @brief 排序(数组专用)
-- @param[func] 排序函数
function P:sort(func)
    if P.ST_Array ~= self._type  then
        warning("LUA <SafeTable:setValue> table is not array")
        return
    end
    table.sort(self._owner, func)
end
return P
