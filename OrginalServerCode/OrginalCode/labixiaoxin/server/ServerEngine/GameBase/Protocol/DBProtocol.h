#pragma once

#include "..\..\Base\Protocol\Protocol.h"
#include "..\Common\GameDefine.h"
#include "..\..\DB Server\LogDefine.h"
#include "ControlProtocol.h"

#define DB_PROTOCOL_GROUP 0x0004

#define MSG_DB_VERIFY_ACCOUNT						MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x0001) //注册

typedef struct tagMsgVerifyAccountRequest
{
	char mac[MAX_MAC_LENGTH + 1];
	char email[MAX_EMAIL_LENGTH + 1];
	ACE_UINT32 unUserID;
}MsgVerifyAccountRequest;

typedef struct tagMsgVerifyAccountResponse : public MsgDBBaseResponse
{
	ACE_UINT32 unUserID;
}MsgVerifyAccountResponse;

#define MSG_DB_QUERY_CHARACTER_INFO					MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x0002)

typedef struct tagMsgDBQueryCharacterInfoRequest
{

}MsgDBQueryCharacterInfoRequest;

typedef struct tagMsgDBQueryCharacterInfoResponse : public MsgDBBaseResponse
{
	CharacterInfo list[MAX_PLAYER_PER_ACCOUNT];
}MsgDBQueryCharacterInfoResponse;

#define MSG_DB_CREATE_CHARACTER						MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x0003)

typedef struct tagMsgDBCreateCharacterRequest
{
	ACE_UINT32 unCharacterID;
	char name[MAX_CHARACTER_LENGTH + 1];
	ACE_UINT32 unPlayerID;
}MsgDBCreateCharacterRequest;

typedef struct tagMsgDBCreateCharacterResponse : public MsgDBBaseResponse
{
	ACE_UINT32 unCharacterID;
	char name[MAX_CHARACTER_LENGTH + 1];
}MsgDBCreateCharacterResponse;

#define MSG_DB_LOAD_CHARACTER_INFO					MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x0004)

typedef struct tagMsgDBLoadCharacterInfoRequest
{
	
}MsgDBLoadCharacterInfoRequest;

#define MSG_DB_CHARACTER_BASIC						MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x0004)//基础信息

typedef struct tagMsgDBCharacterBasicResponse : public MsgDBBaseResponse
{
	ACE_UINT32 unUserID;
	char name[MAX_CHARACTER_LENGTH + 1];
	ACE_UINT32 unLevel;
	ACE_UINT32 unExp;
	ACE_UINT32 unCoin;
	ACE_UINT32 unMoney;
	ACE_UINT32 unPowerPoint;
	ACE_UINT32 unHonour;
	ACE_UINT32 unLastLoginTime;
	ACE_UINT32 unLoginBonusCount;
	ACE_UINT32 unLoginCount;
	ACE_UINT32 unEnergy;
	ACE_UINT32 unEnergyRestoreTime;
// 	ACE_UINT32 unPVPEnergy;
// 	ACE_UINT32 unPVPEnergyRestoreTime;
	ACE_UINT32 unRechargeCount;
	ACE_UINT32 unRechargeAmount;
	ACE_UINT32 unPackageMax;
	ACE_UINT32 unTutorialFlag;
	ACE_UINT32 unUseLuckCount;
	ACE_UINT32 unFlag;
	ACE_UINT32 unGoldenTouchUsedTimes;
	ACE_UINT32 unBuyMonthCardTime;
	ACE_UINT32 unChangedDate;
	ACE_UINT32 unFriendship;
	ACE_UINT32 unDynamicEnergy;//动感能量
	ACE_UINT32 m_unChannel;//渠道
	ACE_INT32 m_unCurrentBuyEnergy;
	VipInfo m_vipInfo;
	VipGift m_vipGift;
	Bitfield m_bitField;
	ProductList m_Productlist;
	ACE_UINT32 m_monthTime;//月卡时间
	ACE_UINT32 m_power;

}MsgDBCharacterBasicResponse;

#define MSG_DB_PLAYER_LIST							MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x0005)

typedef struct tagMsgDBPlayerListResponse : public MsgDBBaseResponse
{
	//ACE_UINT32 unMaxSelected;
	ItemInfo staff;
	ACE_UINT32 selectedList[MAX_PLAYER_SELECTED_COUNT];
	PlayerInfo playerList[MAX_PLAYER_COUNT];
	ACE_UINT32 playerSkillList[MAX_PLAYER_SELECTED_COUNT];
	ACE_UINT32 unHighestPoint;
}MsgDBPlayerListResponse;

