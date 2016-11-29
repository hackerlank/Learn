
function OnUseItem277(wItemID, wCount, eBind, qwMercenID)
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
    local prob = {625,1250,1875,2500,3125,3750,4375,5000,5625,6250,6875,7500,8125,8750,9375,10000}
    local items = {{201,1},{201,2},{204,1},{204,2},{321,1},{321,2},{206,1},{206,2},{312,1},{312,2},{312,3},{2,1000},{2,1500},{2,2000},{9,1000},{9,1500},{9,2000},{3,10},{3,20},{1703,5},{1707,5}}
    local len = #items;
    if len  == 0 then
        return 0
	end
    local emptypack = pack:GetEmptyCount();
    local needpack = 7
    if wCount < needpack then
        needpack = wCount
    end
    if needpack > emptypack then
        user:SendMsg(106)
        return 0
    end
    for k = 1, wCount do
        local p = math.random(1, len)      
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

