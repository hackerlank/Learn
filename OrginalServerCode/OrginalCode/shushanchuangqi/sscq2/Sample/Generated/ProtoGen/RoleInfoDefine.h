/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    RoleInfoDefine.h
//  Purpose:      角色数据定义
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
#include "AchievementProt.h"
#include "ArenaGS.h"
#include "Beauty.h"
#include "CollectionProt.h"
#include "DemonTower.h"
#include "DungeonProt.h"
#include "ExchangeShopProt.h"
#include "FighterProt.h"
#include "FriendProt.h"
#include "GroupTaskProt.h"
#include "GuardEMeiProt.h"
#include "Horse.h"
#include "ItemProt.h"
#include "LevelPrize.h"
#include "ProtoCommon.h"
#include "ShengLingProt.h"
#include "ShipProt.h"
#include "TaskProt.h"
#include "TreasureHuntProt.h"
#include "TripodProt.h"
#include "YaMenTaskProt.h"

namespace NRoleInfoDefine
{

/////////////////////以下为类型定义/////////////////////
//战报类型
enum EBattleReportType
{
	eTypeLadder //天梯
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EBattleReportType);
bool EnumStrToVal(const char*, EBattleReportType&);
#endif //PROT_USE_XML
const char* GetDescription(EBattleReportType);

//战报发起类型
enum EBattleActionType
{
	eTypeAttack, //玩家进攻
	eTypeDefense, //玩家防守
	eTypeALL //防守和进攻
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EBattleActionType);
bool EnumStrToVal(const char*, EBattleActionType&);
#endif //PROT_USE_XML
const char* GetDescription(EBattleActionType);

//兽魂种类
enum EBeastSoulType
{
	eBeastSoulNone = 0, //无加成
	eBeastSoulAtttack, //攻击之魂
	eBeastSoulHP, //生命之魂
	eBeastSoulCritical, //暴击之魂
	eBeastSoulCounter, //反击之魂
	eBeastSoulSpeed, //身法之魂
	eBeastSoulDefence, //防御之魂
	eBeastSoulHit, //命中之魂
	eBeastSoulDodge, //闪避之魂
	eBeastSoulMax //最大
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EBeastSoulType);
bool EnumStrToVal(const char*, EBeastSoulType&);
#endif //PROT_USE_XML

//数据类型
enum EDataType
{
	eTypeRoleBaseInfo, //玩家基本数据
	eTypeItemInfo, //玩家物品数据
	eTypePlayerDgn, //玩家副本数据
	eTypeFighterInfo, //玩家将信息
	eTypeTaskInfo, //玩家任务信息
	eTypeSkillInfo, //技能信息
	eTypePassiveSkillInfo, //被动技能信息
	eTypeFriendInfo, //关系信息
	eTypeVarInfo, //关系信息
	eTypeCittaInfo, //玩家心法数据
	eTypeSlotsInfo, //玩家/其他槽心法数据
	eTypeTrumpInfo, //法宝信息
	eTypeEquipTrumpInfo, //装备法宝信息
	eTypeEquipTrumpShuffleInfo, //装备法宝洗炼信息
	eTypeFormationInfo, //阵形信息
	eTypePetDataInfo, //阵灵信息
	eTypeRolePetInfo, //阵灵全局信息
	eTypeBeastSoulInfo, //兽魂信息
	eTypeTripodFireInfo, //九疑鼎的火种信息
	eTypeArena, //斗剑信息
	eTypeBuffInfo, //Buff信息
	eTypeFashionInfo, //时装信息
	eTypeSoulSpaceInfo, //魄空间信息
	eTypeBubbleInfo, //气泡信息
	eTypeHorseDBInfo, //坐骑信息
	eTypeGroupTask, //师门任务
	eTypeYaMenTask, //衙门任务
	eTypeActivityTask, //活跃度任务
	eTypeTitle, //称号
	eTypeAchievementInfo, //成就
	eTypeCollectionInfo, //收藏
	eTypeAttacked, //玩家被攻击信息
	eTypeExchangedItem, //玩家兑换商品信息
	eTypeSweep, //玩家扫荡信息
	eTypePendRes, //玩家暂存信息
	eTypeXinFaInfo, //心法信息
	eTypeLevelPrize, //心法信息
	eTypeYelloDiamond, //黄钻信息
	eTypeEventInfo, //事件信息
	eTypeBuyItemLimit, //商品数量限购信息
	eTypeDayTarget, //七日目标活动
	eTypeFighterComination, //玩家的散仙组合信息
	eTypeBattleArray, //破阵信息
	eTypeAutoStore, //动态存储信息
	eTypeTH, //寻宝信息
	eTypeBeauty, //美女系统
	eTypeFightFormation, //新阵型系统
	eTypeFightHero, //散仙数据
	eTypeShip, //金船
	eTypeGuardEMei, //守卫峨眉
	eTypeGemstone, //宝石
	eTypeShengLing, //圣陵信息
	eTypeShengLingPrize, //圣陵奖励信息
	eTypeMax //最大值
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EDataType);
bool EnumStrToVal(const char*, EDataType&);
#endif //PROT_USE_XML
const char* GetDescription(EDataType);

//EDataType:eRoleBaseInfo
struct RoleBaseInfo
{
	std::string strName; //玩家名字
	NProtoCommon::ECareerType eCareer; //职业
	NProtoCommon::ESexType eSex; //性别
	UINT16 wMapID; //地图ID
	float fX; //X坐标
	float fY; //Y坐标
	UINT64 qwDgnId; //副本实例ID
	UINT16 dwDgnTypeID; //副本模版ID
	UINT16 wDgnMapId; //副本地图ID
	float fDgnfX; //副本X坐标
	float fDgnfY; //副本Y坐标
	UINT16 wBagMax; //背包容量
	UINT16 wDepotMax; //仓库容量
	UINT32 dwPendSilver; //延迟发放的银币
	UINT32 dwPendCoupon; //延迟发放的礼券
	UINT32 dwPendExp; //延迟发放的经验
	UINT32 dwPendGold; //延迟发放的仙石
	UINT32 dwDemonTowerFloorID; //通关镇妖塔层数
	UINT32 dwDemonTowerPrizeFloorID; //镇妖塔层数
	std::string strGuide; //新手引导内容
	std::string szIcon; //功能开放标签
	std::string szIconDel; //功能关闭标签
	std::string szIconActive; //功能关闭标签
	UINT32 dwPackNextUnlockTime; //背包下次解锁时间
	UINT32 dwActivity; //活跃值
	UINT64 qwSittingPlayer; //一起双修的人
	std::string szDgnStarAward; //副本星级领奖
	std::string strCreateIP; //玩家创角时IP
	std::string strLoginIP; //玩家登录时IP
	UINT32 dwLuckyCoupon; //幸运券
	UINT8 byLevel; //玩家等级
	UINT64 qwExp; //玩家经验值
	UINT8 byNation; //国家
	UINT8 byGMLvl; //GM权限
	UINT32 dwTotalRecharge; //充值金额
	UINT32 dwLoginTime; //上次登陆时间
	UINT32 dwOfflineTime; //上次下线时间
	UINT32 dwLockExpireTime; //被封禁结束时间
	UINT32 dwForbExpireTime; //被禁言结束时间
	UINT32 dwGold; //充值仙石
	UINT32 dwFreeGold; //免费仙石
	UINT32 dwSilver; //银币
	UINT32 dwCoupon; //礼券
	UINT32 dwSoul; //魂魄
	UINT32 dwPrestige; //声望
	UINT32 dwHonor; //荣誉
	UINT32 dwPExp; //修为
	UINT32 dwAction; //体力
	UINT32 dwPoten; //渡劫点数
	UINT32 dwReiki; //副本星级
	UINT32 dwDemonSoul; //锁妖塔魂值
	UINT32 dwSoulAttack; //攻击之魂
	UINT32 dwSoulHp; //生命之魂
	UINT32 dwSoulCritical; //暴击之魂
	UINT32 dwSoulCounter; //破击之魂
	UINT32 dwSoulSpeed; //身法之魂
	UINT32 dwSoulDefence; //防御之魂
	UINT32 dwSoulHit; //命中之魂
	UINT32 dwSoulDodge; //闪避之魂
	UINT32 dwStampHuang; //黄阶除魔印
	UINT32 dwStampXuan; //玄阶除魔印
	UINT32 dwStampDi; //地阶除魔印
	UINT32 dwStampTian; //天阶除魔印
	UINT32 dwStampXing; //星阶除魔印
	UINT32 dwStampYue; //月阶除魔印
	UINT32 dwStampDi2; //帝阶除魔印
	UINT32 dwStampXian; //仙阶除魔印
	UINT32 dwStampSheng; //圣阶除魔印
	UINT32 dwStampFo; //佛阶除魔印
	UINT32 dwLoveHeart; //爱心
	UINT32 dwBlueFairyFate; //蓝色仙缘
	UINT32 dwPurpleFairyFate; //紫色仙缘
	UINT32 dwOrangeFairyFate; //橙色仙缘
	UINT32 dwDuJieFu; //散仙渡劫符数量
	UINT32 dwBTPoint; //战斗力
	std::string szOwnTitle; //拥有的称号
	std::string szEquipTitle; //装备的称号
	UINT8 byDomain; //渠道
	UINT8 byDomainLvl; //渠道等级
	UINT8 byDisplayLvl; //显示等级
	UINT8 byDomainYear; //年费
	std::string szOpenId; //szOpenId
	std::string szOpenKey; //szOpenKey
	std::string strSign; //签名
	UINT16 wMood; //心情表情
	UINT16 wAchievementLevel; //成就等级
	UINT32 dwAchievementAP; //成就点
	UINT16 wCollectLevel; //收藏等级
	UINT32 dwCollectAP; //收藏点
	UINT64 qwInvitedID; //邀请
	UINT8 byWallow; //防沉迷
	UINT32 dwIndulgeKickTime; //防沉迷t人时间
	UINT8 byYDLevel; //玩家QQ黄钻等级
	UINT32 dwCreateTime; //创角时间
	UINT16 wLastSaveMapID; //保存地图ID
	float fLastSaveX; //保存X坐标
	float fLastSaveY; //保存Y坐标

