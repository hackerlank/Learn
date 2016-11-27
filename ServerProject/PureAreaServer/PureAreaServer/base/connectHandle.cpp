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
    boost::shared_ptr<MsgCallBack<Connect*,ProtoMsgData::msg> > callBack(new MsgCallBack<Connect*,ProtoMsgData::msg>(&ConnectHandle::call));\
    Connect::s_connectMsgDispatcher.messageReg<ProtoMsgData::msg>(callBack);\
}
    MESSAGE_INIT(ReqHeartBeat,reqHeartBeat);
    MESSAGE_INIT(AckHeartBeat,ackHeartBeat);
#undef MESSAGE_INIT
    return true;
}

bool ConnectHandle::reqHeartBeat(Connect *connect,const boost::shared_ptr<ProtoMsgData::ReqHeartBeat> message)
{
    if(!connect)
    {
        return false;
    }
    ProtoMsgData::AckHeartBeat ackMsg;
    connect->sendMsg(ackMsg);
    return true;
}
 
bool ConnectHandle::ackHeartBeat(Connect *connect,const boost::shared_ptr<ProtoMsgData::AckHeartBeat> message)
{
    if(!connect)
    {
        return false;
    }
    connect->resetHeartTime();
    return true;
}


