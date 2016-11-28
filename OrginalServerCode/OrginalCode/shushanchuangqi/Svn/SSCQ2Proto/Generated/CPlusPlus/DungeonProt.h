/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    DungeonProt.h
//  Purpose:      副本相关协议
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

namespace NDungeonProt
{

/////////////////////以下为类型定义/////////////////////
//副本结果
enum EDungeonResult
{
	eDungeonSuccess, //成功
	eDungeonSweepingErr, //正在扫荡中
	eDungeonPowerErr, //体力不足
	eDungeonNotSweepingErr, //不在扫荡中
	eDungeonSweepingSpeedUpErr, //扫荡加速中
	eDungeonTypeNotExist, //此副本类型不存在
	eDungeonInDgn, //你在副本中
	eDungeonLowLevel, //你等级不够
	eDungeonCreateErrType, //副本类型不正确，不可以创建副本
	eDungeonPreDgnNotFinish, //前置副本未完成
	eDungeonPackEmptyMin, //包裹空格子不足
	eDungeonOutDgn, //你不在副本中
	eDungeonInsNotExist, //副本不存在
	eDungeonNotFinish, //副本未完成
	eDungeonBusy, //玩家忙
	eDungeonNotSweeping, //不在扫荡状态
	eSpeedUpItemLimit, //加速道具不足
	eDungeonTimesLimit, //进入次数不足
	eDungeonTimesLimitForHero, //英雄本进入次数不足
	eDungeonTimesLimitForLiXian, //历险本进入次数不足
	eDungeonVipBuyHero, //购买英雄副本vip等级不足
	eDungeonVipBuyLiXian, //购买历险副本vip等级不足
	eDungeonNOGold, //仙石不足
	eDungeonOtherErr //未知错误
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EDungeonResult);
bool EnumStrToVal(const char*, EDungeonResult&);
#endif //PROT_USE_XML
const char* GetDescription(EDungeonResult);

//副本类型
enum EDgnType
{
	eNoneDgn, //无定义
	ePlayerDgn, //单人副本
	eGatherDgn, //采集副本
	eTeamDgn, //组队副本
	eDemonTowerDgn //镇妖塔副本
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EDgnType);
bool EnumStrToVal(const char*, EDgnType&);
#endif //PROT_USE_XML
const char* GetDescription(EDgnType);

//副本次类型
enum EDgnSubType
{
	eSubCommon, //普通
	eSubHero, //英雄副本
	eSubHistory, //史诗副本
	eSubLiXian //历险副本
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EDgnSubType);
bool EnumStrToVal(const char*, EDgnSubType&);
#endif //PROT_USE_XML
const char* GetDescription(EDgnSubType);

//条件状态
enum EDgnCondStatus
{
	eCondRun, //未达成
	eCondSuc, //已达成
	eCondFal //已失败
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EDgnCondStatus);
bool EnumStrToVal(const char*, EDgnCondStatus&);
#endif //PROT_USE_XML
const char* GetDescription(EDgnCondStatus);

//副本评价
enum ELogicType
{
	eLogicNone, //无评价
	eLogicOrderMonster //按顺序杀怪
};

#ifdef PROT_USE_XML
const char* EnumValToStr(ELogicType);
bool EnumStrToVal(const char*, ELogicType&);
#endif //PROT_USE_XML
const char* GetDescription(ELogicType);

//结构体：DgnSucCond的继承体系类型
enum EType_DgnSucCond
{
	eType_DgnSucCond, //类型：DgnSucCond
	eType_SucMonster, //类型：SucMonster
	eType_SucGather, //类型：SucGather
	eType_SucTurns, //类型：SucTurns
	eType_SucInTimer, //类型：SucInTimer
	eType_SucMonsterInTimer, //类型：SucMonsterInTimer
	eType_SucGatherInTimer, //类型：SucGatherInTimer
	eType_SucFightWithMonsterMinTimes, //类型：SucFightWithMonsterMinTimes
	eType_SucArriveArea //类型：SucArriveArea
};

//副本条件
struct DgnSucCond
{
	UINT16 wCondId; //条件ID
	EDgnCondStatus eStatus; //0,未达成，1表示已达成，2表示已失败

