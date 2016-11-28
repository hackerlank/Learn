/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    ArenaGS.h
//  Purpose:      竞技场协议
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

namespace NArenaGS
{

/////////////////////以下为类型定义/////////////////////
//竞技等级
enum EArenaLevel
{
	EArenaLevel_NONE, //无等级
	EArenaLevel_IRON, //黑铁
	EArenaLevel_COPPER, //青铜
	EArenaLevel_SILVER, //白银
	EArenaLevel_GOLD, //黄金
	EArenaLevel_DIAMOND, //钻石
	EArenaLevel_END //最大值
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EArenaLevel);
bool EnumStrToVal(const char*, EArenaLevel&);
#endif //PROT_USE_XML

//竞技场操作结果
enum EArenaResult
{
	EArenaR_Suc, //成功
	EArenaR_NoEnter, //没有参加斗剑
	EArenaR_CDTime, //正在冷却
	EArenaR_NoChanllengeTimes, //挑战次数用完
	EArenaR_BuyTimesChanllengeTimes, //购买挑战次数已达上限
	EArenaR_LackMoney, //钱钱不够
	EArenaR_EnemyNoExist, //挑战目标不存在
	EArenaR_EnemyTimeOut, //挑战目标已过期
	EArenaR_EnemyIsSuc, //挑战目标已胜利
	EArenaR_NoReward, //没有奖励可领取
	EArenaR_RewardHasGet, //奖励已经领取
	EArenaR_PackageFull, //包裹满了
	EArenaR_AwardTimeOut, //奖励已过期
	EArenaR_WirShipOverTimes, //膜拜次数已达上限
	EArenaR_WirShipPlayerOverTimer, //膜拜对象已过期
	EArenaR_BuyTimesMax, //累计购买次数已达上限
	EArenaR_VIPLevel, //御剑等级不足
	EArenaR_LadderNOOpen, //天梯未开启
	EArenaR_LadderTimesLimit, //天梯挑战次数不足
	EArenaR_LadderAwardHasGet, //天梯挑战奖励已领
	EArenaR_LadderRankErr, //排名验证错误
	EArenaR_LadderRankLimit, //挑战资格验证错误
	EArenaR_ArenaNoOpen, //斗剑功能未开放
	EArenaR_ArenaTimesLimit, //历练挑战次数不足
	EArenaR_ArenaAwardHasGet, //历练挑战奖励已领
	EArenaR_LadderTimesZero, //天梯挑战次数用完
	EArenaR_LadderBuyTimesUp, //天梯挑战购买次数到达上限
	EArenaR_OtherErr //其他错误
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EArenaResult);
bool EnumStrToVal(const char*, EArenaResult&);
#endif //PROT_USE_XML

//奖励包类型
enum EArenaAwardType
{
	Type_NONE, //无定义
	Type_Level, //段位包
	Type_Rank, //排名包
	Type_LadderRank //天梯排名包
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EArenaAwardType);
bool EnumStrToVal(const char*, EArenaAwardType&);
#endif //PROT_USE_XML

//机器人排名信息
struct SLadderRobot
{
	UINT16 wMonsterID; //机器人ID
	UINT16 wRank; //机器人排名

	SLadderRobot();
	SLadderRobot(UINT16 wMonsterID_, UINT16 wRank_);
};

typedef std::vector<SLadderRobot> TVecLadderRobot;

//玩家奖励信息
struct SArenaAward
{
	EArenaAwardType eType; //奖励包类型
	UINT8 byDraw; //0,表示未领取；1，表示已领取
	UINT32 dwDrawID; //掉落包ID

	SArenaAward();
	SArenaAward(EArenaAwardType eType_, UINT8 byDraw_, UINT32 dwDrawID_);
};

typedef std::vector<SArenaAward> TVecArenaAward;

//竞技场玩家信息
struct SArenaFighter
{
	std::string strName; //名字
	UINT16 wLevel; //等级
	NBattleGS::SPlayerFeature stAppear; //外观

	SArenaFighter();
	SArenaFighter(const std::string& strName_, UINT16 wLevel_, const NBattleGS::SPlayerFeature& stAppear_);
#ifdef __GNUG__
	SArenaFighter(const SArenaFighter& src) = default; //默认拷贝构造函数
	SArenaFighter& operator=(const SArenaFighter& rhs) = default; //默认赋值操作符
#endif
	SArenaFighter(SArenaFighter&& src); //转移构造函数
	SArenaFighter& operator=(SArenaFighter&& rhs); //转移赋值操作符
};

typedef std::vector<SArenaFighter> TVecArenaFighter;

//玩家刷对手信息
struct SFlushFighter
{
	UINT8 bySuc; //0,表示未战胜；1，表示已击败
	UINT64 qwFighterID; //对手ID,小于65535为怪物

