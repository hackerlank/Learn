#include "sceneHandle.h"

SceneHandle::SceneHandle() : MessageHandle("场景服客户端消息处理")
{
}

SceneHandle::~SceneHandle()
{
}

bool SceneHandle::init()
{
#define MESSAGE_INIT(msg,call) \
    {\
        boost::shared_ptr<MsgCallBack<boost::shared_ptr<SceneClient>,ProtoMsgData::msg> > callBack(new MsgCallBack<boost::shared_ptr<SceneClient>,ProtoMsgData::msg>(&SceneHandle::call));\
        SceneTask::s_sceneMsgDispatcher.messageReg<ProtoMsgData::msg>(callBack);\
    }
#undef MESSAGE_INIT
    return true;
}
