#include "threadPool.h"

unsigned int ThreadPool::s_id = 0;

ThreadPool::ThreadPool()
{
}

ThreadPool::~ThreadPool()
{
}

bool ThreadPool::init()
{
    bool ret = false;
    do
    {
        bool flag = true;
        unsigned int num = atol(Flyer::globalConfMap["recyclethread"].c_str());
        for(unsigned cnt = 0;cnt < num;++cnt)
        {
            boost::shared_ptr<RecycleThread> thread (new RecycleThread(++s_id));
            if(!thread->init())
            {
                flag = false;
                break;
            }
            std::pair<std::map<unsigned int,boost::shared_ptr<RecycleThread> >::iterator,bool> pair = m_recycleThreadMap.insert(std::pair<unsigned int,boost::shared_ptr<RecycleThread> >(thread->getTempID(),thread));
            if(!pair.second)
            {
                flag = false;
                break;
            }
        }
        num = atol(Flyer::globalConfMap["verifythread"].c_str());
        for(unsigned cnt = 0;cnt < num && flag;++cnt)
        {
            boost::shared_ptr<VerifyThread> thread (new VerifyThread(++s_id));
            if(!thread->init())
            {
                flag = false;
                break;
            }
            std::pair<std::map<unsigned int,boost::shared_ptr<VerifyThread> >::iterator,bool> pair = m_verifyThreadMap.insert(std::pair<unsigned int,boost::shared_ptr<VerifyThread> >(thread->getTempID(),thread));
            if(!pair.second)
            {
                flag = false;
                break;
            }
        }
        num = atol(Flyer::globalConfMap["mainthread"].c_str());
        for(unsigned cnt = 0;cnt < num && flag;++cnt)
        {
            boost::shared_ptr<MainThread> thread (new MainThread(++s_id));
            if(!thread->init())
            {
                flag = false;
                break;
            }
            std::pair<std::map<unsigned int,boost::shared_ptr<MainThread> >::iterator,bool> pair = m_mainThreadMap.insert(std::pair<unsigned int,boost::shared_ptr<MainThread> >(thread->getTempID(),thread));
            if(!pair.second)
            {
                flag = false;
                break;
            }
        }
        ret = flag;
    }while(false);
    return ret;
}

bool ThreadPool::addVerify(const unsigned long id)
{
    bool ret = false;
    do
    {
        boost::shared_ptr<VerifyThread> thread(NULL);
        for(auto iter = m_verifyThreadMap.begin();iter != m_verifyThreadMap.end();++iter)
        {
            if(!thread)
            {
                thread = iter->second;
            }
            else
            {
                if(thread->size() > iter->second->size())
                {
                    thread = iter->second;
                }
            }
        }
        ret = thread ? thread->add(id) : false;
        if(ret)
        {
            std::pair<std::map<unsigned long,unsigned int>::iterator,bool> flag = m_verifyMap.insert(std::pair<unsigned long,unsigned int>(id,thread->getTempID()));
            ret = flag.second;
        }
    }while(false);
    if(!ret)
    {
        m_verifyMap.erase(id);
        addRecycle(id);
    }
    return ret;
}

bool ThreadPool::addMain(const unsigned long id)
{
    bool ret = false;
    do
    {
        boost::shared_ptr<MainThread> thread(NULL);
        for(auto iter = m_mainThreadMap.begin();iter != m_mainThreadMap.end();++iter)
        {
            if(!thread)
            {
                thread = iter->second;
            }
            else
            {
                if(thread->size() > iter->second->size())
                {
                    thread = iter->second;
                }
            }
        }
        ret = thread ? thread->add(id) : false;
        if(ret)
        {
            std::pair<std::map<unsigned long,unsigned int>::iterator,bool> flag = m_mainMap.insert(std::pair<unsigned long,unsigned int>(id,thread->getTempID()));
            ret = flag.second;
        }
    }while(false);
    if(!ret)
    {
        m_mainMap.erase(id);
        addRecycle(id);
    }
    return ret;
}

