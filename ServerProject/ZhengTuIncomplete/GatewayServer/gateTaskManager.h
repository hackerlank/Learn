#ifndef GATE_TASK_MANAGER_H
#define GATE_TASK_MANAGER_H

#include "base/baseTaskManager.h"
#include "base/baseTaskQueueManager.h"
#include "base/baseClass.h"
#include "gateTask.h"

class GateTaskManager : public TaskQueueManager<GateTask>,public SingletonBase<GateTaskManager>
{
	private:
		friend class SingletonBase<GateTaskManager>;
		GateTaskManager() {}
		~GateTaskManager() {}
};

#endif
