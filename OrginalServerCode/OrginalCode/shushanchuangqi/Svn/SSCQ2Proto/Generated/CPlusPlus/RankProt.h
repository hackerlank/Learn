/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    RankProt.h
//  Purpose:      排行榜相关协议
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
#include "ProtoCommon.h"

namespace NRankProt
{

/////////////////////以下为类型定义/////////////////////
//排行榜类型
enum ERankType
{
	eRTNone = 0, //无效排行榜类型
	eRTHead, //魁首榜
	eRTRoleRankBegin, //玩家排行榜开始索引
	eRTBattlePoint = eRTRoleRankBegin, //总战力榜
	eRTLevel, //等级榜
	eRTFormation, //阵灵榜
	eRTHeroFighter, //散仙榜
	eRTTrump, //法宝榜
	eRTArena, //斗剑榜
	eRTRoleRankEnd = eRTArena, //玩家排行榜结束索引
	eRTGuildRankBegin, //帮派排行榜开始索引
	eRTGuildBattle = eRTGuildRankBegin, //帮派战排行榜
	eRTGuildRankEnd, //帮派排行榜结束索引
	eRTMax //排名类型最大值
};

#ifdef PROT_USE_XML
const char* EnumValToStr(ERankType);
bool EnumStrToVal(const char*, ERankType&);
#endif //PROT_USE_XML

//排行榜返回结果集
enum ERankResult
{
	eRRSuccess = 0, //操作成功
	eRRFailed, //操作失败
	eRRNotExist //不存在
};

#ifdef PROT_USE_XML
const char* EnumValToStr(ERankResult);
bool EnumStrToVal(const char*, ERankResult&);
#endif //PROT_USE_XML

//排行榜返回结果集
enum EAdoreResult
{
	eARSuccess = 0, //操作成功
	eARFailed, //操作失败
	eARNotExist //不存在
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EAdoreResult);
bool EnumStrToVal(const char*, EAdoreResult&);
#endif //PROT_USE_XML

//结构体：SRankInfo的继承体系类型
enum EType_SRankInfo
{
	eType_SRankInfo, //类型：SRankInfo
	eType_SRoleHeadInfo, //类型：SRoleHeadInfo
	eType_SRoleRankInfo, //类型：SRoleRankInfo
	eType_SGuildRankInfo, //类型：SGuildRankInfo
	eType_SRRBattlePointInfo, //类型：SRRBattlePointInfo
	eType_SRRLevelInfo, //类型：SRRLevelInfo
	eType_SRRFormationInfo, //类型：SRRFormationInfo
	eType_SRRHeroFighterInfo, //类型：SRRHeroFighterInfo
	eType_SRRTrumpInfo, //类型：SRRTrumpInfo
	eType_SRRArenaInfo, //类型：SRRArenaInfo
	eType_SGRBattleInfo, //类型：SGRBattleInfo
	eType_SGRLevelInfo //类型：SGRLevelInfo
};

//排名信息
struct SRankInfo
{
	UINT32 dwValue; //排名依据的信息(战斗力/等级……)
	UINT32 dwUpdateTime; //更新时间

	SRankInfo();
	virtual ~SRankInfo() { }
	DEF_NEW_DELETE(SRankInfo); //使用对象池
	virtual EType_SRankInfo GetClassType() const { return eType_SRankInfo; }
};

typedef std::shared_ptr<SRankInfo> SRankInfoPtr;
typedef std::weak_ptr<SRankInfo> SRankInfoWtr;
typedef std::vector<SRankInfoPtr> TVecRankInfo;

//父类：SRankInfo的辅助结构体
struct SRankInfo_Wrapper
{
	SRankInfoPtr ptr;
	SRankInfo_Wrapper(const SRankInfoPtr& ptr_ = NULL) : ptr(ptr_) { }
};

//魁首榜
struct SRoleHeadInfo : public SRankInfo
{
	ERankType eType; //排行榜类型
	UINT64 qwRoleID; //玩家ID
	std::string strName; //玩家姓名
	UINT16 wID; //对应ID
	UINT16 wPlayerFighterID; //主将ID
	UINT8 byQuality; //主将品质(颜色)
	UINT8 byInfoQuality; //魁首品质(颜色)
	std::string strGuildName; //帮派名字

