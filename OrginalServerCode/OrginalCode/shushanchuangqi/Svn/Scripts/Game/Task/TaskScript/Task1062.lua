function DoCaseForDgn1062(wDgnType)
    LOG_WRN('DoCaseForDgn1062' .. tostring(wDgnType) )
    local user = GameScript:GetUser()
    if(wDgnType ~= 5) then
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
    pDgn:CreateMonsterIfNotExist(45,31,81)
	pDgn:DestroyNpc(1062)
end