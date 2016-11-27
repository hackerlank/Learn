#ifndef BASE_TCP_TASK_POOL_H
#define BASE_TCP_TASK_POOL_H
#include "baseThreadManager.h"
#include "baseSyncThread.h"
#include "baseVerifyThread.h"
#include "baseOkayThread.h"
#include "baseRecycleThread.h"
class TcpTaskPool : private Noncopyable
{
	public:
		explicit TcpTaskPool(const DWORD maxConnect,const QWORD us = 50000) : m_maxConnect(maxConnect)
		{
			setUsleepTime(us);
		}
		~TcpTaskPool()
		{
			final();
		}
		DWORD getSize();
		bool addVerify(TcpTask *task);
		bool addSync(TcpTask *task);
		bool addOkay(TcpTask *task);
		void addRecycle(TcpTask *task);
		static void setUsleepTime(const QWORD time)
		{
			s_usleepTime = time;
		}
		bool init();
		void final();
	private:
		const DWORD m_maxConnect;
		TaskThreadManager<VerifyThread> m_verifyThreads;
		TaskThreadManager<SyncThread> m_syncThreads;
		TaskThreadManager<OkayThread> m_okayThreads;
		TaskThreadManager<RecycleThread> m_recycleThreads;
	public:
		static QWORD s_usleepTime;
};

#endif
