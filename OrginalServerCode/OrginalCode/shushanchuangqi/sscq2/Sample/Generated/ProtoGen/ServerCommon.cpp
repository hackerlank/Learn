/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    ServerCommon.cpp
//  Purpose:      服务器通用类型定义
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "ServerCommon.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NServerCommon
{

#ifdef PROT_USE_XML

const char* EnumValToStr(ELeaveType e)
{
	switch(e)
	{
	case eLeaveNone:
		return "eLeaveNone";
	case eLeaveAway:
		return "eLeaveAway";
	case eLeaveReplace:
		return "eLeaveReplace";
	case eLeaveJump:
		return "eLeaveJump";
	case eLeaveKick:
		return "eLeaveKick";
	case eIndulgeKick:
		return "eIndulgeKick";
	case eIndulgeTimeKick:
		return "eIndulgeTimeKick";
	case eLeaveExcept:
		return "eLeaveExcept";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, ELeaveType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, ELeaveType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eLeaveNone", eLeaveNone));
		mapStr2Val.insert(make_pair("eLeaveAway", eLeaveAway));
		mapStr2Val.insert(make_pair("eLeaveReplace", eLeaveReplace));
		mapStr2Val.insert(make_pair("eLeaveJump", eLeaveJump));
		mapStr2Val.insert(make_pair("eLeaveKick", eLeaveKick));
		mapStr2Val.insert(make_pair("eIndulgeKick", eIndulgeKick));
		mapStr2Val.insert(make_pair("eIndulgeTimeKick", eIndulgeTimeKick));
		mapStr2Val.insert(make_pair("eLeaveExcept", eLeaveExcept));
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

const char* GetDescription(ELeaveType e)
{
	switch(e)
	{
	case eLeaveNone:
		return "无";
	case eLeaveAway:
		return "正常下线";
	case eLeaveReplace:
		return "替换帐号";
	case eLeaveJump:
		return "跳服";
	case eLeaveKick:
		return "被踢";
	case eIndulgeKick:
		return "防沉迷系统已启动，请休息5小时";
	case eIndulgeTimeKick:
		return "防沉迷离线不足5小时，请休息5小时";
	case eLeaveExcept:
		return "异常";
	default:
		return "未知错误";
	}
}

#ifdef PROT_USE_XML

const char* EnumValToStr(EUserReqType e)
{
	switch(e)
	{
	case eUserReqNone:
		return "eUserReqNone";
	case eUserReqMail:
		return "eUserReqMail";
	case eUserReqShopMall:
		return "eUserReqShopMall";
	case eUserReqFriend:
		return "eUserReqFriend";
	case eUserReqVIP:
		return "eUserReqVIP";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EUserReqType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EUserReqType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eUserReqNone", eUserReqNone));
		mapStr2Val.insert(make_pair("eUserReqMail", eUserReqMail));
		mapStr2Val.insert(make_pair("eUserReqShopMall", eUserReqShopMall));
		mapStr2Val.insert(make_pair("eUserReqFriend", eUserReqFriend));
		mapStr2Val.insert(make_pair("eUserReqVIP", eUserReqVIP));
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

SUsrIDNameData::SUsrIDNameData() : qwUsrID(0), byLevel(0), byJob(0) { }

SUsrIDNameData::SUsrIDNameData(UINT64 qwUsrID_, const std::string& strName_, UINT8 byLevel_, UINT8 byJob_) : qwUsrID(qwUsrID_), strName(strName_), byLevel(byLevel_), byJob(byJob_) { }

SUsrIDNameData::SUsrIDNameData(SUsrIDNameData&& src) : qwUsrID(src.qwUsrID), strName(move(src.strName)), byLevel(src.byLevel), byJob(src.byJob) { }

SUsrIDNameData& SUsrIDNameData::operator=(SUsrIDNameData&& rhs)
{
	if(this != &rhs)
	{
		this->~SUsrIDNameData();
		new (this) SUsrIDNameData(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SUsrIDNameData& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwUsrID;
	src >> s.strName;
	src >> s.byLevel;
	src >> s.byJob;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SUsrIDNameData& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.qwUsrID;
	src << s.strName;
	src << s.byLevel;
	src << s.byJob;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SUsrIDNameData& s)
{
	if(strcmp(rElement.Value(), "SUsrIDNameData") != 0)
	{
		LOG_CRI << "rElement is not SUsrIDNameData!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwUsrID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwUsrID") != 0)
	{
		LOG_CRI << "Attribute: name is not qwUsrID!";
		return false;
	}
	const char* pszVal_qwUsrID = pElemChild->Attribute("value");
	if(pszVal_qwUsrID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwUsrID, s.qwUsrID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strName is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strName") != 0)
	{
		LOG_CRI << "Attribute: name is not strName!";
		return false;
	}
	const char* pszVal_strName = pElemChild->Attribute("value");
	if(pszVal_strName == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strName = pszVal_strName;
	pElemChild = pElemChild->NextSiblingElement();
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
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byJob is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byJob") != 0)
	{
		LOG_CRI << "Attribute: name is not byJob!";
		return false;
	}
	const char* pszVal_byJob = pElemChild->Attribute("value");
	if(pszVal_byJob == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byJob, s.byJob))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SUsrIDNameData& s, TiXmlElement& rElement)
{
	rElement.SetValue("SUsrIDNameData");
	rElement.SetAttribute("type", ToUTF8Ptr("账号ID,Name数据"));
	unique_ptr<TiXmlElement> pElem_qwUsrID(new TiXmlElement("UINT64"));
	if(pElem_qwUsrID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwUsrID->SetAttribute("name", "qwUsrID");
	pElem_qwUsrID->SetAttribute("value", NumberToString(s.qwUsrID).c_str());
	pElem_qwUsrID->SetAttribute("comment", ToUTF8Ptr("账号ID"));
	if(rElement.LinkEndChild(pElem_qwUsrID.get()) != NULL)
		pElem_qwUsrID.release();
	unique_ptr<TiXmlElement> pElem_strName(new TiXmlElement("string"));
	if(pElem_strName == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strName->SetAttribute("name", "strName");
	pElem_strName->SetAttribute("value", s.strName.c_str());
	pElem_strName->SetAttribute("comment", ToUTF8Ptr("主英雄名"));
	if(rElement.LinkEndChild(pElem_strName.get()) != NULL)
		pElem_strName.release();
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
	unique_ptr<TiXmlElement> pElem_byJob(new TiXmlElement("UINT8"));
	if(pElem_byJob == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byJob->SetAttribute("name", "byJob");
	pElem_byJob->SetAttribute("value", NumberToString(s.byJob).c_str());
	pElem_byJob->SetAttribute("comment", ToUTF8Ptr("职业"));
	if(rElement.LinkEndChild(pElem_byJob.get()) != NULL)
		pElem_byJob.release();
	return true;
}

#endif

} //namespace NServerCommon