	RoleBaseInfo();
#ifdef __GNUG__
	RoleBaseInfo(const RoleBaseInfo& src) = default; //默认拷贝构造函数
	RoleBaseInfo& operator=(const RoleBaseInfo& rhs) = default; //默认赋值操作符
#endif
	RoleBaseInfo(RoleBaseInfo&& src); //转移构造函数
	RoleBaseInfo& operator=(RoleBaseInfo&& rhs); //转移赋值操作符
};

typedef std::vector<RoleBaseInfo> TVecRoleBaseInfo;

//EDataType:eTypePlayerDgn：剧情副本，特定日期副本可以考虑删除
struct RoleDgnInfo
{
	UINT32 dwDgnType; //副本类型
	UINT32 dwLastEnterTimer; //最近副本支付代价时间
	UINT8 byCost; //副本支付代价,是否没有消费,0表示已经消费
	UINT32 dwEnterTimesAppend; //额外增加的副本进入次数
	UINT32 dwAppendEndTimer; //额外增加的副本进入次数的到期时间
	UINT32 dwEnterTimes; //当前副本进入次数
	UINT32 dwLastCompleteTimer; //最近副本通过时间
	UINT32 dwCompleteTimes; //副本通过次数，通过就记录下
	UINT16 wMinTurns; //通过的最少回合数
	UINT32 dwBuyTimer; //最近购买的时间
	UINT32 dwBuyTimesToday; //当天购买的次数
	UINT32 dwFinishTimesToday; //今日完成副本次数

