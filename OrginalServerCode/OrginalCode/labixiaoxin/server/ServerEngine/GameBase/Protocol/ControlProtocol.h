#pragma once

#include "..\..\Base\Protocol\Protocol.h"
#include "..\Common\GameDefine.h"

#define CLIENT_CLOSE_ERROR_NONE				0x00
#define CLIENT_CLOSE_ERROR_INVALID_SESSION	0x01
#define CLIENT_CLOSE_ERROR_KICK_BY_ANOTHER	0x02
#define CLIENT_CLOSE_ERROR_NEW_CONNECTION	0x03

#define GAME_SERVER_CONTROL_PROTOCOL_GROUP 0x0001


#define MSG_REGISTER_ADAPTER_REQUEST				MAKE_MSG_TYPE(GAME_SERVER_CONTROL_PROTOCOL_GROUP, 0x0001)
#define MSG_REGISTER_ADAPTER_RESPONSE				MAKE_MSG_TYPE(GAME_SERVER_CONTROL_PROTOCOL_GROUP, 0x0002)
#define MSG_UNREGISTER_ADAPTER_REQUEST				MAKE_MSG_TYPE(GAME_SERVER_CONTROL_PROTOCOL_GROUP, 0x0003)
#define MSG_UNREGISTER_ADAPTER_RESPONSE				MAKE_MSG_TYPE(GAME_SERVER_CONTROL_PROTOCOL_GROUP, 0x0004)
#define MSG_REPORT_ADAPTER_STATUS					MAKE_MSG_TYPE(GAME_SERVER_CONTROL_PROTOCOL_GROUP, 0x0005)

#define MSG_ADMIN_COMMAND_REQUEST					MAKE_MSG_TYPE(GAME_SERVER_CONTROL_PROTOCOL_GROUP, 0x0101)
#define MSG_ADMIN_COMMAND_RESPONSE					MAKE_MSG_TYPE(GAME_SERVER_CONTROL_PROTOCOL_GROUP, 0x0102)

#define MSG_GET_SERVICE_STATUS_REQUEST				MAKE_MSG_TYPE(GAME_SERVER_CONTROL_PROTOCOL_GROUP, 0x0103)
#define MSG_GET_SERVICE_STATUS_RESPONSE				MAKE_MSG_TYPE(GAME_SERVER_CONTROL_PROTOCOL_GROUP, 0x0104)

typedef struct tagMsgGetServiceStatusRequest
{
	ACE_UINT32 unFlag;
}MsgGetServiceStatusRequest;

typedef struct tagMsgGetServiceStatusResponse
{
	ACE_UINT32 unStatus;
	char info[MAX_SERVICE_INFO_MSG_LEN + 1];
}MsgGetServiceStatusResponse;

#define MSG_ADD_LOG_REQUEST							MAKE_MSG_TYPE(GAME_SERVER_CONTROL_PROTOCOL_GROUP, 0x0201)

typedef struct tagMsgAddLogRequest
{
	char strLog[1];
}MsgAddLogRequest;

#define GAME_INTERNET_PROTOCOL_GROUP 0x0002

#define MSG_CLIENT_MSG_ACK							MAKE_MSG_TYPE(GAME_INTERNET_PROTOCOL_GROUP, 0x0001)

#define MSG_DESTROY_MSG_ACK							MAKE_MSG_TYPE(GAME_INTERNET_PROTOCOL_GROUP, 0x0002)//客户端连接失败
typedef struct tagMsgDestroyRequest
{
	ACE_UINT32 unSN;//错误标记
	ACE_UINT32 unErrorCode;//错误代码
}MsgDestroyRequest;

/*
#define MSG_CREATE_SUB_ADAPTER_OBJ					MAKE_MSG_TYPE(GAME_SERVER_CONTROL_PROTOCOL_GROUP, 0x0006)
#define MSG_CREATE_SUB_ADAPTER_OBJ_RESULT			MAKE_MSG_TYPE(GAME_SERVER_CONTROL_PROTOCOL_GROUP, 0x0007)
#define MSG_DESTROY_SUB_ADAPTER_OBJ					MAKE_MSG_TYPE(GAME_SERVER_CONTROL_PROTOCOL_GROUP, 0x0008)
#define MSG_DESTROY_SUB_ADAPTER_OBJ_RESULT			MAKE_MSG_TYPE(GAME_SERVER_CONTROL_PROTOCOL_GROUP, 0x0009)
#define MSG_WANT_CREATE_SUB_ADAPTER_OBJ				MAKE_MSG_TYPE(GAME_SERVER_CONTROL_PROTOCOL_GROUP, 0x000a)
#define MSG_WANT_DESTROY_SUB_ADAPTER_OBJ			MAKE_MSG_TYPE(GAME_SERVER_CONTROL_PROTOCOL_GROUP, 0x000b)
#define MSG_SUB_ADAPTER_OBJ_REACTIVATE				MAKE_MSG_TYPE(GAME_SERVER_CONTROL_PROTOCOL_GROUP, 0x000c)
#define MSG_SUB_ADAPTER_OBJ_QUERY					MAKE_MSG_TYPE(GAME_SERVER_CONTROL_PROTOCOL_GROUP, 0x0MsgHomeInfoRequest00d)MSG_ENTITY_INFO_RESPONSE
#define MSG_SUB_ADAPTER_OBJ_QUERY_RESULT			MAKE_MSG_TYPE(GAME_SERVER_CONTROL_PROTOCOL_GROUP, 0x000e)
#define MSG_SUB_ADAPTER_OBJ_NOTFOUND				MAKE_MSG_TYPE(GAME_SERVER_CONTROL_PROTOCOL_GROUP, 0x000f)

typedef struct tagMsgSubAdapterObjInfo
{
	ACE_UINT32 unAdapterID;
	ACE_UINT32 unObjID;
	ACE_UINT32 unSN;
}MsgSubAdapterObjInfo;

typedef struct tagMsgSubAdapterObjResult
{
	ACE_UINT32 unObjID;
	ACE_UINT32 unSN;
	int nResult;
}MsgSubAdapterObjResult;

typedef struct tagMsgSubAdapterObjQuery
{
	ACE_UINT32 unServiceID;
	ACE_UINT32 unAdapterID;
	ACE_UINT32 unObjID;
}MsgSubAdapterObjQuery;
*/

typedef struct tagMsgBaseRequest
{
	ACE_UINT32 unSN;
}MsgBaseRequest;

typedef struct tagMsgBaseResponse
{
	ACE_UINT32 unSN;
	int nResult;
}MsgBaseResponse;

#define GAME_BASE_PROTOCOL_GROUP 0x0003



//登录请求
#define MSG_LOGIN_REQUEST							MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0001)
#define MSG_LOGIN_RESPONSE							MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0002)

typedef struct tagMsgLoginRequest
{
	ACE_UINT32 unVersion;
	char mac[MAX_MAC_LENGTH + 1];
	char email[MAX_EMAIL_LENGTH + 1];
	ACE_UINT32 unUserID;
}MsgLoginRequest;

typedef struct tagMsgLoginResponse
{
	int nResult;
	ACE_UINT32 unIP;
	ACE_UINT32 unPort;
	ACE_UINT32 unUserID;
	CharacterInfo list[MAX_PLAYER_PER_ACCOUNT];
}MsgLoginResponse;


//获取登录以后的信息
#define MSG_QUERY_LOGIN_INFO_REQUEST				MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0003)
#define MSG_QUERY_LOGIN_INFO_RESPONSE				MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0004)

typedef struct tagMsgQueryLoginInfoRequest
{
	ACE_UINT32 unLoginID;
	ACE_UINT32 unUserID;
}MsgQueryLoginInfoRequest;


typedef struct tagMsgQueryLoginInfoResponse
{
	ACE_UINT32 unIP;
	ACE_UINT32 unPort;
	ACE_UINT32 unUserID;
	char strSession[CLIENT_SESSION_LEN + 1];
}MsgQueryLoginInfoResponse;

/*
//创建gateway 代理
#define MSG_GATEWAY_PROXY_INIT_DATA_REQUEST			MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0005)
#define MSG_GATEWAY_PROXY_INIT_DATA_RESPONSE		MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0006)
//#define MSG_GATEWAY_PROXY_INIT_DONE					MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0007)

typedef struct tagMsgGatewayProxyInitDataRequest
{
	ACE_UINT32 unLoginAdapter;
	ACE_UINT32 unLoginID;
	char strSession[CLIENT_SESSION_LEN + 1];
}MsgGatewayProxyInitDataRequest;

typedef struct tagMsgGatewayProxyInitDataResponse
{
	ACE_UINT32 unLoginAdapter;
	ACE_UINT32 unLoginID;
	ACE_UINT32 unIP;
	ACE_UINT32 unPort;
}MsgGatewayProxyInitDataResponse;

//删除gateway 代理
#define MSG_GATEWAY_PROXY_DESTROY_REQUEST			MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0008)
#define MSG_GATEWAY_PROXY_DESTROY_RESPONSE			MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0009)

typedef struct tagMsgDestroyGatewayProxyRequest
{
	ACE_UINT32 unID;
	ACE_UINT32 unLoginID;
}MsgDestroyGatewayProxyRequest;

typedef struct tagMsgDestroyGatewayProxyResponse
{

}MsgDestroyGatewayProxyResponse;
*/

#define MSG_CHARACTER_UPDATE_DATA_REQUEST		MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0010)

#define MSG_GET_CHARACTER_ID_LIST_REQUEST		MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0011)

typedef struct tagMsgGetCharacterIDListRequest
{
	ACE_UINT32 unCurrentID;
	ACE_UINT32 unMaxCount;
}MsgGetCharacterIDListRequest;

#define MSG_GET_CHARACTER_ID_LIST_RESPONSE		MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0012)

typedef struct tagMsgGetCharacterIDListResponse
{
	ACE_UINT32 unCount;
	ACE_UINT32 list[1];
}MsgGetCharacterIDListResponse;


#define MSG_QUERY_CHARACTER_REQUEST				MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0101)
#define MSG_QUERY_CHARACTER_RESPONSE				MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0102)

typedef struct tagMsgQueryCharaterRequest : public MsgBaseRequest
{
}MsgQueryCharaterRequest;

typedef struct tagMsgQueryCharacterResponse : public MsgBaseResponse
{
	CharacterInfo list[MAX_PLAYER_PER_ACCOUNT];
}MsgCreateCharacterResponse;

