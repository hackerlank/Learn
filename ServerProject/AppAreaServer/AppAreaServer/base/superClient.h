#ifndef SUPER_CLIENT_H
#define SUPER_CLIENT_H
#include "head.h"
#include "connect.h"
#include "singleton.h"
#include "messageDispatcher.h"
class Server;

class SuperClient;
typedef MessageDispatcher<boost::shared_ptr<SuperClient> > SuperClientMessageDispatcher;
class SuperClient : public Connect,public Thread 
{
    public:
        SuperClient(Server *server);
        void close();
        ~SuperClient();
    private:
        int m_epfd;
        std::vector<struct epoll_event> m_eventVec;
        Server *m_server;
    public:
        static SuperClientMessageDispatcher s_dispatcher;
    public:
        inline Server* getServer()
        {
            return m_server;
        }
        bool init();
        virtual void run(); 
        virtual MsgRet dispatcher(boost::shared_ptr<google::protobuf::Message> message);

};

#endif
