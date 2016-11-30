#include "MapInfoMgr.h"
#include "..\..\GameBase\res\ItemResMgr.h"

#include "..\..\GameBase\res\MapGroupRes.h"
#include "..\..\GameBase\res\DropRes.h"
#include "..\..\GameBase\res\MonsterRes.h"
#include "..\..\GameBase\res\SkillRes.h"
#include "..\..\GameBase\res\GameConfig.h"
#include "..\Map.h"
#include "LootMgr.h"
#include "GlobalInfoMgr.h"
#include "ActivityMgr.h"
#include "TeamProperty.h"

#include "..\..\Base\Service\BaseService.h"


MapInfoMgr::MapInfoMgr()
{
	m_unMapCount = 0;
	m_info.nGlobalMapEventType = GLOBAL_MAP_EVENT_NONE;
	m_unDoubleVersion = -1;
	m_unReward3Star =0 ;
	ZeroVar(m_starCountList);

	ACE_OS::memset(m_flagList, 0, sizeof(MapFlagInfo) * MAX_MAP_COUNT);
	ACE_OS::memset(m_giftList, 0, sizeof(MapFlagInfo) * MAX_MAP_COUNT);
	isSpecialMap = false;
}

MapInfoMgr::~MapInfoMgr()
{

}


void MapInfoMgr::initEx( MapInstanceInfo &instanceInfo, RewardInfo &reward, MapFlagInfo *list, ACE_UINT32 unLastRewardTime, ACE_UINT32 unFreeRebornCount, ACE_UINT32 unLastRebornTime, MapFlagInfo *giftList )
{
	ACE_OS::memcpy(m_flagList, list, sizeof(MapFlagInfo) * MAX_MAP_COUNT);
	ACE_OS::memcpy(m_giftList, giftList, sizeof(MapFlagInfo) * MAX_MAP_COUNT);
	m_info = instanceInfo;
	m_reward = reward;
	m_unLastRewardTime = unLastRewardTime;
	m_unFreeRebornCount = unFreeRebornCount;
	m_unLastRebornTime = unLastRebornTime;

	int tmpCount = GLOBAL_INFO_MGR_INSTANCE::instance()->m_unMapCount;
	m_unMapGroupCount = GLOBAL_INFO_MGR_INSTANCE::instance()->m_unMapGroupCount;


	ACE_UINT32 tmpID;
	ACE_UINT32 unCurrentID = 0;
	ACE_UINT32 unMapID;

	if(m_flagList[0].unMapID == 0)
	{
		for(int i = 0;i < m_unMapGroupCount;i ++)
		{
			ZeroVar(m_giftList[i]);
			m_giftList[i].unMapID = GLOBAL_INFO_MGR_INSTANCE::instance()->m_mapGroupList[i];
		}

		m_unMapCount = 0;
		for(int i = 0;i < tmpCount;i ++)
		{
			if (m_unMapCount >= MAX_MAP_COUNT)
				break;

			unMapID = GLOBAL_INFO_MGR_INSTANCE::instance()->m_mapList[i];

			tmpID = GET_ITEM_MASK_ID(unMapID, 1);

			if(unCurrentID != tmpID)
			{
				unCurrentID = tmpID;
				ZeroVar(m_flagList[m_unMapCount]);
				m_flagList[m_unMapCount].unMapID = tmpID;

				m_unMapCount ++;
			}
		}
	}

	int level;
	m_unMapCount = 0;
	for(int i = 0;i < tmpCount;i ++)
	{
		if (m_unMapCount >= MAX_MAP_COUNT)
			break;

		unMapID = GLOBAL_INFO_MGR_INSTANCE::instance()->m_mapList[i];

		tmpID = GET_ITEM_MASK_ID(unMapID, 1);
		level = GET_ITEM_ID_INFO(unMapID, 0, 1);

		if(unCurrentID != tmpID)
		{
			unCurrentID = tmpID;
			m_unMapCount ++;
		}

		int idx = GET_ITEM_ID_INFO(unMapID, 4, 2) - 1;
		m_starCountList[idx] += GameUtils::get_map_star_count(m_flagList[m_unMapCount - 1].unFlag, level);
	}

	this->unlock_map(GAME_CONFIG_INSTANCE::instance()->m_unInitUnlockMapID);
	std::map<ACE_UINT32, ACE_UINT32> &unlockMap = GAME_CONFIG_INSTANCE::instance()->m_oUnlockPrefixMapID;

	for (std::map<ACE_UINT32, ACE_UINT32>::iterator itMap = unlockMap.begin();itMap != unlockMap.end();++itMap)
	{
		this->unlock_map(itMap->first); //先这样吧
	}

	if(GameUtils::get_day_different(GameUtils::get_utc(), m_unLastRewardTime) != 0)
	{
		Reset_map_day_different_count();
	}
}


