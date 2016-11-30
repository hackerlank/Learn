#pragma once

#include "ace\ace.h"
#include "ace\Hash_Map_Manager.h"
#include "ace\Null_Mutex.h"
#include <map>
#define ZeroVar(p) ZeroMemory( &p, sizeof( p ) )//不能用于虚拟继承关系

namespace Json 
{
	class Value;
}

#define MAX_ACCOUNT_LENGTH 32
#define MAX_EMAIL_LENGTH 32
#define MAX_MAC_LENGTH 40

#define MAX_ITEM_NAME 50

#define MAX_PLAYER_PER_ACCOUNT 1

#define MAX_CHARACTER_LENGTH 32

#define MAX_GIFT_BAG_CODE_LENGTH 24

#define MAX_GIFT_BAG_CODE_COUNT 1024

#define MAX_GLOBLE_GIFT_BAG_CODE_COUNT (1024 * 1024)

#define MAX_ACCOUNT_BRIEF_INFO_LEN 100

#define MAX_PLAYER_COUNT 64
#define MAX_PLAYER_SELECTED_COUNT 5

#define MAX_EQUIPMENT_COUNT 3

#define MAX_MATERIAL_COUNT 1024		//changed by jinpan for handbook count
#define MAX_HANDBOOK_COUNT 512

#define MAX_INIT_BENEFIT_COUNT 4

#define MAX_SECRET_LIST 64    //added by jinpan for secret cfg

#define MAX_PACKAGE_ITEMS_PER_SEGMENT 32
#define MAX_PACKAGE_SEGMENT_COUNT 7
#define MAX_PACKAGE_LIMIT 200
#define MAX_ITEMS_COUNT (MAX_PACKAGE_LIMIT + 32)

#define MAX_WING_LIST MAX_ITEMS_COUNT

#define CLIENT_SESSION_LEN 10

#define ERROR_CODE_VERSION_NOT_MATCH			-1001
#define ERROR_CODE_NOT_ENOUGH_COIN				-1201
#define ERROR_CODE_NOT_ENOUGH_POWER_POINT		-1301
#define ERROR_CODE_NO_EQUIPMENT					-2901
#define ERROR_CODE_NEED_HIGH_LEVEL				-1601
#define ERROR_CODE_NO_PLAYER					-1201
#define ERROR_CODE_NO_SKILL						-3201
#define ERROR_CODE_NOT_ENOUGH_MONEY				-1501
#define ERROR_CODE_ENERGY_FULL					-1401
#define ERROR_CODE_PACKAGE_FULL					-1901
#define ERROR_CODE_PACKAGE_MAX					-1801
#define ERROR_CODE_VERIFY_BATTLE_FAIL			-2701
#define ERROR_CODE_INVALID_NAME					-3501
#define ERROR_CODE_NOT_ENOUGH_EQUIPMENT			-1701
#define ERROR_CODE_FRIEND_FULL					-2101
#define ERROR_CODE_FRIEND_MAX					-2001
#define ERROR_CODE_FRIEND_NOT_EXIST				-3301
#define ERROR_CODE_NOT_ENOUGH_ENERGY			-2201
#define ERROR_CODE_NEED_FRIEND					-2301
#define ERROR_CODE_PACKAGE_FULL					-1901

/*
#define GET_RES_TYPE(t) ((t >> 24) & 0xff)
#define SET_RES_TYPE(t,i) (((t << 24) & 0xff000000) | (i & 0x00ffffff))
#define GET_RES_CHILD_ID(t) (t & 0x00ffffff)
#define GET_RES_QUALITY(t) ((t >> 16) & 0xff)
#define SET_RES_QUALITY(t, i) (((t << 16) & 0x00ff0000) | (i & 0xff00ffff))
#define GET_RES_BASIC_ID(t) (t & 0xff00ffff)
*/

//#define GET_ITEM_TYPE(t) (t / 100000000)
//#define GET_ITEM_SUB_TYPE(t) ((t / 1000000) % 100)
#define GET_ITEM_ID_INFO(t,start,len) ((t >> (start << 2)) & ((1 << (len << 2)) - 1))
#define GET_ITEM_TYPE(t) (GET_ITEM_ID_INFO(t,6, 2) & 0xff)
#define GET_ITEM_MASK_ID(t,mask) ((t >> (mask << 2)) << (mask << 2))

enum
{
	ITEM_RES_TYPE_EQUIPMENT = 12,////设备，装备
	ITEM_RES_TYPE_DROP = 19,//掉落(抽奖)
	ITEM_RES_TYPE_MONSTER = 11,//怪物
	ITEM_RES_TYPE_LUCK = 13,//抽奖
	ITEM_RES_TYPE_MALL = 17,//商城（商店）
	ITEM_RES_TYPE_MAP = 15,//地图
	ITEM_RES_TYPE_PLAYER = 10,//真人
	ITEM_RES_TYPE_SKILL = 14,//技能
	ITEM_RES_TYPE_IMPROVE = 16,//强化
	ITEM_RES_TYPE_STAGE = 18,//场景
	ITEM_RES_TYPE_FUNCTION = 8,//功能解锁（添加一个新功能）
	ITEM_RES_TYPE_VIP = 5,//vip
	ITEM_RES_TYPE_BENIFIT = 7,//增益
	ITEM_RES_TYPE_UNLOCK = 6,//解锁
	ITEM_RES_TYPE_GIFT = 4,//礼包
	ITEM_RES_TYPE_CURRENCY = 20,//货币
	ITEM_RES_TYPE_ACTIVITY = 21,//活动
	ITEM_RES_TYPE_BEHAVIOR = 22,//各种行为
	ITEM_RES_TYPE_MATERIAL = 23,//材料
	ITEM_RES_TYPE_FORMULA = 24,//合成表
	ITEM_RES_TYPE_BASIC_PROPERTY = 25,//所有权(特权)
	ITEM_RES_TYPE_GROWING = 32,//成长属性
	ITEM_RES_TYPE_EXTRA_SKILL = 33,//额外技能
	ITEM_RES_TYPE_PVP_REWARD = 34,//pvp奖励
	ITEM_RES_TYPE_MONEY_TREE = 35,//树-奖励列表
	ITEM_RES_TYPE_MAP_GROUP = 36,//地图关联
	ITEM_RES_TYPE_DROP_MATERIAL = 38,//xxj 2015/04/20  19:48:54 掉落物品类型（支持个数）  0x26
	ITEM_RES_TYPE_CHANNEL = 39,//渠道 0x27
	ITEM_RES_TYPE_DROP_CURRENCY = 40,//xxj 2015/04/17  14:20:43 掉落货币类型（支持个数）  0x28
	ITEM_RES_TYPE_PIECE_ROLE_COST= 41,//碎片转角色 0x29
	ITEM_RES_TYPE_RECHARGE= 42,//充值 0x2A
	ITEM_RES_TYPE_BADGE = 43,//徽章 0x2B
	ITEM_RES_TYPE_PROPS = 0x1B,	//道具27
	ITEM_RES_TYPE_MAX = 64
};

#define ITEM_RES_TYPE_HANDBOOK_OFFSET 0x80

enum
{
	CONFIG_TYPE_EQUIPMENT = 0,
	CONFIG_TYPE_DROP,
	CONFIG_TYPE_MONSTER,
	CONFIG_TYPE_LUCK,
	CONFIG_TYPE_MALL,
	CONFIG_TYPE_MAP,
	CONFIG_TYPE_PLAYER,
	CONFIG_TYPE_SKILL,
	CONFIG_TYPE_IMPROVE,
	CONFIG_TYPE_STAGE,
	CONFIG_TYPE_LOOT_REPLACE,
	CONFIG_TYPE_FUNCTION,
	CONFIG_TYPE_VIP,
	CONFIG_TYPE_UNLOCK,
	CONFIG_TYPE_BENIFIT,
	CONFIG_TYPE_GIFT,
	CONFIG_TYPE_ACTIVITY,
	CONFIG_TYPE_BEHAVIOR,
	CONFIG_TYPE_MATERIAL,
	CONFIG_TYPE_FORMULA,
	CONFIG_TYPE_BASIC_PROPERTY,
	CONFIG_TYPE_GROWING,
	CONFIG_TYPE_EXTRA_SKILL,
	CONFIG_TYPE_PVP_REWARD,
	CONFIG_TYPE_MONEY_TREE,
	CONFIG_TYPE_MAP_GROUP,
	CONFIG_TYPE_GAME_CONFIG,
	CONFIG_TYPE_SECRET_CONFIG,
	CONFIG_TYPE_PVP100,
	CONFIG_TYPE_TEAM_LEVEL,
	CONFIG_TYPE_GRADE,
	CONFIG_TYPE_SIGN_UP,
	CONFIG_TYPE_GIFT_BAG_CODE,
	CONFIG_TYPE_DOUBLE_DROP,
	CONFIG_TYPE_TASK,
	CONFIG_TYPE_ACTIVE_MISSION,//活动任务
	CONFIG_TYPE_ACTIVE_PRIZE,//活动任务奖品
	CONFIG_TYPE_EQUIP_STEP,
	CONFIG_TYPE_ROBOT_PLAYER,
	CONFIG_TYPE_ROBOT_TEAM,
	CONFIG_TYPE_DROP_MATERIAL,//掉落物品（支持个数）
	CONFIG_TYPE_CHANNEL,//渠道
	CONFIG_TYPE_DROP_CURRENCY,//掉落货币
	CONFIG_TYPE_LIMITED_ACTIVITY,//限时活动时间表
	CONFIG_TYPE_LIMITED_MISSION_ACTIVITY,//限时活动任务表
	CONFIG_TYPE_GOLDEN_TOUCH_PROFIT,
	CONFIG_TYPE_GOLDEN_TOUCH_COST,
	CONFIG_TYPE_BUY_ENERGY_COST,
	CONFIG_TYPE_PIECE_ROLE_COST,//碎片转角色
	CONFIG_TYPE_RECHARGE,		//充值
	CONFIG_TYPE_BADGE,			//徽章
	CONFIG_TYPE_BADGELEVEL,		//徽章升级能量
	CONFIG_TYPE_PROPS,
	CONFIG_TYPE_HONORLEVEL,		//pvp每日排名
	CONFIG_TYPE_HONORRANK,		//pvp赛季排名
	CONFIG_TYPE_HONORCOST,		//pvp赛季排名
};

