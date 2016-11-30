#include "ObjTaskInterface.h"
#include "..\Service\ServiceObj.h"
//#include "RootObj.h"

ObjTaskInterface::ObjTaskInterface()
{
	m_unTaskID = OBJ_ID_NONE;
	m_owner = NULL;
	m_unStep = 0;
	setTimerout(OBJ_TASK_TIMEOUT);
	resetTimer();
}

ObjTaskInterface::~ObjTaskInterface()
{
	
}

void ObjTaskInterface::setTimerout(ACE_UINT32 unTimerout)
{
	m_unTimerout = unTimerout;

}

int ObjTaskInterface::advanceTimer()
{
	if(m_unTimer >= m_unTimerout)
	{
		task_timeout();
		return 0;
	}

	m_unTimer ++;

	return 1;
}

void ObjTaskInterface::resetTimer()
{
	m_unTimer = 0;
}

int ObjTaskInterface::task_run(MessageInfo &msgInfo)
{
	return 0;
}

void ObjTaskInterface::setTaskInfo(ACE_UINT32 unTaskID, ServiceObj *owner)
{
	m_unTaskID = unTaskID;
	m_owner = owner;
}

int ObjTaskInterface::initTask(char *arg)
{
	

	return 0;
}

void ObjTaskInterface::task_timeout()
{

}