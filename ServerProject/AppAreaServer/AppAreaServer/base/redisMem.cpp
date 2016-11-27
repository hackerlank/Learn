#include "redisMem.h"
#include "flyer.h"

RedisMem::RedisMem(const unsigned short id,const std::string &host,const unsigned short port) : m_id(id),m_host(host),m_port(port),m_redis(NULL),m_reply(NULL)
{
}

RedisMem::~RedisMem()
{
    disConnect();
}

bool RedisMem::init()
{
    //1.5秒超时
    struct timeval timeout = { 1, 500000 };
    disConnect();
    m_redis = redisConnectWithTimeout(m_host.c_str(),m_port,timeout);
    if(m_redis->err)
    {
        char temp[100] = {0};
        snprintf(temp,sizeof(temp),"[redis缓存] 初始化失败(%s,%u,%s)",m_host.c_str(),m_port,m_redis->errstr);
        Error(Flyer::logger,temp);
        redisFree(m_redis);
        m_redis = NULL;
        return false;
    }
    return true;
}

bool RedisMem::disConnect()
{
    if(m_redis)
    {
        if(m_reply)
        {
            freeReplyObject(m_reply);
            m_reply = NULL;
        }
        redisFree(m_redis);
        m_redis = NULL;
    }
    Info(Flyer::logger,"[redis缓存] 断开连接(" << m_host << "," << m_port << ")");
    return true;
}

bool RedisMem::isConnect()
{
    bool ret = false;
    do
    {
        if(!m_redis)
        {
            init();
        }
        if(!m_redis)
        {
            Info(Flyer::logger,"[redis缓存] 断开连接(" << m_host << "," << m_port << ")");
            break;
        }
        if(m_reply)
        {
            freeReplyObject(m_reply);
            m_reply = NULL;
        }
        ret = true;
    }while(false);
    return ret;
}

bool RedisMem::excelRetCheck()
{
    bool ret = false;
    do
    {
        if(!m_reply)
        {
            disConnect();
            break;
        }
        if(m_reply->type != REDIS_REPLY_ERROR)
        {
            ret = true;
        }
        freeReplyObject(m_reply);
        m_reply = NULL;
    }while(false);
    return ret;
}


bool RedisMem::setInt(const char* table,const unsigned long key,const unsigned long value)
{
    do
    {
        if(!isConnect())
        {
            break;
        }
        if(key)
        {
            m_reply = (redisReply*)redisCommand(m_redis,"SET %s:[%lu] %lu",table,key,value);
            break;
        }
        m_reply = (redisReply*)redisCommand(m_redis,"SET %s %lu",table,value);
    }while(false);
    return excelRetCheck();
}

bool RedisMem::delInt(const char* table,const unsigned long key)
{
    do
    {
        if(!isConnect())
        {
            break;
        }
        if(key)
        {
            m_reply = (redisReply*)redisCommand(m_redis,"DEL %s:[%lu]",table,key);
            break;
        }
        m_reply = (redisReply*)redisCommand(m_redis,"DEL %s",table);
    }while(false);
    return excelRetCheck();
}

Flyer::FlyerValue RedisMem::getInt(const char* table,const unsigned long key)
{
    do
    {
        if(!isConnect())
        {
            break;
        }
        if(m_id)
        {
            m_reply = (redisReply*)redisCommand(m_redis,"GET %s:[%lu]",table,key);
            break;
        }
        m_reply = (redisReply*)redisCommand(m_redis,"GET %s",table);
    }while(false);
    return getVal(RDT_Int);
}

bool RedisMem::setInt(const char* table,const char *key,const unsigned long value)
{
    do
    {
        if(!isConnect())
        {
            break;
        }
        if(key)
        {
            m_reply = (redisReply*)redisCommand(m_redis,"SET %s:[%s] %lu",table,key,value);
            break;
        }
        m_reply = (redisReply*)redisCommand(m_redis,"SET %s %lu",table,value);
    }while(false);
    bool ret = excelRetCheck();
    return ret;
}

bool RedisMem::delInt(const char* table,const char *key)
{
    do
    {
        if(!isConnect())
        {
            break;
        }
        if(key)
        {
            m_reply = (redisReply*)redisCommand(m_redis,"DEL %s:[%s]",table,key);
            break;
        }
        m_reply = (redisReply*)redisCommand(m_redis,"DEL %s",table);
    }while(false);
    return excelRetCheck();
}

