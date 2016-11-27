#include "SuperServer.h"
#include "base/baseFunc.h"
#include "base/baseSqlHandle.h"
#include "base/baseSqlPool.h"
#include "base/baseSqlHandle.h"
#include "base/baseThread.h"
#include "superTimeTick.h"
#include "plateClient.h"

MysqlPool*  SuperServer::s_mySqlPool = NULL;

SuperServer::SuperServer() : NetService("服务器管理器")
{
	m_serverID = 0;
	m_serverType = SUPERSERVER;
	bzero(m_ip,sizeof(m_ip));
	m_port = 0;
	bzero(m_outIP,sizeof(m_outIP));
	m_outPort = 0;
	m_clientPool = NULL;
}

SuperServer::~SuperServer()
{
}

bool SuperServer::getServerInfo()
{
	MysqlHandle *handle = s_mySqlPool->getHandle();
	CheckConditonReturn(handle,false);
	
	bool ret = true;
	std::ostringstream temp;
	temp << "TYPE=" << SUPERSERVER;
	Record where;
	where.put("type",temp.str());
	RecordSet *recordSet = handle->exeSelect("SERVERLIST",NULL,&where);
	if(recordSet && recordSet->size() == 1)
	{
		strncpy(m_ip,recordSet->get(0)->getValue("ip"),strlen(m_ip));
		m_serverID = recordSet->get(0)->getValue("id");
		strncpy(name,recordSet->get(0)->getValue("name"),sizeof(name));
		m_port = recordSet->get(0)->getValue("port");
		m_outPort = recordSet->get(0)->getValue("outPort");
	}
	else
	{
		ret = false;
	}
	DELETE(recordSet);
	s_mySqlPool->putHandle(handle);
	return ret;
}

bool SuperServer::init()
{
	 switchAnalysis((std::string)Global::config["cmdswitch"] == "true");
	s_mySqlPool = new MysqlPool();
	const char *mysql = (const char*)Global::config["mysql"];
	LogErrorCheckCondition(s_mySqlPool && s_mySqlPool->putUrl(0,mysql),false,"管理服务器连接数据库失败%s",mysql); 
	
	strncpy(m_ip,Socket::getIPByIfName(Global::config["ifname"]),sizeof(m_ip));

	LogErrorCheckCondition(getServerInfo(),false,"管理服务器设置IP和端口错误");

	m_taskPool = new TcpTaskPool(Global::config["threadPoolCapacity"]);
	LogErrorCheckCondition(m_taskPool && m_taskPool->init(),false,"管理服务器初始化任务池失败");

	m_clientPool = new TcpClientTaskPool(50,50000);
	LogErrorCheckCondition( m_clientPool && m_clientPool->init(),false,"管理服务器初始化客户端连接池失败" );
	
	plateClient = new PlateClient("平台服务器",(const char*)Global::config["plateip"],(WORD)Global::config["plateport"],(DWORD)Global::config["plateid"]);
	LogErrorCheckCondition(plateClient && plateClient->connectToPlateServer() && plateClient->start(),false,"管理服务器初始化平台服务器连接初始化失败");
	
	LogErrorCheckCondition(NetService::init(m_port),false,"管理服务器邦定端口失败%d",m_port);
	LogErrorCheckCondition(SuperTimeTick::getInstance().start(),false,"管理服务器时间线程启动失败");
	
	return true;
}

void SuperServer::newTcpTask(const SDWORD sock,const struct sockaddr_in *addr)
{
	SuperTask *tcpTask = new SuperTask(sock,addr);
	if(!tcpTask)
	{
		TEMP_FAILURE_RETRY(::close(sock));
	}
	else if(!m_taskPool->addVerify(tcpTask))
	{
		DELETE(tcpTask);
	}
}

void SuperServer::final()
{
#if 0
	Cmd::Server::stShutdownStartServerCmd send;
	SuperTaskManager::getInstance().broadcast(&send,sizeof(send));
	while(!SuperUserManager::getInstance().isEmpty())
	{
		Thread::msleep(10);
	}
#endif
	SuperTimeTick::getInstance().final();
	SuperTimeTick::getInstance().join();
	SuperTimeTick::deleteInstance();
	if(m_taskPool)
	{
		m_taskPool->final();
		DELETE( m_taskPool );
	}
	if(m_clientPool)
	{
		m_clientPool->final();
		DELETE(m_clientPool);
	}
}

void SuperServer::switchAnalysis(const bool switchFlg)
{
	SuperTask::switchCmdAnalysis(switchFlg);
}



