/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    LevelPrize.h
//  Purpose:      等级奖励
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
#include "WonderActivityProt.h"

namespace NLevelPrize
{

/////////////////////以下为类型定义/////////////////////
//奖励状态信息
enum ELevelActStatus
{
	eLevleActStatus_Init = 0, //未完成
	eLevleActStatus_Finish, //完成
	eLevleActStatus_GetPrize, //已领取奖励
	eLevleActStatus_FullPack, //背包满
	eLevleActStatus_Success, //操作成功
	eLevleActStatus_Error //操作失败
};

#ifdef PROT_USE_XML
const char* EnumValToStr(ELevelActStatus);
bool EnumStrToVal(const char*, ELevelActStatus&);
#endif //PROT_USE_XML

//活动信息
enum EActState
{
	eActState_Init = 0, //未完成
	eActState_OnAdvance, //预告
	eActState_OnBegin, //开始
	eActState_OnEnd, //结束
	eActState_OnRetain //保留
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EActState);
bool EnumStrToVal(const char*, EActState&);
#endif //PROT_USE_XML

//奖励
struct SPrize
{
	UINT8 byIndex; //第几个奖
	ELevelActStatus eState; //第几个奖状态
	NItemProt::TVecItemGenInfo vecItem; //物品

	SPrize();
	SPrize(UINT8 byIndex_, ELevelActStatus eState_, const NItemProt::TVecItemGenInfo& vecItem_);
#ifdef __GNUG__
	SPrize(const SPrize& src) = default; //默认拷贝构造函数
	SPrize& operator=(const SPrize& rhs) = default; //默认赋值操作符
#endif
	SPrize(SPrize&& src); //转移构造函数
	SPrize& operator=(SPrize&& rhs); //转移赋值操作符
};

typedef std::vector<SPrize> TVecPrize;

//数据操作
struct SPrize2DB
{
	UINT64 qwRoleID; //玩家ID
	UINT16 wActID; //活动ID
	UINT16 wLevel; //奖励NO
	UINT16 wStatus; //奖励状态

	SPrize2DB();
	SPrize2DB(UINT64 qwRoleID_, UINT16 wActID_, UINT16 wLevel_, UINT16 wStatus_);
};

typedef std::vector<SPrize2DB> TVecPrize2DB;

//活动配置时间
struct STime
{
	UINT32 dwAdvTime; //活动预告时间
	UINT32 dwBeginTime; //活动开始时间
	UINT32 dwEndTime; //活动结束时间
	UINT32 dwRetainTime; //活动预留时间

	STime();
	STime(UINT32 dwAdvTime_, UINT32 dwBeginTime_, UINT32 dwEndTime_, UINT32 dwRetainTime_);
};

//奖励状态
struct SPrizeState
{
	UINT8 byIndex; //领奖
	ELevelActStatus eStatus; //奖励状态

	SPrizeState();
	SPrizeState(UINT8 byIndex_, ELevelActStatus eStatus_);
};

typedef std::vector<SPrizeState> TVecPrizeState;

/////////////////////以下为序列化函数/////////////////////
CInArchive& operator>>(CInArchive&, SPrize&);
COutArchive& operator<<(COutArchive&, const SPrize&);

CInArchive& operator>>(CInArchive&, SPrize2DB&);
COutArchive& operator<<(COutArchive&, const SPrize2DB&);

CInArchive& operator>>(CInArchive&, STime&);
COutArchive& operator<<(COutArchive&, const STime&);

CInArchive& operator>>(CInArchive&, SPrizeState&);
COutArchive& operator<<(COutArchive&, const SPrizeState&);

#ifdef PROT_USE_XML
/////////////////////以下为XML转换函数/////////////////////
bool FromXML(TiXmlElement&, SPrize&);
bool ToXML(const SPrize&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecPrize&);
bool VectorToXML(const TVecPrize&, TiXmlElement&);

bool FromXML(TiXmlElement&, SPrize2DB&);
bool ToXML(const SPrize2DB&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecPrize2DB&);
bool VectorToXML(const TVecPrize2DB&, TiXmlElement&);

bool FromXML(TiXmlElement&, STime&);
bool ToXML(const STime&, TiXmlElement&);

bool FromXML(TiXmlElement&, SPrizeState&);
bool ToXML(const SPrizeState&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecPrizeState&);
bool VectorToXML(const TVecPrizeState&, TiXmlElement&);
#endif //PROT_USE_XML

} //namespace NLevelPrize
