#include "baseOkayThread.h"
#include "baseTaskPool.h"

void OkayThread::_add(TcpTask *task)
{
	task->addEpoll(m_kdpfd,EPOLLIN|EPOLLOUT|EPOLLERR|EPOLLPRI ,(void*)task);
	m_taskContainer.push_back(task);
	m_taskCount = m_taskContainer.size();
	if(m_taskCount > m_epollFdContainer.size())
	{
		m_epollFdContainer.resize(m_taskCount + 16);
	}
	task->listeningRecv(false);
}
void OkayThread::remove(TcpTask_IT &it)
{
	(*it)->delEpoll(m_kdpfd,EPOLLIN | EPOLLOUT | EPOLLERR | EPOLLPRI);
	it = m_taskContainer.erase(it);
	m_taskCount = m_taskContainer.size();
}
void OkayThread::initParam(void *param)
{
	m_pool = (TcpTaskPool*)param;
}
DWORD OkayThread::taskSize() const
{
	return m_taskCount + _size;
}
DWORD OkayThread::maxTaskSize() const
{
	return s_maxTaskSize;
}
void OkayThread::run()
{
	Time currentTime;
	Time writeTime;
	TcpTask_IT it;
	SDWORD kdpfd;
	EpollfdContainer epollFdContainer;
	kdpfd = epoll_create(256);
	assert(-1 != kdpfd);
	m_epollFdContainer.resize(256);
	DWORD countFd = 0;
	bool check = false;
	while(!isFinal())
	{
		this->setRuning();
		currentTime.now();
		if(check)
		{
			check_queue();
			if(!m_taskContainer.empty())
			{
				for(it = m_taskContainer.begin();it != m_taskContainer.end();)
				{
					TcpTask *task = *it;
					processChangeSocket(task,kdpfd);
					task->checkSignal(currentTime);
					processTerminate(it,task,kdpfd,countFd,epollFdContainer);
				}
			}
			check = false;
		}
		Thread::msleep(2);
		processCountFd(countFd,check,kdpfd,epollFdContainer);
		if(check)
		{
			continue;
		}
		if(currentTime.msec() - writeTime.msec() >= (QWORD)(m_pool->s_usleepTime/1000))
		{
			writeTime = currentTime;
			processMsg();
			check = true;
		}
	}
	for(it = m_taskContainer.begin();it != m_taskContainer.end();)
	{
		TcpTask *task = *it;
		remove(it);
		task->getNextState();
		m_pool->addRecycle(task);
	}
	TEMP_FAILURE_RETRY(::close(m_kdpfd));
}

void OkayThread::processCountFd(DWORD &countFd,bool &check,SDWORD &kdpfd,EpollfdContainer &epollFdContainer)
{
	CheckConditonVoid(countFd);
	SDWORD retcode = epoll_wait(kdpfd,&epollFdContainer[0],countFd,0);
	CheckConditonVoid(retcode);
	for(SDWORD index = 0;index < retcode;++index)
	{
		TcpTask *task = (TcpTask*)epollFdContainer[index].data.ptr;
		if(epollFdContainer[index].events & (EPOLLERR|EPOLLPRI))
		{
			task->TerminateError();
			task->Terminate(TcpTask::TM_ACTIVE);
			check = true;
		}
		else
		{
			if(epollFdContainer[index].events & EPOLLIN)
			{
				if(!task->listeningRecv(true))
				{
					task->Terminate(TcpTask::TM_ACTIVE);
					check = true;
				}	
			}
		}
		epollFdContainer[index].events = 0;
	}
}

void OkayThread::processTerminate(TcpTask_IT &it,TcpTask *task,SDWORD &kdpfd,DWORD &countFd,EpollfdContainer &epollFdContainer)
{
	if(task->isTerminateWait())
	{
		task->Terminate();
	}
	if(task->isTerminate())
	{
		if(task->isFdsrAdd())
		{
			task->delEpoll(kdpfd,EPOLLIN|EPOLLERR|EPOLLPRI);
			countFd -= 1;
		}
		remove(it);
		task->getNextState();
		m_pool->addRecycle(task);
	}
	else
	{
		if(!task->isFdsrAdd())
		{
			task->addEpoll(kdpfd,EPOLLIN | EPOLLERR | EPOLLPRI,(void*)task);
			task->fdsrAdd();
			countFd++;
			if(countFd > epollFdContainer.size())
			{
				epollFdContainer.resize(countFd + 16);
			}
		}
		++it;
	}
}

void OkayThread::processChangeSocket(TcpTask *task,SDWORD &kdpfd)
{
	CheckConditonVoid(task->m_mSocket.checkChangeSocket());
	if(task->isFdsrAdd())
	{
		task->delEpoll(kdpfd,EPOLLIN|EPOLLERR|EPOLLPRI);
	}
	task->delEpoll(m_kdpfd,EPOLLIN|EPOLLERR|EPOLLPRI);

	task->m_mSocket.changeSocket(0);
	if(task->isFdsrAdd())
	{
		task->addEpoll(kdpfd,EPOLLIN|EPOLLERR|EPOLLPRI,(void*)task);
	}
	task->addEpoll(m_kdpfd,EPOLLIN|EPOLLOUT|EPOLLERR|EPOLLPRI,(void*)task);

}

void OkayThread::processMsg()
{
	CheckConditonVoid(!m_taskContainer.empty());
	SDWORD retcode = epoll_wait(m_kdpfd,&m_epollFdContainer[0],m_taskCount,0);
	CheckConditonVoid(retcode>0);
	for(SDWORD index = 0;index < retcode;index++)
	{
		TcpTask *task = (TcpTask*)m_epollFdContainer[index].data.ptr;
		if(m_epollFdContainer[index].events & (EPOLLERR|EPOLLPRI))
		{
			task->TerminateError();
			task->Terminate(TcpTask::TM_ACTIVE);
		}
		else
		{
			if(m_epollFdContainer[index].events & EPOLLIN)
			{
				if(!task->listeningRecv(true))
				{
					task->Terminate(TcpTask::TM_ACTIVE);
				}
			}
			if(m_epollFdContainer[index].events & EPOLLOUT)
			{
				if(!task->listeningSend())
				{
					task->Terminate(TcpTask::TM_ACTIVE);
				}
			}
		}
		m_epollFdContainer[index].events = 0;
	}
}
				
