#include "serverHandle.h"
#include "server.h"
#include "recordServer.h"

ServerHandle::ServerHandle() : MessageHandle("档案服务器消息处理")
{
}

ServerHandle::~ServerHandle()
{
}

bool ServerHandle::init()
{
#define MESSAGE_INIT(msg,call) \
{\
    boost::shared_ptr<MsgCallBack<RecordServer&,ProtoMsgData::msg> > callBack(new MsgCallBack<RecordServer&,ProtoMsgData::msg>(&ServerHandle::call));\
    RecordServer::s_serverMsgDispatcher.messageReg<ProtoMsgData::msg>(callBack);\
}
    MESSAGE_INIT(ReqCreateUser,reqCreateUser);
#undef MESSAGE_INIT
    return true;
}

bool ServerHandle::reqCreateUser(RecordServer &recordServer,const boost::shared_ptr<ProtoMsgData::ReqCreateUser> message)
{
    return recordServer.reqCreateUser(message);
}
