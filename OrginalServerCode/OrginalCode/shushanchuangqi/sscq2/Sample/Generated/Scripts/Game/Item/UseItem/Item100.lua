
function OnUseItem100(wItemID, wCount, eBind, qwMercenID)
    local user = GameScript:GetUser()
    LOG_WRN('wItemID: ' .. wItemID .. ' wCount: ' .. wCount .. ' eBind: ' .. eBind .. ' qwMercenID: ' .. tostring(qwMercenID))
    if nil == user then
        return 0
    end 
    local pack = user:GetPack();
    if pack:GetEmptyCount() < 20 * wCount then --背包空格判断
        user:SendMsg(106)
		return 0
    end
    local items = {{5,10060000},{2,790000},{9,80000},{323,1},{360,10},{361,10},{362,10},{700,1},{800,1},{900,10},{901,10},{902,10},{903,10}}    --背包道具
    for k = 1, wCount do
        for i = 1 , 13 do
        local item = items[i];
        if pack:AddItemWithID(item[1],item[2],eBind,0,2) == false then
            user:SendMsg(106)
            return k - 1;
        end
	 end
    end
    return wCount
end

