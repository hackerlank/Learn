/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    PropInfo.cpp
//  Purpose:      属性相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "PropInfo.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NPropInfo
{

#ifdef PROT_USE_XML

const char* EnumValToStr(EPropClass e)
{
	switch(e)
	{
	case eClassRole:
		return "eClassRole";
	case eClassFighter:
		return "eClassFighter";
	case eClassEquip:
		return "eClassEquip";
	case eClassORole:
		return "eClassORole";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EPropClass& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EPropClass> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eClassRole", eClassRole));
		mapStr2Val.insert(make_pair("eClassFighter", eClassFighter));
		mapStr2Val.insert(make_pair("eClassEquip", eClassEquip));
		mapStr2Val.insert(make_pair("eClassORole", eClassORole));
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

const char* EnumValToStr(EPropType e)
{
	switch(e)
	{
	case ePropNone:
		return "ePropNone";
	case ePropGold:
		return "ePropGold";
	case ePropSilver:
		return "ePropSilver";
	case ePropCoupon:
		return "ePropCoupon";
	case eProppGiftCoin:
		return "eProppGiftCoin";
	case ePropExpTemp:
		return "ePropExpTemp";
	case ePropPrestige:
		return "ePropPrestige";
	case ePropSoul:
		return "ePropSoul";
	case ePropHonor:
		return "ePropHonor";
	case ePropPExp:
		return "ePropPExp";
	case ePropSigil:
		return "ePropSigil";
	case ePropCentsY:
		return "ePropCentsY";
	case ePropAction:
		return "ePropAction";
	case ePropSop:
		return "ePropSop";
	case ePropTaoism:
		return "ePropTaoism";
	case ePropPoten:
		return "ePropPoten";
	case ePropReiki:
		return "ePropReiki";
	case ePropHFP:
		return "ePropHFP";
	case ePropDemonSoul:
		return "ePropDemonSoul";
	case ePropSoulAttack:
		return "ePropSoulAttack";
	case ePropSoulHp:
		return "ePropSoulHp";
	case ePropSoulCritical:
		return "ePropSoulCritical";
	case ePropSoulCounter:
		return "ePropSoulCounter";
	case ePropSoulSpeed:
		return "ePropSoulSpeed";
	case ePropSoulDefence:
		return "ePropSoulDefence";
	case ePropSoulHit:
		return "ePropSoulHit";
	case ePropSoulDodge:
		return "ePropSoulDodge";
	case ePropAchievementAP:
		return "ePropAchievementAP";
	case ePropCollectAP:
		return "ePropCollectAP";
	case ePropGuildContrib:
		return "ePropGuildContrib";
	case ePropStampHuang:
		return "ePropStampHuang";
	case ePropStampXuan:
		return "ePropStampXuan";
	case ePropStampDi:
		return "ePropStampDi";
	case ePropStampTian:
		return "ePropStampTian";
	case ePropStampXing:
		return "ePropStampXing";
	case ePropStampYue:
		return "ePropStampYue";
	case ePropStampDi2:
		return "ePropStampDi2";
	case ePropStampXian:
		return "ePropStampXian";
	case ePropStampSheng:
		return "ePropStampSheng";
	case ePropStampFo:
		return "ePropStampFo";
	case ePropLoveHeart:
		return "ePropLoveHeart";
	case ePropBlueFairyFate:
		return "ePropBlueFairyFate";
	case ePropPurpleFairyFate:
		return "ePropPurpleFairyFate";
	case ePropOrangeFairyFate:
		return "ePropOrangeFairyFate";
	case ePropDuJieFu:
		return "ePropDuJieFu";
	case ePropLuckyCoupon:
		return "ePropLuckyCoupon";
	case ePropMoneyEnd:
		return "ePropMoneyEnd";
	case ePropCommon:
		return "ePropCommon";
	case ePropTotalRecharge:
		return "ePropTotalRecharge";
	case ePropBTPoint:
		return "ePropBTPoint";
	case ePropHero:
		return "ePropHero";
	case ePropPos:
		return "ePropPos";
	case ePropTroopPos:
		return "ePropTroopPos";
	case ePropPotential:
		return "ePropPotential";
	case ePropCapacity:
		return "ePropCapacity";
	case ePropLevel:
		return "ePropLevel";
	case ePropLucky:
		return "ePropLucky";
	case ePropExp:
		return "ePropExp";
	case ePropLianPi:
		return "ePropLianPi";
	case ePropTongJin:
		return "ePropTongJin";
	case ePropQiangJi:
		return "ePropQiangJi";
	case ePropDuanGu:
		return "ePropDuanGu";
	case ePropMax:
		return "ePropMax";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EPropType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EPropType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("ePropNone", ePropNone));
		mapStr2Val.insert(make_pair("ePropGold", ePropGold));
		mapStr2Val.insert(make_pair("ePropSilver", ePropSilver));
		mapStr2Val.insert(make_pair("ePropCoupon", ePropCoupon));
		mapStr2Val.insert(make_pair("eProppGiftCoin", eProppGiftCoin));
		mapStr2Val.insert(make_pair("ePropExpTemp", ePropExpTemp));
		mapStr2Val.insert(make_pair("ePropPrestige", ePropPrestige));
		mapStr2Val.insert(make_pair("ePropSoul", ePropSoul));
		mapStr2Val.insert(make_pair("ePropHonor", ePropHonor));
		mapStr2Val.insert(make_pair("ePropPExp", ePropPExp));
		mapStr2Val.insert(make_pair("ePropSigil", ePropSigil));
		mapStr2Val.insert(make_pair("ePropCentsY", ePropCentsY));
		mapStr2Val.insert(make_pair("ePropAction", ePropAction));
		mapStr2Val.insert(make_pair("ePropSop", ePropSop));
		mapStr2Val.insert(make_pair("ePropTaoism", ePropTaoism));
		mapStr2Val.insert(make_pair("ePropPoten", ePropPoten));
		mapStr2Val.insert(make_pair("ePropReiki", ePropReiki));
		mapStr2Val.insert(make_pair("ePropHFP", ePropHFP));
		mapStr2Val.insert(make_pair("ePropDemonSoul", ePropDemonSoul));
		mapStr2Val.insert(make_pair("ePropSoulAttack", ePropSoulAttack));
		mapStr2Val.insert(make_pair("ePropSoulHp", ePropSoulHp));
		mapStr2Val.insert(make_pair("ePropSoulCritical", ePropSoulCritical));
		mapStr2Val.insert(make_pair("ePropSoulCounter", ePropSoulCounter));
		mapStr2Val.insert(make_pair("ePropSoulSpeed", ePropSoulSpeed));
		mapStr2Val.insert(make_pair("ePropSoulDefence", ePropSoulDefence));
		mapStr2Val.insert(make_pair("ePropSoulHit", ePropSoulHit));
		mapStr2Val.insert(make_pair("ePropSoulDodge", ePropSoulDodge));
		mapStr2Val.insert(make_pair("ePropAchievementAP", ePropAchievementAP));
		mapStr2Val.insert(make_pair("ePropCollectAP", ePropCollectAP));
		mapStr2Val.insert(make_pair("ePropGuildContrib", ePropGuildContrib));
		mapStr2Val.insert(make_pair("ePropStampHuang", ePropStampHuang));
		mapStr2Val.insert(make_pair("ePropStampXuan", ePropStampXuan));
		mapStr2Val.insert(make_pair("ePropStampDi", ePropStampDi));
		mapStr2Val.insert(make_pair("ePropStampTian", ePropStampTian));
		mapStr2Val.insert(make_pair("ePropStampXing", ePropStampXing));
		mapStr2Val.insert(make_pair("ePropStampYue", ePropStampYue));
		mapStr2Val.insert(make_pair("ePropStampDi2", ePropStampDi2));
		mapStr2Val.insert(make_pair("ePropStampXian", ePropStampXian));
		mapStr2Val.insert(make_pair("ePropStampSheng", ePropStampSheng));
		mapStr2Val.insert(make_pair("ePropStampFo", ePropStampFo));
		mapStr2Val.insert(make_pair("ePropLoveHeart", ePropLoveHeart));
		mapStr2Val.insert(make_pair("ePropBlueFairyFate", ePropBlueFairyFate));
		mapStr2Val.insert(make_pair("ePropPurpleFairyFate", ePropPurpleFairyFate));
		mapStr2Val.insert(make_pair("ePropOrangeFairyFate", ePropOrangeFairyFate));
		mapStr2Val.insert(make_pair("ePropDuJieFu", ePropDuJieFu));
		mapStr2Val.insert(make_pair("ePropLuckyCoupon", ePropLuckyCoupon));
		mapStr2Val.insert(make_pair("ePropMoneyEnd", ePropMoneyEnd));
		mapStr2Val.insert(make_pair("ePropCommon", ePropCommon));
		mapStr2Val.insert(make_pair("ePropTotalRecharge", ePropTotalRecharge));
		mapStr2Val.insert(make_pair("ePropBTPoint", ePropBTPoint));
		mapStr2Val.insert(make_pair("ePropHero", ePropHero));
		mapStr2Val.insert(make_pair("ePropPos", ePropPos));
		mapStr2Val.insert(make_pair("ePropTroopPos", ePropTroopPos));
		mapStr2Val.insert(make_pair("ePropPotential", ePropPotential));
		mapStr2Val.insert(make_pair("ePropCapacity", ePropCapacity));
		mapStr2Val.insert(make_pair("ePropLevel", ePropLevel));
		mapStr2Val.insert(make_pair("ePropLucky", ePropLucky));
		mapStr2Val.insert(make_pair("ePropExp", ePropExp));
		mapStr2Val.insert(make_pair("ePropLianPi", ePropLianPi));
		mapStr2Val.insert(make_pair("ePropTongJin", ePropTongJin));
		mapStr2Val.insert(make_pair("ePropQiangJi", ePropQiangJi));
		mapStr2Val.insert(make_pair("ePropDuanGu", ePropDuanGu));
		mapStr2Val.insert(make_pair("ePropMax", ePropMax));
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

const char* EnumValToStr(EPropResult e)
{
	switch(e)
	{
	case ePropSucceed:
		return "ePropSucceed";
	case ePropGoldErr:
		return "ePropGoldErr";
	case ePropSilverErr:
		return "ePropSilverErr";
	case ePropCouponErr:
		return "ePropCouponErr";
	case ePropOtherErr:
		return "ePropOtherErr";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EPropResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EPropResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("ePropSucceed", ePropSucceed));
		mapStr2Val.insert(make_pair("ePropGoldErr", ePropGoldErr));
		mapStr2Val.insert(make_pair("ePropSilverErr", ePropSilverErr));
		mapStr2Val.insert(make_pair("ePropCouponErr", ePropCouponErr));
		mapStr2Val.insert(make_pair("ePropOtherErr", ePropOtherErr));
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

const char* EnumValToStr(EExchangeResult e)
{
	switch(e)
	{
	case eExchangeResultSuccess:
		return "eExchangeResultSuccess";
	case eExchangeResultFailed:
		return "eExchangeResultFailed";
	case eExchangeResultLack:
		return "eExchangeResultLack";
	case eExchangeResultLimit:
		return "eExchangeResultLimit";
	case eExchangeResultMax:
		return "eExchangeResultMax";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EExchangeResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EExchangeResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eExchangeResultSuccess", eExchangeResultSuccess));
		mapStr2Val.insert(make_pair("eExchangeResultFailed", eExchangeResultFailed));
		mapStr2Val.insert(make_pair("eExchangeResultLack", eExchangeResultLack));
		mapStr2Val.insert(make_pair("eExchangeResultLimit", eExchangeResultLimit));
		mapStr2Val.insert(make_pair("eExchangeResultMax", eExchangeResultMax));
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

SPropValue::SPropValue() : ePropType((EPropType)0), value(0) { }

SPropValue::SPropValue(EPropType ePropType_, UINT32 value_) : ePropType(ePropType_), value(value_) { }

CInArchive& operator>>(CInArchive& src, SPropValue& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (UINT16&)s.ePropType;
	src >> s.value;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SPropValue& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (UINT16&)s.ePropType;
	src << s.value;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SPropValue& s)
{
	if(strcmp(rElement.Value(), "SPropValue") != 0)
	{
		LOG_CRI << "rElement is not SPropValue!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for ePropType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "EPropType") != 0)
	{
		LOG_CRI << "pElemChild is not EPropType!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "ePropType") != 0)
	{
		LOG_CRI << "Attribute: name is not ePropType!";
		return false;
	}
	const char* pszVal_ePropType = pElemChild->Attribute("value");
	if(pszVal_ePropType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!EnumStrToVal(pszVal_ePropType, s.ePropType))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for value is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "value") != 0)
	{
		LOG_CRI << "Attribute: name is not value!";
		return false;
	}
	const char* pszVal_value = pElemChild->Attribute("value");
	if(pszVal_value == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_value, s.value))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SPropValue& s, TiXmlElement& rElement)
{
	rElement.SetValue("SPropValue");
	rElement.SetAttribute("type", ToUTF8Ptr("属性信息"));
	unique_ptr<TiXmlElement> pElem_ePropType(new TiXmlElement("EPropType"));
	if(pElem_ePropType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_ePropType->SetAttribute("name", "ePropType");
	const char* pszEnum_ePropType = EnumValToStr(s.ePropType);
	if(pszEnum_ePropType == NULL)
	{
		LOG_CRI << "EnumValToStr for EPropType fails!";
		return false;
	}
	pElem_ePropType->SetAttribute("value", pszEnum_ePropType);
	pElem_ePropType->SetAttribute("comment", ToUTF8Ptr("属性类型"));
	if(rElement.LinkEndChild(pElem_ePropType.get()) != NULL)
		pElem_ePropType.release();
	unique_ptr<TiXmlElement> pElem_value(new TiXmlElement("UINT32"));
	if(pElem_value == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_value->SetAttribute("name", "value");
	pElem_value->SetAttribute("value", NumberToString(s.value).c_str());
	pElem_value->SetAttribute("comment", ToUTF8Ptr("属性值，需要根据类型来转换"));
	if(rElement.LinkEndChild(pElem_value.get()) != NULL)
		pElem_value.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecPropValue& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SPropValue s;
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

bool VectorToXML(const TVecPropValue& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SPropValue"));
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

SPropQWValue::SPropQWValue() : ePropType((EPropType)0), value(0) { }

SPropQWValue::SPropQWValue(EPropType ePropType_, UINT64 value_) : ePropType(ePropType_), value(value_) { }

CInArchive& operator>>(CInArchive& src, SPropQWValue& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (UINT16&)s.ePropType;
	src >> s.value;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SPropQWValue& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (UINT16&)s.ePropType;
	src << s.value;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SPropQWValue& s)
{
	if(strcmp(rElement.Value(), "SPropQWValue") != 0)
	{
		LOG_CRI << "rElement is not SPropQWValue!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for ePropType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "EPropType") != 0)
	{
		LOG_CRI << "pElemChild is not EPropType!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "ePropType") != 0)
	{
		LOG_CRI << "Attribute: name is not ePropType!";
		return false;
	}
	const char* pszVal_ePropType = pElemChild->Attribute("value");
	if(pszVal_ePropType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!EnumStrToVal(pszVal_ePropType, s.ePropType))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for value is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "value") != 0)
	{
		LOG_CRI << "Attribute: name is not value!";
		return false;
	}
	const char* pszVal_value = pElemChild->Attribute("value");
	if(pszVal_value == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_value, s.value))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SPropQWValue& s, TiXmlElement& rElement)
{
	rElement.SetValue("SPropQWValue");
	rElement.SetAttribute("type", ToUTF8Ptr("属性信息"));
	unique_ptr<TiXmlElement> pElem_ePropType(new TiXmlElement("EPropType"));
	if(pElem_ePropType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_ePropType->SetAttribute("name", "ePropType");
	const char* pszEnum_ePropType = EnumValToStr(s.ePropType);
	if(pszEnum_ePropType == NULL)
	{
		LOG_CRI << "EnumValToStr for EPropType fails!";
		return false;
	}
	pElem_ePropType->SetAttribute("value", pszEnum_ePropType);
	pElem_ePropType->SetAttribute("comment", ToUTF8Ptr("属性类型"));
	if(rElement.LinkEndChild(pElem_ePropType.get()) != NULL)
		pElem_ePropType.release();
	unique_ptr<TiXmlElement> pElem_value(new TiXmlElement("UINT64"));
	if(pElem_value == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_value->SetAttribute("name", "value");
	pElem_value->SetAttribute("value", NumberToString(s.value).c_str());
	pElem_value->SetAttribute("comment", ToUTF8Ptr("属性值，需要根据类型来转换"));
	if(rElement.LinkEndChild(pElem_value.get()) != NULL)
		pElem_value.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecPropQWValue& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SPropQWValue s;
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

bool VectorToXML(const TVecPropQWValue& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SPropQWValue"));
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

SPropValExt::SPropValExt() : ePropType((EPropType)0), value(0), ext(0) { }

SPropValExt::SPropValExt(EPropType ePropType_, float value_, INT32 ext_) : ePropType(ePropType_), value(value_), ext(ext_) { }

CInArchive& operator>>(CInArchive& src, SPropValExt& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (UINT16&)s.ePropType;
	src >> s.value;
	src >> s.ext;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SPropValExt& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (UINT16&)s.ePropType;
	src << s.value;
	src << s.ext;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SPropValExt& s)
{
	if(strcmp(rElement.Value(), "SPropValExt") != 0)
	{
		LOG_CRI << "rElement is not SPropValExt!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for ePropType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "EPropType") != 0)
	{
		LOG_CRI << "pElemChild is not EPropType!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "ePropType") != 0)
	{
		LOG_CRI << "Attribute: name is not ePropType!";
		return false;
	}
	const char* pszVal_ePropType = pElemChild->Attribute("value");
	if(pszVal_ePropType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!EnumStrToVal(pszVal_ePropType, s.ePropType))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for value is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "float") != 0)
	{
		LOG_CRI << "pElemChild is not float!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "value") != 0)
	{
		LOG_CRI << "Attribute: name is not value!";
		return false;
	}
	const char* pszVal_value = pElemChild->Attribute("value");
	if(pszVal_value == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_value, s.value))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for ext is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "INT32") != 0)
	{
		LOG_CRI << "pElemChild is not INT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "ext") != 0)
	{
		LOG_CRI << "Attribute: name is not ext!";
		return false;
	}
	const char* pszVal_ext = pElemChild->Attribute("value");
	if(pszVal_ext == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_ext, s.ext))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SPropValExt& s, TiXmlElement& rElement)
{
	rElement.SetValue("SPropValExt");
	rElement.SetAttribute("type", ToUTF8Ptr("扩展属性信息"));
	unique_ptr<TiXmlElement> pElem_ePropType(new TiXmlElement("EPropType"));
	if(pElem_ePropType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_ePropType->SetAttribute("name", "ePropType");
	const char* pszEnum_ePropType = EnumValToStr(s.ePropType);
	if(pszEnum_ePropType == NULL)
	{
		LOG_CRI << "EnumValToStr for EPropType fails!";
		return false;
	}
	pElem_ePropType->SetAttribute("value", pszEnum_ePropType);
	pElem_ePropType->SetAttribute("comment", ToUTF8Ptr("属性类型"));
	if(rElement.LinkEndChild(pElem_ePropType.get()) != NULL)
		pElem_ePropType.release();
	unique_ptr<TiXmlElement> pElem_value(new TiXmlElement("float"));
	if(pElem_value == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_value->SetAttribute("name", "value");
	pElem_value->SetAttribute("value", NumberToString(s.value).c_str());
	pElem_value->SetAttribute("comment", ToUTF8Ptr("属性值，需要根据类型来转换"));
	if(rElement.LinkEndChild(pElem_value.get()) != NULL)
		pElem_value.release();
	unique_ptr<TiXmlElement> pElem_ext(new TiXmlElement("INT32"));
	if(pElem_ext == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_ext->SetAttribute("name", "ext");
	pElem_ext->SetAttribute("value", NumberToString(s.ext).c_str());
	pElem_ext->SetAttribute("comment", ToUTF8Ptr("扩展值，不同用途作不同的解释"));
	if(rElement.LinkEndChild(pElem_ext.get()) != NULL)
		pElem_ext.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecPropValExt& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SPropValExt s;
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

bool VectorToXML(const TVecPropValExt& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SPropValExt"));
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

SPropQWValExt::SPropQWValExt() : ePropType((EPropType)0), value(0), ext(0) { }

SPropQWValExt::SPropQWValExt(EPropType ePropType_, UINT64 value_, INT32 ext_) : ePropType(ePropType_), value(value_), ext(ext_) { }

CInArchive& operator>>(CInArchive& src, SPropQWValExt& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (UINT16&)s.ePropType;
	src >> s.value;
	src >> s.ext;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SPropQWValExt& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (UINT16&)s.ePropType;
	src << s.value;
	src << s.ext;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SPropQWValExt& s)
{
	if(strcmp(rElement.Value(), "SPropQWValExt") != 0)
	{
		LOG_CRI << "rElement is not SPropQWValExt!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for ePropType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "EPropType") != 0)
	{
		LOG_CRI << "pElemChild is not EPropType!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "ePropType") != 0)
	{
		LOG_CRI << "Attribute: name is not ePropType!";
		return false;
	}
	const char* pszVal_ePropType = pElemChild->Attribute("value");
	if(pszVal_ePropType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!EnumStrToVal(pszVal_ePropType, s.ePropType))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for value is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "value") != 0)
	{
		LOG_CRI << "Attribute: name is not value!";
		return false;
	}
	const char* pszVal_value = pElemChild->Attribute("value");
	if(pszVal_value == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_value, s.value))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for ext is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "INT32") != 0)
	{
		LOG_CRI << "pElemChild is not INT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "ext") != 0)
	{
		LOG_CRI << "Attribute: name is not ext!";
		return false;
	}
	const char* pszVal_ext = pElemChild->Attribute("value");
	if(pszVal_ext == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_ext, s.ext))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SPropQWValExt& s, TiXmlElement& rElement)
{
	rElement.SetValue("SPropQWValExt");
	rElement.SetAttribute("type", ToUTF8Ptr("扩展属性信息"));
	unique_ptr<TiXmlElement> pElem_ePropType(new TiXmlElement("EPropType"));
	if(pElem_ePropType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_ePropType->SetAttribute("name", "ePropType");
	const char* pszEnum_ePropType = EnumValToStr(s.ePropType);
	if(pszEnum_ePropType == NULL)
	{
		LOG_CRI << "EnumValToStr for EPropType fails!";
		return false;
	}
	pElem_ePropType->SetAttribute("value", pszEnum_ePropType);
	pElem_ePropType->SetAttribute("comment", ToUTF8Ptr("属性类型"));
	if(rElement.LinkEndChild(pElem_ePropType.get()) != NULL)
		pElem_ePropType.release();
	unique_ptr<TiXmlElement> pElem_value(new TiXmlElement("UINT64"));
	if(pElem_value == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_value->SetAttribute("name", "value");
	pElem_value->SetAttribute("value", NumberToString(s.value).c_str());
	pElem_value->SetAttribute("comment", ToUTF8Ptr("属性值，需要根据类型来转换"));
	if(rElement.LinkEndChild(pElem_value.get()) != NULL)
		pElem_value.release();
	unique_ptr<TiXmlElement> pElem_ext(new TiXmlElement("INT32"));
	if(pElem_ext == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_ext->SetAttribute("name", "ext");
	pElem_ext->SetAttribute("value", NumberToString(s.ext).c_str());
	pElem_ext->SetAttribute("comment", ToUTF8Ptr("扩展值，不同用途作不同的解释"));
	if(rElement.LinkEndChild(pElem_ext.get()) != NULL)
		pElem_ext.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecPropQWValExt& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SPropQWValExt s;
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

bool VectorToXML(const TVecPropQWValExt& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SPropQWValExt"));
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

} //namespace NPropInfo
