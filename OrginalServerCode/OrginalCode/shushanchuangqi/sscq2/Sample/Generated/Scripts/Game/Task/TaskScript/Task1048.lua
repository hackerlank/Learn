function DoCaseForDgn1048(wDgnType)
    LOG_WRN('DoCaseForDgn1048' .. tostring(wDgnType) )
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
    pDgn:CreateMonsterIfNotExist(25,35,12)
	pDgn:DestroyNpc(1009)
end
