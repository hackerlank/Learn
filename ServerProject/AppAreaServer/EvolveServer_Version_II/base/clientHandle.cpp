#include "clientHandle.h"
#include "client.h"
#include "clientThread.h"

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
    MESSAGE_INIT(ReqHeartBeat,reqHeartBeat);
#undef MESSAGE_INIT
    return true;
}

bool ClientHandle::ackVerifyServer(boost::shared_ptr<Client> client,const boost::shared_ptr<ProtoMsgData::AckVerifyServer> message)
{
    if(!message->ret())
    {
        ClientThread::getInstance().addRecycle(client->getID());
    }
    else
    {
        client->setStatus(Task_Status_Main);
    }
    return message->ret();
}

bool ClientHandle::reqHeartBeat(boost::shared_ptr<Client> client,const boost::shared_ptr<ProtoMsgData::ReqHeartBeat> message)
{
    ProtoMsgData::AckHeartBeat ackMsg;
    client->sendMsg(ackMsg);
    return true;
}


