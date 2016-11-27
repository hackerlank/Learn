#include "robotServer.h"
#include "flyer.h"
#include "messageHandle.h"
#include "excelBase.h"
#include "robotTimeTick.h"
#include "recycleThread.h"
#include "verifyThread.h"
#include "robotHandle.h"
#include "redisMemManager.h"
#include "logicManager.h"

RobotServer::RobotServer() : Server("机器人服务器",ProtoMsgData::ST_Robot)
{
}

RobotServer::~RobotServer()
{
}

bool RobotServer::init()
{
    bool ret = false;
    do
    {
        if(!Server::init())
        {
            break;
        }
        MessageHandleManager::getInstance().addHandle(boost::shared_ptr<RobotHandle>(new RobotHandle()));
        if(!MessageHandleManager::getInstance().init())
        {
            break;
        }
        startThread();
        ret = true;
    }while(false);

    return ret;
}

void RobotServer::startServerThread()
{
    RobotTimeTick::getInstance().start();
}

void RobotServer::endServerThread()
{
    RobotTimeTick::getInstance().final();
    RobotTimeTick::getInstance().end();
}

bool RobotServer::loadConf()
{
    return true;
#if 0
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
#endif
}

bool RobotServer::loadExcelConf()
{
    std::string path = Flyer::globalConfMap["exceltbx"] + "tbx.xml";
    ExcelTbx::ExcelManager::getInstance().init(path,&Server::loadExcelTbx);
    return true;
}

bool RobotServer::end()
{
    endThread();
    return true;
}

bool RobotServer::acceptConnect(const int socket,const int listenPort)
{
    bool ret = false;
    return ret;
}

int main()
{
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    daemon(1,1);
    Flyer::init();
    Flyer::logger = log4cxx::Logger::getLogger("Robot");
    Flyer::setLogger("log/robot.log");
    if(RobotServer::getInstance().init())
    {
        Info(Flyer::logger,"[机器人服务器] 启动成功");
        std::string cmd = "cmd=ReqRegister,phone=333,num=5000";
        LogicManager::getInstance().add(cmd);
        LogicManager::getInstance().waitCmd();
    }
    google::protobuf::ShutdownProtobufLibrary();
    return 0;
}
