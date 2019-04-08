------------------------------------------------------------------------
--	local m = P.reload(logic.RoleManager)
--	local roleMgr = m:new()
--  roleMgr._roles = m._roles
--  m.instance = roleMgr
------------------------------------------------------------------------
-- @brief 加载模块
local P = class("RoleManager")
local Role = require("core.Role")
local MessageCall = require("core.MessageCall")
local MsgEnums = require("enum.MessageEnums")
local ServerConfig = require("core.ServerConfig")
local SafeTableEnums = require("enum.SafeTableEnums")
local ValueEnums = require("enum.ValueEnums")
local ObjectEnums = require("enum.ObjectEnums")
local RuleManager = require("core.RuleManager")
local msgcall = MessageCall.getInstance()
local ruleMgr = RuleManager.getInstance()
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
    
    self._dateTime = sgLogicServer:getDateTime()
    -- 角色对象表
    self._roles = {}
    -- 角色数量
    self._roleSize = 0
    -- 最大登录数量
    self._MaxRoleSize = 1000
    -- 上次储存角色时间 
    self._lastSaveRolesTime = self._dateTime:getUnixTime() 
    -- 4分钟储存一次
    self._saveSpaceTime = 240
    -- 储存表
    self._saveRoles = {}
    -- 每秒储存数量       
    self._saveCountBySecond = 8
    --  注册消息
    msgcall:setMessageFunc(MsgEnums.Msg_DBRoleLoadValues,       handler(self, self.onMsgLoadRoleValues))
    msgcall:setMessageFunc(MsgEnums.Msg_DBRoleLoadObjects,      handler(self, self.onMsgRoleLoadObjects))
    msgcall:setMessageFunc(MsgEnums.Msg_DBRoleLoadMails,        handler(self, self.onMsgRoleLoadMails))
    msgcall:setMessageFunc(MsgEnums.Msg_DBRoleSaveValues,       handler(self, self.onMsgSaveRoleValuesSucceed))
    msgcall:setMessageFunc(MsgEnums.Msg_DBRoleSaveObjects,      handler(self, self.onMsgSaveRoleObjectsSucceed))
    msgcall:setMessageFunc(MsgEnums.Msg_LoginRole,              handler(self, self.onMsgLoginRole))
end
------------------------------------------------------------------------
-- @brief 查找一个角色对象
-- @param[roleID] 角色ID
function P:findRoleByID(roleID)
    local role = self._roles[roleID]
    if not role then
        warning("<RoleManager:findRole> can not find role(" .. tostring(roleID) .. ")")
        return nil
    end
    return role
end
------------------------------------------------------------------------
-- @brief 获取所有登录角色
function P:getRoles()
    return self._roles
end
------------------------------------------------------------------------
-- @brief 移除一个角色
function P:removeRole(role_id)
    self._roles[role_id] = nil
end
------------------------------------------------------------------------
-- @brief 创建一个角色
-- @param[role_id] 角色ID
-- @param[who] 来自哪个数据库
function P:createRole(role_id, who)
    if not role_id or tolua.type(role_id) ~= "number" then
        warning("<Lua DataBaseRoleCall.onMsgCreateRole> role_id failed")
        return
    end

    if not who or tolua.type(who) ~= "number" then
        warning("<Lua DataBaseRoleCall.onMsgCreateRole> who failed")
        return
    end

    if self._roleSize >= self._MaxRoleSize then
        warning("LUA:<RoleManager:createRole> out of range")
        return nil
    end

    
    local role = self._roles[role_id]
    if not role then
        role = Role.new(role_id)
        role._who = who
        self._roles[role_id] = role
    else
        sgLogicServer:disConnect(role:getSessionID())
    end
    
    local netConnect = sgLogicServer:getCurNetConnect()
    if netConnect and netConnect:getWho() ~= who then
        role._connectTime = netConnect:getConnectTime()
        role._sessionID = netConnect:getSessionID()
        role._ip = netConnect:getIP()
        role._port = netConnect:getPort()
    end
    role:loadValues()
