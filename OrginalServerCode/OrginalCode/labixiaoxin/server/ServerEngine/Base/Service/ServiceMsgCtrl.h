#pragma once

#include "ace\Singleton.h"
#include "..\Protocol\Protocol.h"
#include "ace\Null_Mutex.h"
#include "ace\Hash_Map_Manager.h"
#include "ServiceMsgPeer.h"

#define GENERATE_CACHED_MSG_ID(a, b) ((((ACE_UINT64)a) << 32) | (((ACE_UINT64)b)))

typedef ACE_Hash_Map_Manager_Ex<ACE_UINT64, ServiceMsgPeer *, ACE_Hash<ACE_UINT64>, 
ACE_Equal_To<ACE_UINT64>, ACE_Null_Mutex> SERVICE_MSG_PEER_MAP;
typedef SERVICE_MSG_PEER_MAP::ITERATOR SERVICE_MSG_PEER_MAP_ITERATOR;

/*
typedef struct tagObjLocationInfo
{
	ACE_UINT32 unServiceID;
}ObjLocationInfo;

typedef ACE_Hash_Map_Manager_Ex<ACE_UINT64, ObjLocationInfo *, ACE_Hash<ACE_UINT64>, 
ACE_Equal_To<ACE_UINT64>, ACE_Null_Mutex> OBJ_LOCATION_MAP;
typedef OBJ_LOCATION_MAP::ITERATOR OBJ_LOCATION_MAP_ITERATOR;
*/

typedef struct tagServiceObjQueryData
{
	ACE_UINT32 unAdapterID;
	ObjAdr queryAdr;
	bool bCreateWhenQueryFail;
}ServiceObjQueryData;

#define MAX_SERVICE_OBJ_QUERY_DATA 8

class ServiceMsgCtrl
{
public:
	ServiceMsgCtrl();
	~ServiceMsgCtrl();

	/*
	int sendMsg(MessageInfo &msgInfo);
	void dealAckMsg(MessageInfo &msgInfo);
	void dealNotReachedMsg(MessageInfo &msgInfo);
	void dealObjLocationMsg(MessageInfo &msgInfo);
	*/

	int send_msg(MessageInfo &msgInfo, bool bQuery);
	int pause_send_msg(ACE_UINT32 unAdapterID, ACE_UINT32 unObjID, ACE_UINT32 unServiceID);
	int resume_send_msg(ACE_UINT32 unAdapterID, ACE_UINT32 unObjID, ACE_UINT32 unServiceID);
	int ack(ACE_UINT32 unAdapterID, ACE_UINT32 unObjID, ACE_UINT32 unPacketNo);
	void reset(ACE_UINT32 unAdapterID, ACE_UINT32 unObjID);

	int register_query_data(ACE_UINT32 unAdapterID, ObjAdr &queryAdr, bool bCreateWhenQueryFail);
	void unregister_query_data(ACE_UINT32 unAdapterID);
	ObjAdr *get_query_service_id(ACE_UINT32 unAdapterID, ACE_UINT32 unObjID);
	bool is_create_when_qyery_fail(ACE_UINT32 unAdapterID);
ServiceMsgPeer *removeMsgPeer(ACE_UINT64 unObjID);
private:
	ServiceMsgPeer *createMsgPeer(ACE_UINT32 unAdapterID, ACE_UINT32 unObjID);
	ServiceMsgPeer *getMsgPeer(ACE_UINT64 unObjID);
	ServiceMsgPeer *getMsgPeer(ACE_UINT32 unAdapterID, ACE_UINT32 unObjID);
	
	ServiceMsgPeer *removeMsgPeer(ACE_UINT32 unAdapterID, ACE_UINT32 unObjID);

	SERVICE_MSG_PEER_MAP m_msgPeerMap;

	ACE_UINT32 un_PacketSN;

	ServiceObjQueryData m_queryData[MAX_SERVICE_OBJ_QUERY_DATA];
};

typedef ACE_Singleton<ServiceMsgCtrl, ACE_Thread_Mutex> SERVICE_MSG_CTRL_INSTANCE;