#include "sceneTask.h"
#include "flyerValue.h"
#include "mysqlPool.h"
#include "sceneServer.h"
#include "taskManager.h"

SceneMessageDispatcher SceneTask::s_sceneMsgDispatcher("场景服务器消息处理器");

SceneTask::SceneTask(const int fd) : Connect(fd)
{
}

SceneTask::~SceneTask()
{
}

MsgRet SceneTask::dispatcher(boost::shared_ptr<google::protobuf::Message> message)
{
    boost::shared_ptr<SceneTask> task = boost::dynamic_pointer_cast<SceneTask>(TaskManager::getInstance().getTask(m_id));
    return s_sceneMsgDispatcher.dispatch(task,message);
}

bool SceneTask::verify(const ProtoMsgData::ServerInfo &serverInfo)
{
    bool ret = false;
    std::vector<std::map<std::string,Flyer::FlyerValue> > ipVec;
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
        nextStatus();
        ret = true;
    }while(false);
    return ret;
}


