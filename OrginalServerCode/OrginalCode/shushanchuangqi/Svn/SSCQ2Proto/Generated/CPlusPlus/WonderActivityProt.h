/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    WonderActivityProt.h
//  Purpose:      精彩活动
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

namespace NWonderActivityProt
{

/////////////////////以下为类型定义/////////////////////
//操作结果
enum EWActResult
{
	eWActResult_none, //无此活动
	eWActResult_success, //操作成功
	eWActResult_error //操作失败
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EWActResult);
bool EnumStrToVal(const char*, EWActResult&);
#endif //PROT_USE_XML

//领奖操作结果
enum EGainResult
{
	eGainResult_none, //无此奖励
	eGainResult_success, //领奖成功
	eGainResult_alreadyGain, //奖励已领
	eGainResult_fullBag, //背包满
	eGainResult_notGet, //条件未达到
	eGainResult_error //操作失败
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EGainResult);
bool EnumStrToVal(const char*, EGainResult&);
#endif //PROT_USE_XML

//活动类型
enum EWActType
{
	eWActType_NONE, //无活动
	eWActType_RANKPOINT = 702, //战力排行榜
	eWActType_LEVELACT = 703, //全服等级奖励
	eWActType_HORSEACT = 704, //坐骑收集奖励
	eWActType_DUNGON = 705, //全服副本奖励
	eWActType_FIGHTER = 706, //全服散仙奖励
	eWActType_FORMATION = 707, //全服阵灵奖励
	eWActType_TRUMP = 708, //全服法宝奖励
	eWActType_RANKLEVEL = 709, //等级排行榜
	eWActType_RANKPET = 710, //阵灵排行榜
	eWActType_RANKFIGHTER = 711, //散仙排行榜
	eWActType_RANKARENA = 712, //斗剑排行榜
	eWActType_RANKGUILD = 713, //帮派排行榜
	eWActType_RANKTRUMP = 717, //法宝排行榜
	eWActType_QQCOIN = 715, //Q养成活动
	eWActType_BEAUTYACT = 716, //美女奖励
	eWActType_POINT = 718, //战力奖励
	eWActType_OpenBuy = 719, //开服购买礼包
	eWActType_MAX //活动最大值
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EWActType);
bool EnumStrToVal(const char*, EWActType&);
#endif //PROT_USE_XML

//活动状态
enum EWActState
{
	eWActState_Init, //初始状态
	eWActState_Advance, //活动预告
	eWActState_Begin, //活动开始
	eWActState_End, //活动结束
	eWActState_Retain //活动保留时间
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EWActState);
bool EnumStrToVal(const char*, EWActState&);
#endif //PROT_USE_XML

//活动奖励类型
enum EWActPrizeType
{
	eWActPrizeType_default, //全部奖励
	eWActPrizeType_first, //第一名玩家奖励
	eWActPrizeType_one, //一等奖
	eWActPrizeType_two, //二等奖
	eWActPrizeType_three, //三等奖
	eWActPrizeType_MAX //奖励最大值
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EWActPrizeType);
bool EnumStrToVal(const char*, EWActPrizeType&);
#endif //PROT_USE_XML

//奖励道具信息
struct SItemConfig
{
	UINT32 dwItemID; //道具ID
	UINT32 dwCount; //道具数量

	SItemConfig();
	SItemConfig(UINT32 dwItemID_, UINT32 dwCount_);
};

typedef std::vector<SItemConfig> TVecItemConfig;

//奖励道具信息
struct SPrizeConfig
{
	EWActPrizeType ePrizeType; //奖励类型
	TVecItemConfig vecItems; //道具

	SPrizeConfig();
	SPrizeConfig(EWActPrizeType ePrizeType_, const TVecItemConfig& vecItems_);
#ifdef __GNUG__
	SPrizeConfig(const SPrizeConfig& src) = default; //默认拷贝构造函数
	SPrizeConfig& operator=(const SPrizeConfig& rhs) = default; //默认赋值操作符
#endif
	SPrizeConfig(SPrizeConfig&& src); //转移构造函数
	SPrizeConfig& operator=(SPrizeConfig&& rhs); //转移赋值操作符
};

typedef std::vector<SPrizeConfig> TVecPrizeConfig;

//活动具体配置信息
struct SWActConfig
{
	UINT16 wWActID; //活动ID
	UINT16 wCfgID; //活动配置ID
	EWActPrizeType eWactPrizeType; //奖励类型
	TVecItemConfig vecItemConfig; //奖励道具列表

