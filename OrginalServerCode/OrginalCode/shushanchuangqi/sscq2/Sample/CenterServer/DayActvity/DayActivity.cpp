#include "DayActivity.h"
//#include "Player.h"
//#include "User.h"
#include "DayActivityMgr.h"
//#include "DayActProtS.h"
#include "RTime.h"

CDayActivity::CDayActivity(NDayActProt::EActType eType):
    _eType(eType),
    _dwActID(0),
    _dwAlarmTime(0),
    _dwReadyTime(0),
    _dwBeginTime(0),
    _dwEndTime(0)
{
}


void CDayActivity::UpdateState(time_t tNow)
{
    switch(_dwState)
    {
        case eDayActivityStatusInit:
        {
            //if(IsAlarmTime(tNow))
            // {
            //    OnAlarm();
            //    _dwAlarmTime = Time::Now();
            //    _dwState = eDayActivityStatusAlarm;
            //}
        }
        break;
        case eDayActivityStatusAlarm:
        {
            if(Time::Now() > _dwReadyTime)
            {
                OnReady();
            }
        }
        break;
        case eDayActivityStatusReady:
        {
            if(Time::Now() > _dwBeginTime)
            {
                OnBegin();
            }
        }
        break;
        case eDayActivityStatusProcess:
        {
            if(Time::Now() > _dwEndTime)
            {
               OnEnd();
            }
        }
        break;
    }
}

void CDayActivity::SetStatus(EDayActivityStatus eStatus)
{ 
    _dwState=eStatus; 
    //g_DayActProtS.SendClt_ActChangeNotify(NULL,0,GetActID(),eStatus);
}

UINT32 GetDayTimePoint(const STimerInfo& oTimerInfo)
{
    time_t tNow = Time::Now();
    struct tm *pTm = localtime(&tNow);
	tm oTm = *pTm;
	oTm.tm_hour = oTimerInfo.byHour;
	oTm.tm_min = oTimerInfo.byMinute;
    oTm.tm_sec = 0;

    return mktime(&oTm);

}

bool CDayActivity::OnAlarm()
{
    LOG_INF<<"CDayActivity::OnAlarm";

    SDayActExPtr pDayActEx = GetCFG();
    if(NULL == pDayActEx)
    {
        return false;
    }
    
    _dwAlarmTime = GetDayTimePoint(pDayActEx->oAlarmTime);
    _dwReadyTime = GetDayTimePoint(pDayActEx->oReadyTime);
    _dwBeginTime = GetDayTimePoint(pDayActEx->oBeginTime);
    _dwEndTime   = GetDayTimePoint(pDayActEx->oEndTime);
    SetStatus(eDayActivityStatusAlarm);

    _dwAlarmTimeSpan   = _dwReadyTime - _dwAlarmTime;
    _dwReadyTimeSpan   = _dwBeginTime - _dwReadyTime;
    _dwProcessTimeSpan = _dwEndTime   - _dwBeginTime;

    _dwParam = pDayActEx->_dwParam;

    return true;
}

UINT32 CDayActivity::GetParam() const
{
    SDayActExPtr pDayActEx = GetCFG();
    if(NULL == pDayActEx)
    {
        return 0;
    }
    return pDayActEx->_dwParam;
}

void CDayActivity::OnReady()
{
    LOG_INF<<"CDayActivity::OnReady";
    SetStatus(eDayActivityStatusReady);

}

void CDayActivity::OnBegin()
{
    LOG_INF<<"CDayActivity::OnBegin";
    SetStatus(eDayActivityStatusProcess);
}

void CDayActivity::OnEnd()
{
    LOG_INF<<"CDayActivity::OnEnd";
    SetStatus(eDayActivityStatusEnd);
}

//重置原始状态
void CDayActivity::ResetState()
{
    SetStatus(eDayActivityStatusInit);
}

//void CDayActivity::SetCFG(SDayActExPtr pDayActEx)
//{
//    _pDayActEx = pDayActEx;
//}

//const SDayActEx* CDayActivity::GetCFG()
//{
//    return _pDayActEx.get();
//
//}

SDayActExPtr CDayActivity::GetCFG() const
{
    return g_DayActivityMgr.GetDayActEx(_dwActID);

}
//单次触发事件
void CDayActivity::AddEvent(UINT32 dwEventID,UINT32 dwNextEventTime,UINT32 dwParam/*=0*/,string strParam/*=""*/)
{
    SActEvent tmpData;
    tmpData.dwEventID = dwEventID;
    tmpData.dwNextEventTime = dwNextEventTime;
    tmpData.dwCount = 1;
    tmpData.dwParam = dwParam;
    tmpData.strParam = strParam;
    _mapActEventData.insert(make_pair(dwEventID,tmpData));

}

