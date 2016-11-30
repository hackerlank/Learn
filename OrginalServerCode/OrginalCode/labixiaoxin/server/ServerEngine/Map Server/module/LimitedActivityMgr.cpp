#include "LimitedActivityMgr.h"
#include "..\..\GameBase\res\GameConfig.h"
#include "..\Map.h"

void LimitedActivityMgr::init( MsgDBLimitedActivityList * list )
{
	m_mapCurrentLA.clear();//清除老数据
	ACE_UINT32 now = GameUtils::get_utc();//获取当前时间
	for (int i=0;i<list->m_unCount;i++)
	{
		if (list->m_LAList[i].unCloseTime > now)//限时活动还未过期
			m_mapCurrentLA[list->m_LAList[i].unLAID] = list->m_LAList[i];
	}
	Refresh();//更新现有的

	m_isHaveNew = false;
}

void LimitedActivityMgr::Refresh()
{
	RefreshOld();//删除老的
	RefreshNew();//添加新的
}

void LimitedActivityMgr::RefreshNew()
{
	ACE_UINT32 now = GameUtils::get_utc();//获取当前时间
	const std::map<ACE_UINT32, LimitedActivityConfig> &refLAConfig = GAME_CONFIG_INSTANCE::instance()->m_olimitedActivityConfig;
	std::map<ACE_UINT32, LimitedActivityConfig>::const_iterator c_it = refLAConfig.begin();//当前活动任务列表
	while(c_it != refLAConfig.end())
	{
		if(c_it->second.unStartTime <= now && c_it->second.unCloseTime > now)//任务还没结束 找到了
		{
			if (m_mapCurrentLA[c_it->first].unLAID == 0)
			{
				//m_mapCurrentLA[c_it->first].unCharacterID = m_map->m_unID;
				m_mapCurrentLA[c_it->first].unLAID = c_it->second.unID;
				m_mapCurrentLA[c_it->first].unCloseTime = c_it->second.unCloseTime;
				m_mapCurrentLA[c_it->first].unLinkType = c_it->second.unRelatedType;
				m_mapCurrentLA[c_it->first].unProgress = 0;
				m_mapCurrentLA[c_it->first].unRelatedCount = 0;
			}
		}
		c_it++;
	}
	ACE_ASSERT(m_mapCurrentLA.size()<= MAX_LIMITED_ACTIVITY_COUNT);
}

void LimitedActivityMgr::RefreshOld()
{
	ACE_INT32 now = GameUtils::get_utc();//获取当前时间
	std::map<ACE_UINT32, LimitedActivityInfo>::iterator it = m_mapCurrentLA.begin();//当前活动任务列表
	while(it != m_mapCurrentLA.end())
	{
		if (it->second.unCloseTime < now)
			it = m_mapCurrentLA.erase(it);
		else
			it++;
	}
}

void LimitedActivityMgr::update_2_db()
{
	RefreshOld();//删除老的数据 新数据还未加载故不需要存储
	MsgDBLimitedActivityList db_request;
	int count =0;
	std::map<ACE_UINT32, LimitedActivityInfo>::const_iterator c_it = m_mapCurrentLA.begin();//当前活动任务列表
	while(c_it != m_mapCurrentLA.end() && count < MAX_LIMITED_ACTIVITY_COUNT )
	{
		db_request.m_LAList[count] = c_it->second;
		c_it++;
		count++;
	}

	db_request.m_unCount = count;
	m_map->add_db_request(ADAPTER_DB_HOME_MGR, MSG_DB_UPDATE_LA_PROGRESS_RESPONSE, (char *)&db_request, sizeof(MsgDBLimitedActivityList));
}

void LimitedActivityMgr::update_2_db( const LimitedActivityInfo & laconfig )
{
	LimitedActivityInfo db_request = laconfig;
	db_request.unDealTime = GameUtils::get_utc();
	m_map->add_db_request(ADAPTER_DB_HOME_MGR, MSG_DB_UPDATE_LA_PROGRESS_RESPONSE1, (char *)&db_request, sizeof(LimitedActivityInfo));
}