	SRoleHeadInfo();
#ifdef __GNUG__
	SRoleHeadInfo(const SRoleHeadInfo& src) = default; //默认拷贝构造函数
	SRoleHeadInfo& operator=(const SRoleHeadInfo& rhs) = default; //默认赋值操作符
#endif
	SRoleHeadInfo(SRoleHeadInfo&& src); //转移构造函数
	SRoleHeadInfo& operator=(SRoleHeadInfo&& rhs); //转移赋值操作符
	DEF_NEW_DELETE(SRoleHeadInfo); //使用对象池
	virtual EType_SRankInfo GetClassType() const { return eType_SRoleHeadInfo; }
};

typedef std::shared_ptr<SRoleHeadInfo> SRoleHeadInfoPtr;
typedef std::weak_ptr<SRoleHeadInfo> SRoleHeadInfoWtr;
typedef std::vector<SRoleHeadInfoPtr> TVecRoleHeadInfo;

//玩家相关排名信息
struct SRoleRankInfo : public SRankInfo
{
	UINT64 qwRoleID; //玩家ID
	std::string strName; //玩家姓名
	UINT16 wPlayerFighterID; //主将ID
	UINT8 byQuality; //散仙品质(颜色)
	UINT8 byVIPLevel; //玩家VIP等级
	NProtoCommon::TVecPlatformParam vecPlatforms; //平台信息

	SRoleRankInfo();
	virtual ~SRoleRankInfo() { }
#ifdef __GNUG__
	SRoleRankInfo(const SRoleRankInfo& src) = default; //默认拷贝构造函数
	SRoleRankInfo& operator=(const SRoleRankInfo& rhs) = default; //默认赋值操作符
#endif
	SRoleRankInfo(SRoleRankInfo&& src); //转移构造函数
	SRoleRankInfo& operator=(SRoleRankInfo&& rhs); //转移赋值操作符
	DEF_NEW_DELETE(SRoleRankInfo); //使用对象池
	virtual EType_SRankInfo GetClassType() const { return eType_SRoleRankInfo; }
};

typedef std::shared_ptr<SRoleRankInfo> SRoleRankInfoPtr;
typedef std::weak_ptr<SRoleRankInfo> SRoleRankInfoWtr;
typedef std::vector<SRoleRankInfoPtr> TVecRoleRankInfo;

//父类：SRoleRankInfo的辅助结构体
struct SRoleRankInfo_Wrapper
{
	SRoleRankInfoPtr ptr;
	SRoleRankInfo_Wrapper(const SRoleRankInfoPtr& ptr_ = NULL) : ptr(ptr_) { }
};

//战力信息
struct SRRBattlePointInfo : public SRoleRankInfo
{
	UINT32 dwBattlePoint; //战斗力
	std::string strGuildName; //帮派名称

	SRRBattlePointInfo();
#ifdef __GNUG__
	SRRBattlePointInfo(const SRRBattlePointInfo& src) = default; //默认拷贝构造函数
	SRRBattlePointInfo& operator=(const SRRBattlePointInfo& rhs) = default; //默认赋值操作符
#endif
	SRRBattlePointInfo(SRRBattlePointInfo&& src); //转移构造函数
	SRRBattlePointInfo& operator=(SRRBattlePointInfo&& rhs); //转移赋值操作符
	DEF_NEW_DELETE(SRRBattlePointInfo); //使用对象池
	virtual EType_SRankInfo GetClassType() const { return eType_SRRBattlePointInfo; }
};

typedef std::shared_ptr<SRRBattlePointInfo> SRRBattlePointInfoPtr;
typedef std::weak_ptr<SRRBattlePointInfo> SRRBattlePointInfoWtr;
typedef std::vector<SRRBattlePointInfoPtr> TVecRRBattlePointInfo;

//等级信息
struct SRRLevelInfo : public SRoleRankInfo
{
	UINT16 wLevel; //等级
	UINT64 qwExp; //经验值

