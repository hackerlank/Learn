#pragma once

#include "ace\Singleton.h"
#include "ace\Containers.h"
#include "ace\Null_Mutex.h"
#include "ace\Hash_Map_Manager.h"
#include "ObjTaskInterface.h"
#include "ace\ace.h"
#include "ace\SString.h"

typedef ObjTaskInterface *(*OBJ_TASK_INTERFACE_CREATE)();

typedef ACE_Hash_Map_Manager_Ex<ACE_CString, OBJ_TASK_INTERFACE_CREATE, ACE_Hash<ACE_CString>, 
ACE_Equal_To<ACE_CString>, ACE_Null_Mutex> OBJ_TASK_FUNC_MAP;

class ServiceTaskFactory
{
public:
	ServiceTaskFactory();
	~ServiceTaskFactory();
	
	int registerTask(char *taskName, OBJ_TASK_INTERFACE_CREATE func);
	int unregisterTask(char *taskName);
	ObjTaskInterface *createTask(char *taskName);
private:
	OBJ_TASK_FUNC_MAP m_FuncMap;
};

typedef ACE_Singleton<ServiceTaskFactory, ACE_Thread_Mutex> SERVICE_TASK_FACTORY_INSTANCE;