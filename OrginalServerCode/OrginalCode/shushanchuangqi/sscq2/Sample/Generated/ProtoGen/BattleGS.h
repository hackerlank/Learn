/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    BattleGS.h
//  Purpose:      战斗通信协议
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
#include "ItemProt.h"
#include "ProtoCommon.h"

namespace NBattleGS
{

/////////////////////以下为类型定义/////////////////////
//被动状态枚举
enum EBStatusType
{
	EBStatusType_Evade, //闪避
	EBStatusType_Resist, //抵抗
	EBStatusType_Immu, //免疫
	EBStatusType_Block //格挡
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EBStatusType);
bool EnumStrToVal(const char*, EBStatusType&);
#endif //PROT_USE_XML

//State效果枚举
enum EBStateBuffType
{
	EBFBuffTypeNone = 0, //无状态
	EBFBuffTypeMin = 0, //出手时状态枚举最小值
	EBFBuffTypeStun = 1, //眩晕
	EBFBuffTypeConfuse = 2, //混乱
	EBFBuffTypeCover = 3, //掩护
	EBFBuffTypeEShock = 4, //电击
	EBFBuffTypeBlock = 5, //格挡
	EBFBuffTypeInvincible = 6, //无敌
	EBFBuffTypeShield = 7, //护盾
	EBFBuffTypePierce = 8, //破甲
	EBFBuffTypeBleed = 9, //流血
	EBFBuffTypeForget = 10, //沉默
	EBFBuffTypeFreeze = 11, //冻结
	EBFBuffTypeBurned = 12, //点燃
	EBFBuffTypeAtkAdd = 13, //攻击提升
	EBFBuffTypeAtkSub = 14, //攻击下降
	EBFBuffTypeRedAdd = 15, //免伤提升
	EBFBuffTypeRedSub = 16, //免伤下降
	EBFBuffTypeStoned = 17, //石化
	EBFBuffTypePoison = 18, //中毒
	EBFBuffTypeHide = 19, //影遁
	EBFBuffTypeBronze = 20, //铜人
	EBFBuffTypeKingkong = 21, //金刚
	EBFBuffTypeDmgReduce = 22, //伤害减少
	EBFBuffTypeDmgAdd = 23, //伤害提升
	EBFBuffTypeCongest = 24, //蓄力
	EBFBuffTypeReflect = 25, //反弹状态
	EBFBuffTypeHitDown = 26, //命中降低
	EBFBuffTypeClone = 27, //分身
	EBFBuffTypeSealed = 28, //封印
	EBFBuffTypeBeDmgReudce = 29, //伤害减免
	EBFBuffTypeBlind = 30, //致盲
	EBFBuffTypeSmoke = 31, //烟幕
	EBFBuffTypeGuard = 32, //护卫
	EBFBuffTypeKindKing = 33, //仁王
	EBFBuffTypeBlunt = 34, //麻痹
	EBFBuffTypeIceBlade = 35, //冰刃
	EBFBuffTypeThunderBlade = 36, //雷刃
	EBFBuffTypeFireBlade = 37, //炎刃
	EBFBuffTypeSnowSoul = 38, //雪魂
	EBFBuffTypeHaloRed = 39, //光环红
	EBFBuffTypeHaloBlue = 40, //光环蓝
	EBFBuffTypeDrogenSting = 41, //龙刺
	EBFBuffTypeDmgShare = 42, //伤害分担
	EBFBuffTypeAttrAdd = 43, //属性增益
	EBFBuffTypeAttrSub = 44, //属性减益
	EBFBuffTypeActAtkAdd = 45, //行动后攻击增加
	EBFBuffTypeActDefAdd = 46, //行动后防御增加
	EBFBuffTypeMax //状态最大值
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EBStateBuffType);
bool EnumStrToVal(const char*, EBStateBuffType&);
#endif //PROT_USE_XML

//扣血伤害类型（物理/法术）
enum EBSubHPType
{
	EBSubHPPhy, //物理
	EBSubHPMgc //法术
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EBSubHPType);
bool EnumStrToVal(const char*, EBSubHPType&);
#endif //PROT_USE_XML

//修改血的类型
enum EBModifyHPType
{
	EBMODIFYHP_NORMAL = 0, //普通
	EBMODIFYHP_CRITICAL //暴击
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EBModifyHPType);
bool EnumStrToVal(const char*, EBModifyHPType&);
#endif //PROT_USE_XML

//被动状态枚举
enum EBSheildAbsorbType
{
	EBSheildAbsorbPhysic = 1, //吸收物理伤害
	EBSheildAbsorbMagic, //吸收法术伤害
	EBSheildAbsorbDamage //吸收伤害
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EBSheildAbsorbType);
bool EnumStrToVal(const char*, EBSheildAbsorbType&);
#endif //PROT_USE_XML

//连携槽增长方式
enum ECombineType
{
	eCTNone = 0, //无效方式
	eCTCritical, //暴击
	eCTBlock, //格挡
	eCTEvade, //闪避
	eCTCounter, //反击
	eCTPeerless, //无双
	eCTMax //最大
};

#ifdef PROT_USE_XML
const char* EnumValToStr(ECombineType);
bool EnumStrToVal(const char*, ECombineType&);
#endif //PROT_USE_XML

//连携槽操作
enum ECombineSlotOPType
{
	eCSOPTLock, //关闭连携槽
	eCSOPTUnLock //开启连携槽
};

#ifdef PROT_USE_XML
const char* EnumValToStr(ECombineSlotOPType);
bool EnumStrToVal(const char*, ECombineSlotOPType&);
#endif //PROT_USE_XML

//战斗结果
enum EBattleResult
{
	EBResultNone = 0, //无
	EBResultAttackWin, //攻击方胜利
	EBResultDefenseWin, //防守方胜利
	EBResultTie //平局（最后血量都相同，可能为0）
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EBattleResult);
bool EnumStrToVal(const char*, EBattleResult&);
#endif //PROT_USE_XML

//战斗模式：PVP/PVE
enum EBattleType
{
	EBTINVALID = 1, //PVE(攻击怪物)
	EBTMonster = 2, //PVE(攻击怪物)
	EBTPlayer = 3, //PVP(攻击玩家)
	EBWorldBoss = 4, //世界boss战
	EBArena = 5, //竞技场
	EBDemonTower = 6, //锁妖塔
	ETreasureHunt = 7, //寻宝
	EGuardEMei = 8, //守卫峨嵋
	EBShip = 9, //运船
	EBShushan = 10, //论剑
	EBLingshan = 11, //灵山寻宝
	EBattleEnd //结束标志
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EBattleType);
bool EnumStrToVal(const char*, EBattleType&);
#endif //PROT_USE_XML

//战斗请求结果
enum EBattleReqResult
{
	EBattleReq_Suc = 1, //成功
	EBattleReq_CoolDown = 2, //您还处在战斗冷却中
	EBattleReq_Protect = 3, //对方在战斗保护中
	EBattleReq_GuardFirst = 4, //请先去击杀护卫
	EBattleReq_DieCD = 5, //死亡冷却中
	EBattleReq_FieldCoolDown = 6, //野外战斗冷却中
	EBattleReq_Level = 7, //等级不够
	EBattleReq_Other = 8 //未知错误
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EBattleReqResult);
bool EnumStrToVal(const char*, EBattleReqResult&);
#endif //PROT_USE_XML
const char* GetDescription(EBattleReqResult);

//战报请求结果
enum EReportReqResult
{
	EReportReq_Suc = 1, //成功
	EReportReq_NonExistent = 2, //请求的战报不存在
	EReportReq_Other = 4 //未知错误
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EReportReqResult);
bool EnumStrToVal(const char*, EReportReqResult&);
#endif //PROT_USE_XML
const char* GetDescription(EReportReqResult);

//结构体：SFeatureBase的继承体系类型
enum EType_SFeatureBase
{
	eType_SFeatureBase, //类型：SFeatureBase
	eType_SMonsterFeature, //类型：SMonsterFeature
	eType_SPlayerFeature, //类型：SPlayerFeature
	eType_SHeroFeature, //类型：SHeroFeature
	eType_SFormationFeature, //类型：SFormationFeature
	eType_SFieldFeature, //类型：SFieldFeature
	eType_SBeautyFeature, //类型：SBeautyFeature
	eType_SPlayerFeatureWithBuff, //类型：SPlayerFeatureWithBuff
	eType_SMonsterFeatureWithBuff //类型：SMonsterFeatureWithBuff
};

//结构体：SEffectBase的继承体系类型
enum EType_SEffectBase
{
	eType_SEffectBase, //类型：SEffectBase
	eType_SEffectDecHP, //类型：SEffectDecHP
	eType_SEffectAddStatus, //类型：SEffectAddStatus
	eType_SEffectAddHP, //类型：SEffectAddHP
	eType_SEffectRelive, //类型：SEffectRelive
	eType_SEffectCounter, //类型：SEffectCounter
	eType_SEffectStateBuffAdd, //类型：SEffectStateBuffAdd
	eType_SEffectStateBuffEffect, //类型：SEffectStateBuffEffect
	eType_SEffectStateBuffDec, //类型：SEffectStateBuffDec
	eType_SEffectStateBuffLast, //类型：SEffectStateBuffLast
	eType_SEffectAttrBuffAdd, //类型：SEffectAttrBuffAdd
	eType_SEffectAttrBuffDec, //类型：SEffectAttrBuffDec
	eType_SEffectDied, //类型：SEffectDied
	eType_SEffectShieldAbsorb, //类型：SEffectShieldAbsorb
	eType_SEffectTriggerExecute, //类型：SEffectTriggerExecute
	eType_SEffectSycHP, //类型：SEffectSycHP
	eType_SEffectSycAura, //类型：SEffectSycAura
	eType_SEffectSycCombine, //类型：SEffectSycCombine
	eType_SEffectCombineSlot, //类型：SEffectCombineSlot
	eType_SEffectBrokenShield, //类型：SEffectBrokenShield
	eType_SEffectSummon, //类型：SEffectSummon
	eType_SEffectDialog, //类型：SEffectDialog
	eType_SEffectTransform, //类型：SEffectTransform
	eType_SEffectPartBroken, //类型：SEffectPartBroken
	eType_SEffectBuffAction //类型：SEffectBuffAction
};

//结构体：NewSBattleReport的继承体系类型
enum EType_NewSBattleReport
{
	eType_NewSBattleReport, //类型：NewSBattleReport
	eType_NewSBattleReportV1 //类型：NewSBattleReportV1
};

//发给前端用的显示外形的装备信息
struct SEquipShowInfo
{
	UINT16 wEquipID; //装备TypeID
	UINT8 byStrengthenLevel; //强化等级
	UINT8 byPos; //装备位置

