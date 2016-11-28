/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    LogDataDefine.h
//  Purpose:      日志数据定义
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include <vector>
#include <string>
#include <memory>
#include "ServerDefine.h"
#include "Archive.h"
#ifdef PROT_USE_XML
#include "tinyxml.h"
#endif
#include "MailProt.h"

namespace NLogDataDefine
{

/////////////////////以下为类型定义/////////////////////
//副本操作
enum EDgnOpType
{
	EDgnOpType_CREATE, //副本创建
	EDgnOpType_PLAYERENTER, //玩家进入
	EDgnOpType_PLAYERLEAVE, //玩家退出
	EDgnOpType_FINISH, //副本完成
	EDgnOpType_DESTROY //副本销毁
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EDgnOpType);
bool EnumStrToVal(const char*, EDgnOpType&);
#endif //PROT_USE_XML

//获得物品/或者货币
enum ItemFrom
{
	ItemFrom_GM = 1, //GM指令里得到的物品
	ItemFrom_InLuaBox = 2, //lua脚本使用宝箱获得
	ItemFrom_System = 3, //系统奖励
	ItemFrom_EDgn = 4, //副本奖励
	ItemFrom_DujieAward = 5, //渡劫奖励
	ItemFrom_MonsterDrop = 6, //怪物掉落
	ItemFrom_YaMenAward = 7, //衙门每日奖励
	ItemFrom_BeastSoul = 8, //兽魂奖励
	ItemFrom_Gather = 9, //采集
	ItemFrom_Task = 10, //任务奖励
	ItemFrom_Mail = 11, //邮件
	ItemFrom_Mall = 12, //商城购买
	ItemFrom_DemonTower = 13, //锁妖塔
	ItemFrom_TripodAward = 14, //九疑鼎奖励
	ItemFrom_ArenaAward = 15, //斗剑奖励
	ItemFrom_RankAdoreAward = 16, //排行榜崇拜奖励
	ItemFrom_VIPAward = 17, //VIP礼包
	ItemFrom_YelloDiamondAward = 18, //黄钻礼包
	ItemFrom_FighterFind = 19, //刷将奖励
	ItemFrom_ExchangeItem = 20, //兑换物品
	ItemFrom_LevelPrizeAct = 21, //运营活动
	ItemFrom_Activity = 22, //活跃度
	ItemFrom_CittaStore = 23, //天书背包
	ItemFrom_UserDeptORPack = 24, //玩家仓库与背包道具交换、拆分、合并
	ItemFrom_ActiveTrump = 25, //法宝激活
	ItemFrom_MergeCitta = 26, //心法合成
	ItemFrom_BreakCitta = 27, //心法分解
	ItemFrom_HeroXinFaDisperse = 28, //散仙心法分解
	ItemFrom_PlayerXinFaDisperse = 29, //主将心法分解
	ItemFrom_NewCollection = 30, //收藏
	ItemFrom_NewAchieve = 31, //成就
	ItemFrom_EnergyBuy = 32, //购买精力
	ItemFrom_EnergyBuff = 33, //buffer增加精力
	ItemFrom_DemonTowerSeal = 34, //锁妖塔每日领取
	ItemFrom_DemonTowerPass = 35, //锁妖塔过关领取
	ItemFrom_Pend = 36, //延迟发放
	ItemFrom_Siting = 37, //双修
	ItemFrom_Recharge = 38, //充值
	ItemFrom_LangHuanBless = 39, //琅環福地
	ItemFrom_GroupTask = 40, //师门任务
	ItemFrom_SellItem = 41, //卖出物品
	ItemFrom_SignInAward = 42, //领取签到奖励礼包
	ItemFrom_ArenaBattle = 43, //斗剑历练奖励声望
	ItemFrom_CharInit = 44, //角色初始化获得
	ItemFrom_LoginPkg = 45, //累计登入获得
	ItemFrom_SevenDayTarget = 46, //7日目标活动
	ItemFrom_WonderActivity = 47, //精彩活动
	ItemFrom_PHP = 48, //客服后台操作
	ItemFrom_BattleArrayItem = 49, //破阵
	ItemFrom_TreasureHunt = 50, //寻宝
	ItemFrom_Beauty = 51, //美女系统
	ItemFrom_QQCoinExChange = 52, //QQ养成计划
	ItemFrom_Shushanweiwei = 53, //蜀山微微
	ItemFrom_ShushanFound = 54, //蜀山基金
	ItemFrom_CircleTask = 55, //环任务奖励
	ItemFrom_CircleTaskFinish = 56, //环任务全部完成奖励
	ItemFrom_MallChongZhi = 57, //商城充值活动奖励
	ItemFrom_Answer = 58, //答题活动
	ItemFrom_GuardEMei = 59, //守卫峨眉
	ItemFrom_InviteFriend = 60, //邀请好友
	ItemFrom_QQAlarm = 61, //QQAlarm奖励
	ItemFrom_GuildXihe = 62, //羲和神车奖励
	ItemFrom_Achievement = 63, //羲和神车奖励
	ItemFrom_LadderBattle = 64, //斗剑奖励资源
	ItemFrom_ExchangeMoney = 65, //货币兑换
	ItemFrom_Draw = 66, //求签
	ItemFrom_StarAward = 67, //副本星级领奖
	ItemFrom_GodMonster = 68, //天元神兽奖励
	ItemFrom_LingShan = 69, //秘境寻宝
	ItemFrom_GuildExchangedItem = 70, //帮派战物品兑换
	ItemFrom_MoneyTree = 71, //摇钱树
	ItemFrom_OffStone = 72, //取下宝石
	ItemFrom_MergeStone = 73, //宝石合成
	ItemFrom_Lottery = 74, //抽奖
	ItemFrom_RegisterSevenDaysDis = 75, //注册七天折扣豪礼大回馈
	ItemFrom_SecondRechargeAward = 76, //二次充值礼包
	ItemFrom_Mall_NoGold = 77, //商城购买非仙石
	ItemFrom_ETrumpStrength = 78, //装备法宝强化
	ItemFrom_ETrumpXiLian = 79, //装备法宝洗练
	ItemFrom_BreakEquipTrump = 80, //分解装备法宝
	ItemFrom_MergeEquipTrump = 81, //合成装备法宝
	ItemFrom_WearEquipTrump = 82, //穿戴装备法宝
	ItemFrom_TakeOffEquipTrump = 83, //卸下装备法宝
	ItemFrom_ShengLing = 84, //圣陵
	ItemFrom_Fenbaoyan = 85, //分宝岩
	ItemFrom_Feedback = 86 //消费回馈
};

#ifdef PROT_USE_XML
const char* EnumValToStr(ItemFrom);
bool EnumStrToVal(const char*, ItemFrom&);
#endif //PROT_USE_XML
const char* GetDescription(ItemFrom);

//删除物品/扣除货币
enum ItemTo
{
	ItemTo_Sell = 5000, //出售给系统
	ItemTo_GM = 5001, //GM指令里删除物品
	ItemTo_UseItem = 5002, //物品使用
	ItemTo_BeastSlots = 5003, //激活兽魂
	ItemTo_CommitDujieTask = 5004, //提交渡劫任务消耗
	ItemTo_TripodMakeFire = 5005, //九疑鼎祈火
	ItemTo_TripodSpeed = 5006, //九疑鼎道具入鼎
	ItemTo_TripodActive = 5007, //九疑鼎激活消耗
	ItemTo_TripodUpgrade = 5008, //九疑鼎升级消耗
	ItemTo_DemonTower = 5009, //锁妖塔消耗
	ItemTo_ArenaFlush = 5010, //斗剑刷将
	ItemTo_ArenaClearCD = 5011, //清除斗剑CD
	ItemTo_ArenaWirship = 5012, //斗剑膜拜
	ItemTo_ArenaBuyTimes = 5013, //斗剑购买挑战次数
	ItemTo_ArenaClearLadderCD = 5014, //斗剑天梯cd清除
	ItemTo_GuildDonate = 5015, //帮派捐献
	ItemTo_GuildWorship = 5016, //帮派供奉
	ItemTo_MergeCitta = 5017, //天书使用、分解、穿戴
	ItemTo_UserDeptORPack = 5018, //玩家仓库与背包道具交换、拆分、合并
	ItemTo_GatherCond = 5019, //玩家收集消耗
	ItemTo_Task = 5020, //任务消耗
	ItemTo_TrumpActive = 5021, //主将法宝激活消耗
	ItemTo_TrumpUpgrade = 5022, //主将法宝祭炼升级消耗
	ItemTo_TrumpEvolve = 5023, //主将法宝升阶消耗
	ItemTo_LearnXinFa = 5024, //学习心法消耗
	ItemTo_ZodTrumpUpgrade = 5025, //散仙本命法宝祭炼升级消耗
	ItemTo_EquipUpgrade = 5026, //装备升级消耗
	ItemTo_FashionUpgrade = 5027, //时装升级消耗
	ItemTo_FashionActive = 5028, //时装激活消耗
	ItemTo_HorseActive = 5029, //坐骑激活消耗
	ItemTo_HorseUpgrade = 5030, //坐骑升级消耗
	ItemTo_HeroInstinct = 5031, //散仙血脉激活消耗
	ItemTo_TalentActive = 5032, //天赋激活消耗
	ItemTo_FormationActive = 5033, //阵型激活消耗
	ItemTo_PetActive = 5034, //宠物激活消耗
	ItemTo_PetLvlUp = 5035, //宠物升级消耗
	ItemTo_Recruit = 5036, //将领招募消耗
	ItemTo_ExchangeItem = 5037, //兑换物品消耗
	ItemTo_FlushTask = 5038, //刷新师门任务
	ItemTo_BuyTask = 5039, //购买师门任务
	ItemTo_YaMenFlushTask = 5040, //刷新衙门任务
	ItemTo_YaMenBuyTask = 5041, //购买衙门任务
	ItemTo_HeroShift = 5042, //散仙转移
	ItemTo_HeroCuiTiUpgrade = 5043, //散仙粹体升级
	ItemTo_FighterLuckyExchange = 5044, //散仙兑换
	ItemTo_FighterSearch = 5045, //散仙搜索
	ItemTo_FighterTaoismUpgrade = 5046, //道术升级
	ItemTo_TaskForGroupAward = 5047, //师门任务领奖
	ItemTo_TaskForYaMenAward = 5048, //衙门任务领奖
	ItemTo_FigtherToOther = 5049, //发起战斗
	ItemTo_ExpandStore = 5050, //扩展背包
	ItemTo_BuyGuildSkill = 5051, //购买工会战技能
	ItemTo_SweepingSpeedUp = 5052, //扫荡加速
	ItemTo_EquipIntensify = 5053, //装备强化
	ItemTo_AttachSpirit = 5054, //装备注灵
	ItemTo_MallBuy = 5055, //商城购买
	ItemTo_HeroLevelUpgrade = 5056, //散仙升级
	ItemTo_HeroSkillLevelUpgrade = 5057, //散仙天赋技能升级
	ItemTo_HeroXinFaUpgrade = 5058, //散仙心法升级
	ItemTo_HeroSkillUpgrade = 5059, //散仙技能升级
	ItemTo_PlayerXinFaUpgrade = 5060, //玩家心法升级
	ItemTo_OpenVIP = 5061, //开启vip
	ItemTo_OpenFriendVIP = 5062, //给好友开启vip
	ItemTo_BuyAction = 5063, //购买行动力
	ItemTo_ConsumeAction = 5064, //副本或扫荡消耗
	ItemTo_ZodTrump = 5065, //法宝升级
	ItemTo_BattleBuySkill = 5066, //论剑购买技能
	ItemTo_SoulSpaceUpgrade = 5067, //魄空间升级
	ItemTo_WorldBossRelive = 5068, //世界boss复活
	ItemTo_WorldBossBuyStrength = 5069, //世界boss购买buffer
	ItemTo_WorldAttack = 5070, //世界boss购买立即攻击
	ItemTo_PlayerAdvanceUpgrade = 5071, //主将技能进阶
	ItemTo_PlayerSkillUpgrade = 5072, //主将技能升级
	ItemTo_RuneUpgrade = 5073, //主将技能熔炼
	ItemTo_UpgradeBeastSoul = 5074, //兽魂
	ItemTo_PHP = 5075, //客服后台操作
	ItemTo_FighterCombination = 5076, //散仙组合升级消耗
	ItemTo_BattleArrayItem = 5077, //破阵
	ItemTo_TreasureHunt = 5078, //一键寻宝
	ItemTo_Beauty = 5079, //美女系统
	ItemTo_ByOpenShipTimes = 5080, //购买运船次数
	ItemTo_ByRobShipTimes = 5081, //购买抢船次数
	ItemTo_ByReFlushShipTimes = 5082, //购买刷船次数
	ItemTo_ShushanFound = 5083, //购买蜀山基金
	ItemTo_CircleOneKey = 5084, //环任务立即完成当前
	ItemTo_CircleOneKeyAll = 5085, //环任务立即完成所有
	ItemTo_GetShipOneKey = 5086, //vip召唤船只
	ItemTo_FinishShipOneKey = 5087, //一键完成运船
	ItemTo_CircleUpStar = 5088, //环任务升星
	ItemTo_BuyHeroDgn = 5089, //购买英雄副本次数
	ItemTo_BuyLiXianDgn = 5090, //购买历险副本次数
	ItemTo_BuyEntryNum = 5091, //购买守卫峨眉进入次数
	ItemTo_GuildXihe = 5092, //羲和神车消耗
	ItemTo_BuyLadderTimes = 5093, //购买天梯挑战次数
	ItemTo_ExchangeMoney = 5094, //货币兑换
	ItemTo_Draw = 5095, //求签
	ItemTo_FighterDismiss = 5096, //散功消耗
	ItemTo_LingShan = 5097, //秘境寻宝
	ItemTo_GodMonster = 5098, //天元神兽消耗
	ItemTo_DujieConsume = 5099, //散仙渡劫消耗
	ItemTo_MoneyTree = 5100, //摇钱树消耗
	ItemTo_WareStone = 5101, //装备宝石
	ItemTo_MergeStone = 5102, //合成消耗
	ItemTo_RegisterSevenDaysDis = 5103, //注册七天折扣豪礼大回馈消耗
	ItemTo_MallBuy_NoGold = 5104, //商城购买_礼卷
	ItemTo_NewGuildBattleDead = 5105, //灵山买活
	ItemTo_NewGuildBattleBuyPuppet = 5106, //购买傀儡
	ItemTo_Lottery = 5106, //抽奖
	ItemTo_BreakCitta = 5107, //心法分解
	ItemTo_FighterBuyLYQ = 5108, //邀仙居——李英琼
	ItemTo_FighterBuyQLY = 5109, //邀仙居——齐灵云
	ItemTo_ETrumpStrength = 5110, //装备法宝强化
	ItemTo_ETrumpXiLian = 5111, //装备法宝洗练
	ItemTo_BreakEquipTrump = 5112, //分解装备法宝
	ItemTo_MergeEquipTrump = 5113, //合成装备法宝
	ItemTo_WearEquipTrump = 5114, //穿戴装备法宝
	ItemTo_TakeOffEquipTrump = 5115, //卸下装备法宝
	ItemTo_ShengLing = 5116, //圣陵
	ItemTo_Fenbaoyan = 5117, //分宝岩
	ItemTo_Feedback = 5118 //消费回馈
};

#ifdef PROT_USE_XML
const char* EnumValToStr(ItemTo);
bool EnumStrToVal(const char*, ItemTo&);
#endif //PROT_USE_XML
const char* GetDescription(ItemTo);

//散仙操作类型
enum EFighterOptType
{
	eOptType_Recurit, //招募
	eOptType_Upgrade, //升级
	eOptType_CuiTi, //猝体
	eOptType_FaBao, //法宝
	eOptType_Skill, //技能
	eOptType_Shift, //CuiTi转移
	eOptType_XinFa, //心法
	eOptType_PassiveSkill //被动技能
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EFighterOptType);
bool EnumStrToVal(const char*, EFighterOptType&);
#endif //PROT_USE_XML

//结构体：LogDataBase的继承体系类型
enum EType_LogDataBase
{
	eType_LogDataBase, //类型：LogDataBase
	eType_SDgnLog, //类型：SDgnLog
	eType_SRegisterLog, //类型：SRegisterLog
	eType_SLoginLog, //类型：SLoginLog
	eType_SItemCoursesLog, //类型：SItemCoursesLog
	eType_SMoneyCoursesLog, //类型：SMoneyCoursesLog
	eType_SMailLog, //类型：SMailLog
	eType_SPetLog, //类型：SPetLog
	eType_SDujieLog, //类型：SDujieLog
	eType_SFashionLog, //类型：SFashionLog
	eType_SFighterLog, //类型：SFighterLog
	eType_SHorseLog, //类型：SHorseLog
	eType_STrumpLog, //类型：STrumpLog
	eType_SBeautyLog, //类型：SBeautyLog
	eType_SEquipLog, //类型：SEquipLog
	eType_SGuildLog, //类型：SGuildLog
	eType_SSendMoneyLog, //类型：SSendMoneyLog
	eType_SSendItemLog, //类型：SSendItemLog
	eType_SMailOpLog, //类型：SMailOpLog
	eType_SForbiddenLog, //类型：SForbiddenLog
	eType_SForbiddenChatLog, //类型：SForbiddenChatLog
	eType_SGlobalSendItemLog, //类型：SGlobalSendItemLog
	eType_SQuesOptLog, //类型：SQuesOptLog
	eType_SSendMailLog, //类型：SSendMailLog
	eType_SVIPSendLog, //类型：SVIPSendLog
	eType_SActivityOpenLog, //类型：SActivityOpenLog
	eType_SDiscountItemLog, //类型：SDiscountItemLog
	eType_SLevelChangeLog //类型：SLevelChangeLog
};

//日志数据基类
struct LogDataBase
{
	LogDataBase();
	virtual ~LogDataBase() { }
	DEF_NEW_DELETE(LogDataBase); //使用对象池
	virtual EType_LogDataBase GetClassType() const { return eType_LogDataBase; }
};

typedef std::shared_ptr<LogDataBase> LogDataBasePtr;
typedef std::weak_ptr<LogDataBase> LogDataBaseWtr;
typedef std::vector<LogDataBasePtr> TVecLogDataBase;

//父类：LogDataBase的辅助结构体
struct LogDataBase_Wrapper
{
	LogDataBasePtr ptr;
	LogDataBase_Wrapper(const LogDataBasePtr& ptr_ = NULL) : ptr(ptr_) { }
};

//副本日志
struct SDgnLog : public LogDataBase
{
	EDgnOpType eOpType; //操作类型
	UINT16 wDgnType; //副本类型
	UINT64 qwDgnInsID; //副本实例ID
	UINT64 qwUserID; //操作者，0表示系统

