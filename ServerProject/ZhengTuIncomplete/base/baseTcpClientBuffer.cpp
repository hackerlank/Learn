#include "baseTcpClientBuffer.h"

bool TcpClientBuffer::listeningSend()
{
	if(!m_pSocket)
	{
		return false;
	}
	return m_pSocket->sync();
}

bool TcpClientBuffer::listeningRecv()
{
	SDWORD retcode = m_pSocket->recvToBufNoPoll();
	CheckConditonReturn(retcode!=-1,false);
	do
	{
		BYTE cmd[Socket::s_maxDataSize];
		DWORD cmdLen = m_pSocket->recvToCmdNoPoll(cmd);
		CheckConditonReturn(cmdLen,true);
		using namespace Cmd;	
		NullCmd *nullCmd = (NullCmd*)cmd;
		if(CMD_NULL == nullCmd->byCmd)
		{
			if(SERVER_PARA_NULL == nullCmd->byParam)
			{
				LogErrorCheckCondition(sendCmd(nullCmd,sizeof(*nullCmd)),true,"管理服务器客户端发送信号数据失败%s,%u",m_ip,m_port);
			}
			else if(CLIENT_PARA_NULL == nullCmd->byParam)
			{
			}
		}
		else
		{
			parse(nullCmd,cmdLen);
			analysisRecvingCmd( nullCmd->byCmd,nullCmd->byParam,cmdLen );
		}
	}while( true );
	return true;
}


void TcpClientBuffer::sync()
{
	if(m_pSocket)
	{
		m_pSocket->forceSync();
	}
}

bool TcpClientBuffer::sendCmd(const void *cmd,const DWORD cmdLen)
{
	LogErrorCheckCondition(m_pSocket,false,"套接字发送消息失败套接子为空");
	
	Cmd::NullCmd *nullCmd = (Cmd::NullCmd*)cmd;
	analysisSendingCmd(nullCmd->byCmd,nullCmd->byParam,cmdLen);
	return m_pSocket->sendCmd(cmd,cmdLen,m_bufferFlg);
}

void TcpClientBuffer::run()
{
	m_bufferFlg = true;
	struct pollfd pfds;
	struct pollfd pfds_r;
	m_pSocket->fillPollFd(pfds,POLLIN|POLLOUT|POLLERR|POLLPRI);
	m_pSocket->fillPollFd(pfds_r,POLLIN|POLLOUT|POLLERR|POLLPRI);
	QWORD sleepTime = m_usleepTime;
	while(!isFinal())
	{
		setRuning();
		struct timespec beginTv,endTv;
		clock_gettime(CLOCK_REALTIME,&beginTv);
		if(TEMP_FAILURE_RETRY(::poll(&pfds_r,1,sleepTime/1000L)) > 0)
		{
			if(pfds_r.revents & POLLERR)
			{
				break;
			}
			if(pfds_r.revents & POLLIN)
			{
				if(!listeningRecv())
				{
					break;
				}
			}
			if(pfds_r.revents & POLLOUT)
			{
				if(!listeningSend())
				{
					break;
				}
			}
		}
		clock_gettime(CLOCK_REALTIME,&endTv);
		QWORD endTime = endTv.tv_sec*1000000L + endTv.tv_nsec/1000L;
		QWORD beginTime = beginTv.tv_sec*1000000L + beginTv.tv_nsec/1000L;
		sleepTime -= (endTime - beginTime);
		if(sleepTime <= 0)
		{
			if(TEMP_FAILURE_RETRY(::poll(&pfds,1,0) > 0) > 0)
			{
				if(pfds.revents & POLLERR)
				{
					break;
				}
				if(pfds.revents & POLLIN)
				{
					if(!listeningRecv())
					{
						break;
					}
				}
				if(pfds.revents & POLLOUT)
				{
					if(!listeningSend())
					{
						break;
					}
				}
			}
			sleepTime = m_usleepTime;
		}
	}
	sync();
	m_bufferFlg = false;
}

bool TcpClientBufferQueue::parse(const Cmd::NullCmd *nullCmd,const DWORD cmdLen)
{
	return cmdMsgParse(nullCmd,cmdLen);
}


