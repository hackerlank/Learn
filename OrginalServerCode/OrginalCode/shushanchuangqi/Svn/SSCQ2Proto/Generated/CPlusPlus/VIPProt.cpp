/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    VIPProt.cpp
//  Purpose:      VIP特权相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "VIPProt.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NVIPProt
{

#ifdef PROT_USE_XML

const char* EnumValToStr(EVIPResult e)
{
	switch(e)
	{
	case eVIP_Succeed:
		return "eVIP_Succeed";
	case eVIP_LackMoney:
		return "eVIP_LackMoney";
	case eVIP_HasGetAward:
		return "eVIP_HasGetAward";
	case eVIP_Expired:
		return "eVIP_Expired";
	case eVIP_UnFriend:
		return "eVIP_UnFriend";
	case eVIP_LevelErr:
		return "eVIP_LevelErr";
	case eVIP_OtherErr:
		return "eVIP_OtherErr";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EVIPResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EVIPResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eVIP_Succeed", eVIP_Succeed));
		mapStr2Val.insert(make_pair("eVIP_LackMoney", eVIP_LackMoney));
		mapStr2Val.insert(make_pair("eVIP_HasGetAward", eVIP_HasGetAward));
		mapStr2Val.insert(make_pair("eVIP_Expired", eVIP_Expired));
		mapStr2Val.insert(make_pair("eVIP_UnFriend", eVIP_UnFriend));
		mapStr2Val.insert(make_pair("eVIP_LevelErr", eVIP_LevelErr));
		mapStr2Val.insert(make_pair("eVIP_OtherErr", eVIP_OtherErr));
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

SVIPData::SVIPData() : dwMonthCardEndTime(0), dwDayPack(0), dwLvlAward(0) { }

SVIPData::SVIPData(UINT32 dwMonthCardEndTime_, UINT32 dwDayPack_, UINT32 dwLvlAward_) : dwMonthCardEndTime(dwMonthCardEndTime_), dwDayPack(dwDayPack_), dwLvlAward(dwLvlAward_) { }

CInArchive& operator>>(CInArchive& src, SVIPData& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.dwMonthCardEndTime;
	src >> s.dwDayPack;
	src >> s.dwLvlAward;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SVIPData& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.dwMonthCardEndTime;
	src << s.dwDayPack;
	src << s.dwLvlAward;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SVIPData& s)
{
	if(strcmp(rElement.Value(), "SVIPData") != 0)
	{
		LOG_CRI << "rElement is not SVIPData!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwMonthCardEndTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwMonthCardEndTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwMonthCardEndTime!";
		return false;
	}
	const char* pszVal_dwMonthCardEndTime = pElemChild->Attribute("value");
	if(pszVal_dwMonthCardEndTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwMonthCardEndTime, s.dwMonthCardEndTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwDayPack is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwDayPack") != 0)
	{
		LOG_CRI << "Attribute: name is not dwDayPack!";
		return false;
	}
	const char* pszVal_dwDayPack = pElemChild->Attribute("value");
	if(pszVal_dwDayPack == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwDayPack, s.dwDayPack))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwLvlAward is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwLvlAward") != 0)
	{
		LOG_CRI << "Attribute: name is not dwLvlAward!";
		return false;
	}
	const char* pszVal_dwLvlAward = pElemChild->Attribute("value");
	if(pszVal_dwLvlAward == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwLvlAward, s.dwLvlAward))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SVIPData& s, TiXmlElement& rElement)
{
	rElement.SetValue("SVIPData");
	rElement.SetAttribute("type", ToUTF8Ptr("开启VIP特权数据结构"));
	unique_ptr<TiXmlElement> pElem_dwMonthCardEndTime(new TiXmlElement("UINT32"));
	if(pElem_dwMonthCardEndTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwMonthCardEndTime->SetAttribute("name", "dwMonthCardEndTime");
	pElem_dwMonthCardEndTime->SetAttribute("value", NumberToString(s.dwMonthCardEndTime).c_str());
	pElem_dwMonthCardEndTime->SetAttribute("comment", ToUTF8Ptr("月卡结束时间"));
	if(rElement.LinkEndChild(pElem_dwMonthCardEndTime.get()) != NULL)
		pElem_dwMonthCardEndTime.release();
	unique_ptr<TiXmlElement> pElem_dwDayPack(new TiXmlElement("UINT32"));
	if(pElem_dwDayPack == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwDayPack->SetAttribute("name", "dwDayPack");
	pElem_dwDayPack->SetAttribute("value", NumberToString(s.dwDayPack).c_str());
	pElem_dwDayPack->SetAttribute("comment", ToUTF8Ptr("VIP特权每日礼包领取状态"));
	if(rElement.LinkEndChild(pElem_dwDayPack.get()) != NULL)
		pElem_dwDayPack.release();
	unique_ptr<TiXmlElement> pElem_dwLvlAward(new TiXmlElement("UINT32"));
	if(pElem_dwLvlAward == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwLvlAward->SetAttribute("name", "dwLvlAward");
	pElem_dwLvlAward->SetAttribute("value", NumberToString(s.dwLvlAward).c_str());
	pElem_dwLvlAward->SetAttribute("comment", ToUTF8Ptr("VIP特权等级奖励领取状态"));
	if(rElement.LinkEndChild(pElem_dwLvlAward.get()) != NULL)
		pElem_dwLvlAward.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecVIPData& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SVIPData s;
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

bool VectorToXML(const TVecVIPData& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SVIPData"));
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

} //namespace NVIPProt