	SRRLevelInfo();
	DEF_NEW_DELETE(SRRLevelInfo); //使用对象池
	virtual EType_SRankInfo GetClassType() const { return eType_SRRLevelInfo; }
};

typedef std::shared_ptr<SRRLevelInfo> SRRLevelInfoPtr;
typedef std::weak_ptr<SRRLevelInfo> SRRLevelInfoWtr;
typedef std::vector<SRRLevelInfoPtr> TVecRRLevelInfo;

//阵灵信息
struct SRRFormationInfo : public SRoleRankInfo
{
	UINT32 dwBattlePoint; //战斗力
	std::string strGuildName; //帮派名称
	UINT16 wID; //阵灵配置表ID，同monster

	SRRFormationInfo();
#ifdef __GNUG__
	SRRFormationInfo(const SRRFormationInfo& src) = default; //默认拷贝构造函数
	SRRFormationInfo& operator=(const SRRFormationInfo& rhs) = default; //默认赋值操作符
#endif
	SRRFormationInfo(SRRFormationInfo&& src); //转移构造函数
	SRRFormationInfo& operator=(SRRFormationInfo&& rhs); //转移赋值操作符
	DEF_NEW_DELETE(SRRFormationInfo); //使用对象池
	virtual EType_SRankInfo GetClassType() const { return eType_SRRFormationInfo; }
};

typedef std::shared_ptr<SRRFormationInfo> SRRFormationInfoPtr;
typedef std::weak_ptr<SRRFormationInfo> SRRFormationInfoWtr;
typedef std::vector<SRRFormationInfoPtr> TVecRRFormationInfo;

//散仙信息
struct SRRHeroFighterInfo : public SRoleRankInfo
{
	UINT32 dwBattlePoint; //战斗力
	std::string strGuildName; //帮派名称
	UINT16 wID; //散仙类型
	UINT8 byInfoQuality; //散仙品质(颜色)

	SRRHeroFighterInfo();
#ifdef __GNUG__
	SRRHeroFighterInfo(const SRRHeroFighterInfo& src) = default; //默认拷贝构造函数
	SRRHeroFighterInfo& operator=(const SRRHeroFighterInfo& rhs) = default; //默认赋值操作符
#endif
	SRRHeroFighterInfo(SRRHeroFighterInfo&& src); //转移构造函数
	SRRHeroFighterInfo& operator=(SRRHeroFighterInfo&& rhs); //转移赋值操作符
	DEF_NEW_DELETE(SRRHeroFighterInfo); //使用对象池
	virtual EType_SRankInfo GetClassType() const { return eType_SRRHeroFighterInfo; }
};

typedef std::shared_ptr<SRRHeroFighterInfo> SRRHeroFighterInfoPtr;
typedef std::weak_ptr<SRRHeroFighterInfo> SRRHeroFighterInfoWtr;
typedef std::vector<SRRHeroFighterInfoPtr> TVecRRHeroFighterInfo;

//法宝信息
struct SRRTrumpInfo : public SRoleRankInfo
{
	UINT32 dwBattlePoint; //战斗力
	std::string strGuildName; //帮派名称
	UINT16 wID; //法宝ID

	SRRTrumpInfo();
#ifdef __GNUG__
	SRRTrumpInfo(const SRRTrumpInfo& src) = default; //默认拷贝构造函数
	SRRTrumpInfo& operator=(const SRRTrumpInfo& rhs) = default; //默认赋值操作符
#endif
	SRRTrumpInfo(SRRTrumpInfo&& src); //转移构造函数
	SRRTrumpInfo& operator=(SRRTrumpInfo&& rhs); //转移赋值操作符
	DEF_NEW_DELETE(SRRTrumpInfo); //使用对象池
	virtual EType_SRankInfo GetClassType() const { return eType_SRRTrumpInfo; }
};

typedef std::shared_ptr<SRRTrumpInfo> SRRTrumpInfoPtr;
typedef std::weak_ptr<SRRTrumpInfo> SRRTrumpInfoWtr;
typedef std::vector<SRRTrumpInfoPtr> TVecRRTrumpInfo;

//斗剑信息
struct SRRArenaInfo : public SRoleRankInfo
{
	UINT32 dwBattlePoint; //战斗力
	std::string strGuildName; //帮派名称

