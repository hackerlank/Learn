
function OnUseItem185(wItemID, wCount, eBind, qwMercenID)
    local user = GameScript:GetUser()
    LOG_WRN('wItemID: ' .. wItemID .. ' wCount: ' .. wCount .. ' eBind: ' .. eBind .. ' qwMercenID: ' .. tostring(qwMercenID))
    if nil == user then
        return 0
    end 
    local items = { {56, 6}, }
    local pack = user:GetPack();
    --[[
    if pack:GetEmptyCount() < #items * wCount then --±³°ü¿Õ¸ñÅÐ¶Ï
        user:SendMsg(106)
		return 0
    end
    --]]
    for k = 1, #items do
        if pack:AddItemWithID(items[k][1], items[k][2]*wCount, eBind,0,2) == false then
            user:SendMsg(106)
            return 0;
        end
    end
    user:AddTotalRechargeByLua(wItemID, 3000*wCount);
    return wCount
end