	SEquipShowInfo();
	SEquipShowInfo(UINT16 wEquipID_, UINT8 byStrengthenLevel_, UINT8 byPos_);
};

typedef std::vector<SEquipShowInfo> TVecEquipShowInfo;

//装备的头衔外观
struct STitleAppear
{
	UINT8 byPos; //装备位置
	UINT16 wID; //头衔ID

	STitleAppear();
	STitleAppear(UINT8 byPos_, UINT16 wID_);
};

typedef std::vector<STitleAppear> TVecTitleAppear;

//战斗外的Buff信息
struct SBattleBuffInfo
{
	UINT16 wBuffID; //Buff种类
	TVecUINT32 vecBuffData; //Buff数值
	UINT32 dwBuffCount; //Buff叠加层数
	UINT32 dwBuffTime; //Buff失效时间

	SBattleBuffInfo();
	SBattleBuffInfo(UINT16 wBuffID_, const TVecUINT32& vecBuffData_, UINT32 dwBuffCount_, UINT32 dwBuffTime_);
};

typedef std::vector<SBattleBuffInfo> TVecBattleBuffInfo;

//外观信息
struct SFeatureBase
{
	TVecUINT16 vecBuffID; //BUffID信息

	SFeatureBase();
	virtual ~SFeatureBase() { }
	DEF_NEW_DELETE(SFeatureBase); //使用对象池
	virtual EType_SFeatureBase GetClassType() const { return eType_SFeatureBase; }
};

typedef std::shared_ptr<SFeatureBase> SFeatureBasePtr;
typedef std::weak_ptr<SFeatureBase> SFeatureBaseWtr;
typedef std::vector<SFeatureBasePtr> TVecFeatureBase;

//父类：SFeatureBase的辅助结构体
struct SFeatureBase_Wrapper
{
	SFeatureBasePtr ptr;
	SFeatureBase_Wrapper(const SFeatureBasePtr& ptr_ = NULL) : ptr(ptr_) { }
};

//怪物
struct SMonsterFeature : public SFeatureBase
{
	UINT16 wMonsterID; //配置表里面的英雄ID，根据ID可以取到怪物外观资源

	SMonsterFeature();
	DEF_NEW_DELETE(SMonsterFeature); //使用对象池
	virtual EType_SFeatureBase GetClassType() const { return eType_SMonsterFeature; }
};

typedef std::shared_ptr<SMonsterFeature> SMonsterFeaturePtr;
typedef std::weak_ptr<SMonsterFeature> SMonsterFeatureWtr;
typedef std::vector<SMonsterFeaturePtr> TVecMonsterFeature;

//玩家
struct SPlayerFeature : public SFeatureBase
{
	std::string strName; //玩家姓名
	NProtoCommon::ECareerType eJob; //职业
	NProtoCommon::ESexType eSex; //性别
	TVecEquipShowInfo vEquip; //装备
	TVecTitleAppear vecTitle; //头衔
	std::string strGuildName; //帮派名称
	UINT8 byQuality; //品质
	UINT8 byDujieLevel; //散仙渡劫等级
	UINT8 byVIPLevel; //VIP等级

	SPlayerFeature();
#ifdef __GNUG__
	SPlayerFeature(const SPlayerFeature& src) = default; //默认拷贝构造函数
	SPlayerFeature& operator=(const SPlayerFeature& rhs) = default; //默认赋值操作符
#endif
	SPlayerFeature(SPlayerFeature&& src); //转移构造函数
	SPlayerFeature& operator=(SPlayerFeature&& rhs); //转移赋值操作符
	DEF_NEW_DELETE(SPlayerFeature); //使用对象池
	virtual EType_SFeatureBase GetClassType() const { return eType_SPlayerFeature; }
};

typedef std::shared_ptr<SPlayerFeature> SPlayerFeaturePtr;
typedef std::weak_ptr<SPlayerFeature> SPlayerFeatureWtr;
typedef std::vector<SPlayerFeaturePtr> TVecPlayerFeature;

//散仙
struct SHeroFeature : public SFeatureBase
{
	UINT16 wHeroID; //散仙类型
	UINT8 byQuality; //品质
	UINT8 byDujieLevel; //散仙渡劫等级

	SHeroFeature();
	DEF_NEW_DELETE(SHeroFeature); //使用对象池
	virtual EType_SFeatureBase GetClassType() const { return eType_SHeroFeature; }
};

typedef std::shared_ptr<SHeroFeature> SHeroFeaturePtr;
typedef std::weak_ptr<SHeroFeature> SHeroFeatureWtr;
typedef std::vector<SHeroFeaturePtr> TVecHeroFeature;

//阵灵
struct SFormationFeature : public SFeatureBase
{
	UINT16 wFormationID; //阵灵配置表ID，同monster

	SFormationFeature();
	DEF_NEW_DELETE(SFormationFeature); //使用对象池
	virtual EType_SFeatureBase GetClassType() const { return eType_SFormationFeature; }
};

typedef std::shared_ptr<SFormationFeature> SFormationFeaturePtr;
typedef std::weak_ptr<SFormationFeature> SFormationFeatureWtr;
typedef std::vector<SFormationFeaturePtr> TVecFormationFeature;

//场景
struct SFieldFeature : public SFeatureBase
{
	UINT16 wSceneID; //场景ID

	SFieldFeature();
	DEF_NEW_DELETE(SFieldFeature); //使用对象池
	virtual EType_SFeatureBase GetClassType() const { return eType_SFieldFeature; }
};

typedef std::shared_ptr<SFieldFeature> SFieldFeaturePtr;
typedef std::weak_ptr<SFieldFeature> SFieldFeatureWtr;

//美女
struct SBeautyFeature : public SFeatureBase
{
	UINT16 wBeautyID; //美女ID

	SBeautyFeature();
	DEF_NEW_DELETE(SBeautyFeature); //使用对象池
	virtual EType_SFeatureBase GetClassType() const { return eType_SBeautyFeature; }
};

typedef std::shared_ptr<SBeautyFeature> SBeautyFeaturePtr;
typedef std::weak_ptr<SBeautyFeature> SBeautyFeatureWtr;

//带Buff的玩家信息
struct SPlayerFeatureWithBuff : public SFeatureBase
{
	std::string strName; //玩家姓名
	NProtoCommon::ECareerType eJob; //职业
	NProtoCommon::ESexType eSex; //性别
	TVecEquipShowInfo vEquip; //装备
	TVecTitleAppear vecTitle; //头衔
	std::string strGuildName; //帮派名称
	UINT8 byQuality; //品质
	UINT8 byDujieLevel; //散仙渡劫等级
	UINT8 byVIPLevel; //VIP等级
	TVecBattleBuffInfo vecBuffInfo; //战斗外的Buff信息

