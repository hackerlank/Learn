#include "gatewayHandle.h"
#include "taskManager.h"

GatewayHandle::GatewayHandle() : MessageHandle("登陆服务器消息处理")
{
}

GatewayHandle::~GatewayHandle()
{
}

bool GatewayHandle::init()
{
#define MESSAGE_INIT(msg,call) \
{\
    boost::shared_ptr<MsgCallBack<boost::shared_ptr<GatewayTask>,ProtoMsgData::msg> > callBack(new MsgCallBack<boost::shared_ptr<GatewayTask>,ProtoMsgData::msg>(&GatewayHandle::call));\
    GatewayTask::s_gatewayMsgDispatcher.messageReg<ProtoMsgData::msg>(callBack);\
}
    MESSAGE_INIT(ReqLoginGateway,reqLoginGateway);
#undef MESSAGE_INIT
    return true;
}

bool GatewayHandle::reqLoginGateway(boost::shared_ptr<GatewayTask> gatewayTask,const boost::shared_ptr<ProtoMsgData::ReqLoginGateway> message)
{
    return gatewayTask->loginGateway(message);
}
