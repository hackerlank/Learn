#ifndef SUPER_TASK_MANAGER_H
#define SUPER_TASK_MANAGER_H

#include "base/baseTaskManager.h"
#include "base/baseTaskQueueManager.h"
#include "base/baseClass.h"

class SuperTask;
class SuperTaskManager : public TaskQueueManager<SuperTask>,public SingletonBase<SuperTaskManager>
{
	private:
		friend class SingletonBase<SuperTaskManager>;
		SuperTaskManager() {}
		~SuperTaskManager() {}
	public:
		/// @brief 判断服务器类型是否有依赖关系
		const bool checkDependence(const WORD serverType);
};

#endif
