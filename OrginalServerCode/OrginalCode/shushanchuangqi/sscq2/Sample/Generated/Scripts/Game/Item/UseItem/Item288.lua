
function OnUseItem288(wItemID, wCount, eBind, qwMercenID)
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
    local prob = {800,800,1600,1600,800,800,800,800,150,150,300,300,150,150,150,150,500,50,100,100,50,50,51,49}
    local items = {{8801,1},{8821,1},{8841,1},{8861,1},{8881,1},{8901,1},{8921,1},{8941,1},{8801,2},{8821,2},{8841,2},{8861,2},{8881,2},{8901,2},{8921,2},{8941,2},{8801,3},{8821,3},{8841,3},{8861,3},{8881,3},{8901,3},{8921,3},{8941,3}}
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

