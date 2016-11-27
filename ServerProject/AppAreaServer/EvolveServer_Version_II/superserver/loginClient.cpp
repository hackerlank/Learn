#include "loginClient.h"
#include "clientManager.h"
#include "taskManager.h"

LoginClientMessageDispatcher LoginClient::s_loginClientMsgDispatcher("登录服客户端消息处理器");
LoginClient::LoginClient(const std::string &name,const std::string &ip,const unsigned short port,const int fd) : Client(name,ip,port,fd)
{
}

LoginClient::~LoginClient()
{
}

MsgRet LoginClient::dispatcher(boost::shared_ptr<google::protobuf::Message> message)
{
    MsgRet ret = MR_No_Register;
    do
    {
        ret = Client::dispatcher(message);
        if(ret == MR_No_Register)
        {
            boost::shared_ptr<LoginClient> loginClient = boost::dynamic_pointer_cast<LoginClient>(getPtr());
            ret = s_loginClientMsgDispatcher.dispatch(loginClient,message);
        }
    }while(false);
    return ret;
}

bool LoginClient::reqCreateUser(boost::shared_ptr<ProtoMsgData::ReqCreateUser> message)
{
    bool ret = false;
    do
    {
        boost::shared_ptr<Task> task = TaskManager::getInstance().getServerTaskByType(ProtoMsgData::ST_Record);
        if(!task)
        {
            break;
        }
        ProtoMsgData::ReqCreateUser *reqMsg = message.get();
        ret = reqMsg ? task->sendMsg(*reqMsg) : false;
    }while(false);
    return ret;
}

bool LoginClient::ackCreateUser(boost::shared_ptr<ProtoMsgData::AckCreateUser> message)
{
    bool ret = false;
    do
    {
        boost::shared_ptr<Client> client = ClientManager::getInstance().getClientByType(ProtoMsgData::ST_Login);
        if(!client)
        {
            break;
        }
        ProtoMsgData::AckCreateUser *ackMsg = message.get();
        ret = ackMsg ? client->sendMsg(*ackMsg) : false;
    }while(false);
    return ret;
}