enum
{
	SERVICE_STATUS_POWER_OFF,
	SERVICE_STATUS_AVAILABLE,
	SERVICE_STATUS_CLOSING,
	SERVICE_STATUS_UNAVAILABLE,
};

#define MAX_SERVICE_INFO_MSG_LEN 2048

/*
enum
{
	PROPERTY_ID_NONE = -1,
	PROPERTY_ID_HP = 0,
	PROPERTY_ID_DAMAGE,
	PROPERTY_ID_INCREASE_COIN,
	PROPERTY_ID_ALL_HP,
	PROPERTY_ID_ALL_DAMAGE,
	PROPERTY_ID_CRITICAL,
	PROPERTY_ID_ARMOR,
	PROPERTY_ID_ALL_CRITICAL,
	PROPERTY_ID_ALL_ARMOR,
	PROPERTY_ID_MAX
};
*/

//(0攻击,1血量,2防御,3暴击,4金币)

//char *GAME_EVENT_PROPERTY_UPDATE = "property update";
extern char *GAME_EVENT_PVE_TEAM_UPDATE;
extern char *GAME_EVENT_PLAYER_INFO_UPDATE;
extern char *GAME_EVENT_MAP_DONE;
//extern char *GAME_EVENT_LOOT_IGNORE_UPDATE;
extern char *GAME_EVENT_LEVEL_UP;
extern char *GAME_EVENT_VIP_LEVEL_UP;
extern char *GAME_EVENT_RESET_BENIFIT;
extern char *GAME_EVENT_MAX_LIMIT_CHANGE;
//extern char *GAME_EVENT_BATTLE_DATA_UPDATE;

enum
{
	PLAYER_PROPERTY_NONE = -1,
	PLAYER_PROPERTY_ATTACK = 0,
	PLAYER_PROPERTY_HP,
	PLAYER_PROPERTY_DEFENSE,
	PLAYER_PROPERTY_CRITICAL,
	PLAYER_PROPERTY_COIN,
	PLAYER_PROPERTY_MAX
};

/*
enum
{
	BATTLE_PROPERTY_ID_HP = 0,
	BATTLE_PROPERTY_ID_DAMAGE,
	BATTLE_PROPERTY_ID_CRITICAL,
	BATTLE_PROPERTY_ID_ARMOR,
	BATTLE_PROPERTY_ID_MAX
};
*/

#define RES_CURRENCY_COIN			0x14010001//贝壳
#define RES_CURRENCY_MONEY			0x14020001
#define RES_CURRENCY_ENERGY			0x14030001//体力
#define RES_CURRENCY_POWERPOINT		0x14040001//合金 晶石
#define RES_CURRENCY_EXP			0x14050001
#define RES_CURRENCY_RECHARGE		0x14060001
#define RES_CURRENCY_HONOUR			0x14070001
#define RES_CURRENCY_PVP_ENERGY		0x14080001
#define RES_CURRENCY_FRIENDSHIP     0x14090001
#define RES_CURRENCY_DYNAMIC_ENERGY 0x140A0001//动感能量


#define REWARD_MAIL_TEMPLATE_ID 0x1A000001	//金币mail
#define MONTH_CARD_MAIL_TEMPLATE_ID 0x1A000002//月卡mail
#define FRIENDSHIP_MAIL_TEMPLATE_ID 0x1A000003//友情值mail
#define FRIENDSHIP_MAIL_PLAYER_ID 0x1A000004//角色mail
#define FRIENDSHIP_MAIL_EQUIPMENT_ID 0x1A000005//装备mail
#define FRIENDSHIP_MAIL_POST_ID 0x1A000006//邮件公告mail
#define FRIENDSHIP_MAIL_FIRST_RECHARGE 0x1A000007//首充礼包mail
#define FRIENDSHIP_MAIL_LIMITED_ACTIVITE 0x1A000008 //充值附件（限时活动）
#define FRIENDSHIP_MAIL_LIMITED_ZHANDOULI 0x1A000009 //新服战力排行榜
#define FRIENDSHIP_MAIL_PVP_DAY 0x1A00000A //PVP 每日奖励
#define FRIENDSHIP_MAIL_PVP_RANK 0x1A00000B //pvp 赛季排行榜奖励
#define FIRST_RECHARGE_REWARD_ID 0x1600000C //首充奖励id
#define FIRST_SHAREAD_ACTIVITE_ID 0x1600000D //分享得奖励


#define POST_MAIL_TITLE_STR "系统消息"

typedef struct tagPropertyComponent
{
	//float fValue;
	//float fScale;
	ACE_UINT32 unValue;
	ACE_UINT32 unScale;
}PropertyComponent;

//#define PLAYER_AMOUNT 6

typedef struct tagBaseItemInfo
{
	ACE_UINT32 unItemID;
}BaseItemInfo;

typedef struct tagMaterialInfo : public BaseItemInfo
{
	ACE_UINT32 unCount;
}MaterialInfo;

typedef struct tagPropsInfo : public BaseItemInfo
{
	ACE_UINT32 unCount;
}PropsInfo;

typedef struct tagCharacterInfo : public BaseItemInfo
{
	//ACE_UINT32 unCharacterID;
	ACE_UINT32 unLevel;
	char name[MAX_CHARACTER_LENGTH + 1];
}CharacterInfo;

typedef struct tagRankData
{
	ACE_UINT32 unRank;
	ACE_UINT32 unHonour;//荣誉
	ACE_UINT32 unPoint;
}RankData;

//装备信息
typedef struct tagEquipmentItemInfo
{	
	ACE_UINT32 unLevel;
	ACE_UINT32 unStep;//阶数 越高越牛逼

	void ToJson(Json::Value &root);
}EquipmentItemInfo;

typedef union tagItemDetailInfo
{
	EquipmentItemInfo equipment;

	void ToJson(Json::Value &root);
}ItemDetailInfo;

typedef struct tagItemInfo
{
	ACE_UINT32 unResID;
	ItemDetailInfo info;

	void ToJson(Json::Value &root);
}ItemInfo;

typedef struct tagItemInfoExt
{
	ACE_UINT32 unCount;
	ItemInfo item;

	void ToJson(Json::Value &root);
}ItemInfoExt;

typedef struct tagPackageCell
{
	ACE_UINT32 unIdx;
	ACE_UINT32 unOldIndex;
	ItemInfoExt item;

	void ToJson(Json::Value &root);
}PackageCell;

/*
typedef struct tagOldPlayerInfo : public BaseItemInfo
{
	ACE_UINT32 unSelected;
	ACE_UINT32 unLevel;
}OldPlayerInfo;
*/

typedef struct tagPlayerInfo : public BaseItemInfo
{
	ACE_UINT32 unLevel;
	ACE_UINT32 unStep;//阶数 越高越牛逼
	ItemInfo weapon;//武器
	ItemInfo armor;//防护道具
	ItemInfo belt;//腰带
	ItemInfo staff;//戒指
	ACE_UINT32 unPlayerSkillID;
	ACE_UINT32 unSoulCount;//碎片个数

	void ToJson(Json::Value &root);
}PlayerInfo;

#define MAX_GLOBAL_DROP_COUNT 16
#define MAX_DROP_ENTITY_PER_LIST 128

typedef struct tagDropEntityInfo
{
	ACE_UINT32 unResID;
	//ACE_UINT32 unType;
	float fRate;
}DropEntityInfo;

typedef struct tagDropGroup
{
	//ACE_UINT32 unGlobalCount;
	//ACE_UINT32 globalDropList[MAX_GLOBAL_DROP_COUNT];
	ACE_UINT32 unGlobalDropID;
	ACE_UINT32 unGlobalCount;
	DropEntityInfo globalList[MAX_GLOBAL_DROP_COUNT];
	ACE_UINT32 unCount;
	DropEntityInfo list[MAX_DROP_ENTITY_PER_LIST];
}DropGroup;

//typedef struct tagDrop



//#define GET_MAP_UNLOCK(t,level) (((t >> ((level-1) * 3)) & 0x7) & 0x1)
//#define SET_MAP_UNLOCK(t,f,level) ((t & (~(0x7 << ((level-1) * 3)))) | ((f & 0x1) << ((level-1) * 3)))
//#define GET_MAP_STAR_LEVEL(t, level) ((((t >> ((level-1) * 3)) & 0x7) >> 1) & 0x3)
//#define SET_MAP_STAR_LEVEL(t,s,level) ((t & (~(0x7 << ((level-1) * 3)))) | (((s & 0x3) << ((level-1) * 3)) << 1))

