/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    TeamGS.h
//  Purpose:      竞技场协议
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
#include "BattleGS.h"
#include "ItemProt.h"
#include "ProtoCommon.h"

namespace NTeamGS
{

/////////////////////以下为类型定义/////////////////////
//队伍状态
enum EMemberStatus
{
	EMEMBER_NONE, //无状态
	EMEMBER_READY, //已准备好
	EMEMBER_ERR //不满足条件提示
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EMemberStatus);
bool EnumStrToVal(const char*, EMemberStatus&);
#endif //PROT_USE_XML

//队伍状态
enum TeamListOP
{
	ETeam_Create, //队伍创建
	ETeam_UpDate, //队伍更新
	ETeam_Del //队伍删除
};

#ifdef PROT_USE_XML
const char* EnumValToStr(TeamListOP);
bool EnumStrToVal(const char*, TeamListOP&);
#endif //PROT_USE_XML

//竞技场操作结果
enum ETEAMResult
{
	ETeam_Suc, //成功
	ETeam_OtherTeam, //在其他房间中
	ETeam_NOTInTeam, //不在房间中
	ETeam_PreDgn, //前置副本没有通过
	ETeam_PackFull, //包裹满
	ETeam_Full, //房间满
	ETeam_NOLeader, //您不是队长
	ETeam_NODgnType, //不存在这个副本
	ETeam_ErrTeam, //不存在这个队伍
	ETeam_NewHeroErr, //新将不存在
	ETeam_MainHero, //主将不可替换
	ETeam_NewHeroIn, //新将已在
	ETeam_NewHeroPosErr, //新将位置错误
	ETeam_PlayerINReady, //玩家已准备
	ETeam_PlayerNOReady, //玩家没有准备好
	ETeam_MemBerNOReady, //有玩家没有准备好
	ETeam_LowLevel, //等级不足，无法进入副本
	ETeam_Fighters, //将不足，无法进入副本
	ETeam_KickSelf, //不可踢自己
	ETeam_KickErr, //被踢不在该队伍中
	ETeam_PosErr, //位置不正确
	ETeam_InBattle, //战斗中
	ETeam_MinPerSon, //人数不足
	ETeam_ErrPerSon, //有人不满足条件
	ETeam_DiffDgn, //副本人数不一致
	ETeam_PetErr, //错误玩家阵灵
	ETeam_PassWord, //密码错误
	ETeam_IsLeader, //已经是队长
	ETeam_ErrMem, //不是房间成员
	ETeam_OtherErr //其他错误
};

#ifdef PROT_USE_XML
const char* EnumValToStr(ETEAMResult);
bool EnumStrToVal(const char*, ETEAMResult&);
#endif //PROT_USE_XML
const char* GetDescription(ETEAMResult);

//结构体：TeamFighter的继承体系类型
enum EType_TeamFighter
{
	eType_TeamFighter, //类型：TeamFighter
	eType_CommonFighter, //类型：CommonFighter
	eType_FormationFighter, //类型：FormationFighter
	eType_BeautyFighter //类型：BeautyFighter
};

//房间里的战斗对象
struct TeamFighter
{
	NBattleGS::SFeatureBasePtr pFeature; //外观信息
	UINT32 dwFighterPower; //战斗力
	UINT8 byPos; //在玩家将序列的位置

	TeamFighter();
	virtual ~TeamFighter() { }
	DEF_NEW_DELETE(TeamFighter); //使用对象池
	virtual EType_TeamFighter GetClassType() const { return eType_TeamFighter; }
};

typedef std::shared_ptr<TeamFighter> TeamFighterPtr;
typedef std::weak_ptr<TeamFighter> TeamFighterWtr;
typedef std::vector<TeamFighterPtr> TVecTeamFighter;

//父类：TeamFighter的辅助结构体
struct TeamFighter_Wrapper
{
	TeamFighterPtr ptr;
	TeamFighter_Wrapper(const TeamFighterPtr& ptr_ = NULL) : ptr(ptr_) { }
};

//普通将
struct CommonFighter : public TeamFighter
{
	UINT64 qwInstID; //将唯一ID
	UINT16 wFighterID; //将类型ID
	UINT8 byLevel; //等级
	UINT8 byMain; //是否主将

