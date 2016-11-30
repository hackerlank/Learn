#pragma once

#include "DBHandler.h"

#include "ace\Hash_Map_Manager.h"
#include "ace\Null_Mutex.h"

#include "..\GameBase\Common\GameDefine.h"

#include "..\GameBase\Protocol\DBProtocol.h"
#include "..\GameBase\Common\IDMap.h"
#include "..\GameBase\Protocol\ControlProtocol.h"
#include <vector>

/*
typedef ACE_Hash_Map_Manager_Ex<ACE_UINT32, HomeItemInfo *, ACE_Hash<ACE_UINT32>, 
ACE_Equal_To<ACE_UINT32>, ACE_Null_Mutex> HOME_ITEM_MAP;
typedef HOME_ITEM_MAP::ITERATOR HOME_ITEM_MAP_ITERATOR;

typedef ACE_Hash_Map_Manager_Ex<ACE_UINT32, QuestInfo *, ACE_Hash<ACE_UINT32>, 
ACE_Equal_To<ACE_UINT32>, ACE_Null_Mutex> HOME_QUEST_MAP;
typedef HOME_QUEST_MAP::ITERATOR HOME_QUEST_MAP_ITERATOR;

typedef ACE_Hash_Map_Manager_Ex<ACE_UINT32, AchievementInfo *, ACE_Hash<ACE_UINT32>, 
ACE_Equal_To<ACE_UINT32>, ACE_Null_Mutex> HOME_ACHIEVEMENT_MAP;
typedef HOME_ACHIEVEMENT_MAP::ITERATOR HOME_ACHIEVEMENT_MAP_ITERATOR;
*/

//一个用户的基本信息

class DBHomeHandler : public DBHandler
{
public:
	ACE_Recursive_Thread_Mutex m_mutex;
	DBHomeHandler(ACE_UINT32 unID, BaseAdapter *parent);

	virtual void do_db_load(Connection *db_conn);
	virtual void do_db_request(Connection *db_conn, MessageInfo &msgInfo);
	virtual void update_cache(MessageInfo &msgInfo);

private:
	ACE_UINT32 m_unUserID;
	char m_name[MAX_CHARACTER_LENGTH + 1];
	ACE_UINT32 m_unLevel;
	ACE_UINT32 m_unExp;//经验值
	ACE_UINT32 m_unCoin;
	ACE_UINT32 m_unMoney;
	ACE_UINT32 m_unPowerPoint;
	ACE_UINT32 m_unHonour;
	ACE_UINT32 m_unLastLoginTime;
	ACE_UINT32 m_unLoginBonusCount;
	ACE_UINT32 m_unLoginCount;
	ACE_UINT32 m_unEnergy;
	ACE_UINT32 m_unEnergyRestoreTime;
// 	ACE_UINT32 m_unPVPEnergy;
// 	ACE_UINT32 m_unPVPEnergyRestoreTime;
	ACE_UINT32 m_unChannel;//渠道
	ACE_UINT32 m_unCurrentBuyEnergy;
	//ACE_UINT32 m_unBuyEnergyTime;
	//ACE_UINT32 m_unBuyEnergyCount;

	ACE_UINT32 m_unPackageMax;

	//ACE_UINT32 m_unPlayerCount;
	//ACE_UINT32 m_unMaxPlayerSelected;
	ACE_UINT32 m_unRechargeCount;
	ACE_UINT32 m_unRechargeAmount;
	ItemInfo m_staff;
	ACE_UINT32 m_selectedPlayerList[MAX_PLAYER_SELECTED_COUNT];
	PlayerInfo m_playerList[MAX_PLAYER_COUNT];
	ACE_UINT32 m_selectedPlayerSkillList[MAX_PLAYER_SELECTED_COUNT];
	//PackageCell m_equipmentList[MAX_EQUIPMENT_COUNT];
	ACE_UINT32 m_unItemsCount;
	PackageCell m_itemsList[MAX_ITEMS_COUNT];

	MapInstanceInfo m_mapInstanceInfo;
	RewardInfo m_mapReward;
	MapFlagInfo m_mapFlagList[MAX_MAP_COUNT];
	ACE_UINT32 m_unMapLastRewardTime;
	ACE_UINT32 m_unFreeRebornCount;
	ACE_UINT32 m_unLastRebornTime;
	MapFlagInfo m_mapGiftList[MAX_MAP_COUNT];
	//MapBattleInfo m_battleInfo;
	//BattleSnapInfo m_battleSnapInfo;

