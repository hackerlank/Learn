/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    ProtoCommon.h
//  Purpose:      各个协议、服务器之间通用结构存放文件
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

namespace NProtoCommon
{

/////////////////////以下为类型定义/////////////////////
//枚举类型示例
enum ECareerType
{
	ECAREER_ALL, //所有职业
	ECAREER_RU, //儒
	ECAREER_SHI, //释
	ECAREER_DAO, //道
	ECAREER_MO, //墨
	ECAREER_MAX //最大值
};

#ifdef PROT_USE_XML
const char* EnumValToStr(ECareerType);
bool EnumStrToVal(const char*, ECareerType&);
#endif //PROT_USE_XML

//性别
enum ESexType
{
	ESEX_ALL, //所有性别
	ESEX_MALE,
	ESEX_FEMALE, //女性
	ESEX_MAX //最大值
};

#ifdef PROT_USE_XML
const char* EnumValToStr(ESexType);
bool EnumStrToVal(const char*, ESexType&);
#endif //PROT_USE_XML

//颜色
enum EColor
{
	ECOLOR_BLACK, //黑
	ECOLOR_WHITE,
	ECOLOR_GREEN, //绿
	ECOLOR_BLUE, //兰
	ECOLOR_PURPLE, //紫
	ECOLOR_ORANGE //橙
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EColor);
bool EnumStrToVal(const char*, EColor&);
#endif //PROT_USE_XML

//货币类型
enum ECoinType
{
	eCoinNone, //无
	eGoldCoin, //仙石
	eSilverCoin, //银币
	eCouponCoin, //礼券
	eHonourCoin, //荣誉
	eCoinEnd //结束
};

#ifdef PROT_USE_XML
const char* EnumValToStr(ECoinType);
bool EnumStrToVal(const char*, ECoinType&);
#endif //PROT_USE_XML

//数据变化类型
enum EDataChange
{
	eOpNone, //无变化
	eOpAdd, //数据增加
	eOpDel, //数据删除
	eOpUpdate, //数据更新
	eOpReplace, //数据替换
	eOpAddIgnore, //数据仅新增
	eOpMax //最大值
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EDataChange);
bool EnumStrToVal(const char*, EDataChange&);
#endif //PROT_USE_XML
const char* GetDescription(EDataChange);

//货币类型
enum EMoneyType
{
	EMONEY_NONE = 0, //无类型表示不消耗
	EMONEY_GOLD = 1, //仙石
	EMONEY_SILVER = 2, //银币
	EMONEY_COUPON = 3, //礼券
	EMONEY_GIFTCOIN = 4, //金券
	EMONEY_EXP = 5, //经验
	EMONEY_PRESTIGE = 6, //声望
	EMONEY_SOUL = 7, //魂魄
	EMONEY_HONOR = 8, //荣誉
	EMONEY_PEXP = 9, //修为
	EMONEY_SIGIL = 10, //符印
	EMONEY_CENTSY = 11, //仙元
	EMONEY_ACTION = 12, //体力
	EMONEY_SOP = 13, //阅历
	EMONEY_TAOISM = 14, //道术
	EMONEY_POTEN = 15, //渡劫点数
	EMONEY_REIKI = 16, //副本星级
	EMONEY_HFP = 17, //寻仙积分
	EMONEY_DEMONSOUL = 18, //封印点
	EMONEY_SOULATTACK = 19, //攻击之魂
	EMONEY_SOULHP = 20, //生命之魂
	EMONEY_SOULCRITICAL = 21, //暴击之魂
	EMONEY_SOULCOUNTER = 22, //反击之魂
	EMONEY_SOULSPEED = 23, //身法之魂
	EMONEY_SOULDEFENCE = 24, //防御之魂
	EMONEY_SOULHIT = 25, //命中之魂
	EMONEY_SOULDODGE = 26, //闪避之魂
	EMONEY_ACHIEVEMENTAP = 27, //成就点
	EMONEY_COLLECTAP = 28, //收藏点
	EMONEY_GUILDCONTRIB = 29, //帮派贡献
	EMONEY_STAMPHUANG = 30, //橙阶除魔印
	EMONEY_STAMPXUAN = 31, //蓝阶除魔印
	EMONEY_STAMPDI = 32, //绿阶除魔印
	EMONEY_STAMPTIAN = 33, //紫阶除魔印
	EMONEY_STAMPXING = 34, //星阶除魔印
	EMONEY_STAMPYUE = 35, //月阶除魔印
	EMONEY_STAMPDI2 = 36, //帝阶除魔印
	EMONEY_STAMPXIAN = 37, //仙阶除魔印
	EMONEY_STAMPSHENG = 38, //圣阶除魔印
	EMONEY_STAMPFO = 39, //佛阶除魔印
	EMONEY_LOVEHEART = 40, //爱心
	EMONEY_BLUEFAIRYFATE = 51, //蓝色仙缘
	EMONEY_PURPLEFAIRYFATE = 52, //紫色仙缘
	EMONEY_ORANGEFAIRYFATE = 53, //橙色仙缘
	EMONEY_DUJIEFU = 56, //渡劫符
	EMONEY_LUCKYCOUPON = 57, //抽奖券
	EMONEY_END = 100 //货币类型上限标志
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EMoneyType);
bool EnumStrToVal(const char*, EMoneyType&);
#endif //PROT_USE_XML
const char* GetDescription(EMoneyType);

//属性枚举
enum EFighterAttr
{
	EFIGHTATTR_MIN = 0, //属性枚举最小值
	EFIGHTATTR_PHYATK = 1, //物理攻击
	EFIGHTATTR_MGCATK = 2, //法术攻击
	EFIGHTATTR_PHYDEF = 3, //物理防御
	EFIGHTATTR_MGCDEF = 4, //法术防御
	EFIGHTATTR_PHYRDC = 5, //物理免伤
	EFIGHTATTR_MGCRDC = 6, //魔法免伤
	EFIGHTATTR_MAXHP = 7, //最大生命
	EFIGHTATTR_SPEED = 8, //身法
	EFIGHTATTR_HIT = 9, //命中值
	EFIGHTATTR_HITRATE = 10, //命中率
	EFIGHTATTR_DODGE = 11, //闪避值
	EFIGHTATTR_DODGERATE = 12, //闪避率
	EFIGHTATTR_CRITICAL = 13, //暴击值
	EFIGHTATTR_CRTRATE = 14, //暴击率
	EFIGHTATTR_ANTICRITCAL = 15, //稳固值
	EFIGHTATTR_ANTICRTRATE = 16, //稳固率
	EFIGHTATTR_BLOCK = 17, //格挡值
	EFIGHTATTR_BLOCKRATE = 18, //格挡率
	EFIGHTATTR_PIERCE = 19, //穿透值
	EFIGHTATTR_PIERCERATE = 20, //穿透率
	EFIGHTATTR_COUNTER = 21, //反击值
	EFIGHTATTR_COUNTERRATE = 22, //反击率
	EFIGHTATTR_RESIST = 23, //压制值
	EFIGHTATTR_RESISTRATE = 24, //压制率
	EFIGHTATTR_INITAURA = 25, //入场灵气
	EFIGHTATTR_MAXAURA = 26, //最大灵气
	EFIGHTATTR_CRIEXTRAADD = 27, //暴击伤害增加
	EFIGHTATTR_CRIEXTRARDC = 28, //暴击伤害减免
	EFIGHTATTR_METALATK = 29, //金攻
	EFIGHTATTR_WOODATK = 30, //木攻
	EFIGHTATTR_WATERATK = 31, //水攻
	EFIGHTATTR_FIREATK = 32, //火攻
	EFIGHTATTR_EARTHATK = 33, //土攻
	EFIGHTATTR_METALDEF = 34, //金防
	EFIGHTATTR_WOODDEF = 35, //木防
	EFIGHTATTR_WATERDEF = 36, //水防
	EFIGHTATTR_FIREDEF = 37, //火防
	EFIGHTATTR_EARTHDEF = 38, //土防
	EFIGHTATTR_PHYATK_PER = 39, //物理攻击%
	EFIGHTATTR_MGCATK_PER = 40, //法术攻击%
	EFIGHTATTR_PHYDEF_PER = 41, //物理防御%
	EFIGHTATTR_MGCDEF_PER = 42, //法术防御%
	EFIGHTATTR_MAXHP_PER = 43, //最大生命%
	EFIGHTATTR_SPEED_PER = 44, //身法%
	EFIGHTATTR_HIT_PER = 45, //命中值%
	EFIGHTATTR_DODGE_PER = 46, //闪避值%
	EFIGHTATTR_CRITICAL_PER = 47, //暴击值%
	EFIGHTATTR_ANTICRITCAL_PER = 48, //稳固值%
	EFIGHTATTR_BLOCK_PER = 49, //格挡值%
	EFIGHTATTR_PIERCE_PER = 50, //穿透值%
	EFIGHTATTR_COUNTER_PER = 51, //反击值%
	EFIGHTATTR_RESIST_PER = 52, //压制值%
	EFIGHTATTR_ANTIEFFECT = 53, //法术抵抗
	EFIGHTATTR_COUTEREXTRAADD = 54, //反击伤害增加
	EFIGHTATTR_COUTEREXTRARDC = 55, //反击伤害减免
	EFIGHTATTR_MAX //属性枚举最大值
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EFighterAttr);
bool EnumStrToVal(const char*, EFighterAttr&);
#endif //PROT_USE_XML

//属性加成类型
enum EAttrGroupType
{
	eAttrGpMin, //属性加成
	eAttrGpPlayerBegin, //主将属性加成开始---
	eAttrGpFashion, //时装属性加成
	eAttrGpTitle, //称号属性加成
	eAttrGpCitta, //心法属性加成
	eAttrGpPlayerEnd, //主将加成属性结束-----
	eAttrGpHeroBegin, //散仙加成属性开始
	eAttrGpEquipTrump, //装备法宝属性加成
	eAttrGpGemstone, //宝石属性加成
	eAttrGpHeroEnd, //散仙加成属性结束
	eAttrGpHeroAndPlayerBegin, //全员加成属性开始--
	eAttrGpTrumpActive, //法宝激活属性加成
	eAttrGpTrumpExtra, //法宝附加属性加成
	eAttrGpTrumpHalo, //法宝光环属性加成
	eAttrGpHorse, //坐骑属性加成
	eAttrGpShushanBattle, //蜀山论剑属性加成
	eAttrGpBag, //背包解锁的属性加成
	eAttrGpAchievement, //成就属性加成
	eAttrGpCollection, //收集属性加成
	eAttrGpFormation, //阵形属性加成
	eAttrGpPet, //阵灵属性加成
	eAttrGpBeastSoul, //兽魂
	eAttrGpGuildTech, //帮派技能加成
	eAttrGpBuffer, //外部buffer属性加成
	eAttrGpTripod, //九疑鼎属性加成
	eAttrGpFighterCombination, //散仙组合属性加成
	eAttrBeauty, //美女系统
	eAttrGpHeroAndPlayerEnd, //全员加成属性结束--
	eAttrGpMax //属性加成
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EAttrGroupType);
bool EnumStrToVal(const char*, EAttrGroupType&);
#endif //PROT_USE_XML

//奖励类型
enum AWARDTYPE
{
	AWARDTYPE_TITLE = 1 //称号
};

#ifdef PROT_USE_XML
const char* EnumValToStr(AWARDTYPE);
bool EnumStrToVal(const char*, AWARDTYPE&);
#endif //PROT_USE_XML
const char* GetDescription(AWARDTYPE);

//Buff大类
enum EBuffType
{
	eBTNone = 0, //无效Buff大类
	eBTUser, //帐号相关Buff类型
	eBTPlayer, //玩家自带Buff类型
	eBTMainFighter, //主将相关Buff类型
	eBTFighter, //散仙相关Buff类型
	eBTMonster, //怪物相关Buff类型
	eBTNPC, //NPC相关Buff类型
	eBTMax //Buff大类最大值
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EBuffType);
bool EnumStrToVal(const char*, EBuffType&);
#endif //PROT_USE_XML
const char* GetDescription(EBuffType);

//Buff效果类型
enum EBuffEffectType
{
	eBETNone, //无效Buff效果类型
	eBETAttr, //Buff属性加成
	eBETTimeCount, //Buff持续时间同时持续次数
	eBETCount, //Buff仅持续时间
	eBETMax //Buff效果最大值
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EBuffEffectType);
bool EnumStrToVal(const char*, EBuffEffectType&);
#endif //PROT_USE_XML
const char* GetDescription(EBuffEffectType);

//Buff状态
enum EBuffState
{
	eBSNone = 0, //无效Buff状态
	eBSActived, //Buff生效
	eBSPaused, //Buff暂停
	eBSOverdue, //Buff过期
	eBSMax //Buff状态最大值
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EBuffState);
bool EnumStrToVal(const char*, EBuffState&);
#endif //PROT_USE_XML
const char* GetDescription(EBuffState);

//Buff相关操作结果
enum EBuffOpResult
{
	eBORSuccess = 0, //操作成功
	eBORFailed, //操作失败
	eBORExisted, //存在相同Buff
	eBORNotExisted, //不存在该Buff
	eBOROverdue, //已经过期的Buff
	eBORPaused //已经暂停的Buff
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EBuffOpResult);
bool EnumStrToVal(const char*, EBuffOpResult&);
#endif //PROT_USE_XML
const char* GetDescription(EBuffOpResult);

//被攻击类型
enum EAttacked
{
	eAttacked_None = 0, //无
	eAttacked_Demontower, //锁妖塔
	eAttacked_Max //类型上限
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EAttacked);
bool EnumStrToVal(const char*, EAttacked&);
#endif //PROT_USE_XML
const char* GetDescription(EAttacked);

//QQ平台类型
enum EQQPtType
{
	eQQPtTypeNone, //无
	eQQPtTypeYellow = 1, //黄钻平台
	eQQPtTypeBlue = 2, //蓝钻平台
	eQQPtTypeRed = 3, //红钻/VIP平台
	eQQPtTypeMax //最大值
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EQQPtType);
bool EnumStrToVal(const char*, EQQPtType&);
#endif //PROT_USE_XML
const char* GetDescription(EQQPtType);

//平台类型定义
enum EPtType
{
	ePtTypeNone, //无
	ePtTypeQQYellow = 1, //QQ黄钻平台/Qzone
	ePtTypeQQPengyou = 2, //QQ朋友/校友/黄钻
	ePtTypeQQWeibo = 3, //QQ微博平台
	ePtTypeQQPlus = 4, //QQ/Q+平台
	ePtTypeQQGame = 5, //QQ蓝钻/游戏平台
	ePtTypeQQ3366 = 6, //QQ蓝钻/3366平台/包子
	ePtTypeQQKingxin = 7, //QQ官网平台/QQ会员
	ePtTypeKingxin = 8, //恺英官网平台
	ePtTypeMax //最大值
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EPtType);
bool EnumStrToVal(const char*, EPtType&);
#endif //PROT_USE_XML
const char* GetDescription(EPtType);

//平台额外bit参数定义
enum EPlatformBitType
{
	ePBBitSuper = 0, //豪华/超级
	ePBBitYearly = 1 //年费
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EPlatformBitType);
bool EnumStrToVal(const char*, EPlatformBitType&);
#endif //PROT_USE_XML
const char* GetDescription(EPlatformBitType);

//货币信息
struct SCoinValue
{
	ECoinType eCoinType; //货币类型
	UINT32 dwValue; //值

