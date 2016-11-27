#include "plateTask.h"
#include "base/baseConstruct.h"
#include "plateTaskManager.h"
#include "base/baseSqlHandle.h"
#include "plateTimeTick.h"
#include "PlateServer.h"

bool PlateTask::s_analysisCmdFlg = false;

PlateTask::PlateTask(const SDWORD sock,const struct sockaddr_in *addr) : TcpTaskQueue(sock,addr),m_syncTimer(2*1000L),m_analysisSend("SuperTask指令发送统计"),m_analysisRecv("SuperTask指令接收统计")
{
	m_protocol = 0;
	m_buildTime = 0;
	m_svnVersion = 0;
	bzero(m_ip,sizeof(m_ip));
	m_port = 0;
	bzero(m_outIP,sizeof(m_outIP));
	m_outPort = 0;
	m_serverSize = 0;
	m_serverReturnSize = 0;
	m_hasNotifyOther = false;
	m_hasNotifyMe = false;
	m_hasNotifyMeReturn = false;
	m_recycleTime = 200;

	m_recycleState = RS_First;
	m_verify = false;
}

bool PlateTask::checkRecycle()
{
	CheckConditonReturn(m_recycleState != RS_First,false);
	if(m_recycleState == RS_Second)
	{
		m_recycleState = RS_Third;
	}
	return true;
}

bool PlateTask::verify(const DWORD serverType,const char *ip)
{
	MysqlHandle *handle = PlateServer::s_mySqlPool->getHandle();
	LogErrorCheckCondition(handle,false,"数据库句柄为空");
	
	std::ostringstream oss;
	Record where;
	strncpy(m_ip,ip,sizeof(m_ip));
	oss << "type=" << serverType;
	where.put("type",oss.str());
	oss.str("");
	std::string escapeIP;
	oss << "ip=" << handle->escapeString(ip,escapeIP) << "";
	where.put("ip",oss.str());
	RecordSet *recordSet = handle->exeSelect("SERVERLIST",NULL,&where);
	
	PlateServer::s_mySqlPool->putHandle(handle);	
	if(!recordSet || recordSet->empty())
	{
		DELETE(recordSet);
		return false;
	}

	size_t index = 0;
	while(index < recordSet->size())
	{
		if(PlateTaskManager::getInstance().uniqueVerify(recordSet->get(index)->getValue("id")))
		{
			id = recordSet->get(index)->getValue("id");
			m_taskType = recordSet->get(index)->getValue("type");
			strncpy(name,recordSet->get(index)->getValue("name"),sizeof(name));
			m_port = recordSet->get(index)->getValue("port");
			strncpy(m_outIP,recordSet->get(index)->getValue("outip"),sizeof(m_outIP));
			m_outPort = recordSet->get(index)->getValue("outport");
			break;
		}
		++index;
	}
	
	if(recordSet->size() == index)
	{
		DELETE(recordSet);
		return false;
	}
	DELETE(recordSet);

	using namespace Cmd::Server;
	ResponseStartServerCmd cmd;
	cmd.serverID = id;
	cmd.port = m_port;
	cmd.outPort = m_outPort;
	bcopy(m_outIP,cmd.outIp,sizeof(m_outIP));
	LogErrorCheckCondition(sendCmd(&cmd,sizeof(cmd)),false,"管理服务器连接验证发送消息失败");
	return true;
}

SDWORD PlateTask::verifyConnect()
{
	SDWORD ret = m_mSocket.recvToBufNoPoll();
	CheckConditonReturn(ret>0,ret);

	BYTE cmd[Socket::s_maxDataSize];
	LogErrorCheckCondition(m_mSocket.recvToCmdNoPoll(cmd),0,"管理服务器连接验证接收数据失败");
	using namespace Cmd::Server;
	RequestStartServerCmd *ptCmd = (RequestStartServerCmd*)cmd;
	if(ptCmd->byCmd == START_SERVERCMD && ptCmd->byParam == REQUEST_START_SERVERCMD_PARA)
	{
		if(verify(ptCmd->serverType,ptCmd->ip))
		{
			m_protocol = ptCmd->protocol;
			m_buildTime = ptCmd->buildTime;
			m_svnVersion = ptCmd->svnVersion;
			m_verify = true;
			Global::logger->info("客户端连接通过验证%s,%u",m_ip,m_port);
			return 1;
		}
	}
	Global::logger->error("客户端连接验证失败"); 
	return -1;
}

