#include "baseRecycleThread.h"
#include "baseTaskPool.h"
void RecycleThread::_add(TcpTask *task)
{
	tasks.push_front(task);
}
int RecycleThread::taskSize() const
{
	return 1;
}
void RecycleThread::initParam(void *param)
{
	pool = (TcpTaskPool*)param;
}
int RecycleThread::maxTaskSize() const
{
	return max_task_size;
}
void RecycleThread::run()
{
	TcpTask_IT it;
	while(!isFinal())
	{
		this->setRuning();
		check_queue();
		if(!tasks.empty())
		{
			for(it = tasks.begin();it != tasks.end();)
			{
				TcpTask *task = *it;
				switch(task->recycleConn())
				{
					case 1:
						{
							it = tasks.erase(it);
							if(task->isUnique())
							{
								task->uniqueRemove();
							}
							task->getNextState();
							DELETE(task);
						}
						break;
					case 0:
						{
							it++;
						}
						break;
				}
			}
		}
		Thread::msleep(200);
	}
	for(it = tasks.begin();it != tasks.end();)
	{
		TcpTask *task = *it;
		it = tasks.erase(it);
		if(task->isUnique())
		{
			task->uniqueRemove();
		}
		task->getNextState();
		DELETE(task);
	}
}
