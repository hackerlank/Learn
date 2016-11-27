#include "recycleThread.h"
#include "flyer.h"
#include "taskManager.h"
#include "clientManager.h"
#include "threadPool.h"

RecycleThread::RecycleThread(const unsigned int id) : Thread("回收线程")
{
    m_tempID = id;
}

RecycleThread::~RecycleThread()
{
}

bool RecycleThread::init()
{
    return true;
}

unsigned long RecycleThread::size()
{
    return m_taskSet.size();
}

bool RecycleThread::add(const unsigned long id)
{
    bool flag = false;
    do
    {
        boost::shared_ptr<Task> task = TaskManager::getInstance().getTask(id);
        if(task)
        {
            task->setStatus(Task_Status_Recycle);
        }
        std::pair<std::set<unsigned long>::iterator,bool> ret = m_taskSet.insert(id);
        flag = ret.second;
    }while(false);
    return flag;
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
                boost::shared_ptr<Task> task = TaskManager::getInstance().getTask(*iter);
                if(task && task.get() && task->getSocket() != -1)
                {
                    task->closeFd();
                    TaskManager::getInstance().eraseTask(*iter);
                }
                else
                {
                    boost::shared_ptr<Client> client = ClientManager::getInstance().getClient(*iter);
                    if(client && client.get())
                    {
                        client->closeFd();
                        ClientManager::getInstance().eraseClient(*iter);
                    }
                }
                ThreadPool::getInstance().delFromRecycle(*iter);
            }
            m_taskSet.clear();
        }
        msleep(atol(Flyer::globalConfMap["threadsleep"].c_str()));
    }
    for(auto iter = m_taskSet.begin();iter != m_taskSet.end();++iter)
    {
        boost::shared_ptr<Task> task = TaskManager::getInstance().getTask(*iter);
        if(task)
        {
            task->closeFd();
            TaskManager::getInstance().eraseTask(*iter);
        }
        else
        {
            boost::shared_ptr<Client> client = ClientManager::getInstance().getClient(*iter);
            if(client)
            {
                client->closeFd();
                ClientManager::getInstance().eraseClient(*iter);
            }
        }
    }
    m_taskSet.clear();
}



