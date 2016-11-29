/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    EquipTrumpProt.cpp
//  Purpose:      道具相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "EquipTrumpProt.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NEquipTrumpProt
{

#ifdef PROT_USE_XML

const char* EnumValToStr(EEquipTrumpResult e)
{
	switch(e)
	{
	case eETRSuccess:
		return "eETRSuccess";
	case eETRFailed:
		return "eETRFailed";
	case eETRNotExist:
		return "eETRNotExist";
	case eETRInOthers:
		return "eETRInOthers";
	case eETRSlotFull:
		return "eETRSlotFull";
	case eETRSlotLock:
		return "eETRSlotLock";
	case eETRSlotConflict:
		return "eETRSlotConflict";
	case eETRMax:
		return "eETRMax";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EEquipTrumpResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EEquipTrumpResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eETRSuccess", eETRSuccess));
		mapStr2Val.insert(make_pair("eETRFailed", eETRFailed));
		mapStr2Val.insert(make_pair("eETRNotExist", eETRNotExist));
		mapStr2Val.insert(make_pair("eETRInOthers", eETRInOthers));
		mapStr2Val.insert(make_pair("eETRSlotFull", eETRSlotFull));
		mapStr2Val.insert(make_pair("eETRSlotLock", eETRSlotLock));
		mapStr2Val.insert(make_pair("eETRSlotConflict", eETRSlotConflict));
		mapStr2Val.insert(make_pair("eETRMax", eETRMax));
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

const char* EnumValToStr(EEquipTrumpIntensifyResult e)
{
	switch(e)
	{
	case eETIRSuccess:
		return "eETIRSuccess";
	case eETIRFailed:
		return "eETIRFailed";
	case eETIRCrit:
		return "eETIRCrit";
	case eETIRMaxErr:
		return "eETIRMaxErr";
	case eETIRSilverErr:
		return "eETIRSilverErr";
	case eETIRItemErr:
		return "eETIRItemErr";
	case eETIRCFGErr:
		return "eETIRCFGErr";
	case eETIRTypeErr:
		return "eETIRTypeErr";
	case eETIRRandomFailErr:
		return "eETIRRandomFailErr";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EEquipTrumpIntensifyResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EEquipTrumpIntensifyResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eETIRSuccess", eETIRSuccess));
		mapStr2Val.insert(make_pair("eETIRFailed", eETIRFailed));
		mapStr2Val.insert(make_pair("eETIRCrit", eETIRCrit));
		mapStr2Val.insert(make_pair("eETIRMaxErr", eETIRMaxErr));
		mapStr2Val.insert(make_pair("eETIRSilverErr", eETIRSilverErr));
		mapStr2Val.insert(make_pair("eETIRItemErr", eETIRItemErr));
		mapStr2Val.insert(make_pair("eETIRCFGErr", eETIRCFGErr));
		mapStr2Val.insert(make_pair("eETIRTypeErr", eETIRTypeErr));
		mapStr2Val.insert(make_pair("eETIRRandomFailErr", eETIRRandomFailErr));
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

const char* EnumValToStr(EEquipTrumpMergeResult e)
{
	switch(e)
	{
	case eETMRSuccess:
		return "eETMRSuccess";
	case eETMRFailed:
		return "eETMRFailed";
	case eETMRLackOfMaterial:
		return "eETMRLackOfMaterial";
	case eETMRLackOfSilver:
		return "eETMRLackOfSilver";
	case eETMRPackFull:
		return "eETMRPackFull";
	case eETMRMax:
		return "eETMRMax";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EEquipTrumpMergeResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EEquipTrumpMergeResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eETMRSuccess", eETMRSuccess));
		mapStr2Val.insert(make_pair("eETMRFailed", eETMRFailed));
		mapStr2Val.insert(make_pair("eETMRLackOfMaterial", eETMRLackOfMaterial));
		mapStr2Val.insert(make_pair("eETMRLackOfSilver", eETMRLackOfSilver));
		mapStr2Val.insert(make_pair("eETMRPackFull", eETMRPackFull));
		mapStr2Val.insert(make_pair("eETMRMax", eETMRMax));
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

const char* EnumValToStr(EEquipTrumpBreakResult e)
{
	switch(e)
	{
	case eETBRSuccess:
		return "eETBRSuccess";
	case eETBRFailed:
		return "eETBRFailed";
	case eETBRPackFull:
		return "eETBRPackFull";
	case eETBREquiped:
		return "eETBREquiped";
	case eETBRMax:
		return "eETBRMax";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EEquipTrumpBreakResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EEquipTrumpBreakResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eETBRSuccess", eETBRSuccess));
		mapStr2Val.insert(make_pair("eETBRFailed", eETBRFailed));
		mapStr2Val.insert(make_pair("eETBRPackFull", eETBRPackFull));
		mapStr2Val.insert(make_pair("eETBREquiped", eETBREquiped));
		mapStr2Val.insert(make_pair("eETBRMax", eETBRMax));
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

const char* EnumValToStr(EEquipTrumpShuffleResult e)
{
	switch(e)
	{
	case eETSRSuccess:
		return "eETSRSuccess";
	case eETSRFailed:
		return "eETSRFailed";
	case eETSRLevelErr:
		return "eETSRLevelErr";
	case eETSRSilverErr:
		return "eETSRSilverErr";
	case eETSRMaterialErr:
		return "eETSRMaterialErr";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EEquipTrumpShuffleResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EEquipTrumpShuffleResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eETSRSuccess", eETSRSuccess));
		mapStr2Val.insert(make_pair("eETSRFailed", eETSRFailed));
		mapStr2Val.insert(make_pair("eETSRLevelErr", eETSRLevelErr));
		mapStr2Val.insert(make_pair("eETSRSilverErr", eETSRSilverErr));
		mapStr2Val.insert(make_pair("eETSRMaterialErr", eETSRMaterialErr));
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

const char* EnumValToStr(EEquipTrumpType e)
{
	switch(e)
	{
	case eETTNone:
		return "eETTNone";
	case eETTInnate:
		return "eETTInnate";
	case eETTPassive:
		return "eETTPassive";
	case eETTHalo:
		return "eETTHalo";
	case eETTTransform:
		return "eETTTransform";
	case eETTEnd:
		return "eETTEnd";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EEquipTrumpType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EEquipTrumpType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eETTNone", eETTNone));
		mapStr2Val.insert(make_pair("eETTInnate", eETTInnate));
		mapStr2Val.insert(make_pair("eETTPassive", eETTPassive));
		mapStr2Val.insert(make_pair("eETTHalo", eETTHalo));
		mapStr2Val.insert(make_pair("eETTTransform", eETTTransform));
		mapStr2Val.insert(make_pair("eETTEnd", eETTEnd));
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

const char* EnumValToStr(EEquipTrumpSlotType e)
{
	switch(e)
	{
	case eETSTNone:
		return "eETSTNone";
	case eETSTInnate:
		return "eETSTInnate";
	case eETSTPassive:
		return "eETSTPassive";
	case eETSTHalo:
		return "eETSTHalo";
	case eETSTTransform:
		return "eETSTTransform";
	case eETSTMax:
		return "eETSTMax";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EEquipTrumpSlotType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EEquipTrumpSlotType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eETSTNone", eETSTNone));
		mapStr2Val.insert(make_pair("eETSTInnate", eETSTInnate));
		mapStr2Val.insert(make_pair("eETSTPassive", eETSTPassive));
		mapStr2Val.insert(make_pair("eETSTHalo", eETSTHalo));
		mapStr2Val.insert(make_pair("eETSTTransform", eETSTTransform));
		mapStr2Val.insert(make_pair("eETSTMax", eETSTMax));
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

const char* EnumValToStr(ETIntensifyType e)
{
	switch(e)
	{
	case eETIntensify_None:
		return "eETIntensify_None";
	case eETIntensify_NormalGold:
		return "eETIntensify_NormalGold";
	case eETIntensify_GodGold:
		return "eETIntensify_GodGold";
	case eETIntensify_MAX:
		return "eETIntensify_MAX";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, ETIntensifyType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, ETIntensifyType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eETIntensify_None", eETIntensify_None));
		mapStr2Val.insert(make_pair("eETIntensify_NormalGold", eETIntensify_NormalGold));
		mapStr2Val.insert(make_pair("eETIntensify_GodGold", eETIntensify_GodGold));
		mapStr2Val.insert(make_pair("eETIntensify_MAX", eETIntensify_MAX));
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

SMaxShuffleInfo::SMaxShuffleInfo() : dwType(0), dwValue(0) { }

SMaxShuffleInfo::SMaxShuffleInfo(UINT32 dwType_, UINT32 dwValue_) : dwType(dwType_), dwValue(dwValue_) { }

CInArchive& operator>>(CInArchive& src, SMaxShuffleInfo& s)
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

COutArchive& operator<<(COutArchive& src, const SMaxShuffleInfo& s)
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

bool FromXML(TiXmlElement& rElement, SMaxShuffleInfo& s)
{
	if(strcmp(rElement.Value(), "SMaxShuffleInfo") != 0)
	{
		LOG_CRI << "rElement is not SMaxShuffleInfo!";
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

bool ToXML(const SMaxShuffleInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SMaxShuffleInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("最大洗练属性"));
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

bool VectorFromXML(TiXmlElement& rElement, TVecMaxShuffleInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SMaxShuffleInfo s;
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

bool VectorToXML(const TVecMaxShuffleInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SMaxShuffleInfo"));
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

SXiLianProb::SXiLianProb() : dwMinRate(0), dwMaxRate(0), dwRateValue(0) { }

SXiLianProb::SXiLianProb(UINT32 dwMinRate_, UINT32 dwMaxRate_, UINT32 dwRateValue_) : dwMinRate(dwMinRate_), dwMaxRate(dwMaxRate_), dwRateValue(dwRateValue_) { }

CInArchive& operator>>(CInArchive& src, SXiLianProb& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.dwMinRate;
	src >> s.dwMaxRate;
	src >> s.dwRateValue;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SXiLianProb& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.dwMinRate;
	src << s.dwMaxRate;
	src << s.dwRateValue;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SXiLianProb& s)
{
	if(strcmp(rElement.Value(), "SXiLianProb") != 0)
	{
		LOG_CRI << "rElement is not SXiLianProb!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwMinRate is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwMinRate") != 0)
	{
		LOG_CRI << "Attribute: name is not dwMinRate!";
		return false;
	}
	const char* pszVal_dwMinRate = pElemChild->Attribute("value");
	if(pszVal_dwMinRate == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwMinRate, s.dwMinRate))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwMaxRate is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwMaxRate") != 0)
	{
		LOG_CRI << "Attribute: name is not dwMaxRate!";
		return false;
	}
	const char* pszVal_dwMaxRate = pElemChild->Attribute("value");
	if(pszVal_dwMaxRate == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwMaxRate, s.dwMaxRate))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwRateValue is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwRateValue") != 0)
	{
		LOG_CRI << "Attribute: name is not dwRateValue!";
		return false;
	}
	const char* pszVal_dwRateValue = pElemChild->Attribute("value");
	if(pszVal_dwRateValue == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwRateValue, s.dwRateValue))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SXiLianProb& s, TiXmlElement& rElement)
{
	rElement.SetValue("SXiLianProb");
	rElement.SetAttribute("type", ToUTF8Ptr("洗练区间属性"));
	unique_ptr<TiXmlElement> pElem_dwMinRate(new TiXmlElement("UINT32"));
	if(pElem_dwMinRate == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwMinRate->SetAttribute("name", "dwMinRate");
	pElem_dwMinRate->SetAttribute("value", NumberToString(s.dwMinRate).c_str());
	pElem_dwMinRate->SetAttribute("comment", ToUTF8Ptr("洗炼最小概率"));
	if(rElement.LinkEndChild(pElem_dwMinRate.get()) != NULL)
		pElem_dwMinRate.release();
	unique_ptr<TiXmlElement> pElem_dwMaxRate(new TiXmlElement("UINT32"));
	if(pElem_dwMaxRate == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwMaxRate->SetAttribute("name", "dwMaxRate");
	pElem_dwMaxRate->SetAttribute("value", NumberToString(s.dwMaxRate).c_str());
	pElem_dwMaxRate->SetAttribute("comment", ToUTF8Ptr("洗炼最大概率"));
	if(rElement.LinkEndChild(pElem_dwMaxRate.get()) != NULL)
		pElem_dwMaxRate.release();
	unique_ptr<TiXmlElement> pElem_dwRateValue(new TiXmlElement("UINT32"));
	if(pElem_dwRateValue == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwRateValue->SetAttribute("name", "dwRateValue");
	pElem_dwRateValue->SetAttribute("value", NumberToString(s.dwRateValue).c_str());
	pElem_dwRateValue->SetAttribute("comment", ToUTF8Ptr("洗炼权值空间"));
	if(rElement.LinkEndChild(pElem_dwRateValue.get()) != NULL)
		pElem_dwRateValue.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecXiLianProb& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SXiLianProb s;
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

bool VectorToXML(const TVecXiLianProb& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SXiLianProb"));
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

} //namespace NEquipTrumpProt
