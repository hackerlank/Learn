
function OnUseItem190(wItemID, wCount, eBind, qwMercenID)
    local user = GameScript:GetUser()
    LOG_WRN('wItemID: ' .. wItemID .. ' wCount: ' .. wCount .. ' eBind: ' .. eBind .. ' qwMercenID: ' .. tostring(qwMercenID))
    if nil == user then
        return 0
    end 
    local player = user:GetPlayer()
    if nil == player then
        return 0
    end
    local pack = user:GetPack()
    if (pack == nil) then
        return 0
    end
    local sitems = {}
    local prob = {1800,400,700,700,700,700,700,700,900,900,900,900}
    local items = {{1132,2},{291,1},{290,1},{292,1},{293,1},{10912,1},{201,1},{204,1},{56,60},{56,80},{56,90},{56,100}}
    local len = #items
    if len  == 0 then
        return 0
    end
    local emptypack = pack:GetEmptyCount();
    local needpack = 8
    if wCount < needpack then
        needpack = wCount
    end
    if needpack > emptypack then
        user:SendMsg(106)
        return 0
    end
    --保护物品
    local protect = 1;
    --保护次数
    local protectnum = 7;
    if protect > len or protect == 0 then
        return 0
    end
    if protectnum < 2 then
        return 0
    end
    for k = 1, wCount do
        local p = 1;
        --保护概率
        local nownum = player:GetItemUserCount(190);
        if nownum == 0 or nownum >= protectnum then
            p = protect
            player:SetItemUserCount(190,1)
        else
            local tep = math.random(0, 10000)
            for j = 1,#prob do
                if tep <= prob[j] then
                    p = j
                    break;
                else
                    tep = tep - prob[j]
                end 
            end			
            if p == protect then
                player:SetItemUserCount(190,1)
            else
                player:SetItemUserCount(190,nownum + 1)
            end
        end
        local item = items[p]
        local sitem = {item = 0, num = 0 }
        sitem.item = item[1]
        sitem.num = item[2]
        local bfind = false
        for  j = 1, #sitems do
            if sitems[j].item == sitem.item then
                sitems[j].num = sitems[j].num + sitem.num
                bfind = true
                break
            end
        end
        if bfind == false then
            table.insert(sitems,sitem)
        end
    end
    for  j = 1, #sitems do
        pack:AddItemWithID(tonumber(sitems[j].item),tonumber(sitems[j].num),eBind,0,2) 
    end
    return wCount
end

