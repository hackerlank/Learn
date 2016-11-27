#ifndef RECORD_TASK_MANAGER_H
#define RECORD_TASK_MANAGER_H

#include "base/baseTaskManager.h"
#include "base/baseTaskQueueManager.h"
#include "base/baseClass.h"
#include "recordTask.h"

class RecordTaskManager : public TaskQueueManager<RecordTask>,public SingletonBase<RecordTaskManager>
{
	private:
		friend class SingletonBase<RecordTaskManager>;
		RecordTaskManager() {}
		~RecordTaskManager() {}
};

#endif
