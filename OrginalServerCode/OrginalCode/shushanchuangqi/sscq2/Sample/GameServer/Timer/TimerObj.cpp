#include "stdafx.h"
#include "TimerObj.h"

CTimerObj* CTimerObj::_pCurTimerObj;

CTimerObj::CTimerObj() : _bHasException(false) { }

void CTimerObj::OnTimerException()
{
	LOG_CRI << "CTimerObj::OnTimerException";
}

bool CTimerObj::NotifyException(bool bHandleNow /*= true*/)
{
	if(_pCurTimerObj == NULL)
		return false;
	_pCurTimerObj->SetException(true);
	if(bHandleNow)
		_pCurTimerObj->OnTimerException();
	return true;
}

bool CTimerObj::CanTimerCheck()
{
	if(_bHasException)
	{
		OnTimerException();
		return false;
	}
	_pCurTimerObj = this;
	return true;
}

void CTimerObj::ClearCurObj()
{
	_pCurTimerObj = NULL;
}