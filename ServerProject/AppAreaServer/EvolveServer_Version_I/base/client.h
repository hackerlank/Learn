#ifndef CLIENT_H
#define CLIENT_H
#include "head.h"
#include "connect.h"

class Client;
typedef MessageDispatcher<boost::shared_ptr<Client> > ClientMessageDispatcher;

class Client : public Connect 
{
    public:
        Client(const std::string &name,const std::string &ip,const unsigned short port,const int fd);
        virtual ~Client();
        bool init();
        static bool setConnect(int &fd);
        static bool connectOwner(int &fd,const std::string &ip,const unsigned short port);
        virtual MsgRet dispatcher(boost::shared_ptr<google::protobuf::Message> message);
    private:
        const std::string m_name;
        const std::string m_ip;
        const unsigned short m_port;
    public:
        static ClientMessageDispatcher s_clientMsgDispatcher;
};

#endif
