
#include "GodMonsterMgr.h"

void CGodMonsterMgr::OnBegin()
{
    LOG_INF<<"GodMonster OnBegin.";
    SetState(eBegin);
}

void CGodMonsterMgr::OnEnd()
{
    LOG_INF<<"GodMonster OnEnd.";
    SetState(eEnd);
    
    //发邮件
    OnMail();
}

void CGodMonsterMgr::OnAlarm()
{
    LOG_INF<<"GodMonster OnAlarm.";
    SetState(eAlarm);
}

void CGodMonsterMgr::TimerCheck(time_t tNow)
{
    if(_bInit)
    {
        //开机检测
        //TODO
        _bInit = false;
    }
    UpdateState();
}

void CGodMonsterMgr::UpdateState()
{
    switch(_eState)
    {
        case eNone:
             if(time(NULL) >= _dwAlarmTime)
                 OnAlarm();
             break;
        case eAlarm:
              if(time(NULL) >= _dwBeginTime)
                 OnBegin();
            break;
        case eBegin:
             if(time(NULL) >= _dwEndTime)
                OnEnd();
            break;
        case eEnd:
            _eState = eNone;
            break;
        default:
            break;
    }
}

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */

