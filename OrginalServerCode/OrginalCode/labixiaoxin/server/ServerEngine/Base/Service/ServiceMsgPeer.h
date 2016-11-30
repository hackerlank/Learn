#pragma once

#include "ace\Message_Block.h"
#include "ace\Containers.h"
#include "..\Protocol\Protocol.h"
#include "..\Communication\CommunicationMgr.h"

typedef struct tagCacheMsgNode
{
	ACE_UINT32 unPacketNo;
	ObjAdr *des_adr;
	ACE_Message_Block *msg;
}CacheMsgNode;

typedef ACE_DLList<CacheMsgNode> MSG_PEER_CACHE_LIST;
typedef ACE_DLList_Iterator<CacheMsgNode> MSG_PEER_CACHE_LIST_ITERATOR;

class ServiceMsgPeer
{
public:
	enum
	{
		STATUS_NORMAL = 0,
		STATUS_PAUSE
	};
	ServiceMsgPeer(ACE_UINT32 unAdapterID, ACE_UINT32 unObjID);
	~ServiceMsgPeer();

	int send_msg(MessageInfo &msgInfo);
	int pause(ACE_UINT32 unServiceID);
	int resume(ACE_UINT32 unServiceID);
	int ack(ACE_UINT32 unPacketNo);
	void reset();
	/*
	int SendMsg(MessageInfo &msgInfo);
	int MsgAck(MessageInfo &msgInfo);
	void UpdateLocation(ACE_UINT32 unServiceID, ACE_UINT32 unPacketNo);
	void QueryLocation(ACE_UINT32 unPacketNo);
	*/

	

private:
	ACE_UINT32 m_unAdapterID;
	ACE_UINT32 m_unObjID;

	int m_currentStatus;
	ACE_UINT32 m_unCurrentServiceID;

	int cache_msg(MessageInfo &msgInfo);
	void remove_cache_msg_from_tail();

	MSG_PEER_CACHE_LIST m_cache_list;

	//int m_nQueryCount;

	
	//int CreateNewBlock(ACE_UINT32 unOffset);
	//int CacheMsg(MessageInfo &msgInfo);
	
	
	//MsgPeerBlock *m_blockHead, *m_blockTail;
	//MsgPeerBlock *m_currentBlock;
};