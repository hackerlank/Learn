#include "gatewayTask.h"
#include "flyerValue.h"
#include "mysqlPool.h"
#include "common.pb.h"
#include "taskManager.h"
#include "redisMemManager.h"
#include "clientManager.h"
#include "recycleThread.h"
#include "gatewayServer.h"
#include "sceneClient.h"
#include "serialize.pb.h"

GatewayMessageDispatcher GatewayTask::s_gatewayMsgDispatcher("网关服务器消息处理器");
GatewayTask::GatewayTask(const int fd) : Task(fd),m_charID(0),m_isLogin(false),m_sceneID(0)
{
}

GatewayTask::~GatewayTask()
{
}

MsgRet GatewayTask::dispatcher(boost::shared_ptr<google::protobuf::Message> message)
{
    MsgRet ret = MR_No_Register;
    ret = Task::dispatcher(message);
    if(ret == MR_No_Register)
    {
        boost::shared_ptr<Task> task = TaskManager::getInstance().getTask(m_id);
        boost::shared_ptr<GatewayTask> gatewayTask = boost::dynamic_pointer_cast<GatewayTask>(task);
        if(gatewayTask)
        {
            ret = s_gatewayMsgDispatcher.dispatch(gatewayTask,message);
        }
        if(ret == MR_No_Register)
        {
            bool flg = false;
            boost::shared_ptr<Client> client = ClientManager::getInstance().getServerClient(gatewayTask->getSceneID());
            boost::shared_ptr<SceneClient> sceneClient = boost::dynamic_pointer_cast<SceneClient>(client);
            if(sceneClient)
            {
                google::protobuf::Message *msg = message.get();
                if(msg)
                {
                    flg = sceneClient->sendMsg(*msg);
                }
            }
            ret = flg ? MR_True : MR_False; 
        }
    }
    return ret;
}

bool GatewayTask::loginGateway(boost::shared_ptr<ProtoMsgData::ReqLoginGateway> message)
{
    bool ret = false;
    ProtoMsgData::ErrorCode code = ProtoMsgData::EC_Default;
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
        unsigned int serverID = GatewayServer::getInstance().getServerID();
        redisMem = RedisMemManager::getInstance().getRedis(serverID);
        if(!redisMem)
        {
            break;
        }
        unsigned int gatewayID = redisMem->getInt("logingate",message->phone().c_str());
        if(serverID != gatewayID)
        {
            code = ProtoMsgData::EC_Gateway_Wrong;
            break;
        }
        redisMem = RedisMemManager::getInstance().getRedis();
        if(!redisMem)
        {
            break;
        }
        m_phone = message->phone();
        unsigned long charID = redisMem->getInt("charid",message->phone().c_str());
        if(!charID)
        {
            ProtoMsgData::ReqCreateUser reqMsg;
            reqMsg.set_phone(message->phone());
            reqMsg.set_id(getID());
            boost::shared_ptr<Client> client = ClientManager::getInstance().getClientByType(ProtoMsgData::ST_Record);
            if(!client)
            {
                break;
            }
            std::ostringstream oss;
            oss << "[登录网关(请求新建角色)] (" << message->phone() << "," << getID() << ")";
            Debug(Flyer::logger,oss.str().c_str());
            client->sendMsg(reqMsg);

        }
        else
        {
            m_charID = charID;
            if(!TaskManager::getInstance().addGatewayTask(m_charID,m_id))
            {
                break;
            }
        }
        redisMem = RedisMemManager::getInstance().getRedis(serverID);
        if(!redisMem)
        {
            break;
        }
        char temp[Flyer::msglen];
        bzero(temp,sizeof(temp));
        unsigned int size = redisMem->getBin("gateway",serverID,temp);
        ProtoMsgData::GatewayInfo gateInfo;
        try
        {
            gateInfo.ParseFromArray(temp,size);
        }
        catch(...)
        {
            break;
        }
        gateInfo.set_person(gateInfo.person() + 1);
        bzero(temp,sizeof(temp));
        gateInfo.SerializeToArray(temp,sizeof(temp));
        if(!redisMem->setBin("gateway",serverID,temp,gateInfo.ByteSize()))
        {
            break;
        }
        m_isLogin = true;
        ret = true;
    }while(false);
    if(code != ProtoMsgData::EC_Default)
    {
        ProtoMsgData::AckErrorCode ackMsg;
        ackMsg.set_code(code);
        sendMsg(ackMsg);
    }
    if(m_charID)
    {
        ProtoMsgData::AckLoginGateway ackMsg;
        ackMsg.set_ret(ret);
        sendMsg(ackMsg);
        loginScene();
    }
    std::ostringstream oss;
    oss << "[登录网关" << (ret ? "成功" : "失败") << "] (" << message->phone() << "," << message->passwd() << "," << m_charID << "," << code << ")"; 
    Debug(Flyer::logger,oss.str().c_str());
    return ret;
}

