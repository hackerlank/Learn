#ifndef RECORD_TASK_H
#define RECORD_TASK_H
#include "task.h"
#include "messageDispatcher.h"
#include "system.pb.h"

class RecordTask;
typedef MessageDispatcher<boost::shared_ptr<RecordTask> > RecordMessageDispatcher;
class RecordTask : public Task 
{
    public:
        RecordTask(const int fd);
        ~RecordTask();
    public:
        virtual MsgRet dispatcher(boost::shared_ptr<google::protobuf::Message> message);
        bool verify(const ProtoMsgData::ServerInfo &serverInfo);
        bool createUser(boost::shared_ptr<ProtoMsgData::ReqCreateUser> message);
    public:
        static RecordMessageDispatcher s_recordMsgDispatcher;
};
#endif
