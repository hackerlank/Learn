#ifndef BASE_OKAY_THREAD_H
#define BASE_OKAY_THREAD_H
#include "baseThread.h"
#include "baseTaskContainer.h"
#include "baseTcpTask.h"
#include <list>
class TcpTaskPool;

class OkayThread : public Thread,public TaskQueue<TcpTask>
{
	private:
		typedef std::list<TcpTask*,__gnu_cxx::__pool_alloc<TcpTask*> > TcpTaskContainer;
		typedef TcpTaskContainer::iterator TcpTask_IT;
		typedef std::vector<epoll_event> EpollfdContainer;
		static const DWORD s_maxTaskSize = 512;
		TcpTaskPool *m_pool;
		TcpTaskContainer m_taskContainer;
		TcpTaskContainer::size_type m_taskCount;
		SDWORD m_kdpfd;
		EpollfdContainer m_epollFdContainer;
		void _add(TcpTask *task);
		void remove(TcpTask_IT &it);
		void processMsg();
		void processChangeSocket(TcpTask *task,SDWORD &kdpfd);
		 void processTerminate(TcpTask_IT &it,TcpTask *task,SDWORD &kdpfd,DWORD &countFd,EpollfdContainer &epollFdContainer);
		 void processCountFd(DWORD &countFd,bool &check,SDWORD &kdpfd,EpollfdContainer &epollFdContainer);
	public:
		OkayThread():Thread("工作线程")
		{
			m_pool = NULL;
			m_taskCount = 0;
			m_kdpfd = epoll_create(maxTaskSize());
			assert(-1 != m_kdpfd);
			m_epollFdContainer.resize(maxTaskSize());
		}
		~OkayThread()
		{
			TEMP_FAILURE_RETRY(::close(m_kdpfd));
		}
		static DWORD getMaxSize()
		{
			return s_maxTaskSize;
		}
		DWORD taskSize() const;
		DWORD maxTaskSize() const;
		void run();
		void initParam(void *param);
};

#endif

