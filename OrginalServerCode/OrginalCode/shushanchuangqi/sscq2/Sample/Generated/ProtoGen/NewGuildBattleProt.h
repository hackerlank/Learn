/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    NewGuildBattleProt.h
//  Purpose:      新帮派战相关协议
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

namespace NNewGuildBattleProt
{

/////////////////////以下为类型定义/////////////////////
//帮派战当前状态
enum ENGBState
{
	eNGBSNone, //没有开启帮派战
	eNGBSReady, //帮派战即将开启，倒计时通知阶段
	eNGBSBattle, //帮派战进行中
	eNGBSBattleEnd //帮派战战役结束
};

#ifdef PROT_USE_XML
const char* EnumValToStr(ENGBState);
bool EnumStrToVal(const char*, ENGBState&);
#endif //PROT_USE_XML

//帮派战玩家状态
enum ENGBPlayerState
{
	eNGBPSNone = 0, //无效状态
	eNGBPSWait, //待战状态
	eNGBPSDead, //死亡状态
	eNGBPSRunAway, //逃跑状态
	eNGBPSMax //最大状态
};

#ifdef PROT_USE_XML
const char* EnumValToStr(ENGBPlayerState);
bool EnumStrToVal(const char*, ENGBPlayerState&);
#endif //PROT_USE_XML

//帮派战灵山
enum ENGBMountain
{
	eNGBMNone = 0, //无效灵山
	eNGBMEMei, //峨眉
	eNGBMKunLun, //昆仑
	eNGBMHuangShan, //黄山
	eNGBMMax //最大灵山数
};

#ifdef PROT_USE_XML
const char* EnumValToStr(ENGBMountain);
bool EnumStrToVal(const char*, ENGBMountain&);
#endif //PROT_USE_XML

//帮派战洞府战阵眼类型
enum ENGBCaveCore
{
	eNGBCCNone = 0, //无效阵眼
	eNGBCCDragon, //青龙
	eNGBCCTiger, //白虎
	eNGBCCPhenix, //朱雀
	eNGBCCTurtle, //玄武
	eNGBCCMax //最大阵眼
};

#ifdef PROT_USE_XML
const char* EnumValToStr(ENGBCaveCore);
bool EnumStrToVal(const char*, ENGBCaveCore&);
#endif //PROT_USE_XML

//帮派灵山状态
enum ENGBMountainState
{
	eNGBMSNone = 0, //无效状态
	eNGBMSGate, //城门战
	eNGBMSCave, //洞府战
	eNGBMSEnd, //战斗结束
	eNGBMSMax //最大状态
};

#ifdef PROT_USE_XML
const char* EnumValToStr(ENGBMountainState);
bool EnumStrToVal(const char*, ENGBMountainState&);
#endif //PROT_USE_XML

//帮派战战斗方向
enum ENGBSide
{
	eNGBSideAttacker = 0, //进攻方
	eNGBSideDefencer = 1, //防守方
	eNGBSideInvalid //无效方
};

#ifdef PROT_USE_XML
const char* EnumValToStr(ENGBSide);
bool EnumStrToVal(const char*, ENGBSide&);
#endif //PROT_USE_XML

//帮派战返回结果
enum ENGBResult
{
	eNGBRSuccess = 0, //成功
	eNGBRFailed, //失败
	eNGBRWrongTime, //时间段错误
	eNGBRNotInBattle, //不在帮派战中
	eNGBRNoGuild, //不存在帮派
	eNGBRInvalidMountain, //错误的灵山
	eNGBRNoAuthority //权限不足
};

#ifdef PROT_USE_XML
const char* EnumValToStr(ENGBResult);
bool EnumStrToVal(const char*, ENGBResult&);
#endif //PROT_USE_XML

//帮派战进入结果
enum ENGBEnterResult
{
	eNGBERSuccess = 0, //进入成功
	eNGBERFailed, //进入失败
	eNGBERNotInGuild, //进入时不存在帮派
	eNGBERRepeat, //进入重复
	eNGBERWrongTime, //不在进入时段
	eNGBERGuildLevel, //帮派等级过低
	eNGBEREscape, //刚刚从战斗中逃离
	eNGBERGuildWrong //您的帮派未入围洞府战
};

#ifdef PROT_USE_XML
const char* EnumValToStr(ENGBEnterResult);
bool EnumStrToVal(const char*, ENGBEnterResult&);
#endif //PROT_USE_XML

//帮派战城门战攻击返回结果
enum ENGBGateAttackResult
{
	eNGBGARSuccess = 0, //攻击成功
	eNGBGARFailed, //攻击失败
	eNGBGARTargetIsDead, //目标已经死亡
	eNGBGARSelfIsDead, //还在死亡冷却中
	eNGBGARWrongTime, //不在正确的时间段内
	eNGBGARDefencer, //防守方不能攻击城门
	eNGBGARDefencerAlive //存在防守方成员
};

#ifdef PROT_USE_XML
const char* EnumValToStr(ENGBGateAttackResult);
bool EnumStrToVal(const char*, ENGBGateAttackResult&);
#endif //PROT_USE_XML

//帮派战购买傀儡返回结果
enum ENGBBuyPuppetResult
{
	eNGBBPRSuccess = 0, //购买成功
	eNGBBPRFailed, //购买失败
	eNGBBPRLackOfMoney, //货币不足
	eNGBBPRCountLimit, //已经到达上限
	eNGBBPRWrongTime, //不在正确的时间段内
	eNGBBPRDefencer //防守方不能购买傀儡
};

#ifdef PROT_USE_XML
const char* EnumValToStr(ENGBBuyPuppetResult);
bool EnumStrToVal(const char*, ENGBBuyPuppetResult&);
#endif //PROT_USE_XML

//帮派战买活返回结果
enum ENGBClearDeadCDResult
{
	eNGBCDCDRSuccess = 0, //买活成功
	eNGBCDCDRFailed, //买活失败
	eNGBCDCDRIsAlive, //已经复活
	eNGBCDCDRWrongTime //不在正确的时间段内
};

#ifdef PROT_USE_XML
const char* EnumValToStr(ENGBClearDeadCDResult);
bool EnumStrToVal(const char*, ENGBClearDeadCDResult&);
#endif //PROT_USE_XML

//帮派战洞府战战斗返回结果
enum ENGBCaveAttackResult
{
	eNGBCARSuccess = 0, //战斗成功
	eNGBCARFailed, //战斗失败
	eNGBCARBeCaptured, //已被他人占领
	eNGBCARCountLimit, //已经到达上限
	eNGBCARWrongTime, //不在正确的时间段内
	eNGBCARTargetDead, //目标已经死亡
	eNGBCARNotInCore, //不在阵眼上
	eNGBCARInCore, //在阵眼上无法攻击
	eNGBCARSelfIsDead, //还在死亡冷却中
	eNGBCARSelfSide //不能攻击自己人
};

#ifdef PROT_USE_XML
const char* EnumValToStr(ENGBCaveAttackResult);
bool EnumStrToVal(const char*, ENGBCaveAttackResult&);
#endif //PROT_USE_XML

//帮派战退出结果
enum ENGBQuitResult
{
	eNGBQuitSuccess = 0, //退出成功
	eNGBQuitFailed //退出失败
};

#ifdef PROT_USE_XML
const char* EnumValToStr(ENGBQuitResult);
bool EnumStrToVal(const char*, ENGBQuitResult&);
#endif //PROT_USE_XML

//帮派战战斗相关结果
enum ENGBBattleResult
{
	eNGBBattleSuccess = 0, //战斗成功
	eNGBBattleFailed //战斗失败
};

#ifdef PROT_USE_XML
const char* EnumValToStr(ENGBBattleResult);
bool EnumStrToVal(const char*, ENGBBattleResult&);
#endif //PROT_USE_XML

//傀儡信息
struct SPuppetInfo
{
	UINT8 byIndex; //所属站位(0,1,2; 0为系统战争傀儡)
	UINT64 qwOwnerID; //拥有者ID
	UINT32 dwNextAttackTime; //下一次攻击时间

