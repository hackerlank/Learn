#ifndef LOGIN_CLIENT_H
#define LOGIN_CLIENT_H
#include "client.h"
#include "messageDispatcher.h"

class LoginClient;
typedef MessageDispatcher<boost::shared_ptr<LoginClient> > LoginClientMessageDispatcher;
class LoginClient : public Client
{
    public:
        LoginClient(const std::string &name,const std::string &ip,const unsigned short port,const int fd);
        virtual ~LoginClient();
        virtual MsgRet dispatcher(boost::shared_ptr<google::protobuf::Message> message);
    public:
        static LoginClientMessageDispatcher s_loginClientMsgDispatcher;
};

#endif
