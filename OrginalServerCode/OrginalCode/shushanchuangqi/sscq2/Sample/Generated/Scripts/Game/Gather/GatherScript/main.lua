__L_GatherOP_CanGather= {
}
__L_GatherOP_OnFinishGather = {
}
function LoadAllGather()
    LOG_INF('LUA_INFO: Loading all GatherXXXXX.lua scripts.')
    local GatherScripts = LsDir('Scripts/Game/Gather/GatherScript', "Gather*.lua")
    for k,v in ipairs(GatherScripts) do
        LOG_INF('LUA_INFO: Loading ' .. v)
        local file = v
        if string.len(file) == 0 then
            LOG_CRI('LUA_ERROR: ' .. v .. ' not exist.')
            return false
        end
        local s,e = string.find(file, "Gather[0-9]*.lua")
        local wGatherID = string.sub(file, s+6, e-4)
        dofile(file)
        __L_GatherOP_CanGather[tonumber(wGatherID)] = _G['CanGather'..wGatherID]
        __L_GatherOP_OnFinishGather[tonumber(wGatherID)] = _G['OnFinishGather'..wGatherID]

    end
    LOG_INF('LUA_INFO: Loading end.')
end

function CanGather(wGatherID)
    local trigger = __L_GatherOP_CanGather[wGatherID]
    if trigger == nil then
        return true
    end
    return trigger()
end
function OnFinishGather(wGatherID)
    local trigger = __L_GatherOP_OnFinishGather[wGatherID]
    if trigger == nil then
        return 
    end
    return trigger()
end
function HasCanGatherFunction(wGatherID)
    local trigger = __L_GatherOP_CanGather[wGatherID]
    return  trigger ~= nil 
end
function HasOnFinishGatherFunction(wGatherID)
    local trigger = __L_GatherOP_OnFinishGather[wGatherID]
    return  trigger ~= nil 
end
-- All operations
LoadAllGather()

