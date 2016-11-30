#include "VipMgr.h"
#include "..\..\GameBase\res\GameConfig.h"
#include "..\..\GameBase\Common\GameUtils.h"

#include "..\..\GameBase\res\ItemResMgr.h"
#include "..\Map.h"

#include "BroadcastMgr.h"

bool VipMgr::m_bInitData = false;
// static ACE_UINT32 gVipLevelCount = 0;
// static VipRes *gVipResList[MAX_VIP_LEVEL];

VipMgr::VipMgr()
{
	m_unVipLevel = 0;
	m_currentVipRes = NULL;
	m_vipRes =NULL;
}

VipMgr::~VipMgr()
{

}

void VipMgr::init(ACE_UINT32 unRechargeCount, ACE_UINT32 unRechargeAmount,const VipInfo & vipInfo,const VipGift & vipGift)
{
	m_unRechargeCount = unRechargeCount;
	m_unRechargeAmount = unRechargeAmount;
	m_vipInfo = vipInfo;
	m_vipGift = vipGift;
	UpdateVipRes(false);

	m_unVipLevel = 0;
	m_currentVipRes = NULL;

	//change by xxj 2015/07/08  11: 43:37 
	//set_vip_level(true);
}

void VipMgr::update(ACE_UINT32 unCurrentTime)
{
	
}

void VipMgr::update_2_db()
{
	MsgDBUpdateRechargeInfoRequest db_request;
	db_request.unRechargeCount = m_unRechargeCount;
	db_request.unRechargeAmount = m_unRechargeAmount;

	m_map->add_db_request(ADAPTER_DB_HOME_MGR, MSG_DB_UPDATE_RECHARGE_INFO, (char *)&db_request, sizeof(MsgDBUpdateRechargeInfoRequest));
}

void VipMgr::Update_2_Gift_db()
{
	MsgDBVipGiftInfo db_request;
	db_request.m_vipGift = m_vipGift;
	m_map->add_db_request(ADAPTER_DB_HOME_MGR, MSG_DB_UPDATE_VIP_GIFT_INFO, (char *)&db_request, sizeof(MsgDBVipGiftInfo));
}

void VipMgr::recharge(int amount, bool addCount)
{
	if(amount <= 0)
	{
		return;
	}

	m_unRechargeAmount = m_unRechargeAmount + amount;

	if(addCount)
	{
		m_unRechargeCount ++;
	}

	update_2_db();

	//set_vip_level(false);
}

/*
void VipMgr::set_vip_level(bool isInit)
{
	init_vip_data();

	//int i;
	bool dirty = false;

	while(m_unVipLevel < gVipLevelCount)
	{
		if(m_unRechargeAmount < gVipResList[m_unVipLevel]->m_unRechargeRequired)
		{
			break;
		}

		m_unVipLevel ++;
		dirty = true;

		m_currentVipRes = gVipResList[m_unVipLevel - 1];

		if(!isInit)
		{
			//dispatch msg
			m_map->dispatch_map_event(GAME_EVENT_VIP_LEVEL_UP);
		}
	}


	if(dirty)
	{
		//benefit change
		m_map->dispatch_map_event(GAME_EVENT_RESET_BENIFIT);	
	
		if(!isInit)
		{
			BROADCAST_MGR_INSTANCE::instance()->add_message(m_map->m_strName, BROADCAST_MESSAGE_TYPE_VIP, 0, m_unVipLevel);
		}
//change by xxj 2015/06/19  18: 10:06 
// 		MsgDBVipLevelUpdateRequest db_request;
// 		db_request.unVipLevel = m_unVipLevel;
// 		m_map->add_db_request(ADAPTER_DB_HOME_MGR, MSG_DB_VIP_LEVEL_UPDATE, (char *)&db_request, sizeof(MsgDBVipLevelUpdateRequest));


		MsgCharacterVipUpdateRequest request;
		request.unCharacterID = m_map->m_unID;
		request.unVipLevel = m_unVipLevel;
		m_map->sendMsg(SERVICE_MESSAGE_TYPE_USER, MSG_CHARACTER_VIP_UPDATE_REQUEST, (char *)&request, sizeof(MsgCharacterVipUpdateRequest), m_map->m_unUserInfoServerID, ADAPTER_USER_INFO_MGR, OBJ_ID_NONE);
	}
}
*/
// 
// void VipMgr::init_vip_data()
// {
// 	if(m_bInitData)
// 	{
// 		return;
// 	}
// 
// 	m_bInitData = true;
// 
// 	ACE_UINT32 list[32];
// 	int c = ITEM_RES_MGR_INSTANCE::instance()->get_item_id_list_by_type(ITEM_RES_TYPE_VIP, 0, 0, 0, list, 0);
// 
// 	VipRes *res;
// 	int j = 0;
// 
// 	gVipLevelCount = 0;
// 
// 	for(int i = 0;i < c;i ++)
// 	{
// 		res = (VipRes *)ITEM_RES_MGR_INSTANCE::instance()->get_item_res(list[i]);
// 
// 		if(res == NULL)
// 		{
// 			continue;
// 		}
// 
// 		gVipResList[res->m_unVipLevel - 1] = res;
// 
// 		j ++;
// 	}
// 
// 	gVipLevelCount = j;
// }

