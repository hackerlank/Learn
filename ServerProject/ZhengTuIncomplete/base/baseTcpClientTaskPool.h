#ifndef BASE_TCP_CLIENT_TASK_POOL_H
#define BASE_TCP_CLIENT_TASK_POOL_H

#include "baseClass.h"
#include "baseThreadManager.h"
#include "baseCheckWaitThread.h"
#include "baseCheckConnectThread.h"
#include "baseTcpClientThread.h"

class TcpClientTaskPool : private Noncopyable
{
	public:
		explicit TcpClientTaskPool(const DWORD maxConCnt = 20,const QWORD us = 50000L) : m_maxConCnt(maxConCnt)
		{
			setUsleep( us );
		}
		
		~TcpClientTaskPool()
		{
		}
		
		bool init(const DWORD proThreadSize = 20);
		void final();
		const SDWORD getTotalSize()
		{
			return m_clientTaskThread.taskCount();
		}
		bool put(TcpClientTaskBase *task);
		void addCheckWait(TcpClientTaskBase *task);
		bool addMain(TcpClientTaskBase *task);
		void setUsleep(const QWORD usTime)
		{
			m_usleepTime = usTime;
		}
	private:
		const DWORD m_maxConCnt;
		TaskThreadManager<CheckConnectThread> m_checkConnectThread;
		TaskThreadManager<CheckWaitThread> m_checkWaitThread;
		TaskThreadManager<TcpClientTaskThread> m_clientTaskThread;
	public:
		QWORD m_usleepTime;
};

#endif


