#pragma once

#include "ace\ace.h"
#include "BaseModule.h"
#include "..\..\Base\Event\EventListener.h"
#include <map>

enum
{
	CHARACTER_LIST_TYPE_FRIEND = 0,
	CHARACTER_LIST_TYPE_INVITE,
	CHARACTER_LIST_TYPE_ASSIST,
	CHARACTER_LIST_TYPE_MAX
};

typedef struct tagCharacterDetailRequestInfo
{
	ACE_UINT32 unRequestCount;
	bool requestFlag;
	ACE_UINT32 unRequestSN;
}CharacterDetailRequestInfo;

class FriendMgr : public BaseModule, public EventListener
{
public:
	FriendMgr();
	~FriendMgr();

	void init(ACE_UINT32 unMaxFriendCount, ACE_UINT32 *inviteList, DBFriendInfo *friendList,BadgeShuxingS * bs_list, AssistInfo *assistList,DeleteFriendList & deletelist);

	void request_detail(ACE_UINT32 unType, ACE_UINT32 unSN,ACE_INT32 unPage);

	void request_list_detail(ACE_UINT32 unType,ACE_INT32 unPage);
	void get_list_detail(ACE_UINT32 unType, ACE_UINT32 unCount, CharacterInfoExt *list);

	int can_use_friend(ACE_UINT32 unFriendID);
	int use_friend(ACE_UINT32 unFriendID);
	int add_friend(ACE_UINT32 unFriendID);
	int delete_friend_or_invitation(ACE_UINT32 unType, ACE_UINT32 unFriendID, ACE_UINT32 unSN);
	int delete_friend(ACE_UINT32 unFriendID);
	void update_friend_info(ACE_UINT32 unFriendID, CharacterInfoExt &info);

	int delete_invitation(ACE_UINT32 unFriendID);
	int invite_friend_request(ACE_UINT32 unFriendID);
	void get_invite_request(ACE_UINT32 unFriendID);
	int apply_invite_request(ACE_UINT32 unFriendID, ACE_UINT32 unSN);//Õ¨“‚—˚«Î
	int apply_invite_response(int nResult, ACE_UINT32 unFriendID, ACE_UINT32 unSN);
	int get_invite_answer(ACE_UINT32 unSN, ACE_UINT32 unSrcID);

	void clear_invite();  //copied by jinpan frome mapServer\FriendMgr.h

	int pvp_with_friend(ACE_UINT32 unFriendID, ACE_UINT32 unCurrentTime);

	ACE_UINT32 add_friendship(ACE_UINT32 unCharacterID);
	void record_friendship();

	virtual void handle_event(BaseEvent *e);

	int expand_max_friend();
	void AssistFriendReset();
	void update_FriendMax(ACE_UINT32 friendMax,bool is);

	ACE_UINT32 m_unMaxFriendCount;

	ACE_UINT32 m_unExtraLimit;

	ACE_UINT32 m_unInviteCount;
	CharacterInfoExt m_inviteList[MAX_INVITE_COUNT];
	ACE_UINT32 m_inviteIDList[MAX_INVITE_COUNT];

	ACE_UINT32 m_unFriendCount;
	FriendInfo m_friendList[MAX_FRIEND_COUNT];
	ACE_UINT32 m_friendIDList[MAX_FRIEND_COUNT];
	std::map<ACE_UINT32, BYTE> m_assistMember;
	ACE_UINT32 m_unCurrentAssistFriendship;
	ACE_UINT32 m_unCurrentAssistFriendID;
	ACE_UINT32 m_unAssistType;
	char m_strAssistName[MAX_CHARACTER_LENGTH +1];
	bool m_bSendAssistEmail;

	ACE_UINT32 m_unCount0;
	ACE_UINT32 m_unMaxPage0;
	ACE_UINT32 m_unPage0;

	ACE_UINT32 m_unCount1;
	ACE_UINT32 m_unMaxPage1;
	ACE_UINT32 m_unPage1;
	
	DeleteFriendList m_deleteList;
	void DoDayChange();
	bool m_isHaveNew;
private:
	//ACE_UINT32 m_unDetailInitStep;
	ACE_UINT32 m_unLockCount;

	CharacterDetailRequestInfo m_requestInfoList[CHARACTER_LIST_TYPE_MAX];

	void update_2_db(int type);
	void update_delete_friend_list();
	void send_2_client(ACE_UINT32 unType, ACE_UINT32 unSN);
	void update_id_list(ACE_UINT32 unType);

	static void copy_character_info(CharacterInfoExt *dest, CharacterInfoExt *src);
};