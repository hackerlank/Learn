
function OnUseItem267(wItemID, wCount, eBind, qwMercenID)
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
    local prob = {385,769,1154,1538,1923,2308,2692,3077,3462,3846,4231,4615,5000,5385,5769,6154,6538,6923,7308,7692,8077,8462,8846,9231,9615,10000}
    local items = {{201,1},{201,2},{201,3},{204,1},{204,2},{204,3},{321,1},{321,2},{321,3},{206,1},{206,2},{206,3},{312,1},{312,2},{312,3},{2,2000},{2,2500},{2,3000},{9,2000},{9,2500},{9,3000},{202,1},{202,2},{205,1},{205,2},{322,1},{322,2},{207,1},{207,2},{313,1},{313,2},{1704,1},{1704,2},{1708,1},{1708,2}}
    local len = #items;
    if len  == 0 then
        return 0
	end
    local emptypack = pack:GetEmptyCount();
    local needpack = 12
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

