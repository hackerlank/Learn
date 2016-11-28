/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    GuildBattleProt.h
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
#include "MapProt.h"

namespace NGuildBattleProt
{

/////////////////////以下为类型定义/////////////////////
//帮派战当前状态
enum EGBState
{
	eGBStateNone, //没有开启或即将开启的帮派战
	eGBStatePreReady, //帮派战报名即将开启
	eGBStateReady, //帮派战即将开启，报名阶段
	eGBStatePrepare, //帮派战准备中
	eGBStateBattle, //帮派战进行中
	eGBStateBattleEnd //帮派战战役结束
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EGBState);
bool EnumStrToVal(const char*, EGBState&);
#endif //PROT_USE_XML

//帮派战玩家状态
enum EGBUserState
{
	eGBUserStateNone = 0, //无效状态
	eGBUserStatePrepare, //准备状态(在准备场中)
	eGBUserStateWait, //待战状态
	eGBUserStateBattle, //战斗状态
	eGBUserStateDead, //死亡状态
	eGBUserStateWin, //胜利状态
	eGBUserStateWinTooMuch, //连胜八场，封刀
	eGBUserStateRunAway, //逃跑状态
	eGBUserStateMax //最大状态
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EGBUserState);
bool EnumStrToVal(const char*, EGBUserState&);
#endif //PROT_USE_XML

//帮派战据点
enum EGBSpot
{
	eGBSpotNone = 0, //无效据点
	eGBSpotYuzhufeng = 1, //玉柱峰
	eGBSpotGuangmingding = 2, //光明顶
	eGBSpotShiwangfeng = 3, //十王峰
	eGBSpotWanfoding = 4, //万佛顶
	eGBSpotMax, //最大据点
	eGBSpotZhurongfeng = 5, //祝融峰
	eGBSpotYuxuding = 6 //玉虚顶
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EGBSpot);
bool EnumStrToVal(const char*, EGBSpot&);
#endif //PROT_USE_XML

//帮派据点状态
enum EGBSpotState
{
	eGBSpotStateNone = 0, //无效状态
	eGBSpotStateWin, //胜利
	eGBSpotStateLose, //失败
	eGBSpotStateTie, //平局
	eGBSpotStateBattle, //战斗中
	eGBSpotStateNobody, //无人参战
	eGBSpotStateMax //最大状态
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EGBSpotState);
bool EnumStrToVal(const char*, EGBSpotState&);
#endif //PROT_USE_XML

//帮派战战斗方向
enum EGBSide
{
	eGBSideA = 0, //A方
	eGBSideB = 1, //B方
	eGBSideInvalid //无效方
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EGBSide);
bool EnumStrToVal(const char*, EGBSide&);
#endif //PROT_USE_XML

//帮派战技能
enum EGBSkill
{
	eGBSkillNone = 0, //无效技能
	eGBSkillAttack, //攻击强化
	eGBSkillDefence, //防御强化
	eGBSkillSpeed, //身法强化
	eGBSkillHP, //生命强化
	eGBSkillMax //技能最大值
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EGBSkill);
bool EnumStrToVal(const char*, EGBSkill&);
#endif //PROT_USE_XML

//帮派战返回结果
enum EGBResult
{
	eGBResultSuccess = 0, //成功
	eGBResultFailed, //失败
	eGBResultWrongTime, //时间段错误
	eGBResultNotInBattle, //不在帮派战中
	eGBResultNoGuild, //不存在帮派
	eGBResultNoAuthority //权限不足
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EGBResult);
bool EnumStrToVal(const char*, EGBResult&);
#endif //PROT_USE_XML

//帮派战报名结果
enum EGBSignUpResult
{
	eGBSignUpSuccess = 0, //报名成功
	eGBSignUpFailed, //报名失败
	eGBSignUpNotInGuild, //报名时不存在帮派
	eGBSignUpRepeat, //报名重复
	eGBSignUpWrongTime, //不在报名时段
	eGBSignUpSpotFull, //报名据点已满
	eGBSignUpEscape //由于您刚刚逃离了帮派战，暂时无法报名
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EGBSignUpResult);
bool EnumStrToVal(const char*, EGBSignUpResult&);
#endif //PROT_USE_XML

//帮派战进入结果
enum EGBEnterResult
{
	eGBEnterSuccess = 0, //进入成功
	eGBEnterFailed, //进入失败
	eGBEnterNotInGuild, //进入时不存在帮派
	eGBEnterRepeat, //进入重复
	eGBEnterWrongTime //不在进入时段
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EGBEnterResult);
bool EnumStrToVal(const char*, EGBEnterResult&);
#endif //PROT_USE_XML

//帮派战退出结果
enum EGBQuitResult
{
	eGBQuitSuccess = 0, //退出成功
	eGBQuitFailed, //退出失败
	eGBQuitNotInGuild, //退出时不存在帮派
	eGBQuitNotInBattle, //当前不在帮派战
	eGBQuitRepeat, //退出重复
	eGBQuitWrongTime //当前不存在帮派战
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EGBQuitResult);
bool EnumStrToVal(const char*, EGBQuitResult&);
#endif //PROT_USE_XML

//帮派战调整结果
enum EGBAdjustResult
{
	eGBAdjustSuccess = 0, //调整成功
	eGBAdjustFailed, //调整失败
	eGBAdjustNotInGuild, //调整时不存在帮派
	eGBAdjustNoAuthority, //调整权限不足
	eGBAdjustWrongTime, //不在调整时间段
	eGBAdjustSpotFull //调整目标据点已满
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EGBAdjustResult);
bool EnumStrToVal(const char*, EGBAdjustResult&);
#endif //PROT_USE_XML

//帮派战战斗相关结果
enum EGBBattleResult
{
	eGBBattleSuccess = 0, //战斗成功
	eGBBattleFailed, //战斗失败
	eGBBattleNotInGuild //战斗时不存在帮派
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EGBBattleResult);
bool EnumStrToVal(const char*, EGBBattleResult&);
#endif //PROT_USE_XML

//帮派战技能相关结果
enum EGBSkillResult
{
	eGBSkillSuccess = 0, //成功
	eGBSkillFailed, //失败
	eGBSkillWrongTime, //只有在准备阶段才可以购买增益祝福
	eGBSkillNoGold, //仙石不足
	eGBSkillAlreadyHave //已经拥有该效果
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EGBSkillResult);
bool EnumStrToVal(const char*, EGBSkillResult&);
#endif //PROT_USE_XML

//结构体：SBattleUserInfo的继承体系类型
enum EType_SBattleUserInfo
{
	eType_SBattleUserInfo, //类型：SBattleUserInfo
	eType_SBattleUserAllInfo //类型：SBattleUserAllInfo
};

//结构体：SSpotInfo的继承体系类型
enum EType_SSpotInfo
{
	eType_SSpotInfo, //类型：SSpotInfo
	eType_SSpotAllInfo, //类型：SSpotAllInfo
	eType_SSpotBriefInfo, //类型：SSpotBriefInfo
	eType_SSpotReadyInfo //类型：SSpotReadyInfo
};

//技能信息
struct SSkillInfo
{
	EGBSkill eType; //技能类型

