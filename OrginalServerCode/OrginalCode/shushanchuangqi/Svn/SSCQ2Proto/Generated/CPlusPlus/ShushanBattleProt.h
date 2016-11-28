/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    ShushanBattleProt.h
//  Purpose:      蜀山论剑相关协议
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
#include "MapProt.h"

namespace NShushanBattleProt
{

/////////////////////以下为类型定义/////////////////////
//蜀山论剑参加状态
enum ESSBattleStatus
{
	eSSBattle_ENTER, //已进入
	eSSBattle_QUIT, //已退出
	eSSBattle_JOINBYE, //轮空
	eSSBattle_FIGHTING //正在战斗
};

#ifdef PROT_USE_XML
const char* EnumValToStr(ESSBattleStatus);
bool EnumStrToVal(const char*, ESSBattleStatus&);
#endif //PROT_USE_XML

//蜀山论剑操作结果
enum ESSBattleResult
{
	eSSBattle_Suc, //成功
	eSSBattle_NotRuning, //论剑活动未开始
	eSSBattle_CDTime, //正在冷却
	eSSBattle_LevelLimit, //等级小于30级
	eSSBattle_LackMoney, //金钱不够
	eSSBattle_NotEnter, //未参加
	eSSBattle_Full, //霸气or怒气已满
	eSSBattle_NotEnough, //霸气or怒气不足
	eSSBattle_Used, //已使用
	eSSBattle_OtherErr //其他错误
};

#ifdef PROT_USE_XML
const char* EnumValToStr(ESSBattleResult);
bool EnumStrToVal(const char*, ESSBattleResult&);
#endif //PROT_USE_XML

//任务数据结构
struct SBattleTaskData
{
	UINT8 byTaskID; //任务ID
	UINT8 byAward; //荣誉奖励值
	UINT8 byComplete; //是否完成(0否,1是)

	SBattleTaskData();
	SBattleTaskData(UINT8 byTaskID_, UINT8 byAward_, UINT8 byComplete_);
};

typedef std::vector<SBattleTaskData> TVecTaskData;

//战斗战报数据结构
struct SSSBattleReport
{
	UINT8 byRound; //当前轮次
	std::string strNameA; //攻方玩家名字
	UINT64 qwRoleA; //攻方玩家ID
	std::string strNameB; //守方玩家名字
	UINT64 qwRoleB; //守方玩家ID
	UINT8 byResult; //结果(0是攻方胜利,1是守方胜利,2是攻方逃跑,3守方逃跑,4攻方轮空)
	UINT64 qwBattleID; //战报ID
	UINT8 byCurrKill; //当前连杀数(若个人战报即表明个人连杀数,若全部战报即表明攻方连杀数)
	UINT16 wHonor; //当场获得荣誉值(若个人战报即表明个人获得荣誉值,若全部战报即表明攻方获得荣誉值)

	SSSBattleReport();
	SSSBattleReport(UINT8 byRound_, const std::string& strNameA_, UINT64 qwRoleA_, const std::string& strNameB_, UINT64 qwRoleB_, 
		UINT8 byResult_, UINT64 qwBattleID_, UINT8 byCurrKill_, UINT16 wHonor_);
#ifdef __GNUG__
	SSSBattleReport(const SSSBattleReport& src) = default; //默认拷贝构造函数
	SSSBattleReport& operator=(const SSSBattleReport& rhs) = default; //默认赋值操作符
#endif
	SSSBattleReport(SSSBattleReport&& src); //转移构造函数
	SSSBattleReport& operator=(SSSBattleReport&& rhs); //转移赋值操作符
};

typedef std::vector<SSSBattleReport> TVecSSBattleReport;

//对方玩家数据结构
struct SOtherPlayer
{
	UINT64 qwRoleIDOther; //对方玩家ID
	UINT8 byCurrKillOther; //对方当前连杀数
	UINT16 wHonorOther; //对方总荣誉值
	UINT16 wSkillFlagsOther; //对方技能使用位域,对应位表示技能是否已使用(低8位)
	UINT32 dwMaxHpOther; //对方总血量
	UINT32 dwCurHpOther; //对方当前血量
	UINT32 dwBattlePowerOther; //对方总战斗力
	NMapProt::SPlayerAppear rPlayerAppear; //对方玩家的外观

