
function OnLogin(pUser)
    -- TODO
    LOG_INF('User (' .. tostring(pUser:GetUserID()) .. ') [' .. pUser:GetUserName() .. '] LOGIN')
    LOG_INF('User (' .. tostring(pUser:GetUserID()) .. ') [' .. pUser:GetUserName() .. '] LOGIN2')
    LOG_INF('User (' .. tostring(pUser:GetUserID()) .. ') [' .. pUser:GetUserName() .. '] LOGIN3')
    LOG_INF('User (' .. tostring(pUser:GetUserID()) .. ') [' .. pUser:GetUserName() .. '] LOGIN4')
end

function OnLogout(pUser)
    -- TODO
    LOG_INF('User (' .. tostring(pUser:GetUserID()) .. ') [' .. pUser:GetUserName() .. '] LOGOUT')
end

function OnUserEnter(pUser)
    -- TODO
    LOG_INF('User (' .. tostring(pUser:GetUserID()) .. ') [' .. pUser:GetUserName() .. '] ENTER')
end

function OnEnterJump(pUser)
    -- TODO
    LOG_INF('User (' .. tostring(pUser:GetUserID()) .. ') [' .. pUser:GetUserName() .. '] ENTERJUMP')
end

function OnLevelUp(pPlayer)
    -- TODO
    local pUser = SharedToPtr(pPlayer:GetUserPtr())
    LOG_INF('User (' .. tostring(pUser:GetUserID()) .. ') [' .. pUser:GetUserName() .. '] LEVELUP')
end