	SSkillInfo();
	SSkillInfo(EGBSkill eType_);
};

typedef std::vector<SSkillInfo> TVecSkillInfo;

//帮派战玩家信息
struct SBattleUserInfo
{
	UINT64 qwRoleID; //成员角色ID
	std::string strName; //名字
	UINT16 wLevel; //等级
	EGBUserState eState; //玩家状态
	UINT16 wFighterID; //玩家主将ID
	TVecSkillInfo vecSkillInfo; //玩家技能信息

	SBattleUserInfo();
	virtual ~SBattleUserInfo() { }
#ifdef __GNUG__
	SBattleUserInfo(const SBattleUserInfo& src) = default; //默认拷贝构造函数
	SBattleUserInfo& operator=(const SBattleUserInfo& rhs) = default; //默认赋值操作符
#endif
	SBattleUserInfo(SBattleUserInfo&& src); //转移构造函数
	SBattleUserInfo& operator=(SBattleUserInfo&& rhs); //转移赋值操作符
	DEF_NEW_DELETE(SBattleUserInfo); //使用对象池
	virtual EType_SBattleUserInfo GetClassType() const { return eType_SBattleUserInfo; }
};

typedef std::shared_ptr<SBattleUserInfo> SBattleUserInfoPtr;
typedef std::weak_ptr<SBattleUserInfo> SBattleUserInfoWtr;
typedef std::vector<SBattleUserInfoPtr> TVecBattleUserInfo;

//父类：SBattleUserInfo的辅助结构体
struct SBattleUserInfo_Wrapper
{
	SBattleUserInfoPtr ptr;
	SBattleUserInfo_Wrapper(const SBattleUserInfoPtr& ptr_ = NULL) : ptr(ptr_) { }
};

//帮派战玩家详细信息（包括战斗相关属性）
struct SBattleUserAllInfo : public SBattleUserInfo
{
	NMapProt::SPlayerAppear sAppear; //外观
	UINT8 byHPP; //剩余HP百分比
	UINT8 byPosIndex; //据点站位编号
	UINT32 dwBattlePoint; //战斗力

