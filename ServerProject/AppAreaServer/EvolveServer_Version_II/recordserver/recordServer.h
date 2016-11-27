#ifndef RECORD_SERVER_H
#define RECORD_SERVER_H
#include "singleton.h"
#include "server.h"

class RecordServer;
typedef MessageDispatcher<RecordServer&> ServerMessageDispatcher;

class RecordServer : public Server,public Singleton<RecordServer>
{
    private:
        friend class Singleton<RecordServer>;
        RecordServer();
        bool loadExcelConf();
    public:
        ~RecordServer();
        bool init();
        virtual bool acceptConnect(const int socket,const int listenPort);
        virtual bool loadConf();
        virtual bool end();
        virtual void startServerThread();
        virtual void endServerThread();
        virtual MsgRet dispatcher(boost::shared_ptr<google::protobuf::Message> message);
        bool reqCreateUser(boost::shared_ptr<ProtoMsgData::ReqCreateUser> message);
    public:
        static ServerMessageDispatcher s_serverMsgDispatcher;
};

#endif