int LimitedActivityMgr::GetReward( ACE_UINT32 unLAMissionID, RewardInfo &oRewardInfo )
{
	ACE_INT32 unProgress = 0;
	LimitedActivityInfo * pLa = NULL;
	if (ChickCanGetReward(unLAMissionID,unProgress,pLa))//活动在范围内
	{
		//查看是否被领过
		for (int i = 0;i<pLa->unRelatedCount;i++)
		{
			if (pLa->unRelatedItems[i] == unLAMissionID)//已经被领过了
				return ERROR_MSG_GOT;
		}
		//-----------------------end
		const std::map<ACE_UINT32, LimitedActivityMissionConfig> &refLAConfig = GAME_CONFIG_INSTANCE::instance()->m_olimitedActivityMissionConfig;
		std::map<ACE_UINT32, LimitedActivityMissionConfig>::const_iterator c_it = refLAConfig.find(unLAMissionID);
		if (c_it != refLAConfig.end())
		{
			if(unProgress >= c_it->second.unMissionType[2])//已经达到了先决条件
			{
				if(pLa->unRelatedCount<MAX_RelatedT_ITEMS)
				{
					pLa->unRelatedItems[pLa->unRelatedCount] = unLAMissionID;
					pLa->unRelatedCount++;
					update_2_db(*pLa);//更新到数据库
				}
				else
					return ERROR_MSG_MAX;

				m_map->get_reward_from_config_reward(oRewardInfo,c_it->second.stReward,1,1);
				//----------log日志
				//领取限时活动
				LogItemInfo logInfo;
				logInfo.m_goodsID = unLAMissionID;//装备id
				logInfo.m_op_action = enum_LOG_ACTION::LOG_ACTION_Limited_Activity;//动作原因
				logInfo.SetOp_Way(_LOG_OP_WAY_Limited_Activity);//途径(附加信息)
				m_map->get_reward(oRewardInfo,logInfo);//添加数据到数据库
				return 0;
			}
		}
	}

	return ERROR_MSG_ACTIVE_GOT;
}


int LimitedActivityMgr::GetLACurrentList( MsgGMLimitedActivityListResponse & response )
{
	Refresh();
	response.m_unCount = 0;
	std::map<ACE_UINT32, LimitedActivityInfo>::const_iterator c_it = m_mapCurrentLA.begin();//当前活动任务列表
	while(c_it != m_mapCurrentLA.end())
	{
		response.m_LAList[response.m_unCount] = c_it->second;
		response.m_unCount++;
		if (response.m_unCount >= MAX_LIMITED_ACTIVITY_COUNT)
			break;
		c_it++;
	}

	return 0;
}

bool LimitedActivityMgr::ChickCanGetReward( ACE_UINT32 unLAMissionID,ACE_INT32 & unProgress,LimitedActivityInfo *& pLa )
{
	unProgress = 0;
	//先判断能不能领取
	Refresh();
	const std::map<ACE_UINT32, LimitedActivityConfig> &refLAConfig = GAME_CONFIG_INSTANCE::instance()->m_olimitedActivityConfig;
	std::map<ACE_UINT32, LimitedActivityConfig>::const_iterator c_it = refLAConfig.begin();
	while(c_it != refLAConfig.end())
	{
		for (int i=0;i<c_it->second.unRelatedCount;i++)
		{
			if (c_it->second.unRelatedItems[i] == unLAMissionID)//找到了
			{
				std::map<ACE_UINT32, LimitedActivityInfo>::iterator _c_it = m_mapCurrentLA.find(c_it->first);//当前活动任务列表
				if (_c_it != m_mapCurrentLA.end())//在时间范围内 没有判断先决条件，在getreward中判断
				{
					unProgress = _c_it->second.unProgress;
					pLa = &_c_it->second;
					return true;
				}
			}
		}
		c_it++;
	}
	//------------------------end

	return false;
}

