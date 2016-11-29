/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    TreasureHuntProt.h
//  Purpose:      寻宝协议
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

namespace NTreasureHuntProt
{

/////////////////////以下为类型定义/////////////////////
//操作结果
enum ETHOptResult
{
	eTHOptResultFailed, //失败
	eTHOptResultSucc, //成功
	eTHMaxKillNumDay //今日已达到最大击杀次数
};

#ifdef PROT_USE_XML
const char* EnumValToStr(ETHOptResult);
bool EnumStrToVal(const char*, ETHOptResult&);
#endif //PROT_USE_XML

//寻宝状态
enum ETHStatus
{
	eTHNone, //无
	eTHProgress, //寻宝进行中
	eTHWaitGetAward //等待领取奖品
};

#ifdef PROT_USE_XML
const char* EnumValToStr(ETHStatus);
bool EnumStrToVal(const char*, ETHStatus&);
#endif //PROT_USE_XML

//寻宝开始/结束通知
enum ETHNotify
{
	eTHBegin, //开始
	eTHEnd //结束
};

#ifdef PROT_USE_XML
const char* EnumValToStr(ETHNotify);
bool EnumStrToVal(const char*, ETHNotify&);
#endif //PROT_USE_XML

//寻宝日志类型
enum ETHLogType
{
	eTHLogTypeA, //遇到怪物/BOSS (注：参数：NPCID)
	eTHLogTypeB, //击败怪物 (注：参数：NPCID)
	eTHLogTypeC, //获得银币 (注：参数：Silver)
	eTHLogTypeD, //获得修为 (注：参数：Pexp)
	eTHLogTypeE, //获得宝物 (注：参数：ItemNum)
	eTHLogTypeF, //击败BOSS,造成XX伤害 (注：参数：BOSSID, HPValue)
	eTHLogTypeG, //被BOSS击败,查看战报 (注：参数：BOSSID, HPValue, ReportID)
	eTHLogTypeH, //使用BUFF (注：参数：BUFFID)
	eTHLogTypeI, //对BOSS,造成XX伤害 (注：参数：BOSSID, HPValue)
	eTHLogTypeJ //获得心法残页数量 (注：参数：XFCYNum)
};

#ifdef PROT_USE_XML
const char* EnumValToStr(ETHLogType);
bool EnumStrToVal(const char*, ETHLogType&);
#endif //PROT_USE_XML

//寻宝buff信息
struct STHBuffInfo
{
	UINT8 byBuffID; //BuffID
	UINT8 byBuffNum; //今日已使用Buff次数
	UINT32 dwBuffCDTime; //Buff CD 时间

	STHBuffInfo();
	STHBuffInfo(UINT8 byBuffID_, UINT8 byBuffNum_, UINT32 dwBuffCDTime_);
};

typedef std::vector<STHBuffInfo> TVecTHBuffInfo;

//战斗结果
struct STHBattleResult
{
	UINT8 byCopyID; //副本ID
	UINT32 dwTotalTimes; //寻宝时间
	UINT32 dwCurBossHP; //当前BOSS血量
	UINT32 dwCurSilverNUm; //当前掉落银币数量
	UINT32 dwCurItemNum; //当前掉落物品数量
	UINT32 dwCurXFCYNum; //当前掉落心法残页数量

	STHBattleResult();
	STHBattleResult(UINT8 byCopyID_, UINT32 dwTotalTimes_, UINT32 dwCurBossHP_, UINT32 dwCurSilverNUm_, UINT32 dwCurItemNum_, 
		UINT32 dwCurXFCYNum_);
};

//寻宝奖励信息
struct STHAwardInfo
{
	UINT16 wItemID; //物品ID
	UINT32 dwCount; //堆叠数

	STHAwardInfo();
	STHAwardInfo(UINT16 wItemID_, UINT32 dwCount_);
};

typedef std::vector<STHAwardInfo> TVecTHAwardInfo;

//寻宝DB信息
struct STHDBInfo
{
	UINT64 qwRoleID; //RoleID
	UINT8 byCopyID; //副本ID
	UINT8 byStatus; //寻宝状态（1：正在进行；2：结束，等待领取奖品）
	UINT32 dwBossCurHP; //Boss当前血量
	UINT32 dwLastTime; //攻打上一波怪时间
	UINT32 dwTime; //寻宝累计时间
	UINT32 dwNum; //寻宝累计波数
	std::string strAward; //寻宝奖励

	STHDBInfo();
	STHDBInfo(UINT64 qwRoleID_, UINT8 byCopyID_, UINT8 byStatus_, UINT32 dwBossCurHP_, UINT32 dwLastTime_, 
		UINT32 dwTime_, UINT32 dwNum_, const std::string& strAward_);
#ifdef __GNUG__
	STHDBInfo(const STHDBInfo& src) = default; //默认拷贝构造函数
	STHDBInfo& operator=(const STHDBInfo& rhs) = default; //默认赋值操作符
#endif
	STHDBInfo(STHDBInfo&& src); //转移构造函数
	STHDBInfo& operator=(STHDBInfo&& rhs); //转移赋值操作符
};

typedef std::vector<STHDBInfo> TVecTHDBInfo;

/////////////////////以下为序列化函数/////////////////////
CInArchive& operator>>(CInArchive&, STHBuffInfo&);
COutArchive& operator<<(COutArchive&, const STHBuffInfo&);

CInArchive& operator>>(CInArchive&, STHBattleResult&);
COutArchive& operator<<(COutArchive&, const STHBattleResult&);

CInArchive& operator>>(CInArchive&, STHAwardInfo&);
COutArchive& operator<<(COutArchive&, const STHAwardInfo&);

CInArchive& operator>>(CInArchive&, STHDBInfo&);
COutArchive& operator<<(COutArchive&, const STHDBInfo&);

#ifdef PROT_USE_XML
/////////////////////以下为XML转换函数/////////////////////
bool FromXML(TiXmlElement&, STHBuffInfo&);
bool ToXML(const STHBuffInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecTHBuffInfo&);
bool VectorToXML(const TVecTHBuffInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, STHBattleResult&);
bool ToXML(const STHBattleResult&, TiXmlElement&);

bool FromXML(TiXmlElement&, STHAwardInfo&);
bool ToXML(const STHAwardInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecTHAwardInfo&);
bool VectorToXML(const TVecTHAwardInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, STHDBInfo&);
bool ToXML(const STHDBInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecTHDBInfo&);
bool VectorToXML(const TVecTHDBInfo&, TiXmlElement&);
#endif //PROT_USE_XML

} //namespace NTreasureHuntProt
