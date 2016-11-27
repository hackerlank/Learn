#include "mainThread.h"
#include "flyer.h"
#include "recycleThread.h"

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

void MainThread::run()
{
    while(!isFinal())
    {
        checkQueue();
        if(!m_taskSet.empty())
        {
            int ret = epoll_wait(m_epfd,&m_epollEventVec[0],m_taskSet.size(),0);
            std::vector<boost::shared_ptr<Connect> > delVec;
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
                    if(!task->accpetMsg())
                    {
                        delVec.push_back(task);
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
            for(auto iter = delVec.begin();iter != delVec.end();++iter)
            {
                boost::shared_ptr<Connect> task = *iter;
                task->delEpoll(m_epfd,EPOLLIN);
                task->setStatus(Task_Status_Recycle);
                RecycleThread::getInstance().add(task);
                m_taskSet.erase(task->getID());
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



