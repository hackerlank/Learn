/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    GuildProt.h
//  Purpose:      帮派相关协议
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
#include "ProtoCommon.h"

namespace NGuildProt
{

/////////////////////以下为类型定义/////////////////////
//帮派数据类型
enum EGuildDataType
{
	eGDTBaseInfo, //帮派基本数据
	eGDTUser, //帮派成员信息
	eGDTApplyInfo, //帮派申请列表信息
	eGDTAuthority, //帮派职位可选权限
	eGDTBuilding, //帮派建筑
	eGDTStatue, //帮派神像
	eGDTLog, //帮派日志
	eGDTLSSBLog, //帮派灵山商店购买日志
	eGDTMax, //最大值
	eGDTTech //帮派科技
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EGuildDataType);
bool EnumStrToVal(const char*, EGuildDataType&);
#endif //PROT_USE_XML
const char* GetDescription(EGuildDataType);

//公共帮派数据类型
enum EGuildPubDataType
{
	eGPDTListInfo, //帮派列表信息
	eGPDTBattleInfo, //帮派战相关数据
	eGPDTMax //帮派信息最大值
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EGuildPubDataType);
bool EnumStrToVal(const char*, EGuildPubDataType&);
#endif //PROT_USE_XML
const char* GetDescription(EGuildPubDataType);

//帮派操作返回结果
enum EGuildResult
{
	eGuildSuccess = 0, //操作成功
	eGuildFailed, //操作失败
	eGuildNotExisted, //不存在帮派
	eGuildExisted, //存在帮派
	eGuildLoading, //加载中
	eGuildTryAgain, //没加载到（已经开始加载了）稍等一会再试
	eGuildLackOfMoney //帮贡不足
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EGuildResult);
bool EnumStrToVal(const char*, EGuildResult&);
#endif //PROT_USE_XML

//获取帮派信息返回结果
enum EGuildInfoResult
{
	eGuildInofSuccess = 0, //操作成功
	eGuildInofFailed, //操作失败
	eGuildInofNoGuild //没有帮派
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EGuildInfoResult);
bool EnumStrToVal(const char*, EGuildInfoResult&);
#endif //PROT_USE_XML

//创建帮派返回结果
enum ECreateResult
{
	eGCreateSuccess = 0, //操作成功
	eGCreateFailed, //操作失败
	eGCreateInGuild, //已经在帮派中
	eGCreateLackOfGold, //银币不足
	eGCreateLackOfLevel, //等级不足
	eGCreateNameTooShort, //名称太短
	eGCreateNameTooLong, //名称太长
	eGCreateNameInvalid, //名称非法
	eGCreateNameExisted, //名称存在
	eGCreateExisted, //帮派存在
	eGCreateLackOfVIP //御剑等级不足
};

#ifdef PROT_USE_XML
const char* EnumValToStr(ECreateResult);
bool EnumStrToVal(const char*, ECreateResult&);
#endif //PROT_USE_XML

//退出帮派返回结果
enum EQuitResult
{
	eGQuitSuccess = 0, //操作成功
	eGQuitFailed, //操作失败
	eGQuitNoGuild, //不在帮派中
	eGQuitOwnerQuit, //帮主不能退出帮派
	eGQuitGuildBattle //帮派战期间无法执行此操作
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EQuitResult);
bool EnumStrToVal(const char*, EQuitResult&);
#endif //PROT_USE_XML

//申请帮派返回结果
enum EApplyResult
{
	eGApplySuccess = 0, //操作成功
	eGApplyFailed, //操作失败
	eGApplyGuildFull, //帮派成员已满
	eGApplyOtherGuild, //已加入其他帮派
	eGApplyInGuild, //已在帮派中
	eGApplyListFull, //申请列表已满
	eGApplyNoAuthority, //权限不足
	eGApplyNoGuild, //没有帮派
	eGApplyNoUser, //不存在的用户
	eGApplyNotOnline, //玩家不在线
	eGApplyAlreadyApplyed, //您已经发送过该申请
	eGApplyLevelLow, //等级过低
	eGApplyNoSelf, //不能邀请自己
	eGApplyGuildBattle //帮派战期间无法执行此操作
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EApplyResult);
bool EnumStrToVal(const char*, EApplyResult&);
#endif //PROT_USE_XML

//编辑公告返回结果
enum EEditInfoResult
{
	eGEditInfoSuccess = 0, //操作成功
	eGEditInfoFailed, //操作失败
	eGEditInfoNotInGuild, //不在帮派中
	eGEditInfoNoAuthority, //权限不足
	eGEditInfoTooLong //信息过长
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EEditInfoResult);
bool EnumStrToVal(const char*, EEditInfoResult&);
#endif //PROT_USE_XML

//设置权限返回结果
enum ESetAuthorityResult
{
	eGSetAuthoritySuccess = 0, //操作成功
	eGSetAuthorityFailed, //操作失败
	eGSetAuthorityNotInGuild, //不在帮派中
	eGSetAuthorityNoAuthority, //权限不足
	eGSetAuthorityTooHigh, //只能提升至比自己低的职位
	eGSetAuthorityNoSelfRank //不能改变自身权限
};

#ifdef PROT_USE_XML
const char* EnumValToStr(ESetAuthorityResult);
bool EnumStrToVal(const char*, ESetAuthorityResult&);
#endif //PROT_USE_XML

//帮派成员操作类型
enum EMemberOperateType
{
	eGMOpTypeNone = 0, //无效操作
	eGMOpTypeUp, //提升职位
	eGMOpTypeKick, //踢出帮派
	eGMOpTypeGiveOwner, //移交帮主
	eGMOpTypeDown, //降低职位
	eGMOpTypeFire, //免除职位
	eGMOpTypeMax //最大操作
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EMemberOperateType);
bool EnumStrToVal(const char*, EMemberOperateType&);
#endif //PROT_USE_XML

//帮派成员操作返回结果
enum EMemberOperateResult
{
	eGMOpResultSuccess = 0, //操作成功
	eGMOpResultFailed, //操作失败
	eGMOpResultSelf, //不能对自己操作
	eGMOpResultNotInGuild, //不在帮派中
	eGMOpResultNoAuthority, //权限不足
	eGMOpResultTooHigh, //只能提升至比自己低的职位
	eGMOpResultTooLow, //目标成员职位过低
	eGMOpResultTooMany, //目标职位成员数过多
	eGMOpResultHaveImpeach, //弹劾发起者无法踢出
	eGMOpResultGuildBattle //帮派战期间无法执行此操作
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EMemberOperateResult);
bool EnumStrToVal(const char*, EMemberOperateResult&);
#endif //PROT_USE_XML

//弹劾操作返回结果
enum EImpeachResult
{
	eGImpeachResultSuccess = 0, //操作成功
	eGImpeachResultFailed, //操作失败
	eGImpeachResultSelf, //不能对自己操作
	eGImpeachResultNotInGuild, //不在帮派中
	eGImpeachResultWrongGuild, //不是该帮派
	eGImpeachResultNoAuthority, //权限不足
	eGImpeachResultHasLaunched, //已经存在弹劾
	eGImpeachResultHasReplyed, //已经回应
	eGImpeachResultLackOfGold //仙石不足
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EImpeachResult);
bool EnumStrToVal(const char*, EImpeachResult&);
#endif //PROT_USE_XML

//帮派职位
enum EMemberRank
{
	eMemberNone = 0, //无效职位
	eMemberNormal, //成员
	eMemberElite, //精英
	eMemberElder, //长老
	eMemberViceOwner, //副帮主
	eMemberOwner, //帮主
	eMemberMax //最高职位
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EMemberRank);
bool EnumStrToVal(const char*, EMemberRank&);
#endif //PROT_USE_XML

//帮派建筑类型
enum EBuildingType
{
	eBuildingNone = 0, //无效建筑
	eBuildingOracle, //神谕塔
	eBuildingDepot, //仓库
	eBuildingSword, //剑阁
	eBuildingStore, //商店
	eBuildingBlood, //血池
	eBuildingMax //最高建筑
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EBuildingType);
bool EnumStrToVal(const char*, EBuildingType&);
#endif //PROT_USE_XML

//帮派建筑操作返回结果
enum EBuildingResult
{
	eGBuildingResultSuccess = 0, //操作成功
	eGBuildingResultFailed, //操作失败
	eGBuildingResultNoGuild, //不存在帮派
	eGBuildingResultLackofSilver, //银币不足
	eGBuildingResultLevelMax, //已经是最大等级
	eGBuildingResultNoAuthority, //权限不足
	eGBuildingResultGuildLevelTooLow, //帮派等级过低
	eGBuildingResultOracleLevelTooLow //神谕塔等级过低
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EBuildingResult);
bool EnumStrToVal(const char*, EBuildingResult&);
#endif //PROT_USE_XML

//帮派建筑类型
enum ETechType
{
	eTechNone = 0, //无效科技
	eTechAttack, //攻击之魂
	eTechPhyDef, //物防之魂
	eTechMgcDef, //魔防之魂
	eTechHP, //生命之魂
	eTechSpeed, //身法之魂
	eTechHit, //命中之魂
	eTechDodge, //闪避之魂
	eTechCritial, //暴击之魂
	eTechAntiCritial, //稳固之魂
	eTechPierce, //穿透之魂
	eTechCounter, //反击之魂
	eTechResist, //压制之魂
	eTechMax //最高科技
};

#ifdef PROT_USE_XML
const char* EnumValToStr(ETechType);
bool EnumStrToVal(const char*, ETechType&);
#endif //PROT_USE_XML

//帮派科技操作返回结果
enum ETechResult
{
	eGTResultSuccess = 0, //操作成功
	eGTResultFailed, //操作失败
	eGTResultNoGuild, //不存在帮派
	eGTResultLackofSilver, //帮贡不足
	eGTResultLevelMax, //已经是最大等级
	eGTResultNoAuthority, //权限不足
	eGTResultBuildingLevelTooLow, //帮派建筑等级过低
	eGTResultUserLevelTooLow //玩家等级过低
};

#ifdef PROT_USE_XML
const char* EnumValToStr(ETechResult);
bool EnumStrToVal(const char*, ETechResult&);
#endif //PROT_USE_XML

//帮派捐献操作返回结果
enum EDonateResult
{
	eGDResultSuccess = 0, //操作成功
	eGDResultFailed, //操作失败
	eGDResultNoGuild, //不存在帮派
	eGDResultLackofSilver, //银币不足
	eGDResultNoAuthority, //权限不足
	eGDResultFull, //每日捐献已满
	eGDResultDepotFull //仓库已满
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EDonateResult);
bool EnumStrToVal(const char*, EDonateResult&);
#endif //PROT_USE_XML

//帮派捐献操作返回结果
enum EWorshipResult
{
	eGWResultSuccess = 0, //操作成功
	eGWResultFailed, //操作失败
	eGWResultNoGuild, //不存在帮派
	eGWResultLackofSilver, //银币不足
	eGWResultNoAuthority, //权限不足
	eGWResultLevelTooLow //帮派等级过低
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EWorshipResult);
bool EnumStrToVal(const char*, EWorshipResult&);
#endif //PROT_USE_XML

//日志类型
enum ELogType
{
	eLogNone = 0, //无效日志类型
	eLogMember, //成员日志
	eLogDonate, //捐献日志
	eLogBuilding, //建筑日志
	eLogStatue, //神像日志
	eLogMax //日志类型最大值
};

#ifdef PROT_USE_XML
const char* EnumValToStr(ELogType);
bool EnumStrToVal(const char*, ELogType&);
#endif //PROT_USE_XML

//捐献类型
enum EWorshipType
{
	eWorshipNone = 0, //无效供奉类型
	eWorshipFlower, //鲜花供奉
	eWorshipRedFruit, //朱果供奉
	eWorshipPeach, //蟠桃供奉
	eWorshipMax //供奉类型最大值
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EWorshipType);
bool EnumStrToVal(const char*, EWorshipType&);
#endif //PROT_USE_XML

//帮派神像操作返回结果
enum EStatueResult
{
	eGSResultSuccess = 0, //操作成功
	eGSResultFailed, //操作失败
	eGSResultNoGuild, //不存在帮派
	eGSResultLackofSilver, //银币不足
	eGSResultLackofGold, //仙石不足
	eGSResultLevelMax, //已经是最大等级
	eGSResultNoAuthority, //权限不足
	eGSResultBuildingLevelTooLow, //帮派建筑等级过低
	eGSResultWorshiped, //本日已经供奉过
	eGSResultTooFast, //操作过快
	eGSResultNotToday //进入当日无法操作
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EStatueResult);
bool EnumStrToVal(const char*, EStatueResult&);
#endif //PROT_USE_XML

//羲和神车操作返回结果
enum EGuildXiheResult
{
	eXiheResultSuccess = 0, //操作成功
	eXiheResultFailed, //操作失败
	eXiheResultNoGuild, //不存在帮派
	eXiheResultUnfinish, //货物未装满
	eXiheResultFinish, //货物已装箱
	eXiheResultHasRequest, //货物已请求帮助
	eXiheResultNotRequest, //货物未请求帮助
	eXiheResultNotTruck, //不存在这个货物
	eXiheResultNotItem, //道具不足不能装货
	eXiheResultNotGold, //仙石不足不能装货
	eXiheResultNoSameGuild, //不是同一帮派
	eXiheResultForHelpNumMax, //此次任务请求帮助次数已达上限
	eXiheResultNotRequestLimit //已装货物未达到4个不能请求帮助
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EGuildXiheResult);
bool EnumStrToVal(const char*, EGuildXiheResult&);
#endif //PROT_USE_XML

//羲和神车任务阶段
enum EXiheStage
{
	eXiheStageShipGoods = 0, //装货阶段
	eXiheStageTaskCool = 1, //冷却阶段
	eXiheStageWaitAcess = 2 //等待玩家接取任务
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EXiheStage);
bool EnumStrToVal(const char*, EXiheStage&);
#endif //PROT_USE_XML

//羲和神车任务完成状态
enum EXiheTaskStatus
{
	eXiheTaskUnfinish = 0, //未完成装货也未请求帮助
	eXiheTaskRequest = 1, //未完成装货已请求帮助
	eXiheTaskFinishURe = 2, //未请求帮助但已完成装货
	eXiheTaskFinishRe = 3 //已请求帮助但已完成装货
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EXiheTaskStatus);
bool EnumStrToVal(const char*, EXiheTaskStatus&);
#endif //PROT_USE_XML

//帮派兑换错误码
enum EGuildExchangeRet
{
	eGuildExchange_Failed, //失败
	eGuildExchange_Sucess, //成功
	eGuildExchange_ErrorPack, //背包满无法添加物品
	eGuildExchange_MoneyLimit, //钱币不够
	eGuildExchange_CondLimitA, //商品剩余数量为0
	eGuildExchange_CondLimitB, //帮派成员每天购买次数达到上限
	eGuildExchange_CondLimitC, //帮派所有成员每天购买次数达到上限
	eGuildExchange_NoLingShan //要占领该据点才可兑换
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EGuildExchangeRet);
bool EnumStrToVal(const char*, EGuildExchangeRet&);
#endif //PROT_USE_XML

//结构体：SGuildInfoBase的继承体系类型
enum EType_SGuildInfoBase
{
	eType_SGuildInfoBase, //类型：SGuildInfoBase
	eType_SGuildBaseInfo, //类型：SGuildBaseInfo
	eType_SGuildUserInfo, //类型：SGuildUserInfo
	eType_SGuildApplyInfo, //类型：SGuildApplyInfo
	eType_SGuildBuildingInfo, //类型：SGuildBuildingInfo
	eType_SGuildAuthorityInfo, //类型：SGuildAuthorityInfo
	eType_SGuildTechInfo, //类型：SGuildTechInfo
	eType_SGuildLogInfo, //类型：SGuildLogInfo
	eType_SGuildStatueInfo //类型：SGuildStatueInfo
};

//结构体：SGetGuildInfoBase的继承体系类型
enum EType_SGetGuildInfoBase
{
	eType_SGetGuildInfoBase, //类型：SGetGuildInfoBase
	eType_SOtherGuildListInfo, //类型：SOtherGuildListInfo
	eType_SSelfGuildInfo //类型：SSelfGuildInfo
};

//帮派信息基本类
struct SGuildInfoBase
{
	UINT64 qwGuildID; //帮派唯一ID

