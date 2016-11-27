#ifndef SCENE_SERVER_H
#define SCENE_SERVER_H
#include "singleton.h"
#include "server.h"

class SceneServer : public Server,public Singleton<SceneServer>
{
    private:
        friend class Singleton<SceneServer>;
        SceneServer();
        bool loadExcelConf();
    public:
        ~SceneServer();
        bool init();
        virtual bool acceptConnect(const int socket,const int listenPort); 
        virtual bool loadConf();
        virtual bool end();
        virtual void startServerThread();
        virtual void endServerThread();
};

#endif
