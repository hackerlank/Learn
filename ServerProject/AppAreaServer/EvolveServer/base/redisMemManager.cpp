#include "redisMemManager.h"
#include "flyer.h"

RedisMemManager::RedisMemManager()
{
}

RedisMemManager::~RedisMemManager()
{
}

bool RedisMemManager::init()
{
    bool ret = false;
    do
    {
        pthread_mutex_init(&m_mutex,NULL);
        std::string file = Flyer::globalConfMap["redisxml"];
        if(file.empty())
        {
            break;
        }
        using namespace boost::property_tree;
        ptree tree;
        read_xml(file,tree);
        ptree child = tree.get_child("redisconf.redis");
        for(auto iter = child.begin();iter != child.end();++iter)
        {
            if(iter->first == "<xmlattr>" || iter->first == "<xmlcomment>")
            {
                continue;
            }
            std::string ip = iter->second.get<std::string>("<xmlattr>.ip");
            std::string port = iter->second.get<std::string>("<xmlattr>.port");
            unsigned short memPort = atol(port.c_str());
            std::pair<std::string,unsigned short> pair(ip,memPort);
            m_confVec.push_back(pair);
        }
        ret = m_confVec.empty() ? false : true;
    }while(false);
    char temp[100] = {0};
    snprintf(temp,sizeof(temp),"[redis管理器] 加载配置%s",ret ? "成功" : "失败");
    Info(Flyer::logger,temp);
    return ret;
}

boost::shared_ptr<RedisMem> RedisMemManager::getRedis(const unsigned short id)
{
    pthread_t tid = ::pthread_self();
    auto iter = m_redisMap.find(tid);
    if(iter == m_redisMap.end())
    {
        std::map<unsigned short,boost::shared_ptr<RedisMem> > redisMap;
        for(auto itr = m_confVec.begin();itr != m_confVec.end();++itr)
        {
            const std::pair<std::string,unsigned short> &pair = *itr;
            unsigned short memID = redisMap.size() + 1;
            boost::shared_ptr<RedisMem> redisMem(new RedisMem(memID,pair.first,pair.second));
            if(!redisMem->init())
            {
                continue;
            }
            redisMap.insert(std::pair<unsigned short,boost::shared_ptr<RedisMem> >(redisMem->getID(),redisMem));
        }
        m_redisMap.insert(std::pair<unsigned long,std::map<unsigned short,boost::shared_ptr<RedisMem> > >(tid,redisMap));
    }
    boost::shared_ptr<RedisMem> redisMem(NULL);
    pthread_mutex_lock(&m_mutex);
    iter = m_redisMap.find(tid);
    if(iter != m_redisMap.end())
    {
        const std::map<unsigned short,boost::shared_ptr<RedisMem> > &redisMap = iter->second;
        unsigned int key = id % redisMap.size() + 1;
        auto itr = redisMap.find(key);
        if(itr != redisMap.end())
        {
            redisMem = itr->second;
        }
    }
    pthread_mutex_unlock(&m_mutex);
    return redisMem;
}


void RedisMemManager::clearMemory()
{
    pthread_mutex_lock(&m_mutex);
    for(auto itr = m_redisMap.begin();itr != m_redisMap.end();++itr)
    {
        const std::map<unsigned short,boost::shared_ptr<RedisMem> > &redisMap = itr->second;
        for(auto iter = redisMap.begin();iter != redisMap.end();++iter)
        {
            boost::shared_ptr<RedisMem> redisMem = iter->second;
            redisMem->exeCmd("FLUSHALL");
        }
    }
    pthread_mutex_unlock(&m_mutex);
}
