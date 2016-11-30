#pragma once

#include "..\..\Base\Communication\BaseEndPoint.h"
#include "PhpConnection.h"
#include "PhpAcceptor.h"
#include "ace\Null_Mutex.h"
#include "ace\Hash_Map_Manager.h"

enum
{
	ENDPOINT_TYPE_TCP_PHP = 1
};

typedef ACE_Hash_Map_Manager_Ex<ACE_UINT32, PhpConnection *, ACE_Hash<ACE_UINT32>, 
ACE_Equal_To<ACE_UINT32>, ACE_Null_Mutex> PHP_CONNECTION_MAP;
typedef PHP_CONNECTION_MAP::ITERATOR PHP_CONNECTION_MAP_ITERATOR;

class PhpEndPoint : public BaseEndPoint
{
public:
	PhpEndPoint(ACE_Message_Queue<ACE_MT_SYNCH> *recvQueue,char *strIP, ACE_UINT32 unListenPort);
	virtual ~PhpEndPoint();

	virtual int activate();
	virtual bool do_activate();
	virtual void deactivate();
	virtual bool do_deactivate();

	virtual int sendMessage(void *des_adr, ACE_Message_Block *msg);
	
	int put_msg(ACE_Message_Block *msg, PhpConnection *connection);

	void delete_peer(ACE_UINT32 unPeerID);
	void remove_connection(ACE_UINT32 unPeerID);
protected:
	ACE_UINT32 m_unPeerIDCounter;
	PHP_CONNECTION_MAP m_connectionMap;
	ACE_UINT32 m_unDesAdapterID;
	//virtual int parse_connection_init_data(char *buff, int size, ConnectionInitData &info);
private:
	
	PhpAcceptor m_listenHandler;

	bool is_connection_empty();
	void delete_all_connection();
};