void MapInfoMgr::init(MapInstanceInfo &instanceInfo, RewardInfo &reward, MapFlagInfo *list, ACE_UINT32 unLastRewardTime, ACE_UINT32 unFreeRebornCount, ACE_UINT32 unLastRebornTime, MapFlagInfo *giftList)
{
	m_info = instanceInfo;
	m_reward = reward;
	//ACE_OS::memcpy(m_flagList, list, sizeof(MapFlagInfo) * MAX_MAP_COUNT);
	//ACE_OS::memcpy(m_giftList, giftList, sizeof(MapFlagInfo) * MAX_MAP_COUNT);

	ACE_OS::memset(m_flagList, 0, sizeof(MapFlagInfo) * MAX_MAP_COUNT);
	ACE_OS::memset(m_giftList, 0, sizeof(MapFlagInfo) * MAX_MAP_COUNT);

	int tmpCount = GLOBAL_INFO_MGR_INSTANCE::instance()->m_unMapCount;
	m_unMapGroupCount = GLOBAL_INFO_MGR_INSTANCE::instance()->m_unMapGroupCount;

	int i, j;
	int offset = 0;

	for(i = 0;i < m_unMapGroupCount;i ++)
	{
		m_giftList[i].unMapID = GLOBAL_INFO_MGR_INSTANCE::instance()->m_mapGroupList[i];
		for(j = offset;j < MAX_MAP_COUNT;j ++)
		{
			if(giftList[j].unMapID == 0)
			{
				break;
			}
			if(giftList[j].unMapID == m_giftList[i].unMapID)
			{
				m_giftList[i].unFlag = giftList[j].unFlag;
				m_giftList[i].unFlag2 = giftList[j].unFlag2;
				break;
			}
		}
		offset = j + 1;
		m_starCountList[i] = 0;
	}

	ACE_UINT32 tmpID;
	ACE_UINT32 unCurrentID = 0;
	ACE_UINT32 unMapID;
	int level;
	offset = 0;
	m_unMapCount = 0;
	for(i = 0;i < tmpCount;i ++)
	{
		if (m_unMapCount >= MAX_MAP_COUNT)
			break;

		unMapID = GLOBAL_INFO_MGR_INSTANCE::instance()->m_mapList[i];

		tmpID = GET_ITEM_MASK_ID(unMapID, 1);
		level = GET_ITEM_ID_INFO(unMapID, 0, 1);

		if(unCurrentID != tmpID)
		{
			unCurrentID = tmpID;
			m_flagList[m_unMapCount].unMapID = tmpID;

			for(j = offset;j < MAX_MAP_COUNT;j ++)
			{
				if(list[j].unMapID == 0)
				{
					break;
				}
				if(list[j].unMapID == tmpID)
				{
					m_flagList[m_unMapCount].unFlag = list[j].unFlag;
					m_flagList[m_unMapCount].unFlag2 = list[j].unFlag2;
					break;
				}
			}
			offset = j + 1;

			m_unMapCount ++;
		}

		int idx = GET_ITEM_ID_INFO(unMapID, 4, 2) - 1;
		
		m_starCountList[idx] += GameUtils::get_map_star_count(m_flagList[m_unMapCount - 1].unFlag, level);
	}
	this->unlock_map(GAME_CONFIG_INSTANCE::instance()->m_unInitUnlockMapID);
	std::map<ACE_UINT32, ACE_UINT32> &unlockMap = GAME_CONFIG_INSTANCE::instance()->m_oUnlockPrefixMapID;
	std::map<ACE_UINT32, ACE_UINT32>::iterator itMap = unlockMap.begin();
	for (;itMap != unlockMap.end();++itMap)
	{
		this->unlock_map(itMap->first); //先这样吧
	}

	//sort
	//parse_flag_list();

	m_unLastRewardTime = unLastRewardTime;
	m_unFreeRebornCount = unFreeRebornCount;
	m_unLastRebornTime = unLastRebornTime;
	//m_battleInfo = battleInfo;
	//m_battleSnapInfo = snapInfo;

	//init_stage_data(true);

	if(GameUtils::get_day_different(GameUtils::get_utc(), m_unLastRewardTime) != 0)
	{
		Reset_map_day_different_count();
// 		for(i = 0;i < tmpCount;i ++)
// 		{
// 			unMapID = GLOBAL_INFO_MGR_INSTANCE::instance()->m_mapList[i];
// 			ACE_UINT32 t = GET_ITEM_MASK_ID(unMapID, 1);
// 			int level = GET_ITEM_ID_INFO(unMapID, 0, 1);
// 
// 			MapFlagInfo *flagInfo = get_map_flag_info(t);
// 		
// 			flagInfo->unFlag = GameUtils::set_map_enter_count(flagInfo->unFlag, 0, level);
// 			flagInfo->unFlag2 = GameUtils::set_map_reset_count(flagInfo->unFlag2, 0,level);
// 		}
// 		update_map_flag_2_db();
	}
}

void MapInfoMgr::initDoubleDrop(MsgDBDoubleDropInfoResponse &info)
{
	m_unDoubleVersion = info.m_unVersion;
	for (int i=0;i<info.m_unCount;++i)
	{
		m_setUsedDouble.insert(info.m_usedDoubleList[i]);
	}
}

void MapInfoMgr::send_info(ObjAdr &targetAdr, ACE_UINT32 unSN)
{
	MsgMapListInfoResponse response;
	response.nResult = 0;
	response.unSN = unSN;
	response.instanceInfo = m_info;
	//response.battleInfo = m_battleInfo;
	//response.reward = m_reward;
	response.unCount = m_unMapCount;
	ACE_OS::memcpy(response.flagList, m_flagList, sizeof(MapFlagInfo) * MAX_MAP_COUNT);

	response.unLastRewardTime = m_unLastRewardTime;
	response.unFreeRebornCount = m_unFreeRebornCount;
	response.unLastRebornTime = m_unLastRebornTime;

	response.unMapGroupCount = m_unMapGroupCount;
	ACE_OS::memcpy(response.giftList, m_giftList, sizeof(MapFlagInfo) * MAX_MAP_COUNT);

	m_map->sendMsg(SERVICE_MESSAGE_TYPE_USER, MSG_MAP_LIST_INFO_RESPONSE, (char *)&response, sizeof(MsgMapListInfoResponse), targetAdr);
}

int MapInfoMgr::get_map_gift(ACE_UINT32 unMapGroupID, ACE_UINT32 unIdx, RewardInfo &reward)
{
	GameUtils::reset_reward(reward);

	if(GET_ITEM_TYPE(unMapGroupID) != ITEM_RES_TYPE_MAP_GROUP)
	{
		return ERROR_MSG_RES;
	}

	MapGroupRes *res = (MapGroupRes *)ITEM_RES_MGR_INSTANCE::instance()->get_item_res(unMapGroupID);

	if(res == NULL)
	{
		return ERROR_MSG_RES;
	}

	int i;
	int idx = -1;
	for(i = 0;i < m_unMapGroupCount;i ++)
	{
		if(m_giftList[i].unMapID == unMapGroupID)
		{
			idx = i;
			break;
		}
	}

	if(idx == -1)
	{
		return ERROR_MSG_GIFT;
	}

	if(unIdx < 0 || unIdx >= MAP_REWARD_COUNT)
	{
		return ERROR_MSG_PARAMETER;
	}

	if((m_giftList[idx].unFlag & (1 << unIdx)) != 0)
	{
		return ERROR_MSG_GOT;
	}

	if(m_starCountList[idx] < res->m_unRewardStarNumber[unIdx])
	{
		return -1;
	}

	m_giftList[idx].unFlag = m_giftList[idx].unFlag | (1 << unIdx);

	update_map_flag_2_db();


	m_map->get_reward_from_config_reward(reward, res->m_rewardList[unIdx], 1, 1);
	//----------log日志
	//关卡闯关
	LogItemInfo logInfo;
	logInfo.m_goodsID = m_giftList[idx].unMapID;//map id
	logInfo.m_op_action = enum_LOG_ACTION::LOG_ACTION_map_gift;//动作原因
	logInfo.SetOp_Way(_LOG_OP_WAY_map_gift);//途径(附加信息)
	m_map->get_reward(reward,logInfo);

	return 0;
}

