/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    YelloDiamondProt.cpp
//  Purpose:      QQ黄钻协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "YelloDiamondProt.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NYelloDiamondProt
{

#ifdef PROT_USE_XML

const char* EnumValToStr(EOpResult e)
{
	switch(e)
	{
	case eOtherError:
		return "eOtherError";
	case eShortLevel:
		return "eShortLevel";
	case eNotActive:
		return "eNotActive";
	case eNotYear:
		return "eNotYear";
	case eNotLuxury:
		return "eNotLuxury";
	case eAreadyGain:
		return "eAreadyGain";
	case eBagFull:
		return "eBagFull";
	case eSuccess:
		return "eSuccess";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EOpResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EOpResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eOtherError", eOtherError));
		mapStr2Val.insert(make_pair("eShortLevel", eShortLevel));
		mapStr2Val.insert(make_pair("eNotActive", eNotActive));
		mapStr2Val.insert(make_pair("eNotYear", eNotYear));
		mapStr2Val.insert(make_pair("eNotLuxury", eNotLuxury));
		mapStr2Val.insert(make_pair("eAreadyGain", eAreadyGain));
		mapStr2Val.insert(make_pair("eBagFull", eBagFull));
		mapStr2Val.insert(make_pair("eSuccess", eSuccess));
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

const char* EnumValToStr(EBagType e)
{
	switch(e)
	{
	case EBagType_eNone:
		return "EBagType_eNone";
	case EBagType_eDayBag:
		return "EBagType_eDayBag";
	case EBagType_eYearBag:
		return "EBagType_eYearBag";
	case EBagType_eLuxuryBag:
		return "EBagType_eLuxuryBag";
	case EBagType_eNewBag:
		return "EBagType_eNewBag";
	case EBagType_eGrowBag:
		return "EBagType_eGrowBag";
	case EBagType_eHorseBag:
		return "EBagType_eHorseBag";
	case EBagType_eMax:
		return "EBagType_eMax";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EBagType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EBagType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("EBagType_eNone", EBagType_eNone));
		mapStr2Val.insert(make_pair("EBagType_eDayBag", EBagType_eDayBag));
		mapStr2Val.insert(make_pair("EBagType_eYearBag", EBagType_eYearBag));
		mapStr2Val.insert(make_pair("EBagType_eLuxuryBag", EBagType_eLuxuryBag));
		mapStr2Val.insert(make_pair("EBagType_eNewBag", EBagType_eNewBag));
		mapStr2Val.insert(make_pair("EBagType_eGrowBag", EBagType_eGrowBag));
		mapStr2Val.insert(make_pair("EBagType_eHorseBag", EBagType_eHorseBag));
		mapStr2Val.insert(make_pair("EBagType_eMax", EBagType_eMax));
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

const char* EnumValToStr(EYDType e)
{
	switch(e)
	{
	case EYDType_eNone:
		return "EYDType_eNone";
	case EYDType_eDayType:
		return "EYDType_eDayType";
	case EYDType_eYearType:
		return "EYDType_eYearType";
	case EYDType_eLuxuryType:
		return "EYDType_eLuxuryType";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EYDType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EYDType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("EYDType_eNone", EYDType_eNone));
		mapStr2Val.insert(make_pair("EYDType_eDayType", EYDType_eDayType));
		mapStr2Val.insert(make_pair("EYDType_eYearType", EYDType_eYearType));
		mapStr2Val.insert(make_pair("EYDType_eLuxuryType", EYDType_eLuxuryType));
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

SYDInfo::SYDInfo() : bGainDayBag(false), bGainYearBag(false), bGainLuxuryBag(false), bGainHorseBag(false), dGrowBag(0), 
			bGainNewBag(false) { }

SYDInfo::SYDInfo(bool bGainDayBag_, bool bGainYearBag_, bool bGainLuxuryBag_, bool bGainHorseBag_, UINT16 dGrowBag_, 
			bool bGainNewBag_)
			: bGainDayBag(bGainDayBag_), bGainYearBag(bGainYearBag_), bGainLuxuryBag(bGainLuxuryBag_), bGainHorseBag(bGainHorseBag_), dGrowBag(dGrowBag_), 
			bGainNewBag(bGainNewBag_) { }

CInArchive& operator>>(CInArchive& src, SYDInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.bGainDayBag;
	src >> s.bGainYearBag;
	src >> s.bGainLuxuryBag;
	src >> s.bGainHorseBag;
	src >> s.dGrowBag;
	src >> s.bGainNewBag;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SYDInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.bGainDayBag;
	src << s.bGainYearBag;
	src << s.bGainLuxuryBag;
	src << s.bGainHorseBag;
	src << s.dGrowBag;
	src << s.bGainNewBag;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SYDInfo& s)
{
	if(strcmp(rElement.Value(), "SYDInfo") != 0)
	{
		LOG_CRI << "rElement is not SYDInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for bGainDayBag is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "bool") != 0)
	{
		LOG_CRI << "pElemChild is not bool!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "bGainDayBag") != 0)
	{
		LOG_CRI << "Attribute: name is not bGainDayBag!";
		return false;
	}
	const char* pszVal_bGainDayBag = pElemChild->Attribute("value");
	if(pszVal_bGainDayBag == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_bGainDayBag, s.bGainDayBag))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for bGainYearBag is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "bool") != 0)
	{
		LOG_CRI << "pElemChild is not bool!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "bGainYearBag") != 0)
	{
		LOG_CRI << "Attribute: name is not bGainYearBag!";
		return false;
	}
	const char* pszVal_bGainYearBag = pElemChild->Attribute("value");
	if(pszVal_bGainYearBag == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_bGainYearBag, s.bGainYearBag))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for bGainLuxuryBag is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "bool") != 0)
	{
		LOG_CRI << "pElemChild is not bool!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "bGainLuxuryBag") != 0)
	{
		LOG_CRI << "Attribute: name is not bGainLuxuryBag!";
		return false;
	}
	const char* pszVal_bGainLuxuryBag = pElemChild->Attribute("value");
	if(pszVal_bGainLuxuryBag == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_bGainLuxuryBag, s.bGainLuxuryBag))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for bGainHorseBag is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "bool") != 0)
	{
		LOG_CRI << "pElemChild is not bool!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "bGainHorseBag") != 0)
	{
		LOG_CRI << "Attribute: name is not bGainHorseBag!";
		return false;
	}
	const char* pszVal_bGainHorseBag = pElemChild->Attribute("value");
	if(pszVal_bGainHorseBag == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_bGainHorseBag, s.bGainHorseBag))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dGrowBag is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dGrowBag") != 0)
	{
		LOG_CRI << "Attribute: name is not dGrowBag!";
		return false;
	}
	const char* pszVal_dGrowBag = pElemChild->Attribute("value");
	if(pszVal_dGrowBag == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dGrowBag, s.dGrowBag))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for bGainNewBag is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "bool") != 0)
	{
		LOG_CRI << "pElemChild is not bool!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "bGainNewBag") != 0)
	{
		LOG_CRI << "Attribute: name is not bGainNewBag!";
		return false;
	}
	const char* pszVal_bGainNewBag = pElemChild->Attribute("value");
	if(pszVal_bGainNewBag == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_bGainNewBag, s.bGainNewBag))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SYDInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SYDInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("QQ黄钻信息"));
	unique_ptr<TiXmlElement> pElem_bGainDayBag(new TiXmlElement("bool"));
	if(pElem_bGainDayBag == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_bGainDayBag->SetAttribute("name", "bGainDayBag");
	pElem_bGainDayBag->SetAttribute("value", NumberToString(s.bGainDayBag).c_str());
	pElem_bGainDayBag->SetAttribute("comment", ToUTF8Ptr("是否领取每日礼包"));
	if(rElement.LinkEndChild(pElem_bGainDayBag.get()) != NULL)
		pElem_bGainDayBag.release();
	unique_ptr<TiXmlElement> pElem_bGainYearBag(new TiXmlElement("bool"));
	if(pElem_bGainYearBag == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_bGainYearBag->SetAttribute("name", "bGainYearBag");
	pElem_bGainYearBag->SetAttribute("value", NumberToString(s.bGainYearBag).c_str());
	pElem_bGainYearBag->SetAttribute("comment", ToUTF8Ptr("是否领取年费礼包"));
	if(rElement.LinkEndChild(pElem_bGainYearBag.get()) != NULL)
		pElem_bGainYearBag.release();
	unique_ptr<TiXmlElement> pElem_bGainLuxuryBag(new TiXmlElement("bool"));
	if(pElem_bGainLuxuryBag == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_bGainLuxuryBag->SetAttribute("name", "bGainLuxuryBag");
	pElem_bGainLuxuryBag->SetAttribute("value", NumberToString(s.bGainLuxuryBag).c_str());
	pElem_bGainLuxuryBag->SetAttribute("comment", ToUTF8Ptr("是否领取豪华礼包"));
	if(rElement.LinkEndChild(pElem_bGainLuxuryBag.get()) != NULL)
		pElem_bGainLuxuryBag.release();
	unique_ptr<TiXmlElement> pElem_bGainHorseBag(new TiXmlElement("bool"));
	if(pElem_bGainHorseBag == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_bGainHorseBag->SetAttribute("name", "bGainHorseBag");
	pElem_bGainHorseBag->SetAttribute("value", NumberToString(s.bGainHorseBag).c_str());
	pElem_bGainHorseBag->SetAttribute("comment", ToUTF8Ptr("是否领取座机礼包"));
	if(rElement.LinkEndChild(pElem_bGainHorseBag.get()) != NULL)
		pElem_bGainHorseBag.release();
	unique_ptr<TiXmlElement> pElem_dGrowBag(new TiXmlElement("UINT16"));
	if(pElem_dGrowBag == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dGrowBag->SetAttribute("name", "dGrowBag");
	pElem_dGrowBag->SetAttribute("value", NumberToString(s.dGrowBag).c_str());
	pElem_dGrowBag->SetAttribute("comment", ToUTF8Ptr("已领取成长礼包等级 从低位开始向高位 1表示领取，0表示未领取"));
	if(rElement.LinkEndChild(pElem_dGrowBag.get()) != NULL)
		pElem_dGrowBag.release();
	unique_ptr<TiXmlElement> pElem_bGainNewBag(new TiXmlElement("bool"));
	if(pElem_bGainNewBag == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_bGainNewBag->SetAttribute("name", "bGainNewBag");
	pElem_bGainNewBag->SetAttribute("value", NumberToString(s.bGainNewBag).c_str());
	pElem_bGainNewBag->SetAttribute("comment", ToUTF8Ptr("是否领取新手礼包"));
	if(rElement.LinkEndChild(pElem_bGainNewBag.get()) != NULL)
		pElem_bGainNewBag.release();
	return true;
}

#endif

} //namespace NYelloDiamondProt
