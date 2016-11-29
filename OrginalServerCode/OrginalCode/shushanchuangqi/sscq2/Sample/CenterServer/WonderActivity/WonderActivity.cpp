#include  "WonderActivity.h"
#include <time.h>
#include "WonderActivityMgr.h"
#include "RTime.h"
#include "Protocols.h"
#include "SysMsgDefine.h"
#include "UserMgr.h"
#include "RankMgr.h"

UINT32 GetDayTime(const SWActTime& oTimerInfo)
{
    struct tm  t_tm;
	UINT32 year = oTimerInfo.wYear;
    UINT32 mon = oTimerInfo.byMonth;
    UINT32 day = oTimerInfo.byDay;
    UINT32 hour = oTimerInfo.byHour;
    UINT32 min  = oTimerInfo.byMin;
    t_tm.tm_year = year - 1900;
    t_tm.tm_mon = mon - 1;
    t_tm.tm_mday = day;
    t_tm.tm_hour = hour;
    t_tm.tm_min = min;
    t_tm.tm_sec = 0;
    time_t t2 = mktime(&t_tm);
    return t2; 
    //return Time::MkTime(year,mon,day,hour,min);
}

CWonderActivity::CWonderActivity(UINT16 wActType):_wActType(wActType)
{
    _wActID = 0;
    _dwAdvanceTime = 0;
    _dwBeginTime = 0;
    _dwEndTime = 0;
    _dwRetainTime = 0;
    _eActState = eWActState_Init; 
}

void CWonderActivity::UpdateState()
{
   switch(_eActState)
   {
       case eWActState_Init:
           {
              //if(time(NULL) > _dwAdvanceTime)
               //   OnAdvance();
           }
           break;
       case eWActState_Advance:
           {
               if(time(NULL) > _dwBeginTime)
                   OnBegin();
           }
           break;
       case eWActState_Begin:
           {
               //活动开始后 作弊行为
               SpecialProcess();

               if(time(NULL) > _dwEndTime)
                   OnEnd();
           }
           break;
       case eWActState_End:
           {
               if(time(NULL) > _dwRetainTime)
                   OnRetain();
           }
           break;
       case eWActState_Retain:
           {
               //预留
           }
           break;

   }
}
void CWonderActivity::SpecialProcess()
{
}

void CWonderActivity::OnAdvance()
{
    SetState(eWActState_Advance);
}
void CWonderActivity::OnBegin()
{
    SetState(eWActState_Begin);
    g_GlobalChatProtS.SendClt_SystemFormatMsgIDNotify(NULL,0,eMsgActivityOperatingBegin,BuildStrVec(GetActName()));
}
void CWonderActivity::OnEnd()
{
    SetState(eWActState_End);
    g_GlobalChatProtS.SendClt_SystemFormatMsgIDNotify(NULL,0,eMsgActivityOperatingEnd,BuildStrVec(GetActName()));
}

void CWonderActivity::OnRetain()
{
    SetState(eWActState_Retain);
}

bool CWonderActivity::OnInit()
{
    SWActCFGExPtr pActEx = GetCFG();
    if(NULL == pActEx)
    {
        return false;
    }
    _dwAdvanceTime = GetDayTime(pActEx->sAdvanceTime);
    _dwBeginTime = GetDayTime(pActEx->sBeginTime);
    _dwEndTime = GetDayTime(pActEx->sEndTime);
    _dwRetainTime   = GetDayTime(pActEx->sRetainTime);
    _wCfgID = pActEx->wCfgID;
    OnAdvance();
    return true;
}
string CWonderActivity::GetActName()
{
    string sRet = "";
    SWActCFGExPtr pActEx = GetCFG();
    if(pActEx)
    {
        sRet = pActEx->_Name;
    }
    return sRet;
}
void CWonderActivity::OnReRetain()
{
    SWActCFGExPtr pActEx = GetCFG();
    if(NULL == pActEx)
    {
        return ;
    }
    _dwAdvanceTime = GetDayTime(pActEx->sAdvanceTime);
    _dwBeginTime = GetDayTime(pActEx->sBeginTime);
    _dwEndTime = time(NULL);
    _dwRetainTime  = GetDayTime(pActEx->sRetainTime);
    _wCfgID = pActEx->wCfgID;

    SetState(eWActState_End);
    OpenIcon(false);
}

