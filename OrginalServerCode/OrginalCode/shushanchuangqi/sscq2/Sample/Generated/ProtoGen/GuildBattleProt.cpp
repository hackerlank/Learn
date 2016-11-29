/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    GuildBattleProt.cpp
//  Purpose:      帮派相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "GuildBattleProt.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NGuildBattleProt
{

#ifdef PROT_USE_XML

const char* EnumValToStr(EGBState e)
{
	switch(e)
	{
	case eGBStateNone:
		return "eGBStateNone";
	case eGBStatePreReady:
		return "eGBStatePreReady";
	case eGBStateReady:
		return "eGBStateReady";
	case eGBStatePrepare:
		return "eGBStatePrepare";
	case eGBStateBattle:
		return "eGBStateBattle";
	case eGBStateBattleEnd:
		return "eGBStateBattleEnd";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EGBState& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EGBState> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eGBStateNone", eGBStateNone));
		mapStr2Val.insert(make_pair("eGBStatePreReady", eGBStatePreReady));
		mapStr2Val.insert(make_pair("eGBStateReady", eGBStateReady));
		mapStr2Val.insert(make_pair("eGBStatePrepare", eGBStatePrepare));
		mapStr2Val.insert(make_pair("eGBStateBattle", eGBStateBattle));
		mapStr2Val.insert(make_pair("eGBStateBattleEnd", eGBStateBattleEnd));
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

const char* EnumValToStr(EGBUserState e)
{
	switch(e)
	{
	case eGBUserStateNone:
		return "eGBUserStateNone";
	case eGBUserStatePrepare:
		return "eGBUserStatePrepare";
	case eGBUserStateWait:
		return "eGBUserStateWait";
	case eGBUserStateBattle:
		return "eGBUserStateBattle";
	case eGBUserStateDead:
		return "eGBUserStateDead";
	case eGBUserStateWin:
		return "eGBUserStateWin";
	case eGBUserStateWinTooMuch:
		return "eGBUserStateWinTooMuch";
	case eGBUserStateRunAway:
		return "eGBUserStateRunAway";
	case eGBUserStateMax:
		return "eGBUserStateMax";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EGBUserState& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EGBUserState> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eGBUserStateNone", eGBUserStateNone));
		mapStr2Val.insert(make_pair("eGBUserStatePrepare", eGBUserStatePrepare));
		mapStr2Val.insert(make_pair("eGBUserStateWait", eGBUserStateWait));
		mapStr2Val.insert(make_pair("eGBUserStateBattle", eGBUserStateBattle));
		mapStr2Val.insert(make_pair("eGBUserStateDead", eGBUserStateDead));
		mapStr2Val.insert(make_pair("eGBUserStateWin", eGBUserStateWin));
		mapStr2Val.insert(make_pair("eGBUserStateWinTooMuch", eGBUserStateWinTooMuch));
		mapStr2Val.insert(make_pair("eGBUserStateRunAway", eGBUserStateRunAway));
		mapStr2Val.insert(make_pair("eGBUserStateMax", eGBUserStateMax));
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

const char* EnumValToStr(EGBSpot e)
{
	switch(e)
	{
	case eGBSpotNone:
		return "eGBSpotNone";
	case eGBSpotYuzhufeng:
		return "eGBSpotYuzhufeng";
	case eGBSpotGuangmingding:
		return "eGBSpotGuangmingding";
	case eGBSpotShiwangfeng:
		return "eGBSpotShiwangfeng";
	case eGBSpotWanfoding:
		return "eGBSpotWanfoding";
	case eGBSpotMax:
		return "eGBSpotMax";
	case eGBSpotYuxuding:
		return "eGBSpotYuxuding";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EGBSpot& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EGBSpot> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eGBSpotNone", eGBSpotNone));
		mapStr2Val.insert(make_pair("eGBSpotYuzhufeng", eGBSpotYuzhufeng));
		mapStr2Val.insert(make_pair("eGBSpotGuangmingding", eGBSpotGuangmingding));
		mapStr2Val.insert(make_pair("eGBSpotShiwangfeng", eGBSpotShiwangfeng));
		mapStr2Val.insert(make_pair("eGBSpotWanfoding", eGBSpotWanfoding));
		mapStr2Val.insert(make_pair("eGBSpotMax", eGBSpotMax));
		mapStr2Val.insert(make_pair("eGBSpotYuxuding", eGBSpotYuxuding));
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

const char* EnumValToStr(EGBSpotState e)
{
	switch(e)
	{
	case eGBSpotStateNone:
		return "eGBSpotStateNone";
	case eGBSpotStateWin:
		return "eGBSpotStateWin";
	case eGBSpotStateLose:
		return "eGBSpotStateLose";
	case eGBSpotStateTie:
		return "eGBSpotStateTie";
	case eGBSpotStateBattle:
		return "eGBSpotStateBattle";
	case eGBSpotStateNobody:
		return "eGBSpotStateNobody";
	case eGBSpotStateMax:
		return "eGBSpotStateMax";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EGBSpotState& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EGBSpotState> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eGBSpotStateNone", eGBSpotStateNone));
		mapStr2Val.insert(make_pair("eGBSpotStateWin", eGBSpotStateWin));
		mapStr2Val.insert(make_pair("eGBSpotStateLose", eGBSpotStateLose));
		mapStr2Val.insert(make_pair("eGBSpotStateTie", eGBSpotStateTie));
		mapStr2Val.insert(make_pair("eGBSpotStateBattle", eGBSpotStateBattle));
		mapStr2Val.insert(make_pair("eGBSpotStateNobody", eGBSpotStateNobody));
		mapStr2Val.insert(make_pair("eGBSpotStateMax", eGBSpotStateMax));
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

const char* EnumValToStr(EGBSide e)
{
	switch(e)
	{
	case eGBSideA:
		return "eGBSideA";
	case eGBSideB:
		return "eGBSideB";
	case eGBSideInvalid:
		return "eGBSideInvalid";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EGBSide& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EGBSide> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eGBSideA", eGBSideA));
		mapStr2Val.insert(make_pair("eGBSideB", eGBSideB));
		mapStr2Val.insert(make_pair("eGBSideInvalid", eGBSideInvalid));
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

const char* EnumValToStr(EGBSkill e)
{
	switch(e)
	{
	case eGBSkillNone:
		return "eGBSkillNone";
	case eGBSkillAttack:
		return "eGBSkillAttack";
	case eGBSkillDefence:
		return "eGBSkillDefence";
	case eGBSkillSpeed:
		return "eGBSkillSpeed";
	case eGBSkillHP:
		return "eGBSkillHP";
	case eGBSkillMax:
		return "eGBSkillMax";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EGBSkill& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EGBSkill> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eGBSkillNone", eGBSkillNone));
		mapStr2Val.insert(make_pair("eGBSkillAttack", eGBSkillAttack));
		mapStr2Val.insert(make_pair("eGBSkillDefence", eGBSkillDefence));
		mapStr2Val.insert(make_pair("eGBSkillSpeed", eGBSkillSpeed));
		mapStr2Val.insert(make_pair("eGBSkillHP", eGBSkillHP));
		mapStr2Val.insert(make_pair("eGBSkillMax", eGBSkillMax));
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

const char* EnumValToStr(EGBResult e)
{
	switch(e)
	{
	case eGBResultSuccess:
		return "eGBResultSuccess";
	case eGBResultFailed:
		return "eGBResultFailed";
	case eGBResultWrongTime:
		return "eGBResultWrongTime";
	case eGBResultNotInBattle:
		return "eGBResultNotInBattle";
	case eGBResultNoGuild:
		return "eGBResultNoGuild";
	case eGBResultNoAuthority:
		return "eGBResultNoAuthority";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EGBResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EGBResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eGBResultSuccess", eGBResultSuccess));
		mapStr2Val.insert(make_pair("eGBResultFailed", eGBResultFailed));
		mapStr2Val.insert(make_pair("eGBResultWrongTime", eGBResultWrongTime));
		mapStr2Val.insert(make_pair("eGBResultNotInBattle", eGBResultNotInBattle));
		mapStr2Val.insert(make_pair("eGBResultNoGuild", eGBResultNoGuild));
		mapStr2Val.insert(make_pair("eGBResultNoAuthority", eGBResultNoAuthority));
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

const char* EnumValToStr(EGBSignUpResult e)
{
	switch(e)
	{
	case eGBSignUpSuccess:
		return "eGBSignUpSuccess";
	case eGBSignUpFailed:
		return "eGBSignUpFailed";
	case eGBSignUpNotInGuild:
		return "eGBSignUpNotInGuild";
	case eGBSignUpRepeat:
		return "eGBSignUpRepeat";
	case eGBSignUpWrongTime:
		return "eGBSignUpWrongTime";
	case eGBSignUpSpotFull:
		return "eGBSignUpSpotFull";
	case eGBSignUpEscape:
		return "eGBSignUpEscape";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EGBSignUpResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EGBSignUpResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eGBSignUpSuccess", eGBSignUpSuccess));
		mapStr2Val.insert(make_pair("eGBSignUpFailed", eGBSignUpFailed));
		mapStr2Val.insert(make_pair("eGBSignUpNotInGuild", eGBSignUpNotInGuild));
		mapStr2Val.insert(make_pair("eGBSignUpRepeat", eGBSignUpRepeat));
		mapStr2Val.insert(make_pair("eGBSignUpWrongTime", eGBSignUpWrongTime));
		mapStr2Val.insert(make_pair("eGBSignUpSpotFull", eGBSignUpSpotFull));
		mapStr2Val.insert(make_pair("eGBSignUpEscape", eGBSignUpEscape));
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

const char* EnumValToStr(EGBEnterResult e)
{
	switch(e)
	{
	case eGBEnterSuccess:
		return "eGBEnterSuccess";
	case eGBEnterFailed:
		return "eGBEnterFailed";
	case eGBEnterNotInGuild:
		return "eGBEnterNotInGuild";
	case eGBEnterRepeat:
		return "eGBEnterRepeat";
	case eGBEnterWrongTime:
		return "eGBEnterWrongTime";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EGBEnterResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EGBEnterResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eGBEnterSuccess", eGBEnterSuccess));
		mapStr2Val.insert(make_pair("eGBEnterFailed", eGBEnterFailed));
		mapStr2Val.insert(make_pair("eGBEnterNotInGuild", eGBEnterNotInGuild));
		mapStr2Val.insert(make_pair("eGBEnterRepeat", eGBEnterRepeat));
		mapStr2Val.insert(make_pair("eGBEnterWrongTime", eGBEnterWrongTime));
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

const char* EnumValToStr(EGBQuitResult e)
{
	switch(e)
	{
	case eGBQuitSuccess:
		return "eGBQuitSuccess";
	case eGBQuitFailed:
		return "eGBQuitFailed";
	case eGBQuitNotInGuild:
		return "eGBQuitNotInGuild";
	case eGBQuitNotInBattle:
		return "eGBQuitNotInBattle";
	case eGBQuitRepeat:
		return "eGBQuitRepeat";
	case eGBQuitWrongTime:
		return "eGBQuitWrongTime";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EGBQuitResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EGBQuitResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eGBQuitSuccess", eGBQuitSuccess));
		mapStr2Val.insert(make_pair("eGBQuitFailed", eGBQuitFailed));
		mapStr2Val.insert(make_pair("eGBQuitNotInGuild", eGBQuitNotInGuild));
		mapStr2Val.insert(make_pair("eGBQuitNotInBattle", eGBQuitNotInBattle));
		mapStr2Val.insert(make_pair("eGBQuitRepeat", eGBQuitRepeat));
		mapStr2Val.insert(make_pair("eGBQuitWrongTime", eGBQuitWrongTime));
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

const char* EnumValToStr(EGBAdjustResult e)
{
	switch(e)
	{
	case eGBAdjustSuccess:
		return "eGBAdjustSuccess";
	case eGBAdjustFailed:
		return "eGBAdjustFailed";
	case eGBAdjustNotInGuild:
		return "eGBAdjustNotInGuild";
	case eGBAdjustNoAuthority:
		return "eGBAdjustNoAuthority";
	case eGBAdjustWrongTime:
		return "eGBAdjustWrongTime";
	case eGBAdjustSpotFull:
		return "eGBAdjustSpotFull";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EGBAdjustResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EGBAdjustResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eGBAdjustSuccess", eGBAdjustSuccess));
		mapStr2Val.insert(make_pair("eGBAdjustFailed", eGBAdjustFailed));
		mapStr2Val.insert(make_pair("eGBAdjustNotInGuild", eGBAdjustNotInGuild));
		mapStr2Val.insert(make_pair("eGBAdjustNoAuthority", eGBAdjustNoAuthority));
		mapStr2Val.insert(make_pair("eGBAdjustWrongTime", eGBAdjustWrongTime));
		mapStr2Val.insert(make_pair("eGBAdjustSpotFull", eGBAdjustSpotFull));
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

const char* EnumValToStr(EGBBattleResult e)
{
	switch(e)
	{
	case eGBBattleSuccess:
		return "eGBBattleSuccess";
	case eGBBattleFailed:
		return "eGBBattleFailed";
	case eGBBattleNotInGuild:
		return "eGBBattleNotInGuild";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EGBBattleResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EGBBattleResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eGBBattleSuccess", eGBBattleSuccess));
		mapStr2Val.insert(make_pair("eGBBattleFailed", eGBBattleFailed));
		mapStr2Val.insert(make_pair("eGBBattleNotInGuild", eGBBattleNotInGuild));
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

const char* EnumValToStr(EGBSkillResult e)
{
	switch(e)
	{
	case eGBSkillSuccess:
		return "eGBSkillSuccess";
	case eGBSkillFailed:
		return "eGBSkillFailed";
	case eGBSkillWrongTime:
		return "eGBSkillWrongTime";
	case eGBSkillNoGold:
		return "eGBSkillNoGold";
	case eGBSkillAlreadyHave:
		return "eGBSkillAlreadyHave";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EGBSkillResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EGBSkillResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eGBSkillSuccess", eGBSkillSuccess));
		mapStr2Val.insert(make_pair("eGBSkillFailed", eGBSkillFailed));
		mapStr2Val.insert(make_pair("eGBSkillWrongTime", eGBSkillWrongTime));
		mapStr2Val.insert(make_pair("eGBSkillNoGold", eGBSkillNoGold));
		mapStr2Val.insert(make_pair("eGBSkillAlreadyHave", eGBSkillAlreadyHave));
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

SSkillInfo::SSkillInfo() : eType((EGBSkill)0) { }

SSkillInfo::SSkillInfo(EGBSkill eType_) : eType(eType_) { }

CInArchive& operator>>(CInArchive& src, SSkillInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (UINT8&)s.eType;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SSkillInfo& s)
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
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SSkillInfo& s)
{
	if(strcmp(rElement.Value(), "SSkillInfo") != 0)
	{
		LOG_CRI << "rElement is not SSkillInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "EGBSkill") != 0)
	{
		LOG_CRI << "pElemChild is not EGBSkill!";
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
	return true;
}

bool ToXML(const SSkillInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SSkillInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("技能信息"));
	unique_ptr<TiXmlElement> pElem_eType(new TiXmlElement("EGBSkill"));
	if(pElem_eType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eType->SetAttribute("name", "eType");
	const char* pszEnum_eType = EnumValToStr(s.eType);
	if(pszEnum_eType == NULL)
	{
		LOG_CRI << "EnumValToStr for EGBSkill fails!";
		return false;
	}
	pElem_eType->SetAttribute("value", pszEnum_eType);
	pElem_eType->SetAttribute("comment", ToUTF8Ptr("技能类型"));
	if(rElement.LinkEndChild(pElem_eType.get()) != NULL)
		pElem_eType.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecSkillInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SSkillInfo s;
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

bool VectorToXML(const TVecSkillInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SSkillInfo"));
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

SBattleUserInfo::SBattleUserInfo() : qwRoleID(0), wLevel(0), eState((EGBUserState)0), wFighterID(0) { }

SBattleUserInfo::SBattleUserInfo(SBattleUserInfo&& src) : qwRoleID(src.qwRoleID), strName(move(src.strName)), wLevel(src.wLevel), eState(src.eState), wFighterID(src.wFighterID), 
			vecSkillInfo(move(src.vecSkillInfo)) { }

SBattleUserInfo& SBattleUserInfo::operator=(SBattleUserInfo&& rhs)
{
	if(this != &rhs)
	{
		this->~SBattleUserInfo();
		new (this) SBattleUserInfo(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SBattleUserInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwRoleID;
	src >> s.strName;
	src >> s.wLevel;
	src >> (UINT8&)s.eState;
	src >> s.wFighterID;
	src >> s.vecSkillInfo;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SBattleUserInfo& s)
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
	src << s.wLevel;
	src << (UINT8&)s.eState;
	src << s.wFighterID;
	src << s.vecSkillInfo;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, SBattleUserInfo_Wrapper& rWrapper)
{
	EType_SBattleUserInfo eType = eType_SBattleUserInfo;
	src >> (UINT8&)eType;
	switch(eType)
	{
	case eType_SBattleUserInfo:
		{
			rWrapper.ptr.reset(new SBattleUserInfo);
			src >> (SBattleUserInfo&)*rWrapper.ptr;
		}
		break;
	case eType_SBattleUserAllInfo:
		{
			rWrapper.ptr.reset(new SBattleUserAllInfo);
			src >> (SBattleUserAllInfo&)*rWrapper.ptr;
		}
		break;
	default:
		throw "Unknown value for EType_SBattleUserInfo";
		break;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SBattleUserInfo_Wrapper& rWrapper)
{
	if(rWrapper.ptr != NULL)
	{
		src << (UINT8)rWrapper.ptr->GetClassType();
		switch(rWrapper.ptr->GetClassType())
		{
		case eType_SBattleUserInfo:
			src << (SBattleUserInfo&)*rWrapper.ptr;
			break;
		case eType_SBattleUserAllInfo:
			src << (SBattleUserAllInfo&)*rWrapper.ptr;
			break;
		default:
			throw "Unknown value for EType_SBattleUserInfo";
			break;
		}
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecBattleUserInfo& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SBattleUserInfo_Wrapper wrapper;
		src >> wrapper;
		vec[i] = wrapper.ptr;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecBattleUserInfo& vec)
{
	if(vec.size() > 0x7FFF)
		throw "Vector Size Too Large!";
	UINT16 wSize = (UINT16)vec.size();
	src.WriteContainerSize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SBattleUserInfo_Wrapper wrapper;
		wrapper.ptr = vec[i];
		src << wrapper;
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SBattleUserInfo& s)
{
	if(strcmp(rElement.Value(), "SBattleUserInfo") != 0)
	{
		LOG_CRI << "rElement is not SBattleUserInfo!";
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
		LOG_CRI << "pElemChild for wLevel is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wLevel") != 0)
	{
		LOG_CRI << "Attribute: name is not wLevel!";
		return false;
	}
	const char* pszVal_wLevel = pElemChild->Attribute("value");
	if(pszVal_wLevel == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wLevel, s.wLevel))
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
	if(strcmp(pElemChild->Value(), "EGBUserState") != 0)
	{
		LOG_CRI << "pElemChild is not EGBUserState!";
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
		LOG_CRI << "pElemChild for wFighterID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wFighterID") != 0)
	{
		LOG_CRI << "Attribute: name is not wFighterID!";
		return false;
	}
	const char* pszVal_wFighterID = pElemChild->Attribute("value");
	if(pszVal_wFighterID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wFighterID, s.wFighterID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecSkillInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecSkillInfo") != 0)
	{
		LOG_CRI << "pElemChild is not TVecSkillInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecSkillInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not vecSkillInfo!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecSkillInfo))
	{
		LOG_CRI << "VectorFromXML for vecSkillInfo fails!";
		return false;
	}
	return true;
}

bool ToXML(const SBattleUserInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SBattleUserInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("帮派战玩家信息"));
	unique_ptr<TiXmlElement> pElem_qwRoleID(new TiXmlElement("UINT64"));
	if(pElem_qwRoleID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwRoleID->SetAttribute("name", "qwRoleID");
	pElem_qwRoleID->SetAttribute("value", NumberToString(s.qwRoleID).c_str());
	pElem_qwRoleID->SetAttribute("comment", ToUTF8Ptr("成员角色ID"));
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
	pElem_strName->SetAttribute("comment", ToUTF8Ptr("名字"));
	if(rElement.LinkEndChild(pElem_strName.get()) != NULL)
		pElem_strName.release();
	unique_ptr<TiXmlElement> pElem_wLevel(new TiXmlElement("UINT16"));
	if(pElem_wLevel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wLevel->SetAttribute("name", "wLevel");
	pElem_wLevel->SetAttribute("value", NumberToString(s.wLevel).c_str());
	pElem_wLevel->SetAttribute("comment", ToUTF8Ptr("等级"));
	if(rElement.LinkEndChild(pElem_wLevel.get()) != NULL)
		pElem_wLevel.release();
	unique_ptr<TiXmlElement> pElem_eState(new TiXmlElement("EGBUserState"));
	if(pElem_eState == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eState->SetAttribute("name", "eState");
	const char* pszEnum_eState = EnumValToStr(s.eState);
	if(pszEnum_eState == NULL)
	{
		LOG_CRI << "EnumValToStr for EGBUserState fails!";
		return false;
	}
	pElem_eState->SetAttribute("value", pszEnum_eState);
	pElem_eState->SetAttribute("comment", ToUTF8Ptr("玩家状态"));
	if(rElement.LinkEndChild(pElem_eState.get()) != NULL)
		pElem_eState.release();
	unique_ptr<TiXmlElement> pElem_wFighterID(new TiXmlElement("UINT16"));
	if(pElem_wFighterID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wFighterID->SetAttribute("name", "wFighterID");
	pElem_wFighterID->SetAttribute("value", NumberToString(s.wFighterID).c_str());
	pElem_wFighterID->SetAttribute("comment", ToUTF8Ptr("玩家主将ID"));
	if(rElement.LinkEndChild(pElem_wFighterID.get()) != NULL)
		pElem_wFighterID.release();
	unique_ptr<TiXmlElement> pElem_vecSkillInfo(new TiXmlElement("TVecSkillInfo"));
	if(pElem_vecSkillInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecSkillInfo->SetAttribute("name", "vecSkillInfo");
	if(!VectorToXML(s.vecSkillInfo, *pElem_vecSkillInfo))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecSkillInfo->SetAttribute("comment", ToUTF8Ptr("玩家技能信息"));
	if(rElement.LinkEndChild(pElem_vecSkillInfo.get()) != NULL)
		pElem_vecSkillInfo.release();
	return true;
}

bool SuperFromXML(TiXmlElement& rElement, SBattleUserInfoPtr& p)
{
	const char* pszName = rElement.Value();
	if(pszName == NULL)
	{
		LOG_CRI << "Element Name is empty!";
		return false;
	}
	if(strcmp(pszName, "SBattleUserInfo") == 0)
	{
		SBattleUserInfoPtr pStruct(new SBattleUserInfo);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SBattleUserInfo";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SBattleUserInfo FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SBattleUserAllInfo") == 0)
	{
		SBattleUserAllInfoPtr pStruct(new SBattleUserAllInfo);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SBattleUserAllInfo";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SBattleUserAllInfo FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else
	{
		LOG_CRI << "Invalid name: " << pszName << "!";
		return false;
	}
	return true;
}

bool SuperToXML(const SBattleUserInfo& s, TiXmlElement& rElement)
{
	switch(s.GetClassType())
	{
	case eType_SBattleUserInfo:
		return ToXML((SBattleUserInfo&)s, rElement);
	case eType_SBattleUserAllInfo:
		return ToXML((SBattleUserAllInfo&)s, rElement);
	default:
		LOG_CRI << "Invalid type: " << s.GetClassType();
		return false;
	}
}

bool VectorFromXML(TiXmlElement& rElement, TVecBattleUserInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SBattleUserInfoPtr p;
		if(!SuperFromXML(*pElemMember, p))
		{
			LOG_CRI << "SuperFromXML fails!";
			return false;
		}
		vec.push_back(p);
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecBattleUserInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SBattleUserInfo"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!SuperToXML(*vec[i], *pElemMember))
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

SBattleUserAllInfo::SBattleUserAllInfo() : byHPP(0), byPosIndex(0), dwBattlePoint(0) { }

SBattleUserAllInfo::SBattleUserAllInfo(SBattleUserAllInfo&& src) : SBattleUserInfo(src), sAppear(move(src.sAppear)), byHPP(src.byHPP), byPosIndex(src.byPosIndex), dwBattlePoint(src.dwBattlePoint) { }

SBattleUserAllInfo& SBattleUserAllInfo::operator=(SBattleUserAllInfo&& rhs)
{
	if(this != &rhs)
	{
		this->~SBattleUserAllInfo();
		new (this) SBattleUserAllInfo(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SBattleUserAllInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (SBattleUserInfo&)s;
	src >> s.sAppear;
	src >> s.byHPP;
	src >> s.byPosIndex;
	src >> s.dwBattlePoint;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SBattleUserAllInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const SBattleUserInfo&)s;
	src << s.sAppear;
	src << s.byHPP;
	src << s.byPosIndex;
	src << s.dwBattlePoint;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecBattleUserAllInfo& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SBattleUserAllInfoPtr p(new SBattleUserAllInfo);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecBattleUserAllInfo& vec)
{
	if(vec.size() > 0x7FFF)
		throw "Vector Size Too Large!";
	UINT16 wSize = (UINT16)vec.size();
	src.WriteContainerSize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
		src << *vec[i];
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SBattleUserAllInfo& s)
{
	if(strcmp(rElement.Value(), "SBattleUserAllInfo") != 0)
	{
		LOG_CRI << "rElement is not SBattleUserAllInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for SBattleUserInfo is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (SBattleUserInfo&)s))
	{
		LOG_CRI << "FromXML for: SBattleUserInfo fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for sAppear is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "MapProt::SPlayerAppear") != 0)
	{
		LOG_CRI << "pElemChild is not MapProt::SPlayerAppear!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "sAppear") != 0)
	{
		LOG_CRI << "Attribute: name is not sAppear!";
		return false;
	}
	if(!FromXML(*pElemChild, s.sAppear))
	{
		LOG_CRI << "FromXML for: sAppear fails!";
		return false;
	}
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
		LOG_CRI << "pElemChild for byPosIndex is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byPosIndex") != 0)
	{
		LOG_CRI << "Attribute: name is not byPosIndex!";
		return false;
	}
	const char* pszVal_byPosIndex = pElemChild->Attribute("value");
	if(pszVal_byPosIndex == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byPosIndex, s.byPosIndex))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwBattlePoint is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwBattlePoint") != 0)
	{
		LOG_CRI << "Attribute: name is not dwBattlePoint!";
		return false;
	}
	const char* pszVal_dwBattlePoint = pElemChild->Attribute("value");
	if(pszVal_dwBattlePoint == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwBattlePoint, s.dwBattlePoint))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SBattleUserAllInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SBattleUserAllInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("帮派战玩家详细信息（包括战斗相关属性）"));
	unique_ptr<TiXmlElement> pElem_SBattleUserInfo(new TiXmlElement("SBattleUserInfo"));
	if(pElem_SBattleUserInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const SBattleUserInfo&)s, *pElem_SBattleUserInfo))
	{
		LOG_CRI << "SBattleUserInfo ToXML fails!";
		return false;
	}
	pElem_SBattleUserInfo->SetAttribute("type", ToUTF8Ptr("帮派战玩家信息"));
	pElem_SBattleUserInfo->SetAttribute("comment", ToUTF8Ptr("父类SBattleUserInfo部分"));
	if(rElement.LinkEndChild(pElem_SBattleUserInfo.get()) != NULL)
		pElem_SBattleUserInfo.release();
	unique_ptr<TiXmlElement> pElem_sAppear(new TiXmlElement("MapProt::SPlayerAppear"));
	if(pElem_sAppear == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_sAppear->SetAttribute("name", "sAppear");
	if(!ToXML(s.sAppear, *pElem_sAppear))
	{
		LOG_CRI << "sAppear ToXML fails!";
		return false;
	}
	pElem_sAppear->SetAttribute("comment", ToUTF8Ptr("外观"));
	if(rElement.LinkEndChild(pElem_sAppear.get()) != NULL)
		pElem_sAppear.release();
	unique_ptr<TiXmlElement> pElem_byHPP(new TiXmlElement("UINT8"));
	if(pElem_byHPP == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byHPP->SetAttribute("name", "byHPP");
	pElem_byHPP->SetAttribute("value", NumberToString(s.byHPP).c_str());
	pElem_byHPP->SetAttribute("comment", ToUTF8Ptr("剩余HP百分比"));
	if(rElement.LinkEndChild(pElem_byHPP.get()) != NULL)
		pElem_byHPP.release();
	unique_ptr<TiXmlElement> pElem_byPosIndex(new TiXmlElement("UINT8"));
	if(pElem_byPosIndex == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byPosIndex->SetAttribute("name", "byPosIndex");
	pElem_byPosIndex->SetAttribute("value", NumberToString(s.byPosIndex).c_str());
	pElem_byPosIndex->SetAttribute("comment", ToUTF8Ptr("据点站位编号"));
	if(rElement.LinkEndChild(pElem_byPosIndex.get()) != NULL)
		pElem_byPosIndex.release();
	unique_ptr<TiXmlElement> pElem_dwBattlePoint(new TiXmlElement("UINT32"));
	if(pElem_dwBattlePoint == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwBattlePoint->SetAttribute("name", "dwBattlePoint");
	pElem_dwBattlePoint->SetAttribute("value", NumberToString(s.dwBattlePoint).c_str());
	pElem_dwBattlePoint->SetAttribute("comment", ToUTF8Ptr("战斗力"));
	if(rElement.LinkEndChild(pElem_dwBattlePoint.get()) != NULL)
		pElem_dwBattlePoint.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecBattleUserAllInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SBattleUserAllInfoPtr p(new SBattleUserAllInfo);
		if(!FromXML(*pElemMember, *p))
		{
			LOG_CRI << "FromXML fails!";
			return false;
		}
		vec.push_back(p);
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecBattleUserAllInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SBattleUserAllInfo"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!ToXML(*vec[i], *pElemMember))
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

SBattleInfo::SBattleInfo() : qwBattleID(0), qwRoleIDA(0), qwRoleIDB(0), eWinnerSide((EGBSide)0) { }

SBattleInfo::SBattleInfo(UINT64 qwBattleID_, const std::string& strNameA_, UINT64 qwRoleIDA_, const std::string& strNameB_, UINT64 qwRoleIDB_, 
			EGBSide eWinnerSide_)
			: qwBattleID(qwBattleID_), strNameA(strNameA_), qwRoleIDA(qwRoleIDA_), strNameB(strNameB_), qwRoleIDB(qwRoleIDB_), 
			eWinnerSide(eWinnerSide_) { }

SBattleInfo::SBattleInfo(SBattleInfo&& src) : qwBattleID(src.qwBattleID), strNameA(move(src.strNameA)), qwRoleIDA(src.qwRoleIDA), strNameB(move(src.strNameB)), qwRoleIDB(src.qwRoleIDB), 
			eWinnerSide(src.eWinnerSide) { }

SBattleInfo& SBattleInfo::operator=(SBattleInfo&& rhs)
{
	if(this != &rhs)
	{
		this->~SBattleInfo();
		new (this) SBattleInfo(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SBattleInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwBattleID;
	src >> s.strNameA;
	src >> s.qwRoleIDA;
	src >> s.strNameB;
	src >> s.qwRoleIDB;
	src >> (UINT8&)s.eWinnerSide;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SBattleInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.qwBattleID;
	src << s.strNameA;
	src << s.qwRoleIDA;
	src << s.strNameB;
	src << s.qwRoleIDB;
	src << (UINT8&)s.eWinnerSide;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SBattleInfo& s)
{
	if(strcmp(rElement.Value(), "SBattleInfo") != 0)
	{
		LOG_CRI << "rElement is not SBattleInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwBattleID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwBattleID") != 0)
	{
		LOG_CRI << "Attribute: name is not qwBattleID!";
		return false;
	}
	const char* pszVal_qwBattleID = pElemChild->Attribute("value");
	if(pszVal_qwBattleID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwBattleID, s.qwBattleID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strNameA is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strNameA") != 0)
	{
		LOG_CRI << "Attribute: name is not strNameA!";
		return false;
	}
	const char* pszVal_strNameA = pElemChild->Attribute("value");
	if(pszVal_strNameA == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strNameA = pszVal_strNameA;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwRoleIDA is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwRoleIDA") != 0)
	{
		LOG_CRI << "Attribute: name is not qwRoleIDA!";
		return false;
	}
	const char* pszVal_qwRoleIDA = pElemChild->Attribute("value");
	if(pszVal_qwRoleIDA == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwRoleIDA, s.qwRoleIDA))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strNameB is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strNameB") != 0)
	{
		LOG_CRI << "Attribute: name is not strNameB!";
		return false;
	}
	const char* pszVal_strNameB = pElemChild->Attribute("value");
	if(pszVal_strNameB == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strNameB = pszVal_strNameB;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwRoleIDB is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwRoleIDB") != 0)
	{
		LOG_CRI << "Attribute: name is not qwRoleIDB!";
		return false;
	}
	const char* pszVal_qwRoleIDB = pElemChild->Attribute("value");
	if(pszVal_qwRoleIDB == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwRoleIDB, s.qwRoleIDB))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eWinnerSide is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "EGBSide") != 0)
	{
		LOG_CRI << "pElemChild is not EGBSide!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eWinnerSide") != 0)
	{
		LOG_CRI << "Attribute: name is not eWinnerSide!";
		return false;
	}
	const char* pszVal_eWinnerSide = pElemChild->Attribute("value");
	if(pszVal_eWinnerSide == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!EnumStrToVal(pszVal_eWinnerSide, s.eWinnerSide))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SBattleInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SBattleInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("战斗信息"));
	unique_ptr<TiXmlElement> pElem_qwBattleID(new TiXmlElement("UINT64"));
	if(pElem_qwBattleID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwBattleID->SetAttribute("name", "qwBattleID");
	pElem_qwBattleID->SetAttribute("value", NumberToString(s.qwBattleID).c_str());
	pElem_qwBattleID->SetAttribute("comment", ToUTF8Ptr("战报ID"));
	if(rElement.LinkEndChild(pElem_qwBattleID.get()) != NULL)
		pElem_qwBattleID.release();
	unique_ptr<TiXmlElement> pElem_strNameA(new TiXmlElement("string"));
	if(pElem_strNameA == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strNameA->SetAttribute("name", "strNameA");
	pElem_strNameA->SetAttribute("value", s.strNameA.c_str());
	pElem_strNameA->SetAttribute("comment", ToUTF8Ptr("A方名字"));
	if(rElement.LinkEndChild(pElem_strNameA.get()) != NULL)
		pElem_strNameA.release();
	unique_ptr<TiXmlElement> pElem_qwRoleIDA(new TiXmlElement("UINT64"));
	if(pElem_qwRoleIDA == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwRoleIDA->SetAttribute("name", "qwRoleIDA");
	pElem_qwRoleIDA->SetAttribute("value", NumberToString(s.qwRoleIDA).c_str());
	pElem_qwRoleIDA->SetAttribute("comment", ToUTF8Ptr("A方ID"));
	if(rElement.LinkEndChild(pElem_qwRoleIDA.get()) != NULL)
		pElem_qwRoleIDA.release();
	unique_ptr<TiXmlElement> pElem_strNameB(new TiXmlElement("string"));
	if(pElem_strNameB == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strNameB->SetAttribute("name", "strNameB");
	pElem_strNameB->SetAttribute("value", s.strNameB.c_str());
	pElem_strNameB->SetAttribute("comment", ToUTF8Ptr("B方名字"));
	if(rElement.LinkEndChild(pElem_strNameB.get()) != NULL)
		pElem_strNameB.release();
	unique_ptr<TiXmlElement> pElem_qwRoleIDB(new TiXmlElement("UINT64"));
	if(pElem_qwRoleIDB == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwRoleIDB->SetAttribute("name", "qwRoleIDB");
	pElem_qwRoleIDB->SetAttribute("value", NumberToString(s.qwRoleIDB).c_str());
	pElem_qwRoleIDB->SetAttribute("comment", ToUTF8Ptr("B方ID"));
	if(rElement.LinkEndChild(pElem_qwRoleIDB.get()) != NULL)
		pElem_qwRoleIDB.release();
	unique_ptr<TiXmlElement> pElem_eWinnerSide(new TiXmlElement("EGBSide"));
	if(pElem_eWinnerSide == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eWinnerSide->SetAttribute("name", "eWinnerSide");
	const char* pszEnum_eWinnerSide = EnumValToStr(s.eWinnerSide);
	if(pszEnum_eWinnerSide == NULL)
	{
		LOG_CRI << "EnumValToStr for EGBSide fails!";
		return false;
	}
	pElem_eWinnerSide->SetAttribute("value", pszEnum_eWinnerSide);
	pElem_eWinnerSide->SetAttribute("comment", ToUTF8Ptr("获胜方"));
	if(rElement.LinkEndChild(pElem_eWinnerSide.get()) != NULL)
		pElem_eWinnerSide.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecBattleInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SBattleInfo s;
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

bool VectorToXML(const TVecBattleInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SBattleInfo"));
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

SBattleData::SBattleData() : byIndex(0), qwRoleIDA(0), qwRoleIDB(0), eWinnerSide((EGBSide)0) { }

SBattleData::SBattleData(UINT8 byIndex_, UINT64 qwRoleIDA_, UINT64 qwRoleIDB_, EGBSide eWinnerSide_, const std::string& strBattleReport_)
			: byIndex(byIndex_), qwRoleIDA(qwRoleIDA_), qwRoleIDB(qwRoleIDB_), eWinnerSide(eWinnerSide_), strBattleReport(strBattleReport_) { }

SBattleData::SBattleData(SBattleData&& src) : byIndex(src.byIndex), qwRoleIDA(src.qwRoleIDA), qwRoleIDB(src.qwRoleIDB), eWinnerSide(src.eWinnerSide), strBattleReport(move(src.strBattleReport)) { }

SBattleData& SBattleData::operator=(SBattleData&& rhs)
{
	if(this != &rhs)
	{
		this->~SBattleData();
		new (this) SBattleData(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SBattleData& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.byIndex;
	src >> s.qwRoleIDA;
	src >> s.qwRoleIDB;
	src >> (UINT8&)s.eWinnerSide;
	src >> s.strBattleReport;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SBattleData& s)
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
	src << s.qwRoleIDA;
	src << s.qwRoleIDB;
	src << (UINT8&)s.eWinnerSide;
	src << s.strBattleReport;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SBattleData& s)
{
	if(strcmp(rElement.Value(), "SBattleData") != 0)
	{
		LOG_CRI << "rElement is not SBattleData!";
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
		LOG_CRI << "pElemChild for qwRoleIDA is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwRoleIDA") != 0)
	{
		LOG_CRI << "Attribute: name is not qwRoleIDA!";
		return false;
	}
	const char* pszVal_qwRoleIDA = pElemChild->Attribute("value");
	if(pszVal_qwRoleIDA == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwRoleIDA, s.qwRoleIDA))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwRoleIDB is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwRoleIDB") != 0)
	{
		LOG_CRI << "Attribute: name is not qwRoleIDB!";
		return false;
	}
	const char* pszVal_qwRoleIDB = pElemChild->Attribute("value");
	if(pszVal_qwRoleIDB == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwRoleIDB, s.qwRoleIDB))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eWinnerSide is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "EGBSide") != 0)
	{
		LOG_CRI << "pElemChild is not EGBSide!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eWinnerSide") != 0)
	{
		LOG_CRI << "Attribute: name is not eWinnerSide!";
		return false;
	}
	const char* pszVal_eWinnerSide = pElemChild->Attribute("value");
	if(pszVal_eWinnerSide == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!EnumStrToVal(pszVal_eWinnerSide, s.eWinnerSide))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strBattleReport is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strBattleReport") != 0)
	{
		LOG_CRI << "Attribute: name is not strBattleReport!";
		return false;
	}
	const char* pszVal_strBattleReport = pElemChild->Attribute("value");
	if(pszVal_strBattleReport == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strBattleReport = pszVal_strBattleReport;
	return true;
}

bool ToXML(const SBattleData& s, TiXmlElement& rElement)
{
	rElement.SetValue("SBattleData");
	rElement.SetAttribute("type", ToUTF8Ptr("战斗详细数据"));
	unique_ptr<TiXmlElement> pElem_byIndex(new TiXmlElement("UINT8"));
	if(pElem_byIndex == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byIndex->SetAttribute("name", "byIndex");
	pElem_byIndex->SetAttribute("value", NumberToString(s.byIndex).c_str());
	pElem_byIndex->SetAttribute("comment", ToUTF8Ptr("战斗场编号(1~3)"));
	if(rElement.LinkEndChild(pElem_byIndex.get()) != NULL)
		pElem_byIndex.release();
	unique_ptr<TiXmlElement> pElem_qwRoleIDA(new TiXmlElement("UINT64"));
	if(pElem_qwRoleIDA == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwRoleIDA->SetAttribute("name", "qwRoleIDA");
	pElem_qwRoleIDA->SetAttribute("value", NumberToString(s.qwRoleIDA).c_str());
	pElem_qwRoleIDA->SetAttribute("comment", ToUTF8Ptr("A方玩家ID"));
	if(rElement.LinkEndChild(pElem_qwRoleIDA.get()) != NULL)
		pElem_qwRoleIDA.release();
	unique_ptr<TiXmlElement> pElem_qwRoleIDB(new TiXmlElement("UINT64"));
	if(pElem_qwRoleIDB == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwRoleIDB->SetAttribute("name", "qwRoleIDB");
	pElem_qwRoleIDB->SetAttribute("value", NumberToString(s.qwRoleIDB).c_str());
	pElem_qwRoleIDB->SetAttribute("comment", ToUTF8Ptr("B方玩家ID"));
	if(rElement.LinkEndChild(pElem_qwRoleIDB.get()) != NULL)
		pElem_qwRoleIDB.release();
	unique_ptr<TiXmlElement> pElem_eWinnerSide(new TiXmlElement("EGBSide"));
	if(pElem_eWinnerSide == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eWinnerSide->SetAttribute("name", "eWinnerSide");
	const char* pszEnum_eWinnerSide = EnumValToStr(s.eWinnerSide);
	if(pszEnum_eWinnerSide == NULL)
	{
		LOG_CRI << "EnumValToStr for EGBSide fails!";
		return false;
	}
	pElem_eWinnerSide->SetAttribute("value", pszEnum_eWinnerSide);
	pElem_eWinnerSide->SetAttribute("comment", ToUTF8Ptr("获胜方"));
	if(rElement.LinkEndChild(pElem_eWinnerSide.get()) != NULL)
		pElem_eWinnerSide.release();
	unique_ptr<TiXmlElement> pElem_strBattleReport(new TiXmlElement("string"));
	if(pElem_strBattleReport == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strBattleReport->SetAttribute("name", "strBattleReport");
	pElem_strBattleReport->SetAttribute("value", s.strBattleReport.c_str());
	pElem_strBattleReport->SetAttribute("comment", ToUTF8Ptr("战报"));
	if(rElement.LinkEndChild(pElem_strBattleReport.get()) != NULL)
		pElem_strBattleReport.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecBattleData& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SBattleData s;
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

bool VectorToXML(const TVecBattleData& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SBattleData"));
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

SBattleSlotInfo::SBattleSlotInfo() : byIndex(0), qwBattleID(0) { }

SBattleSlotInfo::SBattleSlotInfo(UINT8 byIndex_, UINT64 qwBattleID_, const SBattleUserAllInfo& sUserAllInfoA_, const SBattleUserAllInfo& sUserAllInfoB_) : byIndex(byIndex_), qwBattleID(qwBattleID_), sUserAllInfoA(sUserAllInfoA_), sUserAllInfoB(sUserAllInfoB_) { }

SBattleSlotInfo::SBattleSlotInfo(SBattleSlotInfo&& src) : byIndex(src.byIndex), qwBattleID(src.qwBattleID), sUserAllInfoA(move(src.sUserAllInfoA)), sUserAllInfoB(move(src.sUserAllInfoB)) { }

SBattleSlotInfo& SBattleSlotInfo::operator=(SBattleSlotInfo&& rhs)
{
	if(this != &rhs)
	{
		this->~SBattleSlotInfo();
		new (this) SBattleSlotInfo(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SBattleSlotInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.byIndex;
	src >> s.qwBattleID;
	src >> s.sUserAllInfoA;
	src >> s.sUserAllInfoB;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SBattleSlotInfo& s)
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
	src << s.qwBattleID;
	src << s.sUserAllInfoA;
	src << s.sUserAllInfoB;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SBattleSlotInfo& s)
{
	if(strcmp(rElement.Value(), "SBattleSlotInfo") != 0)
	{
		LOG_CRI << "rElement is not SBattleSlotInfo!";
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
		LOG_CRI << "pElemChild for qwBattleID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwBattleID") != 0)
	{
		LOG_CRI << "Attribute: name is not qwBattleID!";
		return false;
	}
	const char* pszVal_qwBattleID = pElemChild->Attribute("value");
	if(pszVal_qwBattleID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwBattleID, s.qwBattleID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for sUserAllInfoA is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "SBattleUserAllInfo") != 0)
	{
		LOG_CRI << "pElemChild is not SBattleUserAllInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "sUserAllInfoA") != 0)
	{
		LOG_CRI << "Attribute: name is not sUserAllInfoA!";
		return false;
	}
	if(!FromXML(*pElemChild, s.sUserAllInfoA))
	{
		LOG_CRI << "FromXML for: sUserAllInfoA fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for sUserAllInfoB is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "SBattleUserAllInfo") != 0)
	{
		LOG_CRI << "pElemChild is not SBattleUserAllInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "sUserAllInfoB") != 0)
	{
		LOG_CRI << "Attribute: name is not sUserAllInfoB!";
		return false;
	}
	if(!FromXML(*pElemChild, s.sUserAllInfoB))
	{
		LOG_CRI << "FromXML for: sUserAllInfoB fails!";
		return false;
	}
	return true;
}

bool ToXML(const SBattleSlotInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SBattleSlotInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("战斗场信息"));
	unique_ptr<TiXmlElement> pElem_byIndex(new TiXmlElement("UINT8"));
	if(pElem_byIndex == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byIndex->SetAttribute("name", "byIndex");
	pElem_byIndex->SetAttribute("value", NumberToString(s.byIndex).c_str());
	pElem_byIndex->SetAttribute("comment", ToUTF8Ptr("战斗场编号(1~3)"));
	if(rElement.LinkEndChild(pElem_byIndex.get()) != NULL)
		pElem_byIndex.release();
	unique_ptr<TiXmlElement> pElem_qwBattleID(new TiXmlElement("UINT64"));
	if(pElem_qwBattleID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwBattleID->SetAttribute("name", "qwBattleID");
	pElem_qwBattleID->SetAttribute("value", NumberToString(s.qwBattleID).c_str());
	pElem_qwBattleID->SetAttribute("comment", ToUTF8Ptr("战报ID"));
	if(rElement.LinkEndChild(pElem_qwBattleID.get()) != NULL)
		pElem_qwBattleID.release();
	unique_ptr<TiXmlElement> pElem_sUserAllInfoA(new TiXmlElement("SBattleUserAllInfo"));
	if(pElem_sUserAllInfoA == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_sUserAllInfoA->SetAttribute("name", "sUserAllInfoA");
	if(!ToXML(s.sUserAllInfoA, *pElem_sUserAllInfoA))
	{
		LOG_CRI << "sUserAllInfoA ToXML fails!";
		return false;
	}
	pElem_sUserAllInfoA->SetAttribute("comment", ToUTF8Ptr("A方成员信息"));
	if(rElement.LinkEndChild(pElem_sUserAllInfoA.get()) != NULL)
		pElem_sUserAllInfoA.release();
	unique_ptr<TiXmlElement> pElem_sUserAllInfoB(new TiXmlElement("SBattleUserAllInfo"));
	if(pElem_sUserAllInfoB == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_sUserAllInfoB->SetAttribute("name", "sUserAllInfoB");
	if(!ToXML(s.sUserAllInfoB, *pElem_sUserAllInfoB))
	{
		LOG_CRI << "sUserAllInfoB ToXML fails!";
		return false;
	}
	pElem_sUserAllInfoB->SetAttribute("comment", ToUTF8Ptr("B方成员信息"));
	if(rElement.LinkEndChild(pElem_sUserAllInfoB.get()) != NULL)
		pElem_sUserAllInfoB.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecBattleSlotInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SBattleSlotInfo s;
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

bool VectorToXML(const TVecBattleSlotInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SBattleSlotInfo"));
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

SSpotInfo::SSpotInfo() : eSpotType((EGBSpot)0) { }

CInArchive& operator>>(CInArchive& src, SSpotInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (UINT8&)s.eSpotType;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SSpotInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (UINT8&)s.eSpotType;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, SSpotInfo_Wrapper& rWrapper)
{
	EType_SSpotInfo eType = eType_SSpotInfo;
	src >> (UINT8&)eType;
	switch(eType)
	{
	case eType_SSpotInfo:
		{
			rWrapper.ptr.reset(new SSpotInfo);
			src >> (SSpotInfo&)*rWrapper.ptr;
		}
		break;
	case eType_SSpotAllInfo:
		{
			rWrapper.ptr.reset(new SSpotAllInfo);
			src >> (SSpotAllInfo&)*rWrapper.ptr;
		}
		break;
	case eType_SSpotBriefInfo:
		{
			rWrapper.ptr.reset(new SSpotBriefInfo);
			src >> (SSpotBriefInfo&)*rWrapper.ptr;
		}
		break;
	case eType_SSpotReadyInfo:
		{
			rWrapper.ptr.reset(new SSpotReadyInfo);
			src >> (SSpotReadyInfo&)*rWrapper.ptr;
		}
		break;
	default:
		throw "Unknown value for EType_SSpotInfo";
		break;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SSpotInfo_Wrapper& rWrapper)
{
	if(rWrapper.ptr != NULL)
	{
		src << (UINT8)rWrapper.ptr->GetClassType();
		switch(rWrapper.ptr->GetClassType())
		{
		case eType_SSpotInfo:
			src << (SSpotInfo&)*rWrapper.ptr;
			break;
		case eType_SSpotAllInfo:
			src << (SSpotAllInfo&)*rWrapper.ptr;
			break;
		case eType_SSpotBriefInfo:
			src << (SSpotBriefInfo&)*rWrapper.ptr;
			break;
		case eType_SSpotReadyInfo:
			src << (SSpotReadyInfo&)*rWrapper.ptr;
			break;
		default:
			throw "Unknown value for EType_SSpotInfo";
			break;
		}
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecSpotInfo& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SSpotInfo_Wrapper wrapper;
		src >> wrapper;
		vec[i] = wrapper.ptr;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecSpotInfo& vec)
{
	if(vec.size() > 0x7FFF)
		throw "Vector Size Too Large!";
	UINT16 wSize = (UINT16)vec.size();
	src.WriteContainerSize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SSpotInfo_Wrapper wrapper;
		wrapper.ptr = vec[i];
		src << wrapper;
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SSpotInfo& s)
{
	if(strcmp(rElement.Value(), "SSpotInfo") != 0)
	{
		LOG_CRI << "rElement is not SSpotInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eSpotType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "EGBSpot") != 0)
	{
		LOG_CRI << "pElemChild is not EGBSpot!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eSpotType") != 0)
	{
		LOG_CRI << "Attribute: name is not eSpotType!";
		return false;
	}
	const char* pszVal_eSpotType = pElemChild->Attribute("value");
	if(pszVal_eSpotType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!EnumStrToVal(pszVal_eSpotType, s.eSpotType))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SSpotInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SSpotInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("据点信息"));
	unique_ptr<TiXmlElement> pElem_eSpotType(new TiXmlElement("EGBSpot"));
	if(pElem_eSpotType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eSpotType->SetAttribute("name", "eSpotType");
	const char* pszEnum_eSpotType = EnumValToStr(s.eSpotType);
	if(pszEnum_eSpotType == NULL)
	{
		LOG_CRI << "EnumValToStr for EGBSpot fails!";
		return false;
	}
	pElem_eSpotType->SetAttribute("value", pszEnum_eSpotType);
	pElem_eSpotType->SetAttribute("comment", ToUTF8Ptr("据点类型"));
	if(rElement.LinkEndChild(pElem_eSpotType.get()) != NULL)
		pElem_eSpotType.release();
	return true;
}

bool SuperFromXML(TiXmlElement& rElement, SSpotInfoPtr& p)
{
	const char* pszName = rElement.Value();
	if(pszName == NULL)
	{
		LOG_CRI << "Element Name is empty!";
		return false;
	}
	if(strcmp(pszName, "SSpotInfo") == 0)
	{
		SSpotInfoPtr pStruct(new SSpotInfo);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SSpotInfo";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SSpotInfo FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SSpotAllInfo") == 0)
	{
		SSpotAllInfoPtr pStruct(new SSpotAllInfo);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SSpotAllInfo";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SSpotAllInfo FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SSpotBriefInfo") == 0)
	{
		SSpotBriefInfoPtr pStruct(new SSpotBriefInfo);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SSpotBriefInfo";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SSpotBriefInfo FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SSpotReadyInfo") == 0)
	{
		SSpotReadyInfoPtr pStruct(new SSpotReadyInfo);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SSpotReadyInfo";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SSpotReadyInfo FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else
	{
		LOG_CRI << "Invalid name: " << pszName << "!";
		return false;
	}
	return true;
}

bool SuperToXML(const SSpotInfo& s, TiXmlElement& rElement)
{
	switch(s.GetClassType())
	{
	case eType_SSpotInfo:
		return ToXML((SSpotInfo&)s, rElement);
	case eType_SSpotAllInfo:
		return ToXML((SSpotAllInfo&)s, rElement);
	case eType_SSpotBriefInfo:
		return ToXML((SSpotBriefInfo&)s, rElement);
	case eType_SSpotReadyInfo:
		return ToXML((SSpotReadyInfo&)s, rElement);
	default:
		LOG_CRI << "Invalid type: " << s.GetClassType();
		return false;
	}
}

bool VectorFromXML(TiXmlElement& rElement, TVecSpotInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SSpotInfoPtr p;
		if(!SuperFromXML(*pElemMember, p))
		{
			LOG_CRI << "SuperFromXML fails!";
			return false;
		}
		vec.push_back(p);
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecSpotInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SSpotInfo"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!SuperToXML(*vec[i], *pElemMember))
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

SSpotAllInfo::SSpotAllInfo() : eState((EGBSpotState)0) { }

SSpotAllInfo::SSpotAllInfo(SSpotAllInfo&& src) : SSpotInfo(src), eState(src.eState), vecMemberInfoA(move(src.vecMemberInfoA)), vecMemberInfoB(move(src.vecMemberInfoB)), vecBattleSlotInfo(move(src.vecBattleSlotInfo)), vecBattleInfo(move(src.vecBattleInfo)) { }

SSpotAllInfo& SSpotAllInfo::operator=(SSpotAllInfo&& rhs)
{
	if(this != &rhs)
	{
		this->~SSpotAllInfo();
		new (this) SSpotAllInfo(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SSpotAllInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (SSpotInfo&)s;
	src >> (UINT8&)s.eState;
	src >> s.vecMemberInfoA;
	src >> s.vecMemberInfoB;
	src >> s.vecBattleSlotInfo;
	src >> s.vecBattleInfo;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SSpotAllInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const SSpotInfo&)s;
	src << (UINT8&)s.eState;
	src << s.vecMemberInfoA;
	src << s.vecMemberInfoB;
	src << s.vecBattleSlotInfo;
	src << s.vecBattleInfo;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecSpotAllInfo& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SSpotAllInfoPtr p(new SSpotAllInfo);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecSpotAllInfo& vec)
{
	if(vec.size() > 0x7FFF)
		throw "Vector Size Too Large!";
	UINT16 wSize = (UINT16)vec.size();
	src.WriteContainerSize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
		src << *vec[i];
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SSpotAllInfo& s)
{
	if(strcmp(rElement.Value(), "SSpotAllInfo") != 0)
	{
		LOG_CRI << "rElement is not SSpotAllInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for SSpotInfo is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (SSpotInfo&)s))
	{
		LOG_CRI << "FromXML for: SSpotInfo fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eState is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "EGBSpotState") != 0)
	{
		LOG_CRI << "pElemChild is not EGBSpotState!";
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
		LOG_CRI << "pElemChild for vecMemberInfoA is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecBattleUserInfo") != 0)
	{
		LOG_CRI << "pElemChild is not TVecBattleUserInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecMemberInfoA") != 0)
	{
		LOG_CRI << "Attribute: name is not vecMemberInfoA!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecMemberInfoA))
	{
		LOG_CRI << "VectorFromXML for vecMemberInfoA fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecMemberInfoB is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecBattleUserInfo") != 0)
	{
		LOG_CRI << "pElemChild is not TVecBattleUserInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecMemberInfoB") != 0)
	{
		LOG_CRI << "Attribute: name is not vecMemberInfoB!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecMemberInfoB))
	{
		LOG_CRI << "VectorFromXML for vecMemberInfoB fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecBattleSlotInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecBattleSlotInfo") != 0)
	{
		LOG_CRI << "pElemChild is not TVecBattleSlotInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecBattleSlotInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not vecBattleSlotInfo!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecBattleSlotInfo))
	{
		LOG_CRI << "VectorFromXML for vecBattleSlotInfo fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecBattleInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecBattleInfo") != 0)
	{
		LOG_CRI << "pElemChild is not TVecBattleInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecBattleInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not vecBattleInfo!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecBattleInfo))
	{
		LOG_CRI << "VectorFromXML for vecBattleInfo fails!";
		return false;
	}
	return true;
}

bool ToXML(const SSpotAllInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SSpotAllInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("据点详细信息"));
	unique_ptr<TiXmlElement> pElem_SSpotInfo(new TiXmlElement("SSpotInfo"));
	if(pElem_SSpotInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const SSpotInfo&)s, *pElem_SSpotInfo))
	{
		LOG_CRI << "SSpotInfo ToXML fails!";
		return false;
	}
	pElem_SSpotInfo->SetAttribute("type", ToUTF8Ptr("据点信息"));
	pElem_SSpotInfo->SetAttribute("comment", ToUTF8Ptr("父类SSpotInfo部分"));
	if(rElement.LinkEndChild(pElem_SSpotInfo.get()) != NULL)
		pElem_SSpotInfo.release();
	unique_ptr<TiXmlElement> pElem_eState(new TiXmlElement("EGBSpotState"));
	if(pElem_eState == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eState->SetAttribute("name", "eState");
	const char* pszEnum_eState = EnumValToStr(s.eState);
	if(pszEnum_eState == NULL)
	{
		LOG_CRI << "EnumValToStr for EGBSpotState fails!";
		return false;
	}
	pElem_eState->SetAttribute("value", pszEnum_eState);
	pElem_eState->SetAttribute("comment", ToUTF8Ptr("据点状态"));
	if(rElement.LinkEndChild(pElem_eState.get()) != NULL)
		pElem_eState.release();
	unique_ptr<TiXmlElement> pElem_vecMemberInfoA(new TiXmlElement("TVecBattleUserInfo"));
	if(pElem_vecMemberInfoA == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecMemberInfoA->SetAttribute("name", "vecMemberInfoA");
	if(!VectorToXML(s.vecMemberInfoA, *pElem_vecMemberInfoA))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecMemberInfoA->SetAttribute("comment", ToUTF8Ptr("A方成员信息"));
	if(rElement.LinkEndChild(pElem_vecMemberInfoA.get()) != NULL)
		pElem_vecMemberInfoA.release();
	unique_ptr<TiXmlElement> pElem_vecMemberInfoB(new TiXmlElement("TVecBattleUserInfo"));
	if(pElem_vecMemberInfoB == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecMemberInfoB->SetAttribute("name", "vecMemberInfoB");
	if(!VectorToXML(s.vecMemberInfoB, *pElem_vecMemberInfoB))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecMemberInfoB->SetAttribute("comment", ToUTF8Ptr("B方成员信息"));
	if(rElement.LinkEndChild(pElem_vecMemberInfoB.get()) != NULL)
		pElem_vecMemberInfoB.release();
	unique_ptr<TiXmlElement> pElem_vecBattleSlotInfo(new TiXmlElement("TVecBattleSlotInfo"));
	if(pElem_vecBattleSlotInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecBattleSlotInfo->SetAttribute("name", "vecBattleSlotInfo");
	if(!VectorToXML(s.vecBattleSlotInfo, *pElem_vecBattleSlotInfo))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecBattleSlotInfo->SetAttribute("comment", ToUTF8Ptr("战斗场信息"));
	if(rElement.LinkEndChild(pElem_vecBattleSlotInfo.get()) != NULL)
		pElem_vecBattleSlotInfo.release();
	unique_ptr<TiXmlElement> pElem_vecBattleInfo(new TiXmlElement("TVecBattleInfo"));
	if(pElem_vecBattleInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecBattleInfo->SetAttribute("name", "vecBattleInfo");
	if(!VectorToXML(s.vecBattleInfo, *pElem_vecBattleInfo))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecBattleInfo->SetAttribute("comment", ToUTF8Ptr("战报信息"));
	if(rElement.LinkEndChild(pElem_vecBattleInfo.get()) != NULL)
		pElem_vecBattleInfo.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecSpotAllInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SSpotAllInfoPtr p(new SSpotAllInfo);
		if(!FromXML(*pElemMember, *p))
		{
			LOG_CRI << "FromXML fails!";
			return false;
		}
		vec.push_back(p);
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecSpotAllInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SSpotAllInfo"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!ToXML(*vec[i], *pElemMember))
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

SSpotBriefInfo::SSpotBriefInfo() : eState((EGBSpotState)0) { }

CInArchive& operator>>(CInArchive& src, SSpotBriefInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (SSpotInfo&)s;
	src >> (UINT8&)s.eState;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SSpotBriefInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const SSpotInfo&)s;
	src << (UINT8&)s.eState;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecSpotBriefInfo& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SSpotBriefInfoPtr p(new SSpotBriefInfo);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecSpotBriefInfo& vec)
{
	if(vec.size() > 0x7FFF)
		throw "Vector Size Too Large!";
	UINT16 wSize = (UINT16)vec.size();
	src.WriteContainerSize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
		src << *vec[i];
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SSpotBriefInfo& s)
{
	if(strcmp(rElement.Value(), "SSpotBriefInfo") != 0)
	{
		LOG_CRI << "rElement is not SSpotBriefInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for SSpotInfo is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (SSpotInfo&)s))
	{
		LOG_CRI << "FromXML for: SSpotInfo fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eState is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "EGBSpotState") != 0)
	{
		LOG_CRI << "pElemChild is not EGBSpotState!";
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
	return true;
}

bool ToXML(const SSpotBriefInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SSpotBriefInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("据点简略信息"));
	unique_ptr<TiXmlElement> pElem_SSpotInfo(new TiXmlElement("SSpotInfo"));
	if(pElem_SSpotInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const SSpotInfo&)s, *pElem_SSpotInfo))
	{
		LOG_CRI << "SSpotInfo ToXML fails!";
		return false;
	}
	pElem_SSpotInfo->SetAttribute("type", ToUTF8Ptr("据点信息"));
	pElem_SSpotInfo->SetAttribute("comment", ToUTF8Ptr("父类SSpotInfo部分"));
	if(rElement.LinkEndChild(pElem_SSpotInfo.get()) != NULL)
		pElem_SSpotInfo.release();
	unique_ptr<TiXmlElement> pElem_eState(new TiXmlElement("EGBSpotState"));
	if(pElem_eState == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eState->SetAttribute("name", "eState");
	const char* pszEnum_eState = EnumValToStr(s.eState);
	if(pszEnum_eState == NULL)
	{
		LOG_CRI << "EnumValToStr for EGBSpotState fails!";
		return false;
	}
	pElem_eState->SetAttribute("value", pszEnum_eState);
	pElem_eState->SetAttribute("comment", ToUTF8Ptr("据点状态"));
	if(rElement.LinkEndChild(pElem_eState.get()) != NULL)
		pElem_eState.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecSpotBriefInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SSpotBriefInfoPtr p(new SSpotBriefInfo);
		if(!FromXML(*pElemMember, *p))
		{
			LOG_CRI << "FromXML fails!";
			return false;
		}
		vec.push_back(p);
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecSpotBriefInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SSpotBriefInfo"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!ToXML(*vec[i], *pElemMember))
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

SSpotReadyInfo::SSpotReadyInfo() : byCount(0) { }

CInArchive& operator>>(CInArchive& src, SSpotReadyInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (SSpotInfo&)s;
	src >> s.byCount;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SSpotReadyInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const SSpotInfo&)s;
	src << s.byCount;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecSpotReadyInfo& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SSpotReadyInfoPtr p(new SSpotReadyInfo);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecSpotReadyInfo& vec)
{
	if(vec.size() > 0x7FFF)
		throw "Vector Size Too Large!";
	UINT16 wSize = (UINT16)vec.size();
	src.WriteContainerSize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
		src << *vec[i];
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SSpotReadyInfo& s)
{
	if(strcmp(rElement.Value(), "SSpotReadyInfo") != 0)
	{
		LOG_CRI << "rElement is not SSpotReadyInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for SSpotInfo is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (SSpotInfo&)s))
	{
		LOG_CRI << "FromXML for: SSpotInfo fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byCount is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byCount") != 0)
	{
		LOG_CRI << "Attribute: name is not byCount!";
		return false;
	}
	const char* pszVal_byCount = pElemChild->Attribute("value");
	if(pszVal_byCount == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byCount, s.byCount))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SSpotReadyInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SSpotReadyInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("报名阶段据点信息"));
	unique_ptr<TiXmlElement> pElem_SSpotInfo(new TiXmlElement("SSpotInfo"));
	if(pElem_SSpotInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const SSpotInfo&)s, *pElem_SSpotInfo))
	{
		LOG_CRI << "SSpotInfo ToXML fails!";
		return false;
	}
	pElem_SSpotInfo->SetAttribute("type", ToUTF8Ptr("据点信息"));
	pElem_SSpotInfo->SetAttribute("comment", ToUTF8Ptr("父类SSpotInfo部分"));
	if(rElement.LinkEndChild(pElem_SSpotInfo.get()) != NULL)
		pElem_SSpotInfo.release();
	unique_ptr<TiXmlElement> pElem_byCount(new TiXmlElement("UINT8"));
	if(pElem_byCount == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byCount->SetAttribute("name", "byCount");
	pElem_byCount->SetAttribute("value", NumberToString(s.byCount).c_str());
	pElem_byCount->SetAttribute("comment", ToUTF8Ptr("该据点人数"));
	if(rElement.LinkEndChild(pElem_byCount.get()) != NULL)
		pElem_byCount.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecSpotReadyInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SSpotReadyInfoPtr p(new SSpotReadyInfo);
		if(!FromXML(*pElemMember, *p))
		{
			LOG_CRI << "FromXML fails!";
			return false;
		}
		vec.push_back(p);
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecSpotReadyInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SSpotReadyInfo"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!ToXML(*vec[i], *pElemMember))
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

SFieldInfo::SFieldInfo() { }

SFieldInfo::SFieldInfo(SFieldInfo&& src) : strGuildNameA(move(src.strGuildNameA)), strGuildNameB(move(src.strGuildNameB)), vecSpotInfo(move(src.vecSpotInfo)) { }

SFieldInfo& SFieldInfo::operator=(SFieldInfo&& rhs)
{
	if(this != &rhs)
	{
		this->~SFieldInfo();
		new (this) SFieldInfo(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SFieldInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.strGuildNameA;
	src >> s.strGuildNameB;
	src >> s.vecSpotInfo;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SFieldInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.strGuildNameA;
	src << s.strGuildNameB;
	src << s.vecSpotInfo;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SFieldInfo& s)
{
	if(strcmp(rElement.Value(), "SFieldInfo") != 0)
	{
		LOG_CRI << "rElement is not SFieldInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strGuildNameA is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strGuildNameA") != 0)
	{
		LOG_CRI << "Attribute: name is not strGuildNameA!";
		return false;
	}
	const char* pszVal_strGuildNameA = pElemChild->Attribute("value");
	if(pszVal_strGuildNameA == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strGuildNameA = pszVal_strGuildNameA;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strGuildNameB is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strGuildNameB") != 0)
	{
		LOG_CRI << "Attribute: name is not strGuildNameB!";
		return false;
	}
	const char* pszVal_strGuildNameB = pElemChild->Attribute("value");
	if(pszVal_strGuildNameB == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strGuildNameB = pszVal_strGuildNameB;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecSpotInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecSpotInfo") != 0)
	{
		LOG_CRI << "pElemChild is not TVecSpotInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecSpotInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not vecSpotInfo!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecSpotInfo))
	{
		LOG_CRI << "VectorFromXML for vecSpotInfo fails!";
		return false;
	}
	return true;
}

bool ToXML(const SFieldInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SFieldInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("战场信息"));
	unique_ptr<TiXmlElement> pElem_strGuildNameA(new TiXmlElement("string"));
	if(pElem_strGuildNameA == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strGuildNameA->SetAttribute("name", "strGuildNameA");
	pElem_strGuildNameA->SetAttribute("value", s.strGuildNameA.c_str());
	pElem_strGuildNameA->SetAttribute("comment", ToUTF8Ptr("A方帮派名称"));
	if(rElement.LinkEndChild(pElem_strGuildNameA.get()) != NULL)
		pElem_strGuildNameA.release();
	unique_ptr<TiXmlElement> pElem_strGuildNameB(new TiXmlElement("string"));
	if(pElem_strGuildNameB == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strGuildNameB->SetAttribute("name", "strGuildNameB");
	pElem_strGuildNameB->SetAttribute("value", s.strGuildNameB.c_str());
	pElem_strGuildNameB->SetAttribute("comment", ToUTF8Ptr("B方帮派名称"));
	if(rElement.LinkEndChild(pElem_strGuildNameB.get()) != NULL)
		pElem_strGuildNameB.release();
	unique_ptr<TiXmlElement> pElem_vecSpotInfo(new TiXmlElement("TVecSpotInfo"));
	if(pElem_vecSpotInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecSpotInfo->SetAttribute("name", "vecSpotInfo");
	if(!VectorToXML(s.vecSpotInfo, *pElem_vecSpotInfo))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecSpotInfo->SetAttribute("comment", ToUTF8Ptr("据点详细信息"));
	if(rElement.LinkEndChild(pElem_vecSpotInfo.get()) != NULL)
		pElem_vecSpotInfo.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecFieldInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SFieldInfo s;
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

bool VectorToXML(const TVecFieldInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SFieldInfo"));
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

} //namespace NGuildBattleProt