	GiftInfo m_giftList[MAX_GIFT_COUNT];

	ACE_UINT32 m_skillList[MAX_SKILL_COUNT];
	ACE_UINT32 m_playerSkillList[MAX_PLAYER_SKILL_COUNT];
	SkillBook m_bookRes[MAX_PLAYER_SKILL_COUNT];

	ACE_UINT32 m_unHighestPoint;

	ACE_UINT32 m_unTutorialFlag;
	ACE_UINT32 m_unUseLuckCount;
	ACE_UINT32 m_dwFlag;
	ACE_UINT32 m_dwBuyMonthCardTime;
	//vip 充值
	VipInfo m_vipInfo;
	VipGift m_vipGift;
	Bitfield m_bitField;
	ProductList m_Productlist;
	ACE_UINT32 m_monthTime;

	ACE_UINT32 m_unMaxFriendCount;
	ACE_UINT32 m_inviteList[MAX_INVITE_COUNT];
	DBFriendInfo m_friendList[MAX_FRIEND_COUNT];
	BadgeShuxingS m_bs[MAX_FRIEND_COUNT];

	DeleteFriendList m_deleteFriendList;

	ACE_UINT32 m_unAssistCount;
	AssistInfo m_assistList[MAX_ASSIST_COUNT];

	ACE_UINT32 m_LockedFunctionList[MAX_FUNCTION_COUNT];

	//WeaponSkillInfo m_weaponSkillList[MAX_WEAPON_SKILL_COUNT];

	//PropertyComponent m_improvePropertyList[PROPERTY_ID_MAX];

	CooldownInstanceInfo m_cooldownList[MAX_COOLDOWN_INFO];

	ACE_UINT32 m_unHandbookCount;
	BaseItemInfo m_handbookList[MAX_HANDBOOK_COUNT];

	ACE_UINT32 m_unMaterialCount;
	MaterialInfo m_materialList[MAX_MATERIAL_COUNT];

	std::vector<PropsInfo> m_propsList;

	PVPOpponentInfo m_pvpOpponent;
	PVPBasicInfo m_pvpBasicInfo;
	DBPVPRankInfo m_pvpRankInfo;

	ACE_UINT32 m_unMoneyTreeLevel;
	ACE_UINT32 m_unMoneyTreeExp;

	SecretInfo m_secretMgr; //added by jinpan for secret 
	WingInfo m_wingInfo;

	ACE_UINT32 m_unGiftBagCodeCount;
	WORD m_giftBagCodeSet[MAX_GIFT_BAG_CODE_COUNT];

	ACE_UINT32 m_unDoubleDropVersion;
	ACE_UINT32 m_unUsedDoubleDropCount;
	ACE_UINT32 m_usedDoubleDropList[MAX_DOUBLE_DROP_COUNT];

	ACE_UINT32 m_unChangedDate;
	ACE_UINT32 m_unTaskCount;
	TaskInfo m_taskList[MAX_TOTAL_TASK_COUNT];

	TaskInfo m_taskProgressList[MAX_TOTAL_TASK_COUNT];
	MsgDBLimitedActivityList m_LAlist;//任务列表

	ACE_UINT32 m_unObtainedActivenessRewardCount;
	ACE_UINT32 m_ObtainedActivenessRewardList[MAX_ACTIVENESS_COUNT];
	ACE_UINT32 m_unFriendship;
	ACE_UINT32 m_unUsedGoldenTouchCount;
	ACE_UINT32 m_unDynamicEnergy;//动感能量
	ACE_UINT32 m_unPower;//战斗力//

	std::map<ACE_UINT32, BadgeInfo> m_mapBadge;//当前徽章列表

	//add by xxj 2015/08/18  16:00:44 
	//pvp相关
	PVPInfo m_pvpInfo;//pvp 信息

	//----------------------------------------end

private:

	int load_basic_info(Connection *db_conn);
	int load_items_list(Connection *db_conn);
	int load_map_list(Connection *db_conn);
	int load_skill_list(Connection *db_conn);
	//int load_weapon_skill_list(Connection *db_conn);
	int load_friend_list(Connection *db_conn);
	int load_function_list(Connection *db_conn);
	int load_gift_list(Connection *db_conn);
	int load_player_list(Connection *db_conn);
	int load_cooldown_list(Connection *db_conn);
	int load_handbook_list(Connection *db_conn);
	int load_materail_list(Connection *db_conn);
	int load_props_list(Connection *db_conn);
	int load_pvp_info(Connection *db_conn);
	int load_money_tree_info(Connection *db_conn);
	int load_secret_list(Connection *db_conn);//added by jinpan for secret
	int load_wing_list(Connection *db_conn);	//add by wangwei 翅膀
	int load_task_list(Connection *db_conn);
	int load_obtained_activeness_reward(Connection *db_conn);
	int load_task_progress(Connection *db_conn);
	int load_limited_activity_progress(Connection *db_conn);//从数据库中加载限时活动进度
	int Delete_limited_activity_progress(Connection *db_conn);//删除限时活动进度
	int Load_ProductList(Connection *db_conn);//加载已领列表
	int Load_monthCardTime(Connection *db_conn);//月卡
	int Load_Badge(Connection * db_conn);//徽章
	//int load_globle_gift_bag_code(Connection *db_conn);

	void send_basic_info(ObjAdr &desAdr);
	void send_player_list(ObjAdr &desAdr);
	//void send_equipment_list(ObjAdr &desAdr);
	void send_items_list(ObjAdr &desAdr);
	void send_map_list(ObjAdr &desAdr);
	void send_skill_list(ObjAdr &desAdr);
	//void send_weapon_skill_list(ObjAdr &desAdr);
	void send_friend_list(ObjAdr &desAdr);
	void send_function_list(ObjAdr &desAdr);
	void send_gift_list(ObjAdr &desAdr);
	void send_cooldown_list(ObjAdr &desAdr);
	void send_handbook_list(ObjAdr &desAdr);
	void send_material_list(ObjAdr &desAdr);
	void send_props_list(ObjAdr &desAdr);
	void send_pvp_info(ObjAdr &desAdr);
	void send_money_tree_info(ObjAdr &desAdr);
	void send_secret_list(ObjAdr &desAdr);  //added by jinpan
	void send_wing_list(ObjAdr &desAdr);
	void send_gift_bag_code(ObjAdr &desAdr);
	void send_double_drop(ObjAdr &desAdr);
	void send_task_list(ObjAdr &desAdr);
	void send_obtained_activeness_reward(ObjAdr &desAdr);
	void send_task_progress(ObjAdr &desAdr);
	void send_limited_activity_progress(ObjAdr &desAdr);//发送活动任务进度
	void send_badge_progress(ObjAdr &desAdr);//发送徽章
	//void send_globle_gift_bag_code(ObjAdr &desAdr);

