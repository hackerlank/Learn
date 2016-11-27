#ifndef CONNECT_HANDLE_H
#define CONNECT_HANDLE_H
#include "messageHandle.h"
#include "system.pb.h"
#include "connect.h"

class ConnectHandle : public MessageHandle
{
    public:
        ConnectHandle();
        ~ConnectHandle();
        virtual bool init();
    public:
        static bool ackVerifyServer(boost::shared_ptr<Connect> connect,const boost::shared_ptr<ProtoMsgData::AckVerifyServer> message);
        static bool reqHeartBeat(boost::shared_ptr<Connect> connect,const boost::shared_ptr<ProtoMsgData::ReqHeartBeat> message);
        static bool ackHeartBeat(boost::shared_ptr<Connect> connect,const boost::shared_ptr<ProtoMsgData::AckHeartBeat> message);
};

#endif
