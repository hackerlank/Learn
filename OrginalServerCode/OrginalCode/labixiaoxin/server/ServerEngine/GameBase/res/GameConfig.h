#pragma 

#include "ace\ace.h"
#include "ace\Singleton.h"
#include "..\..\Base\Utils\ConfigLoader.h"
#include "..\Common\GameDefine.h"
#include "ace\Hash_Map_Manager.h"
#include "ace\Null_Mutex.h"
#include <map>
#include <vector>
#include <string>
#include "..\Protocol\ControlProtocol.h"
#include "BuyEnergyCost.h"
#include "..\Common\ErrorMsgHead.h"
#include "ChannelRes.h"

//typedef ACE_Hash_Map_Manager_Ex<ACE_UINT32, ConfigReward *, ACE_Hash<ACE_UINT32>, 
//ACE_Equal_To<ACE_UINT32>, ACE_Null_Mutex> LOOT_REPLACE_MAP;
//typedef LOOT_REPLACE_MAP::ITERATOR LOOT_REPLACE_MAP_ITERATOR;


#define MAX_INIT_ITEM_LIST 256
#define MAX_INIT_UNLOCK_MAP 64
#define MAX_INIT_QUEST 8
#define MAX_LOGIN_BONUS 8
#define MAX_RECHARGE_INFO 16
#define MAX_TEAM_LEVEL 120
#define MAX_ROLE_STEP 20

//解锁等级
typedef struct tagSchemeInfo
{
	tagSchemeInfo()
	{
		ZeroVar(*this);
	}
	ACE_UINT32 m_scheme_arena;//竞技场解锁
	ACE_UINT32 m_scheme_badge;//徽章解锁
}SchemeInfo;

//徽章能量升级
typedef struct tagBadgeLevelInfo
{
	tagBadgeLevelInfo()
	{
		ZeroVar(*this);
	}
	ACE_UINT32 m_level;
	ACE_UINT32 m_energy[5];
}BadgeLevelInfo;

//xxj 2015/04/22  16:40:03 
//配置文件公式
typedef struct tagFormulaInfo
{
	tagFormulaInfo()
	{
		paramA = paramB =paramC = 0;
	}
	double paramA;
	double paramB;
	double paramC;
}FormulaInfo;
//--------------------------------------
//add by xxj 2015/08/18  20:36:12 
//pvp 相关info
typedef struct tagHonorRankInfo
{
	tagHonorRankInfo()
	{
		attack_times = amount =base_honor_point = init_honor = honor_modulus = 0;
	}
	ACE_UINT32 attack_times;//挑战次数恢复（秒）
	ACE_UINT32 amount;//累计次数上限
	ACE_UINT32 base_honor_point;//基础荣誉点获得
	ACE_UINT32 init_honor;//初始荣誉点数
	ACE_UINT32 honor_modulus;//荣誉系数
}HonorRankInfo;
//-------------------------------end
typedef struct tagRechargeInfo
{
	int cost;
	int money;
}RechargeInfo;

class GameConfig : public ConfigLoader
{
public:
	GameConfig();
	~GameConfig();

	int load_all_config();

	virtual int deal_config(int config_id, xmlNodePtr rootNode);

	ACE_UINT32 m_unInitPlayerCount;
	ACE_UINT32 m_InitPlayerList[MAX_PLAYER_COUNT];
	ACE_UINT32 m_unInitSelectPlayerCount;
	ACE_UINT32 m_InitSelectPlayerList[MAX_PLAYER_COUNT];
	ACE_UINT32 m_InitEquipmentList[MAX_EQUIPMENT_COUNT];

	ACE_UINT32 m_unInitBenefitCount;
	ACE_UINT32 m_InitBenefitList[MAX_INIT_BENEFIT_COUNT];

	ACE_UINT32 m_unMaxEnergy;
	ACE_UINT32 m_unEnergyRestoreInterval;
	ACE_UINT32 m_unRestoreEnergyGold;

	ACE_UINT32 m_unMaxPVPEnergy;
	ACE_UINT32 m_unPVPEnergyRestoreInterval;
	ACE_UINT32 m_unPVPRestoreEnergyGold;
 
	ACE_UINT32 m_unInitCoin;

	ACE_UINT32 m_unInitUnlockMapID;

