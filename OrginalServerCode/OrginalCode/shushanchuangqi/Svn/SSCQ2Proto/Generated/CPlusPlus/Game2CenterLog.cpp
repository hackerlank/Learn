/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    Game2CenterLog.cpp
//  Purpose:      GameServer到CenterServer的数据中心log协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "Game2CenterLog.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NGame2CenterLog
{

#ifdef PROT_USE_XML

const char* EnumValToStr(EOpType e)
{
	switch(e)
	{
	case eOpTypeGM:
		return "eOpTypeGM";
	case eOpTypeItemChange:
		return "eOpTypeItemChange";
	case eOpTypeMoneyChange:
		return "eOpTypeMoneyChange";
	case eOpTypeEnd:
		return "eOpTypeEnd";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EOpType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EOpType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eOpTypeGM", eOpTypeGM));
		mapStr2Val.insert(make_pair("eOpTypeItemChange", eOpTypeItemChange));
		mapStr2Val.insert(make_pair("eOpTypeMoneyChange", eOpTypeMoneyChange));
		mapStr2Val.insert(make_pair("eOpTypeEnd", eOpTypeEnd));
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

SUserMoneyChange::SUserMoneyChange() : eMoneyType((NProtoCommon::EMoneyType)0), dwValue(0), wFromTo(0) { }

SUserMoneyChange::SUserMoneyChange(NProtoCommon::EMoneyType eMoneyType_, INT32 dwValue_, UINT16 wFromTo_) : eMoneyType(eMoneyType_), dwValue(dwValue_), wFromTo(wFromTo_) { }

CInArchive& operator>>(CInArchive& src, SUserMoneyChange& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (UINT8&)s.eMoneyType;
	src >> s.dwValue;
	src >> s.wFromTo;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SUserMoneyChange& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (UINT8&)s.eMoneyType;
	src << s.dwValue;
	src << s.wFromTo;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SUserMoneyChange& s)
{
	if(strcmp(rElement.Value(), "SUserMoneyChange") != 0)
	{
		LOG_CRI << "rElement is not SUserMoneyChange!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eMoneyType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "ProtoCommon::EMoneyType") != 0)
	{
		LOG_CRI << "pElemChild is not ProtoCommon::EMoneyType!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eMoneyType") != 0)
	{
		LOG_CRI << "Attribute: name is not eMoneyType!";
		return false;
	}
	const char* pszVal_eMoneyType = pElemChild->Attribute("value");
	if(pszVal_eMoneyType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!NProtoCommon::EnumStrToVal(pszVal_eMoneyType, s.eMoneyType))
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
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wFromTo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wFromTo") != 0)
	{
		LOG_CRI << "Attribute: name is not wFromTo!";
		return false;
	}
	const char* pszVal_wFromTo = pElemChild->Attribute("value");
	if(pszVal_wFromTo == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wFromTo, s.wFromTo))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SUserMoneyChange& s, TiXmlElement& rElement)
{
	rElement.SetValue("SUserMoneyChange");
	rElement.SetAttribute("type", ToUTF8Ptr("帐号金钱变化信息"));
	unique_ptr<TiXmlElement> pElem_eMoneyType(new TiXmlElement("ProtoCommon::EMoneyType"));
	if(pElem_eMoneyType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eMoneyType->SetAttribute("name", "eMoneyType");
	const char* pszEnum_eMoneyType = NProtoCommon::EnumValToStr(s.eMoneyType);
	if(pszEnum_eMoneyType == NULL)
	{
		LOG_CRI << "EnumValToStr for eMoneyType fails!";
		return false;
	}
	pElem_eMoneyType->SetAttribute("value", pszEnum_eMoneyType);
	pElem_eMoneyType->SetAttribute("comment", ToUTF8Ptr("货币类型"));
	if(rElement.LinkEndChild(pElem_eMoneyType.get()) != NULL)
		pElem_eMoneyType.release();
	unique_ptr<TiXmlElement> pElem_dwValue(new TiXmlElement("INT32"));
	if(pElem_dwValue == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwValue->SetAttribute("name", "dwValue");
	pElem_dwValue->SetAttribute("value", NumberToString(s.dwValue).c_str());
	pElem_dwValue->SetAttribute("comment", ToUTF8Ptr("值"));
	if(rElement.LinkEndChild(pElem_dwValue.get()) != NULL)
		pElem_dwValue.release();
	unique_ptr<TiXmlElement> pElem_wFromTo(new TiXmlElement("UINT16"));
	if(pElem_wFromTo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wFromTo->SetAttribute("name", "wFromTo");
	pElem_wFromTo->SetAttribute("value", NumberToString(s.wFromTo).c_str());
	pElem_wFromTo->SetAttribute("comment", ToUTF8Ptr("货币来源or消耗类型(dwValue>0来源 dwValue<0消耗)"));
	if(rElement.LinkEndChild(pElem_wFromTo.get()) != NULL)
		pElem_wFromTo.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecUserMoneyChange& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SUserMoneyChange s;
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

bool VectorToXML(const TVecUserMoneyChange& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SUserMoneyChange"));
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

SUserItemChange::SUserItemChange() : wItemID(0), dwCount(0), dwPrice(0), wFromTo(0) { }

SUserItemChange::SUserItemChange(UINT16 wItemID_, INT32 dwCount_, float dwPrice_, UINT16 wFromTo_) : wItemID(wItemID_), dwCount(dwCount_), dwPrice(dwPrice_), wFromTo(wFromTo_) { }

CInArchive& operator>>(CInArchive& src, SUserItemChange& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.wItemID;
	src >> s.dwCount;
	src >> s.dwPrice;
	src >> s.wFromTo;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SUserItemChange& s)
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
	src << s.dwPrice;
	src << s.wFromTo;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SUserItemChange& s)
{
	if(strcmp(rElement.Value(), "SUserItemChange") != 0)
	{
		LOG_CRI << "rElement is not SUserItemChange!";
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
	if(strcmp(pElemChild->Value(), "INT32") != 0)
	{
		LOG_CRI << "pElemChild is not INT32!";
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
		LOG_CRI << "pElemChild for dwPrice is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "float") != 0)
	{
		LOG_CRI << "pElemChild is not float!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwPrice") != 0)
	{
		LOG_CRI << "Attribute: name is not dwPrice!";
		return false;
	}
	const char* pszVal_dwPrice = pElemChild->Attribute("value");
	if(pszVal_dwPrice == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwPrice, s.dwPrice))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wFromTo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wFromTo") != 0)
	{
		LOG_CRI << "Attribute: name is not wFromTo!";
		return false;
	}
	const char* pszVal_wFromTo = pElemChild->Attribute("value");
	if(pszVal_wFromTo == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wFromTo, s.wFromTo))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SUserItemChange& s, TiXmlElement& rElement)
{
	rElement.SetValue("SUserItemChange");
	rElement.SetAttribute("type", ToUTF8Ptr("帐号道具变化信息"));
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
	unique_ptr<TiXmlElement> pElem_dwCount(new TiXmlElement("INT32"));
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
	unique_ptr<TiXmlElement> pElem_dwPrice(new TiXmlElement("float"));
	if(pElem_dwPrice == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwPrice->SetAttribute("name", "dwPrice");
	pElem_dwPrice->SetAttribute("value", NumberToString(s.dwPrice).c_str());
	pElem_dwPrice->SetAttribute("comment", ToUTF8Ptr("价格"));
	if(rElement.LinkEndChild(pElem_dwPrice.get()) != NULL)
		pElem_dwPrice.release();
	unique_ptr<TiXmlElement> pElem_wFromTo(new TiXmlElement("UINT16"));
	if(pElem_wFromTo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wFromTo->SetAttribute("name", "wFromTo");
	pElem_wFromTo->SetAttribute("value", NumberToString(s.wFromTo).c_str());
	pElem_wFromTo->SetAttribute("comment", ToUTF8Ptr("道具来源or消耗类型(dwCount>0来源 dwCount<0消耗)"));
	if(rElement.LinkEndChild(pElem_wFromTo.get()) != NULL)
		pElem_wFromTo.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecUserItemChange& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SUserItemChange s;
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

bool VectorToXML(const TVecUserItemChange& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SUserItemChange"));
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

} //namespace NGame2CenterLog
