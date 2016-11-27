#ifndef BASE_TCP_TASK_QUEUE_H
#define BASE_TCP_TASK_QUEUE_H
#include "baseTcpTask.h"

class TcpTaskQueue : public TcpTask
{
	public:
		TcpTaskQueue(const SDWORD sock,const struct sockaddr_in *addr = NULL,const bool compress = false,const bool checkSignal = true) : TcpTask(sock,addr,compress)
	{
	}
		virtual ~TcpTaskQueue() {};
		virtual bool checkRecycle() = 0;
	private:
		bool parse(const Cmd::NullCmd *cmd,const DWORD cmdLen);
};

#endif