	SPuppetInfo();
	SPuppetInfo(UINT8 byIndex_, UINT64 qwOwnerID_, UINT32 dwNextAttackTime_);
};

typedef std::vector<SPuppetInfo> TVecPuppetInfo;

//玩家信息
struct SPlayerInfo
{
	UINT64 qwRoleID; //玩家ID
	std::string strName; //玩家姓名
	NProtoCommon::ECareerType eJob; //职业
	NProtoCommon::ESexType eSex; //性别
	UINT8 byQuality; //品质
	UINT64 qwGuildID; //帮派ID
	ENGBSide eSide; //自己所在方向
	UINT32 dwMaxHP; //最大血量
	UINT32 dwHP; //当前血量
	UINT32 dwDeadTime; //死亡时间（复活所需时间）

	SPlayerInfo();
	SPlayerInfo(UINT64 qwRoleID_, const std::string& strName_, NProtoCommon::ECareerType eJob_, NProtoCommon::ESexType eSex_, UINT8 byQuality_, 
		UINT64 qwGuildID_, ENGBSide eSide_, UINT32 dwMaxHP_, UINT32 dwHP_, UINT32 dwDeadTime_);
#ifdef __GNUG__
	SPlayerInfo(const SPlayerInfo& src) = default; //默认拷贝构造函数
	SPlayerInfo& operator=(const SPlayerInfo& rhs) = default; //默认赋值操作符
#endif
	SPlayerInfo(SPlayerInfo&& src); //转移构造函数
	SPlayerInfo& operator=(SPlayerInfo&& rhs); //转移赋值操作符
};

//灵山面板信息
struct SMountainPanelInfo
{
	ENGBMountain eMountainType; //灵山类型
	ENGBMountainState eState; //灵山状态
	UINT64 qwGuildID; //当前占领帮派ID
	std::string strGuildName; //当前占领帮派名称
	UINT16 wGuildLevel; //当前占领帮派等级
	std::string strGuildOwnerName; //当前占领帮派帮主名称
	UINT32 dwGuildOwnCount; //当前占领帮派占领次数
	TVecUINT64 vecAttackGuildID; //（洞府战）攻击帮派ID

