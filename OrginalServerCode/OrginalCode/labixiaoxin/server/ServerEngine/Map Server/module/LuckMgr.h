#pragma once

#include "ace\ace.h"
#include "..\..\GameBase\res\LuckRes.h"
#include "ace\Singleton.h"

#define MAX_LUCK_COUNT 8

class Map;

class LuckMgr
{
public:

	ACE_UINT32 m_unCount;
	LuckRes *m_luckList[MAX_LUCK_COUNT];
	LuckMgr();
	~LuckMgr();

	void init();
	
	ConfigReward *get_config_reward(ACE_UINT32 unLevel);
	//ACE_UINT32 get_luck(ACE_UINT32 unLevel, Map *map, int nCount);

};

typedef ACE_Singleton<LuckMgr, ACE_Thread_Mutex> LUCK_MGR_INSTANCE;