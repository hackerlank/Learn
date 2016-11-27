#ifndef GATE_WAY_SERVER_H
#define GATE_WAY_SERVER_H
#include "singleton.h"
#include "server.h"

class GatewayServer : public Server,public Singleton<GatewayServer>
{
    private:
        friend class Singleton<GatewayServer>;
        GatewayServer();
        bool loadExcelConf();
    public:
        ~GatewayServer();
        bool init();
        virtual bool acceptConnect(const int socket) 
        {
            return true;
        }
        virtual bool loadConf();
        virtual bool end();
        virtual void startServerThread();
        virtual void endServerThread();
};

#endif