	SMountainPanelInfo();
	SMountainPanelInfo(ENGBMountain eMountainType_, ENGBMountainState eState_, UINT64 qwGuildID_, const std::string& strGuildName_, UINT16 wGuildLevel_, 
		const std::string& strGuildOwnerName_, UINT32 dwGuildOwnCount_, const TVecUINT64& vecAttackGuildID_);
#ifdef __GNUG__
	SMountainPanelInfo(const SMountainPanelInfo& src) = default; //默认拷贝构造函数
	SMountainPanelInfo& operator=(const SMountainPanelInfo& rhs) = default; //默认赋值操作符
#endif
	SMountainPanelInfo(SMountainPanelInfo&& src); //转移构造函数
	SMountainPanelInfo& operator=(SMountainPanelInfo&& rhs); //转移赋值操作符
};

typedef std::vector<SMountainPanelInfo> TVecMountainPanelInfo;

//面板玩家信息
struct SPlayerPanelInfo
{
	UINT64 qwRoleID; //玩家ID
	std::string strName; //玩家姓名
	UINT8 byLevel; //玩家等级
	UINT8 byQuality; //品质
	UINT64 qwGuildID; //帮派ID
	ENGBSide eSide; //自己所在方向
	std::string strGuildName; //帮派名称
	UINT8 byHPP; //剩余生命值百分比
	UINT32 dwMaxHP; //最大血量
	UINT32 dwHP; //当前血量

	SPlayerPanelInfo();
	SPlayerPanelInfo(UINT64 qwRoleID_, const std::string& strName_, UINT8 byLevel_, UINT8 byQuality_, UINT64 qwGuildID_, 
		ENGBSide eSide_, const std::string& strGuildName_, UINT8 byHPP_, UINT32 dwMaxHP_, UINT32 dwHP_);
#ifdef __GNUG__
	SPlayerPanelInfo(const SPlayerPanelInfo& src) = default; //默认拷贝构造函数
	SPlayerPanelInfo& operator=(const SPlayerPanelInfo& rhs) = default; //默认赋值操作符
#endif
	SPlayerPanelInfo(SPlayerPanelInfo&& src); //转移构造函数
	SPlayerPanelInfo& operator=(SPlayerPanelInfo&& rhs); //转移赋值操作符
};

typedef std::vector<SPlayerPanelInfo> TVecPlayerPanelInfo;

//占领历史信息
struct SOwnerHistoryInfo
{
	ENGBMountain eMountainType; //灵山类型
	UINT64 qwGuildID; //当前占领帮派ID
	std::string strGuildName; //当前占领帮派名称
	std::string strGuildOwnerName; //当前占领帮派帮主名称
	UINT32 dwTime; //占领时间