	SPlayerFeatureWithBuff();
#ifdef __GNUG__
	SPlayerFeatureWithBuff(const SPlayerFeatureWithBuff& src) = default; //默认拷贝构造函数
	SPlayerFeatureWithBuff& operator=(const SPlayerFeatureWithBuff& rhs) = default; //默认赋值操作符
#endif
	SPlayerFeatureWithBuff(SPlayerFeatureWithBuff&& src); //转移构造函数
	SPlayerFeatureWithBuff& operator=(SPlayerFeatureWithBuff&& rhs); //转移赋值操作符
	DEF_NEW_DELETE(SPlayerFeatureWithBuff); //使用对象池
	virtual EType_SFeatureBase GetClassType() const { return eType_SPlayerFeatureWithBuff; }
};

typedef std::shared_ptr<SPlayerFeatureWithBuff> SPlayerFeatureWithBuffPtr;
typedef std::weak_ptr<SPlayerFeatureWithBuff> SPlayerFeatureWithBuffWtr;
typedef std::vector<SPlayerFeatureWithBuffPtr> TVecPlayerFeatureWithBuff;

//带Buff的怪物信息
struct SMonsterFeatureWithBuff : public SFeatureBase
{
	UINT16 wMonsterID; //配置表里面的英雄ID，根据ID可以取到怪物外观资源
	TVecBattleBuffInfo vecBuffInfo; //战斗外的Buff信息

	SMonsterFeatureWithBuff();
#ifdef __GNUG__
	SMonsterFeatureWithBuff(const SMonsterFeatureWithBuff& src) = default; //默认拷贝构造函数
	SMonsterFeatureWithBuff& operator=(const SMonsterFeatureWithBuff& rhs) = default; //默认赋值操作符
#endif
	SMonsterFeatureWithBuff(SMonsterFeatureWithBuff&& src); //转移构造函数
	SMonsterFeatureWithBuff& operator=(SMonsterFeatureWithBuff&& rhs); //转移赋值操作符
	DEF_NEW_DELETE(SMonsterFeatureWithBuff); //使用对象池
	virtual EType_SFeatureBase GetClassType() const { return eType_SMonsterFeatureWithBuff; }
};

typedef std::shared_ptr<SMonsterFeatureWithBuff> SMonsterFeatureWithBuffPtr;
typedef std::weak_ptr<SMonsterFeatureWithBuff> SMonsterFeatureWithBuffWtr;
typedef std::vector<SMonsterFeatureWithBuffPtr> TVecMonsterFeatureWithBuff;

//参与战斗的技能信息
struct SBattleFightSkillInfo
{
	UINT32 dwSkillID; //技能ID
	UINT32 dwSymboleID; //符文ID

	SBattleFightSkillInfo();
	SBattleFightSkillInfo(UINT32 dwSkillID_, UINT32 dwSymboleID_);
};

typedef std::vector<SBattleFightSkillInfo> TVecFightSkillInfo;

//队伍技能
struct STeamSkillInfo
{
	UINT8 byIndex; //队伍技能唯一编号
	UINT8 byTeamID; //队伍ID
	UINT32 dwSkillID; //技能ID

	STeamSkillInfo();
	STeamSkillInfo(UINT8 byIndex_, UINT8 byTeamID_, UINT32 dwSkillID_);
};

typedef std::vector<STeamSkillInfo> TVecTeamSkillInfo;

//战斗者信息
struct SBattleFighterInfo
{
	UINT64 qwInstID; //将唯一ID
	UINT16 wFighterID; //将类型ID
	INT32 iPos; //将位置
	UINT8 byTeamID; //所属队伍ID
	UINT8 byLevel; //等级
	std::string strName; //将名字
	NProtoCommon::ESexType eSex; //将性别
	NProtoCommon::ECareerType eCareer; //将职业
	UINT32 dwHpMax; //最大血量
	UINT32 dwHp; //当前血量
	UINT32 dwAura; //当前灵气
	UINT32 dwAuraMax; //最大灵气
	NProtoCommon::TVecFtAttrMod oAttrVec; //最终属性
	TVecFightSkillInfo vActiveSkill; //装备的主动技能
	TVecFightSkillInfo vPassiveSkill; //被动技能
	SBattleFightSkillInfo oPeerLees; //无双技能
	SBattleFightSkillInfo oPeerLeesEx; //变身后无双技能
	SFeatureBasePtr pFeature; //外观信息

	SBattleFighterInfo();
};

typedef std::vector<SBattleFighterInfo> TVecFighterInfo;

//Fighter信息
struct SBattleFighter
{
	UINT8 byFighterID; //战场开始之后分配的唯一ID，groupID*5*5+pos
	SBattleFighterInfo oFgtInfo; //FighterInfo

	SBattleFighter();
	SBattleFighter(UINT8 byFighterID_, const SBattleFighterInfo& oFgtInfo_);
};

typedef std::vector<SBattleFighter> TVecBattleFighter;

//战斗小队
struct SBattleGroup
{
	UINT8 byGroupID; //组ID
	UINT64 qwCreatrueID; //玩家ID，地图上跑的时候用的那个ID，怪物为0
	UINT64 qwLeaderID; //队伍主将ID
	UINT16 wLevel; //队伍等级
	TVecBattleFighter vFighters; //队伍里面的所有fighter
	TVecTeamSkillInfo vecCombineSkillInfo; //队伍中的连携技能
	SFeatureBasePtr pMainFeature; //主将外观信息(用于显示头像用)
	UINT32 dwBattlePoint; //战斗力

	SBattleGroup();
};

typedef std::vector<SBattleGroup> TVecBattleGroup;

//战斗基础效果类型
struct SEffectBase
{
	TVecUINT8 vecFighterID; //表现这个效果的fighter(255表示为场景)

	SEffectBase();
	virtual ~SEffectBase() { }
	DEF_NEW_DELETE(SEffectBase); //使用对象池
	virtual EType_SEffectBase GetClassType() const { return eType_SEffectBase; }
};

typedef std::shared_ptr<SEffectBase> SEffectBasePtr;
typedef std::weak_ptr<SEffectBase> SEffectBaseWtr;
typedef std::vector<SEffectBasePtr> TVecEffects;

//父类：SEffectBase的辅助结构体
struct SEffectBase_Wrapper
{
	SEffectBasePtr ptr;
	SEffectBase_Wrapper(const SEffectBasePtr& ptr_ = NULL) : ptr(ptr_) { }
};

//扣血
struct SEffectDecHP : public SEffectBase
{
	UINT32 dwSkillID; //扣血对应ID
	EBSubHPType eSubHPType; //扣血伤害类型（物理/法术）
	EBModifyHPType eHPType; //扣血类型
	UINT32 dwDecHP; //扣掉的血

	SEffectDecHP();
	DEF_NEW_DELETE(SEffectDecHP); //使用对象池
	virtual EType_SEffectBase GetClassType() const { return eType_SEffectDecHP; }
};

typedef std::shared_ptr<SEffectDecHP> SEffectDecHPPtr;
typedef std::weak_ptr<SEffectDecHP> SEffectDecHPWtr;
typedef std::vector<SEffectDecHPPtr> TVecDecHP;

//一个UINT32参数的效果
struct SEffectAddStatus : public SEffectBase
{
	EBStatusType eStatus; //状态类型

	SEffectAddStatus();
	DEF_NEW_DELETE(SEffectAddStatus); //使用对象池
	virtual EType_SEffectBase GetClassType() const { return eType_SEffectAddStatus; }
};

typedef std::shared_ptr<SEffectAddStatus> SEffectAddStatusPtr;
typedef std::weak_ptr<SEffectAddStatus> SEffectAddStatusWtr;
typedef std::vector<SEffectAddStatusPtr> TVecAddStatus;

//加血
struct SEffectAddHP : public SEffectBase
{
	UINT32 dwSkillID; //加血对应ID
	EBModifyHPType eHPType; //加血类型
	UINT32 dwAddHP; //增加的血量

	SEffectAddHP();
	DEF_NEW_DELETE(SEffectAddHP); //使用对象池
	virtual EType_SEffectBase GetClassType() const { return eType_SEffectAddHP; }
};

typedef std::shared_ptr<SEffectAddHP> SEffectAddHPPtr;
typedef std::weak_ptr<SEffectAddHP> SEffectAddHPWtr;
typedef std::vector<SEffectAddHPPtr> TVecAddHP;

//重生
struct SEffectRelive : public SEffectBase
{
	UINT8 byGroupID; //组编号
	UINT8 bySide; //方向编号
	UINT8 byPos; //位置编号
	UINT16 wFighterID; //散仙ID
	UINT32 dwHpMax; //最大血量
	UINT32 dwHp; //当前血量
	UINT32 dwAura; //当前灵气
	UINT32 dwAuraMax; //最大灵气

