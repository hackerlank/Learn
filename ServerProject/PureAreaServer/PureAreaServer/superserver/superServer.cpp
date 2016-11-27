#include "superServer.h"
#include "flyer.h"
#include "superTask.h"
#include "taskManager.h"
#include "messageHandle.h"
#include "superHandle.h"
#include "recycleThread.h"
#include "verifyThread.h"
#include "mainThread.h"
#include "superTimeTick.h"
#include "mysqlPool.h"
#include "client.h"
#include "clientManager.h"
#include "loginClient.h"
#include "loginHandle.h"
#include "excelBase.h"

SuperServer::SuperServer() :Server("管理服务器",ProtoMsgData::ST_Super)
{
}

SuperServer::~SuperServer()
{
}

bool SuperServer::init()
{
    bool ret = false;
    do
    {
        if(!Server::init())
        {
            break;
        }
        MessageHandleManager::getInstance().addHandle(boost::shared_ptr<SuperHandle>(new SuperHandle()));
        MessageHandleManager::getInstance().addHandle(boost::shared_ptr<LoginHandle>(new LoginHandle()));
        if(!MessageHandleManager::getInstance().init())
        {
            break;
        }
        m_ip = Flyer::globalConfMap["superip"];
        m_port = atol(Flyer::globalConfMap["superport"].c_str());
        if(!listenPort())
        {
            break;
        }
        startThread();
        if(!initConnectServer<LoginClient>(ProtoMsgData::ST_Login,ProtoMsgData::ST_Super))
        {
            break;
        }
        ret = true;
    }while(false);

    return ret;
}

bool SuperServer::acceptConnect(const int socket)
{
    bool ret = false;
    boost::shared_ptr<SuperTask> task(new SuperTask(socket));
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

bool SuperServer::loadConf()
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

bool SuperServer::loadExcelConf()
{
    std::string path = Flyer::globalConfMap["exceltbx"] + "tbx.xml";
    ExcelTbx::ExcelManager::getInstance().init(path,&Server::loadExcelTbx);
    return true;
}

bool SuperServer::end()
{
    endThread();
    return true;
}

void SuperServer::startServerThread()
{
    SuperTimeTick::getInstance().start();
}

void SuperServer::endServerThread()
{
    SuperTimeTick::getInstance().final();
    SuperTimeTick::getInstance().end();
}

void SuperServer::verifyOtherNotify(const ProtoMsgData::ServerType &serverType)
{
    for(auto iter = m_serverInfoMap.begin();iter != m_serverInfoMap.end();++iter)
    {
        const ProtoMsgData::ServerInfo &serverInfo = iter->second;
        if(serverInfo.status() == ProtoMsgData::ST_Wait && serverInfo.servertype() > serverType)
        {
            boost::shared_ptr<Connect> connect = TaskManager::getInstance().getServerTask(serverInfo.id());
            if(!connect)
            {
                continue;
            }
            boost::shared_ptr<SuperTask> superTask = boost::dynamic_pointer_cast<SuperTask>(connect);
            if(superTask)
            {
                superTask->verify(serverInfo.servertype());
            }
        }
    }
}

class Base
{
    public:
        virtual void doSameThing()
        {
            boost::shared_ptr<Base> now(this);
            std::cout << "fuck now :" << endl;
        }
        virtual ~Base()
        {
            std::cout << "~Base" << endl;
        }
};

class Father : public Base
{
    public:
        virtual void doSameThing()
        {
            std::cout << "fuck you !" << endl;
            Base::doSameThing();
        }
};

void del(Base *base)
{
    boost::shared_ptr<Base> now(base);
    now->doSameThing();
}


int main()
{

#if 0
    boost::shared_ptr<Father> father (new Father());
    father->doSameThing();
    std::cout << "test end" << endl;
    Base *base = new Base();
    del(base);
    std::cout << "now here del" << endl;
    std::vector<boost::shared_ptr<Base> > testVec;
    testVec.push_back(boost::shared_ptr<Base>(new Base()));
    testVec.push_back(boost::shared_ptr<Base>(new Father()));
    for(auto iter = testVec.begin();iter != testVec.end();++iter)
    {
        boost::shared_ptr<Base> base = *iter;
        base->doSameThing();
    }
    return 0;
#endif
    daemon(1,1);
    Flyer::init();
    Flyer::logger = log4cxx::Logger::getLogger("Super");
    Flyer::setLogger("log/super.log");
    if(SuperServer::getInstance().init())
    {
        Info(Flyer::logger,"[管理服务器] 启动成功");
        SuperServer::getInstance().main();
    }
    return 0;
}

