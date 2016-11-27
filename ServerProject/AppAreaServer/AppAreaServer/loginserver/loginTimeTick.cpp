#include "loginTimeTick.h"
#include "flyer.h"
#include "taskManager.h"
#include "loginServer.h"
#include "httpThread.h"

Time LoginTimeTick::s_time;

LoginTimeTick::LoginTimeTick() : Thread("服务器时间线程"),m_secClock(1000),m_minClock(60*1000),m_hourClock(60*60*1000),m_halfHourClock(30*60*1000)
{
}

void LoginTimeTick::run()
{
    unsigned int cnt = 0;
    while(!isFinal())
    {
        s_time.now();
        if(m_secClock(s_time))
        {
            if(s_time.sec() % (60 * 60) == 0)
            {
                char fileName[100] = {0};
                snprintf(fileName,sizeof(fileName),"log/login-%02u.log",LoginServer::getInstance().getServerID());
                Flyer::changeLogger(fileName,s_time.sec());
            }
        }
        if(m_minClock(s_time))
        {
            TaskManager::getInstance().sendHeartMsg();
            std::ostringstream oss;
            oss << "flyer_" << cnt;
            testHttp(oss.str());
            ++cnt;
        }
        msleep(atol(Flyer::globalConfMap["threadsleep"].c_str()));
    }
}

void LoginTimeTick::testHttp(const std::string userName)
{
    std::ostringstream oss;
    oss << "username=" << userName << "&password=" << userName; 
    HttpReq req(Flyer::globalConfMap["url"],oss.str());
    HttpThread::getInstance().add(req);
}
