#ifndef RECORD_TASK_H
#define RECORD_TASK_H
#include "connect.h"
#include "messageDispatcher.h"
#include "system.pb.h"

class RecordTask;
typedef MessageDispatcher<boost::shared_ptr<RecordTask> > RecordMessageDispatcher;
class RecordTask : public Connect
{
    public:
        RecordTask(const int fd);
        ~RecordTask();
    public:
        virtual MsgRet dispatcher(boost::shared_ptr<google::protobuf::Message> message);
        bool verify(const ProtoMsgData::ServerInfo &serverInfo);
    public:
        static RecordMessageDispatcher s_recordMsgDispatcher;
};
#endif
