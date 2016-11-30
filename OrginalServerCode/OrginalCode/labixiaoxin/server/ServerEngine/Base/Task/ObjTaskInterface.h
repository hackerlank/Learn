#pragma once

#include "..\Protocol\Protocol.h"
#include "ace\Containers.h"

#define OBJ_TASK_TIMEOUT 10

class ServiceObj;

class ObjTaskInterface : public ACE_DLList_Node
{
public:
	ObjTaskInterface();
	virtual ~ObjTaskInterface();

	void setTaskInfo(ACE_UINT32 unTaskID, ServiceObj *owner);

	virtual int task_run(MessageInfo &msgInfo);
	virtual int initTask(char *arg);
	virtual void task_timeout();

	ACE_UINT32 m_unTaskID;

	void setTimerout(ACE_UINT32 unTimerout);
	int advanceTimer();
	void resetTimer();

protected:
	ServiceObj *m_owner;
private:
	ACE_UINT32 m_unStep;
	
	ACE_UINT32 m_unTimer;
	ACE_UINT32 m_unTimerout;
};