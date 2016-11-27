#ifndef BASE_TCP_SERVICE_H
#define BASE_TCP_SERVICE_H

#include "baseClass.h"
#include "common/baseDef.h"
#include "base/global.h"

#include <netinet/in.h>
#include <sys/epoll.h>
#include <errno.h>

class TcpService : private Noncopyable
{
	public:
		TcpService(const std::string &name);
		~TcpService();
		bool bind(const std::string &name,const WORD port);
		SDWORD accept(struct sockaddr_in *addr);
	private:
		static const SDWORD s_msec = 2100;
		static const SDWORD s_maxWaitQueue = 2000;
		char m_name[MAX_NAME_SIZE];
		SDWORD m_sock;
		SDWORD m_kdpfd;
};

#endif
