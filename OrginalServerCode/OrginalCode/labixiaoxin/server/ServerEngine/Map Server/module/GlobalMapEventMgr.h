#pragma once

#include "ace\ace.h"
#include "..\..\GameBase\res\LuckRes.h"
#include "ace\Singleton.h"

class Map;

class GlobalMapEventMgr
{
public:
	GlobalMapEventMgr();
	~GlobalMapEventMgr();

	void update(ACE_UINT32 unCurrentTime);
	void send_info(ACE_UINT32 unCurrentTime, Map *map, ACE_UINT32 unSN);

	int get_event_by_map_id(ACE_UINT32 unMapID);
	
	ACE_UINT32 m_unStartTime;

	ACE_UINT32 m_mapList[COMMON_MAP_STAGE_COUNT * 2];

private:
};

typedef ACE_Singleton<GlobalMapEventMgr, ACE_Thread_Mutex> GLOBAL_MAP_EVENT_MGR_INSTANCE;