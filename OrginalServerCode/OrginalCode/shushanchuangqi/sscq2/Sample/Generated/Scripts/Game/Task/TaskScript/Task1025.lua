
function DoCaseForDgn1025(wDgnType)
    LOG_WRN('DoCaseForDgn1025' .. tostring(wDgnType) )
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
    pDgn:CreateMonsterIfNotExist(16,29,95)
end
