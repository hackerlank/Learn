/********************************************************************
//	TaskLoad Library Source File.
//	File name:	TaskConf.h
//	Created:	2011/09/12	15:00
//	Organization:	
//	Copyright (c) 2010-2020 Jingyuan Wang, All rights reserved.
// ------------------------------------------------------------------
//	Author:		Jingyuan Wang
//	E-Mail:		tyketom@hotmail.com
//	Http://
// ------------------------------------------------------------------
//	Purpose:	
//	Version:	1.0
//	Histroy:
 *********************************************************************/

#pragma once
#ifdef _WIN32
#include <Windows.h>
#else
#include <string.h>
#include <stdint.h>
typedef char INT8;
typedef short INT16;
typedef int INT32;
typedef long LONG;
typedef int64_t INT64;
typedef unsigned char UINT8;
typedef unsigned short UINT16;
typedef unsigned int UINT32;
typedef unsigned long ULONG;
typedef uint64_t UINT64;
#define sscanf_s sscanf
#define strcpy_s(dest, n, src) strncpy(dest, src, n)
#endif

#include <vector>
#include <string>
#include <map>

using namespace std;

//任务归类
enum ETaskConfType
{
    eTaskConfNone = 0,
    eTaskConfMain,      //主线
    eTaskConfBranch,    //支线
    eTaskConfDay,       //日常
    eTaskConfVip,       //vip
    eTaskGuide,			//新手引导任务
    eTaskForGroup,      //师门任务
    eTaskForGroupLevel,//师门晋级
    eTaskForYaMen,      //衙门任务
    eTaskForYaMenLevel, //衙门晋级任务
    eTaskCircle,        //环任务
};

//任务内容
enum EContentType
{
    eContentNone = 0,
    eContentKill = 1,           //猎杀
    eContentGrow = 1 << 1,      //成长
    eContentCollect = 1 << 2,   //收集
    eContentGather = 1 << 3,    //采集
    eContentProbe = 1 << 4,     //探索
    eContentBehave = 1 << 5,    //行为
    //eContentBuild = 1 << 6,   //建设
    eContentTechnics = 1 << 6,  //科技
    eContentTalk = 1 << 7,      //对话
};

//任务类型扩展标记
enum ETaskTypeExtent
{
    eTaskTypeExtent_normal = 0,     //一般任务
    eTaskTypeExtent_reward = 1,     //悬赏任务
};

//性别限制
enum ELimitGender
{
    eLimitGender_none = 0,
    eLimitGender_Male,
    eLimitGender_Female,
};

//阵营限制
enum ELimitCamp
{
    eLimitCamp_none = 0,
    eLimitCamp_1,
    eLimitCamp_2,
    eLimitCamp_3,
};

//家族公会限制
enum ELimitFamily
{
    eLimitFamily_none = 0,
    eLimitFamily_family,
    eLimitFamily_faction,
};

//任务过程-成长-角色属性
enum EProcessRoleProperty
{
    eProcessRoleProperty_none = 0,
    eProcessRoleProperty_level,     //等级
    eProcessRoleProperty_repute,    //声望
};

struct SRoleProperty
{
    EProcessRoleProperty type;
    UINT32 value;
    UINT32 dwExtID;
};

