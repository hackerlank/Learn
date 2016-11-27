#ifndef REDIS_MEM_MANAGER_H
#define REDIS_MEM_MANAGER_H 
#include "redisMem.h"
#include "singleton.h"
#include <pthread.h> 
#include "head.h"

class RedisMemManager : public Singleton<RedisMemManager>
{
    private:
        friend class Singleton<RedisMemManager>;
        RedisMemManager();
        ~RedisMemManager();
    private:
        pthread_mutex_t m_mutex;
        std::map<unsigned long,std::map<unsigned short,boost::shared_ptr<RedisMem> > > m_redisMap;
        std::vector<std::pair<std::string,unsigned short> > m_confVec;
    public:
        bool init();
        boost::shared_ptr<RedisMem> getRedis(const unsigned short id = 0);
        void clearMemory();
};

#endif

