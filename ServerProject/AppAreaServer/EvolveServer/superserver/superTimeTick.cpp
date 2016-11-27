#include "superTimeTick.h"
#include "flyer.h"
#include "taskManager.h"
#include "superServer.h"

Time SuperTimeTick::s_time;

SuperTimeTick::SuperTimeTick() : Thread("服务器时间线程"),m_secClock(1000),m_minClock(60*1000),m_hourClock(60*60*1000),m_halfHourClock(30*60*1000),m_heartClock(1.0*atol(Flyer::globalConfMap["hearttime"].c_str())/(atol(Flyer::globalConfMap["heartcycle"].c_str())*2)*1000)
{
}

void SuperTimeTick::run()
{
    unsigned int cycle = 0;
    unsigned int heartCycleTotal = atol(Flyer::globalConfMap["heartcycle"].c_str());
    while(!isFinal())
    {
        s_time.now();
        if(m_secClock(s_time))
        {
            if(s_time.sec() % (60 * 60) == 0)
            {
                char fileName[100] = {0};
                snprintf(fileName,sizeof(fileName),"log/super-%02u.log",SuperServer::getInstance().getServerID());
                Flyer::changeLogger(fileName,s_time.sec());
            }
        }
        if(m_heartClock(s_time))
        {
            TaskManager::getInstance().sendHeartMsg(cycle);
            cycle += 1;
            cycle %= heartCycleTotal; 
        }
        ClientThread::getInstance().doCmd();
        msleep(atol(Flyer::globalConfMap["threadsleep"].c_str()));
    }
}