	SDgnLog();
	DEF_NEW_DELETE(SDgnLog); //使用对象池
	virtual EType_LogDataBase GetClassType() const { return eType_SDgnLog; }
};

typedef std::shared_ptr<SDgnLog> SDgnLogPtr;
typedef std::weak_ptr<SDgnLog> SDgnLogWtr;
typedef std::vector<SDgnLogPtr> TVecDgnLog;

//注册日志
struct SRegisterLog : public LogDataBase
{
	UINT32 serverId; //服务器ID
	UINT64 playerId; //玩家ID
	std::string playerName; //玩家名字

	SRegisterLog();
#ifdef __GNUG__
	SRegisterLog(const SRegisterLog& src) = default; //默认拷贝构造函数
	SRegisterLog& operator=(const SRegisterLog& rhs) = default; //默认赋值操作符
#endif
	SRegisterLog(SRegisterLog&& src); //转移构造函数
	SRegisterLog& operator=(SRegisterLog&& rhs); //转移赋值操作符
	DEF_NEW_DELETE(SRegisterLog); //使用对象池
	virtual EType_LogDataBase GetClassType() const { return eType_SRegisterLog; }
};

typedef std::shared_ptr<SRegisterLog> SRegisterLogPtr;
typedef std::weak_ptr<SRegisterLog> SRegisterLogWtr;
typedef std::vector<SRegisterLogPtr> TVecRegisterLog;

//登录日志
struct SLoginLog : public LogDataBase
{
	UINT32 serverId; //服务器ID
	UINT64 playerId; //玩家ID
	UINT32 loginTime; //登录时间
	std::string loginIp; //登录IP
	UINT32 logoutTime; //离开时间

