#include "FriendMgr.h"
#include "..\..\GameBase\Common\GameUtils.h"
#include "..\..\GameBase\res\GameConfig.h"
#include "..\Map.h"
#define MAX_TEM_PAGE_COUNT 10

FriendMgr::FriendMgr()
{
	m_unLockCount = 0;
	m_unInviteCount = 0;
	m_unFriendCount = 0;
	m_unExtraLimit = 0;
	m_unCurrentAssistFriendID  = 0;
	m_unCurrentAssistFriendship = 0;
	m_unAssistType = 1;
	m_bSendAssistEmail = false;
	ACE_OS::memset(m_requestInfoList, 0, sizeof(CharacterDetailRequestInfo) * CHARACTER_LIST_TYPE_MAX);
	ACE_OS::memset(m_inviteList, 0, sizeof(CharacterInfoExt) * MAX_INVITE_COUNT);
	ACE_OS::memset(m_friendList, 0, sizeof(FriendInfo) * MAX_FRIEND_COUNT);
	m_assistMember.clear();
	m_unCount0 = 0;
	m_unMaxPage0 =0;
	m_unPage0 =0;
	m_unCount1 = 0;
	m_unMaxPage1 =0;
	m_unPage1 =0;
	m_isHaveNew = false;
}

FriendMgr::~FriendMgr()
{

}

void FriendMgr::init(ACE_UINT32 unMaxFriendCount, ACE_UINT32 *inviteList, DBFriendInfo *friendList,BadgeShuxingS * bs_list, AssistInfo *assistList,DeleteFriendList & deletelist)
{
	m_deleteList = deletelist;
	DoDayChange();
	m_unMaxFriendCount = unMaxFriendCount;
	
	m_unInviteCount = 0;
	m_unFriendCount = 0;
	
	int i;
	for(i = 0;i < MAX_INVITE_COUNT;i ++)
	{
		m_inviteList[i].unItemID = inviteList[i];
		if(m_inviteList[i].unItemID != 0)
		{
			m_unInviteCount ++;
		}
		else
		{
			break;
		}
	}

	for(i = 0;i < MAX_FRIEND_COUNT;i ++)
	{
		m_friendList[i].unItemID = friendList[i].unCharacterID;
		m_friendList[i].unCooldown = friendList[i].unCooldown;
		m_friendList[i].unStartTime = friendList[i].unStartTime;
		m_friendList[i].badgeShuxing = bs_list[i];
		if(m_friendList[i].unItemID != 0)
		{
			m_unFriendCount ++;
		}
		else
		{
			break;
		}
	}

	for (i=0;i<MAX_ASSIST_COUNT;++i)
	{
		if (assistList[i].unAssistPlayerID == 0)
		{
			break;
		}
		m_assistMember.insert(std::make_pair(assistList[i].unAssistPlayerID, assistList[i].unAssistType));
	}

	GameUtils::sort(m_unInviteCount, m_inviteList, sizeof(CharacterInfoExt));
	GameUtils::sort(m_unFriendCount, m_friendList, sizeof(FriendInfo));

	//ACE_UINT32 tmp_list[MAX_FRIEND_COUNT];

	update_id_list(CHARACTER_LIST_TYPE_INVITE);
	//request_list_detail(CHARACTER_LIST_TYPE_INVITE);

	update_id_list(CHARACTER_LIST_TYPE_FRIEND);
	//request_list_detail(CHARACTER_LIST_TYPE_FRIEND);
}

void FriendMgr::clear_invite()
{
	
}

void FriendMgr::update_id_list(ACE_UINT32 unType)
{
	int i;
	if(unType == CHARACTER_LIST_TYPE_FRIEND)
	{
		for(i = 0;i < m_unFriendCount;i ++)
		{
			m_friendIDList[i] = m_friendList[i].unItemID;
		}
	}
	else
	{
		for(i = 0;i < m_unInviteCount;i ++)
		{
			m_inviteIDList[i] = m_inviteList[i].unItemID;
		}
	}
}