	RoleDgnInfo();
};

typedef std::vector<RoleDgnInfo> TVecRoleDgnInfo;

//任务存储结构
struct RoleTaskInfo
{
	UINT32 dwTaskId; //任务Id
	NTaskProt::ETaskState eTaskState; //任务状态
	UINT32 dwAcceptTimes; //接受任务次数
	UINT32 dwLastAcceptTimer; //最近任务接受时间
	UINT32 dwFinishTimes; //完成任务次数
	UINT32 dwLastFinishTimer; //最近完成任务时间
	UINT8 byProcessType1; //进度1的类型
	UINT32 dwProcessParam11; //进度1的第1个参数
	UINT32 dwProcessParam12; //进度1的第2个参数
	UINT8 byProcessType2; //进度2的类型
	UINT32 dwProcessParam21; //进度2的第1个参数
	UINT32 dwProcessParam22; //进度2的第2个参数
	UINT8 byProcessType3; //进度3的类型
	UINT32 dwProcessParam31; //进度3的第1个参数
	UINT32 dwProcessParam32; //进度3的第2个参数
	UINT32 dwRepeatAcceptTimes; //当前有效接任务次数

	RoleTaskInfo();
};

typedef std::vector<RoleTaskInfo> TVecRoleTaskInfo;

//玩家变量数据
struct SVarsDBInfo
{
	UINT64 qwRoleID; //玩家RoleId
	UINT8 byServerType; //服务器类型
	UINT16 wVar; //变量ID
	UINT64 qwValue; //变量值
	UINT32 dwExpired; //过期时间

	SVarsDBInfo();
	SVarsDBInfo(UINT64 qwRoleID_, UINT8 byServerType_, UINT16 wVar_, UINT64 qwValue_, UINT32 dwExpired_);
};

typedef std::vector<SVarsDBInfo> TVecVarsDBInfo;

//系统变量数据
struct SGameVarsDBInfo
{
	UINT8 byServerType; //服务器类型
	UINT16 wVar; //变量ID
	UINT64 qwValue; //变量值
	UINT32 dwExpired; //过期时间

	SGameVarsDBInfo();
	SGameVarsDBInfo(UINT8 byServerType_, UINT16 wVar_, UINT64 qwValue_, UINT32 dwExpired_);
};

typedef std::vector<SGameVarsDBInfo> TVecGameVarsDBInfo;

//EDataType:eTypeSlotsInfo:玩家各种槽数据
struct SRoleSlotsInfo
{
	UINT64 qwRoleID; //玩家RoleID
	UINT64 qwOwnerID; //槽拥有者ID
	NItemProt::EStoreType eStoreType; //槽类型
	UINT16 wMaxSlot; //槽允许的最大数量
	UINT16 wMaxAvaliableSlot; //槽当前的最大数量

	SRoleSlotsInfo();
	SRoleSlotsInfo(UINT64 qwRoleID_, UINT64 qwOwnerID_, NItemProt::EStoreType eStoreType_, UINT16 wMaxSlot_, UINT16 wMaxAvaliableSlot_);
};

typedef std::vector<SRoleSlotsInfo> TVecRoleSlotsInfo;

//阵型信息
struct SFormationInfo
{
	UINT16 wFormationID; //阵型ID
	UINT8 bySelected; //是否启用

	SFormationInfo();
	SFormationInfo(UINT16 wFormationID_, UINT8 bySelected_);
};

typedef std::vector<SFormationInfo> TVecFormationInfo;

//阵灵信息
struct SPetDataInfo
{
	UINT16 wPetID; //阵灵ID
	UINT8 bySelected; //是否启用: 0-未启用 1-出战跟随 2-出战不跟随
	UINT8 byLevel; //阵灵等级
	UINT32 dwExp; //阵灵经验

	SPetDataInfo();
	SPetDataInfo(UINT16 wPetID_, UINT8 bySelected_, UINT8 byLevel_, UINT32 dwExp_);
};

typedef std::vector<SPetDataInfo> TVecPetDataInfo;

//阵灵全局信息
struct SRolePetInfo
{
	UINT32 dwExp; //阵灵经验
	UINT8 byLevel; //阵灵等级
	UINT32 dwSpirit; //阵灵灵力值

	SRolePetInfo();
	SRolePetInfo(UINT32 dwExp_, UINT8 byLevel_, UINT32 dwSpirit_);
};

typedef std::vector<SRolePetInfo> TVecRolePetInfo;

//兽魂信息
struct SBeastSoulInfo
{
	EBeastSoulType eType; //兽魂类型
	UINT8 byRank; //兽魂星图等级
	UINT8 byLevel; //兽魂星魂等级

	SBeastSoulInfo();
	SBeastSoulInfo(EBeastSoulType eType_, UINT8 byRank_, UINT8 byLevel_);
};

typedef std::vector<SBeastSoulInfo> TVecBeastSoulInfo;

//玩家魄空间信息
struct SSoulSpaceInfo
{
	UINT64 qwRoleID; //角色ID
	UINT64 dwSoulSpaceID; //魄空间ID
	UINT64 dwSoulSpaceLevel; //魄空间等级

	SSoulSpaceInfo();
	SSoulSpaceInfo(UINT64 qwRoleID_, UINT64 dwSoulSpaceID_, UINT64 dwSoulSpaceLevel_);
};

typedef std::vector<SSoulSpaceInfo> TVecSoulSpaceInfo;

//EDataType:eTypeArena:玩家斗剑信息
struct SRoleArenaInfo
{
	UINT32 dwLastAwardTimer; //上次刷的那次奖励，记录系统计算时间
	NArenaGS::TVecArenaAward vecAwards; //奖励包状态
	UINT32 dwCDTime; //战斗冷却到期时间戳
	UINT32 dwLadderCDTime; //天梯战斗冷却到期时间戳
	NArenaGS::TVecFlushFither vecFlushFigter; //最近刷的对手