#define MSG_SELECT_CHARACTER_REQUEST				MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0103)

typedef struct tagMsgSelectCharacterRequest : public MsgBaseRequest
{
	ACE_UINT32 unCharacterID;
	char name[MAX_CHARACTER_LENGTH + 1];
	ACE_UINT32 unPlayerID;
}MsgSelectCharacterRequest;

#define MSG_CHARACTER_INFO_RESPONSE					MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0105)

typedef struct tagMsgCharacterInfoResponse : public MsgBaseResponse
{
	ACE_UINT32 unCharacterID;
	char name[MAX_CHARACTER_LENGTH + 1];
	ACE_UINT32 unLevel;
	ACE_UINT32 unExp;
	ACE_UINT32 unCoin;
	ACE_UINT32 unMoney;
	ACE_UINT32 unPowerPoint;
	ACE_UINT32 unHonour;
	ACE_UINT32 unFriendship;
	ACE_UINT32 unDynamicEnergy;//动感能量
	ACE_UINT32 unLastLoginTime;
	ACE_UINT32 unLoginCount;
	ACE_UINT32 unLoginBonusCount;
	ACE_UINT32 unCreateTime;
	ACE_UINT32 unEnergy;
	ACE_UINT32 unEnergyRestoreTime;
// 	ACE_UINT32 unPVPEnergy;
// 	ACE_UINT32 unPVPEnergyRestoreTime;
	//ACE_UINT32 unBuyEnergyCount;
	//ACE_UINT32 unBuyEnergyTime;
	ACE_UINT32 unRechargeCount;
	ACE_UINT32 unRechargeAmount;
	ACE_UINT32 unPackageMax;
	ACE_UINT32 unTutorialFlag;
	ACE_UINT32 unFlag;
	ACE_UINT32 unGoldenTouchUsedCount;
	ACE_UINT32 unCurrentBuyCount;
	
	ACE_UINT32 m_bitField;
	VipInfo m_vipInfo;
	VipGift m_vipGift;
	ProductList m_Productlist;
	ACE_UINT32 m_power;
}MsgCharacterInfoResponse;


#define MSG_PACKAGE_INFO_RESPONSE					MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0106)

typedef struct tagMsgPackageInfoResponse : public MsgBaseResponse
{
	ACE_UINT32 unCount;
	PackageCell list[1];
}MsgPackageInfoResponse;

#define MSG_PLAYER_INFO_RESPONSE					MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0107)

typedef struct tagMsgPlayerInfoResponse : public MsgBaseResponse
{
	ItemInfo staff;
	ACE_UINT32 unCount;
	//ACE_UINT32 unMaxSelected;
	ACE_UINT32 selectedList[MAX_PLAYER_SELECTED_COUNT];
	PlayerInfo playerList[MAX_PLAYER_COUNT];
	ACE_UINT32 playerSkillList[MAX_PLAYER_SELECTED_COUNT];
	ACE_UINT32 unHighestPoint;
}MsgPlayerInfoResponse;

/*
#define MSG_EQUIPMENT_INFO_RESPONSE					MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0108)

typedef struct tagMsgEquipmentInfoResponse : public MsgBaseResponse
{
	ACE_UINT32 unCount;
	PackageCell equipmentList[MAX_EQUIPMENT_COUNT];
}MsgEquipmentInfoResponse;
*/

#define MSG_UPDATE_PLAYER_LIST_REQUEST					MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0109)//换位置
#define MSG_UPDATE_PLAYER_LIST_RESPONSE					MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x010a)

typedef struct tagMsgUpdatePlayerListRequest : public MsgBaseRequest
{
	ACE_UINT32 unType;
	ACE_UINT32 list[MAX_PLAYER_SELECTED_COUNT];
	ACE_UINT32 playerSkillList[MAX_PLAYER_SELECTED_COUNT];
}MsgUpdatePlayerListRequest;

typedef struct tagMsgUpdatePlayerListResponse : public MsgBaseResponse
{
	
}MsgUpdatePlayerListResponse;

#define MSG_SELECT_EQUIPMENT_REQUEST					MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x010b)//换装备
#define MSG_SELECT_EQUIPMENT_RESPONSE					MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x010c)

typedef struct tagMsgSelectEquipmentRequest : public MsgBaseRequest
{
	int idx;
	ACE_UINT32 unPlayerID;
	int equipment_type;
}MsgSelectEquipmentRequest;

typedef struct tagMsgSelectEquipmentResponse : public MsgBaseResponse
{

}MsgSelectEquipmentResponse;

#define MSG_ENTER_MAP_REQUEST							MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x010d)//进入地图请求
#define MSG_ENTER_MAP_RESPONSE							MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x010e)//进入地图返回结果

typedef struct tagMsgEnterMapRequest : public MsgBaseRequest
{
	ACE_UINT32 unMapID;
	ACE_UINT32 specialMap;//密境地图id
	ACE_UINT32 unFriendID;
	ACE_UINT32 unMultEnergy;//xxj 2015/04/21  10:42:41 多倍体力 
}MsgEnterMapRequest;

typedef struct tagMsgEnterMapResponse : public MsgBaseResponse
{
	MapInstanceInfo info;
	RewardInfo reward;
}MsgEnterMapResponse;

#define MSG_GET_MAP_REWARD_REQUEST						MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x010f)//结算奖励请求
#define MSG_GET_MAP_REWARD_RESPONSE						MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0110)//结算奖励返回

typedef struct tagMsgGetMapRewardRequest : public MsgBaseRequest
{
	ACE_UINT32 unMapID;
	ACE_UINT32 unLaunchCount;
	ACE_UINT32 unBellCount;
	
}MsgGetMapRewardRequest;

typedef struct tagMsgGetMapRewardResponse : public MsgBaseResponse
{
	ACE_UINT32 unMultEnergy;//xxj 2015/04/21  15:59:14 多倍体力返回
	ACE_UINT32 unReward3Star;
	RewardInfo reward;
}MsgGetMapRewardResponse;

#define MSG_MAP_LIST_INFO_RESPONSE						MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0111)//地图通关列表

typedef struct tagMsgMapListInfoResponse : public MsgBaseResponse
{
	MapInstanceInfo instanceInfo;
	//MapBattleInfo battleInfo;
	//RewardInfo reward;
	ACE_UINT32 unCount;
	MapFlagInfo flagList[MAX_MAP_COUNT];
	ACE_UINT32 unLastRewardTime;
	ACE_UINT32 unFreeRebornCount;
	ACE_UINT32 unLastRebornTime;
	ACE_UINT32 unMapGroupCount;
	MapFlagInfo giftList[MAX_MAP_COUNT];
}MsgMapListInfoResponse;

#define MSG_SKILL_LIST_RESPONSE							MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0112)

typedef struct tagMsgSkillListResponse : public MsgBaseResponse
{
	ACE_UINT32 unCount;
	ACE_UINT32 skillList[MAX_SKILL_COUNT];
	ACE_UINT32 unPlayerSkillCount;
	ACE_UINT32 playerSkillList[MAX_PLAYER_SKILL_COUNT];

	SkillBook bookRes[MAX_PLAYER_SKILL_COUNT];//作为合成用的技能图纸
	ACE_UINT32 unBookResCount;//最为升级图纸的种类个数
}MsgSkillListResponse;

#define MSG_CHARACTER_INFO_UPDATE_REQUEST				MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0113)//更新基础信息//

typedef struct tagMsgCharacterInfoUpdateRequest
{
	ACE_UINT32 unCharacterID;
	ACE_UINT32 unType;	//pvp or pve
	PlayerTeamInfo teamInfo; 
	/*
	PackageCell equipmentList[MAX_EQUIPMENT_COUNT];
	PropertyComponent propertyList[PLAYER_PROPERTY_MAX];
	ACE_UINT32 unSkillID;
	*/
}MsgCharacterInfoUpdateRequest;

#define MSG_CHARACTER_LEVEL_UPDATE_REQUEST		MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0114)

typedef struct tagMsgCharacterLevelUpdateRequest
{
	ACE_UINT32 unCharacterID;
	ACE_UINT32 unLevel;
}MsgCharacterLevelUpdateRequest;



/*
#define MSG_CHARACTER_EQUIPMENT_LIST_UPDATE_REQUEST		MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0114)

typedef struct tagMsgCharacterEquipmentListUpdateRequest
{
	ACE_UINT32 unCharacterID;
	PackageCell equipmentList[MAX_EQUIPMENT_COUNT];
}MsgCharacterEquipmentListUpdateRequest;

#define MSG_CHARACTER_PROPERTY_UPDATE_REQUEST			MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0115)

typedef struct tagMsgCharacterPropertyUpdateRequest
{
	ACE_UINT32 unCharacterID;
	PropertyComponent propertyList[PROPERTY_ID_MAX];
	ACE_UINT32 unSkillID;
}MsgCharacterPropertyUpdateRequest;
*/
/*
#define MSG_INIT_FRIEND_LIST_REQUEST					MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0115)

typedef struct tagMsgInitFriendListRequest : public MsgBaseRequest
{
	
}MsgInitFriendListRequest;

#define MSG_INIT_FRIEND_LIST_RESPONSE					MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0116)

typedef struct tagMsgInitFriendListResponse : public MsgBaseResponse
{
	ACE_UINT32 unInviteCount;
	ACE_UINT32 unFriendCount;
	CharacterInfoExt inviteList[MAX_INVITE_COUNT];
	FriendInfo friendList[MAX_FRIEND_COUNT];
}MsgInitFriendListResponse;
*/

#define MSG_GET_CHARACTER_DETAIL_REQUEST				MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0117)

typedef struct tagMsgGetCharacterDetailRequest
{
	ACE_UINT32 unType;
	ACE_UINT32 unCount;
	ACE_UINT32 list[1];
}MsgGetCharacterDetailRequest;

#define MSG_GET_CHARACTER_DETAIL_RESPONSE				MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0118)

typedef struct tagMsgGetCharacterDetailResponse
{
	ACE_UINT32 unType;
	ACE_UINT32 unCount;
	CharacterInfoExt list[1];
}MsgGetCharacterDetailResponse;

#define MSG_GET_FRIEND_DETAIL_REQUEST					MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0119)

typedef struct tagMsgGetFriendDetailRequest : public MsgBaseRequest
{
	ACE_UINT32 unType;
	ACE_INT32 unPage;
}MsgGetFriendDetailRequest;

