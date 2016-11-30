#pragma once

#include "ace\Time_Value.h"
#include "ace\Timer_Queue_Adapters.h"
#include "ace\Timer_Heap.h"
#include "BaseTimerHandler.h"
#include "ace\Mutex.h"
#include "ace\Singleton.h"
#include "ace\Null_Mutex.h"
#include "ace\Hash_Map_Manager.h"
//#include "..\Service\RootObj.h"

typedef ACE_Thread_Timer_Queue_Adapter<ACE_Timer_Heap> TIMER_SET;

/*
typedef ACE_Hash_Map_Manager_Ex<long, BaseTimerHandler *, ACE_Hash<long>, 
ACE_Equal_To<long>, ACE_Null_Mutex> TIMER_HANDLER_MAP;
typedef TIMER_HANDLER_MAP::ITERATOR TIMER_HANDLER_MAP_ITERATOR;
*/

/*
typedef ACE_Hash_Map_Manager_Ex<long, RootObj *, ACE_Hash<long>, 
ACE_Equal_To<long>, ACE_Null_Mutex> SERVICE_TIMER_OBJ_MAP;
typedef SERVICE_TIMER_OBJ_MAP::ITERATOR SERVICE_TIMER_OBJ_MAP_ITERATOR;
*/

class TimerMgr
{
public:
	TimerMgr();
	~TimerMgr();

	ACE_INT32 open();
	ACE_INT32 close();

	ACE_INT32 reschedule(long lTimerID, ACE_Time_Value &obIntervalTime);
	//long registTimer(RootObj *owner, void *vParam, ACE_Time_Value &tActTime, ACE_Time_Value &tInterval, Timer_Callback_Func pFunc);
	//long registerTimer(void *owner, Timer_Callback_Func callback, void *vParam, ACE_Time_Value &tActTime, ACE_Time_Value &tInterval);
	BaseTimerHandler *registerTimer(void *owner, Timer_Callback_Func callback, void *vParam, ACE_Time_Value &tActTime, ACE_Time_Value &tInterval);
	//long registTimer(BaseTimerHandler *opHandler, void *vParam, ACE_Time_Value &tActTime, ACE_Time_Value &tInterval, long &lTimerID);
	ACE_INT32 deleteTimer(long lTimerID);
	//void doTimeout(long lTimerID);

private:
	TIMER_SET m_tTimerSet;
	//SERVICE_TIMER_OBJ_MAP m_ObjMap;
	ACE_Recursive_Thread_Mutex m_mutex;

	//TIMER_HANDLER_MAP m_handlerMap;
};

typedef ACE_Singleton<TimerMgr, ACE_Thread_Mutex> TIMER_MGR_INSTANCE;