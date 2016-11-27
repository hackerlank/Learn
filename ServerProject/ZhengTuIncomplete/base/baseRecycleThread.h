#ifndef BASE_RECYCLE_THREAD_H
#define BASE_RECYCLE_THREAD_H
#include "baseThread.h"
#include "baseLock.h"
#include "baseTcpTask.h"
#include "baseTaskContainer.h"
#include <list>
class TcpTaskPool;

class RecycleThread : public Thread,public TaskQueue<TcpTask>
{
	private:
		typedef std::list<TcpTask*,__gnu_cxx::__pool_alloc<TcpTask*> > TcpTaskContainer;
		typedef TcpTaskContainer::iterator TcpTask_IT;

		static const int max_task_size = 65534;
		TcpTaskPool *pool;
		TcpTaskContainer tasks;
		void _add(TcpTask *task);
	public:
		RecycleThread():Thread("回收线程")
		{
			pool = NULL;
		}
		~RecycleThread() {};
		int taskSize() const;
		int maxTaskSize() const;
		void initParam(void *param);
		void run();
};

#endif
