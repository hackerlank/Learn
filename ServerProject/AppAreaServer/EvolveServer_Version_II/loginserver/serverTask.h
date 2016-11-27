#ifndef SERVER_TASK_H
#define SERVER_TASK_H
#include "task.h"
#include "messageDispatcher.h"
#include "system.pb.h"

class ServerTask;
typedef MessageDispatcher<boost::shared_ptr<ServerTask> > ServerMessageDispatcher;
class ServerTask : public Task 
{
    public:
        ServerTask(const int fd);
        ~ServerTask();
    public:
        virtual MsgRet dispatcher(boost::shared_ptr<google::protobuf::Message> message);
        bool verify(const ProtoMsgData::ServerInfo &serverInfo);
        bool ackCreateUser(boost::shared_ptr<ProtoMsgData::AckCreateUser> message);
    public:
        static ServerMessageDispatcher s_serverMsgDispatcher;
};
#endif
