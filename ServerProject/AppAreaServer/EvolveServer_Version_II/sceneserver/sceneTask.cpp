#include "sceneTask.h"
#include "flyerValue.h"
#include "mysqlPool.h"
#include "sceneServer.h"
#include "taskManager.h"
#include "redisMemManager.h"
#include "serialize.pb.h"
#include "sceneUserManager.h"
#include "system.pb.h"

SceneMessageDispatcher SceneTask::s_sceneMsgDispatcher("场景服务器消息处理器");

SceneTask::SceneTask(const int fd) : Task(fd)
{
}

SceneTask::~SceneTask()
{
}

MsgRet SceneTask::dispatcher(boost::shared_ptr<google::protobuf::Message> message)
{
    MsgRet ret = MR_No_Register;
    ret = Task::dispatcher(message);
    if(ret == MR_No_Register)
    {
        boost::shared_ptr<Task> task = TaskManager::getInstance().getTask(m_id);
        boost::shared_ptr<SceneTask> sceneTask = boost::dynamic_pointer_cast<SceneTask>(task);
        if(sceneTask)
        {
            ret = s_sceneMsgDispatcher.dispatch(sceneTask,message);
        }
    }
    return ret;
}

bool SceneTask::verify(const ProtoMsgData::ServerInfo &serverInfo)
{
    bool ret = false;
    do
    {
        ProtoMsgData::AckVerifyServer ackMsg;
        bool flag = SceneServer::getInstance().findServer(serverInfo.id());
        ackMsg.set_ret(flag);
        if(!sendMsg(ackMsg))
        {
            break;
        }
        m_serverID = serverInfo.id();
        m_serverType = serverInfo.servertype();
        setVerify(true);
        ret = true;
    }while(false);
    return ret;
}

bool SceneTask::login(const unsigned long charID)
{
    bool ret = false;
    ProtoMsgData::AckLoginScene ackMsg;
    do
    {
        boost::shared_ptr<RedisMem> redisMem = RedisMemManager::getInstance().getRedis(charID);
        if(!redisMem)
        {
            break;
        }
        char buffer[Flyer::msglen];
        bzero(buffer,sizeof(buffer));
        unsigned int size = redisMem->getBin("userbinary",charID,buffer);
        ProtoMsgData::UserBinary binary;
        try
        {
            binary.ParseFromArray(buffer,size);
        }
        catch(...)
        {
            break;
        }
        boost::shared_ptr<SceneUser> user(new SceneUser(charID,m_serverID));
        if(!user->parseFromBinary(binary))
        {
            break;
        }
        if(!SceneUserManager::getInstance().add(user))
        {
            break;
        }
        if(!user->onLine())
        {
            break;
        }
        ret = true;
    }while(false);
    ackMsg.set_ret(ret);
    ackMsg.set_charid(charID);
    sendMsg(ackMsg);

    std::ostringstream oss;
    oss << "[登录网关(登录场景)] (" << (ret ? "成功" : "失败") << "," << charID << ")";
    Debug(Flyer::logger,oss.str().c_str());
    return ret;
}

