#include "UnlockMgr.h"
#include "..\..\GameBase\res\GameConfig.h"
#include "..\..\GameBase\Common\GameUtils.h"
#include "..\..\GameBase\res\UnlockRes.h"
#include "..\..\GameBase\res\DropRes.h"
#include "..\..\GameBase\res\ItemResMgr.h"
#include "..\Map.h"

static bool gIsUnlockDataInited = false;
static int gUnlockDataCountList[UNLOCK_CONDITION_TYPE_MAX];
static UnlockRes *gUnlockDataList[UNLOCK_CONDITION_TYPE_MAX][64];


UnlockMgr::UnlockMgr()
{
	
}

UnlockMgr::~UnlockMgr()
{

}

void UnlockMgr::init()
{
	
}

void UnlockMgr::update(ACE_UINT32 unCurrentTime)
{
	
}

void UnlockMgr::update_2_db()
{
}

void UnlockMgr::handle_event(BaseEvent *e)
{
	init_unlock_data();

	if(ACE_OS::strcmp(e->m_name, GAME_EVENT_LEVEL_UP) == 0)
	{
		int i;
		int lv = m_map->m_unLevel;
		UnlockRes *res = NULL;
		for(i = 0;i < gUnlockDataCountList[UNLOCK_CONDITION_TYPE_LEVEL_UP];i ++)
		{
			if(lv == gUnlockDataList[UNLOCK_CONDITION_TYPE_LEVEL_UP][i]->m_require.unValue)
			{
				res = gUnlockDataList[UNLOCK_CONDITION_TYPE_LEVEL_UP][i];
				break;
			}
		}

		if(res != NULL)
		{
			MsgUnlockRewardResponse response;
			response.unSN = 0;
			response.nResult = 0;

			m_map->get_reward_from_config_reward(response.reward, res->m_reward, 1, 1);
			
			//-----------log 日志
			//获取解锁奖励
			LogItemInfo logInfo;
			logInfo.m_goodsID = res->m_unResID;//map id
			logInfo.m_op_action = enum_LOG_ACTION::LOG_ACTION_Unlock;//动作原因
			logInfo.SetOp_Way(_LOG_OP_WAY_Unlock);//途径(附加信息)
			m_map->get_reward(response.reward,logInfo);
			m_map->send_msg_2_client(SERVICE_MESSAGE_TYPE_USER, MSG_UNLOCK_REWARD_RESPONSE, (char *)&response, sizeof(MsgUnlockRewardResponse));
		}
	}
	else if(ACE_OS::strcmp(e->m_name, GAME_EVENT_VIP_LEVEL_UP) == 0)
	{
		int i;
		int lv = m_map->m_vipMgr.m_unVipLevel;
		UnlockRes *res = NULL;
		for(i = 0;i < gUnlockDataCountList[UNLOCK_CONDITION_TYPE_VIP_UP];i ++)
		{
			if(lv == gUnlockDataList[UNLOCK_CONDITION_TYPE_VIP_UP][i]->m_require.unValue)
			{
				res = gUnlockDataList[UNLOCK_CONDITION_TYPE_VIP_UP][i];
				break;
			}
		}

		if(res != NULL)
		{
			MsgUnlockRewardResponse response;
			response.unSN = 0;
			response.nResult = 0;

			//RewardInfo reward;

			m_map->get_reward_from_config_reward(response.reward, res->m_reward, 1, 1);
			//-----------log 日志
			//获取pvp奖励
			LogItemInfo logInfo;
			logInfo.m_goodsID = res->m_unResID;//map id
			logInfo.m_op_action = enum_LOG_ACTION::LOG_ACTION_vip_up;//动作原因
			logInfo.SetOp_Way(_LOG_OP_WAY_vip_up);//途径(附加信息)
			m_map->get_reward(response.reward,logInfo);

			m_map->send_msg_2_client(SERVICE_MESSAGE_TYPE_USER, MSG_UNLOCK_REWARD_RESPONSE, (char *)&response, sizeof(MsgUnlockRewardResponse));
		}
	}
}

void UnlockMgr::init_unlock_data()
{
	if(gIsUnlockDataInited)
	{
		return;
	}

	gIsUnlockDataInited = true;

	ACE_UINT32 list[64];
	int c = ITEM_RES_MGR_INSTANCE::instance()->get_item_id_list_by_type(ITEM_RES_TYPE_UNLOCK, 0, 0, 0, list, 0);

	UnlockRes *res;
	int j = 0;

	int i;

	for(i = 0;i < UNLOCK_CONDITION_TYPE_MAX;i ++)
	{
		gUnlockDataCountList[i] = 0;
	}

	for(i = 0;i < c;i ++)
	{
		res = (UnlockRes *)ITEM_RES_MGR_INSTANCE::instance()->get_item_res(list[i]);

		if(res == NULL)
		{
			continue;
		}

		int type = res->m_require.unType;

		int m;

		int idx = gUnlockDataCountList[type];
		for(m = 0;m < gUnlockDataCountList[type];m ++)
		{
			if(gUnlockDataList[type][m]->m_require.unValue > res->m_require.unValue)
			{
				idx = m;
				break;
			}
		}
		
		for(m = gUnlockDataCountList[type];m > idx;m --)
		{
			gUnlockDataList[type][m] = gUnlockDataList[type][m - 1];
		}

		gUnlockDataList[type][idx] = res;

		gUnlockDataCountList[type] ++;
	}

	
}