Flyer::FlyerValue RedisMem::getInt(const char* table,const char *key)
{
    do
    {
        if(!isConnect())
        {
            break;
        }
        if(m_id)
        {
            m_reply = (redisReply*)redisCommand(m_redis,"GET %s:[%s]",table,key);
            break;
        }
        m_reply = (redisReply*)redisCommand(m_redis,"GET %s",table);
    }while(false);
    return getVal(RDT_Int);
}

bool RedisMem::setInt(const char* table,const unsigned long key,const char *col,const unsigned long value)
{
    do
    {
        if(!isConnect())
        {
            break;
        }
        if(col)
        {
            m_reply = (redisReply*)redisCommand(m_redis,"SET %s:[%lu]:%s %lu",table,key,col,value);
            break;
        }
        if(key)
        {
            m_reply = (redisReply*)redisCommand(m_redis,"SET %s:[%lu] %lu",table,key,value);
            break;
        }
        m_reply = (redisReply*)redisCommand(m_redis,"SET %s %lu",table,value);
    }while(false);
    return excelRetCheck();
}

bool RedisMem::delInt(const char* table,const unsigned long key,const char *col)
{
    do
    {
        if(!isConnect())
        {
            break;
        }
        if(col)
        {
            m_reply = (redisReply*)redisCommand(m_redis,"DEL %s:[%lu]:%s",table,key,col);
            break;
        }
        if(key)
        {
            m_reply = (redisReply*)redisCommand(m_redis,"DEL %s:[%lu]",table,key);
            break;
        }
        m_reply = (redisReply*)redisCommand(m_redis,"DEL %s",table);
    }while(false);
    return excelRetCheck();
}

Flyer::FlyerValue RedisMem::getInt(const char* table,const unsigned long key,const char *col)
{
    do
    {
        if(!isConnect())
        {
            break;
        }
        if(col)
        {
            m_reply = (redisReply*)redisCommand(m_redis,"GET %s:[%lu]:%s",table,key,col);
            break;
        }
        if(key)
        {
            m_reply = (redisReply*)redisCommand(m_redis,"GET %s:[%lu]",table,key);
            break;
        }
        m_reply = (redisReply*)redisCommand(m_redis,"GET %s",table);
    }while(false);
    return getVal(RDT_Int);
}

bool RedisMem::setString(const char* table,const unsigned long key,const char *value)
{
    do
    {
        if(!isConnect())
        {
            break;
        }
        if(key)
        {
            m_reply = (redisReply*)redisCommand(m_redis,"SET %s:[%lu] %s",table,key,value);
            break;
        }
        m_reply = (redisReply*)redisCommand(m_redis,"SET %s %s",table,value);
    }while(false);
    return excelRetCheck();
}

bool RedisMem::delString(const char* table,const unsigned long key)
{
    do
    {
        if(!isConnect())
        {
            break;
        }
        if(key)
        {
            m_reply = (redisReply*)redisCommand(m_redis,"DEL %s:[%lu]",table,key);
            break;
        }
        m_reply = (redisReply*)redisCommand(m_redis,"DEL %s",table);
    }while(false);
    return excelRetCheck();
}

Flyer::FlyerValue RedisMem::getString(const char* table,const unsigned long key)
{
    do
    {
        if(!isConnect())
        {
            break;
        }
        if(m_id)
        {
            m_reply = (redisReply*)redisCommand(m_redis,"GET %s:[%lu]",table,key);
            break;
        }
        m_reply = (redisReply*)redisCommand(m_redis,"GET %s",table);
    }while(false);
    return getVal(RDT_String);
}

bool RedisMem::setString(const char* table,const char *key,const char *value)
{
    do
    {
        if(!isConnect())
        {
            break;
        }
        if(key)
        {
            m_reply = (redisReply*)redisCommand(m_redis,"SET %s:[%s] %s",table,key,value);
            break;
        }
        m_reply = (redisReply*)redisCommand(m_redis,"SET %s %s",table,value);
    }while(false);
    return excelRetCheck();
}

