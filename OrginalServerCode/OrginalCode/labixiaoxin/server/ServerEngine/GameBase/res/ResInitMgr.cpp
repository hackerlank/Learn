#include "ResInitMgr.h"
#include "ItemResMgr.h"

CooldownInstanceInfo initCooldownList[MAX_COOLDOWN_INFO];

void init_cooldown_list(ResInitInfo *info)
{
	CooldownInstanceInfo *p = (CooldownInstanceInfo *)info->data;

	ACE_OS::memset(p, 0, sizeof(CooldownInstanceInfo) * MAX_COOLDOWN_INFO);

	ACE_UINT32 list[320];

	int j;
	int type;
	int count = 0;
	for(j = 0;j < 2;j ++)
	{
		if(j == 0)
		{
			type = ITEM_RES_TYPE_MAP;
		}
		else
		{
			type = ITEM_RES_TYPE_BEHAVIOR;
		}

		int c = ITEM_RES_MGR_INSTANCE::instance()->get_item_id_list_by_type(type, 0, 0, 0, list, 0);
		for(int i = 0;i < c;i ++)
		{
			//initCooldownList[idx].unItemID = ;
			BaseRes *res = ITEM_RES_MGR_INSTANCE::instance()->get_item_res(list[i]);

			if(res == NULL)
			{
				continue;
			}

			if(res->m_cdInfo.unCD == 0)
			{
				continue;
			}

			int t = count;
			int k = 0;

			for(k = 0;k < count;k ++)
			{
				if(list[i] < p[k].unItemID)
				{
					break;
				}
			}

			for(int m = count;m > k;m --)
			{
				p[m].unItemID = p[m - 1].unItemID;
			}

			p[k].unItemID = list[i];

			count ++;
		}
	}

	info->unCount = MAX_COOLDOWN_INFO;
	info->size = info->unCount * sizeof(CooldownInstanceInfo);
}

ResInitMgr::ResInitMgr()
{
	m_list[RES_INIT_COOLDOWN].isInited = false;
	m_list[RES_INIT_COOLDOWN].unCount = 0;
	m_list[RES_INIT_COOLDOWN].data = initCooldownList;
	m_list[RES_INIT_COOLDOWN].func = init_cooldown_list;
}

ResInitMgr::~ResInitMgr()
{
	
}

ResInitInfo *ResInitMgr::get_inited_res(int type)
{
	if(!m_list[type].isInited)
	{
		m_list[type].isInited = true;
		
		(*m_list[type].func)(&m_list[type]);
	}

	return &m_list[type];
}




