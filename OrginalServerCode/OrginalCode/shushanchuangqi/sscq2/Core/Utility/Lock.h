/********************************************************************
//	Server Utility Library Source File.
//	File name:	Lock.h
//	Created:	2012/08/21	11:00
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

#pragma once
#ifdef _WIN32
#include <Windows.h>
#else
#include "Linux.h"
#endif

class CSpinLock
{
public:
    CSpinLock()
	{
#ifdef _WIN32
#define LOCK_SPIN_COUNT 4000
		InitializeCriticalSectionAndSpinCount(&_cs, LOCK_SPIN_COUNT);
#else
		pthread_spin_init(&_spinLock, PTHREAD_PROCESS_PRIVATE);
#endif
	}

	~CSpinLock()
	{
#ifdef _WIN32
		DeleteCriticalSection(&_cs);
#else
		pthread_spin_destroy(&_spinLock);
#endif
	}

    void Lock()
	{
#ifdef _WIN32
		EnterCriticalSection(&_cs);
#else
		pthread_spin_lock(&_spinLock);
#endif
	}

    bool TryLock()
	{
#ifdef _WIN32
		return TryEnterCriticalSection(&_cs) == TRUE;
#else
		return pthread_spin_trylock(&_spinLock) == 0;
#endif
	}

    void UnLock()
	{
#ifdef _WIN32
		LeaveCriticalSection(&_cs);
#else
		pthread_spin_unlock(&_spinLock);
#endif
	}

protected:
#ifdef _WIN32
	CRITICAL_SECTION _cs;
#else
    pthread_spinlock_t _spinLock;
#endif
};

class CMutexLock
{
public:
	CMutexLock()
	{
#ifdef _WIN32
		_hMutex = CreateMutex(NULL, FALSE, NULL);
#else
		pthread_mutex_init(&_mutex, NULL);
#endif
	}

	~CMutexLock()
	{
#ifdef _WIN32
		CloseHandle(_hMutex);
#else
		pthread_mutex_destroy(&_mutex);
#endif
	}

    void Lock()
	{
#ifdef _WIN32
		WaitForSingleObject(_hMutex, INFINITE);
#else
		pthread_mutex_lock(&_mutex);
#endif
	}

    bool TryLock()
	{
#ifdef _WIN32
		return WaitForSingleObject(_hMutex, 0) == TRUE;
#else
		return pthread_mutex_trylock(&_mutex) == 0;
#endif
	}

    void UnLock()
	{
#ifdef _WIN32
		ReleaseMutex(_hMutex);
#else
		pthread_mutex_unlock(&_mutex);
#endif
	}

protected:
#ifdef _WIN32
	HANDLE _hMutex;
#else
    pthread_mutex_t _mutex;
#endif
};

template<typename T>
class CAutoLock
{
public:
    CAutoLock(T& rLock) : _rLock(rLock) { rLock.Lock(); }
    ~CAutoLock() { _rLock.UnLock(); }
protected:
    T& _rLock;
};

template<typename T>
class CAutoTryLock
{
public:
    CAutoTryLock(T& rLock) : _rLock(rLock) { _bLocked = rLock.TryLock(); }
    ~CAutoTryLock() { if(_bLocked) _rLock.UnLock(); }
protected:
    T& _rLock;
    bool _bLocked;
};
