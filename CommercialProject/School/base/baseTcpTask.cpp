#include "baseTcpTask.h"
#include "common/nullCmd.h"
#include "baseSubService.h"

bool TcpTask::listeningSend()
{
	return m_mSocket.sync();
}
void TcpTask::getNextState()
{
	TcpTask_State old_state = getState();
	switch(old_state)
	{
		case TTS_NOTUSE:
			setState(TTS_VERIFY);
			break;
		case TTS_VERIFY:
			setState(TTS_SYNC);
			break;
		case TTS_SYNC:
			m_buffered = true;
			addToContainer();
			setState(TTS_OKAY);
			break;
		case TTS_OKAY:
			removeFromContainer();
			setState(TTS_RECYCLE);
			break;
		case TTS_RECYCLE:
			setState(TTS_NOTUSE);
			break;
	}
}
void TcpTask::resetState()
{
	TcpTask_State old_state = getState();
	switch(old_state)
	{
		case TTS_NOTUSE:
		case TTS_RECYCLE: 
			break;
		case TTS_VERIFY:
		case TTS_SYNC:
		case TTS_OKAY:
			break;
	}
	setState(TTS_RECYCLE);
}
void TcpTask::checkSignal(const Time &timeVal)
{
	if(ifCheckSignal() && checkInterval(timeVal))
	{
		if(checkTick())
		{
			Terminate(TM_ACTIVE);
		}
		else
		{
			Cmd::ServerNullCmd cmd;
			if(sendCmd(&cmd,sizeof(cmd)))
			{
				Global::logger->debug("send the signal");
				setTick();
			}
		}
	}
}
TcpTask::TcpTask(const SWORD sock,const struct sockaddr_in *addr,const bool compress):m_taskType(0),m_buffered(false),m_mSocket(sock,addr,compress),m_state(TTS_NOTUSE),m_terminate(TM_NO),m_terminateWait(false),m_fdsradd(false),m_lifeTime(),m_uniqueVerified(false),m_checkSignal(true),m_tickTimer(3600*1000L),m_tick(false),m_checkTimeout(true)
{
	m_verifyState = 0;
}
bool TcpTask::sendCmd(const void *cmd,const DWORD cmdLen)
{
	Cmd::NullCmd *nullCmd = (Cmd::NullCmd*)cmd;
	analysisSendingCmd(nullCmd->byCmd,nullCmd->byParam,cmdLen);
	return m_mSocket.sendCmd(cmd,cmdLen,m_buffered);
}
bool TcpTask::sendCmdNoPack(const void *cmd,const DWORD cmdLen)
{
	return m_mSocket.sendCmdNoPack(cmd,cmdLen,m_buffered);
}
SDWORD TcpTask::verifyConnect()
{
	SWORD ret = m_mSocket.recvToBufNoPoll();
	CheckConditonReturn(ret > 0,ret);
	
	BYTE acceptCmd[Socket::s_maxDataSize];
	DWORD cmdLen = m_mSocket.recvToCmdNoPoll(acceptCmd);
	CheckConditonReturn(cmdLen,0);
	msgParseStart((Cmd::NullCmd*)acceptCmd,cmdLen);
	return m_verifyState;
}

bool TcpTask::verifyLogin(const Cmd::Server::LoginStartServerCmd *ptCmd)
{
	m_verifyState = -1;
	
	const ServerEntry *entry = SubNetService::getInstance().getServerEntry(ptCmd->serverID);
	LogErrorCheckCondition(entry,false,"连接登录认证失败找不到对应的服务器");
	
	LogErrorCheckCondition(ptCmd->serverType==entry->serverType && !strcmp(ptCmd->ip,entry->ip),false,"连接登录认证失败服务器信息错误%s,%u",ptCmd->serverType,ptCmd->ip);
	
	id = ptCmd->serverID;
	m_taskType = ptCmd->serverType;
	strncpy(name,getServerTypeString((ServerType)ptCmd->serverType),sizeof(name));
	
	m_verifyState = 1;
	return true;
}

bool TcpTask::listeningRecv(bool needRecv)
{
	SWORD ret = needRecv ? m_mSocket.recvToBufNoPoll() : 0;
	CheckConditonReturn(ret != -1,false);
	
	do
	{
		BYTE cmd[Socket::s_maxDataSize];
		DWORD cmdLen = m_mSocket.recvToCmdNoPoll(cmd);
		CheckConditonReturn(cmdLen,true);
		using namespace Cmd;
		NullCmd *nullCmd = (NullCmd*)cmd;
		if(CMD_NULL == nullCmd->byCmd)
		{
			if(SERVER_PARA_NULL == nullCmd->byParam)
			{
				clearTick();
			}
			else if(CLIENT_PARA_NULL == nullCmd->byParam)
			{
				sendCmd(nullCmd,cmdLen);
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

#if 0
bool TcpTaskNoQueue::parse(const Cmd::NullCmd *ptNullCmd,const DWORD cmdLen)
{
	switch(ptNullCmd->byCmd)
	{
		case Cmd::Server::START_SERVERCMD:
			{
				return msgParseStart(ptNull,cmdLen);
			}
			break;
		case Cmd::Server::FORWARD_SERVERCMD:
			{
				return msgParseForward(ptNull.cmdLen);
			}
			break;
		default:
			{
				return msgParse(ptNull,cmdLen);
			}
			break;
	}
	rturn true;
}

#endif

