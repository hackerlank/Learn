/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    WonderActivityProt.cpp
//  Purpose:      精彩活动
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "WonderActivityProt.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NWonderActivityProt
{

#ifdef PROT_USE_XML

const char* EnumValToStr(EWActResult e)
{
	switch(e)
	{
	case eWActResult_none:
		return "eWActResult_none";
	case eWActResult_success:
		return "eWActResult_success";
	case eWActResult_error:
		return "eWActResult_error";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EWActResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EWActResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eWActResult_none", eWActResult_none));
		mapStr2Val.insert(make_pair("eWActResult_success", eWActResult_success));
		mapStr2Val.insert(make_pair("eWActResult_error", eWActResult_error));
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

const char* EnumValToStr(EGainResult e)
{
	switch(e)
	{
	case eGainResult_none:
		return "eGainResult_none";
	case eGainResult_success:
		return "eGainResult_success";
	case eGainResult_alreadyGain:
		return "eGainResult_alreadyGain";
	case eGainResult_fullBag:
		return "eGainResult_fullBag";
	case eGainResult_notGet:
		return "eGainResult_notGet";
	case eGainResult_error:
		return "eGainResult_error";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EGainResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EGainResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eGainResult_none", eGainResult_none));
		mapStr2Val.insert(make_pair("eGainResult_success", eGainResult_success));
		mapStr2Val.insert(make_pair("eGainResult_alreadyGain", eGainResult_alreadyGain));
		mapStr2Val.insert(make_pair("eGainResult_fullBag", eGainResult_fullBag));
		mapStr2Val.insert(make_pair("eGainResult_notGet", eGainResult_notGet));
		mapStr2Val.insert(make_pair("eGainResult_error", eGainResult_error));
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

const char* EnumValToStr(EWActType e)
{
	switch(e)
	{
	case eWActType_NONE:
		return "eWActType_NONE";
	case eWActType_RANKPOINT:
		return "eWActType_RANKPOINT";
	case eWActType_LEVELACT:
		return "eWActType_LEVELACT";
	case eWActType_HORSEACT:
		return "eWActType_HORSEACT";
	case eWActType_DUNGON:
		return "eWActType_DUNGON";
	case eWActType_FIGHTER:
		return "eWActType_FIGHTER";
	case eWActType_FORMATION:
		return "eWActType_FORMATION";
	case eWActType_TRUMP:
		return "eWActType_TRUMP";
	case eWActType_RANKLEVEL:
		return "eWActType_RANKLEVEL";
	case eWActType_RANKPET:
		return "eWActType_RANKPET";
	case eWActType_RANKFIGHTER:
		return "eWActType_RANKFIGHTER";
	case eWActType_RANKARENA:
		return "eWActType_RANKARENA";
	case eWActType_RANKGUILD:
		return "eWActType_RANKGUILD";
	case eWActType_RANKTRUMP:
		return "eWActType_RANKTRUMP";
	case eWActType_QQCOIN:
		return "eWActType_QQCOIN";
	case eWActType_BEAUTYACT:
		return "eWActType_BEAUTYACT";
	case eWActType_POINT:
		return "eWActType_POINT";
	case eWActType_OpenBuy:
		return "eWActType_OpenBuy";
	case eWActType_MAX:
		return "eWActType_MAX";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EWActType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EWActType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eWActType_NONE", eWActType_NONE));
		mapStr2Val.insert(make_pair("eWActType_RANKPOINT", eWActType_RANKPOINT));
		mapStr2Val.insert(make_pair("eWActType_LEVELACT", eWActType_LEVELACT));
		mapStr2Val.insert(make_pair("eWActType_HORSEACT", eWActType_HORSEACT));
		mapStr2Val.insert(make_pair("eWActType_DUNGON", eWActType_DUNGON));
		mapStr2Val.insert(make_pair("eWActType_FIGHTER", eWActType_FIGHTER));
		mapStr2Val.insert(make_pair("eWActType_FORMATION", eWActType_FORMATION));
		mapStr2Val.insert(make_pair("eWActType_TRUMP", eWActType_TRUMP));
		mapStr2Val.insert(make_pair("eWActType_RANKLEVEL", eWActType_RANKLEVEL));
		mapStr2Val.insert(make_pair("eWActType_RANKPET", eWActType_RANKPET));
		mapStr2Val.insert(make_pair("eWActType_RANKFIGHTER", eWActType_RANKFIGHTER));
		mapStr2Val.insert(make_pair("eWActType_RANKARENA", eWActType_RANKARENA));
		mapStr2Val.insert(make_pair("eWActType_RANKGUILD", eWActType_RANKGUILD));
		mapStr2Val.insert(make_pair("eWActType_RANKTRUMP", eWActType_RANKTRUMP));
		mapStr2Val.insert(make_pair("eWActType_QQCOIN", eWActType_QQCOIN));
		mapStr2Val.insert(make_pair("eWActType_BEAUTYACT", eWActType_BEAUTYACT));
		mapStr2Val.insert(make_pair("eWActType_POINT", eWActType_POINT));
		mapStr2Val.insert(make_pair("eWActType_OpenBuy", eWActType_OpenBuy));
		mapStr2Val.insert(make_pair("eWActType_MAX", eWActType_MAX));
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

const char* EnumValToStr(EWActState e)
{
	switch(e)
	{
	case eWActState_Init:
		return "eWActState_Init";
	case eWActState_Advance:
		return "eWActState_Advance";
	case eWActState_Begin:
		return "eWActState_Begin";
	case eWActState_End:
		return "eWActState_End";
	case eWActState_Retain:
		return "eWActState_Retain";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EWActState& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EWActState> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eWActState_Init", eWActState_Init));
		mapStr2Val.insert(make_pair("eWActState_Advance", eWActState_Advance));
		mapStr2Val.insert(make_pair("eWActState_Begin", eWActState_Begin));
		mapStr2Val.insert(make_pair("eWActState_End", eWActState_End));
		mapStr2Val.insert(make_pair("eWActState_Retain", eWActState_Retain));
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

const char* EnumValToStr(EWActPrizeType e)
{
	switch(e)
	{
	case eWActPrizeType_default:
		return "eWActPrizeType_default";
	case eWActPrizeType_first:
		return "eWActPrizeType_first";
	case eWActPrizeType_one:
		return "eWActPrizeType_one";
	case eWActPrizeType_two:
		return "eWActPrizeType_two";
	case eWActPrizeType_three:
		return "eWActPrizeType_three";
	case eWActPrizeType_MAX:
		return "eWActPrizeType_MAX";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EWActPrizeType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EWActPrizeType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eWActPrizeType_default", eWActPrizeType_default));
		mapStr2Val.insert(make_pair("eWActPrizeType_first", eWActPrizeType_first));
		mapStr2Val.insert(make_pair("eWActPrizeType_one", eWActPrizeType_one));
		mapStr2Val.insert(make_pair("eWActPrizeType_two", eWActPrizeType_two));
		mapStr2Val.insert(make_pair("eWActPrizeType_three", eWActPrizeType_three));
		mapStr2Val.insert(make_pair("eWActPrizeType_MAX", eWActPrizeType_MAX));
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

SItemConfig::SItemConfig() : dwItemID(0), dwCount(0) { }

SItemConfig::SItemConfig(UINT32 dwItemID_, UINT32 dwCount_) : dwItemID(dwItemID_), dwCount(dwCount_) { }

CInArchive& operator>>(CInArchive& src, SItemConfig& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.dwItemID;
	src >> s.dwCount;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SItemConfig& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.dwItemID;
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

bool FromXML(TiXmlElement& rElement, SItemConfig& s)
{
	if(strcmp(rElement.Value(), "SItemConfig") != 0)
	{
		LOG_CRI << "rElement is not SItemConfig!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwItemID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwItemID") != 0)
	{
		LOG_CRI << "Attribute: name is not dwItemID!";
		return false;
	}
	const char* pszVal_dwItemID = pElemChild->Attribute("value");
	if(pszVal_dwItemID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwItemID, s.dwItemID))
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

bool ToXML(const SItemConfig& s, TiXmlElement& rElement)
{
	rElement.SetValue("SItemConfig");
	rElement.SetAttribute("type", ToUTF8Ptr("奖励道具信息"));
	unique_ptr<TiXmlElement> pElem_dwItemID(new TiXmlElement("UINT32"));
	if(pElem_dwItemID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwItemID->SetAttribute("name", "dwItemID");
	pElem_dwItemID->SetAttribute("value", NumberToString(s.dwItemID).c_str());
	pElem_dwItemID->SetAttribute("comment", ToUTF8Ptr("道具ID"));
	if(rElement.LinkEndChild(pElem_dwItemID.get()) != NULL)
		pElem_dwItemID.release();
	unique_ptr<TiXmlElement> pElem_dwCount(new TiXmlElement("UINT32"));
	if(pElem_dwCount == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwCount->SetAttribute("name", "dwCount");
	pElem_dwCount->SetAttribute("value", NumberToString(s.dwCount).c_str());
	pElem_dwCount->SetAttribute("comment", ToUTF8Ptr("道具数量"));
	if(rElement.LinkEndChild(pElem_dwCount.get()) != NULL)
		pElem_dwCount.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecItemConfig& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SItemConfig s;
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

bool VectorToXML(const TVecItemConfig& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SItemConfig"));
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

SPrizeConfig::SPrizeConfig() : ePrizeType((EWActPrizeType)0) { }

SPrizeConfig::SPrizeConfig(EWActPrizeType ePrizeType_, const TVecItemConfig& vecItems_) : ePrizeType(ePrizeType_), vecItems(vecItems_) { }

SPrizeConfig::SPrizeConfig(SPrizeConfig&& src) : ePrizeType(src.ePrizeType), vecItems(move(src.vecItems)) { }

SPrizeConfig& SPrizeConfig::operator=(SPrizeConfig&& rhs)
{
	if(this != &rhs)
	{
		this->~SPrizeConfig();
		new (this) SPrizeConfig(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SPrizeConfig& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (UINT8&)s.ePrizeType;
	src >> s.vecItems;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SPrizeConfig& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (UINT8&)s.ePrizeType;
	src << s.vecItems;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SPrizeConfig& s)
{
	if(strcmp(rElement.Value(), "SPrizeConfig") != 0)
	{
		LOG_CRI << "rElement is not SPrizeConfig!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for ePrizeType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "EWActPrizeType") != 0)
	{
		LOG_CRI << "pElemChild is not EWActPrizeType!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "ePrizeType") != 0)
	{
		LOG_CRI << "Attribute: name is not ePrizeType!";
		return false;
	}
	const char* pszVal_ePrizeType = pElemChild->Attribute("value");
	if(pszVal_ePrizeType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!EnumStrToVal(pszVal_ePrizeType, s.ePrizeType))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecItems is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecItemConfig") != 0)
	{
		LOG_CRI << "pElemChild is not TVecItemConfig!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecItems") != 0)
	{
		LOG_CRI << "Attribute: name is not vecItems!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecItems))
	{
		LOG_CRI << "VectorFromXML for vecItems fails!";
		return false;
	}
	return true;
}

bool ToXML(const SPrizeConfig& s, TiXmlElement& rElement)
{
	rElement.SetValue("SPrizeConfig");
	rElement.SetAttribute("type", ToUTF8Ptr("奖励道具信息"));
	unique_ptr<TiXmlElement> pElem_ePrizeType(new TiXmlElement("EWActPrizeType"));
	if(pElem_ePrizeType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_ePrizeType->SetAttribute("name", "ePrizeType");
	const char* pszEnum_ePrizeType = EnumValToStr(s.ePrizeType);
	if(pszEnum_ePrizeType == NULL)
	{
		LOG_CRI << "EnumValToStr for EWActPrizeType fails!";
		return false;
	}
	pElem_ePrizeType->SetAttribute("value", pszEnum_ePrizeType);
	pElem_ePrizeType->SetAttribute("comment", ToUTF8Ptr("奖励类型"));
	if(rElement.LinkEndChild(pElem_ePrizeType.get()) != NULL)
		pElem_ePrizeType.release();
	unique_ptr<TiXmlElement> pElem_vecItems(new TiXmlElement("TVecItemConfig"));
	if(pElem_vecItems == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecItems->SetAttribute("name", "vecItems");
	if(!VectorToXML(s.vecItems, *pElem_vecItems))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecItems->SetAttribute("comment", ToUTF8Ptr("道具"));
	if(rElement.LinkEndChild(pElem_vecItems.get()) != NULL)
		pElem_vecItems.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecPrizeConfig& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SPrizeConfig s;
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

bool VectorToXML(const TVecPrizeConfig& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SPrizeConfig"));
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

SWActConfig::SWActConfig() : wWActID(0), wCfgID(0), eWactPrizeType((EWActPrizeType)0) { }

SWActConfig::SWActConfig(UINT16 wWActID_, UINT16 wCfgID_, EWActPrizeType eWactPrizeType_, const TVecItemConfig& vecItemConfig_) : wWActID(wWActID_), wCfgID(wCfgID_), eWactPrizeType(eWactPrizeType_), vecItemConfig(vecItemConfig_) { }

SWActConfig::SWActConfig(SWActConfig&& src) : wWActID(src.wWActID), wCfgID(src.wCfgID), eWactPrizeType(src.eWactPrizeType), vecItemConfig(move(src.vecItemConfig)) { }

SWActConfig& SWActConfig::operator=(SWActConfig&& rhs)
{
	if(this != &rhs)
	{
		this->~SWActConfig();
		new (this) SWActConfig(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SWActConfig& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.wWActID;
	src >> s.wCfgID;
	src >> (UINT8&)s.eWactPrizeType;
	src >> s.vecItemConfig;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SWActConfig& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.wWActID;
	src << s.wCfgID;
	src << (UINT8&)s.eWactPrizeType;
	src << s.vecItemConfig;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SWActConfig& s)
{
	if(strcmp(rElement.Value(), "SWActConfig") != 0)
	{
		LOG_CRI << "rElement is not SWActConfig!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wWActID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wWActID") != 0)
	{
		LOG_CRI << "Attribute: name is not wWActID!";
		return false;
	}
	const char* pszVal_wWActID = pElemChild->Attribute("value");
	if(pszVal_wWActID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wWActID, s.wWActID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wCfgID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wCfgID") != 0)
	{
		LOG_CRI << "Attribute: name is not wCfgID!";
		return false;
	}
	const char* pszVal_wCfgID = pElemChild->Attribute("value");
	if(pszVal_wCfgID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wCfgID, s.wCfgID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eWactPrizeType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "EWActPrizeType") != 0)
	{
		LOG_CRI << "pElemChild is not EWActPrizeType!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eWactPrizeType") != 0)
	{
		LOG_CRI << "Attribute: name is not eWactPrizeType!";
		return false;
	}
	const char* pszVal_eWactPrizeType = pElemChild->Attribute("value");
	if(pszVal_eWactPrizeType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!EnumStrToVal(pszVal_eWactPrizeType, s.eWactPrizeType))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecItemConfig is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecItemConfig") != 0)
	{
		LOG_CRI << "pElemChild is not TVecItemConfig!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecItemConfig") != 0)
	{
		LOG_CRI << "Attribute: name is not vecItemConfig!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecItemConfig))
	{
		LOG_CRI << "VectorFromXML for vecItemConfig fails!";
		return false;
	}
	return true;
}

bool ToXML(const SWActConfig& s, TiXmlElement& rElement)
{
	rElement.SetValue("SWActConfig");
	rElement.SetAttribute("type", ToUTF8Ptr("活动具体配置信息"));
	unique_ptr<TiXmlElement> pElem_wWActID(new TiXmlElement("UINT16"));
	if(pElem_wWActID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wWActID->SetAttribute("name", "wWActID");
	pElem_wWActID->SetAttribute("value", NumberToString(s.wWActID).c_str());
	pElem_wWActID->SetAttribute("comment", ToUTF8Ptr("活动ID"));
	if(rElement.LinkEndChild(pElem_wWActID.get()) != NULL)
		pElem_wWActID.release();
	unique_ptr<TiXmlElement> pElem_wCfgID(new TiXmlElement("UINT16"));
	if(pElem_wCfgID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wCfgID->SetAttribute("name", "wCfgID");
	pElem_wCfgID->SetAttribute("value", NumberToString(s.wCfgID).c_str());
	pElem_wCfgID->SetAttribute("comment", ToUTF8Ptr("活动配置ID"));
	if(rElement.LinkEndChild(pElem_wCfgID.get()) != NULL)
		pElem_wCfgID.release();
	unique_ptr<TiXmlElement> pElem_eWactPrizeType(new TiXmlElement("EWActPrizeType"));
	if(pElem_eWactPrizeType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eWactPrizeType->SetAttribute("name", "eWactPrizeType");
	const char* pszEnum_eWactPrizeType = EnumValToStr(s.eWactPrizeType);
	if(pszEnum_eWactPrizeType == NULL)
	{
		LOG_CRI << "EnumValToStr for EWActPrizeType fails!";
		return false;
	}
	pElem_eWactPrizeType->SetAttribute("value", pszEnum_eWactPrizeType);
	pElem_eWactPrizeType->SetAttribute("comment", ToUTF8Ptr("奖励类型"));
	if(rElement.LinkEndChild(pElem_eWactPrizeType.get()) != NULL)
		pElem_eWactPrizeType.release();
	unique_ptr<TiXmlElement> pElem_vecItemConfig(new TiXmlElement("TVecItemConfig"));
	if(pElem_vecItemConfig == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecItemConfig->SetAttribute("name", "vecItemConfig");
	if(!VectorToXML(s.vecItemConfig, *pElem_vecItemConfig))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecItemConfig->SetAttribute("comment", ToUTF8Ptr("奖励道具列表"));
	if(rElement.LinkEndChild(pElem_vecItemConfig.get()) != NULL)
		pElem_vecItemConfig.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecWActConfig& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SWActConfig s;
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

bool VectorToXML(const TVecWActConfig& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SWActConfig"));
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

SWActPlayerInfo::SWActPlayerInfo() : wWActID(0), wID(0), qwPlayerID(0), eCareer((NProtoCommon::ECareerType)0), eSex((NProtoCommon::ESexType)0), 
			dwValue1(0), dwValue2(0) { }

SWActPlayerInfo::SWActPlayerInfo(UINT16 wWActID_, UINT16 wID_, UINT64 qwPlayerID_, const std::string& strName_, NProtoCommon::ECareerType eCareer_, 
			NProtoCommon::ESexType eSex_, const std::string& strName1_, UINT32 dwValue1_, UINT32 dwValue2_)
			: wWActID(wWActID_), wID(wID_), qwPlayerID(qwPlayerID_), strName(strName_), eCareer(eCareer_), 
			eSex(eSex_), strName1(strName1_), dwValue1(dwValue1_), dwValue2(dwValue2_) { }

SWActPlayerInfo::SWActPlayerInfo(SWActPlayerInfo&& src) : wWActID(src.wWActID), wID(src.wID), qwPlayerID(src.qwPlayerID), strName(move(src.strName)), eCareer(src.eCareer), 
			eSex(src.eSex), strName1(move(src.strName1)), dwValue1(src.dwValue1), dwValue2(src.dwValue2) { }

SWActPlayerInfo& SWActPlayerInfo::operator=(SWActPlayerInfo&& rhs)
{
	if(this != &rhs)
	{
		this->~SWActPlayerInfo();
		new (this) SWActPlayerInfo(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SWActPlayerInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.wWActID;
	src >> s.wID;
	src >> s.qwPlayerID;
	src >> s.strName;
	src >> (UINT8&)s.eCareer;
	src >> (UINT8&)s.eSex;
	src >> s.strName1;
	src >> s.dwValue1;
	src >> s.dwValue2;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SWActPlayerInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.wWActID;
	src << s.wID;
	src << s.qwPlayerID;
	src << s.strName;
	src << (UINT8&)s.eCareer;
	src << (UINT8&)s.eSex;
	src << s.strName1;
	src << s.dwValue1;
	src << s.dwValue2;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SWActPlayerInfo& s)
{
	if(strcmp(rElement.Value(), "SWActPlayerInfo") != 0)
	{
		LOG_CRI << "rElement is not SWActPlayerInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wWActID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wWActID") != 0)
	{
		LOG_CRI << "Attribute: name is not wWActID!";
		return false;
	}
	const char* pszVal_wWActID = pElemChild->Attribute("value");
	if(pszVal_wWActID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wWActID, s.wWActID))
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
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwPlayerID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwPlayerID") != 0)
	{
		LOG_CRI << "Attribute: name is not qwPlayerID!";
		return false;
	}
	const char* pszVal_qwPlayerID = pElemChild->Attribute("value");
	if(pszVal_qwPlayerID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwPlayerID, s.qwPlayerID))
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
		LOG_CRI << "pElemChild for strName1 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strName1") != 0)
	{
		LOG_CRI << "Attribute: name is not strName1!";
		return false;
	}
	const char* pszVal_strName1 = pElemChild->Attribute("value");
	if(pszVal_strName1 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strName1 = pszVal_strName1;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwValue1 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwValue1") != 0)
	{
		LOG_CRI << "Attribute: name is not dwValue1!";
		return false;
	}
	const char* pszVal_dwValue1 = pElemChild->Attribute("value");
	if(pszVal_dwValue1 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwValue1, s.dwValue1))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwValue2 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwValue2") != 0)
	{
		LOG_CRI << "Attribute: name is not dwValue2!";
		return false;
	}
	const char* pszVal_dwValue2 = pElemChild->Attribute("value");
	if(pszVal_dwValue2 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwValue2, s.dwValue2))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SWActPlayerInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SWActPlayerInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("人物信息"));
	unique_ptr<TiXmlElement> pElem_wWActID(new TiXmlElement("UINT16"));
	if(pElem_wWActID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wWActID->SetAttribute("name", "wWActID");
	pElem_wWActID->SetAttribute("value", NumberToString(s.wWActID).c_str());
	pElem_wWActID->SetAttribute("comment", ToUTF8Ptr("活动ID"));
	if(rElement.LinkEndChild(pElem_wWActID.get()) != NULL)
		pElem_wWActID.release();
	unique_ptr<TiXmlElement> pElem_wID(new TiXmlElement("UINT16"));
	if(pElem_wID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wID->SetAttribute("name", "wID");
	pElem_wID->SetAttribute("value", NumberToString(s.wID).c_str());
	pElem_wID->SetAttribute("comment", ToUTF8Ptr("散仙|阵灵ID"));
	if(rElement.LinkEndChild(pElem_wID.get()) != NULL)
		pElem_wID.release();
	unique_ptr<TiXmlElement> pElem_qwPlayerID(new TiXmlElement("UINT64"));
	if(pElem_qwPlayerID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwPlayerID->SetAttribute("name", "qwPlayerID");
	pElem_qwPlayerID->SetAttribute("value", NumberToString(s.qwPlayerID).c_str());
	pElem_qwPlayerID->SetAttribute("comment", ToUTF8Ptr("玩家ID"));
	if(rElement.LinkEndChild(pElem_qwPlayerID.get()) != NULL)
		pElem_qwPlayerID.release();
	unique_ptr<TiXmlElement> pElem_strName(new TiXmlElement("string"));
	if(pElem_strName == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strName->SetAttribute("name", "strName");
	pElem_strName->SetAttribute("value", s.strName.c_str());
	pElem_strName->SetAttribute("comment", ToUTF8Ptr("玩家名字|帮主名"));
	if(rElement.LinkEndChild(pElem_strName.get()) != NULL)
		pElem_strName.release();
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
	pElem_eCareer->SetAttribute("comment", ToUTF8Ptr("玩家职业"));
	if(rElement.LinkEndChild(pElem_eCareer.get()) != NULL)
		pElem_eCareer.release();
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
	pElem_eSex->SetAttribute("comment", ToUTF8Ptr("玩家性别"));
	if(rElement.LinkEndChild(pElem_eSex.get()) != NULL)
		pElem_eSex.release();
	unique_ptr<TiXmlElement> pElem_strName1(new TiXmlElement("string"));
	if(pElem_strName1 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strName1->SetAttribute("name", "strName1");
	pElem_strName1->SetAttribute("value", s.strName1.c_str());
	pElem_strName1->SetAttribute("comment", ToUTF8Ptr("帮派名"));
	if(rElement.LinkEndChild(pElem_strName1.get()) != NULL)
		pElem_strName1.release();
	unique_ptr<TiXmlElement> pElem_dwValue1(new TiXmlElement("UINT32"));
	if(pElem_dwValue1 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwValue1->SetAttribute("name", "dwValue1");
	pElem_dwValue1->SetAttribute("value", NumberToString(s.dwValue1).c_str());
	pElem_dwValue1->SetAttribute("comment", ToUTF8Ptr("参数1(战力，等级，散仙，阵灵，帮派）排名"));
	if(rElement.LinkEndChild(pElem_dwValue1.get()) != NULL)
		pElem_dwValue1.release();
	unique_ptr<TiXmlElement> pElem_dwValue2(new TiXmlElement("UINT32"));
	if(pElem_dwValue2 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwValue2->SetAttribute("name", "dwValue2");
	pElem_dwValue2->SetAttribute("value", NumberToString(s.dwValue2).c_str());
	pElem_dwValue2->SetAttribute("comment", ToUTF8Ptr("参数2(战力，等级，散仙战力，阵灵战力，帮派等级)"));
	if(rElement.LinkEndChild(pElem_dwValue2.get()) != NULL)
		pElem_dwValue2.release();
	return true;
}

#endif

STime::STime() : wWActID(0), dwAdvTime(0), dwBeginTime(0), dwEndTime(0), dwRetainTime(0) { }

STime::STime(UINT16 wWActID_, UINT32 dwAdvTime_, UINT32 dwBeginTime_, UINT32 dwEndTime_, UINT32 dwRetainTime_)
			: wWActID(wWActID_), dwAdvTime(dwAdvTime_), dwBeginTime(dwBeginTime_), dwEndTime(dwEndTime_), dwRetainTime(dwRetainTime_) { }

CInArchive& operator>>(CInArchive& src, STime& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.wWActID;
	src >> s.dwAdvTime;
	src >> s.dwBeginTime;
	src >> s.dwEndTime;
	src >> s.dwRetainTime;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const STime& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.wWActID;
	src << s.dwAdvTime;
	src << s.dwBeginTime;
	src << s.dwEndTime;
	src << s.dwRetainTime;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, STime& s)
{
	if(strcmp(rElement.Value(), "STime") != 0)
	{
		LOG_CRI << "rElement is not STime!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wWActID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wWActID") != 0)
	{
		LOG_CRI << "Attribute: name is not wWActID!";
		return false;
	}
	const char* pszVal_wWActID = pElemChild->Attribute("value");
	if(pszVal_wWActID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wWActID, s.wWActID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwAdvTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwAdvTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwAdvTime!";
		return false;
	}
	const char* pszVal_dwAdvTime = pElemChild->Attribute("value");
	if(pszVal_dwAdvTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwAdvTime, s.dwAdvTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwBeginTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwBeginTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwBeginTime!";
		return false;
	}
	const char* pszVal_dwBeginTime = pElemChild->Attribute("value");
	if(pszVal_dwBeginTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwBeginTime, s.dwBeginTime))
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
		LOG_CRI << "pElemChild for dwRetainTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwRetainTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwRetainTime!";
		return false;
	}
	const char* pszVal_dwRetainTime = pElemChild->Attribute("value");
	if(pszVal_dwRetainTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwRetainTime, s.dwRetainTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const STime& s, TiXmlElement& rElement)
{
	rElement.SetValue("STime");
	rElement.SetAttribute("type", ToUTF8Ptr("活动时间信息"));
	unique_ptr<TiXmlElement> pElem_wWActID(new TiXmlElement("UINT16"));
	if(pElem_wWActID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wWActID->SetAttribute("name", "wWActID");
	pElem_wWActID->SetAttribute("value", NumberToString(s.wWActID).c_str());
	pElem_wWActID->SetAttribute("comment", ToUTF8Ptr("活动ID"));
	if(rElement.LinkEndChild(pElem_wWActID.get()) != NULL)
		pElem_wWActID.release();
	unique_ptr<TiXmlElement> pElem_dwAdvTime(new TiXmlElement("UINT32"));
	if(pElem_dwAdvTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwAdvTime->SetAttribute("name", "dwAdvTime");
	pElem_dwAdvTime->SetAttribute("value", NumberToString(s.dwAdvTime).c_str());
	pElem_dwAdvTime->SetAttribute("comment", ToUTF8Ptr("活动预告时间"));
	if(rElement.LinkEndChild(pElem_dwAdvTime.get()) != NULL)
		pElem_dwAdvTime.release();
	unique_ptr<TiXmlElement> pElem_dwBeginTime(new TiXmlElement("UINT32"));
	if(pElem_dwBeginTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwBeginTime->SetAttribute("name", "dwBeginTime");
	pElem_dwBeginTime->SetAttribute("value", NumberToString(s.dwBeginTime).c_str());
	pElem_dwBeginTime->SetAttribute("comment", ToUTF8Ptr("活动开始时间"));
	if(rElement.LinkEndChild(pElem_dwBeginTime.get()) != NULL)
		pElem_dwBeginTime.release();
	unique_ptr<TiXmlElement> pElem_dwEndTime(new TiXmlElement("UINT32"));
	if(pElem_dwEndTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwEndTime->SetAttribute("name", "dwEndTime");
	pElem_dwEndTime->SetAttribute("value", NumberToString(s.dwEndTime).c_str());
	pElem_dwEndTime->SetAttribute("comment", ToUTF8Ptr("活动结束时间"));
	if(rElement.LinkEndChild(pElem_dwEndTime.get()) != NULL)
		pElem_dwEndTime.release();
	unique_ptr<TiXmlElement> pElem_dwRetainTime(new TiXmlElement("UINT32"));
	if(pElem_dwRetainTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwRetainTime->SetAttribute("name", "dwRetainTime");
	pElem_dwRetainTime->SetAttribute("value", NumberToString(s.dwRetainTime).c_str());
	pElem_dwRetainTime->SetAttribute("comment", ToUTF8Ptr("活动预留时间"));
	if(rElement.LinkEndChild(pElem_dwRetainTime.get()) != NULL)
		pElem_dwRetainTime.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecTime& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		STime s;
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

bool VectorToXML(const TVecTime& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("STime"));
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

SWonderPrize2DB::SWonderPrize2DB() : qwRoleID(0), wActID(0), wActType(0), wCond(0), byStatus(0) { }

SWonderPrize2DB::SWonderPrize2DB(UINT64 qwRoleID_, UINT16 wActID_, UINT16 wActType_, UINT32 wCond_, UINT8 byStatus_)
			: qwRoleID(qwRoleID_), wActID(wActID_), wActType(wActType_), wCond(wCond_), byStatus(byStatus_) { }

CInArchive& operator>>(CInArchive& src, SWonderPrize2DB& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwRoleID;
	src >> s.wActID;
	src >> s.wActType;
	src >> s.wCond;
	src >> s.byStatus;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SWonderPrize2DB& s)
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
	src << s.wActID;
	src << s.wActType;
	src << s.wCond;
	src << s.byStatus;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SWonderPrize2DB& s)
{
	if(strcmp(rElement.Value(), "SWonderPrize2DB") != 0)
	{
		LOG_CRI << "rElement is not SWonderPrize2DB!";
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
		LOG_CRI << "pElemChild for wActID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wActID") != 0)
	{
		LOG_CRI << "Attribute: name is not wActID!";
		return false;
	}
	const char* pszVal_wActID = pElemChild->Attribute("value");
	if(pszVal_wActID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wActID, s.wActID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wActType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wActType") != 0)
	{
		LOG_CRI << "Attribute: name is not wActType!";
		return false;
	}
	const char* pszVal_wActType = pElemChild->Attribute("value");
	if(pszVal_wActType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wActType, s.wActType))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wCond is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wCond") != 0)
	{
		LOG_CRI << "Attribute: name is not wCond!";
		return false;
	}
	const char* pszVal_wCond = pElemChild->Attribute("value");
	if(pszVal_wCond == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wCond, s.wCond))
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
	return true;
}

bool ToXML(const SWonderPrize2DB& s, TiXmlElement& rElement)
{
	rElement.SetValue("SWonderPrize2DB");
	rElement.SetAttribute("type", ToUTF8Ptr("数据库信息"));
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
	unique_ptr<TiXmlElement> pElem_wActID(new TiXmlElement("UINT16"));
	if(pElem_wActID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wActID->SetAttribute("name", "wActID");
	pElem_wActID->SetAttribute("value", NumberToString(s.wActID).c_str());
	pElem_wActID->SetAttribute("comment", ToUTF8Ptr("活动ID"));
	if(rElement.LinkEndChild(pElem_wActID.get()) != NULL)
		pElem_wActID.release();
	unique_ptr<TiXmlElement> pElem_wActType(new TiXmlElement("UINT16"));
	if(pElem_wActType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wActType->SetAttribute("name", "wActType");
	pElem_wActType->SetAttribute("value", NumberToString(s.wActType).c_str());
	pElem_wActType->SetAttribute("comment", ToUTF8Ptr("活动类型"));
	if(rElement.LinkEndChild(pElem_wActType.get()) != NULL)
		pElem_wActType.release();
	unique_ptr<TiXmlElement> pElem_wCond(new TiXmlElement("UINT32"));
	if(pElem_wCond == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wCond->SetAttribute("name", "wCond");
	pElem_wCond->SetAttribute("value", NumberToString(s.wCond).c_str());
	pElem_wCond->SetAttribute("comment", ToUTF8Ptr("活动条件"));
	if(rElement.LinkEndChild(pElem_wCond.get()) != NULL)
		pElem_wCond.release();
	unique_ptr<TiXmlElement> pElem_byStatus(new TiXmlElement("UINT8"));
	if(pElem_byStatus == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byStatus->SetAttribute("name", "byStatus");
	pElem_byStatus->SetAttribute("value", NumberToString(s.byStatus).c_str());
	pElem_byStatus->SetAttribute("comment", ToUTF8Ptr("活动状态"));
	if(rElement.LinkEndChild(pElem_byStatus.get()) != NULL)
		pElem_byStatus.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecWonderPrize2DB& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SWonderPrize2DB s;
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

bool VectorToXML(const TVecWonderPrize2DB& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SWonderPrize2DB"));
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

SPrizeStatus::SPrizeStatus() : qwRoleID(0), wActID(0) { }

SPrizeStatus::SPrizeStatus(UINT64 qwRoleID_, UINT16 wActID_, const TVecUINT8& vecStatus_) : qwRoleID(qwRoleID_), wActID(wActID_), vecStatus(vecStatus_) { }

CInArchive& operator>>(CInArchive& src, SPrizeStatus& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwRoleID;
	src >> s.wActID;
	src >> s.vecStatus;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SPrizeStatus& s)
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
	src << s.wActID;
	src << s.vecStatus;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SPrizeStatus& s)
{
	if(strcmp(rElement.Value(), "SPrizeStatus") != 0)
	{
		LOG_CRI << "rElement is not SPrizeStatus!";
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
		LOG_CRI << "pElemChild for wActID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wActID") != 0)
	{
		LOG_CRI << "Attribute: name is not wActID!";
		return false;
	}
	const char* pszVal_wActID = pElemChild->Attribute("value");
	if(pszVal_wActID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wActID, s.wActID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecStatus is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecUINT8") != 0)
	{
		LOG_CRI << "pElemChild is not TVecUINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecStatus") != 0)
	{
		LOG_CRI << "Attribute: name is not vecStatus!";
		return false;
	}
	const char* pszText_vecStatus = pElemChild->GetText();
	if(pszText_vecStatus != NULL)
		SplitToNumber(pszText_vecStatus, ",", s.vecStatus);
	return true;
}

bool ToXML(const SPrizeStatus& s, TiXmlElement& rElement)
{
	rElement.SetValue("SPrizeStatus");
	rElement.SetAttribute("type", ToUTF8Ptr("状态信息"));
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
	unique_ptr<TiXmlElement> pElem_wActID(new TiXmlElement("UINT16"));
	if(pElem_wActID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wActID->SetAttribute("name", "wActID");
	pElem_wActID->SetAttribute("value", NumberToString(s.wActID).c_str());
	pElem_wActID->SetAttribute("comment", ToUTF8Ptr("活动ID"));
	if(rElement.LinkEndChild(pElem_wActID.get()) != NULL)
		pElem_wActID.release();
	unique_ptr<TiXmlElement> pElem_vecStatus(new TiXmlElement("TVecUINT8"));
	if(pElem_vecStatus == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecStatus->SetAttribute("name", "vecStatus");
	string strText_vecStatus;
	for(size_t i = 0; i < s.vecStatus.size(); ++i)
	{
		if(i > 0)
			strText_vecStatus += ", ";
		strText_vecStatus += NumberToString(s.vecStatus[i]);
	}
	unique_ptr<TiXmlText> pText_vecStatus(new TiXmlText(strText_vecStatus.c_str()));
	if(pText_vecStatus == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(pElem_vecStatus->LinkEndChild(pText_vecStatus.get()) != NULL)
		pText_vecStatus.release();
	pElem_vecStatus->SetAttribute("comment", ToUTF8Ptr("活动状态"));
	if(rElement.LinkEndChild(pElem_vecStatus.get()) != NULL)
		pElem_vecStatus.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecPrizeStatus& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SPrizeStatus s;
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

bool VectorToXML(const TVecPrizeStatus& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SPrizeStatus"));
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

SRoleStatus::SRoleStatus() : wCond(0), dwMaxRole(0), dwCurRole(0), byStatus(0) { }

SRoleStatus::SRoleStatus(UINT32 wCond_, UINT32 dwMaxRole_, UINT32 dwCurRole_, UINT8 byStatus_) : wCond(wCond_), dwMaxRole(dwMaxRole_), dwCurRole(dwCurRole_), byStatus(byStatus_) { }

CInArchive& operator>>(CInArchive& src, SRoleStatus& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.wCond;
	src >> s.dwMaxRole;
	src >> s.dwCurRole;
	src >> s.byStatus;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SRoleStatus& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.wCond;
	src << s.dwMaxRole;
	src << s.dwCurRole;
	src << s.byStatus;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SRoleStatus& s)
{
	if(strcmp(rElement.Value(), "SRoleStatus") != 0)
	{
		LOG_CRI << "rElement is not SRoleStatus!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wCond is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wCond") != 0)
	{
		LOG_CRI << "Attribute: name is not wCond!";
		return false;
	}
	const char* pszVal_wCond = pElemChild->Attribute("value");
	if(pszVal_wCond == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wCond, s.wCond))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwMaxRole is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwMaxRole") != 0)
	{
		LOG_CRI << "Attribute: name is not dwMaxRole!";
		return false;
	}
	const char* pszVal_dwMaxRole = pElemChild->Attribute("value");
	if(pszVal_dwMaxRole == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwMaxRole, s.dwMaxRole))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwCurRole is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwCurRole") != 0)
	{
		LOG_CRI << "Attribute: name is not dwCurRole!";
		return false;
	}
	const char* pszVal_dwCurRole = pElemChild->Attribute("value");
	if(pszVal_dwCurRole == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwCurRole, s.dwCurRole))
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
	return true;
}

bool ToXML(const SRoleStatus& s, TiXmlElement& rElement)
{
	rElement.SetValue("SRoleStatus");
	rElement.SetAttribute("type", ToUTF8Ptr("玩家在活动中的状态信息"));
	unique_ptr<TiXmlElement> pElem_wCond(new TiXmlElement("UINT32"));
	if(pElem_wCond == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wCond->SetAttribute("name", "wCond");
	pElem_wCond->SetAttribute("value", NumberToString(s.wCond).c_str());
	pElem_wCond->SetAttribute("comment", ToUTF8Ptr("活动ID"));
	if(rElement.LinkEndChild(pElem_wCond.get()) != NULL)
		pElem_wCond.release();
	unique_ptr<TiXmlElement> pElem_dwMaxRole(new TiXmlElement("UINT32"));
	if(pElem_dwMaxRole == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwMaxRole->SetAttribute("name", "dwMaxRole");
	pElem_dwMaxRole->SetAttribute("value", NumberToString(s.dwMaxRole).c_str());
	pElem_dwMaxRole->SetAttribute("comment", ToUTF8Ptr("活动达到条件人数"));
	if(rElement.LinkEndChild(pElem_dwMaxRole.get()) != NULL)
		pElem_dwMaxRole.release();
	unique_ptr<TiXmlElement> pElem_dwCurRole(new TiXmlElement("UINT32"));
	if(pElem_dwCurRole == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwCurRole->SetAttribute("name", "dwCurRole");
	pElem_dwCurRole->SetAttribute("value", NumberToString(s.dwCurRole).c_str());
	pElem_dwCurRole->SetAttribute("comment", ToUTF8Ptr("活动目前人数"));
	if(rElement.LinkEndChild(pElem_dwCurRole.get()) != NULL)
		pElem_dwCurRole.release();
	unique_ptr<TiXmlElement> pElem_byStatus(new TiXmlElement("UINT8"));
	if(pElem_byStatus == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byStatus->SetAttribute("name", "byStatus");
	pElem_byStatus->SetAttribute("value", NumberToString(s.byStatus).c_str());
	pElem_byStatus->SetAttribute("comment", ToUTF8Ptr("活动状态"));
	if(rElement.LinkEndChild(pElem_byStatus.get()) != NULL)
		pElem_byStatus.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecRoleStatus& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SRoleStatus s;
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

bool VectorToXML(const TVecRoleStatus& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SRoleStatus"));
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

SRetain::SRetain() : qwRoleID(0), byCareer(0), bySex(0), wActID(0), wID(0), 
			wType(0), dwValue(0), dwTime(0) { }

SRetain::SRetain(UINT64 qwRoleID_, const std::string& strName_, UINT8 byCareer_, UINT8 bySex_, UINT16 wActID_, 
			UINT16 wID_, const std::string& strGuildName_, UINT16 wType_, UINT32 dwValue_, UINT32 dwTime_)
			: qwRoleID(qwRoleID_), strName(strName_), byCareer(byCareer_), bySex(bySex_), wActID(wActID_), 
			wID(wID_), strGuildName(strGuildName_), wType(wType_), dwValue(dwValue_), dwTime(dwTime_) { }

SRetain::SRetain(SRetain&& src) : qwRoleID(src.qwRoleID), strName(move(src.strName)), byCareer(src.byCareer), bySex(src.bySex), wActID(src.wActID), 
			wID(src.wID), strGuildName(move(src.strGuildName)), wType(src.wType), dwValue(src.dwValue), dwTime(src.dwTime) { }

SRetain& SRetain::operator=(SRetain&& rhs)
{
	if(this != &rhs)
	{
		this->~SRetain();
		new (this) SRetain(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SRetain& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwRoleID;
	src >> s.strName;
	src >> s.byCareer;
	src >> s.bySex;
	src >> s.wActID;
	src >> s.wID;
	src >> s.strGuildName;
	src >> s.wType;
	src >> s.dwValue;
	src >> s.dwTime;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SRetain& s)
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
	src << s.byCareer;
	src << s.bySex;
	src << s.wActID;
	src << s.wID;
	src << s.strGuildName;
	src << s.wType;
	src << s.dwValue;
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

bool FromXML(TiXmlElement& rElement, SRetain& s)
{
	if(strcmp(rElement.Value(), "SRetain") != 0)
	{
		LOG_CRI << "rElement is not SRetain!";
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
		LOG_CRI << "pElemChild for byCareer is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byCareer") != 0)
	{
		LOG_CRI << "Attribute: name is not byCareer!";
		return false;
	}
	const char* pszVal_byCareer = pElemChild->Attribute("value");
	if(pszVal_byCareer == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byCareer, s.byCareer))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for bySex is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "bySex") != 0)
	{
		LOG_CRI << "Attribute: name is not bySex!";
		return false;
	}
	const char* pszVal_bySex = pElemChild->Attribute("value");
	if(pszVal_bySex == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_bySex, s.bySex))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wActID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wActID") != 0)
	{
		LOG_CRI << "Attribute: name is not wActID!";
		return false;
	}
	const char* pszVal_wActID = pElemChild->Attribute("value");
	if(pszVal_wActID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wActID, s.wActID))
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
		LOG_CRI << "pElemChild for wType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wType") != 0)
	{
		LOG_CRI << "Attribute: name is not wType!";
		return false;
	}
	const char* pszVal_wType = pElemChild->Attribute("value");
	if(pszVal_wType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wType, s.wType))
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

bool ToXML(const SRetain& s, TiXmlElement& rElement)
{
	rElement.SetValue("SRetain");
	rElement.SetAttribute("type", ToUTF8Ptr("玩家在活动中的保留值"));
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
	pElem_strName->SetAttribute("comment", ToUTF8Ptr("玩家名字"));
	if(rElement.LinkEndChild(pElem_strName.get()) != NULL)
		pElem_strName.release();
	unique_ptr<TiXmlElement> pElem_byCareer(new TiXmlElement("UINT8"));
	if(pElem_byCareer == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byCareer->SetAttribute("name", "byCareer");
	pElem_byCareer->SetAttribute("value", NumberToString(s.byCareer).c_str());
	pElem_byCareer->SetAttribute("comment", ToUTF8Ptr("玩家职业"));
	if(rElement.LinkEndChild(pElem_byCareer.get()) != NULL)
		pElem_byCareer.release();
	unique_ptr<TiXmlElement> pElem_bySex(new TiXmlElement("UINT8"));
	if(pElem_bySex == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_bySex->SetAttribute("name", "bySex");
	pElem_bySex->SetAttribute("value", NumberToString(s.bySex).c_str());
	pElem_bySex->SetAttribute("comment", ToUTF8Ptr("性别"));
	if(rElement.LinkEndChild(pElem_bySex.get()) != NULL)
		pElem_bySex.release();
	unique_ptr<TiXmlElement> pElem_wActID(new TiXmlElement("UINT16"));
	if(pElem_wActID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wActID->SetAttribute("name", "wActID");
	pElem_wActID->SetAttribute("value", NumberToString(s.wActID).c_str());
	pElem_wActID->SetAttribute("comment", ToUTF8Ptr("活动ID"));
	if(rElement.LinkEndChild(pElem_wActID.get()) != NULL)
		pElem_wActID.release();
	unique_ptr<TiXmlElement> pElem_wID(new TiXmlElement("UINT16"));
	if(pElem_wID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wID->SetAttribute("name", "wID");
	pElem_wID->SetAttribute("value", NumberToString(s.wID).c_str());
	pElem_wID->SetAttribute("comment", ToUTF8Ptr("保留值（散仙ID,帮派ID,阵灵ID.....)"));
	if(rElement.LinkEndChild(pElem_wID.get()) != NULL)
		pElem_wID.release();
	unique_ptr<TiXmlElement> pElem_strGuildName(new TiXmlElement("string"));
	if(pElem_strGuildName == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strGuildName->SetAttribute("name", "strGuildName");
	pElem_strGuildName->SetAttribute("value", s.strGuildName.c_str());
	pElem_strGuildName->SetAttribute("comment", ToUTF8Ptr("帮派名字"));
	if(rElement.LinkEndChild(pElem_strGuildName.get()) != NULL)
		pElem_strGuildName.release();
	unique_ptr<TiXmlElement> pElem_wType(new TiXmlElement("UINT16"));
	if(pElem_wType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wType->SetAttribute("name", "wType");
	pElem_wType->SetAttribute("value", NumberToString(s.wType).c_str());
	pElem_wType->SetAttribute("comment", ToUTF8Ptr("保留类型"));
	if(rElement.LinkEndChild(pElem_wType.get()) != NULL)
		pElem_wType.release();
	unique_ptr<TiXmlElement> pElem_dwValue(new TiXmlElement("UINT32"));
	if(pElem_dwValue == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwValue->SetAttribute("name", "dwValue");
	pElem_dwValue->SetAttribute("value", NumberToString(s.dwValue).c_str());
	pElem_dwValue->SetAttribute("comment", ToUTF8Ptr("保留值"));
	if(rElement.LinkEndChild(pElem_dwValue.get()) != NULL)
		pElem_dwValue.release();
	unique_ptr<TiXmlElement> pElem_dwTime(new TiXmlElement("UINT32"));
	if(pElem_dwTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwTime->SetAttribute("name", "dwTime");
	pElem_dwTime->SetAttribute("value", NumberToString(s.dwTime).c_str());
	pElem_dwTime->SetAttribute("comment", ToUTF8Ptr("时间"));
	if(rElement.LinkEndChild(pElem_dwTime.get()) != NULL)
		pElem_dwTime.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecRetain& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SRetain s;
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

bool VectorToXML(const TVecRetain& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SRetain"));
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

SRoleAllStatus::SRoleAllStatus() : wActID(0) { }

SRoleAllStatus::SRoleAllStatus(UINT16 wActID_, const TVecRoleStatus& vecAllState_) : wActID(wActID_), vecAllState(vecAllState_) { }

SRoleAllStatus::SRoleAllStatus(SRoleAllStatus&& src) : wActID(src.wActID), vecAllState(move(src.vecAllState)) { }

SRoleAllStatus& SRoleAllStatus::operator=(SRoleAllStatus&& rhs)
{
	if(this != &rhs)
	{
		this->~SRoleAllStatus();
		new (this) SRoleAllStatus(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SRoleAllStatus& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.wActID;
	src >> s.vecAllState;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SRoleAllStatus& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.wActID;
	src << s.vecAllState;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SRoleAllStatus& s)
{
	if(strcmp(rElement.Value(), "SRoleAllStatus") != 0)
	{
		LOG_CRI << "rElement is not SRoleAllStatus!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wActID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wActID") != 0)
	{
		LOG_CRI << "Attribute: name is not wActID!";
		return false;
	}
	const char* pszVal_wActID = pElemChild->Attribute("value");
	if(pszVal_wActID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wActID, s.wActID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecAllState is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecRoleStatus") != 0)
	{
		LOG_CRI << "pElemChild is not TVecRoleStatus!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecAllState") != 0)
	{
		LOG_CRI << "Attribute: name is not vecAllState!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecAllState))
	{
		LOG_CRI << "VectorFromXML for vecAllState fails!";
		return false;
	}
	return true;
}

bool ToXML(const SRoleAllStatus& s, TiXmlElement& rElement)
{
	rElement.SetValue("SRoleAllStatus");
	rElement.SetAttribute("type", ToUTF8Ptr("玩家在所有活动中的信息"));
	unique_ptr<TiXmlElement> pElem_wActID(new TiXmlElement("UINT16"));
	if(pElem_wActID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wActID->SetAttribute("name", "wActID");
	pElem_wActID->SetAttribute("value", NumberToString(s.wActID).c_str());
	pElem_wActID->SetAttribute("comment", ToUTF8Ptr("活动ID"));
	if(rElement.LinkEndChild(pElem_wActID.get()) != NULL)
		pElem_wActID.release();
	unique_ptr<TiXmlElement> pElem_vecAllState(new TiXmlElement("TVecRoleStatus"));
	if(pElem_vecAllState == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecAllState->SetAttribute("name", "vecAllState");
	if(!VectorToXML(s.vecAllState, *pElem_vecAllState))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecAllState->SetAttribute("comment", ToUTF8Ptr("状态"));
	if(rElement.LinkEndChild(pElem_vecAllState.get()) != NULL)
		pElem_vecAllState.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecRoleAllStatus& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SRoleAllStatus s;
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

bool VectorToXML(const TVecRoleAllStatus& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SRoleAllStatus"));
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

SDragonBallAct::SDragonBallAct() : dwBeginTime(0), dwEndTime(0), dwRecharge(0), byIdx(0), byDay(0), 
			byAll(0), byRemain(0) { }

SDragonBallAct::SDragonBallAct(UINT32 dwBeginTime_, UINT32 dwEndTime_, UINT32 dwRecharge_, UINT8 byIdx_, UINT8 byDay_, 
			UINT8 byAll_, UINT8 byRemain_)
			: dwBeginTime(dwBeginTime_), dwEndTime(dwEndTime_), dwRecharge(dwRecharge_), byIdx(byIdx_), byDay(byDay_), 
			byAll(byAll_), byRemain(byRemain_) { }

CInArchive& operator>>(CInArchive& src, SDragonBallAct& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.dwBeginTime;
	src >> s.dwEndTime;
	src >> s.dwRecharge;
	src >> s.byIdx;
	src >> s.byDay;
	src >> s.byAll;
	src >> s.byRemain;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SDragonBallAct& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.dwBeginTime;
	src << s.dwEndTime;
	src << s.dwRecharge;
	src << s.byIdx;
	src << s.byDay;
	src << s.byAll;
	src << s.byRemain;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SDragonBallAct& s)
{
	if(strcmp(rElement.Value(), "SDragonBallAct") != 0)
	{
		LOG_CRI << "rElement is not SDragonBallAct!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwBeginTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwBeginTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwBeginTime!";
		return false;
	}
	const char* pszVal_dwBeginTime = pElemChild->Attribute("value");
	if(pszVal_dwBeginTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwBeginTime, s.dwBeginTime))
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
		LOG_CRI << "pElemChild for dwRecharge is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwRecharge") != 0)
	{
		LOG_CRI << "Attribute: name is not dwRecharge!";
		return false;
	}
	const char* pszVal_dwRecharge = pElemChild->Attribute("value");
	if(pszVal_dwRecharge == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwRecharge, s.dwRecharge))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
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
		LOG_CRI << "pElemChild for byDay is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byDay") != 0)
	{
		LOG_CRI << "Attribute: name is not byDay!";
		return false;
	}
	const char* pszVal_byDay = pElemChild->Attribute("value");
	if(pszVal_byDay == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byDay, s.byDay))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byAll is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byAll") != 0)
	{
		LOG_CRI << "Attribute: name is not byAll!";
		return false;
	}
	const char* pszVal_byAll = pElemChild->Attribute("value");
	if(pszVal_byAll == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byAll, s.byAll))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byRemain is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byRemain") != 0)
	{
		LOG_CRI << "Attribute: name is not byRemain!";
		return false;
	}
	const char* pszVal_byRemain = pElemChild->Attribute("value");
	if(pszVal_byRemain == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byRemain, s.byRemain))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SDragonBallAct& s, TiXmlElement& rElement)
{
	rElement.SetValue("SDragonBallAct");
	rElement.SetAttribute("type", ToUTF8Ptr("七星龙珠活动信息"));
	unique_ptr<TiXmlElement> pElem_dwBeginTime(new TiXmlElement("UINT32"));
	if(pElem_dwBeginTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwBeginTime->SetAttribute("name", "dwBeginTime");
	pElem_dwBeginTime->SetAttribute("value", NumberToString(s.dwBeginTime).c_str());
	pElem_dwBeginTime->SetAttribute("comment", ToUTF8Ptr("活动开始时间"));
	if(rElement.LinkEndChild(pElem_dwBeginTime.get()) != NULL)
		pElem_dwBeginTime.release();
	unique_ptr<TiXmlElement> pElem_dwEndTime(new TiXmlElement("UINT32"));
	if(pElem_dwEndTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwEndTime->SetAttribute("name", "dwEndTime");
	pElem_dwEndTime->SetAttribute("value", NumberToString(s.dwEndTime).c_str());
	pElem_dwEndTime->SetAttribute("comment", ToUTF8Ptr("活动结束时间"));
	if(rElement.LinkEndChild(pElem_dwEndTime.get()) != NULL)
		pElem_dwEndTime.release();
	unique_ptr<TiXmlElement> pElem_dwRecharge(new TiXmlElement("UINT32"));
	if(pElem_dwRecharge == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwRecharge->SetAttribute("name", "dwRecharge");
	pElem_dwRecharge->SetAttribute("value", NumberToString(s.dwRecharge).c_str());
	pElem_dwRecharge->SetAttribute("comment", ToUTF8Ptr("今日充值仙石数"));
	if(rElement.LinkEndChild(pElem_dwRecharge.get()) != NULL)
		pElem_dwRecharge.release();
	unique_ptr<TiXmlElement> pElem_byIdx(new TiXmlElement("UINT8"));
	if(pElem_byIdx == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byIdx->SetAttribute("name", "byIdx");
	pElem_byIdx->SetAttribute("value", NumberToString(s.byIdx).c_str());
	pElem_byIdx->SetAttribute("comment", ToUTF8Ptr("第几期活动"));
	if(rElement.LinkEndChild(pElem_byIdx.get()) != NULL)
		pElem_byIdx.release();
	unique_ptr<TiXmlElement> pElem_byDay(new TiXmlElement("UINT8"));
	if(pElem_byDay == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byDay->SetAttribute("name", "byDay");
	pElem_byDay->SetAttribute("value", NumberToString(s.byDay).c_str());
	pElem_byDay->SetAttribute("comment", ToUTF8Ptr("今日完成的龙珠数"));
	if(rElement.LinkEndChild(pElem_byDay.get()) != NULL)
		pElem_byDay.release();
	unique_ptr<TiXmlElement> pElem_byAll(new TiXmlElement("UINT8"));
	if(pElem_byAll == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byAll->SetAttribute("name", "byAll");
	pElem_byAll->SetAttribute("value", NumberToString(s.byAll).c_str());
	pElem_byAll->SetAttribute("comment", ToUTF8Ptr("完成的龙珠总数"));
	if(rElement.LinkEndChild(pElem_byAll.get()) != NULL)
		pElem_byAll.release();
	unique_ptr<TiXmlElement> pElem_byRemain(new TiXmlElement("UINT8"));
	if(pElem_byRemain == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byRemain->SetAttribute("name", "byRemain");
	pElem_byRemain->SetAttribute("value", NumberToString(s.byRemain).c_str());
	pElem_byRemain->SetAttribute("comment", ToUTF8Ptr("今日之前剩余可点亮的龙珠数"));
	if(rElement.LinkEndChild(pElem_byRemain.get()) != NULL)
		pElem_byRemain.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecDragonBallAct& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SDragonBallAct s;
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

bool VectorToXML(const TVecDragonBallAct& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SDragonBallAct"));
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

SSevenConsumeAct::SSevenConsumeAct() : dwBeginTime(0), dwEndTime(0), dwConsume(0), byInfo(0) { }

SSevenConsumeAct::SSevenConsumeAct(UINT32 dwBeginTime_, UINT32 dwEndTime_, UINT32 dwConsume_, UINT8 byInfo_) : dwBeginTime(dwBeginTime_), dwEndTime(dwEndTime_), dwConsume(dwConsume_), byInfo(byInfo_) { }

CInArchive& operator>>(CInArchive& src, SSevenConsumeAct& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.dwBeginTime;
	src >> s.dwEndTime;
	src >> s.dwConsume;
	src >> s.byInfo;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SSevenConsumeAct& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.dwBeginTime;
	src << s.dwEndTime;
	src << s.dwConsume;
	src << s.byInfo;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SSevenConsumeAct& s)
{
	if(strcmp(rElement.Value(), "SSevenConsumeAct") != 0)
	{
		LOG_CRI << "rElement is not SSevenConsumeAct!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwBeginTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwBeginTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwBeginTime!";
		return false;
	}
	const char* pszVal_dwBeginTime = pElemChild->Attribute("value");
	if(pszVal_dwBeginTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwBeginTime, s.dwBeginTime))
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
		LOG_CRI << "pElemChild for dwConsume is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwConsume") != 0)
	{
		LOG_CRI << "Attribute: name is not dwConsume!";
		return false;
	}
	const char* pszVal_dwConsume = pElemChild->Attribute("value");
	if(pszVal_dwConsume == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwConsume, s.dwConsume))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not byInfo!";
		return false;
	}
	const char* pszVal_byInfo = pElemChild->Attribute("value");
	if(pszVal_byInfo == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byInfo, s.byInfo))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SSevenConsumeAct& s, TiXmlElement& rElement)
{
	rElement.SetValue("SSevenConsumeAct");
	rElement.SetAttribute("type", ToUTF8Ptr("七日消费活动信息"));
	unique_ptr<TiXmlElement> pElem_dwBeginTime(new TiXmlElement("UINT32"));
	if(pElem_dwBeginTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwBeginTime->SetAttribute("name", "dwBeginTime");
	pElem_dwBeginTime->SetAttribute("value", NumberToString(s.dwBeginTime).c_str());
	pElem_dwBeginTime->SetAttribute("comment", ToUTF8Ptr("活动开始时间"));
	if(rElement.LinkEndChild(pElem_dwBeginTime.get()) != NULL)
		pElem_dwBeginTime.release();
	unique_ptr<TiXmlElement> pElem_dwEndTime(new TiXmlElement("UINT32"));
	if(pElem_dwEndTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwEndTime->SetAttribute("name", "dwEndTime");
	pElem_dwEndTime->SetAttribute("value", NumberToString(s.dwEndTime).c_str());
	pElem_dwEndTime->SetAttribute("comment", ToUTF8Ptr("活动结束时间"));
	if(rElement.LinkEndChild(pElem_dwEndTime.get()) != NULL)
		pElem_dwEndTime.release();
	unique_ptr<TiXmlElement> pElem_dwConsume(new TiXmlElement("UINT32"));
	if(pElem_dwConsume == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwConsume->SetAttribute("name", "dwConsume");
	pElem_dwConsume->SetAttribute("value", NumberToString(s.dwConsume).c_str());
	pElem_dwConsume->SetAttribute("comment", ToUTF8Ptr("七日总消费仙石数"));
	if(rElement.LinkEndChild(pElem_dwConsume.get()) != NULL)
		pElem_dwConsume.release();
	unique_ptr<TiXmlElement> pElem_byInfo(new TiXmlElement("UINT8"));
	if(pElem_byInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byInfo->SetAttribute("name", "byInfo");
	pElem_byInfo->SetAttribute("value", NumberToString(s.byInfo).c_str());
	pElem_byInfo->SetAttribute("comment", ToUTF8Ptr("奖励领取状态信息(从低到高按位取,1已领取 0未领取)"));
	if(rElement.LinkEndChild(pElem_byInfo.get()) != NULL)
		pElem_byInfo.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecSevenConsumeAct& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SSevenConsumeAct s;
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

bool VectorToXML(const TVecSevenConsumeAct& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SSevenConsumeAct"));
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

SQQCoinActInfo::SQQCoinActInfo() : dwTime(0), byLevel(0), dwMaxValue(0), dwCurValue(0) { }

SQQCoinActInfo::SQQCoinActInfo(UINT32 dwTime_, UINT8 byLevel_, UINT32 dwMaxValue_, UINT32 dwCurValue_) : dwTime(dwTime_), byLevel(byLevel_), dwMaxValue(dwMaxValue_), dwCurValue(dwCurValue_) { }

CInArchive& operator>>(CInArchive& src, SQQCoinActInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.dwTime;
	src >> s.byLevel;
	src >> s.dwMaxValue;
	src >> s.dwCurValue;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SQQCoinActInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.dwTime;
	src << s.byLevel;
	src << s.dwMaxValue;
	src << s.dwCurValue;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SQQCoinActInfo& s)
{
	if(strcmp(rElement.Value(), "SQQCoinActInfo") != 0)
	{
		LOG_CRI << "rElement is not SQQCoinActInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
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
		LOG_CRI << "pElemChild for dwMaxValue is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwMaxValue") != 0)
	{
		LOG_CRI << "Attribute: name is not dwMaxValue!";
		return false;
	}
	const char* pszVal_dwMaxValue = pElemChild->Attribute("value");
	if(pszVal_dwMaxValue == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwMaxValue, s.dwMaxValue))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwCurValue is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwCurValue") != 0)
	{
		LOG_CRI << "Attribute: name is not dwCurValue!";
		return false;
	}
	const char* pszVal_dwCurValue = pElemChild->Attribute("value");
	if(pszVal_dwCurValue == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwCurValue, s.dwCurValue))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SQQCoinActInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SQQCoinActInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("Q币养成活动信息"));
	unique_ptr<TiXmlElement> pElem_dwTime(new TiXmlElement("UINT32"));
	if(pElem_dwTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwTime->SetAttribute("name", "dwTime");
	pElem_dwTime->SetAttribute("value", NumberToString(s.dwTime).c_str());
	pElem_dwTime->SetAttribute("comment", ToUTF8Ptr("活动剩余时间"));
	if(rElement.LinkEndChild(pElem_dwTime.get()) != NULL)
		pElem_dwTime.release();
	unique_ptr<TiXmlElement> pElem_byLevel(new TiXmlElement("UINT8"));
	if(pElem_byLevel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byLevel->SetAttribute("name", "byLevel");
	pElem_byLevel->SetAttribute("value", NumberToString(s.byLevel).c_str());
	pElem_byLevel->SetAttribute("comment", ToUTF8Ptr("当前兑换的等级"));
	if(rElement.LinkEndChild(pElem_byLevel.get()) != NULL)
		pElem_byLevel.release();
	unique_ptr<TiXmlElement> pElem_dwMaxValue(new TiXmlElement("UINT32"));
	if(pElem_dwMaxValue == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwMaxValue->SetAttribute("name", "dwMaxValue");
	pElem_dwMaxValue->SetAttribute("value", NumberToString(s.dwMaxValue).c_str());
	pElem_dwMaxValue->SetAttribute("comment", ToUTF8Ptr("奖励最大值"));
	if(rElement.LinkEndChild(pElem_dwMaxValue.get()) != NULL)
		pElem_dwMaxValue.release();
	unique_ptr<TiXmlElement> pElem_dwCurValue(new TiXmlElement("UINT32"));
	if(pElem_dwCurValue == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwCurValue->SetAttribute("name", "dwCurValue");
	pElem_dwCurValue->SetAttribute("value", NumberToString(s.dwCurValue).c_str());
	pElem_dwCurValue->SetAttribute("comment", ToUTF8Ptr("当前值"));
	if(rElement.LinkEndChild(pElem_dwCurValue.get()) != NULL)
		pElem_dwCurValue.release();
	return true;
}

#endif

} //namespace NWonderActivityProt
