#include "baseTcpClientTaskPool.h"

bool TcpClientTaskPool::put( TcpClientTaskBase *task )
{
	CheckConnectThread *pThread = m_checkConnectThread.getOne();
	if( pThread )
	{
		pThread->add( task );
	}
	return true;
}

bool TcpClientTaskPool::init( const DWORD preThreadSize )
{
	LogErrorCheckCondition( m_checkConnectThread.init(1,1,"CheckConnectThread",this),false,"连接检查线程池初始化失败" ); 
	LogErrorCheckCondition( m_checkWaitThread.init(1,1,"CheckWaitThread",this),false,"等待检查线程池初始化失败" ); 
	TcpClientTaskThread::setMaxSize( preThreadSize );
	SDWORD maxThreadCount = ( m_maxConCnt + TcpClientTaskThread::getMaxSize() - 1 ) / TcpClientTaskThread::getMaxSize();
	LogErrorCheckCondition( m_clientTaskThread.init(1,maxThreadCount,"ClientTaskThread",this),false,"客户端连接池初始化失败" );
	return true;
}
void TcpClientTaskPool::final()
{
	Global::logger->debug( "%s",__PRETTY_FUNCTION__  );
	m_checkConnectThread.final();
	m_checkWaitThread.final();
	m_clientTaskThread.final();
}

void TcpClientTaskPool::addCheckWait( TcpClientTaskBase *task )
{
	CheckWaitThread *pThread = m_checkWaitThread.getOne();
	if(pThread)
	{
		pThread->add(task);
		task->getNextState();
	}
}

bool TcpClientTaskPool::addMain( TcpClientTaskBase *task )
{
	TcpClientTaskThread *pThread = m_clientTaskThread.getOne();
	if( pThread )
	{
		pThread->add( task );
		task->getNextState();
		return true;
	}
	return false;
}
