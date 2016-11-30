#pragma once

#include "ace\ace.h"
//#include "ace\Time_Value.h"
#include "ace\Event_Handler.h"
#include "ace\Mutex.h"
//#include "..\..\ace\Recursive_Thread_Mutex.h"

typedef void (*Timer_Callback_Func)(void *, long);

class BaseTimerHandler : public ACE_Event_Handler
{
public:
	BaseTimerHandler(void *owner, Timer_Callback_Func callback);
	virtual ~BaseTimerHandler();

	virtual int handle_timeout(const ACE_Time_Value & , const void *arg);
	virtual int handle_close(ACE_HANDLE handle, ACE_Reactor_Mask close_mask);

	void clear();

	long m_lTimerID;

private:
	//ACE_Recursive_Thread_Mutex m_mutex;

	void *m_owner;
	Timer_Callback_Func m_callback;
};