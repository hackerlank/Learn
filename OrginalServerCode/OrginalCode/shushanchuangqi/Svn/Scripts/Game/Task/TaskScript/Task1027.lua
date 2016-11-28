
function DoCaseForDgn1027(wDgnType)
    LOG_WRN('DoCaseForDgn1027' .. tostring(wDgnType) )
    local user = GameScript:GetUser()
    if(wDgnType ~= 2) then
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
    pDgn:CreateMonsterIfNotExist(17,35,68)
	pDgn:DestroyNpc(1080)
end
