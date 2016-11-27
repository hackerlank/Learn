#include "recordClient.h"
#include "clientManager.h"

RecordClientMessageDispatcher RecordClient::s_recordClientMsgDispatcher("档案服客户端消息处理器");
RecordClient::RecordClient(const std::string &name,const std::string &ip,const unsigned short port,const int fd) : Client(name,ip,port,fd)
{
}

RecordClient::~RecordClient()
{
}

MsgRet RecordClient::dispatcher(boost::shared_ptr<google::protobuf::Message> message)
{
    MsgRet ret = MR_False;
    do
    {
        ret = Client::dispatcher(message);
        if(ret == MR_No_Register)
        {
            boost::shared_ptr<RecordClient> recordClient = boost::dynamic_pointer_cast<RecordClient>(getPtr());
            ret = s_recordClientMsgDispatcher.dispatch(recordClient,message);
        }
    }while(false);
    return ret;
}
