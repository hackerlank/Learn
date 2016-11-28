/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    ShushanweiweiProt.cpp
//  Purpose:      蜀山微微协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "ShushanweiweiProt.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NShushanweiweiProt
{

#ifdef PROT_USE_XML

const char* EnumValToStr(EPkgResult e)
{
	switch(e)
	{
	case ePackError:
		return "ePackError";
	case ePackGain:
		return "ePackGain";
	case ePackFull:
		return "ePackFull";
	case ePackSuccess:
		return "ePackSuccess";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EPkgResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EPkgResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("ePackError", ePackError));
		mapStr2Val.insert(make_pair("ePackGain", ePackGain));
		mapStr2Val.insert(make_pair("ePackFull", ePackFull));
		mapStr2Val.insert(make_pair("ePackSuccess", ePackSuccess));
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

const char* EnumValToStr(EPkgType e)
{
	switch(e)
	{
	case eWeibo:
		return "eWeibo";
	case eWeixin:
		return "eWeixin";
	case eMax:
		return "eMax";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EPkgType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EPkgType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eWeibo", eWeibo));
		mapStr2Val.insert(make_pair("eWeixin", eWeixin));
		mapStr2Val.insert(make_pair("eMax", eMax));
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

SPrizeInfo::SPrizeInfo() : eType((EPkgType)0), dwCount(0), bListen(false), bResult(false), wResult(0) { }

SPrizeInfo::SPrizeInfo(EPkgType eType_, UINT32 dwCount_, bool bListen_, bool bResult_, UINT16 wResult_)
			: eType(eType_), dwCount(dwCount_), bListen(bListen_), bResult(bResult_), wResult(wResult_) { }

CInArchive& operator>>(CInArchive& src, SPrizeInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (UINT8&)s.eType;
	src >> s.dwCount;
	src >> s.bListen;
	src >> s.bResult;
	src >> s.wResult;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SPrizeInfo& s)
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
	src << s.dwCount;
	src << s.bListen;
	src << s.bResult;
	src << s.wResult;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SPrizeInfo& s)
{
	if(strcmp(rElement.Value(), "SPrizeInfo") != 0)
	{
		LOG_CRI << "rElement is not SPrizeInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "EPkgType") != 0)
	{
		LOG_CRI << "pElemChild is not EPkgType!";
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
		LOG_CRI << "pElemChild for bListen is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "bool") != 0)
	{
		LOG_CRI << "pElemChild is not bool!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "bListen") != 0)
	{
		LOG_CRI << "Attribute: name is not bListen!";
		return false;
	}
	const char* pszVal_bListen = pElemChild->Attribute("value");
	if(pszVal_bListen == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_bListen, s.bListen))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for bResult is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "bool") != 0)
	{
		LOG_CRI << "pElemChild is not bool!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "bResult") != 0)
	{
		LOG_CRI << "Attribute: name is not bResult!";
		return false;
	}
	const char* pszVal_bResult = pElemChild->Attribute("value");
	if(pszVal_bResult == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_bResult, s.bResult))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wResult is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wResult") != 0)
	{
		LOG_CRI << "Attribute: name is not wResult!";
		return false;
	}
	const char* pszVal_wResult = pElemChild->Attribute("value");
	if(pszVal_wResult == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wResult, s.wResult))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SPrizeInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SPrizeInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("奖励信息"));
	unique_ptr<TiXmlElement> pElem_eType(new TiXmlElement("EPkgType"));
	if(pElem_eType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eType->SetAttribute("name", "eType");
	const char* pszEnum_eType = EnumValToStr(s.eType);
	if(pszEnum_eType == NULL)
	{
		LOG_CRI << "EnumValToStr for EPkgType fails!";
		return false;
	}
	pElem_eType->SetAttribute("value", pszEnum_eType);
	pElem_eType->SetAttribute("comment", ToUTF8Ptr("奖励类型"));
	if(rElement.LinkEndChild(pElem_eType.get()) != NULL)
		pElem_eType.release();
	unique_ptr<TiXmlElement> pElem_dwCount(new TiXmlElement("UINT32"));
	if(pElem_dwCount == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwCount->SetAttribute("name", "dwCount");
	pElem_dwCount->SetAttribute("value", NumberToString(s.dwCount).c_str());
	pElem_dwCount->SetAttribute("comment", ToUTF8Ptr("当前人数"));
	if(rElement.LinkEndChild(pElem_dwCount.get()) != NULL)
		pElem_dwCount.release();
	unique_ptr<TiXmlElement> pElem_bListen(new TiXmlElement("bool"));
	if(pElem_bListen == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_bListen->SetAttribute("name", "bListen");
	pElem_bListen->SetAttribute("value", NumberToString(s.bListen).c_str());
	pElem_bListen->SetAttribute("comment", ToUTF8Ptr("微博是否收听"));
	if(rElement.LinkEndChild(pElem_bListen.get()) != NULL)
		pElem_bListen.release();
	unique_ptr<TiXmlElement> pElem_bResult(new TiXmlElement("bool"));
	if(pElem_bResult == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_bResult->SetAttribute("name", "bResult");
	pElem_bResult->SetAttribute("value", NumberToString(s.bResult).c_str());
	pElem_bResult->SetAttribute("comment", ToUTF8Ptr("个人奖励是否领取"));
	if(rElement.LinkEndChild(pElem_bResult.get()) != NULL)
		pElem_bResult.release();
	unique_ptr<TiXmlElement> pElem_wResult(new TiXmlElement("UINT16"));
	if(pElem_wResult == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wResult->SetAttribute("name", "wResult");
	pElem_wResult->SetAttribute("value", NumberToString(s.wResult).c_str());
	pElem_wResult->SetAttribute("comment", ToUTF8Ptr("全服奖励领取结果"));
	if(rElement.LinkEndChild(pElem_wResult.get()) != NULL)
		pElem_wResult.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecPrizeInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SPrizeInfo s;
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

bool VectorToXML(const TVecPrizeInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SPrizeInfo"));
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

} //namespace NShushanweiweiProt
