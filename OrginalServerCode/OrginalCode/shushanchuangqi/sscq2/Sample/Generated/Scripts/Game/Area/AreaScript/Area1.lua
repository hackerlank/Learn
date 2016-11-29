function InArea1()
    local user = GameScript:GetUser()
    LOG_WRN('Do ' .. tostring(user:GetUserID()) .. 'OnArea1' )
	local pPlayer = SharedToPtr(user:GetPlayer())
    if (nil == pPlayer) then
        LOG_WRN('NO Player')
        return 
    end
    local pDgn = SharedToPtr(pPlayer:GetDgn())
    if (pDgn == nil) then
        LOG_WRN('NO Dgn')
        return
    end
	pDgn:DestroyBlockByIndex(1)
end


--local user = GameScript:GetUser() 获得user
--local pPlayer = SharedToPtr(user:GetPlayer()) 获得pPlayer
--local pDgn = SharedToPtr(pPlayer:GetDgn()) 获得pDgn
--pPlayer:FitherToMonster(wMonsterGroup)//战斗
--pDgn:CreateMonster(wMonsterGroup,fX,fY)//创建怪物
--pDgn:DestroyMonster(wMonsterGroup)//清除怪物
--pDgn:CreateGather(wGatherId,fX,fY)//创建采集物
--pDgn:DestroyGather(MonsterGroup)//清楚
--pDgn:TransPlayer(Player,wMap,fX,fy) ://传送，副本里的地图
--pDgn:ClearMist(wMist)//清除迷雾
--pDgn:AddMist(wMist)//添加迷雾
--User:NoticeStory(wStroyID)//触发剧情
--pPlayer:ElasticFrame(wType)//弹窗
--pDgn:SetTimer(wTimerId,dwTimerIntral)//设置定时器，定时器id，时间
--pDgn:EndTimer(wTimerId)//立刻结束定时器
--pDgn:SetParam(wParamId,dwParamVal)//存储临时参数
--pDgn:GetParam(wParamId)//获取临时参数
--pDgn:CreateBlockByIndex(wIndex)//创建路障
--pDgn:DestroyBlockByIndex(wIndex)//删除路障
