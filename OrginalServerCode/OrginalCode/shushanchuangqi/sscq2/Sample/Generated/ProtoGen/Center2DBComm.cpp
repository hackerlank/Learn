/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    Center2DBComm.cpp
//  Purpose:      CenterServer到DBServer的通信协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "Center2DBComm.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NCenter2DBComm
{

#ifdef PROT_USE_XML

const char* EnumValToStr(ECenterData e)
{
	switch(e)
	{
	case eCenterDate_BeautyLog:
		return "eCenterDate_BeautyLog";
	case eCenterDate_InviteFriend:
		return "eCenterDate_InviteFriend";
	case eCenterDate_InviteTask:
		return "eCenterDate_InviteTask";
	case eCenterDate_DemonTower_MinRonds:
		return "eCenterDate_DemonTower_MinRonds";
	case eCenterDate_DemonTower_MinBattlePoint:
		return "eCenterDate_DemonTower_MinBattlePoint";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, ECenterData& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, ECenterData> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eCenterDate_BeautyLog", eCenterDate_BeautyLog));
		mapStr2Val.insert(make_pair("eCenterDate_InviteFriend", eCenterDate_InviteFriend));
		mapStr2Val.insert(make_pair("eCenterDate_InviteTask", eCenterDate_InviteTask));
		mapStr2Val.insert(make_pair("eCenterDate_DemonTower_MinRonds", eCenterDate_DemonTower_MinRonds));
		mapStr2Val.insert(make_pair("eCenterDate_DemonTower_MinBattlePoint", eCenterDate_DemonTower_MinBattlePoint));
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

SCenterData::SCenterData() : wType(0), qwInstID(0), qwInstID2(0), qwParam(0), dwParam1(0), 
			dwParam2(0), dwParam3(0), qwParam4(0) { }

SCenterData::SCenterData(UINT16 wType_, UINT64 qwInstID_, UINT64 qwInstID2_, UINT64 qwParam_, const std::string& strParam_, 
			UINT32 dwParam1_, UINT32 dwParam2_, UINT32 dwParam3_, UINT64 qwParam4_)
			: wType(wType_), qwInstID(qwInstID_), qwInstID2(qwInstID2_), qwParam(qwParam_), strParam(strParam_), 
			dwParam1(dwParam1_), dwParam2(dwParam2_), dwParam3(dwParam3_), qwParam4(qwParam4_) { }

SCenterData::SCenterData(SCenterData&& src) : wType(src.wType), qwInstID(src.qwInstID), qwInstID2(src.qwInstID2), qwParam(src.qwParam), strParam(move(src.strParam)), 
			dwParam1(src.dwParam1), dwParam2(src.dwParam2), dwParam3(src.dwParam3), qwParam4(src.qwParam4) { }

SCenterData& SCenterData::operator=(SCenterData&& rhs)
{
	if(this != &rhs)
	{
		this->~SCenterData();
		new (this) SCenterData(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SCenterData& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.wType;
	src >> s.qwInstID;
	src >> s.qwInstID2;
	src >> s.qwParam;
	src >> s.strParam;
	src >> s.dwParam1;
	src >> s.dwParam2;
	src >> s.dwParam3;
	src >> s.qwParam4;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SCenterData& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.wType;
	src << s.qwInstID;
	src << s.qwInstID2;
	src << s.qwParam;
	src << s.strParam;
	src << s.dwParam1;
	src << s.dwParam2;
	src << s.dwParam3;
	src << s.qwParam4;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SCenterData& s)
{
	if(strcmp(rElement.Value(), "SCenterData") != 0)
	{
		LOG_CRI << "rElement is not SCenterData!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wType") != 0)
	{
		LOG_CRI << "Attribute: name is not wType!";
		return false;
	}
	const char* pszVal_wType = pElemChild->Attribute("value");
	if(pszVal_wType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wType, s.wType))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwInstID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwInstID") != 0)
	{
		LOG_CRI << "Attribute: name is not qwInstID!";
		return false;
	}
	const char* pszVal_qwInstID = pElemChild->Attribute("value");
	if(pszVal_qwInstID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwInstID, s.qwInstID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwInstID2 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwInstID2") != 0)
	{
		LOG_CRI << "Attribute: name is not qwInstID2!";
		return false;
	}
	const char* pszVal_qwInstID2 = pElemChild->Attribute("value");
	if(pszVal_qwInstID2 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwInstID2, s.qwInstID2))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwParam is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwParam") != 0)
	{
		LOG_CRI << "Attribute: name is not qwParam!";
		return false;
	}
	const char* pszVal_qwParam = pElemChild->Attribute("value");
	if(pszVal_qwParam == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwParam, s.qwParam))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strParam is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strParam") != 0)
	{
		LOG_CRI << "Attribute: name is not strParam!";
		return false;
	}
	const char* pszVal_strParam = pElemChild->Attribute("value");
	if(pszVal_strParam == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strParam = pszVal_strParam;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwParam1 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwParam1") != 0)
	{
		LOG_CRI << "Attribute: name is not dwParam1!";
		return false;
	}
	const char* pszVal_dwParam1 = pElemChild->Attribute("value");
	if(pszVal_dwParam1 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwParam1, s.dwParam1))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwParam2 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwParam2") != 0)
	{
		LOG_CRI << "Attribute: name is not dwParam2!";
		return false;
	}
	const char* pszVal_dwParam2 = pElemChild->Attribute("value");
	if(pszVal_dwParam2 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwParam2, s.dwParam2))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwParam3 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwParam3") != 0)
	{
		LOG_CRI << "Attribute: name is not dwParam3!";
		return false;
	}
	const char* pszVal_dwParam3 = pElemChild->Attribute("value");
	if(pszVal_dwParam3 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwParam3, s.dwParam3))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwParam4 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwParam4") != 0)
	{
		LOG_CRI << "Attribute: name is not qwParam4!";
		return false;
	}
	const char* pszVal_qwParam4 = pElemChild->Attribute("value");
	if(pszVal_qwParam4 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwParam4, s.qwParam4))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SCenterData& s, TiXmlElement& rElement)
{
	rElement.SetValue("SCenterData");
	rElement.SetAttribute("type", ToUTF8Ptr("中心服存储数据"));
	unique_ptr<TiXmlElement> pElem_wType(new TiXmlElement("UINT16"));
	if(pElem_wType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wType->SetAttribute("name", "wType");
	pElem_wType->SetAttribute("value", NumberToString(s.wType).c_str());
	pElem_wType->SetAttribute("comment", ToUTF8Ptr("类型 ECenterData"));
	if(rElement.LinkEndChild(pElem_wType.get()) != NULL)
		pElem_wType.release();
	unique_ptr<TiXmlElement> pElem_qwInstID(new TiXmlElement("UINT64"));
	if(pElem_qwInstID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwInstID->SetAttribute("name", "qwInstID");
	pElem_qwInstID->SetAttribute("value", NumberToString(s.qwInstID).c_str());
	pElem_qwInstID->SetAttribute("comment", ToUTF8Ptr("keyid1"));
	if(rElement.LinkEndChild(pElem_qwInstID.get()) != NULL)
		pElem_qwInstID.release();
	unique_ptr<TiXmlElement> pElem_qwInstID2(new TiXmlElement("UINT64"));
	if(pElem_qwInstID2 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwInstID2->SetAttribute("name", "qwInstID2");
	pElem_qwInstID2->SetAttribute("value", NumberToString(s.qwInstID2).c_str());
	pElem_qwInstID2->SetAttribute("comment", ToUTF8Ptr("keyid2"));
	if(rElement.LinkEndChild(pElem_qwInstID2.get()) != NULL)
		pElem_qwInstID2.release();
	unique_ptr<TiXmlElement> pElem_qwParam(new TiXmlElement("UINT64"));
	if(pElem_qwParam == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwParam->SetAttribute("name", "qwParam");
	pElem_qwParam->SetAttribute("value", NumberToString(s.qwParam).c_str());
	pElem_qwParam->SetAttribute("comment", ToUTF8Ptr("64位参数"));
	if(rElement.LinkEndChild(pElem_qwParam.get()) != NULL)
		pElem_qwParam.release();
	unique_ptr<TiXmlElement> pElem_strParam(new TiXmlElement("string"));
	if(pElem_strParam == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strParam->SetAttribute("name", "strParam");
	pElem_strParam->SetAttribute("value", s.strParam.c_str());
	pElem_strParam->SetAttribute("comment", ToUTF8Ptr("整形参数"));
	if(rElement.LinkEndChild(pElem_strParam.get()) != NULL)
		pElem_strParam.release();
	unique_ptr<TiXmlElement> pElem_dwParam1(new TiXmlElement("UINT32"));
	if(pElem_dwParam1 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwParam1->SetAttribute("name", "dwParam1");
	pElem_dwParam1->SetAttribute("value", NumberToString(s.dwParam1).c_str());
	pElem_dwParam1->SetAttribute("comment", ToUTF8Ptr("32位参数1"));
	if(rElement.LinkEndChild(pElem_dwParam1.get()) != NULL)
		pElem_dwParam1.release();
	unique_ptr<TiXmlElement> pElem_dwParam2(new TiXmlElement("UINT32"));
	if(pElem_dwParam2 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwParam2->SetAttribute("name", "dwParam2");
	pElem_dwParam2->SetAttribute("value", NumberToString(s.dwParam2).c_str());
	pElem_dwParam2->SetAttribute("comment", ToUTF8Ptr("32位参数2"));
	if(rElement.LinkEndChild(pElem_dwParam2.get()) != NULL)
		pElem_dwParam2.release();
	unique_ptr<TiXmlElement> pElem_dwParam3(new TiXmlElement("UINT32"));
	if(pElem_dwParam3 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwParam3->SetAttribute("name", "dwParam3");
	pElem_dwParam3->SetAttribute("value", NumberToString(s.dwParam3).c_str());
	pElem_dwParam3->SetAttribute("comment", ToUTF8Ptr("32位参数3"));
	if(rElement.LinkEndChild(pElem_dwParam3.get()) != NULL)
		pElem_dwParam3.release();
	unique_ptr<TiXmlElement> pElem_qwParam4(new TiXmlElement("UINT64"));
	if(pElem_qwParam4 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwParam4->SetAttribute("name", "qwParam4");
	pElem_qwParam4->SetAttribute("value", NumberToString(s.qwParam4).c_str());
	pElem_qwParam4->SetAttribute("comment", ToUTF8Ptr("64位参数4"));
	if(rElement.LinkEndChild(pElem_qwParam4.get()) != NULL)
		pElem_qwParam4.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecCenterData& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SCenterData s;
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

bool VectorToXML(const TVecCenterData& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SCenterData"));
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

SSystemMailTargetInfo::SSystemMailTargetInfo() : qwMailID(0), qwReceiveID(0) { }

SSystemMailTargetInfo::SSystemMailTargetInfo(UINT64 qwMailID_, UINT64 qwReceiveID_) : qwMailID(qwMailID_), qwReceiveID(qwReceiveID_) { }

CInArchive& operator>>(CInArchive& src, SSystemMailTargetInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwMailID;
	src >> s.qwReceiveID;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SSystemMailTargetInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.qwMailID;
	src << s.qwReceiveID;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SSystemMailTargetInfo& s)
{
	if(strcmp(rElement.Value(), "SSystemMailTargetInfo") != 0)
	{
		LOG_CRI << "rElement is not SSystemMailTargetInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwMailID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwMailID") != 0)
	{
		LOG_CRI << "Attribute: name is not qwMailID!";
		return false;
	}
	const char* pszVal_qwMailID = pElemChild->Attribute("value");
	if(pszVal_qwMailID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwMailID, s.qwMailID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwReceiveID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwReceiveID") != 0)
	{
		LOG_CRI << "Attribute: name is not qwReceiveID!";
		return false;
	}
	const char* pszVal_qwReceiveID = pElemChild->Attribute("value");
	if(pszVal_qwReceiveID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwReceiveID, s.qwReceiveID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SSystemMailTargetInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SSystemMailTargetInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("系统邮件信息"));
	unique_ptr<TiXmlElement> pElem_qwMailID(new TiXmlElement("UINT64"));
	if(pElem_qwMailID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwMailID->SetAttribute("name", "qwMailID");
	pElem_qwMailID->SetAttribute("value", NumberToString(s.qwMailID).c_str());
	pElem_qwMailID->SetAttribute("comment", ToUTF8Ptr("邮件ID"));
	if(rElement.LinkEndChild(pElem_qwMailID.get()) != NULL)
		pElem_qwMailID.release();
	unique_ptr<TiXmlElement> pElem_qwReceiveID(new TiXmlElement("UINT64"));
	if(pElem_qwReceiveID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwReceiveID->SetAttribute("name", "qwReceiveID");
	pElem_qwReceiveID->SetAttribute("value", NumberToString(s.qwReceiveID).c_str());
	pElem_qwReceiveID->SetAttribute("comment", ToUTF8Ptr("接受者ID"));
	if(rElement.LinkEndChild(pElem_qwReceiveID.get()) != NULL)
		pElem_qwReceiveID.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecSystemMailTargetInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SSystemMailTargetInfo s;
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

bool VectorToXML(const TVecSystemMailTargetInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SSystemMailTargetInfo"));
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

MailDelData::MailDelData() : qwMailID(0), byGet(0) { }

MailDelData::MailDelData(UINT64 qwMailID_, UINT8 byGet_) : qwMailID(qwMailID_), byGet(byGet_) { }

CInArchive& operator>>(CInArchive& src, MailDelData& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwMailID;
	src >> s.byGet;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const MailDelData& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.qwMailID;
	src << s.byGet;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, MailDelData& s)
{
	if(strcmp(rElement.Value(), "MailDelData") != 0)
	{
		LOG_CRI << "rElement is not MailDelData!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwMailID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwMailID") != 0)
	{
		LOG_CRI << "Attribute: name is not qwMailID!";
		return false;
	}
	const char* pszVal_qwMailID = pElemChild->Attribute("value");
	if(pszVal_qwMailID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwMailID, s.qwMailID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byGet is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byGet") != 0)
	{
		LOG_CRI << "Attribute: name is not byGet!";
		return false;
	}
	const char* pszVal_byGet = pElemChild->Attribute("value");
	if(pszVal_byGet == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byGet, s.byGet))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const MailDelData& s, TiXmlElement& rElement)
{
	rElement.SetValue("MailDelData");
	rElement.SetAttribute("type", ToUTF8Ptr("邮件删除提示结构"));
	unique_ptr<TiXmlElement> pElem_qwMailID(new TiXmlElement("UINT64"));
	if(pElem_qwMailID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwMailID->SetAttribute("name", "qwMailID");
	pElem_qwMailID->SetAttribute("value", NumberToString(s.qwMailID).c_str());
	pElem_qwMailID->SetAttribute("comment", ToUTF8Ptr("邮件ID"));
	if(rElement.LinkEndChild(pElem_qwMailID.get()) != NULL)
		pElem_qwMailID.release();
	unique_ptr<TiXmlElement> pElem_byGet(new TiXmlElement("UINT8"));
	if(pElem_byGet == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byGet->SetAttribute("name", "byGet");
	pElem_byGet->SetAttribute("value", NumberToString(s.byGet).c_str());
	pElem_byGet->SetAttribute("comment", ToUTF8Ptr("邮件的附件状态"));
	if(rElement.LinkEndChild(pElem_byGet.get()) != NULL)
		pElem_byGet.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecMailDelData& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		MailDelData s;
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

bool VectorToXML(const TVecMailDelData& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("MailDelData"));
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

SSystemMailInfo::SSystemMailInfo() : eMailType((NMailProt::EMailType)0), eMailState((NMailProt::EMailState)0), dwSendTime(0), byGet(0) { }

SSystemMailInfo::SSystemMailInfo(SSystemMailInfo&& src) : eMailType(src.eMailType), eMailState(src.eMailState), dwSendTime(src.dwSendTime), strTitle(move(src.strTitle)), strSender(move(src.strSender)), 
			strMsg(move(src.strMsg)), byGet(src.byGet), vecMailAttachment(move(src.vecMailAttachment)) { }

SSystemMailInfo& SSystemMailInfo::operator=(SSystemMailInfo&& rhs)
{
	if(this != &rhs)
	{
		this->~SSystemMailInfo();
		new (this) SSystemMailInfo(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SSystemMailInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (UINT8&)s.eMailType;
	src >> (UINT8&)s.eMailState;
	src >> s.dwSendTime;
	src >> s.strTitle;
	src >> s.strSender;
	src >> s.strMsg;
	src >> s.byGet;
	src >> s.vecMailAttachment;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SSystemMailInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (UINT8&)s.eMailType;
	src << (UINT8&)s.eMailState;
	src << s.dwSendTime;
	src << s.strTitle;
	src << s.strSender;
	src << s.strMsg;
	src << s.byGet;
	src << s.vecMailAttachment;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SSystemMailInfo& s)
{
	if(strcmp(rElement.Value(), "SSystemMailInfo") != 0)
	{
		LOG_CRI << "rElement is not SSystemMailInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eMailType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "MailProt::EMailType") != 0)
	{
		LOG_CRI << "pElemChild is not MailProt::EMailType!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eMailType") != 0)
	{
		LOG_CRI << "Attribute: name is not eMailType!";
		return false;
	}
	const char* pszVal_eMailType = pElemChild->Attribute("value");
	if(pszVal_eMailType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!NMailProt::EnumStrToVal(pszVal_eMailType, s.eMailType))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eMailState is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "MailProt::EMailState") != 0)
	{
		LOG_CRI << "pElemChild is not MailProt::EMailState!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eMailState") != 0)
	{
		LOG_CRI << "Attribute: name is not eMailState!";
		return false;
	}
	const char* pszVal_eMailState = pElemChild->Attribute("value");
	if(pszVal_eMailState == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!NMailProt::EnumStrToVal(pszVal_eMailState, s.eMailState))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwSendTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwSendTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwSendTime!";
		return false;
	}
	const char* pszVal_dwSendTime = pElemChild->Attribute("value");
	if(pszVal_dwSendTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwSendTime, s.dwSendTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strTitle is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strTitle") != 0)
	{
		LOG_CRI << "Attribute: name is not strTitle!";
		return false;
	}
	const char* pszVal_strTitle = pElemChild->Attribute("value");
	if(pszVal_strTitle == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strTitle = pszVal_strTitle;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strSender is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strSender") != 0)
	{
		LOG_CRI << "Attribute: name is not strSender!";
		return false;
	}
	const char* pszVal_strSender = pElemChild->Attribute("value");
	if(pszVal_strSender == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strSender = pszVal_strSender;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strMsg is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strMsg") != 0)
	{
		LOG_CRI << "Attribute: name is not strMsg!";
		return false;
	}
	const char* pszVal_strMsg = pElemChild->Attribute("value");
	if(pszVal_strMsg == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strMsg = pszVal_strMsg;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byGet is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byGet") != 0)
	{
		LOG_CRI << "Attribute: name is not byGet!";
		return false;
	}
	const char* pszVal_byGet = pElemChild->Attribute("value");
	if(pszVal_byGet == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byGet, s.byGet))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecMailAttachment is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "MailProt::TVecMailAttachment") != 0)
	{
		LOG_CRI << "pElemChild is not MailProt::TVecMailAttachment!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecMailAttachment") != 0)
	{
		LOG_CRI << "Attribute: name is not vecMailAttachment!";
		return false;
	}
	if(!NMailProt::VectorFromXML(*pElemChild, s.vecMailAttachment))
	{
		LOG_CRI << "VectorFromXML for vecMailAttachment fails!";
		return false;
	}
	return true;
}

bool ToXML(const SSystemMailInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SSystemMailInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("系统邮件信息"));
	unique_ptr<TiXmlElement> pElem_eMailType(new TiXmlElement("MailProt::EMailType"));
	if(pElem_eMailType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eMailType->SetAttribute("name", "eMailType");
	const char* pszEnum_eMailType = NMailProt::EnumValToStr(s.eMailType);
	if(pszEnum_eMailType == NULL)
	{
		LOG_CRI << "EnumValToStr for eMailType fails!";
		return false;
	}
	pElem_eMailType->SetAttribute("value", pszEnum_eMailType);
	pElem_eMailType->SetAttribute("comment", ToUTF8Ptr("邮件类型"));
	if(rElement.LinkEndChild(pElem_eMailType.get()) != NULL)
		pElem_eMailType.release();
	unique_ptr<TiXmlElement> pElem_eMailState(new TiXmlElement("MailProt::EMailState"));
	if(pElem_eMailState == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eMailState->SetAttribute("name", "eMailState");
	const char* pszEnum_eMailState = NMailProt::EnumValToStr(s.eMailState);
	if(pszEnum_eMailState == NULL)
	{
		LOG_CRI << "EnumValToStr for eMailState fails!";
		return false;
	}
	pElem_eMailState->SetAttribute("value", pszEnum_eMailState);
	pElem_eMailState->SetAttribute("comment", ToUTF8Ptr("邮件状态"));
	if(rElement.LinkEndChild(pElem_eMailState.get()) != NULL)
		pElem_eMailState.release();
	unique_ptr<TiXmlElement> pElem_dwSendTime(new TiXmlElement("UINT32"));
	if(pElem_dwSendTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwSendTime->SetAttribute("name", "dwSendTime");
	pElem_dwSendTime->SetAttribute("value", NumberToString(s.dwSendTime).c_str());
	pElem_dwSendTime->SetAttribute("comment", ToUTF8Ptr("发送时间"));
	if(rElement.LinkEndChild(pElem_dwSendTime.get()) != NULL)
		pElem_dwSendTime.release();
	unique_ptr<TiXmlElement> pElem_strTitle(new TiXmlElement("string"));
	if(pElem_strTitle == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strTitle->SetAttribute("name", "strTitle");
	pElem_strTitle->SetAttribute("value", s.strTitle.c_str());
	pElem_strTitle->SetAttribute("comment", ToUTF8Ptr("标题"));
	if(rElement.LinkEndChild(pElem_strTitle.get()) != NULL)
		pElem_strTitle.release();
	unique_ptr<TiXmlElement> pElem_strSender(new TiXmlElement("string"));
	if(pElem_strSender == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strSender->SetAttribute("name", "strSender");
	pElem_strSender->SetAttribute("value", s.strSender.c_str());
	pElem_strSender->SetAttribute("comment", ToUTF8Ptr("发送者"));
	if(rElement.LinkEndChild(pElem_strSender.get()) != NULL)
		pElem_strSender.release();
	unique_ptr<TiXmlElement> pElem_strMsg(new TiXmlElement("string"));
	if(pElem_strMsg == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strMsg->SetAttribute("name", "strMsg");
	pElem_strMsg->SetAttribute("value", s.strMsg.c_str());
	pElem_strMsg->SetAttribute("comment", ToUTF8Ptr("邮件内容"));
	if(rElement.LinkEndChild(pElem_strMsg.get()) != NULL)
		pElem_strMsg.release();
	unique_ptr<TiXmlElement> pElem_byGet(new TiXmlElement("UINT8"));
	if(pElem_byGet == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byGet->SetAttribute("name", "byGet");
	pElem_byGet->SetAttribute("value", NumberToString(s.byGet).c_str());
	pElem_byGet->SetAttribute("comment", ToUTF8Ptr("附件状态"));
	if(rElement.LinkEndChild(pElem_byGet.get()) != NULL)
		pElem_byGet.release();
	unique_ptr<TiXmlElement> pElem_vecMailAttachment(new TiXmlElement("MailProt::TVecMailAttachment"));
	if(pElem_vecMailAttachment == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecMailAttachment->SetAttribute("name", "vecMailAttachment");
	if(!NMailProt::VectorToXML(s.vecMailAttachment, *pElem_vecMailAttachment))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecMailAttachment->SetAttribute("comment", ToUTF8Ptr("附件"));
	if(rElement.LinkEndChild(pElem_vecMailAttachment.get()) != NULL)
		pElem_vecMailAttachment.release();
	return true;
}

#endif

SBaseCond::SBaseCond() : byLevel(0) { }

SBaseCond::SBaseCond(UINT8 byLevel_) : byLevel(byLevel_) { }

CInArchive& operator>>(CInArchive& src, SBaseCond& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.byLevel;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SBaseCond& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.byLevel;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SBaseCond& s)
{
	if(strcmp(rElement.Value(), "SBaseCond") != 0)
	{
		LOG_CRI << "rElement is not SBaseCond!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byLevel is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byLevel") != 0)
	{
		LOG_CRI << "Attribute: name is not byLevel!";
		return false;
	}
	const char* pszVal_byLevel = pElemChild->Attribute("value");
	if(pszVal_byLevel == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byLevel, s.byLevel))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SBaseCond& s, TiXmlElement& rElement)
{
	rElement.SetValue("SBaseCond");
	rElement.SetAttribute("type", ToUTF8Ptr("数据库查询基本条件"));
	unique_ptr<TiXmlElement> pElem_byLevel(new TiXmlElement("UINT8"));
	if(pElem_byLevel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byLevel->SetAttribute("name", "byLevel");
	pElem_byLevel->SetAttribute("value", NumberToString(s.byLevel).c_str());
	pElem_byLevel->SetAttribute("comment", ToUTF8Ptr("等级"));
	if(rElement.LinkEndChild(pElem_byLevel.get()) != NULL)
		pElem_byLevel.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecBaseCond& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SBaseCond s;
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

bool VectorToXML(const TVecBaseCond& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SBaseCond"));
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

SBaseResult::SBaseResult() : dwResult(0) { }

SBaseResult::SBaseResult(const TVecUINT64& vecPlayerID_, UINT32 dwResult_) : vecPlayerID(vecPlayerID_), dwResult(dwResult_) { }

CInArchive& operator>>(CInArchive& src, SBaseResult& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.vecPlayerID;
	src >> s.dwResult;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SBaseResult& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.vecPlayerID;
	src << s.dwResult;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SBaseResult& s)
{
	if(strcmp(rElement.Value(), "SBaseResult") != 0)
	{
		LOG_CRI << "rElement is not SBaseResult!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecPlayerID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecUINT64") != 0)
	{
		LOG_CRI << "pElemChild is not TVecUINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecPlayerID") != 0)
	{
		LOG_CRI << "Attribute: name is not vecPlayerID!";
		return false;
	}
	const char* pszText_vecPlayerID = pElemChild->GetText();
	if(pszText_vecPlayerID != NULL)
		SplitToNumber(pszText_vecPlayerID, ",", s.vecPlayerID);
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwResult is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwResult") != 0)
	{
		LOG_CRI << "Attribute: name is not dwResult!";
		return false;
	}
	const char* pszVal_dwResult = pElemChild->Attribute("value");
	if(pszVal_dwResult == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwResult, s.dwResult))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SBaseResult& s, TiXmlElement& rElement)
{
	rElement.SetValue("SBaseResult");
	rElement.SetAttribute("type", ToUTF8Ptr("数据库查询返回"));
	unique_ptr<TiXmlElement> pElem_vecPlayerID(new TiXmlElement("TVecUINT64"));
	if(pElem_vecPlayerID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecPlayerID->SetAttribute("name", "vecPlayerID");
	string strText_vecPlayerID;
	for(size_t i = 0; i < s.vecPlayerID.size(); ++i)
	{
		if(i > 0)
			strText_vecPlayerID += ", ";
		strText_vecPlayerID += NumberToString(s.vecPlayerID[i]);
	}
	unique_ptr<TiXmlText> pText_vecPlayerID(new TiXmlText(strText_vecPlayerID.c_str()));
	if(pText_vecPlayerID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(pElem_vecPlayerID->LinkEndChild(pText_vecPlayerID.get()) != NULL)
		pText_vecPlayerID.release();
	pElem_vecPlayerID->SetAttribute("comment", ToUTF8Ptr("玩家ID"));
	if(rElement.LinkEndChild(pElem_vecPlayerID.get()) != NULL)
		pElem_vecPlayerID.release();
	unique_ptr<TiXmlElement> pElem_dwResult(new TiXmlElement("UINT32"));
	if(pElem_dwResult == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwResult->SetAttribute("name", "dwResult");
	pElem_dwResult->SetAttribute("value", NumberToString(s.dwResult).c_str());
	pElem_dwResult->SetAttribute("comment", ToUTF8Ptr("查询结果"));
	if(rElement.LinkEndChild(pElem_dwResult.get()) != NULL)
		pElem_dwResult.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecBaseResult& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SBaseResult s;
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

bool VectorToXML(const TVecBaseResult& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SBaseResult"));
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

SRoleLevel::SRoleLevel() : dwID(0), dwCount(0) { }

SRoleLevel::SRoleLevel(UINT32 dwID_, UINT32 dwCount_, const TVecUINT64& vecRole_) : dwID(dwID_), dwCount(dwCount_), vecRole(vecRole_) { }

CInArchive& operator>>(CInArchive& src, SRoleLevel& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.dwID;
	src >> s.dwCount;
	src >> s.vecRole;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SRoleLevel& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.dwID;
	src << s.dwCount;
	src << s.vecRole;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SRoleLevel& s)
{
	if(strcmp(rElement.Value(), "SRoleLevel") != 0)
	{
		LOG_CRI << "rElement is not SRoleLevel!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwID") != 0)
	{
		LOG_CRI << "Attribute: name is not dwID!";
		return false;
	}
	const char* pszVal_dwID = pElemChild->Attribute("value");
	if(pszVal_dwID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwID, s.dwID))
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
		LOG_CRI << "pElemChild for vecRole is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecUINT64") != 0)
	{
		LOG_CRI << "pElemChild is not TVecUINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecRole") != 0)
	{
		LOG_CRI << "Attribute: name is not vecRole!";
		return false;
	}
	const char* pszText_vecRole = pElemChild->GetText();
	if(pszText_vecRole != NULL)
		SplitToNumber(pszText_vecRole, ",", s.vecRole);
	return true;
}

bool ToXML(const SRoleLevel& s, TiXmlElement& rElement)
{
	rElement.SetValue("SRoleLevel");
	rElement.SetAttribute("type", ToUTF8Ptr("玩家等级"));
	unique_ptr<TiXmlElement> pElem_dwID(new TiXmlElement("UINT32"));
	if(pElem_dwID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwID->SetAttribute("name", "dwID");
	pElem_dwID->SetAttribute("value", NumberToString(s.dwID).c_str());
	pElem_dwID->SetAttribute("comment", ToUTF8Ptr("条件ID"));
	if(rElement.LinkEndChild(pElem_dwID.get()) != NULL)
		pElem_dwID.release();
	unique_ptr<TiXmlElement> pElem_dwCount(new TiXmlElement("UINT32"));
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
	unique_ptr<TiXmlElement> pElem_vecRole(new TiXmlElement("TVecUINT64"));
	if(pElem_vecRole == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecRole->SetAttribute("name", "vecRole");
	string strText_vecRole;
	for(size_t i = 0; i < s.vecRole.size(); ++i)
	{
		if(i > 0)
			strText_vecRole += ", ";
		strText_vecRole += NumberToString(s.vecRole[i]);
	}
	unique_ptr<TiXmlText> pText_vecRole(new TiXmlText(strText_vecRole.c_str()));
	if(pText_vecRole == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(pElem_vecRole->LinkEndChild(pText_vecRole.get()) != NULL)
		pText_vecRole.release();
	pElem_vecRole->SetAttribute("comment", ToUTF8Ptr("玩家ID"));
	if(rElement.LinkEndChild(pElem_vecRole.get()) != NULL)
		pElem_vecRole.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecRoleLevel& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SRoleLevel s;
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

bool VectorToXML(const TVecRoleLevel& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SRoleLevel"));
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

} //namespace NCenter2DBComm
