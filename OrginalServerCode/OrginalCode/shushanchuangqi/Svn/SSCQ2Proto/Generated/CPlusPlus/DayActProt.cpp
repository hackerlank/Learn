/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    DayActProt.cpp
//  Purpose:      活动
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "DayActProt.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NDayActProt
{

#ifdef PROT_USE_XML

const char* EnumValToStr(EActID e)
{
	switch(e)
	{
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EActID& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EActID> mapStr2Val;
	if(mapStr2Val.empty())
	{
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

const char* EnumValToStr(EActType e)
{
	switch(e)
	{
	case eActTypeInvalid:
		return "eActTypeInvalid";
	case eActTypeWorldBoss:
		return "eActTypeWorldBoss";
	case eActTypeLangHuanBless:
		return "eActTypeLangHuanBless";
	case eActTypeGuildBattle:
		return "eActTypeGuildBattle";
	case eActTypeShushanBattle:
		return "eActTypeShushanBattle";
	case eActTypeEnergy:
		return "eActTypeEnergy";
	case eActTypeTeamReward:
		return "eActTypeTeamReward";
	case eActTypeAnswer:
		return "eActTypeAnswer";
	case eActTypeLingShan:
		return "eActTypeLingShan";
	case eActTypeNewGuildBattle:
		return "eActTypeNewGuildBattle";
	case eActTypeChest:
		return "eActTypeChest";
	case eActTypeShipReward:
		return "eActTypeShipReward";
	case eActTypeEnd:
		return "eActTypeEnd";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EActType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EActType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eActTypeInvalid", eActTypeInvalid));
		mapStr2Val.insert(make_pair("eActTypeWorldBoss", eActTypeWorldBoss));
		mapStr2Val.insert(make_pair("eActTypeLangHuanBless", eActTypeLangHuanBless));
		mapStr2Val.insert(make_pair("eActTypeGuildBattle", eActTypeGuildBattle));
		mapStr2Val.insert(make_pair("eActTypeShushanBattle", eActTypeShushanBattle));
		mapStr2Val.insert(make_pair("eActTypeEnergy", eActTypeEnergy));
		mapStr2Val.insert(make_pair("eActTypeTeamReward", eActTypeTeamReward));
		mapStr2Val.insert(make_pair("eActTypeAnswer", eActTypeAnswer));
		mapStr2Val.insert(make_pair("eActTypeLingShan", eActTypeLingShan));
		mapStr2Val.insert(make_pair("eActTypeNewGuildBattle", eActTypeNewGuildBattle));
		mapStr2Val.insert(make_pair("eActTypeChest", eActTypeChest));
		mapStr2Val.insert(make_pair("eActTypeShipReward", eActTypeShipReward));
		mapStr2Val.insert(make_pair("eActTypeEnd", eActTypeEnd));
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

const char* EnumValToStr(EDayActivityStatus e)
{
	switch(e)
	{
	case eDayActivityStatusInit:
		return "eDayActivityStatusInit";
	case eDayActivityStatusAlarm:
		return "eDayActivityStatusAlarm";
	case eDayActivityStatusReady:
		return "eDayActivityStatusReady";
	case eDayActivityStatusProcess:
		return "eDayActivityStatusProcess";
	case eDayActivityStatusEnd:
		return "eDayActivityStatusEnd";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EDayActivityStatus& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EDayActivityStatus> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eDayActivityStatusInit", eDayActivityStatusInit));
		mapStr2Val.insert(make_pair("eDayActivityStatusAlarm", eDayActivityStatusAlarm));
		mapStr2Val.insert(make_pair("eDayActivityStatusReady", eDayActivityStatusReady));
		mapStr2Val.insert(make_pair("eDayActivityStatusProcess", eDayActivityStatusProcess));
		mapStr2Val.insert(make_pair("eDayActivityStatusEnd", eDayActivityStatusEnd));
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

SActInfo::SActInfo() : dwActType(0), dwActStatus(0) { }

SActInfo::SActInfo(UINT32 dwActType_, UINT32 dwActStatus_) : dwActType(dwActType_), dwActStatus(dwActStatus_) { }

CInArchive& operator>>(CInArchive& src, SActInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.dwActType;
	src >> s.dwActStatus;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SActInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.dwActType;
	src << s.dwActStatus;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SActInfo& s)
{
	if(strcmp(rElement.Value(), "SActInfo") != 0)
	{
		LOG_CRI << "rElement is not SActInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwActType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwActType") != 0)
	{
		LOG_CRI << "Attribute: name is not dwActType!";
		return false;
	}
	const char* pszVal_dwActType = pElemChild->Attribute("value");
	if(pszVal_dwActType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwActType, s.dwActType))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwActStatus is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwActStatus") != 0)
	{
		LOG_CRI << "Attribute: name is not dwActStatus!";
		return false;
	}
	const char* pszVal_dwActStatus = pElemChild->Attribute("value");
	if(pszVal_dwActStatus == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwActStatus, s.dwActStatus))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SActInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SActInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("活动信息表"));
	unique_ptr<TiXmlElement> pElem_dwActType(new TiXmlElement("UINT32"));
	if(pElem_dwActType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwActType->SetAttribute("name", "dwActType");
	pElem_dwActType->SetAttribute("value", NumberToString(s.dwActType).c_str());
	pElem_dwActType->SetAttribute("comment", ToUTF8Ptr("活动id"));
	if(rElement.LinkEndChild(pElem_dwActType.get()) != NULL)
		pElem_dwActType.release();
	unique_ptr<TiXmlElement> pElem_dwActStatus(new TiXmlElement("UINT32"));
	if(pElem_dwActStatus == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwActStatus->SetAttribute("name", "dwActStatus");
	pElem_dwActStatus->SetAttribute("value", NumberToString(s.dwActStatus).c_str());
	pElem_dwActStatus->SetAttribute("comment", ToUTF8Ptr("活动状态"));
	if(rElement.LinkEndChild(pElem_dwActStatus.get()) != NULL)
		pElem_dwActStatus.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecActInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SActInfo s;
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

bool VectorToXML(const TVecActInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SActInfo"));
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

} //namespace NDayActProt
