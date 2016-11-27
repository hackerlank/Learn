#include "gatewayTimeTick.h"
#include "flyer.h"
#include "taskManager.h"
#include "gatewayServer.h"

Time GatewayTimeTick::s_time;

GatewayTimeTick::GatewayTimeTick() : Thread("服务器时间线程"),m_secClock(1000),m_minClock(60*1000),m_hourClock(60*60*1000),m_halfHourClock(30*60*1000)
{
}

void GatewayTimeTick::run()
{
    while(!isFinal())
    {
        s_time.now();
        if(m_secClock(s_time))
        {
            if(s_time.sec() % (60 * 60) == 0)
            {
                char fileName[100] = {0};
                snprintf(fileName,sizeof(fileName),"log/gateway-%02u.log",GatewayServer::getInstance().getServerID());
                Flyer::changeLogger(fileName,s_time.sec());
            }
        }
        if(m_minClock(s_time))
        {
            TaskManager::getInstance().sendHeartMsg();
        }
        msleep(atol(Flyer::globalConfMap["threadsleep"].c_str()));
    }
}

