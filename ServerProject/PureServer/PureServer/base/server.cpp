#include "server.h"
#include "taskManager.h"
#include "timeTick.h"
#include "flyer.h"
#include "mainThread.h"
#include <log4cxx/propertyconfigurator.h>
#include "flyerXmlParse.h"
#include "cmdFunManager.h"
#include "mysqlPool.h"

Server::Server()
{
    m_fd = -1;
    m_epfd = epoll_create(10);
}

bool Server::init()
{
    bool ret = false;
    do
    {

        if(!CmdFunManager::getInstance().loadCmd(Flyer::globalConfMap["cmdxml"].c_str()))
        {
            break;
        }
        if(!MysqlPool::getInstance().addUrl(Flyer::globalConfMap["mysql"]))
        {
            break;
        }
        CmdFunManager::getInstance().logCmdMap();
        m_fd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
        if(m_fd == -1 || m_socketPortMap.find(m_fd) != m_socketPortMap.end())
        {
            break;
        }
        int reUseAddr = 1;
        if(setsockopt(m_fd,SOL_SOCKET,SO_REUSEADDR,&reUseAddr,sizeof(reUseAddr)) == -1)
        {
            break;
        }
        socklen_t windowSize = atol(Flyer::globalConfMap["socketbuffersize"].c_str());
        if(setsockopt(m_fd,SOL_SOCKET,SO_RCVBUF,&windowSize,sizeof(windowSize)) == -1)
        {
            break;
        }
        if(setsockopt(m_fd,SOL_SOCKET,SO_SNDBUF,&windowSize,sizeof(windowSize)) == -1)
        {
            break;
        }
        struct sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = inet_addr("121.40.77.217");
        addr.sin_port = htons(s_port);
        if(-1 == ::bind(m_fd,(struct sockaddr*)&addr,sizeof(struct sockaddr)))
        {
            break;
        }
        if(listen(m_fd,20000) == -1)
        {
            break;
        }
        m_socketPortMap.insert(std::pair<int,int>(m_fd,addr.sin_port));
        if(m_socketPortMap.size() > m_epollEventVec.size())
        {
            m_epollEventVec.resize(m_socketPortMap.size() + 3);
        }

        struct epoll_event event;
        event.events = EPOLLIN;
        event.data.fd = m_fd;
        epoll_ctl(m_epfd,EPOLL_CTL_ADD,m_fd,&event);
        TimeTick::getInstance().start();
        MainThread::getInstance().start();
        ret = true;
    }while(0);
    if(!ret)
    {
        TEMP_FAILURE_RETRY(close(m_fd));
        m_fd = -1;
    }
    return ret;
}

int Server::accept(std::map<int,int> &socketMap)
{
    int ret = epoll_wait(m_epfd,&m_epollEventVec[0],m_socketPortMap.size(),s_timeOut);
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
        boost::shared_ptr<Task> task(new Task(iter->first));
        if(TaskManager::getInstance().addTask(task))
        {
            MainThread::getInstance().addTask(task);
        }
    }
    socketMap.clear();
    return ;
}

int main()
{
    daemon(1,1);
    Flyer::seed = time(NULL);
    Flyer::logger = log4cxx::Logger::getLogger("Server");
    Flyer::setLogger("log/server.log");
    const char *fileName = "configdir/config.xml";
    Flyer::loadXmlConf(fileName);
    Flyer::logGlobalMap();
    if(Server::getInstance().init())
    {
        std::cout << "服务器启动完毕!" << std::endl;
        while(true)
        {
            Server::getInstance().serverCallBack();
        }
    }
    return 0;
}
