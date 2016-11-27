#ifndef ROBOT_SERVER_H
#define ROBOT_SERVER_H 
#include "singleton.h"
#include "server.h"

class RobotServer : public Server,public Singleton<RobotServer>
{
    private:
        friend class Singleton<RobotServer>;
        RobotServer();
        bool loadExcelConf();
    public:
        ~RobotServer();
        bool init();
        virtual bool acceptConnect(const int socket,const int listenPort); 
        virtual bool loadConf();
        virtual bool end();
        virtual void startServerThread();
        virtual void endServerThread();
};

#endif
