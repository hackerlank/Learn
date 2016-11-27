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
    MESSAGE_INIT(AckVerifyServer,ackVerifyServer);
#undef MESSAGE_INIT
    return true;
}

bool ClientHandle::ackVerifyServer(boost::shared_ptr<Client> client,const boost::shared_ptr<ProtoMsgData::AckVerifyServer> message)
{
    TaskStatus status = message->ret() ? Task_Status_Main : Task_Status_Recycle; 
    client->setStatus(status);
    return true;
}
