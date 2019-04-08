--local UIPvpFree = require("app.views.uidatas.ui_pvpFree")
--local UIRaidPlayerNode = require("app.views.uidatas.ui_raidPlayerNode")
--local CoolTime = require("app.views.common.CoolTime")
-----------------------------------------------------------------------
local P = class("PvpFreeLayer", BaseLayer)
P.Start_Time = nil
-----------------------------------------------------------------------
function P.initConfig() 
    if P.WarfareReward then
        return
    end

    local totalExp = 0 
    for i, v in ipairs(tpl_Warfare) do
        v.last = v
        totalExp = totalExp + v.point 
        v.total = totalExp
        if i > 1 and tpl_Warfare[i-1]  then
            v.last = tpl_Warfare[i-1]
        end
        if i < #tpl_Warfare then
            v.next = tpl_Warfare[i+1]
        end
    end

    table.sort(tpl_Warfare, function(a, b) return a.total < b.total end)


    local totalFightCount = 0
    P.WarfareReward = {}
    for  i, v in ipairs(tpl_WarfareReward) do
        if not P.WarfareReward[v.box_id] then
             P.WarfareReward[v.box_id] = {}
        end
        local t = P.WarfareReward[v.box_id][v.level_id]  
        if not t then
            totalFightCount = 0
            P.WarfareReward[v.box_id][v.level_id] = {}            
            t = P.WarfareReward[v.box_id][v.level_id]  
        end
        totalFightCount = totalFightCount + v.needfight
        v.totalFightCount = totalFightCount
        table.insert(t, v)
    end
    
    for i, v in pairs(P.WarfareReward) do
        table.sort(v, function(a, b) return a.totalFightCount < b.totalFightCount end)
    end
