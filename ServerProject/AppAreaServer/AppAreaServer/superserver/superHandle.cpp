#include "superHandle.h"
#include "taskManager.h"

SuperHandle::SuperHandle() : MessageHandle("管理服务器消息处理")
{
}

SuperHandle::~SuperHandle()
{
}

bool SuperHandle::init()
{
#define MESSAGE_INIT(msg,call) \
{\
    boost::shared_ptr<MsgCallBack<boost::shared_ptr<SuperTask>,ProtoMsgData::msg> > callBack(new MsgCallBack<boost::shared_ptr<SuperTask>,ProtoMsgData::msg>(&SuperHandle::call));\
    SuperTask::s_superMsgDispatcher.messageReg<ProtoMsgData::msg>(callBack);\
}
    MESSAGE_INIT(ReqServerInfo,reqServerInfo);
    MESSAGE_INIT(AckRespServerInfo,ackRespServerInfo);
#undef MESSAGE_INIT
    return true;
}

bool SuperHandle::reqServerInfo(boost::shared_ptr<SuperTask> superTask,const boost::shared_ptr<ProtoMsgData::ReqServerInfo> message)
{
    return superTask->verify(message->servertype());
}

bool SuperHandle::ackRespServerInfo(boost::shared_ptr<SuperTask> superTask,const boost::shared_ptr<ProtoMsgData::AckRespServerInfo> message)
{
    bool ret = false;
    boost::shared_ptr<Connect> connect = TaskManager::getInstance().getServerTask(message->id());
    boost::shared_ptr<SuperTask> task = boost::dynamic_pointer_cast<SuperTask>(connect);
    ret = task->accepteResp(superTask->getServerID());
    return ret;
}