void FriendMgr::request_detail(ACE_UINT32 unType, ACE_UINT32 unSN,ACE_INT32 unPage)
{
	m_requestInfoList[unType].requestFlag = true;
	m_requestInfoList[unType].unRequestSN = unSN;

	request_list_detail(unType,unPage);

	/*
	if(m_requestInfoList[unType].unRequestCount > 0)
	{
		
	}
	else
	{
		//send 2 client
		//send_2_client(unType, unSN);
		request_list_detail(unType);
	}
	*/
	m_isHaveNew = false;
}

int FriendMgr::delete_friend_or_invitation(ACE_UINT32 unType, ACE_UINT32 unFriendID, ACE_UINT32 unSN)
{
	MsgDeleteFriendResponse response;
	response.unSN = unSN;
	response.nResult = -1;

	if(unType == CHARACTER_LIST_TYPE_FRIEND)
	{
		response.nResult = delete_friend(unFriendID);

		if(response.nResult == 0)
		{
			MsgDeleteFriendRequest request;
			request.unSN = unSN;
			request.unFriendID = m_map->m_unID;
			request.unType = CHARACTER_LIST_TYPE_FRIEND;

			m_map->sendMsg(SERVICE_MESSAGE_TYPE_USER, MSG_DELETE_FRIEND_REQUEST, (char *)&request, sizeof(MsgDeleteFriendRequest), OBJ_ID_NONE, ADAPTER_MAP_MGR, unFriendID);
		}
	}
	else
	{
		response.nResult =  this->delete_invitation(unFriendID); //GameUtils::delete_element(m_unInviteCount, m_inviteList, sizeof(CharacterInfoExt), unFriendID);
	}

	m_map->send_msg_2_client(SERVICE_MESSAGE_TYPE_USER, MSG_DELETE_FRIEND_RESPONSE, (char *)&response, sizeof(MsgDeleteFriendResponse));
	m_map->send_response_end(m_map->m_unUserID, unSN);

	return 0;
}

void FriendMgr::send_2_client(ACE_UINT32 unType, ACE_UINT32 unSN)
{
	//char send_buff[4096];
	int size = 0;
	if(unType == CHARACTER_LIST_TYPE_FRIEND)
	{
		MsgFriendDetailResponse *msg = (MsgFriendDetailResponse *)public_send_buff;

		int tmp_c = m_unCount0;

		msg->nResult = 0;
		msg->unSN = unSN;
		msg->unMaxFriendCount = m_unMaxFriendCount;
		msg->unCount = tmp_c;
		msg->unMaxPage = m_unMaxPage0;
		msg->unPage = m_unPage0;
		ACE_OS::memcpy(msg->list, m_friendList + m_unPage0*MAX_TEM_PAGE_COUNT, sizeof(FriendInfo) * tmp_c);

		ACE_UINT32 t = GameUtils::get_utc();

		for(int i = 0;i < tmp_c;i ++)
		{
			ACE_UINT32 tmp = t - msg->list[i].unStartTime;
			if(msg->list[i].unCooldown <= tmp)
			{
				msg->list[i].unCooldown = 0;
			}
			else
			{
				msg->list[i].unCooldown = msg->list[i].unCooldown - tmp;
			}
		}

		size = sizeof(MsgFriendDetailResponse) + (tmp_c-1) * sizeof(FriendInfo);

		m_map->send_msg_2_client(SERVICE_MESSAGE_TYPE_USER, MSG_FRIEND_DETAIL_RESPONSE, (char *)msg, size);
	}
	else
	{
		MsgInviteDetailResponse *msg = (MsgInviteDetailResponse *)public_send_buff;

		msg->nResult = 0;
		msg->unSN = unSN;
		msg->unCount = m_unCount1;
		msg->unMaxPage = m_unMaxPage1;
		msg->unPage = m_unPage1;
		ACE_OS::memcpy(msg->list, m_inviteList + m_unPage1*MAX_TEM_PAGE_COUNT, sizeof(CharacterInfoExt) * m_unCount1);

		size = sizeof(MsgInviteDetailResponse) + (m_unCount1-1) * sizeof(CharacterInfoExt);

		m_map->send_msg_2_client(SERVICE_MESSAGE_TYPE_USER, MSG_INVITE_DETAIL_RESPONSE, (char *)msg, size);
	}

	m_map->send_response_end(m_map->m_unUserID, unSN);
}

