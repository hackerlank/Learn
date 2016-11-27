#include "GatewayServer.h"
#include "base/baseProperty.h"
#include "base/testAutoPtr.h"
#include "recordClient.h"
#include "sessionClient.h"
#include "gateTask.h"

bool GatewayServer::s_reloadConfig = false;
bool GatewayServer::s_initOK = false;
bool GatewayServer::s_waitFinal = false;

GatewayServer::GatewayServer() : SubNetService("Gateway",GATEWAYSERVER)
{
}

GatewayServer::~GatewayServer()
{
}

bool GatewayServer::init()
{
	m_taskPool = new TcpTaskPool((DWORD)Global::config["threadPoolSize"],5000);

	LogErrorCheckCondition(m_taskPool && m_taskPool->init(),false,"网关服务器初始化任务池失败");
	
	LogErrorCheckCondition(SubNetService::init(),false,"网关服务器初始化网络服务器失败");
	
	const ServerEntry *serverEntry = getServerEntryByType(RECORDSERVER);
	LogErrorCheckCondition(serverEntry,false,"网关服务器初始化找不到档案服务器");
	
	recordClient = new RecordClient("档案服务器",serverEntry->ip,serverEntry->port,serverEntry->serverID);
	LogErrorCheckCondition(recordClient && recordClient->connectToRecordServer() && recordClient->start(),false,"网关服务器初始化档案服务器连接初始化失败");

	serverEntry = getServerEntryByType(SESSIONSERVER);
	LogErrorCheckCondition(serverEntry,false,"网关服务器初始化找不到会话服务器");

	sessionClient = new SessionClient( "Session服务器",serverEntry->ip,serverEntry->port,serverEntry->serverID);
	LogErrorCheckCondition(sessionClient && sessionClient->connectToSessionServer() && sessionClient->start(),false,"网关服务器初始化服务器连接初始化失败");
	
	LogErrorCheckCondition(GateTimeTick::getInstance().start(),false,"网关服务器初始化时间线程启动失败");
	
	switchAnalysis((std::string)Global::config["cmdswitch"] == "true");
	startUpOK();
	s_initOK = true;
	return true;
}

void GatewayServer::startUpOver()
{
	SubNetService::startUpOver();
}

void GatewayServer::newTcpTask(const int sock,const struct sockaddr_in *addr)
{
	GateTask *tcpTask = new GateTask(sock,addr);
	if(!tcpTask)
	{
		TEMP_FAILURE_RETRY(::close(sock));
	}
	else if(!m_taskPool->addVerify(tcpTask))
	{
		DELETE(tcpTask);
	}
}

bool GatewayServer::msgParse_InfoServer(const Cmd::NullCmd *nullCmd,const DWORD cmdLen)
{
#if 0
	if( !SceneAdminToolMgr::getInstance().msgParse( nullCmd,cmdLen ) )
	{
		return SubNetService::msgParse_InfoServer( nullCmd,cmdLen );
	}
#endif
	return true;
}

bool GatewayServer::msgParse_SuperService(const Cmd::NullCmd *nullCmd,const DWORD cmdLen)
{
#if 0
	using namespace Cmd::Server;
	switch( nullCmd->byCmd )
	{
		case FORWARD_SERVERCMD:
			{
				switch( nullCmd->byParam )
				{
					case SEND_USERCMD_TO_SERVERUSER_FORWARD_SERVERCMD:
						{
							stSendUserCmdToServerUserForwardServerCmd *rev = (stSendUserCmdToServerUserForwardServerCmd*)nullCmd;
							SceneUser *pUser = SceneUserManager::getInstance().getUserByID( rev->id );
							if( pUser )
							{
								pUser->userMsgParse( ( Cmd::stNullUserCmd* )rev->data,rev->dataSize );
							}
							return true;
						}
						break;
					}
				}
				break;
			case Cmd::Zone::CMD_ZONE:
				{
					return msgParse_ZoneService( nullCmd,cmdLen );
				}
				break;
	}
#endif
	return false;
}

void GatewayServer::finalSave()
{
#if 0
	Global::logger->debug(" 停机保存数据" );
	SceneUserManager::getInstance().removeSceneUserAll();
	SceneNpcManager::getInstance().saveAllNpc();
#endif
}

void GatewayServer::checkFinal()
{
	CheckConditonVoid(s_waitFinal);
	finalSave();
	s_waitFinal = true;
}

void GatewayServer::final()
{
	s_waitFinal = true;
	while(s_initOK && s_waitFinal && !GateTimeTick::getInstance().isFinal())
	{
		Thread::msleep(10);
	}
	GateTimeTick::getInstance().final();
	GateTimeTick::getInstance().join();
	GateTimeTick::deleteInstance();

	if(m_taskPool)
	{
		m_taskPool->final();
		DELETE(m_taskPool);
	}
	if(sessionClient)
	{
		sessionClient->final();
		sessionClient->join();
		DELETE(sessionClient);
	}
	if(recordClient)
	{
		recordClient->final();
		recordClient->join();
		DELETE(recordClient);
	}

	SubNetService::final();
}

void GatewayServer::reloadConfig()
{
	s_reloadConfig = true;
}

void GatewayServer::checkAndReloadConfig()
{
	CheckConditonVoid(s_reloadConfig);
	s_reloadConfig = false;
	switchAnalysis((std::string)Global::config["cmdswitch"] == "true");
}

int main(int argc,char **argv)
{
	struct timespec ts;
	clock_gettime(CLOCK_REALTIME,&ts);
	DWORD begin_time = ts.tv_sec*1000 + ts.tv_nsec/1000000;
	
	Global::logger = new Logger("GA");
	Global::config["cmdswitch"] = "true";
	Global::config["logfilename"] = "/home/flyer/flyer/SchoolProgress/trunk/School/log/gatewayserver.log";
	Global::config["LoggerLevel"] = "debug";
	Global::config["daemon"] = "true";
	Global::config["port"] = 5000;
	Global::config["serverIP"] = "127.0.0.1";
	Global::config["ifname"] = "eth0";

	Global::logger->setLevel((const char*)Global::config["LoggerLevel"]);
	if(strlen(Global::config["logfilename"]))
	{
		Global::logger->setFile((const char*)Global::config["logfilename"]);
	}
	
	if(!strcmp("true",Global::config["daemon"]))
	{
		Global::logger->info("Program will be run as a daemon");
		Global::logger->removeConsole();
		daemon(1,1);
	}

	GatewayServer::newInstance<GatewayServer>();
	GatewayServer::getInstance().loop();

	return EXIT_SUCCESS;
}

void GatewayServer::switchAnalysis(const bool switchFlg)
{
	sessionClient->switchCmdAnalysis(switchFlg);
	recordClient->switchCmdAnalysis(switchFlg);
	GateTask::switchCmdAnalysis(switchFlg);
}


		