/*
void MapInfoMgr::parse_flag_list()
{
	m_unMapCount = 0;
	int i, j;

	for(i = 0;i < MAX_MAP_COUNT;i ++)
	{
		if(m_flagList[i].unMapID == 0)
		{
			break;
		}

		m_unMapCount ++;
	}

	ACE_UINT32 tmp_min;
	int idx;
	MapFlagInfo tmp;
	for(i = 0;i < m_unMapCount;i ++)
	{
		idx = i;
		tmp_min = m_flagList[i].unMapID;
		for(j = i + 1;j < m_unMapCount;j ++)
		{
			if(m_flagList[j].unMapID < tmp_min)
			{
				tmp_min = m_flagList[j].unMapID;
				idx = j;
			}
		}

		if(idx != i)
		{
			tmp = m_flagList[idx];
			m_flagList[idx] = m_flagList[i];
			m_flagList[i] = tmp;
		}
	}
}
*/

MapFlagInfo *MapInfoMgr::get_map_flag_info(ACE_UINT32 unMapID)
{
	int s = 0;
	int e = m_unMapCount - 1;

	int t;
	do 
	{
		t = (s + e) / 2;
		if(m_flagList[t].unMapID == unMapID)
		{
			return &m_flagList[t];
		}
		else if(m_flagList[t].unMapID < unMapID)
		{
			s = t + 1;
		}
		else
		{
			e = t - 1;
		}
	} while (s <= e);

	return NULL;
}

MapFlagInfo *MapInfoMgr::add_map_flag_info(ACE_UINT32 unMapID)
{
	ACE_UINT32 tmp_id = GET_ITEM_MASK_ID(unMapID, 1);

	int i;
	int idx = -1;

	for(i = 0;i < m_unMapCount;i ++)
	{
		if(m_flagList[i].unMapID == unMapID)
		{
			return &m_flagList[i];
		}
		else if(m_flagList[i].unMapID > unMapID)
		{
			idx = i;
			break;
		}
	}

	if(idx == -1)
	{
		idx = m_unMapCount;
		
	}
	else
	{
		for(i = m_unMapCount;i > idx;i --)
		{
			m_flagList[i] = m_flagList[i - 1];
		}
	}

	ACE_OS::memset(&m_flagList[idx], 0, sizeof(MapFlagInfo));

	m_flagList[idx].unMapID = tmp_id;

	m_unMapCount ++;
	//this->unlock_map(unMapID);

	return &m_flagList[idx];
}

//进入管卡前就将奖品设置成功了，
int MapInfoMgr::enter_map(ACE_UINT32 unMapIDT,ACE_UINT32 unsMapID, int nGlobalMapEventType, CharacterInfoExt *friendInfo)
{
	//ACE_UINT32 t = (unMapID / 10) * 10;
	//int level = unMapID % 10;
	ACE_UINT32 unMapID= unMapIDT;
	if (unsMapID == 0x0FD00101)
	{
		isSpecialMap = true;
		unMapID = unsMapID;
	}
	else
		isSpecialMap = false;

	ACE_UINT32 t = GET_ITEM_MASK_ID(unMapID, 1);
	int level = GET_ITEM_ID_INFO(unMapID, 0, 1);

	//没有多倍体力地图
	int iDuplicationType = GET_ITEM_ID_INFO(unMapID, 2, 4);
	switch (iDuplicationType)
	{
	case 0xA001:
	case 0xA002:
	case 0xA003:
	case 0xA004:
	case 0xA005:
	case 0xB101:
	case 0xB201:
	case 0xB301:
	case 0xB401:
	case 0xB501:
	case 0xB601:
	case 0xB701: 
		{
			m_map->m_unMultEnergy = 1;//不能多倍体力
		}break;
	}
	//---------------------------------end

	MapRes *res = (MapRes *)ITEM_RES_MGR_INSTANCE::instance()->get_item_res(unMapID);

	if(res == NULL)
	{
		return ERROR_MSG_RES;
	}

	MapFlagInfo *flagInfo = get_map_flag_info(t);

	
// 	if(flagInfo == NULL)
// 	{
// 		flagInfo = add_map_flag_info(unMapID);
// 
// 		update_map_flag_2_db();
// 	}
// 
// 	if(!ACTIVITY_MGR_INSTANCE::instance()->is_activity(unMapID) && GameUtils::get_map_unlock_flag(flagInfo->unFlag,level) == 0)
// 	{
// 		return -1;
// 		//this->unlock_map(unMapID);
// 	}
	
	
    if (!check_enter(flagInfo, level, res))
	{
		return ERROR_MSG_TIMES;
	}

	//generate
	_unMapID = unMapIDT;
	_unsMapID = unsMapID;
	if (isSpecialMap)
		m_info.unMapID = unsMapID;
	else
		m_info.unMapID = unMapIDT;
	if(GameUtils::is_hit(res->m_fSubbossRate))
	{
		m_info.unSpecialBossID = 1;
	}
	else
	{
		m_info.unSpecialBossID = 0;
	}

	//m_nGlobalMapEventType = nGlobalMapEventType;
	m_info.nGlobalMapEventType = GLOBAL_MAP_EVENT_NONE;//nGlobalMapEventType; 
	m_info.friendInfo = *friendInfo;

	//GameUtils::reset_reward(m_reward);
	int dropCount = 1;
	int iRawMapID = (t & 0xFFFFFFF0);
	if (isSpecialMap)//是密境地图
	{
		ACE_UINT32 t1 = GET_ITEM_MASK_ID(unMapIDT, 1);
		iRawMapID = (t1 & 0xFFFFFFF0);
	}


	//  关卡双倍掉落
	std::map<UINT32, ACE_Byte> &refMapDoubleDrop = GAME_CONFIG_INSTANCE::instance()->m_vecDoubleDropMap[GAME_CONFIG_INSTANCE::instance()->m_unRefreshDoubleDropVersion];
	std::map<UINT32, ACE_Byte>::iterator itMap = refMapDoubleDrop.find(iRawMapID);
	if (m_map->m_unLevel >= 10 && itMap != refMapDoubleDrop.end() && m_setUsedDouble.count(iRawMapID) == 0)
	{
		m_info.nGlobalMapEventType = itMap->second;
		if (itMap->second == GLOBAL_MAP_EVENT_DROP_DOUBLE)
		{			
			dropCount = 2;
		}
	}

	int old_star = GameUtils::get_map_star(flagInfo->unFlag, level);
	ConfigReward &oReward = old_star > 0 ? res->m_reward : res->m_firstReward;

	//编号【5】关卡掉落双倍，关卡1ID，关卡2ID，…
	ACE_UINT32 count = 1;
	if (m_map->m_LAMgr.DoLATypeMapCount(unMapID,LA_TYPE_5,count))
	{
		count = 2;
	}
	else
		count =1;
	//-----------------------------------end

	GameUtils::reset_reward(m_reward);
	GameUtils::reset_reward(m_rewardTemp);

    if (old_star > 0)
	{
		m_map->add_reward_from_config_reward(m_reward, oReward, 1, 1);//从配置文件中初始化关卡结果
		for (int i=1;i<m_map->m_unMultEnergy;i++)
			m_map->add_reward_from_config_reward(m_reward, res->m_reward, 1, 1);//从配置文件中初始化关卡结果

		if(m_info.unSpecialBossID != 0)
		{
			m_map->add_reward_from_config_reward(m_reward, res->m_specialReward, 1, 1);
		}
	}
	else
	{
		m_map->add_reward_from_config_reward(m_reward, oReward, 1, 1);//从配置文件中初始化关卡结果
		for (int i=1;i<m_map->m_unMultEnergy;i++)
			m_map->add_reward_from_config_reward(m_reward, res->m_reward, 1, 1);//从配置文件中初始化关卡结果
	}

	ACE_UINT32 _drop = dropCount*count;
	if (_drop > 1)
	{
// 		m_rewardCount = _drop;
// 		m_reward.unCoin *=_drop;
// 		m_reward.unMoney *=_drop;
// 		m_reward.unExp *=_drop;
// 		m_reward.unPowerPoint *=_drop;
// 		m_reward.unHonour *=_drop;
// 		m_reward.unRecharge *=_drop;
// 		m_reward.unEnergy *=_drop;
// 		m_reward.unPVPEnergy *=_drop;
// 		m_reward.unFriendship *=_drop;
		for (int i=0;i<m_reward.unCount;i++)
			m_reward.list[i].unCount *= _drop;
	}

	m_rewardTemp = m_reward;
	//编号【4】关卡资源双倍，关卡1ID，关卡2ID，…
	if (m_map->m_LAMgr.DoLATypeMapCount(unMapID,LA_TYPE_4,count))
	{
		count = 2;
		m_reward.unCoin *=count;
// 		m_reward.unMoney *=count;
// 		m_reward.unExp *=count;
// 		m_reward.unPowerPoint *=count;
// 		m_reward.unHonour *=count;
// 		m_reward.unRecharge *=count;
// 		m_reward.unEnergy *=count;
// 		m_reward.unPVPEnergy *=count;
// 		m_reward.unFriendship *=count;
// 		for (int i=0;i<m_reward.unCount;i++)
// 			m_reward.list[i].unCount *= count;
	}
	//-----------------------------------end

	m_info.unItemCount = m_reward.unCount;

	//init_stage_data(false);

	//update 2 db
	update_map_info_2_db();

	//update_battle_info_2_db();

	return 0;
}

