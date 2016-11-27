#include "serverHandle.h"

ServerHandle::ServerHandle() : MessageHandle("登陆服务器消息处理")
{
}

ServerHandle::~ServerHandle()
{
}

bool ServerHandle::init()
{
#define MESSAGE_INIT(msg,call) \
{\
    boost::shared_ptr<MsgCallBack<boost::shared_ptr<ServerTask>,ProtoMsgData::msg> > callBack(new MsgCallBack<boost::shared_ptr<ServerTask>,ProtoMsgData::msg>(&ServerHandle::call));\
    ServerTask::s_serverMsgDispatcher.messageReg<ProtoMsgData::msg>(callBack);\
}
    MESSAGE_INIT(ReqVerifyServer,reqVerifyServer);

#undef MESSAGE_INIT

    return true;
}

bool ServerHandle::reqVerifyServer(boost::shared_ptr<ServerTask> serverTask,const boost::shared_ptr<ProtoMsgData::ReqVerifyServer> message)
{
    return serverTask->verify(message->serverinfo());
}
