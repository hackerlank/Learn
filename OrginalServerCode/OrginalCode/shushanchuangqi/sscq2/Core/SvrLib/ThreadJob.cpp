#include "ServerDefine.h"
#include "Thread.h"
#include "ThreadJob.h"
#include "NetMgr.h"

struct SJobInfo
{
	FnThreadJob fnThrdJob;
	FnJobResult fnResult;
	UINT32 dwThrdIdx;

	SJobInfo() : dwThrdIdx(0) { }
};

struct SThreadInfo
{
	CThread thrd;
	boost::lockfree::queue<SJobInfo*> queJob;
	atomic<INT32> dwJobCount;

	SThreadInfo() : queJob(128), dwJobCount(0) { assert(queJob.is_lock_free()); }
};

bool CThreadJobHandler::Start(UINT32 dwThrdCnt)
{
	_bRun = true;
	for(UINT32 i = 0; i < dwThrdCnt; ++i)
	{
		SThreadInfoPtr pThreadInfo(new SThreadInfo);
		if(pThreadInfo == NULL)
		{
			LOG_CRI << "pThreadInfo is NULL!";
			return false;
		}
		_vecThrdInfo.push_back(pThreadInfo);
	}
	for(UINT32 i = 0; i < dwThrdCnt; ++i)
	{
		SThreadInfoPtr pThreadInfo = _vecThrdInfo[i];
		if(!pThreadInfo->thrd.Start(CThreadJobHandler::JobThread, this, i))
		{
			LOG_CRI << "Start JobThread fails!";
			return false;
		}
	}
	return true;
}

void CThreadJobHandler::Stop()
{
	_bRun = false;
	for(auto& p : _vecThrdInfo)
		p->thrd.Join();
}

bool CThreadJobHandler::DoThreadJob(FnThreadJob fnThrdJob, FnJobResult fnResult /*= nullptr*/, UINT32 dwThrdIdx /*= 0*/)
{
	SJobInfo* pJobInfo = new SJobInfo;
	if(pJobInfo == NULL)
	{
		LOG_CRI << "pJobInfo is NULL!";
		return false;
	}
	pJobInfo->fnThrdJob = fnThrdJob;
	pJobInfo->fnResult = fnResult;
	if(dwThrdIdx >= _vecThrdInfo.size())
	{
		LOG_CRI << "Invalid dwThrdIdx: " << dwThrdIdx;
		return false;
	}
	SThreadInfoPtr pThreadInfo = _vecThrdInfo[dwThrdIdx];
	assert(pThreadInfo != NULL);
	if(!pThreadInfo->queJob.push(pJobInfo))
	{
		LOG_CRI << "queJob push fails!";
		return false;
	}
	++pThreadInfo->dwJobCount;
	CheckQueueLength();
	return true;
}

void CThreadJobHandler::JobThread(CThreadJobHandler* pThis, UINT32 dwThrdIdx)
{
	SThreadInfoPtr pThreadInfo = pThis->_vecThrdInfo[dwThrdIdx];
	assert(pThreadInfo != NULL);
	while(pThis->IsRunning() || !pThreadInfo->queJob.empty())
	{
		SJobInfo* pJobInfo = NULL;
		if(pThreadInfo->queJob.pop(pJobInfo))
		{
			--pThreadInfo->dwJobCount;
			if(pJobInfo->fnThrdJob)
				pJobInfo->fnThrdJob();
			if(pThis->_queResult.push(pJobInfo))
				++pThis->_dwResCount;
		}
		else
		{
			Sleep(1);
		}
	}
}

UINT32 CThreadJobHandler::GetJobCount(UINT32 dwIndex) const
{
	assert(dwIndex < _vecThrdInfo.size());
	auto& pThreadInfo = _vecThrdInfo[dwIndex];
	assert(pThreadInfo != NULL);
	return pThreadInfo->dwJobCount;
}

bool CThreadJobHandler::ProcessResult()
{
	SJobInfo* pJobInfo = NULL;
	if(_queResult.pop(pJobInfo))
	{
		--_dwResCount;
		if(pJobInfo->fnResult)
			pJobInfo->fnResult();
		delete pJobInfo;
		return true;
	}
	return false;
}

void CThreadJobHandler::CheckQueueLength()
{
	if(!_bRun)
		return;
	time_t tNow = time(NULL);
	if(tNow > _tLastCheckTime && tNow - _tLastCheckTime >= 10)
	{
		INT32 dwResCount = _dwResCount.load(memory_order_relaxed);
		if(dwResCount > 100)
			LOG_INF << "Result Queue Size: " << dwResCount;
		for(size_t i = 0; i < _vecThrdInfo.size(); ++i)
		{
			INT32 dwJobCount = _vecThrdInfo[i]->dwJobCount;
			if(dwJobCount > 500)
				LOG_INF << "Job Queue Size: " << dwJobCount << ", Index: " << i;
		}
		_tLastCheckTime = tNow;
	}
}