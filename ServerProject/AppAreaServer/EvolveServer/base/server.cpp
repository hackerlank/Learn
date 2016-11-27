#include "server.h"
#include "cmdFunManager.h"
#include "mysqlPool.h"
#include "flyer.h"
#include "superClientHandle.h"
#include "client.h"
#include "excel.h"
#include "taskManager.h"
#include "clientManager.h"
#include "clientHandle.h"
#include "redisMemManager.h"
#include "connectHandle.h"
#include "clientThread.h"
#include "threadPool.h"

Server::Server(const std::string &name,const ProtoMsgData::ServerType &type) : m_name(name),m_type(type),m_id(0),m_port(0),m_fd(-1),m_epfd(-1),m_verify(false),m_outIp(),m_outPort(0),m_outFd(-1),m_superClient(NULL),m_terminate(false)
{
    m_epfd = epoll_create(10);
}

Server::~Server()
{
    if(m_fd != -1)
    {
        TEMP_FAILURE_RETRY(::close(m_fd));
    }
    if(m_outFd != -1)
    {
        TEMP_FAILURE_RETRY(::close(m_outFd));
    }
    TEMP_FAILURE_RETRY(::close(m_epfd));
}

std::string Server::getNodeName()
{
    std::string nodeName;
    switch(m_type)
    {
        case ProtoMsgData::ST_Login:
            {
                nodeName = "login";
            }
            break;
        case ProtoMsgData::ST_Super:
            {
                nodeName = "super";
            }
            break;
        case ProtoMsgData::ST_Record:
            {
                nodeName = "record";
            }
            break;
        case ProtoMsgData::ST_Scene:
            {
                nodeName = "scene";
            }
            break;
        case ProtoMsgData::ST_Gateway:
            {
                nodeName = "gateway";
            }
            break;
        case ProtoMsgData::ST_Robot:
            {
                nodeName = "robot";
            }
            break;
        default:
            break;
    }
    return nodeName;
}

bool Server::init()
{
    bool ret = false;
    do
    {
        std::string nodeName = getNodeName();
        if(!Flyer::loadXmlConf("configdir/config.xml",nodeName.c_str()))
        {
            break;
        }
        if(!CmdFunManager::getInstance().loadCmd(Flyer::globalConfMap["cmdxml"].c_str()))
        {
            break;
        }
        if(!MysqlPool::getInstance().addUrl(Flyer::globalConfMap["mysql"]))
        {
            break;
        }
        if(m_type != ProtoMsgData::ST_Robot && m_type != ProtoMsgData::ST_Login && m_type != ProtoMsgData::ST_Super)
        {
            MessageHandleManager::getInstance().addHandle(boost::shared_ptr<SuperClientHandle>(new SuperClientHandle()));
            m_superClient = boost::shared_ptr<SuperClient>(new SuperClient(this));
        }
        MessageHandleManager::getInstance().addHandle(boost::shared_ptr<ConnectHandle>(new ConnectHandle()));
        MessageHandleManager::getInstance().addHandle(boost::shared_ptr<TaskHandle>(new TaskHandle()));
        if(!ThreadPool::getInstance().init())
        {
            break;
        }
        if(m_type != ProtoMsgData::ST_Login)
        {
            MessageHandleManager::getInstance().addHandle(boost::shared_ptr<ClientHandle>(new ClientHandle()));
        }
        if(!loadConf())
        {
            break;
        }
        if(m_type != ProtoMsgData::ST_Login && m_type != ProtoMsgData::ST_Record)
        {
            if(!ClientThread::getInstance().init())
            {
                break;
            }
        }
        if(!RedisMemManager::getInstance().init())
        {
            break;
        }
        //清空redis
        if(m_type == ProtoMsgData::ST_Login)
        {
            if(!RedisMemManager::getInstance().getRedis())
            {
                break;
            }
            RedisMemManager::getInstance().clearMemory();
        }
        ret = true;
    }while(0);
    return ret;
}

bool Server::listenPort()
{
    bool ret = false;
    do
    {
        if(!Client::setConnect(m_fd))
        {
            break;
        }
        struct sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = inet_addr(m_ip.c_str());
        addr.sin_port = htons(m_port);
        if(-1 == ::bind(m_fd,(struct sockaddr*)&addr,sizeof(struct sockaddr)))
        {
            break;
        }
        if(listen(m_fd,20000) == -1)
        {
            break;
        }
        m_socketPortMap.insert(std::pair<int,int>(m_fd,m_port));
        if(m_socketPortMap.size() > m_epollEventVec.size())
        {
            m_epollEventVec.resize(m_socketPortMap.size() + 3);
        }
        struct epoll_event event;
        event.events = EPOLLIN;
        event.data.fd = m_fd;
        epoll_ctl(m_epfd,EPOLL_CTL_ADD,m_fd,&event);

        if(m_type != ProtoMsgData::ST_Login)
        {
            ret = true;
            break;
        }
        if(!Client::setConnect(m_outFd))
        {
            break;
        }
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = inet_addr(m_outIp.c_str());
        addr.sin_port = htons(m_outPort);
        if(-1 == ::bind(m_outFd,(struct sockaddr*)&addr,sizeof(struct sockaddr)))
        {
            break;
        }
        if(listen(m_outFd,20000) == -1)
        {
            break;
        }
        m_socketPortMap.insert(std::pair<int,int>(m_outFd,m_outPort));
        if(m_socketPortMap.size() > m_epollEventVec.size())
        {
            m_epollEventVec.resize(m_socketPortMap.size() + 3);
        }
        event.events = EPOLLIN;
        event.data.fd = m_outFd;
        epoll_ctl(m_epfd,EPOLL_CTL_ADD,m_outFd,&event);
        ret = true;
    }while(0);
    if(!ret)
    {
        TEMP_FAILURE_RETRY(close(m_fd));
        m_fd = -1;
        TEMP_FAILURE_RETRY(close(m_outFd));
        m_outFd = -1;
    }
    return ret;
}