end
-----------------------------------------------------------------------
function P.getLevelPoint(point)
    P.initConfig()
    for i, v in ipairs(tpl_Warfare) do

        if i == #tpl_Warfare and point >= v.total then
            local c = clone(v)
            c.last = c
            c.isLast = true
            return c
        end 

        if v.total > point then
            return v
        end

    end

    local c = tpl_Warfare[#tpl_Warfare]
    c.isLast = true
    return c
end

-----------------------------------------------------------------------
function P.getLevelReward(box_id, levelID, fightCount)
    P.initConfig()
    --dump(P.WarfareReward)
    local rewardData = P.WarfareReward[box_id][levelID]
    local len = #rewardData
    for i, v in ipairs(rewardData) do

        if i == len and fightCount < v.totalFightCount then
            return v
        end 

        if v.totalFightCount >= fightCount then
            return v
        end 

    end
    return rewardData[len]
end


---------------------------------------------------------------------
function P:delayGoto(layerName, args)
    if not UnlockManager:isUnlocked(UnlockSystem.PVPFree, true) then
        return
    end

    LoadingLayer.isShowLoading(true)
    local function gotoLayer(object)
        sgGameState:getRoomManager():init()
        sgGameState:getRoomManager():setBattleType(Constants.BATTLETYPE_PPVPP_FREE)
        sgGameState:getRoomManager():createRoom(10001, function (obj)
            if (obj.status ~= 0 and obj.status ~= 3) then 
                LoadingLayer.isShowLoading(false)
                return 
            end
            sgLayerManager:goto(layerName, object)
            local layer = sgLayerManager:getLayer(layerName)
            layer:updatePlayerNode()

        end)
    end


    local req = ptl.Req4020:create()
    req.type = 1
    req.rewardType = 1
    ReqAndResp:callReq(req, function(data)
        gotoLayer({data})
    end)

end
-----------------------------------------------------------------------
function P:ctor(datas, isBackToRoom)
    _RES:addSpriteFrames("ui/font/chwenzi.plist")
    LoadingLayer.isShowLoading(false)
    P.super.ctor(self, "ui_pvpFree")
    self._isFullWindow = true

    self._isBackToRoom = isBackToRoom

    sgCommon:setTitle(self._ui.label64)


    self:onEvent(ChatManager.CHAT_NEW_MSG, handler(self, self.onChat))
    --self:onEvent(ChatManager.FACE_STR, handler(self, self.onFaceStr))


    self.battleType = Constants.BATTLETYPE_PPVPP_FREE
    sgGameState:getRoomManager()._lastLevel = sgGameState:getUserState().level
    sgGameState:getRoomManager()._isMatch = 0
    sgGameState:getRoomManager():setUpdateRoomInfoCB(handler(self, self.updatePlayerNode))
    sgGameState:getRoomManager():setReadyCB(handler(self, self.roomMemberReady))
    sgGameState:getRoomManager():setExitRoomCB(handler(self, self.exitRoom))
    sgGameState:getRoomManager():setChooseHeroCB(handler(self, self.syncChooseHeroCallBack))
    sgGameState:getRoomManager():setKickPlayerCB(handler(self, self.syncKickPlayerCallBack))
    sgGameState:getRoomManager():setStartBattleCB(handler(self, self.onStartBattle))
    self:onNetEvent(ptl.Resp10009.protoid, handler(self, self.syncChooseHeroCallBack))
    self:onNetEvent(ptl.Resp4022.protoid, handler(self, self.syncPlayerLevelup))



    self.playerObjects = {}
    self:initUI()
    self._ui.node:setTouchBegan(handler(self, self.onTouchBegin))

    self._ui.csbChat.ui.btnFriend:setClickCallback(function(s,t)
            sgLayerManager:goto("app.views.friend.FriendLayer")
        end)

    if IS_YV_VOICE then
        self._ui.csbChat.ui.btnMsg:setVisible(true)
        self._ui.csbChat.ui.btnMsg:setTouchCallback(handler(self, self.onFriend))
    else
        self._ui.csbChat.ui.btnMsg:setVisible(false)
    end
    

    self._ui.csbChat.ui.btnImg:setClickCallback(function(s,t)
            local layer = requireEx("app.views.chat.ChatFaceLayer"):create(nil, ChatManager.CHAT_TEAM)
            layer:setPosition(cc.p(96, 156))
            self:addChild(layer, 10)
        end)


    self._ui.spFchestOpen:setVisible(false)
    local res = "uieff/ui_chest_open/"
    self.aniFchestOpen = DNFactory:createNormalDN(res, "ui_chest_open")
    self.aniFchestOpen:setPosition(46, 44)
    self._ui.spFchestOpen:addChild(self.aniFchestOpen)


    local spmbk_size = self._ui.spmbk:getContentSize()
    local res = "uieff/ui_jjdz/"
    local ani = DNFactory:createNormalDN(res, "ui_jjdz")
    ani:setPosition(spmbk_size.width * 0.5, spmbk_size.height * 0.5)
    ani:doAnimation("animation2")
    self._ui.spmbk:addChild(ani)

    res = "uieff/ui_jjdz/"
    ani = DNFactory:createNormalDN(res, "ui_jjdz")
    ani:setPosition(spmbk_size.width * 0.5, spmbk_size.height * 0.5)
    ani:doAnimation("animation1")
    self._ui.spmbk:addChild(ani)

    -- res = "uieff/ui_jjdz/"
    -- ani = DNFactory:createNormalDN(res, "ui_jjdz")
    -- ani:setPosition(spmbk_size.width * 0.5, spmbk_size.height * 0.5)
    -- ani:doAnimation("animation")
    -- self._ui.spmbk:addChild(ani)

    local x = self._ui.csbRole2:getPositionX()
    local y = self._ui.csbRole2:getPositionY()
    self._ui.btnInvite:setPosition(cc.p(x, y - 152))
    self._ui.btnQuickInvite:setPosition(cc.p(x, y - 196))

    self._ui.objTimeChests:setPosition(cc.p(x, y - 262))

    
    Event.dispatch(GuideManager.GUIDE_MODEL_INIT_MSG, nil, nil, self)
    self:preInitUI(datas[1])

    local res = "uieff/ui_chest_effect/"
    local ani = DNFactory:createNormalDN(res, "ui_chest_effect")
    ani:setAnchorPoint(0.5, 0.5)
    ani:doAnimation("animation")
    self._ui.fchestAniNode:addChild(ani)
    self._ui.fchestAniNode:setVisible(false)

    local res = "uieff/ui_gameplay/"
    self.aniStart = DNFactory:createNormalDN(res, "ui_gameplay")
    self.aniStart:setPosition(110, 40)
    self.aniStart:doAnimation("animation")
    self._ui.dnStart:addChild(self.aniStart)


    res = "uieff/ui_gameplay/"
    self.aniEnterStart = DNFactory:createNormalDN(res, "ui_gameplay")
    self.aniEnterStart:setPosition(0, 0)
    self.aniEnterStart:doAnimation("animation1")
    self.aniEnterStart:setName("enterStart")
    self._ui.dnEnterStart:addChild(self.aniEnterStart)

    res = "uieff/ui_gameplay/"
    local ani = DNFactory:createNormalDN(res, "ui_gameplay")
    ani:setPosition(110, 40)
    ani:doAnimation("animation2")
    self._ui.dnReady:addChild(ani)


    local res = "uieff/ui_gameplay/"
    ani = DNFactory:createNormalDN(res, "ui_gameplay")
    ani:setPosition(110, 40)
    ani:doAnimation("animation3")
    self._ui.dnCancel:addChild(ani)

    self._ui.btnStartFight:setClickCallback(handler(self, self.onStart))
    self._ui.btnReady:setClickCallback(handler(self, self.onStart))
    self._ui.btnCancel:setClickCallback(handler(self, self.onStart))
    
    self._ui.csbChat.ui.spFriend:setVisible(BadgeManager:getFlag(BadgeSystem.Friend))
    self:refreshFriendChatRedDot()

    self:onEvent(BadgeManager.BADGE_MSG, function (event, data)
        if data.key == BadgeSystem.Chat then
            -- self._ui.csbChat.ui.spMsg:setVisible(data.flag)
        elseif data.key == BadgeSystem.Friend then
            self._ui.csbChat.ui.spFriend:setVisible(data.flag)
        end
    end)

    self:onEvent(FriendMgr:getInstance().FRIEND_CHAT_REDDOT, function (event, data)
        self:refreshFriendChatRedDot()
    end)

    ChatManager:showSmallChat(self, "pvpfree")

    if not self._ui.csbChat.ui.btnMsg:isVisible() then
        self._ui.csbChat:setPositionX(self._ui.csbChat:getPositionX() - 87)
    end
    if not self._ui.csbChat.ui.btnFriend:isVisible() then
        self._ui.csbChat:setPositionX(self._ui.csbChat:getPositionX() - 87)
    end

    self:onEvent("GameState_ChangeGoods", function()
        self:refreshTimeChests(true)
    end)

    local sdate = sgGameState:date(sgGameState:getServerTime())
    local time = tonumber(sgCommon:getDataFromUserDefaule("FreeDayChestTime", "0"))
    if time == 0 and sdate.hour >= 5 then
        sgGameState._pvpFreeDayChests = 0
        sgCommon:setDataToUserDefault("FreeDayChestTime", sgGameState:getServerTime())  
    else
        local ldate = sgGameState:date(time)
        if sdate.day ~= ldate.day and sdate.hour >= 5 then
            sgGameState._pvpFreeDayChests = 0
            sgCommon:setDataToUserDefault("FreeDayChestTime", sgGameState:getServerTime())    
        end
    end

    self:initAchievement()

    self:adjustPos()

    self._ui.sprite50:setVisible(false)
    print("zhenke==================================9999")
    print("zhenke==================================9999")
    print("zhenke==================================9999")
    print("zhenke==================================9999")
end

function P:initAchievement(  )
    self._eventAchievementTag = Event.register(Constants.DISPATCH_ON_ACHIEVEMENT_CHANGE, handler(self, self.onAchievementChange))
    local reqs = ptl.Req28003:create()
    ReqAndResp:callReq(reqs, function(datas) 
        if datas.status == 0 then
            AchievementMgr:getInstance():setAchievementData(datas.achievement)
        end
    end)
    local ani = DNFactory:createNormalDN("uieff/ui_hdpj/", "ui_hdpj")
    ani:setPosition(cc.p(self._ui.btnAchievement:getContentSize().width/2, self._ui.btnAchievement:getContentSize().height/2))
    ani:doAnimation("animation2")
    ani:setName("AchievementAni")
    self._ui.btnAchievement:addChild(ani)
    ani:setVisible(false)
end

function P:onAchievementChange()
    self:setAchievementAni(AchievementMgr:getInstance():hasAchievementShare())
end

function P:setAchievementAni( bshow )
    self._ui.btnAchievement:getChildByName("AchievementAni"):setVisible(bshow)
end

--平刘海设置
function P:adjustPos()
    sgCommon:adaptiveScreen({self._ui.sprite50,self._ui.csbChat,self._ui.spBKStart})
end
-------------------------------------------------------------------------
function P:setStartFightGray(isGray)
    if self.aniStart then
        self.aniStart:setGray(isGray)
    end
    if self.aniEnterStart then        
        self.aniEnterStart:setGray(isGray)
    end
    
    self._isFightGray = isGray
end
-------------------------------------------------------------------------
function P:showStartFight(index)
    if index == 1 then
        self._ui.btnStartFight:setEnabled(true)
        self._ui.btnStartFight:setVisible(true)
        self._ui.btnReady:setVisible(false)
        self._ui.btnCancel:setVisible(false)
    elseif index == 2 then
        self._ui.btnStartFight:setVisible(false)
        self._ui.btnReady:setVisible(true)
        self._ui.btnCancel:setVisible(false)
    elseif index == 3 then
        self._ui.btnStartFight:setVisible(false) 
        self._ui.btnReady:setVisible(false)
        self._ui.btnCancel:setVisible(true)
    end
end


-------------------------------------------------------------------------
function P:onChat(event, args)
    if args.msg_type ~= ChatManager.CHAT_TEAM or args.data_type ~= 3 then
        return
    end

    local faceId = args.content
    local csbRoleUI = self.playerObjects[args.send_playerId]
   
    if tonumber(faceId) then

        -- 表情
        csbRoleUI.spLabelChat:setVisible(false)
        local aniFace = DNFactory:createFaceDN(faceId)
        aniFace:doAnimation("animation", 2, function() aniFace:removeFromParent() end)
        aniFace:setName("aniFace")
        csbRoleUI.chat:removeAllChildren()
        csbRoleUI.chat:addChild(aniFace)
    else
        
        csbRoleUI.chat:removeAllChildren()
        csbRoleUI.spLabelChat:setVisible(true)
        csbRoleUI.lbLabelChat:setString(faceId)

        local dt = cc.DelayTime:create(2)
        local f = cc.CallFunc:create(function() 
            csbRoleUI.spLabelChat:setVisible(false)
        end)

        local action = cc.Sequence:create(dt, f)
        self:runAction(action)
    end
end
-------------------------------------------------------------------------
-- function P:onFaceStr(event,args)
--     local arrRoomPlayerInfo = sgGameState:getRoomManager()._roomInfo.arrRoomPlayerInfo
    
--     local localPlayerId = sgGameState:getUserState().playerId
--     local faceId = args.faceStr
--     local req = ptl.Req16002:create()


--     req.msg_type = ChatManager.CHAT_TEAM
--     req.data_type = 3
--     req.content = faceId    

--     for _, pi in ipairs(arrRoomPlayerInfo) do
--         table.insert(req.target_playerIds, pi.normalUserInfo.playerId)
--     end
--     ReqAndResp:callReq(req, function(obj) end)
-- end
-------------------------------------------------------------------------
function P:update()

    self:updateTimeChests()

    local seconds = InviteManager:getQuickInviteCD(Constants.BATTLETYPE_PPVPP_FREE)
    if seconds > 0 then
        self._ui.lbQITime:setString(seconds.. _T("Pvp.TimeInfo"))
        self._ui.lbQITime:setCustomColor(1,0)
        self._ui.btnQuickInvite:setEnabled(false)
    else
        self._ui.lbQITime:setString(_T("MLR.Qinv"))
        self._ui.lbQITime:setCustomColor(9,0)
        self._ui.btnQuickInvite:setEnabled(true)
    end



    if self._pauseUpdate then
        return
    end

    local seconds = sgGameState:getServerTime() - self.reward_time
    local tick_seconds = tpl_Config.parameter1(40) * 60 - seconds
    if tick_seconds > 0  then
        local hour = math.floor(tick_seconds / 3600)
        local min = math.floor((tick_seconds % 3600 )/ 60)
        if hour == 0 and min == 0  then
            min = 1
        end
        --self._ui.fchestAniNode:setVisible(false)
        self.aniFchestOpen:setVisible(false)
        self._ui.spFchestOpen:setVisible(true)
        self._ui.btnFchest:setVisible(false)
        self._ui.spFchestRoot:setVisible(true)
        self._ui.lbFchestTime:setString(string.format(_T("Pvp.FormatTime"), hour, min))
        self._ui.sprite47:setVisible(false)
    else
    	self._ui.spFchestOpen:setVisible(false)
        self._ui.spFchestRoot:setVisible(false)
        self._ui.btnFchest:setVisible(true)
        self._ui.sprite47:setVisible(true)
    end
end
-------------------------------------------------------------------------
function P:onEnter()
    P.super.onEnter(self)

    self:runAction(cc.CallFunc:create(function ()
        BroadcastManager:showBroadcast(self, 2)
        Event.dispatch(InviteManager.INVITE_NOTICE)
    end))

    self._handleReqId = cc.Director:getInstance():getScheduler():scheduleScriptFunc(handler(self, self.update), 0, false)
    
    cc.SimpleAudioEngine:getInstance():playMusic(CocosEx:getUISound(204), true)
end

-------------------------------------------------------------------------
function P:onExit()
    if self._eventAchievementTag then
        Event.unregister(self._eventAchievementTag)
        self._eventAchievementTag = nil
    end
    P.super.onExit(self)
    sgGameState:getRoomManager():cleanAllCallBack()
    cc.Director:getInstance():getScheduler():unscheduleScriptEntry(self._handleReqId)
    if sgLayerManager:getCurrentScene().__cname ~= "PlayScene" then
        cc.SimpleAudioEngine:getInstance():playMusic(CocosEx:getUISound(201), true)
    end
    self:releaseDragonNode()

end

function P:releaseDragonNode()
    DragonNode:removeDragonBones("ui_chest_effect")
    DragonNode:removeDragonBones("ui_chest_open")
    DragonNode:removeDragonBones("ui_rcdjdb")
    DragonNode:removeDragonBones("ui_hdpj")
end
-----------------------------------------------------------------------
function P:initUI()
    self._ui.btBack:setClickCallback(function(s, t)
        self._isRelease = true
        sgGameState:getRoomManager():exitRoom( function(data)
            if not sgLayerManager:getLayer("app.views.pvp.PvpFreeLayer") then
                return
            end
            self:onRelease()
            ChatManager:clearMsg(ChatManager.CHAT_TEAM)
        end )
    end)

    self._ui.btnLife:setClickCallback(function(s, t)
        self._ui.uiObjLife:setVisible(true)
        self._ui.uiObjDay:setVisible(false)
    end)
    self._ui.btnDay:setClickCallback(function(s, t)
        self._ui.uiObjLife:setVisible(false)
        self._ui.uiObjDay:setVisible(true)
    end)
    self._isLockChestTouch = false
    self:refreshTimeChests()
end
-----------------------------------------------------------------------
function P:refreshTimeChests(isChangeGoods)
    sgPvpFreeTimeChestMgr:initTimeChestsInPack()
    local cfgs = sgPvpFreeTimeChestMgr:getTimeChests()
    for i=1, 4 do 
        local cfg = cfgs[i]
        if cfg then
            self:initTimeChestObject(i, cfg)
            if not isChangeGoods then
                self:newTimeChest(i, cfg)
            end    
        else
            local time_chest = self._ui["objTimeChest" .. tostring(i)]
            time_chest.ui.btnChest:setVisible(false)
            time_chest.ui.lbDiamonds:setVisible(false)
            time_chest.ui.spRefreshTime:setVisible(false)
            time_chest.ui.objAni:setVisible(false)
            time_chest.ui.objeff:setVisible(false)
        end
    end

end
-----------------------------------------------------------------------
function P:newTimeChest(index, config)
    -- 判断是否解锁
    if config.bag_item.unlock ~= 0 then
        return
    end 
    self._isLockChestTouch = true
    local time_chest = self._ui["objTimeChest" .. tostring(index)]
    local goodsId = config.bag_item.goodsId
    local aniName = sgPvpFreeTimeChestMgr:getChestAnimationByGoodsId(goodsId)
    
    time_chest.ui.btnChest:setVisible(true)
    time_chest.ui.lbRefreshTime:setVisible(false)
    time_chest.ui.spRefreshTime:setVisible(false)
    time_chest.btnEffect:setVisible(false)
    time_chest.ui.lbDiamonds:setVisible(config.bag_item.unlock ~= 0)

    time_chest.rcdjdb:stopAllActions()
    local dt = cc.DelayTime:create(1)
    local f = cc.CallFunc:create(function()
        time_chest.ui.btnChest:setVisible(false)
        time_chest.btnEffect:setVisible(false)
        time_chest.rcdjdb:setVisible(true)
        time_chest.rcdjdb:doAnimation(aniName, 1, function()
            time_chest.ui.btnChest:setVisible(true)
            time_chest.rcdjdb:setVisible(false)
            time_chest.ui.lbRefreshTime:setVisible(true)
            time_chest.ui.spRefreshTime:setVisible(true)
            time_chest.btnEffect:setVisible(true)
            time_chest.ui.lbDiamonds:setVisible(config.bag_item.unlock ~= 0)
            self._isLockChestTouch = false
        end)        
    end)
    local action = cc.Sequence:create(dt, f)
    time_chest.rcdjdb:runAction(action)
end
-----------------------------------------------------------------------
function P:initTimeChestObject(index, config)
    local pic_path = sgCommon:getGoodsIconPath(config.bag_item.goodsId)
    local sp = UiManager:getInstance():getSpriteByName(pic_path)
    local time_chest = self._ui["objTimeChest" .. tostring(index)] 
    if not time_chest then
        return
    end

    if not time_chest.rcdjdb then
        local res = "uieff/ui_rcdjdb/"
        time_chest.rcdjdb = DNFactory:createNormalDN(res, "ui_rcdjdb")
        time_chest.ui.objAni:addChild(time_chest.rcdjdb)
    end

    if not time_chest.effect then
        local res = "uieff/ui_chest_effect/"
        time_chest.effect = DNFactory:createNormalDN(res, "ui_chest_effect")
        time_chest.ui.objAni:addChild(time_chest.effect)
        time_chest.effect:doAnimation("animation")
    end

    if not time_chest.btnEffect then
        local res = "uieff/ui_rcdjdb/"
        time_chest.btnEffect = DNFactory:createNormalDN(res, "ui_rcdjdb")
        time_chest.ui.objeff:addChild(time_chest.btnEffect)
    end

    time_chest.ui.objeff:setVisible(true)
    time_chest.ui.objAni:setVisible(true)
    time_chest.ui.btnChest:setVisible(true)
    time_chest.effect:setVisible(false)
    time_chest.rcdjdb:setVisible(false)
    time_chest.rcdjdb:stopAllActions()
    time_chest.btnEffect:setVisible(config.bag_item.unlock == 0)

    local name = sgPvpFreeTimeChestMgr:getChestEffectByGoodsId(config.bag_item.goodsId)
    time_chest.btnEffect:doAnimation(name)


    if sp then time_chest.ui.btnChest:setNormalImage(sp) end
    time_chest.ui.btnChest:setClickCallback(function()
        -- 动画播放完成前不给操作
        if self._isLockChestTouch then
            return
        end
        -- 背包道具数据
        local bag_item = config.bag_item

        sgPvpFreeTimeChestMgr:selectTimeChestId(bag_item.id)
        sgPvpFreeTimeChestMgr:selectTimeChestGoodsId(bag_item.goodsId)

        -- 解锁时间
        local usetimestamp = bag_item.usetimestamp
        -- 服务器时间
        local servertime = sgGameState:getServerTime()
        -- 刷新时间
        local refresh_time = usetimestamp - servertime
        -- 判断是否到解锁时间
        if refresh_time <= 0 and bag_item.unlock ~= 0 then
            sgPvpFreeTimeChestMgr:rewardByServerData(config)
            return
        end
        sgLayerManager:goto("app.views.pvp.PvpFreeTimeChestLookLayer")
    end)

    -- 设置显示时间
    local time = config.cfg_line.parameter1 * 60
    self:clcChestTime(time_chest, config, time)
end
-----------------------------------------------------------------------
function P:clcChestTime(time_chest, config, time)
    local lbRefreshTime = time_chest.ui.lbRefreshTime
    local spRefreshTime = time_chest.ui.spRefreshTime
    local lbDiamonds = time_chest.ui.lbDiamonds
    lbRefreshTime:setVisible(true)
    spRefreshTime:setVisible(true)
    lbDiamonds:setVisible(config.bag_item.unlock ~= 0)
    return sgPvpFreeTimeChestMgr:updateChestByTime(config, lbRefreshTime, spRefreshTime, lbDiamonds, time)
end
-----------------------------------------------------------------------
function P:updateTimeChest(index, config)
    local time_chest = self._ui["objTimeChest" .. tostring(index)]
    local bag_item = config.bag_item
    if bag_item.unlock ~= 0 then
        local refresh_time = self:clcChestTime(time_chest, config)
        time_chest.btnEffect:setVisible(false)
        local effect = time_chest.effect
        if refresh_time <= 0 and not effect:isVisible() then
            effect:setVisible(true)
            effect:doAnimation("animation")
        end
    end
end
-----------------------------------------------------------------------
function P:updateTimeChests()
    local time_chests = sgPvpFreeTimeChestMgr:getTimeChests()
    for i, cfg in ipairs(time_chests) do
        self:updateTimeChest(i, cfg)
    end   
end
-----------------------------------------------------------------------
function P:onStartBattle(data)
    --print(debug.traceback())
    if data.status == 2 then
        printInfo("[pvpFreeLayer:onStartBattle] battleType is error")
        return
    end

    if data.status == 2 then
        printInfo("[pvpFreeLayer:onStartBattle] not found room")
        return
    end

    if data.status == 3 then
        printInfo("[pvpFreeLayer:onStartBattle] op is error")
        return
    end

    if data.status == 4 then
        printInfo("[pvpFreeLayer:onStartBattle] in op")
        return
    end

    if data.status == 5 then
        printInfo("[pvpFreeLayer:onStartBattle] in fighting")
        return
    end

    if data.status == 6 then
        printInfo("[pvpFreeLayer:onStartBattle] not open")
        return
    end

    if data.status == 7 then
        printInfo("[pvpFreeLayer:onStartBattle] player is not ready")
        return
    end

    -- if data.status == 8 then
    --     printInfo("[pvpFreeLayer:onStartBattle] in op")
    --     return
    -- end

    if data.status == 9 then
        printInfo("[pvpFreeLayer:onStartBattle] choose hero")
        return
    end


    local vs = sgLayerManager:getLayer("app.views.pvp.VsLayer")
    if vs then
        if data.status == 0 and data.op == 0 then
            vs:stopSchedule()       
            vs:onRelease()
        end
        return
    end

    local hostId = sgGameState:getRoomManager()._roomInfo.hostId
    local pvpType = 2 
    if not self._ui.csbRole2.ui.btnLock:isVisible() then
        pvpType = 1
    end

    if sgGameState:getRoomManager()._isLocal then
        pvpType = 1
    elseif #sgGameState:getRoomManager()._roomInfo.arrRoomPlayerInfo >= 2 then
        pvpType = 2
    end


    local s = _T("Pvp.Team")
    if pvpType == 1 then
        s = _T("Pvp.Free")
    end

    data.pvpRoomInfo.arrRoomPlayerInfo = sgGameState:getRoomManager()._roomInfo.arrRoomPlayerInfo
    sgLayerManager:goto("app.views.pvp.VsLayer", data, pvpType, Constants.BATTLETYPE_PPVPP_FREE)
end
-----------------------------------------------------------------------
function P:getLockValue()
    if sgCommon:getDataFromUserDefaule("pveRoomLock") == "" then
        sgCommon:setDataToUserDefault("pveRoomLock", 0)
        return 0
    end
    return tonumber(sgCommon:getDataFromUserDefaule("pveRoomLock"))
end
-----------------------------------------------------------------------
function P:setLockValue(val)
    sgCommon:setDataToUserDefault("pveRoomLock", val)
end
-- -----------------------------------------------------------------------
function P:overTime()
    local localPlayerId = sgGameState:getUserState().playerId
    local hostId = sgGameState:getRoomManager()._roomInfo.hostId
    if localPlayerId ~= hostId then
        return
    end

    local overTick = os.time()

    local layerName = "app.views.common.CommonDialog"
    local title = _T("")
    local lbYes = _T("Pvp.pvpfree.info1")
    local lbNo = _T("Pvp.pvpfree.info2")
    local content = _T("Pvp.pvpfree.info3")
    sgLayerManager:goto(layerName, 1, title, content, function()
        if os.time() - overTick <= 10 then
            self._isOverTime = true
            self:onStart()
            self._isOverTime = false
        else
            self:onStart()
        end
        return
    end)
    sgLayerManager._curLayer._ui.lblConfirm:setString(lbYes)
    sgLayerManager._curLayer._ui.lblCancel:setString(lbNo)
end

-----------------------------------------------------------------------
function P:initVIP(csbRoleUI, pi)
    if pi.normalUserInfo.bg_frame and pi.normalUserInfo.bg_frame > 0 then
        local spIcon = sgCommon:changeBattleRoomBgImage(pi.normalUserInfo.bg_frame, csbRoleUI.objVip)
        spIcon:setScaleX(-0.8)
        spIcon:setScaleY(0.8)
        spIcon:setPosition(-2, -20)
    end
end

-----------------------------------------------------------------------
function P:updatePlayerNode()   
    if self._isRelease then
        return
    end

    self.playerObjects = {}
    local hostId = sgGameState:getRoomManager()._roomInfo.hostId
    local localPlayerId = sgGameState:getUserState().playerId
    local roomInfo = sgGameState:getRoomManager()._roomInfo
    local arrRoomPlayerInfo = sgGameState:getRoomManager()._roomInfo.arrRoomPlayerInfo
    local csbRoles = {}

    for _, pi in ipairs(arrRoomPlayerInfo) do
        local nuf = pi.normalUserInfo
        if nuf.playerId == localPlayerId then
            csbRoles[nuf.playerId] = self._ui.csbRole1
        else
            csbRoles[nuf.playerId] = self._ui.csbRole2
        end
    end
    self._ui.csbRole2.ui.spRoleBK:setScale(0.8)
    self._ui.csbRole2.ui.objVip:setScale(0.8)
    self._ui.csbRole2.ui.objReady:setScale(0.9)

    if #arrRoomPlayerInfo <= 1 then
        if not self._isInitData then
            local csbRoleUI = self._ui.csbRole2.ui  
            csbRoleUI.spOwner:setVisible(false)
            csbRoleUI.btnUnlock:setVisible(true)
            csbRoleUI.btnLock:setVisible(false)

            self._ui.btnInvite:setVisible(false)
            self._ui.btnQuickInvite:setVisible(false)

            if not self._isBackToRoom then
                self:setLockValue(1)
            end

            self._isInitData = true
        else
            local csbRoleUI = self._ui.csbRole2.ui
            local lockVal = self:getLockValue()

            csbRoleUI.btnLock:setVisible(lockVal <= 0)
            csbRoleUI.btnUnlock:setVisible(lockVal > 0)

            self._ui.btnInvite:setVisible(lockVal <= 0)
            self._ui.btnQuickInvite:setVisible(lockVal <= 0)
        end
    else
        self._ui.btnInvite:setVisible(false)
        self._ui.btnQuickInvite:setVisible(false)
    end

    for i, pi in ipairs(arrRoomPlayerInfo) do

        --local csbRoleUI = csbRoles[i].ui
        local nuf = pi.normalUserInfo
        local csbRoleUI = csbRoles[nuf.playerId].ui
        self.playerObjects[nuf.playerId] = csbRoleUI

        -- 移除数据
        csbRoleUI.objVip:removeAllChildren()

        --调整称号显示
        local chatdeltaY = 38
        if nuf.title_frame and nuf.title_frame ~= 0 then
            csbRoleUI.sprTitleFrame:setVisible(true)
            csbRoleUI.sprTitleFrame:setSpriteFrame(UiManager:getInstance():getFrameByName(tpl_Goods[nuf.title_frame].pic_path..".png"))
            -- csbRoleUI.spLabelChat:setPositionY(324 + chatdeltaY)
            -- csbRoleUI.chat:setPositionY(316 + chatdeltaY)
        else
            csbRoleUI.sprTitleFrame:setVisible(false)
            -- csbRoleUI.spLabelChat:setPositionY(324)
            -- csbRoleUI.chat:setPositionY(316)
        end
        
        --csbRoleUI.lbLevel:setString(tostring(nuf.level))
        csbRoleUI.spLevel:setTexture(sgCommon:getLevelPath(nuf.level))

        -- 设置vip
        local vipSize = csbRoleUI.spVip:getContentSize() 
        local vipIcon = sgCommon:createVIPIcon(nuf.vipLv)
        vipIcon:setPosition(cc.p(vipSize.width*0.5, vipSize.height*0.5))
        csbRoleUI.spVip:addChild(vipIcon)
        if nuf.vipLv == 0 then
            csbRoleUI.spVip:setVisible(false)
            csbRoleUI.spMaster:setPosition(14, 197)
        else
            csbRoleUI.spVip:setVisible(true)
            csbRoleUI.spMaster:setPosition(14, 147)
        end

        --csbRoleUI.lbVip:setString(tostring(nuf.vipLv))
        csbRoleUI.lbPlayerName:setString(nuf.name)

        csbRoleUI.spMaster:setVisible(nuf.playerId == roomInfo.hostId)
        
        csbRoleUI.btnClose:setVisible(nuf.playerId ~= roomInfo.hostId and nuf.playerId ~= localPlayerId)
        
        csbRoleUI.btnClose:setTag(nuf.playerId)

        csbRoleUI.spReady:setVisible(false)
        if not csbRoleUI.aniReady then
            res = "uieff/ui_vszb/"
            csbRoleUI.aniReady = DNFactory:createNormalDN(res, "ui_vszb")
            csbRoleUI.aniReady:setAnchorPoint(0.5, 0.5)
            csbRoleUI.aniReady:setPosition(0, -90)
            csbRoleUI.aniReady:setVisible(false)
            csbRoleUI.objReady:addChild(csbRoleUI.aniReady)
        end
  
        self:initVIP(csbRoleUI, pi)
        
        csbRoleUI.btnLock:setVisible(false)

        csbRoleUI.btnUnlock:setVisible(false)
        
        csbRoleUI.spOwner:setVisible(true)

        csbRoleUI.lbUnionName:setVisible(false)
        if nuf.guildName then 
            local x = csbRoleUI.lbPlayerName:getPositionX()
            local size = csbRoleUI.lbPlayerName:getContentSize()
            csbRoleUI.lbUnionName:setPositionX(x + size.width * 0.5)
            csbRoleUI.lbUnionName:setVisible(nuf.guildName ~= "")
            csbRoleUI.lbUnionName:setString("<".. nuf.guildName .. ">")
        end

        local boneNode = csbRoleUI.boneNode
        boneNode:removeAllChildren()

        local currentSuitId = nuf.heroInfo.suitId
        if not currentSuitId or currentSuitId == 0 then
            currentSuitId = 10101
        end
        local suitName = tpl_Goods.pic_path(currentSuitId)
        local dnPlayer = DNFactory:createUiNode(suitName, Constants.DIRECTION_LEFT)
        --
        dnPlayer:doCombAnimations( { { "stand", 3 } })    
        boneNode:addChild(dnPlayer)


        if localPlayerId ~= nuf.playerId then
            dnPlayer:setScale(0.8)
            csbRoleUI.aniReady:setScale(0.9)
            csbRoleUI.objReady:setPositionY(131 -16)
            csbRoleUI.objVip:setPositionY(131 -20)
        else
            csbRoleUI.attObj:setPosition(0, 30)
        end

        self._ui.btnInvite:setClickCallback(function(s,t)
            sgLayerManager:goto("app.views.invite.InviteLayer", self.battleType, sgGameState:getRoomManager()._roomInfo.roomId)
        end)

        self._ui.btnQuickInvite:setClickCallback(function(s,t) 
            InviteManager:quicklyInvite(self.battleType, sgGameState:getRoomManager()._roomInfo.roomId)
        end)

    end

    for _, v in pairs({self._ui.csbRole1, self._ui.csbRole2}) do 
        local csbRoleUI = v.ui
        csbRoleUI.btnClose:setClickCallback(function(s, t)            
            local req = ptl.Req4016:create()
            local arrRoomPlayerInfo = sgGameState:getRoomManager()._roomInfo.arrRoomPlayerInfo
            req.roomId = sgGameState:getRoomManager()._roomInfo.roomId
            req.playerId = sgGameState:getUserState().playerId
            req.kickOutPlayerId = s:getTag() 
            req.battleType = self.battleType
            self.kickOutPlayerId = req.kickOutPlayerId
            ReqAndResp:callReq(req, function(data)
                if data.status == 0 then
                    local csbRoleUI = self.playerObjects[self.kickOutPlayerId]
                    -- 移除数据
                    csbRoleUI.objVip:removeAllChildren()
                    csbRoleUI.btnClose:setVisible(false)
                    csbRoleUI.spOwner:setVisible(false)
                    csbRoleUI.spReady:setVisible(false)
                    csbRoleUI.aniReady:setVisible(false)
                    self:setStartFightGray(false)
                    self:showStartFight(1)                   
                    self:onLockMsg(0)
                    self._ui.btnStartFight:setEnabled(data.status == 0)
                end
            end )
        end)

        csbRoleUI.btnLock:setClickCallback(function(s, t) self:onLockMsg(1) end)
        csbRoleUI.btnUnlock:setClickCallback( function(s, t) self:onLockMsg(0) end)
    end

    local isNewAhv,ahv_id,isFirst = AchievementMgr:getInstance():getNewAhvId()
    if isNewAhv then
        if not self.bgEffect then
            local btnSize = self._ui.btnAchievement:getContentSize()
            self.bgEffect = DNFactory:createNormalDN("uieff/ui_hdpj/", "ui_hdpj")
            self.bgEffect:setPosition(cc.p(btnSize.width/2,btnSize.height/2))
            self._ui.btnAchievement:addChild(self.bgEffect,0)       
            if isFirst then 
                self.bgEffect:doAnimation("animation1", 1, function()
                    self.bgEffect:doAnimation("animation2")
                end)
            else
                self.bgEffect:doAnimation("animation2")
            end
        else
            self.bgEffect:setVisible(true)
        end
    else
        if self.bgEffect then
            self.bgEffect:setVisible(false)
        end
    end
    self._ui.btnAchievement:setClickCallback(function(s, t)
        if self.bgEffect then
            self.bgEffect:setVisible(false)
        end
        sgLayerManager:autoGoto("app.views.achievement.AchievementLayer",ahv_id)
        ahv_id = 0
    end)


    local function addGregoryLabel(text)
        if not text then
            return
        end

        local obj = UiObject:create()
        obj:setAnchorPoint(cc.p(0.500,0.500))
        obj:setContentSize(cc.size(275,38))


        local res = "uieff/ui_hdpj/"
        local ani = DNFactory:createNormalDN(res, "ui_hdpj")
        ani:setAnchorPoint(0.5, 0.5)
        ani:doAnimation("animation")
        ani:setPosition(138, 16)
        obj:addChild(ani)

        local label = cc.Label:create()
        label:setName("lbGregory2")
        label:setSystemFontSize(20)
        label:setString(text)
        label:setDimensions(label:getContentSize().width * 1.2, 38)
        label:setAnchorPoint(0.0, 0.5)
        label:setCustomColor(15, 2)
        label:setPosition(50, 12)
        obj:addChild(label)

        self._ui.lboxAchievement:addItem(obj)
    end

    local results = sgGameState:getRoomManager().results
    --results = {{pvpType=1,total1=999, total2=999, win=999,killNum=999,damage=999}}
    if results and #results > 0 then
        -- local killCount = 0
        -- local totalFight = 0
        -- local text = nil
        -- local winCount = 0
        for i, v in  ipairs(results) do
            if i == 1 then
                local totalFight = math.max(1, (v.total1 + v.total2))
                local p = math.floor((v.win / totalFight * 100))
                self._ui.lb1v1FC:setString(v.total1 > 0 and tostring(v.total1) or "0")
                self._ui.lb2v2FC:setString(v.total2 > 0 and tostring(v.total2) or "0")
                self._ui.lbWinCount:setString(v.win > 0 and tostring(v.win) or "0")
                self._ui.lbKillCount:setString(v.killNum > 0 and tostring(v.killNum) or "0")
                if v.assistKill then
                    self._ui.lbHelpCount:setString(v.assistKill > 0 and tostring(v.assistKill) or "0")
                end
                self._ui.lbFP:setString(p > 0 and tostring(p) .. "%" or "0")
        

            elseif i == 2 then
                local totalFight = math.max(1, (v.total1 + v.total2))
                local p = math.floor((v.win / totalFight * 100))
                self._ui.lbTotal1v1FC:setString(v.total1 > 0 and tostring(v.total1) or "0")
                self._ui.lbTotal2v2FC:setString(v.total2 > 0 and tostring(v.total2) or "0")
                self._ui.lbTotalWinCount:setString(v.win > 0 and tostring(v.win) or "0")
                self._ui.lbTotalKillCount:setString(v.killNum > 0 and tostring(v.killNum) or "0")
                if v.assistKill then
                    self._ui.lbTotalHelpCount:setString(v.assistKill > 0 and tostring(v.assistKill) or "0")
                end
                self._ui.lbTotalFP:setString(p > 0 and tostring(p) .. "%" or "0")
            end
        end
    end

    local x = self._ui.label3:getPositionX() + self._ui.label3:getContentSize().width * 2
    self._ui.sprite47:setPositionX(x + 16)

    x = self._ui.sprite28:getPositionX() + self._ui.sprite28:getContentSize().width
    self._ui.spAchievementObj:setPositionX(x - 4)

    self._ui.btnItem1:setClickCallback(function(s, t)
            local roomId = sgGameState:getRoomManager()._roomInfo.roomId
            sgLayerManager:goto("app.views.item.ItemLayer", self.battleType, nil, handler(self, self.buildItems), roomId)
    end)

    self._ui.btnItem2:setClickCallback(function(s, t)
            local roomId = sgGameState:getRoomManager()._roomInfo.roomId
            sgLayerManager:goto("app.views.item.ItemLayer", self.battleType, nil, handler(self, self.buildItems), roomId)
    end)

    self:buildItems()

    if self._isBackToRoom and #arrRoomPlayerInfo <=1 then
        self:onLockMsg(self:getLockValue())
    end

    self:runReq4020()
    for i, pi in ipairs(arrRoomPlayerInfo) do
        local nuf = pi.normalUserInfo
        local ready_data = {}
        ready_data.readyPlayerId = nuf.playerId
        ready_data.status = pi.status
        self:roomMemberReady(ready_data)
    end
end
-----------------------------------------------------------------------
function P:runReq4020()
    local req = ptl.Req4020:create()
    req.type = 1
    req.rewardType = 1
    ReqAndResp:callReq(req, function(data)
        if self.preInitUI then
            self:preInitUI(data)
        end
    end)
end
-----------------------------------------------------------------------
function P:preInitUI(data)
    if data.status ~= 0 then
        return
    end
    sgGameState:getRoomManager():setPvpFreeDayWinCount(data.count)
    local battleBoxs = data.battleBoxs
    local line = P.getLevelPoint(data.score)
    local uiMgr = UiManager:getInstance()
    local cur_point = data.score - line.last.total
    local levelPoint = line.total - line.last.total
    local str_rank_exp = tostring(cur_point) .. "/" .. tostring(levelPoint)

    if levelPoint == 0 then
        str_rank_exp = "Max"
    end
    
    self._ui.lbRankLevelExp:setVisible(true)
    self._ui.lbRankLevelExp:setString(str_rank_exp) 
    self._ui.psRankExp:setPercentage(cur_point/levelPoint * 100.0)    
    self._ui.spRankLevel:setSpriteFrame(uiMgr:getFrameByName(line.last.military .. ".png"))
    self._ui.lbRankLevel:setString("Lv." .. tostring(line.last.show_level))



    if not battleBoxs then
        return
    end

    --local line = P.getLevelPoint(data.score)
    self:initPvpReward(battleBoxs, line)

end

-----------------------------------------------------------------------
function P:initPvpReward(battleBoxs, line)
    if not battleBoxs[1] then
        battleBoxs[1] = {}
        battleBoxs[1].type = 1
        battleBoxs[1].count = 0
        battleBoxs[1].time = 0
        battleBoxs[1].index = 1
        battleBoxs[1].rewardT = 0
        battleBoxs[1].win = 0
        battleBoxs[1].kill = 0
    end
    -- dump(battleBoxs)
    -- dump(line)

    local v = battleBoxs[1]
    -- local rewardLine = P.getLevelReward(v.index, line.last.level_id, v.count)
    local rewardLine = P.getLevelReward(1, line.last.level_id, v.count)
    local checkCount = v.win > rewardLine.needfight and rewardLine.needfight or v.win
    self._ui.lbRewardExp:setString(tostring(checkCount) .. "/" .. tostring(rewardLine.needfight))
    self._ui.psRewardExp:setPercentage(checkCount / rewardLine.needfight * 100.0)
    
    self.battleBoxs = v
    self.reward_time = sgGameState:getServerTime()
    self.reward_time = v.rewardT
    self:update()

    --v.win = 10
    if v.win >= rewardLine.needfight then
        self._ui.fchestAniNode:setVisible(true)
        sgCommon:playChestShakeAnimation(self._ui.btnFchest)
    end

    self._ui.btnFchest:setClickCallback( function(s, t)
        local items = P.WarfareReward[v.index][line.last.level_id]
        local next_items = P.WarfareReward[v.index][line.level_id] 
        if line.isLast then
            items = P.WarfareReward[v.index][line.level_id]
            next_items = {}
        end
                        
        if v.win < rewardLine.needfight then
            if self:getChildByName("PvpFreeViewChestItemsLayer") then
                return
            end
            local si = require("app.views.pvp.PvpFreeViewChestItemsLayer"):new()
            si:setName("PvpFreeViewChestItemsLayer")
            si:setCurrentItems(items)
            si:setNextItems(next_items)
            si:setSafePosition(self._ui.btnFchest, self._ui.node)
            self:addChild(si)
            si._ui.label2:setVisible(#next_items <= 0)
            return
        end

        local req = ptl.Req4020:create()
        req.type = 2
        req.rewardType = 1
        ReqAndResp:callReq(req, function(data)
            if data.status ~= 0 then
                return
            end
            sgGameState:getRoomManager():setPvpFreeDayWinCount(data.count)
            local rewardLine = P.getLevelReward(v.index, line.last.level_id, v.count)
            self._ui.lbRewardExp:setString(tostring(0) .. "/" .. tostring(rewardLine.needfight))
            self._ui.psRewardExp:setPercentage(0.0);
            --TipsLayer.showTips(_T("Pvp.sReward"))
            self._ui.fchestAniNode:setVisible(false)
            self._ui.btnFchest:stopAllActions()

            self._ui.btnFchest:setVisible(false)           
            self._ui.spFchestOpen:setVisible(true)

            self._pauseUpdate = true

            self.aniFchestOpen:doAnimation("animation", 1, function()

                --self._ui.btnFchest:setVisible(true)
                self._ui.btnFchest:setRotation(0)
                self._pauseUpdate = false         
                --self._ui.spFchestOpen:setVisible(false)


                for i, item in ipairs(items) do
                    item.rewardId = item.goods_id
                    item.rewardNum = item.count
                end
                sgLayerManager:autoGoto("app.views.common.ReceiveLayer", items)
                self:runReq4020()
            end)
        end )
    end )
end

-----------------------------------------------------------------------
function P:onTouchBegin(touch)
    if not self._coolTime then
        self._coolTime = os.time()
    end

    if os.time() - self._coolTime < 1 and GuideManager:getIsPvpStep() then
       return true 
    end

    local p = touch:getLocation()
    p = self:convertToNodeSpace(p)
    local loaclPlayerId = sgGameState:getUserState().playerId
    local csbRoles = {self._ui.csbRole1, self._ui.csbRole2}
    for playerId, ui in pairs(self.playerObjects) do
        
        if ui.spOwner:isVisible() and playerId == loaclPlayerId then
            local pos = ui.node:getParent():convertToWorldSpace(cc.p(ui.node:getPosition()))
            local size = ui.node:getContentSize()
            local ax = ui.node:getAnchorPoint().x
            local ay = ui.node:getAnchorPoint().y
            local x = pos.x - size.width * ax
            local y = pos.y - size.height * ay
            local w = size.width * ui.node:getScaleX()
            local h = size.height * ui.node:getScaleY()
            local rect = cc.rect(x, y, w, h)

            if cc.rectContainsPoint(rect, p) then
                local roomId = sgGameState:getRoomManager()._roomInfo.roomId
                sgLayerManager:goto("app.views.adventure.SelectHeroLayer", self.battleType, nil, roomId)
                return true
            end
        end
    end
    return true
end

-----------------------------------------------------------------------
function P:onLockMsg(lockVal)
    if not sgGameState:getRoomManager()._roomInfo then
        return
    end
    local hostId = sgGameState:getRoomManager()._roomInfo.hostId
    local localPlayerId = sgGameState:getUserState().playerId
    local req = ptl.Req4015:create()
    
    req.roomId = sgGameState:getRoomManager()._roomInfo.roomId
    req.playerId = localPlayerId
    req.lock = lockVal
    req.battleType = self.battleType
    ReqAndResp:callReq(req, function(data)
        if data.status ~= 0 then
            return
        end
        self:setLockValue(lockVal)
        local arrRoomPlayerInfo = sgGameState:getRoomManager()._roomInfo.arrRoomPlayerInfo
        if #arrRoomPlayerInfo >= 2 then
            return
        end

        local csbRoleUI = self._ui.csbRole2.ui
        csbRoleUI.btnLock:setVisible(lockVal <= 0)
        csbRoleUI.btnUnlock:setVisible(lockVal > 0)
        self._ui.btnInvite:setVisible(lockVal <= 0)
        self._ui.btnQuickInvite:setVisible(lockVal <= 0)

    end )
end
-----------------------------------------------------------------------
function P:onStart(s, t)


    local function run()
        local hostId = sgGameState:getRoomManager()._roomInfo.hostId
        local playerId = sgGameState._userState.playerId

        if self._isFightGray and hostId == playerId then
            return
        end

        if P.Start_Time and P.Start_Time - os.time() > 0 then
            TipsLayer.showTips(_T("Pvp.StartTimeInfo"))
            return
        end

        P.Start_Time = os.time() + 3

        local arrRoomPlayerInfo = sgGameState:getRoomManager()._roomInfo.arrRoomPlayerInfo
        local isOkFight = 0
        local pvpType = 2 
        if not self._ui.csbRole2.ui.btnLock:isVisible() then
            pvpType = 1
        end
        if sgGameState:getRoomManager()._isLocal then
            pvpType = 1
        elseif #arrRoomPlayerInfo >= 2 then
            pvpType = 2
        end


        if playerId ~= hostId then
            local isReady = self.playerObjects[playerId].spReady:isVisible()
            self.playerObjects[playerId].spReady:setVisible(not isReady)
            local req = ptl.Req4004:create()
            req.status =(isReady and 0 or 1)
            req.roomId = sgGameState:getRoomManager()._roomInfo.roomId
            req.playerId = sgGameState:getUserState().playerId
            req.battleType = self.battleType
            ReqAndResp:callReq(req, function(data) end )
            self:showStartFight(isReady and 2 or 3)


            if not isReady then
                self.playerObjects[playerId].aniReady:setVisible(true)
                self.playerObjects[playerId].aniReady:doAnimation("animation1")
            else
                self.playerObjects[playerId].aniReady:doAnimation("animation2", 1, function()
                    self.playerObjects[playerId].aniReady:setVisible(false)
                end)
            end


        else
            for k, player in pairs(self.playerObjects) do
                isOkFight = isOkFight + (player.spReady:isVisible() and 1 or 0)
            end
        end
        if isOkFight >= #arrRoomPlayerInfo then
            LoadingLayer.isShowLoading(true)
            sgGameState:getRoomManager():match(pvpType, 1, nil, self._isOverTime)
        end
    end

    local chest_count = sgGameState:getPvpFreeCountByChests() 
    if sgPvpFreeTimeChestMgr:isFullChests(chest_count) then
        local data = {}
        data.dayKey = "PvpFree_ChestsDayDialog"
        data.content = "pvp.chestsInBag"
        data.confirmCB = run
        data.hour = 5
        sgLayerManager:autoGoto("app.views.common.CommonDayDialog", data) 
    else
        run()
    end
end
-----------------------------------------------------------------------
function P:roomMemberReady(data)
    if not sgGameState:getRoomManager()._roomInfo then
        return
    end
    local hostId = sgGameState:getRoomManager()._roomInfo.hostId
    local playerId = sgGameState._userState.playerId
    local  ui = self.playerObjects[data.readyPlayerId]
    if not ui then
        return
    end

    if data.readyPlayerId == hostId then
        ui.spReady:setVisible(true)
        ui.aniReady:setVisible(false)
        ui.aniReady:doAnimation("animation4")
    else
        if data.status ~= 0 then
            ui.spReady:setVisible(true)
            ui.aniReady:setVisible(true)
            ui.aniReady:doAnimation("animation1")
        else
            ui.spReady:setVisible(false)
            ui.aniReady:doAnimation("animation2", 1, function()
                ui.aniReady:setVisible(false)
            end)
        end
    end
    
    if data.readyPlayerId ~= hostId and data.readyPlayerId == playerId then
        self:showStartFight(data.status ~= 0 and 3 or 2)  
    elseif data.readyPlayerId ~= playerId then
        self:showStartFight(1)
        self:setStartFightGray(data.status == 0)
        self._ui.btnStartFight:setEnabled(data.status ~= 0)
    end
end
-----------------------------------------------------------------------
function P:syncKickPlayerCallBack(data)
    if data.status ~= 6 then
        print("P:syncKickPlayerCallBack not kick")
        return
    end

    if sgGameState._userState.playerId ~= data.playerId then
        print("sgGameState._userState.playerId ~= data.playerId")
        return
    end


    if sgLayerManager._curLayer.__cname == "SelectHeroLayer" then
        sgLayerManager._curLayer:onRelease()
    end
    if sgLayerManager._curLayer.__cname == "ItemLayer" then
        sgLayerManager._curLayer:onRelease()
    end
    -- if sgLayerManager._curLayer.__cname == "InviteLayer" then
    --     sgLayerManager._curLayer:onRelease()
    -- end

    ChatManager:clearBattleChat()
    self:onRelease()
end

-----------------------------------------------------------------------
function P:syncPlayerLevelup(data)

    local csbRoleUI = self.playerObjects[data.changePlayerId]
    if not csbRoleUI then
        return
    end

    if data.level <= 0 then
        return
    end

    csbRoleUI.spLevel:setTexture(sgCommon:getLevelPath(data.level))
    
    local arrRoomPlayerInfo = sgGameState:getRoomManager()._roomInfo.arrRoomPlayerInfo
    for _, pi in pairs(arrRoomPlayerInfo) do
        if pi.normalUserInfo.playerId == data.changePlayerId then
            pi.normalUserInfo.level = data.level
            break
        end
    end
end

-----------------------------------------------------------------------
function P:syncChooseHeroCallBack(data)
    if data.status and data.status > 0 then
        return
    end
    local arrRoomPlayerInfo = sgGameState:getRoomManager()._roomInfo.arrRoomPlayerInfo
    for _, pi in pairs(arrRoomPlayerInfo) do
        if pi.normalUserInfo.playerId == data.changePlayerId then
            pi.normalUserInfo.heroInfo = data.heroInfo
            break
        end
    end
    self:updatePlayerNode()
    sgCommon:playExtremeSpeech(data.heroInfo.heroId, 2)
end
-----------------------------------------------------------------------
function P:buildItems()
    
    -- dump(roomInfo.arrRoomPlayerInfo[1].normalUserInfo.props)
    -- roomInfo.arrRoomPlayerInfo[1].normalUserInfo.props = nil

    if self.ib1 then
        self.ib1:removeFromParent()
        
    end

    if self.ib2 then
        self.ib2:removeFromParent()
    end

    local selectProp1 = sgGameState:getSelectProps(Constants.BATTLETYPE_PPVPP_FREE)[1]
    local selectProp2 = sgGameState:getSelectProps(Constants.BATTLETYPE_PPVPP_FREE)[2]

    local info1 = sgGameState:getFightPropInfoById(selectProp1)
    local info2 = sgGameState:getFightPropInfoById(selectProp2)

    if info1 and info1.propId > 0 then
        --sgCommon:createGoodsIcon()
        local size = self._ui.btnItem1:getContentSize()
        self.ib1 = cc.Sprite:create(sgCommon:getIconfromItemsPath(tpl_RoleSkill.pic(info1.propId)))
        self.ib1:setAnchorPoint(cc.p(0.5, 0.5))
        self.ib1:setScale(0.6, 0.6)
        self.ib1:setPosition(size.width * 0.5, size.height * 0.5)
        self._ui.btnItem1:addChild(self.ib1)
        self._ui.spBKItem1:setVisible(false)
    end

    if info2 and info2.propId > 0 then
        local size = self._ui.btnItem2:getContentSize()
        self.ib2 = cc.Sprite:create(sgCommon:getIconfromItemsPath(tpl_RoleSkill.pic(info2.propId)))
        self.ib2:setAnchorPoint(cc.p(0.5, 0.5))
        self.ib2:setScale(0.6, 0.6)
        self.ib2:setPosition(size.width * 0.5, size.height * 0.5)
        self._ui.btnItem2:addChild(self.ib2)
        self._ui.spBKItem2:setVisible(false)
    end

    if sgGameState._userState.guideIndex == 500 then
        local roomInfo = sgGameState:getRoomManager()._roomInfo
        local item_data =  ptl.FightProps:create()
        item_data.battleType = Constants.BATTLETYPE_PPVPP_FREE
        if info1 then
           item_data.prop1 = info1.propId
        end
        if info2 then
            item_data.prop2 = info2.propId
        end    
        roomInfo.arrRoomPlayerInfo[1].normalUserInfo.props = item_data
    end

end
-----------------------------------------------------------------------
function P:exitRoom(data)
    if sgLayerManager._curLayer.__cname == "VsLayer" then
        sgLayerManager._curLayer:onRelease()
    end

    local layer = sgLayerManager:getLayer("app.views.common.CommonDayDialog")
    if layer then
        layer:onRelease()
    end

    local csbRoleUI = self.playerObjects[data.quitPlayerId]
    if not csbRoleUI then
        return
    end

    csbRoleUI.spOwner:setVisible(false)
    local lockVal = 0
    self:setLockValue(lockVal)
    csbRoleUI.btnLock:setVisible(lockVal <= 0)
    csbRoleUI.btnUnlock:setVisible(lockVal > 0)
    csbRoleUI.aniReady:setVisible(false)
    csbRoleUI.aniReady:setVisible(false)
    csbRoleUI.boneNode:removeAllChildren()
    csbRoleUI.objVip:removeAllChildren()

    -- 自己
    local localPlayerId = sgGameState:getUserState().playerId
    csbRoleUI = self.playerObjects[localPlayerId]
    csbRoleUI.spReady:setVisible(true)
    csbRoleUI.aniReady:setVisible(true)
    csbRoleUI.aniReady:doAnimation("animation4")
    csbRoleUI.spMaster:setVisible(true)

    self:showStartFight(1)
    self:setStartFightGray(false)

    self._ui.btnInvite:setVisible(lockVal <= 0)
    self._ui.btnQuickInvite:setVisible(lockVal <= 0)



end

function P:refreshFriendChatRedDot()
    local unreadNum = ChatManager:getUnreadChatMsgs(ChatManager.CHAT_CHAT)
    self._ui.csbChat.ui.spChatNumBg:setVisible(tonumber(unreadNum)>0)
    if tonumber(unreadNum)>0 then
        local chatNum = self._ui.csbChat.ui.spChatNumBg:getChildByTag(1)
        if chatNum then
            local tempStr = unreadNum
            if unreadNum > 99 then
                tempStr = "99+" 
                --chatNum:setPosition(cc.p(21,26))
            else
                --chatNum:setPosition(cc.p(19,20))
            end
            chatNum:setString(tempStr)
        else
            self._ui.csbChat.ui.spChatNumBg:setVisible(false)
        end
    end
end

-- 快捷对聊按钮
function P:onFriend(sender, eventType)
    if 1 == eventType then  -- 开始
        if YVVoiceManager:isLogin() then
            self._chatVoiceInfo = requireEx("app.views.chat.ChatVoiceInfo"):create()
            self._chatVoiceInfo:setName("chatVoiceInfo")
            self:addChild(self._chatVoiceInfo)

            cc.SimpleAudioEngine:getInstance():pauseMusic()
            ChatManager:setVoiceType(ChatManager.CHAT_TEAM)
            YVVoiceManager:startRecord()
            --voiceTime = os.clock()
            self.voiceTime2 = 0 --做60s的限制
            if not self._updateId then
                self._updateId = cc.Director:getInstance():getScheduler():scheduleScriptFunc( handler(self, self.updateVoice), 0.1, false)
            end
        end
    elseif 3 == eventType then  -- 确定
        if self.voiceTime2>=0 and self.voiceTime2<60 then
            self:voiceEnd()
            self:stopUpdate()
        end
    elseif 4 == eventType then -- 取消
        if self._chatVoiceInfo then
            self._chatVoiceInfo:removeFromParent(true)
        end
        cc.SimpleAudioEngine:getInstance():resumeMusic()
    elseif 5 == eventType then -- 移动回按钮区域
        if self._chatVoiceInfo then
            self._chatVoiceInfo:setType(1)
        end
    elseif 6 == eventType then -- 移动出按钮区域
        if self._chatVoiceInfo then
            self._chatVoiceInfo:setType(2)
        end
    end
end

--录音正常结束
function P:voiceEnd()
    if self._chatVoiceInfo then
        self._chatVoiceInfo:removeFromParent(true)
    end
    cc.SimpleAudioEngine:getInstance():resumeMusic()
    if self.voiceTime2 == 0 then
        TipsLayer.showTips(_T("chat.voiceFail"))
        YVVoiceManager:stopRecord(true)
    else
        --self.voiceTime2 = os.clock() - self.voiceTime
        if self.voiceTime2 < ChatManager.MIN_VOICE_TIME then
            TipsLayer.showTips(_T("chat.voiceshort"))
            YVVoiceManager:stopRecord(true)
        else
            --LoadingLayer.isShowLoading(true)
            if ChatManager.CHAT_UNION == self._chatType then
                ChatManager:setTargetPlayerIds({self._talkTarget})
            end
            
            ChatManager:setVoiceTime(self.voiceTime2)
            YVVoiceManager:stopRecord()
        end
    end
end
 
function P:updateVoice(dt)
    if self._updateId and self.voiceTime2>=0 then
        self.voiceTime2 = self.voiceTime2 + dt
        if self.voiceTime2>=60 then
            self:voiceEnd()
            self:stopUpdate()
        end
    end
end

function P:stopUpdate()
    if self._updateId then
        cc.Director:getInstance():getScheduler():unscheduleScriptEntry(self._updateId)
        self._updateId = nil
        self.voiceTime2 = -1
    end
end


return P