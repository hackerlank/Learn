#include "robotHandle.h"

RobotHandle::RobotHandle() : MessageHandle("机器人消息处理")
{
}

RobotHandle::~RobotHandle()
{
}

bool RobotHandle::init()
{
#define MESSAGE_INIT(msg,call) \
{\
    boost::shared_ptr<MsgCallBack<boost::shared_ptr<RobotClient>,ProtoMsgData::msg> > callBack(new MsgCallBack<boost::shared_ptr<RobotClient>,ProtoMsgData::msg>(&RobotHandle::call));\
    RobotClient::s_robotClientMsgDispatcher.messageReg<ProtoMsgData::msg>(callBack);\
}
    MESSAGE_INIT(AckRegister,ackRegister);
    MESSAGE_INIT(AckGateway,ackGateway);
#undef MESSAGE_INIT
    return true;
}

bool RobotHandle::ackRegister(boost::shared_ptr<RobotClient> robotClient,const boost::shared_ptr<ProtoMsgData::AckRegister> message)
{
    bool ret = false;
    if(message->ret())
    {
        ProtoMsgData::ReqGateway reqMsg;
        reqMsg.set_phone(robotClient->getPhone());
        reqMsg.set_passwd(robotClient->getPhone());
        ret = robotClient->sendMsg(reqMsg);
    }
    return ret;
}

bool RobotHandle::ackGateway(boost::shared_ptr<RobotClient> robotClient,const boost::shared_ptr<ProtoMsgData::AckGateway> message)
{
    bool ret = false;
    if(message->ret())
    {
        ret = robotClient->reqLoginGateway(message->ip(),message->port());
    }
    return ret;
}