	SGuildInfoBase();
	virtual ~SGuildInfoBase() { }
	DEF_NEW_DELETE(SGuildInfoBase); //使用对象池
	virtual EType_SGuildInfoBase GetClassType() const { return eType_SGuildInfoBase; }
};

typedef std::shared_ptr<SGuildInfoBase> SGuildInfoBasePtr;
typedef std::weak_ptr<SGuildInfoBase> SGuildInfoBaseWtr;
typedef std::vector<SGuildInfoBasePtr> TVecSGuildInfoBase;

//父类：SGuildInfoBase的辅助结构体
struct SGuildInfoBase_Wrapper
{
	SGuildInfoBasePtr ptr;
	SGuildInfoBase_Wrapper(const SGuildInfoBasePtr& ptr_ = NULL) : ptr(ptr_) { }
};

//帮派基本信息
struct SGuildBaseInfo : public SGuildInfoBase
{
	std::string strName; //帮派名称
	UINT64 qwOwnerID; //帮主角色ID
	std::string strOwnerName; //帮主名称
	std::string strInfo; //帮派公告
	UINT64 qwQQGroupID; //帮派Q群群号
	UINT16 wUserCount; //成员数量
	UINT16 wMaxUserCount; //最大成员数量
	UINT32 dwMoney; //帮派资金
	EMemberRank eSelfRank; //本人职位
	UINT32 dwContribution; //本人贡献值
	UINT32 dwRemainDonate; //剩余捐献额
	UINT16 wPlayerFighterID; //帮主ID
	UINT8 byQuality; //帮主品质
	UINT32 dwScore; //天元神兽积分
	UINT32 dwCount; //帮派所有成员兑换物品数量
	std::string strLingShan; //占领灵山

