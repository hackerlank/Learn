#include "GatewaySession.h"

#include "ace\OS_NS_string.h"

#include "..\Base\Communication\CommunicationMgr.h"
#include "..\GameBase\Game Network\ClientEndPoint.h"
#include "..\Base\Service\BaseService.h"
#include "..\GameBase\Protocol\DBProtocol.h"
#include "..\GameBase\Common\GameUtils.h"
#include "..\Base\Service\ServiceConfigMgr.h"

#define MAX_GATEWAY_SESSION_LIVE ( 5*60)


ACE_UINT32 GatewaySession::m_unGameServerID = 0;
ACE_UINT32 GatewaySession::m_unUserInfoServerID = 0;
#define MAX_LOBODY_RELEASE (delete[]body)

GatewaySession::GatewaySession(ACE_UINT32 unID, BaseAdapter *parent)
:ClientObj(unID, parent)
{
	m_strSession[0] = '\0';
	m_unCurrentCharacterID = 0;
	//m_unLevel = 0;

	ACE_OS::memset(m_CharacterList, 0, sizeof(CharacterInfo) * MAX_PLAYER_PER_ACCOUNT);

	if(m_unGameServerID == 0)
	{
		m_unGameServerID = SERVICE_CONFIG_MGR_INSTANCE::instance()->get_service_instance_id("Game Server");
		m_unUserInfoServerID = SERVICE_CONFIG_MGR_INSTANCE::instance()->get_service_instance_id("Test User Info Server");
	}

	m_unActiveTimer = 0;
	m_isDestroyMsg = false;
	m_unLoginID = 0;

	m_bDoTimeout = true;

	m_unGatewayStep = GATEWAY_STEP_NORMAL;
}

GatewaySession::~GatewaySession()
{

}

int GatewaySession::deal_client_msg(MessageInfo &msgInfo)
{
	/*printf("get msg type = 0x%08x,character_id = %d\n", msgInfo.m_head->unType, m_unID);*/

	bool deal_flag = false;

	m_unCurrentSig = m_unLoginID;

	if(msgInfo.p_head->unType == SERVICE_MESSAGE_TYPE_USER)
	{
		//CLogBase *pLog = BaseService::GetLogInstance();
		//sprintf(pLog->m_szLogBuffer, "[%s][%d]:deal_client_msg = %d",__FILE__, __LINE__, msgInfo.m_head->unType);
		//pLog->RecordLog(Log_Type_Error, pLog->m_szLogBuffer);
		switch(msgInfo.m_head->unType)
		{
		case MSG_QUERY_CHARACTER_REQUEST:
			//获取角色信息请求
			//this->add_db_request(ADAPTER_DB_USER_MGR, MSG_DB_CHARACTER_INFO, (char *)msgInfo.body, sizeof(MsgCharacterQueryRequest));
			{
				if(m_unGatewayStep == GATEWAY_STEP_NORMAL)
				{
					MsgQueryCharaterRequest *body = (MsgQueryCharaterRequest *)msgInfo.body;
					m_unCurrentRequestSN = body->unSN;

					//MsgDBQueryCharacterInfoRequest msg_request;

					this->add_db_request(ADAPTER_DB_USER_MGR, MSG_DB_QUERY_CHARACTER_INFO, NULL, 0);
					
					m_unGatewayStep = GATEWAY_STEP_QUERY;
				}
				else
				{
					send_response_end(-1);
				}
				deal_flag = true;
				m_oCommunicationRecord.clear();
			}
			
			break;
		case MSG_SELECT_CHARACTER_REQUEST:
			//获取角色信息请求
			//this->add_db_request(ADAPTER_DB_USER_MGR, MSG_DB_CHARACTER_INFO, (char *)msgInfo.body, sizeof(MsgCharacterQueryRequest));
			{
				if(m_unGatewayStep == GATEWAY_STEP_WAIT_SELECT)
				{
					MsgSelectCharacterRequest *body = (MsgSelectCharacterRequest *)msgInfo.body;
					m_unCurrentRequestSN = body->unSN;
					int idx = -1;

					if(body->unCharacterID != 0)
					{
						for(int i = 0;i < MAX_PLAYER_PER_ACCOUNT;i ++)
						{
							if(m_CharacterList[i].unItemID == body->unCharacterID)
							{
								idx = i;
								break;
							}
						}
					}
					
					if(idx != -1)
					{
						//set to map 
						if(m_CharacterList[idx].unLevel == 0)
						{
							//create db msg
							if(ACE_OS::strlen(body->name) == 0)
							{
								send_response_end(-1);
							}
							else
							{
								MsgDBCreateCharacterRequest msg_request;

								msg_request.unCharacterID = body->unCharacterID;
								ACE_OS::memcpy(msg_request.name, body->name, MAX_CHARACTER_LENGTH + 1);
								msg_request.unPlayerID = body->unPlayerID;

								this->add_db_request(ADAPTER_DB_USER_MGR, MSG_DB_CREATE_CHARACTER, (char *)&msg_request, sizeof(MsgDBCreateCharacterRequest));

								m_unGatewayStep = GATEWAY_STEP_CREATE;
							}
						}
						else
						{
							send_select_msg(m_CharacterList[idx].unItemID);

							m_unGatewayStep = GATEWAY_STEP_NORMAL;
						}
					}
					else
					{
						//send fail msg
						send_response_end(-1);
					}
				}
				else
				{
					send_response_end(-1);
				}

				/*
				MsgDBCharacterQueryRequest msg_request;
				msg_request.unGiftSenderID = body->unGiftSenderID;
				msg_request.unGiftItemID = body->unGiftItemID;

				this->add_db_request(ADAPTER_DB_USER_MGR, MSG_DB_CHARACTER_INFO, (char *)&msg_request, sizeof(MsgDBCharacterQueryRequest));
				*/
				deal_flag = true;
			}
			
			break;
		}
	}

	//转发消息给内网
	if(!deal_flag && m_unCurrentCharacterID != 0 && GATEWAY_STEP_NORMAL == m_unGatewayStep)
	{
		this->forward_msg(msgInfo, OBJ_ID_NONE, ADAPTER_MAP_MGR, m_unCurrentCharacterID);
		//this->forward_msg(msgInfo, OBJ_ID_NONE, ADAPTER_MAP_MGR, m_unCharacterID);
	}

	return ClientObj::deal_client_msg(msgInfo);
}

int GatewaySession::deal_other_msg(MessageInfo &msgInfo)
{
	if(msgInfo.p_head->unType == SERVICE_MESSAGE_TYPE_USER)
	{
		//CLogBase *pLog = BaseService::GetLogInstance();
		//sprintf(pLog->m_szLogBuffer, "[%s][%d]:deal_other_msg = %d",__FILE__, __LINE__, msgInfo.m_head->unType);
		//pLog->RecordLog(Log_Type_Error, pLog->m_szLogBuffer);
		switch(msgInfo.m_head->unType)
		{
		case MSG_QUERY_LOGIN_INFO_REQUEST:
			{
				MsgQueryLoginInfoRequest *body = (MsgQueryLoginInfoRequest *)msgInfo.body;


				m_unLoginID = body->unLoginID;

				GameUtils::generate_session_id(m_strSession);

				ClientEndPoint *endPoint = (ClientEndPoint *)COMMUNICATION_MGR_INSTANCE::instance()->getEndPoint(ENDPOINT_TYPE_TCP_INTERNET);

				bool flag = false;

				if(endPoint != NULL)
				{
					if(endPoint->reset_peer(m_unID, m_strSession) != NULL)
					{
						flag = true;
					}
				}

				MsgQueryLoginInfoResponse info;

				ACE_OS::memset(&info, 0, sizeof(MsgQueryLoginInfoResponse));

				if(flag)
				{
					ACE_INET_Addr t_adr(BaseService::instance()->m_ownServiceInfo->publicAdr.port, BaseService::instance()->m_ownServiceInfo->publicAdr.ip);
					info.unIP = t_adr.get_ip_address();
					info.unPort = t_adr.get_port_number();
					info.unUserID = m_unID;
					ACE_OS::strncpy(info.strSession, m_strSession, CLIENT_SESSION_LEN + 1);
				}

				m_unGatewayStep = GATEWAY_STEP_NORMAL;

				sendMsg(SERVICE_MESSAGE_TYPE_USER, MSG_QUERY_LOGIN_INFO_RESPONSE, (char*)&info, sizeof(MsgQueryLoginInfoResponse), msgInfo.s_head->srcAdr);
			}
			break;
		}
	}

	return ClientObj::deal_other_msg(msgInfo);
}

int GatewaySession::deal_db_msg(ACE_UINT32 unType, void *msg)
{
	/*printf("get db msg type = 0x%08x\n", unType);*/

	switch(unType)
	{
	case MSG_DB_QUERY_CHARACTER_INFO:
		{
			MsgDBQueryCharacterInfoResponse *body = (MsgDBQueryCharacterInfoResponse *)msg;
			ACE_OS::memcpy(m_CharacterList, body->list, sizeof(CharacterInfo) * MAX_PLAYER_PER_ACCOUNT);

			if(m_unGatewayStep == GATEWAY_STEP_QUERY && m_CharacterList[0].unLevel >= 0)
			{
				send_character_query_response();
				m_unGatewayStep = GATEWAY_STEP_WAIT_SELECT;
			}
			else
			{
				printf("o,shit\n");
			}
		}
		
		break;
	case MSG_DB_CREATE_CHARACTER:
		{
			MsgDBCreateCharacterResponse *body = (MsgDBCreateCharacterResponse *)msg;

			if(body->nResult == 0)
			{
				set_character_create_done(body->unCharacterID, body->name);
			}

			if(m_unGatewayStep == GATEWAY_STEP_CREATE)
			{
				if(body->nResult != 0)
				{
					send_response_end(body->nResult);
					m_unGatewayStep = GATEWAY_STEP_WAIT_SELECT;
				}
				else
				{
					m_unCurrentSig = m_unLoginID;
					send_select_msg(body->unCharacterID);
					m_unGatewayStep = GATEWAY_STEP_NORMAL;
				}
			}
			else
			{
				printf("o,fuck\n");
			}
		}
		break;
	default:
		break;
	}

	return SERVICE_OBJ_DB_REQUEST_DONE;
}

void GatewaySession::set_character_create_done(ACE_UINT32 unCharacterID, char *name)
{
	//ACE_OS::memcpy(m_CharacterList, body->list, sizeof(CharacterInfo) * MAX_PLAYER_PER_ACCOUNT);
	for(int i = 0;i < MAX_PLAYER_PER_ACCOUNT;i ++)
	{
		if(m_CharacterList[i].unItemID == unCharacterID)
		{
			if(m_CharacterList[i].unLevel == 0)
			{
				m_CharacterList[i].unLevel = 1;
				ACE_OS::memcpy(m_CharacterList[i].name, name, MAX_CHARACTER_LENGTH + 1);

#if 0 //guo
				MsgCharacterLevelUpdateRequest tmpInfo;
				tmpInfo.unCharacterID = unCharacterID;
				tmpInfo.unLevel = 1;
				this->sendMsg(SERVICE_MESSAGE_TYPE_USER, MSG_CHARACTER_LEVEL_UPDATE_REQUEST,(char *)&tmpInfo, sizeof(MsgCharacterLevelUpdateRequest), m_unUserInfoServerID, ADAPTER_USER_INFO_MGR, OBJ_ID_NONE);
#endif
			}
			break;
		}
	}
}

void GatewaySession::create_done()
{
	//this->sendMsg(SERVICE_MESSAGE_TYPE_USER, MSG_GATEWAY_PROXY_INIT_DATA_REQUEST, NULL, 0, GAME_SERVER_ID, ADAPTER_GAME_SERVER_MGR, m_unID);

	ClientObj::create_done();
}

int GatewaySession::start_destroy()
{
	ClientEndPoint *endPoint = (ClientEndPoint *)COMMUNICATION_MGR_INSTANCE::instance()->getEndPoint(ENDPOINT_TYPE_TCP_INTERNET);

	if(endPoint != NULL)
	{
		endPoint->delete_peer(m_unID);
	}

	/*
	MsgDestroyGatewayProxyRequest body;
	body.unID = m_unID;
	body.unLoginID = m_unLoginID;

	this->sendMsg(SERVICE_MESSAGE_TYPE_USER, MSG_GATEWAY_PROXY_DESTROY_REQUEST, (char *)&body, sizeof(MsgDestroyGatewayProxyRequest), m_unGameServerID, ADAPTER_GAME_SERVER_MGR, OBJ_ID_NONE);
	*/
	return ClientObj::start_destroy();
}

