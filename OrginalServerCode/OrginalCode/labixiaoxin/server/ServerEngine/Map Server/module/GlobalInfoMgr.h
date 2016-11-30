#pragma once

#include "ace\ace.h"
#include "ace\Singleton.h"
#include "..\..\Base\Utils\ConfigLoader.h"
#include "ace\Hash_Map_Manager.h"
#include "ace\Null_Mutex.h"
#include "..\..\GameBase\common\GameDefine.h"

class GlobalInfoMgr
{
public:
	GlobalInfoMgr();
	~GlobalInfoMgr();

	void init();
	
	ACE_UINT32 m_unMapGroupCount;
	ACE_UINT32 m_mapGroupList[MAX_MAP_COUNT];
	ACE_UINT32 m_unMapCount;
	ACE_UINT32 m_mapList[MAX_MAP_COUNT * MAX_MAP_DIFFRENCE];

private:
	void add_map_id(ACE_UINT32 unMapID);
};

typedef ACE_Singleton<GlobalInfoMgr, ACE_Thread_Mutex> GLOBAL_INFO_MGR_INSTANCE;