	CommonFighter();
	DEF_NEW_DELETE(CommonFighter); //使用对象池
	virtual EType_TeamFighter GetClassType() const { return eType_CommonFighter; }
};

typedef std::shared_ptr<CommonFighter> CommonFighterPtr;
typedef std::weak_ptr<CommonFighter> CommonFighterWtr;
typedef std::vector<CommonFighterPtr> TVecCommonFighter;

//阵灵
struct FormationFighter : public TeamFighter
{
	UINT16 wFighterID; //阵灵ID
	UINT8 byPetLevel; //阵灵的阶

	FormationFighter();
	DEF_NEW_DELETE(FormationFighter); //使用对象池
	virtual EType_TeamFighter GetClassType() const { return eType_FormationFighter; }
};

typedef std::shared_ptr<FormationFighter> FormationFighterPtr;
typedef std::weak_ptr<FormationFighter> FormationFighterWtr;
typedef std::vector<FormationFighterPtr> TVecFormationFighter;

//阵灵
struct BeautyFighter : public TeamFighter
{
	UINT16 wFighterID; //阵灵ID

	BeautyFighter();
	DEF_NEW_DELETE(BeautyFighter); //使用对象池
	virtual EType_TeamFighter GetClassType() const { return eType_BeautyFighter; }
};

typedef std::shared_ptr<BeautyFighter> BeautyFighterPtr;
typedef std::weak_ptr<BeautyFighter> BeautyFighterWtr;
typedef std::vector<BeautyFighterPtr> TVecBeautyFighter;

//队伍玩家
struct TeamMember
{
	UINT64 qwRoleID; //玩家ID
	UINT8 byPos; //位置
	std::string strName; //名字
	EMemberStatus eStatus; //玩家状态
	UINT8 byVIPLevel; //vip等级
	NProtoCommon::SPlatformParam oPlatformParam; //qq平台信息
	TVecTeamFighter vecFighter; //战斗对象

	TeamMember();
#ifdef __GNUG__
	TeamMember(const TeamMember& src) = default; //默认拷贝构造函数
	TeamMember& operator=(const TeamMember& rhs) = default; //默认赋值操作符
#endif
	TeamMember(TeamMember&& src); //转移构造函数
	TeamMember& operator=(TeamMember&& rhs); //转移赋值操作符
};

typedef std::vector<TeamMember> TVecTeamMember;

//队伍设定
struct TeamSetting
{
	UINT32 dwPassWord; //队伍密码

	TeamSetting();
	TeamSetting(UINT32 dwPassWord_);
};

typedef std::vector<TeamSetting> TVecTeamSetting;

//队伍信息
struct TeamInfo
{
	UINT32 TeamID; //队伍ID
	UINT16 DgnType; //副本模板
	UINT64 TeamLeader; //队长ID
	UINT64 qwPetOwner; //出战阵灵的拥有者
	TeamSetting stSetting; //队伍设置
	TVecTeamMember vecMember; //队伍成员

	TeamInfo();
	TeamInfo(UINT32 TeamID_, UINT16 DgnType_, UINT64 TeamLeader_, UINT64 qwPetOwner_, const TeamSetting& stSetting_, 
		const TVecTeamMember& vecMember_);
#ifdef __GNUG__
	TeamInfo(const TeamInfo& src) = default; //默认拷贝构造函数
	TeamInfo& operator=(const TeamInfo& rhs) = default; //默认赋值操作符
#endif
	TeamInfo(TeamInfo&& src); //转移构造函数
	TeamInfo& operator=(TeamInfo&& rhs); //转移赋值操作符
};

typedef std::vector<TeamInfo> TVecTeamInfo;

//房间列表信息
struct TeamInfoForList
{
	UINT32 TeamID; //队伍ID
	UINT16 DgnType; //房间ID
	TeamSetting stSetting; //队伍设置密码0 或 1，1表示有密码
	TeamFighterPtr stLeader; //队长信息
	std::string strLeaderName; //队长名字
	UINT8 bySize; //当前人数