/*
#define MSG_DB_EQUIPMENT_LIST						MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x0006)

typedef struct tagMsgDBEquipmentListResponse : public MsgDBBaseResponse
{
	PackageCell equipmentList[MAX_EQUIPMENT_COUNT];
}MsgDBEquipmentListResponse;
*/

#define MSG_DB_ITEMS_LIST							MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x0007)

typedef struct tagMsgDBItemsListResponse : public MsgDBBaseResponse
{
	ACE_UINT32 unCount;
	PackageCell list[1];
}MsgDBItemsListResponse;

#define MSG_DB_MAP_LIST								MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x0008)

typedef struct tagMsgDBMapListResponse : public MsgDBBaseResponse
{
	MapInstanceInfo instanceInfo;
	RewardInfo reward;
	MapFlagInfo flagList[MAX_MAP_COUNT];
	ACE_UINT32 unLastRewardTime;
	ACE_UINT32 unFreeRebornCount;
	ACE_UINT32 unLastRebornTime;
	MapFlagInfo giftList[MAX_MAP_COUNT];
	//BattleSnapInfo snapInfo;
	//MapBattleInfo battleInfo;
}MsgDBMapListResponse;

#define MSG_DB_UPDATE_BASIC_INFO					MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x0009)

typedef struct tagMsgDBUpdateBasicInfoRequest
{
	ACE_UINT32 unCoin;//贝壳
	ACE_UINT32 unMoney;//金币
	ACE_UINT32 unExp;//exp
	ACE_UINT32 unLevel;//等级
	ACE_UINT32 unPowerPoint;//合金
	ACE_UINT32 unHonour;//荣誉值
	ACE_UINT32 unFriendship;//友情值
	ACE_UINT32 unDynamicEnergy;//动感能量
}MsgDBUpdateBasicInfoRequest;

#define MSG_DB_UPDATE_ENERGY						MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x000a)

typedef struct tagMsgDBUpdateEnergyRequest
{
	ACE_UINT32 unEnergy;
	ACE_UINT32 unRestoreTime;
// 	ACE_UINT32 unPVPEnergy;
// 	ACE_UINT32 unPVPRestoreTime;
	//ACE_UINT32 unEnergyBuyTime;
	//ACE_UINT32 unEnergyBuyCount;
}MsgDBUpdateEnergyRequest;

#define MSG_DB_UPDATE_CURRENT_MAP					MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x000b)

typedef struct tagMsgDBUpdateCurrentMapRequest
{
	MapInstanceInfo info;
	RewardInfo reward;
	ACE_UINT32 unLastRewardTime;
}MsgDBUpdateCurrentMapRequest;

#define MSG_DB_UPDATE_MAP_FLAG_LIST					MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x000c)

typedef struct tagMsgDBUpdateMapFlagListRequest
{
	MapFlagInfo flagList[MAX_MAP_COUNT];
	MapFlagInfo	giftList[MAX_MAP_COUNT];
}MsgDBUpdateMapFlagListRequest;

#define MSG_DB_UPDATE_PLAYER_LIST					MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x000d)

typedef struct tagMsgDBUpdatePlayerListRequest
{
	//ACE_UINT32 unCount;
	//ACE_UINT32 unMaxSelected;
	ItemInfo staff;
	ACE_UINT32 selectedList[MAX_PLAYER_SELECTED_COUNT];
	PlayerInfo playerList[MAX_PLAYER_COUNT];
	ACE_UINT32 playerSkillList[MAX_PLAYER_SELECTED_COUNT];
}MsgDBUpdatePlayerListRequest;

/*
#define MSG_DB_UPDATE_EQUIPMENT_LIST				MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x000e)

typedef struct tagMsgDBUpdateEquipmentListRequest
{
	PackageCell equipmentList[MAX_EQUIPMENT_COUNT];
}MsgDBUpdateEquipmentListRequest;
*/

#define MSG_DB_UPDATE_PACKAGE_CELL					MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x000f)

typedef struct tagMsgDBUpdatePackageCellRequest
{
	PackageCell cell;
}MsgDBUpdatePackageCellRequest;

#define MSG_DB_ADD_PACKAGE_CELL						MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x0010)

typedef struct tagMsgDBAddPackageCellRequest
{
	PackageCell cell;
}MsgDBAddPackageCellRequest;