#define MAX_MAP_COUNT 256
#define MAX_MAP_DIFFRENCE 3
#define MAP_REWARD_COUNT 3

#define MAX_SKILL_COUNT 16

#define MAX_PLAYER_SKILL_COUNT 32

#define TANG_MONK_ID 0x0A300001

//#define MAX_WEAPON_SKILL_COUNT 256

#define MAX_REWARD_ITEM 50

typedef struct tagRewardInfo
{
	ACE_UINT32 unCoin;//贝壳
	ACE_UINT32 unMoney;//金币 金卡
	ACE_UINT32 unExp;//经验值
	ACE_UINT32 unPowerPoint;//合金
	ACE_UINT32 unHonour;//荣誉值
	ACE_UINT32 unRecharge;
	ACE_UINT32 unEnergy;//体力
	ACE_UINT32 unPVPEnergy;//pvp体力
	ACE_UINT32 unFriendship;//友谊点
	ACE_UINT32 unDynamicEnergy;//动感能量
	ACE_UINT32 unCount;//list 长度
	ItemInfoExt list[MAX_REWARD_ITEM];
}RewardInfo;

typedef struct tagDoubleDropInfo
{
	ACE_UINT32 unRawMapID;
	ACE_Byte   byType;
}DoubleDropInfo;

#define MAX_CONFIG_REWARD_COUNT 24

typedef struct tagConfigRewardInfo
{
	ACE_UINT32 unResID;
	ACE_UINT32 unCount;
}ConfigRewardInfo;

typedef struct tagConfigReward
{
	ACE_UINT32 unCoin;
	ACE_UINT32 unMoney;
	ACE_UINT32 unExp;
	ACE_UINT32 unPowerPoint;
	ACE_UINT32 unHonour;
	ACE_UINT32 unRecharge;
	ACE_UINT32 unEnergy;
	ACE_UINT32 unPVPEnergy;
	ACE_UINT32 unFriendship;
	ACE_UINT32 unDynamicEnergy;//动感能量
	ACE_UINT32 unCount;
	ConfigRewardInfo list[MAX_CONFIG_REWARD_COUNT];
}ConfigReward;

typedef struct tagTaskConfig
{
	ACE_UINT32 unID;
	ACE_UINT32 unCompleteCount;//数量需求
	ACE_UINT32 unPremiseTaskCase;
	ACE_UINT32 unNextTaskID;
	ACE_UINT32 unLevelCase;
	ACE_UINT32 unActiveEventType;//条件类型
	ACE_UINT32 unAttachID;//星级需求

	//ACE_UINT32 unExpiredTime;

	ACE_UINT32 unOtherCase; //暂留
	ConfigReward stReward;
}TaskConfig;

typedef struct tagTaskInfo
{
	ACE_UINT32 unTaskID;
	ACE_UINT32 unCurrentProgress;
	ACE_Byte byStatus;
}TaskInfo;

typedef struct tagActivenessInfo
{
	ACE_UINT32 unCompleteCount;
	ACE_UINT32 unLevelCase;
	ACE_UINT32 unActivenessPoints;
	ACE_UINT32 unActiveEventType;
	ACE_UINT32 unAttachID;
	ConfigReward stReward;
}ActivenessInfo;

typedef struct tagGoldenTouchProfit
{
	ACE_UINT32 unBaseProfit;
	ACE_UINT32 unCountProfit;
}GoldenTouchProfit;

typedef struct tagGoldenTouchCost
{
	ACE_UINT32 unTouchCost;
	ACE_UINT32 unCriticalOdds;
}GoldenTouchCost;

//pvp赛季奖励 日奖励
typedef struct tagHonorLevel
{
	ACE_UINT32 unLevel;//段位等级
	ACE_UINT32 unlevelupHonor;//段位所需荣誉
	ACE_UINT32 undayReward;//"日奖励behavior"
	tagHonorLevel()
	{
		ZeroVar(*this);
	}
}HonorLevel;

//pvp赛季奖励 日奖励
typedef struct tagHonorRank
{
	ACE_UINT32 rankid;//段位等级
	ACE_UINT32 unrank_limited;//段位名
	ACE_UINT32 season_reward;//"赛季奖励behavior"
	tagHonorRank()
	{
		ZeroVar(*this);
	}
}HonorRank;

enum
{
	DROP_LOCAL_TYPE = 0,
	DROP_GLOBAL_TYPE
};

#define MAX_INVITE_COUNT 20
#define MAX_FRIEND_COUNT 64
#define MAX_FRIEND_DELETE_COUNT 51

#define MAX_ASSIST_COUNT 256
typedef struct tagAssistInfo
{
	ACE_UINT32 unAssistPlayerID;
	ACE_Byte unAssistType;
}AssistInfo;

typedef struct tagEquipStepConfig
{
	ACE_UINT32 unEquipStep;
	ACE_UINT32 unMaxLevelBonus;
	float fAttributeRate;
}EquipStepConfig;

/*
typedef struct tagCharacterInfoExt : public CharacterInfo
{
	PackageCell equipmentList[MAX_EQUIPMENT_COUNT];
	PropertyComponent propertyList[PROPERTY_ID_MAX];
	ACE_UINT32 unSkillID;
	ACE_UINT32 unVipLevel;
}CharacterInfoExt;
*/


#define MAX_BSINFO_NUM 16
typedef struct tagBadgeShuxing
{
	//0固定值 1百分比
	int gongji_1_0;
	int gongji_1_1;
	int shengming_2_0;
	int shengming_2_1;
	int baoji_3_0;
	int baoji_3_1;
	int fangyu_4_0;
	int fangyu_4_1;
	int beike_5_0;
	int beike_5_1;
	int hejin_6_0;
	int hejin_6_1;
	ACE_UINT32 roleID;

	tagBadgeShuxing()
	{
		ZeroVar(*this);
	}
}BadgeShuxing;

typedef struct tagBadgeShuxingS
{
	ACE_UINT32 unCount;
	BadgeShuxing bsInfo[MAX_BSINFO_NUM];

	tagBadgeShuxingS()
	{
		ZeroVar(*this);
	}
}BadgeShuxingS;


typedef struct tagAssistFriendship
{
	ACE_UINT32 unCharacterID;
	ACE_UINT32 unAddFriendship;
}AssistFriendship;

typedef struct tagPlayerTeamInfo
{
	ItemInfo staff;
	ACE_UINT32 unCount;
	ACE_UINT32 unPoint;
	PlayerInfo playerList[MAX_PLAYER_SELECTED_COUNT];
	ACE_UINT32 skillList[MAX_PLAYER_SELECTED_COUNT];
	ACE_UINT32 playerSkillList[MAX_PLAYER_SELECTED_COUNT];
	ACE_UINT32 unStarCount;
	void ToJson(Json::Value &root);
}PlayerTeamInfo;

typedef struct tagCharacterInfoExt : public CharacterInfo
{
	tagCharacterInfoExt()
	{
		ZeroVar(*this);
	}
	//PackageCell equipmentList[MAX_EQUIPMENT_COUNT];
	//PropertyComponent propertyList[PROPERTY_ID_MAX];
	//PlayerTeamInfo teamInfo;
	PlayerTeamInfo pveTeam;
	PlayerTeamInfo pvpTeam;
	ACE_UINT32 unVipLevel;
	BadgeShuxingS badgeShuxing;
	void ToJson(Json::Value &root);
}CharacterInfoExt;

typedef struct tagFriendInfo : public CharacterInfoExt
{
	ACE_UINT32 unCooldown;
	ACE_UINT32 unStartTime;
	ACE_UINT32 unLastInteractionTime;
	ACE_UINT32 unInteractionFlag;
	//ACE_UINT32 unAddFriendshipFlag;
}FriendInfo;


typedef struct tagDBFriendInfo 
{
	ACE_UINT32 unCharacterID;
	ACE_UINT32 unCooldown;
	ACE_UINT32 unStartTime;
	ACE_UINT32 unLastInteractionTime;
	ACE_UINT32 unInteractionFlag;
	//ACE_UINT32 unAddFriendshipFlag;
}DBFriendInfo;

typedef struct tagPVPTeamInfo : public CharacterInfo
{
	ACE_UINT32 unScore;
	ACE_UINT32 unWin;
	ACE_UINT32 unAll;
	ACE_UINT32 unRankID;
	PlayerTeamInfo teamInfo;
}PVPTeamInfo;

#define MAIL_SENDER_NAME_LEN 32//发送者名字长度
#define MAIL_TITLE_LEN 24//标题长度
#define MAIL_BODY_LEN 255//内容长度
#define MAIL_ATTACHMENT_LEN 5//附件长度
#define MAIL_FLAG_HAVE_READ 0x1//已读
#define MAIL_FLAG_PUBLIC_MAIL 0x2//公共邮件
#define MAIL_FLAG_HAVE_DELETED 0x4//已删除
#define MAIL_TIME_OUT (7 * 24 * 3600) //邮件超时时间

typedef struct tagMailAttachment
{
	tagMailAttachment() : m_dwItemID(0), m_dwItemCount(0)
	{
	}
	ACE_UINT32 m_dwItemID;
	ACE_UINT32 m_dwItemCount;
}MailAttachment;

