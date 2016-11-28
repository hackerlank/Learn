/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    DemonTowerGS.h
//  Purpose:      锁妖塔
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

namespace NDemonTowerGS
{

/////////////////////以下为类型定义/////////////////////
//镇妖塔
enum EDemonTower
{
	eDemonTower_Sucess = 0, //成功
	eDemonTower_Error = 1, //锁妖塔错误码
	eDemonTower_NotPass = 2, //未通关层数，不能进入
	eDemonTower_NotInTower = 3, //不在镇妖塔中
	eDemonTower_Invalid_CFG = 4, //配置不存在
	eDemonTower_Invalid_FloorID = 5, //层数错误
	eDemonTower_Invalid_Positoin = 6, //镇守位置错误
	eDemonTower_Not_Empty_Positoin, //非空镇守位置
	eDemonTower_Empty_Positoin, //空位置没有玩家镇守
	eDemonTower_Empty_Prize, //无奖励或奖励已经领取
	eDemonTower_Invalid_PrizeType, //错误的领奖类型
	eDemonTower_Invalid_UserID, //玩家不在线
	eDemonTower_FightCD, //镇守位处在战斗状态中
	eDemonTower_LackMoney //钻石不足
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EDemonTower);
bool EnumStrToVal(const char*, EDemonTower&);
#endif //PROT_USE_XML
const char* GetDescription(EDemonTower);

//数据更新类型
enum EDemonTowerDB
{
	eDemonTowerDB_Add = 1, //添加
	eDemonTowerDB_Update = 2, //更新
	eDemonTowerDB_Delete = 3 //删除
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EDemonTowerDB);
bool EnumStrToVal(const char*, EDemonTowerDB&);
#endif //PROT_USE_XML
const char* GetDescription(EDemonTowerDB);

//领取奖励
enum EDemonTowerPrize
{
	eDemonTower_Prize_Fail = 1, //镇守失败奖励
	eDemonTower_Prize_Day, //镇守1天收益奖励
	eDemonTower_Prize_Seal //封印每天奖励(改成gmeserver领取)
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EDemonTowerPrize);
bool EnumStrToVal(const char*, EDemonTowerPrize&);
#endif //PROT_USE_XML
const char* GetDescription(EDemonTowerPrize);

//钱币列表
struct MoneyInfo
{
	UINT32 dwMoneyType; //钱币类型
	UINT32 dwMoneyValue; //钱数

	MoneyInfo();
	MoneyInfo(UINT32 dwMoneyType_, UINT32 dwMoneyValue_);
};

typedef std::vector<MoneyInfo> TVecMoneyInfo;

//镇守层的玩家信息
struct SDemonFloorPlayer
{
	UINT32 dwFloorID; //当前所在塔层
	UINT64 qwUserID; //uid
	std::string strRoleName; //角色名
	UINT8 bySex; //性别
	UINT16 byLevel; //等级
	UINT32 dwPower; //战斗力
	UINT32 dwGuardStartTime; //镇守开始时间
	UINT32 dwGuardReduceRate; //减弱比例(百分比1为%1)
	TVecMoneyInfo vecSoulPrize; //当前获得魄奖励

	SDemonFloorPlayer();
	SDemonFloorPlayer(UINT32 dwFloorID_, UINT64 qwUserID_, const std::string& strRoleName_, UINT8 bySex_, UINT16 byLevel_, 
		UINT32 dwPower_, UINT32 dwGuardStartTime_, UINT32 dwGuardReduceRate_, const TVecMoneyInfo& vecSoulPrize_);
#ifdef __GNUG__
	SDemonFloorPlayer(const SDemonFloorPlayer& src) = default; //默认拷贝构造函数
	SDemonFloorPlayer& operator=(const SDemonFloorPlayer& rhs) = default; //默认赋值操作符
#endif
	SDemonFloorPlayer(SDemonFloorPlayer&& src); //转移构造函数
	SDemonFloorPlayer& operator=(SDemonFloorPlayer&& rhs); //转移赋值操作符
};

typedef std::vector<SDemonFloorPlayer> TVecDemonFloorPlayer;

//镇守榜分页信息
struct SDemonFloorPage
{
	UINT16 wCurPage; //当前页码
	UINT16 wMaxPage; //最大页码
	TVecDemonFloorPlayer vecDemonFloorPlayer; //分页信息