#define MSG_DB_SKILL_LIST							MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x0011)

typedef struct tagMsgDBSkillListResponse : public MsgDBBaseResponse
{
	ACE_UINT32 skillList[MAX_SKILL_COUNT];
	ACE_UINT32 playerSkillList[MAX_PLAYER_SKILL_COUNT];
	SkillBook bookRes[MAX_PLAYER_SKILL_COUNT];
}MsgDBSkillListResponse;

#define MSG_DB_UPDATE_SKILL_LIST					MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x0012)

typedef struct tagMsgDBUpdateSkillListRequest
{
	ACE_UINT32 skillList[MAX_SKILL_COUNT];
	ACE_UINT32 playerSkillList[MAX_PLAYER_SKILL_COUNT];
	SkillBook bookRes[MAX_PLAYER_SKILL_COUNT];
}MsgDBUpdateSkillListRequest;

#define MSG_DB_FRIEND_LIST							MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x0013)

typedef struct tagMsgDBFriendListResponse : public MsgDBBaseResponse
{
	ACE_UINT32 unMaxFriendCount;
	ACE_UINT32 inviteList[MAX_INVITE_COUNT];
	DBFriendInfo friendList[MAX_FRIEND_COUNT];
	AssistInfo assistList[MAX_ASSIST_COUNT];
	BadgeShuxingS m_bs[MAX_FRIEND_COUNT];
	DeleteFriendList deleteFriendList;
}MsgDBFriendListResponse;

#define MSG_DB_UPDATE_FRIEND_LIST					MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x0014)

typedef struct tagMsgDBUpdateFriendListRequest
{
	ACE_UINT32 unMaxFriendCount;
	DBFriendInfo friendList[MAX_FRIEND_COUNT];
}MsgDBUpdateFriendListRequest;

#define MSG_DB_UPDATE_INVITE_LIST					MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x0015)

typedef struct tagMsgDBUpdateInviteListRequest
{
	ACE_UINT32 inviteList[MAX_INVITE_COUNT];
}MsgDBUpdateInviteListRequest;


#define MSG_DB_UPDATE_CHARACTER_SNAP_INFO						MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x0016)

typedef struct tagMsgDBUpdateCharacterSnapInfoRequest
{
	PlayerTeamInfo teamInfo;
	//PlayerTeamInfo pvpTeamInfo;
}MsgDBUpdateCharacterSnapInfoRequest;

/*
#define MSG_DB_UPDATE_WEAPON_SKILL_LIST				MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x0016)

typedef struct tagMsgDBUpdateWeaponSkillListRequest
{
	WeaponSkillInfo list[MAX_WEAPON_SKILL_COUNT];
}MsgDBUpdateWeaponSkillListRequest;

#define MSG_DB_WEAPON_SKILL_LIST							MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x0017)

typedef struct tagMsgDBWeaponSkillListResponse : public MsgDBBaseResponse
{
	WeaponSkillInfo list[MAX_WEAPON_SKILL_COUNT];
	PropertyComponent improvePropertyList[PROPERTY_ID_MAX];
}MsgDBWeaponSkillListResponse;

#define MSG_DB_PROPERTY_UPDATE						MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x0018)

typedef struct tagMsgDBPropertyUpdateRequest
{
	PropertyComponent propertyList[PROPERTY_ID_MAX];
	ACE_UINT32 unSkillID;
}MsgDBPropertyUpdateRequest;
*/

#define MSG_DB_DELETE_LAST_ITEM						MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x0019)

typedef struct tagMsgDBDeleteLastItemRequest
{
	ACE_UINT32 unIdx;
}MsgDBDeleteLastItemRequest;

#define MSG_UPDATE_NAME								MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x001a)

typedef struct tagMsgDBUpdateNameRequest
{
	ACE_UINT32 unSN;
	ACE_UINT32 unSig;
	char name[MAX_CHARACTER_LENGTH + 1];
}MsgDBUpdateNameRequest;

typedef struct tagMsgDBUpdateNameResponse : public MsgDBBaseResponse
{
	ACE_UINT32 unSN;
	ACE_UINT32 unSig;
	char name[MAX_CHARACTER_LENGTH + 1];
}MsgDBUpdateNameResponse;

#define MSG_DB_UPDATE_LOGIN_INFO					MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x001b)

typedef struct tagMsgDBUpdateLoginInfoRequest
{
	ACE_UINT32 unLoginTime;
	ACE_UINT32 unLoginCount;
	ACE_UINT32 unLoginBonusCount;
}MsgDBUpdateLoginInfoRequest;

