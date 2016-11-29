/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    FighterProt.cpp
//  Purpose:      道具相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "FighterProt.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NFighterProt
{

#ifdef PROT_USE_XML

const char* EnumValToStr(EFighterType e)
{
	switch(e)
	{
	case eFighter:
		return "eFighter";
	case eFighterPlayer:
		return "eFighterPlayer";
	case eFighterHero:
		return "eFighterHero";
	case eFighterMonster:
		return "eFighterMonster";
	case eFighterMax:
		return "eFighterMax";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EFighterType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EFighterType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eFighter", eFighter));
		mapStr2Val.insert(make_pair("eFighterPlayer", eFighterPlayer));
		mapStr2Val.insert(make_pair("eFighterHero", eFighterHero));
		mapStr2Val.insert(make_pair("eFighterMonster", eFighterMonster));
		mapStr2Val.insert(make_pair("eFighterMax", eFighterMax));
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

const char* EnumValToStr(ESkillResult e)
{
	switch(e)
	{
	case eSkillSucc:
		return "eSkillSucc";
	case eSkillFailed:
		return "eSkillFailed";
	case eSkillNotExist:
		return "eSkillNotExist";
	case eSkillLevelMax:
		return "eSkillLevelMax";
	case eSkillLevelErr:
		return "eSkillLevelErr";
	case eSkillNotUp:
		return "eSkillNotUp";
	case eSkillPExpErr:
		return "eSkillPExpErr";
	case eSkillSopErr:
		return "eSkillSopErr";
	case eSkillSigilErr:
		return "eSkillSigilErr";
	case eSkillCentsYErr:
		return "eSkillCentsYErr";
	case eSkillPotenErr:
		return "eSkillPotenErr";
	case eRuneNotExist:
		return "eRuneNotExist";
	case eRuneLevelMax:
		return "eRuneLevelMax";
	case eRuneLevelErr:
		return "eRuneLevelErr";
	case eAdvNotExist:
		return "eAdvNotExist";
	case eAdvLevelGTSkillLevelErr:
		return "eAdvLevelGTSkillLevelErr";
	case eItemNotEnough:
		return "eItemNotEnough";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, ESkillResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, ESkillResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eSkillSucc", eSkillSucc));
		mapStr2Val.insert(make_pair("eSkillFailed", eSkillFailed));
		mapStr2Val.insert(make_pair("eSkillNotExist", eSkillNotExist));
		mapStr2Val.insert(make_pair("eSkillLevelMax", eSkillLevelMax));
		mapStr2Val.insert(make_pair("eSkillLevelErr", eSkillLevelErr));
		mapStr2Val.insert(make_pair("eSkillNotUp", eSkillNotUp));
		mapStr2Val.insert(make_pair("eSkillPExpErr", eSkillPExpErr));
		mapStr2Val.insert(make_pair("eSkillSopErr", eSkillSopErr));
		mapStr2Val.insert(make_pair("eSkillSigilErr", eSkillSigilErr));
		mapStr2Val.insert(make_pair("eSkillCentsYErr", eSkillCentsYErr));
		mapStr2Val.insert(make_pair("eSkillPotenErr", eSkillPotenErr));
		mapStr2Val.insert(make_pair("eRuneNotExist", eRuneNotExist));
		mapStr2Val.insert(make_pair("eRuneLevelMax", eRuneLevelMax));
		mapStr2Val.insert(make_pair("eRuneLevelErr", eRuneLevelErr));
		mapStr2Val.insert(make_pair("eAdvNotExist", eAdvNotExist));
		mapStr2Val.insert(make_pair("eAdvLevelGTSkillLevelErr", eAdvLevelGTSkillLevelErr));
		mapStr2Val.insert(make_pair("eItemNotEnough", eItemNotEnough));
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

const char* EnumValToStr(EDrawType e)
{
	switch(e)
	{
	case eDrawTypeNone:
		return "eDrawTypeNone";
	case eDrawTypeNormal:
		return "eDrawTypeNormal";
	case eDrawTypeAdvance:
		return "eDrawTypeAdvance";
	case eDrawTypeMax:
		return "eDrawTypeMax";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EDrawType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EDrawType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eDrawTypeNone", eDrawTypeNone));
		mapStr2Val.insert(make_pair("eDrawTypeNormal", eDrawTypeNormal));
		mapStr2Val.insert(make_pair("eDrawTypeAdvance", eDrawTypeAdvance));
		mapStr2Val.insert(make_pair("eDrawTypeMax", eDrawTypeMax));
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

const char* EnumValToStr(EDrawRewardType e)
{
	switch(e)
	{
	case eDrawRewardTypeNone:
		return "eDrawRewardTypeNone";
	case eDrawRewardTypeBlue:
		return "eDrawRewardTypeBlue";
	case eDrawRewardTypePurple:
		return "eDrawRewardTypePurple";
	case eDrawRewardTypeOrange:
		return "eDrawRewardTypeOrange";
	case eDrawRewardTypeMax:
		return "eDrawRewardTypeMax";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EDrawRewardType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EDrawRewardType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eDrawRewardTypeNone", eDrawRewardTypeNone));
		mapStr2Val.insert(make_pair("eDrawRewardTypeBlue", eDrawRewardTypeBlue));
		mapStr2Val.insert(make_pair("eDrawRewardTypePurple", eDrawRewardTypePurple));
		mapStr2Val.insert(make_pair("eDrawRewardTypeOrange", eDrawRewardTypeOrange));
		mapStr2Val.insert(make_pair("eDrawRewardTypeMax", eDrawRewardTypeMax));
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

const char* EnumValToStr(EDrawResult e)
{
	switch(e)
	{
	case eDrawResultSuccess:
		return "eDrawResultSuccess";
	case eDrawResultFailed:
		return "eDrawResultFailed";
	case eDrawResultLackOfCount:
		return "eDrawResultLackOfCount";
	case eDrawResultLackOfMoney:
		return "eDrawResultLackOfMoney";
	case eDrawResultMax:
		return "eDrawResultMax";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EDrawResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EDrawResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eDrawResultSuccess", eDrawResultSuccess));
		mapStr2Val.insert(make_pair("eDrawResultFailed", eDrawResultFailed));
		mapStr2Val.insert(make_pair("eDrawResultLackOfCount", eDrawResultLackOfCount));
		mapStr2Val.insert(make_pair("eDrawResultLackOfMoney", eDrawResultLackOfMoney));
		mapStr2Val.insert(make_pair("eDrawResultMax", eDrawResultMax));
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

const char* EnumValToStr(ERecruitResult e)
{
	switch(e)
	{
	case eRecruitSucc:
		return "eRecruitSucc";
	case eRecruitFailed:
		return "eRecruitFailed";
	case eRecruitAlready:
		return "eRecruitAlready";
	case eRecruitLackOfMoney:
		return "eRecruitLackOfMoney";
	case eRecruitLevelLimited:
		return "eRecruitLevelLimited";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, ERecruitResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, ERecruitResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eRecruitSucc", eRecruitSucc));
		mapStr2Val.insert(make_pair("eRecruitFailed", eRecruitFailed));
		mapStr2Val.insert(make_pair("eRecruitAlready", eRecruitAlready));
		mapStr2Val.insert(make_pair("eRecruitLackOfMoney", eRecruitLackOfMoney));
		mapStr2Val.insert(make_pair("eRecruitLevelLimited", eRecruitLevelLimited));
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

const char* EnumValToStr(ECuiTiType e)
{
	switch(e)
	{
	case eCuiTiLianPi:
		return "eCuiTiLianPi";
	case eCuiTiTongJin:
		return "eCuiTiTongJin";
	case eCuiTiQiangJi:
		return "eCuiTiQiangJi";
	case eCuiTiDuanGu:
		return "eCuiTiDuanGu";
	case eCuiTiHuoLuo:
		return "eCuiTiHuoLuo";
	case eCuiTiXiSui:
		return "eCuiTiXiSui";
	case eCuiTiMax:
		return "eCuiTiMax";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, ECuiTiType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, ECuiTiType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eCuiTiLianPi", eCuiTiLianPi));
		mapStr2Val.insert(make_pair("eCuiTiTongJin", eCuiTiTongJin));
		mapStr2Val.insert(make_pair("eCuiTiQiangJi", eCuiTiQiangJi));
		mapStr2Val.insert(make_pair("eCuiTiDuanGu", eCuiTiDuanGu));
		mapStr2Val.insert(make_pair("eCuiTiHuoLuo", eCuiTiHuoLuo));
		mapStr2Val.insert(make_pair("eCuiTiXiSui", eCuiTiXiSui));
		mapStr2Val.insert(make_pair("eCuiTiMax", eCuiTiMax));
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

const char* EnumValToStr(ECuiTiResult e)
{
	switch(e)
	{
	case eCuiTiResultSucc:
		return "eCuiTiResultSucc";
	case eCuiTiResultFailed:
		return "eCuiTiResultFailed";
	case eCuiTiResultSilverErr:
		return "eCuiTiResultSilverErr";
	case eCuiTiResultLvlMaxErr:
		return "eCuiTiResultLvlMaxErr";
	case eCuiTiResultPlayerLvlErr:
		return "eCuiTiResultPlayerLvlErr";
	case eCuiTiResultUnlock:
		return "eCuiTiResultUnlock";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, ECuiTiResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, ECuiTiResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eCuiTiResultSucc", eCuiTiResultSucc));
		mapStr2Val.insert(make_pair("eCuiTiResultFailed", eCuiTiResultFailed));
		mapStr2Val.insert(make_pair("eCuiTiResultSilverErr", eCuiTiResultSilverErr));
		mapStr2Val.insert(make_pair("eCuiTiResultLvlMaxErr", eCuiTiResultLvlMaxErr));
		mapStr2Val.insert(make_pair("eCuiTiResultPlayerLvlErr", eCuiTiResultPlayerLvlErr));
		mapStr2Val.insert(make_pair("eCuiTiResultUnlock", eCuiTiResultUnlock));
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

const char* EnumValToStr(EShiftResult e)
{
	switch(e)
	{
	case eShiftSucc:
		return "eShiftSucc";
	case eShiftFailed:
		return "eShiftFailed";
	case eShiftGoldErr:
		return "eShiftGoldErr";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EShiftResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EShiftResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eShiftSucc", eShiftSucc));
		mapStr2Val.insert(make_pair("eShiftFailed", eShiftFailed));
		mapStr2Val.insert(make_pair("eShiftGoldErr", eShiftGoldErr));
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

const char* EnumValToStr(ESyncLevelResult e)
{
	switch(e)
	{
	case eSyncLevelSucc:
		return "eSyncLevelSucc";
	case eSyncLevelFailed:
		return "eSyncLevelFailed";
	case eSyncLevelAlready:
		return "eSyncLevelAlready";
	case eSyncLevelMoney:
		return "eSyncLevelMoney";
	case eSyncLevelMoneyMore:
		return "eSyncLevelMoneyMore";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, ESyncLevelResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, ESyncLevelResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eSyncLevelSucc", eSyncLevelSucc));
		mapStr2Val.insert(make_pair("eSyncLevelFailed", eSyncLevelFailed));
		mapStr2Val.insert(make_pair("eSyncLevelAlready", eSyncLevelAlready));
		mapStr2Val.insert(make_pair("eSyncLevelMoney", eSyncLevelMoney));
		mapStr2Val.insert(make_pair("eSyncLevelMoneyMore", eSyncLevelMoneyMore));
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

const char* EnumValToStr(EDujieResult e)
{
	switch(e)
	{
	case eDujieSucc:
		return "eDujieSucc";
	case eDujieFailed:
		return "eDujieFailed";
	case eDujieItemErr:
		return "eDujieItemErr";
	case eDujieLevelMaxErr:
		return "eDujieLevelMaxErr";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EDujieResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EDujieResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eDujieSucc", eDujieSucc));
		mapStr2Val.insert(make_pair("eDujieFailed", eDujieFailed));
		mapStr2Val.insert(make_pair("eDujieItemErr", eDujieItemErr));
		mapStr2Val.insert(make_pair("eDujieLevelMaxErr", eDujieLevelMaxErr));
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

const char* EnumValToStr(EXinFaResult e)
{
	switch(e)
	{
	case eXinFaSucc:
		return "eXinFaSucc";
	case eXinFaFailed:
		return "eXinFaFailed";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EXinFaResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EXinFaResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eXinFaSucc", eXinFaSucc));
		mapStr2Val.insert(make_pair("eXinFaFailed", eXinFaFailed));
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

const char* EnumValToStr(ECombinationResult e)
{
	switch(e)
	{
	case eCombinationSucc:
		return "eCombinationSucc";
	case eCombinationFailed:
		return "eCombinationFailed";
	case eCombinationMaxLevel:
		return "eCombinationMaxLevel";
	case eCombinationHaved:
		return "eCombinationHaved";
	case eCombinationNotHaved:
		return "eCombinationNotHaved";
	case eCombinationFighterErr:
		return "eCombinationFighterErr";
	case eCombinationItemErr:
		return "eCombinationItemErr";
	case eCombinationMainLevelErr:
		return "eCombinationMainLevelErr";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, ECombinationResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, ECombinationResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eCombinationSucc", eCombinationSucc));
		mapStr2Val.insert(make_pair("eCombinationFailed", eCombinationFailed));
		mapStr2Val.insert(make_pair("eCombinationMaxLevel", eCombinationMaxLevel));
		mapStr2Val.insert(make_pair("eCombinationHaved", eCombinationHaved));
		mapStr2Val.insert(make_pair("eCombinationNotHaved", eCombinationNotHaved));
		mapStr2Val.insert(make_pair("eCombinationFighterErr", eCombinationFighterErr));
		mapStr2Val.insert(make_pair("eCombinationItemErr", eCombinationItemErr));
		mapStr2Val.insert(make_pair("eCombinationMainLevelErr", eCombinationMainLevelErr));
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

const char* EnumValToStr(EDismissResult e)
{
	switch(e)
	{
	case eDismissSucc:
		return "eDismissSucc";
	case eDismissFailed:
		return "eDismissFailed";
	case eNeedTakeOffStone:
		return "eNeedTakeOffStone";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EDismissResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EDismissResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eDismissSucc", eDismissSucc));
		mapStr2Val.insert(make_pair("eDismissFailed", eDismissFailed));
		mapStr2Val.insert(make_pair("eNeedTakeOffStone", eNeedTakeOffStone));
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

const char* EnumValToStr(EFighterBuyResult e)
{
	switch(e)
	{
	case eFighterBuySucc:
		return "eFighterBuySucc";
	case eFighterBuyFailed:
		return "eFighterBuyFailed";
	case eFighterBuyAlready:
		return "eFighterBuyAlready";
	case eFighterBuyLackOfMoney:
		return "eFighterBuyLackOfMoney";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EFighterBuyResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EFighterBuyResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eFighterBuySucc", eFighterBuySucc));
		mapStr2Val.insert(make_pair("eFighterBuyFailed", eFighterBuyFailed));
		mapStr2Val.insert(make_pair("eFighterBuyAlready", eFighterBuyAlready));
		mapStr2Val.insert(make_pair("eFighterBuyLackOfMoney", eFighterBuyLackOfMoney));
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

SFighterBuyInfo::SFighterBuyInfo() : wFighterID(0), byFighterBuyStatus(0) { }

SFighterBuyInfo::SFighterBuyInfo(UINT16 wFighterID_, UINT8 byFighterBuyStatus_) : wFighterID(wFighterID_), byFighterBuyStatus(byFighterBuyStatus_) { }

CInArchive& operator>>(CInArchive& src, SFighterBuyInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.wFighterID;
	src >> s.byFighterBuyStatus;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SFighterBuyInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.wFighterID;
	src << s.byFighterBuyStatus;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SFighterBuyInfo& s)
{
	if(strcmp(rElement.Value(), "SFighterBuyInfo") != 0)
	{
		LOG_CRI << "rElement is not SFighterBuyInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
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
		LOG_CRI << "pElemChild for byFighterBuyStatus is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byFighterBuyStatus") != 0)
	{
		LOG_CRI << "Attribute: name is not byFighterBuyStatus!";
		return false;
	}
	const char* pszVal_byFighterBuyStatus = pElemChild->Attribute("value");
	if(pszVal_byFighterBuyStatus == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byFighterBuyStatus, s.byFighterBuyStatus))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SFighterBuyInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SFighterBuyInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("玩家购买散仙信息"));
	unique_ptr<TiXmlElement> pElem_wFighterID(new TiXmlElement("UINT16"));
	if(pElem_wFighterID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wFighterID->SetAttribute("name", "wFighterID");
	pElem_wFighterID->SetAttribute("value", NumberToString(s.wFighterID).c_str());
	pElem_wFighterID->SetAttribute("comment", ToUTF8Ptr("将类型ID"));
	if(rElement.LinkEndChild(pElem_wFighterID.get()) != NULL)
		pElem_wFighterID.release();
	unique_ptr<TiXmlElement> pElem_byFighterBuyStatus(new TiXmlElement("UINT8"));
	if(pElem_byFighterBuyStatus == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byFighterBuyStatus->SetAttribute("name", "byFighterBuyStatus");
	pElem_byFighterBuyStatus->SetAttribute("value", NumberToString(s.byFighterBuyStatus).c_str());
	pElem_byFighterBuyStatus->SetAttribute("comment", ToUTF8Ptr("购买状态（0：未购买；1：已购买）"));
	if(rElement.LinkEndChild(pElem_byFighterBuyStatus.get()) != NULL)
		pElem_byFighterBuyStatus.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecFighterBuyInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SFighterBuyInfo s;
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

bool VectorToXML(const TVecFighterBuyInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SFighterBuyInfo"));
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

SFighterCombination::SFighterCombination() : byGroupID(0), byGroupLvl(0), dwGroupExp(0), byInLineUp(0), byInEMei(0) { }

SFighterCombination::SFighterCombination(UINT8 byGroupID_, UINT8 byGroupLvl_, UINT32 dwGroupExp_, UINT8 byInLineUp_, UINT8 byInEMei_)
			: byGroupID(byGroupID_), byGroupLvl(byGroupLvl_), dwGroupExp(dwGroupExp_), byInLineUp(byInLineUp_), byInEMei(byInEMei_) { }

CInArchive& operator>>(CInArchive& src, SFighterCombination& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.byGroupID;
	src >> s.byGroupLvl;
	src >> s.dwGroupExp;
	src >> s.byInLineUp;
	src >> s.byInEMei;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SFighterCombination& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.byGroupID;
	src << s.byGroupLvl;
	src << s.dwGroupExp;
	src << s.byInLineUp;
	src << s.byInEMei;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SFighterCombination& s)
{
	if(strcmp(rElement.Value(), "SFighterCombination") != 0)
	{
		LOG_CRI << "rElement is not SFighterCombination!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byGroupID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byGroupID") != 0)
	{
		LOG_CRI << "Attribute: name is not byGroupID!";
		return false;
	}
	const char* pszVal_byGroupID = pElemChild->Attribute("value");
	if(pszVal_byGroupID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byGroupID, s.byGroupID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byGroupLvl is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byGroupLvl") != 0)
	{
		LOG_CRI << "Attribute: name is not byGroupLvl!";
		return false;
	}
	const char* pszVal_byGroupLvl = pElemChild->Attribute("value");
	if(pszVal_byGroupLvl == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byGroupLvl, s.byGroupLvl))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwGroupExp is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwGroupExp") != 0)
	{
		LOG_CRI << "Attribute: name is not dwGroupExp!";
		return false;
	}
	const char* pszVal_dwGroupExp = pElemChild->Attribute("value");
	if(pszVal_dwGroupExp == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwGroupExp, s.dwGroupExp))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byInLineUp is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byInLineUp") != 0)
	{
		LOG_CRI << "Attribute: name is not byInLineUp!";
		return false;
	}
	const char* pszVal_byInLineUp = pElemChild->Attribute("value");
	if(pszVal_byInLineUp == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byInLineUp, s.byInLineUp))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byInEMei is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byInEMei") != 0)
	{
		LOG_CRI << "Attribute: name is not byInEMei!";
		return false;
	}
	const char* pszVal_byInEMei = pElemChild->Attribute("value");
	if(pszVal_byInEMei == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byInEMei, s.byInEMei))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SFighterCombination& s, TiXmlElement& rElement)
{
	rElement.SetValue("SFighterCombination");
	rElement.SetAttribute("type", ToUTF8Ptr("玩家的散仙组合信息"));
	unique_ptr<TiXmlElement> pElem_byGroupID(new TiXmlElement("UINT8"));
	if(pElem_byGroupID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byGroupID->SetAttribute("name", "byGroupID");
	pElem_byGroupID->SetAttribute("value", NumberToString(s.byGroupID).c_str());
	pElem_byGroupID->SetAttribute("comment", ToUTF8Ptr("散仙组合ID"));
	if(rElement.LinkEndChild(pElem_byGroupID.get()) != NULL)
		pElem_byGroupID.release();
	unique_ptr<TiXmlElement> pElem_byGroupLvl(new TiXmlElement("UINT8"));
	if(pElem_byGroupLvl == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byGroupLvl->SetAttribute("name", "byGroupLvl");
	pElem_byGroupLvl->SetAttribute("value", NumberToString(s.byGroupLvl).c_str());
	pElem_byGroupLvl->SetAttribute("comment", ToUTF8Ptr("散仙组合等级"));
	if(rElement.LinkEndChild(pElem_byGroupLvl.get()) != NULL)
		pElem_byGroupLvl.release();
	unique_ptr<TiXmlElement> pElem_dwGroupExp(new TiXmlElement("UINT32"));
	if(pElem_dwGroupExp == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwGroupExp->SetAttribute("name", "dwGroupExp");
	pElem_dwGroupExp->SetAttribute("value", NumberToString(s.dwGroupExp).c_str());
	pElem_dwGroupExp->SetAttribute("comment", ToUTF8Ptr("散仙组合当前经验值"));
	if(rElement.LinkEndChild(pElem_dwGroupExp.get()) != NULL)
		pElem_dwGroupExp.release();
	unique_ptr<TiXmlElement> pElem_byInLineUp(new TiXmlElement("UINT8"));
	if(pElem_byInLineUp == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byInLineUp->SetAttribute("name", "byInLineUp");
	pElem_byInLineUp->SetAttribute("value", NumberToString(s.byInLineUp).c_str());
	pElem_byInLineUp->SetAttribute("comment", ToUTF8Ptr("是否出战在阵型(0未出战 1已出战)"));
	if(rElement.LinkEndChild(pElem_byInLineUp.get()) != NULL)
		pElem_byInLineUp.release();
	unique_ptr<TiXmlElement> pElem_byInEMei(new TiXmlElement("UINT8"));
	if(pElem_byInEMei == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byInEMei->SetAttribute("name", "byInEMei");
	pElem_byInEMei->SetAttribute("value", NumberToString(s.byInEMei).c_str());
	pElem_byInEMei->SetAttribute("comment", ToUTF8Ptr("是否出战在守卫峨眉(0未出战 1已出战)"));
	if(rElement.LinkEndChild(pElem_byInEMei.get()) != NULL)
		pElem_byInEMei.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecFighterCombination& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SFighterCombination s;
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

bool VectorToXML(const TVecFighterCombination& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SFighterCombination"));
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

SFighterDBInfo::SFighterDBInfo() : qwInstID(0), qwRoleID(0), wFighterID(0), byRecruited(0), byStar(0), 
			iSlot(0), iPos(0), fPotential(0), fCapacity(0), byLevel(0), 
			qwExp(0), byLianPi(0), byTongJin(0), byQiangJi(0), byDuanGu(0), 
			byHuoLuo(0), byXiSui(0), dwDujieExp(0), dwSpiritPower(0) { }

CInArchive& operator>>(CInArchive& src, SFighterDBInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwInstID;
	src >> s.qwRoleID;
	src >> s.wFighterID;
	src >> s.byRecruited;
	src >> s.byStar;
	src >> s.iSlot;
	src >> s.iPos;
	src >> s.fPotential;
	src >> s.fCapacity;
	src >> s.byLevel;
	src >> s.qwExp;
	src >> s.byLianPi;
	src >> s.byTongJin;
	src >> s.byQiangJi;
	src >> s.byDuanGu;
	src >> s.byHuoLuo;
	src >> s.byXiSui;
	src >> s.dwDujieExp;
	src >> s.dwSpiritPower;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SFighterDBInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.qwInstID;
	src << s.qwRoleID;
	src << s.wFighterID;
	src << s.byRecruited;
	src << s.byStar;
	src << s.iSlot;
	src << s.iPos;
	src << s.fPotential;
	src << s.fCapacity;
	src << s.byLevel;
	src << s.qwExp;
	src << s.byLianPi;
	src << s.byTongJin;
	src << s.byQiangJi;
	src << s.byDuanGu;
	src << s.byHuoLuo;
	src << s.byXiSui;
	src << s.dwDujieExp;
	src << s.dwSpiritPower;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SFighterDBInfo& s)
{
	if(strcmp(rElement.Value(), "SFighterDBInfo") != 0)
	{
		LOG_CRI << "rElement is not SFighterDBInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwInstID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwInstID") != 0)
	{
		LOG_CRI << "Attribute: name is not qwInstID!";
		return false;
	}
	const char* pszVal_qwInstID = pElemChild->Attribute("value");
	if(pszVal_qwInstID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwInstID, s.qwInstID))
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
		LOG_CRI << "pElemChild for byRecruited is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byRecruited") != 0)
	{
		LOG_CRI << "Attribute: name is not byRecruited!";
		return false;
	}
	const char* pszVal_byRecruited = pElemChild->Attribute("value");
	if(pszVal_byRecruited == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byRecruited, s.byRecruited))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byStar is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byStar") != 0)
	{
		LOG_CRI << "Attribute: name is not byStar!";
		return false;
	}
	const char* pszVal_byStar = pElemChild->Attribute("value");
	if(pszVal_byStar == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byStar, s.byStar))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for iSlot is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "INT32") != 0)
	{
		LOG_CRI << "pElemChild is not INT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "iSlot") != 0)
	{
		LOG_CRI << "Attribute: name is not iSlot!";
		return false;
	}
	const char* pszVal_iSlot = pElemChild->Attribute("value");
	if(pszVal_iSlot == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_iSlot, s.iSlot))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for iPos is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "INT32") != 0)
	{
		LOG_CRI << "pElemChild is not INT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "iPos") != 0)
	{
		LOG_CRI << "Attribute: name is not iPos!";
		return false;
	}
	const char* pszVal_iPos = pElemChild->Attribute("value");
	if(pszVal_iPos == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_iPos, s.iPos))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for fPotential is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "float") != 0)
	{
		LOG_CRI << "pElemChild is not float!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "fPotential") != 0)
	{
		LOG_CRI << "Attribute: name is not fPotential!";
		return false;
	}
	const char* pszVal_fPotential = pElemChild->Attribute("value");
	if(pszVal_fPotential == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_fPotential, s.fPotential))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for fCapacity is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "float") != 0)
	{
		LOG_CRI << "pElemChild is not float!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "fCapacity") != 0)
	{
		LOG_CRI << "Attribute: name is not fCapacity!";
		return false;
	}
	const char* pszVal_fCapacity = pElemChild->Attribute("value");
	if(pszVal_fCapacity == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_fCapacity, s.fCapacity))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
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
		LOG_CRI << "pElemChild for qwExp is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwExp") != 0)
	{
		LOG_CRI << "Attribute: name is not qwExp!";
		return false;
	}
	const char* pszVal_qwExp = pElemChild->Attribute("value");
	if(pszVal_qwExp == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwExp, s.qwExp))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byLianPi is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byLianPi") != 0)
	{
		LOG_CRI << "Attribute: name is not byLianPi!";
		return false;
	}
	const char* pszVal_byLianPi = pElemChild->Attribute("value");
	if(pszVal_byLianPi == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byLianPi, s.byLianPi))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byTongJin is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byTongJin") != 0)
	{
		LOG_CRI << "Attribute: name is not byTongJin!";
		return false;
	}
	const char* pszVal_byTongJin = pElemChild->Attribute("value");
	if(pszVal_byTongJin == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byTongJin, s.byTongJin))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byQiangJi is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byQiangJi") != 0)
	{
		LOG_CRI << "Attribute: name is not byQiangJi!";
		return false;
	}
	const char* pszVal_byQiangJi = pElemChild->Attribute("value");
	if(pszVal_byQiangJi == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byQiangJi, s.byQiangJi))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byDuanGu is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byDuanGu") != 0)
	{
		LOG_CRI << "Attribute: name is not byDuanGu!";
		return false;
	}
	const char* pszVal_byDuanGu = pElemChild->Attribute("value");
	if(pszVal_byDuanGu == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byDuanGu, s.byDuanGu))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byHuoLuo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byHuoLuo") != 0)
	{
		LOG_CRI << "Attribute: name is not byHuoLuo!";
		return false;
	}
	const char* pszVal_byHuoLuo = pElemChild->Attribute("value");
	if(pszVal_byHuoLuo == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byHuoLuo, s.byHuoLuo))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byXiSui is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byXiSui") != 0)
	{
		LOG_CRI << "Attribute: name is not byXiSui!";
		return false;
	}
	const char* pszVal_byXiSui = pElemChild->Attribute("value");
	if(pszVal_byXiSui == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byXiSui, s.byXiSui))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwDujieExp is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwDujieExp") != 0)
	{
		LOG_CRI << "Attribute: name is not dwDujieExp!";
		return false;
	}
	const char* pszVal_dwDujieExp = pElemChild->Attribute("value");
	if(pszVal_dwDujieExp == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwDujieExp, s.dwDujieExp))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwSpiritPower is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwSpiritPower") != 0)
	{
		LOG_CRI << "Attribute: name is not dwSpiritPower!";
		return false;
	}
	const char* pszVal_dwSpiritPower = pElemChild->Attribute("value");
	if(pszVal_dwSpiritPower == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwSpiritPower, s.dwSpiritPower))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SFighterDBInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SFighterDBInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("数据库同步到游戏服务器的将信息"));
	unique_ptr<TiXmlElement> pElem_qwInstID(new TiXmlElement("UINT64"));
	if(pElem_qwInstID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwInstID->SetAttribute("name", "qwInstID");
	pElem_qwInstID->SetAttribute("value", NumberToString(s.qwInstID).c_str());
	pElem_qwInstID->SetAttribute("comment", ToUTF8Ptr("将唯一ID"));
	if(rElement.LinkEndChild(pElem_qwInstID.get()) != NULL)
		pElem_qwInstID.release();
	unique_ptr<TiXmlElement> pElem_qwRoleID(new TiXmlElement("UINT64"));
	if(pElem_qwRoleID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwRoleID->SetAttribute("name", "qwRoleID");
	pElem_qwRoleID->SetAttribute("value", NumberToString(s.qwRoleID).c_str());
	pElem_qwRoleID->SetAttribute("comment", ToUTF8Ptr("所属玩家ID"));
	if(rElement.LinkEndChild(pElem_qwRoleID.get()) != NULL)
		pElem_qwRoleID.release();
	unique_ptr<TiXmlElement> pElem_wFighterID(new TiXmlElement("UINT16"));
	if(pElem_wFighterID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wFighterID->SetAttribute("name", "wFighterID");
	pElem_wFighterID->SetAttribute("value", NumberToString(s.wFighterID).c_str());
	pElem_wFighterID->SetAttribute("comment", ToUTF8Ptr("将类型ID"));
	if(rElement.LinkEndChild(pElem_wFighterID.get()) != NULL)
		pElem_wFighterID.release();
	unique_ptr<TiXmlElement> pElem_byRecruited(new TiXmlElement("UINT8"));
	if(pElem_byRecruited == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byRecruited->SetAttribute("name", "byRecruited");
	pElem_byRecruited->SetAttribute("value", NumberToString(s.byRecruited).c_str());
	pElem_byRecruited->SetAttribute("comment", ToUTF8Ptr("是否已招募"));
	if(rElement.LinkEndChild(pElem_byRecruited.get()) != NULL)
		pElem_byRecruited.release();
	unique_ptr<TiXmlElement> pElem_byStar(new TiXmlElement("UINT8"));
	if(pElem_byStar == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byStar->SetAttribute("name", "byStar");
	pElem_byStar->SetAttribute("value", NumberToString(s.byStar).c_str());
	pElem_byStar->SetAttribute("comment", ToUTF8Ptr("当前星级"));
	if(rElement.LinkEndChild(pElem_byStar.get()) != NULL)
		pElem_byStar.release();
	unique_ptr<TiXmlElement> pElem_iSlot(new TiXmlElement("INT32"));
	if(pElem_iSlot == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_iSlot->SetAttribute("name", "iSlot");
	pElem_iSlot->SetAttribute("value", NumberToString(s.iSlot).c_str());
	pElem_iSlot->SetAttribute("comment", ToUTF8Ptr("将位置"));
	if(rElement.LinkEndChild(pElem_iSlot.get()) != NULL)
		pElem_iSlot.release();
	unique_ptr<TiXmlElement> pElem_iPos(new TiXmlElement("INT32"));
	if(pElem_iPos == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_iPos->SetAttribute("name", "iPos");
	pElem_iPos->SetAttribute("value", NumberToString(s.iPos).c_str());
	pElem_iPos->SetAttribute("comment", ToUTF8Ptr("阵型中的位置"));
	if(rElement.LinkEndChild(pElem_iPos.get()) != NULL)
		pElem_iPos.release();
	unique_ptr<TiXmlElement> pElem_fPotential(new TiXmlElement("float"));
	if(pElem_fPotential == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_fPotential->SetAttribute("name", "fPotential");
	pElem_fPotential->SetAttribute("value", NumberToString(s.fPotential).c_str());
	pElem_fPotential->SetAttribute("comment", ToUTF8Ptr("潜力"));
	if(rElement.LinkEndChild(pElem_fPotential.get()) != NULL)
		pElem_fPotential.release();
	unique_ptr<TiXmlElement> pElem_fCapacity(new TiXmlElement("float"));
	if(pElem_fCapacity == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_fCapacity->SetAttribute("name", "fCapacity");
	pElem_fCapacity->SetAttribute("value", NumberToString(s.fCapacity).c_str());
	pElem_fCapacity->SetAttribute("comment", ToUTF8Ptr("资质"));
	if(rElement.LinkEndChild(pElem_fCapacity.get()) != NULL)
		pElem_fCapacity.release();
	unique_ptr<TiXmlElement> pElem_byLevel(new TiXmlElement("UINT8"));
	if(pElem_byLevel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byLevel->SetAttribute("name", "byLevel");
	pElem_byLevel->SetAttribute("value", NumberToString(s.byLevel).c_str());
	pElem_byLevel->SetAttribute("comment", ToUTF8Ptr("等级"));
	if(rElement.LinkEndChild(pElem_byLevel.get()) != NULL)
		pElem_byLevel.release();
	unique_ptr<TiXmlElement> pElem_qwExp(new TiXmlElement("UINT64"));
	if(pElem_qwExp == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwExp->SetAttribute("name", "qwExp");
	pElem_qwExp->SetAttribute("value", NumberToString(s.qwExp).c_str());
	pElem_qwExp->SetAttribute("comment", ToUTF8Ptr("经验"));
	if(rElement.LinkEndChild(pElem_qwExp.get()) != NULL)
		pElem_qwExp.release();
	unique_ptr<TiXmlElement> pElem_byLianPi(new TiXmlElement("UINT8"));
	if(pElem_byLianPi == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byLianPi->SetAttribute("name", "byLianPi");
	pElem_byLianPi->SetAttribute("value", NumberToString(s.byLianPi).c_str());
	pElem_byLianPi->SetAttribute("comment", ToUTF8Ptr("炼皮"));
	if(rElement.LinkEndChild(pElem_byLianPi.get()) != NULL)
		pElem_byLianPi.release();
	unique_ptr<TiXmlElement> pElem_byTongJin(new TiXmlElement("UINT8"));
	if(pElem_byTongJin == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byTongJin->SetAttribute("name", "byTongJin");
	pElem_byTongJin->SetAttribute("value", NumberToString(s.byTongJin).c_str());
	pElem_byTongJin->SetAttribute("comment", ToUTF8Ptr("通筋"));
	if(rElement.LinkEndChild(pElem_byTongJin.get()) != NULL)
		pElem_byTongJin.release();
	unique_ptr<TiXmlElement> pElem_byQiangJi(new TiXmlElement("UINT8"));
	if(pElem_byQiangJi == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byQiangJi->SetAttribute("name", "byQiangJi");
	pElem_byQiangJi->SetAttribute("value", NumberToString(s.byQiangJi).c_str());
	pElem_byQiangJi->SetAttribute("comment", ToUTF8Ptr("强肌"));
	if(rElement.LinkEndChild(pElem_byQiangJi.get()) != NULL)
		pElem_byQiangJi.release();
	unique_ptr<TiXmlElement> pElem_byDuanGu(new TiXmlElement("UINT8"));
	if(pElem_byDuanGu == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byDuanGu->SetAttribute("name", "byDuanGu");
	pElem_byDuanGu->SetAttribute("value", NumberToString(s.byDuanGu).c_str());
	pElem_byDuanGu->SetAttribute("comment", ToUTF8Ptr("锻骨"));
	if(rElement.LinkEndChild(pElem_byDuanGu.get()) != NULL)
		pElem_byDuanGu.release();
	unique_ptr<TiXmlElement> pElem_byHuoLuo(new TiXmlElement("UINT8"));
	if(pElem_byHuoLuo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byHuoLuo->SetAttribute("name", "byHuoLuo");
	pElem_byHuoLuo->SetAttribute("value", NumberToString(s.byHuoLuo).c_str());
	pElem_byHuoLuo->SetAttribute("comment", ToUTF8Ptr("活络"));
	if(rElement.LinkEndChild(pElem_byHuoLuo.get()) != NULL)
		pElem_byHuoLuo.release();
	unique_ptr<TiXmlElement> pElem_byXiSui(new TiXmlElement("UINT8"));
	if(pElem_byXiSui == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byXiSui->SetAttribute("name", "byXiSui");
	pElem_byXiSui->SetAttribute("value", NumberToString(s.byXiSui).c_str());
	pElem_byXiSui->SetAttribute("comment", ToUTF8Ptr("洗髓"));
	if(rElement.LinkEndChild(pElem_byXiSui.get()) != NULL)
		pElem_byXiSui.release();
	unique_ptr<TiXmlElement> pElem_dwDujieExp(new TiXmlElement("UINT32"));
	if(pElem_dwDujieExp == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwDujieExp->SetAttribute("name", "dwDujieExp");
	pElem_dwDujieExp->SetAttribute("value", NumberToString(s.dwDujieExp).c_str());
	pElem_dwDujieExp->SetAttribute("comment", ToUTF8Ptr("散仙渡劫经验"));
	if(rElement.LinkEndChild(pElem_dwDujieExp.get()) != NULL)
		pElem_dwDujieExp.release();
	unique_ptr<TiXmlElement> pElem_dwSpiritPower(new TiXmlElement("UINT32"));
	if(pElem_dwSpiritPower == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwSpiritPower->SetAttribute("name", "dwSpiritPower");
	pElem_dwSpiritPower->SetAttribute("value", NumberToString(s.dwSpiritPower).c_str());
	pElem_dwSpiritPower->SetAttribute("comment", ToUTF8Ptr("元神力"));
	if(rElement.LinkEndChild(pElem_dwSpiritPower.get()) != NULL)
		pElem_dwSpiritPower.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecFighterDBInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SFighterDBInfo s;
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

bool VectorToXML(const TVecFighterDBInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SFighterDBInfo"));
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

SSkillDBInfo::SSkillDBInfo() : qwOwnerID(0), dwUpSkill1(0), dwUpSkill2(0), dwUpSkill3(0), dwUpSkill4(0), 
			dwUpSkill5(0), dwUpSkill6(0), dwSkill1(0), dwSkill2(0), dwSkill3(0), 
			dwSkill4(0), dwSkill5(0), dwSkill6(0), dwSkill7(0), dwSkill8(0), 
			dwSkill9(0), dwRune1(0), dwRune2(0), dwRune3(0), dwRune4(0), 
			dwRune5(0), dwRune6(0), dwRune7(0), dwRune8(0), dwRune9(0), 
			dwSkillAdv1(0), dwSkillAdv2(0), dwSkillAdv3(0), dwSkillAdv4(0), dwSkillAdv5(0), 
			dwSkillAdv6(0), dwSkillAdv7(0), dwSkillAdv8(0), dwSkillAdv9(0) { }

CInArchive& operator>>(CInArchive& src, SSkillDBInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwOwnerID;
	src >> s.dwUpSkill1;
	src >> s.dwUpSkill2;
	src >> s.dwUpSkill3;
	src >> s.dwUpSkill4;
	src >> s.dwUpSkill5;
	src >> s.dwUpSkill6;
	src >> s.dwSkill1;
	src >> s.dwSkill2;
	src >> s.dwSkill3;
	src >> s.dwSkill4;
	src >> s.dwSkill5;
	src >> s.dwSkill6;
	src >> s.dwSkill7;
	src >> s.dwSkill8;
	src >> s.dwSkill9;
	src >> s.dwRune1;
	src >> s.dwRune2;
	src >> s.dwRune3;
	src >> s.dwRune4;
	src >> s.dwRune5;
	src >> s.dwRune6;
	src >> s.dwRune7;
	src >> s.dwRune8;
	src >> s.dwRune9;
	src >> s.dwSkillAdv1;
	src >> s.dwSkillAdv2;
	src >> s.dwSkillAdv3;
	src >> s.dwSkillAdv4;
	src >> s.dwSkillAdv5;
	src >> s.dwSkillAdv6;
	src >> s.dwSkillAdv7;
	src >> s.dwSkillAdv8;
	src >> s.dwSkillAdv9;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SSkillDBInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.qwOwnerID;
	src << s.dwUpSkill1;
	src << s.dwUpSkill2;
	src << s.dwUpSkill3;
	src << s.dwUpSkill4;
	src << s.dwUpSkill5;
	src << s.dwUpSkill6;
	src << s.dwSkill1;
	src << s.dwSkill2;
	src << s.dwSkill3;
	src << s.dwSkill4;
	src << s.dwSkill5;
	src << s.dwSkill6;
	src << s.dwSkill7;
	src << s.dwSkill8;
	src << s.dwSkill9;
	src << s.dwRune1;
	src << s.dwRune2;
	src << s.dwRune3;
	src << s.dwRune4;
	src << s.dwRune5;
	src << s.dwRune6;
	src << s.dwRune7;
	src << s.dwRune8;
	src << s.dwRune9;
	src << s.dwSkillAdv1;
	src << s.dwSkillAdv2;
	src << s.dwSkillAdv3;
	src << s.dwSkillAdv4;
	src << s.dwSkillAdv5;
	src << s.dwSkillAdv6;
	src << s.dwSkillAdv7;
	src << s.dwSkillAdv8;
	src << s.dwSkillAdv9;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SSkillDBInfo& s)
{
	if(strcmp(rElement.Value(), "SSkillDBInfo") != 0)
	{
		LOG_CRI << "rElement is not SSkillDBInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
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
		LOG_CRI << "pElemChild for dwUpSkill1 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwUpSkill1") != 0)
	{
		LOG_CRI << "Attribute: name is not dwUpSkill1!";
		return false;
	}
	const char* pszVal_dwUpSkill1 = pElemChild->Attribute("value");
	if(pszVal_dwUpSkill1 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwUpSkill1, s.dwUpSkill1))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwUpSkill2 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwUpSkill2") != 0)
	{
		LOG_CRI << "Attribute: name is not dwUpSkill2!";
		return false;
	}
	const char* pszVal_dwUpSkill2 = pElemChild->Attribute("value");
	if(pszVal_dwUpSkill2 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwUpSkill2, s.dwUpSkill2))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwUpSkill3 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwUpSkill3") != 0)
	{
		LOG_CRI << "Attribute: name is not dwUpSkill3!";
		return false;
	}
	const char* pszVal_dwUpSkill3 = pElemChild->Attribute("value");
	if(pszVal_dwUpSkill3 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwUpSkill3, s.dwUpSkill3))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwUpSkill4 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwUpSkill4") != 0)
	{
		LOG_CRI << "Attribute: name is not dwUpSkill4!";
		return false;
	}
	const char* pszVal_dwUpSkill4 = pElemChild->Attribute("value");
	if(pszVal_dwUpSkill4 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwUpSkill4, s.dwUpSkill4))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwUpSkill5 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwUpSkill5") != 0)
	{
		LOG_CRI << "Attribute: name is not dwUpSkill5!";
		return false;
	}
	const char* pszVal_dwUpSkill5 = pElemChild->Attribute("value");
	if(pszVal_dwUpSkill5 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwUpSkill5, s.dwUpSkill5))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwUpSkill6 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwUpSkill6") != 0)
	{
		LOG_CRI << "Attribute: name is not dwUpSkill6!";
		return false;
	}
	const char* pszVal_dwUpSkill6 = pElemChild->Attribute("value");
	if(pszVal_dwUpSkill6 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwUpSkill6, s.dwUpSkill6))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwSkill1 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwSkill1") != 0)
	{
		LOG_CRI << "Attribute: name is not dwSkill1!";
		return false;
	}
	const char* pszVal_dwSkill1 = pElemChild->Attribute("value");
	if(pszVal_dwSkill1 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwSkill1, s.dwSkill1))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwSkill2 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwSkill2") != 0)
	{
		LOG_CRI << "Attribute: name is not dwSkill2!";
		return false;
	}
	const char* pszVal_dwSkill2 = pElemChild->Attribute("value");
	if(pszVal_dwSkill2 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwSkill2, s.dwSkill2))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwSkill3 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwSkill3") != 0)
	{
		LOG_CRI << "Attribute: name is not dwSkill3!";
		return false;
	}
	const char* pszVal_dwSkill3 = pElemChild->Attribute("value");
	if(pszVal_dwSkill3 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwSkill3, s.dwSkill3))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwSkill4 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwSkill4") != 0)
	{
		LOG_CRI << "Attribute: name is not dwSkill4!";
		return false;
	}
	const char* pszVal_dwSkill4 = pElemChild->Attribute("value");
	if(pszVal_dwSkill4 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwSkill4, s.dwSkill4))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwSkill5 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwSkill5") != 0)
	{
		LOG_CRI << "Attribute: name is not dwSkill5!";
		return false;
	}
	const char* pszVal_dwSkill5 = pElemChild->Attribute("value");
	if(pszVal_dwSkill5 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwSkill5, s.dwSkill5))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwSkill6 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwSkill6") != 0)
	{
		LOG_CRI << "Attribute: name is not dwSkill6!";
		return false;
	}
	const char* pszVal_dwSkill6 = pElemChild->Attribute("value");
	if(pszVal_dwSkill6 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwSkill6, s.dwSkill6))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwSkill7 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwSkill7") != 0)
	{
		LOG_CRI << "Attribute: name is not dwSkill7!";
		return false;
	}
	const char* pszVal_dwSkill7 = pElemChild->Attribute("value");
	if(pszVal_dwSkill7 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwSkill7, s.dwSkill7))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwSkill8 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwSkill8") != 0)
	{
		LOG_CRI << "Attribute: name is not dwSkill8!";
		return false;
	}
	const char* pszVal_dwSkill8 = pElemChild->Attribute("value");
	if(pszVal_dwSkill8 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwSkill8, s.dwSkill8))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwSkill9 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwSkill9") != 0)
	{
		LOG_CRI << "Attribute: name is not dwSkill9!";
		return false;
	}
	const char* pszVal_dwSkill9 = pElemChild->Attribute("value");
	if(pszVal_dwSkill9 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwSkill9, s.dwSkill9))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwRune1 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwRune1") != 0)
	{
		LOG_CRI << "Attribute: name is not dwRune1!";
		return false;
	}
	const char* pszVal_dwRune1 = pElemChild->Attribute("value");
	if(pszVal_dwRune1 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwRune1, s.dwRune1))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwRune2 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwRune2") != 0)
	{
		LOG_CRI << "Attribute: name is not dwRune2!";
		return false;
	}
	const char* pszVal_dwRune2 = pElemChild->Attribute("value");
	if(pszVal_dwRune2 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwRune2, s.dwRune2))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwRune3 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwRune3") != 0)
	{
		LOG_CRI << "Attribute: name is not dwRune3!";
		return false;
	}
	const char* pszVal_dwRune3 = pElemChild->Attribute("value");
	if(pszVal_dwRune3 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwRune3, s.dwRune3))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwRune4 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwRune4") != 0)
	{
		LOG_CRI << "Attribute: name is not dwRune4!";
		return false;
	}
	const char* pszVal_dwRune4 = pElemChild->Attribute("value");
	if(pszVal_dwRune4 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwRune4, s.dwRune4))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwRune5 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwRune5") != 0)
	{
		LOG_CRI << "Attribute: name is not dwRune5!";
		return false;
	}
	const char* pszVal_dwRune5 = pElemChild->Attribute("value");
	if(pszVal_dwRune5 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwRune5, s.dwRune5))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwRune6 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwRune6") != 0)
	{
		LOG_CRI << "Attribute: name is not dwRune6!";
		return false;
	}
	const char* pszVal_dwRune6 = pElemChild->Attribute("value");
	if(pszVal_dwRune6 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwRune6, s.dwRune6))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwRune7 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwRune7") != 0)
	{
		LOG_CRI << "Attribute: name is not dwRune7!";
		return false;
	}
	const char* pszVal_dwRune7 = pElemChild->Attribute("value");
	if(pszVal_dwRune7 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwRune7, s.dwRune7))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwRune8 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwRune8") != 0)
	{
		LOG_CRI << "Attribute: name is not dwRune8!";
		return false;
	}
	const char* pszVal_dwRune8 = pElemChild->Attribute("value");
	if(pszVal_dwRune8 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwRune8, s.dwRune8))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwRune9 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwRune9") != 0)
	{
		LOG_CRI << "Attribute: name is not dwRune9!";
		return false;
	}
	const char* pszVal_dwRune9 = pElemChild->Attribute("value");
	if(pszVal_dwRune9 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwRune9, s.dwRune9))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwSkillAdv1 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwSkillAdv1") != 0)
	{
		LOG_CRI << "Attribute: name is not dwSkillAdv1!";
		return false;
	}
	const char* pszVal_dwSkillAdv1 = pElemChild->Attribute("value");
	if(pszVal_dwSkillAdv1 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwSkillAdv1, s.dwSkillAdv1))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwSkillAdv2 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwSkillAdv2") != 0)
	{
		LOG_CRI << "Attribute: name is not dwSkillAdv2!";
		return false;
	}
	const char* pszVal_dwSkillAdv2 = pElemChild->Attribute("value");
	if(pszVal_dwSkillAdv2 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwSkillAdv2, s.dwSkillAdv2))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwSkillAdv3 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwSkillAdv3") != 0)
	{
		LOG_CRI << "Attribute: name is not dwSkillAdv3!";
		return false;
	}
	const char* pszVal_dwSkillAdv3 = pElemChild->Attribute("value");
	if(pszVal_dwSkillAdv3 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwSkillAdv3, s.dwSkillAdv3))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwSkillAdv4 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwSkillAdv4") != 0)
	{
		LOG_CRI << "Attribute: name is not dwSkillAdv4!";
		return false;
	}
	const char* pszVal_dwSkillAdv4 = pElemChild->Attribute("value");
	if(pszVal_dwSkillAdv4 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwSkillAdv4, s.dwSkillAdv4))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwSkillAdv5 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwSkillAdv5") != 0)
	{
		LOG_CRI << "Attribute: name is not dwSkillAdv5!";
		return false;
	}
	const char* pszVal_dwSkillAdv5 = pElemChild->Attribute("value");
	if(pszVal_dwSkillAdv5 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwSkillAdv5, s.dwSkillAdv5))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwSkillAdv6 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwSkillAdv6") != 0)
	{
		LOG_CRI << "Attribute: name is not dwSkillAdv6!";
		return false;
	}
	const char* pszVal_dwSkillAdv6 = pElemChild->Attribute("value");
	if(pszVal_dwSkillAdv6 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwSkillAdv6, s.dwSkillAdv6))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwSkillAdv7 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwSkillAdv7") != 0)
	{
		LOG_CRI << "Attribute: name is not dwSkillAdv7!";
		return false;
	}
	const char* pszVal_dwSkillAdv7 = pElemChild->Attribute("value");
	if(pszVal_dwSkillAdv7 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwSkillAdv7, s.dwSkillAdv7))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwSkillAdv8 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwSkillAdv8") != 0)
	{
		LOG_CRI << "Attribute: name is not dwSkillAdv8!";
		return false;
	}
	const char* pszVal_dwSkillAdv8 = pElemChild->Attribute("value");
	if(pszVal_dwSkillAdv8 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwSkillAdv8, s.dwSkillAdv8))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwSkillAdv9 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwSkillAdv9") != 0)
	{
		LOG_CRI << "Attribute: name is not dwSkillAdv9!";
		return false;
	}
	const char* pszVal_dwSkillAdv9 = pElemChild->Attribute("value");
	if(pszVal_dwSkillAdv9 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwSkillAdv9, s.dwSkillAdv9))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SSkillDBInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SSkillDBInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("数据库同步到游戏服务器的技能信息"));
	unique_ptr<TiXmlElement> pElem_qwOwnerID(new TiXmlElement("UINT64"));
	if(pElem_qwOwnerID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwOwnerID->SetAttribute("name", "qwOwnerID");
	pElem_qwOwnerID->SetAttribute("value", NumberToString(s.qwOwnerID).c_str());
	pElem_qwOwnerID->SetAttribute("comment", ToUTF8Ptr("将唯一ID"));
	if(rElement.LinkEndChild(pElem_qwOwnerID.get()) != NULL)
		pElem_qwOwnerID.release();
	unique_ptr<TiXmlElement> pElem_dwUpSkill1(new TiXmlElement("UINT32"));
	if(pElem_dwUpSkill1 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwUpSkill1->SetAttribute("name", "dwUpSkill1");
	pElem_dwUpSkill1->SetAttribute("value", NumberToString(s.dwUpSkill1).c_str());
	pElem_dwUpSkill1->SetAttribute("comment", ToUTF8Ptr("使用中的技能1"));
	if(rElement.LinkEndChild(pElem_dwUpSkill1.get()) != NULL)
		pElem_dwUpSkill1.release();
	unique_ptr<TiXmlElement> pElem_dwUpSkill2(new TiXmlElement("UINT32"));
	if(pElem_dwUpSkill2 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwUpSkill2->SetAttribute("name", "dwUpSkill2");
	pElem_dwUpSkill2->SetAttribute("value", NumberToString(s.dwUpSkill2).c_str());
	pElem_dwUpSkill2->SetAttribute("comment", ToUTF8Ptr("使用中的技能2"));
	if(rElement.LinkEndChild(pElem_dwUpSkill2.get()) != NULL)
		pElem_dwUpSkill2.release();
	unique_ptr<TiXmlElement> pElem_dwUpSkill3(new TiXmlElement("UINT32"));
	if(pElem_dwUpSkill3 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwUpSkill3->SetAttribute("name", "dwUpSkill3");
	pElem_dwUpSkill3->SetAttribute("value", NumberToString(s.dwUpSkill3).c_str());
	pElem_dwUpSkill3->SetAttribute("comment", ToUTF8Ptr("使用中的技能3"));
	if(rElement.LinkEndChild(pElem_dwUpSkill3.get()) != NULL)
		pElem_dwUpSkill3.release();
	unique_ptr<TiXmlElement> pElem_dwUpSkill4(new TiXmlElement("UINT32"));
	if(pElem_dwUpSkill4 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwUpSkill4->SetAttribute("name", "dwUpSkill4");
	pElem_dwUpSkill4->SetAttribute("value", NumberToString(s.dwUpSkill4).c_str());
	pElem_dwUpSkill4->SetAttribute("comment", ToUTF8Ptr("使用中的技能4"));
	if(rElement.LinkEndChild(pElem_dwUpSkill4.get()) != NULL)
		pElem_dwUpSkill4.release();
	unique_ptr<TiXmlElement> pElem_dwUpSkill5(new TiXmlElement("UINT32"));
	if(pElem_dwUpSkill5 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwUpSkill5->SetAttribute("name", "dwUpSkill5");
	pElem_dwUpSkill5->SetAttribute("value", NumberToString(s.dwUpSkill5).c_str());
	pElem_dwUpSkill5->SetAttribute("comment", ToUTF8Ptr("使用中的技能5"));
	if(rElement.LinkEndChild(pElem_dwUpSkill5.get()) != NULL)
		pElem_dwUpSkill5.release();
	unique_ptr<TiXmlElement> pElem_dwUpSkill6(new TiXmlElement("UINT32"));
	if(pElem_dwUpSkill6 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwUpSkill6->SetAttribute("name", "dwUpSkill6");
	pElem_dwUpSkill6->SetAttribute("value", NumberToString(s.dwUpSkill6).c_str());
	pElem_dwUpSkill6->SetAttribute("comment", ToUTF8Ptr("使用中的技能6"));
	if(rElement.LinkEndChild(pElem_dwUpSkill6.get()) != NULL)
		pElem_dwUpSkill6.release();
	unique_ptr<TiXmlElement> pElem_dwSkill1(new TiXmlElement("UINT32"));
	if(pElem_dwSkill1 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwSkill1->SetAttribute("name", "dwSkill1");
	pElem_dwSkill1->SetAttribute("value", NumberToString(s.dwSkill1).c_str());
	pElem_dwSkill1->SetAttribute("comment", ToUTF8Ptr("技能1"));
	if(rElement.LinkEndChild(pElem_dwSkill1.get()) != NULL)
		pElem_dwSkill1.release();
	unique_ptr<TiXmlElement> pElem_dwSkill2(new TiXmlElement("UINT32"));
	if(pElem_dwSkill2 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwSkill2->SetAttribute("name", "dwSkill2");
	pElem_dwSkill2->SetAttribute("value", NumberToString(s.dwSkill2).c_str());
	pElem_dwSkill2->SetAttribute("comment", ToUTF8Ptr("技能2"));
	if(rElement.LinkEndChild(pElem_dwSkill2.get()) != NULL)
		pElem_dwSkill2.release();
	unique_ptr<TiXmlElement> pElem_dwSkill3(new TiXmlElement("UINT32"));
	if(pElem_dwSkill3 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwSkill3->SetAttribute("name", "dwSkill3");
	pElem_dwSkill3->SetAttribute("value", NumberToString(s.dwSkill3).c_str());
	pElem_dwSkill3->SetAttribute("comment", ToUTF8Ptr("技能3"));
	if(rElement.LinkEndChild(pElem_dwSkill3.get()) != NULL)
		pElem_dwSkill3.release();
	unique_ptr<TiXmlElement> pElem_dwSkill4(new TiXmlElement("UINT32"));
	if(pElem_dwSkill4 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwSkill4->SetAttribute("name", "dwSkill4");
	pElem_dwSkill4->SetAttribute("value", NumberToString(s.dwSkill4).c_str());
	pElem_dwSkill4->SetAttribute("comment", ToUTF8Ptr("技能4"));
	if(rElement.LinkEndChild(pElem_dwSkill4.get()) != NULL)
		pElem_dwSkill4.release();
	unique_ptr<TiXmlElement> pElem_dwSkill5(new TiXmlElement("UINT32"));
	if(pElem_dwSkill5 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwSkill5->SetAttribute("name", "dwSkill5");
	pElem_dwSkill5->SetAttribute("value", NumberToString(s.dwSkill5).c_str());
	pElem_dwSkill5->SetAttribute("comment", ToUTF8Ptr("技能5"));
	if(rElement.LinkEndChild(pElem_dwSkill5.get()) != NULL)
		pElem_dwSkill5.release();
	unique_ptr<TiXmlElement> pElem_dwSkill6(new TiXmlElement("UINT32"));
	if(pElem_dwSkill6 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwSkill6->SetAttribute("name", "dwSkill6");
	pElem_dwSkill6->SetAttribute("value", NumberToString(s.dwSkill6).c_str());
	pElem_dwSkill6->SetAttribute("comment", ToUTF8Ptr("技能6"));
	if(rElement.LinkEndChild(pElem_dwSkill6.get()) != NULL)
		pElem_dwSkill6.release();
	unique_ptr<TiXmlElement> pElem_dwSkill7(new TiXmlElement("UINT32"));
	if(pElem_dwSkill7 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwSkill7->SetAttribute("name", "dwSkill7");
	pElem_dwSkill7->SetAttribute("value", NumberToString(s.dwSkill7).c_str());
	pElem_dwSkill7->SetAttribute("comment", ToUTF8Ptr("技能7"));
	if(rElement.LinkEndChild(pElem_dwSkill7.get()) != NULL)
		pElem_dwSkill7.release();
	unique_ptr<TiXmlElement> pElem_dwSkill8(new TiXmlElement("UINT32"));
	if(pElem_dwSkill8 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwSkill8->SetAttribute("name", "dwSkill8");
	pElem_dwSkill8->SetAttribute("value", NumberToString(s.dwSkill8).c_str());
	pElem_dwSkill8->SetAttribute("comment", ToUTF8Ptr("技能8"));
	if(rElement.LinkEndChild(pElem_dwSkill8.get()) != NULL)
		pElem_dwSkill8.release();
	unique_ptr<TiXmlElement> pElem_dwSkill9(new TiXmlElement("UINT32"));
	if(pElem_dwSkill9 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwSkill9->SetAttribute("name", "dwSkill9");
	pElem_dwSkill9->SetAttribute("value", NumberToString(s.dwSkill9).c_str());
	pElem_dwSkill9->SetAttribute("comment", ToUTF8Ptr("技能9"));
	if(rElement.LinkEndChild(pElem_dwSkill9.get()) != NULL)
		pElem_dwSkill9.release();
	unique_ptr<TiXmlElement> pElem_dwRune1(new TiXmlElement("UINT32"));
	if(pElem_dwRune1 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwRune1->SetAttribute("name", "dwRune1");
	pElem_dwRune1->SetAttribute("value", NumberToString(s.dwRune1).c_str());
	pElem_dwRune1->SetAttribute("comment", ToUTF8Ptr("符文1"));
	if(rElement.LinkEndChild(pElem_dwRune1.get()) != NULL)
		pElem_dwRune1.release();
	unique_ptr<TiXmlElement> pElem_dwRune2(new TiXmlElement("UINT32"));
	if(pElem_dwRune2 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwRune2->SetAttribute("name", "dwRune2");
	pElem_dwRune2->SetAttribute("value", NumberToString(s.dwRune2).c_str());
	pElem_dwRune2->SetAttribute("comment", ToUTF8Ptr("符文2"));
	if(rElement.LinkEndChild(pElem_dwRune2.get()) != NULL)
		pElem_dwRune2.release();
	unique_ptr<TiXmlElement> pElem_dwRune3(new TiXmlElement("UINT32"));
	if(pElem_dwRune3 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwRune3->SetAttribute("name", "dwRune3");
	pElem_dwRune3->SetAttribute("value", NumberToString(s.dwRune3).c_str());
	pElem_dwRune3->SetAttribute("comment", ToUTF8Ptr("符文3"));
	if(rElement.LinkEndChild(pElem_dwRune3.get()) != NULL)
		pElem_dwRune3.release();
	unique_ptr<TiXmlElement> pElem_dwRune4(new TiXmlElement("UINT32"));
	if(pElem_dwRune4 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwRune4->SetAttribute("name", "dwRune4");
	pElem_dwRune4->SetAttribute("value", NumberToString(s.dwRune4).c_str());
	pElem_dwRune4->SetAttribute("comment", ToUTF8Ptr("符文4"));
	if(rElement.LinkEndChild(pElem_dwRune4.get()) != NULL)
		pElem_dwRune4.release();
	unique_ptr<TiXmlElement> pElem_dwRune5(new TiXmlElement("UINT32"));
	if(pElem_dwRune5 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwRune5->SetAttribute("name", "dwRune5");
	pElem_dwRune5->SetAttribute("value", NumberToString(s.dwRune5).c_str());
	pElem_dwRune5->SetAttribute("comment", ToUTF8Ptr("符文5"));
	if(rElement.LinkEndChild(pElem_dwRune5.get()) != NULL)
		pElem_dwRune5.release();
	unique_ptr<TiXmlElement> pElem_dwRune6(new TiXmlElement("UINT32"));
	if(pElem_dwRune6 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwRune6->SetAttribute("name", "dwRune6");
	pElem_dwRune6->SetAttribute("value", NumberToString(s.dwRune6).c_str());
	pElem_dwRune6->SetAttribute("comment", ToUTF8Ptr("符文6"));
	if(rElement.LinkEndChild(pElem_dwRune6.get()) != NULL)
		pElem_dwRune6.release();
	unique_ptr<TiXmlElement> pElem_dwRune7(new TiXmlElement("UINT32"));
	if(pElem_dwRune7 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwRune7->SetAttribute("name", "dwRune7");
	pElem_dwRune7->SetAttribute("value", NumberToString(s.dwRune7).c_str());
	pElem_dwRune7->SetAttribute("comment", ToUTF8Ptr("符文7"));
	if(rElement.LinkEndChild(pElem_dwRune7.get()) != NULL)
		pElem_dwRune7.release();
	unique_ptr<TiXmlElement> pElem_dwRune8(new TiXmlElement("UINT32"));
	if(pElem_dwRune8 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwRune8->SetAttribute("name", "dwRune8");
	pElem_dwRune8->SetAttribute("value", NumberToString(s.dwRune8).c_str());
	pElem_dwRune8->SetAttribute("comment", ToUTF8Ptr("符文8"));
	if(rElement.LinkEndChild(pElem_dwRune8.get()) != NULL)
		pElem_dwRune8.release();
	unique_ptr<TiXmlElement> pElem_dwRune9(new TiXmlElement("UINT32"));
	if(pElem_dwRune9 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwRune9->SetAttribute("name", "dwRune9");
	pElem_dwRune9->SetAttribute("value", NumberToString(s.dwRune9).c_str());
	pElem_dwRune9->SetAttribute("comment", ToUTF8Ptr("符文9"));
	if(rElement.LinkEndChild(pElem_dwRune9.get()) != NULL)
		pElem_dwRune9.release();
	unique_ptr<TiXmlElement> pElem_dwSkillAdv1(new TiXmlElement("UINT32"));
	if(pElem_dwSkillAdv1 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwSkillAdv1->SetAttribute("name", "dwSkillAdv1");
	pElem_dwSkillAdv1->SetAttribute("value", NumberToString(s.dwSkillAdv1).c_str());
	pElem_dwSkillAdv1->SetAttribute("comment", ToUTF8Ptr("技能进阶1"));
	if(rElement.LinkEndChild(pElem_dwSkillAdv1.get()) != NULL)
		pElem_dwSkillAdv1.release();
	unique_ptr<TiXmlElement> pElem_dwSkillAdv2(new TiXmlElement("UINT32"));
	if(pElem_dwSkillAdv2 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwSkillAdv2->SetAttribute("name", "dwSkillAdv2");
	pElem_dwSkillAdv2->SetAttribute("value", NumberToString(s.dwSkillAdv2).c_str());
	pElem_dwSkillAdv2->SetAttribute("comment", ToUTF8Ptr("技能进阶2"));
	if(rElement.LinkEndChild(pElem_dwSkillAdv2.get()) != NULL)
		pElem_dwSkillAdv2.release();
	unique_ptr<TiXmlElement> pElem_dwSkillAdv3(new TiXmlElement("UINT32"));
	if(pElem_dwSkillAdv3 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwSkillAdv3->SetAttribute("name", "dwSkillAdv3");
	pElem_dwSkillAdv3->SetAttribute("value", NumberToString(s.dwSkillAdv3).c_str());
	pElem_dwSkillAdv3->SetAttribute("comment", ToUTF8Ptr("技能进阶3"));
	if(rElement.LinkEndChild(pElem_dwSkillAdv3.get()) != NULL)
		pElem_dwSkillAdv3.release();
	unique_ptr<TiXmlElement> pElem_dwSkillAdv4(new TiXmlElement("UINT32"));
	if(pElem_dwSkillAdv4 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwSkillAdv4->SetAttribute("name", "dwSkillAdv4");
	pElem_dwSkillAdv4->SetAttribute("value", NumberToString(s.dwSkillAdv4).c_str());
	pElem_dwSkillAdv4->SetAttribute("comment", ToUTF8Ptr("技能进阶4"));
	if(rElement.LinkEndChild(pElem_dwSkillAdv4.get()) != NULL)
		pElem_dwSkillAdv4.release();
	unique_ptr<TiXmlElement> pElem_dwSkillAdv5(new TiXmlElement("UINT32"));
	if(pElem_dwSkillAdv5 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwSkillAdv5->SetAttribute("name", "dwSkillAdv5");
	pElem_dwSkillAdv5->SetAttribute("value", NumberToString(s.dwSkillAdv5).c_str());
	pElem_dwSkillAdv5->SetAttribute("comment", ToUTF8Ptr("技能进阶5"));
	if(rElement.LinkEndChild(pElem_dwSkillAdv5.get()) != NULL)
		pElem_dwSkillAdv5.release();
	unique_ptr<TiXmlElement> pElem_dwSkillAdv6(new TiXmlElement("UINT32"));
	if(pElem_dwSkillAdv6 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwSkillAdv6->SetAttribute("name", "dwSkillAdv6");
	pElem_dwSkillAdv6->SetAttribute("value", NumberToString(s.dwSkillAdv6).c_str());
	pElem_dwSkillAdv6->SetAttribute("comment", ToUTF8Ptr("技能进阶6"));
	if(rElement.LinkEndChild(pElem_dwSkillAdv6.get()) != NULL)
		pElem_dwSkillAdv6.release();
	unique_ptr<TiXmlElement> pElem_dwSkillAdv7(new TiXmlElement("UINT32"));
	if(pElem_dwSkillAdv7 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwSkillAdv7->SetAttribute("name", "dwSkillAdv7");
	pElem_dwSkillAdv7->SetAttribute("value", NumberToString(s.dwSkillAdv7).c_str());
	pElem_dwSkillAdv7->SetAttribute("comment", ToUTF8Ptr("技能进阶7"));
	if(rElement.LinkEndChild(pElem_dwSkillAdv7.get()) != NULL)
		pElem_dwSkillAdv7.release();
	unique_ptr<TiXmlElement> pElem_dwSkillAdv8(new TiXmlElement("UINT32"));
	if(pElem_dwSkillAdv8 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwSkillAdv8->SetAttribute("name", "dwSkillAdv8");
	pElem_dwSkillAdv8->SetAttribute("value", NumberToString(s.dwSkillAdv8).c_str());
	pElem_dwSkillAdv8->SetAttribute("comment", ToUTF8Ptr("技能进阶8"));
	if(rElement.LinkEndChild(pElem_dwSkillAdv8.get()) != NULL)
		pElem_dwSkillAdv8.release();
	unique_ptr<TiXmlElement> pElem_dwSkillAdv9(new TiXmlElement("UINT32"));
	if(pElem_dwSkillAdv9 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwSkillAdv9->SetAttribute("name", "dwSkillAdv9");
	pElem_dwSkillAdv9->SetAttribute("value", NumberToString(s.dwSkillAdv9).c_str());
	pElem_dwSkillAdv9->SetAttribute("comment", ToUTF8Ptr("技能进阶9"));
	if(rElement.LinkEndChild(pElem_dwSkillAdv9.get()) != NULL)
		pElem_dwSkillAdv9.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecSkillDBInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SSkillDBInfo s;
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

bool VectorToXML(const TVecSkillDBInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SSkillDBInfo"));
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

SPassiveSkillDBInfo::SPassiveSkillDBInfo() : qwOwnerID(0), qwRoleID(0), dwSkillID(0), dwSkillQuality(0), dwSkillLevel(0) { }

SPassiveSkillDBInfo::SPassiveSkillDBInfo(UINT64 qwOwnerID_, UINT64 qwRoleID_, UINT32 dwSkillID_, UINT32 dwSkillQuality_, UINT32 dwSkillLevel_)
			: qwOwnerID(qwOwnerID_), qwRoleID(qwRoleID_), dwSkillID(dwSkillID_), dwSkillQuality(dwSkillQuality_), dwSkillLevel(dwSkillLevel_) { }

CInArchive& operator>>(CInArchive& src, SPassiveSkillDBInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwOwnerID;
	src >> s.qwRoleID;
	src >> s.dwSkillID;
	src >> s.dwSkillQuality;
	src >> s.dwSkillLevel;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SPassiveSkillDBInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.qwOwnerID;
	src << s.qwRoleID;
	src << s.dwSkillID;
	src << s.dwSkillQuality;
	src << s.dwSkillLevel;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SPassiveSkillDBInfo& s)
{
	if(strcmp(rElement.Value(), "SPassiveSkillDBInfo") != 0)
	{
		LOG_CRI << "rElement is not SPassiveSkillDBInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
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
		LOG_CRI << "pElemChild for dwSkillID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwSkillID") != 0)
	{
		LOG_CRI << "Attribute: name is not dwSkillID!";
		return false;
	}
	const char* pszVal_dwSkillID = pElemChild->Attribute("value");
	if(pszVal_dwSkillID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwSkillID, s.dwSkillID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwSkillQuality is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwSkillQuality") != 0)
	{
		LOG_CRI << "Attribute: name is not dwSkillQuality!";
		return false;
	}
	const char* pszVal_dwSkillQuality = pElemChild->Attribute("value");
	if(pszVal_dwSkillQuality == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwSkillQuality, s.dwSkillQuality))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwSkillLevel is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwSkillLevel") != 0)
	{
		LOG_CRI << "Attribute: name is not dwSkillLevel!";
		return false;
	}
	const char* pszVal_dwSkillLevel = pElemChild->Attribute("value");
	if(pszVal_dwSkillLevel == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwSkillLevel, s.dwSkillLevel))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SPassiveSkillDBInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SPassiveSkillDBInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("数据库同步到游戏服务器的技能信息"));
	unique_ptr<TiXmlElement> pElem_qwOwnerID(new TiXmlElement("UINT64"));
	if(pElem_qwOwnerID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwOwnerID->SetAttribute("name", "qwOwnerID");
	pElem_qwOwnerID->SetAttribute("value", NumberToString(s.qwOwnerID).c_str());
	pElem_qwOwnerID->SetAttribute("comment", ToUTF8Ptr("将唯一ID"));
	if(rElement.LinkEndChild(pElem_qwOwnerID.get()) != NULL)
		pElem_qwOwnerID.release();
	unique_ptr<TiXmlElement> pElem_qwRoleID(new TiXmlElement("UINT64"));
	if(pElem_qwRoleID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwRoleID->SetAttribute("name", "qwRoleID");
	pElem_qwRoleID->SetAttribute("value", NumberToString(s.qwRoleID).c_str());
	pElem_qwRoleID->SetAttribute("comment", ToUTF8Ptr("玩家一ID"));
	if(rElement.LinkEndChild(pElem_qwRoleID.get()) != NULL)
		pElem_qwRoleID.release();
	unique_ptr<TiXmlElement> pElem_dwSkillID(new TiXmlElement("UINT32"));
	if(pElem_dwSkillID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwSkillID->SetAttribute("name", "dwSkillID");
	pElem_dwSkillID->SetAttribute("value", NumberToString(s.dwSkillID).c_str());
	pElem_dwSkillID->SetAttribute("comment", ToUTF8Ptr("技能ID"));
	if(rElement.LinkEndChild(pElem_dwSkillID.get()) != NULL)
		pElem_dwSkillID.release();
	unique_ptr<TiXmlElement> pElem_dwSkillQuality(new TiXmlElement("UINT32"));
	if(pElem_dwSkillQuality == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwSkillQuality->SetAttribute("name", "dwSkillQuality");
	pElem_dwSkillQuality->SetAttribute("value", NumberToString(s.dwSkillQuality).c_str());
	pElem_dwSkillQuality->SetAttribute("comment", ToUTF8Ptr("技能品质"));
	if(rElement.LinkEndChild(pElem_dwSkillQuality.get()) != NULL)
		pElem_dwSkillQuality.release();
	unique_ptr<TiXmlElement> pElem_dwSkillLevel(new TiXmlElement("UINT32"));
	if(pElem_dwSkillLevel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwSkillLevel->SetAttribute("name", "dwSkillLevel");
	pElem_dwSkillLevel->SetAttribute("value", NumberToString(s.dwSkillLevel).c_str());
	pElem_dwSkillLevel->SetAttribute("comment", ToUTF8Ptr("技能等级"));
	if(rElement.LinkEndChild(pElem_dwSkillLevel.get()) != NULL)
		pElem_dwSkillLevel.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecPassiveSkillDBInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SPassiveSkillDBInfo s;
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

bool VectorToXML(const TVecPassiveSkillDBInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SPassiveSkillDBInfo"));
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

SHeroFighterInTavernInfo::SHeroFighterInTavernInfo() : wID(0), bHired(false) { }

SHeroFighterInTavernInfo::SHeroFighterInTavernInfo(UINT16 wID_, bool bHired_) : wID(wID_), bHired(bHired_) { }

CInArchive& operator>>(CInArchive& src, SHeroFighterInTavernInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.wID;
	src >> s.bHired;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SHeroFighterInTavernInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.wID;
	src << s.bHired;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SHeroFighterInTavernInfo& s)
{
	if(strcmp(rElement.Value(), "SHeroFighterInTavernInfo") != 0)
	{
		LOG_CRI << "rElement is not SHeroFighterInTavernInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wID") != 0)
	{
		LOG_CRI << "Attribute: name is not wID!";
		return false;
	}
	const char* pszVal_wID = pElemChild->Attribute("value");
	if(pszVal_wID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wID, s.wID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for bHired is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "bool") != 0)
	{
		LOG_CRI << "pElemChild is not bool!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "bHired") != 0)
	{
		LOG_CRI << "Attribute: name is not bHired!";
		return false;
	}
	const char* pszVal_bHired = pElemChild->Attribute("value");
	if(pszVal_bHired == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_bHired, s.bHired))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SHeroFighterInTavernInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SHeroFighterInTavernInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("客栈散仙信息"));
	unique_ptr<TiXmlElement> pElem_wID(new TiXmlElement("UINT16"));
	if(pElem_wID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wID->SetAttribute("name", "wID");
	pElem_wID->SetAttribute("value", NumberToString(s.wID).c_str());
	pElem_wID->SetAttribute("comment", ToUTF8Ptr("散仙ID"));
	if(rElement.LinkEndChild(pElem_wID.get()) != NULL)
		pElem_wID.release();
	unique_ptr<TiXmlElement> pElem_bHired(new TiXmlElement("bool"));
	if(pElem_bHired == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_bHired->SetAttribute("name", "bHired");
	pElem_bHired->SetAttribute("value", NumberToString(s.bHired).c_str());
	pElem_bHired->SetAttribute("comment", ToUTF8Ptr("是否已招募"));
	if(rElement.LinkEndChild(pElem_bHired.get()) != NULL)
		pElem_bHired.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecHeroFighterInTavernInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SHeroFighterInTavernInfo s;
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

bool VectorToXML(const TVecHeroFighterInTavernInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SHeroFighterInTavernInfo"));
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

STavernInfo::STavernInfo() : wID(0) { }

STavernInfo::STavernInfo(UINT16 wID_, const TVecHeroFighterInTavernInfo& vecFighterInfo_) : wID(wID_), vecFighterInfo(vecFighterInfo_) { }

STavernInfo::STavernInfo(STavernInfo&& src) : wID(src.wID), vecFighterInfo(move(src.vecFighterInfo)) { }

STavernInfo& STavernInfo::operator=(STavernInfo&& rhs)
{
	if(this != &rhs)
	{
		this->~STavernInfo();
		new (this) STavernInfo(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, STavernInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.wID;
	src >> s.vecFighterInfo;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const STavernInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.wID;
	src << s.vecFighterInfo;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, STavernInfo& s)
{
	if(strcmp(rElement.Value(), "STavernInfo") != 0)
	{
		LOG_CRI << "rElement is not STavernInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wID") != 0)
	{
		LOG_CRI << "Attribute: name is not wID!";
		return false;
	}
	const char* pszVal_wID = pElemChild->Attribute("value");
	if(pszVal_wID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wID, s.wID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecFighterInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecHeroFighterInTavernInfo") != 0)
	{
		LOG_CRI << "pElemChild is not TVecHeroFighterInTavernInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecFighterInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not vecFighterInfo!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecFighterInfo))
	{
		LOG_CRI << "VectorFromXML for vecFighterInfo fails!";
		return false;
	}
	return true;
}

bool ToXML(const STavernInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("STavernInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("客栈信息"));
	unique_ptr<TiXmlElement> pElem_wID(new TiXmlElement("UINT16"));
	if(pElem_wID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wID->SetAttribute("name", "wID");
	pElem_wID->SetAttribute("value", NumberToString(s.wID).c_str());
	pElem_wID->SetAttribute("comment", ToUTF8Ptr("客栈ID"));
	if(rElement.LinkEndChild(pElem_wID.get()) != NULL)
		pElem_wID.release();
	unique_ptr<TiXmlElement> pElem_vecFighterInfo(new TiXmlElement("TVecHeroFighterInTavernInfo"));
	if(pElem_vecFighterInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecFighterInfo->SetAttribute("name", "vecFighterInfo");
	if(!VectorToXML(s.vecFighterInfo, *pElem_vecFighterInfo))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecFighterInfo->SetAttribute("comment", ToUTF8Ptr("客栈中散仙信息"));
	if(rElement.LinkEndChild(pElem_vecFighterInfo.get()) != NULL)
		pElem_vecFighterInfo.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecTavernInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		STavernInfo s;
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

bool VectorToXML(const TVecTavernInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("STavernInfo"));
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

SFighterBaseInfo::SFighterBaseInfo() : qwInstID(0), wFighterID(0), byRecruited(0), byStar(0), iSlot(0), 
			iPos(0), byLevel(0), qwExp(0), dwHpMax(0), dwHp(0), 
			dwAura(0), dwAuraMax(0), byLianPi(0), byTongJin(0), byQiangJi(0), 
			byDuanGu(0), byHuoLuo(0), byXiSui(0), byDujieLevel(0), dwDujieExp(0), 
			byQuality(0), dwSpiritPower(0) { }

SFighterBaseInfo::SFighterBaseInfo(SFighterBaseInfo&& src) : qwInstID(src.qwInstID), wFighterID(src.wFighterID), byRecruited(src.byRecruited), byStar(src.byStar), iSlot(src.iSlot), 
			iPos(src.iPos), byLevel(src.byLevel), qwExp(src.qwExp), strName(move(src.strName)), dwHpMax(src.dwHpMax), 
			dwHp(src.dwHp), dwAura(src.dwAura), dwAuraMax(src.dwAuraMax), byLianPi(src.byLianPi), byTongJin(src.byTongJin), 
			byQiangJi(src.byQiangJi), byDuanGu(src.byDuanGu), byHuoLuo(src.byHuoLuo), byXiSui(src.byXiSui), byDujieLevel(src.byDujieLevel), 
			dwDujieExp(src.dwDujieExp), byQuality(src.byQuality), dwSpiritPower(src.dwSpiritPower) { }

SFighterBaseInfo& SFighterBaseInfo::operator=(SFighterBaseInfo&& rhs)
{
	if(this != &rhs)
	{
		this->~SFighterBaseInfo();
		new (this) SFighterBaseInfo(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SFighterBaseInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwInstID;
	src >> s.wFighterID;
	src >> s.byRecruited;
	src >> s.byStar;
	src >> s.iSlot;
	src >> s.iPos;
	src >> s.byLevel;
	src >> s.qwExp;
	src >> s.strName;
	src >> s.dwHpMax;
	src >> s.dwHp;
	src >> s.dwAura;
	src >> s.dwAuraMax;
	src >> s.byLianPi;
	src >> s.byTongJin;
	src >> s.byQiangJi;
	src >> s.byDuanGu;
	src >> s.byHuoLuo;
	src >> s.byXiSui;
	src >> s.byDujieLevel;
	src >> s.dwDujieExp;
	src >> s.byQuality;
	src >> s.dwSpiritPower;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SFighterBaseInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.qwInstID;
	src << s.wFighterID;
	src << s.byRecruited;
	src << s.byStar;
	src << s.iSlot;
	src << s.iPos;
	src << s.byLevel;
	src << s.qwExp;
	src << s.strName;
	src << s.dwHpMax;
	src << s.dwHp;
	src << s.dwAura;
	src << s.dwAuraMax;
	src << s.byLianPi;
	src << s.byTongJin;
	src << s.byQiangJi;
	src << s.byDuanGu;
	src << s.byHuoLuo;
	src << s.byXiSui;
	src << s.byDujieLevel;
	src << s.dwDujieExp;
	src << s.byQuality;
	src << s.dwSpiritPower;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SFighterBaseInfo& s)
{
	if(strcmp(rElement.Value(), "SFighterBaseInfo") != 0)
	{
		LOG_CRI << "rElement is not SFighterBaseInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwInstID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwInstID") != 0)
	{
		LOG_CRI << "Attribute: name is not qwInstID!";
		return false;
	}
	const char* pszVal_qwInstID = pElemChild->Attribute("value");
	if(pszVal_qwInstID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwInstID, s.qwInstID))
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
		LOG_CRI << "pElemChild for byRecruited is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byRecruited") != 0)
	{
		LOG_CRI << "Attribute: name is not byRecruited!";
		return false;
	}
	const char* pszVal_byRecruited = pElemChild->Attribute("value");
	if(pszVal_byRecruited == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byRecruited, s.byRecruited))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byStar is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byStar") != 0)
	{
		LOG_CRI << "Attribute: name is not byStar!";
		return false;
	}
	const char* pszVal_byStar = pElemChild->Attribute("value");
	if(pszVal_byStar == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byStar, s.byStar))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for iSlot is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "INT32") != 0)
	{
		LOG_CRI << "pElemChild is not INT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "iSlot") != 0)
	{
		LOG_CRI << "Attribute: name is not iSlot!";
		return false;
	}
	const char* pszVal_iSlot = pElemChild->Attribute("value");
	if(pszVal_iSlot == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_iSlot, s.iSlot))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for iPos is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "INT32") != 0)
	{
		LOG_CRI << "pElemChild is not INT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "iPos") != 0)
	{
		LOG_CRI << "Attribute: name is not iPos!";
		return false;
	}
	const char* pszVal_iPos = pElemChild->Attribute("value");
	if(pszVal_iPos == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_iPos, s.iPos))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
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
		LOG_CRI << "pElemChild for qwExp is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwExp") != 0)
	{
		LOG_CRI << "Attribute: name is not qwExp!";
		return false;
	}
	const char* pszVal_qwExp = pElemChild->Attribute("value");
	if(pszVal_qwExp == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwExp, s.qwExp))
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
		LOG_CRI << "pElemChild for dwHpMax is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwHpMax") != 0)
	{
		LOG_CRI << "Attribute: name is not dwHpMax!";
		return false;
	}
	const char* pszVal_dwHpMax = pElemChild->Attribute("value");
	if(pszVal_dwHpMax == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwHpMax, s.dwHpMax))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwHp is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwHp") != 0)
	{
		LOG_CRI << "Attribute: name is not dwHp!";
		return false;
	}
	const char* pszVal_dwHp = pElemChild->Attribute("value");
	if(pszVal_dwHp == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwHp, s.dwHp))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwAura is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwAura") != 0)
	{
		LOG_CRI << "Attribute: name is not dwAura!";
		return false;
	}
	const char* pszVal_dwAura = pElemChild->Attribute("value");
	if(pszVal_dwAura == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwAura, s.dwAura))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwAuraMax is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwAuraMax") != 0)
	{
		LOG_CRI << "Attribute: name is not dwAuraMax!";
		return false;
	}
	const char* pszVal_dwAuraMax = pElemChild->Attribute("value");
	if(pszVal_dwAuraMax == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwAuraMax, s.dwAuraMax))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byLianPi is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byLianPi") != 0)
	{
		LOG_CRI << "Attribute: name is not byLianPi!";
		return false;
	}
	const char* pszVal_byLianPi = pElemChild->Attribute("value");
	if(pszVal_byLianPi == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byLianPi, s.byLianPi))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byTongJin is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byTongJin") != 0)
	{
		LOG_CRI << "Attribute: name is not byTongJin!";
		return false;
	}
	const char* pszVal_byTongJin = pElemChild->Attribute("value");
	if(pszVal_byTongJin == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byTongJin, s.byTongJin))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byQiangJi is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byQiangJi") != 0)
	{
		LOG_CRI << "Attribute: name is not byQiangJi!";
		return false;
	}
	const char* pszVal_byQiangJi = pElemChild->Attribute("value");
	if(pszVal_byQiangJi == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byQiangJi, s.byQiangJi))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byDuanGu is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byDuanGu") != 0)
	{
		LOG_CRI << "Attribute: name is not byDuanGu!";
		return false;
	}
	const char* pszVal_byDuanGu = pElemChild->Attribute("value");
	if(pszVal_byDuanGu == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byDuanGu, s.byDuanGu))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byHuoLuo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byHuoLuo") != 0)
	{
		LOG_CRI << "Attribute: name is not byHuoLuo!";
		return false;
	}
	const char* pszVal_byHuoLuo = pElemChild->Attribute("value");
	if(pszVal_byHuoLuo == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byHuoLuo, s.byHuoLuo))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byXiSui is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byXiSui") != 0)
	{
		LOG_CRI << "Attribute: name is not byXiSui!";
		return false;
	}
	const char* pszVal_byXiSui = pElemChild->Attribute("value");
	if(pszVal_byXiSui == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byXiSui, s.byXiSui))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byDujieLevel is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byDujieLevel") != 0)
	{
		LOG_CRI << "Attribute: name is not byDujieLevel!";
		return false;
	}
	const char* pszVal_byDujieLevel = pElemChild->Attribute("value");
	if(pszVal_byDujieLevel == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byDujieLevel, s.byDujieLevel))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwDujieExp is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwDujieExp") != 0)
	{
		LOG_CRI << "Attribute: name is not dwDujieExp!";
		return false;
	}
	const char* pszVal_dwDujieExp = pElemChild->Attribute("value");
	if(pszVal_dwDujieExp == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwDujieExp, s.dwDujieExp))
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
		LOG_CRI << "pElemChild for dwSpiritPower is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwSpiritPower") != 0)
	{
		LOG_CRI << "Attribute: name is not dwSpiritPower!";
		return false;
	}
	const char* pszVal_dwSpiritPower = pElemChild->Attribute("value");
	if(pszVal_dwSpiritPower == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwSpiritPower, s.dwSpiritPower))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SFighterBaseInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SFighterBaseInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("战斗者除了外观之外的杂七杂八的基本信息"));
	unique_ptr<TiXmlElement> pElem_qwInstID(new TiXmlElement("UINT64"));
	if(pElem_qwInstID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwInstID->SetAttribute("name", "qwInstID");
	pElem_qwInstID->SetAttribute("value", NumberToString(s.qwInstID).c_str());
	pElem_qwInstID->SetAttribute("comment", ToUTF8Ptr("将唯一ID"));
	if(rElement.LinkEndChild(pElem_qwInstID.get()) != NULL)
		pElem_qwInstID.release();
	unique_ptr<TiXmlElement> pElem_wFighterID(new TiXmlElement("UINT16"));
	if(pElem_wFighterID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wFighterID->SetAttribute("name", "wFighterID");
	pElem_wFighterID->SetAttribute("value", NumberToString(s.wFighterID).c_str());
	pElem_wFighterID->SetAttribute("comment", ToUTF8Ptr("将类型ID"));
	if(rElement.LinkEndChild(pElem_wFighterID.get()) != NULL)
		pElem_wFighterID.release();
	unique_ptr<TiXmlElement> pElem_byRecruited(new TiXmlElement("UINT8"));
	if(pElem_byRecruited == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byRecruited->SetAttribute("name", "byRecruited");
	pElem_byRecruited->SetAttribute("value", NumberToString(s.byRecruited).c_str());
	pElem_byRecruited->SetAttribute("comment", ToUTF8Ptr("是否已招募"));
	if(rElement.LinkEndChild(pElem_byRecruited.get()) != NULL)
		pElem_byRecruited.release();
	unique_ptr<TiXmlElement> pElem_byStar(new TiXmlElement("UINT8"));
	if(pElem_byStar == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byStar->SetAttribute("name", "byStar");
	pElem_byStar->SetAttribute("value", NumberToString(s.byStar).c_str());
	pElem_byStar->SetAttribute("comment", ToUTF8Ptr("当前星级"));
	if(rElement.LinkEndChild(pElem_byStar.get()) != NULL)
		pElem_byStar.release();
	unique_ptr<TiXmlElement> pElem_iSlot(new TiXmlElement("INT32"));
	if(pElem_iSlot == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_iSlot->SetAttribute("name", "iSlot");
	pElem_iSlot->SetAttribute("value", NumberToString(s.iSlot).c_str());
	pElem_iSlot->SetAttribute("comment", ToUTF8Ptr("将位置"));
	if(rElement.LinkEndChild(pElem_iSlot.get()) != NULL)
		pElem_iSlot.release();
	unique_ptr<TiXmlElement> pElem_iPos(new TiXmlElement("INT32"));
	if(pElem_iPos == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_iPos->SetAttribute("name", "iPos");
	pElem_iPos->SetAttribute("value", NumberToString(s.iPos).c_str());
	pElem_iPos->SetAttribute("comment", ToUTF8Ptr("阵型中的位置"));
	if(rElement.LinkEndChild(pElem_iPos.get()) != NULL)
		pElem_iPos.release();
	unique_ptr<TiXmlElement> pElem_byLevel(new TiXmlElement("UINT8"));
	if(pElem_byLevel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byLevel->SetAttribute("name", "byLevel");
	pElem_byLevel->SetAttribute("value", NumberToString(s.byLevel).c_str());
	pElem_byLevel->SetAttribute("comment", ToUTF8Ptr("等级"));
	if(rElement.LinkEndChild(pElem_byLevel.get()) != NULL)
		pElem_byLevel.release();
	unique_ptr<TiXmlElement> pElem_qwExp(new TiXmlElement("UINT64"));
	if(pElem_qwExp == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwExp->SetAttribute("name", "qwExp");
	pElem_qwExp->SetAttribute("value", NumberToString(s.qwExp).c_str());
	pElem_qwExp->SetAttribute("comment", ToUTF8Ptr("总经验"));
	if(rElement.LinkEndChild(pElem_qwExp.get()) != NULL)
		pElem_qwExp.release();
	unique_ptr<TiXmlElement> pElem_strName(new TiXmlElement("string"));
	if(pElem_strName == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strName->SetAttribute("name", "strName");
	pElem_strName->SetAttribute("value", s.strName.c_str());
	pElem_strName->SetAttribute("comment", ToUTF8Ptr("将名字"));
	if(rElement.LinkEndChild(pElem_strName.get()) != NULL)
		pElem_strName.release();
	unique_ptr<TiXmlElement> pElem_dwHpMax(new TiXmlElement("UINT32"));
	if(pElem_dwHpMax == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwHpMax->SetAttribute("name", "dwHpMax");
	pElem_dwHpMax->SetAttribute("value", NumberToString(s.dwHpMax).c_str());
	pElem_dwHpMax->SetAttribute("comment", ToUTF8Ptr("最大血量"));
	if(rElement.LinkEndChild(pElem_dwHpMax.get()) != NULL)
		pElem_dwHpMax.release();
	unique_ptr<TiXmlElement> pElem_dwHp(new TiXmlElement("UINT32"));
	if(pElem_dwHp == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwHp->SetAttribute("name", "dwHp");
	pElem_dwHp->SetAttribute("value", NumberToString(s.dwHp).c_str());
	pElem_dwHp->SetAttribute("comment", ToUTF8Ptr("当前血量"));
	if(rElement.LinkEndChild(pElem_dwHp.get()) != NULL)
		pElem_dwHp.release();
	unique_ptr<TiXmlElement> pElem_dwAura(new TiXmlElement("UINT32"));
	if(pElem_dwAura == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwAura->SetAttribute("name", "dwAura");
	pElem_dwAura->SetAttribute("value", NumberToString(s.dwAura).c_str());
	pElem_dwAura->SetAttribute("comment", ToUTF8Ptr("当前灵气"));
	if(rElement.LinkEndChild(pElem_dwAura.get()) != NULL)
		pElem_dwAura.release();
	unique_ptr<TiXmlElement> pElem_dwAuraMax(new TiXmlElement("UINT32"));
	if(pElem_dwAuraMax == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwAuraMax->SetAttribute("name", "dwAuraMax");
	pElem_dwAuraMax->SetAttribute("value", NumberToString(s.dwAuraMax).c_str());
	pElem_dwAuraMax->SetAttribute("comment", ToUTF8Ptr("最大灵气"));
	if(rElement.LinkEndChild(pElem_dwAuraMax.get()) != NULL)
		pElem_dwAuraMax.release();
	unique_ptr<TiXmlElement> pElem_byLianPi(new TiXmlElement("UINT8"));
	if(pElem_byLianPi == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byLianPi->SetAttribute("name", "byLianPi");
	pElem_byLianPi->SetAttribute("value", NumberToString(s.byLianPi).c_str());
	pElem_byLianPi->SetAttribute("comment", ToUTF8Ptr("炼皮"));
	if(rElement.LinkEndChild(pElem_byLianPi.get()) != NULL)
		pElem_byLianPi.release();
	unique_ptr<TiXmlElement> pElem_byTongJin(new TiXmlElement("UINT8"));
	if(pElem_byTongJin == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byTongJin->SetAttribute("name", "byTongJin");
	pElem_byTongJin->SetAttribute("value", NumberToString(s.byTongJin).c_str());
	pElem_byTongJin->SetAttribute("comment", ToUTF8Ptr("通筋"));
	if(rElement.LinkEndChild(pElem_byTongJin.get()) != NULL)
		pElem_byTongJin.release();
	unique_ptr<TiXmlElement> pElem_byQiangJi(new TiXmlElement("UINT8"));
	if(pElem_byQiangJi == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byQiangJi->SetAttribute("name", "byQiangJi");
	pElem_byQiangJi->SetAttribute("value", NumberToString(s.byQiangJi).c_str());
	pElem_byQiangJi->SetAttribute("comment", ToUTF8Ptr("强肌"));
	if(rElement.LinkEndChild(pElem_byQiangJi.get()) != NULL)
		pElem_byQiangJi.release();
	unique_ptr<TiXmlElement> pElem_byDuanGu(new TiXmlElement("UINT8"));
	if(pElem_byDuanGu == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byDuanGu->SetAttribute("name", "byDuanGu");
	pElem_byDuanGu->SetAttribute("value", NumberToString(s.byDuanGu).c_str());
	pElem_byDuanGu->SetAttribute("comment", ToUTF8Ptr("锻骨"));
	if(rElement.LinkEndChild(pElem_byDuanGu.get()) != NULL)
		pElem_byDuanGu.release();
	unique_ptr<TiXmlElement> pElem_byHuoLuo(new TiXmlElement("UINT8"));
	if(pElem_byHuoLuo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byHuoLuo->SetAttribute("name", "byHuoLuo");
	pElem_byHuoLuo->SetAttribute("value", NumberToString(s.byHuoLuo).c_str());
	pElem_byHuoLuo->SetAttribute("comment", ToUTF8Ptr("活络"));
	if(rElement.LinkEndChild(pElem_byHuoLuo.get()) != NULL)
		pElem_byHuoLuo.release();
	unique_ptr<TiXmlElement> pElem_byXiSui(new TiXmlElement("UINT8"));
	if(pElem_byXiSui == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byXiSui->SetAttribute("name", "byXiSui");
	pElem_byXiSui->SetAttribute("value", NumberToString(s.byXiSui).c_str());
	pElem_byXiSui->SetAttribute("comment", ToUTF8Ptr("洗髓"));
	if(rElement.LinkEndChild(pElem_byXiSui.get()) != NULL)
		pElem_byXiSui.release();
	unique_ptr<TiXmlElement> pElem_byDujieLevel(new TiXmlElement("UINT8"));
	if(pElem_byDujieLevel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byDujieLevel->SetAttribute("name", "byDujieLevel");
	pElem_byDujieLevel->SetAttribute("value", NumberToString(s.byDujieLevel).c_str());
	pElem_byDujieLevel->SetAttribute("comment", ToUTF8Ptr("散仙渡劫等级"));
	if(rElement.LinkEndChild(pElem_byDujieLevel.get()) != NULL)
		pElem_byDujieLevel.release();
	unique_ptr<TiXmlElement> pElem_dwDujieExp(new TiXmlElement("UINT32"));
	if(pElem_dwDujieExp == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwDujieExp->SetAttribute("name", "dwDujieExp");
	pElem_dwDujieExp->SetAttribute("value", NumberToString(s.dwDujieExp).c_str());
	pElem_dwDujieExp->SetAttribute("comment", ToUTF8Ptr("散仙渡劫经验"));
	if(rElement.LinkEndChild(pElem_dwDujieExp.get()) != NULL)
		pElem_dwDujieExp.release();
	unique_ptr<TiXmlElement> pElem_byQuality(new TiXmlElement("UINT8"));
	if(pElem_byQuality == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byQuality->SetAttribute("name", "byQuality");
	pElem_byQuality->SetAttribute("value", NumberToString(s.byQuality).c_str());
	pElem_byQuality->SetAttribute("comment", ToUTF8Ptr("散仙品质(颜色)"));
	if(rElement.LinkEndChild(pElem_byQuality.get()) != NULL)
		pElem_byQuality.release();
	unique_ptr<TiXmlElement> pElem_dwSpiritPower(new TiXmlElement("UINT32"));
	if(pElem_dwSpiritPower == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwSpiritPower->SetAttribute("name", "dwSpiritPower");
	pElem_dwSpiritPower->SetAttribute("value", NumberToString(s.dwSpiritPower).c_str());
	pElem_dwSpiritPower->SetAttribute("comment", ToUTF8Ptr("元神力"));
	if(rElement.LinkEndChild(pElem_dwSpiritPower.get()) != NULL)
		pElem_dwSpiritPower.release();
	return true;
}

#endif

SFightSkillInfo::SFightSkillInfo() : byIdx(0), dwSkillID(0) { }

SFightSkillInfo::SFightSkillInfo(UINT8 byIdx_, UINT32 dwSkillID_) : byIdx(byIdx_), dwSkillID(dwSkillID_) { }

CInArchive& operator>>(CInArchive& src, SFightSkillInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.byIdx;
	src >> s.dwSkillID;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SFightSkillInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.byIdx;
	src << s.dwSkillID;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SFightSkillInfo& s)
{
	if(strcmp(rElement.Value(), "SFightSkillInfo") != 0)
	{
		LOG_CRI << "rElement is not SFightSkillInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byIdx is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byIdx") != 0)
	{
		LOG_CRI << "Attribute: name is not byIdx!";
		return false;
	}
	const char* pszVal_byIdx = pElemChild->Attribute("value");
	if(pszVal_byIdx == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byIdx, s.byIdx))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwSkillID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwSkillID") != 0)
	{
		LOG_CRI << "Attribute: name is not dwSkillID!";
		return false;
	}
	const char* pszVal_dwSkillID = pElemChild->Attribute("value");
	if(pszVal_dwSkillID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwSkillID, s.dwSkillID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SFightSkillInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SFightSkillInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("参与战斗的技能信息"));
	unique_ptr<TiXmlElement> pElem_byIdx(new TiXmlElement("UINT8"));
	if(pElem_byIdx == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byIdx->SetAttribute("name", "byIdx");
	pElem_byIdx->SetAttribute("value", NumberToString(s.byIdx).c_str());
	pElem_byIdx->SetAttribute("comment", ToUTF8Ptr("技能槽idx"));
	if(rElement.LinkEndChild(pElem_byIdx.get()) != NULL)
		pElem_byIdx.release();
	unique_ptr<TiXmlElement> pElem_dwSkillID(new TiXmlElement("UINT32"));
	if(pElem_dwSkillID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwSkillID->SetAttribute("name", "dwSkillID");
	pElem_dwSkillID->SetAttribute("value", NumberToString(s.dwSkillID).c_str());
	pElem_dwSkillID->SetAttribute("comment", ToUTF8Ptr("技能ID"));
	if(rElement.LinkEndChild(pElem_dwSkillID.get()) != NULL)
		pElem_dwSkillID.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecFightSkillInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SFightSkillInfo s;
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

bool VectorToXML(const TVecFightSkillInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SFightSkillInfo"));
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

SXinFaInfo::SXinFaInfo() : dwXinFaID(0), byXinFaLvl(0), iSlot(0) { }

SXinFaInfo::SXinFaInfo(UINT32 dwXinFaID_, UINT8 byXinFaLvl_, INT32 iSlot_) : dwXinFaID(dwXinFaID_), byXinFaLvl(byXinFaLvl_), iSlot(iSlot_) { }

CInArchive& operator>>(CInArchive& src, SXinFaInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.dwXinFaID;
	src >> s.byXinFaLvl;
	src >> s.iSlot;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SXinFaInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.dwXinFaID;
	src << s.byXinFaLvl;
	src << s.iSlot;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SXinFaInfo& s)
{
	if(strcmp(rElement.Value(), "SXinFaInfo") != 0)
	{
		LOG_CRI << "rElement is not SXinFaInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwXinFaID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwXinFaID") != 0)
	{
		LOG_CRI << "Attribute: name is not dwXinFaID!";
		return false;
	}
	const char* pszVal_dwXinFaID = pElemChild->Attribute("value");
	if(pszVal_dwXinFaID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwXinFaID, s.dwXinFaID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byXinFaLvl is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byXinFaLvl") != 0)
	{
		LOG_CRI << "Attribute: name is not byXinFaLvl!";
		return false;
	}
	const char* pszVal_byXinFaLvl = pElemChild->Attribute("value");
	if(pszVal_byXinFaLvl == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byXinFaLvl, s.byXinFaLvl))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for iSlot is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "INT32") != 0)
	{
		LOG_CRI << "pElemChild is not INT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "iSlot") != 0)
	{
		LOG_CRI << "Attribute: name is not iSlot!";
		return false;
	}
	const char* pszVal_iSlot = pElemChild->Attribute("value");
	if(pszVal_iSlot == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_iSlot, s.iSlot))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SXinFaInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SXinFaInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("心法信息"));
	unique_ptr<TiXmlElement> pElem_dwXinFaID(new TiXmlElement("UINT32"));
	if(pElem_dwXinFaID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwXinFaID->SetAttribute("name", "dwXinFaID");
	pElem_dwXinFaID->SetAttribute("value", NumberToString(s.dwXinFaID).c_str());
	pElem_dwXinFaID->SetAttribute("comment", ToUTF8Ptr("心法ID"));
	if(rElement.LinkEndChild(pElem_dwXinFaID.get()) != NULL)
		pElem_dwXinFaID.release();
	unique_ptr<TiXmlElement> pElem_byXinFaLvl(new TiXmlElement("UINT8"));
	if(pElem_byXinFaLvl == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byXinFaLvl->SetAttribute("name", "byXinFaLvl");
	pElem_byXinFaLvl->SetAttribute("value", NumberToString(s.byXinFaLvl).c_str());
	pElem_byXinFaLvl->SetAttribute("comment", ToUTF8Ptr("心法等级"));
	if(rElement.LinkEndChild(pElem_byXinFaLvl.get()) != NULL)
		pElem_byXinFaLvl.release();
	unique_ptr<TiXmlElement> pElem_iSlot(new TiXmlElement("INT32"));
	if(pElem_iSlot == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_iSlot->SetAttribute("name", "iSlot");
	pElem_iSlot->SetAttribute("value", NumberToString(s.iSlot).c_str());
	pElem_iSlot->SetAttribute("comment", ToUTF8Ptr("心法槽 -1表示心法没装备"));
	if(rElement.LinkEndChild(pElem_iSlot.get()) != NULL)
		pElem_iSlot.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecXinFaInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SXinFaInfo s;
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

bool VectorToXML(const TVecXinFaInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SXinFaInfo"));
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

SXinFaDBInfo::SXinFaDBInfo() : qwRoleID(0), qwOwnerID(0), dwXinFaID(0), byXinFaLvl(0), iSlot(0) { }

SXinFaDBInfo::SXinFaDBInfo(UINT64 qwRoleID_, UINT64 qwOwnerID_, UINT32 dwXinFaID_, UINT8 byXinFaLvl_, INT32 iSlot_)
			: qwRoleID(qwRoleID_), qwOwnerID(qwOwnerID_), dwXinFaID(dwXinFaID_), byXinFaLvl(byXinFaLvl_), iSlot(iSlot_) { }

CInArchive& operator>>(CInArchive& src, SXinFaDBInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwRoleID;
	src >> s.qwOwnerID;
	src >> s.dwXinFaID;
	src >> s.byXinFaLvl;
	src >> s.iSlot;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SXinFaDBInfo& s)
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
	src << s.qwOwnerID;
	src << s.dwXinFaID;
	src << s.byXinFaLvl;
	src << s.iSlot;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SXinFaDBInfo& s)
{
	if(strcmp(rElement.Value(), "SXinFaDBInfo") != 0)
	{
		LOG_CRI << "rElement is not SXinFaDBInfo!";
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
		LOG_CRI << "pElemChild for dwXinFaID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwXinFaID") != 0)
	{
		LOG_CRI << "Attribute: name is not dwXinFaID!";
		return false;
	}
	const char* pszVal_dwXinFaID = pElemChild->Attribute("value");
	if(pszVal_dwXinFaID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwXinFaID, s.dwXinFaID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byXinFaLvl is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byXinFaLvl") != 0)
	{
		LOG_CRI << "Attribute: name is not byXinFaLvl!";
		return false;
	}
	const char* pszVal_byXinFaLvl = pElemChild->Attribute("value");
	if(pszVal_byXinFaLvl == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byXinFaLvl, s.byXinFaLvl))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for iSlot is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "INT32") != 0)
	{
		LOG_CRI << "pElemChild is not INT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "iSlot") != 0)
	{
		LOG_CRI << "Attribute: name is not iSlot!";
		return false;
	}
	const char* pszVal_iSlot = pElemChild->Attribute("value");
	if(pszVal_iSlot == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_iSlot, s.iSlot))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SXinFaDBInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SXinFaDBInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("数据库同步到游戏服务器的心法信息"));
	unique_ptr<TiXmlElement> pElem_qwRoleID(new TiXmlElement("UINT64"));
	if(pElem_qwRoleID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwRoleID->SetAttribute("name", "qwRoleID");
	pElem_qwRoleID->SetAttribute("value", NumberToString(s.qwRoleID).c_str());
	pElem_qwRoleID->SetAttribute("comment", ToUTF8Ptr("所属角色唯一ID"));
	if(rElement.LinkEndChild(pElem_qwRoleID.get()) != NULL)
		pElem_qwRoleID.release();
	unique_ptr<TiXmlElement> pElem_qwOwnerID(new TiXmlElement("UINT64"));
	if(pElem_qwOwnerID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwOwnerID->SetAttribute("name", "qwOwnerID");
	pElem_qwOwnerID->SetAttribute("value", NumberToString(s.qwOwnerID).c_str());
	pElem_qwOwnerID->SetAttribute("comment", ToUTF8Ptr("所属散仙ID"));
	if(rElement.LinkEndChild(pElem_qwOwnerID.get()) != NULL)
		pElem_qwOwnerID.release();
	unique_ptr<TiXmlElement> pElem_dwXinFaID(new TiXmlElement("UINT32"));
	if(pElem_dwXinFaID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwXinFaID->SetAttribute("name", "dwXinFaID");
	pElem_dwXinFaID->SetAttribute("value", NumberToString(s.dwXinFaID).c_str());
	pElem_dwXinFaID->SetAttribute("comment", ToUTF8Ptr("心法ID"));
	if(rElement.LinkEndChild(pElem_dwXinFaID.get()) != NULL)
		pElem_dwXinFaID.release();
	unique_ptr<TiXmlElement> pElem_byXinFaLvl(new TiXmlElement("UINT8"));
	if(pElem_byXinFaLvl == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byXinFaLvl->SetAttribute("name", "byXinFaLvl");
	pElem_byXinFaLvl->SetAttribute("value", NumberToString(s.byXinFaLvl).c_str());
	pElem_byXinFaLvl->SetAttribute("comment", ToUTF8Ptr("心法等级"));
	if(rElement.LinkEndChild(pElem_byXinFaLvl.get()) != NULL)
		pElem_byXinFaLvl.release();
	unique_ptr<TiXmlElement> pElem_iSlot(new TiXmlElement("INT32"));
	if(pElem_iSlot == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_iSlot->SetAttribute("name", "iSlot");
	pElem_iSlot->SetAttribute("value", NumberToString(s.iSlot).c_str());
	pElem_iSlot->SetAttribute("comment", ToUTF8Ptr("心法槽 -1表示心法没装备"));
	if(rElement.LinkEndChild(pElem_iSlot.get()) != NULL)
		pElem_iSlot.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecXinFaDBInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SXinFaDBInfo s;
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

bool VectorToXML(const TVecXinFaDBInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SXinFaDBInfo"));
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

SFighterInfo::SFighterInfo() { }

SFighterInfo::SFighterInfo(SFighterInfo&& src) : oBaseInfo(move(src.oBaseInfo)), oAttrVec(move(src.oAttrVec)), vActiveSkill(move(src.vActiveSkill)), vPassiveSkill(move(src.vPassiveSkill)), oPeerLees(src.oPeerLees), 
			vecXinFa(move(src.vecXinFa)), vecStoneItem(move(src.vecStoneItem)), vecEquipTrump(move(src.vecEquipTrump)) { }

SFighterInfo& SFighterInfo::operator=(SFighterInfo&& rhs)
{
	if(this != &rhs)
	{
		this->~SFighterInfo();
		new (this) SFighterInfo(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SFighterInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.oBaseInfo;
	src >> s.oAttrVec;
	src >> s.vActiveSkill;
	src >> s.vPassiveSkill;
	src >> s.oPeerLees;
	src >> s.vecXinFa;
	src >> s.vecStoneItem;
	src >> s.vecEquipTrump;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SFighterInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.oBaseInfo;
	src << s.oAttrVec;
	src << s.vActiveSkill;
	src << s.vPassiveSkill;
	src << s.oPeerLees;
	src << s.vecXinFa;
	src << s.vecStoneItem;
	src << s.vecEquipTrump;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SFighterInfo& s)
{
	if(strcmp(rElement.Value(), "SFighterInfo") != 0)
	{
		LOG_CRI << "rElement is not SFighterInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for oBaseInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "SFighterBaseInfo") != 0)
	{
		LOG_CRI << "pElemChild is not SFighterBaseInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "oBaseInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not oBaseInfo!";
		return false;
	}
	if(!FromXML(*pElemChild, s.oBaseInfo))
	{
		LOG_CRI << "FromXML for: oBaseInfo fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for oAttrVec is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "ProtoCommon::TVecFtAttrMod") != 0)
	{
		LOG_CRI << "pElemChild is not ProtoCommon::TVecFtAttrMod!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "oAttrVec") != 0)
	{
		LOG_CRI << "Attribute: name is not oAttrVec!";
		return false;
	}
	if(!NProtoCommon::VectorFromXML(*pElemChild, s.oAttrVec))
	{
		LOG_CRI << "VectorFromXML for oAttrVec fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vActiveSkill is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecFightSkillInfo") != 0)
	{
		LOG_CRI << "pElemChild is not TVecFightSkillInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vActiveSkill") != 0)
	{
		LOG_CRI << "Attribute: name is not vActiveSkill!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vActiveSkill))
	{
		LOG_CRI << "VectorFromXML for vActiveSkill fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vPassiveSkill is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecFightSkillInfo") != 0)
	{
		LOG_CRI << "pElemChild is not TVecFightSkillInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vPassiveSkill") != 0)
	{
		LOG_CRI << "Attribute: name is not vPassiveSkill!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vPassiveSkill))
	{
		LOG_CRI << "VectorFromXML for vPassiveSkill fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for oPeerLees is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "SFightSkillInfo") != 0)
	{
		LOG_CRI << "pElemChild is not SFightSkillInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "oPeerLees") != 0)
	{
		LOG_CRI << "Attribute: name is not oPeerLees!";
		return false;
	}
	if(!FromXML(*pElemChild, s.oPeerLees))
	{
		LOG_CRI << "FromXML for: oPeerLees fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecXinFa is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecXinFaInfo") != 0)
	{
		LOG_CRI << "pElemChild is not TVecXinFaInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecXinFa") != 0)
	{
		LOG_CRI << "Attribute: name is not vecXinFa!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecXinFa))
	{
		LOG_CRI << "VectorFromXML for vecXinFa fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecStoneItem is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "ItemProt::TVecItem") != 0)
	{
		LOG_CRI << "pElemChild is not ItemProt::TVecItem!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecStoneItem") != 0)
	{
		LOG_CRI << "Attribute: name is not vecStoneItem!";
		return false;
	}
	if(!NItemProt::VectorFromXML(*pElemChild, s.vecStoneItem))
	{
		LOG_CRI << "VectorFromXML for vecStoneItem fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecEquipTrump is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "ItemProt::TVecEquipTrump") != 0)
	{
		LOG_CRI << "pElemChild is not ItemProt::TVecEquipTrump!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecEquipTrump") != 0)
	{
		LOG_CRI << "Attribute: name is not vecEquipTrump!";
		return false;
	}
	if(!NItemProt::VectorFromXML(*pElemChild, s.vecEquipTrump))
	{
		LOG_CRI << "VectorFromXML for vecEquipTrump fails!";
		return false;
	}
	return true;
}

bool ToXML(const SFighterInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SFighterInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("战斗者信息"));
	unique_ptr<TiXmlElement> pElem_oBaseInfo(new TiXmlElement("SFighterBaseInfo"));
	if(pElem_oBaseInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_oBaseInfo->SetAttribute("name", "oBaseInfo");
	if(!ToXML(s.oBaseInfo, *pElem_oBaseInfo))
	{
		LOG_CRI << "oBaseInfo ToXML fails!";
		return false;
	}
	pElem_oBaseInfo->SetAttribute("comment", ToUTF8Ptr("基本信息"));
	if(rElement.LinkEndChild(pElem_oBaseInfo.get()) != NULL)
		pElem_oBaseInfo.release();
	unique_ptr<TiXmlElement> pElem_oAttrVec(new TiXmlElement("ProtoCommon::TVecFtAttrMod"));
	if(pElem_oAttrVec == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_oAttrVec->SetAttribute("name", "oAttrVec");
	if(!NProtoCommon::VectorToXML(s.oAttrVec, *pElem_oAttrVec))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_oAttrVec->SetAttribute("comment", ToUTF8Ptr("将属性"));
	if(rElement.LinkEndChild(pElem_oAttrVec.get()) != NULL)
		pElem_oAttrVec.release();
	unique_ptr<TiXmlElement> pElem_vActiveSkill(new TiXmlElement("TVecFightSkillInfo"));
	if(pElem_vActiveSkill == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vActiveSkill->SetAttribute("name", "vActiveSkill");
	if(!VectorToXML(s.vActiveSkill, *pElem_vActiveSkill))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vActiveSkill->SetAttribute("comment", ToUTF8Ptr("装备的主动技能"));
	if(rElement.LinkEndChild(pElem_vActiveSkill.get()) != NULL)
		pElem_vActiveSkill.release();
	unique_ptr<TiXmlElement> pElem_vPassiveSkill(new TiXmlElement("TVecFightSkillInfo"));
	if(pElem_vPassiveSkill == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vPassiveSkill->SetAttribute("name", "vPassiveSkill");
	if(!VectorToXML(s.vPassiveSkill, *pElem_vPassiveSkill))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vPassiveSkill->SetAttribute("comment", ToUTF8Ptr("被动技能"));
	if(rElement.LinkEndChild(pElem_vPassiveSkill.get()) != NULL)
		pElem_vPassiveSkill.release();
	unique_ptr<TiXmlElement> pElem_oPeerLees(new TiXmlElement("SFightSkillInfo"));
	if(pElem_oPeerLees == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_oPeerLees->SetAttribute("name", "oPeerLees");
	if(!ToXML(s.oPeerLees, *pElem_oPeerLees))
	{
		LOG_CRI << "oPeerLees ToXML fails!";
		return false;
	}
	pElem_oPeerLees->SetAttribute("comment", ToUTF8Ptr("无双技能"));
	if(rElement.LinkEndChild(pElem_oPeerLees.get()) != NULL)
		pElem_oPeerLees.release();
	unique_ptr<TiXmlElement> pElem_vecXinFa(new TiXmlElement("TVecXinFaInfo"));
	if(pElem_vecXinFa == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecXinFa->SetAttribute("name", "vecXinFa");
	if(!VectorToXML(s.vecXinFa, *pElem_vecXinFa))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecXinFa->SetAttribute("comment", ToUTF8Ptr("散仙已经学会的心法信息(注：供客户端计算属性百分比加成)"));
	if(rElement.LinkEndChild(pElem_vecXinFa.get()) != NULL)
		pElem_vecXinFa.release();
	unique_ptr<TiXmlElement> pElem_vecStoneItem(new TiXmlElement("ItemProt::TVecItem"));
	if(pElem_vecStoneItem == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecStoneItem->SetAttribute("name", "vecStoneItem");
	if(!NItemProt::VectorToXML(s.vecStoneItem, *pElem_vecStoneItem))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecStoneItem->SetAttribute("comment", ToUTF8Ptr("宝石信息"));
	if(rElement.LinkEndChild(pElem_vecStoneItem.get()) != NULL)
		pElem_vecStoneItem.release();
	unique_ptr<TiXmlElement> pElem_vecEquipTrump(new TiXmlElement("ItemProt::TVecEquipTrump"));
	if(pElem_vecEquipTrump == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecEquipTrump->SetAttribute("name", "vecEquipTrump");
	if(!NItemProt::VectorToXML(s.vecEquipTrump, *pElem_vecEquipTrump))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecEquipTrump->SetAttribute("comment", ToUTF8Ptr("装备法宝信息"));
	if(rElement.LinkEndChild(pElem_vecEquipTrump.get()) != NULL)
		pElem_vecEquipTrump.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecFighterInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SFighterInfo s;
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

bool VectorToXML(const TVecFighterInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SFighterInfo"));
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

SFighterPos::SFighterPos() : qwInstID(0), iPos(0) { }

SFighterPos::SFighterPos(UINT64 qwInstID_, INT32 iPos_) : qwInstID(qwInstID_), iPos(iPos_) { }

CInArchive& operator>>(CInArchive& src, SFighterPos& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwInstID;
	src >> s.iPos;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SFighterPos& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.qwInstID;
	src << s.iPos;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SFighterPos& s)
{
	if(strcmp(rElement.Value(), "SFighterPos") != 0)
	{
		LOG_CRI << "rElement is not SFighterPos!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwInstID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwInstID") != 0)
	{
		LOG_CRI << "Attribute: name is not qwInstID!";
		return false;
	}
	const char* pszVal_qwInstID = pElemChild->Attribute("value");
	if(pszVal_qwInstID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwInstID, s.qwInstID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for iPos is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "INT32") != 0)
	{
		LOG_CRI << "pElemChild is not INT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "iPos") != 0)
	{
		LOG_CRI << "Attribute: name is not iPos!";
		return false;
	}
	const char* pszVal_iPos = pElemChild->Attribute("value");
	if(pszVal_iPos == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_iPos, s.iPos))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SFighterPos& s, TiXmlElement& rElement)
{
	rElement.SetValue("SFighterPos");
	rElement.SetAttribute("type", ToUTF8Ptr("阵型位置信息"));
	unique_ptr<TiXmlElement> pElem_qwInstID(new TiXmlElement("UINT64"));
	if(pElem_qwInstID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwInstID->SetAttribute("name", "qwInstID");
	pElem_qwInstID->SetAttribute("value", NumberToString(s.qwInstID).c_str());
	pElem_qwInstID->SetAttribute("comment", ToUTF8Ptr("将唯一ID"));
	if(rElement.LinkEndChild(pElem_qwInstID.get()) != NULL)
		pElem_qwInstID.release();
	unique_ptr<TiXmlElement> pElem_iPos(new TiXmlElement("INT32"));
	if(pElem_iPos == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_iPos->SetAttribute("name", "iPos");
	pElem_iPos->SetAttribute("value", NumberToString(s.iPos).c_str());
	pElem_iPos->SetAttribute("comment", ToUTF8Ptr("将在阵型中的位置：-1表示下阵型"));
	if(rElement.LinkEndChild(pElem_iPos.get()) != NULL)
		pElem_iPos.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecFighterPos& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SFighterPos s;
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

bool VectorToXML(const TVecFighterPos& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SFighterPos"));
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

SFighterSkill::SFighterSkill() : dwSkillID(0) { }

SFighterSkill::SFighterSkill(UINT32 dwSkillID_) : dwSkillID(dwSkillID_) { }

CInArchive& operator>>(CInArchive& src, SFighterSkill& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.dwSkillID;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SFighterSkill& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.dwSkillID;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SFighterSkill& s)
{
	if(strcmp(rElement.Value(), "SFighterSkill") != 0)
	{
		LOG_CRI << "rElement is not SFighterSkill!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwSkillID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwSkillID") != 0)
	{
		LOG_CRI << "Attribute: name is not dwSkillID!";
		return false;
	}
	const char* pszVal_dwSkillID = pElemChild->Attribute("value");
	if(pszVal_dwSkillID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwSkillID, s.dwSkillID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SFighterSkill& s, TiXmlElement& rElement)
{
	rElement.SetValue("SFighterSkill");
	rElement.SetAttribute("type", ToUTF8Ptr("散仙技能信息"));
	unique_ptr<TiXmlElement> pElem_dwSkillID(new TiXmlElement("UINT32"));
	if(pElem_dwSkillID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwSkillID->SetAttribute("name", "dwSkillID");
	pElem_dwSkillID->SetAttribute("value", NumberToString(s.dwSkillID).c_str());
	pElem_dwSkillID->SetAttribute("comment", ToUTF8Ptr("技能ID"));
	if(rElement.LinkEndChild(pElem_dwSkillID.get()) != NULL)
		pElem_dwSkillID.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecFighterSkill& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SFighterSkill s;
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

bool VectorToXML(const TVecFighterSkill& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SFighterSkill"));
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

} //namespace NFighterProt
