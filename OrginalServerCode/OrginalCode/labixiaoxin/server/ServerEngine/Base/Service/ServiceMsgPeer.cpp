#include "ServiceMsgPeer.h"
//#include "RootObj.h"
#include "BaseService.h"

#define MAX_QUERY_INTERVAL 5

ServiceMsgPeer::ServiceMsgPeer(ACE_UINT32 unAdapterID, ACE_UINT32 unObjID)
{
	m_unAdapterID = unAdapterID;
	m_unObjID = unObjID;

	m_unCurrentServiceID = OBJ_ID_NONE;
	m_currentStatus = STATUS_NORMAL;
}

ServiceMsgPeer::~ServiceMsgPeer()
{
	reset();
}

void ServiceMsgPeer::reset()
{
	MSG_PEER_CACHE_LIST_ITERATOR iter(m_cache_list);

	CacheMsgNode *info = NULL;

	while(!iter.done())
	{
		info = iter.next();

		iter.remove();
		info->msg->release();
		delete info;

		//iter.advance();
	}

	m_cache_list.reset();
}

int ServiceMsgPeer::send_msg(MessageInfo &msgInfo)
{
	if(cache_msg(msgInfo) == -1)
	{
		return -1;
	}

	//change by xxj 2015/05/22  20: 48:16 
	if(m_currentStatus == STATUS_NORMAL)
	{
		if(m_unCurrentServiceID == OBJ_ID_NONE)
		{
			return 1;
		}
		else
		{
			msgInfo.s_head->desAdr.unServiceID = m_unCurrentServiceID;

			//send msg
			if(COMMUNICATION_MGR_INSTANCE::instance()->sendMsg(ENDPOINT_TYPE_SERVICE, &msgInfo.s_head->desAdr, msgInfo.msg) == -1)
			{
				remove_cache_msg_from_tail();
				return -1;
			}
		}
	}

	return 0;
}

int ServiceMsgPeer::pause(ACE_UINT32 unServiceID)
{
	if(m_currentStatus == STATUS_NORMAL && (unServiceID == OBJ_ID_NONE || m_unCurrentServiceID == unServiceID))
	{
		m_currentStatus = STATUS_PAUSE;
		return 0;
	}

	return -1;
}

int ServiceMsgPeer::resume(ACE_UINT32 unServiceID)
{
	if(m_currentStatus == STATUS_NORMAL)
	{
		return -1;
	}
	
	m_unCurrentServiceID = unServiceID;
	m_currentStatus = STATUS_NORMAL;

	//send msg cached

	MSG_PEER_CACHE_LIST_ITERATOR iter(m_cache_list);

	CacheMsgNode *info = NULL;

	while(!iter.done())
	{
		info = iter.next();

		info->des_adr->unServiceID = m_unCurrentServiceID;

		//send msg
		ACE_Message_Block *msg = info->msg->duplicate();

		if(COMMUNICATION_MGR_INSTANCE::instance()->sendMsg(ENDPOINT_TYPE_SERVICE, info->des_adr, msg) == -1)
		{
			msg->release();
			iter.remove();
			info->msg->release();
			delete info;
		}
		else
		{
			iter.advance();
		}
	}

	return 0;
}

int ServiceMsgPeer::ack(ACE_UINT32 unPacketNo)
{
	MSG_PEER_CACHE_LIST_ITERATOR iter(m_cache_list);
	CacheMsgNode *info = NULL;

	if(!iter.done())
	{
		info = iter.next();

		if(info->unPacketNo == unPacketNo)
		{
			iter.remove();
			info->msg->release();
			delete info;
			return 0;
		}
		else
		{
			return -1;
		}
	}

	return -1;

}

int ServiceMsgPeer::cache_msg(MessageInfo &msgInfo)
{
	CacheMsgNode *pnode = new CacheMsgNode();
	if(pnode == NULL)
	{
		return -1;
	}
	pnode->unPacketNo = msgInfo.m_head->unPacketNO;
	pnode->des_adr = &(msgInfo.s_head->desAdr);
	pnode->msg = msgInfo.msg->duplicate();

	m_cache_list.insert_tail(pnode);

	return 0;
}

void ServiceMsgPeer::remove_cache_msg_from_tail()
{
	CacheMsgNode *info = m_cache_list.delete_tail();
	if(info != NULL)
	{
		info->msg->release();
		delete info;
	}
}

