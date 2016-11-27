#include "baseCheckConnectThread.h"
#include "baseTcpClientTaskPool.h"

void CheckConnectThread::_add(TcpClientTaskBase *task)
{
	m_taskContainer.push_back(task);
}

DWORD CheckConnectThread::taskSize() const
{
	return m_taskContainer.size();
}
DWORD CheckConnectThread::maxTaskSize() const
{
	return s_maxConCnt;
}

void CheckConnectThread::initParam(void *param)
{
	m_pool = (TcpClientTaskPool *)param;
}

void CheckConnectThread::run()
{
	while(!isFinal())
	{
		this->setRuning();
		Thread::sleep(1);
		Time ct;
		check_queue();
		for(TcpClientTaskBase_IT it = m_taskContainer.begin();it != m_taskContainer.end();)
		{
			TcpClientTaskBase *task = *it;
			switch(task->getState())
			{
			#if 0
				case TcpClientTaskBase::close:
					{
					#if 0
						if( !task->checkStateTimeout( TcpClientTaskBase::close,ct,4 ) )
						{
							if( task->connect() )
							{
								m_pool->addCheckWait( task );
							}
							else if( !task->needReConn() )
							{
								TcpClientTaskBase_IT temp = it;
								++it;
								m_taskContainer.erase( temp );
								task->resetState();
								SAFE_DELETE( task );
								continue;
							}
						}
					}
					#endif
					break;
				case TcpClientTaskBase::sync:
					break;
				case TcpClientTaskBase::okay:
					task->checkConn();
					break;
				case TcpClientTaskBase::recycle:
					#if 0
					if( task->checkStateTimeout( TcpClientTaskBase::recycle,ct,4 ) )
					{
						task->getNextState();
						if( !task->needReConn() )
						{
							TcpClientTaskBase_IT temp = it;
							++it;
							m_taskContainer.erase( temp );
							SAFE_DELETE( task );
							continue;
						}
					}
				#endif
				break;
			#endif
			}
			++it;
		}
	}
}
