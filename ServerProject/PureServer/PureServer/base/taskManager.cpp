#include "taskManager.h"
#include <utility>
#include "flyer.h"
#include <strings.h>

bool TaskManager::addTask(boost::shared_ptr<Task> task)
{
    if(!task.get())
    {
        return false;
    }
    std::pair<std::map<unsigned long,boost::shared_ptr<Task> >::iterator,bool> ret = m_taskMap.insert(std::pair<unsigned long,boost::shared_ptr<Task> >(task->getID(),task));
    return ret.second;
}

void TaskManager::randSendMsg(const unsigned long cnt)
{
    Debug(Flyer::logger,"随机批量发送消息开始(" << cnt << ")");
    for(unsigned long num = 0;num < cnt;)
    {
        int randID = Flyer::randBetween(1,m_taskMap.size());
        auto iter = m_taskMap.find(randID);
        if(iter != m_taskMap.end())
        {
            boost::shared_ptr<Task> task = iter->second;
            task->sendMsg();
            ++num;
        }
    }
    Debug(Flyer::logger,"随机批量发送结束开始(" << cnt << ")");
}

void TaskManager::randCloseFd(const unsigned long cnt)
{
    Debug(Flyer::logger,"随机批量断开连接开始(" << cnt << ")");
    for(unsigned long num = 0;num < cnt;)
    {
        int randID = Flyer::randBetween(1,m_taskMap.size());
        auto iter = m_taskMap.find(randID);
        if(iter != m_taskMap.end())
        {
            boost::shared_ptr<Task> task = iter->second;
            task->closeFd();
            m_taskMap.erase(randID);
            ++num;
        }
    }
    Debug(Flyer::logger,"随机批量断开结束(" << cnt << ")");
}

void TaskManager::randOpDB(const unsigned long cnt)
{
    Debug(Flyer::logger,"随机批量插入数据开始(" << cnt << ")");
    for(unsigned long num = 0;num < cnt;)
    {
        int randID = Flyer::randBetween(1,m_taskMap.size());
        auto iter = m_taskMap.find(randID);
        if(iter != m_taskMap.end())
        {
            boost::shared_ptr<Task> task = iter->second;
            task->randTestDB();
            ++num;
        }
    }
    Debug(Flyer::logger,"随机批量插入数据结束(" << cnt << ")");
}