	SOwnerHistoryInfo();
	SOwnerHistoryInfo(ENGBMountain eMountainType_, UINT64 qwGuildID_, const std::string& strGuildName_, const std::string& strGuildOwnerName_, UINT32 dwTime_);
#ifdef __GNUG__
	SOwnerHistoryInfo(const SOwnerHistoryInfo& src) = default; //默认拷贝构造函数
	SOwnerHistoryInfo& operator=(const SOwnerHistoryInfo& rhs) = default; //默认赋值操作符
#endif
	SOwnerHistoryInfo(SOwnerHistoryInfo&& src); //转移构造函数
	SOwnerHistoryInfo& operator=(SOwnerHistoryInfo&& rhs); //转移赋值操作符
};

typedef std::vector<SOwnerHistoryInfo> TVecOwnerHistoryInfo;

//灵山城门信息
struct SMountainGateInfo
{
	UINT32 dwRemainTime; //开始倒计时
	UINT32 dwGateMaxHP; //城门总血量
	UINT32 dwGateHP; //城门剩余血量
	TVecPuppetInfo vecPuppetInfo; //傀儡信息
	ENGBSide eSelfSide; //自己所在方向
	SPlayerInfo sSelfInfo; //自己的信息
	TVecPlayerPanelInfo vecPlayerInfo; //对面玩家信息

	SMountainGateInfo();
	SMountainGateInfo(UINT32 dwRemainTime_, UINT32 dwGateMaxHP_, UINT32 dwGateHP_, const TVecPuppetInfo& vecPuppetInfo_, ENGBSide eSelfSide_, 
		const SPlayerInfo& sSelfInfo_, const TVecPlayerPanelInfo& vecPlayerInfo_);
#ifdef __GNUG__
	SMountainGateInfo(const SMountainGateInfo& src) = default; //默认拷贝构造函数
	SMountainGateInfo& operator=(const SMountainGateInfo& rhs) = default; //默认赋值操作符
#endif
	SMountainGateInfo(SMountainGateInfo&& src); //转移构造函数
	SMountainGateInfo& operator=(SMountainGateInfo&& rhs); //转移赋值操作符
};

//洞府阵眼信息
struct SCaveCoreInfo
{
	ENGBCaveCore eType; //阵眼类型
	TVecPlayerPanelInfo vecPlayerInfo; //占领者信息（数量只能为0/1）

	SCaveCoreInfo();
	SCaveCoreInfo(ENGBCaveCore eType_, const TVecPlayerPanelInfo& vecPlayerInfo_);
#ifdef __GNUG__
	SCaveCoreInfo(const SCaveCoreInfo& src) = default; //默认拷贝构造函数
	SCaveCoreInfo& operator=(const SCaveCoreInfo& rhs) = default; //默认赋值操作符
#endif
	SCaveCoreInfo(SCaveCoreInfo&& src); //转移构造函数
	SCaveCoreInfo& operator=(SCaveCoreInfo&& rhs); //转移赋值操作符
};

typedef std::vector<SCaveCoreInfo> TVecCaveCoreInfo;

//洞府战攻击帮派信息
struct SCaveAttackGuildInfo
{
	UINT64 qwGuildID; //帮派ID
	std::string strName; //帮派姓名
	UINT32 dwMaxEnergy; //能量上限
	UINT32 dwEnergy; //当前能量

