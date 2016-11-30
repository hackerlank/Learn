#pragma once

#include "ace\Condition_Thread_Mutex.h"
#include "ace\Recursive_Thread_Mutex.h"
#include "ace\Null_Condition.h"

class NetworkMutex
{
public:
	NetworkMutex();
	~NetworkMutex();

	ACE_Recursive_Thread_Mutex m_mutex;
	
	int m_nReferenceCount;
};