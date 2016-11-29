
-- global defines
D = debug

function LsDir(directory, filter)
    local i, t, popen = 0, {}, io.popen
    if filter == nil then
        filter = ''
    end
    local pipe = popen('ls -a '.. directory .. '/' .. filter)
    if pipe == nil then
        return t
    end
    for filename in pipe:lines() do
        i = i + 1
        t[i] = filename;
    end
    io.close(pipe)
    return t
end

function SharedToPtr(shared)
    return shared
end

function WeakToPtr(weak)
    return nil
end

-- RETURN: user,player,other,oplayer
function TouchMe()
    local user = GameScript:GetUser()
    local other = GameScript:GetOther()
    local oplayer = nil
    if other ~= nil then
        oplayer = SharedToPtr(other:GetPlayer())
    end
    if user == nil then
        return nil,nil,other,oplayer
    end
    local player = SharedToPtr(user:GetPlayer())
    if player == nil then
        return user,nil,other,oplayer
    end
    return user,player,other,oplayer
end

dofile('Scripts/log.lua')

