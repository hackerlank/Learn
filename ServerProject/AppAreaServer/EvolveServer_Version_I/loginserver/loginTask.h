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
    public:
        static LoginMessageDispatcher s_loginMsgDispatcher;
};
#endif