int GatewaySession::parse_into_intranet_msg(MessageInfo &msgInfo,char *buff, int size)
{
	m_stream.reset(buff, size);

	ACE_UINT32 unType;
	ACE_UINT32 unSN;
	m_isDestroyMsg = false;

	if(m_stream.readInt(unType) == -1)
	{
		return -1;
	}
	if(m_stream.readInt(unSN) == -1)
	{
		return -1;
	}

	msgInfo.msg = NULL;
	int nRet = -1;

	CommunicationRecord stRecord;
	stRecord.unCmd = unType;
	stRecord.unRecvTime = GetTickCount();
	stRecord.unSendTime = 0;
	m_oCommunicationRecord.insert(std::make_pair(unSN, stRecord));

	CLogBase *pLog = BaseService::GetLogInstance();
	sprintf(pLog->m_szLogBuffer, "[%s][%d]:recv cmd = %x, characterid=%d",__FILE__, __LINE__, unType,get_current_id());
	pLog->RecordLog(Log_Type_Info, pLog->m_szLogBuffer);

	switch(unType)
	{
	case MSG_QUERY_CHARACTER_REQUEST:
		{
			nRet = allocMessageWithInfo(msgInfo, sizeof(MsgQueryCharaterRequest), SERVICE_MESSAGE_TYPE_USER, 
				OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, unType);
			if(nRet == 0)
			{
				MsgQueryCharaterRequest *body = (MsgQueryCharaterRequest *)msgInfo.body;
				body->unSN = unSN;

			}
		}
		break;
	case MSG_SELECT_CHARACTER_REQUEST:
		{
			nRet = allocMessageWithInfo(msgInfo, sizeof(MsgSelectCharacterRequest), SERVICE_MESSAGE_TYPE_USER, 
				OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, unType);
			if(nRet == 0)
			{
				MsgSelectCharacterRequest *body = (MsgSelectCharacterRequest *)msgInfo.body;
				body->unSN = unSN;
				if(m_stream.readInt(body->unCharacterID) == -1)
				{
					nRet = -1;
					break;
				}
				if(m_stream.readString(body->name, MAX_CHARACTER_LENGTH) == -1)
				{
					nRet = -1;
				}
				if(m_stream.readInt(body->unPlayerID) == -1)
				{
					nRet = -1;
				}
			}
		}
		break;
	case MSG_RESET_MAP_REQUEST:
		{
			nRet = allocMessageWithInfo(msgInfo, sizeof(MsgResetMapRequest), SERVICE_MESSAGE_TYPE_USER,
				OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, unType);
			if(nRet == 0)
			{
				MsgResetMapRequest *body = (MsgResetMapRequest*)msgInfo.body;
				body->unSN = unSN;
				if(m_stream.readInt(body->unMapID) == -1)
				{
					nRet = -1;
					break;
				}
			}
		}
		break;
	case MSG_UPDATE_PLAYER_LIST_REQUEST:
		{
			nRet = allocMessageWithInfo(msgInfo, sizeof(MsgUpdatePlayerListRequest), SERVICE_MESSAGE_TYPE_USER, 
				OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, unType);
			if(nRet == 0)
			{
				MsgUpdatePlayerListRequest *body = (MsgUpdatePlayerListRequest *)msgInfo.body;
				body->unSN = unSN;
				if(m_stream.readInt((ACE_UINT32&)body->unType) == -1)
				{
					nRet = -1;
					break;
				}

				int i = 0;

				for(i = 0;i < MAX_PLAYER_SELECTED_COUNT;i ++)
				{
					if(m_stream.readInt((ACE_UINT32&)body->list[i]) == -1)
					{
						break;
					}
				}

				if(i < MAX_PLAYER_SELECTED_COUNT)
				{
					nRet = -1;
					break;
				}

				for(i = 0;i < MAX_PLAYER_SELECTED_COUNT;i ++)
				{
					if(m_stream.readInt((ACE_UINT32&)body->playerSkillList[i]) == -1)
					{
						nRet = -1;
						break;
					}
				}
			}
		}
		break;
	case MSG_SELECT_EQUIPMENT_REQUEST:
		{
			nRet = allocMessageWithInfo(msgInfo, sizeof(MsgSelectEquipmentRequest), SERVICE_MESSAGE_TYPE_USER, 
				OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, unType);
			if(nRet == 0)
			{
				MsgSelectEquipmentRequest *body = (MsgSelectEquipmentRequest *)msgInfo.body;
				body->unSN = unSN;
				if(m_stream.readInt((ACE_UINT32&)body->idx) == -1 || m_stream.readInt((ACE_UINT32&)body->unPlayerID) == -1 ||
					m_stream.readInt((ACE_UINT32&)body->equipment_type) == -1)
				{
					nRet = -1;
				}
			}
		}
		break;
	case MSG_ENTER_MAP_REQUEST:
		{
			nRet = allocMessageWithInfo(msgInfo, sizeof(MsgEnterMapRequest), SERVICE_MESSAGE_TYPE_USER, 
				OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, unType);
			if(nRet == 0)
			{
				MsgEnterMapRequest *body = (MsgEnterMapRequest *)msgInfo.body;
				body->unSN = unSN;
				if(m_stream.readInt(body->unMapID) == -1 || m_stream.readInt(body->specialMap) == -1 || m_stream.readInt(body->unFriendID) == -1 || m_stream.readInt(body->unMultEnergy) == -1/*多倍体力*/)
				{
					nRet = -1;
				}
			}
		}
		break;
	case MSG_ASSIST_FRIENDSHIP_REQUEST:
		{
			nRet = allocMessageWithInfo(msgInfo, sizeof(MsgAssistFriendshipRequest), SERVICE_MESSAGE_TYPE_USER, 
				OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, unType);
			if(nRet == 0)
			{
				MsgAssistFriendshipRequest *body = (MsgAssistFriendshipRequest *)msgInfo.body;
				body->unSN = unSN;
				for (int i=0;i<MAX_RANDOM_CHARACTER;++i)
				{
					if (m_stream.readInt(body->characterIDList[i]) == -1)
					{
						nRet = -1;
						break;
					}
				}
			}
		}break;
	case MSG_GET_MAP_REWARD_REQUEST:
		{
			nRet = allocMessageWithInfo(msgInfo, sizeof(MsgGetMapRewardRequest), SERVICE_MESSAGE_TYPE_USER, 
				OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, unType);
			if(nRet == 0)
			{
				MsgGetMapRewardRequest *body = (MsgGetMapRewardRequest *)msgInfo.body;
				body->unSN = unSN;
				if(m_stream.readInt(body->unMapID) == -1 ||  m_stream.readInt(body->unLaunchCount) == -1 || m_stream.readInt(body->unBellCount) == -1)
				{
					nRet = -1;
					break;
				}
			}
		}
		break;
	case MSG_GET_FRIEND_DETAIL_REQUEST:
		{
			nRet = allocMessageWithInfo(msgInfo, sizeof(MsgGetFriendDetailRequest), SERVICE_MESSAGE_TYPE_USER, 
				OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, unType);
			if(nRet == 0)
			{
				MsgGetFriendDetailRequest *body = (MsgGetFriendDetailRequest *)msgInfo.body;
				body->unSN = unSN;
				body->unPage = 0;
				if(m_stream.readInt(body->unType) == -1 || m_stream.readInt(body->unPage) == -1)
				{
					nRet = -1;//change by xxj 测试使用
				}
			}
		}
		break;
	case MSG_INVITE_FRIEND_REQUEST:
		{
			nRet = allocMessageWithInfo(msgInfo, sizeof(MsgInviteFriendRequest), SERVICE_MESSAGE_TYPE_USER, 
				OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, unType);
			if(nRet == 0)
			{
				MsgInviteFriendRequest *body = (MsgInviteFriendRequest *)msgInfo.body;
				body->unSN = unSN;
				if(m_stream.readInt(body->unFriendID) == -1)
				{
					nRet = -1;
				}
			}
		}
		break;
	case MSG_DELETE_FRIEND_REQUEST:
		{
			nRet = allocMessageWithInfo(msgInfo, sizeof(MsgDeleteFriendRequest), SERVICE_MESSAGE_TYPE_USER, 
				OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, unType);
			if(nRet == 0)
			{
				MsgDeleteFriendRequest *body = (MsgDeleteFriendRequest *)msgInfo.body;
				body->unSN = unSN;
				if(m_stream.readInt(body->unType) == -1 || m_stream.readInt(body->unFriendID) == -1)
				{
					nRet = -1;
				}
			}
		}
		break;
	case MSG_APPLY_INVITATION_REQUEST:
		{
			nRet = allocMessageWithInfo(msgInfo, sizeof(MsgApplyInvitationRequest), SERVICE_MESSAGE_TYPE_USER, 
				OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, unType);
			if(nRet == 0)
			{
				MsgApplyInvitationRequest *body = (MsgApplyInvitationRequest *)msgInfo.body;
				body->unSN = unSN;
				if(m_stream.readInt(body->unFriendID) == -1)
				{
					nRet = -1;
				}
			}
		}
		break;
	case MSG_READ_MAIL_REQUEST:
		{
			nRet = allocMessageWithInfo(msgInfo, sizeof(MsgReadMailRequest), SERVICE_MESSAGE_TYPE_USER, 
				OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, unType);
			if(nRet == 0)
			{
				MsgReadMailRequest *body = (MsgReadMailRequest *)msgInfo.body;
				body->unSN = unSN;
				if(m_stream.readInt(body->m_dwMailID) == -1)
				{
					nRet = -1;
				}
			}
		}
		break;
	case MSG_GET_MAIL_LIST_REQUEST:
		{
			nRet = allocMessageWithInfo(msgInfo, sizeof(MsgGetMailListRequest), SERVICE_MESSAGE_TYPE_USER, 
				OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, unType);
			if(nRet == 0)
			{
				MsgGetMailListRequest *body = (MsgGetMailListRequest *)msgInfo.body;
				body->unSN = unSN;
			}
		}
		break;
	case MSG_DELETE_READ_MAIL_REQUEST:
		{
			nRet = allocMessageWithInfo(msgInfo, sizeof(MsgDeleteReadMailRequest), SERVICE_MESSAGE_TYPE_USER, 
				OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, unType);
			if(nRet == 0)
			{
				MsgDeleteReadMailRequest *body = (MsgDeleteReadMailRequest *)msgInfo.body;
				body->unSN = unSN;
				if(m_stream.readInt(body->m_dwMailID) == -1)
				{
					nRet = -1;
				}
			}
		}
		break;
	case MSG_GET_ALL_MAIL_REWARD_REQUEST:
		{
			nRet = allocMessageWithInfo(msgInfo, sizeof(MsgGetAllMailRewardRequest), SERVICE_MESSAGE_TYPE_USER, 
				OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, unType);
			if(nRet == 0)
			{
				MsgGetAllMailRewardRequest *body = (MsgGetAllMailRewardRequest *)msgInfo.body;
				body->unSN = unSN;
			}
		}
		break;
	case MSG_DELETE_ALL_READ_MAIL_REQUEST:
		{
			nRet = allocMessageWithInfo(msgInfo, sizeof(MsgDeleteAllReadMailRequest), SERVICE_MESSAGE_TYPE_USER, 
				OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, unType);
			if(nRet == 0)
			{
				MsgDeleteAllReadMailRequest *body = (MsgDeleteAllReadMailRequest *)msgInfo.body;
				body->unSN = unSN;
			}
		}
		break;
	case MSG_KEEP_ALIVE_REQUEST:
		{
			nRet = allocMessageWithInfo(msgInfo, sizeof(MsgKeepAliveRequest), SERVICE_MESSAGE_TYPE_USER, 
				OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, unType);
			if(nRet == 0)
			{
				MsgKeepAliveRequest *body = (MsgKeepAliveRequest *)msgInfo.body;
				body->unSN = unSN;
			}
		}
		break;
	case MSG_GET_SIGN_UP_REWARD_REQUEST:
		{
			nRet = allocMessageWithInfo(msgInfo, sizeof(MsgGetSignUpRewardRequest), SERVICE_MESSAGE_TYPE_USER, 
				OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, unType);
			if(nRet == 0)
			{
				MsgGetSignUpRewardRequest *body = (MsgGetSignUpRewardRequest *)msgInfo.body;
				body->unSN = unSN;
			}
		}
		break;
	case MSG_CONVERT_GIFT_BAG_CODE_REQUEST:
		{
			nRet = allocMessageWithInfo(msgInfo, sizeof(MsgConvertGiftBagCodeRequest), SERVICE_MESSAGE_TYPE_USER, 
				OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, unType);
			if(nRet == 0)
			{
				MsgConvertGiftBagCodeRequest *body = (MsgConvertGiftBagCodeRequest *)msgInfo.body;
				body->unSN = unSN;
				if(m_stream.readString(body->m_strGiftBagCode, MAX_GIFT_BAG_CODE_LENGTH) == -1)
				{
					nRet = -1;
				}
			}
		}
		break;
	case MSG_DOUBLE_DROP_LIST_REQUEST:
		{
			nRet = allocMessageWithInfo(msgInfo, sizeof(MsgDoubleDropListRequest), SERVICE_MESSAGE_TYPE_USER, 
				OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, unType);
			if(nRet == 0)
			{
				MsgDoubleDropListRequest *body = (MsgDoubleDropListRequest *)msgInfo.body;
				body->unSN = unSN;
			}
		}break;
	case MSG_TASK_OPERATE_REQUEST:
		{
			nRet = allocMessageWithInfo(msgInfo, sizeof(MsgTaskOperateRequest), SERVICE_MESSAGE_TYPE_USER,
				OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, unType);
			if (nRet == 0)
			{
				MsgTaskOperateRequest *body = (MsgTaskOperateRequest *)msgInfo.body;
				body->unSN = unSN;
				if(m_stream.readInt(body->iTaskID) == -1 || m_stream.readInt(body->unOperateType) == -1)
				{
					nRet = -1;
				}
				//CLogBase *pLog = BaseService::GetLogInstance();
				//sprintf(pLog->m_szLogBuffer, "[%s][%d]:Gateway MSG_TASK_OPERATE_REQUEST taskid = %d, optype=%d",__FILE__, __LINE__, body->iTaskID, body->unOperateType);
				//pLog->RecordLog(Log_Type_Error, pLog->m_szLogBuffer);
			}
		}break;
	case MSG_GOLDEN_TOUCH_REQUEST:
		{
			nRet = allocMessageWithInfo(msgInfo, sizeof(MsgGoldenTouchRequest), SERVICE_MESSAGE_TYPE_USER,
				OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, unType);
			if (nRet == 0)
			{
				MsgGoldenTouchRequest *body = (MsgGoldenTouchRequest *)msgInfo.body;
				body->unSN = unSN;
			}
		}break;
	case MSG_GET_RANDOM_CHARACTER_REQUEST:
		{
			nRet = allocMessageWithInfo(msgInfo, sizeof(MsgRandomCharacterRequest), SERVICE_MESSAGE_TYPE_USER, 
				OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, unType);
			if(nRet == 0)
			{
				MsgRandomCharacterRequest *body = (MsgRandomCharacterRequest *)msgInfo.body;
				body->unSN = unSN;

				if(m_stream.readInt(body->unMapID) == -1)
				{
					nRet = -1;
				}
			}
		}
		break;
	case MSG_GET_LUCK_REQUEST:
		{
			nRet = allocMessageWithInfo(msgInfo, sizeof(MsgGetLuckRequest), SERVICE_MESSAGE_TYPE_USER, 
				OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, unType);
			if(nRet == 0)
			{
				MsgGetLuckRequest *body = (MsgGetLuckRequest *)msgInfo.body;
				body->unSN = unSN;
				if(m_stream.readInt(body->unIsTen) == -1 || m_stream.readInt(body->unBehaviorID) == -1)
				{
					nRet = -1;
				}
			}
		}
		break;
		/*
	case MSG_GET_MORE_LUCK_REQUEST:
		{
			nRet = allocMessageWithInfo(msgInfo, sizeof(MsgGetMoreLuckRequest), SERVICE_MESSAGE_TYPE_USER, 
				OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, unType);
			if(nRet == 0)
			{
				MsgGetMoreLuckRequest *body = (MsgGetMoreLuckRequest *)msgInfo.body;
				body->unSN = unSN;
			
			}
		}
		break;
		*/
	case MSG_GET_LOGIN_REWARD_REQUEST:
		{
			nRet = allocMessageWithInfo(msgInfo, sizeof(MsgGetLoginRewardRequest), SERVICE_MESSAGE_TYPE_USER, 
				OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, unType);
			if(nRet == 0)
			{
				MsgGetLoginRewardRequest *body = (MsgGetLoginRewardRequest *)msgInfo.body;
				body->unSN = unSN;

			}
		}
		break;
	case MSG_GET_GLOBAL_MAP_EVENT_REQUEST:
		{
			nRet = allocMessageWithInfo(msgInfo, sizeof(MsgGetGlobalMapEventRequest), SERVICE_MESSAGE_TYPE_USER, 
				OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, unType);
			if(nRet == 0)
			{
				MsgGetGlobalMapEventRequest *body = (MsgGetGlobalMapEventRequest *)msgInfo.body;
				body->unSN = unSN;

			}
		}
		break;
	case MSG_ITEM_LEVEL_UP_REQUEST:
		{
			nRet = allocMessageWithInfo(msgInfo, sizeof(MsgItemLevelUpRequest), SERVICE_MESSAGE_TYPE_USER, 
				OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, unType);
			if(nRet == 0)
			{
				MsgItemLevelUpRequest *body = (MsgItemLevelUpRequest *)msgInfo.body;
				body->unSN = unSN;
				if(m_stream.readInt(body->unIdx) == -1 || m_stream.readInt(body->unPlayerID) == -1 || m_stream.readInt(body->unLevel) == -1)
				{
					nRet = -1;
				}
			}
		}
		break;
	case MSG_SKILL_LEVEL_UP_REQUEST:
		{
			nRet = allocMessageWithInfo(msgInfo, sizeof(MsgSkillLevelUpRequest), SERVICE_MESSAGE_TYPE_USER, 
				OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, unType);
			if(nRet == 0)
			{
				MsgSkillLevelUpRequest *body = (MsgSkillLevelUpRequest *)msgInfo.body;
				body->unSN = unSN;
				if(m_stream.readInt(body->unSkillID) == -1 /*|| m_stream.readInt(body->skillType) == -1*/ || m_stream.readInt(body->unLevel) == -1)
				{
					nRet = -1;
				}
			}
		}
		break;
	case MSG_FIND_CHARACTER_REQUEST:
		{
			nRet = allocMessageWithInfo(msgInfo, sizeof(MsgFindCharacterRequest), SERVICE_MESSAGE_TYPE_USER, 
				OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, unType);
			if(nRet == 0)
			{
				MsgFindCharacterRequest *body = (MsgFindCharacterRequest *)msgInfo.body;
				body->unSN = unSN;
				if(m_stream.readInt(body->unCharacterID) == -1)
				{
					nRet = -1;
				}
			}
		}
		break;
	case MSG_DELETE_ITEM_REQUEST:
		{
			nRet = allocMessageWithInfo(msgInfo, sizeof(MsgDeleteItemRequest), SERVICE_MESSAGE_TYPE_USER, 
				OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, unType);
			if(nRet == 0)
			{
				MsgDeleteItemRequest *body = (MsgDeleteItemRequest *)msgInfo.body;
				body->unSN = unSN;
				if(m_stream.readInt(body->unDeleteType) == -1 || m_stream.readInt(body->unCount) == -1)
				{
					nRet = -1;
				}

				int i = 0;
				for(i = 0;i < body->unCount;i ++)
				{
					if(m_stream.readInt(body->unIdxList[i]) == -1)
					{
						break;
					}
				}
				if(i < body->unCount)
				{
					nRet = -1;
				}
			}
		}
		break;
	case MSG_GOLD_BUY_REQUEST:
		{
			nRet = allocMessageWithInfo(msgInfo, sizeof(MsgGoldBuyRequest), SERVICE_MESSAGE_TYPE_USER, 
				OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, unType);
			if(nRet == 0)
			{
				MsgGoldBuyRequest *body = (MsgGoldBuyRequest *)msgInfo.body;
				body->unSN = unSN;
				if(m_stream.readInt(body->unType) == -1)
				{
					nRet = -1;
				}
			}
		}
		break;
	case MSG_EQUIPMENT_STEP_UP_REQUEST:
		{
			nRet = allocMessageWithInfo(msgInfo, sizeof(MsgEquipmentStepUpRequest), SERVICE_MESSAGE_TYPE_USER, 
				OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, unType);
			if(nRet == 0)
			{
				MsgEquipmentStepUpRequest *body = (MsgEquipmentStepUpRequest *)msgInfo.body;
				body->unSN = unSN;
				if(m_stream.readInt(body->unIdx) == -1 || m_stream.readInt(body->unPlayerID) == -1)
				{
					nRet = -1;
					break;
				}

				if(m_stream.readInt(body->unGrade) == -1)
				{
					nRet = -1;
					break;
				}

				if (body->unGrade > MsgEquipmentStepUp_unGrade_MAX)
					body->unGrade = MsgEquipmentStepUp_unGrade_MAX;

				for(int i = 0;i < body->unGrade;i ++)
				{
					if(m_stream.readInt(body->unMaterialIdxList[i]) == -1)
					{
						nRet = -1;
						break;
					}
				}
			}
		}
		break;
	case MSG_CHANGE_NAME_REQUEST:
		{
			nRet = allocMessageWithInfo(msgInfo, sizeof(MsgChangeNameRequest), SERVICE_MESSAGE_TYPE_USER, 
				OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, unType);
			if(nRet == 0)
			{
				MsgChangeNameRequest *body = (MsgChangeNameRequest *)msgInfo.body;
				body->unSN = unSN;
				if(m_stream.readString(body->name, MAX_CHARACTER_LENGTH) == -1)
				{
					nRet = -1;

				}
			}
		}
		break;
	case MSG_BATTLE_REBORN_REQUEST:
		{
			nRet = allocMessageWithInfo(msgInfo, sizeof(MsgBattleRebornRequest), SERVICE_MESSAGE_TYPE_USER, 
				OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, unType);
			if(nRet == 0)
			{
				MsgBattleRebornRequest *body = (MsgBattleRebornRequest *)msgInfo.body;
				body->unSN = unSN;
			}
		}
		break;
	case MSG_CLEAR_MAP_REQUEST:
		{
			nRet = allocMessageWithInfo(msgInfo, sizeof(MsgClearMapRequest), SERVICE_MESSAGE_TYPE_USER, 
				OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, unType);
			if(nRet == 0)
			{
				MsgClearMapRequest *body = (MsgClearMapRequest *)msgInfo.body;
				body->unSN = unSN;

				if(m_stream.readInt(body->unType) == -1)
				{
					nRet = -1;
				}
			}
		}
		break;
	case MSG_USE_ITEM_REQUEST:
		{
			nRet = allocMessageWithInfo(msgInfo, sizeof(MsgUseItemRequest), SERVICE_MESSAGE_TYPE_USER, 
				OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, unType);
			if(nRet == 0)
			{
				MsgUseItemRequest *body = (MsgUseItemRequest *)msgInfo.body;
				body->unSN = unSN;

				if(m_stream.readInt(body->unItemType) == -1 || m_stream.readInt(body->unIndex) == -1)
				{
					nRet = -1;
				}
			}
		}
		break;
		/*
	case MSG_BATTLE_COMMAND_REQUEST:
		{
			nRet = allocMessageWithInfo(msgInfo, sizeof(MsgBattleCommandRequest), SERVICE_MESSAGE_TYPE_USER, 
				OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, unType);
			if(nRet == 0)
			{
				MsgBattleCommandRequest *body = (MsgBattleCommandRequest *)msgInfo.body;
				body->unSN = unSN;

				if(m_stream.readInt(body->unBattleInfoSize) == -1)
				{
					nRet = -1;
					break;
				}

				if(m_stream.left() != body->unBattleInfoSize)
				{
					nRet = -1;
					break;
				}

				if(m_stream.readStream(body->battleInfo, body->unBattleInfoSize) == -1)
				{
					nRet = -1;
				}
			}
		}
		break;
		*/
	case MSG_UPDATE_TUTORIAL_FLAG_REQUEST:
		{
			nRet = allocMessageWithInfo(msgInfo, sizeof(MsgUpdateTutorialFlagRequest), SERVICE_MESSAGE_TYPE_USER, 
				OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, unType);
			if(nRet == 0)
			{
				MsgUpdateTutorialFlagRequest *body = (MsgUpdateTutorialFlagRequest *)msgInfo.body;
				body->unSN = unSN;

				if(m_stream.readInt(body->unTutorialFlag) == -1)
				{
					nRet = -1;
					break;
				}
			}
		}
		break;
	case MSG_DO_BEHAVIOR_REQUEST:
		{
			nRet = allocMessageWithInfo(msgInfo, sizeof(MsgDoBehaviorRequest), SERVICE_MESSAGE_TYPE_USER, 
				OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, unType);
			if(nRet == 0)
			{
				MsgDoBehaviorRequest *body = (MsgDoBehaviorRequest *)msgInfo.body;
				body->unSN = unSN;
				if(m_stream.readInt(body->unID) == -1)
				{
					nRet = -1;
					break;
				}
			}
		}
		break;
	case MSG_DO_BUYENERGY_REQUEST://买体力
		{
			nRet = allocMessageWithInfo(msgInfo, sizeof(MsgDoBehaviorRequest), SERVICE_MESSAGE_TYPE_USER, 
				OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, unType);
			if(nRet == 0)
			{
				MsgDoBehaviorRequest *body = (MsgDoBehaviorRequest *)msgInfo.body;
				body->unSN = unSN;
			}
		}
		break;
	case MSG_COMPOSE_REQUEST:
		{
			nRet = allocMessageWithInfo(msgInfo, sizeof(MsgComposeRequest), SERVICE_MESSAGE_TYPE_USER, 
				OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, unType);
			if(nRet == 0)
			{
				MsgComposeRequest *body = (MsgComposeRequest *)msgInfo.body;
				body->unSN = unSN;
				if(m_stream.readInt(body->unItemID) == -1 || m_stream.readInt(body->unTimes) == -1)  //在这将要读入的数存入结构体内
				{
					nRet = -1;
					break;
				}				
			}
		}
		break;
	case MSG_GET_BROADCAST_MESSAGE_REQUEST:
		{
			nRet = allocMessageWithInfo(msgInfo, sizeof(MsgGetBroadcastMessageRequest), SERVICE_MESSAGE_TYPE_USER, 
				OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, unType);
			if(nRet == 0)
			{
				MsgGetBroadcastMessageRequest *body = (MsgGetBroadcastMessageRequest *)msgInfo.body;
				body->unSN = unSN;
				
			}
		}
		break;
	case MSG_PVP_RANK_INFO_REQUEST:
		{
			nRet = allocMessageWithInfo(msgInfo, sizeof(MsgPVPRankInfoRequest), SERVICE_MESSAGE_TYPE_USER, 
				OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, unType);
			if(nRet == 0)
			{
				MsgPVPRankInfoRequest *body = (MsgPVPRankInfoRequest *)msgInfo.body;
				body->unSN = unSN;

			}
		}
		break;
	case MSG_COMMIT_PVP_RESULT_REQUEST:
		{
			//ACE_UINT32 unFriendID;
			ACE_UINT32 win, size;

			/*
			if(m_stream.readInt(unFriendID) == -1)
			{
				nRet = -1;
				break;
			}
			*/

			if(m_stream.readInt(win) == -1)
			{
				nRet = -1;
				break;
			}

			if(m_stream.readInt(size) == -1)
			{
				nRet = -1;
				break;
			}

			if(size > MAX_PVP_COMMAND_DATA_SIZE)
			{
				nRet = -1;
				break;
			}

			nRet = allocMessageWithInfo(msgInfo, sizeof(MsgCommitPVPResultRequest) + size, SERVICE_MESSAGE_TYPE_USER, 
				OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, unType);
			if(nRet == 0)
			{
				MsgCommitPVPResultRequest *body = (MsgCommitPVPResultRequest *)msgInfo.body;
				body->unSN = unSN;
				
				//body->unFriendID = unFriendID;
				body->win = win;
				body->unSize = size;
		
				if(m_stream.left() != body->unSize)
				{
					nRet = -1;
					break;
				}

				if(m_stream.readStream(body->commandData, body->unSize) == -1)
				{
					nRet = -1;
				}	
			}
		}
		break;
	case MSG_GET_PVP_RANK_REWARD_REQUEST:
		{
			nRet = allocMessageWithInfo(msgInfo, sizeof(MsgGetPVPRankRewardRequest), SERVICE_MESSAGE_TYPE_USER, 
				OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, unType);
			if(nRet == 0)
			{
				MsgGetPVPRankRewardRequest *body = (MsgGetPVPRankRewardRequest *)msgInfo.body;
				body->unSN = unSN;
				
				if(m_stream.readInt(body->unRewardID) == -1)
				{
					nRet = -1;
					break;
				}
			}
		}
		break;
	case MSG_GET_PVP_LEADERBOARD_REQUEST:
		{
			nRet = allocMessageWithInfo(msgInfo, sizeof(MsgGetPVPLeaderboardRequest), SERVICE_MESSAGE_TYPE_USER, 
				OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, unType);
			if(nRet == 0)
			{
				MsgGetPVPLeaderboardRequest *body = (MsgGetPVPLeaderboardRequest *)msgInfo.body;
				body->unSN = unSN;

				if(m_stream.readInt(body->unType) == -1)
				{
					nRet = -1;
					break;
				}

				if(m_stream.readInt(body->unCount) == -1)
				{
					nRet = -1;
					break;
				}

				if(m_stream.readInt(body->unPage) == -1)
				{
					nRet = -1;
					break;
				}

				if(body->unCount != 0)
				{
					nRet = -1;
					break;
				}
			}
		}
		break;
	case MSG_START_PVP_REQUEST:
		{
			nRet = allocMessageWithInfo(msgInfo, sizeof(MsgStartPVPRequest), SERVICE_MESSAGE_TYPE_USER, 
				OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, unType);
			if(nRet == 0)
			{
				MsgStartPVPRequest *body = (MsgStartPVPRequest *)msgInfo.body;
				body->unSN = unSN;
				if(m_stream.readInt(body->unContinue) == -1 || m_stream.readInt(body->unFriendID) == -1)
				{
					nRet = -1;
					break;
				}
			}
		}
		break;
		/*
	case MSG_UPDATE_PVP_TEAM_REQUEST:
		{
			nRet = allocMessageWithInfo(msgInfo, sizeof(MsgUpdatePVPTeamRequest), SERVICE_MESSAGE_TYPE_USER, 
				OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, unType);
			if(nRet == 0)
			{
				MsgUpdatePVPTeamRequest *body = (MsgUpdatePVPTeamRequest *)msgInfo.body;
				body->unSN = unSN;

				int i;
				
				for(i = 0;i < MAX_PLAYER_SELECTED_COUNT;i ++)
				{
					if(m_stream.readInt(body->playerList[i]) == -1)
					{
						break;
					}
				}

				if(i < MAX_PLAYER_SELECTED_COUNT)
				{
					nRet = -1;
					break;
				}

				for(i = 0;i < MAX_PLAYER_SELECTED_COUNT;i ++)
				{
					if(m_stream.readInt(body->skillList[i]) == -1)
					{
						break;
					}
				}

				if(i < MAX_PLAYER_SELECTED_COUNT)
				{
					nRet = -1;
					break;
				}
			}
		}
		break;
		*/
	case MSG_GET_PVP_TEAM_INFO_REQUEST:
		{
			nRet = allocMessageWithInfo(msgInfo, sizeof(MsgGetPVPTeamInfoRequest), SERVICE_MESSAGE_TYPE_USER, 
				OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, unType);
			if(nRet == 0)
			{
				MsgGetPVPTeamInfoRequest *body = (MsgGetPVPTeamInfoRequest *)msgInfo.body;
				body->unSN = unSN;

				if(m_stream.readInt(body->unCharacterID) == -1)
				{
					nRet = -1;
					break;
				}
			}
		}
		break;
		/*
	case MSG_SELECT_PLAYER_SKILL_REQUEST:
		{
			nRet = allocMessageWithInfo(msgInfo, sizeof(MsgSelectPlayerSkillRequest), SERVICE_MESSAGE_TYPE_USER, 
				OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, unType);
			if(nRet == 0)
			{
				MsgSelectPlayerSkillRequest *body = (MsgSelectPlayerSkillRequest *)msgInfo.body;
				body->unSN = unSN;

				if(m_stream.readInt(body->unIndex) == -1 || m_stream.readInt(body->unSkillID) == -1)
				{
					nRet = -1;
					break;
				}
			}
		}
		break;
		*/
	case MSG_GET_MAP_GROUP_REWARD_REQUEST:
		{
			nRet = allocMessageWithInfo(msgInfo, sizeof(MsgGetMapGroupRewardRequest), SERVICE_MESSAGE_TYPE_USER, 
				OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, unType);
			if(nRet == 0)
			{
				MsgGetMapGroupRewardRequest *body = (MsgGetMapGroupRewardRequest *)msgInfo.body;
				body->unSN = unSN;

				if(m_stream.readInt(body->unMapGroupID) == -1 || m_stream.readInt(body->unIdx) == -1)
				{
					nRet = -1;
					break;
				}
			}
		}
		break;

	
	case MSG_GET_ARTICLE_REQUEST:
		{
			nRet = allocMessageWithInfo(msgInfo, sizeof(MsgGetArticleRequest), SERVICE_MESSAGE_TYPE_USER, 
				OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, unType);
			if(nRet == 0)
			{
				MsgGetArticleRequest *body = (MsgGetArticleRequest *)msgInfo.body;
				body->unSN = unSN;

				if(m_stream.readInt(body->unArticleId) == -1||m_stream.readInt(body->unCount) == -1)  //数据在这里读入结构体
				{
					nRet = -1;
					break;
				}
				
			}
		}
		break;
	case MSG_SECRET_LIST_REQUEST:
		{
			nRet = allocMessageWithInfo(msgInfo, sizeof(MsgSecretListRequest), SERVICE_MESSAGE_TYPE_USER, 
				OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, unType);
			if(nRet == 0)
			{
				MsgSecretListRequest *body = (MsgSecretListRequest *)msgInfo.body;
				body->unSN = unSN;

				if(m_stream.readInt(body->unType) == -1)  //数据在这里读入结构体
				{
					nRet = -1;
					break;
				}

			}

		}
		break;
	case MSG_SECRET_EXPAND_REQUEST:
		{
			nRet = allocMessageWithInfo(msgInfo, sizeof(MsgSecreteExpandRequest), SERVICE_MESSAGE_TYPE_USER, 
				OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, unType);
			if(nRet == 0)
			{
				MsgSecreteExpandRequest *body = (MsgSecreteExpandRequest *)msgInfo.body;
				body->unSN = unSN;

				if(m_stream.readInt(body->unCellCount) == -1)  //数据在这里读入结构体
				{
					nRet = -1;
					break;
				}

			}

		}
		break;
	case MSG_SECRET_BUY_REQUEST:
		{
			nRet = allocMessageWithInfo(msgInfo, sizeof(MsgSecretBuyRequest), SERVICE_MESSAGE_TYPE_USER, 
				OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, unType);
			if(nRet == 0)
			{
				MsgSecretBuyRequest *body = (MsgSecretBuyRequest *)msgInfo.body;
				body->unSN = unSN;
				if(m_stream.readInt(body->unItemId) == -1 || m_stream.readInt(body->unIdx) == -1  )  //在这将要读入的数存入结构体内
				{
					nRet = -1;
					break;
				}
	
			}
		}
		break;
	case MSG_ADD_NEW_MAP_REQUEST:
		{
			nRet = allocMessageWithInfo(msgInfo, sizeof(MsgAddNewMapRequest), SERVICE_MESSAGE_TYPE_USER, 
				OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, unType);
			if(nRet == 0)
			{
				MsgAddNewMapRequest *body = (MsgAddNewMapRequest *)msgInfo.body;
				body->unSN = unSN;
				if(m_stream.readInt(body->unMapID) == -1)  //在这将要读入的数存入结构体内
				{
					nRet = -1;
					break;
				}
			}
		}
		break;
	case MSG_GM_REQUEST://GM 信息请求
		{
			nRet = allocMessageWithInfo(msgInfo, sizeof(MsgAnnouncementRequest), SERVICE_MESSAGE_TYPE_USER,
				OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, unType);
			if(nRet == 0)
			{
				MsgAnnouncementRequest *body = (MsgAnnouncementRequest*)msgInfo.body;
				body->unSN = unSN;
				if(m_stream.readInt(body->unTypeID) == -1)
				{
					nRet = -1;
					break;
				}
			}
		}
		break;
	case MSG_GET_LA_LIST_REQUEST://限时活动请求
		{
			nRet = allocMessageWithInfo(msgInfo, sizeof(MsgBaseRequest), SERVICE_MESSAGE_TYPE_USER,
				OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, unType);
			if(nRet == 0)
			{
				MsgBaseRequest *body = (MsgBaseRequest*)msgInfo.body;
				body->unSN = unSN;
			}
		}
		break;
	case MSG_GET_LA_REWARD_REQUEST:
		{
			nRet = allocMessageWithInfo(msgInfo, sizeof(MsgGMLARewardRequest), SERVICE_MESSAGE_TYPE_USER,
				OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, unType);
			if(nRet == 0)
			{
				MsgGMLARewardRequest *body = (MsgGMLARewardRequest*)msgInfo.body;
				body->unSN = unSN;
				if(m_stream.readInt(body->unLAMID) == -1)
				{
					nRet = -1;
					break;
				}
			}
		}break;
	case  MSG_DESTROY_MSG_ACK://异常断开
		{
			nRet = allocMessageWithInfo(msgInfo, sizeof(MsgDestroyRequest), SERVICE_MESSAGE_TYPE_USER,
				OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, unType);
			if(nRet == 0)
			{
				MsgDestroyRequest *body = (MsgDestroyRequest*)msgInfo.body;
				body->unSN = unSN;
				//if(m_stream.readInt(body->unErrorCode) == -1)
				{
					//nRet = -1;
					m_isDestroyMsg = true;
					m_unActiveTimer = MAX_GATEWAY_SESSION_LIVE-1;//先缓存一下 设置超时时间
					printf("destroy Gateway session：[%d]\n",m_unCurrentCharacterID);
				}
			}
		}break;
	case MSG_DO_ORDER_REQUEST://请求订单号
		{
			nRet = allocMessageWithInfo(msgInfo, sizeof(MsgDoOrderRequest), SERVICE_MESSAGE_TYPE_USER, 
				OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, unType);
			if(nRet == 0)
			{
				MsgDoOrderRequest *body = (MsgDoOrderRequest *)msgInfo.body;
				body->unSN = unSN;
				if(m_stream.readInt(body->product_id) == -1 || m_stream.readInt(body->product_count) == -1)
				{
					nRet = -1;
					break;
				}
			}
		}
		break;
	case MSG_DO_RECHARGE_REQUEST://充值成功检测
		{
			nRet = allocMessageWithInfo(msgInfo, sizeof(MsgDoRechargeRequest), SERVICE_MESSAGE_TYPE_USER, 
				OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, unType);
			if(nRet == 0)
			{
				MsgDoRechargeRequest *body = (MsgDoRechargeRequest *)msgInfo.body;
				body->unSN = unSN;
				if(m_stream.readString(body->orderID,RECHARGE_ORDERID_LEN) == -1)
				{
					nRet = -1;
					break;
				}
			}
		}
		break;
	case MSG_DO_PIECE_ROLE_REQUEST://碎片转角色
		{
			nRet = allocMessageWithInfo(msgInfo, sizeof(MsgDoPieceToRoleRequest), SERVICE_MESSAGE_TYPE_USER, 
				OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, unType);
			if(nRet == 0)
			{
				MsgDoPieceToRoleRequest *body = (MsgDoPieceToRoleRequest *)msgInfo.body;
				body->unSN = unSN;
				if(m_stream.readInt(body->unItemID) == -1)
				{
					nRet = -1;
					break;
				}
			}
		}break;
	case MSG_DO_GET_RECHARGE_INFO_REQUEST:
		{
			nRet = allocMessageWithInfo(msgInfo, sizeof(MsgBaseRequest), SERVICE_MESSAGE_TYPE_USER, 
				OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, unType);
			if(nRet == 0)
			{
				MsgBaseRequest *body = (MsgBaseRequest *)msgInfo.body;
				body->unSN = unSN;
			}
		}break;
	case MSG_DO_SHARED_ACTIVITES_REQUEST:
		{
			nRet = allocMessageWithInfo(msgInfo, sizeof(MsgBaseRequest), SERVICE_MESSAGE_TYPE_USER, 
				OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, unType);
			if(nRet == 0)
			{
				MsgBaseRequest *body = (MsgBaseRequest *)msgInfo.body;
				body->unSN = unSN;
			}
		}break;
	case MSG_DO_VIP_GIFT_REQUEST:
		{
			nRet = allocMessageWithInfo(msgInfo, sizeof(MsgVipGiftRequest), SERVICE_MESSAGE_TYPE_USER, 
				OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, unType);
			if(nRet == 0)
			{
				MsgVipGiftRequest *body = (MsgVipGiftRequest *)msgInfo.body;
				body->unSN = unSN;

				if(m_stream.readInt(body->ungiftId) == -1)
				{
					nRet = -1;
					break;
				}

				if(m_stream.readInt(body->unvipLevel) == -1)
				{
					nRet = -1;
					break;
				}
			}
		}break;
	case MSG_DO_Get_BadgeGaint_REQUEST:
		{
			nRet = allocMessageWithInfo(msgInfo, sizeof(MsgBaseRequest), SERVICE_MESSAGE_TYPE_USER, 
				OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, unType);
			if(nRet == 0)
			{
				MsgBaseRequest *body = (MsgBaseRequest *)msgInfo.body;
				body->unSN = unSN;
			}
		}break;
	case MSG_DO_Up_BadgeGaint_REQUEST://升级徽章//
	case MSG_DO_Up_BadgeGaint_REQUESTEX:
		{
			nRet = allocMessageWithInfo(msgInfo, sizeof(MsgDoUpBadgeGaintRequest), SERVICE_MESSAGE_TYPE_USER, 
				OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, unType);
			if(nRet == 0)
			{
				MsgDoUpBadgeGaintRequest *body = (MsgDoUpBadgeGaintRequest *)msgInfo.body;
				body->unSN = unSN;
				if(m_stream.readInt(body->unCount) == -1)
				{
					nRet = -1;
					break;
				}

				if (body->unCount > MsgBadgeGaint_MAX)
				{
					body->unCount = MsgBadgeGaint_MAX;
				}

				nRet = 0;
				for (int i=0;i<body->unCount;i++)
				{
					if(m_stream.readInt(body->unIndex[i]) == -1 
						|| m_stream.readInt(body->unIds[i]) == -1)
					{
						nRet = -1;
						break;
					}
				}

			}
		}break;
	case MSG_DO_Up_BadgeGaint_REQUEST1:
		{
			nRet = allocMessageWithInfo(msgInfo, sizeof(MsgBaseRequest), SERVICE_MESSAGE_TYPE_USER, 
				OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, unType);
			if(nRet == 0)
			{
				MsgGETBadgeRequest *body = (MsgGETBadgeRequest *)msgInfo.body;
				body->unSN = unSN;
				body->unPage = 100;
				if(body)
				{
					MAX_LOBODY_RELEASE;
				}
			}
		}break;
	case MSG_DO_GET_Badge_REQUEST:
		{
			nRet = allocMessageWithInfo(msgInfo, sizeof(MsgGETBadgeRequest), SERVICE_MESSAGE_TYPE_USER, 
				OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, unType);
			if(nRet == 0)
			{
				MsgGETBadgeRequest *body = (MsgGETBadgeRequest *)msgInfo.body;
				body->unSN = unSN;
				if(m_stream.readInt(body->unPage) == -1 || m_stream.readInt(body->isClear) == -1)
				{
					nRet = -1;
					break;
				}
			}
		}break;
	case MSG_GET_CHARACTER_INFO_REQUEST:
		{
			nRet = allocMessageWithInfo(msgInfo, sizeof(MsgGetCharacterInfoRequest), SERVICE_MESSAGE_TYPE_USER, 
				OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, unType);
			if(nRet == 0)
			{
				MsgGetCharacterInfoRequest *body = (MsgGetCharacterInfoRequest *)msgInfo.body;
				body->unSN = unSN;
				if(m_stream.readInt(body->unCharacterID) == -1)
				{
					nRet = -1;
					break;
				}
			}
		}break;
	case MSG_GET_PVP_INFO_REQUEST://获取pvp信息
		{
			nRet = allocMessageWithInfo(msgInfo, sizeof(MsgBaseRequest), SERVICE_MESSAGE_TYPE_USER, 
				OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, unType);
			if(nRet == 0)
			{
				MsgBaseRequest *body = (MsgBaseRequest *)msgInfo.body;
				body->unSN = unSN;
			}
		}break;
	case MSG_PVP_ENTER_FIGHT_REQUEST:
		{
			nRet = allocMessageWithInfo(msgInfo, sizeof(MsgPVPEnterFightRequestEx), SERVICE_MESSAGE_TYPE_USER, 
				OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, unType);
			if(nRet == 0)
			{
				MsgPVPEnterFightRequestEx *body = (MsgPVPEnterFightRequestEx *)msgInfo.body;
				body->unSN = unSN;
				if(m_stream.readInt(body->isReFreash) == -1)
				{
					nRet = -1;
					break;
				}
			}
		}break;
	case MSG_PVP_GET_ORDER_REQUEST:
		{
			nRet = allocMessageWithInfo(msgInfo, sizeof(MsgBaseRequest), SERVICE_MESSAGE_TYPE_USER, 
				OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, unType);
			if(nRet == 0)
			{
				MsgBaseRequest *body = (MsgBaseRequest *)msgInfo.body;
				body->unSN = unSN;
			}
		}break;
	case MSG_PVP_BUY_TIMES_REQUEST:
		{
			nRet = allocMessageWithInfo(msgInfo, sizeof(MsgBaseRequest), SERVICE_MESSAGE_TYPE_USER, 
				OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, unType);
			if(nRet == 0)
			{
				MsgBaseRequest *body = (MsgBaseRequest *)msgInfo.body;
				body->unSN = unSN;
			}
		}break;
	case MSG_PVP_ENTER_REQUEST:
		{
			nRet = allocMessageWithInfo(msgInfo, sizeof(MsgBaseRequest), SERVICE_MESSAGE_TYPE_USER, 
				OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, unType);
			if(nRet == 0)
			{
				MsgBaseRequest *body = (MsgBaseRequest *)msgInfo.body;
				body->unSN = unSN;
			}
		}break;
	case MSG_PVP_ACCOUNTS_REQUEST:
		{
			nRet = allocMessageWithInfo(msgInfo, sizeof(MsgPVPAccountRequest), SERVICE_MESSAGE_TYPE_USER, 
				OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, unType);
			if(nRet == 0)
			{
				MsgPVPAccountRequest *body = (MsgPVPAccountRequest *)msgInfo.body;
				ZeroVar(*body);
				body->unSN = unSN;

				if(m_stream.readInt(body->info.to.m_characterID) == -1)
				{
					nRet = -1;
					break;
				}

				if (m_stream.readInt(body->info.isWin)==-1)
				{
					nRet = -1;
					break;
				}

				if (m_stream.readInt(body->info.from.fightInfo.unCount)==-1)
				{
					nRet = -1;
					break;
				}

				nRet = 0;
				for (int i=0;i<body->info.from.fightInfo.unCount;i++)
				{
					if (m_stream.readInt(body->info.from.fightInfo.role_list[i])==-1
						||m_stream.readInt(body->info.from.fightInfo.setup_list[i])==-1
						||m_stream.readInt(body->info.from.fightInfo.score_list[i])==-1)
					{
						nRet = -1;
						break;
					}
				}

				if (nRet == 0)
				{
					if (m_stream.readInt(body->info.to.fightInfo.unCount)==-1)
					{
						nRet = -1;
						break;
					}

					nRet = 0;
					for (int i=0;i<body->info.to.fightInfo.unCount;i++)
					{
						if (m_stream.readInt(body->info.to.fightInfo.role_list[i])==-1
							||m_stream.readInt(body->info.to.fightInfo.setup_list[i])==-1
							||m_stream.readInt(body->info.to.fightInfo.score_list[i])==-1)
						{
							nRet = -1;
							break;
						}
					}
				}

			}
		}break;
	case MSG_PVP_GET_FightRecordInfo_REQUEST:
		{
			nRet = allocMessageWithInfo(msgInfo, sizeof(MsgPVPFightRecordInfoRequest), SERVICE_MESSAGE_TYPE_USER, 
				OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, unType);
			if(nRet == 0)
			{
				MsgPVPFightRecordInfoRequest *body = (MsgPVPFightRecordInfoRequest *)msgInfo.body;
				body->unSN = unSN;
			}
		}break;
	case MSG_Update_badge_info_REQUESTE:
		{
			nRet = allocMessageWithInfo(msgInfo, sizeof(MsgUpdateBadgeInfoRequest), SERVICE_MESSAGE_TYPE_USER, 
				OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, unType);
			if(nRet == 0)
			{
				MsgUpdateBadgeInfoRequest *body = (MsgUpdateBadgeInfoRequest *)msgInfo.body;
				body->unSN = unSN;
				if(m_stream.readInt(body->bsInfos.unCount) == -1)
				{
					nRet = -1;
					break;
				}

				if (body->bsInfos.unCount>MAX_BSINFO_NUM)
					body->bsInfos.unCount = MAX_BSINFO_NUM;

				nRet = 0;
				for (int i=0;i<body->bsInfos.unCount;i++)
				{
					if (!Read_BS_info(body->bsInfos.bsInfo[i]))
					{
						nRet = -1;
						break;
					}
				}
			}
		}break;
	case MSG_Get_badge_info_REQUESTE:
		{
			nRet = allocMessageWithInfo(msgInfo, sizeof(MsgGetBadgeInfoRequest), SERVICE_MESSAGE_TYPE_USER, 
				OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, unType);
			if(nRet == 0)
			{
				MsgGetBadgeInfoRequest *body = (MsgGetBadgeInfoRequest *)msgInfo.body;
				body->unSN = unSN;
				if(m_stream.readInt(body->unCharacterID) == -1)
				{
					nRet = -1;
					break;
				}
			}
		}break;
	case MSG_Get_active_inofo_REQUEST:
		{			
			nRet = allocMessageWithInfo(msgInfo, sizeof(MsgGetBadgeInfoRequest), SERVICE_MESSAGE_TYPE_USER, 
			OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, unType);
			if(nRet == 0)
			{
				MsgGetBadgeInfoRequest *body = (MsgGetBadgeInfoRequest *)msgInfo.body;
				body->unSN = unSN;
			}
		}break;
	case MSG_Get_POWER_REQUEST:
		{
			nRet = allocMessageWithInfo(msgInfo, sizeof(MsgGetPowerRequest), SERVICE_MESSAGE_TYPE_USER, 
				OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, OBJ_ID_NONE, unType);
			if(nRet == 0)
			{
				MsgGetPowerRequest *body = (MsgGetPowerRequest *)msgInfo.body;
				body->unSN = unSN;

				if(m_stream.readInt(body->power) == -1)
				{
					nRet = -1;
					break;
				}
			}
		}break;
	}
		

	
		
	if(nRet == -1 && msgInfo.msg != NULL)
	{
		msgInfo.msg->release();
	}

	if(nRet == 0 && !m_isDestroyMsg)
	{
		m_unActiveTimer = 0;
	}

	return nRet;
}

