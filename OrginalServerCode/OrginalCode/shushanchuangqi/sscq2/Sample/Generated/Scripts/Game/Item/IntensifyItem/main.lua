IntensifyTable = {
    "IntensifyTrump.lua"
}
function LoadAllIntensify()
    LOG_INF('LUA_INFO: Loading all IntensifyXXX.lua scripts.')
    local ItemScripts = LsDir('Scripts/Game/Item/IntensifyItem', "Intensify*.lua")
    for i=1,#IntensifyTable do
        local file = IntensifyTable[i]
        LOG_INF('LUA_INFO: Loading ' .. IntensifyTable[i])
        --dofile(file)
    end
    LOG_INF('LUA_INFO: Loading end.')
    return true
end

-- All operations
LoadAllIntensify()
