#include "BroadcastMgr.h"
#include "..\..\GameBase\res\GameConfig.h"

#include "..\..\GameBase\Common\GameUtils.h"
#include "..\..\GameBase\res\ItemResMgr.h"
#include "..\Map.h"

BroadcastMgr::BroadcastMgr()
{
	m_unCounter = 0;
	m_head = m_tail = 0;
}

BroadcastMgr::~BroadcastMgr()
{
	
}

void BroadcastMgr::init()
{
	m_unCounter = 0;
	m_head = m_tail = 0;
}

void BroadcastMgr::add_message(char *name, ACE_UINT32 unType, ACE_UINT32 unItemID, ACE_UINT32 unParam)
{
	ACE_OS::memcpy(m_queue[m_tail].name, name, sizeof(char) * MAX_CHARACTER_LENGTH);
	m_queue[m_tail].name[MAX_CHARACTER_LENGTH] = '\0';

	m_queue[m_tail].unType = unType;
	m_queue[m_tail].unItemID = unItemID;
	m_queue[m_tail].unParam = unParam;
// 	m_queue[m_tail].unCoin = unCoin;
// 	m_queue[m_tail].unPowerPoint = unPowerPoint;

	m_tail = (m_tail + 1) % MAX_BROADCAST_MESSAGE_COUNT;

	m_unCounter ++;

	if(m_head == m_tail)
	{
		m_head = (m_head + 1) % MAX_BROADCAST_MESSAGE_COUNT;
	}
}

void BroadcastMgr::send_info(Map *map, ObjAdr &targetAdr, ACE_UINT32 unSN)
{
	MsgGetBroadcastMessageResponse *response = (MsgGetBroadcastMessageResponse *)public_send_buff;

	response->nResult = 0;
	response->unSN = unSN;
	response->unCurrentCounter = m_unCounter;

	int c = 0;

	int idx = m_head;

	while(idx != m_tail)
	{
		response->list[c] = m_queue[idx];
		c ++;
		idx = (idx + 1) % MAX_BROADCAST_MESSAGE_COUNT;
	}

	response->unCount = c;

	map->sendMsg(SERVICE_MESSAGE_TYPE_USER, MSG_GET_BROADCAST_MESSAGE_RESPONSE, (char *)response, sizeof(MsgGetBroadcastMessageResponse), targetAdr);
	map->send_response_end(map->m_unUserID, unSN);
}