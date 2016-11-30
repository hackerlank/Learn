#include "LootMgr.h"
#include "..\..\GameBase\res\GameConfig.h"
#include "..\..\GameBase\Common\GameUtils.h"
#include "..\..\GameBase\res\ItemResMgr.h"
#include "..\..\GameBase\res\PlayerRes.h"
#include "..\..\GameBase\res\EquipmentRes.h"
#include "..\..\GameBase\res\ImproveRes.h"
#include "..\..\GameBase\res\SkillRes.h"
#include "PlayerMgr.h"
#include "..\..\GameBase\Common\GlobalLootMgr.h"
#include "..\Map.h"

LootMgr::LootMgr()
{
	//m_unCount = 0;
}

LootMgr::~LootMgr()
{

}

void LootMgr::handle_event(BaseEvent *e)
{
	/*
	int i;

	m_unCount = 0;

	for(i = 0;i < m_map->m_playerMgr.m_unPlayerCount;i ++)
	{
		m_ignoreList[m_unCount] = m_map->m_playerMgr.m_list[i].unItemID;
		m_unCount ++;
	}
	*/
}

ACE_UINT32 LootMgr::loot(DropGroup &group, int nCount)
{
	ACE_UINT32 unRet = GLOBAL_LOOT_MGR_INSTANCE::instance()->loot(group, nCount);

	//judge ignore
	/*
	int i;

	for(i = 0;i < m_unCount;i ++)
	{
		if(m_ignoreList[i] == unRet)
		{
			RewardInfo reward;

			m_map->get_reward_from_config_reward(reward, GAME_CONFIG_INSTANCE::instance()->m_lootReplaceReward, 1, nCount);

			if(reward.unCount > 0)
			{
				unRet = reward.list[0].item.unResID;
			}
			else
			{
				unRet = 0;
			}
			break;
		}
	}
	*/

	return unRet;
}