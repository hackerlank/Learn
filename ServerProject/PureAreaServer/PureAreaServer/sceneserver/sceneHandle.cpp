#include "sceneHandle.h"

SceneHandle::SceneHandle() : MessageHandle("场景服务器消息处理")
{
}

SceneHandle::~SceneHandle()
{
}

bool SceneHandle::init()
{
#define MESSAGE_INIT(msg,call) \
{\
    boost::shared_ptr<MsgCallBack<boost::shared_ptr<SceneTask>,ProtoMsgData::msg> > callBack(new MsgCallBack<boost::shared_ptr<SceneTask>,ProtoMsgData::msg>(&SceneHandle::call));\
    SceneTask::s_sceneMsgDispatcher.messageReg<ProtoMsgData::msg>(callBack);\
}
    MESSAGE_INIT(ReqVerifyServer,reqVerifyServer);

#undef MESSAGE_INIT

    return true;
}

bool SceneHandle::reqVerifyServer(boost::shared_ptr<SceneTask> sceneTask,const boost::shared_ptr<ProtoMsgData::ReqVerifyServer> message)
{
    return sceneTask->verify(message->serverinfo());
}