int MapInfoMgr::get_reward(ACE_UINT32 unMapIDT, ACE_UINT32 unCurrentTime, ACE_UINT32 unBellCount, ACE_UINT32 unLaunchCount,ACE_INT32 maxExp)
{
	ACE_UINT32 unMapID= _unMapID;
	ACE_UINT32 unsMapID = _unsMapID;
	if (unsMapID == 0x0FD00101)
	{
		unMapID = unsMapID;
	}

	m_unReward3Star = 0;
	if(unMapID == 0 /*|| m_info.unMapID != unMapID*/)
	{
		return -1;
	}

	MapRes *res = (MapRes *)ITEM_RES_MGR_INSTANCE::instance()->get_item_res(unMapID);

	if(res == NULL)
	{
		return -1;
	}

	/*

	if(!BattleMgr::verify(unMapID, battleData, battleDataSize, unLaunchCount, unBellCount, m_map->m_teamMgr.m_memberList, m_map->m_teamMgr.m_unMemberCount, &m_info.friendInfo))
	{
		return -1;
	}
	*/
	/*
	if(m_battleInfo.isValid == 0 ||  m_battleInfo.nCurrentSection != (m_nSectionCount - 1) || !can_end_section())
	{
		printf("verify battle failed\n");
		return -1;
	}

	ACE_UINT32 unLaunchCount = m_battleInfo.nLauchCount;
	ACE_UINT32 unBellCount = m_battleInfo.nBellCount;
	*/

	if(res->m_unBellAmount < unBellCount)
	{
		return -1;
	}

	//printf("battle done, launch count = %d, bell count = %d\n", unLaunchCount, unBellCount);

	int star = 1;

	if(res->m_unLaunchCount >= unLaunchCount)
	{
		star = star | 0x02;
	}
	/*
	if(unBellCount > res->m_unBellAmount)
	{
		unBellCount = 0;
	}
	*/

	if(res->m_unBellCount <= unBellCount)
	{
		star = star | 0x04;
	}

	//ACE_UINT32 t = (unMapID / 10) * 10;
	//int level = unMapID % 10;
	ACE_UINT32 t = GET_ITEM_MASK_ID(unMapID, 1);
	int level = GET_ITEM_ID_INFO(unMapID, 0, 1);

	MapFlagInfo *flagInfo = get_map_flag_info(t);

	/*
	if(flagInfo == NULL)
	{
		return -1;
	}
	*/

	int i;

	bool dirty = false;

	//for(i = 0;i < res->m_unUnlockCount;i ++)
	//{
	//	if(unlock_map(res->m_unlockList[i]) == 0)
	//	{
	//		dirty = true;
	//	}
	//}

	if(flagInfo != NULL)
	{
		int old_star = GameUtils::get_map_star(flagInfo->unFlag, level);

		int star_count = 0, tmp = star;
		for(i = 0;i < 3;i ++)
		{
			if((tmp & 0x1) != 0)
			{
				star_count ++;
			}
			tmp = tmp >> 1;
		}
		star = (old_star | star) & 0x07;

		if(old_star != star)
		{
			add_star(unMapID, star, old_star);

			flagInfo->unFlag = GameUtils::set_map_star(flagInfo->unFlag, star, level);

			if(star == 0x07) //首次三星
			{
				//m_reward.unMoney += res->m_unBonusMoney;
				m_reward.unMoney += res->m_bonusReward.unMoney;
				m_unReward3Star = res->m_bonusReward.unMoney;
			}

			dirty = true;
		}
		if(star_count != 0)
		{
			update_star_count_2_db(star_count);
		}
		int iDuplicationType = GET_ITEM_ID_INFO(unMapID, 2, 4);
		switch (iDuplicationType)
		{
		case 0xB101:
		case 0xB201:
		case 0xB301:
		case 0xB401:
		case 0xB501:
		case 0xB601:
		case 0xB701: 
			{
				SetJinYingMapCount(0x0FB10101,m_map->m_unMultEnergy);
				SetJinYingMapCount(0x0FB20101,m_map->m_unMultEnergy);
				SetJinYingMapCount(0x0FB30101,m_map->m_unMultEnergy);
				SetJinYingMapCount(0x0FB40101,m_map->m_unMultEnergy);
				SetJinYingMapCount(0x0FB50101,m_map->m_unMultEnergy);
				SetJinYingMapCount(0x0FB60101,m_map->m_unMultEnergy);
				SetJinYingMapCount(0x0FB70101,m_map->m_unMultEnergy);
			}break;
// 		case 0xA001:
// 		case 0xA002:
// 		case 0xA003:
// 		case 0xA004:
// 		case 0xA005:
// 			{
// 				flagInfo->unFlag = GameUtils::set_map_enter_count(flagInfo->unFlag, GameUtils::get_map_enter_count(flagInfo->unFlag, level) + 1, level);//多倍体力
// 				break;
// 			}
		default:
			{
				flagInfo->unFlag = GameUtils::set_map_enter_count(flagInfo->unFlag, GameUtils::get_map_enter_count(flagInfo->unFlag, 1) + m_map->m_unMultEnergy, 1);//多倍体力
				flagInfo->unFlag = GameUtils::set_map_enter_count(flagInfo->unFlag, GameUtils::get_map_enter_count(flagInfo->unFlag, 3) + m_map->m_unMultEnergy, 3);//多倍体力
				flagInfo->unFlag = GameUtils::set_map_enter_count(flagInfo->unFlag, GameUtils::get_map_enter_count(flagInfo->unFlag, 5) + m_map->m_unMultEnergy, 5);//多倍体力
			}break;
		}

		dirty = true;
	}

	//双倍掉落取消
	if (m_map->m_unLevel >= 10 && m_unDoubleVersion == GAME_CONFIG_INSTANCE::instance()->m_unRefreshDoubleDropVersion && m_info.nGlobalMapEventType != GLOBAL_MAP_EVENT_NONE)
	{
		int iRawMapID = (t & 0xFFFFFFF0);
		if(isSpecialMap)
		{
			ACE_UINT32 t1 = GET_ITEM_MASK_ID(_unMapID, 1);
			iRawMapID = (t1 & 0xFFFFFFF0);
			m_info.nGlobalMapEventType = GLOBAL_MAP_EVENT_NONE;
		}

		std::map<UINT32, ACE_Byte> &refMapDoubleDrop = GAME_CONFIG_INSTANCE::instance()->m_vecDoubleDropMap[GAME_CONFIG_INSTANCE::instance()->m_unRefreshDoubleDropVersion];
		std::map<UINT32, ACE_Byte>::iterator itMap = refMapDoubleDrop.find(iRawMapID);
		if (itMap != refMapDoubleDrop.end())
		{
			m_setUsedDouble.insert(iRawMapID);
			update_double_drop_db();
		}
	}

	isSpecialMap = false;
	


	int tmp_coin = res->m_unBellCoin;

	//PropertyComponent *own_property = m_map->m_teamMgr.get_property_by_id(0, PROPERTY_ID_INCREASE_COIN);
	//PropertyComponent friend_property = &m_info.friendInfo.propertyList[PLAYER_PROPERTY_COIN];
	PropertyComponent friend_property = TeamProperty::get_coin_property(&m_info.friendInfo.pveTeam);
	PropertyComponent own_property = TeamProperty::get_coin_property(&m_map->m_playerMgr.m_teamInfo);

	tmp_coin = (int)((tmp_coin + own_property.unValue + friend_property.unValue) * ((1000 + (m_info.nGlobalMapEventType == GLOBAL_MAP_EVENT_COIN_DOUBLE ? 1000 : 0)) / 1000));

	if(tmp_coin < 0)
	{
		tmp_coin = 0;
	}
	m_rewardTemp.unCoin += (unBellCount * tmp_coin);
	m_reward.unCoin += (unBellCount * tmp_coin);

	if(GameUtils::get_day_different(unCurrentTime, m_unLastRewardTime) != 0)
	{
		m_reward.unCoin = m_map->m_benefitMgr.get_benefit(BENEFIT_TYPE_MAP_REWARD, (float)m_reward.unCoin);
		if (maxExp >= 0){
			m_reward.unExp = maxExp;  //升到最高等级所需的exp，当等级大于最高等级时，经验不增加
		}else{
			m_reward.unExp = m_map->m_benefitMgr.get_benefit(BENEFIT_TYPE_MAP_REWARD, (float)m_reward.unExp);
		}

		m_rewardTemp.unCoin = m_reward.unCoin;
		m_rewardTemp.unExp = m_reward.unExp;
	}
	if (maxExp >= 0){
		m_reward.unExp = maxExp;
		m_rewardTemp.unExp = m_reward.unExp;
	}
	m_unLastRewardTime = unCurrentTime;

	if(dirty)
	{
		//update 2 db
		update_map_flag_2_db();
	}

	m_unLastRewardTime = unCurrentTime;
	int iDuplicationType = GET_ITEM_ID_INFO(unMapID, 2, 4);
	switch (iDuplicationType)
	{
	case 0xA001:
	case 0xA002:
		{
			m_map->m_taskMgr.RefreshTask(Event_Base_Type_TreasureMountain, unMapID);
			m_map->m_dailyTaskMgr.RefreshTask(Event_Base_Type_TreasureMountain, unMapID);
		}break;
	case 0xA003:
	case 0xA004:
	case 0xA005:
		{
			m_map->m_taskMgr.RefreshTask(Event_Base_Type_Trial, unMapID);
			m_map->m_dailyTaskMgr.RefreshTask(Event_Base_Type_Trial, unMapID);
		}break;
	default:
		{
			m_map->m_taskMgr.RefreshTask(Event_Base_Type_Duplication, level,m_map->m_unMultEnergy);
			m_map->m_dailyTaskMgr.RefreshTask(Event_Base_Type_Duplication, level,m_map->m_unMultEnergy);
		}break;
	}
	m_map->m_taskMgr.RefreshTask(Event_Base_Type_SpecificDuplication, unMapID);
	//m_map->m_taskMgr.RefreshTaskEx(Event_Base_Type_SpecificDuplication, unMapID);
	m_map->m_dailyTaskMgr.RefreshTask(Event_Base_Type_SpecificDuplication, unMapID);
	std::map<ACE_UINT32, ACE_UINT32> &unlockMap = GAME_CONFIG_INSTANCE::instance()->m_oUnlockPrefixMapID;
	std::map<ACE_UINT32, ACE_UINT32>::iterator itMap = unlockMap.begin();
	for (;itMap != unlockMap.end();++itMap)
	{
		this->unlock_map(itMap->first); //先这样吧
	}
	
	return 0;
}

