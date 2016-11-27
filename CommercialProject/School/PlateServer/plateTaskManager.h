#ifndef PLATE_TASK_MANAGER_H
#define PLATE_TASK_MANAGER_H

#include "base/baseTaskManager.h"
#include "base/baseTaskQueueManager.h"
#include "base/baseClass.h"

class PlateTask;
class PlateTaskManager : public TaskQueueManager<PlateTask>,public SingletonBase<PlateTaskManager>
{
	private:
		friend class SingletonBase<PlateTaskManager>;
		PlateTaskManager() {}
		~PlateTaskManager() {}
	public:
		/// @brief 判断服务器类型是否有依赖关系
		const bool checkDependence(const WORD serverType);
};

#endif
