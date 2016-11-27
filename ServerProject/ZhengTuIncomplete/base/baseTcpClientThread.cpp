#include "baseTcpClientThread.h"
#include "baseTcpClientTaskPool.h"

DWORD TcpClientTaskThread::s_maxConCnt = 20;
TcpClientTaskThread::TcpClientTaskThread() : Thread( "工作线程" )
{
	m_taskCount = 0;
	m_kdpfd = epoll_create( s_maxConCnt );
	assert( -1 != m_kdpfd );
	m_epfds.resize( s_maxConCnt );
}

void TcpClientTaskThread::setMaxSize( DWORD perThreadSize )
{
	s_maxConCnt = perThreadSize;
}

int TcpClientTaskThread::getMaxSize()
{
	return s_maxConCnt;
}
int TcpClientTaskThread::taskSize() const
{
	return m_taskCount + _size;
}
int TcpClientTaskThread::maxTaskSize() const
{
	return s_maxConCnt;
}
void TcpClientTaskThread::initParam( void *param )
{
	m_pool = (TcpClientTaskPool*)param;
}
void TcpClientTaskThread::_add( TcpClientTaskBase *task )
{
	task->addEpoll( m_kdpfd,EPOLLIN | EPOLLERR | EPOLLPRI,(void*)task );
	m_taskContainer.push_back( task );
	if( m_taskCount > m_epfds.size() )
	{
		m_epfds.resize( m_taskCount + 16 );
	}
}
void TcpClientTaskThread::remove( TcpClientTaskBase_IT &it )
{
	(*it)->delEpoll( m_kdpfd,EPOLLIN | EPOLLOUT | EPOLLERR | EPOLLPRI );
	m_taskContainer.erase( it );
	m_taskCount = m_taskContainer.size();
}
void TcpClientTaskThread::run()
{
	TcpClientTaskBase_IT it,next;
	Time currentTime;
	Time _write_time;
	
	int kdpfd_r;
	EpollfdContainer epfds_r;
	kdpfd_r = epoll_create(256);
	assert( -1 != kdpfd_r );
	epfds_r.resize( 256 );
	DWORD fds_count_r = 0;
	bool check = false;
	while( !isFinal() )
	{
		currentTime.now();
		this->setRuning();
		if( check )
		{
			check_queue();
			if( !m_taskContainer.empty() )
			{
				for( it = m_taskContainer.begin(),next = it,next++;it != m_taskContainer.end();it = next,next++ )
				{
					TcpClientTaskBase *task = *it;
					if( task->isTerminate() )
					{
						if( task->isFdsrAdd() )
						{
							task->delEpoll( kdpfd_r,EPOLLIN | EPOLLPRI );
							fds_count_r -= 1;
						#if 0
							task->fdsrAdd( false );
						#endif
						}
						remove( it );
						task->getNextState();
					}
					else
					{
					#if 0
						if( task->checkFirstMainLoop() )
						{
							task->ListeningRecv( false );
						}
					#endif
						if( !task->isFdsrAdd() )
						{
							task->addEpoll(kdpfd_r,EPOLLIN | EPOLLERR | EPOLLPRI,(void*)task);
						#if 0
							task->fdsrAdd(true);
						#endif
							fds_count_r += 1;
							if(fds_count_r > epfds_r.size() )
							{
								epfds_r.resize(fds_count_r + 16 );
							}
						}
					}
				}
			}
			check = false;
		}
		Thread::msleep(2);
		if(fds_count_r)
		{
			int retcode = epoll_wait(kdpfd_r,&epfds_r[0],fds_count_r,0);
			if(retcode > 0 )
			{
				for(int i = 0;i < retcode;++i)
				{
					TcpClientTaskBase *task = (TcpClientTaskBase*)epfds_r[i].data.ptr;
					if(epfds_r[i].events & (EPOLLERR | EPOLLPRI ) )
					{
					#if 0
						task->Terminate(TcpClientTaskBase::TM_sock_error );
					#endif
						check = true;
					}
					else
					{
						if(epfds_r[i].events & EPOLLIN )
						{
						#if 0
							if( !task->ListeningRecv(true) )
							{
								task->Terminate( TcpClientTaskBase::TM_sock_error );
								check = true;
							}
						#endif
						}
					}
					epfds_r[i].events = 0;
				}
			}
		}
		if( check )
		{
			continue;
		}
		if( currentTime.msec() - _write_time.msec() >= (unsigned long)(m_pool->m_usleepTime/1000) )
		{
			_write_time = currentTime;
			if(!m_taskContainer.empty() )
			{
				int retcode = epoll_wait(m_kdpfd,&m_epfds[0],m_taskCount,0);
				if(retcode)
				{
					for(int i=0;i < retcode;i++ )
					{
						TcpClientTaskBase *task = (TcpClientTaskBase*)m_epfds[i].data.ptr;
						if(m_epfds[i].events & (EPOLLERR | EPOLLPRI ) )
						{
						#if 0
							task->Terminate(TcpClientTaskBase::TM_sock_error);
						#endif
						}
						else
						{
							if(m_epfds[i].events & EPOLLIN )
							{
							#if 0
								if(!task->ListeningRecv(true))
								{
									task->Terminate(TcpClientTaskBase::TM_sock_error );
								}
							#endif
							}
							if(m_epfds[i].events & EPOLLOUT)
							{
								if(!task->listeningSend())
								{
								#if 0
									task->Terminate(TcpClientTaskBase::TM_sock_error );
								#endif
								}
							}
						}
						m_epfds[i].events = 0;
					}
				}
			}
			check = true;
		}
	}
	for(it = m_taskContainer.begin(),next = it,next++;it != m_taskContainer.end();it = next,next++)
	{
		TcpClientTaskBase *task = *it;
		remove(it);
		task->getNextState();
	}
}