	SRoleArenaInfo();
	SRoleArenaInfo(UINT32 dwLastAwardTimer_, const NArenaGS::TVecArenaAward& vecAwards_, UINT32 dwCDTime_, UINT32 dwLadderCDTime_, const NArenaGS::TVecFlushFither& vecFlushFigter_);
#ifdef __GNUG__
	SRoleArenaInfo(const SRoleArenaInfo& src) = default; //默认拷贝构造函数
	SRoleArenaInfo& operator=(const SRoleArenaInfo& rhs) = default; //默认赋值操作符
#endif
	SRoleArenaInfo(SRoleArenaInfo&& src); //转移构造函数
	SRoleArenaInfo& operator=(SRoleArenaInfo&& rhs); //转移赋值操作符
};

typedef std::vector<SRoleArenaInfo> TVecRoleArenaInfo;

//战报保存
struct SBattleRePort
{
	UINT64 qwRoleID; //玩家ID
	UINT64 qwBattleID; //战报Id
	UINT64 qwAttackID; //对方ID
	std::string strAttackID; //对方名字
	EBattleActionType eActionType; //玩家战斗方式
	EBattleReportType eType; //战报类型
	EBattleActionType eSuc; //胜利方
	UINT32 dwTime; //战报时间
	UINT32 dwParam1; //参数1
	UINT32 dwParam2; //参数2
	UINT32 dwParam3; //参数3
	UINT32 dwIndex; //类型流水

	SBattleRePort();
#ifdef __GNUG__
	SBattleRePort(const SBattleRePort& src) = default; //默认拷贝构造函数
	SBattleRePort& operator=(const SBattleRePort& rhs) = default; //默认赋值操作符
#endif
	SBattleRePort(SBattleRePort&& src); //转移构造函数
	SBattleRePort& operator=(SBattleRePort&& rhs); //转移赋值操作符
};

typedef std::vector<SBattleRePort> TVecBattleRePort;

//气泡信息
struct SDBBubbleInfo
{
	UINT64 qwRoleID; //角色ID
	UINT64 qwTransID; //唯一流水ID
	UINT16 wMsgID; //气泡ID
	UINT32 dwTime; //气泡时间
	TVecINT64 vecParam; //整型变量
	TVecString vecString; //字符串型变量

	SDBBubbleInfo();
	SDBBubbleInfo(UINT64 qwRoleID_, UINT64 qwTransID_, UINT16 wMsgID_, UINT32 dwTime_, const TVecINT64& vecParam_, 
		const TVecString& vecString_);
};

typedef std::vector<SDBBubbleInfo> TVecDBBubbleInfo;

//气泡信息
struct SBubbleInfo
{
	UINT16 wMsgID; //气泡ID
	UINT16 wMessageID; //消息ID
	UINT8 byIndex; //气泡位置
	UINT32 dwTime; //气泡时间
	TVecINT64 vecParam; //整型变量
	TVecString vecString; //字符串型变量

	SBubbleInfo();
	SBubbleInfo(UINT16 wMsgID_, UINT16 wMessageID_, UINT8 byIndex_, UINT32 dwTime_, const TVecINT64& vecParam_, 
		const TVecString& vecString_);
};

typedef std::vector<SBubbleInfo> TVecBubbleInfo;

//师门任务
struct SGroupTaskInfo
{
	UINT32 dwRepute; //声望
	UINT8 byReputeLevel; //声望等级
	UINT8 byBuyTimes; //购买的师门任务数
	UINT32 dwFlushTask1; //刷的任务
	NGroupTaskProt::EGroupTaskState eState1; //任务状态
	UINT32 dwFlushTask2; //刷的任务
	NGroupTaskProt::EGroupTaskState eState2; //任务状态
	UINT32 dwFlushTask3; //刷的任务
	NGroupTaskProt::EGroupTaskState eState3; //任务状态
	UINT32 dwFlushTask4; //刷的任务
	NGroupTaskProt::EGroupTaskState eState4; //任务状态
	UINT32 dwFlushTask5; //刷的任务
	NGroupTaskProt::EGroupTaskState eState5; //任务状态

	SGroupTaskInfo();
};

typedef std::vector<SGroupTaskInfo> TVecGroupTaskInfo;

//衙门任务
struct SYaMenTaskInfo
{
	UINT32 dwHoly; //圣义值
	UINT8 byHolyLevel; //圣义等级
	UINT8 byBuyTimes; //购买的衙门任务数
	UINT32 dwFlushTask1; //刷的任务
	NYaMenTaskProt::EYaMenTaskState eState1; //任务状态
	UINT32 dwFlushTask2; //刷的任务
	NYaMenTaskProt::EYaMenTaskState eState2; //任务状态
	UINT32 dwFlushTask3; //刷的任务
	NYaMenTaskProt::EYaMenTaskState eState3; //任务状态
	UINT32 dwFlushTask4; //刷的任务
	NYaMenTaskProt::EYaMenTaskState eState4; //任务状态
	UINT32 dwFlushTask5; //刷的任务
	NYaMenTaskProt::EYaMenTaskState eState5; //任务状态

	SYaMenTaskInfo();
};

typedef std::vector<SYaMenTaskInfo> TVecYaMenTaskInfo;

//活跃任务
struct SActivityTaskInfo
{
	UINT16 wId; //活跃触发点ID
	UINT8 byTimes; //完成次数
	UINT8 byIsSpecial; //是否特别任务

	SActivityTaskInfo();
	SActivityTaskInfo(UINT16 wId_, UINT8 byTimes_, UINT8 byIsSpecial_);
};

typedef std::vector<SActivityTaskInfo> TVecActivityTaskInfo;

//头衔
struct STitle
{
	UINT16 wId; //头衔ID
	UINT8 byEquipPos; //装备位,从1开始，0表示未装备
	UINT32 dwValidTime; //有效截止时间,0表示永久

