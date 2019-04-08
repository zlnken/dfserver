------------------------------------------------------------------------
-- @brief  角色类加载数据库到内存
-- @brief 加载模块
local P = class("Role")
local RuleManager = require("core.RuleManager")
local MsgEnums = require("enum.MessageEnums")
local ValueEnums = require("enum.ValueEnums")
local ObjectEnums = require("enum.ObjectEnums")
local ruleMgr = RuleManager.getInstance()
------------------------------------------------------------------------
-- @brief 构造函数
-- @param[roleID] 角色ID
function P:ctor(roleID)
    -- 角色ID(全球唯一)
    self._roleID = roleID
    -- 区也是连接ID
    self._sessionID = nil
    -- 连接时间
    self._connectTime = nil
    -- ip地址
    self._ip = nil
    -- 端口号
    self._port = nil
    -- 是否被踢出服务器
    self._isKick = false
    -- 是否存储到数据库
    self._isSave = true
    -- 从数据库里取出单一数据数组
    self._values = {}
    -- 从数据库取出复合数据数组
    self._objects = {}
    -- 从数据库取出邮件数据数组
    self._mails = {}
    -- 数据库ID
    self._who = nil
    -- 名字
    self._name = ""

    -- 初始化单一数组
    local valueSize = ruleMgr:getValueSize()
    for i=1, valueSize do
        table.insert(self._values, i, 0)
    end

    -- 初始化复合数组
    local objectSize = ruleMgr:getObjectSize()
    for i=1, objectSize do
        table.insert(self._objects, i, {})
    end
end
------------------------------------------------------------------------
-- @brief 初始化单一数组
-- @param[obj]  数组数据
function P:initValue(obj)
    if not obj then
        return
    end
    for i, v in ipairs(obj) do
        self._values[i] = v
    end
end
------------------------------------------------------------------------
-- @brief 初始化复合数组
-- @param[obj]  数组数据
function P:initObject(obj)
    if not obj then
        return
    end
    for k, v in pairs(obj) do
        self._objects[k] = v
    end
end
------------------------------------------------------------------------
-- @brief 初始化邮件
-- @param[obj]  数组数据
function P:initMails(obj)
    if not obj then
        return
    end
    self._mails = obj
end
------------------------------------------------------------------------
-- @brief 同步单一数组
function P:syncValue()
    self:sendObject(MsgEnums.Msg_RoleSyncValues, self._values)
end
------------------------------------------------------------------------
-- @brief 同步复合数组
function P:syncObject()
    self:sendObject(MsgEnums.Msg_RoleSyncValues, self._objects) 
end
------------------------------------------------------------------------
-- @brief 同步邮件
function P:syncMails()
    self:sendObject(MsgEnums.Msg_RoleSyncMails, self._mails)
end
------------------------------------------------------------------------
-- @brief 读取单一数组
function P:loadValues()
    if not self._who or tolua.type(self._who) ~= "number" then
        warning("LUA <Role:save> self._who is nil")
        return
    end
    sgPackMsg:packType(MsgEnums.Msg_DBRoleLoadValues)
    sgPackMsg:packValue(self._roleID)
    sgLogicServer:sendWhoPackMsg(self._who)
end
------------------------------------------------------------------------
-- @brief 读取复合数组
function P:loadObjects()
    if not self._who or tolua.type(self._who) ~= "number" then
        warning("LUA <Role:save> self._who is nil")
        return
    end
    sgPackMsg:packType(MsgEnums.Msg_DBRoleLoadObjects)
    sgPackMsg:packValue(self._roleID)
    sgLogicServer:sendWhoPackMsg(self._who)
end
------------------------------------------------------------------------
-- @brief 读取邮件
function P:loadMails()
    if not self._who or tolua.type(self._who) ~= "number" then
        warning("LUA <Role:save> self._who is nil")
        return
    end
    sgPackMsg:packType(MsgEnums.Msg_DBRoleLoadMails)
    sgPackMsg:packValue(self._roleID)
    sgLogicServer:sendWhoPackMsg(self._who)
end
------------------------------------------------------------------------
-- @brief 存储单一数组到服务器
function P:save()
    if not self._who or tolua.type(self._who) ~= "number" then
        warning("LUA <Role:save> self._who is nil")
        return
    end
    sgPackMsg:packType(MsgEnums.Msg_DBRoleSaveValues)
    sgPackMsg:packValue(self._roleID)
    sgPackMsg:packObject({self._values})
    sgLogicServer:sendWhoPackMsg(self._who)
