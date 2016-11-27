#include "connectHandle.h"

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
    MESSAGE_INIT(AckVerifyServer,ackVerifyServer);
    MESSAGE_INIT(ReqHeartBeat,reqHeartBeat);
    MESSAGE_INIT(AckHeartBeat,ackHeartBeat);
#undef MESSAGE_INIT
    return true;
}

bool ConnectHandle::ackVerifyServer(boost::shared_ptr<Connect> connect,const boost::shared_ptr<ProtoMsgData::AckVerifyServer> message)
{
    TaskStatus status = message->ret() ? Task_Status_Main : Task_Status_Recycle; 
    connect->setStatus(status);
    return true;
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