	SWActConfig();
	SWActConfig(UINT16 wWActID_, UINT16 wCfgID_, EWActPrizeType eWactPrizeType_, const TVecItemConfig& vecItemConfig_);
#ifdef __GNUG__
	SWActConfig(const SWActConfig& src) = default; //默认拷贝构造函数
	SWActConfig& operator=(const SWActConfig& rhs) = default; //默认赋值操作符
#endif
	SWActConfig(SWActConfig&& src); //转移构造函数
	SWActConfig& operator=(SWActConfig&& rhs); //转移赋值操作符
};

typedef std::vector<SWActConfig> TVecWActConfig;

//人物信息
struct SWActPlayerInfo
{
	UINT16 wWActID; //活动ID
	UINT16 wID; //散仙|阵灵ID
	UINT64 qwPlayerID; //玩家ID
	std::string strName; //玩家名字|帮主名
	NProtoCommon::ECareerType eCareer; //玩家职业
	NProtoCommon::ESexType eSex; //玩家性别
	std::string strName1; //帮派名
	UINT32 dwValue1; //参数1(战力，等级，散仙，阵灵，帮派）排名
	UINT32 dwValue2; //参数2(战力，等级，散仙战力，阵灵战力，帮派等级)

	SWActPlayerInfo();
	SWActPlayerInfo(UINT16 wWActID_, UINT16 wID_, UINT64 qwPlayerID_, const std::string& strName_, NProtoCommon::ECareerType eCareer_, 
		NProtoCommon::ESexType eSex_, const std::string& strName1_, UINT32 dwValue1_, UINT32 dwValue2_);
#ifdef __GNUG__
	SWActPlayerInfo(const SWActPlayerInfo& src) = default; //默认拷贝构造函数
	SWActPlayerInfo& operator=(const SWActPlayerInfo& rhs) = default; //默认赋值操作符
#endif
	SWActPlayerInfo(SWActPlayerInfo&& src); //转移构造函数
	SWActPlayerInfo& operator=(SWActPlayerInfo&& rhs); //转移赋值操作符
};

//活动时间信息
struct STime
{
	UINT16 wWActID; //活动ID
	UINT32 dwAdvTime; //活动预告时间
	UINT32 dwBeginTime; //活动开始时间
	UINT32 dwEndTime; //活动结束时间
	UINT32 dwRetainTime; //活动预留时间

	STime();
	STime(UINT16 wWActID_, UINT32 dwAdvTime_, UINT32 dwBeginTime_, UINT32 dwEndTime_, UINT32 dwRetainTime_);
};

typedef std::vector<STime> TVecTime;

//数据库信息
struct SWonderPrize2DB
{
	UINT64 qwRoleID; //玩家ID
	UINT16 wActID; //活动ID
	UINT16 wActType; //活动类型
	UINT32 wCond; //活动条件
	UINT8 byStatus; //活动状态

	SWonderPrize2DB();
	SWonderPrize2DB(UINT64 qwRoleID_, UINT16 wActID_, UINT16 wActType_, UINT32 wCond_, UINT8 byStatus_);
};

typedef std::vector<SWonderPrize2DB> TVecWonderPrize2DB;

//状态信息
struct SPrizeStatus
{
	UINT64 qwRoleID; //玩家ID
	UINT16 wActID; //活动ID
	TVecUINT8 vecStatus; //活动状态

	SPrizeStatus();
	SPrizeStatus(UINT64 qwRoleID_, UINT16 wActID_, const TVecUINT8& vecStatus_);
};

typedef std::vector<SPrizeStatus> TVecPrizeStatus;

//玩家在活动中的状态信息
struct SRoleStatus
{
	UINT32 wCond; //活动ID
	UINT32 dwMaxRole; //活动达到条件人数
	UINT32 dwCurRole; //活动目前人数
	UINT8 byStatus; //活动状态

