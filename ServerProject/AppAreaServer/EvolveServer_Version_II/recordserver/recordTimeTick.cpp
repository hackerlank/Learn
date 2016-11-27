#include "recordTimeTick.h"
#include "flyer.h"
#include "taskManager.h"
#include "recordServer.h"
#include "recordDataManager.h"

Time RecordTimeTick::s_time;

RecordTimeTick::RecordTimeTick() : Thread("服务器时间线程"),m_secClock(1000),m_minClock(60*1000),m_hourClock(60*60*1000),m_halfHourClock(30*60*1000),m_tenSecClock(10*1000),m_heartClock(atol(Flyer::globalConfMap["hearttime"].c_str())/(1.0*atol(Flyer::globalConfMap["heartcycle"].c_str())*2)*1000),m_dbClock(1.0*atol(Flyer::globalConfMap["savedatatime"].c_str())/atol(Flyer::globalConfMap["dbcycle"].c_str())*1000)
{
}

void RecordTimeTick::run()
{
    unsigned int heartCycle = 0;
    unsigned int heartCycleTotal = atol(Flyer::globalConfMap["heartcycle"].c_str());
    unsigned int dbCycle = 0;
    unsigned int dbCycyleTotal = atol(Flyer::globalConfMap["dbcycle"].c_str());
    while(!isFinal())
    {
        s_time.now();
        if(m_secClock(s_time))
        {
            if(s_time.sec() % (60 * 60) == 0)
            {
                char fileName[100] = {0};
                snprintf(fileName,sizeof(fileName),"log/record-%02u.log",RecordServer::getInstance().getServerID());
                Flyer::changeLogger(fileName,s_time.sec());
            }
        }
        if(m_heartClock(s_time))
        {
            TaskManager::getInstance().sendHeartMsg(heartCycle);
            heartCycle += 1;
            heartCycle %= heartCycleTotal;
        }
        if(m_dbClock(s_time))
        {
            RecordDataManager::getInstance().loop(dbCycle);
            dbCycle += 1;
            dbCycle %= dbCycyleTotal;
        }
        msleep(atol(Flyer::globalConfMap["threadsleep"].c_str()));
    }
}

