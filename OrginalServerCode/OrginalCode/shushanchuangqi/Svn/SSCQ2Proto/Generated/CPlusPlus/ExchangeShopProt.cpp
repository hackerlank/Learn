/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    ExchangeShopProt.cpp
//  Purpose:      兑换商店
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "ExchangeShopProt.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NExchangeShopProt
{

#ifdef PROT_USE_XML

const char* EnumValToStr(EExchangeShop e)
{
	switch(e)
	{
	case eExchangeShop_Sucess:
		return "eExchangeShop_Sucess";
	case eExchangeShop_CfgLimit:
		return "eExchangeShop_CfgLimit";
	case eExchangeShop_MoneyLimit:
		return "eExchangeShop_MoneyLimit";
	case eExchangeShop_CondLimit:
		return "eExchangeShop_CondLimit";
	case eExchangeShop_CountLimit:
		return "eExchangeShop_CountLimit";
	case eExchangeShop_ErrorItemID:
		return "eExchangeShop_ErrorItemID";
	case eExchangeShop_ErrorPack:
		return "eExchangeShop_ErrorPack";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EExchangeShop& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EExchangeShop> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eExchangeShop_Sucess", eExchangeShop_Sucess));
		mapStr2Val.insert(make_pair("eExchangeShop_CfgLimit", eExchangeShop_CfgLimit));
		mapStr2Val.insert(make_pair("eExchangeShop_MoneyLimit", eExchangeShop_MoneyLimit));
		mapStr2Val.insert(make_pair("eExchangeShop_CondLimit", eExchangeShop_CondLimit));
		mapStr2Val.insert(make_pair("eExchangeShop_CountLimit", eExchangeShop_CountLimit));
		mapStr2Val.insert(make_pair("eExchangeShop_ErrorItemID", eExchangeShop_ErrorItemID));
		mapStr2Val.insert(make_pair("eExchangeShop_ErrorPack", eExchangeShop_ErrorPack));
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

ExchangeInfo::ExchangeInfo() : qwRoleID(0), dwExchangeID(0), dwCount(0), dwFinishTime(0) { }

ExchangeInfo::ExchangeInfo(UINT64 qwRoleID_, UINT32 dwExchangeID_, UINT32 dwCount_, UINT32 dwFinishTime_) : qwRoleID(qwRoleID_), dwExchangeID(dwExchangeID_), dwCount(dwCount_), dwFinishTime(dwFinishTime_) { }

CInArchive& operator>>(CInArchive& src, ExchangeInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwRoleID;
	src >> s.dwExchangeID;
	src >> s.dwCount;
	src >> s.dwFinishTime;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const ExchangeInfo& s)
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
	src << s.dwExchangeID;
	src << s.dwCount;
	src << s.dwFinishTime;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, ExchangeInfo& s)
{
	if(strcmp(rElement.Value(), "ExchangeInfo") != 0)
	{
		LOG_CRI << "rElement is not ExchangeInfo!";
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
		LOG_CRI << "pElemChild for dwExchangeID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwExchangeID") != 0)
	{
		LOG_CRI << "Attribute: name is not dwExchangeID!";
		return false;
	}
	const char* pszVal_dwExchangeID = pElemChild->Attribute("value");
	if(pszVal_dwExchangeID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwExchangeID, s.dwExchangeID))
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
		LOG_CRI << "pElemChild for dwFinishTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwFinishTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwFinishTime!";
		return false;
	}
	const char* pszVal_dwFinishTime = pElemChild->Attribute("value");
	if(pszVal_dwFinishTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwFinishTime, s.dwFinishTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const ExchangeInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("ExchangeInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("已兑换信息列表"));
	unique_ptr<TiXmlElement> pElem_qwRoleID(new TiXmlElement("UINT64"));
	if(pElem_qwRoleID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwRoleID->SetAttribute("name", "qwRoleID");
	pElem_qwRoleID->SetAttribute("value", NumberToString(s.qwRoleID).c_str());
	pElem_qwRoleID->SetAttribute("comment", ToUTF8Ptr("角色ID"));
	if(rElement.LinkEndChild(pElem_qwRoleID.get()) != NULL)
		pElem_qwRoleID.release();
	unique_ptr<TiXmlElement> pElem_dwExchangeID(new TiXmlElement("UINT32"));
	if(pElem_dwExchangeID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwExchangeID->SetAttribute("name", "dwExchangeID");
	pElem_dwExchangeID->SetAttribute("value", NumberToString(s.dwExchangeID).c_str());
	pElem_dwExchangeID->SetAttribute("comment", ToUTF8Ptr("兑换ID"));
	if(rElement.LinkEndChild(pElem_dwExchangeID.get()) != NULL)
		pElem_dwExchangeID.release();
	unique_ptr<TiXmlElement> pElem_dwCount(new TiXmlElement("UINT32"));
	if(pElem_dwCount == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwCount->SetAttribute("name", "dwCount");
	pElem_dwCount->SetAttribute("value", NumberToString(s.dwCount).c_str());
	pElem_dwCount->SetAttribute("comment", ToUTF8Ptr("已兑换次数"));
	if(rElement.LinkEndChild(pElem_dwCount.get()) != NULL)
		pElem_dwCount.release();
	unique_ptr<TiXmlElement> pElem_dwFinishTime(new TiXmlElement("UINT32"));
	if(pElem_dwFinishTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwFinishTime->SetAttribute("name", "dwFinishTime");
	pElem_dwFinishTime->SetAttribute("value", NumberToString(s.dwFinishTime).c_str());
	pElem_dwFinishTime->SetAttribute("comment", ToUTF8Ptr("兑换时间"));
	if(rElement.LinkEndChild(pElem_dwFinishTime.get()) != NULL)
		pElem_dwFinishTime.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecExchangeInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		ExchangeInfo s;
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

bool VectorToXML(const TVecExchangeInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("ExchangeInfo"));
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

} //namespace NExchangeShopProt
