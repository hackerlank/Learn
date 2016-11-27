#include "client.h"
#include "flyer.h"
#include "clientManager.h"
#include "superClient.h"

ClientMessageDispatcher Client::s_clientMsgDispatcher("客户端消息处理器");

Client::Client(const std::string &name,const std::string &ip,const unsigned short port,const int fd) : Connect(fd),m_name(name),m_ip(ip),m_port(port)
{
}

Client::~Client()
{
}

bool Client::init()
{
    return true;
}

bool Client::setConnect(int &fd)
{
    bool ret = false;
    do
    {
        fd = socket(AF_INET,SOCK_STREAM,0);
        int reUseAddr = 1;
        if(setsockopt(fd,SOL_SOCKET,SO_REUSEADDR,&reUseAddr,sizeof(reUseAddr)) == -1)
        {
            break;
        }
        socklen_t windowSize = atol(Flyer::globalConfMap["socketbuffersize"].c_str());
        if(setsockopt(fd,SOL_SOCKET,SO_RCVBUF,&windowSize,sizeof(windowSize)) == -1)
        {
            break;
        }
        if(setsockopt(fd,SOL_SOCKET,SO_SNDBUF,&windowSize,sizeof(windowSize)) == -1)
        {
            break;
        }
        ret = true;
    }while(false);
    return ret;
}

bool Client::connectOwner(int &fd,const std::string &ip,const unsigned short port)
{
    bool ret = false;
    do
    {
        if(!setConnect(fd))
        {
            break;
        }
        struct sockaddr_in address;
        bzero(&address,sizeof(address));
        address.sin_family = AF_INET;  
        address.sin_addr.s_addr = inet_addr(ip.c_str()); 
        address.sin_port = htons(port);
        if(connect(fd,(struct sockaddr*)(&address),sizeof(sockaddr)) == -1)
        {
            break;
        }
        ret = true;
    }while(false);
    return ret;
}

MsgRet Client::dispatcher(boost::shared_ptr<google::protobuf::Message> message)
{
    MsgRet ret = MR_No_Register;
    do
    {
        boost::shared_ptr<Client> client = ClientManager::getInstance().getClient(m_id);
        if(client)
        {
            ret = s_clientMsgDispatcher.dispatch(client,message);
        }
        else
        {
            client = boost::dynamic_pointer_cast<SuperClient>(getPtr());
            boost::shared_ptr<SuperClient> superClient = boost::dynamic_pointer_cast<SuperClient>(client);
            if(superClient)
            {
                ret = s_clientMsgDispatcher.dispatch(client,message);
            }
        }
    }while(false);
    return ret;
}
