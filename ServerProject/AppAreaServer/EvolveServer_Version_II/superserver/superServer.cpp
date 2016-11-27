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

static void ctrlHandler(int signal)
{
    Info(Flyer::logger,"[管理服务器] 终止");
    SuperServer &ref = SuperServer::getInstance();
    ref.setTerminate();
}

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
        struct sigaction sig;
        sig.sa_handler = ctrlHandler;
        sig.sa_flags = 0;
        sigemptyset(&sig.sa_mask);
        sigaction(SIGINT,&sig,NULL);

#if 0
        sigaction(SIGQUIT,&sig,NULL);
        sigaction(SIGABRT,&sig,NULL);
        sigaction(SIGTERM,&sig,NULL);
        sigaction(SIGHUP,&sig,NULL);
#endif

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
        m_id = atol(Flyer::globalConfMap["superid"].c_str());
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

bool SuperServer::acceptConnect(const int socket,const int listenPort)
{
    bool ret = false;
    if(listenPort != m_port)
    {
        return ret;
    }
    boost::shared_ptr<SuperTask> task(new SuperTask(socket));
    if(TaskManager::getInstance().addTask(task))
    {
        ret = VerifyThread::getInstance().add(task->getID());
    }
    if(!ret)
    {
        RecycleThread::getInstance().add(task->getID());
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
            boost::shared_ptr<Task> task = TaskManager::getInstance().getServerTask(serverInfo.id());
            boost::shared_ptr<SuperTask> superTask = boost::dynamic_pointer_cast<SuperTask>(task);
            if(superTask)
            {
                superTask->verify(serverInfo.servertype());
            }
        }
    }
}

class Base : public boost::enable_shared_from_this<Base>
{
    public:
        virtual void doSameThing()
        {
        }
        virtual ~Base()
        {
            std::cout << "~Base" << endl;
        }
        boost::shared_ptr<Base> getSharedPtr()
        {
            boost::shared_ptr<Base> ptr = shared_from_this();
            return ptr;
        }
};

class Father : public Base
{
    public:
        virtual void doSameThing()
        {
            std::cout << "fuck you !" << endl;
        }
};

void del(Base *base)
{
    boost::shared_ptr<Base> now = base->getSharedPtr();
    now->doSameThing();
}

void delFather(Base *base)
{
    boost::shared_ptr<Father> now = boost::dynamic_pointer_cast<Father>(base->getSharedPtr());
    now->doSameThing();
}



int main()
{
#if 0
    Base *base = new Base();
    boost::shared_ptr<Base> here(base);
    del(base);
    Father *father = new Father();
    boost::shared_ptr<Base> fat(father);
    delFather(father);

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
    Flyer::destory();
    return 0;
}

