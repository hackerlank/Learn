#include "GiftMgr.h"
#include "..\..\GameBase\res\GameConfig.h"
#include "..\..\GameBase\Common\GameUtils.h"
#include "..\..\GameBase\res\GiftRes.h"
#include "..\..\GameBase\res\ItemResMgr.h"
#include "..\Map.h"
#include "..\..\GameBase\Logger\LoggerClient.h"

GiftMgr::GiftMgr()
{
	m_unGiftCount = 0;
}

GiftMgr::~GiftMgr()
{

}

void GiftMgr::init(GiftInfo *list)
{
	ACE_OS::memcpy(m_giftList, list, sizeof(GiftInfo) * MAX_GIFT_COUNT);

	int i;

	m_unGiftCount = 0;
	for(i = 0;i < MAX_GIFT_COUNT;i ++)
	{
		if(m_giftList[i].unGiftID == 0)
		{
			break;
		}

		m_unGiftCount ++;
	}
}

void GiftMgr::update(ACE_UINT32 unCurrentTime)
{
	
}

void GiftMgr::send_info(ObjAdr &targetAdr, ACE_UINT32 unSN)
{
	MsgGiftListResponse response;
	response.nResult = 0;
	response.unSN = unSN;
	response.unCount = m_unGiftCount;

	ACE_UINT32 unTime = GameUtils::get_utc();

	//ACE_OS::memcpy(response.giftList, m_giftList, sizeof(GiftInfo) * MAX_GIFT_COUNT);
	for(int i = 0;i < MAX_GIFT_COUNT;i ++)
	{
		response.giftList[i].unGiftID = m_giftList[i].unGiftID;
		response.giftList[i].unTimeStamp = unTime - m_giftList[i].unTimeStamp;
	}

	m_map->sendMsg(SERVICE_MESSAGE_TYPE_USER, MSG_GIFT_LIST_RESPONSE, (char *)&response, sizeof(MsgGiftListResponse), targetAdr);
}

int GiftMgr::add_gift(ACE_UINT32 unID)
{
	if(m_unGiftCount < MAX_GIFT_COUNT)
	{
		m_giftList[m_unGiftCount].unGiftID = unID;
		m_giftList[m_unGiftCount].unTimeStamp = GameUtils::get_utc();

		m_unGiftCount ++;
	}
	
	update_2_db();

	return 0;
}

//使用道具，领礼包
int GiftMgr::use_gift(int idx, RewardInfo &reward)
{
	if(idx < 0 || idx >= m_unGiftCount)
	{
		return ERROR_MSG_PARAMETER;
	}

	if(m_map->m_packageMgr.is_full())
	{
		return ERROR_MSG_PKG_FULL;
	}

	GiftRes *res = (GiftRes *)ITEM_RES_MGR_INSTANCE::instance()->get_item_res(m_giftList[idx].unGiftID);

	if(res == NULL)
	{
		return ERROR_MSG_RES;
	}

	LOGGER_CLIENT_INSTANCE::instance()->log("[ID=0x%08x]use gift,giftID=0x%08x", m_map->m_unID, m_giftList[idx].unGiftID);

	if(idx < (m_unGiftCount - 1))
	{
		m_giftList[idx] = m_giftList[m_unGiftCount - 1];
	}

	m_giftList[m_unGiftCount - 1].unGiftID = 0;
	m_giftList[m_unGiftCount - 1].unTimeStamp = 0;

	m_unGiftCount --;

	//use gift
	m_map->get_reward_from_config_reward(reward, res->m_reward, 1, 1);

	//----------log日志
	//领取礼包
	LogItemInfo logInfo;
	logInfo.m_goodsID = m_giftList[idx].unGiftID;//装备id
	logInfo.m_op_action = enum_LOG_ACTION::LOG_ACTION_use_gift;//动作原因
	logInfo.SetOp_Way(_LOG_OP_WAY_use_gift);//途径(附加信息)
	m_map->get_reward(reward,logInfo);

	update_2_db();

	return 0;
}

void GiftMgr::update_2_db()
{
	MsgDBUpdateGiftListRequest db_request;
	ACE_OS::memcpy(db_request.list, m_giftList, sizeof(GiftInfo) * MAX_GIFT_COUNT);
	m_map->add_db_request(ADAPTER_DB_HOME_MGR, MSG_UPDATE_GIFT_LIST, (char *)&db_request, sizeof(MsgDBUpdateGiftListRequest));
}