	STitle();
	STitle(UINT16 wId_, UINT8 byEquipPos_, UINT32 dwValidTime_);
};

typedef std::vector<STitle> TVecTitle;

//暂存信息
struct SPendRes
{
	UINT8 byResType; //类型
	UINT32 dwValue; //数据
	UINT8 bySource; //暂存原因0,战斗，1副本
	UINT32 dwParam; //参数

	SPendRes();
	SPendRes(UINT8 byResType_, UINT32 dwValue_, UINT8 bySource_, UINT32 dwParam_);
};

typedef std::vector<SPendRes> TVecPendRes;

//事件信息
struct SEventInfo
{
	UINT64 qwRoleID; //角色ID
	UINT8 byActClassID; //活动类型ID
	UINT32 dwEventInstID; //事件实例ID
	UINT32 dwApplyID; //具体活动ID
	UINT16 wEventStatus; //事件状态
	UINT8 bySave; //是否存数据库
	UINT32 dwParam1; //统计参数1
	INT32 dwParam2; //统计参数2
	UINT32 dwStartTime; //开始时间
	UINT32 dwEndTime; //结束时间

	SEventInfo();
	SEventInfo(UINT64 qwRoleID_, UINT8 byActClassID_, UINT32 dwEventInstID_, UINT32 dwApplyID_, UINT16 wEventStatus_, 
		UINT8 bySave_, UINT32 dwParam1_, INT32 dwParam2_, UINT32 dwStartTime_, UINT32 dwEndTime_);
};

typedef std::vector<SEventInfo> TVecEventInfo;

//离线事件
struct SEventOffLine
{
	UINT8 byServerType; //服务器类型
	UINT32 dwEventType; //事件类型
	UINT32 dwTime; //发生时间
	std::string strParam1; //TVecUINT32
	std::string strParam2; //字符参数

	SEventOffLine();
	SEventOffLine(UINT8 byServerType_, UINT32 dwEventType_, UINT32 dwTime_, const std::string& strParam1_, const std::string& strParam2_);
#ifdef __GNUG__
	SEventOffLine(const SEventOffLine& src) = default; //默认拷贝构造函数
	SEventOffLine& operator=(const SEventOffLine& rhs) = default; //默认赋值操作符
#endif
	SEventOffLine(SEventOffLine&& src); //转移构造函数
	SEventOffLine& operator=(SEventOffLine&& rhs); //转移赋值操作符
};

typedef std::vector<SEventOffLine> TVecEventOffLine;

//物品购买数量db信息
struct SBuyItemDBInfo
{
	UINT64 qwRoleID; //玩家ID
	UINT32 dwInstID; //实例ID
	UINT32 dwCount; //物品数量

	SBuyItemDBInfo();
	SBuyItemDBInfo(UINT64 qwRoleID_, UINT32 dwInstID_, UINT32 dwCount_);
};

typedef std::vector<SBuyItemDBInfo> TVecBuyItemDBInfo;

//7日目标活动信息
struct SDayTargetDBInfo
{
	UINT64 qwRoleID; //玩家ID
	UINT16 wTaskID; //任务ID
	UINT8 byStatus; //任务状态
	UINT32 dwProcess; //任务进度

	SDayTargetDBInfo();
	SDayTargetDBInfo(UINT64 qwRoleID_, UINT16 wTaskID_, UINT8 byStatus_, UINT32 dwProcess_);
};

typedef std::vector<SDayTargetDBInfo> TVecDayTargetDBInfo;

//破阵信息
struct SBattleArrayDBInfo
{
	UINT64 qwRoleID; //玩家ID
	UINT16 wBattleArrayID; //阵id
	UINT32 dwBattleArrayLevelID; //进度(阵图id)
	UINT8 byBattleArrayStatus; //状态

	SBattleArrayDBInfo();
	SBattleArrayDBInfo(UINT64 qwRoleID_, UINT16 wBattleArrayID_, UINT32 dwBattleArrayLevelID_, UINT8 byBattleArrayStatus_);
};

typedef std::vector<SBattleArrayDBInfo> TVecBattleArrayDBInfo;

//动态存储信息
struct SAutoStoreDBInfo
{
	UINT64 qwRoleID; //玩家ID
	UINT16 wType; //大类
	UINT32 dwClassID; //小类
	UINT32 dwValue; //数值

	SAutoStoreDBInfo();
	SAutoStoreDBInfo(UINT64 qwRoleID_, UINT16 wType_, UINT32 dwClassID_, UINT32 dwValue_);
};

typedef std::vector<SAutoStoreDBInfo> TVecAutoStoreDBInfo;

//新阵型信息
struct SFightFormationDBInfo
{
	UINT64 qwRoleID; //玩家ID
	UINT16 wBattleType; //战斗类型
	UINT16 wFormationID; //当前阵形ID
	std::string strBattlePosInfo; //阵型信息

	SFightFormationDBInfo();
	SFightFormationDBInfo(UINT64 qwRoleID_, UINT16 wBattleType_, UINT16 wFormationID_, const std::string& strBattlePosInfo_);
#ifdef __GNUG__
	SFightFormationDBInfo(const SFightFormationDBInfo& src) = default; //默认拷贝构造函数
	SFightFormationDBInfo& operator=(const SFightFormationDBInfo& rhs) = default; //默认赋值操作符
#endif
	SFightFormationDBInfo(SFightFormationDBInfo&& src); //转移构造函数
	SFightFormationDBInfo& operator=(SFightFormationDBInfo&& rhs); //转移赋值操作符
};

typedef std::vector<SFightFormationDBInfo> TVecFightFormationDBInfo;

//战斗散仙数据
struct SFightHeroDBInfo
{
	UINT64 qwRoleID; //玩家ID
	UINT16 wBattleType; //战斗类型
	UINT64 qwInstID; //散仙instID
	UINT32 dwHP; //当前生命值
	UINT32 dwMaxHP; //最大生命值（可能用到）
	UINT32 dwAura; //灵气值
	UINT32 dwMaxAura; //灵气值

