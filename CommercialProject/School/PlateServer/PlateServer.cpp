#include "PlateServer.h"
#include "base/baseFunc.h"
#include "base/baseSqlHandle.h"
#include "base/baseSqlPool.h"
#include "base/baseSqlHandle.h"
#include "base/baseThread.h"
#include "plateTimeTick.h"

MysqlPool*  PlateServer::s_mySqlPool = NULL;

PlateServer::PlateServer() : NetService("平台服务器")
{
	m_serverID = 0;
	m_serverType = PLATESERVER;
	bzero(m_ip,sizeof(m_ip));
	m_port = 0;
	bzero(m_outIP,sizeof(m_outIP));
	m_outPort = 0;
	m_clientPool = NULL;
}

PlateServer::~PlateServer()
{
}

bool PlateServer::getServerInfo()
{
	strncpy(m_ip,"127.0.0.1",sizeof(m_ip));
	m_serverID = 3000;
	m_port = 3000;
	strncpy(name,"PLATESERVER",sizeof(name));
	m_outPort = 3005;
	return true;

#if 0
	MysqlHandle *handle = s_mySqlPool->getHandle();
	CheckConditonReturn(handle,false);
	
	bool ret = true;
	std::ostringstream temp;
	temp << "TYPE=" << SUPERSERVER;
	Record where;
	where.put("type",temp.str());
	RecordSet *recordSet = handle->exeSelect("PLATESERVER",NULL,&where);
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
#endif
}

bool PlateServer::init()
{
	 switchAnalysis((std::string)Global::config["cmdswitch"] == "true");
	s_mySqlPool = new MysqlPool();
	const char *mysql = (const char*)Global::config["mysql"];
	LogErrorCheckCondition(s_mySqlPool && s_mySqlPool->putUrl(0,mysql),false,"平台服务器连接数据库失败%s",mysql); 
	
	strncpy(m_ip,Socket::getIPByIfName(Global::config["ifname"]),sizeof(m_ip));

	LogErrorCheckCondition(getServerInfo(),false,"平台服务器设置IP和端口错误");

	m_taskPool = new TcpTaskPool(Global::config["threadPoolCapacity"]);
	LogErrorCheckCondition(m_taskPool && m_taskPool->init(),false,"平台服务器初始化任务池失败");

	m_clientPool = new TcpClientTaskPool(50,50000);
	LogErrorCheckCondition( m_clientPool && m_clientPool->init(),false,"平台服务器初始化客户端连接池失败" );
	LogErrorCheckCondition(PlateTimeTick::getInstance().start(),false,"平台服务器时间线程启动失败");
	LogErrorCheckCondition(NetService::init(m_port),false,"平台服务器邦定端口失败%d",m_port);
	return true;
}

void PlateServer::newTcpTask(const SDWORD sock,const struct sockaddr_in *addr)
{
	PlateTask *tcpTask = new PlateTask(sock,addr);
	if(!tcpTask)
	{
		TEMP_FAILURE_RETRY(::close(sock));
	}
	else if(!m_taskPool->addVerify(tcpTask))
	{
		DELETE(tcpTask);
	}
}

void PlateServer::final()
{
#if 0
	Cmd::Server::stShutdownStartServerCmd send;
	SuperTaskManager::getInstance().broadcast(&send,sizeof(send));
	while(!SuperUserManager::getInstance().isEmpty())
	{
		Thread::msleep(10);
	}
#endif
	PlateTimeTick::getInstance().final();
	PlateTimeTick::getInstance().join();
	PlateTimeTick::deleteInstance();
	if(m_taskPool)
	{
		m_taskPool->final();
		DELETE( m_taskPool );
	}
}

void PlateServer::switchAnalysis(const bool switchFlg)
{
	PlateTask::switchCmdAnalysis(switchFlg);
}



