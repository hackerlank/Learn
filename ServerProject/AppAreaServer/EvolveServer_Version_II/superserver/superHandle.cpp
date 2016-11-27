#include "superHandle.h"
#include "taskManager.h"
#include "loginClient.h"
#include "clientManager.h"

SuperHandle::SuperHandle() : MessageHandle("管理服务器消息处理")
{
}

SuperHandle::~SuperHandle()
{
}

bool SuperHandle::init()
{
#define MESSAGE_INIT(msg,call) \
{\
    boost::shared_ptr<MsgCallBack<boost::shared_ptr<SuperTask>,ProtoMsgData::msg> > callBack(new MsgCallBack<boost::shared_ptr<SuperTask>,ProtoMsgData::msg>(&SuperHandle::call));\
    SuperTask::s_superMsgDispatcher.messageReg<ProtoMsgData::msg>(callBack);\
}
    MESSAGE_INIT(ReqServerInfo,reqServerInfo);
    MESSAGE_INIT(AckRespServerInfo,ackRespServerInfo);
    MESSAGE_INIT(AckCreateUser,ackCreateUser);
#undef MESSAGE_INIT
    return true;
}

bool SuperHandle::reqServerInfo(boost::shared_ptr<SuperTask> superTask,const boost::shared_ptr<ProtoMsgData::ReqServerInfo> message)
{
    return superTask->verify(message->servertype());
}

bool SuperHandle::ackRespServerInfo(boost::shared_ptr<SuperTask> superTask,const boost::shared_ptr<ProtoMsgData::AckRespServerInfo> message)
{
    bool ret = false;
    do
    {
        boost::shared_ptr<Task> task = TaskManager::getInstance().getServerTask(message->id());
        boost::shared_ptr<SuperTask> super = boost::dynamic_pointer_cast<SuperTask>(task);
        if(!super)
        {
            break;
        }
        ret = super->accepteResp(superTask->getServerID());
    }while(false);
    return ret;
}

bool SuperHandle::ackCreateUser(boost::shared_ptr<SuperTask> superTask,const boost::shared_ptr<ProtoMsgData::AckCreateUser> message)
{
    bool ret = false;
    do
    {
        boost::shared_ptr<Client> client = ClientManager::getInstance().getClientByType(ProtoMsgData::ST_Login);
        boost::shared_ptr<LoginClient> loginClient = boost::dynamic_pointer_cast<LoginClient>(client);
        if(loginClient)
        {
            ret = loginClient->ackCreateUser(message);
        }
    }while(false);
    return ret;
}