#define MSG_DB_FUNCTION_LIST						MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x001c)

typedef struct tagMsgDBFunctionListResponse : public MsgDBBaseResponse
{
	ACE_UINT32 list[MAX_FUNCTION_COUNT];
}MsgDBFunctionListResponse;

#define MSG_DB_UPDATE_FUNCTION_LIST					MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x001d)

typedef struct tagMsgDBUpdateFunctionListRequest
{
	ACE_UINT32 list[MAX_FUNCTION_COUNT];
}MsgDBUpdateFunctionListRequest;

#define MSG_DB_UPDATE_RECHARGE_INFO					MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x001e)

typedef struct tagMsgDBUpdateRechargeInfoRequest
{
	ACE_UINT32 unRechargeCount;
	ACE_UINT32 unRechargeAmount;
}MsgDBUpdateRechargeInfoRequest;

#define MSG_DB_UPDATE_PACKAGE_MAX					MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x001f)

typedef struct tagMsgDBUpdatePackageMaxRequest
{
	ACE_UINT32 unPackageMax;
}MsgDBUpdatePackageMaxRequest;

#define MSG_DB_UPDATE_REBORN_INFO					MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x0020)

typedef struct tagMsgDBUpdateRebornInfoRequest
{
	ACE_UINT32 unFreeRebornCount;
	ACE_UINT32 unLastRebornTime;
}MsgDBUpdateRebornInfoRequest;

/*
#define MSG_DB_UPDATE_BATTLE_INFO					MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x0021)

typedef struct tagMsgDBUpdateBattleInfoRequest
{
	MapBattleInfo battleInfo;
	BattleSnapInfo snapInfo;
}MsgDBUpdateBattleInfoRequest;
*/

#define MSG_DB_GIFT_LIST						MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x0022)

typedef struct tagMsgDBGiftListResponse : public MsgDBBaseResponse
{
	GiftInfo list[MAX_GIFT_COUNT];
}MsgDBGiftListResponse;

#define MSG_UPDATE_GIFT_LIST					MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x0023)

typedef struct tagMsgDBUpdateGiftListRequest
{
	GiftInfo list[MAX_GIFT_COUNT];
}MsgDBUpdateGiftListRequest;

#define MSG_UPDATE_TUTORIAL_FLAG				MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x0024)

typedef struct tagMsgDBUpdateTutorialFlagRequest
{
	ACE_UINT32 unTutorialFlag;
}MsgDBUpdateTutorialFlagRequest;

#define MSG_UPDATE_USE_LUCK_COUNT				MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x0025)

typedef struct tagMsgDBUpdateUseLuckCountRequest
{
	ACE_UINT32 unUseLuckCount;
}MsgDBUpdateUseLuckCountRequest;

/*
#define MSG_UPDATE_IMPROVE_PROPERTY				MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x0026)

typedef struct tagMsgDBUpdateImprovePropertyRequest
{
	PropertyComponent improvePropertyList[PROPERTY_ID_MAX];
}MsgDBUpdateImprovePropertyRequest;
*/

#define MSG_DB_COUNT_LIMIT_LIST					MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x0027)

typedef struct tagMsgDBCooldownListResponse : public MsgDBBaseResponse
{
	CooldownInstanceInfo list[MAX_COOLDOWN_INFO];
}MsgDBCooldownListResponse;

#define MSG_DB_UPDATE_COOLDOWN_LIST				MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x0028)

typedef struct tagMsgDBUpdateCooldownListRequest
{
	CooldownInstanceInfo list[MAX_COOLDOWN_INFO];
}MsgDBUpdateCooldownListRequest;

#define MSG_DB_HANDBOOK_LIST					MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x0029)

typedef struct tagMsgDBHandbookListResponse : public MsgDBBaseResponse
{
	ACE_UINT32 unCount;
	BaseItemInfo list[1];
}MsgDBHandbookListResponse;


#define MSG_DB_UPDATE_HANDBOOK_LIST					MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x002a)

typedef struct tagMsgDBUpdateHandbookListRequest
{
	ACE_UINT32 unCount;
	BaseItemInfo list[1];
}MsgDBUpdateHandbookListRequest;

#define MSG_DB_MATERIAL_LIST					MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x002b)

typedef struct tagMsgDBMaterialListResponse : public MsgDBBaseResponse
{
	ACE_UINT32 unCount;
	MaterialInfo list[1];
}MsgDBMaterialListResponse;