	SGuildBaseInfo();
#ifdef __GNUG__
	SGuildBaseInfo(const SGuildBaseInfo& src) = default; //默认拷贝构造函数
	SGuildBaseInfo& operator=(const SGuildBaseInfo& rhs) = default; //默认赋值操作符
#endif
	SGuildBaseInfo(SGuildBaseInfo&& src); //转移构造函数
	SGuildBaseInfo& operator=(SGuildBaseInfo&& rhs); //转移赋值操作符
	DEF_NEW_DELETE(SGuildBaseInfo); //使用对象池
	virtual EType_SGuildInfoBase GetClassType() const { return eType_SGuildBaseInfo; }
};

typedef std::shared_ptr<SGuildBaseInfo> SGuildBaseInfoPtr;
typedef std::weak_ptr<SGuildBaseInfo> SGuildBaseInfoWtr;
typedef std::vector<SGuildBaseInfoPtr> TVecSGuildBaseInfo;

//帮派成员信息
struct SGuildUserInfo : public SGuildInfoBase
{
	UINT64 qwRoleID; //玩家ID
	std::string strName; //玩家姓名
	UINT16 wLevel; //玩家等级
	UINT32 dwContribution; //贡献值
	UINT32 dwLastOnlineTime; //最后在线时间
	UINT32 dwJoinTime; //入帮时间
	EMemberRank eMemberRank; //帮派职位
	EMemberRank eMemberLastRank; //帮派上一次职位
	UINT32 dwAuthority; //帮派权限
	UINT8 byVIPLevel; //御剑等级
	NProtoCommon::TVecPlatformParam vecPlatforms; //平台信息

