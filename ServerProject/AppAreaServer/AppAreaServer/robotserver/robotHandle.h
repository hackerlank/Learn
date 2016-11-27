#ifndef ROBOT_HANDLE_H
#define ROBOT_HANDLE_H
#include "messageHandle.h"
#include "system.pb.h"
#include "robotClient.h"
#include "login.pb.h"

class RobotHandle : public MessageHandle
{
    public:
        RobotHandle();
        ~RobotHandle();
        virtual bool init();
    public:
        static bool ackRegister(boost::shared_ptr<RobotClient> robotClient,const boost::shared_ptr<ProtoMsgData::AckRegister> message);
        static bool ackGateway(boost::shared_ptr<RobotClient> robotClient,const boost::shared_ptr<ProtoMsgData::AckGateway> message);
};

#endif