SDWORD PlateTask::waitSync()
{
	SDWORD retcode = m_mSocket.waitForRead();
	CheckConditonReturn(retcode != -1,retcode);
	if(retcode > 0)
	{
		retcode = m_mSocket.recvToBufNoPoll();
		CheckConditonReturn(retcode>0,retcode);
	}
	BYTE cmd[Socket::s_maxDataSize];
	DWORD cmdLen = m_mSocket.recvToCmdNoPoll(cmd);
	if(cmdLen > 0)
	{
		using namespace Cmd::Server;
		OkStartServerCmd *ptCmd = (OkStartServerCmd*)cmd;
		if(ptCmd->byCmd == START_SERVERCMD && ptCmd->byParam == OK_START_SERVERCMD_PARA && id == ptCmd->serverID)
		{
			sendCmd(ptCmd,sizeof(OkStartServerCmd));
			Global::logger->info("服务器连接同步成功%s,%u",m_ip,m_port);
			return 1;
		}
		return 0;
	}
	if(!m_hasNotifyOther && m_syncTimer(PlateTimeTick::s_currentTime) && PlateTaskManager::getInstance().checkDependence(getType()))
	{
		if(notifyOther())
		{
			m_hasNotifyOther = true;
		}
	}
	if(!m_hasNotifyMe && m_hasNotifyOther && notifyReturnOK())
	{
		m_hasNotifyMe = true;
		notifyMe();
	}
	return 0;
}

