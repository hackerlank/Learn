/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    GuardEMeiProt.cpp
//  Purpose:      守卫峨眉协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "GuardEMeiProt.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NGuardEMeiProt
{

#ifdef PROT_USE_XML

const char* EnumValToStr(EGEMOptResult e)
{
	switch(e)
	{
	case eGEMOptResultFailed:
		return "eGEMOptResultFailed";
	case eGEMOptResultSucc:
		return "eGEMOptResultSucc";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EGEMOptResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EGEMOptResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eGEMOptResultFailed", eGEMOptResultFailed));
		mapStr2Val.insert(make_pair("eGEMOptResultSucc", eGEMOptResultSucc));
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

const char* EnumValToStr(EGEMBattleType e)
{
	switch(e)
	{
	case eGEMBattleTypeA:
		return "eGEMBattleTypeA";
	case eGEMBattleTypeB:
		return "eGEMBattleTypeB";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EGEMBattleType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EGEMBattleType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eGEMBattleTypeA", eGEMBattleTypeA));
		mapStr2Val.insert(make_pair("eGEMBattleTypeB", eGEMBattleTypeB));
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

const char* EnumValToStr(EGEMBattleRet e)
{
	switch(e)
	{
	case eGEMBattleFailed:
		return "eGEMBattleFailed";
	case eGEMBattleSucc:
		return "eGEMBattleSucc";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EGEMBattleRet& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EGEMBattleRet> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eGEMBattleFailed", eGEMBattleFailed));
		mapStr2Val.insert(make_pair("eGEMBattleSucc", eGEMBattleSucc));
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

SGEMBattleFighterInfo::SGEMBattleFighterInfo() : dwFighterID(0), byFighterLevel(0), byFighterColour(0), dwFighterCurHP(0), dwFighterMaxHP(0), 
			dwFighterCurAnima(0), dwFighterMaxAnima(0) { }

SGEMBattleFighterInfo::SGEMBattleFighterInfo(UINT32 dwFighterID_, UINT8 byFighterLevel_, UINT8 byFighterColour_, UINT32 dwFighterCurHP_, UINT32 dwFighterMaxHP_, 
			UINT32 dwFighterCurAnima_, UINT32 dwFighterMaxAnima_)
			: dwFighterID(dwFighterID_), byFighterLevel(byFighterLevel_), byFighterColour(byFighterColour_), dwFighterCurHP(dwFighterCurHP_), dwFighterMaxHP(dwFighterMaxHP_), 
			dwFighterCurAnima(dwFighterCurAnima_), dwFighterMaxAnima(dwFighterMaxAnima_) { }

CInArchive& operator>>(CInArchive& src, SGEMBattleFighterInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.dwFighterID;
	src >> s.byFighterLevel;
	src >> s.byFighterColour;
	src >> s.dwFighterCurHP;
	src >> s.dwFighterMaxHP;
	src >> s.dwFighterCurAnima;
	src >> s.dwFighterMaxAnima;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SGEMBattleFighterInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.dwFighterID;
	src << s.byFighterLevel;
	src << s.byFighterColour;
	src << s.dwFighterCurHP;
	src << s.dwFighterMaxHP;
	src << s.dwFighterCurAnima;
	src << s.dwFighterMaxAnima;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SGEMBattleFighterInfo& s)
{
	if(strcmp(rElement.Value(), "SGEMBattleFighterInfo") != 0)
	{
		LOG_CRI << "rElement is not SGEMBattleFighterInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwFighterID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwFighterID") != 0)
	{
		LOG_CRI << "Attribute: name is not dwFighterID!";
		return false;
	}
	const char* pszVal_dwFighterID = pElemChild->Attribute("value");
	if(pszVal_dwFighterID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwFighterID, s.dwFighterID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byFighterLevel is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byFighterLevel") != 0)
	{
		LOG_CRI << "Attribute: name is not byFighterLevel!";
		return false;
	}
	const char* pszVal_byFighterLevel = pElemChild->Attribute("value");
	if(pszVal_byFighterLevel == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byFighterLevel, s.byFighterLevel))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byFighterColour is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byFighterColour") != 0)
	{
		LOG_CRI << "Attribute: name is not byFighterColour!";
		return false;
	}
	const char* pszVal_byFighterColour = pElemChild->Attribute("value");
	if(pszVal_byFighterColour == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byFighterColour, s.byFighterColour))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwFighterCurHP is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwFighterCurHP") != 0)
	{
		LOG_CRI << "Attribute: name is not dwFighterCurHP!";
		return false;
	}
	const char* pszVal_dwFighterCurHP = pElemChild->Attribute("value");
	if(pszVal_dwFighterCurHP == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwFighterCurHP, s.dwFighterCurHP))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwFighterMaxHP is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwFighterMaxHP") != 0)
	{
		LOG_CRI << "Attribute: name is not dwFighterMaxHP!";
		return false;
	}
	const char* pszVal_dwFighterMaxHP = pElemChild->Attribute("value");
	if(pszVal_dwFighterMaxHP == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwFighterMaxHP, s.dwFighterMaxHP))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwFighterCurAnima is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwFighterCurAnima") != 0)
	{
		LOG_CRI << "Attribute: name is not dwFighterCurAnima!";
		return false;
	}
	const char* pszVal_dwFighterCurAnima = pElemChild->Attribute("value");
	if(pszVal_dwFighterCurAnima == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwFighterCurAnima, s.dwFighterCurAnima))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwFighterMaxAnima is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwFighterMaxAnima") != 0)
	{
		LOG_CRI << "Attribute: name is not dwFighterMaxAnima!";
		return false;
	}
	const char* pszVal_dwFighterMaxAnima = pElemChild->Attribute("value");
	if(pszVal_dwFighterMaxAnima == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwFighterMaxAnima, s.dwFighterMaxAnima))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SGEMBattleFighterInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SGEMBattleFighterInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("守卫峨眉参战散仙信息"));
	unique_ptr<TiXmlElement> pElem_dwFighterID(new TiXmlElement("UINT32"));
	if(pElem_dwFighterID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwFighterID->SetAttribute("name", "dwFighterID");
	pElem_dwFighterID->SetAttribute("value", NumberToString(s.dwFighterID).c_str());
	pElem_dwFighterID->SetAttribute("comment", ToUTF8Ptr("将模版ID"));
	if(rElement.LinkEndChild(pElem_dwFighterID.get()) != NULL)
		pElem_dwFighterID.release();
	unique_ptr<TiXmlElement> pElem_byFighterLevel(new TiXmlElement("UINT8"));
	if(pElem_byFighterLevel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byFighterLevel->SetAttribute("name", "byFighterLevel");
	pElem_byFighterLevel->SetAttribute("value", NumberToString(s.byFighterLevel).c_str());
	pElem_byFighterLevel->SetAttribute("comment", ToUTF8Ptr("将等级"));
	if(rElement.LinkEndChild(pElem_byFighterLevel.get()) != NULL)
		pElem_byFighterLevel.release();
	unique_ptr<TiXmlElement> pElem_byFighterColour(new TiXmlElement("UINT8"));
	if(pElem_byFighterColour == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byFighterColour->SetAttribute("name", "byFighterColour");
	pElem_byFighterColour->SetAttribute("value", NumberToString(s.byFighterColour).c_str());
	pElem_byFighterColour->SetAttribute("comment", ToUTF8Ptr("将颜色"));
	if(rElement.LinkEndChild(pElem_byFighterColour.get()) != NULL)
		pElem_byFighterColour.release();
	unique_ptr<TiXmlElement> pElem_dwFighterCurHP(new TiXmlElement("UINT32"));
	if(pElem_dwFighterCurHP == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwFighterCurHP->SetAttribute("name", "dwFighterCurHP");
	pElem_dwFighterCurHP->SetAttribute("value", NumberToString(s.dwFighterCurHP).c_str());
	pElem_dwFighterCurHP->SetAttribute("comment", ToUTF8Ptr("将当前血量"));
	if(rElement.LinkEndChild(pElem_dwFighterCurHP.get()) != NULL)
		pElem_dwFighterCurHP.release();
	unique_ptr<TiXmlElement> pElem_dwFighterMaxHP(new TiXmlElement("UINT32"));
	if(pElem_dwFighterMaxHP == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwFighterMaxHP->SetAttribute("name", "dwFighterMaxHP");
	pElem_dwFighterMaxHP->SetAttribute("value", NumberToString(s.dwFighterMaxHP).c_str());
	pElem_dwFighterMaxHP->SetAttribute("comment", ToUTF8Ptr("将最大血量"));
	if(rElement.LinkEndChild(pElem_dwFighterMaxHP.get()) != NULL)
		pElem_dwFighterMaxHP.release();
	unique_ptr<TiXmlElement> pElem_dwFighterCurAnima(new TiXmlElement("UINT32"));
	if(pElem_dwFighterCurAnima == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwFighterCurAnima->SetAttribute("name", "dwFighterCurAnima");
	pElem_dwFighterCurAnima->SetAttribute("value", NumberToString(s.dwFighterCurAnima).c_str());
	pElem_dwFighterCurAnima->SetAttribute("comment", ToUTF8Ptr("将当前灵气"));
	if(rElement.LinkEndChild(pElem_dwFighterCurAnima.get()) != NULL)
		pElem_dwFighterCurAnima.release();
	unique_ptr<TiXmlElement> pElem_dwFighterMaxAnima(new TiXmlElement("UINT32"));
	if(pElem_dwFighterMaxAnima == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwFighterMaxAnima->SetAttribute("name", "dwFighterMaxAnima");
	pElem_dwFighterMaxAnima->SetAttribute("value", NumberToString(s.dwFighterMaxAnima).c_str());
	pElem_dwFighterMaxAnima->SetAttribute("comment", ToUTF8Ptr("将最大灵气"));
	if(rElement.LinkEndChild(pElem_dwFighterMaxAnima.get()) != NULL)
		pElem_dwFighterMaxAnima.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecGEMBattleFighterInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SGEMBattleFighterInfo s;
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

bool VectorToXML(const TVecGEMBattleFighterInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SGEMBattleFighterInfo"));
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

SGEMAwardInfo::SGEMAwardInfo() : wItemID(0), dwCount(0) { }

SGEMAwardInfo::SGEMAwardInfo(UINT16 wItemID_, UINT32 dwCount_) : wItemID(wItemID_), dwCount(dwCount_) { }

CInArchive& operator>>(CInArchive& src, SGEMAwardInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.wItemID;
	src >> s.dwCount;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SGEMAwardInfo& s)
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
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SGEMAwardInfo& s)
{
	if(strcmp(rElement.Value(), "SGEMAwardInfo") != 0)
	{
		LOG_CRI << "rElement is not SGEMAwardInfo!";
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

bool ToXML(const SGEMAwardInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SGEMAwardInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("守卫峨眉奖励信息"));
	unique_ptr<TiXmlElement> pElem_wItemID(new TiXmlElement("UINT16"));
	if(pElem_wItemID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wItemID->SetAttribute("name", "wItemID");
	pElem_wItemID->SetAttribute("value", NumberToString(s.wItemID).c_str());
	pElem_wItemID->SetAttribute("comment", ToUTF8Ptr("物品ID"));
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
	pElem_dwCount->SetAttribute("comment", ToUTF8Ptr("堆叠数"));
	if(rElement.LinkEndChild(pElem_dwCount.get()) != NULL)
		pElem_dwCount.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecGEMAwardInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SGEMAwardInfo s;
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

bool VectorToXML(const TVecGEMAwardInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SGEMAwardInfo"));
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

SGEMBuffInfo::SGEMBuffInfo() : dwBuffID(0), dwBuffNum(0) { }

SGEMBuffInfo::SGEMBuffInfo(UINT32 dwBuffID_, UINT32 dwBuffNum_) : dwBuffID(dwBuffID_), dwBuffNum(dwBuffNum_) { }

CInArchive& operator>>(CInArchive& src, SGEMBuffInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.dwBuffID;
	src >> s.dwBuffNum;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SGEMBuffInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.dwBuffID;
	src << s.dwBuffNum;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SGEMBuffInfo& s)
{
	if(strcmp(rElement.Value(), "SGEMBuffInfo") != 0)
	{
		LOG_CRI << "rElement is not SGEMBuffInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwBuffID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwBuffID") != 0)
	{
		LOG_CRI << "Attribute: name is not dwBuffID!";
		return false;
	}
	const char* pszVal_dwBuffID = pElemChild->Attribute("value");
	if(pszVal_dwBuffID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwBuffID, s.dwBuffID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwBuffNum is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwBuffNum") != 0)
	{
		LOG_CRI << "Attribute: name is not dwBuffNum!";
		return false;
	}
	const char* pszVal_dwBuffNum = pElemChild->Attribute("value");
	if(pszVal_dwBuffNum == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwBuffNum, s.dwBuffNum))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SGEMBuffInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SGEMBuffInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("守卫峨眉Buff信息"));
	unique_ptr<TiXmlElement> pElem_dwBuffID(new TiXmlElement("UINT32"));
	if(pElem_dwBuffID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwBuffID->SetAttribute("name", "dwBuffID");
	pElem_dwBuffID->SetAttribute("value", NumberToString(s.dwBuffID).c_str());
	pElem_dwBuffID->SetAttribute("comment", ToUTF8Ptr("BuffID"));
	if(rElement.LinkEndChild(pElem_dwBuffID.get()) != NULL)
		pElem_dwBuffID.release();
	unique_ptr<TiXmlElement> pElem_dwBuffNum(new TiXmlElement("UINT32"));
	if(pElem_dwBuffNum == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwBuffNum->SetAttribute("name", "dwBuffNum");
	pElem_dwBuffNum->SetAttribute("value", NumberToString(s.dwBuffNum).c_str());
	pElem_dwBuffNum->SetAttribute("comment", ToUTF8Ptr("Buff数量"));
	if(rElement.LinkEndChild(pElem_dwBuffNum.get()) != NULL)
		pElem_dwBuffNum.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecGEMBuffInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SGEMBuffInfo s;
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

bool VectorToXML(const TVecGEMBuffInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SGEMBuffInfo"));
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

SGEMPrepareBattleInfo::SGEMPrepareBattleInfo() : wCurProgress(0), dwMonsterID(0), dwBattlePoint(0) { }

SGEMPrepareBattleInfo::SGEMPrepareBattleInfo(UINT16 wCurProgress_, UINT32 dwMonsterID_, UINT32 dwBattlePoint_, const TVecGEMBuffInfo& vecGEMBuffInfo_, const TVecGEMBattleFighterInfo& vecGEMBattleFighterInfo_)
			: wCurProgress(wCurProgress_), dwMonsterID(dwMonsterID_), dwBattlePoint(dwBattlePoint_), vecGEMBuffInfo(vecGEMBuffInfo_), vecGEMBattleFighterInfo(vecGEMBattleFighterInfo_) { }

SGEMPrepareBattleInfo::SGEMPrepareBattleInfo(SGEMPrepareBattleInfo&& src) : wCurProgress(src.wCurProgress), dwMonsterID(src.dwMonsterID), dwBattlePoint(src.dwBattlePoint), vecGEMBuffInfo(move(src.vecGEMBuffInfo)), vecGEMBattleFighterInfo(move(src.vecGEMBattleFighterInfo)) { }

SGEMPrepareBattleInfo& SGEMPrepareBattleInfo::operator=(SGEMPrepareBattleInfo&& rhs)
{
	if(this != &rhs)
	{
		this->~SGEMPrepareBattleInfo();
		new (this) SGEMPrepareBattleInfo(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SGEMPrepareBattleInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.wCurProgress;
	src >> s.dwMonsterID;
	src >> s.dwBattlePoint;
	src >> s.vecGEMBuffInfo;
	src >> s.vecGEMBattleFighterInfo;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SGEMPrepareBattleInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.wCurProgress;
	src << s.dwMonsterID;
	src << s.dwBattlePoint;
	src << s.vecGEMBuffInfo;
	src << s.vecGEMBattleFighterInfo;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SGEMPrepareBattleInfo& s)
{
	if(strcmp(rElement.Value(), "SGEMPrepareBattleInfo") != 0)
	{
		LOG_CRI << "rElement is not SGEMPrepareBattleInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wCurProgress is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wCurProgress") != 0)
	{
		LOG_CRI << "Attribute: name is not wCurProgress!";
		return false;
	}
	const char* pszVal_wCurProgress = pElemChild->Attribute("value");
	if(pszVal_wCurProgress == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wCurProgress, s.wCurProgress))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwMonsterID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwMonsterID") != 0)
	{
		LOG_CRI << "Attribute: name is not dwMonsterID!";
		return false;
	}
	const char* pszVal_dwMonsterID = pElemChild->Attribute("value");
	if(pszVal_dwMonsterID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwMonsterID, s.dwMonsterID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwBattlePoint is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwBattlePoint") != 0)
	{
		LOG_CRI << "Attribute: name is not dwBattlePoint!";
		return false;
	}
	const char* pszVal_dwBattlePoint = pElemChild->Attribute("value");
	if(pszVal_dwBattlePoint == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwBattlePoint, s.dwBattlePoint))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecGEMBuffInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecGEMBuffInfo") != 0)
	{
		LOG_CRI << "pElemChild is not TVecGEMBuffInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecGEMBuffInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not vecGEMBuffInfo!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecGEMBuffInfo))
	{
		LOG_CRI << "VectorFromXML for vecGEMBuffInfo fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecGEMBattleFighterInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecGEMBattleFighterInfo") != 0)
	{
		LOG_CRI << "pElemChild is not TVecGEMBattleFighterInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecGEMBattleFighterInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not vecGEMBattleFighterInfo!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecGEMBattleFighterInfo))
	{
		LOG_CRI << "VectorFromXML for vecGEMBattleFighterInfo fails!";
		return false;
	}
	return true;
}

bool ToXML(const SGEMPrepareBattleInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SGEMPrepareBattleInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("守卫峨眉准备战斗信息"));
	unique_ptr<TiXmlElement> pElem_wCurProgress(new TiXmlElement("UINT16"));
	if(pElem_wCurProgress == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wCurProgress->SetAttribute("name", "wCurProgress");
	pElem_wCurProgress->SetAttribute("value", NumberToString(s.wCurProgress).c_str());
	pElem_wCurProgress->SetAttribute("comment", ToUTF8Ptr("当前进度"));
	if(rElement.LinkEndChild(pElem_wCurProgress.get()) != NULL)
		pElem_wCurProgress.release();
	unique_ptr<TiXmlElement> pElem_dwMonsterID(new TiXmlElement("UINT32"));
	if(pElem_dwMonsterID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwMonsterID->SetAttribute("name", "dwMonsterID");
	pElem_dwMonsterID->SetAttribute("value", NumberToString(s.dwMonsterID).c_str());
	pElem_dwMonsterID->SetAttribute("comment", ToUTF8Ptr("怪物ID"));
	if(rElement.LinkEndChild(pElem_dwMonsterID.get()) != NULL)
		pElem_dwMonsterID.release();
	unique_ptr<TiXmlElement> pElem_dwBattlePoint(new TiXmlElement("UINT32"));
	if(pElem_dwBattlePoint == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwBattlePoint->SetAttribute("name", "dwBattlePoint");
	pElem_dwBattlePoint->SetAttribute("value", NumberToString(s.dwBattlePoint).c_str());
	pElem_dwBattlePoint->SetAttribute("comment", ToUTF8Ptr("参战散仙战斗力"));
	if(rElement.LinkEndChild(pElem_dwBattlePoint.get()) != NULL)
		pElem_dwBattlePoint.release();
	unique_ptr<TiXmlElement> pElem_vecGEMBuffInfo(new TiXmlElement("TVecGEMBuffInfo"));
	if(pElem_vecGEMBuffInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecGEMBuffInfo->SetAttribute("name", "vecGEMBuffInfo");
	if(!VectorToXML(s.vecGEMBuffInfo, *pElem_vecGEMBuffInfo))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecGEMBuffInfo->SetAttribute("comment", ToUTF8Ptr("守卫峨眉Buff信息"));
	if(rElement.LinkEndChild(pElem_vecGEMBuffInfo.get()) != NULL)
		pElem_vecGEMBuffInfo.release();
	unique_ptr<TiXmlElement> pElem_vecGEMBattleFighterInfo(new TiXmlElement("TVecGEMBattleFighterInfo"));
	if(pElem_vecGEMBattleFighterInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecGEMBattleFighterInfo->SetAttribute("name", "vecGEMBattleFighterInfo");
	if(!VectorToXML(s.vecGEMBattleFighterInfo, *pElem_vecGEMBattleFighterInfo))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecGEMBattleFighterInfo->SetAttribute("comment", ToUTF8Ptr("守卫峨眉参战散仙信息"));
	if(rElement.LinkEndChild(pElem_vecGEMBattleFighterInfo.get()) != NULL)
		pElem_vecGEMBattleFighterInfo.release();
	return true;
}

#endif

SGEMMissionInfo::SGEMMissionInfo() : wFreeEntryNumDay(0), wBuyEntryNumDay(0), wBuyEntryTotalNum(0), qwIsGuardSucc(0), wCurMissionID(0), 
			byGEMType(0), wCurProgress(0) { }

SGEMMissionInfo::SGEMMissionInfo(UINT16 wFreeEntryNumDay_, UINT16 wBuyEntryNumDay_, UINT16 wBuyEntryTotalNum_, UINT64 qwIsGuardSucc_, UINT16 wCurMissionID_, 
			UINT8 byGEMType_, UINT16 wCurProgress_)
			: wFreeEntryNumDay(wFreeEntryNumDay_), wBuyEntryNumDay(wBuyEntryNumDay_), wBuyEntryTotalNum(wBuyEntryTotalNum_), qwIsGuardSucc(qwIsGuardSucc_), wCurMissionID(wCurMissionID_), 
			byGEMType(byGEMType_), wCurProgress(wCurProgress_) { }

CInArchive& operator>>(CInArchive& src, SGEMMissionInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.wFreeEntryNumDay;
	src >> s.wBuyEntryNumDay;
	src >> s.wBuyEntryTotalNum;
	src >> s.qwIsGuardSucc;
	src >> s.wCurMissionID;
	src >> s.byGEMType;
	src >> s.wCurProgress;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SGEMMissionInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.wFreeEntryNumDay;
	src << s.wBuyEntryNumDay;
	src << s.wBuyEntryTotalNum;
	src << s.qwIsGuardSucc;
	src << s.wCurMissionID;
	src << s.byGEMType;
	src << s.wCurProgress;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SGEMMissionInfo& s)
{
	if(strcmp(rElement.Value(), "SGEMMissionInfo") != 0)
	{
		LOG_CRI << "rElement is not SGEMMissionInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wFreeEntryNumDay is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wFreeEntryNumDay") != 0)
	{
		LOG_CRI << "Attribute: name is not wFreeEntryNumDay!";
		return false;
	}
	const char* pszVal_wFreeEntryNumDay = pElemChild->Attribute("value");
	if(pszVal_wFreeEntryNumDay == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wFreeEntryNumDay, s.wFreeEntryNumDay))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wBuyEntryNumDay is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wBuyEntryNumDay") != 0)
	{
		LOG_CRI << "Attribute: name is not wBuyEntryNumDay!";
		return false;
	}
	const char* pszVal_wBuyEntryNumDay = pElemChild->Attribute("value");
	if(pszVal_wBuyEntryNumDay == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wBuyEntryNumDay, s.wBuyEntryNumDay))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wBuyEntryTotalNum is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wBuyEntryTotalNum") != 0)
	{
		LOG_CRI << "Attribute: name is not wBuyEntryTotalNum!";
		return false;
	}
	const char* pszVal_wBuyEntryTotalNum = pElemChild->Attribute("value");
	if(pszVal_wBuyEntryTotalNum == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wBuyEntryTotalNum, s.wBuyEntryTotalNum))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwIsGuardSucc is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwIsGuardSucc") != 0)
	{
		LOG_CRI << "Attribute: name is not qwIsGuardSucc!";
		return false;
	}
	const char* pszVal_qwIsGuardSucc = pElemChild->Attribute("value");
	if(pszVal_qwIsGuardSucc == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwIsGuardSucc, s.qwIsGuardSucc))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wCurMissionID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wCurMissionID") != 0)
	{
		LOG_CRI << "Attribute: name is not wCurMissionID!";
		return false;
	}
	const char* pszVal_wCurMissionID = pElemChild->Attribute("value");
	if(pszVal_wCurMissionID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wCurMissionID, s.wCurMissionID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byGEMType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byGEMType") != 0)
	{
		LOG_CRI << "Attribute: name is not byGEMType!";
		return false;
	}
	const char* pszVal_byGEMType = pElemChild->Attribute("value");
	if(pszVal_byGEMType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byGEMType, s.byGEMType))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wCurProgress is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wCurProgress") != 0)
	{
		LOG_CRI << "Attribute: name is not wCurProgress!";
		return false;
	}
	const char* pszVal_wCurProgress = pElemChild->Attribute("value");
	if(pszVal_wCurProgress == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wCurProgress, s.wCurProgress))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SGEMMissionInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SGEMMissionInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("守卫峨眉关卡信息"));
	unique_ptr<TiXmlElement> pElem_wFreeEntryNumDay(new TiXmlElement("UINT16"));
	if(pElem_wFreeEntryNumDay == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wFreeEntryNumDay->SetAttribute("name", "wFreeEntryNumDay");
	pElem_wFreeEntryNumDay->SetAttribute("value", NumberToString(s.wFreeEntryNumDay).c_str());
	pElem_wFreeEntryNumDay->SetAttribute("comment", ToUTF8Ptr("当日免费进入次数"));
	if(rElement.LinkEndChild(pElem_wFreeEntryNumDay.get()) != NULL)
		pElem_wFreeEntryNumDay.release();
	unique_ptr<TiXmlElement> pElem_wBuyEntryNumDay(new TiXmlElement("UINT16"));
	if(pElem_wBuyEntryNumDay == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wBuyEntryNumDay->SetAttribute("name", "wBuyEntryNumDay");
	pElem_wBuyEntryNumDay->SetAttribute("value", NumberToString(s.wBuyEntryNumDay).c_str());
	pElem_wBuyEntryNumDay->SetAttribute("comment", ToUTF8Ptr("当日购买进入次数"));
	if(rElement.LinkEndChild(pElem_wBuyEntryNumDay.get()) != NULL)
		pElem_wBuyEntryNumDay.release();
	unique_ptr<TiXmlElement> pElem_wBuyEntryTotalNum(new TiXmlElement("UINT16"));
	if(pElem_wBuyEntryTotalNum == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wBuyEntryTotalNum->SetAttribute("name", "wBuyEntryTotalNum");
	pElem_wBuyEntryTotalNum->SetAttribute("value", NumberToString(s.wBuyEntryTotalNum).c_str());
	pElem_wBuyEntryTotalNum->SetAttribute("comment", ToUTF8Ptr("购买进入总次数"));
	if(rElement.LinkEndChild(pElem_wBuyEntryTotalNum.get()) != NULL)
		pElem_wBuyEntryTotalNum.release();
	unique_ptr<TiXmlElement> pElem_qwIsGuardSucc(new TiXmlElement("UINT64"));
	if(pElem_qwIsGuardSucc == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwIsGuardSucc->SetAttribute("name", "qwIsGuardSucc");
	pElem_qwIsGuardSucc->SetAttribute("value", NumberToString(s.qwIsGuardSucc).c_str());
	pElem_qwIsGuardSucc->SetAttribute("comment", ToUTF8Ptr("每一位表示守卫是否成功（注：0未成功；1成功）"));
	if(rElement.LinkEndChild(pElem_qwIsGuardSucc.get()) != NULL)
		pElem_qwIsGuardSucc.release();
	unique_ptr<TiXmlElement> pElem_wCurMissionID(new TiXmlElement("UINT16"));
	if(pElem_wCurMissionID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wCurMissionID->SetAttribute("name", "wCurMissionID");
	pElem_wCurMissionID->SetAttribute("value", NumberToString(s.wCurMissionID).c_str());
	pElem_wCurMissionID->SetAttribute("comment", ToUTF8Ptr("正在进行的关卡ID（注：0表示没有）"));
	if(rElement.LinkEndChild(pElem_wCurMissionID.get()) != NULL)
		pElem_wCurMissionID.release();
	unique_ptr<TiXmlElement> pElem_byGEMType(new TiXmlElement("UINT8"));
	if(pElem_byGEMType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byGEMType->SetAttribute("name", "byGEMType");
	pElem_byGEMType->SetAttribute("value", NumberToString(s.byGEMType).c_str());
	pElem_byGEMType->SetAttribute("comment", ToUTF8Ptr("正在进行的类型（注：0表示没有；1：守卫；2：扫荡）"));
	if(rElement.LinkEndChild(pElem_byGEMType.get()) != NULL)
		pElem_byGEMType.release();
	unique_ptr<TiXmlElement> pElem_wCurProgress(new TiXmlElement("UINT16"));
	if(pElem_wCurProgress == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wCurProgress->SetAttribute("name", "wCurProgress");
	pElem_wCurProgress->SetAttribute("value", NumberToString(s.wCurProgress).c_str());
	pElem_wCurProgress->SetAttribute("comment", ToUTF8Ptr("正在进行的关卡进度（注：0表示没有）"));
	if(rElement.LinkEndChild(pElem_wCurProgress.get()) != NULL)
		pElem_wCurProgress.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecGEMMissionInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SGEMMissionInfo s;
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

bool VectorToXML(const TVecGEMMissionInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SGEMMissionInfo"));
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

SGEMDBInfo::SGEMDBInfo() : qwRoleID(0), wMissionID(0), byGEMType(0), wCurProgress(0), wGuardProgress(0), 
			dwGuardMonsterGroupID(0), dwSweepEndTime(0) { }

SGEMDBInfo::SGEMDBInfo(UINT64 qwRoleID_, UINT16 wMissionID_, UINT8 byGEMType_, UINT16 wCurProgress_, UINT16 wGuardProgress_, 
			UINT32 dwGuardMonsterGroupID_, UINT32 dwSweepEndTime_, const std::string& strBuff_)
			: qwRoleID(qwRoleID_), wMissionID(wMissionID_), byGEMType(byGEMType_), wCurProgress(wCurProgress_), wGuardProgress(wGuardProgress_), 
			dwGuardMonsterGroupID(dwGuardMonsterGroupID_), dwSweepEndTime(dwSweepEndTime_), strBuff(strBuff_) { }

SGEMDBInfo::SGEMDBInfo(SGEMDBInfo&& src) : qwRoleID(src.qwRoleID), wMissionID(src.wMissionID), byGEMType(src.byGEMType), wCurProgress(src.wCurProgress), wGuardProgress(src.wGuardProgress), 
			dwGuardMonsterGroupID(src.dwGuardMonsterGroupID), dwSweepEndTime(src.dwSweepEndTime), strBuff(move(src.strBuff)) { }

SGEMDBInfo& SGEMDBInfo::operator=(SGEMDBInfo&& rhs)
{
	if(this != &rhs)
	{
		this->~SGEMDBInfo();
		new (this) SGEMDBInfo(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SGEMDBInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwRoleID;
	src >> s.wMissionID;
	src >> s.byGEMType;
	src >> s.wCurProgress;
	src >> s.wGuardProgress;
	src >> s.dwGuardMonsterGroupID;
	src >> s.dwSweepEndTime;
	src >> s.strBuff;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SGEMDBInfo& s)
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
	src << s.wMissionID;
	src << s.byGEMType;
	src << s.wCurProgress;
	src << s.wGuardProgress;
	src << s.dwGuardMonsterGroupID;
	src << s.dwSweepEndTime;
	src << s.strBuff;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SGEMDBInfo& s)
{
	if(strcmp(rElement.Value(), "SGEMDBInfo") != 0)
	{
		LOG_CRI << "rElement is not SGEMDBInfo!";
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
		LOG_CRI << "pElemChild for wMissionID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wMissionID") != 0)
	{
		LOG_CRI << "Attribute: name is not wMissionID!";
		return false;
	}
	const char* pszVal_wMissionID = pElemChild->Attribute("value");
	if(pszVal_wMissionID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wMissionID, s.wMissionID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byGEMType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byGEMType") != 0)
	{
		LOG_CRI << "Attribute: name is not byGEMType!";
		return false;
	}
	const char* pszVal_byGEMType = pElemChild->Attribute("value");
	if(pszVal_byGEMType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byGEMType, s.byGEMType))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wCurProgress is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wCurProgress") != 0)
	{
		LOG_CRI << "Attribute: name is not wCurProgress!";
		return false;
	}
	const char* pszVal_wCurProgress = pElemChild->Attribute("value");
	if(pszVal_wCurProgress == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wCurProgress, s.wCurProgress))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wGuardProgress is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wGuardProgress") != 0)
	{
		LOG_CRI << "Attribute: name is not wGuardProgress!";
		return false;
	}
	const char* pszVal_wGuardProgress = pElemChild->Attribute("value");
	if(pszVal_wGuardProgress == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wGuardProgress, s.wGuardProgress))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwGuardMonsterGroupID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwGuardMonsterGroupID") != 0)
	{
		LOG_CRI << "Attribute: name is not dwGuardMonsterGroupID!";
		return false;
	}
	const char* pszVal_dwGuardMonsterGroupID = pElemChild->Attribute("value");
	if(pszVal_dwGuardMonsterGroupID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwGuardMonsterGroupID, s.dwGuardMonsterGroupID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwSweepEndTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwSweepEndTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwSweepEndTime!";
		return false;
	}
	const char* pszVal_dwSweepEndTime = pElemChild->Attribute("value");
	if(pszVal_dwSweepEndTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwSweepEndTime, s.dwSweepEndTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strBuff is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strBuff") != 0)
	{
		LOG_CRI << "Attribute: name is not strBuff!";
		return false;
	}
	const char* pszVal_strBuff = pElemChild->Attribute("value");
	if(pszVal_strBuff == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strBuff = pszVal_strBuff;
	return true;
}

bool ToXML(const SGEMDBInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SGEMDBInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("守卫峨眉DB信息"));
	unique_ptr<TiXmlElement> pElem_qwRoleID(new TiXmlElement("UINT64"));
	if(pElem_qwRoleID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwRoleID->SetAttribute("name", "qwRoleID");
	pElem_qwRoleID->SetAttribute("value", NumberToString(s.qwRoleID).c_str());
	pElem_qwRoleID->SetAttribute("comment", ToUTF8Ptr("RoleID"));
	if(rElement.LinkEndChild(pElem_qwRoleID.get()) != NULL)
		pElem_qwRoleID.release();
	unique_ptr<TiXmlElement> pElem_wMissionID(new TiXmlElement("UINT16"));
	if(pElem_wMissionID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wMissionID->SetAttribute("name", "wMissionID");
	pElem_wMissionID->SetAttribute("value", NumberToString(s.wMissionID).c_str());
	pElem_wMissionID->SetAttribute("comment", ToUTF8Ptr("关卡ID"));
	if(rElement.LinkEndChild(pElem_wMissionID.get()) != NULL)
		pElem_wMissionID.release();
	unique_ptr<TiXmlElement> pElem_byGEMType(new TiXmlElement("UINT8"));
	if(pElem_byGEMType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byGEMType->SetAttribute("name", "byGEMType");
	pElem_byGEMType->SetAttribute("value", NumberToString(s.byGEMType).c_str());
	pElem_byGEMType->SetAttribute("comment", ToUTF8Ptr("正在进行的类型（注：0表示没有；1：守卫；2：扫荡）"));
	if(rElement.LinkEndChild(pElem_byGEMType.get()) != NULL)
		pElem_byGEMType.release();
	unique_ptr<TiXmlElement> pElem_wCurProgress(new TiXmlElement("UINT16"));
	if(pElem_wCurProgress == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wCurProgress->SetAttribute("name", "wCurProgress");
	pElem_wCurProgress->SetAttribute("value", NumberToString(s.wCurProgress).c_str());
	pElem_wCurProgress->SetAttribute("comment", ToUTF8Ptr("当前进度"));
	if(rElement.LinkEndChild(pElem_wCurProgress.get()) != NULL)
		pElem_wCurProgress.release();
	unique_ptr<TiXmlElement> pElem_wGuardProgress(new TiXmlElement("UINT16"));
	if(pElem_wGuardProgress == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wGuardProgress->SetAttribute("name", "wGuardProgress");
	pElem_wGuardProgress->SetAttribute("value", NumberToString(s.wGuardProgress).c_str());
	pElem_wGuardProgress->SetAttribute("comment", ToUTF8Ptr("守卫进度"));
	if(rElement.LinkEndChild(pElem_wGuardProgress.get()) != NULL)
		pElem_wGuardProgress.release();
	unique_ptr<TiXmlElement> pElem_dwGuardMonsterGroupID(new TiXmlElement("UINT32"));
	if(pElem_dwGuardMonsterGroupID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwGuardMonsterGroupID->SetAttribute("name", "dwGuardMonsterGroupID");
	pElem_dwGuardMonsterGroupID->SetAttribute("value", NumberToString(s.dwGuardMonsterGroupID).c_str());
	pElem_dwGuardMonsterGroupID->SetAttribute("comment", ToUTF8Ptr("怪物组ID"));
	if(rElement.LinkEndChild(pElem_dwGuardMonsterGroupID.get()) != NULL)
		pElem_dwGuardMonsterGroupID.release();
	unique_ptr<TiXmlElement> pElem_dwSweepEndTime(new TiXmlElement("UINT32"));
	if(pElem_dwSweepEndTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwSweepEndTime->SetAttribute("name", "dwSweepEndTime");
	pElem_dwSweepEndTime->SetAttribute("value", NumberToString(s.dwSweepEndTime).c_str());
	pElem_dwSweepEndTime->SetAttribute("comment", ToUTF8Ptr("扫荡结束时间"));
	if(rElement.LinkEndChild(pElem_dwSweepEndTime.get()) != NULL)
		pElem_dwSweepEndTime.release();
	unique_ptr<TiXmlElement> pElem_strBuff(new TiXmlElement("string"));
	if(pElem_strBuff == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strBuff->SetAttribute("name", "strBuff");
	pElem_strBuff->SetAttribute("value", s.strBuff.c_str());
	pElem_strBuff->SetAttribute("comment", ToUTF8Ptr("守卫峨眉Buff"));
	if(rElement.LinkEndChild(pElem_strBuff.get()) != NULL)
		pElem_strBuff.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecGEMDBInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SGEMDBInfo s;
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

bool VectorToXML(const TVecGEMDBInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SGEMDBInfo"));
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

} //namespace NGuardEMeiProt