//任务过程-行为-功能
enum EProcessAction
{
    eProcessAction_none = 0, 
    eProcessAction_sCopy = 1,           //单人副本
    eProcessAction_mCopy = 2,           //多人副本
    eProcessAction_StrEquip = 3,        //强化装备次数
    eProcessAction_Upgrade = 4,         //装备铸造
    eProcessAction_WorldBoss = 5,       //世界boss伤害
    eProcessAction_JoinGuild = 6,       //加入帮派
    eProcessAction_RecruitCortege = 7,  //招募散仙
    eProcessAction_Chest = 8,           //扫荡副本
    eProcessAction_RanCortege = 9,      //培养散仙
    eProcessAction_GuildContrib = 10,    //帮派贡献
    eProcessAction_GuildSkill = 11,      //帮派技能
    eProcessAction_Skill = 12,           //升级技能
    eProcessAction_CollectGame = 13,     //收藏游戏
    eProcessAction_UnlockEquip = 14,     //解封装备
    eProcessAction_LearnSkill = 15,      //获得技能
    eProcessAction_GetTrump = 16,        //获得法宝
    eProcessAction_Refer = 17,           //推荐好友
    eProcessAction_ActFormation = 18,    //激活阵型
    eProcessAction_ActMounts = 19,       //激活坐骑
    eProcessAction_MountsUp = 20,        //坐骑升级
    eProcessAction_ActPet = 21,          //激活阵灵
    eProcessAction_PetUp = 22,           //阵灵升级
    eProcessAction_FighterWork = 23,     //散仙出战
    eProcessAction_FighterCT = 24,       //散仙淬体
    eProcessAction_FighterTrump = 25,    //散仙法宝
    eProcessAction_FighterSkill = 26,    //散仙技能
    eProcessAction_UpdateTrump = 27,     //法宝祭炼
    eProcessAction_TodayActivity = 28,   //当日活跃度 
    eProcessAction_FinishGroupTask = 29, //完成师门任务
    eProcessAction_FinishYaMenYask = 30, //完成衙门任务 = ,
    eProcessAction_FighterDuJie = 31,    //散仙渡劫到N = ,
    eProcessAction_MakeFire = 32,        //仙府祈火 = ,
    eProcessAction_BeastUpLevel = 33,    //兽魂升级 = ,
    eProcessAction_FighterSkillUpLevel = 34,//散仙技能升级
    eProcessAction_ArenaChallenge = 35,      //斗剑历练一次
    eProcessAction_LadderChallenge = 36,    //天梯挑战
    eProcessAction_TowerLevel = 37,        //索妖塔到达层数
    eProcessAction_SpecialHeroLevel = 38,  //指定某散仙某等级
    eProcessAction_HeroTeamUpLevel = 39,   //任意组合散仙升阶，有动作即可
    eProcessAction_FinishTreasureHunt = 40,//完成任一寻宝
    eProcessAction_GetBeauty = 41,         //激活任一美女
    eProcessAction_DefenseShushanSuc = 42, //守卫任一蜀山成功
    eProcessAction_HeroXinFa = 43,         //指定某散仙激活某心法
    eProcessAction_BrockenBattleArrayEyeSuc = 44,    //成功任一破阵眼
    eProcessAction_OpenShip = 45,             //开启任一运镖
    eProcessAction_SpecialHeroToTalCTLv = 46, //特定散仙淬体到达某等级
    eProcessAction_SpecialTrumpUpdate = 47,   //特定法宝，升到特定等级
    eProcessAction_SpecialHeroDuJie = 48,     //特定散仙渡劫到特定等级
    eProcessAction_SpecialStrEquip = 49,      //特定装备强化到特定等级
    eProcessAction_GetItem = 50,              //得到某件物品
    eProcessAction_SpecialHeroCTLvl = 51,     //指定散仙淬体每项等级都超过N级
    eProcessAction_SpecialHeroSkillLvl = 52,  //指定散仙特定技能升到某等级
    eProcessAction_SpecialPetLvl = 53,        //指定阵灵升级到指定品阶
    eProcessAction_SpecialHorseLvl = 54,      //指定坐骑升阶到指定品阶
    eProcessAction_CombinedActivation = 55,   //组合激活
    eProcessAction_SpecialFighterWork = 56,   //特定散仙出战
    eProcessAction_MoneyTree = 57,            //摇钱树
    eProcessAction_SpecialBeautyPoint = 58,   //特定美女，特定亲密度
    eProcessAction_SpecialStone = 59,         //指定宝石镶嵌
    eProcessAction_MergeStone = 60,           //宝石合成
    eProcessAction_ZhanQi = 61,               //战旗
    eProcessAction_GetBeast = 62,             //激活指定兽魂
    eProcessAction_EnterShengLing = 63,         //参加圣陵一次
    eProcessAction_ActiveNewEquipTrump = 64,  //激活任意新法宝
    eProcessAction_StrongEquipTrump = 65,  //  强化任意法宝
    eProcessAction_XiLianEquipTrump = 66,  //洗练任意法宝
    eProcessAction_DeComposeEquipTrump = 67,//分解任意法宝
    eProcessAction_TianShu             =68,//装备任意天书一次
    eProcessAction_Max                   //行为最大值
};

