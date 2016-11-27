#ifndef BASE_CHECK_WAIT_THREAD_H
#define BASE_CHECK_WAIT_THREAD_H

#include <iostream>
using namespace std;
#include <sys/epoll.h>
#include <list>

#include "baseThread.h"
#include "baseTaskContainer.h"
#include "baseTcpClientTask.h"

class TcpClientTaskPool;
class CheckWaitThread : public Thread,public TaskQueue<TcpClientTaskBase>
{
	private:
		typedef std::list<TcpClientTaskBase*,__gnu_cxx::__pool_alloc<TcpClientTaskBase*> > TcpClientTaskBaseContainer;
		typedef TcpClientTaskBaseContainer::iterator TcpClientTaskBase_IT;
		typedef std::queue<TcpClientTaskBase*,std::deque<TcpClientTaskBase*,__gnu_cxx::__pool_alloc<TcpClientTaskBase*> > > TcpClientTaskBaseQueue;
		typedef std::vector<epoll_event> EpollfdContainer;
		static const DWORD s_maxConCnt = 4096;
		TcpClientTaskPool *m_pool;
		TcpClientTaskBaseContainer m_taskContainer;
		TcpClientTaskBaseContainer::size_type m_taskCount;
		SDWORD m_kdpfd;
		EpollfdContainer m_epfds;
		void _add(TcpClientTaskBase *task);
		void remove(TcpClientTaskBase *task);
		void remove( TcpClientTaskBase_IT &it );
	public:
		CheckWaitThread();
		~CheckWaitThread()
		{
			TEMP_FAILURE_RETRY(::close(m_kdpfd));
		}
		DWORD taskSize() const;
		DWORD maxTaskSize() const;
		void initParam( void *param );
		virtual void run();
};

#endif
