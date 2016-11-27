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
        boost::shared_ptr<GatewayServer> ptr(this);
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
        if(!initConnectServer<RecordClient>(ProtoMsgData::ST_Record,ProtoMsgData::ST_Gateway))
        {
            break;
        }
        if(!initConnectServer<SceneClient>(ProtoMsgData::ST_Scene,ProtoMsgData::ST_Gateway))
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
    return 0;
}
