/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    BeautyLogGS.cpp
//  Purpose:      美女log
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "BeautyLogGS.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NBeautyLogGS
{

#ifdef PROT_USE_XML

const char* EnumValToStr(EBeautyLog e)
{
	switch(e)
	{
	case eBeautyLog_Sucess:
		return "eBeautyLog_Sucess";
	case eBeautyLog_Error:
		return "eBeautyLog_Error";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EBeautyLog& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EBeautyLog> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eBeautyLog_Sucess", eBeautyLog_Sucess));
		mapStr2Val.insert(make_pair("eBeautyLog_Error", eBeautyLog_Error));
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

const char* GetDescription(EBeautyLog e)
{
	switch(e)
	{
	case eBeautyLog_Sucess:
		return "成功";
	case eBeautyLog_Error:
		return "失败";
	default:
		return "未知错误";
	}
}

SBeautyLog::SBeautyLog() : qwUserID(0), byColor(0), wItemID(0), dwCount(0) { }

SBeautyLog::SBeautyLog(UINT64 qwUserID_, const std::string& strRoleName_, UINT8 byColor_, UINT16 wItemID_, UINT32 dwCount_)
			: qwUserID(qwUserID_), strRoleName(strRoleName_), byColor(byColor_), wItemID(wItemID_), dwCount(dwCount_) { }

SBeautyLog::SBeautyLog(SBeautyLog&& src) : qwUserID(src.qwUserID), strRoleName(move(src.strRoleName)), byColor(src.byColor), wItemID(src.wItemID), dwCount(src.dwCount) { }

SBeautyLog& SBeautyLog::operator=(SBeautyLog&& rhs)
{
	if(this != &rhs)
	{
		this->~SBeautyLog();
		new (this) SBeautyLog(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SBeautyLog& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwUserID;
	src >> s.strRoleName;
	src >> s.byColor;
	src >> s.wItemID;
	src >> s.dwCount;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SBeautyLog& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.qwUserID;
	src << s.strRoleName;
	src << s.byColor;
	src << s.wItemID;
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

bool FromXML(TiXmlElement& rElement, SBeautyLog& s)
{
	if(strcmp(rElement.Value(), "SBeautyLog") != 0)
	{
		LOG_CRI << "rElement is not SBeautyLog!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwUserID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwUserID") != 0)
	{
		LOG_CRI << "Attribute: name is not qwUserID!";
		return false;
	}
	const char* pszVal_qwUserID = pElemChild->Attribute("value");
	if(pszVal_qwUserID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwUserID, s.qwUserID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strRoleName is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strRoleName") != 0)
	{
		LOG_CRI << "Attribute: name is not strRoleName!";
		return false;
	}
	const char* pszVal_strRoleName = pElemChild->Attribute("value");
	if(pszVal_strRoleName == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strRoleName = pszVal_strRoleName;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byColor is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byColor") != 0)
	{
		LOG_CRI << "Attribute: name is not byColor!";
		return false;
	}
	const char* pszVal_byColor = pElemChild->Attribute("value");
	if(pszVal_byColor == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byColor, s.byColor))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
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

bool ToXML(const SBeautyLog& s, TiXmlElement& rElement)
{
	rElement.SetValue("SBeautyLog");
	rElement.SetAttribute("type", ToUTF8Ptr("美女log信息"));
	unique_ptr<TiXmlElement> pElem_qwUserID(new TiXmlElement("UINT64"));
	if(pElem_qwUserID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwUserID->SetAttribute("name", "qwUserID");
	pElem_qwUserID->SetAttribute("value", NumberToString(s.qwUserID).c_str());
	pElem_qwUserID->SetAttribute("comment", ToUTF8Ptr("uid"));
	if(rElement.LinkEndChild(pElem_qwUserID.get()) != NULL)
		pElem_qwUserID.release();
	unique_ptr<TiXmlElement> pElem_strRoleName(new TiXmlElement("string"));
	if(pElem_strRoleName == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strRoleName->SetAttribute("name", "strRoleName");
	pElem_strRoleName->SetAttribute("value", s.strRoleName.c_str());
	pElem_strRoleName->SetAttribute("comment", ToUTF8Ptr("角色名"));
	if(rElement.LinkEndChild(pElem_strRoleName.get()) != NULL)
		pElem_strRoleName.release();
	unique_ptr<TiXmlElement> pElem_byColor(new TiXmlElement("UINT8"));
	if(pElem_byColor == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byColor->SetAttribute("name", "byColor");
	pElem_byColor->SetAttribute("value", NumberToString(s.byColor).c_str());
	pElem_byColor->SetAttribute("comment", ToUTF8Ptr("角色颜色"));
	if(rElement.LinkEndChild(pElem_byColor.get()) != NULL)
		pElem_byColor.release();
	unique_ptr<TiXmlElement> pElem_wItemID(new TiXmlElement("UINT16"));
	if(pElem_wItemID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wItemID->SetAttribute("name", "wItemID");
	pElem_wItemID->SetAttribute("value", NumberToString(s.wItemID).c_str());
	pElem_wItemID->SetAttribute("comment", ToUTF8Ptr("物品id"));
	if(rElement.LinkEndChild(pElem_wItemID.get()) != NULL)
		pElem_wItemID.release();
	unique_ptr<TiXmlElement> pElem_dwCount(new TiXmlElement("UINT32"));
	if(pElem_dwCount == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwCount->SetAttribute("name", "dwCount");
	pElem_dwCount->SetAttribute("value", NumberToString(s.dwCount).c_str());
	pElem_dwCount->SetAttribute("comment", ToUTF8Ptr("物品数量"));
	if(rElement.LinkEndChild(pElem_dwCount.get()) != NULL)
		pElem_dwCount.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecBeautyLog& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SBeautyLog s;
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

bool VectorToXML(const TVecBeautyLog& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SBeautyLog"));
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

} //namespace NBeautyLogGS