	SRRArenaInfo();
#ifdef __GNUG__
	SRRArenaInfo(const SRRArenaInfo& src) = default; //默认拷贝构造函数
	SRRArenaInfo& operator=(const SRRArenaInfo& rhs) = default; //默认赋值操作符
#endif
	SRRArenaInfo(SRRArenaInfo&& src); //转移构造函数
	SRRArenaInfo& operator=(SRRArenaInfo&& rhs); //转移赋值操作符
	DEF_NEW_DELETE(SRRArenaInfo); //使用对象池
	virtual EType_SRankInfo GetClassType() const { return eType_SRRArenaInfo; }
};

typedef std::shared_ptr<SRRArenaInfo> SRRArenaInfoPtr;
typedef std::weak_ptr<SRRArenaInfo> SRRArenaInfoWtr;
typedef std::vector<SRRArenaInfoPtr> TVecRRArenaInfo;

//帮派相关排名信息
struct SGuildRankInfo : public SRankInfo
{
	UINT64 qwGuildID; //帮派ID
	std::string strName; //帮主姓名
	UINT16 wLevel; //帮派等级
	std::string strGuildName; //帮派姓名
	UINT64 qwRoleID; //帮主ID
	UINT8 byQuality; //主将品质(颜色)
	UINT16 wPlayerFighterID; //主将ID

	SGuildRankInfo();
	virtual ~SGuildRankInfo() { }
#ifdef __GNUG__
	SGuildRankInfo(const SGuildRankInfo& src) = default; //默认拷贝构造函数
	SGuildRankInfo& operator=(const SGuildRankInfo& rhs) = default; //默认赋值操作符
#endif
	SGuildRankInfo(SGuildRankInfo&& src); //转移构造函数
	SGuildRankInfo& operator=(SGuildRankInfo&& rhs); //转移赋值操作符
	DEF_NEW_DELETE(SGuildRankInfo); //使用对象池
	virtual EType_SRankInfo GetClassType() const { return eType_SGuildRankInfo; }
};

typedef std::shared_ptr<SGuildRankInfo> SGuildRankInfoPtr;
typedef std::weak_ptr<SGuildRankInfo> SGuildRankInfoWtr;
typedef std::vector<SGuildRankInfoPtr> TVecGuildRankInfo;

//父类：SGuildRankInfo的辅助结构体
struct SGuildRankInfo_Wrapper
{
	SGuildRankInfoPtr ptr;
	SGuildRankInfo_Wrapper(const SGuildRankInfoPtr& ptr_ = NULL) : ptr(ptr_) { }
};

//帮派战排名
struct SGRBattleInfo : public SGuildRankInfo
{
	UINT32 dwBattleScore; //帮派战积分

	SGRBattleInfo();
	DEF_NEW_DELETE(SGRBattleInfo); //使用对象池
	virtual EType_SRankInfo GetClassType() const { return eType_SGRBattleInfo; }
};

typedef std::shared_ptr<SGRBattleInfo> SGRBattleInfoPtr;
typedef std::weak_ptr<SGRBattleInfo> SGRBattleInfoWtr;
typedef std::vector<SGRBattleInfoPtr> TVecGRBattleInfo;

//帮派等级排名
struct SGRLevelInfo : public SGuildRankInfo
{
	UINT16 wLevel2; //帮派等级

