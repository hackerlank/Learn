function OnFinishTask3059()
    LOG_WRN('OnFinishTask3059' .. tostring(wDgnType) )
    local user = GameScript:GetUser()
    if(nil == user) then
        return 
    end
    user:DelIconByLua(115)
end