typedef struct tagMailInfo
{
	tagMailInfo() : m_dwID(0), m_dwIDinTable(0), m_dwCharacterID(0), m_dwFlag(0), m_dwTimeoutDate(0), m_dwReadDate(0)
	{
		memset(m_strSenderName, 0, sizeof(char) *(MAIL_SENDER_NAME_LEN + 1));
		memset(m_strTitle, 0, sizeof(char) * (MAIL_TITLE_LEN + 1));
		memset(m_strBody, 0, sizeof(char) * (MAIL_BODY_LEN + 1));
		memset(m_aMailAttachment, 0, sizeof(MailAttachment) * MAIL_ATTACHMENT_LEN);
	}
	ACE_UINT32 m_dwID;
	ACE_UINT32 m_dwIDinTable;//特定邮件种类标记
	ACE_UINT32 m_dwCharacterID; //给谁发，0表示广播
	ACE_UINT32 m_dwFlag;
	ACE_UINT32 m_dwTimeoutDate;//发送时间
	ACE_UINT32 m_dwReadDate;	//阅读时间
	MailAttachment m_aMailAttachment[MAIL_ATTACHMENT_LEN];//附件
	char m_strSenderName[MAIL_SENDER_NAME_LEN + 1];//发送者
	char m_strTitle[MAIL_TITLE_LEN + 1];//标题
	char m_strBody[MAIL_BODY_LEN + 1];//内容
	void SetSenderName(const wchar_t * str)
	{
		ZeroVar(m_strSenderName);
		char rstrUtf8[MAIL_SENDER_NAME_LEN + 1];
		ZeroVar(rstrUtf8);
		int dwLen = -1;
		WideCharToMultiByte(CP_UTF8, 0, str, dwLen, &rstrUtf8[0], MAIL_SENDER_NAME_LEN, NULL, NULL);
		memcpy(m_strSenderName,rstrUtf8,MAIL_SENDER_NAME_LEN + 1);
	}
}MailInfo;

typedef struct tagPVPBasicInfo
{
	ACE_UINT32 playerList[MAX_PLAYER_SELECTED_COUNT];
	ACE_UINT32 playerSkillList[MAX_PLAYER_SELECTED_COUNT];
	//ACE_UINT32 honour;
}PVPBasicInfo;

typedef struct tagPVPRankInfo
{
	ACE_UINT32 unSeasonID;
	ACE_UINT32 unScore;
	ACE_UINT32 unAll;
	ACE_UINT32 unWin;
	int nOrder;
	ACE_UINT32 unRank;
	ACE_UINT32 unRewardSeasonID;
	ACE_UINT32 unRewardID;
	//ACE_UINT32 unRewardID;
}PVPRankInfo;

typedef struct tagDBPVPRankInfo
{
	ACE_UINT32 unRewardSeasonID;
	ACE_UINT32 unRewardID;
}DBPVPRankInfo;

/*
typedef struct tagTeamPointSnapInfo
{
	ACE_UINT32 unPoint;
	PlayerTeamInfo teamInfo;
}TeamPointSnapInfo;

typedef struct tagLeaderboardCell
{
	ACE_UINT32 *pScore;
	int unOrder;
}LeaderboardCell;
*/

enum
{
	PLAYER_POOL_TYPE_LEVEL = 0,
	PLAYER_POOL_TYPE_TEAM_RANK,
	PLAYER_POOL_TYPE_PVP_RANK,
	PLAYER_POOL_TYPE_MAX
};

typedef struct tagPlayerPoolPosition
{
	int nPoolID;
	int nIndex;
}PlayerPoolPosition;

typedef struct tagPublicPlayerInfo
{
	tagPublicPlayerInfo()
	{
		ZeroVar(*this);
	}
	CharacterInfoExt characterInfo;

	//PVPBasicInfo pvpBasicInfo;
	PVPRankInfo pvpRankInfo;
	//PlayerTeamInfo pvpTeamInfo;
	PlayerTeamInfo highestTeamInfo;

	PlayerPoolPosition poolPosition[PLAYER_POOL_TYPE_MAX];

	ACE_UINT32 unPVPOrderUpdateTime;

}PublicPlayerInfo;

/*
typedef struct tagTeamRankCell
{
	ACE_UINT32 unCharacterID;
	ACE_UINT32 unPoint;
	ACE_UINT32 unUpdateTime;
	PlayerTeamInfo teamInfo;
}TeamRankCell;

typedef struct tagPVPSeasonRankCell
{
	ACE_UINT32 unCharacterID;
	ACE_UINT32 unScore;
	ACE_UINT32 unAll;
	ACE_UINT32 unWin;
	ACE_UINT32 unUpdateTime;
}PVPSeasonRankCell;
*/

#define MAX_PVP_COMMAND_DATA_SIZE 4096

typedef struct tagPVPCommand
{
	ACE_UINT32 unRound;
	ACE_UINT32 unTurn;
	ACE_UINT32 unSkillIndex;
}PVPCommand;

typedef struct tagPVPOpponentInfo
{
	ACE_UINT32 unSeasonID;
	ACE_UINT32 unStartTime;
	ACE_UINT32 pvpType;
	ACE_UINT32 unSeed;
	CharacterInfoExt opponent;
}PVPOpponentInfo;

enum
{
	PVP_TYPE_SEASON = 0,
	PVP_TYPE_FRIEND
};

enum
{
	PVP_LEADERBOARD_TEAM_POINT = 0,//战斗力 排行榜
	PVP_LEADERBOARD_SCORE,//赛季 排行榜
	PVP_LEADERBOARD_FRIEND,//好友 排行榜
	PVP_LEADERBOARD_STAR_COUNT//星级 排行榜
};

enum
{
	PVP_STATUS_NORMAL = 0,
	PVP_STATUS_SEASON_END
};

#define PVP_WIN_SCORE 5
#define PVP_LOSE_SCORE 2
#define PVP_WIN_HONOUR 4
#define PVP_LOSE_HONOUR 2
#define PVP_HONOUR_FRIEND 1

#define MAX_RANDOM_CHARACTER 20
#define MAX_RANDOM_FRIEND 10

#define MAX_DOUBLE_DROP_COUNT 20

#define MAX_TOTAL_TASK_COUNT 64
#define MAX_CURRENT_TASK_COUNT 16
#define MAX_ACTIVENESS_COUNT 10
#define MAX_LIMITED_ACTIVITY_COUNT 32//限时活动最大数

/*
#define MAX_ITEM_LIST_PER_PLAYER 8
#define MAX_MONSTER_PER_SECTION 32
#define MAX_ITEM_PER_SECTION 32


typedef struct tagBattleEntity
{
	int hp;
}BattleEntity;

typedef struct tagBattlePlayerInfo : public tagBattleEntity
{
	ACE_UINT32 itemList[MAX_ITEM_LIST_PER_PLAYER];
}BattlePlayerInfo;

typedef struct tagBattleMonsterInfo : public tagBattleEntity
{
}BattleMonsterInfo;

typedef struct tagBattleItemInfo
{
	int isDestroyed;
}BattleItemInfo;

typedef struct tagBattleEntityInfo
{
	BattlePlayerInfo playerList[MAX_PLAYER_SELECTED_COUNT + 2];
	BattleMonsterInfo monsterList[MAX_MONSTER_PER_SECTION];
	BattleItemInfo itemList[MAX_ITEM_PER_SECTION];
}BattleEntityInfo;

typedef struct tagMapBattleInfo
{
	int isValid;
	int nCurrentSection;
	int nLauchCount;
	int nBellCount;
	int nRandSeed;
	//int unPlayerCount;
	//ACE_UINT32 playerList[MAX_PLAYER_SELECTED_COUNT];
	BattleEntityInfo entityInfo;
}MapBattleInfo;
*/

typedef struct tagMapInstanceInfo
{
	ACE_UINT32 unMapID;
	ACE_UINT32 unSpecialBossID;
	ACE_UINT32 unItemCount;
	int nGlobalMapEventType;
	CharacterInfoExt friendInfo;
	//MapBattleInfo battleInfo;
	void ToJson(Json::Value &root);
}MapInstanceInfo;

/*
typedef struct tagBattleSnapInfo
{
	ACE_UINT32 unStep;
	ACE_UINT32 rebornFlag;
	BattleEntityInfo entityInfo;
}BattleSnapInfo;
*/

typedef struct tagMapFlagInfo
{
	ACE_UINT32 unMapID;
	ACE_UINT32 unFlag;
	ACE_UINT32 unFlag2;	//4位标识一个难度的重置次数
}MapFlagInfo;


typedef struct tagWeaponSkillInfo : public BaseItemInfo
{
	ACE_UINT32 unLevel;
}WeaponSkillInfo;

/*
enum
{
	PACKAGE_TYPE_PACKAGE = 0,
	PACKAGE_TYPE_PLAYER,
	PACKAGE_TYPE_EQUIPMENT,
};
*/

#define MAX_EQUIPMENT_LEVEL 30
#define MAX_SKILL_LEVEL 60

/*
typedef struct tagTeamMember
{
	ACE_UINT32 unItemID;
	PropertyComponent propertyList[PLAYER_PROPERTY_MAX];
	ACE_UINT32 unSkillID;
}TeamMember;
*/

