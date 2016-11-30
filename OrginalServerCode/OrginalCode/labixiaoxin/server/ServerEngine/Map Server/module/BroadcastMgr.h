#pragma once

#include "ace\ace.h"
#include "BaseModule.h"
#include "ace\Singleton.h"

class Map;

class BroadcastMgr : public BaseModule
{
public:
	BroadcastMgr();
	~BroadcastMgr();

	void init();

	void add_message(char *name, ACE_UINT32 unType, ACE_UINT32 unItemID, ACE_UINT32 unParam);

	void send_info(Map *map, ObjAdr &targetAdr, ACE_UINT32 unSN);
private:
	ACE_UINT32 m_unCounter;

	BroadcastMessage m_queue[MAX_BROADCAST_MESSAGE_COUNT];

	int m_head;
	int m_tail;
};

typedef ACE_Singleton<BroadcastMgr, ACE_Thread_Mutex> BROADCAST_MGR_INSTANCE;