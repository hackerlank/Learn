#include "mainThread.h"
#include "flyer.h"

bool MainThread::add(boost::shared_ptr<Task> task)
{
    if(!task.get())
    {
        return false;
    }
    task->addEpoll(m_epfd,EPOLLIN | EPOLLOUT | EPOLLPRI | EPOLLERR);
    m_taskSet.insert(std::pair<unsigned long,boost::shared_ptr<Task> >(task->getID(),task));
    if(m_taskSet.size() > m_epollEventVec.size())
    {
        m_epollEventVec.resize(m_taskSet.size() + 10);
    }
    return true;
}

void MainThread::run()
{
    while(!isFinal())
    {
        checkQueue();
        if(!m_taskSet.empty())
        {
            int ret = epoll_wait(m_epfd,&m_epollEventVec[0],m_taskSet.size(),0);
            std::vector<boost::shared_ptr<Task> > delVec;
            for(int cnt = 0;cnt < ret;++cnt)
            {
                struct epoll_event &event  = m_epollEventVec[cnt];
                unsigned long taskID = event.data.u64;
                auto itr = m_taskSet.find(taskID);
                if(itr == m_taskSet.end())
                {
                    continue;
                }
                boost::shared_ptr<Task> task = itr->second;
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
                boost::shared_ptr<Task> task = *iter;
                task->delEpoll(m_epfd,EPOLLIN);
                m_taskSet.erase(task->getID());
                Info(Flyer::logger,"断开连接(" << task->getID() << ")");
            }
        }
        msleep(10);
    }

    for(auto iter = m_taskSet.begin();iter != m_taskSet.end();++iter)
    {
        boost::shared_ptr<Task> task = iter->second;
        if(!task.get())
        {
            continue;
        }
        task->delEpoll(m_epfd,EPOLLIN);
    }
    m_taskSet.clear();
}



