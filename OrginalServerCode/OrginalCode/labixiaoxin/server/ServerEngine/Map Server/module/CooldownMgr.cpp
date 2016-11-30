#include "CooldownMgr.h"
#include "..\..\GameBase\res\GameConfig.h"
#include "..\..\GameBase\Common\GameUtils.h"
#include "..\..\GameBase\res\ItemResMgr.h"
#include "..\Map.h"

#include "ActivityMgr.h"


CooldownMgr::CooldownMgr()
{
	m_unCooldownInfoCount = 0;
}

CooldownMgr::~CooldownMgr()
{
	
}

void CooldownMgr::init(CooldownInstanceInfo *list)
{
	ACE_OS::memcpy(m_list, list, sizeof(CooldownInstanceInfo) * MAX_COOLDOWN_INFO);

	int i;
	m_unCooldownInfoCount = 0;
	for(i = 0;i < MAX_COOLDOWN_INFO;i ++)
	{
		if(m_list[i].unItemID == 0)
		{
			break;
		}

		m_unCooldownInfoCount ++;
	}
}

void CooldownMgr::update(ACE_UINT32 unCurrentTime)
{
	
}

void CooldownMgr::send_info(ObjAdr &targetAdr, ACE_UINT32 unSN)
{
	MsgCooldownListResponse response;
	response.nResult = 0;
	response.unSN = unSN;

	response.unCount = m_unCooldownInfoCount;

	ACE_OS::memcpy(response.list, m_list, sizeof(CooldownInstanceInfo) * m_unCooldownInfoCount);

	m_map->sendMsg(SERVICE_MESSAGE_TYPE_USER, MSG_COOLDOWN_LIST_RESPONSE, (char *)&response, sizeof(MsgCooldownListResponse), targetAdr);
}

void CooldownMgr::update_2_db()
{
	MsgDBUpdateCooldownListRequest db_request;
	ACE_OS::memcpy(db_request.list, m_list, sizeof(CooldownInstanceInfo) * MAX_COOLDOWN_INFO);
	m_map->add_db_request(ADAPTER_DB_HOME_MGR, MSG_DB_UPDATE_COOLDOWN_LIST, (char *)&db_request, sizeof(MsgDBUpdateCooldownListRequest));
}


int CooldownMgr::can_do(ACE_UINT32 unCurrentTime, ACE_UINT32 unID, ACE_UINT32 unTimes)//判断是否已过冷却时间
{
	int t = ACTIVITY_MGR_INSTANCE::instance()->get_status(unID, unCurrentTime, unTimes);//

	if(t == ACTIVITY_STATUS_OFFLINE)
	{
		return -1;
	}

	BaseRes *res = ITEM_RES_MGR_INSTANCE::instance()->get_item_res(unID);
	if(res == NULL)
	{
		return -1;
	}

	int idx = get_cd_info(unID);

	if(idx == -1)
	{
		return 0;
	}

	CooldownInstanceInfo *info = &m_list[idx];

	//update_cooldown(unCurrentTime, info, res);

	/*
	if(info->unCount < res->m_cdInfo.unCountLimit)
	{
		return 0;
	}
	*/

	if(get_current_count(unCurrentTime, info, res) < res->m_cdInfo.unCountLimit)
	{
		return 0;
	}

	return -1;
}

int CooldownMgr::get_current_count(ACE_UINT32 unCurrentTime, CooldownInstanceInfo *info, BaseRes *res)
{
	int t = GameUtils::get_time_offset(unCurrentTime, info->unLastUpdateTime, res->m_cdInfo.unOffset, res->m_cdInfo.unPrecision);

	if(t >= res->m_cdInfo.unCD)
	{
		return 0;
	}
	
	return info->unCount;
}

int CooldownMgr::get_count( ACE_UINT32 unCurrentTime, ACE_UINT32 unID, ACE_UINT32 unTimes /*= -1*/ )
{
	int t = ACTIVITY_MGR_INSTANCE::instance()->get_status(unID, unCurrentTime, unTimes);//

	if(t == ACTIVITY_STATUS_OFFLINE)
	{
		return -1;
	}

	BaseRes *res = ITEM_RES_MGR_INSTANCE::instance()->get_item_res(unID);
	if(res == NULL)
	{
		return -1;
	}

	int idx = get_cd_info(unID);

	if(idx == -1)
	{
		return 0;
	}

	CooldownInstanceInfo *info = &m_list[idx];

	return get_current_count(unCurrentTime, info, res);
}


int CooldownMgr::do_once(ACE_UINT32 unCurrentTime, ACE_UINT32 unID)
{
	BaseRes *res = ITEM_RES_MGR_INSTANCE::instance()->get_item_res(unID);
	if(res == NULL)
	{
		return -1;
	}

	int idx = get_cd_info(unID);

	if(idx == -1)
	{
		return 0;
	}

	CooldownInstanceInfo *info = &m_list[idx];

	/*
	update_cooldown(unCurrentTime, info, res);

	if(info->unCount < res->m_cdInfo.unCountLimit)
	{
		info->unCount ++;
		update_2_db();
		return 0;
	}
	*/
	return add_count(unCurrentTime, info, res);
}

int CooldownMgr::add_count(ACE_UINT32 unCurrentTime, CooldownInstanceInfo *info, BaseRes *res)
{
	int t = GameUtils::get_time_offset(unCurrentTime, info->unLastUpdateTime, res->m_cdInfo.unOffset, res->m_cdInfo.unPrecision);

	if(t >= res->m_cdInfo.unCD)
	{
		info->unCount = 0;
		info->unLastUpdateTime = unCurrentTime;
	}
	
	if(info->unCount >= res->m_cdInfo.unCountLimit)
	{
		return -1;
	}

	info->unCount ++;
	update_2_db();

	return 0;
}

int CooldownMgr::get_cd_info(ACE_UINT32 unID)
{
	BaseRes *res = ITEM_RES_MGR_INSTANCE::instance()->get_item_res(unID);

	if(res == NULL)
	{
		return -1;
	}

	if(res->m_cdInfo.unCD == 0)
	{
		return -1;
	}

	int idx = GameUtils::find_element(m_unCooldownInfoCount, m_list, sizeof(CooldownInstanceInfo), unID);

	if(idx == -1)
	{
		idx = GameUtils::add_element(m_unCooldownInfoCount, m_list, MAX_COOLDOWN_INFO, sizeof(CooldownInstanceInfo), unID);
	}

	return idx;
}

/*
bool CooldownMgr::update_cooldown(ACE_UINT32 unCurrentTime, CooldownInstanceInfo *info)
{
	BaseRes *res = ITEM_RES_MGR_INSTANCE::instance()->get_item_res(info->unItemID);

	if(res == NULL)
	{
		return false;
	}

	return update_cooldown(unCurrentTime, info, res);

	
}

bool CooldownMgr::update_cooldown(ACE_UINT32 unCurrentTime, CooldownInstanceInfo *info, BaseRes *res)
{
	if(res->m_cdInfo.unCD == 0)
	{
		return false;
	}

	int t = GameUtils::get_time_offset(unCurrentTime, info->unLastUpdateTime, res->m_cdInfo.unOffset, res->m_cdInfo.unPrecision);

	if(t >= res->m_cdInfo.unCD)
	{
		info->unCount = 0;
		info->unLastUpdateTime = unCurrentTime;

		return true;
	}
	
	return false;
}
*/