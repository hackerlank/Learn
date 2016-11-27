#include "plateClient.h"
#include "SuperServer.h"

PlateClient *plateClient = NULL;

PlateClient::PlateClient(const std::string &name,const std::string &ip,const WORD port,const QWORD serverID) : TcpClientBufferQueue(name,ip,port,serverID),m_analysisSend("RecordClient指令发送统计"),m_analysisRecv("RecordClient指令接收统计")
{
}

bool PlateClient::connectToPlateServer()
{
	while(!SuperServer::getInstance().isTerminate())
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

void PlateClient::run()
{
	while(!SuperServer::getInstance().isTerminate())
	{
		TcpClientBuffer::run();
		break;
	}
	SuperServer::getInstance().Terminate();
}

bool PlateClient::broadCmdToScene(const void *cmd,const DWORD cmdLen)
{
	return true;
}

void PlateClient::analysisSendingCmd(const BYTE cmd,const BYTE param,const DWORD cmdLen)
{
	m_analysisSend.addCmd(cmd,param,cmdLen);
}

void PlateClient::analysisRecvingCmd(const BYTE cmd,const BYTE param,const DWORD cmdLen)
{
	m_analysisRecv.addCmd(cmd,param,cmdLen);
}

void PlateClient::switchCmdAnalysis(const bool switchOn)
{
	m_analysisSend.setSwitch(switchOn);
	m_analysisRecv.setSwitch(switchOn);
}

bool PlateClient::msgParseStart(const Cmd::NullCmd *nullCmd,const DWORD cmdLen)
{
	switch(nullCmd->byParam)
	{
		default:
			break;
	}
	Global::logger->error("%s(%u,%u,%u)",__PRETTY_FUNCTION__,nullCmd->byCmd,nullCmd->byParam,cmdLen);
	return false;
}

bool PlateClient::msgParseForward(const Cmd::NullCmd *nullCmd,const DWORD cmdLen)
{
	return true;
}

bool PlateClient::msgParse(const Cmd::NullCmd *nullCmd,const DWORD cmdLen)
{
	return true;
}   