	SFightHeroDBInfo();
	SFightHeroDBInfo(UINT64 qwRoleID_, UINT16 wBattleType_, UINT64 qwInstID_, UINT32 dwHP_, UINT32 dwMaxHP_, 
		UINT32 dwAura_, UINT32 dwMaxAura_);
};

typedef std::vector<SFightHeroDBInfo> TVecFightHeroDBInfo;

//玩家整体数据
struct RoleDataInfo
{
	UINT64 qwRoleId; //玩家RoleId
	RoleBaseInfo stBaseInfo; //玩家基本数据成员
	NFighterProt::TVecFighterDBInfo vecFighterInfo; //将信息
	NFighterProt::TVecSkillDBInfo vecSkillInfo; //将技能信息
	NFighterProt::TVecPassiveSkillDBInfo vecPassiveSkillInfo; //将技能信息
	NFighterProt::TVecFighterCombination vecFighterCombination; //玩家的散仙组合信息
	NItemProt::TVecItem vecRoleItemInfo; //玩家物品成员
	NFriendProt::TVecFriendDBInfo vecFriendsInfo; //好友信息
	TVecRoleDgnInfo vecRoleDgnInfo; //玩家副本信息
	TVecRoleTaskInfo vecRoleTaskInfo; //玩家任务信息
	TVecVarsDBInfo vecGameVars; //玩家身上Game上的变量任务信息
	TVecRoleSlotsInfo vecRoleSlotsInfo; //玩家身上的槽的信息
	TVecFormationInfo vecFormationInfo; //玩家的阵形信息
	TVecPetDataInfo vecPetDataInfo; //玩家的阵灵信息
	SRolePetInfo oRolePetInfo; //玩家的阵形全局信息
	TVecBeastSoulInfo vecBeastSoulInfo; //玩家的兽魂信息
	NTripodProt::TVecFireInfo vecFireInfo; //玩家九疑鼎的火种信息
	TVecRoleArenaInfo vecArenaInfo; //玩家斗剑信息
	NProtoCommon::TVecDBBuffInfo vecDBBuffInfo; //玩家Buff信息
	TVecSoulSpaceInfo vecSoulSpaceInfo; //玩家魄空间信息
	TVecDBBubbleInfo vecBubbleInfo; //玩家气泡信息
	NHorse::TVecHorseDB vecHorseDB; //玩家魄坐骑信息
	SGroupTaskInfo sGroupInfo; //师门任务信息
	SYaMenTaskInfo sYaMenInfo; //衙门任务信息
	TVecActivityTaskInfo vecActivityTask; //活跃度任务信息
	TVecTitle vecTitle; //称号信息
	NAchievementProt::TVecAchievementInfo vecAchievementInfo; //成就信息
	NCollectionProt::TVecCollectionInfo vecCollectionInfo; //收藏信息
	NDemonTower::TVecRoleAttaked vecRoleAttaked; //玩家被攻击信息列表
	NExchangeShopProt::TVecExchangeInfo vecExchangeInfo; //玩家兑换信息列表
	NDungeonProt::TVecSweepInfo vecSweepInfo; //玩家兑换信息列表
	TVecPendRes vecPendRes; //玩家暂存资源列表
	NFighterProt::TVecXinFaDBInfo vecXinFaDBInfo; //玩家心法信息
	NLevelPrize::TVecPrize2DB vecLevelPrize; //玩家条件奖励信息
	NProtoCommon::TVecPlatformParam vecPlatformParam; //玩家平台信息
	TVecEventInfo vecEventInfo; //事件信息
	TVecEventOffLine vecEventOffLine; //离线事件
	TVecBuyItemDBInfo vecBuyItemDBInfo; //商品购买数量
	TVecDayTargetDBInfo vecDayTargetDBInfo; //7日目标活动信息
	TVecBattleArrayDBInfo vecBattleArrayDBInfo; //破阵信息
	TVecAutoStoreDBInfo vecAutoStoreDBInfo; //动态存储信息
	NTreasureHuntProt::TVecTHDBInfo vecTHDBInfo; //玩家寻宝信息
	NBeauty::TVecBeauty vecBeauty; //美女信息
	TVecFightFormationDBInfo vecFightFormationDBInfo; //新阵型信息
	TVecFightHeroDBInfo vecFightHeroDBInfo; //战斗散仙数据
	NShipProt::PlayerSelfShipData sShipData; //自己运船信息
	NShipProt::TVecShipReport vecShipReport; //战报信息
	NGuardEMeiProt::TVecGEMDBInfo vecGEMDBInfo; //玩家守卫峨眉信息
	NShengLingProt::TVecShengLingInfo2DB vecShengLing; //玩家圣陵信息
	NShengLingProt::TVecShengLingPrize2DB vecShengLingPrize; //玩家圣陵奖励

	RoleDataInfo();
#ifdef __GNUG__
	RoleDataInfo(const RoleDataInfo& src) = default; //默认拷贝构造函数
	RoleDataInfo& operator=(const RoleDataInfo& rhs) = default; //默认赋值操作符
#endif
	RoleDataInfo(RoleDataInfo&& src); //转移构造函数
	RoleDataInfo& operator=(RoleDataInfo&& rhs); //转移赋值操作符
};

typedef std::vector<RoleDataInfo> TVecRoleDataInfo;

//DB存储玩家充值仙石的结构体
struct SRecharge
{
	std::string strNo; //充值流水号
	UINT64 qwRoleID; //用户ID
	UINT16 wGoldID; //仙石包ID(41[10仙石],42[100仙石],43[300仙石],44[500仙石],45[1000仙石],46[3000仙石])
	UINT32 dwCount; //充值的仙石包数量
	UINT32 dwGold; //充值的仙石总数
	UINT8 byStatus; //仙石是否到账(0-准备/不成功 1-成功,2-补单成功)
	UINT32 dwHappenedTime; //充值时间

