#include "RecordServer.h"
#include "base/baseProperty.h"
#include "recordTimeTick.h"
#include "recordTask.h"

bool RecordServer::s_reloadConfig = false;
bool RecordServer::s_initOK = false;
bool RecordServer::s_waitFinal = false;


RecordServer::RecordServer() : SubNetService("RecordServer",RECORDSERVER)
{
}

RecordServer::~RecordServer()
{
}

bool RecordServer::init()
{
	switchAnalysis((std::string)Global::config["cmdswitch"] == "true");

	m_taskPool = new TcpTaskPool((DWORD)Global::config["threadPoolSize"],5000);
	LogErrorCheckCondition(m_taskPool && m_taskPool->init(),false,"档案服务器初始化任务池失败");
	
	LogErrorCheckCondition(SubNetService::init(),false,"档案服务器服务器初始化失败");

	LogErrorCheckCondition(RecordTimeTick::getInstance().start(),false,"档案服务器时间线程启动失败");
	
	startUpOK();
	s_initOK = true;
	return true;
}

void RecordServer::startUpOver()
{
	SubNetService::startUpOver();
}

void RecordServer::newTcpTask(const int sock,const struct sockaddr_in *addr)
{
	RecordTask *tcpTask = new RecordTask(sock,addr);
	if(!tcpTask)
	{
		TEMP_FAILURE_RETRY(::close(sock));
	}
	else if(!m_taskPool->addVerify(tcpTask))
	{
		DELETE(tcpTask);
	}
}

bool RecordServer::msgParse_InfoServer(const Cmd::NullCmd *nullCmd,const DWORD cmdLen)
{
#if 0
	if( !SceneAdminToolMgr::getInstance().msgParse( nullCmd,cmdLen ) )
	{
		return SubNetService::msgParse_InfoServer( nullCmd,cmdLen );
	}
#endif
	return true;
}

bool RecordServer::msgParse_SuperService(const Cmd::NullCmd *nullCmd,const DWORD cmdLen)
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

void RecordServer::finalSave()
{
#if 0
	Global::logger->debug(" 停机保存数据" );
	SceneUserManager::getInstance().removeSceneUserAll();
	SceneNpcManager::getInstance().saveAllNpc();
#endif
}

void RecordServer::checkFinal()
{
	CheckConditonVoid(s_waitFinal);
	finalSave();
	s_waitFinal = true;
}

void RecordServer::final()
{
	s_waitFinal = true;
	while(s_initOK && s_waitFinal && !RecordTimeTick::getInstance().isFinal())
	{
		Thread::msleep(10);
	}
	RecordTimeTick::getInstance().final();
	RecordTimeTick::getInstance().join();
	RecordTimeTick::deleteInstance();

	if(m_taskPool)
	{
		m_taskPool->final();
		DELETE(m_taskPool);
	}
	
	SubNetService::final();
}


void RecordServer::reloadConfig()
{
	s_reloadConfig = true;
}

void RecordServer::checkAndReloadConfig()
{
	LogCheckConditionOnly(s_reloadConfig,"档案服务器加载配置文件失败");
	
	s_reloadConfig = false;
	switchAnalysis( (std::string)Global::config["cmdswitch"] == "true" );
}

int main( int argc,char **argv )
{
	struct timespec timeVal;
	clock_gettime( CLOCK_REALTIME,&timeVal);
	DWORD begin_time = timeVal.tv_sec*1000 + timeVal.tv_nsec/1000000;
	
	Global::logger = new Logger( "RE" );
	Global::config["cmdswitch"] = "true";
	Global::config["logfilename"] = "/home/flyer/flyer/SchoolProgress/trunk/School/log/recordserver.log";
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
		Global::logger->info("RecordServer will be run as a daemon");
		Global::logger->removeConsole();
		daemon(1,1);
	}

	RecordServer::newInstance<RecordServer>();
	RecordServer::getInstance().loop();

	return EXIT_SUCCESS;
}

void RecordServer::switchAnalysis(const bool switchFlg)
{
	RecordTask::switchCmdAnalysis(switchFlg);
}



		