	DgnSucCond();
	virtual ~DgnSucCond() { }
	DEF_NEW_DELETE(DgnSucCond); //使用对象池
	virtual EType_DgnSucCond GetClassType() const { return eType_DgnSucCond; }
};

typedef std::shared_ptr<DgnSucCond> DgnSucCondPtr;
typedef std::weak_ptr<DgnSucCond> DgnSucCondWtr;
typedef std::vector<DgnSucCondPtr> TVecSucCond;

//父类：DgnSucCond的辅助结构体
struct DgnSucCond_Wrapper
{
	DgnSucCondPtr ptr;
	DgnSucCond_Wrapper(const DgnSucCondPtr& ptr_ = NULL) : ptr(ptr_) { }
};

//杀怪条件
struct SucMonster : public DgnSucCond
{
	UINT16 wMonsterGroup; //怪物组ID
	UINT8 byTotalNum; //怪物总数
	UINT8 byCurNum; //当前数量

	SucMonster();
	DEF_NEW_DELETE(SucMonster); //使用对象池
	virtual EType_DgnSucCond GetClassType() const { return eType_SucMonster; }
};

typedef std::shared_ptr<SucMonster> SucMonsterPtr;
typedef std::weak_ptr<SucMonster> SucMonsterWtr;
typedef std::vector<SucMonsterPtr> TVecSucMonster;

//采集条件
struct SucGather : public DgnSucCond
{
	UINT16 wGather; //采集ID
	UINT8 byTotalNum; //采集总数
	UINT8 byCurNum; //当前数量

	SucGather();
	DEF_NEW_DELETE(SucGather); //使用对象池
	virtual EType_DgnSucCond GetClassType() const { return eType_SucGather; }
};

typedef std::shared_ptr<SucGather> SucGatherPtr;
typedef std::weak_ptr<SucGather> SucGatherWtr;
typedef std::vector<SucGatherPtr> TVecSucGather;

//回合数判定
struct SucTurns : public DgnSucCond
{
	UINT8 byTotalTurns; //总回合数
	UINT8 byCurTurns; //当前回合数

	SucTurns();
	DEF_NEW_DELETE(SucTurns); //使用对象池
	virtual EType_DgnSucCond GetClassType() const { return eType_SucTurns; }
};

typedef std::shared_ptr<SucTurns> SucTurnsPtr;
typedef std::weak_ptr<SucTurns> SucTurnsWtr;
typedef std::vector<SucTurnsPtr> TVecSucTurns;

//时间判定
struct SucInTimer : public DgnSucCond
{
	UINT32 dwTotalTimer; //总计时间
	UINT32 dwBeginTimer; //起始时间

	SucInTimer();
	DEF_NEW_DELETE(SucInTimer); //使用对象池
	virtual EType_DgnSucCond GetClassType() const { return eType_SucInTimer; }
};

typedef std::shared_ptr<SucInTimer> SucInTimerPtr;
typedef std::weak_ptr<SucInTimer> SucInTimerWtr;
typedef std::vector<SucInTimerPtr> TVecSucInTimer;

//定时杀怪
struct SucMonsterInTimer : public DgnSucCond
{
	UINT32 dwTotalTimer; //总计时间
	UINT32 dwBeginTimer; //起始时间
	UINT16 wMonsterGroup; //怪物组ID
	UINT8 byTotalNum; //怪物总数
	UINT8 byCurNum; //当前数量

	SucMonsterInTimer();
	DEF_NEW_DELETE(SucMonsterInTimer); //使用对象池
	virtual EType_DgnSucCond GetClassType() const { return eType_SucMonsterInTimer; }
};

typedef std::shared_ptr<SucMonsterInTimer> SucMonsterInTimerPtr;
typedef std::weak_ptr<SucMonsterInTimer> SucMonsterInTimerWtr;
typedef std::vector<SucMonsterInTimerPtr> TVecSucMonsterInTimer;

//定时采集
struct SucGatherInTimer : public DgnSucCond
{
	UINT32 dwTotalTimer; //总计时间
	UINT32 dwBeginTimer; //起始时间
	UINT16 wGather; //采集ID
	UINT8 byTotalNum; //采集总数
	UINT8 byCurNum; //当前数量

