
-- XXX: 如果你的脚本在重新加载后也需要被加载请使用dofile而不是require

function GameInit(_type)
    dofile("Scripts/lib.lua")

    LOG_INF('LUA_INFO: GameInit(' .. tostring(_type) .. ')')
    if bit ~= nil then
        if bit.band(_type, SCRIPT_TYPE_ITEMUSE) then
            dofile("Scripts/Game/Item/main.lua")
        else
            LOG_CIR("Scripts/Game/Item/main.lua not binded.")
        end

        if bit.band(_type, SCRIPT_TYPE_ACT) then
            dofile("Scripts/Game/Act/main.lua")
        end

        if bit.band(_type, SCRIPT_TYPE_SYS) then
            dofile("Scripts/Game/Sys/main.lua")
        end
        if bit.band(_type, SCRIPT_TYPE_TASK) then
            dofile("Scripts/Game/Task/main.lua")
        end
        if bit.band(_type, SCRIPT_TYPE_NPC) then
            dofile("Scripts/Game/Npc/main.lua")
        end
        if bit.band(_type, SCRIPT_TYPE_DGN) then
            dofile("Scripts/Game/Dungeon/main.lua")
        end
        if bit.band(_type, SCRIPT_TYPE_GATHER) then
            dofile("Scripts/Game/Gather/main.lua")
        end
        if bit.band(_type, SCRIPT_TYPE_AREA) then
            dofile("Scripts/Game/Area/main.lua")
        end

    else
        LOG_CRI('ERROR: need lib bit')
        return false
    end
    LOG_INF('LUA_INFO: All scripts loaded OK.')
    collectgarbage("setpause",100)
    collectgarbage("setstepmul",5000)
    return true
end

function CenterInit(_type)
    return false
end

function Init(server, _type)
    if server == ENUMS.eHostGame then
        return GameInit(_type)
    end
    if server == ENUMS.eHostCenter then
        return CenterInit(_type)
    end
    return false
end

print('Loading Lua...')
