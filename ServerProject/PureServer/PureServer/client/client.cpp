#include "client.h"
#include "flyer.h"
#include "string.h"
#include "timeTick.h"
#include "taskManager.h"
#include "mainThread.h"
#include "flyerXmlParse.h"
#include "cmdFunManager.h"
#include "mysqlPool.h"

std::string Client::s_ip = "121.40.77.217";
int Client::s_port = 10000;

bool Client::connectServer()
{
    bool ret = false;
    do
    {
        int fd = socket(AF_INET,SOCK_STREAM,0);
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

        struct sockaddr_in address;
        bzero(&address,sizeof(address));
        address.sin_family = AF_INET;  
        address.sin_addr.s_addr = inet_addr("121.40.77.217"); 
        address.sin_port = htons(s_port);
        if(connect(fd,(struct sockaddr*)(&address),sizeof(sockaddr)) == -1)
        {
            LOG4CXX_INFO(Flyer::logger,"客户端connect错误");
            break;
        }
        char buffer[100] = {0};
        snprintf(buffer,sizeof(buffer),"客户端连接成功(%u)",fd);
        LOG4CXX_INFO(Flyer::logger,buffer);
        boost::shared_ptr<Task> task(new Task(fd));
        if(TaskManager::getInstance().addTask(task))
        {
            MainThread::getInstance().addTask(task);
            ret = true;
        }
    }while(false);

    return ret;
}

int main()
{
    daemon(1,1);
    Flyer::seed = time(NULL);
    Flyer::logger = log4cxx::Logger::getLogger("Client");
    Flyer::setLogger("log/client.log");
    const char *fileName = "configdir/config.xml";
    Flyer::loadXmlConf(fileName);
    Flyer::logGlobalMap();
    CmdFunManager::getInstance().loadCmd(Flyer::globalConfMap["cmdxml"].c_str());
    CmdFunManager::getInstance().logCmdMap();
    MysqlPool::getInstance().addUrl(Flyer::globalConfMap["mysql"]);
    MainThread::getInstance().start();
    TimeTick::getInstance().start();
    while(true)
    {
    }
    return 0;
}

