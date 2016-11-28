/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    LogEvent.cpp
//  Purpose:      日志协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "LogEvent.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NLogEvent
{

#ifdef PROT_USE_XML

const char* EnumValToStr(ELogType e)
{
	switch(e)
	{
	case eLogNone:
		return "eLogNone";
	case eLogSystem:
		return "eLogSystem";
	case eLogItem:
		return "eLogItem";
	case eLogMoney:
		return "eLogMoney";
	case eLogLoginout:
		return "eLogLoginout";
	case eLogMall:
		return "eLogMall";
	case eLogLevelUp:
		return "eLogLevelUp";
	case eLogRecruit:
		return "eLogRecruit";
	case eLogProp:
		return "eLogProp";
	case eLogSkill:
		return "eLogSkill";
	case eLogTask:
		return "eLogTask";
	case eLogBattle:
		return "eLogBattle";
	case eLogEquipReplace:
		return "eLogEquipReplace";
	case eLogEquipOpeator:
		return "eLogEquipOpeator";
	case eLogAlchemy:
		return "eLogAlchemy";
	case eLogDungeon:
		return "eLogDungeon";
	case eLogActivity:
		return "eLogActivity";
	case eLogPVPRank:
		return "eLogPVPRank";
	case eLogBuilding:
		return "eLogBuilding";
	case eLogGuild:
		return "eLogGuild";
	case eLogFamily:
		return "eLogFamily";
	case eLogVIP:
		return "eLogVIP";
	case eLogUDPLog:
		return "eLogUDPLog";
	case eLogMail:
		return "eLogMail";
	case eLogActive:
		return "eLogActive";
	case eLogEnd:
		return "eLogEnd";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, ELogType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, ELogType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eLogNone", eLogNone));
		mapStr2Val.insert(make_pair("eLogSystem", eLogSystem));
		mapStr2Val.insert(make_pair("eLogItem", eLogItem));
		mapStr2Val.insert(make_pair("eLogMoney", eLogMoney));
		mapStr2Val.insert(make_pair("eLogLoginout", eLogLoginout));
		mapStr2Val.insert(make_pair("eLogMall", eLogMall));
		mapStr2Val.insert(make_pair("eLogLevelUp", eLogLevelUp));
		mapStr2Val.insert(make_pair("eLogRecruit", eLogRecruit));
		mapStr2Val.insert(make_pair("eLogProp", eLogProp));
		mapStr2Val.insert(make_pair("eLogSkill", eLogSkill));
		mapStr2Val.insert(make_pair("eLogTask", eLogTask));
		mapStr2Val.insert(make_pair("eLogBattle", eLogBattle));
		mapStr2Val.insert(make_pair("eLogEquipReplace", eLogEquipReplace));
		mapStr2Val.insert(make_pair("eLogEquipOpeator", eLogEquipOpeator));
		mapStr2Val.insert(make_pair("eLogAlchemy", eLogAlchemy));
		mapStr2Val.insert(make_pair("eLogDungeon", eLogDungeon));
		mapStr2Val.insert(make_pair("eLogActivity", eLogActivity));
		mapStr2Val.insert(make_pair("eLogPVPRank", eLogPVPRank));
		mapStr2Val.insert(make_pair("eLogBuilding", eLogBuilding));
		mapStr2Val.insert(make_pair("eLogGuild", eLogGuild));
		mapStr2Val.insert(make_pair("eLogFamily", eLogFamily));
		mapStr2Val.insert(make_pair("eLogVIP", eLogVIP));
		mapStr2Val.insert(make_pair("eLogUDPLog", eLogUDPLog));
		mapStr2Val.insert(make_pair("eLogMail", eLogMail));
		mapStr2Val.insert(make_pair("eLogActive", eLogActive));
		mapStr2Val.insert(make_pair("eLogEnd", eLogEnd));
	}
	auto it = mapStr2Val.find(pszEnumStr);
	if(it == mapStr2Val.end())
	{
		LOG_CRI << "Unrecognized enum string: " << pszEnumStr;
		return false;
	}
	e = it->second;
	return true;
}

#endif //PROT_USE_XML

} //namespace NLogEvent
