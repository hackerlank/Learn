#pragma once

#include "..\Service\Service_Config.h"
#include "..\Communication\BaseEndPoint.h"
#include "ace\Null_Mutex.h"
#include "ace\Hash_Map_Manager.h"
#include "ace\Asynch_IO.h"
#include "ace\SOCK_Dgram.h"
#include "ace\SOCK_Dgram_Mcast.h"
#include "ace\INET_Addr.h"
//#include "UDPConnection.h"
#include "NetworkPeer.h"
#include "NetworkPeerAcceptor.h"
#include "NetworkPeerConnector.h"

/*
ServiceID 构成 IP 最高字节为Service Type，后3个字节为序号

Service Manager的Service ID是固定的(这里是Cluster Manager),0x01000000

*/

/*
typedef struct tagServiceInfo
{
	ACE_UINT32 unServiceID;
	//ACE_UINT32 unServiceType;
	ACE_UINT32 unIP;
	ACE_UINT32 unListenPort;
	UDPConnection *pConnection;
}ServiceInfo;
*/

typedef ACE_Hash_Map_Manager_Ex<ACE_UINT32, NetworkPeer *, ACE_Hash<ACE_UINT32>, 
ACE_Equal_To<ACE_UINT32>, ACE_Null_Mutex> NETWORK_PEER_MAP;
typedef NETWORK_PEER_MAP::ITERATOR NETWORK_PEER_MAP_ITERATOR;

class NetworkEndPoint : public BaseEndPoint, public ACE_Service_Handler
{
public:
	NetworkEndPoint(ACE_Message_Queue<ACE_MT_SYNCH> *recvQueue, char *strIP, ACE_UINT32 unListenPort);
	virtual ~NetworkEndPoint();

	virtual int activate();
	virtual bool do_activate();
	virtual void deactivate();
	virtual bool do_deactivate();

	virtual int putMsg(ACE_Message_Block *msg);

private:

	NETWORK_PEER_MAP m_NetworkPeerMap;

	NetworkPeerAcceptor m_listenHandler;
	NetworkPeerConnector m_connectHandler;
};