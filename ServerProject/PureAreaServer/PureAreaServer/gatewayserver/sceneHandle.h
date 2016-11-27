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
};

#endif
