#include "recordServer.h"
#include "flyer.h"
#include "superClient.h"
#include "messageHandle.h"
#include "excelBase.h"
#include "recordTimeTick.h"
#include "recordHandle.h"
#include "taskManager.h"
#include "recycleThread.h"
#include "verifyThread.h"
#include "recordDataManager.h"
#include "serverHandle.h"

static void ctrlHandler(int signal)
{
    Info(Flyer::logger,"[档案服务器] 终止");
    RecordServer &ref = RecordServer::getInstance();
    ref.setTerminate();
}

RecordServer::RecordServer() : Server("档案服务器",ProtoMsgData::ST_Record)
{
}

RecordServer::~RecordServer()
{
}

bool RecordServer::init()
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
        MessageHandleManager::getInstance().addHandle(boost::shared_ptr<ServerHandle>(new ServerHandle()));
        MessageHandleManager::getInstance().addHandle(boost::shared_ptr<RecordHandle>(new RecordHandle()));
        if(!MessageHandleManager::getInstance().init())
        {
            break;
        }
        if(!RecordDataManager::getInstance().init())
        {
            break;
        }
        if(!m_superClient->init())
        {
            break;
        }
        m_superClient->start();
        while(!getVerify())
        {
        }
        if(!listenPort())
        {
            break;
        }
        startThread();
        ret = true;
    }while(false);

    return ret;
}

bool RecordServer::loadConf()
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

bool RecordServer::loadExcelConf()
{
    std::string path = Flyer::globalConfMap["exceltbx"] + "tbx.xml";
    ExcelTbx::ExcelManager::getInstance().init(path,&Server::loadExcelTbx);
    return true;
}

bool RecordServer::end()
{
    endThread();
    return true;
}

void RecordServer::startServerThread()
{
    RecordTimeTick::getInstance().start();
}

void RecordServer::endServerThread()
{
    RecordTimeTick::getInstance().final();
    RecordTimeTick::getInstance().end();
}

bool RecordServer::acceptConnect(const int socket,const int listenPort)
{
    bool ret = false;
    do
    {
        if(listenPort != m_port)
        {
            break;
        }
        boost::shared_ptr<RecordTask> task(new RecordTask(socket));
        if(TaskManager::getInstance().addTask(task))
        {
            ret = VerifyThread::getInstance().add(task->getID());
        }
        if(!ret)
        {
            RecycleThread::getInstance().add(task->getID());
        }
    }while(false);
    return ret;
}



int main()
{
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    daemon(1,1);
    Flyer::init();
    Flyer::logger = log4cxx::Logger::getLogger("Record");
    Flyer::setLogger("log/record.log");
    if(RecordServer::getInstance().init())
    {
        Info(Flyer::logger,"[档案服务器] 启动成功");
        RecordServer::getInstance().main();
    }
    google::protobuf::ShutdownProtobufLibrary();
    Flyer::destory();
    return 0;
}
