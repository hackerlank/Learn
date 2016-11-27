#include "taskHandle.h"
#include "task.h"

TaskHandle::TaskHandle() : MessageHandle("task消息处理")
{
}

TaskHandle::~TaskHandle()
{
}

bool TaskHandle::init()
{
#define MESSAGE_INIT(msg,call) \
    {\
        boost::shared_ptr<MsgCallBack<boost::shared_ptr<Task>,ProtoMsgData::msg> > callBack(new MsgCallBack<boost::shared_ptr<Task>,ProtoMsgData::msg>(&TaskHandle::call));\
        Task::s_taskMsgDispatcher.messageReg<ProtoMsgData::msg>(callBack);\
    }
    MESSAGE_INIT(AckHeartBeat,ackHeartBeat);
#undef MESSAGE_INIT
    return true;
}

bool TaskHandle::ackHeartBeat(boost::shared_ptr<Task> task,const boost::shared_ptr<ProtoMsgData::AckHeartBeat> message)
{
    task->resetHeartTime();
    return true;
}