void FriendMgr::request_list_detail(ACE_UINT32 unType,ACE_INT32 unPage)
{
	m_requestInfoList[unType].unRequestCount ++;
	bool isAll = false;

	if(unPage <= 0)
	{
		unPage = 1;
		isAll = true;
	}
	unPage--;

	ACE_UINT32 unMaxPage = 0;
	ACE_UINT32 unCount = 0;
	ACE_UINT32 *list;

	if(unType == CHARACTER_LIST_TYPE_FRIEND)
	{
		unMaxPage = (m_unFriendCount + MAX_TEM_PAGE_COUNT -1)/MAX_TEM_PAGE_COUNT;
		if (unMaxPage == 0)
		{
			unPage = 0;
			unCount = 0;
		}
		else
		{
			if (unPage > unMaxPage-1)//容错处理
			{
				unPage = unMaxPage-1;
				unCount = 0;
			}
			else
				unCount = ((unMaxPage-1) > unPage)?MAX_TEM_PAGE_COUNT:(m_unFriendCount - unPage*MAX_TEM_PAGE_COUNT);
		}
		//unCount = m_unFriendCount;
		list = m_friendIDList + unPage*MAX_TEM_PAGE_COUNT;

		if (isAll)
			unCount = m_unInviteCount;

		m_unCount0 = unCount;
		m_unMaxPage0 = unMaxPage;
		m_unPage0 = unPage;
	}
	else
	{
		unMaxPage = (m_unInviteCount + MAX_TEM_PAGE_COUNT -1)/MAX_TEM_PAGE_COUNT;
		if (unMaxPage == 0)
		{
			unPage = 0;
			unCount = 0;
		}
		else
		{
			if (unPage > unMaxPage-1)//容错处理
			{
				unPage = unMaxPage-1;
				unCount = 0;
			}
			else
				unCount = ((unMaxPage-1) > unPage)?MAX_TEM_PAGE_COUNT:(m_unInviteCount - unPage*MAX_TEM_PAGE_COUNT);
		}

		//unCount = m_unInviteCount;
		list = m_inviteIDList + unPage*MAX_TEM_PAGE_COUNT;
		
		if (isAll)
			unCount = m_unInviteCount;

		m_unCount1 = unCount;
		m_unMaxPage1 = unMaxPage;
		m_unPage1 = unPage;
	}

	//send request

	//char send_buff[4096];

	MsgGetCharacterDetailRequest *msg = (MsgGetCharacterDetailRequest *)public_send_buff;
	msg->unType = unType;
	msg->unCount = unCount;
	ACE_OS::memcpy(msg->list, list, sizeof(ACE_UINT32) * unCount);

	int size = sizeof(MsgGetCharacterDetailRequest) + (unCount-1) * sizeof(ACE_UINT32);

	m_map->sendMsg(SERVICE_MESSAGE_TYPE_USER, MSG_GET_CHARACTER_DETAIL_REQUEST, (char *)msg, size, m_map->m_unUserInfoServerID, ADAPTER_USER_INFO_MGR, OBJ_ID_NONE);
}

void FriendMgr::get_list_detail(ACE_UINT32 unType, ACE_UINT32 unCount, CharacterInfoExt *list)
{
	if(m_requestInfoList[unType].unRequestCount > 0)
	{
		m_requestInfoList[unType].unRequestCount --;
	}

	ACE_UINT32 tmp_count;
	CharacterInfoExt *element;
	int size = 0;
	char *base_p = NULL;
	if(unType == CHARACTER_LIST_TYPE_FRIEND)
	{
		tmp_count = m_unFriendCount;
		size = sizeof(FriendInfo);
		base_p = (char *)m_friendList;
	}
	else
	{
		tmp_count = m_unInviteCount;
		size = sizeof(CharacterInfoExt);
		base_p = (char *)m_inviteList;
	}

	int i;
	int c = 0;
	for(i = 0;i < tmp_count;i ++)
	{
		element = (CharacterInfoExt *)(base_p + i * size);

		if(element->unItemID == list[c].unItemID)
		{
			copy_character_info(element, &list[c]);
			c ++;
		}
		else if(element->unItemID > list[c].unItemID)
		{
			i --;
			c ++;
		}

		if(c >= unCount)
		{
			break;
		}
	}

	if(m_requestInfoList[unType].unRequestCount == 0 && m_requestInfoList[unType].requestFlag)
	{
		m_requestInfoList[unType].requestFlag = false;
		//send detail info 2 client
		send_2_client(unType, m_requestInfoList[unType].unRequestSN);
	}
}


