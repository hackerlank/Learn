#include "loginHandle.h"
#include "taskManager.h"

LoginHandle::LoginHandle() : MessageHandle("登陆服务器消息处理")
{
}

LoginHandle::~LoginHandle()
{
}

bool LoginHandle::init()
{
#define MESSAGE_INIT(msg,call) \
{\
    boost::shared_ptr<MsgCallBack<boost::shared_ptr<LoginTask>,ProtoMsgData::msg> > callBack(new MsgCallBack<boost::shared_ptr<LoginTask>,ProtoMsgData::msg>(&LoginHandle::call));\
    LoginTask::s_loginMsgDispatcher.messageReg<ProtoMsgData::msg>(callBack);\
}
    MESSAGE_INIT(ReqRegister,reqRegister);
    MESSAGE_INIT(ReqGateway,reqGateway);
#undef MESSAGE_INIT
    return true;
}

bool LoginHandle::reqRegister(boost::shared_ptr<LoginTask> loginTask,const boost::shared_ptr<ProtoMsgData::ReqRegister> message)
{
    return loginTask->registerAccount(message);
}

bool LoginHandle::reqGateway(boost::shared_ptr<LoginTask> loginTask,const boost::shared_ptr<ProtoMsgData::ReqGateway> message)
{
    return loginTask->getGatewayInfo(message);
}
