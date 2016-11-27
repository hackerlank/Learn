#include "loginTask.h"
#include "flyerValue.h"
#include "mysqlPool.h"
#include "common.pb.h"
#include "taskManager.h"
#include "redisMemManager.h"
#include "mainThread.h"

LoginMessageDispatcher LoginTask::s_loginMsgDispatcher("登陆服务器消息处理器");
LoginTask::LoginTask(const int fd) : Task(fd),m_charID(0)
{
}

LoginTask::~LoginTask()
{
}

MsgRet LoginTask::dispatcher(boost::shared_ptr<google::protobuf::Message> message)
{
    MsgRet ret = MR_No_Register;
    ret = Task::dispatcher(message);
    if(ret == MR_No_Register)
    {
        boost::shared_ptr<Task> task = TaskManager::getInstance().getTask(m_id);
        boost::shared_ptr<LoginTask> loginTask = boost::dynamic_pointer_cast<LoginTask>(task);
        if(loginTask)
        {
            ret = s_loginMsgDispatcher.dispatch(loginTask,message);
        }
    }
    return ret;
}

bool LoginTask::registerAccount(boost::shared_ptr<ProtoMsgData::ReqRegister> message)
{
    bool ret = false;
    boost::shared_ptr<MysqlHandle> handle = MysqlPool::getInstance().getIdleHandle();
    if(!handle)
    {
        return ret;
    }
    ProtoMsgData::ErrorCode code = ProtoMsgData::EC_Default;
    do
    {
        boost::shared_ptr<RedisMem> redisMem = RedisMemManager::getInstance().getRedis();
        if(!redisMem)
        {
            break;
        }
        std::string passwd = redisMem->getString("register",message->phone().c_str());
        if(!passwd.empty())
        {
            code = ProtoMsgData::EC_Register_Again;
            break;
        }
        std::ostringstream oss;
        oss << "insert into t_register(phone,passwd,regtime) values" << "('" << message->phone() << "'," << "'" << message->passwd() << "',current_timestamp)"; 
        if(!handle->execSql(oss.str().c_str(),oss.str().size()))
        {
            break;
        }
        if(!redisMem->setString("register",message->phone().c_str(),message->passwd().c_str()))
        {
            break;
        }
        std::string getKey =  redisMem->getString("register",message->phone().c_str());
        Info(Flyer::logger,"[注册取回](" << getKey << ")");
        ret = true;
    }while(false);
    handle->resetStatus();
    if(code != ProtoMsgData::EC_Default)
    {
        ProtoMsgData::AckErrorCode ackMsg;
        ackMsg.set_code(code);
        sendMsg(ackMsg);
    }
    ProtoMsgData::AckRegister ackMsg;
    ackMsg.set_ret(ret);
    sendMsg(ackMsg);
    std::ostringstream oss;
    oss << "[注册 " << (ret ? "成功" : "失败") << "] (" << message->phone() << "," << message->passwd() << ")";
    Debug(Flyer::logger,oss.str().c_str());
    return ret;
}

bool LoginTask::getGatewayInfo(boost::shared_ptr<ProtoMsgData::ReqGateway> message)
{
    bool ret = false;
    ProtoMsgData::ErrorCode code = ProtoMsgData::EC_Default;
    ProtoMsgData::AckGateway ackMsg;
    do
    {
        boost::shared_ptr<RedisMem> redisMem = RedisMemManager::getInstance().getRedis();
        if(!redisMem)
        {
            break;
        }
        std::string passwd = redisMem->getString("register",message->phone().c_str());
        if(passwd.empty())
        {
            code = ProtoMsgData::EC_Register_No;
            break;
        }
        if(passwd.compare(message->passwd()))
        {
            code = ProtoMsgData::EC_Passwd_Wrong;
            break;
        }
        if(!hasCreateUser(message->phone()))
        {
            ret = createUser(message->phone());
            break;
        }
        if(!findGateway(message->phone(),ackMsg))
        {
            break;
        }
        ret = true;
    }while(false);
    if(code != ProtoMsgData::EC_Default)
    {
        ProtoMsgData::AckErrorCode ackMsg;
        ackMsg.set_code(code);
        sendMsg(ackMsg);
    }
    if(ret)
    {
        if(m_charID)
        {
            ackMsg.set_ret(ret);
            sendMsg(ackMsg);
            ThreadPool::getInstance().addRecycleFromVerify(m_id);
        }
        else
        {
            setVerify(true);
        }
    }
    else
    {
        ackMsg.set_ret(ret);
        sendMsg(ackMsg);
        ThreadPool::getInstance().addRecycleFromVerify(m_id);
    }

    std::ostringstream oss;
    oss << "[请求登陆网关" << (ret ? "成功" : "失败") << "] (" << message->phone() << "," << message->passwd() << "," << ackMsg.ip() << "," << ackMsg.port() << "," << m_charID << "," << code << ")"; 
    Debug(Flyer::logger,oss.str().c_str());
    return ret;
}

