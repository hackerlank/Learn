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
        if(!Server::init())
        {
            break;
        }
        MessageHandleManager::getInstance().addHandle(boost::shared_ptr<RecordHandle>(new RecordHandle()));
        if(!MessageHandleManager::getInstance().init())
        {
            break;
        }
        boost::shared_ptr<RecordServer> ptr(this);
        SuperClient::getInstance().s_server = ptr;
        if(!SuperClient::getInstance().init())
        {
            break;
        }
        SuperClient::getInstance().start();
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
    SuperClient::getInstance().final();
    SuperClient::getInstance().end();

    RecordTimeTick::getInstance().final();
    RecordTimeTick::getInstance().end();
}

bool RecordServer::acceptConnect(const int socket)
{
    bool ret = false;
    boost::shared_ptr<RecordTask> task(new RecordTask(socket));
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
    return 0;
}