	SCoinValue();
	SCoinValue(ECoinType eCoinType_, UINT32 dwValue_);
};

typedef std::vector<SCoinValue> TVecCoinValue;

//属性变化结构
struct SFtAttrMod
{
	EFighterAttr _eAttr; //属性类型
	float _fValue; //改变的值

	SFtAttrMod();
	SFtAttrMod(EFighterAttr _eAttr_, float _fValue_);
};

typedef std::vector<SFtAttrMod> TVecFtAttrMod;

//属性加成
struct SAttrGroup
{
	EAttrGroupType eType; //属性加成类型
	TVecFtAttrMod vecFtAttrMod; //属性变化结构

	SAttrGroup();
	SAttrGroup(EAttrGroupType eType_, const TVecFtAttrMod& vecFtAttrMod_);
#ifdef __GNUG__
	SAttrGroup(const SAttrGroup& src) = default; //默认拷贝构造函数
	SAttrGroup& operator=(const SAttrGroup& rhs) = default; //默认赋值操作符
#endif
	SAttrGroup(SAttrGroup&& src); //转移构造函数
	SAttrGroup& operator=(SAttrGroup&& rhs); //转移赋值操作符
};

typedef std::vector<SAttrGroup> TVecAttrGroup;

//Buff数据信息
struct SDBBuffInfo
{
	UINT64 qwRoleID; //对应玩家ID
	UINT64 qwOwnerID; //所属实例ID(Role/Fighter/...
	EBuffType eBuffType; //Buff大类
	UINT16 wBuffID; //Buff种类
	EBuffEffectType eBuffEffectType; //Buff效果类型
	EBuffState eBuffState; //Buff当前状态
	TVecUINT32 vecBuffParam; //Buff效果参数
	UINT32 dwBuffCount; //Buff失效次数
	UINT32 dwBuffTime; //Buff失效时间
	TVecUINT32 vecEffectMapID; //地图ID限制，空表示任意地图
	UINT8 byBattleType; //有效的战斗类型(不存数据库)

