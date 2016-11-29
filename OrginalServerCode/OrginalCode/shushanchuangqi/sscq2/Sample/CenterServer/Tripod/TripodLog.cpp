#include "stdafx.h"

#include "TripodLog.h"
#include "SysMsgDefine.h"
#include "Protocols.h"
#include "RTime.h"

CTripodLog::CTripodLog(UINT64 qwRoleID):
    _qwRoleID(qwRoleID), _wMsgID(0), _dwTime(0)
{
}

CTripodLog::~CTripodLog()
{
}

bool CTripodLog::GetAllInfo(STripodLog& rInfo) const
{
    rInfo.qwRoleID  = _qwRoleID;
    rInfo.wMsgID    = _wMsgID;
    rInfo.vecParam  = _vecParam;
    rInfo.vecString = _vecString;
    rInfo.dwTime    = _dwTime;
    return true;
}

bool CTripodLog::InitFromDB(const STripodLog& rInfo)
{
    _qwRoleID  = rInfo.qwRoleID ;
    _wMsgID    = rInfo.wMsgID   ;
    _vecParam  = rInfo.vecParam ;
    _vecString = rInfo.vecString;
    _dwTime    = rInfo.dwTime   ;
    return true;
}

UINT64 CTripodLog::GetRoleID() const
{
    return _qwRoleID;
}

UINT16 CTripodLog::GetID() const
{
    return _wMsgID;
}

bool CTripodLog::FormatParam(UINT16 wMsgID, const TVecINT64& rvecParam, const TVecString& rvecString, UINT32 dwTime)
{
    _wMsgID         = wMsgID;
    _vecParam       = rvecParam;
    _vecString      = rvecString;
    if (!dwTime)
        _dwTime     = Time::Now();
    else
        _dwTime     = dwTime;
    return true;
}

void CTripodLog::Update2DB(CTripodLogPtr pTripodLog)
{
    STripodLog sLogInfo;
    if (pTripodLog)
    {
        pTripodLog->GetAllInfo(sLogInfo);
        //string strData;
        //COutArchive iar(strData);
        //iar << sLogInfo;
        g_Center2DBCommC.Send_UpdateTripodLog(pTripodLog->GetRoleID(), eOpAdd, sLogInfo);
    }
}

CTripodHelpLog:: CTripodHelpLog(UINT64 qwRoleID):
    CTripodLog(qwRoleID)
{
}

CTripodHelpLog::~CTripodHelpLog()
{
}

ETripodLogType CTripodHelpLog::GetType() const
{
    return eTripodLogHelp;
}