	SOtherPlayer();
	SOtherPlayer(UINT64 qwRoleIDOther_, UINT8 byCurrKillOther_, UINT16 wHonorOther_, UINT16 wSkillFlagsOther_, UINT32 dwMaxHpOther_, 
		UINT32 dwCurHpOther_, UINT32 dwBattlePowerOther_, const NMapProt::SPlayerAppear& rPlayerAppear_);
#ifdef __GNUG__
	SOtherPlayer(const SOtherPlayer& src) = default; //默认拷贝构造函数
	SOtherPlayer& operator=(const SOtherPlayer& rhs) = default; //默认赋值操作符
#endif
	SOtherPlayer(SOtherPlayer&& src); //转移构造函数
	SOtherPlayer& operator=(SOtherPlayer&& rhs); //转移赋值操作符
};

typedef std::vector<SOtherPlayer> TVecOtherPlayer;

//论剑场玩家的配对信息，也是发给前端用的信息
struct SSSBattlePairInfo
{
	UINT8 byRound; //当前轮次
	UINT16 wTimeLeft; //距离下一场【或者开始】时间(秒)
	UINT8 byCurrKill; //当前连杀数
	UINT8 byMaxKill; //最高连杀数
	UINT8 byTotalWin; //胜利场数
	UINT8 byTotalLose; //失败场数
	UINT16 wHonor; //总荣誉值
	UINT8 byDomineer; //霸气值
	UINT8 byAnger; //怒气值
	UINT16 wSkillFlags; //技能使用位域,对应位表示技能是否已使用(低8位)
	TVecTaskData vecTaskData; //任务数据vec
	UINT32 dwMaxHp; //自己总血量
	UINT32 dwCurHp; //自己当前血量
	UINT32 dwBattlePower; //自己总战斗力
	TVecOtherPlayer vecOtherPlayer; //对方玩家数据

	SSSBattlePairInfo();
#ifdef __GNUG__
	SSSBattlePairInfo(const SSSBattlePairInfo& src) = default; //默认拷贝构造函数
	SSSBattlePairInfo& operator=(const SSSBattlePairInfo& rhs) = default; //默认赋值操作符
#endif
	SSSBattlePairInfo(SSSBattlePairInfo&& src); //转移构造函数
	SSSBattlePairInfo& operator=(SSSBattlePairInfo&& rhs); //转移赋值操作符
};

//蜀山论剑场玩家使用技能返回的数据结构
struct SSSBattleUseSkill
{
	UINT64 qwRoleID; //玩家ID
	UINT16 wHonor; //总荣誉值
	UINT16 wSkillFlags; //技能使用位域,对应位表示技能是否已使用(低8位)
	UINT32 dwCurHp; //当前血量

	SSSBattleUseSkill();
	SSSBattleUseSkill(UINT64 qwRoleID_, UINT16 wHonor_, UINT16 wSkillFlags_, UINT32 dwCurHp_);
};

/////////////////////以下为序列化函数/////////////////////
CInArchive& operator>>(CInArchive&, SBattleTaskData&);
COutArchive& operator<<(COutArchive&, const SBattleTaskData&);

CInArchive& operator>>(CInArchive&, SSSBattleReport&);
COutArchive& operator<<(COutArchive&, const SSSBattleReport&);

CInArchive& operator>>(CInArchive&, SOtherPlayer&);
COutArchive& operator<<(COutArchive&, const SOtherPlayer&);

CInArchive& operator>>(CInArchive&, SSSBattlePairInfo&);
COutArchive& operator<<(COutArchive&, const SSSBattlePairInfo&);

CInArchive& operator>>(CInArchive&, SSSBattleUseSkill&);
COutArchive& operator<<(COutArchive&, const SSSBattleUseSkill&);

#ifdef PROT_USE_XML
/////////////////////以下为XML转换函数/////////////////////
bool FromXML(TiXmlElement&, SBattleTaskData&);
bool ToXML(const SBattleTaskData&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecTaskData&);
bool VectorToXML(const TVecTaskData&, TiXmlElement&);

bool FromXML(TiXmlElement&, SSSBattleReport&);
bool ToXML(const SSSBattleReport&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecSSBattleReport&);
bool VectorToXML(const TVecSSBattleReport&, TiXmlElement&);

bool FromXML(TiXmlElement&, SOtherPlayer&);
bool ToXML(const SOtherPlayer&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecOtherPlayer&);
bool VectorToXML(const TVecOtherPlayer&, TiXmlElement&);

bool FromXML(TiXmlElement&, SSSBattlePairInfo&);
bool ToXML(const SSSBattlePairInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SSSBattleUseSkill&);
bool ToXML(const SSSBattleUseSkill&, TiXmlElement&);
#endif //PROT_USE_XML

} //namespace NShushanBattleProt
