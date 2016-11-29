#include "stdafx.h"
#include "TimePointMgr.h"

//----------------------------
// GameServer
//----------------------------

bool CTimePointMgr::_bInit = false;
STimePoint CTimePointMgr::_arTimePoint[eTimePointCount];
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
	for(size_t i = 0; i < (size_t)eTimePointCount; ++i)
	{
		// plz reference **enum ETimePointType**
		if((ETimePointType)i == eTimePointDaily0)
		{
			_arTimePoint[(ETimePointType)i].pfnCheck = DailyCheck;
			_arTimePoint[(ETimePointType)i].SetDailyTargetTime(0, 0, 0);
		}
		else if((ETimePointType)i == eTimePointDaily1)
		{
			_arTimePoint[(ETimePointType)i].pfnCheck = DailyCheck;
			_arTimePoint[(ETimePointType)i].SetDailyTargetTime(1, 0, 0);
		}
		else if((ETimePointType)i == eTimePointDaily2)
		{
			_arTimePoint[(ETimePointType)i].pfnCheck = DailyCheck;
			_arTimePoint[(ETimePointType)i].SetDailyTargetTime(2, 0, 0);
		}
		else if((ETimePointType)i == eTimePointDaily3)
		{
			_arTimePoint[(ETimePointType)i].pfnCheck = DailyCheck;
			_arTimePoint[(ETimePointType)i].SetDailyTargetTime(3, 0, 0);
		}
		else if((ETimePointType)i == eTimePointDaily4)
		{
			_arTimePoint[(ETimePointType)i].pfnCheck = DailyCheck;
			_arTimePoint[(ETimePointType)i].SetDailyTargetTime(4, 0, 0);
		}
		else if((ETimePointType)i == eTimePointDaily5)
		{
			_arTimePoint[(ETimePointType)i].pfnCheck = DailyCheck;
			_arTimePoint[(ETimePointType)i].SetDailyTargetTime(5, 0, 0);
		}
		else if((ETimePointType)i == eTimePointDaily6)
		{
			_arTimePoint[(ETimePointType)i].pfnCheck = DailyCheck;
			_arTimePoint[(ETimePointType)i].SetDailyTargetTime(6, 0, 0);
		}
		else if((ETimePointType)i == eTimePointDaily7)
		{
			_arTimePoint[(ETimePointType)i].pfnCheck = DailyCheck;
			_arTimePoint[(ETimePointType)i].SetDailyTargetTime(7, 0, 0);
		}
		else if((ETimePointType)i == eTimePointDaily8)
		{
			_arTimePoint[(ETimePointType)i].pfnCheck = DailyCheck;
			_arTimePoint[(ETimePointType)i].SetDailyTargetTime(8, 0, 0);
		}
		else if((ETimePointType)i == eTimePointDaily9)
		{
			_arTimePoint[(ETimePointType)i].pfnCheck = DailyCheck;
			_arTimePoint[(ETimePointType)i].SetDailyTargetTime(9, 0, 0);
		}
		else if((ETimePointType)i == eTimePointDaily10)
		{
			_arTimePoint[(ETimePointType)i].pfnCheck = DailyCheck;
			_arTimePoint[(ETimePointType)i].SetDailyTargetTime(10, 0, 0);
		}
		else if((ETimePointType)i == eTimePointDaily11)
		{
			_arTimePoint[(ETimePointType)i].pfnCheck = DailyCheck;
			_arTimePoint[(ETimePointType)i].SetDailyTargetTime(11, 0, 0);
		}
		else if((ETimePointType)i == eTimePointDaily12)
		{
			_arTimePoint[(ETimePointType)i].pfnCheck = DailyCheck;
			_arTimePoint[(ETimePointType)i].SetDailyTargetTime(12, 0, 0);
		}
		else if((ETimePointType)i == eTimePointDaily13)
		{
			_arTimePoint[(ETimePointType)i].pfnCheck = DailyCheck;
			_arTimePoint[(ETimePointType)i].SetDailyTargetTime(13, 0, 0);
		}
		else if((ETimePointType)i == eTimePointDaily14)
		{
			_arTimePoint[(ETimePointType)i].pfnCheck = DailyCheck;
			_arTimePoint[(ETimePointType)i].SetDailyTargetTime(14, 0, 0);
		}
		else if((ETimePointType)i == eTimePointDaily15)
		{
			_arTimePoint[(ETimePointType)i].pfnCheck = DailyCheck;
			_arTimePoint[(ETimePointType)i].SetDailyTargetTime(15, 0, 0);
		}
		else if((ETimePointType)i == eTimePointDaily16)
		{
			_arTimePoint[(ETimePointType)i].pfnCheck = DailyCheck;
			_arTimePoint[(ETimePointType)i].SetDailyTargetTime(16, 0, 0);
		}
		else if((ETimePointType)i == eTimePointDaily17)
		{
			_arTimePoint[(ETimePointType)i].pfnCheck = DailyCheck;
			_arTimePoint[(ETimePointType)i].SetDailyTargetTime(17, 0, 0);
		}
		else if((ETimePointType)i == eTimePointDaily18)
		{
			_arTimePoint[(ETimePointType)i].pfnCheck = DailyCheck;
			_arTimePoint[(ETimePointType)i].SetDailyTargetTime(18, 0, 0);
		}
		else if((ETimePointType)i == eTimePointDaily19)
		{
			_arTimePoint[(ETimePointType)i].pfnCheck = DailyCheck;
			_arTimePoint[(ETimePointType)i].SetDailyTargetTime(19, 0, 0);
		}
		else if((ETimePointType)i == eTimePointDaily20)
		{
			_arTimePoint[(ETimePointType)i].pfnCheck = DailyCheck;
			_arTimePoint[(ETimePointType)i].SetDailyTargetTime(20, 0, 0);
		}
		else if((ETimePointType)i == eTimePointDaily21)
		{
			_arTimePoint[(ETimePointType)i].pfnCheck = DailyCheck;
			_arTimePoint[(ETimePointType)i].SetDailyTargetTime(21, 0, 0);
		}
		else if((ETimePointType)i == eTimePointDaily22)
		{
			_arTimePoint[(ETimePointType)i].pfnCheck = DailyCheck;
			_arTimePoint[(ETimePointType)i].SetDailyTargetTime(22, 0, 0);
		}
		else if((ETimePointType)i == eTimePointDaily23)
		{
			_arTimePoint[(ETimePointType)i].pfnCheck = DailyCheck;
			_arTimePoint[(ETimePointType)i].SetDailyTargetTime(23, 0, 0);
		}
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
		assert(false);
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
		STimePoint& rTimePoint = _arTimePoint[(ETimePointType)i];
		assert(rTimePoint.pfnCheck);
		if(rTimePoint.pfnCheck(tNow, rTimePoint))
		{
			for(auto itr = rTimePoint.lstCallback.begin(); itr != rTimePoint.lstCallback.end(); ++itr)
			{
				Callback cb = *itr;
				
				if(cb)
					cb((ETimePointType)i);
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
	_arTimePoint[eType].lstCallback.push_back(f);
}