void FriendMgr::copy_character_info(CharacterInfoExt *dest, CharacterInfoExt *src)
{
	dest->unItemID = src->unItemID;
	dest->unLevel = src->unLevel;
	ACE_OS::memcpy(dest->name, src->name, MAX_CHARACTER_LENGTH + 1);
	ACE_OS::memcpy(&dest->pveTeam, &src->pveTeam, sizeof(PlayerTeamInfo));
	//ACE_OS::memcpy(&dest->pvpTeam, &src->pvpTeam, sizeof(PlayerTeamInfo));
	//ACE_OS::memcpy(dest->equipmentList, src->equipmentList, sizeof(PackageCell) * MAX_EQUIPMENT_COUNT);
	//ACE_OS::memcpy(dest->propertyList, src->propertyList, sizeof(PropertyComponent) * PROPERTY_ID_MAX);
	//dest->unSkillID = src->unSkillID;
	dest->unVipLevel = src->unVipLevel;
}

void FriendMgr::update_2_db(int type)
{
	int i;
	if(type == CHARACTER_LIST_TYPE_FRIEND)
	{
		MsgDBUpdateFriendListRequest db_request;

		db_request.unMaxFriendCount = m_unMaxFriendCount;

		for(i = 0;i < MAX_FRIEND_COUNT;i ++)
		{
			
			db_request.friendList[i].unCharacterID = m_friendList[i].unItemID;
			db_request.friendList[i].unCooldown = m_friendList[i].unCooldown;
			db_request.friendList[i].unStartTime = m_friendList[i].unStartTime;
			db_request.friendList[i].unLastInteractionTime = m_friendList[i].unLastInteractionTime;
			db_request.friendList[i].unInteractionFlag = m_friendList[i].unInteractionFlag;
			//db_request.friendList[i].unAddFriendshipFlag = m_friendList[i].unAddFriendshipFlag;
		}

		m_map->add_db_request(ADAPTER_DB_HOME_MGR, MSG_DB_UPDATE_FRIEND_LIST, (char *)&db_request, sizeof(MsgDBUpdateFriendListRequest));
	}
	else if (type == CHARACTER_LIST_TYPE_ASSIST)
	{
		MsgDBUpdateAssistListRequest db_request;
		db_request.unCount = m_assistMember.size();
		std::map<ACE_UINT32, BYTE>::iterator itMap;
		int i=0;
		for (itMap=m_assistMember.begin();itMap!=m_assistMember.end() && i<MAX_ASSIST_COUNT;++i, ++itMap)
		{
			db_request.assistList[i].unAssistPlayerID = itMap->first;
			db_request.assistList[i].unAssistType = itMap->second;
		}
		m_map->add_db_request(ADAPTER_DB_HOME_MGR, MSG_DB_UPDATE_ASSIST_LIST, (char *)&db_request, sizeof(MsgDBUpdateAssistListRequest));
	}
	else
	{
		MsgDBUpdateInviteListRequest db_request;

		for(i = 0;i < MAX_INVITE_COUNT;i ++)
		{
			db_request.inviteList[i] = m_inviteList[i].unItemID;
		}

		m_map->add_db_request(ADAPTER_DB_HOME_MGR, MSG_DB_UPDATE_INVITE_LIST, (char *)&db_request, sizeof(MsgDBUpdateInviteListRequest));
	}
}

void FriendMgr::update_friend_info(ACE_UINT32 unFriendID, CharacterInfoExt &info)
{
	int idx = GameUtils::find_element(m_unFriendCount, m_friendList, sizeof(FriendInfo), unFriendID);

	if(idx == -1)
	{
		return;
	}

	copy_character_info(&m_friendList[idx], &info);
}

