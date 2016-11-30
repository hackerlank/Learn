#include "TimerMgr.h"

#if _MEMORY_DEBUG
#include "../../GameBase/Common/debugnew.h"
#define new new(__FILE__, __LINE__)
#endif


TimerMgr::TimerMgr()
{

}

TimerMgr::~TimerMgr()
{

}

ACE_INT32 TimerMgr::open()
{
	return m_tTimerSet.activate();
}

ACE_INT32 TimerMgr::close()
{
	m_tTimerSet.deactivate();

	return 0;
}

ACE_INT32 TimerMgr::reschedule(long lTimerID, ACE_Time_Value &obIntervalTime)
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);

	ACE_Timer_Heap *opTimerQueue = m_tTimerSet.timer_queue();
	if (opTimerQueue == NULL) {
		return -1;
	}

	opTimerQueue->reset_interval(lTimerID, obIntervalTime);

	return 0;
}

/*
long TimerMgr::registTimer(BaseTimerHandler *opHandler, void *vParam, ACE_Time_Value &tActTime, ACE_Time_Value &tInterval, long &lTimerID)
{
	ACE_Guard<ACE_Thread_Mutex> guard(m_mutex);

	long tmp_id;

	const ACE_Time_Value tCurTime = ACE_OS::gettimeofday();
	tmp_id = m_tTimerSet.schedule(opHandler, vParam, tCurTime+tActTime, tInterval);
	if (tmp_id == -1) {
		return -1;
	}

	opHandler->m_lTimerID = tmp_id;
	lTimerID = tmp_id;

	return tmp_id;
}
*/

/*
long TimerMgr::registerTimer(void *owner, Timer_Callback_Func callback, void *vParam, ACE_Time_Value &tActTime, ACE_Time_Value &tInterval)
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);

	BaseTimerHandler *opHandler = new BaseTimerHandler(owner, callback);

	if(opHandler == NULL)
	{
		return -1;
	}
	
	long tmp_id;

	const ACE_Time_Value tCurTime = ACE_OS::gettimeofday();

	tmp_id = m_tTimerSet.schedule(opHandler, vParam, tCurTime+tActTime, tInterval);
	if (tmp_id == -1) {
		delete opHandler;
		return -1;
	}

	opHandler->m_lTimerID = tmp_id;

	return tmp_id;
}
*/

BaseTimerHandler *TimerMgr::registerTimer(void *owner, Timer_Callback_Func callback, void *vParam, ACE_Time_Value &tActTime, ACE_Time_Value &tInterval)
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);

	BaseTimerHandler *opHandler = new BaseTimerHandler(owner, callback);

	if(opHandler == NULL)
	{
		return NULL;
	}
	
	long tmp_id;

	const ACE_Time_Value tCurTime = ACE_OS::gettimeofday();

	tmp_id = m_tTimerSet.schedule(opHandler, vParam, tCurTime+tActTime, tInterval);
	if (tmp_id == -1) {
		delete opHandler;
		return NULL;
	}

	opHandler->m_lTimerID = tmp_id;

	return opHandler;
}

/*
long TimerMgr::registTimer(RootObj *owner, void *vParam, ACE_Time_Value &tActTime, ACE_Time_Value &tInterval, Timer_Callback_Func pFunc)
{
	ACE_Guard<ACE_Thread_Mutex> guard(m_mutex);

	BaseTimerHandler *handler = new BaseTimerHandler(pFunc);

	if(handler == NULL)
	{
		return -1;
	}

	long tmp_id;

	const ACE_Time_Value tCurTime = ACE_OS::gettimeofday();

	tmp_id = m_tTimerSet.schedule(handler, vParam, tCurTime+tActTime, tInterval);
	if (tmp_id == -1) {
		delete handler;
		return -1;
	}

	if(m_ObjMap.bind(tmp_id, owner) != 0)
	{
		deleteTimer(tmp_id);
		delete handler;
		return -1;
	}

	handler->m_lTimerID = tmp_id;

	return tmp_id;
}
*/

ACE_INT32 TimerMgr::deleteTimer(long lTimerID)
{
	ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);

	if(lTimerID == -1)
	{
		return 0;
	}

	int ret = m_tTimerSet.cancel(lTimerID);

	printf("delete timer ret = %d\n", ret);
	//m_tTimerSet.c
	//m_ObjMap.unbind(lTimerID);

	return 0;
}


/*
void TimerMgr::doTimeout(long lTimerID)
{
	ACE_Guard<ACE_Thread_Mutex> guard(m_mutex);

	RootObj *pObj = NULL;
	if(m_ObjMap.find(lTimerID, pObj) == 0 && pObj != NULL)
	{
		pObj->handleTimeout(lTimerID);
	}
}
*/