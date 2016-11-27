#include "sceneTimeTick.h"
#include "flyer.h"
#include "taskManager.h"
#include "sceneServer.h"
#include "sceneUserManager.h"

Time SceneTimeTick::s_time;

SceneTimeTick::SceneTimeTick() : Thread("服务器时间线程"),m_secClock(1000),m_minClock(60*1000),m_hourClock(60*60*1000),m_halfHourClock(30*60*1000),m_tenSecClock(10*1000),m_heartClock(1.0*atol(Flyer::globalConfMap["hearttime"].c_str())/(atol(Flyer::globalConfMap["heartcycle"].c_str())*2)*1000)
{
}

void SceneTimeTick::run()
{
    unsigned int cycle = 0;
    unsigned int cycleTotal = atol(Flyer::globalConfMap["heartcycle"].c_str());
    while(!isFinal())
    {
        s_time.now();
        if(m_secClock(s_time))
        {
            if(s_time.sec() % (60 * 60) == 0)
            {
                char fileName[100] = {0};
                snprintf(fileName,sizeof(fileName),"log/scene-%02u.log",SceneServer::getInstance().getServerID());
                Flyer::changeLogger(fileName,s_time.sec());
            }
            if(m_tenSecClock(s_time))
            {
                SceneUserManager::getInstance().loop();
            }
        }
        if(m_heartClock(s_time))
        {
            TaskManager::getInstance().sendHeartMsg(cycle);
            cycle += 1;
            cycle %= cycleTotal; 
        }
        ClientThread::getInstance().doCmd(); 
        msleep(atol(Flyer::globalConfMap["threadsleep"].c_str()));
    }
}