bool RedisMem::delString(const char* table,const char *key)
{
    do
    {
        if(!isConnect())
        {
            break;
        }
        if(key)
        {
            m_reply = (redisReply*)redisCommand(m_redis,"DEL %s:[%s]",table,key);
            break;
        }
        m_reply = (redisReply*)redisCommand(m_redis,"DEL %s %s",table);
    }while(false);
    return excelRetCheck();
}

Flyer::FlyerValue RedisMem::getString(const char* table,const char *key)
{
    do
    {
        if(!isConnect())
        {
            break;
        }
        if(m_id)
        {
            m_reply = (redisReply*)redisCommand(m_redis,"GET %s:[%s]",table,key);
            break;
        }
        m_reply = (redisReply*)redisCommand(m_redis,"GET %s",table);
    }while(false);
    return getVal(RDT_String);
}

bool RedisMem::setSet(const char* table,const unsigned long key,const char *set,const unsigned long value)
{
    do
    {
        if(!isConnect())
        {
            break;
        }
        if(set)
        {
            m_reply = (redisReply*)redisCommand(m_redis,"SADD %s:[%lu]:%s %lu",table,key,set,value);
            break;
        }
        if(key)
        {
            m_reply = (redisReply*)redisCommand(m_redis,"SADD %s:[%lu] %lu",table,key,value);
            break;
        }
        m_reply = (redisReply*)redisCommand(m_redis,"SADD %s %lu",table,value);
    }while(false);
    return excelRetCheck();
}

bool RedisMem::delSet(const char* table,const unsigned long key,const char *set)
{
    do
    {
        if(!isConnect())
        {
            break;
        }
        if(set)
        {
            m_reply = (redisReply*)redisCommand(m_redis,"DEL %s:[%lu]:%s",table,key,set);
            break;
        }
        if(key)
        {
            m_reply = (redisReply*)redisCommand(m_redis,"DEL %s:[%lu]",table,key);
            break;
        }
        m_reply = (redisReply*)redisCommand(m_redis,"DEL %s",table);
    }while(false);
    return excelRetCheck();
}

bool RedisMem::getSet(const char* table,const unsigned long key,const char *set,std::set<std::string> &retSet,const unsigned int cnt)
{
    bool ret = false;
    do
    {
        if(!isConnect())
        {
            break;
        }
        if(set)
        {
            m_reply = (redisReply*)redisCommand(m_redis,"SRANDMEMBER %s:[%lu]:%s %u",table,key,set,cnt);
            break;
        }
        if(key)
        {
            m_reply = (redisReply*)redisCommand(m_redis,"SRANDMEMBER %s:[%lu] %u",table,key,cnt);
            break;
        }
        m_reply = (redisReply*)redisCommand(m_redis,"SRANDMEMBER %s %u",table,cnt);
    }while(false);
    if(isReplyOK())
    {
        if(m_reply && m_reply->type == REDIS_REPLY_ARRAY)
        {
            for(unsigned int num = 0; num < m_reply->elements;++num)
            {
                retSet.insert(m_reply->element[num]->str);
            }
            ret = true;
        }
    }
    return ret;
}

bool RedisMem::getSet(const char* table,const char *set,std::set<unsigned long> &retSet,const unsigned int cnt)
{
    bool ret = false;
    do
    {
        if(!isConnect())
        {
            break;
        }
        if(set)
        {
            m_reply = (redisReply*)redisCommand(m_redis,"SMEMBERS %s:%s %u",table,set,cnt);
            break;
        }
        m_reply = (redisReply*)redisCommand(m_redis,"SMEMBERS %s %u",table,cnt);
    }while(false);
    if(isReplyOK())
    {
        if(m_reply && m_reply->type == REDIS_REPLY_ARRAY)
        {
            for(unsigned int num = 0; num < m_reply->elements;++num)
            {
                retSet.insert(atol(m_reply->element[num]->str));
            }
            ret = true;
        }
    }
    return ret;
}

bool RedisMem::getSet(const char* table,const char *set,std::set<unsigned long> &retSet)
{
    bool ret = false;
    do
    {
        if(!isConnect())
        {
            break;
        }
        if(set)
        {
            m_reply = (redisReply*)redisCommand(m_redis,"SMEMBERS %s:%s ",table,set);
            break;
        }
        m_reply = (redisReply*)redisCommand(m_redis,"SMEMBERS %s ",table);
    }while(false);
    if(isReplyOK())
    {
        if(m_reply && m_reply->type == REDIS_REPLY_ARRAY)
        {
            for(unsigned int num = 0; num < m_reply->elements;++num)
            {
                retSet.insert(atol(m_reply->element[num]->str));
            }
            ret = true;
        }
    }
    return ret;
}