	SGuildUserInfo();
#ifdef __GNUG__
	SGuildUserInfo(const SGuildUserInfo& src) = default; //默认拷贝构造函数
	SGuildUserInfo& operator=(const SGuildUserInfo& rhs) = default; //默认赋值操作符
#endif
	SGuildUserInfo(SGuildUserInfo&& src); //转移构造函数
	SGuildUserInfo& operator=(SGuildUserInfo&& rhs); //转移赋值操作符
	DEF_NEW_DELETE(SGuildUserInfo); //使用对象池
	virtual EType_SGuildInfoBase GetClassType() const { return eType_SGuildUserInfo; }
};

typedef std::shared_ptr<SGuildUserInfo> SGuildUserInfoPtr;
typedef std::weak_ptr<SGuildUserInfo> SGuildUserInfoWtr;
typedef std::vector<SGuildUserInfoPtr> TVecGuildUserInfo;

//帮派申请列表信息
struct SGuildApplyInfo : public SGuildInfoBase
{
	UINT64 qwRoleID; //玩家ID
	std::string strName; //玩家姓名
	UINT16 wLevel; //玩家等级
	UINT32 dwBattlePoint; //玩家战斗力

	SGuildApplyInfo();
#ifdef __GNUG__
	SGuildApplyInfo(const SGuildApplyInfo& src) = default; //默认拷贝构造函数
	SGuildApplyInfo& operator=(const SGuildApplyInfo& rhs) = default; //默认赋值操作符
#endif
	SGuildApplyInfo(SGuildApplyInfo&& src); //转移构造函数
	SGuildApplyInfo& operator=(SGuildApplyInfo&& rhs); //转移赋值操作符
	DEF_NEW_DELETE(SGuildApplyInfo); //使用对象池
	virtual EType_SGuildInfoBase GetClassType() const { return eType_SGuildApplyInfo; }
};

typedef std::shared_ptr<SGuildApplyInfo> SGuildApplyInfoPtr;
typedef std::weak_ptr<SGuildApplyInfo> SGuildApplyInfoWtr;
typedef std::vector<SGuildApplyInfoPtr> TVecGuildApplyInfo;

//帮派建筑信息
struct SGuildBuildingInfo : public SGuildInfoBase
{
	EBuildingType eBuildingType; //帮派建筑类型
	UINT16 wLevel; //帮派建筑等级

	SGuildBuildingInfo();
	DEF_NEW_DELETE(SGuildBuildingInfo); //使用对象池
	virtual EType_SGuildInfoBase GetClassType() const { return eType_SGuildBuildingInfo; }
};

typedef std::shared_ptr<SGuildBuildingInfo> SGuildBuildingInfoPtr;
typedef std::weak_ptr<SGuildBuildingInfo> SGuildBuildingInfoWtr;
typedef std::vector<SGuildBuildingInfoPtr> TVecGuildBuildingInfo;

//帮派可选权限信息
struct SGuildAuthorityInfo : public SGuildInfoBase
{
	EMemberRank eMemberRank; //帮派职位
	UINT32 dwAuthority; //可选权限 0x01:指挥帮战 0x02:升级建筑 0x04:开启血池 0x08:指挥末日之战 0x10:创建遗迹攻击小队

	SGuildAuthorityInfo();
	DEF_NEW_DELETE(SGuildAuthorityInfo); //使用对象池
	virtual EType_SGuildInfoBase GetClassType() const { return eType_SGuildAuthorityInfo; }
};

typedef std::shared_ptr<SGuildAuthorityInfo> SGuildAuthorityInfoPtr;
typedef std::weak_ptr<SGuildAuthorityInfo> SGuildAuthorityInfoWtr;
typedef std::vector<SGuildAuthorityInfoPtr> TVecGuildAuthorityInfo;

//帮派科技
struct SGuildTechInfo : public SGuildInfoBase
{
	ETechType eType; //科技类型
	UINT16 wLevel; //科技等级

	SGuildTechInfo();
	DEF_NEW_DELETE(SGuildTechInfo); //使用对象池
	virtual EType_SGuildInfoBase GetClassType() const { return eType_SGuildTechInfo; }
};

typedef std::shared_ptr<SGuildTechInfo> SGuildTechInfoPtr;
typedef std::weak_ptr<SGuildTechInfo> SGuildTechInfoWtr;
typedef std::vector<SGuildTechInfoPtr> TVecGuildTechInfo;

//日志
struct SGuildLogInfo : public SGuildInfoBase
{
	UINT64 qwInstID; //唯一流水ID
	ELogType eType; //日志类型
	UINT16 wMsgID; //消息ID
	TVecINT64 vecParam; //整型变量
	TVecString vecString; //字符串型变量
	UINT32 dwTime; //日志时间

	SGuildLogInfo();
	DEF_NEW_DELETE(SGuildLogInfo); //使用对象池
	virtual EType_SGuildInfoBase GetClassType() const { return eType_SGuildLogInfo; }
};

typedef std::shared_ptr<SGuildLogInfo> SGuildLogInfoPtr;
typedef std::weak_ptr<SGuildLogInfo> SGuildLogInfoWtr;
typedef std::vector<SGuildLogInfoPtr> TVecGuildLogInfo;

//帮派神像
struct SGuildStatueInfo : public SGuildInfoBase
{
	UINT16 wLevel; //神像等级
	UINT32 dwExp; //神像经验值
	TVecGuildLogInfo vecLogInfo; //神像日志
	UINT8 byWorshipCount; //供奉人数
	UINT8 byWorshipBit; //当前供奉（第N位表示第N种供奉类型）
	UINT32 dwTime; //操作时间