	SBattleUserAllInfo();
#ifdef __GNUG__
	SBattleUserAllInfo(const SBattleUserAllInfo& src) = default; //默认拷贝构造函数
	SBattleUserAllInfo& operator=(const SBattleUserAllInfo& rhs) = default; //默认赋值操作符
#endif
	SBattleUserAllInfo(SBattleUserAllInfo&& src); //转移构造函数
	SBattleUserAllInfo& operator=(SBattleUserAllInfo&& rhs); //转移赋值操作符
	DEF_NEW_DELETE(SBattleUserAllInfo); //使用对象池
	virtual EType_SBattleUserInfo GetClassType() const { return eType_SBattleUserAllInfo; }
};

typedef std::shared_ptr<SBattleUserAllInfo> SBattleUserAllInfoPtr;
typedef std::weak_ptr<SBattleUserAllInfo> SBattleUserAllInfoWtr;
typedef std::vector<SBattleUserAllInfoPtr> TVecBattleUserAllInfo;

//战斗信息
struct SBattleInfo
{
	UINT64 qwBattleID; //战报ID
	std::string strNameA; //A方名字
	UINT64 qwRoleIDA; //A方ID
	std::string strNameB; //B方名字
	UINT64 qwRoleIDB; //B方ID
	EGBSide eWinnerSide; //获胜方

	SBattleInfo();
	SBattleInfo(UINT64 qwBattleID_, const std::string& strNameA_, UINT64 qwRoleIDA_, const std::string& strNameB_, UINT64 qwRoleIDB_, 
		EGBSide eWinnerSide_);
#ifdef __GNUG__
	SBattleInfo(const SBattleInfo& src) = default; //默认拷贝构造函数
	SBattleInfo& operator=(const SBattleInfo& rhs) = default; //默认赋值操作符
#endif
	SBattleInfo(SBattleInfo&& src); //转移构造函数
	SBattleInfo& operator=(SBattleInfo&& rhs); //转移赋值操作符
};

typedef std::vector<SBattleInfo> TVecBattleInfo;

//战斗详细数据
struct SBattleData
{
	UINT8 byIndex; //战斗场编号(1~3)
	UINT64 qwRoleIDA; //A方玩家ID
	UINT64 qwRoleIDB; //B方玩家ID
	EGBSide eWinnerSide; //获胜方
	std::string strBattleReport; //战报

	SBattleData();
	SBattleData(UINT8 byIndex_, UINT64 qwRoleIDA_, UINT64 qwRoleIDB_, EGBSide eWinnerSide_, const std::string& strBattleReport_);
#ifdef __GNUG__
	SBattleData(const SBattleData& src) = default; //默认拷贝构造函数
	SBattleData& operator=(const SBattleData& rhs) = default; //默认赋值操作符
#endif
	SBattleData(SBattleData&& src); //转移构造函数
	SBattleData& operator=(SBattleData&& rhs); //转移赋值操作符
};

typedef std::vector<SBattleData> TVecBattleData;

//战斗场信息
struct SBattleSlotInfo
{
	UINT8 byIndex; //战斗场编号(1~3)
	UINT64 qwBattleID; //战报ID
	SBattleUserAllInfo sUserAllInfoA; //A方成员信息
	SBattleUserAllInfo sUserAllInfoB; //B方成员信息

	SBattleSlotInfo();
	SBattleSlotInfo(UINT8 byIndex_, UINT64 qwBattleID_, const SBattleUserAllInfo& sUserAllInfoA_, const SBattleUserAllInfo& sUserAllInfoB_);
#ifdef __GNUG__
	SBattleSlotInfo(const SBattleSlotInfo& src) = default; //默认拷贝构造函数
	SBattleSlotInfo& operator=(const SBattleSlotInfo& rhs) = default; //默认赋值操作符
#endif
	SBattleSlotInfo(SBattleSlotInfo&& src); //转移构造函数
	SBattleSlotInfo& operator=(SBattleSlotInfo&& rhs); //转移赋值操作符
};

typedef std::vector<SBattleSlotInfo> TVecBattleSlotInfo;

//据点信息
struct SSpotInfo
{
	EGBSpot eSpotType; //据点类型

