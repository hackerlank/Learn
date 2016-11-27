#ifndef LOGIN_TASK_H
#define LOGIN_TASK_H
#include "task.h"
#include "messageDispatcher.h"
#include "login.pb.h"

class LoginTask;
typedef MessageDispatcher<boost::shared_ptr<LoginTask> > LoginMessageDispatcher;
class LoginTask : public Task 
{
    public:
        LoginTask(const int fd);
        ~LoginTask();
    public:
        virtual MsgRet dispatcher(boost::shared_ptr<google::protobuf::Message> message);
        bool registerAccount(boost::shared_ptr<ProtoMsgData::ReqRegister> message);
        bool getGatewayInfo(boost::shared_ptr<ProtoMsgData::ReqGateway> message);
        bool ackCreateUser(boost::shared_ptr<ProtoMsgData::AckCreateUser> message);
    private:
        bool createUser(const std::string phone);
        bool findGateway(const std::string &phone,ProtoMsgData::AckGateway &ackMsg);
        bool hasCreateUser(const std::string phone);
    public:
        static LoginMessageDispatcher s_loginMsgDispatcher;
    private:
        unsigned long m_charID;
};
#endif