	SLoginLog();
#ifdef __GNUG__
	SLoginLog(const SLoginLog& src) = default; //默认拷贝构造函数
	SLoginLog& operator=(const SLoginLog& rhs) = default; //默认赋值操作符
#endif
	SLoginLog(SLoginLog&& src); //转移构造函数
	SLoginLog& operator=(SLoginLog&& rhs); //转移赋值操作符
	DEF_NEW_DELETE(SLoginLog); //使用对象池
	virtual EType_LogDataBase GetClassType() const { return eType_SLoginLog; }
};

typedef std::shared_ptr<SLoginLog> SLoginLogPtr;
typedef std::weak_ptr<SLoginLog> SLoginLogWtr;
typedef std::vector<SLoginLogPtr> TVecLoginLog;

//道具流水日志
struct SItemCoursesLog : public LogDataBase
{
	UINT32 serverId; //服务器ID
	UINT64 playerId; //玩家ID
	std::string strOpenId; //玩家的openId
	UINT64 qwInstId; //物品流水ID
	UINT32 itemId; //物品ID
	UINT32 itemNum; //物品使用or增加数量
	UINT16 fromto; //物品出处id
	std::string fromtoStr; //物品出处字符描述
	UINT32 happenedTime; //时间

	SItemCoursesLog();
#ifdef __GNUG__
	SItemCoursesLog(const SItemCoursesLog& src) = default; //默认拷贝构造函数
	SItemCoursesLog& operator=(const SItemCoursesLog& rhs) = default; //默认赋值操作符
#endif
	SItemCoursesLog(SItemCoursesLog&& src); //转移构造函数
	SItemCoursesLog& operator=(SItemCoursesLog&& rhs); //转移赋值操作符
	DEF_NEW_DELETE(SItemCoursesLog); //使用对象池
	virtual EType_LogDataBase GetClassType() const { return eType_SItemCoursesLog; }
};

typedef std::shared_ptr<SItemCoursesLog> SItemCoursesLogPtr;
typedef std::weak_ptr<SItemCoursesLog> SItemCoursesLogWtr;
typedef std::vector<SItemCoursesLogPtr> TVecItemCoursesLog;

//货币流水日志
struct SMoneyCoursesLog : public LogDataBase
{
	UINT32 serverId; //服务器ID
	UINT64 playerId; //玩家ID
	std::string strOpenId; //玩家的openId
	UINT8 moneyType; //货币类型ID
	UINT32 moneyNum; //货币使用or增加数量
	UINT32 totalNum; //当前货币总数量
	UINT16 fromto; //物品出处id
	std::string fromtoStr; //物品出处字符描述
	UINT32 happenedTime; //时间
	UINT8 bIsFreeGold; //是否使用免费仙石

	SMoneyCoursesLog();
#ifdef __GNUG__
	SMoneyCoursesLog(const SMoneyCoursesLog& src) = default; //默认拷贝构造函数
	SMoneyCoursesLog& operator=(const SMoneyCoursesLog& rhs) = default; //默认赋值操作符
#endif
	SMoneyCoursesLog(SMoneyCoursesLog&& src); //转移构造函数
	SMoneyCoursesLog& operator=(SMoneyCoursesLog&& rhs); //转移赋值操作符
	DEF_NEW_DELETE(SMoneyCoursesLog); //使用对象池
	virtual EType_LogDataBase GetClassType() const { return eType_SMoneyCoursesLog; }
};

typedef std::shared_ptr<SMoneyCoursesLog> SMoneyCoursesLogPtr;
typedef std::weak_ptr<SMoneyCoursesLog> SMoneyCoursesLogWtr;
typedef std::vector<SMoneyCoursesLogPtr> TVecMoneyCoursesLog;

//邮件流水日志
struct SMailLog : public LogDataBase
{
	UINT32 dwServerId; //服务器ID
	UINT64 qwPlayerId; //玩家ID
	UINT64 qwMailId; //邮件ID
	UINT8 byType; //邮件类型
	std::string strTitle; //邮件标题
	std::string strText; //邮件正文
	std::string strAttach; //邮件附件
	UINT8 byState; //邮件状态
	UINT32 dwRevTime; //操作时间
	UINT32 dwDelTime; //删除时间