void MapInfoMgr::add_star(ACE_UINT32 unMapID, int star, int old_star)
{
	int idx = GET_ITEM_ID_INFO(unMapID, 4, 2) - 1;

	int c0 = 0, c1 = 0;
	for(int i = 0;i < 3;i ++)
	{
		if((star & 0x1) != 0)
		{
			c0 ++;
		}
		if((old_star & 0x1) != 0)
		{
			c1 ++;
		}
		star = star >> 1;
		old_star = old_star >> 1;
	}

	m_starCountList[idx] += (c0 - c1);

	//-----------log 日志
	//管卡进度
	LogItemInfo logInfo;
	logInfo.m_goodsID = unMapID;//关卡id
	logInfo.m_op_action = enum_LOG_ACTION::LOG_ACTION_map_start;//动作原因
	logInfo.SetOp_Way(_LOG_OP_WAY_map_start);//途径(附加信息)
	m_map->SetlogUserInfo(logInfo);
	
	//log日志文件
	logInfo.m_unType = enum_LOG_TYPE::LOG_TYPE_map_start_add;
	logInfo.m_op_before = m_starCountList[idx] - (c0 - c1);
	logInfo.m_op_after = m_starCountList[idx];
	std::vector<LogItemInfo> logver;
	logver.push_back(logInfo);
	m_map->SendLogInfoItemMSG(logver);//log 日志
	//-------------------------------------------
}

