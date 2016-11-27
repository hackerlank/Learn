#ifndef SCENE_CLIENT_H
#define SCENE_CLIENT_H 
#include "client.h"
#include "messageDispatcher.h"

class SceneClient;
typedef MessageDispatcher<boost::shared_ptr<SceneClient> > SceneClientMessageDispatcher;
class SceneClient : public Client
{
    public:
        SceneClient(const std::string &name,const std::string &ip,const unsigned short port,const int fd);
        virtual ~SceneClient();
        virtual MsgRet dispatcher(boost::shared_ptr<google::protobuf::Message> message);
    public:
        static SceneClientMessageDispatcher s_sceneClientMsgDispatcher;
    public:
        bool ackLoginScene(boost::shared_ptr<ProtoMsgData::AckLoginScene> message);
        bool ackUserMsg(boost::shared_ptr<ProtoMsgData::AckUserMsg> message);
};

#endif
