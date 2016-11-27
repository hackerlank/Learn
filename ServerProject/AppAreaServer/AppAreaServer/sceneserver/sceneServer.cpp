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
#include "redisMemManager.h"

static void ctrlHandler(int signal)
{
    Info(Flyer::logger,"[场景服务器] 终止");
    SceneServer &ref = SceneServer::getInstance();
    ref.setTerminate();
}

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
        MessageHandleManager::getInstance().addHandle(boost::shared_ptr<RecordHandle>(new RecordHandle()));
        MessageHandleManager::getInstance().addHandle(boost::shared_ptr<SceneHandle>(new SceneHandle()));
        if(!MessageHandleManager::getInstance().init())
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
        if(!initConnectServer<RecordClient>(ProtoMsgData::ST_Record,ProtoMsgData::ST_Scene))
        {
            break;
        }
        boost::shared_ptr<RedisMem> redisMem = RedisMemManager::getInstance().getRedis();
        if(!redisMem)
        {
            break;
        }
        ProtoMsgData::SceneInfo sceneInfo;
        sceneInfo.set_id(m_id);
        sceneInfo.set_person(0);
        sceneInfo.set_status(ProtoMsgData::GS_Normal);
        char temp[Flyer::msglen] = {0};
        sceneInfo.SerializeToArray(temp,Flyer::msglen);
        if(!redisMem->setSet("scene","idset",m_id))
        {
            break;
        }
        redisMem = RedisMemManager::getInstance().getRedis(m_id);
        if(!redisMem)
        {
            break;
        }
        if(!redisMem->setBin("scene",m_id,temp,sceneInfo.ByteSize()))
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

bool SceneServer::acceptConnect(const int socket,const int listenPort)
{
    bool ret = false;
    if(listenPort != m_port)
    {
        return ret;
    }
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
    Flyer::destory();
    google::protobuf::ShutdownProtobufLibrary();
    return 0;
}
