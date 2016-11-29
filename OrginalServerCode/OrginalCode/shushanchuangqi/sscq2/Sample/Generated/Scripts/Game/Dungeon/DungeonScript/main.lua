__L_DungeonOP_OnEnterLimit = {
}
__L_DungeonOP_OnInit = {
}
__L_DungeonOP_OnTimer = {
}
__L_DungeonOP_OnEnd = {
}
__L_DungeonOP_OnFinish = {
}
function LoadAllDungeon()
    LOG_INF('LUA_INFO: Loading all DungeonXXXXX.lua scripts.')
    local DungeonScripts = LsDir('Scripts/Game/Dungeon/DungeonScript', "Dungeon*.lua")
    for k,v in ipairs(DungeonScripts) do
        LOG_INF('LUA_INFO: Loading ' .. v)
        local file = v
        if string.len(file) == 0 then
            LOG_CRI('LUA_ERROR: ' .. v .. ' not exist.')
            return false
        end
        local s,e = string.find(file, "Dungeon[0-9]*.lua")
        local wDungeonID = string.sub(file, s+7, e-4)
        dofile(file)
        __L_DungeonOP_OnEnterLimit[tonumber(wDungeonID)] = _G['DungeonOnEnterLimit'..wDungeonID]
        __L_DungeonOP_OnInit[tonumber(wDungeonID)] = _G['DungeonOnInit'..wDungeonID]
        __L_DungeonOP_OnTimer[tonumber(wDungeonID)] = _G['DungeonOnTimer'..wDungeonID]
        __L_DungeonOP_OnEnd[tonumber(wDungeonID)] = _G['DungeonOnEnd'..wDungeonID]
        __L_DungeonOP_OnFinish[tonumber(wDungeonID)] = _G['DungeonOnFinish'..wDungeonID]

    end
    LOG_INF('LUA_INFO: Loading end.')
end

function DungeonOnEnterLimit(wDungeonID)
    local trigger = __L_DungeonOP_OnEnterLimit[wDungeonID]
    if trigger == nil then
        return true
    end
    return trigger()
end
function DungeonOnInit(wDungeonID,Dgn)
    local trigger =  __L_DungeonOP_OnInit[wDungeonID]
    if trigger == nil then
        return 
    end
    return trigger(Dgn)
end
function DungeonOnTimer(wDungeonID,Dgn,TimerId)
    local trigger = __L_DungeonOP_OnTimer[wDungeonID]
    if trigger == nil then
        return 
    end
    return trigger(Dgn,TimerId)
end
function DungeonOnEnd(wDungeonID,Dgn)
    local trigger = __L_DungeonOP_OnEnd[wDungeonID]
    if trigger == nil then
        return 
    end
    return trigger(Dgn)
end
function DungeonOnFinish(wDungeonID,Dgn)
     LOG_INF('LUA_INFO: Call OnFinish............... ' .. wDungeonID)
    local trigger = __L_DungeonOP_OnFinish[wDungeonID]
    if trigger == nil then
        return 
    end
    return trigger(Dgn)
end


function DungeonHasOnEnterLimitFunction(wDungeonID)
    local trigger = __L_DungeonOP_OnEnterLimit[wDungeonID]
    return  trigger ~= nil 
end
function DungeonHasOnInitFunction(wDungeonID)
    local trigger =  __L_DungeonOP_OnInit[wDungeonID]
    return  trigger ~= nil 
end
function DungeonHasOnTimerFunction(wDungeonID)
    local trigger = __L_DungeonOP_OnTimer[wDungeonID]
    return trigger ~= nil 
end
function DungeonHasOnEndFunction(wDungeonID)
    local trigger = __L_DungeonOP_OnEnd[wDungeonID]
    return  trigger ~= nil 
end
function DungeonHasOnFinishFunction(wDungeonID)
    local trigger = __L_DungeonOP_OnFinish[wDungeonID]
    return  trigger ~= nil 
end

-- All operations
LoadAllDungeon()

