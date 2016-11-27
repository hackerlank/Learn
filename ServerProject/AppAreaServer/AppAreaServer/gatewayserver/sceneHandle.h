#ifndef SCENE_HANDLE_H
#define SCENE_HANDLE_H
#include "messageHandle.h"
#include "system.pb.h"
#include "sceneClient.h"

class SceneHandle : public MessageHandle
{
    public:
        SceneHandle();
        ~SceneHandle();
        virtual bool init();
    public:
        static bool ackLoginScene(boost::shared_ptr<SceneClient> sceneClient,const boost::shared_ptr<ProtoMsgData::AckLoginScene> message);
        static bool ackUserMsg(boost::shared_ptr<SceneClient> sceneClient,const boost::shared_ptr<ProtoMsgData::AckUserMsg> message);
};

#endif
