#include "baseNetService.h"

NetService::NetService( const std::string &name ):Service( name )
{
	strncpy( this->name,name.c_str(),sizeof( this->name ) );
	m_tcpService = NULL;
	m_taskPool = NULL;
}

NetService::~NetService()
{
	if( m_taskPool )
	{
		m_taskPool->final();
		DELETE( m_taskPool );
	}
}
const DWORD NetService::getPoolSize() const
{
	if( m_taskPool )
	{
		return m_taskPool->getSize();
	}
	return 0;
}
bool NetService::init(const WORD port)
{
	LogErrorCheckCondition(Service::init(),false,"网络服务器初始化失败%s",name);
	m_tcpService = new TcpService(name);
	LogErrorCheckCondition(m_tcpService && m_tcpService->bind(name,port),false,"网络服务器帮定端口失败%s,%d",name,port);
	return true;
}

bool NetService::serviceCallBack()
{
	struct sockaddr_in addr;
	int retcode = m_tcpService->accept( &addr );
	if( retcode >= 0 )
	{
		newTcpTask( retcode,&addr );
	}
	return true;
}

void NetService::final()
{
	DELETE( m_tcpService );
}

		
		
