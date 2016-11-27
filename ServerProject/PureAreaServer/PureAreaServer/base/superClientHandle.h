#ifndef SUPER_CLIENT_HANDLE_H
#define SUPER_CLIENT_HANDLE_H
#include "messageHandle.h"
#include "superClient.h"
#include "system.pb.h"

class SuperClientHandle : public MessageHandle
{
    public:
        SuperClientHandle();
        ~SuperClientHandle();
        virtual bool init();
    public:
        static bool ackUpdateServerInfo(SuperClient &superClient,const boost::shared_ptr<ProtoMsgData::AckUpdateServerInfo> message);
    
        static bool ackServerInfo(SuperClient &superClient,const boost::shared_ptr<ProtoMsgData::AckNotifyMe> message);

};

#endif
