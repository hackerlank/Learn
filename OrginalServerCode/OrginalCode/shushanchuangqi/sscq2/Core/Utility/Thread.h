/********************************************************************
//	Server Utility Library Source File.
//	File name:	Thread.h
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

#pragma once
#include <thread>
#include <utility>
#include <system_error>

class CThread
{
public:
	CThread() : _bRunning(false) { }
	CThread(CThread&& src) : _bRunning(src._bRunning), _thread(move(src._thread)) { src._bRunning = false; }

	~CThread()
	{
		if(_thread.joinable())
			_thread.detach();
	}

#ifdef _WIN32
	template<typename F>
	bool Start(F&& f)
	{
		if(_bRunning)
			return false;
		try
		{
			_thread = std::thread(std::forward<F>(f));
			_bRunning = true;
		}
		catch(std::system_error& ex)
		{
			printf("Start Thread Fails: %s", ex.what());
		}
		catch(...)
		{
			printf("Start Thread Fails!");
		}
		return _bRunning;
	}

	template<typename F, typename A1>
	bool Start(F&& f, A1&& a1)
	{
		if(_bRunning)
			return false;
		try
		{
			_thread = std::thread(std::forward<F>(f), std::forward<A1>(a1));
			_bRunning = true;
		}
		catch(std::system_error& ex)
		{
			printf("Start Thread Fails: %s", ex.what());
		}
		catch(...)
		{
			printf("Start Thread Fails!");
		}
		return _bRunning;
	}

	template<typename F, typename A1, typename A2>
	bool Start(F&& f, A1&& a1, A2&& a2)
	{
		if(_bRunning)
			return false;
		try
		{
			_thread = std::thread(std::forward<F>(f), std::forward<A1>(a1), std::forward<A2>(a2));
			_bRunning = true;
		}
		catch(std::system_error& ex)
		{
			printf("Start Thread Fails: %s", ex.what());
		}
		catch(...)
		{
			printf("Start Thread Fails!");
		}
		return _bRunning;
	}
#else
	template<typename F, typename... Args>
	bool Start(F&& f, Args&&... args)
	{
		if(_bRunning)
			return false;
		try
		{
			_thread = std::thread(std::forward<F>(f), std::forward<Args>(args)...);
			_bRunning = true;
		}
		catch(std::system_error& ex)
		{
			printf("Start Thread Fails: %s", ex.what());
		}
		catch(...)
		{
			printf("Start Thread Fails!");
		}
		return _bRunning;
	}
#endif

	bool IsRunning() const { return _bRunning; }

	void Join()
	{
		bool bRunning  = _bRunning;
		_bRunning = false;
		if(bRunning)
			_thread.join();
	}

protected:
	bool _bRunning;
	std::thread _thread;
};