void MapInfoMgr::clear_map()
{
	//m_info.unMapID = 0;
	//m_info.unSpecialBossID = 0;
	ACE_OS::memset(&m_info, 0, sizeof(MapInstanceInfo));
	GameUtils::reset_reward(m_reward);

	//update 2 db
	update_map_info_2_db();
}

int MapInfoMgr::unlock_map(ACE_UINT32 unMapID)
{
	//ACE_UINT32 t = (unMapID / 10) * 10;
	//int level = unMapID % 10;
	ACE_UINT32 t = GET_ITEM_MASK_ID(unMapID, 1);
	int level = GET_ITEM_ID_INFO(unMapID, 0, 1);

	MapFlagInfo *flagInfo = get_map_flag_info(t);

	if(flagInfo == NULL)
	{
		return ERROR_MSG_RES;
	}

	int f = GameUtils::get_map_unlock_flag(flagInfo->unFlag,level);

	if(f != 0)
	{
		/*printf("already unlocked %d[%d]\n", unMapID, level);*/
		return 0;
	}
	else
	{
		MapGroupRes *resGroup = (MapGroupRes *)ITEM_RES_MGR_INSTANCE::instance()->get_item_res(MapGroupRes::g_map_to_mapGroup[unMapID]);
		if (resGroup)//地图解锁，关联战队等级
		{
			if (resGroup->m_level_require > m_map->m_unLevel)
			{
				return ERROR_MSG_MAP_UNLOCK;
			}
		}

		MapRes *res = (MapRes *)ITEM_RES_MGR_INSTANCE::instance()->get_item_res(unMapID);
		if (res != NULL)
		{
			int preID = 0, preUnlockFlag = 0, preStarCount = 0;
			if (res->m_UnlockCases.byLimited)
			{
			    if(res->m_UnlockCases.unLevel <= m_map->m_unLevel)  
				{
					std::map<ACE_UINT32, ACE_UINT32> &unlockMap = GAME_CONFIG_INSTANCE::instance()->m_oUnlockPrefixMapID;
					std::map<ACE_UINT32, ACE_UINT32>::iterator itMap = unlockMap.find(unMapID);
					if (itMap != unlockMap.end())
					{
						preID = itMap->second;
						ACE_UINT32 t1 = GET_ITEM_MASK_ID(itMap->second, 1);
						int level1 = GET_ITEM_ID_INFO(itMap->second, 0, 1);

						MapFlagInfo *flagInfo1 = get_map_flag_info(t1);

						if(flagInfo1 == NULL)
						{
							return ERROR_MSG_RES;
						}

						preUnlockFlag = GameUtils::get_map_unlock_flag(flagInfo1->unFlag,level1);
						preStarCount = GameUtils::get_map_star_count(flagInfo1->unFlag,level1);
						if (preUnlockFlag == 0 || preStarCount == 0)
						{
							return ERROR_MSG_MAP_UNLOCK;
						}
					}
					else
					{
						return ERROR_MSG_RES;
					}
				}
				else
				{
					return ERROR_MSG_LEVEL;
				}
			}
			flagInfo->unFlag = GameUtils::set_map_unlock_flag(flagInfo->unFlag, 1, level);
			CLogBase *pLog = BaseService::GetLogInstance();
			sprintf(pLog->m_szLogBuffer, "[%s][%d]:unlock_map mapid=%d,unlockflag=%d,level=%d, preid=%d,unlocklv=%d,preunlockflag=%d,prestarcout=%d",__FILE__, __LINE__,
				unMapID, flagInfo->unFlag, level,preID,res->m_UnlockCases.unLevel,preUnlockFlag,preStarCount);
			pLog->RecordLog(Log_Type_Info, pLog->m_szLogBuffer);
			update_map_flag_2_db();
		}
		else
		{
			return ERROR_MSG_RES;
		}
	}

	return 0;
}

void MapInfoMgr::handle_event(BaseEvent *e)
{
	if(ACE_OS::strcmp(e->m_name, GAME_EVENT_MAX_LIMIT_CHANGE) == 0)
	{
		m_unFreeRebornMax = m_map->m_benefitMgr.get_benefit(BENEFIT_TYPE_REBORN, 0);
	}
}

