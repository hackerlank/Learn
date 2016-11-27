#include "baseVerifyThread.h"
#include "baseTaskPool.h"

void VerifyThread::_add(TcpTask *task)
{
	task->addEpoll(m_kdpfd,EPOLLIN | EPOLLERR | EPOLLPRI,(void*)task);
	m_taskContainer.push_back(task);
	if(m_taskCount > m_epollFdContainer.size())
	{
		m_epollFdContainer.resize(m_taskCount);
	}
	m_taskCount = m_taskContainer.size();
}

void VerifyThread::remove(TcpTask *task)
{
	task->delEpoll(m_kdpfd,EPOLLIN | EPOLLERR | EPOLLPRI);
	m_taskContainer.remove(task);
	m_taskCount = m_taskContainer.size();
}

void VerifyThread::remove(TcpTask_IT &it)
{
	(*it)->delEpoll(m_kdpfd,EPOLLIN | EPOLLERR | EPOLLPRI);
	it = m_taskContainer.erase(it);
	m_taskCount = m_taskContainer.size();
}
int VerifyThread::taskSize() const
{
	return m_taskCount + _size;
}
int VerifyThread::maxTaskSize() const
{
	return s_maxTaskSize;
}
void VerifyThread::initParam(void *param)
{
	m_pool = (TcpTaskPool*)param;
}

void VerifyThread::run()
{
	Time currentTime;
	TcpTask_IT it;
	while(!isFinal())
	{
		this->setRuning();
		currentTime.now();
		check_queue();
		if(!m_taskContainer.empty())
		{
			for(it = m_taskContainer.begin(); it != m_taskContainer.end();)
			{
				TcpTask *task = *it;
				if(task->m_mSocket.checkChangeSocket())
				{
					task->delEpoll(m_kdpfd,EPOLLIN|EPOLLERR|EPOLLPRI);
					task->m_mSocket.changeSocket(0);
					task->addEpoll(m_kdpfd,EPOLLIN | EPOLLERR | EPOLLPRI,(void*)task);
				}
				if(task->checkVerifyTimeout(currentTime))
				{
					remove(it);
					task->resetState();
					m_pool->addRecycle(task);
				}
				else
				{
					++it;
				}
			}
			SDWORD retcode = epoll_wait(m_kdpfd,&m_epollFdContainer[0],m_taskCount,0);
			if(retcode > 0)
			{
				for(SDWORD index = 0;index < retcode;index++)
				{
					TcpTask *task = (TcpTask*)m_epollFdContainer[index].data.ptr;
					if(m_epollFdContainer[index].events & EPOLLERR)
					{
						remove(task);
						task->resetState();
						m_pool->addRecycle(task);
					}
					else if(m_epollFdContainer[index].events & EPOLLIN)
					{
						switch(task->verifyConnect())
						{
							case 1:
								{
									remove(task);
									if(task->uniqueAdd())
									{
										task->setUnique();
										m_pool->addSync(task);
									}
									else
									{
										task->resetState();
										m_pool->addRecycle(task);
									}
								}
								break;
							case 0:
								break;
							case -1:
								{
									remove(task);
									task->resetState();
									m_pool->addRecycle(task);
								}
								break;
						}
					}
				}
			}
		}
		Thread::msleep(50);
	}
	for(it = m_taskContainer.begin();it != m_taskContainer.end();)
	{
		TcpTask *task = *it;
		remove(it);
		task->resetState();
		m_pool->addRecycle(task);
	}
}
							


