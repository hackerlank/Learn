#ifndef BASE_THREAD_H
#define BASE_THREAD_H

#include <signal.h>
#include <bits/atomicity.h>
#include "baseLock.h"
#include "baseEntry.h"

class Thread : public Entry
{
	private:
		static void *threadProc(void *arg);
		virtual void run() = 0;
	public:
		virtual void initParam(void *arg)
		{
		}
		Thread(const char *name,const bool joinable = true);
		virtual ~Thread();
		const char* getClassName()
		{
			return "线程";
		}
		void mysqlInit();
		void mysqlDestroy();
		bool start();
		bool checkRunning();
		inline void setRuning()
		{
			m_run = true;
		}
		pthread_t getThreadID();
		void join();
		const bool isJoinable() const;
		void final();
		const bool isAlive() const;
		const bool isFinal() const;
		static void sleep(const SQWORD sec);
		static void msleep(const SQWORD millis);
		static void usleep(const SQWORD usec);
		static pthread_t getCurrentThreadId();
		static SQWORD atomicAdd(volatile SQWORD *val,const SQWORD x);
		static long atomicInc(volatile SQWORD *val);
		static long atomicDec(volatile SQWORD *val);
	private:
		Mutex m_mlock;
		Condition m_cond;
		bool m_joinable;
		pthread_t m_thread;
		volatile bool m_alive;
		volatile bool m_complete;
		volatile bool m_run;
		static QWORD s_tempId;
};

class ThreadManager : public EntryManager<EntryID,EntryNone<2>,EntryNone<3>,true>,public SingletonBase<ThreadManager>
{
	private:
		friend class SingletonBase<ThreadManager>;
		ThreadManager()
		{
		}
		~ThreadManager()
		{
		}
	public:
		bool addThread(Thread *entry);
		void removeThread(Thread *entry);
		template<class YourEntry>
		bool execEveryThread(EntryCallBack<YourEntry> &exec)
		{
			bool ret = false;
			rwlock.rdlock();
			ret = execEveryEntry<>(exec);
			rwlock.unlock();
			return ret;
		}
	private:
		RWLock rwlock;
};



#endif