ACE_Message_Block *GatewaySession::parse_into_internet_msg(MessageInfo &msgInfo)   //Response
{
	ACE_Message_Block *msg = NULL;
	int nRet = -1;
	int size;
	ACE_UINT32 unSN = *(ACE_UINT32*)msgInfo.body;

	CLogBase *pLog = BaseService::GetLogInstance();

	sprintf(pLog->m_szLogBuffer, "[%s][%d]:send cmd = %x, characterid=%d",__FILE__, __LINE__, msgInfo.m_head->unType, get_current_id());
	pLog->RecordLog(Log_Type_Fatal, pLog->m_szLogBuffer);


	std::map<ACE_UINT32, CommunicationRecord>::iterator itMap =	m_oCommunicationRecord.find(unSN);
	if (itMap == m_oCommunicationRecord.end())
	{
		
		sprintf(pLog->m_szLogBuffer, "[%s][%d]:CommunicationRecord no this sn = %d",__FILE__, __LINE__, unSN);
		pLog->RecordLog(Log_Type_Info, pLog->m_szLogBuffer);
	}
	else
	{
		itMap->second.unSendTime = GetTickCount();
		ACE_UINT32 unTime = itMap->second.unSendTime - itMap->second.unRecvTime;
		if (unTime > 1000)
		{
			sprintf(pLog->m_szLogBuffer, "[%s][%d]:CommunicationRecord too long,sn=%d, cmd=%d, time = %d, characterid=%d",__FILE__, __LINE__,unSN, msgInfo.m_head->unType, unTime,get_current_id());
			pLog->RecordLog(Log_Type_Info, pLog->m_szLogBuffer);
		}
	}
	if (m_oCommunicationRecord.size() > 100)
	{
		sprintf(pLog->m_szLogBuffer, "[%s][%d]:CommunicationRecord clear, current size = %d",__FILE__, __LINE__, m_oCommunicationRecord.size());
		pLog->RecordLog(Log_Type_Info, pLog->m_szLogBuffer);
		m_oCommunicationRecord.clear();
	}
	if(msgInfo.p_head->unType == SERVICE_MESSAGE_TYPE_USER)
	{
		switch(msgInfo.m_head->unType)
		{
		case MSG_CHARACTER_INFO_RESPONSE:
			{
				MsgCharacterInfoResponse *body = (MsgCharacterInfoResponse *)msgInfo.body;
				size = sizeof(MsgCharacterInfoResponse);

				msg = create_send_msg(size);
				if(msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1 || m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}

					if(m_stream.writeInt(body->unCharacterID) == -1 || m_stream.writeString(body->name, MAX_CHARACTER_LENGTH) == -1)
					{
						break;
					}

					if(m_stream.writeInt(body->unLevel) == -1 || m_stream.writeInt(body->unExp) == -1 || m_stream.writeInt(body->unCoin) == -1 
						|| m_stream.writeInt(body->unMoney) == -1 || m_stream.writeInt(body->unPowerPoint) == -1 || m_stream.writeInt(body->unHonour) == -1 
						|| m_stream.writeInt(body->unFriendship) == -1 || m_stream.writeInt(body->unDynamicEnergy) == -1)
					{
						break;
					}

					if(m_stream.writeInt(body->unLastLoginTime) == -1 || m_stream.writeInt(body->unLoginCount) == -1 || m_stream.writeInt(body->unLoginBonusCount) == -1)
					{
						break;
					}

					if(m_stream.writeInt(body->unCreateTime) == -1 || m_stream.writeInt(body->unEnergy) == -1 || m_stream.writeInt(body->unEnergyRestoreTime) == -1)
					{
						break;
					}

// 					if(m_stream.writeInt(body->unPVPEnergy) == -1 || m_stream.writeInt(body->unPVPEnergyRestoreTime) == -1)
// 					{
// 						break;
// 					}

					if(m_stream.writeInt(body->unRechargeCount) == -1 || m_stream.writeInt(body->unRechargeAmount) == -1)
					{
						break;
					}

					if(m_stream.writeInt(body->unPackageMax) == -1 || m_stream.writeInt(body->unTutorialFlag) == -1)
					{
						break;
					}

					if(m_stream.writeInt(body->unFlag) == -1 || m_stream.writeInt(body->unGoldenTouchUsedCount) == -1)
					{
						break;
					}
					if(m_stream.writeInt(body->unCurrentBuyCount) == -1 )
					{
						break;
					}
					if (m_stream.writeInt(body->m_vipInfo.vip_level)==-1 || m_stream.writeInt(body->m_vipInfo.vip_amount)==-1)
					{
						break;
					}

					if(m_stream.writeInt(body->m_power) == -1)
					{
						break;
					}

					if (m_stream.writeInt(body->m_bitField)==-1  || m_stream.writeInt(body->m_Productlist.unCount)==-1)
					{
						break;
					}
					for(int i=0;i<body->m_Productlist.unCount;i++)
					{
						m_stream.writeInt(body->m_Productlist.list[i]);
					}

					if(m_stream.writeInt(body->m_vipGift.unCount) == -1)//vip礼包
					{
						break;
					}
					for (int i=0;i<body->m_vipGift.unCount;i++)
					{
						m_stream.writeInt(body->m_vipGift.list[i]);
					}

					nRet = 0;
				}
			}
			break;
		case MSG_FUNCTION_LIST_RESPONSE:
			{
				MsgFunctionListResponse *body = (MsgFunctionListResponse *)msgInfo.body;
				
				size = sizeof(MsgFunctionListResponse) + body->unCount * sizeof(ACE_UINT32);

				msg = create_send_msg(size);
				if(msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1 || m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}

					if(m_stream.writeInt(body->unCount) == -1)
					{
						break;
					}

					int i = 0;
					for(i = 0;i < body->unCount;i ++)
					{
						if(m_stream.writeInt(body->list[i]) == -1)
						{
							break;
						}
					}

					if(i >= body->unCount)
					{
						nRet = 0;
					}
				}
			}
			break;
		case MSG_GIFT_LIST_RESPONSE:
			{
				MsgGiftListResponse *body = (MsgGiftListResponse *)msgInfo.body;
				
				size = sizeof(MsgGiftListResponse);

				msg = create_send_msg(size);
				if(msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1 || m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}

					if(m_stream.writeInt(body->unCount) == -1)
					{
						break;
					}

					int i = 0;
					for(i = 0;i < body->unCount;i ++)
					{
						if(m_stream.writeInt(body->giftList[i].unGiftID) == -1 || m_stream.writeInt(body->giftList[i].unTimeStamp) == -1)
						{
							break;
						}
					}

					if(i >= body->unCount)
					{
						nRet = 0;
					}
				}
			}
			break;
		case MSG_PACKAGE_INFO_RESPONSE:
			{
				MsgPackageInfoResponse *body = (MsgPackageInfoResponse *)msgInfo.body;
				size = sizeof(MsgPackageInfoResponse) + body->unCount * sizeof(PackageCell);

				msg = create_send_msg(size);
				if(msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1 || m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}

					if(m_stream.writeInt(body->unCount) == -1)
					{
						break;
					}

					int i = 0;
					for(i = 0;i < body->unCount;i ++)
					{
						if(!this->write_package_cell(&body->list[i]))
						{
							break;
						}
					}

					if(i >= body->unCount)
					{
						nRet = 0;
					}
				}
			}
			break;
		case MSG_PLAYER_INFO_RESPONSE:
			{
				MsgPlayerInfoResponse *body = (MsgPlayerInfoResponse *)msgInfo.body;
				size = sizeof(MsgPlayerInfoResponse) + body->unCount * sizeof(PlayerInfo);

				msg = create_send_msg(size);
				if(msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1 || m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}

					if(!write_item_info(&body->staff))
					{
						break;
					}

					if(m_stream.writeInt(body->unCount) == -1)
					{
						break;
					}

					/*
					if(m_stream.writeInt(body->unMaxSelected) == -1)
					{
						break;
					}
					*/

					int i = 0;

					for(i = 0;i < MAX_PLAYER_SELECTED_COUNT;i ++)
					{
						if(m_stream.writeInt(body->selectedList[i]) == -1)
						{
							break;
						}
					}

					if(i < MAX_PLAYER_SELECTED_COUNT)
					{
						break;
					}

					for(i = 0;i < body->unCount;i ++)
					{
						if(!write_player_info(&body->playerList[i]))
						{
							break;
						}
					}

					if(i < body->unCount)
					{
						break;
					}

					for(i = 0;i < MAX_PLAYER_SELECTED_COUNT;i ++)
					{
						if(m_stream.writeInt(body->playerSkillList[i]) == -1)
						{
							break;
						}
					}

					if(i < MAX_PLAYER_SELECTED_COUNT)
					{
						break;
					}

					if(m_stream.writeInt(body->unHighestPoint) == -1)
					{
						break;
					}

					nRet = 0;
				}
			}
			break;
			/*
		case MSG_SELECT_PLAYER_SKILL_RESPONSE:
			{
				MsgSelectPlayerSkillResponse *body = (MsgSelectPlayerSkillResponse *)msgInfo.body;
				size = sizeof(MsgSelectPlayerSkillResponse);

				msg = create_send_msg(size);
				if(msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1 || m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}

					nRet = 0;
				}
			}
			break;
			*/
			/*
		case MSG_EQUIPMENT_INFO_RESPONSE:
			{
				MsgEquipmentInfoResponse *body = (MsgEquipmentInfoResponse *)msgInfo.body;
				size = sizeof(MsgEquipmentInfoResponse);

				msg = create_send_msg(size);
				if(msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1 || m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}

					int i = 0;
					for(i = 0;i < MAX_EQUIPMENT_COUNT;i ++)
					{
						if(!this->write_package_cell(&body->equipmentList[i]))
						{
							break;
						}
					}

					if(i >= MAX_EQUIPMENT_COUNT)
					{
						nRet = 0;
					}
				}
			}
			break;
			*/
		case MSG_MAP_LIST_INFO_RESPONSE:
			{
				MsgMapListInfoResponse *body = (MsgMapListInfoResponse *)msgInfo.body;
				size = sizeof(MsgMapListInfoResponse);

				msg = create_send_msg(size);
				if(msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1 || m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}

					if(!write_map_instance_info(&body->instanceInfo))
					{
						break;
					}

					/*
					if(!write_battle_info(&body->battleInfo))
					{
						break;
					}
					*/

					/*
					if(!write_reward(body->reward))
					{
						break;
					}
					*/

					if(m_stream.writeInt(body->unCount) == -1)
					{
						break;
					}

					int i;

					for(i = 0;i < body->unCount;i ++)
					{
						if(m_stream.writeInt(body->flagList[i].unMapID) == -1 || m_stream.writeInt(body->flagList[i].unFlag) == -1 ||
							m_stream.writeInt(body->flagList[i].unFlag2) == -1)
						{
							break;
						}
					}

					if(i < body->unCount)
					{
						break;
					}

					if(m_stream.writeInt(body->unLastRewardTime) == -1 || m_stream.writeInt(body->unFreeRebornCount) == -1 || m_stream.writeInt(body->unLastRebornTime) == -1)
					{
						break;
					}

					if(m_stream.writeInt(body->unMapGroupCount) == -1)
					{
						break;
					}
					for(i = 0;i < body->unMapGroupCount;i ++)
					{
						if(m_stream.writeInt(body->giftList[i].unMapID) == -1 || m_stream.writeInt(body->giftList[i].unFlag) == -1 ||
							m_stream.writeInt(body->giftList[i].unFlag2) == -1)
						{
							break;
						}
					}

					if(i < body->unMapGroupCount)
					{
						break;
					}

					nRet = 0;
				}
			}
			break;
		case MSG_SKILL_LIST_RESPONSE:
			{
				MsgSkillListResponse *body = (MsgSkillListResponse *)msgInfo.body;
				size = sizeof(MsgSkillListResponse);

				msg = create_send_msg(size);
				if(msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1 || m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}

					if(m_stream.writeInt(body->unCount) == -1)
					{
						break;
					}

					int i;

					for(i = 0;i < body->unCount;i ++)
					{
						if(m_stream.writeInt(body->skillList[i]) == -1)
						{
							break;
						}
					}

					if(i < body->unCount)
					{
						break;
					}

					if(m_stream.writeInt(body->unPlayerSkillCount) == -1)
					{
						break;
					}

					for(i = 0;i < body->unPlayerSkillCount;i ++)
					{
						if(m_stream.writeInt(body->playerSkillList[i]) == -1)
						{
							break;
						}
					}

					if(i < body->unPlayerSkillCount)
					{
						break;
					}

					if(m_stream.writeInt(body->unBookResCount) == -1)
					{
						break;
					}
					for(i = 0;i < body->unBookResCount;i ++)  //jinpan 添加升级的技能书
					{
						if(m_stream.writeInt(body->bookRes[i].unId) == -1 || m_stream.writeInt(body->bookRes[i].unCount) == -1)
						{
							break;
						}
					}

					if(i < body->unBookResCount)
					{
						break;
					}


					nRet = 0;
				}
			}
			break;
			/*
		case MSG_WEAPON_SKILL_LIST_RESPONSE:
			{
				MsgWeaponSkillListResponse *body = (MsgWeaponSkillListResponse *)msgInfo.body;
				size = sizeof(MsgWeaponSkillListResponse);

				msg = create_send_msg(size);
				if(msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1 || m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}

					if(m_stream.writeInt(body->unCount) == -1)
					{
						break;
					}

					int i;

					for(i = 0;i < body->unCount;i ++)
					{
						if(m_stream.writeInt(body->skillList[i].unItemID) == -1 || m_stream.writeInt(body->skillList[i].unLevel) == -1)
						{
							break;
						}
					}

					if(i >= body->unCount)
					{
						nRet = 0;
					}
				}
			}
			break;
			*/
		case MSG_UPDATE_PLAYER_LIST_RESPONSE:
			{
				MsgUpdatePlayerListResponse *body = (MsgUpdatePlayerListResponse *)msgInfo.body;
				size = sizeof(MsgUpdatePlayerListResponse);

				msg = create_send_msg(size);
				if(msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1 || m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}

					nRet = 0;
				}
			}
			break;
		case MSG_RESET_MAP_RESPONSE:
			{
				MsgResetMapResponse *body = (MsgResetMapResponse *)msgInfo.body;
				size = sizeof(MsgResetMapResponse);

				msg = create_send_msg(size);
				if(msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1 || m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1 || m_stream.writeInt(body->unMapID) == -1)
					{
						break;
					}

					nRet = 0;
				}
			}
			break;
		case MSG_SELECT_EQUIPMENT_RESPONSE:
			{
				MsgSelectEquipmentResponse *body = (MsgSelectEquipmentResponse *)msgInfo.body;
				size = sizeof(MsgSelectEquipmentResponse);

				msg = create_send_msg(size);
				if(msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1 || m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}

					nRet = 0;
				}
			}
			break;
		case MSG_ASSIST_FRIENDSHIP_RESPONSE:
			{
				MsgAssistFriendshipResponse *body = (MsgAssistFriendshipResponse*)msgInfo.body;
				size = sizeof(MsgAssistFriendshipResponse) + body->unCount * sizeof(AssistFriendship);
				msg = create_send_msg(size);
				if(msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1 || m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}
					if (m_stream.writeInt(body->unCount) == -1)
					{
						break;
					}
					nRet = 0;
					for (int i=0;i<body->unCount;++i)
					{
						if (m_stream.writeInt(body->list[i].unCharacterID) == -1 || m_stream.writeInt(body->list[i].unAddFriendship) == -1)
						{
							nRet = -1;
							break;
						}
					}
				}
			}break;
		case MSG_ENTER_MAP_RESPONSE:
			{
				MsgEnterMapResponse *body = (MsgEnterMapResponse *)msgInfo.body;
				size = sizeof(MsgEnterMapResponse);

				msg = create_send_msg(size);
				if(msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1 || m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}

					/*

					if(m_stream.writeInt(body->info.unMapID) == -1 || m_stream.writeInt(body->info.unSpecialBossID) == -1 || m_stream.writeInt(body->info.unItemCount) == -1)
					{
						break;
					}
					*/

					if(!write_map_instance_info(&body->info))
					{
						break;
					}

					if(!write_reward(body->reward))
						break;

					nRet = 0;
				}
			}
			break;
		case MSG_GET_MAP_REWARD_RESPONSE:
			{
				MsgGetMapRewardResponse *body = (MsgGetMapRewardResponse *)msgInfo.body;
				size = sizeof(MsgGetMapRewardResponse);

				msg = create_send_msg(size);
				if(msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1 || m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}

					if (m_stream.writeInt(body->unMultEnergy)==-1)//xxj 2015/04/21  16:01:55 多倍体力
						break;
					if (m_stream.writeInt(body->unReward3Star)==-1)
						break;


					if(write_reward(body->reward))
					{
						nRet = 0;
					}

				}
			}
			break;
		case MSG_INVITE_DETAIL_RESPONSE:
			{
				MsgInviteDetailResponse *body = (MsgInviteDetailResponse *)msgInfo.body;
				size = sizeof(MsgInviteDetailResponse) + body->unCount * sizeof(CharacterInfoExt);

				msg = create_send_msg(size);
				if(msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1 || m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}

					if(m_stream.writeInt(body->unMaxPage) == -1 || m_stream.writeInt(body->unPage) == -1)
					{
						break;
					}

					if(m_stream.writeInt(body->unCount) == -1)
					{
						break;
					}

					int i = 0;
					for(i = 0;i < body->unCount;i ++)
					{
						if(!this->write_character_info(&body->list[i]))
						{
							break;
						}
					}

					if(i >= body->unCount)
					{
						nRet = 0;
					}
				}
			}
			break;
		case MSG_FRIEND_DETAIL_RESPONSE:
			{
				MsgFriendDetailResponse *body = (MsgFriendDetailResponse *)msgInfo.body;
				size = sizeof(MsgFriendDetailResponse) + body->unCount * sizeof(FriendInfo);

				msg = create_send_msg(size);
				if(msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1 || m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}

					if(m_stream.writeInt(body->unMaxPage) == -1 || m_stream.writeInt(body->unPage) == -1 || m_stream.writeInt(body->unMaxFriendCount) == -1 || m_stream.writeInt(body->unCount) == -1 )
					{
						break;
					}

					int i = 0;

					for(i = 0;i < body->unCount;i ++)
					{
						if(!this->write_friend_info(&body->list[i]))
						{
							break;
						}
					}

					if(i >= body->unCount)
					{
						nRet = 0;
					}
				}
			}
			break;
		case MSG_APPLY_INVITATION_RESPONSE:
			{
				MsgApplyInvitationResponse *body = (MsgApplyInvitationResponse *)msgInfo.body;
				size = sizeof(MsgApplyInvitationResponse);

				msg = create_send_msg(size);
				if(msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1 || m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}

					if(m_stream.writeInt(body->unFriendID) == -1)
					{
						break;
					}

					nRet = 0;
				}
			}
			break;
		case MSG_DELETE_FRIEND_RESPONSE:
			{
				MsgDeleteFriendResponse *body = (MsgDeleteFriendResponse *)msgInfo.body;
				size = sizeof(MsgDeleteFriendResponse);

				msg = create_send_msg(size);
				if(msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1 || m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}

					nRet = 0;
				}
			}
			break;
		case MSG_READ_MAIL_RESPONSE:
			{
				MsgReadMailResponse *body = (MsgReadMailResponse *)msgInfo.body;
				size = sizeof(MsgReadMailResponse);

				msg = create_send_msg(size);
				if(msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1 || m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}

					if(m_stream.writeInt(body->m_dwNewMailID) == -1)
					{
						break;
					}

					if(m_stream.writeInt(body->m_dwReadDate) == -1)
					{
						break;
					}

					nRet = 0;
				}
			}
			break;
		case MSG_DELETE_READ_MAIL_RESPONSE:
			{
				MsgDeleteReadMailResponse *body = (MsgDeleteReadMailResponse *)msgInfo.body;
				size = sizeof(MsgDeleteReadMailResponse);

				msg = create_send_msg(size);
				if(msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1 || m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}
					nRet = 0;
				}
			}
			break;
		case MSG_GET_ALL_MAIL_REWARD_RESPONSE:
			{
				MsgGetAllMailRewardResponse *body = (MsgGetAllMailRewardResponse *)msgInfo.body;
				size = sizeof(MsgGetAllMailRewardResponse);

				msg = create_send_msg(size);
				if(msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1 || m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}
					nRet = 0;
				}
			}
			break;
		case MSG_DELETE_ALL_READ_MAIL_RESPONSE:
			{
				MsgDeleteAllReadMailResponse *body = (MsgDeleteAllReadMailResponse *)msgInfo.body;
				size = sizeof(MsgDeleteAllReadMailResponse);

				msg = create_send_msg(size);
				if(msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1 || m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}
					nRet = 0;
				}
			}
			break;
		case MSG_KEEP_ALIVE_RESPONSE:
			{
				MsgKeepAliveResponse *body = (MsgKeepAliveResponse *)msgInfo.body;
				size = sizeof(MsgKeepAliveResponse);

				msg = create_send_msg(size);
				if(msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1 || m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}

					if(m_stream.writeInt(body->unTime) == -1)
					{
						break;
					}
					if(m_stream.writeInt(body->unKey) == -1)
					{
						break;
					}
					nRet = 0;
				}
			}
			break;
		case MSG_GET_MAIL_LIST_RESPONSE:
			{
				MsgGetMailListResponse *body = (MsgGetMailListResponse *)msgInfo.body;
				size = sizeof(MsgGetMailListResponse) + body->unCount * sizeof(MailInfo);

				msg = create_send_msg(size);
				if(msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1 || m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}

					if(m_stream.writeInt(body->StartIndex) == -1)
					{
						break;
					}

					if(m_stream.writeInt(body->unCount) == -1)
					{
						break;
					}

					int i = 0;
					for(i = 0;i < body->unCount;i ++)
					{
						if(!this->write_mail_info(&body->list[i]))
						{
							break;
						}
					}

					if(i >= body->unCount)
					{
						nRet = 0;
					}
				}
			}
			break;
		case MSG_GET_SIGN_UP_REWARD_RESPONSE:
			{
				MsgGetSignUpRewardResponse *body = (MsgGetSignUpRewardResponse *)msgInfo.body;
				size = sizeof(MsgGetSignUpRewardResponse);

				msg = create_send_msg(size);
				if(msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1 || m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}

					nRet = 0;
				}
			}
			break;
		case MSG_GET_RANDOM_CHARACTER_RESPONSE:
			{
				MsgGetRandomCharacterResponse *body = (MsgGetRandomCharacterResponse *)msgInfo.body;
				size = sizeof(MsgGetRandomCharacterResponse) + body->unCount * sizeof(CharacterInfoExt);

				msg = create_send_msg(size);
				if(msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1 || m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}

					if(m_stream.writeInt(body->unCount) == -1)
					{
						break;
					}

					int i = 0;
					for(i = 0;i < body->unCount;i ++)
					{
						if(!this->write_character_info(&body->list[i]))
						{
							break;
						}
					}

					if(i >= body->unCount)
					{
						nRet = 0;
					}
				}
			}
			break;
		case MSG_GET_LUCK_RESPONSE:
			{
				MsgGetLuckResponse *body = (MsgGetLuckResponse *)msgInfo.body;
				size = sizeof(MsgGetLuckResponse);

				msg = create_send_msg(size);
				if(msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1 || m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}

					if(!write_reward(body->reward))
					{
						break;
					}

					nRet = 0;
				}
			}
			break;
			/*
		case MSG_GET_MORE_LUCK_RESPONSE:
			{
				MsgGetMoreLuckResponse *body = (MsgGetMoreLuckResponse *)msgInfo.body;
				size = sizeof(MsgGetMoreLuckResponse);

				msg = create_send_msg(size);
				if(msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1 || m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}

					int i = 0;

					for(i = 0;i < 10;i ++)
					{
						if(m_stream.writeInt(body->unItemList[i]) == -1)
						{
							break;
						}
					}

					if(i >= 10)
					{
						nRet = 0;
					}
				}
			}
			break;
			*/
		case MSG_GET_LOGIN_REWARD_RESPONSE:
			{
				MsgGetLoginRewardResponse *body = (MsgGetLoginRewardResponse *)msgInfo.body;
				size = sizeof(MsgGetLoginRewardResponse);

				msg = create_send_msg(size);
				if(msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1 || m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}

					if(m_stream.writeInt(body->unLoginCount) == -1)
					{
						break;
					}

					nRet = 0;
				}
			}
			break;
		case MSG_GET_GLOBAL_MAP_EVENT_RESPONSE:
			{
				MsgGetGlobalMapEventResponse *body = (MsgGetGlobalMapEventResponse *)msgInfo.body;
				size = sizeof(MsgGetGlobalMapEventResponse);

				msg = create_send_msg(size);
				if(msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1 || m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}

					if(m_stream.writeInt(body->unCooldown) == -1)
					{
						break;
					}

					int i = 0;

					for(i = 0;i < COMMON_MAP_STAGE_COUNT*2;i ++)
					{
						if(m_stream.writeInt(body->unMapList[i]) == -1)
						{
							break;
						}
					}

					if(i >= COMMON_MAP_STAGE_COUNT*2)
					{
						nRet = 0;
					}
				}
			}
			break;
		case MSG_ITEM_LEVEL_UP_RESPONSE:
			{
				MsgItemLevelUpResponse *body = (MsgItemLevelUpResponse *)msgInfo.body;
				size = sizeof(MsgItemLevelUpResponse);

				msg = create_send_msg(size);
				if(msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1 || m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}

					if(m_stream.writeInt(body->unCoin) == -1 || m_stream.writeInt(body->unPowerPoint) == -1)
					{
						break;
					}

					if (m_stream.writeInt(body->unPower) == -1)
					{
						break;
					}

					nRet = 0;
				}
			}
			break;
		case MSG_SKILL_LEVEL_UP_RESPONSE:
			{
				MsgSkillLevelUpResponse *body = (MsgSkillLevelUpResponse *)msgInfo.body;
				size = sizeof(MsgSkillLevelUpResponse);

				msg = create_send_msg(size);
				if(msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1 || m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}

					if (m_stream.writeInt(body->unPower) == -1)
					{
						break;
					}
					if (m_stream.writeInt(body->unDynamicEnergy) == -1)
					{
						break;
					}

					nRet = 0;
				}
			}
			break;
		case MSG_FIND_CHARACTER_RESPONSE:
			{
				MsgFindCharacterResponse *body = (MsgFindCharacterResponse *)msgInfo.body;
				size = sizeof(MsgFindCharacterResponse);

				msg = create_send_msg(size);
				if(msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1 || m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}

					if(!this->write_character_info(&body->info))
					{
						break;
					}

					nRet = 0;
				}
			}
			break;
		case MSG_DELETE_ITEM_RESPONSE:
			{
				MsgDeleteItemResponse *body = (MsgDeleteItemResponse *)msgInfo.body;
				size = sizeof(MsgDeleteItemResponse);

				msg = create_send_msg(size);
				if(msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1 || m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}

					nRet = 0;
				}
			}
			break;
		case MSG_EQUIPMENT_STEP_UP_RESPONSE:
			{
				MsgEquipmentStepUpResponse *body = (MsgEquipmentStepUpResponse *)msgInfo.body;
				size = sizeof(MsgEquipmentStepUpResponse);

				msg = create_send_msg(size);
				if(msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1 || m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}

					if (m_stream.writeInt(body->unPower) == -1)
					{
						break;
					}

					nRet = 0;
				}
			}
			break;
		case MSG_CHANGE_NAME_RESPONSE:
			{
				MsgChangeNameResponse *body = (MsgChangeNameResponse *)msgInfo.body;
				size = sizeof(MsgChangeNameResponse);

				msg = create_send_msg(size);
				if(msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1 || m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}
					if (m_stream.writeString(body->name,33) == -1)
					{
						break;
					}

					nRet = 0;
				}
			}
			break;
		case MSG_GOLD_BUY_RESPONSE:
			{
				MsgGoldBuyResponse *body = (MsgGoldBuyResponse *)msgInfo.body;
				size = sizeof(MsgGoldBuyResponse);

				msg = create_send_msg(size);
				if(msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1 || m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}

					nRet = 0;
				}
			}
			break;
		case MSG_UNLOCK_REWARD_RESPONSE:
			{
				MsgUnlockRewardResponse *body = (MsgUnlockRewardResponse *)msgInfo.body;

				size = sizeof(MsgUnlockRewardResponse);

				msg = create_send_msg(size);
				if(msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());

					if(m_stream.writeInt(msgInfo.m_head->unType) == -1 || m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}

					if(write_reward(body->reward))
					{
						nRet = 0;
					}
				}
			}
			break;
		case MSG_BATTLE_REBORN_RESPONSE:
			{
				MsgBattleRebornResponse *body = (MsgBattleRebornResponse *)msgInfo.body;
				size = sizeof(MsgBattleRebornResponse);

				msg = create_send_msg(size);
				if(msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1 || m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}

					nRet = 0;
				}
			}
			break;
		case MSG_CLEAR_MAP_RESPONSE:
			{
				MsgClearMapResponse *body = (MsgClearMapResponse *)msgInfo.body;
				size = sizeof(MsgClearMapResponse);

				msg = create_send_msg(size);
				if(msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1 || m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}

					nRet = 0;
				}
			}
			break;
		case MSG_USE_ITEM_RESPONSE:
			{
				MsgUseItemResponse *body = (MsgUseItemResponse *)msgInfo.body;
				size = sizeof(MsgUseItemResponse);

				msg = create_send_msg(size);
				if(msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1 || m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}

					if(!this->write_reward(body->reward))
					{
						break;
					}

					nRet = 0;
				}
			}
			break;
		case MSG_UPDATE_TUTORIAL_FLAG_RESPONSE:
			{
				MsgUpdateTutorialFlagResponse *body = (MsgUpdateTutorialFlagResponse *)msgInfo.body;
				size = sizeof(MsgUpdateTutorialFlagResponse);

				msg = create_send_msg(size);
				if(msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1 || m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}

					nRet = 0;
				}
			}
			break;
		case MSG_COOLDOWN_LIST_RESPONSE:
			{
				MsgCooldownListResponse *body = (MsgCooldownListResponse *)msgInfo.body;
				size = sizeof(MsgCooldownListResponse);

				msg = create_send_msg(size);
				if(msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1 || m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}

					if(m_stream.writeInt(body->unCount) == -1)
					{
						break;
					}

					int i = 0;

					for(i = 0;i < body->unCount;i ++)
					{
						if(m_stream.writeInt(body->list[i].unItemID) == -1 || m_stream.writeInt(body->list[i].unCount) == -1 || m_stream.writeInt(body->list[i].unLastUpdateTime) == -1)
						{
							break;
						}
					}

					if(i >= body->unCount)
					{
						nRet = 0;
					}
				}
			}
			break;
		case MSG_HANDBOOK_LIST_RESPONSE:
			{
				MsgHandbookListResponse *body = (MsgHandbookListResponse *)msgInfo.body;
				size = sizeof(MsgHandbookListResponse) + sizeof(BaseItemInfo) * body->unCount;

				msg = create_send_msg(size);
				if(msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1 || m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}

					if(m_stream.writeInt(body->unCount) == -1)
					{
						break;
					}

					int i = 0;

					for(i = 0;i < body->unCount;i ++)
					{
						if(m_stream.writeInt(body->list[i].unItemID) == -1)
						{
							break;
						}
					}

					if(i >= body->unCount)
					{
						nRet = 0;
					}
				}
			}
			break;
		case MSG_MATERIAL_LIST_RESPONSE:
			{
				MsgMaterialListResponse *body = (MsgMaterialListResponse *)msgInfo.body;
				size = sizeof(MsgMaterialListResponse) + sizeof(MaterialInfo) * body->unCount;

				msg = create_send_msg(size);
				if(msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1 || m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}

					if(m_stream.writeInt(body->unCount) == -1)
					{
						break;
					}

					int i = 0;

					for(i = 0;i < body->unCount;i ++)
					{
						if(m_stream.writeInt(body->list[i].unItemID) == -1 || m_stream.writeInt(body->list[i].unCount) == -1)
						{
							break;
						}
					}

					if(i >= body->unCount)
					{
						nRet = 0;
					}
				}
			}
			break;
		case MSG_PROPS_LIST_RESPONSE:
			{
				MsgPropsListResponse *body = (MsgPropsListResponse *)msgInfo.body;
				size = sizeof(MsgPropsListResponse) + sizeof(PropsInfo) * body->unCount;

				msg = create_send_msg(size);
				if(msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1 || m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}

					if(m_stream.writeInt(body->unCount) == -1)
					{
						break;
					}

					int i = 0;

					for(i = 0;i < body->unCount;i ++)
					{
						if(m_stream.writeInt(body->list[i].unItemID) == -1 || m_stream.writeInt(body->list[i].unCount) == -1)
						{
							break;
						}
					}

					if(i >= body->unCount)
					{
						nRet = 0;
					}
				}
			}
			break;
		case MSG_DO_BEHAVIOR_RESPONSE:
			{
				MsgDoBehaviorResponse *body = (MsgDoBehaviorResponse *)msgInfo.body;
				size = sizeof(MsgDoBehaviorResponse);

				msg = create_send_msg(size);
				if(msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1 || m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}

					if(!this->write_reward(body->reward))
					{
						break;
					}

					nRet = 0;
				}
			}
			break;
		case MSG_DO_BUYENERGY_RESPONSE://买体力
			{
				MsgDoBuyEnergyResponse *body = (MsgDoBuyEnergyResponse *)msgInfo.body;
				size = sizeof(MsgDoBuyEnergyResponse);

				msg = create_send_msg(size);
				if(msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1 || m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}

					if(m_stream.writeInt(body->unCurrentCount) == -1)
					{
						break;
					}


					if(m_stream.writeInt(body->unEnergy) == -1)
					{
						break;
					}

					if(m_stream.writeInt(body->unMoneyCost) == -1)
					{
						break;
					}

// 					if(!this->write_reward(body->reward))
// 					{
// 						break;
// 					}

					nRet = 0;
				}
			}
			break;
			/*
		case MSG_BATTLE_COMMAND_RESPONSE:
			{
				MsgBattleCommandResponse *body = (MsgBattleCommandResponse *)msgInfo.body;
				size = sizeof(MsgBattleCommandResponse);

				msg = create_send_msg(size);
				if(msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1 || m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}

					if(m_stream.writeInt(body->unValid) == -1 || m_stream.writeInt(body->currentSection) == -1 || m_stream.writeInt(body->errorCode) == -1 || m_stream.writeInt(body->commandIndex) == -1)
					{
						break;
					}

					if(m_stream.writeStream(body->command, MAX_COMMAND_BUFF_SIZE))
					{
						break;
					}

					int i;

					for(i = 0;i < (MAX_PLAYER_SELECTED_COUNT + 2);i ++)
					{
						if(m_stream.writeInt(body->playerHP[i]) == -1)
						{
							break;
						}
					}

					if(i < (MAX_PLAYER_SELECTED_COUNT + 2))
					{
						break;
					}

					for(i = 0;i < 8;i ++)
					{
						if(m_stream.writeInt(body->monsterHP[i]) == -1)
						{
							break;
						}
					}

					if(i < 8)
					{
						break;
					}

					nRet = 0;
				}
			}
			break;
			*/
		case MSG_COMPOSE_RESPONSE:
			{
				MsgComposeResponse *body = (MsgComposeResponse *)msgInfo.body;
				size = sizeof(MsgComposeResponse);

				msg = create_send_msg(size);
				if(msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1 || m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}

					nRet = 0;
				}
			}
			break;
		case MSG_GET_BROADCAST_MESSAGE_RESPONSE:
			{
				MsgGetBroadcastMessageResponse *body = (MsgGetBroadcastMessageResponse *)msgInfo.body;
				size = sizeof(MsgGetBroadcastMessageResponse);

				msg = create_send_msg(size);
				if(msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1 || m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}

					if(m_stream.writeInt(body->unCurrentCounter) == -1 || m_stream.writeInt(body->unCount) == -1)
					{
						break;
					}

					int i;

					for(i = 0;i < body->unCount;i ++)
					{
						if(m_stream.writeString(body->list[i].name, MAX_CHARACTER_LENGTH) == -1 || m_stream.writeInt(body->list[i].unType) == -1
							|| m_stream.writeInt(body->list[i].unItemID) == -1 || m_stream.writeInt(body->list[i].unParam) == -1 )
						{
							break;
						}
					}

					if(i < body->unCount)
					{
						break;
					}


					nRet = 0;
				}
			}
			break;
		case MSG_PVP_RANK_INFO_RESPONSE:
			{
				MsgPVPRankInfoResponse *body = (MsgPVPRankInfoResponse *)msgInfo.body;
				size = sizeof(MsgPVPRankInfoResponse);

				msg = create_send_msg(size);
				if(msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1 || m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}

					if(m_stream.writeInt(body->unTotalCount) == -1)
					{
						break;
					}

					if(!write_pvp_rank_info(&body->rankInfo))
					{
						break;
					}

					nRet = 0;
				}
			}
			break;
		case MSG_PVP_BASIC_INFO_RESPONSE:
			{
				MsgPVPBasicInfoResponse *body = (MsgPVPBasicInfoResponse *)msgInfo.body;
				size = sizeof(MsgPVPBasicInfoResponse);

				msg = create_send_msg(size);
				if(msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1 || m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}

					if(!write_pvp_basic_info(&body->basicInfo))
					{
						break;
					}

					nRet = 0;
				}
			}
			break;
		case MSG_COMMIT_PVP_RESULT_RESPONSE:
			{
				MsgCommitPVPResultResponse *body = (MsgCommitPVPResultResponse *)msgInfo.body;
				size = sizeof(MsgCommitPVPResultResponse);

				msg = create_send_msg(size);
				if(msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1 || m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}

					nRet = 0;
				}
			}
			break;
		case MSG_GET_PVP_RANK_REWARD_RESPONSE:
			{
				MsgGetPVPRankRewardResponse *body = (MsgGetPVPRankRewardResponse *)msgInfo.body;
				size = sizeof(MsgGetPVPRankRewardResponse);

				msg = create_send_msg(size);
				if(msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1 || m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}

					if(!write_reward(body->reward))
					{
						break;
					}

					nRet = 0;
				}
			}
			break;
		case MSG_GET_PVP_LEADERBOARD_RESPONSE:
			{
				tagMsgGetPVPLeaderboardResponse *body = (tagMsgGetPVPLeaderboardResponse *)msgInfo.body;
				size = sizeof(tagMsgGetPVPLeaderboardResponse) + body->unCount * sizeof(PVPTeamInfo);

				msg = create_send_msg(size);
				if(msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1 || m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}

					if(m_stream.writeInt(body->unMaxPage) == -1)
					{
						break;
					}

					if(m_stream.writeInt(body->unCount) == -1)
					{
						break;
					}

					int i = 0;

					for(i = 0;i < body->unCount;i ++)
					{
						if(!write_pvp_team_info(&body->list[i]))
						{
							break;
						}
					}

					if(i < body->unCount)
					{
						break;
					}

					nRet = 0;
				}
			}
			break;
		case MSG_START_PVP_RESPONSE:
			{
				MsgStartPVPResponse *body = (MsgStartPVPResponse *)msgInfo.body;
				size = sizeof(MsgStartPVPResponse);

				msg = create_send_msg(size);
				if(msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1 || m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}

					if(m_stream.writeInt(body->unStatus) == -1 || m_stream.writeInt(body->pvpType) == -1 || m_stream.writeInt(body->unSeed) == -1)
					{
						break;
					}

					if(!write_character_info(&body->opponent))
					{
						break;
					}

					nRet = 0;
				}
			}
			break;
			/*
		case MSG_UPDATE_PVP_TEAM_RESPONSE:
			{
				MsgUpdatePVPTeamResponse *body = (MsgUpdatePVPTeamResponse *)msgInfo.body;
				size = sizeof(MsgUpdatePVPTeamResponse);

				msg = create_send_msg(size);
				if(msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1 || m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}

					nRet = 0;
				}
			}
			break;
			*/
		case MSG_GET_PVP_TEAM_INFO_RESPONSE:
			{
				MsgGetPVPTeamInfoResponse *body = (MsgGetPVPTeamInfoResponse *)msgInfo.body;
				size = sizeof(MsgGetPVPTeamInfoResponse);

				msg = create_send_msg(size);
				if(msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1 || m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}

					if(!write_team_info(&body->teamInfo))
					{
						break;
					}

					nRet = 0;
				}
			}
			break;
		case MSG_MONEY_TREE_INFO_RESPONSE:
			{
				MsgMoneyTreeInfoResponse *body = (MsgMoneyTreeInfoResponse *)msgInfo.body;
				size = sizeof(MsgMoneyTreeInfoResponse);

				msg = create_send_msg(size);
				if(msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1 || m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}

					if(m_stream.writeInt(body->unLevel) == -1 || m_stream.writeInt(body->unExp) == -1)
					{
						break;
					}

					nRet = 0;
				}
			}
			break;
		case MSG_GET_MAP_GROUP_REWARD_RESPONSE:
			{
				MsgGetMapGroupRewardResponse *body = (MsgGetMapGroupRewardResponse *)msgInfo.body;
				size = sizeof(MsgGetMapGroupRewardResponse);

				msg = create_send_msg(size);
				if(msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1 || m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}

					if(!this->write_reward(body->reward))
					{
						break;
					}

					nRet = 0;
				}
			}
			break;
			
		case MSG_RESPONSE_END:
			{
				MsgResponseEnd *body = (MsgResponseEnd *)msgInfo.body;
				size = sizeof(MsgResponseEnd);

				msg = create_send_msg(size);
				if(msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1 || m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}

					nRet = 0;
				}
			}
			break;

		case MSG_SECRET_LIST_RESPONSE:  //added by jinpan for secret
			{
				MsgSecretListResponse *body = (MsgSecretListResponse *)msgInfo.body;
				size = sizeof(MsgSecretListResponse) + sizeof(SecretItemInfo) * body->unCell;

				msg = create_send_msg(size);
				if(msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1 || m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}

					if(m_stream.writeInt(body->unRemainingTime) == -1)
					{
						break;
					}
					if(m_stream.writeInt(body->unCell) == -1)
					{
						break;
					}


					if(m_stream.writeInt(body->unRefreshTimes) == -1)
					{
						break;
					}
					if (m_stream.writeInt(body->unPaidRefreshPrice) == -1)
					{
						break;
					}

					int i = 0;

					for(i = 0;i < body->unCell;i ++)  //这里是发送信息的，所有都要写入，并且要和前台对接
					{
						if(m_stream.writeInt(body->list[i].unItemID) == -1 ||m_stream.writeInt(body->list[i].unCount ) == -1 || m_stream.writeInt(body->list[i].bBuy ) == -1)
						{
							break;
						}
					}

					if(i >= body->unCell)
					{
						nRet = 0;
					}
				}
			}
			break;
		case MSG_WING_LIST_RESPONSE:
			{
				MsgWingListResponse *body = (MsgWingListResponse *)msgInfo.body;
				size = sizeof(MsgWingListResponse);

				msg = create_send_msg(size);
				if(msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1 || m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}

					int i = 0;

					for(i = 0;i < MAX_WING_LIST;i ++)  //这里是发送信息的，所有都要写入，并且要和前台对接
					{
						if(m_stream.writeInt(body->list[i].unItemID) == -1 || m_stream.writeInt(body->list[i].unPlayerId) == -1 || m_stream.writeInt(body->list[i].unIdx ) == -1 || m_stream.writeInt(body->list[i].unExpires ) == -1)
						{
							break;
						}
					}
					nRet = 0;
				}
			}
			break;
		case MSG_CONVERT_GIFT_BAG_CODE_RESPONSE:
			{
				MsgConvertGiftBagCodeResponse *body = (MsgConvertGiftBagCodeResponse *)msgInfo.body;
				size = sizeof(MsgConvertGiftBagCodeResponse);

				msg = create_send_msg(size);
				if(msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1 || m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}

					if(write_reward(body->reward))
					{
						nRet = 0;
					}
				}
			}break;
		case MSG_DOUBLE_DROP_LIST_RESPONSE:
			{
				MsgDoubleDropListResponse *body = (MsgDoubleDropListResponse *)msgInfo.body;
				size = sizeof(MsgDoubleDropListResponse);
				msg = create_send_msg(size);
				if (msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1 || m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}

					if(m_stream.writeInt(body->iNextFreshTime) == -1 || m_stream.writeInt(body->iCount) == -1)
					{
						break;
					}
					int i=0;
					for (;i<MAX_DOUBLE_DROP_COUNT;++i)
					{
						if(m_stream.writeInt(body->doubleDropList[i].unRawMapID) == -1 || m_stream.writeInt(body->doubleDropList[i].byType) == -1)
						{
							break;
						}
					}
			
					nRet = i == MAX_DOUBLE_DROP_COUNT ? 0 : -1;
				}
			}break;
		case MSG_TASK_LIST:
			{
				MsgTaskList *body = (MsgTaskList *)msgInfo.body;
				size = sizeof(MsgTaskList);
				msg = create_send_msg(size);
				if (msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1 || m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}

					if(m_stream.writeInt(body->iListType) == -1 || m_stream.writeInt(body->iTaskNum) == -1)
					{
						break;
					}
					int i=0;
					for (;i<MAX_CURRENT_TASK_COUNT;++i)
					{
						if(m_stream.writeInt(body->taskInfo[i].unTaskID) == -1 || m_stream.writeInt(body->taskInfo[i].unCurrentProgress) == -1 
							|| m_stream.writeInt(body->taskInfo[i].byStatus) == -1)
						{
							break;
						}
					}

					nRet = i == MAX_CURRENT_TASK_COUNT ? 0 : -1;
				}
			}break;
		case MSG_TASK_REWARD:
			{
				MsgTaskReward *body = (MsgTaskReward *)msgInfo.body;
				size = sizeof(MsgTaskReward);
				msg = create_send_msg(size);
				if (msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1 || m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}
					if(!write_reward(body->reward))
					{
						break;
					}
					nRet = 0;
				}
			}break;
		case MSG_ACTIVENESS_CHANGED:
			{
				MsgActivenessChanged *body = (MsgActivenessChanged *)msgInfo.body;
				size = sizeof(MsgActivenessChanged);
				msg = create_send_msg(size);
				if (msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1|| m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}
					if(m_stream.writeInt(body->unActivenessChanged) == -1)
					{
						break;
					}
					nRet = 0;
				}
			}break;
		case MSG_DAILY_SINGLE_TASK_REWARD:
			{
				MsgDailySingleTaskReward *body = (MsgDailySingleTaskReward *)msgInfo.body;
				size = sizeof(MsgDailySingleTaskReward);
				msg = create_send_msg(size);
				if (msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1 || m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}
					if (m_stream.writeInt(body->unActivenessChanged) == -1)
					{
						break;
					}
					if(!write_reward(body->reward))
					{
						break;
					}
					nRet = 0;
				}
			}break;
		case MSG_GOLDEN_TOUCH_RESPONSE:
			{
				MsgGoldenTouchResponse *body = (MsgGoldenTouchResponse *)msgInfo.body;
				size = sizeof(MsgGoldenTouchResponse);
				msg = create_send_msg(size);
				if (msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1 || m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}
					if (m_stream.writeInt(body->m_unBellCount) == -1 || m_stream.writeInt(body->m_unCriticalTimes) == -1)
					{
						break;
					}
					nRet = 0;
				}
			}break;
		case MSG_OBTAINED_ACTIVENESS_REWARD:
			{
				MsgObtainedActivenessReward *body = (MsgObtainedActivenessReward *)msgInfo.body;
				size = sizeof(MsgObtainedActivenessReward);
				msg = create_send_msg(size);
				if (msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1|| m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}
					if(m_stream.writeInt(body->unObtainedCount) == -1)
					{
						break;
					}
					int i=0;
					for (;i<MAX_ACTIVENESS_COUNT;++i)
					{
						if (m_stream.writeInt(body->obtainedList[i]) == -1)
						{
							break;
						}
					}
					nRet = i == MAX_ACTIVENESS_COUNT ? 0 : -1;
				}
			}break;
		case MSG_ADD_NEW_MAP_RESPONSE:
			{
				MsgAddNewMapResponse *body = (MsgAddNewMapResponse *)msgInfo.body;
				size = sizeof(MsgAddNewMapResponse);
				msg = create_send_msg(size);
				if (msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1|| m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}
					if(m_stream.writeInt(body->unMapID) == -1)
					{
						break;
					}
					nRet = 0 ;
				}

			}break;
		case MSG_GM_RESPONSE://GM推送
			{
				MsgGMRsponse *body = (MsgGMRsponse *)msgInfo.body;
				size = sizeof(MsgGMRsponse);
				msg = create_send_msg(size);
				if (msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1|| m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}
					if(m_stream.writeInt(body->unCount) == -1)
					{
						break;
					}

					nRet = 0 ;
					for (int i=0;i<body->unCount;i++)
					{
						if(m_stream.writeInt(body->info[i].unFromID)==-1 ||
						m_stream.writeInt(body->info[i].unToID)==-1 ||
						m_stream.writeInt(body->info[i].unType)==-1 ||
						m_stream.writeInt(body->info[i].unGoodID)==-1 ||
						m_stream.writeInt(body->info[i].unLevel)==-1 ||
						m_stream.writeString(body->info[i].fromName,MAX_CHARACTER_LENGTH)==-1 ||
						m_stream.writeString(body->info[i].strBuffer,MAIL_BODY_LEN)==-1)
						{
							nRet = -1 ;
							break;
						}
					}
					
				}
			}break;
		case MSG_GET_LA_LIST_RESPONST://限时活动
			{
				MsgGMLimitedActivityListResponse *body = (MsgGMLimitedActivityListResponse *)msgInfo.body;
				size = sizeof(MsgGMLimitedActivityListResponse);
				msg = create_send_msg(size);
				if (msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1|| m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}
					if(m_stream.writeInt(body->m_unCount) == -1)
					{
						break;
					}
					//LimitedActivityInfo
					nRet = 0 ;
					for (int i=0;i<body->m_unCount;i++)
					{
						if(m_stream.writeInt(body->m_LAList[i].unLAID)==-1 ||
						m_stream.writeInt(body->m_LAList[i].unCloseTime)==-1 ||
						m_stream.writeInt(body->m_LAList[i].unProgress)==-1 ||
						m_stream.writeInt(body->m_LAList[i].unLinkType)==-1 ||
						m_stream.writeInt(body->m_LAList[i].unRelatedCount)==-1)
						{
							nRet = -1;
							break;
						}
						for (int j=0;j<body->m_LAList[i].unRelatedCount;j++)
						{
							m_stream.writeInt(body->m_LAList[i].unRelatedItems[j]);
						}
					}
					nRet = 0 ;
				}
			}break;
		case MSG_GET_LA_REWARD_RESPONST:
			{
				MsgGMLARewardResponse *body = (MsgGMLARewardResponse *)msgInfo.body;
				size = sizeof(MsgGMLARewardResponse);
				msg = create_send_msg(size);
				if (msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1|| m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}

					if (!write_reward(body->stReward))
					{
						break;
					}
					nRet = 0 ;
				}
			}
			break;
		case MSG_DO_ORDER_RESPONSE:
			{
				MsgDoOrderResponse *body = (MsgDoOrderResponse *)msgInfo.body;
				size = sizeof(MsgDoOrderResponse);

				msg = create_send_msg(size);
				if(msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1 || m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}

// 					if(m_stream.writeInt(body->m_unID) == -1)
// 					{
// 						break;
// 					}

					if(m_stream.writeString(body->orderID,RECHARGE_ORDERID_LEN) == -1)
					{
						break;
					}

					nRet = 0;
				}
			}break;
		case MSG_DO_RECHARGE_RESPONSE:
			{
				MsgDoRechargeResponse *body = (MsgDoRechargeResponse *)msgInfo.body;
				size = sizeof(MsgDoRechargeResponse);

				msg = create_send_msg(size);
				if(msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1 || m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}

					if(m_stream.writeString(body->orderID,RECHARGE_ORDERID_LEN) == -1)
					{
						break;
					}

					if(m_stream.writeInt(body->deal_time) == -1 || m_stream.writeInt(body->unRenminbi) == -1 
						|| m_stream.writeInt(body->unMoney) == -1 || m_stream.writeInt(body->unProductId) == -1
						|| m_stream.writeInt(body->unProductCount) == -1 || m_stream.writeInt(body->unbitField)==-1
						|| m_stream.writeInt(body->unMoneyEx) == -1)
					{
						break;
					}

					nRet = 0;
				}
			}break;
		case MSG_DO_PIECE_ROLE_RESPONSE://碎片转角色
			{
				MsgDoPieceToRoleResponse *body = (MsgDoPieceToRoleResponse *)msgInfo.body;
				size = sizeof(MsgDoPieceToRoleResponse);
				msg = create_send_msg(size);
				if (msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1|| m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}

					if (m_stream.writeInt(body->unPlayerID) == -1)
					{
						break;
					}

					if (m_stream.writeInt(body->unPieceRoleID) == -1)
					{
						break;
					}

// 					if (!Write_CostInfoList(body->cost))
// 					{
// 						break;
// 					}
					nRet = 0 ;
				}
			}break;
		case MSG_DO_GET_RECHARGE_INFO_RESPONSE:
			{
				MsgDoGetRechargeInfoResponse *body = (MsgDoGetRechargeInfoResponse *)msgInfo.body;
				size = sizeof(MsgDoGetRechargeInfoResponse);
				msg = create_send_msg(size);
				if (msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1|| m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}

					if (m_stream.writeInt(body->m_bitField) == -1)
					{
						break;
					}

					if (m_stream.writeInt(body->info.vip_level) == -1 || m_stream.writeInt(body->info.vip_amount) == -1)
					{
						break;
					}

					if (m_stream.writeInt(body->m_Productlist.unCount) == -1)
					{
						break;
					}

					nRet = 0 ;
					for (int i=0;i<body->m_Productlist.unCount;i++)
					{
						if (m_stream.writeInt(body->m_Productlist.list[i]) == -1)
						{
							nRet = -1;
							break;
						}
					}
				}
			}break;
		case MSG_DO_SHARED_ACTIVITES_RESPONSE:
			{
				MsgSharedActivitesResponse *body = (MsgSharedActivitesResponse *)msgInfo.body;
				size = sizeof(MsgSharedActivitesResponse);
				msg = create_send_msg(size);
				if (msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1 || m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}

					if (!write_reward(body->reward))
					{
						break;
					}

					nRet = 0 ;
				}
			}break;
		case MSG_DO_VIP_GIFT_RESPONSE:
			{
				MsgVipGiftResponse *body = (MsgVipGiftResponse *)msgInfo.body;
				size = sizeof(MsgVipGiftResponse);
				msg = create_send_msg(size);
				if (msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1 || m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}
					
					if(m_stream.writeInt(body->unGiftID) == -1)
					{
						break;
					}

					if (!write_reward(body->reward))
					{
						break;
					}

					nRet = 0 ;
				}
			}break;
		case MSG_DESTROY_MSG_ACK://停封删除
			{
				this->setObjStatus(SERVICE_OBJ_DESTROY);
				this->set_destroy(true);
				m_unActiveTimer = 0;
			}break;
		case MSG_DO_DB_SERVER_TIME_HARD:
			{
				printf("db server is hard !!!sleep some times\n");
				Sleep(2000);
			}break;
		case MSG_DO_Get_BadgeGaint_RESPONSE:
			{
				MsgGetBadgeGaintResponse *body = (MsgGetBadgeGaintResponse *)msgInfo.body;
				size = body->unCount*sizeof(MsgGetBadgeGaintResponse::tagGetBadgeGaintInfo) + sizeof(ACE_UINT32) + sizeof(MsgBaseResponse) ;
				msg = create_send_msg(size);
				if (msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1 || m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}

					if(m_stream.writeInt(body->unCount) == -1)
					{
						break;
					}

					nRet = 0 ;
					for (int i=0;i<body->unCount;i++)
					{
						if (m_stream.writeInt(body->getBadgeGaintinfo[i].unGaint[0])== -1 
							|| m_stream.writeInt(body->getBadgeGaintinfo[i].unGaint[1])== -1
							||m_stream.writeInt(body->getBadgeGaintinfo[i].unGaint[2])== -1
							||m_stream.writeInt(body->getBadgeGaintinfo[i].unGaint[3])== -1)
						{
							nRet = -1;
							break;
						}
					}
				}
			}break;
		case MSG_DO_Up_BadgeGaint_RESPONSE:
			{
				MsgBaseResponse *body = (MsgBaseResponse *)msgInfo.body;
				size = sizeof(MsgBaseResponse);
				msg = create_send_msg(size);
				if (msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1 || m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}
					nRet = 0;
				}
			}break;
		case MSG_DO_Up_BadgeGaint_RESPONSEEX:
			{
				MsgBaseResponse *body = (MsgBaseResponse *)msgInfo.body;
				size = sizeof(MsgBaseResponse);
				msg = create_send_msg(size);
				if (msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1 || m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}
					nRet = 0;
				}
			}break;
		case MSG_DO_GET_Badge_RESPONSE:
			{
				MsgGETBadgeResponse *body = (MsgGETBadgeResponse *)msgInfo.body;
				size = sizeof(MsgGETBadgeResponse);
				msg = create_send_msg(size);
				if (msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1 || m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}

					if(m_stream.writeInt(body->unMaxPage) == -1 || m_stream.writeInt(body->unPage) == -1 || m_stream.writeInt(body->unCount) == -1)
					{
						break;
					}
					nRet = 0 ;
					for (int i=0;i<body->unCount;i++)
					{
						if (m_stream.writeInt(body->unBadgeInfo[i].unID)== -1 
							|| m_stream.writeInt(body->unBadgeInfo[i].m_gain)== -1
							||m_stream.writeInt(body->unBadgeInfo[i].m_charge_value)== -1
							||m_stream.writeInt(body->unBadgeInfo[i].m_flag)== -1)
						{
							nRet = -1;
							break;
						}
					}
				}
			}break;
		case MSG_GET_CHARACTER_INFO_RESPONSE:
			{
				MsgGetCharacterInfoResponse *body = (MsgGetCharacterInfoResponse *)msgInfo.body;
				size = sizeof(MsgGetCharacterInfoResponse);
				msg = create_send_msg(size);
				if (msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1 || m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}

					if (!write_character_info(&body->info))
					{
						break;
					}

					nRet = 0;
				}

			}break;
		case MSG_INVITE_FRIEND_RESPONSE:
			{
				MsgGetCharacterInfoResponse *body = (MsgGetCharacterInfoResponse *)msgInfo.body;
				size = sizeof(MsgGetCharacterInfoResponse);
				msg = create_send_msg(size);
				if (msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1 || m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}

					nRet = 0;
				}
			}break;
		case MSG_GET_PVP_INFO_RESPONSE:
			{
				MsgGetPVPInfoResponse *body = (MsgGetPVPInfoResponse *)msgInfo.body;
				size = sizeof(MsgGetPVPInfoResponse);
				msg = create_send_msg(size);
				if (msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1 || m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}

					if (m_stream.writeInt(body->info.nhonour)==-1 
						|| m_stream.writeInt(body->info.unAttackTimes)==-1
						||m_stream.writeInt(body->info.unLastChangeTime)==-1 
						||m_stream.writeInt(body->info.unWinLost)==-1 
						|| m_stream.writeInt(body->info.unBuyCount)==-1
						||m_stream.writeInt(body->info.unFreshenCount)==-1
						|| m_stream.writeInt(body->info.nhonourRank)==-1)
					{
						nRet = -1;
						break;
					}

					nRet = 0;
				}
			}break;
		case MSG_PVP_ENTER_FIGHT_RESPONSE:
			{
				MsgPVPEnterFightResponse *body = (MsgPVPEnterFightResponse *)msgInfo.body;
				size = sizeof(MsgPVPEnterFightResponse);
				msg = create_send_msg(size);
				if (msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1 || m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}

					//写入基础信息
					if (m_stream.writeInt(body->info.nhonour)==-1 
						|| m_stream.writeInt(body->info.unAttackTimes)==-1
						|| m_stream.writeInt(body->info.unLastChangeTime)==-1
						|| m_stream.writeInt(body->info.unWinLost)==-1 
						|| m_stream.writeInt(body->info.unBuyCount)==-1
						|| m_stream.writeInt(body->info.unFreshenCount)==-1)
					{
						nRet = -1;
						break;
					}

					if(m_stream.writeInt(body->_array.uncount) == -1)
					{
						nRet = -1;
						break;
					}

					nRet = 0;
					for (int i=0;i<body->_array.uncount;i++)
					{
						if(!write_character_info(&(body->_array.playerinfo[i])))
						{
							nRet = -1;
							break;
						}
					}
				}
			}break;
		case MSG_PVP_GET_ORDER_RESPONSE:
			{
				MsgPVPGetOrderResponse *body = (MsgPVPGetOrderResponse *)msgInfo.body;
				size = sizeof(MsgPVPGetOrderResponse);
				msg = create_send_msg(size);
				if (msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1 || m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}

					if (m_stream.writeInt(body->unCount)==-1)
					{
						nRet = -1;
						break;
					}

					nRet = 0;
					for (int i=0;i<body->unCount;i++)
					{
						if (m_stream.writeInt(body->userInfoArray[i].m_userID)==-1
							||m_stream.writeInt(body->userInfoArray[i].m_roleHeadID)==-1
							||m_stream.writeInt(body->userInfoArray[i].m_unStep)==-1
							||m_stream.writeInt(body->userInfoArray[i].m_honour)==-1
							||m_stream.writeString(body->userInfoArray[i].name, MAX_CHARACTER_LENGTH) == -1
							)
						{
							nRet = -1;
							break;
						}
					}
				}
			}break;
		case MSG_PVP_BUY_TIMES_RESPONSE:
			{
				MsgPVPBuyTimesResponse *body = (MsgPVPBuyTimesResponse *)msgInfo.body;
				size = sizeof(MsgPVPBuyTimesResponse);
				msg = create_send_msg(size);
				if (msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1 || m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}

					//写入基础信息
					if (m_stream.writeInt(body->info.nhonour)==-1 
						|| m_stream.writeInt(body->info.unAttackTimes)==-1
						|| m_stream.writeInt(body->info.unLastChangeTime)==-1
						|| m_stream.writeInt(body->info.unWinLost)==-1 
						|| m_stream.writeInt(body->info.unBuyCount)==-1
						|| m_stream.writeInt(body->info.unFreshenCount)==-1)
					{
						nRet = -1;
						break;
					}

					if (m_stream.writeInt(body->unMoney)==-1 )
					{
						nRet = -1;
						break;
					}

					nRet = 0;
				}
			}break;
		case MSG_PVP_ENTER_RESPONSE:
			{
				MsgPVPEnterResponse *body = (MsgPVPEnterResponse *)msgInfo.body;
				size = sizeof(MsgPVPEnterResponse);
				msg = create_send_msg(size);
				if (msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1 || m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}

					//写入基础信息
					if (m_stream.writeInt(body->info.nhonour)==-1 
						|| m_stream.writeInt(body->info.unAttackTimes)==-1
						|| m_stream.writeInt(body->info.unLastChangeTime)==-1
						|| m_stream.writeInt(body->info.unWinLost)==-1 
						|| m_stream.writeInt(body->info.unBuyCount)==-1
						|| m_stream.writeInt(body->info.unFreshenCount)==-1)
					{
						nRet = -1;
						break;
					}

					nRet = 0;
				}
			}break;
		case MSG_PVP_ACCOUNTS_RESPONSE:
			{
				MsgPVPAccountResponse *body = (MsgPVPAccountResponse *)msgInfo.body;
				size = sizeof(MsgPVPAccountResponse);
				msg = create_send_msg(size);
				if (msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1 || m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}

					if (m_stream.writeInt(body->score)==-1 )
					{
						nRet = -1;
						break;
					}

					//写入基础信息
					if (m_stream.writeInt(body->info.nhonour)==-1 
						|| m_stream.writeInt(body->info.unAttackTimes)==-1
						|| m_stream.writeInt(body->info.unLastChangeTime)==-1
						|| m_stream.writeInt(body->info.unWinLost)==-1 
						|| m_stream.writeInt(body->info.unBuyCount)==-1
						|| m_stream.writeInt(body->info.unFreshenCount)==-1)
					{
						nRet = -1;
						break;
					}

					nRet = 0;
				}
			}break;
		case MSG_PVP_GET_FightRecordInfo_RESPONSE:
			{
				MsgPVPFightRecordInfoResponse *body = (MsgPVPFightRecordInfoResponse *)msgInfo.body;
				size = sizeof(MsgPVPFightRecordInfoResponse);
				msg = create_send_msg(size);
				if (msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1 || m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}

					//写入基础信息
					if (m_stream.writeInt(body->pvpinfo.nhonour)==-1 
						|| m_stream.writeInt(body->pvpinfo.unAttackTimes)==-1
						|| m_stream.writeInt(body->pvpinfo.unLastChangeTime)==-1
						|| m_stream.writeInt(body->pvpinfo.unWinLost)==-1 
						|| m_stream.writeInt(body->pvpinfo.unBuyCount)==-1
						|| m_stream.writeInt(body->pvpinfo.unFreshenCount)==-1)
					{
						nRet = -1;
						break;
					}

					if (m_stream.writeInt(body->info.unCount) == -1)
					{
						nRet = -1;
						break;
					}

					nRet = 0;
					for (int i=0;i<body->info.unCount;i++)
					{
						if(!Write_pvp_FightRecordInfo(body->info.info[i]))
						{
							nRet = -1;
							break;
						}
					}
				}
			}break;
		case MSG_Get_badge_info_RESPONSE:
			{
				MsgGetBadgeInfoResponse *body = (MsgGetBadgeInfoResponse *)msgInfo.body;
				size = sizeof(MsgGetBadgeInfoResponse);
				msg = create_send_msg(size);
				if (msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1 || m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}
					if (m_stream.writeInt(body->unCharacterID) == -1 || m_stream.writeInt(body->bsInfos.unCount))
					{
						break;
					}

					nRet = 0;
					for (int i=0;i<body->bsInfos.unCount;i++)
					{
						//写入基础信息
						if (m_stream.writeInt(body->bsInfos.bsInfo[i].gongji_1_0)==-1 || m_stream.writeInt(body->bsInfos.bsInfo[i].gongji_1_1)==-1 
							|| m_stream.writeInt(body->bsInfos.bsInfo[i].shengming_2_0)==-1 || m_stream.writeInt(body->bsInfos.bsInfo[i].shengming_2_1)==-1 
							|| m_stream.writeInt(body->bsInfos.bsInfo[i].baoji_3_0)==-1 || m_stream.writeInt(body->bsInfos.bsInfo[i].baoji_3_1)==-1 
							|| m_stream.writeInt(body->bsInfos.bsInfo[i].fangyu_4_0)==-1 || m_stream.writeInt(body->bsInfos.bsInfo[i].fangyu_4_1)==-1 
							|| m_stream.writeInt(body->bsInfos.bsInfo[i].beike_5_0)==-1 || m_stream.writeInt(body->bsInfos.bsInfo[i].beike_5_1)==-1 
							|| m_stream.writeInt(body->bsInfos.bsInfo[i].hejin_6_0)==-1 || m_stream.writeInt(body->bsInfos.bsInfo[i].hejin_6_1)==-1 
							|| m_stream.writeInt(body->bsInfos.bsInfo[i].roleID)==-1)
						{
							nRet = -1;
							break;
						}

					}
				}
			}break;
		case MSG_Get_active_inofo_RESBONSE:
			{
				MsgGetActiveInfoResponse *body = (MsgGetActiveInfoResponse *)msgInfo.body;
				size = sizeof(MsgGetActiveInfoResponse);
				msg = create_send_msg(size);
				if (msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1 || m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}
					if (m_stream.writeInt(body->key) == -1 )
					{
						break;
					}

					nRet = 0;
				}
			}break;
		case MSG_Get_POWER_RESBONSE:
			{
				MsgGetPowerResponse *body = (MsgGetPowerResponse *)msgInfo.body;
				size = sizeof(MsgGetPowerResponse);
				msg = create_send_msg(size);
				if (msg != NULL)
				{
					m_stream.reset(msg->base(), msg->size());
					if(m_stream.writeInt(msgInfo.m_head->unType) == -1 || m_stream.writeInt(body->unSN) == -1 || m_stream.writeInt(body->nResult) == -1)
					{
						break;
					}
					if (m_stream.writeInt(body->power) == -1 )
					{
						break;
					}

					nRet = 0;
				}
			}break;
		}
	}

	if(nRet == -1 && msg != NULL)
	{
		msg->release();
		msg = NULL;
	}

	if(msg != NULL)
	{
		/*printf("get msg sig = %d,current = %d\n", msgInfo.i_head->unSig, m_unLoginID);*/
		if(msgInfo.i_head->unSig != m_unLoginID)
		{
			msg->release();
			msg = NULL;
			printf("it's old msg, discard[0x%08x]!!!\n", msgInfo.m_head->unType);
		}
		else
		{
			if(set_send_size(msg, m_stream.getCursor()) == -1)
			{
				msg->release();
				msg = NULL;
			}
		}
	}

	return msg;
}

