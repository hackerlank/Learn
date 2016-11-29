
function DoCaseForDgn1006(wDgnType)
    LOG_WRN('DoCaseForDgn1006' .. tostring(wDgnType) )
    local user = GameScript:GetUser()
    if(wDgnType ~= 1) then
        return 
    end
    local pPlayer = SharedToPtr(user:GetPlayer())
    if (nil == pPlayer) then
        LOG_WRN('NO Player')
        return 
    end
    local pDgn = SharedToPtr(pPlayer:GetDgn())
    if (pDgn == nil) then
        LOG_WRN('NO Dgn')
        return
    end
    pDgn:AddGatherByIndex(2)
end