	SDBBuffInfo();
};

typedef std::vector<SDBBuffInfo> TVecDBBuffInfo;

//Buff详细信息
struct SBuffInfo
{
	UINT64 qwRoleID; //对应玩家ID
	UINT64 qwOwnerID; //所属实例ID(Role/Fighter/...
	UINT16 wBuffID; //Buff种类
	EBuffState eBuffState; //Buff当前状态
	TVecUINT32 vecBuffData; //Buff数值
	UINT32 dwBuffCount; //Buff叠加层数
	UINT32 dwBuffTime; //Buff失效时间

	SBuffInfo();
	SBuffInfo(UINT64 qwRoleID_, UINT64 qwOwnerID_, UINT16 wBuffID_, EBuffState eBuffState_, const TVecUINT32& vecBuffData_, 
		UINT32 dwBuffCount_, UINT32 dwBuffTime_);
};

typedef std::vector<SBuffInfo> TVecBuffInfo;

//货币列表
struct SMoneyCount
{
	EMoneyType eMoneyType; //货币类型
	UINT32 dwCount; //货币量

	SMoneyCount();
	SMoneyCount(EMoneyType eMoneyType_, UINT32 dwCount_);
};

typedef std::vector<SMoneyCount> TVecMoneyCount;

//平台相关参数
struct SPlatformParam
{
	EPtType byPtType; //平台类型
	EQQPtType byQQPtType; //QQ平台类型
	UINT8 byQQPtLv; //QQ平台类型等级
	UINT8 bySPType; //Bit位定义见EPlatformBitType

