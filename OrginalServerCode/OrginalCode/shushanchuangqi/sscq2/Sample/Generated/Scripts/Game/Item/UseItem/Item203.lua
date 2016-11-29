
function OnUseItem203(wItemID, wCount, eBind, qwMercenID)
    local user = GameScript:GetUser()
    local other = GameScript:GetOther()
    local pPlayer = SharedToPtr(user:GetPlayer())
    if(nil == pPlayer or wCount ~= 1) then
        return 0
    end 
    local bResult = pPlayer:UserYaMenHoly();
    if(bResult ~= true) then
       return 0
    end
    return wCount
end

