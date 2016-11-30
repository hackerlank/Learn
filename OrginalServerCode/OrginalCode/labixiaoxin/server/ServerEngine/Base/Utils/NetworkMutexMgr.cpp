#include "NetworkMutexMgr.h"
#include "ace\OS_NS_string.h"

#if _MEMORY_DEBUG
#include "../../GameBase/Common/debugnew.h"
#define new new(__FILE__, __LINE__)
#endif


NetworkMutexMgr::NetworkMutexMgr()
{
	ACE_OS::memset(m_connectionCountList, 0, sizeof(int) * MAX_NETWORK_MUTEX_MAP);	
}

NetworkMutexMgr::~NetworkMutexMgr()
{
	
}

void NetworkMutexMgr::increase_connection_count(ACE_UINT32 unIdx)
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);
	if(unIdx < 0 || unIdx >= MAX_NETWORK_MUTEX_MAP)
	{
		return;
	}

	m_connectionCountList[unIdx] ++;

	printf("increase:::connectiont count = %d[%d]\n", m_connectionCountList[unIdx], unIdx);
}

void NetworkMutexMgr::decrease_connection_count(ACE_UINT32 unIdx)
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);
	if(unIdx < 0 || unIdx >= MAX_NETWORK_MUTEX_MAP)
	{
		return;
	}

	m_connectionCountList[unIdx] --;

	printf("decrease:::connectiont count = %d[%d]\n", m_connectionCountList[unIdx], unIdx);

	if(m_connectionCountList[unIdx] < 0)
	{
		m_connectionCountList[unIdx] = 0;
	}
}

int NetworkMutexMgr::get_connection_count(ACE_UINT32 unIdx)
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);
	if(unIdx < 0 || unIdx >= MAX_NETWORK_MUTEX_MAP)
	{
		return 0;
	}

	return m_connectionCountList[unIdx];
}

NetworkMutex *NetworkMutexMgr::acquire(ACE_UINT32 unIdx, ACE_UINT32 unID)
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);

	if(unIdx < 0 || unIdx >= MAX_NETWORK_MUTEX_MAP)
	{
		return NULL;
	}

	NetworkMutex *networkMutex = NULL;

	if(m_mutexMapList[unIdx].find(unID, networkMutex) != 0)
	{
		networkMutex = new NetworkMutex();

		if(networkMutex == NULL)
		{
			return NULL;
		}

		if(m_mutexMapList[unIdx].bind(unID, networkMutex) != 0)
		{
			delete networkMutex;

			return NULL;
		}
	}
	
	networkMutex->m_nReferenceCount ++;

	return networkMutex;
}

void NetworkMutexMgr::release(ACE_UINT32 unIdx, ACE_UINT32 unID)
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);

	if(unIdx < 0 || unIdx >= MAX_NETWORK_MUTEX_MAP)
	{
		return;
	}

	NetworkMutex *networkMutex = NULL;

	if(m_mutexMapList[unIdx].find(unID, networkMutex) != 0)
	{
		return;
	}

	networkMutex->m_nReferenceCount --;

	if(networkMutex->m_nReferenceCount <= 0)
	{
		m_mutexMapList[unIdx].unbind(unID, networkMutex);
		delete networkMutex;
	}
}

bool NetworkMutexMgr::is_empty()
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);

	int i;

	for(i = 0;i < MAX_NETWORK_MUTEX_MAP;i ++)
	{
		if(!is_empty(i))
		{
			return false;
		}
	}

	return true;
}

bool NetworkMutexMgr::is_empty(ACE_UINT32 unIdx)
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);

	if(unIdx < 0 || unIdx >= MAX_NETWORK_MUTEX_MAP)
	{
		return true;
	}

	return (m_mutexMapList[unIdx].current_size() == 0);
}