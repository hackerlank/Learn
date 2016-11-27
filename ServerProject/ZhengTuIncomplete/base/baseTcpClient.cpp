#include "baseTcpClient.h"
#include "baseSubService.h"

TcpClientBase::TcpClientBase(const std::string &name,const std::string &ip,const WORD port,const WORD serverID,const bool compress):Thread(name.c_str()),m_port(port),m_serverID(serverID),m_pSocket(NULL),m_compress(compress)
{
	strncpy(m_ip,ip.c_str(),ip.length());
}

TcpClientBase::~TcpClientBase()
{
	close();
}

bool TcpClientBase::connect()
{
	SDWORD sock = ::socket(PF_INET,SOCK_STREAM,0);
	LogErrorCheckCondition(sock != -1,false,"创建套接口失败%s,%u",m_ip,m_port);
	
	socklen_t windowSize = 128 * 1024;
	SDWORD retcode = ::setsockopt(sock,SOL_SOCKET,SO_RCVBUF,&windowSize,sizeof(windowSize));
	if(retcode == -1)
	{
		TEMP_FAILURE_RETRY(::close(sock));
		return false;
	}

	retcode = ::setsockopt(sock,SOL_SOCKET,SO_SNDBUF,&windowSize,sizeof(windowSize));
	if(retcode == -1)
	{
		TEMP_FAILURE_RETRY(::close(sock));
		return false;
	}

	struct sockaddr_in addr;
	bzero(&addr,sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(m_ip);
	addr.sin_port = htons(m_port);
	retcode = TEMP_FAILURE_RETRY(::connect(sock,(struct sockaddr *)&addr,sizeof(addr)));
	if(retcode == -1)
	{
		Global::logger->error("创建到服务器%s,%u的连接失败",m_ip,m_port);
		TEMP_FAILURE_RETRY(::close(sock));
		return false;
	}
	m_pSocket = new Socket(sock,&addr,m_compress);
	if(!m_pSocket)
	{
		Global::logger->fatal("创建Socket实例失败,内存不够%s,%u",m_ip,m_port);
		TEMP_FAILURE_RETRY(::close(sock));
		return false;
	}

	LogInfoCheckConditionOnly(false,"创建到服务器%s,%u的连接成功",m_ip,m_port);
	return true;
}
bool TcpClientBase::sendCmd(const void *strCmd,const DWORD cmdLen)
{
	LogErrorCheckConditionOnly(m_pSocket,false,"服务器连接套接字为空%s,%u",m_ip,m_port);
	
	Cmd::NullCmd *nullCmd = (Cmd::NullCmd*)strCmd;
	analysisSendingCmd(nullCmd->byCmd,nullCmd->byParam,cmdLen);
	return m_pSocket->sendCmd(strCmd,cmdLen);
}

bool TcpClientBase::sendLoginCmd()
{
	using namespace Cmd::Server;
	LoginStartServerCmd cmd;
	cmd.serverID = SubNetService::getInstance().getServerID();
	cmd.serverType = SubNetService::getInstance().getServerType();
	strncpy(cmd.ip,SubNetService::getInstance().getIP(),sizeof(cmd.ip));
	
	return sendCmd(&cmd,sizeof(cmd));
}

bool TcpClientBase::reConnect(const char *ip,const WORD port)
{
	while(true)
	{
		if(connect(ip,port))
		{
			if(sendLoginCmd())
			{
				return true;
			}
		}
		close();
		Thread::sleep(4);
	}
	return false;
}
void TcpClientBase::run()
{
	while(!isFinal())
	{
		setRuning();
		BYTE strCmd[Socket::s_maxDataSize];
		bzero( strCmd,Socket::s_maxDataSize);
		int cmdLen = m_pSocket->recvToCmd( strCmd,false );
		if( cmdLen > 0 )
		{
			Cmd::NullCmd *nullCmd = ( Cmd::NullCmd* )strCmd;
			if( Cmd::CMD_NULL == nullCmd->byCmd )
			{
				if( Cmd::SERVER_PARA_NULL == nullCmd->byParam )
				{
					if( !sendCmd( strCmd,cmdLen ) )
					{
						if( m_reconnect )
						{
							break;
						}
						else
						{
							break;
						}
					}
				}
			#if 0
				else if( Cmd::CLIENT_PARA_NULL == nullCmd->byParam )
				{
				}
			#endif
			}
			else
			{
				parse( nullCmd,cmdLen );
			}
		}
		else if( cmdLen == -1 )
		{
			if( m_reconnect )
			{
				break;
			}
			else
			{
				break;
			}
		}
	}
}

		
	