	ACE_UINT32 m_unGetLuckCost;
	ACE_UINT32 m_unGetMoreLuckCost;

	ACE_UINT32 m_unRebornCost;

	ACE_UINT32 m_unRenameCost;

	ACE_UINT32 m_unMaxLv; // added by  jinpan for max level

	

	//ACE_UINT32 m_unLuckFixRewardList[2];
	ConfigReward m_luckFixRewardList[2];

	PackageExpandInfo m_friendExpandInfo;
	PackageExpandInfo m_packageExpandInfo;

	CareerInfo m_careerList[MAX_MAIN_CHARACTER_ID];

	ACE_UINT32 m_unSkillPriceList[MAX_SKILL_LEVEL];

	char m_defaultName[MAX_CHARACTER_LENGTH + 1];

	ACE_UINT32 m_loginBonusList[MAX_LOGIN_BONUS_COUNT];

	//LOOT_REPLACE_MAP m_lootReplaceMap;
	ConfigReward m_lootReplaceReward;

	ConfigReward m_firstRechargeReward;

	Secret m_secretCfg;  //added by jinpan for secretcfg

	Pvp100ListCfg m_pvp100Cfg;//百人斩jinpan

	TeamLevel m_teamLevel[MAX_TEAM_LEVEL + 1];
	ACE_UINT32 m_maxLevel;

	RoleStepInfo m_roleStepInfo[MAX_ROLE_STEP + 1];

	std::map<int, SignUpGift> m_oSignUpGift;

	ACE_UINT32 m_unCurrentVersion;

	std::map<ACE_UINT32, GiftBagCodeReward> m_oGiftBagCodeReward;

	std::vector<std::map<UINT32, ACE_Byte> > m_vecDoubleDropMap;
	ACE_UINT32 m_unRefreshDoubleDropSecs;
	ACE_UINT32 m_unRefreshDoubleDropVersion;
	ACE_UINT32 m_unAddFriendshipFriend;
	ACE_UINT32 m_unAddFriendshipStranger;
	ACE_UINT32 m_unReturnFriendshipFriend;
	ACE_UINT32 m_unReturnFriendshipStranger;

	std::map<ACE_UINT32, TaskConfig> m_oTaskConfig;//主线任务
	std::multimap<ACE_UINT32, TaskConfig> m_oTaskTypeConfig;//任务获得的值

	std::map<ACE_UINT32, ActivenessInfo> m_oActivenessList;//活跃任务
	std::map<ACE_UINT32, ConfigReward> m_oActivenessReward;//活跃任务或得的值
	std::map<ACE_UINT32, GoldenTouchProfit> m_oGoldenTouchProfit;
	std::map<ACE_UINT32, GoldenTouchCost> m_oGoldenTouchCost;
	std::map<ACE_UINT32, ACE_UINT32> m_vipGiftList;//vip礼包列表
	//consumeactive消费活动

	std::vector<EquipStepConfig> m_oEquipStepConfig;

	std::map<ACE_UINT32, PlayerInfo> m_oRobotPlayer;
	std::map<ACE_UINT32, PublicPlayerInfo *> m_oRobotTeam;
	std::map<ACE_UINT32, std::pair<std::vector<UINT32>, std::vector<PublicPlayerInfo *> > > m_oLevelRobotTeam;
	

	std::map<ACE_UINT32, ACE_UINT32> m_oUnlockPrefixMapID;
	float m_fSecretOff;
	ACE_UINT32 get_main_character_id_by_equipment(ACE_UINT32 unEquipmentID);
	ACE_UINT32 get_required_player_id_by_equipment(ACE_UINT32 unEquipmentID);

	FormulaInfo m_vecFormulaInfo[4];//xxj 2015/04/22  16:49:16 公式列表
	//限时活动相关
	std::map<ACE_UINT32, LimitedActivityConfig> m_olimitedActivityConfig;//活动任务表，限时活动
	std::map<ACE_UINT32, std::vector<ACE_UINT32>> m_olimitedActivityTypeList;//活动任务列表--类型对应列表
	std::map<ACE_UINT32, LimitedActivityMissionConfig> m_olimitedActivityMissionConfig;//限时活动任务表
	//------------------
	//新服战力排行榜
	std::map<ACE_UINT32, LimitedActivityConfig> m_olimitedActivityConfigEx;//活动任务表，限时活动,新服战力排行榜 会时时更新
	//--------------------------end