	SGuildStatueInfo();
#ifdef __GNUG__
	SGuildStatueInfo(const SGuildStatueInfo& src) = default; //默认拷贝构造函数
	SGuildStatueInfo& operator=(const SGuildStatueInfo& rhs) = default; //默认赋值操作符
#endif
	SGuildStatueInfo(SGuildStatueInfo&& src); //转移构造函数
	SGuildStatueInfo& operator=(SGuildStatueInfo&& rhs); //转移赋值操作符
	DEF_NEW_DELETE(SGuildStatueInfo); //使用对象池
	virtual EType_SGuildInfoBase GetClassType() const { return eType_SGuildStatueInfo; }
};

typedef std::shared_ptr<SGuildStatueInfo> SGuildStatueInfoPtr;
typedef std::weak_ptr<SGuildStatueInfo> SGuildStatueInfoWtr;
typedef std::vector<SGuildStatueInfoPtr> TVecGuildStatueInfo;

//数据库加载用帮派玩家数据
struct SDBGuildUserInfo
{
	SGuildUserInfo sBaseInfo; //帮派用户基本信息
	TVecGuildTechInfo vecTechInfo; //帮派科技信息
	UINT32 dwBattleScore; //帮派战积分
	UINT16 wPlayerFighterID; //主将ID
	UINT8 byQuality; //主将品质

	SDBGuildUserInfo();
	SDBGuildUserInfo(const SGuildUserInfo& sBaseInfo_, const TVecGuildTechInfo& vecTechInfo_, UINT32 dwBattleScore_, UINT16 wPlayerFighterID_, UINT8 byQuality_);
#ifdef __GNUG__
	SDBGuildUserInfo(const SDBGuildUserInfo& src) = default; //默认拷贝构造函数
	SDBGuildUserInfo& operator=(const SDBGuildUserInfo& rhs) = default; //默认赋值操作符
#endif
	SDBGuildUserInfo(SDBGuildUserInfo&& src); //转移构造函数
	SDBGuildUserInfo& operator=(SDBGuildUserInfo&& rhs); //转移赋值操作符
};

typedef std::vector<SDBGuildUserInfo> TVecDBGuildUserInfo;

//帮派完整信息
struct SGuildAllInfo
{
	SGuildBaseInfo sBaseInfo; //基本信息
	TVecGuildUserInfo vecMemberInfo; //帮派成员信息
	TVecGuildApplyInfo vecApplyInfo; //帮派申请信息
	TVecGuildBuildingInfo vecBuildingInfo; //帮派建筑信息
	TVecGuildAuthorityInfo vecAuthority; //帮派可选权限信息
	TVecGuildTechInfo vecTech; //帮派科技信息
	SGuildStatueInfo sStatueInfo; //帮派神像信息
	TVecGuildLogInfo vecLogInfo; //帮派日志信息

	SGuildAllInfo();
	SGuildAllInfo(const SGuildBaseInfo& sBaseInfo_, const TVecGuildUserInfo& vecMemberInfo_, const TVecGuildApplyInfo& vecApplyInfo_, const TVecGuildBuildingInfo& vecBuildingInfo_, const TVecGuildAuthorityInfo& vecAuthority_, 
		const TVecGuildTechInfo& vecTech_, const SGuildStatueInfo& sStatueInfo_, const TVecGuildLogInfo& vecLogInfo_);
#ifdef __GNUG__
	SGuildAllInfo(const SGuildAllInfo& src) = default; //默认拷贝构造函数
	SGuildAllInfo& operator=(const SGuildAllInfo& rhs) = default; //默认赋值操作符
#endif
	SGuildAllInfo(SGuildAllInfo&& src); //转移构造函数
	SGuildAllInfo& operator=(SGuildAllInfo&& rhs); //转移赋值操作符
};

typedef std::vector<SGuildAllInfo> TVecGuildAllInfo;

//帮派完整信息(数据库传来的内部协议)
struct SDBGuildAllInfo
{
	SGuildBaseInfo sBaseInfo; //基本信息
	TVecDBGuildUserInfo vecMemberInfo; //帮派成员信息
	TVecGuildApplyInfo vecApplyInfo; //帮派申请信息
	TVecGuildBuildingInfo vecBuildingInfo; //帮派建筑信息
	TVecGuildAuthorityInfo vecAuthority; //帮派可选权限信息
	SGuildStatueInfo sStatueInfo; //帮派神像信息
	TVecGuildLogInfo vecLogInfo; //帮派日志信息
	TVecGuildLogInfo vecLingShanShopBuyLogInfo; //帮派灵山商店购买日志信息

	SDBGuildAllInfo();
	SDBGuildAllInfo(const SGuildBaseInfo& sBaseInfo_, const TVecDBGuildUserInfo& vecMemberInfo_, const TVecGuildApplyInfo& vecApplyInfo_, const TVecGuildBuildingInfo& vecBuildingInfo_, const TVecGuildAuthorityInfo& vecAuthority_, 
		const SGuildStatueInfo& sStatueInfo_, const TVecGuildLogInfo& vecLogInfo_, const TVecGuildLogInfo& vecLingShanShopBuyLogInfo_);
#ifdef __GNUG__
	SDBGuildAllInfo(const SDBGuildAllInfo& src) = default; //默认拷贝构造函数
	SDBGuildAllInfo& operator=(const SDBGuildAllInfo& rhs) = default; //默认赋值操作符
#endif
	SDBGuildAllInfo(SDBGuildAllInfo&& src); //转移构造函数
	SDBGuildAllInfo& operator=(SDBGuildAllInfo&& rhs); //转移赋值操作符
};

typedef std::vector<SDBGuildAllInfo> TVecDBGuildAllInfo;

//帮派列表信息
struct SGuildListInfo
{
	UINT64 qwGuildID; //帮派唯一ID
	std::string strName; //帮派名称
	std::string strInfo; //帮派公告
	UINT64 qwOwnerID; //帮主ID
	std::string strOwnerName; //帮主名称
	UINT8 byLevel; //帮派等级
	UINT16 wUserCount; //成员数量
	UINT16 wMaxUserCount; //最大成员数量

