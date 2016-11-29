/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    Horse.cpp
//  Purpose:      坐骑
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "Horse.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NHorse
{

#ifdef PROT_USE_XML

const char* EnumValToStr(EHorseStatus e)
{
	switch(e)
	{
	case eHorseStatusUnMount:
		return "eHorseStatusUnMount";
	case eHorseStatusMounted:
		return "eHorseStatusMounted";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EHorseStatus& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EHorseStatus> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eHorseStatusUnMount", eHorseStatusUnMount));
		mapStr2Val.insert(make_pair("eHorseStatusMounted", eHorseStatusMounted));
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

const char* EnumValToStr(EHorseOpType e)
{
	switch(e)
	{
	case eHorseOpType_Add:
		return "eHorseOpType_Add";
	case eHorseOpType_Update:
		return "eHorseOpType_Update";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EHorseOpType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EHorseOpType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eHorseOpType_Add", eHorseOpType_Add));
		mapStr2Val.insert(make_pair("eHorseOpType_Update", eHorseOpType_Update));
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

SHorseDB::SHorseDB() : qwRoleID(0), qwUserID(0), dwHorseID(0), dwHorseLevel(0), dwPos(0), 
			dwModelID(0), dwExp(0), dwLock(0) { }

SHorseDB::SHorseDB(UINT64 qwRoleID_, UINT64 qwUserID_, UINT32 dwHorseID_, UINT32 dwHorseLevel_, UINT32 dwPos_, 
			UINT32 dwModelID_, UINT32 dwExp_, UINT32 dwLock_, const std::string& strModel_)
			: qwRoleID(qwRoleID_), qwUserID(qwUserID_), dwHorseID(dwHorseID_), dwHorseLevel(dwHorseLevel_), dwPos(dwPos_), 
			dwModelID(dwModelID_), dwExp(dwExp_), dwLock(dwLock_), strModel(strModel_) { }

SHorseDB::SHorseDB(SHorseDB&& src) : qwRoleID(src.qwRoleID), qwUserID(src.qwUserID), dwHorseID(src.dwHorseID), dwHorseLevel(src.dwHorseLevel), dwPos(src.dwPos), 
			dwModelID(src.dwModelID), dwExp(src.dwExp), dwLock(src.dwLock), strModel(move(src.strModel)) { }

SHorseDB& SHorseDB::operator=(SHorseDB&& rhs)
{
	if(this != &rhs)
	{
		this->~SHorseDB();
		new (this) SHorseDB(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SHorseDB& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwRoleID;
	src >> s.qwUserID;
	src >> s.dwHorseID;
	src >> s.dwHorseLevel;
	src >> s.dwPos;
	src >> s.dwModelID;
	src >> s.dwExp;
	src >> s.dwLock;
	src >> s.strModel;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SHorseDB& s)
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
	src << s.qwUserID;
	src << s.dwHorseID;
	src << s.dwHorseLevel;
	src << s.dwPos;
	src << s.dwModelID;
	src << s.dwExp;
	src << s.dwLock;
	src << s.strModel;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SHorseDB& s)
{
	if(strcmp(rElement.Value(), "SHorseDB") != 0)
	{
		LOG_CRI << "rElement is not SHorseDB!";
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
		LOG_CRI << "pElemChild for dwHorseID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwHorseID") != 0)
	{
		LOG_CRI << "Attribute: name is not dwHorseID!";
		return false;
	}
	const char* pszVal_dwHorseID = pElemChild->Attribute("value");
	if(pszVal_dwHorseID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwHorseID, s.dwHorseID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwHorseLevel is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwHorseLevel") != 0)
	{
		LOG_CRI << "Attribute: name is not dwHorseLevel!";
		return false;
	}
	const char* pszVal_dwHorseLevel = pElemChild->Attribute("value");
	if(pszVal_dwHorseLevel == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwHorseLevel, s.dwHorseLevel))
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
		LOG_CRI << "pElemChild for dwModelID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwModelID") != 0)
	{
		LOG_CRI << "Attribute: name is not dwModelID!";
		return false;
	}
	const char* pszVal_dwModelID = pElemChild->Attribute("value");
	if(pszVal_dwModelID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwModelID, s.dwModelID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwExp is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwExp") != 0)
	{
		LOG_CRI << "Attribute: name is not dwExp!";
		return false;
	}
	const char* pszVal_dwExp = pElemChild->Attribute("value");
	if(pszVal_dwExp == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwExp, s.dwExp))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwLock is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwLock") != 0)
	{
		LOG_CRI << "Attribute: name is not dwLock!";
		return false;
	}
	const char* pszVal_dwLock = pElemChild->Attribute("value");
	if(pszVal_dwLock == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwLock, s.dwLock))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strModel is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strModel") != 0)
	{
		LOG_CRI << "Attribute: name is not strModel!";
		return false;
	}
	const char* pszVal_strModel = pElemChild->Attribute("value");
	if(pszVal_strModel == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strModel = pszVal_strModel;
	return true;
}

bool ToXML(const SHorseDB& s, TiXmlElement& rElement)
{
	rElement.SetValue("SHorseDB");
	rElement.SetAttribute("type", ToUTF8Ptr("坐骑数据库数据"));
	unique_ptr<TiXmlElement> pElem_qwRoleID(new TiXmlElement("UINT64"));
	if(pElem_qwRoleID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwRoleID->SetAttribute("name", "qwRoleID");
	pElem_qwRoleID->SetAttribute("value", NumberToString(s.qwRoleID).c_str());
	pElem_qwRoleID->SetAttribute("comment", ToUTF8Ptr("角色id"));
	if(rElement.LinkEndChild(pElem_qwRoleID.get()) != NULL)
		pElem_qwRoleID.release();
	unique_ptr<TiXmlElement> pElem_qwUserID(new TiXmlElement("UINT64"));
	if(pElem_qwUserID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwUserID->SetAttribute("name", "qwUserID");
	pElem_qwUserID->SetAttribute("value", NumberToString(s.qwUserID).c_str());
	pElem_qwUserID->SetAttribute("comment", ToUTF8Ptr("账号"));
	if(rElement.LinkEndChild(pElem_qwUserID.get()) != NULL)
		pElem_qwUserID.release();
	unique_ptr<TiXmlElement> pElem_dwHorseID(new TiXmlElement("UINT32"));
	if(pElem_dwHorseID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwHorseID->SetAttribute("name", "dwHorseID");
	pElem_dwHorseID->SetAttribute("value", NumberToString(s.dwHorseID).c_str());
	pElem_dwHorseID->SetAttribute("comment", ToUTF8Ptr("坐骑id"));
	if(rElement.LinkEndChild(pElem_dwHorseID.get()) != NULL)
		pElem_dwHorseID.release();
	unique_ptr<TiXmlElement> pElem_dwHorseLevel(new TiXmlElement("UINT32"));
	if(pElem_dwHorseLevel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwHorseLevel->SetAttribute("name", "dwHorseLevel");
	pElem_dwHorseLevel->SetAttribute("value", NumberToString(s.dwHorseLevel).c_str());
	pElem_dwHorseLevel->SetAttribute("comment", ToUTF8Ptr("坐骑等级"));
	if(rElement.LinkEndChild(pElem_dwHorseLevel.get()) != NULL)
		pElem_dwHorseLevel.release();
	unique_ptr<TiXmlElement> pElem_dwPos(new TiXmlElement("UINT32"));
	if(pElem_dwPos == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwPos->SetAttribute("name", "dwPos");
	pElem_dwPos->SetAttribute("value", NumberToString(s.dwPos).c_str());
	pElem_dwPos->SetAttribute("comment", ToUTF8Ptr("坐骑位置1表示骑乘"));
	if(rElement.LinkEndChild(pElem_dwPos.get()) != NULL)
		pElem_dwPos.release();
	unique_ptr<TiXmlElement> pElem_dwModelID(new TiXmlElement("UINT32"));
	if(pElem_dwModelID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwModelID->SetAttribute("name", "dwModelID");
	pElem_dwModelID->SetAttribute("value", NumberToString(s.dwModelID).c_str());
	pElem_dwModelID->SetAttribute("comment", ToUTF8Ptr("坐骑模型id"));
	if(rElement.LinkEndChild(pElem_dwModelID.get()) != NULL)
		pElem_dwModelID.release();
	unique_ptr<TiXmlElement> pElem_dwExp(new TiXmlElement("UINT32"));
	if(pElem_dwExp == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwExp->SetAttribute("name", "dwExp");
	pElem_dwExp->SetAttribute("value", NumberToString(s.dwExp).c_str());
	pElem_dwExp->SetAttribute("comment", ToUTF8Ptr("坐骑当前经验"));
	if(rElement.LinkEndChild(pElem_dwExp.get()) != NULL)
		pElem_dwExp.release();
	unique_ptr<TiXmlElement> pElem_dwLock(new TiXmlElement("UINT32"));
	if(pElem_dwLock == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwLock->SetAttribute("name", "dwLock");
	pElem_dwLock->SetAttribute("value", NumberToString(s.dwLock).c_str());
	pElem_dwLock->SetAttribute("comment", ToUTF8Ptr("坐骑技能锁定"));
	if(rElement.LinkEndChild(pElem_dwLock.get()) != NULL)
		pElem_dwLock.release();
	unique_ptr<TiXmlElement> pElem_strModel(new TiXmlElement("string"));
	if(pElem_strModel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strModel->SetAttribute("name", "strModel");
	pElem_strModel->SetAttribute("value", s.strModel.c_str());
	pElem_strModel->SetAttribute("comment", ToUTF8Ptr("坐骑外观列表"));
	if(rElement.LinkEndChild(pElem_strModel.get()) != NULL)
		pElem_strModel.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecHorseDB& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SHorseDB s;
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

bool VectorToXML(const TVecHorseDB& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SHorseDB"));
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

SHorseInfo::SHorseInfo() : dwHorseID(0), dwHorseLevel(0), dwExp(0), dwPos(0) { }

SHorseInfo::SHorseInfo(UINT32 dwHorseID_, UINT32 dwHorseLevel_, UINT32 dwExp_, UINT32 dwPos_, const TVecUINT32& vecHorseID_)
			: dwHorseID(dwHorseID_), dwHorseLevel(dwHorseLevel_), dwExp(dwExp_), dwPos(dwPos_), vecHorseID(vecHorseID_) { }

CInArchive& operator>>(CInArchive& src, SHorseInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.dwHorseID;
	src >> s.dwHorseLevel;
	src >> s.dwExp;
	src >> s.dwPos;
	src >> s.vecHorseID;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SHorseInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.dwHorseID;
	src << s.dwHorseLevel;
	src << s.dwExp;
	src << s.dwPos;
	src << s.vecHorseID;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SHorseInfo& s)
{
	if(strcmp(rElement.Value(), "SHorseInfo") != 0)
	{
		LOG_CRI << "rElement is not SHorseInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwHorseID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwHorseID") != 0)
	{
		LOG_CRI << "Attribute: name is not dwHorseID!";
		return false;
	}
	const char* pszVal_dwHorseID = pElemChild->Attribute("value");
	if(pszVal_dwHorseID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwHorseID, s.dwHorseID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwHorseLevel is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwHorseLevel") != 0)
	{
		LOG_CRI << "Attribute: name is not dwHorseLevel!";
		return false;
	}
	const char* pszVal_dwHorseLevel = pElemChild->Attribute("value");
	if(pszVal_dwHorseLevel == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwHorseLevel, s.dwHorseLevel))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwExp is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwExp") != 0)
	{
		LOG_CRI << "Attribute: name is not dwExp!";
		return false;
	}
	const char* pszVal_dwExp = pElemChild->Attribute("value");
	if(pszVal_dwExp == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwExp, s.dwExp))
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
		LOG_CRI << "pElemChild for vecHorseID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecUINT32") != 0)
	{
		LOG_CRI << "pElemChild is not TVecUINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecHorseID") != 0)
	{
		LOG_CRI << "Attribute: name is not vecHorseID!";
		return false;
	}
	const char* pszText_vecHorseID = pElemChild->GetText();
	if(pszText_vecHorseID != NULL)
		SplitToNumber(pszText_vecHorseID, ",", s.vecHorseID);
	return true;
}

bool ToXML(const SHorseInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SHorseInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("坐骑信息"));
	unique_ptr<TiXmlElement> pElem_dwHorseID(new TiXmlElement("UINT32"));
	if(pElem_dwHorseID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwHorseID->SetAttribute("name", "dwHorseID");
	pElem_dwHorseID->SetAttribute("value", NumberToString(s.dwHorseID).c_str());
	pElem_dwHorseID->SetAttribute("comment", ToUTF8Ptr("坐骑id"));
	if(rElement.LinkEndChild(pElem_dwHorseID.get()) != NULL)
		pElem_dwHorseID.release();
	unique_ptr<TiXmlElement> pElem_dwHorseLevel(new TiXmlElement("UINT32"));
	if(pElem_dwHorseLevel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwHorseLevel->SetAttribute("name", "dwHorseLevel");
	pElem_dwHorseLevel->SetAttribute("value", NumberToString(s.dwHorseLevel).c_str());
	pElem_dwHorseLevel->SetAttribute("comment", ToUTF8Ptr("坐骑等阶"));
	if(rElement.LinkEndChild(pElem_dwHorseLevel.get()) != NULL)
		pElem_dwHorseLevel.release();
	unique_ptr<TiXmlElement> pElem_dwExp(new TiXmlElement("UINT32"));
	if(pElem_dwExp == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwExp->SetAttribute("name", "dwExp");
	pElem_dwExp->SetAttribute("value", NumberToString(s.dwExp).c_str());
	pElem_dwExp->SetAttribute("comment", ToUTF8Ptr("坐骑当前经验"));
	if(rElement.LinkEndChild(pElem_dwExp.get()) != NULL)
		pElem_dwExp.release();
	unique_ptr<TiXmlElement> pElem_dwPos(new TiXmlElement("UINT32"));
	if(pElem_dwPos == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwPos->SetAttribute("name", "dwPos");
	pElem_dwPos->SetAttribute("value", NumberToString(s.dwPos).c_str());
	pElem_dwPos->SetAttribute("comment", ToUTF8Ptr("骑乘状态"));
	if(rElement.LinkEndChild(pElem_dwPos.get()) != NULL)
		pElem_dwPos.release();
	unique_ptr<TiXmlElement> pElem_vecHorseID(new TiXmlElement("TVecUINT32"));
	if(pElem_vecHorseID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecHorseID->SetAttribute("name", "vecHorseID");
	string strText_vecHorseID;
	for(size_t i = 0; i < s.vecHorseID.size(); ++i)
	{
		if(i > 0)
			strText_vecHorseID += ", ";
		strText_vecHorseID += NumberToString(s.vecHorseID[i]);
	}
	unique_ptr<TiXmlText> pText_vecHorseID(new TiXmlText(strText_vecHorseID.c_str()));
	if(pText_vecHorseID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(pElem_vecHorseID->LinkEndChild(pText_vecHorseID.get()) != NULL)
		pText_vecHorseID.release();
	pElem_vecHorseID->SetAttribute("comment", ToUTF8Ptr("坐骑外观列表"));
	if(rElement.LinkEndChild(pElem_vecHorseID.get()) != NULL)
		pElem_vecHorseID.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecHorseInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SHorseInfo s;
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

bool VectorToXML(const TVecHorseInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SHorseInfo"));
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

SAttrInfo::SAttrInfo() : dwAttrType(0), fAttrValue(0) { }

SAttrInfo::SAttrInfo(UINT32 dwAttrType_, float fAttrValue_) : dwAttrType(dwAttrType_), fAttrValue(fAttrValue_) { }

CInArchive& operator>>(CInArchive& src, SAttrInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.dwAttrType;
	src >> s.fAttrValue;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SAttrInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.dwAttrType;
	src << s.fAttrValue;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SAttrInfo& s)
{
	if(strcmp(rElement.Value(), "SAttrInfo") != 0)
	{
		LOG_CRI << "rElement is not SAttrInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwAttrType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwAttrType") != 0)
	{
		LOG_CRI << "Attribute: name is not dwAttrType!";
		return false;
	}
	const char* pszVal_dwAttrType = pElemChild->Attribute("value");
	if(pszVal_dwAttrType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwAttrType, s.dwAttrType))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for fAttrValue is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "float") != 0)
	{
		LOG_CRI << "pElemChild is not float!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "fAttrValue") != 0)
	{
		LOG_CRI << "Attribute: name is not fAttrValue!";
		return false;
	}
	const char* pszVal_fAttrValue = pElemChild->Attribute("value");
	if(pszVal_fAttrValue == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_fAttrValue, s.fAttrValue))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SAttrInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SAttrInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("属性信息表"));
	unique_ptr<TiXmlElement> pElem_dwAttrType(new TiXmlElement("UINT32"));
	if(pElem_dwAttrType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwAttrType->SetAttribute("name", "dwAttrType");
	pElem_dwAttrType->SetAttribute("value", NumberToString(s.dwAttrType).c_str());
	pElem_dwAttrType->SetAttribute("comment", ToUTF8Ptr("属性类型id"));
	if(rElement.LinkEndChild(pElem_dwAttrType.get()) != NULL)
		pElem_dwAttrType.release();
	unique_ptr<TiXmlElement> pElem_fAttrValue(new TiXmlElement("float"));
	if(pElem_fAttrValue == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_fAttrValue->SetAttribute("name", "fAttrValue");
	pElem_fAttrValue->SetAttribute("value", NumberToString(s.fAttrValue).c_str());
	pElem_fAttrValue->SetAttribute("comment", ToUTF8Ptr("属性值"));
	if(rElement.LinkEndChild(pElem_fAttrValue.get()) != NULL)
		pElem_fAttrValue.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecAttrInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SAttrInfo s;
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

bool VectorToXML(const TVecAttrInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SAttrInfo"));
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

} //namespace NHorse