/*
typedef struct tagPropertyInfo
{
	ACE_UINT32 unPropertyID;
	ACE_UINT32 unType;
	float fValue;
}PropertyInfo;

#define MAX_PROPERTY_COUNT 8

typedef struct tagPropertyList
{
	ACE_UINT32 unCount;
	PropertyInfo list[MAX_PROPERTY_COUNT];
}PropertyList;
*/

#define MAX_BENEFIT_COUNT 8

typedef struct tagBenefitInfo
{
	ACE_UINT32 unBenefitID;
	ACE_UINT32 unType;
	ACE_UINT32 unValue;
	//float fValue;
}BenefitInfo;

typedef struct tagBenefitList
{
	ACE_UINT32 unCount;
	BenefitInfo list[MAX_BENEFIT_COUNT];
}BenefitList;

#define MAX_MAIN_CHARACTER_ID 5

typedef struct tagCareerInfo
{
	ACE_UINT32 unCharacterID;
	ACE_UINT32 unEquipmentTypeID;
	ACE_UINT32 unSkillTypeID;
	ACE_UINT32 unRequiredPlayerID;
}CareerInfo;

enum
{
	EQUIPMENT_TYPE_WEAPON = 0x01,
	EQUIPMENT_TYPE_ARMOR = 0x02,
	EQUIPMENT_TYPE_STAFF = 0x03,
	EQUIPMENT_TYPE_WING = 0x04,
	EQUIPMENT_TYPE_BELT = 0x05,

	EQUIPMENT_TYPE_MAX = EQUIPMENT_TYPE_BELT,
};

enum
{
	LEVEL_UP_TYPE_EQUIPMENT = 0,//装备升级
	LEVEL_UP_TYPE_EQUIPMENT_STEP,//升阶
	LEVEL_UP_TYPE_PLAYER//伙伴 玩家升级
};

#define MAX_EQUIPMENT_STEP 3
#define MAX_EQUIPMENT_LEVEL_PER_STEP 5

enum
{
	DELETE_ITEM_TYPE_SOLD = 0,//卖出去
	DELETE_ITEM_TYPE_MELT//分解 融化
};

enum
{
	GLOBAL_MAP_EVENT_NONE = -1,
	GLOBAL_MAP_EVENT_COIN_DOUBLE = 0,
	GLOBAL_MAP_EVENT_DROP_DOUBLE,
	GLOBAL_MAP_EVENT_MAX
};

//typedef struct 
#define GLOBAL_MAP_EVENT_COOLDOWN (2 * 60 * 60)

typedef struct tagPackageExpandInfo
{
	ACE_UINT32 unMin;
	ACE_UINT32 unMax;
	ACE_UINT32 unCountPerTime;
	ACE_UINT32 unGold;
}PackageExpandInfo;

enum
{
	GOLD_BUY_TYPE_ENERGY = 0,
	GOLD_BUY_TYPE_PACKAGE,
	GOLD_BUY_TYPE_FRIEND,
	GOLD_BUY_TYPE_PVP_ENERGY
};

enum
{
	STAGE_ITEM_TYPE_NONE = 0,
	STAGE_ITEM_TYPE_HP,
	STAGE_ITEM_TYPE_BELL,
	STAGE_ITEM_TYPE_BUFF
};

#define MAX_VIP_BENIFIT_COUNT 32

#define MAX_FUNCTION_COUNT 32

#define MAX_VIP_LEVEL 32

#define MAX_LOGIN_BONUS_COUNT 7

enum
{
	UNLOCK_CONDITION_TYPE_LEVEL_UP = 0,
	UNLOCK_CONDITION_TYPE_STAGE_DONE,
	UNLOCK_CONDITION_TYPE_VIP_UP,
	UNLOCK_CONDITION_TYPE_MAX
};


//1登陆给元宝，2免费复活，3背包上限，4好友上限，5体力上限，6卖出增加钱，7熔炼增加晶石，8体力时间缩减，9首胜奖励增加，10抽奖折扣，11充值翻倍
enum 
{
	BENEFIT_TYPE_LOGIN_GOLD = 1,
	BENEFIT_TYPE_REBORN,
	BENEFIT_TYPE_PACKAGE_LIMIT,
	BENEFIT_TYPE_FRIEND_LIMIT,
	BENEFIT_TYPE_ENERGY_LIMIT,
	BENEFIT_TYPE_SOLD,
	BENEFIT_TYPE_MELT,
	BENEFIT_TYPE_ENERGY_RESTORE,
	BENEFIT_TYPE_MAP_REWARD,
	BENEFIT_TYPE_LUCK_COST,
	BENEFIT_TYPE_FIRST_RECHARGE,
	BENEFIT_TYPE_LOGIN_COIN,
	BENEFIT_TYPE_LOGIN_POWER_POINT,
	BENEFIT_TYPE_MAX
};

#define FUNCTION_EXCHANGE_EQUIPMENT		800000002
#define FUNCTION_IMPROVE_PLAYER			800000006
#define FUNCTION_IMPROVE_EQUIPMENT		800000007
#define FUNCTION_IMPROVE_SKILL			800000008
#define FUNCTION_STEPUP_EQUIPMENT		800000009
#define FUNCTION_GET_LUCK				800000010
#define FUNCTION_PVP					800000019


typedef struct tagGiftInfo
{
	ACE_UINT32 unGiftID;
	ACE_UINT32 unTimeStamp;
}GiftInfo;

#define MAX_GIFT_COUNT 32

enum
{
	USE_ITEM_TYPE_GIFT = 0,
	USE_ITEM_TYPE_PROPS = 1
};

typedef struct tagBattleUnitInfo
{
	int oldHP;
	int newHP;
	int damage;
	int heal;
	ACE_UINT32 itemList[8];
}BattleUnitInfo;

#define MAX_COMMAND_BUFF_SIZE 64

typedef struct tagCooldownInstanceInfo : public BaseItemInfo
{
	ACE_UINT32 unCount;
	ACE_UINT32 unLastUpdateTime;
}CooldownInstanceInfo;

#define MAX_COOLDOWN_INFO 64

#define MAX_ADMIN_OP_PARAM_COUNT 8

#define MAX_ADMIN_OP_BUFFER_LENGTH 128

#define MAX_ADMIN_OP_BUFFER_ANNOUNCEMENT_LENGTH 256//公告长度

//后台命令
enum
{
	ADMIN_OP_TYPE_GET_BASIC_INFO = 0,
	ADMIN_OP_TYPE_GET_PLAYER_LIST,
	ADMIN_OP_TYPE_GET_EQUIPMENT_LIST,
	ADMIN_OP_TYPE_GET_PACKAGE,
	ADMIN_OP_TYPE_GET_LOCK_FUNCTION_LIST,
	ADMIN_OP_TYPE_GET_SKILL_LIST,
	ADMIN_OP_TYPE_SET_LEVEL,
	ADMIN_OP_TYPE_SET_COIN,
	ADMIN_OP_TYPE_ADD_COIN,//增加贝壳
	ADMIN_OP_TYPE_SET_MONEY,
	ADMIN_OP_TYPE_ADD_MONEY,//增加金币
	ADMIN_OP_TYPE_SET_POWER_POINT,
	ADMIN_OP_TYPE_ADD_EQUIPMENT,//增加装备
	ADMIN_OP_TYPE_DELETE_EQUIPMENT,
	ADMIN_OP_TYPE_EDIT_EQUIPMENT,
	ADMIN_OP_TYPE_ADD_PLAYER,//增加角色
	ADMIN_OP_TYPE_DELETE_PLAYER,
	ADMIN_OP_TYPE_EDIT_PLAYER,
	ADMIN_OP_TYPE_SET_SKILL_LEVEL,
	ADMIN_OP_TYPE_UNLOCK,
	ADMIN_OP_TYPE_DISABLE_ACCOUNT,//封停
	ADMIN_OP_TYPE_ENABLE_ACCOUNT,//解封
	ADMIN_OP_TYPE_ADD_GIFT_BAG_CODE,//礼包码
	ADMIN_OP_TYPE_STATISTICS,//统计
	ADMIN_OP_TYPE_MAIL_POST,//邮件公告
	ADMIN_OP_TYPE_GM_POST,//GM工具GM推送
};


#define  MAX_GM_USER_COUNT 10//最大10个
enum
{
	ADMIN_OP_GM_ALL = 0,//默认
	ADMIN_OP_GM_PUT = 2,//运营消息

	ADMIN_OP_GM_USER = 10,//炫耀消息断点

	ADMIN_OP_GM_LUCK_EQUIPMENT = 11,//抽奖 获得3星或以上装备
	ADMIN_OP_GM_LUCK_PLAYER = 12,//抽奖 获得角色
	ADMIN_OP_GM_STEP_EQUIPMENT = 13,//进阶装备
	ADMIN_OP_GM_STEP_PLAYER = 14,//进阶角色
	ADMIN_OP_GM_COMPOSE =15,//合成装备
	ADMIN_OP_GM_PROPS = 16	//道具
};

/*
#define GAME_COIN_ID	0x14010001
#define GAME_GOLD_ID	0x14020001
#define GAME_ENERGY_ID	0x14030001
#define GAME_POWER_POINT_ID	0x14040001
#define GAME_EXP_ID	0x14050001
#define GAME_RECHARGE_ID	0x14060001
#define GAME_HONOUR_ID	0x14070001
*/