#define MSG_DB_UPDATE_MATERIAL_LIST					MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x002c)

typedef struct tagMsgDBUpdateMaterialListRequest
{
	ACE_UINT32 unCount;
	MaterialInfo list[1];
}MsgDBUpdateMaterialListRequest;

#define MSG_DB_VIP_LEVEL_UPDATE						MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x002d)

typedef struct tagMsgDBVipLevelUpdateRequest
{
	ACE_UINT32 unVipLevel;
}MsgDBVipLevelUpdateRequest;

#define MSG_DB_PVP_INFO							MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x002e)

typedef struct tagMsgDBPVPInfoResponse : public MsgDBBaseResponse
{
	PVPInfo info;
}MsgDBPVPInfoResponse;


#define MSG_DB_UPDATE_PVP_INFO							MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x002f)

typedef struct tagMsgDBUpdatePVPInfoResquest
{
	PVPInfo info;
}MsgDBUpdatePVPInfoResquest;
typedef struct tagMsgDBUpdatePVPInfoResquestEx : public MsgBaseRequest
{
	HLInfo info;
}MsgDBUpdatePVPInfoResquestEx;

#define MSG_DB_UPDATE_NAME_INTERNAL						MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x0030)

typedef struct tagMsgDBUpdateNameInternalRequest
{
	char name[MAX_CHARACTER_LENGTH + 1];
}MsgDBUpdateNameInternalRequest;

#define MSG_DB_MONEY_TREE_INFO							MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x0031)

typedef struct tagMsgDBMoneyTreeInfoResponse : MsgDBBaseResponse
{
	ACE_UINT32 unLevel;
	ACE_UINT32 unExp;
}MsgDBMoneyTreeInfoResponse;

#define MSG_DB_UPDATE_MONEY_TREE_INFO							MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x0032)

typedef struct tagMsgDBUpdateMoneyTreeInfoRequest
{
	ACE_UINT32 unLevel;
	ACE_UINT32 unExp;
}MsgDBUpdateMoneyTreeInfoRequest;

#define MSG_DB_UPDATE_HIGHEST_TEAM_INFO					MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x0033)

typedef struct tagMsgDBUpdateHighestTeamInfoRequest
{
	ACE_UINT32 unType;
	PlayerTeamInfo info;
}MsgDBUpdateHighestTeamInfoRequest;


#define MSG_DB_UPDATE_DATABASE					MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x0fffe)

typedef struct tagMsgDBUpdateDatabase
{
	ACE_UINT32 unVersion;
}MsgDBUpdateDatabase;

#define MSG_DB_LOAD_FAILED							MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x0fff)

typedef struct tagMsgDBLoadFailedResponse  : public MsgDBBaseResponse
{
	ACE_UINT32 unCode;
}MsgDBLoadFailedResponse;


#define MSG_DB_SECRET_LIST					MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x0034)
typedef struct tagMsgDBSecretListResponse : public MsgDBBaseResponse  //added by jinpan for secret
{
//	SecretItemInfo list[1];
	SecretItemInfo list[MAX_SECRET_LIST];
	ACE_UINT32 unCellCount;
	ACE_UINT32 unRefreshTimes;
	ACE_UINT32 unLastRefreshTime;
}MsgDBSecretListResponse;


#define MSG_DB_UPDATE_SECRET_LIST					MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x0035)

typedef struct tagMsgDBUpdateSecretListRequest
{
	ACE_UINT32 unCellCount;
	ACE_UINT32 unRefreshTimes;
	ACE_UINT32 unLastRefreshTime;
	SecretItemInfo list[1];
}MsgDBUpdateSecretListRequest;

//---------wangwei wing
#define MSG_DB_WING_LIST						MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x0036)
typedef struct tagMsgDBWingListResponse : public MsgDBBaseResponse{
	ACE_UINT32 unCount;
	WingItemInfo list[MAX_WING_LIST];
}MsgDBWingListResponse;

#define MSG_DB_UPDATE_WING_LIST					MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x0037)
typedef struct tagMsgDBUpdateWingListRequest{
	ACE_UINT32 unCount;
	WingItemInfo list[MAX_WING_LIST];
}MsgDBUpdateWingListRequest;

#define MSG_DB_GET_ACCOUNT_INFO		MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x0038)
#define FIND_TYPE_BY_ACCOUNT_NAME 1 //通过帐号查找
#define FIND_TYPE_BY_PLAYER_NAME 2//通过名字查找
typedef struct tagMsgDBGetAccountInfoRequest
{
	ACE_UINT32 dwFindType;
	char name[MAX_CHARACTER_LENGTH + 1];
}MsgDBGetAccountInfoRequest;

