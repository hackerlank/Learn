#ifndef BASE_TCP_CLIENT_TASK_H
#define BASE_TCP_CLIENT_TASK_H

#include "baseTime.h"
#include "baseEntry.h"
#include "baseSocket.h"

class TcpClientTaskBase : public Entry
{
	public:
		enum TerminateMethod
		{
			TM_NO,
			TM_SOCK_ERROR,
			TM_SERVER_CLOSE,
		};
		enum ConnectState
		{
			CS_CLOSE = 0,
			CS_SYNC = 1,
			CS_OKAY = 2,
			CS_RECYCLE = 3,
		};
		TcpClientTaskBase(const std::string &ip,const DWORD port,const bool compress = false,const bool reConnect = true,const DWORD reConnTimer = 60*1000L);
		virtual ~TcpClientTaskBase()
		{
			final();
		}
		void final()
		{
			DELETE (m_pSocket );
			m_terminate = TM_NO;
			m_mainLoop = false;
		}
		bool isTerminate() const
		{
			return TM_NO != m_terminate;
		}
		void terminate(const TerminateMethod method )
		{
			m_terminate = method;
		}
		bool checkFirstMainLoop()
		{
			CheckConditonReturn(!m_mainLoop,false);
			m_mainLoop = true;
			return true;
		}
		const ConnectState getState() const
		{
			return m_state;
		}
		void setState(const ConnectState state)
		{
			this->m_state = state;
		}
		bool isOkay() const
		{
			return getState() == CS_OKAY;
		}
		const DWORD getID() const
		{
			return id;
		}
		const DWORD getType() const
		{
			return m_taskType;
		}
		const char* getStateString(const ConnectState state)
		{
			const char *retval = NULL;
			switch(m_state)
			{
				case CS_CLOSE:
					retval = "close";
					break;
				case CS_SYNC:
					retval = "sync";
					break;
				case CS_OKAY:
					retval = "okay";
					break;
				case CS_RECYCLE:
					retval = "recycle";
					break;
			}
			return retval;
		}
		void addEpoll(const SDWORD kdpfd,const DWORD events,void *ptr)
		{
			if(m_pSocket)
			{
				m_pSocket->addEpoll(kdpfd,events,ptr);
			}
		}
		void delEpoll(const SDWORD kdpfd,const DWORD events)
		{
			if(m_pSocket)
			{
				m_pSocket->delEpoll(kdpfd,events);
			}
		}
		bool checkStateTimeOut(const ConnectState state,const Time &timeVal,const DWORD timeout)
		{
			if(state == this->m_state)
			{
				if(m_lifeTime.elapse(timeVal) >= timeout*1000L)
				{
					m_lifeTime = timeVal;
					return true;
				}
			}
			return false;
		}
		virtual SDWORD checkRebound()
		{
			return 1;
		}
		virtual void recycleConnect()
		{
		}
		virtual void addToContainer()
		{
		}
		virtual void removeFromContainer()
		{
		}
		virtual bool connect();
		void checkConnect();
		bool sendCmd(const void *cmd,const DWORD cmdLen);
		virtual bool sendLoginCmd();
		bool listeningRecv(bool needRecv);
		bool listeningSend();
		void getNextState();
		void resetState();
		bool needReConnect()
		{
			return m_reConnect;
		}
		const WORD getPort() const
		{
			return m_pSocket->getPort();
		}
		const char* getIP() const
		{
			return m_pSocket->getIP();
		}
		const DWORD getAddr() const
		{
			return m_pSocket->getAddr();
		}
		bool isFdsrAdd()
		{
			return m_fdsradd;
		}
		bool fdsrAdd(bool flg=true)
		{
			m_fdsradd = flg;
			return m_fdsradd;
		}
		virtual bool parse(const Cmd::NullCmd *cmd,const DWORD cmdLen) = 0;
		virtual void onReconnect();
	protected:
		DWORD m_taskType;
		Socket *m_pSocket;
		volatile ConnectState m_state;
		bool checkTick() const
		{
			return m_tick;
		}
		void clearTick()
		{
			m_tick = false;
		}
		void setTick()
		{
			m_tick = true;
		}
		void resetTickTimer(const QWORD howLong);
	private:
		bool m_fdsradd;
		const bool m_compress;
		const bool m_reConnect;
		const std::string m_ip;
		const DWORD m_port;
		Time m_lifeTime;
		TerminateMethod m_terminate;
		volatile bool m_mainLoop;
		Timer m_tickTimer;
		bool m_tick;
	private:
		virtual void analysisSendingCmd(const BYTE cmd,const BYTE param,const DWORD cmdLen) {};
		virtual void analysisRecvingCmd(const BYTE cmd,const BYTE param,const DWORD cmdLen) {};

};

#endif