SDWORD PlateTask::recycleConnect()
{
	SDWORD ret = 1;
	CheckConditonReturn( m_verify,ret );
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

bool PlateTask::uniqueAdd()
{
	return PlateTaskManager::getInstance().addTask(this);
}

bool PlateTask::uniqueRemove()
{
	return PlateTaskManager::getInstance().uniqueRemove(this);
}

bool PlateTask::msgParseStart(const Cmd::NullCmd *cmd,const DWORD cmdLen)
{
	using namespace Cmd::Server;
	switch(cmd->byParam)
	{
		case NOTIFY_OTHER_SERVERCMD_PARA:
			{
				NotifyOtherServer *ptCmd = (NotifyOtherServer*)cmd;
				PlateTask *task = (PlateTask*)PlateTaskManager::getInstance().getTaskByID(ptCmd->entry.serverID);
				if(task)
				{
					task->notifyReturn();
				}
				return true;
			}
			break;
		case OK_START_RETURN_SERVERCMD_PARA:
			{
				m_hasNotifyMeReturn = true;
				return true;
			}
			break;
		default:
			Global::logger->error("管理器任务接受未处理消息%s,%u,%u,%u",__PRETTY_FUNCTION__,cmd->byCmd,cmd->byParam,cmdLen);
			break;
	}
	return false;
}

bool PlateTask::msgParseForward(const Cmd::NullCmd *cmd,const DWORD cmdLen)
{
	return false;
}

bool PlateTask::msgParse(const Cmd::NullCmd *cmd,const DWORD cmdLen)
{
	return true;
}

bool PlateTask::notifyOther()
{
	using namespace Cmd::Server;
	NotifyOtherServer cmd;
	bzero(&cmd.entry,sizeof(cmd.entry));
	cmd.entry.serverID = id;
	cmd.entry.serverType = getType();
	strncpy(cmd.entry.name,name,sizeof(name));
	strncpy(cmd.entry.ip,m_ip,sizeof(m_ip));
	cmd.entry.port = m_port;
	strncpy(cmd.entry.outNetIP,m_outIP,sizeof(m_outIP));
	cmd.entry.outNetPort = m_outPort;
	cmd.entry.state = m_state;
	
	struct CheckNotifyOtherExec : public EntryCallBack<PlateTask>
	{
		WORD type;
		CheckNotifyOtherExec(const WORD _type) : type(_type)
		{
		}
		bool exec(PlateTask *task)
		{
			if(task->getType() < type)
			{
				CheckConditonReturn(task->getState() == TcpTask::TTS_OKAY,false);
			}
			return true;
		}
	};
	CheckNotifyOtherExec exec(getType());

	CheckConditonReturn(PlateTaskManager::getInstance().execEveryTask(exec),false);
	
	struct NotifyOtherExec : public EntryCallBack<PlateTask>
	{
		const NotifyOtherServer *send;
		WORD type;
		DWORD count;
		NotifyOtherExec(const NotifyOtherServer *_send,const WORD _type) : send(_send),type(_type)
		{
			count = 0;
		}
		bool exec(PlateTask *task)
		{
			if(task->getType() < type)
			{
				CheckConditonReturn(task->getState() == TcpTask::TTS_OKAY,false);
				++count;
				task->sendCmd(send,sizeof(NotifyOtherServer));
			}
			else if(task->getType() != type && task->getState() == TcpTask::TTS_OKAY)
			{
				task->sendCmd(send,sizeof(NotifyOtherServer));
			}
			return true;
		}
	};
	NotifyOtherExec notifyExec(&cmd,getType());
	PlateTaskManager::getInstance().execEveryTask(notifyExec);
	m_serverSize = notifyExec.count;
	return true;
}

bool PlateTask::notifyMe()
{
	using namespace Cmd::Server;
	BYTE pBuffer[Socket::s_maxDataSize];
	NotifyMeServer *ptCmd = (NotifyMeServer*)pBuffer;
	constructInPlace(ptCmd);
	ptCmd->size = 0;

	struct NotifyMeExec : public EntryCallBack<PlateTask>
	{
		NotifyMeServer *send;
		WORD id;
		NotifyMeExec(NotifyMeServer *_send,const WORD _id) : send(_send),id(_id)
		{
		}
		bool exec(PlateTask *task)
		{
			if(task->getID() != id)
			{
				bzero(&send->entry[send->size],sizeof(send->entry[send->size]));
				send->entry[send->size].serverID = task->getID();
				send->entry[send->size].serverType = task->getType();
				strncpy(send->entry[send->size].name,task->name,sizeof(task->name));
				strncpy(send->entry[send->size].ip,task->m_ip,sizeof(task->m_ip));
				send->entry[send->size].port = task->m_port;
				strncpy(send->entry[send->size].outNetIP,task->m_outIP,sizeof(task->m_outIP));
				send->entry[send->size].outNetPort = task->m_outPort;
				send->entry[send->size].state = task->m_state;
				send->size += 1;
			}
			return true;
		}
	};
	NotifyMeExec exec(ptCmd,getID());
	PlateTaskManager::getInstance().execEveryTask(exec);
	return sendCmd(ptCmd,ptCmd->allSize());
}

void PlateTask::analysisSendingCmd(const BYTE cmd,const BYTE param,const DWORD cmdLen)
{
	CheckConditonVoid(s_analysisCmdFlg);
	if(s_analysisCmdFlg != m_analysisSend.getSwitch())
	{
		m_analysisSend.setSwitch(s_analysisCmdFlg);
	}
	m_analysisSend.addCmd(cmd,param,cmdLen);
}

void PlateTask::analysisRecvingCmd(const BYTE cmd,const BYTE param,const DWORD cmdLen)
{
	CheckConditonVoid(s_analysisCmdFlg);
	if(s_analysisCmdFlg != m_analysisRecv.getSwitch())
	{
		m_analysisRecv.setSwitch(s_analysisCmdFlg);
	}
	m_analysisRecv.addCmd(cmd,param,cmdLen);
}

void PlateTask::switchCmdAnalysis(const bool switchOn)
{
	s_analysisCmdFlg = switchOn;
}


