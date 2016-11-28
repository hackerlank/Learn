/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    NewGuildBattleProt.cpp
//  Purpose:      新帮派战相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "NewGuildBattleProt.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NNewGuildBattleProt
{

#ifdef PROT_USE_XML

const char* EnumValToStr(ENGBState e)
{
	switch(e)
	{
	case eNGBSNone:
		return "eNGBSNone";
	case eNGBSReady:
		return "eNGBSReady";
	case eNGBSBattle:
		return "eNGBSBattle";
	case eNGBSBattleEnd:
		return "eNGBSBattleEnd";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, ENGBState& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, ENGBState> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eNGBSNone", eNGBSNone));
		mapStr2Val.insert(make_pair("eNGBSReady", eNGBSReady));
		mapStr2Val.insert(make_pair("eNGBSBattle", eNGBSBattle));
		mapStr2Val.insert(make_pair("eNGBSBattleEnd", eNGBSBattleEnd));
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

#ifdef PROT_USE_XML

const char* EnumValToStr(ENGBPlayerState e)
{
	switch(e)
	{
	case eNGBPSNone:
		return "eNGBPSNone";
	case eNGBPSWait:
		return "eNGBPSWait";
	case eNGBPSDead:
		return "eNGBPSDead";
	case eNGBPSRunAway:
		return "eNGBPSRunAway";
	case eNGBPSMax:
		return "eNGBPSMax";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, ENGBPlayerState& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, ENGBPlayerState> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eNGBPSNone", eNGBPSNone));
		mapStr2Val.insert(make_pair("eNGBPSWait", eNGBPSWait));
		mapStr2Val.insert(make_pair("eNGBPSDead", eNGBPSDead));
		mapStr2Val.insert(make_pair("eNGBPSRunAway", eNGBPSRunAway));
		mapStr2Val.insert(make_pair("eNGBPSMax", eNGBPSMax));
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

#ifdef PROT_USE_XML

const char* EnumValToStr(ENGBMountain e)
{
	switch(e)
	{
	case eNGBMNone:
		return "eNGBMNone";
	case eNGBMEMei:
		return "eNGBMEMei";
	case eNGBMKunLun:
		return "eNGBMKunLun";
	case eNGBMHuangShan:
		return "eNGBMHuangShan";
	case eNGBMMax:
		return "eNGBMMax";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, ENGBMountain& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, ENGBMountain> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eNGBMNone", eNGBMNone));
		mapStr2Val.insert(make_pair("eNGBMEMei", eNGBMEMei));
		mapStr2Val.insert(make_pair("eNGBMKunLun", eNGBMKunLun));
		mapStr2Val.insert(make_pair("eNGBMHuangShan", eNGBMHuangShan));
		mapStr2Val.insert(make_pair("eNGBMMax", eNGBMMax));
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

#ifdef PROT_USE_XML

const char* EnumValToStr(ENGBCaveCore e)
{
	switch(e)
	{
	case eNGBCCNone:
		return "eNGBCCNone";
	case eNGBCCDragon:
		return "eNGBCCDragon";
	case eNGBCCTiger:
		return "eNGBCCTiger";
	case eNGBCCPhenix:
		return "eNGBCCPhenix";
	case eNGBCCTurtle:
		return "eNGBCCTurtle";
	case eNGBCCMax:
		return "eNGBCCMax";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, ENGBCaveCore& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, ENGBCaveCore> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eNGBCCNone", eNGBCCNone));
		mapStr2Val.insert(make_pair("eNGBCCDragon", eNGBCCDragon));
		mapStr2Val.insert(make_pair("eNGBCCTiger", eNGBCCTiger));
		mapStr2Val.insert(make_pair("eNGBCCPhenix", eNGBCCPhenix));
		mapStr2Val.insert(make_pair("eNGBCCTurtle", eNGBCCTurtle));
		mapStr2Val.insert(make_pair("eNGBCCMax", eNGBCCMax));
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

#ifdef PROT_USE_XML

const char* EnumValToStr(ENGBMountainState e)
{
	switch(e)
	{
	case eNGBMSNone:
		return "eNGBMSNone";
	case eNGBMSGate:
		return "eNGBMSGate";
	case eNGBMSCave:
		return "eNGBMSCave";
	case eNGBMSEnd:
		return "eNGBMSEnd";
	case eNGBMSMax:
		return "eNGBMSMax";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, ENGBMountainState& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, ENGBMountainState> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eNGBMSNone", eNGBMSNone));
		mapStr2Val.insert(make_pair("eNGBMSGate", eNGBMSGate));
		mapStr2Val.insert(make_pair("eNGBMSCave", eNGBMSCave));
		mapStr2Val.insert(make_pair("eNGBMSEnd", eNGBMSEnd));
		mapStr2Val.insert(make_pair("eNGBMSMax", eNGBMSMax));
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

#ifdef PROT_USE_XML

const char* EnumValToStr(ENGBSide e)
{
	switch(e)
	{
	case eNGBSideAttacker:
		return "eNGBSideAttacker";
	case eNGBSideDefencer:
		return "eNGBSideDefencer";
	case eNGBSideInvalid:
		return "eNGBSideInvalid";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, ENGBSide& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, ENGBSide> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eNGBSideAttacker", eNGBSideAttacker));
		mapStr2Val.insert(make_pair("eNGBSideDefencer", eNGBSideDefencer));
		mapStr2Val.insert(make_pair("eNGBSideInvalid", eNGBSideInvalid));
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

#ifdef PROT_USE_XML

const char* EnumValToStr(ENGBResult e)
{
	switch(e)
	{
	case eNGBRSuccess:
		return "eNGBRSuccess";
	case eNGBRFailed:
		return "eNGBRFailed";
	case eNGBRWrongTime:
		return "eNGBRWrongTime";
	case eNGBRNotInBattle:
		return "eNGBRNotInBattle";
	case eNGBRNoGuild:
		return "eNGBRNoGuild";
	case eNGBRInvalidMountain:
		return "eNGBRInvalidMountain";
	case eNGBRNoAuthority:
		return "eNGBRNoAuthority";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, ENGBResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, ENGBResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eNGBRSuccess", eNGBRSuccess));
		mapStr2Val.insert(make_pair("eNGBRFailed", eNGBRFailed));
		mapStr2Val.insert(make_pair("eNGBRWrongTime", eNGBRWrongTime));
		mapStr2Val.insert(make_pair("eNGBRNotInBattle", eNGBRNotInBattle));
		mapStr2Val.insert(make_pair("eNGBRNoGuild", eNGBRNoGuild));
		mapStr2Val.insert(make_pair("eNGBRInvalidMountain", eNGBRInvalidMountain));
		mapStr2Val.insert(make_pair("eNGBRNoAuthority", eNGBRNoAuthority));
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

#ifdef PROT_USE_XML

const char* EnumValToStr(ENGBEnterResult e)
{
	switch(e)
	{
	case eNGBERSuccess:
		return "eNGBERSuccess";
	case eNGBERFailed:
		return "eNGBERFailed";
	case eNGBERNotInGuild:
		return "eNGBERNotInGuild";
	case eNGBERRepeat:
		return "eNGBERRepeat";
	case eNGBERWrongTime:
		return "eNGBERWrongTime";
	case eNGBERGuildLevel:
		return "eNGBERGuildLevel";
	case eNGBEREscape:
		return "eNGBEREscape";
	case eNGBERGuildWrong:
		return "eNGBERGuildWrong";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, ENGBEnterResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, ENGBEnterResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eNGBERSuccess", eNGBERSuccess));
		mapStr2Val.insert(make_pair("eNGBERFailed", eNGBERFailed));
		mapStr2Val.insert(make_pair("eNGBERNotInGuild", eNGBERNotInGuild));
		mapStr2Val.insert(make_pair("eNGBERRepeat", eNGBERRepeat));
		mapStr2Val.insert(make_pair("eNGBERWrongTime", eNGBERWrongTime));
		mapStr2Val.insert(make_pair("eNGBERGuildLevel", eNGBERGuildLevel));
		mapStr2Val.insert(make_pair("eNGBEREscape", eNGBEREscape));
		mapStr2Val.insert(make_pair("eNGBERGuildWrong", eNGBERGuildWrong));
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

#ifdef PROT_USE_XML

const char* EnumValToStr(ENGBGateAttackResult e)
{
	switch(e)
	{
	case eNGBGARSuccess:
		return "eNGBGARSuccess";
	case eNGBGARFailed:
		return "eNGBGARFailed";
	case eNGBGARTargetIsDead:
		return "eNGBGARTargetIsDead";
	case eNGBGARSelfIsDead:
		return "eNGBGARSelfIsDead";
	case eNGBGARWrongTime:
		return "eNGBGARWrongTime";
	case eNGBGARDefencer:
		return "eNGBGARDefencer";
	case eNGBGARDefencerAlive:
		return "eNGBGARDefencerAlive";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, ENGBGateAttackResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, ENGBGateAttackResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eNGBGARSuccess", eNGBGARSuccess));
		mapStr2Val.insert(make_pair("eNGBGARFailed", eNGBGARFailed));
		mapStr2Val.insert(make_pair("eNGBGARTargetIsDead", eNGBGARTargetIsDead));
		mapStr2Val.insert(make_pair("eNGBGARSelfIsDead", eNGBGARSelfIsDead));
		mapStr2Val.insert(make_pair("eNGBGARWrongTime", eNGBGARWrongTime));
		mapStr2Val.insert(make_pair("eNGBGARDefencer", eNGBGARDefencer));
		mapStr2Val.insert(make_pair("eNGBGARDefencerAlive", eNGBGARDefencerAlive));
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

#ifdef PROT_USE_XML

const char* EnumValToStr(ENGBBuyPuppetResult e)
{
	switch(e)
	{
	case eNGBBPRSuccess:
		return "eNGBBPRSuccess";
	case eNGBBPRFailed:
		return "eNGBBPRFailed";
	case eNGBBPRLackOfMoney:
		return "eNGBBPRLackOfMoney";
	case eNGBBPRCountLimit:
		return "eNGBBPRCountLimit";
	case eNGBBPRWrongTime:
		return "eNGBBPRWrongTime";
	case eNGBBPRDefencer:
		return "eNGBBPRDefencer";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, ENGBBuyPuppetResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, ENGBBuyPuppetResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eNGBBPRSuccess", eNGBBPRSuccess));
		mapStr2Val.insert(make_pair("eNGBBPRFailed", eNGBBPRFailed));
		mapStr2Val.insert(make_pair("eNGBBPRLackOfMoney", eNGBBPRLackOfMoney));
		mapStr2Val.insert(make_pair("eNGBBPRCountLimit", eNGBBPRCountLimit));
		mapStr2Val.insert(make_pair("eNGBBPRWrongTime", eNGBBPRWrongTime));
		mapStr2Val.insert(make_pair("eNGBBPRDefencer", eNGBBPRDefencer));
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

#ifdef PROT_USE_XML

const char* EnumValToStr(ENGBClearDeadCDResult e)
{
	switch(e)
	{
	case eNGBCDCDRSuccess:
		return "eNGBCDCDRSuccess";
	case eNGBCDCDRFailed:
		return "eNGBCDCDRFailed";
	case eNGBCDCDRIsAlive:
		return "eNGBCDCDRIsAlive";
	case eNGBCDCDRWrongTime:
		return "eNGBCDCDRWrongTime";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, ENGBClearDeadCDResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, ENGBClearDeadCDResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eNGBCDCDRSuccess", eNGBCDCDRSuccess));
		mapStr2Val.insert(make_pair("eNGBCDCDRFailed", eNGBCDCDRFailed));
		mapStr2Val.insert(make_pair("eNGBCDCDRIsAlive", eNGBCDCDRIsAlive));
		mapStr2Val.insert(make_pair("eNGBCDCDRWrongTime", eNGBCDCDRWrongTime));
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

#ifdef PROT_USE_XML

const char* EnumValToStr(ENGBCaveAttackResult e)
{
	switch(e)
	{
	case eNGBCARSuccess:
		return "eNGBCARSuccess";
	case eNGBCARFailed:
		return "eNGBCARFailed";
	case eNGBCARBeCaptured:
		return "eNGBCARBeCaptured";
	case eNGBCARCountLimit:
		return "eNGBCARCountLimit";
	case eNGBCARWrongTime:
		return "eNGBCARWrongTime";
	case eNGBCARTargetDead:
		return "eNGBCARTargetDead";
	case eNGBCARNotInCore:
		return "eNGBCARNotInCore";
	case eNGBCARInCore:
		return "eNGBCARInCore";
	case eNGBCARSelfIsDead:
		return "eNGBCARSelfIsDead";
	case eNGBCARSelfSide:
		return "eNGBCARSelfSide";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, ENGBCaveAttackResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, ENGBCaveAttackResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eNGBCARSuccess", eNGBCARSuccess));
		mapStr2Val.insert(make_pair("eNGBCARFailed", eNGBCARFailed));
		mapStr2Val.insert(make_pair("eNGBCARBeCaptured", eNGBCARBeCaptured));
		mapStr2Val.insert(make_pair("eNGBCARCountLimit", eNGBCARCountLimit));
		mapStr2Val.insert(make_pair("eNGBCARWrongTime", eNGBCARWrongTime));
		mapStr2Val.insert(make_pair("eNGBCARTargetDead", eNGBCARTargetDead));
		mapStr2Val.insert(make_pair("eNGBCARNotInCore", eNGBCARNotInCore));
		mapStr2Val.insert(make_pair("eNGBCARInCore", eNGBCARInCore));
		mapStr2Val.insert(make_pair("eNGBCARSelfIsDead", eNGBCARSelfIsDead));
		mapStr2Val.insert(make_pair("eNGBCARSelfSide", eNGBCARSelfSide));
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

#ifdef PROT_USE_XML

const char* EnumValToStr(ENGBQuitResult e)
{
	switch(e)
	{
	case eNGBQuitSuccess:
		return "eNGBQuitSuccess";
	case eNGBQuitFailed:
		return "eNGBQuitFailed";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, ENGBQuitResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, ENGBQuitResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eNGBQuitSuccess", eNGBQuitSuccess));
		mapStr2Val.insert(make_pair("eNGBQuitFailed", eNGBQuitFailed));
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

#ifdef PROT_USE_XML

const char* EnumValToStr(ENGBBattleResult e)
{
	switch(e)
	{
	case eNGBBattleSuccess:
		return "eNGBBattleSuccess";
	case eNGBBattleFailed:
		return "eNGBBattleFailed";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, ENGBBattleResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, ENGBBattleResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eNGBBattleSuccess", eNGBBattleSuccess));
		mapStr2Val.insert(make_pair("eNGBBattleFailed", eNGBBattleFailed));
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

SPuppetInfo::SPuppetInfo() : byIndex(0), qwOwnerID(0), dwNextAttackTime(0) { }

SPuppetInfo::SPuppetInfo(UINT8 byIndex_, UINT64 qwOwnerID_, UINT32 dwNextAttackTime_) : byIndex(byIndex_), qwOwnerID(qwOwnerID_), dwNextAttackTime(dwNextAttackTime_) { }

CInArchive& operator>>(CInArchive& src, SPuppetInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.byIndex;
	src >> s.qwOwnerID;
	src >> s.dwNextAttackTime;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SPuppetInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.byIndex;
	src << s.qwOwnerID;
	src << s.dwNextAttackTime;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SPuppetInfo& s)
{
	if(strcmp(rElement.Value(), "SPuppetInfo") != 0)
	{
		LOG_CRI << "rElement is not SPuppetInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byIndex is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byIndex") != 0)
	{
		LOG_CRI << "Attribute: name is not byIndex!";
		return false;
	}
	const char* pszVal_byIndex = pElemChild->Attribute("value");
	if(pszVal_byIndex == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byIndex, s.byIndex))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwOwnerID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwOwnerID") != 0)
	{
		LOG_CRI << "Attribute: name is not qwOwnerID!";
		return false;
	}
	const char* pszVal_qwOwnerID = pElemChild->Attribute("value");
	if(pszVal_qwOwnerID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwOwnerID, s.qwOwnerID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwNextAttackTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwNextAttackTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwNextAttackTime!";
		return false;
	}
	const char* pszVal_dwNextAttackTime = pElemChild->Attribute("value");
	if(pszVal_dwNextAttackTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwNextAttackTime, s.dwNextAttackTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SPuppetInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SPuppetInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("傀儡信息"));
	unique_ptr<TiXmlElement> pElem_byIndex(new TiXmlElement("UINT8"));
	if(pElem_byIndex == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byIndex->SetAttribute("name", "byIndex");
	pElem_byIndex->SetAttribute("value", NumberToString(s.byIndex).c_str());
	pElem_byIndex->SetAttribute("comment", ToUTF8Ptr("所属站位(0,1,2; 0为系统战争傀儡)"));
	if(rElement.LinkEndChild(pElem_byIndex.get()) != NULL)
		pElem_byIndex.release();
	unique_ptr<TiXmlElement> pElem_qwOwnerID(new TiXmlElement("UINT64"));
	if(pElem_qwOwnerID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwOwnerID->SetAttribute("name", "qwOwnerID");
	pElem_qwOwnerID->SetAttribute("value", NumberToString(s.qwOwnerID).c_str());
	pElem_qwOwnerID->SetAttribute("comment", ToUTF8Ptr("拥有者ID"));
	if(rElement.LinkEndChild(pElem_qwOwnerID.get()) != NULL)
		pElem_qwOwnerID.release();
	unique_ptr<TiXmlElement> pElem_dwNextAttackTime(new TiXmlElement("UINT32"));
	if(pElem_dwNextAttackTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwNextAttackTime->SetAttribute("name", "dwNextAttackTime");
	pElem_dwNextAttackTime->SetAttribute("value", NumberToString(s.dwNextAttackTime).c_str());
	pElem_dwNextAttackTime->SetAttribute("comment", ToUTF8Ptr("下一次攻击时间"));
	if(rElement.LinkEndChild(pElem_dwNextAttackTime.get()) != NULL)
		pElem_dwNextAttackTime.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecPuppetInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SPuppetInfo s;
		if(!FromXML(*pElemMember, s))
		{
			LOG_CRI << "FromXML fails!";
			return false;
		}
		vec.emplace_back(move(s));
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecPuppetInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SPuppetInfo"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!ToXML(vec[i], *pElemMember))
		{
			LOG_CRI << "ToXML fails!";
			return false;
		}
		if(rElement.LinkEndChild(pElemMember.get()) != NULL)
			pElemMember.release();
	}
	return true;
}

#endif

SPlayerInfo::SPlayerInfo() : qwRoleID(0), eJob((NProtoCommon::ECareerType)0), eSex((NProtoCommon::ESexType)0), byQuality(0), qwGuildID(0), 
			eSide((ENGBSide)0), dwMaxHP(0), dwHP(0), dwDeadTime(0) { }

SPlayerInfo::SPlayerInfo(UINT64 qwRoleID_, const std::string& strName_, NProtoCommon::ECareerType eJob_, NProtoCommon::ESexType eSex_, UINT8 byQuality_, 
			UINT64 qwGuildID_, ENGBSide eSide_, UINT32 dwMaxHP_, UINT32 dwHP_, UINT32 dwDeadTime_)
			: qwRoleID(qwRoleID_), strName(strName_), eJob(eJob_), eSex(eSex_), byQuality(byQuality_), 
			qwGuildID(qwGuildID_), eSide(eSide_), dwMaxHP(dwMaxHP_), dwHP(dwHP_), dwDeadTime(dwDeadTime_) { }

SPlayerInfo::SPlayerInfo(SPlayerInfo&& src) : qwRoleID(src.qwRoleID), strName(move(src.strName)), eJob(src.eJob), eSex(src.eSex), byQuality(src.byQuality), 
			qwGuildID(src.qwGuildID), eSide(src.eSide), dwMaxHP(src.dwMaxHP), dwHP(src.dwHP), dwDeadTime(src.dwDeadTime) { }

SPlayerInfo& SPlayerInfo::operator=(SPlayerInfo&& rhs)
{
	if(this != &rhs)
	{
		this->~SPlayerInfo();
		new (this) SPlayerInfo(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SPlayerInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwRoleID;
	src >> s.strName;
	src >> (UINT8&)s.eJob;
	src >> (UINT8&)s.eSex;
	src >> s.byQuality;
	src >> s.qwGuildID;
	src >> (UINT8&)s.eSide;
	src >> s.dwMaxHP;
	src >> s.dwHP;
	src >> s.dwDeadTime;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SPlayerInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.qwRoleID;
	src << s.strName;
	src << (UINT8&)s.eJob;
	src << (UINT8&)s.eSex;
	src << s.byQuality;
	src << s.qwGuildID;
	src << (UINT8&)s.eSide;
	src << s.dwMaxHP;
	src << s.dwHP;
	src << s.dwDeadTime;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SPlayerInfo& s)
{
	if(strcmp(rElement.Value(), "SPlayerInfo") != 0)
	{
		LOG_CRI << "rElement is not SPlayerInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwRoleID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwRoleID") != 0)
	{
		LOG_CRI << "Attribute: name is not qwRoleID!";
		return false;
	}
	const char* pszVal_qwRoleID = pElemChild->Attribute("value");
	if(pszVal_qwRoleID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwRoleID, s.qwRoleID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strName is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strName") != 0)
	{
		LOG_CRI << "Attribute: name is not strName!";
		return false;
	}
	const char* pszVal_strName = pElemChild->Attribute("value");
	if(pszVal_strName == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strName = pszVal_strName;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eJob is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "ProtoCommon::ECareerType") != 0)
	{
		LOG_CRI << "pElemChild is not ProtoCommon::ECareerType!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eJob") != 0)
	{
		LOG_CRI << "Attribute: name is not eJob!";
		return false;
	}
	const char* pszVal_eJob = pElemChild->Attribute("value");
	if(pszVal_eJob == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!NProtoCommon::EnumStrToVal(pszVal_eJob, s.eJob))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eSex is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "ProtoCommon::ESexType") != 0)
	{
		LOG_CRI << "pElemChild is not ProtoCommon::ESexType!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eSex") != 0)
	{
		LOG_CRI << "Attribute: name is not eSex!";
		return false;
	}
	const char* pszVal_eSex = pElemChild->Attribute("value");
	if(pszVal_eSex == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!NProtoCommon::EnumStrToVal(pszVal_eSex, s.eSex))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byQuality is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byQuality") != 0)
	{
		LOG_CRI << "Attribute: name is not byQuality!";
		return false;
	}
	const char* pszVal_byQuality = pElemChild->Attribute("value");
	if(pszVal_byQuality == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byQuality, s.byQuality))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwGuildID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwGuildID") != 0)
	{
		LOG_CRI << "Attribute: name is not qwGuildID!";
		return false;
	}
	const char* pszVal_qwGuildID = pElemChild->Attribute("value");
	if(pszVal_qwGuildID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwGuildID, s.qwGuildID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eSide is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "ENGBSide") != 0)
	{
		LOG_CRI << "pElemChild is not ENGBSide!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eSide") != 0)
	{
		LOG_CRI << "Attribute: name is not eSide!";
		return false;
	}
	const char* pszVal_eSide = pElemChild->Attribute("value");
	if(pszVal_eSide == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!EnumStrToVal(pszVal_eSide, s.eSide))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwMaxHP is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwMaxHP") != 0)
	{
		LOG_CRI << "Attribute: name is not dwMaxHP!";
		return false;
	}
	const char* pszVal_dwMaxHP = pElemChild->Attribute("value");
	if(pszVal_dwMaxHP == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwMaxHP, s.dwMaxHP))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwHP is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwHP") != 0)
	{
		LOG_CRI << "Attribute: name is not dwHP!";
		return false;
	}
	const char* pszVal_dwHP = pElemChild->Attribute("value");
	if(pszVal_dwHP == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwHP, s.dwHP))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwDeadTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwDeadTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwDeadTime!";
		return false;
	}
	const char* pszVal_dwDeadTime = pElemChild->Attribute("value");
	if(pszVal_dwDeadTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwDeadTime, s.dwDeadTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SPlayerInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SPlayerInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("玩家信息"));
	unique_ptr<TiXmlElement> pElem_qwRoleID(new TiXmlElement("UINT64"));
	if(pElem_qwRoleID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwRoleID->SetAttribute("name", "qwRoleID");
	pElem_qwRoleID->SetAttribute("value", NumberToString(s.qwRoleID).c_str());
	pElem_qwRoleID->SetAttribute("comment", ToUTF8Ptr("玩家ID"));
	if(rElement.LinkEndChild(pElem_qwRoleID.get()) != NULL)
		pElem_qwRoleID.release();
	unique_ptr<TiXmlElement> pElem_strName(new TiXmlElement("string"));
	if(pElem_strName == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strName->SetAttribute("name", "strName");
	pElem_strName->SetAttribute("value", s.strName.c_str());
	pElem_strName->SetAttribute("comment", ToUTF8Ptr("玩家姓名"));
	if(rElement.LinkEndChild(pElem_strName.get()) != NULL)
		pElem_strName.release();
	unique_ptr<TiXmlElement> pElem_eJob(new TiXmlElement("ProtoCommon::ECareerType"));
	if(pElem_eJob == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eJob->SetAttribute("name", "eJob");
	const char* pszEnum_eJob = NProtoCommon::EnumValToStr(s.eJob);
	if(pszEnum_eJob == NULL)
	{
		LOG_CRI << "EnumValToStr for eJob fails!";
		return false;
	}
	pElem_eJob->SetAttribute("value", pszEnum_eJob);
	pElem_eJob->SetAttribute("comment", ToUTF8Ptr("职业"));
	if(rElement.LinkEndChild(pElem_eJob.get()) != NULL)
		pElem_eJob.release();
	unique_ptr<TiXmlElement> pElem_eSex(new TiXmlElement("ProtoCommon::ESexType"));
	if(pElem_eSex == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eSex->SetAttribute("name", "eSex");
	const char* pszEnum_eSex = NProtoCommon::EnumValToStr(s.eSex);
	if(pszEnum_eSex == NULL)
	{
		LOG_CRI << "EnumValToStr for eSex fails!";
		return false;
	}
	pElem_eSex->SetAttribute("value", pszEnum_eSex);
	pElem_eSex->SetAttribute("comment", ToUTF8Ptr("性别"));
	if(rElement.LinkEndChild(pElem_eSex.get()) != NULL)
		pElem_eSex.release();
	unique_ptr<TiXmlElement> pElem_byQuality(new TiXmlElement("UINT8"));
	if(pElem_byQuality == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byQuality->SetAttribute("name", "byQuality");
	pElem_byQuality->SetAttribute("value", NumberToString(s.byQuality).c_str());
	pElem_byQuality->SetAttribute("comment", ToUTF8Ptr("品质"));
	if(rElement.LinkEndChild(pElem_byQuality.get()) != NULL)
		pElem_byQuality.release();
	unique_ptr<TiXmlElement> pElem_qwGuildID(new TiXmlElement("UINT64"));
	if(pElem_qwGuildID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwGuildID->SetAttribute("name", "qwGuildID");
	pElem_qwGuildID->SetAttribute("value", NumberToString(s.qwGuildID).c_str());
	pElem_qwGuildID->SetAttribute("comment", ToUTF8Ptr("帮派ID"));
	if(rElement.LinkEndChild(pElem_qwGuildID.get()) != NULL)
		pElem_qwGuildID.release();
	unique_ptr<TiXmlElement> pElem_eSide(new TiXmlElement("ENGBSide"));
	if(pElem_eSide == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eSide->SetAttribute("name", "eSide");
	const char* pszEnum_eSide = EnumValToStr(s.eSide);
	if(pszEnum_eSide == NULL)
	{
		LOG_CRI << "EnumValToStr for ENGBSide fails!";
		return false;
	}
	pElem_eSide->SetAttribute("value", pszEnum_eSide);
	pElem_eSide->SetAttribute("comment", ToUTF8Ptr("自己所在方向"));
	if(rElement.LinkEndChild(pElem_eSide.get()) != NULL)
		pElem_eSide.release();
	unique_ptr<TiXmlElement> pElem_dwMaxHP(new TiXmlElement("UINT32"));
	if(pElem_dwMaxHP == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwMaxHP->SetAttribute("name", "dwMaxHP");
	pElem_dwMaxHP->SetAttribute("value", NumberToString(s.dwMaxHP).c_str());
	pElem_dwMaxHP->SetAttribute("comment", ToUTF8Ptr("最大血量"));
	if(rElement.LinkEndChild(pElem_dwMaxHP.get()) != NULL)
		pElem_dwMaxHP.release();
	unique_ptr<TiXmlElement> pElem_dwHP(new TiXmlElement("UINT32"));
	if(pElem_dwHP == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwHP->SetAttribute("name", "dwHP");
	pElem_dwHP->SetAttribute("value", NumberToString(s.dwHP).c_str());
	pElem_dwHP->SetAttribute("comment", ToUTF8Ptr("当前血量"));
	if(rElement.LinkEndChild(pElem_dwHP.get()) != NULL)
		pElem_dwHP.release();
	unique_ptr<TiXmlElement> pElem_dwDeadTime(new TiXmlElement("UINT32"));
	if(pElem_dwDeadTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwDeadTime->SetAttribute("name", "dwDeadTime");
	pElem_dwDeadTime->SetAttribute("value", NumberToString(s.dwDeadTime).c_str());
	pElem_dwDeadTime->SetAttribute("comment", ToUTF8Ptr("死亡时间（复活所需时间）"));
	if(rElement.LinkEndChild(pElem_dwDeadTime.get()) != NULL)
		pElem_dwDeadTime.release();
	return true;
}

#endif

SMountainPanelInfo::SMountainPanelInfo() : eMountainType((ENGBMountain)0), eState((ENGBMountainState)0), qwGuildID(0), wGuildLevel(0), dwGuildOwnCount(0) { }

SMountainPanelInfo::SMountainPanelInfo(ENGBMountain eMountainType_, ENGBMountainState eState_, UINT64 qwGuildID_, const std::string& strGuildName_, UINT16 wGuildLevel_, 
			const std::string& strGuildOwnerName_, UINT32 dwGuildOwnCount_, const TVecUINT64& vecAttackGuildID_)
			: eMountainType(eMountainType_), eState(eState_), qwGuildID(qwGuildID_), strGuildName(strGuildName_), wGuildLevel(wGuildLevel_), 
			strGuildOwnerName(strGuildOwnerName_), dwGuildOwnCount(dwGuildOwnCount_), vecAttackGuildID(vecAttackGuildID_) { }

SMountainPanelInfo::SMountainPanelInfo(SMountainPanelInfo&& src) : eMountainType(src.eMountainType), eState(src.eState), qwGuildID(src.qwGuildID), strGuildName(move(src.strGuildName)), wGuildLevel(src.wGuildLevel), 
			strGuildOwnerName(move(src.strGuildOwnerName)), dwGuildOwnCount(src.dwGuildOwnCount), vecAttackGuildID(src.vecAttackGuildID) { }

SMountainPanelInfo& SMountainPanelInfo::operator=(SMountainPanelInfo&& rhs)
{
	if(this != &rhs)
	{
		this->~SMountainPanelInfo();
		new (this) SMountainPanelInfo(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SMountainPanelInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (UINT8&)s.eMountainType;
	src >> (UINT8&)s.eState;
	src >> s.qwGuildID;
	src >> s.strGuildName;
	src >> s.wGuildLevel;
	src >> s.strGuildOwnerName;
	src >> s.dwGuildOwnCount;
	src >> s.vecAttackGuildID;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SMountainPanelInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (UINT8&)s.eMountainType;
	src << (UINT8&)s.eState;
	src << s.qwGuildID;
	src << s.strGuildName;
	src << s.wGuildLevel;
	src << s.strGuildOwnerName;
	src << s.dwGuildOwnCount;
	src << s.vecAttackGuildID;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SMountainPanelInfo& s)
{
	if(strcmp(rElement.Value(), "SMountainPanelInfo") != 0)
	{
		LOG_CRI << "rElement is not SMountainPanelInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eMountainType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "ENGBMountain") != 0)
	{
		LOG_CRI << "pElemChild is not ENGBMountain!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eMountainType") != 0)
	{
		LOG_CRI << "Attribute: name is not eMountainType!";
		return false;
	}
	const char* pszVal_eMountainType = pElemChild->Attribute("value");
	if(pszVal_eMountainType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!EnumStrToVal(pszVal_eMountainType, s.eMountainType))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eState is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "ENGBMountainState") != 0)
	{
		LOG_CRI << "pElemChild is not ENGBMountainState!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eState") != 0)
	{
		LOG_CRI << "Attribute: name is not eState!";
		return false;
	}
	const char* pszVal_eState = pElemChild->Attribute("value");
	if(pszVal_eState == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!EnumStrToVal(pszVal_eState, s.eState))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwGuildID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwGuildID") != 0)
	{
		LOG_CRI << "Attribute: name is not qwGuildID!";
		return false;
	}
	const char* pszVal_qwGuildID = pElemChild->Attribute("value");
	if(pszVal_qwGuildID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwGuildID, s.qwGuildID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strGuildName is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strGuildName") != 0)
	{
		LOG_CRI << "Attribute: name is not strGuildName!";
		return false;
	}
	const char* pszVal_strGuildName = pElemChild->Attribute("value");
	if(pszVal_strGuildName == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strGuildName = pszVal_strGuildName;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wGuildLevel is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wGuildLevel") != 0)
	{
		LOG_CRI << "Attribute: name is not wGuildLevel!";
		return false;
	}
	const char* pszVal_wGuildLevel = pElemChild->Attribute("value");
	if(pszVal_wGuildLevel == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wGuildLevel, s.wGuildLevel))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strGuildOwnerName is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strGuildOwnerName") != 0)
	{
		LOG_CRI << "Attribute: name is not strGuildOwnerName!";
		return false;
	}
	const char* pszVal_strGuildOwnerName = pElemChild->Attribute("value");
	if(pszVal_strGuildOwnerName == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strGuildOwnerName = pszVal_strGuildOwnerName;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwGuildOwnCount is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwGuildOwnCount") != 0)
	{
		LOG_CRI << "Attribute: name is not dwGuildOwnCount!";
		return false;
	}
	const char* pszVal_dwGuildOwnCount = pElemChild->Attribute("value");
	if(pszVal_dwGuildOwnCount == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwGuildOwnCount, s.dwGuildOwnCount))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecAttackGuildID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecUINT64") != 0)
	{
		LOG_CRI << "pElemChild is not TVecUINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecAttackGuildID") != 0)
	{
		LOG_CRI << "Attribute: name is not vecAttackGuildID!";
		return false;
	}
	const char* pszText_vecAttackGuildID = pElemChild->GetText();
	if(pszText_vecAttackGuildID != NULL)
		SplitToNumber(pszText_vecAttackGuildID, ",", s.vecAttackGuildID);
	return true;
}

bool ToXML(const SMountainPanelInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SMountainPanelInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("灵山面板信息"));
	unique_ptr<TiXmlElement> pElem_eMountainType(new TiXmlElement("ENGBMountain"));
	if(pElem_eMountainType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eMountainType->SetAttribute("name", "eMountainType");
	const char* pszEnum_eMountainType = EnumValToStr(s.eMountainType);
	if(pszEnum_eMountainType == NULL)
	{
		LOG_CRI << "EnumValToStr for ENGBMountain fails!";
		return false;
	}
	pElem_eMountainType->SetAttribute("value", pszEnum_eMountainType);
	pElem_eMountainType->SetAttribute("comment", ToUTF8Ptr("灵山类型"));
	if(rElement.LinkEndChild(pElem_eMountainType.get()) != NULL)
		pElem_eMountainType.release();
	unique_ptr<TiXmlElement> pElem_eState(new TiXmlElement("ENGBMountainState"));
	if(pElem_eState == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eState->SetAttribute("name", "eState");
	const char* pszEnum_eState = EnumValToStr(s.eState);
	if(pszEnum_eState == NULL)
	{
		LOG_CRI << "EnumValToStr for ENGBMountainState fails!";
		return false;
	}
	pElem_eState->SetAttribute("value", pszEnum_eState);
	pElem_eState->SetAttribute("comment", ToUTF8Ptr("灵山状态"));
	if(rElement.LinkEndChild(pElem_eState.get()) != NULL)
		pElem_eState.release();
	unique_ptr<TiXmlElement> pElem_qwGuildID(new TiXmlElement("UINT64"));
	if(pElem_qwGuildID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwGuildID->SetAttribute("name", "qwGuildID");
	pElem_qwGuildID->SetAttribute("value", NumberToString(s.qwGuildID).c_str());
	pElem_qwGuildID->SetAttribute("comment", ToUTF8Ptr("当前占领帮派ID"));
	if(rElement.LinkEndChild(pElem_qwGuildID.get()) != NULL)
		pElem_qwGuildID.release();
	unique_ptr<TiXmlElement> pElem_strGuildName(new TiXmlElement("string"));
	if(pElem_strGuildName == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strGuildName->SetAttribute("name", "strGuildName");
	pElem_strGuildName->SetAttribute("value", s.strGuildName.c_str());
	pElem_strGuildName->SetAttribute("comment", ToUTF8Ptr("当前占领帮派名称"));
	if(rElement.LinkEndChild(pElem_strGuildName.get()) != NULL)
		pElem_strGuildName.release();
	unique_ptr<TiXmlElement> pElem_wGuildLevel(new TiXmlElement("UINT16"));
	if(pElem_wGuildLevel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wGuildLevel->SetAttribute("name", "wGuildLevel");
	pElem_wGuildLevel->SetAttribute("value", NumberToString(s.wGuildLevel).c_str());
	pElem_wGuildLevel->SetAttribute("comment", ToUTF8Ptr("当前占领帮派等级"));
	if(rElement.LinkEndChild(pElem_wGuildLevel.get()) != NULL)
		pElem_wGuildLevel.release();
	unique_ptr<TiXmlElement> pElem_strGuildOwnerName(new TiXmlElement("string"));
	if(pElem_strGuildOwnerName == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strGuildOwnerName->SetAttribute("name", "strGuildOwnerName");
	pElem_strGuildOwnerName->SetAttribute("value", s.strGuildOwnerName.c_str());
	pElem_strGuildOwnerName->SetAttribute("comment", ToUTF8Ptr("当前占领帮派帮主名称"));
	if(rElement.LinkEndChild(pElem_strGuildOwnerName.get()) != NULL)
		pElem_strGuildOwnerName.release();
	unique_ptr<TiXmlElement> pElem_dwGuildOwnCount(new TiXmlElement("UINT32"));
	if(pElem_dwGuildOwnCount == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwGuildOwnCount->SetAttribute("name", "dwGuildOwnCount");
	pElem_dwGuildOwnCount->SetAttribute("value", NumberToString(s.dwGuildOwnCount).c_str());
	pElem_dwGuildOwnCount->SetAttribute("comment", ToUTF8Ptr("当前占领帮派占领次数"));
	if(rElement.LinkEndChild(pElem_dwGuildOwnCount.get()) != NULL)
		pElem_dwGuildOwnCount.release();
	unique_ptr<TiXmlElement> pElem_vecAttackGuildID(new TiXmlElement("TVecUINT64"));
	if(pElem_vecAttackGuildID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecAttackGuildID->SetAttribute("name", "vecAttackGuildID");
	string strText_vecAttackGuildID;
	for(size_t i = 0; i < s.vecAttackGuildID.size(); ++i)
	{
		if(i > 0)
			strText_vecAttackGuildID += ", ";
		strText_vecAttackGuildID += NumberToString(s.vecAttackGuildID[i]);
	}
	unique_ptr<TiXmlText> pText_vecAttackGuildID(new TiXmlText(strText_vecAttackGuildID.c_str()));
	if(pText_vecAttackGuildID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(pElem_vecAttackGuildID->LinkEndChild(pText_vecAttackGuildID.get()) != NULL)
		pText_vecAttackGuildID.release();
	pElem_vecAttackGuildID->SetAttribute("comment", ToUTF8Ptr("（洞府战）攻击帮派ID"));
	if(rElement.LinkEndChild(pElem_vecAttackGuildID.get()) != NULL)
		pElem_vecAttackGuildID.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecMountainPanelInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SMountainPanelInfo s;
		if(!FromXML(*pElemMember, s))
		{
			LOG_CRI << "FromXML fails!";
			return false;
		}
		vec.emplace_back(move(s));
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecMountainPanelInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SMountainPanelInfo"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!ToXML(vec[i], *pElemMember))
		{
			LOG_CRI << "ToXML fails!";
			return false;
		}
		if(rElement.LinkEndChild(pElemMember.get()) != NULL)
			pElemMember.release();
	}
	return true;
}

#endif

SPlayerPanelInfo::SPlayerPanelInfo() : qwRoleID(0), byLevel(0), byQuality(0), qwGuildID(0), eSide((ENGBSide)0), 
			byHPP(0), dwMaxHP(0), dwHP(0) { }

SPlayerPanelInfo::SPlayerPanelInfo(UINT64 qwRoleID_, const std::string& strName_, UINT8 byLevel_, UINT8 byQuality_, UINT64 qwGuildID_, 
			ENGBSide eSide_, const std::string& strGuildName_, UINT8 byHPP_, UINT32 dwMaxHP_, UINT32 dwHP_)
			: qwRoleID(qwRoleID_), strName(strName_), byLevel(byLevel_), byQuality(byQuality_), qwGuildID(qwGuildID_), 
			eSide(eSide_), strGuildName(strGuildName_), byHPP(byHPP_), dwMaxHP(dwMaxHP_), dwHP(dwHP_) { }

SPlayerPanelInfo::SPlayerPanelInfo(SPlayerPanelInfo&& src) : qwRoleID(src.qwRoleID), strName(move(src.strName)), byLevel(src.byLevel), byQuality(src.byQuality), qwGuildID(src.qwGuildID), 
			eSide(src.eSide), strGuildName(move(src.strGuildName)), byHPP(src.byHPP), dwMaxHP(src.dwMaxHP), dwHP(src.dwHP) { }

SPlayerPanelInfo& SPlayerPanelInfo::operator=(SPlayerPanelInfo&& rhs)
{
	if(this != &rhs)
	{
		this->~SPlayerPanelInfo();
		new (this) SPlayerPanelInfo(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SPlayerPanelInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwRoleID;
	src >> s.strName;
	src >> s.byLevel;
	src >> s.byQuality;
	src >> s.qwGuildID;
	src >> (UINT8&)s.eSide;
	src >> s.strGuildName;
	src >> s.byHPP;
	src >> s.dwMaxHP;
	src >> s.dwHP;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SPlayerPanelInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.qwRoleID;
	src << s.strName;
	src << s.byLevel;
	src << s.byQuality;
	src << s.qwGuildID;
	src << (UINT8&)s.eSide;
	src << s.strGuildName;
	src << s.byHPP;
	src << s.dwMaxHP;
	src << s.dwHP;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SPlayerPanelInfo& s)
{
	if(strcmp(rElement.Value(), "SPlayerPanelInfo") != 0)
	{
		LOG_CRI << "rElement is not SPlayerPanelInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwRoleID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwRoleID") != 0)
	{
		LOG_CRI << "Attribute: name is not qwRoleID!";
		return false;
	}
	const char* pszVal_qwRoleID = pElemChild->Attribute("value");
	if(pszVal_qwRoleID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwRoleID, s.qwRoleID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strName is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strName") != 0)
	{
		LOG_CRI << "Attribute: name is not strName!";
		return false;
	}
	const char* pszVal_strName = pElemChild->Attribute("value");
	if(pszVal_strName == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strName = pszVal_strName;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byLevel is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byLevel") != 0)
	{
		LOG_CRI << "Attribute: name is not byLevel!";
		return false;
	}
	const char* pszVal_byLevel = pElemChild->Attribute("value");
	if(pszVal_byLevel == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byLevel, s.byLevel))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byQuality is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byQuality") != 0)
	{
		LOG_CRI << "Attribute: name is not byQuality!";
		return false;
	}
	const char* pszVal_byQuality = pElemChild->Attribute("value");
	if(pszVal_byQuality == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byQuality, s.byQuality))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwGuildID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwGuildID") != 0)
	{
		LOG_CRI << "Attribute: name is not qwGuildID!";
		return false;
	}
	const char* pszVal_qwGuildID = pElemChild->Attribute("value");
	if(pszVal_qwGuildID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwGuildID, s.qwGuildID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eSide is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "ENGBSide") != 0)
	{
		LOG_CRI << "pElemChild is not ENGBSide!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eSide") != 0)
	{
		LOG_CRI << "Attribute: name is not eSide!";
		return false;
	}
	const char* pszVal_eSide = pElemChild->Attribute("value");
	if(pszVal_eSide == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!EnumStrToVal(pszVal_eSide, s.eSide))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strGuildName is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strGuildName") != 0)
	{
		LOG_CRI << "Attribute: name is not strGuildName!";
		return false;
	}
	const char* pszVal_strGuildName = pElemChild->Attribute("value");
	if(pszVal_strGuildName == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strGuildName = pszVal_strGuildName;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byHPP is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byHPP") != 0)
	{
		LOG_CRI << "Attribute: name is not byHPP!";
		return false;
	}
	const char* pszVal_byHPP = pElemChild->Attribute("value");
	if(pszVal_byHPP == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byHPP, s.byHPP))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwMaxHP is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwMaxHP") != 0)
	{
		LOG_CRI << "Attribute: name is not dwMaxHP!";
		return false;
	}
	const char* pszVal_dwMaxHP = pElemChild->Attribute("value");
	if(pszVal_dwMaxHP == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwMaxHP, s.dwMaxHP))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwHP is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwHP") != 0)
	{
		LOG_CRI << "Attribute: name is not dwHP!";
		return false;
	}
	const char* pszVal_dwHP = pElemChild->Attribute("value");
	if(pszVal_dwHP == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwHP, s.dwHP))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SPlayerPanelInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SPlayerPanelInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("面板玩家信息"));
	unique_ptr<TiXmlElement> pElem_qwRoleID(new TiXmlElement("UINT64"));
	if(pElem_qwRoleID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwRoleID->SetAttribute("name", "qwRoleID");
	pElem_qwRoleID->SetAttribute("value", NumberToString(s.qwRoleID).c_str());
	pElem_qwRoleID->SetAttribute("comment", ToUTF8Ptr("玩家ID"));
	if(rElement.LinkEndChild(pElem_qwRoleID.get()) != NULL)
		pElem_qwRoleID.release();
	unique_ptr<TiXmlElement> pElem_strName(new TiXmlElement("string"));
	if(pElem_strName == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strName->SetAttribute("name", "strName");
	pElem_strName->SetAttribute("value", s.strName.c_str());
	pElem_strName->SetAttribute("comment", ToUTF8Ptr("玩家姓名"));
	if(rElement.LinkEndChild(pElem_strName.get()) != NULL)
		pElem_strName.release();
	unique_ptr<TiXmlElement> pElem_byLevel(new TiXmlElement("UINT8"));
	if(pElem_byLevel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byLevel->SetAttribute("name", "byLevel");
	pElem_byLevel->SetAttribute("value", NumberToString(s.byLevel).c_str());
	pElem_byLevel->SetAttribute("comment", ToUTF8Ptr("玩家等级"));
	if(rElement.LinkEndChild(pElem_byLevel.get()) != NULL)
		pElem_byLevel.release();
	unique_ptr<TiXmlElement> pElem_byQuality(new TiXmlElement("UINT8"));
	if(pElem_byQuality == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byQuality->SetAttribute("name", "byQuality");
	pElem_byQuality->SetAttribute("value", NumberToString(s.byQuality).c_str());
	pElem_byQuality->SetAttribute("comment", ToUTF8Ptr("品质"));
	if(rElement.LinkEndChild(pElem_byQuality.get()) != NULL)
		pElem_byQuality.release();
	unique_ptr<TiXmlElement> pElem_qwGuildID(new TiXmlElement("UINT64"));
	if(pElem_qwGuildID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwGuildID->SetAttribute("name", "qwGuildID");
	pElem_qwGuildID->SetAttribute("value", NumberToString(s.qwGuildID).c_str());
	pElem_qwGuildID->SetAttribute("comment", ToUTF8Ptr("帮派ID"));
	if(rElement.LinkEndChild(pElem_qwGuildID.get()) != NULL)
		pElem_qwGuildID.release();
	unique_ptr<TiXmlElement> pElem_eSide(new TiXmlElement("ENGBSide"));
	if(pElem_eSide == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eSide->SetAttribute("name", "eSide");
	const char* pszEnum_eSide = EnumValToStr(s.eSide);
	if(pszEnum_eSide == NULL)
	{
		LOG_CRI << "EnumValToStr for ENGBSide fails!";
		return false;
	}
	pElem_eSide->SetAttribute("value", pszEnum_eSide);
	pElem_eSide->SetAttribute("comment", ToUTF8Ptr("自己所在方向"));
	if(rElement.LinkEndChild(pElem_eSide.get()) != NULL)
		pElem_eSide.release();
	unique_ptr<TiXmlElement> pElem_strGuildName(new TiXmlElement("string"));
	if(pElem_strGuildName == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strGuildName->SetAttribute("name", "strGuildName");
	pElem_strGuildName->SetAttribute("value", s.strGuildName.c_str());
	pElem_strGuildName->SetAttribute("comment", ToUTF8Ptr("帮派名称"));
	if(rElement.LinkEndChild(pElem_strGuildName.get()) != NULL)
		pElem_strGuildName.release();
	unique_ptr<TiXmlElement> pElem_byHPP(new TiXmlElement("UINT8"));
	if(pElem_byHPP == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byHPP->SetAttribute("name", "byHPP");
	pElem_byHPP->SetAttribute("value", NumberToString(s.byHPP).c_str());
	pElem_byHPP->SetAttribute("comment", ToUTF8Ptr("剩余生命值百分比"));
	if(rElement.LinkEndChild(pElem_byHPP.get()) != NULL)
		pElem_byHPP.release();
	unique_ptr<TiXmlElement> pElem_dwMaxHP(new TiXmlElement("UINT32"));
	if(pElem_dwMaxHP == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwMaxHP->SetAttribute("name", "dwMaxHP");
	pElem_dwMaxHP->SetAttribute("value", NumberToString(s.dwMaxHP).c_str());
	pElem_dwMaxHP->SetAttribute("comment", ToUTF8Ptr("最大血量"));
	if(rElement.LinkEndChild(pElem_dwMaxHP.get()) != NULL)
		pElem_dwMaxHP.release();
	unique_ptr<TiXmlElement> pElem_dwHP(new TiXmlElement("UINT32"));
	if(pElem_dwHP == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwHP->SetAttribute("name", "dwHP");
	pElem_dwHP->SetAttribute("value", NumberToString(s.dwHP).c_str());
	pElem_dwHP->SetAttribute("comment", ToUTF8Ptr("当前血量"));
	if(rElement.LinkEndChild(pElem_dwHP.get()) != NULL)
		pElem_dwHP.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecPlayerPanelInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SPlayerPanelInfo s;
		if(!FromXML(*pElemMember, s))
		{
			LOG_CRI << "FromXML fails!";
			return false;
		}
		vec.emplace_back(move(s));
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecPlayerPanelInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SPlayerPanelInfo"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!ToXML(vec[i], *pElemMember))
		{
			LOG_CRI << "ToXML fails!";
			return false;
		}
		if(rElement.LinkEndChild(pElemMember.get()) != NULL)
			pElemMember.release();
	}
	return true;
}

#endif

SOwnerHistoryInfo::SOwnerHistoryInfo() : eMountainType((ENGBMountain)0), qwGuildID(0), dwTime(0) { }

SOwnerHistoryInfo::SOwnerHistoryInfo(ENGBMountain eMountainType_, UINT64 qwGuildID_, const std::string& strGuildName_, const std::string& strGuildOwnerName_, UINT32 dwTime_)
			: eMountainType(eMountainType_), qwGuildID(qwGuildID_), strGuildName(strGuildName_), strGuildOwnerName(strGuildOwnerName_), dwTime(dwTime_) { }

SOwnerHistoryInfo::SOwnerHistoryInfo(SOwnerHistoryInfo&& src) : eMountainType(src.eMountainType), qwGuildID(src.qwGuildID), strGuildName(move(src.strGuildName)), strGuildOwnerName(move(src.strGuildOwnerName)), dwTime(src.dwTime) { }

SOwnerHistoryInfo& SOwnerHistoryInfo::operator=(SOwnerHistoryInfo&& rhs)
{
	if(this != &rhs)
	{
		this->~SOwnerHistoryInfo();
		new (this) SOwnerHistoryInfo(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SOwnerHistoryInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (UINT8&)s.eMountainType;
	src >> s.qwGuildID;
	src >> s.strGuildName;
	src >> s.strGuildOwnerName;
	src >> s.dwTime;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SOwnerHistoryInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (UINT8&)s.eMountainType;
	src << s.qwGuildID;
	src << s.strGuildName;
	src << s.strGuildOwnerName;
	src << s.dwTime;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SOwnerHistoryInfo& s)
{
	if(strcmp(rElement.Value(), "SOwnerHistoryInfo") != 0)
	{
		LOG_CRI << "rElement is not SOwnerHistoryInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eMountainType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "ENGBMountain") != 0)
	{
		LOG_CRI << "pElemChild is not ENGBMountain!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eMountainType") != 0)
	{
		LOG_CRI << "Attribute: name is not eMountainType!";
		return false;
	}
	const char* pszVal_eMountainType = pElemChild->Attribute("value");
	if(pszVal_eMountainType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!EnumStrToVal(pszVal_eMountainType, s.eMountainType))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwGuildID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwGuildID") != 0)
	{
		LOG_CRI << "Attribute: name is not qwGuildID!";
		return false;
	}
	const char* pszVal_qwGuildID = pElemChild->Attribute("value");
	if(pszVal_qwGuildID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwGuildID, s.qwGuildID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strGuildName is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strGuildName") != 0)
	{
		LOG_CRI << "Attribute: name is not strGuildName!";
		return false;
	}
	const char* pszVal_strGuildName = pElemChild->Attribute("value");
	if(pszVal_strGuildName == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strGuildName = pszVal_strGuildName;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strGuildOwnerName is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strGuildOwnerName") != 0)
	{
		LOG_CRI << "Attribute: name is not strGuildOwnerName!";
		return false;
	}
	const char* pszVal_strGuildOwnerName = pElemChild->Attribute("value");
	if(pszVal_strGuildOwnerName == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strGuildOwnerName = pszVal_strGuildOwnerName;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwTime!";
		return false;
	}
	const char* pszVal_dwTime = pElemChild->Attribute("value");
	if(pszVal_dwTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwTime, s.dwTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SOwnerHistoryInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SOwnerHistoryInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("占领历史信息"));
	unique_ptr<TiXmlElement> pElem_eMountainType(new TiXmlElement("ENGBMountain"));
	if(pElem_eMountainType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eMountainType->SetAttribute("name", "eMountainType");
	const char* pszEnum_eMountainType = EnumValToStr(s.eMountainType);
	if(pszEnum_eMountainType == NULL)
	{
		LOG_CRI << "EnumValToStr for ENGBMountain fails!";
		return false;
	}
	pElem_eMountainType->SetAttribute("value", pszEnum_eMountainType);
	pElem_eMountainType->SetAttribute("comment", ToUTF8Ptr("灵山类型"));
	if(rElement.LinkEndChild(pElem_eMountainType.get()) != NULL)
		pElem_eMountainType.release();
	unique_ptr<TiXmlElement> pElem_qwGuildID(new TiXmlElement("UINT64"));
	if(pElem_qwGuildID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwGuildID->SetAttribute("name", "qwGuildID");
	pElem_qwGuildID->SetAttribute("value", NumberToString(s.qwGuildID).c_str());
	pElem_qwGuildID->SetAttribute("comment", ToUTF8Ptr("当前占领帮派ID"));
	if(rElement.LinkEndChild(pElem_qwGuildID.get()) != NULL)
		pElem_qwGuildID.release();
	unique_ptr<TiXmlElement> pElem_strGuildName(new TiXmlElement("string"));
	if(pElem_strGuildName == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strGuildName->SetAttribute("name", "strGuildName");
	pElem_strGuildName->SetAttribute("value", s.strGuildName.c_str());
	pElem_strGuildName->SetAttribute("comment", ToUTF8Ptr("当前占领帮派名称"));
	if(rElement.LinkEndChild(pElem_strGuildName.get()) != NULL)
		pElem_strGuildName.release();
	unique_ptr<TiXmlElement> pElem_strGuildOwnerName(new TiXmlElement("string"));
	if(pElem_strGuildOwnerName == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strGuildOwnerName->SetAttribute("name", "strGuildOwnerName");
	pElem_strGuildOwnerName->SetAttribute("value", s.strGuildOwnerName.c_str());
	pElem_strGuildOwnerName->SetAttribute("comment", ToUTF8Ptr("当前占领帮派帮主名称"));
	if(rElement.LinkEndChild(pElem_strGuildOwnerName.get()) != NULL)
		pElem_strGuildOwnerName.release();
	unique_ptr<TiXmlElement> pElem_dwTime(new TiXmlElement("UINT32"));
	if(pElem_dwTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwTime->SetAttribute("name", "dwTime");
	pElem_dwTime->SetAttribute("value", NumberToString(s.dwTime).c_str());
	pElem_dwTime->SetAttribute("comment", ToUTF8Ptr("占领时间"));
	if(rElement.LinkEndChild(pElem_dwTime.get()) != NULL)
		pElem_dwTime.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecOwnerHistoryInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SOwnerHistoryInfo s;
		if(!FromXML(*pElemMember, s))
		{
			LOG_CRI << "FromXML fails!";
			return false;
		}
		vec.emplace_back(move(s));
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecOwnerHistoryInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SOwnerHistoryInfo"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!ToXML(vec[i], *pElemMember))
		{
			LOG_CRI << "ToXML fails!";
			return false;
		}
		if(rElement.LinkEndChild(pElemMember.get()) != NULL)
			pElemMember.release();
	}
	return true;
}

#endif

SMountainGateInfo::SMountainGateInfo() : dwRemainTime(0), dwGateMaxHP(0), dwGateHP(0), eSelfSide((ENGBSide)0) { }

SMountainGateInfo::SMountainGateInfo(UINT32 dwRemainTime_, UINT32 dwGateMaxHP_, UINT32 dwGateHP_, const TVecPuppetInfo& vecPuppetInfo_, ENGBSide eSelfSide_, 
			const SPlayerInfo& sSelfInfo_, const TVecPlayerPanelInfo& vecPlayerInfo_)
			: dwRemainTime(dwRemainTime_), dwGateMaxHP(dwGateMaxHP_), dwGateHP(dwGateHP_), vecPuppetInfo(vecPuppetInfo_), eSelfSide(eSelfSide_), 
			sSelfInfo(sSelfInfo_), vecPlayerInfo(vecPlayerInfo_) { }

SMountainGateInfo::SMountainGateInfo(SMountainGateInfo&& src) : dwRemainTime(src.dwRemainTime), dwGateMaxHP(src.dwGateMaxHP), dwGateHP(src.dwGateHP), vecPuppetInfo(move(src.vecPuppetInfo)), eSelfSide(src.eSelfSide), 
			sSelfInfo(move(src.sSelfInfo)), vecPlayerInfo(move(src.vecPlayerInfo)) { }

SMountainGateInfo& SMountainGateInfo::operator=(SMountainGateInfo&& rhs)
{
	if(this != &rhs)
	{
		this->~SMountainGateInfo();
		new (this) SMountainGateInfo(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SMountainGateInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.dwRemainTime;
	src >> s.dwGateMaxHP;
	src >> s.dwGateHP;
	src >> s.vecPuppetInfo;
	src >> (UINT8&)s.eSelfSide;
	src >> s.sSelfInfo;
	src >> s.vecPlayerInfo;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SMountainGateInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.dwRemainTime;
	src << s.dwGateMaxHP;
	src << s.dwGateHP;
	src << s.vecPuppetInfo;
	src << (UINT8&)s.eSelfSide;
	src << s.sSelfInfo;
	src << s.vecPlayerInfo;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SMountainGateInfo& s)
{
	if(strcmp(rElement.Value(), "SMountainGateInfo") != 0)
	{
		LOG_CRI << "rElement is not SMountainGateInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwRemainTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwRemainTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwRemainTime!";
		return false;
	}
	const char* pszVal_dwRemainTime = pElemChild->Attribute("value");
	if(pszVal_dwRemainTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwRemainTime, s.dwRemainTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwGateMaxHP is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwGateMaxHP") != 0)
	{
		LOG_CRI << "Attribute: name is not dwGateMaxHP!";
		return false;
	}
	const char* pszVal_dwGateMaxHP = pElemChild->Attribute("value");
	if(pszVal_dwGateMaxHP == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwGateMaxHP, s.dwGateMaxHP))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwGateHP is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwGateHP") != 0)
	{
		LOG_CRI << "Attribute: name is not dwGateHP!";
		return false;
	}
	const char* pszVal_dwGateHP = pElemChild->Attribute("value");
	if(pszVal_dwGateHP == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwGateHP, s.dwGateHP))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecPuppetInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecPuppetInfo") != 0)
	{
		LOG_CRI << "pElemChild is not TVecPuppetInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecPuppetInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not vecPuppetInfo!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecPuppetInfo))
	{
		LOG_CRI << "VectorFromXML for vecPuppetInfo fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eSelfSide is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "ENGBSide") != 0)
	{
		LOG_CRI << "pElemChild is not ENGBSide!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eSelfSide") != 0)
	{
		LOG_CRI << "Attribute: name is not eSelfSide!";
		return false;
	}
	const char* pszVal_eSelfSide = pElemChild->Attribute("value");
	if(pszVal_eSelfSide == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!EnumStrToVal(pszVal_eSelfSide, s.eSelfSide))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for sSelfInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "SPlayerInfo") != 0)
	{
		LOG_CRI << "pElemChild is not SPlayerInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "sSelfInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not sSelfInfo!";
		return false;
	}
	if(!FromXML(*pElemChild, s.sSelfInfo))
	{
		LOG_CRI << "FromXML for: sSelfInfo fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecPlayerInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecPlayerPanelInfo") != 0)
	{
		LOG_CRI << "pElemChild is not TVecPlayerPanelInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecPlayerInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not vecPlayerInfo!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecPlayerInfo))
	{
		LOG_CRI << "VectorFromXML for vecPlayerInfo fails!";
		return false;
	}
	return true;
}

bool ToXML(const SMountainGateInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SMountainGateInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("灵山城门信息"));
	unique_ptr<TiXmlElement> pElem_dwRemainTime(new TiXmlElement("UINT32"));
	if(pElem_dwRemainTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwRemainTime->SetAttribute("name", "dwRemainTime");
	pElem_dwRemainTime->SetAttribute("value", NumberToString(s.dwRemainTime).c_str());
	pElem_dwRemainTime->SetAttribute("comment", ToUTF8Ptr("开始倒计时"));
	if(rElement.LinkEndChild(pElem_dwRemainTime.get()) != NULL)
		pElem_dwRemainTime.release();
	unique_ptr<TiXmlElement> pElem_dwGateMaxHP(new TiXmlElement("UINT32"));
	if(pElem_dwGateMaxHP == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwGateMaxHP->SetAttribute("name", "dwGateMaxHP");
	pElem_dwGateMaxHP->SetAttribute("value", NumberToString(s.dwGateMaxHP).c_str());
	pElem_dwGateMaxHP->SetAttribute("comment", ToUTF8Ptr("城门总血量"));
	if(rElement.LinkEndChild(pElem_dwGateMaxHP.get()) != NULL)
		pElem_dwGateMaxHP.release();
	unique_ptr<TiXmlElement> pElem_dwGateHP(new TiXmlElement("UINT32"));
	if(pElem_dwGateHP == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwGateHP->SetAttribute("name", "dwGateHP");
	pElem_dwGateHP->SetAttribute("value", NumberToString(s.dwGateHP).c_str());
	pElem_dwGateHP->SetAttribute("comment", ToUTF8Ptr("城门剩余血量"));
	if(rElement.LinkEndChild(pElem_dwGateHP.get()) != NULL)
		pElem_dwGateHP.release();
	unique_ptr<TiXmlElement> pElem_vecPuppetInfo(new TiXmlElement("TVecPuppetInfo"));
	if(pElem_vecPuppetInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecPuppetInfo->SetAttribute("name", "vecPuppetInfo");
	if(!VectorToXML(s.vecPuppetInfo, *pElem_vecPuppetInfo))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecPuppetInfo->SetAttribute("comment", ToUTF8Ptr("傀儡信息"));
	if(rElement.LinkEndChild(pElem_vecPuppetInfo.get()) != NULL)
		pElem_vecPuppetInfo.release();
	unique_ptr<TiXmlElement> pElem_eSelfSide(new TiXmlElement("ENGBSide"));
	if(pElem_eSelfSide == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eSelfSide->SetAttribute("name", "eSelfSide");
	const char* pszEnum_eSelfSide = EnumValToStr(s.eSelfSide);
	if(pszEnum_eSelfSide == NULL)
	{
		LOG_CRI << "EnumValToStr for ENGBSide fails!";
		return false;
	}
	pElem_eSelfSide->SetAttribute("value", pszEnum_eSelfSide);
	pElem_eSelfSide->SetAttribute("comment", ToUTF8Ptr("自己所在方向"));
	if(rElement.LinkEndChild(pElem_eSelfSide.get()) != NULL)
		pElem_eSelfSide.release();
	unique_ptr<TiXmlElement> pElem_sSelfInfo(new TiXmlElement("SPlayerInfo"));
	if(pElem_sSelfInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_sSelfInfo->SetAttribute("name", "sSelfInfo");
	if(!ToXML(s.sSelfInfo, *pElem_sSelfInfo))
	{
		LOG_CRI << "sSelfInfo ToXML fails!";
		return false;
	}
	pElem_sSelfInfo->SetAttribute("comment", ToUTF8Ptr("自己的信息"));
	if(rElement.LinkEndChild(pElem_sSelfInfo.get()) != NULL)
		pElem_sSelfInfo.release();
	unique_ptr<TiXmlElement> pElem_vecPlayerInfo(new TiXmlElement("TVecPlayerPanelInfo"));
	if(pElem_vecPlayerInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecPlayerInfo->SetAttribute("name", "vecPlayerInfo");
	if(!VectorToXML(s.vecPlayerInfo, *pElem_vecPlayerInfo))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecPlayerInfo->SetAttribute("comment", ToUTF8Ptr("对面玩家信息"));
	if(rElement.LinkEndChild(pElem_vecPlayerInfo.get()) != NULL)
		pElem_vecPlayerInfo.release();
	return true;
}

#endif

SCaveCoreInfo::SCaveCoreInfo() : eType((ENGBCaveCore)0) { }

SCaveCoreInfo::SCaveCoreInfo(ENGBCaveCore eType_, const TVecPlayerPanelInfo& vecPlayerInfo_) : eType(eType_), vecPlayerInfo(vecPlayerInfo_) { }

SCaveCoreInfo::SCaveCoreInfo(SCaveCoreInfo&& src) : eType(src.eType), vecPlayerInfo(move(src.vecPlayerInfo)) { }

SCaveCoreInfo& SCaveCoreInfo::operator=(SCaveCoreInfo&& rhs)
{
	if(this != &rhs)
	{
		this->~SCaveCoreInfo();
		new (this) SCaveCoreInfo(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SCaveCoreInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (UINT8&)s.eType;
	src >> s.vecPlayerInfo;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SCaveCoreInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (UINT8&)s.eType;
	src << s.vecPlayerInfo;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SCaveCoreInfo& s)
{
	if(strcmp(rElement.Value(), "SCaveCoreInfo") != 0)
	{
		LOG_CRI << "rElement is not SCaveCoreInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "ENGBCaveCore") != 0)
	{
		LOG_CRI << "pElemChild is not ENGBCaveCore!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eType") != 0)
	{
		LOG_CRI << "Attribute: name is not eType!";
		return false;
	}
	const char* pszVal_eType = pElemChild->Attribute("value");
	if(pszVal_eType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!EnumStrToVal(pszVal_eType, s.eType))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecPlayerInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecPlayerPanelInfo") != 0)
	{
		LOG_CRI << "pElemChild is not TVecPlayerPanelInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecPlayerInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not vecPlayerInfo!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecPlayerInfo))
	{
		LOG_CRI << "VectorFromXML for vecPlayerInfo fails!";
		return false;
	}
	return true;
}

bool ToXML(const SCaveCoreInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SCaveCoreInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("洞府阵眼信息"));
	unique_ptr<TiXmlElement> pElem_eType(new TiXmlElement("ENGBCaveCore"));
	if(pElem_eType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eType->SetAttribute("name", "eType");
	const char* pszEnum_eType = EnumValToStr(s.eType);
	if(pszEnum_eType == NULL)
	{
		LOG_CRI << "EnumValToStr for ENGBCaveCore fails!";
		return false;
	}
	pElem_eType->SetAttribute("value", pszEnum_eType);
	pElem_eType->SetAttribute("comment", ToUTF8Ptr("阵眼类型"));
	if(rElement.LinkEndChild(pElem_eType.get()) != NULL)
		pElem_eType.release();
	unique_ptr<TiXmlElement> pElem_vecPlayerInfo(new TiXmlElement("TVecPlayerPanelInfo"));
	if(pElem_vecPlayerInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecPlayerInfo->SetAttribute("name", "vecPlayerInfo");
	if(!VectorToXML(s.vecPlayerInfo, *pElem_vecPlayerInfo))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecPlayerInfo->SetAttribute("comment", ToUTF8Ptr("占领者信息（数量只能为0/1）"));
	if(rElement.LinkEndChild(pElem_vecPlayerInfo.get()) != NULL)
		pElem_vecPlayerInfo.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecCaveCoreInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SCaveCoreInfo s;
		if(!FromXML(*pElemMember, s))
		{
			LOG_CRI << "FromXML fails!";
			return false;
		}
		vec.emplace_back(move(s));
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecCaveCoreInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SCaveCoreInfo"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!ToXML(vec[i], *pElemMember))
		{
			LOG_CRI << "ToXML fails!";
			return false;
		}
		if(rElement.LinkEndChild(pElemMember.get()) != NULL)
			pElemMember.release();
	}
	return true;
}

#endif

SCaveAttackGuildInfo::SCaveAttackGuildInfo() : qwGuildID(0), dwMaxEnergy(0), dwEnergy(0) { }

SCaveAttackGuildInfo::SCaveAttackGuildInfo(UINT64 qwGuildID_, const std::string& strName_, UINT32 dwMaxEnergy_, UINT32 dwEnergy_) : qwGuildID(qwGuildID_), strName(strName_), dwMaxEnergy(dwMaxEnergy_), dwEnergy(dwEnergy_) { }

SCaveAttackGuildInfo::SCaveAttackGuildInfo(SCaveAttackGuildInfo&& src) : qwGuildID(src.qwGuildID), strName(move(src.strName)), dwMaxEnergy(src.dwMaxEnergy), dwEnergy(src.dwEnergy) { }

SCaveAttackGuildInfo& SCaveAttackGuildInfo::operator=(SCaveAttackGuildInfo&& rhs)
{
	if(this != &rhs)
	{
		this->~SCaveAttackGuildInfo();
		new (this) SCaveAttackGuildInfo(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SCaveAttackGuildInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwGuildID;
	src >> s.strName;
	src >> s.dwMaxEnergy;
	src >> s.dwEnergy;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SCaveAttackGuildInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.qwGuildID;
	src << s.strName;
	src << s.dwMaxEnergy;
	src << s.dwEnergy;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SCaveAttackGuildInfo& s)
{
	if(strcmp(rElement.Value(), "SCaveAttackGuildInfo") != 0)
	{
		LOG_CRI << "rElement is not SCaveAttackGuildInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwGuildID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwGuildID") != 0)
	{
		LOG_CRI << "Attribute: name is not qwGuildID!";
		return false;
	}
	const char* pszVal_qwGuildID = pElemChild->Attribute("value");
	if(pszVal_qwGuildID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwGuildID, s.qwGuildID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strName is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strName") != 0)
	{
		LOG_CRI << "Attribute: name is not strName!";
		return false;
	}
	const char* pszVal_strName = pElemChild->Attribute("value");
	if(pszVal_strName == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strName = pszVal_strName;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwMaxEnergy is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwMaxEnergy") != 0)
	{
		LOG_CRI << "Attribute: name is not dwMaxEnergy!";
		return false;
	}
	const char* pszVal_dwMaxEnergy = pElemChild->Attribute("value");
	if(pszVal_dwMaxEnergy == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwMaxEnergy, s.dwMaxEnergy))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwEnergy is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwEnergy") != 0)
	{
		LOG_CRI << "Attribute: name is not dwEnergy!";
		return false;
	}
	const char* pszVal_dwEnergy = pElemChild->Attribute("value");
	if(pszVal_dwEnergy == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwEnergy, s.dwEnergy))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SCaveAttackGuildInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SCaveAttackGuildInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("洞府战攻击帮派信息"));
	unique_ptr<TiXmlElement> pElem_qwGuildID(new TiXmlElement("UINT64"));
	if(pElem_qwGuildID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwGuildID->SetAttribute("name", "qwGuildID");
	pElem_qwGuildID->SetAttribute("value", NumberToString(s.qwGuildID).c_str());
	pElem_qwGuildID->SetAttribute("comment", ToUTF8Ptr("帮派ID"));
	if(rElement.LinkEndChild(pElem_qwGuildID.get()) != NULL)
		pElem_qwGuildID.release();
	unique_ptr<TiXmlElement> pElem_strName(new TiXmlElement("string"));
	if(pElem_strName == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strName->SetAttribute("name", "strName");
	pElem_strName->SetAttribute("value", s.strName.c_str());
	pElem_strName->SetAttribute("comment", ToUTF8Ptr("帮派姓名"));
	if(rElement.LinkEndChild(pElem_strName.get()) != NULL)
		pElem_strName.release();
	unique_ptr<TiXmlElement> pElem_dwMaxEnergy(new TiXmlElement("UINT32"));
	if(pElem_dwMaxEnergy == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwMaxEnergy->SetAttribute("name", "dwMaxEnergy");
	pElem_dwMaxEnergy->SetAttribute("value", NumberToString(s.dwMaxEnergy).c_str());
	pElem_dwMaxEnergy->SetAttribute("comment", ToUTF8Ptr("能量上限"));
	if(rElement.LinkEndChild(pElem_dwMaxEnergy.get()) != NULL)
		pElem_dwMaxEnergy.release();
	unique_ptr<TiXmlElement> pElem_dwEnergy(new TiXmlElement("UINT32"));
	if(pElem_dwEnergy == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwEnergy->SetAttribute("name", "dwEnergy");
	pElem_dwEnergy->SetAttribute("value", NumberToString(s.dwEnergy).c_str());
	pElem_dwEnergy->SetAttribute("comment", ToUTF8Ptr("当前能量"));
	if(rElement.LinkEndChild(pElem_dwEnergy.get()) != NULL)
		pElem_dwEnergy.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecCaveAttackGuildInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SCaveAttackGuildInfo s;
		if(!FromXML(*pElemMember, s))
		{
			LOG_CRI << "FromXML fails!";
			return false;
		}
		vec.emplace_back(move(s));
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecCaveAttackGuildInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SCaveAttackGuildInfo"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!ToXML(vec[i], *pElemMember))
		{
			LOG_CRI << "ToXML fails!";
			return false;
		}
		if(rElement.LinkEndChild(pElemMember.get()) != NULL)
			pElemMember.release();
	}
	return true;
}

#endif

SCaveInfo::SCaveInfo() : dwRemainTime(0), eSelfSide((ENGBSide)0) { }

SCaveInfo::SCaveInfo(UINT32 dwRemainTime_, ENGBSide eSelfSide_, const TVecCaveCoreInfo& vecCaveCoreInfo_, const TVecCaveAttackGuildInfo& vecCaveAttackGuildInfo_, const SPlayerInfo& sSelfInfo_, 
			const TVecPlayerPanelInfo& vecPlayerInfo_)
			: dwRemainTime(dwRemainTime_), eSelfSide(eSelfSide_), vecCaveCoreInfo(vecCaveCoreInfo_), vecCaveAttackGuildInfo(vecCaveAttackGuildInfo_), sSelfInfo(sSelfInfo_), 
			vecPlayerInfo(vecPlayerInfo_) { }

SCaveInfo::SCaveInfo(SCaveInfo&& src) : dwRemainTime(src.dwRemainTime), eSelfSide(src.eSelfSide), vecCaveCoreInfo(move(src.vecCaveCoreInfo)), vecCaveAttackGuildInfo(move(src.vecCaveAttackGuildInfo)), sSelfInfo(move(src.sSelfInfo)), 
			vecPlayerInfo(move(src.vecPlayerInfo)) { }

SCaveInfo& SCaveInfo::operator=(SCaveInfo&& rhs)
{
	if(this != &rhs)
	{
		this->~SCaveInfo();
		new (this) SCaveInfo(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SCaveInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.dwRemainTime;
	src >> (UINT8&)s.eSelfSide;
	src >> s.vecCaveCoreInfo;
	src >> s.vecCaveAttackGuildInfo;
	src >> s.sSelfInfo;
	src >> s.vecPlayerInfo;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SCaveInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.dwRemainTime;
	src << (UINT8&)s.eSelfSide;
	src << s.vecCaveCoreInfo;
	src << s.vecCaveAttackGuildInfo;
	src << s.sSelfInfo;
	src << s.vecPlayerInfo;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SCaveInfo& s)
{
	if(strcmp(rElement.Value(), "SCaveInfo") != 0)
	{
		LOG_CRI << "rElement is not SCaveInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwRemainTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwRemainTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwRemainTime!";
		return false;
	}
	const char* pszVal_dwRemainTime = pElemChild->Attribute("value");
	if(pszVal_dwRemainTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwRemainTime, s.dwRemainTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eSelfSide is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "ENGBSide") != 0)
	{
		LOG_CRI << "pElemChild is not ENGBSide!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eSelfSide") != 0)
	{
		LOG_CRI << "Attribute: name is not eSelfSide!";
		return false;
	}
	const char* pszVal_eSelfSide = pElemChild->Attribute("value");
	if(pszVal_eSelfSide == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!EnumStrToVal(pszVal_eSelfSide, s.eSelfSide))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecCaveCoreInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecCaveCoreInfo") != 0)
	{
		LOG_CRI << "pElemChild is not TVecCaveCoreInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecCaveCoreInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not vecCaveCoreInfo!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecCaveCoreInfo))
	{
		LOG_CRI << "VectorFromXML for vecCaveCoreInfo fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecCaveAttackGuildInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecCaveAttackGuildInfo") != 0)
	{
		LOG_CRI << "pElemChild is not TVecCaveAttackGuildInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecCaveAttackGuildInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not vecCaveAttackGuildInfo!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecCaveAttackGuildInfo))
	{
		LOG_CRI << "VectorFromXML for vecCaveAttackGuildInfo fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for sSelfInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "SPlayerInfo") != 0)
	{
		LOG_CRI << "pElemChild is not SPlayerInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "sSelfInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not sSelfInfo!";
		return false;
	}
	if(!FromXML(*pElemChild, s.sSelfInfo))
	{
		LOG_CRI << "FromXML for: sSelfInfo fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecPlayerInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecPlayerPanelInfo") != 0)
	{
		LOG_CRI << "pElemChild is not TVecPlayerPanelInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecPlayerInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not vecPlayerInfo!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecPlayerInfo))
	{
		LOG_CRI << "VectorFromXML for vecPlayerInfo fails!";
		return false;
	}
	return true;
}

bool ToXML(const SCaveInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SCaveInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("洞府战具体信息"));
	unique_ptr<TiXmlElement> pElem_dwRemainTime(new TiXmlElement("UINT32"));
	if(pElem_dwRemainTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwRemainTime->SetAttribute("name", "dwRemainTime");
	pElem_dwRemainTime->SetAttribute("value", NumberToString(s.dwRemainTime).c_str());
	pElem_dwRemainTime->SetAttribute("comment", ToUTF8Ptr("开始倒计时"));
	if(rElement.LinkEndChild(pElem_dwRemainTime.get()) != NULL)
		pElem_dwRemainTime.release();
	unique_ptr<TiXmlElement> pElem_eSelfSide(new TiXmlElement("ENGBSide"));
	if(pElem_eSelfSide == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eSelfSide->SetAttribute("name", "eSelfSide");
	const char* pszEnum_eSelfSide = EnumValToStr(s.eSelfSide);
	if(pszEnum_eSelfSide == NULL)
	{
		LOG_CRI << "EnumValToStr for ENGBSide fails!";
		return false;
	}
	pElem_eSelfSide->SetAttribute("value", pszEnum_eSelfSide);
	pElem_eSelfSide->SetAttribute("comment", ToUTF8Ptr("自己所在方向"));
	if(rElement.LinkEndChild(pElem_eSelfSide.get()) != NULL)
		pElem_eSelfSide.release();
	unique_ptr<TiXmlElement> pElem_vecCaveCoreInfo(new TiXmlElement("TVecCaveCoreInfo"));
	if(pElem_vecCaveCoreInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecCaveCoreInfo->SetAttribute("name", "vecCaveCoreInfo");
	if(!VectorToXML(s.vecCaveCoreInfo, *pElem_vecCaveCoreInfo))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecCaveCoreInfo->SetAttribute("comment", ToUTF8Ptr("阵眼信息"));
	if(rElement.LinkEndChild(pElem_vecCaveCoreInfo.get()) != NULL)
		pElem_vecCaveCoreInfo.release();
	unique_ptr<TiXmlElement> pElem_vecCaveAttackGuildInfo(new TiXmlElement("TVecCaveAttackGuildInfo"));
	if(pElem_vecCaveAttackGuildInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecCaveAttackGuildInfo->SetAttribute("name", "vecCaveAttackGuildInfo");
	if(!VectorToXML(s.vecCaveAttackGuildInfo, *pElem_vecCaveAttackGuildInfo))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecCaveAttackGuildInfo->SetAttribute("comment", ToUTF8Ptr("洞府攻击帮派信息"));
	if(rElement.LinkEndChild(pElem_vecCaveAttackGuildInfo.get()) != NULL)
		pElem_vecCaveAttackGuildInfo.release();
	unique_ptr<TiXmlElement> pElem_sSelfInfo(new TiXmlElement("SPlayerInfo"));
	if(pElem_sSelfInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_sSelfInfo->SetAttribute("name", "sSelfInfo");
	if(!ToXML(s.sSelfInfo, *pElem_sSelfInfo))
	{
		LOG_CRI << "sSelfInfo ToXML fails!";
		return false;
	}
	pElem_sSelfInfo->SetAttribute("comment", ToUTF8Ptr("自己的信息"));
	if(rElement.LinkEndChild(pElem_sSelfInfo.get()) != NULL)
		pElem_sSelfInfo.release();
	unique_ptr<TiXmlElement> pElem_vecPlayerInfo(new TiXmlElement("TVecPlayerPanelInfo"));
	if(pElem_vecPlayerInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecPlayerInfo->SetAttribute("name", "vecPlayerInfo");
	if(!VectorToXML(s.vecPlayerInfo, *pElem_vecPlayerInfo))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecPlayerInfo->SetAttribute("comment", ToUTF8Ptr("对面玩家信息"));
	if(rElement.LinkEndChild(pElem_vecPlayerInfo.get()) != NULL)
		pElem_vecPlayerInfo.release();
	return true;
}

#endif

SGuildRankInfo::SGuildRankInfo() : wRank(0), qwGuildID(0), dwScore(0) { }

SGuildRankInfo::SGuildRankInfo(UINT16 wRank_, UINT64 qwGuildID_, const std::string& strName_, UINT32 dwScore_) : wRank(wRank_), qwGuildID(qwGuildID_), strName(strName_), dwScore(dwScore_) { }

SGuildRankInfo::SGuildRankInfo(SGuildRankInfo&& src) : wRank(src.wRank), qwGuildID(src.qwGuildID), strName(move(src.strName)), dwScore(src.dwScore) { }

SGuildRankInfo& SGuildRankInfo::operator=(SGuildRankInfo&& rhs)
{
	if(this != &rhs)
	{
		this->~SGuildRankInfo();
		new (this) SGuildRankInfo(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SGuildRankInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.wRank;
	src >> s.qwGuildID;
	src >> s.strName;
	src >> s.dwScore;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SGuildRankInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.wRank;
	src << s.qwGuildID;
	src << s.strName;
	src << s.dwScore;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SGuildRankInfo& s)
{
	if(strcmp(rElement.Value(), "SGuildRankInfo") != 0)
	{
		LOG_CRI << "rElement is not SGuildRankInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wRank is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wRank") != 0)
	{
		LOG_CRI << "Attribute: name is not wRank!";
		return false;
	}
	const char* pszVal_wRank = pElemChild->Attribute("value");
	if(pszVal_wRank == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wRank, s.wRank))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwGuildID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwGuildID") != 0)
	{
		LOG_CRI << "Attribute: name is not qwGuildID!";
		return false;
	}
	const char* pszVal_qwGuildID = pElemChild->Attribute("value");
	if(pszVal_qwGuildID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwGuildID, s.qwGuildID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strName is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strName") != 0)
	{
		LOG_CRI << "Attribute: name is not strName!";
		return false;
	}
	const char* pszVal_strName = pElemChild->Attribute("value");
	if(pszVal_strName == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strName = pszVal_strName;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwScore is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwScore") != 0)
	{
		LOG_CRI << "Attribute: name is not dwScore!";
		return false;
	}
	const char* pszVal_dwScore = pElemChild->Attribute("value");
	if(pszVal_dwScore == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwScore, s.dwScore))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SGuildRankInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SGuildRankInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("排行榜帮派信息"));
	unique_ptr<TiXmlElement> pElem_wRank(new TiXmlElement("UINT16"));
	if(pElem_wRank == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wRank->SetAttribute("name", "wRank");
	pElem_wRank->SetAttribute("value", NumberToString(s.wRank).c_str());
	pElem_wRank->SetAttribute("comment", ToUTF8Ptr("排名"));
	if(rElement.LinkEndChild(pElem_wRank.get()) != NULL)
		pElem_wRank.release();
	unique_ptr<TiXmlElement> pElem_qwGuildID(new TiXmlElement("UINT64"));
	if(pElem_qwGuildID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwGuildID->SetAttribute("name", "qwGuildID");
	pElem_qwGuildID->SetAttribute("value", NumberToString(s.qwGuildID).c_str());
	pElem_qwGuildID->SetAttribute("comment", ToUTF8Ptr("帮派ID"));
	if(rElement.LinkEndChild(pElem_qwGuildID.get()) != NULL)
		pElem_qwGuildID.release();
	unique_ptr<TiXmlElement> pElem_strName(new TiXmlElement("string"));
	if(pElem_strName == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strName->SetAttribute("name", "strName");
	pElem_strName->SetAttribute("value", s.strName.c_str());
	pElem_strName->SetAttribute("comment", ToUTF8Ptr("帮派姓名"));
	if(rElement.LinkEndChild(pElem_strName.get()) != NULL)
		pElem_strName.release();
	unique_ptr<TiXmlElement> pElem_dwScore(new TiXmlElement("UINT32"));
	if(pElem_dwScore == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwScore->SetAttribute("name", "dwScore");
	pElem_dwScore->SetAttribute("value", NumberToString(s.dwScore).c_str());
	pElem_dwScore->SetAttribute("comment", ToUTF8Ptr("战功"));
	if(rElement.LinkEndChild(pElem_dwScore.get()) != NULL)
		pElem_dwScore.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecGuildRankInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SGuildRankInfo s;
		if(!FromXML(*pElemMember, s))
		{
			LOG_CRI << "FromXML fails!";
			return false;
		}
		vec.emplace_back(move(s));
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecGuildRankInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SGuildRankInfo"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!ToXML(vec[i], *pElemMember))
		{
			LOG_CRI << "ToXML fails!";
			return false;
		}
		if(rElement.LinkEndChild(pElemMember.get()) != NULL)
			pElemMember.release();
	}
	return true;
}

#endif

SGuildMemberRankInfo::SGuildMemberRankInfo() : wRank(0), qwGuildID(0), qwRoleID(0), dwScore(0) { }

SGuildMemberRankInfo::SGuildMemberRankInfo(UINT16 wRank_, UINT64 qwGuildID_, UINT64 qwRoleID_, const std::string& strName_, UINT32 dwScore_)
			: wRank(wRank_), qwGuildID(qwGuildID_), qwRoleID(qwRoleID_), strName(strName_), dwScore(dwScore_) { }

SGuildMemberRankInfo::SGuildMemberRankInfo(SGuildMemberRankInfo&& src) : wRank(src.wRank), qwGuildID(src.qwGuildID), qwRoleID(src.qwRoleID), strName(move(src.strName)), dwScore(src.dwScore) { }

SGuildMemberRankInfo& SGuildMemberRankInfo::operator=(SGuildMemberRankInfo&& rhs)
{
	if(this != &rhs)
	{
		this->~SGuildMemberRankInfo();
		new (this) SGuildMemberRankInfo(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SGuildMemberRankInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.wRank;
	src >> s.qwGuildID;
	src >> s.qwRoleID;
	src >> s.strName;
	src >> s.dwScore;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SGuildMemberRankInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.wRank;
	src << s.qwGuildID;
	src << s.qwRoleID;
	src << s.strName;
	src << s.dwScore;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SGuildMemberRankInfo& s)
{
	if(strcmp(rElement.Value(), "SGuildMemberRankInfo") != 0)
	{
		LOG_CRI << "rElement is not SGuildMemberRankInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wRank is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wRank") != 0)
	{
		LOG_CRI << "Attribute: name is not wRank!";
		return false;
	}
	const char* pszVal_wRank = pElemChild->Attribute("value");
	if(pszVal_wRank == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wRank, s.wRank))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwGuildID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwGuildID") != 0)
	{
		LOG_CRI << "Attribute: name is not qwGuildID!";
		return false;
	}
	const char* pszVal_qwGuildID = pElemChild->Attribute("value");
	if(pszVal_qwGuildID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwGuildID, s.qwGuildID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwRoleID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwRoleID") != 0)
	{
		LOG_CRI << "Attribute: name is not qwRoleID!";
		return false;
	}
	const char* pszVal_qwRoleID = pElemChild->Attribute("value");
	if(pszVal_qwRoleID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwRoleID, s.qwRoleID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strName is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strName") != 0)
	{
		LOG_CRI << "Attribute: name is not strName!";
		return false;
	}
	const char* pszVal_strName = pElemChild->Attribute("value");
	if(pszVal_strName == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strName = pszVal_strName;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwScore is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwScore") != 0)
	{
		LOG_CRI << "Attribute: name is not dwScore!";
		return false;
	}
	const char* pszVal_dwScore = pElemChild->Attribute("value");
	if(pszVal_dwScore == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwScore, s.dwScore))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SGuildMemberRankInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SGuildMemberRankInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("排行榜帮派信息"));
	unique_ptr<TiXmlElement> pElem_wRank(new TiXmlElement("UINT16"));
	if(pElem_wRank == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wRank->SetAttribute("name", "wRank");
	pElem_wRank->SetAttribute("value", NumberToString(s.wRank).c_str());
	pElem_wRank->SetAttribute("comment", ToUTF8Ptr("排名"));
	if(rElement.LinkEndChild(pElem_wRank.get()) != NULL)
		pElem_wRank.release();
	unique_ptr<TiXmlElement> pElem_qwGuildID(new TiXmlElement("UINT64"));
	if(pElem_qwGuildID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwGuildID->SetAttribute("name", "qwGuildID");
	pElem_qwGuildID->SetAttribute("value", NumberToString(s.qwGuildID).c_str());
	pElem_qwGuildID->SetAttribute("comment", ToUTF8Ptr("帮派ID"));
	if(rElement.LinkEndChild(pElem_qwGuildID.get()) != NULL)
		pElem_qwGuildID.release();
	unique_ptr<TiXmlElement> pElem_qwRoleID(new TiXmlElement("UINT64"));
	if(pElem_qwRoleID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwRoleID->SetAttribute("name", "qwRoleID");
	pElem_qwRoleID->SetAttribute("value", NumberToString(s.qwRoleID).c_str());
	pElem_qwRoleID->SetAttribute("comment", ToUTF8Ptr("玩家ID"));
	if(rElement.LinkEndChild(pElem_qwRoleID.get()) != NULL)
		pElem_qwRoleID.release();
	unique_ptr<TiXmlElement> pElem_strName(new TiXmlElement("string"));
	if(pElem_strName == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strName->SetAttribute("name", "strName");
	pElem_strName->SetAttribute("value", s.strName.c_str());
	pElem_strName->SetAttribute("comment", ToUTF8Ptr("玩家姓名"));
	if(rElement.LinkEndChild(pElem_strName.get()) != NULL)
		pElem_strName.release();
	unique_ptr<TiXmlElement> pElem_dwScore(new TiXmlElement("UINT32"));
	if(pElem_dwScore == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwScore->SetAttribute("name", "dwScore");
	pElem_dwScore->SetAttribute("value", NumberToString(s.dwScore).c_str());
	pElem_dwScore->SetAttribute("comment", ToUTF8Ptr("战功"));
	if(rElement.LinkEndChild(pElem_dwScore.get()) != NULL)
		pElem_dwScore.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecGuildMemberRankInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SGuildMemberRankInfo s;
		if(!FromXML(*pElemMember, s))
		{
			LOG_CRI << "FromXML fails!";
			return false;
		}
		vec.emplace_back(move(s));
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecGuildMemberRankInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SGuildMemberRankInfo"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!ToXML(vec[i], *pElemMember))
		{
			LOG_CRI << "ToXML fails!";
			return false;
		}
		if(rElement.LinkEndChild(pElemMember.get()) != NULL)
			pElemMember.release();
	}
	return true;
}

#endif

SPlayerRankInfo::SPlayerRankInfo() : wRank(0), qwRoleID(0), dwScore(0) { }

SPlayerRankInfo::SPlayerRankInfo(UINT16 wRank_, UINT64 qwRoleID_, const std::string& strName_, UINT32 dwScore_) : wRank(wRank_), qwRoleID(qwRoleID_), strName(strName_), dwScore(dwScore_) { }

SPlayerRankInfo::SPlayerRankInfo(SPlayerRankInfo&& src) : wRank(src.wRank), qwRoleID(src.qwRoleID), strName(move(src.strName)), dwScore(src.dwScore) { }

SPlayerRankInfo& SPlayerRankInfo::operator=(SPlayerRankInfo&& rhs)
{
	if(this != &rhs)
	{
		this->~SPlayerRankInfo();
		new (this) SPlayerRankInfo(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SPlayerRankInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.wRank;
	src >> s.qwRoleID;
	src >> s.strName;
	src >> s.dwScore;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SPlayerRankInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.wRank;
	src << s.qwRoleID;
	src << s.strName;
	src << s.dwScore;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SPlayerRankInfo& s)
{
	if(strcmp(rElement.Value(), "SPlayerRankInfo") != 0)
	{
		LOG_CRI << "rElement is not SPlayerRankInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wRank is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wRank") != 0)
	{
		LOG_CRI << "Attribute: name is not wRank!";
		return false;
	}
	const char* pszVal_wRank = pElemChild->Attribute("value");
	if(pszVal_wRank == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wRank, s.wRank))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwRoleID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwRoleID") != 0)
	{
		LOG_CRI << "Attribute: name is not qwRoleID!";
		return false;
	}
	const char* pszVal_qwRoleID = pElemChild->Attribute("value");
	if(pszVal_qwRoleID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwRoleID, s.qwRoleID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strName is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strName") != 0)
	{
		LOG_CRI << "Attribute: name is not strName!";
		return false;
	}
	const char* pszVal_strName = pElemChild->Attribute("value");
	if(pszVal_strName == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strName = pszVal_strName;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwScore is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwScore") != 0)
	{
		LOG_CRI << "Attribute: name is not dwScore!";
		return false;
	}
	const char* pszVal_dwScore = pElemChild->Attribute("value");
	if(pszVal_dwScore == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwScore, s.dwScore))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SPlayerRankInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SPlayerRankInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("排行榜个人信息"));
	unique_ptr<TiXmlElement> pElem_wRank(new TiXmlElement("UINT16"));
	if(pElem_wRank == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wRank->SetAttribute("name", "wRank");
	pElem_wRank->SetAttribute("value", NumberToString(s.wRank).c_str());
	pElem_wRank->SetAttribute("comment", ToUTF8Ptr("排名"));
	if(rElement.LinkEndChild(pElem_wRank.get()) != NULL)
		pElem_wRank.release();
	unique_ptr<TiXmlElement> pElem_qwRoleID(new TiXmlElement("UINT64"));
	if(pElem_qwRoleID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwRoleID->SetAttribute("name", "qwRoleID");
	pElem_qwRoleID->SetAttribute("value", NumberToString(s.qwRoleID).c_str());
	pElem_qwRoleID->SetAttribute("comment", ToUTF8Ptr("玩家ID"));
	if(rElement.LinkEndChild(pElem_qwRoleID.get()) != NULL)
		pElem_qwRoleID.release();
	unique_ptr<TiXmlElement> pElem_strName(new TiXmlElement("string"));
	if(pElem_strName == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strName->SetAttribute("name", "strName");
	pElem_strName->SetAttribute("value", s.strName.c_str());
	pElem_strName->SetAttribute("comment", ToUTF8Ptr("玩家姓名"));
	if(rElement.LinkEndChild(pElem_strName.get()) != NULL)
		pElem_strName.release();
	unique_ptr<TiXmlElement> pElem_dwScore(new TiXmlElement("UINT32"));
	if(pElem_dwScore == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwScore->SetAttribute("name", "dwScore");
	pElem_dwScore->SetAttribute("value", NumberToString(s.dwScore).c_str());
	pElem_dwScore->SetAttribute("comment", ToUTF8Ptr("战功"));
	if(rElement.LinkEndChild(pElem_dwScore.get()) != NULL)
		pElem_dwScore.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecPlayerRankInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SPlayerRankInfo s;
		if(!FromXML(*pElemMember, s))
		{
			LOG_CRI << "FromXML fails!";
			return false;
		}
		vec.emplace_back(move(s));
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecPlayerRankInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SPlayerRankInfo"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!ToXML(vec[i], *pElemMember))
		{
			LOG_CRI << "ToXML fails!";
			return false;
		}
		if(rElement.LinkEndChild(pElemMember.get()) != NULL)
			pElemMember.release();
	}
	return true;
}

#endif

} //namespace NNewGuildBattleProt