	SMailLog();
#ifdef __GNUG__
	SMailLog(const SMailLog& src) = default; //默认拷贝构造函数
	SMailLog& operator=(const SMailLog& rhs) = default; //默认赋值操作符
#endif
	SMailLog(SMailLog&& src); //转移构造函数
	SMailLog& operator=(SMailLog&& rhs); //转移赋值操作符
	DEF_NEW_DELETE(SMailLog); //使用对象池
	virtual EType_LogDataBase GetClassType() const { return eType_SMailLog; }
};

typedef std::shared_ptr<SMailLog> SMailLogPtr;
typedef std::weak_ptr<SMailLog> SMailLogWtr;
typedef std::vector<SMailLogPtr> TVecMailLog;

//阵灵日志
struct SPetLog : public LogDataBase
{
	UINT32 dwServerId; //服务器ID
	UINT64 qwPlayerId; //玩家ID
	std::string sName; //阵灵名字
	UINT8 byOpType; //操作类型
	UINT16 wLevel; //阵灵等级
	UINT32 happenedTime; //时间

	SPetLog();
#ifdef __GNUG__
	SPetLog(const SPetLog& src) = default; //默认拷贝构造函数
	SPetLog& operator=(const SPetLog& rhs) = default; //默认赋值操作符
#endif
	SPetLog(SPetLog&& src); //转移构造函数
	SPetLog& operator=(SPetLog&& rhs); //转移赋值操作符
	DEF_NEW_DELETE(SPetLog); //使用对象池
	virtual EType_LogDataBase GetClassType() const { return eType_SPetLog; }
};

typedef std::shared_ptr<SPetLog> SPetLogPtr;
typedef std::weak_ptr<SPetLog> SPetLogWtr;
typedef std::vector<SPetLogPtr> TVecPetLog;

//渡劫日志
struct SDujieLog : public LogDataBase
{
	UINT32 dwServerId; //服务器ID
	UINT64 qwPlayerId; //玩家ID
	UINT16 wFighterId; //散仙ID
	std::string sFighterName; //散仙名字
	std::string sPeriodName; //渡劫阶段
	UINT32 dwExp; //当前渡劫经验值
	UINT32 happenedTime; //时间

	SDujieLog();
#ifdef __GNUG__
	SDujieLog(const SDujieLog& src) = default; //默认拷贝构造函数
	SDujieLog& operator=(const SDujieLog& rhs) = default; //默认赋值操作符
#endif
	SDujieLog(SDujieLog&& src); //转移构造函数
	SDujieLog& operator=(SDujieLog&& rhs); //转移赋值操作符
	DEF_NEW_DELETE(SDujieLog); //使用对象池
	virtual EType_LogDataBase GetClassType() const { return eType_SDujieLog; }
};

typedef std::shared_ptr<SDujieLog> SDujieLogPtr;
typedef std::weak_ptr<SDujieLog> SDujieLogWtr;
typedef std::vector<SDujieLogPtr> TVecDujieLog;

//时装日志
struct SFashionLog : public LogDataBase
{
	UINT32 dwServerId; //服务器ID
	UINT64 qwUserId; //玩家ID
	UINT16 wId; //时装ID
	std::string sName; //时装名字
	UINT32 dwLevel; //时装等级
	UINT32 happenedTime; //时间

	SFashionLog();
#ifdef __GNUG__
	SFashionLog(const SFashionLog& src) = default; //默认拷贝构造函数
	SFashionLog& operator=(const SFashionLog& rhs) = default; //默认赋值操作符
#endif
	SFashionLog(SFashionLog&& src); //转移构造函数
	SFashionLog& operator=(SFashionLog&& rhs); //转移赋值操作符
	DEF_NEW_DELETE(SFashionLog); //使用对象池
	virtual EType_LogDataBase GetClassType() const { return eType_SFashionLog; }
};

typedef std::shared_ptr<SFashionLog> SFashionLogPtr;
typedef std::weak_ptr<SFashionLog> SFashionLogWtr;
typedef std::vector<SFashionLogPtr> TVecFashionLog;

//散仙日志
struct SFighterLog : public LogDataBase
{
	UINT32 dwServerId; //服务器ID
	UINT64 qwUserId; //玩家ID
	UINT16 wFighterId; //散仙ID
	std::string sName; //散仙名字
	UINT16 wLevel; //散仙等级
	UINT8 byQuality; //散仙品质
	EFighterOptType eOptType; //操作类型1
	UINT32 dwType; //操作类型2(本命法宝时，0表示法宝，1表示法宝技能)
	UINT64 qwResult; //操作结果(本命法宝时：前32位表示ID，后32为表示等级
	UINT32 happenedTime; //时间

	SFighterLog();
#ifdef __GNUG__
	SFighterLog(const SFighterLog& src) = default; //默认拷贝构造函数
	SFighterLog& operator=(const SFighterLog& rhs) = default; //默认赋值操作符
#endif
	SFighterLog(SFighterLog&& src); //转移构造函数
	SFighterLog& operator=(SFighterLog&& rhs); //转移赋值操作符
	DEF_NEW_DELETE(SFighterLog); //使用对象池
	virtual EType_LogDataBase GetClassType() const { return eType_SFighterLog; }
};

typedef std::shared_ptr<SFighterLog> SFighterLogPtr;
typedef std::weak_ptr<SFighterLog> SFighterLogWtr;
typedef std::vector<SFighterLogPtr> TVecFighterLog;

//坐骑日志
struct SHorseLog : public LogDataBase
{
	UINT32 dwServerId; //服务器ID
	UINT64 qwUserId; //玩家ID
	UINT32 dwID; //坐骑ID
	std::string sName; //坐骑名字
	UINT32 dwLevel; //坐骑等级
	UINT32 happenedTime; //时间

	SHorseLog();
#ifdef __GNUG__
	SHorseLog(const SHorseLog& src) = default; //默认拷贝构造函数
	SHorseLog& operator=(const SHorseLog& rhs) = default; //默认赋值操作符
#endif
	SHorseLog(SHorseLog&& src); //转移构造函数
	SHorseLog& operator=(SHorseLog&& rhs); //转移赋值操作符
	DEF_NEW_DELETE(SHorseLog); //使用对象池
	virtual EType_LogDataBase GetClassType() const { return eType_SHorseLog; }
};

typedef std::shared_ptr<SHorseLog> SHorseLogPtr;
typedef std::weak_ptr<SHorseLog> SHorseLogWtr;
typedef std::vector<SHorseLogPtr> TVecHorseLog;

//法宝日志
struct STrumpLog : public LogDataBase
{
	UINT32 dwServerId; //服务器ID
	UINT64 qwUserId; //玩家ID
	UINT16 wID; //法宝ID
	std::string sName; //法宝名字
	UINT32 dwSkillId; //法宝技能等级
	UINT32 dwLevel; //法宝品节
	UINT32 dwExp; //法宝当前祭炼值
	UINT32 happenedTime; //时间

	STrumpLog();
#ifdef __GNUG__
	STrumpLog(const STrumpLog& src) = default; //默认拷贝构造函数
	STrumpLog& operator=(const STrumpLog& rhs) = default; //默认赋值操作符
#endif
	STrumpLog(STrumpLog&& src); //转移构造函数
	STrumpLog& operator=(STrumpLog&& rhs); //转移赋值操作符
	DEF_NEW_DELETE(STrumpLog); //使用对象池
	virtual EType_LogDataBase GetClassType() const { return eType_STrumpLog; }
};

typedef std::shared_ptr<STrumpLog> STrumpLogPtr;
typedef std::weak_ptr<STrumpLog> STrumpLogWtr;
typedef std::vector<STrumpLogPtr> TVecTrumpLog;

//美女日志
struct SBeautyLog : public LogDataBase
{
	UINT32 dwServerId; //服务器ID
	UINT64 qwUserId; //玩家ID
	UINT16 wID; //美女ID
	std::string sName; //美女名字
	UINT16 wLevel; //亲密等级
	UINT32 dwExp; //亲密度
	UINT32 happenedTime; //时间

