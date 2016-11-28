
__L_ItemUseID2OP = {
    -- ID = OnUseItem, 
}

function LoadAllItemUse()
    LOG_INF('LUA_INFO: Loading all ItemXXXXX.lua scripts.')
    local ItemScripts = LsDir('Scripts/Game/Item/UseItem', "Item*.lua")
    for k,v in ipairs(ItemScripts) do
        LOG_INF('LUA_INFO: Loading ' .. v)
        local file = v
        if string.len(file) == 0 then
            LOG_CRI('LUA_ERROR: ' .. v .. ' not exist.')
            return false
        end
        local s,e = string.find(file, "Item[0-9]*.lua")
        local wItemID = string.sub(file, s+4, e-4)
        dofile(file)

        __L_ItemUseID2OP[tonumber(wItemID)] = _G['OnUseItem'..wItemID]
    end
    LOG_INF('LUA_INFO: Loading end.')
end

function ItemUseNormal(wItemID, wCount, byBind, qwMercenID)
    local trigger = __L_ItemUseID2OP[wItemID]
    if trigger == nil then
        return 0
    end
    return trigger(wItemID, wCount, byBind, qwMercenID)
end

function HasUseFunction(wItemID)
    if __L_ItemUseID2OP[wItemID] ~= nil then
        return true
    end
    --LOG_WRN("LUA_WARNING: " .. wItemID .. " not inited.")
    return false 
end

--九疑鼎火种激活
function OnUseItemTripod(wItemID, wCount, eBind, qwMercenID)
    if wItemID <= 10700 and wItemID > 10900 then
        return 0
    end
    local user = GameScript:GetUser()
    LOG_WRN('wItemID: ' .. wItemID .. ' wCount: ' .. wCount .. ' eBind: ' .. eBind .. ' qwMercenID: ' .. tostring(qwMercenID))
    if nil == user then
        return 0
    end
    for k = 1, wCount do
        user:ActiveTripodFire(wItemID-10700)
    end
    return wCount
end

-- All operations
LoadAllItemUse()