//周期触发事件
void CDayActivity::AddPeriodEvent(UINT32 dwEventID,UINT32 dwNextEventTime,UINT32 dwCount,UINT32 dwPeriodTime,UINT32 dwParam/*=0*/,string strParam/*=""*/)
{
    SActEvent tmpData;
    tmpData.dwEventID = dwEventID;
    tmpData.dwNextEventTime = dwNextEventTime;
    tmpData.dwCount = dwCount;
    tmpData.dwPeriodTime = dwPeriodTime;
    tmpData.dwParam = dwParam;
    tmpData.strParam = strParam;
    _mapActEventData.insert(make_pair(dwEventID,tmpData));
}

void CDayActivity::UpdateEvent(time_t tNow)
{
    for(auto itr = _mapActEventData.begin();itr != _mapActEventData.end();)
    {
        auto itrInfo = itr;
        itr++;
        if(itrInfo->second.dwNextEventTime < tNow)
        {
            OnEvent(itrInfo->second);

           if(itrInfo->second.dwCount > 1)
           {
               itrInfo->second.dwCount -= 1;
               itrInfo->second.dwNextEventTime = tNow + itrInfo->second.dwPeriodTime;
           }
           else
           {
               _mapActEventData.erase(itrInfo);
           }
        }
    }
}
                                       
// 0表示清除全部事件
void CDayActivity::ClearEvent(UINT32 dwEventID /*= 0*/)
{
    if(0 == dwEventID)
    {
        _mapActEventData.clear();
    }

    auto itr = _mapActEventData.find(dwEventID);
    if(itr != _mapActEventData.end())
    {
        _mapActEventData.erase(itr);
    }
}
////////////////////////////////////////////////////////////////////
void CDayActEvent::OnAlarm()
{
    LOG_INF<<"CDayActEvent::OnAlarm : "<<_dwActType;

    CDayActivity* pAct = g_DayActivityMgr.GetDayActivity(_dwActType);
    if(pAct)
    {
        //pAct->SetCFG(_pDayActEx);
        pAct->SetActID(_dwActID);
        pAct->OnAlarm();
    }

}

bool CDayActEvent::IsOpenDay()
{
    time_t tTime = Time::Now();
    struct tm *pTm = localtime(&tTime);

    SDayActExPtr pDayActEx = GetCFG();
    if(NULL == pDayActEx)
    {
        return false;
    }

    if(pDayActEx->_Moth && pDayActEx->_Moth != pTm->tm_mon)
    {
        return false;
    }

    if(pDayActEx->_MothDay && pDayActEx->_MothDay != pTm->tm_mday)
    {
        return false;
    }

    if(pDayActEx->_WeekDay && pDayActEx->_WeekDay != (pTm->tm_wday+1)) //1表示周日2表示周1依次类推
    {
        return false;
    }
    return true;
}

bool CDayActEvent::IsAlarmTime(time_t tNow)
{

    if(!IsOpenDay())
    {
        return false;
    }
    
    struct tm *pTm = localtime(&tNow);

    SDayActExPtr pDayActEx = GetCFG();
    if(NULL == pDayActEx)
    {
        return false;
    }

    if(pDayActEx->oAlarmTime.byHour != pTm->tm_hour)
    {
        return false;
    }

    if(pDayActEx->oAlarmTime.byMinute != pTm->tm_min)
    {
        return false;
    }

    return true;
}

void CDayActEvent::CheckStatus()
{
    if(!IsOpenDay())
    {
        return;
    }

    SDayActExPtr pDayActEx = GetCFG();
    if(NULL == pDayActEx)
    {
        return;
    }

    UINT32 dwAlarmTime = GetDayTimePoint(pDayActEx->oAlarmTime);
    UINT32 dwReadyTime = GetDayTimePoint(pDayActEx->oReadyTime);
    UINT32 dwEndTime   = GetDayTimePoint(pDayActEx->oEndTime);

    //LOG_DBG << "CheckStatus:" <<_dwActID << " " << dwAlarmTime << " | " << dwEndTime << " | " << Time::Now();
    
    //alarm 阶段
    if(Time::Now() > dwAlarmTime && Time::Now() < dwReadyTime)
    {
        CDayActivity* pAct = g_DayActivityMgr.GetDayActivity(_dwActType);
        if(pAct)
        {
            pAct->SetActID(_dwActID);
            pAct->OnAlarm();
            return;
        }
    }

    //process阶段
    if(Time::Now() > dwReadyTime && Time::Now() < dwEndTime)
    {
        CDayActivity* pAct = g_DayActivityMgr.GetDayActivity(_dwActType);
        if(pAct)
        {
            pAct->SetActID(_dwActID);
            pAct->OnReBegin();
        }
    }
}

void CDayActEvent::GMOpen()
{
    CDayActivity* pAct = g_DayActivityMgr.GetDayActivity(_dwActType);
    if(pAct)
    {
        //pAct->SetCFG(_pDayActEx);
        pAct->SetActID(_dwActID);
        pAct->GMOpen();
    }
}

SDayActExPtr CDayActEvent::GetCFG()
{
    return g_DayActivityMgr.GetDayActEx(_dwActID);
}