	SBeautyLog();
#ifdef __GNUG__
	SBeautyLog(const SBeautyLog& src) = default; //默认拷贝构造函数
	SBeautyLog& operator=(const SBeautyLog& rhs) = default; //默认赋值操作符
#endif
	SBeautyLog(SBeautyLog&& src); //转移构造函数
	SBeautyLog& operator=(SBeautyLog&& rhs); //转移赋值操作符
	DEF_NEW_DELETE(SBeautyLog); //使用对象池
	virtual EType_LogDataBase GetClassType() const { return eType_SBeautyLog; }
};

typedef std::shared_ptr<SBeautyLog> SBeautyLogPtr;
typedef std::weak_ptr<SBeautyLog> SBeautyLogWtr;
typedef std::vector<SBeautyLogPtr> TVecBeautyLog;

//装备日志
struct SEquipLog : public LogDataBase
{
	UINT32 dwServerId; //服务器ID
	UINT64 qwUserId; //玩家ID
	UINT32 dwID; //装备ID
	std::string sName; //装备名字
	UINT32 dwLevel; //装备等级
	UINT32 happenedTime; //时间

	SEquipLog();
#ifdef __GNUG__
	SEquipLog(const SEquipLog& src) = default; //默认拷贝构造函数
	SEquipLog& operator=(const SEquipLog& rhs) = default; //默认赋值操作符
#endif
	SEquipLog(SEquipLog&& src); //转移构造函数
	SEquipLog& operator=(SEquipLog&& rhs); //转移赋值操作符
	DEF_NEW_DELETE(SEquipLog); //使用对象池
	virtual EType_LogDataBase GetClassType() const { return eType_SEquipLog; }
};

typedef std::shared_ptr<SEquipLog> SEquipLogPtr;
typedef std::weak_ptr<SEquipLog> SEquipLogWtr;
typedef std::vector<SEquipLogPtr> TVecEquipLog;

//帮会日志
struct SGuildLog : public LogDataBase
{
	UINT32 dwServerId; //服务器ID
	UINT64 qwGuildId; //帮派ID
	std::string sName; //帮派名字
	UINT8 byLevel; //帮派等级
	UINT32 dwCount; //帮派人员
	UINT8 byTowerLvl; //神谕塔等级
	UINT8 byStoreLvl; //仓库等级
	UINT8 byHourseLvl; //剑阁等级
	UINT32 dwScore; //帮派积分
	UINT32 dwMoney; //帮派金钱
	UINT32 happenedTime; //创建时间
	UINT8 byOptType; //数据库操作 (1创建，其他Update)
	UINT8 byOptParam; //附加参数(1加入2加钱3加积分4神谕塔升级5仓库升级6剑阁升级)

	SGuildLog();
#ifdef __GNUG__
	SGuildLog(const SGuildLog& src) = default; //默认拷贝构造函数
	SGuildLog& operator=(const SGuildLog& rhs) = default; //默认赋值操作符
#endif
	SGuildLog(SGuildLog&& src); //转移构造函数
	SGuildLog& operator=(SGuildLog&& rhs); //转移赋值操作符
	DEF_NEW_DELETE(SGuildLog); //使用对象池
	virtual EType_LogDataBase GetClassType() const { return eType_SGuildLog; }
};

typedef std::shared_ptr<SGuildLog> SGuildLogPtr;
typedef std::weak_ptr<SGuildLog> SGuildLogWtr;
typedef std::vector<SGuildLogPtr> TVecGuildLog;

//发送货币日志
struct SSendMoneyLog : public LogDataBase
{
	std::string strSendName; //发送人
	UINT8 byStatus; //状态
	UINT32 dwServerId; //大区
	UINT64 qwUserId; //玩家ID
	UINT8 byMoneyType; //货币类型
	UINT32 dwMoneyValue; //发送数量
	std::string strReason; //发送理由
	UINT32 dwOpTime; //操作时间

	SSendMoneyLog();
#ifdef __GNUG__
	SSendMoneyLog(const SSendMoneyLog& src) = default; //默认拷贝构造函数
	SSendMoneyLog& operator=(const SSendMoneyLog& rhs) = default; //默认赋值操作符
#endif
	SSendMoneyLog(SSendMoneyLog&& src); //转移构造函数
	SSendMoneyLog& operator=(SSendMoneyLog&& rhs); //转移赋值操作符
	DEF_NEW_DELETE(SSendMoneyLog); //使用对象池
	virtual EType_LogDataBase GetClassType() const { return eType_SSendMoneyLog; }
};

typedef std::shared_ptr<SSendMoneyLog> SSendMoneyLogPtr;
typedef std::weak_ptr<SSendMoneyLog> SSendMoneyLogWtr;
typedef std::vector<SSendMoneyLogPtr> TVecSendMoneyLog;

//发送物品日志
struct SSendItemLog : public LogDataBase
{
	std::string strSendName; //发送人
	UINT8 byStatus; //状态
	UINT32 dwServerId; //大区
	UINT64 qwUserId; //玩家ID
	std::string strTitle; //标题
	std::string strBody; //内容
	std::string strItemList; //物品列表
	std::string strReason; //发送理由
	UINT32 dwOpTime; //操作时间

	SSendItemLog();
#ifdef __GNUG__
	SSendItemLog(const SSendItemLog& src) = default; //默认拷贝构造函数
	SSendItemLog& operator=(const SSendItemLog& rhs) = default; //默认赋值操作符
#endif
	SSendItemLog(SSendItemLog&& src); //转移构造函数
	SSendItemLog& operator=(SSendItemLog&& rhs); //转移赋值操作符
	DEF_NEW_DELETE(SSendItemLog); //使用对象池
	virtual EType_LogDataBase GetClassType() const { return eType_SSendItemLog; }
};

typedef std::shared_ptr<SSendItemLog> SSendItemLogPtr;
typedef std::weak_ptr<SSendItemLog> SSendItemLogWtr;
typedef std::vector<SSendItemLogPtr> TVecSendItemLog;

//邮件操作日志
struct SMailOpLog : public LogDataBase
{
	std::string strSendName; //操作人
	UINT8 byStatus; //状态
	UINT32 dwServerId; //大区
	UINT64 qwUserId; //玩家ID
	UINT8 byMailOpType; //邮件操作类型
	UINT32 dwOpTime; //操作时间

	SMailOpLog();
#ifdef __GNUG__
	SMailOpLog(const SMailOpLog& src) = default; //默认拷贝构造函数
	SMailOpLog& operator=(const SMailOpLog& rhs) = default; //默认赋值操作符
#endif
	SMailOpLog(SMailOpLog&& src); //转移构造函数
	SMailOpLog& operator=(SMailOpLog&& rhs); //转移赋值操作符
	DEF_NEW_DELETE(SMailOpLog); //使用对象池
	virtual EType_LogDataBase GetClassType() const { return eType_SMailOpLog; }
};

typedef std::shared_ptr<SMailOpLog> SMailOpLogPtr;
typedef std::weak_ptr<SMailOpLog> SMailOpLogWtr;
typedef std::vector<SMailOpLogPtr> TVecMailOpLog;

//封号*解封记录
struct SForbiddenLog : public LogDataBase
{
	std::string strSendName; //操作人
	UINT8 byStatus; //状态
	UINT32 dwServerId; //大区
	UINT64 qwUserId; //玩家ID
	UINT8 byOpType; //操作类型
	UINT32 dwForbidTime; //封禁时间
	std::string strReason; //理由
	UINT32 dwOpTime; //操作时间

	SForbiddenLog();
#ifdef __GNUG__
	SForbiddenLog(const SForbiddenLog& src) = default; //默认拷贝构造函数
	SForbiddenLog& operator=(const SForbiddenLog& rhs) = default; //默认赋值操作符
#endif
	SForbiddenLog(SForbiddenLog&& src); //转移构造函数
	SForbiddenLog& operator=(SForbiddenLog&& rhs); //转移赋值操作符
	DEF_NEW_DELETE(SForbiddenLog); //使用对象池
	virtual EType_LogDataBase GetClassType() const { return eType_SForbiddenLog; }
};

typedef std::shared_ptr<SForbiddenLog> SForbiddenLogPtr;
typedef std::weak_ptr<SForbiddenLog> SForbiddenLogWtr;
typedef std::vector<SForbiddenLogPtr> TVecForbiddenLog;

//禁言*解禁记录
struct SForbiddenChatLog : public LogDataBase
{
	std::string strSendName; //操作人
	UINT8 byStatus; //状态
	UINT32 dwServerId; //大区
	UINT64 qwUserId; //玩家ID
	UINT8 byOpType; //操作类型
	UINT32 dwForbidTime; //封禁时间
	std::string strReason; //理由
	UINT32 dwOpTime; //操作时间

