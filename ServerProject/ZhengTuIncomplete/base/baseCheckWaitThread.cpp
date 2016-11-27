#include "baseCheckWaitThread.h"
#include "baseTcpClientTaskPool.h"

void CheckWaitThread::_add(TcpClientTaskBase *task)
{
	task->addEpoll(m_kdpfd,EPOLLIN|EPOLLERR|EPOLLPRI,(void*)task);
	m_taskContainer.push_back(task);
	_size = m_taskContainer.size();
	m_taskCount = m_taskContainer.size();
	if(_size > m_epfds.size())
	{
		m_epfds.resize(_size + 16);
	}
}

void CheckWaitThread::remove(TcpClientTaskBase *task)
{
	task->delEpoll(m_kdpfd,EPOLLIN|EPOLLPRI|EPOLLERR);
	m_taskContainer.remove(task);
	_size = m_taskContainer.size();
	m_taskCount = m_taskContainer.size();
}
void CheckWaitThread::remove(TcpClientTaskBase_IT &it)
{
	(*it)->delEpoll(m_kdpfd,EPOLLIN|EPOLLPRI|EPOLLERR);
	m_taskContainer.erase( it );
	_size = m_taskContainer.size();
	m_taskCount = m_taskContainer.size();
}
CheckWaitThread::CheckWaitThread() : Thread("验证线程")
{
	m_taskCount = 0;
	m_kdpfd = epoll_create(256);
	assert(-1 != m_kdpfd);
	m_epfds.resize(256);
}
DWORD CheckWaitThread::taskSize() const
{
	return m_taskCount + _size;
}
DWORD CheckWaitThread::maxTaskSize() const
{
	return s_maxConCnt;
}
void CheckWaitThread::initParam(void *param)
{
	m_pool = (TcpClientTaskPool*)param;
}
void CheckWaitThread::run()
{
	TcpClientTaskBase_IT it,next;
	while(!isFinal())
	{
		this->setRuning();
		Thread::sleep(1);
		check_queue();
		if(!m_taskContainer.empty())
		{
			int retcode = epoll_wait(m_kdpfd,&m_epfds[0],m_taskCount,0);
			if(retcode > 0)
			{
				for(int i = 0;i < retcode;++i)
				{
					TcpClientTaskBase *task = (TcpClientTaskBase*)m_epfds[i].data.ptr;
					if(m_epfds[i].events & (EPOLLERR | EPOLLPRI))
					{
						remove(task);
						task->resetState();
					}
					else if(m_epfds[i].events & EPOLLIN )
					{
				#if 0
						switch( task->checkRebound() )
						{
							case 1:
								{
									remove( task );
									if( pool->addMain( task ) )
									{
										task->resetState();
									}
									break;
								}
							case 0:
								break;
							case -1:
								{
									remove( task );
									task->resetState();
									break;
								}
						}
				#endif
					}
				}
			}
		}
		Time ct;
		for(it = m_taskContainer.begin(),next = it,next++;it != m_taskContainer.end();it = next,next++)
		{
			TcpClientTaskBase *task = *it;
		#if 0
			if( task->checkStateTimeout( TcpClientTaskBase::sync,ct,4 ) )
			{
				remove( it );
				task->resetState();
			}
		#endif
		}
		Thread::msleep( 50 );
	}
	for( it = m_taskContainer.begin(),next = it,next++;it != m_taskContainer.end();it = next,next++ )
	{
		TcpClientTaskBase *task = *it;
		remove( it );
		task->resetState();
	}
}



		