	TeamInfoForList();
#ifdef __GNUG__
	TeamInfoForList(const TeamInfoForList& src) = default; //默认拷贝构造函数
	TeamInfoForList& operator=(const TeamInfoForList& rhs) = default; //默认赋值操作符
#endif
	TeamInfoForList(TeamInfoForList&& src); //转移构造函数
	TeamInfoForList& operator=(TeamInfoForList&& rhs); //转移赋值操作符
};

typedef std::vector<TeamInfoForList> TVecTeamInfoForList;

/////////////////////以下为序列化函数/////////////////////
CInArchive& operator>>(CInArchive&, TeamFighter&);
COutArchive& operator<<(COutArchive&, const TeamFighter&);
CInArchive& operator>>(CInArchive&, TeamFighter_Wrapper&);
COutArchive& operator<<(COutArchive&, const TeamFighter_Wrapper&);
CInArchive& operator>>(CInArchive&, TVecTeamFighter&);
COutArchive& operator<<(COutArchive&, const TVecTeamFighter&);

CInArchive& operator>>(CInArchive&, CommonFighter&);
COutArchive& operator<<(COutArchive&, const CommonFighter&);
CInArchive& operator>>(CInArchive&, TVecCommonFighter&);
COutArchive& operator<<(COutArchive&, const TVecCommonFighter&);

CInArchive& operator>>(CInArchive&, FormationFighter&);
COutArchive& operator<<(COutArchive&, const FormationFighter&);
CInArchive& operator>>(CInArchive&, TVecFormationFighter&);
COutArchive& operator<<(COutArchive&, const TVecFormationFighter&);

CInArchive& operator>>(CInArchive&, BeautyFighter&);
COutArchive& operator<<(COutArchive&, const BeautyFighter&);
CInArchive& operator>>(CInArchive&, TVecBeautyFighter&);
COutArchive& operator<<(COutArchive&, const TVecBeautyFighter&);

CInArchive& operator>>(CInArchive&, TeamMember&);
COutArchive& operator<<(COutArchive&, const TeamMember&);

CInArchive& operator>>(CInArchive&, TeamSetting&);
COutArchive& operator<<(COutArchive&, const TeamSetting&);

CInArchive& operator>>(CInArchive&, TeamInfo&);
COutArchive& operator<<(COutArchive&, const TeamInfo&);

CInArchive& operator>>(CInArchive&, TeamInfoForList&);
COutArchive& operator<<(COutArchive&, const TeamInfoForList&);

#ifdef PROT_USE_XML
/////////////////////以下为XML转换函数/////////////////////
bool FromXML(TiXmlElement&, TeamFighter&);
bool ToXML(const TeamFighter&, TiXmlElement&);
bool SuperFromXML(TiXmlElement&, TeamFighterPtr&);
bool SuperToXML(const TeamFighter&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecTeamFighter&);
bool VectorToXML(const TVecTeamFighter&, TiXmlElement&);

bool FromXML(TiXmlElement&, CommonFighter&);
bool ToXML(const CommonFighter&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecCommonFighter&);
bool VectorToXML(const TVecCommonFighter&, TiXmlElement&);

bool FromXML(TiXmlElement&, FormationFighter&);
bool ToXML(const FormationFighter&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecFormationFighter&);
bool VectorToXML(const TVecFormationFighter&, TiXmlElement&);

bool FromXML(TiXmlElement&, BeautyFighter&);
bool ToXML(const BeautyFighter&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecBeautyFighter&);
bool VectorToXML(const TVecBeautyFighter&, TiXmlElement&);

bool FromXML(TiXmlElement&, TeamMember&);
bool ToXML(const TeamMember&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecTeamMember&);
bool VectorToXML(const TVecTeamMember&, TiXmlElement&);

bool FromXML(TiXmlElement&, TeamSetting&);
bool ToXML(const TeamSetting&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecTeamSetting&);
bool VectorToXML(const TVecTeamSetting&, TiXmlElement&);

bool FromXML(TiXmlElement&, TeamInfo&);
bool ToXML(const TeamInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecTeamInfo&);
bool VectorToXML(const TVecTeamInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, TeamInfoForList&);
bool ToXML(const TeamInfoForList&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecTeamInfoForList&);
bool VectorToXML(const TVecTeamInfoForList&, TiXmlElement&);
#endif //PROT_USE_XML

} //namespace NTeamGS
