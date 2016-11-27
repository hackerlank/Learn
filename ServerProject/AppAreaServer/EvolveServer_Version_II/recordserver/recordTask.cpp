#include "recordTask.h"
#include "flyerValue.h"
#include "mysqlPool.h"
#include "recordServer.h"
#include "taskManager.h"
#include "recordDataManager.h"

RecordMessageDispatcher RecordTask::s_recordMsgDispatcher("档案服务器消息处理器");

RecordTask::RecordTask(const int fd) : Task(fd)
{
}

RecordTask::~RecordTask()
{
}

MsgRet RecordTask::dispatcher(boost::shared_ptr<google::protobuf::Message> message)
{
    MsgRet ret = MR_No_Register;
    ret = Task::dispatcher(message);
    if(ret == MR_No_Register)
    {
        boost::shared_ptr<Task> task = TaskManager::getInstance().getTask(m_id);
        boost::shared_ptr<RecordTask> recordTask = boost::dynamic_pointer_cast<RecordTask>(task);
        if(recordTask)
        {
            ret = s_recordMsgDispatcher.dispatch(recordTask,message);
        }
    }
    return ret;
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
        setVerify(true);
        ret = true;
    }while(false);
    return ret;
}

bool RecordTask::createUser(boost::shared_ptr<ProtoMsgData::ReqCreateUser> message)
{
    bool ret = false;
    unsigned long charID = 0;
    do
    {
        if(!RecordDataManager::getInstance().createUser(message->phone(),charID))
        {
            break;
        }
        ret = true;
    }while(false);
    ProtoMsgData::AckCreateUser ackMsg;
    ackMsg.set_code(ret ? ProtoMsgData::EC_Default : ProtoMsgData::EC_Create_Role);
    ackMsg.set_phone(message->phone());
    ackMsg.set_charid(charID);
    ackMsg.set_id(message->id());
    sendMsg(ackMsg);
    return ret;
}