int FriendMgr::can_use_friend(ACE_UINT32 unFriendID)
{
	int idx = GameUtils::find_element(m_unFriendCount, m_friendList, sizeof(FriendInfo), unFriendID);

	if(idx == -1)
	{
		m_unCurrentAssistFriendID = unFriendID;
		m_unCurrentAssistFriendship = GAME_CONFIG_INSTANCE::instance()->m_unAddFriendshipStranger;
		return -1;
	}

	FriendInfo *f = &m_friendList[idx];

	ACE_UINT32 t = m_map->m_unCurrentTime;

	ACE_UINT32 tmp = t - f->unStartTime;
	if(tmp < f->unCooldown)
	{
		return 1;
	}

	m_unCurrentAssistFriendID = unFriendID;
	m_unCurrentAssistFriendship = GAME_CONFIG_INSTANCE::instance()->m_unAddFriendshipStranger;
	memcpy(m_strAssistName, m_map->m_strName, MAX_CHARACTER_LENGTH+1);
	return 0;
}

int FriendMgr::use_friend(ACE_UINT32 unFriendID)
{
	int idx = GameUtils::find_element(m_unFriendCount, m_friendList, sizeof(FriendInfo), unFriendID);

	if(idx == -1)
	{
		
		return -1;
	}

	FriendInfo *f = &m_friendList[idx];

	ACE_UINT32 t = m_map->m_unCurrentTime;

	ACE_UINT32 tmp = t - f->unStartTime;
	if(tmp < f->unCooldown)
	{
		//m_unCurrentAssistFriendship = GAME_CONFIG_INSTANCE::instance()->m_unAddFriendship;
		return 1;
	}

	f->unStartTime = t;
	//f->unCooldown = 1800;

	int tmp_cd = 1800;

	int lv = (int)((int)f->unLevel - (int)m_map->m_unLevel);

	if(lv <= 0)
	{
		tmp_cd = 900;
	}
	else if(lv < 5)
	{
		tmp_cd = 1800;
	}
	else if(lv < 10)
	{
		tmp_cd = 3600;
	}
	else if(lv < 20)
	{
		tmp_cd = 43200;
	}
	else
	{
		tmp_cd = 86400;
	}

	f->unCooldown = tmp_cd;

	//update 2 db
	update_2_db(CHARACTER_LIST_TYPE_FRIEND);
	//m_unCurrentAssistFriendID = unFriendID;
	//m_unCurrentAssistFriendship = GAME_CONFIG_INSTANCE::instance()->m_unAddFriendship;


	return 0;
}

int FriendMgr::delete_friend(ACE_UINT32 unFriendID)
{
	if (m_deleteList.m_count >= MAX_FRIEND_DELETE_COUNT)
		return ERROR_MSG_FRIEND_DEL_MAX; 

	int ret = GameUtils::delete_element(m_unFriendCount, m_friendList, sizeof(FriendInfo), unFriendID);

	if(ret == 0)
	{
		//update 2 db
		update_2_db(CHARACTER_LIST_TYPE_FRIEND);

		update_id_list(CHARACTER_LIST_TYPE_FRIEND);

		m_deleteList.m_delete_list[m_deleteList.m_count] = unFriendID;
		m_deleteList.m_time = GameUtils::get_utc();
		m_deleteList.m_count++;
		update_delete_friend_list();
	}
	
	return ret;
}

int FriendMgr::add_friend(ACE_UINT32 unFriendID)
{
	if(unFriendID == m_map->m_unID)
	{
		return ERROR_MSG_PARAMETER;
	}

	if(m_unFriendCount >= m_unMaxFriendCount - m_unLockCount)
		return ERROR_MSG_FRIEND_FULL;

	//int ret = GameUtils::add_element(m_unFriendCount, m_friendList, m_unMaxFriendCount, sizeof(FriendInfo), unFriendID);
	int ret = GameUtils::add_element(m_unFriendCount, m_friendList, m_unMaxFriendCount - m_unLockCount /*+ m_unExtraLimit*/, sizeof(FriendInfo), unFriendID);

	if(ret >= 0)
	{
		//update 2 db
		update_2_db(CHARACTER_LIST_TYPE_FRIEND);

		update_id_list(CHARACTER_LIST_TYPE_FRIEND);

		//ACE_UINT32 tmp[1];
		//tmp[0] = unFriendID;
		//request_list_detail(CHARACTER_LIST_TYPE_FRIEND, 1, tmp);

		ret = 0;
	}
	else
	{
		ret = ERROR_MSG_FRIEND_HAVE;
	}


	return ret;
}