#define MSG_INVITE_DETAIL_RESPONSE						MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x011a)

typedef struct tagMsgInviteDetailResponse : public MsgBaseResponse
{
	ACE_UINT32 unCount;
	ACE_UINT32 unMaxPage;
	ACE_UINT32 unPage;
	CharacterInfoExt list[1];
}MsgInviteDetailResponse;

#define MSG_FRIEND_DETAIL_RESPONSE						MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x011b)

typedef struct tagMsgFriendDetailResponse : public MsgBaseResponse
{
	ACE_UINT32 unMaxFriendCount;
	ACE_UINT32 unCount;
	ACE_UINT32 unMaxPage;
	ACE_UINT32 unPage;
	FriendInfo list[1];
}MsgFriendDetailResponse;

#define MSG_INVITE_FRIEND_REQUEST						MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x011c)//添加好友

typedef struct tagMsgInviteFriendRequest : public MsgBaseRequest
{
	ACE_UINT32 unFriendID;
}MsgInviteFriendRequest;

#define MSG_APPLY_INVITATION_REQUEST					MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x011d)//同意邀请

typedef struct tagMsgApplyInvitationRequest : public MsgBaseRequest
{
	ACE_UINT32 unFriendID;
}MsgApplyInvitationRequest;

#define MSG_APPLY_INVITATION_RESPONSE					MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x011e)

typedef struct tagMsgApplyInvitationResponse : public MsgBaseResponse
{
	ACE_UINT32 unFriendID;
}MsgApplyInvitationResponse;

#define MSG_GET_RANDOM_CHARACTER_REQUEST				MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x011f)//获得助战队友
typedef struct tagMsgRandomCharacterRequest : public MsgBaseRequest
{
	ACE_UINT32 unMapID;
}MsgRandomCharacterRequest;

typedef struct tagMsgGetRandomCharacterRequest : public MsgBaseRequest
{
	ACE_UINT32 unGuidanceFlag;
	ACE_UINT32 unMapID;
	ACE_UINT32 unCount;
	ACE_UINT32 oFriendIDList[MAX_FRIEND_COUNT];
}MsgGetRandomCharacterRequest;

#define MSG_GET_RANDOM_CHARACTER_RESPONSE				MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0120)

typedef struct tagMsgGetRandomCharacterResponse : public MsgBaseResponse
{
	ACE_UINT32 unCount;
	CharacterInfoExt list[1];
}MsgGetRandomCharacterResponse;

#define MSG_GET_LUCK_REQUEST							MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0121)

typedef struct tagMsgGetLuckRequest : public MsgBaseRequest
{
	ACE_UINT32 unIsTen;
	ACE_UINT32 unBehaviorID;
}MsgGetLuckRequest;

#define MSG_GET_LUCK_RESPONSE							MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0122)

typedef struct tagMsgGetLuckResponse : public MsgBaseResponse
{
	/*
	ACE_UINT32 
	ACE_UINT32 unItemID;
	*/
	RewardInfo reward;
}MsgGetLuckResponse;

/*
#define MSG_WEAPON_SKILL_LIST_RESPONSE							MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0123)

typedef struct tagMsgWeaponSkillListResponse : public MsgBaseResponse
{
	ACE_UINT32 unCount;
	WeaponSkillInfo skillList[MAX_WEAPON_SKILL_COUNT];
}MsgWeaponSkillListResponse;
*/

#define MSG_ITEM_LEVEL_UP_REQUEST							MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0124)//物品升级
//升级将领或装备//
typedef struct tagMsgItemLevelUpRequest : public MsgBaseRequest
{
	ACE_UINT32 unIdx;//升级将领，idx传0//	// 身上装备 传id作为idx//
	ACE_UINT32 unPlayerID;//升级腰带，playerID为唐僧的//
	ACE_UINT32 unLevel;//如果是背包里的装备，idx为实际的，playerID为0//
}MsgItemLevelUpRequest;

#define MSG_ITEM_LEVEL_UP_RESPONSE						MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0125)//物品升级返回值//

typedef struct tagMsgItemLevelUpResponse : public MsgBaseResponse
{
	ACE_UINT32 unCoin;
	ACE_UINT32 unPowerPoint;
	ACE_UINT32 unPower;
}MsgItemLevelUpResponse;

#define MSG_SKILL_LEVEL_UP_REQUEST						MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0126)//技能升级

typedef struct tagMsgSkillLevelUpRequest : public MsgBaseRequest
{
	ACE_UINT32 unSkillID;
	//ACE_UINT32 skillType;
	ACE_UINT32 unLevel;
}MsgSkillLevelUpRequest;

#define MSG_SKILL_LEVEL_UP_RESPONSE					MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0127)

typedef struct tagMsgSkillLevelUpResponse : public MsgBaseResponse
{
	ACE_UINT32 unPower;
	ACE_UINT32 unDynamicEnergy;
}MsgSkillLevelUpResponse;

#define MSG_FIND_CHARACTER_REQUEST					MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0128)//查找人//

typedef struct tagMsgFindCharacterRequest : public MsgBaseRequest
{
	ACE_UINT32 unCharacterID;
}MsgFindCharacterRequest;

#define MSG_FIND_CHARACTER_RESPONSE					MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0129)

typedef struct tagMsgFindCharacterResponse : public MsgBaseResponse
{
	CharacterInfoExt info;
}MsgFindCharacterResponse;

#define MSG_DELETE_FRIEND_REQUEST					MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x012a)

typedef struct tagMsgDeleteFriendRequest : public MsgBaseRequest
{
	ACE_UINT32 unType;
	ACE_UINT32 unFriendID;
}MsgDeleteFriendRequest;

#define MSG_DELETE_FRIEND_RESPONSE					MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x012b)

typedef struct tagMsgDeleteFriendResponse : public MsgBaseResponse
{
}MsgDeleteFriendResponse;

#define MSG_DELETE_ITEM_REQUEST						MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x012c)//卖东西or熔炼DELETE_ITEM//分解

typedef struct tagMsgDeleteItemRequest : public MsgBaseRequest
{
	ACE_UINT32 unDeleteType;
	ACE_UINT32 unCount;
	ACE_UINT32 unIdxList[256];
}MsgDeleteItemRequest;

#define MSG_DELETE_ITEM_RESPONSE					MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x012d)

typedef struct tagMsgDeleteItemResponse : public MsgBaseResponse
{
}MsgDeleteItemResponse;

#define MSG_EQUIPMENT_STEP_UP_REQUEST				MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x012e)//升阶
#define MsgEquipmentStepUp_unGrade_MAX 16
typedef struct tagMsgEquipmentStepUpRequest : public MsgBaseRequest
{
	ACE_UINT32 unIdx;
	ACE_UINT32 unPlayerID;
	ACE_UINT32 unGrade;
	ACE_UINT32 unMaterialIdxList[MsgEquipmentStepUp_unGrade_MAX];
}MsgEquipmentStepUpRequest;

#define MSG_EQUIPMENT_STEP_UP_RESPONSE				MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x012f)

typedef struct tagMsgEquipmentStepUpResponse : public MsgBaseResponse
{
	ACE_UINT32 unPower;
}MsgEquipmentStepUpResponse;

#define MSG_CHANGE_NAME_REQUEST						MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0130)

typedef struct tagMsgChangeNameRequest : public MsgBaseRequest
{
	char name[MAX_CHARACTER_LENGTH + 1];
}MsgChangeNameRequest;

#define MSG_CHANGE_NAME_RESPONSE					MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0131)

typedef struct tagMsgChangeNameResponse : public MsgBaseResponse
{
	char name[MAX_CHARACTER_LENGTH + 1];
}MsgChangeNameResponse;

#define MSG_CHARACTER_NAME_UPDATE_REQUEST			MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0132)

typedef struct tagMsgCharacterNameUpdateRequest
{
	ACE_UINT32 unCharacterID;
	char name[MAX_CHARACTER_LENGTH + 1];
}MsgCharacterNameUpdateRequest;

/*
#define MSG_GET_MORE_LUCK_REQUEST							MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0133)

typedef struct tagMsgGetMoreLuckRequest : public MsgBaseRequest
{
	ACE_UINT32 unBehaviorID;
}MsgGetMoreLuckRequest;

#define MSG_GET_MORE_LUCK_RESPONSE							MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0134)

typedef struct tagMsgGetMoreLuckResponse : public MsgBaseResponse
{
	ACE_UINT32 unItemList[10];
}MsgGetMoreLuckResponse;
*/

#define MSG_GET_LOGIN_REWARD_REQUEST						MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0135)

typedef struct tagMsgGetLoginRewardRequest : public MsgBaseRequest
{
}MsgGetLoginRewardRequest;

#define MSG_GET_LOGIN_REWARD_RESPONSE						MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0136)

typedef struct tagMsgGetLoginRewardResponse : public MsgBaseResponse
{
	ACE_UINT32 unLoginCount;
}MsgGetLoginRewardResponse;

#define MSG_GET_GLOBAL_MAP_EVENT_REQUEST					MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0137)

typedef struct tagMsgGetGlobalMapEventRequest : public MsgBaseRequest
{
}MsgGetGlobalMapEventRequest;

#define MSG_GET_GLOBAL_MAP_EVENT_RESPONSE						MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0138)

typedef struct tagMsgGetGlobalMapEventResponse : public MsgBaseResponse
{
	ACE_UINT32 unCooldown;
	ACE_UINT32 unMapList[2 * COMMON_MAP_STAGE_COUNT];
}MsgGetGlobalMapEventResponse;

#define MSG_GOLD_BUY_REQUEST								MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0139)

typedef struct tagMsgGoldBuyRequest : public MsgBaseRequest
{
	ACE_UINT32 unType;
}MsgGoldBuyRequest;

#define MSG_GOLD_BUY_RESPONSE								MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x013a)

typedef struct tagMsgGoldBuyResponse : public MsgBaseResponse
{
}MsgGoldBuyResponse;

#define MSG_ENTER_MAP_QUERY_CHARACTER_REQUEST				MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x013b)//查询队友列表请求

typedef struct tagMsgEnterMapQueryCharacterRequest
{
	ACE_UINT32 unSN;
	ACE_UINT32 unMapID;
	ACE_UINT32 specialMap;
	ACE_UINT32 unCharacterID;//队友ID
	ACE_UINT32 unMultEnergy;
}MsgEnterMapQueryCharacterRequest;

