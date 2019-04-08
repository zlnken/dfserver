-------------Common-----------------
function warning(str)
end
function printInfo(str)
end
function printError(str)
end
--------------------DF.BaseServer-------------------
DF.BaseServer.BSTE_OnStar = nil
DF.BaseServer.BSTE_OnLost = nil
DF.BaseServer.BSTE_OnMsg = nil
DF.BaseServer.BSTE_BeforeNewMinute = nil
DF.BaseServer.BSTE_BeforeNewHour = nil
DF.BaseServer.BSTE_BeforeNewDay = nil
DF.BaseServer.BSTE_AfterNewMinute = nil
DF.BaseServer.BSTE_AfterNewHour = nil
DF.BaseServer.BSTE_AfterNewDay = nil
DF.BaseServer.BSTE_PerSecond = nil
DF.BaseServer.BSTE_KeyboardKeyDown = nil
DF.BaseServer.BSTE_MaxCount = nil
function DF.BaseServer.sendPackMsg(uSessionID)
end
function DF.BaseServer.sendObject(uSessionID,uMsgType)
end
function DF.BaseServer.sendBytes(uSessionID,pHead,uSize)
end
function DF.BaseServer.sendWhoPackMsg(uWho)
end
function DF.BaseServer.sendWhoObject(uWho,uMsgType)
end
function DF.BaseServer.connect(ip,uPort,uWho)
end
function DF.BaseServer.disConnect(uSessionID)
end
function DF.BaseServer.hasConnect(uSessionID)
end
function DF.BaseServer.isSendOver(uSessionID)
end
function DF.BaseServer.setWorld(uWorld)
end
function DF.BaseServer.allocGloablID()
end
function DF.BaseServer.getPackMessage()
end
function DF.BaseServer.getUnpackMessage()
end
function DF.BaseServer.setPackMessage(pPackMsg)
end
function DF.BaseServer.setUnpackMessage(pUnpackMsg)
end
function DF.BaseServer.getCurNetConnect()
end
function DF.BaseServer.getProcess()
end
function DF.BaseServer.getDateTime()
end
function DF.BaseServer.getIP()
end
function DF.BaseServer.getProt()
end
function DF.BaseServer.setTrigger(eType,pTrigger)
end
--------------------DF.Config-------------------
DF.Config.MIN_INT8 = nil
DF.Config.MAX_INT8 = nil
DF.Config.MIN_INT16 = nil
DF.Config.MAX_INT16 = nil
DF.Config.MIN_INT32 = nil
DF.Config.MAX_INT32 = nil
DF.Config.MIN_INT64 = nil
DF.Config.MAX_INT64 = nil
DF.Config.MAX_UINT8 = nil
DF.Config.MAX_UINT16 = nil
DF.Config.MAX_UINT32 = nil
DF.Config.MAX_UINT64 = nil
DF.Config.MIN_FLOAT = nil
DF.Config.MAX_FLOAT = nil
DF.Config.MIN_DOUBLE = nil
DF.Config.MAX_DOUBLE = nil
DF.Config.MAX_STACK_DEEP = nil
DF.Config.NONE_FLAG = nil
DF.Config.TRUE_FLAG = nil
DF.Config.FALSE_FLAG = nil
DF.Config.SMALL_TUPLE_FLAG = nil
DF.Config.BIG_TUPLE_FLAG = nil
DF.Config.SMALL_LIST_FLAG = nil
DF.Config.BIG_LIST_FLAG = nil
DF.Config.SMALL_SET_FLAG = nil
DF.Config.BIG_SET_FLAG = nil
DF.Config.SMALL_DICT_FLAG = nil
DF.Config.BIG_DICT_FLAG = nil
DF.Config.SMALL_STRING_FLAG = nil
DF.Config.BIG_STRING_FLAG = nil
DF.Config.DATETIME_FLAG = nil
DF.Config.SIGNED_INT8_FLAG = nil
DF.Config.SIGNED_INT16_FLAG = nil
DF.Config.SIGNED_INT32_FLAG = nil
DF.Config.SIGNED_INT64_FLAG = nil
DF.Config.CLASS_OBJ_FLAG = nil
DF.Config.FLOAT_FLAG = nil
DF.Config.DOUBLE_FLAG = nil
DF.Config.SEND_BLOCK_SIZE = nil
DF.Config.SEND_BLOCK_NUM = nil
DF.Config.RECV_BLOCK_SIZE = nil
DF.Config.RECV_BLOCK_NUM = nil
DF.Config.MSG_MAX_SIZE = nil
DF.Config.MSG_BASE_SIZE = nil
DF.Config.MAX_PACK_SIZE = nil
DF.Config.MAX_CONNECT = nil
DF.Config.MAX_THREAD = nil
DF.Config.DEFAULT_PORT = nil
DF.Config.DATA_BASE_PORT = nil
--------------------DF.DataBaseMySQL-------------------
function DF.DataBaseMySQL.execute(sql,pPackMsg)
end
function DF.DataBaseMySQL.executeStmt(sql,unpack)
end
function DF.DataBaseMySQL.initStmt(sql)
end
function DF.DataBaseMySQL.pushString(val)
end
function DF.DataBaseMySQL.pushBlob(val,len)
end
function DF.DataBaseMySQL.pushData(type,data)
end
function DF.DataBaseMySQL.executeStmt()
end
function DF.DataBaseMySQL.getUser()
end
function DF.DataBaseMySQL.getPassword()
end
function DF.DataBaseMySQL.getHost()
end
function DF.DataBaseMySQL.getIP()
end
function DF.DataBaseMySQL.getPort()
end
--------------------DF.DataBaseServer-------------------
function DF.DataBaseServer.instancePtr()
end
function DF.DataBaseServer.unintance()
end
function DF.DataBaseServer.initDataBase(host,user,passwd,port)
end
function DF.DataBaseServer.executeSQL(sql)
end
function DF.DataBaseServer.executeStmt(sql,unpack)
end
function DF.DataBaseServer.getDataBaseMySQL()
end
--------------------DF.DateTime-------------------
function DF.DateTime.year()
end
function DF.DateTime.month()
end
function DF.DateTime.day()
end
function DF.DateTime.hour()
end
function DF.DateTime.minute()
end
function DF.DateTime.second()
end
function DF.DateTime.milliseSecond()
end
function DF.DateTime.days()
end
function DF.DateTime.weeks()
end
function DF.DateTime.months()
end
function DF.DateTime.yearDay()
end
function DF.DateTime.monthDay()
end
function DF.DateTime.weekDay()
end
function DF.DateTime.seconds()
end
function DF.DateTime.getUnixTime()
end
function DF.DateTime.timeZoneSeconds()
end
function DF.DateTime.setUnixTime(uUnixTime)
end
function DF.DateTime.setTimeSpeed(uTimeSpeed)
end
--------------------DF.LogicServer-------------------
function DF.LogicServer.instancePtr()
end
function DF.LogicServer.unintance()
end
--------------------DF.LoginServer-------------------
function DF.LoginServer.instancePtr()
end
function DF.LoginServer.unintance()
end
--------------------DF.LuaFunction-------------------
function DF.LuaFunction.screate()
end
function DF.LuaFunction.screate(sName)
end
--------------------DF.LuaSystem-------------------
function DF.LuaSystem.instancePtr()
end
function DF.LuaSystem.setDebug(bDebug)
end
function DF.LuaSystem.doString(pStr)
end
function DF.LuaSystem.doFile(sFileName)
end
function DF.LuaSystem.reload(sModuleFileName)
end
function DF.LuaSystem.enableReturn(file)
end
function DF.LuaSystem.disableReturn()
end
function DF.LuaSystem.getRootPath()
end
function DF.LuaSystem.setIsRunScriptMsg(isRunScriptMsg)
end
function DF.LuaSystem.getRunScirptPrint()
end
function DF.LuaSystem.loadFiles(path)
end
function DF.LuaSystem.loadAllFiles(strFolderPath,curPath)
end
function DF.LuaSystem.getServer()
end
--------------------DF.LuaTrigger-------------------
DF.LuaTrigger.LTE_Dtor  = nil
DF.LuaTrigger.LTE_TriMsg  = nil
DF.LuaTrigger.LTE_TriNone  = nil
DF.LuaTrigger.LTE_Clear  = nil
DF.LuaTrigger.LTE_MaxCount = nil
function DF.LuaTrigger.clear()
end
function DF.LuaTrigger.triggering()
end
function DF.LuaTrigger.triggering(pMsg)
end
function DF.LuaTrigger.getID()
end
function DF.LuaTrigger.getType()
end
function DF.LuaTrigger.pushFunction(funcEnum,pfunc)
end
function DF.LuaTrigger.addToRootCallBack(sTag,iTag)
end
function DF.LuaTrigger.screate()
end
--------------------DF.MessageBase-------------------
function DF.MessageBase.getSize()
end
function DF.MessageBase.setSize(uSize)
end
function DF.MessageBase.addSize(uSize)
end
function DF.MessageBase.getType()
end
function DF.MessageBase.getBody()
end
function DF.MessageBase.getBodySize()
end
function DF.MessageBase.align()
end
--------------------DF.NetConnect-------------------
function DF.NetConnect.isShutdown()
end
function DF.NetConnect.getSessionID()
end
function DF.NetConnect.getConnectTime()
end
function DF.NetConnect.getIP()
end
function DF.NetConnect.getPort()
end
function DF.NetConnect.getWho()
end
function DF.NetConnect.sendBytes(pHead,uSize)
end
--------------------DF.PackMessage-------------------
function DF.PackMessage.packType(uType)
end
function DF.PackMessage.packMsg(pMsg)
end
function DF.PackMessage.packBytes(pHead,uSize)
end
function DF.PackMessage.packInt8(i8)
end
function DF.PackMessage.packInt16(i16)
end
function DF.PackMessage.packInt32(i32)
end
function DF.PackMessage.packUint8(ui8)
end
function DF.PackMessage.packUint16(ui16)
end
function DF.PackMessage.packUint32(ui32)
end
function DF.PackMessage.packFloat(f)
end
function DF.PackMessage.packDouble(d)
end
function DF.PackMessage.packValue(d)
end
function DF.PackMessage.packInt(d)
end
function DF.PackMessage.packDict(uSize)
end
function DF.PackMessage.packString(v)
end
function DF.PackMessage.packObject()
end
function DF.PackMessage.getIsOK()
end
function DF.PackMessage.getTotalBodySize()
end
function DF.PackMessage.getCurrentEmptySize()
end
function DF.PackMessage.getMsg()
end