int FriendMgr::invite_friend_request(ACE_UINT32 unFriendID)
{
	if (unFriendID == m_map->m_unID)
	{
		return ERROR_MSG_PARAMETER;
	}
	int idx = GameUtils::find_element(m_unFriendCount, m_friendList, sizeof(FriendInfo), unFriendID);
	if(idx != -1)
	{
		return ERROR_MSG_FRIEND_HAVE;
	}


	//判断是否在好友邀请列表里面
// 	for (int i= 0;i<m_unInviteCount;i++)
// 	{
// 		if (m_inviteList[i].unItemID == unFriendID)
// 			return ERROR_MSG_FRIEND_HAVE;
// 	}
	//------------------------------end




	for(int i=0;i<m_deleteList.m_count && i<MAX_FRIEND_DELETE_COUNT;i++)
	{
		if (m_deleteList.m_delete_list[i] == unFriendID)//一天之内已经删除过
		{
			return ERROR_MSG_FRIEND_DEL;
		}
	}

// 	if (m_deleteList.m_count >= MAX_FRIEND_DELETE_COUNT)
// 	{
// 		return 
// 	}

	//send request
    //change by xxj 2015/06/14  21: 13:03 

	MsgInviteFriendRequest body;
	body.unSN = 0;
	body.unFriendID = unFriendID;
	m_map->sendMsg(SERVICE_MESSAGE_TYPE_USER, MSG_INVITE_FRIEND_REQUEST, (char *)&body, sizeof(MsgInviteFriendRequest), OBJ_ID_NONE, ADAPTER_MAP_MGR, unFriendID);

	return 0;
}

void FriendMgr::get_invite_request(ACE_UINT32 unFriendID)
{
	int idx = GameUtils::find_element(m_unFriendCount, m_friendList, sizeof(FriendInfo), unFriendID);
	if(idx != -1)
	{
		return;
	}

	if(GameUtils::add_element(m_unInviteCount, m_inviteList, MAX_INVITE_COUNT, sizeof(CharacterInfoExt), unFriendID) >= 0)
	{

		update_2_db(CHARACTER_LIST_TYPE_INVITE);

		update_id_list(CHARACTER_LIST_TYPE_INVITE);
		m_isHaveNew = true;
	}
}

int FriendMgr::apply_invite_request(ACE_UINT32 unFriendID, ACE_UINT32 unSN)
{
	//int ret = GameUtils::delete_element(m_unInviteCount, m_inviteList, sizeof(CharacterInfoExt), unFriendID);
	int ret = this->delete_invitation(unFriendID);
	
	if(ret == 0)
	{
		if(m_unFriendCount < (m_unMaxFriendCount - m_unLockCount /*+ m_unExtraLimit*/))
		{
			m_unLockCount ++;
			//get_invite_answer(unSN, unFriendID);
			//send msg 2 dest
			//change by xxj 2015/06/14  21: 22:09 
			MsgApplyInvitationRequest body;
			body.unSN = unSN;
			body.unFriendID = unFriendID;
			m_map->sendMsg(SERVICE_MESSAGE_TYPE_USER, MSG_APPLY_INVITATION_REQUEST, (char *)&body, sizeof(MsgApplyInvitationRequest), OBJ_ID_NONE, ADAPTER_MAP_MGR, unFriendID);
		}
		else
		{
			ret = ERROR_MSG_FRIEND_FULL1;
		}
	}

	if(ret != 0)
	{
		MsgApplyInvitationResponse response;
		response.nResult = -1;
		response.unSN = unSN;
		response.unFriendID = unFriendID;
		
		m_map->send_msg_2_client(SERVICE_MESSAGE_TYPE_USER, MSG_APPLY_INVITATION_RESPONSE, (char *)&response, sizeof(MsgApplyInvitationResponse));
		m_map->send_response_end(m_map->m_unUserID, unSN);
	}

	return ret;
}

