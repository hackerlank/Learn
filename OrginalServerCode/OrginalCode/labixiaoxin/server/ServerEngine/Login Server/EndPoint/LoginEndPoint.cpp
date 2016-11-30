#include "LoginEndPoint.h"

#if _MEMORY_DEBUG
#include "../../GameBase/Common/debugnew.h"
#define new new(__FILE__, __LINE__)
#endif


LoginEndPoint::LoginEndPoint(ACE_Message_Queue<ACE_MT_SYNCH> *recvQueue, char *strIP, ACE_UINT32 unListenPort)
:ClientEndPoint(recvQueue, strIP, unListenPort)
{
	m_unPeerMaxConnection = 1;
	//m_unListenPort = 1500;
	m_unPeerIDCounter = 1;
	m_bReliable = false;
	m_unAdapterID = ADAPTER_LOGIN_MGR;
}

LoginEndPoint::~LoginEndPoint()
{

}

int LoginEndPoint::parse_connection_init_data(char *buff, int size, ConnectionInitData &info)
{
	info.unPeerID = m_unPeerIDCounter;
	info.strSession[0] = '\0';

	//send create login obj msg
	MessageInfo msgInfo;

	if(allocMessageWithInfo(msgInfo, sizeof(MsgServiceObjOpArg), SERVICE_MESSAGE_TYPE_SYSTEM, OBJ_ID_NONE, ADAPTER_LOGIN_MGR, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, MSG_CREATE_BASE_OBJ) == -1)
	{
		return -1;
	}

	MsgServiceObjOpArg *body = (MsgServiceObjOpArg *)msgInfo.body;
	body->unID = info.unPeerID;

	if(this->putMsg(msgInfo.msg) == -1)
	{
		msgInfo.msg->release();
		return -1;
	}
	
	m_unPeerIDCounter ++;
	if(m_unPeerIDCounter == 0)
	{
		m_unPeerIDCounter = 1;
	}

	return 0;
}

ClientConnection *LoginEndPoint::newConnection()
{
	ClientConnection *t = new ClientConnection();

	if(t == NULL)
	{
		return NULL;
	}

	t->set_info(0, 0, false);

	return t;
}