int Server::accept(std::map<int,int> &socketMap)
{
    int ret = epoll_wait(m_epfd,&m_epollEventVec[0],m_socketPortMap.size(),atol(Flyer::globalConfMap["acceptwaittime"].c_str()));
    for(int cnt = 0;cnt < ret;++cnt)
    {
        if(m_epollEventVec[cnt].events & EPOLLIN)
        {
            int socket = TEMP_FAILURE_RETRY(::accept(m_epollEventVec[cnt].data.fd,NULL,NULL));
            socketMap.insert(std::pair<int,int>(socket,m_socketPortMap[m_epollEventVec[cnt].data.fd]));
        }
    }
    return ret;
}

void Server::serverCallBack()
{
    std::map<int,int> socketMap;
    accept(socketMap);
    for(auto iter = socketMap.begin();iter != socketMap.end();++iter)
    {
        if(iter->first == -1)
        {
            Error(Flyer::logger,"[接收错误](套接字为负数)");
        }
        else
        {
            acceptConnect(iter->first,iter->second);
        }
    }
    socketMap.clear();
    return ;
}

void Server::main()
{
    while(!m_terminate)
    {
        serverCallBack();
    }
    end();
}

ProtoMsgData::ServerType Server::getType() const
{
    return m_type;
}

void Server::setServerInfo(const ProtoMsgData::ServerInfo &serverInfo)
{
    m_id = serverInfo.id();
    m_port = serverInfo.port();
    m_ip = serverInfo.ip();
    m_verify = true;
    char temp[100] = {0};
    switch(m_type)
    {
        case ProtoMsgData::ST_Record:
            {
                snprintf(temp,sizeof(temp),"log/record-%02d.log",m_id);
            }
            break;
        case ProtoMsgData::ST_Scene:
            {
                snprintf(temp,sizeof(temp),"log/scene-%02d.log",m_id);
            }
            break;
        case ProtoMsgData::ST_Gateway:
            {
                snprintf(temp,sizeof(temp),"log/gateway-%02d.log",m_id);
            }
            break;
        case ProtoMsgData::ST_Login:
            {
                snprintf(temp,sizeof(temp),"log/login-%02d.log",m_id);
            }
            break;
        case ProtoMsgData::ST_Super:
            {
                snprintf(temp,sizeof(temp),"log/super-%02d.log",m_id);
            }
            break;
        default:
            {
            }
            break;
    }
    if(strlen(temp))
    {
        Flyer::changeLogger(temp,0);
    }
}

bool Server::getVerify() const
{
    return m_verify;
}

void Server::loadExcelTbx(const std::string &file,char *&buf,int &size)
{
    FILE *fp = fopen(file.c_str(), "rb+");
    if(fp)
    {
        fseek(fp, SEEK_SET, SEEK_END);
        size = ftell(fp);
        fseek(fp, 0, SEEK_SET);
        buf = new char[size];
        if(fread(buf, size, 1, fp));
        fclose(fp);
    }
}

void Server::updateOtherServer(const ProtoMsgData::ServerInfo &serverInfo)
{
    m_serverInfoMap[serverInfo.id()] = serverInfo;
}

bool Server::findServer(const unsigned int id)
{
    return m_serverInfoMap.find(id) != m_serverInfoMap.end();
}
void Server::addServer(const ProtoMsgData::ServerInfo &info)
{
    m_serverInfoMap.insert(std::pair<unsigned int,ProtoMsgData::ServerInfo>(info.id(),info));
}

ProtoMsgData::ServerInfo* Server::getServer(const unsigned int id)
{
    ProtoMsgData::ServerInfo* ret = NULL;
    auto iter = m_serverInfoMap.find(id);
    if(iter != m_serverInfoMap.end())
    {
        ret = &(iter->second);
    }
    return ret;
}

unsigned int Server::getServerID() const
{
    return m_id;
}

void Server::startThread()
{
    this->startServerThread();
    ThreadPool::getInstance().start();
}

void Server::endThread()
{
    this->endServerThread();
    if(m_superClient)
    {
        m_superClient->final();
        m_superClient->end();
    }
    ThreadPool::getInstance().final();
}

