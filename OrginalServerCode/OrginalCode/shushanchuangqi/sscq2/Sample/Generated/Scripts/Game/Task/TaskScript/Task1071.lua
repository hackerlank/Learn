function DoCaseForDgn1071(wDgnType)
    LOG_WRN('DoCaseForDgn1071' .. tostring(wDgnType) )
    local user = GameScript:GetUser()
    if(wDgnType ~= 8) then
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
	pDgn:AddNpcByIndex(2)
end