	SCaveAttackGuildInfo();
	SCaveAttackGuildInfo(UINT64 qwGuildID_, const std::string& strName_, UINT32 dwMaxEnergy_, UINT32 dwEnergy_);
#ifdef __GNUG__
	SCaveAttackGuildInfo(const SCaveAttackGuildInfo& src) = default; //默认拷贝构造函数
	SCaveAttackGuildInfo& operator=(const SCaveAttackGuildInfo& rhs) = default; //默认赋值操作符
#endif
	SCaveAttackGuildInfo(SCaveAttackGuildInfo&& src); //转移构造函数
	SCaveAttackGuildInfo& operator=(SCaveAttackGuildInfo&& rhs); //转移赋值操作符
};

typedef std::vector<SCaveAttackGuildInfo> TVecCaveAttackGuildInfo;

//洞府战具体信息
struct SCaveInfo
{
	UINT32 dwRemainTime; //开始倒计时
	ENGBSide eSelfSide; //自己所在方向
	TVecCaveCoreInfo vecCaveCoreInfo; //阵眼信息
	TVecCaveAttackGuildInfo vecCaveAttackGuildInfo; //洞府攻击帮派信息
	SPlayerInfo sSelfInfo; //自己的信息
	TVecPlayerPanelInfo vecPlayerInfo; //对面玩家信息

	SCaveInfo();
	SCaveInfo(UINT32 dwRemainTime_, ENGBSide eSelfSide_, const TVecCaveCoreInfo& vecCaveCoreInfo_, const TVecCaveAttackGuildInfo& vecCaveAttackGuildInfo_, const SPlayerInfo& sSelfInfo_, 
		const TVecPlayerPanelInfo& vecPlayerInfo_);
#ifdef __GNUG__
	SCaveInfo(const SCaveInfo& src) = default; //默认拷贝构造函数
	SCaveInfo& operator=(const SCaveInfo& rhs) = default; //默认赋值操作符
#endif
	SCaveInfo(SCaveInfo&& src); //转移构造函数
	SCaveInfo& operator=(SCaveInfo&& rhs); //转移赋值操作符
};

//排行榜帮派信息
struct SGuildRankInfo
{
	UINT16 wRank; //排名
	UINT64 qwGuildID; //帮派ID
	std::string strName; //帮派姓名
	UINT32 dwScore; //战功

	SGuildRankInfo();
	SGuildRankInfo(UINT16 wRank_, UINT64 qwGuildID_, const std::string& strName_, UINT32 dwScore_);
#ifdef __GNUG__
	SGuildRankInfo(const SGuildRankInfo& src) = default; //默认拷贝构造函数
	SGuildRankInfo& operator=(const SGuildRankInfo& rhs) = default; //默认赋值操作符
#endif
	SGuildRankInfo(SGuildRankInfo&& src); //转移构造函数
	SGuildRankInfo& operator=(SGuildRankInfo&& rhs); //转移赋值操作符
};

typedef std::vector<SGuildRankInfo> TVecGuildRankInfo;

//排行榜帮派信息
struct SGuildMemberRankInfo
{
	UINT16 wRank; //排名
	UINT64 qwGuildID; //帮派ID
	UINT64 qwRoleID; //玩家ID
	std::string strName; //玩家姓名
	UINT32 dwScore; //战功

	SGuildMemberRankInfo();
	SGuildMemberRankInfo(UINT16 wRank_, UINT64 qwGuildID_, UINT64 qwRoleID_, const std::string& strName_, UINT32 dwScore_);
#ifdef __GNUG__
	SGuildMemberRankInfo(const SGuildMemberRankInfo& src) = default; //默认拷贝构造函数
	SGuildMemberRankInfo& operator=(const SGuildMemberRankInfo& rhs) = default; //默认赋值操作符
#endif
	SGuildMemberRankInfo(SGuildMemberRankInfo&& src); //转移构造函数
	SGuildMemberRankInfo& operator=(SGuildMemberRankInfo&& rhs); //转移赋值操作符
};

typedef std::vector<SGuildMemberRankInfo> TVecGuildMemberRankInfo;

//排行榜个人信息
struct SPlayerRankInfo
{
	UINT16 wRank; //排名
	UINT64 qwRoleID; //玩家ID
	std::string strName; //玩家姓名
	UINT32 dwScore; //战功

