__L_TaskOP_CanFinishTask = {
}
__L_TaskOP_OnAcceptTask = {
}
__L_TaskOP_OnGiveUpTask = {
}
__L_TaskOP_OnFinishTask = {
}
__L_TaskOP_CanAcceptTask = {
}
__L_TaskOP_DoCaseForDgn = {
}
function LoadAllTask()
    LOG_INF('LUA_INFO: Loading all TaskXXXXX.lua scripts.')
    local TaskScripts = LsDir('Scripts/Game/Task/TaskScript', "Task*.lua")
    for k,v in ipairs(TaskScripts) do
        LOG_INF('LUA_INFO: Loading ' .. v)
        local file = v
        if string.len(file) == 0 then
            LOG_CRI('LUA_ERROR: ' .. v .. ' not exist.')
            return false
        end
        local s,e = string.find(file, "Task[0-9]*.lua")
        local wTaskID = string.sub(file, s+4, e-4)
        dofile(file)
        __L_TaskOP_CanFinishTask[tonumber(wTaskID)] = _G['CanFinishTask'..wTaskID]
        __L_TaskOP_OnGiveUpTask[tonumber(wTaskID)] = _G['OnGiveUpTask'..wTaskID]
        __L_TaskOP_OnAcceptTask[tonumber(wTaskID)] = _G['OnAcceptTask'..wTaskID]
        __L_TaskOP_OnFinishTask[tonumber(wTaskID)] = _G['OnFinishTask'..wTaskID]
        __L_TaskOP_CanAcceptTask[tonumber(wTaskID)] = _G['CanAcceptTask'..wTaskID]
        __L_TaskOP_DoCaseForDgn[tonumber(wTaskID)] = _G['DoCaseForDgn'..wTaskID]


    end
    LOG_INF('LUA_INFO: Loading end.')
end

function CanFinishTask(wTaskID)
    local trigger = __L_TaskOP_CanFinishTask[wTaskID]
    if trigger == nil then
        return true
    end
    return trigger()
end
function OnGiveUpTask(wTaskID)
    local trigger =  __L_TaskOP_OnGiveUpTask[wTaskID]
    if trigger == nil then
        return 
    end
    return trigger()
end
function OnAcceptTask(wTaskID)
    local trigger = __L_TaskOP_OnAcceptTask[wTaskID]
    if trigger == nil then
        return 
    end
    return trigger()
end
function OnFinishTask(wTaskID)
    local trigger = __L_TaskOP_OnFinishTask[wTaskID]
    if trigger == nil then
        return 
    end
    return trigger()
end
function CanAcceptTask(wTaskID)
     LOG_INF('LUA_INFO: Call CanAcceptTask............... ' .. wTaskID)
    local trigger = __L_TaskOP_CanAcceptTask[wTaskID]
    if trigger == nil then
        return 
    end
    return trigger()
end
function DoCaseForDgn(wTaskID,wDgnID)
     LOG_INF('LUA_INFO: Call DoCaseForDgn............... ' .. wTaskID)
    local trigger = __L_TaskOP_DoCaseForDgn[wTaskID]
    if trigger == nil then
        return 
    end
    LOG_INF('LUA_INFO: Call DoCaseForDgn............... ' .. wTaskID..':'..wDgnID)
    return trigger(wDgnID)
end


function HasCanFinishTaskFunction(wTaskID)
    local trigger = __L_TaskOP_CanFinishTask[wTaskID]
    return  trigger ~= nil 
end
function HasOnGiveUpTaskFunction(wTaskID)
    local trigger =  __L_TaskOP_OnGiveUpTask[wTaskID]
    return  trigger ~= nil 
end
function HasOnAcceptTaskFunction(wTaskID)
    local trigger = __L_TaskOP_OnAcceptTask[wTaskID]
    return trigger ~= nil 
end
function HasOnFinishTaskFunction(wTaskID)
    local trigger = __L_TaskOP_OnFinishTask[wTaskID]
    return  trigger ~= nil 
end
function HasCanAcceptTaskFunction(wTaskID)
    local trigger = __L_TaskOP_CanAcceptTask[wTaskID]
    return  trigger ~= nil 
end
function HasDoCaseForDgnFunction(wTaskID)
    local trigger = __L_TaskOP_DoCaseForDgn[wTaskID]
    return  trigger ~= nil 
end

-- All operations
LoadAllTask()

