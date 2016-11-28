/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    BattleGS.cpp
//  Purpose:      战斗通信协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "BattleGS.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NBattleGS
{

#ifdef PROT_USE_XML

const char* EnumValToStr(EBStatusType e)
{
	switch(e)
	{
	case EBStatusType_Evade:
		return "EBStatusType_Evade";
	case EBStatusType_Resist:
		return "EBStatusType_Resist";
	case EBStatusType_Immu:
		return "EBStatusType_Immu";
	case EBStatusType_Block:
		return "EBStatusType_Block";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EBStatusType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EBStatusType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("EBStatusType_Evade", EBStatusType_Evade));
		mapStr2Val.insert(make_pair("EBStatusType_Resist", EBStatusType_Resist));
		mapStr2Val.insert(make_pair("EBStatusType_Immu", EBStatusType_Immu));
		mapStr2Val.insert(make_pair("EBStatusType_Block", EBStatusType_Block));
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

const char* EnumValToStr(EBStateBuffType e)
{
	switch(e)
	{
	case EBFBuffTypeNone:
		return "EBFBuffTypeNone";
	case EBFBuffTypeStun:
		return "EBFBuffTypeStun";
	case EBFBuffTypeConfuse:
		return "EBFBuffTypeConfuse";
	case EBFBuffTypeCover:
		return "EBFBuffTypeCover";
	case EBFBuffTypeEShock:
		return "EBFBuffTypeEShock";
	case EBFBuffTypeBlock:
		return "EBFBuffTypeBlock";
	case EBFBuffTypeInvincible:
		return "EBFBuffTypeInvincible";
	case EBFBuffTypeShield:
		return "EBFBuffTypeShield";
	case EBFBuffTypePierce:
		return "EBFBuffTypePierce";
	case EBFBuffTypeBleed:
		return "EBFBuffTypeBleed";
	case EBFBuffTypeForget:
		return "EBFBuffTypeForget";
	case EBFBuffTypeFreeze:
		return "EBFBuffTypeFreeze";
	case EBFBuffTypeBurned:
		return "EBFBuffTypeBurned";
	case EBFBuffTypeAtkAdd:
		return "EBFBuffTypeAtkAdd";
	case EBFBuffTypeAtkSub:
		return "EBFBuffTypeAtkSub";
	case EBFBuffTypeRedAdd:
		return "EBFBuffTypeRedAdd";
	case EBFBuffTypeRedSub:
		return "EBFBuffTypeRedSub";
	case EBFBuffTypeStoned:
		return "EBFBuffTypeStoned";
	case EBFBuffTypePoison:
		return "EBFBuffTypePoison";
	case EBFBuffTypeHide:
		return "EBFBuffTypeHide";
	case EBFBuffTypeBronze:
		return "EBFBuffTypeBronze";
	case EBFBuffTypeKingkong:
		return "EBFBuffTypeKingkong";
	case EBFBuffTypeDmgReduce:
		return "EBFBuffTypeDmgReduce";
	case EBFBuffTypeDmgAdd:
		return "EBFBuffTypeDmgAdd";
	case EBFBuffTypeCongest:
		return "EBFBuffTypeCongest";
	case EBFBuffTypeReflect:
		return "EBFBuffTypeReflect";
	case EBFBuffTypeHitDown:
		return "EBFBuffTypeHitDown";
	case EBFBuffTypeClone:
		return "EBFBuffTypeClone";
	case EBFBuffTypeSealed:
		return "EBFBuffTypeSealed";
	case EBFBuffTypeBeDmgReudce:
		return "EBFBuffTypeBeDmgReudce";
	case EBFBuffTypeBlind:
		return "EBFBuffTypeBlind";
	case EBFBuffTypeSmoke:
		return "EBFBuffTypeSmoke";
	case EBFBuffTypeGuard:
		return "EBFBuffTypeGuard";
	case EBFBuffTypeKindKing:
		return "EBFBuffTypeKindKing";
	case EBFBuffTypeBlunt:
		return "EBFBuffTypeBlunt";
	case EBFBuffTypeIceBlade:
		return "EBFBuffTypeIceBlade";
	case EBFBuffTypeThunderBlade:
		return "EBFBuffTypeThunderBlade";
	case EBFBuffTypeFireBlade:
		return "EBFBuffTypeFireBlade";
	case EBFBuffTypeSnowSoul:
		return "EBFBuffTypeSnowSoul";
	case EBFBuffTypeHaloRed:
		return "EBFBuffTypeHaloRed";
	case EBFBuffTypeHaloBlue:
		return "EBFBuffTypeHaloBlue";
	case EBFBuffTypeDrogenSting:
		return "EBFBuffTypeDrogenSting";
	case EBFBuffTypeDmgShare:
		return "EBFBuffTypeDmgShare";
	case EBFBuffTypeAttrAdd:
		return "EBFBuffTypeAttrAdd";
	case EBFBuffTypeAttrSub:
		return "EBFBuffTypeAttrSub";
	case EBFBuffTypeActAtkAdd:
		return "EBFBuffTypeActAtkAdd";
	case EBFBuffTypeActDefAdd:
		return "EBFBuffTypeActDefAdd";
	case EBFBuffTypeMax:
		return "EBFBuffTypeMax";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EBStateBuffType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EBStateBuffType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("EBFBuffTypeNone", EBFBuffTypeNone));
		mapStr2Val.insert(make_pair("EBFBuffTypeStun", EBFBuffTypeStun));
		mapStr2Val.insert(make_pair("EBFBuffTypeConfuse", EBFBuffTypeConfuse));
		mapStr2Val.insert(make_pair("EBFBuffTypeCover", EBFBuffTypeCover));
		mapStr2Val.insert(make_pair("EBFBuffTypeEShock", EBFBuffTypeEShock));
		mapStr2Val.insert(make_pair("EBFBuffTypeBlock", EBFBuffTypeBlock));
		mapStr2Val.insert(make_pair("EBFBuffTypeInvincible", EBFBuffTypeInvincible));
		mapStr2Val.insert(make_pair("EBFBuffTypeShield", EBFBuffTypeShield));
		mapStr2Val.insert(make_pair("EBFBuffTypePierce", EBFBuffTypePierce));
		mapStr2Val.insert(make_pair("EBFBuffTypeBleed", EBFBuffTypeBleed));
		mapStr2Val.insert(make_pair("EBFBuffTypeForget", EBFBuffTypeForget));
		mapStr2Val.insert(make_pair("EBFBuffTypeFreeze", EBFBuffTypeFreeze));
		mapStr2Val.insert(make_pair("EBFBuffTypeBurned", EBFBuffTypeBurned));
		mapStr2Val.insert(make_pair("EBFBuffTypeAtkAdd", EBFBuffTypeAtkAdd));
		mapStr2Val.insert(make_pair("EBFBuffTypeAtkSub", EBFBuffTypeAtkSub));
		mapStr2Val.insert(make_pair("EBFBuffTypeRedAdd", EBFBuffTypeRedAdd));
		mapStr2Val.insert(make_pair("EBFBuffTypeRedSub", EBFBuffTypeRedSub));
		mapStr2Val.insert(make_pair("EBFBuffTypeStoned", EBFBuffTypeStoned));
		mapStr2Val.insert(make_pair("EBFBuffTypePoison", EBFBuffTypePoison));
		mapStr2Val.insert(make_pair("EBFBuffTypeHide", EBFBuffTypeHide));
		mapStr2Val.insert(make_pair("EBFBuffTypeBronze", EBFBuffTypeBronze));
		mapStr2Val.insert(make_pair("EBFBuffTypeKingkong", EBFBuffTypeKingkong));
		mapStr2Val.insert(make_pair("EBFBuffTypeDmgReduce", EBFBuffTypeDmgReduce));
		mapStr2Val.insert(make_pair("EBFBuffTypeDmgAdd", EBFBuffTypeDmgAdd));
		mapStr2Val.insert(make_pair("EBFBuffTypeCongest", EBFBuffTypeCongest));
		mapStr2Val.insert(make_pair("EBFBuffTypeReflect", EBFBuffTypeReflect));
		mapStr2Val.insert(make_pair("EBFBuffTypeHitDown", EBFBuffTypeHitDown));
		mapStr2Val.insert(make_pair("EBFBuffTypeClone", EBFBuffTypeClone));
		mapStr2Val.insert(make_pair("EBFBuffTypeSealed", EBFBuffTypeSealed));
		mapStr2Val.insert(make_pair("EBFBuffTypeBeDmgReudce", EBFBuffTypeBeDmgReudce));
		mapStr2Val.insert(make_pair("EBFBuffTypeBlind", EBFBuffTypeBlind));
		mapStr2Val.insert(make_pair("EBFBuffTypeSmoke", EBFBuffTypeSmoke));
		mapStr2Val.insert(make_pair("EBFBuffTypeGuard", EBFBuffTypeGuard));
		mapStr2Val.insert(make_pair("EBFBuffTypeKindKing", EBFBuffTypeKindKing));
		mapStr2Val.insert(make_pair("EBFBuffTypeBlunt", EBFBuffTypeBlunt));
		mapStr2Val.insert(make_pair("EBFBuffTypeIceBlade", EBFBuffTypeIceBlade));
		mapStr2Val.insert(make_pair("EBFBuffTypeThunderBlade", EBFBuffTypeThunderBlade));
		mapStr2Val.insert(make_pair("EBFBuffTypeFireBlade", EBFBuffTypeFireBlade));
		mapStr2Val.insert(make_pair("EBFBuffTypeSnowSoul", EBFBuffTypeSnowSoul));
		mapStr2Val.insert(make_pair("EBFBuffTypeHaloRed", EBFBuffTypeHaloRed));
		mapStr2Val.insert(make_pair("EBFBuffTypeHaloBlue", EBFBuffTypeHaloBlue));
		mapStr2Val.insert(make_pair("EBFBuffTypeDrogenSting", EBFBuffTypeDrogenSting));
		mapStr2Val.insert(make_pair("EBFBuffTypeDmgShare", EBFBuffTypeDmgShare));
		mapStr2Val.insert(make_pair("EBFBuffTypeAttrAdd", EBFBuffTypeAttrAdd));
		mapStr2Val.insert(make_pair("EBFBuffTypeAttrSub", EBFBuffTypeAttrSub));
		mapStr2Val.insert(make_pair("EBFBuffTypeActAtkAdd", EBFBuffTypeActAtkAdd));
		mapStr2Val.insert(make_pair("EBFBuffTypeActDefAdd", EBFBuffTypeActDefAdd));
		mapStr2Val.insert(make_pair("EBFBuffTypeMax", EBFBuffTypeMax));
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

const char* EnumValToStr(EBSubHPType e)
{
	switch(e)
	{
	case EBSubHPPhy:
		return "EBSubHPPhy";
	case EBSubHPMgc:
		return "EBSubHPMgc";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EBSubHPType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EBSubHPType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("EBSubHPPhy", EBSubHPPhy));
		mapStr2Val.insert(make_pair("EBSubHPMgc", EBSubHPMgc));
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

const char* EnumValToStr(EBModifyHPType e)
{
	switch(e)
	{
	case EBMODIFYHP_NORMAL:
		return "EBMODIFYHP_NORMAL";
	case EBMODIFYHP_CRITICAL:
		return "EBMODIFYHP_CRITICAL";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EBModifyHPType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EBModifyHPType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("EBMODIFYHP_NORMAL", EBMODIFYHP_NORMAL));
		mapStr2Val.insert(make_pair("EBMODIFYHP_CRITICAL", EBMODIFYHP_CRITICAL));
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

const char* EnumValToStr(EBSheildAbsorbType e)
{
	switch(e)
	{
	case EBSheildAbsorbPhysic:
		return "EBSheildAbsorbPhysic";
	case EBSheildAbsorbMagic:
		return "EBSheildAbsorbMagic";
	case EBSheildAbsorbDamage:
		return "EBSheildAbsorbDamage";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EBSheildAbsorbType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EBSheildAbsorbType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("EBSheildAbsorbPhysic", EBSheildAbsorbPhysic));
		mapStr2Val.insert(make_pair("EBSheildAbsorbMagic", EBSheildAbsorbMagic));
		mapStr2Val.insert(make_pair("EBSheildAbsorbDamage", EBSheildAbsorbDamage));
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

const char* EnumValToStr(ECombineType e)
{
	switch(e)
	{
	case eCTNone:
		return "eCTNone";
	case eCTCritical:
		return "eCTCritical";
	case eCTBlock:
		return "eCTBlock";
	case eCTEvade:
		return "eCTEvade";
	case eCTCounter:
		return "eCTCounter";
	case eCTPeerless:
		return "eCTPeerless";
	case eCTMax:
		return "eCTMax";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, ECombineType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, ECombineType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eCTNone", eCTNone));
		mapStr2Val.insert(make_pair("eCTCritical", eCTCritical));
		mapStr2Val.insert(make_pair("eCTBlock", eCTBlock));
		mapStr2Val.insert(make_pair("eCTEvade", eCTEvade));
		mapStr2Val.insert(make_pair("eCTCounter", eCTCounter));
		mapStr2Val.insert(make_pair("eCTPeerless", eCTPeerless));
		mapStr2Val.insert(make_pair("eCTMax", eCTMax));
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

const char* EnumValToStr(ECombineSlotOPType e)
{
	switch(e)
	{
	case eCSOPTLock:
		return "eCSOPTLock";
	case eCSOPTUnLock:
		return "eCSOPTUnLock";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, ECombineSlotOPType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, ECombineSlotOPType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eCSOPTLock", eCSOPTLock));
		mapStr2Val.insert(make_pair("eCSOPTUnLock", eCSOPTUnLock));
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

const char* EnumValToStr(EBattleResult e)
{
	switch(e)
	{
	case EBResultNone:
		return "EBResultNone";
	case EBResultAttackWin:
		return "EBResultAttackWin";
	case EBResultDefenseWin:
		return "EBResultDefenseWin";
	case EBResultTie:
		return "EBResultTie";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EBattleResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EBattleResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("EBResultNone", EBResultNone));
		mapStr2Val.insert(make_pair("EBResultAttackWin", EBResultAttackWin));
		mapStr2Val.insert(make_pair("EBResultDefenseWin", EBResultDefenseWin));
		mapStr2Val.insert(make_pair("EBResultTie", EBResultTie));
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

const char* EnumValToStr(EBattleType e)
{
	switch(e)
	{
	case EBTINVALID:
		return "EBTINVALID";
	case EBTMonster:
		return "EBTMonster";
	case EBTPlayer:
		return "EBTPlayer";
	case EBWorldBoss:
		return "EBWorldBoss";
	case EBArena:
		return "EBArena";
	case EBDemonTower:
		return "EBDemonTower";
	case ETreasureHunt:
		return "ETreasureHunt";
	case EGuardEMei:
		return "EGuardEMei";
	case EBShip:
		return "EBShip";
	case EBShushan:
		return "EBShushan";
	case EBLingshan:
		return "EBLingshan";
	case EBattleEnd:
		return "EBattleEnd";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EBattleType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EBattleType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("EBTINVALID", EBTINVALID));
		mapStr2Val.insert(make_pair("EBTMonster", EBTMonster));
		mapStr2Val.insert(make_pair("EBTPlayer", EBTPlayer));
		mapStr2Val.insert(make_pair("EBWorldBoss", EBWorldBoss));
		mapStr2Val.insert(make_pair("EBArena", EBArena));
		mapStr2Val.insert(make_pair("EBDemonTower", EBDemonTower));
		mapStr2Val.insert(make_pair("ETreasureHunt", ETreasureHunt));
		mapStr2Val.insert(make_pair("EGuardEMei", EGuardEMei));
		mapStr2Val.insert(make_pair("EBShip", EBShip));
		mapStr2Val.insert(make_pair("EBShushan", EBShushan));
		mapStr2Val.insert(make_pair("EBLingshan", EBLingshan));
		mapStr2Val.insert(make_pair("EBattleEnd", EBattleEnd));
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

const char* EnumValToStr(EBattleReqResult e)
{
	switch(e)
	{
	case EBattleReq_Suc:
		return "EBattleReq_Suc";
	case EBattleReq_CoolDown:
		return "EBattleReq_CoolDown";
	case EBattleReq_Protect:
		return "EBattleReq_Protect";
	case EBattleReq_GuardFirst:
		return "EBattleReq_GuardFirst";
	case EBattleReq_DieCD:
		return "EBattleReq_DieCD";
	case EBattleReq_FieldCoolDown:
		return "EBattleReq_FieldCoolDown";
	case EBattleReq_Level:
		return "EBattleReq_Level";
	case EBattleReq_Other:
		return "EBattleReq_Other";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EBattleReqResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EBattleReqResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("EBattleReq_Suc", EBattleReq_Suc));
		mapStr2Val.insert(make_pair("EBattleReq_CoolDown", EBattleReq_CoolDown));
		mapStr2Val.insert(make_pair("EBattleReq_Protect", EBattleReq_Protect));
		mapStr2Val.insert(make_pair("EBattleReq_GuardFirst", EBattleReq_GuardFirst));
		mapStr2Val.insert(make_pair("EBattleReq_DieCD", EBattleReq_DieCD));
		mapStr2Val.insert(make_pair("EBattleReq_FieldCoolDown", EBattleReq_FieldCoolDown));
		mapStr2Val.insert(make_pair("EBattleReq_Level", EBattleReq_Level));
		mapStr2Val.insert(make_pair("EBattleReq_Other", EBattleReq_Other));
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

const char* GetDescription(EBattleReqResult e)
{
	switch(e)
	{
	case EBattleReq_Suc:
		return "成功";
	case EBattleReq_CoolDown:
		return "您还处在战斗冷却中";
	case EBattleReq_Protect:
		return "对方在战斗保护中";
	case EBattleReq_GuardFirst:
		return "请先去击杀护卫";
	case EBattleReq_DieCD:
		return "死亡冷却中";
	case EBattleReq_FieldCoolDown:
		return "野外战斗冷却中";
	case EBattleReq_Level:
		return "等级不够";
	case EBattleReq_Other:
		return "未知错误";
	default:
		return "未知错误";
	}
}

#ifdef PROT_USE_XML

const char* EnumValToStr(EReportReqResult e)
{
	switch(e)
	{
	case EReportReq_Suc:
		return "EReportReq_Suc";
	case EReportReq_NonExistent:
		return "EReportReq_NonExistent";
	case EReportReq_Other:
		return "EReportReq_Other";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EReportReqResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EReportReqResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("EReportReq_Suc", EReportReq_Suc));
		mapStr2Val.insert(make_pair("EReportReq_NonExistent", EReportReq_NonExistent));
		mapStr2Val.insert(make_pair("EReportReq_Other", EReportReq_Other));
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

const char* GetDescription(EReportReqResult e)
{
	switch(e)
	{
	case EReportReq_Suc:
		return "成功";
	case EReportReq_NonExistent:
		return "请求的战报不存在";
	case EReportReq_Other:
		return "未知错误";
	default:
		return "未知错误";
	}
}

SEquipShowInfo::SEquipShowInfo() : wEquipID(0), byStrengthenLevel(0), byPos(0) { }

SEquipShowInfo::SEquipShowInfo(UINT16 wEquipID_, UINT8 byStrengthenLevel_, UINT8 byPos_) : wEquipID(wEquipID_), byStrengthenLevel(byStrengthenLevel_), byPos(byPos_) { }

CInArchive& operator>>(CInArchive& src, SEquipShowInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.wEquipID;
	src >> s.byStrengthenLevel;
	src >> s.byPos;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SEquipShowInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.wEquipID;
	src << s.byStrengthenLevel;
	src << s.byPos;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SEquipShowInfo& s)
{
	if(strcmp(rElement.Value(), "SEquipShowInfo") != 0)
	{
		LOG_CRI << "rElement is not SEquipShowInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wEquipID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wEquipID") != 0)
	{
		LOG_CRI << "Attribute: name is not wEquipID!";
		return false;
	}
	const char* pszVal_wEquipID = pElemChild->Attribute("value");
	if(pszVal_wEquipID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wEquipID, s.wEquipID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byStrengthenLevel is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byStrengthenLevel") != 0)
	{
		LOG_CRI << "Attribute: name is not byStrengthenLevel!";
		return false;
	}
	const char* pszVal_byStrengthenLevel = pElemChild->Attribute("value");
	if(pszVal_byStrengthenLevel == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byStrengthenLevel, s.byStrengthenLevel))
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
	return true;
}

bool ToXML(const SEquipShowInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SEquipShowInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("发给前端用的显示外形的装备信息"));
	unique_ptr<TiXmlElement> pElem_wEquipID(new TiXmlElement("UINT16"));
	if(pElem_wEquipID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wEquipID->SetAttribute("name", "wEquipID");
	pElem_wEquipID->SetAttribute("value", NumberToString(s.wEquipID).c_str());
	pElem_wEquipID->SetAttribute("comment", ToUTF8Ptr("装备TypeID"));
	if(rElement.LinkEndChild(pElem_wEquipID.get()) != NULL)
		pElem_wEquipID.release();
	unique_ptr<TiXmlElement> pElem_byStrengthenLevel(new TiXmlElement("UINT8"));
	if(pElem_byStrengthenLevel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byStrengthenLevel->SetAttribute("name", "byStrengthenLevel");
	pElem_byStrengthenLevel->SetAttribute("value", NumberToString(s.byStrengthenLevel).c_str());
	pElem_byStrengthenLevel->SetAttribute("comment", ToUTF8Ptr("强化等级"));
	if(rElement.LinkEndChild(pElem_byStrengthenLevel.get()) != NULL)
		pElem_byStrengthenLevel.release();
	unique_ptr<TiXmlElement> pElem_byPos(new TiXmlElement("UINT8"));
	if(pElem_byPos == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byPos->SetAttribute("name", "byPos");
	pElem_byPos->SetAttribute("value", NumberToString(s.byPos).c_str());
	pElem_byPos->SetAttribute("comment", ToUTF8Ptr("装备位置"));
	if(rElement.LinkEndChild(pElem_byPos.get()) != NULL)
		pElem_byPos.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecEquipShowInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SEquipShowInfo s;
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

bool VectorToXML(const TVecEquipShowInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SEquipShowInfo"));
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

STitleAppear::STitleAppear() : byPos(0), wID(0) { }

STitleAppear::STitleAppear(UINT8 byPos_, UINT16 wID_) : byPos(byPos_), wID(wID_) { }

CInArchive& operator>>(CInArchive& src, STitleAppear& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.byPos;
	src >> s.wID;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const STitleAppear& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.byPos;
	src << s.wID;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, STitleAppear& s)
{
	if(strcmp(rElement.Value(), "STitleAppear") != 0)
	{
		LOG_CRI << "rElement is not STitleAppear!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
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
	return true;
}

bool ToXML(const STitleAppear& s, TiXmlElement& rElement)
{
	rElement.SetValue("STitleAppear");
	rElement.SetAttribute("type", ToUTF8Ptr("装备的头衔外观"));
	unique_ptr<TiXmlElement> pElem_byPos(new TiXmlElement("UINT8"));
	if(pElem_byPos == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byPos->SetAttribute("name", "byPos");
	pElem_byPos->SetAttribute("value", NumberToString(s.byPos).c_str());
	pElem_byPos->SetAttribute("comment", ToUTF8Ptr("装备位置"));
	if(rElement.LinkEndChild(pElem_byPos.get()) != NULL)
		pElem_byPos.release();
	unique_ptr<TiXmlElement> pElem_wID(new TiXmlElement("UINT16"));
	if(pElem_wID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wID->SetAttribute("name", "wID");
	pElem_wID->SetAttribute("value", NumberToString(s.wID).c_str());
	pElem_wID->SetAttribute("comment", ToUTF8Ptr("头衔ID"));
	if(rElement.LinkEndChild(pElem_wID.get()) != NULL)
		pElem_wID.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecTitleAppear& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		STitleAppear s;
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

bool VectorToXML(const TVecTitleAppear& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("STitleAppear"));
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

SBattleBuffInfo::SBattleBuffInfo() : wBuffID(0), dwBuffCount(0), dwBuffTime(0) { }

SBattleBuffInfo::SBattleBuffInfo(UINT16 wBuffID_, const TVecUINT32& vecBuffData_, UINT32 dwBuffCount_, UINT32 dwBuffTime_) : wBuffID(wBuffID_), vecBuffData(vecBuffData_), dwBuffCount(dwBuffCount_), dwBuffTime(dwBuffTime_) { }

CInArchive& operator>>(CInArchive& src, SBattleBuffInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.wBuffID;
	src >> s.vecBuffData;
	src >> s.dwBuffCount;
	src >> s.dwBuffTime;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SBattleBuffInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.wBuffID;
	src << s.vecBuffData;
	src << s.dwBuffCount;
	src << s.dwBuffTime;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SBattleBuffInfo& s)
{
	if(strcmp(rElement.Value(), "SBattleBuffInfo") != 0)
	{
		LOG_CRI << "rElement is not SBattleBuffInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wBuffID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wBuffID") != 0)
	{
		LOG_CRI << "Attribute: name is not wBuffID!";
		return false;
	}
	const char* pszVal_wBuffID = pElemChild->Attribute("value");
	if(pszVal_wBuffID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wBuffID, s.wBuffID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecBuffData is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecUINT32") != 0)
	{
		LOG_CRI << "pElemChild is not TVecUINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecBuffData") != 0)
	{
		LOG_CRI << "Attribute: name is not vecBuffData!";
		return false;
	}
	const char* pszText_vecBuffData = pElemChild->GetText();
	if(pszText_vecBuffData != NULL)
		SplitToNumber(pszText_vecBuffData, ",", s.vecBuffData);
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwBuffCount is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwBuffCount") != 0)
	{
		LOG_CRI << "Attribute: name is not dwBuffCount!";
		return false;
	}
	const char* pszVal_dwBuffCount = pElemChild->Attribute("value");
	if(pszVal_dwBuffCount == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwBuffCount, s.dwBuffCount))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwBuffTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwBuffTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwBuffTime!";
		return false;
	}
	const char* pszVal_dwBuffTime = pElemChild->Attribute("value");
	if(pszVal_dwBuffTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwBuffTime, s.dwBuffTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SBattleBuffInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SBattleBuffInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("战斗外的Buff信息"));
	unique_ptr<TiXmlElement> pElem_wBuffID(new TiXmlElement("UINT16"));
	if(pElem_wBuffID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wBuffID->SetAttribute("name", "wBuffID");
	pElem_wBuffID->SetAttribute("value", NumberToString(s.wBuffID).c_str());
	pElem_wBuffID->SetAttribute("comment", ToUTF8Ptr("Buff种类"));
	if(rElement.LinkEndChild(pElem_wBuffID.get()) != NULL)
		pElem_wBuffID.release();
	unique_ptr<TiXmlElement> pElem_vecBuffData(new TiXmlElement("TVecUINT32"));
	if(pElem_vecBuffData == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecBuffData->SetAttribute("name", "vecBuffData");
	string strText_vecBuffData;
	for(size_t i = 0; i < s.vecBuffData.size(); ++i)
	{
		if(i > 0)
			strText_vecBuffData += ", ";
		strText_vecBuffData += NumberToString(s.vecBuffData[i]);
	}
	unique_ptr<TiXmlText> pText_vecBuffData(new TiXmlText(strText_vecBuffData.c_str()));
	if(pText_vecBuffData == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(pElem_vecBuffData->LinkEndChild(pText_vecBuffData.get()) != NULL)
		pText_vecBuffData.release();
	pElem_vecBuffData->SetAttribute("comment", ToUTF8Ptr("Buff数值"));
	if(rElement.LinkEndChild(pElem_vecBuffData.get()) != NULL)
		pElem_vecBuffData.release();
	unique_ptr<TiXmlElement> pElem_dwBuffCount(new TiXmlElement("UINT32"));
	if(pElem_dwBuffCount == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwBuffCount->SetAttribute("name", "dwBuffCount");
	pElem_dwBuffCount->SetAttribute("value", NumberToString(s.dwBuffCount).c_str());
	pElem_dwBuffCount->SetAttribute("comment", ToUTF8Ptr("Buff叠加层数"));
	if(rElement.LinkEndChild(pElem_dwBuffCount.get()) != NULL)
		pElem_dwBuffCount.release();
	unique_ptr<TiXmlElement> pElem_dwBuffTime(new TiXmlElement("UINT32"));
	if(pElem_dwBuffTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwBuffTime->SetAttribute("name", "dwBuffTime");
	pElem_dwBuffTime->SetAttribute("value", NumberToString(s.dwBuffTime).c_str());
	pElem_dwBuffTime->SetAttribute("comment", ToUTF8Ptr("Buff失效时间"));
	if(rElement.LinkEndChild(pElem_dwBuffTime.get()) != NULL)
		pElem_dwBuffTime.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecBattleBuffInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SBattleBuffInfo s;
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

bool VectorToXML(const TVecBattleBuffInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SBattleBuffInfo"));
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

SFeatureBase::SFeatureBase() { }

CInArchive& operator>>(CInArchive& src, SFeatureBase& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.vecBuffID;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SFeatureBase& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.vecBuffID;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, SFeatureBase_Wrapper& rWrapper)
{
	EType_SFeatureBase eType = eType_SFeatureBase;
	src >> (UINT8&)eType;
	switch(eType)
	{
	case eType_SFeatureBase:
		{
			rWrapper.ptr.reset(new SFeatureBase);
			src >> (SFeatureBase&)*rWrapper.ptr;
		}
		break;
	case eType_SMonsterFeature:
		{
			rWrapper.ptr.reset(new SMonsterFeature);
			src >> (SMonsterFeature&)*rWrapper.ptr;
		}
		break;
	case eType_SPlayerFeature:
		{
			rWrapper.ptr.reset(new SPlayerFeature);
			src >> (SPlayerFeature&)*rWrapper.ptr;
		}
		break;
	case eType_SHeroFeature:
		{
			rWrapper.ptr.reset(new SHeroFeature);
			src >> (SHeroFeature&)*rWrapper.ptr;
		}
		break;
	case eType_SFormationFeature:
		{
			rWrapper.ptr.reset(new SFormationFeature);
			src >> (SFormationFeature&)*rWrapper.ptr;
		}
		break;
	case eType_SFieldFeature:
		{
			rWrapper.ptr.reset(new SFieldFeature);
			src >> (SFieldFeature&)*rWrapper.ptr;
		}
		break;
	case eType_SBeautyFeature:
		{
			rWrapper.ptr.reset(new SBeautyFeature);
			src >> (SBeautyFeature&)*rWrapper.ptr;
		}
		break;
	case eType_SPlayerFeatureWithBuff:
		{
			rWrapper.ptr.reset(new SPlayerFeatureWithBuff);
			src >> (SPlayerFeatureWithBuff&)*rWrapper.ptr;
		}
		break;
	case eType_SMonsterFeatureWithBuff:
		{
			rWrapper.ptr.reset(new SMonsterFeatureWithBuff);
			src >> (SMonsterFeatureWithBuff&)*rWrapper.ptr;
		}
		break;
	default:
		throw "Unknown value for EType_SFeatureBase";
		break;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SFeatureBase_Wrapper& rWrapper)
{
	if(rWrapper.ptr != NULL)
	{
		src << (UINT8)rWrapper.ptr->GetClassType();
		switch(rWrapper.ptr->GetClassType())
		{
		case eType_SFeatureBase:
			src << (SFeatureBase&)*rWrapper.ptr;
			break;
		case eType_SMonsterFeature:
			src << (SMonsterFeature&)*rWrapper.ptr;
			break;
		case eType_SPlayerFeature:
			src << (SPlayerFeature&)*rWrapper.ptr;
			break;
		case eType_SHeroFeature:
			src << (SHeroFeature&)*rWrapper.ptr;
			break;
		case eType_SFormationFeature:
			src << (SFormationFeature&)*rWrapper.ptr;
			break;
		case eType_SFieldFeature:
			src << (SFieldFeature&)*rWrapper.ptr;
			break;
		case eType_SBeautyFeature:
			src << (SBeautyFeature&)*rWrapper.ptr;
			break;
		case eType_SPlayerFeatureWithBuff:
			src << (SPlayerFeatureWithBuff&)*rWrapper.ptr;
			break;
		case eType_SMonsterFeatureWithBuff:
			src << (SMonsterFeatureWithBuff&)*rWrapper.ptr;
			break;
		default:
			throw "Unknown value for EType_SFeatureBase";
			break;
		}
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecFeatureBase& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SFeatureBase_Wrapper wrapper;
		src >> wrapper;
		vec[i] = wrapper.ptr;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecFeatureBase& vec)
{
	if(vec.size() > 0x7FFF)
		throw "Vector Size Too Large!";
	UINT16 wSize = (UINT16)vec.size();
	src.WriteContainerSize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SFeatureBase_Wrapper wrapper;
		wrapper.ptr = vec[i];
		src << wrapper;
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SFeatureBase& s)
{
	if(strcmp(rElement.Value(), "SFeatureBase") != 0)
	{
		LOG_CRI << "rElement is not SFeatureBase!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecBuffID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecUINT16") != 0)
	{
		LOG_CRI << "pElemChild is not TVecUINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecBuffID") != 0)
	{
		LOG_CRI << "Attribute: name is not vecBuffID!";
		return false;
	}
	const char* pszText_vecBuffID = pElemChild->GetText();
	if(pszText_vecBuffID != NULL)
		SplitToNumber(pszText_vecBuffID, ",", s.vecBuffID);
	return true;
}

bool ToXML(const SFeatureBase& s, TiXmlElement& rElement)
{
	rElement.SetValue("SFeatureBase");
	rElement.SetAttribute("type", ToUTF8Ptr("外观信息"));
	unique_ptr<TiXmlElement> pElem_vecBuffID(new TiXmlElement("TVecUINT16"));
	if(pElem_vecBuffID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecBuffID->SetAttribute("name", "vecBuffID");
	string strText_vecBuffID;
	for(size_t i = 0; i < s.vecBuffID.size(); ++i)
	{
		if(i > 0)
			strText_vecBuffID += ", ";
		strText_vecBuffID += NumberToString(s.vecBuffID[i]);
	}
	unique_ptr<TiXmlText> pText_vecBuffID(new TiXmlText(strText_vecBuffID.c_str()));
	if(pText_vecBuffID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(pElem_vecBuffID->LinkEndChild(pText_vecBuffID.get()) != NULL)
		pText_vecBuffID.release();
	pElem_vecBuffID->SetAttribute("comment", ToUTF8Ptr("BUffID信息"));
	if(rElement.LinkEndChild(pElem_vecBuffID.get()) != NULL)
		pElem_vecBuffID.release();
	return true;
}

bool SuperFromXML(TiXmlElement& rElement, SFeatureBasePtr& p)
{
	const char* pszName = rElement.Value();
	if(pszName == NULL)
	{
		LOG_CRI << "Element Name is empty!";
		return false;
	}
	if(strcmp(pszName, "SFeatureBase") == 0)
	{
		SFeatureBasePtr pStruct(new SFeatureBase);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SFeatureBase";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SFeatureBase FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SMonsterFeature") == 0)
	{
		SMonsterFeaturePtr pStruct(new SMonsterFeature);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SMonsterFeature";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SMonsterFeature FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SPlayerFeature") == 0)
	{
		SPlayerFeaturePtr pStruct(new SPlayerFeature);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SPlayerFeature";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SPlayerFeature FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SHeroFeature") == 0)
	{
		SHeroFeaturePtr pStruct(new SHeroFeature);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SHeroFeature";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SHeroFeature FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SFormationFeature") == 0)
	{
		SFormationFeaturePtr pStruct(new SFormationFeature);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SFormationFeature";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SFormationFeature FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SFieldFeature") == 0)
	{
		SFieldFeaturePtr pStruct(new SFieldFeature);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SFieldFeature";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SFieldFeature FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SBeautyFeature") == 0)
	{
		SBeautyFeaturePtr pStruct(new SBeautyFeature);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SBeautyFeature";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SBeautyFeature FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SPlayerFeatureWithBuff") == 0)
	{
		SPlayerFeatureWithBuffPtr pStruct(new SPlayerFeatureWithBuff);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SPlayerFeatureWithBuff";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SPlayerFeatureWithBuff FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SMonsterFeatureWithBuff") == 0)
	{
		SMonsterFeatureWithBuffPtr pStruct(new SMonsterFeatureWithBuff);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SMonsterFeatureWithBuff";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SMonsterFeatureWithBuff FromXML fails!";
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

bool SuperToXML(const SFeatureBase& s, TiXmlElement& rElement)
{
	switch(s.GetClassType())
	{
	case eType_SFeatureBase:
		return ToXML((SFeatureBase&)s, rElement);
	case eType_SMonsterFeature:
		return ToXML((SMonsterFeature&)s, rElement);
	case eType_SPlayerFeature:
		return ToXML((SPlayerFeature&)s, rElement);
	case eType_SHeroFeature:
		return ToXML((SHeroFeature&)s, rElement);
	case eType_SFormationFeature:
		return ToXML((SFormationFeature&)s, rElement);
	case eType_SFieldFeature:
		return ToXML((SFieldFeature&)s, rElement);
	case eType_SBeautyFeature:
		return ToXML((SBeautyFeature&)s, rElement);
	case eType_SPlayerFeatureWithBuff:
		return ToXML((SPlayerFeatureWithBuff&)s, rElement);
	case eType_SMonsterFeatureWithBuff:
		return ToXML((SMonsterFeatureWithBuff&)s, rElement);
	default:
		LOG_CRI << "Invalid type: " << s.GetClassType();
		return false;
	}
}

bool VectorFromXML(TiXmlElement& rElement, TVecFeatureBase& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SFeatureBasePtr p;
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

bool VectorToXML(const TVecFeatureBase& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SFeatureBase"));
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

SMonsterFeature::SMonsterFeature() : wMonsterID(0) { }

CInArchive& operator>>(CInArchive& src, SMonsterFeature& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (SFeatureBase&)s;
	src >> s.wMonsterID;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SMonsterFeature& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const SFeatureBase&)s;
	src << s.wMonsterID;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecMonsterFeature& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SMonsterFeaturePtr p(new SMonsterFeature);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecMonsterFeature& vec)
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

bool FromXML(TiXmlElement& rElement, SMonsterFeature& s)
{
	if(strcmp(rElement.Value(), "SMonsterFeature") != 0)
	{
		LOG_CRI << "rElement is not SMonsterFeature!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for SFeatureBase is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (SFeatureBase&)s))
	{
		LOG_CRI << "FromXML for: SFeatureBase fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wMonsterID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wMonsterID") != 0)
	{
		LOG_CRI << "Attribute: name is not wMonsterID!";
		return false;
	}
	const char* pszVal_wMonsterID = pElemChild->Attribute("value");
	if(pszVal_wMonsterID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wMonsterID, s.wMonsterID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SMonsterFeature& s, TiXmlElement& rElement)
{
	rElement.SetValue("SMonsterFeature");
	rElement.SetAttribute("type", ToUTF8Ptr("怪物"));
	unique_ptr<TiXmlElement> pElem_SFeatureBase(new TiXmlElement("SFeatureBase"));
	if(pElem_SFeatureBase == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const SFeatureBase&)s, *pElem_SFeatureBase))
	{
		LOG_CRI << "SFeatureBase ToXML fails!";
		return false;
	}
	pElem_SFeatureBase->SetAttribute("type", ToUTF8Ptr("外观信息"));
	pElem_SFeatureBase->SetAttribute("comment", ToUTF8Ptr("父类SFeatureBase部分"));
	if(rElement.LinkEndChild(pElem_SFeatureBase.get()) != NULL)
		pElem_SFeatureBase.release();
	unique_ptr<TiXmlElement> pElem_wMonsterID(new TiXmlElement("UINT16"));
	if(pElem_wMonsterID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wMonsterID->SetAttribute("name", "wMonsterID");
	pElem_wMonsterID->SetAttribute("value", NumberToString(s.wMonsterID).c_str());
	pElem_wMonsterID->SetAttribute("comment", ToUTF8Ptr("配置表里面的英雄ID，根据ID可以取到怪物外观资源"));
	if(rElement.LinkEndChild(pElem_wMonsterID.get()) != NULL)
		pElem_wMonsterID.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecMonsterFeature& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SMonsterFeaturePtr p(new SMonsterFeature);
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

bool VectorToXML(const TVecMonsterFeature& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SMonsterFeature"));
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

SPlayerFeature::SPlayerFeature() : eJob((NProtoCommon::ECareerType)0), eSex((NProtoCommon::ESexType)0), byQuality(0), byDujieLevel(0), byVIPLevel(0) { }

SPlayerFeature::SPlayerFeature(SPlayerFeature&& src) : SFeatureBase(src), strName(move(src.strName)), eJob(src.eJob), eSex(src.eSex), vEquip(move(src.vEquip)), vecTitle(move(src.vecTitle)), 
			strGuildName(move(src.strGuildName)), byQuality(src.byQuality), byDujieLevel(src.byDujieLevel), byVIPLevel(src.byVIPLevel) { }

SPlayerFeature& SPlayerFeature::operator=(SPlayerFeature&& rhs)
{
	if(this != &rhs)
	{
		this->~SPlayerFeature();
		new (this) SPlayerFeature(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SPlayerFeature& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (SFeatureBase&)s;
	src >> s.strName;
	src >> (UINT8&)s.eJob;
	src >> (UINT8&)s.eSex;
	src >> s.vEquip;
	src >> s.vecTitle;
	src >> s.strGuildName;
	src >> s.byQuality;
	src >> s.byDujieLevel;
	src >> s.byVIPLevel;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SPlayerFeature& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const SFeatureBase&)s;
	src << s.strName;
	src << (UINT8&)s.eJob;
	src << (UINT8&)s.eSex;
	src << s.vEquip;
	src << s.vecTitle;
	src << s.strGuildName;
	src << s.byQuality;
	src << s.byDujieLevel;
	src << s.byVIPLevel;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecPlayerFeature& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SPlayerFeaturePtr p(new SPlayerFeature);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecPlayerFeature& vec)
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

bool FromXML(TiXmlElement& rElement, SPlayerFeature& s)
{
	if(strcmp(rElement.Value(), "SPlayerFeature") != 0)
	{
		LOG_CRI << "rElement is not SPlayerFeature!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for SFeatureBase is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (SFeatureBase&)s))
	{
		LOG_CRI << "FromXML for: SFeatureBase fails!";
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
		LOG_CRI << "pElemChild for vEquip is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecEquipShowInfo") != 0)
	{
		LOG_CRI << "pElemChild is not TVecEquipShowInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vEquip") != 0)
	{
		LOG_CRI << "Attribute: name is not vEquip!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vEquip))
	{
		LOG_CRI << "VectorFromXML for vEquip fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecTitle is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecTitleAppear") != 0)
	{
		LOG_CRI << "pElemChild is not TVecTitleAppear!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecTitle") != 0)
	{
		LOG_CRI << "Attribute: name is not vecTitle!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecTitle))
	{
		LOG_CRI << "VectorFromXML for vecTitle fails!";
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
	return true;
}

bool ToXML(const SPlayerFeature& s, TiXmlElement& rElement)
{
	rElement.SetValue("SPlayerFeature");
	rElement.SetAttribute("type", ToUTF8Ptr("玩家"));
	unique_ptr<TiXmlElement> pElem_SFeatureBase(new TiXmlElement("SFeatureBase"));
	if(pElem_SFeatureBase == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const SFeatureBase&)s, *pElem_SFeatureBase))
	{
		LOG_CRI << "SFeatureBase ToXML fails!";
		return false;
	}
	pElem_SFeatureBase->SetAttribute("type", ToUTF8Ptr("外观信息"));
	pElem_SFeatureBase->SetAttribute("comment", ToUTF8Ptr("父类SFeatureBase部分"));
	if(rElement.LinkEndChild(pElem_SFeatureBase.get()) != NULL)
		pElem_SFeatureBase.release();
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
	unique_ptr<TiXmlElement> pElem_vEquip(new TiXmlElement("TVecEquipShowInfo"));
	if(pElem_vEquip == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vEquip->SetAttribute("name", "vEquip");
	if(!VectorToXML(s.vEquip, *pElem_vEquip))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vEquip->SetAttribute("comment", ToUTF8Ptr("装备"));
	if(rElement.LinkEndChild(pElem_vEquip.get()) != NULL)
		pElem_vEquip.release();
	unique_ptr<TiXmlElement> pElem_vecTitle(new TiXmlElement("TVecTitleAppear"));
	if(pElem_vecTitle == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecTitle->SetAttribute("name", "vecTitle");
	if(!VectorToXML(s.vecTitle, *pElem_vecTitle))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecTitle->SetAttribute("comment", ToUTF8Ptr("头衔"));
	if(rElement.LinkEndChild(pElem_vecTitle.get()) != NULL)
		pElem_vecTitle.release();
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
	unique_ptr<TiXmlElement> pElem_byVIPLevel(new TiXmlElement("UINT8"));
	if(pElem_byVIPLevel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byVIPLevel->SetAttribute("name", "byVIPLevel");
	pElem_byVIPLevel->SetAttribute("value", NumberToString(s.byVIPLevel).c_str());
	pElem_byVIPLevel->SetAttribute("comment", ToUTF8Ptr("VIP等级"));
	if(rElement.LinkEndChild(pElem_byVIPLevel.get()) != NULL)
		pElem_byVIPLevel.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecPlayerFeature& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SPlayerFeaturePtr p(new SPlayerFeature);
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

bool VectorToXML(const TVecPlayerFeature& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SPlayerFeature"));
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

SHeroFeature::SHeroFeature() : wHeroID(0), byQuality(0), byDujieLevel(0) { }

CInArchive& operator>>(CInArchive& src, SHeroFeature& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (SFeatureBase&)s;
	src >> s.wHeroID;
	src >> s.byQuality;
	src >> s.byDujieLevel;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SHeroFeature& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const SFeatureBase&)s;
	src << s.wHeroID;
	src << s.byQuality;
	src << s.byDujieLevel;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecHeroFeature& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SHeroFeaturePtr p(new SHeroFeature);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecHeroFeature& vec)
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

bool FromXML(TiXmlElement& rElement, SHeroFeature& s)
{
	if(strcmp(rElement.Value(), "SHeroFeature") != 0)
	{
		LOG_CRI << "rElement is not SHeroFeature!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for SFeatureBase is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (SFeatureBase&)s))
	{
		LOG_CRI << "FromXML for: SFeatureBase fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wHeroID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wHeroID") != 0)
	{
		LOG_CRI << "Attribute: name is not wHeroID!";
		return false;
	}
	const char* pszVal_wHeroID = pElemChild->Attribute("value");
	if(pszVal_wHeroID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wHeroID, s.wHeroID))
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
	return true;
}

bool ToXML(const SHeroFeature& s, TiXmlElement& rElement)
{
	rElement.SetValue("SHeroFeature");
	rElement.SetAttribute("type", ToUTF8Ptr("散仙"));
	unique_ptr<TiXmlElement> pElem_SFeatureBase(new TiXmlElement("SFeatureBase"));
	if(pElem_SFeatureBase == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const SFeatureBase&)s, *pElem_SFeatureBase))
	{
		LOG_CRI << "SFeatureBase ToXML fails!";
		return false;
	}
	pElem_SFeatureBase->SetAttribute("type", ToUTF8Ptr("外观信息"));
	pElem_SFeatureBase->SetAttribute("comment", ToUTF8Ptr("父类SFeatureBase部分"));
	if(rElement.LinkEndChild(pElem_SFeatureBase.get()) != NULL)
		pElem_SFeatureBase.release();
	unique_ptr<TiXmlElement> pElem_wHeroID(new TiXmlElement("UINT16"));
	if(pElem_wHeroID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wHeroID->SetAttribute("name", "wHeroID");
	pElem_wHeroID->SetAttribute("value", NumberToString(s.wHeroID).c_str());
	pElem_wHeroID->SetAttribute("comment", ToUTF8Ptr("散仙类型"));
	if(rElement.LinkEndChild(pElem_wHeroID.get()) != NULL)
		pElem_wHeroID.release();
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
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecHeroFeature& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SHeroFeaturePtr p(new SHeroFeature);
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

bool VectorToXML(const TVecHeroFeature& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SHeroFeature"));
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

SFormationFeature::SFormationFeature() : wFormationID(0) { }

CInArchive& operator>>(CInArchive& src, SFormationFeature& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (SFeatureBase&)s;
	src >> s.wFormationID;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SFormationFeature& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const SFeatureBase&)s;
	src << s.wFormationID;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecFormationFeature& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SFormationFeaturePtr p(new SFormationFeature);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecFormationFeature& vec)
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

bool FromXML(TiXmlElement& rElement, SFormationFeature& s)
{
	if(strcmp(rElement.Value(), "SFormationFeature") != 0)
	{
		LOG_CRI << "rElement is not SFormationFeature!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for SFeatureBase is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (SFeatureBase&)s))
	{
		LOG_CRI << "FromXML for: SFeatureBase fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wFormationID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wFormationID") != 0)
	{
		LOG_CRI << "Attribute: name is not wFormationID!";
		return false;
	}
	const char* pszVal_wFormationID = pElemChild->Attribute("value");
	if(pszVal_wFormationID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wFormationID, s.wFormationID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SFormationFeature& s, TiXmlElement& rElement)
{
	rElement.SetValue("SFormationFeature");
	rElement.SetAttribute("type", ToUTF8Ptr("阵灵"));
	unique_ptr<TiXmlElement> pElem_SFeatureBase(new TiXmlElement("SFeatureBase"));
	if(pElem_SFeatureBase == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const SFeatureBase&)s, *pElem_SFeatureBase))
	{
		LOG_CRI << "SFeatureBase ToXML fails!";
		return false;
	}
	pElem_SFeatureBase->SetAttribute("type", ToUTF8Ptr("外观信息"));
	pElem_SFeatureBase->SetAttribute("comment", ToUTF8Ptr("父类SFeatureBase部分"));
	if(rElement.LinkEndChild(pElem_SFeatureBase.get()) != NULL)
		pElem_SFeatureBase.release();
	unique_ptr<TiXmlElement> pElem_wFormationID(new TiXmlElement("UINT16"));
	if(pElem_wFormationID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wFormationID->SetAttribute("name", "wFormationID");
	pElem_wFormationID->SetAttribute("value", NumberToString(s.wFormationID).c_str());
	pElem_wFormationID->SetAttribute("comment", ToUTF8Ptr("阵灵配置表ID，同monster"));
	if(rElement.LinkEndChild(pElem_wFormationID.get()) != NULL)
		pElem_wFormationID.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecFormationFeature& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SFormationFeaturePtr p(new SFormationFeature);
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

bool VectorToXML(const TVecFormationFeature& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SFormationFeature"));
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

SFieldFeature::SFieldFeature() : wSceneID(0) { }

CInArchive& operator>>(CInArchive& src, SFieldFeature& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (SFeatureBase&)s;
	src >> s.wSceneID;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SFieldFeature& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const SFeatureBase&)s;
	src << s.wSceneID;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SFieldFeature& s)
{
	if(strcmp(rElement.Value(), "SFieldFeature") != 0)
	{
		LOG_CRI << "rElement is not SFieldFeature!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for SFeatureBase is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (SFeatureBase&)s))
	{
		LOG_CRI << "FromXML for: SFeatureBase fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wSceneID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wSceneID") != 0)
	{
		LOG_CRI << "Attribute: name is not wSceneID!";
		return false;
	}
	const char* pszVal_wSceneID = pElemChild->Attribute("value");
	if(pszVal_wSceneID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wSceneID, s.wSceneID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SFieldFeature& s, TiXmlElement& rElement)
{
	rElement.SetValue("SFieldFeature");
	rElement.SetAttribute("type", ToUTF8Ptr("场景"));
	unique_ptr<TiXmlElement> pElem_SFeatureBase(new TiXmlElement("SFeatureBase"));
	if(pElem_SFeatureBase == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const SFeatureBase&)s, *pElem_SFeatureBase))
	{
		LOG_CRI << "SFeatureBase ToXML fails!";
		return false;
	}
	pElem_SFeatureBase->SetAttribute("type", ToUTF8Ptr("外观信息"));
	pElem_SFeatureBase->SetAttribute("comment", ToUTF8Ptr("父类SFeatureBase部分"));
	if(rElement.LinkEndChild(pElem_SFeatureBase.get()) != NULL)
		pElem_SFeatureBase.release();
	unique_ptr<TiXmlElement> pElem_wSceneID(new TiXmlElement("UINT16"));
	if(pElem_wSceneID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wSceneID->SetAttribute("name", "wSceneID");
	pElem_wSceneID->SetAttribute("value", NumberToString(s.wSceneID).c_str());
	pElem_wSceneID->SetAttribute("comment", ToUTF8Ptr("场景ID"));
	if(rElement.LinkEndChild(pElem_wSceneID.get()) != NULL)
		pElem_wSceneID.release();
	return true;
}

#endif

SBeautyFeature::SBeautyFeature() : wBeautyID(0) { }

CInArchive& operator>>(CInArchive& src, SBeautyFeature& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (SFeatureBase&)s;
	src >> s.wBeautyID;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SBeautyFeature& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const SFeatureBase&)s;
	src << s.wBeautyID;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SBeautyFeature& s)
{
	if(strcmp(rElement.Value(), "SBeautyFeature") != 0)
	{
		LOG_CRI << "rElement is not SBeautyFeature!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for SFeatureBase is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (SFeatureBase&)s))
	{
		LOG_CRI << "FromXML for: SFeatureBase fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wBeautyID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wBeautyID") != 0)
	{
		LOG_CRI << "Attribute: name is not wBeautyID!";
		return false;
	}
	const char* pszVal_wBeautyID = pElemChild->Attribute("value");
	if(pszVal_wBeautyID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wBeautyID, s.wBeautyID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SBeautyFeature& s, TiXmlElement& rElement)
{
	rElement.SetValue("SBeautyFeature");
	rElement.SetAttribute("type", ToUTF8Ptr("美女"));
	unique_ptr<TiXmlElement> pElem_SFeatureBase(new TiXmlElement("SFeatureBase"));
	if(pElem_SFeatureBase == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const SFeatureBase&)s, *pElem_SFeatureBase))
	{
		LOG_CRI << "SFeatureBase ToXML fails!";
		return false;
	}
	pElem_SFeatureBase->SetAttribute("type", ToUTF8Ptr("外观信息"));
	pElem_SFeatureBase->SetAttribute("comment", ToUTF8Ptr("父类SFeatureBase部分"));
	if(rElement.LinkEndChild(pElem_SFeatureBase.get()) != NULL)
		pElem_SFeatureBase.release();
	unique_ptr<TiXmlElement> pElem_wBeautyID(new TiXmlElement("UINT16"));
	if(pElem_wBeautyID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wBeautyID->SetAttribute("name", "wBeautyID");
	pElem_wBeautyID->SetAttribute("value", NumberToString(s.wBeautyID).c_str());
	pElem_wBeautyID->SetAttribute("comment", ToUTF8Ptr("美女ID"));
	if(rElement.LinkEndChild(pElem_wBeautyID.get()) != NULL)
		pElem_wBeautyID.release();
	return true;
}

#endif

SPlayerFeatureWithBuff::SPlayerFeatureWithBuff() : eJob((NProtoCommon::ECareerType)0), eSex((NProtoCommon::ESexType)0), byQuality(0), byDujieLevel(0), byVIPLevel(0) { }

SPlayerFeatureWithBuff::SPlayerFeatureWithBuff(SPlayerFeatureWithBuff&& src) : SFeatureBase(src), strName(move(src.strName)), eJob(src.eJob), eSex(src.eSex), vEquip(move(src.vEquip)), vecTitle(move(src.vecTitle)), 
			strGuildName(move(src.strGuildName)), byQuality(src.byQuality), byDujieLevel(src.byDujieLevel), byVIPLevel(src.byVIPLevel), vecBuffInfo(move(src.vecBuffInfo)) { }

SPlayerFeatureWithBuff& SPlayerFeatureWithBuff::operator=(SPlayerFeatureWithBuff&& rhs)
{
	if(this != &rhs)
	{
		this->~SPlayerFeatureWithBuff();
		new (this) SPlayerFeatureWithBuff(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SPlayerFeatureWithBuff& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (SFeatureBase&)s;
	src >> s.strName;
	src >> (UINT8&)s.eJob;
	src >> (UINT8&)s.eSex;
	src >> s.vEquip;
	src >> s.vecTitle;
	src >> s.strGuildName;
	src >> s.byQuality;
	src >> s.byDujieLevel;
	src >> s.byVIPLevel;
	src >> s.vecBuffInfo;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SPlayerFeatureWithBuff& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const SFeatureBase&)s;
	src << s.strName;
	src << (UINT8&)s.eJob;
	src << (UINT8&)s.eSex;
	src << s.vEquip;
	src << s.vecTitle;
	src << s.strGuildName;
	src << s.byQuality;
	src << s.byDujieLevel;
	src << s.byVIPLevel;
	src << s.vecBuffInfo;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecPlayerFeatureWithBuff& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SPlayerFeatureWithBuffPtr p(new SPlayerFeatureWithBuff);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecPlayerFeatureWithBuff& vec)
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

bool FromXML(TiXmlElement& rElement, SPlayerFeatureWithBuff& s)
{
	if(strcmp(rElement.Value(), "SPlayerFeatureWithBuff") != 0)
	{
		LOG_CRI << "rElement is not SPlayerFeatureWithBuff!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for SFeatureBase is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (SFeatureBase&)s))
	{
		LOG_CRI << "FromXML for: SFeatureBase fails!";
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
		LOG_CRI << "pElemChild for vEquip is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecEquipShowInfo") != 0)
	{
		LOG_CRI << "pElemChild is not TVecEquipShowInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vEquip") != 0)
	{
		LOG_CRI << "Attribute: name is not vEquip!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vEquip))
	{
		LOG_CRI << "VectorFromXML for vEquip fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecTitle is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecTitleAppear") != 0)
	{
		LOG_CRI << "pElemChild is not TVecTitleAppear!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecTitle") != 0)
	{
		LOG_CRI << "Attribute: name is not vecTitle!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecTitle))
	{
		LOG_CRI << "VectorFromXML for vecTitle fails!";
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
		LOG_CRI << "pElemChild for vecBuffInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecBattleBuffInfo") != 0)
	{
		LOG_CRI << "pElemChild is not TVecBattleBuffInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecBuffInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not vecBuffInfo!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecBuffInfo))
	{
		LOG_CRI << "VectorFromXML for vecBuffInfo fails!";
		return false;
	}
	return true;
}

bool ToXML(const SPlayerFeatureWithBuff& s, TiXmlElement& rElement)
{
	rElement.SetValue("SPlayerFeatureWithBuff");
	rElement.SetAttribute("type", ToUTF8Ptr("带Buff的玩家信息"));
	unique_ptr<TiXmlElement> pElem_SFeatureBase(new TiXmlElement("SFeatureBase"));
	if(pElem_SFeatureBase == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const SFeatureBase&)s, *pElem_SFeatureBase))
	{
		LOG_CRI << "SFeatureBase ToXML fails!";
		return false;
	}
	pElem_SFeatureBase->SetAttribute("type", ToUTF8Ptr("外观信息"));
	pElem_SFeatureBase->SetAttribute("comment", ToUTF8Ptr("父类SFeatureBase部分"));
	if(rElement.LinkEndChild(pElem_SFeatureBase.get()) != NULL)
		pElem_SFeatureBase.release();
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
	unique_ptr<TiXmlElement> pElem_vEquip(new TiXmlElement("TVecEquipShowInfo"));
	if(pElem_vEquip == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vEquip->SetAttribute("name", "vEquip");
	if(!VectorToXML(s.vEquip, *pElem_vEquip))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vEquip->SetAttribute("comment", ToUTF8Ptr("装备"));
	if(rElement.LinkEndChild(pElem_vEquip.get()) != NULL)
		pElem_vEquip.release();
	unique_ptr<TiXmlElement> pElem_vecTitle(new TiXmlElement("TVecTitleAppear"));
	if(pElem_vecTitle == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecTitle->SetAttribute("name", "vecTitle");
	if(!VectorToXML(s.vecTitle, *pElem_vecTitle))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecTitle->SetAttribute("comment", ToUTF8Ptr("头衔"));
	if(rElement.LinkEndChild(pElem_vecTitle.get()) != NULL)
		pElem_vecTitle.release();
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
	unique_ptr<TiXmlElement> pElem_byVIPLevel(new TiXmlElement("UINT8"));
	if(pElem_byVIPLevel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byVIPLevel->SetAttribute("name", "byVIPLevel");
	pElem_byVIPLevel->SetAttribute("value", NumberToString(s.byVIPLevel).c_str());
	pElem_byVIPLevel->SetAttribute("comment", ToUTF8Ptr("VIP等级"));
	if(rElement.LinkEndChild(pElem_byVIPLevel.get()) != NULL)
		pElem_byVIPLevel.release();
	unique_ptr<TiXmlElement> pElem_vecBuffInfo(new TiXmlElement("TVecBattleBuffInfo"));
	if(pElem_vecBuffInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecBuffInfo->SetAttribute("name", "vecBuffInfo");
	if(!VectorToXML(s.vecBuffInfo, *pElem_vecBuffInfo))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecBuffInfo->SetAttribute("comment", ToUTF8Ptr("战斗外的Buff信息"));
	if(rElement.LinkEndChild(pElem_vecBuffInfo.get()) != NULL)
		pElem_vecBuffInfo.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecPlayerFeatureWithBuff& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SPlayerFeatureWithBuffPtr p(new SPlayerFeatureWithBuff);
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

bool VectorToXML(const TVecPlayerFeatureWithBuff& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SPlayerFeatureWithBuff"));
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

SMonsterFeatureWithBuff::SMonsterFeatureWithBuff() : wMonsterID(0) { }

SMonsterFeatureWithBuff::SMonsterFeatureWithBuff(SMonsterFeatureWithBuff&& src) : SFeatureBase(src), wMonsterID(src.wMonsterID), vecBuffInfo(move(src.vecBuffInfo)) { }

SMonsterFeatureWithBuff& SMonsterFeatureWithBuff::operator=(SMonsterFeatureWithBuff&& rhs)
{
	if(this != &rhs)
	{
		this->~SMonsterFeatureWithBuff();
		new (this) SMonsterFeatureWithBuff(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SMonsterFeatureWithBuff& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (SFeatureBase&)s;
	src >> s.wMonsterID;
	src >> s.vecBuffInfo;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SMonsterFeatureWithBuff& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const SFeatureBase&)s;
	src << s.wMonsterID;
	src << s.vecBuffInfo;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecMonsterFeatureWithBuff& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SMonsterFeatureWithBuffPtr p(new SMonsterFeatureWithBuff);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecMonsterFeatureWithBuff& vec)
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

bool FromXML(TiXmlElement& rElement, SMonsterFeatureWithBuff& s)
{
	if(strcmp(rElement.Value(), "SMonsterFeatureWithBuff") != 0)
	{
		LOG_CRI << "rElement is not SMonsterFeatureWithBuff!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for SFeatureBase is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (SFeatureBase&)s))
	{
		LOG_CRI << "FromXML for: SFeatureBase fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wMonsterID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wMonsterID") != 0)
	{
		LOG_CRI << "Attribute: name is not wMonsterID!";
		return false;
	}
	const char* pszVal_wMonsterID = pElemChild->Attribute("value");
	if(pszVal_wMonsterID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wMonsterID, s.wMonsterID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecBuffInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecBattleBuffInfo") != 0)
	{
		LOG_CRI << "pElemChild is not TVecBattleBuffInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecBuffInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not vecBuffInfo!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecBuffInfo))
	{
		LOG_CRI << "VectorFromXML for vecBuffInfo fails!";
		return false;
	}
	return true;
}

bool ToXML(const SMonsterFeatureWithBuff& s, TiXmlElement& rElement)
{
	rElement.SetValue("SMonsterFeatureWithBuff");
	rElement.SetAttribute("type", ToUTF8Ptr("带Buff的怪物信息"));
	unique_ptr<TiXmlElement> pElem_SFeatureBase(new TiXmlElement("SFeatureBase"));
	if(pElem_SFeatureBase == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const SFeatureBase&)s, *pElem_SFeatureBase))
	{
		LOG_CRI << "SFeatureBase ToXML fails!";
		return false;
	}
	pElem_SFeatureBase->SetAttribute("type", ToUTF8Ptr("外观信息"));
	pElem_SFeatureBase->SetAttribute("comment", ToUTF8Ptr("父类SFeatureBase部分"));
	if(rElement.LinkEndChild(pElem_SFeatureBase.get()) != NULL)
		pElem_SFeatureBase.release();
	unique_ptr<TiXmlElement> pElem_wMonsterID(new TiXmlElement("UINT16"));
	if(pElem_wMonsterID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wMonsterID->SetAttribute("name", "wMonsterID");
	pElem_wMonsterID->SetAttribute("value", NumberToString(s.wMonsterID).c_str());
	pElem_wMonsterID->SetAttribute("comment", ToUTF8Ptr("配置表里面的英雄ID，根据ID可以取到怪物外观资源"));
	if(rElement.LinkEndChild(pElem_wMonsterID.get()) != NULL)
		pElem_wMonsterID.release();
	unique_ptr<TiXmlElement> pElem_vecBuffInfo(new TiXmlElement("TVecBattleBuffInfo"));
	if(pElem_vecBuffInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecBuffInfo->SetAttribute("name", "vecBuffInfo");
	if(!VectorToXML(s.vecBuffInfo, *pElem_vecBuffInfo))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecBuffInfo->SetAttribute("comment", ToUTF8Ptr("战斗外的Buff信息"));
	if(rElement.LinkEndChild(pElem_vecBuffInfo.get()) != NULL)
		pElem_vecBuffInfo.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecMonsterFeatureWithBuff& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SMonsterFeatureWithBuffPtr p(new SMonsterFeatureWithBuff);
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

bool VectorToXML(const TVecMonsterFeatureWithBuff& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SMonsterFeatureWithBuff"));
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

SBattleFightSkillInfo::SBattleFightSkillInfo() : dwSkillID(0), dwSymboleID(0) { }

SBattleFightSkillInfo::SBattleFightSkillInfo(UINT32 dwSkillID_, UINT32 dwSymboleID_) : dwSkillID(dwSkillID_), dwSymboleID(dwSymboleID_) { }

CInArchive& operator>>(CInArchive& src, SBattleFightSkillInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.dwSkillID;
	src >> s.dwSymboleID;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SBattleFightSkillInfo& s)
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
	src << s.dwSymboleID;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SBattleFightSkillInfo& s)
{
	if(strcmp(rElement.Value(), "SBattleFightSkillInfo") != 0)
	{
		LOG_CRI << "rElement is not SBattleFightSkillInfo!";
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
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwSymboleID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwSymboleID") != 0)
	{
		LOG_CRI << "Attribute: name is not dwSymboleID!";
		return false;
	}
	const char* pszVal_dwSymboleID = pElemChild->Attribute("value");
	if(pszVal_dwSymboleID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwSymboleID, s.dwSymboleID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SBattleFightSkillInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SBattleFightSkillInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("参与战斗的技能信息"));
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
	unique_ptr<TiXmlElement> pElem_dwSymboleID(new TiXmlElement("UINT32"));
	if(pElem_dwSymboleID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwSymboleID->SetAttribute("name", "dwSymboleID");
	pElem_dwSymboleID->SetAttribute("value", NumberToString(s.dwSymboleID).c_str());
	pElem_dwSymboleID->SetAttribute("comment", ToUTF8Ptr("符文ID"));
	if(rElement.LinkEndChild(pElem_dwSymboleID.get()) != NULL)
		pElem_dwSymboleID.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecFightSkillInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SBattleFightSkillInfo s;
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
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SBattleFightSkillInfo"));
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

STeamSkillInfo::STeamSkillInfo() : byIndex(0), byTeamID(0), dwSkillID(0) { }

STeamSkillInfo::STeamSkillInfo(UINT8 byIndex_, UINT8 byTeamID_, UINT32 dwSkillID_) : byIndex(byIndex_), byTeamID(byTeamID_), dwSkillID(dwSkillID_) { }

CInArchive& operator>>(CInArchive& src, STeamSkillInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.byIndex;
	src >> s.byTeamID;
	src >> s.dwSkillID;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const STeamSkillInfo& s)
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
	src << s.byTeamID;
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

bool FromXML(TiXmlElement& rElement, STeamSkillInfo& s)
{
	if(strcmp(rElement.Value(), "STeamSkillInfo") != 0)
	{
		LOG_CRI << "rElement is not STeamSkillInfo!";
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
		LOG_CRI << "pElemChild for byTeamID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byTeamID") != 0)
	{
		LOG_CRI << "Attribute: name is not byTeamID!";
		return false;
	}
	const char* pszVal_byTeamID = pElemChild->Attribute("value");
	if(pszVal_byTeamID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byTeamID, s.byTeamID))
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

bool ToXML(const STeamSkillInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("STeamSkillInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("队伍技能"));
	unique_ptr<TiXmlElement> pElem_byIndex(new TiXmlElement("UINT8"));
	if(pElem_byIndex == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byIndex->SetAttribute("name", "byIndex");
	pElem_byIndex->SetAttribute("value", NumberToString(s.byIndex).c_str());
	pElem_byIndex->SetAttribute("comment", ToUTF8Ptr("队伍技能唯一编号"));
	if(rElement.LinkEndChild(pElem_byIndex.get()) != NULL)
		pElem_byIndex.release();
	unique_ptr<TiXmlElement> pElem_byTeamID(new TiXmlElement("UINT8"));
	if(pElem_byTeamID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byTeamID->SetAttribute("name", "byTeamID");
	pElem_byTeamID->SetAttribute("value", NumberToString(s.byTeamID).c_str());
	pElem_byTeamID->SetAttribute("comment", ToUTF8Ptr("队伍ID"));
	if(rElement.LinkEndChild(pElem_byTeamID.get()) != NULL)
		pElem_byTeamID.release();
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

bool VectorFromXML(TiXmlElement& rElement, TVecTeamSkillInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		STeamSkillInfo s;
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

bool VectorToXML(const TVecTeamSkillInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("STeamSkillInfo"));
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

SBattleFighterInfo::SBattleFighterInfo() : qwInstID(0), wFighterID(0), iPos(0), byTeamID(0), byLevel(0), 
			eSex((NProtoCommon::ESexType)0), eCareer((NProtoCommon::ECareerType)0), dwHpMax(0), dwHp(0), dwAura(0), 
			dwAuraMax(0) { }

CInArchive& operator>>(CInArchive& src, SBattleFighterInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	SFeatureBase_Wrapper pFeature_Wrapper;
	src >> s.qwInstID;
	src >> s.wFighterID;
	src >> s.iPos;
	src >> s.byTeamID;
	src >> s.byLevel;
	src >> s.strName;
	src >> (UINT8&)s.eSex;
	src >> (UINT8&)s.eCareer;
	src >> s.dwHpMax;
	src >> s.dwHp;
	src >> s.dwAura;
	src >> s.dwAuraMax;
	src >> s.oAttrVec;
	src >> s.vActiveSkill;
	src >> s.vPassiveSkill;
	src >> s.oPeerLees;
	src >> s.oPeerLeesEx;
	src >> pFeature_Wrapper;
	s.pFeature = pFeature_Wrapper.ptr;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SBattleFighterInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	SFeatureBase_Wrapper pFeature_Wrapper(s.pFeature);
	src << s.qwInstID;
	src << s.wFighterID;
	src << s.iPos;
	src << s.byTeamID;
	src << s.byLevel;
	src << s.strName;
	src << (UINT8&)s.eSex;
	src << (UINT8&)s.eCareer;
	src << s.dwHpMax;
	src << s.dwHp;
	src << s.dwAura;
	src << s.dwAuraMax;
	src << s.oAttrVec;
	src << s.vActiveSkill;
	src << s.vPassiveSkill;
	src << s.oPeerLees;
	src << s.oPeerLeesEx;
	src << pFeature_Wrapper;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SBattleFighterInfo& s)
{
	if(strcmp(rElement.Value(), "SBattleFighterInfo") != 0)
	{
		LOG_CRI << "rElement is not SBattleFighterInfo!";
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
		LOG_CRI << "pElemChild for byTeamID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byTeamID") != 0)
	{
		LOG_CRI << "Attribute: name is not byTeamID!";
		return false;
	}
	const char* pszVal_byTeamID = pElemChild->Attribute("value");
	if(pszVal_byTeamID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byTeamID, s.byTeamID))
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
		LOG_CRI << "pElemChild for eCareer is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "ProtoCommon::ECareerType") != 0)
	{
		LOG_CRI << "pElemChild is not ProtoCommon::ECareerType!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eCareer") != 0)
	{
		LOG_CRI << "Attribute: name is not eCareer!";
		return false;
	}
	const char* pszVal_eCareer = pElemChild->Attribute("value");
	if(pszVal_eCareer == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!NProtoCommon::EnumStrToVal(pszVal_eCareer, s.eCareer))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
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
	if(strcmp(pElemChild->Value(), "SBattleFightSkillInfo") != 0)
	{
		LOG_CRI << "pElemChild is not SBattleFightSkillInfo!";
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
		LOG_CRI << "pElemChild for oPeerLeesEx is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "SBattleFightSkillInfo") != 0)
	{
		LOG_CRI << "pElemChild is not SBattleFightSkillInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "oPeerLeesEx") != 0)
	{
		LOG_CRI << "Attribute: name is not oPeerLeesEx!";
		return false;
	}
	if(!FromXML(*pElemChild, s.oPeerLeesEx))
	{
		LOG_CRI << "FromXML for: oPeerLeesEx fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for pFeature is empty!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "pFeature") != 0)
	{
		LOG_CRI << "Attribute: name is not pFeature!";
		return false;
	}
	if(!SuperFromXML(*pElemChild, s.pFeature))
	{
		LOG_CRI << "FromXML for: pFeature fails!";
		return false;
	}
	return true;
}

bool ToXML(const SBattleFighterInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SBattleFighterInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("战斗者信息"));
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
	unique_ptr<TiXmlElement> pElem_iPos(new TiXmlElement("INT32"));
	if(pElem_iPos == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_iPos->SetAttribute("name", "iPos");
	pElem_iPos->SetAttribute("value", NumberToString(s.iPos).c_str());
	pElem_iPos->SetAttribute("comment", ToUTF8Ptr("将位置"));
	if(rElement.LinkEndChild(pElem_iPos.get()) != NULL)
		pElem_iPos.release();
	unique_ptr<TiXmlElement> pElem_byTeamID(new TiXmlElement("UINT8"));
	if(pElem_byTeamID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byTeamID->SetAttribute("name", "byTeamID");
	pElem_byTeamID->SetAttribute("value", NumberToString(s.byTeamID).c_str());
	pElem_byTeamID->SetAttribute("comment", ToUTF8Ptr("所属队伍ID"));
	if(rElement.LinkEndChild(pElem_byTeamID.get()) != NULL)
		pElem_byTeamID.release();
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
	pElem_eSex->SetAttribute("comment", ToUTF8Ptr("将性别"));
	if(rElement.LinkEndChild(pElem_eSex.get()) != NULL)
		pElem_eSex.release();
	unique_ptr<TiXmlElement> pElem_eCareer(new TiXmlElement("ProtoCommon::ECareerType"));
	if(pElem_eCareer == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eCareer->SetAttribute("name", "eCareer");
	const char* pszEnum_eCareer = NProtoCommon::EnumValToStr(s.eCareer);
	if(pszEnum_eCareer == NULL)
	{
		LOG_CRI << "EnumValToStr for eCareer fails!";
		return false;
	}
	pElem_eCareer->SetAttribute("value", pszEnum_eCareer);
	pElem_eCareer->SetAttribute("comment", ToUTF8Ptr("将职业"));
	if(rElement.LinkEndChild(pElem_eCareer.get()) != NULL)
		pElem_eCareer.release();
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
	pElem_oAttrVec->SetAttribute("comment", ToUTF8Ptr("最终属性"));
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
	unique_ptr<TiXmlElement> pElem_oPeerLees(new TiXmlElement("SBattleFightSkillInfo"));
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
	unique_ptr<TiXmlElement> pElem_oPeerLeesEx(new TiXmlElement("SBattleFightSkillInfo"));
	if(pElem_oPeerLeesEx == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_oPeerLeesEx->SetAttribute("name", "oPeerLeesEx");
	if(!ToXML(s.oPeerLeesEx, *pElem_oPeerLeesEx))
	{
		LOG_CRI << "oPeerLeesEx ToXML fails!";
		return false;
	}
	pElem_oPeerLeesEx->SetAttribute("comment", ToUTF8Ptr("变身后无双技能"));
	if(rElement.LinkEndChild(pElem_oPeerLeesEx.get()) != NULL)
		pElem_oPeerLeesEx.release();
	unique_ptr<TiXmlElement> pElem_pFeature(new TiXmlElement("SFeatureBase"));
	if(pElem_pFeature == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_pFeature->SetAttribute("name", "pFeature");
	if(s.pFeature == NULL)
	{
		LOG_CRI << "pFeature is NULL!";
		return false;
	}
	if(!SuperToXML(*s.pFeature, *pElem_pFeature))
	{
		LOG_CRI << "pFeature SuperToXML fails!";
		return false;
	}
	pElem_pFeature->SetAttribute("comment", ToUTF8Ptr("外观信息"));
	if(rElement.LinkEndChild(pElem_pFeature.get()) != NULL)
		pElem_pFeature.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecFighterInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SBattleFighterInfo s;
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
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SBattleFighterInfo"));
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

SBattleFighter::SBattleFighter() : byFighterID(0) { }

SBattleFighter::SBattleFighter(UINT8 byFighterID_, const SBattleFighterInfo& oFgtInfo_) : byFighterID(byFighterID_), oFgtInfo(oFgtInfo_) { }

CInArchive& operator>>(CInArchive& src, SBattleFighter& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.byFighterID;
	src >> s.oFgtInfo;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SBattleFighter& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.byFighterID;
	src << s.oFgtInfo;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SBattleFighter& s)
{
	if(strcmp(rElement.Value(), "SBattleFighter") != 0)
	{
		LOG_CRI << "rElement is not SBattleFighter!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byFighterID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byFighterID") != 0)
	{
		LOG_CRI << "Attribute: name is not byFighterID!";
		return false;
	}
	const char* pszVal_byFighterID = pElemChild->Attribute("value");
	if(pszVal_byFighterID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byFighterID, s.byFighterID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for oFgtInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "SBattleFighterInfo") != 0)
	{
		LOG_CRI << "pElemChild is not SBattleFighterInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "oFgtInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not oFgtInfo!";
		return false;
	}
	if(!FromXML(*pElemChild, s.oFgtInfo))
	{
		LOG_CRI << "FromXML for: oFgtInfo fails!";
		return false;
	}
	return true;
}

bool ToXML(const SBattleFighter& s, TiXmlElement& rElement)
{
	rElement.SetValue("SBattleFighter");
	rElement.SetAttribute("type", ToUTF8Ptr("Fighter信息"));
	unique_ptr<TiXmlElement> pElem_byFighterID(new TiXmlElement("UINT8"));
	if(pElem_byFighterID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byFighterID->SetAttribute("name", "byFighterID");
	pElem_byFighterID->SetAttribute("value", NumberToString(s.byFighterID).c_str());
	pElem_byFighterID->SetAttribute("comment", ToUTF8Ptr("战场开始之后分配的唯一ID，groupID*5*5+pos"));
	if(rElement.LinkEndChild(pElem_byFighterID.get()) != NULL)
		pElem_byFighterID.release();
	unique_ptr<TiXmlElement> pElem_oFgtInfo(new TiXmlElement("SBattleFighterInfo"));
	if(pElem_oFgtInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_oFgtInfo->SetAttribute("name", "oFgtInfo");
	if(!ToXML(s.oFgtInfo, *pElem_oFgtInfo))
	{
		LOG_CRI << "oFgtInfo ToXML fails!";
		return false;
	}
	pElem_oFgtInfo->SetAttribute("comment", ToUTF8Ptr("FighterInfo"));
	if(rElement.LinkEndChild(pElem_oFgtInfo.get()) != NULL)
		pElem_oFgtInfo.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecBattleFighter& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SBattleFighter s;
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

bool VectorToXML(const TVecBattleFighter& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SBattleFighter"));
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

SBattleGroup::SBattleGroup() : byGroupID(0), qwCreatrueID(0), qwLeaderID(0), wLevel(0), dwBattlePoint(0) { }

CInArchive& operator>>(CInArchive& src, SBattleGroup& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	SFeatureBase_Wrapper pMainFeature_Wrapper;
	src >> s.byGroupID;
	src >> s.qwCreatrueID;
	src >> s.qwLeaderID;
	src >> s.wLevel;
	src >> s.vFighters;
	src >> s.vecCombineSkillInfo;
	src >> pMainFeature_Wrapper;
	src >> s.dwBattlePoint;
	s.pMainFeature = pMainFeature_Wrapper.ptr;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SBattleGroup& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	SFeatureBase_Wrapper pMainFeature_Wrapper(s.pMainFeature);
	src << s.byGroupID;
	src << s.qwCreatrueID;
	src << s.qwLeaderID;
	src << s.wLevel;
	src << s.vFighters;
	src << s.vecCombineSkillInfo;
	src << pMainFeature_Wrapper;
	src << s.dwBattlePoint;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SBattleGroup& s)
{
	if(strcmp(rElement.Value(), "SBattleGroup") != 0)
	{
		LOG_CRI << "rElement is not SBattleGroup!";
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
		LOG_CRI << "pElemChild for qwCreatrueID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwCreatrueID") != 0)
	{
		LOG_CRI << "Attribute: name is not qwCreatrueID!";
		return false;
	}
	const char* pszVal_qwCreatrueID = pElemChild->Attribute("value");
	if(pszVal_qwCreatrueID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwCreatrueID, s.qwCreatrueID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwLeaderID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwLeaderID") != 0)
	{
		LOG_CRI << "Attribute: name is not qwLeaderID!";
		return false;
	}
	const char* pszVal_qwLeaderID = pElemChild->Attribute("value");
	if(pszVal_qwLeaderID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwLeaderID, s.qwLeaderID))
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
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vFighters is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecBattleFighter") != 0)
	{
		LOG_CRI << "pElemChild is not TVecBattleFighter!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vFighters") != 0)
	{
		LOG_CRI << "Attribute: name is not vFighters!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vFighters))
	{
		LOG_CRI << "VectorFromXML for vFighters fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecCombineSkillInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecTeamSkillInfo") != 0)
	{
		LOG_CRI << "pElemChild is not TVecTeamSkillInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecCombineSkillInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not vecCombineSkillInfo!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecCombineSkillInfo))
	{
		LOG_CRI << "VectorFromXML for vecCombineSkillInfo fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for pMainFeature is empty!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "pMainFeature") != 0)
	{
		LOG_CRI << "Attribute: name is not pMainFeature!";
		return false;
	}
	if(!SuperFromXML(*pElemChild, s.pMainFeature))
	{
		LOG_CRI << "FromXML for: pMainFeature fails!";
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

bool ToXML(const SBattleGroup& s, TiXmlElement& rElement)
{
	rElement.SetValue("SBattleGroup");
	rElement.SetAttribute("type", ToUTF8Ptr("战斗小队"));
	unique_ptr<TiXmlElement> pElem_byGroupID(new TiXmlElement("UINT8"));
	if(pElem_byGroupID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byGroupID->SetAttribute("name", "byGroupID");
	pElem_byGroupID->SetAttribute("value", NumberToString(s.byGroupID).c_str());
	pElem_byGroupID->SetAttribute("comment", ToUTF8Ptr("组ID"));
	if(rElement.LinkEndChild(pElem_byGroupID.get()) != NULL)
		pElem_byGroupID.release();
	unique_ptr<TiXmlElement> pElem_qwCreatrueID(new TiXmlElement("UINT64"));
	if(pElem_qwCreatrueID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwCreatrueID->SetAttribute("name", "qwCreatrueID");
	pElem_qwCreatrueID->SetAttribute("value", NumberToString(s.qwCreatrueID).c_str());
	pElem_qwCreatrueID->SetAttribute("comment", ToUTF8Ptr("玩家ID，地图上跑的时候用的那个ID，怪物为0"));
	if(rElement.LinkEndChild(pElem_qwCreatrueID.get()) != NULL)
		pElem_qwCreatrueID.release();
	unique_ptr<TiXmlElement> pElem_qwLeaderID(new TiXmlElement("UINT64"));
	if(pElem_qwLeaderID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwLeaderID->SetAttribute("name", "qwLeaderID");
	pElem_qwLeaderID->SetAttribute("value", NumberToString(s.qwLeaderID).c_str());
	pElem_qwLeaderID->SetAttribute("comment", ToUTF8Ptr("队伍主将ID"));
	if(rElement.LinkEndChild(pElem_qwLeaderID.get()) != NULL)
		pElem_qwLeaderID.release();
	unique_ptr<TiXmlElement> pElem_wLevel(new TiXmlElement("UINT16"));
	if(pElem_wLevel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wLevel->SetAttribute("name", "wLevel");
	pElem_wLevel->SetAttribute("value", NumberToString(s.wLevel).c_str());
	pElem_wLevel->SetAttribute("comment", ToUTF8Ptr("队伍等级"));
	if(rElement.LinkEndChild(pElem_wLevel.get()) != NULL)
		pElem_wLevel.release();
	unique_ptr<TiXmlElement> pElem_vFighters(new TiXmlElement("TVecBattleFighter"));
	if(pElem_vFighters == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vFighters->SetAttribute("name", "vFighters");
	if(!VectorToXML(s.vFighters, *pElem_vFighters))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vFighters->SetAttribute("comment", ToUTF8Ptr("队伍里面的所有fighter"));
	if(rElement.LinkEndChild(pElem_vFighters.get()) != NULL)
		pElem_vFighters.release();
	unique_ptr<TiXmlElement> pElem_vecCombineSkillInfo(new TiXmlElement("TVecTeamSkillInfo"));
	if(pElem_vecCombineSkillInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecCombineSkillInfo->SetAttribute("name", "vecCombineSkillInfo");
	if(!VectorToXML(s.vecCombineSkillInfo, *pElem_vecCombineSkillInfo))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecCombineSkillInfo->SetAttribute("comment", ToUTF8Ptr("队伍中的连携技能"));
	if(rElement.LinkEndChild(pElem_vecCombineSkillInfo.get()) != NULL)
		pElem_vecCombineSkillInfo.release();
	unique_ptr<TiXmlElement> pElem_pMainFeature(new TiXmlElement("SFeatureBase"));
	if(pElem_pMainFeature == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_pMainFeature->SetAttribute("name", "pMainFeature");
	if(s.pMainFeature == NULL)
	{
		LOG_CRI << "pMainFeature is NULL!";
		return false;
	}
	if(!SuperToXML(*s.pMainFeature, *pElem_pMainFeature))
	{
		LOG_CRI << "pMainFeature SuperToXML fails!";
		return false;
	}
	pElem_pMainFeature->SetAttribute("comment", ToUTF8Ptr("主将外观信息(用于显示头像用)"));
	if(rElement.LinkEndChild(pElem_pMainFeature.get()) != NULL)
		pElem_pMainFeature.release();
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

bool VectorFromXML(TiXmlElement& rElement, TVecBattleGroup& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SBattleGroup s;
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

bool VectorToXML(const TVecBattleGroup& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SBattleGroup"));
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

SEffectBase::SEffectBase() { }

CInArchive& operator>>(CInArchive& src, SEffectBase& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.vecFighterID;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SEffectBase& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.vecFighterID;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, SEffectBase_Wrapper& rWrapper)
{
	EType_SEffectBase eType = eType_SEffectBase;
	src >> (UINT8&)eType;
	switch(eType)
	{
	case eType_SEffectBase:
		{
			rWrapper.ptr.reset(new SEffectBase);
			src >> (SEffectBase&)*rWrapper.ptr;
		}
		break;
	case eType_SEffectDecHP:
		{
			rWrapper.ptr.reset(new SEffectDecHP);
			src >> (SEffectDecHP&)*rWrapper.ptr;
		}
		break;
	case eType_SEffectAddStatus:
		{
			rWrapper.ptr.reset(new SEffectAddStatus);
			src >> (SEffectAddStatus&)*rWrapper.ptr;
		}
		break;
	case eType_SEffectAddHP:
		{
			rWrapper.ptr.reset(new SEffectAddHP);
			src >> (SEffectAddHP&)*rWrapper.ptr;
		}
		break;
	case eType_SEffectRelive:
		{
			rWrapper.ptr.reset(new SEffectRelive);
			src >> (SEffectRelive&)*rWrapper.ptr;
		}
		break;
	case eType_SEffectCounter:
		{
			rWrapper.ptr.reset(new SEffectCounter);
			src >> (SEffectCounter&)*rWrapper.ptr;
		}
		break;
	case eType_SEffectStateBuffAdd:
		{
			rWrapper.ptr.reset(new SEffectStateBuffAdd);
			src >> (SEffectStateBuffAdd&)*rWrapper.ptr;
		}
		break;
	case eType_SEffectStateBuffEffect:
		{
			rWrapper.ptr.reset(new SEffectStateBuffEffect);
			src >> (SEffectStateBuffEffect&)*rWrapper.ptr;
		}
		break;
	case eType_SEffectStateBuffDec:
		{
			rWrapper.ptr.reset(new SEffectStateBuffDec);
			src >> (SEffectStateBuffDec&)*rWrapper.ptr;
		}
		break;
	case eType_SEffectStateBuffLast:
		{
			rWrapper.ptr.reset(new SEffectStateBuffLast);
			src >> (SEffectStateBuffLast&)*rWrapper.ptr;
		}
		break;
	case eType_SEffectAttrBuffAdd:
		{
			rWrapper.ptr.reset(new SEffectAttrBuffAdd);
			src >> (SEffectAttrBuffAdd&)*rWrapper.ptr;
		}
		break;
	case eType_SEffectAttrBuffDec:
		{
			rWrapper.ptr.reset(new SEffectAttrBuffDec);
			src >> (SEffectAttrBuffDec&)*rWrapper.ptr;
		}
		break;
	case eType_SEffectDied:
		{
			rWrapper.ptr.reset(new SEffectDied);
			src >> (SEffectDied&)*rWrapper.ptr;
		}
		break;
	case eType_SEffectShieldAbsorb:
		{
			rWrapper.ptr.reset(new SEffectShieldAbsorb);
			src >> (SEffectShieldAbsorb&)*rWrapper.ptr;
		}
		break;
	case eType_SEffectTriggerExecute:
		{
			rWrapper.ptr.reset(new SEffectTriggerExecute);
			src >> (SEffectTriggerExecute&)*rWrapper.ptr;
		}
		break;
	case eType_SEffectSycHP:
		{
			rWrapper.ptr.reset(new SEffectSycHP);
			src >> (SEffectSycHP&)*rWrapper.ptr;
		}
		break;
	case eType_SEffectSycAura:
		{
			rWrapper.ptr.reset(new SEffectSycAura);
			src >> (SEffectSycAura&)*rWrapper.ptr;
		}
		break;
	case eType_SEffectSycCombine:
		{
			rWrapper.ptr.reset(new SEffectSycCombine);
			src >> (SEffectSycCombine&)*rWrapper.ptr;
		}
		break;
	case eType_SEffectCombineSlot:
		{
			rWrapper.ptr.reset(new SEffectCombineSlot);
			src >> (SEffectCombineSlot&)*rWrapper.ptr;
		}
		break;
	case eType_SEffectBrokenShield:
		{
			rWrapper.ptr.reset(new SEffectBrokenShield);
			src >> (SEffectBrokenShield&)*rWrapper.ptr;
		}
		break;
	case eType_SEffectSummon:
		{
			rWrapper.ptr.reset(new SEffectSummon);
			src >> (SEffectSummon&)*rWrapper.ptr;
		}
		break;
	case eType_SEffectDialog:
		{
			rWrapper.ptr.reset(new SEffectDialog);
			src >> (SEffectDialog&)*rWrapper.ptr;
		}
		break;
	case eType_SEffectTransform:
		{
			rWrapper.ptr.reset(new SEffectTransform);
			src >> (SEffectTransform&)*rWrapper.ptr;
		}
		break;
	case eType_SEffectPartBroken:
		{
			rWrapper.ptr.reset(new SEffectPartBroken);
			src >> (SEffectPartBroken&)*rWrapper.ptr;
		}
		break;
	case eType_SEffectBuffAction:
		{
			rWrapper.ptr.reset(new SEffectBuffAction);
			src >> (SEffectBuffAction&)*rWrapper.ptr;
		}
		break;
	default:
		throw "Unknown value for EType_SEffectBase";
		break;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SEffectBase_Wrapper& rWrapper)
{
	if(rWrapper.ptr != NULL)
	{
		src << (UINT8)rWrapper.ptr->GetClassType();
		switch(rWrapper.ptr->GetClassType())
		{
		case eType_SEffectBase:
			src << (SEffectBase&)*rWrapper.ptr;
			break;
		case eType_SEffectDecHP:
			src << (SEffectDecHP&)*rWrapper.ptr;
			break;
		case eType_SEffectAddStatus:
			src << (SEffectAddStatus&)*rWrapper.ptr;
			break;
		case eType_SEffectAddHP:
			src << (SEffectAddHP&)*rWrapper.ptr;
			break;
		case eType_SEffectRelive:
			src << (SEffectRelive&)*rWrapper.ptr;
			break;
		case eType_SEffectCounter:
			src << (SEffectCounter&)*rWrapper.ptr;
			break;
		case eType_SEffectStateBuffAdd:
			src << (SEffectStateBuffAdd&)*rWrapper.ptr;
			break;
		case eType_SEffectStateBuffEffect:
			src << (SEffectStateBuffEffect&)*rWrapper.ptr;
			break;
		case eType_SEffectStateBuffDec:
			src << (SEffectStateBuffDec&)*rWrapper.ptr;
			break;
		case eType_SEffectStateBuffLast:
			src << (SEffectStateBuffLast&)*rWrapper.ptr;
			break;
		case eType_SEffectAttrBuffAdd:
			src << (SEffectAttrBuffAdd&)*rWrapper.ptr;
			break;
		case eType_SEffectAttrBuffDec:
			src << (SEffectAttrBuffDec&)*rWrapper.ptr;
			break;
		case eType_SEffectDied:
			src << (SEffectDied&)*rWrapper.ptr;
			break;
		case eType_SEffectShieldAbsorb:
			src << (SEffectShieldAbsorb&)*rWrapper.ptr;
			break;
		case eType_SEffectTriggerExecute:
			src << (SEffectTriggerExecute&)*rWrapper.ptr;
			break;
		case eType_SEffectSycHP:
			src << (SEffectSycHP&)*rWrapper.ptr;
			break;
		case eType_SEffectSycAura:
			src << (SEffectSycAura&)*rWrapper.ptr;
			break;
		case eType_SEffectSycCombine:
			src << (SEffectSycCombine&)*rWrapper.ptr;
			break;
		case eType_SEffectCombineSlot:
			src << (SEffectCombineSlot&)*rWrapper.ptr;
			break;
		case eType_SEffectBrokenShield:
			src << (SEffectBrokenShield&)*rWrapper.ptr;
			break;
		case eType_SEffectSummon:
			src << (SEffectSummon&)*rWrapper.ptr;
			break;
		case eType_SEffectDialog:
			src << (SEffectDialog&)*rWrapper.ptr;
			break;
		case eType_SEffectTransform:
			src << (SEffectTransform&)*rWrapper.ptr;
			break;
		case eType_SEffectPartBroken:
			src << (SEffectPartBroken&)*rWrapper.ptr;
			break;
		case eType_SEffectBuffAction:
			src << (SEffectBuffAction&)*rWrapper.ptr;
			break;
		default:
			throw "Unknown value for EType_SEffectBase";
			break;
		}
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecEffects& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SEffectBase_Wrapper wrapper;
		src >> wrapper;
		vec[i] = wrapper.ptr;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecEffects& vec)
{
	if(vec.size() > 0x7FFF)
		throw "Vector Size Too Large!";
	UINT16 wSize = (UINT16)vec.size();
	src.WriteContainerSize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SEffectBase_Wrapper wrapper;
		wrapper.ptr = vec[i];
		src << wrapper;
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SEffectBase& s)
{
	if(strcmp(rElement.Value(), "SEffectBase") != 0)
	{
		LOG_CRI << "rElement is not SEffectBase!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecFighterID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecUINT8") != 0)
	{
		LOG_CRI << "pElemChild is not TVecUINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecFighterID") != 0)
	{
		LOG_CRI << "Attribute: name is not vecFighterID!";
		return false;
	}
	const char* pszText_vecFighterID = pElemChild->GetText();
	if(pszText_vecFighterID != NULL)
		SplitToNumber(pszText_vecFighterID, ",", s.vecFighterID);
	return true;
}

bool ToXML(const SEffectBase& s, TiXmlElement& rElement)
{
	rElement.SetValue("SEffectBase");
	rElement.SetAttribute("type", ToUTF8Ptr("战斗基础效果类型"));
	unique_ptr<TiXmlElement> pElem_vecFighterID(new TiXmlElement("TVecUINT8"));
	if(pElem_vecFighterID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecFighterID->SetAttribute("name", "vecFighterID");
	string strText_vecFighterID;
	for(size_t i = 0; i < s.vecFighterID.size(); ++i)
	{
		if(i > 0)
			strText_vecFighterID += ", ";
		strText_vecFighterID += NumberToString(s.vecFighterID[i]);
	}
	unique_ptr<TiXmlText> pText_vecFighterID(new TiXmlText(strText_vecFighterID.c_str()));
	if(pText_vecFighterID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(pElem_vecFighterID->LinkEndChild(pText_vecFighterID.get()) != NULL)
		pText_vecFighterID.release();
	pElem_vecFighterID->SetAttribute("comment", ToUTF8Ptr("表现这个效果的fighter(255表示为场景)"));
	if(rElement.LinkEndChild(pElem_vecFighterID.get()) != NULL)
		pElem_vecFighterID.release();
	return true;
}

bool SuperFromXML(TiXmlElement& rElement, SEffectBasePtr& p)
{
	const char* pszName = rElement.Value();
	if(pszName == NULL)
	{
		LOG_CRI << "Element Name is empty!";
		return false;
	}
	if(strcmp(pszName, "SEffectBase") == 0)
	{
		SEffectBasePtr pStruct(new SEffectBase);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SEffectBase";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SEffectBase FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SEffectDecHP") == 0)
	{
		SEffectDecHPPtr pStruct(new SEffectDecHP);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SEffectDecHP";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SEffectDecHP FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SEffectAddStatus") == 0)
	{
		SEffectAddStatusPtr pStruct(new SEffectAddStatus);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SEffectAddStatus";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SEffectAddStatus FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SEffectAddHP") == 0)
	{
		SEffectAddHPPtr pStruct(new SEffectAddHP);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SEffectAddHP";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SEffectAddHP FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SEffectRelive") == 0)
	{
		SEffectRelivePtr pStruct(new SEffectRelive);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SEffectRelive";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SEffectRelive FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SEffectCounter") == 0)
	{
		SEffectCounterPtr pStruct(new SEffectCounter);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SEffectCounter";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SEffectCounter FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SEffectStateBuffAdd") == 0)
	{
		SEffectStateBuffAddPtr pStruct(new SEffectStateBuffAdd);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SEffectStateBuffAdd";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SEffectStateBuffAdd FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SEffectStateBuffEffect") == 0)
	{
		SEffectStateBuffEffectPtr pStruct(new SEffectStateBuffEffect);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SEffectStateBuffEffect";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SEffectStateBuffEffect FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SEffectStateBuffDec") == 0)
	{
		SEffectStateBuffDecPtr pStruct(new SEffectStateBuffDec);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SEffectStateBuffDec";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SEffectStateBuffDec FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SEffectStateBuffLast") == 0)
	{
		SEffectStateBuffLastPtr pStruct(new SEffectStateBuffLast);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SEffectStateBuffLast";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SEffectStateBuffLast FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SEffectAttrBuffAdd") == 0)
	{
		SEffectAttrBuffAddPtr pStruct(new SEffectAttrBuffAdd);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SEffectAttrBuffAdd";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SEffectAttrBuffAdd FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SEffectAttrBuffDec") == 0)
	{
		SEffectAttrBuffDecPtr pStruct(new SEffectAttrBuffDec);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SEffectAttrBuffDec";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SEffectAttrBuffDec FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SEffectDied") == 0)
	{
		SEffectDiedPtr pStruct(new SEffectDied);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SEffectDied";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SEffectDied FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SEffectShieldAbsorb") == 0)
	{
		SEffectShieldAbsorbPtr pStruct(new SEffectShieldAbsorb);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SEffectShieldAbsorb";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SEffectShieldAbsorb FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SEffectTriggerExecute") == 0)
	{
		SEffectTriggerExecutePtr pStruct(new SEffectTriggerExecute);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SEffectTriggerExecute";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SEffectTriggerExecute FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SEffectSycHP") == 0)
	{
		SEffectSycHPPtr pStruct(new SEffectSycHP);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SEffectSycHP";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SEffectSycHP FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SEffectSycAura") == 0)
	{
		SEffectSycAuraPtr pStruct(new SEffectSycAura);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SEffectSycAura";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SEffectSycAura FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SEffectSycCombine") == 0)
	{
		SEffectSycCombinePtr pStruct(new SEffectSycCombine);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SEffectSycCombine";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SEffectSycCombine FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SEffectCombineSlot") == 0)
	{
		SEffectCombineSlotPtr pStruct(new SEffectCombineSlot);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SEffectCombineSlot";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SEffectCombineSlot FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SEffectBrokenShield") == 0)
	{
		SEffectBrokenShieldPtr pStruct(new SEffectBrokenShield);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SEffectBrokenShield";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SEffectBrokenShield FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SEffectSummon") == 0)
	{
		SEffectSummonPtr pStruct(new SEffectSummon);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SEffectSummon";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SEffectSummon FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SEffectDialog") == 0)
	{
		SEffectDialogPtr pStruct(new SEffectDialog);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SEffectDialog";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SEffectDialog FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SEffectTransform") == 0)
	{
		SEffectTransformPtr pStruct(new SEffectTransform);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SEffectTransform";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SEffectTransform FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SEffectPartBroken") == 0)
	{
		SEffectPartBrokenPtr pStruct(new SEffectPartBroken);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SEffectPartBroken";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SEffectPartBroken FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SEffectBuffAction") == 0)
	{
		SEffectBuffActionPtr pStruct(new SEffectBuffAction);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SEffectBuffAction";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SEffectBuffAction FromXML fails!";
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

bool SuperToXML(const SEffectBase& s, TiXmlElement& rElement)
{
	switch(s.GetClassType())
	{
	case eType_SEffectBase:
		return ToXML((SEffectBase&)s, rElement);
	case eType_SEffectDecHP:
		return ToXML((SEffectDecHP&)s, rElement);
	case eType_SEffectAddStatus:
		return ToXML((SEffectAddStatus&)s, rElement);
	case eType_SEffectAddHP:
		return ToXML((SEffectAddHP&)s, rElement);
	case eType_SEffectRelive:
		return ToXML((SEffectRelive&)s, rElement);
	case eType_SEffectCounter:
		return ToXML((SEffectCounter&)s, rElement);
	case eType_SEffectStateBuffAdd:
		return ToXML((SEffectStateBuffAdd&)s, rElement);
	case eType_SEffectStateBuffEffect:
		return ToXML((SEffectStateBuffEffect&)s, rElement);
	case eType_SEffectStateBuffDec:
		return ToXML((SEffectStateBuffDec&)s, rElement);
	case eType_SEffectStateBuffLast:
		return ToXML((SEffectStateBuffLast&)s, rElement);
	case eType_SEffectAttrBuffAdd:
		return ToXML((SEffectAttrBuffAdd&)s, rElement);
	case eType_SEffectAttrBuffDec:
		return ToXML((SEffectAttrBuffDec&)s, rElement);
	case eType_SEffectDied:
		return ToXML((SEffectDied&)s, rElement);
	case eType_SEffectShieldAbsorb:
		return ToXML((SEffectShieldAbsorb&)s, rElement);
	case eType_SEffectTriggerExecute:
		return ToXML((SEffectTriggerExecute&)s, rElement);
	case eType_SEffectSycHP:
		return ToXML((SEffectSycHP&)s, rElement);
	case eType_SEffectSycAura:
		return ToXML((SEffectSycAura&)s, rElement);
	case eType_SEffectSycCombine:
		return ToXML((SEffectSycCombine&)s, rElement);
	case eType_SEffectCombineSlot:
		return ToXML((SEffectCombineSlot&)s, rElement);
	case eType_SEffectBrokenShield:
		return ToXML((SEffectBrokenShield&)s, rElement);
	case eType_SEffectSummon:
		return ToXML((SEffectSummon&)s, rElement);
	case eType_SEffectDialog:
		return ToXML((SEffectDialog&)s, rElement);
	case eType_SEffectTransform:
		return ToXML((SEffectTransform&)s, rElement);
	case eType_SEffectPartBroken:
		return ToXML((SEffectPartBroken&)s, rElement);
	case eType_SEffectBuffAction:
		return ToXML((SEffectBuffAction&)s, rElement);
	default:
		LOG_CRI << "Invalid type: " << s.GetClassType();
		return false;
	}
}

bool VectorFromXML(TiXmlElement& rElement, TVecEffects& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SEffectBasePtr p;
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

bool VectorToXML(const TVecEffects& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SEffectBase"));
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

SEffectDecHP::SEffectDecHP() : dwSkillID(0), eSubHPType((EBSubHPType)0), eHPType((EBModifyHPType)0), dwDecHP(0) { }

CInArchive& operator>>(CInArchive& src, SEffectDecHP& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (SEffectBase&)s;
	src >> s.dwSkillID;
	src >> (UINT8&)s.eSubHPType;
	src >> (UINT8&)s.eHPType;
	src >> s.dwDecHP;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SEffectDecHP& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const SEffectBase&)s;
	src << s.dwSkillID;
	src << (UINT8&)s.eSubHPType;
	src << (UINT8&)s.eHPType;
	src << s.dwDecHP;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecDecHP& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SEffectDecHPPtr p(new SEffectDecHP);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecDecHP& vec)
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

bool FromXML(TiXmlElement& rElement, SEffectDecHP& s)
{
	if(strcmp(rElement.Value(), "SEffectDecHP") != 0)
	{
		LOG_CRI << "rElement is not SEffectDecHP!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for SEffectBase is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (SEffectBase&)s))
	{
		LOG_CRI << "FromXML for: SEffectBase fails!";
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
		LOG_CRI << "pElemChild for eSubHPType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "EBSubHPType") != 0)
	{
		LOG_CRI << "pElemChild is not EBSubHPType!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eSubHPType") != 0)
	{
		LOG_CRI << "Attribute: name is not eSubHPType!";
		return false;
	}
	const char* pszVal_eSubHPType = pElemChild->Attribute("value");
	if(pszVal_eSubHPType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!EnumStrToVal(pszVal_eSubHPType, s.eSubHPType))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eHPType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "EBModifyHPType") != 0)
	{
		LOG_CRI << "pElemChild is not EBModifyHPType!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eHPType") != 0)
	{
		LOG_CRI << "Attribute: name is not eHPType!";
		return false;
	}
	const char* pszVal_eHPType = pElemChild->Attribute("value");
	if(pszVal_eHPType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!EnumStrToVal(pszVal_eHPType, s.eHPType))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwDecHP is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwDecHP") != 0)
	{
		LOG_CRI << "Attribute: name is not dwDecHP!";
		return false;
	}
	const char* pszVal_dwDecHP = pElemChild->Attribute("value");
	if(pszVal_dwDecHP == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwDecHP, s.dwDecHP))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SEffectDecHP& s, TiXmlElement& rElement)
{
	rElement.SetValue("SEffectDecHP");
	rElement.SetAttribute("type", ToUTF8Ptr("扣血"));
	unique_ptr<TiXmlElement> pElem_SEffectBase(new TiXmlElement("SEffectBase"));
	if(pElem_SEffectBase == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const SEffectBase&)s, *pElem_SEffectBase))
	{
		LOG_CRI << "SEffectBase ToXML fails!";
		return false;
	}
	pElem_SEffectBase->SetAttribute("type", ToUTF8Ptr("战斗基础效果类型"));
	pElem_SEffectBase->SetAttribute("comment", ToUTF8Ptr("父类SEffectBase部分"));
	if(rElement.LinkEndChild(pElem_SEffectBase.get()) != NULL)
		pElem_SEffectBase.release();
	unique_ptr<TiXmlElement> pElem_dwSkillID(new TiXmlElement("UINT32"));
	if(pElem_dwSkillID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwSkillID->SetAttribute("name", "dwSkillID");
	pElem_dwSkillID->SetAttribute("value", NumberToString(s.dwSkillID).c_str());
	pElem_dwSkillID->SetAttribute("comment", ToUTF8Ptr("扣血对应ID"));
	if(rElement.LinkEndChild(pElem_dwSkillID.get()) != NULL)
		pElem_dwSkillID.release();
	unique_ptr<TiXmlElement> pElem_eSubHPType(new TiXmlElement("EBSubHPType"));
	if(pElem_eSubHPType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eSubHPType->SetAttribute("name", "eSubHPType");
	const char* pszEnum_eSubHPType = EnumValToStr(s.eSubHPType);
	if(pszEnum_eSubHPType == NULL)
	{
		LOG_CRI << "EnumValToStr for EBSubHPType fails!";
		return false;
	}
	pElem_eSubHPType->SetAttribute("value", pszEnum_eSubHPType);
	pElem_eSubHPType->SetAttribute("comment", ToUTF8Ptr("扣血伤害类型（物理/法术）"));
	if(rElement.LinkEndChild(pElem_eSubHPType.get()) != NULL)
		pElem_eSubHPType.release();
	unique_ptr<TiXmlElement> pElem_eHPType(new TiXmlElement("EBModifyHPType"));
	if(pElem_eHPType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eHPType->SetAttribute("name", "eHPType");
	const char* pszEnum_eHPType = EnumValToStr(s.eHPType);
	if(pszEnum_eHPType == NULL)
	{
		LOG_CRI << "EnumValToStr for EBModifyHPType fails!";
		return false;
	}
	pElem_eHPType->SetAttribute("value", pszEnum_eHPType);
	pElem_eHPType->SetAttribute("comment", ToUTF8Ptr("扣血类型"));
	if(rElement.LinkEndChild(pElem_eHPType.get()) != NULL)
		pElem_eHPType.release();
	unique_ptr<TiXmlElement> pElem_dwDecHP(new TiXmlElement("UINT32"));
	if(pElem_dwDecHP == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwDecHP->SetAttribute("name", "dwDecHP");
	pElem_dwDecHP->SetAttribute("value", NumberToString(s.dwDecHP).c_str());
	pElem_dwDecHP->SetAttribute("comment", ToUTF8Ptr("扣掉的血"));
	if(rElement.LinkEndChild(pElem_dwDecHP.get()) != NULL)
		pElem_dwDecHP.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecDecHP& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SEffectDecHPPtr p(new SEffectDecHP);
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

bool VectorToXML(const TVecDecHP& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SEffectDecHP"));
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

SEffectAddStatus::SEffectAddStatus() : eStatus((EBStatusType)0) { }

CInArchive& operator>>(CInArchive& src, SEffectAddStatus& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (SEffectBase&)s;
	src >> (UINT8&)s.eStatus;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SEffectAddStatus& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const SEffectBase&)s;
	src << (UINT8&)s.eStatus;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecAddStatus& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SEffectAddStatusPtr p(new SEffectAddStatus);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecAddStatus& vec)
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

bool FromXML(TiXmlElement& rElement, SEffectAddStatus& s)
{
	if(strcmp(rElement.Value(), "SEffectAddStatus") != 0)
	{
		LOG_CRI << "rElement is not SEffectAddStatus!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for SEffectBase is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (SEffectBase&)s))
	{
		LOG_CRI << "FromXML for: SEffectBase fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eStatus is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "EBStatusType") != 0)
	{
		LOG_CRI << "pElemChild is not EBStatusType!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eStatus") != 0)
	{
		LOG_CRI << "Attribute: name is not eStatus!";
		return false;
	}
	const char* pszVal_eStatus = pElemChild->Attribute("value");
	if(pszVal_eStatus == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!EnumStrToVal(pszVal_eStatus, s.eStatus))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SEffectAddStatus& s, TiXmlElement& rElement)
{
	rElement.SetValue("SEffectAddStatus");
	rElement.SetAttribute("type", ToUTF8Ptr("一个UINT32参数的效果"));
	unique_ptr<TiXmlElement> pElem_SEffectBase(new TiXmlElement("SEffectBase"));
	if(pElem_SEffectBase == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const SEffectBase&)s, *pElem_SEffectBase))
	{
		LOG_CRI << "SEffectBase ToXML fails!";
		return false;
	}
	pElem_SEffectBase->SetAttribute("type", ToUTF8Ptr("战斗基础效果类型"));
	pElem_SEffectBase->SetAttribute("comment", ToUTF8Ptr("父类SEffectBase部分"));
	if(rElement.LinkEndChild(pElem_SEffectBase.get()) != NULL)
		pElem_SEffectBase.release();
	unique_ptr<TiXmlElement> pElem_eStatus(new TiXmlElement("EBStatusType"));
	if(pElem_eStatus == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eStatus->SetAttribute("name", "eStatus");
	const char* pszEnum_eStatus = EnumValToStr(s.eStatus);
	if(pszEnum_eStatus == NULL)
	{
		LOG_CRI << "EnumValToStr for EBStatusType fails!";
		return false;
	}
	pElem_eStatus->SetAttribute("value", pszEnum_eStatus);
	pElem_eStatus->SetAttribute("comment", ToUTF8Ptr("状态类型"));
	if(rElement.LinkEndChild(pElem_eStatus.get()) != NULL)
		pElem_eStatus.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecAddStatus& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SEffectAddStatusPtr p(new SEffectAddStatus);
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

bool VectorToXML(const TVecAddStatus& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SEffectAddStatus"));
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

SEffectAddHP::SEffectAddHP() : dwSkillID(0), eHPType((EBModifyHPType)0), dwAddHP(0) { }

CInArchive& operator>>(CInArchive& src, SEffectAddHP& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (SEffectBase&)s;
	src >> s.dwSkillID;
	src >> (UINT8&)s.eHPType;
	src >> s.dwAddHP;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SEffectAddHP& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const SEffectBase&)s;
	src << s.dwSkillID;
	src << (UINT8&)s.eHPType;
	src << s.dwAddHP;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecAddHP& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SEffectAddHPPtr p(new SEffectAddHP);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecAddHP& vec)
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

bool FromXML(TiXmlElement& rElement, SEffectAddHP& s)
{
	if(strcmp(rElement.Value(), "SEffectAddHP") != 0)
	{
		LOG_CRI << "rElement is not SEffectAddHP!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for SEffectBase is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (SEffectBase&)s))
	{
		LOG_CRI << "FromXML for: SEffectBase fails!";
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
		LOG_CRI << "pElemChild for eHPType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "EBModifyHPType") != 0)
	{
		LOG_CRI << "pElemChild is not EBModifyHPType!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eHPType") != 0)
	{
		LOG_CRI << "Attribute: name is not eHPType!";
		return false;
	}
	const char* pszVal_eHPType = pElemChild->Attribute("value");
	if(pszVal_eHPType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!EnumStrToVal(pszVal_eHPType, s.eHPType))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwAddHP is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwAddHP") != 0)
	{
		LOG_CRI << "Attribute: name is not dwAddHP!";
		return false;
	}
	const char* pszVal_dwAddHP = pElemChild->Attribute("value");
	if(pszVal_dwAddHP == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwAddHP, s.dwAddHP))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SEffectAddHP& s, TiXmlElement& rElement)
{
	rElement.SetValue("SEffectAddHP");
	rElement.SetAttribute("type", ToUTF8Ptr("加血"));
	unique_ptr<TiXmlElement> pElem_SEffectBase(new TiXmlElement("SEffectBase"));
	if(pElem_SEffectBase == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const SEffectBase&)s, *pElem_SEffectBase))
	{
		LOG_CRI << "SEffectBase ToXML fails!";
		return false;
	}
	pElem_SEffectBase->SetAttribute("type", ToUTF8Ptr("战斗基础效果类型"));
	pElem_SEffectBase->SetAttribute("comment", ToUTF8Ptr("父类SEffectBase部分"));
	if(rElement.LinkEndChild(pElem_SEffectBase.get()) != NULL)
		pElem_SEffectBase.release();
	unique_ptr<TiXmlElement> pElem_dwSkillID(new TiXmlElement("UINT32"));
	if(pElem_dwSkillID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwSkillID->SetAttribute("name", "dwSkillID");
	pElem_dwSkillID->SetAttribute("value", NumberToString(s.dwSkillID).c_str());
	pElem_dwSkillID->SetAttribute("comment", ToUTF8Ptr("加血对应ID"));
	if(rElement.LinkEndChild(pElem_dwSkillID.get()) != NULL)
		pElem_dwSkillID.release();
	unique_ptr<TiXmlElement> pElem_eHPType(new TiXmlElement("EBModifyHPType"));
	if(pElem_eHPType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eHPType->SetAttribute("name", "eHPType");
	const char* pszEnum_eHPType = EnumValToStr(s.eHPType);
	if(pszEnum_eHPType == NULL)
	{
		LOG_CRI << "EnumValToStr for EBModifyHPType fails!";
		return false;
	}
	pElem_eHPType->SetAttribute("value", pszEnum_eHPType);
	pElem_eHPType->SetAttribute("comment", ToUTF8Ptr("加血类型"));
	if(rElement.LinkEndChild(pElem_eHPType.get()) != NULL)
		pElem_eHPType.release();
	unique_ptr<TiXmlElement> pElem_dwAddHP(new TiXmlElement("UINT32"));
	if(pElem_dwAddHP == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwAddHP->SetAttribute("name", "dwAddHP");
	pElem_dwAddHP->SetAttribute("value", NumberToString(s.dwAddHP).c_str());
	pElem_dwAddHP->SetAttribute("comment", ToUTF8Ptr("增加的血量"));
	if(rElement.LinkEndChild(pElem_dwAddHP.get()) != NULL)
		pElem_dwAddHP.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecAddHP& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SEffectAddHPPtr p(new SEffectAddHP);
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

bool VectorToXML(const TVecAddHP& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SEffectAddHP"));
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

SEffectRelive::SEffectRelive() : byGroupID(0), bySide(0), byPos(0), wFighterID(0), dwHpMax(0), 
			dwHp(0), dwAura(0), dwAuraMax(0) { }

CInArchive& operator>>(CInArchive& src, SEffectRelive& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (SEffectBase&)s;
	src >> s.byGroupID;
	src >> s.bySide;
	src >> s.byPos;
	src >> s.wFighterID;
	src >> s.dwHpMax;
	src >> s.dwHp;
	src >> s.dwAura;
	src >> s.dwAuraMax;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SEffectRelive& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const SEffectBase&)s;
	src << s.byGroupID;
	src << s.bySide;
	src << s.byPos;
	src << s.wFighterID;
	src << s.dwHpMax;
	src << s.dwHp;
	src << s.dwAura;
	src << s.dwAuraMax;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecRelive& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SEffectRelivePtr p(new SEffectRelive);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecRelive& vec)
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

bool FromXML(TiXmlElement& rElement, SEffectRelive& s)
{
	if(strcmp(rElement.Value(), "SEffectRelive") != 0)
	{
		LOG_CRI << "rElement is not SEffectRelive!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for SEffectBase is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (SEffectBase&)s))
	{
		LOG_CRI << "FromXML for: SEffectBase fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
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
		LOG_CRI << "pElemChild for bySide is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "bySide") != 0)
	{
		LOG_CRI << "Attribute: name is not bySide!";
		return false;
	}
	const char* pszVal_bySide = pElemChild->Attribute("value");
	if(pszVal_bySide == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_bySide, s.bySide))
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
	return true;
}

bool ToXML(const SEffectRelive& s, TiXmlElement& rElement)
{
	rElement.SetValue("SEffectRelive");
	rElement.SetAttribute("type", ToUTF8Ptr("重生"));
	unique_ptr<TiXmlElement> pElem_SEffectBase(new TiXmlElement("SEffectBase"));
	if(pElem_SEffectBase == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const SEffectBase&)s, *pElem_SEffectBase))
	{
		LOG_CRI << "SEffectBase ToXML fails!";
		return false;
	}
	pElem_SEffectBase->SetAttribute("type", ToUTF8Ptr("战斗基础效果类型"));
	pElem_SEffectBase->SetAttribute("comment", ToUTF8Ptr("父类SEffectBase部分"));
	if(rElement.LinkEndChild(pElem_SEffectBase.get()) != NULL)
		pElem_SEffectBase.release();
	unique_ptr<TiXmlElement> pElem_byGroupID(new TiXmlElement("UINT8"));
	if(pElem_byGroupID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byGroupID->SetAttribute("name", "byGroupID");
	pElem_byGroupID->SetAttribute("value", NumberToString(s.byGroupID).c_str());
	pElem_byGroupID->SetAttribute("comment", ToUTF8Ptr("组编号"));
	if(rElement.LinkEndChild(pElem_byGroupID.get()) != NULL)
		pElem_byGroupID.release();
	unique_ptr<TiXmlElement> pElem_bySide(new TiXmlElement("UINT8"));
	if(pElem_bySide == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_bySide->SetAttribute("name", "bySide");
	pElem_bySide->SetAttribute("value", NumberToString(s.bySide).c_str());
	pElem_bySide->SetAttribute("comment", ToUTF8Ptr("方向编号"));
	if(rElement.LinkEndChild(pElem_bySide.get()) != NULL)
		pElem_bySide.release();
	unique_ptr<TiXmlElement> pElem_byPos(new TiXmlElement("UINT8"));
	if(pElem_byPos == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byPos->SetAttribute("name", "byPos");
	pElem_byPos->SetAttribute("value", NumberToString(s.byPos).c_str());
	pElem_byPos->SetAttribute("comment", ToUTF8Ptr("位置编号"));
	if(rElement.LinkEndChild(pElem_byPos.get()) != NULL)
		pElem_byPos.release();
	unique_ptr<TiXmlElement> pElem_wFighterID(new TiXmlElement("UINT16"));
	if(pElem_wFighterID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wFighterID->SetAttribute("name", "wFighterID");
	pElem_wFighterID->SetAttribute("value", NumberToString(s.wFighterID).c_str());
	pElem_wFighterID->SetAttribute("comment", ToUTF8Ptr("散仙ID"));
	if(rElement.LinkEndChild(pElem_wFighterID.get()) != NULL)
		pElem_wFighterID.release();
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
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecRelive& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SEffectRelivePtr p(new SEffectRelive);
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

bool VectorToXML(const TVecRelive& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SEffectRelive"));
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

SEffectCounter::SEffectCounter() : eSubHPType((EBSubHPType)0), eHPType((EBModifyHPType)0), dwDecHP(0) { }

CInArchive& operator>>(CInArchive& src, SEffectCounter& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (SEffectBase&)s;
	src >> (UINT8&)s.eSubHPType;
	src >> (UINT8&)s.eHPType;
	src >> s.dwDecHP;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SEffectCounter& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const SEffectBase&)s;
	src << (UINT8&)s.eSubHPType;
	src << (UINT8&)s.eHPType;
	src << s.dwDecHP;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecCounter& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SEffectCounterPtr p(new SEffectCounter);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecCounter& vec)
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

bool FromXML(TiXmlElement& rElement, SEffectCounter& s)
{
	if(strcmp(rElement.Value(), "SEffectCounter") != 0)
	{
		LOG_CRI << "rElement is not SEffectCounter!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for SEffectBase is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (SEffectBase&)s))
	{
		LOG_CRI << "FromXML for: SEffectBase fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eSubHPType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "EBSubHPType") != 0)
	{
		LOG_CRI << "pElemChild is not EBSubHPType!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eSubHPType") != 0)
	{
		LOG_CRI << "Attribute: name is not eSubHPType!";
		return false;
	}
	const char* pszVal_eSubHPType = pElemChild->Attribute("value");
	if(pszVal_eSubHPType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!EnumStrToVal(pszVal_eSubHPType, s.eSubHPType))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eHPType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "EBModifyHPType") != 0)
	{
		LOG_CRI << "pElemChild is not EBModifyHPType!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eHPType") != 0)
	{
		LOG_CRI << "Attribute: name is not eHPType!";
		return false;
	}
	const char* pszVal_eHPType = pElemChild->Attribute("value");
	if(pszVal_eHPType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!EnumStrToVal(pszVal_eHPType, s.eHPType))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwDecHP is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwDecHP") != 0)
	{
		LOG_CRI << "Attribute: name is not dwDecHP!";
		return false;
	}
	const char* pszVal_dwDecHP = pElemChild->Attribute("value");
	if(pszVal_dwDecHP == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwDecHP, s.dwDecHP))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SEffectCounter& s, TiXmlElement& rElement)
{
	rElement.SetValue("SEffectCounter");
	rElement.SetAttribute("type", ToUTF8Ptr("反击"));
	unique_ptr<TiXmlElement> pElem_SEffectBase(new TiXmlElement("SEffectBase"));
	if(pElem_SEffectBase == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const SEffectBase&)s, *pElem_SEffectBase))
	{
		LOG_CRI << "SEffectBase ToXML fails!";
		return false;
	}
	pElem_SEffectBase->SetAttribute("type", ToUTF8Ptr("战斗基础效果类型"));
	pElem_SEffectBase->SetAttribute("comment", ToUTF8Ptr("父类SEffectBase部分"));
	if(rElement.LinkEndChild(pElem_SEffectBase.get()) != NULL)
		pElem_SEffectBase.release();
	unique_ptr<TiXmlElement> pElem_eSubHPType(new TiXmlElement("EBSubHPType"));
	if(pElem_eSubHPType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eSubHPType->SetAttribute("name", "eSubHPType");
	const char* pszEnum_eSubHPType = EnumValToStr(s.eSubHPType);
	if(pszEnum_eSubHPType == NULL)
	{
		LOG_CRI << "EnumValToStr for EBSubHPType fails!";
		return false;
	}
	pElem_eSubHPType->SetAttribute("value", pszEnum_eSubHPType);
	pElem_eSubHPType->SetAttribute("comment", ToUTF8Ptr("扣血伤害类型（物理/法术）"));
	if(rElement.LinkEndChild(pElem_eSubHPType.get()) != NULL)
		pElem_eSubHPType.release();
	unique_ptr<TiXmlElement> pElem_eHPType(new TiXmlElement("EBModifyHPType"));
	if(pElem_eHPType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eHPType->SetAttribute("name", "eHPType");
	const char* pszEnum_eHPType = EnumValToStr(s.eHPType);
	if(pszEnum_eHPType == NULL)
	{
		LOG_CRI << "EnumValToStr for EBModifyHPType fails!";
		return false;
	}
	pElem_eHPType->SetAttribute("value", pszEnum_eHPType);
	pElem_eHPType->SetAttribute("comment", ToUTF8Ptr("扣血类型"));
	if(rElement.LinkEndChild(pElem_eHPType.get()) != NULL)
		pElem_eHPType.release();
	unique_ptr<TiXmlElement> pElem_dwDecHP(new TiXmlElement("UINT32"));
	if(pElem_dwDecHP == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwDecHP->SetAttribute("name", "dwDecHP");
	pElem_dwDecHP->SetAttribute("value", NumberToString(s.dwDecHP).c_str());
	pElem_dwDecHP->SetAttribute("comment", ToUTF8Ptr("反击的伤害量"));
	if(rElement.LinkEndChild(pElem_dwDecHP.get()) != NULL)
		pElem_dwDecHP.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecCounter& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SEffectCounterPtr p(new SEffectCounter);
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

bool VectorToXML(const TVecCounter& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SEffectCounter"));
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

SEffectStateBuffAdd::SEffectStateBuffAdd() : dwBuffKey(0), eStateBuffType((EBStateBuffType)0), dwSkillID(0), dwBaseSkillID(0), byLast(0), 
			dwValue(0) { }

CInArchive& operator>>(CInArchive& src, SEffectStateBuffAdd& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (SEffectBase&)s;
	src >> s.dwBuffKey;
	src >> (UINT16&)s.eStateBuffType;
	src >> s.dwSkillID;
	src >> s.dwBaseSkillID;
	src >> s.byLast;
	src >> s.dwValue;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SEffectStateBuffAdd& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const SEffectBase&)s;
	src << s.dwBuffKey;
	src << (UINT16&)s.eStateBuffType;
	src << s.dwSkillID;
	src << s.dwBaseSkillID;
	src << s.byLast;
	src << s.dwValue;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecStateBuffAdd& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SEffectStateBuffAddPtr p(new SEffectStateBuffAdd);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecStateBuffAdd& vec)
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

bool FromXML(TiXmlElement& rElement, SEffectStateBuffAdd& s)
{
	if(strcmp(rElement.Value(), "SEffectStateBuffAdd") != 0)
	{
		LOG_CRI << "rElement is not SEffectStateBuffAdd!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for SEffectBase is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (SEffectBase&)s))
	{
		LOG_CRI << "FromXML for: SEffectBase fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwBuffKey is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwBuffKey") != 0)
	{
		LOG_CRI << "Attribute: name is not dwBuffKey!";
		return false;
	}
	const char* pszVal_dwBuffKey = pElemChild->Attribute("value");
	if(pszVal_dwBuffKey == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwBuffKey, s.dwBuffKey))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eStateBuffType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "EBStateBuffType") != 0)
	{
		LOG_CRI << "pElemChild is not EBStateBuffType!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eStateBuffType") != 0)
	{
		LOG_CRI << "Attribute: name is not eStateBuffType!";
		return false;
	}
	const char* pszVal_eStateBuffType = pElemChild->Attribute("value");
	if(pszVal_eStateBuffType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!EnumStrToVal(pszVal_eStateBuffType, s.eStateBuffType))
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
		LOG_CRI << "pElemChild for dwBaseSkillID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwBaseSkillID") != 0)
	{
		LOG_CRI << "Attribute: name is not dwBaseSkillID!";
		return false;
	}
	const char* pszVal_dwBaseSkillID = pElemChild->Attribute("value");
	if(pszVal_dwBaseSkillID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwBaseSkillID, s.dwBaseSkillID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byLast is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byLast") != 0)
	{
		LOG_CRI << "Attribute: name is not byLast!";
		return false;
	}
	const char* pszVal_byLast = pElemChild->Attribute("value");
	if(pszVal_byLast == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byLast, s.byLast))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwValue is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "INT32") != 0)
	{
		LOG_CRI << "pElemChild is not INT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwValue") != 0)
	{
		LOG_CRI << "Attribute: name is not dwValue!";
		return false;
	}
	const char* pszVal_dwValue = pElemChild->Attribute("value");
	if(pszVal_dwValue == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwValue, s.dwValue))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SEffectStateBuffAdd& s, TiXmlElement& rElement)
{
	rElement.SetValue("SEffectStateBuffAdd");
	rElement.SetAttribute("type", ToUTF8Ptr("加状态Buff"));
	unique_ptr<TiXmlElement> pElem_SEffectBase(new TiXmlElement("SEffectBase"));
	if(pElem_SEffectBase == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const SEffectBase&)s, *pElem_SEffectBase))
	{
		LOG_CRI << "SEffectBase ToXML fails!";
		return false;
	}
	pElem_SEffectBase->SetAttribute("type", ToUTF8Ptr("战斗基础效果类型"));
	pElem_SEffectBase->SetAttribute("comment", ToUTF8Ptr("父类SEffectBase部分"));
	if(rElement.LinkEndChild(pElem_SEffectBase.get()) != NULL)
		pElem_SEffectBase.release();
	unique_ptr<TiXmlElement> pElem_dwBuffKey(new TiXmlElement("UINT32"));
	if(pElem_dwBuffKey == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwBuffKey->SetAttribute("name", "dwBuffKey");
	pElem_dwBuffKey->SetAttribute("value", NumberToString(s.dwBuffKey).c_str());
	pElem_dwBuffKey->SetAttribute("comment", ToUTF8Ptr("查找这个buff的唯一ID"));
	if(rElement.LinkEndChild(pElem_dwBuffKey.get()) != NULL)
		pElem_dwBuffKey.release();
	unique_ptr<TiXmlElement> pElem_eStateBuffType(new TiXmlElement("EBStateBuffType"));
	if(pElem_eStateBuffType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eStateBuffType->SetAttribute("name", "eStateBuffType");
	const char* pszEnum_eStateBuffType = EnumValToStr(s.eStateBuffType);
	if(pszEnum_eStateBuffType == NULL)
	{
		LOG_CRI << "EnumValToStr for EBStateBuffType fails!";
		return false;
	}
	pElem_eStateBuffType->SetAttribute("value", pszEnum_eStateBuffType);
	pElem_eStateBuffType->SetAttribute("comment", ToUTF8Ptr("状态枚举"));
	if(rElement.LinkEndChild(pElem_eStateBuffType.get()) != NULL)
		pElem_eStateBuffType.release();
	unique_ptr<TiXmlElement> pElem_dwSkillID(new TiXmlElement("UINT32"));
	if(pElem_dwSkillID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwSkillID->SetAttribute("name", "dwSkillID");
	pElem_dwSkillID->SetAttribute("value", NumberToString(s.dwSkillID).c_str());
	pElem_dwSkillID->SetAttribute("comment", ToUTF8Ptr("该Buff的技能来源"));
	if(rElement.LinkEndChild(pElem_dwSkillID.get()) != NULL)
		pElem_dwSkillID.release();
	unique_ptr<TiXmlElement> pElem_dwBaseSkillID(new TiXmlElement("UINT32"));
	if(pElem_dwBaseSkillID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwBaseSkillID->SetAttribute("name", "dwBaseSkillID");
	pElem_dwBaseSkillID->SetAttribute("value", NumberToString(s.dwBaseSkillID).c_str());
	pElem_dwBaseSkillID->SetAttribute("comment", ToUTF8Ptr("初始技能ID（SkillBase表的ID）"));
	if(rElement.LinkEndChild(pElem_dwBaseSkillID.get()) != NULL)
		pElem_dwBaseSkillID.release();
	unique_ptr<TiXmlElement> pElem_byLast(new TiXmlElement("UINT8"));
	if(pElem_byLast == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byLast->SetAttribute("name", "byLast");
	pElem_byLast->SetAttribute("value", NumberToString(s.byLast).c_str());
	pElem_byLast->SetAttribute("comment", ToUTF8Ptr("持续时间"));
	if(rElement.LinkEndChild(pElem_byLast.get()) != NULL)
		pElem_byLast.release();
	unique_ptr<TiXmlElement> pElem_dwValue(new TiXmlElement("INT32"));
	if(pElem_dwValue == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwValue->SetAttribute("name", "dwValue");
	pElem_dwValue->SetAttribute("value", NumberToString(s.dwValue).c_str());
	pElem_dwValue->SetAttribute("comment", ToUTF8Ptr("该Buff的效果值"));
	if(rElement.LinkEndChild(pElem_dwValue.get()) != NULL)
		pElem_dwValue.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecStateBuffAdd& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SEffectStateBuffAddPtr p(new SEffectStateBuffAdd);
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

bool VectorToXML(const TVecStateBuffAdd& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SEffectStateBuffAdd"));
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

SEffectStateBuffEffect::SEffectStateBuffEffect() : dwBuffKey(0) { }

CInArchive& operator>>(CInArchive& src, SEffectStateBuffEffect& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (SEffectBase&)s;
	src >> s.dwBuffKey;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SEffectStateBuffEffect& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const SEffectBase&)s;
	src << s.dwBuffKey;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecStateBuffEffect& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SEffectStateBuffEffectPtr p(new SEffectStateBuffEffect);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecStateBuffEffect& vec)
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

bool FromXML(TiXmlElement& rElement, SEffectStateBuffEffect& s)
{
	if(strcmp(rElement.Value(), "SEffectStateBuffEffect") != 0)
	{
		LOG_CRI << "rElement is not SEffectStateBuffEffect!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for SEffectBase is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (SEffectBase&)s))
	{
		LOG_CRI << "FromXML for: SEffectBase fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwBuffKey is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwBuffKey") != 0)
	{
		LOG_CRI << "Attribute: name is not dwBuffKey!";
		return false;
	}
	const char* pszVal_dwBuffKey = pElemChild->Attribute("value");
	if(pszVal_dwBuffKey == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwBuffKey, s.dwBuffKey))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SEffectStateBuffEffect& s, TiXmlElement& rElement)
{
	rElement.SetValue("SEffectStateBuffEffect");
	rElement.SetAttribute("type", ToUTF8Ptr("状态Buff生效"));
	unique_ptr<TiXmlElement> pElem_SEffectBase(new TiXmlElement("SEffectBase"));
	if(pElem_SEffectBase == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const SEffectBase&)s, *pElem_SEffectBase))
	{
		LOG_CRI << "SEffectBase ToXML fails!";
		return false;
	}
	pElem_SEffectBase->SetAttribute("type", ToUTF8Ptr("战斗基础效果类型"));
	pElem_SEffectBase->SetAttribute("comment", ToUTF8Ptr("父类SEffectBase部分"));
	if(rElement.LinkEndChild(pElem_SEffectBase.get()) != NULL)
		pElem_SEffectBase.release();
	unique_ptr<TiXmlElement> pElem_dwBuffKey(new TiXmlElement("UINT32"));
	if(pElem_dwBuffKey == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwBuffKey->SetAttribute("name", "dwBuffKey");
	pElem_dwBuffKey->SetAttribute("value", NumberToString(s.dwBuffKey).c_str());
	pElem_dwBuffKey->SetAttribute("comment", ToUTF8Ptr("查找这个Buff的唯一ID"));
	if(rElement.LinkEndChild(pElem_dwBuffKey.get()) != NULL)
		pElem_dwBuffKey.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecStateBuffEffect& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SEffectStateBuffEffectPtr p(new SEffectStateBuffEffect);
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

bool VectorToXML(const TVecStateBuffEffect& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SEffectStateBuffEffect"));
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

SEffectStateBuffDec::SEffectStateBuffDec() : dwBuffKey(0) { }

CInArchive& operator>>(CInArchive& src, SEffectStateBuffDec& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (SEffectBase&)s;
	src >> s.dwBuffKey;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SEffectStateBuffDec& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const SEffectBase&)s;
	src << s.dwBuffKey;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecStateBuffDec& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SEffectStateBuffDecPtr p(new SEffectStateBuffDec);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecStateBuffDec& vec)
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

bool FromXML(TiXmlElement& rElement, SEffectStateBuffDec& s)
{
	if(strcmp(rElement.Value(), "SEffectStateBuffDec") != 0)
	{
		LOG_CRI << "rElement is not SEffectStateBuffDec!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for SEffectBase is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (SEffectBase&)s))
	{
		LOG_CRI << "FromXML for: SEffectBase fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwBuffKey is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwBuffKey") != 0)
	{
		LOG_CRI << "Attribute: name is not dwBuffKey!";
		return false;
	}
	const char* pszVal_dwBuffKey = pElemChild->Attribute("value");
	if(pszVal_dwBuffKey == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwBuffKey, s.dwBuffKey))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SEffectStateBuffDec& s, TiXmlElement& rElement)
{
	rElement.SetValue("SEffectStateBuffDec");
	rElement.SetAttribute("type", ToUTF8Ptr("减状态Buff"));
	unique_ptr<TiXmlElement> pElem_SEffectBase(new TiXmlElement("SEffectBase"));
	if(pElem_SEffectBase == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const SEffectBase&)s, *pElem_SEffectBase))
	{
		LOG_CRI << "SEffectBase ToXML fails!";
		return false;
	}
	pElem_SEffectBase->SetAttribute("type", ToUTF8Ptr("战斗基础效果类型"));
	pElem_SEffectBase->SetAttribute("comment", ToUTF8Ptr("父类SEffectBase部分"));
	if(rElement.LinkEndChild(pElem_SEffectBase.get()) != NULL)
		pElem_SEffectBase.release();
	unique_ptr<TiXmlElement> pElem_dwBuffKey(new TiXmlElement("UINT32"));
	if(pElem_dwBuffKey == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwBuffKey->SetAttribute("name", "dwBuffKey");
	pElem_dwBuffKey->SetAttribute("value", NumberToString(s.dwBuffKey).c_str());
	pElem_dwBuffKey->SetAttribute("comment", ToUTF8Ptr("查找这个Buff的唯一ID"));
	if(rElement.LinkEndChild(pElem_dwBuffKey.get()) != NULL)
		pElem_dwBuffKey.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecStateBuffDec& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SEffectStateBuffDecPtr p(new SEffectStateBuffDec);
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

bool VectorToXML(const TVecStateBuffDec& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SEffectStateBuffDec"));
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

SEffectStateBuffLast::SEffectStateBuffLast() : dwBuffKey(0), byLast(0) { }

CInArchive& operator>>(CInArchive& src, SEffectStateBuffLast& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (SEffectBase&)s;
	src >> s.dwBuffKey;
	src >> s.byLast;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SEffectStateBuffLast& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const SEffectBase&)s;
	src << s.dwBuffKey;
	src << s.byLast;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecStateBuffLast& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SEffectStateBuffLastPtr p(new SEffectStateBuffLast);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecStateBuffLast& vec)
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

bool FromXML(TiXmlElement& rElement, SEffectStateBuffLast& s)
{
	if(strcmp(rElement.Value(), "SEffectStateBuffLast") != 0)
	{
		LOG_CRI << "rElement is not SEffectStateBuffLast!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for SEffectBase is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (SEffectBase&)s))
	{
		LOG_CRI << "FromXML for: SEffectBase fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwBuffKey is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwBuffKey") != 0)
	{
		LOG_CRI << "Attribute: name is not dwBuffKey!";
		return false;
	}
	const char* pszVal_dwBuffKey = pElemChild->Attribute("value");
	if(pszVal_dwBuffKey == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwBuffKey, s.dwBuffKey))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byLast is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byLast") != 0)
	{
		LOG_CRI << "Attribute: name is not byLast!";
		return false;
	}
	const char* pszVal_byLast = pElemChild->Attribute("value");
	if(pszVal_byLast == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byLast, s.byLast))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SEffectStateBuffLast& s, TiXmlElement& rElement)
{
	rElement.SetValue("SEffectStateBuffLast");
	rElement.SetAttribute("type", ToUTF8Ptr("Buff持续时间"));
	unique_ptr<TiXmlElement> pElem_SEffectBase(new TiXmlElement("SEffectBase"));
	if(pElem_SEffectBase == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const SEffectBase&)s, *pElem_SEffectBase))
	{
		LOG_CRI << "SEffectBase ToXML fails!";
		return false;
	}
	pElem_SEffectBase->SetAttribute("type", ToUTF8Ptr("战斗基础效果类型"));
	pElem_SEffectBase->SetAttribute("comment", ToUTF8Ptr("父类SEffectBase部分"));
	if(rElement.LinkEndChild(pElem_SEffectBase.get()) != NULL)
		pElem_SEffectBase.release();
	unique_ptr<TiXmlElement> pElem_dwBuffKey(new TiXmlElement("UINT32"));
	if(pElem_dwBuffKey == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwBuffKey->SetAttribute("name", "dwBuffKey");
	pElem_dwBuffKey->SetAttribute("value", NumberToString(s.dwBuffKey).c_str());
	pElem_dwBuffKey->SetAttribute("comment", ToUTF8Ptr("查找这个Buff的唯一ID"));
	if(rElement.LinkEndChild(pElem_dwBuffKey.get()) != NULL)
		pElem_dwBuffKey.release();
	unique_ptr<TiXmlElement> pElem_byLast(new TiXmlElement("UINT8"));
	if(pElem_byLast == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byLast->SetAttribute("name", "byLast");
	pElem_byLast->SetAttribute("value", NumberToString(s.byLast).c_str());
	pElem_byLast->SetAttribute("comment", ToUTF8Ptr("持续时间"));
	if(rElement.LinkEndChild(pElem_byLast.get()) != NULL)
		pElem_byLast.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecStateBuffLast& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SEffectStateBuffLastPtr p(new SEffectStateBuffLast);
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

bool VectorToXML(const TVecStateBuffLast& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SEffectStateBuffLast"));
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

SEffectAttrBuffAdd::SEffectAttrBuffAdd() : eBuffType((NProtoCommon::EFighterAttr)0), dwBuffKey(0), dwSkillID(0), byLast(0), dwValue(0) { }

CInArchive& operator>>(CInArchive& src, SEffectAttrBuffAdd& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (SEffectBase&)s;
	src >> (UINT8&)s.eBuffType;
	src >> s.dwBuffKey;
	src >> s.dwSkillID;
	src >> s.byLast;
	src >> s.dwValue;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SEffectAttrBuffAdd& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const SEffectBase&)s;
	src << (UINT8&)s.eBuffType;
	src << s.dwBuffKey;
	src << s.dwSkillID;
	src << s.byLast;
	src << s.dwValue;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecAttrBuffAdd& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SEffectAttrBuffAddPtr p(new SEffectAttrBuffAdd);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecAttrBuffAdd& vec)
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

bool FromXML(TiXmlElement& rElement, SEffectAttrBuffAdd& s)
{
	if(strcmp(rElement.Value(), "SEffectAttrBuffAdd") != 0)
	{
		LOG_CRI << "rElement is not SEffectAttrBuffAdd!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for SEffectBase is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (SEffectBase&)s))
	{
		LOG_CRI << "FromXML for: SEffectBase fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eBuffType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "ProtoCommon::EFighterAttr") != 0)
	{
		LOG_CRI << "pElemChild is not ProtoCommon::EFighterAttr!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eBuffType") != 0)
	{
		LOG_CRI << "Attribute: name is not eBuffType!";
		return false;
	}
	const char* pszVal_eBuffType = pElemChild->Attribute("value");
	if(pszVal_eBuffType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!NProtoCommon::EnumStrToVal(pszVal_eBuffType, s.eBuffType))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwBuffKey is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwBuffKey") != 0)
	{
		LOG_CRI << "Attribute: name is not dwBuffKey!";
		return false;
	}
	const char* pszVal_dwBuffKey = pElemChild->Attribute("value");
	if(pszVal_dwBuffKey == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwBuffKey, s.dwBuffKey))
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
		LOG_CRI << "pElemChild for byLast is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byLast") != 0)
	{
		LOG_CRI << "Attribute: name is not byLast!";
		return false;
	}
	const char* pszVal_byLast = pElemChild->Attribute("value");
	if(pszVal_byLast == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byLast, s.byLast))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwValue is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "INT32") != 0)
	{
		LOG_CRI << "pElemChild is not INT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwValue") != 0)
	{
		LOG_CRI << "Attribute: name is not dwValue!";
		return false;
	}
	const char* pszVal_dwValue = pElemChild->Attribute("value");
	if(pszVal_dwValue == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwValue, s.dwValue))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SEffectAttrBuffAdd& s, TiXmlElement& rElement)
{
	rElement.SetValue("SEffectAttrBuffAdd");
	rElement.SetAttribute("type", ToUTF8Ptr("加修改人物属性buff"));
	unique_ptr<TiXmlElement> pElem_SEffectBase(new TiXmlElement("SEffectBase"));
	if(pElem_SEffectBase == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const SEffectBase&)s, *pElem_SEffectBase))
	{
		LOG_CRI << "SEffectBase ToXML fails!";
		return false;
	}
	pElem_SEffectBase->SetAttribute("type", ToUTF8Ptr("战斗基础效果类型"));
	pElem_SEffectBase->SetAttribute("comment", ToUTF8Ptr("父类SEffectBase部分"));
	if(rElement.LinkEndChild(pElem_SEffectBase.get()) != NULL)
		pElem_SEffectBase.release();
	unique_ptr<TiXmlElement> pElem_eBuffType(new TiXmlElement("ProtoCommon::EFighterAttr"));
	if(pElem_eBuffType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eBuffType->SetAttribute("name", "eBuffType");
	const char* pszEnum_eBuffType = NProtoCommon::EnumValToStr(s.eBuffType);
	if(pszEnum_eBuffType == NULL)
	{
		LOG_CRI << "EnumValToStr for eBuffType fails!";
		return false;
	}
	pElem_eBuffType->SetAttribute("value", pszEnum_eBuffType);
	pElem_eBuffType->SetAttribute("comment", ToUTF8Ptr("修改的属性枚举"));
	if(rElement.LinkEndChild(pElem_eBuffType.get()) != NULL)
		pElem_eBuffType.release();
	unique_ptr<TiXmlElement> pElem_dwBuffKey(new TiXmlElement("UINT32"));
	if(pElem_dwBuffKey == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwBuffKey->SetAttribute("name", "dwBuffKey");
	pElem_dwBuffKey->SetAttribute("value", NumberToString(s.dwBuffKey).c_str());
	pElem_dwBuffKey->SetAttribute("comment", ToUTF8Ptr("查找这个buff的唯一ID"));
	if(rElement.LinkEndChild(pElem_dwBuffKey.get()) != NULL)
		pElem_dwBuffKey.release();
	unique_ptr<TiXmlElement> pElem_dwSkillID(new TiXmlElement("UINT32"));
	if(pElem_dwSkillID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwSkillID->SetAttribute("name", "dwSkillID");
	pElem_dwSkillID->SetAttribute("value", NumberToString(s.dwSkillID).c_str());
	pElem_dwSkillID->SetAttribute("comment", ToUTF8Ptr("该Buff的技能来源"));
	if(rElement.LinkEndChild(pElem_dwSkillID.get()) != NULL)
		pElem_dwSkillID.release();
	unique_ptr<TiXmlElement> pElem_byLast(new TiXmlElement("UINT8"));
	if(pElem_byLast == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byLast->SetAttribute("name", "byLast");
	pElem_byLast->SetAttribute("value", NumberToString(s.byLast).c_str());
	pElem_byLast->SetAttribute("comment", ToUTF8Ptr("持续时间"));
	if(rElement.LinkEndChild(pElem_byLast.get()) != NULL)
		pElem_byLast.release();
	unique_ptr<TiXmlElement> pElem_dwValue(new TiXmlElement("INT32"));
	if(pElem_dwValue == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwValue->SetAttribute("name", "dwValue");
	pElem_dwValue->SetAttribute("value", NumberToString(s.dwValue).c_str());
	pElem_dwValue->SetAttribute("comment", ToUTF8Ptr("该Buff的效果值"));
	if(rElement.LinkEndChild(pElem_dwValue.get()) != NULL)
		pElem_dwValue.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecAttrBuffAdd& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SEffectAttrBuffAddPtr p(new SEffectAttrBuffAdd);
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

bool VectorToXML(const TVecAttrBuffAdd& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SEffectAttrBuffAdd"));
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

SEffectAttrBuffDec::SEffectAttrBuffDec() : dwBuffKey(0) { }

CInArchive& operator>>(CInArchive& src, SEffectAttrBuffDec& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (SEffectBase&)s;
	src >> s.dwBuffKey;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SEffectAttrBuffDec& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const SEffectBase&)s;
	src << s.dwBuffKey;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecAttrBuffDec& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SEffectAttrBuffDecPtr p(new SEffectAttrBuffDec);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecAttrBuffDec& vec)
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

bool FromXML(TiXmlElement& rElement, SEffectAttrBuffDec& s)
{
	if(strcmp(rElement.Value(), "SEffectAttrBuffDec") != 0)
	{
		LOG_CRI << "rElement is not SEffectAttrBuffDec!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for SEffectBase is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (SEffectBase&)s))
	{
		LOG_CRI << "FromXML for: SEffectBase fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwBuffKey is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwBuffKey") != 0)
	{
		LOG_CRI << "Attribute: name is not dwBuffKey!";
		return false;
	}
	const char* pszVal_dwBuffKey = pElemChild->Attribute("value");
	if(pszVal_dwBuffKey == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwBuffKey, s.dwBuffKey))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SEffectAttrBuffDec& s, TiXmlElement& rElement)
{
	rElement.SetValue("SEffectAttrBuffDec");
	rElement.SetAttribute("type", ToUTF8Ptr("减修改人物属性buff"));
	unique_ptr<TiXmlElement> pElem_SEffectBase(new TiXmlElement("SEffectBase"));
	if(pElem_SEffectBase == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const SEffectBase&)s, *pElem_SEffectBase))
	{
		LOG_CRI << "SEffectBase ToXML fails!";
		return false;
	}
	pElem_SEffectBase->SetAttribute("type", ToUTF8Ptr("战斗基础效果类型"));
	pElem_SEffectBase->SetAttribute("comment", ToUTF8Ptr("父类SEffectBase部分"));
	if(rElement.LinkEndChild(pElem_SEffectBase.get()) != NULL)
		pElem_SEffectBase.release();
	unique_ptr<TiXmlElement> pElem_dwBuffKey(new TiXmlElement("UINT32"));
	if(pElem_dwBuffKey == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwBuffKey->SetAttribute("name", "dwBuffKey");
	pElem_dwBuffKey->SetAttribute("value", NumberToString(s.dwBuffKey).c_str());
	pElem_dwBuffKey->SetAttribute("comment", ToUTF8Ptr("查找这个buff的唯一ID"));
	if(rElement.LinkEndChild(pElem_dwBuffKey.get()) != NULL)
		pElem_dwBuffKey.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecAttrBuffDec& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SEffectAttrBuffDecPtr p(new SEffectAttrBuffDec);
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

bool VectorToXML(const TVecAttrBuffDec& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SEffectAttrBuffDec"));
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

SEffectDied::SEffectDied() : dwSkillID(0) { }

CInArchive& operator>>(CInArchive& src, SEffectDied& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (SEffectBase&)s;
	src >> s.dwSkillID;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SEffectDied& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const SEffectBase&)s;
	src << s.dwSkillID;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecDied& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SEffectDiedPtr p(new SEffectDied);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecDied& vec)
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

bool FromXML(TiXmlElement& rElement, SEffectDied& s)
{
	if(strcmp(rElement.Value(), "SEffectDied") != 0)
	{
		LOG_CRI << "rElement is not SEffectDied!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for SEffectBase is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (SEffectBase&)s))
	{
		LOG_CRI << "FromXML for: SEffectBase fails!";
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

bool ToXML(const SEffectDied& s, TiXmlElement& rElement)
{
	rElement.SetValue("SEffectDied");
	rElement.SetAttribute("type", ToUTF8Ptr("我死了"));
	unique_ptr<TiXmlElement> pElem_SEffectBase(new TiXmlElement("SEffectBase"));
	if(pElem_SEffectBase == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const SEffectBase&)s, *pElem_SEffectBase))
	{
		LOG_CRI << "SEffectBase ToXML fails!";
		return false;
	}
	pElem_SEffectBase->SetAttribute("type", ToUTF8Ptr("战斗基础效果类型"));
	pElem_SEffectBase->SetAttribute("comment", ToUTF8Ptr("父类SEffectBase部分"));
	if(rElement.LinkEndChild(pElem_SEffectBase.get()) != NULL)
		pElem_SEffectBase.release();
	unique_ptr<TiXmlElement> pElem_dwSkillID(new TiXmlElement("UINT32"));
	if(pElem_dwSkillID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwSkillID->SetAttribute("name", "dwSkillID");
	pElem_dwSkillID->SetAttribute("value", NumberToString(s.dwSkillID).c_str());
	pElem_dwSkillID->SetAttribute("comment", ToUTF8Ptr("死亡时动画技能ID"));
	if(rElement.LinkEndChild(pElem_dwSkillID.get()) != NULL)
		pElem_dwSkillID.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecDied& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SEffectDiedPtr p(new SEffectDied);
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

bool VectorToXML(const TVecDied& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SEffectDied"));
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

SEffectShieldAbsorb::SEffectShieldAbsorb() : eType((EBSheildAbsorbType)0), dwHP(0) { }

CInArchive& operator>>(CInArchive& src, SEffectShieldAbsorb& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (SEffectBase&)s;
	src >> (UINT8&)s.eType;
	src >> s.dwHP;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SEffectShieldAbsorb& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const SEffectBase&)s;
	src << (UINT8&)s.eType;
	src << s.dwHP;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecShieldAbsorb& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SEffectShieldAbsorbPtr p(new SEffectShieldAbsorb);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecShieldAbsorb& vec)
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

bool FromXML(TiXmlElement& rElement, SEffectShieldAbsorb& s)
{
	if(strcmp(rElement.Value(), "SEffectShieldAbsorb") != 0)
	{
		LOG_CRI << "rElement is not SEffectShieldAbsorb!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for SEffectBase is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (SEffectBase&)s))
	{
		LOG_CRI << "FromXML for: SEffectBase fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "EBSheildAbsorbType") != 0)
	{
		LOG_CRI << "pElemChild is not EBSheildAbsorbType!";
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

bool ToXML(const SEffectShieldAbsorb& s, TiXmlElement& rElement)
{
	rElement.SetValue("SEffectShieldAbsorb");
	rElement.SetAttribute("type", ToUTF8Ptr("盾牌吸收伤害"));
	unique_ptr<TiXmlElement> pElem_SEffectBase(new TiXmlElement("SEffectBase"));
	if(pElem_SEffectBase == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const SEffectBase&)s, *pElem_SEffectBase))
	{
		LOG_CRI << "SEffectBase ToXML fails!";
		return false;
	}
	pElem_SEffectBase->SetAttribute("type", ToUTF8Ptr("战斗基础效果类型"));
	pElem_SEffectBase->SetAttribute("comment", ToUTF8Ptr("父类SEffectBase部分"));
	if(rElement.LinkEndChild(pElem_SEffectBase.get()) != NULL)
		pElem_SEffectBase.release();
	unique_ptr<TiXmlElement> pElem_eType(new TiXmlElement("EBSheildAbsorbType"));
	if(pElem_eType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eType->SetAttribute("name", "eType");
	const char* pszEnum_eType = EnumValToStr(s.eType);
	if(pszEnum_eType == NULL)
	{
		LOG_CRI << "EnumValToStr for EBSheildAbsorbType fails!";
		return false;
	}
	pElem_eType->SetAttribute("value", pszEnum_eType);
	pElem_eType->SetAttribute("comment", ToUTF8Ptr("吸收类型"));
	if(rElement.LinkEndChild(pElem_eType.get()) != NULL)
		pElem_eType.release();
	unique_ptr<TiXmlElement> pElem_dwHP(new TiXmlElement("UINT32"));
	if(pElem_dwHP == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwHP->SetAttribute("name", "dwHP");
	pElem_dwHP->SetAttribute("value", NumberToString(s.dwHP).c_str());
	pElem_dwHP->SetAttribute("comment", ToUTF8Ptr("吸收的数值"));
	if(rElement.LinkEndChild(pElem_dwHP.get()) != NULL)
		pElem_dwHP.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecShieldAbsorb& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SEffectShieldAbsorbPtr p(new SEffectShieldAbsorb);
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

bool VectorToXML(const TVecShieldAbsorb& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SEffectShieldAbsorb"));
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

SEffectTriggerExecute::SEffectTriggerExecute() : dwSkillID(0) { }

CInArchive& operator>>(CInArchive& src, SEffectTriggerExecute& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (SEffectBase&)s;
	src >> s.dwSkillID;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SEffectTriggerExecute& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const SEffectBase&)s;
	src << s.dwSkillID;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecTriggerExecute& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SEffectTriggerExecutePtr p(new SEffectTriggerExecute);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecTriggerExecute& vec)
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

bool FromXML(TiXmlElement& rElement, SEffectTriggerExecute& s)
{
	if(strcmp(rElement.Value(), "SEffectTriggerExecute") != 0)
	{
		LOG_CRI << "rElement is not SEffectTriggerExecute!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for SEffectBase is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (SEffectBase&)s))
	{
		LOG_CRI << "FromXML for: SEffectBase fails!";
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

bool ToXML(const SEffectTriggerExecute& s, TiXmlElement& rElement)
{
	rElement.SetValue("SEffectTriggerExecute");
	rElement.SetAttribute("type", ToUTF8Ptr("被动触发执行"));
	unique_ptr<TiXmlElement> pElem_SEffectBase(new TiXmlElement("SEffectBase"));
	if(pElem_SEffectBase == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const SEffectBase&)s, *pElem_SEffectBase))
	{
		LOG_CRI << "SEffectBase ToXML fails!";
		return false;
	}
	pElem_SEffectBase->SetAttribute("type", ToUTF8Ptr("战斗基础效果类型"));
	pElem_SEffectBase->SetAttribute("comment", ToUTF8Ptr("父类SEffectBase部分"));
	if(rElement.LinkEndChild(pElem_SEffectBase.get()) != NULL)
		pElem_SEffectBase.release();
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

bool VectorFromXML(TiXmlElement& rElement, TVecTriggerExecute& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SEffectTriggerExecutePtr p(new SEffectTriggerExecute);
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

bool VectorToXML(const TVecTriggerExecute& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SEffectTriggerExecute"));
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

SEffectSycHP::SEffectSycHP() : dwHP(0), dwHPMax(0) { }

CInArchive& operator>>(CInArchive& src, SEffectSycHP& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (SEffectBase&)s;
	src >> s.dwHP;
	src >> s.dwHPMax;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SEffectSycHP& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const SEffectBase&)s;
	src << s.dwHP;
	src << s.dwHPMax;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecSycHP& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SEffectSycHPPtr p(new SEffectSycHP);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecSycHP& vec)
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

bool FromXML(TiXmlElement& rElement, SEffectSycHP& s)
{
	if(strcmp(rElement.Value(), "SEffectSycHP") != 0)
	{
		LOG_CRI << "rElement is not SEffectSycHP!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for SEffectBase is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (SEffectBase&)s))
	{
		LOG_CRI << "FromXML for: SEffectBase fails!";
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
		LOG_CRI << "pElemChild for dwHPMax is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwHPMax") != 0)
	{
		LOG_CRI << "Attribute: name is not dwHPMax!";
		return false;
	}
	const char* pszVal_dwHPMax = pElemChild->Attribute("value");
	if(pszVal_dwHPMax == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwHPMax, s.dwHPMax))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SEffectSycHP& s, TiXmlElement& rElement)
{
	rElement.SetValue("SEffectSycHP");
	rElement.SetAttribute("type", ToUTF8Ptr("同步血量和血上限"));
	unique_ptr<TiXmlElement> pElem_SEffectBase(new TiXmlElement("SEffectBase"));
	if(pElem_SEffectBase == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const SEffectBase&)s, *pElem_SEffectBase))
	{
		LOG_CRI << "SEffectBase ToXML fails!";
		return false;
	}
	pElem_SEffectBase->SetAttribute("type", ToUTF8Ptr("战斗基础效果类型"));
	pElem_SEffectBase->SetAttribute("comment", ToUTF8Ptr("父类SEffectBase部分"));
	if(rElement.LinkEndChild(pElem_SEffectBase.get()) != NULL)
		pElem_SEffectBase.release();
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
	unique_ptr<TiXmlElement> pElem_dwHPMax(new TiXmlElement("UINT32"));
	if(pElem_dwHPMax == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwHPMax->SetAttribute("name", "dwHPMax");
	pElem_dwHPMax->SetAttribute("value", NumberToString(s.dwHPMax).c_str());
	pElem_dwHPMax->SetAttribute("comment", ToUTF8Ptr("当前血上限"));
	if(rElement.LinkEndChild(pElem_dwHPMax.get()) != NULL)
		pElem_dwHPMax.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecSycHP& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SEffectSycHPPtr p(new SEffectSycHP);
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

bool VectorToXML(const TVecSycHP& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SEffectSycHP"));
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

SEffectSycAura::SEffectSycAura() : iAura(0) { }

CInArchive& operator>>(CInArchive& src, SEffectSycAura& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (SEffectBase&)s;
	src >> s.iAura;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SEffectSycAura& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const SEffectBase&)s;
	src << s.iAura;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecSycAura& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SEffectSycAuraPtr p(new SEffectSycAura);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecSycAura& vec)
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

bool FromXML(TiXmlElement& rElement, SEffectSycAura& s)
{
	if(strcmp(rElement.Value(), "SEffectSycAura") != 0)
	{
		LOG_CRI << "rElement is not SEffectSycAura!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for SEffectBase is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (SEffectBase&)s))
	{
		LOG_CRI << "FromXML for: SEffectBase fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for iAura is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "INT32") != 0)
	{
		LOG_CRI << "pElemChild is not INT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "iAura") != 0)
	{
		LOG_CRI << "Attribute: name is not iAura!";
		return false;
	}
	const char* pszVal_iAura = pElemChild->Attribute("value");
	if(pszVal_iAura == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_iAura, s.iAura))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SEffectSycAura& s, TiXmlElement& rElement)
{
	rElement.SetValue("SEffectSycAura");
	rElement.SetAttribute("type", ToUTF8Ptr("同步灵气"));
	unique_ptr<TiXmlElement> pElem_SEffectBase(new TiXmlElement("SEffectBase"));
	if(pElem_SEffectBase == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const SEffectBase&)s, *pElem_SEffectBase))
	{
		LOG_CRI << "SEffectBase ToXML fails!";
		return false;
	}
	pElem_SEffectBase->SetAttribute("type", ToUTF8Ptr("战斗基础效果类型"));
	pElem_SEffectBase->SetAttribute("comment", ToUTF8Ptr("父类SEffectBase部分"));
	if(rElement.LinkEndChild(pElem_SEffectBase.get()) != NULL)
		pElem_SEffectBase.release();
	unique_ptr<TiXmlElement> pElem_iAura(new TiXmlElement("INT32"));
	if(pElem_iAura == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_iAura->SetAttribute("name", "iAura");
	pElem_iAura->SetAttribute("value", NumberToString(s.iAura).c_str());
	pElem_iAura->SetAttribute("comment", ToUTF8Ptr("当前怒气值"));
	if(rElement.LinkEndChild(pElem_iAura.get()) != NULL)
		pElem_iAura.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecSycAura& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SEffectSycAuraPtr p(new SEffectSycAura);
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

bool VectorToXML(const TVecSycAura& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SEffectSycAura"));
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

SEffectSycCombine::SEffectSycCombine() : iCombine(0) { }

CInArchive& operator>>(CInArchive& src, SEffectSycCombine& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (SEffectBase&)s;
	src >> s.iCombine;
	src >> s.vecSycType;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SEffectSycCombine& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const SEffectBase&)s;
	src << s.iCombine;
	src << s.vecSycType;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecSycCombine& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SEffectSycCombinePtr p(new SEffectSycCombine);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecSycCombine& vec)
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

bool FromXML(TiXmlElement& rElement, SEffectSycCombine& s)
{
	if(strcmp(rElement.Value(), "SEffectSycCombine") != 0)
	{
		LOG_CRI << "rElement is not SEffectSycCombine!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for SEffectBase is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (SEffectBase&)s))
	{
		LOG_CRI << "FromXML for: SEffectBase fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for iCombine is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "INT32") != 0)
	{
		LOG_CRI << "pElemChild is not INT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "iCombine") != 0)
	{
		LOG_CRI << "Attribute: name is not iCombine!";
		return false;
	}
	const char* pszVal_iCombine = pElemChild->Attribute("value");
	if(pszVal_iCombine == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_iCombine, s.iCombine))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecSycType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecUINT8") != 0)
	{
		LOG_CRI << "pElemChild is not TVecUINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecSycType") != 0)
	{
		LOG_CRI << "Attribute: name is not vecSycType!";
		return false;
	}
	const char* pszText_vecSycType = pElemChild->GetText();
	if(pszText_vecSycType != NULL)
		SplitToNumber(pszText_vecSycType, ",", s.vecSycType);
	return true;
}

bool ToXML(const SEffectSycCombine& s, TiXmlElement& rElement)
{
	rElement.SetValue("SEffectSycCombine");
	rElement.SetAttribute("type", ToUTF8Ptr("同步连携值"));
	unique_ptr<TiXmlElement> pElem_SEffectBase(new TiXmlElement("SEffectBase"));
	if(pElem_SEffectBase == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const SEffectBase&)s, *pElem_SEffectBase))
	{
		LOG_CRI << "SEffectBase ToXML fails!";
		return false;
	}
	pElem_SEffectBase->SetAttribute("type", ToUTF8Ptr("战斗基础效果类型"));
	pElem_SEffectBase->SetAttribute("comment", ToUTF8Ptr("父类SEffectBase部分"));
	if(rElement.LinkEndChild(pElem_SEffectBase.get()) != NULL)
		pElem_SEffectBase.release();
	unique_ptr<TiXmlElement> pElem_iCombine(new TiXmlElement("INT32"));
	if(pElem_iCombine == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_iCombine->SetAttribute("name", "iCombine");
	pElem_iCombine->SetAttribute("value", NumberToString(s.iCombine).c_str());
	pElem_iCombine->SetAttribute("comment", ToUTF8Ptr("当前连携值"));
	if(rElement.LinkEndChild(pElem_iCombine.get()) != NULL)
		pElem_iCombine.release();
	unique_ptr<TiXmlElement> pElem_vecSycType(new TiXmlElement("TVecUINT8"));
	if(pElem_vecSycType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecSycType->SetAttribute("name", "vecSycType");
	string strText_vecSycType;
	for(size_t i = 0; i < s.vecSycType.size(); ++i)
	{
		if(i > 0)
			strText_vecSycType += ", ";
		strText_vecSycType += NumberToString(s.vecSycType[i]);
	}
	unique_ptr<TiXmlText> pText_vecSycType(new TiXmlText(strText_vecSycType.c_str()));
	if(pText_vecSycType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(pElem_vecSycType->LinkEndChild(pText_vecSycType.get()) != NULL)
		pText_vecSycType.release();
	pElem_vecSycType->SetAttribute("comment", ToUTF8Ptr("更改方式（见ECombineType）)"));
	if(rElement.LinkEndChild(pElem_vecSycType.get()) != NULL)
		pElem_vecSycType.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecSycCombine& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SEffectSycCombinePtr p(new SEffectSycCombine);
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

bool VectorToXML(const TVecSycCombine& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SEffectSycCombine"));
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

SEffectCombineSlot::SEffectCombineSlot() : eType((ECombineSlotOPType)0) { }

CInArchive& operator>>(CInArchive& src, SEffectCombineSlot& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (SEffectBase&)s;
	src >> (UINT8&)s.eType;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SEffectCombineSlot& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const SEffectBase&)s;
	src << (UINT8&)s.eType;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecCombineSlot& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SEffectCombineSlotPtr p(new SEffectCombineSlot);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecCombineSlot& vec)
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

bool FromXML(TiXmlElement& rElement, SEffectCombineSlot& s)
{
	if(strcmp(rElement.Value(), "SEffectCombineSlot") != 0)
	{
		LOG_CRI << "rElement is not SEffectCombineSlot!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for SEffectBase is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (SEffectBase&)s))
	{
		LOG_CRI << "FromXML for: SEffectBase fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "ECombineSlotOPType") != 0)
	{
		LOG_CRI << "pElemChild is not ECombineSlotOPType!";
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

bool ToXML(const SEffectCombineSlot& s, TiXmlElement& rElement)
{
	rElement.SetValue("SEffectCombineSlot");
	rElement.SetAttribute("type", ToUTF8Ptr("连携槽相关操作效果"));
	unique_ptr<TiXmlElement> pElem_SEffectBase(new TiXmlElement("SEffectBase"));
	if(pElem_SEffectBase == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const SEffectBase&)s, *pElem_SEffectBase))
	{
		LOG_CRI << "SEffectBase ToXML fails!";
		return false;
	}
	pElem_SEffectBase->SetAttribute("type", ToUTF8Ptr("战斗基础效果类型"));
	pElem_SEffectBase->SetAttribute("comment", ToUTF8Ptr("父类SEffectBase部分"));
	if(rElement.LinkEndChild(pElem_SEffectBase.get()) != NULL)
		pElem_SEffectBase.release();
	unique_ptr<TiXmlElement> pElem_eType(new TiXmlElement("ECombineSlotOPType"));
	if(pElem_eType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eType->SetAttribute("name", "eType");
	const char* pszEnum_eType = EnumValToStr(s.eType);
	if(pszEnum_eType == NULL)
	{
		LOG_CRI << "EnumValToStr for ECombineSlotOPType fails!";
		return false;
	}
	pElem_eType->SetAttribute("value", pszEnum_eType);
	pElem_eType->SetAttribute("comment", ToUTF8Ptr("操作方式"));
	if(rElement.LinkEndChild(pElem_eType.get()) != NULL)
		pElem_eType.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecCombineSlot& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SEffectCombineSlotPtr p(new SEffectCombineSlot);
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

bool VectorToXML(const TVecCombineSlot& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SEffectCombineSlot"));
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

SEffectBrokenShield::SEffectBrokenShield() : iPoint(0) { }

CInArchive& operator>>(CInArchive& src, SEffectBrokenShield& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (SEffectBase&)s;
	src >> s.iPoint;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SEffectBrokenShield& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const SEffectBase&)s;
	src << s.iPoint;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecBrokenShield& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SEffectBrokenShieldPtr p(new SEffectBrokenShield);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecBrokenShield& vec)
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

bool FromXML(TiXmlElement& rElement, SEffectBrokenShield& s)
{
	if(strcmp(rElement.Value(), "SEffectBrokenShield") != 0)
	{
		LOG_CRI << "rElement is not SEffectBrokenShield!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for SEffectBase is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (SEffectBase&)s))
	{
		LOG_CRI << "FromXML for: SEffectBase fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for iPoint is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "INT32") != 0)
	{
		LOG_CRI << "pElemChild is not INT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "iPoint") != 0)
	{
		LOG_CRI << "Attribute: name is not iPoint!";
		return false;
	}
	const char* pszVal_iPoint = pElemChild->Attribute("value");
	if(pszVal_iPoint == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_iPoint, s.iPoint))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SEffectBrokenShield& s, TiXmlElement& rElement)
{
	rElement.SetValue("SEffectBrokenShield");
	rElement.SetAttribute("type", ToUTF8Ptr("破盾效果"));
	unique_ptr<TiXmlElement> pElem_SEffectBase(new TiXmlElement("SEffectBase"));
	if(pElem_SEffectBase == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const SEffectBase&)s, *pElem_SEffectBase))
	{
		LOG_CRI << "SEffectBase ToXML fails!";
		return false;
	}
	pElem_SEffectBase->SetAttribute("type", ToUTF8Ptr("战斗基础效果类型"));
	pElem_SEffectBase->SetAttribute("comment", ToUTF8Ptr("父类SEffectBase部分"));
	if(rElement.LinkEndChild(pElem_SEffectBase.get()) != NULL)
		pElem_SEffectBase.release();
	unique_ptr<TiXmlElement> pElem_iPoint(new TiXmlElement("INT32"));
	if(pElem_iPoint == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_iPoint->SetAttribute("name", "iPoint");
	pElem_iPoint->SetAttribute("value", NumberToString(s.iPoint).c_str());
	pElem_iPoint->SetAttribute("comment", ToUTF8Ptr("盾牌耐久扣减值"));
	if(rElement.LinkEndChild(pElem_iPoint.get()) != NULL)
		pElem_iPoint.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecBrokenShield& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SEffectBrokenShieldPtr p(new SEffectBrokenShield);
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

bool VectorToXML(const TVecBrokenShield& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SEffectBrokenShield"));
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

SEffectSummon::SEffectSummon() : byGroupID(0), bySide(0), byPos(0), wFighterID(0), dwHpMax(0), 
			dwHp(0), dwAura(0), dwAuraMax(0) { }

CInArchive& operator>>(CInArchive& src, SEffectSummon& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (SEffectBase&)s;
	src >> s.byGroupID;
	src >> s.bySide;
	src >> s.byPos;
	src >> s.wFighterID;
	src >> s.dwHpMax;
	src >> s.dwHp;
	src >> s.dwAura;
	src >> s.dwAuraMax;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SEffectSummon& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const SEffectBase&)s;
	src << s.byGroupID;
	src << s.bySide;
	src << s.byPos;
	src << s.wFighterID;
	src << s.dwHpMax;
	src << s.dwHp;
	src << s.dwAura;
	src << s.dwAuraMax;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecSummon& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SEffectSummonPtr p(new SEffectSummon);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecSummon& vec)
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

bool FromXML(TiXmlElement& rElement, SEffectSummon& s)
{
	if(strcmp(rElement.Value(), "SEffectSummon") != 0)
	{
		LOG_CRI << "rElement is not SEffectSummon!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for SEffectBase is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (SEffectBase&)s))
	{
		LOG_CRI << "FromXML for: SEffectBase fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
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
		LOG_CRI << "pElemChild for bySide is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "bySide") != 0)
	{
		LOG_CRI << "Attribute: name is not bySide!";
		return false;
	}
	const char* pszVal_bySide = pElemChild->Attribute("value");
	if(pszVal_bySide == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_bySide, s.bySide))
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
	return true;
}

bool ToXML(const SEffectSummon& s, TiXmlElement& rElement)
{
	rElement.SetValue("SEffectSummon");
	rElement.SetAttribute("type", ToUTF8Ptr("召唤效果"));
	unique_ptr<TiXmlElement> pElem_SEffectBase(new TiXmlElement("SEffectBase"));
	if(pElem_SEffectBase == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const SEffectBase&)s, *pElem_SEffectBase))
	{
		LOG_CRI << "SEffectBase ToXML fails!";
		return false;
	}
	pElem_SEffectBase->SetAttribute("type", ToUTF8Ptr("战斗基础效果类型"));
	pElem_SEffectBase->SetAttribute("comment", ToUTF8Ptr("父类SEffectBase部分"));
	if(rElement.LinkEndChild(pElem_SEffectBase.get()) != NULL)
		pElem_SEffectBase.release();
	unique_ptr<TiXmlElement> pElem_byGroupID(new TiXmlElement("UINT8"));
	if(pElem_byGroupID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byGroupID->SetAttribute("name", "byGroupID");
	pElem_byGroupID->SetAttribute("value", NumberToString(s.byGroupID).c_str());
	pElem_byGroupID->SetAttribute("comment", ToUTF8Ptr("组编号"));
	if(rElement.LinkEndChild(pElem_byGroupID.get()) != NULL)
		pElem_byGroupID.release();
	unique_ptr<TiXmlElement> pElem_bySide(new TiXmlElement("UINT8"));
	if(pElem_bySide == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_bySide->SetAttribute("name", "bySide");
	pElem_bySide->SetAttribute("value", NumberToString(s.bySide).c_str());
	pElem_bySide->SetAttribute("comment", ToUTF8Ptr("方向编号"));
	if(rElement.LinkEndChild(pElem_bySide.get()) != NULL)
		pElem_bySide.release();
	unique_ptr<TiXmlElement> pElem_byPos(new TiXmlElement("UINT8"));
	if(pElem_byPos == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byPos->SetAttribute("name", "byPos");
	pElem_byPos->SetAttribute("value", NumberToString(s.byPos).c_str());
	pElem_byPos->SetAttribute("comment", ToUTF8Ptr("位置编号"));
	if(rElement.LinkEndChild(pElem_byPos.get()) != NULL)
		pElem_byPos.release();
	unique_ptr<TiXmlElement> pElem_wFighterID(new TiXmlElement("UINT16"));
	if(pElem_wFighterID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wFighterID->SetAttribute("name", "wFighterID");
	pElem_wFighterID->SetAttribute("value", NumberToString(s.wFighterID).c_str());
	pElem_wFighterID->SetAttribute("comment", ToUTF8Ptr("散仙ID"));
	if(rElement.LinkEndChild(pElem_wFighterID.get()) != NULL)
		pElem_wFighterID.release();
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
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecSummon& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SEffectSummonPtr p(new SEffectSummon);
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

bool VectorToXML(const TVecSummon& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SEffectSummon"));
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

SEffectDialog::SEffectDialog() : dwID(0) { }

CInArchive& operator>>(CInArchive& src, SEffectDialog& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (SEffectBase&)s;
	src >> s.dwID;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SEffectDialog& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const SEffectBase&)s;
	src << s.dwID;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecDialog& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SEffectDialogPtr p(new SEffectDialog);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecDialog& vec)
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

bool FromXML(TiXmlElement& rElement, SEffectDialog& s)
{
	if(strcmp(rElement.Value(), "SEffectDialog") != 0)
	{
		LOG_CRI << "rElement is not SEffectDialog!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for SEffectBase is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (SEffectBase&)s))
	{
		LOG_CRI << "FromXML for: SEffectBase fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwID") != 0)
	{
		LOG_CRI << "Attribute: name is not dwID!";
		return false;
	}
	const char* pszVal_dwID = pElemChild->Attribute("value");
	if(pszVal_dwID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwID, s.dwID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SEffectDialog& s, TiXmlElement& rElement)
{
	rElement.SetValue("SEffectDialog");
	rElement.SetAttribute("type", ToUTF8Ptr("对话效果"));
	unique_ptr<TiXmlElement> pElem_SEffectBase(new TiXmlElement("SEffectBase"));
	if(pElem_SEffectBase == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const SEffectBase&)s, *pElem_SEffectBase))
	{
		LOG_CRI << "SEffectBase ToXML fails!";
		return false;
	}
	pElem_SEffectBase->SetAttribute("type", ToUTF8Ptr("战斗基础效果类型"));
	pElem_SEffectBase->SetAttribute("comment", ToUTF8Ptr("父类SEffectBase部分"));
	if(rElement.LinkEndChild(pElem_SEffectBase.get()) != NULL)
		pElem_SEffectBase.release();
	unique_ptr<TiXmlElement> pElem_dwID(new TiXmlElement("UINT32"));
	if(pElem_dwID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwID->SetAttribute("name", "dwID");
	pElem_dwID->SetAttribute("value", NumberToString(s.dwID).c_str());
	pElem_dwID->SetAttribute("comment", ToUTF8Ptr("对话ID"));
	if(rElement.LinkEndChild(pElem_dwID.get()) != NULL)
		pElem_dwID.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecDialog& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SEffectDialogPtr p(new SEffectDialog);
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

bool VectorToXML(const TVecDialog& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SEffectDialog"));
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

SEffectTransform::SEffectTransform() : wFeatureID(0) { }

CInArchive& operator>>(CInArchive& src, SEffectTransform& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (SEffectBase&)s;
	src >> s.wFeatureID;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SEffectTransform& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const SEffectBase&)s;
	src << s.wFeatureID;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecTransform& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SEffectTransformPtr p(new SEffectTransform);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecTransform& vec)
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

bool FromXML(TiXmlElement& rElement, SEffectTransform& s)
{
	if(strcmp(rElement.Value(), "SEffectTransform") != 0)
	{
		LOG_CRI << "rElement is not SEffectTransform!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for SEffectBase is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (SEffectBase&)s))
	{
		LOG_CRI << "FromXML for: SEffectBase fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wFeatureID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wFeatureID") != 0)
	{
		LOG_CRI << "Attribute: name is not wFeatureID!";
		return false;
	}
	const char* pszVal_wFeatureID = pElemChild->Attribute("value");
	if(pszVal_wFeatureID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wFeatureID, s.wFeatureID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SEffectTransform& s, TiXmlElement& rElement)
{
	rElement.SetValue("SEffectTransform");
	rElement.SetAttribute("type", ToUTF8Ptr("变身效果"));
	unique_ptr<TiXmlElement> pElem_SEffectBase(new TiXmlElement("SEffectBase"));
	if(pElem_SEffectBase == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const SEffectBase&)s, *pElem_SEffectBase))
	{
		LOG_CRI << "SEffectBase ToXML fails!";
		return false;
	}
	pElem_SEffectBase->SetAttribute("type", ToUTF8Ptr("战斗基础效果类型"));
	pElem_SEffectBase->SetAttribute("comment", ToUTF8Ptr("父类SEffectBase部分"));
	if(rElement.LinkEndChild(pElem_SEffectBase.get()) != NULL)
		pElem_SEffectBase.release();
	unique_ptr<TiXmlElement> pElem_wFeatureID(new TiXmlElement("UINT16"));
	if(pElem_wFeatureID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wFeatureID->SetAttribute("name", "wFeatureID");
	pElem_wFeatureID->SetAttribute("value", NumberToString(s.wFeatureID).c_str());
	pElem_wFeatureID->SetAttribute("comment", ToUTF8Ptr("模型ID"));
	if(rElement.LinkEndChild(pElem_wFeatureID.get()) != NULL)
		pElem_wFeatureID.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecTransform& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SEffectTransformPtr p(new SEffectTransform);
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

bool VectorToXML(const TVecTransform& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SEffectTransform"));
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

SEffectPartBroken::SEffectPartBroken() : wPartID(0) { }

CInArchive& operator>>(CInArchive& src, SEffectPartBroken& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (SEffectBase&)s;
	src >> s.wPartID;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SEffectPartBroken& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const SEffectBase&)s;
	src << s.wPartID;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecPartBorken& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SEffectPartBrokenPtr p(new SEffectPartBroken);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecPartBorken& vec)
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

bool FromXML(TiXmlElement& rElement, SEffectPartBroken& s)
{
	if(strcmp(rElement.Value(), "SEffectPartBroken") != 0)
	{
		LOG_CRI << "rElement is not SEffectPartBroken!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for SEffectBase is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (SEffectBase&)s))
	{
		LOG_CRI << "FromXML for: SEffectBase fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wPartID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wPartID") != 0)
	{
		LOG_CRI << "Attribute: name is not wPartID!";
		return false;
	}
	const char* pszVal_wPartID = pElemChild->Attribute("value");
	if(pszVal_wPartID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wPartID, s.wPartID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SEffectPartBroken& s, TiXmlElement& rElement)
{
	rElement.SetValue("SEffectPartBroken");
	rElement.SetAttribute("type", ToUTF8Ptr("部位破坏"));
	unique_ptr<TiXmlElement> pElem_SEffectBase(new TiXmlElement("SEffectBase"));
	if(pElem_SEffectBase == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const SEffectBase&)s, *pElem_SEffectBase))
	{
		LOG_CRI << "SEffectBase ToXML fails!";
		return false;
	}
	pElem_SEffectBase->SetAttribute("type", ToUTF8Ptr("战斗基础效果类型"));
	pElem_SEffectBase->SetAttribute("comment", ToUTF8Ptr("父类SEffectBase部分"));
	if(rElement.LinkEndChild(pElem_SEffectBase.get()) != NULL)
		pElem_SEffectBase.release();
	unique_ptr<TiXmlElement> pElem_wPartID(new TiXmlElement("UINT16"));
	if(pElem_wPartID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wPartID->SetAttribute("name", "wPartID");
	pElem_wPartID->SetAttribute("value", NumberToString(s.wPartID).c_str());
	pElem_wPartID->SetAttribute("comment", ToUTF8Ptr("部位ID"));
	if(rElement.LinkEndChild(pElem_wPartID.get()) != NULL)
		pElem_wPartID.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecPartBorken& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SEffectPartBrokenPtr p(new SEffectPartBroken);
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

bool VectorToXML(const TVecPartBorken& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SEffectPartBroken"));
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

SEffectBuffAction::SEffectBuffAction() : dwSkillID(0) { }

CInArchive& operator>>(CInArchive& src, SEffectBuffAction& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (SEffectBase&)s;
	src >> s.dwSkillID;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SEffectBuffAction& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const SEffectBase&)s;
	src << s.dwSkillID;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecBuffAction& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SEffectBuffActionPtr p(new SEffectBuffAction);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecBuffAction& vec)
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

bool FromXML(TiXmlElement& rElement, SEffectBuffAction& s)
{
	if(strcmp(rElement.Value(), "SEffectBuffAction") != 0)
	{
		LOG_CRI << "rElement is not SEffectBuffAction!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for SEffectBase is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (SEffectBase&)s))
	{
		LOG_CRI << "FromXML for: SEffectBase fails!";
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

bool ToXML(const SEffectBuffAction& s, TiXmlElement& rElement)
{
	rElement.SetValue("SEffectBuffAction");
	rElement.SetAttribute("type", ToUTF8Ptr("被动技能出手动作"));
	unique_ptr<TiXmlElement> pElem_SEffectBase(new TiXmlElement("SEffectBase"));
	if(pElem_SEffectBase == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const SEffectBase&)s, *pElem_SEffectBase))
	{
		LOG_CRI << "SEffectBase ToXML fails!";
		return false;
	}
	pElem_SEffectBase->SetAttribute("type", ToUTF8Ptr("战斗基础效果类型"));
	pElem_SEffectBase->SetAttribute("comment", ToUTF8Ptr("父类SEffectBase部分"));
	if(rElement.LinkEndChild(pElem_SEffectBase.get()) != NULL)
		pElem_SEffectBase.release();
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

bool VectorFromXML(TiXmlElement& rElement, TVecBuffAction& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SEffectBuffActionPtr p(new SEffectBuffAction);
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

bool VectorToXML(const TVecBuffAction& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SEffectBuffAction"));
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

SBattleTargetPos::SBattleTargetPos() : byGroupID(0), byPos(0) { }

SBattleTargetPos::SBattleTargetPos(UINT8 byGroupID_, UINT8 byPos_) : byGroupID(byGroupID_), byPos(byPos_) { }

CInArchive& operator>>(CInArchive& src, SBattleTargetPos& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.byGroupID;
	src >> s.byPos;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SBattleTargetPos& s)
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
	src << s.byPos;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SBattleTargetPos& s)
{
	if(strcmp(rElement.Value(), "SBattleTargetPos") != 0)
	{
		LOG_CRI << "rElement is not SBattleTargetPos!";
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
	return true;
}

bool ToXML(const SBattleTargetPos& s, TiXmlElement& rElement)
{
	rElement.SetValue("SBattleTargetPos");
	rElement.SetAttribute("type", ToUTF8Ptr("目标位置，由组ID和位置唯一能找到坐标"));
	unique_ptr<TiXmlElement> pElem_byGroupID(new TiXmlElement("UINT8"));
	if(pElem_byGroupID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byGroupID->SetAttribute("name", "byGroupID");
	pElem_byGroupID->SetAttribute("value", NumberToString(s.byGroupID).c_str());
	pElem_byGroupID->SetAttribute("comment", ToUTF8Ptr("组ID"));
	if(rElement.LinkEndChild(pElem_byGroupID.get()) != NULL)
		pElem_byGroupID.release();
	unique_ptr<TiXmlElement> pElem_byPos(new TiXmlElement("UINT8"));
	if(pElem_byPos == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byPos->SetAttribute("name", "byPos");
	pElem_byPos->SetAttribute("value", NumberToString(s.byPos).c_str());
	pElem_byPos->SetAttribute("comment", ToUTF8Ptr("位置ID"));
	if(rElement.LinkEndChild(pElem_byPos.get()) != NULL)
		pElem_byPos.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecBattleTargetPos& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SBattleTargetPos s;
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

bool VectorToXML(const TVecBattleTargetPos& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SBattleTargetPos"));
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

SBattleProgress::SBattleProgress() : dwSkillID(0) { }

SBattleProgress::SBattleProgress(SBattleProgress&& src) : vecCasterIndex(src.vecCasterIndex), vEffectsBefore(move(src.vEffectsBefore)), dwSkillID(src.dwSkillID), vTargetID(src.vTargetID), vTargetIDEx(src.vTargetIDEx), 
			vTargetPos(move(src.vTargetPos)), vSkillEffects(move(src.vSkillEffects)), vEffectsAfter(move(src.vEffectsAfter)) { }

SBattleProgress& SBattleProgress::operator=(SBattleProgress&& rhs)
{
	if(this != &rhs)
	{
		this->~SBattleProgress();
		new (this) SBattleProgress(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SBattleProgress& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.vecCasterIndex;
	src >> s.vEffectsBefore;
	src >> s.dwSkillID;
	src >> s.vTargetID;
	src >> s.vTargetIDEx;
	src >> s.vTargetPos;
	src >> s.vSkillEffects;
	src >> s.vEffectsAfter;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SBattleProgress& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.vecCasterIndex;
	src << s.vEffectsBefore;
	src << s.dwSkillID;
	src << s.vTargetID;
	src << s.vTargetIDEx;
	src << s.vTargetPos;
	src << s.vSkillEffects;
	src << s.vEffectsAfter;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SBattleProgress& s)
{
	if(strcmp(rElement.Value(), "SBattleProgress") != 0)
	{
		LOG_CRI << "rElement is not SBattleProgress!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecCasterIndex is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecUINT8") != 0)
	{
		LOG_CRI << "pElemChild is not TVecUINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecCasterIndex") != 0)
	{
		LOG_CRI << "Attribute: name is not vecCasterIndex!";
		return false;
	}
	const char* pszText_vecCasterIndex = pElemChild->GetText();
	if(pszText_vecCasterIndex != NULL)
		SplitToNumber(pszText_vecCasterIndex, ",", s.vecCasterIndex);
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vEffectsBefore is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecEffects") != 0)
	{
		LOG_CRI << "pElemChild is not TVecEffects!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vEffectsBefore") != 0)
	{
		LOG_CRI << "Attribute: name is not vEffectsBefore!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vEffectsBefore))
	{
		LOG_CRI << "VectorFromXML for vEffectsBefore fails!";
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
		LOG_CRI << "pElemChild for vTargetID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecUINT8") != 0)
	{
		LOG_CRI << "pElemChild is not TVecUINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vTargetID") != 0)
	{
		LOG_CRI << "Attribute: name is not vTargetID!";
		return false;
	}
	const char* pszText_vTargetID = pElemChild->GetText();
	if(pszText_vTargetID != NULL)
		SplitToNumber(pszText_vTargetID, ",", s.vTargetID);
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vTargetIDEx is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecUINT8") != 0)
	{
		LOG_CRI << "pElemChild is not TVecUINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vTargetIDEx") != 0)
	{
		LOG_CRI << "Attribute: name is not vTargetIDEx!";
		return false;
	}
	const char* pszText_vTargetIDEx = pElemChild->GetText();
	if(pszText_vTargetIDEx != NULL)
		SplitToNumber(pszText_vTargetIDEx, ",", s.vTargetIDEx);
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vTargetPos is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecBattleTargetPos") != 0)
	{
		LOG_CRI << "pElemChild is not TVecBattleTargetPos!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vTargetPos") != 0)
	{
		LOG_CRI << "Attribute: name is not vTargetPos!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vTargetPos))
	{
		LOG_CRI << "VectorFromXML for vTargetPos fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vSkillEffects is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecEffects") != 0)
	{
		LOG_CRI << "pElemChild is not TVecEffects!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vSkillEffects") != 0)
	{
		LOG_CRI << "Attribute: name is not vSkillEffects!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vSkillEffects))
	{
		LOG_CRI << "VectorFromXML for vSkillEffects fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vEffectsAfter is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecEffects") != 0)
	{
		LOG_CRI << "pElemChild is not TVecEffects!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vEffectsAfter") != 0)
	{
		LOG_CRI << "Attribute: name is not vEffectsAfter!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vEffectsAfter))
	{
		LOG_CRI << "VectorFromXML for vEffectsAfter fails!";
		return false;
	}
	return true;
}

bool ToXML(const SBattleProgress& s, TiXmlElement& rElement)
{
	rElement.SetValue("SBattleProgress");
	rElement.SetAttribute("type", ToUTF8Ptr("某个fighter一次出手"));
	unique_ptr<TiXmlElement> pElem_vecCasterIndex(new TiXmlElement("TVecUINT8"));
	if(pElem_vecCasterIndex == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecCasterIndex->SetAttribute("name", "vecCasterIndex");
	string strText_vecCasterIndex;
	for(size_t i = 0; i < s.vecCasterIndex.size(); ++i)
	{
		if(i > 0)
			strText_vecCasterIndex += ", ";
		strText_vecCasterIndex += NumberToString(s.vecCasterIndex[i]);
	}
	unique_ptr<TiXmlText> pText_vecCasterIndex(new TiXmlText(strText_vecCasterIndex.c_str()));
	if(pText_vecCasterIndex == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(pElem_vecCasterIndex->LinkEndChild(pText_vecCasterIndex.get()) != NULL)
		pText_vecCasterIndex.release();
	pElem_vecCasterIndex->SetAttribute("comment", ToUTF8Ptr("主犯(255代表入场技能或者场景技能"));
	if(rElement.LinkEndChild(pElem_vecCasterIndex.get()) != NULL)
		pElem_vecCasterIndex.release();
	unique_ptr<TiXmlElement> pElem_vEffectsBefore(new TiXmlElement("TVecEffects"));
	if(pElem_vEffectsBefore == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vEffectsBefore->SetAttribute("name", "vEffectsBefore");
	if(!VectorToXML(s.vEffectsBefore, *pElem_vEffectsBefore))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vEffectsBefore->SetAttribute("comment", ToUTF8Ptr("主犯施法前的效果列表"));
	if(rElement.LinkEndChild(pElem_vEffectsBefore.get()) != NULL)
		pElem_vEffectsBefore.release();
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
	unique_ptr<TiXmlElement> pElem_vTargetID(new TiXmlElement("TVecUINT8"));
	if(pElem_vTargetID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vTargetID->SetAttribute("name", "vTargetID");
	string strText_vTargetID;
	for(size_t i = 0; i < s.vTargetID.size(); ++i)
	{
		if(i > 0)
			strText_vTargetID += ", ";
		strText_vTargetID += NumberToString(s.vTargetID[i]);
	}
	unique_ptr<TiXmlText> pText_vTargetID(new TiXmlText(strText_vTargetID.c_str()));
	if(pText_vTargetID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(pElem_vTargetID->LinkEndChild(pText_vTargetID.get()) != NULL)
		pText_vTargetID.release();
	pElem_vTargetID->SetAttribute("comment", ToUTF8Ptr("所有目标ID"));
	if(rElement.LinkEndChild(pElem_vTargetID.get()) != NULL)
		pElem_vTargetID.release();
	unique_ptr<TiXmlElement> pElem_vTargetIDEx(new TiXmlElement("TVecUINT8"));
	if(pElem_vTargetIDEx == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vTargetIDEx->SetAttribute("name", "vTargetIDEx");
	string strText_vTargetIDEx;
	for(size_t i = 0; i < s.vTargetIDEx.size(); ++i)
	{
		if(i > 0)
			strText_vTargetIDEx += ", ";
		strText_vTargetIDEx += NumberToString(s.vTargetIDEx[i]);
	}
	unique_ptr<TiXmlText> pText_vTargetIDEx(new TiXmlText(strText_vTargetIDEx.c_str()));
	if(pText_vTargetIDEx == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(pElem_vTargetIDEx->LinkEndChild(pText_vTargetIDEx.get()) != NULL)
		pText_vTargetIDEx.release();
	pElem_vTargetIDEx->SetAttribute("comment", ToUTF8Ptr("波及目标ID"));
	if(rElement.LinkEndChild(pElem_vTargetIDEx.get()) != NULL)
		pElem_vTargetIDEx.release();
	unique_ptr<TiXmlElement> pElem_vTargetPos(new TiXmlElement("TVecBattleTargetPos"));
	if(pElem_vTargetPos == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vTargetPos->SetAttribute("name", "vTargetPos");
	if(!VectorToXML(s.vTargetPos, *pElem_vTargetPos))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vTargetPos->SetAttribute("comment", ToUTF8Ptr("技能主执行覆盖区域位置"));
	if(rElement.LinkEndChild(pElem_vTargetPos.get()) != NULL)
		pElem_vTargetPos.release();
	unique_ptr<TiXmlElement> pElem_vSkillEffects(new TiXmlElement("TVecEffects"));
	if(pElem_vSkillEffects == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vSkillEffects->SetAttribute("name", "vSkillEffects");
	if(!VectorToXML(s.vSkillEffects, *pElem_vSkillEffects))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vSkillEffects->SetAttribute("comment", ToUTF8Ptr("技能效果列表"));
	if(rElement.LinkEndChild(pElem_vSkillEffects.get()) != NULL)
		pElem_vSkillEffects.release();
	unique_ptr<TiXmlElement> pElem_vEffectsAfter(new TiXmlElement("TVecEffects"));
	if(pElem_vEffectsAfter == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vEffectsAfter->SetAttribute("name", "vEffectsAfter");
	if(!VectorToXML(s.vEffectsAfter, *pElem_vEffectsAfter))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vEffectsAfter->SetAttribute("comment", ToUTF8Ptr("主犯施法后效果列表"));
	if(rElement.LinkEndChild(pElem_vEffectsAfter.get()) != NULL)
		pElem_vEffectsAfter.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecBattleProgress& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SBattleProgress s;
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

bool VectorToXML(const TVecBattleProgress& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SBattleProgress"));
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

SBattleRound::SBattleRound() : dwRounds(0) { }

SBattleRound::SBattleRound(UINT32 dwRounds_, const TVecBattleProgress& vTargets_) : dwRounds(dwRounds_), vTargets(vTargets_) { }

SBattleRound::SBattleRound(SBattleRound&& src) : dwRounds(src.dwRounds), vTargets(move(src.vTargets)) { }

SBattleRound& SBattleRound::operator=(SBattleRound&& rhs)
{
	if(this != &rhs)
	{
		this->~SBattleRound();
		new (this) SBattleRound(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SBattleRound& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.dwRounds;
	src >> s.vTargets;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SBattleRound& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.dwRounds;
	src << s.vTargets;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SBattleRound& s)
{
	if(strcmp(rElement.Value(), "SBattleRound") != 0)
	{
		LOG_CRI << "rElement is not SBattleRound!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwRounds is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwRounds") != 0)
	{
		LOG_CRI << "Attribute: name is not dwRounds!";
		return false;
	}
	const char* pszVal_dwRounds = pElemChild->Attribute("value");
	if(pszVal_dwRounds == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwRounds, s.dwRounds))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vTargets is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecBattleProgress") != 0)
	{
		LOG_CRI << "pElemChild is not TVecBattleProgress!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vTargets") != 0)
	{
		LOG_CRI << "Attribute: name is not vTargets!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vTargets))
	{
		LOG_CRI << "VectorFromXML for vTargets fails!";
		return false;
	}
	return true;
}

bool ToXML(const SBattleRound& s, TiXmlElement& rElement)
{
	rElement.SetValue("SBattleRound");
	rElement.SetAttribute("type", ToUTF8Ptr("一个回合（所有队伍都出手一次）"));
	unique_ptr<TiXmlElement> pElem_dwRounds(new TiXmlElement("UINT32"));
	if(pElem_dwRounds == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwRounds->SetAttribute("name", "dwRounds");
	pElem_dwRounds->SetAttribute("value", NumberToString(s.dwRounds).c_str());
	pElem_dwRounds->SetAttribute("comment", ToUTF8Ptr("当前回合数"));
	if(rElement.LinkEndChild(pElem_dwRounds.get()) != NULL)
		pElem_dwRounds.release();
	unique_ptr<TiXmlElement> pElem_vTargets(new TiXmlElement("TVecBattleProgress"));
	if(pElem_vTargets == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vTargets->SetAttribute("name", "vTargets");
	if(!VectorToXML(s.vTargets, *pElem_vTargets))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vTargets->SetAttribute("comment", ToUTF8Ptr("其它人出手"));
	if(rElement.LinkEndChild(pElem_vTargets.get()) != NULL)
		pElem_vTargets.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecBattleRound& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SBattleRound s;
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

bool VectorToXML(const TVecBattleRound& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SBattleRound"));
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

SBattleReport::SBattleReport() : qwBattleID(0), qwNextBattleID(0), wSceneID(0), by1Vs1(0), eType((EBattleType)0), 
			byAWaves(0), byBWaves(0), eResult((EBattleResult)0) { }

SBattleReport::SBattleReport(SBattleReport&& src) : qwBattleID(src.qwBattleID), qwNextBattleID(src.qwNextBattleID), wSceneID(src.wSceneID), by1Vs1(src.by1Vs1), eType(src.eType), 
			vAGroups(move(src.vAGroups)), vBGroups(move(src.vBGroups)), vSummons(move(src.vSummons)), vRound(move(src.vRound)), byAWaves(src.byAWaves), 
			byBWaves(src.byBWaves), eResult(src.eResult), vecItem(move(src.vecItem)), vecResSource(move(src.vecResSource)) { }

SBattleReport& SBattleReport::operator=(SBattleReport&& rhs)
{
	if(this != &rhs)
	{
		this->~SBattleReport();
		new (this) SBattleReport(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SBattleReport& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwBattleID;
	src >> s.qwNextBattleID;
	src >> s.wSceneID;
	src >> s.by1Vs1;
	src >> (UINT8&)s.eType;
	src >> s.vAGroups;
	src >> s.vBGroups;
	src >> s.vSummons;
	src >> s.vRound;
	src >> s.byAWaves;
	src >> s.byBWaves;
	src >> (UINT8&)s.eResult;
	src >> s.vecItem;
	src >> s.vecResSource;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SBattleReport& s)
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
	src << s.qwNextBattleID;
	src << s.wSceneID;
	src << s.by1Vs1;
	src << (UINT8&)s.eType;
	src << s.vAGroups;
	src << s.vBGroups;
	src << s.vSummons;
	src << s.vRound;
	src << s.byAWaves;
	src << s.byBWaves;
	src << (UINT8&)s.eResult;
	src << s.vecItem;
	src << s.vecResSource;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SBattleReport& s)
{
	if(strcmp(rElement.Value(), "SBattleReport") != 0)
	{
		LOG_CRI << "rElement is not SBattleReport!";
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
		LOG_CRI << "pElemChild for qwNextBattleID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwNextBattleID") != 0)
	{
		LOG_CRI << "Attribute: name is not qwNextBattleID!";
		return false;
	}
	const char* pszVal_qwNextBattleID = pElemChild->Attribute("value");
	if(pszVal_qwNextBattleID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwNextBattleID, s.qwNextBattleID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wSceneID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wSceneID") != 0)
	{
		LOG_CRI << "Attribute: name is not wSceneID!";
		return false;
	}
	const char* pszVal_wSceneID = pElemChild->Attribute("value");
	if(pszVal_wSceneID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wSceneID, s.wSceneID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for by1Vs1 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "by1Vs1") != 0)
	{
		LOG_CRI << "Attribute: name is not by1Vs1!";
		return false;
	}
	const char* pszVal_by1Vs1 = pElemChild->Attribute("value");
	if(pszVal_by1Vs1 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_by1Vs1, s.by1Vs1))
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
	if(strcmp(pElemChild->Value(), "EBattleType") != 0)
	{
		LOG_CRI << "pElemChild is not EBattleType!";
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
		LOG_CRI << "pElemChild for vAGroups is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecBattleGroup") != 0)
	{
		LOG_CRI << "pElemChild is not TVecBattleGroup!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vAGroups") != 0)
	{
		LOG_CRI << "Attribute: name is not vAGroups!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vAGroups))
	{
		LOG_CRI << "VectorFromXML for vAGroups fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vBGroups is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecBattleGroup") != 0)
	{
		LOG_CRI << "pElemChild is not TVecBattleGroup!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vBGroups") != 0)
	{
		LOG_CRI << "Attribute: name is not vBGroups!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vBGroups))
	{
		LOG_CRI << "VectorFromXML for vBGroups fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vSummons is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecBattleFighter") != 0)
	{
		LOG_CRI << "pElemChild is not TVecBattleFighter!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vSummons") != 0)
	{
		LOG_CRI << "Attribute: name is not vSummons!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vSummons))
	{
		LOG_CRI << "VectorFromXML for vSummons fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vRound is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecBattleRound") != 0)
	{
		LOG_CRI << "pElemChild is not TVecBattleRound!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vRound") != 0)
	{
		LOG_CRI << "Attribute: name is not vRound!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vRound))
	{
		LOG_CRI << "VectorFromXML for vRound fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byAWaves is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byAWaves") != 0)
	{
		LOG_CRI << "Attribute: name is not byAWaves!";
		return false;
	}
	const char* pszVal_byAWaves = pElemChild->Attribute("value");
	if(pszVal_byAWaves == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byAWaves, s.byAWaves))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byBWaves is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byBWaves") != 0)
	{
		LOG_CRI << "Attribute: name is not byBWaves!";
		return false;
	}
	const char* pszVal_byBWaves = pElemChild->Attribute("value");
	if(pszVal_byBWaves == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byBWaves, s.byBWaves))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eResult is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "EBattleResult") != 0)
	{
		LOG_CRI << "pElemChild is not EBattleResult!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eResult") != 0)
	{
		LOG_CRI << "Attribute: name is not eResult!";
		return false;
	}
	const char* pszVal_eResult = pElemChild->Attribute("value");
	if(pszVal_eResult == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!EnumStrToVal(pszVal_eResult, s.eResult))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecItem is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "ItemProt::TVecItemGenInfo") != 0)
	{
		LOG_CRI << "pElemChild is not ItemProt::TVecItemGenInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecItem") != 0)
	{
		LOG_CRI << "Attribute: name is not vecItem!";
		return false;
	}
	if(!NItemProt::VectorFromXML(*pElemChild, s.vecItem))
	{
		LOG_CRI << "VectorFromXML for vecItem fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecResSource is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "ItemProt::TVecResource") != 0)
	{
		LOG_CRI << "pElemChild is not ItemProt::TVecResource!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecResSource") != 0)
	{
		LOG_CRI << "Attribute: name is not vecResSource!";
		return false;
	}
	if(!NItemProt::VectorFromXML(*pElemChild, s.vecResSource))
	{
		LOG_CRI << "VectorFromXML for vecResSource fails!";
		return false;
	}
	return true;
}

bool ToXML(const SBattleReport& s, TiXmlElement& rElement)
{
	rElement.SetValue("SBattleReport");
	rElement.SetAttribute("type", ToUTF8Ptr("战报"));
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
	unique_ptr<TiXmlElement> pElem_qwNextBattleID(new TiXmlElement("UINT64"));
	if(pElem_qwNextBattleID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwNextBattleID->SetAttribute("name", "qwNextBattleID");
	pElem_qwNextBattleID->SetAttribute("value", NumberToString(s.qwNextBattleID).c_str());
	pElem_qwNextBattleID->SetAttribute("comment", ToUTF8Ptr("next战报ID"));
	if(rElement.LinkEndChild(pElem_qwNextBattleID.get()) != NULL)
		pElem_qwNextBattleID.release();
	unique_ptr<TiXmlElement> pElem_wSceneID(new TiXmlElement("UINT16"));
	if(pElem_wSceneID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wSceneID->SetAttribute("name", "wSceneID");
	pElem_wSceneID->SetAttribute("value", NumberToString(s.wSceneID).c_str());
	pElem_wSceneID->SetAttribute("comment", ToUTF8Ptr("战斗场景ID"));
	if(rElement.LinkEndChild(pElem_wSceneID.get()) != NULL)
		pElem_wSceneID.release();
	unique_ptr<TiXmlElement> pElem_by1Vs1(new TiXmlElement("UINT8"));
	if(pElem_by1Vs1 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_by1Vs1->SetAttribute("name", "by1Vs1");
	pElem_by1Vs1->SetAttribute("value", NumberToString(s.by1Vs1).c_str());
	pElem_by1Vs1->SetAttribute("comment", ToUTF8Ptr("0:普通一打多，1：普通一打一，2：boss一打多， 3：boss一打一"));
	if(rElement.LinkEndChild(pElem_by1Vs1.get()) != NULL)
		pElem_by1Vs1.release();
	unique_ptr<TiXmlElement> pElem_eType(new TiXmlElement("EBattleType"));
	if(pElem_eType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eType->SetAttribute("name", "eType");
	const char* pszEnum_eType = EnumValToStr(s.eType);
	if(pszEnum_eType == NULL)
	{
		LOG_CRI << "EnumValToStr for EBattleType fails!";
		return false;
	}
	pElem_eType->SetAttribute("value", pszEnum_eType);
	pElem_eType->SetAttribute("comment", ToUTF8Ptr("战斗模式：PVP/PVE"));
	if(rElement.LinkEndChild(pElem_eType.get()) != NULL)
		pElem_eType.release();
	unique_ptr<TiXmlElement> pElem_vAGroups(new TiXmlElement("TVecBattleGroup"));
	if(pElem_vAGroups == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vAGroups->SetAttribute("name", "vAGroups");
	if(!VectorToXML(s.vAGroups, *pElem_vAGroups))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vAGroups->SetAttribute("comment", ToUTF8Ptr("A队伍里的所有小组"));
	if(rElement.LinkEndChild(pElem_vAGroups.get()) != NULL)
		pElem_vAGroups.release();
	unique_ptr<TiXmlElement> pElem_vBGroups(new TiXmlElement("TVecBattleGroup"));
	if(pElem_vBGroups == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vBGroups->SetAttribute("name", "vBGroups");
	if(!VectorToXML(s.vBGroups, *pElem_vBGroups))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vBGroups->SetAttribute("comment", ToUTF8Ptr("B队伍里的所有小组"));
	if(rElement.LinkEndChild(pElem_vBGroups.get()) != NULL)
		pElem_vBGroups.release();
	unique_ptr<TiXmlElement> pElem_vSummons(new TiXmlElement("TVecBattleFighter"));
	if(pElem_vSummons == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vSummons->SetAttribute("name", "vSummons");
	if(!VectorToXML(s.vSummons, *pElem_vSummons))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vSummons->SetAttribute("comment", ToUTF8Ptr("战斗中可能召唤的散仙"));
	if(rElement.LinkEndChild(pElem_vSummons.get()) != NULL)
		pElem_vSummons.release();
	unique_ptr<TiXmlElement> pElem_vRound(new TiXmlElement("TVecBattleRound"));
	if(pElem_vRound == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vRound->SetAttribute("name", "vRound");
	if(!VectorToXML(s.vRound, *pElem_vRound))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vRound->SetAttribute("comment", ToUTF8Ptr("所有的出手回合"));
	if(rElement.LinkEndChild(pElem_vRound.get()) != NULL)
		pElem_vRound.release();
	unique_ptr<TiXmlElement> pElem_byAWaves(new TiXmlElement("UINT8"));
	if(pElem_byAWaves == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byAWaves->SetAttribute("name", "byAWaves");
	pElem_byAWaves->SetAttribute("value", NumberToString(s.byAWaves).c_str());
	pElem_byAWaves->SetAttribute("comment", ToUTF8Ptr("A队剩余波数"));
	if(rElement.LinkEndChild(pElem_byAWaves.get()) != NULL)
		pElem_byAWaves.release();
	unique_ptr<TiXmlElement> pElem_byBWaves(new TiXmlElement("UINT8"));
	if(pElem_byBWaves == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byBWaves->SetAttribute("name", "byBWaves");
	pElem_byBWaves->SetAttribute("value", NumberToString(s.byBWaves).c_str());
	pElem_byBWaves->SetAttribute("comment", ToUTF8Ptr("B队剩余波数"));
	if(rElement.LinkEndChild(pElem_byBWaves.get()) != NULL)
		pElem_byBWaves.release();
	unique_ptr<TiXmlElement> pElem_eResult(new TiXmlElement("EBattleResult"));
	if(pElem_eResult == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eResult->SetAttribute("name", "eResult");
	const char* pszEnum_eResult = EnumValToStr(s.eResult);
	if(pszEnum_eResult == NULL)
	{
		LOG_CRI << "EnumValToStr for EBattleResult fails!";
		return false;
	}
	pElem_eResult->SetAttribute("value", pszEnum_eResult);
	pElem_eResult->SetAttribute("comment", ToUTF8Ptr("战斗结果"));
	if(rElement.LinkEndChild(pElem_eResult.get()) != NULL)
		pElem_eResult.release();
	unique_ptr<TiXmlElement> pElem_vecItem(new TiXmlElement("ItemProt::TVecItemGenInfo"));
	if(pElem_vecItem == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecItem->SetAttribute("name", "vecItem");
	if(!NItemProt::VectorToXML(s.vecItem, *pElem_vecItem))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecItem->SetAttribute("comment", ToUTF8Ptr("获得物品"));
	if(rElement.LinkEndChild(pElem_vecItem.get()) != NULL)
		pElem_vecItem.release();
	unique_ptr<TiXmlElement> pElem_vecResSource(new TiXmlElement("ItemProt::TVecResource"));
	if(pElem_vecResSource == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecResSource->SetAttribute("name", "vecResSource");
	if(!NItemProt::VectorToXML(s.vecResSource, *pElem_vecResSource))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecResSource->SetAttribute("comment", ToUTF8Ptr("获得资源"));
	if(rElement.LinkEndChild(pElem_vecResSource.get()) != NULL)
		pElem_vecResSource.release();
	return true;
}

#endif

NewSBattleReport::NewSBattleReport() : qwHash(0) { }

CInArchive& operator>>(CInArchive& src, NewSBattleReport& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwHash;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const NewSBattleReport& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.qwHash;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, NewSBattleReport_Wrapper& rWrapper)
{
	EType_NewSBattleReport eType = eType_NewSBattleReport;
	src >> (UINT8&)eType;
	switch(eType)
	{
	case eType_NewSBattleReport:
		{
			rWrapper.ptr.reset(new NewSBattleReport);
			src >> (NewSBattleReport&)*rWrapper.ptr;
		}
		break;
	case eType_NewSBattleReportV1:
		{
			rWrapper.ptr.reset(new NewSBattleReportV1);
			src >> (NewSBattleReportV1&)*rWrapper.ptr;
		}
		break;
	default:
		throw "Unknown value for EType_NewSBattleReport";
		break;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const NewSBattleReport_Wrapper& rWrapper)
{
	if(rWrapper.ptr != NULL)
	{
		src << (UINT8)rWrapper.ptr->GetClassType();
		switch(rWrapper.ptr->GetClassType())
		{
		case eType_NewSBattleReport:
			src << (NewSBattleReport&)*rWrapper.ptr;
			break;
		case eType_NewSBattleReportV1:
			src << (NewSBattleReportV1&)*rWrapper.ptr;
			break;
		default:
			throw "Unknown value for EType_NewSBattleReport";
			break;
		}
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, NewSBattleReport& s)
{
	if(strcmp(rElement.Value(), "NewSBattleReport") != 0)
	{
		LOG_CRI << "rElement is not NewSBattleReport!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwHash is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwHash") != 0)
	{
		LOG_CRI << "Attribute: name is not qwHash!";
		return false;
	}
	const char* pszVal_qwHash = pElemChild->Attribute("value");
	if(pszVal_qwHash == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwHash, s.qwHash))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const NewSBattleReport& s, TiXmlElement& rElement)
{
	rElement.SetValue("NewSBattleReport");
	rElement.SetAttribute("type", ToUTF8Ptr("战报"));
	unique_ptr<TiXmlElement> pElem_qwHash(new TiXmlElement("UINT64"));
	if(pElem_qwHash == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwHash->SetAttribute("name", "qwHash");
	pElem_qwHash->SetAttribute("value", NumberToString(s.qwHash).c_str());
	pElem_qwHash->SetAttribute("comment", ToUTF8Ptr("新版本战报校验字段(应该始终为0xFFFFFFFF)"));
	if(rElement.LinkEndChild(pElem_qwHash.get()) != NULL)
		pElem_qwHash.release();
	return true;
}

bool SuperFromXML(TiXmlElement& rElement, NewSBattleReportPtr& p)
{
	const char* pszName = rElement.Value();
	if(pszName == NULL)
	{
		LOG_CRI << "Element Name is empty!";
		return false;
	}
	if(strcmp(pszName, "NewSBattleReport") == 0)
	{
		NewSBattleReportPtr pStruct(new NewSBattleReport);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for NewSBattleReport";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "NewSBattleReport FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "NewSBattleReportV1") == 0)
	{
		NewSBattleReportV1Ptr pStruct(new NewSBattleReportV1);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for NewSBattleReportV1";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "NewSBattleReportV1 FromXML fails!";
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

bool SuperToXML(const NewSBattleReport& s, TiXmlElement& rElement)
{
	switch(s.GetClassType())
	{
	case eType_NewSBattleReport:
		return ToXML((NewSBattleReport&)s, rElement);
	case eType_NewSBattleReportV1:
		return ToXML((NewSBattleReportV1&)s, rElement);
	default:
		LOG_CRI << "Invalid type: " << s.GetClassType();
		return false;
	}
}

#endif

NewSBattleReportV1::NewSBattleReportV1() : qwBattleID(0), qwNextBattleID(0), wSceneID(0), by1Vs1(0), eType((EBattleType)0), 
			byAWaves(0), byBWaves(0), eResult((EBattleResult)0) { }

NewSBattleReportV1::NewSBattleReportV1(NewSBattleReportV1&& src) : NewSBattleReport(src), qwBattleID(src.qwBattleID), qwNextBattleID(src.qwNextBattleID), wSceneID(src.wSceneID), by1Vs1(src.by1Vs1), eType(src.eType), 
			vAGroups(move(src.vAGroups)), vBGroups(move(src.vBGroups)), vSummons(move(src.vSummons)), vRound(move(src.vRound)), byAWaves(src.byAWaves), 
			byBWaves(src.byBWaves), eResult(src.eResult), vecItem(move(src.vecItem)), vecResSource(move(src.vecResSource)) { }

NewSBattleReportV1& NewSBattleReportV1::operator=(NewSBattleReportV1&& rhs)
{
	if(this != &rhs)
	{
		this->~NewSBattleReportV1();
		new (this) NewSBattleReportV1(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, NewSBattleReportV1& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (NewSBattleReport&)s;
	src >> s.qwBattleID;
	src >> s.qwNextBattleID;
	src >> s.wSceneID;
	src >> s.by1Vs1;
	src >> (UINT8&)s.eType;
	src >> s.vAGroups;
	src >> s.vBGroups;
	src >> s.vSummons;
	src >> s.vRound;
	src >> s.byAWaves;
	src >> s.byBWaves;
	src >> (UINT8&)s.eResult;
	src >> s.vecItem;
	src >> s.vecResSource;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const NewSBattleReportV1& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const NewSBattleReport&)s;
	src << s.qwBattleID;
	src << s.qwNextBattleID;
	src << s.wSceneID;
	src << s.by1Vs1;
	src << (UINT8&)s.eType;
	src << s.vAGroups;
	src << s.vBGroups;
	src << s.vSummons;
	src << s.vRound;
	src << s.byAWaves;
	src << s.byBWaves;
	src << (UINT8&)s.eResult;
	src << s.vecItem;
	src << s.vecResSource;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, NewSBattleReportV1& s)
{
	if(strcmp(rElement.Value(), "NewSBattleReportV1") != 0)
	{
		LOG_CRI << "rElement is not NewSBattleReportV1!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for NewSBattleReport is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (NewSBattleReport&)s))
	{
		LOG_CRI << "FromXML for: NewSBattleReport fails!";
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
		LOG_CRI << "pElemChild for qwNextBattleID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwNextBattleID") != 0)
	{
		LOG_CRI << "Attribute: name is not qwNextBattleID!";
		return false;
	}
	const char* pszVal_qwNextBattleID = pElemChild->Attribute("value");
	if(pszVal_qwNextBattleID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwNextBattleID, s.qwNextBattleID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wSceneID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wSceneID") != 0)
	{
		LOG_CRI << "Attribute: name is not wSceneID!";
		return false;
	}
	const char* pszVal_wSceneID = pElemChild->Attribute("value");
	if(pszVal_wSceneID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wSceneID, s.wSceneID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for by1Vs1 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "by1Vs1") != 0)
	{
		LOG_CRI << "Attribute: name is not by1Vs1!";
		return false;
	}
	const char* pszVal_by1Vs1 = pElemChild->Attribute("value");
	if(pszVal_by1Vs1 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_by1Vs1, s.by1Vs1))
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
	if(strcmp(pElemChild->Value(), "EBattleType") != 0)
	{
		LOG_CRI << "pElemChild is not EBattleType!";
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
		LOG_CRI << "pElemChild for vAGroups is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecBattleGroup") != 0)
	{
		LOG_CRI << "pElemChild is not TVecBattleGroup!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vAGroups") != 0)
	{
		LOG_CRI << "Attribute: name is not vAGroups!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vAGroups))
	{
		LOG_CRI << "VectorFromXML for vAGroups fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vBGroups is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecBattleGroup") != 0)
	{
		LOG_CRI << "pElemChild is not TVecBattleGroup!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vBGroups") != 0)
	{
		LOG_CRI << "Attribute: name is not vBGroups!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vBGroups))
	{
		LOG_CRI << "VectorFromXML for vBGroups fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vSummons is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecBattleFighter") != 0)
	{
		LOG_CRI << "pElemChild is not TVecBattleFighter!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vSummons") != 0)
	{
		LOG_CRI << "Attribute: name is not vSummons!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vSummons))
	{
		LOG_CRI << "VectorFromXML for vSummons fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vRound is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecBattleRound") != 0)
	{
		LOG_CRI << "pElemChild is not TVecBattleRound!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vRound") != 0)
	{
		LOG_CRI << "Attribute: name is not vRound!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vRound))
	{
		LOG_CRI << "VectorFromXML for vRound fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byAWaves is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byAWaves") != 0)
	{
		LOG_CRI << "Attribute: name is not byAWaves!";
		return false;
	}
	const char* pszVal_byAWaves = pElemChild->Attribute("value");
	if(pszVal_byAWaves == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byAWaves, s.byAWaves))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byBWaves is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byBWaves") != 0)
	{
		LOG_CRI << "Attribute: name is not byBWaves!";
		return false;
	}
	const char* pszVal_byBWaves = pElemChild->Attribute("value");
	if(pszVal_byBWaves == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byBWaves, s.byBWaves))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eResult is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "EBattleResult") != 0)
	{
		LOG_CRI << "pElemChild is not EBattleResult!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eResult") != 0)
	{
		LOG_CRI << "Attribute: name is not eResult!";
		return false;
	}
	const char* pszVal_eResult = pElemChild->Attribute("value");
	if(pszVal_eResult == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!EnumStrToVal(pszVal_eResult, s.eResult))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecItem is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "ItemProt::TVecItemGenInfo") != 0)
	{
		LOG_CRI << "pElemChild is not ItemProt::TVecItemGenInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecItem") != 0)
	{
		LOG_CRI << "Attribute: name is not vecItem!";
		return false;
	}
	if(!NItemProt::VectorFromXML(*pElemChild, s.vecItem))
	{
		LOG_CRI << "VectorFromXML for vecItem fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecResSource is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "ItemProt::TVecResource") != 0)
	{
		LOG_CRI << "pElemChild is not ItemProt::TVecResource!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecResSource") != 0)
	{
		LOG_CRI << "Attribute: name is not vecResSource!";
		return false;
	}
	if(!NItemProt::VectorFromXML(*pElemChild, s.vecResSource))
	{
		LOG_CRI << "VectorFromXML for vecResSource fails!";
		return false;
	}
	return true;
}

bool ToXML(const NewSBattleReportV1& s, TiXmlElement& rElement)
{
	rElement.SetValue("NewSBattleReportV1");
	rElement.SetAttribute("type", ToUTF8Ptr("版本1战报"));
	unique_ptr<TiXmlElement> pElem_NewSBattleReport(new TiXmlElement("NewSBattleReport"));
	if(pElem_NewSBattleReport == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const NewSBattleReport&)s, *pElem_NewSBattleReport))
	{
		LOG_CRI << "NewSBattleReport ToXML fails!";
		return false;
	}
	pElem_NewSBattleReport->SetAttribute("type", ToUTF8Ptr("战报"));
	pElem_NewSBattleReport->SetAttribute("comment", ToUTF8Ptr("父类NewSBattleReport部分"));
	if(rElement.LinkEndChild(pElem_NewSBattleReport.get()) != NULL)
		pElem_NewSBattleReport.release();
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
	unique_ptr<TiXmlElement> pElem_qwNextBattleID(new TiXmlElement("UINT64"));
	if(pElem_qwNextBattleID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwNextBattleID->SetAttribute("name", "qwNextBattleID");
	pElem_qwNextBattleID->SetAttribute("value", NumberToString(s.qwNextBattleID).c_str());
	pElem_qwNextBattleID->SetAttribute("comment", ToUTF8Ptr("next战报ID"));
	if(rElement.LinkEndChild(pElem_qwNextBattleID.get()) != NULL)
		pElem_qwNextBattleID.release();
	unique_ptr<TiXmlElement> pElem_wSceneID(new TiXmlElement("UINT16"));
	if(pElem_wSceneID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wSceneID->SetAttribute("name", "wSceneID");
	pElem_wSceneID->SetAttribute("value", NumberToString(s.wSceneID).c_str());
	pElem_wSceneID->SetAttribute("comment", ToUTF8Ptr("战斗场景ID"));
	if(rElement.LinkEndChild(pElem_wSceneID.get()) != NULL)
		pElem_wSceneID.release();
	unique_ptr<TiXmlElement> pElem_by1Vs1(new TiXmlElement("UINT8"));
	if(pElem_by1Vs1 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_by1Vs1->SetAttribute("name", "by1Vs1");
	pElem_by1Vs1->SetAttribute("value", NumberToString(s.by1Vs1).c_str());
	pElem_by1Vs1->SetAttribute("comment", ToUTF8Ptr("0:普通一打多，1：普通一打一，2：boss一打多， 3：boss一打一"));
	if(rElement.LinkEndChild(pElem_by1Vs1.get()) != NULL)
		pElem_by1Vs1.release();
	unique_ptr<TiXmlElement> pElem_eType(new TiXmlElement("EBattleType"));
	if(pElem_eType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eType->SetAttribute("name", "eType");
	const char* pszEnum_eType = EnumValToStr(s.eType);
	if(pszEnum_eType == NULL)
	{
		LOG_CRI << "EnumValToStr for EBattleType fails!";
		return false;
	}
	pElem_eType->SetAttribute("value", pszEnum_eType);
	pElem_eType->SetAttribute("comment", ToUTF8Ptr("战斗模式：PVP/PVE"));
	if(rElement.LinkEndChild(pElem_eType.get()) != NULL)
		pElem_eType.release();
	unique_ptr<TiXmlElement> pElem_vAGroups(new TiXmlElement("TVecBattleGroup"));
	if(pElem_vAGroups == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vAGroups->SetAttribute("name", "vAGroups");
	if(!VectorToXML(s.vAGroups, *pElem_vAGroups))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vAGroups->SetAttribute("comment", ToUTF8Ptr("A队伍里的所有小组"));
	if(rElement.LinkEndChild(pElem_vAGroups.get()) != NULL)
		pElem_vAGroups.release();
	unique_ptr<TiXmlElement> pElem_vBGroups(new TiXmlElement("TVecBattleGroup"));
	if(pElem_vBGroups == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vBGroups->SetAttribute("name", "vBGroups");
	if(!VectorToXML(s.vBGroups, *pElem_vBGroups))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vBGroups->SetAttribute("comment", ToUTF8Ptr("B队伍里的所有小组"));
	if(rElement.LinkEndChild(pElem_vBGroups.get()) != NULL)
		pElem_vBGroups.release();
	unique_ptr<TiXmlElement> pElem_vSummons(new TiXmlElement("TVecBattleFighter"));
	if(pElem_vSummons == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vSummons->SetAttribute("name", "vSummons");
	if(!VectorToXML(s.vSummons, *pElem_vSummons))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vSummons->SetAttribute("comment", ToUTF8Ptr("战斗中可能召唤的散仙"));
	if(rElement.LinkEndChild(pElem_vSummons.get()) != NULL)
		pElem_vSummons.release();
	unique_ptr<TiXmlElement> pElem_vRound(new TiXmlElement("TVecBattleRound"));
	if(pElem_vRound == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vRound->SetAttribute("name", "vRound");
	if(!VectorToXML(s.vRound, *pElem_vRound))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vRound->SetAttribute("comment", ToUTF8Ptr("所有的出手回合"));
	if(rElement.LinkEndChild(pElem_vRound.get()) != NULL)
		pElem_vRound.release();
	unique_ptr<TiXmlElement> pElem_byAWaves(new TiXmlElement("UINT8"));
	if(pElem_byAWaves == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byAWaves->SetAttribute("name", "byAWaves");
	pElem_byAWaves->SetAttribute("value", NumberToString(s.byAWaves).c_str());
	pElem_byAWaves->SetAttribute("comment", ToUTF8Ptr("A队剩余波数"));
	if(rElement.LinkEndChild(pElem_byAWaves.get()) != NULL)
		pElem_byAWaves.release();
	unique_ptr<TiXmlElement> pElem_byBWaves(new TiXmlElement("UINT8"));
	if(pElem_byBWaves == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byBWaves->SetAttribute("name", "byBWaves");
	pElem_byBWaves->SetAttribute("value", NumberToString(s.byBWaves).c_str());
	pElem_byBWaves->SetAttribute("comment", ToUTF8Ptr("B队剩余波数"));
	if(rElement.LinkEndChild(pElem_byBWaves.get()) != NULL)
		pElem_byBWaves.release();
	unique_ptr<TiXmlElement> pElem_eResult(new TiXmlElement("EBattleResult"));
	if(pElem_eResult == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eResult->SetAttribute("name", "eResult");
	const char* pszEnum_eResult = EnumValToStr(s.eResult);
	if(pszEnum_eResult == NULL)
	{
		LOG_CRI << "EnumValToStr for EBattleResult fails!";
		return false;
	}
	pElem_eResult->SetAttribute("value", pszEnum_eResult);
	pElem_eResult->SetAttribute("comment", ToUTF8Ptr("战斗结果"));
	if(rElement.LinkEndChild(pElem_eResult.get()) != NULL)
		pElem_eResult.release();
	unique_ptr<TiXmlElement> pElem_vecItem(new TiXmlElement("ItemProt::TVecItemGenInfo"));
	if(pElem_vecItem == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecItem->SetAttribute("name", "vecItem");
	if(!NItemProt::VectorToXML(s.vecItem, *pElem_vecItem))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecItem->SetAttribute("comment", ToUTF8Ptr("获得物品"));
	if(rElement.LinkEndChild(pElem_vecItem.get()) != NULL)
		pElem_vecItem.release();
	unique_ptr<TiXmlElement> pElem_vecResSource(new TiXmlElement("ItemProt::TVecResource"));
	if(pElem_vecResSource == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecResSource->SetAttribute("name", "vecResSource");
	if(!NItemProt::VectorToXML(s.vecResSource, *pElem_vecResSource))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecResSource->SetAttribute("comment", ToUTF8Ptr("获得资源"));
	if(rElement.LinkEndChild(pElem_vecResSource.get()) != NULL)
		pElem_vecResSource.release();
	return true;
}

#endif

} //namespace NBattleGS
