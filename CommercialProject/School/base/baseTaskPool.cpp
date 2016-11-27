#include "baseTaskPool.h"
QWORD TcpTaskPool::s_usleepTime = 50000L;
DWORD TcpTaskPool::getSize()
{
	return m_okayThreads.taskCount();
}

bool TcpTaskPool::addVerify(TcpTask *task)
{
	VerifyThread *pThread = m_verifyThreads.getOne();
	if(pThread)
	{
		task->getNextState();
		pThread->add(task);
	}
	return true;
}

bool TcpTaskPool::addSync(TcpTask *task)
{
	SyncThread *pThread = m_syncThreads.getOne();
	if(pThread)
	{
		task->getNextState();
		pThread->add(task);
	}
	return true;
}
bool TcpTaskPool::addOkay(TcpTask *task)
{
	OkayThread *pThread = m_okayThreads.getOne();
	if(pThread)
	{
		task->getNextState();
		pThread->add(task);
		return true;
	}
	return false;
}
void TcpTaskPool::addRecycle(TcpTask *task)
{
	RecycleThread *pThread = m_recycleThreads.getOne();
	if(pThread)
	{
		pThread->add(task);
	}
}
bool TcpTaskPool::init()
{
	LogErrorCheckCondition(m_recycleThreads.init(1,1,"RecycleThread",this),false,"任务线程池回收线程初始化失败");
	LogErrorCheckCondition(m_verifyThreads.init(1,8,"VerifyThreads",this),false,"任务线程池认证线程初始化失败"); 	
	LogErrorCheckCondition(m_syncThreads.init(1,1,"SyncThread",this),false,"任务线程池同步线程初始化失败");
	
	DWORD maxThreadCount = (m_maxConnect+OkayThread::getMaxSize()-1)/OkayThread::getMaxSize();
	
	LogErrorCheckCondition(m_okayThreads.init(1,maxThreadCount,"OkayThread",this),false,"任务线程池处理线程初始化失败");
	return true;
}
void TcpTaskPool::final()
{
	m_verifyThreads.final();
	m_syncThreads.final();
	m_okayThreads.final();
	m_recycleThreads.final();
}


