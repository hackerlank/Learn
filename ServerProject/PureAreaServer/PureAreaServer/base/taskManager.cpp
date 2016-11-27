#include "taskManager.h"
#include "recycleThread.h"

bool TaskManager::addTask(boost::shared_ptr<Connect> task)
{
    std::pair<std::map<unsigned long,boost::shared_ptr<Connect> >::iterator,bool> ret = m_taskMap.insert(std::pair<unsigned long,boost::shared_ptr<Connect> >(task->getID(),task));
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
            boost::shared_ptr<Connect> task = iter->second;
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
            boost::shared_ptr<Connect> task = iter->second;
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

boost::shared_ptr<Connect> TaskManager::getTask(const unsigned long id)
{
    auto iter = m_taskMap.find(id);
    return iter == m_taskMap.end() ? boost::shared_ptr<Connect>(NULL) : iter->second;
}

bool TaskManager::sendServerMsg(const unsigned int serverID,const google::protobuf::Message &message)
{
    for(auto iter = m_taskMap.begin();iter != m_taskMap.end();++iter)
    {
        boost::shared_ptr<Connect> task = iter->second;
        if(task->getServerID() == serverID)
        {
            return task->sendMsg(message);
        }
    }
    return false;
}
boost::shared_ptr<Connect> TaskManager::getServerTask(const unsigned int serverID)
{
    for(auto iter = m_taskMap.begin();iter != m_taskMap.end();++iter)
    {
        boost::shared_ptr<Connect> task = iter->second;
        if(task->getServerID() == serverID)
        {
            return task;
        }
    }
    return boost::shared_ptr<Connect>(NULL);
}
void TaskManager::sendHeartMsg()
{
    std::vector<unsigned long> delVec;
    for(auto iter = m_taskMap.begin();iter != m_taskMap.end();++iter)
    {
        boost::shared_ptr<Connect> task = iter->second;
        if(!task->sendHeartMsg())
        {
            delVec.push_back(task->getID());
        }
    }
    for(auto iter = delVec.begin();iter != delVec.end();++iter)
    {
        boost::shared_ptr<Connect> task = getTask(*iter);
        if(task)
        {
            RecycleThread::getInstance().add(task);
        }
    }
}
