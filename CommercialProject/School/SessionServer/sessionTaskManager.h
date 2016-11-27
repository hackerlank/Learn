#ifndef SESSION_TASK_MANAGER_H
#define SESSION_TASK_MANAGER_H

#include "base/baseTaskManager.h"
#include "base/baseTaskQueueManager.h"
#include "base/baseClass.h"
#include "sessionTask.h"

class SessionTaskManager : public TaskQueueManager<SessionTask>,public SingletonBase<SessionTaskManager>
{
	private:
		friend class SingletonBase<SessionTaskManager>;
		SessionTaskManager() {}
		~SessionTaskManager() {}
};

#endif
