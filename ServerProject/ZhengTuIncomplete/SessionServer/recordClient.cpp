#include "recordClient.h"
#include "SessionServer.h"

RecordClient *recordClient = NULL;

RecordClient::RecordClient(const std::string &name,const std::string &ip,const WORD port,const QWORD serverID) : TcpClientBufferQueue(name,ip,port,serverID),m_analysisSend("RecordClient指令发送统计"),m_analysisRecv("RecordClient指令接收统计")
{
}

bool RecordClient::connectToRecordServer()
{
	while(!SessionServer::getInstance().isTerminate())
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

void RecordClient::run()
{
	while(!SessionServer::getInstance().isTerminate())
	{
		TcpClientBuffer::run();
		break;
	}
	SessionServer::getInstance().Terminate();
}

bool RecordClient::broadCmdToScene(const void *cmd,const DWORD cmdLen)
{
	return true;
}

void RecordClient::analysisSendingCmd(const BYTE cmd,const BYTE param,const DWORD cmdLen)
{
	m_analysisSend.addCmd(cmd,param,cmdLen);
}

void RecordClient::analysisRecvingCmd(const BYTE cmd,const BYTE param,const DWORD cmdLen)
{
	m_analysisRecv.addCmd(cmd,param,cmdLen);
}

void RecordClient::switchCmdAnalysis(const bool switchOn)
{
	m_analysisSend.setSwitch(switchOn);
	m_analysisRecv.setSwitch(switchOn);
}

bool RecordClient::msgParseStart(const Cmd::NullCmd *nullCmd,const DWORD cmdLen)
{
	switch(nullCmd->byParam)
	{
		default:
			break;
	}
	Global::logger->error("%s(%u,%u,%u)",__PRETTY_FUNCTION__,nullCmd->byCmd,nullCmd->byParam,cmdLen);
	return false;
}

bool RecordClient::msgParseForward(const Cmd::NullCmd *nullCmd,const DWORD cmdLen)
{
	return true;
}

bool RecordClient::msgParse(const Cmd::NullCmd *nullCmd,const DWORD cmdLen)
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
