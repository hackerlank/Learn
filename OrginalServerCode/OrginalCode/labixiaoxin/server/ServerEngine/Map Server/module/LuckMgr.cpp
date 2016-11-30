#include "LuckMgr.h"
#include "..\..\GameBase\res\GameConfig.h"
#include "..\..\GameBase\Common\GameUtils.h"
#include "..\..\GameBase\res\ItemResMgr.h"
#include "LootMgr.h"
#include "..\Map.h"

LuckMgr::LuckMgr()
{
	m_unCount = 0;
}

LuckMgr::~LuckMgr()
{

}

void LuckMgr::init()
{
	ACE_UINT32 tmp[MAX_LUCK_COUNT];

	int c = ITEM_RES_MGR_INSTANCE::instance()->get_item_id_list_by_type(ITEM_RES_TYPE_LUCK, 0, 0, 0, tmp, 0);

	LuckRes *res;
	m_unCount = 0;
	for(int i = 0;i < c;i ++)
	{
		res = (LuckRes *)ITEM_RES_MGR_INSTANCE::instance()->get_item_res(tmp[i]);
		if(res == NULL)
		{
			continue;
		}

		int j;

		for(j = 0;j < m_unCount;j ++)
		{
			if(m_luckList[j]->m_unLevel > res->m_unLevel)
			{
				for(int m = m_unCount;m > j;m --)
				{
					m_luckList[m] = m_luckList[m - 1];
				}
				
				break;
			}
		}

		m_luckList[j] = res;

		m_unCount ++;
	}
}

ConfigReward *LuckMgr::get_config_reward(ACE_UINT32 unLevel)
{
	int i;

	for(i = 0;i < m_unCount;i ++)
	{
		if(m_luckList[i]->m_unLevel > unLevel)
		{
			break;
		}
	}
	if(i >= m_unCount)
	{
		i = m_unCount - 1;
	}

	return &m_luckList[i]->m_reward;

	/*
	RewardInfo reward;

	map->get_reward_from_config_reward(reward, m_luckList[i]->m_reward, 1, nCount);

	if(reward.unCount > 0)
	{
		return reward.list[0].item.unResID;
	}

	return 0;
	*/
}

/*
ACE_UINT32 LuckMgr::get_luck(ACE_UINT32 unLevel, Map *map, int nCount)
{
	int i;

	for(i = 0;i < m_unCount;i ++)
	{
		if(m_luckList[i]->m_unLevel > unLevel)
		{
			break;
		}
	}
	if(i >= m_unCount)
	{
		i = m_unCount - 1;
	}

	RewardInfo reward;

	map->get_reward_from_config_reward(reward, m_luckList[i]->m_reward, 1, nCount);

	if(reward.unCount > 0)
	{
		return reward.list[0].item.unResID;
	}

	return 0;

	//return map->m_lootMgr.loot(m_luckList[i]->m_drop, nCount);

	//return GLOBAL_LOOT_MGR_INSTANCE::instance()->loot(m_luckList[i]->m_drop);

	//return GameUtils::get_drop(m_luckList[i]->m_drop);
}
*/