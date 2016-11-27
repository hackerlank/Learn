#include "timeTick.h"
#include "flyer.h"
#include "taskManager.h"

Time TimeTick::s_time;

TimeTick::TimeTick() : Thread("服务器时间线程"),m_secClock(1000),m_minClock(60*1000),m_hourClock(60*60*1000),m_halfHourClock(30*60*1000)
{
}

void TimeTick::run()
{
    while(!isFinal())
    {
        s_time.now();
        unsigned long now = s_time.sec();
        if(m_halfHourClock(s_time))
        {
            char fileName[100] = {0};
            tm *localTime = localtime((time_t*)&now);
            snprintf(fileName,sizeof(fileName),"log/server.log-%02d-%02d-%02d-%02d-%02d.log",localTime->tm_year + 1900,localTime->tm_mon + 1,localTime->tm_mday,localTime->tm_hour,localTime->tm_min);
            LOG4CXX_INFO(Flyer::logger,fileName);
            Flyer::setLogger(fileName);
        }
        if(m_minClock(s_time))
        {
            TaskManager::getInstance().randOpDB(TaskManager::getInstance().size()/2);
        }
    }
}

