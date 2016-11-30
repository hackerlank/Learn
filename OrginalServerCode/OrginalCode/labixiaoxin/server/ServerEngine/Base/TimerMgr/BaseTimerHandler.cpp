#include "BaseTimerHandler.h"

BaseTimerHandler::BaseTimerHandler(void *owner, Timer_Callback_Func callback)
{
	m_lTimerID = -1;
	m_owner = owner;
	m_callback = callback;
}

BaseTimerHandler::~BaseTimerHandler()
{
	printf("timer handler delete = %d\n", m_lTimerID);
}

int BaseTimerHandler::handle_timeout(const ACE_Time_Value & , const void *arg)
{
	//ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);
	if(m_callback != NULL)
	{
		(*m_callback)(m_owner, m_lTimerID);
	}

	return 0;
}

void BaseTimerHandler::clear()
{
	//ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);
	m_callback = NULL;
	m_owner = NULL;
}

int BaseTimerHandler::handle_close(ACE_HANDLE handle, ACE_Reactor_Mask close_mask)
{
	//ACE_Guard<ACE_Recursive_Thread_Mutex> guard(m_mutex);
	//remove from 
	printf("close handler = %d\n", m_lTimerID);
	delete this;

	return 0;
}
