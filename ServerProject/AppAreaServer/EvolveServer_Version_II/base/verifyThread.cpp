#include "verifyThread.h"
#include "flyer.h"
#include "mainThread.h"
#include "recycleThread.h"
#include "taskManager.h"

bool VerifyThread::add(const unsigned long id)
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
        task->resetLifeTime();
        task->setStatus(Task_Status_Verify);
        task->addEpoll(m_epfd,EPOLLIN | EPOLLOUT | EPOLLPRI | EPOLLERR);
        if(m_taskSet.size() > m_epollEventVec.size())
        {
            m_epollEventVec.resize(m_taskSet.size() + atol(Flyer::globalConfMap["addepollsize"].c_str()));
        }
    }while(false);
    return flag;
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
                    boost::shared_ptr<Task> task = TaskManager::getInstance().getTask(taskID);
                    if(!task || !task.get())
                    {
                        break;
                    }
                    if(event.events & EPOLLPRI || event.events & EPOLLERR)
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
                addRecycle(*iter);
            }
            delVec.clear();
            for(auto iter = m_taskSet.begin();iter != m_taskSet.end();++iter)
            {
                boost::shared_ptr<Task> task = TaskManager::getInstance().getTask(*iter);
                if(!task || task->isElapse())
                {
                    delVec.push_back(*iter);
                }
            }
            for(auto iter = delVec.begin();iter != delVec.end();++iter)
            {
                addRecycle(*iter);
            }
        }
        msleep(atol(Flyer::globalConfMap["threadsleep"].c_str()));
    }

    for(auto iter = m_taskSet.begin();iter != m_taskSet.end();++iter)
    {
        addRecycle(*iter,false);
    }
    m_taskSet.clear();
}

void VerifyThread::addRecycle(const unsigned long id,const bool del)
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

void VerifyThread::VerifyThread::addMain(const unsigned long id)
{
    boost::shared_ptr<Task> task = TaskManager::getInstance().getTask(id);
    if(task)
    {
        task->delEpoll(m_epfd,EPOLLIN);
        m_taskSet.erase(task->getID());
        task->resetLifeTime();
        if(!MainThread::getInstance().add(task->getID()))
        {
            addRecycle(id);
        }
    }
    else
    {
        addRecycle(id);
    }
}

