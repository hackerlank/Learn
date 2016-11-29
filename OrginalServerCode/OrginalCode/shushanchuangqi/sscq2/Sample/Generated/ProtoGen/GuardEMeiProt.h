/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    GuardEMeiProt.h
//  Purpose:      守卫峨眉协议
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

namespace NGuardEMeiProt
{

/////////////////////以下为类型定义/////////////////////
//操作结果
enum EGEMOptResult
{
	eGEMOptResultFailed, //失败
	eGEMOptResultSucc //成功
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EGEMOptResult);
bool EnumStrToVal(const char*, EGEMOptResult&);
#endif //PROT_USE_XML

//战斗类型
enum EGEMBattleType
{
	eGEMBattleTypeA, //播放战报战斗
	eGEMBattleTypeB //不播放战报战斗
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EGEMBattleType);
bool EnumStrToVal(const char*, EGEMBattleType&);
#endif //PROT_USE_XML

//战斗结果
enum EGEMBattleRet
{
	eGEMBattleFailed, //战斗失败
	eGEMBattleSucc //战斗成功
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EGEMBattleRet);
bool EnumStrToVal(const char*, EGEMBattleRet&);
#endif //PROT_USE_XML

//守卫峨眉参战散仙信息
struct SGEMBattleFighterInfo
{
	UINT32 dwFighterID; //将模版ID
	UINT8 byFighterLevel; //将等级
	UINT8 byFighterColour; //将颜色
	UINT32 dwFighterCurHP; //将当前血量
	UINT32 dwFighterMaxHP; //将最大血量
	UINT32 dwFighterCurAnima; //将当前灵气
	UINT32 dwFighterMaxAnima; //将最大灵气

	SGEMBattleFighterInfo();
	SGEMBattleFighterInfo(UINT32 dwFighterID_, UINT8 byFighterLevel_, UINT8 byFighterColour_, UINT32 dwFighterCurHP_, UINT32 dwFighterMaxHP_, 
		UINT32 dwFighterCurAnima_, UINT32 dwFighterMaxAnima_);
};

typedef std::vector<SGEMBattleFighterInfo> TVecGEMBattleFighterInfo;

//守卫峨眉奖励信息
struct SGEMAwardInfo
{
	UINT16 wItemID; //物品ID
	UINT32 dwCount; //堆叠数

	SGEMAwardInfo();
	SGEMAwardInfo(UINT16 wItemID_, UINT32 dwCount_);
};

typedef std::vector<SGEMAwardInfo> TVecGEMAwardInfo;

//守卫峨眉Buff信息
struct SGEMBuffInfo
{
	UINT32 dwBuffID; //BuffID
	UINT32 dwBuffNum; //Buff数量

	SGEMBuffInfo();
	SGEMBuffInfo(UINT32 dwBuffID_, UINT32 dwBuffNum_);
};

typedef std::vector<SGEMBuffInfo> TVecGEMBuffInfo;

//守卫峨眉准备战斗信息
struct SGEMPrepareBattleInfo
{
	UINT16 wCurProgress; //当前进度
	UINT32 dwMonsterID; //怪物ID
	UINT32 dwBattlePoint; //参战散仙战斗力
	TVecGEMBuffInfo vecGEMBuffInfo; //守卫峨眉Buff信息
	TVecGEMBattleFighterInfo vecGEMBattleFighterInfo; //守卫峨眉参战散仙信息

	SGEMPrepareBattleInfo();
	SGEMPrepareBattleInfo(UINT16 wCurProgress_, UINT32 dwMonsterID_, UINT32 dwBattlePoint_, const TVecGEMBuffInfo& vecGEMBuffInfo_, const TVecGEMBattleFighterInfo& vecGEMBattleFighterInfo_);
#ifdef __GNUG__
	SGEMPrepareBattleInfo(const SGEMPrepareBattleInfo& src) = default; //默认拷贝构造函数
	SGEMPrepareBattleInfo& operator=(const SGEMPrepareBattleInfo& rhs) = default; //默认赋值操作符
#endif
	SGEMPrepareBattleInfo(SGEMPrepareBattleInfo&& src); //转移构造函数
	SGEMPrepareBattleInfo& operator=(SGEMPrepareBattleInfo&& rhs); //转移赋值操作符
};

//守卫峨眉关卡信息
struct SGEMMissionInfo
{
	UINT16 wFreeEntryNumDay; //当日免费进入次数
	UINT16 wBuyEntryNumDay; //当日购买进入次数
	UINT16 wBuyEntryTotalNum; //购买进入总次数
	UINT64 qwIsGuardSucc; //每一位表示守卫是否成功（注：0未成功；1成功）
	UINT16 wCurMissionID; //正在进行的关卡ID（注：0表示没有）
	UINT8 byGEMType; //正在进行的类型（注：0表示没有；1：守卫；2：扫荡）
	UINT16 wCurProgress; //正在进行的关卡进度（注：0表示没有）