LimitedActivityMissionConfig LimitedActivityMgr::FindLAmissionItem( ACE_UINT32 unLAMissionID )
{
	LimitedActivityMissionConfig lamConfig;
	ZeroVar(lamConfig);
	const std::map<ACE_UINT32, LimitedActivityMissionConfig> &refLAConfig = GAME_CONFIG_INSTANCE::instance()->m_olimitedActivityMissionConfig;
	std::map<ACE_UINT32, LimitedActivityMissionConfig>::const_iterator c_it = refLAConfig.find(unLAMissionID);
	if (c_it != refLAConfig.end())
		lamConfig = c_it->second;

	return lamConfig;
}

LimitedActivityConfig LimitedActivityMgr::FindLAItem( ACE_UINT32 unLAID )
{
	LimitedActivityConfig laConfig;
	ZeroVar(laConfig);
	const std::map<ACE_UINT32, LimitedActivityConfig> &refLAConfig = GAME_CONFIG_INSTANCE::instance()->m_olimitedActivityConfig;
	std::map<ACE_UINT32, LimitedActivityConfig>::const_iterator c_it = refLAConfig.find(unLAID);
	if (c_it != refLAConfig.end())
		laConfig = c_it->second;

	return laConfig;
}

bool LimitedActivityMgr::ChickTimeIsInActivity( LimitedActivityConfig & laconfig )
{
	//时间判断
	ACE_INT32 now = GameUtils::get_utc();
	if(laconfig.unStartTime <= now && laconfig.unEndTime > now)//大时间对了
	{
		int week = GameUtils::get_week(now);
		if((laconfig.unWeekCircle & (1 << week)) != 0)//周循环通过
		{
			ACE_INT32 day = GameUtils::Get_current_day_0_0();//获取今天的凌晨零点
			ACE_INT32 unDayStart = day + laconfig.unDayTimeStart;//一天的开始时间
			ACE_INT32 unDayEnd = day + laconfig.unDayTimeEnd;//一天的结束时间
			if(unDayStart<=now && unDayEnd>=now)
				return true;
		}
	}

	return false;
}

bool LimitedActivityMgr::DoLATypeLinkcost( ACE_UINT32 unLAMissionType,CostInfoList & costList/*,int times*/)
{
	//LA_TYPE_LINK= 0,
	//编号【0】关联任务类，任务1ID，任务2ID
	return DoActionFindByType(LA_TYPE_LINK,unLAMissionType,costList,/*times,*/&LimitedActivityMgr::CallFun_Cost);
}

bool LimitedActivityMgr::DoLATypeLuck( ACE_UINT32 unLAMissionType,const CostInfoList & costList,ACE_UINT32 unMissionType/*,int times*/ )
{
	//LA_TYPE_LINK= 0,
	//编号【0】关联任务类，任务1ID，任务2ID
	unMissionType = 1;
	for(int i = 0;i < costList.unCount;i ++)
	{
		switch(costList.list[i].unID)
		{
		case RES_CURRENCY_MONEY:
			{
				unMissionType =2;
			}break;
		case RES_CURRENCY_FRIENDSHIP:
			{
				unMissionType = 1;
			}break;
		}
	}
	return DoActionFindByType(LA_TYPE_LINK,unLAMissionType,unMissionType,/*times,*/&LimitedActivityMgr::CallFun_Luck);
}

bool LimitedActivityMgr::DoLATypeSecret( ACE_UINT32 unLAMissionType,CostInfoList & costList/*,int times*/ )
{
	//编号【1】神秘商店折扣任务类，货币类型，折扣率
	return DoActionFindByType(LA_TYPE_1,unLAMissionType,costList,/*times,*/&LimitedActivityMgr::CallFun_Secret);
}

