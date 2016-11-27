#ifndef BASE_MSG_CONTAINER_H
#define BASE_MSG_CONTAINER_H
#include <iostream>
#include <string.h>
#include <vector>
#include <assert.h>
#include <queue>
#include <ext/pool_allocator.h>
#include "baseLock.h"

#include "base/global.h"
#include "common/nullCmd.h"
#include "protol/protolCmd.h"

using namespace std;

const DWORD trunkSize = 64 * 1024;

#define trunkCount(size)(((size) + trunkSize - 1) / trunkSize)

#define unzip_size(zip_size)((zip_size) * 120 / 100 + 12)

const DWORD PACKET_ZIP_BUFFER = unzip_size(trunkSize - 1) + sizeof(DWORD) + 8;
template<typename Type>
class ByteBuffer
{
	private:
		DWORD m_maxSize;
		DWORD m_offPtr;
		DWORD m_curPtr;
		Type m_buffer;
	public:
		ByteBuffer();
		inline void put(const BYTE *buf,const DWORD size)
		{
			wrReserve(size);
			bcopy(buf,&m_buffer[m_curPtr],size);
			m_curPtr += size;
		}

		inline BYTE *wrBuffer()
		{
			return &m_buffer[m_curPtr];
		}
		inline BYTE *rdBuffer()
		{
			return &m_buffer[m_offPtr];
		}
		inline bool rdReady()
		{
			return m_curPtr > m_offPtr;
		}
		inline DWORD rdSize()
		{
			return m_curPtr - m_offPtr;
		}
		inline void rdFlip(const DWORD size)
		{
			CheckConditonVoid(size);
			m_offPtr += size;
			if(m_curPtr > m_offPtr)
			{
				DWORD tmp = m_curPtr - m_offPtr;
				if(tmp <= m_offPtr)
				{
					memmove(&m_buffer[0],&m_buffer[m_offPtr],tmp);
					m_offPtr = 0;
					m_curPtr = tmp;
				}
			}
			else
			{
				m_offPtr = 0;
				m_curPtr = 0;
			}
		}
		inline DWORD wrSize()
		{
			return m_maxSize - m_curPtr;
		}
		inline void wrFlip(const DWORD size)
		{
			m_curPtr += size;
		}
		inline void reset()
		{
			m_offPtr = 0;
			m_curPtr = 0;
		}
		inline const DWORD maxSize() const
		{
			return m_maxSize;
		}
		void wrReserve(const DWORD size);
};

typedef ByteBuffer<std::vector<BYTE> > BufferCmdQueue;

typedef ByteBuffer<BYTE [PACKET_ZIP_BUFFER]> StackCmdQueue;

template<typename Cmd_type,DWORD size = 64 * 1024>
class CmdBuffer_wrapper
{
	public:
		typedef Cmd_type type;
		DWORD cmd_size;
		DWORD max_size;
		type* cnt;
		CmdBuffer_wrapper():cmd_size(sizeof(type)),max_size(size)
		{
			cnt = (type*)buffer;
			constructInPlace(cnt);
		}
	private:
		BYTE buffer[size];
};

class Processor
{
	public:
		virtual bool msgParse(const Cmd::NullCmd *cmd,const DWORD length) = 0;
		virtual bool msgParseStart(const Cmd::NullCmd *cmd,const DWORD length) = 0;
		virtual bool msgParseForward(const Cmd::NullCmd *cmd,const DWORD length) = 0;
};
typedef std::pair<DWORD,BYTE*> CmdPair;
#define QueueSize 102400
class MsgQueue
{
	public:
		MsgQueue()
		{
			queueRead = 0;
			queueWrite = 0;
		}
		~MsgQueue()
		{
			clear();
		}
		typedef std::pair<volatile bool,CmdPair> CmdQueue;
		CmdPair* get()
		{
			CmdPair *ret = NULL;
			if(cmdQueue[queueRead].first)
			{
				ret = &cmdQueue[queueRead].second;
			}
			return ret;
		}
		void erase()
		{
			free(cmdQueue[queueRead].second.second);
			cmdQueue[queueRead].first = false;
			queueRead = (++queueRead) % QueueSize;
		}
		bool put(const void *ptNullCmd,const DWORD cmdLen)
		{
			BYTE *buf = (BYTE*)malloc(cmdLen + 1);
			if(buf)
			{
				bcopy(ptNullCmd,buf,cmdLen);
				if(!putQueueToArray() && !cmdQueue[queueWrite].first)
				{
					cmdQueue[queueWrite].second.first = cmdLen;
					cmdQueue[queueWrite].second.second = buf;
					cmdQueue[queueWrite].first = true;
					queueWrite = (++queueWrite) % QueueSize;
					return true;
				}
				else
				{
					queueCmd.push(std::make_pair(cmdLen,buf));
				}
				return true;
			}
			return false;
		}
	private:
		void clear()
		{
			while(putQueueToArray())
			{
				while(get())
				{
					erase();
				}
			}
			while(get())
			{
				erase();
			}
		}
		bool putQueueToArray()
		{
			bool isLeft = false;
			while(!queueCmd.empty())
			{
				if(!cmdQueue[queueWrite].first)
				{
					cmdQueue[queueWrite].second = queueCmd.front();
					cmdQueue[queueWrite].first = true;
					queueWrite = (++queueWrite) % QueueSize;
					queueCmd.pop();
				}
				else
				{
					isLeft = true;
					break;
				}
			}
			return isLeft;
		}
	//	__gnu_cxx::__mt_alloc<BYTE>  __mt_alloc;
		CmdQueue cmdQueue[QueueSize];
	//	std::queue<CmdPair,std::deque<CmdPair,__gnu_cxx::_pool_alloc<CmdPair> > >queueCmd;
		std::queue<CmdPair>queueCmd;
		DWORD queueWrite;
		DWORD queueRead;
};
				

template<bool lock=false>
class MessageQueue : public RWLocker<lock>,public Processor
{
	protected:
		virtual ~MessageQueue()
		{
		}
	public:
		bool cmdMsgParse(const Cmd::NullCmd *ptNullCmd,const DWORD cmdLen)
		{
			RWLocker<lock>::wrlock();
			Global::logger->debug("cmdMsgParse %u,%u",ptNullCmd->byCmd,ptNullCmd->byParam);
			bool bret = cmdQueue.put((void*)ptNullCmd,cmdLen);
			RWLocker<lock>::unlock();
			return bret;
		}
		bool doCmd()
		{
			RWLocker<lock>::wrlock();
			CmdPair *cmd = cmdQueue.get();
			while(cmd)
			{
				const Cmd::NullCmd *ptNullCmd = (const Cmd::NullCmd*)cmd->second;
				switch(ptNullCmd->byCmd)
				{
					case Cmd::Server::START_SERVERCMD:
						{
							msgParseStart(ptNullCmd,cmd->first);
						}
						break;
					case Cmd::Server::FORWARD_SERVERCMD:
						{
							msgParseForward(ptNullCmd,cmd->first);
						}
						break;
					default:
						{
							msgParse(ptNullCmd,cmd->first);
						}
						break;
				}
			cmdQueue.erase();
			cmd = cmdQueue.get();
		}
		if(cmd)
		{
			cmdQueue.erase();
		}
		RWLocker<lock>::unlock();
		return true;
	}
private:
	MsgQueue cmdQueue;
};
#endif