	SucGatherInTimer();
	DEF_NEW_DELETE(SucGatherInTimer); //使用对象池
	virtual EType_DgnSucCond GetClassType() const { return eType_SucGatherInTimer; }
};

typedef std::shared_ptr<SucGatherInTimer> SucGatherInTimerPtr;
typedef std::weak_ptr<SucGatherInTimer> SucGatherInTimerWtr;
typedef std::vector<SucGatherInTimerPtr> TVecSucGatherInTimer;

//尽量不和怪物发生战斗
struct SucFightWithMonsterMinTimes : public DgnSucCond
{
	UINT16 wGroup; //怪物
	UINT8 byTotalTimes; //总战斗次数
	UINT8 byCurTimes; //当前战斗次数

	SucFightWithMonsterMinTimes();
	DEF_NEW_DELETE(SucFightWithMonsterMinTimes); //使用对象池
	virtual EType_DgnSucCond GetClassType() const { return eType_SucFightWithMonsterMinTimes; }
};

typedef std::shared_ptr<SucFightWithMonsterMinTimes> SucFightWithMonsterMinTimesPtr;
typedef std::weak_ptr<SucFightWithMonsterMinTimes> SucFightWithMonsterMinTimesWtr;
typedef std::vector<SucFightWithMonsterMinTimesPtr> TVecSucFightWithMonsterMinTimes;

//到达某个区域
struct SucArriveArea : public DgnSucCond
{
	UINT16 wAreaID; //区域ID

	SucArriveArea();
	DEF_NEW_DELETE(SucArriveArea); //使用对象池
	virtual EType_DgnSucCond GetClassType() const { return eType_SucArriveArea; }
};

typedef std::shared_ptr<SucArriveArea> SucArriveAreaPtr;
typedef std::weak_ptr<SucArriveArea> SucArriveAreaWtr;
typedef std::vector<SucArriveAreaPtr> TVecSucArriveArea;

//多重条件信息
struct MulCond
{
	TVecSucCond vecCond; //多重条件

	MulCond();
#ifdef __GNUG__
	MulCond(const MulCond& src) = default; //默认拷贝构造函数
	MulCond& operator=(const MulCond& rhs) = default; //默认赋值操作符
#endif
	MulCond(MulCond&& src); //转移构造函数
	MulCond& operator=(MulCond&& rhs); //转移赋值操作符
};

typedef std::vector<MulCond> TVecMulCond;

//副本星级信息
struct DgnStar
{
	UINT16 wDgnId; //副本ID
	UINT8 byStar; //星级
	UINT32 dwFinishTimesToday; //今日完成次数
	UINT32 dwBuyTimesToday; //今日购买次数
	UINT32 dwBuyTimes; //购买的总次数
	UINT32 dwCompleteTimes; //总通关次数

	DgnStar();
	DgnStar(UINT16 wDgnId_, UINT8 byStar_, UINT32 dwFinishTimesToday_, UINT32 dwBuyTimesToday_, UINT32 dwBuyTimes_, 
		UINT32 dwCompleteTimes_);
};

typedef std::vector<DgnStar> TVecDgnStar;

//历险副本信息
struct DgnLiXian
{
	UINT32 dwFinishTimesToday; //今日完成次数
	UINT32 dwBuyTimesToday; //今日购买次数
	UINT32 dwBuyTimes; //购买的总次数

	DgnLiXian();
	DgnLiXian(UINT32 dwFinishTimesToday_, UINT32 dwBuyTimesToday_, UINT32 dwBuyTimes_);
};

typedef std::vector<DgnLiXian> TVecDgnLiXian;

//扫荡信息
struct SSweepInfo
{
	UINT64 qwRoleID; //玩家ID
	UINT16 wCurDgnID; //当前扫荡副本
	UINT16 wCurCount; //当前剩余扫荡次数
	UINT32 dwReserverTime; //下次扫荡剩余时间
	UINT32 dwSaveTime; //保存时间
	UINT16 wOptions; //扫荡类型
	UINT16 wCount; //扫荡需求次数
	std::string strVecDgn; //未开始扫荡副本

