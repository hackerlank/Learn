#pragma once

#include "..\..\Base\Communication\BaseEndPoint.h"
#include "ClientConnection.h"
#include "ClientPeer.h"
#include "ClientAcceptor.h"
#include "ace\Null_Mutex.h"
#include "ace\Hash_Map_Manager.h"
#include "..\..\base\TimerMgr\TimerMgr.h"

typedef ACE_Hash_Map_Manager_Ex<ACE_UINT32, ClientPeer *, ACE_Hash<ACE_UINT32>, 
ACE_Equal_To<ACE_UINT32>, ACE_Null_Mutex> CLIENT_PEER_MAP;
typedef CLIENT_PEER_MAP::ITERATOR CLIENT_PEER_MAP_ITERATOR;


enum
{
	ENDPOINT_TYPE_TCP_INTERNET = 1
};

typedef struct tagConnectionInitData
{
	ACE_UINT32 unPeerID;
	char strSession[CLIENT_SESSION_LEN + 1];
}ConnectionInitData;

class ClientEndPoint : public BaseEndPoint
{
public:
	ClientEndPoint(ACE_Message_Queue<ACE_MT_SYNCH> *recvQueue, char *strIP, ACE_UINT32 unListenPort);
	virtual ~ClientEndPoint();

	virtual int activate();
	virtual bool do_activate();
	virtual void deactivate();
	virtual bool do_deactivate();

	virtual int sendMessage(void *des_adr, ACE_Message_Block *msg);

	int validate_connection(char *buff, int size, ClientConnection *pConnection, bool canCreate);
	//ClientPeer *create_client_peer(char *buff, int size, ClientConnection *pConnection, bool canCreate);
	ClientPeer *reset_peer(ACE_UINT32 unPeerID, char *strSession);
	virtual ClientPeer *create_peer(ACE_UINT32 unPeerID, char *strSession, bool canCreate);
	virtual int delete_peer(ACE_UINT32 unPeerID);
	ClientPeer *find_peer(ACE_UINT32 unPeerID);

	//login server also forward login request to logic
	virtual int parse_connection_init_data(char *buff, int size, ConnectionInitData &info) = 0;
	//virtual ClientPeer *new_peer(ACE_UINT32 unPeerID, ACE_UINT32 unSessionID, ACE_UINT32 unMaxConnection);
	virtual ClientConnection *newConnection() = 0;

	//void set_internet_ip(char *strIP);

protected:
	//ACE_UINT32 m_unListenPort;
	//ACE_UINT32 m_unListenIP;
	ACE_UINT32 m_unPeerMaxConnection;
	ACE_UINT32 m_unAdapterID;
	bool m_bReliable;
private:
	void peer_timeout();

	ClientAcceptor m_listenHandler;
	CLIENT_PEER_MAP m_peerMap;

	//long m_lTimerID;
	BaseTimerHandler *m_timerHandler;

	static void timerCallback(void *p, long lTimerID);
};