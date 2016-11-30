#include "MoneyTreeMgr.h"
#include "..\..\GameBase\res\GameConfig.h"
#include "..\..\GameBase\Common\GameUtils.h"
#include "..\..\GameBase\res\GiftRes.h"
#include "..\..\GameBase\res\ItemResMgr.h"
#include "..\Map.h"
#include "..\..\GameBase\Logger\LoggerClient.h"

MoneyTreeMgr::MoneyTreeMgr()
{
	
}

MoneyTreeMgr::~MoneyTreeMgr()
{

}

void MoneyTreeMgr::init(ACE_UINT32 unLevel, ACE_UINT32 unExp)
{
	m_unLevel = unLevel;
	m_unExp = unExp;
}

void MoneyTreeMgr::update(ACE_UINT32 unCurrentTime)
{
	
}

void MoneyTreeMgr::send_info(ObjAdr &targetAdr, ACE_UINT32 unSN)
{
	/*
	MsgGiftListResponse response;
	response.nResult = 0;
	response.unSN = unSN;
	response.unCount = 0;

	ACE_UINT32 unTime = GameUtils::get_utc();

	//ACE_OS::memcpy(response.giftList, m_giftList, sizeof(GiftInfo) * MAX_GIFT_COUNT);
	for(int i = 0;i < MAX_GIFT_COUNT;i ++)
	{
		response.giftList[i].unGiftID = m_giftList[i].unGiftID;
		response.giftList[i].unTimeStamp = unTime - m_giftList[i].unTimeStamp;
	}

	m_map->sendMsg(SERVICE_MESSAGE_TYPE_USER, MSG_GIFT_LIST_RESPONSE, (char *)&response, sizeof(MsgGiftListResponse), targetAdr);
	*/
	MsgMoneyTreeInfoResponse response;
	response.nResult = 0;
	response.unSN = unSN;
	response.unLevel = m_unLevel;
	response.unExp = m_unExp;

	m_map->sendMsg(SERVICE_MESSAGE_TYPE_USER, MSG_MONEY_TREE_INFO_RESPONSE, (char *)&response, sizeof(MsgMoneyTreeInfoResponse), targetAdr);
}


void MoneyTreeMgr::update_2_db()
{
	MsgDBUpdateMoneyTreeInfoRequest db_request;
	
	db_request.unLevel = m_unLevel;
	db_request.unExp = m_unExp;
	m_map->add_db_request(ADAPTER_DB_HOME_MGR, MSG_DB_UPDATE_MONEY_TREE_INFO, (char *)&db_request, sizeof(MsgDBUpdateMoneyTreeInfoRequest));
	
}

void MoneyTreeMgr::watering()
{
	MoneyTreeRes *res = get_res(m_unLevel + 1);

	if(res == NULL)
	{
		return;
	}

	m_unExp += 1;

	if(m_unExp >= res->m_unExp)
	{
		m_unLevel ++;
		m_unExp = m_unExp - res->m_unExp;
	}

	update_2_db();
	m_map->m_taskMgr.RefreshTask(Event_Base_Type_SupermanPowerStone, m_unLevel);
	m_map->m_dailyTaskMgr.RefreshTask(Event_Base_Type_SupermanPowerStone, m_unLevel);
}

void MoneyTreeMgr::get_reward(RewardInfo &reward)
{
	MoneyTreeRes *res = get_res(m_unLevel);

	if(res == NULL)
	{
		GameUtils::reset_reward(reward);
		return;
	}

	int idx = m_map->m_vipMgr.m_unVipLevel;

	m_map->get_reward_from_config_reward(reward, res->m_rewardList[idx], 1, 1);
}

MoneyTreeRes *MoneyTreeMgr::get_res(ACE_UINT32 unLevel)
{
	ACE_UINT32 unID = 0x23001000 | unLevel;

	return (MoneyTreeRes *)ITEM_RES_MGR_INSTANCE::instance()->get_item_res(unID);
}