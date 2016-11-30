#include "ClientSession.h"
#include "..\..\Base\Communication\CommunicationMgr.h"
#include "..\Game Network\TCPEndPoint.h"

#define CLIENT_LOST_TIMEOUT 10

#define VERIFY_ID(a, b) ((((ACE_UINT64)a) << 32) | b)

ClientSession::ClientSession(ACE_UINT32 unID, ACE_UINT32 unSessionID, BaseAdapter *parent, ObjAdr entityAdr)
:BaseObj(unID, parent)
{
	setSessionID(unSessionID);
	m_entityAdr = entityAdr;
	m_unLostConnectionCounter = 0;
}

ClientSession::~ClientSession()
{
	
}

void ClientSession::setSessionID(ACE_UINT32 unSessionID)
{
	if(m_unSessionID == unSessionID)
	{
		return;
	}

	closeClientConnection(m_unSessionID, m_unID);

	m_unSessionID = unSessionID;

	m_verifyID = VERIFY_ID(m_unSessionID, m_unID);
}

void ClientSession::setEntityAdr(ObjAdr entityAdr)
{
	m_entityAdr = entityAdr;
}

int ClientSession::dealMsg(MessageInfo &msgInfo)
{
	if((msgInfo.p_head->unCtrlCode & SERVICE_MESSAGE_CTRL_TO_INTERNET) != 0)
	{

		msgInfo.p_head->unCtrlCode = msgInfo.p_head->unCtrlCode &~(SERVICE_MESSAGE_CTRL_FROM_INTERNET | SERVICE_MESSAGE_CTRL_TO_INTERNET);
		msgInfo.s_head->desAdr.unServiceID = 0;
		msgInfo.s_head->desAdr.unAdapterID = m_unSessionID;
		msgInfo.s_head->desAdr.unObjID = m_unID;

		MessageInfo info = msgInfo;
		info.msg = info.msg->duplicate();
		
		if(COMMUNICATION_MGR_INSTANCE::instance()->sendMsg(ENDPOINT_TYPE_TCP_INTERNET, info.s_head->desAdr, info.msg) == -1)
		{
			info.msg->release();
			return -1;
		}

		return 0;
	}
	if((msgInfo.p_head->unCtrlCode & SERVICE_MESSAGE_CTRL_FROM_INTERNET) != 0)
	{
		if(m_verifyID != VERIFY_ID(msgInfo.s_head->srcAdr.unAdapterID, msgInfo.s_head->srcAdr.unObjID))
		{
			closeClientConnection(msgInfo.s_head->srcAdr.unAdapterID, msgInfo.s_head->srcAdr.unObjID); 
		}
		else
		{
			m_unLostConnectionCounter = 0;
			msgInfo.p_head->unCtrlCode = msgInfo.p_head->unCtrlCode &~(SERVICE_MESSAGE_CTRL_FROM_INTERNET | SERVICE_MESSAGE_CTRL_TO_INTERNET);
			msgInfo.s_head->desAdr = m_entityAdr;

			MessageInfo info = msgInfo;
			info.msg = info.msg->duplicate();
			return this->sendMsg(msgInfo);
		}
	}
	
	

	return 0;
}

void ClientSession::closeClientConnection(ACE_UINT32 unSessionID, ACE_UINT32 unID)
{
	closeClientConnection(VERIFY_ID(unSessionID, unID));
}

void ClientSession::closeClientConnection(ACE_UINT64 verifyID)
{
	
}

void ClientSession::run()
{
	if(m_unLostConnectionCounter >= CLIENT_LOST_TIMEOUT)
	{
		closeClientConnection(m_verifyID);
		return;
	}
	m_unLostConnectionCounter ++;
}