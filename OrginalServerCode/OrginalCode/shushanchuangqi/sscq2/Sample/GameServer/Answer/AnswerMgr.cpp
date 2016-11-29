
#include "stdafx.h"
#include "Protocols.h"
#include "DayActProt.h"
#include "AnswerMgr.h"

CAnswerMgr::CAnswerMgr()
    :CDayActivity(eActTypeAnswer)
{
}

CAnswerMgr::~CAnswerMgr()
{}

void CAnswerMgr::OnBegin()
{
    CDayActivity::OnBegin();
}

bool CAnswerMgr::OnAlarm()
{
    CDayActivity::OnAlarm();
    LOG_WRN << "CAnswerMgr::OnAlarm()";
    return true;
}

void CAnswerMgr::OnReady()
{
    CDayActivity::OnReady();
}

void CAnswerMgr::OnEnd()
{
    CDayActivity::OnEnd();
}

bool CAnswerMgr::GMOpen()
{
    //TODO
    return true;
}

void CAnswerMgr::OnEvent(SActEventData& oSActEventData)
{
    switch(oSActEventData.dwEventID)
    {
        default:
            break;
    }
}

void CAnswerMgr::UpdateState(time_t tNow)
{
    CDayActivity::UpdateState(tNow);
}

void CAnswerMgr::ResetState()
{
}

void CAnswerMgr::OnReBegin()
{ 

    LOG_WRN <<" Answer Server ReBegin!";
    OnAlarm();
}

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

