#ifndef SUPER_TASK_H
#define SUPER_TASK_H
#include "task.h"
#include "messageDispatcher.h"
#include "system.pb.h"

class SuperTask;
typedef MessageDispatcher<boost::shared_ptr<SuperTask> > SuperMessageDispatcher;
class SuperTask : public Task 
{
    public:
        SuperTask(const int fd);
        ~SuperTask();
    public:
        virtual MsgRet dispatcher(boost::shared_ptr<google::protobuf::Message> message);
        bool verify(const ProtoMsgData::ServerType &serverType);
        bool accepteResp(const unsigned int serverID);
    public:
        static SuperMessageDispatcher s_superMsgDispatcher;
    private:
        bool getDependMap(const ProtoMsgData::ServerType &serverType);
        bool notifyDepend();
        bool verifyIp(const ProtoMsgData::ServerType &serverType);
        bool notifyMe();
    private:
        std::map<unsigned int,bool> m_dependMap;
        bool m_notifyFlg;
};
#endif
