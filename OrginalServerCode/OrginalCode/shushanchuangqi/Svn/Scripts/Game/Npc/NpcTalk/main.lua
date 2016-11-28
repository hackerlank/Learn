__L_NPC_Talk = {
}
function LoadAllNpc()
    LOG_INF('LUA_INFO: Loading all NpcXXXXX.lua scripts.')
    local NpcScripts = LsDir('Scripts/Game/Npc/NpcTalk', "Npc*.lua")
    for k,v in ipairs(NpcScripts) do
        LOG_INF('LUA_INFO: Loading ' .. v)
        local file = v
        if string.len(file) == 0 then
            LOG_CRI('LUA_ERROR: ' .. v .. ' not exist.')
            return false
        end
        local s,e = string.find(file, "Npc[0-9]*.lua")
        local wNpcID = string.sub(file, s+3, e-4)
        dofile(file)
        __L_NPC_Talk[tonumber(wNpcID)] = _G["Npc"..tonumber(wNpcID)]
    end
    LOG_INF('LUA_INFO: Loading end.')
end

function NpcTalk(wNpcTalkID,strFunName)
    LOG_INF('LUA_INFO: NpcTalk ' .. wNpcTalkID..":"..strFunName)
    local NpcTable = __L_NPC_Talk[tonumber(wNpcTalkID)]
    if NpcTable == nil then
        LOG_CRI('Table is nil: '..wNpcTalkID)
        return ""
    end
    local NpcFun =  NpcTable[strFunName];
    if NpcFun == nil then
        LOG_CRI('Fun is nil :'..wNpcTalkID..'fun is'..strFunName)
        return ""
    end
    local strReturn = NpcFun();
    LOG_INF('return str is'..strReturn)
    return strReturn
end
-- All operations
LoadAllNpc()

