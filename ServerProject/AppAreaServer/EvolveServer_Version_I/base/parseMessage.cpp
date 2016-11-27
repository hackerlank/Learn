#include "cmdFunManager.h"
#include "messageQueue.h"
#include "parseMessage.h"

google::protobuf::Message* createMessage(const char *messageName)
{
    google::protobuf::Message *message = NULL;
    if(!messageName)
    {
        return message;
    }
    const google::protobuf::Descriptor* descriptor = google::protobuf::DescriptorPool::generated_pool()->FindMessageTypeByName(messageName);
    if(!descriptor)
    {
        return message;
    }
    const google::protobuf::Message* prototype = google::protobuf::MessageFactory::generated_factory()->GetPrototype(descriptor);
    if(prototype)
    {
        message = prototype->New();
    }
    return message;
}

bool encodeMessage(const google::protobuf::Message* message,std::string &ret)
{
    if(!message)
    {
        return false;
    }
    unsigned int cmdKey = CmdFunManager::getInstance().getCmd(message->GetTypeName());
    if(!cmdKey)
    {
        Error(Flyer::logger,"[消息解析] 错误:没有注册(" << message->GetTypeName() << ")");
        return false;
    }
    unsigned int len = sizeof(unsigned int) + sizeof(cmdKey) + message->ByteSize();
    ret.append(reinterpret_cast<char*>(&len), sizeof(int32_t));
    ret.append(reinterpret_cast<char*>(&cmdKey), sizeof(int32_t));
    message->AppendToString(&ret);
    return true;
}

boost::shared_ptr<google::protobuf::Message> decodeMessage(boost::shared_ptr<MessageData> messageData)
{
    google::protobuf::Message *message = NULL;
    do
    {
        std::string protoName = CmdFunManager::getInstance().getProtoName(messageData->key);
        if(protoName.empty())
        {
            Error(Flyer::logger,"[消息解析] 错误:没有注册(" << messageData->key << ")");
            break;
        }
        message = createMessage(protoName.c_str());
        if(!message)
        {
            Error(Flyer::logger,"[消息解析] 错误:生成消息(" << protoName << ")");
            break;
        }
        message->ParseFromArray(messageData->data,messageData->size);
    }while(false);
    return boost::shared_ptr<google::protobuf::Message>(message);
}

boost::shared_ptr<google::protobuf::Message> decodeMessage(MessageData *messageData)
{
    google::protobuf::Message *message = NULL;
    do
    {
        std::string protoName = CmdFunManager::getInstance().getProtoName(messageData->key);
        if(protoName.empty())
        {
            Error(Flyer::logger,"[消息解析] 错误:没有注册(" << messageData->key << ")");
            break;
        }
        message = createMessage(protoName.c_str());
        if(!message)
        {
            Error(Flyer::logger,"[消息解析] 错误:生成消息(" << protoName << ")");
            break;
        }
        message->ParseFromArray(messageData->data,messageData->size);
    }while(false);
    return boost::shared_ptr<google::protobuf::Message>(message);
}