	SGuildListInfo();
	SGuildListInfo(UINT64 qwGuildID_, const std::string& strName_, const std::string& strInfo_, UINT64 qwOwnerID_, const std::string& strOwnerName_, 
		UINT8 byLevel_, UINT16 wUserCount_, UINT16 wMaxUserCount_);
#ifdef __GNUG__
	SGuildListInfo(const SGuildListInfo& src) = default; //默认拷贝构造函数
	SGuildListInfo& operator=(const SGuildListInfo& rhs) = default; //默认赋值操作符
#endif
	SGuildListInfo(SGuildListInfo&& src); //转移构造函数
	SGuildListInfo& operator=(SGuildListInfo&& rhs); //转移赋值操作符
};

typedef std::vector<SGuildListInfo> TVecGuildListInfo;

//数据库加载用帮派玩家数据
struct SDBGuildBattleInfo
{
	UINT64 qwGuildID; //帮派唯一ID
	UINT32 dwScore; //帮派战积分

	SDBGuildBattleInfo();
	SDBGuildBattleInfo(UINT64 qwGuildID_, UINT32 dwScore_);
};

typedef std::vector<SDBGuildBattleInfo> TVecDBGuildBattleInfo;

//
struct SGetGuildInfoBase
{
	SGetGuildInfoBase();
	virtual ~SGetGuildInfoBase() { }
	DEF_NEW_DELETE(SGetGuildInfoBase); //使用对象池
	virtual EType_SGetGuildInfoBase GetClassType() const { return eType_SGetGuildInfoBase; }
};

typedef std::shared_ptr<SGetGuildInfoBase> SGetGuildInfoBasePtr;
typedef std::weak_ptr<SGetGuildInfoBase> SGetGuildInfoBaseWtr;

//父类：SGetGuildInfoBase的辅助结构体
struct SGetGuildInfoBase_Wrapper
{
	SGetGuildInfoBasePtr ptr;
	SGetGuildInfoBase_Wrapper(const SGetGuildInfoBasePtr& ptr_ = NULL) : ptr(ptr_) { }
};

//没有帮派返回的其他帮派列表信息
struct SOtherGuildListInfo : public SGetGuildInfoBase
{
	UINT32 dwMaxGuildCount; //最大帮派
	UINT32 dwCurGuildCount; //当前帮派索引
	TVecGuildListInfo vecGuildListInfo; //帮派列表信息
	TVecUINT64 vecApplyGuildID; //已申请列表帮派ID

	SOtherGuildListInfo();
#ifdef __GNUG__
	SOtherGuildListInfo(const SOtherGuildListInfo& src) = default; //默认拷贝构造函数
	SOtherGuildListInfo& operator=(const SOtherGuildListInfo& rhs) = default; //默认赋值操作符
#endif
	SOtherGuildListInfo(SOtherGuildListInfo&& src); //转移构造函数
	SOtherGuildListInfo& operator=(SOtherGuildListInfo&& rhs); //转移赋值操作符
	DEF_NEW_DELETE(SOtherGuildListInfo); //使用对象池
	virtual EType_SGetGuildInfoBase GetClassType() const { return eType_SOtherGuildListInfo; }
};

typedef std::shared_ptr<SOtherGuildListInfo> SOtherGuildListInfoPtr;
typedef std::weak_ptr<SOtherGuildListInfo> SOtherGuildListInfoWtr;
typedef std::vector<SOtherGuildListInfoPtr> TVecOtherGuildListInfo;

//存在帮派的本帮信息
struct SSelfGuildInfo : public SGetGuildInfoBase
{
	SGuildAllInfo sAllInfo; //帮派完整信息

	SSelfGuildInfo();
#ifdef __GNUG__
	SSelfGuildInfo(const SSelfGuildInfo& src) = default; //默认拷贝构造函数
	SSelfGuildInfo& operator=(const SSelfGuildInfo& rhs) = default; //默认赋值操作符
#endif
	SSelfGuildInfo(SSelfGuildInfo&& src); //转移构造函数
	SSelfGuildInfo& operator=(SSelfGuildInfo&& rhs); //转移赋值操作符
	DEF_NEW_DELETE(SSelfGuildInfo); //使用对象池
	virtual EType_SGetGuildInfoBase GetClassType() const { return eType_SSelfGuildInfo; }
};

typedef std::shared_ptr<SSelfGuildInfo> SSelfGuildInfoPtr;
typedef std::weak_ptr<SSelfGuildInfo> SSelfGuildInfoWtr;

//帮派公共数据（用于服务端读取加载常驻内存的基础数据）
struct SPubGuildAllInfo
{
	SGuildListInfo sGuildListInfo; //帮派列表数据
	SDBGuildBattleInfo sGuildBattleInfo; //帮派战数据

	SPubGuildAllInfo();
	SPubGuildAllInfo(const SGuildListInfo& sGuildListInfo_, const SDBGuildBattleInfo& sGuildBattleInfo_);
};

typedef std::vector<SPubGuildAllInfo> TVecPubGuildAllInfo;

//羲和神车的货号信息
struct STruckInfo
{
	UINT8 byTruckID; //货号id
	UINT8 byStatus; //EXiheTaskStatus货号状态(0未完成装货 1已请求帮助 2已完成装货)
	UINT8 byPos; //货物顺序索引(0~7)
	std::string strName; //status为3时,完成装货的玩家名字(注:自己完成为空,不存储)
	UINT8 byColor; //帮助者玩家颜色

	STruckInfo();
	STruckInfo(UINT8 byTruckID_, UINT8 byStatus_, UINT8 byPos_, const std::string& strName_, UINT8 byColor_);
#ifdef __GNUG__
	STruckInfo(const STruckInfo& src) = default; //默认拷贝构造函数
	STruckInfo& operator=(const STruckInfo& rhs) = default; //默认赋值操作符
#endif
	STruckInfo(STruckInfo&& src); //转移构造函数
	STruckInfo& operator=(STruckInfo&& rhs); //转移赋值操作符
};

typedef std::vector<STruckInfo> TVecTruckInfo;

//玩家羲和神车信息
struct SGuildXihe
{
	UINT64 qwRoleID; //玩家ID
	TVecTruckInfo vecTruckInfo; //货号信息
	UINT8 byStage; //EXiheStage当前阶段(0装货阶段 1任务冷却阶段 2等待玩家接取任务)
	UINT32 dwEndTime; //当前阶段的结束时间
	UINT8 byRequest; //已请求帮助的次数