#define MSG_ENTER_MAP_QUERY_CHARACTER_RESPONSE				MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x013c)//返回的查询队友列表结果

typedef struct tagMsgEnterMapQueryCharacterResponse
{
	int nResult;
	ACE_UINT32 unSN;
	ACE_UINT32 unMapID;
	ACE_UINT32 specialMap;
	ACE_UINT32 unMultEnergy;//xxj 2015/04/21  10:49:31 多倍体力
	CharacterInfoExt info;
}MsgEnterMapQueryCharacterResponse;

#define MSG_FUNCTION_LIST_RESPONSE							MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x013d)

typedef struct tagMsgFunctionListResponse : public MsgBaseResponse
{
	ACE_UINT32 unCount;
	ACE_UINT32 list[MAX_FUNCTION_COUNT];
}MsgFunctionListResponse;

#define MSG_UNLOCK_REWARD_RESPONSE							MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x013e)

typedef struct tagMsgUnlockRewardResponse : public MsgBaseResponse
{
	RewardInfo reward;
}MsgUnlockRewardResponse;

#define MSG_BATTLE_REBORN_REQUEST							MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x013f)
#define MSG_BATTLE_REBORN_RESPONSE							MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0140)

typedef struct tagMsgBattleRebornRequest : public MsgBaseRequest
{
}MsgBattleRebornRequest;

typedef struct tagMsgBattleRebornResponse : public MsgBaseResponse
{
}MsgBattleRebornResponse;

/*
#define MSG_BATTLE_COMMAND_REQUEST							MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0141)

typedef struct tagMsgBattleCommandRequest : public MsgBaseRequest
{
	ACE_UINT32 unBattleInfoSize;
	char battleInfo[3072];
}MsgBattleCommandRequest;
*/

#define MSG_CLEAR_MAP_REQUEST								MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0142)
#define MSG_CLEAR_MAP_RESPONSE								MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0143)

typedef struct tagMsgClearMapRequest : public MsgBaseRequest
{
	ACE_UINT32 unType;
}MsgClearMapRequest;

typedef struct tagMsgClearMapResponse : public MsgBaseResponse
{
}MsgClearMapResponse;

#define MSG_GIFT_LIST_RESPONSE								MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0144)

typedef struct tagMsgGiftListResponse : public MsgBaseResponse
{
	ACE_UINT32 unCount;
	GiftInfo giftList[MAX_GIFT_COUNT];
}MsgGiftListResponse;

#define MSG_USE_ITEM_REQUEST								MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0145)//使用道具，领礼包//
#define MSG_USE_ITEM_RESPONSE								MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0146)

typedef struct tagMsgUseItemRequest : public MsgBaseRequest
{
	ACE_UINT32 unItemType;
	ACE_UINT32 unIndex;
}MsgUseItemRequest;

typedef struct tagMsgUseItemResponse : public MsgBaseResponse
{
	RewardInfo reward;
}MsgUseItemResponse;

#define MSG_PURCHASE_GOLD_REQUEST								MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0147)//充值
#define MSG_PURCHASE_GOLD_RESPONSE								MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0148)

typedef struct tagMsgPurchaseRequest
{
	ACE_UINT32 unPurchaseID;
}MsgPurchaseRequest;

typedef struct tagMsgPurchaseResponse
{
	int nResult;
}MsgMsgPurchaseResponse;

#define MSG_UPDATE_TUTORIAL_FLAG_REQUEST						MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0149)
#define MSG_UPDATE_TUTORIAL_FLAG_RESPONSE						MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x014a)

typedef struct tagMsgUpdateTutorialFlagRequest : public MsgBaseRequest
{
	ACE_UINT32 unTutorialFlag;
}MsgUpdateTutorialFlagRequest;

typedef struct tagMsgUpdateTutorialFlagResponse : public MsgBaseResponse
{
}MsgUpdateTutorialFlagResponse;

/*
#define MSG_BATTLE_COMMAND_RESPONSE							MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x014b)

typedef struct tagMsgBattleCommandResponse : public MsgBaseResponse
{
	ACE_UINT32 unValid;
	int currentSection;
	int errorCode;
	int commandIndex;
	char command[MAX_COMMAND_BUFF_SIZE];
	int playerHP[MAX_PLAYER_SELECTED_COUNT + 2];
	int monsterHP[8];
}MsgBattleCommandResponse;
*/


#define MSG_COOLDOWN_LIST_RESPONSE						MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x014c)

typedef struct tagMsgCooldownListResponse : public MsgBaseResponse
{
	ACE_UINT32 unCount;
	CooldownInstanceInfo list[MAX_COOLDOWN_INFO];
}MsgCooldownListResponse;


#define MSG_DO_BEHAVIOR_REQUEST						MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x014d)

typedef struct tagMsgDoBehaviorRequest : public MsgBaseRequest
{
	ACE_UINT32 unID;
}MsgDoBehaviorRequest;

#define MSG_DO_BEHAVIOR_RESPONSE						MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x014e)

typedef struct tagMsgDoBehaviorResponse : public MsgBaseResponse
{
	//int nGold;
	RewardInfo reward;
}MsgDoBehaviorResponse;

#define MSG_GET_BROADCAST_MESSAGE_REQUEST						MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x014f)

typedef struct tagMsgGetBroadcastMessageRequest : public MsgBaseRequest
{
}MsgGetBroadcastMessageRequest;

#define MSG_GET_BROADCAST_MESSAGE_RESPONSE						MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0150)

typedef struct tagMsgGetBroadcastMessageResponse : public MsgBaseResponse
{
	ACE_UINT32 unCurrentCounter;
	ACE_UINT32 unCount;
	BroadcastMessage list[MAX_BROADCAST_MESSAGE_COUNT];
}MsgGetBroadcastMessageResponse;

#define MSG_HANDBOOK_LIST_RESPONSE							MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0151)

typedef struct tagMsgHandbookListResponse : public MsgBaseResponse
{
	ACE_UINT32 unCount;
	BaseItemInfo list[1];
}MsgHandbookListResponse;

#define MSG_MATERIAL_LIST_RESPONSE							MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0152)

typedef struct tagMsgMaterialListResponse : public MsgBaseResponse
{
	ACE_UINT32 unCount;
	MaterialInfo list[1];
}MsgMaterialListResponse;

#define MSG_COMPOSE_REQUEST									MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0153)//合成
#define MSG_COMPOSE_RESPONSE								MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0154)

typedef struct tagMsgComposeRequest : public MsgBaseRequest
{		
	ACE_UINT32 unItemID;
	ACE_UINT32 unTimes;
	
}MsgComposeRequest;

typedef struct tagMsgComposeResponse : public MsgBaseResponse
{

}MsgComposeResponse;


#define MSG_CHARACTER_VIP_UPDATE_REQUEST					MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0155)

typedef struct tagMsgCharacterVipUpdateRequest
{
	ACE_UINT32 unCharacterID;
	ACE_UINT32 unVipLevel;
}MsgCharacterVipUpdateRequest;

/*
#define MSG_SELECT_PLAYER_SKILL_REQUEST					MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0156)
#define MSG_SELECT_PLAYER_SKILL_RESPONSE					MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0157)

typedef struct tagMsgSelectPlayerSkillRequest : public MsgBaseRequest
{
	ACE_UINT32 unIndex;
	ACE_UINT32 unSkillID;
}MsgSelectPlayerSkillRequest;

typedef struct tagMsgSelectPlayerSkillResponse : public MsgBaseResponse
{

}MsgSelectPlayerSkillResponse;

*/


#define MSG_PVP_RANK_INFO_REQUEST							MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0158)
#define MSG_PVP_RANK_INFO_RESPONSE							MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0159)

typedef struct tagMsgPVPRankInfoRequest : public MsgBaseRequest
{
	
}MsgPVPRankInfoRequest;

typedef struct tagMsgPVPRankInfoResponse : public MsgBaseResponse
{
	ACE_UINT32 unTotalCount;
	PVPRankInfo rankInfo;
}MsgPVPRankInfoResponse;

#define MSG_PVP_BASIC_INFO_RESPONSE						MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x015a)

typedef struct tagMsgPVPBasicInfoResponse : public MsgBaseResponse
{
	PVPBasicInfo basicInfo;
	PVPOpponentInfo opponent;
}MsgPVPBasicInfoResponse;

/*
#define MSG_UPDATE_PVP_RANK_REQUEST						MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x015a)

typedef struct tagMsgUpdatePVPRankRequest
{
	ACE_UINT32 unCharacterID;
	PVPRankInfo rankInfo;
}MsgUpdatePVPRankRequest;
*/

/*
#define MSG_UPDATE_PVP_SCORE_REQUEST					MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x015b)

typedef struct tagMsgUpdatePVPScoreRequest
{
	ACE_UINT32 unCharacterID;
	ACE_UINT32 unSeasonID;
	ACE_UINT32 unScore;
	ACE_UINT32 unAll;
	ACE_UINT32 unWin;
}MsgUpdatePVPScoreRequest;
*/
/*
#define MSG_GET_PVP_OPPONENT_REQUEST					MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x015c)
#define MSG_GET_PVP_OPPONENT_RESPONSE					MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x015d)

typedef struct tagMsgGetPVPOpponentRequest
{
	ACE_UINT32 unCharacterID;
}MsgGetPVPOpponentRequest;

typedef struct tagMsgGetPVPOpponentResponse
{
	CharacterInfoExt opponent;
}MsgGetPVPOpponentResponse;
*/

#define MSG_COMMIT_PVP_RESULT_REQUEST					MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x015e)
#define MSG_COMMIT_PVP_RESULT_RESPONSE					MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x015f)

typedef struct tagMsgCommitPVPResultRequest : public MsgBaseRequest
{
	ACE_UINT32 win;
	ACE_UINT32 unSize;
	char commandData[1];
}MsgCommitPVPResultRequest;

typedef struct tagMsgCommitPVPResultResponse : public MsgBaseResponse
{
}MsgCommitPVPResultResponse;

#define MSG_GET_PVP_RANK_REWARD_REQUEST						MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0160)
#define MSG_GET_PVP_RANK_REWARD_RESPONSE					MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0161)

typedef struct tagMsgGetPVPRankRewardRequest : public MsgBaseRequest
{
	ACE_UINT32 unRewardID;
}MsgGetPVPRankRewardRequest;

