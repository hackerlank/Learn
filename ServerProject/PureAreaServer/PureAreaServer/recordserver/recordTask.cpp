#include "recordTask.h"
#include "flyerValue.h"
#include "mysqlPool.h"
#include "recordServer.h"
#include "taskManager.h"

RecordMessageDispatcher RecordTask::s_recordMsgDispatcher("档案服务器消息处理器");

RecordTask::RecordTask(const int fd) : Connect(fd)
{
}

RecordTask::~RecordTask()
{
}

MsgRet RecordTask::dispatcher(boost::shared_ptr<google::protobuf::Message> message)
{
    boost::shared_ptr<RecordTask> task = boost::dynamic_pointer_cast<RecordTask>(TaskManager::getInstance().getTask(m_id));
    return s_recordMsgDispatcher.dispatch(task,message);
}

bool RecordTask::verify(const ProtoMsgData::ServerInfo &serverInfo)
{
    bool ret = false;
    do
    {
        ProtoMsgData::AckVerifyServer ackMsg;
        bool flag = RecordServer::getInstance().findServer(serverInfo.id());
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


