#ifndef PARSE_MESSAGE_H
#define PARSE_MESSAGE_H
#include "head.h"
#include "messageQueue.h"

//通过消息的名称，查找且拷贝出一份消息
google::protobuf::Message* createMessage(const char *messageName);

//封装protobuf消息包
bool encodeMessage(const google::protobuf::Message* message,std::string &ret);

//解开protobuf消息包
google::protobuf::Message* decodeMessage(boost::shared_ptr<MessageData> messageData);

#endif
