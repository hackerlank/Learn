#include "baseTcpService.h"
TcpService::TcpService(const std::string &name) : m_sock(-1)
{
	bzero( m_name,sizeof(m_name) );
	strncpy( m_name,name.c_str(),sizeof(m_name) );
	m_kdpfd = epoll_create(1);
	assert(m_kdpfd != -1);
}
TcpService::~TcpService()
{
	TEMP_FAILURE_RETRY(::close(m_kdpfd));
	if(m_sock != -1)
	{
		::shutdown(m_sock,SHUT_RD);
		TEMP_FAILURE_RETRY(::close(m_sock));
		m_sock = -1;
	}
}
bool TcpService::bind(const std::string &name,const WORD port)
{
	LogErrorCheckCondition(m_sock == -1,false,"网络连接服务器端口邦定失败%s,%d",m_name,m_sock);

	struct sockaddr_in addr;
	m_sock = ::socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	LogErrorCheckCondition( m_sock != -1,false,"网络连接服务器端口绑定生成套接口失败%s,%d",m_name,m_sock );
	
	SDWORD reuse = 1;
	if(::setsockopt(m_sock,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(reuse)) == -1)
	{
		TEMP_FAILURE_RETRY(::close(m_sock));
		m_sock = -1;
		return false;
	}
	
	socklen_t window_size = 128 * 1024;
	if(::setsockopt(m_sock,SOL_SOCKET,SO_RCVBUF,&window_size,sizeof(window_size)) == -1)
	{
		TEMP_FAILURE_RETRY(::close(m_sock));
		m_sock = -1;
		return false;
	}
	
	if(::setsockopt(m_sock,SOL_SOCKET,SO_SNDBUF,&window_size,sizeof(window_size)) == -1)
	{
		TEMP_FAILURE_RETRY(::close(m_sock));
		m_sock = -1;
		return false;
	}
	
	bzero(&addr,sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(port);
	SDWORD retcode = ::bind(m_sock,(struct sockaddr*)&addr,sizeof(addr));
	if(retcode == -1)
	{
		TEMP_FAILURE_RETRY(::close(m_sock));
		m_sock = -1;
		return false;
	}
	
	retcode = ::listen(m_sock,s_maxWaitQueue);
	if(retcode == -1)
	{
		Global::logger->debug("setsockopt 4444");
		TEMP_FAILURE_RETRY(::close(m_sock));
		m_sock = -1;
		return false;
	}
	
	struct epoll_event ev;
	ev.events = EPOLLIN;
	ev.data.ptr = NULL;
	LogErrorCheckCondition(epoll_ctl(m_kdpfd,EPOLL_CTL_ADD,m_sock,&ev) != -1,false,"网络连接服务器端口绑定创建文件描述符失败");
	return true;
}
SDWORD TcpService::accept(struct sockaddr_in *addr)
{
	socklen_t len = sizeof(struct sockaddr_in);
	bzero(addr,sizeof(struct sockaddr_in));
	struct epoll_event ev;
	SDWORD rc = epoll_wait(m_kdpfd,&ev,1,s_msec);
	if(rc == 1 && (ev.events & EPOLLIN))
	{
		return TEMP_FAILURE_RETRY(::accept(m_sock,(struct sockaddr*)addr,&len));
	}
	return -1;
}

