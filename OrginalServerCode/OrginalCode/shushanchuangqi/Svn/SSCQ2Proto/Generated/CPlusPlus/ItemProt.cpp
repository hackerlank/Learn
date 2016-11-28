/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    ItemProt.cpp
//  Purpose:      道具相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "ItemProt.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NItemProt
{

#ifdef PROT_USE_XML

const char* EnumValToStr(EItemResult e)
{
	switch(e)
	{
	case eItemSucceed:
		return "eItemSucceed";
	case eItemFailed:
		return "eItemFailed";
	case eItemNotEnougth:
		return "eItemNotEnougth";
	case eItemNotExist:
		return "eItemNotExist";
	case eItemErrBind:
		return "eItemErrBind";
	case eItemErrUse:
		return "eItemErrUse";
	case eItemStoreFull:
		return "eItemStoreFull";
	case eItemStoreErr:
		return "eItemStoreErr";
	case eItemRangeErr:
		return "eItemRangeErr";
	case eItemNoStack:
		return "eItemNoStack";
	case eItemNoCoin:
		return "eItemNoCoin";
	case eItemCoinFull:
		return "eItemCoinFull";
	case eItemNoMoney:
		return "eItemNoMoney";
	case eItemMoneyFull:
		return "eItemMoneyFull";
	case eItemErrOper:
		return "eItemErrOper";
	case eItemErrCD:
		return "eItemErrCD";
	case eItemErrSlot:
		return "eItemErrSlot";
	case eItemNotNeed:
		return "eItemNotNeed";
	case eItemErrName:
		return "eItemErrName";
	case eItemExpired:
		return "eItemExpired";
	case eItemErrSell:
		return "eItemErrSell";
	case eItemErrDrop:
		return "eItemErrDrop";
	case eItemErrLevel:
		return "eItemErrLevel";
	case eItemErrJob:
		return "eItemErrJob";
	case eItemNoStuff:
		return "eItemNoStuff";
	case eItemErrDungeon:
		return "eItemErrDungeon";
	case eItemErrTransfMap:
		return "eItemErrTransfMap";
	case eItemMountExist:
		return "eItemMountExist";
	case eItemMutualEquip:
		return "eItemMutualEquip";
	case eItemMutual:
		return "eItemMutual";
	case eItemNoTakeOff:
		return "eItemNoTakeOff";
	case eItemSkillExist:
		return "eItemSkillExist";
	case eItemFashionExist:
		return "eItemFashionExist";
	case eItemStoreMax:
		return "eItemStoreMax";
	case eItemDepotMax:
		return "eItemDepotMax";
	case eItemErrOther:
		return "eItemErrOther";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EItemResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EItemResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eItemSucceed", eItemSucceed));
		mapStr2Val.insert(make_pair("eItemFailed", eItemFailed));
		mapStr2Val.insert(make_pair("eItemNotEnougth", eItemNotEnougth));
		mapStr2Val.insert(make_pair("eItemNotExist", eItemNotExist));
		mapStr2Val.insert(make_pair("eItemErrBind", eItemErrBind));
		mapStr2Val.insert(make_pair("eItemErrUse", eItemErrUse));
		mapStr2Val.insert(make_pair("eItemStoreFull", eItemStoreFull));
		mapStr2Val.insert(make_pair("eItemStoreErr", eItemStoreErr));
		mapStr2Val.insert(make_pair("eItemRangeErr", eItemRangeErr));
		mapStr2Val.insert(make_pair("eItemNoStack", eItemNoStack));
		mapStr2Val.insert(make_pair("eItemNoCoin", eItemNoCoin));
		mapStr2Val.insert(make_pair("eItemCoinFull", eItemCoinFull));
		mapStr2Val.insert(make_pair("eItemNoMoney", eItemNoMoney));
		mapStr2Val.insert(make_pair("eItemMoneyFull", eItemMoneyFull));
		mapStr2Val.insert(make_pair("eItemErrOper", eItemErrOper));
		mapStr2Val.insert(make_pair("eItemErrCD", eItemErrCD));
		mapStr2Val.insert(make_pair("eItemErrSlot", eItemErrSlot));
		mapStr2Val.insert(make_pair("eItemNotNeed", eItemNotNeed));
		mapStr2Val.insert(make_pair("eItemErrName", eItemErrName));
		mapStr2Val.insert(make_pair("eItemExpired", eItemExpired));
		mapStr2Val.insert(make_pair("eItemErrSell", eItemErrSell));
		mapStr2Val.insert(make_pair("eItemErrDrop", eItemErrDrop));
		mapStr2Val.insert(make_pair("eItemErrLevel", eItemErrLevel));
		mapStr2Val.insert(make_pair("eItemErrJob", eItemErrJob));
		mapStr2Val.insert(make_pair("eItemNoStuff", eItemNoStuff));
		mapStr2Val.insert(make_pair("eItemErrDungeon", eItemErrDungeon));
		mapStr2Val.insert(make_pair("eItemErrTransfMap", eItemErrTransfMap));
		mapStr2Val.insert(make_pair("eItemMountExist", eItemMountExist));
		mapStr2Val.insert(make_pair("eItemMutualEquip", eItemMutualEquip));
		mapStr2Val.insert(make_pair("eItemMutual", eItemMutual));
		mapStr2Val.insert(make_pair("eItemNoTakeOff", eItemNoTakeOff));
		mapStr2Val.insert(make_pair("eItemSkillExist", eItemSkillExist));
		mapStr2Val.insert(make_pair("eItemFashionExist", eItemFashionExist));
		mapStr2Val.insert(make_pair("eItemStoreMax", eItemStoreMax));
		mapStr2Val.insert(make_pair("eItemDepotMax", eItemDepotMax));
		mapStr2Val.insert(make_pair("eItemErrOther", eItemErrOther));
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

const char* EnumValToStr(ECittaResult e)
{
	switch(e)
	{
	case eCittaSuccess:
		return "eCittaSuccess";
	case eCittaFailed:
		return "eCittaFailed";
	case eCittaPackFull:
		return "eCittaPackFull";
	case eCittaMaterialLack:
		return "eCittaMaterialLack";
	case eCittaSlotNotEmpty:
		return "eCittaSlotNotEmpty";
	case eCittaSlotEmpty:
		return "eCittaSlotEmpty";
	case eCittaSilverLack:
		return "eCittaSilverLack";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, ECittaResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, ECittaResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eCittaSuccess", eCittaSuccess));
		mapStr2Val.insert(make_pair("eCittaFailed", eCittaFailed));
		mapStr2Val.insert(make_pair("eCittaPackFull", eCittaPackFull));
		mapStr2Val.insert(make_pair("eCittaMaterialLack", eCittaMaterialLack));
		mapStr2Val.insert(make_pair("eCittaSlotNotEmpty", eCittaSlotNotEmpty));
		mapStr2Val.insert(make_pair("eCittaSlotEmpty", eCittaSlotEmpty));
		mapStr2Val.insert(make_pair("eCittaSilverLack", eCittaSilverLack));
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

const char* EnumValToStr(ETrumpResult e)
{
	switch(e)
	{
	case eTrumpSuccess:
		return "eTrumpSuccess";
	case eTrumpFailed:
		return "eTrumpFailed";
	case eTrumpExist:
		return "eTrumpExist";
	case eTrumpNotifyFailed:
		return "eTrumpNotifyFailed";
	case eTrumpNotActived:
		return "eTrumpNotActived";
	case eTrumpNotExist:
		return "eTrumpNotExist";
	case eTrumpUpgradeMaterialLack:
		return "eTrumpUpgradeMaterialLack";
	case eTrumpEvolveMaterialLack:
		return "eTrumpEvolveMaterialLack";
	case eTrumpFull:
		return "eTrumpFull";
	case eTrumpIsEquiped:
		return "eTrumpIsEquiped";
	case eTrumpNotEquiped:
		return "eTrumpNotEquiped";
	case eTrumpActiveFailed:
		return "eTrumpActiveFailed";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, ETrumpResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, ETrumpResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eTrumpSuccess", eTrumpSuccess));
		mapStr2Val.insert(make_pair("eTrumpFailed", eTrumpFailed));
		mapStr2Val.insert(make_pair("eTrumpExist", eTrumpExist));
		mapStr2Val.insert(make_pair("eTrumpNotifyFailed", eTrumpNotifyFailed));
		mapStr2Val.insert(make_pair("eTrumpNotActived", eTrumpNotActived));
		mapStr2Val.insert(make_pair("eTrumpNotExist", eTrumpNotExist));
		mapStr2Val.insert(make_pair("eTrumpUpgradeMaterialLack", eTrumpUpgradeMaterialLack));
		mapStr2Val.insert(make_pair("eTrumpEvolveMaterialLack", eTrumpEvolveMaterialLack));
		mapStr2Val.insert(make_pair("eTrumpFull", eTrumpFull));
		mapStr2Val.insert(make_pair("eTrumpIsEquiped", eTrumpIsEquiped));
		mapStr2Val.insert(make_pair("eTrumpNotEquiped", eTrumpNotEquiped));
		mapStr2Val.insert(make_pair("eTrumpActiveFailed", eTrumpActiveFailed));
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

const char* EnumValToStr(EFashionResult e)
{
	switch(e)
	{
	case eFashionSucc:
		return "eFashionSucc";
	case eFashionFailed:
		return "eFashionFailed";
	case eFashionItemErr:
		return "eFashionItemErr";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EFashionResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EFashionResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eFashionSucc", eFashionSucc));
		mapStr2Val.insert(make_pair("eFashionFailed", eFashionFailed));
		mapStr2Val.insert(make_pair("eFashionItemErr", eFashionItemErr));
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

const char* EnumValToStr(EGemstoneResult e)
{
	switch(e)
	{
	case eGemstoneSuccess:
		return "eGemstoneSuccess";
	case eGemstoneFailed:
		return "eGemstoneFailed";
	case eGemstoneSlotNotEmpty:
		return "eGemstoneSlotNotEmpty";
	case eGemstoneSlotEmpty:
		return "eGemstoneSlotEmpty";
	case eGemstonePackFull:
		return "eGemstonePackFull";
	case eGemstoneHeroErr:
		return "eGemstoneHeroErr";
	case eGemstoneNoStone:
		return "eGemstoneNoStone";
	case eGemstoneErrStone:
		return "eGemstoneErrStone";
	case eGemstoneMaterialLack:
		return "eGemstoneMaterialLack";
	case eGemstoneHasSameType:
		return "eGemstoneHasSameType";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EGemstoneResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EGemstoneResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eGemstoneSuccess", eGemstoneSuccess));
		mapStr2Val.insert(make_pair("eGemstoneFailed", eGemstoneFailed));
		mapStr2Val.insert(make_pair("eGemstoneSlotNotEmpty", eGemstoneSlotNotEmpty));
		mapStr2Val.insert(make_pair("eGemstoneSlotEmpty", eGemstoneSlotEmpty));
		mapStr2Val.insert(make_pair("eGemstonePackFull", eGemstonePackFull));
		mapStr2Val.insert(make_pair("eGemstoneHeroErr", eGemstoneHeroErr));
		mapStr2Val.insert(make_pair("eGemstoneNoStone", eGemstoneNoStone));
		mapStr2Val.insert(make_pair("eGemstoneErrStone", eGemstoneErrStone));
		mapStr2Val.insert(make_pair("eGemstoneMaterialLack", eGemstoneMaterialLack));
		mapStr2Val.insert(make_pair("eGemstoneHasSameType", eGemstoneHasSameType));
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

const char* EnumValToStr(EItemQuality e)
{
	switch(e)
	{
	case eColorNone:
		return "eColorNone";
	case eColorGreen:
		return "eColorGreen";
	case eColorBlue:
		return "eColorBlue";
	case eColorPurple:
		return "eColorPurple";
	case eColorOrange:
		return "eColorOrange";
	case eColorBlackGold:
		return "eColorBlackGold";
	case eColorEnd:
		return "eColorEnd";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EItemQuality& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EItemQuality> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eColorNone", eColorNone));
		mapStr2Val.insert(make_pair("eColorGreen", eColorGreen));
		mapStr2Val.insert(make_pair("eColorBlue", eColorBlue));
		mapStr2Val.insert(make_pair("eColorPurple", eColorPurple));
		mapStr2Val.insert(make_pair("eColorOrange", eColorOrange));
		mapStr2Val.insert(make_pair("eColorBlackGold", eColorBlackGold));
		mapStr2Val.insert(make_pair("eColorEnd", eColorEnd));
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

const char* EnumValToStr(EStoreType e)
{
	switch(e)
	{
	case eStoreNone:
		return "eStoreNone";
	case eStorePack:
		return "eStorePack";
	case eStoreDepot:
		return "eStoreDepot";
	case eStorePlayerTrump:
		return "eStorePlayerTrump";
	case eStorePlayerCitta:
		return "eStorePlayerCitta";
	case eStoreFashion:
		return "eStoreFashion";
	case eStoreGemstone:
		return "eStoreGemstone";
	case eStoreEquipTrump:
		return "eStoreEquipTrump";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EStoreType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EStoreType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eStoreNone", eStoreNone));
		mapStr2Val.insert(make_pair("eStorePack", eStorePack));
		mapStr2Val.insert(make_pair("eStoreDepot", eStoreDepot));
		mapStr2Val.insert(make_pair("eStorePlayerTrump", eStorePlayerTrump));
		mapStr2Val.insert(make_pair("eStorePlayerCitta", eStorePlayerCitta));
		mapStr2Val.insert(make_pair("eStoreFashion", eStoreFashion));
		mapStr2Val.insert(make_pair("eStoreGemstone", eStoreGemstone));
		mapStr2Val.insert(make_pair("eStoreEquipTrump", eStoreEquipTrump));
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

const char* EnumValToStr(EItemLoggerType e)
{
	switch(e)
	{
	case eItemLogger1:
		return "eItemLogger1";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EItemLoggerType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EItemLoggerType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eItemLogger1", eItemLogger1));
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

const char* EnumValToStr(EBindType e)
{
	switch(e)
	{
	case eBindNone:
		return "eBindNone";
	case eBindGet:
		return "eBindGet";
	case eBindStren:
		return "eBindStren";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EBindType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EBindType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eBindNone", eBindNone));
		mapStr2Val.insert(make_pair("eBindGet", eBindGet));
		mapStr2Val.insert(make_pair("eBindStren", eBindStren));
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

const char* EnumValToStr(EBindUseType e)
{
	switch(e)
	{
	case eBindUseNone:
		return "eBindUseNone";
	case eBindUseBind:
		return "eBindUseBind";
	case eBindUseNoneFirst:
		return "eBindUseNoneFirst";
	case eBindUseBindFirst:
		return "eBindUseBindFirst";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EBindUseType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EBindUseType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eBindUseNone", eBindUseNone));
		mapStr2Val.insert(make_pair("eBindUseBind", eBindUseBind));
		mapStr2Val.insert(make_pair("eBindUseNoneFirst", eBindUseNoneFirst));
		mapStr2Val.insert(make_pair("eBindUseBindFirst", eBindUseBindFirst));
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

const char* EnumValToStr(EItemType e)
{
	switch(e)
	{
	case eItemNone:
		return "eItemNone";
	case eItemResource:
		return "eItemResource";
	case eItemNormal:
		return "eItemNormal";
	case eItemTrump:
		return "eItemTrump";
	case eItemEquipTrump:
		return "eItemEquipTrump";
	case eItemFashion:
		return "eItemFashion";
	case eItemFormation:
		return "eItemFormation";
	case eItemCitta:
		return "eItemCitta";
	case eItemIntensify:
		return "eItemIntensify";
	case eItemSkillBook:
		return "eItemSkillBook";
	case eItemStone:
		return "eItemStone";
	case eItemStuff:
		return "eItemStuff";
	case eItemTask:
		return "eItemTask";
	case eItemSpirit:
		return "eItemSpirit";
	case eItemSoul:
		return "eItemSoul";
	case eItemNeidan:
		return "eItemNeidan";
	case eItemVigour:
		return "eItemVigour";
	case eItemOther:
		return "eItemOther";
	case eItemEnd:
		return "eItemEnd";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EItemType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EItemType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eItemNone", eItemNone));
		mapStr2Val.insert(make_pair("eItemResource", eItemResource));
		mapStr2Val.insert(make_pair("eItemNormal", eItemNormal));
		mapStr2Val.insert(make_pair("eItemTrump", eItemTrump));
		mapStr2Val.insert(make_pair("eItemEquipTrump", eItemEquipTrump));
		mapStr2Val.insert(make_pair("eItemFashion", eItemFashion));
		mapStr2Val.insert(make_pair("eItemFormation", eItemFormation));
		mapStr2Val.insert(make_pair("eItemCitta", eItemCitta));
		mapStr2Val.insert(make_pair("eItemIntensify", eItemIntensify));
		mapStr2Val.insert(make_pair("eItemSkillBook", eItemSkillBook));
		mapStr2Val.insert(make_pair("eItemStone", eItemStone));
		mapStr2Val.insert(make_pair("eItemStuff", eItemStuff));
		mapStr2Val.insert(make_pair("eItemTask", eItemTask));
		mapStr2Val.insert(make_pair("eItemSpirit", eItemSpirit));
		mapStr2Val.insert(make_pair("eItemSoul", eItemSoul));
		mapStr2Val.insert(make_pair("eItemNeidan", eItemNeidan));
		mapStr2Val.insert(make_pair("eItemVigour", eItemVigour));
		mapStr2Val.insert(make_pair("eItemOther", eItemOther));
		mapStr2Val.insert(make_pair("eItemEnd", eItemEnd));
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

const char* EnumValToStr(EItemSubType e)
{
	switch(e)
	{
	case eItemSubNone:
		return "eItemSubNone";
	case eItemSubResource:
		return "eItemSubResource";
	case eItemSubNormal:
		return "eItemSubNormal";
	case eItemSubFasionMaterial:
		return "eItemSubFasionMaterial";
	case eItemSubZTMaterial:
		return "eItemSubZTMaterial";
	case eItemSubWepaon:
		return "eItemSubWepaon";
	case eItemSubRing:
		return "eItemSubRing";
	case eItemSubNeck:
		return "eItemSubNeck";
	case eItemSubHead:
		return "eItemSubHead";
	case eItemSubChest:
		return "eItemSubChest";
	case eItemSubLegging:
		return "eItemSubLegging";
	case eItemSubMounts:
		return "eItemSubMounts";
	case eItemSubActiveTrump:
		return "eItemSubActiveTrump";
	case eItemSubPassiveTrump:
		return "eItemSubPassiveTrump";
	case eItemSubFashion:
		return "eItemSubFashion";
	case eItemSubFashion2:
		return "eItemSubFashion2";
	case eItemSubSpirit:
		return "eItemSubSpirit";
	case eItemSubPetSoul:
		return "eItemSubPetSoul";
	case eItemSubEquipTrumpInnate:
		return "eItemSubEquipTrumpInnate";
	case eItemSubEquipTrumpPassive:
		return "eItemSubEquipTrumpPassive";
	case eItemSubEquipTrumpTransform:
		return "eItemSubEquipTrumpTransform";
	case eItemSubEquipTrumpHalo:
		return "eItemSubEquipTrumpHalo";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EItemSubType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EItemSubType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eItemSubNone", eItemSubNone));
		mapStr2Val.insert(make_pair("eItemSubResource", eItemSubResource));
		mapStr2Val.insert(make_pair("eItemSubNormal", eItemSubNormal));
		mapStr2Val.insert(make_pair("eItemSubFasionMaterial", eItemSubFasionMaterial));
		mapStr2Val.insert(make_pair("eItemSubZTMaterial", eItemSubZTMaterial));
		mapStr2Val.insert(make_pair("eItemSubWepaon", eItemSubWepaon));
		mapStr2Val.insert(make_pair("eItemSubRing", eItemSubRing));
		mapStr2Val.insert(make_pair("eItemSubNeck", eItemSubNeck));
		mapStr2Val.insert(make_pair("eItemSubHead", eItemSubHead));
		mapStr2Val.insert(make_pair("eItemSubChest", eItemSubChest));
		mapStr2Val.insert(make_pair("eItemSubLegging", eItemSubLegging));
		mapStr2Val.insert(make_pair("eItemSubMounts", eItemSubMounts));
		mapStr2Val.insert(make_pair("eItemSubActiveTrump", eItemSubActiveTrump));
		mapStr2Val.insert(make_pair("eItemSubPassiveTrump", eItemSubPassiveTrump));
		mapStr2Val.insert(make_pair("eItemSubFashion", eItemSubFashion));
		mapStr2Val.insert(make_pair("eItemSubFashion2", eItemSubFashion2));
		mapStr2Val.insert(make_pair("eItemSubSpirit", eItemSubSpirit));
		mapStr2Val.insert(make_pair("eItemSubPetSoul", eItemSubPetSoul));
		mapStr2Val.insert(make_pair("eItemSubEquipTrumpInnate", eItemSubEquipTrumpInnate));
		mapStr2Val.insert(make_pair("eItemSubEquipTrumpPassive", eItemSubEquipTrumpPassive));
		mapStr2Val.insert(make_pair("eItemSubEquipTrumpTransform", eItemSubEquipTrumpTransform));
		mapStr2Val.insert(make_pair("eItemSubEquipTrumpHalo", eItemSubEquipTrumpHalo));
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

const char* EnumValToStr(ETrumpSlotType e)
{
	switch(e)
	{
	case eSlotTrump1:
		return "eSlotTrump1";
	case eSlotTrump2:
		return "eSlotTrump2";
	case eSlotTrump3:
		return "eSlotTrump3";
	case eSlotTrump4:
		return "eSlotTrump4";
	case eSlotTrump5:
		return "eSlotTrump5";
	case eSlotTrump6:
		return "eSlotTrump6";
	case eSlotTrump7:
		return "eSlotTrump7";
	case eSlotTrump8:
		return "eSlotTrump8";
	case eSlotTrump9:
		return "eSlotTrump9";
	case eSlotTrump10:
		return "eSlotTrump10";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, ETrumpSlotType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, ETrumpSlotType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eSlotTrump1", eSlotTrump1));
		mapStr2Val.insert(make_pair("eSlotTrump2", eSlotTrump2));
		mapStr2Val.insert(make_pair("eSlotTrump3", eSlotTrump3));
		mapStr2Val.insert(make_pair("eSlotTrump4", eSlotTrump4));
		mapStr2Val.insert(make_pair("eSlotTrump5", eSlotTrump5));
		mapStr2Val.insert(make_pair("eSlotTrump6", eSlotTrump6));
		mapStr2Val.insert(make_pair("eSlotTrump7", eSlotTrump7));
		mapStr2Val.insert(make_pair("eSlotTrump8", eSlotTrump8));
		mapStr2Val.insert(make_pair("eSlotTrump9", eSlotTrump9));
		mapStr2Val.insert(make_pair("eSlotTrump10", eSlotTrump10));
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

const char* EnumValToStr(ECittaSlotType e)
{
	switch(e)
	{
	case eSlotCitta1:
		return "eSlotCitta1";
	case eSlotCitta2:
		return "eSlotCitta2";
	case eSlotCitta3:
		return "eSlotCitta3";
	case eSlotCitta4:
		return "eSlotCitta4";
	case eSlotCitta5:
		return "eSlotCitta5";
	case eSlotCitta6:
		return "eSlotCitta6";
	case eSlotCitta7:
		return "eSlotCitta7";
	case eSlotCitta8:
		return "eSlotCitta8";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, ECittaSlotType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, ECittaSlotType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eSlotCitta1", eSlotCitta1));
		mapStr2Val.insert(make_pair("eSlotCitta2", eSlotCitta2));
		mapStr2Val.insert(make_pair("eSlotCitta3", eSlotCitta3));
		mapStr2Val.insert(make_pair("eSlotCitta4", eSlotCitta4));
		mapStr2Val.insert(make_pair("eSlotCitta5", eSlotCitta5));
		mapStr2Val.insert(make_pair("eSlotCitta6", eSlotCitta6));
		mapStr2Val.insert(make_pair("eSlotCitta7", eSlotCitta7));
		mapStr2Val.insert(make_pair("eSlotCitta8", eSlotCitta8));
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

const char* EnumValToStr(ECittaNameType e)
{
	switch(e)
	{
	case eNameNone:
		return "eNameNone";
	case eNameAttack:
		return "eNameAttack";
	case eNameDefence:
		return "eNameDefence";
	case eNameMgcDefence:
		return "eNameMgcDefence";
	case eNameHP:
		return "eNameHP";
	case eNameHit:
		return "eNameHit";
	case eNameDodge:
		return "eNameDodge";
	case eNameCritical:
		return "eNameCritical";
	case eNameAntiCri:
		return "eNameAntiCri";
	case eNamePiece:
		return "eNamePiece";
	case eNameCounter:
		return "eNameCounter";
	case eNameResist:
		return "eNameResist";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, ECittaNameType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, ECittaNameType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eNameNone", eNameNone));
		mapStr2Val.insert(make_pair("eNameAttack", eNameAttack));
		mapStr2Val.insert(make_pair("eNameDefence", eNameDefence));
		mapStr2Val.insert(make_pair("eNameMgcDefence", eNameMgcDefence));
		mapStr2Val.insert(make_pair("eNameHP", eNameHP));
		mapStr2Val.insert(make_pair("eNameHit", eNameHit));
		mapStr2Val.insert(make_pair("eNameDodge", eNameDodge));
		mapStr2Val.insert(make_pair("eNameCritical", eNameCritical));
		mapStr2Val.insert(make_pair("eNameAntiCri", eNameAntiCri));
		mapStr2Val.insert(make_pair("eNamePiece", eNamePiece));
		mapStr2Val.insert(make_pair("eNameCounter", eNameCounter));
		mapStr2Val.insert(make_pair("eNameResist", eNameResist));
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

SItemGenInfo::SItemGenInfo() : wItemID(0), dwCount(0), byQuality(0), eBindType((EBindType)0), dwTimeID(0) { }

SItemGenInfo::SItemGenInfo(UINT16 wItemID_, UINT32 dwCount_, UINT8 byQuality_, EBindType eBindType_, UINT32 dwTimeID_)
			: wItemID(wItemID_), dwCount(dwCount_), byQuality(byQuality_), eBindType(eBindType_), dwTimeID(dwTimeID_) { }

CInArchive& operator>>(CInArchive& src, SItemGenInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.wItemID;
	src >> s.dwCount;
	src >> s.byQuality;
	src >> (UINT8&)s.eBindType;
	src >> s.dwTimeID;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SItemGenInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.wItemID;
	src << s.dwCount;
	src << s.byQuality;
	src << (UINT8&)s.eBindType;
	src << s.dwTimeID;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SItemGenInfo& s)
{
	if(strcmp(rElement.Value(), "SItemGenInfo") != 0)
	{
		LOG_CRI << "rElement is not SItemGenInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wItemID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wItemID") != 0)
	{
		LOG_CRI << "Attribute: name is not wItemID!";
		return false;
	}
	const char* pszVal_wItemID = pElemChild->Attribute("value");
	if(pszVal_wItemID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wItemID, s.wItemID))
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
		LOG_CRI << "pElemChild for eBindType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "EBindType") != 0)
	{
		LOG_CRI << "pElemChild is not EBindType!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eBindType") != 0)
	{
		LOG_CRI << "Attribute: name is not eBindType!";
		return false;
	}
	const char* pszVal_eBindType = pElemChild->Attribute("value");
	if(pszVal_eBindType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!EnumStrToVal(pszVal_eBindType, s.eBindType))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwTimeID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwTimeID") != 0)
	{
		LOG_CRI << "Attribute: name is not dwTimeID!";
		return false;
	}
	const char* pszVal_dwTimeID = pElemChild->Attribute("value");
	if(pszVal_dwTimeID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwTimeID, s.dwTimeID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SItemGenInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SItemGenInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("显示用的模板数据"));
	unique_ptr<TiXmlElement> pElem_wItemID(new TiXmlElement("UINT16"));
	if(pElem_wItemID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wItemID->SetAttribute("name", "wItemID");
	pElem_wItemID->SetAttribute("value", NumberToString(s.wItemID).c_str());
	pElem_wItemID->SetAttribute("comment", ToUTF8Ptr("模板ID"));
	if(rElement.LinkEndChild(pElem_wItemID.get()) != NULL)
		pElem_wItemID.release();
	unique_ptr<TiXmlElement> pElem_dwCount(new TiXmlElement("UINT32"));
	if(pElem_dwCount == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwCount->SetAttribute("name", "dwCount");
	pElem_dwCount->SetAttribute("value", NumberToString(s.dwCount).c_str());
	pElem_dwCount->SetAttribute("comment", ToUTF8Ptr("数量"));
	if(rElement.LinkEndChild(pElem_dwCount.get()) != NULL)
		pElem_dwCount.release();
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
	unique_ptr<TiXmlElement> pElem_eBindType(new TiXmlElement("EBindType"));
	if(pElem_eBindType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eBindType->SetAttribute("name", "eBindType");
	const char* pszEnum_eBindType = EnumValToStr(s.eBindType);
	if(pszEnum_eBindType == NULL)
	{
		LOG_CRI << "EnumValToStr for EBindType fails!";
		return false;
	}
	pElem_eBindType->SetAttribute("value", pszEnum_eBindType);
	pElem_eBindType->SetAttribute("comment", ToUTF8Ptr("绑定类型"));
	if(rElement.LinkEndChild(pElem_eBindType.get()) != NULL)
		pElem_eBindType.release();
	unique_ptr<TiXmlElement> pElem_dwTimeID(new TiXmlElement("UINT32"));
	if(pElem_dwTimeID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwTimeID->SetAttribute("name", "dwTimeID");
	pElem_dwTimeID->SetAttribute("value", NumberToString(s.dwTimeID).c_str());
	pElem_dwTimeID->SetAttribute("comment", ToUTF8Ptr("时钟ID"));
	if(rElement.LinkEndChild(pElem_dwTimeID.get()) != NULL)
		pElem_dwTimeID.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecItemGenInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SItemGenInfo s;
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

bool VectorToXML(const TVecItemGenInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SItemGenInfo"));
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

SInstCount::SInstCount() : qwInstID(0), wCount(0) { }

SInstCount::SInstCount(UINT64 qwInstID_, UINT32 wCount_) : qwInstID(qwInstID_), wCount(wCount_) { }

CInArchive& operator>>(CInArchive& src, SInstCount& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwInstID;
	src >> s.wCount;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SInstCount& s)
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
	src << s.wCount;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SInstCount& s)
{
	if(strcmp(rElement.Value(), "SInstCount") != 0)
	{
		LOG_CRI << "rElement is not SInstCount!";
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
		LOG_CRI << "pElemChild for wCount is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wCount") != 0)
	{
		LOG_CRI << "Attribute: name is not wCount!";
		return false;
	}
	const char* pszVal_wCount = pElemChild->Attribute("value");
	if(pszVal_wCount == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wCount, s.wCount))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SInstCount& s, TiXmlElement& rElement)
{
	rElement.SetValue("SInstCount");
	rElement.SetAttribute("type", ToUTF8Ptr("物品列表"));
	unique_ptr<TiXmlElement> pElem_qwInstID(new TiXmlElement("UINT64"));
	if(pElem_qwInstID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwInstID->SetAttribute("name", "qwInstID");
	pElem_qwInstID->SetAttribute("value", NumberToString(s.qwInstID).c_str());
	pElem_qwInstID->SetAttribute("comment", ToUTF8Ptr("道具唯一ID"));
	if(rElement.LinkEndChild(pElem_qwInstID.get()) != NULL)
		pElem_qwInstID.release();
	unique_ptr<TiXmlElement> pElem_wCount(new TiXmlElement("UINT32"));
	if(pElem_wCount == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wCount->SetAttribute("name", "wCount");
	pElem_wCount->SetAttribute("value", NumberToString(s.wCount).c_str());
	pElem_wCount->SetAttribute("comment", ToUTF8Ptr("道具个数"));
	if(rElement.LinkEndChild(pElem_wCount.get()) != NULL)
		pElem_wCount.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecInstCount& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SInstCount s;
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

bool VectorToXML(const TVecInstCount& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SInstCount"));
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

SItemCount::SItemCount() : wItemID(0), wCount(0) { }

SItemCount::SItemCount(UINT16 wItemID_, UINT32 wCount_) : wItemID(wItemID_), wCount(wCount_) { }

CInArchive& operator>>(CInArchive& src, SItemCount& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.wItemID;
	src >> s.wCount;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SItemCount& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.wItemID;
	src << s.wCount;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SItemCount& s)
{
	if(strcmp(rElement.Value(), "SItemCount") != 0)
	{
		LOG_CRI << "rElement is not SItemCount!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wItemID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wItemID") != 0)
	{
		LOG_CRI << "Attribute: name is not wItemID!";
		return false;
	}
	const char* pszVal_wItemID = pElemChild->Attribute("value");
	if(pszVal_wItemID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wItemID, s.wItemID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wCount is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wCount") != 0)
	{
		LOG_CRI << "Attribute: name is not wCount!";
		return false;
	}
	const char* pszVal_wCount = pElemChild->Attribute("value");
	if(pszVal_wCount == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wCount, s.wCount))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SItemCount& s, TiXmlElement& rElement)
{
	rElement.SetValue("SItemCount");
	rElement.SetAttribute("type", ToUTF8Ptr("物品列表"));
	unique_ptr<TiXmlElement> pElem_wItemID(new TiXmlElement("UINT16"));
	if(pElem_wItemID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wItemID->SetAttribute("name", "wItemID");
	pElem_wItemID->SetAttribute("value", NumberToString(s.wItemID).c_str());
	pElem_wItemID->SetAttribute("comment", ToUTF8Ptr("道具ID"));
	if(rElement.LinkEndChild(pElem_wItemID.get()) != NULL)
		pElem_wItemID.release();
	unique_ptr<TiXmlElement> pElem_wCount(new TiXmlElement("UINT32"));
	if(pElem_wCount == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wCount->SetAttribute("name", "wCount");
	pElem_wCount->SetAttribute("value", NumberToString(s.wCount).c_str());
	pElem_wCount->SetAttribute("comment", ToUTF8Ptr("道具个数"));
	if(rElement.LinkEndChild(pElem_wCount.get()) != NULL)
		pElem_wCount.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecItemCount& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SItemCount s;
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

bool VectorToXML(const TVecItemCount& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SItemCount"));
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

SResource::SResource() : _eRes((NProtoCommon::EMoneyType)0), _dwValue(0) { }

SResource::SResource(NProtoCommon::EMoneyType _eRes_, UINT32 _dwValue_) : _eRes(_eRes_), _dwValue(_dwValue_) { }

CInArchive& operator>>(CInArchive& src, SResource& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (UINT8&)s._eRes;
	src >> s._dwValue;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SResource& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (UINT8&)s._eRes;
	src << s._dwValue;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SResource& s)
{
	if(strcmp(rElement.Value(), "SResource") != 0)
	{
		LOG_CRI << "rElement is not SResource!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for _eRes is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "ProtoCommon::EMoneyType") != 0)
	{
		LOG_CRI << "pElemChild is not ProtoCommon::EMoneyType!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "_eRes") != 0)
	{
		LOG_CRI << "Attribute: name is not _eRes!";
		return false;
	}
	const char* pszVal__eRes = pElemChild->Attribute("value");
	if(pszVal__eRes == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!NProtoCommon::EnumStrToVal(pszVal__eRes, s._eRes))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for _dwValue is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "_dwValue") != 0)
	{
		LOG_CRI << "Attribute: name is not _dwValue!";
		return false;
	}
	const char* pszVal__dwValue = pElemChild->Attribute("value");
	if(pszVal__dwValue == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal__dwValue, s._dwValue))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SResource& s, TiXmlElement& rElement)
{
	rElement.SetValue("SResource");
	rElement.SetAttribute("type", ToUTF8Ptr("资源列表"));
	unique_ptr<TiXmlElement> pElem__eRes(new TiXmlElement("ProtoCommon::EMoneyType"));
	if(pElem__eRes == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem__eRes->SetAttribute("name", "_eRes");
	const char* pszEnum__eRes = NProtoCommon::EnumValToStr(s._eRes);
	if(pszEnum__eRes == NULL)
	{
		LOG_CRI << "EnumValToStr for _eRes fails!";
		return false;
	}
	pElem__eRes->SetAttribute("value", pszEnum__eRes);
	pElem__eRes->SetAttribute("comment", ToUTF8Ptr("资源(货币)类型"));
	if(rElement.LinkEndChild(pElem__eRes.get()) != NULL)
		pElem__eRes.release();
	unique_ptr<TiXmlElement> pElem__dwValue(new TiXmlElement("UINT32"));
	if(pElem__dwValue == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem__dwValue->SetAttribute("name", "_dwValue");
	pElem__dwValue->SetAttribute("value", NumberToString(s._dwValue).c_str());
	pElem__dwValue->SetAttribute("comment", ToUTF8Ptr("资源(货币)数量"));
	if(rElement.LinkEndChild(pElem__dwValue.get()) != NULL)
		pElem__dwValue.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecResource& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SResource s;
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

bool VectorToXML(const TVecResource& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SResource"));
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

RoleItemInfo::RoleItemInfo() : qwInstID(0), wItemID(0), byStoreType(0), wIndex(0), wCount(0), 
			byBind(0), byExpired(0), dwExpireTime(0), dwMark(0) { }

RoleItemInfo::RoleItemInfo(UINT64 qwInstID_, UINT16 wItemID_, UINT8 byStoreType_, INT16 wIndex_, UINT16 wCount_, 
			UINT8 byBind_, UINT8 byExpired_, UINT32 dwExpireTime_, UINT32 dwMark_)
			: qwInstID(qwInstID_), wItemID(wItemID_), byStoreType(byStoreType_), wIndex(wIndex_), wCount(wCount_), 
			byBind(byBind_), byExpired(byExpired_), dwExpireTime(dwExpireTime_), dwMark(dwMark_) { }

CInArchive& operator>>(CInArchive& src, RoleItemInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwInstID;
	src >> s.wItemID;
	src >> s.byStoreType;
	src >> s.wIndex;
	src >> s.wCount;
	src >> s.byBind;
	src >> s.byExpired;
	src >> s.dwExpireTime;
	src >> s.dwMark;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const RoleItemInfo& s)
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
	src << s.wItemID;
	src << s.byStoreType;
	src << s.wIndex;
	src << s.wCount;
	src << s.byBind;
	src << s.byExpired;
	src << s.dwExpireTime;
	src << s.dwMark;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, RoleItemInfo& s)
{
	if(strcmp(rElement.Value(), "RoleItemInfo") != 0)
	{
		LOG_CRI << "rElement is not RoleItemInfo!";
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
		LOG_CRI << "pElemChild for wItemID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wItemID") != 0)
	{
		LOG_CRI << "Attribute: name is not wItemID!";
		return false;
	}
	const char* pszVal_wItemID = pElemChild->Attribute("value");
	if(pszVal_wItemID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wItemID, s.wItemID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byStoreType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byStoreType") != 0)
	{
		LOG_CRI << "Attribute: name is not byStoreType!";
		return false;
	}
	const char* pszVal_byStoreType = pElemChild->Attribute("value");
	if(pszVal_byStoreType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byStoreType, s.byStoreType))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wIndex is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "INT16") != 0)
	{
		LOG_CRI << "pElemChild is not INT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wIndex") != 0)
	{
		LOG_CRI << "Attribute: name is not wIndex!";
		return false;
	}
	const char* pszVal_wIndex = pElemChild->Attribute("value");
	if(pszVal_wIndex == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wIndex, s.wIndex))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wCount is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wCount") != 0)
	{
		LOG_CRI << "Attribute: name is not wCount!";
		return false;
	}
	const char* pszVal_wCount = pElemChild->Attribute("value");
	if(pszVal_wCount == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wCount, s.wCount))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byBind is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byBind") != 0)
	{
		LOG_CRI << "Attribute: name is not byBind!";
		return false;
	}
	const char* pszVal_byBind = pElemChild->Attribute("value");
	if(pszVal_byBind == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byBind, s.byBind))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byExpired is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byExpired") != 0)
	{
		LOG_CRI << "Attribute: name is not byExpired!";
		return false;
	}
	const char* pszVal_byExpired = pElemChild->Attribute("value");
	if(pszVal_byExpired == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byExpired, s.byExpired))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwExpireTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwExpireTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwExpireTime!";
		return false;
	}
	const char* pszVal_dwExpireTime = pElemChild->Attribute("value");
	if(pszVal_dwExpireTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwExpireTime, s.dwExpireTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwMark is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwMark") != 0)
	{
		LOG_CRI << "Attribute: name is not dwMark!";
		return false;
	}
	const char* pszVal_dwMark = pElemChild->Attribute("value");
	if(pszVal_dwMark == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwMark, s.dwMark))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const RoleItemInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("RoleItemInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("EDataType:eRoleItemInfo"));
	unique_ptr<TiXmlElement> pElem_qwInstID(new TiXmlElement("UINT64"));
	if(pElem_qwInstID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwInstID->SetAttribute("name", "qwInstID");
	pElem_qwInstID->SetAttribute("value", NumberToString(s.qwInstID).c_str());
	pElem_qwInstID->SetAttribute("comment", ToUTF8Ptr("物品唯一ID"));
	if(rElement.LinkEndChild(pElem_qwInstID.get()) != NULL)
		pElem_qwInstID.release();
	unique_ptr<TiXmlElement> pElem_wItemID(new TiXmlElement("UINT16"));
	if(pElem_wItemID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wItemID->SetAttribute("name", "wItemID");
	pElem_wItemID->SetAttribute("value", NumberToString(s.wItemID).c_str());
	pElem_wItemID->SetAttribute("comment", ToUTF8Ptr("物品模板"));
	if(rElement.LinkEndChild(pElem_wItemID.get()) != NULL)
		pElem_wItemID.release();
	unique_ptr<TiXmlElement> pElem_byStoreType(new TiXmlElement("UINT8"));
	if(pElem_byStoreType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byStoreType->SetAttribute("name", "byStoreType");
	pElem_byStoreType->SetAttribute("value", NumberToString(s.byStoreType).c_str());
	pElem_byStoreType->SetAttribute("comment", ToUTF8Ptr("背包类型-数据来源：EStoreType"));
	if(rElement.LinkEndChild(pElem_byStoreType.get()) != NULL)
		pElem_byStoreType.release();
	unique_ptr<TiXmlElement> pElem_wIndex(new TiXmlElement("INT16"));
	if(pElem_wIndex == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wIndex->SetAttribute("name", "wIndex");
	pElem_wIndex->SetAttribute("value", NumberToString(s.wIndex).c_str());
	pElem_wIndex->SetAttribute("comment", ToUTF8Ptr("所属背包的位置"));
	if(rElement.LinkEndChild(pElem_wIndex.get()) != NULL)
		pElem_wIndex.release();
	unique_ptr<TiXmlElement> pElem_wCount(new TiXmlElement("UINT16"));
	if(pElem_wCount == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wCount->SetAttribute("name", "wCount");
	pElem_wCount->SetAttribute("value", NumberToString(s.wCount).c_str());
	pElem_wCount->SetAttribute("comment", ToUTF8Ptr("具的堆叠数"));
	if(rElement.LinkEndChild(pElem_wCount.get()) != NULL)
		pElem_wCount.release();
	unique_ptr<TiXmlElement> pElem_byBind(new TiXmlElement("UINT8"));
	if(pElem_byBind == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byBind->SetAttribute("name", "byBind");
	pElem_byBind->SetAttribute("value", NumberToString(s.byBind).c_str());
	pElem_byBind->SetAttribute("comment", ToUTF8Ptr("绑定类型0非绑定，1绑定"));
	if(rElement.LinkEndChild(pElem_byBind.get()) != NULL)
		pElem_byBind.release();
	unique_ptr<TiXmlElement> pElem_byExpired(new TiXmlElement("UINT8"));
	if(pElem_byExpired == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byExpired->SetAttribute("name", "byExpired");
	pElem_byExpired->SetAttribute("value", NumberToString(s.byExpired).c_str());
	pElem_byExpired->SetAttribute("comment", ToUTF8Ptr("是否时效，>0 时效物品"));
	if(rElement.LinkEndChild(pElem_byExpired.get()) != NULL)
		pElem_byExpired.release();
	unique_ptr<TiXmlElement> pElem_dwExpireTime(new TiXmlElement("UINT32"));
	if(pElem_dwExpireTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwExpireTime->SetAttribute("name", "dwExpireTime");
	pElem_dwExpireTime->SetAttribute("value", NumberToString(s.dwExpireTime).c_str());
	pElem_dwExpireTime->SetAttribute("comment", ToUTF8Ptr("时效过期时间"));
	if(rElement.LinkEndChild(pElem_dwExpireTime.get()) != NULL)
		pElem_dwExpireTime.release();
	unique_ptr<TiXmlElement> pElem_dwMark(new TiXmlElement("UINT32"));
	if(pElem_dwMark == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwMark->SetAttribute("name", "dwMark");
	pElem_dwMark->SetAttribute("value", NumberToString(s.dwMark).c_str());
	pElem_dwMark->SetAttribute("comment", ToUTF8Ptr("标记为错误物品,存下标记时间"));
	if(rElement.LinkEndChild(pElem_dwMark.get()) != NULL)
		pElem_dwMark.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecRoleItemInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		RoleItemInfo s;
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

bool VectorToXML(const TVecRoleItemInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("RoleItemInfo"));
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

SShuffleInfo::SShuffleInfo() : dwType(0), dwValue(0) { }

SShuffleInfo::SShuffleInfo(UINT32 dwType_, UINT32 dwValue_) : dwType(dwType_), dwValue(dwValue_) { }

CInArchive& operator>>(CInArchive& src, SShuffleInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.dwType;
	src >> s.dwValue;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SShuffleInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.dwType;
	src << s.dwValue;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SShuffleInfo& s)
{
	if(strcmp(rElement.Value(), "SShuffleInfo") != 0)
	{
		LOG_CRI << "rElement is not SShuffleInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwType") != 0)
	{
		LOG_CRI << "Attribute: name is not dwType!";
		return false;
	}
	const char* pszVal_dwType = pElemChild->Attribute("value");
	if(pszVal_dwType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwType, s.dwType))
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
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
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

bool ToXML(const SShuffleInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SShuffleInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("洗炼信息"));
	unique_ptr<TiXmlElement> pElem_dwType(new TiXmlElement("UINT32"));
	if(pElem_dwType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwType->SetAttribute("name", "dwType");
	pElem_dwType->SetAttribute("value", NumberToString(s.dwType).c_str());
	pElem_dwType->SetAttribute("comment", ToUTF8Ptr("洗炼类型"));
	if(rElement.LinkEndChild(pElem_dwType.get()) != NULL)
		pElem_dwType.release();
	unique_ptr<TiXmlElement> pElem_dwValue(new TiXmlElement("UINT32"));
	if(pElem_dwValue == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwValue->SetAttribute("name", "dwValue");
	pElem_dwValue->SetAttribute("value", NumberToString(s.dwValue).c_str());
	pElem_dwValue->SetAttribute("comment", ToUTF8Ptr("洗炼数值"));
	if(rElement.LinkEndChild(pElem_dwValue.get()) != NULL)
		pElem_dwValue.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecShuffleInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SShuffleInfo s;
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

bool VectorToXML(const TVecShuffleInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SShuffleInfo"));
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

SItem::SItem() { }

CInArchive& operator>>(CInArchive& src, SItem& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.sItemInfo;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SItem& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.sItemInfo;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, SItem_Wrapper& rWrapper)
{
	EType_SItem eType = eType_SItem;
	src >> (UINT8&)eType;
	switch(eType)
	{
	case eType_SItem:
		{
			rWrapper.ptr.reset(new SItem);
			src >> (SItem&)*rWrapper.ptr;
		}
		break;
	case eType_SStack:
		{
			rWrapper.ptr.reset(new SStack);
			src >> (SStack&)*rWrapper.ptr;
		}
		break;
	case eType_SEquipTrump:
		{
			rWrapper.ptr.reset(new SEquipTrump);
			src >> (SEquipTrump&)*rWrapper.ptr;
		}
		break;
	case eType_SCitta:
		{
			rWrapper.ptr.reset(new SCitta);
			src >> (SCitta&)*rWrapper.ptr;
		}
		break;
	case eType_STrump:
		{
			rWrapper.ptr.reset(new STrump);
			src >> (STrump&)*rWrapper.ptr;
		}
		break;
	case eType_SFashion:
		{
			rWrapper.ptr.reset(new SFashion);
			src >> (SFashion&)*rWrapper.ptr;
		}
		break;
	case eType_SGemstone:
		{
			rWrapper.ptr.reset(new SGemstone);
			src >> (SGemstone&)*rWrapper.ptr;
		}
		break;
	default:
		throw "Unknown value for EType_SItem";
		break;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SItem_Wrapper& rWrapper)
{
	if(rWrapper.ptr != NULL)
	{
		src << (UINT8)rWrapper.ptr->GetClassType();
		switch(rWrapper.ptr->GetClassType())
		{
		case eType_SItem:
			src << (SItem&)*rWrapper.ptr;
			break;
		case eType_SStack:
			src << (SStack&)*rWrapper.ptr;
			break;
		case eType_SEquipTrump:
			src << (SEquipTrump&)*rWrapper.ptr;
			break;
		case eType_SCitta:
			src << (SCitta&)*rWrapper.ptr;
			break;
		case eType_STrump:
			src << (STrump&)*rWrapper.ptr;
			break;
		case eType_SFashion:
			src << (SFashion&)*rWrapper.ptr;
			break;
		case eType_SGemstone:
			src << (SGemstone&)*rWrapper.ptr;
			break;
		default:
			throw "Unknown value for EType_SItem";
			break;
		}
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecItem& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SItem_Wrapper wrapper;
		src >> wrapper;
		vec[i] = wrapper.ptr;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecItem& vec)
{
	if(vec.size() > 0x7FFF)
		throw "Vector Size Too Large!";
	UINT16 wSize = (UINT16)vec.size();
	src.WriteContainerSize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SItem_Wrapper wrapper;
		wrapper.ptr = vec[i];
		src << wrapper;
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SItem& s)
{
	if(strcmp(rElement.Value(), "SItem") != 0)
	{
		LOG_CRI << "rElement is not SItem!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for sItemInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "RoleItemInfo") != 0)
	{
		LOG_CRI << "pElemChild is not RoleItemInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "sItemInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not sItemInfo!";
		return false;
	}
	if(!FromXML(*pElemChild, s.sItemInfo))
	{
		LOG_CRI << "FromXML for: sItemInfo fails!";
		return false;
	}
	return true;
}

bool ToXML(const SItem& s, TiXmlElement& rElement)
{
	rElement.SetValue("SItem");
	rElement.SetAttribute("type", ToUTF8Ptr("道具的信息"));
	unique_ptr<TiXmlElement> pElem_sItemInfo(new TiXmlElement("RoleItemInfo"));
	if(pElem_sItemInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_sItemInfo->SetAttribute("name", "sItemInfo");
	if(!ToXML(s.sItemInfo, *pElem_sItemInfo))
	{
		LOG_CRI << "sItemInfo ToXML fails!";
		return false;
	}
	pElem_sItemInfo->SetAttribute("comment", ToUTF8Ptr("道具信息"));
	if(rElement.LinkEndChild(pElem_sItemInfo.get()) != NULL)
		pElem_sItemInfo.release();
	return true;
}

bool SuperFromXML(TiXmlElement& rElement, SItemPtr& p)
{
	const char* pszName = rElement.Value();
	if(pszName == NULL)
	{
		LOG_CRI << "Element Name is empty!";
		return false;
	}
	if(strcmp(pszName, "SItem") == 0)
	{
		SItemPtr pStruct(new SItem);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SItem";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SItem FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SStack") == 0)
	{
		SStackPtr pStruct(new SStack);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SStack";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SStack FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SEquipTrump") == 0)
	{
		SEquipTrumpPtr pStruct(new SEquipTrump);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SEquipTrump";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SEquipTrump FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SCitta") == 0)
	{
		SCittaPtr pStruct(new SCitta);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SCitta";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SCitta FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "STrump") == 0)
	{
		STrumpPtr pStruct(new STrump);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for STrump";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "STrump FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SFashion") == 0)
	{
		SFashionPtr pStruct(new SFashion);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SFashion";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SFashion FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SGemstone") == 0)
	{
		SGemstonePtr pStruct(new SGemstone);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SGemstone";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SGemstone FromXML fails!";
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

bool SuperToXML(const SItem& s, TiXmlElement& rElement)
{
	switch(s.GetClassType())
	{
	case eType_SItem:
		return ToXML((SItem&)s, rElement);
	case eType_SStack:
		return ToXML((SStack&)s, rElement);
	case eType_SEquipTrump:
		return ToXML((SEquipTrump&)s, rElement);
	case eType_SCitta:
		return ToXML((SCitta&)s, rElement);
	case eType_STrump:
		return ToXML((STrump&)s, rElement);
	case eType_SFashion:
		return ToXML((SFashion&)s, rElement);
	case eType_SGemstone:
		return ToXML((SGemstone&)s, rElement);
	default:
		LOG_CRI << "Invalid type: " << s.GetClassType();
		return false;
	}
}

bool VectorFromXML(TiXmlElement& rElement, TVecItem& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SItemPtr p;
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

bool VectorToXML(const TVecItem& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SItem"));
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

SStack::SStack() { }

CInArchive& operator>>(CInArchive& src, SStack& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (SItem&)s;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SStack& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const SItem&)s;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecStack& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SStackPtr p(new SStack);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecStack& vec)
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

bool FromXML(TiXmlElement& rElement, SStack& s)
{
	if(strcmp(rElement.Value(), "SStack") != 0)
	{
		LOG_CRI << "rElement is not SStack!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for SItem is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (SItem&)s))
	{
		LOG_CRI << "FromXML for: SItem fails!";
		return false;
	}
	return true;
}

bool ToXML(const SStack& s, TiXmlElement& rElement)
{
	rElement.SetValue("SStack");
	rElement.SetAttribute("type", ToUTF8Ptr("堆叠道具的信息，只用于识别"));
	unique_ptr<TiXmlElement> pElem_SItem(new TiXmlElement("SItem"));
	if(pElem_SItem == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const SItem&)s, *pElem_SItem))
	{
		LOG_CRI << "SItem ToXML fails!";
		return false;
	}
	pElem_SItem->SetAttribute("type", ToUTF8Ptr("道具的信息"));
	pElem_SItem->SetAttribute("comment", ToUTF8Ptr("父类SItem部分"));
	if(rElement.LinkEndChild(pElem_SItem.get()) != NULL)
		pElem_SItem.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecStack& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SStackPtr p(new SStack);
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

bool VectorToXML(const TVecStack& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SStack"));
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

SEquipTrump::SEquipTrump() : qwOwnerID(0), byIntensifyLvl(0), byIntensifyLvlMax(0), dwBlessing(0), dwXiLianBlessing(0) { }

SEquipTrump::SEquipTrump(SEquipTrump&& src) : SItem(src), qwOwnerID(src.qwOwnerID), byIntensifyLvl(src.byIntensifyLvl), byIntensifyLvlMax(src.byIntensifyLvlMax), dwBlessing(src.dwBlessing), vecShuffleInfo(move(src.vecShuffleInfo)), 
			vecNowReplace(move(src.vecNowReplace)), dwXiLianBlessing(src.dwXiLianBlessing) { }

SEquipTrump& SEquipTrump::operator=(SEquipTrump&& rhs)
{
	if(this != &rhs)
	{
		this->~SEquipTrump();
		new (this) SEquipTrump(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SEquipTrump& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (SItem&)s;
	src >> s.qwOwnerID;
	src >> s.byIntensifyLvl;
	src >> s.byIntensifyLvlMax;
	src >> s.dwBlessing;
	src >> s.vecShuffleInfo;
	src >> s.vecNowReplace;
	src >> s.dwXiLianBlessing;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SEquipTrump& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const SItem&)s;
	src << s.qwOwnerID;
	src << s.byIntensifyLvl;
	src << s.byIntensifyLvlMax;
	src << s.dwBlessing;
	src << s.vecShuffleInfo;
	src << s.vecNowReplace;
	src << s.dwXiLianBlessing;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecEquipTrump& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SEquipTrumpPtr p(new SEquipTrump);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecEquipTrump& vec)
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

bool FromXML(TiXmlElement& rElement, SEquipTrump& s)
{
	if(strcmp(rElement.Value(), "SEquipTrump") != 0)
	{
		LOG_CRI << "rElement is not SEquipTrump!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for SItem is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (SItem&)s))
	{
		LOG_CRI << "FromXML for: SItem fails!";
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
		LOG_CRI << "pElemChild for byIntensifyLvl is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byIntensifyLvl") != 0)
	{
		LOG_CRI << "Attribute: name is not byIntensifyLvl!";
		return false;
	}
	const char* pszVal_byIntensifyLvl = pElemChild->Attribute("value");
	if(pszVal_byIntensifyLvl == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byIntensifyLvl, s.byIntensifyLvl))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byIntensifyLvlMax is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byIntensifyLvlMax") != 0)
	{
		LOG_CRI << "Attribute: name is not byIntensifyLvlMax!";
		return false;
	}
	const char* pszVal_byIntensifyLvlMax = pElemChild->Attribute("value");
	if(pszVal_byIntensifyLvlMax == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byIntensifyLvlMax, s.byIntensifyLvlMax))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwBlessing is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwBlessing") != 0)
	{
		LOG_CRI << "Attribute: name is not dwBlessing!";
		return false;
	}
	const char* pszVal_dwBlessing = pElemChild->Attribute("value");
	if(pszVal_dwBlessing == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwBlessing, s.dwBlessing))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecShuffleInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecShuffleInfo") != 0)
	{
		LOG_CRI << "pElemChild is not TVecShuffleInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecShuffleInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not vecShuffleInfo!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecShuffleInfo))
	{
		LOG_CRI << "VectorFromXML for vecShuffleInfo fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecNowReplace is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecShuffleInfo") != 0)
	{
		LOG_CRI << "pElemChild is not TVecShuffleInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecNowReplace") != 0)
	{
		LOG_CRI << "Attribute: name is not vecNowReplace!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecNowReplace))
	{
		LOG_CRI << "VectorFromXML for vecNowReplace fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwXiLianBlessing is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwXiLianBlessing") != 0)
	{
		LOG_CRI << "Attribute: name is not dwXiLianBlessing!";
		return false;
	}
	const char* pszVal_dwXiLianBlessing = pElemChild->Attribute("value");
	if(pszVal_dwXiLianBlessing == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwXiLianBlessing, s.dwXiLianBlessing))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SEquipTrump& s, TiXmlElement& rElement)
{
	rElement.SetValue("SEquipTrump");
	rElement.SetAttribute("type", ToUTF8Ptr("装备的信息"));
	unique_ptr<TiXmlElement> pElem_SItem(new TiXmlElement("SItem"));
	if(pElem_SItem == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const SItem&)s, *pElem_SItem))
	{
		LOG_CRI << "SItem ToXML fails!";
		return false;
	}
	pElem_SItem->SetAttribute("type", ToUTF8Ptr("道具的信息"));
	pElem_SItem->SetAttribute("comment", ToUTF8Ptr("父类SItem部分"));
	if(rElement.LinkEndChild(pElem_SItem.get()) != NULL)
		pElem_SItem.release();
	unique_ptr<TiXmlElement> pElem_qwOwnerID(new TiXmlElement("UINT64"));
	if(pElem_qwOwnerID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwOwnerID->SetAttribute("name", "qwOwnerID");
	pElem_qwOwnerID->SetAttribute("value", NumberToString(s.qwOwnerID).c_str());
	pElem_qwOwnerID->SetAttribute("comment", ToUTF8Ptr("散仙唯一ID，属于散仙的物品时有效"));
	if(rElement.LinkEndChild(pElem_qwOwnerID.get()) != NULL)
		pElem_qwOwnerID.release();
	unique_ptr<TiXmlElement> pElem_byIntensifyLvl(new TiXmlElement("UINT8"));
	if(pElem_byIntensifyLvl == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byIntensifyLvl->SetAttribute("name", "byIntensifyLvl");
	pElem_byIntensifyLvl->SetAttribute("value", NumberToString(s.byIntensifyLvl).c_str());
	pElem_byIntensifyLvl->SetAttribute("comment", ToUTF8Ptr("当前强化等级"));
	if(rElement.LinkEndChild(pElem_byIntensifyLvl.get()) != NULL)
		pElem_byIntensifyLvl.release();
	unique_ptr<TiXmlElement> pElem_byIntensifyLvlMax(new TiXmlElement("UINT8"));
	if(pElem_byIntensifyLvlMax == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byIntensifyLvlMax->SetAttribute("name", "byIntensifyLvlMax");
	pElem_byIntensifyLvlMax->SetAttribute("value", NumberToString(s.byIntensifyLvlMax).c_str());
	pElem_byIntensifyLvlMax->SetAttribute("comment", ToUTF8Ptr("可强的最高等级"));
	if(rElement.LinkEndChild(pElem_byIntensifyLvlMax.get()) != NULL)
		pElem_byIntensifyLvlMax.release();
	unique_ptr<TiXmlElement> pElem_dwBlessing(new TiXmlElement("UINT32"));
	if(pElem_dwBlessing == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwBlessing->SetAttribute("name", "dwBlessing");
	pElem_dwBlessing->SetAttribute("value", NumberToString(s.dwBlessing).c_str());
	pElem_dwBlessing->SetAttribute("comment", ToUTF8Ptr("强化祝福值"));
	if(rElement.LinkEndChild(pElem_dwBlessing.get()) != NULL)
		pElem_dwBlessing.release();
	unique_ptr<TiXmlElement> pElem_vecShuffleInfo(new TiXmlElement("TVecShuffleInfo"));
	if(pElem_vecShuffleInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecShuffleInfo->SetAttribute("name", "vecShuffleInfo");
	if(!VectorToXML(s.vecShuffleInfo, *pElem_vecShuffleInfo))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecShuffleInfo->SetAttribute("comment", ToUTF8Ptr("洗炼信息"));
	if(rElement.LinkEndChild(pElem_vecShuffleInfo.get()) != NULL)
		pElem_vecShuffleInfo.release();
	unique_ptr<TiXmlElement> pElem_vecNowReplace(new TiXmlElement("TVecShuffleInfo"));
	if(pElem_vecNowReplace == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecNowReplace->SetAttribute("name", "vecNowReplace");
	if(!VectorToXML(s.vecNowReplace, *pElem_vecNowReplace))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecNowReplace->SetAttribute("comment", ToUTF8Ptr("可替换的洗炼信息"));
	if(rElement.LinkEndChild(pElem_vecNowReplace.get()) != NULL)
		pElem_vecNowReplace.release();
	unique_ptr<TiXmlElement> pElem_dwXiLianBlessing(new TiXmlElement("UINT32"));
	if(pElem_dwXiLianBlessing == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwXiLianBlessing->SetAttribute("name", "dwXiLianBlessing");
	pElem_dwXiLianBlessing->SetAttribute("value", NumberToString(s.dwXiLianBlessing).c_str());
	pElem_dwXiLianBlessing->SetAttribute("comment", ToUTF8Ptr("洗练祝福值"));
	if(rElement.LinkEndChild(pElem_dwXiLianBlessing.get()) != NULL)
		pElem_dwXiLianBlessing.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecEquipTrump& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SEquipTrumpPtr p(new SEquipTrump);
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

bool VectorToXML(const TVecEquipTrump& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SEquipTrump"));
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

SCitta::SCitta() : qwOwnerID(0), eCittaNameType((ECittaNameType)0), dwSkillID(0), dwSignetID(0) { }

SCitta::SCitta(SCitta&& src) : SItem(src), qwOwnerID(src.qwOwnerID), eCittaNameType(src.eCittaNameType), oAttrVec(move(src.oAttrVec)), dwSkillID(src.dwSkillID), dwSignetID(src.dwSignetID) { }

SCitta& SCitta::operator=(SCitta&& rhs)
{
	if(this != &rhs)
	{
		this->~SCitta();
		new (this) SCitta(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SCitta& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (SItem&)s;
	src >> s.qwOwnerID;
	src >> (UINT8&)s.eCittaNameType;
	src >> s.oAttrVec;
	src >> s.dwSkillID;
	src >> s.dwSignetID;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SCitta& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const SItem&)s;
	src << s.qwOwnerID;
	src << (UINT8&)s.eCittaNameType;
	src << s.oAttrVec;
	src << s.dwSkillID;
	src << s.dwSignetID;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecCitta& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SCittaPtr p(new SCitta);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecCitta& vec)
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

bool FromXML(TiXmlElement& rElement, SCitta& s)
{
	if(strcmp(rElement.Value(), "SCitta") != 0)
	{
		LOG_CRI << "rElement is not SCitta!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for SItem is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (SItem&)s))
	{
		LOG_CRI << "FromXML for: SItem fails!";
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
		LOG_CRI << "pElemChild for eCittaNameType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "ECittaNameType") != 0)
	{
		LOG_CRI << "pElemChild is not ECittaNameType!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eCittaNameType") != 0)
	{
		LOG_CRI << "Attribute: name is not eCittaNameType!";
		return false;
	}
	const char* pszVal_eCittaNameType = pElemChild->Attribute("value");
	if(pszVal_eCittaNameType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!EnumStrToVal(pszVal_eCittaNameType, s.eCittaNameType))
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
		LOG_CRI << "pElemChild for dwSignetID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwSignetID") != 0)
	{
		LOG_CRI << "Attribute: name is not dwSignetID!";
		return false;
	}
	const char* pszVal_dwSignetID = pElemChild->Attribute("value");
	if(pszVal_dwSignetID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwSignetID, s.dwSignetID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SCitta& s, TiXmlElement& rElement)
{
	rElement.SetValue("SCitta");
	rElement.SetAttribute("type", ToUTF8Ptr("心法的信息"));
	unique_ptr<TiXmlElement> pElem_SItem(new TiXmlElement("SItem"));
	if(pElem_SItem == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const SItem&)s, *pElem_SItem))
	{
		LOG_CRI << "SItem ToXML fails!";
		return false;
	}
	pElem_SItem->SetAttribute("type", ToUTF8Ptr("道具的信息"));
	pElem_SItem->SetAttribute("comment", ToUTF8Ptr("父类SItem部分"));
	if(rElement.LinkEndChild(pElem_SItem.get()) != NULL)
		pElem_SItem.release();
	unique_ptr<TiXmlElement> pElem_qwOwnerID(new TiXmlElement("UINT64"));
	if(pElem_qwOwnerID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwOwnerID->SetAttribute("name", "qwOwnerID");
	pElem_qwOwnerID->SetAttribute("value", NumberToString(s.qwOwnerID).c_str());
	pElem_qwOwnerID->SetAttribute("comment", ToUTF8Ptr("散仙唯一ID，属于散仙的物品时有效"));
	if(rElement.LinkEndChild(pElem_qwOwnerID.get()) != NULL)
		pElem_qwOwnerID.release();
	unique_ptr<TiXmlElement> pElem_eCittaNameType(new TiXmlElement("ECittaNameType"));
	if(pElem_eCittaNameType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eCittaNameType->SetAttribute("name", "eCittaNameType");
	const char* pszEnum_eCittaNameType = EnumValToStr(s.eCittaNameType);
	if(pszEnum_eCittaNameType == NULL)
	{
		LOG_CRI << "EnumValToStr for ECittaNameType fails!";
		return false;
	}
	pElem_eCittaNameType->SetAttribute("value", pszEnum_eCittaNameType);
	pElem_eCittaNameType->SetAttribute("comment", ToUTF8Ptr("心法姓名前缀"));
	if(rElement.LinkEndChild(pElem_eCittaNameType.get()) != NULL)
		pElem_eCittaNameType.release();
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
	pElem_oAttrVec->SetAttribute("comment", ToUTF8Ptr("增加属性"));
	if(rElement.LinkEndChild(pElem_oAttrVec.get()) != NULL)
		pElem_oAttrVec.release();
	unique_ptr<TiXmlElement> pElem_dwSkillID(new TiXmlElement("UINT32"));
	if(pElem_dwSkillID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwSkillID->SetAttribute("name", "dwSkillID");
	pElem_dwSkillID->SetAttribute("value", NumberToString(s.dwSkillID).c_str());
	pElem_dwSkillID->SetAttribute("comment", ToUTF8Ptr("附加技能ID"));
	if(rElement.LinkEndChild(pElem_dwSkillID.get()) != NULL)
		pElem_dwSkillID.release();
	unique_ptr<TiXmlElement> pElem_dwSignetID(new TiXmlElement("UINT32"));
	if(pElem_dwSignetID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwSignetID->SetAttribute("name", "dwSignetID");
	pElem_dwSignetID->SetAttribute("value", NumberToString(s.dwSignetID).c_str());
	pElem_dwSignetID->SetAttribute("comment", ToUTF8Ptr("印记ID"));
	if(rElement.LinkEndChild(pElem_dwSignetID.get()) != NULL)
		pElem_dwSignetID.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecCitta& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SCittaPtr p(new SCitta);
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

bool VectorToXML(const TVecCitta& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SCitta"));
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

STrump::STrump() : qwRoleID(0), byActived(0), byUsed(0), dwExp(0), wLevel(0), 
			wRank(0) { }

CInArchive& operator>>(CInArchive& src, STrump& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (SItem&)s;
	src >> s.qwRoleID;
	src >> s.byActived;
	src >> s.byUsed;
	src >> s.dwExp;
	src >> s.wLevel;
	src >> s.wRank;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const STrump& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const SItem&)s;
	src << s.qwRoleID;
	src << s.byActived;
	src << s.byUsed;
	src << s.dwExp;
	src << s.wLevel;
	src << s.wRank;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecTrump& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		STrumpPtr p(new STrump);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecTrump& vec)
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

bool FromXML(TiXmlElement& rElement, STrump& s)
{
	if(strcmp(rElement.Value(), "STrump") != 0)
	{
		LOG_CRI << "rElement is not STrump!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for SItem is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (SItem&)s))
	{
		LOG_CRI << "FromXML for: SItem fails!";
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
		LOG_CRI << "pElemChild for byActived is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byActived") != 0)
	{
		LOG_CRI << "Attribute: name is not byActived!";
		return false;
	}
	const char* pszVal_byActived = pElemChild->Attribute("value");
	if(pszVal_byActived == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byActived, s.byActived))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byUsed is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byUsed") != 0)
	{
		LOG_CRI << "Attribute: name is not byUsed!";
		return false;
	}
	const char* pszVal_byUsed = pElemChild->Attribute("value");
	if(pszVal_byUsed == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byUsed, s.byUsed))
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
	return true;
}

bool ToXML(const STrump& s, TiXmlElement& rElement)
{
	rElement.SetValue("STrump");
	rElement.SetAttribute("type", ToUTF8Ptr("法宝信息"));
	unique_ptr<TiXmlElement> pElem_SItem(new TiXmlElement("SItem"));
	if(pElem_SItem == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const SItem&)s, *pElem_SItem))
	{
		LOG_CRI << "SItem ToXML fails!";
		return false;
	}
	pElem_SItem->SetAttribute("type", ToUTF8Ptr("道具的信息"));
	pElem_SItem->SetAttribute("comment", ToUTF8Ptr("父类SItem部分"));
	if(rElement.LinkEndChild(pElem_SItem.get()) != NULL)
		pElem_SItem.release();
	unique_ptr<TiXmlElement> pElem_qwRoleID(new TiXmlElement("UINT64"));
	if(pElem_qwRoleID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwRoleID->SetAttribute("name", "qwRoleID");
	pElem_qwRoleID->SetAttribute("value", NumberToString(s.qwRoleID).c_str());
	pElem_qwRoleID->SetAttribute("comment", ToUTF8Ptr("拥有者RoleID"));
	if(rElement.LinkEndChild(pElem_qwRoleID.get()) != NULL)
		pElem_qwRoleID.release();
	unique_ptr<TiXmlElement> pElem_byActived(new TiXmlElement("UINT8"));
	if(pElem_byActived == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byActived->SetAttribute("name", "byActived");
	pElem_byActived->SetAttribute("value", NumberToString(s.byActived).c_str());
	pElem_byActived->SetAttribute("comment", ToUTF8Ptr(""));
	if(rElement.LinkEndChild(pElem_byActived.get()) != NULL)
		pElem_byActived.release();
	unique_ptr<TiXmlElement> pElem_byUsed(new TiXmlElement("UINT8"));
	if(pElem_byUsed == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byUsed->SetAttribute("name", "byUsed");
	pElem_byUsed->SetAttribute("value", NumberToString(s.byUsed).c_str());
	pElem_byUsed->SetAttribute("comment", ToUTF8Ptr("法宝是否出战"));
	if(rElement.LinkEndChild(pElem_byUsed.get()) != NULL)
		pElem_byUsed.release();
	unique_ptr<TiXmlElement> pElem_dwExp(new TiXmlElement("UINT32"));
	if(pElem_dwExp == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwExp->SetAttribute("name", "dwExp");
	pElem_dwExp->SetAttribute("value", NumberToString(s.dwExp).c_str());
	pElem_dwExp->SetAttribute("comment", ToUTF8Ptr("法宝祭炼值"));
	if(rElement.LinkEndChild(pElem_dwExp.get()) != NULL)
		pElem_dwExp.release();
	unique_ptr<TiXmlElement> pElem_wLevel(new TiXmlElement("UINT16"));
	if(pElem_wLevel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wLevel->SetAttribute("name", "wLevel");
	pElem_wLevel->SetAttribute("value", NumberToString(s.wLevel).c_str());
	pElem_wLevel->SetAttribute("comment", ToUTF8Ptr("法宝祭炼等级"));
	if(rElement.LinkEndChild(pElem_wLevel.get()) != NULL)
		pElem_wLevel.release();
	unique_ptr<TiXmlElement> pElem_wRank(new TiXmlElement("UINT16"));
	if(pElem_wRank == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wRank->SetAttribute("name", "wRank");
	pElem_wRank->SetAttribute("value", NumberToString(s.wRank).c_str());
	pElem_wRank->SetAttribute("comment", ToUTF8Ptr("法宝祭炼阶数"));
	if(rElement.LinkEndChild(pElem_wRank.get()) != NULL)
		pElem_wRank.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecTrump& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		STrumpPtr p(new STrump);
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

bool VectorToXML(const TVecTrump& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("STrump"));
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

SFashion::SFashion() : byLevel(0), dwExp(0), bySelected(0), byHide(0) { }

CInArchive& operator>>(CInArchive& src, SFashion& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (SItem&)s;
	src >> s.byLevel;
	src >> s.dwExp;
	src >> s.bySelected;
	src >> s.byHide;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SFashion& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const SItem&)s;
	src << s.byLevel;
	src << s.dwExp;
	src << s.bySelected;
	src << s.byHide;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecFashion& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SFashionPtr p(new SFashion);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecFashion& vec)
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

bool FromXML(TiXmlElement& rElement, SFashion& s)
{
	if(strcmp(rElement.Value(), "SFashion") != 0)
	{
		LOG_CRI << "rElement is not SFashion!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for SItem is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (SItem&)s))
	{
		LOG_CRI << "FromXML for: SItem fails!";
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
		LOG_CRI << "pElemChild for bySelected is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "bySelected") != 0)
	{
		LOG_CRI << "Attribute: name is not bySelected!";
		return false;
	}
	const char* pszVal_bySelected = pElemChild->Attribute("value");
	if(pszVal_bySelected == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_bySelected, s.bySelected))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byHide is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byHide") != 0)
	{
		LOG_CRI << "Attribute: name is not byHide!";
		return false;
	}
	const char* pszVal_byHide = pElemChild->Attribute("value");
	if(pszVal_byHide == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byHide, s.byHide))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SFashion& s, TiXmlElement& rElement)
{
	rElement.SetValue("SFashion");
	rElement.SetAttribute("type", ToUTF8Ptr("时装信息"));
	unique_ptr<TiXmlElement> pElem_SItem(new TiXmlElement("SItem"));
	if(pElem_SItem == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const SItem&)s, *pElem_SItem))
	{
		LOG_CRI << "SItem ToXML fails!";
		return false;
	}
	pElem_SItem->SetAttribute("type", ToUTF8Ptr("道具的信息"));
	pElem_SItem->SetAttribute("comment", ToUTF8Ptr("父类SItem部分"));
	if(rElement.LinkEndChild(pElem_SItem.get()) != NULL)
		pElem_SItem.release();
	unique_ptr<TiXmlElement> pElem_byLevel(new TiXmlElement("UINT8"));
	if(pElem_byLevel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byLevel->SetAttribute("name", "byLevel");
	pElem_byLevel->SetAttribute("value", NumberToString(s.byLevel).c_str());
	pElem_byLevel->SetAttribute("comment", ToUTF8Ptr("时装等级"));
	if(rElement.LinkEndChild(pElem_byLevel.get()) != NULL)
		pElem_byLevel.release();
	unique_ptr<TiXmlElement> pElem_dwExp(new TiXmlElement("UINT32"));
	if(pElem_dwExp == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwExp->SetAttribute("name", "dwExp");
	pElem_dwExp->SetAttribute("value", NumberToString(s.dwExp).c_str());
	pElem_dwExp->SetAttribute("comment", ToUTF8Ptr("时装经验"));
	if(rElement.LinkEndChild(pElem_dwExp.get()) != NULL)
		pElem_dwExp.release();
	unique_ptr<TiXmlElement> pElem_bySelected(new TiXmlElement("UINT8"));
	if(pElem_bySelected == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_bySelected->SetAttribute("name", "bySelected");
	pElem_bySelected->SetAttribute("value", NumberToString(s.bySelected).c_str());
	pElem_bySelected->SetAttribute("comment", ToUTF8Ptr("是否选中"));
	if(rElement.LinkEndChild(pElem_bySelected.get()) != NULL)
		pElem_bySelected.release();
	unique_ptr<TiXmlElement> pElem_byHide(new TiXmlElement("UINT8"));
	if(pElem_byHide == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byHide->SetAttribute("name", "byHide");
	pElem_byHide->SetAttribute("value", NumberToString(s.byHide).c_str());
	pElem_byHide->SetAttribute("comment", ToUTF8Ptr("是否隐藏"));
	if(rElement.LinkEndChild(pElem_byHide.get()) != NULL)
		pElem_byHide.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecFashion& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SFashionPtr p(new SFashion);
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

bool VectorToXML(const TVecFashion& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SFashion"));
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

SGemstone::SGemstone() : qwOwnerID(0) { }

CInArchive& operator>>(CInArchive& src, SGemstone& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (SItem&)s;
	src >> s.qwOwnerID;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SGemstone& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const SItem&)s;
	src << s.qwOwnerID;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecGemstone& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SGemstonePtr p(new SGemstone);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecGemstone& vec)
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

bool FromXML(TiXmlElement& rElement, SGemstone& s)
{
	if(strcmp(rElement.Value(), "SGemstone") != 0)
	{
		LOG_CRI << "rElement is not SGemstone!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for SItem is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (SItem&)s))
	{
		LOG_CRI << "FromXML for: SItem fails!";
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
	return true;
}

bool ToXML(const SGemstone& s, TiXmlElement& rElement)
{
	rElement.SetValue("SGemstone");
	rElement.SetAttribute("type", ToUTF8Ptr("宝石信息"));
	unique_ptr<TiXmlElement> pElem_SItem(new TiXmlElement("SItem"));
	if(pElem_SItem == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const SItem&)s, *pElem_SItem))
	{
		LOG_CRI << "SItem ToXML fails!";
		return false;
	}
	pElem_SItem->SetAttribute("type", ToUTF8Ptr("道具的信息"));
	pElem_SItem->SetAttribute("comment", ToUTF8Ptr("父类SItem部分"));
	if(rElement.LinkEndChild(pElem_SItem.get()) != NULL)
		pElem_SItem.release();
	unique_ptr<TiXmlElement> pElem_qwOwnerID(new TiXmlElement("UINT64"));
	if(pElem_qwOwnerID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwOwnerID->SetAttribute("name", "qwOwnerID");
	pElem_qwOwnerID->SetAttribute("value", NumberToString(s.qwOwnerID).c_str());
	pElem_qwOwnerID->SetAttribute("comment", ToUTF8Ptr("散仙唯一ID"));
	if(rElement.LinkEndChild(pElem_qwOwnerID.get()) != NULL)
		pElem_qwOwnerID.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecGemstone& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SGemstonePtr p(new SGemstone);
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

bool VectorToXML(const TVecGemstone& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SGemstone"));
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

SStoreStream::SStoreStream() : wCapacity(0) { }

SStoreStream::SStoreStream(SStoreStream&& src) : wCapacity(src.wCapacity), vecItem(move(src.vecItem)) { }

SStoreStream& SStoreStream::operator=(SStoreStream&& rhs)
{
	if(this != &rhs)
	{
		this->~SStoreStream();
		new (this) SStoreStream(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SStoreStream& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.wCapacity;
	src >> s.vecItem;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SStoreStream& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.wCapacity;
	src << s.vecItem;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SStoreStream& s)
{
	if(strcmp(rElement.Value(), "SStoreStream") != 0)
	{
		LOG_CRI << "rElement is not SStoreStream!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wCapacity is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wCapacity") != 0)
	{
		LOG_CRI << "Attribute: name is not wCapacity!";
		return false;
	}
	const char* pszVal_wCapacity = pElemChild->Attribute("value");
	if(pszVal_wCapacity == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wCapacity, s.wCapacity))
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
	if(strcmp(pElemChild->Value(), "TVecItem") != 0)
	{
		LOG_CRI << "pElemChild is not TVecItem!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecItem") != 0)
	{
		LOG_CRI << "Attribute: name is not vecItem!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecItem))
	{
		LOG_CRI << "VectorFromXML for vecItem fails!";
		return false;
	}
	return true;
}

bool ToXML(const SStoreStream& s, TiXmlElement& rElement)
{
	rElement.SetValue("SStoreStream");
	rElement.SetAttribute("type", ToUTF8Ptr("背包信息"));
	unique_ptr<TiXmlElement> pElem_wCapacity(new TiXmlElement("UINT16"));
	if(pElem_wCapacity == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wCapacity->SetAttribute("name", "wCapacity");
	pElem_wCapacity->SetAttribute("value", NumberToString(s.wCapacity).c_str());
	pElem_wCapacity->SetAttribute("comment", ToUTF8Ptr("背包大小(不发最大值，最大值由两端的配置决定)"));
	if(rElement.LinkEndChild(pElem_wCapacity.get()) != NULL)
		pElem_wCapacity.release();
	unique_ptr<TiXmlElement> pElem_vecItem(new TiXmlElement("TVecItem"));
	if(pElem_vecItem == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecItem->SetAttribute("name", "vecItem");
	if(!VectorToXML(s.vecItem, *pElem_vecItem))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecItem->SetAttribute("comment", ToUTF8Ptr("物品信息"));
	if(rElement.LinkEndChild(pElem_vecItem.get()) != NULL)
		pElem_vecItem.release();
	return true;
}

#endif

SItemColdTime::SItemColdTime() : wID(0), dwTime(0) { }

SItemColdTime::SItemColdTime(UINT16 wID_, UINT32 dwTime_) : wID(wID_), dwTime(dwTime_) { }

CInArchive& operator>>(CInArchive& src, SItemColdTime& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.wID;
	src >> s.dwTime;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SItemColdTime& s)
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

bool FromXML(TiXmlElement& rElement, SItemColdTime& s)
{
	if(strcmp(rElement.Value(), "SItemColdTime") != 0)
	{
		LOG_CRI << "rElement is not SItemColdTime!";
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

bool ToXML(const SItemColdTime& s, TiXmlElement& rElement)
{
	rElement.SetValue("SItemColdTime");
	rElement.SetAttribute("type", ToUTF8Ptr("玩家道具冷却时间"));
	unique_ptr<TiXmlElement> pElem_wID(new TiXmlElement("UINT16"));
	if(pElem_wID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wID->SetAttribute("name", "wID");
	pElem_wID->SetAttribute("value", NumberToString(s.wID).c_str());
	pElem_wID->SetAttribute("comment", ToUTF8Ptr("冷却ID"));
	if(rElement.LinkEndChild(pElem_wID.get()) != NULL)
		pElem_wID.release();
	unique_ptr<TiXmlElement> pElem_dwTime(new TiXmlElement("UINT32"));
	if(pElem_dwTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwTime->SetAttribute("name", "dwTime");
	pElem_dwTime->SetAttribute("value", NumberToString(s.dwTime).c_str());
	pElem_dwTime->SetAttribute("comment", ToUTF8Ptr("冷却到期时间"));
	if(rElement.LinkEndChild(pElem_dwTime.get()) != NULL)
		pElem_dwTime.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecItemColdTime& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SItemColdTime s;
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

bool VectorToXML(const TVecItemColdTime& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SItemColdTime"));
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

SAddItemMsg::SAddItemMsg() : wItemID(0), wCount(0), byQuality(0) { }

SAddItemMsg::SAddItemMsg(UINT16 wItemID_, UINT16 wCount_, UINT8 byQuality_) : wItemID(wItemID_), wCount(wCount_), byQuality(byQuality_) { }

CInArchive& operator>>(CInArchive& src, SAddItemMsg& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.wItemID;
	src >> s.wCount;
	src >> s.byQuality;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SAddItemMsg& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.wItemID;
	src << s.wCount;
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

bool FromXML(TiXmlElement& rElement, SAddItemMsg& s)
{
	if(strcmp(rElement.Value(), "SAddItemMsg") != 0)
	{
		LOG_CRI << "rElement is not SAddItemMsg!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wItemID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wItemID") != 0)
	{
		LOG_CRI << "Attribute: name is not wItemID!";
		return false;
	}
	const char* pszVal_wItemID = pElemChild->Attribute("value");
	if(pszVal_wItemID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wItemID, s.wItemID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wCount is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wCount") != 0)
	{
		LOG_CRI << "Attribute: name is not wCount!";
		return false;
	}
	const char* pszVal_wCount = pElemChild->Attribute("value");
	if(pszVal_wCount == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wCount, s.wCount))
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

bool ToXML(const SAddItemMsg& s, TiXmlElement& rElement)
{
	rElement.SetValue("SAddItemMsg");
	rElement.SetAttribute("type", ToUTF8Ptr("玩家获得道具"));
	unique_ptr<TiXmlElement> pElem_wItemID(new TiXmlElement("UINT16"));
	if(pElem_wItemID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wItemID->SetAttribute("name", "wItemID");
	pElem_wItemID->SetAttribute("value", NumberToString(s.wItemID).c_str());
	pElem_wItemID->SetAttribute("comment", ToUTF8Ptr("道具的ID"));
	if(rElement.LinkEndChild(pElem_wItemID.get()) != NULL)
		pElem_wItemID.release();
	unique_ptr<TiXmlElement> pElem_wCount(new TiXmlElement("UINT16"));
	if(pElem_wCount == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wCount->SetAttribute("name", "wCount");
	pElem_wCount->SetAttribute("value", NumberToString(s.wCount).c_str());
	pElem_wCount->SetAttribute("comment", ToUTF8Ptr("道具个数"));
	if(rElement.LinkEndChild(pElem_wCount.get()) != NULL)
		pElem_wCount.release();
	unique_ptr<TiXmlElement> pElem_byQuality(new TiXmlElement("UINT8"));
	if(pElem_byQuality == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byQuality->SetAttribute("name", "byQuality");
	pElem_byQuality->SetAttribute("value", NumberToString(s.byQuality).c_str());
	pElem_byQuality->SetAttribute("comment", ToUTF8Ptr("道具品质"));
	if(rElement.LinkEndChild(pElem_byQuality.get()) != NULL)
		pElem_byQuality.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecAddItemMsg& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SAddItemMsg s;
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

bool VectorToXML(const TVecAddItemMsg& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SAddItemMsg"));
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

SLoggedItem::SLoggedItem() : wItemID(0), byQuality(0), dwCount(0), bBind(false) { }

SLoggedItem::SLoggedItem(UINT16 wItemID_, UINT8 byQuality_, UINT32 dwCount_, bool bBind_) : wItemID(wItemID_), byQuality(byQuality_), dwCount(dwCount_), bBind(bBind_) { }

CInArchive& operator>>(CInArchive& src, SLoggedItem& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.wItemID;
	src >> s.byQuality;
	src >> s.dwCount;
	src >> s.bBind;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SLoggedItem& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.wItemID;
	src << s.byQuality;
	src << s.dwCount;
	src << s.bBind;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SLoggedItem& s)
{
	if(strcmp(rElement.Value(), "SLoggedItem") != 0)
	{
		LOG_CRI << "rElement is not SLoggedItem!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wItemID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wItemID") != 0)
	{
		LOG_CRI << "Attribute: name is not wItemID!";
		return false;
	}
	const char* pszVal_wItemID = pElemChild->Attribute("value");
	if(pszVal_wItemID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wItemID, s.wItemID))
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
		LOG_CRI << "pElemChild for bBind is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "bool") != 0)
	{
		LOG_CRI << "pElemChild is not bool!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "bBind") != 0)
	{
		LOG_CRI << "Attribute: name is not bBind!";
		return false;
	}
	const char* pszVal_bBind = pElemChild->Attribute("value");
	if(pszVal_bBind == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_bBind, s.bBind))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SLoggedItem& s, TiXmlElement& rElement)
{
	rElement.SetValue("SLoggedItem");
	rElement.SetAttribute("type", ToUTF8Ptr("记录的道具"));
	unique_ptr<TiXmlElement> pElem_wItemID(new TiXmlElement("UINT16"));
	if(pElem_wItemID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wItemID->SetAttribute("name", "wItemID");
	pElem_wItemID->SetAttribute("value", NumberToString(s.wItemID).c_str());
	pElem_wItemID->SetAttribute("comment", ToUTF8Ptr("道具ID"));
	if(rElement.LinkEndChild(pElem_wItemID.get()) != NULL)
		pElem_wItemID.release();
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
	unique_ptr<TiXmlElement> pElem_dwCount(new TiXmlElement("UINT32"));
	if(pElem_dwCount == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwCount->SetAttribute("name", "dwCount");
	pElem_dwCount->SetAttribute("value", NumberToString(s.dwCount).c_str());
	pElem_dwCount->SetAttribute("comment", ToUTF8Ptr("道具个数"));
	if(rElement.LinkEndChild(pElem_dwCount.get()) != NULL)
		pElem_dwCount.release();
	unique_ptr<TiXmlElement> pElem_bBind(new TiXmlElement("bool"));
	if(pElem_bBind == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_bBind->SetAttribute("name", "bBind");
	pElem_bBind->SetAttribute("value", NumberToString(s.bBind).c_str());
	pElem_bBind->SetAttribute("comment", ToUTF8Ptr("是否绑定"));
	if(rElement.LinkEndChild(pElem_bBind.get()) != NULL)
		pElem_bBind.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecLoggedItem& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SLoggedItem s;
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

bool VectorToXML(const TVecLoggedItem& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SLoggedItem"));
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

SGMMailTarget::SGMMailTarget() : qwTargetID(0) { }

SGMMailTarget::SGMMailTarget(UINT64 qwTargetID_, const std::string& strTarget_) : qwTargetID(qwTargetID_), strTarget(strTarget_) { }

SGMMailTarget::SGMMailTarget(SGMMailTarget&& src) : qwTargetID(src.qwTargetID), strTarget(move(src.strTarget)) { }

SGMMailTarget& SGMMailTarget::operator=(SGMMailTarget&& rhs)
{
	if(this != &rhs)
	{
		this->~SGMMailTarget();
		new (this) SGMMailTarget(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SGMMailTarget& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwTargetID;
	src >> s.strTarget;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SGMMailTarget& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.qwTargetID;
	src << s.strTarget;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SGMMailTarget& s)
{
	if(strcmp(rElement.Value(), "SGMMailTarget") != 0)
	{
		LOG_CRI << "rElement is not SGMMailTarget!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwTargetID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwTargetID") != 0)
	{
		LOG_CRI << "Attribute: name is not qwTargetID!";
		return false;
	}
	const char* pszVal_qwTargetID = pElemChild->Attribute("value");
	if(pszVal_qwTargetID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwTargetID, s.qwTargetID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strTarget is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strTarget") != 0)
	{
		LOG_CRI << "Attribute: name is not strTarget!";
		return false;
	}
	const char* pszVal_strTarget = pElemChild->Attribute("value");
	if(pszVal_strTarget == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strTarget = pszVal_strTarget;
	return true;
}

bool ToXML(const SGMMailTarget& s, TiXmlElement& rElement)
{
	rElement.SetValue("SGMMailTarget");
	rElement.SetAttribute("type", ToUTF8Ptr("收件人信息"));
	unique_ptr<TiXmlElement> pElem_qwTargetID(new TiXmlElement("UINT64"));
	if(pElem_qwTargetID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwTargetID->SetAttribute("name", "qwTargetID");
	pElem_qwTargetID->SetAttribute("value", NumberToString(s.qwTargetID).c_str());
	pElem_qwTargetID->SetAttribute("comment", ToUTF8Ptr("收件人ID"));
	if(rElement.LinkEndChild(pElem_qwTargetID.get()) != NULL)
		pElem_qwTargetID.release();
	unique_ptr<TiXmlElement> pElem_strTarget(new TiXmlElement("string"));
	if(pElem_strTarget == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strTarget->SetAttribute("name", "strTarget");
	pElem_strTarget->SetAttribute("value", s.strTarget.c_str());
	pElem_strTarget->SetAttribute("comment", ToUTF8Ptr("收件人名"));
	if(rElement.LinkEndChild(pElem_strTarget.get()) != NULL)
		pElem_strTarget.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecGMMailTarget& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SGMMailTarget s;
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

bool VectorToXML(const TVecGMMailTarget& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SGMMailTarget"));
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

SGMMailItem::SGMMailItem() : wItemID(0), wItemCount(0) { }

SGMMailItem::SGMMailItem(UINT16 wItemID_, UINT32 wItemCount_) : wItemID(wItemID_), wItemCount(wItemCount_) { }

CInArchive& operator>>(CInArchive& src, SGMMailItem& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.wItemID;
	src >> s.wItemCount;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SGMMailItem& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.wItemID;
	src << s.wItemCount;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SGMMailItem& s)
{
	if(strcmp(rElement.Value(), "SGMMailItem") != 0)
	{
		LOG_CRI << "rElement is not SGMMailItem!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wItemID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wItemID") != 0)
	{
		LOG_CRI << "Attribute: name is not wItemID!";
		return false;
	}
	const char* pszVal_wItemID = pElemChild->Attribute("value");
	if(pszVal_wItemID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wItemID, s.wItemID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wItemCount is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wItemCount") != 0)
	{
		LOG_CRI << "Attribute: name is not wItemCount!";
		return false;
	}
	const char* pszVal_wItemCount = pElemChild->Attribute("value");
	if(pszVal_wItemCount == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wItemCount, s.wItemCount))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SGMMailItem& s, TiXmlElement& rElement)
{
	rElement.SetValue("SGMMailItem");
	rElement.SetAttribute("type", ToUTF8Ptr("道具信息"));
	unique_ptr<TiXmlElement> pElem_wItemID(new TiXmlElement("UINT16"));
	if(pElem_wItemID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wItemID->SetAttribute("name", "wItemID");
	pElem_wItemID->SetAttribute("value", NumberToString(s.wItemID).c_str());
	pElem_wItemID->SetAttribute("comment", ToUTF8Ptr("道具配置ID"));
	if(rElement.LinkEndChild(pElem_wItemID.get()) != NULL)
		pElem_wItemID.release();
	unique_ptr<TiXmlElement> pElem_wItemCount(new TiXmlElement("UINT32"));
	if(pElem_wItemCount == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wItemCount->SetAttribute("name", "wItemCount");
	pElem_wItemCount->SetAttribute("value", NumberToString(s.wItemCount).c_str());
	pElem_wItemCount->SetAttribute("comment", ToUTF8Ptr("道具数量"));
	if(rElement.LinkEndChild(pElem_wItemCount.get()) != NULL)
		pElem_wItemCount.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecGMMailItem& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SGMMailItem s;
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

bool VectorToXML(const TVecGMMailItem& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SGMMailItem"));
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

} //namespace NItemProt
