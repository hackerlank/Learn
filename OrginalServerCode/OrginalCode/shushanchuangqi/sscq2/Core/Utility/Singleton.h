#pragma once
#include <stdlib.h>
#include <atomic>

// Singleton object MUST BE initialized manually.
template<typename T>
class Singleton
{
public:
	static T& Instance() // Unique point of access
	{
		if(_instance == nullptr)
		{
			_instance = new T;
			// atexit(Destroy); // XXX: 有必要吗？程序都退出了就没有这个必要了
		}
		return *_instance;
	}
private:
	static void Destroy() // Destroy the only instance
	{
		if(_instance != nullptr)
		{
			delete(_instance);
			_instance = nullptr;
		}
	}
	static T* volatile _instance; // The one and only instance
};

template<typename T>
T* volatile Singleton<T>::_instance;

template <typename T>
class StaticSingleton
{
public:
	static T& Instance() // Unique point of access
	{
		return _instance;
	}
private:
	static T _instance; // The one and only instance
};

template<typename T>
T StaticSingleton<T>::_instance;

template<typename T>
class MultiThreadSingleton
{
public:
	static T& Instance() // Multiple point of access
	{
		if(_instance.load() == nullptr)
		{
			T* pExpected = nullptr;
			T* pValue = new T;
			if(!_instance.compare_exchange_strong(pExpected, pValue))
				delete pValue;
		}
		return *_instance;
	}
private:
	static std::atomic<T*> _instance;
};

template<typename T>
std::atomic<T*> MultiThreadSingleton<T>::_instance;
