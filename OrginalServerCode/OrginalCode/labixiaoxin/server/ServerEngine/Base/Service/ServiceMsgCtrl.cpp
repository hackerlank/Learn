#include "ServiceMsgCtrl.h"
#include "..\Communication\CommunicationMgr.h"
#include "BaseService.h"
#include "..\Protocol\ServiceProtocol.h"

ServiceMsgCtrl::ServiceMsgCtrl()
{
	un_PacketSN = 0;
	for(int i = 0;i < MAX_SERVICE_OBJ_QUERY_DATA;i ++)
	{
		m_queryData[i].unAdapterID = OBJ_ID_NONE;
	}
}


ServiceMsgCtrl::~ServiceMsgCtrl()
{
	SERVICE_MSG_PEER_MAP_ITERATOR iter(m_msgPeerMap);
	ServiceMsgPeer *peer;

	for(iter = m_msgPeerMap.begin(); iter != m_msgPeerMap.end(); iter++)
	{
		peer = (*iter).int_id_;

		if(peer == NULL)
		{
			continue;
		}

		delete peer;
	}

	m_msgPeerMap.unbind_all();
}
/*
int ServiceMsgCtrl::sendMsg(MessageInfo &msgInfo)
{
	return COMMUNICATION_MGR_INSTANCE::instance()->sendMsg(ENDPOINT_TYPE_SERVICE, msgInfo.s_head->desAdr, msgInfo.msg);

#if 0
	if(msgInfo.p_head->unType <= SERVICE_MESSAGE_TYPE_OBJ_LOCATION)
	{
		//send directly
		return COMMUNICATION_MGR_INSTANCE::instance()->sendMsg(ENDPOINT_TYPE_SERVICE, msgInfo.s_head->desAdr, msgInfo.msg);
	}

	ObjAdr addr;

	addr.unServiceID = BaseService::instance()->getObjLocationQueryService(msgInfo.s_head->desAdr.unAdapterID);

	if(addr.unServiceID == OBJ_ID_NONE)
	{
		//send directly
		return COMMUNICATION_MGR_INSTANCE::instance()->sendMsg(ENDPOINT_TYPE_SERVICE, msgInfo.s_head->desAdr, msgInfo.msg);
	}

	addr.unAdapterID = addr.unObjID = OBJ_ID_NONE;

	ServiceMsgPeer *peer = createMsgPeer(msgInfo.s_head->desAdr.unAdapterID, msgInfo.s_head->desAdr.unObjID);

	if(peer != NULL)
	{
		if(peer->SendMsg(msgInfo) == -1)
		{
			return -1;
		}
	}
	else
	{
		//send directly
		return COMMUNICATION_MGR_INSTANCE::instance()->sendMsg(ENDPOINT_TYPE_SERVICE, msgInfo.s_head->desAdr, msgInfo.msg);
	}

	return 0;
#endif
}

void ServiceMsgCtrl::dealAckMsg(MessageInfo &msgInfo)
{
	MsgObjReached *body = (MsgObjReached *)msgInfo.body;

	ServiceMsgPeer *peer = getMsgPeer(body->unObjID);

	if(peer == NULL)
	{
		return;
	}

	peer->MsgAck(msgInfo);
}

void ServiceMsgCtrl::dealNotReachedMsg(MessageInfo &msgInfo)
{
	MsgObjNotfound *body = (MsgObjNotfound *)msgInfo.body;

	ServiceMsgPeer *peer = getMsgPeer(body->unObjID);

	if(peer == NULL)
	{
		return;
	}

	peer->QueryLocation(msgInfo.m_head->unPacketNO);
}

void ServiceMsgCtrl::dealObjLocationMsg(MessageInfo &msgInfo)
{
	MsgAnswerObjLocation *body = (MsgAnswerObjLocation *)msgInfo.body;

	ServiceMsgPeer *peer = getMsgPeer(body->unObjID);
	if(peer = NULL)
	{
		return;
	}

	if(body->unServiceID == OBJ_ID_NONE)
	{
		peer = removeMsgPeer(body->unObjID);
		if(peer != NULL)
		{
			delete peer;
		}
	}
	else
	{
		peer->UpdateLocation(body->unServiceID, msgInfo.m_head->unPacketNO);
	}
}
*/

ServiceMsgPeer *ServiceMsgCtrl::createMsgPeer(ACE_UINT32 unAdapterID, ACE_UINT32 unObjID)
{
	ACE_UINT64 t = GENERATE_CACHED_MSG_ID(unAdapterID, unObjID);

	ServiceMsgPeer *peer = getMsgPeer(t);

	if(peer != NULL)
	{
		return peer;
	}

	peer = new ServiceMsgPeer(unAdapterID, unObjID);
	if(peer == NULL)
	{
		return NULL;
	}

	if(m_msgPeerMap.bind(t, peer) != 0)
	{
		delete peer;
		return NULL;
	}

	return peer;
}

ServiceMsgPeer *ServiceMsgCtrl::getMsgPeer(ACE_UINT32 unAdapterID, ACE_UINT32 unObjID)
{
	ACE_UINT64 t = GENERATE_CACHED_MSG_ID(unAdapterID, unObjID);
	return getMsgPeer(t);
}

ServiceMsgPeer *ServiceMsgCtrl::getMsgPeer(ACE_UINT64 unObjID)
{
	ServiceMsgPeer *peer = NULL;

	if(m_msgPeerMap.find(unObjID, peer) != 0)
	{
		return NULL;
	}

	return peer;
}

