#pragma once

#include "..\GameBase\Obj\ClientObj.h"
#include "..\GameBase\Protocol\ControlProtocol.h"
#include <map>

class GatewaySession : public ClientObj
{
public:
	enum
	{
		GATEWAY_STEP_NORMAL = 0,
		GATEWAY_STEP_QUERY,
		GATEWAY_STEP_WAIT_SELECT,
		GATEWAY_STEP_CREATE
	};

	GatewaySession(ACE_UINT32 unID, BaseAdapter *parent);
	virtual ~GatewaySession();

	virtual int deal_client_msg(MessageInfo &msgInfo);
	virtual int deal_other_msg(MessageInfo &msgInfo);

	virtual void create_done();
	virtual int start_destroy();

	virtual void obj_timeout();

	virtual int deal_db_msg(ACE_UINT32 unType, void *msg);

	virtual int parse_into_intranet_msg(MessageInfo &msgInfo,char *buff, int size);
	virtual ACE_Message_Block *parse_into_internet_msg(MessageInfo &msgInfo);

	ACE_UINT32 get_current_id() const {return m_unCurrentCharacterID;}

	std::map<ACE_UINT32, CommunicationRecord> m_oCommunicationRecord;
private:
	char m_strSession[CLIENT_SESSION_LEN + 1];

	//ACE_UINT32 m_unCharacterID;
	//ACE_UINT32 m_unLevel;

	void send_character_query_response();
	void send_response_end(int ret);

	void set_character_create_done(ACE_UINT32 unCharacterID, char *name);

	void send_select_msg(ACE_UINT32 unCharacterID);

	bool write_package_cell(PackageCell *cell);
	bool write_reward(RewardInfo &reward);
	bool write_character_info(CharacterInfoExt *info);
	bool write_mail_info(MailInfo *info);
	bool write_mail_attachment(MailAttachment* info);
	bool write_friend_info(FriendInfo *info);
	bool write_map_instance_info(MapInstanceInfo *info);
	//bool write_battle_info(MapBattleInfo *info);
	bool write_item_info(ItemInfo *itemInfo);
	bool write_player_info(PlayerInfo *player);
	bool write_team_info(PlayerTeamInfo *teamInfo);
	bool write_pvp_basic_info(PVPBasicInfo *basicInfo);
	bool write_pvp_rank_info(PVPRankInfo *rankInfo);
	bool write_pvp_team_info(PVPTeamInfo *teamInfo);
	bool Write_pvp_FightRecordInfo(FightRecordInfo & info);
	bool Write_badge_info(BadgeShuxingS & bsInfos);

	ACE_UINT32 m_unCurrentRequestSN;

	ACE_UINT32 m_unCurrentCharacterID;

	CharacterInfo m_CharacterList[MAX_PLAYER_PER_ACCOUNT];

	static ACE_UINT32 m_unGameServerID;
	static ACE_UINT32 m_unUserInfoServerID;
	ACE_UINT32 m_unActiveTimer;
	bool m_isDestroyMsg;

	ACE_UINT32 m_unLoginID;

	ACE_UINT32 m_unGatewayStep;

	bool Read_BS_info(BadgeShuxing & info);
};