void GatewaySession::send_character_query_response()
{
	ACE_Message_Block *msg = create_send_msg(sizeof(MsgCreateCharacterResponse));
	if(msg == NULL)
	{
		return;
	}

	m_stream.reset(msg->base(), msg->size());

	if(m_stream.writeInt(MSG_QUERY_CHARACTER_RESPONSE) == -1)
	{
		msg->release();
		return;
	}

	if(m_stream.writeInt(m_unCurrentRequestSN) == -1)
	{
		msg->release();
		return;
	}

	if(m_stream.writeInt(0) == -1)
	{
		msg->release();
		return;
	}

	for(int i = 0;i < MAX_PLAYER_PER_ACCOUNT;i ++)
	{
		if(m_stream.writeInt(m_CharacterList[i].unItemID) == -1)
		{
			msg->release();
			return;
		}

		if(m_stream.writeInt(m_CharacterList[i].unLevel) == -1)
		{
			msg->release();
			return;
		}

		if(m_stream.writeString(m_CharacterList[i].name, MAX_CHARACTER_LENGTH) == -1)
		{
			msg->release();
			return;
		}
	}

	if(set_send_size(msg, m_stream.getCursor()) == -1)
	{
		msg->release();
		return;
	}

	if(send_msg_2_internet(msg) == -1)
	{
		msg->release();
	}

	send_response_end(0);
}


