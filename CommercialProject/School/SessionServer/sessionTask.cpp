#include "sessionTask.h"
#include "base/baseConstruct.h"
#include "base/baseSqlHandle.h"
#include "sessionTimeTick.h"
#include "SessionServer.h"
#include "sessionTaskManager.h"

 bool SessionTask::s_analysisCmdFlg = false;

SessionTask::SessionTask(const SDWORD sock,const struct sockaddr_in *addr) : TcpTaskQueue(sock,addr),m_analysisSend("SessionTask指令发送统计"),m_analysisRecv("SessionTask指令接收统计")
{
	m_recycleTime = 200;
	m_recycleState = RS_First;
	m_verify = false;
}

bool SessionTask::checkRecycle()
{
	CheckConditonReturn(m_recycleState != RS_First,false);
	if(m_recycleState == RS_Second)
	{
		m_recycleState = RS_Third;
	}
	return true;
}

SDWORD SessionTask::verifyConnect()
{
	SDWORD ret = m_mSocket.recvToBufNoPoll();
	CheckConditonReturn(ret > 0,ret);

	BYTE cmd[Socket::s_maxDataSize];
	LogErrorCheckCondition(m_mSocket.recvToCmdNoPoll(cmd),0,"会话服务器连接验证接收数据失败");
	
	using namespace Cmd::Server;
	LoginStartServerCmd*ptCmd = (LoginStartServerCmd*)cmd;
	if(ptCmd->byCmd == START_SERVERCMD && ptCmd->byParam == LOGIN_START_SERVERCMD_PARA)
	{
		if(verifyLogin(ptCmd))
		{
			m_verify = true;
			Global::logger->info("会话服务器客户端连接通过验证%u,%u",id,m_taskType);
			return 1;
		}
	}
	Global::logger->error("会话服务器客户端连接验证失败"); 
	return -1;
}

SDWORD SessionTask::waitSync()
{
	return 1;
}

SDWORD SessionTask::recycleConnect()
{
	SDWORD ret = 1;
	CheckConditonReturn(m_verify,ret);
	switch(m_recycleState)
	{
		case RS_First:
			{
				m_recycleState = RS_First;
				ret = 0;
			}
			break;
		case RS_Second:
			{
				ret = 0;
			}
			break;
		case RS_Third:
			break;
	}
	return ret;
}

bool SessionTask::uniqueAdd()
{
	return SessionTaskManager::getInstance().addTask(this);
}

bool SessionTask::uniqueRemove()
{
	return SessionTaskManager::getInstance().uniqueRemove(this);
}

bool SessionTask::msgParseStart(const Cmd::NullCmd *cmd,const DWORD cmdLen)
{
	return true;
}

bool SessionTask::msgParseForward(const Cmd::NullCmd *cmd,const DWORD cmdLen)
{
	return false;
}

bool SessionTask::msgParse(const Cmd::NullCmd *cmd,const DWORD cmdLen)
{
	return true;
}

void SessionTask::analysisSendingCmd(const BYTE cmd,const BYTE param,const DWORD cmdLen)
{
	CheckConditonVoid(s_analysisCmdFlg);
	if(s_analysisCmdFlg != m_analysisSend.getSwitch())
	{
		m_analysisSend.setSwitch(s_analysisCmdFlg);
	}
	m_analysisSend.addCmd(cmd,param,cmdLen);
}

void SessionTask::analysisRecvingCmd(const BYTE cmd,const BYTE param,const DWORD cmdLen)
{
	CheckConditonVoid(s_analysisCmdFlg);
	if(s_analysisCmdFlg != m_analysisRecv.getSwitch())
	{
		m_analysisRecv.setSwitch(s_analysisCmdFlg);
	}
	m_analysisRecv.addCmd(cmd,param,cmdLen);
}

void SessionTask::switchCmdAnalysis(const bool switchOn)
{
	s_analysisCmdFlg = switchOn;
}


