function CanGather1()
    local user = GameScript:GetUser()
    LOG_WRN('Check: ' .. tostring(user:GetUserID()) .. 'CanGather1')
    return 0
end

function OnFinishGather1()
    local user = GameScript:GetUser()
    LOG_WRN('Do ' .. tostring(user:GetUserID()) .. 'OnFinishGather1' )
end