	SEffectRelive();
	DEF_NEW_DELETE(SEffectRelive); //使用对象池
	virtual EType_SEffectBase GetClassType() const { return eType_SEffectRelive; }
};

typedef std::shared_ptr<SEffectRelive> SEffectRelivePtr;
typedef std::weak_ptr<SEffectRelive> SEffectReliveWtr;
typedef std::vector<SEffectRelivePtr> TVecRelive;

//反击
struct SEffectCounter : public SEffectBase
{
	EBSubHPType eSubHPType; //扣血伤害类型（物理/法术）
	EBModifyHPType eHPType; //扣血类型
	UINT32 dwDecHP; //反击的伤害量

	SEffectCounter();
	DEF_NEW_DELETE(SEffectCounter); //使用对象池
	virtual EType_SEffectBase GetClassType() const { return eType_SEffectCounter; }
};

typedef std::shared_ptr<SEffectCounter> SEffectCounterPtr;
typedef std::weak_ptr<SEffectCounter> SEffectCounterWtr;
typedef std::vector<SEffectCounterPtr> TVecCounter;

//加状态Buff
struct SEffectStateBuffAdd : public SEffectBase
{
	UINT32 dwBuffKey; //查找这个buff的唯一ID
	EBStateBuffType eStateBuffType; //状态枚举
	UINT32 dwSkillID; //该Buff的技能来源
	UINT32 dwBaseSkillID; //初始技能ID（SkillBase表的ID）
	UINT8 byLast; //持续时间
	INT32 dwValue; //该Buff的效果值

	SEffectStateBuffAdd();
	DEF_NEW_DELETE(SEffectStateBuffAdd); //使用对象池
	virtual EType_SEffectBase GetClassType() const { return eType_SEffectStateBuffAdd; }
};

typedef std::shared_ptr<SEffectStateBuffAdd> SEffectStateBuffAddPtr;
typedef std::weak_ptr<SEffectStateBuffAdd> SEffectStateBuffAddWtr;
typedef std::vector<SEffectStateBuffAddPtr> TVecStateBuffAdd;

//状态Buff生效
struct SEffectStateBuffEffect : public SEffectBase
{
	UINT32 dwBuffKey; //查找这个Buff的唯一ID

	SEffectStateBuffEffect();
	DEF_NEW_DELETE(SEffectStateBuffEffect); //使用对象池
	virtual EType_SEffectBase GetClassType() const { return eType_SEffectStateBuffEffect; }
};

typedef std::shared_ptr<SEffectStateBuffEffect> SEffectStateBuffEffectPtr;
typedef std::weak_ptr<SEffectStateBuffEffect> SEffectStateBuffEffectWtr;
typedef std::vector<SEffectStateBuffEffectPtr> TVecStateBuffEffect;

//减状态Buff
struct SEffectStateBuffDec : public SEffectBase
{
	UINT32 dwBuffKey; //查找这个Buff的唯一ID

	SEffectStateBuffDec();
	DEF_NEW_DELETE(SEffectStateBuffDec); //使用对象池
	virtual EType_SEffectBase GetClassType() const { return eType_SEffectStateBuffDec; }
};

typedef std::shared_ptr<SEffectStateBuffDec> SEffectStateBuffDecPtr;
typedef std::weak_ptr<SEffectStateBuffDec> SEffectStateBuffDecWtr;
typedef std::vector<SEffectStateBuffDecPtr> TVecStateBuffDec;

//Buff持续时间
struct SEffectStateBuffLast : public SEffectBase
{
	UINT32 dwBuffKey; //查找这个Buff的唯一ID
	UINT8 byLast; //持续时间

	SEffectStateBuffLast();
	DEF_NEW_DELETE(SEffectStateBuffLast); //使用对象池
	virtual EType_SEffectBase GetClassType() const { return eType_SEffectStateBuffLast; }
};

typedef std::shared_ptr<SEffectStateBuffLast> SEffectStateBuffLastPtr;
typedef std::weak_ptr<SEffectStateBuffLast> SEffectStateBuffLastWtr;
typedef std::vector<SEffectStateBuffLastPtr> TVecStateBuffLast;

//加修改人物属性buff
struct SEffectAttrBuffAdd : public SEffectBase
{
	NProtoCommon::EFighterAttr eBuffType; //修改的属性枚举
	UINT32 dwBuffKey; //查找这个buff的唯一ID
	UINT32 dwSkillID; //该Buff的技能来源
	UINT8 byLast; //持续时间
	INT32 dwValue; //该Buff的效果值

	SEffectAttrBuffAdd();
	DEF_NEW_DELETE(SEffectAttrBuffAdd); //使用对象池
	virtual EType_SEffectBase GetClassType() const { return eType_SEffectAttrBuffAdd; }
};

typedef std::shared_ptr<SEffectAttrBuffAdd> SEffectAttrBuffAddPtr;
typedef std::weak_ptr<SEffectAttrBuffAdd> SEffectAttrBuffAddWtr;
typedef std::vector<SEffectAttrBuffAddPtr> TVecAttrBuffAdd;

//减修改人物属性buff
struct SEffectAttrBuffDec : public SEffectBase
{
	UINT32 dwBuffKey; //查找这个buff的唯一ID

	SEffectAttrBuffDec();
	DEF_NEW_DELETE(SEffectAttrBuffDec); //使用对象池
	virtual EType_SEffectBase GetClassType() const { return eType_SEffectAttrBuffDec; }
};

typedef std::shared_ptr<SEffectAttrBuffDec> SEffectAttrBuffDecPtr;
typedef std::weak_ptr<SEffectAttrBuffDec> SEffectAttrBuffDecWtr;
typedef std::vector<SEffectAttrBuffDecPtr> TVecAttrBuffDec;

//我死了
struct SEffectDied : public SEffectBase
{
	UINT32 dwSkillID; //死亡时动画技能ID

	SEffectDied();
	DEF_NEW_DELETE(SEffectDied); //使用对象池
	virtual EType_SEffectBase GetClassType() const { return eType_SEffectDied; }
};

typedef std::shared_ptr<SEffectDied> SEffectDiedPtr;
typedef std::weak_ptr<SEffectDied> SEffectDiedWtr;
typedef std::vector<SEffectDiedPtr> TVecDied;

//盾牌吸收伤害
struct SEffectShieldAbsorb : public SEffectBase
{
	EBSheildAbsorbType eType; //吸收类型
	UINT32 dwHP; //吸收的数值

	SEffectShieldAbsorb();
	DEF_NEW_DELETE(SEffectShieldAbsorb); //使用对象池
	virtual EType_SEffectBase GetClassType() const { return eType_SEffectShieldAbsorb; }
};

typedef std::shared_ptr<SEffectShieldAbsorb> SEffectShieldAbsorbPtr;
typedef std::weak_ptr<SEffectShieldAbsorb> SEffectShieldAbsorbWtr;
typedef std::vector<SEffectShieldAbsorbPtr> TVecShieldAbsorb;

//被动触发执行
struct SEffectTriggerExecute : public SEffectBase
{
	UINT32 dwSkillID; //技能ID

	SEffectTriggerExecute();
	DEF_NEW_DELETE(SEffectTriggerExecute); //使用对象池
	virtual EType_SEffectBase GetClassType() const { return eType_SEffectTriggerExecute; }
};

typedef std::shared_ptr<SEffectTriggerExecute> SEffectTriggerExecutePtr;
typedef std::weak_ptr<SEffectTriggerExecute> SEffectTriggerExecuteWtr;
typedef std::vector<SEffectTriggerExecutePtr> TVecTriggerExecute;

//同步血量和血上限
struct SEffectSycHP : public SEffectBase
{
	UINT32 dwHP; //当前血量
	UINT32 dwHPMax; //当前血上限

	SEffectSycHP();
	DEF_NEW_DELETE(SEffectSycHP); //使用对象池
	virtual EType_SEffectBase GetClassType() const { return eType_SEffectSycHP; }
};

typedef std::shared_ptr<SEffectSycHP> SEffectSycHPPtr;
typedef std::weak_ptr<SEffectSycHP> SEffectSycHPWtr;
typedef std::vector<SEffectSycHPPtr> TVecSycHP;

//同步灵气
struct SEffectSycAura : public SEffectBase
{
	INT32 iAura; //当前怒气值

