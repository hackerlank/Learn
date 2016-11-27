#include "sceneServer.h"
#include "flyer.h"
#include "superClient.h"
#include "messageHandle.h"
#include "excelBase.h"
#include "sceneTimeTick.h"
#include "recordClient.h"
#include "recordHandle.h"
#include "taskManager.h"
#include "recycleThread.h"
#include "verifyThread.h"
#include "sceneTask.h"
#include "sceneHandle.h"

SceneServer::SceneServer() : Server("场景服务器",ProtoMsgData::ST_Scene)
{
}

SceneServer::~SceneServer()
{
}

bool SceneServer::init()
{
    bool ret = false;
    do
    {
        if(!Server::init())
        {
            break;
        }
        MessageHandleManager::getInstance().addHandle(boost::shared_ptr<RecordHandle>(new RecordHandle()));
        MessageHandleManager::getInstance().addHandle(boost::shared_ptr<SceneHandle>(new SceneHandle()));
        if(!MessageHandleManager::getInstance().init())
        {
            break;
        }
        boost::shared_ptr<SceneServer> ptr(this);
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
        if(!initConnectServer<RecordClient>(ProtoMsgData::ST_Record,ProtoMsgData::ST_Scene))
        {
            break;
        }
        ret = true;
    }while(false);

    return ret;
}

void SceneServer::startServerThread()
{
    SceneTimeTick::getInstance().start();
}

void SceneServer::endServerThread()
{
    SceneTimeTick::getInstance().final();
    SceneTimeTick::getInstance().end();
}

bool SceneServer::loadConf()
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

bool SceneServer::loadExcelConf()
{
    std::string path = Flyer::globalConfMap["exceltbx"] + "tbx.xml";
    ExcelTbx::ExcelManager::getInstance().init(path,&Server::loadExcelTbx);
    return true;
}

bool SceneServer::end()
{
    endThread();
    return true;
}

bool SceneServer::acceptConnect(const int socket)
{
    bool ret = false;
    boost::shared_ptr<SceneTask> task(new SceneTask(socket));
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
    Flyer::logger = log4cxx::Logger::getLogger("Scene");
    Flyer::setLogger("log/scene.log");
    if(SceneServer::getInstance().init())
    {
        Info(Flyer::logger,"[场景服务器] 启动成功");
        SceneServer::getInstance().main();
    }
    google::protobuf::ShutdownProtobufLibrary();
    return 0;
}
