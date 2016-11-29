/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    BattleArray.h
//  Purpose:      破阵
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

namespace NBattleArray
{

/////////////////////以下为类型定义/////////////////////
//阵状态
enum EBattleArrayStatus
{
	eBattleArrayStatus_Init, //初始状态
	eBattleArrayStatus_End, //已破阵
	eBattleArrayStatus_TakePrized //已领奖
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EBattleArrayStatus);
bool EnumStrToVal(const char*, EBattleArrayStatus&);
#endif //PROT_USE_XML

//破阵操作结果
enum EBattleArrayRet
{
	eBattleArrayRet_Sucess, //成功
	eBattleArrayRet_LevelLimit, //等级不够
	eBattleArrayRet_PreID, //前置阵未破
	eBattleArrayRet_PosLimit, //阵位只能一次
	eBattleArrayRet_AttackLimit, //攻击次数限制
	eBattleArrayRet_TotalAttackLimit, //总攻击次数一次
	eBattleArrayRet_ErrorCFG, //配置错误
	eBattleArrayRet_PreLevel, //阵图未解锁
	eBattleArrayRet_NoPass, //未破阵图
	eBattleArrayRet_TakePrized, //已经领过奖励
	eBattleArrayRet_PackError, //背包格子不够
	eBattleArrayRet_MoneyError, //钻石不够
	eBattleArrayRet_MaxBuyCnt, //超过最大购买次数
	eBattleArrayRet_AttackCd //攻击cd
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EBattleArrayRet);
bool EnumStrToVal(const char*, EBattleArrayRet&);
#endif //PROT_USE_XML

//获的物品的类型
enum EBattleArrayGain
{
	eBattleArrayGain_Attack, //攻击阵图
	eBattleArrayGain_Sweep //扫荡(自动破阵)
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EBattleArrayGain);
bool EnumStrToVal(const char*, EBattleArrayGain&);
#endif //PROT_USE_XML

//阵信息
struct SBattleArray
{
	UINT16 wBattleArrayID; //阵id
	UINT32 dwBattleArrayLevelID; //破阵进度(阵图id)
	EBattleArrayStatus eBattleArrayStatus; //阵状态

	SBattleArray();
	SBattleArray(UINT16 wBattleArrayID_, UINT32 dwBattleArrayLevelID_, EBattleArrayStatus eBattleArrayStatus_);
};

typedef std::vector<SBattleArray> TVecBattleArray;

//攻击阵图信息
struct SBattleArrayAttackCnt
{
	UINT32 dwBattleArrayLevelID; //阵图id
	UINT16 wCount; //次数
	UINT16 wMinTurn; //最小回合数

	SBattleArrayAttackCnt();
	SBattleArrayAttackCnt(UINT32 dwBattleArrayLevelID_, UINT16 wCount_, UINT16 wMinTurn_);
};

typedef std::vector<SBattleArrayAttackCnt> TVecBattleArrayAttackCnt;

/////////////////////以下为序列化函数/////////////////////
CInArchive& operator>>(CInArchive&, SBattleArray&);
COutArchive& operator<<(COutArchive&, const SBattleArray&);

CInArchive& operator>>(CInArchive&, SBattleArrayAttackCnt&);
COutArchive& operator<<(COutArchive&, const SBattleArrayAttackCnt&);

#ifdef PROT_USE_XML
/////////////////////以下为XML转换函数/////////////////////
bool FromXML(TiXmlElement&, SBattleArray&);
bool ToXML(const SBattleArray&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecBattleArray&);
bool VectorToXML(const TVecBattleArray&, TiXmlElement&);

bool FromXML(TiXmlElement&, SBattleArrayAttackCnt&);
bool ToXML(const SBattleArrayAttackCnt&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecBattleArrayAttackCnt&);
bool VectorToXML(const TVecBattleArrayAttackCnt&, TiXmlElement&);
#endif //PROT_USE_XML

} //namespace NBattleArray