	SEffectSycAura();
	DEF_NEW_DELETE(SEffectSycAura); //使用对象池
	virtual EType_SEffectBase GetClassType() const { return eType_SEffectSycAura; }
};

typedef std::shared_ptr<SEffectSycAura> SEffectSycAuraPtr;
typedef std::weak_ptr<SEffectSycAura> SEffectSycAuraWtr;
typedef std::vector<SEffectSycAuraPtr> TVecSycAura;

//同步连携值
struct SEffectSycCombine : public SEffectBase
{
	INT32 iCombine; //当前连携值
	TVecUINT8 vecSycType; //更改方式（见ECombineType）)

	SEffectSycCombine();
	DEF_NEW_DELETE(SEffectSycCombine); //使用对象池
	virtual EType_SEffectBase GetClassType() const { return eType_SEffectSycCombine; }
};

typedef std::shared_ptr<SEffectSycCombine> SEffectSycCombinePtr;
typedef std::weak_ptr<SEffectSycCombine> SEffectSycCombineWtr;
typedef std::vector<SEffectSycCombinePtr> TVecSycCombine;

//连携槽相关操作效果
struct SEffectCombineSlot : public SEffectBase
{
	ECombineSlotOPType eType; //操作方式

	SEffectCombineSlot();
	DEF_NEW_DELETE(SEffectCombineSlot); //使用对象池
	virtual EType_SEffectBase GetClassType() const { return eType_SEffectCombineSlot; }
};

typedef std::shared_ptr<SEffectCombineSlot> SEffectCombineSlotPtr;
typedef std::weak_ptr<SEffectCombineSlot> SEffectCombineSlotWtr;
typedef std::vector<SEffectCombineSlotPtr> TVecCombineSlot;

//破盾效果
struct SEffectBrokenShield : public SEffectBase
{
	INT32 iPoint; //盾牌耐久扣减值

	SEffectBrokenShield();
	DEF_NEW_DELETE(SEffectBrokenShield); //使用对象池
	virtual EType_SEffectBase GetClassType() const { return eType_SEffectBrokenShield; }
};

typedef std::shared_ptr<SEffectBrokenShield> SEffectBrokenShieldPtr;
typedef std::weak_ptr<SEffectBrokenShield> SEffectBrokenShieldWtr;
typedef std::vector<SEffectBrokenShieldPtr> TVecBrokenShield;

//召唤效果
struct SEffectSummon : public SEffectBase
{
	UINT8 byGroupID; //组编号
	UINT8 bySide; //方向编号
	UINT8 byPos; //位置编号
	UINT16 wFighterID; //散仙ID
	UINT32 dwHpMax; //最大血量
	UINT32 dwHp; //当前血量
	UINT32 dwAura; //当前灵气
	UINT32 dwAuraMax; //最大灵气

	SEffectSummon();
	DEF_NEW_DELETE(SEffectSummon); //使用对象池
	virtual EType_SEffectBase GetClassType() const { return eType_SEffectSummon; }
};

typedef std::shared_ptr<SEffectSummon> SEffectSummonPtr;
typedef std::weak_ptr<SEffectSummon> SEffectSummonWtr;
typedef std::vector<SEffectSummonPtr> TVecSummon;

//对话效果
struct SEffectDialog : public SEffectBase
{
	UINT32 dwID; //对话ID

	SEffectDialog();
	DEF_NEW_DELETE(SEffectDialog); //使用对象池
	virtual EType_SEffectBase GetClassType() const { return eType_SEffectDialog; }
};

typedef std::shared_ptr<SEffectDialog> SEffectDialogPtr;
typedef std::weak_ptr<SEffectDialog> SEffectDialogWtr;
typedef std::vector<SEffectDialogPtr> TVecDialog;

//变身效果
struct SEffectTransform : public SEffectBase
{
	UINT16 wFeatureID; //模型ID

	SEffectTransform();
	DEF_NEW_DELETE(SEffectTransform); //使用对象池
	virtual EType_SEffectBase GetClassType() const { return eType_SEffectTransform; }
};

typedef std::shared_ptr<SEffectTransform> SEffectTransformPtr;
typedef std::weak_ptr<SEffectTransform> SEffectTransformWtr;
typedef std::vector<SEffectTransformPtr> TVecTransform;

//部位破坏
struct SEffectPartBroken : public SEffectBase
{
	UINT16 wPartID; //部位ID

	SEffectPartBroken();
	DEF_NEW_DELETE(SEffectPartBroken); //使用对象池
	virtual EType_SEffectBase GetClassType() const { return eType_SEffectPartBroken; }
};

typedef std::shared_ptr<SEffectPartBroken> SEffectPartBrokenPtr;
typedef std::weak_ptr<SEffectPartBroken> SEffectPartBrokenWtr;
typedef std::vector<SEffectPartBrokenPtr> TVecPartBorken;

//被动技能出手动作
struct SEffectBuffAction : public SEffectBase
{
	UINT32 dwSkillID; //技能ID

	SEffectBuffAction();
	DEF_NEW_DELETE(SEffectBuffAction); //使用对象池
	virtual EType_SEffectBase GetClassType() const { return eType_SEffectBuffAction; }
};

typedef std::shared_ptr<SEffectBuffAction> SEffectBuffActionPtr;
typedef std::weak_ptr<SEffectBuffAction> SEffectBuffActionWtr;
typedef std::vector<SEffectBuffActionPtr> TVecBuffAction;

//目标位置，由组ID和位置唯一能找到坐标
struct SBattleTargetPos
{
	UINT8 byGroupID; //组ID
	UINT8 byPos; //位置ID

	SBattleTargetPos();
	SBattleTargetPos(UINT8 byGroupID_, UINT8 byPos_);
};

typedef std::vector<SBattleTargetPos> TVecBattleTargetPos;

//某个fighter一次出手
struct SBattleProgress
{
	TVecUINT8 vecCasterIndex; //主犯(255代表入场技能或者场景技能
	TVecEffects vEffectsBefore; //主犯施法前的效果列表
	UINT32 dwSkillID; //技能ID
	TVecUINT8 vTargetID; //所有目标ID
	TVecUINT8 vTargetIDEx; //波及目标ID
	TVecBattleTargetPos vTargetPos; //技能主执行覆盖区域位置
	TVecEffects vSkillEffects; //技能效果列表
	TVecEffects vEffectsAfter; //主犯施法后效果列表

	SBattleProgress();
#ifdef __GNUG__
	SBattleProgress(const SBattleProgress& src) = default; //默认拷贝构造函数
	SBattleProgress& operator=(const SBattleProgress& rhs) = default; //默认赋值操作符
#endif
	SBattleProgress(SBattleProgress&& src); //转移构造函数
	SBattleProgress& operator=(SBattleProgress&& rhs); //转移赋值操作符
};

typedef std::vector<SBattleProgress> TVecBattleProgress;

//一个回合（所有队伍都出手一次）
struct SBattleRound
{
	UINT32 dwRounds; //当前回合数
	TVecBattleProgress vTargets; //其它人出手

	SBattleRound();
	SBattleRound(UINT32 dwRounds_, const TVecBattleProgress& vTargets_);
#ifdef __GNUG__
	SBattleRound(const SBattleRound& src) = default; //默认拷贝构造函数
	SBattleRound& operator=(const SBattleRound& rhs) = default; //默认赋值操作符
#endif
	SBattleRound(SBattleRound&& src); //转移构造函数
	SBattleRound& operator=(SBattleRound&& rhs); //转移赋值操作符
};

typedef std::vector<SBattleRound> TVecBattleRound;

//战报
struct SBattleReport
{
	UINT64 qwBattleID; //战报ID
	UINT64 qwNextBattleID; //next战报ID
	UINT16 wSceneID; //战斗场景ID
	UINT8 by1Vs1; //0:普通一打多，1：普通一打一，2：boss一打多， 3：boss一打一
	EBattleType eType; //战斗模式：PVP/PVE
	TVecBattleGroup vAGroups; //A队伍里的所有小组
	TVecBattleGroup vBGroups; //B队伍里的所有小组
	TVecBattleFighter vSummons; //战斗中可能召唤的散仙
	TVecBattleRound vRound; //所有的出手回合
	UINT8 byAWaves; //A队剩余波数
	UINT8 byBWaves; //B队剩余波数
	EBattleResult eResult; //战斗结果
	NItemProt::TVecItemGenInfo vecItem; //获得物品
	NItemProt::TVecResource vecResSource; //获得资源