	SDemonFloorPage();
	SDemonFloorPage(UINT16 wCurPage_, UINT16 wMaxPage_, const TVecDemonFloorPlayer& vecDemonFloorPlayer_);
#ifdef __GNUG__
	SDemonFloorPage(const SDemonFloorPage& src) = default; //默认拷贝构造函数
	SDemonFloorPage& operator=(const SDemonFloorPage& rhs) = default; //默认赋值操作符
#endif
	SDemonFloorPage(SDemonFloorPage&& src); //转移构造函数
	SDemonFloorPage& operator=(SDemonFloorPage&& rhs); //转移赋值操作符
};

//镇守的玩家信息列表
struct SDemonTowerPlayer
{
	UINT64 qwUserID; //uid
	UINT64 qwRoleID; //角色id
	std::string strRoleName; //角色名
	UINT8 bySex; //性别
	UINT16 byLevel; //等级
	UINT32 dwFloorID; //当前所在塔层
	UINT32 dwGuardFloorID; //镇守塔层
	UINT32 dwGuardPos; //镇守位置
	UINT32 dwGuardStartTime; //镇守开始时间
	UINT32 dwGuardEndTime; //镇守结束时间
	UINT32 dwGuardNextPrizeTime; //下次奖励时间
	UINT32 dwGuardNextReduceRateTime; //下次减弱时间
	UINT32 dwGuardGatherSpeed; //聚魂速度
	UINT32 dwGuardGatherSpeedEndTimer; //加速时间
	UINT32 dwGuardReduceRate; //元神灵力(百分比1为1%)
	UINT32 dwGuardNextAttackTime; //镇守可以攻击的时间
	UINT32 dwPower; //战斗力
	UINT32 dwBuyTime; //购买cd(服务器用)
	TVecMoneyInfo vecGatherSoulPrize; //当前聚集的魄奖励
	TVecMoneyInfo vecFailSoulPrize; //失败后的魄奖励
	TVecMoneyInfo vecDaySoulPrize; //7点结算的魄奖励
	UINT32 dwTotalTime; //镇守时间(服务器用)
	UINT32 dwFailFloorID; //失败镇守塔层
	UINT32 dwFailPos; //失败镇守位置
	UINT8 byColor; //角色颜色

	SDemonTowerPlayer();
#ifdef __GNUG__
	SDemonTowerPlayer(const SDemonTowerPlayer& src) = default; //默认拷贝构造函数
	SDemonTowerPlayer& operator=(const SDemonTowerPlayer& rhs) = default; //默认赋值操作符
#endif
	SDemonTowerPlayer(SDemonTowerPlayer&& src); //转移构造函数
	SDemonTowerPlayer& operator=(SDemonTowerPlayer&& rhs); //转移赋值操作符
};

typedef std::vector<SDemonTowerPlayer> TVecDemonTowerPlayer;

//镇守的玩家信息列表
struct GuardInfo
{
	UINT64 qwUserID; //uid
	UINT64 qwRoleID; //角色id
	UINT32 dwGuardPos; //封印位置
	UINT32 dwLastFightCD; //战斗cd 1s
	SDemonFloorPlayer oDemonFloorPlayer; //玩家信息

