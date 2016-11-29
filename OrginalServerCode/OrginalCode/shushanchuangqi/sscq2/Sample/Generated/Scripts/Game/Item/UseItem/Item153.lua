
function OnUseItem153(wItemID, wCount, byBind, qwMercenID)
    local user,player,other,oplayer = TouchMe() -- XXX: TouchMe返回4个值
    if user == nil or player == nil then
        return 0
    end
        wUsed = 0
    for i = 1 , wCount do 
        ret = player:AddBuff(35)
        if ret ~= 0 then
            return wUsed
        else
            wUsed = wUsed + 1
        end
    end
    return wUsed
end
