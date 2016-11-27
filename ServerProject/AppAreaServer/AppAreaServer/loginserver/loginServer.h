#ifndef LOGIN_SERVER_H
#define LOGIN_SERVER_H
#include "singleton.h"
#include "server.h"
#include "system.pb.h"

class LoginServer : public Server,public Singleton<LoginServer>
{
    private:
        friend class Singleton<LoginServer>;
        LoginServer();
        ~LoginServer();
        bool loadExcelConf();
        bool loadAccount();
    public:
        bool init();
        virtual bool acceptConnect(const int socket,const int listenPort);
        bool initLoginIp();
        virtual bool loadConf();
        virtual bool end();
        virtual void startServerThread();
        virtual void endServerThread();
};

#endif