	SForbiddenChatLog();
#ifdef __GNUG__
	SForbiddenChatLog(const SForbiddenChatLog& src) = default; //默认拷贝构造函数
	SForbiddenChatLog& operator=(const SForbiddenChatLog& rhs) = default; //默认赋值操作符
#endif
	SForbiddenChatLog(SForbiddenChatLog&& src); //转移构造函数
	SForbiddenChatLog& operator=(SForbiddenChatLog&& rhs); //转移赋值操作符
	DEF_NEW_DELETE(SForbiddenChatLog); //使用对象池
	virtual EType_LogDataBase GetClassType() const { return eType_SForbiddenChatLog; }
};

typedef std::shared_ptr<SForbiddenChatLog> SForbiddenChatLogPtr;
typedef std::weak_ptr<SForbiddenChatLog> SForbiddenChatLogWtr;
typedef std::vector<SForbiddenChatLogPtr> TVecForbiddenChatLog;

//发送物品日志
struct SGlobalSendItemLog : public LogDataBase
{
	std::string strSendName; //发送人
	UINT8 byStatus; //状态
	UINT32 dwServerId; //大区
	UINT64 qwUserId; //玩家ID
	UINT32 dwGold; //仙石
	UINT32 dwCoupon; //礼卷
	UINT32 dwSliver; //银币
	UINT32 dwHonor; //荣誉
	std::string strItemList; //物品列表
	std::string strReason; //理由
	UINT32 dwOpTime; //操作时间

	SGlobalSendItemLog();
#ifdef __GNUG__
	SGlobalSendItemLog(const SGlobalSendItemLog& src) = default; //默认拷贝构造函数
	SGlobalSendItemLog& operator=(const SGlobalSendItemLog& rhs) = default; //默认赋值操作符
#endif
	SGlobalSendItemLog(SGlobalSendItemLog&& src); //转移构造函数
	SGlobalSendItemLog& operator=(SGlobalSendItemLog&& rhs); //转移赋值操作符
	DEF_NEW_DELETE(SGlobalSendItemLog); //使用对象池
	virtual EType_LogDataBase GetClassType() const { return eType_SGlobalSendItemLog; }
};

typedef std::shared_ptr<SGlobalSendItemLog> SGlobalSendItemLogPtr;
typedef std::weak_ptr<SGlobalSendItemLog> SGlobalSendItemLogWtr;
typedef std::vector<SGlobalSendItemLogPtr> TVecGlobalSendItemLog;

//任务管理记录
struct SQuesOptLog : public LogDataBase
{
	std::string strSendName; //操作人
	UINT8 byStatus; //状态
	UINT32 dwServerId; //大区
	UINT64 qwUserId; //玩家ID
	UINT8 byOpType; //操作类型
	UINT16 wQuestType; //任务类型
	std::string strQuestName; //任务名字
	UINT32 dwOpTime; //操作时间

	SQuesOptLog();
#ifdef __GNUG__
	SQuesOptLog(const SQuesOptLog& src) = default; //默认拷贝构造函数
	SQuesOptLog& operator=(const SQuesOptLog& rhs) = default; //默认赋值操作符
#endif
	SQuesOptLog(SQuesOptLog&& src); //转移构造函数
	SQuesOptLog& operator=(SQuesOptLog&& rhs); //转移赋值操作符
	DEF_NEW_DELETE(SQuesOptLog); //使用对象池
	virtual EType_LogDataBase GetClassType() const { return eType_SQuesOptLog; }
};

typedef std::shared_ptr<SQuesOptLog> SQuesOptLogPtr;
typedef std::weak_ptr<SQuesOptLog> SQuesOptLogWtr;
typedef std::vector<SQuesOptLogPtr> TVecQuesOptLog;

//邮件发送日志
struct SSendMailLog : public LogDataBase
{
	std::string strSendName; //发送人
	UINT8 byStatus; //状态
	UINT32 dwServerId; //大区
	UINT64 qwUserId; //玩家ID
	std::string strTitel; //标题
	std::string strBody; //内容
	UINT32 dwOpTime; //操作时间

	SSendMailLog();
#ifdef __GNUG__
	SSendMailLog(const SSendMailLog& src) = default; //默认拷贝构造函数
	SSendMailLog& operator=(const SSendMailLog& rhs) = default; //默认赋值操作符
#endif
	SSendMailLog(SSendMailLog&& src); //转移构造函数
	SSendMailLog& operator=(SSendMailLog&& rhs); //转移赋值操作符
	DEF_NEW_DELETE(SSendMailLog); //使用对象池
	virtual EType_LogDataBase GetClassType() const { return eType_SSendMailLog; }
};

typedef std::shared_ptr<SSendMailLog> SSendMailLogPtr;
typedef std::weak_ptr<SSendMailLog> SSendMailLogWtr;
typedef std::vector<SSendMailLogPtr> TVecSendMailLog;

//VIP物品发放记录
struct SVIPSendLog : public LogDataBase
{
	std::string strSendName; //发送人
	UINT8 byStatus; //状态
	UINT32 dwServerId; //大区
	UINT64 qwUserId; //玩家ID
	UINT32 dwVIPLevel; //vip等级
	std::string strBody; //内容
	UINT32 dwOpTime; //操作时间

	SVIPSendLog();
#ifdef __GNUG__
	SVIPSendLog(const SVIPSendLog& src) = default; //默认拷贝构造函数
	SVIPSendLog& operator=(const SVIPSendLog& rhs) = default; //默认赋值操作符
#endif
	SVIPSendLog(SVIPSendLog&& src); //转移构造函数
	SVIPSendLog& operator=(SVIPSendLog&& rhs); //转移赋值操作符
	DEF_NEW_DELETE(SVIPSendLog); //使用对象池
	virtual EType_LogDataBase GetClassType() const { return eType_SVIPSendLog; }
};

typedef std::shared_ptr<SVIPSendLog> SVIPSendLogPtr;
typedef std::weak_ptr<SVIPSendLog> SVIPSendLogWtr;
typedef std::vector<SVIPSendLogPtr> TVecVIPSendLog;

//活动开启记录
struct SActivityOpenLog : public LogDataBase
{
	std::string strSendName; //发送人
	UINT8 byStatus; //状态
	UINT32 dwServerId; //大区
	UINT64 qwUserId; //玩家ID
	std::string strActivityName; //活动名称
	UINT32 dwBeginTime; //开始时间
	UINT32 dwEndTime; //结束时间
	UINT32 dwOpTime; //操作时间

	SActivityOpenLog();
#ifdef __GNUG__
	SActivityOpenLog(const SActivityOpenLog& src) = default; //默认拷贝构造函数
	SActivityOpenLog& operator=(const SActivityOpenLog& rhs) = default; //默认赋值操作符
#endif
	SActivityOpenLog(SActivityOpenLog&& src); //转移构造函数
	SActivityOpenLog& operator=(SActivityOpenLog&& rhs); //转移赋值操作符
	DEF_NEW_DELETE(SActivityOpenLog); //使用对象池
	virtual EType_LogDataBase GetClassType() const { return eType_SActivityOpenLog; }
};

typedef std::shared_ptr<SActivityOpenLog> SActivityOpenLogPtr;
typedef std::weak_ptr<SActivityOpenLog> SActivityOpenLogWtr;
typedef std::vector<SActivityOpenLogPtr> TVecActivityOpenLog;

//限时限购配置记录
struct SDiscountItemLog : public LogDataBase
{
	std::string strSendName; //发送人
	UINT8 byStatus; //状态
	UINT32 dwServerId; //大区
	UINT64 qwUserId; //玩家ID
	UINT8 byType; //类型
	UINT32 dwBeginTime; //开始时间
	UINT32 dwEndTime; //结束时间
	std::string strItemList; //物品列表
	UINT32 dwOpTime; //操作时间