int FriendMgr::apply_invite_response(int nResult, ACE_UINT32 unFriendID, ACE_UINT32 unSN)
{
	int ret = -1;
	if(m_unLockCount > 0)
	{
		m_unLockCount --;
	}
	if(nResult == 0)
	{
		ret = add_friend(unFriendID);
	}
	else
	{
		//delete_friend(unFriendID);
	}

	MsgApplyInvitationResponse response;
	response.nResult = nResult;
	response.unSN = unSN;
	response.unFriendID = unFriendID;

	m_map->send_msg_2_client(SERVICE_MESSAGE_TYPE_USER, MSG_APPLY_INVITATION_RESPONSE, (char *)&response, sizeof(MsgApplyInvitationResponse));

	m_map->send_response_end(m_map->m_unUserID, unSN);

	return ret;
}

int FriendMgr::get_invite_answer(ACE_UINT32 unSN, ACE_UINT32 unSrcID)
{
	int ret = add_friend(unSrcID);

	MsgApplyInvitationResponse response;
	response.nResult = ret;
	response.unSN = unSN;
	response.unFriendID = m_map->m_unID;

	m_map->sendMsg(SERVICE_MESSAGE_TYPE_USER, MSG_APPLY_INVITATION_RESPONSE, (char *)&response, sizeof(MsgApplyInvitationResponse), OBJ_ID_NONE, ADAPTER_MAP_MGR, unSrcID);

	return ret;
}

int FriendMgr::delete_invitation(ACE_UINT32 unFriendID)
{
	int ret = GameUtils::delete_element(m_unInviteCount, m_inviteList, sizeof(CharacterInfoExt), unFriendID);

	if(ret == 0)
	{
		update_2_db(CHARACTER_LIST_TYPE_INVITE);

		update_id_list(CHARACTER_LIST_TYPE_INVITE);
	}

	return ret;
}

int FriendMgr::expand_max_friend()
{
	if(m_unMaxFriendCount >= GAME_CONFIG_INSTANCE::instance()->m_friendExpandInfo.unMax)
	{
		return -1;
	}

	int t = (int)GAME_CONFIG_INSTANCE::instance()->m_friendExpandInfo.unGold;

	if(m_map->m_unMoney < t)
	{
		return -1;
	}

	m_map->set_basic_info(0, -t, 0, 0, 0,0,0);

	m_unMaxFriendCount = m_unMaxFriendCount + GAME_CONFIG_INSTANCE::instance()->m_friendExpandInfo.unCountPerTime;

	update_2_db(CHARACTER_LIST_TYPE_FRIEND);

	return 0;
}

void FriendMgr::handle_event(BaseEvent *e)
{
	m_unExtraLimit = m_map->m_benefitMgr.get_benefit(BENEFIT_TYPE_FRIEND_LIMIT, 0);
}

int FriendMgr::pvp_with_friend(ACE_UINT32 unFriendID, ACE_UINT32 unCurrentTime)
{
	int idx = GameUtils::find_element(m_unFriendCount, m_friendList, sizeof(FriendInfo), unFriendID);

	if(idx == -1)
	{
		return -1;
	}

	FriendInfo *info = &m_friendList[idx];

	int d = GameUtils::get_day_different(unCurrentTime, info->unLastInteractionTime);

	if(d > 0)
	{
		info->unInteractionFlag = 0;
	}

	if(info->unInteractionFlag != 0)
	{
		return -1;
	}

	info->unInteractionFlag = 1;
	info->unLastInteractionTime = unCurrentTime;

	update_2_db(CHARACTER_LIST_TYPE_FRIEND);

	return 0;
}

void FriendMgr::AssistFriendReset()
{
	m_assistMember.clear();
	update_2_db(CHARACTER_LIST_TYPE_ASSIST);
}

