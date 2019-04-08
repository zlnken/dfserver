------------------------------------------------------------------------
local ServerConfig = require("core.ServerConfig")
local MessageCall = require("core.MessageCall")
local RoleManager = require("core.RoleManager")
local SafeTableEnums = require("enum.SafeTableEnums")
local SafeTable = require("core.SafeTable")
local MsgEnums = require("enum.MessageEnums")
local ValueEnums = require("enum.ValueEnums")
local ObjectEnums = require("enum.ObjectEnums")
local msgcall = MessageCall.getInstance()
------------------------------------------------------------------------
local P = {}
P.IncludeModle = "local MessageCall = require(\"core.MessageCall\")\nlocal RoleManager = require(\"core.RoleManager\")\nlocal SafeTableEnums = require(\"enum.SafeTableEnums\")\nlocal SafeTable = require(\"core.SafeTable\")\nlocal MsgEnums = require(\"enum.MessageEnums\")\nlocal ValueEnums = require(\"enum.ValueEnums\")\nlocal ObjectEnums = require(\"enum.ObjectEnums\")\nlocal gm = require(\"gm.GameMaster\")\n"
------------------------------------------------------------------------
-- @brief 初始化数据
function P.initData()
 
end
------------------------------------------------------------------------
-- @brief 加载
function P.load()
	msgcall:setMessageFunc(MsgEnums.Msg_GMRunScript, P.onMsgGMRunScript)
end
------------------------------------------------------------------------
-- @brief 收取脚本数据
-- @param[upk] 数据
function P.onMsgGMRunScript(upk)
    if not sgLogicServer then
        warning("<Lua GameMaster.onRunScript> is not logic server.")
        return
    end

    local role_id = upk:unpackValue()
    local script_text = upk:unpackString()
    P.onScript(role_id, script_text)
end
------------------------------------------------------------------------
-- @brief 执行脚本
-- @param[role_id] 角色id
-- @param[script_text] 脚本
function P.onScript(role_id, script_text)
    if not role_id or type(role_id) ~= "number" then
        warning("<Lua GameMaster.onRunScript> role_id failed")
        return
    end

    if not script_text or type(script_text) ~= "string" then
        warning("<Lua GameMaster.onRunScript> script_text failed")
        return
    end

    local roleInfo = "local role = RoleManager.getInstance():findRoleByID(" .. tostring(role_id) .. ")\n"
    local full_script_text = P.IncludeModle .. roleInfo .. script_text
    print("---------------------runScirptMsg-----------------------------")
    print(full_script_text)
    
    DF.LuaSystem:instancePtr():setIsRunScriptMsg(true)
    DF.LuaSystem:instancePtr():doString(full_script_text)
    DF.LuaSystem:instancePtr():setIsRunScriptMsg(false)

    local send_string = DF.LuaSystem:instancePtr():getRunScirptPrint()
    local netCurrent = sgLogicServer:getCurNetConnect()
    sgPackMsg:packType(MsgEnums.Msg_GMRunScript)
    sgPackMsg:packString(send_string)
    sgLogicServer:sendPackMsg(netCurrent:getSessionID())
    
end

------------------------------------------------------------------------
-- @brief 重新加载脚本文件
-- @param[f]  文件
function P.reload(f)
	package.loaded[f] = nil
	return require(f)
end
------------------------------------------------------------------------
-- @brief 小时跳跃(不允许时间倒流)
-- @param[hour]  小时
-- @param[minute]  分钟
-- @param[second]  秒
function P.toTime(hour,minute,second)
    -- 检查是否为逻辑服
    if not sgLogicServer then
        warning("<Lua GameMaster.toTime> is not logic server.")
        return
    end
    -- 检查时间
    if hour >= 24 or minute >= 60 or second >= 60 then
        warning(string.format("to time is failed %d:%d:%d", hour, minute, second))
        return
    end
    -- 执行时间跳跃
    local date_time = sgLogicServer:getDateTime()
    local unix_time = date_time:getUnixTime()
    local day_time = date_time:hour() * 3600 + date_time:minute() * 60 + date_time:second()
    local jump_time = hour * 3600 + minute * 60 + second

    if jump_time <= day_time then
        warning("<Lua GameMaster.toTime> jump_time < day_time.")
       return 
    end
    
    local time_diff = jump_time - day_time
    local to_time = unix_time + time_diff
       
    date_time:setUnixTime(to_time)
    printInfo("----------------------------------")
    dump(os.date("*t", date_time:getUnixTime()))
    printInfo("----------------------------------")
end
------------------------------------------------------------------------
-- @brief 天跳跃(不允许时间倒流)
-- @param[days]  小时
function P.toDays(days)
    -- 检查是否为逻辑服
    if not sgLogicServer then
        warning("<Lua GameMaster.toDays> is not logic server.")
        return
    end
    
    local date_time = sgLogicServer:getDateTime()
    local to_time = date_time:getUnixTime() + days * 86400
    date_time:setUnixTime(to_time)    
