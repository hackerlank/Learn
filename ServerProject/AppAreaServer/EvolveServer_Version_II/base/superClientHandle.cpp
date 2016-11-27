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
    MESSAGE_INIT(ReqCreateUser,reqCreateUser);
#undef MESSAGE_INIT
    return true;
}

bool SuperClientHandle::ackUpdateServerInfo(boost::shared_ptr<SuperClient> superClient,const boost::shared_ptr<ProtoMsgData::AckUpdateServerInfo> message)
{
    bool ret = false;
    do
    {
        const ProtoMsgData::ServerInfo &serverInfo = message->serverinfo();
        Server *server = superClient->getServer();
        if(!server)
        {
            break;
        }
        server->updateOtherServer(serverInfo);
        if(server->getType() < serverInfo.servertype())
        {
            ProtoMsgData::AckRespServerInfo ackMsg;
            ackMsg.set_id(serverInfo.id());
            superClient->sendMsg(ackMsg);
        }
        ret = true;
    }while(false);
    return ret;
}

bool SuperClientHandle::ackServerInfo(boost::shared_ptr<SuperClient> superClient,const boost::shared_ptr<ProtoMsgData::AckNotifyMe> message)
{
    bool ret = false;
    do
    {
        if(message->serverinfo_size() < 1)
        {
            break;
        }
        Server *server = superClient->getServer();
        if(!server)
        {
            break;
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
        ret = true;
    }while(false);
    return ret;
}

bool SuperClientHandle::reqCreateUser(boost::shared_ptr<SuperClient> superClient,const boost::shared_ptr<ProtoMsgData::ReqCreateUser> message)
{
    bool ret = false;
    do
    {
        Server *server = superClient->getServer();
        if(!server)
        {
            break;
        }
        MsgRet flg = server->dispatcher(message);
        ret = flg == MR_False ? false : true;
    }while(false);
    return ret;
}
