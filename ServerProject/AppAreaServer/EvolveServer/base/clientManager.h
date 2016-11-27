#ifndef CLIENT_MANAGER_H
#define CLIENT_MANAGER_H
#include "head.h"
#include "client.h"

class ClientManager : public Singleton<ClientManager>
{
    private:
        std::map<unsigned long,boost::shared_ptr<Client> >m_clientMap;
    private:
        friend class Singleton<ClientManager>;
        ClientManager();
        ~ClientManager();
    public:
        virtual bool add(boost::shared_ptr<Client> client);
        boost::shared_ptr<Client> getClient(const unsigned long id);
        boost::shared_ptr<Client> getServerClient(const unsigned short id);
        void eraseClient(const unsigned long id);
        //检查是否连上
        int checkStatus(const unsigned int num,const ProtoMsgData::ServerType &serverType);
        boost::shared_ptr<Client> getClientByType(const ProtoMsgData::ServerType serverType);

};

#endif

