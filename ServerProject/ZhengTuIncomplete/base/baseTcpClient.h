#ifndef BASE_TCP_CLIENT_H
#define BASE_TCP_CLIENT_H

#include "baseSocket.h"
#include "baseThread.h"

class TcpClientBase : public Thread
{
	public:
		TcpClientBase(const std::string &name,const std::string &ip = "127.0.0.1",const WORD port = 80,const WORD serverID = 0,const bool compresess = false);
		virtual ~TcpClientBase();
		bool connect();
		bool connect(const char *ip,const WORD port)
		{
			if(ip)
			{
				strncpy(m_ip,ip,sizeof(m_ip));
			}
			m_port = port;
			return connect();
		}
		bool reConnect(const char *ip,const WORD port);
		virtual bool sendLoginCmd();
		virtual void close()
		{
			DELETE(m_pSocket);
		}
		virtual bool sendCmd(const void *pstrCmd,const DWORD cmdLen);
		void setIP(const char *ip) 
		{
			if(ip)
			{
				strncpy(m_ip,ip,sizeof(m_ip));
			}
		}

		const char *getIP() const
		{
			return m_ip;
		}
		void setPort(const WORD port)
		{
			m_port = port;
		}
		const WORD getPort() const
		{
			return m_port;
		}
		void setReConnect(bool connectFlg)
		{
			m_reconnect = connectFlg;
		}
		virtual bool parse(const Cmd::NullCmd *ptNullCmd,const DWORD cmdLen) = 0;
		virtual void run();
		DWORD getServerID()
		{
			return m_serverID;
		}
	protected:
		char m_ip[MAX_IP_LENGTH];
		WORD m_port;
		DWORD m_serverID;
		Socket *m_pSocket;
		const bool m_compress;
		bool m_reconnect;
	protected:
		virtual void analysisSendingCmd(const BYTE cmd,const BYTE param,const DWORD cmdLen) {};
		virtual void analysisRecvingCmd(const BYTE cmd,const BYTE param,const DWORD cmdLen) {};
};

#endif
			