#define MAX_COST_TYPE_COUNT 7

typedef struct tagCostInfo
{
	ACE_UINT32 unID;
	int cost;
}CostInfo;

typedef struct tagCostInfoList
{
	ACE_UINT32 unCount;
	CostInfo list[MAX_COST_TYPE_COUNT];
}CostInfoList;

typedef struct tagCooldownInfo
{
	ACE_UINT32 unCD;
	ACE_UINT32 unPrecision;
	ACE_UINT32 unCountLimit;
	ACE_UINT32 unOffset;
}CooldownInfo;



#define MAX_RELATED_ID_PER_ACTIVITY 8

/*
typedef struct tagLimitInfo : public BaseItemInfo
{
	ACE_UINT32 unCountLimit;
	ACE_UINT32 unActivityLimit;
}LimitInfo;
*/


#define COMMON_MAP_STAGE_COUNT 5
#define COMMON_MAP_SUB_STAGE_COUNT 7


#define MAX_SECURITY_KEY_COUNT 80000
#define SECURITY_KEY_LENGTH 8

enum
{
	BROADCAST_MESSAGE_TYPE_GET_EQUIPMENT = 0,
	BROADCAST_MESSAGE_TYPE_STEP_UP,
	BROADCAST_MESSAGE_TYPE_LEVEL_UP,
	BROADCAST_MESSAGE_TYPE_VIP,
	BROADCAST_MESSAGE_TYPE_GET_PLAYER
};

typedef struct tagBroadcastMessage
{
	char name[MAX_CHARACTER_LENGTH + 1];
	ACE_UINT32 unType;
	ACE_UINT32 unItemID;
	ACE_UINT32 unParam;
// 	ACE_UINT32 unCoin;//贝壳
// 	ACE_UINT32 unPowerPoint;//合金
}BroadcastMessage;

#define MAX_BROADCAST_MESSAGE_COUNT 10


//#define BEHAVIOUR_BUY_ENERGY 0x16000001
#define BEHAVIOR_MONEY_TREE_WATERING 0x16100019
#define BEHAVIOR_MONEY_TREE_REWARD 0x16100020
#define BEHAVIOR_EAT_RSG_REWARD 0x16000022
#define BEHAVIOR_EVERYDAY_REWARD 0x16000023 //每日登陆礼包

#define SECRET_PAID_REFRESH_TIMES_COUNT_UPPER_BOUND 15    //不要改这个值，因为涉及到按位保存的数据存储与解析

enum
{
	TYPE_PVE = 0,
	TYPE_PVP
};

enum SECRET_REFRESH_TYPE
{
	SECRET_REFRESH_FREE = 0,
	SECRET_REFRESH_1,
	SECRET_REFRESH_2,
	SECRET_REFRESH_3,
	SECRET_REFRESH_4
};

typedef struct tagSecretItem
{
	ACE_UINT32 unId;
	ACE_UINT32 unCount;
}SecretItem;   //下面两行特殊配置

typedef struct tagSecretCfg   //jinpan  secretshop
{
	ACE_UINT32 unCell;					//所开格子的个数
	ACE_UINT32 certainList[MAX_SECRET_LIST];//必出列表
	ACE_UINT32 unCertainCount;				//必出物品的个数
	
	ACE_UINT32 unOtherItems[MAX_SECRET_LIST];  //其他物品随机的总表
	ACE_UINT32 unOtherCount;
}SecretCfg;


typedef struct tagSecret{
	SecretCfg secretCfg[MAX_SECRET_LIST];
	ACE_UINT32 unCount;
	ACE_UINT32 unRefreshSec;
	ACE_UINT32 unMaxCell;

	SecretItem cellPrice[MAX_SECRET_LIST];
	SecretItem specialAmount[MAX_SECRET_LIST];
	SecretItem moenyRefresh;//低级元宝刷新 type 1
	SecretItem itemRefresh;//低级材料刷新 type 2
	SecretItem higher_moenyRefresh;//高级金币刷新 type3
	SecretItem higher_itemRefresh;//高级材料刷新	type 4

	ACE_UINT32  unHigher_moneyRefresh_increase;
	ACE_UINT32  unHigher_moneyRefresh_increaseUpperBound;
	
}Secret;

typedef struct tagSecretItemInfo : MaterialInfo{
	ACE_UINT32 bBuy;//是否已经购买 true表示已经被买了，false 表示未被购买
}SecretItemInfo;
typedef struct tagsSecretInfo{
	SecretItemInfo m_list[MAX_SECRET_LIST];  //物品的id和个数
	ACE_UINT32 m_unCellCount;//当前拥有格子数
	ACE_UINT32 m_refreshTimes;//刷新次数
	ACE_UINT32 m_unLastRefreshTime;//上次刷新时间

}SecretInfo;

enum GIFT_BAG_CODE_TYPE
{
	GIFT_BAG_CODE_ONCE = 0,
	GIFT_BAG_CODE_EVERYONE = 1,
	GIFT_BAG_CODE_GM = 2,

	GIFT_BAG_CODE_INVALID = 3,
};

typedef struct tagAdminGiftBagCode
{
	char strCode[MAX_GIFT_BAG_CODE_LENGTH+1];
	ACE_UINT32 unGiftBagType;  //礼包类型，每种类型礼包每人只能领一次
	ACE_UINT32 unCodeType;     //码类型，0:本码只能被一个人，1，本码能被所有人用， 2，测试用，无限制不记表
	//ACE_Byte   byUsed;         //是否曾经被使用过，只有类型0，会用该数据
}AdminGiftBagCode;

typedef struct tagGiftBagCodeInfo
{
	ACE_UINT32 unGiftBagType;  //礼包类型，每种类型礼包每人只能领一次
	ACE_UINT32 unCodeType;     //码类型，0:本码只能被一个人，1，本码能被所有人用， 2，测试用，无限制不记表
	ACE_Byte   byUsed;         //是否曾经被使用过，只有类型0，会用该数据
}GiftBagCodeInfo;

//xxj 2015/05/06 15:01:27 
typedef struct tagGMInfo
{
	ACE_UINT32 unFromID;  //推送原地址
	ACE_UINT32 unToID;  //推送目标地址
	ACE_UINT32 unType;			//类型
	ACE_UINT32 unGoodID;		//物品id
	ACE_UINT32 unLevel;			//等级
	//ACE_UINT32 unBufferLen;
	char fromName[MAX_CHARACTER_LENGTH + 1];  //推送源地址名字
	char strBuffer[MAIL_BODY_LEN + 1];//内容
}GMInfo;

typedef struct tagGiftBagCodeReward
{
	time_t tExpiredTime;
	ACE_UINT32 unGiftBagID; 
	//ConfigReward oReward;//如果一个礼包ID对应一个礼包奖励，那这个就没必要存储了
}GiftBagCodeReward;

//----------------wangwei
typedef struct tagWingItemInfo : public BaseItemInfo{
	ACE_UINT32 unPlayerId;		//角色id，未装备为0
	ACE_UINT32 unIdx;		//背包index，装备后为0，需注意修改背包index时，这里要随动
	ACE_UINT32 unExpires;		//剩余时间
}WingItemInfo;
typedef struct tagWingInfo{
	WingItemInfo m_list[MAX_WING_LIST];
	ACE_UINT32 m_count;
}WingInfo;
//----------------------

//#define MAX_SECRET_CELL 10  //最大格子数

typedef struct tagSkillBook{
	ACE_UINT32 unId;
	ACE_UINT32 unCount;
}SkillBook;



#define MAX_TEAM_RANK_100_COUNT 1000  //added by jinpan for 100pvp
#define MAX_PVP100_STAGE_COUNT 10   //最大分成20组
#define MAX_PVP100_GROUP_COUNT 100 //每组内的最大人数
#define MAX_PVP100_CFG  24  //百人斩最多分24档

typedef struct tagPvp100{
	ACE_UINT32 unStart;  //当前档次开始时の战斗力
	ACE_UINT32 unEnd;	 //当前档次结束时的战斗力
}Pvp100;

typedef struct tagPvp100Cfg{
	ACE_UINT32 unStage;		//pvp100的阶段
	ACE_UINT32 unCount;  //完成本阶段需要斩杀的人数
	Pvp100 points;			//当前阶段匹配的攻击力
	CostInfoList reward;//奖励
}Pvp100Cfg;

typedef struct tagPvp100ListCfg{
	Pvp100Cfg pvp100Cfg[MAX_PVP100_CFG];
	ACE_UINT32 unCount;//一共配置了多少项
}Pvp100ListCfg;

typedef struct tagPvp100_node{	
	ACE_UINT32 unId;
	ACE_UINT32 unScore;
	tagPvp100_node *next;
}Pvp100_node;

typedef struct tagPvp100Group{
	Pvp100_node *head;//头指针
	Pvp100_node *cur;//当前指针指向
	ACE_UINT32 unCount;
}Pvp100Group;

typedef struct tagTeamLevel
{
public :
	tagTeamLevel() :
		level(0), levelup_exp(0), extraskill_slots(0),
		extraskill_learn(0), player_levelmax(0), equip_levelmax(0)
	{ }
	int level;
	int levelup_exp;
	int extraskill_slots;
	int extraskill_learn;
	int player_levelmax;
	int equip_levelmax;
}TeamLevel;
//  typedef struct tagPvp100List{
//  	Pvp100Group list[MAX_PVP100_STAGE_COUNT];
// }Pvp100List; //pvp100按照攻击力排列的1000名 