	SGEMMissionInfo();
	SGEMMissionInfo(UINT16 wFreeEntryNumDay_, UINT16 wBuyEntryNumDay_, UINT16 wBuyEntryTotalNum_, UINT64 qwIsGuardSucc_, UINT16 wCurMissionID_, 
		UINT8 byGEMType_, UINT16 wCurProgress_);
};

typedef std::vector<SGEMMissionInfo> TVecGEMMissionInfo;

//守卫峨眉DB信息
struct SGEMDBInfo
{
	UINT64 qwRoleID; //RoleID
	UINT16 wMissionID; //关卡ID
	UINT8 byGEMType; //正在进行的类型（注：0表示没有；1：守卫；2：扫荡）
	UINT16 wCurProgress; //当前进度
	UINT16 wGuardProgress; //守卫进度
	UINT32 dwGuardMonsterGroupID; //怪物组ID
	UINT32 dwSweepEndTime; //扫荡结束时间
	std::string strBuff; //守卫峨眉Buff

	SGEMDBInfo();
	SGEMDBInfo(UINT64 qwRoleID_, UINT16 wMissionID_, UINT8 byGEMType_, UINT16 wCurProgress_, UINT16 wGuardProgress_, 
		UINT32 dwGuardMonsterGroupID_, UINT32 dwSweepEndTime_, const std::string& strBuff_);
#ifdef __GNUG__
	SGEMDBInfo(const SGEMDBInfo& src) = default; //默认拷贝构造函数
	SGEMDBInfo& operator=(const SGEMDBInfo& rhs) = default; //默认赋值操作符
#endif
	SGEMDBInfo(SGEMDBInfo&& src); //转移构造函数
	SGEMDBInfo& operator=(SGEMDBInfo&& rhs); //转移赋值操作符
};

typedef std::vector<SGEMDBInfo> TVecGEMDBInfo;

/////////////////////以下为序列化函数/////////////////////
CInArchive& operator>>(CInArchive&, SGEMBattleFighterInfo&);
COutArchive& operator<<(COutArchive&, const SGEMBattleFighterInfo&);

CInArchive& operator>>(CInArchive&, SGEMAwardInfo&);
COutArchive& operator<<(COutArchive&, const SGEMAwardInfo&);

CInArchive& operator>>(CInArchive&, SGEMBuffInfo&);
COutArchive& operator<<(COutArchive&, const SGEMBuffInfo&);

CInArchive& operator>>(CInArchive&, SGEMPrepareBattleInfo&);
COutArchive& operator<<(COutArchive&, const SGEMPrepareBattleInfo&);

CInArchive& operator>>(CInArchive&, SGEMMissionInfo&);
COutArchive& operator<<(COutArchive&, const SGEMMissionInfo&);

CInArchive& operator>>(CInArchive&, SGEMDBInfo&);
COutArchive& operator<<(COutArchive&, const SGEMDBInfo&);

#ifdef PROT_USE_XML
/////////////////////以下为XML转换函数/////////////////////
bool FromXML(TiXmlElement&, SGEMBattleFighterInfo&);
bool ToXML(const SGEMBattleFighterInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecGEMBattleFighterInfo&);
bool VectorToXML(const TVecGEMBattleFighterInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SGEMAwardInfo&);
bool ToXML(const SGEMAwardInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecGEMAwardInfo&);
bool VectorToXML(const TVecGEMAwardInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SGEMBuffInfo&);
bool ToXML(const SGEMBuffInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecGEMBuffInfo&);
bool VectorToXML(const TVecGEMBuffInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SGEMPrepareBattleInfo&);
bool ToXML(const SGEMPrepareBattleInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SGEMMissionInfo&);
bool ToXML(const SGEMMissionInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecGEMMissionInfo&);
bool VectorToXML(const TVecGEMMissionInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SGEMDBInfo&);
bool ToXML(const SGEMDBInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecGEMDBInfo&);
bool VectorToXML(const TVecGEMDBInfo&, TiXmlElement&);
#endif //PROT_USE_XML

} //namespace NGuardEMeiProt
