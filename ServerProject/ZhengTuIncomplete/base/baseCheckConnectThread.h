#ifndef BASE_CHECK_CONNECT_THREAD_H
#define BASE_CHECK_CONNECT_THREAD_H

#include <iostream>
using namespace std;
#include <sys/epoll.h>
#include <list>

#include "baseThread.h"
#include "baseTaskContainer.h"
#include "baseTcpClientTask.h"

class TcpClientTaskPool;
class CheckConnectThread : public Thread,public TaskQueue<TcpClientTaskBase>
{
	private:
		typedef std::list<TcpClientTaskBase*,__gnu_cxx::__pool_alloc<TcpClientTaskBase*> > TcpClientTaskBaseContainer;
		typedef TcpClientTaskBaseContainer::iterator TcpClientTaskBase_IT;
		typedef std::queue<TcpClientTaskBase*,std::deque<TcpClientTaskBase*,__gnu_cxx::__pool_alloc<TcpClientTaskBase*> > > TcpClientTaskBaseQueue;
		typedef std::vector<epoll_event> EpollfdContainer;
		TcpClientTaskBaseContainer m_taskContainer;
		TcpClientTaskPool *m_pool;
		static const DWORD s_maxConCnt = 4096;
	public:
		CheckConnectThread() : Thread("连接检查线程")
		{
			
		}
		void _add(TcpClientTaskBase *task);
		DWORD taskSize() const;
		DWORD maxTaskSize() const;
		void initParam( void *param );
		virtual void run();
};

#endif