bool RedisMem::setSet(const char* table,const char *set,const unsigned long value)
{
    do
    {
        if(!isConnect())
        {
            break;
        }
        if(set)
        {
            m_reply = (redisReply*)redisCommand(m_redis,"SADD %s:%s %lu",table,set,value);
            break;
        }
        m_reply = (redisReply*)redisCommand(m_redis,"SADD %s %lu",table,value);
    }while(false);
    return excelRetCheck();
}

bool RedisMem::delSet(const char* table,const char *set)
{
    do
    {
        if(!isConnect())
        {
            break;
        }
        if(set)
        {
            m_reply = (redisReply*)redisCommand(m_redis,"DEL %s:%s",table,set);
            break;
        }
        m_reply = (redisReply*)redisCommand(m_redis,"DEL %s",table);
    }while(false);
    return excelRetCheck();
}

bool RedisMem::getSet(const char* table,const char *set,std::set<std::string> &retSet,const unsigned int cnt)
{
    bool ret = false;
    do
    {
        if(!isConnect())
        {
            break;
        }
        if(set)
        {
            m_reply = (redisReply*)redisCommand(m_redis,"SRANDMEMBER %s:%s %u",table,set,cnt);
            break;
        }
        m_reply = (redisReply*)redisCommand(m_redis,"SRANDMEMBER %s %u",table,cnt);
    }while(false);
    if(isReplyOK())
    {
        if(m_reply && m_reply->type == REDIS_REPLY_ARRAY)
        {
            for(unsigned int num = 0; num < m_reply->elements;++num)
            {
                retSet.insert(m_reply->element[num]->str);
            }
            ret = true;
        }
    }
    return ret;
}

bool RedisMem::getSet(const char* table,const char *set,std::set<std::string> &retSet)
{
    bool ret = false;
    do
    {
        if(!isConnect())
        {
            break;
        }
        if(set)
        {
            m_reply = (redisReply*)redisCommand(m_redis,"SRANDMEMBER %s:%s ",table,set);
            break;
        }
        m_reply = (redisReply*)redisCommand(m_redis,"SRANDMEMBER %s ",table);
    }while(false);
    if(isReplyOK())
    {
        if(m_reply && m_reply->type == REDIS_REPLY_ARRAY)
        {
            for(unsigned int num = 0; num < m_reply->elements;++num)
            {
                retSet.insert(m_reply->element[num]->str);
            }
            ret = true;
        }
    }
    return ret;
}

bool RedisMem::setBin(const char* table,const unsigned long key,const char *val,const unsigned int len)
{
    do
    {
        if(!isConnect())
        {
            break;
        }
        if(key)
        {
            m_reply = (redisReply*)redisCommand(m_redis,"SET %s:[%lu] %b",table,key,val,len);
            break;
        }
        m_reply = (redisReply*)redisCommand(m_redis,"SET %s %b",table,val,len);
    }while(false);
    return excelRetCheck();
}

bool RedisMem::delBin(const char* table,const unsigned long key)
{
    do
    {
        if(!isConnect())
        {
            break;
        }
        if(key)
        {
            m_reply = (redisReply*)redisCommand(m_redis,"DEL %s:[%lu]",table,key);
            break;
        }
        m_reply = (redisReply*)redisCommand(m_redis,"DEL %s",table);
    }while(false);
    return excelRetCheck();
}

unsigned int RedisMem::getBin(const char* table,const unsigned long key,char *val)
{
    bool ret = true;
    unsigned int len = 0;
    do
    {
        if(!isConnect())
        {
            break;
            ret = false;
        }
        if(key)
        {
            m_reply = (redisReply*)redisCommand(m_redis,"GET %s:[%lu]",table,key);
            break;
        }
        m_reply = (redisReply*)redisCommand(m_redis,"SET %s ",table);
    }while(false);

    if(ret)
    {
        if(m_reply && m_reply->type == REDIS_REPLY_STRING)
        {
            memcpy(val,m_reply->str,m_reply->len);
            len = m_reply->len;
        }
    }
    freeReplyObject(m_reply);
    m_reply = NULL;
    return len;
}