typedef struct tagMsgGetPVPRankRewardResponse : public MsgBaseResponse
{
	RewardInfo reward;
}MsgGetPVPRankRewardResponse;

#define MSG_GET_PVP_LEADERBOARD_REQUEST						MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0162)//排行榜
#define MSG_GET_PVP_LEADERBOARD_RESPONSE					MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0163)

typedef struct tagMsgGetPVPLeaderboardRequest : public MsgBaseRequest
{
	ACE_UINT32 unType;
	ACE_UINT32 unCount;
	ACE_UINT32 unPage;//第几页
	ACE_UINT32 list[1];
}MsgGetPVPLeaderboardRequest;

typedef struct tagMsgGetPVPLeaderboardResponse : public MsgBaseResponse
{
	ACE_UINT32 unMaxPage;//总共多少页
	ACE_UINT32 unPage;//第几页
	ACE_UINT32 unCount;
	PVPTeamInfo list[1];
}MsgGetPVPLeaderboardResponse;

#define MSG_START_PVP_REQUEST						MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0164)
#define MSG_START_PVP_RESPONSE						MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0165)

typedef struct tagMsgStartPVPRequest : public MsgBaseRequest
{
	ACE_UINT32 unContinue;
	ACE_UINT32 unFriendID;
}MsgStartPVPRequest;

typedef struct tagMsgStartPVPResponse : public MsgBaseResponse
{
	ACE_UINT32 unStatus;
	ACE_UINT32 pvpType;
	ACE_UINT32 unSeed;
	CharacterInfoExt opponent;
}MsgStartPVPResponse;

#define MSG_UPDATE_PLAYER_RANK_INFO_REQUEST			MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0166)
#define MSG_UPDATE_PLAYER_RANK_INFO_RESPONSE			MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0167)

typedef struct tagMsgUpdatePlayerRankInfoRequest
{
	ACE_UINT32 unCharacterID;
	int dscore;
}MsgUpdatePlayerRankInfoRequest;

typedef struct tagMsgUpdatePlayerRankInfoResponse
{
	ACE_UINT32 unTotalCount;
	PVPRankInfo rankInfo;
}MsgUpdatePlayerRankInfoResponse;

/*
#define MSG_UPDATE_PVP_TEAM_REQUEST						MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0168)
#define MSG_UPDATE_PVP_TEAM_RESPONSE						MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0169)

typedef struct tagMsgUpdatePVPTeamRequest : public MsgBaseRequest
{
	ACE_UINT32 playerList[MAX_PLAYER_SELECTED_COUNT];
	ACE_UINT32 skillList[MAX_PLAYER_SELECTED_COUNT];
}MsgUpdatePVPTeamRequest;

typedef struct tagMsgUpdatePVPTeamResponse : public MsgBaseResponse
{
}MsgUpdatePVPTeamResponse;
*/

#define MSG_GET_PVP_TEAM_INFO_REQUEST						MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x016a)
#define MSG_GET_PVP_TEAM_INFO_RESPONSE						MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x016b)

typedef struct tagMsgGetPVPTeamInfoRequest : public MsgBaseRequest
{
	ACE_UINT32 unCharacterID;
}MsgGetPVPTeamInfoRequest;

typedef struct tagMsgGetPVPTeamInfoResponse : public MsgBaseResponse
{
	PlayerTeamInfo teamInfo;
}MsgGetPVPTeamInfoResponse;

#define MSG_UPDATE_PVP_TEAM_INFO_REQUEST				MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x016c)

typedef struct tagMsgUpdatePVPTeamInfoRequest
{
	ACE_UINT32 unCharacterID;
	PlayerTeamInfo teamInfo;
}MsgUpdatePVPTeamInfoRequest;

#define MSG_PLAYER_PVP_RANK_RESPONSE					MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x016d)

typedef struct tagMsgPlayerPVPRankResponse
{
	ACE_UINT32 unCharacterID;
	ACE_UINT32 unSeasonID;
	ACE_UINT32 unRank;
}MsgPlayerPVPRankResponse;

#define MSG_PLAYER_PVP_ORDER_RESPONSE					MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x016e)

typedef struct tagMsgPlayerPVPOrderResponse
{
	ACE_UINT32 unCharacterID;
	ACE_UINT32 unSeasonID;
	int nOrder;
}MsgPlayerPVPOrderResponse;

#define MSG_MONEY_TREE_INFO_RESPONSE					MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x016f)

typedef struct tagMsgMoneyTreeInfoResponse : public MsgBaseResponse
{
	ACE_UINT32 unLevel;
	ACE_UINT32 unExp;
}MsgMoneyTreeInfoResponse;



#define MSG_GET_MAP_GROUP_REWARD_REQUEST					MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0170)//累积星星奖励
#define MSG_GET_MAP_GROUP_REWARD_RESPONSE					MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0171)

typedef struct tagMsgGetMapGroupRewardRequest : public MsgBaseRequest
{
	ACE_UINT32 unMapGroupID;
	ACE_UINT32 unIdx;
}MsgGetMapGroupRewardRequest;

typedef struct tagMsgGetMapGroupRewardResponse : public MsgBaseResponse
{
	RewardInfo reward;
}MsgGetMapGroupRewardResponse;

#define MSG_BIND_SUCCESS_REQUEST						MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0172)
#define MSG_BIND_SUCCESS_RESPONSE						MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0173)

typedef struct tagMsgBindSuccessRequest
{
	ACE_UINT32 unUserID;
}MsgBindSuccessRequest;

typedef struct tagMsgBindSuccessResponse
{
	int nResult;
}MsgBindSuccessResponse;


#define MSG_WEAPON_FRAGMENT_STEP_UP_REQUEST				MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0174)

typedef struct tagMsgWeaponFragmentStepUpRequest : public MsgBaseRequest
{
	ACE_UINT32 unIdx;
	ACE_UINT32 unPlayerID;
	ACE_UINT32 unMaterialIdxList[1];
}MsgWeaponFragementStepUpRequest;

#define MSG_WEAPON_FRAGMENT_STEP_UP_RESPONSE				MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0174)

typedef struct tagMsgWeaponFragmentStepUpResponse : public MsgBaseResponse
{
}MsgWeaponFragementStepUpResponse;

#define MSG_ADMIN_OP_BUFFER_REQUEST								MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0200)//后台请求带缓存消息

typedef struct tagMsgAdminOpBufferRequest
{
	ACE_UINT32 unOpType;
	ACE_UINT32 unParamCount;
	ACE_UINT32 paramList[MAX_ADMIN_OP_PARAM_COUNT];
	ACE_UINT32 unBufferLen;
	char strBuffer[MAX_ADMIN_OP_BUFFER_LENGTH+1];
}MsgAdminOPBufferRequest;



#define MSG_ADMIN_OP_REQUEST								MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0201)//后台请求消息

typedef struct tagMsgAdminOpRequest
{
	ACE_UINT32 unOpType;//类型
	ACE_UINT32 unCharacterID;//发送给谁，0表示广播
	ACE_UINT32 unParamCount;
	ACE_UINT32 paramList[MAX_ADMIN_OP_PARAM_COUNT];
	ACE_UINT32 unBufferLen;//xxj 2015/04/22  14:42:50 添加带缓存功能
	char strBuffer[MAIL_BODY_LEN + 1];//邮件内容
	char strTitle[MAIL_TITLE_LEN + 1];//标题
}MsgAdminOPRequest;

#define MSG_ADMIN_OP_RESPONSE								MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0202)
typedef struct tagMsgAdminOpResponse
{
	int nResult;
}MsgAdminOpResponse;

#define MSG_GET_ARTICLE_REQUEST								MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0203)

typedef struct tagMsgGetArticleRequest    //added for test jinpan
{
	ACE_UINT32 unArticleId;
	ACE_UINT32 unCount;	
	ACE_UINT32 unSN;
}MsgGetArticleRequest;


#define MSG_SECRET_LIST_REQUEST				MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0206)

typedef struct tagMsgSecretListRequest : public MsgBaseRequest  //added by jinpan for secret request
{
	ACE_UINT32 unType;	
}MsgSecretListRequest;

#define MSG_SECRET_EXPAND_REQUEST				MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0207)//扩充神秘商店的格子
typedef struct tagMsgSecreteExpandRequest : public MsgBaseRequest  //added by jinpan for secret request
{
	ACE_UINT32 unCellCount;//需要扩充到的格子数	
}MsgSecreteExpandRequest;


#define MSG_GET_ARTICLE_RESPONSE								MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0204)

typedef struct tagMsgGetArticleResponse
{
	int nResult;
}MsgGetArticleResponse;


#define MSG_SECRET_LIST_RESPONSE								MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0205)

typedef struct tagMsgSecretListResponse  : public MsgBaseResponse   //added for secretshop jinpan发送给前台的什么商店列表
{
	ACE_UINT32 unCell;     //格子个数
	ACE_UINT32 unRemainingTime;
	ACE_UINT32 unRefreshTimes;
	ACE_UINT32 unPaidRefreshPrice;
	SecretItemInfo list[MAX_SECRET_LIST];   //列表
}MsgSecretListResponse;



#define MSG_SECRET_BUY_REQUEST								MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0208)//神秘商店购买

typedef struct tagMsgSecretBuyRequest : public MsgBaseRequest    //added for secretshop jinpan发送给前台的什么商店列表
{
	ACE_UINT32 unItemId;     //购买物品的id
	ACE_UINT32 unIdx;        //购买的格子数
	
}MsgSecretBuyRequest;

#define MSG_WING_LIST_RESPONSE							MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0X0209)
typedef struct tagMsgWingListResponse : public MsgBaseResponse	//翅膀归属与时限列表
{
	ACE_UINT32 unCount;
	WingItemInfo list[1];
}MsgWingListResponse;


#define MSG_RESET_MAP_REQUEST								MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0231)//重置map次数

typedef struct tagMsgResetMapRequest : public MsgBaseRequest
{
	ACE_UINT32 unMapID;
}MsgResetMapRequest;


#define MSG_RESET_MAP_RESPONSE								MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0233)

typedef struct tagMsgResetMapResponse : public MsgBaseResponse
{
	ACE_UINT32 unMapID;
}MsgResetMapResponse;

#define MSG_GET_MAIL_LIST_REQUEST				MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0234)

