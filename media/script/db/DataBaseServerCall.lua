------------------------------------------------------------------------
-- @brief 数据库服回调
------------------------------------------------------------------------
sgDataBaseServer = DF.DataBaseServer:instancePtr() -- 数据服对象
sgUnpackMsg = sgDataBaseServer:getUnpackMessage()  -- 数据服解包
sgPackMsg = sgDataBaseServer:getPackMessage()       -- 数据服打包
------------------------------------------------------------------------
require("common.functions")
local CLuaTrigger = require ("core.CLuaTrigger")
local ServerConfig = require("core.ServerConfig")
local MessageCall = require("core.MessageCall")
local DBMsgCall = require ("db.DataBaseMsgCall")
local MsgEnums = require("enum.MessageEnums")
local sqls = require("db.DataBaseSQLConfig")
------------------------------------------------------------------------
-- 单例
sgDataBaseServerCall = {}
local P = sgDataBaseServerCall
------------------------------------------------------------------------
-- @brief 初始化数据服一个触发器
-- @param[type] 类型
-- @param[func] 回调函数
function P.initTrigger(type, func)
	local tri = CLuaTrigger:new()
	tri:push(func)
	sgDataBaseServer:setTrigger(type, tri)
end

------------------------------------------------------------------------
-- @brief 初始化数据服回调
function P.initDataBaseServer()
	P.initTrigger(DF.BaseServer.BSTE_OnMsg, P.onMsg)
	P.initTrigger(DF.BaseServer.BSTE_OnLost, P.onLost)
	P.initTrigger(DF.BaseServer.BSTE_AfterNewHour, P.callAfterNewHour)
	P.initTrigger(DF.BaseServer.BSTE_KeyboardKeyDown, P.callKeyBoardKeyDown)

	local s = ServerConfig.default
	sgDataBaseServer:initDataBase(s.host, s.user, s.passwd, s.db_port, s.ip)
    sgDataBaseServer:setWorld(s.id)

	local dbUseWorld = string.format(sqls.dbUseWorld, s.id)
	if not sgDataBaseServer:executeSQL(dbUseWorld) then
		sgDataBaseServer:executeSQL(string.format(sqls.dbCreateWorld, s.id))
		sgDataBaseServer:executeSQL(dbUseWorld)
		sgDataBaseServer:executeSQL(sqls.tbRoleCreate)
		sgDataBaseServer:executeSQL(sqls.tbGlobalDatasCreate)
        sgDataBaseServer:executeSQL(sqls.tbLoginCreate)
        sgDataBaseServer:executeSQL(sqls.tbLogCreate)
	end


	DBMsgCall.initData()
	DBMsgCall.load()
end
------------------------------------------------------------------------
-- @brief 消息分发
-- @param[msg] 消息
function P.onMsg(msg)
	local msgType = msg:getType()		
	local msgCall = MessageCall.getInstance():getMessage(msgType)
	if not msgCall then
		warning("<LUA DataBaseServer.onMsg> can not find msg(" .. tostring(msgType) .. ")")
        sgPackMsg:packType(MsgEnums.Msg_Error)
        sgPackMsg:packString("LUA can not found msgCall._func msg(" .. msgCall._name .. ")")
	    sgDataBaseServer:sendPackMsg(sgLoginServer:getCurNetConnect():getSessionID())
		return
	end

	if not msgCall._func then
		warning("LUA can not found msgCall._func msg(" .. tostring(msgCall._name) .. ")")
		return
	end 

	if msg:getSize() == 4 then
		msgCall._func()
		return
	end
	sgUnpackMsg:reset(msg)
	sgUnpackMsg:unpackMsg()
	msgCall._func(sgUnpackMsg)

end
------------------------------------------------------------------------
-- @brief 掉线
function P.onLost()


end
------------------------------------------------------------------------
-- @brief 每小时更新后
function P.callAfterNewHour()
    printInfo("callAfterNewHour......")
    -- 进行数据备份
    printInfo("backup database")
    if sgDataBaseServer:getDateTime():hour() == 12 then
        P.backupDataBase()
    end
end
------------------------------------------------------------------------
-- @brief 备份文件
function P.backupFile(path, backup_path, file)
    local f = io.open(path .. file, "rb")
    local data = f:read("*a");
    f:close()
    f = io.open(backup_path .. file, "wb")
    f:write(data)
    f:close()
end
------------------------------------------------------------------------
-- @brief 备份数据库
function P.backupDataBase()
    -- 是否存在
    if P.co then
       return 
    end

    -- 创建协同线程
    P.co = coroutine.create( function()
        -- 时间
        local year = tostring(sgDataBaseServer:getDateTime():year())
        local month = tostring(sgDataBaseServer:getDateTime():month())
        local day = tostring(sgDataBaseServer:getDateTime():day())

        -- 路径
        local platform_path = "C:/Program Files/MySQL/MySQL Server 5.7/data/"
        local world_id = "world_" .. tostring(ServerConfig.default.id) 
        local path = platform_path .. world_id .. "/"
        local root_backup_path = platform_path .. "backup/"
        local backup_path = root_backup_path .. world_id .. "_" ..  year .. "_" .. month .. "_" .. day .. "/"
    
        -- 创建路径
        os.execute("mkdir \"" .. root_backup_path .. "\"")
        os.execute("mkdir \"" .. backup_path .. "\"")
           
        -- 备份文件
        sgDataBaseServer:executeSQL("flush tables with read lock;")
        P.backupFile(path, backup_path, "db.opt")
        P.backupFile(path, backup_path, "tb_global_datas.frm")
        P.backupFile(path, backup_path, "tb_global_datas.MYD")
        P.backupFile(path, backup_path, "tb_global_datas.MYI")
        P.backupFile(path, backup_path, "tb_login.frm")
        P.backupFile(path, backup_path, "tb_login.MYD")
        P.backupFile(path, backup_path, "tb_login.MYI")
        P.backupFile(path, backup_path, "tb_role.frm")
        P.backupFile(path, backup_path, "tb_role.MYD")
        P.backupFile(path, backup_path, "tb_role.MYI")
        sgDataBaseServer:executeSQL("unlock tables;")

        -- 协同挂起线程
        coroutine.yield()
        P.co = nil
    end)

    -- 协同线程开始
    coroutine.resume(P.co)
end
------------------------------------------------------------------------
-- @brief 键盘响应回调
function P.callKeyBoardKeyDown(msg)
	local keyCode = msg:getType()
	if keyCode == 0x7B then
        printInfo("DataBaseServerCall.callKeyBoardKeyDown runing...")
		package.loaded["gm.GameMaster"] = nil
		require("gm.GameMaster"):runScript()
		printInfo("DataBaseServerCall.callKeyBoardKeyDown end.")
	end
end
------------------------------------------------------------------------
-- 初始化
sgDataBaseServerCall.initDataBaseServer()


