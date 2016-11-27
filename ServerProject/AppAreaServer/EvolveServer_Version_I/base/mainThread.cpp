#include "mainThread.h"
#include "recycleThread.h"
#include "taskManager.h"

bool MainThread::add(const unsigned long id)
{
    bool flag = false;
    do
    {
        boost::shared_ptr<Task> task = TaskManager::getInstance().getTask(id);
        if(!task)
        {
            break;
        }
        std::pair<std::set<unsigned long>::iterator,bool> ret = m_taskSet.insert(id);
        flag = ret.second;
        if(!flag)
        {
            break;
        }
        task->resetHeartTime();
        task->setStatus(Task_Status_Main);
        task->addEpoll(m_epfd,EPOLLIN | EPOLLOUT | EPOLLPRI | EPOLLERR);
        if(m_taskSet.size() > m_epollEventVec.size())
        {
            m_epollEventVec.resize(m_taskSet.size() + atol(Flyer::globalConfMap["addepollsize"].c_str()));
        }
    }while(false);
    return flag;
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
                    boost::shared_ptr<Task> task = TaskManager::getInstance().getTask(taskID);
                    if(!task || !task.get())
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
                        if(!task->acceptMsg())
                        {
                            break;
                        }
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
                addRecycle(*iter);
            }
            delVec.clear();
        }
        msleep(atol(Flyer::globalConfMap["threadsleep"].c_str()));
    }

    for(auto iter = m_taskSet.begin();iter != m_taskSet.end();++iter)
    {
        addRecycle(*iter,false);
    }
    m_taskSet.clear();
}

void MainThread::addRecycle(const unsigned long id,const bool del)
{
    boost::shared_ptr<Task> task = TaskManager::getInstance().getTask(id);
    if(task)
    {
        task->delEpoll(m_epfd,EPOLLIN);
        RecycleThread::getInstance().add(id);
    }
    if(del)
    {
        m_taskSet.erase(id);
    }
}



