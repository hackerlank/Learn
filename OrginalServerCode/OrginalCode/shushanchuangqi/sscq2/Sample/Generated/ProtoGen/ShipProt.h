/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    ShipProt.h
//  Purpose:      元江金船协议
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

namespace NShipProt
{

/////////////////////以下为类型定义/////////////////////
//战斗原因
enum EShipBattleSource
{
	EBS_OPENSHIP, //开船
	EBS_ROBWITHOWER, //打劫与船主战斗
	EBS_ROBWITHDEFENSE, //打劫与护卫战斗
	EBS_GRABBYOWER, //返抢与船主战斗
	EBS_GRABBYDEFENSE, //返抢与护卫战斗
	EBS_CLOSESHIP //结束航运
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EShipBattleSource);
bool EnumStrToVal(const char*, EShipBattleSource&);
#endif //PROT_USE_XML

//金船操作结果
enum EShipResult
{
	EShip_Suc, //成功
	EShip_NoShip, //船不存在
	EShip_NoFlushShip, //你没有刷船
	EShip_NoFlushShip2, //邀请你的人没有刷船
	EShip_DeFenseIsAgree, //已经有人同意帮你护送
	EShip_DeFenseIsAgree2, //已经有人同意帮船主护送
	EShip_DriveHasShip, //你的船已开
	EShip_DriveHasShip2, //邀请你的人的船已开
	EShip_InviteDeFenseOffLine, //你邀请的人不在线
	EShip_InviteDeFenseOffLine2, //船主不在线
	EShip_DeFenseAgreeOther, //你邀请的人答应护送其他船
	EShip_DeFenseAgreeOther2, //你已答应护送其他船
	EShip_DeFenseOtherShip, //你邀请的人在护送其他船
	EShip_DeFenseOtherShip2, //你在护送其他船
	EShip_OtherDeFenseTimesOut, //你邀请的人护送次数用完
	EShip_OtherDeFenseTimesOut2, //你的护送次数用完
	EShip_DeFenseDisAgree, //邀请的人不同意帮你护送
	EShip_DeFenseDisAgree2, //邀请的人不同意帮你护送
	EShip_DeFenseErrFriend, //他不是你的护卫
	EShip_BuyOpenGoldLimit, //购买运船仙石不足
	EShip_BuyRobGoldLimit, //购买抢劫仙石不足
	EShip_RelushGoldLimit, //购买刷新次数仙石不足
	EShip_RelushShipUpLimit, //刷新次数用完
	EShip_DriveOverLimit, //今日开船到达上限
	EShip_DriveGoldLimit, //开船金币不足
	EShip_ROBOverLimit, //今日抢劫次数到达上限
	EShip_ROBOverShip, //这条船被抢劫次数到达上限
	EShip_ROBDone, //这条船你已经打劫
	EShip_ROBSelf, //这条船被你护卫或者是你的，不可抢劫
	EShip_GRABErrOwer, //这条船不是你的或者你不是护卫，不可返抢
	EShip_GRABErr, //返抢对手错误
	EShip_BattleCool, //战斗冷却
	EShip_FinishOneKeyNoGold, //一键完成运船金币不足
	EShip_GetShipOneKeyNoGold, //一键召唤Vip金币不足
	EShip_GetShipOneKeyNoVip, //一键召唤Vip等级不足
	EShip_OtherErr //其他错误
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EShipResult);
bool EnumStrToVal(const char*, EShipResult&);
#endif //PROT_USE_XML
const char* GetDescription(EShipResult);

//金船信息
struct PlayerShip
{
	UINT64 qwInsID; //金船唯一ID
	UINT64 qwOwer; //金船拥有者
	UINT32 dwOwerPoint; //金船拥有者战斗力
	UINT8 byOwerLevel; //拥有者等级
	UINT8 byOwerColor; //拥有者颜色
	UINT8 byChannel; //航道
	UINT16 wShipId; //金船模板
	UINT64 qwDefense; //护送者ID
	UINT32 dwDefensePoint; //护送者战斗力
	UINT8 byDefenseLevel; //护送者等级
	UINT8 byDefenseColor; //护送者颜色
	UINT64 qwRoBId1; //打劫者1
	UINT8 byRoB1Color; //打劫者1颜色
	UINT32 dwRoB1Point; //打劫者1战斗力
	UINT8 byRoB1Level; //打劫者1等级
	UINT64 qwRoBId2; //打劫者2
	UINT8 byRoB2Color; //打劫者2颜色
	UINT32 dwRoB2Point; //打劫者2战斗力
	UINT8 byRoB2Level; //打劫者2等级
	UINT64 qwRoBId3; //打劫者3
	UINT8 byRoB3Color; //打劫者3颜色
	UINT32 dwRoB3Point; //打劫者3战斗力
	UINT8 byRoB3Level; //打劫者3等级
	UINT32 dwBeginTimer; //开船时间
	UINT32 dwEndTimer; //结束时间
	UINT32 dwAwardRate; //奖励倍率

