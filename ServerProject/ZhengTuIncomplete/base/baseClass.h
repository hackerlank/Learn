#ifndef BASE_CLASS_H
#define BASE_CLASS_H
#include <iostream>
#include <assert.h>

#include "baseFunc.h"
using namespace std;

//不可拷贝类基类
class Noncopyable
{
	private:
		const Noncopyable& operator= (const Noncopyable& noncopyable);
		Noncopyable(const Noncopyable &noncopyable);
	protected:
		Noncopyable(){};
		virtual ~Noncopyable(){};
};

//单例基类
template<typename T,bool INIT = true>
class SingletonBase : private Noncopyable
{
};

template<typename T>
class SingletonBase<T,true> : private Noncopyable
{
	protected:
		SingletonBase()
		{
		}
		~SingletonBase()
		{
		}
	private:
		 static T *instance;
	public:
		static T& getInstance()
		{
			if( !instance )
			{
				instance = new T();
			}
			return *instance;
		}
		static void newInstance()
		{
			DELETE( instance );
			instance = new T();
		}
		static void deleteInstance()
		{
			DELETE( instance );
		}
};

template<typename T>
class SingletonBase<T,false> : private Noncopyable
{
	protected:
		SingletonBase()
		{
		}
		~SingletonBase()
		{
		}
	private:
		 static T *instance;
	public:
		static T& getInstance()
		{
			assert( instance );
			return *instance;
		}
		template<typename T1>
		static T1& getInstance()
		{
			assert( instance );
			return *(T1*)instance;
		}
		template<typename T1>
		static void newInstance()
		{
			DELETE( instance );
			instance = new T1();
		}
		static void deleteInstance()
		{
			DELETE( instance );
		}
};


template<typename T> T* SingletonBase<T,true>::instance = NULL;
template<typename T> T* SingletonBase<T,false>::instance = NULL;
#endif
			
