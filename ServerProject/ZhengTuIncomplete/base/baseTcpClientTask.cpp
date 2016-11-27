#include "baseTcpClientTask.h"
#include "baseFunc.h"
#include "common/nullCmd.h"
#include "baseTcpClient.h"
#include "baseSubService.h"

TcpClientTaskBase::TcpClientTaskBase(const std::string &ip,const DWORD port,const bool compress,const bool reConnect,const DWORD reConnectTimer) : m_pSocket(NULL),m_compress(compress),m_reConnect(reConnect),m_ip(ip),m_port(port),m_tickTimer(reConnectTimer,false,3600*1000L)
{
	m_lifeTime.now();
	m_state = CS_CLOSE;
	m_terminate = TM_NO;
	m_mainLoop = false;
	m_fdsradd = false;
	m_tick = false;
}
void TcpClientTaskBase::resetTickTimer(const QWORD howLong)
{
	Time timeVal;
	m_tickTimer.reset(howLong,timeVal);
}
bool TcpClientTaskBase::connect()
{
	SDWORD sock = ::socket(PF_INET,SOCK_STREAM,0);
	LogErrorCheckConditionOnly(sock != -1,false,"创建套接字失败%s,%d",m_ip.c_str(),m_port);
	
	socklen_t windowSize = 128*1024;
	SDWORD retcode = ::setsockopt(sock,SOL_SOCKET,SO_RCVBUF,&windowSize,sizeof(windowSize));
	if(retcode==-1)
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
	addr.sin_addr.s_addr = inet_addr(m_ip.c_str());
	addr.sin_port = htons(m_port);
	retcode = TEMP_FAILURE_RETRY(::connect(sock,(struct sockaddr*)&addr,sizeof(addr)));
	if(retcode == -1)
	{
		TEMP_FAILURE_RETRY(::close(sock));
		return false;
	}
	m_pSocket = new Socket(sock,&addr,m_compress);
	if(!m_pSocket)
	{
		TEMP_FAILURE_RETRY(::close(sock));
		return false;
	}
	LogInfoCheckConditionOnly( false,"创建到服务器%s,%u的连接成功",m_ip.c_str(),m_port);
	return true;
}

void TcpClientTaskBase::checkConnect()
{
	Time currentTime;
	if(m_tickTimer(currentTime))
	{
		if(checkTick())
		{
			terminate(TM_SOCK_ERROR);
			clearTick();
		}
		else
		{
			Cmd::ClientNullCmd cmd;
			if(sendCmd(&cmd,sizeof(cmd)))
			{
				setTick();
			}
		}
	}
}
bool TcpClientTaskBase::sendCmd(const void *cmd,const DWORD cmdLen)
{
	Cmd::NullCmd *nullCmd = (Cmd::NullCmd*)cmd;
	analysisSendingCmd(nullCmd->byCmd,nullCmd->byParam,cmdLen);
	switch(m_state)
	{
		case CS_CLOSE:
			CheckConditonReturn( m_pSocket,false );
			return m_pSocket->sendCmd(cmd,cmdLen);
			break;
		case CS_OKAY:
		case CS_RECYCLE:
			CheckConditonReturn( m_pSocket,false );
			return m_pSocket->sendCmd(cmd,cmdLen,true);
			break;
	}
	return false;
}
bool TcpClientTaskBase::sendLoginCmd()
{
	using namespace Cmd::Server;
	LoginStartServerCmd cmd;
	cmd.serverID = SubNetService::getInstance().getServerID();
	cmd.serverType = SubNetService::getInstance().getServerType();
	strncpy(cmd.ip,SubNetService::getInstance().getIP(),sizeof(cmd.ip));

	return sendCmd(&cmd,sizeof(cmd));
}
bool TcpClientTaskBase::listeningRecv(bool needRecv)
{
	SDWORD retcode = needRecv ? m_pSocket->recvToBufNoPoll() : 0;
	CheckConditonReturn(retcode!=-1,false);
	do
	{
		BYTE cmd[Socket::s_maxDataSize];
		DWORD cmdLen = m_pSocket->recvToCmdNoPoll(cmd);
		if(cmdLen == 0)
		{
			break;
		}
		Cmd::NullCmd *nullCmd = (Cmd::NullCmd*)cmd;
		if(nullCmd->byCmd == Cmd::CMD_NULL)
		{
			if(nullCmd->byParam == Cmd::SERVER_PARA_NULL)
			{
				if(!sendCmd(cmd,cmdLen))
				{
					return false;
				}
			}
			else if(Cmd::CLIENT_PARA_NULL == nullCmd->byParam)
			{
				clearTick();
			}
			else if(Cmd::ZIP_CMD_PARA_NULL == nullCmd->byParam)
			{
				parse(nullCmd,cmdLen);
			}
		}
		else
		{
			parse(nullCmd,cmdLen);
			analysisRecvingCmd(nullCmd->byCmd,nullCmd->byParam,cmdLen);
		}
	}while(true);
	return true;
}
bool TcpClientTaskBase::listeningSend()
{
	return m_pSocket ? m_pSocket->sync() : false;
}
void TcpClientTaskBase::onReconnect()
{
}
void TcpClientTaskBase::getNextState()
{
	ConnectState oldState = getState();
	m_lifeTime.now();
	switch(oldState)
	{
		case CS_CLOSE:
			setState(CS_SYNC);
			break;
		case CS_SYNC:
			addToContainer();
			setState(CS_OKAY);
			onReconnect();
			break;
		case CS_OKAY:
			removeFromContainer();
			setState(CS_RECYCLE);
			break;
		case CS_RECYCLE:
			if(m_terminate == TM_SERVER_CLOSE)
			{
				recycleConnect();
			}
			setState(CS_CLOSE);
			final();
			break;
	}
}
void TcpClientTaskBase::resetState()
{
	ConnectState oldState = getState();
	m_lifeTime.now();
	setState(CS_CLOSE);
	final();
}