typedef struct tagSignUpGift
{
	tagSignUpGift() : m_dwDate(0), m_dwVipCheck(0), m_dwRewardID(0),
		m_dwRewardCount(0), m_dwVipRewardID(0), m_dwVipRewardCount(0)
	{ }
	int m_dwDate;
	int m_dwVipCheck;
	int m_dwRewardID;
	int m_dwRewardCount;
	int m_dwVipRewardID;
	int m_dwVipRewardCount;
}SignUpGift;

typedef struct tagRoleStepInfo
{
	int step;
	int upgrade_cost;
	ACE_UINT32 role_lv_require;//角色进阶要求角色等级
}RoleStepInfo;

//技能信息
typedef struct tagSkillInfo
{
	tagSkillInfo()
	{
		skillID = 0;
		skillLevel = 0;
		memset(m_strName,0,MAX_ITEM_NAME + 1);
	}
	ACE_UINT32 skillID;//技能id
	ACE_UINT32 skillLevel;//技能等级
	char m_strName[MAX_ITEM_NAME + 1];//技能名字
	void ToJson(Json::Value &root);
}SkillInfo;

typedef struct tagAccountBasicInfo
{
	ACE_UINT32 m_unCharacterID;
	char m_email[MAX_EMAIL_LENGTH + 1];
	char m_mac[MAX_ACCOUNT_LENGTH + 1];
	char m_PlayerName[MAX_CHARACTER_LENGTH + 1];
	SkillInfo m_skillList[MAX_SKILL_COUNT];//技能列表
	ACE_UINT32 m_unLevel;
	ACE_UINT32 m_unExp;
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
	ACE_UINT32 m_unRechargeCount;
	ACE_UINT32 m_unRechargeAmount;
	ACE_UINT32 m_unPackageMax;
	ACE_UINT32 m_unTutorialFlag;//新手引导标记
	ACE_UINT32 m_unUseLuckCount;
	ACE_UINT32 m_unCreateTime;//xxj 2015/04/23  11:29:41 创建时间
	ACE_UINT32 m_unPoint;//战力
	ACE_UINT32 m_unChannel;//渠道
	
	void ToJson(Json::Value &root);
}AccountBasicInfos;

typedef struct tagAccountBriefInfo
{
	ACE_UINT32 m_unCharacterID;
	char m_mac[MAX_ACCOUNT_LENGTH + 1];
	char m_email[MAX_EMAIL_LENGTH + 1];
	char m_PlayerName[MAX_CHARACTER_LENGTH + 1];

	void ToJson(Json::Value &root);
}AccountBriefInfo;

typedef struct tagAccountBriefInfoList
{
	ACE_UINT32 m_AccountCount;
	AccountBriefInfo m_oBriefInfos[MAX_ACCOUNT_BRIEF_INFO_LEN];

	void ToJson(Json::Value &root);
}AccountBriefInfoList;

typedef struct tagAccountItemInfo
{
	ACE_UINT32 m_unItemsCount;
	PackageCell m_itemsList[MAX_ITEMS_COUNT];

	void ToJson(Json::Value &root);
}AccountItemInfos;

typedef struct tagAccountPlayerInfo
{
	ItemInfo m_staff;
	ACE_UINT32 m_selectedPlayerList[MAX_PLAYER_SELECTED_COUNT];
	PlayerInfo m_playerList[MAX_PLAYER_COUNT];
	ACE_UINT32 m_selectedPlayerSkillList[MAX_PLAYER_SELECTED_COUNT];

	void ToJson(Json::Value &root);
}AccountPlayerInfos;

//删除好友列表
struct DeleteFriendList
{
	ACE_UINT32 m_time;//最近处理时间
	ACE_UINT32 m_count;
	ACE_UINT32 m_delete_list[MAX_FRIEND_DELETE_COUNT];//删除好友的id
};

/*typedef struct tagGiftBagCodeDBItem
{
	char m_strGiftBagCode[MAX_GIFT_BAG_CODE_LENGTH];
	ACE_UINT32 m_unCodeType;
	ACE_UINT32 m_unGiftBagType;
	ACE_Byte   m_byUsed;
	//ACE_UINT32 m_unExpiredTime;
}GiftBagCodeDBItem;*/

typedef struct tagAdminStatistics
{
	char strDate[11];
	ACE_UINT32 unStatisticsType;  
}AdminStatistics;

enum E_Statistics_Type
{
	E_Statistics_Character_Amount = 0,//角色数
	E_Statistics_Daily_Online = 1,//在线人数
	E_Statistics_Nextday_Remain = 2,//次日留存
	E_Statistics_3days_Remain = 3,//3日留存
	E_Statistics_7days_Remain = 4,//7日留存
	E_Statistics_15days_Remain = 5,//15日留存
	E_Statistics_30days_Remain = 6,//30日留存

	E_Statistics_ACU = 7,   //每日平均在线人数 先按10分钟抽样
	E_Statistics_PCU = 8,   //每日同时在线人数的峰值
	E_Statistics_Tutorial= 9,//新手引导数量
	E_Statistics_Effect_Character= 10,//有效用户
	E_Statistics_Effect_Register= 11,//注册帐号
	E_Statistics_Effect_Login= 12,//登录帐号
	E_Statistics_lost_Login= 13,//用户流失

	//Add before this line
	E_Statistics_ItemAmount,
};


#define Statistics_ACU_Interval    (600 * 1000)

#define Statistics_ACU_Num (144)

#define Statistics_Reload_Interval (60 * 1000)

//任务事件类型
enum E_ACTIVE_BASE_EVENT
{
	Event_Base_Type_Duplication = 1, //副本
	Event_Base_Type_TreasureMountain = 2, //金山
	Event_Base_Type_Trial = 3,             //
	Event_Base_Type_Lottery = 4,           //奖劵
	Event_Base_Type_LevelUp = 5,		//升级
	Event_Base_Type_EquipmentUpgrade = 6, //装备升级
	Event_Base_Type_EnhanceSkill = 7,   //技能增加
	Event_Base_Type_SecretBuy = 8,              //神秘商店
	Event_Base_Type_SupermanPowerStone = 9,     //动感能量石
	Event_Base_Type_SpecificDuplication = 10,	//特殊副本
	Event_Base_Type_ReachSpecificLevel = 11,	//等级
	Event_Base_Type_ReachSpecificStar = 12,		//星星
	Event_Base_Type_EquipmentSpecificLevel = 13,//装备特殊等级
	Event_Base_Type_EquipmentSpecificStar = 14,	//装备特殊星星
};

enum E_TASK_STATUS
{
	TASK_STATUS_OPEN = 1,	//开启状态
	TASK_STATUS_FINISHED = 2,	//完成状态
	TASK_STATUS_REWARED = 3,	//已完成 并领取

	TASK_STATUS_ERROR,
};

enum E_TASK_OPERATOR
{
	TASK_OPT_LIST = 1,
	TASK_OPT_ADD = 2,//添加
	TASK_OPT_GETREWARD = 3,//领奖
	TASK_OPT_DAILY_LIST = 4,
	TASK_OPT_DAILY_ADD = 5,
	TASK_OPT_DAILY_GETREWARD = 6,
	TASK_OPT_DAILY_OBTAINEDREWARD = 7,
	TASK_OPT_DAILY_ACTIVENESS = 8,
	TASK_OPT_DAILY_SINGLE_REWARD = 9,
};

enum E_TASK_LIST_TYPE
{
	TASK_LIST_MAIN = 1,
	TASK_LIST_DAILY = 2,
};

struct ActiveEvent 
{
	ActiveEvent() {
		Reset();
	};

	void Reset()
	{
		m_byTaskStatus = TASK_STATUS_OPEN;
		m_unCurrentProgress = 0;
	}

	ACE_Byte m_byTaskStatus;

	ACE_UINT32 m_unTaskID;
	ACE_UINT32 m_unActiveEventType;
	//ACE_UINT32 m_unAttachObj;
	ACE_UINT32 m_unCurrentProgress;
};

class TaskComp
{
public:
	bool operator () (const ActiveEvent &obj_left, const ActiveEvent &obj_right) const
	{
		return obj_left.m_unTaskID < obj_right.m_unTaskID;
	}
};

typedef struct tagCommunicationRecord
{
	ACE_UINT32 unCmd;
	ACE_UINT32 unRecvTime;
	ACE_UINT32 unSendTime;
}CommunicationRecord;

//限时活动相关

//限时活动时间表
#define MAX_RelatedT_ITEMS 20
typedef struct tagLimitedActivityConfig
{
	ACE_UINT32 unID;
	ACE_UINT32 unStartTime;//开始时间
	ACE_UINT32 unEndTime;//结束时间
	ACE_UINT32 unWeekCircle;//一周日期循环
	ACE_UINT32 unDayTimeStart;//一天的开放时间开始
	ACE_UINT32 unDayTimeEnd;//一天的开放时间结束点
	ACE_UINT32 unRelatedType;//关联类型编号
	ACE_UINT32 unRelatedCount;//下面数据长度
	ACE_UINT32 unRelatedItems[MAX_RelatedT_ITEMS];//关联数据
	ACE_UINT32 unCloseTime;//关闭时间
}LimitedActivityConfig;


