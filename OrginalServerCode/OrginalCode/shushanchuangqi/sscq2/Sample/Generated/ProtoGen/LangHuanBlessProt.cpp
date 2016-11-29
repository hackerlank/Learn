/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    LangHuanBlessProt.cpp
//  Purpose:      中午挂机活动
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "LangHuanBlessProt.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NLangHuanBlessProt
{

#ifdef PROT_USE_XML

const char* EnumValToStr(ELHBResult e)
{
	switch(e)
	{
	case eLHBResult_none:
		return "eLHBResult_none";
	case eLHBResult_empty:
		return "eLHBResult_empty";
	case eLHBResult_inCD:
		return "eLHBResult_inCD";
	case eLHBResult_hasBuff:
		return "eLHBResult_hasBuff";
	case eLHBResult_success:
		return "eLHBResult_success";
	case eLHBResult_CMapError:
		return "eLHBResult_CMapError";
	case eLHBResult_enterMapError:
		return "eLHBResult_enterMapError";
	case eLHBResult_otherError:
		return "eLHBResult_otherError";
	case eLHBResult_lowLevel:
		return "eLHBResult_lowLevel";
	case eLHBResult_notBegin:
		return "eLHBResult_notBegin";
	case eLHBResult_end:
		return "eLHBResult_end";
	case eLHBResult_wait5min:
		return "eLHBResult_wait5min";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, ELHBResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, ELHBResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eLHBResult_none", eLHBResult_none));
		mapStr2Val.insert(make_pair("eLHBResult_empty", eLHBResult_empty));
		mapStr2Val.insert(make_pair("eLHBResult_inCD", eLHBResult_inCD));
		mapStr2Val.insert(make_pair("eLHBResult_hasBuff", eLHBResult_hasBuff));
		mapStr2Val.insert(make_pair("eLHBResult_success", eLHBResult_success));
		mapStr2Val.insert(make_pair("eLHBResult_CMapError", eLHBResult_CMapError));
		mapStr2Val.insert(make_pair("eLHBResult_enterMapError", eLHBResult_enterMapError));
		mapStr2Val.insert(make_pair("eLHBResult_otherError", eLHBResult_otherError));
		mapStr2Val.insert(make_pair("eLHBResult_lowLevel", eLHBResult_lowLevel));
		mapStr2Val.insert(make_pair("eLHBResult_notBegin", eLHBResult_notBegin));
		mapStr2Val.insert(make_pair("eLHBResult_end", eLHBResult_end));
		mapStr2Val.insert(make_pair("eLHBResult_wait5min", eLHBResult_wait5min));
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

const char* EnumValToStr(ELHBState e)
{
	switch(e)
	{
	case eLHBState_none:
		return "eLHBState_none";
	case eLHBState_alarm:
		return "eLHBState_alarm";
	case eLHBState_ready:
		return "eLHBState_ready";
	case eLHBState_begin:
		return "eLHBState_begin";
	case eLHBState_end:
		return "eLHBState_end";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, ELHBState& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, ELHBState> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eLHBState_none", eLHBState_none));
		mapStr2Val.insert(make_pair("eLHBState_alarm", eLHBState_alarm));
		mapStr2Val.insert(make_pair("eLHBState_ready", eLHBState_ready));
		mapStr2Val.insert(make_pair("eLHBState_begin", eLHBState_begin));
		mapStr2Val.insert(make_pair("eLHBState_end", eLHBState_end));
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

const char* EnumValToStr(ELHBSkillType e)
{
	switch(e)
	{
	case eLHBSkillType_eNone:
		return "eLHBSkillType_eNone";
	case eLHBSkillType_eAskTaoism:
		return "eLHBSkillType_eAskTaoism";
	case eLHBSkillType_eTalkTaoism:
		return "eLHBSkillType_eTalkTaoism";
	case eLHBSkillType_eWander:
		return "eLHBSkillType_eWander";
	case eLHBSkillType_eSit:
		return "eLHBSkillType_eSit";
	case eLHBSkillType_max:
		return "eLHBSkillType_max";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, ELHBSkillType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, ELHBSkillType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eLHBSkillType_eNone", eLHBSkillType_eNone));
		mapStr2Val.insert(make_pair("eLHBSkillType_eAskTaoism", eLHBSkillType_eAskTaoism));
		mapStr2Val.insert(make_pair("eLHBSkillType_eTalkTaoism", eLHBSkillType_eTalkTaoism));
		mapStr2Val.insert(make_pair("eLHBSkillType_eWander", eLHBSkillType_eWander));
		mapStr2Val.insert(make_pair("eLHBSkillType_eSit", eLHBSkillType_eSit));
		mapStr2Val.insert(make_pair("eLHBSkillType_max", eLHBSkillType_max));
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

SLHBSkillInfo::SLHBSkillInfo() : eLHBSkillType((ELHBSkillType)0), byCD(0), wScore(0), byTimes(0) { }

SLHBSkillInfo::SLHBSkillInfo(ELHBSkillType eLHBSkillType_, UINT8 byCD_, UINT32 wScore_, UINT8 byTimes_) : eLHBSkillType(eLHBSkillType_), byCD(byCD_), wScore(wScore_), byTimes(byTimes_) { }

CInArchive& operator>>(CInArchive& src, SLHBSkillInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (UINT8&)s.eLHBSkillType;
	src >> s.byCD;
	src >> s.wScore;
	src >> s.byTimes;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SLHBSkillInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (UINT8&)s.eLHBSkillType;
	src << s.byCD;
	src << s.wScore;
	src << s.byTimes;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SLHBSkillInfo& s)
{
	if(strcmp(rElement.Value(), "SLHBSkillInfo") != 0)
	{
		LOG_CRI << "rElement is not SLHBSkillInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eLHBSkillType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "ELHBSkillType") != 0)
	{
		LOG_CRI << "pElemChild is not ELHBSkillType!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eLHBSkillType") != 0)
	{
		LOG_CRI << "Attribute: name is not eLHBSkillType!";
		return false;
	}
	const char* pszVal_eLHBSkillType = pElemChild->Attribute("value");
	if(pszVal_eLHBSkillType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!EnumStrToVal(pszVal_eLHBSkillType, s.eLHBSkillType))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byCD is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byCD") != 0)
	{
		LOG_CRI << "Attribute: name is not byCD!";
		return false;
	}
	const char* pszVal_byCD = pElemChild->Attribute("value");
	if(pszVal_byCD == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byCD, s.byCD))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wScore is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wScore") != 0)
	{
		LOG_CRI << "Attribute: name is not wScore!";
		return false;
	}
	const char* pszVal_wScore = pElemChild->Attribute("value");
	if(pszVal_wScore == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wScore, s.wScore))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byTimes is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byTimes") != 0)
	{
		LOG_CRI << "Attribute: name is not byTimes!";
		return false;
	}
	const char* pszVal_byTimes = pElemChild->Attribute("value");
	if(pszVal_byTimes == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byTimes, s.byTimes))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SLHBSkillInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SLHBSkillInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("技能信息"));
	unique_ptr<TiXmlElement> pElem_eLHBSkillType(new TiXmlElement("ELHBSkillType"));
	if(pElem_eLHBSkillType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eLHBSkillType->SetAttribute("name", "eLHBSkillType");
	const char* pszEnum_eLHBSkillType = EnumValToStr(s.eLHBSkillType);
	if(pszEnum_eLHBSkillType == NULL)
	{
		LOG_CRI << "EnumValToStr for ELHBSkillType fails!";
		return false;
	}
	pElem_eLHBSkillType->SetAttribute("value", pszEnum_eLHBSkillType);
	pElem_eLHBSkillType->SetAttribute("comment", ToUTF8Ptr("技能类型"));
	if(rElement.LinkEndChild(pElem_eLHBSkillType.get()) != NULL)
		pElem_eLHBSkillType.release();
	unique_ptr<TiXmlElement> pElem_byCD(new TiXmlElement("UINT8"));
	if(pElem_byCD == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byCD->SetAttribute("name", "byCD");
	pElem_byCD->SetAttribute("value", NumberToString(s.byCD).c_str());
	pElem_byCD->SetAttribute("comment", ToUTF8Ptr("技能CD"));
	if(rElement.LinkEndChild(pElem_byCD.get()) != NULL)
		pElem_byCD.release();
	unique_ptr<TiXmlElement> pElem_wScore(new TiXmlElement("UINT32"));
	if(pElem_wScore == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wScore->SetAttribute("name", "wScore");
	pElem_wScore->SetAttribute("value", NumberToString(s.wScore).c_str());
	pElem_wScore->SetAttribute("comment", ToUTF8Ptr("修为值"));
	if(rElement.LinkEndChild(pElem_wScore.get()) != NULL)
		pElem_wScore.release();
	unique_ptr<TiXmlElement> pElem_byTimes(new TiXmlElement("UINT8"));
	if(pElem_byTimes == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byTimes->SetAttribute("name", "byTimes");
	pElem_byTimes->SetAttribute("value", NumberToString(s.byTimes).c_str());
	pElem_byTimes->SetAttribute("comment", ToUTF8Ptr("使用次数"));
	if(rElement.LinkEndChild(pElem_byTimes.get()) != NULL)
		pElem_byTimes.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecLHBSkillInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SLHBSkillInfo s;
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

bool VectorToXML(const TVecLHBSkillInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SLHBSkillInfo"));
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

SLHBTotalInfo::SLHBTotalInfo() : byState((ELHBState)0), dwTime(0), dwXiuwei(0), dwExp(0) { }

SLHBTotalInfo::SLHBTotalInfo(ELHBState byState_, UINT32 dwTime_, UINT32 dwXiuwei_, UINT32 dwExp_, const TVecLHBSkillInfo& vecLHBSkillInfo_)
			: byState(byState_), dwTime(dwTime_), dwXiuwei(dwXiuwei_), dwExp(dwExp_), vecLHBSkillInfo(vecLHBSkillInfo_) { }

SLHBTotalInfo::SLHBTotalInfo(SLHBTotalInfo&& src) : byState(src.byState), dwTime(src.dwTime), dwXiuwei(src.dwXiuwei), dwExp(src.dwExp), vecLHBSkillInfo(move(src.vecLHBSkillInfo)) { }

SLHBTotalInfo& SLHBTotalInfo::operator=(SLHBTotalInfo&& rhs)
{
	if(this != &rhs)
	{
		this->~SLHBTotalInfo();
		new (this) SLHBTotalInfo(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SLHBTotalInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (UINT8&)s.byState;
	src >> s.dwTime;
	src >> s.dwXiuwei;
	src >> s.dwExp;
	src >> s.vecLHBSkillInfo;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SLHBTotalInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (UINT8&)s.byState;
	src << s.dwTime;
	src << s.dwXiuwei;
	src << s.dwExp;
	src << s.vecLHBSkillInfo;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SLHBTotalInfo& s)
{
	if(strcmp(rElement.Value(), "SLHBTotalInfo") != 0)
	{
		LOG_CRI << "rElement is not SLHBTotalInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byState is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "ELHBState") != 0)
	{
		LOG_CRI << "pElemChild is not ELHBState!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byState") != 0)
	{
		LOG_CRI << "Attribute: name is not byState!";
		return false;
	}
	const char* pszVal_byState = pElemChild->Attribute("value");
	if(pszVal_byState == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!EnumStrToVal(pszVal_byState, s.byState))
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
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwXiuwei is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwXiuwei") != 0)
	{
		LOG_CRI << "Attribute: name is not dwXiuwei!";
		return false;
	}
	const char* pszVal_dwXiuwei = pElemChild->Attribute("value");
	if(pszVal_dwXiuwei == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwXiuwei, s.dwXiuwei))
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
		LOG_CRI << "pElemChild for vecLHBSkillInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecLHBSkillInfo") != 0)
	{
		LOG_CRI << "pElemChild is not TVecLHBSkillInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecLHBSkillInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not vecLHBSkillInfo!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecLHBSkillInfo))
	{
		LOG_CRI << "VectorFromXML for vecLHBSkillInfo fails!";
		return false;
	}
	return true;
}

bool ToXML(const SLHBTotalInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SLHBTotalInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("总的信息"));
	unique_ptr<TiXmlElement> pElem_byState(new TiXmlElement("ELHBState"));
	if(pElem_byState == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byState->SetAttribute("name", "byState");
	const char* pszEnum_byState = EnumValToStr(s.byState);
	if(pszEnum_byState == NULL)
	{
		LOG_CRI << "EnumValToStr for ELHBState fails!";
		return false;
	}
	pElem_byState->SetAttribute("value", pszEnum_byState);
	pElem_byState->SetAttribute("comment", ToUTF8Ptr("活动状态"));
	if(rElement.LinkEndChild(pElem_byState.get()) != NULL)
		pElem_byState.release();
	unique_ptr<TiXmlElement> pElem_dwTime(new TiXmlElement("UINT32"));
	if(pElem_dwTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwTime->SetAttribute("name", "dwTime");
	pElem_dwTime->SetAttribute("value", NumberToString(s.dwTime).c_str());
	pElem_dwTime->SetAttribute("comment", ToUTF8Ptr("玩家持续时间"));
	if(rElement.LinkEndChild(pElem_dwTime.get()) != NULL)
		pElem_dwTime.release();
	unique_ptr<TiXmlElement> pElem_dwXiuwei(new TiXmlElement("UINT32"));
	if(pElem_dwXiuwei == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwXiuwei->SetAttribute("name", "dwXiuwei");
	pElem_dwXiuwei->SetAttribute("value", NumberToString(s.dwXiuwei).c_str());
	pElem_dwXiuwei->SetAttribute("comment", ToUTF8Ptr("获得的修为值"));
	if(rElement.LinkEndChild(pElem_dwXiuwei.get()) != NULL)
		pElem_dwXiuwei.release();
	unique_ptr<TiXmlElement> pElem_dwExp(new TiXmlElement("UINT32"));
	if(pElem_dwExp == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwExp->SetAttribute("name", "dwExp");
	pElem_dwExp->SetAttribute("value", NumberToString(s.dwExp).c_str());
	pElem_dwExp->SetAttribute("comment", ToUTF8Ptr("获得的经验值"));
	if(rElement.LinkEndChild(pElem_dwExp.get()) != NULL)
		pElem_dwExp.release();
	unique_ptr<TiXmlElement> pElem_vecLHBSkillInfo(new TiXmlElement("TVecLHBSkillInfo"));
	if(pElem_vecLHBSkillInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecLHBSkillInfo->SetAttribute("name", "vecLHBSkillInfo");
	if(!VectorToXML(s.vecLHBSkillInfo, *pElem_vecLHBSkillInfo))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecLHBSkillInfo->SetAttribute("comment", ToUTF8Ptr("技能使用信息"));
	if(rElement.LinkEndChild(pElem_vecLHBSkillInfo.get()) != NULL)
		pElem_vecLHBSkillInfo.release();
	return true;
}

#endif

} //namespace NLangHuanBlessProt
