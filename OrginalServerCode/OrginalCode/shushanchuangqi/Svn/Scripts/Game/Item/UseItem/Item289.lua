
function OnUseItem289(wItemID, wCount, eBind, qwMercenID)
    local user = GameScript:GetUser()
    LOG_WRN('wItemID: ' .. wItemID .. ' wCount: ' .. wCount .. ' eBind: ' .. eBind .. ' qwMercenID: ' .. tostring(qwMercenID))
    if nil == user then
        return 0
    end 
    local pack = user:GetPack();
    if (pack == nil) then
        return 0
    end
    local sitems = {}
    local prob = {1250,1250,1250,1250,1250,1250,1250,1250}
    local items = {{8805,1},{8825,1},{8845,1},{8865,1},{8885,1},{8905,1},{8925,1},{8945,1}}
    local len = #items;
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
    for k = 1, wCount do
        local tep = math.random(0, 10000)
        local p = 1;
        for j = 1,#prob do
            if tep <= prob[j] then
                p = j
                break;
            else
                tep = tep - prob[j]
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

