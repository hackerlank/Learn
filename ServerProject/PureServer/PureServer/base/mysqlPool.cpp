#include "mysqlPool.h"

MysqlPool::MysqlPool()
{
    pthread_mutex_init(&m_mutex,NULL);
}

bool MysqlPool::addUrl(const std::string &_url)
{
    bool ret = false;
    do
    {
        UrlInfo url(_url);
        if(!url.getValid())
        {
            break;
        }
        boost::shared_ptr<MysqlHandle> handle(new MysqlHandle(url));
        if(!handle->init())
        {
            break;
        }
        pthread_mutex_lock(&m_mutex);
        std::pair<std::map<unsigned short,UrlInfo>::iterator,bool> flag = m_codeUrlMap.insert(std::pair<unsigned short,UrlInfo>(url.getCode(),url));
        if(!flag.second)
        {
            pthread_mutex_unlock(&m_mutex);
            break;
        }
        std::pair<std::map<unsigned int,boost::shared_ptr<MysqlHandle> >::iterator,bool> handFlg = m_handleMap.insert(std::pair<unsigned int,boost::shared_ptr<MysqlHandle> >(handle->getID(),handle));
        if(!handFlg.second)
        {
            m_codeUrlMap.erase(url.getCode());
            pthread_mutex_unlock(&m_mutex);
            break;
        }
                
        auto iter = m_codeHandeMap.find(url.getCode());
        if(iter == m_codeHandeMap.end())
        {
            std::set<unsigned int> idSet;
            idSet.insert(handle->getID());
            m_codeHandeMap.insert(std::pair<unsigned short,std::set<unsigned int> >(url.getCode(),idSet));
        }
        else
        {
            std::set<unsigned int> &idSet = const_cast<std::set<unsigned int>&>(iter->second);
            idSet.insert(handle->getID());
        }
        pthread_mutex_unlock(&m_mutex);
        ret = true;
    }while(false);

    char temp[100] = {0};
    snprintf(temp,sizeof(temp),"[数据库连接池] 增加连接%s(%s)",ret ? "成功" : "失败",_url.c_str());
    Info(Flyer::logger,temp);
    return ret;
}

boost::shared_ptr<MysqlHandle> MysqlPool::getHandle(const unsigned int id)
{
    auto iter = m_handleMap.find(id);
    return iter == m_handleMap.end() ? boost::shared_ptr<MysqlHandle>(NULL) : iter->second;
}

boost::shared_ptr<MysqlHandle> MysqlPool::getIdleHandle(const unsigned short code)
{
    unsigned long id = 0;
    do
    {
        pthread_mutex_lock(&m_mutex);
        auto iter = m_codeHandeMap.find(code);
        if(iter == m_codeHandeMap.end())
        {
            pthread_mutex_unlock(&m_mutex);
            break;
        }
        std::vector<unsigned int> delVec;
        std::set<unsigned int> &idSet = iter->second;
        for(auto it = idSet.begin();it != idSet.end();++it)
        {
            boost::shared_ptr<MysqlHandle> handle = getHandle(*it);
            if(!handle)
            {
                delVec.push_back(*it);
                continue;
            }
            if(!handle->checkConnect())
            {
                delVec.push_back(*it);
                continue;
            }
            id = *it;
            break;
        }
        for(auto it = delVec.begin();it != delVec.end();++it)
        {
            m_handleMap.erase(*it);
            idSet.erase(*it);
        }
        pthread_mutex_unlock(&m_mutex);
    }while(false);

    return getHandle(id);
}





