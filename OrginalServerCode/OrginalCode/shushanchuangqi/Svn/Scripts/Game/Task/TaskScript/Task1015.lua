
function DoCaseForDgn1015(wDgnType)
    LOG_WRN('DoCaseForDgn1015' .. tostring(wDgnType) )
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
    pDgn:CreateMonsterIfNotExist(43,14,66)
	pDgn:DestroyNpc(1066)
end
