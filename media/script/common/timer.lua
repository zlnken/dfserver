------------------------------------------------------------------------
-- @brief 事件触发器
------------------------------------------------------------------------
local P = class("Timer")
P.TimerMgr = {}
P.Timer_Start = 1
P.Timer_Pause = 2
P.Timer_Stop = 3
------------------------------------------------------------------------
-- @brief 构造函数
function P:ctor(name)
    self._checkTime = 0
    self._callfunc = nil
    self._isLoop = nil
    self._name = name or ""
    self._state = P.Timer_Stop
end
------------------------------------------------------------------------
-- @brief 获取名字
function P:getName()
    return self._name
end
------------------------------------------------------------------------
-- @brief 开始计时
-- @param[seconds] 秒
-- @param[func] 回调函数
function P:start(seconds, func, isLoop)
    if self._state ~= P.Timer_Stop then
        return
    end
    self._checkTime = seconds
    self._updateTime = 0.0
    self._isLoop = isLoop
    self._state = P.Timer_Start
    self._callfunc = func
end
------------------------------------------------------------------------
-- @brief 停止计时
function P:stop()
    self._isLoop = nil
    self._state = P.Timer_Stop
    self._chekTime = 0
    self._callfunc = nil
end
------------------------------------------------------------------------
-- @brief 停止计时
function P:pause()
     self._state = P.Timer_Pause
end
------------------------------------------------------------------------
-- @brief 是否开始
function P:getIsStart()
    return self._state == P.Timer_Start
end
------------------------------------------------------------------------
-- @brief 更新
function P:update()
    if P.Timer_Pause == self._state or P.Timer_Stop == self._state then
        return
    end

    if not self._callfunc then
        return
    end
    if self._updateTime >= self._checkTime then
        if self._isLoop then
            self._updateTime = 0.0
        else
            self._state = P.Timer_Stop
        end
        
        self._callfunc()
    else
        self._updateTime = self._updateTime + 1
    end
end
------------------------------------------------------------------------
-- @brief 创建一个触发器
-- @param[name] 触发器名字
function P.screate(name)
    local timer = P.sfind(name)
    if timer then
        return timer
    end
    timer = P.new(name)
    P.TimerMgr[name] = timer
    return timer
end
------------------------------------------------------------------------
-- @brief 查找一个触发器
-- @param[name] 触发器名字
function P.sfind(name)
    return P.TimerMgr[name]
end
------------------------------------------------------------------------
-- @brief 移除一个触发器
-- @param[name] 触发器名字
function P.sremove(name)
    P.TimerMgr[name] = nil
end
------------------------------------------------------------------------
-- @brief 清空触发器管理器
function P.sclear()
    P.TimerMgr = {}
end
------------------------------------------------------------------------
-- @brief 更新时间
function P.run()
    local removes = {}
    for name, timer in pairs(P.TimerMgr) do
        if timer._state == P.Timer_Stop then
            table.insert(removes, name)
        end
        timer:update()
    end
    for _, name in ipairs(removes) do
        P.TimerMgr[name] = nil
    end
end

return P