typedef struct tagMsgDBAccountInfoResponse : public MsgDBBaseResponse
{
	AccountBasicInfos m_oBasicInfos;
	AccountItemInfos m_oItemInfos;
	AccountPlayerInfos m_oPlayerInfos;
}MsgDBAccountInfoResponse;

#define MSG_DB_QUERY_ACCOUNT_LIST		MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x0039)

typedef struct tagMsgDBQueryAccountListRequest
{
	ACE_UINT32 dwFindType;
	char name[MAX_CHARACTER_LENGTH + 1];
}MsgDBQueryAccountListRequest;

#define MSG_DB_UPDATE_CHARACTER_FLAG				MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x0040)

typedef struct tagMsgDBUpdateCharacterFlagRequest
{
	tagMsgDBUpdateCharacterFlagRequest()
	{
		unFlag = 0;
	}
	ACE_UINT32 unFlag;
}MsgDBUpdateCharacterFlagRequest;

typedef struct tagMsgDBQueryAccountListResponse : public MsgDBBaseResponse
{
	AccountBriefInfoList m_oAccountList;
}MsgDBQueryAccountListResponse;

#define MSG_DB_PLAYER_GIFT_BAG_CODE						MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x0041)

typedef struct tagMsgDBPlayerGiftBagCodeResponse : public MsgDBBaseResponse
{
	ACE_UINT32 m_dwGiftBagCodeNum;
	WORD m_giftBagCodeSet[MAX_GIFT_BAG_CODE_COUNT];
}MsgDBPlayerGiftBagCodeResponse;

#define MSG_DB_UPDATE_PLAYER_GIFT_BAG_CODE					MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x0042)

typedef struct tagMsgDBUpdatePlayerGiftBagCodeRequest
{
	WORD wGiftBagCodeType;
}MsgDBUpdatePlayerGiftBagCodeRequest;

#define MSG_DB_ADMIN_STATISTICS_REQ				MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x0043)

typedef struct tagMsgDBAdminStatisticsRequest
{
	ACE_UINT32 unStatisticsType;
	char strDate[11];
}MsgDBAdminStatisticsRequest;

typedef struct tagMsgDBAdminStatisticsResponse : public MsgDBBaseResponse
{
	ACE_UINT32 unData;
	ACE_UINT32 unStatisticsType;  
}MsgDBAdminStatisticsResponse;

#define MSG_DB_DOUBLE_DROP_INFO						MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x0045)

typedef struct tagMsgDBDoubleDropInfoResponse : public MsgDBBaseResponse
{
	ACE_UINT32 m_unVersion;
	ACE_UINT32 m_unCount;
	ACE_UINT32 m_usedDoubleList[MAX_DOUBLE_DROP_COUNT];
}MsgDBDoubleDropInfoResponse;

#define MSG_DB_UPDATE_DOUBLE_DROP_INFO					MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x0046)

typedef struct tagMsgDBUpdateDoubleDropInfoRequest 
{
	ACE_UINT32 m_unVersion;
	ACE_UINT32 m_usedDoubleList[MAX_DOUBLE_DROP_COUNT];
}MsgDBUpdateDoubleDropInfoRequest;

#define MSG_DB_TASK_LIST                             MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x0047)

typedef struct tagMsgDBUpdateTaskInfoRequest
{
	TaskInfo m_taskInfo;
}MsgDBUpdateTaskInfoRequest;

#define MSG_DB_UPDATE_TASK_LIST                      MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x0048)
#define MSG_DB_INSERT_TASK_LIST                      MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x0049)
typedef struct tagMsgDBTaskList
{
	ACE_UINT32 m_unCount;
	TaskInfo m_taskList[MAX_TOTAL_TASK_COUNT];
}MsgDBTaskList;

#define MSG_DB_UPDATE_CHANGED_DATE                      MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x004A)
typedef struct tagMsgDBUpdateChangedDate
{
	ACE_UINT32 m_unUpdateChangedDate;
}MsgDBUpdateChangedDate;

#define MSG_DB_INSERT_OBTAINED_ACTIVENESS_REWARD                      MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x004B)
typedef struct tagMsgDBInsertObtainedActivenessRewardRequest
{
	ACE_UINT32 m_unObtainedActivenessReward;
}MsgDBInsertObtainedActivenessRewardRequest;