bool LimitedActivityMgr::DoLATypeMapCount( ACE_UINT32 unMapID,ACE_UINT32 type,ACE_UINT32 & nMult )
{
	//编号【2】关卡上限双倍，关卡1ID，关卡2ID，…
	return DoActionFindByType(type,unMapID,nMult,/*times,*/&LimitedActivityMgr::CallFun_MapCount);
}

bool LimitedActivityMgr::DoLATypeLeveUP( ACE_UINT32 unLAtype,ACE_UINT32 & nMult )
{
	return DoActionFindByType(unLAtype,0,nMult,/*times,*/&LimitedActivityMgr::CallFun_LeveUp);
}

bool LimitedActivityMgr::DoLATypeLinkRecharge( ACE_UINT32 unLAMissionType,ACE_UINT32 nGold/*,int times*/ )
{
	return DoActionFindByType(LA_TYPE_LINK,0,nGold,/*times,*/&LimitedActivityMgr::CallFun_Recharge);
}

bool LimitedActivityMgr::DoLATypeLinkRechargeGift(ACE_UINT32 unProductId )
{
	const RechargeRes * res = (const RechargeRes *)ITEM_RES_MGR_INSTANCE::instance()->get_item_res(unProductId);
	if (res)
	{
		if (res->m_unSubType == RechargeRes_type_LIMITED_ACTIVITY)//是限时活动
		{
			return DoActionFindByType(LA_TYPE_11,0,unProductId,/*times,*/&LimitedActivityMgr::callFun_RechargeGift);

			// 			Refresh();//先更新
			// 			std::map<ACE_UINT32, LimitedActivityInfo>::iterator it = m_mapCurrentLA.begin();//当前活动任务列表
			// 			while(it != m_mapCurrentLA.end())
			// 			{
			// 				if (it->second.unLinkType == LA_TYPE_11)
			// 				{
			// 					LimitedActivityConfig laconfig = FindLAItem(it->second.unLAID);
			// 					for (int i=0;i<laconfig.unRelatedCount;i++)
			// 					{
			// 						if (laconfig.unRelatedItems[i] == unProductId)//找到了 可以领取
			// 						{
			// 							ACE_UINT32 unCurrentUTC = GameUtils::get_utc();
			// 							int dwDayOffset = GameUtils::get_day_different(unCurrentUTC, it->second.unDealTime);
			// 							if ( dwDayOffset > 0)
			// 							{
			// 								it->second.unRelatedCount = 0;
			// 								ZeroVar(it->second.unRelatedItems);
			// 							}	
			// 						
			// 							//判断今天是否已经领取过
			// 							bool isGet =false;
			// 							for(int j=0;j<it->second.unRelatedCount;j++)
			// 							{
			// 								if (it->second.unRelatedItems[j] == unProductId)//已经领取了
			// 								{
			// 									isGet = true;
			// 									break;
			// 								}
			// 							}
			// 
			// 							if (!isGet && it->second.unRelatedCount < MAX_RelatedT_ITEMS)//还没有领取过
			// 							{
			// 								it->second.unRelatedItems[it->second.unRelatedCount] = unProductId;
			// 								it->second.unRelatedCount ++;
			// 							}
			// 
			// 
			// 							it->second.unDealTime = unCurrentUTC;
			// 							update_2_db(it->second);
			// 							return true;
			// 						}
			// 					}
			// 				}
			// 				it++;
			// 			}
		}
	}

	return false;
}

bool LimitedActivityMgr::DoLATypeLogin()
{
	ACE_UINT32 unLAMissionType = LA_MISSION_TYPE_1005;
	ACE_UINT32 unTimes = 1;//次数
	return DoActionFindByType(LA_TYPE_LINK,unLAMissionType,unTimes,/*times,*/&LimitedActivityMgr::callFun_Login);
}