	SGRLevelInfo();
	DEF_NEW_DELETE(SGRLevelInfo); //使用对象池
	virtual EType_SRankInfo GetClassType() const { return eType_SGRLevelInfo; }
};

typedef std::shared_ptr<SGRLevelInfo> SGRLevelInfoPtr;
typedef std::weak_ptr<SGRLevelInfo> SGRLevelInfoWtr;
typedef std::vector<SGRLevelInfoPtr> TVecGRLevelInfo;

//崇拜数据库信息
struct SDBAdoreInfo
{
	UINT64 qwRoleID; //玩家ID
	UINT32 dwCount; //被崇拜数量
	UINT32 dwUpdateTime; //更新时间

	SDBAdoreInfo();
	SDBAdoreInfo(UINT64 qwRoleID_, UINT32 dwCount_, UINT32 dwUpdateTime_);
};

typedef std::vector<SDBAdoreInfo> TVecDBAdoreInfo;

/////////////////////以下为序列化函数/////////////////////
CInArchive& operator>>(CInArchive&, SRankInfo&);
COutArchive& operator<<(COutArchive&, const SRankInfo&);
CInArchive& operator>>(CInArchive&, SRankInfo_Wrapper&);
COutArchive& operator<<(COutArchive&, const SRankInfo_Wrapper&);
CInArchive& operator>>(CInArchive&, TVecRankInfo&);
COutArchive& operator<<(COutArchive&, const TVecRankInfo&);

CInArchive& operator>>(CInArchive&, SRoleHeadInfo&);
COutArchive& operator<<(COutArchive&, const SRoleHeadInfo&);
CInArchive& operator>>(CInArchive&, TVecRoleHeadInfo&);
COutArchive& operator<<(COutArchive&, const TVecRoleHeadInfo&);

CInArchive& operator>>(CInArchive&, SRoleRankInfo&);
COutArchive& operator<<(COutArchive&, const SRoleRankInfo&);
CInArchive& operator>>(CInArchive&, SRoleRankInfo_Wrapper&);
COutArchive& operator<<(COutArchive&, const SRoleRankInfo_Wrapper&);
CInArchive& operator>>(CInArchive&, TVecRoleRankInfo&);
COutArchive& operator<<(COutArchive&, const TVecRoleRankInfo&);

CInArchive& operator>>(CInArchive&, SRRBattlePointInfo&);
COutArchive& operator<<(COutArchive&, const SRRBattlePointInfo&);
CInArchive& operator>>(CInArchive&, TVecRRBattlePointInfo&);
COutArchive& operator<<(COutArchive&, const TVecRRBattlePointInfo&);

CInArchive& operator>>(CInArchive&, SRRLevelInfo&);
COutArchive& operator<<(COutArchive&, const SRRLevelInfo&);
CInArchive& operator>>(CInArchive&, TVecRRLevelInfo&);
COutArchive& operator<<(COutArchive&, const TVecRRLevelInfo&);

CInArchive& operator>>(CInArchive&, SRRFormationInfo&);
COutArchive& operator<<(COutArchive&, const SRRFormationInfo&);
CInArchive& operator>>(CInArchive&, TVecRRFormationInfo&);
COutArchive& operator<<(COutArchive&, const TVecRRFormationInfo&);

CInArchive& operator>>(CInArchive&, SRRHeroFighterInfo&);
COutArchive& operator<<(COutArchive&, const SRRHeroFighterInfo&);
CInArchive& operator>>(CInArchive&, TVecRRHeroFighterInfo&);
COutArchive& operator<<(COutArchive&, const TVecRRHeroFighterInfo&);

CInArchive& operator>>(CInArchive&, SRRTrumpInfo&);
COutArchive& operator<<(COutArchive&, const SRRTrumpInfo&);
CInArchive& operator>>(CInArchive&, TVecRRTrumpInfo&);
COutArchive& operator<<(COutArchive&, const TVecRRTrumpInfo&);

CInArchive& operator>>(CInArchive&, SRRArenaInfo&);
COutArchive& operator<<(COutArchive&, const SRRArenaInfo&);
CInArchive& operator>>(CInArchive&, TVecRRArenaInfo&);
COutArchive& operator<<(COutArchive&, const TVecRRArenaInfo&);

CInArchive& operator>>(CInArchive&, SGuildRankInfo&);
COutArchive& operator<<(COutArchive&, const SGuildRankInfo&);
CInArchive& operator>>(CInArchive&, SGuildRankInfo_Wrapper&);
COutArchive& operator<<(COutArchive&, const SGuildRankInfo_Wrapper&);
CInArchive& operator>>(CInArchive&, TVecGuildRankInfo&);
COutArchive& operator<<(COutArchive&, const TVecGuildRankInfo&);

CInArchive& operator>>(CInArchive&, SGRBattleInfo&);
COutArchive& operator<<(COutArchive&, const SGRBattleInfo&);
CInArchive& operator>>(CInArchive&, TVecGRBattleInfo&);
COutArchive& operator<<(COutArchive&, const TVecGRBattleInfo&);

CInArchive& operator>>(CInArchive&, SGRLevelInfo&);
COutArchive& operator<<(COutArchive&, const SGRLevelInfo&);
CInArchive& operator>>(CInArchive&, TVecGRLevelInfo&);
COutArchive& operator<<(COutArchive&, const TVecGRLevelInfo&);

CInArchive& operator>>(CInArchive&, SDBAdoreInfo&);
COutArchive& operator<<(COutArchive&, const SDBAdoreInfo&);

#ifdef PROT_USE_XML
/////////////////////以下为XML转换函数/////////////////////
bool FromXML(TiXmlElement&, SRankInfo&);
bool ToXML(const SRankInfo&, TiXmlElement&);
bool SuperFromXML(TiXmlElement&, SRankInfoPtr&);
bool SuperToXML(const SRankInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecRankInfo&);
bool VectorToXML(const TVecRankInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SRoleHeadInfo&);
bool ToXML(const SRoleHeadInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecRoleHeadInfo&);
bool VectorToXML(const TVecRoleHeadInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SRoleRankInfo&);
bool ToXML(const SRoleRankInfo&, TiXmlElement&);
bool SuperFromXML(TiXmlElement&, SRoleRankInfoPtr&);
bool SuperToXML(const SRoleRankInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecRoleRankInfo&);
bool VectorToXML(const TVecRoleRankInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SRRBattlePointInfo&);
bool ToXML(const SRRBattlePointInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecRRBattlePointInfo&);
bool VectorToXML(const TVecRRBattlePointInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SRRLevelInfo&);
bool ToXML(const SRRLevelInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecRRLevelInfo&);
bool VectorToXML(const TVecRRLevelInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SRRFormationInfo&);
bool ToXML(const SRRFormationInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecRRFormationInfo&);
bool VectorToXML(const TVecRRFormationInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SRRHeroFighterInfo&);
bool ToXML(const SRRHeroFighterInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecRRHeroFighterInfo&);
bool VectorToXML(const TVecRRHeroFighterInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SRRTrumpInfo&);
bool ToXML(const SRRTrumpInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecRRTrumpInfo&);
bool VectorToXML(const TVecRRTrumpInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SRRArenaInfo&);
bool ToXML(const SRRArenaInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecRRArenaInfo&);
bool VectorToXML(const TVecRRArenaInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SGuildRankInfo&);
bool ToXML(const SGuildRankInfo&, TiXmlElement&);
bool SuperFromXML(TiXmlElement&, SGuildRankInfoPtr&);
bool SuperToXML(const SGuildRankInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecGuildRankInfo&);
bool VectorToXML(const TVecGuildRankInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SGRBattleInfo&);
bool ToXML(const SGRBattleInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecGRBattleInfo&);
bool VectorToXML(const TVecGRBattleInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SGRLevelInfo&);
bool ToXML(const SGRLevelInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecGRLevelInfo&);
bool VectorToXML(const TVecGRLevelInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SDBAdoreInfo&);
bool ToXML(const SDBAdoreInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecDBAdoreInfo&);
bool VectorToXML(const TVecDBAdoreInfo&, TiXmlElement&);
#endif //PROT_USE_XML

} //namespace NRankProt
