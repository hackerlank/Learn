#include "ActivityMgr.h"
#include "..\..\GameBase\res\GameConfig.h"

#include "..\..\GameBase\Common\GameUtils.h"
#include "..\..\GameBase\res\ItemResMgr.h"
#include "..\Map.h"

#if _MEMORY_DEBUG
#include "../../GameBase/Common/debugnew.h"
#define new new(__FILE__, __LINE__)
#endif


ActivityMgr::ActivityMgr()
{
	m_unTimer = 1;

	m_unOnlineActivityCount = 0;
}

ActivityMgr::~ActivityMgr()
{
	ACTIVITY_ITEM_MAP_ITERATOR iter(m_itemMap);
	ActivityItemInfo *pItem;

	for(iter = m_itemMap.begin(); iter != m_itemMap.end(); iter++)
	{
		pItem = (*iter).int_id_;

		if(pItem == NULL)
		{
			continue;
		}

		delete pItem;
	}

	m_itemMap.unbind_all();
}

void ActivityMgr::init()
{
	m_unTimer = 1;

	ACE_UINT32 tmp_list[512];

	int c = ITEM_RES_MGR_INSTANCE::instance()->get_item_id_list_by_type(ITEM_RES_TYPE_ACTIVITY, 0, 0, 0, tmp_list, 0);

	ActivityRes *res;

	ACE_UINT32 unCurrentTime = GameUtils::get_utc();

	m_unOnlineActivityCount = 0;

	bool onlineFlag = false;
	bool addFlag = false;

	for(int i = 0;i < c;i ++)
	{
		res = (ActivityRes *)ITEM_RES_MGR_INSTANCE::instance()->get_item_res(tmp_list[i]);
		if(res == NULL)
		{
			continue;
		}

		if(res->m_unEndTime != 0 && res->m_unEndTime <= unCurrentTime)
		{
			onlineFlag = false;
			addFlag = false;
		}
		else
		{
			addFlag = true;
			if(res->m_unStartTime != 0 && res->m_unStartTime > unCurrentTime)
			{
				onlineFlag = false;
			}
			else
			{
				onlineFlag = true;
			}

			
		}
		
		for(int j = 0;j < res->m_unRelatedCount;j ++)
		{
			ActivityItemInfo *info = new ActivityItemInfo();

			if(info == NULL)
			{
				continue;
			}

			if(m_itemMap.bind(res->m_relatedList[j], info) != 0)
			{
				delete info;
				continue;
			}

			info->bOnline = onlineFlag;

			if(addFlag)
			{
				info->activity = &m_onlineActivityList[m_unOnlineActivityCount];
			}
			else
			{
				info->activity = NULL;
			}
		}

		if(addFlag)
		{
			m_onlineActivityList[m_unOnlineActivityCount].isStart = onlineFlag;
			m_onlineActivityList[m_unOnlineActivityCount].res = res;
			m_unOnlineActivityCount ++;
		}		
	}
}

void ActivityMgr::update(ACE_UINT32 unCurrentTime)
{
	int i;
	ActivityRes *res;

	bool flag = false;

	bool onlineFlag = false;

	for(i = 0;i < m_unOnlineActivityCount;i ++)
	{
		res = m_onlineActivityList[i].res;

		if(res->m_unEndTime != 0 && res->m_unEndTime <= unCurrentTime)
		{
			onlineFlag = false;
		}
		else if(res->m_unStartTime != 0 && res->m_unStartTime > unCurrentTime)
		{
			onlineFlag = false;
		}
		else
		{
			onlineFlag = true;
			/*
			if(!m_onlineActivityList[i].isStart)
			{
				m_onlineActivityList[i].isStart = true;
				flag = true;
			}*/
		}

		if(m_onlineActivityList[i].isStart != onlineFlag)
		{
			flag = true;
			m_onlineActivityList[i].isStart = onlineFlag;
		}
	}

	if(!flag)
	{
		return;
	}

	m_unTimer ++;

	if(m_unTimer == 0)
	{
		m_unTimer = 1;
	}
}

bool ActivityMgr::is_activity(ACE_UINT32 unID)
{
	if(m_itemMap.find(unID) == 0)
	{
		return true;
	}

	return false;
}

int ActivityMgr::get_status(ACE_UINT32 unID, ACE_UINT32 unCurrentTime, ACE_UINT32 unTimes)
{
	ActivityItemInfo *info;

	if(m_itemMap.find(unID, info) == 0)
	{
		if(info->activity == NULL)
		{
			return ACTIVITY_STATUS_OFFLINE;
		}

		if(info->activity->isStart)
		{
			if(info->activity->res->is_activity_online(unCurrentTime, unTimes))
			{
				return ACTIVITY_STATUS_ONLINE;
			}
			else
			{
				return ACTIVITY_STATUS_OFFLINE;
			}
		}

		return ACTIVITY_STATUS_OFFLINE;
	}

	return ACTIVITY_STATUS_NONE;
}