struct SProcessAction
{
    EProcessAction type;
    UINT32 value;
    string param;
};

//一般奖励
/*enum EAwardGeneral
  {
  eAward_gold , // 仙石
  eAward_coupon, // 礼券
  eAward_silver, // 钱币
  eAward_soul, // 魂魄
  eAward_prestige, // 声望
  eAward_honor, // 荣誉
  eAward_pexp, // 修为
  eAward_sigil, // 符印
  eAward_centsy, // 仙元
  eAward_action, // 体力
  eAward_sop, // 阅历
  eAward_taoism, // 道术
  eAward_poten, // 潜能
  eAward_reiki, // 灵力
  eAward_xianquan, // 仙券
  eAward_exp, // 经验
  eAward_end,
  };*/

//一般奖励 统一成EMoneyType类型
/*
   enum EAwardGeneral
   {
   eAward_gold = 1,            //仙石
   eAward_silver = 2,          //银币
   eAward_coupon = 3,          //礼券
   eAward_giftcoin = 4,        //金券
   eAward_exp = 5,             //经验
   eAward_prestige = 6,        //声望
   eAward_soul = 7,            //魂魄
   eAward_honor = 8,           //荣誉
   eAward_pexp = 9,            //修为
   eAward_sigil = 10,          //符印
   eAward_centsy = 11,         //仙元
   eAward_action = 12,         //体力
   eAward_sop = 13,            //阅历
   eAward_taoism = 14,         //道术
   eAward_poten = 15,          //渡劫点数
   eAward_reiki = 16,          //副本星级
   eAward_hfp = 17,            //寻仙积分
   eAward_demonsoul = 18,      //封印点
   eAward_soulattack = 19,     //攻击之魂
   eAward_soulhp = 20,         //生命之魂
   eAward_soulcritical = 21,   //暴击之魂
   eAward_soulcounter = 22,    //反击之魂
   eAward_soulspeed = 23,      //身法之魂
   eAward_souldefence = 24,    //防御之魂
   eAward_soulhit = 25,        //命中之魂
   eAward_souldodge = 26,      //闪避之魂
   eAward_achievementap = 27,  //成就点
   eAward_collectap = 28,      //收藏点
   eAward_guildcontrib = 29,   //帮派贡献
   eAward_end                  //货币类型上限标志
   };
   */
struct SAwardGeneral
{
    UINT32 type;
    UINT32 value;
};

//属性奖励
enum EAwardProperty
{
    eAwardProperty_repute = 0,			//声望
    eAwardProperty_familyPrestige,		//家族威望
    eAwardProperty_factionContri,		//公会贡献
    eAwardProperty_end
};

struct SAwardProperty
{
    EAwardProperty type;
    UINT32 value;
};

//任务星级
enum EStarType
{
    eStarNone,	//无
    eStarC,		//C级任务
    eStarB,		//B级任务
    eStarA,		//A级任务
    eStarS,		//S级任务
    eStarSS		//SS级任务
};

//领取提交类型
enum ETargetType
{
    eTargetNone,	//无
    eTargetNpc,		//NPC委托
    eTargetScene,	//系统给予
    eTargetItem,	//道具触发
    eTargetPlayer, //玩家接取
    eTargetEnd
};