	SPlayerRankInfo();
	SPlayerRankInfo(UINT16 wRank_, UINT64 qwRoleID_, const std::string& strName_, UINT32 dwScore_);
#ifdef __GNUG__
	SPlayerRankInfo(const SPlayerRankInfo& src) = default; //默认拷贝构造函数
	SPlayerRankInfo& operator=(const SPlayerRankInfo& rhs) = default; //默认赋值操作符
#endif
	SPlayerRankInfo(SPlayerRankInfo&& src); //转移构造函数
	SPlayerRankInfo& operator=(SPlayerRankInfo&& rhs); //转移赋值操作符
};

typedef std::vector<SPlayerRankInfo> TVecPlayerRankInfo;

/////////////////////以下为序列化函数/////////////////////
CInArchive& operator>>(CInArchive&, SPuppetInfo&);
COutArchive& operator<<(COutArchive&, const SPuppetInfo&);

CInArchive& operator>>(CInArchive&, SPlayerInfo&);
COutArchive& operator<<(COutArchive&, const SPlayerInfo&);

CInArchive& operator>>(CInArchive&, SMountainPanelInfo&);
COutArchive& operator<<(COutArchive&, const SMountainPanelInfo&);

CInArchive& operator>>(CInArchive&, SPlayerPanelInfo&);
COutArchive& operator<<(COutArchive&, const SPlayerPanelInfo&);

CInArchive& operator>>(CInArchive&, SOwnerHistoryInfo&);
COutArchive& operator<<(COutArchive&, const SOwnerHistoryInfo&);

CInArchive& operator>>(CInArchive&, SMountainGateInfo&);
COutArchive& operator<<(COutArchive&, const SMountainGateInfo&);

CInArchive& operator>>(CInArchive&, SCaveCoreInfo&);
COutArchive& operator<<(COutArchive&, const SCaveCoreInfo&);

CInArchive& operator>>(CInArchive&, SCaveAttackGuildInfo&);
COutArchive& operator<<(COutArchive&, const SCaveAttackGuildInfo&);

CInArchive& operator>>(CInArchive&, SCaveInfo&);
COutArchive& operator<<(COutArchive&, const SCaveInfo&);

CInArchive& operator>>(CInArchive&, SGuildRankInfo&);
COutArchive& operator<<(COutArchive&, const SGuildRankInfo&);

CInArchive& operator>>(CInArchive&, SGuildMemberRankInfo&);
COutArchive& operator<<(COutArchive&, const SGuildMemberRankInfo&);

CInArchive& operator>>(CInArchive&, SPlayerRankInfo&);
COutArchive& operator<<(COutArchive&, const SPlayerRankInfo&);

#ifdef PROT_USE_XML
/////////////////////以下为XML转换函数/////////////////////
bool FromXML(TiXmlElement&, SPuppetInfo&);
bool ToXML(const SPuppetInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecPuppetInfo&);
bool VectorToXML(const TVecPuppetInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SPlayerInfo&);
bool ToXML(const SPlayerInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SMountainPanelInfo&);
bool ToXML(const SMountainPanelInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecMountainPanelInfo&);
bool VectorToXML(const TVecMountainPanelInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SPlayerPanelInfo&);
bool ToXML(const SPlayerPanelInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecPlayerPanelInfo&);
bool VectorToXML(const TVecPlayerPanelInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SOwnerHistoryInfo&);
bool ToXML(const SOwnerHistoryInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecOwnerHistoryInfo&);
bool VectorToXML(const TVecOwnerHistoryInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SMountainGateInfo&);
bool ToXML(const SMountainGateInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SCaveCoreInfo&);
bool ToXML(const SCaveCoreInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecCaveCoreInfo&);
bool VectorToXML(const TVecCaveCoreInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SCaveAttackGuildInfo&);
bool ToXML(const SCaveAttackGuildInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecCaveAttackGuildInfo&);
bool VectorToXML(const TVecCaveAttackGuildInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SCaveInfo&);
bool ToXML(const SCaveInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SGuildRankInfo&);
bool ToXML(const SGuildRankInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecGuildRankInfo&);
bool VectorToXML(const TVecGuildRankInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SGuildMemberRankInfo&);
bool ToXML(const SGuildMemberRankInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecGuildMemberRankInfo&);
bool VectorToXML(const TVecGuildMemberRankInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SPlayerRankInfo&);
bool ToXML(const SPlayerRankInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecPlayerRankInfo&);
bool VectorToXML(const TVecPlayerRankInfo&, TiXmlElement&);
#endif //PROT_USE_XML

} //namespace NNewGuildBattleProt