	SSpotInfo();
	virtual ~SSpotInfo() { }
	DEF_NEW_DELETE(SSpotInfo); //使用对象池
	virtual EType_SSpotInfo GetClassType() const { return eType_SSpotInfo; }
};

typedef std::shared_ptr<SSpotInfo> SSpotInfoPtr;
typedef std::weak_ptr<SSpotInfo> SSpotInfoWtr;
typedef std::vector<SSpotInfoPtr> TVecSpotInfo;

//父类：SSpotInfo的辅助结构体
struct SSpotInfo_Wrapper
{
	SSpotInfoPtr ptr;
	SSpotInfo_Wrapper(const SSpotInfoPtr& ptr_ = NULL) : ptr(ptr_) { }
};

//据点详细信息
struct SSpotAllInfo : public SSpotInfo
{
	EGBSpotState eState; //据点状态
	TVecBattleUserInfo vecMemberInfoA; //A方成员信息
	TVecBattleUserInfo vecMemberInfoB; //B方成员信息
	TVecBattleSlotInfo vecBattleSlotInfo; //战斗场信息
	TVecBattleInfo vecBattleInfo; //战报信息

	SSpotAllInfo();
#ifdef __GNUG__
	SSpotAllInfo(const SSpotAllInfo& src) = default; //默认拷贝构造函数
	SSpotAllInfo& operator=(const SSpotAllInfo& rhs) = default; //默认赋值操作符
#endif
	SSpotAllInfo(SSpotAllInfo&& src); //转移构造函数
	SSpotAllInfo& operator=(SSpotAllInfo&& rhs); //转移赋值操作符
	DEF_NEW_DELETE(SSpotAllInfo); //使用对象池
	virtual EType_SSpotInfo GetClassType() const { return eType_SSpotAllInfo; }
};

typedef std::shared_ptr<SSpotAllInfo> SSpotAllInfoPtr;
typedef std::weak_ptr<SSpotAllInfo> SSpotAllInfoWtr;
typedef std::vector<SSpotAllInfoPtr> TVecSpotAllInfo;

//据点简略信息
struct SSpotBriefInfo : public SSpotInfo
{
	EGBSpotState eState; //据点状态

	SSpotBriefInfo();
	DEF_NEW_DELETE(SSpotBriefInfo); //使用对象池
	virtual EType_SSpotInfo GetClassType() const { return eType_SSpotBriefInfo; }
};

typedef std::shared_ptr<SSpotBriefInfo> SSpotBriefInfoPtr;
typedef std::weak_ptr<SSpotBriefInfo> SSpotBriefInfoWtr;
typedef std::vector<SSpotBriefInfoPtr> TVecSpotBriefInfo;

//报名阶段据点信息
struct SSpotReadyInfo : public SSpotInfo
{
	UINT8 byCount; //该据点人数

	SSpotReadyInfo();
	DEF_NEW_DELETE(SSpotReadyInfo); //使用对象池
	virtual EType_SSpotInfo GetClassType() const { return eType_SSpotReadyInfo; }
};

typedef std::shared_ptr<SSpotReadyInfo> SSpotReadyInfoPtr;
typedef std::weak_ptr<SSpotReadyInfo> SSpotReadyInfoWtr;
typedef std::vector<SSpotReadyInfoPtr> TVecSpotReadyInfo;

//战场信息
struct SFieldInfo
{
	std::string strGuildNameA; //A方帮派名称
	std::string strGuildNameB; //B方帮派名称
	TVecSpotInfo vecSpotInfo; //据点详细信息

