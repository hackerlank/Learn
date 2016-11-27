#ifndef BASE_SYNC_THREAD_H
#define BASE_SYNC_THREAD_H
#include "baseThread.h"
#include "baseTaskContainer.h"
#include "baseTcpTask.h"
#include <list>
class TcpTaskPool;
class SyncThread : public Thread,public TaskQueue<TcpTask>
{
	private:
		typedef std::list<TcpTask*,__gnu_cxx::__pool_alloc<TcpTask*> > TcpTaskContainer;
		typedef TcpTaskContainer::iterator TcpTask_IT;
		static const DWORD s_maxTaskSize = 65534;
		TcpTaskPool *m_pool;
		TcpTaskContainer m_taskContainer;
		void _add(TcpTask *task);
	public:
		SyncThread() : Thread("同步线程")
		{
			m_pool = NULL;
		}
		~SyncThread()
		{
		}
		DWORD taskSize() const;
		DWORD maxTaskSize() const;
		void initParam(void *param);
		void run();
};

#endif

