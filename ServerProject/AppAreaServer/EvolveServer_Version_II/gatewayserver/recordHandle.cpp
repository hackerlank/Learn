#include "recordHandle.h"
#include "taskManager.h"
#include "gatewayTask.h"

RecordHandle::RecordHandle() : MessageHandle("档案服客户端消息处理")
{
}

RecordHandle::~RecordHandle()
{
}

bool RecordHandle::init()
{
#define MESSAGE_INIT(msg,call) \
    {\
        boost::shared_ptr<MsgCallBack<boost::shared_ptr<RecordClient>,ProtoMsgData::msg> > callBack(new MsgCallBack<boost::shared_ptr<RecordClient>,ProtoMsgData::msg>(&RecordHandle::call));\
        RecordClient::s_recordClientMsgDispatcher.messageReg<ProtoMsgData::msg>(callBack);\
    }
    MESSAGE_INIT(AckCreateUser,ackCreateUser);
#undef MESSAGE_INIT
    return true;
}

bool RecordHandle::ackCreateUser(boost::shared_ptr<RecordClient> recordClient,boost::shared_ptr<ProtoMsgData::AckCreateUser> message)
{
    boost::shared_ptr<Connect> task = TaskManager::getInstance().getTask(message->id());
    boost::shared_ptr<GatewayTask> gatewayTask = boost::dynamic_pointer_cast<GatewayTask>(task);
    return gatewayTask ? gatewayTask->ackCreateUser(message) : false;
}
