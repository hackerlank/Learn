#pragma once

#include "ace\ace.h"
#include "ace\Singleton.h"
#include "ace\Null_Mutex.h"
#include "ace\Hash_Map_Manager.h"
#include "..\..\GameBase\res\DropRes.h"


typedef struct tagGlobalLootInfo
{
	int lootFlag[125];
	int nCursor;
	int nHitCount;
	DropGroup dropGroup;
}GlobalLootInfo;


typedef ACE_Hash_Map_Manager_Ex<ACE_UINT32, GlobalLootInfo *, ACE_Hash<ACE_UINT32>, 
ACE_Equal_To<ACE_UINT32>, ACE_Null_Mutex> GLOBAL_LOOT_MAP;
typedef GLOBAL_LOOT_MAP::ITERATOR GLOBAL_LOOT_MAP_ITERATOR;


class GlobalLootMgr
{
public:
	GlobalLootMgr();
	~GlobalLootMgr();

	ACE_UINT32 create_global_drop(float rate, ACE_UINT32 unCount, DropEntityInfo *list);
	
	//void init();

	bool global_loot(GlobalLootInfo *lootInfo);

	ACE_UINT32 loot(DropGroup &group, int nCount);

private:
	GLOBAL_LOOT_MAP m_lootMap;

	void reset(GlobalLootInfo *info);

	ACE_UINT32 get_drop(DropGroup &group);

	ACE_UINT32 m_unCurrentID;
	
};

typedef ACE_Singleton<GlobalLootMgr, ACE_Thread_Mutex> GLOBAL_LOOT_MGR_INSTANCE;