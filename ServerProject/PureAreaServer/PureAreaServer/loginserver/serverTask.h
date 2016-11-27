#ifndef SERVER_TASK_H
#define SERVER_TASK_H
#include "connect.h"
#include "messageDispatcher.h"
#include "system.pb.h"

class ServerTask;
typedef MessageDispatcher<boost::shared_ptr<ServerTask> > ServerMessageDispatcher;
class ServerTask : public Connect
{
    public:
        ServerTask(const int fd);
        ~ServerTask();
    public:
        virtual MsgRet dispatcher(boost::shared_ptr<google::protobuf::Message> message);
        bool verify(const ProtoMsgData::ServerInfo &serverInfo);
    public:
        static ServerMessageDispatcher s_serverMsgDispatcher;
};
#endif
