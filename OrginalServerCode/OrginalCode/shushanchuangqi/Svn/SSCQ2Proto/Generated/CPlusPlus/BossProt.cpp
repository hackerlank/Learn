/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    BossProt.cpp
//  Purpose:      BOSS相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "BossProt.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NBossProt
{

#ifdef PROT_USE_XML

const char* EnumValToStr(EBossBuyType e)
{
	switch(e)
	{
	case eGold:
		return "eGold";
	case eSliver:
		return "eSliver";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EBossBuyType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EBossBuyType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eGold", eGold));
		mapStr2Val.insert(make_pair("eSliver", eSliver));
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

const char* EnumValToStr(EWorldBossPrize e)
{
	switch(e)
	{
	case eWorldBossPrizeTop:
		return "eWorldBossPrizeTop";
	case eWorldBossPrizeDamage:
		return "eWorldBossPrizeDamage";
	case eWorldBossPrizeRandom:
		return "eWorldBossPrizeRandom";
	case eWorldBossPrizeNPC:
		return "eWorldBossPrizeNPC";
	case eWorldBossPrizeKillBoss:
		return "eWorldBossPrizeKillBoss";
	case eWorldBossPrizeBossHP:
		return "eWorldBossPrizeBossHP";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EWorldBossPrize& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EWorldBossPrize> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eWorldBossPrizeTop", eWorldBossPrizeTop));
		mapStr2Val.insert(make_pair("eWorldBossPrizeDamage", eWorldBossPrizeDamage));
		mapStr2Val.insert(make_pair("eWorldBossPrizeRandom", eWorldBossPrizeRandom));
		mapStr2Val.insert(make_pair("eWorldBossPrizeNPC", eWorldBossPrizeNPC));
		mapStr2Val.insert(make_pair("eWorldBossPrizeKillBoss", eWorldBossPrizeKillBoss));
		mapStr2Val.insert(make_pair("eWorldBossPrizeBossHP", eWorldBossPrizeBossHP));
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

SPlayerInfo::SPlayerInfo() : dwNo(0), qwUserID(0), dwDamageHP(0), dwBossMaxHP(0) { }

SPlayerInfo::SPlayerInfo(UINT32 dwNo_, UINT64 qwUserID_, const std::string& strUserName_, UINT32 dwDamageHP_, UINT32 dwBossMaxHP_)
			: dwNo(dwNo_), qwUserID(qwUserID_), strUserName(strUserName_), dwDamageHP(dwDamageHP_), dwBossMaxHP(dwBossMaxHP_) { }

SPlayerInfo::SPlayerInfo(SPlayerInfo&& src) : dwNo(src.dwNo), qwUserID(src.qwUserID), strUserName(move(src.strUserName)), dwDamageHP(src.dwDamageHP), dwBossMaxHP(src.dwBossMaxHP) { }

SPlayerInfo& SPlayerInfo::operator=(SPlayerInfo&& rhs)
{
	if(this != &rhs)
	{
		this->~SPlayerInfo();
		new (this) SPlayerInfo(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SPlayerInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.dwNo;
	src >> s.qwUserID;
	src >> s.strUserName;
	src >> s.dwDamageHP;
	src >> s.dwBossMaxHP;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SPlayerInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.dwNo;
	src << s.qwUserID;
	src << s.strUserName;
	src << s.dwDamageHP;
	src << s.dwBossMaxHP;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SPlayerInfo& s)
{
	if(strcmp(rElement.Value(), "SPlayerInfo") != 0)
	{
		LOG_CRI << "rElement is not SPlayerInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwNo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwNo") != 0)
	{
		LOG_CRI << "Attribute: name is not dwNo!";
		return false;
	}
	const char* pszVal_dwNo = pElemChild->Attribute("value");
	if(pszVal_dwNo == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwNo, s.dwNo))
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
		LOG_CRI << "pElemChild for strUserName is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strUserName") != 0)
	{
		LOG_CRI << "Attribute: name is not strUserName!";
		return false;
	}
	const char* pszVal_strUserName = pElemChild->Attribute("value");
	if(pszVal_strUserName == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strUserName = pszVal_strUserName;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwDamageHP is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwDamageHP") != 0)
	{
		LOG_CRI << "Attribute: name is not dwDamageHP!";
		return false;
	}
	const char* pszVal_dwDamageHP = pElemChild->Attribute("value");
	if(pszVal_dwDamageHP == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwDamageHP, s.dwDamageHP))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwBossMaxHP is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwBossMaxHP") != 0)
	{
		LOG_CRI << "Attribute: name is not dwBossMaxHP!";
		return false;
	}
	const char* pszVal_dwBossMaxHP = pElemChild->Attribute("value");
	if(pszVal_dwBossMaxHP == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwBossMaxHP, s.dwBossMaxHP))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SPlayerInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SPlayerInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("排行帮信息"));
	unique_ptr<TiXmlElement> pElem_dwNo(new TiXmlElement("UINT32"));
	if(pElem_dwNo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwNo->SetAttribute("name", "dwNo");
	pElem_dwNo->SetAttribute("value", NumberToString(s.dwNo).c_str());
	pElem_dwNo->SetAttribute("comment", ToUTF8Ptr("名次"));
	if(rElement.LinkEndChild(pElem_dwNo.get()) != NULL)
		pElem_dwNo.release();
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
	unique_ptr<TiXmlElement> pElem_strUserName(new TiXmlElement("string"));
	if(pElem_strUserName == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strUserName->SetAttribute("name", "strUserName");
	pElem_strUserName->SetAttribute("value", s.strUserName.c_str());
	pElem_strUserName->SetAttribute("comment", ToUTF8Ptr("玩家名字"));
	if(rElement.LinkEndChild(pElem_strUserName.get()) != NULL)
		pElem_strUserName.release();
	unique_ptr<TiXmlElement> pElem_dwDamageHP(new TiXmlElement("UINT32"));
	if(pElem_dwDamageHP == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwDamageHP->SetAttribute("name", "dwDamageHP");
	pElem_dwDamageHP->SetAttribute("value", NumberToString(s.dwDamageHP).c_str());
	pElem_dwDamageHP->SetAttribute("comment", ToUTF8Ptr("伤害的总血量"));
	if(rElement.LinkEndChild(pElem_dwDamageHP.get()) != NULL)
		pElem_dwDamageHP.release();
	unique_ptr<TiXmlElement> pElem_dwBossMaxHP(new TiXmlElement("UINT32"));
	if(pElem_dwBossMaxHP == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwBossMaxHP->SetAttribute("name", "dwBossMaxHP");
	pElem_dwBossMaxHP->SetAttribute("value", NumberToString(s.dwBossMaxHP).c_str());
	pElem_dwBossMaxHP->SetAttribute("comment", ToUTF8Ptr("Boss的总血量"));
	if(rElement.LinkEndChild(pElem_dwBossMaxHP.get()) != NULL)
		pElem_dwBossMaxHP.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecPlayerInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SPlayerInfo s;
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

bool VectorToXML(const TVecPlayerInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SPlayerInfo"));
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

SPrizeMoneyInfo::SPrizeMoneyInfo() : dwMoneyType(0), dwMoneyValue(0) { }

SPrizeMoneyInfo::SPrizeMoneyInfo(UINT32 dwMoneyType_, UINT32 dwMoneyValue_) : dwMoneyType(dwMoneyType_), dwMoneyValue(dwMoneyValue_) { }

CInArchive& operator>>(CInArchive& src, SPrizeMoneyInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.dwMoneyType;
	src >> s.dwMoneyValue;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SPrizeMoneyInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.dwMoneyType;
	src << s.dwMoneyValue;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SPrizeMoneyInfo& s)
{
	if(strcmp(rElement.Value(), "SPrizeMoneyInfo") != 0)
	{
		LOG_CRI << "rElement is not SPrizeMoneyInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwMoneyType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwMoneyType") != 0)
	{
		LOG_CRI << "Attribute: name is not dwMoneyType!";
		return false;
	}
	const char* pszVal_dwMoneyType = pElemChild->Attribute("value");
	if(pszVal_dwMoneyType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwMoneyType, s.dwMoneyType))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwMoneyValue is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwMoneyValue") != 0)
	{
		LOG_CRI << "Attribute: name is not dwMoneyValue!";
		return false;
	}
	const char* pszVal_dwMoneyValue = pElemChild->Attribute("value");
	if(pszVal_dwMoneyValue == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwMoneyValue, s.dwMoneyValue))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SPrizeMoneyInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SPrizeMoneyInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("货币列表"));
	unique_ptr<TiXmlElement> pElem_dwMoneyType(new TiXmlElement("UINT32"));
	if(pElem_dwMoneyType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwMoneyType->SetAttribute("name", "dwMoneyType");
	pElem_dwMoneyType->SetAttribute("value", NumberToString(s.dwMoneyType).c_str());
	pElem_dwMoneyType->SetAttribute("comment", ToUTF8Ptr("货币类型"));
	if(rElement.LinkEndChild(pElem_dwMoneyType.get()) != NULL)
		pElem_dwMoneyType.release();
	unique_ptr<TiXmlElement> pElem_dwMoneyValue(new TiXmlElement("UINT32"));
	if(pElem_dwMoneyValue == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwMoneyValue->SetAttribute("name", "dwMoneyValue");
	pElem_dwMoneyValue->SetAttribute("value", NumberToString(s.dwMoneyValue).c_str());
	pElem_dwMoneyValue->SetAttribute("comment", ToUTF8Ptr("货币值"));
	if(rElement.LinkEndChild(pElem_dwMoneyValue.get()) != NULL)
		pElem_dwMoneyValue.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecPrizeMoneyInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SPrizeMoneyInfo s;
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

bool VectorToXML(const TVecPrizeMoneyInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SPrizeMoneyInfo"));
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

SPrizeIteminfo::SPrizeIteminfo() : dwItemID(0), dwItemCount(0) { }

SPrizeIteminfo::SPrizeIteminfo(UINT32 dwItemID_, UINT32 dwItemCount_) : dwItemID(dwItemID_), dwItemCount(dwItemCount_) { }

CInArchive& operator>>(CInArchive& src, SPrizeIteminfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.dwItemID;
	src >> s.dwItemCount;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SPrizeIteminfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.dwItemID;
	src << s.dwItemCount;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SPrizeIteminfo& s)
{
	if(strcmp(rElement.Value(), "SPrizeIteminfo") != 0)
	{
		LOG_CRI << "rElement is not SPrizeIteminfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwItemID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwItemID") != 0)
	{
		LOG_CRI << "Attribute: name is not dwItemID!";
		return false;
	}
	const char* pszVal_dwItemID = pElemChild->Attribute("value");
	if(pszVal_dwItemID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwItemID, s.dwItemID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwItemCount is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwItemCount") != 0)
	{
		LOG_CRI << "Attribute: name is not dwItemCount!";
		return false;
	}
	const char* pszVal_dwItemCount = pElemChild->Attribute("value");
	if(pszVal_dwItemCount == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwItemCount, s.dwItemCount))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SPrizeIteminfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SPrizeIteminfo");
	rElement.SetAttribute("type", ToUTF8Ptr("货币列表"));
	unique_ptr<TiXmlElement> pElem_dwItemID(new TiXmlElement("UINT32"));
	if(pElem_dwItemID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwItemID->SetAttribute("name", "dwItemID");
	pElem_dwItemID->SetAttribute("value", NumberToString(s.dwItemID).c_str());
	pElem_dwItemID->SetAttribute("comment", ToUTF8Ptr("物品id"));
	if(rElement.LinkEndChild(pElem_dwItemID.get()) != NULL)
		pElem_dwItemID.release();
	unique_ptr<TiXmlElement> pElem_dwItemCount(new TiXmlElement("UINT32"));
	if(pElem_dwItemCount == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwItemCount->SetAttribute("name", "dwItemCount");
	pElem_dwItemCount->SetAttribute("value", NumberToString(s.dwItemCount).c_str());
	pElem_dwItemCount->SetAttribute("comment", ToUTF8Ptr("物品数量"));
	if(rElement.LinkEndChild(pElem_dwItemCount.get()) != NULL)
		pElem_dwItemCount.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecPrizeItemInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SPrizeIteminfo s;
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

bool VectorToXML(const TVecPrizeItemInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SPrizeIteminfo"));
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

SPlayerPrize::SPlayerPrize() : dwPrizeType(0) { }

SPlayerPrize::SPlayerPrize(UINT8 dwPrizeType_, const TVecPrizeMoneyInfo& vecPrizeMoneyInfo_, const TVecPrizeItemInfo& vecPrizeItemInfo_) : dwPrizeType(dwPrizeType_), vecPrizeMoneyInfo(vecPrizeMoneyInfo_), vecPrizeItemInfo(vecPrizeItemInfo_) { }

SPlayerPrize::SPlayerPrize(SPlayerPrize&& src) : dwPrizeType(src.dwPrizeType), vecPrizeMoneyInfo(move(src.vecPrizeMoneyInfo)), vecPrizeItemInfo(move(src.vecPrizeItemInfo)) { }

SPlayerPrize& SPlayerPrize::operator=(SPlayerPrize&& rhs)
{
	if(this != &rhs)
	{
		this->~SPlayerPrize();
		new (this) SPlayerPrize(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SPlayerPrize& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.dwPrizeType;
	src >> s.vecPrizeMoneyInfo;
	src >> s.vecPrizeItemInfo;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SPlayerPrize& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.dwPrizeType;
	src << s.vecPrizeMoneyInfo;
	src << s.vecPrizeItemInfo;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SPlayerPrize& s)
{
	if(strcmp(rElement.Value(), "SPlayerPrize") != 0)
	{
		LOG_CRI << "rElement is not SPlayerPrize!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwPrizeType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwPrizeType") != 0)
	{
		LOG_CRI << "Attribute: name is not dwPrizeType!";
		return false;
	}
	const char* pszVal_dwPrizeType = pElemChild->Attribute("value");
	if(pszVal_dwPrizeType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwPrizeType, s.dwPrizeType))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecPrizeMoneyInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecPrizeMoneyInfo") != 0)
	{
		LOG_CRI << "pElemChild is not TVecPrizeMoneyInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecPrizeMoneyInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not vecPrizeMoneyInfo!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecPrizeMoneyInfo))
	{
		LOG_CRI << "VectorFromXML for vecPrizeMoneyInfo fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecPrizeItemInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecPrizeItemInfo") != 0)
	{
		LOG_CRI << "pElemChild is not TVecPrizeItemInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecPrizeItemInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not vecPrizeItemInfo!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecPrizeItemInfo))
	{
		LOG_CRI << "VectorFromXML for vecPrizeItemInfo fails!";
		return false;
	}
	return true;
}

bool ToXML(const SPlayerPrize& s, TiXmlElement& rElement)
{
	rElement.SetValue("SPlayerPrize");
	rElement.SetAttribute("type", ToUTF8Ptr("排行帮信息"));
	unique_ptr<TiXmlElement> pElem_dwPrizeType(new TiXmlElement("UINT8"));
	if(pElem_dwPrizeType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwPrizeType->SetAttribute("name", "dwPrizeType");
	pElem_dwPrizeType->SetAttribute("value", NumberToString(s.dwPrizeType).c_str());
	pElem_dwPrizeType->SetAttribute("comment", ToUTF8Ptr("奖励类型"));
	if(rElement.LinkEndChild(pElem_dwPrizeType.get()) != NULL)
		pElem_dwPrizeType.release();
	unique_ptr<TiXmlElement> pElem_vecPrizeMoneyInfo(new TiXmlElement("TVecPrizeMoneyInfo"));
	if(pElem_vecPrizeMoneyInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecPrizeMoneyInfo->SetAttribute("name", "vecPrizeMoneyInfo");
	if(!VectorToXML(s.vecPrizeMoneyInfo, *pElem_vecPrizeMoneyInfo))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecPrizeMoneyInfo->SetAttribute("comment", ToUTF8Ptr("货币奖励"));
	if(rElement.LinkEndChild(pElem_vecPrizeMoneyInfo.get()) != NULL)
		pElem_vecPrizeMoneyInfo.release();
	unique_ptr<TiXmlElement> pElem_vecPrizeItemInfo(new TiXmlElement("TVecPrizeItemInfo"));
	if(pElem_vecPrizeItemInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecPrizeItemInfo->SetAttribute("name", "vecPrizeItemInfo");
	if(!VectorToXML(s.vecPrizeItemInfo, *pElem_vecPrizeItemInfo))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecPrizeItemInfo->SetAttribute("comment", ToUTF8Ptr("物品奖励"));
	if(rElement.LinkEndChild(pElem_vecPrizeItemInfo.get()) != NULL)
		pElem_vecPrizeItemInfo.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecPlayerPrize& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SPlayerPrize s;
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

bool VectorToXML(const TVecPlayerPrize& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SPlayerPrize"));
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

} //namespace NBossProt