end
------------------------------------------------------------------------
-- @brief 存储复合数组到服务器
function P:saveObjects()
    if not self._who or tolua.type(self._who) ~= "number" then
        warning("LUA <Role:save> self._who is nil")
        return
    end
    sgPackMsg:packType(MsgEnums.Msg_DBRoleSaveObjects)
    sgPackMsg:packValue(self._roleID)
    sgPackMsg:packObject({self._objects})
    sgLogicServer:sendWhoPackMsg(self._who)
end
------------------------------------------------------------------------
-- @brief 存储邮件数组到服务器
function P:saveMails()
    if not self._who or tolua.type(self._who) ~= "number" then
        warning("LUA <Role:save> self._who is nil")
        return
    end
    sgPackMsg:packType(MsgEnums.Msg_DBRoleSaveMails)
    sgPackMsg:packValue(self._roleID)
    sgPackMsg:packValue(1)
    sgPackMsg:packObject({self._mails})
    sgLogicServer:sendWhoPackMsg(self._who)
end
------------------------------------------------------------------------
-- @brief 获取单一数据
-- @param[idx]  下标
function P:getValue(idx)
    if idx > ruleMgr:getValueSize() then
        warning("<LUA:Role:getValue> index out of rang")
        return nil
    end
    return self._values[idx]
end
------------------------------------------------------------------------
-- @brief 设置单一数据
-- @param[idx]  下标
-- @param[jap]  值
function P:setValue(idx, jap)
    local oldjap = self:getValue(idx)
    local vr = ruleMgr:getValueRule(idx)

    if not vr then
        warning("LUA:role(".. tostring(self._roleID) .. ") setValue(" ..  tostring(idx) ..", " .. tostring(jap) .. ")  vr is nil")
        return false
    end 

    if jap < vr._min then
        warning("LUA:role(".. tostring(self._roleID) .. ") setValue(" ..  tostring(idx) ..", " .. tostring(jap) .. ") < min value")
        return false
    end

    if jap > vr._max then
        warning("LUA:role(".. tostring(self._roleID) .. ") setValue(" ..  tostring(idx) ..", " .. tostring(jap) .. ") > max value")
        return false
    end

    self._values[idx] = jap
    vr._setCount = vr._setCount + 1

    if vr._isLog then
        sgPackMsg:packType(MsgEnums.Msg_DBRoleAddNewLog)
        sgPackMsg:packValue(self._roleID)
        sgPackMsg:packValue(sgLogicServer:getDateTime():getUnixTime())
        sgPackMsg:packString(self._name)
        sgPackMsg:packString(vr._name)
        sgPackMsg:packObject({{idx, oldjap, jap}})
        sgLogicServer:sendWhoPackMsg(self._who)
    end

    if vr._isSyncClient then
        self:sendObject(MsgEnums.Msg_RoleSyncValues, {idx=jap})
    end

    if vr._event then
        vr._event:trigering({idx, oldjap, jap})
    end

    return true
end
------------------------------------------------------------------------
-- @brief 增加单一数据
-- @param[idx]  下标
-- @param[jap]  值
function P:incValue(idx, jap)
    if 0 == jap then
        return 0
    end
    if not self:setValue(idx, self:getValue(idx) + jap) then
        warning("LUA:role(".. tostring(self._roleID) .. ") incValue(" ..  tostring(idx) ..", " .. tostring(jap) .. ") out of range")
        return 0
    end
    return jap
end
------------------------------------------------------------------------
-- @brief 减少单一数据
-- @param[idx]  下标
-- @param[jap]  值
function P:decValue(idx, jap)
    if 0 == jap then
        return 0
    end
    if not self:setValue(idx, self:getValue(idx) - jap) then
        warning("LUA role(".. tostring(self._roleID) .. ") decValue(" ..  tostring(idx) ..", " .. tostring(jap) .. ") out of range")
        return 0
    end
    return jap
end
------------------------------------------------------------------------
-- @brief 获取复合数据
-- @param[idx]  下标
-- @param[jap]  值
function P:getObject(idx)
    if idx > ruleMgr:getObjectSize() then
        warning("<LUA Role:getObject> index out of rang")
        return nil
    end
    return self._objects[idx]
end
------------------------------------------------------------------------
-- @brief 设置复合数据
-- @param[idx]  下标
-- @param[obj]  数据
function P:setObject(idx, obj)
    local vr = ruleMgr:getObjectRule(idx)
    if not vr then
        return false
    end

    local oldObj = self._objects[idx]
    if oldObj ~= obj then
        self._objects[idx] = obj
    end

    if vr._isLog then
        sgPackMsg:packType(MsgEnums.Msg_DBRoleAddNewLog)
        sgPackMsg:packValue(self._roleID)
        sgPackMsg:packValue(sgLogicServer:getDateTime():getUnixTime())
        sgPackMsg:packString(self._name)
        sgPackMsg:packString(vr._name)
        sgPackMsg:packObject({{idx, oldObj, obj}})
        sgLogicServer:sendWhoPackMsg(self._who)
    end

    if vr._isSyncClient then
        self:sendObject(MsgEnums.Msg_RoleSyncObjects, {idx=obj})
    end

    if vr._event then
        vr._event:trigering({idx, oldObj, obj})
    end
    return true
