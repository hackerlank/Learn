#include "NetworkPeerConnector.h"
//#include "..\Service\ServiceConfigMgr.h"

// #if _MEMORY_DEBUG
// #include "../../GameBase/Common/debugnew.h"
// DebugNewTracer DebugNewTrace;
// #define new new(__FILE__, __LINE__)
// #endif
#include "../Service/BaseService.h"

NetworkPeerConnector::NetworkPeerConnector()
{

}

NetworkConnection *NetworkPeerConnector::make_handler(void)
{
	NetworkConnection *conn = new NetworkConnection();

	if(conn != NULL)
	{
		//conn->m_unType = ServiceConnection::TYPE_SEND;
		conn->m_endpoint = m_endpoint;
	}

	return conn;
}

void NetworkPeerConnector::close()
{
	this->cancel();
	ACE_OS::closesocket(this->handle());
	this->handle(ACE_INVALID_HANDLE);
	CLogBase *pLog = BaseService::GetLogInstance();
	sprintf(pLog->m_szLogBuffer, "[%s][%d]:NetworkPeerConnector::close",__FILE__, __LINE__);
	pLog->RecordLog(Log_Type_Fatal, pLog->m_szLogBuffer);
}

void NetworkPeerConnector::setEndPoint(NetworkEndPoint *endpoint)
{
	this->m_endpoint = endpoint;
}

void NetworkPeerConnector::handle_time_out(const ACE_Time_Value &tv, const void *act)
{
	printf("asynch connector time out\n");
	CLogBase *pLog = BaseService::GetLogInstance();
	sprintf(pLog->m_szLogBuffer, "[%s][%d]:handle_time_out",__FILE__, __LINE__);
	pLog->RecordLog(Log_Type_Fatal, pLog->m_szLogBuffer);
	
}

int NetworkPeerConnector::validate_connection(const ACE_Asynch_Connect::Result& result, const ACE_INET_Addr &remote, const ACE_INET_Addr &local)
{
	int t = result.success();

	//ServiceInstanceInfo *p = (ServiceInstanceInfo *)result.act();

	/*

	if(p == NULL)
	{
		printf("asynch connector validate result = %d[0x00000000]\n", t);
	}
	else
	{
		printf("asynch connector validate result = %d[0x%08x]\n", t, p->unID);
	}
	*/

	if(!t)
	{
		return -1;
	}

	return 0;
}