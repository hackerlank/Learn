#include "clientHandle.h"
#include "client.h"

ClientHandle::ClientHandle() : MessageHandle("服客户端消息处理")
{
}

ClientHandle::~ClientHandle()
{
}

bool ClientHandle::init()
{
#define MESSAGE_INIT(msg,call) \
    {\
        boost::shared_ptr<MsgCallBack<boost::shared_ptr<Client>,ProtoMsgData::msg> > callBack(new MsgCallBack<boost::shared_ptr<Client>,ProtoMsgData::msg>(&ClientHandle::call));\
        Client::s_clientMsgDispatcher.messageReg<ProtoMsgData::msg>(callBack);\
    }
#undef MESSAGE_INIT
    return true;
}

