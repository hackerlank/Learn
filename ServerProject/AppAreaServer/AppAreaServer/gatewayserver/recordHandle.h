#ifndef LOGIN_HANDLE_H
#define LOGIN_HANDLE_H
#include "messageHandle.h"
#include "system.pb.h"
#include "recordClient.h"

class RecordHandle : public MessageHandle
{
    public:
        RecordHandle();
        ~RecordHandle();
        virtual bool init();
    public:
        static bool ackCreateUser(boost::shared_ptr<RecordClient> recordClient,boost::shared_ptr<ProtoMsgData::AckCreateUser> message);

};

#endif