void VipMgr::UpdateVipRes(bool isUpdateDb)
{
	m_vipRes = NULL;
	m_vipRes = (VipRes *)ITEM_RES_MGR_INSTANCE::instance()->get_item_res(GAME_CONFIG_INSTANCE::instance()->m_vipGiftList[m_vipInfo.vip_level]);//查询是否可以升级
	if (m_vipRes)
	{
		m_map->m_packageMgr.update_PackageMax(m_vipRes->m_package_limit,isUpdateDb);
		m_map->m_friendMgr.update_FriendMax(m_vipRes->m_friends_limit,isUpdateDb);
		m_map->m_energyMgr.update_EnergyMax(m_vipRes->m_energy_limit,isUpdateDb);
		m_map->m_goldenTouchMgr.update_GoldMax(m_vipRes->m_buy_gold_limit,isUpdateDb);
		m_map->m_pvpMgr.update_TimesMax(m_vipRes->m_buy_pvp_limit,isUpdateDb);
	}
}

void VipMgr::UpdateVipRes(const VipInfo & vipInfo )
{
	m_vipInfo = vipInfo;
	UpdateVipRes(true);
}

double VipMgr::GetVipGold_profit()
{
	if (m_vipRes)
	{
		return m_vipRes->m_gold_profit * 0.01;
	}
	else
		return 0.0;
}

bool VipMgr::isEnergyCountIn( ACE_UINT32 unCount )
{
	if(m_vipRes)
		return m_vipRes->m_buyenergy_limit > unCount;
	else
		return false;
}

int VipMgr::GetResetlevellimit()
{
	if(m_vipRes)
		return m_vipRes->m_reset_level_limit;
	else
		return 0;
}

int VipMgr::GetResetDngeonLimit()
{
	if(m_vipRes)
		return m_vipRes->m_reset_dngeon_limit;
	else
		return 0;
}

bool VipMgr::HasVipGift( ACE_UINT32 ungiftId )
{
	for (int i=0;i<m_vipGift.unCount;i++)
	{
		if (m_vipGift.list[i] == ungiftId)
			return true;
	}

	return false;
}


int VipMgr::GetVipGift( ACE_UINT32 ungiftId,ACE_UINT32 unvipLevel,RewardInfo & reward )
{
	if(unvipLevel > m_vipInfo.vip_level)//等级错误
		return -1;
	
	const VipRes * pvipRes = (const VipRes *)ITEM_RES_MGR_INSTANCE::instance()->get_item_res(GAME_CONFIG_INSTANCE::instance()->m_vipGiftList[unvipLevel]);//查询是否可以升级
	if (!pvipRes)
		return -1;
	
	if (ungiftId != pvipRes->m_unGift_id)
		return -1;//gift_id 不匹配

	if (m_vipGift.unCount >= RECHARGE_MAX_PRODUCT)
		return -1;

	if (HasVipGift(ungiftId))//已经领取过了
		return -1;
	
	const BehaviorRes * pbehaviorRes = (const BehaviorRes *)ITEM_RES_MGR_INSTANCE::instance()->get_item_res(ungiftId);
	if(!pbehaviorRes)
		return -1;
	//开始获取
	ZeroVar(reward);
	//-----------log 日志
	//获取pvp奖励
	LogItemInfo logInfo;
	logInfo.m_op_action = enum_LOG_ACTION::LOG_ACTION_level_Gift;//动作原因
	logInfo.SetOp_Way(_LOG_OP_WAY_level_Gift);//途径(附加信息)
	m_map->get_reward_from_config_reward(reward, pbehaviorRes->m_reward, 1, 1);
	m_map->get_reward(reward,logInfo);

	m_vipGift.list[m_vipGift.unCount] = ungiftId;
	m_vipGift.unCount ++;

	Update_2_Gift_db();

	return 0;
}

ACE_UINT32 VipMgr::GetVipGolden_profit()
{
	if (m_vipRes)
	{
		if (m_vipRes->m_golden_profit <= 2)
			return 2;

		return (rand() % (m_vipRes->m_golden_profit-2)) + 2;
	}
	else
		return 0.0;
}
