#include "baseSuperClient.h"

SuperClient::SuperClient():TcpClientBufferQueue("服务器管理器客户端"),m_verify(false)
{
}

SuperClient::~SuperClient()
{
}

void SuperClient::run()
{
	TcpClientBuffer::run();
#if 0
	SubNetService::getInstance().Terminate();
#endif
}

bool SuperClient::msgParseStart(const Cmd::NullCmd *nullCmd,const DWORD cmdLen)
{
	Global::logger->debug("superclient accept msg%u,%u",nullCmd->byCmd,nullCmd->byParam);
	using namespace Cmd::Server;
	switch(nullCmd->byParam)
	{
		case RESPONSE_START_SERVERCMD_PARA:
			{
				ResponseStartServerCmd *cmd = (ResponseStartServerCmd*)nullCmd;
				SubNetService::getInstance().setServerInfo(cmd);
				return true;
			}
			break;
		case NOTIFY_ME_SERVERCMD_PARA:
			{
				NotifyMeServer *cmd = (NotifyMeServer*)nullCmd;
				for(size_t index = 0;index < cmd->size;++index)
				{
					SubNetService::getInstance().addServerEntry(cmd->entry[index]);
				}
				m_verify = true;
				return true;
			}
			break;
		case NOTIFY_OTHER_SERVERCMD_PARA:
			{
				NotifyOtherServer *cmd = (NotifyOtherServer*)nullCmd;
				if(SubNetService::getInstance().addServerEntry(cmd->entry))
				{
					if(SubNetService::getInstance().getServerType() < cmd->entry.serverType)
					{
						return sendCmd(cmd,cmdLen);
					}
					return true;
				}
			}
			break;
		case OK_START_SERVERCMD_PARA:
			{
				SubNetService::getInstance().startUpOver();
				return true;
			}
			break;
	#if 0
		case SHUTDOWN_START_SERVERCMD_PARA:
			{
				SubNetService::getInstance().TerminateWait();
				return true;
			}
			break;
		case RELOAD_TABLE_SERVERCMD_PARA:
			{
				stReloadTableStartServerCmd *rev = (stReloadTableStartServerCmd*)nullCmd;
				if(reloadDBManager(rev->name))
				{
				}
				return true;
			}
			break;
	#endif
		default:
			break;
	}
	return false;
}

bool SuperClient::msgParseForward(const Cmd::NullCmd *nullCmd,const DWORD cmdLen)
{
	using namespace Cmd::Server;
	LogCheckCondition(SubNetService::getInstance().m_startUp,false,"服务器还没有启动");
#if 0
	switch(nullCmd->byParam)
	{
		case FL_SERVER_FORWARD_SERVERCMD:
			{
				stFLServerForwardServerCmd *rev = (stFLServerForwardServerCmd*)nullCmd;
				SubNetService::getInstance().msgParse_FLServer((Cmd::NullCmd*)rev->data,rev->dataSize);
				return true;
			}
			break;
		case MONITOR_SERVER_FORWARD_SERVERCMD:
			{
				stMonitorServerForwardServerCmd *rev = (stMonitorServerForwardServerCmd*)nullCmd;
				SubNetService::getInstance().msgParse_MonitorServer((Cmd::NullCmd*)rev->data,rev->dataSize);
				return true;
			}
			break;
		case NAME_SERVER_FORWARD_SERVERCMD:
			{
				stNameServerForwardServerCmd *rev = (stNameServerForwardServerCmd*)nullCmd;
				SubNetService::getInstance().msgParse_NameServer((Cmd::NullCmd*)rev->data,rev->dataSize);
				return true;
			}
			break;
		case USER_SERVER_FORWARD_SERVERCMD:
			{
				stUserServerForwardServerCmd *rev = (stUserServerForwardServerCmd*)nullCmd;
				SubNetService::getInstance().msgParse_UserServer((Cmd::NullCmd*)rev->data,rev->dataSize);
				return true;
			}
			break;
		case SHARE_FORWARD_SERVERCMD:
			{
				stShareForwardServerCmd *rev = (stShareForwardServerCmd*)nullCmd;
				SubNetService::getInstance().msgParseLogin((Cmd::NullCmd*)rev->data,rev->dataSize);
				return true;
			}
			break;
		case INFO_SERVER_FORWARD_SERVERCMD:
			{
				stInfoServerForwardServerCmd *rev = (stInfoServerForwardServerCmd*)nullCmd;
				SubNetService::getInstance().msgParse_InfoServer((Cmd::NullCmd*)rev->data,rev->dataSize);
				return true;
			}
			break;
		case ROLE_SERVER_FORWARD_SERVERCMD:
			{
				stRoleServerForwardServerCmd *rev = (stRoleServerForwardServerCmd*)nullCmd;
				SubNetService::getInstance().msgParse_RoleServer(Cmd::NullCmd*)rev->data,rev->dataSize);
				return true;
			}
			break;
		default:
			{
				SubNetService::getInstance().msgParse_SuperService(nullCmd,cmdLen);
				return true;
			}
			break;
	}
#endif
	return false;
}

bool SuperClient::msgParse(const Cmd::NullCmd *nullCmd,const DWORD cmdLen)
{
#if 0
	if(!SubNetService::getInstance().startup)
	{
		return false;
	}
	return SubNetService::getInstance().msgParse_SuperService(nullCmd,cmdLen);
#endif
}


		


