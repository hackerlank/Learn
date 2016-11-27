#include "taskManager.h"
#include "recycleThread.h"
#include "mainThread.h"

bool TaskManager::addTask(boost::shared_ptr<Task> task)
{
    std::pair<std::map<unsigned long,boost::shared_ptr<Task> >::iterator,bool> ret = m_taskMap.insert(std::pair<unsigned long,boost::shared_ptr<Task> >(task->getID(),task));
    return ret.second;
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

void TaskManager::eraseTask(const unsigned long taskID)
{
    m_taskMap.erase(taskID);
}

boost::shared_ptr<Task> TaskManager::getTask(const unsigned long id)
{
    boost::shared_ptr<Task> ret(NULL);
    auto iter = m_taskMap.find(id);
    if(iter != m_taskMap.end())
    {
        ret = iter->second;
    }
    return ret;
}

bool TaskManager::sendServerMsg(const unsigned int serverID,const google::protobuf::Message &message)
{
    for(auto iter = m_taskMap.begin();iter != m_taskMap.end();++iter)
    {
        boost::shared_ptr<Task> task = iter->second;
        if(task->getServerID() == serverID)
        {
            return task->sendMsg(message);
        }
    }
    return false;
}

boost::shared_ptr<Task> TaskManager::getServerTask(const unsigned int serverID)
{
    for(auto iter = m_taskMap.begin();iter != m_taskMap.end();++iter)
    {
        boost::shared_ptr<Task> task = iter->second;
        if(task->getServerID() == serverID)
        {
            return task;
        }
    }
    return boost::shared_ptr<Task>(NULL);
}

boost::shared_ptr<Task> TaskManager::getServerTaskByType(const ProtoMsgData::ServerType type)
{
    for(auto iter = m_taskMap.begin();iter != m_taskMap.end();++iter)
    {
        boost::shared_ptr<Task> task = iter->second;
        if(task->getServerType() == type)
        {
            return task;
        }
    }
    return boost::shared_ptr<Task>(NULL);
}


void TaskManager::sendHeartMsg(const unsigned cycle)
{
    unsigned int cycleTotal = atol(Flyer::globalConfMap["heartcycle"].c_str());
    std::vector<unsigned long> delVec;
    for(auto iter = m_taskMap.begin();iter != m_taskMap.end();++iter)
    {
        boost::shared_ptr<Task> task = iter->second;
        if(task->getID() % cycleTotal != cycle)
        {
            continue;
        }
        if(!task->sendHeartMsg())
        {
            delVec.push_back(task->getID());
        }
    }
    for(auto iter = delVec.begin();iter != delVec.end();++iter)
    {
        MainThread::getInstance().addRecycle(*iter);
    }
}

bool TaskManager::addGatewayTask(const unsigned charID,const unsigned long id)
{
    bool flag = false;
    do
    {
        boost::shared_ptr<Task> task = getTask(id);
        if(!task)
        {
            break;
        }
        if(m_charIDMap.find(charID) != m_charIDMap.end())
        {
            break;
        }
        m_charIDMap.insert(std::pair<unsigned long,unsigned long>(charID,id));
        flag = true;
    }while(false);
    return flag;
}

boost::shared_ptr<Task> TaskManager::getGatewayTask(const unsigned charID)
{
    auto iter = m_charIDMap.find(charID);
    if(iter != m_charIDMap.end())
    {
        return getTask(iter->second);
    }
    return boost::shared_ptr<Task>(NULL);
}