bool LimitedActivityMgr::CallFun_Cost( ACE_INT32 unLAMissionType,LimitedActivityInfo & info,CostInfoList & costList /*,int times*/)
{
	LimitedActivityConfig laconfig = FindLAItem(info.unLAID);
	if (laconfig.unID > 0)
	{
		if (ChickTimeIsInActivity(laconfig))//时间检查
		{
			for (int i=0;i<laconfig.unRelatedCount;i++)
			{
				LimitedActivityMissionConfig lamConfig = FindLAmissionItem(laconfig.unRelatedItems[i]);
				if (lamConfig.unID > 0 && lamConfig.unMissionType[0] == unLAMissionType)//找到了 活跃度
				{
					for(int j = 0;j < costList.unCount;j ++)
					{
						if (costList.list[j].unID == lamConfig.unMissionType[1])
						{
							info.unProgress += costList.list[j].cost/**times*/;//物品id
							update_2_db(info);//更新到数据库
							isDown(info.unLAID);
							return true;
						}
					}
				}
			}
		}
		//---------------------
	}
	return false;
}

bool LimitedActivityMgr::CallFun_Luck( ACE_INT32 unLAMissionType,LimitedActivityInfo & info,ACE_UINT32 & unMissionType/*,int times*/ )
{
	LimitedActivityConfig laconfig = FindLAItem(info.unLAID);
	if (laconfig.unID > 0)
	{
		if (ChickTimeIsInActivity(laconfig))//时间检查
		{
			for (int i=0;i<laconfig.unRelatedCount;i++)
			{
				LimitedActivityMissionConfig lamConfig = FindLAmissionItem(laconfig.unRelatedItems[i]);
				if (lamConfig.unID > 0 && lamConfig.unMissionType[0] == unLAMissionType)//找到了 活跃度
				{
					if (unMissionType == lamConfig.unMissionType[1])
					{
						info.unProgress += 1;//进度
						update_2_db(info);//更新到数据库
						isDown(info.unLAID);
						return true;
					}
				}
			}
		}
		//---------------------
	}
	return false;
}


bool LimitedActivityMgr::CallFun_Secret( ACE_INT32 unLAMissionType,LimitedActivityInfo & info,CostInfoList & costList/*,int times*/ )
{
	LimitedActivityConfig laconfig = FindLAItem(info.unLAID);
	if (laconfig.unID > 0)
	{
		if (ChickTimeIsInActivity(laconfig))//时间检查
		{
			ACE_ASSERT(laconfig.unRelatedCount == 2);//0折扣类型 1折扣率
			for(int i=0;i<costList.unCount;i++)
			{
				if (costList.list[i].unID == laconfig.unRelatedItems[0])//找到此折扣商品
				{
					//立即折扣
					costList.list[i].cost *= (double)laconfig.unRelatedItems[1]*0.01;
					return true;
				}
			}
		}
		//---------------------
	}
	return false;
}


bool LimitedActivityMgr::CallFun_MapCount( ACE_INT32 unMapID,LimitedActivityInfo & info,ACE_UINT32 & nMult/*,int times*/ )
{
	LimitedActivityConfig laconfig = FindLAItem(info.unLAID);
	if (laconfig.unID > 0)
	{
		if (ChickTimeIsInActivity(laconfig))//时间检查
		{
			for(int i=0;i<laconfig.unRelatedCount;i++)
			{
				if (unMapID == laconfig.unRelatedItems[i])//找到此折扣商品
				{
					//立即折扣
					nMult = 2;
					return true;
				}
			}
		}
		//---------------------
	}
	return false;
}

bool LimitedActivityMgr::CallFun_LeveUp( ACE_INT32 unMapID,LimitedActivityInfo & info,ACE_UINT32 & nMult/*,int times*/ )
{
	LimitedActivityConfig laconfig = FindLAItem(info.unLAID);
	if (laconfig.unID > 0)
	{
		if (ChickTimeIsInActivity(laconfig))//时间检查
		{
			nMult = laconfig.unRelatedItems[1];//立即折扣
			return true;
		}
		//---------------------
	}
	return false;
}