end
------------------------------------------------------------------------
-- @brief 每秒更新
function P:updateLost()
    for roleID, role in pairs(self._roles) do
        local sessionID = role:getSessionID()
        if sessionID and not sgLogicServer:hasConnect(sessionID) then
            role:save()
            role:kick()
        elseif role:getIsKick() then
            role:save()
        end
    end
end
------------------------------------------------------------------------
-- @brief 广播给所有角色
function P:sendPackMsg()
    for _, role in pairs(self._roles) do
        role:sendPackMsg()
    end
end
------------------------------------------------------------------------
-- @brief 广播给所有角色
-- @param[obj] 数据
function P:sendObject(obj)
    for _, role in pairs(self._roles) do
        role:sendObject(obj)
    end
end
------------------------------------------------------------------------
-- @brief 收取一个登录角色消息
-- @param[upk] 数据
function P:onMsgLoginRole(upk)
    local role_id = upk:unpackValue()
    local who = upk:unpackValue()
    self:createRole(role_id, who)
end
------------------------------------------------------------------------
-- @brief 收取一个角色单一数组数据
-- @param[upk] 数据
function P:onMsgLoadRoleValues(upk)
    local role_id = upk:unpackObject()
    local obj = upk:unpackObject()

    if not obj then
        warning("<Lua RoleManager:onMsgLoadRoleValues> obj is nil")
        return
    end

    if not role_id then
        warning("<Lua RoleManager:onMsgLoadRoleValues> role_id is nil")
        return
    end

    if obj.who and tolua.type(obj.who) == "number" then
        return   
    end

    local netConnect = sgLogicServer:getCurNetConnect()
    if not netConnect then
        return
    end

    local who = netConnect:getWho()
    if who >= 0 then
        local data = obj[1]
        local name = data[1]
        local values = data[2]
        local role = self:findRoleByID(role_id)
        if not role then
            warning("<LUA RoleManager:onMsgLoadRoleValues> can not find role by id(".. role_id .. ")" )
            return
        end
        if name then
            role._name = name
        end
        if values then
            role:initValue(values)
        end
        role:loadObjects()
        return
    end
end
------------------------------------------------------------------------
-- @brief 收取一个角色对象数组数据
-- @param[upk] 数据
function P:onMsgRoleLoadObjects(upk)
    local role_id = upk:unpackObject()

    local obj = upk:unpackObject()
    if not obj then
        warning("<Lua RoleManager:onMsgRoleLoadObjects> obj is nil")
        return
    end

    if not role_id then
        warning("<Lua RoleManager:onMsgRoleLoadObjects> role_id is nil")
        return
    end

    local netConnect = sgLogicServer:getCurNetConnect()
    if not netConnect then
        return
    end
    local who = netConnect:getWho()
    if who >= 0 then
        local objects = obj[1][1]
        local role = self:findRoleByID(role_id)
        if not role then
            warning("<LUA RoleManager:onMsgRoleLoadObjects> can not find role by id(".. role_id .. ")" )
            return
        end
        if objects then
            role:initObject(objects)
        end
        role:updateNewDay()
        role:syncValue()
        role:syncObject()
        role:loadMails()
    end
end
------------------------------------------------------------------------
-- @brief 收取一个角色邮件数组数据
-- @param[upk] 数据
function P:onMsgRoleLoadMails(upk)
    local role_id = upk:unpackObject()
    local obj = upk:unpackObject()
    if not obj then
        warning("<Lua RoleManager:onMsgRoleLoadMails> obj is nil")
        return
    end

    if not role_id then
        warning("<Lua RoleManager:onMsgRoleLoadMails> role_id is nil")
        return
    end

    local netConnect = sgLogicServer:getCurNetConnect()
    if not netConnect then
        return
    end
    local who = netConnect:getWho()
    if who >= 0 then
        local mails = obj[1][1]
        local role = self:findRoleByID(role_id)
        if not role then
            warning("<LUA RoleManager:onMsgRoleLoadObjects> can not find role by id(".. role_id .. ")" )
            return
        end
        if mails then
            role:initMails(mails)
        end
    end