bool GatewayTask::loginScene()
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
        if(!redisMem->getSet("scene","idset",idSet))
        {
            break;
        }
        unsigned short sceneID = 0;
        unsigned long num = 0;
        for(auto iter = idSet.begin();iter != idSet.end();++iter)
        {
            boost::shared_ptr<RedisMem> redisMem = RedisMemManager::getInstance().getRedis(*iter);
            if(!redisMem)
            {
                break;
            }
            char temp[Flyer::msglen];
            bzero(temp,sizeof(temp));
            unsigned size = redisMem->getBin("scene",*iter,temp);
            ProtoMsgData::SceneInfo sceneInfo;
            try
            {
                sceneInfo.ParseFromArray(temp,size);
            }
            catch(...)
            {
                break;
            }
            if(sceneInfo.status() == ProtoMsgData::GS_Normal)
            {
                if(!num || num > sceneInfo.person())
                {
                    num = sceneInfo.person();
                    sceneID = sceneInfo.id();
                }
            }
        }
        if(!sceneID)
        {
            break;
        }
        m_sceneID = sceneID;
        boost::shared_ptr<Client> client = ClientManager::getInstance().getServerClient(sceneID);
        if(!client)
        {
            break;
        }
        ProtoMsgData::ReqLoginScene reqMsg;
        reqMsg.set_charid(m_charID);
        client->sendMsg(reqMsg);
        ret = true;
    }while(false);

    std::ostringstream oss;
    oss << "[登录网关(请求登录场景)] (" << (ret ? "成功" : "失败") << "," << m_charID << "," << m_sceneID << ")";
    Debug(Flyer::logger,oss.str().c_str());
    if(ret)
    {
        setVerify(true);
    }
    return ret;
}

bool GatewayTask::ackCreateUser(boost::shared_ptr<ProtoMsgData::AckCreateUser> message)
{
    bool ret = false;
    do
    {
        if(m_charID)
        {
            break;
        }
        if(message->code() != ProtoMsgData::EC_Default)
        {
            ProtoMsgData::AckErrorCode ackMsg;
            ackMsg.set_code(message->code());
            sendMsg(ackMsg);
            break;
        }
        m_charID = message->charid();
        if(!TaskManager::getInstance().addGatewayTask(m_charID,m_id))
        {
            break;
        }
        boost::shared_ptr<RedisMem> redisMem = RedisMemManager::getInstance().getRedis(m_charID);
        if(!redisMem)
        {
            break;
        }
        char buffer[Flyer::msglen];
        bzero(buffer,sizeof(buffer));
        unsigned int size = redisMem->getBin("userbinary",m_charID,buffer);
        if(!size)
        {
            break;
        }
        ProtoMsgData::UserBinary binary;
        try
        {
            binary.ParseFromArray(buffer,size);
        }
        catch(...)
        {
            break;
        }
        ret = true;
    }while(false);

    ProtoMsgData::AckLoginGateway ackMsg;
    ackMsg.set_ret(ret);
    sendMsg(ackMsg);
    if(!ret)
    {
        ThreadPool::getInstance().addRecycleFromVerify(getID());
    }
    else
    {
        loginScene();
    }
    std::ostringstream oss;
    oss << "[登录网关(新建角色返回)] (" << (ret ? "成功" : "失败") << "," << message->phone() << "," << message->charid() << "," << message->code() << ")";
    Debug(Flyer::logger,oss.str().c_str());
    return ret;
}

void GatewayTask::disConnect()
{
    do
    {
        unsigned int serverID = GatewayServer::getInstance().getServerID();
        boost::shared_ptr<RedisMem> redisMem = RedisMemManager::getInstance().getRedis(serverID);
        if(!redisMem)
        {
            break;
        }
        char temp[Flyer::msglen] = {0};
        unsigned int size = redisMem->getBin("gateway",serverID,temp);
        ProtoMsgData::GatewayInfo gateInfo;
        try
        {
            gateInfo.ParseFromArray(temp,size);
        }
        catch(...)
        {
            break;
        }
        gateInfo.set_person(gateInfo.person() - 1);
        bzero(temp,sizeof(temp));
        gateInfo.SerializeToArray(temp,sizeof(temp));
        if(!redisMem->setBin("gateway",serverID,temp,gateInfo.ByteSize()))
        {
            break;
        }
        m_isLogin = false;
    }while(false);
}
