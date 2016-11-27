#include "sceneTimeTick.h"
#include "flyer.h"
#include "taskManager.h"
#include "sceneServer.h"

Time SceneTimeTick::s_time;

SceneTimeTick::SceneTimeTick() : Thread("服务器时间线程"),m_secClock(1000),m_minClock(60*1000),m_hourClock(60*60*1000),m_halfHourClock(30*60*1000)
{
}

void SceneTimeTick::run()
{
    while(!isFinal())
    {
        s_time.now();
        if(m_hourClock(s_time))
        {
            char fileName[100] = {0};
            snprintf(fileName,sizeof(fileName),"log/scene-%02u.log",SceneServer::getInstance().getServerID());
            Flyer::changeLogger(fileName,s_time.sec());
        }
        if(m_minClock(s_time))
        {
            TaskManager::getInstance().sendHeartMsg();
        }
        msleep(atol(Flyer::globalConfMap["timeticksleep"].c_str()));
    }
}

