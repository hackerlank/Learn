#pragma once
//处理玩家数据

#include "DBHandler.h"
#include "..\GameBase\Protocol\DBProtocol.h"
#include "..\GameBase\Protocol\ControlProtocol.h"

extern CooldownInstanceInfo initCooldownList[MAX_COOLDOWN_INFO];

class DBUserHandler : public DBHandler
{
public:
	ACE_Recursive_Thread_Mutex m_mutex;

	DBUserHandler(ACE_UINT32 unID, BaseAdapter *parent);

	virtual void do_db_load(Connection *db_conn);
	virtual void do_db_request(Connection *db_conn, MessageInfo &msgInfo);
	virtual void update_cache(MessageInfo &msgInfo);
	void SendAdminLogItem(const MsgDBAdminLogInfoResponse & response,const ObjAdr & _srcAdr);//log日志请求结果返回
	
	//static void init_weapon_skill_list();
	//static void init_cooldown_list();
private:
	void deal_admin_op(Connection *db_conn, MsgAdminOPRequest *request, ObjAdr &targetAdr);
	void load_character_id(Connection *db_conn);
	int create_character(Connection *db_conn, ACE_UINT32 unID, char *name, ACE_UINT32 unPlayerID);

	static void init_map_flag_list();
	static void init_skill_list();
	static void init_function_list();
	
	void send_character_list(ObjAdr &adr);

	int load_basic_info(Connection *db_conn, int type, const std::string& rstrName, AccountBasicInfos& roAccountBasicInfo);
	int load_basic_info(Connection *db_conn, int dwCharchterID, AccountBasicInfos& roAccountBasicInfo);
	int load_account_list(Connection *db_conn, int type, const std::string& rstrName, AccountBriefInfoList& roAccountList);
	int load_items_list(Connection *db_conn, int dwCharchterID, AccountItemInfos& roAccountItemInfos);
	int load_player_list(Connection *db_conn, int dwCharchterID, AccountPlayerInfos& roAccountPlayerInfos);
	int load_Point_info(Connection *db_conn, int dwCharchterID, AccountBasicInfos& roAccountPlayerInfos);//xxj 2015/04/23 17:14:08 加载战力
	int load_Skill_list(Connection *db_conn, int dwCharchterID, AccountBasicInfos& roAccountPlayerInfos);//xxj 2015/04/23 19:35:58  加载技能 
	int Recharge_request(Connection *db_conn, const MsgDBAdminRechargeRequest * request,MsgDBAdminRechargeResponse & response);//添加充值消息
	int GetOrderInfo(Connection *db_conn, OrderInfo & info);//获取order信息
	bool DoRechargeAction(Connection *db_conn,const OrderInfo & info,ACE_UINT32 type,Bitfield & bitfield);//充值结束后消息
	
	bool GetBitfield(Connection *db_conn,ACE_UINT32 unCharacterID,Bitfield & bitfield);//获取位域
	bool UpdateBitfield(Connection *db_conn,ACE_UINT32 unCharacterID,const Bitfield & bitfield);//更新位域
	bool DoRechargeMail(Connection *db_conn,const OrderInfo & info,Bitfield & bitfield);//首充邮件
	bool GetMailInfo(MailInfo & oMailInfo,ACE_UINT32 unCharacterID,ACE_UINT32 unid);
	bool GetMailInfo(MailInfo & oMailInfo,ConfigReward & reward,ACE_UINT32 unCharacterID,ACE_UINT32 unMailId);
	bool DoCheckMonthCard(Connection *db_conn,const OrderInfo & info);//充值月卡
	bool DoUpdateMonthCard(Connection *db_conn,ACE_UINT32 unCharacterID,ACE_UINT32 time = 0);//充值月卡
	void send_month_card(ACE_UINT32 unCharacterID);

	void send_account_info(MsgDBAccountInfoResponse &info, ObjAdr &desAdr);
	void update_basic_info(Connection *db_conn, AccountBasicInfos &info);
	void update_character_flag(Connection *db_conn, MsgDBUpdateCharacterFlagRequest *info,ACE_UINT32 unID);//更新用户标记

	ACE_UINT32 GetUserID(Connection *db_conn,ACE_UINT32 characterID);
private:
	void build_property(PlayerTeamInfo * pteamInfo);
	void add_player_property(PropertyComponent *componentList, PlayerInfo *player);
	void add_equipment_property(PropertyComponent *componentList, ItemInfo *equipment);

	CharacterInfo m_CharacterList[MAX_PLAYER_PER_ACCOUNT];
public:
	static ACE_UINT32 m_unUserInfoServerID;
	static void SendLogInfoItemMSG(LogItemInfo & ver,ACE_UINT32 unUserID,DBHandler * handle);//日志系统发送一条日志信息

	bool m_bDirty;
};