/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    GuildProt.cpp
//  Purpose:      帮派相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "GuildProt.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NGuildProt
{

#ifdef PROT_USE_XML

const char* EnumValToStr(EGuildDataType e)
{
	switch(e)
	{
	case eGDTBaseInfo:
		return "eGDTBaseInfo";
	case eGDTUser:
		return "eGDTUser";
	case eGDTApplyInfo:
		return "eGDTApplyInfo";
	case eGDTAuthority:
		return "eGDTAuthority";
	case eGDTBuilding:
		return "eGDTBuilding";
	case eGDTStatue:
		return "eGDTStatue";
	case eGDTLog:
		return "eGDTLog";
	case eGDTLSSBLog:
		return "eGDTLSSBLog";
	case eGDTMax:
		return "eGDTMax";
	case eGDTTech:
		return "eGDTTech";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EGuildDataType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EGuildDataType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eGDTBaseInfo", eGDTBaseInfo));
		mapStr2Val.insert(make_pair("eGDTUser", eGDTUser));
		mapStr2Val.insert(make_pair("eGDTApplyInfo", eGDTApplyInfo));
		mapStr2Val.insert(make_pair("eGDTAuthority", eGDTAuthority));
		mapStr2Val.insert(make_pair("eGDTBuilding", eGDTBuilding));
		mapStr2Val.insert(make_pair("eGDTStatue", eGDTStatue));
		mapStr2Val.insert(make_pair("eGDTLog", eGDTLog));
		mapStr2Val.insert(make_pair("eGDTLSSBLog", eGDTLSSBLog));
		mapStr2Val.insert(make_pair("eGDTMax", eGDTMax));
		mapStr2Val.insert(make_pair("eGDTTech", eGDTTech));
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

const char* GetDescription(EGuildDataType e)
{
	switch(e)
	{
	case eGDTBaseInfo:
		return "帮派基本数据";
	case eGDTUser:
		return "帮派成员信息";
	case eGDTApplyInfo:
		return "帮派申请列表信息";
	case eGDTAuthority:
		return "帮派职位可选权限";
	case eGDTBuilding:
		return "帮派建筑";
	case eGDTStatue:
		return "帮派神像";
	case eGDTLog:
		return "帮派日志";
	case eGDTLSSBLog:
		return "帮派灵山商店购买日志";
	case eGDTMax:
		return "最大值";
	case eGDTTech:
		return "帮派科技";
	default:
		return "未知错误";
	}
}

#ifdef PROT_USE_XML

const char* EnumValToStr(EGuildPubDataType e)
{
	switch(e)
	{
	case eGPDTListInfo:
		return "eGPDTListInfo";
	case eGPDTBattleInfo:
		return "eGPDTBattleInfo";
	case eGPDTMax:
		return "eGPDTMax";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EGuildPubDataType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EGuildPubDataType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eGPDTListInfo", eGPDTListInfo));
		mapStr2Val.insert(make_pair("eGPDTBattleInfo", eGPDTBattleInfo));
		mapStr2Val.insert(make_pair("eGPDTMax", eGPDTMax));
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

const char* GetDescription(EGuildPubDataType e)
{
	switch(e)
	{
	case eGPDTListInfo:
		return "帮派列表信息";
	case eGPDTBattleInfo:
		return "帮派战相关数据";
	case eGPDTMax:
		return "帮派信息最大值";
	default:
		return "未知错误";
	}
}

#ifdef PROT_USE_XML

const char* EnumValToStr(EGuildResult e)
{
	switch(e)
	{
	case eGuildSuccess:
		return "eGuildSuccess";
	case eGuildFailed:
		return "eGuildFailed";
	case eGuildNotExisted:
		return "eGuildNotExisted";
	case eGuildExisted:
		return "eGuildExisted";
	case eGuildLoading:
		return "eGuildLoading";
	case eGuildTryAgain:
		return "eGuildTryAgain";
	case eGuildLackOfMoney:
		return "eGuildLackOfMoney";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EGuildResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EGuildResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eGuildSuccess", eGuildSuccess));
		mapStr2Val.insert(make_pair("eGuildFailed", eGuildFailed));
		mapStr2Val.insert(make_pair("eGuildNotExisted", eGuildNotExisted));
		mapStr2Val.insert(make_pair("eGuildExisted", eGuildExisted));
		mapStr2Val.insert(make_pair("eGuildLoading", eGuildLoading));
		mapStr2Val.insert(make_pair("eGuildTryAgain", eGuildTryAgain));
		mapStr2Val.insert(make_pair("eGuildLackOfMoney", eGuildLackOfMoney));
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

const char* EnumValToStr(EGuildInfoResult e)
{
	switch(e)
	{
	case eGuildInofSuccess:
		return "eGuildInofSuccess";
	case eGuildInofFailed:
		return "eGuildInofFailed";
	case eGuildInofNoGuild:
		return "eGuildInofNoGuild";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EGuildInfoResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EGuildInfoResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eGuildInofSuccess", eGuildInofSuccess));
		mapStr2Val.insert(make_pair("eGuildInofFailed", eGuildInofFailed));
		mapStr2Val.insert(make_pair("eGuildInofNoGuild", eGuildInofNoGuild));
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

const char* EnumValToStr(ECreateResult e)
{
	switch(e)
	{
	case eGCreateSuccess:
		return "eGCreateSuccess";
	case eGCreateFailed:
		return "eGCreateFailed";
	case eGCreateInGuild:
		return "eGCreateInGuild";
	case eGCreateLackOfGold:
		return "eGCreateLackOfGold";
	case eGCreateLackOfLevel:
		return "eGCreateLackOfLevel";
	case eGCreateNameTooShort:
		return "eGCreateNameTooShort";
	case eGCreateNameTooLong:
		return "eGCreateNameTooLong";
	case eGCreateNameInvalid:
		return "eGCreateNameInvalid";
	case eGCreateNameExisted:
		return "eGCreateNameExisted";
	case eGCreateExisted:
		return "eGCreateExisted";
	case eGCreateLackOfVIP:
		return "eGCreateLackOfVIP";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, ECreateResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, ECreateResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eGCreateSuccess", eGCreateSuccess));
		mapStr2Val.insert(make_pair("eGCreateFailed", eGCreateFailed));
		mapStr2Val.insert(make_pair("eGCreateInGuild", eGCreateInGuild));
		mapStr2Val.insert(make_pair("eGCreateLackOfGold", eGCreateLackOfGold));
		mapStr2Val.insert(make_pair("eGCreateLackOfLevel", eGCreateLackOfLevel));
		mapStr2Val.insert(make_pair("eGCreateNameTooShort", eGCreateNameTooShort));
		mapStr2Val.insert(make_pair("eGCreateNameTooLong", eGCreateNameTooLong));
		mapStr2Val.insert(make_pair("eGCreateNameInvalid", eGCreateNameInvalid));
		mapStr2Val.insert(make_pair("eGCreateNameExisted", eGCreateNameExisted));
		mapStr2Val.insert(make_pair("eGCreateExisted", eGCreateExisted));
		mapStr2Val.insert(make_pair("eGCreateLackOfVIP", eGCreateLackOfVIP));
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

const char* EnumValToStr(EQuitResult e)
{
	switch(e)
	{
	case eGQuitSuccess:
		return "eGQuitSuccess";
	case eGQuitFailed:
		return "eGQuitFailed";
	case eGQuitNoGuild:
		return "eGQuitNoGuild";
	case eGQuitOwnerQuit:
		return "eGQuitOwnerQuit";
	case eGQuitGuildBattle:
		return "eGQuitGuildBattle";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EQuitResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EQuitResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eGQuitSuccess", eGQuitSuccess));
		mapStr2Val.insert(make_pair("eGQuitFailed", eGQuitFailed));
		mapStr2Val.insert(make_pair("eGQuitNoGuild", eGQuitNoGuild));
		mapStr2Val.insert(make_pair("eGQuitOwnerQuit", eGQuitOwnerQuit));
		mapStr2Val.insert(make_pair("eGQuitGuildBattle", eGQuitGuildBattle));
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

const char* EnumValToStr(EApplyResult e)
{
	switch(e)
	{
	case eGApplySuccess:
		return "eGApplySuccess";
	case eGApplyFailed:
		return "eGApplyFailed";
	case eGApplyGuildFull:
		return "eGApplyGuildFull";
	case eGApplyOtherGuild:
		return "eGApplyOtherGuild";
	case eGApplyInGuild:
		return "eGApplyInGuild";
	case eGApplyListFull:
		return "eGApplyListFull";
	case eGApplyNoAuthority:
		return "eGApplyNoAuthority";
	case eGApplyNoGuild:
		return "eGApplyNoGuild";
	case eGApplyNoUser:
		return "eGApplyNoUser";
	case eGApplyNotOnline:
		return "eGApplyNotOnline";
	case eGApplyAlreadyApplyed:
		return "eGApplyAlreadyApplyed";
	case eGApplyLevelLow:
		return "eGApplyLevelLow";
	case eGApplyNoSelf:
		return "eGApplyNoSelf";
	case eGApplyGuildBattle:
		return "eGApplyGuildBattle";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EApplyResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EApplyResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eGApplySuccess", eGApplySuccess));
		mapStr2Val.insert(make_pair("eGApplyFailed", eGApplyFailed));
		mapStr2Val.insert(make_pair("eGApplyGuildFull", eGApplyGuildFull));
		mapStr2Val.insert(make_pair("eGApplyOtherGuild", eGApplyOtherGuild));
		mapStr2Val.insert(make_pair("eGApplyInGuild", eGApplyInGuild));
		mapStr2Val.insert(make_pair("eGApplyListFull", eGApplyListFull));
		mapStr2Val.insert(make_pair("eGApplyNoAuthority", eGApplyNoAuthority));
		mapStr2Val.insert(make_pair("eGApplyNoGuild", eGApplyNoGuild));
		mapStr2Val.insert(make_pair("eGApplyNoUser", eGApplyNoUser));
		mapStr2Val.insert(make_pair("eGApplyNotOnline", eGApplyNotOnline));
		mapStr2Val.insert(make_pair("eGApplyAlreadyApplyed", eGApplyAlreadyApplyed));
		mapStr2Val.insert(make_pair("eGApplyLevelLow", eGApplyLevelLow));
		mapStr2Val.insert(make_pair("eGApplyNoSelf", eGApplyNoSelf));
		mapStr2Val.insert(make_pair("eGApplyGuildBattle", eGApplyGuildBattle));
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

const char* EnumValToStr(EEditInfoResult e)
{
	switch(e)
	{
	case eGEditInfoSuccess:
		return "eGEditInfoSuccess";
	case eGEditInfoFailed:
		return "eGEditInfoFailed";
	case eGEditInfoNotInGuild:
		return "eGEditInfoNotInGuild";
	case eGEditInfoNoAuthority:
		return "eGEditInfoNoAuthority";
	case eGEditInfoTooLong:
		return "eGEditInfoTooLong";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EEditInfoResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EEditInfoResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eGEditInfoSuccess", eGEditInfoSuccess));
		mapStr2Val.insert(make_pair("eGEditInfoFailed", eGEditInfoFailed));
		mapStr2Val.insert(make_pair("eGEditInfoNotInGuild", eGEditInfoNotInGuild));
		mapStr2Val.insert(make_pair("eGEditInfoNoAuthority", eGEditInfoNoAuthority));
		mapStr2Val.insert(make_pair("eGEditInfoTooLong", eGEditInfoTooLong));
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

const char* EnumValToStr(ESetAuthorityResult e)
{
	switch(e)
	{
	case eGSetAuthoritySuccess:
		return "eGSetAuthoritySuccess";
	case eGSetAuthorityFailed:
		return "eGSetAuthorityFailed";
	case eGSetAuthorityNotInGuild:
		return "eGSetAuthorityNotInGuild";
	case eGSetAuthorityNoAuthority:
		return "eGSetAuthorityNoAuthority";
	case eGSetAuthorityTooHigh:
		return "eGSetAuthorityTooHigh";
	case eGSetAuthorityNoSelfRank:
		return "eGSetAuthorityNoSelfRank";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, ESetAuthorityResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, ESetAuthorityResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eGSetAuthoritySuccess", eGSetAuthoritySuccess));
		mapStr2Val.insert(make_pair("eGSetAuthorityFailed", eGSetAuthorityFailed));
		mapStr2Val.insert(make_pair("eGSetAuthorityNotInGuild", eGSetAuthorityNotInGuild));
		mapStr2Val.insert(make_pair("eGSetAuthorityNoAuthority", eGSetAuthorityNoAuthority));
		mapStr2Val.insert(make_pair("eGSetAuthorityTooHigh", eGSetAuthorityTooHigh));
		mapStr2Val.insert(make_pair("eGSetAuthorityNoSelfRank", eGSetAuthorityNoSelfRank));
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

const char* EnumValToStr(EMemberOperateType e)
{
	switch(e)
	{
	case eGMOpTypeNone:
		return "eGMOpTypeNone";
	case eGMOpTypeUp:
		return "eGMOpTypeUp";
	case eGMOpTypeKick:
		return "eGMOpTypeKick";
	case eGMOpTypeGiveOwner:
		return "eGMOpTypeGiveOwner";
	case eGMOpTypeDown:
		return "eGMOpTypeDown";
	case eGMOpTypeFire:
		return "eGMOpTypeFire";
	case eGMOpTypeMax:
		return "eGMOpTypeMax";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EMemberOperateType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EMemberOperateType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eGMOpTypeNone", eGMOpTypeNone));
		mapStr2Val.insert(make_pair("eGMOpTypeUp", eGMOpTypeUp));
		mapStr2Val.insert(make_pair("eGMOpTypeKick", eGMOpTypeKick));
		mapStr2Val.insert(make_pair("eGMOpTypeGiveOwner", eGMOpTypeGiveOwner));
		mapStr2Val.insert(make_pair("eGMOpTypeDown", eGMOpTypeDown));
		mapStr2Val.insert(make_pair("eGMOpTypeFire", eGMOpTypeFire));
		mapStr2Val.insert(make_pair("eGMOpTypeMax", eGMOpTypeMax));
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

const char* EnumValToStr(EMemberOperateResult e)
{
	switch(e)
	{
	case eGMOpResultSuccess:
		return "eGMOpResultSuccess";
	case eGMOpResultFailed:
		return "eGMOpResultFailed";
	case eGMOpResultSelf:
		return "eGMOpResultSelf";
	case eGMOpResultNotInGuild:
		return "eGMOpResultNotInGuild";
	case eGMOpResultNoAuthority:
		return "eGMOpResultNoAuthority";
	case eGMOpResultTooHigh:
		return "eGMOpResultTooHigh";
	case eGMOpResultTooLow:
		return "eGMOpResultTooLow";
	case eGMOpResultTooMany:
		return "eGMOpResultTooMany";
	case eGMOpResultHaveImpeach:
		return "eGMOpResultHaveImpeach";
	case eGMOpResultGuildBattle:
		return "eGMOpResultGuildBattle";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EMemberOperateResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EMemberOperateResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eGMOpResultSuccess", eGMOpResultSuccess));
		mapStr2Val.insert(make_pair("eGMOpResultFailed", eGMOpResultFailed));
		mapStr2Val.insert(make_pair("eGMOpResultSelf", eGMOpResultSelf));
		mapStr2Val.insert(make_pair("eGMOpResultNotInGuild", eGMOpResultNotInGuild));
		mapStr2Val.insert(make_pair("eGMOpResultNoAuthority", eGMOpResultNoAuthority));
		mapStr2Val.insert(make_pair("eGMOpResultTooHigh", eGMOpResultTooHigh));
		mapStr2Val.insert(make_pair("eGMOpResultTooLow", eGMOpResultTooLow));
		mapStr2Val.insert(make_pair("eGMOpResultTooMany", eGMOpResultTooMany));
		mapStr2Val.insert(make_pair("eGMOpResultHaveImpeach", eGMOpResultHaveImpeach));
		mapStr2Val.insert(make_pair("eGMOpResultGuildBattle", eGMOpResultGuildBattle));
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

const char* EnumValToStr(EImpeachResult e)
{
	switch(e)
	{
	case eGImpeachResultSuccess:
		return "eGImpeachResultSuccess";
	case eGImpeachResultFailed:
		return "eGImpeachResultFailed";
	case eGImpeachResultSelf:
		return "eGImpeachResultSelf";
	case eGImpeachResultNotInGuild:
		return "eGImpeachResultNotInGuild";
	case eGImpeachResultWrongGuild:
		return "eGImpeachResultWrongGuild";
	case eGImpeachResultNoAuthority:
		return "eGImpeachResultNoAuthority";
	case eGImpeachResultHasLaunched:
		return "eGImpeachResultHasLaunched";
	case eGImpeachResultHasReplyed:
		return "eGImpeachResultHasReplyed";
	case eGImpeachResultLackOfGold:
		return "eGImpeachResultLackOfGold";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EImpeachResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EImpeachResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eGImpeachResultSuccess", eGImpeachResultSuccess));
		mapStr2Val.insert(make_pair("eGImpeachResultFailed", eGImpeachResultFailed));
		mapStr2Val.insert(make_pair("eGImpeachResultSelf", eGImpeachResultSelf));
		mapStr2Val.insert(make_pair("eGImpeachResultNotInGuild", eGImpeachResultNotInGuild));
		mapStr2Val.insert(make_pair("eGImpeachResultWrongGuild", eGImpeachResultWrongGuild));
		mapStr2Val.insert(make_pair("eGImpeachResultNoAuthority", eGImpeachResultNoAuthority));
		mapStr2Val.insert(make_pair("eGImpeachResultHasLaunched", eGImpeachResultHasLaunched));
		mapStr2Val.insert(make_pair("eGImpeachResultHasReplyed", eGImpeachResultHasReplyed));
		mapStr2Val.insert(make_pair("eGImpeachResultLackOfGold", eGImpeachResultLackOfGold));
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

const char* EnumValToStr(EMemberRank e)
{
	switch(e)
	{
	case eMemberNone:
		return "eMemberNone";
	case eMemberNormal:
		return "eMemberNormal";
	case eMemberElite:
		return "eMemberElite";
	case eMemberElder:
		return "eMemberElder";
	case eMemberViceOwner:
		return "eMemberViceOwner";
	case eMemberOwner:
		return "eMemberOwner";
	case eMemberMax:
		return "eMemberMax";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EMemberRank& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EMemberRank> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eMemberNone", eMemberNone));
		mapStr2Val.insert(make_pair("eMemberNormal", eMemberNormal));
		mapStr2Val.insert(make_pair("eMemberElite", eMemberElite));
		mapStr2Val.insert(make_pair("eMemberElder", eMemberElder));
		mapStr2Val.insert(make_pair("eMemberViceOwner", eMemberViceOwner));
		mapStr2Val.insert(make_pair("eMemberOwner", eMemberOwner));
		mapStr2Val.insert(make_pair("eMemberMax", eMemberMax));
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

const char* EnumValToStr(EBuildingType e)
{
	switch(e)
	{
	case eBuildingNone:
		return "eBuildingNone";
	case eBuildingOracle:
		return "eBuildingOracle";
	case eBuildingDepot:
		return "eBuildingDepot";
	case eBuildingSword:
		return "eBuildingSword";
	case eBuildingStore:
		return "eBuildingStore";
	case eBuildingBlood:
		return "eBuildingBlood";
	case eBuildingMax:
		return "eBuildingMax";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EBuildingType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EBuildingType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eBuildingNone", eBuildingNone));
		mapStr2Val.insert(make_pair("eBuildingOracle", eBuildingOracle));
		mapStr2Val.insert(make_pair("eBuildingDepot", eBuildingDepot));
		mapStr2Val.insert(make_pair("eBuildingSword", eBuildingSword));
		mapStr2Val.insert(make_pair("eBuildingStore", eBuildingStore));
		mapStr2Val.insert(make_pair("eBuildingBlood", eBuildingBlood));
		mapStr2Val.insert(make_pair("eBuildingMax", eBuildingMax));
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

const char* EnumValToStr(EBuildingResult e)
{
	switch(e)
	{
	case eGBuildingResultSuccess:
		return "eGBuildingResultSuccess";
	case eGBuildingResultFailed:
		return "eGBuildingResultFailed";
	case eGBuildingResultNoGuild:
		return "eGBuildingResultNoGuild";
	case eGBuildingResultLackofSilver:
		return "eGBuildingResultLackofSilver";
	case eGBuildingResultLevelMax:
		return "eGBuildingResultLevelMax";
	case eGBuildingResultNoAuthority:
		return "eGBuildingResultNoAuthority";
	case eGBuildingResultGuildLevelTooLow:
		return "eGBuildingResultGuildLevelTooLow";
	case eGBuildingResultOracleLevelTooLow:
		return "eGBuildingResultOracleLevelTooLow";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EBuildingResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EBuildingResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eGBuildingResultSuccess", eGBuildingResultSuccess));
		mapStr2Val.insert(make_pair("eGBuildingResultFailed", eGBuildingResultFailed));
		mapStr2Val.insert(make_pair("eGBuildingResultNoGuild", eGBuildingResultNoGuild));
		mapStr2Val.insert(make_pair("eGBuildingResultLackofSilver", eGBuildingResultLackofSilver));
		mapStr2Val.insert(make_pair("eGBuildingResultLevelMax", eGBuildingResultLevelMax));
		mapStr2Val.insert(make_pair("eGBuildingResultNoAuthority", eGBuildingResultNoAuthority));
		mapStr2Val.insert(make_pair("eGBuildingResultGuildLevelTooLow", eGBuildingResultGuildLevelTooLow));
		mapStr2Val.insert(make_pair("eGBuildingResultOracleLevelTooLow", eGBuildingResultOracleLevelTooLow));
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

const char* EnumValToStr(ETechType e)
{
	switch(e)
	{
	case eTechNone:
		return "eTechNone";
	case eTechAttack:
		return "eTechAttack";
	case eTechPhyDef:
		return "eTechPhyDef";
	case eTechMgcDef:
		return "eTechMgcDef";
	case eTechHP:
		return "eTechHP";
	case eTechSpeed:
		return "eTechSpeed";
	case eTechHit:
		return "eTechHit";
	case eTechDodge:
		return "eTechDodge";
	case eTechCritial:
		return "eTechCritial";
	case eTechAntiCritial:
		return "eTechAntiCritial";
	case eTechPierce:
		return "eTechPierce";
	case eTechCounter:
		return "eTechCounter";
	case eTechResist:
		return "eTechResist";
	case eTechMax:
		return "eTechMax";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, ETechType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, ETechType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eTechNone", eTechNone));
		mapStr2Val.insert(make_pair("eTechAttack", eTechAttack));
		mapStr2Val.insert(make_pair("eTechPhyDef", eTechPhyDef));
		mapStr2Val.insert(make_pair("eTechMgcDef", eTechMgcDef));
		mapStr2Val.insert(make_pair("eTechHP", eTechHP));
		mapStr2Val.insert(make_pair("eTechSpeed", eTechSpeed));
		mapStr2Val.insert(make_pair("eTechHit", eTechHit));
		mapStr2Val.insert(make_pair("eTechDodge", eTechDodge));
		mapStr2Val.insert(make_pair("eTechCritial", eTechCritial));
		mapStr2Val.insert(make_pair("eTechAntiCritial", eTechAntiCritial));
		mapStr2Val.insert(make_pair("eTechPierce", eTechPierce));
		mapStr2Val.insert(make_pair("eTechCounter", eTechCounter));
		mapStr2Val.insert(make_pair("eTechResist", eTechResist));
		mapStr2Val.insert(make_pair("eTechMax", eTechMax));
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

const char* EnumValToStr(ETechResult e)
{
	switch(e)
	{
	case eGTResultSuccess:
		return "eGTResultSuccess";
	case eGTResultFailed:
		return "eGTResultFailed";
	case eGTResultNoGuild:
		return "eGTResultNoGuild";
	case eGTResultLackofSilver:
		return "eGTResultLackofSilver";
	case eGTResultLevelMax:
		return "eGTResultLevelMax";
	case eGTResultNoAuthority:
		return "eGTResultNoAuthority";
	case eGTResultBuildingLevelTooLow:
		return "eGTResultBuildingLevelTooLow";
	case eGTResultUserLevelTooLow:
		return "eGTResultUserLevelTooLow";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, ETechResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, ETechResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eGTResultSuccess", eGTResultSuccess));
		mapStr2Val.insert(make_pair("eGTResultFailed", eGTResultFailed));
		mapStr2Val.insert(make_pair("eGTResultNoGuild", eGTResultNoGuild));
		mapStr2Val.insert(make_pair("eGTResultLackofSilver", eGTResultLackofSilver));
		mapStr2Val.insert(make_pair("eGTResultLevelMax", eGTResultLevelMax));
		mapStr2Val.insert(make_pair("eGTResultNoAuthority", eGTResultNoAuthority));
		mapStr2Val.insert(make_pair("eGTResultBuildingLevelTooLow", eGTResultBuildingLevelTooLow));
		mapStr2Val.insert(make_pair("eGTResultUserLevelTooLow", eGTResultUserLevelTooLow));
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

const char* EnumValToStr(EDonateResult e)
{
	switch(e)
	{
	case eGDResultSuccess:
		return "eGDResultSuccess";
	case eGDResultFailed:
		return "eGDResultFailed";
	case eGDResultNoGuild:
		return "eGDResultNoGuild";
	case eGDResultLackofSilver:
		return "eGDResultLackofSilver";
	case eGDResultNoAuthority:
		return "eGDResultNoAuthority";
	case eGDResultFull:
		return "eGDResultFull";
	case eGDResultDepotFull:
		return "eGDResultDepotFull";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EDonateResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EDonateResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eGDResultSuccess", eGDResultSuccess));
		mapStr2Val.insert(make_pair("eGDResultFailed", eGDResultFailed));
		mapStr2Val.insert(make_pair("eGDResultNoGuild", eGDResultNoGuild));
		mapStr2Val.insert(make_pair("eGDResultLackofSilver", eGDResultLackofSilver));
		mapStr2Val.insert(make_pair("eGDResultNoAuthority", eGDResultNoAuthority));
		mapStr2Val.insert(make_pair("eGDResultFull", eGDResultFull));
		mapStr2Val.insert(make_pair("eGDResultDepotFull", eGDResultDepotFull));
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

const char* EnumValToStr(EWorshipResult e)
{
	switch(e)
	{
	case eGWResultSuccess:
		return "eGWResultSuccess";
	case eGWResultFailed:
		return "eGWResultFailed";
	case eGWResultNoGuild:
		return "eGWResultNoGuild";
	case eGWResultLackofSilver:
		return "eGWResultLackofSilver";
	case eGWResultNoAuthority:
		return "eGWResultNoAuthority";
	case eGWResultLevelTooLow:
		return "eGWResultLevelTooLow";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EWorshipResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EWorshipResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eGWResultSuccess", eGWResultSuccess));
		mapStr2Val.insert(make_pair("eGWResultFailed", eGWResultFailed));
		mapStr2Val.insert(make_pair("eGWResultNoGuild", eGWResultNoGuild));
		mapStr2Val.insert(make_pair("eGWResultLackofSilver", eGWResultLackofSilver));
		mapStr2Val.insert(make_pair("eGWResultNoAuthority", eGWResultNoAuthority));
		mapStr2Val.insert(make_pair("eGWResultLevelTooLow", eGWResultLevelTooLow));
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

const char* EnumValToStr(ELogType e)
{
	switch(e)
	{
	case eLogNone:
		return "eLogNone";
	case eLogMember:
		return "eLogMember";
	case eLogDonate:
		return "eLogDonate";
	case eLogBuilding:
		return "eLogBuilding";
	case eLogStatue:
		return "eLogStatue";
	case eLogMax:
		return "eLogMax";
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
		mapStr2Val.insert(make_pair("eLogMember", eLogMember));
		mapStr2Val.insert(make_pair("eLogDonate", eLogDonate));
		mapStr2Val.insert(make_pair("eLogBuilding", eLogBuilding));
		mapStr2Val.insert(make_pair("eLogStatue", eLogStatue));
		mapStr2Val.insert(make_pair("eLogMax", eLogMax));
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

const char* EnumValToStr(EWorshipType e)
{
	switch(e)
	{
	case eWorshipNone:
		return "eWorshipNone";
	case eWorshipFlower:
		return "eWorshipFlower";
	case eWorshipRedFruit:
		return "eWorshipRedFruit";
	case eWorshipPeach:
		return "eWorshipPeach";
	case eWorshipMax:
		return "eWorshipMax";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EWorshipType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EWorshipType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eWorshipNone", eWorshipNone));
		mapStr2Val.insert(make_pair("eWorshipFlower", eWorshipFlower));
		mapStr2Val.insert(make_pair("eWorshipRedFruit", eWorshipRedFruit));
		mapStr2Val.insert(make_pair("eWorshipPeach", eWorshipPeach));
		mapStr2Val.insert(make_pair("eWorshipMax", eWorshipMax));
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

const char* EnumValToStr(EStatueResult e)
{
	switch(e)
	{
	case eGSResultSuccess:
		return "eGSResultSuccess";
	case eGSResultFailed:
		return "eGSResultFailed";
	case eGSResultNoGuild:
		return "eGSResultNoGuild";
	case eGSResultLackofSilver:
		return "eGSResultLackofSilver";
	case eGSResultLackofGold:
		return "eGSResultLackofGold";
	case eGSResultLevelMax:
		return "eGSResultLevelMax";
	case eGSResultNoAuthority:
		return "eGSResultNoAuthority";
	case eGSResultBuildingLevelTooLow:
		return "eGSResultBuildingLevelTooLow";
	case eGSResultWorshiped:
		return "eGSResultWorshiped";
	case eGSResultTooFast:
		return "eGSResultTooFast";
	case eGSResultNotToday:
		return "eGSResultNotToday";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EStatueResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EStatueResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eGSResultSuccess", eGSResultSuccess));
		mapStr2Val.insert(make_pair("eGSResultFailed", eGSResultFailed));
		mapStr2Val.insert(make_pair("eGSResultNoGuild", eGSResultNoGuild));
		mapStr2Val.insert(make_pair("eGSResultLackofSilver", eGSResultLackofSilver));
		mapStr2Val.insert(make_pair("eGSResultLackofGold", eGSResultLackofGold));
		mapStr2Val.insert(make_pair("eGSResultLevelMax", eGSResultLevelMax));
		mapStr2Val.insert(make_pair("eGSResultNoAuthority", eGSResultNoAuthority));
		mapStr2Val.insert(make_pair("eGSResultBuildingLevelTooLow", eGSResultBuildingLevelTooLow));
		mapStr2Val.insert(make_pair("eGSResultWorshiped", eGSResultWorshiped));
		mapStr2Val.insert(make_pair("eGSResultTooFast", eGSResultTooFast));
		mapStr2Val.insert(make_pair("eGSResultNotToday", eGSResultNotToday));
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

const char* EnumValToStr(EGuildXiheResult e)
{
	switch(e)
	{
	case eXiheResultSuccess:
		return "eXiheResultSuccess";
	case eXiheResultFailed:
		return "eXiheResultFailed";
	case eXiheResultNoGuild:
		return "eXiheResultNoGuild";
	case eXiheResultUnfinish:
		return "eXiheResultUnfinish";
	case eXiheResultFinish:
		return "eXiheResultFinish";
	case eXiheResultHasRequest:
		return "eXiheResultHasRequest";
	case eXiheResultNotRequest:
		return "eXiheResultNotRequest";
	case eXiheResultNotTruck:
		return "eXiheResultNotTruck";
	case eXiheResultNotItem:
		return "eXiheResultNotItem";
	case eXiheResultNotGold:
		return "eXiheResultNotGold";
	case eXiheResultNoSameGuild:
		return "eXiheResultNoSameGuild";
	case eXiheResultForHelpNumMax:
		return "eXiheResultForHelpNumMax";
	case eXiheResultNotRequestLimit:
		return "eXiheResultNotRequestLimit";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EGuildXiheResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EGuildXiheResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eXiheResultSuccess", eXiheResultSuccess));
		mapStr2Val.insert(make_pair("eXiheResultFailed", eXiheResultFailed));
		mapStr2Val.insert(make_pair("eXiheResultNoGuild", eXiheResultNoGuild));
		mapStr2Val.insert(make_pair("eXiheResultUnfinish", eXiheResultUnfinish));
		mapStr2Val.insert(make_pair("eXiheResultFinish", eXiheResultFinish));
		mapStr2Val.insert(make_pair("eXiheResultHasRequest", eXiheResultHasRequest));
		mapStr2Val.insert(make_pair("eXiheResultNotRequest", eXiheResultNotRequest));
		mapStr2Val.insert(make_pair("eXiheResultNotTruck", eXiheResultNotTruck));
		mapStr2Val.insert(make_pair("eXiheResultNotItem", eXiheResultNotItem));
		mapStr2Val.insert(make_pair("eXiheResultNotGold", eXiheResultNotGold));
		mapStr2Val.insert(make_pair("eXiheResultNoSameGuild", eXiheResultNoSameGuild));
		mapStr2Val.insert(make_pair("eXiheResultForHelpNumMax", eXiheResultForHelpNumMax));
		mapStr2Val.insert(make_pair("eXiheResultNotRequestLimit", eXiheResultNotRequestLimit));
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

const char* EnumValToStr(EXiheStage e)
{
	switch(e)
	{
	case eXiheStageShipGoods:
		return "eXiheStageShipGoods";
	case eXiheStageTaskCool:
		return "eXiheStageTaskCool";
	case eXiheStageWaitAcess:
		return "eXiheStageWaitAcess";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EXiheStage& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EXiheStage> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eXiheStageShipGoods", eXiheStageShipGoods));
		mapStr2Val.insert(make_pair("eXiheStageTaskCool", eXiheStageTaskCool));
		mapStr2Val.insert(make_pair("eXiheStageWaitAcess", eXiheStageWaitAcess));
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

const char* EnumValToStr(EXiheTaskStatus e)
{
	switch(e)
	{
	case eXiheTaskUnfinish:
		return "eXiheTaskUnfinish";
	case eXiheTaskRequest:
		return "eXiheTaskRequest";
	case eXiheTaskFinishURe:
		return "eXiheTaskFinishURe";
	case eXiheTaskFinishRe:
		return "eXiheTaskFinishRe";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EXiheTaskStatus& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EXiheTaskStatus> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eXiheTaskUnfinish", eXiheTaskUnfinish));
		mapStr2Val.insert(make_pair("eXiheTaskRequest", eXiheTaskRequest));
		mapStr2Val.insert(make_pair("eXiheTaskFinishURe", eXiheTaskFinishURe));
		mapStr2Val.insert(make_pair("eXiheTaskFinishRe", eXiheTaskFinishRe));
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

const char* EnumValToStr(EGuildExchangeRet e)
{
	switch(e)
	{
	case eGuildExchange_Failed:
		return "eGuildExchange_Failed";
	case eGuildExchange_Sucess:
		return "eGuildExchange_Sucess";
	case eGuildExchange_ErrorPack:
		return "eGuildExchange_ErrorPack";
	case eGuildExchange_MoneyLimit:
		return "eGuildExchange_MoneyLimit";
	case eGuildExchange_CondLimitA:
		return "eGuildExchange_CondLimitA";
	case eGuildExchange_CondLimitB:
		return "eGuildExchange_CondLimitB";
	case eGuildExchange_CondLimitC:
		return "eGuildExchange_CondLimitC";
	case eGuildExchange_NoLingShan:
		return "eGuildExchange_NoLingShan";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EGuildExchangeRet& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EGuildExchangeRet> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eGuildExchange_Failed", eGuildExchange_Failed));
		mapStr2Val.insert(make_pair("eGuildExchange_Sucess", eGuildExchange_Sucess));
		mapStr2Val.insert(make_pair("eGuildExchange_ErrorPack", eGuildExchange_ErrorPack));
		mapStr2Val.insert(make_pair("eGuildExchange_MoneyLimit", eGuildExchange_MoneyLimit));
		mapStr2Val.insert(make_pair("eGuildExchange_CondLimitA", eGuildExchange_CondLimitA));
		mapStr2Val.insert(make_pair("eGuildExchange_CondLimitB", eGuildExchange_CondLimitB));
		mapStr2Val.insert(make_pair("eGuildExchange_CondLimitC", eGuildExchange_CondLimitC));
		mapStr2Val.insert(make_pair("eGuildExchange_NoLingShan", eGuildExchange_NoLingShan));
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

SGuildInfoBase::SGuildInfoBase() : qwGuildID(0) { }

CInArchive& operator>>(CInArchive& src, SGuildInfoBase& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwGuildID;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SGuildInfoBase& s)
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
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, SGuildInfoBase_Wrapper& rWrapper)
{
	EType_SGuildInfoBase eType = eType_SGuildInfoBase;
	src >> (UINT8&)eType;
	switch(eType)
	{
	case eType_SGuildInfoBase:
		{
			rWrapper.ptr.reset(new SGuildInfoBase);
			src >> (SGuildInfoBase&)*rWrapper.ptr;
		}
		break;
	case eType_SGuildBaseInfo:
		{
			rWrapper.ptr.reset(new SGuildBaseInfo);
			src >> (SGuildBaseInfo&)*rWrapper.ptr;
		}
		break;
	case eType_SGuildUserInfo:
		{
			rWrapper.ptr.reset(new SGuildUserInfo);
			src >> (SGuildUserInfo&)*rWrapper.ptr;
		}
		break;
	case eType_SGuildApplyInfo:
		{
			rWrapper.ptr.reset(new SGuildApplyInfo);
			src >> (SGuildApplyInfo&)*rWrapper.ptr;
		}
		break;
	case eType_SGuildBuildingInfo:
		{
			rWrapper.ptr.reset(new SGuildBuildingInfo);
			src >> (SGuildBuildingInfo&)*rWrapper.ptr;
		}
		break;
	case eType_SGuildAuthorityInfo:
		{
			rWrapper.ptr.reset(new SGuildAuthorityInfo);
			src >> (SGuildAuthorityInfo&)*rWrapper.ptr;
		}
		break;
	case eType_SGuildTechInfo:
		{
			rWrapper.ptr.reset(new SGuildTechInfo);
			src >> (SGuildTechInfo&)*rWrapper.ptr;
		}
		break;
	case eType_SGuildLogInfo:
		{
			rWrapper.ptr.reset(new SGuildLogInfo);
			src >> (SGuildLogInfo&)*rWrapper.ptr;
		}
		break;
	case eType_SGuildStatueInfo:
		{
			rWrapper.ptr.reset(new SGuildStatueInfo);
			src >> (SGuildStatueInfo&)*rWrapper.ptr;
		}
		break;
	default:
		throw "Unknown value for EType_SGuildInfoBase";
		break;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SGuildInfoBase_Wrapper& rWrapper)
{
	if(rWrapper.ptr != NULL)
	{
		src << (UINT8)rWrapper.ptr->GetClassType();
		switch(rWrapper.ptr->GetClassType())
		{
		case eType_SGuildInfoBase:
			src << (SGuildInfoBase&)*rWrapper.ptr;
			break;
		case eType_SGuildBaseInfo:
			src << (SGuildBaseInfo&)*rWrapper.ptr;
			break;
		case eType_SGuildUserInfo:
			src << (SGuildUserInfo&)*rWrapper.ptr;
			break;
		case eType_SGuildApplyInfo:
			src << (SGuildApplyInfo&)*rWrapper.ptr;
			break;
		case eType_SGuildBuildingInfo:
			src << (SGuildBuildingInfo&)*rWrapper.ptr;
			break;
		case eType_SGuildAuthorityInfo:
			src << (SGuildAuthorityInfo&)*rWrapper.ptr;
			break;
		case eType_SGuildTechInfo:
			src << (SGuildTechInfo&)*rWrapper.ptr;
			break;
		case eType_SGuildLogInfo:
			src << (SGuildLogInfo&)*rWrapper.ptr;
			break;
		case eType_SGuildStatueInfo:
			src << (SGuildStatueInfo&)*rWrapper.ptr;
			break;
		default:
			throw "Unknown value for EType_SGuildInfoBase";
			break;
		}
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecSGuildInfoBase& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SGuildInfoBase_Wrapper wrapper;
		src >> wrapper;
		vec[i] = wrapper.ptr;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecSGuildInfoBase& vec)
{
	if(vec.size() > 0x7FFF)
		throw "Vector Size Too Large!";
	UINT16 wSize = (UINT16)vec.size();
	src.WriteContainerSize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SGuildInfoBase_Wrapper wrapper;
		wrapper.ptr = vec[i];
		src << wrapper;
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SGuildInfoBase& s)
{
	if(strcmp(rElement.Value(), "SGuildInfoBase") != 0)
	{
		LOG_CRI << "rElement is not SGuildInfoBase!";
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
	return true;
}

bool ToXML(const SGuildInfoBase& s, TiXmlElement& rElement)
{
	rElement.SetValue("SGuildInfoBase");
	rElement.SetAttribute("type", ToUTF8Ptr("帮派信息基本类"));
	unique_ptr<TiXmlElement> pElem_qwGuildID(new TiXmlElement("UINT64"));
	if(pElem_qwGuildID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwGuildID->SetAttribute("name", "qwGuildID");
	pElem_qwGuildID->SetAttribute("value", NumberToString(s.qwGuildID).c_str());
	pElem_qwGuildID->SetAttribute("comment", ToUTF8Ptr("帮派唯一ID"));
	if(rElement.LinkEndChild(pElem_qwGuildID.get()) != NULL)
		pElem_qwGuildID.release();
	return true;
}

bool SuperFromXML(TiXmlElement& rElement, SGuildInfoBasePtr& p)
{
	const char* pszName = rElement.Value();
	if(pszName == NULL)
	{
		LOG_CRI << "Element Name is empty!";
		return false;
	}
	if(strcmp(pszName, "SGuildInfoBase") == 0)
	{
		SGuildInfoBasePtr pStruct(new SGuildInfoBase);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SGuildInfoBase";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SGuildInfoBase FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SGuildBaseInfo") == 0)
	{
		SGuildBaseInfoPtr pStruct(new SGuildBaseInfo);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SGuildBaseInfo";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SGuildBaseInfo FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SGuildUserInfo") == 0)
	{
		SGuildUserInfoPtr pStruct(new SGuildUserInfo);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SGuildUserInfo";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SGuildUserInfo FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SGuildApplyInfo") == 0)
	{
		SGuildApplyInfoPtr pStruct(new SGuildApplyInfo);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SGuildApplyInfo";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SGuildApplyInfo FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SGuildBuildingInfo") == 0)
	{
		SGuildBuildingInfoPtr pStruct(new SGuildBuildingInfo);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SGuildBuildingInfo";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SGuildBuildingInfo FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SGuildAuthorityInfo") == 0)
	{
		SGuildAuthorityInfoPtr pStruct(new SGuildAuthorityInfo);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SGuildAuthorityInfo";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SGuildAuthorityInfo FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SGuildTechInfo") == 0)
	{
		SGuildTechInfoPtr pStruct(new SGuildTechInfo);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SGuildTechInfo";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SGuildTechInfo FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SGuildLogInfo") == 0)
	{
		SGuildLogInfoPtr pStruct(new SGuildLogInfo);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SGuildLogInfo";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SGuildLogInfo FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SGuildStatueInfo") == 0)
	{
		SGuildStatueInfoPtr pStruct(new SGuildStatueInfo);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SGuildStatueInfo";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SGuildStatueInfo FromXML fails!";
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

bool SuperToXML(const SGuildInfoBase& s, TiXmlElement& rElement)
{
	switch(s.GetClassType())
	{
	case eType_SGuildInfoBase:
		return ToXML((SGuildInfoBase&)s, rElement);
	case eType_SGuildBaseInfo:
		return ToXML((SGuildBaseInfo&)s, rElement);
	case eType_SGuildUserInfo:
		return ToXML((SGuildUserInfo&)s, rElement);
	case eType_SGuildApplyInfo:
		return ToXML((SGuildApplyInfo&)s, rElement);
	case eType_SGuildBuildingInfo:
		return ToXML((SGuildBuildingInfo&)s, rElement);
	case eType_SGuildAuthorityInfo:
		return ToXML((SGuildAuthorityInfo&)s, rElement);
	case eType_SGuildTechInfo:
		return ToXML((SGuildTechInfo&)s, rElement);
	case eType_SGuildLogInfo:
		return ToXML((SGuildLogInfo&)s, rElement);
	case eType_SGuildStatueInfo:
		return ToXML((SGuildStatueInfo&)s, rElement);
	default:
		LOG_CRI << "Invalid type: " << s.GetClassType();
		return false;
	}
}

bool VectorFromXML(TiXmlElement& rElement, TVecSGuildInfoBase& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SGuildInfoBasePtr p;
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

bool VectorToXML(const TVecSGuildInfoBase& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SGuildInfoBase"));
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

SGuildBaseInfo::SGuildBaseInfo() : qwOwnerID(0), qwQQGroupID(0), wUserCount(0), wMaxUserCount(0), dwMoney(0), 
			eSelfRank((EMemberRank)0), dwContribution(0), dwRemainDonate(0), wPlayerFighterID(0), byQuality(0), 
			dwScore(0), dwCount(0) { }

SGuildBaseInfo::SGuildBaseInfo(SGuildBaseInfo&& src) : SGuildInfoBase(src), strName(move(src.strName)), qwOwnerID(src.qwOwnerID), strOwnerName(move(src.strOwnerName)), strInfo(move(src.strInfo)), qwQQGroupID(src.qwQQGroupID), 
			wUserCount(src.wUserCount), wMaxUserCount(src.wMaxUserCount), dwMoney(src.dwMoney), eSelfRank(src.eSelfRank), dwContribution(src.dwContribution), 
			dwRemainDonate(src.dwRemainDonate), wPlayerFighterID(src.wPlayerFighterID), byQuality(src.byQuality), dwScore(src.dwScore), dwCount(src.dwCount), 
			strLingShan(move(src.strLingShan)) { }

SGuildBaseInfo& SGuildBaseInfo::operator=(SGuildBaseInfo&& rhs)
{
	if(this != &rhs)
	{
		this->~SGuildBaseInfo();
		new (this) SGuildBaseInfo(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SGuildBaseInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (SGuildInfoBase&)s;
	src >> s.strName;
	src >> s.qwOwnerID;
	src >> s.strOwnerName;
	src >> s.strInfo;
	src >> s.qwQQGroupID;
	src >> s.wUserCount;
	src >> s.wMaxUserCount;
	src >> s.dwMoney;
	src >> (UINT8&)s.eSelfRank;
	src >> s.dwContribution;
	src >> s.dwRemainDonate;
	src >> s.wPlayerFighterID;
	src >> s.byQuality;
	src >> s.dwScore;
	src >> s.dwCount;
	src >> s.strLingShan;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SGuildBaseInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const SGuildInfoBase&)s;
	src << s.strName;
	src << s.qwOwnerID;
	src << s.strOwnerName;
	src << s.strInfo;
	src << s.qwQQGroupID;
	src << s.wUserCount;
	src << s.wMaxUserCount;
	src << s.dwMoney;
	src << (UINT8&)s.eSelfRank;
	src << s.dwContribution;
	src << s.dwRemainDonate;
	src << s.wPlayerFighterID;
	src << s.byQuality;
	src << s.dwScore;
	src << s.dwCount;
	src << s.strLingShan;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecSGuildBaseInfo& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SGuildBaseInfoPtr p(new SGuildBaseInfo);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecSGuildBaseInfo& vec)
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

bool FromXML(TiXmlElement& rElement, SGuildBaseInfo& s)
{
	if(strcmp(rElement.Value(), "SGuildBaseInfo") != 0)
	{
		LOG_CRI << "rElement is not SGuildBaseInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for SGuildInfoBase is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (SGuildInfoBase&)s))
	{
		LOG_CRI << "FromXML for: SGuildInfoBase fails!";
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
		LOG_CRI << "pElemChild for strOwnerName is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strOwnerName") != 0)
	{
		LOG_CRI << "Attribute: name is not strOwnerName!";
		return false;
	}
	const char* pszVal_strOwnerName = pElemChild->Attribute("value");
	if(pszVal_strOwnerName == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strOwnerName = pszVal_strOwnerName;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not strInfo!";
		return false;
	}
	const char* pszVal_strInfo = pElemChild->Attribute("value");
	if(pszVal_strInfo == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strInfo = pszVal_strInfo;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwQQGroupID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwQQGroupID") != 0)
	{
		LOG_CRI << "Attribute: name is not qwQQGroupID!";
		return false;
	}
	const char* pszVal_qwQQGroupID = pElemChild->Attribute("value");
	if(pszVal_qwQQGroupID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwQQGroupID, s.qwQQGroupID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wUserCount is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wUserCount") != 0)
	{
		LOG_CRI << "Attribute: name is not wUserCount!";
		return false;
	}
	const char* pszVal_wUserCount = pElemChild->Attribute("value");
	if(pszVal_wUserCount == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wUserCount, s.wUserCount))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wMaxUserCount is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wMaxUserCount") != 0)
	{
		LOG_CRI << "Attribute: name is not wMaxUserCount!";
		return false;
	}
	const char* pszVal_wMaxUserCount = pElemChild->Attribute("value");
	if(pszVal_wMaxUserCount == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wMaxUserCount, s.wMaxUserCount))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwMoney is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwMoney") != 0)
	{
		LOG_CRI << "Attribute: name is not dwMoney!";
		return false;
	}
	const char* pszVal_dwMoney = pElemChild->Attribute("value");
	if(pszVal_dwMoney == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwMoney, s.dwMoney))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eSelfRank is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "EMemberRank") != 0)
	{
		LOG_CRI << "pElemChild is not EMemberRank!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eSelfRank") != 0)
	{
		LOG_CRI << "Attribute: name is not eSelfRank!";
		return false;
	}
	const char* pszVal_eSelfRank = pElemChild->Attribute("value");
	if(pszVal_eSelfRank == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!EnumStrToVal(pszVal_eSelfRank, s.eSelfRank))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwContribution is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwContribution") != 0)
	{
		LOG_CRI << "Attribute: name is not dwContribution!";
		return false;
	}
	const char* pszVal_dwContribution = pElemChild->Attribute("value");
	if(pszVal_dwContribution == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwContribution, s.dwContribution))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwRemainDonate is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwRemainDonate") != 0)
	{
		LOG_CRI << "Attribute: name is not dwRemainDonate!";
		return false;
	}
	const char* pszVal_dwRemainDonate = pElemChild->Attribute("value");
	if(pszVal_dwRemainDonate == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwRemainDonate, s.dwRemainDonate))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wPlayerFighterID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wPlayerFighterID") != 0)
	{
		LOG_CRI << "Attribute: name is not wPlayerFighterID!";
		return false;
	}
	const char* pszVal_wPlayerFighterID = pElemChild->Attribute("value");
	if(pszVal_wPlayerFighterID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wPlayerFighterID, s.wPlayerFighterID))
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
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwCount is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwCount") != 0)
	{
		LOG_CRI << "Attribute: name is not dwCount!";
		return false;
	}
	const char* pszVal_dwCount = pElemChild->Attribute("value");
	if(pszVal_dwCount == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwCount, s.dwCount))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strLingShan is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strLingShan") != 0)
	{
		LOG_CRI << "Attribute: name is not strLingShan!";
		return false;
	}
	const char* pszVal_strLingShan = pElemChild->Attribute("value");
	if(pszVal_strLingShan == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strLingShan = pszVal_strLingShan;
	return true;
}

bool ToXML(const SGuildBaseInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SGuildBaseInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("帮派基本信息"));
	unique_ptr<TiXmlElement> pElem_SGuildInfoBase(new TiXmlElement("SGuildInfoBase"));
	if(pElem_SGuildInfoBase == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const SGuildInfoBase&)s, *pElem_SGuildInfoBase))
	{
		LOG_CRI << "SGuildInfoBase ToXML fails!";
		return false;
	}
	pElem_SGuildInfoBase->SetAttribute("type", ToUTF8Ptr("帮派信息基本类"));
	pElem_SGuildInfoBase->SetAttribute("comment", ToUTF8Ptr("父类SGuildInfoBase部分"));
	if(rElement.LinkEndChild(pElem_SGuildInfoBase.get()) != NULL)
		pElem_SGuildInfoBase.release();
	unique_ptr<TiXmlElement> pElem_strName(new TiXmlElement("string"));
	if(pElem_strName == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strName->SetAttribute("name", "strName");
	pElem_strName->SetAttribute("value", s.strName.c_str());
	pElem_strName->SetAttribute("comment", ToUTF8Ptr("帮派名称"));
	if(rElement.LinkEndChild(pElem_strName.get()) != NULL)
		pElem_strName.release();
	unique_ptr<TiXmlElement> pElem_qwOwnerID(new TiXmlElement("UINT64"));
	if(pElem_qwOwnerID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwOwnerID->SetAttribute("name", "qwOwnerID");
	pElem_qwOwnerID->SetAttribute("value", NumberToString(s.qwOwnerID).c_str());
	pElem_qwOwnerID->SetAttribute("comment", ToUTF8Ptr("帮主角色ID"));
	if(rElement.LinkEndChild(pElem_qwOwnerID.get()) != NULL)
		pElem_qwOwnerID.release();
	unique_ptr<TiXmlElement> pElem_strOwnerName(new TiXmlElement("string"));
	if(pElem_strOwnerName == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strOwnerName->SetAttribute("name", "strOwnerName");
	pElem_strOwnerName->SetAttribute("value", s.strOwnerName.c_str());
	pElem_strOwnerName->SetAttribute("comment", ToUTF8Ptr("帮主名称"));
	if(rElement.LinkEndChild(pElem_strOwnerName.get()) != NULL)
		pElem_strOwnerName.release();
	unique_ptr<TiXmlElement> pElem_strInfo(new TiXmlElement("string"));
	if(pElem_strInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strInfo->SetAttribute("name", "strInfo");
	pElem_strInfo->SetAttribute("value", s.strInfo.c_str());
	pElem_strInfo->SetAttribute("comment", ToUTF8Ptr("帮派公告"));
	if(rElement.LinkEndChild(pElem_strInfo.get()) != NULL)
		pElem_strInfo.release();
	unique_ptr<TiXmlElement> pElem_qwQQGroupID(new TiXmlElement("UINT64"));
	if(pElem_qwQQGroupID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwQQGroupID->SetAttribute("name", "qwQQGroupID");
	pElem_qwQQGroupID->SetAttribute("value", NumberToString(s.qwQQGroupID).c_str());
	pElem_qwQQGroupID->SetAttribute("comment", ToUTF8Ptr("帮派Q群群号"));
	if(rElement.LinkEndChild(pElem_qwQQGroupID.get()) != NULL)
		pElem_qwQQGroupID.release();
	unique_ptr<TiXmlElement> pElem_wUserCount(new TiXmlElement("UINT16"));
	if(pElem_wUserCount == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wUserCount->SetAttribute("name", "wUserCount");
	pElem_wUserCount->SetAttribute("value", NumberToString(s.wUserCount).c_str());
	pElem_wUserCount->SetAttribute("comment", ToUTF8Ptr("成员数量"));
	if(rElement.LinkEndChild(pElem_wUserCount.get()) != NULL)
		pElem_wUserCount.release();
	unique_ptr<TiXmlElement> pElem_wMaxUserCount(new TiXmlElement("UINT16"));
	if(pElem_wMaxUserCount == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wMaxUserCount->SetAttribute("name", "wMaxUserCount");
	pElem_wMaxUserCount->SetAttribute("value", NumberToString(s.wMaxUserCount).c_str());
	pElem_wMaxUserCount->SetAttribute("comment", ToUTF8Ptr("最大成员数量"));
	if(rElement.LinkEndChild(pElem_wMaxUserCount.get()) != NULL)
		pElem_wMaxUserCount.release();
	unique_ptr<TiXmlElement> pElem_dwMoney(new TiXmlElement("UINT32"));
	if(pElem_dwMoney == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwMoney->SetAttribute("name", "dwMoney");
	pElem_dwMoney->SetAttribute("value", NumberToString(s.dwMoney).c_str());
	pElem_dwMoney->SetAttribute("comment", ToUTF8Ptr("帮派资金"));
	if(rElement.LinkEndChild(pElem_dwMoney.get()) != NULL)
		pElem_dwMoney.release();
	unique_ptr<TiXmlElement> pElem_eSelfRank(new TiXmlElement("EMemberRank"));
	if(pElem_eSelfRank == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eSelfRank->SetAttribute("name", "eSelfRank");
	const char* pszEnum_eSelfRank = EnumValToStr(s.eSelfRank);
	if(pszEnum_eSelfRank == NULL)
	{
		LOG_CRI << "EnumValToStr for EMemberRank fails!";
		return false;
	}
	pElem_eSelfRank->SetAttribute("value", pszEnum_eSelfRank);
	pElem_eSelfRank->SetAttribute("comment", ToUTF8Ptr("本人职位"));
	if(rElement.LinkEndChild(pElem_eSelfRank.get()) != NULL)
		pElem_eSelfRank.release();
	unique_ptr<TiXmlElement> pElem_dwContribution(new TiXmlElement("UINT32"));
	if(pElem_dwContribution == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwContribution->SetAttribute("name", "dwContribution");
	pElem_dwContribution->SetAttribute("value", NumberToString(s.dwContribution).c_str());
	pElem_dwContribution->SetAttribute("comment", ToUTF8Ptr("本人贡献值"));
	if(rElement.LinkEndChild(pElem_dwContribution.get()) != NULL)
		pElem_dwContribution.release();
	unique_ptr<TiXmlElement> pElem_dwRemainDonate(new TiXmlElement("UINT32"));
	if(pElem_dwRemainDonate == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwRemainDonate->SetAttribute("name", "dwRemainDonate");
	pElem_dwRemainDonate->SetAttribute("value", NumberToString(s.dwRemainDonate).c_str());
	pElem_dwRemainDonate->SetAttribute("comment", ToUTF8Ptr("剩余捐献额"));
	if(rElement.LinkEndChild(pElem_dwRemainDonate.get()) != NULL)
		pElem_dwRemainDonate.release();
	unique_ptr<TiXmlElement> pElem_wPlayerFighterID(new TiXmlElement("UINT16"));
	if(pElem_wPlayerFighterID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wPlayerFighterID->SetAttribute("name", "wPlayerFighterID");
	pElem_wPlayerFighterID->SetAttribute("value", NumberToString(s.wPlayerFighterID).c_str());
	pElem_wPlayerFighterID->SetAttribute("comment", ToUTF8Ptr("帮主ID"));
	if(rElement.LinkEndChild(pElem_wPlayerFighterID.get()) != NULL)
		pElem_wPlayerFighterID.release();
	unique_ptr<TiXmlElement> pElem_byQuality(new TiXmlElement("UINT8"));
	if(pElem_byQuality == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byQuality->SetAttribute("name", "byQuality");
	pElem_byQuality->SetAttribute("value", NumberToString(s.byQuality).c_str());
	pElem_byQuality->SetAttribute("comment", ToUTF8Ptr("帮主品质"));
	if(rElement.LinkEndChild(pElem_byQuality.get()) != NULL)
		pElem_byQuality.release();
	unique_ptr<TiXmlElement> pElem_dwScore(new TiXmlElement("UINT32"));
	if(pElem_dwScore == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwScore->SetAttribute("name", "dwScore");
	pElem_dwScore->SetAttribute("value", NumberToString(s.dwScore).c_str());
	pElem_dwScore->SetAttribute("comment", ToUTF8Ptr("天元神兽积分"));
	if(rElement.LinkEndChild(pElem_dwScore.get()) != NULL)
		pElem_dwScore.release();
	unique_ptr<TiXmlElement> pElem_dwCount(new TiXmlElement("UINT32"));
	if(pElem_dwCount == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwCount->SetAttribute("name", "dwCount");
	pElem_dwCount->SetAttribute("value", NumberToString(s.dwCount).c_str());
	pElem_dwCount->SetAttribute("comment", ToUTF8Ptr("帮派所有成员兑换物品数量"));
	if(rElement.LinkEndChild(pElem_dwCount.get()) != NULL)
		pElem_dwCount.release();
	unique_ptr<TiXmlElement> pElem_strLingShan(new TiXmlElement("string"));
	if(pElem_strLingShan == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strLingShan->SetAttribute("name", "strLingShan");
	pElem_strLingShan->SetAttribute("value", s.strLingShan.c_str());
	pElem_strLingShan->SetAttribute("comment", ToUTF8Ptr("占领灵山"));
	if(rElement.LinkEndChild(pElem_strLingShan.get()) != NULL)
		pElem_strLingShan.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecSGuildBaseInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SGuildBaseInfoPtr p(new SGuildBaseInfo);
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

bool VectorToXML(const TVecSGuildBaseInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SGuildBaseInfo"));
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

SGuildUserInfo::SGuildUserInfo() : qwRoleID(0), wLevel(0), dwContribution(0), dwLastOnlineTime(0), dwJoinTime(0), 
			eMemberRank((EMemberRank)0), eMemberLastRank((EMemberRank)0), dwAuthority(0), byVIPLevel(0) { }

SGuildUserInfo::SGuildUserInfo(SGuildUserInfo&& src) : SGuildInfoBase(src), qwRoleID(src.qwRoleID), strName(move(src.strName)), wLevel(src.wLevel), dwContribution(src.dwContribution), dwLastOnlineTime(src.dwLastOnlineTime), 
			dwJoinTime(src.dwJoinTime), eMemberRank(src.eMemberRank), eMemberLastRank(src.eMemberLastRank), dwAuthority(src.dwAuthority), byVIPLevel(src.byVIPLevel), 
			vecPlatforms(move(src.vecPlatforms)) { }

SGuildUserInfo& SGuildUserInfo::operator=(SGuildUserInfo&& rhs)
{
	if(this != &rhs)
	{
		this->~SGuildUserInfo();
		new (this) SGuildUserInfo(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SGuildUserInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (SGuildInfoBase&)s;
	src >> s.qwRoleID;
	src >> s.strName;
	src >> s.wLevel;
	src >> s.dwContribution;
	src >> s.dwLastOnlineTime;
	src >> s.dwJoinTime;
	src >> (UINT8&)s.eMemberRank;
	src >> (UINT8&)s.eMemberLastRank;
	src >> s.dwAuthority;
	src >> s.byVIPLevel;
	src >> s.vecPlatforms;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SGuildUserInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const SGuildInfoBase&)s;
	src << s.qwRoleID;
	src << s.strName;
	src << s.wLevel;
	src << s.dwContribution;
	src << s.dwLastOnlineTime;
	src << s.dwJoinTime;
	src << (UINT8&)s.eMemberRank;
	src << (UINT8&)s.eMemberLastRank;
	src << s.dwAuthority;
	src << s.byVIPLevel;
	src << s.vecPlatforms;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecGuildUserInfo& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SGuildUserInfoPtr p(new SGuildUserInfo);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecGuildUserInfo& vec)
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

bool FromXML(TiXmlElement& rElement, SGuildUserInfo& s)
{
	if(strcmp(rElement.Value(), "SGuildUserInfo") != 0)
	{
		LOG_CRI << "rElement is not SGuildUserInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for SGuildInfoBase is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (SGuildInfoBase&)s))
	{
		LOG_CRI << "FromXML for: SGuildInfoBase fails!";
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
		LOG_CRI << "pElemChild for dwContribution is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwContribution") != 0)
	{
		LOG_CRI << "Attribute: name is not dwContribution!";
		return false;
	}
	const char* pszVal_dwContribution = pElemChild->Attribute("value");
	if(pszVal_dwContribution == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwContribution, s.dwContribution))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwLastOnlineTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwLastOnlineTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwLastOnlineTime!";
		return false;
	}
	const char* pszVal_dwLastOnlineTime = pElemChild->Attribute("value");
	if(pszVal_dwLastOnlineTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwLastOnlineTime, s.dwLastOnlineTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwJoinTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwJoinTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwJoinTime!";
		return false;
	}
	const char* pszVal_dwJoinTime = pElemChild->Attribute("value");
	if(pszVal_dwJoinTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwJoinTime, s.dwJoinTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eMemberRank is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "EMemberRank") != 0)
	{
		LOG_CRI << "pElemChild is not EMemberRank!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eMemberRank") != 0)
	{
		LOG_CRI << "Attribute: name is not eMemberRank!";
		return false;
	}
	const char* pszVal_eMemberRank = pElemChild->Attribute("value");
	if(pszVal_eMemberRank == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!EnumStrToVal(pszVal_eMemberRank, s.eMemberRank))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eMemberLastRank is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "EMemberRank") != 0)
	{
		LOG_CRI << "pElemChild is not EMemberRank!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eMemberLastRank") != 0)
	{
		LOG_CRI << "Attribute: name is not eMemberLastRank!";
		return false;
	}
	const char* pszVal_eMemberLastRank = pElemChild->Attribute("value");
	if(pszVal_eMemberLastRank == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!EnumStrToVal(pszVal_eMemberLastRank, s.eMemberLastRank))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwAuthority is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwAuthority") != 0)
	{
		LOG_CRI << "Attribute: name is not dwAuthority!";
		return false;
	}
	const char* pszVal_dwAuthority = pElemChild->Attribute("value");
	if(pszVal_dwAuthority == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwAuthority, s.dwAuthority))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byVIPLevel is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byVIPLevel") != 0)
	{
		LOG_CRI << "Attribute: name is not byVIPLevel!";
		return false;
	}
	const char* pszVal_byVIPLevel = pElemChild->Attribute("value");
	if(pszVal_byVIPLevel == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byVIPLevel, s.byVIPLevel))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecPlatforms is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "ProtoCommon::TVecPlatformParam") != 0)
	{
		LOG_CRI << "pElemChild is not ProtoCommon::TVecPlatformParam!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecPlatforms") != 0)
	{
		LOG_CRI << "Attribute: name is not vecPlatforms!";
		return false;
	}
	if(!NProtoCommon::VectorFromXML(*pElemChild, s.vecPlatforms))
	{
		LOG_CRI << "VectorFromXML for vecPlatforms fails!";
		return false;
	}
	return true;
}

bool ToXML(const SGuildUserInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SGuildUserInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("帮派成员信息"));
	unique_ptr<TiXmlElement> pElem_SGuildInfoBase(new TiXmlElement("SGuildInfoBase"));
	if(pElem_SGuildInfoBase == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const SGuildInfoBase&)s, *pElem_SGuildInfoBase))
	{
		LOG_CRI << "SGuildInfoBase ToXML fails!";
		return false;
	}
	pElem_SGuildInfoBase->SetAttribute("type", ToUTF8Ptr("帮派信息基本类"));
	pElem_SGuildInfoBase->SetAttribute("comment", ToUTF8Ptr("父类SGuildInfoBase部分"));
	if(rElement.LinkEndChild(pElem_SGuildInfoBase.get()) != NULL)
		pElem_SGuildInfoBase.release();
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
	unique_ptr<TiXmlElement> pElem_wLevel(new TiXmlElement("UINT16"));
	if(pElem_wLevel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wLevel->SetAttribute("name", "wLevel");
	pElem_wLevel->SetAttribute("value", NumberToString(s.wLevel).c_str());
	pElem_wLevel->SetAttribute("comment", ToUTF8Ptr("玩家等级"));
	if(rElement.LinkEndChild(pElem_wLevel.get()) != NULL)
		pElem_wLevel.release();
	unique_ptr<TiXmlElement> pElem_dwContribution(new TiXmlElement("UINT32"));
	if(pElem_dwContribution == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwContribution->SetAttribute("name", "dwContribution");
	pElem_dwContribution->SetAttribute("value", NumberToString(s.dwContribution).c_str());
	pElem_dwContribution->SetAttribute("comment", ToUTF8Ptr("贡献值"));
	if(rElement.LinkEndChild(pElem_dwContribution.get()) != NULL)
		pElem_dwContribution.release();
	unique_ptr<TiXmlElement> pElem_dwLastOnlineTime(new TiXmlElement("UINT32"));
	if(pElem_dwLastOnlineTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwLastOnlineTime->SetAttribute("name", "dwLastOnlineTime");
	pElem_dwLastOnlineTime->SetAttribute("value", NumberToString(s.dwLastOnlineTime).c_str());
	pElem_dwLastOnlineTime->SetAttribute("comment", ToUTF8Ptr("最后在线时间"));
	if(rElement.LinkEndChild(pElem_dwLastOnlineTime.get()) != NULL)
		pElem_dwLastOnlineTime.release();
	unique_ptr<TiXmlElement> pElem_dwJoinTime(new TiXmlElement("UINT32"));
	if(pElem_dwJoinTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwJoinTime->SetAttribute("name", "dwJoinTime");
	pElem_dwJoinTime->SetAttribute("value", NumberToString(s.dwJoinTime).c_str());
	pElem_dwJoinTime->SetAttribute("comment", ToUTF8Ptr("入帮时间"));
	if(rElement.LinkEndChild(pElem_dwJoinTime.get()) != NULL)
		pElem_dwJoinTime.release();
	unique_ptr<TiXmlElement> pElem_eMemberRank(new TiXmlElement("EMemberRank"));
	if(pElem_eMemberRank == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eMemberRank->SetAttribute("name", "eMemberRank");
	const char* pszEnum_eMemberRank = EnumValToStr(s.eMemberRank);
	if(pszEnum_eMemberRank == NULL)
	{
		LOG_CRI << "EnumValToStr for EMemberRank fails!";
		return false;
	}
	pElem_eMemberRank->SetAttribute("value", pszEnum_eMemberRank);
	pElem_eMemberRank->SetAttribute("comment", ToUTF8Ptr("帮派职位"));
	if(rElement.LinkEndChild(pElem_eMemberRank.get()) != NULL)
		pElem_eMemberRank.release();
	unique_ptr<TiXmlElement> pElem_eMemberLastRank(new TiXmlElement("EMemberRank"));
	if(pElem_eMemberLastRank == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eMemberLastRank->SetAttribute("name", "eMemberLastRank");
	const char* pszEnum_eMemberLastRank = EnumValToStr(s.eMemberLastRank);
	if(pszEnum_eMemberLastRank == NULL)
	{
		LOG_CRI << "EnumValToStr for EMemberRank fails!";
		return false;
	}
	pElem_eMemberLastRank->SetAttribute("value", pszEnum_eMemberLastRank);
	pElem_eMemberLastRank->SetAttribute("comment", ToUTF8Ptr("帮派上一次职位"));
	if(rElement.LinkEndChild(pElem_eMemberLastRank.get()) != NULL)
		pElem_eMemberLastRank.release();
	unique_ptr<TiXmlElement> pElem_dwAuthority(new TiXmlElement("UINT32"));
	if(pElem_dwAuthority == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwAuthority->SetAttribute("name", "dwAuthority");
	pElem_dwAuthority->SetAttribute("value", NumberToString(s.dwAuthority).c_str());
	pElem_dwAuthority->SetAttribute("comment", ToUTF8Ptr("帮派权限"));
	if(rElement.LinkEndChild(pElem_dwAuthority.get()) != NULL)
		pElem_dwAuthority.release();
	unique_ptr<TiXmlElement> pElem_byVIPLevel(new TiXmlElement("UINT8"));
	if(pElem_byVIPLevel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byVIPLevel->SetAttribute("name", "byVIPLevel");
	pElem_byVIPLevel->SetAttribute("value", NumberToString(s.byVIPLevel).c_str());
	pElem_byVIPLevel->SetAttribute("comment", ToUTF8Ptr("御剑等级"));
	if(rElement.LinkEndChild(pElem_byVIPLevel.get()) != NULL)
		pElem_byVIPLevel.release();
	unique_ptr<TiXmlElement> pElem_vecPlatforms(new TiXmlElement("ProtoCommon::TVecPlatformParam"));
	if(pElem_vecPlatforms == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecPlatforms->SetAttribute("name", "vecPlatforms");
	if(!NProtoCommon::VectorToXML(s.vecPlatforms, *pElem_vecPlatforms))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecPlatforms->SetAttribute("comment", ToUTF8Ptr("平台信息"));
	if(rElement.LinkEndChild(pElem_vecPlatforms.get()) != NULL)
		pElem_vecPlatforms.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecGuildUserInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SGuildUserInfoPtr p(new SGuildUserInfo);
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

bool VectorToXML(const TVecGuildUserInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SGuildUserInfo"));
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

SGuildApplyInfo::SGuildApplyInfo() : qwRoleID(0), wLevel(0), dwBattlePoint(0) { }

SGuildApplyInfo::SGuildApplyInfo(SGuildApplyInfo&& src) : SGuildInfoBase(src), qwRoleID(src.qwRoleID), strName(move(src.strName)), wLevel(src.wLevel), dwBattlePoint(src.dwBattlePoint) { }

SGuildApplyInfo& SGuildApplyInfo::operator=(SGuildApplyInfo&& rhs)
{
	if(this != &rhs)
	{
		this->~SGuildApplyInfo();
		new (this) SGuildApplyInfo(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SGuildApplyInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (SGuildInfoBase&)s;
	src >> s.qwRoleID;
	src >> s.strName;
	src >> s.wLevel;
	src >> s.dwBattlePoint;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SGuildApplyInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const SGuildInfoBase&)s;
	src << s.qwRoleID;
	src << s.strName;
	src << s.wLevel;
	src << s.dwBattlePoint;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecGuildApplyInfo& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SGuildApplyInfoPtr p(new SGuildApplyInfo);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecGuildApplyInfo& vec)
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

bool FromXML(TiXmlElement& rElement, SGuildApplyInfo& s)
{
	if(strcmp(rElement.Value(), "SGuildApplyInfo") != 0)
	{
		LOG_CRI << "rElement is not SGuildApplyInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for SGuildInfoBase is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (SGuildInfoBase&)s))
	{
		LOG_CRI << "FromXML for: SGuildInfoBase fails!";
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

bool ToXML(const SGuildApplyInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SGuildApplyInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("帮派申请列表信息"));
	unique_ptr<TiXmlElement> pElem_SGuildInfoBase(new TiXmlElement("SGuildInfoBase"));
	if(pElem_SGuildInfoBase == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const SGuildInfoBase&)s, *pElem_SGuildInfoBase))
	{
		LOG_CRI << "SGuildInfoBase ToXML fails!";
		return false;
	}
	pElem_SGuildInfoBase->SetAttribute("type", ToUTF8Ptr("帮派信息基本类"));
	pElem_SGuildInfoBase->SetAttribute("comment", ToUTF8Ptr("父类SGuildInfoBase部分"));
	if(rElement.LinkEndChild(pElem_SGuildInfoBase.get()) != NULL)
		pElem_SGuildInfoBase.release();
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
	unique_ptr<TiXmlElement> pElem_wLevel(new TiXmlElement("UINT16"));
	if(pElem_wLevel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wLevel->SetAttribute("name", "wLevel");
	pElem_wLevel->SetAttribute("value", NumberToString(s.wLevel).c_str());
	pElem_wLevel->SetAttribute("comment", ToUTF8Ptr("玩家等级"));
	if(rElement.LinkEndChild(pElem_wLevel.get()) != NULL)
		pElem_wLevel.release();
	unique_ptr<TiXmlElement> pElem_dwBattlePoint(new TiXmlElement("UINT32"));
	if(pElem_dwBattlePoint == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwBattlePoint->SetAttribute("name", "dwBattlePoint");
	pElem_dwBattlePoint->SetAttribute("value", NumberToString(s.dwBattlePoint).c_str());
	pElem_dwBattlePoint->SetAttribute("comment", ToUTF8Ptr("玩家战斗力"));
	if(rElement.LinkEndChild(pElem_dwBattlePoint.get()) != NULL)
		pElem_dwBattlePoint.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecGuildApplyInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SGuildApplyInfoPtr p(new SGuildApplyInfo);
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

bool VectorToXML(const TVecGuildApplyInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SGuildApplyInfo"));
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

SGuildBuildingInfo::SGuildBuildingInfo() : eBuildingType((EBuildingType)0), wLevel(0) { }

CInArchive& operator>>(CInArchive& src, SGuildBuildingInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (SGuildInfoBase&)s;
	src >> (UINT8&)s.eBuildingType;
	src >> s.wLevel;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SGuildBuildingInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const SGuildInfoBase&)s;
	src << (UINT8&)s.eBuildingType;
	src << s.wLevel;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecGuildBuildingInfo& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SGuildBuildingInfoPtr p(new SGuildBuildingInfo);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecGuildBuildingInfo& vec)
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

bool FromXML(TiXmlElement& rElement, SGuildBuildingInfo& s)
{
	if(strcmp(rElement.Value(), "SGuildBuildingInfo") != 0)
	{
		LOG_CRI << "rElement is not SGuildBuildingInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for SGuildInfoBase is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (SGuildInfoBase&)s))
	{
		LOG_CRI << "FromXML for: SGuildInfoBase fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eBuildingType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "EBuildingType") != 0)
	{
		LOG_CRI << "pElemChild is not EBuildingType!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eBuildingType") != 0)
	{
		LOG_CRI << "Attribute: name is not eBuildingType!";
		return false;
	}
	const char* pszVal_eBuildingType = pElemChild->Attribute("value");
	if(pszVal_eBuildingType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!EnumStrToVal(pszVal_eBuildingType, s.eBuildingType))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
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
	return true;
}

bool ToXML(const SGuildBuildingInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SGuildBuildingInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("帮派建筑信息"));
	unique_ptr<TiXmlElement> pElem_SGuildInfoBase(new TiXmlElement("SGuildInfoBase"));
	if(pElem_SGuildInfoBase == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const SGuildInfoBase&)s, *pElem_SGuildInfoBase))
	{
		LOG_CRI << "SGuildInfoBase ToXML fails!";
		return false;
	}
	pElem_SGuildInfoBase->SetAttribute("type", ToUTF8Ptr("帮派信息基本类"));
	pElem_SGuildInfoBase->SetAttribute("comment", ToUTF8Ptr("父类SGuildInfoBase部分"));
	if(rElement.LinkEndChild(pElem_SGuildInfoBase.get()) != NULL)
		pElem_SGuildInfoBase.release();
	unique_ptr<TiXmlElement> pElem_eBuildingType(new TiXmlElement("EBuildingType"));
	if(pElem_eBuildingType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eBuildingType->SetAttribute("name", "eBuildingType");
	const char* pszEnum_eBuildingType = EnumValToStr(s.eBuildingType);
	if(pszEnum_eBuildingType == NULL)
	{
		LOG_CRI << "EnumValToStr for EBuildingType fails!";
		return false;
	}
	pElem_eBuildingType->SetAttribute("value", pszEnum_eBuildingType);
	pElem_eBuildingType->SetAttribute("comment", ToUTF8Ptr("帮派建筑类型"));
	if(rElement.LinkEndChild(pElem_eBuildingType.get()) != NULL)
		pElem_eBuildingType.release();
	unique_ptr<TiXmlElement> pElem_wLevel(new TiXmlElement("UINT16"));
	if(pElem_wLevel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wLevel->SetAttribute("name", "wLevel");
	pElem_wLevel->SetAttribute("value", NumberToString(s.wLevel).c_str());
	pElem_wLevel->SetAttribute("comment", ToUTF8Ptr("帮派建筑等级"));
	if(rElement.LinkEndChild(pElem_wLevel.get()) != NULL)
		pElem_wLevel.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecGuildBuildingInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SGuildBuildingInfoPtr p(new SGuildBuildingInfo);
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

bool VectorToXML(const TVecGuildBuildingInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SGuildBuildingInfo"));
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

SGuildAuthorityInfo::SGuildAuthorityInfo() : eMemberRank((EMemberRank)0), dwAuthority(0) { }

CInArchive& operator>>(CInArchive& src, SGuildAuthorityInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (SGuildInfoBase&)s;
	src >> (UINT8&)s.eMemberRank;
	src >> s.dwAuthority;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SGuildAuthorityInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const SGuildInfoBase&)s;
	src << (UINT8&)s.eMemberRank;
	src << s.dwAuthority;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecGuildAuthorityInfo& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SGuildAuthorityInfoPtr p(new SGuildAuthorityInfo);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecGuildAuthorityInfo& vec)
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

bool FromXML(TiXmlElement& rElement, SGuildAuthorityInfo& s)
{
	if(strcmp(rElement.Value(), "SGuildAuthorityInfo") != 0)
	{
		LOG_CRI << "rElement is not SGuildAuthorityInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for SGuildInfoBase is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (SGuildInfoBase&)s))
	{
		LOG_CRI << "FromXML for: SGuildInfoBase fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eMemberRank is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "EMemberRank") != 0)
	{
		LOG_CRI << "pElemChild is not EMemberRank!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eMemberRank") != 0)
	{
		LOG_CRI << "Attribute: name is not eMemberRank!";
		return false;
	}
	const char* pszVal_eMemberRank = pElemChild->Attribute("value");
	if(pszVal_eMemberRank == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!EnumStrToVal(pszVal_eMemberRank, s.eMemberRank))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwAuthority is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwAuthority") != 0)
	{
		LOG_CRI << "Attribute: name is not dwAuthority!";
		return false;
	}
	const char* pszVal_dwAuthority = pElemChild->Attribute("value");
	if(pszVal_dwAuthority == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwAuthority, s.dwAuthority))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SGuildAuthorityInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SGuildAuthorityInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("帮派可选权限信息"));
	unique_ptr<TiXmlElement> pElem_SGuildInfoBase(new TiXmlElement("SGuildInfoBase"));
	if(pElem_SGuildInfoBase == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const SGuildInfoBase&)s, *pElem_SGuildInfoBase))
	{
		LOG_CRI << "SGuildInfoBase ToXML fails!";
		return false;
	}
	pElem_SGuildInfoBase->SetAttribute("type", ToUTF8Ptr("帮派信息基本类"));
	pElem_SGuildInfoBase->SetAttribute("comment", ToUTF8Ptr("父类SGuildInfoBase部分"));
	if(rElement.LinkEndChild(pElem_SGuildInfoBase.get()) != NULL)
		pElem_SGuildInfoBase.release();
	unique_ptr<TiXmlElement> pElem_eMemberRank(new TiXmlElement("EMemberRank"));
	if(pElem_eMemberRank == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eMemberRank->SetAttribute("name", "eMemberRank");
	const char* pszEnum_eMemberRank = EnumValToStr(s.eMemberRank);
	if(pszEnum_eMemberRank == NULL)
	{
		LOG_CRI << "EnumValToStr for EMemberRank fails!";
		return false;
	}
	pElem_eMemberRank->SetAttribute("value", pszEnum_eMemberRank);
	pElem_eMemberRank->SetAttribute("comment", ToUTF8Ptr("帮派职位"));
	if(rElement.LinkEndChild(pElem_eMemberRank.get()) != NULL)
		pElem_eMemberRank.release();
	unique_ptr<TiXmlElement> pElem_dwAuthority(new TiXmlElement("UINT32"));
	if(pElem_dwAuthority == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwAuthority->SetAttribute("name", "dwAuthority");
	pElem_dwAuthority->SetAttribute("value", NumberToString(s.dwAuthority).c_str());
	pElem_dwAuthority->SetAttribute("comment", ToUTF8Ptr("可选权限 0x01:指挥帮战 0x02:升级建筑 0x04:开启血池 0x08:指挥末日之战 0x10:创建遗迹攻击小队"));
	if(rElement.LinkEndChild(pElem_dwAuthority.get()) != NULL)
		pElem_dwAuthority.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecGuildAuthorityInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SGuildAuthorityInfoPtr p(new SGuildAuthorityInfo);
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

bool VectorToXML(const TVecGuildAuthorityInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SGuildAuthorityInfo"));
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

SGuildTechInfo::SGuildTechInfo() : eType((ETechType)0), wLevel(0) { }

CInArchive& operator>>(CInArchive& src, SGuildTechInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (SGuildInfoBase&)s;
	src >> (UINT8&)s.eType;
	src >> s.wLevel;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SGuildTechInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const SGuildInfoBase&)s;
	src << (UINT8&)s.eType;
	src << s.wLevel;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecGuildTechInfo& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SGuildTechInfoPtr p(new SGuildTechInfo);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecGuildTechInfo& vec)
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

bool FromXML(TiXmlElement& rElement, SGuildTechInfo& s)
{
	if(strcmp(rElement.Value(), "SGuildTechInfo") != 0)
	{
		LOG_CRI << "rElement is not SGuildTechInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for SGuildInfoBase is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (SGuildInfoBase&)s))
	{
		LOG_CRI << "FromXML for: SGuildInfoBase fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "ETechType") != 0)
	{
		LOG_CRI << "pElemChild is not ETechType!";
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
	return true;
}

bool ToXML(const SGuildTechInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SGuildTechInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("帮派科技"));
	unique_ptr<TiXmlElement> pElem_SGuildInfoBase(new TiXmlElement("SGuildInfoBase"));
	if(pElem_SGuildInfoBase == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const SGuildInfoBase&)s, *pElem_SGuildInfoBase))
	{
		LOG_CRI << "SGuildInfoBase ToXML fails!";
		return false;
	}
	pElem_SGuildInfoBase->SetAttribute("type", ToUTF8Ptr("帮派信息基本类"));
	pElem_SGuildInfoBase->SetAttribute("comment", ToUTF8Ptr("父类SGuildInfoBase部分"));
	if(rElement.LinkEndChild(pElem_SGuildInfoBase.get()) != NULL)
		pElem_SGuildInfoBase.release();
	unique_ptr<TiXmlElement> pElem_eType(new TiXmlElement("ETechType"));
	if(pElem_eType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eType->SetAttribute("name", "eType");
	const char* pszEnum_eType = EnumValToStr(s.eType);
	if(pszEnum_eType == NULL)
	{
		LOG_CRI << "EnumValToStr for ETechType fails!";
		return false;
	}
	pElem_eType->SetAttribute("value", pszEnum_eType);
	pElem_eType->SetAttribute("comment", ToUTF8Ptr("科技类型"));
	if(rElement.LinkEndChild(pElem_eType.get()) != NULL)
		pElem_eType.release();
	unique_ptr<TiXmlElement> pElem_wLevel(new TiXmlElement("UINT16"));
	if(pElem_wLevel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wLevel->SetAttribute("name", "wLevel");
	pElem_wLevel->SetAttribute("value", NumberToString(s.wLevel).c_str());
	pElem_wLevel->SetAttribute("comment", ToUTF8Ptr("科技等级"));
	if(rElement.LinkEndChild(pElem_wLevel.get()) != NULL)
		pElem_wLevel.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecGuildTechInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SGuildTechInfoPtr p(new SGuildTechInfo);
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

bool VectorToXML(const TVecGuildTechInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SGuildTechInfo"));
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

SGuildLogInfo::SGuildLogInfo() : qwInstID(0), eType((ELogType)0), wMsgID(0), dwTime(0) { }

CInArchive& operator>>(CInArchive& src, SGuildLogInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (SGuildInfoBase&)s;
	src >> s.qwInstID;
	src >> (UINT8&)s.eType;
	src >> s.wMsgID;
	src >> s.vecParam;
	src >> s.vecString;
	src >> s.dwTime;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SGuildLogInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const SGuildInfoBase&)s;
	src << s.qwInstID;
	src << (UINT8&)s.eType;
	src << s.wMsgID;
	src << s.vecParam;
	src << s.vecString;
	src << s.dwTime;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecGuildLogInfo& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SGuildLogInfoPtr p(new SGuildLogInfo);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecGuildLogInfo& vec)
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

bool FromXML(TiXmlElement& rElement, SGuildLogInfo& s)
{
	if(strcmp(rElement.Value(), "SGuildLogInfo") != 0)
	{
		LOG_CRI << "rElement is not SGuildLogInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for SGuildInfoBase is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (SGuildInfoBase&)s))
	{
		LOG_CRI << "FromXML for: SGuildInfoBase fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
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
		LOG_CRI << "pElemChild for eType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "ELogType") != 0)
	{
		LOG_CRI << "pElemChild is not ELogType!";
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
		LOG_CRI << "pElemChild for wMsgID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wMsgID") != 0)
	{
		LOG_CRI << "Attribute: name is not wMsgID!";
		return false;
	}
	const char* pszVal_wMsgID = pElemChild->Attribute("value");
	if(pszVal_wMsgID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wMsgID, s.wMsgID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecParam is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecINT64") != 0)
	{
		LOG_CRI << "pElemChild is not TVecINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecParam") != 0)
	{
		LOG_CRI << "Attribute: name is not vecParam!";
		return false;
	}
	const char* pszText_vecParam = pElemChild->GetText();
	if(pszText_vecParam != NULL)
		SplitToNumber(pszText_vecParam, ",", s.vecParam);
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecString is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecString") != 0)
	{
		LOG_CRI << "pElemChild is not TVecString!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecString") != 0)
	{
		LOG_CRI << "Attribute: name is not vecString!";
		return false;
	}
	const char* pszText_vecString = pElemChild->GetText();
	if(pszText_vecString != NULL)
		SplitToText(pszText_vecString, ",", s.vecString);
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

bool ToXML(const SGuildLogInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SGuildLogInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("日志"));
	unique_ptr<TiXmlElement> pElem_SGuildInfoBase(new TiXmlElement("SGuildInfoBase"));
	if(pElem_SGuildInfoBase == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const SGuildInfoBase&)s, *pElem_SGuildInfoBase))
	{
		LOG_CRI << "SGuildInfoBase ToXML fails!";
		return false;
	}
	pElem_SGuildInfoBase->SetAttribute("type", ToUTF8Ptr("帮派信息基本类"));
	pElem_SGuildInfoBase->SetAttribute("comment", ToUTF8Ptr("父类SGuildInfoBase部分"));
	if(rElement.LinkEndChild(pElem_SGuildInfoBase.get()) != NULL)
		pElem_SGuildInfoBase.release();
	unique_ptr<TiXmlElement> pElem_qwInstID(new TiXmlElement("UINT64"));
	if(pElem_qwInstID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwInstID->SetAttribute("name", "qwInstID");
	pElem_qwInstID->SetAttribute("value", NumberToString(s.qwInstID).c_str());
	pElem_qwInstID->SetAttribute("comment", ToUTF8Ptr("唯一流水ID"));
	if(rElement.LinkEndChild(pElem_qwInstID.get()) != NULL)
		pElem_qwInstID.release();
	unique_ptr<TiXmlElement> pElem_eType(new TiXmlElement("ELogType"));
	if(pElem_eType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eType->SetAttribute("name", "eType");
	const char* pszEnum_eType = EnumValToStr(s.eType);
	if(pszEnum_eType == NULL)
	{
		LOG_CRI << "EnumValToStr for ELogType fails!";
		return false;
	}
	pElem_eType->SetAttribute("value", pszEnum_eType);
	pElem_eType->SetAttribute("comment", ToUTF8Ptr("日志类型"));
	if(rElement.LinkEndChild(pElem_eType.get()) != NULL)
		pElem_eType.release();
	unique_ptr<TiXmlElement> pElem_wMsgID(new TiXmlElement("UINT16"));
	if(pElem_wMsgID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wMsgID->SetAttribute("name", "wMsgID");
	pElem_wMsgID->SetAttribute("value", NumberToString(s.wMsgID).c_str());
	pElem_wMsgID->SetAttribute("comment", ToUTF8Ptr("消息ID"));
	if(rElement.LinkEndChild(pElem_wMsgID.get()) != NULL)
		pElem_wMsgID.release();
	unique_ptr<TiXmlElement> pElem_vecParam(new TiXmlElement("TVecINT64"));
	if(pElem_vecParam == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecParam->SetAttribute("name", "vecParam");
	string strText_vecParam;
	for(size_t i = 0; i < s.vecParam.size(); ++i)
	{
		if(i > 0)
			strText_vecParam += ", ";
		strText_vecParam += NumberToString(s.vecParam[i]);
	}
	unique_ptr<TiXmlText> pText_vecParam(new TiXmlText(strText_vecParam.c_str()));
	if(pText_vecParam == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(pElem_vecParam->LinkEndChild(pText_vecParam.get()) != NULL)
		pText_vecParam.release();
	pElem_vecParam->SetAttribute("comment", ToUTF8Ptr("整型变量"));
	if(rElement.LinkEndChild(pElem_vecParam.get()) != NULL)
		pElem_vecParam.release();
	unique_ptr<TiXmlElement> pElem_vecString(new TiXmlElement("TVecString"));
	if(pElem_vecString == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecString->SetAttribute("name", "vecString");
	string strText_vecString;
	for(size_t i = 0; i < s.vecString.size(); ++i)
	{
		if(i > 0)
			strText_vecString += ", ";
		strText_vecString += s.vecString[i];
	}
	unique_ptr<TiXmlText> pText_vecString(new TiXmlText(strText_vecString.c_str()));
	if(pText_vecString == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(pElem_vecString->LinkEndChild(pText_vecString.get()) != NULL)
		pText_vecString.release();
	pElem_vecString->SetAttribute("comment", ToUTF8Ptr("字符串型变量"));
	if(rElement.LinkEndChild(pElem_vecString.get()) != NULL)
		pElem_vecString.release();
	unique_ptr<TiXmlElement> pElem_dwTime(new TiXmlElement("UINT32"));
	if(pElem_dwTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwTime->SetAttribute("name", "dwTime");
	pElem_dwTime->SetAttribute("value", NumberToString(s.dwTime).c_str());
	pElem_dwTime->SetAttribute("comment", ToUTF8Ptr("日志时间"));
	if(rElement.LinkEndChild(pElem_dwTime.get()) != NULL)
		pElem_dwTime.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecGuildLogInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SGuildLogInfoPtr p(new SGuildLogInfo);
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

bool VectorToXML(const TVecGuildLogInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SGuildLogInfo"));
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

SGuildStatueInfo::SGuildStatueInfo() : wLevel(0), dwExp(0), byWorshipCount(0), byWorshipBit(0), dwTime(0) { }

SGuildStatueInfo::SGuildStatueInfo(SGuildStatueInfo&& src) : SGuildInfoBase(src), wLevel(src.wLevel), dwExp(src.dwExp), vecLogInfo(move(src.vecLogInfo)), byWorshipCount(src.byWorshipCount), byWorshipBit(src.byWorshipBit), 
			dwTime(src.dwTime) { }

SGuildStatueInfo& SGuildStatueInfo::operator=(SGuildStatueInfo&& rhs)
{
	if(this != &rhs)
	{
		this->~SGuildStatueInfo();
		new (this) SGuildStatueInfo(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SGuildStatueInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (SGuildInfoBase&)s;
	src >> s.wLevel;
	src >> s.dwExp;
	src >> s.vecLogInfo;
	src >> s.byWorshipCount;
	src >> s.byWorshipBit;
	src >> s.dwTime;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SGuildStatueInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const SGuildInfoBase&)s;
	src << s.wLevel;
	src << s.dwExp;
	src << s.vecLogInfo;
	src << s.byWorshipCount;
	src << s.byWorshipBit;
	src << s.dwTime;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecGuildStatueInfo& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SGuildStatueInfoPtr p(new SGuildStatueInfo);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecGuildStatueInfo& vec)
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

bool FromXML(TiXmlElement& rElement, SGuildStatueInfo& s)
{
	if(strcmp(rElement.Value(), "SGuildStatueInfo") != 0)
	{
		LOG_CRI << "rElement is not SGuildStatueInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for SGuildInfoBase is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (SGuildInfoBase&)s))
	{
		LOG_CRI << "FromXML for: SGuildInfoBase fails!";
		return false;
	}
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
		LOG_CRI << "pElemChild for dwExp is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwExp") != 0)
	{
		LOG_CRI << "Attribute: name is not dwExp!";
		return false;
	}
	const char* pszVal_dwExp = pElemChild->Attribute("value");
	if(pszVal_dwExp == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwExp, s.dwExp))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecLogInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecGuildLogInfo") != 0)
	{
		LOG_CRI << "pElemChild is not TVecGuildLogInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecLogInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not vecLogInfo!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecLogInfo))
	{
		LOG_CRI << "VectorFromXML for vecLogInfo fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byWorshipCount is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byWorshipCount") != 0)
	{
		LOG_CRI << "Attribute: name is not byWorshipCount!";
		return false;
	}
	const char* pszVal_byWorshipCount = pElemChild->Attribute("value");
	if(pszVal_byWorshipCount == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byWorshipCount, s.byWorshipCount))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byWorshipBit is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byWorshipBit") != 0)
	{
		LOG_CRI << "Attribute: name is not byWorshipBit!";
		return false;
	}
	const char* pszVal_byWorshipBit = pElemChild->Attribute("value");
	if(pszVal_byWorshipBit == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byWorshipBit, s.byWorshipBit))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
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

bool ToXML(const SGuildStatueInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SGuildStatueInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("帮派神像"));
	unique_ptr<TiXmlElement> pElem_SGuildInfoBase(new TiXmlElement("SGuildInfoBase"));
	if(pElem_SGuildInfoBase == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const SGuildInfoBase&)s, *pElem_SGuildInfoBase))
	{
		LOG_CRI << "SGuildInfoBase ToXML fails!";
		return false;
	}
	pElem_SGuildInfoBase->SetAttribute("type", ToUTF8Ptr("帮派信息基本类"));
	pElem_SGuildInfoBase->SetAttribute("comment", ToUTF8Ptr("父类SGuildInfoBase部分"));
	if(rElement.LinkEndChild(pElem_SGuildInfoBase.get()) != NULL)
		pElem_SGuildInfoBase.release();
	unique_ptr<TiXmlElement> pElem_wLevel(new TiXmlElement("UINT16"));
	if(pElem_wLevel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wLevel->SetAttribute("name", "wLevel");
	pElem_wLevel->SetAttribute("value", NumberToString(s.wLevel).c_str());
	pElem_wLevel->SetAttribute("comment", ToUTF8Ptr("神像等级"));
	if(rElement.LinkEndChild(pElem_wLevel.get()) != NULL)
		pElem_wLevel.release();
	unique_ptr<TiXmlElement> pElem_dwExp(new TiXmlElement("UINT32"));
	if(pElem_dwExp == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwExp->SetAttribute("name", "dwExp");
	pElem_dwExp->SetAttribute("value", NumberToString(s.dwExp).c_str());
	pElem_dwExp->SetAttribute("comment", ToUTF8Ptr("神像经验值"));
	if(rElement.LinkEndChild(pElem_dwExp.get()) != NULL)
		pElem_dwExp.release();
	unique_ptr<TiXmlElement> pElem_vecLogInfo(new TiXmlElement("TVecGuildLogInfo"));
	if(pElem_vecLogInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecLogInfo->SetAttribute("name", "vecLogInfo");
	if(!VectorToXML(s.vecLogInfo, *pElem_vecLogInfo))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecLogInfo->SetAttribute("comment", ToUTF8Ptr("神像日志"));
	if(rElement.LinkEndChild(pElem_vecLogInfo.get()) != NULL)
		pElem_vecLogInfo.release();
	unique_ptr<TiXmlElement> pElem_byWorshipCount(new TiXmlElement("UINT8"));
	if(pElem_byWorshipCount == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byWorshipCount->SetAttribute("name", "byWorshipCount");
	pElem_byWorshipCount->SetAttribute("value", NumberToString(s.byWorshipCount).c_str());
	pElem_byWorshipCount->SetAttribute("comment", ToUTF8Ptr("供奉人数"));
	if(rElement.LinkEndChild(pElem_byWorshipCount.get()) != NULL)
		pElem_byWorshipCount.release();
	unique_ptr<TiXmlElement> pElem_byWorshipBit(new TiXmlElement("UINT8"));
	if(pElem_byWorshipBit == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byWorshipBit->SetAttribute("name", "byWorshipBit");
	pElem_byWorshipBit->SetAttribute("value", NumberToString(s.byWorshipBit).c_str());
	pElem_byWorshipBit->SetAttribute("comment", ToUTF8Ptr("当前供奉（第N位表示第N种供奉类型）"));
	if(rElement.LinkEndChild(pElem_byWorshipBit.get()) != NULL)
		pElem_byWorshipBit.release();
	unique_ptr<TiXmlElement> pElem_dwTime(new TiXmlElement("UINT32"));
	if(pElem_dwTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwTime->SetAttribute("name", "dwTime");
	pElem_dwTime->SetAttribute("value", NumberToString(s.dwTime).c_str());
	pElem_dwTime->SetAttribute("comment", ToUTF8Ptr("操作时间"));
	if(rElement.LinkEndChild(pElem_dwTime.get()) != NULL)
		pElem_dwTime.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecGuildStatueInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SGuildStatueInfoPtr p(new SGuildStatueInfo);
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

bool VectorToXML(const TVecGuildStatueInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SGuildStatueInfo"));
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

SDBGuildUserInfo::SDBGuildUserInfo() : dwBattleScore(0), wPlayerFighterID(0), byQuality(0) { }

SDBGuildUserInfo::SDBGuildUserInfo(const SGuildUserInfo& sBaseInfo_, const TVecGuildTechInfo& vecTechInfo_, UINT32 dwBattleScore_, UINT16 wPlayerFighterID_, UINT8 byQuality_)
			: sBaseInfo(sBaseInfo_), vecTechInfo(vecTechInfo_), dwBattleScore(dwBattleScore_), wPlayerFighterID(wPlayerFighterID_), byQuality(byQuality_) { }

SDBGuildUserInfo::SDBGuildUserInfo(SDBGuildUserInfo&& src) : sBaseInfo(move(src.sBaseInfo)), vecTechInfo(move(src.vecTechInfo)), dwBattleScore(src.dwBattleScore), wPlayerFighterID(src.wPlayerFighterID), byQuality(src.byQuality) { }

SDBGuildUserInfo& SDBGuildUserInfo::operator=(SDBGuildUserInfo&& rhs)
{
	if(this != &rhs)
	{
		this->~SDBGuildUserInfo();
		new (this) SDBGuildUserInfo(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SDBGuildUserInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.sBaseInfo;
	src >> s.vecTechInfo;
	src >> s.dwBattleScore;
	src >> s.wPlayerFighterID;
	src >> s.byQuality;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SDBGuildUserInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.sBaseInfo;
	src << s.vecTechInfo;
	src << s.dwBattleScore;
	src << s.wPlayerFighterID;
	src << s.byQuality;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SDBGuildUserInfo& s)
{
	if(strcmp(rElement.Value(), "SDBGuildUserInfo") != 0)
	{
		LOG_CRI << "rElement is not SDBGuildUserInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for sBaseInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "SGuildUserInfo") != 0)
	{
		LOG_CRI << "pElemChild is not SGuildUserInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "sBaseInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not sBaseInfo!";
		return false;
	}
	if(!FromXML(*pElemChild, s.sBaseInfo))
	{
		LOG_CRI << "FromXML for: sBaseInfo fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecTechInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecGuildTechInfo") != 0)
	{
		LOG_CRI << "pElemChild is not TVecGuildTechInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecTechInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not vecTechInfo!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecTechInfo))
	{
		LOG_CRI << "VectorFromXML for vecTechInfo fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwBattleScore is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwBattleScore") != 0)
	{
		LOG_CRI << "Attribute: name is not dwBattleScore!";
		return false;
	}
	const char* pszVal_dwBattleScore = pElemChild->Attribute("value");
	if(pszVal_dwBattleScore == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwBattleScore, s.dwBattleScore))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wPlayerFighterID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wPlayerFighterID") != 0)
	{
		LOG_CRI << "Attribute: name is not wPlayerFighterID!";
		return false;
	}
	const char* pszVal_wPlayerFighterID = pElemChild->Attribute("value");
	if(pszVal_wPlayerFighterID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wPlayerFighterID, s.wPlayerFighterID))
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
	return true;
}

bool ToXML(const SDBGuildUserInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SDBGuildUserInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("数据库加载用帮派玩家数据"));
	unique_ptr<TiXmlElement> pElem_sBaseInfo(new TiXmlElement("SGuildUserInfo"));
	if(pElem_sBaseInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_sBaseInfo->SetAttribute("name", "sBaseInfo");
	if(!ToXML(s.sBaseInfo, *pElem_sBaseInfo))
	{
		LOG_CRI << "sBaseInfo ToXML fails!";
		return false;
	}
	pElem_sBaseInfo->SetAttribute("comment", ToUTF8Ptr("帮派用户基本信息"));
	if(rElement.LinkEndChild(pElem_sBaseInfo.get()) != NULL)
		pElem_sBaseInfo.release();
	unique_ptr<TiXmlElement> pElem_vecTechInfo(new TiXmlElement("TVecGuildTechInfo"));
	if(pElem_vecTechInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecTechInfo->SetAttribute("name", "vecTechInfo");
	if(!VectorToXML(s.vecTechInfo, *pElem_vecTechInfo))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecTechInfo->SetAttribute("comment", ToUTF8Ptr("帮派科技信息"));
	if(rElement.LinkEndChild(pElem_vecTechInfo.get()) != NULL)
		pElem_vecTechInfo.release();
	unique_ptr<TiXmlElement> pElem_dwBattleScore(new TiXmlElement("UINT32"));
	if(pElem_dwBattleScore == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwBattleScore->SetAttribute("name", "dwBattleScore");
	pElem_dwBattleScore->SetAttribute("value", NumberToString(s.dwBattleScore).c_str());
	pElem_dwBattleScore->SetAttribute("comment", ToUTF8Ptr("帮派战积分"));
	if(rElement.LinkEndChild(pElem_dwBattleScore.get()) != NULL)
		pElem_dwBattleScore.release();
	unique_ptr<TiXmlElement> pElem_wPlayerFighterID(new TiXmlElement("UINT16"));
	if(pElem_wPlayerFighterID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wPlayerFighterID->SetAttribute("name", "wPlayerFighterID");
	pElem_wPlayerFighterID->SetAttribute("value", NumberToString(s.wPlayerFighterID).c_str());
	pElem_wPlayerFighterID->SetAttribute("comment", ToUTF8Ptr("主将ID"));
	if(rElement.LinkEndChild(pElem_wPlayerFighterID.get()) != NULL)
		pElem_wPlayerFighterID.release();
	unique_ptr<TiXmlElement> pElem_byQuality(new TiXmlElement("UINT8"));
	if(pElem_byQuality == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byQuality->SetAttribute("name", "byQuality");
	pElem_byQuality->SetAttribute("value", NumberToString(s.byQuality).c_str());
	pElem_byQuality->SetAttribute("comment", ToUTF8Ptr("主将品质"));
	if(rElement.LinkEndChild(pElem_byQuality.get()) != NULL)
		pElem_byQuality.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecDBGuildUserInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SDBGuildUserInfo s;
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

bool VectorToXML(const TVecDBGuildUserInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SDBGuildUserInfo"));
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

SGuildAllInfo::SGuildAllInfo() { }

SGuildAllInfo::SGuildAllInfo(const SGuildBaseInfo& sBaseInfo_, const TVecGuildUserInfo& vecMemberInfo_, const TVecGuildApplyInfo& vecApplyInfo_, const TVecGuildBuildingInfo& vecBuildingInfo_, const TVecGuildAuthorityInfo& vecAuthority_, 
			const TVecGuildTechInfo& vecTech_, const SGuildStatueInfo& sStatueInfo_, const TVecGuildLogInfo& vecLogInfo_)
			: sBaseInfo(sBaseInfo_), vecMemberInfo(vecMemberInfo_), vecApplyInfo(vecApplyInfo_), vecBuildingInfo(vecBuildingInfo_), vecAuthority(vecAuthority_), 
			vecTech(vecTech_), sStatueInfo(sStatueInfo_), vecLogInfo(vecLogInfo_) { }

SGuildAllInfo::SGuildAllInfo(SGuildAllInfo&& src) : sBaseInfo(move(src.sBaseInfo)), vecMemberInfo(move(src.vecMemberInfo)), vecApplyInfo(move(src.vecApplyInfo)), vecBuildingInfo(move(src.vecBuildingInfo)), vecAuthority(move(src.vecAuthority)), 
			vecTech(move(src.vecTech)), sStatueInfo(move(src.sStatueInfo)), vecLogInfo(move(src.vecLogInfo)) { }

SGuildAllInfo& SGuildAllInfo::operator=(SGuildAllInfo&& rhs)
{
	if(this != &rhs)
	{
		this->~SGuildAllInfo();
		new (this) SGuildAllInfo(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SGuildAllInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.sBaseInfo;
	src >> s.vecMemberInfo;
	src >> s.vecApplyInfo;
	src >> s.vecBuildingInfo;
	src >> s.vecAuthority;
	src >> s.vecTech;
	src >> s.sStatueInfo;
	src >> s.vecLogInfo;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SGuildAllInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.sBaseInfo;
	src << s.vecMemberInfo;
	src << s.vecApplyInfo;
	src << s.vecBuildingInfo;
	src << s.vecAuthority;
	src << s.vecTech;
	src << s.sStatueInfo;
	src << s.vecLogInfo;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SGuildAllInfo& s)
{
	if(strcmp(rElement.Value(), "SGuildAllInfo") != 0)
	{
		LOG_CRI << "rElement is not SGuildAllInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for sBaseInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "SGuildBaseInfo") != 0)
	{
		LOG_CRI << "pElemChild is not SGuildBaseInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "sBaseInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not sBaseInfo!";
		return false;
	}
	if(!FromXML(*pElemChild, s.sBaseInfo))
	{
		LOG_CRI << "FromXML for: sBaseInfo fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecMemberInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecGuildUserInfo") != 0)
	{
		LOG_CRI << "pElemChild is not TVecGuildUserInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecMemberInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not vecMemberInfo!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecMemberInfo))
	{
		LOG_CRI << "VectorFromXML for vecMemberInfo fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecApplyInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecGuildApplyInfo") != 0)
	{
		LOG_CRI << "pElemChild is not TVecGuildApplyInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecApplyInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not vecApplyInfo!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecApplyInfo))
	{
		LOG_CRI << "VectorFromXML for vecApplyInfo fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecBuildingInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecGuildBuildingInfo") != 0)
	{
		LOG_CRI << "pElemChild is not TVecGuildBuildingInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecBuildingInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not vecBuildingInfo!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecBuildingInfo))
	{
		LOG_CRI << "VectorFromXML for vecBuildingInfo fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecAuthority is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecGuildAuthorityInfo") != 0)
	{
		LOG_CRI << "pElemChild is not TVecGuildAuthorityInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecAuthority") != 0)
	{
		LOG_CRI << "Attribute: name is not vecAuthority!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecAuthority))
	{
		LOG_CRI << "VectorFromXML for vecAuthority fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecTech is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecGuildTechInfo") != 0)
	{
		LOG_CRI << "pElemChild is not TVecGuildTechInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecTech") != 0)
	{
		LOG_CRI << "Attribute: name is not vecTech!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecTech))
	{
		LOG_CRI << "VectorFromXML for vecTech fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for sStatueInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "SGuildStatueInfo") != 0)
	{
		LOG_CRI << "pElemChild is not SGuildStatueInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "sStatueInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not sStatueInfo!";
		return false;
	}
	if(!FromXML(*pElemChild, s.sStatueInfo))
	{
		LOG_CRI << "FromXML for: sStatueInfo fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecLogInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecGuildLogInfo") != 0)
	{
		LOG_CRI << "pElemChild is not TVecGuildLogInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecLogInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not vecLogInfo!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecLogInfo))
	{
		LOG_CRI << "VectorFromXML for vecLogInfo fails!";
		return false;
	}
	return true;
}

bool ToXML(const SGuildAllInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SGuildAllInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("帮派完整信息"));
	unique_ptr<TiXmlElement> pElem_sBaseInfo(new TiXmlElement("SGuildBaseInfo"));
	if(pElem_sBaseInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_sBaseInfo->SetAttribute("name", "sBaseInfo");
	if(!ToXML(s.sBaseInfo, *pElem_sBaseInfo))
	{
		LOG_CRI << "sBaseInfo ToXML fails!";
		return false;
	}
	pElem_sBaseInfo->SetAttribute("comment", ToUTF8Ptr("基本信息"));
	if(rElement.LinkEndChild(pElem_sBaseInfo.get()) != NULL)
		pElem_sBaseInfo.release();
	unique_ptr<TiXmlElement> pElem_vecMemberInfo(new TiXmlElement("TVecGuildUserInfo"));
	if(pElem_vecMemberInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecMemberInfo->SetAttribute("name", "vecMemberInfo");
	if(!VectorToXML(s.vecMemberInfo, *pElem_vecMemberInfo))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecMemberInfo->SetAttribute("comment", ToUTF8Ptr("帮派成员信息"));
	if(rElement.LinkEndChild(pElem_vecMemberInfo.get()) != NULL)
		pElem_vecMemberInfo.release();
	unique_ptr<TiXmlElement> pElem_vecApplyInfo(new TiXmlElement("TVecGuildApplyInfo"));
	if(pElem_vecApplyInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecApplyInfo->SetAttribute("name", "vecApplyInfo");
	if(!VectorToXML(s.vecApplyInfo, *pElem_vecApplyInfo))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecApplyInfo->SetAttribute("comment", ToUTF8Ptr("帮派申请信息"));
	if(rElement.LinkEndChild(pElem_vecApplyInfo.get()) != NULL)
		pElem_vecApplyInfo.release();
	unique_ptr<TiXmlElement> pElem_vecBuildingInfo(new TiXmlElement("TVecGuildBuildingInfo"));
	if(pElem_vecBuildingInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecBuildingInfo->SetAttribute("name", "vecBuildingInfo");
	if(!VectorToXML(s.vecBuildingInfo, *pElem_vecBuildingInfo))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecBuildingInfo->SetAttribute("comment", ToUTF8Ptr("帮派建筑信息"));
	if(rElement.LinkEndChild(pElem_vecBuildingInfo.get()) != NULL)
		pElem_vecBuildingInfo.release();
	unique_ptr<TiXmlElement> pElem_vecAuthority(new TiXmlElement("TVecGuildAuthorityInfo"));
	if(pElem_vecAuthority == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecAuthority->SetAttribute("name", "vecAuthority");
	if(!VectorToXML(s.vecAuthority, *pElem_vecAuthority))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecAuthority->SetAttribute("comment", ToUTF8Ptr("帮派可选权限信息"));
	if(rElement.LinkEndChild(pElem_vecAuthority.get()) != NULL)
		pElem_vecAuthority.release();
	unique_ptr<TiXmlElement> pElem_vecTech(new TiXmlElement("TVecGuildTechInfo"));
	if(pElem_vecTech == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecTech->SetAttribute("name", "vecTech");
	if(!VectorToXML(s.vecTech, *pElem_vecTech))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecTech->SetAttribute("comment", ToUTF8Ptr("帮派科技信息"));
	if(rElement.LinkEndChild(pElem_vecTech.get()) != NULL)
		pElem_vecTech.release();
	unique_ptr<TiXmlElement> pElem_sStatueInfo(new TiXmlElement("SGuildStatueInfo"));
	if(pElem_sStatueInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_sStatueInfo->SetAttribute("name", "sStatueInfo");
	if(!ToXML(s.sStatueInfo, *pElem_sStatueInfo))
	{
		LOG_CRI << "sStatueInfo ToXML fails!";
		return false;
	}
	pElem_sStatueInfo->SetAttribute("comment", ToUTF8Ptr("帮派神像信息"));
	if(rElement.LinkEndChild(pElem_sStatueInfo.get()) != NULL)
		pElem_sStatueInfo.release();
	unique_ptr<TiXmlElement> pElem_vecLogInfo(new TiXmlElement("TVecGuildLogInfo"));
	if(pElem_vecLogInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecLogInfo->SetAttribute("name", "vecLogInfo");
	if(!VectorToXML(s.vecLogInfo, *pElem_vecLogInfo))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecLogInfo->SetAttribute("comment", ToUTF8Ptr("帮派日志信息"));
	if(rElement.LinkEndChild(pElem_vecLogInfo.get()) != NULL)
		pElem_vecLogInfo.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecGuildAllInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SGuildAllInfo s;
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

bool VectorToXML(const TVecGuildAllInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SGuildAllInfo"));
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

SDBGuildAllInfo::SDBGuildAllInfo() { }

SDBGuildAllInfo::SDBGuildAllInfo(const SGuildBaseInfo& sBaseInfo_, const TVecDBGuildUserInfo& vecMemberInfo_, const TVecGuildApplyInfo& vecApplyInfo_, const TVecGuildBuildingInfo& vecBuildingInfo_, const TVecGuildAuthorityInfo& vecAuthority_, 
			const SGuildStatueInfo& sStatueInfo_, const TVecGuildLogInfo& vecLogInfo_, const TVecGuildLogInfo& vecLingShanShopBuyLogInfo_)
			: sBaseInfo(sBaseInfo_), vecMemberInfo(vecMemberInfo_), vecApplyInfo(vecApplyInfo_), vecBuildingInfo(vecBuildingInfo_), vecAuthority(vecAuthority_), 
			sStatueInfo(sStatueInfo_), vecLogInfo(vecLogInfo_), vecLingShanShopBuyLogInfo(vecLingShanShopBuyLogInfo_) { }

SDBGuildAllInfo::SDBGuildAllInfo(SDBGuildAllInfo&& src) : sBaseInfo(move(src.sBaseInfo)), vecMemberInfo(move(src.vecMemberInfo)), vecApplyInfo(move(src.vecApplyInfo)), vecBuildingInfo(move(src.vecBuildingInfo)), vecAuthority(move(src.vecAuthority)), 
			sStatueInfo(move(src.sStatueInfo)), vecLogInfo(move(src.vecLogInfo)), vecLingShanShopBuyLogInfo(move(src.vecLingShanShopBuyLogInfo)) { }

SDBGuildAllInfo& SDBGuildAllInfo::operator=(SDBGuildAllInfo&& rhs)
{
	if(this != &rhs)
	{
		this->~SDBGuildAllInfo();
		new (this) SDBGuildAllInfo(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SDBGuildAllInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.sBaseInfo;
	src >> s.vecMemberInfo;
	src >> s.vecApplyInfo;
	src >> s.vecBuildingInfo;
	src >> s.vecAuthority;
	src >> s.sStatueInfo;
	src >> s.vecLogInfo;
	src >> s.vecLingShanShopBuyLogInfo;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SDBGuildAllInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.sBaseInfo;
	src << s.vecMemberInfo;
	src << s.vecApplyInfo;
	src << s.vecBuildingInfo;
	src << s.vecAuthority;
	src << s.sStatueInfo;
	src << s.vecLogInfo;
	src << s.vecLingShanShopBuyLogInfo;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SDBGuildAllInfo& s)
{
	if(strcmp(rElement.Value(), "SDBGuildAllInfo") != 0)
	{
		LOG_CRI << "rElement is not SDBGuildAllInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for sBaseInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "SGuildBaseInfo") != 0)
	{
		LOG_CRI << "pElemChild is not SGuildBaseInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "sBaseInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not sBaseInfo!";
		return false;
	}
	if(!FromXML(*pElemChild, s.sBaseInfo))
	{
		LOG_CRI << "FromXML for: sBaseInfo fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecMemberInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecDBGuildUserInfo") != 0)
	{
		LOG_CRI << "pElemChild is not TVecDBGuildUserInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecMemberInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not vecMemberInfo!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecMemberInfo))
	{
		LOG_CRI << "VectorFromXML for vecMemberInfo fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecApplyInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecGuildApplyInfo") != 0)
	{
		LOG_CRI << "pElemChild is not TVecGuildApplyInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecApplyInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not vecApplyInfo!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecApplyInfo))
	{
		LOG_CRI << "VectorFromXML for vecApplyInfo fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecBuildingInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecGuildBuildingInfo") != 0)
	{
		LOG_CRI << "pElemChild is not TVecGuildBuildingInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecBuildingInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not vecBuildingInfo!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecBuildingInfo))
	{
		LOG_CRI << "VectorFromXML for vecBuildingInfo fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecAuthority is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecGuildAuthorityInfo") != 0)
	{
		LOG_CRI << "pElemChild is not TVecGuildAuthorityInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecAuthority") != 0)
	{
		LOG_CRI << "Attribute: name is not vecAuthority!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecAuthority))
	{
		LOG_CRI << "VectorFromXML for vecAuthority fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for sStatueInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "SGuildStatueInfo") != 0)
	{
		LOG_CRI << "pElemChild is not SGuildStatueInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "sStatueInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not sStatueInfo!";
		return false;
	}
	if(!FromXML(*pElemChild, s.sStatueInfo))
	{
		LOG_CRI << "FromXML for: sStatueInfo fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecLogInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecGuildLogInfo") != 0)
	{
		LOG_CRI << "pElemChild is not TVecGuildLogInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecLogInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not vecLogInfo!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecLogInfo))
	{
		LOG_CRI << "VectorFromXML for vecLogInfo fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecLingShanShopBuyLogInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecGuildLogInfo") != 0)
	{
		LOG_CRI << "pElemChild is not TVecGuildLogInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecLingShanShopBuyLogInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not vecLingShanShopBuyLogInfo!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecLingShanShopBuyLogInfo))
	{
		LOG_CRI << "VectorFromXML for vecLingShanShopBuyLogInfo fails!";
		return false;
	}
	return true;
}

bool ToXML(const SDBGuildAllInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SDBGuildAllInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("帮派完整信息(数据库传来的内部协议)"));
	unique_ptr<TiXmlElement> pElem_sBaseInfo(new TiXmlElement("SGuildBaseInfo"));
	if(pElem_sBaseInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_sBaseInfo->SetAttribute("name", "sBaseInfo");
	if(!ToXML(s.sBaseInfo, *pElem_sBaseInfo))
	{
		LOG_CRI << "sBaseInfo ToXML fails!";
		return false;
	}
	pElem_sBaseInfo->SetAttribute("comment", ToUTF8Ptr("基本信息"));
	if(rElement.LinkEndChild(pElem_sBaseInfo.get()) != NULL)
		pElem_sBaseInfo.release();
	unique_ptr<TiXmlElement> pElem_vecMemberInfo(new TiXmlElement("TVecDBGuildUserInfo"));
	if(pElem_vecMemberInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecMemberInfo->SetAttribute("name", "vecMemberInfo");
	if(!VectorToXML(s.vecMemberInfo, *pElem_vecMemberInfo))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecMemberInfo->SetAttribute("comment", ToUTF8Ptr("帮派成员信息"));
	if(rElement.LinkEndChild(pElem_vecMemberInfo.get()) != NULL)
		pElem_vecMemberInfo.release();
	unique_ptr<TiXmlElement> pElem_vecApplyInfo(new TiXmlElement("TVecGuildApplyInfo"));
	if(pElem_vecApplyInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecApplyInfo->SetAttribute("name", "vecApplyInfo");
	if(!VectorToXML(s.vecApplyInfo, *pElem_vecApplyInfo))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecApplyInfo->SetAttribute("comment", ToUTF8Ptr("帮派申请信息"));
	if(rElement.LinkEndChild(pElem_vecApplyInfo.get()) != NULL)
		pElem_vecApplyInfo.release();
	unique_ptr<TiXmlElement> pElem_vecBuildingInfo(new TiXmlElement("TVecGuildBuildingInfo"));
	if(pElem_vecBuildingInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecBuildingInfo->SetAttribute("name", "vecBuildingInfo");
	if(!VectorToXML(s.vecBuildingInfo, *pElem_vecBuildingInfo))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecBuildingInfo->SetAttribute("comment", ToUTF8Ptr("帮派建筑信息"));
	if(rElement.LinkEndChild(pElem_vecBuildingInfo.get()) != NULL)
		pElem_vecBuildingInfo.release();
	unique_ptr<TiXmlElement> pElem_vecAuthority(new TiXmlElement("TVecGuildAuthorityInfo"));
	if(pElem_vecAuthority == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecAuthority->SetAttribute("name", "vecAuthority");
	if(!VectorToXML(s.vecAuthority, *pElem_vecAuthority))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecAuthority->SetAttribute("comment", ToUTF8Ptr("帮派可选权限信息"));
	if(rElement.LinkEndChild(pElem_vecAuthority.get()) != NULL)
		pElem_vecAuthority.release();
	unique_ptr<TiXmlElement> pElem_sStatueInfo(new TiXmlElement("SGuildStatueInfo"));
	if(pElem_sStatueInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_sStatueInfo->SetAttribute("name", "sStatueInfo");
	if(!ToXML(s.sStatueInfo, *pElem_sStatueInfo))
	{
		LOG_CRI << "sStatueInfo ToXML fails!";
		return false;
	}
	pElem_sStatueInfo->SetAttribute("comment", ToUTF8Ptr("帮派神像信息"));
	if(rElement.LinkEndChild(pElem_sStatueInfo.get()) != NULL)
		pElem_sStatueInfo.release();
	unique_ptr<TiXmlElement> pElem_vecLogInfo(new TiXmlElement("TVecGuildLogInfo"));
	if(pElem_vecLogInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecLogInfo->SetAttribute("name", "vecLogInfo");
	if(!VectorToXML(s.vecLogInfo, *pElem_vecLogInfo))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecLogInfo->SetAttribute("comment", ToUTF8Ptr("帮派日志信息"));
	if(rElement.LinkEndChild(pElem_vecLogInfo.get()) != NULL)
		pElem_vecLogInfo.release();
	unique_ptr<TiXmlElement> pElem_vecLingShanShopBuyLogInfo(new TiXmlElement("TVecGuildLogInfo"));
	if(pElem_vecLingShanShopBuyLogInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecLingShanShopBuyLogInfo->SetAttribute("name", "vecLingShanShopBuyLogInfo");
	if(!VectorToXML(s.vecLingShanShopBuyLogInfo, *pElem_vecLingShanShopBuyLogInfo))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecLingShanShopBuyLogInfo->SetAttribute("comment", ToUTF8Ptr("帮派灵山商店购买日志信息"));
	if(rElement.LinkEndChild(pElem_vecLingShanShopBuyLogInfo.get()) != NULL)
		pElem_vecLingShanShopBuyLogInfo.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecDBGuildAllInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SDBGuildAllInfo s;
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

bool VectorToXML(const TVecDBGuildAllInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SDBGuildAllInfo"));
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

SGuildListInfo::SGuildListInfo() : qwGuildID(0), qwOwnerID(0), byLevel(0), wUserCount(0), wMaxUserCount(0) { }

SGuildListInfo::SGuildListInfo(UINT64 qwGuildID_, const std::string& strName_, const std::string& strInfo_, UINT64 qwOwnerID_, const std::string& strOwnerName_, 
			UINT8 byLevel_, UINT16 wUserCount_, UINT16 wMaxUserCount_)
			: qwGuildID(qwGuildID_), strName(strName_), strInfo(strInfo_), qwOwnerID(qwOwnerID_), strOwnerName(strOwnerName_), 
			byLevel(byLevel_), wUserCount(wUserCount_), wMaxUserCount(wMaxUserCount_) { }

SGuildListInfo::SGuildListInfo(SGuildListInfo&& src) : qwGuildID(src.qwGuildID), strName(move(src.strName)), strInfo(move(src.strInfo)), qwOwnerID(src.qwOwnerID), strOwnerName(move(src.strOwnerName)), 
			byLevel(src.byLevel), wUserCount(src.wUserCount), wMaxUserCount(src.wMaxUserCount) { }

SGuildListInfo& SGuildListInfo::operator=(SGuildListInfo&& rhs)
{
	if(this != &rhs)
	{
		this->~SGuildListInfo();
		new (this) SGuildListInfo(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SGuildListInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwGuildID;
	src >> s.strName;
	src >> s.strInfo;
	src >> s.qwOwnerID;
	src >> s.strOwnerName;
	src >> s.byLevel;
	src >> s.wUserCount;
	src >> s.wMaxUserCount;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SGuildListInfo& s)
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
	src << s.strInfo;
	src << s.qwOwnerID;
	src << s.strOwnerName;
	src << s.byLevel;
	src << s.wUserCount;
	src << s.wMaxUserCount;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SGuildListInfo& s)
{
	if(strcmp(rElement.Value(), "SGuildListInfo") != 0)
	{
		LOG_CRI << "rElement is not SGuildListInfo!";
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
		LOG_CRI << "pElemChild for strInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not strInfo!";
		return false;
	}
	const char* pszVal_strInfo = pElemChild->Attribute("value");
	if(pszVal_strInfo == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strInfo = pszVal_strInfo;
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
		LOG_CRI << "pElemChild for strOwnerName is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strOwnerName") != 0)
	{
		LOG_CRI << "Attribute: name is not strOwnerName!";
		return false;
	}
	const char* pszVal_strOwnerName = pElemChild->Attribute("value");
	if(pszVal_strOwnerName == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strOwnerName = pszVal_strOwnerName;
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
		LOG_CRI << "pElemChild for wUserCount is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wUserCount") != 0)
	{
		LOG_CRI << "Attribute: name is not wUserCount!";
		return false;
	}
	const char* pszVal_wUserCount = pElemChild->Attribute("value");
	if(pszVal_wUserCount == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wUserCount, s.wUserCount))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wMaxUserCount is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wMaxUserCount") != 0)
	{
		LOG_CRI << "Attribute: name is not wMaxUserCount!";
		return false;
	}
	const char* pszVal_wMaxUserCount = pElemChild->Attribute("value");
	if(pszVal_wMaxUserCount == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wMaxUserCount, s.wMaxUserCount))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SGuildListInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SGuildListInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("帮派列表信息"));
	unique_ptr<TiXmlElement> pElem_qwGuildID(new TiXmlElement("UINT64"));
	if(pElem_qwGuildID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwGuildID->SetAttribute("name", "qwGuildID");
	pElem_qwGuildID->SetAttribute("value", NumberToString(s.qwGuildID).c_str());
	pElem_qwGuildID->SetAttribute("comment", ToUTF8Ptr("帮派唯一ID"));
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
	pElem_strName->SetAttribute("comment", ToUTF8Ptr("帮派名称"));
	if(rElement.LinkEndChild(pElem_strName.get()) != NULL)
		pElem_strName.release();
	unique_ptr<TiXmlElement> pElem_strInfo(new TiXmlElement("string"));
	if(pElem_strInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strInfo->SetAttribute("name", "strInfo");
	pElem_strInfo->SetAttribute("value", s.strInfo.c_str());
	pElem_strInfo->SetAttribute("comment", ToUTF8Ptr("帮派公告"));
	if(rElement.LinkEndChild(pElem_strInfo.get()) != NULL)
		pElem_strInfo.release();
	unique_ptr<TiXmlElement> pElem_qwOwnerID(new TiXmlElement("UINT64"));
	if(pElem_qwOwnerID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwOwnerID->SetAttribute("name", "qwOwnerID");
	pElem_qwOwnerID->SetAttribute("value", NumberToString(s.qwOwnerID).c_str());
	pElem_qwOwnerID->SetAttribute("comment", ToUTF8Ptr("帮主ID"));
	if(rElement.LinkEndChild(pElem_qwOwnerID.get()) != NULL)
		pElem_qwOwnerID.release();
	unique_ptr<TiXmlElement> pElem_strOwnerName(new TiXmlElement("string"));
	if(pElem_strOwnerName == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strOwnerName->SetAttribute("name", "strOwnerName");
	pElem_strOwnerName->SetAttribute("value", s.strOwnerName.c_str());
	pElem_strOwnerName->SetAttribute("comment", ToUTF8Ptr("帮主名称"));
	if(rElement.LinkEndChild(pElem_strOwnerName.get()) != NULL)
		pElem_strOwnerName.release();
	unique_ptr<TiXmlElement> pElem_byLevel(new TiXmlElement("UINT8"));
	if(pElem_byLevel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byLevel->SetAttribute("name", "byLevel");
	pElem_byLevel->SetAttribute("value", NumberToString(s.byLevel).c_str());
	pElem_byLevel->SetAttribute("comment", ToUTF8Ptr("帮派等级"));
	if(rElement.LinkEndChild(pElem_byLevel.get()) != NULL)
		pElem_byLevel.release();
	unique_ptr<TiXmlElement> pElem_wUserCount(new TiXmlElement("UINT16"));
	if(pElem_wUserCount == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wUserCount->SetAttribute("name", "wUserCount");
	pElem_wUserCount->SetAttribute("value", NumberToString(s.wUserCount).c_str());
	pElem_wUserCount->SetAttribute("comment", ToUTF8Ptr("成员数量"));
	if(rElement.LinkEndChild(pElem_wUserCount.get()) != NULL)
		pElem_wUserCount.release();
	unique_ptr<TiXmlElement> pElem_wMaxUserCount(new TiXmlElement("UINT16"));
	if(pElem_wMaxUserCount == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wMaxUserCount->SetAttribute("name", "wMaxUserCount");
	pElem_wMaxUserCount->SetAttribute("value", NumberToString(s.wMaxUserCount).c_str());
	pElem_wMaxUserCount->SetAttribute("comment", ToUTF8Ptr("最大成员数量"));
	if(rElement.LinkEndChild(pElem_wMaxUserCount.get()) != NULL)
		pElem_wMaxUserCount.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecGuildListInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SGuildListInfo s;
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

bool VectorToXML(const TVecGuildListInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SGuildListInfo"));
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

SDBGuildBattleInfo::SDBGuildBattleInfo() : qwGuildID(0), dwScore(0) { }

SDBGuildBattleInfo::SDBGuildBattleInfo(UINT64 qwGuildID_, UINT32 dwScore_) : qwGuildID(qwGuildID_), dwScore(dwScore_) { }

CInArchive& operator>>(CInArchive& src, SDBGuildBattleInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwGuildID;
	src >> s.dwScore;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SDBGuildBattleInfo& s)
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

bool FromXML(TiXmlElement& rElement, SDBGuildBattleInfo& s)
{
	if(strcmp(rElement.Value(), "SDBGuildBattleInfo") != 0)
	{
		LOG_CRI << "rElement is not SDBGuildBattleInfo!";
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

bool ToXML(const SDBGuildBattleInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SDBGuildBattleInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("数据库加载用帮派玩家数据"));
	unique_ptr<TiXmlElement> pElem_qwGuildID(new TiXmlElement("UINT64"));
	if(pElem_qwGuildID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwGuildID->SetAttribute("name", "qwGuildID");
	pElem_qwGuildID->SetAttribute("value", NumberToString(s.qwGuildID).c_str());
	pElem_qwGuildID->SetAttribute("comment", ToUTF8Ptr("帮派唯一ID"));
	if(rElement.LinkEndChild(pElem_qwGuildID.get()) != NULL)
		pElem_qwGuildID.release();
	unique_ptr<TiXmlElement> pElem_dwScore(new TiXmlElement("UINT32"));
	if(pElem_dwScore == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwScore->SetAttribute("name", "dwScore");
	pElem_dwScore->SetAttribute("value", NumberToString(s.dwScore).c_str());
	pElem_dwScore->SetAttribute("comment", ToUTF8Ptr("帮派战积分"));
	if(rElement.LinkEndChild(pElem_dwScore.get()) != NULL)
		pElem_dwScore.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecDBGuildBattleInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SDBGuildBattleInfo s;
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

bool VectorToXML(const TVecDBGuildBattleInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SDBGuildBattleInfo"));
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

SGetGuildInfoBase::SGetGuildInfoBase() { }

CInArchive& operator>>(CInArchive& src, SGetGuildInfoBase& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SGetGuildInfoBase& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, SGetGuildInfoBase_Wrapper& rWrapper)
{
	EType_SGetGuildInfoBase eType = eType_SGetGuildInfoBase;
	src >> (UINT8&)eType;
	switch(eType)
	{
	case eType_SGetGuildInfoBase:
		{
			rWrapper.ptr.reset(new SGetGuildInfoBase);
			src >> (SGetGuildInfoBase&)*rWrapper.ptr;
		}
		break;
	case eType_SOtherGuildListInfo:
		{
			rWrapper.ptr.reset(new SOtherGuildListInfo);
			src >> (SOtherGuildListInfo&)*rWrapper.ptr;
		}
		break;
	case eType_SSelfGuildInfo:
		{
			rWrapper.ptr.reset(new SSelfGuildInfo);
			src >> (SSelfGuildInfo&)*rWrapper.ptr;
		}
		break;
	default:
		throw "Unknown value for EType_SGetGuildInfoBase";
		break;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SGetGuildInfoBase_Wrapper& rWrapper)
{
	if(rWrapper.ptr != NULL)
	{
		src << (UINT8)rWrapper.ptr->GetClassType();
		switch(rWrapper.ptr->GetClassType())
		{
		case eType_SGetGuildInfoBase:
			src << (SGetGuildInfoBase&)*rWrapper.ptr;
			break;
		case eType_SOtherGuildListInfo:
			src << (SOtherGuildListInfo&)*rWrapper.ptr;
			break;
		case eType_SSelfGuildInfo:
			src << (SSelfGuildInfo&)*rWrapper.ptr;
			break;
		default:
			throw "Unknown value for EType_SGetGuildInfoBase";
			break;
		}
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SGetGuildInfoBase& s)
{
	if(strcmp(rElement.Value(), "SGetGuildInfoBase") != 0)
	{
		LOG_CRI << "rElement is not SGetGuildInfoBase!";
		return false;
	}
	return true;
}

bool ToXML(const SGetGuildInfoBase& s, TiXmlElement& rElement)
{
	rElement.SetValue("SGetGuildInfoBase");
	rElement.SetAttribute("type", ToUTF8Ptr(""));
	return true;
}

bool SuperFromXML(TiXmlElement& rElement, SGetGuildInfoBasePtr& p)
{
	const char* pszName = rElement.Value();
	if(pszName == NULL)
	{
		LOG_CRI << "Element Name is empty!";
		return false;
	}
	if(strcmp(pszName, "SGetGuildInfoBase") == 0)
	{
		SGetGuildInfoBasePtr pStruct(new SGetGuildInfoBase);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SGetGuildInfoBase";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SGetGuildInfoBase FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SOtherGuildListInfo") == 0)
	{
		SOtherGuildListInfoPtr pStruct(new SOtherGuildListInfo);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SOtherGuildListInfo";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SOtherGuildListInfo FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SSelfGuildInfo") == 0)
	{
		SSelfGuildInfoPtr pStruct(new SSelfGuildInfo);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SSelfGuildInfo";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SSelfGuildInfo FromXML fails!";
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

bool SuperToXML(const SGetGuildInfoBase& s, TiXmlElement& rElement)
{
	switch(s.GetClassType())
	{
	case eType_SGetGuildInfoBase:
		return ToXML((SGetGuildInfoBase&)s, rElement);
	case eType_SOtherGuildListInfo:
		return ToXML((SOtherGuildListInfo&)s, rElement);
	case eType_SSelfGuildInfo:
		return ToXML((SSelfGuildInfo&)s, rElement);
	default:
		LOG_CRI << "Invalid type: " << s.GetClassType();
		return false;
	}
}

#endif

SOtherGuildListInfo::SOtherGuildListInfo() : dwMaxGuildCount(0), dwCurGuildCount(0) { }

SOtherGuildListInfo::SOtherGuildListInfo(SOtherGuildListInfo&& src) : SGetGuildInfoBase(src), dwMaxGuildCount(src.dwMaxGuildCount), dwCurGuildCount(src.dwCurGuildCount), vecGuildListInfo(move(src.vecGuildListInfo)), vecApplyGuildID(src.vecApplyGuildID) { }

SOtherGuildListInfo& SOtherGuildListInfo::operator=(SOtherGuildListInfo&& rhs)
{
	if(this != &rhs)
	{
		this->~SOtherGuildListInfo();
		new (this) SOtherGuildListInfo(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SOtherGuildListInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (SGetGuildInfoBase&)s;
	src >> s.dwMaxGuildCount;
	src >> s.dwCurGuildCount;
	src >> s.vecGuildListInfo;
	src >> s.vecApplyGuildID;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SOtherGuildListInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const SGetGuildInfoBase&)s;
	src << s.dwMaxGuildCount;
	src << s.dwCurGuildCount;
	src << s.vecGuildListInfo;
	src << s.vecApplyGuildID;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecOtherGuildListInfo& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SOtherGuildListInfoPtr p(new SOtherGuildListInfo);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecOtherGuildListInfo& vec)
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

bool FromXML(TiXmlElement& rElement, SOtherGuildListInfo& s)
{
	if(strcmp(rElement.Value(), "SOtherGuildListInfo") != 0)
	{
		LOG_CRI << "rElement is not SOtherGuildListInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for SGetGuildInfoBase is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (SGetGuildInfoBase&)s))
	{
		LOG_CRI << "FromXML for: SGetGuildInfoBase fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwMaxGuildCount is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwMaxGuildCount") != 0)
	{
		LOG_CRI << "Attribute: name is not dwMaxGuildCount!";
		return false;
	}
	const char* pszVal_dwMaxGuildCount = pElemChild->Attribute("value");
	if(pszVal_dwMaxGuildCount == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwMaxGuildCount, s.dwMaxGuildCount))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwCurGuildCount is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwCurGuildCount") != 0)
	{
		LOG_CRI << "Attribute: name is not dwCurGuildCount!";
		return false;
	}
	const char* pszVal_dwCurGuildCount = pElemChild->Attribute("value");
	if(pszVal_dwCurGuildCount == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwCurGuildCount, s.dwCurGuildCount))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecGuildListInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecGuildListInfo") != 0)
	{
		LOG_CRI << "pElemChild is not TVecGuildListInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecGuildListInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not vecGuildListInfo!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecGuildListInfo))
	{
		LOG_CRI << "VectorFromXML for vecGuildListInfo fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecApplyGuildID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecUINT64") != 0)
	{
		LOG_CRI << "pElemChild is not TVecUINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecApplyGuildID") != 0)
	{
		LOG_CRI << "Attribute: name is not vecApplyGuildID!";
		return false;
	}
	const char* pszText_vecApplyGuildID = pElemChild->GetText();
	if(pszText_vecApplyGuildID != NULL)
		SplitToNumber(pszText_vecApplyGuildID, ",", s.vecApplyGuildID);
	return true;
}

bool ToXML(const SOtherGuildListInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SOtherGuildListInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("没有帮派返回的其他帮派列表信息"));
	unique_ptr<TiXmlElement> pElem_SGetGuildInfoBase(new TiXmlElement("SGetGuildInfoBase"));
	if(pElem_SGetGuildInfoBase == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const SGetGuildInfoBase&)s, *pElem_SGetGuildInfoBase))
	{
		LOG_CRI << "SGetGuildInfoBase ToXML fails!";
		return false;
	}
	pElem_SGetGuildInfoBase->SetAttribute("type", ToUTF8Ptr(""));
	pElem_SGetGuildInfoBase->SetAttribute("comment", ToUTF8Ptr("父类SGetGuildInfoBase部分"));
	if(rElement.LinkEndChild(pElem_SGetGuildInfoBase.get()) != NULL)
		pElem_SGetGuildInfoBase.release();
	unique_ptr<TiXmlElement> pElem_dwMaxGuildCount(new TiXmlElement("UINT32"));
	if(pElem_dwMaxGuildCount == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwMaxGuildCount->SetAttribute("name", "dwMaxGuildCount");
	pElem_dwMaxGuildCount->SetAttribute("value", NumberToString(s.dwMaxGuildCount).c_str());
	pElem_dwMaxGuildCount->SetAttribute("comment", ToUTF8Ptr("最大帮派"));
	if(rElement.LinkEndChild(pElem_dwMaxGuildCount.get()) != NULL)
		pElem_dwMaxGuildCount.release();
	unique_ptr<TiXmlElement> pElem_dwCurGuildCount(new TiXmlElement("UINT32"));
	if(pElem_dwCurGuildCount == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwCurGuildCount->SetAttribute("name", "dwCurGuildCount");
	pElem_dwCurGuildCount->SetAttribute("value", NumberToString(s.dwCurGuildCount).c_str());
	pElem_dwCurGuildCount->SetAttribute("comment", ToUTF8Ptr("当前帮派索引"));
	if(rElement.LinkEndChild(pElem_dwCurGuildCount.get()) != NULL)
		pElem_dwCurGuildCount.release();
	unique_ptr<TiXmlElement> pElem_vecGuildListInfo(new TiXmlElement("TVecGuildListInfo"));
	if(pElem_vecGuildListInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecGuildListInfo->SetAttribute("name", "vecGuildListInfo");
	if(!VectorToXML(s.vecGuildListInfo, *pElem_vecGuildListInfo))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecGuildListInfo->SetAttribute("comment", ToUTF8Ptr("帮派列表信息"));
	if(rElement.LinkEndChild(pElem_vecGuildListInfo.get()) != NULL)
		pElem_vecGuildListInfo.release();
	unique_ptr<TiXmlElement> pElem_vecApplyGuildID(new TiXmlElement("TVecUINT64"));
	if(pElem_vecApplyGuildID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecApplyGuildID->SetAttribute("name", "vecApplyGuildID");
	string strText_vecApplyGuildID;
	for(size_t i = 0; i < s.vecApplyGuildID.size(); ++i)
	{
		if(i > 0)
			strText_vecApplyGuildID += ", ";
		strText_vecApplyGuildID += NumberToString(s.vecApplyGuildID[i]);
	}
	unique_ptr<TiXmlText> pText_vecApplyGuildID(new TiXmlText(strText_vecApplyGuildID.c_str()));
	if(pText_vecApplyGuildID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(pElem_vecApplyGuildID->LinkEndChild(pText_vecApplyGuildID.get()) != NULL)
		pText_vecApplyGuildID.release();
	pElem_vecApplyGuildID->SetAttribute("comment", ToUTF8Ptr("已申请列表帮派ID"));
	if(rElement.LinkEndChild(pElem_vecApplyGuildID.get()) != NULL)
		pElem_vecApplyGuildID.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecOtherGuildListInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SOtherGuildListInfoPtr p(new SOtherGuildListInfo);
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

bool VectorToXML(const TVecOtherGuildListInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SOtherGuildListInfo"));
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

SSelfGuildInfo::SSelfGuildInfo() { }

SSelfGuildInfo::SSelfGuildInfo(SSelfGuildInfo&& src) : SGetGuildInfoBase(src), sAllInfo(move(src.sAllInfo)) { }

SSelfGuildInfo& SSelfGuildInfo::operator=(SSelfGuildInfo&& rhs)
{
	if(this != &rhs)
	{
		this->~SSelfGuildInfo();
		new (this) SSelfGuildInfo(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SSelfGuildInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (SGetGuildInfoBase&)s;
	src >> s.sAllInfo;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SSelfGuildInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const SGetGuildInfoBase&)s;
	src << s.sAllInfo;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SSelfGuildInfo& s)
{
	if(strcmp(rElement.Value(), "SSelfGuildInfo") != 0)
	{
		LOG_CRI << "rElement is not SSelfGuildInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for SGetGuildInfoBase is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (SGetGuildInfoBase&)s))
	{
		LOG_CRI << "FromXML for: SGetGuildInfoBase fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for sAllInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "SGuildAllInfo") != 0)
	{
		LOG_CRI << "pElemChild is not SGuildAllInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "sAllInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not sAllInfo!";
		return false;
	}
	if(!FromXML(*pElemChild, s.sAllInfo))
	{
		LOG_CRI << "FromXML for: sAllInfo fails!";
		return false;
	}
	return true;
}

bool ToXML(const SSelfGuildInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SSelfGuildInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("存在帮派的本帮信息"));
	unique_ptr<TiXmlElement> pElem_SGetGuildInfoBase(new TiXmlElement("SGetGuildInfoBase"));
	if(pElem_SGetGuildInfoBase == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const SGetGuildInfoBase&)s, *pElem_SGetGuildInfoBase))
	{
		LOG_CRI << "SGetGuildInfoBase ToXML fails!";
		return false;
	}
	pElem_SGetGuildInfoBase->SetAttribute("type", ToUTF8Ptr(""));
	pElem_SGetGuildInfoBase->SetAttribute("comment", ToUTF8Ptr("父类SGetGuildInfoBase部分"));
	if(rElement.LinkEndChild(pElem_SGetGuildInfoBase.get()) != NULL)
		pElem_SGetGuildInfoBase.release();
	unique_ptr<TiXmlElement> pElem_sAllInfo(new TiXmlElement("SGuildAllInfo"));
	if(pElem_sAllInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_sAllInfo->SetAttribute("name", "sAllInfo");
	if(!ToXML(s.sAllInfo, *pElem_sAllInfo))
	{
		LOG_CRI << "sAllInfo ToXML fails!";
		return false;
	}
	pElem_sAllInfo->SetAttribute("comment", ToUTF8Ptr("帮派完整信息"));
	if(rElement.LinkEndChild(pElem_sAllInfo.get()) != NULL)
		pElem_sAllInfo.release();
	return true;
}

#endif

SPubGuildAllInfo::SPubGuildAllInfo() { }

SPubGuildAllInfo::SPubGuildAllInfo(const SGuildListInfo& sGuildListInfo_, const SDBGuildBattleInfo& sGuildBattleInfo_) : sGuildListInfo(sGuildListInfo_), sGuildBattleInfo(sGuildBattleInfo_) { }

CInArchive& operator>>(CInArchive& src, SPubGuildAllInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.sGuildListInfo;
	src >> s.sGuildBattleInfo;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SPubGuildAllInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.sGuildListInfo;
	src << s.sGuildBattleInfo;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SPubGuildAllInfo& s)
{
	if(strcmp(rElement.Value(), "SPubGuildAllInfo") != 0)
	{
		LOG_CRI << "rElement is not SPubGuildAllInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for sGuildListInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "SGuildListInfo") != 0)
	{
		LOG_CRI << "pElemChild is not SGuildListInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "sGuildListInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not sGuildListInfo!";
		return false;
	}
	if(!FromXML(*pElemChild, s.sGuildListInfo))
	{
		LOG_CRI << "FromXML for: sGuildListInfo fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for sGuildBattleInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "SDBGuildBattleInfo") != 0)
	{
		LOG_CRI << "pElemChild is not SDBGuildBattleInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "sGuildBattleInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not sGuildBattleInfo!";
		return false;
	}
	if(!FromXML(*pElemChild, s.sGuildBattleInfo))
	{
		LOG_CRI << "FromXML for: sGuildBattleInfo fails!";
		return false;
	}
	return true;
}

bool ToXML(const SPubGuildAllInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SPubGuildAllInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("帮派公共数据（用于服务端读取加载常驻内存的基础数据）"));
	unique_ptr<TiXmlElement> pElem_sGuildListInfo(new TiXmlElement("SGuildListInfo"));
	if(pElem_sGuildListInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_sGuildListInfo->SetAttribute("name", "sGuildListInfo");
	if(!ToXML(s.sGuildListInfo, *pElem_sGuildListInfo))
	{
		LOG_CRI << "sGuildListInfo ToXML fails!";
		return false;
	}
	pElem_sGuildListInfo->SetAttribute("comment", ToUTF8Ptr("帮派列表数据"));
	if(rElement.LinkEndChild(pElem_sGuildListInfo.get()) != NULL)
		pElem_sGuildListInfo.release();
	unique_ptr<TiXmlElement> pElem_sGuildBattleInfo(new TiXmlElement("SDBGuildBattleInfo"));
	if(pElem_sGuildBattleInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_sGuildBattleInfo->SetAttribute("name", "sGuildBattleInfo");
	if(!ToXML(s.sGuildBattleInfo, *pElem_sGuildBattleInfo))
	{
		LOG_CRI << "sGuildBattleInfo ToXML fails!";
		return false;
	}
	pElem_sGuildBattleInfo->SetAttribute("comment", ToUTF8Ptr("帮派战数据"));
	if(rElement.LinkEndChild(pElem_sGuildBattleInfo.get()) != NULL)
		pElem_sGuildBattleInfo.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecPubGuildAllInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SPubGuildAllInfo s;
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

bool VectorToXML(const TVecPubGuildAllInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SPubGuildAllInfo"));
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

STruckInfo::STruckInfo() : byTruckID(0), byStatus(0), byPos(0), byColor(0) { }

STruckInfo::STruckInfo(UINT8 byTruckID_, UINT8 byStatus_, UINT8 byPos_, const std::string& strName_, UINT8 byColor_)
			: byTruckID(byTruckID_), byStatus(byStatus_), byPos(byPos_), strName(strName_), byColor(byColor_) { }

STruckInfo::STruckInfo(STruckInfo&& src) : byTruckID(src.byTruckID), byStatus(src.byStatus), byPos(src.byPos), strName(move(src.strName)), byColor(src.byColor) { }

STruckInfo& STruckInfo::operator=(STruckInfo&& rhs)
{
	if(this != &rhs)
	{
		this->~STruckInfo();
		new (this) STruckInfo(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, STruckInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.byTruckID;
	src >> s.byStatus;
	src >> s.byPos;
	src >> s.strName;
	src >> s.byColor;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const STruckInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.byTruckID;
	src << s.byStatus;
	src << s.byPos;
	src << s.strName;
	src << s.byColor;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, STruckInfo& s)
{
	if(strcmp(rElement.Value(), "STruckInfo") != 0)
	{
		LOG_CRI << "rElement is not STruckInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byTruckID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byTruckID") != 0)
	{
		LOG_CRI << "Attribute: name is not byTruckID!";
		return false;
	}
	const char* pszVal_byTruckID = pElemChild->Attribute("value");
	if(pszVal_byTruckID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byTruckID, s.byTruckID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byStatus is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byStatus") != 0)
	{
		LOG_CRI << "Attribute: name is not byStatus!";
		return false;
	}
	const char* pszVal_byStatus = pElemChild->Attribute("value");
	if(pszVal_byStatus == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byStatus, s.byStatus))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byPos is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byPos") != 0)
	{
		LOG_CRI << "Attribute: name is not byPos!";
		return false;
	}
	const char* pszVal_byPos = pElemChild->Attribute("value");
	if(pszVal_byPos == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byPos, s.byPos))
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
		LOG_CRI << "pElemChild for byColor is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byColor") != 0)
	{
		LOG_CRI << "Attribute: name is not byColor!";
		return false;
	}
	const char* pszVal_byColor = pElemChild->Attribute("value");
	if(pszVal_byColor == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byColor, s.byColor))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const STruckInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("STruckInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("羲和神车的货号信息"));
	unique_ptr<TiXmlElement> pElem_byTruckID(new TiXmlElement("UINT8"));
	if(pElem_byTruckID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byTruckID->SetAttribute("name", "byTruckID");
	pElem_byTruckID->SetAttribute("value", NumberToString(s.byTruckID).c_str());
	pElem_byTruckID->SetAttribute("comment", ToUTF8Ptr("货号id"));
	if(rElement.LinkEndChild(pElem_byTruckID.get()) != NULL)
		pElem_byTruckID.release();
	unique_ptr<TiXmlElement> pElem_byStatus(new TiXmlElement("UINT8"));
	if(pElem_byStatus == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byStatus->SetAttribute("name", "byStatus");
	pElem_byStatus->SetAttribute("value", NumberToString(s.byStatus).c_str());
	pElem_byStatus->SetAttribute("comment", ToUTF8Ptr("EXiheTaskStatus货号状态(0未完成装货 1已请求帮助 2已完成装货)"));
	if(rElement.LinkEndChild(pElem_byStatus.get()) != NULL)
		pElem_byStatus.release();
	unique_ptr<TiXmlElement> pElem_byPos(new TiXmlElement("UINT8"));
	if(pElem_byPos == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byPos->SetAttribute("name", "byPos");
	pElem_byPos->SetAttribute("value", NumberToString(s.byPos).c_str());
	pElem_byPos->SetAttribute("comment", ToUTF8Ptr("货物顺序索引(0~7)"));
	if(rElement.LinkEndChild(pElem_byPos.get()) != NULL)
		pElem_byPos.release();
	unique_ptr<TiXmlElement> pElem_strName(new TiXmlElement("string"));
	if(pElem_strName == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strName->SetAttribute("name", "strName");
	pElem_strName->SetAttribute("value", s.strName.c_str());
	pElem_strName->SetAttribute("comment", ToUTF8Ptr("status为3时,完成装货的玩家名字(注:自己完成为空,不存储)"));
	if(rElement.LinkEndChild(pElem_strName.get()) != NULL)
		pElem_strName.release();
	unique_ptr<TiXmlElement> pElem_byColor(new TiXmlElement("UINT8"));
	if(pElem_byColor == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byColor->SetAttribute("name", "byColor");
	pElem_byColor->SetAttribute("value", NumberToString(s.byColor).c_str());
	pElem_byColor->SetAttribute("comment", ToUTF8Ptr("帮助者玩家颜色"));
	if(rElement.LinkEndChild(pElem_byColor.get()) != NULL)
		pElem_byColor.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecTruckInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		STruckInfo s;
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

bool VectorToXML(const TVecTruckInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("STruckInfo"));
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

SGuildXihe::SGuildXihe() : qwRoleID(0), byStage(0), dwEndTime(0), byRequest(0) { }

SGuildXihe::SGuildXihe(UINT64 qwRoleID_, const TVecTruckInfo& vecTruckInfo_, UINT8 byStage_, UINT32 dwEndTime_, UINT8 byRequest_)
			: qwRoleID(qwRoleID_), vecTruckInfo(vecTruckInfo_), byStage(byStage_), dwEndTime(dwEndTime_), byRequest(byRequest_) { }

SGuildXihe::SGuildXihe(SGuildXihe&& src) : qwRoleID(src.qwRoleID), vecTruckInfo(move(src.vecTruckInfo)), byStage(src.byStage), dwEndTime(src.dwEndTime), byRequest(src.byRequest) { }

SGuildXihe& SGuildXihe::operator=(SGuildXihe&& rhs)
{
	if(this != &rhs)
	{
		this->~SGuildXihe();
		new (this) SGuildXihe(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SGuildXihe& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwRoleID;
	src >> s.vecTruckInfo;
	src >> s.byStage;
	src >> s.dwEndTime;
	src >> s.byRequest;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SGuildXihe& s)
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
	src << s.vecTruckInfo;
	src << s.byStage;
	src << s.dwEndTime;
	src << s.byRequest;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SGuildXihe& s)
{
	if(strcmp(rElement.Value(), "SGuildXihe") != 0)
	{
		LOG_CRI << "rElement is not SGuildXihe!";
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
		LOG_CRI << "pElemChild for vecTruckInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecTruckInfo") != 0)
	{
		LOG_CRI << "pElemChild is not TVecTruckInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecTruckInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not vecTruckInfo!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecTruckInfo))
	{
		LOG_CRI << "VectorFromXML for vecTruckInfo fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byStage is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byStage") != 0)
	{
		LOG_CRI << "Attribute: name is not byStage!";
		return false;
	}
	const char* pszVal_byStage = pElemChild->Attribute("value");
	if(pszVal_byStage == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byStage, s.byStage))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwEndTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwEndTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwEndTime!";
		return false;
	}
	const char* pszVal_dwEndTime = pElemChild->Attribute("value");
	if(pszVal_dwEndTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwEndTime, s.dwEndTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byRequest is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byRequest") != 0)
	{
		LOG_CRI << "Attribute: name is not byRequest!";
		return false;
	}
	const char* pszVal_byRequest = pElemChild->Attribute("value");
	if(pszVal_byRequest == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byRequest, s.byRequest))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SGuildXihe& s, TiXmlElement& rElement)
{
	rElement.SetValue("SGuildXihe");
	rElement.SetAttribute("type", ToUTF8Ptr("玩家羲和神车信息"));
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
	unique_ptr<TiXmlElement> pElem_vecTruckInfo(new TiXmlElement("TVecTruckInfo"));
	if(pElem_vecTruckInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecTruckInfo->SetAttribute("name", "vecTruckInfo");
	if(!VectorToXML(s.vecTruckInfo, *pElem_vecTruckInfo))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecTruckInfo->SetAttribute("comment", ToUTF8Ptr("货号信息"));
	if(rElement.LinkEndChild(pElem_vecTruckInfo.get()) != NULL)
		pElem_vecTruckInfo.release();
	unique_ptr<TiXmlElement> pElem_byStage(new TiXmlElement("UINT8"));
	if(pElem_byStage == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byStage->SetAttribute("name", "byStage");
	pElem_byStage->SetAttribute("value", NumberToString(s.byStage).c_str());
	pElem_byStage->SetAttribute("comment", ToUTF8Ptr("EXiheStage当前阶段(0装货阶段 1任务冷却阶段 2等待玩家接取任务)"));
	if(rElement.LinkEndChild(pElem_byStage.get()) != NULL)
		pElem_byStage.release();
	unique_ptr<TiXmlElement> pElem_dwEndTime(new TiXmlElement("UINT32"));
	if(pElem_dwEndTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwEndTime->SetAttribute("name", "dwEndTime");
	pElem_dwEndTime->SetAttribute("value", NumberToString(s.dwEndTime).c_str());
	pElem_dwEndTime->SetAttribute("comment", ToUTF8Ptr("当前阶段的结束时间"));
	if(rElement.LinkEndChild(pElem_dwEndTime.get()) != NULL)
		pElem_dwEndTime.release();
	unique_ptr<TiXmlElement> pElem_byRequest(new TiXmlElement("UINT8"));
	if(pElem_byRequest == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byRequest->SetAttribute("name", "byRequest");
	pElem_byRequest->SetAttribute("value", NumberToString(s.byRequest).c_str());
	pElem_byRequest->SetAttribute("comment", ToUTF8Ptr("已请求帮助的次数"));
	if(rElement.LinkEndChild(pElem_byRequest.get()) != NULL)
		pElem_byRequest.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecGuildXihe& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SGuildXihe s;
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

bool VectorToXML(const TVecGuildXihe& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SGuildXihe"));
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

SXiheRequest::SXiheRequest() : qwRoleID(0), byReqColor(0), byPos(0), byTruckID(0), bystatus(0), 
			byHelpColor(0) { }

SXiheRequest::SXiheRequest(UINT64 qwRoleID_, const std::string& strName_, UINT8 byReqColor_, UINT8 byPos_, UINT8 byTruckID_, 
			UINT8 bystatus_, const std::string& strHelpName_, UINT8 byHelpColor_)
			: qwRoleID(qwRoleID_), strName(strName_), byReqColor(byReqColor_), byPos(byPos_), byTruckID(byTruckID_), 
			bystatus(bystatus_), strHelpName(strHelpName_), byHelpColor(byHelpColor_) { }

SXiheRequest::SXiheRequest(SXiheRequest&& src) : qwRoleID(src.qwRoleID), strName(move(src.strName)), byReqColor(src.byReqColor), byPos(src.byPos), byTruckID(src.byTruckID), 
			bystatus(src.bystatus), strHelpName(move(src.strHelpName)), byHelpColor(src.byHelpColor) { }

SXiheRequest& SXiheRequest::operator=(SXiheRequest&& rhs)
{
	if(this != &rhs)
	{
		this->~SXiheRequest();
		new (this) SXiheRequest(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SXiheRequest& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwRoleID;
	src >> s.strName;
	src >> s.byReqColor;
	src >> s.byPos;
	src >> s.byTruckID;
	src >> s.bystatus;
	src >> s.strHelpName;
	src >> s.byHelpColor;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SXiheRequest& s)
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
	src << s.byReqColor;
	src << s.byPos;
	src << s.byTruckID;
	src << s.bystatus;
	src << s.strHelpName;
	src << s.byHelpColor;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SXiheRequest& s)
{
	if(strcmp(rElement.Value(), "SXiheRequest") != 0)
	{
		LOG_CRI << "rElement is not SXiheRequest!";
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
		LOG_CRI << "pElemChild for byReqColor is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byReqColor") != 0)
	{
		LOG_CRI << "Attribute: name is not byReqColor!";
		return false;
	}
	const char* pszVal_byReqColor = pElemChild->Attribute("value");
	if(pszVal_byReqColor == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byReqColor, s.byReqColor))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byPos is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byPos") != 0)
	{
		LOG_CRI << "Attribute: name is not byPos!";
		return false;
	}
	const char* pszVal_byPos = pElemChild->Attribute("value");
	if(pszVal_byPos == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byPos, s.byPos))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byTruckID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byTruckID") != 0)
	{
		LOG_CRI << "Attribute: name is not byTruckID!";
		return false;
	}
	const char* pszVal_byTruckID = pElemChild->Attribute("value");
	if(pszVal_byTruckID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byTruckID, s.byTruckID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for bystatus is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "bystatus") != 0)
	{
		LOG_CRI << "Attribute: name is not bystatus!";
		return false;
	}
	const char* pszVal_bystatus = pElemChild->Attribute("value");
	if(pszVal_bystatus == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_bystatus, s.bystatus))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strHelpName is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strHelpName") != 0)
	{
		LOG_CRI << "Attribute: name is not strHelpName!";
		return false;
	}
	const char* pszVal_strHelpName = pElemChild->Attribute("value");
	if(pszVal_strHelpName == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strHelpName = pszVal_strHelpName;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byHelpColor is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byHelpColor") != 0)
	{
		LOG_CRI << "Attribute: name is not byHelpColor!";
		return false;
	}
	const char* pszVal_byHelpColor = pElemChild->Attribute("value");
	if(pszVal_byHelpColor == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byHelpColor, s.byHelpColor))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SXiheRequest& s, TiXmlElement& rElement)
{
	rElement.SetValue("SXiheRequest");
	rElement.SetAttribute("type", ToUTF8Ptr("羲和神车的请求帮助信息"));
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
	pElem_strName->SetAttribute("comment", ToUTF8Ptr("请求玩家的名字"));
	if(rElement.LinkEndChild(pElem_strName.get()) != NULL)
		pElem_strName.release();
	unique_ptr<TiXmlElement> pElem_byReqColor(new TiXmlElement("UINT8"));
	if(pElem_byReqColor == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byReqColor->SetAttribute("name", "byReqColor");
	pElem_byReqColor->SetAttribute("value", NumberToString(s.byReqColor).c_str());
	pElem_byReqColor->SetAttribute("comment", ToUTF8Ptr("请求玩家的名字颜色"));
	if(rElement.LinkEndChild(pElem_byReqColor.get()) != NULL)
		pElem_byReqColor.release();
	unique_ptr<TiXmlElement> pElem_byPos(new TiXmlElement("UINT8"));
	if(pElem_byPos == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byPos->SetAttribute("name", "byPos");
	pElem_byPos->SetAttribute("value", NumberToString(s.byPos).c_str());
	pElem_byPos->SetAttribute("comment", ToUTF8Ptr("货物顺序索引(0~7)"));
	if(rElement.LinkEndChild(pElem_byPos.get()) != NULL)
		pElem_byPos.release();
	unique_ptr<TiXmlElement> pElem_byTruckID(new TiXmlElement("UINT8"));
	if(pElem_byTruckID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byTruckID->SetAttribute("name", "byTruckID");
	pElem_byTruckID->SetAttribute("value", NumberToString(s.byTruckID).c_str());
	pElem_byTruckID->SetAttribute("comment", ToUTF8Ptr("货号ID"));
	if(rElement.LinkEndChild(pElem_byTruckID.get()) != NULL)
		pElem_byTruckID.release();
	unique_ptr<TiXmlElement> pElem_bystatus(new TiXmlElement("UINT8"));
	if(pElem_bystatus == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_bystatus->SetAttribute("name", "bystatus");
	pElem_bystatus->SetAttribute("value", NumberToString(s.bystatus).c_str());
	pElem_bystatus->SetAttribute("comment", ToUTF8Ptr("状态"));
	if(rElement.LinkEndChild(pElem_bystatus.get()) != NULL)
		pElem_bystatus.release();
	unique_ptr<TiXmlElement> pElem_strHelpName(new TiXmlElement("string"));
	if(pElem_strHelpName == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strHelpName->SetAttribute("name", "strHelpName");
	pElem_strHelpName->SetAttribute("value", s.strHelpName.c_str());
	pElem_strHelpName->SetAttribute("comment", ToUTF8Ptr("帮助玩家的名字"));
	if(rElement.LinkEndChild(pElem_strHelpName.get()) != NULL)
		pElem_strHelpName.release();
	unique_ptr<TiXmlElement> pElem_byHelpColor(new TiXmlElement("UINT8"));
	if(pElem_byHelpColor == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byHelpColor->SetAttribute("name", "byHelpColor");
	pElem_byHelpColor->SetAttribute("value", NumberToString(s.byHelpColor).c_str());
	pElem_byHelpColor->SetAttribute("comment", ToUTF8Ptr("帮助者名字颜色"));
	if(rElement.LinkEndChild(pElem_byHelpColor.get()) != NULL)
		pElem_byHelpColor.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecXiheRequest& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SXiheRequest s;
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

bool VectorToXML(const TVecXiheRequest& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SXiheRequest"));
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

SGuildExchangedItem::SGuildExchangedItem() : qwGuildID(0), dwExchangeID(0), dwCount(0) { }

SGuildExchangedItem::SGuildExchangedItem(UINT64 qwGuildID_, UINT32 dwExchangeID_, UINT32 dwCount_) : qwGuildID(qwGuildID_), dwExchangeID(dwExchangeID_), dwCount(dwCount_) { }

CInArchive& operator>>(CInArchive& src, SGuildExchangedItem& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwGuildID;
	src >> s.dwExchangeID;
	src >> s.dwCount;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SGuildExchangedItem& s)
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
	src << s.dwExchangeID;
	src << s.dwCount;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SGuildExchangedItem& s)
{
	if(strcmp(rElement.Value(), "SGuildExchangedItem") != 0)
	{
		LOG_CRI << "rElement is not SGuildExchangedItem!";
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
		LOG_CRI << "pElemChild for dwExchangeID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwExchangeID") != 0)
	{
		LOG_CRI << "Attribute: name is not dwExchangeID!";
		return false;
	}
	const char* pszVal_dwExchangeID = pElemChild->Attribute("value");
	if(pszVal_dwExchangeID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwExchangeID, s.dwExchangeID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwCount is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwCount") != 0)
	{
		LOG_CRI << "Attribute: name is not dwCount!";
		return false;
	}
	const char* pszVal_dwCount = pElemChild->Attribute("value");
	if(pszVal_dwCount == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwCount, s.dwCount))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SGuildExchangedItem& s, TiXmlElement& rElement)
{
	rElement.SetValue("SGuildExchangedItem");
	rElement.SetAttribute("type", ToUTF8Ptr("帮派兑换物品"));
	unique_ptr<TiXmlElement> pElem_qwGuildID(new TiXmlElement("UINT64"));
	if(pElem_qwGuildID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwGuildID->SetAttribute("name", "qwGuildID");
	pElem_qwGuildID->SetAttribute("value", NumberToString(s.qwGuildID).c_str());
	pElem_qwGuildID->SetAttribute("comment", ToUTF8Ptr("帮派唯一ID"));
	if(rElement.LinkEndChild(pElem_qwGuildID.get()) != NULL)
		pElem_qwGuildID.release();
	unique_ptr<TiXmlElement> pElem_dwExchangeID(new TiXmlElement("UINT32"));
	if(pElem_dwExchangeID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwExchangeID->SetAttribute("name", "dwExchangeID");
	pElem_dwExchangeID->SetAttribute("value", NumberToString(s.dwExchangeID).c_str());
	pElem_dwExchangeID->SetAttribute("comment", ToUTF8Ptr("兑换ID"));
	if(rElement.LinkEndChild(pElem_dwExchangeID.get()) != NULL)
		pElem_dwExchangeID.release();
	unique_ptr<TiXmlElement> pElem_dwCount(new TiXmlElement("UINT32"));
	if(pElem_dwCount == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwCount->SetAttribute("name", "dwCount");
	pElem_dwCount->SetAttribute("value", NumberToString(s.dwCount).c_str());
	pElem_dwCount->SetAttribute("comment", ToUTF8Ptr("兑换数量"));
	if(rElement.LinkEndChild(pElem_dwCount.get()) != NULL)
		pElem_dwCount.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecGuildExchangedItem& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SGuildExchangedItem s;
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

bool VectorToXML(const TVecGuildExchangedItem& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SGuildExchangedItem"));
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

} //namespace NGuildProt
