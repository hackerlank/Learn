#ifndef BASE_TCP_CLIENT_TASK_THREAD_H
#define BASE_TCP_CLIENT_TASK_THREAD_H

#include <iostream>
using namespace std;
#include <sys/epoll.h>
#include <list>

#include "baseThread.h"
#include "baseTaskContainer.h"
#include "baseTcpClientTask.h"

class TcpClientTaskPool;
class TcpClientTaskThread : public Thread, public TaskQueue<TcpClientTaskBase>
{
	private:
		typedef std::list<TcpClientTaskBase*,__gnu_cxx::__pool_alloc<TcpClientTaskBase*> > TcpClientTaskBaseContainer;
		typedef TcpClientTaskBaseContainer::iterator TcpClientTaskBase_IT;
		typedef std::queue<TcpClientTaskBase*,std::deque<TcpClientTaskBase*,__gnu_cxx::__pool_alloc<TcpClientTaskBase*> > > TcpClientTaskBaseQueue;
		typedef std::vector<epoll_event> EpollfdContainer;
		static DWORD s_maxConCnt;
		TcpClientTaskPool *m_pool;
		TcpClientTaskBaseContainer m_taskContainer;
		TcpClientTaskBaseContainer::size_type m_taskCount;
		int m_kdpfd;
		EpollfdContainer m_epfds;
		void _add(TcpClientTaskBase *task);
		void remove(TcpClientTaskBase_IT &it);
	public:
		TcpClientTaskThread();
		~TcpClientTaskThread()
		{
			TEMP_FAILURE_RETRY( ::close( m_kdpfd ) );
		}
		static int getMaxSize();
		static void setMaxSize( DWORD perThreadSize );
		int taskSize() const;
		int maxTaskSize() const;
		void initParam( void *param );
		virtual void run();
};
#endif
