#include "gatewayServer.h"
#include "flyer.h"
#include "superClient.h"
#include "messageHandle.h"
#include "excelBase.h"
#include "gatewayTimeTick.h"
#include "recordClient.h"
#include "sceneClient.h"
#include "recordHandle.h"
#include "sceneHandle.h"
#include "redisMemManager.h"
#include "system.pb.h"
#include "taskManager.h"
#include "verifyThread.h"
#include "recycleThread.h"
#include "gatewayTask.h"
#include "gatewayHandle.h"

static void ctrlHandler(int signal)
{
    Info(Flyer::logger,"[网关服务器] 终止");
    GatewayServer &ref = GatewayServer::getInstance();
    ref.setTerminate();
}

GatewayServer::GatewayServer() : Server("网关服务器",ProtoMsgData::ST_Gateway)
{
}

GatewayServer::~GatewayServer()
{
}

bool GatewayServer::init()
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
        MessageHandleManager::getInstance().addHandle(boost::shared_ptr<GatewayHandle>(new GatewayHandle()));
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
        if(!initConnectServer<RecordClient>(ProtoMsgData::ST_Record,ProtoMsgData::ST_Gateway))
        {
            break;
        }
        if(!initConnectServer<SceneClient>(ProtoMsgData::ST_Scene,ProtoMsgData::ST_Gateway))
        {
            break;
        }
        boost::shared_ptr<RedisMem> redisMem = RedisMemManager::getInstance().getRedis();
        if(!redisMem)
        {
            break;
        }
        ProtoMsgData::GatewayInfo gateInfo;
        gateInfo.set_id(m_id);
        gateInfo.set_ip(m_ip);
        gateInfo.set_port(m_port);
        gateInfo.set_person(0);
        gateInfo.set_status(ProtoMsgData::GS_Normal);
        char temp[Flyer::msglen] = {0};
        gateInfo.SerializeToArray(temp,Flyer::msglen);
        if(!redisMem->setSet("gateway","idset",m_id))
        {
            break;
        }
        redisMem = RedisMemManager::getInstance().getRedis(m_id);
        if(!redisMem)
        {
            break;
        }
        if(!redisMem->setBin("gateway",m_id,temp,gateInfo.ByteSize()))
        {
            break;
        }
        ret = true;
    }while(false);

    return ret;
}

bool GatewayServer::loadConf()
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

bool GatewayServer::loadExcelConf()
{
    std::string path = Flyer::globalConfMap["exceltbx"] + "tbx.xml";
    ExcelTbx::ExcelManager::getInstance().init(path,&Server::loadExcelTbx);
    return true;
}

bool GatewayServer::end()
{
    endThread();
    return true;
}

void GatewayServer::startServerThread()
{
    GatewayTimeTick::getInstance().start();
}

void GatewayServer::endServerThread()
{
    GatewayTimeTick::getInstance().final();
    GatewayTimeTick::getInstance().end();
}

bool GatewayServer::acceptConnect(const int socket,const int listenFd)
{
    bool ret = false;
    boost::shared_ptr<GatewayTask> task(new GatewayTask(socket));
    if(TaskManager::getInstance().addTask(task))
    {
        task->setServerType(ProtoMsgData::ST_Client);
        task->nextStatus();
        ret = VerifyThread::getInstance().add(task);
    }
    else
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
    Flyer::logger = log4cxx::Logger::getLogger("Gateway");
    Flyer::setLogger("log/gateway.log");
    if(GatewayServer::getInstance().init())
    {
        Info(Flyer::logger,"[管理服务器] 启动成功");
        GatewayServer::getInstance().main();
    }
    google::protobuf::ShutdownProtobufLibrary();
    Flyer::destory();
    return 0;
}
