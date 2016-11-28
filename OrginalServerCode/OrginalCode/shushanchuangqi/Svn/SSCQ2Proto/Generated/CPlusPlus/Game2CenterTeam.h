/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    Game2CenterTeam.h
//  Purpose:      GameServer到CenterServer关于Team的通信协议
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
#include "TeamGS.h"

namespace NGame2CenterTeam
{

/////////////////////以下为类型定义/////////////////////
//请求结果
enum EPlayerTeam
{
	EPlayerEnterTeam, //玩家进入队伍
	EPlayerLeaveTeam //玩家离开队伍
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EPlayerTeam);
bool EnumStrToVal(const char*, EPlayerTeam&);
#endif //PROT_USE_XML

//一个战报
struct BattleReport
{
	UINT64 qwBattleID; //战报ID
	std::string strBattle; //战报
	UINT16 wMonsterGroup; //怪物组
	UINT8 bySuc; //是否胜利

	BattleReport();
	BattleReport(UINT64 qwBattleID_, const std::string& strBattle_, UINT16 wMonsterGroup_, UINT8 bySuc_);
#ifdef __GNUG__
	BattleReport(const BattleReport& src) = default; //默认拷贝构造函数
	BattleReport& operator=(const BattleReport& rhs) = default; //默认赋值操作符
#endif
	BattleReport(BattleReport&& src); //转移构造函数
	BattleReport& operator=(BattleReport&& rhs); //转移赋值操作符
};

typedef std::vector<BattleReport> TVecBattleReport;

//一场战斗结果
struct TeamReport
{
	TVecBattleReport vecReport; //战报序列
	UINT8 bySuc; //是否胜利
	UINT16 wTurns; //总回合数
	UINT64 qwLeaderID; //队长ID
	UINT64 qwLeaderFighter; //队长主将

	TeamReport();
	TeamReport(const TVecBattleReport& vecReport_, UINT8 bySuc_, UINT16 wTurns_, UINT64 qwLeaderID_, UINT64 qwLeaderFighter_);
#ifdef __GNUG__
	TeamReport(const TeamReport& src) = default; //默认拷贝构造函数
	TeamReport& operator=(const TeamReport& rhs) = default; //默认赋值操作符
#endif
	TeamReport(TeamReport&& src); //转移构造函数
	TeamReport& operator=(TeamReport&& rhs); //转移赋值操作符
};

typedef std::vector<TeamReport> TVecTeamReport;

/////////////////////以下为序列化函数/////////////////////
CInArchive& operator>>(CInArchive&, BattleReport&);
COutArchive& operator<<(COutArchive&, const BattleReport&);

CInArchive& operator>>(CInArchive&, TeamReport&);
COutArchive& operator<<(COutArchive&, const TeamReport&);

#ifdef PROT_USE_XML
/////////////////////以下为XML转换函数/////////////////////
bool FromXML(TiXmlElement&, BattleReport&);
bool ToXML(const BattleReport&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecBattleReport&);
bool VectorToXML(const TVecBattleReport&, TiXmlElement&);

bool FromXML(TiXmlElement&, TeamReport&);
bool ToXML(const TeamReport&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecTeamReport&);
bool VectorToXML(const TVecTeamReport&, TiXmlElement&);
#endif //PROT_USE_XML

} //namespace NGame2CenterTeam