/*
int ServiceMsgPeer::SendMsg(MessageInfo &msgInfo)
{
	if(CacheMsg(msgInfo) == -1)
	{
		return -1;
	}

	if(m_currentStatus == STATUS_NORMAL)
	{
		if(m_unCurrentServiceID == OBJ_ID_NONE)
		{
			if(msgInfo.s_head->desAdr.unServiceID == OBJ_ID_NONE)
			{
				//query entity position
				QueryLocation(msgInfo.m_head->unPacketNO);
			}
			else
			{
				m_unCurrentServiceID = msgInfo.s_head->desAdr.unServiceID;
			}
		}
		else
		{
			msgInfo.s_head->desAdr.unServiceID = m_unCurrentServiceID;
		}
	}

	if(m_currentStatus == STATUS_NORMAL)
	{
		//send msg

		return COMMUNICATION_MGR_INSTANCE::instance()->sendMsg(ENDPOINT_TYPE_SERVICE, msgInfo.s_head->desAdr, msgInfo.msg);
	}
	
	return 0;
}

int ServiceMsgPeer::MsgAck(MessageInfo &msgInfo)
{
	if(m_blockHead == NULL)
	{
		return -1;
	}

	ACE_UINT32 t = m_blockHead->unOffset + m_blockHead->s_idx;

	if(t != msgInfo.m_head->unPacketNO)
	{
		return -1;
	}

	//release msg
	m_blockHead->msgList[m_blockHead->s_idx].msg->release();

	m_blockHead->s_idx ++;

	if(m_blockHead->s_idx >= MSG_PEER_BLOCK_NODE_COUNT)
	{
		m_blockHead->s_idx = m_blockHead->e_idx = 0;

		if(m_blockHead == m_blockTail)
		{
			m_blockHead->unOffset = m_blockTail->unOffset + MSG_PEER_BLOCK_NODE_COUNT;
		}
		else
		{
			MsgPeerBlock *t_block = m_blockHead;
			m_blockHead->unOffset = m_blockTail->unOffset + MSG_PEER_BLOCK_NODE_COUNT;
			m_blockHead = m_blockHead->next;
			m_blockHead->prev = NULL;
			m_blockTail->next = t_block;
			t_block->prev = m_blockTail;
			t_block->next = NULL;
			m_blockTail = t_block;
		}
	}

	return 0;
}

int ServiceMsgPeer::CacheMsg(MessageInfo &msgInfo)
{
	if(m_currentBlock == NULL)
	{
		return -1;
	}

	ACE_UINT32 t = m_currentBlock->unOffset + m_currentBlock->e_idx;

	msgInfo.m_head->unPacketNO = t;

	//cache
	msgInfo.p_head->unCtrlCode = msgInfo.p_head->unCtrlCode ^ (~SERVICE_MESSAGE_CTRL_NEED_QUERY_LOCATION);
	m_currentBlock->msgList[m_currentBlock->e_idx].msg = msgInfo.msg->duplicate();
	m_currentBlock->msgList[m_currentBlock->e_idx].s_head = msgInfo.s_head;

	m_currentBlock->e_idx ++;

	if(m_currentBlock->e_idx >= MSG_PEER_BLOCK_NODE_COUNT)
	{
		if(CreateNewBlock(m_currentBlock->unOffset + MSG_PEER_BLOCK_NODE_COUNT) == -1)
		{
			m_currentBlock->e_idx --;
			return -1;
		}

		m_currentBlock = m_blockTail;
	}

	return 0;
}

void ServiceMsgPeer::UpdateLocation(ACE_UINT32 unServiceID, ACE_UINT32 unPacketNo)
{
	if(m_currentStatus == STATUS_NORMAL)
	{
		return;
	}

	if(m_blockHead == NULL)
	{
		return;
	}

	ACE_UINT32 t = m_blockHead->unOffset + m_blockHead->s_idx;

	if(t != unPacketNo)
	{
		return;
	}

	m_currentStatus = STATUS_NORMAL;

	m_unCurrentServiceID = unServiceID;

	MsgPeerBlock *t_block = m_blockHead;

	while(true)
	{
		int i;
		MsgPeerNode *pNode;
		for(i = t_block->s_idx;i < t_block->e_idx;i ++)
		{
			pNode = &t_block->msgList[i];
			
			//send msg
			ACE_Message_Block *msg = pNode->msg->duplicate();
			if(COMMUNICATION_MGR_INSTANCE::instance()->sendMsg(ENDPOINT_TYPE_SERVICE, pNode->s_head->desAdr, msg) == -1)
			{
				msg->release();
			}
		}

		if(t_block == m_currentBlock)
		{
			break;
		}

		t_block = t_block->next;
	}
}

void ServiceMsgPeer::QueryLocation(ACE_UINT32 unPacketNo)
{
	if(m_currentStatus == STATUS_NORMAL)
	{
		m_currentStatus = STATUS_SEARCH;
		m_nQueryCount = 0;
	}

	if(m_nQueryCount == 0)
	{
		//query
		BaseService::instance()->queryObjLocation(m_unAdapterID, m_unObjID, unPacketNo);
	}

	m_nQueryCount = (m_nQueryCount + 1) % MAX_QUERY_INTERVAL;
}

*/