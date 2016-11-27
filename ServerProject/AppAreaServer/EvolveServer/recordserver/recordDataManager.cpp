#include "recordDataManager.h"
#include "mysqlPool.h"
#include "flyerValue.h"
#include "redisMemManager.h"
#include "head.h"
#include "serialize.pb.h"

unsigned long RecordDataManager::s_charID = 0; 
RecordDataManager::RecordDataManager()
{
}

RecordDataManager::~RecordDataManager()
{
}

bool RecordDataManager::init()
{
    bool ret = false;
    do
    {
        if(!loadUserData())
        {
            break;
        }
        ret = true;
    }while(false);
    return ret;
}

bool RecordDataManager::loadUserData()
{
    bool ret = false;
    boost::shared_ptr<MysqlHandle> handle = MysqlPool::getInstance().getIdleHandle();
    if(!handle)
    {
        return ret;
    }
    do
    {
        std::vector<std::map<std::string,Flyer::FlyerValue> > ipVec;
        char temp[100] = {0};
        snprintf(temp,sizeof(temp),"select * from t_user");
        if(!handle->select(temp,strlen(temp),ipVec))
        {
            break;
        }
        for(unsigned int cnt = 0;cnt < ipVec.size();++cnt)
        {
            std::map<std::string,Flyer::FlyerValue> &tempMap = ipVec[cnt];
            if(tempMap.find("charid") == tempMap.end())
            {
                continue;
            }
            unsigned long charID = tempMap["charid"];
            std::string binary = tempMap["binary"];
            char buffer[Flyer::msglen];
            bzero(buffer,sizeof(buffer));
            memmove(buffer,binary.c_str(),binary.size());
            ProtoMsgData::UserBinary userBinary;
            bool isLoad = true;
            try
            {
                userBinary.ParseFromArray(buffer,binary.size());
            }
            catch(...)
            {
                isLoad = false;
            }

            Info(Flyer::logger,"[加载角色信息] (" << charID << "," << isLoad << ")");
            if(!isLoad || userBinary.charid() != charID)
            {
                continue;
            }
            boost::shared_ptr<RedisMem> redisMem = RedisMemManager::getInstance().getRedis();
            if(!redisMem)
            {
                break;
            }
            if(!redisMem->setInt("charid",userBinary.phone().c_str(),charID))
            {
                break;
            }
            redisMem = RedisMemManager::getInstance().getRedis(charID);
            if(!redisMem)
            {
                break;
            }
            if(!redisMem->setString("phone",charID,userBinary.phone().c_str()))
            {
                break;
            }
            if(!redisMem->setBin("userbinary",charID,buffer,binary.size()))
            {
                break;
            }
        }
        ipVec.clear();
        bzero(temp,sizeof(temp));
        snprintf(temp,sizeof(temp),"select max(charid) as charid from t_user");
        if(!handle->select(temp,strlen(temp),ipVec))
        {
            break;
        }
        for(unsigned int cnt = 0;cnt < ipVec.size();++cnt)
        {
            std::map<std::string,Flyer::FlyerValue> &tempMap = ipVec[cnt];
            if(tempMap.find("charid") != tempMap.end())
            {
                s_charID = tempMap["charid"];
            }
            break;
        }
        ret = true;
    }while(false);
    handle->resetStatus();
    Info(Flyer::logger,"[加载角色信息完毕] (" << s_charID << "," << ret << ")")
    return ret;
}

bool RecordDataManager::loop(const unsigned cycle)
{
    unsigned int cycleTotal = atol(Flyer::globalConfMap["dbcycle"].c_str());
    bool ret = false;
    boost::shared_ptr<MysqlHandle> handle = MysqlPool::getInstance().getIdleHandle();
    if(!handle)
    {
        return ret;
    }
    do
    {
        boost::shared_ptr<RedisMem> redisMem = RedisMemManager::getInstance().getRedis();
        if(!redisMem)
        {
            break;
        }
        std::set<unsigned long> idSet;
        if(!redisMem->getSet("serialize","userset",idSet))
        {
            break;
        }
        for(auto iter = idSet.begin();iter != idSet.end();++iter)
        {
            bool flag = false;
            unsigned long charID = *iter;
            if(charID % cycleTotal != cycle)
            {
                continue;
            }
            do
            {
                redisMem = RedisMemManager::getInstance().getRedis(charID);
                if(!redisMem)
                {
                    break;
                }
                char buffer[Flyer::msglen];
                bzero(buffer,sizeof(buffer));
                unsigned int size = redisMem->getBin("serialize",charID,"user",buffer);
                if(!size)
                {
                    break;
                }
                redisMem = RedisMemManager::getInstance().getRedis();
                if(!redisMem)
                {
                    break;
                }
                if(!redisMem->delSet("serialize",charID,"userset"))
                {
                    break;
                }
                ProtoMsgData::UserBinary binary;
                binary.ParseFromArray(buffer,size);
                std::ostringstream oss;
                oss << "update t_user set `phone` = '" << binary.phone() << "'," << "`binary` = ";
                handle->getRealString(buffer,binary.ByteSize(),oss);
                oss << " where charid = " << charID;
                if(!handle->execSql(oss.str().c_str(),oss.str().size()))
                {
                    break;
                }
                flag = true;
            }while(false);
            if(!flag)
            {
                Debug(Flyer::logger,"[数据库存档角色数据]失败(" << charID << ")");
            }
        }
        ret = true;
    }while(false);
    handle->resetStatus();
    return ret;
}

bool RecordDataManager::createUser(const std::string &phone,unsigned long &charID)
{
    bool ret = false;
    boost::shared_ptr<MysqlHandle> handle = MysqlPool::getInstance().getIdleHandle();
    if(!handle)
    {
        return ret;
    }
    do
    {
        ProtoMsgData::UserBinary binary;
        binary.set_phone(phone);
        binary.set_charid(s_charID + 1);
        binary.set_ontime(0);
        binary.set_offtime(0);
        char buffer[Flyer::msglen];
        bzero(buffer,sizeof(buffer));
        binary.SerializeToArray(buffer,sizeof(buffer));
        std::ostringstream oss;
        oss << "insert into t_user values(" << binary.charid() << ",'" << binary.phone() << "',";
        handle->getRealString(buffer,binary.ByteSize(),oss);
        oss << ")";
        if(!handle->execSql(oss.str().c_str(),oss.str().size()))
        {
            break;
        }
        s_charID += 1;
        boost::shared_ptr<RedisMem> redisMem = RedisMemManager::getInstance().getRedis();
        if(!redisMem)
        {
            break;
        }
        if(!redisMem->setInt("charid",binary.phone().c_str(),binary.charid()))
        {
            break;
        }
        redisMem = RedisMemManager::getInstance().getRedis(binary.charid());
        if(!redisMem)
        {
            break;
        }
        if(!redisMem->setString("phone",binary.charid(),binary.phone().c_str()))
        {
            break;
        }
        if(!redisMem->setBin("userbinary",binary.charid(),buffer,binary.ByteSize()))
        {
            break;
        }
        unsigned long getCharID = redisMem->getInt("charid",binary.phone().c_str());
        if(binary.charid() != getCharID)
        {
            Debug(Flyer::logger,"[redis取错误](" << getCharID << "," << binary.charid() << "," << binary.phone() << ")");
            break;
        }
        charID = binary.charid();
        ret = true;
    }while(false);
    handle->resetStatus();
    char temp[100] = {0};
    snprintf(temp,sizeof(temp),"[新建角色] %s(%s)",ret ? "成功" : "失败", phone.c_str());
    Info(Flyer::logger,temp);
    return ret;
}