void GatewaySession::send_response_end(int ret)
{
	ACE_Message_Block *msg = create_send_msg(sizeof(MsgResponseEnd));
	if(msg == NULL)
	{
		return;
	}

	m_stream.reset(msg->base(), msg->size());

	if(m_stream.writeInt(MSG_RESPONSE_END) == -1)
	{
		msg->release();
		return;
	}

	if(m_stream.writeInt(m_unCurrentRequestSN) == -1)
	{
		msg->release();
		return;
	}

	if(m_stream.writeInt(ret) == -1)
	{
		msg->release();
		return;
	}

	if(set_send_size(msg, m_stream.getCursor()) == -1)
	{
		msg->release();
		return;
	}

	if(send_msg_2_internet(msg) == -1)
	{
		msg->release();
	}
}

void GatewaySession::send_select_msg(ACE_UINT32 unCharacterID)
{
	m_unCurrentCharacterID = unCharacterID;

	MsgSelectCharacterRequest info;
	info.unSN = m_unCurrentRequestSN;
	info.unCharacterID = unCharacterID;
	info.unPlayerID = 0;

	int n = sendMsg(SERVICE_MESSAGE_TYPE_USER, MSG_SELECT_CHARACTER_REQUEST, (char *)&info, sizeof(MsgSelectCharacterRequest), OBJ_ID_NONE, ADAPTER_MAP_MGR, unCharacterID);

	//send_response_end(0);
}