int MapInfoMgr::battle_reborn(ACE_UINT32 unCurrentTime)
{
	/*
	if(m_battleSnapInfo.rebornFlag == 0)
	{
		printf("reborn status invalid\n");
		return -1;
	}
	*/

	int ret = 0;
	bool reborn_dirty = false;

	int t = GameUtils::get_day_different(unCurrentTime, this->m_unLastRebornTime);

	if(t != 0)
	{
		m_unLastRebornTime = unCurrentTime;
		m_unFreeRebornCount = 0;
		reborn_dirty = true;
	}

	if(m_unFreeRebornCount < m_unFreeRebornMax)
	{
		m_unFreeRebornCount ++;
		reborn_dirty = true;
	}
	else
	{
		int t_money = GAME_CONFIG_INSTANCE::instance()->m_unRebornCost;

		if(m_map->m_unMoney >= t_money)
		{
			m_map->set_basic_info(0, -t_money, 0, 0, 0,0,0);
		}
		else
		{
			printf("reborn not enough money\n");
			ret = -1;
		}
	}

	if(reborn_dirty)
	{
		MsgDBUpdateRebornInfoRequest db_request;
		db_request.unFreeRebornCount = m_unFreeRebornCount;
		db_request.unLastRebornTime = m_unLastRebornTime;
		m_map->add_db_request(ADAPTER_DB_HOME_MGR, MSG_DB_UPDATE_REBORN_INFO, (char *)&db_request, sizeof(MsgDBUpdateRebornInfoRequest));
	}

	if(ret == -1)
	{
		return -1;
	}

	return 0;
}

void MapInfoMgr::update_map_info_2_db()
{
	MsgDBUpdateCurrentMapRequest db_request;
	db_request.info = m_info;
	db_request.reward = m_reward;
	db_request.unLastRewardTime = m_unLastRewardTime;
	m_map->add_db_request(ADAPTER_DB_HOME_MGR, MSG_DB_UPDATE_CURRENT_MAP, (char *)&db_request, sizeof(MsgDBUpdateCurrentMapRequest));
}

void MapInfoMgr::update_map_flag_2_db()
{
	MsgDBUpdateMapFlagListRequest db_request;
	ACE_OS::memcpy(db_request.flagList, m_flagList, sizeof(MapFlagInfo) * MAX_MAP_COUNT);
	ACE_OS::memcpy(db_request.giftList, m_giftList, sizeof(MapFlagInfo) * MAX_MAP_COUNT);
	m_map->add_db_request(ADAPTER_DB_HOME_MGR, MSG_DB_UPDATE_MAP_FLAG_LIST, (char *)&db_request, sizeof(MsgDBUpdateMapFlagListRequest));
}

void MapInfoMgr::update_double_drop_db()
{
	MsgDBUpdateDoubleDropInfoRequest db_request;
	std::set<ACE_UINT32>::iterator itSet = m_setUsedDouble.begin();
	int i=0;
	memset(db_request.m_usedDoubleList, 0, sizeof(ACE_UINT32) * MAX_DOUBLE_DROP_COUNT);
	for (;i<MAX_DOUBLE_DROP_COUNT && itSet!=m_setUsedDouble.end();++itSet,++i)
	{
		db_request.m_usedDoubleList[i] = *itSet;
	}
    db_request.m_unVersion = m_unDoubleVersion;
	m_map->add_db_request(ADAPTER_DB_HOME_MGR, MSG_DB_UPDATE_DOUBLE_DROP_INFO, (char *)&db_request, sizeof(MsgDBUpdateDoubleDropInfoRequest));
}

int MapInfoMgr::reset_map( ACE_UINT32 unMapID )
{
	ACE_UINT32 t = GET_ITEM_MASK_ID(unMapID, 1);
	int level = GET_ITEM_ID_INFO(unMapID, 0, 1);

	MapRes *res = (MapRes *)ITEM_RES_MGR_INSTANCE::instance()->get_item_res(unMapID);

	if(res == NULL)
	{
		return ERROR_MSG_RES;
	}

	MapFlagInfo *flagInfo = get_map_flag_info(t);
	if(NULL == flagInfo)
		return ERROR_MSG_RES;

	
	bool isSpecialMap = false;//特殊管卡
	bool isJingying = false;
	int iDuplicationType = GET_ITEM_ID_INFO(unMapID, 2, 4);
	switch (iDuplicationType)
	{
	case 0xA001:
	case 0xA002:
	case 0xA003:
	case 0xA004:
	case 0xA005:
		{
			isSpecialMap = true;
			break;
		}
	case 0xB101:
	case 0xB201:
	case 0xB301:
	case 0xB401:
	case 0xB501:
	case 0xB601:
	case 0xB701: 
		{
			isJingying = true;
		}break;
	default:
		{
			isSpecialMap = false;
		}break;
	}

	int dwResetCount = GameUtils::get_map_reset_count(flagInfo->unFlag2, level);//得到重置次数
	if (isSpecialMap)//特殊副本
	{
		if(dwResetCount >= m_map->m_vipMgr.GetResetDngeonLimit())
			return ERROR_MSG_MAX;
	}
	else if(isJingying)//精英关卡
	{
		for(int i = 0; ; i++)
		{
			MapFlagInfo *newflagInfo = get_map_flag_info(GET_ITEM_MASK_ID(0x0FB10101 + (i * 0x10000), 1));
			if(newflagInfo == NULL)
				break;
			int dwNewResetCount = GameUtils::get_map_reset_count(newflagInfo->unFlag2, 1);
			if(dwResetCount > dwNewResetCount)
				dwResetCount = dwNewResetCount;
		}
	}
	else//普通管卡
	{
		if(dwResetCount >= m_map->m_vipMgr.GetResetlevellimit())
			return ERROR_MSG_MAX;
	}


	//FormulaInfo formula = GAME_CONFIG_INSTANCE::instance()->m_vecFormulaInfo[4];//公式
	//int nMonney =formula.paramA + dwResetCount * formula.paramB;
	int nMonney = 10;

	if(m_map->m_unMoney < nMonney)
		return ERROR_MSG_COST;

	if(isSpecialMap)//特殊管卡
	{
		for(int i=0;i<3;i++)//重置
		{
			level = 2*i +1;
			flagInfo->unFlag2 = GameUtils::set_map_reset_count(flagInfo->unFlag2, dwResetCount + 1, level);
			flagInfo->unFlag = GameUtils::set_map_enter_count(flagInfo->unFlag, 0, level);
		}
// 		flagInfo->unFlag2 = GameUtils::set_map_reset_count(flagInfo->unFlag2, dwResetCount + 1, level);
// 		flagInfo->unFlag = GameUtils::set_map_enter_count(flagInfo->unFlag, 0, level);
	}
	else if(isJingying)//精英关卡
	{
		for(int i = 0; ; i++)
		{
			MapFlagInfo *newflagInfo = get_map_flag_info(GET_ITEM_MASK_ID(0x0FB10101 + (i * 0x10000), 1));
			if(newflagInfo == NULL)
				break;
			newflagInfo->unFlag2 = GameUtils::set_map_reset_count(newflagInfo->unFlag2, dwResetCount + 1, 1);
			newflagInfo->unFlag = GameUtils::set_map_enter_count(newflagInfo->unFlag, 0, 1);
		}
	}
	else//普通管卡
	{
		for(int i=0;i<3;i++)//重置
		{
			level = 2*i +1;
			flagInfo->unFlag2 = GameUtils::set_map_reset_count(flagInfo->unFlag2, dwResetCount + 1, level);
			flagInfo->unFlag = GameUtils::set_map_enter_count(flagInfo->unFlag, 0, level);
		}
	}

	//-----------log日志
	//MAP重置
	LogItemInfo logInfo;
	logInfo.m_op_action = enum_LOG_ACTION::LOG_ACTION_MAP_RESET;//动作原因
	logInfo.SetOp_Way(_LOG_OP_WAY_MAP_RESET);//途径(附加信息)
	std::vector<LogItemInfo> logInfoVer;
	m_map->SetlogUserInfo(logInfo);//写入基本信息
	logInfo.m_unType = enum_LOG_TYPE::LOG_TYPE_money_lower;
	logInfo.m_op_before = m_map->m_unMoney;
	logInfo.m_op_after = m_map->m_unMoney - nMonney;
	logInfoVer.push_back(logInfo);
	//----------------------------
	m_map->set_basic_info(0, -nMonney, 0, 0, 0,0,0);

	update_map_flag_2_db();

	m_map->SendLogInfoItemMSG(logInfoVer);

	return 0;
}

