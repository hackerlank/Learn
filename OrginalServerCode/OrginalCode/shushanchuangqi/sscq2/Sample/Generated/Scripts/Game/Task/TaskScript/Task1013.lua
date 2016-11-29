
function DoCaseForDgn1013(wDgnType)
    LOG_WRN('DoCaseForDgn1013' .. tostring(wDgnType) )
    local user = GameScript:GetUser()
    if(wDgnType ~= 12) then
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
    pDgn:CreateMonsterIfNotExist(42,7,40)
	pDgn:DestroyNpc(1065)
end



