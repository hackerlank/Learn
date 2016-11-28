/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    DemonTower.cpp
//  Purpose:      锁妖塔
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "DemonTower.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NDemonTower
{

#ifdef PROT_USE_XML

const char* EnumValToStr(EAttackedType e)
{
	switch(e)
	{
	case eAttackedType_DemonTower:
		return "eAttackedType_DemonTower";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EAttackedType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EAttackedType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eAttackedType_DemonTower", eAttackedType_DemonTower));
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

const char* GetDescription(EAttackedType e)
{
	switch(e)
	{
	case eAttackedType_DemonTower:
		return "锁妖塔";
	default:
		return "未知错误";
	}
}

SSpaceInfo::SSpaceInfo() : dwSoulSpaceID(0), dwSoulSpaceLevel(0) { }

SSpaceInfo::SSpaceInfo(UINT32 dwSoulSpaceID_, UINT32 dwSoulSpaceLevel_) : dwSoulSpaceID(dwSoulSpaceID_), dwSoulSpaceLevel(dwSoulSpaceLevel_) { }

CInArchive& operator>>(CInArchive& src, SSpaceInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.dwSoulSpaceID;
	src >> s.dwSoulSpaceLevel;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SSpaceInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.dwSoulSpaceID;
	src << s.dwSoulSpaceLevel;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SSpaceInfo& s)
{
	if(strcmp(rElement.Value(), "SSpaceInfo") != 0)
	{
		LOG_CRI << "rElement is not SSpaceInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwSoulSpaceID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwSoulSpaceID") != 0)
	{
		LOG_CRI << "Attribute: name is not dwSoulSpaceID!";
		return false;
	}
	const char* pszVal_dwSoulSpaceID = pElemChild->Attribute("value");
	if(pszVal_dwSoulSpaceID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwSoulSpaceID, s.dwSoulSpaceID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwSoulSpaceLevel is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwSoulSpaceLevel") != 0)
	{
		LOG_CRI << "Attribute: name is not dwSoulSpaceLevel!";
		return false;
	}
	const char* pszVal_dwSoulSpaceLevel = pElemChild->Attribute("value");
	if(pszVal_dwSoulSpaceLevel == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwSoulSpaceLevel, s.dwSoulSpaceLevel))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SSpaceInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SSpaceInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("魄空间列表"));
	unique_ptr<TiXmlElement> pElem_dwSoulSpaceID(new TiXmlElement("UINT32"));
	if(pElem_dwSoulSpaceID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwSoulSpaceID->SetAttribute("name", "dwSoulSpaceID");
	pElem_dwSoulSpaceID->SetAttribute("value", NumberToString(s.dwSoulSpaceID).c_str());
	pElem_dwSoulSpaceID->SetAttribute("comment", ToUTF8Ptr("魄空间id"));
	if(rElement.LinkEndChild(pElem_dwSoulSpaceID.get()) != NULL)
		pElem_dwSoulSpaceID.release();
	unique_ptr<TiXmlElement> pElem_dwSoulSpaceLevel(new TiXmlElement("UINT32"));
	if(pElem_dwSoulSpaceLevel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwSoulSpaceLevel->SetAttribute("name", "dwSoulSpaceLevel");
	pElem_dwSoulSpaceLevel->SetAttribute("value", NumberToString(s.dwSoulSpaceLevel).c_str());
	pElem_dwSoulSpaceLevel->SetAttribute("comment", ToUTF8Ptr("魄空间等级"));
	if(rElement.LinkEndChild(pElem_dwSoulSpaceLevel.get()) != NULL)
		pElem_dwSoulSpaceLevel.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecSpaceInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SSpaceInfo s;
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

bool VectorToXML(const TVecSpaceInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SSpaceInfo"));
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

SRoleAttaked::SRoleAttaked() : qwRoleID(0), dwPos(0), qwAtkRoleID(0), byLevel(0), dwAttackedTime(0), 
			dwFighterType(0) { }

SRoleAttaked::SRoleAttaked(UINT64 qwRoleID_, UINT32 dwPos_, UINT64 qwAtkRoleID_, const std::string& strRoleName_, UINT8 byLevel_, 
			UINT32 dwAttackedTime_, UINT32 dwFighterType_)
			: qwRoleID(qwRoleID_), dwPos(dwPos_), qwAtkRoleID(qwAtkRoleID_), strRoleName(strRoleName_), byLevel(byLevel_), 
			dwAttackedTime(dwAttackedTime_), dwFighterType(dwFighterType_) { }

SRoleAttaked::SRoleAttaked(SRoleAttaked&& src) : qwRoleID(src.qwRoleID), dwPos(src.dwPos), qwAtkRoleID(src.qwAtkRoleID), strRoleName(move(src.strRoleName)), byLevel(src.byLevel), 
			dwAttackedTime(src.dwAttackedTime), dwFighterType(src.dwFighterType) { }

SRoleAttaked& SRoleAttaked::operator=(SRoleAttaked&& rhs)
{
	if(this != &rhs)
	{
		this->~SRoleAttaked();
		new (this) SRoleAttaked(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SRoleAttaked& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwRoleID;
	src >> s.dwPos;
	src >> s.qwAtkRoleID;
	src >> s.strRoleName;
	src >> s.byLevel;
	src >> s.dwAttackedTime;
	src >> s.dwFighterType;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SRoleAttaked& s)
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
	src << s.dwPos;
	src << s.qwAtkRoleID;
	src << s.strRoleName;
	src << s.byLevel;
	src << s.dwAttackedTime;
	src << s.dwFighterType;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SRoleAttaked& s)
{
	if(strcmp(rElement.Value(), "SRoleAttaked") != 0)
	{
		LOG_CRI << "rElement is not SRoleAttaked!";
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
		LOG_CRI << "pElemChild for dwPos is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwPos") != 0)
	{
		LOG_CRI << "Attribute: name is not dwPos!";
		return false;
	}
	const char* pszVal_dwPos = pElemChild->Attribute("value");
	if(pszVal_dwPos == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwPos, s.dwPos))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwAtkRoleID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwAtkRoleID") != 0)
	{
		LOG_CRI << "Attribute: name is not qwAtkRoleID!";
		return false;
	}
	const char* pszVal_qwAtkRoleID = pElemChild->Attribute("value");
	if(pszVal_qwAtkRoleID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwAtkRoleID, s.qwAtkRoleID))
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
		LOG_CRI << "pElemChild for dwAttackedTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwAttackedTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwAttackedTime!";
		return false;
	}
	const char* pszVal_dwAttackedTime = pElemChild->Attribute("value");
	if(pszVal_dwAttackedTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwAttackedTime, s.dwAttackedTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwFighterType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwFighterType") != 0)
	{
		LOG_CRI << "Attribute: name is not dwFighterType!";
		return false;
	}
	const char* pszVal_dwFighterType = pElemChild->Attribute("value");
	if(pszVal_dwFighterType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwFighterType, s.dwFighterType))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SRoleAttaked& s, TiXmlElement& rElement)
{
	rElement.SetValue("SRoleAttaked");
	rElement.SetAttribute("type", ToUTF8Ptr("被攻击列表"));
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
	unique_ptr<TiXmlElement> pElem_dwPos(new TiXmlElement("UINT32"));
	if(pElem_dwPos == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwPos->SetAttribute("name", "dwPos");
	pElem_dwPos->SetAttribute("value", NumberToString(s.dwPos).c_str());
	pElem_dwPos->SetAttribute("comment", ToUTF8Ptr("存储位置"));
	if(rElement.LinkEndChild(pElem_dwPos.get()) != NULL)
		pElem_dwPos.release();
	unique_ptr<TiXmlElement> pElem_qwAtkRoleID(new TiXmlElement("UINT64"));
	if(pElem_qwAtkRoleID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwAtkRoleID->SetAttribute("name", "qwAtkRoleID");
	pElem_qwAtkRoleID->SetAttribute("value", NumberToString(s.qwAtkRoleID).c_str());
	pElem_qwAtkRoleID->SetAttribute("comment", ToUTF8Ptr("攻击角色ID"));
	if(rElement.LinkEndChild(pElem_qwAtkRoleID.get()) != NULL)
		pElem_qwAtkRoleID.release();
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
	unique_ptr<TiXmlElement> pElem_dwAttackedTime(new TiXmlElement("UINT32"));
	if(pElem_dwAttackedTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwAttackedTime->SetAttribute("name", "dwAttackedTime");
	pElem_dwAttackedTime->SetAttribute("value", NumberToString(s.dwAttackedTime).c_str());
	pElem_dwAttackedTime->SetAttribute("comment", ToUTF8Ptr("攻击时间"));
	if(rElement.LinkEndChild(pElem_dwAttackedTime.get()) != NULL)
		pElem_dwAttackedTime.release();
	unique_ptr<TiXmlElement> pElem_dwFighterType(new TiXmlElement("UINT32"));
	if(pElem_dwFighterType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwFighterType->SetAttribute("name", "dwFighterType");
	pElem_dwFighterType->SetAttribute("value", NumberToString(s.dwFighterType).c_str());
	pElem_dwFighterType->SetAttribute("comment", ToUTF8Ptr("战斗类型"));
	if(rElement.LinkEndChild(pElem_dwFighterType.get()) != NULL)
		pElem_dwFighterType.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecRoleAttaked& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SRoleAttaked s;
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

bool VectorToXML(const TVecRoleAttaked& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SRoleAttaked"));
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

SDemonToweAttackedInfo::SDemonToweAttackedInfo() : qwAtkRoleID(0), dwLayerID(0), byLevel(0), dwAttackedTime(0) { }

SDemonToweAttackedInfo::SDemonToweAttackedInfo(UINT64 qwAtkRoleID_, const std::string& strRoleName_, UINT32 dwLayerID_, UINT8 byLevel_, UINT32 dwAttackedTime_)
			: qwAtkRoleID(qwAtkRoleID_), strRoleName(strRoleName_), dwLayerID(dwLayerID_), byLevel(byLevel_), dwAttackedTime(dwAttackedTime_) { }

SDemonToweAttackedInfo::SDemonToweAttackedInfo(SDemonToweAttackedInfo&& src) : qwAtkRoleID(src.qwAtkRoleID), strRoleName(move(src.strRoleName)), dwLayerID(src.dwLayerID), byLevel(src.byLevel), dwAttackedTime(src.dwAttackedTime) { }

SDemonToweAttackedInfo& SDemonToweAttackedInfo::operator=(SDemonToweAttackedInfo&& rhs)
{
	if(this != &rhs)
	{
		this->~SDemonToweAttackedInfo();
		new (this) SDemonToweAttackedInfo(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SDemonToweAttackedInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwAtkRoleID;
	src >> s.strRoleName;
	src >> s.dwLayerID;
	src >> s.byLevel;
	src >> s.dwAttackedTime;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SDemonToweAttackedInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.qwAtkRoleID;
	src << s.strRoleName;
	src << s.dwLayerID;
	src << s.byLevel;
	src << s.dwAttackedTime;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SDemonToweAttackedInfo& s)
{
	if(strcmp(rElement.Value(), "SDemonToweAttackedInfo") != 0)
	{
		LOG_CRI << "rElement is not SDemonToweAttackedInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwAtkRoleID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwAtkRoleID") != 0)
	{
		LOG_CRI << "Attribute: name is not qwAtkRoleID!";
		return false;
	}
	const char* pszVal_qwAtkRoleID = pElemChild->Attribute("value");
	if(pszVal_qwAtkRoleID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwAtkRoleID, s.qwAtkRoleID))
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
		LOG_CRI << "pElemChild for dwLayerID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwLayerID") != 0)
	{
		LOG_CRI << "Attribute: name is not dwLayerID!";
		return false;
	}
	const char* pszVal_dwLayerID = pElemChild->Attribute("value");
	if(pszVal_dwLayerID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwLayerID, s.dwLayerID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
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
		LOG_CRI << "pElemChild for dwAttackedTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwAttackedTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwAttackedTime!";
		return false;
	}
	const char* pszVal_dwAttackedTime = pElemChild->Attribute("value");
	if(pszVal_dwAttackedTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwAttackedTime, s.dwAttackedTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SDemonToweAttackedInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SDemonToweAttackedInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("锁妖塔被攻击列表"));
	unique_ptr<TiXmlElement> pElem_qwAtkRoleID(new TiXmlElement("UINT64"));
	if(pElem_qwAtkRoleID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwAtkRoleID->SetAttribute("name", "qwAtkRoleID");
	pElem_qwAtkRoleID->SetAttribute("value", NumberToString(s.qwAtkRoleID).c_str());
	pElem_qwAtkRoleID->SetAttribute("comment", ToUTF8Ptr("攻击角色ID"));
	if(rElement.LinkEndChild(pElem_qwAtkRoleID.get()) != NULL)
		pElem_qwAtkRoleID.release();
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
	unique_ptr<TiXmlElement> pElem_dwLayerID(new TiXmlElement("UINT32"));
	if(pElem_dwLayerID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwLayerID->SetAttribute("name", "dwLayerID");
	pElem_dwLayerID->SetAttribute("value", NumberToString(s.dwLayerID).c_str());
	pElem_dwLayerID->SetAttribute("comment", ToUTF8Ptr("层数"));
	if(rElement.LinkEndChild(pElem_dwLayerID.get()) != NULL)
		pElem_dwLayerID.release();
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
	unique_ptr<TiXmlElement> pElem_dwAttackedTime(new TiXmlElement("UINT32"));
	if(pElem_dwAttackedTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwAttackedTime->SetAttribute("name", "dwAttackedTime");
	pElem_dwAttackedTime->SetAttribute("value", NumberToString(s.dwAttackedTime).c_str());
	pElem_dwAttackedTime->SetAttribute("comment", ToUTF8Ptr("攻击时间"));
	if(rElement.LinkEndChild(pElem_dwAttackedTime.get()) != NULL)
		pElem_dwAttackedTime.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecDemonToweAttackedInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SDemonToweAttackedInfo s;
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

bool VectorToXML(const TVecDemonToweAttackedInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SDemonToweAttackedInfo"));
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

} //namespace NDemonTower
