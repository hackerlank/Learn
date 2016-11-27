#include "baseThread.h"

QWORD Thread::s_tempId = 0;
Thread::Thread(const char* name,const bool joinable):m_run(true),m_joinable(joinable)
{
	id = ++s_tempId;
	ThreadManager::getInstance().addThread(this);
	strncpy(this->name,name,sizeof(this->name));
	m_alive = false;
	m_thread = 0;
	m_complete= false;
}
Thread::~Thread()
{
	ThreadManager::getInstance().removeThread(this);
	m_thread = 0;
}
bool Thread::checkRunning()
{
	if(!isAlive())
	{
		return true;
	}
	if(m_run)
	{
		m_run = false;
		return true;
	}
	return false;
}
void* Thread::threadProc(void *arg)
{
	Thread *thread = (Thread*)arg;
	thread->m_mlock.lock();
	thread->m_alive = true;
	thread->m_cond.broadcast();
	thread->m_mlock.unlock();
	sigset_t sig_mask;
	sigfillset(&sig_mask);
	pthread_sigmask(SIG_SETMASK,&sig_mask,NULL);
	thread->run();
	thread->m_mlock.lock();
	thread->m_alive = false;
	thread->m_cond.broadcast();
	thread->m_mlock.unlock();
	if(!thread->isJoinable())
	{
		DELETE(thread);
	}
	pthread_exit(NULL);
}
bool Thread::start()
{
	SDWORD ret = 1;
	m_mlock.lock();
	if(!m_alive)
	{
		 ret = pthread_create(&m_thread,NULL,threadProc,this);
	}
	m_mlock.unlock();
	LogErrorCheckCondition( !ret,false,"线程初始化失败%d",m_alive );
	return true;
}
void Thread::join()
{
	if(m_thread && m_joinable)
	{
		pthread_join(m_thread,NULL);
		m_thread = 0;
		m_mlock.lock();
		while(m_alive)
		{
			m_cond.wait(m_mlock);
		}
	}
}
pthread_t Thread::getCurrentThreadId()
{
	return pthread_self();
}
void Thread::sleep(const SQWORD sec)
{
	::sleep(sec);
}
void Thread::msleep(const SQWORD mills)
{
	::usleep(1000 * mills);
}
void Thread::usleep(const SQWORD usec)
{
	::usleep(usec);
}
void Thread::final()
{
	m_complete = true;
}
const bool Thread::isFinal() const
{
	return m_complete;
}
long Thread::atomicAdd(volatile SQWORD *val,SQWORD x)
{
	return __gnu_cxx::__exchange_and_add((volatile _Atomic_word *)val,x) + x;
}
long Thread::atomicInc(volatile SQWORD *val)
{
	return atomicAdd(val,1);
}
long Thread::atomicDec(volatile SQWORD *val)
{
	return atomicAdd(val,-1);
}
const bool Thread::isAlive() const
{
	return m_alive;
}
const bool Thread::isJoinable()const
{
	return m_joinable;
}
bool ThreadManager::addThread(Thread *entry)
{
	bool ret = false;
	rwlock.wrlock();
	ret = addEntry(entry);
	rwlock.unlock();
	return ret;
}
void ThreadManager::removeThread(Thread *entry)
{
	rwlock.wrlock();
	removeEntry(entry);
	rwlock.unlock();
}