#define MSG_DB_OBTAINED_ACTIVENESS_REWARD_LIST                        MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x004C)
typedef struct tagMsgDBObtainedActivenessRewardList
{
	ACE_UINT32 m_unCount;
	ACE_UINT32 m_ObtainedList[MAX_ACTIVENESS_COUNT];
}MsgDBObtainedActivenessRewardList;

#define MSG_DB_DELETE_TASK                        MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x004D)
typedef struct tagMsgDBDeleteTaskInfoRequest
{
	ACE_UINT32 m_unTaskID;
}MsgDBDeleteTaskInfoRequest;

#define MSG_DB_UPDATE_FRIENDSHIP						MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x004E)

typedef struct tagMsgDBUpdateFriendshipRequest
{
	ACE_UINT32 m_unFriendship;
}MsgDBUpdateFriendshipRequest;

#define MSG_DB_UPDATE_ASSIST_LIST					MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x004F)

typedef struct tagMsgDBUpdateAssistListRequest
{
	UINT32 unCount;
	AssistInfo assistList[MAX_ASSIST_COUNT];
}MsgDBUpdateAssistListRequest;

#define MSG_DB_UPDATE_TASK_PROGRESS_REQUEST					MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x0050)//任务进度
#define MSG_DB_UPDATE_TASK_PROGRESS_RESPONSE				MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x0051)

#define MSG_DB_GET_DATA_STATISTICS		MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x0060)

typedef struct tagMsgDBGetStatisticsResponse : public MsgDBBaseResponse
{
	ACE_UINT32 unData;
	ACE_UINT32 unType;
}MsgDBGetStatisticsResponse;

#define MSG_DB_LOG_INFO_REQUEST		MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x0063)//向数据库写日志请求
#define MSG_DB_LOG_INFO_MAX_LEN		20

typedef struct tagMsgDBLogInfoRequest
{
	ACE_UINT32  unCount;
	LogItemInfo logInfoItem[MSG_DB_LOG_INFO_MAX_LEN];//日志信息
}MsgDBLogInfoRequest;

#define MSG_DB_ADMINCOMMAND_LOG_INFO_REQUEST		MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x0070)//获取日志信息请求
typedef struct tagMsgDBAdminLogInfoRequest
{
	tagMsgDBAdminLogInfoRequest()
	{
		ZeroVar(*this);
	}
	ACE_UINT32 m_unType;//log类别 0表示忽略此项
	ACE_UINT32 m_unUserID;//帐号查询 0表示忽略此项
	ACE_UINT32 m_unLevel;//等级查询 0表示忽略此项
	ACE_UINT32 m_goodsID;//装备ID查询 0表示忽略此项
	ACE_INT32 m_op_action;//动作发生原因查询 0表示忽略此项
	int m_pageNum;//显示页数 每次以100项为一页
	ObjAdr m_srcAdr;
}MsgDBAdminLogInfoRequest;

#define MSG_DB_ADMINCOMMAND_LOG_INFO_RESPONSE		MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x0071)//获取日志信息结果
#define MSG_DB_ADMINCOMMAND_LOG_MAX_COUNT 100
typedef struct tagMsgDBAdminLogInfoResponse
{
	ACE_UINT32  m_unCount;
	LogItemInfo m_logInfoItem[MSG_DB_ADMINCOMMAND_LOG_MAX_COUNT];//日志内容
}MsgDBAdminLogInfoResponse;


// #define MSG_DB_UPDATE_TASK_LIST                      MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x0048)
// #define MSG_DB_INSERT_TASK_LIST                      MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x0049)
#define MSG_DB_UPDATE_LA_PROGRESS_REQUEST					MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x0072)//限时活动任务
#define MSG_DB_UPDATE_LA_PROGRESS_RESPONSE				MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x0073)
#define MSG_DB_UPDATE_LA_PROGRESS_RESPONSE1				MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x0074)
typedef struct tagMsgDBLimitedActivityList
{
	ACE_UINT32 m_unCount;
	LimitedActivityInfo m_LAList[MAX_LIMITED_ACTIVITY_COUNT];//限时活动列表
}MsgDBLimitedActivityList;


#define MSG_DB_UPDATE_GOLDEN_TOUCH_REQUEST					MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x0075)

typedef struct tagMsgDBUpdateGoldenTouchRequest
{
	ACE_UINT32 m_unUsedCount;
}MsgDBUpdateGoldenTouchRequest;


