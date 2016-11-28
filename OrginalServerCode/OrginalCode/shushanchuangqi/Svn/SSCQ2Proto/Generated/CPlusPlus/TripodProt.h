/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    TripodProt.h
//  Purpose:      九疑鼎相关协议
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
#include "ArenaGS.h"
#include "ItemProt.h"
#include "ProtoCommon.h"

namespace NTripodProt
{

/////////////////////以下为类型定义/////////////////////
//九疑鼎操作结果
enum ETripodType
{
	eTripodSucc, //成功
	eTripodFailed, //失败
	eTripodCondIDErr, //激活条件不足
	eTripodItemErr, //道具不足
	eTripodNotFire, //未祈火
	eTripodNoEnoughCnt, //剩余祈火次数不足
	eTripodYuanqiNotFull, //元气值未满
	eTripodYuanqiFull, //元气值已满
	eTripodNotTime, //时间未到
	eTripodShanfengFull, //扇风次数已满
	eTripodHelpTimesFull, //协助次数已满
	eTripodNotHelp //不能协助
};

#ifdef PROT_USE_XML
const char* EnumValToStr(ETripodType);
bool EnumStrToVal(const char*, ETripodType&);
#endif //PROT_USE_XML

//九疑鼎日志类型
enum ETripodLogType
{
	eTripodLogNone = 0, //无效日志类型
	eTripodLogHelp, //成员日志
	eTripodLogMax //日志类型最大值
};

#ifdef PROT_USE_XML
const char* EnumValToStr(ETripodLogType);
bool EnumStrToVal(const char*, ETripodLogType&);
#endif //PROT_USE_XML

//玩家的九疑鼎数据
struct STripodInfo
{
	UINT8 byTripodID; //九疑鼎ID
	UINT8 byLevel; //九疑鼎等级
	UINT32 dwExp; //九疑鼎当前经验值
	UINT16 wFireID; //火种ID
	UINT8 byFireLvl; //火种等级(品质)
	UINT32 dwStartTime; //上一次结算时间
	UINT32 dwShanfengTime; //上一次扇风时间(为0未扇风)
	UINT32 dwSoul; //当前已结算的总元气值
	UINT32 dwLine; //产物加成系数（万分比）

	STripodInfo();
	STripodInfo(UINT8 byTripodID_, UINT8 byLevel_, UINT32 dwExp_, UINT16 wFireID_, UINT8 byFireLvl_, 
		UINT32 dwStartTime_, UINT32 dwShanfengTime_, UINT32 dwSoul_, UINT32 dwLine_);
};

typedef std::vector<STripodInfo> TVecTripodInfo;

//九疑鼎散仙协助
struct SFighterHelpInfo
{
	UINT16 wFighterID; //散仙ID
	UINT8 byPos; //协助位置(0,1)
	UINT8 byColor; //散仙协助时的品质
	UINT32 dwStartTime; //开始协助的时间

	SFighterHelpInfo();
	SFighterHelpInfo(UINT16 wFighterID_, UINT8 byPos_, UINT8 byColor_, UINT32 dwStartTime_);
};

typedef std::vector<SFighterHelpInfo> TVecFighterHelpInfo;

//九疑鼎玩家协助
struct SPlayerHelpInfo
{
	UINT64 qwRoleID; //协助者(玩家)ID
	UINT8 byPos; //协助位置(0,1,2)
	UINT8 byLevel; //玩家协助时的等级
	UINT32 dwStartTime; //开始协助的时间
	NArenaGS::SArenaFighter stPlayer; //玩家的基础信息(外观)
	NProtoCommon::TVecPlatformParam vecPlatforms; //平台信息

	SPlayerHelpInfo();
	SPlayerHelpInfo(UINT64 qwRoleID_, UINT8 byPos_, UINT8 byLevel_, UINT32 dwStartTime_, const NArenaGS::SArenaFighter& stPlayer_, 
		const NProtoCommon::TVecPlatformParam& vecPlatforms_);
#ifdef __GNUG__
	SPlayerHelpInfo(const SPlayerHelpInfo& src) = default; //默认拷贝构造函数
	SPlayerHelpInfo& operator=(const SPlayerHelpInfo& rhs) = default; //默认赋值操作符
#endif
	SPlayerHelpInfo(SPlayerHelpInfo&& src); //转移构造函数
	SPlayerHelpInfo& operator=(SPlayerHelpInfo&& rhs); //转移赋值操作符
};

typedef std::vector<SPlayerHelpInfo> TVecPlayerHelpInfo;

//九疑鼎的协助信息
struct STripodHelp
{
	UINT64 qwRoleID; //九疑鼎的所属玩家的ID
	TVecFighterHelpInfo vecFighterHelp; //散仙协助信息
	TVecPlayerHelpInfo vecPlayerHelp; //玩家协助信息

	STripodHelp();
	STripodHelp(UINT64 qwRoleID_, const TVecFighterHelpInfo& vecFighterHelp_, const TVecPlayerHelpInfo& vecPlayerHelp_);
#ifdef __GNUG__
	STripodHelp(const STripodHelp& src) = default; //默认拷贝构造函数
	STripodHelp& operator=(const STripodHelp& rhs) = default; //默认赋值操作符
#endif
	STripodHelp(STripodHelp&& src); //转移构造函数
	STripodHelp& operator=(STripodHelp&& rhs); //转移赋值操作符
};

typedef std::vector<STripodHelp> TVecTripodHelp;

//九疑鼎历史日志
struct STripodLog
{
	UINT64 qwRoleID; //九疑鼎的所属玩家的ID
	UINT16 wMsgID; //对应日志ID（详见Message）
	TVecINT64 vecParam; //整型变量
	TVecString vecString; //字符串型变量
	UINT32 dwTime; //日志时间