bool LimitedActivityMgr::CallFun_Recharge( ACE_INT32 unMapID,LimitedActivityInfo & info,ACE_UINT32 & nGold/*,int times*/ )
{
	LimitedActivityConfig laconfig = FindLAItem(info.unLAID);
	if (laconfig.unID > 0)
	{
		if (ChickTimeIsInActivity(laconfig))//时间检查
		{
			info.unProgress += nGold;//立即更新
			update_2_db(info);//更新到数据库
			isDown(info.unLAID);
			return true;
		}
		//---------------------
	}
	return false;
}

void LimitedActivityMgr::Cost_basic_info( int nCoin, int nMoney, int nExp, int nPowerPoint, int nHonour, int nFriendship )
{
	CostInfoList costList;
	ZeroVar(costList);
	int c = 0;
	if (nCoin < 0)//消耗贝壳
	{
		costList.list[c].unID = RES_CURRENCY_COIN;
		costList.list[c].cost = -nCoin;
		c++;
	}

	if (nMoney < 0)//金卡消耗
	{
		costList.list[c].unID = RES_CURRENCY_MONEY;
		costList.list[c].cost = -nMoney;
		c++;
	}

	if (nExp < 0)//exp消耗
	{
		costList.list[c].unID = RES_CURRENCY_EXP;
		costList.list[c].cost = -nExp;
		c++;
	}

	if (nPowerPoint < 0)//合金
	{
		costList.list[c].unID = RES_CURRENCY_POWERPOINT;
		costList.list[c].cost = -nPowerPoint;
		c++;
	}

	if (nHonour < 0)//荣誉值
	{
		costList.list[c].unID = RES_CURRENCY_HONOUR;
		costList.list[c].cost = -nHonour;
		c++;
	}

	if (nFriendship < 0)//友情点
	{
		costList.list[c].unID = RES_CURRENCY_FRIENDSHIP;
		costList.list[c].cost = -nFriendship;
		c++;
	}

	costList.unCount = c;
	if (c>0)
	{
		DoLATypeLinkcost(LA_MISSION_TYPE_1002, costList);
	}
}

int LimitedActivityMgr::ChickLARecharge( const RechargeRes * res )
{
	if (!res)
		return ERROR_MSG_RES;

	if (res->m_unSubType == RechargeRes_type_LIMITED_ACTIVITY)//是限时活动
	{
		Refresh();//先更新
		std::map<ACE_UINT32, LimitedActivityInfo>::const_iterator c_it = m_mapCurrentLA.begin();//当前活动任务列表
		while(c_it != m_mapCurrentLA.end())
		{
			if (c_it->second.unLinkType == LA_TYPE_11)
			{
				LimitedActivityConfig laconfig = FindLAItem(c_it->second.unLAID);
				if (ChickTimeIsInActivity(laconfig))//时间检查
				{
					for (int i=0;i<laconfig.unRelatedCount;i++)
					{
						if (laconfig.unRelatedItems[i] == res->m_unResID)//找到了 可以领取
						{
							ACE_UINT32 unCurrentUTC = GameUtils::get_utc();
							int dwDayOffset = GameUtils::get_day_different(unCurrentUTC, c_it->second.unDealTime);
							if ( dwDayOffset > 0)
								return 0;
							else//判断今天是否已经领取过
							{
								bool isGet =false;
								for(int j=0;j<c_it->second.unRelatedCount;j++)
								{
									if (c_it->second.unRelatedItems[j] == res->m_unResID)//已经领取了
									{
										isGet = true;
										break;
									}
								}

								if (!isGet)//还没有领取过
									return 0;
								else
									return ERROR_MSG_GOT;
							}

						}
					}
				}
			}
			c_it++;
		}

		return ERROR_MSG_TIME_OUT;
	}
	else
		return 0;

}


