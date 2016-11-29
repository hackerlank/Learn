/********************************************************************
//	Server Utility Library Source File.
//	File name:	Event.cpp
//	Created:	2012/08/24	11:00
//	Organization:
//	Copyright (c) 2010-2020 Jingyuan Wang, All rights reserved.
// ------------------------------------------------------------------
//	Author:		Jingyuan Wang
//	E-Mail:		tyketom@hotmail.com
//	Http://
// ------------------------------------------------------------------
//	Purpose:
//	Version:	1.0
//	Histroy:
*********************************************************************/

#include "Event.h"
#ifdef __GNUG__
#include <sys/time.h>
#endif

CEvent::CEvent(bool bAutoReset) : _bAutoReset(bAutoReset)
{
#ifdef _WIN32
	_event = CreateEvent(NULL, bAutoReset ? FALSE : TRUE, FALSE, NULL);
#else
	_bSignaled = false;
	pthread_mutex_init(&_mutex, NULL);
	pthread_cond_init(&_cond, NULL);
#endif
}

CEvent::~CEvent()
{
#ifdef _WIN32
	CloseHandle(_event);
#else
	pthread_mutex_destroy(&_mutex);
	pthread_cond_destroy(&_cond);
#endif
}

bool CEvent::Set()
{
#ifdef _WIN32
	if(_event == NULL)
		return false;
	return SetEvent(_event) == TRUE;
#else
	if(pthread_mutex_lock(&_mutex) != 0)
		return false;
	_bSignaled = true;
	if(pthread_cond_broadcast(&_cond) != 0)
	{
		pthread_mutex_unlock(&_mutex);
		return false;
	}
	return pthread_mutex_unlock(&_mutex) == 0;
#endif
}

bool CEvent::Reset()
{
#ifdef _WIN32
	if(_event == NULL)
		return false;
	return ResetEvent(_event) == TRUE;
#else
	if(pthread_mutex_lock(&_mutex) != 0)
		return false;
	_bSignaled = false;
	return pthread_mutex_unlock(&_mutex) == 0;
#endif
}

bool CEvent::Wait()
{
#ifdef _WIN32
	if(_event == NULL)
		return false;
	if(WaitForSingleObject(_event, INFINITE) == WAIT_OBJECT_0)
		return true;
	return false;
#else
	if(pthread_mutex_lock(&_mutex) != 0)
		return false;
	while(!_bSignaled)
	{
		if(pthread_cond_wait(&_cond, &_mutex) != 0)
		{
			pthread_mutex_unlock(&_mutex);
			return false;
		}
	}
	if(_bAutoReset)
		_bSignaled = false;
	return pthread_mutex_unlock(&_mutex) == 0;
#endif
}

bool CEvent::Wait(UINT32 dwMilliSeconds)
{
#ifdef _WIN32
	if(_event == NULL)
		return false;
	if(WaitForSingleObject(_event, dwMilliSeconds) == WAIT_OBJECT_0)
		return true;
	return false;
#else
	int rc = 0;
	struct timespec abstime;
	struct timeval tv;
	gettimeofday(&tv, NULL);
	abstime.tv_sec  = tv.tv_sec + dwMilliSeconds / 1000;
	abstime.tv_nsec = tv.tv_usec*1000 + (dwMilliSeconds % 1000)*1000000;
	if (abstime.tv_nsec >= 1000000000)
	{
		abstime.tv_nsec -= 1000000000;
		abstime.tv_sec++;
	}
	if(pthread_mutex_lock(&_mutex) != 0)
		return false;
	while(!_bSignaled)
	{
		if((rc = pthread_cond_timedwait(&_cond, &_mutex, &abstime)))
		{
			if(rc == ETIMEDOUT)
				break;
			pthread_mutex_unlock(&_mutex);
			return false;
		}
	}
	if(rc == 0 && _bAutoReset)
		_bSignaled = false;
	pthread_mutex_unlock(&_mutex);
	return rc == 0;
#endif
}