typedef struct tagMsgGetMailListRequest : public MsgBaseRequest
{
}MsgGetMailListRequest;

#define MSG_GET_MAIL_LIST_RESPONSE				MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0235)

typedef struct tagMsgGetMailListResponse : public MsgBaseResponse
{
	ACE_UINT32 StartIndex;
	ACE_UINT32 unCount;
	MailInfo list[1];
}MsgGetMailListResponse;

#define MSG_READ_MAIL_REQUEST				MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0236)//邮件提取

typedef struct tagMsgReadMailRequest : public MsgBaseRequest
{
	ACE_UINT32 m_dwMailID;
}MsgReadMailRequest;

#define MSG_READ_MAIL_RESPONSE				MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0237)//邮件提取

typedef struct tagMsgReadMailResponse : public MsgBaseResponse
{
	tagMsgReadMailResponse() : m_dwNewMailID(0), m_dwReadDate(0)
	{ }
	ACE_UINT32 m_dwNewMailID;
	ACE_UINT32 m_dwReadDate;
}MsgReadMailResponse;

#define MSG_GET_REWARD_FROM_MAIL_REQUEST				MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0238)//邮件提取

typedef struct tagMsgGetRewardFromMailRequest : public MsgBaseRequest
{
	ACE_UINT32 m_dwCharacterID;
	ACE_UINT32 m_dwMailID;
	ACE_UINT32 m_dwReadMailRequestSN;
	MailAttachment m_aMailAttachment[MAIL_ATTACHMENT_LEN];
	char m_strSenderName[MAIL_SENDER_NAME_LEN + 1];//发送者
}MsgGetRewardFromMailRequest;

#define MSG_GET_REWARD_FROM_MAIL_RESPONSE				MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0239)

typedef struct tagMsgGetRewardFromMailResponse : public MsgBaseResponse
{
	ACE_UINT32 m_dwCharacterID;
	ACE_UINT32 m_dwMailID;
	ACE_UINT32 m_dwReadMailRequestSN;
}MsgGetRewardFromMailResponse;

#define MSG_GET_SIGN_UP_REWARD_REQUEST				MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x023A)//每日签到

typedef struct tagMsgGetSignUpRewardRequest : public MsgBaseRequest
{

}MsgGetSignUpRewardRequest;

#define MSG_GET_SIGN_UP_REWARD_RESPONSE				MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x023B)

typedef struct tagMsgGetSignUpRewardResponse : public MsgBaseResponse
{

}MsgGetSignUpRewardResponse;

#define MSG_SEND_MONTH_CARD				MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x023C)

typedef struct tagMsgSendMonthCardRequest : public MsgBaseRequest
{
	ACE_UINT32 m_dwCharacterID;
	ACE_UINT32 m_unTime;
}MsgSendMonthCardRequest;

#define MSG_BUY_MONTH_CARD_REQUEST				MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x023D)

typedef struct tagMsgBuyMonthCardRequest : public MsgBaseRequest
{

}MsgBuyMonthCardRequest;

#define MSG_BUY_MONTH_CARD_RESPONSE				MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x023E)

typedef struct tagMsgBuyMonthCardResponse : public MsgBaseResponse
{

}MsgBuyMonthCardResponse;

#define MSG_UPDATE_STAR_COUNT_REQUEST				MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x023F)

typedef struct tagMsgUpdateStarCount
{
	ACE_UINT32 m_dwCharacterID;
	ACE_UINT32 m_dwStarAdded;
}MsgUpdateStarCount;

#define MSG_CONVERT_GIFT_BAG_CODE_REQUEST			MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0240)

typedef struct tagMsgConvertGiftBagCodeRequest : public MsgBaseRequest
{
	char m_strGiftBagCode[MAX_GIFT_BAG_CODE_LENGTH+1];
}MsgConvertGiftBagCodeRequest;

#define MSG_CONVERT_GIFT_BAG_CODE_USER_INFO_REQUEST	MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0241)//礼包码请求

typedef struct tagMsgConvertGiftBagCodeUserInfoRequest : public MsgBaseRequest
{
	//ACE_UINT32 m_dwCharacterID;
	ACE_UINT32 m_dwGiftBagType;
	ACE_UINT32 m_dwCodeType;
	char m_strCode[MAX_GIFT_BAG_CODE_LENGTH+1];
    int m_nResult;
}MsgConvertGiftBagCodeUserInfoRequest;

#define MSG_CONVERT_GIFT_BAG_CODE_RESPONSE			MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0242)

typedef struct tagMsgConvertGiftBagCodeResponse : public MsgBaseResponse
{
	int nResult;
	RewardInfo reward;
}MsgConvertGiftBagCodeResponse;

#define MSG_UPDATE_USER_INFO_GIFT_BAG_CODE	MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0243)

typedef struct tagMsgUpdateUserInfoGiftBagCodeRequest : public MsgBaseRequest
{
	char m_strCode[MAX_GIFT_BAG_CODE_LENGTH+1];
	ACE_UINT32 m_dwUsed;
}MsgUpdateUserInfoGiftBagCodeRequest;


#define MSG_DOUBLE_DROP_LIST_REQUEST	MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0244)//双倍掉落请求

typedef struct tagMsgDoubleDropListRequest : public MsgBaseRequest
{

}MsgDoubleDropListRequest;

#define MSG_DOUBLE_DROP_LIST_RESPONSE			MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0245)

typedef struct tagMsgDoubleDropListResponse : public MsgBaseResponse
{
	int iNextFreshTime;
	int iCount;
	DoubleDropInfo doubleDropList[MAX_DOUBLE_DROP_COUNT];
}MsgDoubleDropListResponse;

#define MSG_TASK_LIST	MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0246)

typedef struct tagMsgTaskList : public MsgBaseResponse //包括上线获得的任务列表和新任务刷新任务列表
{
	int iListType;
	int iTaskNum;
	TaskInfo taskInfo[MAX_CURRENT_TASK_COUNT];
}MsgTaskList;

#define MSG_TASK_OPERATE_REQUEST MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0247)

typedef struct tagMsgTaskOperateRequest : public MsgBaseRequest
{
	ACE_UINT32 iTaskID;
	ACE_UINT32 unOperateType;
}MsgTaskOperateRequest;

#define MSG_TASK_REWARD    MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0248)
typedef struct tagMsgTaskReward : public MsgBaseResponse
{
	RewardInfo reward;
}MsgTaskReward;

#define MSG_DAILY_SINGLE_TASK_REWARD    MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x025A)
typedef struct tagMsgDailySingleTaskReward : public MsgBaseResponse
{
	ACE_UINT32 unActivenessChanged;
	RewardInfo reward;
}MsgDailySingleTaskReward;

#define MSG_GOLDEN_TOUCH_REQUEST    MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x025B)
typedef struct tagMsgGoldenTouchRequest : public MsgBaseRequest
{
}MsgGoldenTouchRequest;

#define MSG_GOLDEN_TOUCH_RESPONSE    MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x025C)
typedef struct tagMsgGoldenTouchResponse : public MsgBaseResponse
{
	UINT32 m_unBellCount;
	ACE_UINT32 m_unCriticalTimes;
}MsgGoldenTouchResponse;

#define MSG_ACTIVENESS_CHANGED    MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0249)
typedef struct tagMsgActivenessChanged : public MsgBaseResponse
{
	ACE_UINT32 unActivenessChanged;
}MsgActivenessChanged;

#define MSG_OBTAINED_ACTIVENESS_REWARD    MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x024A)
typedef struct tagMsgObtainedActivenessReward : public MsgBaseResponse
{
	ACE_UINT32 unObtainedCount;
	ACE_UINT32 obtainedList[MAX_ACTIVENESS_COUNT];
}MsgObtainedActivenessReward;

#define MSG_ADD_NEW_MAP_REQUEST    MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x024B)
typedef struct tagMsgAddNewMapRequest : public MsgBaseRequest
{
	ACE_UINT32 unMapID;
}MsgAddNewMapRequest;

#define MSG_ADD_NEW_MAP_RESPONSE    MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x024C)//解锁地图
typedef struct tagMsgAddNewMapResponse : public MsgBaseResponse
{
	ACE_UINT32 unMapID;
}MsgAddNewMapResponse;

#define MSG_ADD_FRIENDSHIP_MAIL_REQUEST MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x024D)
typedef struct tagMsgAddFriendshipMailRequest : public MsgBaseRequest
{
	ACE_UINT32 m_dwCharacterID;
	ACE_UINT32 m_dwAddFriendship;
	ACE_UINT32 m_dwAssistFlag;
	char m_strName[MAX_CHARACTER_LENGTH+1];
}MsgAddFriendshipMailRequest;

#define MSG_ASSIST_FRIENDSHIP_REQUEST    MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x024E)
typedef struct tagMsgAssistFriendshipRequest : public MsgBaseRequest
{
	ACE_UINT32 characterIDList[MAX_RANDOM_CHARACTER]; 
}MsgAssistFriendshipRequest;

#define MSG_ASSIST_FRIENDSHIP_RESPONSE MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x024F)
typedef struct tagMsgAssistFriendshipResponse : public MsgBaseResponse
{
	ACE_UINT32 unCount;
	AssistFriendship list[1];
}MsgAssistFriendshipResponse;

#define MSG_DELETE_READ_MAIL_REQUEST				MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0250)

typedef struct tagMsgDeleteReadMailRequest : public MsgBaseRequest
{
	ACE_UINT32 m_dwMailID;
}MsgDeleteReadMailRequest;

#define MSG_DELETE_READ_MAIL_RESPONSE				MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0251)

typedef struct tagMsgDeleteReadMailResponse : public MsgBaseResponse
{
}MsgDeleteReadMailResponse;

#define MSG_GET_ALL_MAIL_REWARD_REQUEST				MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0252)

typedef struct tagMsgGetAllMailRewardRequest : public MsgBaseRequest
{
}MsgGetAllMailRewardRequest;

#define MSG_GET_ALL_MAIL_REWARD_RESPONSE				MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0253)

typedef struct tagMsgGetAllMailRewardResponse : public MsgBaseResponse
{
}MsgGetAllMailRewardResponse;

#define MSG_GET_ALL_MAIL_REWARD_TO_MAP_SERVER_REQUEST				MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0254)