bool LimitedActivityMgr::callFun_RechargeGift( ACE_INT32 unMapID,LimitedActivityInfo & info,ACE_UINT32 & unProductId )
{
	LimitedActivityConfig laconfig = FindLAItem(info.unLAID);
	if (ChickTimeIsInActivity(laconfig))//时间检查
	{
		for (int i=0;i<laconfig.unRelatedCount;i++)
		{
			if (laconfig.unRelatedItems[i] == unProductId)//找到了 可以领取
			{
				ACE_UINT32 unCurrentUTC = GameUtils::get_utc();
				int dwDayOffset = GameUtils::get_day_different(unCurrentUTC, info.unDealTime);
				if ( dwDayOffset > 0)
				{
					info.unRelatedCount = 0;
					ZeroVar(info.unRelatedItems);
				}	

				//判断今天是否已经领取过
				bool isGet =false;
				for(int j=0;j<info.unRelatedCount;j++)
				{
					if (info.unRelatedItems[j] == unProductId)//已经领取了
					{
						isGet = true;
						break;
					}
				}

				if (!isGet && info.unRelatedCount < MAX_RelatedT_ITEMS)//还没有领取过
				{
					info.unRelatedItems[info.unRelatedCount] = unProductId;
					info.unRelatedCount ++;
				}


				info.unDealTime = unCurrentUTC;
				update_2_db(info);
				return true;
			}
		}
	}

	return false;
}

bool LimitedActivityMgr::callFun_Login( ACE_INT32 unLAMissionType,LimitedActivityInfo & info,ACE_UINT32 & unTimes )
{
	LimitedActivityConfig laconfig = FindLAItem(info.unLAID);//查找limitedactivity.xml
	if (laconfig.unID > 0)
	{
		if (ChickTimeIsInActivity(laconfig))//时间检查
		{
			for (int i=0;i<laconfig.unRelatedCount;i++)
			{
				LimitedActivityMissionConfig lamConfig = FindLAmissionItem(laconfig.unRelatedItems[i]);//查找limitedactivitymission.xml
				if (lamConfig.unID > 0 && lamConfig.unMissionType[0] == unLAMissionType)//找到了 活跃度1005
				{
					ACE_UINT32 unNow = GameUtils::get_utc();
					ACE_UINT32 offsetday = GameUtils::cut_current_day_0_0(unNow) - GameUtils::cut_current_day_0_0(info.unDealTime);
					offsetday = offsetday/(24*60*60);

					if (offsetday != 0)//不是同天登录
					{
						if (offsetday > 1)
							info.unProgress = 1;
						else
							info.unProgress++;
						info.unDealTime = unNow;//最近处理时间
						update_2_db(info);
						isDown(info.unLAID);
					}

					return true;
				}
			}
		}
		//---------------------
	}
	return false;
}

void LimitedActivityMgr::isDown( ACE_UINT32 unLAMissionID )
{
	ACE_INT32 unProgress = 0;
	LimitedActivityInfo * pLa = NULL;
	if (ChickCanGetReward(unLAMissionID,unProgress,pLa))//活动在范围内
	{
		//查看是否被领过
		for (int i = 0;i<pLa->unRelatedCount;i++)
		{
			if (pLa->unRelatedItems[i] == unLAMissionID)//已经被领过了
				return;
		}
		//-----------------------end

		const std::map<ACE_UINT32, LimitedActivityMissionConfig> &refLAConfig = GAME_CONFIG_INSTANCE::instance()->m_olimitedActivityMissionConfig;
		std::map<ACE_UINT32, LimitedActivityMissionConfig>::const_iterator c_it = refLAConfig.find(unLAMissionID);
		if (c_it != refLAConfig.end())
		{
			if(unProgress >= c_it->second.unMissionType[2])//已经达到了先决条件
			{
				if(pLa->unRelatedCount<MAX_RelatedT_ITEMS)
				{
					m_isHaveNew = true;
				}
				else
					return;
			}
		}
	}

	return;
}

