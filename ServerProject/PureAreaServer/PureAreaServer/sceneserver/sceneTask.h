#ifndef SCENE_TASK_H
#define SCENE_TASK_H
#include "connect.h"
#include "messageDispatcher.h"
#include "system.pb.h"

class SceneTask;
typedef MessageDispatcher<boost::shared_ptr<SceneTask> > SceneMessageDispatcher;
class SceneTask : public Connect
{
    public:
        SceneTask(const int fd);
        ~SceneTask();
    public:
        virtual MsgRet dispatcher(boost::shared_ptr<google::protobuf::Message> message);
        bool verify(const ProtoMsgData::ServerInfo &serverInfo);
    public:
        static SceneMessageDispatcher s_sceneMsgDispatcher;
};
#endif
