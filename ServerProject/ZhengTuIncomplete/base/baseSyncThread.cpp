#include "baseSyncThread.h"
#include "baseTaskPool.h"
void SyncThread::_add(TcpTask *task)
{
	m_taskContainer.push_front(task);
}
DWORD SyncThread::taskSize() const
{
	return 1;
}
void SyncThread::initParam(void *param)
{
	m_pool = (TcpTaskPool*)param;
}
DWORD SyncThread::maxTaskSize() const
{
	return s_maxTaskSize;
}
void SyncThread::run()
{
	TcpTask_IT it;
	while(!isFinal())
	{
		this->setRuning();
		check_queue();
		if(!m_taskContainer.empty())
		{
			for(it = m_taskContainer.begin();it != m_taskContainer.end();)
			{
				TcpTask *task = *it;
				switch(task->waitSync())
				{
					case 1:
						{
							it = m_taskContainer.erase(it);
							if(!m_pool->addOkay(task))
							{
								task->resetState();
								m_pool->addRecycle(task);
							}
							Cmd::ServerNullCmd cmd;
							if(task->sendCmd(&cmd,sizeof(cmd)))
							{
								task->setTick();
							}
						}
						break;
					case 0:
						{
							it++;
						}
						break;
					case -1:
						{
							it = m_taskContainer.erase(it);
							task->resetState();
							m_pool->addRecycle(task);
						}
						break;
				}
			}
		}
		Thread::msleep(200);
	}
	for(it = m_taskContainer.begin();it != m_taskContainer.end();)
	{
		TcpTask *task = *it;
		it = m_taskContainer.erase(it);
		task->resetState();
		m_pool->addRecycle(task);
	}
}

	


