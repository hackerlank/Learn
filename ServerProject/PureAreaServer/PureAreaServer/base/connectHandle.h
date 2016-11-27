#ifndef CONNECT_HANDLE_H
#define CONNECT_HANDLE_H 
#include "messageHandle.h"
#include "connect.h"
#include "system.pb.h"

class ConnectHandle : public MessageHandle
{
    public:
        ConnectHandle();
        ~ConnectHandle();
        virtual bool init();
    public:
        static bool reqHeartBeat(Connect *connect,const boost::shared_ptr<ProtoMsgData::ReqHeartBeat> message);

        static bool ackHeartBeat(Connect *connect,const boost::shared_ptr<ProtoMsgData::AckHeartBeat> message);
};

#endif
