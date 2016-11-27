#ifndef RECORD_SERVER_H
#define RECORD_SERVER_H
#include "singleton.h"
#include "server.h"

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
};

#endif
