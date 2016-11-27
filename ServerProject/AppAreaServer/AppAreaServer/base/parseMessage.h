#ifndef PARSE_MESSAGE_H
#define PARSE_MESSAGE_H
#include "head.h"
class MessageData;

//通过消息的名称，查找且拷贝出一份消息
google::protobuf::Message* createMessage(const char *messageName);

//封装protobuf消息包
bool encodeMessage(const google::protobuf::Message* message,std::string &ret);

//解开protobuf消息包
boost::shared_ptr<google::protobuf::Message> decodeMessage(boost::shared_ptr<MessageData> messageData);

//解开protobuf消息包
boost::shared_ptr<google::protobuf::Message> decodeMessage(MessageData *message);
        
#endif