bool LoginTask::hasCreateUser(const std::string phone)
{
    bool ret = false;
    do
    {
        boost::shared_ptr<RedisMem> redisMem = RedisMemManager::getInstance().getRedis();
        if(!redisMem)
        {
            break;
        }
        m_charID = redisMem->getInt("charid",phone.c_str());
        if(!m_charID)
        {
            break;
        }
        ret = true;
    }while(false);
    return ret;
}
 
bool LoginTask::createUser(const std::string phone)
{
    bool ret = false;
    do
    {
        boost::shared_ptr<RedisMem> redisMem = RedisMemManager::getInstance().getRedis();
        if(!redisMem)
        {
            break;
        }
        unsigned long charID = redisMem->getInt("charid",phone.c_str());
        if(charID)
        {
            break;
        }
        ProtoMsgData::ReqCreateUser reqMsg;
        reqMsg.set_phone(phone);
        reqMsg.set_id(getID());
        boost::shared_ptr<Task> task = TaskManager::getInstance().getServerTaskByType(ProtoMsgData::ST_Super);
        if(!task)
        {
            break;
        }
        std::ostringstream oss;
        oss << "[请求网关(请求新建角色)] (" << phone << "," << getID() << ")";
        Debug(Flyer::logger,oss.str().c_str());
        ret = task->sendMsg(reqMsg);
    }while(false);
    return ret;
}

bool LoginTask::ackCreateUser(boost::shared_ptr<ProtoMsgData::AckCreateUser> message)
{
    bool ret = false;
    ProtoMsgData::ErrorCode code = ProtoMsgData::EC_Default;
    ProtoMsgData::AckGateway ackMsg;
    do
    {
        if(message->code() != ProtoMsgData::EC_Default)
        {
            code = message->code();
            break;
        }
        boost::shared_ptr<RedisMem> redisMem = RedisMemManager::getInstance().getRedis();
        if(!redisMem)
        {
            break;
        }
        std::set<unsigned long> idSet;
        if(!redisMem->getSet("gateway","idset",idSet))
        {
            break;
        }
        if(!findGateway(message->phone(),ackMsg))
        {
            break;
        }
        unsigned long charID = redisMem->getInt("charid",message->phone().c_str());
        if(charID != message->charid())
        {
            Debug(Flyer::logger,"[redis取出错] (" << charID << "," << message->charid() << "," << message->phone() << ")");
            break;
        }
        m_charID = message->charid();
        ret = true;
    }while(false);
    if(code != ProtoMsgData::EC_Default)
    {
        ProtoMsgData::AckErrorCode codeMsg;
        codeMsg.set_code(code);
        sendMsg(codeMsg);
    }
    ackMsg.set_ret(ret);
    sendMsg(ackMsg);

    std::ostringstream oss;
    oss << "[请求网关(建角返回)" << (ret ? "成功" : "失败") << "] (" << message->phone() << "," << ackMsg.ip() << "," << ackMsg.port() << "," << m_charID << "," << code << ")"; 
    Debug(Flyer::logger,oss.str().c_str());
    ThreadPool::getInstance().addRecycleFromMain(m_id);
    return ret;
}

bool LoginTask::findGateway(const std::string &phone,ProtoMsgData::AckGateway &ackMsg)
{
    bool ret = false;
    do
    {
        boost::shared_ptr<RedisMem> redisMem = RedisMemManager::getInstance().getRedis();
        if(!redisMem)
        {
            break;
        }
        std::set<unsigned long> idSet;
        if(!redisMem->getSet("gateway","idset",idSet))
        {
            break;
        }
        unsigned long lessID = 0,lessNum = 0,port = 0;
        std::string ip;
        for(auto iter = idSet.begin();iter != idSet.end();++iter)
        {
            redisMem = RedisMemManager::getInstance().getRedis(*iter);
            if(!redisMem)
            {
                break;
            }
            char temp[Flyer::msglen];
            bzero(temp,sizeof(temp));
            unsigned int len = redisMem->getBin("gateway",*iter,temp);
            ProtoMsgData::GatewayInfo gateInfo;
            gateInfo.ParseFromArray(temp,len);
            if(gateInfo.status() != ProtoMsgData::GS_Normal)
            {
                continue;
            }
            if(!port || gateInfo.person() <= lessNum)
            {
                lessID = *iter;
                lessNum = gateInfo.person();
                port = gateInfo.port();
                ip = gateInfo.ip();
            }
            Info(Flyer::logger,"[查找网关] (" << gateInfo.id() << "," << gateInfo.person() << "," << lessNum << "," << lessID <<")");
        }
        if(!lessID)
        {
            break;
        }
        redisMem = RedisMemManager::getInstance().getRedis(lessID);
        if(!redisMem)
        {
            break;
        }
        if(!redisMem->setInt("logingate",phone.c_str(),lessID))
        {
            break;
        }
        ackMsg.set_ip(ip);
        ackMsg.set_port(port);
        ret = true;
    }while(false);
    return ret;
}
