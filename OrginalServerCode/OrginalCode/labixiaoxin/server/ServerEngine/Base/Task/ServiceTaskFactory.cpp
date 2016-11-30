#include "ServiceTaskFactory.h"

ServiceTaskFactory::ServiceTaskFactory()
{

}

ServiceTaskFactory::~ServiceTaskFactory()
{

}

int ServiceTaskFactory::registerTask(char *taskName, OBJ_TASK_INTERFACE_CREATE func)
{
	ACE_CString str(taskName);
	
	if(m_FuncMap.bind(str, func) != 0)
	{
		return -1;
	}

	return 0;
}

int ServiceTaskFactory::unregisterTask(char *taskName)
{
	ACE_CString str(taskName);

	if(m_FuncMap.unbind(str) != 0)
	{
		return -1;
	}

	return 0;
}

ObjTaskInterface *ServiceTaskFactory::createTask(char *taskName)
{
	ACE_CString str(taskName);

	OBJ_TASK_INTERFACE_CREATE func = NULL;

	if(m_FuncMap.find(str, func) != 0)
	{
		return NULL;
	}

	return (*func)();
}