	SSweepInfo();
	SSweepInfo(UINT64 qwRoleID_, UINT16 wCurDgnID_, UINT16 wCurCount_, UINT32 dwReserverTime_, UINT32 dwSaveTime_, 
		UINT16 wOptions_, UINT16 wCount_, const std::string& strVecDgn_);
#ifdef __GNUG__
	SSweepInfo(const SSweepInfo& src) = default; //默认拷贝构造函数
	SSweepInfo& operator=(const SSweepInfo& rhs) = default; //默认赋值操作符
#endif
	SSweepInfo(SSweepInfo&& src); //转移构造函数
	SSweepInfo& operator=(SSweepInfo&& rhs); //转移赋值操作符
};

typedef std::vector<SSweepInfo> TVecSweepInfo;

//扫荡日志信息
struct SSweepItem
{
	UINT16 wTurn; //当前扫荡轮数
	NItemProt::TVecItemGenInfo vecItemGenInfo; //获得物品
	NItemProt::TVecResource vecResource; //获得资源

	SSweepItem();
	SSweepItem(UINT16 wTurn_, const NItemProt::TVecItemGenInfo& vecItemGenInfo_, const NItemProt::TVecResource& vecResource_);
#ifdef __GNUG__
	SSweepItem(const SSweepItem& src) = default; //默认拷贝构造函数
	SSweepItem& operator=(const SSweepItem& rhs) = default; //默认赋值操作符
#endif
	SSweepItem(SSweepItem&& src); //转移构造函数
	SSweepItem& operator=(SSweepItem&& rhs); //转移赋值操作符
};

typedef std::vector<SSweepItem> TVecSweepItem;

//客户段获取的扫荡信息
struct SGetSweepInfo
{
	UINT16 wDgnId; //扫荡副本实例
	UINT32 dwReserverTimer; //剩余时间
	UINT16 wCount; //剩余次数
	UINT16 wMaxCount; //总的扫荡次数
	TVecSweepItem vecSweepItem; //扫荡日志

	SGetSweepInfo();
	SGetSweepInfo(UINT16 wDgnId_, UINT32 dwReserverTimer_, UINT16 wCount_, UINT16 wMaxCount_, const TVecSweepItem& vecSweepItem_);
#ifdef __GNUG__
	SGetSweepInfo(const SGetSweepInfo& src) = default; //默认拷贝构造函数
	SGetSweepInfo& operator=(const SGetSweepInfo& rhs) = default; //默认赋值操作符
#endif
	SGetSweepInfo(SGetSweepInfo&& src); //转移构造函数
	SGetSweepInfo& operator=(SGetSweepInfo&& rhs); //转移赋值操作符
};

typedef std::vector<SGetSweepInfo> TVecGetSweepInfo;

//组队副本领奖记录
struct TeamAwardRecord
{
	UINT16 wDgnType; //副本模板
	UINT8 byAwardTimes; //今日领奖次数

	TeamAwardRecord();
	TeamAwardRecord(UINT16 wDgnType_, UINT8 byAwardTimes_);
};

typedef std::vector<TeamAwardRecord> TVecTeamAwardRecord;

//组队副本总领奖记录
struct TeamAwardAllRecord
{
	UINT8 byAwardTimesToday; //今日领奖次数
	TVecTeamAwardRecord vecDgn; //每个副本领奖次数

