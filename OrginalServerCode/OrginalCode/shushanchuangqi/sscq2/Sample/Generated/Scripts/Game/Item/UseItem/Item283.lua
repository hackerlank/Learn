
function OnUseItem283(wItemID, wCount, eBind, qwMercenID)
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
    local items = {{10901,1},{10901,2},{10901,3},{10905,1},{10905,2},{10905,3},{10909,1},{10909,2},{10909,3}}
    local len = #items;
    if len  == 0 then
        return 0
	end
    local emptypack = pack:GetEmptyCount();
    local needpack = 3
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

