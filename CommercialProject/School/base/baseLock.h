#ifndef BASE_LOCK_H
#define BASE_LOCK_H

#include <sys/time.h>
#include <time.h>
#include <pthread.h>
#include "baseClass.h"

class Mutex : private Noncopyable
{
	public:
		friend class Condition;
		enum MutexType
		{
			fast = PTHREAD_MUTEX_ADAPTIVE_NP,
			recursive = PTHREAD_MUTEX_RECURSIVE_NP,
			timed = PTHREAD_MUTEX_TIMED_NP,
			errorcheck = PTHREAD_MUTEX_ERRORCHECK_NP
		};
		Mutex(MutexType _t = fast)
		{
			pthread_mutexattr_t attr;
			pthread_mutexattr_init(&attr);
			pthread_mutexattr_settype(&attr,_t);
			pthread_mutex_init(&mutex,&attr);
		}
		~Mutex()
		{
			pthread_mutex_destroy(&mutex);
		}
		void lock()
		{
			pthread_mutex_lock(&mutex);
		}
		void unlock()
		{
			pthread_mutex_unlock(&mutex);
		}
		bool trylock()
		{
			return pthread_mutex_trylock(&mutex) == 0;
		}
	private:
		pthread_mutex_t mutex;
};
class Condition : private Noncopyable
{
	public:
		Condition()
		{
			pthread_cond_init(&cond,NULL);
		}
		~Condition()
		{
			pthread_cond_destroy(&cond);
		}
		void broadcast()
		{
			pthread_cond_broadcast(&cond);
		}
		void signal()
		{
			pthread_cond_signal(&cond);
		}
		void wait(Mutex &mutex)
		{
			pthread_cond_wait(&cond,&mutex.mutex);
		}
		bool timedwait(Mutex &mutex,unsigned int timeout)
		{
			struct timeval now;
			gettimeofday(&now,NULL);
			struct timespec tsp;
			tsp.tv_sec = now.tv_sec + timeout;
			tsp.tv_nsec = now.tv_usec * 1000 + (timeout % 1000) * 1000 * 1000;
			if(0 == pthread_cond_timedwait(&cond,&mutex.mutex,&tsp))
			{
				return true;
			}
			return false;
		}
	private:
		pthread_cond_t cond;
};

class RWLock : private Noncopyable
{
	private:
		pthread_rwlock_t rwlock;
	public:
		RWLock()
		{
			pthread_rwlock_init(&rwlock,NULL);
		}
		~RWLock()
		{
			pthread_rwlock_destroy(&rwlock);
		}
		
		inline void rdlock()
		{
			pthread_rwlock_rdlock(&rwlock);
		}

		inline void wrlock()
		{
			pthread_rwlock_wrlock(&rwlock);
		}
		inline void unlock()
		{
			pthread_rwlock_unlock(&rwlock);
		}
};
template<bool T = true>
class RWLocker
{
	private:
		RWLock rwlock;
	public:
		void rdlock() { rwlock.rdlock();}
		void wrlock() { rwlock.wrlock();}
		void unlock() { rwlock.unlock();}
};
template<>
class RWLocker<false>
{
	public:
		void rdlock() {}
		void wrlock() {}
		void unlock() {}
};
class RWLock_scope_rdlock : private Noncopyable
{
	private:
		RWLock &rdlock;
	public:
		RWLock_scope_rdlock(RWLock &_rdlock):rdlock(_rdlock)
		{
			rdlock.rdlock();
		}
		~RWLock_scope_rdlock()
		{
			rdlock.unlock();
		}
};

class RWLock_scope_wrlock : private Noncopyable
{
	private:
		RWLock &wrlock;
	public:
		RWLock_scope_wrlock(RWLock &_wrlock):wrlock(_wrlock)
		{
			wrlock.wrlock();
		}
		~RWLock_scope_wrlock()
		{
			wrlock.unlock();
		}
};



#endif
