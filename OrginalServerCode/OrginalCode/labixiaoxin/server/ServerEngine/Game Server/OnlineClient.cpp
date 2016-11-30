#include "OnlineClient.h"
#include "..\Base\Service\BaseAdapter.h"

//#define SESSION_CHARACTER_TBL_LEN 74
#define SESSION_CHARACTER_TBL_LEN 62

static char *g_session_character_tbl = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@#$%^&*()-=";

OnlineClient::OnlineClient(ACE_UINT32 unID, BaseAdapter *parent)
:BaseObj(unID, parent)
{
	/*m_unSessionID = 0;*/
	m_strSession[0] = '\0';
}

OnlineClient::~OnlineClient()
{

}

int OnlineClient::obj_init(void *arg, ACE_UINT32 unArgLen)
{
	if(arg == NULL || unArgLen != sizeof(ObjAdr))
	{
		return -1;
	}

	ObjAdr *p = (ObjAdr *)arg;

	m_loginResponseAdr = *p;

	return BaseObj::obj_init(arg, unArgLen);
}


int OnlineClient::start_running()
{
	send_gateway_request();
	return 0;
}

int OnlineClient::deal_msg(MessageInfo &msgInfo)
{
	if(msgInfo.p_head->unType == SERVICE_MESSAGE_TYPE_USER)
	{
		switch(msgInfo.m_head->unType)
		{
		case MSG_GATEWAY_PROXY_INIT_DATA_RESPONSE:
			{
				MsgGatewayProxyInitDataResponse *body = (MsgGatewayProxyInitDataResponse *)msgInfo.body;

				//if(body->unLoginAdapter != m_loginResponseAdr.unAdapterID || body->unLoginID != m_loginResponseAdr.unObjID)
				if(!is_same_login(body->unLoginID))
				{
					//send_login_info(0, 0, body->unLoginAdapter, body->unLoginID);
				}
				else
				{
					send_login_info(body->unIP, body->unPort, m_loginResponseAdr);
				}
			}
			break;
		}
	}

	return BaseObj::deal_msg(msgInfo);
}


//void OnlineClient::send_login_info(ACE_UINT32 unIP, ACE_UINT32 unPort, ACE_UINT32 unAdapterID, ACE_UINT32 unLoginID)
void OnlineClient::send_login_info(ACE_UINT32 unIP, ACE_UINT32 unPort, ObjAdr &desAdr)
{
	MsgQueryLoginInfoResponse info;

	info.unIP = unIP;
	info.unPort = unPort;
	info.unUserID = m_unID;
	ACE_OS::strncpy(info.strSession, m_strSession, CLIENT_SESSION_LEN + 1);

	sendMsg(SERVICE_MESSAGE_TYPE_USER, MSG_QUERY_LOGIN_INFO_RESPONSE, (char*)&info, sizeof(MsgQueryLoginInfoResponse), desAdr.unServiceID, desAdr.unAdapterID, desAdr.unObjID);
}

void OnlineClient::generate_session_id()
{
	int t = 0;

	for(int i = 0;i < CLIENT_SESSION_LEN;i ++)
	{
		t = rand() % SESSION_CHARACTER_TBL_LEN;
		m_strSession[i] = g_session_character_tbl[t];
	}

	m_strSession[CLIENT_SESSION_LEN] = '\0';
}

void OnlineClient::set_login_response_adr(ObjAdr &adr)
{
	//m_unLoginID = unLoginID;
	m_loginResponseAdr = adr;

	if(m_unObjStatus == SERVICE_OBJ_RUN)
	{
		send_gateway_request();
	}
}

void OnlineClient::send_gateway_request()
{
	generate_session_id();

	MsgGatewayProxyInitDataRequest info;

	info.unLoginAdapter = m_loginResponseAdr.unAdapterID;
	info.unLoginID = m_loginResponseAdr.unObjID;
	ACE_OS::strncpy(info.strSession, m_strSession, CLIENT_SESSION_LEN + 1);

	if(sendMsg(SERVICE_MESSAGE_TYPE_USER, MSG_GATEWAY_PROXY_INIT_DATA_REQUEST, (char*)&info, sizeof(MsgGatewayProxyInitDataRequest), OBJ_ID_NONE, ADAPTER_GATEWAY_MGR, m_unID) == -1)
	{
		//send login fail
		send_login_info(0, 0, m_loginResponseAdr);
	}
}

bool OnlineClient::is_same_login(ACE_UINT32 unLoginID)
{

	return (unLoginID == m_loginResponseAdr.unObjID);
}