	SFlushFighter();
	SFlushFighter(UINT8 bySuc_, UINT64 qwFighterID_);
};

typedef std::vector<SFlushFighter> TVecFlushFither;

//竞技场玩家基本信息
struct SArenaPlayerBaseData
{
	UINT32 dwRanking; //同积分序号
	UINT32 dwScore; //积分
	UINT32 dwLadderRank; //天梯排名0表示天梯功未开启，10000表示天梯功能已开启未挑机器人，9999表示已挑战机器人
	EArenaLevel eLevel; //竞技等级
	UINT32 dwLastFlushTime; //最近客户端刷新时间
	UINT32 dwLastRank; //最近结算排名
	EArenaLevel eLastLevel; //最近结算之前段位
	UINT32 dwFighterPower; //战斗力
	UINT8 byQuality; //品质
	UINT8 byVIPLevel; //VIP等级
	UINT32 dwLastLadderRank; //最近结算排名

	SArenaPlayerBaseData();
};

typedef std::vector<SArenaPlayerBaseData> TVecArenaPlayerBaseData;

//竞技场玩家信息，要进数据库的总信息
struct SArenaPlayerData
{
	UINT64 qwRoleID; //玩家ID
	SArenaFighter stFighter; //角色基本信息
	SArenaPlayerBaseData stBaseData; //基本竞技场信息

	SArenaPlayerData();
	SArenaPlayerData(UINT64 qwRoleID_, const SArenaFighter& stFighter_, const SArenaPlayerBaseData& stBaseData_);
};

typedef std::vector<SArenaPlayerData> TVecArenaPlayerData;

//竞技场更新信息
struct SArenaPlayerBaseDataUpdate
{
	UINT64 qwRoleID; //玩家ID
	SArenaPlayerBaseData stBaseData; //基本竞技场信息

	SArenaPlayerBaseDataUpdate();
	SArenaPlayerBaseDataUpdate(UINT64 qwRoleID_, const SArenaPlayerBaseData& stBaseData_);
};

typedef std::vector<SArenaPlayerBaseDataUpdate> TVecArenaPlayerBaseDataUpdate;

//客户端竞技场的对手
struct SFlushFitherForClient
{
	SFlushFighter stFlushFighter; //id，小于65535为机器人，读怪物列表
	UINT32 wGroup; //
	EArenaLevel eLevel; //段位,无段位表示没有加入竞技场
	SArenaFighter stFighter; //其他属性
	UINT32 dwFighterPower; //战斗力
	UINT32 dwLadderRank; //天梯排名
	UINT32 dwArenaRank; //历练排名

	SFlushFitherForClient();
	SFlushFitherForClient(const SFlushFighter& stFlushFighter_, UINT32 wGroup_, EArenaLevel eLevel_, const SArenaFighter& stFighter_, UINT32 dwFighterPower_, 
		UINT32 dwLadderRank_, UINT32 dwArenaRank_);
#ifdef __GNUG__
	SFlushFitherForClient(const SFlushFitherForClient& src) = default; //默认拷贝构造函数
	SFlushFitherForClient& operator=(const SFlushFitherForClient& rhs) = default; //默认赋值操作符
#endif
	SFlushFitherForClient(SFlushFitherForClient&& src); //转移构造函数
	SFlushFitherForClient& operator=(SFlushFitherForClient&& rhs); //转移赋值操作符
};

typedef std::vector<SFlushFitherForClient> TVecSFlushFitherForClient;

//战报
struct SLadderReport
{
	UINT64 qwBattleID; //战报ID
	UINT64 qwEmemyID; //对手ID
	std::string strName; //对手名字
	UINT32 dwMonsterId; //对手是机器人,机器人ID
	UINT8 byAttack; //0,表示挑战别人，1表示别人挑战自己
	UINT8 bySuc; //0,自己失败，1，自己胜利
	UINT32 dwPreRank; //挑战之前的排名
	UINT32 dwNowRank; //挑战之后的排名
	UINT32 dwTimer; //战报时间

