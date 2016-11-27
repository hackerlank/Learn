#include "robotTimeTick.h"
#include "flyer.h"
#include "robotServer.h"
#include "logicManager.h"

Time RobotTimeTick::s_time;

RobotTimeTick::RobotTimeTick() : Thread("服务器时间线程"),m_secClock(1000),m_minClock(60*1000),m_hourClock(60*60*1000),m_halfHourClock(30*60*1000),m_tenSecClock(10*1000),m_halfSecClock(500)
{
}

void RobotTimeTick::run()
{
    while(!isFinal())
    {
        s_time.now();
        if(m_halfSecClock(s_time))
        {
            LogicManager::getInstance().loop();
        }
        if(m_secClock(s_time))
        {
            if(s_time.sec() % (60 * 60) == 0)
            {
                char fileName[100] = {0};
                snprintf(fileName,sizeof(fileName),"log/robot-%02u.log",RobotServer::getInstance().getServerID());
                Flyer::changeLogger(fileName,s_time.sec());
            }
        }
        ClientThread::getInstance().doCmd();
        msleep(atol(Flyer::globalConfMap["threadsleep"].c_str()));
    }
}

