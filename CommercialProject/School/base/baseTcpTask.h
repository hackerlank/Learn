#ifndef BASE_TCP_TASK_H
#define BASE_TCP_TASK_H

#include "baseSocket.h"
#include "baseEntry.h"
#include "baseTime.h"

class TcpTask : public Entry,public MessageQueue<false>
{
	public:
		enum TerminateMethod
		{
			TM_NO,
			TM_ACTIVE,
			TM_PASSIVE,
		};
		enum TcpTask_State
		{
			TTS_NOTUSE = 0,
			TTS_VERIFY = 1,
			TTS_SYNC = 2,
			TTS_OKAY = 3,
			TTS_RECYCLE = 4,
		};
		TcpTask(const SWORD sock,const struct sockaddr_in *addr = NULL,const bool compress = false);
		virtual ~TcpTask()
		{
		}
		void addEpoll(SWORD kdpfd,__uint32_t events,void *ptr)
		{
			m_mSocket.addEpoll(kdpfd,events,ptr);
		}
		void delEpoll(SWORD kdpfd,__uint32_t events)
		{
			m_mSocket.delEpoll(kdpfd,events);
		}
		bool checkVerifyTimeout(const Time &timeVal,const QWORD interval = 4000L) const
		{
			return m_checkTimeout ? m_lifeTime.elapse(timeVal) > interval : false ;
		}
		bool isFdsrAdd() const
		{
			return m_fdsradd;
		}
		bool fdsrAdd()
		{
			m_fdsradd = true;
			return m_fdsradd;
		}
		bool verifyLogin(const Cmd::Server::LoginStartServerCmd *ptCmd);
		virtual SDWORD verifyConnect();
		virtual SDWORD waitSync()
		{
			return 1;
		}

		virtual SWORD recycleConn()
		{
			return 1;
		}
		virtual void addToContainer()
		{
		}
		virtual void removeFromContainer()
		{
		}
		virtual bool uniqueAdd()
		{
			return true;
		}
		virtual bool uniqueRemove()
		{
			return true;
		}
		void setUnique()
		{
			m_uniqueVerified = true;
		}
		bool isUnique() const
		{
			return m_uniqueVerified;
		}
		bool isTerminateWait()
		{
			return m_terminateWait;
		}
		void terminaterWait()
		{
			m_terminateWait = true;
		}
		bool isTerminate() const
		{
			return TM_NO != m_terminate;
		}
		virtual void Terminate(const TerminateMethod method = TM_PASSIVE)
		{
			m_terminate = method;
		}
		virtual bool TerminateError()
		{
			return true;
		}
		virtual bool parse(const Cmd::NullCmd *nullCmd,const DWORD cmdLen) = 0;
		virtual bool sendCmd(const void *cmd,const DWORD cmdLen);
		bool sendCmdNoPack(const void *cmd,const DWORD cmdLen);
		virtual bool listeningRecv(bool needRecv);
		virtual bool listeningSend();
		const TcpTask_State getState() const
		{
			return m_state;
		}
		void setState(const TcpTask_State state)
		{
			this->m_state = state;
		}
		void getNextState();
		void resetState();
		const char* getStateString(const TcpTask_State state) const
		{
			const char *retval = NULL;
			switch(m_state)
			{
				case TTS_NOTUSE:
					retval = "notuse";
					break;
				case TTS_VERIFY:
					retval = "verify";
					break;
				case TTS_SYNC:
					retval = "sync";
					break;
				case TTS_OKAY:
					retval = "okay";
					break;
				case TTS_RECYCLE:
					retval = "recycle";
					break;
				default:
					retval = "none";
					break;
			}
			return retval;
		}
		const WORD getPort() const
		{
			return m_mSocket.getPort();
		}
		const char* getIP() const
		{
			return m_mSocket.getIP();
		}
		const DWORD getAddr() const
		{
			return m_mSocket.getAddr();
		}
		const bool ifCheckSignal() const
		{
			return m_checkSignal;
		}
		bool checkInterval(const Time &timeVal)
		{
			return m_tickTimer(timeVal);
		}
		bool checkTick() const
		{
			return m_tick;
		}
		void clearTick()
		{
			m_tick = false;
		}
		const DWORD getID() const
		{
			return id;
		}
		const DWORD getType() const
		{
			return m_taskType;
		}
		void setTick()
		{
			m_tick = true;
		}
		void checkSignal(const Time &timeVal);
		bool checkVerifyOK()
		{
			return m_verifyState == 1;
		}
		void setCheckTimeout(bool check)
		{
			m_checkTimeout = check;
		}
	public:
		DWORD m_taskType;
		bool m_buffered;
		Socket m_mSocket;
		TcpTask_State m_state;
	private:
		TerminateMethod m_terminate;
		bool m_terminateWait;
		bool m_fdsradd;
		Time m_lifeTime;
		bool m_uniqueVerified;
		const bool m_checkSignal;
		Timer m_tickTimer;
		bool m_tick;
		SWORD m_verifyState;
		bool m_checkTimeout;
	protected:
		virtual void analysisSendingCmd(BYTE cmd,BYTE param,DWORD size) {};
		virtual void analysisRecvingCmd(BYTE cmd,BYTE param,DWORD size) {};
};

#endif
