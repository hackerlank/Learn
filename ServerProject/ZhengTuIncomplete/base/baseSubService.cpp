#include "baseSubService.h"
#include "baseSuperClient.h"
#include "baseProperty.h"
#include "protol/protolCmd.h"

SubNetService::SubNetService( const std::string &name,const DWORD type ):NetService( name ),m_monitorTimer( 10*1000L ),m_generation( 0 )
{
	m_superPort = (DWORD )Global::config["port"];
	bzero( m_superIP,sizeof( m_superIP ) );
	strncpy( m_superIP,( const char* )Global::config["serverIP"],sizeof( m_superIP ) );
	m_superClient = new SuperClient();
	m_serverID = 0;
	m_serverType = type;

	bzero(m_serverName,sizeof(m_serverName));
	bzero(m_ip,sizeof(m_ip));

	m_port= 0;
	bzero(m_outIP,sizeof(m_outIP));
	m_outPort = 0;
	m_netType = 0;
	m_taskPool = NULL;
	m_startUp = false;
}

void SubNetService::setServerInfo(const Cmd::Server::ResponseStartServerCmd *cmd)
{
	m_serverID = cmd->serverID;
	m_port = cmd->port;
	m_outPort = cmd->outPort;
	m_netType = cmd->netType;
	strncpy(m_outIP,m_outIP,sizeof(m_outIP));
	Global::logger->debug("管理服务器客户端设置信息成功");
}

const ServerEntry* SubNetService::getServerEntryByType(const DWORD serverType)
{
	const ServerEntry *serverEntry = NULL;
	for(std::deque<ServerEntry>::iterator iter = m_serverList.begin();iter != m_serverList.end();++iter)
	{
		if((*iter).serverType == serverType)
		{
			serverEntry = &(*iter);
			break;
		}
	}
	return serverEntry;
}

void SubNetService::startUpOver()
{
	m_startUp = true;
	using namespace Cmd::Server;
	OkStartReturnServerCmd send;
	m_superClient->sendCmd(&send,sizeof(send));
}

SubNetService::~SubNetService()
{
	m_serverList.clear();
	DELETE( m_superClient );
}

bool SubNetService::init()
{
	LogErrorCheckCondition(m_superClient->connect(m_superIP,m_superPort),false,"服务器连接管理服务器失败%s,%u",m_superIP,m_superPort);

	strncpy(m_ip,Socket::getIPByIfName(Global::config["ifname"]),sizeof(m_ip));	
	
	m_superClient->setReConnect(false);
	using namespace Cmd::Server;
	RequestStartServerCmd cmd;
	cmd.serverType = m_serverType;
	cmd.protocol = Global::getVerifyVersion();
	cmd.buildTime = 0;
	cmd.svnVersion = 0;
	strncpy(cmd.ip,m_ip,sizeof(m_ip));
	
	LogErrorCheckCondition(m_superClient->sendCmd(&cmd,sizeof(cmd)),false,"网络服务器初始化发送消息给管理服务器失败%s,%u",m_superIP,m_superPort);
	
	while(!m_superClient->m_verify)
	{
		BYTE acceptCmd[Socket::s_maxDataSize];
		SDWORD cmdLen = m_superClient->m_pSocket->recvToCmd(acceptCmd,true);
		LogErrorCheckCondition(cmdLen != -1,false,"网络服务器初始化接受管理服务器消息失败%s,%u",m_superIP,m_superPort);

		if(cmdLen > 0)
		{
			Cmd::NullCmd *nullCmd = (Cmd::NullCmd*)acceptCmd;
			switch( nullCmd->byCmd )
			{
				case Cmd::Server::START_SERVERCMD:
					{
						m_superClient->msgParseStart(nullCmd,cmdLen);
					}
					break;
				case Cmd::Server::FORWARD_SERVERCMD:
					{
						m_superClient->msgParseForward(nullCmd,cmdLen);
					}
					break;
				default:
					m_superClient->msgParse(nullCmd,cmdLen);
					break;
			}
		}
	}

	std::ostringstream oss;
	oss << Global::logger->getName() << " " << m_serverID;
	Global::logger->setName(oss.str().c_str());

	m_superClient->start();
	
	LogErrorCheckCondition(NetService::init(m_port),false,"网络服务器初始化端口失败%s,%u",m_serverID,m_port);
	return true;
}

bool SubNetService::validate()
{
	using namespace Cmd::Server;
	OkStartServerCmd cmd;
	cmd.serverID = m_serverID;
	m_superClient->sendCmd(&cmd,sizeof(cmd));
	return true;
}

void SubNetService::final()
{
	NetService::final();
	m_superClient->final();
	m_superClient->join();
	m_superClient->close();
}

bool SubNetService::sendCmdToSuperServer( const void *strCmd,const DWORD cmdLen )
{
	return m_superClient->sendCmd( strCmd,cmdLen );
}

bool SubNetService::doCmd()
{
	return m_superClient->doCmd();
}

bool SubNetService::broadCmdToFLServer( const void *strCmd,const DWORD cmdLen )
{
#if 0
	BYTE buffer[Socket::s_maxDataSize];
	Cmd::Server::stFLServerForwardServerCmd *sendCmd = ( Cmd::Server::stFLServerForwardServerCmd* )buffer;
	constructInPlace( sendCmd );
	sendCmd->id = 0;
	sendCmd->num = cmdLen;
	bcopy( strCmd,sendCmd->data,cmdLen );
	return m_superClient->sendCmd( buffer,sendCmd->size() );
#endif
}

bool SubNetService::sendCmdToFLServer( const WORD serverID,const void *strCmd,const DWORD cmdLen )
{
	return true;
#if 0
	BYTE buffer[Socket::s_maxDataSize];
	Cmd::Server::stFLServerForwardServerCmd *sendCmd = ( Cmd::Server::stFLServerForwardServerCmd* )buffer;
	constructInPlace( sendCmd );
	sendCmd->id = serverID;
	sendCmd->num = cmdLen;
	bcopy( strCmd,sendCmd->data,cmdLen );
	return m_superClient->sendCmd( buffer,sendCmd->size() );
#endif
}

bool SubNetService::broadCmdToUserServer( const void *strCmd,const DWORD cmdLen )
{
	return true;
#if 0
	BYTE buffer[Socket::s_maxDataSize];
	Cmd::Server::stUserServerForwardServerCmd *sendCmd = ( Cmd::Server::stUserServerForwardServerCmd* ) buffer;
	constructInPlace( sendCmd );
	sendCmd->num = cmdLen;
	bcopy( strCmd,sendCmd->data,cmdLen );
	return m_superClient->sendCmd( buffer,sendCmd->size() );
#endif
}

bool SubNetService::addServerEntry(const ServerEntry &entry)
{
	bool findFlg = false;
	for(std::deque<ServerEntry>::iterator iter = m_serverList.begin();iter != m_serverList.end();++iter)
	{
		if((*iter).serverID == entry.serverID)
		{
			(*iter) = entry;
			findFlg = true;
			break;
		}
	}
	if(!findFlg)
	{
		m_serverList.push_back(entry);
	}
	return true;
}

const ServerEntry* SubNetService::getServerEntry(const DWORD serverID)
{
	const ServerEntry* entry = NULL;
	for(std::deque<ServerEntry>::iterator iter = m_serverList.begin();iter != m_serverList.end();++iter)
	{
		if((*iter).serverID == serverID)
		{
			entry = &(*iter);
			break;
		}
	}
	return entry;
}

