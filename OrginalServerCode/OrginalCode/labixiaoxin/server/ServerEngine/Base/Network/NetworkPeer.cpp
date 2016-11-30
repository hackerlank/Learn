#include "NetworkPeer.h"
#include "NetworkEndPoint.h"
//#include "..\Protocol\ServiceProtocol.h"
#include "..\Service\BaseService.h"

//to do
//add timer to judge connect fail

NetworkPeer::NetworkPeer(ACE_UINT32 unIP, ACE_UINT32 unListenPort, NetworkEndPoint *endpoint)
{
	m_endpoint = endpoint;

	m_sendQueue.high_water_mark(0x40000);
	m_sendQueue.low_water_mark(0x40000);
}

NetworkPeer::~NetworkPeer()
{
}
