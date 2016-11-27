#include "loginClient.h"
#include "clientManager.h"

LoginClientMessageDispatcher LoginClient::s_loginClientMsgDispatcher("登录服客户端消息处理器");
LoginClient::LoginClient(const std::string &name,const std::string &ip,const unsigned short port,const int fd) : Client(name,ip,port,fd)
{
}

LoginClient::~LoginClient()
{
}

MsgRet LoginClient::dispatcher(boost::shared_ptr<google::protobuf::Message> message)
{
    MsgRet ret = MR_False;
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
