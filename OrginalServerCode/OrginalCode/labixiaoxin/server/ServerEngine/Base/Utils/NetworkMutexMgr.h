#pragma once

#include "NetworkMutex.h"
#include "ace\Singleton.h"

#include "ace\Condition_Thread_Mutex.h"
#include "ace\Recursive_Thread_Mutex.h"
#include "ace\Null_Condition.h"

#include "ace\Hash_Map_Manager.h"
#include "ace\Null_Mutex.h"


typedef ACE_Hash_Map_Manager_Ex<ACE_UINT32, NetworkMutex *, ACE_Hash<ACE_UINT32>, 
ACE_Equal_To<ACE_UINT32>, ACE_Null_Mutex> NETWORK_MUTEX_MAP;
typedef NETWORK_MUTEX_MAP::ITERATOR NETWORK_MUTEX_MAP_ITERATOR;

#define MAX_NETWORK_MUTEX_MAP 3

class NetworkMutexMgr
{
public:
	NetworkMutexMgr();
	~NetworkMutexMgr();

	ACE_Recursive_Thread_Mutex m_mutex;
	
	NetworkMutex *acquire(ACE_UINT32 unIdx, ACE_UINT32 unID);
	void release(ACE_UINT32 unIdx, ACE_UINT32 unID);

	bool is_empty();
	bool is_empty(ACE_UINT32 unIdx);

	void increase_connection_count(ACE_UINT32 unIdx);
	void decrease_connection_count(ACE_UINT32 unIdx);
	int get_connection_count(ACE_UINT32 unIdx);

private:
	NETWORK_MUTEX_MAP m_mutexMapList[MAX_NETWORK_MUTEX_MAP];
	int m_connectionCountList[MAX_NETWORK_MUTEX_MAP];
};

typedef ACE_Singleton<NetworkMutexMgr, ACE_Thread_Mutex> NETWORK_MUTEXT_MGR_INSTANCE;