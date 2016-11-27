#include "timeTick.h"
#include "flyer.h"
#include "client.h"
#include "taskManager.h"

Time TimeTick::s_time;

TimeTick::TimeTick() : Thread("客户端时间线程"),m_secClock(1000),m_minClock(60*1000),m_hourClock(60*60*1000),m_halfHourClock(30*60*1000)
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
            snprintf(fileName,sizeof(fileName),"log/client.log-%02d-%02d-%02d-%02d-%02d.log",localTime->tm_year + 1900,localTime->tm_mon + 1,localTime->tm_mday,localTime->tm_hour,localTime->tm_min);
            LOG4CXX_INFO(Flyer::logger,fileName);
            Flyer::setLogger(fileName);
        } 

        if(TaskManager::getInstance().size() <= 10)
        {
            for(int cnt = 0; cnt < 10;++cnt)
            {
                Client::getInstance().connectServer();
            }
        }
        TaskManager::getInstance().randSendMsg(TaskManager::getInstance().size() / 2);
        TaskManager::getInstance().randOpDB(TaskManager::getInstance().size()/2);
        //TaskManager::getInstance().randCloseFd(TaskManager::getInstance().size() / 10);
    }
}