	STripodLog();
	STripodLog(UINT64 qwRoleID_, UINT16 wMsgID_, const TVecINT64& vecParam_, const TVecString& vecString_, UINT32 dwTime_);
};

typedef std::vector<STripodLog> TVecTripodLog;

//玩家九疑鼎信息
struct STripodData
{
	UINT64 qwRoleID; //玩家的ID
	NArenaGS::SArenaFighter stPlayer; //九疑鼎所属玩家的基础信息
	STripodHelp tripodHelpData; //玩家九疑鼎的协助数据
	TVecTripodInfo vecTripods; //玩家的所有九疑鼎数据
	TVecTripodLog vecTripodLog; //九疑鼎日志

	STripodData();
	STripodData(UINT64 qwRoleID_, const NArenaGS::SArenaFighter& stPlayer_, const STripodHelp& tripodHelpData_, const TVecTripodInfo& vecTripods_, const TVecTripodLog& vecTripodLog_);
#ifdef __GNUG__
	STripodData(const STripodData& src) = default; //默认拷贝构造函数
	STripodData& operator=(const STripodData& rhs) = default; //默认赋值操作符
#endif
	STripodData(STripodData&& src); //转移构造函数
	STripodData& operator=(STripodData&& rhs); //转移赋值操作符
};

typedef std::vector<STripodData> TVecTripodData;

//玩家的九疑鼎火种数据
struct SFireInfo
{
	UINT16 wFireID; //九疑鼎火种ID
	UINT32 dwSucceed; //火种祈火成功次数
	UINT32 dwRemain; //火种剩余祈火次数

	SFireInfo();
	SFireInfo(UINT16 wFireID_, UINT32 dwSucceed_, UINT32 dwRemain_);
};

typedef std::vector<SFireInfo> TVecFireInfo;

//玩家九疑鼎的扇火、协助状态
struct STripodStatus
{
	UINT64 qwRoleID; //玩家的ID
	UINT8 byShanfengst; //是否可以扇火(1是 0否)
	UINT8 byHelpst; //是否可以协助(1是 0否)

	STripodStatus();
	STripodStatus(UINT64 qwRoleID_, UINT8 byShanfengst_, UINT8 byHelpst_);
};

typedef std::vector<STripodStatus> TVecTripodStatus;

/////////////////////以下为序列化函数/////////////////////
CInArchive& operator>>(CInArchive&, STripodInfo&);
COutArchive& operator<<(COutArchive&, const STripodInfo&);

CInArchive& operator>>(CInArchive&, SFighterHelpInfo&);
COutArchive& operator<<(COutArchive&, const SFighterHelpInfo&);

CInArchive& operator>>(CInArchive&, SPlayerHelpInfo&);
COutArchive& operator<<(COutArchive&, const SPlayerHelpInfo&);

CInArchive& operator>>(CInArchive&, STripodHelp&);
COutArchive& operator<<(COutArchive&, const STripodHelp&);

CInArchive& operator>>(CInArchive&, STripodLog&);
COutArchive& operator<<(COutArchive&, const STripodLog&);

CInArchive& operator>>(CInArchive&, STripodData&);
COutArchive& operator<<(COutArchive&, const STripodData&);

CInArchive& operator>>(CInArchive&, SFireInfo&);
COutArchive& operator<<(COutArchive&, const SFireInfo&);

CInArchive& operator>>(CInArchive&, STripodStatus&);
COutArchive& operator<<(COutArchive&, const STripodStatus&);

#ifdef PROT_USE_XML
/////////////////////以下为XML转换函数/////////////////////
bool FromXML(TiXmlElement&, STripodInfo&);
bool ToXML(const STripodInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecTripodInfo&);
bool VectorToXML(const TVecTripodInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SFighterHelpInfo&);
bool ToXML(const SFighterHelpInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecFighterHelpInfo&);
bool VectorToXML(const TVecFighterHelpInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SPlayerHelpInfo&);
bool ToXML(const SPlayerHelpInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecPlayerHelpInfo&);
bool VectorToXML(const TVecPlayerHelpInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, STripodHelp&);
bool ToXML(const STripodHelp&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecTripodHelp&);
bool VectorToXML(const TVecTripodHelp&, TiXmlElement&);

bool FromXML(TiXmlElement&, STripodLog&);
bool ToXML(const STripodLog&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecTripodLog&);
bool VectorToXML(const TVecTripodLog&, TiXmlElement&);

bool FromXML(TiXmlElement&, STripodData&);
bool ToXML(const STripodData&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecTripodData&);
bool VectorToXML(const TVecTripodData&, TiXmlElement&);

bool FromXML(TiXmlElement&, SFireInfo&);
bool ToXML(const SFireInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecFireInfo&);
bool VectorToXML(const TVecFireInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, STripodStatus&);
bool ToXML(const STripodStatus&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecTripodStatus&);
bool VectorToXML(const TVecTripodStatus&, TiXmlElement&);
#endif //PROT_USE_XML

} //namespace NTripodProt