bool GatewaySession::write_package_cell(PackageCell *cell)
{
	if(m_stream.writeInt(cell->unIdx) == -1 || m_stream.writeInt(cell->item.unCount) == -1)
	{
		return false;
	}

	return write_item_info(&cell->item.item);
	/*

	if(m_stream.writeInt(cell->item.item.unResID) == -1)
	{
		return false;
	}

	if(m_stream.writeInt(cell->item.item.info.equipment.unLevel) == -1 || m_stream.writeInt(cell->item.item.info.equipment.unStep) == -1)
	{
		return false;
	}

	return true;
	*/
}

bool GatewaySession::write_reward(RewardInfo &reward)
{
	bool ret = false;
	if(m_stream.writeInt(reward.unCoin) == -1 
		|| m_stream.writeInt(reward.unMoney) == -1 || m_stream.writeInt(reward.unExp) == -1 
		|| m_stream.writeInt(reward.unPowerPoint) == -1 || m_stream.writeInt(reward.unHonour) == -1 
		|| m_stream.writeInt(reward.unRecharge) == -1 || m_stream.writeInt(reward.unEnergy) == -1
		|| m_stream.writeInt(reward.unPVPEnergy) == -1 || m_stream.writeInt(reward.unFriendship) == -1
		||m_stream.writeInt(reward.unDynamicEnergy) == -1)
	{
		return false;
	}

	if(m_stream.writeInt(reward.unCount) == -1)
	{
		return false;
	}

	int i = 0;
	for(i = 0;i < reward.unCount;i ++)
	{
		if(m_stream.writeInt(reward.list[i].unCount) == -1 || m_stream.writeInt(reward.list[i].item.unResID) == -1 
			|| m_stream.writeInt(reward.list[i].item.info.equipment.unLevel) == -1 || m_stream.writeInt(reward.list[i].item.info.equipment.unStep) == -1)
		{
			return false;
		}
	}

	return true;
}

