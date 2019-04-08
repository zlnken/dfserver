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
