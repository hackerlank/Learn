#include "sceneClient.h"
#include "clientManager.h"
#include "taskManager.h"
#include "gatewayTask.h"
#include "construct.h"
#include "parseMessage.h"

SceneClientMessageDispatcher SceneClient::s_sceneClientMsgDispatcher("场景服客户端消息处理器");
SceneClient::SceneClient(const std::string &name,const std::string &ip,const unsigned short port,const int fd) : Client(name,ip,port,fd)
{
}

SceneClient::~SceneClient()
{
}

MsgRet SceneClient::dispatcher(boost::shared_ptr<google::protobuf::Message> message)
{
    MsgRet ret = MR_No_Register;
    do
    {
        ret = Client::dispatcher(message);
        if(ret == MR_No_Register)
        {
            boost::shared_ptr<Client> client = ClientManager::getInstance().getClient(m_id);
            boost::shared_ptr<SceneClient> sceneClient = boost::dynamic_pointer_cast<SceneClient>(client);
            if(sceneClient)
            {
                ret = s_sceneClientMsgDispatcher.dispatch(sceneClient,message);
            }
        }
    }while(false);
    return ret;
}

bool SceneClient::ackLoginScene(boost::shared_ptr<ProtoMsgData::AckLoginScene> message)
{
    bool ret = false;
    do
    {
        boost::shared_ptr<Connect> connect = TaskManager::getInstance().getGatewayTask(message->charid());
        boost::shared_ptr<GatewayTask> gatewayTask = boost::dynamic_pointer_cast<GatewayTask>(connect);
        if(!gatewayTask)
        {
            break;
        }
        ret = true;
    }while(false);
    return ret;
}

bool SceneClient::ackUserMsg(boost::shared_ptr<ProtoMsgData::AckUserMsg> message)
{
    bool ret = false;
    do
    {
        boost::shared_ptr<Connect> connect = TaskManager::getInstance().getGatewayTask(message->charid());
        boost::shared_ptr<GatewayTask> gatewayTask = boost::dynamic_pointer_cast<GatewayTask>(connect);
        if(!gatewayTask)
        {
            break;
        }
        unsigned char buffer[atol(Flyer::globalConfMap["datasize"].c_str())];
        bzero(buffer,sizeof(buffer));
        MessageData *messageData = (MessageData*)buffer;
        constructInBuffer(messageData);
        if(!messageData->initFromData(message->data()))
        {
            break;
        }
        boost::shared_ptr<google::protobuf::Message> msg = decodeMessage(messageData);
        if(!msg)
        {
            break;
        }
        google::protobuf::Message *proMsg = msg.get();
        if(!proMsg)
        {
            break;
        }
        ret = gatewayTask->sendMsg(*proMsg);
    }while(false);
    return ret;
}

