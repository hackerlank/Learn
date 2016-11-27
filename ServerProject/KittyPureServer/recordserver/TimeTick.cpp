/**
 * \file
 * \version  $Id: TimeTick.cpp 24 2013-03-30 08:04:25Z  $
 * \author  ，
 * \date 2006年12月27日 21时03分02秒 CST
 * \brief 存档定时器实现
 *
 * 
 */

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

#include "Fir.h"
#include "zThread.h"
#include "TimeTick.h"
#include "RecordUserManager.h"
#include "RecordTask.h"
#include "RecordServer.h"

zRTime RecordTimeTick::currentTime;

void RecordTimeTick::run()
{
    while(!isFinal())
    {
        zThread::msleep(50);

        //获取当前时间
        currentTime.now();

        if (_one_min(currentTime))
        {
            RecordService::getMe().save();
        }
        if(_one_sec(currentTime))
        {
            RecordUserM::getMe().saveplayer();
        }
    }
}

bool RecordTimeTick::isSameday(DWORD timer)
{
    DWORD now = currentTime.sec();
    struct tm tm_old,tm_now;
    zRTime::getLocalTime(tm_now, now);
    zRTime::getLocalTime(tm_old, timer);
    if(tm_old.tm_year != tm_now.tm_year || tm_old.tm_mon != tm_now.tm_mon || tm_old.tm_mday != tm_now.tm_mday)
    {
        return false;
    }
    return true;
}