ServiceMsgPeer *ServiceMsgCtrl::removeMsgPeer(ACE_UINT32 unAdapterID, ACE_UINT32 unObjID)
{
	ACE_UINT64 t = GENERATE_CACHED_MSG_ID(unAdapterID, unObjID);

	return removeMsgPeer(t);
}

ServiceMsgPeer *ServiceMsgCtrl::removeMsgPeer(ACE_UINT64 unObjID)
{
	ServiceMsgPeer *peer = NULL;

	m_msgPeerMap.unbind(unObjID, peer);

	return peer;
}

int ServiceMsgCtrl::send_msg(MessageInfo &msgInfo, bool bQuery)
{
	ObjAdr *queryAdr = NULL;

	if(msgInfo.p_head->unType == SERVICE_MESSAGE_TYPE_OBJ_LOCATION && msgInfo.m_head->unType == MSG_SERVICE_QUERY_OBJ_LOCATION)
	{
		msgInfo.s_head->srcAdr.unAdapterID = msgInfo.s_head->srcAdr.unObjID = OBJ_ID_NONE;
	}
	
	if(bQuery)
	{
		queryAdr = get_query_service_id(msgInfo.s_head->desAdr.unAdapterID, msgInfo.s_head->desAdr.unObjID);
	}

	if(queryAdr == NULL)
	{
		//send directly
		return COMMUNICATION_MGR_INSTANCE::instance()->sendMsg(ENDPOINT_TYPE_SERVICE, &msgInfo.s_head->desAdr, msgInfo.msg);
	}

	ServiceMsgPeer *peer = NULL;
	
	peer = createMsgPeer(msgInfo.s_head->desAdr.unAdapterID, msgInfo.s_head->desAdr.unObjID);

	if(peer == NULL)
	{
		printf("create msg peer failed\n");
		return -1;
	}

	msgInfo.m_head->unPacketNO = un_PacketSN;
	un_PacketSN ++;
	
	return peer->send_msg(msgInfo);
}

int ServiceMsgCtrl::pause_send_msg(ACE_UINT32 unAdapterID, ACE_UINT32 unObjID, ACE_UINT32 unServiceID)
{
	ServiceMsgPeer *peer = getMsgPeer(unAdapterID, unObjID);

	if(peer == NULL)
	{
		return -1;
	}
	
	return peer->pause(unServiceID);
}

int ServiceMsgCtrl::resume_send_msg(ACE_UINT32 unAdapterID, ACE_UINT32 unObjID, ACE_UINT32 unServiceID)
{
	ServiceMsgPeer *peer = NULL;

	if(unServiceID == OBJ_ID_NONE)
	{
		peer = removeMsgPeer(unAdapterID, unObjID);
		if(peer != NULL)
		{
			delete peer;
		}
		return 0;
	}

	peer = getMsgPeer(unAdapterID, unObjID);

	if(peer == NULL)
	{
		return -1;
	}

	return peer->resume(unServiceID);
}

int ServiceMsgCtrl::ack(ACE_UINT32 unAdapterID, ACE_UINT32 unObjID, ACE_UINT32 unPacketNo)
{
	ServiceMsgPeer *peer = getMsgPeer(unAdapterID, unObjID);

	if(peer == NULL)
	{
		return -1;
	}

	return peer->ack(unPacketNo);
}

void ServiceMsgCtrl::reset(ACE_UINT32 unAdapterID, ACE_UINT32 unObjID)
{
	ServiceMsgPeer *peer = getMsgPeer(unAdapterID, unObjID);

	if(peer == NULL)
	{
		return;
	}

	peer->reset();
}

int ServiceMsgCtrl::register_query_data(ACE_UINT32 unAdapterID, ObjAdr &queryAdr, bool bCreateWhenQueryFail)
{
	int idx = -1;
	for(int i = 0;i < MAX_SERVICE_OBJ_QUERY_DATA;i ++)
	{
		if(m_queryData[i].unAdapterID == OBJ_ID_NONE || idx == -1)
		{
			idx = i;
		}

		if(m_queryData[i].unAdapterID == unAdapterID)
		{
			return -1;
		}
	}

	if(idx == -1)
	{
		return -1;
	}

	m_queryData[idx].unAdapterID = unAdapterID;
	m_queryData[idx].queryAdr = queryAdr;
	m_queryData[idx].bCreateWhenQueryFail = bCreateWhenQueryFail;

	return 0;
}

void ServiceMsgCtrl::unregister_query_data(ACE_UINT32 unAdapterID)
{
	for(int i = 0;i < MAX_SERVICE_OBJ_QUERY_DATA;i ++)
	{
		if(m_queryData[i].unAdapterID == unAdapterID)
		{
			m_queryData[i].unAdapterID = OBJ_ID_NONE;
			break;
		}
	}
}

ObjAdr *ServiceMsgCtrl::get_query_service_id(ACE_UINT32 unAdapterID, ACE_UINT32 unObjID)
{
	if(unAdapterID == OBJ_ID_NONE || unObjID == OBJ_ID_NONE)
	{
		return NULL;
	}
	for(int i = 0;i < MAX_SERVICE_OBJ_QUERY_DATA;i ++)
	{
		if(m_queryData[i].unAdapterID == unAdapterID)
		{
			return &m_queryData[i].queryAdr;
		}
	}

	return NULL;
}

bool ServiceMsgCtrl::is_create_when_qyery_fail(ACE_UINT32 unAdapterID)
{
	if(unAdapterID == OBJ_ID_NONE)
	{
		return false;
	}
	for(int i = 0;i < MAX_SERVICE_OBJ_QUERY_DATA;i ++)
	{
		if(m_queryData[i].unAdapterID == unAdapterID)
		{
			return m_queryData[i].bCreateWhenQueryFail;
		}
	}

	return false;
}