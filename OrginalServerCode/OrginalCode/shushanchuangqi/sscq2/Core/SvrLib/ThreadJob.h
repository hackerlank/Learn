#pragma once
#include <functional>
#include <vector>
#include <memory>
#include <atomic>
#include <boost/lockfree/queue.hpp>
#include "Platform.h"

using namespace std;

typedef function<void()> FnThreadJob;
typedef function<void()> FnJobResult;

struct SJobInfo;
struct SThreadInfo;
typedef shared_ptr<SThreadInfo> SThreadInfoPtr;

//将工作分发到其它线程(非逻辑线程)中运行
class CThreadJobHandler
{
public:
	CThreadJobHandler() : _queResult(128), _dwResCount(0), _tLastCheckTime(0), _bRun(false) { assert(_queResult.is_lock_free()); }
	~CThreadJobHandler() { Stop(); }
	bool Start(UINT32 dwThrdCnt = 1);
	void Stop();
	bool IsRunning() const { return _bRun; }

	//fnThrdJob: 在别的线程中运行的函数
	//FnJobResult: 在主逻辑线程中获取结果的函数
	//dwThrdIdx: 线程的编号
	bool DoThreadJob(FnThreadJob fnThrdJob, FnJobResult fnResult = nullptr, UINT32 dwThrdIdx = 0);
	UINT32 GetJobCount(UINT32 dwIndex) const;
	bool ProcessResult();
protected:
	static void JobThread(CThreadJobHandler* pThis, UINT32 dwThrdIdx);
	void CheckQueueLength();

	vector<SThreadInfoPtr> _vecThrdInfo;
	boost::lockfree::queue<SJobInfo*> _queResult;
	atomic<INT32> _dwResCount;
	time_t _tLastCheckTime;
	bool _bRun;
};