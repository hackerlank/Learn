#include "SessionServer.h"
#include "base/baseProperty.h"
#include "sessionTimeTick.h"
#include "recordClient.h"
#include "sessionTask.h"

bool SessionServer::s_reloadConfig = false;
bool SessionServer::s_initOK = false;
bool SessionServer::s_waitFinal = false;


SessionServer::SessionServer() : SubNetService("SessionServer",SESSIONSERVER)
{
}

SessionServer::~SessionServer()
{
}

bool SessionServer::init()
{
	m_taskPool = new TcpTaskPool((DWORD)Global::config["threadPoolSize"],5000 );
	LogErrorCheckCondition(m_taskPool && m_taskPool->init(),false,"会话服务器初始化任务池失败");
	
	LogErrorCheckCondition(SubNetService::init(),false,"会话服务器服务器初始化失败");

	const ServerEntry *serverEntry = getServerEntryByType(RECORDSERVER);
	LogErrorCheckCondition(serverEntry,false,"会话服务器初始化找不到档案服务器");
	
	recordClient = new RecordClient("档案服务器",serverEntry->ip,serverEntry->port,serverEntry->serverID);
	LogErrorCheckCondition(recordClient && recordClient->connectToRecordServer() && recordClient->start(),false,"会话服务器初始化档案服务器连接初始化失败");
	
	LogErrorCheckCondition(SessionTimeTick::getInstance().start(),false,"会话服务器时间线程启动失败");
	
	switchAnalysis((std::string)Global::config["cmdswitch"] == "true");
	
	startUpOK();
	s_initOK = true;
	return true;
}

void SessionServer::startUpOver()
{
	SubNetService::startUpOver();
}

void SessionServer::newTcpTask(const int sock,const struct sockaddr_in *addr)
{
	SessionTask *tcpTask = new SessionTask(sock,addr);
	if(!tcpTask)
	{
		TEMP_FAILURE_RETRY(::close(sock));
	}
	else if(!m_taskPool->addVerify(tcpTask))
	{
		DELETE(tcpTask);
	}
}

bool SessionServer::msgParse_InfoServer(const Cmd::NullCmd *nullCmd,const DWORD cmdLen)
{
#if 0
	if( !SceneAdminToolMgr::getInstance().msgParse( nullCmd,cmdLen ) )
	{
		return SubNetService::msgParse_InfoServer( nullCmd,cmdLen );
	}
#endif
	return true;
}

bool SessionServer::msgParse_SuperService(const Cmd::NullCmd *nullCmd,const DWORD cmdLen)
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

void SessionServer::finalSave()
{
#if 0
	Global::logger->debug(" 停机保存数据" );
	SceneUserManager::getInstance().removeSceneUserAll();
	SceneNpcManager::getInstance().saveAllNpc();
#endif
}

void SessionServer::checkFinal()
{
	CheckConditonVoid(s_waitFinal);
	finalSave();
	s_waitFinal = true;
}

void SessionServer::final()
{
	s_waitFinal = true;
	while(s_initOK && s_waitFinal && !SessionTimeTick::getInstance().isFinal())
	{
		Thread::msleep(10);
	}
	SessionTimeTick::getInstance().final();
	SessionTimeTick::getInstance().join();
	SessionTimeTick::deleteInstance();

	if(m_taskPool)
	{
		m_taskPool->final();
		DELETE(m_taskPool);
	}
	if(recordClient)
	{
		recordClient->final();
		recordClient->join();
		DELETE(recordClient);
	}

	SubNetService::final();
}


void SessionServer::reloadConfig()
{
	s_reloadConfig = true;
}

void SessionServer::checkAndReloadConfig()
{
	CheckConditonVoid(s_reloadConfig);
	s_reloadConfig = false;
	switchAnalysis((std::string)Global::config["cmdswitch"] == "true");
}

int main( int argc,char **argv )
{
	struct timespec timeVal;
	clock_gettime( CLOCK_REALTIME,&timeVal);
	DWORD begin_time = timeVal.tv_sec*1000 + timeVal.tv_nsec/1000000;
	
	Global::logger = new Logger( "SE" );
	Global::config["cmdswitch"] = "true";
	Global::config["logfilename"] = "/home/flyer/flyer/SchoolProgress/trunk/School/log/sessionserver.log";
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
		Global::logger->info("SessionServer will be run as a daemon");
		Global::logger->removeConsole();
		daemon(1,1);
	}
	SessionServer::newInstance<SessionServer>();
	SessionServer::getInstance().loop();

	return EXIT_SUCCESS;
}

void SessionServer::switchAnalysis(const bool switchFlg)
{
	recordClient->switchCmdAnalysis(switchFlg);
	SessionTask::switchCmdAnalysis(switchFlg);
}


		



