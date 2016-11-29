function DoCaseForDgn1045(wDgnType)
    LOG_WRN('DoCaseForDgn1045' .. tostring(wDgnType) )
    local user = GameScript:GetUser()
    if(wDgnType ~= 4) then
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
    pDgn:CreateMonsterIfNotExist(24,27,31)
	pDgn:DestroyNpc(1051)
end
