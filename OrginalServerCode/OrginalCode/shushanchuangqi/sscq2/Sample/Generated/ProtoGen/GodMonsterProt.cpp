/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    GodMonsterProt.cpp
//  Purpose:      天元神兽协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "GodMonsterProt.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NGodMonsterProt
{

#ifdef PROT_USE_XML

const char* EnumValToStr(EMonsterResult e)
{
	switch(e)
	{
	case EMonsterResult_suc:
		return "EMonsterResult_suc";
	case EMonsterResult_ful:
		return "EMonsterResult_ful";
	case EMonsterResult_get:
		return "EMonsterResult_get";
	case EMonsterResult_not:
		return "EMonsterResult_not";
	case EMonsterResult_lack:
		return "EMonsterResult_lack";
	case EMonsterResult_Level:
		return "EMonsterResult_Level";
	case EMonsterResult_Devote:
		return "EMonsterResult_Devote";
	case EMonsterResult_guild:
		return "EMonsterResult_guild";
	case EMonsterResult_Num:
		return "EMonsterResult_Num";
	case EMonsterResult_Err:
		return "EMonsterResult_Err";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EMonsterResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EMonsterResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("EMonsterResult_suc", EMonsterResult_suc));
		mapStr2Val.insert(make_pair("EMonsterResult_ful", EMonsterResult_ful));
		mapStr2Val.insert(make_pair("EMonsterResult_get", EMonsterResult_get));
		mapStr2Val.insert(make_pair("EMonsterResult_not", EMonsterResult_not));
		mapStr2Val.insert(make_pair("EMonsterResult_lack", EMonsterResult_lack));
		mapStr2Val.insert(make_pair("EMonsterResult_Level", EMonsterResult_Level));
		mapStr2Val.insert(make_pair("EMonsterResult_Devote", EMonsterResult_Devote));
		mapStr2Val.insert(make_pair("EMonsterResult_guild", EMonsterResult_guild));
		mapStr2Val.insert(make_pair("EMonsterResult_Num", EMonsterResult_Num));
		mapStr2Val.insert(make_pair("EMonsterResult_Err", EMonsterResult_Err));
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

const char* EnumValToStr(EMonsterPeroid e)
{
	switch(e)
	{
	case EMonsterPeroid_none:
		return "EMonsterPeroid_none";
	case EMonsterPeroid_1:
		return "EMonsterPeroid_1";
	case EMonsterPeroid_2:
		return "EMonsterPeroid_2";
	case EMonsterPeroid_3:
		return "EMonsterPeroid_3";
	case EMonsterPeroid_4:
		return "EMonsterPeroid_4";
	case EMonsterPeroid_5:
		return "EMonsterPeroid_5";
	case EMonsterPeroid_6:
		return "EMonsterPeroid_6";
	case EMonsterPeroid_end:
		return "EMonsterPeroid_end";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EMonsterPeroid& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EMonsterPeroid> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("EMonsterPeroid_none", EMonsterPeroid_none));
		mapStr2Val.insert(make_pair("EMonsterPeroid_1", EMonsterPeroid_1));
		mapStr2Val.insert(make_pair("EMonsterPeroid_2", EMonsterPeroid_2));
		mapStr2Val.insert(make_pair("EMonsterPeroid_3", EMonsterPeroid_3));
		mapStr2Val.insert(make_pair("EMonsterPeroid_4", EMonsterPeroid_4));
		mapStr2Val.insert(make_pair("EMonsterPeroid_5", EMonsterPeroid_5));
		mapStr2Val.insert(make_pair("EMonsterPeroid_6", EMonsterPeroid_6));
		mapStr2Val.insert(make_pair("EMonsterPeroid_end", EMonsterPeroid_end));
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

const char* EnumValToStr(EMonsterPrizeType e)
{
	switch(e)
	{
	case EMonsterPrize_Begin:
		return "EMonsterPrize_Begin";
	case EMonsterPrize_1:
		return "EMonsterPrize_1";
	case EMonsterPrize_2:
		return "EMonsterPrize_2";
	case EMonsterPrize_3:
		return "EMonsterPrize_3";
	case EMonsterPrize_4:
		return "EMonsterPrize_4";
	case EMonsterPrize_5:
		return "EMonsterPrize_5";
	case EMonsterPrize_End:
		return "EMonsterPrize_End";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EMonsterPrizeType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EMonsterPrizeType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("EMonsterPrize_Begin", EMonsterPrize_Begin));
		mapStr2Val.insert(make_pair("EMonsterPrize_1", EMonsterPrize_1));
		mapStr2Val.insert(make_pair("EMonsterPrize_2", EMonsterPrize_2));
		mapStr2Val.insert(make_pair("EMonsterPrize_3", EMonsterPrize_3));
		mapStr2Val.insert(make_pair("EMonsterPrize_4", EMonsterPrize_4));
		mapStr2Val.insert(make_pair("EMonsterPrize_5", EMonsterPrize_5));
		mapStr2Val.insert(make_pair("EMonsterPrize_End", EMonsterPrize_End));
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

const char* EnumValToStr(EMonsterRank e)
{
	switch(e)
	{
	case EMonsterRank_none:
		return "EMonsterRank_none";
	case EMonsterRank_1:
		return "EMonsterRank_1";
	case EMonsterRank_2:
		return "EMonsterRank_2";
	case EMonsterRank_end:
		return "EMonsterRank_end";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EMonsterRank& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EMonsterRank> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("EMonsterRank_none", EMonsterRank_none));
		mapStr2Val.insert(make_pair("EMonsterRank_1", EMonsterRank_1));
		mapStr2Val.insert(make_pair("EMonsterRank_2", EMonsterRank_2));
		mapStr2Val.insert(make_pair("EMonsterRank_end", EMonsterRank_end));
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

SMonsterRankInfo::SMonsterRankInfo() : dwRank(0), dwScore(0) { }

SMonsterRankInfo::SMonsterRankInfo(UINT32 dwRank_, const std::string& strName_, UINT32 dwScore_) : dwRank(dwRank_), strName(strName_), dwScore(dwScore_) { }

SMonsterRankInfo::SMonsterRankInfo(SMonsterRankInfo&& src) : dwRank(src.dwRank), strName(move(src.strName)), dwScore(src.dwScore) { }

SMonsterRankInfo& SMonsterRankInfo::operator=(SMonsterRankInfo&& rhs)
{
	if(this != &rhs)
	{
		this->~SMonsterRankInfo();
		new (this) SMonsterRankInfo(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SMonsterRankInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.dwRank;
	src >> s.strName;
	src >> s.dwScore;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SMonsterRankInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.dwRank;
	src << s.strName;
	src << s.dwScore;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SMonsterRankInfo& s)
{
	if(strcmp(rElement.Value(), "SMonsterRankInfo") != 0)
	{
		LOG_CRI << "rElement is not SMonsterRankInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwRank is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwRank") != 0)
	{
		LOG_CRI << "Attribute: name is not dwRank!";
		return false;
	}
	const char* pszVal_dwRank = pElemChild->Attribute("value");
	if(pszVal_dwRank == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwRank, s.dwRank))
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
		LOG_CRI << "pElemChild for dwScore is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwScore") != 0)
	{
		LOG_CRI << "Attribute: name is not dwScore!";
		return false;
	}
	const char* pszVal_dwScore = pElemChild->Attribute("value");
	if(pszVal_dwScore == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwScore, s.dwScore))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SMonsterRankInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SMonsterRankInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("排行榜数据"));
	unique_ptr<TiXmlElement> pElem_dwRank(new TiXmlElement("UINT32"));
	if(pElem_dwRank == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwRank->SetAttribute("name", "dwRank");
	pElem_dwRank->SetAttribute("value", NumberToString(s.dwRank).c_str());
	pElem_dwRank->SetAttribute("comment", ToUTF8Ptr("排名"));
	if(rElement.LinkEndChild(pElem_dwRank.get()) != NULL)
		pElem_dwRank.release();
	unique_ptr<TiXmlElement> pElem_strName(new TiXmlElement("string"));
	if(pElem_strName == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strName->SetAttribute("name", "strName");
	pElem_strName->SetAttribute("value", s.strName.c_str());
	pElem_strName->SetAttribute("comment", ToUTF8Ptr("名字"));
	if(rElement.LinkEndChild(pElem_strName.get()) != NULL)
		pElem_strName.release();
	unique_ptr<TiXmlElement> pElem_dwScore(new TiXmlElement("UINT32"));
	if(pElem_dwScore == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwScore->SetAttribute("name", "dwScore");
	pElem_dwScore->SetAttribute("value", NumberToString(s.dwScore).c_str());
	pElem_dwScore->SetAttribute("comment", ToUTF8Ptr("积分"));
	if(rElement.LinkEndChild(pElem_dwScore.get()) != NULL)
		pElem_dwScore.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecMonsterRankInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SMonsterRankInfo s;
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

bool VectorToXML(const TVecMonsterRankInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SMonsterRankInfo"));
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

SMonsterRank::SMonsterRank() : eRank((EMonsterRank)0) { }

SMonsterRank::SMonsterRank(EMonsterRank eRank_, const TVecMonsterRankInfo& vecRankInfo_) : eRank(eRank_), vecRankInfo(vecRankInfo_) { }

SMonsterRank::SMonsterRank(SMonsterRank&& src) : eRank(src.eRank), vecRankInfo(move(src.vecRankInfo)) { }

SMonsterRank& SMonsterRank::operator=(SMonsterRank&& rhs)
{
	if(this != &rhs)
	{
		this->~SMonsterRank();
		new (this) SMonsterRank(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SMonsterRank& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (UINT8&)s.eRank;
	src >> s.vecRankInfo;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SMonsterRank& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (UINT8&)s.eRank;
	src << s.vecRankInfo;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SMonsterRank& s)
{
	if(strcmp(rElement.Value(), "SMonsterRank") != 0)
	{
		LOG_CRI << "rElement is not SMonsterRank!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eRank is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "EMonsterRank") != 0)
	{
		LOG_CRI << "pElemChild is not EMonsterRank!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eRank") != 0)
	{
		LOG_CRI << "Attribute: name is not eRank!";
		return false;
	}
	const char* pszVal_eRank = pElemChild->Attribute("value");
	if(pszVal_eRank == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!EnumStrToVal(pszVal_eRank, s.eRank))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecRankInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecMonsterRankInfo") != 0)
	{
		LOG_CRI << "pElemChild is not TVecMonsterRankInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecRankInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not vecRankInfo!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecRankInfo))
	{
		LOG_CRI << "VectorFromXML for vecRankInfo fails!";
		return false;
	}
	return true;
}

bool ToXML(const SMonsterRank& s, TiXmlElement& rElement)
{
	rElement.SetValue("SMonsterRank");
	rElement.SetAttribute("type", ToUTF8Ptr("排行榜"));
	unique_ptr<TiXmlElement> pElem_eRank(new TiXmlElement("EMonsterRank"));
	if(pElem_eRank == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eRank->SetAttribute("name", "eRank");
	const char* pszEnum_eRank = EnumValToStr(s.eRank);
	if(pszEnum_eRank == NULL)
	{
		LOG_CRI << "EnumValToStr for EMonsterRank fails!";
		return false;
	}
	pElem_eRank->SetAttribute("value", pszEnum_eRank);
	pElem_eRank->SetAttribute("comment", ToUTF8Ptr("排名"));
	if(rElement.LinkEndChild(pElem_eRank.get()) != NULL)
		pElem_eRank.release();
	unique_ptr<TiXmlElement> pElem_vecRankInfo(new TiXmlElement("TVecMonsterRankInfo"));
	if(pElem_vecRankInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecRankInfo->SetAttribute("name", "vecRankInfo");
	if(!VectorToXML(s.vecRankInfo, *pElem_vecRankInfo))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecRankInfo->SetAttribute("comment", ToUTF8Ptr("数据"));
	if(rElement.LinkEndChild(pElem_vecRankInfo.get()) != NULL)
		pElem_vecRankInfo.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecMonsterRank& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SMonsterRank s;
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

bool VectorToXML(const TVecMonsterRank& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SMonsterRank"));
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

SMonsterPrize::SMonsterPrize() : eType((EMonsterPrizeType)0), byType(0) { }

SMonsterPrize::SMonsterPrize(EMonsterPrizeType eType_, UINT8 byType_) : eType(eType_), byType(byType_) { }

CInArchive& operator>>(CInArchive& src, SMonsterPrize& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (UINT8&)s.eType;
	src >> s.byType;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SMonsterPrize& s)
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
	src << s.byType;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SMonsterPrize& s)
{
	if(strcmp(rElement.Value(), "SMonsterPrize") != 0)
	{
		LOG_CRI << "rElement is not SMonsterPrize!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "EMonsterPrizeType") != 0)
	{
		LOG_CRI << "pElemChild is not EMonsterPrizeType!";
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
		LOG_CRI << "pElemChild for byType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byType") != 0)
	{
		LOG_CRI << "Attribute: name is not byType!";
		return false;
	}
	const char* pszVal_byType = pElemChild->Attribute("value");
	if(pszVal_byType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byType, s.byType))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SMonsterPrize& s, TiXmlElement& rElement)
{
	rElement.SetValue("SMonsterPrize");
	rElement.SetAttribute("type", ToUTF8Ptr("排行榜"));
	unique_ptr<TiXmlElement> pElem_eType(new TiXmlElement("EMonsterPrizeType"));
	if(pElem_eType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eType->SetAttribute("name", "eType");
	const char* pszEnum_eType = EnumValToStr(s.eType);
	if(pszEnum_eType == NULL)
	{
		LOG_CRI << "EnumValToStr for EMonsterPrizeType fails!";
		return false;
	}
	pElem_eType->SetAttribute("value", pszEnum_eType);
	pElem_eType->SetAttribute("comment", ToUTF8Ptr("奖励类型"));
	if(rElement.LinkEndChild(pElem_eType.get()) != NULL)
		pElem_eType.release();
	unique_ptr<TiXmlElement> pElem_byType(new TiXmlElement("UINT8"));
	if(pElem_byType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byType->SetAttribute("name", "byType");
	pElem_byType->SetAttribute("value", NumberToString(s.byType).c_str());
	pElem_byType->SetAttribute("comment", ToUTF8Ptr("0表示条件未达到，1表示可以领取，2表示已经领取"));
	if(rElement.LinkEndChild(pElem_byType.get()) != NULL)
		pElem_byType.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecMonsterPrize& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SMonsterPrize s;
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

bool VectorToXML(const TVecMonsterPrize& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SMonsterPrize"));
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

SGuildUserDevote::SGuildUserDevote() : qwRoleID(0), dwScore(0) { }

SGuildUserDevote::SGuildUserDevote(UINT64 qwRoleID_, const std::string& strName_, const std::string& strLevel_, UINT32 dwScore_) : qwRoleID(qwRoleID_), strName(strName_), strLevel(strLevel_), dwScore(dwScore_) { }

SGuildUserDevote::SGuildUserDevote(SGuildUserDevote&& src) : qwRoleID(src.qwRoleID), strName(move(src.strName)), strLevel(move(src.strLevel)), dwScore(src.dwScore) { }

SGuildUserDevote& SGuildUserDevote::operator=(SGuildUserDevote&& rhs)
{
	if(this != &rhs)
	{
		this->~SGuildUserDevote();
		new (this) SGuildUserDevote(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SGuildUserDevote& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwRoleID;
	src >> s.strName;
	src >> s.strLevel;
	src >> s.dwScore;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SGuildUserDevote& s)
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
	src << s.strLevel;
	src << s.dwScore;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SGuildUserDevote& s)
{
	if(strcmp(rElement.Value(), "SGuildUserDevote") != 0)
	{
		LOG_CRI << "rElement is not SGuildUserDevote!";
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
		LOG_CRI << "pElemChild for strLevel is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strLevel") != 0)
	{
		LOG_CRI << "Attribute: name is not strLevel!";
		return false;
	}
	const char* pszVal_strLevel = pElemChild->Attribute("value");
	if(pszVal_strLevel == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strLevel = pszVal_strLevel;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwScore is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwScore") != 0)
	{
		LOG_CRI << "Attribute: name is not dwScore!";
		return false;
	}
	const char* pszVal_dwScore = pElemChild->Attribute("value");
	if(pszVal_dwScore == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwScore, s.dwScore))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SGuildUserDevote& s, TiXmlElement& rElement)
{
	rElement.SetValue("SGuildUserDevote");
	rElement.SetAttribute("type", ToUTF8Ptr("帮派成员贡献"));
	unique_ptr<TiXmlElement> pElem_qwRoleID(new TiXmlElement("UINT64"));
	if(pElem_qwRoleID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwRoleID->SetAttribute("name", "qwRoleID");
	pElem_qwRoleID->SetAttribute("value", NumberToString(s.qwRoleID).c_str());
	pElem_qwRoleID->SetAttribute("comment", ToUTF8Ptr("ID"));
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
	pElem_strName->SetAttribute("comment", ToUTF8Ptr("名字"));
	if(rElement.LinkEndChild(pElem_strName.get()) != NULL)
		pElem_strName.release();
	unique_ptr<TiXmlElement> pElem_strLevel(new TiXmlElement("string"));
	if(pElem_strLevel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strLevel->SetAttribute("name", "strLevel");
	pElem_strLevel->SetAttribute("value", s.strLevel.c_str());
	pElem_strLevel->SetAttribute("comment", ToUTF8Ptr("职务"));
	if(rElement.LinkEndChild(pElem_strLevel.get()) != NULL)
		pElem_strLevel.release();
	unique_ptr<TiXmlElement> pElem_dwScore(new TiXmlElement("UINT32"));
	if(pElem_dwScore == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwScore->SetAttribute("name", "dwScore");
	pElem_dwScore->SetAttribute("value", NumberToString(s.dwScore).c_str());
	pElem_dwScore->SetAttribute("comment", ToUTF8Ptr("积分"));
	if(rElement.LinkEndChild(pElem_dwScore.get()) != NULL)
		pElem_dwScore.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecGuildUserDevote& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SGuildUserDevote s;
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

bool VectorToXML(const TVecGuildUserDevote& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SGuildUserDevote"));
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

SLimitPrize::SLimitPrize() : wPrizeID(0), wCurNum(0), wMaxNum(0) { }

SLimitPrize::SLimitPrize(UINT16 wPrizeID_, UINT16 wCurNum_, UINT16 wMaxNum_) : wPrizeID(wPrizeID_), wCurNum(wCurNum_), wMaxNum(wMaxNum_) { }

CInArchive& operator>>(CInArchive& src, SLimitPrize& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.wPrizeID;
	src >> s.wCurNum;
	src >> s.wMaxNum;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SLimitPrize& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.wPrizeID;
	src << s.wCurNum;
	src << s.wMaxNum;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SLimitPrize& s)
{
	if(strcmp(rElement.Value(), "SLimitPrize") != 0)
	{
		LOG_CRI << "rElement is not SLimitPrize!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wPrizeID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wPrizeID") != 0)
	{
		LOG_CRI << "Attribute: name is not wPrizeID!";
		return false;
	}
	const char* pszVal_wPrizeID = pElemChild->Attribute("value");
	if(pszVal_wPrizeID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wPrizeID, s.wPrizeID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wCurNum is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wCurNum") != 0)
	{
		LOG_CRI << "Attribute: name is not wCurNum!";
		return false;
	}
	const char* pszVal_wCurNum = pElemChild->Attribute("value");
	if(pszVal_wCurNum == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wCurNum, s.wCurNum))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wMaxNum is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wMaxNum") != 0)
	{
		LOG_CRI << "Attribute: name is not wMaxNum!";
		return false;
	}
	const char* pszVal_wMaxNum = pElemChild->Attribute("value");
	if(pszVal_wMaxNum == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wMaxNum, s.wMaxNum))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SLimitPrize& s, TiXmlElement& rElement)
{
	rElement.SetValue("SLimitPrize");
	rElement.SetAttribute("type", ToUTF8Ptr("限购礼包"));
	unique_ptr<TiXmlElement> pElem_wPrizeID(new TiXmlElement("UINT16"));
	if(pElem_wPrizeID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wPrizeID->SetAttribute("name", "wPrizeID");
	pElem_wPrizeID->SetAttribute("value", NumberToString(s.wPrizeID).c_str());
	pElem_wPrizeID->SetAttribute("comment", ToUTF8Ptr("礼品ID"));
	if(rElement.LinkEndChild(pElem_wPrizeID.get()) != NULL)
		pElem_wPrizeID.release();
	unique_ptr<TiXmlElement> pElem_wCurNum(new TiXmlElement("UINT16"));
	if(pElem_wCurNum == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wCurNum->SetAttribute("name", "wCurNum");
	pElem_wCurNum->SetAttribute("value", NumberToString(s.wCurNum).c_str());
	pElem_wCurNum->SetAttribute("comment", ToUTF8Ptr("已经购买数量"));
	if(rElement.LinkEndChild(pElem_wCurNum.get()) != NULL)
		pElem_wCurNum.release();
	unique_ptr<TiXmlElement> pElem_wMaxNum(new TiXmlElement("UINT16"));
	if(pElem_wMaxNum == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wMaxNum->SetAttribute("name", "wMaxNum");
	pElem_wMaxNum->SetAttribute("value", NumberToString(s.wMaxNum).c_str());
	pElem_wMaxNum->SetAttribute("comment", ToUTF8Ptr("最大值"));
	if(rElement.LinkEndChild(pElem_wMaxNum.get()) != NULL)
		pElem_wMaxNum.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecLimitPrize& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SLimitPrize s;
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

bool VectorToXML(const TVecLimitPrize& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SLimitPrize"));
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

SyncInfoToClient::SyncInfoToClient() : ePeroid((EMonsterPeroid)0), dwPersonScore(0), dwGuildScore(0), dwPersonDevote(0), dwPersonRank(0), 
			dwGuildRank(0), dwFruit(0) { }

SyncInfoToClient::SyncInfoToClient(SyncInfoToClient&& src) : ePeroid(src.ePeroid), dwPersonScore(src.dwPersonScore), dwGuildScore(src.dwGuildScore), dwPersonDevote(src.dwPersonDevote), dwPersonRank(src.dwPersonRank), 
			dwGuildRank(src.dwGuildRank), dwFruit(src.dwFruit), vecPrize(move(src.vecPrize)), vecRank(move(src.vecRank)), vecUser(move(src.vecUser)), 
			vecLimitPrize(move(src.vecLimitPrize)) { }

SyncInfoToClient& SyncInfoToClient::operator=(SyncInfoToClient&& rhs)
{
	if(this != &rhs)
	{
		this->~SyncInfoToClient();
		new (this) SyncInfoToClient(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SyncInfoToClient& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (UINT8&)s.ePeroid;
	src >> s.dwPersonScore;
	src >> s.dwGuildScore;
	src >> s.dwPersonDevote;
	src >> s.dwPersonRank;
	src >> s.dwGuildRank;
	src >> s.dwFruit;
	src >> s.vecPrize;
	src >> s.vecRank;
	src >> s.vecUser;
	src >> s.vecLimitPrize;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SyncInfoToClient& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (UINT8&)s.ePeroid;
	src << s.dwPersonScore;
	src << s.dwGuildScore;
	src << s.dwPersonDevote;
	src << s.dwPersonRank;
	src << s.dwGuildRank;
	src << s.dwFruit;
	src << s.vecPrize;
	src << s.vecRank;
	src << s.vecUser;
	src << s.vecLimitPrize;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SyncInfoToClient& s)
{
	if(strcmp(rElement.Value(), "SyncInfoToClient") != 0)
	{
		LOG_CRI << "rElement is not SyncInfoToClient!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for ePeroid is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "EMonsterPeroid") != 0)
	{
		LOG_CRI << "pElemChild is not EMonsterPeroid!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "ePeroid") != 0)
	{
		LOG_CRI << "Attribute: name is not ePeroid!";
		return false;
	}
	const char* pszVal_ePeroid = pElemChild->Attribute("value");
	if(pszVal_ePeroid == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!EnumStrToVal(pszVal_ePeroid, s.ePeroid))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwPersonScore is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwPersonScore") != 0)
	{
		LOG_CRI << "Attribute: name is not dwPersonScore!";
		return false;
	}
	const char* pszVal_dwPersonScore = pElemChild->Attribute("value");
	if(pszVal_dwPersonScore == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwPersonScore, s.dwPersonScore))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwGuildScore is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwGuildScore") != 0)
	{
		LOG_CRI << "Attribute: name is not dwGuildScore!";
		return false;
	}
	const char* pszVal_dwGuildScore = pElemChild->Attribute("value");
	if(pszVal_dwGuildScore == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwGuildScore, s.dwGuildScore))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwPersonDevote is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwPersonDevote") != 0)
	{
		LOG_CRI << "Attribute: name is not dwPersonDevote!";
		return false;
	}
	const char* pszVal_dwPersonDevote = pElemChild->Attribute("value");
	if(pszVal_dwPersonDevote == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwPersonDevote, s.dwPersonDevote))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwPersonRank is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwPersonRank") != 0)
	{
		LOG_CRI << "Attribute: name is not dwPersonRank!";
		return false;
	}
	const char* pszVal_dwPersonRank = pElemChild->Attribute("value");
	if(pszVal_dwPersonRank == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwPersonRank, s.dwPersonRank))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwGuildRank is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwGuildRank") != 0)
	{
		LOG_CRI << "Attribute: name is not dwGuildRank!";
		return false;
	}
	const char* pszVal_dwGuildRank = pElemChild->Attribute("value");
	if(pszVal_dwGuildRank == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwGuildRank, s.dwGuildRank))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwFruit is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwFruit") != 0)
	{
		LOG_CRI << "Attribute: name is not dwFruit!";
		return false;
	}
	const char* pszVal_dwFruit = pElemChild->Attribute("value");
	if(pszVal_dwFruit == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwFruit, s.dwFruit))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecPrize is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecMonsterPrize") != 0)
	{
		LOG_CRI << "pElemChild is not TVecMonsterPrize!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecPrize") != 0)
	{
		LOG_CRI << "Attribute: name is not vecPrize!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecPrize))
	{
		LOG_CRI << "VectorFromXML for vecPrize fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecRank is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecMonsterRank") != 0)
	{
		LOG_CRI << "pElemChild is not TVecMonsterRank!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecRank") != 0)
	{
		LOG_CRI << "Attribute: name is not vecRank!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecRank))
	{
		LOG_CRI << "VectorFromXML for vecRank fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecUser is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecGuildUserDevote") != 0)
	{
		LOG_CRI << "pElemChild is not TVecGuildUserDevote!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecUser") != 0)
	{
		LOG_CRI << "Attribute: name is not vecUser!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecUser))
	{
		LOG_CRI << "VectorFromXML for vecUser fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecLimitPrize is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecLimitPrize") != 0)
	{
		LOG_CRI << "pElemChild is not TVecLimitPrize!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecLimitPrize") != 0)
	{
		LOG_CRI << "Attribute: name is not vecLimitPrize!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecLimitPrize))
	{
		LOG_CRI << "VectorFromXML for vecLimitPrize fails!";
		return false;
	}
	return true;
}

bool ToXML(const SyncInfoToClient& s, TiXmlElement& rElement)
{
	rElement.SetValue("SyncInfoToClient");
	rElement.SetAttribute("type", ToUTF8Ptr("发送给客户端的数据"));
	unique_ptr<TiXmlElement> pElem_ePeroid(new TiXmlElement("EMonsterPeroid"));
	if(pElem_ePeroid == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_ePeroid->SetAttribute("name", "ePeroid");
	const char* pszEnum_ePeroid = EnumValToStr(s.ePeroid);
	if(pszEnum_ePeroid == NULL)
	{
		LOG_CRI << "EnumValToStr for EMonsterPeroid fails!";
		return false;
	}
	pElem_ePeroid->SetAttribute("value", pszEnum_ePeroid);
	pElem_ePeroid->SetAttribute("comment", ToUTF8Ptr("神兽阶段"));
	if(rElement.LinkEndChild(pElem_ePeroid.get()) != NULL)
		pElem_ePeroid.release();
	unique_ptr<TiXmlElement> pElem_dwPersonScore(new TiXmlElement("UINT32"));
	if(pElem_dwPersonScore == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwPersonScore->SetAttribute("name", "dwPersonScore");
	pElem_dwPersonScore->SetAttribute("value", NumberToString(s.dwPersonScore).c_str());
	pElem_dwPersonScore->SetAttribute("comment", ToUTF8Ptr("个人总积分"));
	if(rElement.LinkEndChild(pElem_dwPersonScore.get()) != NULL)
		pElem_dwPersonScore.release();
	unique_ptr<TiXmlElement> pElem_dwGuildScore(new TiXmlElement("UINT32"));
	if(pElem_dwGuildScore == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwGuildScore->SetAttribute("name", "dwGuildScore");
	pElem_dwGuildScore->SetAttribute("value", NumberToString(s.dwGuildScore).c_str());
	pElem_dwGuildScore->SetAttribute("comment", ToUTF8Ptr("帮派总积分"));
	if(rElement.LinkEndChild(pElem_dwGuildScore.get()) != NULL)
		pElem_dwGuildScore.release();
	unique_ptr<TiXmlElement> pElem_dwPersonDevote(new TiXmlElement("UINT32"));
	if(pElem_dwPersonDevote == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwPersonDevote->SetAttribute("name", "dwPersonDevote");
	pElem_dwPersonDevote->SetAttribute("value", NumberToString(s.dwPersonDevote).c_str());
	pElem_dwPersonDevote->SetAttribute("comment", ToUTF8Ptr("个人贡献值"));
	if(rElement.LinkEndChild(pElem_dwPersonDevote.get()) != NULL)
		pElem_dwPersonDevote.release();
	unique_ptr<TiXmlElement> pElem_dwPersonRank(new TiXmlElement("UINT32"));
	if(pElem_dwPersonRank == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwPersonRank->SetAttribute("name", "dwPersonRank");
	pElem_dwPersonRank->SetAttribute("value", NumberToString(s.dwPersonRank).c_str());
	pElem_dwPersonRank->SetAttribute("comment", ToUTF8Ptr("个人总排名"));
	if(rElement.LinkEndChild(pElem_dwPersonRank.get()) != NULL)
		pElem_dwPersonRank.release();
	unique_ptr<TiXmlElement> pElem_dwGuildRank(new TiXmlElement("UINT32"));
	if(pElem_dwGuildRank == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwGuildRank->SetAttribute("name", "dwGuildRank");
	pElem_dwGuildRank->SetAttribute("value", NumberToString(s.dwGuildRank).c_str());
	pElem_dwGuildRank->SetAttribute("comment", ToUTF8Ptr("帮派总排名"));
	if(rElement.LinkEndChild(pElem_dwGuildRank.get()) != NULL)
		pElem_dwGuildRank.release();
	unique_ptr<TiXmlElement> pElem_dwFruit(new TiXmlElement("UINT32"));
	if(pElem_dwFruit == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwFruit->SetAttribute("name", "dwFruit");
	pElem_dwFruit->SetAttribute("value", NumberToString(s.dwFruit).c_str());
	pElem_dwFruit->SetAttribute("comment", ToUTF8Ptr("朱果数量"));
	if(rElement.LinkEndChild(pElem_dwFruit.get()) != NULL)
		pElem_dwFruit.release();
	unique_ptr<TiXmlElement> pElem_vecPrize(new TiXmlElement("TVecMonsterPrize"));
	if(pElem_vecPrize == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecPrize->SetAttribute("name", "vecPrize");
	if(!VectorToXML(s.vecPrize, *pElem_vecPrize))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecPrize->SetAttribute("comment", ToUTF8Ptr("奖励数据"));
	if(rElement.LinkEndChild(pElem_vecPrize.get()) != NULL)
		pElem_vecPrize.release();
	unique_ptr<TiXmlElement> pElem_vecRank(new TiXmlElement("TVecMonsterRank"));
	if(pElem_vecRank == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecRank->SetAttribute("name", "vecRank");
	if(!VectorToXML(s.vecRank, *pElem_vecRank))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecRank->SetAttribute("comment", ToUTF8Ptr("排行榜数据"));
	if(rElement.LinkEndChild(pElem_vecRank.get()) != NULL)
		pElem_vecRank.release();
	unique_ptr<TiXmlElement> pElem_vecUser(new TiXmlElement("TVecGuildUserDevote"));
	if(pElem_vecUser == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecUser->SetAttribute("name", "vecUser");
	if(!VectorToXML(s.vecUser, *pElem_vecUser))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecUser->SetAttribute("comment", ToUTF8Ptr("成员贡献数据"));
	if(rElement.LinkEndChild(pElem_vecUser.get()) != NULL)
		pElem_vecUser.release();
	unique_ptr<TiXmlElement> pElem_vecLimitPrize(new TiXmlElement("TVecLimitPrize"));
	if(pElem_vecLimitPrize == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecLimitPrize->SetAttribute("name", "vecLimitPrize");
	if(!VectorToXML(s.vecLimitPrize, *pElem_vecLimitPrize))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecLimitPrize->SetAttribute("comment", ToUTF8Ptr("玩家限购礼包数据"));
	if(rElement.LinkEndChild(pElem_vecLimitPrize.get()) != NULL)
		pElem_vecLimitPrize.release();
	return true;
}

#endif

SGuildUser2DB::SGuildUser2DB() : qwRoleID(0), qwGuildID(0), dwFruit(0), dwScore(0), dwTotalScore(0) { }

SGuildUser2DB::SGuildUser2DB(UINT64 qwRoleID_, UINT64 qwGuildID_, UINT32 dwFruit_, UINT32 dwScore_, UINT32 dwTotalScore_)
			: qwRoleID(qwRoleID_), qwGuildID(qwGuildID_), dwFruit(dwFruit_), dwScore(dwScore_), dwTotalScore(dwTotalScore_) { }

CInArchive& operator>>(CInArchive& src, SGuildUser2DB& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwRoleID;
	src >> s.qwGuildID;
	src >> s.dwFruit;
	src >> s.dwScore;
	src >> s.dwTotalScore;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SGuildUser2DB& s)
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
	src << s.qwGuildID;
	src << s.dwFruit;
	src << s.dwScore;
	src << s.dwTotalScore;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SGuildUser2DB& s)
{
	if(strcmp(rElement.Value(), "SGuildUser2DB") != 0)
	{
		LOG_CRI << "rElement is not SGuildUser2DB!";
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
		LOG_CRI << "pElemChild for dwFruit is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwFruit") != 0)
	{
		LOG_CRI << "Attribute: name is not dwFruit!";
		return false;
	}
	const char* pszVal_dwFruit = pElemChild->Attribute("value");
	if(pszVal_dwFruit == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwFruit, s.dwFruit))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwScore is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwScore") != 0)
	{
		LOG_CRI << "Attribute: name is not dwScore!";
		return false;
	}
	const char* pszVal_dwScore = pElemChild->Attribute("value");
	if(pszVal_dwScore == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwScore, s.dwScore))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwTotalScore is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwTotalScore") != 0)
	{
		LOG_CRI << "Attribute: name is not dwTotalScore!";
		return false;
	}
	const char* pszVal_dwTotalScore = pElemChild->Attribute("value");
	if(pszVal_dwTotalScore == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwTotalScore, s.dwTotalScore))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SGuildUser2DB& s, TiXmlElement& rElement)
{
	rElement.SetValue("SGuildUser2DB");
	rElement.SetAttribute("type", ToUTF8Ptr("DB Operator"));
	unique_ptr<TiXmlElement> pElem_qwRoleID(new TiXmlElement("UINT64"));
	if(pElem_qwRoleID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwRoleID->SetAttribute("name", "qwRoleID");
	pElem_qwRoleID->SetAttribute("value", NumberToString(s.qwRoleID).c_str());
	pElem_qwRoleID->SetAttribute("comment", ToUTF8Ptr("名字"));
	if(rElement.LinkEndChild(pElem_qwRoleID.get()) != NULL)
		pElem_qwRoleID.release();
	unique_ptr<TiXmlElement> pElem_qwGuildID(new TiXmlElement("UINT64"));
	if(pElem_qwGuildID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwGuildID->SetAttribute("name", "qwGuildID");
	pElem_qwGuildID->SetAttribute("value", NumberToString(s.qwGuildID).c_str());
	pElem_qwGuildID->SetAttribute("comment", ToUTF8Ptr("职务"));
	if(rElement.LinkEndChild(pElem_qwGuildID.get()) != NULL)
		pElem_qwGuildID.release();
	unique_ptr<TiXmlElement> pElem_dwFruit(new TiXmlElement("UINT32"));
	if(pElem_dwFruit == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwFruit->SetAttribute("name", "dwFruit");
	pElem_dwFruit->SetAttribute("value", NumberToString(s.dwFruit).c_str());
	pElem_dwFruit->SetAttribute("comment", ToUTF8Ptr("朱果数量"));
	if(rElement.LinkEndChild(pElem_dwFruit.get()) != NULL)
		pElem_dwFruit.release();
	unique_ptr<TiXmlElement> pElem_dwScore(new TiXmlElement("UINT32"));
	if(pElem_dwScore == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwScore->SetAttribute("name", "dwScore");
	pElem_dwScore->SetAttribute("value", NumberToString(s.dwScore).c_str());
	pElem_dwScore->SetAttribute("comment", ToUTF8Ptr("积分"));
	if(rElement.LinkEndChild(pElem_dwScore.get()) != NULL)
		pElem_dwScore.release();
	unique_ptr<TiXmlElement> pElem_dwTotalScore(new TiXmlElement("UINT32"));
	if(pElem_dwTotalScore == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwTotalScore->SetAttribute("name", "dwTotalScore");
	pElem_dwTotalScore->SetAttribute("value", NumberToString(s.dwTotalScore).c_str());
	pElem_dwTotalScore->SetAttribute("comment", ToUTF8Ptr("总积分"));
	if(rElement.LinkEndChild(pElem_dwTotalScore.get()) != NULL)
		pElem_dwTotalScore.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecGuildUser2DB& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SGuildUser2DB s;
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

bool VectorToXML(const TVecGuildUser2DB& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SGuildUser2DB"));
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

SLimitPrize2DB::SLimitPrize2DB() : qwRoleID(0), wPrizeID(0), wNum(0) { }

SLimitPrize2DB::SLimitPrize2DB(UINT64 qwRoleID_, UINT16 wPrizeID_, UINT16 wNum_) : qwRoleID(qwRoleID_), wPrizeID(wPrizeID_), wNum(wNum_) { }

CInArchive& operator>>(CInArchive& src, SLimitPrize2DB& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwRoleID;
	src >> s.wPrizeID;
	src >> s.wNum;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SLimitPrize2DB& s)
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
	src << s.wPrizeID;
	src << s.wNum;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SLimitPrize2DB& s)
{
	if(strcmp(rElement.Value(), "SLimitPrize2DB") != 0)
	{
		LOG_CRI << "rElement is not SLimitPrize2DB!";
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
		LOG_CRI << "pElemChild for wPrizeID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wPrizeID") != 0)
	{
		LOG_CRI << "Attribute: name is not wPrizeID!";
		return false;
	}
	const char* pszVal_wPrizeID = pElemChild->Attribute("value");
	if(pszVal_wPrizeID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wPrizeID, s.wPrizeID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wNum is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wNum") != 0)
	{
		LOG_CRI << "Attribute: name is not wNum!";
		return false;
	}
	const char* pszVal_wNum = pElemChild->Attribute("value");
	if(pszVal_wNum == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wNum, s.wNum))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SLimitPrize2DB& s, TiXmlElement& rElement)
{
	rElement.SetValue("SLimitPrize2DB");
	rElement.SetAttribute("type", ToUTF8Ptr("DB Operator"));
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
	unique_ptr<TiXmlElement> pElem_wPrizeID(new TiXmlElement("UINT16"));
	if(pElem_wPrizeID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wPrizeID->SetAttribute("name", "wPrizeID");
	pElem_wPrizeID->SetAttribute("value", NumberToString(s.wPrizeID).c_str());
	pElem_wPrizeID->SetAttribute("comment", ToUTF8Ptr("礼品ID"));
	if(rElement.LinkEndChild(pElem_wPrizeID.get()) != NULL)
		pElem_wPrizeID.release();
	unique_ptr<TiXmlElement> pElem_wNum(new TiXmlElement("UINT16"));
	if(pElem_wNum == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wNum->SetAttribute("name", "wNum");
	pElem_wNum->SetAttribute("value", NumberToString(s.wNum).c_str());
	pElem_wNum->SetAttribute("comment", ToUTF8Ptr("购买数量"));
	if(rElement.LinkEndChild(pElem_wNum.get()) != NULL)
		pElem_wNum.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecLimitPrize2DB& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SLimitPrize2DB s;
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

bool VectorToXML(const TVecLimitPrize2DB& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SLimitPrize2DB"));
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

} //namespace NGodMonsterProt
