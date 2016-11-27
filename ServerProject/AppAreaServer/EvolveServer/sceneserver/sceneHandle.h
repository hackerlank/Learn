#ifndef SCENE_HANDLE_H
#define SCENE_HANDLE_H
#include "sceneTask.h"
#include "messageHandle.h"
#include "system.pb.h"

class SceneHandle : public MessageHandle
{
    public:
        SceneHandle();
        ~SceneHandle();
        virtual bool init();
    public:
        static bool reqVerifyServer(boost::shared_ptr<SceneTask> sceneTask,const boost::shared_ptr<ProtoMsgData::ReqVerifyServer> message);
        static bool reqLoginScene(boost::shared_ptr<SceneTask> sceneTask,const boost::shared_ptr<ProtoMsgData::ReqLoginScene> message);
};

#endif
