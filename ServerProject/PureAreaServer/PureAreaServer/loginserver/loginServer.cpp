#include "loginServer.h"
#include "flyer.h"
#include "serverTask.h"
#include "taskManager.h"
#include "messageHandle.h"
#include "serverHandle.h"
#include "recycleThread.h"
#include "verifyThread.h"
#include "mainThread.h"
#include "loginTimeTick.h"
#include "mysqlPool.h"
#include "excelBase.h"

LoginServer::LoginServer() :Server("登陆服务器",ProtoMsgData::ST_Login)
{
}

LoginServer::~LoginServer()
{
}

bool LoginServer::init()
{
    bool ret = false;
    do
    {
        if(!Server::init())
        {
            break;
        }
        MessageHandleManager::getInstance().addHandle(boost::shared_ptr<ServerHandle>(new ServerHandle()));
        if(!MessageHandleManager::getInstance().init())
        {
            break;
        }
        if(!initLoginIp())
        {
            break;
        }
        startThread();
        ret = true;
    }while(false);

    return ret;
}

bool LoginServer::acceptConnect(const int socket)
{
    bool ret = false;
    boost::shared_ptr<ServerTask> task(new ServerTask(socket));
    if(TaskManager::getInstance().addTask(task))
    {
        task->nextStatus();
        ret = VerifyThread::getInstance().add(task);
    }
    if(!ret)
    {
        TaskManager::getInstance().eraseTask(task->getID());
        task->setStatus(Task_Status_Recycle);
        RecycleThread::getInstance().add(task);
    }
    return ret;
}

bool LoginServer::initLoginIp()
{
    bool ret = false;
    std::vector<std::map<std::string,Flyer::FlyerValue> > ipVec;
    do
    {
        boost::shared_ptr<MysqlHandle> handle = MysqlPool::getInstance().getIdleHandle();
        if(!handle)
        {
            break;
        }
        char temp[100] = {0};
        snprintf(temp,sizeof(temp),"select id,ip,port from t_serverinfo where servertype = %u",ProtoMsgData::ST_Login);
        if(!handle->select(temp,strlen(temp),ipVec))
        {
            break;
        }
        for(unsigned int cnt = 0;cnt < ipVec.size();++cnt)
        {
            std::map<std::string,Flyer::FlyerValue> &tempMap = ipVec[cnt];
            if(tempMap.find("id") == tempMap.end())
            {
                continue;
            }
            std::string ip = tempMap["ip"];
            m_ip = ip;
            m_port = tempMap["port"];
            if(!listenPort())
            {
                break;
            }
        }
        ret = true;

    }while(false);
    return ret;
}

bool LoginServer::loadConf()
{
    bool ret = false;
    do
    {
        if(!loadExcelConf())
        {
            break;
        }
        ret = true;
    }while(false);
    return ret;
}

bool LoginServer::loadExcelConf() 
{
    std::string path = Flyer::globalConfMap["exceltbx"] + "tbx.xml";
    ExcelTbx::ExcelManager::getInstance().init(path,&Server::loadExcelTbx);
    return true;
}

bool LoginServer::end()
{
    endThread();
    return true;
}

void LoginServer::endServerThread()
{
    LoginTimeTick::getInstance().final();
    LoginTimeTick::getInstance().end();
}

void LoginServer::startServerThread()
{
    LoginTimeTick::getInstance().start();
}

int main()
{
    daemon(1,1);
    Flyer::init();
    Flyer::logger = log4cxx::Logger::getLogger("Login");
    Flyer::setLogger("log/login.log");
    if(LoginServer::getInstance().init())
    {
        Info(Flyer::logger,"[登陆服务器] 启动成功");
        LoginServer::getInstance().main();
    }
    return 0;
}