	SGuildXihe();
	SGuildXihe(UINT64 qwRoleID_, const TVecTruckInfo& vecTruckInfo_, UINT8 byStage_, UINT32 dwEndTime_, UINT8 byRequest_);
#ifdef __GNUG__
	SGuildXihe(const SGuildXihe& src) = default; //默认拷贝构造函数
	SGuildXihe& operator=(const SGuildXihe& rhs) = default; //默认赋值操作符
#endif
	SGuildXihe(SGuildXihe&& src); //转移构造函数
	SGuildXihe& operator=(SGuildXihe&& rhs); //转移赋值操作符
};

typedef std::vector<SGuildXihe> TVecGuildXihe;

//羲和神车的请求帮助信息
struct SXiheRequest
{
	UINT64 qwRoleID; //玩家ID
	std::string strName; //请求玩家的名字
	UINT8 byReqColor; //请求玩家的名字颜色
	UINT8 byPos; //货物顺序索引(0~7)
	UINT8 byTruckID; //货号ID
	UINT8 bystatus; //状态
	std::string strHelpName; //帮助玩家的名字
	UINT8 byHelpColor; //帮助者名字颜色

	SXiheRequest();
	SXiheRequest(UINT64 qwRoleID_, const std::string& strName_, UINT8 byReqColor_, UINT8 byPos_, UINT8 byTruckID_, 
		UINT8 bystatus_, const std::string& strHelpName_, UINT8 byHelpColor_);
#ifdef __GNUG__
	SXiheRequest(const SXiheRequest& src) = default; //默认拷贝构造函数
	SXiheRequest& operator=(const SXiheRequest& rhs) = default; //默认赋值操作符
#endif
	SXiheRequest(SXiheRequest&& src); //转移构造函数
	SXiheRequest& operator=(SXiheRequest&& rhs); //转移赋值操作符
};

typedef std::vector<SXiheRequest> TVecXiheRequest;

//帮派兑换物品
struct SGuildExchangedItem
{
	UINT64 qwGuildID; //帮派唯一ID
	UINT32 dwExchangeID; //兑换ID
	UINT32 dwCount; //兑换数量

