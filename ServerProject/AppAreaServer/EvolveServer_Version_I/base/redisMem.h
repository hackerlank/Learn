#ifndef REDIS_MEM_H
#define REDIS_MEM_H
#include "hiredis.h"
#include <string>
#include "flyerValue.h"
#include <set>

enum RedisDataType
{
    RDT_Int = 0, //整数
    RDT_String = 1,//字符串
    RDT_Bin = 2,//二进制
};


class RedisMem
{
    private:
        unsigned short m_id;
        std::string m_host;
        unsigned short m_port;
        redisContext *m_redis; 
        redisReply *m_reply;
    public:
        RedisMem(const unsigned short id,const std::string &host,const unsigned short port);
        ~RedisMem();
        bool init();
        inline unsigned short getID() const
        {
            return m_id;
        }
    private:
        bool disConnect();
        bool isConnect();
        bool excelRetCheck();
        bool isReplyOK();
        Flyer::FlyerValue getVal(const RedisDataType &redisDataType);
    public:
        void exeCmd(const char *cmd);
        bool setInt(const char* table,const unsigned long key,const unsigned long value);
        bool delInt(const char* table,const unsigned long key);
        Flyer::FlyerValue getInt(const char* table,const unsigned long key);
        bool setInt(const char* table,const char *key,const unsigned long value);
        bool delInt(const char* table,const char *key);
        Flyer::FlyerValue getInt(const char* table,const char *key);
        bool setInt(const char* table,const unsigned long key,const char *col,const unsigned long value);
        bool delInt(const char* table,const unsigned long key,const char *col);
        Flyer::FlyerValue getInt(const char* table,const unsigned long key,const char *col);

        bool setString(const char* table,const char *key,const char *value);
        bool delString(const char* table,const unsigned long key);
        Flyer::FlyerValue getString(const char* table,const char *key);

        bool setString(const char* table,const unsigned long key,const char *value);
        bool delString(const char* table,const char *key);
        Flyer::FlyerValue getString(const char* table,const unsigned long key);

        bool setSet(const char* table,const unsigned long key,const char *set,const unsigned long value);
        bool delSet(const char* table,const unsigned long key,const char *set);
        bool getSet(const char* table,const unsigned long key,const char *set,std::set<std::string> &retSet,const unsigned int cnt = 10000);
        bool setBin(const char* table,const unsigned long key,const char *col,const char *val,const unsigned int len);
        unsigned int getBin(const char* table,const unsigned long key,const char *col,char *val);
        bool setSet(const char* table,const char *set,const unsigned long value);
        bool delSet(const char* table,const char *set);
        bool getSet(const char* table,const char *set,std::set<std::string> &retSet,const unsigned int cnt = 10000);
        bool getSet(const char* table,const char *set,std::set<std::string> &retSet);
        bool setBin(const char* table,const unsigned long key,const char *val,const unsigned int len);
        bool delBin(const char* table,const unsigned long key);
        unsigned int getBin(const char* table,const unsigned long key,char *val);
        bool getSet(const char* table,const char *set,std::set<unsigned long> &retSet,const unsigned int cnt);
        bool getSet(const char* table,const char *set,std::set<unsigned long> &retSet);
        bool delBin(const char* table,const unsigned long key,const char *col);


};

#endif
