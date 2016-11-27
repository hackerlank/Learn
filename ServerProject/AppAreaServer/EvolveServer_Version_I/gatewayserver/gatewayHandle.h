#ifndef GATE_WAY_HANDLE_H
#define GATE_WAY_HANDLE_H 
#include "gatewayTask.h"
#include "messageHandle.h"
#include "login.pb.h"

class GatewayHandle : public MessageHandle
{
    public:
        GatewayHandle();
        ~GatewayHandle();
        virtual bool init();
    public:
        static bool reqLoginGateway(boost::shared_ptr<GatewayTask> gatewayTask,const boost::shared_ptr<ProtoMsgData::ReqLoginGateway> message);
};

#endif