	SPlatformParam();
	SPlatformParam(EPtType byPtType_, EQQPtType byQQPtType_, UINT8 byQQPtLv_, UINT8 bySPType_);
};

typedef std::vector<SPlatformParam> TVecPlatformParam;

//Center2Game 活动时间同步
struct SActivityTime
{
	UINT32 dwActID; //活动ID
	UINT32 dwAlarm; //公告
	UINT32 dwReady; //准备
	UINT32 dwBegin; //开始
	UINT32 dwEnd; //结束

	SActivityTime();
	SActivityTime(UINT32 dwActID_, UINT32 dwAlarm_, UINT32 dwReady_, UINT32 dwBegin_, UINT32 dwEnd_);
};

//活动中心数据库记录
struct SActivityOpt
{
	UINT32 dwActID; //活动ID
	UINT8 byIndex; //场次
	std::string strName; //活动名字
	UINT32 dwSync; //活动时间 同步
	UINT32 dwAlarm; //活动公告时间
	UINT32 dwReady; //活动准备时间
	UINT32 dwBegin; //活动开始时间
	UINT32 dwEnd; //活动结束时间
	bool bSync; //是否同步Game
	UINT32 dwOptTime; //操作时间

	SActivityOpt();
	SActivityOpt(UINT32 dwActID_, UINT8 byIndex_, const std::string& strName_, UINT32 dwSync_, UINT32 dwAlarm_, 
		UINT32 dwReady_, UINT32 dwBegin_, UINT32 dwEnd_, bool bSync_, UINT32 dwOptTime_);
#ifdef __GNUG__
	SActivityOpt(const SActivityOpt& src) = default; //默认拷贝构造函数
	SActivityOpt& operator=(const SActivityOpt& rhs) = default; //默认赋值操作符
#endif
	SActivityOpt(SActivityOpt&& src); //转移构造函数
	SActivityOpt& operator=(SActivityOpt&& rhs); //转移赋值操作符
};

typedef std::vector<SActivityOpt> TVecActivityOpt;

/////////////////////以下为序列化函数/////////////////////
CInArchive& operator>>(CInArchive&, SCoinValue&);
COutArchive& operator<<(COutArchive&, const SCoinValue&);

CInArchive& operator>>(CInArchive&, SFtAttrMod&);
COutArchive& operator<<(COutArchive&, const SFtAttrMod&);

CInArchive& operator>>(CInArchive&, SAttrGroup&);
COutArchive& operator<<(COutArchive&, const SAttrGroup&);

CInArchive& operator>>(CInArchive&, SDBBuffInfo&);
COutArchive& operator<<(COutArchive&, const SDBBuffInfo&);

CInArchive& operator>>(CInArchive&, SBuffInfo&);
COutArchive& operator<<(COutArchive&, const SBuffInfo&);

CInArchive& operator>>(CInArchive&, SMoneyCount&);
COutArchive& operator<<(COutArchive&, const SMoneyCount&);

CInArchive& operator>>(CInArchive&, SPlatformParam&);
COutArchive& operator<<(COutArchive&, const SPlatformParam&);

CInArchive& operator>>(CInArchive&, SActivityTime&);
COutArchive& operator<<(COutArchive&, const SActivityTime&);

CInArchive& operator>>(CInArchive&, SActivityOpt&);
COutArchive& operator<<(COutArchive&, const SActivityOpt&);

#ifdef PROT_USE_XML
/////////////////////以下为XML转换函数/////////////////////
bool FromXML(TiXmlElement&, SCoinValue&);
bool ToXML(const SCoinValue&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecCoinValue&);
bool VectorToXML(const TVecCoinValue&, TiXmlElement&);

bool FromXML(TiXmlElement&, SFtAttrMod&);
bool ToXML(const SFtAttrMod&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecFtAttrMod&);
bool VectorToXML(const TVecFtAttrMod&, TiXmlElement&);

bool FromXML(TiXmlElement&, SAttrGroup&);
bool ToXML(const SAttrGroup&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecAttrGroup&);
bool VectorToXML(const TVecAttrGroup&, TiXmlElement&);

bool FromXML(TiXmlElement&, SDBBuffInfo&);
bool ToXML(const SDBBuffInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecDBBuffInfo&);
bool VectorToXML(const TVecDBBuffInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SBuffInfo&);
bool ToXML(const SBuffInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecBuffInfo&);
bool VectorToXML(const TVecBuffInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SMoneyCount&);
bool ToXML(const SMoneyCount&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecMoneyCount&);
bool VectorToXML(const TVecMoneyCount&, TiXmlElement&);

bool FromXML(TiXmlElement&, SPlatformParam&);
bool ToXML(const SPlatformParam&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecPlatformParam&);
bool VectorToXML(const TVecPlatformParam&, TiXmlElement&);

bool FromXML(TiXmlElement&, SActivityTime&);
bool ToXML(const SActivityTime&, TiXmlElement&);

bool FromXML(TiXmlElement&, SActivityOpt&);
bool ToXML(const SActivityOpt&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecActivityOpt&);
bool VectorToXML(const TVecActivityOpt&, TiXmlElement&);
#endif //PROT_USE_XML

} //namespace NProtoCommon