bool ThreadPool::addRecycle(const unsigned long id)
{
    bool ret = false;
    do
    {
        boost::shared_ptr<RecycleThread> thread(NULL);
        for(auto iter = m_recycleThreadMap.begin();iter != m_recycleThreadMap.end();++iter)
        {
            if(!thread)
            {
                thread = iter->second;
            }
            else
            {
                if(thread->size() > iter->second->size())
                {
                    thread = iter->second;
                }
            }
        }
        ret = thread ? thread->add(id) : false;
        if(ret)
        {
            std::pair<std::map<unsigned long,unsigned int>::iterator,bool> flag = m_recycleMap.insert(std::pair<unsigned long,unsigned int>(id,thread->getTempID()));
            ret = flag.second;
        }
    }while(false);
    return ret;
}

bool ThreadPool::addMainFromVerify(const unsigned long id)
{
    bool ret = false;
    do
    {
        auto itr = m_verifyMap.find(id);
        if(itr == m_verifyMap.end())
        {
            break;
        }
        auto iter = m_verifyThreadMap.find(itr->second);
        if(iter == m_verifyThreadMap.end())
        {
            break;
        }
        ret = iter->second->addMain(id);
    }while(false);
    ret = ret ? ret : addRecycle(id);
    return ret;
}

bool ThreadPool::addRecycleFromVerify(const unsigned long id)
{
    bool ret = false;
    do
    {
        auto itr = m_verifyMap.find(id);
        if(itr == m_verifyMap.end())
        {
            break;
        }
        auto iter = m_verifyThreadMap.find(itr->second);
        if(iter == m_verifyThreadMap.end())
        {
            break;
        }
        iter->second->addRecycle(id);
        ret = true;
    }while(false);
    ret = ret ? ret : addRecycle(id);
    return ret;
}

bool ThreadPool::addRecycleFromMain(const unsigned long id)
{
    bool ret = false;
    do
    {
        auto itr = m_mainMap.find(id);
        if(itr == m_mainMap.end())
        {
            break;
        }
        auto iter = m_mainThreadMap.find(itr->second);
        if(iter == m_mainThreadMap.end())
        {
            break;
        }
        iter->second->addRecycle(id);
        ret = true;
    }while(false);
    ret = ret ? ret : addRecycle(id);
    return ret;
}

void ThreadPool::start()
{
    for(auto iter = m_verifyThreadMap.begin();iter != m_verifyThreadMap.end();++iter)
    {
        iter->second->start();
    }
    for(auto iter = m_mainThreadMap.begin();iter != m_mainThreadMap.end();++iter)
    {
        iter->second->start();
    }
    for(auto iter = m_recycleThreadMap.begin();iter != m_recycleThreadMap.end();++iter)
    {
        iter->second->start();
    }
}

void ThreadPool::final()
{
    for(auto iter = m_verifyThreadMap.begin();iter != m_verifyThreadMap.end();++iter)
    {
        iter->second->final();
        iter->second->end();
    }
    for(auto iter = m_mainThreadMap.begin();iter != m_mainThreadMap.end();++iter)
    {
        iter->second->final();
        iter->second->end();
    }
    for(auto iter = m_recycleThreadMap.begin();iter != m_recycleThreadMap.end();++iter)
    {
        iter->second->final();
        iter->second->end();
    }
}

void ThreadPool::delFromVefiry(const unsigned long id)
{
    m_verifyMap.erase(id);
}

void ThreadPool::delFromMain(const unsigned long id)
{
    m_mainMap.erase(id);
}

void ThreadPool::delFromRecycle(const unsigned long id)
{
    m_recycleMap.erase(id);
}

void ThreadPool::print()
{
    Info(Flyer::logger,"[线程池测试开始]");
    for(auto iter = m_verifyThreadMap.begin();iter != m_verifyThreadMap.end();++iter)
    {
        Info(Flyer::logger,"[认证线程] (" << iter->second->getTempID() << "," << iter->second->size() << ")");
    }
    for(auto iter = m_mainThreadMap.begin();iter != m_mainThreadMap.end();++iter)
    {
        Info(Flyer::logger,"[逻辑线程] (" << iter->second->getTempID() << "," << iter->second->size() << ")");
    }
    for(auto iter = m_recycleThreadMap.begin();iter != m_recycleThreadMap.end();++iter)
    {
        Info(Flyer::logger,"[回收线程] (" << iter->second->getTempID() << "," << iter->second->size() << ")");
    }
    Info(Flyer::logger,"[线程池测试结束]");
}
