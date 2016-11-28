/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    FeedBackProt.cpp
//  Purpose:      消费回馈
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "FeedBackProt.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NFeedBackProt
{

#ifdef PROT_USE_XML

const char* EnumValToStr(EFeedBackRet e)
{
	switch(e)
	{
	case eFeedBackRet_Sucess:
		return "eFeedBackRet_Sucess";
	case eFeedBackRet_MoneyLimit:
		return "eFeedBackRet_MoneyLimit";
	case eFeedBackRet_TakeCntLimit:
		return "eFeedBackRet_TakeCntLimit";
	case eFeedBackRet_IDError:
		return "eFeedBackRet_IDError";
	case eFeedBackRet_TimeError:
		return "eFeedBackRet_TimeError";
	case eFeedBackRet_CFGError:
		return "eFeedBackRet_CFGError";
	case eFeedBackRet_ParamError:
		return "eFeedBackRet_ParamError";
	case eFeedBackRet_PackError:
		return "eFeedBackRet_PackError";
	case eFeedBackRet_ActiveTimeError:
		return "eFeedBackRet_ActiveTimeError";
	case eFeedBackRet_PrizeCntError:
		return "eFeedBackRet_PrizeCntError";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EFeedBackRet& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EFeedBackRet> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eFeedBackRet_Sucess", eFeedBackRet_Sucess));
		mapStr2Val.insert(make_pair("eFeedBackRet_MoneyLimit", eFeedBackRet_MoneyLimit));
		mapStr2Val.insert(make_pair("eFeedBackRet_TakeCntLimit", eFeedBackRet_TakeCntLimit));
		mapStr2Val.insert(make_pair("eFeedBackRet_IDError", eFeedBackRet_IDError));
		mapStr2Val.insert(make_pair("eFeedBackRet_TimeError", eFeedBackRet_TimeError));
		mapStr2Val.insert(make_pair("eFeedBackRet_CFGError", eFeedBackRet_CFGError));
		mapStr2Val.insert(make_pair("eFeedBackRet_ParamError", eFeedBackRet_ParamError));
		mapStr2Val.insert(make_pair("eFeedBackRet_PackError", eFeedBackRet_PackError));
		mapStr2Val.insert(make_pair("eFeedBackRet_ActiveTimeError", eFeedBackRet_ActiveTimeError));
		mapStr2Val.insert(make_pair("eFeedBackRet_PrizeCntError", eFeedBackRet_PrizeCntError));
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

const char* EnumValToStr(EFeedBackActType e)
{
	switch(e)
	{
	case eFeedBackActType_Invalid:
		return "eFeedBackActType_Invalid";
	case eFeedBackActType_EquipTrump:
		return "eFeedBackActType_EquipTrump";
	case eFeedBackActType_Stone:
		return "eFeedBackActType_Stone";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EFeedBackActType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EFeedBackActType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eFeedBackActType_Invalid", eFeedBackActType_Invalid));
		mapStr2Val.insert(make_pair("eFeedBackActType_EquipTrump", eFeedBackActType_EquipTrump));
		mapStr2Val.insert(make_pair("eFeedBackActType_Stone", eFeedBackActType_Stone));
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

SFeedBackInfo::SFeedBackInfo() : dwActID(0), dwBeginTime(0), dwEndTime(0), dwTakePrizeMax(0), dwTakePrizedCnt(0) { }

SFeedBackInfo::SFeedBackInfo(UINT32 dwActID_, UINT32 dwBeginTime_, UINT32 dwEndTime_, UINT32 dwTakePrizeMax_, UINT32 dwTakePrizedCnt_)
			: dwActID(dwActID_), dwBeginTime(dwBeginTime_), dwEndTime(dwEndTime_), dwTakePrizeMax(dwTakePrizeMax_), dwTakePrizedCnt(dwTakePrizedCnt_) { }

CInArchive& operator>>(CInArchive& src, SFeedBackInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.dwActID;
	src >> s.dwBeginTime;
	src >> s.dwEndTime;
	src >> s.dwTakePrizeMax;
	src >> s.dwTakePrizedCnt;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SFeedBackInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.dwActID;
	src << s.dwBeginTime;
	src << s.dwEndTime;
	src << s.dwTakePrizeMax;
	src << s.dwTakePrizedCnt;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SFeedBackInfo& s)
{
	if(strcmp(rElement.Value(), "SFeedBackInfo") != 0)
	{
		LOG_CRI << "rElement is not SFeedBackInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwActID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwActID") != 0)
	{
		LOG_CRI << "Attribute: name is not dwActID!";
		return false;
	}
	const char* pszVal_dwActID = pElemChild->Attribute("value");
	if(pszVal_dwActID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwActID, s.dwActID))
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
		LOG_CRI << "pElemChild for dwTakePrizeMax is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwTakePrizeMax") != 0)
	{
		LOG_CRI << "Attribute: name is not dwTakePrizeMax!";
		return false;
	}
	const char* pszVal_dwTakePrizeMax = pElemChild->Attribute("value");
	if(pszVal_dwTakePrizeMax == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwTakePrizeMax, s.dwTakePrizeMax))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwTakePrizedCnt is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwTakePrizedCnt") != 0)
	{
		LOG_CRI << "Attribute: name is not dwTakePrizedCnt!";
		return false;
	}
	const char* pszVal_dwTakePrizedCnt = pElemChild->Attribute("value");
	if(pszVal_dwTakePrizedCnt == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwTakePrizedCnt, s.dwTakePrizedCnt))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SFeedBackInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SFeedBackInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("回馈信息"));
	unique_ptr<TiXmlElement> pElem_dwActID(new TiXmlElement("UINT32"));
	if(pElem_dwActID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwActID->SetAttribute("name", "dwActID");
	pElem_dwActID->SetAttribute("value", NumberToString(s.dwActID).c_str());
	pElem_dwActID->SetAttribute("comment", ToUTF8Ptr("活动id"));
	if(rElement.LinkEndChild(pElem_dwActID.get()) != NULL)
		pElem_dwActID.release();
	unique_ptr<TiXmlElement> pElem_dwBeginTime(new TiXmlElement("UINT32"));
	if(pElem_dwBeginTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwBeginTime->SetAttribute("name", "dwBeginTime");
	pElem_dwBeginTime->SetAttribute("value", NumberToString(s.dwBeginTime).c_str());
	pElem_dwBeginTime->SetAttribute("comment", ToUTF8Ptr("开始时间"));
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
	pElem_dwEndTime->SetAttribute("comment", ToUTF8Ptr("结束时间"));
	if(rElement.LinkEndChild(pElem_dwEndTime.get()) != NULL)
		pElem_dwEndTime.release();
	unique_ptr<TiXmlElement> pElem_dwTakePrizeMax(new TiXmlElement("UINT32"));
	if(pElem_dwTakePrizeMax == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwTakePrizeMax->SetAttribute("name", "dwTakePrizeMax");
	pElem_dwTakePrizeMax->SetAttribute("value", NumberToString(s.dwTakePrizeMax).c_str());
	pElem_dwTakePrizeMax->SetAttribute("comment", ToUTF8Ptr("可领奖次数"));
	if(rElement.LinkEndChild(pElem_dwTakePrizeMax.get()) != NULL)
		pElem_dwTakePrizeMax.release();
	unique_ptr<TiXmlElement> pElem_dwTakePrizedCnt(new TiXmlElement("UINT32"));
	if(pElem_dwTakePrizedCnt == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwTakePrizedCnt->SetAttribute("name", "dwTakePrizedCnt");
	pElem_dwTakePrizedCnt->SetAttribute("value", NumberToString(s.dwTakePrizedCnt).c_str());
	pElem_dwTakePrizedCnt->SetAttribute("comment", ToUTF8Ptr("已领奖次数"));
	if(rElement.LinkEndChild(pElem_dwTakePrizedCnt.get()) != NULL)
		pElem_dwTakePrizedCnt.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecFeedBackInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SFeedBackInfo s;
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

bool VectorToXML(const TVecFeedBackInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SFeedBackInfo"));
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

SBuyDiscountInfo::SBuyDiscountInfo() : eType((EFeedBackActType)0), dwBuyCount(0) { }

SBuyDiscountInfo::SBuyDiscountInfo(EFeedBackActType eType_, UINT32 dwBuyCount_) : eType(eType_), dwBuyCount(dwBuyCount_) { }

CInArchive& operator>>(CInArchive& src, SBuyDiscountInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (UINT8&)s.eType;
	src >> s.dwBuyCount;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SBuyDiscountInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (UINT8&)s.eType;
	src << s.dwBuyCount;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SBuyDiscountInfo& s)
{
	if(strcmp(rElement.Value(), "SBuyDiscountInfo") != 0)
	{
		LOG_CRI << "rElement is not SBuyDiscountInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "EFeedBackActType") != 0)
	{
		LOG_CRI << "pElemChild is not EFeedBackActType!";
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
		LOG_CRI << "pElemChild for dwBuyCount is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwBuyCount") != 0)
	{
		LOG_CRI << "Attribute: name is not dwBuyCount!";
		return false;
	}
	const char* pszVal_dwBuyCount = pElemChild->Attribute("value");
	if(pszVal_dwBuyCount == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwBuyCount, s.dwBuyCount))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SBuyDiscountInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SBuyDiscountInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("折扣限购信息"));
	unique_ptr<TiXmlElement> pElem_eType(new TiXmlElement("EFeedBackActType"));
	if(pElem_eType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eType->SetAttribute("name", "eType");
	const char* pszEnum_eType = EnumValToStr(s.eType);
	if(pszEnum_eType == NULL)
	{
		LOG_CRI << "EnumValToStr for EFeedBackActType fails!";
		return false;
	}
	pElem_eType->SetAttribute("value", pszEnum_eType);
	pElem_eType->SetAttribute("comment", ToUTF8Ptr("消费回馈类型"));
	if(rElement.LinkEndChild(pElem_eType.get()) != NULL)
		pElem_eType.release();
	unique_ptr<TiXmlElement> pElem_dwBuyCount(new TiXmlElement("UINT32"));
	if(pElem_dwBuyCount == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwBuyCount->SetAttribute("name", "dwBuyCount");
	pElem_dwBuyCount->SetAttribute("value", NumberToString(s.dwBuyCount).c_str());
	pElem_dwBuyCount->SetAttribute("comment", ToUTF8Ptr("已领购买次数"));
	if(rElement.LinkEndChild(pElem_dwBuyCount.get()) != NULL)
		pElem_dwBuyCount.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecSBuyDiscountInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SBuyDiscountInfo s;
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

bool VectorToXML(const TVecSBuyDiscountInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SBuyDiscountInfo"));
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

} //namespace NFeedBackProt
