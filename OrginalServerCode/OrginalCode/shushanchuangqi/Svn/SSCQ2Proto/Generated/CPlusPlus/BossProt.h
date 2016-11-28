/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    BossProt.h
//  Purpose:      BOSS相关协议
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

namespace NBossProt
{

/////////////////////以下为类型定义/////////////////////
//购买加持类型
enum EBossBuyType
{
	eGold, //金币购买
	eSliver //银币购买
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EBossBuyType);
bool EnumStrToVal(const char*, EBossBuyType&);
#endif //PROT_USE_XML

//boss奖励类型
enum EWorldBossPrize
{
	eWorldBossPrizeTop = 1, //排名奖励
	eWorldBossPrizeDamage, //伤害奖励
	eWorldBossPrizeRandom, //幸运奖励
	eWorldBossPrizeNPC, //参与奖励
	eWorldBossPrizeKillBoss, //击杀世界boss奖励
	eWorldBossPrizeBossHP //伤害boss百分比血量奖励
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EWorldBossPrize);
bool EnumStrToVal(const char*, EWorldBossPrize&);
#endif //PROT_USE_XML

//排行帮信息
struct SPlayerInfo
{
	UINT32 dwNo; //名次
	UINT64 qwUserID; //uid
	std::string strUserName; //玩家名字
	UINT32 dwDamageHP; //伤害的总血量
	UINT32 dwBossMaxHP; //Boss的总血量

	SPlayerInfo();
	SPlayerInfo(UINT32 dwNo_, UINT64 qwUserID_, const std::string& strUserName_, UINT32 dwDamageHP_, UINT32 dwBossMaxHP_);
#ifdef __GNUG__
	SPlayerInfo(const SPlayerInfo& src) = default; //默认拷贝构造函数
	SPlayerInfo& operator=(const SPlayerInfo& rhs) = default; //默认赋值操作符
#endif
	SPlayerInfo(SPlayerInfo&& src); //转移构造函数
	SPlayerInfo& operator=(SPlayerInfo&& rhs); //转移赋值操作符
};

typedef std::vector<SPlayerInfo> TVecPlayerInfo;

//货币列表
struct SPrizeMoneyInfo
{
	UINT32 dwMoneyType; //货币类型
	UINT32 dwMoneyValue; //货币值

	SPrizeMoneyInfo();
	SPrizeMoneyInfo(UINT32 dwMoneyType_, UINT32 dwMoneyValue_);
};

typedef std::vector<SPrizeMoneyInfo> TVecPrizeMoneyInfo;

//货币列表
struct SPrizeIteminfo
{
	UINT32 dwItemID; //物品id
	UINT32 dwItemCount; //物品数量

	SPrizeIteminfo();
	SPrizeIteminfo(UINT32 dwItemID_, UINT32 dwItemCount_);
};

typedef std::vector<SPrizeIteminfo> TVecPrizeItemInfo;

//排行帮信息
struct SPlayerPrize
{
	UINT8 dwPrizeType; //奖励类型
	TVecPrizeMoneyInfo vecPrizeMoneyInfo; //货币奖励
	TVecPrizeItemInfo vecPrizeItemInfo; //物品奖励

	SPlayerPrize();
	SPlayerPrize(UINT8 dwPrizeType_, const TVecPrizeMoneyInfo& vecPrizeMoneyInfo_, const TVecPrizeItemInfo& vecPrizeItemInfo_);
#ifdef __GNUG__
	SPlayerPrize(const SPlayerPrize& src) = default; //默认拷贝构造函数
	SPlayerPrize& operator=(const SPlayerPrize& rhs) = default; //默认赋值操作符
#endif
	SPlayerPrize(SPlayerPrize&& src); //转移构造函数
	SPlayerPrize& operator=(SPlayerPrize&& rhs); //转移赋值操作符
};

typedef std::vector<SPlayerPrize> TVecPlayerPrize;

/////////////////////以下为序列化函数/////////////////////
CInArchive& operator>>(CInArchive&, SPlayerInfo&);
COutArchive& operator<<(COutArchive&, const SPlayerInfo&);

CInArchive& operator>>(CInArchive&, SPrizeMoneyInfo&);
COutArchive& operator<<(COutArchive&, const SPrizeMoneyInfo&);

CInArchive& operator>>(CInArchive&, SPrizeIteminfo&);
COutArchive& operator<<(COutArchive&, const SPrizeIteminfo&);

CInArchive& operator>>(CInArchive&, SPlayerPrize&);
COutArchive& operator<<(COutArchive&, const SPlayerPrize&);

#ifdef PROT_USE_XML
/////////////////////以下为XML转换函数/////////////////////
bool FromXML(TiXmlElement&, SPlayerInfo&);
bool ToXML(const SPlayerInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecPlayerInfo&);
bool VectorToXML(const TVecPlayerInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SPrizeMoneyInfo&);
bool ToXML(const SPrizeMoneyInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecPrizeMoneyInfo&);
bool VectorToXML(const TVecPrizeMoneyInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SPrizeIteminfo&);
bool ToXML(const SPrizeIteminfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecPrizeItemInfo&);
bool VectorToXML(const TVecPrizeItemInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SPlayerPrize&);
bool ToXML(const SPlayerPrize&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecPlayerPrize&);
bool VectorToXML(const TVecPlayerPrize&, TiXmlElement&);
#endif //PROT_USE_XML

} //namespace NBossProt
