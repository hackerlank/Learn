#include "clientManager.h"
#include "recycleThread.h"

ClientManager::ClientManager()
{
}

ClientManager::~ClientManager()
{
}

bool ClientManager::add(boost::shared_ptr<Client> client)
{
    bool flag = false;
    do
    {
        std::pair<std::map<unsigned long,boost::shared_ptr<Client> >::iterator,bool> ret = m_clientMap.insert(std::pair<unsigned long,boost::shared_ptr<Client> >(client->getID(),client));
        flag = ret.second;
        if(!flag)
        {
            break;
        }
    }while(false);
    return flag;
}


boost::shared_ptr<Client> ClientManager::getClient(const unsigned long id)
{
    boost::shared_ptr<Client> ret(NULL);
    auto iter = m_clientMap.find(id);
    if(iter != m_clientMap.end())
    {
        ret = iter->second;
    }
    return ret;
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


boost::shared_ptr<Client> ClientManager::getClientByType(const ProtoMsgData::ServerType serverType)
{
    for(auto iter = m_clientMap.begin();iter != m_clientMap.end();++iter)
    {
        boost::shared_ptr<Client> client = iter->second;
        if(client->getServerType() == serverType)
        {
            return client;
        }
    }
    return boost::shared_ptr<Client>(NULL);
}

boost::shared_ptr<Client> ClientManager::getServerClient(const unsigned short id)
{
    for(auto iter = m_clientMap.begin();iter != m_clientMap.end();++iter)
    {
        boost::shared_ptr<Client> client = iter->second;
        if(client->getServerID() == id)
        {
            return client;
        }
    }
    return boost::shared_ptr<Client>(NULL);
}

void ClientManager::eraseClient(const unsigned long id)
{
    m_clientMap.erase(id);
}

