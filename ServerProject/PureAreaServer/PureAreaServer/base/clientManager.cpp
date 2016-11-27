#include "clientManager.h"
#include "recycleThread.h"

ClientManager::ClientManager() : Thread("客户端管理器")
{
    init();
}

ClientManager::~ClientManager()
{
    TEMP_FAILURE_RETRY(::close(m_epfd));
}

bool ClientManager::init()
{
    m_epfd = epoll_create(atol(Flyer::globalConfMap["addepollsize"].c_str()));
    return m_epfd != -1;
}

bool ClientManager::add(boost::shared_ptr<Client> client)
{
    client->addEpoll(m_epfd,EPOLLIN | EPOLLOUT | EPOLLPRI | EPOLLERR);
    m_clientMap.insert(std::pair<unsigned long,boost::shared_ptr<Client> >(client->getID(),client));
    if(m_clientMap.size() > m_eventVec.size())
    {
        m_eventVec.resize(m_clientMap.size() + atol(Flyer::globalConfMap["addepollsize"].c_str()));
    }
    return true;
}


boost::shared_ptr<Client> ClientManager::getClient(const unsigned long id)
{
    auto iter = m_clientMap.find(id);
    return iter == m_clientMap.end() ? boost::shared_ptr<Client> (NULL) : iter->second;
}

int ClientManager::checkStatus(const unsigned int num,const ProtoMsgData::ServerType &serverType)
{
    int ret = -1;
    do
    {
        unsigned int cnt = 0;
        if(m_clientMap.size() < num)
        {
            break;
        }
        bool breakFlg = false;
        for(auto iter = m_clientMap.begin();iter != m_clientMap.end();++iter)
        {
            boost::shared_ptr<Client> client = iter->second;
            if(client->getServerType() == serverType)
            {
                if(client->getStatus() == Task_Status_Recycle)
                {
                    breakFlg = true;
                    break;
                }
                if(client->getStatus() == Task_Status_Main)
                {
                    ++cnt;
                }
            }
        }
        if(breakFlg)
        {
            break;
        }
        ret = cnt == num ? 1 : 0;
    }while(false);
    return ret;
}

void ClientManager::run()
{
    while(!isFinal())
    {
        checkQueue();
        if(!m_clientMap.empty())
        {
            std::vector<unsigned long> delVec;
            int ret = epoll_wait(m_epfd,&m_eventVec[0],m_clientMap.size(),0);
            for(int cnt = 0;cnt < ret;++cnt)
            {
                struct epoll_event &event = m_eventVec[cnt];
                bool delFlg = true;
                do
                {
                    boost::shared_ptr<Client> client = getClient(event.data.u64);
                    if(!client)
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
                        client->accpetMsg();
                        delFlg = false;
                    }
                    if(event.events & EPOLLOUT)
                    {
                        delFlg = false;
                    }
                    if(client->getStatus() == Task_Status_Recycle)
                    {
                        delFlg = true;
                    }
                }while(false);
                event.events = 0;
                if(delFlg)
                {
                    delVec.push_back(event.data.u64);
                }
            }
            for(auto iter = delVec.begin();iter != delVec.end();++iter)
            {
                boost::shared_ptr<Client> client = getClient(*iter);
                if(client)
                {
                    client->delEpoll(m_epfd,EPOLLIN);
                    RecycleThread::getInstance().add(client);
                }
                m_clientMap.erase(*iter);
                Info(Flyer::logger,"断开连接(" << *iter << ")");
            }
        }
        msleep(atol(Flyer::globalConfMap["threadsleep"].c_str()));
    }

    for(auto iter = m_clientMap.begin();iter != m_clientMap.end();++iter)
    {
        boost::shared_ptr<Client> client = iter->second;
        if(client)
        {
            client->delEpoll(m_epfd,EPOLLIN);
            RecycleThread::getInstance().add(client);
        }
    }
    m_clientMap.clear();
}