end
------------------------------------------------------------------------
-- @brief 发送消息
function P:sendPackMsg()
    if self._isKick then
        return
    end
    if not self._sessionID then
        warning("LUA <Role:sendPackMsg> self._sessionID is nil")
        return
    end
    sgLogicServer:sendPackMsg(self._sessionID)
end
------------------------------------------------------------------------
-- @brief 发送消息
-- @param[msgType]  消息类型
-- @param[obj]  消息数据
function P:sendObject(msgType, obj)
    if self._isKick then
        return
    end

    if not msgType or tolua.type(msgType) ~= "number" then
        warning("LUA <Role:sendObject> msgType is nil")
        return
    end 

    if not obj or tolua.type(obj) ~= "table" then
        warning("LUA <Role:sendObject> msgType is nil")
        return
    end 

    if not self._sessionID then
        warning("LUA <Role:sendObject> self._sessionID is nil")
        return
    end
    sgPackMsg:packType(msgType)
    sgPackMsg:packValue(self._roleID)
    sgPackMsg:packObject(obj)
    sgLogicServer:sendPackMsg(self._sessionID)

end
------------------------------------------------------------------------
-- @brief 获取角色ID
function P:getRoleID()
    return self._roleID
end
------------------------------------------------------------------------
-- @brief 获取连接区ID
function P:getSessionID()
    return self._sessionID
end
------------------------------------------------------------------------
-- @brief 获取连接时间
function P:getConnectTime()
    return self._connectTime
end
------------------------------------------------------------------------
-- @brief 获取网络地址
function P:getIP()
    return self._ip
end
------------------------------------------------------------------------
-- @brief 获取端口
function P:getPort()
    return self._port
end
------------------------------------------------------------------------
-- @brief 是否被踢出
function P:getIsKick()
    return self._isKick
end
------------------------------------------------------------------------
-- @brief 新的一天需要清除一些数据
function P:updateNewDay()
    -- 时间
    local unix_time = sgLogicServer:getDateTime():getUnixTime()
    local off_line_time = self:getValue(ValueEnums.Val_OffLineTime)
    local off_line_date = os.date("*t", off_line_time)
    local unix_date = os.date("*t", unix_time)

    -- 判断是否穿越
    if unix_time <= off_line_time then
        warning("<LUA Role:updateNewDay> overtime by RoleID[" .. tostring(self._roleID) .. "].")
        return
    end

    -- 是否同一天
    if unix_date.day == off_line_date.day and unix_date.month == off_line_date.month and unix_date.year == off_line_date.year then
        return
    end
    
    -- 清空value数据
    for i, v in ipairs(ruleMgr._valueRules) do
        if v._clearTime == ruleMgr.dayClear then
            if unix_date.day ~= off_line_date.day or unix_date.month ~= off_line_date.month or unix_date.year ~= off_line_date.year then
                self._values[i] = 0
            end
        elseif v._clearTime == ruleMgr.weekClear then
            if unix_date.wday ~= off_line_date.wday then
                self._values[i] = 0
            end
        elseif v._clearTime == ruleMgr.monthClear then
            if unix_date.month ~= off_line_date.month or unix_date.year ~= off_line_date.year then
                self._values[i] = 0
            end 
        end
    end

    -- 清空object数据
    for i, v in ipairs(ruleMgr._objectRules) do
        if v._clearTime == ruleMgr.dayClear then
            if unix_date.day ~= off_line_date.day or unix_date.month ~= off_line_date.month or unix_date.year ~= off_line_date.year then
                self._objects[i] = {}
            end
        elseif v._clearTime == ruleMgr.weekClear then
            if unix_date.wday ~= off_line_date.wday then
                self._objects[i] = {}
            end
        elseif v._clearTime == ruleMgr.monthClear then
            if unix_date.month ~= off_line_date.month or unix_date.year ~= off_line_date.year then
                self._objects[i] = {}
            end 
        end
    end

    self:setValue(ValueEnums.Val_RoleID, self._roleID)
    self:setValue(ValueEnums.Val_OffLineTime, unix_time)
    self:setValue(ValueEnums.Val_LoginTime, unix_time)
end

return P
