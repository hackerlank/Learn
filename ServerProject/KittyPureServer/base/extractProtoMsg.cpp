#include "extractProtoMsg.h"
#include "FLCommand.h"
#include "cmdFunManager.h"

//通过消息的名称，查找且拷贝出一份消息
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

//把接收到的消息萃取Message
google::protobuf::Message* extraceProtoMsg(const BYTE *data, const DWORD nCmdLen)
{
    google::protobuf::Message *message = NULL;

    DWORD dataOffset = 0;
    DWORD cmdKey = *(DWORD*)(data+dataOffset);
    std::string protoName = CmdFunManager::getMe().getProtoName(cmdKey);
    if(protoName.empty())
    {
        return message;
    }
    dataOffset += sizeof(DWORD);
    message = createMessage(protoName.c_str());
    if(!message)
    {
        return message;
    }

    if(nCmdLen < dataOffset)
    {
        SAFE_DELETE(message);
        return message;
    }
    message->ParseFromArray(data+dataOffset, nCmdLen-dataOffset);
	return message;
}

bool encodeMessage(const google::protobuf::Message *message,std::string &result)
{
    if(!message)
    {
        return false;
    }
    DWORD cmdKey = CmdFunManager::getMe().getCmd(message->GetTypeName());
    if(!cmdKey)
    {
        return false;
    }
    BYTE messageType = PROTOBUF_TYPE;
    result.append(reinterpret_cast<char*>(&messageType), sizeof(BYTE));
    result.append(reinterpret_cast<char*>(&cmdKey), sizeof(int32_t)); 
    return message->AppendToString(&result);
}
 
bool encodeMessage(const _null_cmd_ *message,const DWORD len,std::string &result)
{
    if(!message || len <= 0 )
    {
        return false;
    }
    BYTE messageType = STRUCT_TYPE;
    result.append(reinterpret_cast<char*>(&messageType), sizeof(BYTE));
    result.append((char*)(&(*message)),len);
    return true;
}

void logStructMessage(const CMD::t_NullCmd *ptNullCmd, const DWORD nCmdLen,const QWORD mesc,const bool sendFlg)
{
    if(ptNullCmd->cmd != CMD::FL::PARA_LOGIN && ptNullCmd->para != CMD::FL::PARA_FL_GYLIST)
    {
        Fir::logger->debug("c++ [%s消息统计](%u,%u,%u,%lu)",sendFlg ? "发送" : "接收",ptNullCmd->cmd,ptNullCmd->para,nCmdLen,mesc);
    }
}

bool encodeMessage(const char *data,const DWORD size,std::string &result)
{
    if(!data || size <= 0)
    {
        return false;
    }
    
    BYTE messageType = STRUCT_TYPE;
    result.append(reinterpret_cast<char*>(&messageType), sizeof(BYTE));
    result.append(data,size);
    return true;
}

void logProtoMessage(const char *name,const DWORD nCmdLen,const QWORD msec,const bool sendFlg)
{    
    if(strcmp(name,"HelloKittyMsgData.AckGameTime"))
    {
        Fir::logger->debug("proto [%s消息统计](%s,%u,%lu)",sendFlg ? "发送" : "接收",name,nCmdLen,msec);
    }
}

void logMessage(const char *data,const DWORD nCmdLen,const QWORD msec,const bool sendFlg)
{
    //能否保证是个完整包？？？
    if(!data || nCmdLen <= 0)
    {
        return;
    }
    
    BYTE messageType = *(BYTE*)data;
    if(messageType == STRUCT_TYPE)
    {
        return logStructMessage((CMD::t_NullCmd*)data,nCmdLen-1,msec,sendFlg);
    }
    else if(messageType != PROTOBUF_TYPE)
    {
        return;
    }
    DWORD cmdKey = *(DWORD*)(data+sizeof(BYTE)); 
    std::string protoName = CmdFunManager::getMe().getProtoName(cmdKey);
    if(!cmdKey || protoName.empty())
    {
        return;
    }
    if(nCmdLen  <  sizeof(BYTE) + sizeof(DWORD))
    {
        int lens = nCmdLen - sizeof(BYTE)-sizeof(DWORD);
        Fir::logger->debug("proto [%s警告消息长度](%s,%d,%lu)",sendFlg ? "发送" : "接收",protoName.c_str(),lens,msec);
        return;
    }
    logProtoMessage(protoName.c_str(),nCmdLen-sizeof(BYTE)-sizeof(DWORD),msec,sendFlg);
    return;
}


