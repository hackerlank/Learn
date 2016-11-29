function DoCaseForDgn1011(wDgnType)
    LOG_WRN('DoCaseForDgn1001' .. tostring(wDgnType) )
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
    pDgn:CreateMonsterIfNotExist(14,20,22)
end



