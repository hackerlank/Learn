#include "ServicePeerConnector.h"
#include "..\Service\ServiceConfigMgr.h"

#if _MEMORY_DEBUG
#include "../../GameBase/Common/debugnew.h"
#define new new(__FILE__, __LINE__)
#endif

ServicePeerConnector::ServicePeerConnector()
{

}

ServiceConnection *ServicePeerConnector::make_handler(void)
{
	ServiceConnection *conn = new ServiceConnection();

	if(conn != NULL)
	{
		conn->m_unType = ServiceConnection::TYPE_SEND;
		conn->m_endpoint = m_endpoint;
	}

	return conn;
}

void ServicePeerConnector::close()
{
	this->cancel();
	ACE_OS::closesocket(this->handle());
	this->handle(ACE_INVALID_HANDLE);
}

void ServicePeerConnector::setEndPoint(ServiceEndPoint *endpoint)
{
	this->m_endpoint = endpoint;
}

void ServicePeerConnector::handle_time_out(const ACE_Time_Value &tv, const void *act)
{
	printf("asynch connector time out\n");
}

int ServicePeerConnector::validate_connection(const ACE_Asynch_Connect::Result& result, const ACE_INET_Addr &remote, const ACE_INET_Addr &local)
{
	int t = result.success();

	ServiceInstanceInfo *p = (ServiceInstanceInfo *)result.act();

	if(p == NULL)
	{
		printf("asynch connector validate result = %d[0x00000000]\n", t);
	}
	else
	{
		printf("asynch connector validate result = %d[0x%08x]\n", t, p->unID);
	}

	if(!t)
	{
		return -1;
	}

	return 0;
}