bool MapInfoMgr::check_enter(MapFlagInfo *flagInfo, int level, MapRes *res)
{
	if(flagInfo != NULL)
	{
		if (!res->m_UnlockCases.byLimited)
		{
			return true;
		}
		if (res->m_UnlockCases.unLevel > m_map->m_unLevel)
		{
			return false;
		}
		if(GameUtils::get_map_unlock_flag(flagInfo->unFlag,level) == 0)
		{
			return false;
		}

		//关卡上限双倍 检测
		ACE_UINT32 count = 1;
		if (m_map->m_LAMgr.DoLATypeMapCount(flagInfo->unMapID,LA_TYPE_2,count))
		{
			count = 2;
		}
		else
			count =1;
		//-----------------------------------end
		ACE_UINT32 unTotalCount = res->m_unTotalEnterCount * count;
		if(unTotalCount <= 0)
			return true;
		int unCount = GameUtils::get_map_enter_count(flagInfo->unFlag, level) + m_map->m_unMultEnergy;
		return unCount <= unTotalCount;
// 		if(GameUtils::check_enter_map_count(flagInfo->unFlag, level, res->m_unTotalEnterCount * count) == false)
// 		{
// 			return false;
// 		}
// 		return true;
	}
	return false;
}

void MapInfoMgr::update_star_count_2_db(int dwStarAdded)
{
	MsgUpdateStarCount request;
	request.m_dwCharacterID = m_map->m_unID;
	request.m_dwStarAdded = dwStarAdded;
	m_map->sendMsg(SERVICE_MESSAGE_TYPE_USER, MSG_UPDATE_STAR_COUNT_REQUEST, (char *)&request, sizeof(request), m_map->m_unUserInfoServerID, ADAPTER_USER_INFO_MGR, OBJ_ID_NONE);
}

void MapInfoMgr::Reset_map_day_different_count()
{
	int tmpCount = GLOBAL_INFO_MGR_INSTANCE::instance()->m_unMapCount;
	ACE_UINT32 unMapID = 0;
	for(int i = 0;i < tmpCount;i ++)
	{
		unMapID = GLOBAL_INFO_MGR_INSTANCE::instance()->m_mapList[i];
		ACE_UINT32 t = GET_ITEM_MASK_ID(unMapID, 1);
		int level = GET_ITEM_ID_INFO(unMapID, 0, 1);

		MapFlagInfo *flagInfo = get_map_flag_info(t);

		if (flagInfo)
		{
			flagInfo->unFlag = GameUtils::set_map_enter_count(flagInfo->unFlag, 0, level);
			flagInfo->unFlag2 = GameUtils::set_map_reset_count(flagInfo->unFlag2, 0,level);
		}

	}
	update_map_flag_2_db();
}

int MapInfoMgr::get_map_star( ACE_UINT32 unMapID )
{
	int star = 0;
	ACE_UINT32 t = GET_ITEM_MASK_ID(unMapID, 1);
	int level = GET_ITEM_ID_INFO(unMapID, 0, 1);

	MapFlagInfo *flagInfo = get_map_flag_info(t);
	if (flagInfo)
	{
		star = GameUtils::get_map_star(flagInfo->unFlag, level);
	}

	return star;
}

void MapInfoMgr::SetJinYingMapCount( ACE_UINT32 unMapID,ACE_UINT32 unCount )
{
	ACE_UINT32 t = GET_ITEM_MASK_ID(unMapID, 1);
	//int level = GET_ITEM_ID_INFO(unMapID, 0, 1);
	MapFlagInfo *flagInfo = get_map_flag_info(t);
	if (flagInfo)
	{
		flagInfo->unFlag = GameUtils::set_map_enter_count(flagInfo->unFlag, GameUtils::get_map_enter_count(flagInfo->unFlag, 1) + unCount, 1);//多倍体力
		//flagInfo->unFlag = GameUtils::set_map_enter_count(flagInfo->unFlag, GameUtils::get_map_enter_count(flagInfo->unFlag, 3) + unCount, 3);//多倍体力普通
		//flagInfo->unFlag = GameUtils::set_map_enter_count(flagInfo->unFlag, GameUtils::get_map_enter_count(flagInfo->unFlag, 5) + unCount, 5);//多倍体力困难
	}
}
