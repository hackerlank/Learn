/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    LogEvent.h
//  Purpose:      日志协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include <string>
#include <memory>
#include "ServerDefine.h"
#include "Archive.h"
#ifdef PROT_USE_XML
#include "tinyxml.h"
#endif
#include "LogDataDefine.h"

namespace NLogEvent
{

/////////////////////以下为类型定义/////////////////////
//日志的类型
enum ELogType
{
	eLogNone, //无
	eLogSystem, //系统日志
	eLogItem, //道具日志
	eLogMoney, //金钱日志
	eLogLoginout, //登陆登出日志
	eLogMall, //商城日志
	eLogLevelUp, //升级日志
	eLogRecruit, //招募日志
	eLogProp, //属性日志
	eLogSkill, //技能日志
	eLogTask, //任务日志
	eLogBattle, //战斗日志
	eLogEquipReplace, //装备替换日志
	eLogEquipOpeator, //装备操作日志
	eLogAlchemy, //圣物操作日志
	eLogDungeon, //副本日志
	eLogActivity, //活动日志
	eLogPVPRank, //PVP排行
	eLogBuilding, //建筑日志
	eLogGuild, //公会日志
	eLogFamily, //家族日志
	eLogVIP, //VIP日志
	eLogUDPLog, //UDPLog日志
	eLogMail, //邮件日志
	eLogActive, //活跃度日志
	eLogEnd
};

#ifdef PROT_USE_XML
const char* EnumValToStr(ELogType);
bool EnumStrToVal(const char*, ELogType&);
#endif //PROT_USE_XML


} //namespace NLogEvent