void CWonderActivity::OnReBegin()
{
    SWActCFGExPtr pActEx = GetCFG();
    if(NULL == pActEx)
    {
        return ;
    }
    _dwAdvanceTime = GetDayTime(pActEx->sAdvanceTime);
    _dwBeginTime = time(NULL);
    _dwEndTime = GetDayTime(pActEx->sEndTime);
    _dwRetainTime   = GetDayTime(pActEx->sRetainTime);
    _wCfgID = pActEx->wCfgID;
    SetState(eWActState_Begin);
    OpenIcon(false);

}
void CWonderActivity::OnReAdvance()
{
    SWActCFGExPtr pActEx = GetCFG();
    if(NULL == pActEx)
    {
        return ;
    }
    _dwAdvanceTime = time(NULL);
    _dwBeginTime = GetDayTime(pActEx->sBeginTime);
    _dwEndTime = GetDayTime(pActEx->sEndTime);
    _dwRetainTime   = GetDayTime(pActEx->sRetainTime);
    _wCfgID = pActEx->wCfgID;

    OnAdvance();
}
void  CWonderActivity::GMOpen(SWActTime& sAdv,SWActTime sBegin,SWActTime sEnd,SWActTime sRetain)
{
    LOG_INF<<"CWonderActivity::GMOpen";
    OnAdvance();
    SWActCFGExPtr pActEx = GetCFG();
    if(NULL == pActEx)
    {
        return;
    }
    _dwAdvanceTime = GetDayTime(sAdv);
    _dwBeginTime = GetDayTime(sBegin); 
    _dwEndTime = GetDayTime(sEnd); 
    _dwRetainTime   = GetDayTime(sRetain); 
    _wCfgID = pActEx->wCfgID;
}

bool CWonderActivity::OnMail()
{
    SWActConfigCFGPtr pCfgPtr = g_WonderActivityMgr.GetPrizeConfig(_wCfgID);
    if(pCfgPtr == NULL)
    {
        LOG_INF << " ActivityPrizeConfig NULL " ;
        return false;
    }
   UINT16 wTitleID = pCfgPtr->wMailID;
   UINT16 wContentID = pCfgPtr->wMailContentID;
   TVecPrizeCFGPtr vecPrize = pCfgPtr->vecWActPrizePtr;
   for(auto oIt=vecPrize.begin(); oIt!=vecPrize.end(); ++oIt)
   {
       SendMail((*oIt)->wHigh,(*oIt)->wLow,(*oIt)->vecItem,wTitleID,wContentID);
   }
   return true;
}

SWActCFGExPtr CWonderActivity::GetCFG()
{
    return g_WonderActivityMgr.GetConfigEx(_wActID);
}

void CWonderActivity::GetConds(TVecUINT32& vecConds)
{
    SWActConfigCFGPtr pCfgPtr = g_WonderActivityMgr.GetPrizeConfig(_wCfgID);
    if(pCfgPtr == NULL)
    {
        return;
    }
    TVecPrizeCFGPtr vecPrize = pCfgPtr->vecWActPrizePtr;
   for(auto oIt=vecPrize.begin(); oIt!=vecPrize.end(); ++oIt)
   {
        UINT32 wConds_ =  (*oIt)->wHigh;
        vecConds.push_back(wConds_);
   }

}

TVecItemConfigPtr s_vecItem;

