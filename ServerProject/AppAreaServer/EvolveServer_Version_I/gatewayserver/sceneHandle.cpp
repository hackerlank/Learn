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
        SceneClient::s_sceneClientMsgDispatcher.messageReg<ProtoMsgData::msg>(callBack);\
    }
    MESSAGE_INIT(AckLoginScene,ackLoginScene);
    MESSAGE_INIT(AckUserMsg,ackUserMsg);
#undef MESSAGE_INIT
    return true;
}

bool SceneHandle::ackLoginScene(boost::shared_ptr<SceneClient> sceneClient,const boost::shared_ptr<ProtoMsgData::AckLoginScene> message)
{
    return sceneClient->ackLoginScene(message);
}

bool SceneHandle::ackUserMsg(boost::shared_ptr<SceneClient> sceneClient,const boost::shared_ptr<ProtoMsgData::AckUserMsg> message)
{
    return sceneClient->ackUserMsg(message);
}
