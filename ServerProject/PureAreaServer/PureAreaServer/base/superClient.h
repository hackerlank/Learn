#ifndef SUPER_CLIENT_H
#define SUPER_CLIENT_H
#include "head.h"
#include "connect.h"
#include "singleton.h"
#include "messageDispatcher.h"
#include "server.h"

class SuperClient;
typedef MessageDispatcher<SuperClient&> SuperClientMessageDispatcher;
class SuperClient : public Connect,public Thread,public Singleton<SuperClient> 
{
    private:
        friend class Singleton<SuperClient>;
        SuperClient();
        void close();
    public:
        ~SuperClient();
    private:
        int m_epfd;
        std::vector<struct epoll_event> m_eventVec;
    public:
        static SuperClientMessageDispatcher s_dispatcher;
        static boost::shared_ptr<Server> s_server;
    public:
        bool init();
        virtual void run(); 
        virtual MsgRet dispatcher(boost::shared_ptr<google::protobuf::Message> message);

};

#endif