	SFieldInfo();
#ifdef __GNUG__
	SFieldInfo(const SFieldInfo& src) = default; //默认拷贝构造函数
	SFieldInfo& operator=(const SFieldInfo& rhs) = default; //默认赋值操作符
#endif
	SFieldInfo(SFieldInfo&& src); //转移构造函数
	SFieldInfo& operator=(SFieldInfo&& rhs); //转移赋值操作符
};

typedef std::vector<SFieldInfo> TVecFieldInfo;

/////////////////////以下为序列化函数/////////////////////
CInArchive& operator>>(CInArchive&, SSkillInfo&);
COutArchive& operator<<(COutArchive&, const SSkillInfo&);

CInArchive& operator>>(CInArchive&, SBattleUserInfo&);
COutArchive& operator<<(COutArchive&, const SBattleUserInfo&);
CInArchive& operator>>(CInArchive&, SBattleUserInfo_Wrapper&);
COutArchive& operator<<(COutArchive&, const SBattleUserInfo_Wrapper&);
CInArchive& operator>>(CInArchive&, TVecBattleUserInfo&);
COutArchive& operator<<(COutArchive&, const TVecBattleUserInfo&);

CInArchive& operator>>(CInArchive&, SBattleUserAllInfo&);
COutArchive& operator<<(COutArchive&, const SBattleUserAllInfo&);
CInArchive& operator>>(CInArchive&, TVecBattleUserAllInfo&);
COutArchive& operator<<(COutArchive&, const TVecBattleUserAllInfo&);

CInArchive& operator>>(CInArchive&, SBattleInfo&);
COutArchive& operator<<(COutArchive&, const SBattleInfo&);

CInArchive& operator>>(CInArchive&, SBattleData&);
COutArchive& operator<<(COutArchive&, const SBattleData&);

CInArchive& operator>>(CInArchive&, SBattleSlotInfo&);
COutArchive& operator<<(COutArchive&, const SBattleSlotInfo&);

CInArchive& operator>>(CInArchive&, SSpotInfo&);
COutArchive& operator<<(COutArchive&, const SSpotInfo&);
CInArchive& operator>>(CInArchive&, SSpotInfo_Wrapper&);
COutArchive& operator<<(COutArchive&, const SSpotInfo_Wrapper&);
CInArchive& operator>>(CInArchive&, TVecSpotInfo&);
COutArchive& operator<<(COutArchive&, const TVecSpotInfo&);

CInArchive& operator>>(CInArchive&, SSpotAllInfo&);
COutArchive& operator<<(COutArchive&, const SSpotAllInfo&);
CInArchive& operator>>(CInArchive&, TVecSpotAllInfo&);
COutArchive& operator<<(COutArchive&, const TVecSpotAllInfo&);

CInArchive& operator>>(CInArchive&, SSpotBriefInfo&);
COutArchive& operator<<(COutArchive&, const SSpotBriefInfo&);
CInArchive& operator>>(CInArchive&, TVecSpotBriefInfo&);
COutArchive& operator<<(COutArchive&, const TVecSpotBriefInfo&);

CInArchive& operator>>(CInArchive&, SSpotReadyInfo&);
COutArchive& operator<<(COutArchive&, const SSpotReadyInfo&);
CInArchive& operator>>(CInArchive&, TVecSpotReadyInfo&);
COutArchive& operator<<(COutArchive&, const TVecSpotReadyInfo&);

CInArchive& operator>>(CInArchive&, SFieldInfo&);
COutArchive& operator<<(COutArchive&, const SFieldInfo&);

#ifdef PROT_USE_XML
/////////////////////以下为XML转换函数/////////////////////
bool FromXML(TiXmlElement&, SSkillInfo&);
bool ToXML(const SSkillInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecSkillInfo&);
bool VectorToXML(const TVecSkillInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SBattleUserInfo&);
bool ToXML(const SBattleUserInfo&, TiXmlElement&);
bool SuperFromXML(TiXmlElement&, SBattleUserInfoPtr&);
bool SuperToXML(const SBattleUserInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecBattleUserInfo&);
bool VectorToXML(const TVecBattleUserInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SBattleUserAllInfo&);
bool ToXML(const SBattleUserAllInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecBattleUserAllInfo&);
bool VectorToXML(const TVecBattleUserAllInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SBattleInfo&);
bool ToXML(const SBattleInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecBattleInfo&);
bool VectorToXML(const TVecBattleInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SBattleData&);
bool ToXML(const SBattleData&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecBattleData&);
bool VectorToXML(const TVecBattleData&, TiXmlElement&);

bool FromXML(TiXmlElement&, SBattleSlotInfo&);
bool ToXML(const SBattleSlotInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecBattleSlotInfo&);
bool VectorToXML(const TVecBattleSlotInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SSpotInfo&);
bool ToXML(const SSpotInfo&, TiXmlElement&);
bool SuperFromXML(TiXmlElement&, SSpotInfoPtr&);
bool SuperToXML(const SSpotInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecSpotInfo&);
bool VectorToXML(const TVecSpotInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SSpotAllInfo&);
bool ToXML(const SSpotAllInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecSpotAllInfo&);
bool VectorToXML(const TVecSpotAllInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SSpotBriefInfo&);
bool ToXML(const SSpotBriefInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecSpotBriefInfo&);
bool VectorToXML(const TVecSpotBriefInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SSpotReadyInfo&);
bool ToXML(const SSpotReadyInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecSpotReadyInfo&);
bool VectorToXML(const TVecSpotReadyInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SFieldInfo&);
bool ToXML(const SFieldInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecFieldInfo&);
bool VectorToXML(const TVecFieldInfo&, TiXmlElement&);
#endif //PROT_USE_XML

} //namespace NGuildBattleProt