typedef struct tagMsgGetAllMailRewardToMapServerRequest : public MsgBaseRequest
{
	ACE_UINT32 m_dwCharacterID;
	ACE_UINT32 m_dwGetAllMailRewardRequestSN;
	ACE_UINT32 m_dwCount;
	MailAttachment m_aMailAttachment[1];
}MsgGetAllMailRewardToMapServerRequest;

#define MSG_GET_ALL_MAIL_REWARD_TO_MAP_SERVER_RESPONSE				MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0255)

typedef struct tagMsgGetAllMailRewardToMapServerResponse : public MsgBaseResponse
{
	ACE_UINT32 m_dwCharacterID;
	ACE_UINT32 m_dwGetAllMailRewardRequestSN;
}MsgGetAllMailRewardToMapServerResponse;

#define MSG_DELETE_ALL_READ_MAIL_REQUEST				MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0256)

typedef struct tagMsgDeleteAllReadMailRequest : public MsgBaseRequest
{
}MsgDeleteAllReadMailRequest;

#define MSG_DELETE_ALL_READ_MAIL_RESPONSE				MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0257)

typedef struct tagMsgDeleteAllReadMailResponse : public MsgBaseResponse
{
}MsgDeleteAllReadMailResponse;

#define MSG_KEEP_ALIVE_REQUEST				MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0258)

typedef struct tagMsgKeepAliveRequest : public MsgBaseRequest
{
}MsgKeepAliveRequest;

#define MSG_KEEP_ALIVE_RESPONSE				MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0259)

typedef struct tagMsgKeepAliveResponse : public MsgBaseResponse
{
	ACE_UINT32 unTime;
	ACE_UINT32 unKey;
}MsgKeepAliveResponse;

/*
ADMIN_OP_GM_ALL = 0,//默认
ADMIN_OP_GM_PUT = 2,//运营消息
ADMIN_OP_GM_USER = 10,//炫耀消息断点
ADMIN_OP_GM_LUCK_EQUIPMENT = 11,//抽奖 获得3星或以上装备
ADMIN_OP_GM_LUCK_PLAYER = 12,//抽奖 获得角色
ADMIN_OP_GM_STEP_EQUIPMENT = 13,//进阶装备
ADMIN_OP_GM_STEP_PLAYER = 14,//进阶角色
ADMIN_OP_GM_COMPOSE =15,//合成装备
ADMIN_OP_GM_PROPS = 16	//道具
*/

#define MSG_GM_REQUEST								MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0260)//GM请求
typedef struct tagMsgAnnouncementRequest : public MsgBaseRequest
{
	ACE_UINT32 unTypeID;//消息类型
}MsgAnnouncementRequest;

//
#define MSG_DB_GM_REQUEST								MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0261)//GM DB请求
typedef struct tagMsgGMRequest : public MsgBaseRequest
{
	ACE_UINT32 unTypeID;//消息类型
	ACE_UINT32 unToID;//请求人
}MsgGMRequest;
#define MSG_DB_GM_RESPONSE								MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0262)////公告牌请求返回
#define MSG_GM_RESPONSE								MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0263)////公告牌请求返回
#define MSG_GM_MAX_LEN 20
typedef struct tagMsgGMRsponse : public MsgBaseResponse
{
	ACE_UINT32 unCount;
	GMInfo info[MSG_GM_MAX_LEN];//gm推送数据
}MsgGMRsponse;

#define MSG_GET_LA_LIST_REQUEST						MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0264)//获取限时活动请求
//MsgBaseRequest
#define MSG_GET_LA_LIST_RESPONST						MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0265)//返回限时活动请求
//#define MAX_LIMITED_ACTIVITY_COUNT 32//限时活动最大数
typedef struct tagMsgGMLimitedActivityList :MsgBaseResponse
{
	ACE_UINT32 m_unCount;
	LimitedActivityInfo m_LAList[MAX_LIMITED_ACTIVITY_COUNT];//限时活动列表
}MsgGMLimitedActivityListResponse;

#define MSG_GET_LA_REWARD_REQUEST						MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0266)//限时活动领取请求
typedef struct tagMsgGMLARewardRequest : public MsgBaseRequest
{
	ACE_UINT32 unLAMID;//限时活动任务列表id
}MsgGMLARewardRequest;
#define MSG_GET_LA_REWARD_RESPONST						MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0267)//限时活动领取返回结果
typedef struct tagMsgGMLARewardResponse :MsgBaseResponse
{
	RewardInfo stReward;//奖励内容
}MsgGMLARewardResponse;

#define MSG_DO_BUYENERGY_REQUEST						MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0268)//买体力
typedef struct tagMsgDoBuyEnergyRequest : public MsgBaseRequest
{
}MsgDoBuyEnergyRequest;

#define MSG_DO_BUYENERGY_RESPONSE						MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0269)//买体力返回

typedef struct tagMsgDoBuyEnergyResponse : public MsgBaseResponse
{
	//int nGold;
	ACE_UINT32 unCurrentCount;//已购买次数
	ACE_UINT32 unEnergy;//买了多少体力
	ACE_UINT32 unMoneyCost;//消耗多少钱
	//RewardInfo reward;
}MsgDoBuyEnergyResponse;

#define MSG_ADMIN_OP_RECHARGE_REQUEST								MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x026a)//充值

#define MSG_DO_ORDER_REQUEST						MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0270)//充值订单请求
typedef struct tagMsgDoOrderRequest : public MsgBaseRequest
{
	ACE_UINT32  product_id;//订单类型
	ACE_UINT32  product_count;//订单类型
}MsgDoOrderRequest;

#define MSG_DO_ORDER_RESPONSE						MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0271)//充值订单请求返回结果
typedef struct tagMsgDoOrderResponse : public MsgBaseResponse
{
	//ACE_UINT32 m_unID;
	char orderID[RECHARGE_ORDERID_LEN+1];//充值头
}MsgDoOrderResponse;

#define MSG_DO_RECHARGE_REQUEST						MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0272)//充值成功检测
typedef struct tagMsgDoRechargeRequest : public MsgBaseResponse
{
	char orderID[RECHARGE_ORDERID_LEN+1];//充值头
}MsgDoRechargeRequest;

#define MSG_DO_RECHARGE_RESPONSE						MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0273)//充值成功返回结果
typedef struct tagMsgDoRechargeResponse : public MsgBaseResponse
{
	char orderID[RECHARGE_ORDERID_LEN+1];//充值头
	ACE_UINT32 deal_time;//订单完成时间
	ACE_UINT32 unRenminbi;//充值金额(人民币)
	ACE_UINT32  unMoney;//充值金卡数量
	ACE_INT32	unProductId;//商品id
	ACE_INT32	unProductCount;//商品数量
	//ACE_UINT32 unChannel;//充值渠道id
	//OrderInfo info;
	ACE_UINT32  unbitField;
	ACE_UINT32  unMoneyEx;//赠送的钱
}MsgDoRechargeResponse;

#define MSG_USER_INFO_ADD_MAIL								MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0274)//添加邮件

#define MSG_DO_PIECE_ROLE_REQUEST				MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0280)//碎片转角色请求
typedef struct tagMsgDoPieceToRoleRequest : public MsgBaseRequest
{
	ACE_UINT32  unItemID;//29开头
}MsgDoPieceToRoleRequest;

#define MSG_DO_PIECE_ROLE_RESPONSE				MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0281)//碎片转角色请求返回
typedef struct tagMsgDoPieceToRoleResponse : public MsgBaseResponse
{
	ACE_UINT32 unPlayerID;//角色id
	ACE_UINT32 unPieceRoleID;//碎片id
	//CostInfoList cost;
}MsgDoPieceToRoleResponse;

#define MSG_DO_UPDATE_LIVEL_REQUEST				MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0282)//更新等级
#define MSG_Update_Bitfield					MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0283)//更新标志
typedef struct tagMsgDoBitFieldRequest : public MsgBaseRequest
{
	ACE_UINT32 unCharactID;
	ACE_UINT32 bitfield;//标记
}MsgDoBitFieldRequest;

#define MSG_DO_GET_RECHARGE_INFO_REQUEST				MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0284)//获取充值或vip信息
#define MSG_DO_GET_RECHARGE_INFO_RESPONSE				MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0285)//获取充值或vip信息
typedef struct tagMsgDoGetRechargeInfoResponse : public MsgBaseResponse
{
	ACE_UINT32 m_bitField;
	ProductList m_Productlist;//已充值列表
	VipInfo info;//vip信息
}MsgDoGetRechargeInfoResponse;

typedef struct tagBitfield
{
	int firstRecharge:1;//首充
	int monthCard:1;//月卡
	int sharedActivites:1;//分享得奖励

	tagBitfield() { memset(this, 0, sizeof(*this)); }
	tagBitfield(ACE_UINT32 value){SetValue(value);}
	void SetValue(ACE_UINT32 value)
	{
		memcpy(this,&value,sizeof(Bitfield));
	}
	ACE_UINT32 GetValue() const
	{
		ACE_UINT32 n = 0;
		memcpy(&n,this,sizeof(Bitfield));
		return n;
	}
}Bitfield;

#define MSG_DO_SHARED_ACTIVITES_REQUEST				MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0286)//分享活动
#define MSG_DO_SHARED_ACTIVITES_RESPONSE				MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0287)//分享活动
typedef struct tagMsgSharedActivitesResponse : public MsgBaseResponse
{
	RewardInfo reward;//分享获得的奖励
}MsgSharedActivitesResponse;

#define MSG_DO_VIP_GIFT_REQUEST				MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0288)//VIP等级礼包
typedef struct tagMsgVipGiftRequest : public MsgBaseRequest
{
	ACE_UINT32 ungiftId;//礼包id
	ACE_UINT32 unvipLevel;//等级
}MsgVipGiftRequest;
#define MSG_DO_VIP_GIFT_RESPONSE				MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0289)//VIP等级礼包
typedef struct tagMsgVipGiftResponse : public MsgBaseResponse
{
	ACE_UINT32 unGiftID;//礼包id
	RewardInfo reward;//获得的奖励
}MsgVipGiftResponse;

#define MSG_DO_DB_SERVER_TIME_HARD				MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x028A)//服务器压力太大，需要休息2秒钟时间
#define ITME_HARD_SLEEP 1000 //睡眠时间
typedef struct tagMsgDoDBTimeHardRequest : public MsgBaseRequest
{
}MsgDoDBTimeHardRequest;