end
------------------------------------------------------------------------
-- @brief 登录一个角色
-- @param[role_id] 角色id
function P.loginRole(role_id)
    -- 检查是否为逻辑服
    if not sgLogicServer then
        warning("<Lua GameMaster.loginRole> is not logic server.")
        return
    end

    -- 加载一个角色
    printInfo(role_id, ServerConfig.default.id)
    RoleManager.getInstance():createRole(role_id, ServerConfig.default.id)
end
------------------------------------------------------------------------
-- @brief 创建一个角色(只能在数据进程执行,请不要尝试其他进程)
-- @param[user] 用户
-- @param[password] 密码
-- @param[name] 名字
function P.newDBRole(user, password, name, world_id)
    -- 检查是否为逻辑服
    if not sgLogicServer then
        warning("<Lua GameMaster.newDBRole> is not logic server.")
        return
    end
    -- 给数据进程发送一个
    sgPackMsg:packType(MsgEnums.Msg_DBNewUser)
    sgPackMsg:packString(user)
    sgPackMsg:packString(password)
    sgPackMsg:packString(name)
    sgLogicServer:sendWhoPackMsg(world_id)

end
------------------------------------------------------------------------
-- @brief 测试消息脚本
-- @param[role_id] 角色id
-- @param[script_text] 脚本
function P.testOnMsgGMRunScript(role_id, strScript)
    -- 检查是否为逻辑服
    if not sgLogicServer then
        print("<Lua GameMaster.testOnMsgGMRunScript> is not logic server.")
        return
    end
    sgPackMsg:packType(MsgEnums.Msg_GMRunScript)
    sgPackMsg:packValue(role_id)
    sgPackMsg:packString(strScript)
    sgLogicServerCall.onMsg(sgPackMsg:getMsg())
end
------------------------------------------------------------------------
-- @brief 测试消息
-- @param[isLogic]  是否逻辑服
-- @param[msgType]  消息类型
-- @param[roleID]   角色ID
-- @param[ext]      额外数据
-- @param[obj]      数据
function P.runMsg(isLogic, msgType, roleID, ext, obj)
    sgPackMsg:packType(msgType)
    sgPackMsg:packValue(roleID)

    if ext then
        for _, v in ipairs(ext) do
            if type(v) == "string" then
                sgPackMsg:packString(v)
            elseif type(v) == "number" then
                sgPackMsg:packValue(v)
            elseif type(v) == "table" then
                sgPackMsg:packObject(v)
            end
        end
    end

    if obj then
        sgPackMsg:packObject(obj)
    end
    
    if isLogic then
        sgLogicServerCall.onMsg(sgPackMsg:getMsg())
    else
        sgDataBaseServerCall.onMsg(sgPackMsg:getMsg())
    end
end
------------------------------------------------------------------------
-- @brief 测试登录消息
-- @param[role_id]  角色ID
-- @param[who]  数据库ID
function P.runMsgLoginRole(role_id, who)
    if who then
       P.runMsg(true, MsgEnums.Msg_LoginRole, role_id, nil, who)
       return
    end
    P.runMsg(true, MsgEnums.Msg_LoginRole, role_id, nil, {who=ServerConfig.default.id})
end
------------------------------------------------------------------------
-- @brief 测试数据服登录消息
-- @param[user]  用户
-- @param[password]  密码
function P.runMsgByDBLoginUser(user, password)

    if not sgDataBaseServerCall then
        return
    end

    sgPackMsg:packType(MsgEnums.Msg_DBLoginUser)
    sgPackMsg:packString(user)
    sgPackMsg:packString(password)
    sgDataBaseServerCall.onMsg(sgPackMsg:getMsg())
    
    sgUnpackMsg:reset(sgPackMsg:getMsg())
    sgUnpackMsg:unpackMsg()
    local obj = sgUnpackMsg:unpackObject()
end
------------------------------------------------------------------------
-- @brief 测试登录服新建一个用户
-- @param[user]  用户
-- @param[password]  密码
-- @param[role_name]  用户名
function P.runMsgLoginByNewUser(user, password, role_name)
    if not sgLoginServerCall then
        return
    end
    sgPackMsg:packType(MsgEnums.Msg_NewUser)
    sgPackMsg:packValue(ServerConfig.default.id)
    sgPackMsg:packString(user)
    sgPackMsg:packString(password)
    sgPackMsg:packString(role_name)
    sgLoginServerCall.onMsg(sgPackMsg:getMsg())
end
------------------------------------------------------------------------
-- @brief 测试脚本
function P.runScript()
    -- P.loginRole(1105336684425)
    -- local role = RoleManager.getInstance():findRoleByID(1105336684425)
    -- role:setValue(ValueEnums.Val_Test1, 14)
    -- role:setValue(ValueEnums.Val_Test2, 200)
    -- role:setObject(ObjectEnums.Obj_Test0, {1,2,3,4})
    -- role:save() 
    local net = sgLogServer:getCurNetConnect()
    local data = "11111111111"
    net:sendBytes(data, string.len(data))
end
------------------------------------------------------------------------
return P