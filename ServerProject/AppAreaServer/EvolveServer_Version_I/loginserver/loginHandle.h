#ifndef LOGIN_HANDLE_H
#define LOGIN_HANDLE_H
#include "loginTask.h"
#include "messageHandle.h"
#include "login.pb.h"

class LoginHandle : public MessageHandle
{
    public:
        LoginHandle();
        ~LoginHandle();
        virtual bool init();
    public:
        static bool reqRegister(boost::shared_ptr<LoginTask> loginTask,const boost::shared_ptr<ProtoMsgData::ReqRegister> message);
        static bool reqGateway(boost::shared_ptr<LoginTask> loginTask,const boost::shared_ptr<ProtoMsgData::ReqGateway> message);

};

#endif
