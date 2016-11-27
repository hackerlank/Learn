#ifndef BASE_TCP_CLIENT_BUFFER_H
#define BASE_TCP_CLIENT_BUFFER_H

#include "baseTcpClient.h"

class TcpClientBuffer : public TcpClientBase
{
	public:
		TcpClientBuffer(const std::string &name,const std::string &ip = "127.0.0.1",const WORD port = 80,const WORD serverID = 0,const bool compress = false,const QWORD usleepTime = 50000L)
		:TcpClientBase(name,ip,port,serverID,compress),m_usleepTime(usleepTime),m_bufferFlg(false)
		{
		}

		virtual ~TcpClientBuffer()
		{
		}
		void close()
		{
			sync();
			TcpClientBase::close();
		}
		void setUsleepTime(const QWORD uSleepTime)
		{
			m_usleepTime = uSleepTime;
		}
		void run();
		virtual bool sendCmd(const void *strCmd,const DWORD cmdLen);
	private:
		bool listeningRecv();
		bool listeningSend();
		void sync();
	private:
		QWORD m_usleepTime;
		volatile bool m_bufferFlg;
};

class TcpClientBufferQueue : public TcpClientBuffer,public MessageQueue<false>
{
	public:
		TcpClientBufferQueue(const std::string name,const std::string &ip = "127.0.0.1",const WORD port = 80,const WORD serverID = 0,const bool compress = false,const DWORD usleepTime = 50000) : TcpClientBuffer(name,ip,port,serverID,compress,usleepTime)
		{
		}
		~TcpClientBufferQueue()
		{
		}
		
		bool parse(const Cmd::NullCmd *nullCmd,const DWORD cmdLen);
};

#endif