	SRoleStatus();
	SRoleStatus(UINT32 wCond_, UINT32 dwMaxRole_, UINT32 dwCurRole_, UINT8 byStatus_);
};

typedef std::vector<SRoleStatus> TVecRoleStatus;

//玩家在活动中的保留值
struct SRetain
{
	UINT64 qwRoleID; //玩家ID
	std::string strName; //玩家名字
	UINT8 byCareer; //玩家职业
	UINT8 bySex; //性别
	UINT16 wActID; //活动ID
	UINT16 wID; //保留值（散仙ID,帮派ID,阵灵ID.....)
	std::string strGuildName; //帮派名字
	UINT16 wType; //保留类型
	UINT32 dwValue; //保留值
	UINT32 dwTime; //时间

	SRetain();
	SRetain(UINT64 qwRoleID_, const std::string& strName_, UINT8 byCareer_, UINT8 bySex_, UINT16 wActID_, 
		UINT16 wID_, const std::string& strGuildName_, UINT16 wType_, UINT32 dwValue_, UINT32 dwTime_);
#ifdef __GNUG__
	SRetain(const SRetain& src) = default; //默认拷贝构造函数
	SRetain& operator=(const SRetain& rhs) = default; //默认赋值操作符
#endif
	SRetain(SRetain&& src); //转移构造函数
	SRetain& operator=(SRetain&& rhs); //转移赋值操作符
};

typedef std::vector<SRetain> TVecRetain;

//玩家在所有活动中的信息
struct SRoleAllStatus
{
	UINT16 wActID; //活动ID
	TVecRoleStatus vecAllState; //状态

	SRoleAllStatus();
	SRoleAllStatus(UINT16 wActID_, const TVecRoleStatus& vecAllState_);
#ifdef __GNUG__
	SRoleAllStatus(const SRoleAllStatus& src) = default; //默认拷贝构造函数
	SRoleAllStatus& operator=(const SRoleAllStatus& rhs) = default; //默认赋值操作符
#endif
	SRoleAllStatus(SRoleAllStatus&& src); //转移构造函数
	SRoleAllStatus& operator=(SRoleAllStatus&& rhs); //转移赋值操作符
};

typedef std::vector<SRoleAllStatus> TVecRoleAllStatus;

//七星龙珠活动信息
struct SDragonBallAct
{
	UINT32 dwBeginTime; //活动开始时间
	UINT32 dwEndTime; //活动结束时间
	UINT32 dwRecharge; //今日充值仙石数
	UINT8 byIdx; //第几期活动
	UINT8 byDay; //今日完成的龙珠数
	UINT8 byAll; //完成的龙珠总数
	UINT8 byRemain; //今日之前剩余可点亮的龙珠数

	SDragonBallAct();
	SDragonBallAct(UINT32 dwBeginTime_, UINT32 dwEndTime_, UINT32 dwRecharge_, UINT8 byIdx_, UINT8 byDay_, 
		UINT8 byAll_, UINT8 byRemain_);
};

typedef std::vector<SDragonBallAct> TVecDragonBallAct;

//七日消费活动信息
struct SSevenConsumeAct
{
	UINT32 dwBeginTime; //活动开始时间
	UINT32 dwEndTime; //活动结束时间
	UINT32 dwConsume; //七日总消费仙石数
	UINT8 byInfo; //奖励领取状态信息(从低到高按位取,1已领取 0未领取)

	SSevenConsumeAct();
	SSevenConsumeAct(UINT32 dwBeginTime_, UINT32 dwEndTime_, UINT32 dwConsume_, UINT8 byInfo_);
};

typedef std::vector<SSevenConsumeAct> TVecSevenConsumeAct;

//Q币养成活动信息
struct SQQCoinActInfo
{
	UINT32 dwTime; //活动剩余时间
	UINT8 byLevel; //当前兑换的等级
	UINT32 dwMaxValue; //奖励最大值
	UINT32 dwCurValue; //当前值

