#include "verifyThread.h"
#include "flyer.h"
#include "mainThread.h"
#include "recycleThread.h"
#include "taskManager.h"

bool VerifyThread::add(boost::shared_ptr<Connect> task)
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

boost::shared_ptr<Connect> VerifyThread::getTask(const unsigned long taskID)
{
    boost::shared_ptr<Connect> ret(NULL);
    auto itr = m_taskSet.find(taskID);
    if(itr != m_taskSet.end())
    {
        ret = itr->second;
    }
    return ret;
}

void VerifyThread::run()
{
    while(!isFinal())
    {
        checkQueue();
        std::vector<unsigned long> delVec;
        if(!m_taskSet.empty())
        {
            int ret = epoll_wait(m_epfd,&m_epollEventVec[0],m_taskSet.size(),0);
            for(int cnt = 0;cnt < ret;++cnt)
            {
                struct epoll_event &event  = m_epollEventVec[cnt];
                unsigned long taskID = event.data.u64;
                bool del = true;
                do
                {
                    boost::shared_ptr<Connect> task = getTask(taskID);
                    if(!task)
                    {
                        break;
                    }
                    if(event.events & EPOLLPRI || event.events & EPOLLERR)
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
                    del = false;
                }while(false);
                event.events = 0;
                if(del)
                {
                    delVec.push_back(taskID);
                }
            }
            for(auto iter = delVec.begin();iter != delVec.end();++iter)
            {
                boost::shared_ptr<Connect> task = getTask(*iter);
                task = task ? task : TaskManager::getInstance().getTask(*iter);
                if(task)
                {
                    task->setStatus(Task_Status_Recycle);
                    task->delEpoll(m_epfd,EPOLLIN);
                    RecycleThread::getInstance().add(task);
                }
                m_taskSet.erase(task->getID());
            }
            delVec.clear();
            for(auto iter = m_taskSet.begin();iter != m_taskSet.end();++iter)
            {
                boost::shared_ptr<Connect> task = getTask(iter->first);
                if(!task || task->isElapse())
                {
                    delVec.push_back(iter->first);
                    continue;
                }
                if(task->getVerify())
                {
                    task->delEpoll(m_epfd,EPOLLIN);
                    m_taskSet.erase(task->getID());
                    task->resetLifeTime();
                    if(!MainThread::getInstance().add(task))
                    {
                        delVec.push_back(iter->first);
                    }
                }
            }
            for(auto iter = delVec.begin();iter != delVec.end();++iter)
            {
                boost::shared_ptr<Connect> task = getTask(*iter);
                task = task ? task : TaskManager::getInstance().getTask(*iter);
                if(task)
                {
                    task->setStatus(Task_Status_Recycle);
                    task->delEpoll(m_epfd,EPOLLIN);
                    RecycleThread::getInstance().add(task);
                }
                m_taskSet.erase(task->getID());
            }
        }
        msleep(atol(Flyer::globalConfMap["threadsleep"].c_str()));
    }

    for(auto iter = m_taskSet.begin();iter != m_taskSet.end();++iter)
    {
        boost::shared_ptr<Connect> task = iter->second;
        task->setStatus(Task_Status_Recycle);
        task->delEpoll(m_epfd,EPOLLIN);
        RecycleThread::getInstance().add(task);
    }
    m_taskSet.clear();
}



