/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    CompareBattlePoint.cpp
//  Purpose:      变强(战力对比)相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "CompareBattlePoint.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NCompareBattlePoint
{

SCompareData::SCompareData() : qwRoleID(0), byLevel(0), eCareer((NProtoCommon::ECareerType)0), eSex((NProtoCommon::ESexType)0), dwBattlePoint(0), 
			dwHeroBP(0), dwBeautyBP(0), dwTrumpBP(0), dwHorseBP(0), dwDujieBP(0), 
			dwXinfaBP(0), dwClanBP(0) { }

SCompareData::SCompareData(SCompareData&& src) : qwRoleID(src.qwRoleID), strName(move(src.strName)), byLevel(src.byLevel), eCareer(src.eCareer), eSex(src.eSex), 
			dwBattlePoint(src.dwBattlePoint), dwHeroBP(src.dwHeroBP), dwBeautyBP(src.dwBeautyBP), dwTrumpBP(src.dwTrumpBP), dwHorseBP(src.dwHorseBP), 
			dwDujieBP(src.dwDujieBP), dwXinfaBP(src.dwXinfaBP), dwClanBP(src.dwClanBP) { }

SCompareData& SCompareData::operator=(SCompareData&& rhs)
{
	if(this != &rhs)
	{
		this->~SCompareData();
		new (this) SCompareData(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SCompareData& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwRoleID;
	src >> s.strName;
	src >> s.byLevel;
	src >> (UINT8&)s.eCareer;
	src >> (UINT8&)s.eSex;
	src >> s.dwBattlePoint;
	src >> s.dwHeroBP;
	src >> s.dwBeautyBP;
	src >> s.dwTrumpBP;
	src >> s.dwHorseBP;
	src >> s.dwDujieBP;
	src >> s.dwXinfaBP;
	src >> s.dwClanBP;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SCompareData& s)
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
	src << s.strName;
	src << s.byLevel;
	src << (UINT8&)s.eCareer;
	src << (UINT8&)s.eSex;
	src << s.dwBattlePoint;
	src << s.dwHeroBP;
	src << s.dwBeautyBP;
	src << s.dwTrumpBP;
	src << s.dwHorseBP;
	src << s.dwDujieBP;
	src << s.dwXinfaBP;
	src << s.dwClanBP;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SCompareData& s)
{
	if(strcmp(rElement.Value(), "SCompareData") != 0)
	{
		LOG_CRI << "rElement is not SCompareData!";
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
		LOG_CRI << "pElemChild for eCareer is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "ProtoCommon::ECareerType") != 0)
	{
		LOG_CRI << "pElemChild is not ProtoCommon::ECareerType!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eCareer") != 0)
	{
		LOG_CRI << "Attribute: name is not eCareer!";
		return false;
	}
	const char* pszVal_eCareer = pElemChild->Attribute("value");
	if(pszVal_eCareer == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!NProtoCommon::EnumStrToVal(pszVal_eCareer, s.eCareer))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eSex is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "ProtoCommon::ESexType") != 0)
	{
		LOG_CRI << "pElemChild is not ProtoCommon::ESexType!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eSex") != 0)
	{
		LOG_CRI << "Attribute: name is not eSex!";
		return false;
	}
	const char* pszVal_eSex = pElemChild->Attribute("value");
	if(pszVal_eSex == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!NProtoCommon::EnumStrToVal(pszVal_eSex, s.eSex))
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
		LOG_CRI << "pElemChild for dwHeroBP is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwHeroBP") != 0)
	{
		LOG_CRI << "Attribute: name is not dwHeroBP!";
		return false;
	}
	const char* pszVal_dwHeroBP = pElemChild->Attribute("value");
	if(pszVal_dwHeroBP == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwHeroBP, s.dwHeroBP))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwBeautyBP is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwBeautyBP") != 0)
	{
		LOG_CRI << "Attribute: name is not dwBeautyBP!";
		return false;
	}
	const char* pszVal_dwBeautyBP = pElemChild->Attribute("value");
	if(pszVal_dwBeautyBP == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwBeautyBP, s.dwBeautyBP))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwTrumpBP is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwTrumpBP") != 0)
	{
		LOG_CRI << "Attribute: name is not dwTrumpBP!";
		return false;
	}
	const char* pszVal_dwTrumpBP = pElemChild->Attribute("value");
	if(pszVal_dwTrumpBP == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwTrumpBP, s.dwTrumpBP))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwHorseBP is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwHorseBP") != 0)
	{
		LOG_CRI << "Attribute: name is not dwHorseBP!";
		return false;
	}
	const char* pszVal_dwHorseBP = pElemChild->Attribute("value");
	if(pszVal_dwHorseBP == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwHorseBP, s.dwHorseBP))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwDujieBP is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwDujieBP") != 0)
	{
		LOG_CRI << "Attribute: name is not dwDujieBP!";
		return false;
	}
	const char* pszVal_dwDujieBP = pElemChild->Attribute("value");
	if(pszVal_dwDujieBP == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwDujieBP, s.dwDujieBP))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwXinfaBP is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwXinfaBP") != 0)
	{
		LOG_CRI << "Attribute: name is not dwXinfaBP!";
		return false;
	}
	const char* pszVal_dwXinfaBP = pElemChild->Attribute("value");
	if(pszVal_dwXinfaBP == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwXinfaBP, s.dwXinfaBP))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwClanBP is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwClanBP") != 0)
	{
		LOG_CRI << "Attribute: name is not dwClanBP!";
		return false;
	}
	const char* pszVal_dwClanBP = pElemChild->Attribute("value");
	if(pszVal_dwClanBP == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwClanBP, s.dwClanBP))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SCompareData& s, TiXmlElement& rElement)
{
	rElement.SetValue("SCompareData");
	rElement.SetAttribute("type", ToUTF8Ptr("对比的数据结构"));
	unique_ptr<TiXmlElement> pElem_qwRoleID(new TiXmlElement("UINT64"));
	if(pElem_qwRoleID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwRoleID->SetAttribute("name", "qwRoleID");
	pElem_qwRoleID->SetAttribute("value", NumberToString(s.qwRoleID).c_str());
	pElem_qwRoleID->SetAttribute("comment", ToUTF8Ptr("玩家ID"));
	if(rElement.LinkEndChild(pElem_qwRoleID.get()) != NULL)
		pElem_qwRoleID.release();
	unique_ptr<TiXmlElement> pElem_strName(new TiXmlElement("string"));
	if(pElem_strName == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strName->SetAttribute("name", "strName");
	pElem_strName->SetAttribute("value", s.strName.c_str());
	pElem_strName->SetAttribute("comment", ToUTF8Ptr("玩家名字"));
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
	pElem_byLevel->SetAttribute("comment", ToUTF8Ptr("玩家等级"));
	if(rElement.LinkEndChild(pElem_byLevel.get()) != NULL)
		pElem_byLevel.release();
	unique_ptr<TiXmlElement> pElem_eCareer(new TiXmlElement("ProtoCommon::ECareerType"));
	if(pElem_eCareer == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eCareer->SetAttribute("name", "eCareer");
	const char* pszEnum_eCareer = NProtoCommon::EnumValToStr(s.eCareer);
	if(pszEnum_eCareer == NULL)
	{
		LOG_CRI << "EnumValToStr for eCareer fails!";
		return false;
	}
	pElem_eCareer->SetAttribute("value", pszEnum_eCareer);
	pElem_eCareer->SetAttribute("comment", ToUTF8Ptr("玩家主将职业"));
	if(rElement.LinkEndChild(pElem_eCareer.get()) != NULL)
		pElem_eCareer.release();
	unique_ptr<TiXmlElement> pElem_eSex(new TiXmlElement("ProtoCommon::ESexType"));
	if(pElem_eSex == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eSex->SetAttribute("name", "eSex");
	const char* pszEnum_eSex = NProtoCommon::EnumValToStr(s.eSex);
	if(pszEnum_eSex == NULL)
	{
		LOG_CRI << "EnumValToStr for eSex fails!";
		return false;
	}
	pElem_eSex->SetAttribute("value", pszEnum_eSex);
	pElem_eSex->SetAttribute("comment", ToUTF8Ptr("玩家主将性别"));
	if(rElement.LinkEndChild(pElem_eSex.get()) != NULL)
		pElem_eSex.release();
	unique_ptr<TiXmlElement> pElem_dwBattlePoint(new TiXmlElement("UINT32"));
	if(pElem_dwBattlePoint == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwBattlePoint->SetAttribute("name", "dwBattlePoint");
	pElem_dwBattlePoint->SetAttribute("value", NumberToString(s.dwBattlePoint).c_str());
	pElem_dwBattlePoint->SetAttribute("comment", ToUTF8Ptr("玩家总战斗力"));
	if(rElement.LinkEndChild(pElem_dwBattlePoint.get()) != NULL)
		pElem_dwBattlePoint.release();
	unique_ptr<TiXmlElement> pElem_dwHeroBP(new TiXmlElement("UINT32"));
	if(pElem_dwHeroBP == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwHeroBP->SetAttribute("name", "dwHeroBP");
	pElem_dwHeroBP->SetAttribute("value", NumberToString(s.dwHeroBP).c_str());
	pElem_dwHeroBP->SetAttribute("comment", ToUTF8Ptr("散仙的战斗力(渡劫和心法除外)"));
	if(rElement.LinkEndChild(pElem_dwHeroBP.get()) != NULL)
		pElem_dwHeroBP.release();
	unique_ptr<TiXmlElement> pElem_dwBeautyBP(new TiXmlElement("UINT32"));
	if(pElem_dwBeautyBP == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwBeautyBP->SetAttribute("name", "dwBeautyBP");
	pElem_dwBeautyBP->SetAttribute("value", NumberToString(s.dwBeautyBP).c_str());
	pElem_dwBeautyBP->SetAttribute("comment", ToUTF8Ptr("美女系统战斗力"));
	if(rElement.LinkEndChild(pElem_dwBeautyBP.get()) != NULL)
		pElem_dwBeautyBP.release();
	unique_ptr<TiXmlElement> pElem_dwTrumpBP(new TiXmlElement("UINT32"));
	if(pElem_dwTrumpBP == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwTrumpBP->SetAttribute("name", "dwTrumpBP");
	pElem_dwTrumpBP->SetAttribute("value", NumberToString(s.dwTrumpBP).c_str());
	pElem_dwTrumpBP->SetAttribute("comment", ToUTF8Ptr("法宝战斗力"));
	if(rElement.LinkEndChild(pElem_dwTrumpBP.get()) != NULL)
		pElem_dwTrumpBP.release();
	unique_ptr<TiXmlElement> pElem_dwHorseBP(new TiXmlElement("UINT32"));
	if(pElem_dwHorseBP == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwHorseBP->SetAttribute("name", "dwHorseBP");
	pElem_dwHorseBP->SetAttribute("value", NumberToString(s.dwHorseBP).c_str());
	pElem_dwHorseBP->SetAttribute("comment", ToUTF8Ptr("坐骑战斗力"));
	if(rElement.LinkEndChild(pElem_dwHorseBP.get()) != NULL)
		pElem_dwHorseBP.release();
	unique_ptr<TiXmlElement> pElem_dwDujieBP(new TiXmlElement("UINT32"));
	if(pElem_dwDujieBP == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwDujieBP->SetAttribute("name", "dwDujieBP");
	pElem_dwDujieBP->SetAttribute("value", NumberToString(s.dwDujieBP).c_str());
	pElem_dwDujieBP->SetAttribute("comment", ToUTF8Ptr("渡劫战斗力"));
	if(rElement.LinkEndChild(pElem_dwDujieBP.get()) != NULL)
		pElem_dwDujieBP.release();
	unique_ptr<TiXmlElement> pElem_dwXinfaBP(new TiXmlElement("UINT32"));
	if(pElem_dwXinfaBP == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwXinfaBP->SetAttribute("name", "dwXinfaBP");
	pElem_dwXinfaBP->SetAttribute("value", NumberToString(s.dwXinfaBP).c_str());
	pElem_dwXinfaBP->SetAttribute("comment", ToUTF8Ptr("心法战斗力"));
	if(rElement.LinkEndChild(pElem_dwXinfaBP.get()) != NULL)
		pElem_dwXinfaBP.release();
	unique_ptr<TiXmlElement> pElem_dwClanBP(new TiXmlElement("UINT32"));
	if(pElem_dwClanBP == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwClanBP->SetAttribute("name", "dwClanBP");
	pElem_dwClanBP->SetAttribute("value", NumberToString(s.dwClanBP).c_str());
	pElem_dwClanBP->SetAttribute("comment", ToUTF8Ptr("帮派战斗力"));
	if(rElement.LinkEndChild(pElem_dwClanBP.get()) != NULL)
		pElem_dwClanBP.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecCompareData& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SCompareData s;
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

bool VectorToXML(const TVecCompareData& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SCompareData"));
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

} //namespace NCompareBattlePoint
