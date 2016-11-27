#ifndef LOGIN_HANDLE_H
#define LOGIN_HANDLE_H
#include "messageHandle.h"
#include "system.pb.h"
#include "loginClient.h"

class LoginHandle : public MessageHandle
{
    public:
        LoginHandle();
        ~LoginHandle();
        virtual bool init();
    public:
        static bool reqCreateUser(boost::shared_ptr<LoginClient> client,boost::shared_ptr<ProtoMsgData::ReqCreateUser> message);
};

#endif