TVecItemConfigPtr CWonderActivity::GetPrize(UINT32 wConds)
{
    SWActConfigCFGPtr pCfgPtr = g_WonderActivityMgr.GetPrizeConfig(_wCfgID);
    if(pCfgPtr == NULL)
    {
        LOG_INF << " ActivityPrizeConfig NULL " ;
    }
    TVecPrizeCFGPtr vecPrize = pCfgPtr->vecWActPrizePtr;
    for(auto oIt=vecPrize.begin(); oIt!=vecPrize.end(); ++oIt)
    {
        UINT32 wConds_ =  (*oIt)->wHigh;
        if(wConds_ == wConds)
        {
            return (*oIt)->vecItem;
        }
    }
    return s_vecItem;
}

UINT32 CWonderActivity::GetMaxRoleCount(UINT32 wCond)
{
    SWActConfigCFGPtr pCfgPtr = g_WonderActivityMgr.GetPrizeConfig(_wCfgID);
    if(pCfgPtr == NULL)
    {
        LOG_INF << " ActivityPrizeConfig NULL " ;
        return 0;
    }
    TVecPrizeCFGPtr vecPrize = pCfgPtr->vecWActPrizePtr;
   for(auto oIt=vecPrize.begin(); oIt!=vecPrize.end(); ++oIt)
   {
        UINT32 wConds_ =  (*oIt)->wHigh;
        if(wConds_ == wCond)
        {
            return (*oIt)->wLow;
        }
   }
   return 0;

}
////////////////////////////////////////////////////////////////////
void CWonderActivityEvent::OnInit()
{
    CWonderActivity* pAct = g_WonderActivityMgr.GetWAct(_wActType);
    if(pAct)
    {
        pAct->SetActID(_wActID);
        pAct->OnInit();
    }
}

void CWonderActivityEvent::CheckStatus()
{
    SWActCFGExPtr pActEx = GetCFG();
    if(NULL == pActEx)
    {
        LOG_CRI << "pActEx NULL";
        return ;
    }
    
    UINT32 dwAdvanceTime = GetDayTime(pActEx->sAdvanceTime);
    UINT32 dwBeginTime = GetDayTime(pActEx->sBeginTime);
    UINT32 dwEndTime = GetDayTime(pActEx->sEndTime);
    UINT32 dwRetainTime = GetDayTime(pActEx->sRetainTime);
   
    CWonderActivity* pAct = g_WonderActivityMgr.GetWAct(_wActType);
    if(pAct == NULL)
    {
        return ;
    }
    // LOG_INF << _wActID << ": " <<dwAdvanceTime << " | " << dwBeginTime << " | " << dwEndTime << " | " << time(NULL);
    if(time(NULL) > dwAdvanceTime 
       && time(NULL) < dwBeginTime)
    {
        pAct->SetActID(_wActID);
        pAct->OnReAdvance();
    }
    if(time(NULL) > dwBeginTime && time(NULL) < dwEndTime)
    {
        pAct->SetActID(_wActID);
        pAct->OnReBegin();
    }
    if(time(NULL) > dwEndTime && time(NULL) < dwRetainTime)
    {
        pAct->SetActID(_wActID);
        pAct->OnReRetain();
    }

}

bool CWonderActivityEvent::IsInitTime(time_t tNow)
{
    struct tm *pTm = localtime(&tNow);

    SWActCFGExPtr pWActCFGEx = GetCFG();
    if(NULL == pWActCFGEx)
    {
        return false;
    }
    if(pWActCFGEx->sAdvanceTime.wYear != (pTm->tm_year + 1900)
       || pWActCFGEx->sAdvanceTime.byMonth != (pTm->tm_mon + 1)
       || pWActCFGEx->sAdvanceTime.byDay != pTm->tm_mday
       || pWActCFGEx->sAdvanceTime.byHour != pTm->tm_hour
       || pWActCFGEx->sAdvanceTime.byMin != pTm->tm_min
       )
    {
        return false;
    }
    return true;
}
SWActCFGExPtr CWonderActivityEvent::GetCFG()
{
    return g_WonderActivityMgr.GetConfigEx(_wActID);
}

