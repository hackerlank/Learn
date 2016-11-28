function DoCaseForDgn1047(wDgnType)
    LOG_WRN('DoCaseForDgn1047' .. tostring(wDgnType) )
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
	pDgn:DestroyNpc(1073)
	pDgn:AddNpcByIndex(3)
end
