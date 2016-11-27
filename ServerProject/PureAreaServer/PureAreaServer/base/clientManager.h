#ifndef CLIENT_MANAGER_H
#define CLIENT_MANAGER_H
#include "client.h"
#include "head.h"
#include "thread.h"
#include "taskQueue.h"
#include "client.h"

class ClientManager : public Thread,public TaskQueue,public Singleton<ClientManager>
{
    private:
        std::map<unsigned long,boost::shared_ptr<Client> >m_clientMap;
        int m_epfd;
        std::vector<struct epoll_event> m_eventVec;
    private:
        friend class Singleton<ClientManager>;
        ClientManager();
        ~ClientManager();
    public:
        virtual bool add(boost::shared_ptr<Client> client);
        boost::shared_ptr<Client> getClient(const unsigned long id);
        virtual void run();
        bool init();
        //检查是否连上
        int checkStatus(const unsigned int num,const ProtoMsgData::ServerType &serverType);
};

#endif

