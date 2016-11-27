#ifndef SERVER_HANDLE_H
#define SERVER_HANDLE_H
#include "serverTask.h"
#include "messageHandle.h"
#include "system.pb.h"

class ServerHandle : public MessageHandle
{
    public:
        ServerHandle();
        ~ServerHandle();
        virtual bool init();
    public:
        static bool reqVerifyServer(boost::shared_ptr<ServerTask> serverTask,const boost::shared_ptr<ProtoMsgData::ReqVerifyServer> message);
};

#endif