bool GatewaySession::write_character_info(CharacterInfoExt *info)
{
	if(m_stream.writeInt(info->unItemID) == -1)
	{
		return false;
	}

	if(m_stream.writeInt(info->unLevel) == -1)
	{
		return false;
	}

	if(m_stream.writeString(info->name, MAX_CHARACTER_LENGTH) == -1)
	{
		return false;
	}

	/*
	int i;
	for(i = 0;i < MAX_EQUIPMENT_COUNT;i ++)
	{
		if(!this->write_package_cell(&info->equipmentList[i]))
		{
			return false;
		}
	}

	for(i = 0;i < PROPERTY_ID_MAX;i ++)
	{
		if(m_stream.writeFloat(info->propertyList[i].fValue) == -1 || m_stream.writeFloat(info->propertyList[i].fScale) == -1)
		{
			return false;
		}
	}

	if(m_stream.writeInt(info->unSkillID) == -1)
	{
		return false;
	}
	*/
	if(!write_team_info(&info->pveTeam))
	{
		return false;
	}

	if(!write_team_info(&info->pvpTeam))
	{
		return false;
	}

	if(m_stream.writeInt(info->unVipLevel) == -1)
	{
		return false;
	}

	if (!Write_badge_info(info->badgeShuxing))
	{
		return false;
	}

	return true;
}

