#include "superClientHandle.h"

SuperClientHandle::SuperClientHandle() : MessageHandle("管理服务器客户端消息处理")
{
}

SuperClientHandle::~SuperClientHandle()
{
}

bool SuperClientHandle::init()
{
#define MESSAGE_INIT(msg,call) \
{\
    boost::shared_ptr<MsgCallBack<SuperClient&,ProtoMsgData::msg> > callBack(new MsgCallBack<SuperClient&,ProtoMsgData::msg>(&SuperClientHandle::call));\
    SuperClient::s_dispatcher.messageReg<ProtoMsgData::msg>(callBack);\
}
    MESSAGE_INIT(AckUpdateServerInfo,ackUpdateServerInfo);
    MESSAGE_INIT(AckNotifyMe,ackServerInfo);
#undef MESSAGE_INIT
    return true;
}

bool SuperClientHandle::ackUpdateServerInfo(SuperClient &superClient,const boost::shared_ptr<ProtoMsgData::AckUpdateServerInfo> message)
{
    const ProtoMsgData::ServerInfo &serverInfo = message->serverinfo();
    superClient.s_server->updateOtherServer(serverInfo);
    if(superClient.s_server->getType() < serverInfo.servertype())
    {
        ProtoMsgData::AckRespServerInfo ackMsg;
        ackMsg.set_id(serverInfo.id());
        superClient.sendMsg(ackMsg);
    }
    return true;
}

bool SuperClientHandle::ackServerInfo(SuperClient &superClient,const boost::shared_ptr<ProtoMsgData::AckNotifyMe> message)
{
    if(message->serverinfo_size() < 1)
    {
        return false;
    }
    for(int cnt = 0;cnt < message->serverinfo_size();++cnt)
    {
        const ProtoMsgData::ServerInfo &serverInfo = message->serverinfo(cnt);
        if(cnt == 0)
        {
            superClient.s_server->setServerInfo(serverInfo);
        }
        else
        {
            superClient.s_server->updateOtherServer(serverInfo);
        }
    }
    return true;
}