enum EChatType
{
    eChatNone,
    eChatMid,
    eChatBegin,
    eChatEnd
};

//任务属性触发类型
enum ETaskLimitPropType
{
    eLimtPropNone = 0,
    eLimtPropLevel = 1, //等级触发
    eLimtPropRepute = 2,    //声望触发
    eLimtPropEnd = 3
};

struct SLimitProp
{
    ETaskLimitPropType eLimitType;
    UINT16 wValue;
};

struct SChat
{
    EChatType eChatType;
    string strPC;
    string strNPC;

    SChat() : eChatType(eChatNone) { }
};

struct SNpcTalk
{
    vector<SChat> vecChat;
    map<UINT16, UINT16> mapItem2Count;
};

struct SMapArea
{
    UINT16 wMapID;
    float fX1, fZ1, fX2, fZ2;

    SMapArea() { memset(this, 0, sizeof*this); }
    bool operator==(const SMapArea& rhs)
    {
        if (wMapID == rhs.wMapID && fX1 == rhs.fX1
                && fX2 == rhs.fX2 && fZ1 == rhs.fZ1
                && fZ2 == rhs.fZ2)
            return true;

        return false;
    }
};

struct SUseItem
{
    UINT16 wItemID;
    SMapArea* pMapArea;

    SUseItem() { memset(this, 0, sizeof*this); }
};

struct SUseSkill
{
    UINT32 dwSkillID;
    SMapArea* pMapArea;

    SUseSkill() { memset(this, 0, sizeof*this); }
};

struct SCollectItem
{
    UINT16 wMonsterID;
    UINT16 wItemID;
    UINT16 wCount;

    SCollectItem() { memset(this, 0, sizeof*this); }
};

struct SKillMonster
{
    UINT16 wMonsterID;
    UINT16 wCount;
    bool bFake;

    SKillMonster() { memset(this, 0, sizeof*this); }
};

struct SAwardMercen
{
    UINT16 wMonsterID;
    UINT16 wNameID;
    UINT8 byPos;

    SAwardMercen() { memset(this, 0, sizeof*this); }
};

struct SIdxType
{
    UINT32 dwIdx;
    ETargetType eType;

    SIdxType() : dwIdx(0), eType(eTargetNone) { }
};

struct SIdxCount
{
    UINT32 dwIdx;
    UINT16 wCount;

    SIdxCount() : dwIdx(0), wCount(0) { }
};

struct SIdxCountJob
{
    UINT32 dwIdx;
    UINT16 wCount;
    UINT8 byJob;

    SIdxCountJob() : dwIdx(0), wCount(0), byJob(0) { }
};

struct STaskConfig
{
    //任务基本内容
    UINT16 wID;	//任务ID
    string strName;	//任务名称
    UINT8 byLevel;	//任务等级
    ETaskConfType eTaskType; //任务类型
    bool bOpen;	//是否开放
    bool bShare;	//是否共享
    UINT32 dwCharge;	//是否充值
    UINT32 dwRepeat;	//重复次数：0为不可重复，非0为每日重复次数，0xFFFFFFFF为无限重复
    ETaskTypeExtent eTaskTypeExtent;   //任务类型扩展
    bool bCanGiveUp;   //可否放弃
    bool bAwardLinkLevel;	//资源奖励是否等级相关
    UINT32 dwGuideType;	//探索任务引导类型，1为寻路完成，2为立即跳转完成

    UINT32 dwStarGroupID;	//星级任务组ID
    EStarType eStarType;	//任务星级

    UINT32 dwContentType;	//任务内容

    SIdxType oTriggerTarget;	//任务触发来源
    SIdxType oSubmitTarget;	//任务提交去处

    //任务描述
    string strTaskDesc;		//任务描述
    string strTaskPurpose;	//任务目的
    string strTaskFail;		//任务失败提示
    string strTaskFinish;	//任务完成提示