bool GatewaySession::write_friend_info(FriendInfo *info)
{
	if(!write_character_info(info))
	{
		return false;
	}

	if(m_stream.writeInt(info->unCooldown) == -1 || m_stream.writeInt(info->unLastInteractionTime) == -1 || m_stream.writeInt(info->unInteractionFlag) == -1)
	{
		return false;
	}

	return true;
}

bool GatewaySession::write_map_instance_info(MapInstanceInfo *info)
{
	if(m_stream.writeInt(info->unMapID) == -1 || m_stream.writeInt(info->unSpecialBossID) == -1 || m_stream.writeInt(info->unItemCount) == -1)
	{
		return false;
	}

	if(m_stream.writeInt(info->nGlobalMapEventType) == -1)
	{
		return false;
	}

	if(!write_character_info(&info->friendInfo))
	{
		return false;
	}

	return true;
}

/*
bool GatewaySession::write_battle_info(MapBattleInfo *info)
{

	if(m_stream.writeInt(info->isValid) == -1 || m_stream.writeInt(info->nCurrentSection) == -1 || m_stream.writeInt(info->nLauchCount) == -1)
	{
		return false;
	}

	if(m_stream.writeInt(info->nBellCount) == -1 || m_stream.writeInt(info->nRandSeed) == -1)
	{
		return false;
	}

	int i;
	int j;

	for(i = 0;i < (MAX_PLAYER_SELECTED_COUNT + 2);i ++)
	{
		if(m_stream.writeInt(info->entityInfo.playerList[i].hp) == -1)
		{
			return false;
		}

		for(j = 0;j < MAX_ITEM_LIST_PER_PLAYER;j ++)
		{
			if(m_stream.writeInt(info->entityInfo.playerList[i].itemList[j]) == -1)
			{
				return false;
			}
		}
	}

	for(i = 0;i < MAX_MONSTER_PER_SECTION;i ++)
	{
		if(m_stream.writeInt(info->entityInfo.monsterList[i].hp) == -1)
		{
			return false;
		}
	}

	for(i = 0;i < MAX_ITEM_PER_SECTION;i ++)
	{
		if(m_stream.writeInt(info->entityInfo.itemList[i].isDestroyed) == -1)
		{
			return false;
		}
	}


	return true;
}
*/

bool GatewaySession::write_item_info(ItemInfo *itemInfo)
{
	if(m_stream.writeInt(itemInfo->unResID) == -1)
	{
		return false;
	}

	if(m_stream.writeInt(itemInfo->info.equipment.unLevel) == -1 || m_stream.writeInt(itemInfo->info.equipment.unStep) == -1)
	{
		return false;
	}

	return true;
}

/*
typedef struct tagPlayerInfo : public BaseItemInfo
{
ACE_UINT32 unLevel;
ItemInfo weapon;
ItemInfo armor;
ACE_UINT32 unPlayerSkillID;
}PlayerInfo;
*/

bool GatewaySession::write_player_info(PlayerInfo *player)
{
	if(m_stream.writeInt(player->unItemID) == -1 || m_stream.writeInt(player->unLevel) == -1 || m_stream.writeInt(player->unStep) == -1)
	{
		return false;
	}

	if(!write_item_info(&player->weapon) || !write_item_info(&player->armor) || !write_item_info(&player->belt) || !write_item_info(&player->staff))
	{
		return false;
	}

	if(m_stream.writeInt(player->unPlayerSkillID) == -1 || m_stream.writeInt(player->unSoulCount) == -1)
	{
		return false;
	}

	return true;
}

bool GatewaySession::write_team_info(PlayerTeamInfo *teamInfo)
{
	if(!write_item_info(&teamInfo->staff))
	{
		return false;
	}

	int i;

	if(m_stream.writeInt(teamInfo->unCount) == -1 || m_stream.writeInt(teamInfo->unPoint) == -1)
	{
		return false;
	}

	for(i = 0;i < MAX_PLAYER_SELECTED_COUNT;i ++)
	{
		if(!write_player_info(&teamInfo->playerList[i]))
		{
			return false;
		}
	}

	for(i = 0;i < MAX_PLAYER_SELECTED_COUNT;i ++)
	{
		if(m_stream.writeInt(teamInfo->skillList[i]) == -1)
		{
			return false;
		}
	}

	for(i = 0;i < MAX_PLAYER_SELECTED_COUNT;i ++)
	{
		if(m_stream.writeInt(teamInfo->playerSkillList[i]) == -1)
		{
			return false;
		}
	}

	if(m_stream.writeInt(teamInfo->unStarCount) == -1)
	{
		return false;
	}

	return true;
}

bool GatewaySession::write_pvp_basic_info(PVPBasicInfo *basicInfo)
{
	int i;

	for(i = 0;i < MAX_PLAYER_SELECTED_COUNT;i ++)
	{
		if(m_stream.writeInt(basicInfo->playerList[i]) == -1)
		{
			return false;
		}
	}

	for(i = 0;i < MAX_PLAYER_SELECTED_COUNT;i ++)
	{
		if(m_stream.writeInt(basicInfo->playerSkillList[i]) == -1)
		{
			return false;
		}
	}
	/*
	
	if(m_stream.writeInt(basicInfo->honour) == -1)
	{
		return false;
	}
	*/
	return true;
}

bool GatewaySession::write_pvp_rank_info(PVPRankInfo *rankInfo)
{
	if(m_stream.writeInt(rankInfo->unSeasonID) == -1)
	{
		return false;
	}

	if(m_stream.writeInt(rankInfo->unScore) == -1)
	{
		return false;
	}

	if(m_stream.writeInt(rankInfo->unAll) == -1)
	{
		return false;
	}

	if(m_stream.writeInt(rankInfo->unWin) == -1)
	{
		return false;
	}

	if(m_stream.writeInt(rankInfo->nOrder) == -1)
	{
		return false;
	}

	if(m_stream.writeInt(rankInfo->unRank) == -1)
	{
		return false;
	}

	if(m_stream.writeInt(rankInfo->unRewardID) == -1)
	{
		return false;
	}

	return true;
}

bool GatewaySession::write_pvp_team_info(PVPTeamInfo *teamInfo)
{
	
	/*
	typedef struct tagPVPTeamInfo
	{
	ACE_UINT32 unScore;
	ACE_UINT32 unWin;
	ACE_UINT32 unAll;
	ACE_UINT32 unRankID;
	PlayerTeamInfo teamInfo;
	}PVPTeamInfo;
	*/
	if(m_stream.writeInt(teamInfo->unItemID) == -1)
	{
		return false;
	}

	if(m_stream.writeInt(teamInfo->unLevel) == -1)
	{
		return false;
	}

	if(m_stream.writeString(teamInfo->name, MAX_CHARACTER_LENGTH) == -1)
	{
		return false;
	}

	if(m_stream.writeInt(teamInfo->unScore) == -1)
	{
		return false;
	}

	if(m_stream.writeInt(teamInfo->unWin) == -1)
	{
		return false;
	}

	if(m_stream.writeInt(teamInfo->unAll) == -1)
	{
		return false;
	}

	if(m_stream.writeInt(teamInfo->unRankID) == -1)
	{
		return false;
	}

	if(!write_team_info(&teamInfo->teamInfo))
	{
		return false;
	}

	return true;
}

void GatewaySession::obj_timeout()
{
	if(m_unActiveTimer >= MAX_GATEWAY_SESSION_LIVE)
	{
		if (!m_isDestroyMsg)
		{
			MsgDestroyRequest info;
			info.unErrorCode = 0;
			sendMsg(SERVICE_MESSAGE_TYPE_USER, MSG_DESTROY_MSG_ACK, (char *)&info, sizeof(MsgDestroyRequest), OBJ_ID_NONE, ADAPTER_MAP_MGR, m_unCurrentCharacterID);//退出
			printf("destroy Gateway session：[%d]\n",m_unCurrentCharacterID);
		}
		this->setObjStatus(SERVICE_OBJ_DESTROY);
		this->set_destroy(true);
		m_unActiveTimer = 0;
	}
	else
	{
		m_unActiveTimer ++;
	}

	//printf("-------------GatewaySession time out:[%d]\n",m_unActiveTimer);
}

bool GatewaySession::write_mail_info( MailInfo *info )
{
	if(m_stream.writeInt(info->m_dwID) == -1)
	{
		return false;
	}

	if(m_stream.writeInt(info->m_dwIDinTable) == -1)
	{
		return false;
	}

	if(m_stream.writeInt(info->m_dwCharacterID) == -1)
	{
		return false;
	}

	if(m_stream.writeInt(info->m_dwFlag) == -1)
	{
		return false;
	}

	if(m_stream.writeInt(info->m_dwTimeoutDate) == -1)
	{
		return false;
	}

	if(m_stream.writeInt(info->m_dwReadDate) == -1)
	{
		return false;
	}

	for(int i = 0; i != MAIL_ATTACHMENT_LEN; i++)
	{
		if(!write_mail_attachment(&(info->m_aMailAttachment[i])))
			return false;
	}

	if(m_stream.writeString(info->m_strSenderName, MAIL_SENDER_NAME_LEN) == -1)
	{
		return false;
	}

	if(m_stream.writeString(info->m_strTitle, MAIL_TITLE_LEN) == -1)
	{
		return false;
	}

	if(m_stream.writeString(info->m_strBody, MAIL_BODY_LEN) == -1)
	{
		return false;
	}

	return true;
}

bool GatewaySession::write_mail_attachment( MailAttachment* info )
{
	if(m_stream.writeInt(info->m_dwItemID) == -1)
	{
		return false;
	}

	if(m_stream.writeInt(info->m_dwItemCount) == -1)
	{
		return false;
	}
	return true;
}

bool GatewaySession::Write_pvp_FightRecordInfo( FightRecordInfo & info )
{
	if (m_stream.writeInt(info.score) == -1 || m_stream.writeInt(info.isWin) == -1)
	{
		return false;
	}

	if (m_stream.writeInt(info.from.m_characterID)==-1
		||m_stream.writeInt(info.from.m_level)==-1
		||m_stream.writeInt(info.from.m_honour)==-1
		||m_stream.writeString(info.from.name,MAX_CHARACTER_LENGTH) == -1)
	{
		return false;
	}

	if (m_stream.writeInt(info.from.fightInfo.unCount) == -1)
	{
		return false;
	}

	for (int i=0;i<info.from.fightInfo.unCount;i++)
	{
		if (m_stream.writeInt(info.from.fightInfo.role_list[i]) == -1)
		{
			return false;
		}
	}

	for (int i=0;i<info.from.fightInfo.unCount;i++)
	{
		if (m_stream.writeInt(info.from.fightInfo.setup_list[i]) == -1)
		{
			return false;
		}
	}

	for (int i=0;i<info.from.fightInfo.unCount;i++)
	{
		if (m_stream.writeInt(info.from.fightInfo.score_list[i]) == -1)
		{
			return false;
		}
	}

	//----to

	if (m_stream.writeInt(info.to.m_characterID)==-1
		||m_stream.writeInt(info.to.m_level)==-1
		||m_stream.writeInt(info.to.m_honour)==-1
		||m_stream.writeString(info.to.name,MAX_CHARACTER_LENGTH) == -1)
	{
		return false;
	}

	if (m_stream.writeInt(info.to.fightInfo.unCount) == -1)
	{
		return false;
	}

	for (int i=0;i<info.to.fightInfo.unCount;i++)
	{
		if (m_stream.writeInt(info.to.fightInfo.role_list[i]) == -1)
		{
			return false;
		}
	}

	for (int i=0;i<info.to.fightInfo.unCount;i++)
	{
		if (m_stream.writeInt(info.to.fightInfo.setup_list[i]) == -1)
		{
			return false;
		}
	}

	for (int i=0;i<info.to.fightInfo.unCount;i++)
	{
		if (m_stream.writeInt(info.to.fightInfo.score_list[i]) == -1)
		{
			return false;
		}
	}

	return true;
}

bool GatewaySession::Read_BS_info( BadgeShuxing & info )
{
	if(m_stream.readInt(info.gongji_1_0) == -1 || m_stream.readInt(info.gongji_1_1) == -1
		|| m_stream.readInt(info.shengming_2_0) == -1|| m_stream.readInt(info.shengming_2_1) == -1
		|| m_stream.readInt(info.baoji_3_0) == -1|| m_stream.readInt(info.baoji_3_1) == -1
		|| m_stream.readInt(info.fangyu_4_0) == -1|| m_stream.readInt(info.fangyu_4_1) == -1
		|| m_stream.readInt(info.beike_5_0) == -1|| m_stream.readInt(info.beike_5_1) == -1
		|| m_stream.readInt(info.hejin_6_0) == -1|| m_stream.readInt(info.hejin_6_1) == -1
		|| m_stream.readInt(info.roleID) == -1
		)
	{
		return false;
	}

	return true;
}

bool GatewaySession::Write_badge_info( BadgeShuxingS & bsInfos )
{
	if (m_stream.writeInt(bsInfos.unCount))
	{
		return false;
	}

	for (int i=0;i<bsInfos.unCount;i++)
	{
		//写入基础信息
		if (m_stream.writeInt(bsInfos.bsInfo[i].gongji_1_0)==-1 || m_stream.writeInt(bsInfos.bsInfo[i].gongji_1_1)==-1 
			|| m_stream.writeInt(bsInfos.bsInfo[i].shengming_2_0)==-1 || m_stream.writeInt(bsInfos.bsInfo[i].shengming_2_1)==-1 
			|| m_stream.writeInt(bsInfos.bsInfo[i].baoji_3_0)==-1 || m_stream.writeInt(bsInfos.bsInfo[i].baoji_3_1)==-1 
			|| m_stream.writeInt(bsInfos.bsInfo[i].fangyu_4_0)==-1 || m_stream.writeInt(bsInfos.bsInfo[i].fangyu_4_1)==-1 
			|| m_stream.writeInt(bsInfos.bsInfo[i].beike_5_0)==-1 || m_stream.writeInt(bsInfos.bsInfo[i].beike_5_1)==-1 
			|| m_stream.writeInt(bsInfos.bsInfo[i].hejin_6_0)==-1 || m_stream.writeInt(bsInfos.bsInfo[i].hejin_6_1)==-1 
			|| m_stream.writeInt(bsInfos.bsInfo[i].roleID)==-1)
		{
			return false;
		}
	}

	return true;
}