//限时活动任务表
#define MAX_PreMission_COUNT 4
#define MAX_MissionPrize_COUNT 10
typedef struct tagMissionPrize
{
	ACE_UINT32 unID;
	ACE_UINT32 unCount;
}MissionPrize;

typedef struct tagLimitedActivityMissionConfig
{
	ACE_UINT32 unID;
	ACE_UINT32 unActiviID;//对应的活动id
	ACE_UINT32 unLvLimit;//解锁等级
	ACE_UINT32 unPreMissionID[MAX_PreMission_COUNT];//前置任务ID
	ACE_UINT32 unMissionType[3];//类型编号
	ConfigReward stReward;//奖励品
	//MissionPrize unPrizeItems[MAX_MissionPrize_COUNT];//奖励品
}LimitedActivityMissionConfig;

//对应数据库信息
#define ZeroVar(p) ZeroMemory( &p, sizeof( p ) )
typedef struct tagLimitedActivityInfo
{
	tagLimitedActivityInfo()
	{
		ZeroVar(*this);
	}
	//ACE_UINT32 unCharacterID;//角色id
	ACE_UINT32 unLAID;//限时活动id
	ACE_UINT32 unCloseTime;//关闭时间
	ACE_UINT32 unProgress;//条件进度(先决条件)
	ACE_UINT32 unDealTime;//最近处理时间
	ACE_UINT32 unLinkType;//关联条件
	ACE_UINT32 unRelatedCount;//已领取列表长度
	ACE_UINT32 unRelatedItems[MAX_RelatedT_ITEMS];//已领取列表
}LimitedActivityInfo;

/*
"类型编号，关联数据1，关联数据2，…
编号【0】关联任务类，任务1ID，任务2ID,…
编号【1】神秘商店折扣任务类，货币类型，折扣率
编号【2】关卡上限双倍，关卡1ID，关卡2ID，…
编号【3】关卡消耗减半，关卡1ID，关卡2ID，…
编号【4】关卡资源双倍，关卡1ID，关卡2ID，…
编号【5】关卡掉落双倍，关卡1ID，关卡2ID，…
编号【6】装备强化折扣，折扣率
编号【7】角色升级折扣，折扣率
编号【8】等级排行活动，任务1ID，任务2ID，…
编号【9】战力排行活动，任务1ID，任务2ID，…
编号【10】徽章排行活动，任务1ID，任务2ID，…
编号【11】限时礼包活动，付费1ID，付费2ID，…
编号【12】道具兑换活动，任务1ID，任务2ID，…"
*/
enum E_L_A_TYPE
{
	LA_TYPE_LINK= 0,
	LA_TYPE_1 = 1,
	LA_TYPE_2 = 2,
	LA_TYPE_3 = 3,
	LA_TYPE_4 = 4,
	LA_TYPE_5 = 5,
	LA_TYPE_6 = 6,
	LA_TYPE_7 = 7,
	LA_TYPE_9 = 9,
	LA_TYPE_11 = 11,
};

/*
大格式:条件1类型,条件1参数(16进制),完成次数
类型【1001】充值类，0，数量
类型【1002】消费类，资源ID，数量
类型【1003】十连抽，【友情点1/金卡2】，次数
类型【1004】单抽，类型【友情点1/金卡2】，次数
类型【1005】连续登陆，累计登陆次数【数字】，0
类型【1006】排行奖励类，排名上限，排名下限
类型【1007】兑换类，0，0
*/
#define LA_MISSION_TYPE_1001 1001
#define LA_MISSION_TYPE_1002 1002
#define LA_MISSION_TYPE_1003 1003
#define LA_MISSION_TYPE_1004 1004
#define LA_MISSION_TYPE_1005 1005
#define LA_MISSION_TYPE_1006 1006


typedef struct tagBadgeInfo
{
	tagBadgeInfo(ACE_UINT32 id = 0)
	{
		ZeroVar(*this);
		unID = id;
		m_flag = 1;
	}

	ACE_UINT32 unID;//资源id
	ACE_UINT32 m_gain;//加成
	ACE_UINT32 m_charge_value;//充能值
	ACE_UINT32 m_flag;
}BadgeInfo;

//add by xxj 2015/08/18  16:01:47 
//pvp 相关
//pvp信息
#define DAY_TIME_SETTLE_START (47*30*60) //结算 23:30 开始
#define DAY_TIME_SETTLE_END (24*60*60-1) //结算 23:59:59 结束
#define DAY_TIME_SETTLE_STARTEX (21*60*60) //结算开始21:00 每日奖励
#define DAY_TIME_SETTLE_ENDEX (21*60*60 + 30*60) //结算 21:15 结束

#define MAX_FightRecordInfo_LEN 10		//记录最大条数

typedef struct tagPVPInfo
{
	ACE_INT32  nhonour;//荣誉值
	ACE_UINT32 unAttackTimes;//挑战次数
	ACE_UINT32 unLastChangeTime;//最后更新时间
	ACE_UINT32 unWinLost;//胜负次数16位一个 0x0FFFF前16位胜利，0xFFFF0000后16位失败
	ACE_UINT32 unBuyCount;//购买次数
	ACE_UINT32 unFreshenCount;//刷新次数
	tagPVPInfo()
	{
		ZeroVar(*this);
	}
}PVPInfo;

typedef struct tagPVPInfoEx:public tagPVPInfo
{
	ACE_INT32  nhonourRank;//荣誉值排名
	tagPVPInfoEx()
	{
		ZeroVar(*this);
	}
}PVPInfoEx;

typedef struct tagHLInfo
{
	tagHLInfo()
	{
		ZeroVar(*this);
		isRobt = false;
	}

	bool operator>(const tagHLInfo& rhs)const//降序排序时必须写的函数
	{   
		return m_honour > rhs.m_honour; 
	}

	ACE_UINT32 m_characterID;
	ACE_INT32  m_honour;
	bool isRobt;
}HLInfo;

typedef struct tagHLInfoArray
{
	int uncount;
	HLInfo m_array[3];
	CharacterInfoExt playerinfo[3];
	tagHLInfoArray()
	{
		uncount = 0;
	}
}HLInfoArray;

#define MAX_HONOUR_LEVEL_COUNT 50

typedef struct tagHLUserInfo
{
	ACE_UINT32 m_userID;//账户id
	ACE_UINT32 m_roleHeadID;//队长id
	ACE_UINT32 m_unStep;//队长阶数
	ACE_INT32 m_honour;//荣誉值
	char name[MAX_CHARACTER_LENGTH + 1];//名字
	tagHLUserInfo()
	{
		ZeroVar(*this);
	}
}HLUserInfo;

typedef struct tagFightScoreInfo//得分记录
{
	ACE_UINT32 unCount;//上阵人数
	ACE_UINT32 role_list[MAX_PLAYER_SELECTED_COUNT];//角色id
	ACE_UINT32 setup_list[MAX_PLAYER_SELECTED_COUNT];//角色阶数
	ACE_INT32 score_list[MAX_PLAYER_SELECTED_COUNT];//得分总数
	tagFightScoreInfo()
	{
		ZeroVar(*this);
	}
}FightScoreInfo;

typedef struct tagFightUserInfo
{
	ACE_UINT32 m_characterID;//账户id
	ACE_UINT32 m_level;//等级
	ACE_INT32 m_honour;//荣誉值
	char name[MAX_CHARACTER_LENGTH + 1];//名字
	FightScoreInfo fightInfo;//得分记录

	tagFightUserInfo()
	{
		ZeroVar(*this);
	}
}FightUserInfo;

typedef struct tagFightRecordInfo//记录
{
	ACE_INT32 score;//攻击者得分
	ACE_INT32 isWin;//攻击者是否获胜
	FightUserInfo from;//攻击者
	FightUserInfo to;//被攻击者

	tagFightRecordInfo()
	{
		ZeroVar(*this);
	}
}FightRecordInfo;

typedef struct tagFightRecordInfoEx//记录
{
	FightRecordInfo info;
	bool isRoobt;//是否机器人
}FightRecordInfoEx;

//战绩列表
typedef struct tagFightRecordInfoList
{
	ACE_UINT32 unCount;
	FightRecordInfo info[MAX_FightRecordInfo_LEN];
}FightRecordInfoList;

//最大伤害值
typedef struct tagFightRoleHurtInfo
{
	ACE_UINT32 unCharacterID;
	ACE_UINT32 unRoleID;
	ACE_UINT32 unHurt;//伤害
}FightRoleHurtInfo;
//-----------------------------------------end

//------------------------------闯关最高伤害排行榜 相关
#define MAX_FIGHT_LEVEL_COUNT 50
typedef struct tagFightPlayerInfoBase
{
	ACE_UINT32 m_userID;//账户id
	ACE_UINT32 m_roleID;//最高伤害角色id
	ACE_UINT32 m_unStep;//角色阶数
	ACE_INT32 m_hurt;//伤害值
	tagFightPlayerInfoBase()
	{
		ZeroVar(*this);
	}
}FightPlayerInfoBase;

typedef struct tagFightPlayerInfo
{
	ACE_UINT32 m_level;//等级
	FightPlayerInfoBase info;//伤害基础信息
	char name[MAX_CHARACTER_LENGTH + 1];//名字
	tagFightPlayerInfo()
	{
		ZeroVar(*this);
	}
}FightPlayerInfo;
//--------------------