bool RedisMem::setBin(const char* table,const unsigned long key,const char *col,const char *val,const unsigned int len)
{
    do
    {
        if(!isConnect())
        {
            break;
        }
        if(col)
        {
            m_reply = (redisReply*)redisCommand(m_redis,"SET %s:[%lu]:%s %b",table,key,col,val,len);
            break;
        }
        if(key)
        {
            m_reply = (redisReply*)redisCommand(m_redis,"SET %s:[%lu] %b",table,key,val,len);
            break;
        }
        m_reply = (redisReply*)redisCommand(m_redis,"SET %s %b",table,val,len);
    }while(false);
    return excelRetCheck();
}

bool RedisMem::delBin(const char* table,const unsigned long key,const char *col)
{
    do
    {
        if(!isConnect())
        {
            break;
        }
        if(col)
        {
            m_reply = (redisReply*)redisCommand(m_redis,"DEL %s:[%lu]",table,key,col);
            break;
        }
        if(key)
        {
            m_reply = (redisReply*)redisCommand(m_redis,"SET %s:[%lu]",table,key);
            break;
        }
        m_reply = (redisReply*)redisCommand(m_redis,"SET %s",table);
    }while(false);
    return excelRetCheck();
}

unsigned int RedisMem::getBin(const char* table,const unsigned long key,const char *col,char *val)
{
    bool ret = true;
    unsigned int len = 0;
    do
    {
        if(!isConnect())
        {
            break;
            ret = false;
        }
        if(col)
        {
            m_reply = (redisReply*)redisCommand(m_redis,"GET %s:[%lu]:%s",table,key,col);
            break;
        }
        if(key)
        {
            m_reply = (redisReply*)redisCommand(m_redis,"SET %s:[%lu]",table,key);
            break;
        }
        m_reply = (redisReply*)redisCommand(m_redis,"SET %s ",table);
    }while(false);

    if(ret)
    {
        if(m_reply && m_reply->type == REDIS_REPLY_STRING)
        {
            memcpy(val,m_reply->str,m_reply->len);
            len = m_reply->len;
        }
    }
    freeReplyObject(m_reply);
    m_reply = NULL;
    return len;
}

bool RedisMem::isReplyOK()
{
    return m_reply != NULL;
}

Flyer::FlyerValue RedisMem::getVal(const RedisDataType &redisDataType)
{
    Flyer::FlyerValue ret;
    do
    {
        if(!isReplyOK()) 
        {
            disConnect();
            break;
        }
        switch(m_reply->type)
        {
            case REDIS_REPLY_STATUS:
            {
            }
            break;
            case REDIS_REPLY_ERROR:
            {
                Info(Flyer::logger,"[redis缓存] 执行错误(" << m_reply->str << ")");
            }
            break;
            case REDIS_REPLY_INTEGER:
            {
                if(redisDataType == RDT_Int)
                {    
                    ret = m_reply->integer;
                }
            } 
            break;
        case REDIS_REPLY_NIL:
            {
            }
            break;
        case REDIS_REPLY_STRING:
            {
                //只处理基本类型，INT,STRING,BIN
                if(redisDataType == RDT_Int)
                {
                    ret = atol(m_reply->str);
                }
                else if(redisDataType == RDT_String)
                {
                    std::string val(m_reply->str,m_reply->len);
                    ret = val;
                }
                else 
                {
                    //default,暂时未用
                    std::string val(m_reply->str,m_reply->len);
                    ret = val;
                }
            }
            break;
        case REDIS_REPLY_ARRAY:
            {
                //set,vector,list,不在此处理
            }
            break;
        default:
            {
            }
            break;
        }
    }while(false);

    freeReplyObject(m_reply);
    m_reply = NULL;
    return ret;
}

void RedisMem::exeCmd(const char *cmd)
{
    if(m_reply)
    {
        freeReplyObject(m_reply);
        m_reply = NULL;
    }
    m_reply = (redisReply*)redisCommand(m_redis,cmd);
    freeReplyObject(m_reply);
    m_reply = NULL;
}