	void update_basic_info(Connection *db_conn, MsgDBUpdateBasicInfoRequest *info);
	void update_character_flag(Connection *db_conn, MsgDBUpdateCharacterFlagRequest *info);
	void update_current_map(Connection *db_conn, MsgDBUpdateCurrentMapRequest *info);
	void update_map_flag_list(Connection *db_conn, MsgDBUpdateMapFlagListRequest *info);
	void update_double_drop(Connection *db_conn, MsgDBUpdateDoubleDropInfoRequest *info);
	void update_task_list(Connection *db_conn, MsgDBUpdateTaskInfoRequest *info);
	void insert_task_list(Connection *db_conn, MsgDBUpdateTaskInfoRequest *info);
	void delete_task(Connection *db_conn, MsgDBDeleteTaskInfoRequest *info);
	void update_task_progress(Connection *db_conn, MsgDBTaskList *info);//更新任务进度
	void update_golden_touch(Connection *db_conn, MsgDBUpdateGoldenTouchRequest *info);
	void update_Buy_energy(Connection *db_conn, MsgDBUpdateBuyEnergyRequest *info);
	void update_changed_date(Connection *db_conn, MsgDBUpdateChangedDate *info);
	void insert_obtained_activeness_reward(Connection *db_conn, MsgDBInsertObtainedActivenessRewardRequest *info);
	void update_player_list(Connection *db_conn, MsgDBUpdatePlayerListRequest *info);
	//void update_equipment_list(Connection *db_conn, MsgDBUpdateEquipmentListRequest *info);
	void update_package_cell(Connection *db_conn, MsgDBUpdatePackageCellRequest *info);
	void add_package_cell(Connection *db_conn, MsgDBAddPackageCellRequest *info);//添加一个装备
	void update_energy_info(Connection *db_conn, MsgDBUpdateEnergyRequest *info);
	void update_skill_list(Connection *db_conn, MsgDBUpdateSkillListRequest *info);
	//void update_weapon_skill_list(Connection *db_conn, MsgDBUpdateWeaponSkillListRequest *info);
	void update_friend_list(Connection *db_conn, MsgDBUpdateFriendListRequest *info);
	void update_invite_list(Connection *db_conn, MsgDBUpdateInviteListRequest *info);
	void update_assist_list(Connection *db_conn, MsgDBUpdateAssistListRequest *info);
	void update_friend_delete_list(Connection *db_conn, DeleteFriendList *info);
	//void update_property_list(Connection *db_conn, MsgDBPropertyUpdateRequest *info);
	void update_vip_level(Connection *db_conn, MsgDBVipLevelUpdateRequest *info);
	void delete_last_item(Connection *db_conn, MsgDBDeleteLastItemRequest *info);
	void update_name(Connection *db_conn, MsgDBUpdateNameRequest *info, ObjAdr &desAdr);
	void update_login_info(Connection *db_conn, MsgDBUpdateLoginInfoRequest *info);
	void update_function_list(Connection *db_conn, MsgDBUpdateFunctionListRequest *info);
	void update_recharge_info(Connection *db_conn, MsgDBUpdateRechargeInfoRequest *info);
	void update_package_max(Connection *db_conn, MsgDBUpdatePackageMaxRequest *info);
	void update_reborn_info(Connection *db_conn, MsgDBUpdateRebornInfoRequest *info);
	//void update_battle_info(Connection *db_conn, MsgDBUpdateBattleInfoRequest *info);
	void update_gift_list(Connection *db_conn, MsgDBUpdateGiftListRequest *info);
	void update_tutorial_flag(Connection *db_conn, MsgDBUpdateTutorialFlagRequest *info);
	void update_use_luck_count(Connection *db_conn, MsgDBUpdateUseLuckCountRequest *info);
	//void update_improve_property(Connection *db_conn, MsgDBUpdateImprovePropertyRequest *info);
	void update_cooldown_list(Connection *db_conn, MsgDBUpdateCooldownListRequest *info);
	void insert_cooldown_list(Connection *db_conn, CooldownInstanceInfo *list);
	void insert_new_table(Connection *db_conn);
	void update_handbook_list(Connection *db_conn, MsgDBUpdateHandbookListRequest *info);
	void update_material_list(Connection *db_conn, MsgDBUpdateMaterialListRequest *info);
	void update_props_list(Connection *db_conn, MsgDBUpdatePropsListRequest *info);
	void update_character_snap_info(Connection *db_conn, MsgDBUpdateCharacterSnapInfoRequest *info);
	void update_friendship(Connection *db_conn, MsgDBUpdateFriendshipRequest *info);
	void update_pvp_info(Connection *db_conn, MsgDBUpdatePVPInfoResquest *info);
	void update_money_tree(Connection *db_conn, MsgDBUpdateMoneyTreeInfoRequest *info);
	void update_highest_team_info(Connection *db_conn, MsgDBUpdateHighestTeamInfoRequest *info);
	void update_secret_list(Connection *db_conn, MsgDBUpdateSecretListRequest *info);
	void update_wing_list(Connection *db_conn, MsgDBUpdateWingListRequest *info);
	void update_player_gift_bag_code(Connection *db_conn, MsgDBUpdatePlayerGiftBagCodeRequest *info);
	//void update_globle_gift_bag_code(Connection *db_conn, MsgDBUpdateGlobleGiftBagCodeRequest *info);
	void deal_admin_op( Connection *db_conn, MsgAdminOPRequest *request, ObjAdr &targetAdr );
	void Deal_recharge_op_result(Connection *db_conn, OrderInfo *request);

	void deal_admin_buffer_op(MsgAdminOPBufferRequest *pRequest, ObjAdr &strAdr);
	int load_Channel_info(Connection *db_conn);//xxj 2015/04/26 19:20:52 得到渠道id
	void update_LA_progress(Connection *db_conn, MsgDBLimitedActivityList *info);//更新任务进度
	void update_LA_progress(Connection *db_conn, LimitedActivityInfo *info);//更新任务进度
	void CreatOneOrder(Connection *db_conn,MsgDBOrderRequest * request);//创建一个订单
	void GetNewOrderID(char * orderid);
	void update_Vip_Gift_info(Connection *db_conn, MsgDBVipGiftInfo *info);
	void update_Badge_progress(Connection *db_conn, BadgeInfo *info);//更新任务进度

	void Get_BS_info( Connection *db_conn,BadgeShuxingS& infos,ACE_UINT32 unCharacterID);//得到徽章属性

	bool m_bValidID;
};