	SGuildExchangedItem();
	SGuildExchangedItem(UINT64 qwGuildID_, UINT32 dwExchangeID_, UINT32 dwCount_);
};

typedef std::vector<SGuildExchangedItem> TVecGuildExchangedItem;

/////////////////////以下为序列化函数/////////////////////
CInArchive& operator>>(CInArchive&, SGuildInfoBase&);
COutArchive& operator<<(COutArchive&, const SGuildInfoBase&);
CInArchive& operator>>(CInArchive&, SGuildInfoBase_Wrapper&);
COutArchive& operator<<(COutArchive&, const SGuildInfoBase_Wrapper&);
CInArchive& operator>>(CInArchive&, TVecSGuildInfoBase&);
COutArchive& operator<<(COutArchive&, const TVecSGuildInfoBase&);

CInArchive& operator>>(CInArchive&, SGuildBaseInfo&);
COutArchive& operator<<(COutArchive&, const SGuildBaseInfo&);
CInArchive& operator>>(CInArchive&, TVecSGuildBaseInfo&);
COutArchive& operator<<(COutArchive&, const TVecSGuildBaseInfo&);

CInArchive& operator>>(CInArchive&, SGuildUserInfo&);
COutArchive& operator<<(COutArchive&, const SGuildUserInfo&);
CInArchive& operator>>(CInArchive&, TVecGuildUserInfo&);
COutArchive& operator<<(COutArchive&, const TVecGuildUserInfo&);

CInArchive& operator>>(CInArchive&, SGuildApplyInfo&);
COutArchive& operator<<(COutArchive&, const SGuildApplyInfo&);
CInArchive& operator>>(CInArchive&, TVecGuildApplyInfo&);
COutArchive& operator<<(COutArchive&, const TVecGuildApplyInfo&);

CInArchive& operator>>(CInArchive&, SGuildBuildingInfo&);
COutArchive& operator<<(COutArchive&, const SGuildBuildingInfo&);
CInArchive& operator>>(CInArchive&, TVecGuildBuildingInfo&);
COutArchive& operator<<(COutArchive&, const TVecGuildBuildingInfo&);

CInArchive& operator>>(CInArchive&, SGuildAuthorityInfo&);
COutArchive& operator<<(COutArchive&, const SGuildAuthorityInfo&);
CInArchive& operator>>(CInArchive&, TVecGuildAuthorityInfo&);
COutArchive& operator<<(COutArchive&, const TVecGuildAuthorityInfo&);

CInArchive& operator>>(CInArchive&, SGuildTechInfo&);
COutArchive& operator<<(COutArchive&, const SGuildTechInfo&);
CInArchive& operator>>(CInArchive&, TVecGuildTechInfo&);
COutArchive& operator<<(COutArchive&, const TVecGuildTechInfo&);

CInArchive& operator>>(CInArchive&, SGuildLogInfo&);
COutArchive& operator<<(COutArchive&, const SGuildLogInfo&);
CInArchive& operator>>(CInArchive&, TVecGuildLogInfo&);
COutArchive& operator<<(COutArchive&, const TVecGuildLogInfo&);

CInArchive& operator>>(CInArchive&, SGuildStatueInfo&);
COutArchive& operator<<(COutArchive&, const SGuildStatueInfo&);
CInArchive& operator>>(CInArchive&, TVecGuildStatueInfo&);
COutArchive& operator<<(COutArchive&, const TVecGuildStatueInfo&);

CInArchive& operator>>(CInArchive&, SDBGuildUserInfo&);
COutArchive& operator<<(COutArchive&, const SDBGuildUserInfo&);

CInArchive& operator>>(CInArchive&, SGuildAllInfo&);
COutArchive& operator<<(COutArchive&, const SGuildAllInfo&);

CInArchive& operator>>(CInArchive&, SDBGuildAllInfo&);
COutArchive& operator<<(COutArchive&, const SDBGuildAllInfo&);

CInArchive& operator>>(CInArchive&, SGuildListInfo&);
COutArchive& operator<<(COutArchive&, const SGuildListInfo&);

CInArchive& operator>>(CInArchive&, SDBGuildBattleInfo&);
COutArchive& operator<<(COutArchive&, const SDBGuildBattleInfo&);

CInArchive& operator>>(CInArchive&, SGetGuildInfoBase&);
COutArchive& operator<<(COutArchive&, const SGetGuildInfoBase&);
CInArchive& operator>>(CInArchive&, SGetGuildInfoBase_Wrapper&);
COutArchive& operator<<(COutArchive&, const SGetGuildInfoBase_Wrapper&);

CInArchive& operator>>(CInArchive&, SOtherGuildListInfo&);
COutArchive& operator<<(COutArchive&, const SOtherGuildListInfo&);
CInArchive& operator>>(CInArchive&, TVecOtherGuildListInfo&);
COutArchive& operator<<(COutArchive&, const TVecOtherGuildListInfo&);

CInArchive& operator>>(CInArchive&, SSelfGuildInfo&);
COutArchive& operator<<(COutArchive&, const SSelfGuildInfo&);

CInArchive& operator>>(CInArchive&, SPubGuildAllInfo&);
COutArchive& operator<<(COutArchive&, const SPubGuildAllInfo&);

CInArchive& operator>>(CInArchive&, STruckInfo&);
COutArchive& operator<<(COutArchive&, const STruckInfo&);

CInArchive& operator>>(CInArchive&, SGuildXihe&);
COutArchive& operator<<(COutArchive&, const SGuildXihe&);

CInArchive& operator>>(CInArchive&, SXiheRequest&);
COutArchive& operator<<(COutArchive&, const SXiheRequest&);

CInArchive& operator>>(CInArchive&, SGuildExchangedItem&);
COutArchive& operator<<(COutArchive&, const SGuildExchangedItem&);

#ifdef PROT_USE_XML
/////////////////////以下为XML转换函数/////////////////////
bool FromXML(TiXmlElement&, SGuildInfoBase&);
bool ToXML(const SGuildInfoBase&, TiXmlElement&);
bool SuperFromXML(TiXmlElement&, SGuildInfoBasePtr&);
bool SuperToXML(const SGuildInfoBase&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecSGuildInfoBase&);
bool VectorToXML(const TVecSGuildInfoBase&, TiXmlElement&);

bool FromXML(TiXmlElement&, SGuildBaseInfo&);
bool ToXML(const SGuildBaseInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecSGuildBaseInfo&);
bool VectorToXML(const TVecSGuildBaseInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SGuildUserInfo&);
bool ToXML(const SGuildUserInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecGuildUserInfo&);
bool VectorToXML(const TVecGuildUserInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SGuildApplyInfo&);
bool ToXML(const SGuildApplyInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecGuildApplyInfo&);
bool VectorToXML(const TVecGuildApplyInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SGuildBuildingInfo&);
bool ToXML(const SGuildBuildingInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecGuildBuildingInfo&);
bool VectorToXML(const TVecGuildBuildingInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SGuildAuthorityInfo&);
bool ToXML(const SGuildAuthorityInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecGuildAuthorityInfo&);
bool VectorToXML(const TVecGuildAuthorityInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SGuildTechInfo&);
bool ToXML(const SGuildTechInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecGuildTechInfo&);
bool VectorToXML(const TVecGuildTechInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SGuildLogInfo&);
bool ToXML(const SGuildLogInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecGuildLogInfo&);
bool VectorToXML(const TVecGuildLogInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SGuildStatueInfo&);
bool ToXML(const SGuildStatueInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecGuildStatueInfo&);
bool VectorToXML(const TVecGuildStatueInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SDBGuildUserInfo&);
bool ToXML(const SDBGuildUserInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecDBGuildUserInfo&);
bool VectorToXML(const TVecDBGuildUserInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SGuildAllInfo&);
bool ToXML(const SGuildAllInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecGuildAllInfo&);
bool VectorToXML(const TVecGuildAllInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SDBGuildAllInfo&);
bool ToXML(const SDBGuildAllInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecDBGuildAllInfo&);
bool VectorToXML(const TVecDBGuildAllInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SGuildListInfo&);
bool ToXML(const SGuildListInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecGuildListInfo&);
bool VectorToXML(const TVecGuildListInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SDBGuildBattleInfo&);
bool ToXML(const SDBGuildBattleInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecDBGuildBattleInfo&);
bool VectorToXML(const TVecDBGuildBattleInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SGetGuildInfoBase&);
bool ToXML(const SGetGuildInfoBase&, TiXmlElement&);
bool SuperFromXML(TiXmlElement&, SGetGuildInfoBasePtr&);
bool SuperToXML(const SGetGuildInfoBase&, TiXmlElement&);

bool FromXML(TiXmlElement&, SOtherGuildListInfo&);
bool ToXML(const SOtherGuildListInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecOtherGuildListInfo&);
bool VectorToXML(const TVecOtherGuildListInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SSelfGuildInfo&);
bool ToXML(const SSelfGuildInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SPubGuildAllInfo&);
bool ToXML(const SPubGuildAllInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecPubGuildAllInfo&);
bool VectorToXML(const TVecPubGuildAllInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, STruckInfo&);
bool ToXML(const STruckInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecTruckInfo&);
bool VectorToXML(const TVecTruckInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SGuildXihe&);
bool ToXML(const SGuildXihe&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecGuildXihe&);
bool VectorToXML(const TVecGuildXihe&, TiXmlElement&);

bool FromXML(TiXmlElement&, SXiheRequest&);
bool ToXML(const SXiheRequest&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecXiheRequest&);
bool VectorToXML(const TVecXiheRequest&, TiXmlElement&);

bool FromXML(TiXmlElement&, SGuildExchangedItem&);
bool ToXML(const SGuildExchangedItem&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecGuildExchangedItem&);
bool VectorToXML(const TVecGuildExchangedItem&, TiXmlElement&);
#endif //PROT_USE_XML

} //namespace NGuildProt
