#include "UserInfoEndPoint.h"

UserInfoEndPoint::UserInfoEndPoint(ACE_Message_Queue<ACE_MT_SYNCH> *recvQueue,char *strIP, ACE_UINT32 unListenPort)
:PhpEndPoint(recvQueue, strIP, unListenPort)
{
	
}

int UserInfoEndPoint::put_msg(ACE_Message_Block *msg, PhpConnection *connection)
{
	if(m_connectionMap.bind(m_unPeerIDCounter, connection) != 0)
	{
		return -1;
	}

	MessageInfo tmpInfo;

	parseMsg(tmpInfo, msg);
	tmpInfo.s_head->desAdr.unAdapterID = ADAPTER_USER_INFO_MGR;
	tmpInfo.s_head->desAdr.unObjID = 0;
	tmpInfo.s_head->srcAdr.unObjID = m_unPeerIDCounter;

	if(this->putMsg(msg) == -1)
	{
		return -1;
	}

	m_unPeerIDCounter ++;
	if(m_unPeerIDCounter == 0)
	{
		m_unPeerIDCounter = 1;
	}

	return 0;
}