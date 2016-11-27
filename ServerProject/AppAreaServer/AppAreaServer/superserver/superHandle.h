#ifndef SUPER_HANDLE_H
#define SUPER_HANDLE_H
#include "superTask.h"
#include "messageHandle.h"
#include "system.pb.h"

class SuperHandle : public MessageHandle
{
    public:
        SuperHandle();
        ~SuperHandle();
        virtual bool init();
    public:
        static bool reqServerInfo(boost::shared_ptr<SuperTask> superTask,const boost::shared_ptr<ProtoMsgData::ReqServerInfo> message);
        static bool ackRespServerInfo(boost::shared_ptr<SuperTask> superTask,const boost::shared_ptr<ProtoMsgData::AckRespServerInfo> message);

};

#endif