#define MSG_DB_ADMINCOMMAND_RECHARGE_INFO_REQUEST		MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x0076)//充值请求
typedef struct tagMsgDBAdminRechargeRequest
{
	tagMsgDBAdminRechargeRequest()
	{
		ZeroVar(*this);
	}
	char orderID[RECHARGE_ORDERID_LEN+1];//充值头
	ACE_UINT32 unProductCount;//购买商品数量
	ACE_UINT32 unCharacterID;//充值用户id
	ACE_UINT32 unPayStats;//支付状态
	ACE_UINT32 unProductId;//商品id
	double	  unRenminbi;//充值金额(人民币)
	char  strChannel[RECHARGE_CHANNEL_LEN + 1];//充值渠道id
	char  deal_time[33];//处理时间
}MsgDBAdminRechargeRequest;

#define MSG_DB_ADMINCOMMAND_RECHARGE_INFO_RESPONSE		MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x0077)//充值请求返回结果
typedef struct tagMsgDBAdminRechargeResponse: public MsgDBBaseResponse
{
	tagMsgDBAdminRechargeResponse()
	{
		ZeroVar(*this);
	}
	char orderID[RECHARGE_ORDERID_LEN];//充值头
	int unErrorflag;//附加标记位，主要用于错误类型标记
}MsgDBAdminRechargeResponse;// #define  MSG_DB_ADMINCOMMAND_Announcement_REQUEST		MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x0073)//公告请求
// typedef struct tagMsgDBAdminAnnouncementRequest
// {
//	ACE_UINT32  m_unOpType;
//	ACE_UINT32  m_unCount;
//	char m_strBuffer[MAX_ADMIN_OP_BUFFER_ANNOUNCEMENT_LENGTH+1];
//}MsgDBAdminAnnouncementRequest;

#define MSG_DB_GM_ADD_REQUEST								MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x0078)//GM DB 添加请求
typedef struct tagMsgGMAddRequest
{
	GMInfo gm;//gm内容
}MsgGMAddRequest;

#define MSG_DB_UPDATE_BUY_ENERGY_REQUEST					MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x0079)
typedef struct tagMsgDBUpdateBuyEnergyRequest
{
	ACE_UINT32 m_unCurrentCount;
}MsgDBUpdateBuyEnergyRequest;

#define MSG_DB_ORDER_REQUEST					MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x0080)
typedef struct tagMsgDBOrderRequest
{
	ACE_UINT32 unSig;
	ACE_UINT32 unSN;
	ACE_INT32 product_id;//商品id
	ACE_INT32 product_count;//商品数量
}MsgDBOrderRequest;

#define MSG_DB_ORDER_RESPONSE					MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x0081)
typedef struct tagMsgDBOrderResponse: public MsgDBOrderRequest
{
	char orderID[RECHARGE_ORDERID_LEN+1];//充值头
	ACE_UINT32 m_unID;
	ACE_INT32 nResult;
	ACE_UINT32 unSig;
}MsgDBOrderResponse;

#define MSG_DB_UPDATE_VIP_GIFT_INFO					MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x0082)//更新已领取vip礼包
typedef struct tagMsgDBVipGiftInfo
{
	VipGift m_vipGift;//vip礼包内容
}MsgDBVipGiftInfo;

#define MSG_DB_UPDATE_DELERE_FRIEND_LIST					MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x0083)//更新删除好友列表

//徽章系统
#define MSG_DB_UPDATE_BADGE_PROGRESS_RESPONSE				MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x0084)//更新徽章系统
#define MSG_DB_UPDATE_BADGE_PROGRESS_RESPONSE1				MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x0085)//更新徽章系统
typedef struct tagMsgDBBadgeList
{
	ACE_UINT32 m_unCount;
	BadgeInfo m_BadgeList[1];//徽章内容
}MsgDBBadgeList;

#define MSG_DB_PROPS_LIST					MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x0086)//获取道具

typedef struct tagMsgDBPropsListResponse : public MsgDBBaseResponse
{
	ACE_UINT32 unCount;
	PropsInfo list[1];
}MsgDBPropsListResponse;

#define MSG_DB_UPDATE_PROPS_LIST					MAKE_MSG_TYPE(DB_PROTOCOL_GROUP, 0x0087)//更新道具

typedef struct tagMsgDBUpdatePropsListRequest
{
	ACE_UINT32 unCount;
	PropsInfo list[1];
}MsgDBUpdatePropsListRequest;