	PlayerShip();
};

typedef std::vector<PlayerShip> TVecPlayerShip;

//金船战报
struct ShipReport
{
	UINT64 qwInsID; //金船唯一ID
	EShipBattleSource eSource; //战斗原因
	UINT64 qwOwer; //金船拥有者
	UINT8 byOwerColor; //拥有者颜色
	UINT16 wShipId; //金船模板
	UINT64 qwDefense; //护送者ID
	UINT8 byDefenseColor; //护送者颜色
	UINT64 qwRoBId; //打劫者
	UINT8 byRoBColor; //打劫者颜色
	UINT64 qwBattleID; //战报ID
	UINT32 dwFinishTimer; //该船到达时间
	UINT32 dwTimer; //发生时间
	UINT8 byRobTimes; //被抢劫次数
	UINT32 dwAwardRate; //奖励倍率

	ShipReport();
};

typedef std::vector<ShipReport> TVecShipReport;

//金船客户端信息
struct PlayerShipForClient
{
	PlayerShip stInfo; //金船信息
	std::string strOwerName; //金船拥有者名字
	std::string strGuipName; //金船拥有者帮派
	std::string strDefenseName; //金船护卫名字
	std::string strRoBIdName1; //金船抢劫者1名字
	std::string strRoBIdName2; //金船抢劫者2名字
	std::string strRoBIdName3; //金船抢劫者3名字

	PlayerShipForClient();
	PlayerShipForClient(const PlayerShip& stInfo_, const std::string& strOwerName_, const std::string& strGuipName_, const std::string& strDefenseName_, const std::string& strRoBIdName1_, 
		const std::string& strRoBIdName2_, const std::string& strRoBIdName3_);
#ifdef __GNUG__
	PlayerShipForClient(const PlayerShipForClient& src) = default; //默认拷贝构造函数
	PlayerShipForClient& operator=(const PlayerShipForClient& rhs) = default; //默认赋值操作符
#endif
	PlayerShipForClient(PlayerShipForClient&& src); //转移构造函数
	PlayerShipForClient& operator=(PlayerShipForClient&& rhs); //转移赋值操作符
};

typedef std::vector<PlayerShipForClient> TVecPlayerShipForClient;

//玩家数据库信息
struct PlayerSelfShipData
{
	UINT32 dwBuyOpenShipTimes; //购买的运船次数
	UINT32 dwBuyRoBShipTimes; //购买的抢劫次数
	UINT32 dwBuyReflushShipTimes; //购买的刷新次数
	UINT16 wReflushShip; //刷出来的船
	UINT32 dwReflushShipTimer; //刷船的时间
	UINT64 qwInviteDefense; //邀请的护送者
	UINT32 dwInviteDefenseAgreeTime; //别人同意护送的时间
	UINT32 dwInviteDefensePoint; //护送者战斗力
	UINT8 byInviteDefenseLevel; //护送者等级
	UINT8 byInviteDefenseColor; //护送者颜色
	UINT64 qwAgreeDefenseShipOwer; //我同意护送的船
	UINT32 dwAgreeDefenseShipOwerTime; //我同意护送的时间

	PlayerSelfShipData();
};

typedef std::vector<PlayerSelfShipData> TVecPlayerSelfShipData;

//列表信息
struct PlayerShipForList
{
	UINT64 qwInsID; //金船唯一ID
	UINT64 qwOwer; //金船拥有者
	UINT16 wShipId; //船模板
	UINT8 byChannel; //航道
	UINT32 dwBeginTimer; //开船时间
	UINT32 dwEndTimer; //结束时间

	PlayerShipForList();
	PlayerShipForList(UINT64 qwInsID_, UINT64 qwOwer_, UINT16 wShipId_, UINT8 byChannel_, UINT32 dwBeginTimer_, 
		UINT32 dwEndTimer_);
};

typedef std::vector<PlayerShipForList> TVecPlayerShipForList;

//玩家信息
struct PlayerSelfView
{
	PlayerSelfShipData stData; //基本信息
	UINT32 dwRobTimes; //抢劫次数
	UINT8 byDefenseTimes; //护送次数
	UINT32 dwOpenShipTimes; //开船次数
	UINT32 dwReFluseTimes; //刷新次数
	UINT32 dwBuyRobTimes; //今日购买的抢劫次数
	UINT32 dwBuyOpenShipTimesToday; //今日购买的运船次数
	UINT32 dwBuyRlushShipTimesToday; //今日购买的刷新次数
	UINT32 dwFreezBattleTime; //金船战斗冷却时间
	UINT32 dwBeginTimer; //自己开船时间
	UINT32 dwEndTimer; //自己船结束时间
	UINT64 qwDefenseShip; //我护送的船
	UINT64 qwSelfShip; //我自己的船
	std::string strInviteDefenseName; //同意护送者名字

