#include "GlobalLootMgr.h"
#include "..\..\GameBase\res\GameConfig.h"
#include "..\..\GameBase\Common\GameUtils.h"
#include "..\..\GameBase\res\ItemResMgr.h"
#include "..\Logger\LoggerClient.h"

#if _MEMORY_DEBUG
#include "../../GameBase/Common/debugnew.h"
#define new new(__FILE__, __LINE__)
#endif

GlobalLootMgr::GlobalLootMgr()
{
	m_unCurrentID = 1;
}

GlobalLootMgr::~GlobalLootMgr()
{

}

ACE_UINT32 GlobalLootMgr::create_global_drop(float rate, ACE_UINT32 unCount, DropEntityInfo *list)
{
	if(unCount <= 0)
	{
		return 0;
	}

	int t = (int)(rate * 1000);

	if(t <= 0)
	{
		return 0;
	}
	if(t > 1000)
	{
		t = 1000;
	}

	GlobalLootInfo *info = new GlobalLootInfo();

	if(info == NULL)
	{
		return 0;
	}

	ACE_OS::memset(info, 0, sizeof(GlobalLootInfo));

	ACE_UINT32 ret = m_unCurrentID;

	if(m_lootMap.bind(ret, info) != 0)
	{
		delete info;
		return 0;
	}

	info->nHitCount = t;

	info->dropGroup.unCount = unCount;

	for(ACE_UINT32 i = 0;i < unCount;i ++)
	{
		info->dropGroup.list[i] = list[i];
	}

	reset(info);

	m_unCurrentID ++;

	return ret;
	
}

/*
void GlobalLootMgr::init()
{
	ACE_UINT32 tmp_list[512];

	int c = ITEM_RES_MGR_INSTANCE::instance()->get_item_id_list_by_type(ITEM_RES_TYPE_DROP, 0, 0, 0, tmp_list, 0);

	DropRes *res;

	GlobalLootInfo *info = NULL;

	for(int i = 0;i < c;i ++)
	{
		res = (DropRes *)ITEM_RES_MGR_INSTANCE::instance()->get_item_res(tmp_list[i]);
		if(res == NULL)
		{
			continue;
		}

		if(res->m_unDropType == DROP_LOCAL_TYPE)
		{
			continue;
		}

		int t = (int)(res->m_fRate * 1000);

		if(t <= 0)
		{
			continue;
		}
		if(t > 1000)
		{
			t = 1000;
		}

		info = new GlobalLootInfo();
		if(info == NULL)
		{
			continue;
		}

		info->nHitCount = t;

		if(m_lootMap.bind(tmp_list[i], info) != 0)
		{
			delete info;
			continue;
		}

		reset(info);
	}
}

*/

void GlobalLootMgr::reset(GlobalLootInfo *info)
{
	ACE_OS::memset(info->lootFlag, 0, sizeof(int) * 125);
	info->nCursor = 0;

	int c = 1000;
	int pos = 0;
	//int t;
	int tmp_c = info->nHitCount;

	if(info->nHitCount > 0)
	{
		int count = 1000 / tmp_c;

		int i = 0;
		for(i = 0;i < tmp_c;i ++)
		{
			pos = i * count + ACE_OS::rand() % count;

			int idx = pos >> 3;
			int shift = pos & 0x7;

			info->lootFlag[idx] = info->lootFlag[idx] | (1 << shift);
		}
	}
}

bool GlobalLootMgr::global_loot(GlobalLootInfo *lootInfo)
{
	/*
	GlobalLootInfo *info = NULL;

	if(m_lootMap.find(unID, info) != 0)
	{
		return false;
	}
	*/

	bool ret = false;

	//int idx = info->nCursor / 8;
	//int shift = info->nCursor % 8;

	int idx = lootInfo->nCursor >> 3;
	int shift = lootInfo->nCursor & 0x7;

	if(((lootInfo->lootFlag[idx] >> shift) & 0x01) != 0)
	{
		ret = true;
	}

	lootInfo->nCursor ++;

	if(lootInfo->nCursor >= 1000)
	{
		reset(lootInfo);
	}

	return ret;
}

ACE_UINT32 GlobalLootMgr::loot(DropGroup &group, int nCount)
{
	//int i;
	int c = nCount;

	GlobalLootInfo *lootInfo = NULL;

	if(group.unGlobalDropID != 0)
	{
		if(m_lootMap.find(group.unGlobalDropID, lootInfo) == 0)
		{
			c = nCount;
			while(c > 0)
			{
				if(global_loot(lootInfo))
				{
					return get_drop(lootInfo->dropGroup);
					/*
					DropRes *res = (DropRes *)ITEM_RES_MGR_INSTANCE::instance()->get_item_res(group.globalDropList[i]);
					if(res != NULL)
					{
						return GameUtils::get_drop(res->m_dropGroup);
					}
					*/
				}
				c --;
			}
		}
	}

	/*
	for(i = 0;i < group.unGlobalCount;i ++)
	{
		c = nCount;
		while(c > 0)
		{
			if(global_loot(group.globalDropList[i]))
			{
				DropRes *res = (DropRes *)ITEM_RES_MGR_INSTANCE::instance()->get_item_res(group.globalDropList[i]);
				if(res != NULL)
				{
					return GameUtils::get_drop(res->m_dropGroup);
				}
			}
			c --;
		}
	}
	*/

	return get_drop(group);
}

ACE_UINT32 GlobalLootMgr::get_drop(DropGroup &group)
{
	ACE_UINT32 ret = 0;

	ACE_UINT32 t = ACE_OS::rand() % 1000;
	ACE_UINT32 c = 0;

	for(ACE_UINT32 i = 0;i < group.unCount;i ++)
	{
		c += (int)(group.list[i].fRate * 1000);

		if(t < c)
		{
			ret = group.list[i].unResID;
			break;
		}
	}

	if(ret == 0)
	{
		if(group.unCount > 0)
		{
			ret = group.list[group.unCount - 1].unResID;
		}
		else
		{
			//printf("roll: drop group is empty!\n");
			return 0;
		}

		//return 0;
	}

	int type = GET_ITEM_TYPE(ret);

	if(type == ITEM_RES_TYPE_DROP)
	{
		DropRes *res = (DropRes *)ITEM_RES_MGR_INSTANCE::instance()->get_item_res(ret);
		if(res == NULL)
		{
			//printf("roll: [ID=0x%08x] is not exist!\n", ret);
			return 0;
		}
		ret = get_drop(res->m_dropGroup);
	}
	//printf("roll: get [ID=0x%08x]\n", ret);
	return ret;
}