#define MSG_DO_Get_BadgeGaint_REQUEST				MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x028B)//获得加成目标，更新曾益
#define MSG_DO_Get_BadgeGaint_RESPONSE				MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x028C)//获得加成目标，更新曾益
typedef struct tagMsgGetBadgeGaintResponse : public MsgBaseResponse
{
	struct tagGetBadgeGaintInfo
	{
		ACE_UINT32 unGaint[4];
	};

	ACE_UINT32 unCount;
	tagGetBadgeGaintInfo getBadgeGaintinfo[1];//加成详细信息
}MsgGetBadgeGaintResponse;
#define MSG_DO_Up_BadgeGaint_REQUEST				MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x028D)//升级徽章
#define MsgBadgeGaint_MAX 128
typedef struct tagMsgDoUpBadgeGaintRequest : public MsgBaseRequest
{
	ACE_UINT32 unCount;
	ACE_INT32 unIndex[MsgBadgeGaint_MAX];//装备索引
	ACE_UINT32 unIds[MsgBadgeGaint_MAX];//装备id
}MsgDoUpBadgeGaintRequest;
#define MSG_DO_Up_BadgeGaint_RESPONSE				MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x028E)//升级徽章
#define MSG_DO_Up_BadgeGaint_REQUEST1				MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x028F)//升级徽章s
#define MSG_DO_GET_Badge_REQUEST					MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP,0x0290)//获取徽章列表
typedef struct tagMsgGETBadgeRequest : public MsgBaseRequest
{
	ACE_UINT32 unPage;//第几页
	ACE_INT32  isClear;//是否清除首次获得
}MsgGETBadgeRequest;
#define MSG_DO_GET_Badge_RESPONSE					MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP,0x0291)//获取徽章列表
#define BADGE_MAX_PAGE 64
typedef struct tagMsgGETBadgeResponse : public MsgBaseResponse
{
	ACE_UINT32 unMaxPage;//最大页数
	ACE_UINT32 unPage;//第几页了
	ACE_UINT32 unCount;
	BadgeInfo unBadgeInfo[BADGE_MAX_PAGE];//当前页的内容
}MsgGETBadgeResponse;

#define MSG_PROPS_LIST_RESPONSE							MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0292)//道具
typedef struct tagMsgPropsListResponse : public MsgBaseResponse
{
	ACE_UINT32 unCount;
	PropsInfo list[1];
}MsgPropsListResponse;

#define MSG_INVITE_FRIEND_RESPONSE						MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0293)//添加好友 用于返回值判断

//获取用户信息
#define MSG_GET_CHARACTER_INFO_REQUEST				MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0294)
typedef struct tagMsgGetCharacterInfoRequest : public MsgBaseRequest
{
	ACE_UINT32 unCharacterID;//要请求的id
}MsgGetCharacterInfoRequest;

#define MSG_GET_CHARACTER_INFO_RESPONSE				MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0295)
typedef struct tagMsgGetCharacterInfoResponse : public MsgBaseResponse
{
	CharacterInfoExt info;
}MsgGetCharacterInfoResponse;
//-------------------------------------------------------

//-------------------------------------------------------pvp竞技场相关

//获取pvp信息
#define MSG_GET_PVP_INFO_REQUEST				MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0296)//获取pvp信息
#define MSG_GET_PVP_INFO_RESPONSE				MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0297)//获取pvp信息
 typedef struct tagMsgGetPVPInfoResponse : public MsgBaseResponse
 {
	 PVPInfoEx info;
 }MsgGetPVPInfoResponse;
#define MSG_PVP_ENTER_FIGHT_REQUEST				MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0298)//开始战斗请求
 typedef struct tagMsgPVPEnterFightRequestEx : public MsgBaseResponse
 {
	 int isReFreash;//是否刷新
 }MsgPVPEnterFightRequestEx;
 typedef struct tagMsgPVPEnterFightRequest : public MsgBaseRequest
 {
	 int isReFreash;
	 ACE_UINT32 m_characterID;
	 HLInfo quitList[3];//排除列表
 }MsgPVPEnterFightRequest;
#define MSG_PVP_ENTER_FIGHT_RESPONSE				MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x0299)//开始战斗返回
typedef struct tagMsgPVPEnterFightResponse : public MsgBaseResponse
{
	int isReFreash; 
	PVPInfo info;//最新信息
	HLInfoArray _array;//上战列表
}MsgPVPEnterFightResponse;

#define MSG_PVP_GET_ORDER_REQUEST				MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x029A)//获取pvp排名信息
#define MSG_PVP_GET_ORDER_RESPONSE				MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x029B)//获取pvp排名信息
typedef struct tagMsgPVPGetOrderResponse : public MsgBaseResponse
{
	ACE_UINT32 unCount;
	HLUserInfo userInfoArray[MAX_HONOUR_LEVEL_COUNT];//pvp排名
}MsgPVPGetOrderResponse;

#define MSG_PVP_BUY_TIMES_REQUEST				MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x029C)//买pvp竞技场次数
#define MSG_PVP_BUY_TIMES_RESPONSE				MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x029D)//买pvp竞技场次数
typedef struct tagMsgPVPBuyTimesResponse : public MsgBaseResponse
{
	ACE_UINT32 unMoney;
	PVPInfo info;//最新信息
}MsgPVPBuyTimesResponse;

#define MSG_PVP_ENTER_REQUEST				MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x029E)//进入
#define MSG_PVP_ENTER_RESPONSE				MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x029F)//进入
typedef struct tagMsgPVPEnterResponse : public MsgBaseResponse
{
	PVPInfo info;//最新pvp信息
}MsgPVPEnterResponse;

#define MSG_PVP_ACCOUNTS_REQUEST				MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x02A0)//pvp结算请求
typedef struct tagMsgPVPAccountRequest : public MsgBaseRequest
{
	FightRecordInfo info;
	//FightPlayerInfoBase fpInfo;
}MsgPVPAccountRequest;
#define MSG_PVP_ACCOUNTS_RESPONSE				MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x02A1)//pvp结算请求返回
typedef struct tagMsgPVPAccountResponse : public MsgBaseResponse
{
	ACE_INT32 score;//得分
	PVPInfo info;//最新pvp信息
}MsgPVPAccountResponse;

//FightRecordInfo
#define MSG_PVP_GET_FightRecordInfo_REQUEST				MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x02A2)//pvp获取战绩
typedef struct tagMsgPVPFightRecordInfoRequest : public MsgBaseRequest
{
	ACE_UINT32 m_characterID;
}MsgPVPFightRecordInfoRequest;
#define MSG_PVP_GET_FightRecordInfo_RESPONSE				MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x02A3)//pvp获取战绩
typedef struct tagMsgPVPFightRecordInfoResponse : public MsgBaseResponse
{
	PVPInfo pvpinfo;//最新pvp信息
	FightRecordInfoList info;//战绩
}MsgPVPFightRecordInfoResponse;
//--------------------------------------------------------------end

#define MSG_DO_Up_BadgeGaint_REQUESTEX				MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x02A4)//升级徽章 图鉴
typedef struct tagMsgDoUpBadgeGaintRequestEx : public MsgBaseRequest
{
	ACE_UINT32 unCount;
	ACE_UINT32 unIds[MsgBadgeGaint_MAX];//图鉴列表
	ACE_INT32 unIndex[MsgBadgeGaint_MAX];//多少个
}MsgDoUpBadgeGaintRequestEx;
#define MSG_DO_Up_BadgeGaint_RESPONSEEX				MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x02A5)//升级徽章

//------------------闯关最高伤害排行榜 相关
// #define MSG_FIGHT_ROOLE_REQUEST			  MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x02A6)//更新闯关最高伤害排行榜
// 
// #define MSG_FIGHT_ROOLE_LIST_REQUEST			  MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x02A8)//获取闯关最高伤害排行榜
// #define MSG_FIGHT_ROOLE_LIST_RESPONSE		  MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x02A9)//闯关最高伤害排行榜
//------------------------------------------end

//徽章信息相关
#define MSG_Update_badge_info_REQUESTE				MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x02A6)//更新徽章属性
typedef struct tagMsgUpdateBadgeInfoRequest : public MsgBaseRequest
{
	ACE_UINT32 unCharacterID;
	BadgeShuxingS bsInfos;//属性信息
	tagMsgUpdateBadgeInfoRequest()
	{
		ZeroVar(*this);
	}
}MsgUpdateBadgeInfoRequest;
#define MSG_Update_badge_info_RESPONSE				MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x02A76)//更新徽章属性

#define MSG_Get_badge_info_REQUESTE				MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x02A8)//获取徽章属性
typedef struct tagMsgGetBadgeInfoRequest : public MsgBaseRequest
{
	ACE_UINT32 unCharacterID;
}MsgGetBadgeInfoRequest;

#define MSG_Get_badge_info_RESPONSE				MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x02A9)//获取徽章属性
typedef struct tagMsgGetBadgeInfoResponse : public MsgBaseResponse
{
	ACE_UINT32 unCharacterID;
	BadgeShuxingS bsInfos;//属性信息
}MsgGetBadgeInfoResponse;
//----------------------------------------------------end

#define MSG_Get_active_inofo_REQUEST			MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x02AA)//任务刷新//
#define MSG_Get_active_inofo_RESBONSE				MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x02AB)//任务刷新
typedef struct tagMsgGetActiveInfoResponse : public MsgBaseResponse
{
	ACE_UINT32 key;//要显示红点的值
}MsgGetActiveInfoResponse;

#define MSG_Get_POWER_REQUEST				MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x02AC)//更新战力//
typedef struct tagMsgGetPowerRequest : public MsgBaseRequest
{
	ACE_INT32 power;//当前战斗力
}MsgGetPowerRequest;
#define MSG_Get_POWER_RESBONSE				MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0x02AD)
typedef struct tagMsgGetPowerResponse : public MsgBaseResponse
{
	ACE_INT32 power;//当前战斗力
}MsgGetPowerResponse;


#define MSG_INVALID_HOME						MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0xFFFE)

typedef struct tagMsgInvalidHomeResponse : public MsgBaseResponse
{
	
}MsgInvalidHomeResponse;

#define MSG_RESPONSE_END						MAKE_MSG_TYPE(GAME_BASE_PROTOCOL_GROUP, 0xFFFF)

typedef struct tagMsgResponseEnd : public MsgBaseResponse
{

}MsgResponseEnd;