	SDiscountItemLog();
#ifdef __GNUG__
	SDiscountItemLog(const SDiscountItemLog& src) = default; //默认拷贝构造函数
	SDiscountItemLog& operator=(const SDiscountItemLog& rhs) = default; //默认赋值操作符
#endif
	SDiscountItemLog(SDiscountItemLog&& src); //转移构造函数
	SDiscountItemLog& operator=(SDiscountItemLog&& rhs); //转移赋值操作符
	DEF_NEW_DELETE(SDiscountItemLog); //使用对象池
	virtual EType_LogDataBase GetClassType() const { return eType_SDiscountItemLog; }
};

typedef std::shared_ptr<SDiscountItemLog> SDiscountItemLogPtr;
typedef std::weak_ptr<SDiscountItemLog> SDiscountItemLogWtr;
typedef std::vector<SDiscountItemLogPtr> TVecDiscountItemLog;

//等级修改记录
struct SLevelChangeLog : public LogDataBase
{
	std::string strSendName; //发送人
	UINT8 byStatus; //状态
	UINT32 dwServerId; //大区
	UINT64 qwUserId; //玩家ID
	UINT8 byLevel; //玩家等级
	UINT32 dwOpTime; //操作时间

	SLevelChangeLog();
#ifdef __GNUG__
	SLevelChangeLog(const SLevelChangeLog& src) = default; //默认拷贝构造函数
	SLevelChangeLog& operator=(const SLevelChangeLog& rhs) = default; //默认赋值操作符
#endif
	SLevelChangeLog(SLevelChangeLog&& src); //转移构造函数
	SLevelChangeLog& operator=(SLevelChangeLog&& rhs); //转移赋值操作符
	DEF_NEW_DELETE(SLevelChangeLog); //使用对象池
	virtual EType_LogDataBase GetClassType() const { return eType_SLevelChangeLog; }
};

typedef std::shared_ptr<SLevelChangeLog> SLevelChangeLogPtr;
typedef std::weak_ptr<SLevelChangeLog> SLevelChangeLogWtr;
typedef std::vector<SLevelChangeLogPtr> TVecLevelChangeLog;

/////////////////////以下为序列化函数/////////////////////
CInArchive& operator>>(CInArchive&, LogDataBase&);
COutArchive& operator<<(COutArchive&, const LogDataBase&);
CInArchive& operator>>(CInArchive&, LogDataBase_Wrapper&);
COutArchive& operator<<(COutArchive&, const LogDataBase_Wrapper&);
CInArchive& operator>>(CInArchive&, TVecLogDataBase&);
COutArchive& operator<<(COutArchive&, const TVecLogDataBase&);

CInArchive& operator>>(CInArchive&, SDgnLog&);
COutArchive& operator<<(COutArchive&, const SDgnLog&);
CInArchive& operator>>(CInArchive&, TVecDgnLog&);
COutArchive& operator<<(COutArchive&, const TVecDgnLog&);

CInArchive& operator>>(CInArchive&, SRegisterLog&);
COutArchive& operator<<(COutArchive&, const SRegisterLog&);
CInArchive& operator>>(CInArchive&, TVecRegisterLog&);
COutArchive& operator<<(COutArchive&, const TVecRegisterLog&);

CInArchive& operator>>(CInArchive&, SLoginLog&);
COutArchive& operator<<(COutArchive&, const SLoginLog&);
CInArchive& operator>>(CInArchive&, TVecLoginLog&);
COutArchive& operator<<(COutArchive&, const TVecLoginLog&);

CInArchive& operator>>(CInArchive&, SItemCoursesLog&);
COutArchive& operator<<(COutArchive&, const SItemCoursesLog&);
CInArchive& operator>>(CInArchive&, TVecItemCoursesLog&);
COutArchive& operator<<(COutArchive&, const TVecItemCoursesLog&);

CInArchive& operator>>(CInArchive&, SMoneyCoursesLog&);
COutArchive& operator<<(COutArchive&, const SMoneyCoursesLog&);
CInArchive& operator>>(CInArchive&, TVecMoneyCoursesLog&);
COutArchive& operator<<(COutArchive&, const TVecMoneyCoursesLog&);

CInArchive& operator>>(CInArchive&, SMailLog&);
COutArchive& operator<<(COutArchive&, const SMailLog&);
CInArchive& operator>>(CInArchive&, TVecMailLog&);
COutArchive& operator<<(COutArchive&, const TVecMailLog&);

CInArchive& operator>>(CInArchive&, SPetLog&);
COutArchive& operator<<(COutArchive&, const SPetLog&);
CInArchive& operator>>(CInArchive&, TVecPetLog&);
COutArchive& operator<<(COutArchive&, const TVecPetLog&);

CInArchive& operator>>(CInArchive&, SDujieLog&);
COutArchive& operator<<(COutArchive&, const SDujieLog&);
CInArchive& operator>>(CInArchive&, TVecDujieLog&);
COutArchive& operator<<(COutArchive&, const TVecDujieLog&);

CInArchive& operator>>(CInArchive&, SFashionLog&);
COutArchive& operator<<(COutArchive&, const SFashionLog&);
CInArchive& operator>>(CInArchive&, TVecFashionLog&);
COutArchive& operator<<(COutArchive&, const TVecFashionLog&);

CInArchive& operator>>(CInArchive&, SFighterLog&);
COutArchive& operator<<(COutArchive&, const SFighterLog&);
CInArchive& operator>>(CInArchive&, TVecFighterLog&);
COutArchive& operator<<(COutArchive&, const TVecFighterLog&);

CInArchive& operator>>(CInArchive&, SHorseLog&);
COutArchive& operator<<(COutArchive&, const SHorseLog&);
CInArchive& operator>>(CInArchive&, TVecHorseLog&);
COutArchive& operator<<(COutArchive&, const TVecHorseLog&);

CInArchive& operator>>(CInArchive&, STrumpLog&);
COutArchive& operator<<(COutArchive&, const STrumpLog&);
CInArchive& operator>>(CInArchive&, TVecTrumpLog&);
COutArchive& operator<<(COutArchive&, const TVecTrumpLog&);

CInArchive& operator>>(CInArchive&, SBeautyLog&);
COutArchive& operator<<(COutArchive&, const SBeautyLog&);
CInArchive& operator>>(CInArchive&, TVecBeautyLog&);
COutArchive& operator<<(COutArchive&, const TVecBeautyLog&);

CInArchive& operator>>(CInArchive&, SEquipLog&);
COutArchive& operator<<(COutArchive&, const SEquipLog&);
CInArchive& operator>>(CInArchive&, TVecEquipLog&);
COutArchive& operator<<(COutArchive&, const TVecEquipLog&);

CInArchive& operator>>(CInArchive&, SGuildLog&);
COutArchive& operator<<(COutArchive&, const SGuildLog&);
CInArchive& operator>>(CInArchive&, TVecGuildLog&);
COutArchive& operator<<(COutArchive&, const TVecGuildLog&);

CInArchive& operator>>(CInArchive&, SSendMoneyLog&);
COutArchive& operator<<(COutArchive&, const SSendMoneyLog&);
CInArchive& operator>>(CInArchive&, TVecSendMoneyLog&);
COutArchive& operator<<(COutArchive&, const TVecSendMoneyLog&);

CInArchive& operator>>(CInArchive&, SSendItemLog&);
COutArchive& operator<<(COutArchive&, const SSendItemLog&);
CInArchive& operator>>(CInArchive&, TVecSendItemLog&);
COutArchive& operator<<(COutArchive&, const TVecSendItemLog&);

CInArchive& operator>>(CInArchive&, SMailOpLog&);
COutArchive& operator<<(COutArchive&, const SMailOpLog&);
CInArchive& operator>>(CInArchive&, TVecMailOpLog&);
COutArchive& operator<<(COutArchive&, const TVecMailOpLog&);

CInArchive& operator>>(CInArchive&, SForbiddenLog&);
COutArchive& operator<<(COutArchive&, const SForbiddenLog&);
CInArchive& operator>>(CInArchive&, TVecForbiddenLog&);
COutArchive& operator<<(COutArchive&, const TVecForbiddenLog&);

CInArchive& operator>>(CInArchive&, SForbiddenChatLog&);
COutArchive& operator<<(COutArchive&, const SForbiddenChatLog&);
CInArchive& operator>>(CInArchive&, TVecForbiddenChatLog&);
COutArchive& operator<<(COutArchive&, const TVecForbiddenChatLog&);

CInArchive& operator>>(CInArchive&, SGlobalSendItemLog&);
COutArchive& operator<<(COutArchive&, const SGlobalSendItemLog&);
CInArchive& operator>>(CInArchive&, TVecGlobalSendItemLog&);
COutArchive& operator<<(COutArchive&, const TVecGlobalSendItemLog&);

CInArchive& operator>>(CInArchive&, SQuesOptLog&);
COutArchive& operator<<(COutArchive&, const SQuesOptLog&);
CInArchive& operator>>(CInArchive&, TVecQuesOptLog&);
COutArchive& operator<<(COutArchive&, const TVecQuesOptLog&);

CInArchive& operator>>(CInArchive&, SSendMailLog&);
COutArchive& operator<<(COutArchive&, const SSendMailLog&);
CInArchive& operator>>(CInArchive&, TVecSendMailLog&);
COutArchive& operator<<(COutArchive&, const TVecSendMailLog&);

CInArchive& operator>>(CInArchive&, SVIPSendLog&);
COutArchive& operator<<(COutArchive&, const SVIPSendLog&);
CInArchive& operator>>(CInArchive&, TVecVIPSendLog&);
COutArchive& operator<<(COutArchive&, const TVecVIPSendLog&);

CInArchive& operator>>(CInArchive&, SActivityOpenLog&);
COutArchive& operator<<(COutArchive&, const SActivityOpenLog&);
CInArchive& operator>>(CInArchive&, TVecActivityOpenLog&);
COutArchive& operator<<(COutArchive&, const TVecActivityOpenLog&);

CInArchive& operator>>(CInArchive&, SDiscountItemLog&);
COutArchive& operator<<(COutArchive&, const SDiscountItemLog&);
CInArchive& operator>>(CInArchive&, TVecDiscountItemLog&);
COutArchive& operator<<(COutArchive&, const TVecDiscountItemLog&);

CInArchive& operator>>(CInArchive&, SLevelChangeLog&);
COutArchive& operator<<(COutArchive&, const SLevelChangeLog&);
CInArchive& operator>>(CInArchive&, TVecLevelChangeLog&);
COutArchive& operator<<(COutArchive&, const TVecLevelChangeLog&);

#ifdef PROT_USE_XML
/////////////////////以下为XML转换函数/////////////////////
bool FromXML(TiXmlElement&, LogDataBase&);
bool ToXML(const LogDataBase&, TiXmlElement&);
bool SuperFromXML(TiXmlElement&, LogDataBasePtr&);
bool SuperToXML(const LogDataBase&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecLogDataBase&);
bool VectorToXML(const TVecLogDataBase&, TiXmlElement&);

bool FromXML(TiXmlElement&, SDgnLog&);
bool ToXML(const SDgnLog&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecDgnLog&);
bool VectorToXML(const TVecDgnLog&, TiXmlElement&);

bool FromXML(TiXmlElement&, SRegisterLog&);
bool ToXML(const SRegisterLog&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecRegisterLog&);
bool VectorToXML(const TVecRegisterLog&, TiXmlElement&);

bool FromXML(TiXmlElement&, SLoginLog&);
bool ToXML(const SLoginLog&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecLoginLog&);
bool VectorToXML(const TVecLoginLog&, TiXmlElement&);

bool FromXML(TiXmlElement&, SItemCoursesLog&);
bool ToXML(const SItemCoursesLog&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecItemCoursesLog&);
bool VectorToXML(const TVecItemCoursesLog&, TiXmlElement&);

bool FromXML(TiXmlElement&, SMoneyCoursesLog&);
bool ToXML(const SMoneyCoursesLog&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecMoneyCoursesLog&);
bool VectorToXML(const TVecMoneyCoursesLog&, TiXmlElement&);

bool FromXML(TiXmlElement&, SMailLog&);
bool ToXML(const SMailLog&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecMailLog&);
bool VectorToXML(const TVecMailLog&, TiXmlElement&);

bool FromXML(TiXmlElement&, SPetLog&);
bool ToXML(const SPetLog&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecPetLog&);
bool VectorToXML(const TVecPetLog&, TiXmlElement&);

bool FromXML(TiXmlElement&, SDujieLog&);
bool ToXML(const SDujieLog&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecDujieLog&);
bool VectorToXML(const TVecDujieLog&, TiXmlElement&);

bool FromXML(TiXmlElement&, SFashionLog&);
bool ToXML(const SFashionLog&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecFashionLog&);
bool VectorToXML(const TVecFashionLog&, TiXmlElement&);

bool FromXML(TiXmlElement&, SFighterLog&);
bool ToXML(const SFighterLog&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecFighterLog&);
bool VectorToXML(const TVecFighterLog&, TiXmlElement&);

bool FromXML(TiXmlElement&, SHorseLog&);
bool ToXML(const SHorseLog&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecHorseLog&);
bool VectorToXML(const TVecHorseLog&, TiXmlElement&);

bool FromXML(TiXmlElement&, STrumpLog&);
bool ToXML(const STrumpLog&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecTrumpLog&);
bool VectorToXML(const TVecTrumpLog&, TiXmlElement&);

bool FromXML(TiXmlElement&, SBeautyLog&);
bool ToXML(const SBeautyLog&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecBeautyLog&);
bool VectorToXML(const TVecBeautyLog&, TiXmlElement&);

bool FromXML(TiXmlElement&, SEquipLog&);
bool ToXML(const SEquipLog&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecEquipLog&);
bool VectorToXML(const TVecEquipLog&, TiXmlElement&);

bool FromXML(TiXmlElement&, SGuildLog&);
bool ToXML(const SGuildLog&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecGuildLog&);
bool VectorToXML(const TVecGuildLog&, TiXmlElement&);

bool FromXML(TiXmlElement&, SSendMoneyLog&);
bool ToXML(const SSendMoneyLog&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecSendMoneyLog&);
bool VectorToXML(const TVecSendMoneyLog&, TiXmlElement&);

bool FromXML(TiXmlElement&, SSendItemLog&);
bool ToXML(const SSendItemLog&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecSendItemLog&);
bool VectorToXML(const TVecSendItemLog&, TiXmlElement&);

bool FromXML(TiXmlElement&, SMailOpLog&);
bool ToXML(const SMailOpLog&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecMailOpLog&);
bool VectorToXML(const TVecMailOpLog&, TiXmlElement&);

bool FromXML(TiXmlElement&, SForbiddenLog&);
bool ToXML(const SForbiddenLog&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecForbiddenLog&);
bool VectorToXML(const TVecForbiddenLog&, TiXmlElement&);

bool FromXML(TiXmlElement&, SForbiddenChatLog&);
bool ToXML(const SForbiddenChatLog&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecForbiddenChatLog&);
bool VectorToXML(const TVecForbiddenChatLog&, TiXmlElement&);

bool FromXML(TiXmlElement&, SGlobalSendItemLog&);
bool ToXML(const SGlobalSendItemLog&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecGlobalSendItemLog&);
bool VectorToXML(const TVecGlobalSendItemLog&, TiXmlElement&);

bool FromXML(TiXmlElement&, SQuesOptLog&);
bool ToXML(const SQuesOptLog&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecQuesOptLog&);
bool VectorToXML(const TVecQuesOptLog&, TiXmlElement&);

bool FromXML(TiXmlElement&, SSendMailLog&);
bool ToXML(const SSendMailLog&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecSendMailLog&);
bool VectorToXML(const TVecSendMailLog&, TiXmlElement&);

bool FromXML(TiXmlElement&, SVIPSendLog&);
bool ToXML(const SVIPSendLog&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecVIPSendLog&);
bool VectorToXML(const TVecVIPSendLog&, TiXmlElement&);

bool FromXML(TiXmlElement&, SActivityOpenLog&);
bool ToXML(const SActivityOpenLog&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecActivityOpenLog&);
bool VectorToXML(const TVecActivityOpenLog&, TiXmlElement&);

bool FromXML(TiXmlElement&, SDiscountItemLog&);
bool ToXML(const SDiscountItemLog&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecDiscountItemLog&);
bool VectorToXML(const TVecDiscountItemLog&, TiXmlElement&);

bool FromXML(TiXmlElement&, SLevelChangeLog&);
bool ToXML(const SLevelChangeLog&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecLevelChangeLog&);
bool VectorToXML(const TVecLevelChangeLog&, TiXmlElement&);
#endif //PROT_USE_XML

} //namespace NLogDataDefine
