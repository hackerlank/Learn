#include "verifyThread.h"
#include "flyer.h"
#include "mainThread.h"
#include "recycleThread.h"

bool VerifyThread::add(boost::shared_ptr<Connect> task)
{
    task->addEpoll(m_epfd,EPOLLIN | EPOLLOUT | EPOLLPRI | EPOLLERR);
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

void VerifyThread::run()
{
    while(!isFinal())
    {
        checkQueue();
        std::vector<boost::shared_ptr<Connect> > delVec;
        if(!m_taskSet.empty())
        {
            int ret = epoll_wait(m_epfd,&m_epollEventVec[0],m_taskSet.size(),0);
            for(int cnt = 0;cnt < ret;++cnt)
            {
                struct epoll_event &event  = m_epollEventVec[cnt];
                unsigned long taskID = event.data.u64;
                auto itr = m_taskSet.find(taskID);
                if(itr == m_taskSet.end())
                {
                    continue;
                }
                boost::shared_ptr<Connect> task = itr->second;
                if(event.events & EPOLLIN)
                {
                    task->accpetMsg();
                    if(task->getStatus() == Task_Status_Main)
                    {
                        task->delEpoll(m_epfd,EPOLLIN);
                        m_taskSet.erase(task->getID());
                        task->resetLifeTime();
                        MainThread::getInstance().add(task);
                    }
                    else
                    {
                    //    delVec.push_back(task);
                    }
                }
                if(event.events & EPOLLOUT)
                {
                }
                if(event.events & EPOLLPRI)
                {
                    delVec.push_back(task);
                }
                if(event.events & EPOLLERR)
                {
                    delVec.push_back(task);
                }
                event.events = 0;
            }
        }
        for(auto iter = m_taskSet.begin();iter != m_taskSet.end();++iter)
        {
            boost::shared_ptr<Connect> task = iter->second;
            if(task->getStatus() == Task_Status_Main)
            {
                continue;
            }
            if(task->isElapse())
            {
                delVec.push_back(task);
            }
        }
        for(auto iter = delVec.begin();iter != delVec.end();++iter)
        {
            boost::shared_ptr<Connect> task = *iter;
            task->setStatus(Task_Status_Recycle);
            task->delEpoll(m_epfd,EPOLLIN);
            RecycleThread::getInstance().add(task);
            m_taskSet.erase(task->getID());
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



