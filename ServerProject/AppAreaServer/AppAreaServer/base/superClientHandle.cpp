#include "superClientHandle.h"
#include "server.h"

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
    boost::shared_ptr<MsgCallBack<boost::shared_ptr<SuperClient>,ProtoMsgData::msg> > callBack(new MsgCallBack<boost::shared_ptr<SuperClient>,ProtoMsgData::msg>(&SuperClientHandle::call));\
    SuperClient::s_dispatcher.messageReg<ProtoMsgData::msg>(callBack);\
}
    MESSAGE_INIT(AckUpdateServerInfo,ackUpdateServerInfo);
    MESSAGE_INIT(AckNotifyMe,ackServerInfo);
#undef MESSAGE_INIT
    return true;
}

bool SuperClientHandle::ackUpdateServerInfo(boost::shared_ptr<SuperClient> superClient,const boost::shared_ptr<ProtoMsgData::AckUpdateServerInfo> message)
{
    const ProtoMsgData::ServerInfo &serverInfo = message->serverinfo();
    Server *server = superClient->getServer();
    if(!server)
    {
        return false;
    }
    server->updateOtherServer(serverInfo);
    if(server->getType() < serverInfo.servertype())
    {
        ProtoMsgData::AckRespServerInfo ackMsg;
        ackMsg.set_id(serverInfo.id());
        superClient->sendMsg(ackMsg);
    }
    return true;
}

bool SuperClientHandle::ackServerInfo(boost::shared_ptr<SuperClient> superClient,const boost::shared_ptr<ProtoMsgData::AckNotifyMe> message)
{
    if(message->serverinfo_size() < 1)
    {
        return false;
    }
    Server *server = superClient->getServer();
    if(!server)
    {
        return false;
    }
    for(int cnt = 0;cnt < message->serverinfo_size();++cnt)
    {
        const ProtoMsgData::ServerInfo &serverInfo = message->serverinfo(cnt);
        if(cnt == 0)
        {
            server->setServerInfo(serverInfo);
        }
        else
        {
            server->updateOtherServer(serverInfo);
        }
    }
    return true;
}
