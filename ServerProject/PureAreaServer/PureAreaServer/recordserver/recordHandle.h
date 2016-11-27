#ifndef RECORD_HANDLE_H
#define RECORD_HANDLE_H
#include "recordTask.h"
#include "messageHandle.h"
#include "system.pb.h"

class RecordHandle : public MessageHandle
{
    public:
        RecordHandle();
        ~RecordHandle();
        virtual bool init();
    public:
        static bool reqVerifyServer(boost::shared_ptr<RecordTask> serverTask,const boost::shared_ptr<ProtoMsgData::ReqVerifyServer> message);
};

#endif
