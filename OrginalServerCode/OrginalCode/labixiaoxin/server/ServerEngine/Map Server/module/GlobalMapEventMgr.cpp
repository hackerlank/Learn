#include "GlobalMapEventMgr.h"
#include "..\..\GameBase\res\GameConfig.h"
#include "..\..\GameBase\Common\GameUtils.h"
#include "..\..\GameBase\res\ItemResMgr.h"
#include "..\Map.h"

GlobalMapEventMgr::GlobalMapEventMgr()
{
	m_unStartTime = 0;
	ACE_OS::memset(m_mapList, 0, sizeof(ACE_UINT32) * 2 * COMMON_MAP_STAGE_COUNT);
}

GlobalMapEventMgr::~GlobalMapEventMgr()
{

}


void GlobalMapEventMgr::update(ACE_UINT32 unCurrentTime)
{
	int t = (int)(unCurrentTime - m_unStartTime);

	if((t / GLOBAL_MAP_EVENT_COOLDOWN) <= 0)
	{
		return;
	}

	m_unStartTime = unCurrentTime - t % GLOBAL_MAP_EVENT_COOLDOWN;

	int i;//, j;
	//int idx;

	for(i = 0;i < COMMON_MAP_STAGE_COUNT;i ++)
	{
		m_mapList[2 * i] = (ACE_OS::rand() % COMMON_MAP_SUB_STAGE_COUNT) + 1;
		m_mapList[2 * i + 1] = (ACE_OS::rand() % COMMON_MAP_SUB_STAGE_COUNT) + 1;

		if(m_mapList[2 * i] == m_mapList[2 * i + 1])
		{
			m_mapList[2 * i + 1] ++;

			if(m_mapList[2 * i + 1] > COMMON_MAP_SUB_STAGE_COUNT)
			{
				m_mapList[2 * i + 1] = 1;
			}
		}
	}
}

void GlobalMapEventMgr::send_info(ACE_UINT32 unCurrentTime, Map *map, ACE_UINT32 unSN)
{
	update(unCurrentTime);

	MsgGetGlobalMapEventResponse response;
	response.nResult = 0;
	response.unSN = unSN;
	response.unCooldown = unCurrentTime - m_unStartTime;
	ACE_OS::memcpy(response.unMapList, m_mapList, sizeof(ACE_UINT32) * 2 * COMMON_MAP_STAGE_COUNT);

	map->send_msg_2_client(SERVICE_MESSAGE_TYPE_USER, MSG_GET_GLOBAL_MAP_EVENT_RESPONSE, (char *)&response, sizeof(MsgGetGlobalMapEventResponse));
}

int GlobalMapEventMgr::get_event_by_map_id(ACE_UINT32 unMapID)
{
	//1504070001
	//int m = (unMapID / 1000000) % 100;
	//int n = (unMapID / 10000) % 100;

	int m = GET_ITEM_ID_INFO(unMapID, 4, 2);
	int n = GET_ITEM_ID_INFO(unMapID, 2, 1);

	if(m > COMMON_MAP_STAGE_COUNT || n > COMMON_MAP_SUB_STAGE_COUNT)
	{
		return GLOBAL_MAP_EVENT_NONE;
	}

	m = m - 1;

	int nRet = GLOBAL_MAP_EVENT_NONE;
	
	if(m_mapList[2 * m] == n)
	{
		nRet = GLOBAL_MAP_EVENT_COIN_DOUBLE;
	}
	else if(m_mapList[2 * m + 1] == n)
	{
		nRet = GLOBAL_MAP_EVENT_DROP_DOUBLE;
	}

	return nRet;
}