	SLadderReport();
	SLadderReport(UINT64 qwBattleID_, UINT64 qwEmemyID_, const std::string& strName_, UINT32 dwMonsterId_, UINT8 byAttack_, 
		UINT8 bySuc_, UINT32 dwPreRank_, UINT32 dwNowRank_, UINT32 dwTimer_);
#ifdef __GNUG__
	SLadderReport(const SLadderReport& src) = default; //默认拷贝构造函数
	SLadderReport& operator=(const SLadderReport& rhs) = default; //默认赋值操作符
#endif
	SLadderReport(SLadderReport&& src); //转移构造函数
	SLadderReport& operator=(SLadderReport&& rhs); //转移赋值操作符
};

typedef std::vector<SLadderReport> TVecLadderReport;

//排行信息
struct SArenaRank2Client
{
	UINT64 qwRoleID; //ID
	UINT32 dwRank; //名次
	UINT32 dwScore; //积分
	SArenaFighter stFighter; //其它信息
	UINT32 dwFighterPower; //战斗力
	UINT8 byQuality; //品质
	UINT8 byVIPLevel; //品质
	UINT32 dwLadderRank; //天梯排名

	SArenaRank2Client();
	SArenaRank2Client(UINT64 qwRoleID_, UINT32 dwRank_, UINT32 dwScore_, const SArenaFighter& stFighter_, UINT32 dwFighterPower_, 
		UINT8 byQuality_, UINT8 byVIPLevel_, UINT32 dwLadderRank_);
#ifdef __GNUG__
	SArenaRank2Client(const SArenaRank2Client& src) = default; //默认拷贝构造函数
	SArenaRank2Client& operator=(const SArenaRank2Client& rhs) = default; //默认赋值操作符
#endif
	SArenaRank2Client(SArenaRank2Client&& src); //转移构造函数
	SArenaRank2Client& operator=(SArenaRank2Client&& rhs); //转移赋值操作符
};

typedef std::vector<SArenaRank2Client> TVecArenaRank2Client;

//竞技场玩家基本信息，也是发给前端用的信息
struct SArenaPlayerBaseData2Client
{
	UINT32 dwRanking; //本段位排名
	UINT32 dwScore; //积分
	EArenaLevel eLevel; //段位
	UINT32 dwTotalSize; //本段位总人数
	EArenaLevel ePreLevel; //前次结算段位
	UINT32 dwPreRank; //前次结算排名
	TVecArenaAward vecAwards; //奖励包状态
	UINT32 dwArenaCDTime; //历练冷却到期时间戳
	UINT32 dwLadderCDTime; //天梯冷却到期时间戳
	UINT16 wChallenge; //当前挑战次数，每天0点清0
	UINT16 wChallengeBuyTimes; //购买的挑战次数
	UINT16 wSelfReflush; //当前购买刷新次数
	UINT16 wSelfFreeReflush; //当前VIP免费刷新次数
	UINT8 byArenaWirship; //膜拜次数
	UINT32 dwLastLadderRank; //上次结算天梯排名，0表示排名
	UINT32 dwMinLadderRank; //天梯最好排名,0表示无排名
	TVecSFlushFitherForClient vecFlushFigter; //最近刷的对手
	TVecArenaRank2Client vecWirshipFigter; //膜拜对象列表
	UINT32 dwFighterPower; //战斗力
	UINT32 dwLadderRank; //天梯排名，0表示未参与天梯，9999表示已经与机器战斗，但是不计入排名，否者为真实排名
	UINT16 wLadderChallenge; //天梯挑战次数
	UINT32 dwArenaAward; //历练挑战奖励，天梯挑战奖励领取状况，右到左1位历练，2位天梯
	UINT32 dwLadderBuyTimes; //购买的天梯挑战次数
	UINT32 dwLadderBuyTimesToday; //今日购买的天梯挑战次数