	GuardInfo();
	GuardInfo(UINT64 qwUserID_, UINT64 qwRoleID_, UINT32 dwGuardPos_, UINT32 dwLastFightCD_, const SDemonFloorPlayer& oDemonFloorPlayer_);
#ifdef __GNUG__
	GuardInfo(const GuardInfo& src) = default; //默认拷贝构造函数
	GuardInfo& operator=(const GuardInfo& rhs) = default; //默认赋值操作符
#endif
	GuardInfo(GuardInfo&& src); //转移构造函数
	GuardInfo& operator=(GuardInfo&& rhs); //转移赋值操作符
};

typedef std::vector<GuardInfo> TVecGuardInfo;

//通关信息
struct SDemonTowerKillMonster
{
	UINT64 qwUserID; //账号id
	std::string strName; //名字
	UINT8 byColor; //角色颜色
	UINT8 bySex; //性别
	UINT8 byCareer; //职业
	UINT8 byLevel; //等级
	UINT32 dwRounds; //通关回合数
	UINT32 dwBattlePoint; //战斗力
	UINT64 qwReportID; //战报

	SDemonTowerKillMonster();
	SDemonTowerKillMonster(UINT64 qwUserID_, const std::string& strName_, UINT8 byColor_, UINT8 bySex_, UINT8 byCareer_, 
		UINT8 byLevel_, UINT32 dwRounds_, UINT32 dwBattlePoint_, UINT64 qwReportID_);
#ifdef __GNUG__
	SDemonTowerKillMonster(const SDemonTowerKillMonster& src) = default; //默认拷贝构造函数
	SDemonTowerKillMonster& operator=(const SDemonTowerKillMonster& rhs) = default; //默认赋值操作符
#endif
	SDemonTowerKillMonster(SDemonTowerKillMonster&& src); //转移构造函数
	SDemonTowerKillMonster& operator=(SDemonTowerKillMonster&& rhs); //转移赋值操作符
};

typedef std::vector<SDemonTowerKillMonster> TVecDemonTowerKillMonster;

/////////////////////以下为序列化函数/////////////////////
CInArchive& operator>>(CInArchive&, MoneyInfo&);
COutArchive& operator<<(COutArchive&, const MoneyInfo&);

CInArchive& operator>>(CInArchive&, SDemonFloorPlayer&);
COutArchive& operator<<(COutArchive&, const SDemonFloorPlayer&);

CInArchive& operator>>(CInArchive&, SDemonFloorPage&);
COutArchive& operator<<(COutArchive&, const SDemonFloorPage&);

CInArchive& operator>>(CInArchive&, SDemonTowerPlayer&);
COutArchive& operator<<(COutArchive&, const SDemonTowerPlayer&);

CInArchive& operator>>(CInArchive&, GuardInfo&);
COutArchive& operator<<(COutArchive&, const GuardInfo&);

CInArchive& operator>>(CInArchive&, SDemonTowerKillMonster&);
COutArchive& operator<<(COutArchive&, const SDemonTowerKillMonster&);

#ifdef PROT_USE_XML
/////////////////////以下为XML转换函数/////////////////////
bool FromXML(TiXmlElement&, MoneyInfo&);
bool ToXML(const MoneyInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecMoneyInfo&);
bool VectorToXML(const TVecMoneyInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SDemonFloorPlayer&);
bool ToXML(const SDemonFloorPlayer&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecDemonFloorPlayer&);
bool VectorToXML(const TVecDemonFloorPlayer&, TiXmlElement&);

bool FromXML(TiXmlElement&, SDemonFloorPage&);
bool ToXML(const SDemonFloorPage&, TiXmlElement&);

bool FromXML(TiXmlElement&, SDemonTowerPlayer&);
bool ToXML(const SDemonTowerPlayer&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecDemonTowerPlayer&);
bool VectorToXML(const TVecDemonTowerPlayer&, TiXmlElement&);

bool FromXML(TiXmlElement&, GuardInfo&);
bool ToXML(const GuardInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecGuardInfo&);
bool VectorToXML(const TVecGuardInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SDemonTowerKillMonster&);
bool ToXML(const SDemonTowerKillMonster&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecDemonTowerKillMonster&);
bool VectorToXML(const TVecDemonTowerKillMonster&, TiXmlElement&);
#endif //PROT_USE_XML

} //namespace NDemonTowerGS
