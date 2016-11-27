#ifndef BASE_VERIFY_THREAD_H
#define BASE_VERIFY_THREAD_H
#include "baseThread.h"
#include "baseTaskContainer.h"
#include "baseTcpTask.h"
#include <list>
class TcpTaskPool;

class VerifyThread : public Thread,public TaskQueue<TcpTask>
{
	private:
		typedef std::list<TcpTask*,__gnu_cxx::__pool_alloc<TcpTask*> > TcpTaskContainer;
		typedef TcpTaskContainer::iterator TcpTask_IT;
		typedef std::vector<struct epoll_event> EpollfdContainer;
		static const SDWORD s_maxTaskSize = 1024;
		TcpTaskPool *m_pool;
		TcpTaskContainer m_taskContainer;
		TcpTaskContainer::size_type m_taskCount;
		SDWORD m_kdpfd;
		EpollfdContainer m_epollFdContainer;
		void _add(TcpTask *task);
		void remove(TcpTask *task);
		void remove(TcpTask_IT &it);
	public:
		VerifyThread():Thread("验证线程")
		{
			m_pool = NULL;
			m_taskCount = 0;

			m_kdpfd = epoll_create(256);
			assert(-1 != m_kdpfd);
			m_epollFdContainer.resize(256);
		}
		~VerifyThread()
		{
			TEMP_FAILURE_RETRY(::close(m_kdpfd));
		}
		int taskSize() const;
		int maxTaskSize() const;
		void run();
		void initParam(void *param);
};


#endif