	SRecharge();
	SRecharge(const std::string& strNo_, UINT64 qwRoleID_, UINT16 wGoldID_, UINT32 dwCount_, UINT32 dwGold_, 
		UINT8 byStatus_, UINT32 dwHappenedTime_);
#ifdef __GNUG__
	SRecharge(const SRecharge& src) = default; //默认拷贝构造函数
	SRecharge& operator=(const SRecharge& rhs) = default; //默认赋值操作符
#endif
	SRecharge(SRecharge&& src); //转移构造函数
	SRecharge& operator=(SRecharge&& rhs); //转移赋值操作符
};

typedef std::vector<SRecharge> TVecRecharge;

//DB存储玩家未创角预先充值仙石的结构体
struct SPrepaid
{
	UINT64 qwRoleID; //用户ID
	UINT32 dwGold; //预先充值的仙石总数量

	SPrepaid();
	SPrepaid(UINT64 qwRoleID_, UINT32 dwGold_);
};

typedef std::vector<SPrepaid> TVecPrepaid;

/////////////////////以下为序列化函数/////////////////////
CInArchive& operator>>(CInArchive&, RoleBaseInfo&);
COutArchive& operator<<(COutArchive&, const RoleBaseInfo&);

CInArchive& operator>>(CInArchive&, RoleDgnInfo&);
COutArchive& operator<<(COutArchive&, const RoleDgnInfo&);

CInArchive& operator>>(CInArchive&, RoleTaskInfo&);
COutArchive& operator<<(COutArchive&, const RoleTaskInfo&);

CInArchive& operator>>(CInArchive&, SVarsDBInfo&);
COutArchive& operator<<(COutArchive&, const SVarsDBInfo&);

CInArchive& operator>>(CInArchive&, SGameVarsDBInfo&);
COutArchive& operator<<(COutArchive&, const SGameVarsDBInfo&);

CInArchive& operator>>(CInArchive&, SRoleSlotsInfo&);
COutArchive& operator<<(COutArchive&, const SRoleSlotsInfo&);

CInArchive& operator>>(CInArchive&, SFormationInfo&);
COutArchive& operator<<(COutArchive&, const SFormationInfo&);

CInArchive& operator>>(CInArchive&, SPetDataInfo&);
COutArchive& operator<<(COutArchive&, const SPetDataInfo&);

CInArchive& operator>>(CInArchive&, SRolePetInfo&);
COutArchive& operator<<(COutArchive&, const SRolePetInfo&);

CInArchive& operator>>(CInArchive&, SBeastSoulInfo&);
COutArchive& operator<<(COutArchive&, const SBeastSoulInfo&);

CInArchive& operator>>(CInArchive&, SSoulSpaceInfo&);
COutArchive& operator<<(COutArchive&, const SSoulSpaceInfo&);

CInArchive& operator>>(CInArchive&, SRoleArenaInfo&);
COutArchive& operator<<(COutArchive&, const SRoleArenaInfo&);

CInArchive& operator>>(CInArchive&, SBattleRePort&);
COutArchive& operator<<(COutArchive&, const SBattleRePort&);

CInArchive& operator>>(CInArchive&, SDBBubbleInfo&);
COutArchive& operator<<(COutArchive&, const SDBBubbleInfo&);

CInArchive& operator>>(CInArchive&, SBubbleInfo&);
COutArchive& operator<<(COutArchive&, const SBubbleInfo&);

CInArchive& operator>>(CInArchive&, SGroupTaskInfo&);
COutArchive& operator<<(COutArchive&, const SGroupTaskInfo&);

CInArchive& operator>>(CInArchive&, SYaMenTaskInfo&);
COutArchive& operator<<(COutArchive&, const SYaMenTaskInfo&);

CInArchive& operator>>(CInArchive&, SActivityTaskInfo&);
COutArchive& operator<<(COutArchive&, const SActivityTaskInfo&);

CInArchive& operator>>(CInArchive&, STitle&);
COutArchive& operator<<(COutArchive&, const STitle&);

CInArchive& operator>>(CInArchive&, SPendRes&);
COutArchive& operator<<(COutArchive&, const SPendRes&);

CInArchive& operator>>(CInArchive&, SEventInfo&);
COutArchive& operator<<(COutArchive&, const SEventInfo&);

CInArchive& operator>>(CInArchive&, SEventOffLine&);
COutArchive& operator<<(COutArchive&, const SEventOffLine&);

CInArchive& operator>>(CInArchive&, SBuyItemDBInfo&);
COutArchive& operator<<(COutArchive&, const SBuyItemDBInfo&);

CInArchive& operator>>(CInArchive&, SDayTargetDBInfo&);
COutArchive& operator<<(COutArchive&, const SDayTargetDBInfo&);

CInArchive& operator>>(CInArchive&, SBattleArrayDBInfo&);
COutArchive& operator<<(COutArchive&, const SBattleArrayDBInfo&);

CInArchive& operator>>(CInArchive&, SAutoStoreDBInfo&);
COutArchive& operator<<(COutArchive&, const SAutoStoreDBInfo&);

CInArchive& operator>>(CInArchive&, SFightFormationDBInfo&);
COutArchive& operator<<(COutArchive&, const SFightFormationDBInfo&);

CInArchive& operator>>(CInArchive&, SFightHeroDBInfo&);
COutArchive& operator<<(COutArchive&, const SFightHeroDBInfo&);

CInArchive& operator>>(CInArchive&, RoleDataInfo&);
COutArchive& operator<<(COutArchive&, const RoleDataInfo&);

CInArchive& operator>>(CInArchive&, SRecharge&);
COutArchive& operator<<(COutArchive&, const SRecharge&);

CInArchive& operator>>(CInArchive&, SPrepaid&);
COutArchive& operator<<(COutArchive&, const SPrepaid&);

#ifdef PROT_USE_XML
/////////////////////以下为XML转换函数/////////////////////
bool FromXML(TiXmlElement&, RoleBaseInfo&);
bool ToXML(const RoleBaseInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecRoleBaseInfo&);
bool VectorToXML(const TVecRoleBaseInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, RoleDgnInfo&);
bool ToXML(const RoleDgnInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecRoleDgnInfo&);
bool VectorToXML(const TVecRoleDgnInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, RoleTaskInfo&);
bool ToXML(const RoleTaskInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecRoleTaskInfo&);
bool VectorToXML(const TVecRoleTaskInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SVarsDBInfo&);
bool ToXML(const SVarsDBInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecVarsDBInfo&);
bool VectorToXML(const TVecVarsDBInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SGameVarsDBInfo&);
bool ToXML(const SGameVarsDBInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecGameVarsDBInfo&);
bool VectorToXML(const TVecGameVarsDBInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SRoleSlotsInfo&);
bool ToXML(const SRoleSlotsInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecRoleSlotsInfo&);
bool VectorToXML(const TVecRoleSlotsInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SFormationInfo&);
bool ToXML(const SFormationInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecFormationInfo&);
bool VectorToXML(const TVecFormationInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SPetDataInfo&);
bool ToXML(const SPetDataInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecPetDataInfo&);
bool VectorToXML(const TVecPetDataInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SRolePetInfo&);
bool ToXML(const SRolePetInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecRolePetInfo&);
bool VectorToXML(const TVecRolePetInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SBeastSoulInfo&);
bool ToXML(const SBeastSoulInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecBeastSoulInfo&);
bool VectorToXML(const TVecBeastSoulInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SSoulSpaceInfo&);
bool ToXML(const SSoulSpaceInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecSoulSpaceInfo&);
bool VectorToXML(const TVecSoulSpaceInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SRoleArenaInfo&);
bool ToXML(const SRoleArenaInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecRoleArenaInfo&);
bool VectorToXML(const TVecRoleArenaInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SBattleRePort&);
bool ToXML(const SBattleRePort&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecBattleRePort&);
bool VectorToXML(const TVecBattleRePort&, TiXmlElement&);

bool FromXML(TiXmlElement&, SDBBubbleInfo&);
bool ToXML(const SDBBubbleInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecDBBubbleInfo&);
bool VectorToXML(const TVecDBBubbleInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SBubbleInfo&);
bool ToXML(const SBubbleInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecBubbleInfo&);
bool VectorToXML(const TVecBubbleInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SGroupTaskInfo&);
bool ToXML(const SGroupTaskInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecGroupTaskInfo&);
bool VectorToXML(const TVecGroupTaskInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SYaMenTaskInfo&);
bool ToXML(const SYaMenTaskInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecYaMenTaskInfo&);
bool VectorToXML(const TVecYaMenTaskInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SActivityTaskInfo&);
bool ToXML(const SActivityTaskInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecActivityTaskInfo&);
bool VectorToXML(const TVecActivityTaskInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, STitle&);
bool ToXML(const STitle&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecTitle&);
bool VectorToXML(const TVecTitle&, TiXmlElement&);

bool FromXML(TiXmlElement&, SPendRes&);
bool ToXML(const SPendRes&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecPendRes&);
bool VectorToXML(const TVecPendRes&, TiXmlElement&);

bool FromXML(TiXmlElement&, SEventInfo&);
bool ToXML(const SEventInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecEventInfo&);
bool VectorToXML(const TVecEventInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SEventOffLine&);
bool ToXML(const SEventOffLine&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecEventOffLine&);
bool VectorToXML(const TVecEventOffLine&, TiXmlElement&);

bool FromXML(TiXmlElement&, SBuyItemDBInfo&);
bool ToXML(const SBuyItemDBInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecBuyItemDBInfo&);
bool VectorToXML(const TVecBuyItemDBInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SDayTargetDBInfo&);
bool ToXML(const SDayTargetDBInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecDayTargetDBInfo&);
bool VectorToXML(const TVecDayTargetDBInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SBattleArrayDBInfo&);
bool ToXML(const SBattleArrayDBInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecBattleArrayDBInfo&);
bool VectorToXML(const TVecBattleArrayDBInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SAutoStoreDBInfo&);
bool ToXML(const SAutoStoreDBInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecAutoStoreDBInfo&);
bool VectorToXML(const TVecAutoStoreDBInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SFightFormationDBInfo&);
bool ToXML(const SFightFormationDBInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecFightFormationDBInfo&);
bool VectorToXML(const TVecFightFormationDBInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SFightHeroDBInfo&);
bool ToXML(const SFightHeroDBInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecFightHeroDBInfo&);
bool VectorToXML(const TVecFightHeroDBInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, RoleDataInfo&);
bool ToXML(const RoleDataInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecRoleDataInfo&);
bool VectorToXML(const TVecRoleDataInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SRecharge&);
bool ToXML(const SRecharge&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecRecharge&);
bool VectorToXML(const TVecRecharge&, TiXmlElement&);

bool FromXML(TiXmlElement&, SPrepaid&);
bool ToXML(const SPrepaid&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecPrepaid&);
bool VectorToXML(const TVecPrepaid&, TiXmlElement&);
#endif //PROT_USE_XML

} //namespace NRoleInfoDefine