    //任务限制
    ELimitGender eLimitGender;		//性别限制
    //UINT16 wLimitReputeMin;		//声望限制
    //UINT16 wLimitReputeMax;
    //UINT16 wLimitJingJieMin;		//境界限制
    //UINT16 wLimitJingJieMax;
    vector<SMapArea> vecTrigger;	 //地图区域触发
    vector<SLimitProp> vecLimitProp; //属性限制
    UINT16 wLimitCampID;			 //声望阵营ID

    ELimitCamp eLimitCamp;			//阵营限制
    ELimitFamily eLimitFamily;		//家族公会限制
    UINT8 byRace;					//种族限制

    INT64 qwLimitDateFrom;  //日期限制
    INT64 qwLimitDateTo;

    UINT16 wLimitDayTimeFrom; //每日时间段限制，目前存储的为hour值
    UINT16 wLimitDayTimeTo;

    UINT8 byLimitPreTaskFlag;   //0, 全部完成；1，完成其一
    vector<UINT16> vecLimitPreTasks;  //前置任务列表
    vector<UINT32> vecLimitCareers;   //职业限制

    //任务过程
    UINT32 dwLimitTime;	//任务时间限制，0为不限时间
    vector<SIdxCount> vecItemGive;	//任务开始时给予的道具

    vector<SKillMonster> vecMonsterKill;	//杀怪
    vector<SCollectItem> vecItemCollect;	//收集
    UINT8 byProbeFlag;   //0, 探索全部；1，探索其一
    vector<SMapArea> vecProbe;			//探索
    //vector<SUseItem> vecUseItem;		//使用道具
    //vector<SUseSkill> vecUseSkill;	//使用技能

    typedef std::map<UINT16, SNpcTalk> TMapNpc2Talk;
    TMapNpc2Talk mapNpc2Talk;				//NPC对话
    vector<SIdxCount> vecGather;			//采集
    vector<SRoleProperty> vecRoleProps;		//成长_角色属性
    vector<SProcessAction> vecRoleActions;	//行为
    vector<SIdxCount> vecBuildings;			//建设_建筑
    vector<SIdxCount> vecTechnics;			//建设_科技

    //任务奖励
    vector<SAwardGeneral> vecAwardGeneral;	//一般奖励

    float fStarCoef;	//星级系数
    float fRingCoef;	//环系数
    vector<SIdxCountJob> vecMustAwardItem;	//必给道具
    vector<SIdxCountJob> vecOptAwardItem;	//选给道具

    //称号奖励
    vector<UINT32> vecAwardTitle;

    //属性奖励
    vector<SAwardProperty> vecAwardProp;//奖励_角色属性
    UINT16 wAwardPropCampID;   //奖励_声望属性对应的阵营ID
    string strAwardPropCampName;

    //佣兵奖励
    vector<SAwardMercen> vecAwardMercen;

    STaskConfig() : 
        wID(0),
        byLevel(0),
        eTaskType(eTaskConfNone), 
        bOpen(false), 
        bShare(false), 
        dwCharge(0), 
        dwRepeat(0), 
        eTaskTypeExtent(eTaskTypeExtent_normal),
        bCanGiveUp(false),
        bAwardLinkLevel(false),
        dwGuideType(0),
        dwStarGroupID(0),	
        eStarType(eStarNone), 
        dwContentType(0),

        //任务限制
        eLimitGender(eLimitGender_none),
        wLimitCampID(0),
        eLimitCamp(eLimitCamp_none),
        eLimitFamily(eLimitFamily_none),
        byRace(0),
        qwLimitDateFrom(0),
        qwLimitDateTo(0),
        wLimitDayTimeFrom(0),
        wLimitDayTimeTo(0),
        byLimitPreTaskFlag(0),

        //任务过程
        dwLimitTime(0), 
        byProbeFlag(0),

        //奖励
        fStarCoef(0), 
        fRingCoef(0),
        wAwardPropCampID(0)
        {
        }

    bool ParseXML(const string& strFilePath);
};
