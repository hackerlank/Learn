#pragma once

#include "..\Service\Service_Config.h"
#include "BaseEndPoint.h"
#include "ace\Null_Mutex.h"
#include "ace\Hash_Map_Manager.h"
#include "ace\Asynch_IO.h"
#include "ace\SOCK_Dgram.h"
#include "ace\SOCK_Dgram_Mcast.h"
#include "ace\INET_Addr.h"
//#include "UDPConnection.h"
#include "ServicePeer.h"
#include "ServicePeerAcceptor.h"
#include "ServicePeerConnector.h"
#include "..\TimerMgr\TimerMgr.h"

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

typedef ACE_Hash_Map_Manager_Ex<ACE_UINT32, ServicePeer *, ACE_Hash<ACE_UINT32>, 
ACE_Equal_To<ACE_UINT32>, ACE_Null_Mutex> SERVICE_PEER_MAP;
typedef SERVICE_PEER_MAP::ITERATOR SERVICE_PEER_MAP_ITERATOR;

class ServiceEndPoint : public BaseEndPoint, public ACE_Service_Handler
{
public:
	ServiceEndPoint(ACE_Message_Queue<ACE_MT_SYNCH> *recvQueue, char *strIP, ACE_UINT32 unListenPort, ACE_UINT32 bServiceMgr);
	virtual ~ServiceEndPoint();

	virtual int activate();
	virtual bool do_activate();
	virtual void deactivate();
	virtual bool do_deactivate();

	int connect(ACE_UINT32 unServiceID, ACE_UINT32 unIP, ACE_UINT32 unPort);
	int query_service_address(ACE_UINT32 unServiceID);
	int register_service();
	int unregister_service();

	ServicePeer *set_service_peer_connection(ACE_UINT32 unServiceID, ACE_UINT32 unIP, ACE_UINT32 unPort, ServiceConnection *conn, ACE_UINT32 unType);
	void notify_send_done(ACE_UINT32 unServiceID, ACE_Message_Block *msg);
	void remove_connection(ACE_UINT32 unServiceID, ACE_UINT32 unType);

	//void handle_read_dgram(const ACE_Asynch_Read_Dgram::Result &result);
	//void handle_write_dgram(const ACE_Asynch_Write_Dgram::Result &result);

	virtual int sendMessage(void *des_adr, ACE_Message_Block *msg);

	void clear_service_info(ACE_UINT32 unServiceID);
	void update_service_info(ACE_UINT32 unServiceID, ACE_UINT32 unIP, ACE_UINT32 unListenPort);
	void answer_service_info(ACE_UINT32 unQueryServiceID, ACE_UINT32 unServiceID);


	virtual int putMsg(ACE_Message_Block *msg);

	int get_service_list(ServerBasicInfo desList[], int nMaxCount);
	bool is_service_on(ACE_UINT32 unServiceID);

	//ACE_UINT32 getLocalPort();
private:
	int listen();

	void destroy();

	//static void mcastCallback(void *p, long lTimerID);

	static void serviceEndPointTimerCallback(void *p, long lTimerID);

	//void multicast();
	void connect_all_peer();
	void disconnect_all_peer();
	void broadcast_service_status_msg(ACE_UINT32 unType, ACE_UINT32 unServiceID);
	int send_service_status_msg(ACE_UINT32 unType, ACE_UINT32 unServiceID, ACE_UINT32 unIP, ACE_UINT32 unPort, ACE_UINT32 unTargetServiceID);

	ServicePeer *create_service_peer(ACE_UINT32 unServiceID, ACE_UINT32 unIP, ACE_UINT32 unListenPort);
	

	ACE_UINT32 m_bServiceMgr;
	//long m_mcastTimer;

	void set_register_flag(bool flag);

	BaseTimerHandler *m_timerHandler;

	SERVICE_PEER_MAP m_ServicePeerMap;

	ServicePeerAcceptor m_listenHandler;
	ServicePeerConnector m_connectHandler;

	bool m_bRegister;
};