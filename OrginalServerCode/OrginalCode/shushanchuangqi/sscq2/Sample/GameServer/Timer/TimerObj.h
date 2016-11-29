#pragma once

class CTimerObj
{
public:
	CTimerObj();
	bool HasException() const { return _bHasException; }
	void SetException(bool bHasException) { _bHasException = bHasException; }
	virtual void OnTimerException();
	virtual bool CanTimerCheck();
	static bool NotifyException(bool bHandleNow = true);
	static void ClearCurObj();
protected:
	static CTimerObj* _pCurTimerObj;
	bool _bHasException;
};

class CAutoCheck
{
public:
	CAutoCheck(CTimerObj& rTimerObj) : _rTimerObj(rTimerObj) { }
	operator bool() { return _rTimerObj.CanTimerCheck(); }
	~CAutoCheck() { CTimerObj::ClearCurObj(); }
protected:
	CTimerObj& _rTimerObj;
};