	TeamAwardAllRecord();
	TeamAwardAllRecord(UINT8 byAwardTimesToday_, const TVecTeamAwardRecord& vecDgn_);
#ifdef __GNUG__
	TeamAwardAllRecord(const TeamAwardAllRecord& src) = default; //默认拷贝构造函数
	TeamAwardAllRecord& operator=(const TeamAwardAllRecord& rhs) = default; //默认赋值操作符
#endif
	TeamAwardAllRecord(TeamAwardAllRecord&& src); //转移构造函数
	TeamAwardAllRecord& operator=(TeamAwardAllRecord&& rhs); //转移赋值操作符
};

typedef std::vector<TeamAwardAllRecord> TVecTeamAwardAllRecord;

/////////////////////以下为序列化函数/////////////////////
CInArchive& operator>>(CInArchive&, DgnSucCond&);
COutArchive& operator<<(COutArchive&, const DgnSucCond&);
CInArchive& operator>>(CInArchive&, DgnSucCond_Wrapper&);
COutArchive& operator<<(COutArchive&, const DgnSucCond_Wrapper&);
CInArchive& operator>>(CInArchive&, TVecSucCond&);
COutArchive& operator<<(COutArchive&, const TVecSucCond&);

CInArchive& operator>>(CInArchive&, SucMonster&);
COutArchive& operator<<(COutArchive&, const SucMonster&);
CInArchive& operator>>(CInArchive&, TVecSucMonster&);
COutArchive& operator<<(COutArchive&, const TVecSucMonster&);

CInArchive& operator>>(CInArchive&, SucGather&);
COutArchive& operator<<(COutArchive&, const SucGather&);
CInArchive& operator>>(CInArchive&, TVecSucGather&);
COutArchive& operator<<(COutArchive&, const TVecSucGather&);

CInArchive& operator>>(CInArchive&, SucTurns&);
COutArchive& operator<<(COutArchive&, const SucTurns&);
CInArchive& operator>>(CInArchive&, TVecSucTurns&);
COutArchive& operator<<(COutArchive&, const TVecSucTurns&);

CInArchive& operator>>(CInArchive&, SucInTimer&);
COutArchive& operator<<(COutArchive&, const SucInTimer&);
CInArchive& operator>>(CInArchive&, TVecSucInTimer&);
COutArchive& operator<<(COutArchive&, const TVecSucInTimer&);

CInArchive& operator>>(CInArchive&, SucMonsterInTimer&);
COutArchive& operator<<(COutArchive&, const SucMonsterInTimer&);
CInArchive& operator>>(CInArchive&, TVecSucMonsterInTimer&);
COutArchive& operator<<(COutArchive&, const TVecSucMonsterInTimer&);

CInArchive& operator>>(CInArchive&, SucGatherInTimer&);
COutArchive& operator<<(COutArchive&, const SucGatherInTimer&);
CInArchive& operator>>(CInArchive&, TVecSucGatherInTimer&);
COutArchive& operator<<(COutArchive&, const TVecSucGatherInTimer&);

CInArchive& operator>>(CInArchive&, SucFightWithMonsterMinTimes&);
COutArchive& operator<<(COutArchive&, const SucFightWithMonsterMinTimes&);
CInArchive& operator>>(CInArchive&, TVecSucFightWithMonsterMinTimes&);
COutArchive& operator<<(COutArchive&, const TVecSucFightWithMonsterMinTimes&);

CInArchive& operator>>(CInArchive&, SucArriveArea&);
COutArchive& operator<<(COutArchive&, const SucArriveArea&);
CInArchive& operator>>(CInArchive&, TVecSucArriveArea&);
COutArchive& operator<<(COutArchive&, const TVecSucArriveArea&);

CInArchive& operator>>(CInArchive&, MulCond&);
COutArchive& operator<<(COutArchive&, const MulCond&);

CInArchive& operator>>(CInArchive&, DgnStar&);
COutArchive& operator<<(COutArchive&, const DgnStar&);

CInArchive& operator>>(CInArchive&, DgnLiXian&);
COutArchive& operator<<(COutArchive&, const DgnLiXian&);

CInArchive& operator>>(CInArchive&, SSweepInfo&);
COutArchive& operator<<(COutArchive&, const SSweepInfo&);

CInArchive& operator>>(CInArchive&, SSweepItem&);
COutArchive& operator<<(COutArchive&, const SSweepItem&);

CInArchive& operator>>(CInArchive&, SGetSweepInfo&);
COutArchive& operator<<(COutArchive&, const SGetSweepInfo&);

CInArchive& operator>>(CInArchive&, TeamAwardRecord&);
COutArchive& operator<<(COutArchive&, const TeamAwardRecord&);

CInArchive& operator>>(CInArchive&, TeamAwardAllRecord&);
COutArchive& operator<<(COutArchive&, const TeamAwardAllRecord&);

#ifdef PROT_USE_XML
/////////////////////以下为XML转换函数/////////////////////
bool FromXML(TiXmlElement&, DgnSucCond&);
bool ToXML(const DgnSucCond&, TiXmlElement&);
bool SuperFromXML(TiXmlElement&, DgnSucCondPtr&);
bool SuperToXML(const DgnSucCond&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecSucCond&);
bool VectorToXML(const TVecSucCond&, TiXmlElement&);

bool FromXML(TiXmlElement&, SucMonster&);
bool ToXML(const SucMonster&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecSucMonster&);
bool VectorToXML(const TVecSucMonster&, TiXmlElement&);

bool FromXML(TiXmlElement&, SucGather&);
bool ToXML(const SucGather&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecSucGather&);
bool VectorToXML(const TVecSucGather&, TiXmlElement&);

bool FromXML(TiXmlElement&, SucTurns&);
bool ToXML(const SucTurns&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecSucTurns&);
bool VectorToXML(const TVecSucTurns&, TiXmlElement&);

bool FromXML(TiXmlElement&, SucInTimer&);
bool ToXML(const SucInTimer&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecSucInTimer&);
bool VectorToXML(const TVecSucInTimer&, TiXmlElement&);

bool FromXML(TiXmlElement&, SucMonsterInTimer&);
bool ToXML(const SucMonsterInTimer&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecSucMonsterInTimer&);
bool VectorToXML(const TVecSucMonsterInTimer&, TiXmlElement&);

bool FromXML(TiXmlElement&, SucGatherInTimer&);
bool ToXML(const SucGatherInTimer&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecSucGatherInTimer&);
bool VectorToXML(const TVecSucGatherInTimer&, TiXmlElement&);

bool FromXML(TiXmlElement&, SucFightWithMonsterMinTimes&);
bool ToXML(const SucFightWithMonsterMinTimes&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecSucFightWithMonsterMinTimes&);
bool VectorToXML(const TVecSucFightWithMonsterMinTimes&, TiXmlElement&);

bool FromXML(TiXmlElement&, SucArriveArea&);
bool ToXML(const SucArriveArea&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecSucArriveArea&);
bool VectorToXML(const TVecSucArriveArea&, TiXmlElement&);

bool FromXML(TiXmlElement&, MulCond&);
bool ToXML(const MulCond&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecMulCond&);
bool VectorToXML(const TVecMulCond&, TiXmlElement&);

bool FromXML(TiXmlElement&, DgnStar&);
bool ToXML(const DgnStar&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecDgnStar&);
bool VectorToXML(const TVecDgnStar&, TiXmlElement&);

bool FromXML(TiXmlElement&, DgnLiXian&);
bool ToXML(const DgnLiXian&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecDgnLiXian&);
bool VectorToXML(const TVecDgnLiXian&, TiXmlElement&);

bool FromXML(TiXmlElement&, SSweepInfo&);
bool ToXML(const SSweepInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecSweepInfo&);
bool VectorToXML(const TVecSweepInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SSweepItem&);
bool ToXML(const SSweepItem&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecSweepItem&);
bool VectorToXML(const TVecSweepItem&, TiXmlElement&);

bool FromXML(TiXmlElement&, SGetSweepInfo&);
bool ToXML(const SGetSweepInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecGetSweepInfo&);
bool VectorToXML(const TVecGetSweepInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, TeamAwardRecord&);
bool ToXML(const TeamAwardRecord&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecTeamAwardRecord&);
bool VectorToXML(const TVecTeamAwardRecord&, TiXmlElement&);

bool FromXML(TiXmlElement&, TeamAwardAllRecord&);
bool ToXML(const TeamAwardAllRecord&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecTeamAwardAllRecord&);
bool VectorToXML(const TVecTeamAwardAllRecord&, TiXmlElement&);
#endif //PROT_USE_XML

} //namespace NDungeonProt
