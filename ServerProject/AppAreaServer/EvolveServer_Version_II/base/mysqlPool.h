#ifndef MYSQL_POOL_H
#define MYSQL_POOL_H
#include "mysqlUrl.h"
#include "mysqlHandle.h"
#include "singleton.h"
#include "head.h"

class MysqlPool : public Singleton<MysqlPool>
{
    private:
        std::map<unsigned short,UrlInfo> m_codeUrlMap;
        std::map<unsigned short,std::set<unsigned int> >m_codeHandeMap;
        std::map<unsigned int,boost::shared_ptr<MysqlHandle> >m_handleMap;
        pthread_mutex_t m_mutex;
    private:
        friend class Singleton<MysqlPool>;
        MysqlPool();
        ~MysqlPool();
        boost::shared_ptr<MysqlHandle> getHandle(const unsigned int id);
    public:
        boost::shared_ptr<MysqlHandle> getIdleHandle(const unsigned short code = 0);
        bool addUrl(const std::string &_url);
};

#endif