	BuyEnergyCostRes m_oBuyEnergyCost;//购买体力列表
	std::map<ACE_UINT32,ChannelRes> m_oChannelRes;
	std::map<ACE_UINT32,BadgeLevelInfo> m_oBadgelevelConfig;//徽章等级
	//pvp 信息
	HonorRankInfo m_oHonorRankConfig;//pvp荣誉排位
	ACE_INT32 m_oHLmin;
	ACE_INT32 m_oHLmax;
	std::map<ACE_UINT32,HonorLevel> m_oHonorLevel;//每日奖励
	std::map<ACE_UINT32,HonorRank> m_oHonorRank;//赛季奖励
	std::map<ACE_UINT32,ACE_UINT32> m_oHonorCost;//赛季次数购买
	//----------------------end
	
	SchemeInfo m_oSchemeInfo;//解锁等级
	static ACE_INT32 g_maxSetup;
private:
	void parse_game_config(xmlNodePtr rootNode);
	//void parse_init_player_list(xmlNodePtr rootNode);
	//void parse_init_equipment_list(xmlNodePtr rootNode);
	ACE_UINT32 parse_init_id_list(xmlNodePtr rootNode, ACE_UINT32 *dest);
	void parse_career_list(xmlNodePtr rootNode);
	void parse_skill_price_list(xmlNodePtr rootNode);

	void parse_loot_replace_config(xmlNodePtr rootNode);
	void parse_loot_replace(xmlNodePtr rootNode);

	void parse_energy(xmlNodePtr rootNode, bool flag);
	void parse_expand_info(xmlNodePtr rootNode, PackageExpandInfo &info);

	//void parse_init_benefit_list(xmlNodePtr rootNode);

	void parse_get_luck_cost(xmlNodePtr rootNode);

	void parse_login_bonus(xmlNodePtr rootNode);
	void parse_login_gold(char *str);
	void get_luck_fix_reward(int idx, xmlNodePtr rootNode);

	ACE_UINT32 get_cost(xmlNodePtr rootNode);
	void parse_secret_config(xmlNodePtr rootNode);  //added by jinpan
	void parse_pvp100_config(xmlNodePtr rootNode);  //处理百人斩配置  jinpan
	void parse_team_level_config( xmlNodePtr rootNode );

	void parse_grade_config(xmlNodePtr rootNode);
	void parse_sign_up_config(xmlNodePtr rootNode);

	void parse_gift_bag_code_config(xmlNodePtr rootNode);

	void parse_double_drop_config(xmlNodePtr rootNode);
	void parse_task_config(xmlNodePtr rootNode);
	void parse_active_mission(xmlNodePtr rootNode);
	void parse_active_prize(xmlNodePtr rootNode);
	void parse_equip_step(xmlNodePtr rootNode);
	void parse_robot_player(xmlNodePtr rootNode);
	void parse_robot_team(xmlNodePtr rootNode);
	void Parse_Formula_config(char *str,int n);//xxj 2015/04/22  16:42:37 加载公式
	void Parse_Formula_info(FormulaInfo &dest, char *str);//公式解析
	void Parse_limited_activity(xmlNodePtr rootNode);//限时活动
	void Parse_limited_mission_activity(xmlNodePtr rootNode);//限时活动任务表
	void Parse_golden_touch_profit(xmlNodePtr rootNode);
	void Parse_golden_touch_cost(xmlNodePtr rootNode);
	void Parse_BuyEnergy_cost(xmlNodePtr rootNode);
	void Parse_channel(xmlNodePtr rootNode);
	void Parse_badgeLevel(xmlNodePtr rootNode);
	void parse_gameconfig_honor_rank(xmlNodePtr rootNode);
	void parse_honor_level(xmlNodePtr rootNode);
	void parse_honor_rank(xmlNodePtr rootNode);
	void parse_honor_cost(xmlNodePtr rootNode);
	void parse_gameconfig_button_unlock(xmlNodePtr rootNode);
	//int m_InitUnlockMapOffset;
	//int m_InitMonsterOffset;
};

typedef ACE_Singleton<GameConfig, ACE_Thread_Mutex> GAME_CONFIG_INSTANCE;