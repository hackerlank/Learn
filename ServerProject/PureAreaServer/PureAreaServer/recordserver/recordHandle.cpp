#include "recordHandle.h"

RecordHandle::RecordHandle() : MessageHandle("档案服务器消息处理")
{
}

RecordHandle::~RecordHandle()
{
}

bool RecordHandle::init()
{
#define MESSAGE_INIT(msg,call) \
{\
    boost::shared_ptr<MsgCallBack<boost::shared_ptr<RecordTask>,ProtoMsgData::msg> > callBack(new MsgCallBack<boost::shared_ptr<RecordTask>,ProtoMsgData::msg>(&RecordHandle::call));\
    RecordTask::s_recordMsgDispatcher.messageReg<ProtoMsgData::msg>(callBack);\
}
    MESSAGE_INIT(ReqVerifyServer,reqVerifyServer);

#undef MESSAGE_INIT

    return true;
}

bool RecordHandle::reqVerifyServer(boost::shared_ptr<RecordTask> recordTask,const boost::shared_ptr<ProtoMsgData::ReqVerifyServer> message)
{
    return recordTask->verify(message->serverinfo());
}
