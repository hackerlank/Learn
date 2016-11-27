#ifndef SERVER_HANDLE_H
#define SERVER_HANDLE_H
#include "messageHandle.h"
#include "system.pb.h"
#include "login.pb.h"

class RecordServer;

class ServerHandle : public MessageHandle
{
    public:
        ServerHandle();
        ~ServerHandle();
        virtual bool init();
    public:
        static bool reqCreateUser(RecordServer &recordServer,const boost::shared_ptr<ProtoMsgData::ReqCreateUser> message);

};

#endif
