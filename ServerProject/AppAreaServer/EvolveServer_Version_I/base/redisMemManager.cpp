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
            std::string id = iter->second.get<std::string>("<xmlattr>.id");
            std::string ip = iter->second.get<std::string>("<xmlattr>.ip");
            std::string port = iter->second.get<std::string>("<xmlattr>.port");
            unsigned short memID = atol(id.c_str());
            unsigned short memPort = atol(port.c_str());
            boost::shared_ptr<RedisMem> redisMem(new RedisMem(memID,ip,memPort));
            if(!redisMem->init())
            {
                continue;
            }
            m_redisMap.insert(std::pair<unsigned short,boost::shared_ptr<RedisMem> >(redisMem->getID(),redisMem));
        }
        ret = m_redisMap.empty() ? false : true;
    }while(false);
    char temp[100] = {0};
    snprintf(temp,sizeof(temp),"[redis管理器] 加载配置%s",ret ? "成功" : "失败");
    Info(Flyer::logger,temp);
    return ret;
}

boost::shared_ptr<RedisMem> RedisMemManager::getRedis(const unsigned short id)
{
    unsigned int key = id % m_redisMap.size() + 1;
    boost::shared_ptr<RedisMem> redisMem(NULL);
    pthread_mutex_lock(&m_mutex);
    auto iter = m_redisMap.find(key);
    if(iter != m_redisMap.end())
    {
        redisMem = iter->second;
    }
    pthread_mutex_unlock(&m_mutex);
    return redisMem;
}

void RedisMemManager::clearMemory()
{
    pthread_mutex_lock(&m_mutex);
    for(auto iter = m_redisMap.begin();iter != m_redisMap.end();++iter)
    {
        boost::shared_ptr<RedisMem> redisMem = iter->second;
        redisMem->exeCmd("FLUSHALL");
    }
    pthread_mutex_unlock(&m_mutex);
}