end
------------------------------------------------------------------------
-- @brief 收取一个角色成功储存单一数组数据
-- @param[upk] 数据
function P:onMsgSaveRoleValuesSucceed(upk)
    local role_id = upk:unpackObject()
    local obj = upk:unpackObject()
    if not obj then
        warning("<Lua RoleManager:onMsgSaveRoleValuesSucceed> obj is nil")
        return
    end

    if not role_id then
        warning("<Lua RoleManager:onMsgSaveRoleValuesSucceed> role_id is nil")
        return
    end

    local isOk = obj[1]
    if not isOk then
        warning("<Lua RoleManager:onMsgSaveRoleValuesSucceed> role_id save values is Failed")
        return
    end

    local role = self:findRoleByID(role_id)
    if not role then
        return
    end
    role:saveObjects()
end
------------------------------------------------------------------------
-- @brief 收取一个角色成功储存对象数组数据
-- @param[upk] 数据
function P:onMsgSaveRoleObjectsSucceed(upk)
    local role_id = upk:unpackObject()
    local obj = upk:unpackObject()
    if not obj then
        warning("<Lua RoleManager:onMsgSaveRoleObjectsSucceed> obj is nil")
        return
    end

    if not role_id then
        warning("<Lua RoleManager:onMsgSaveRoleObjectsSucceed> role_id is nil")
        return
    end

    local isOk = obj[1]
    if not isOk then
        warning("<Lua RoleManager:onMsgSaveRoleObjectsSucceed> role_id save values is Failed")
        return
    end

    local role = self:findRoleByID(role_id)
    if not role then
        return
    end
    
    role:saveMails()

    local sessionID = role:getSessionID()
    if sessionID and not sgLogicServer:hasConnect(sessionID) then
        self._roles[role._roleID] = nil
    end

end
------------------------------------------------------------------------
-- @brief 发送一个离线邮件
-- @param[role_id] 角色ID
-- @param[mails] 邮件
function P:sendOfflineMails(role_id, mails)
    local who = ServerConfig.default.id
    sgPackMsg:packType(MsgEnums.Msg_SaveRoleMails)
    sgPackMsg:packValue(role_id)
    sgPackMsg:packValue(0)
    sgPackMsg:packObject({mails})
    sgLogicServer:sendWhoPackMsg(who)
end

------------------------------------------------------------------------
-- @brief 发送一个离线邮件
-- @param[role_id] 角色ID
function P:kickRole(role_id, is_save)
    local role = self._roles[role_id]
    if not role then
        return
    end
    --  是否存储
    if is_save then
        self:setValue(ValueEnums.Val_OffLineTime, sgLogicServer:getDateTime():getUnixTime())
        role:save()
    end

    -- 同步踢人
    self:sendObject(MsgEnums.Msg_KickRole, true)

    -- 断开连接
    if role:getSessionID() then
        sgLogicServer:disConnect(role:getSessionID())
    end
    
    -- 清空数据
    self._roles[role_id] = nil
end

------------------------------------------------------------------------
-- @brief 每日刷新数据
function P:callAfterNewDay()
    for _, role in pairs(self._roles) do
        if role then
            role:updateNewDay()
        end
    end
end
------------------------------------------------------------------------
-- @brief 更新存储角色数据
function P:updateSaveRoles()    
    -- 检查储存角色
    if #self._saveRoles > 0 then
        for i=1, self._saveCountBySecond do
            local role = table.remove(self._saveRoles, 1)
            if not role then
                self._lastSaveRolesTime = self._dateTime:getUnixTime()
                break
            end
            warning("save role id[" .. role._roleID .. "]")
            role:save()
        end
        return
    end

    local unix_time = self._dateTime:getUnixTime()
    local spcae_tiem = unix_time - self._lastSaveRolesTime

    -- 开始储存角色
    if spcae_tiem >= self._saveSpaceTime then
        for _, role in pairs(self._roles) do
            if not role:getIsKick() then
                table.insert(self._saveRoles, role)
            end
        end
    end
end

return P
