#include "mainThread.h"
#include "flyer.h"
#include "recycleThread.h"
#include "taskManager.h"

bool MainThread::add(boost::shared_ptr<Connect> task)
{
    std::pair<std::map<unsigned long,boost::shared_ptr<Connect> >::iterator,bool> ret = m_taskSet.insert(std::pair<unsigned long,boost::shared_ptr<Connect> >(task->getID(),task));
    if(ret.second)
    {
        task->addEpoll(m_epfd,EPOLLIN | EPOLLOUT | EPOLLPRI | EPOLLERR);
    }
    if(m_taskSet.size() > m_epollEventVec.size())
    {
        m_epollEventVec.resize(m_taskSet.size() + atol(Flyer::globalConfMap["addepollsize"].c_str()));
    }
    return ret.second;
}

boost::shared_ptr<Connect> MainThread::getTask(const unsigned long id)
{
    boost::shared_ptr<Connect> task(NULL);
    auto itr = m_taskSet.find(id);
    if(itr != m_taskSet.end())
    {
        task = itr->second;
    }
    return task;
}

void MainThread::run()
{
    while(!isFinal())
    {
        checkQueue();
        if(!m_taskSet.empty())
        {
            int ret = epoll_wait(m_epfd,&m_epollEventVec[0],m_taskSet.size(),0);
            std::vector<unsigned long> delVec;
            for(int cnt = 0;cnt < ret;++cnt)
            {
                bool flag = true;
                struct epoll_event &event  = m_epollEventVec[cnt];
                unsigned long taskID = event.data.u64;
                do
                {
                    boost::shared_ptr<Connect> task = getTask(taskID);
                    if(!task)
                    {
                        break;
                    }
                    if(event.events & EPOLLPRI)
                    {
                        break;
                    }
                    if(event.events & EPOLLERR)
                    {
                        break;
                    }
                    if(event.events & EPOLLIN)
                    {
                        task->accpetMsg();
                    }
                    if(event.events & EPOLLOUT)
                    {
                    }
                    flag = false;
                }while(false);
                if(flag)
                {
                    delVec.push_back(taskID);
                }
                event.events = 0;
            }
            for(auto iter = delVec.begin();iter != delVec.end();++iter)
            {
                const unsigned long id = *iter;
                boost::shared_ptr<Connect> task = getTask(id);
                task = task ? task : TaskManager::getInstance().getTask(id);
                if(task)
                {
                    task->delEpoll(m_epfd,EPOLLIN);
                    task->setStatus(Task_Status_Recycle);
                    RecycleThread::getInstance().add(task);
                }
                m_taskSet.erase(id);
            }
            delVec.clear();
            for(auto iter = m_taskSet.begin();iter != m_taskSet.end();++iter)
            {
                boost::shared_ptr<Connect> task = getTask(iter->first);
                if(!task || task->getStatus() == Task_Status_Recycle)
                {
                    delVec.push_back(iter->first);
                }
            }
            for(auto iter = delVec.begin();iter != delVec.end();++iter)
            {
                const unsigned long id = *iter;
                boost::shared_ptr<Connect> task = getTask(id);
                task = task ? task : TaskManager::getInstance().getTask(id);
                if(task)
                {
                    task->delEpoll(m_epfd,EPOLLIN);
                    task->setStatus(Task_Status_Recycle);
                    RecycleThread::getInstance().add(task);
                }
                m_taskSet.erase(id);
            }
        }
        msleep(atol(Flyer::globalConfMap["threadsleep"].c_str()));
    }

    for(auto iter = m_taskSet.begin();iter != m_taskSet.end();++iter)
    {
        boost::shared_ptr<Connect> task = iter->second;
        task->delEpoll(m_epfd,EPOLLIN);
        task->setStatus(Task_Status_Recycle);
        RecycleThread::getInstance().add(task);
    }
    m_taskSet.clear();
}