	SBattleReport();
#ifdef __GNUG__
	SBattleReport(const SBattleReport& src) = default; //默认拷贝构造函数
	SBattleReport& operator=(const SBattleReport& rhs) = default; //默认赋值操作符
#endif
	SBattleReport(SBattleReport&& src); //转移构造函数
	SBattleReport& operator=(SBattleReport&& rhs); //转移赋值操作符
};

//战报
struct NewSBattleReport
{
	UINT64 qwHash; //新版本战报校验字段(应该始终为0xFFFFFFFF)

	NewSBattleReport();
	virtual ~NewSBattleReport() { }
	DEF_NEW_DELETE(NewSBattleReport); //使用对象池
	virtual EType_NewSBattleReport GetClassType() const { return eType_NewSBattleReport; }
};

typedef std::shared_ptr<NewSBattleReport> NewSBattleReportPtr;
typedef std::weak_ptr<NewSBattleReport> NewSBattleReportWtr;

//父类：NewSBattleReport的辅助结构体
struct NewSBattleReport_Wrapper
{
	NewSBattleReportPtr ptr;
	NewSBattleReport_Wrapper(const NewSBattleReportPtr& ptr_ = NULL) : ptr(ptr_) { }
};

//版本1战报
struct NewSBattleReportV1 : public NewSBattleReport
{
	UINT64 qwBattleID; //战报ID
	UINT64 qwNextBattleID; //next战报ID
	UINT16 wSceneID; //战斗场景ID
	UINT8 by1Vs1; //0:普通一打多，1：普通一打一，2：boss一打多， 3：boss一打一
	EBattleType eType; //战斗模式：PVP/PVE
	TVecBattleGroup vAGroups; //A队伍里的所有小组
	TVecBattleGroup vBGroups; //B队伍里的所有小组
	TVecBattleFighter vSummons; //战斗中可能召唤的散仙
	TVecBattleRound vRound; //所有的出手回合
	UINT8 byAWaves; //A队剩余波数
	UINT8 byBWaves; //B队剩余波数
	EBattleResult eResult; //战斗结果
	NItemProt::TVecItemGenInfo vecItem; //获得物品
	NItemProt::TVecResource vecResSource; //获得资源

