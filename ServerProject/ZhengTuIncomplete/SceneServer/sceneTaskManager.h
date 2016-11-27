#ifndef SECENE_TASK_MANAGER_H
#define SECENE_TASK_MANAGER_H

#include "base/baseTaskManager.h"
#include "base/baseTaskQueueManager.h"
#include "base/baseClass.h"
#include "sceneTask.h"

class SceneTaskManager : public TaskQueueManager<SceneTask>,public SingletonBase<SceneTaskManager>
{
	private:
		friend class SingletonBase<SceneTaskManager>;
		SceneTaskManager() {}
		~SceneTaskManager() {}
};

#endif
