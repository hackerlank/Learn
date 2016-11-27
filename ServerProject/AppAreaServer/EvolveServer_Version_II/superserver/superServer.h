#ifndef SUPER_SERVER_H
#define SUPER_SERVER_H
#include "singleton.h"
#include "server.h"
#include "system.pb.h"

class SuperServer : public Server,public Singleton<SuperServer>
{
    private:
        friend class Singleton<SuperServer>;
        SuperServer();
        //这个不能放到base下,两个namespace会产生冲突
        bool loadExcelConf();
    public:
        ~SuperServer();
        bool init();
        virtual bool acceptConnect(const int socket,const int listenPort);
        bool verify(const unsigned int id);
        virtual bool loadConf();
        virtual bool end();
        void verifyOtherNotify(const ProtoMsgData::ServerType &serverType);
        virtual void startServerThread();
        virtual void endServerThread();

};

#endif
