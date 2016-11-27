#include "recycleThread.h"
#include "flyer.h"
#include "taskManager.h"

bool RecycleThread::add(boost::shared_ptr<Connect> task)
{
    m_taskSet.insert(std::pair<unsigned long,boost::shared_ptr<Connect> >(task->getID(),task));
    return true;
}

void RecycleThread::run()
{
    while(!isFinal())
    {
        checkQueue();
        if(!m_taskSet.empty())
        {
            for(auto iter = m_taskSet.begin();iter != m_taskSet.end();++iter)
            {
                boost::shared_ptr<Connect> task = iter->second;
                task->closeFd();
                TaskManager::getInstance().eraseTask(task->getID());
            }
            m_taskSet.clear();
        }
        msleep(atol(Flyer::globalConfMap["threadsleep"].c_str()));
    }
    for(auto iter = m_taskSet.begin();iter != m_taskSet.end();++iter)
    {
        boost::shared_ptr<Connect> task = iter->second;
        task->closeFd();
        TaskManager::getInstance().eraseTask(task->getID());
    }
    m_taskSet.clear();
}