	PlayerSelfView();
#ifdef __GNUG__
	PlayerSelfView(const PlayerSelfView& src) = default; //默认拷贝构造函数
	PlayerSelfView& operator=(const PlayerSelfView& rhs) = default; //默认赋值操作符
#endif
	PlayerSelfView(PlayerSelfView&& src); //转移构造函数
	PlayerSelfView& operator=(PlayerSelfView&& rhs); //转移赋值操作符
};

typedef std::vector<PlayerSelfView> TVecPlayerSelfView;

//金船战报客户端信息
struct ShipReportForClient
{
	ShipReport stInfo; //战报信息
	NBattleGS::EBattleResult eResult; //
	std::string strOwerName; //金船拥有者名字
	std::string strDefenseName; //金船护卫名字
	std::string strRoBIdName; //金船抢劫者名字

	ShipReportForClient();
	ShipReportForClient(const ShipReport& stInfo_, NBattleGS::EBattleResult eResult_, const std::string& strOwerName_, const std::string& strDefenseName_, const std::string& strRoBIdName_);
#ifdef __GNUG__
	ShipReportForClient(const ShipReportForClient& src) = default; //默认拷贝构造函数
	ShipReportForClient& operator=(const ShipReportForClient& rhs) = default; //默认赋值操作符
#endif
	ShipReportForClient(ShipReportForClient&& src); //转移构造函数
	ShipReportForClient& operator=(ShipReportForClient&& rhs); //转移赋值操作符
};

typedef std::vector<ShipReportForClient> TVecShipReportForClient;

/////////////////////以下为序列化函数/////////////////////
CInArchive& operator>>(CInArchive&, PlayerShip&);
COutArchive& operator<<(COutArchive&, const PlayerShip&);

CInArchive& operator>>(CInArchive&, ShipReport&);
COutArchive& operator<<(COutArchive&, const ShipReport&);

CInArchive& operator>>(CInArchive&, PlayerShipForClient&);
COutArchive& operator<<(COutArchive&, const PlayerShipForClient&);

CInArchive& operator>>(CInArchive&, PlayerSelfShipData&);
COutArchive& operator<<(COutArchive&, const PlayerSelfShipData&);

CInArchive& operator>>(CInArchive&, PlayerShipForList&);
COutArchive& operator<<(COutArchive&, const PlayerShipForList&);

CInArchive& operator>>(CInArchive&, PlayerSelfView&);
COutArchive& operator<<(COutArchive&, const PlayerSelfView&);

CInArchive& operator>>(CInArchive&, ShipReportForClient&);
COutArchive& operator<<(COutArchive&, const ShipReportForClient&);

#ifdef PROT_USE_XML
/////////////////////以下为XML转换函数/////////////////////
bool FromXML(TiXmlElement&, PlayerShip&);
bool ToXML(const PlayerShip&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecPlayerShip&);
bool VectorToXML(const TVecPlayerShip&, TiXmlElement&);

bool FromXML(TiXmlElement&, ShipReport&);
bool ToXML(const ShipReport&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecShipReport&);
bool VectorToXML(const TVecShipReport&, TiXmlElement&);

bool FromXML(TiXmlElement&, PlayerShipForClient&);
bool ToXML(const PlayerShipForClient&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecPlayerShipForClient&);
bool VectorToXML(const TVecPlayerShipForClient&, TiXmlElement&);

bool FromXML(TiXmlElement&, PlayerSelfShipData&);
bool ToXML(const PlayerSelfShipData&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecPlayerSelfShipData&);
bool VectorToXML(const TVecPlayerSelfShipData&, TiXmlElement&);

bool FromXML(TiXmlElement&, PlayerShipForList&);
bool ToXML(const PlayerShipForList&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecPlayerShipForList&);
bool VectorToXML(const TVecPlayerShipForList&, TiXmlElement&);

bool FromXML(TiXmlElement&, PlayerSelfView&);
bool ToXML(const PlayerSelfView&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecPlayerSelfView&);
bool VectorToXML(const TVecPlayerSelfView&, TiXmlElement&);

bool FromXML(TiXmlElement&, ShipReportForClient&);
bool ToXML(const ShipReportForClient&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecShipReportForClient&);
bool VectorToXML(const TVecShipReportForClient&, TiXmlElement&);
#endif //PROT_USE_XML

} //namespace NShipProt