	SArenaPlayerBaseData2Client();
#ifdef __GNUG__
	SArenaPlayerBaseData2Client(const SArenaPlayerBaseData2Client& src) = default; //默认拷贝构造函数
	SArenaPlayerBaseData2Client& operator=(const SArenaPlayerBaseData2Client& rhs) = default; //默认赋值操作符
#endif
	SArenaPlayerBaseData2Client(SArenaPlayerBaseData2Client&& src); //转移构造函数
	SArenaPlayerBaseData2Client& operator=(SArenaPlayerBaseData2Client&& rhs); //转移赋值操作符
};

typedef std::vector<SArenaPlayerBaseData2Client> TVecArenaPlayerBaseData2Client;

/////////////////////以下为序列化函数/////////////////////
CInArchive& operator>>(CInArchive&, SLadderRobot&);
COutArchive& operator<<(COutArchive&, const SLadderRobot&);

CInArchive& operator>>(CInArchive&, SArenaAward&);
COutArchive& operator<<(COutArchive&, const SArenaAward&);

CInArchive& operator>>(CInArchive&, SArenaFighter&);
COutArchive& operator<<(COutArchive&, const SArenaFighter&);

CInArchive& operator>>(CInArchive&, SFlushFighter&);
COutArchive& operator<<(COutArchive&, const SFlushFighter&);

CInArchive& operator>>(CInArchive&, SArenaPlayerBaseData&);
COutArchive& operator<<(COutArchive&, const SArenaPlayerBaseData&);

CInArchive& operator>>(CInArchive&, SArenaPlayerData&);
COutArchive& operator<<(COutArchive&, const SArenaPlayerData&);

CInArchive& operator>>(CInArchive&, SArenaPlayerBaseDataUpdate&);
COutArchive& operator<<(COutArchive&, const SArenaPlayerBaseDataUpdate&);

CInArchive& operator>>(CInArchive&, SFlushFitherForClient&);
COutArchive& operator<<(COutArchive&, const SFlushFitherForClient&);

CInArchive& operator>>(CInArchive&, SLadderReport&);
COutArchive& operator<<(COutArchive&, const SLadderReport&);

CInArchive& operator>>(CInArchive&, SArenaRank2Client&);
COutArchive& operator<<(COutArchive&, const SArenaRank2Client&);

CInArchive& operator>>(CInArchive&, SArenaPlayerBaseData2Client&);
COutArchive& operator<<(COutArchive&, const SArenaPlayerBaseData2Client&);

#ifdef PROT_USE_XML
/////////////////////以下为XML转换函数/////////////////////
bool FromXML(TiXmlElement&, SLadderRobot&);
bool ToXML(const SLadderRobot&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecLadderRobot&);
bool VectorToXML(const TVecLadderRobot&, TiXmlElement&);

bool FromXML(TiXmlElement&, SArenaAward&);
bool ToXML(const SArenaAward&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecArenaAward&);
bool VectorToXML(const TVecArenaAward&, TiXmlElement&);

bool FromXML(TiXmlElement&, SArenaFighter&);
bool ToXML(const SArenaFighter&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecArenaFighter&);
bool VectorToXML(const TVecArenaFighter&, TiXmlElement&);

bool FromXML(TiXmlElement&, SFlushFighter&);
bool ToXML(const SFlushFighter&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecFlushFither&);
bool VectorToXML(const TVecFlushFither&, TiXmlElement&);

bool FromXML(TiXmlElement&, SArenaPlayerBaseData&);
bool ToXML(const SArenaPlayerBaseData&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecArenaPlayerBaseData&);
bool VectorToXML(const TVecArenaPlayerBaseData&, TiXmlElement&);

bool FromXML(TiXmlElement&, SArenaPlayerData&);
bool ToXML(const SArenaPlayerData&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecArenaPlayerData&);
bool VectorToXML(const TVecArenaPlayerData&, TiXmlElement&);

bool FromXML(TiXmlElement&, SArenaPlayerBaseDataUpdate&);
bool ToXML(const SArenaPlayerBaseDataUpdate&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecArenaPlayerBaseDataUpdate&);
bool VectorToXML(const TVecArenaPlayerBaseDataUpdate&, TiXmlElement&);

bool FromXML(TiXmlElement&, SFlushFitherForClient&);
bool ToXML(const SFlushFitherForClient&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecSFlushFitherForClient&);
bool VectorToXML(const TVecSFlushFitherForClient&, TiXmlElement&);

bool FromXML(TiXmlElement&, SLadderReport&);
bool ToXML(const SLadderReport&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecLadderReport&);
bool VectorToXML(const TVecLadderReport&, TiXmlElement&);

bool FromXML(TiXmlElement&, SArenaRank2Client&);
bool ToXML(const SArenaRank2Client&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecArenaRank2Client&);
bool VectorToXML(const TVecArenaRank2Client&, TiXmlElement&);

bool FromXML(TiXmlElement&, SArenaPlayerBaseData2Client&);
bool ToXML(const SArenaPlayerBaseData2Client&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecArenaPlayerBaseData2Client&);
bool VectorToXML(const TVecArenaPlayerBaseData2Client&, TiXmlElement&);
#endif //PROT_USE_XML

} //namespace NArenaGS
