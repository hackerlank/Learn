#include "sessionClient.h"
#include "SceneServer.h"

SessionClient *sessionClient = NULL;

SessionClient::SessionClient(const std::string &name,const std::string &ip,const WORD port,const QWORD serverID) : TcpClientBufferQueue(name,ip,port,serverID),m_analysisSend("SessionClient指令发送统计"),m_analysisRecv("SessionClient指令接收统计")
{
}

bool SessionClient::connectToSessionServer()
{
	while(!SceneServer::getInstance().isTerminate())
	{
		if(TcpClientBase::connect(getIP(),getPort()))
		{
			break;
		}
		TcpClientBase::close();
		Thread::sleep(4);
	}
	return sendLoginCmd();
}

void SessionClient::run()
{
	while(!SceneServer::getInstance().isTerminate())
	{
		TcpClientBuffer::run();
		break;
	}
	SceneServer::getInstance().Terminate();
}

bool SessionClient::broadCmdToScene(const void *cmd,const DWORD cmdLen)
{
	return true;
}

void SessionClient::analysisSendingCmd(const BYTE cmd,const BYTE param,const DWORD cmdLen)
{
	m_analysisSend.addCmd(cmd,param,cmdLen);
}

void SessionClient::analysisRecvingCmd(const BYTE cmd,const BYTE param,const DWORD cmdLen)
{
	m_analysisRecv.addCmd(cmd,param,cmdLen);
}

void SessionClient::switchCmdAnalysis(const bool switchOn)
{
	m_analysisSend.setSwitch(switchOn);
	m_analysisRecv.setSwitch(switchOn);
}

bool SessionClient::msgParseStart(const Cmd::NullCmd *nullCmd,const DWORD cmdLen)
{
	switch(nullCmd->byParam)
	{
		default:
			break;
	}
	Global::logger->error("%s(%u,%u,%u)",__PRETTY_FUNCTION__,nullCmd->byCmd,nullCmd->byParam,cmdLen);
	return false;
}

bool SessionClient::msgParseForward(const Cmd::NullCmd *nullCmd,const DWORD cmdLen)
{
	return true;
}

bool SessionClient::msgParse(const Cmd::NullCmd *nullCmd,const DWORD cmdLen)
{
	CheckConditonReturn(nullCmd && cmdLen,false);
#if 0
	switch(nullCmd->byCmd)
	{
		case LOGIN_SESSIONCMD:
			{
				return SessionLoginMsgParse(nullCmd,cmdLen);
			}
	}
#endif
	return true;
}   

