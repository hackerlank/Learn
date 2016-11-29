#include "stdafx.h"
#include "TimePointMgr.h"

//----------------------------
// CenterServer
//----------------------------

bool CTimePointMgr::_bInit = false;
STimePoint CTimePointMgr::_arrayTimePoint[eTimePointCount];
bool CTimePointMgr::_bRun = false;

static bool DailyCheck(time_t tNow, STimePoint& rTimePt)
{
	if(rTimePt.tLastTime == 0)
	{
		rTimePt.tLastTime = tNow;
		return false;
	}
	
	struct tm *pTm = localtime(&tNow);
	tm oTm = *pTm;
	oTm.tm_hour = rTimePt.hour;
	oTm.tm_min = rTimePt.min;
	oTm.tm_sec = rTimePt.sec;

	time_t tTarget = mktime(&oTm);
	if(tTarget < tNow && tTarget >= rTimePt.tLastTime)
	{
		rTimePt.tLastTime = tNow;
		return true;
	}

	return false;
}

bool CTimePointMgr::Init()
{
	for(int i = 0; i < (int)eTimePointCount; ++i)
	{
		_arrayTimePoint[(ETimePointType)i].pfnCheck = DailyCheck;
		_arrayTimePoint[(ETimePointType)i].SetDailyTargetTime(i, 0, 0);
		//plz reference **enum ETimePointType**
		/*if((ETimePointType)i == eTimePointDaily0)
		{
			_arrayTimePoint[(ETimePointType)i].pfnCheck = DailyCheck;
			_arrayTimePoint[(ETimePointType)i].SetDailyTargetTime(0, 0, 0);
		}
		else if((ETimePointType)i == eTimePointDaily1)
		{
			_arrayTimePoint[(ETimePointType)i].pfnCheck = DailyCheck;
			_arrayTimePoint[(ETimePointType)i].SetDailyTargetTime(1, 0, 0);
		}*/
	}

	assert(!_bInit);
	_bInit = true;

	return true;
}

void CTimePointMgr::Start()
{
	assert(!_bRun);
	if(!_bInit)
	{
		//assert(false);
		LOG_CRI << "CTimePointMgr Not Initialize!";
		return;
	}
	_bRun = true;
}

void CTimePointMgr::TimerCheck(time_t tNow)
{
	if(!_bRun)
		return;

	for(size_t i = 0; i < (size_t)eTimePointCount; ++i)
	{
		STimePoint& rTimePoint = _arrayTimePoint[(ETimePointType)i];
		assert(rTimePoint.pfnCheck);
		if(rTimePoint.pfnCheck(tNow, rTimePoint))
		{
			for(auto itr = rTimePoint.lstCallback.begin(); itr != rTimePoint.lstCallback.end(); ++itr)
			{
				Callback cb = *itr;
				
				if(cb)
					cb();
				else
				{
					assert(cb);
				}
			}
		}
	}
}

void CTimePointMgr::AddCallback(ETimePointType eType, Callback f)
{
	assert(eType >= eTimePointStart && eType < eTimePointCount && f);
	_arrayTimePoint[eType].lstCallback.push_back(f);
}
