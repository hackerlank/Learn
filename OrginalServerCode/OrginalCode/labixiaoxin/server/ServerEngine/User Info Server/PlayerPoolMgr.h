#pragma once

#include "..\GameBase\Common\GameDefine.h"
#include "ace\Null_Mutex.h"
#include "ace\Hash_Map_Manager.h"
#include "PlayerPool.h"

#define MIN_PLAYER_POOL_COUNT 64

class PlayerPoolMgr
{
public:
	PlayerPoolMgr();
	~PlayerPoolMgr();

	void init(ACE_UINT32 unSize);
	void resize(ACE_UINT32 unSize);
	void reset();

	void add(int nPoolID, PublicPlayerInfo *playerInfo);
	void move(int nPoolID, PublicPlayerInfo *playerInfo);

	int pool_size(int nPoolID);
	int get_random_player(int nPoolID, int minCount, PublicPlayerInfo *list[], int nCount);

	ACE_UINT32 m_unPoolType;
private:
	ACE_UINT32 cal_capcity(ACE_UINT32 unSize);

	PPlayerPool *m_poolList;
	//ACE_UINT32 m_unSize;
	ACE_UINT32 m_unCapcity;

	int m_randomCountList[1024];
};