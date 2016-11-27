#ifndef RECORD_CLIENT_H
#define RECORD_CLIENT_H 
#include "client.h"
#include "messageDispatcher.h"

class RecordClient;
typedef MessageDispatcher<boost::shared_ptr<RecordClient> > RecordClientMessageDispatcher;
class RecordClient : public Client
{
    public:
        RecordClient(const std::string &name,const std::string &ip,const unsigned short port,const int fd);
        virtual ~RecordClient();
        virtual MsgRet dispatcher(boost::shared_ptr<google::protobuf::Message> message);
    public:
        static RecordClientMessageDispatcher s_recordClientMsgDispatcher;
};

#endif
