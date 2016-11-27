#include "connectHandle.h"
#include "clientThread.h"

ConnectHandle::ConnectHandle() : MessageHandle("连接消息处理")
{
}

ConnectHandle::~ConnectHandle()
{
}

bool ConnectHandle::init()
{
#define MESSAGE_INIT(msg,call) \
    {\
        boost::shared_ptr<MsgCallBack<boost::shared_ptr<Connect>,ProtoMsgData::msg> > callBack(new MsgCallBack<boost::shared_ptr<Connect>,ProtoMsgData::msg>(&ConnectHandle::call));\
        Connect::s_connectMsgDispatcher.messageReg<ProtoMsgData::msg>(callBack);\
    }
#if 0
    MESSAGE_INIT(AckVerifyServer,ackVerifyServer);
    MESSAGE_INIT(ReqHeartBeat,reqHeartBeat);
    MESSAGE_INIT(AckHeartBeat,ackHeartBeat);
#endif
#undef MESSAGE_INIT
    return true;
}
#if 0
bool ConnectHandle::ackVerifyServer(boost::shared_ptr<Connect> connect,const boost::shared_ptr<ProtoMsgData::AckVerifyServer> message)
{
    if(!message->ret())
    {
        ClientThread::getInstance().addRecycle(connect->getID());
    }
    else
    {
        connect->setStatus(Task_Status_Main);
    }
    return message->ret();
}

bool ConnectHandle::reqHeartBeat(boost::shared_ptr<Connect> connect,const boost::shared_ptr<ProtoMsgData::ReqHeartBeat> message)
{
    ProtoMsgData::AckHeartBeat ackMsg;
    connect->sendMsg(ackMsg);
    return true;
}

bool ConnectHandle::ackHeartBeat(boost::shared_ptr<Connect> connect,const boost::shared_ptr<ProtoMsgData::AckHeartBeat> message)
{
    connect->resetHeartTime();
    return true;
}
#endif
