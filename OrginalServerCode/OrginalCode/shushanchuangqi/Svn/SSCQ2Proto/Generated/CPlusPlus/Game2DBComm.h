/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    Game2DBComm.h
//  Purpose:      GameServer到DBServer的通信协议
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
#include "MallProt.h"
#include "ProtoCommon.h"
#include "RoleInfoDefine.h"
#include "ServerCommon.h"
#include "ShengLingProt.h"

namespace NGame2DBComm
{

/////////////////////以下为类型定义/////////////////////
//保存请求的类型
enum ESaveType
{
	eSaveNone, //无
	eSaveAway, //暂时离开
	eSaveOff, //下线离开
	eSaveJump, //跳线
	eSaveKick, //被踢
	eSaveExcept, //异常
	eSaveData, //定时保存
	eSaveToCross, //跳到跨服服务器
	eSaveFromCross //从跨服服务器跳回
};

#ifdef PROT_USE_XML
const char* EnumValToStr(ESaveType);
bool EnumStrToVal(const char*, ESaveType&);
#endif //PROT_USE_XML

//进入GameServer的类型
enum EEnterType
{
	eEnterNone, //无
	eEnterLogin, //正常上线
	eEnterJump, //跳线
	eEnterToCross, //跳到跨服服务器
	eEnterFromCross //从跨服服务器跳回
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EEnterType);
bool EnumStrToVal(const char*, EEnterType&);
#endif //PROT_USE_XML

//EDataType:eTypeWorldBossInfo
struct SWBossDBInfo
{
	UINT16 wBossID; //BOSSID
	UINT32 dwLast; //次被击杀所用时长，单位秒
	UINT32 dwHP; //上次最大血量
	UINT32 dwAtk; //上次物理攻击力
	UINT32 dwMAtk; //上次魔法攻击力
	UINT32 dwLastEndTime; //上次结束时间

	SWBossDBInfo();
	SWBossDBInfo(UINT16 wBossID_, UINT32 dwLast_, UINT32 dwHP_, UINT32 dwAtk_, UINT32 dwMAtk_, 
		UINT32 dwLastEndTime_);
};

typedef std::vector<SWBossDBInfo> TVecWBossDBInfo;

//数据库加载的新帮派战历史信息
struct SDBGuildNewBattleHistoryInfo
{
	UINT8 byMountainType; //灵山类型
	UINT64 qwGuildID; //当前占领帮派ID
	std::string strGuildName; //当前占领帮派名称
	std::string strGuildOwnerName; //当前占领帮派帮主名称
	UINT32 dwTime; //占领时间

	SDBGuildNewBattleHistoryInfo();
	SDBGuildNewBattleHistoryInfo(UINT8 byMountainType_, UINT64 qwGuildID_, const std::string& strGuildName_, const std::string& strGuildOwnerName_, UINT32 dwTime_);
#ifdef __GNUG__
	SDBGuildNewBattleHistoryInfo(const SDBGuildNewBattleHistoryInfo& src) = default; //默认拷贝构造函数
	SDBGuildNewBattleHistoryInfo& operator=(const SDBGuildNewBattleHistoryInfo& rhs) = default; //默认赋值操作符
#endif
	SDBGuildNewBattleHistoryInfo(SDBGuildNewBattleHistoryInfo&& src); //转移构造函数
	SDBGuildNewBattleHistoryInfo& operator=(SDBGuildNewBattleHistoryInfo&& rhs); //转移赋值操作符
};

typedef std::vector<SDBGuildNewBattleHistoryInfo> TVecDBGuildNewBattleHistoryInfo;

/////////////////////以下为序列化函数/////////////////////
CInArchive& operator>>(CInArchive&, SWBossDBInfo&);
COutArchive& operator<<(COutArchive&, const SWBossDBInfo&);

CInArchive& operator>>(CInArchive&, SDBGuildNewBattleHistoryInfo&);
COutArchive& operator<<(COutArchive&, const SDBGuildNewBattleHistoryInfo&);

#ifdef PROT_USE_XML
/////////////////////以下为XML转换函数/////////////////////
bool FromXML(TiXmlElement&, SWBossDBInfo&);
bool ToXML(const SWBossDBInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecWBossDBInfo&);
bool VectorToXML(const TVecWBossDBInfo&, TiXmlElement&);

bool FromXML(TiXmlElement&, SDBGuildNewBattleHistoryInfo&);
bool ToXML(const SDBGuildNewBattleHistoryInfo&, TiXmlElement&);
bool VectorFromXML(TiXmlElement&, TVecDBGuildNewBattleHistoryInfo&);
bool VectorToXML(const TVecDBGuildNewBattleHistoryInfo&, TiXmlElement&);
#endif //PROT_USE_XML

} //namespace NGame2DBComm
