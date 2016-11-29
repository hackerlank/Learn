__L_AreaOP_InArea = {
}
function LoadAllArea()
    LOG_INF('LUA_INFO: Loading all AreaXXXXX.lua scripts.')
    local AreaScripts = LsDir('Scripts/Game/Area/AreaScript', "Area*.lua")
    for k,v in ipairs(AreaScripts) do
        LOG_INF('LUA_INFO: Loading ' .. v)
        local file = v
        if string.len(file) == 0 then
            LOG_CRI('LUA_ERROR: ' .. v .. ' not exist.')
            return false
        end
        local s,e = string.find(file, "Area[0-9]*.lua")
        local wAreaID = string.sub(file, s+4, e-4)
        dofile(file)
        __L_AreaOP_InArea[tonumber(wAreaID)] = _G['InArea'..wAreaID]

    end
    LOG_INF('LUA_INFO: Loading end.')
end

function InArea(wAreaID)
    local trigger = __L_AreaOP_InArea[wAreaID]
    if trigger == nil then
        return 
    end
    return trigger()
end
function HasInAreaFunction(wAreaID)
    local trigger = __L_AreaOP_InArea[wAreaID]
    return  trigger ~= nil 
end
-- All operations
LoadAllArea()

