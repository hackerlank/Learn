/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    Game2DBComm.cpp
//  Purpose:      GameServer到DBServer的通信协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "Game2DBComm.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NGame2DBComm
{

#ifdef PROT_USE_XML

const char* EnumValToStr(ESaveType e)
{
	switch(e)
	{
	case eSaveNone:
		return "eSaveNone";
	case eSaveAway:
		return "eSaveAway";
	case eSaveOff:
		return "eSaveOff";
	case eSaveJump:
		return "eSaveJump";
	case eSaveKick:
		return "eSaveKick";
	case eSaveExcept:
		return "eSaveExcept";
	case eSaveData:
		return "eSaveData";
	case eSaveToCross:
		return "eSaveToCross";
	case eSaveFromCross:
		return "eSaveFromCross";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, ESaveType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, ESaveType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eSaveNone", eSaveNone));
		mapStr2Val.insert(make_pair("eSaveAway", eSaveAway));
		mapStr2Val.insert(make_pair("eSaveOff", eSaveOff));
		mapStr2Val.insert(make_pair("eSaveJump", eSaveJump));
		mapStr2Val.insert(make_pair("eSaveKick", eSaveKick));
		mapStr2Val.insert(make_pair("eSaveExcept", eSaveExcept));
		mapStr2Val.insert(make_pair("eSaveData", eSaveData));
		mapStr2Val.insert(make_pair("eSaveToCross", eSaveToCross));
		mapStr2Val.insert(make_pair("eSaveFromCross", eSaveFromCross));
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

const char* EnumValToStr(EEnterType e)
{
	switch(e)
	{
	case eEnterNone:
		return "eEnterNone";
	case eEnterLogin:
		return "eEnterLogin";
	case eEnterJump:
		return "eEnterJump";
	case eEnterToCross:
		return "eEnterToCross";
	case eEnterFromCross:
		return "eEnterFromCross";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EEnterType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EEnterType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eEnterNone", eEnterNone));
		mapStr2Val.insert(make_pair("eEnterLogin", eEnterLogin));
		mapStr2Val.insert(make_pair("eEnterJump", eEnterJump));
		mapStr2Val.insert(make_pair("eEnterToCross", eEnterToCross));
		mapStr2Val.insert(make_pair("eEnterFromCross", eEnterFromCross));
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

SWBossDBInfo::SWBossDBInfo() : wBossID(0), dwLast(0), dwHP(0), dwAtk(0), dwMAtk(0), 
			dwLastEndTime(0) { }

SWBossDBInfo::SWBossDBInfo(UINT16 wBossID_, UINT32 dwLast_, UINT32 dwHP_, UINT32 dwAtk_, UINT32 dwMAtk_, 
			UINT32 dwLastEndTime_)
			: wBossID(wBossID_), dwLast(dwLast_), dwHP(dwHP_), dwAtk(dwAtk_), dwMAtk(dwMAtk_), 
			dwLastEndTime(dwLastEndTime_) { }

CInArchive& operator>>(CInArchive& src, SWBossDBInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.wBossID;
	src >> s.dwLast;
	src >> s.dwHP;
	src >> s.dwAtk;
	src >> s.dwMAtk;
	src >> s.dwLastEndTime;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SWBossDBInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.wBossID;
	src << s.dwLast;
	src << s.dwHP;
	src << s.dwAtk;
	src << s.dwMAtk;
	src << s.dwLastEndTime;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SWBossDBInfo& s)
{
	if(strcmp(rElement.Value(), "SWBossDBInfo") != 0)
	{
		LOG_CRI << "rElement is not SWBossDBInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wBossID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wBossID") != 0)
	{
		LOG_CRI << "Attribute: name is not wBossID!";
		return false;
	}
	const char* pszVal_wBossID = pElemChild->Attribute("value");
	if(pszVal_wBossID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wBossID, s.wBossID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwLast is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwLast") != 0)
	{
		LOG_CRI << "Attribute: name is not dwLast!";
		return false;
	}
	const char* pszVal_dwLast = pElemChild->Attribute("value");
	if(pszVal_dwLast == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwLast, s.dwLast))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwHP is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwHP") != 0)
	{
		LOG_CRI << "Attribute: name is not dwHP!";
		return false;
	}
	const char* pszVal_dwHP = pElemChild->Attribute("value");
	if(pszVal_dwHP == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwHP, s.dwHP))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwAtk is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwAtk") != 0)
	{
		LOG_CRI << "Attribute: name is not dwAtk!";
		return false;
	}
	const char* pszVal_dwAtk = pElemChild->Attribute("value");
	if(pszVal_dwAtk == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwAtk, s.dwAtk))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwMAtk is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwMAtk") != 0)
	{
		LOG_CRI << "Attribute: name is not dwMAtk!";
		return false;
	}
	const char* pszVal_dwMAtk = pElemChild->Attribute("value");
	if(pszVal_dwMAtk == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwMAtk, s.dwMAtk))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwLastEndTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwLastEndTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwLastEndTime!";
		return false;
	}
	const char* pszVal_dwLastEndTime = pElemChild->Attribute("value");
	if(pszVal_dwLastEndTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwLastEndTime, s.dwLastEndTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SWBossDBInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SWBossDBInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("EDataType:eTypeWorldBossInfo"));
	unique_ptr<TiXmlElement> pElem_wBossID(new TiXmlElement("UINT16"));
	if(pElem_wBossID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wBossID->SetAttribute("name", "wBossID");
	pElem_wBossID->SetAttribute("value", NumberToString(s.wBossID).c_str());
	pElem_wBossID->SetAttribute("comment", ToUTF8Ptr("BOSSID"));
	if(rElement.LinkEndChild(pElem_wBossID.get()) != NULL)
		pElem_wBossID.release();
	unique_ptr<TiXmlElement> pElem_dwLast(new TiXmlElement("UINT32"));
	if(pElem_dwLast == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwLast->SetAttribute("name", "dwLast");
	pElem_dwLast->SetAttribute("value", NumberToString(s.dwLast).c_str());
	pElem_dwLast->SetAttribute("comment", ToUTF8Ptr("次被击杀所用时长，单位秒"));
	if(rElement.LinkEndChild(pElem_dwLast.get()) != NULL)
		pElem_dwLast.release();
	unique_ptr<TiXmlElement> pElem_dwHP(new TiXmlElement("UINT32"));
	if(pElem_dwHP == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwHP->SetAttribute("name", "dwHP");
	pElem_dwHP->SetAttribute("value", NumberToString(s.dwHP).c_str());
	pElem_dwHP->SetAttribute("comment", ToUTF8Ptr("上次最大血量"));
	if(rElement.LinkEndChild(pElem_dwHP.get()) != NULL)
		pElem_dwHP.release();
	unique_ptr<TiXmlElement> pElem_dwAtk(new TiXmlElement("UINT32"));
	if(pElem_dwAtk == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwAtk->SetAttribute("name", "dwAtk");
	pElem_dwAtk->SetAttribute("value", NumberToString(s.dwAtk).c_str());
	pElem_dwAtk->SetAttribute("comment", ToUTF8Ptr("上次物理攻击力"));
	if(rElement.LinkEndChild(pElem_dwAtk.get()) != NULL)
		pElem_dwAtk.release();
	unique_ptr<TiXmlElement> pElem_dwMAtk(new TiXmlElement("UINT32"));
	if(pElem_dwMAtk == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwMAtk->SetAttribute("name", "dwMAtk");
	pElem_dwMAtk->SetAttribute("value", NumberToString(s.dwMAtk).c_str());
	pElem_dwMAtk->SetAttribute("comment", ToUTF8Ptr("上次魔法攻击力"));
	if(rElement.LinkEndChild(pElem_dwMAtk.get()) != NULL)
		pElem_dwMAtk.release();
	unique_ptr<TiXmlElement> pElem_dwLastEndTime(new TiXmlElement("UINT32"));
	if(pElem_dwLastEndTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwLastEndTime->SetAttribute("name", "dwLastEndTime");
	pElem_dwLastEndTime->SetAttribute("value", NumberToString(s.dwLastEndTime).c_str());
	pElem_dwLastEndTime->SetAttribute("comment", ToUTF8Ptr("上次结束时间"));
	if(rElement.LinkEndChild(pElem_dwLastEndTime.get()) != NULL)
		pElem_dwLastEndTime.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecWBossDBInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SWBossDBInfo s;
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

bool VectorToXML(const TVecWBossDBInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SWBossDBInfo"));
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

SDBGuildNewBattleHistoryInfo::SDBGuildNewBattleHistoryInfo() : byMountainType(0), qwGuildID(0), dwTime(0) { }

SDBGuildNewBattleHistoryInfo::SDBGuildNewBattleHistoryInfo(UINT8 byMountainType_, UINT64 qwGuildID_, const std::string& strGuildName_, const std::string& strGuildOwnerName_, UINT32 dwTime_)
			: byMountainType(byMountainType_), qwGuildID(qwGuildID_), strGuildName(strGuildName_), strGuildOwnerName(strGuildOwnerName_), dwTime(dwTime_) { }

SDBGuildNewBattleHistoryInfo::SDBGuildNewBattleHistoryInfo(SDBGuildNewBattleHistoryInfo&& src) : byMountainType(src.byMountainType), qwGuildID(src.qwGuildID), strGuildName(move(src.strGuildName)), strGuildOwnerName(move(src.strGuildOwnerName)), dwTime(src.dwTime) { }

SDBGuildNewBattleHistoryInfo& SDBGuildNewBattleHistoryInfo::operator=(SDBGuildNewBattleHistoryInfo&& rhs)
{
	if(this != &rhs)
	{
		this->~SDBGuildNewBattleHistoryInfo();
		new (this) SDBGuildNewBattleHistoryInfo(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SDBGuildNewBattleHistoryInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.byMountainType;
	src >> s.qwGuildID;
	src >> s.strGuildName;
	src >> s.strGuildOwnerName;
	src >> s.dwTime;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SDBGuildNewBattleHistoryInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.byMountainType;
	src << s.qwGuildID;
	src << s.strGuildName;
	src << s.strGuildOwnerName;
	src << s.dwTime;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SDBGuildNewBattleHistoryInfo& s)
{
	if(strcmp(rElement.Value(), "SDBGuildNewBattleHistoryInfo") != 0)
	{
		LOG_CRI << "rElement is not SDBGuildNewBattleHistoryInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byMountainType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byMountainType") != 0)
	{
		LOG_CRI << "Attribute: name is not byMountainType!";
		return false;
	}
	const char* pszVal_byMountainType = pElemChild->Attribute("value");
	if(pszVal_byMountainType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byMountainType, s.byMountainType))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwGuildID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwGuildID") != 0)
	{
		LOG_CRI << "Attribute: name is not qwGuildID!";
		return false;
	}
	const char* pszVal_qwGuildID = pElemChild->Attribute("value");
	if(pszVal_qwGuildID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwGuildID, s.qwGuildID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strGuildName is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strGuildName") != 0)
	{
		LOG_CRI << "Attribute: name is not strGuildName!";
		return false;
	}
	const char* pszVal_strGuildName = pElemChild->Attribute("value");
	if(pszVal_strGuildName == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strGuildName = pszVal_strGuildName;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strGuildOwnerName is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strGuildOwnerName") != 0)
	{
		LOG_CRI << "Attribute: name is not strGuildOwnerName!";
		return false;
	}
	const char* pszVal_strGuildOwnerName = pElemChild->Attribute("value");
	if(pszVal_strGuildOwnerName == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strGuildOwnerName = pszVal_strGuildOwnerName;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwTime!";
		return false;
	}
	const char* pszVal_dwTime = pElemChild->Attribute("value");
	if(pszVal_dwTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwTime, s.dwTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SDBGuildNewBattleHistoryInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SDBGuildNewBattleHistoryInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("数据库加载的新帮派战历史信息"));
	unique_ptr<TiXmlElement> pElem_byMountainType(new TiXmlElement("UINT8"));
	if(pElem_byMountainType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byMountainType->SetAttribute("name", "byMountainType");
	pElem_byMountainType->SetAttribute("value", NumberToString(s.byMountainType).c_str());
	pElem_byMountainType->SetAttribute("comment", ToUTF8Ptr("灵山类型"));
	if(rElement.LinkEndChild(pElem_byMountainType.get()) != NULL)
		pElem_byMountainType.release();
	unique_ptr<TiXmlElement> pElem_qwGuildID(new TiXmlElement("UINT64"));
	if(pElem_qwGuildID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwGuildID->SetAttribute("name", "qwGuildID");
	pElem_qwGuildID->SetAttribute("value", NumberToString(s.qwGuildID).c_str());
	pElem_qwGuildID->SetAttribute("comment", ToUTF8Ptr("当前占领帮派ID"));
	if(rElement.LinkEndChild(pElem_qwGuildID.get()) != NULL)
		pElem_qwGuildID.release();
	unique_ptr<TiXmlElement> pElem_strGuildName(new TiXmlElement("string"));
	if(pElem_strGuildName == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strGuildName->SetAttribute("name", "strGuildName");
	pElem_strGuildName->SetAttribute("value", s.strGuildName.c_str());
	pElem_strGuildName->SetAttribute("comment", ToUTF8Ptr("当前占领帮派名称"));
	if(rElement.LinkEndChild(pElem_strGuildName.get()) != NULL)
		pElem_strGuildName.release();
	unique_ptr<TiXmlElement> pElem_strGuildOwnerName(new TiXmlElement("string"));
	if(pElem_strGuildOwnerName == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strGuildOwnerName->SetAttribute("name", "strGuildOwnerName");
	pElem_strGuildOwnerName->SetAttribute("value", s.strGuildOwnerName.c_str());
	pElem_strGuildOwnerName->SetAttribute("comment", ToUTF8Ptr("当前占领帮派帮主名称"));
	if(rElement.LinkEndChild(pElem_strGuildOwnerName.get()) != NULL)
		pElem_strGuildOwnerName.release();
	unique_ptr<TiXmlElement> pElem_dwTime(new TiXmlElement("UINT32"));
	if(pElem_dwTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwTime->SetAttribute("name", "dwTime");
	pElem_dwTime->SetAttribute("value", NumberToString(s.dwTime).c_str());
	pElem_dwTime->SetAttribute("comment", ToUTF8Ptr("占领时间"));
	if(rElement.LinkEndChild(pElem_dwTime.get()) != NULL)
		pElem_dwTime.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecDBGuildNewBattleHistoryInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SDBGuildNewBattleHistoryInfo s;
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

bool VectorToXML(const TVecDBGuildNewBattleHistoryInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SDBGuildNewBattleHistoryInfo"));
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

} //namespace NGame2DBComm