ACE_UINT32 FriendMgr::add_friendship(ACE_UINT32 unCharacterID)
{
	m_map->CheckDateChanged();
	int idx = GameUtils::find_element(m_unFriendCount, m_friendList, sizeof(FriendInfo), unCharacterID);

	std::map<ACE_UINT32, BYTE>::iterator itMap = m_assistMember.find(unCharacterID);
	ACE_UINT32 unAddFriendship = 0;

	if (itMap != m_assistMember.end())   //助战过
	{
		if (idx != -1 && itMap->second == 0)  //原来非好友时助战过，现在是好友了，同样加
		{
			unAddFriendship = GAME_CONFIG_INSTANCE::instance()->m_unAddFriendshipFriend;
			//itMap->second = 1;
			//m_map->send_friendship_mail(m_unCurrentAssistFriendID, GAME_CONFIG_INSTANCE::instance()->m_unAddFriendship * 2);
			//m_map->update_friendship_2_db();
			//update_2_db(CHARACTER_LIST_TYPE_ASSIST);
		}
	}
	else
	{
		if (idx != -1)
		{
			unAddFriendship = GAME_CONFIG_INSTANCE::instance()->m_unAddFriendshipFriend;
			//m_assistMember.insert(std::make_pair(m_unCurrentAssistFriendID, 1));
			//m_map->send_friendship_mail(m_unCurrentAssistFriendID, unAddFriendship);
		}
		else
		{
			unAddFriendship = GAME_CONFIG_INSTANCE::instance()->m_unAddFriendshipStranger;
			//m_assistMember.insert(std::make_pair(m_unCurrentAssistFriendID, 0));
		}
		//m_map->update_friendship_2_db();
		//update_2_db(CHARACTER_LIST_TYPE_ASSIST);
	}

	return unAddFriendship;
}


void FriendMgr::record_friendship()
{
	if (m_unCurrentAssistFriendID == 0)
	{
		return;
	}
	m_map->CheckDateChanged();
	int idx = GameUtils::find_element(m_unFriendCount, m_friendList, sizeof(FriendInfo), m_unCurrentAssistFriendID);

	std::map<ACE_UINT32, BYTE>::iterator itMap = m_assistMember.find(m_unCurrentAssistFriendID);

	if (itMap != m_assistMember.end())   //助战过
	{
		if (idx != -1 && itMap->second == 0)  //原来非好友时助战过，现在是好友了，同样加
		{
			m_unCurrentAssistFriendship = GAME_CONFIG_INSTANCE::instance()->m_unAddFriendshipFriend;
			itMap->second = 1;
			m_bSendAssistEmail = true;
			m_unAssistType = 2;
			//m_map->send_friendship_mail(m_unCurrentAssistFriendID, GAME_CONFIG_INSTANCE::instance()->m_unAddFriendship * 2);
			update_2_db(CHARACTER_LIST_TYPE_ASSIST);
		}
		else
			m_unCurrentAssistFriendship = 0;
	}
	else
	{
		if (idx != -1)
		{
			m_unCurrentAssistFriendship = GAME_CONFIG_INSTANCE::instance()->m_unAddFriendshipFriend;
			m_bSendAssistEmail = true;
			m_unAssistType = 2;
			m_assistMember.insert(std::make_pair(m_unCurrentAssistFriendID, 1));
			//m_map->send_friendship_mail(m_unCurrentAssistFriendID, unAddFriendship);
		}
		else
		{
			m_unCurrentAssistFriendship = GAME_CONFIG_INSTANCE::instance()->m_unAddFriendshipStranger;
			m_bSendAssistEmail = true;
			m_unAssistType = 1;
			m_assistMember.insert(std::make_pair(m_unCurrentAssistFriendID, 0));
		}
		update_2_db(CHARACTER_LIST_TYPE_ASSIST);
	}
}

void FriendMgr::update_FriendMax( ACE_UINT32 friendMax,bool is )
{
	m_unMaxFriendCount = friendMax;
	if (is)
		update_2_db(CHARACTER_LIST_TYPE_FRIEND);
}

void FriendMgr::DoDayChange()
{
	ACE_UINT32 unCurrentUTC = GameUtils::get_utc();
	int dwDayOffset = GameUtils::get_day_different(unCurrentUTC, m_deleteList.m_time);
	if ( dwDayOffset > 0)
	{
		ZeroVar(m_deleteList);
		m_deleteList.m_time = unCurrentUTC;
		update_delete_friend_list();
	}
}

void FriendMgr::update_delete_friend_list()
{
	
	m_map->add_db_request(ADAPTER_DB_HOME_MGR, MSG_DB_UPDATE_DELERE_FRIEND_LIST, (char *)&m_deleteList, sizeof(DeleteFriendList));
}
