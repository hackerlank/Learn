
function DoCaseForDgn1036(wDgnType)
    LOG_WRN('DoCaseForDgn1036' .. tostring(wDgnType) )
    local user = GameScript:GetUser()
    if(wDgnType ~= 3) then
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
    pDgn:CreateMonsterIfNotExist(35,18,34)
	pDgn:DestroyNpc(1050)
end