	SQQCoinActInfo();
	SQQCoinActInfo(UINT32 dwTime_, UINT8 byLevel_, UINT32 dwMaxValue_, UINT32 dwCurValue_);
};

/////////////////////以下为序列化函数/////////////////////
CInArchive& operator>>(CInArchive&, SItemConfig&);
COutArchive& operator<<(COutArchive&, const SItemConfig&);

CInArchive& operator>>(CInArchive&, SPrizeConfig&);
COutArchive& operator<<(COutArchive&, const SPrizeConfig&);

CInArchive& operator>>(CInArchive&, SWActConfig&);
COutArchive& operator<<(COutArchive&, const SWActConfig&);

CInArchive& operator>>(CInArchive&, SWActPlayerInfo&);
COutArchive& operator<<(COutArchive&, const SWActPlayerInfo&);

CInArchive& operator>>(CInArchive&, STime&);
COutArchive& operator<<(COutArchive&, const STime&);

CInArchive& operator>>(CInArchive&, SWonderPrize2DB&);
COutArchive& operator<<(COutArchive&, const SWonderPrize2DB&);

CInArchive& operator>>(CInArchive&, SPrizeStatus&);
COutArchive& operator<<(COutArchive&, const SPrizeStatus&);

CInArchive& operator>>(CInArchive&, SRoleStatus&);
COutArchive& operator<<(COutArchive&, const SRoleStatus&);

CInArchive& operator>>(CInArchive&, SRetain&);
COutArchive& operator<<(COutArchive&, const SRetain&);

CInArchive& operator>>(CInArchive&, SRoleAllStatus&);
COutArchive& operator<<(COutArchive&, const SRoleAllStatus&);

CInArchive& operator>>(CInArchive&, SDragonBallAct&);
COutArchive& operator<<(COutArchive&, const SDragonBallAct&);

CInArchive& operator>>(CInArchive&, SSevenConsumeAct&);
COutArchive& operator<<(COutArchive&, const SSevenConsumeAct&);

CInArchive& operator>>(CInArchive&, SQQCoinActInfo&);
COutArchive& operator<<(COutArchive&, const SQQCoinActInfo&);

#ifdef PROT_USE_XML
/////////////////////以下为XML转换函数/////////////////////
bool FromXML(TiXmlElement&, SItemConfig&);
bool ToXML(const SItemConfig&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecItemConfig&);
bool VectorToXML(const TVecItemConfig&, TiXmlElement&);

bool FromXML(TiXmlElement&, SPrizeConfig&);
bool ToXML(const SPrizeConfig&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecPrizeConfig&);
bool VectorToXML(const TVecPrizeConfig&, TiXmlElement&);

bool FromXML(TiXmlElement&, SWActConfig&);
bool ToXML(const SWActConfig&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecWActConfig&);
bool VectorToXML(const TVecWActConfig&, TiXmlElement&);

bool FromXML(TiXmlElement&, SWActPlayerInfo&);
bool ToXML(const SWActPlayerInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, STime&);
bool ToXML(const STime&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecTime&);
bool VectorToXML(const TVecTime&, TiXmlElement&);

bool FromXML(TiXmlElement&, SWonderPrize2DB&);
bool ToXML(const SWonderPrize2DB&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecWonderPrize2DB&);
bool VectorToXML(const TVecWonderPrize2DB&, TiXmlElement&);

bool FromXML(TiXmlElement&, SPrizeStatus&);
bool ToXML(const SPrizeStatus&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecPrizeStatus&);
bool VectorToXML(const TVecPrizeStatus&, TiXmlElement&);

bool FromXML(TiXmlElement&, SRoleStatus&);
bool ToXML(const SRoleStatus&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecRoleStatus&);
bool VectorToXML(const TVecRoleStatus&, TiXmlElement&);

bool FromXML(TiXmlElement&, SRetain&);
bool ToXML(const SRetain&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecRetain&);
bool VectorToXML(const TVecRetain&, TiXmlElement&);

bool FromXML(TiXmlElement&, SRoleAllStatus&);
bool ToXML(const SRoleAllStatus&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecRoleAllStatus&);
bool VectorToXML(const TVecRoleAllStatus&, TiXmlElement&);

bool FromXML(TiXmlElement&, SDragonBallAct&);
bool ToXML(const SDragonBallAct&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecDragonBallAct&);
bool VectorToXML(const TVecDragonBallAct&, TiXmlElement&);

bool FromXML(TiXmlElement&, SSevenConsumeAct&);
bool ToXML(const SSevenConsumeAct&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecSevenConsumeAct&);
bool VectorToXML(const TVecSevenConsumeAct&, TiXmlElement&);

bool FromXML(TiXmlElement&, SQQCoinActInfo&);
bool ToXML(const SQQCoinActInfo&, TiXmlElement&);
#endif //PROT_USE_XML

} //namespace NWonderActivityProt