	NewSBattleReportV1();
#ifdef __GNUG__
	NewSBattleReportV1(const NewSBattleReportV1& src) = default; //默认拷贝构造函数
	NewSBattleReportV1& operator=(const NewSBattleReportV1& rhs) = default; //默认赋值操作符
#endif
	NewSBattleReportV1(NewSBattleReportV1&& src); //转移构造函数
	NewSBattleReportV1& operator=(NewSBattleReportV1&& rhs); //转移赋值操作符
	DEF_NEW_DELETE(NewSBattleReportV1); //使用对象池
	virtual EType_NewSBattleReport GetClassType() const { return eType_NewSBattleReportV1; }
};

typedef std::shared_ptr<NewSBattleReportV1> NewSBattleReportV1Ptr;
typedef std::weak_ptr<NewSBattleReportV1> NewSBattleReportV1Wtr;

/////////////////////以下为序列化函数/////////////////////
CInArchive& operator>>(CInArchive&, SEquipShowInfo&);
COutArchive& operator<<(COutArchive&, const SEquipShowInfo&);

CInArchive& operator>>(CInArchive&, STitleAppear&);
COutArchive& operator<<(COutArchive&, const STitleAppear&);

CInArchive& operator>>(CInArchive&, SBattleBuffInfo&);
COutArchive& operator<<(COutArchive&, const SBattleBuffInfo&);

CInArchive& operator>>(CInArchive&, SFeatureBase&);
COutArchive& operator<<(COutArchive&, const SFeatureBase&);
CInArchive& operator>>(CInArchive&, SFeatureBase_Wrapper&);
COutArchive& operator<<(COutArchive&, const SFeatureBase_Wrapper&);
CInArchive& operator>>(CInArchive&, TVecFeatureBase&);
COutArchive& operator<<(COutArchive&, const TVecFeatureBase&);

CInArchive& operator>>(CInArchive&, SMonsterFeature&);
COutArchive& operator<<(COutArchive&, const SMonsterFeature&);
CInArchive& operator>>(CInArchive&, TVecMonsterFeature&);
COutArchive& operator<<(COutArchive&, const TVecMonsterFeature&);

CInArchive& operator>>(CInArchive&, SPlayerFeature&);
COutArchive& operator<<(COutArchive&, const SPlayerFeature&);
CInArchive& operator>>(CInArchive&, TVecPlayerFeature&);
COutArchive& operator<<(COutArchive&, const TVecPlayerFeature&);

CInArchive& operator>>(CInArchive&, SHeroFeature&);
COutArchive& operator<<(COutArchive&, const SHeroFeature&);
CInArchive& operator>>(CInArchive&, TVecHeroFeature&);
COutArchive& operator<<(COutArchive&, const TVecHeroFeature&);

CInArchive& operator>>(CInArchive&, SFormationFeature&);
COutArchive& operator<<(COutArchive&, const SFormationFeature&);
CInArchive& operator>>(CInArchive&, TVecFormationFeature&);
COutArchive& operator<<(COutArchive&, const TVecFormationFeature&);

CInArchive& operator>>(CInArchive&, SFieldFeature&);
COutArchive& operator<<(COutArchive&, const SFieldFeature&);

CInArchive& operator>>(CInArchive&, SBeautyFeature&);
COutArchive& operator<<(COutArchive&, const SBeautyFeature&);

CInArchive& operator>>(CInArchive&, SPlayerFeatureWithBuff&);
COutArchive& operator<<(COutArchive&, const SPlayerFeatureWithBuff&);
CInArchive& operator>>(CInArchive&, TVecPlayerFeatureWithBuff&);
COutArchive& operator<<(COutArchive&, const TVecPlayerFeatureWithBuff&);

CInArchive& operator>>(CInArchive&, SMonsterFeatureWithBuff&);
COutArchive& operator<<(COutArchive&, const SMonsterFeatureWithBuff&);
CInArchive& operator>>(CInArchive&, TVecMonsterFeatureWithBuff&);
COutArchive& operator<<(COutArchive&, const TVecMonsterFeatureWithBuff&);

CInArchive& operator>>(CInArchive&, SBattleFightSkillInfo&);
COutArchive& operator<<(COutArchive&, const SBattleFightSkillInfo&);

CInArchive& operator>>(CInArchive&, STeamSkillInfo&);
COutArchive& operator<<(COutArchive&, const STeamSkillInfo&);

CInArchive& operator>>(CInArchive&, SBattleFighterInfo&);
COutArchive& operator<<(COutArchive&, const SBattleFighterInfo&);

CInArchive& operator>>(CInArchive&, SBattleFighter&);
COutArchive& operator<<(COutArchive&, const SBattleFighter&);

CInArchive& operator>>(CInArchive&, SBattleGroup&);
COutArchive& operator<<(COutArchive&, const SBattleGroup&);

CInArchive& operator>>(CInArchive&, SEffectBase&);
COutArchive& operator<<(COutArchive&, const SEffectBase&);
CInArchive& operator>>(CInArchive&, SEffectBase_Wrapper&);
COutArchive& operator<<(COutArchive&, const SEffectBase_Wrapper&);
CInArchive& operator>>(CInArchive&, TVecEffects&);
COutArchive& operator<<(COutArchive&, const TVecEffects&);

CInArchive& operator>>(CInArchive&, SEffectDecHP&);
COutArchive& operator<<(COutArchive&, const SEffectDecHP&);
CInArchive& operator>>(CInArchive&, TVecDecHP&);
COutArchive& operator<<(COutArchive&, const TVecDecHP&);

CInArchive& operator>>(CInArchive&, SEffectAddStatus&);
COutArchive& operator<<(COutArchive&, const SEffectAddStatus&);
CInArchive& operator>>(CInArchive&, TVecAddStatus&);
COutArchive& operator<<(COutArchive&, const TVecAddStatus&);

CInArchive& operator>>(CInArchive&, SEffectAddHP&);
COutArchive& operator<<(COutArchive&, const SEffectAddHP&);
CInArchive& operator>>(CInArchive&, TVecAddHP&);
COutArchive& operator<<(COutArchive&, const TVecAddHP&);

CInArchive& operator>>(CInArchive&, SEffectRelive&);
COutArchive& operator<<(COutArchive&, const SEffectRelive&);
CInArchive& operator>>(CInArchive&, TVecRelive&);
COutArchive& operator<<(COutArchive&, const TVecRelive&);

CInArchive& operator>>(CInArchive&, SEffectCounter&);
COutArchive& operator<<(COutArchive&, const SEffectCounter&);
CInArchive& operator>>(CInArchive&, TVecCounter&);
COutArchive& operator<<(COutArchive&, const TVecCounter&);

CInArchive& operator>>(CInArchive&, SEffectStateBuffAdd&);
COutArchive& operator<<(COutArchive&, const SEffectStateBuffAdd&);
CInArchive& operator>>(CInArchive&, TVecStateBuffAdd&);
COutArchive& operator<<(COutArchive&, const TVecStateBuffAdd&);

CInArchive& operator>>(CInArchive&, SEffectStateBuffEffect&);
COutArchive& operator<<(COutArchive&, const SEffectStateBuffEffect&);
CInArchive& operator>>(CInArchive&, TVecStateBuffEffect&);
COutArchive& operator<<(COutArchive&, const TVecStateBuffEffect&);

CInArchive& operator>>(CInArchive&, SEffectStateBuffDec&);
COutArchive& operator<<(COutArchive&, const SEffectStateBuffDec&);
CInArchive& operator>>(CInArchive&, TVecStateBuffDec&);
COutArchive& operator<<(COutArchive&, const TVecStateBuffDec&);

CInArchive& operator>>(CInArchive&, SEffectStateBuffLast&);
COutArchive& operator<<(COutArchive&, const SEffectStateBuffLast&);
CInArchive& operator>>(CInArchive&, TVecStateBuffLast&);
COutArchive& operator<<(COutArchive&, const TVecStateBuffLast&);

CInArchive& operator>>(CInArchive&, SEffectAttrBuffAdd&);
COutArchive& operator<<(COutArchive&, const SEffectAttrBuffAdd&);
CInArchive& operator>>(CInArchive&, TVecAttrBuffAdd&);
COutArchive& operator<<(COutArchive&, const TVecAttrBuffAdd&);

CInArchive& operator>>(CInArchive&, SEffectAttrBuffDec&);
COutArchive& operator<<(COutArchive&, const SEffectAttrBuffDec&);
CInArchive& operator>>(CInArchive&, TVecAttrBuffDec&);
COutArchive& operator<<(COutArchive&, const TVecAttrBuffDec&);

CInArchive& operator>>(CInArchive&, SEffectDied&);
COutArchive& operator<<(COutArchive&, const SEffectDied&);
CInArchive& operator>>(CInArchive&, TVecDied&);
COutArchive& operator<<(COutArchive&, const TVecDied&);

CInArchive& operator>>(CInArchive&, SEffectShieldAbsorb&);
COutArchive& operator<<(COutArchive&, const SEffectShieldAbsorb&);
CInArchive& operator>>(CInArchive&, TVecShieldAbsorb&);
COutArchive& operator<<(COutArchive&, const TVecShieldAbsorb&);

CInArchive& operator>>(CInArchive&, SEffectTriggerExecute&);
COutArchive& operator<<(COutArchive&, const SEffectTriggerExecute&);
CInArchive& operator>>(CInArchive&, TVecTriggerExecute&);
COutArchive& operator<<(COutArchive&, const TVecTriggerExecute&);

CInArchive& operator>>(CInArchive&, SEffectSycHP&);
COutArchive& operator<<(COutArchive&, const SEffectSycHP&);
CInArchive& operator>>(CInArchive&, TVecSycHP&);
COutArchive& operator<<(COutArchive&, const TVecSycHP&);

CInArchive& operator>>(CInArchive&, SEffectSycAura&);
COutArchive& operator<<(COutArchive&, const SEffectSycAura&);
CInArchive& operator>>(CInArchive&, TVecSycAura&);
COutArchive& operator<<(COutArchive&, const TVecSycAura&);

CInArchive& operator>>(CInArchive&, SEffectSycCombine&);
COutArchive& operator<<(COutArchive&, const SEffectSycCombine&);
CInArchive& operator>>(CInArchive&, TVecSycCombine&);
COutArchive& operator<<(COutArchive&, const TVecSycCombine&);

CInArchive& operator>>(CInArchive&, SEffectCombineSlot&);
COutArchive& operator<<(COutArchive&, const SEffectCombineSlot&);
CInArchive& operator>>(CInArchive&, TVecCombineSlot&);
COutArchive& operator<<(COutArchive&, const TVecCombineSlot&);

CInArchive& operator>>(CInArchive&, SEffectBrokenShield&);
COutArchive& operator<<(COutArchive&, const SEffectBrokenShield&);
CInArchive& operator>>(CInArchive&, TVecBrokenShield&);
COutArchive& operator<<(COutArchive&, const TVecBrokenShield&);

CInArchive& operator>>(CInArchive&, SEffectSummon&);
COutArchive& operator<<(COutArchive&, const SEffectSummon&);
CInArchive& operator>>(CInArchive&, TVecSummon&);
COutArchive& operator<<(COutArchive&, const TVecSummon&);

CInArchive& operator>>(CInArchive&, SEffectDialog&);
COutArchive& operator<<(COutArchive&, const SEffectDialog&);
CInArchive& operator>>(CInArchive&, TVecDialog&);
COutArchive& operator<<(COutArchive&, const TVecDialog&);

CInArchive& operator>>(CInArchive&, SEffectTransform&);
COutArchive& operator<<(COutArchive&, const SEffectTransform&);
CInArchive& operator>>(CInArchive&, TVecTransform&);
COutArchive& operator<<(COutArchive&, const TVecTransform&);

CInArchive& operator>>(CInArchive&, SEffectPartBroken&);
COutArchive& operator<<(COutArchive&, const SEffectPartBroken&);
CInArchive& operator>>(CInArchive&, TVecPartBorken&);
COutArchive& operator<<(COutArchive&, const TVecPartBorken&);

CInArchive& operator>>(CInArchive&, SEffectBuffAction&);
COutArchive& operator<<(COutArchive&, const SEffectBuffAction&);
CInArchive& operator>>(CInArchive&, TVecBuffAction&);
COutArchive& operator<<(COutArchive&, const TVecBuffAction&);

CInArchive& operator>>(CInArchive&, SBattleTargetPos&);
COutArchive& operator<<(COutArchive&, const SBattleTargetPos&);

CInArchive& operator>>(CInArchive&, SBattleProgress&);
COutArchive& operator<<(COutArchive&, const SBattleProgress&);

CInArchive& operator>>(CInArchive&, SBattleRound&);
COutArchive& operator<<(COutArchive&, const SBattleRound&);

CInArchive& operator>>(CInArchive&, SBattleReport&);
COutArchive& operator<<(COutArchive&, const SBattleReport&);

CInArchive& operator>>(CInArchive&, NewSBattleReport&);
COutArchive& operator<<(COutArchive&, const NewSBattleReport&);
CInArchive& operator>>(CInArchive&, NewSBattleReport_Wrapper&);
COutArchive& operator<<(COutArchive&, const NewSBattleReport_Wrapper&);

CInArchive& operator>>(CInArchive&, NewSBattleReportV1&);
COutArchive& operator<<(COutArchive&, const NewSBattleReportV1&);

#ifdef PROT_USE_XML
/////////////////////以下为XML转换函数/////////////////////
bool FromXML(TiXmlElement&, SEquipShowInfo&);
bool ToXML(const SEquipShowInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecEquipShowInfo&);
bool VectorToXML(const TVecEquipShowInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, STitleAppear&);
bool ToXML(const STitleAppear&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecTitleAppear&);
bool VectorToXML(const TVecTitleAppear&, TiXmlElement&);

bool FromXML(TiXmlElement&, SBattleBuffInfo&);
bool ToXML(const SBattleBuffInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecBattleBuffInfo&);
bool VectorToXML(const TVecBattleBuffInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SFeatureBase&);
bool ToXML(const SFeatureBase&, TiXmlElement&);
bool SuperFromXML(TiXmlElement&, SFeatureBasePtr&);
bool SuperToXML(const SFeatureBase&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecFeatureBase&);
bool VectorToXML(const TVecFeatureBase&, TiXmlElement&);

bool FromXML(TiXmlElement&, SMonsterFeature&);
bool ToXML(const SMonsterFeature&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecMonsterFeature&);
bool VectorToXML(const TVecMonsterFeature&, TiXmlElement&);

bool FromXML(TiXmlElement&, SPlayerFeature&);
bool ToXML(const SPlayerFeature&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecPlayerFeature&);
bool VectorToXML(const TVecPlayerFeature&, TiXmlElement&);

bool FromXML(TiXmlElement&, SHeroFeature&);
bool ToXML(const SHeroFeature&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecHeroFeature&);
bool VectorToXML(const TVecHeroFeature&, TiXmlElement&);

bool FromXML(TiXmlElement&, SFormationFeature&);
bool ToXML(const SFormationFeature&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecFormationFeature&);
bool VectorToXML(const TVecFormationFeature&, TiXmlElement&);

bool FromXML(TiXmlElement&, SFieldFeature&);
bool ToXML(const SFieldFeature&, TiXmlElement&);

bool FromXML(TiXmlElement&, SBeautyFeature&);
bool ToXML(const SBeautyFeature&, TiXmlElement&);

bool FromXML(TiXmlElement&, SPlayerFeatureWithBuff&);
bool ToXML(const SPlayerFeatureWithBuff&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecPlayerFeatureWithBuff&);
bool VectorToXML(const TVecPlayerFeatureWithBuff&, TiXmlElement&);

bool FromXML(TiXmlElement&, SMonsterFeatureWithBuff&);
bool ToXML(const SMonsterFeatureWithBuff&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecMonsterFeatureWithBuff&);
bool VectorToXML(const TVecMonsterFeatureWithBuff&, TiXmlElement&);

bool FromXML(TiXmlElement&, SBattleFightSkillInfo&);
bool ToXML(const SBattleFightSkillInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecFightSkillInfo&);
bool VectorToXML(const TVecFightSkillInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, STeamSkillInfo&);
bool ToXML(const STeamSkillInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecTeamSkillInfo&);
bool VectorToXML(const TVecTeamSkillInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SBattleFighterInfo&);
bool ToXML(const SBattleFighterInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecFighterInfo&);
bool VectorToXML(const TVecFighterInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SBattleFighter&);
bool ToXML(const SBattleFighter&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecBattleFighter&);
bool VectorToXML(const TVecBattleFighter&, TiXmlElement&);

bool FromXML(TiXmlElement&, SBattleGroup&);
bool ToXML(const SBattleGroup&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecBattleGroup&);
bool VectorToXML(const TVecBattleGroup&, TiXmlElement&);

bool FromXML(TiXmlElement&, SEffectBase&);
bool ToXML(const SEffectBase&, TiXmlElement&);
bool SuperFromXML(TiXmlElement&, SEffectBasePtr&);
bool SuperToXML(const SEffectBase&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecEffects&);
bool VectorToXML(const TVecEffects&, TiXmlElement&);

bool FromXML(TiXmlElement&, SEffectDecHP&);
bool ToXML(const SEffectDecHP&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecDecHP&);
bool VectorToXML(const TVecDecHP&, TiXmlElement&);

bool FromXML(TiXmlElement&, SEffectAddStatus&);
bool ToXML(const SEffectAddStatus&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecAddStatus&);
bool VectorToXML(const TVecAddStatus&, TiXmlElement&);

bool FromXML(TiXmlElement&, SEffectAddHP&);
bool ToXML(const SEffectAddHP&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecAddHP&);
bool VectorToXML(const TVecAddHP&, TiXmlElement&);

bool FromXML(TiXmlElement&, SEffectRelive&);
bool ToXML(const SEffectRelive&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecRelive&);
bool VectorToXML(const TVecRelive&, TiXmlElement&);

bool FromXML(TiXmlElement&, SEffectCounter&);
bool ToXML(const SEffectCounter&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecCounter&);
bool VectorToXML(const TVecCounter&, TiXmlElement&);

bool FromXML(TiXmlElement&, SEffectStateBuffAdd&);
bool ToXML(const SEffectStateBuffAdd&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecStateBuffAdd&);
bool VectorToXML(const TVecStateBuffAdd&, TiXmlElement&);

bool FromXML(TiXmlElement&, SEffectStateBuffEffect&);
bool ToXML(const SEffectStateBuffEffect&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecStateBuffEffect&);
bool VectorToXML(const TVecStateBuffEffect&, TiXmlElement&);

bool FromXML(TiXmlElement&, SEffectStateBuffDec&);
bool ToXML(const SEffectStateBuffDec&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecStateBuffDec&);
bool VectorToXML(const TVecStateBuffDec&, TiXmlElement&);

bool FromXML(TiXmlElement&, SEffectStateBuffLast&);
bool ToXML(const SEffectStateBuffLast&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecStateBuffLast&);
bool VectorToXML(const TVecStateBuffLast&, TiXmlElement&);

bool FromXML(TiXmlElement&, SEffectAttrBuffAdd&);
bool ToXML(const SEffectAttrBuffAdd&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecAttrBuffAdd&);
bool VectorToXML(const TVecAttrBuffAdd&, TiXmlElement&);

bool FromXML(TiXmlElement&, SEffectAttrBuffDec&);
bool ToXML(const SEffectAttrBuffDec&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecAttrBuffDec&);
bool VectorToXML(const TVecAttrBuffDec&, TiXmlElement&);

bool FromXML(TiXmlElement&, SEffectDied&);
bool ToXML(const SEffectDied&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecDied&);
bool VectorToXML(const TVecDied&, TiXmlElement&);

bool FromXML(TiXmlElement&, SEffectShieldAbsorb&);
bool ToXML(const SEffectShieldAbsorb&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecShieldAbsorb&);
bool VectorToXML(const TVecShieldAbsorb&, TiXmlElement&);

bool FromXML(TiXmlElement&, SEffectTriggerExecute&);
bool ToXML(const SEffectTriggerExecute&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecTriggerExecute&);
bool VectorToXML(const TVecTriggerExecute&, TiXmlElement&);

bool FromXML(TiXmlElement&, SEffectSycHP&);
bool ToXML(const SEffectSycHP&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecSycHP&);
bool VectorToXML(const TVecSycHP&, TiXmlElement&);

bool FromXML(TiXmlElement&, SEffectSycAura&);
bool ToXML(const SEffectSycAura&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecSycAura&);
bool VectorToXML(const TVecSycAura&, TiXmlElement&);

bool FromXML(TiXmlElement&, SEffectSycCombine&);
bool ToXML(const SEffectSycCombine&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecSycCombine&);
bool VectorToXML(const TVecSycCombine&, TiXmlElement&);

bool FromXML(TiXmlElement&, SEffectCombineSlot&);
bool ToXML(const SEffectCombineSlot&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecCombineSlot&);
bool VectorToXML(const TVecCombineSlot&, TiXmlElement&);

bool FromXML(TiXmlElement&, SEffectBrokenShield&);
bool ToXML(const SEffectBrokenShield&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecBrokenShield&);
bool VectorToXML(const TVecBrokenShield&, TiXmlElement&);

bool FromXML(TiXmlElement&, SEffectSummon&);
bool ToXML(const SEffectSummon&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecSummon&);
bool VectorToXML(const TVecSummon&, TiXmlElement&);

bool FromXML(TiXmlElement&, SEffectDialog&);
bool ToXML(const SEffectDialog&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecDialog&);
bool VectorToXML(const TVecDialog&, TiXmlElement&);

bool FromXML(TiXmlElement&, SEffectTransform&);
bool ToXML(const SEffectTransform&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecTransform&);
bool VectorToXML(const TVecTransform&, TiXmlElement&);

bool FromXML(TiXmlElement&, SEffectPartBroken&);
bool ToXML(const SEffectPartBroken&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecPartBorken&);
bool VectorToXML(const TVecPartBorken&, TiXmlElement&);

bool FromXML(TiXmlElement&, SEffectBuffAction&);
bool ToXML(const SEffectBuffAction&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecBuffAction&);
bool VectorToXML(const TVecBuffAction&, TiXmlElement&);

bool FromXML(TiXmlElement&, SBattleTargetPos&);
bool ToXML(const SBattleTargetPos&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecBattleTargetPos&);
bool VectorToXML(const TVecBattleTargetPos&, TiXmlElement&);

bool FromXML(TiXmlElement&, SBattleProgress&);
bool ToXML(const SBattleProgress&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecBattleProgress&);
bool VectorToXML(const TVecBattleProgress&, TiXmlElement&);

bool FromXML(TiXmlElement&, SBattleRound&);
bool ToXML(const SBattleRound&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecBattleRound&);
bool VectorToXML(const TVecBattleRound&, TiXmlElement&);

bool FromXML(TiXmlElement&, SBattleReport&);
bool ToXML(const SBattleReport&, TiXmlElement&);

bool FromXML(TiXmlElement&, NewSBattleReport&);
bool ToXML(const NewSBattleReport&, TiXmlElement&);
bool SuperFromXML(TiXmlElement&, NewSBattleReportPtr&);
bool SuperToXML(const NewSBattleReport&, TiXmlElement&);

bool FromXML(TiXmlElement&, NewSBattleReportV1&);
bool ToXML(const NewSBattleReportV1&, TiXmlElement&);
#endif //PROT_USE_XML

} //namespace NBattleGS
