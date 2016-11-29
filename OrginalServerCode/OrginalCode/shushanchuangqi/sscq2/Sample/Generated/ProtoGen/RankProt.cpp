/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    RankProt.cpp
//  Purpose:      排行榜相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "RankProt.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NRankProt
{

#ifdef PROT_USE_XML

const char* EnumValToStr(ERankType e)
{
	switch(e)
	{
	case eRTNone:
		return "eRTNone";
	case eRTHead:
		return "eRTHead";
	case eRTRoleRankBegin:
		return "eRTRoleRankBegin";
	case eRTLevel:
		return "eRTLevel";
	case eRTFormation:
		return "eRTFormation";
	case eRTHeroFighter:
		return "eRTHeroFighter";
	case eRTTrump:
		return "eRTTrump";
	case eRTArena:
		return "eRTArena";
	case eRTGuildRankBegin:
		return "eRTGuildRankBegin";
	case eRTGuildRankEnd:
		return "eRTGuildRankEnd";
	case eRTMax:
		return "eRTMax";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, ERankType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, ERankType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eRTNone", eRTNone));
		mapStr2Val.insert(make_pair("eRTHead", eRTHead));
		mapStr2Val.insert(make_pair("eRTRoleRankBegin", eRTRoleRankBegin));
		mapStr2Val.insert(make_pair("eRTLevel", eRTLevel));
		mapStr2Val.insert(make_pair("eRTFormation", eRTFormation));
		mapStr2Val.insert(make_pair("eRTHeroFighter", eRTHeroFighter));
		mapStr2Val.insert(make_pair("eRTTrump", eRTTrump));
		mapStr2Val.insert(make_pair("eRTArena", eRTArena));
		mapStr2Val.insert(make_pair("eRTGuildRankBegin", eRTGuildRankBegin));
		mapStr2Val.insert(make_pair("eRTGuildRankEnd", eRTGuildRankEnd));
		mapStr2Val.insert(make_pair("eRTMax", eRTMax));
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

const char* EnumValToStr(ERankResult e)
{
	switch(e)
	{
	case eRRSuccess:
		return "eRRSuccess";
	case eRRFailed:
		return "eRRFailed";
	case eRRNotExist:
		return "eRRNotExist";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, ERankResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, ERankResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eRRSuccess", eRRSuccess));
		mapStr2Val.insert(make_pair("eRRFailed", eRRFailed));
		mapStr2Val.insert(make_pair("eRRNotExist", eRRNotExist));
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

const char* EnumValToStr(EAdoreResult e)
{
	switch(e)
	{
	case eARSuccess:
		return "eARSuccess";
	case eARFailed:
		return "eARFailed";
	case eARNotExist:
		return "eARNotExist";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EAdoreResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EAdoreResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eARSuccess", eARSuccess));
		mapStr2Val.insert(make_pair("eARFailed", eARFailed));
		mapStr2Val.insert(make_pair("eARNotExist", eARNotExist));
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

SRankInfo::SRankInfo() : dwValue(0), dwUpdateTime(0) { }

CInArchive& operator>>(CInArchive& src, SRankInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.dwValue;
	src >> s.dwUpdateTime;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SRankInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.dwValue;
	src << s.dwUpdateTime;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, SRankInfo_Wrapper& rWrapper)
{
	EType_SRankInfo eType = eType_SRankInfo;
	src >> (UINT8&)eType;
	switch(eType)
	{
	case eType_SRankInfo:
		{
			rWrapper.ptr.reset(new SRankInfo);
			src >> (SRankInfo&)*rWrapper.ptr;
		}
		break;
	case eType_SRoleHeadInfo:
		{
			rWrapper.ptr.reset(new SRoleHeadInfo);
			src >> (SRoleHeadInfo&)*rWrapper.ptr;
		}
		break;
	case eType_SRoleRankInfo:
		{
			rWrapper.ptr.reset(new SRoleRankInfo);
			src >> (SRoleRankInfo&)*rWrapper.ptr;
		}
		break;
	case eType_SGuildRankInfo:
		{
			rWrapper.ptr.reset(new SGuildRankInfo);
			src >> (SGuildRankInfo&)*rWrapper.ptr;
		}
		break;
	case eType_SRRBattlePointInfo:
		{
			rWrapper.ptr.reset(new SRRBattlePointInfo);
			src >> (SRRBattlePointInfo&)*rWrapper.ptr;
		}
		break;
	case eType_SRRLevelInfo:
		{
			rWrapper.ptr.reset(new SRRLevelInfo);
			src >> (SRRLevelInfo&)*rWrapper.ptr;
		}
		break;
	case eType_SRRFormationInfo:
		{
			rWrapper.ptr.reset(new SRRFormationInfo);
			src >> (SRRFormationInfo&)*rWrapper.ptr;
		}
		break;
	case eType_SRRHeroFighterInfo:
		{
			rWrapper.ptr.reset(new SRRHeroFighterInfo);
			src >> (SRRHeroFighterInfo&)*rWrapper.ptr;
		}
		break;
	case eType_SRRTrumpInfo:
		{
			rWrapper.ptr.reset(new SRRTrumpInfo);
			src >> (SRRTrumpInfo&)*rWrapper.ptr;
		}
		break;
	case eType_SRRArenaInfo:
		{
			rWrapper.ptr.reset(new SRRArenaInfo);
			src >> (SRRArenaInfo&)*rWrapper.ptr;
		}
		break;
	case eType_SGRBattleInfo:
		{
			rWrapper.ptr.reset(new SGRBattleInfo);
			src >> (SGRBattleInfo&)*rWrapper.ptr;
		}
		break;
	case eType_SGRLevelInfo:
		{
			rWrapper.ptr.reset(new SGRLevelInfo);
			src >> (SGRLevelInfo&)*rWrapper.ptr;
		}
		break;
	default:
		throw "Unknown value for EType_SRankInfo";
		break;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SRankInfo_Wrapper& rWrapper)
{
	if(rWrapper.ptr != NULL)
	{
		src << (UINT8)rWrapper.ptr->GetClassType();
		switch(rWrapper.ptr->GetClassType())
		{
		case eType_SRankInfo:
			src << (SRankInfo&)*rWrapper.ptr;
			break;
		case eType_SRoleHeadInfo:
			src << (SRoleHeadInfo&)*rWrapper.ptr;
			break;
		case eType_SRoleRankInfo:
			src << (SRoleRankInfo&)*rWrapper.ptr;
			break;
		case eType_SGuildRankInfo:
			src << (SGuildRankInfo&)*rWrapper.ptr;
			break;
		case eType_SRRBattlePointInfo:
			src << (SRRBattlePointInfo&)*rWrapper.ptr;
			break;
		case eType_SRRLevelInfo:
			src << (SRRLevelInfo&)*rWrapper.ptr;
			break;
		case eType_SRRFormationInfo:
			src << (SRRFormationInfo&)*rWrapper.ptr;
			break;
		case eType_SRRHeroFighterInfo:
			src << (SRRHeroFighterInfo&)*rWrapper.ptr;
			break;
		case eType_SRRTrumpInfo:
			src << (SRRTrumpInfo&)*rWrapper.ptr;
			break;
		case eType_SRRArenaInfo:
			src << (SRRArenaInfo&)*rWrapper.ptr;
			break;
		case eType_SGRBattleInfo:
			src << (SGRBattleInfo&)*rWrapper.ptr;
			break;
		case eType_SGRLevelInfo:
			src << (SGRLevelInfo&)*rWrapper.ptr;
			break;
		default:
			throw "Unknown value for EType_SRankInfo";
			break;
		}
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecRankInfo& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SRankInfo_Wrapper wrapper;
		src >> wrapper;
		vec[i] = wrapper.ptr;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecRankInfo& vec)
{
	if(vec.size() > 0x7FFF)
		throw "Vector Size Too Large!";
	UINT16 wSize = (UINT16)vec.size();
	src.WriteContainerSize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SRankInfo_Wrapper wrapper;
		wrapper.ptr = vec[i];
		src << wrapper;
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SRankInfo& s)
{
	if(strcmp(rElement.Value(), "SRankInfo") != 0)
	{
		LOG_CRI << "rElement is not SRankInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwValue is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwValue") != 0)
	{
		LOG_CRI << "Attribute: name is not dwValue!";
		return false;
	}
	const char* pszVal_dwValue = pElemChild->Attribute("value");
	if(pszVal_dwValue == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwValue, s.dwValue))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwUpdateTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwUpdateTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwUpdateTime!";
		return false;
	}
	const char* pszVal_dwUpdateTime = pElemChild->Attribute("value");
	if(pszVal_dwUpdateTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwUpdateTime, s.dwUpdateTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SRankInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SRankInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("排名信息"));
	unique_ptr<TiXmlElement> pElem_dwValue(new TiXmlElement("UINT32"));
	if(pElem_dwValue == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwValue->SetAttribute("name", "dwValue");
	pElem_dwValue->SetAttribute("value", NumberToString(s.dwValue).c_str());
	pElem_dwValue->SetAttribute("comment", ToUTF8Ptr("排名依据的信息(战斗力/等级……)"));
	if(rElement.LinkEndChild(pElem_dwValue.get()) != NULL)
		pElem_dwValue.release();
	unique_ptr<TiXmlElement> pElem_dwUpdateTime(new TiXmlElement("UINT32"));
	if(pElem_dwUpdateTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwUpdateTime->SetAttribute("name", "dwUpdateTime");
	pElem_dwUpdateTime->SetAttribute("value", NumberToString(s.dwUpdateTime).c_str());
	pElem_dwUpdateTime->SetAttribute("comment", ToUTF8Ptr("更新时间"));
	if(rElement.LinkEndChild(pElem_dwUpdateTime.get()) != NULL)
		pElem_dwUpdateTime.release();
	return true;
}

bool SuperFromXML(TiXmlElement& rElement, SRankInfoPtr& p)
{
	const char* pszName = rElement.Value();
	if(pszName == NULL)
	{
		LOG_CRI << "Element Name is empty!";
		return false;
	}
	if(strcmp(pszName, "SRankInfo") == 0)
	{
		SRankInfoPtr pStruct(new SRankInfo);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SRankInfo";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SRankInfo FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SRoleHeadInfo") == 0)
	{
		SRoleHeadInfoPtr pStruct(new SRoleHeadInfo);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SRoleHeadInfo";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SRoleHeadInfo FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SRoleRankInfo") == 0)
	{
		SRoleRankInfoPtr pStruct(new SRoleRankInfo);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SRoleRankInfo";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SRoleRankInfo FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SGuildRankInfo") == 0)
	{
		SGuildRankInfoPtr pStruct(new SGuildRankInfo);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SGuildRankInfo";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SGuildRankInfo FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SRRBattlePointInfo") == 0)
	{
		SRRBattlePointInfoPtr pStruct(new SRRBattlePointInfo);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SRRBattlePointInfo";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SRRBattlePointInfo FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SRRLevelInfo") == 0)
	{
		SRRLevelInfoPtr pStruct(new SRRLevelInfo);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SRRLevelInfo";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SRRLevelInfo FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SRRFormationInfo") == 0)
	{
		SRRFormationInfoPtr pStruct(new SRRFormationInfo);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SRRFormationInfo";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SRRFormationInfo FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SRRHeroFighterInfo") == 0)
	{
		SRRHeroFighterInfoPtr pStruct(new SRRHeroFighterInfo);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SRRHeroFighterInfo";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SRRHeroFighterInfo FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SRRTrumpInfo") == 0)
	{
		SRRTrumpInfoPtr pStruct(new SRRTrumpInfo);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SRRTrumpInfo";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SRRTrumpInfo FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SRRArenaInfo") == 0)
	{
		SRRArenaInfoPtr pStruct(new SRRArenaInfo);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SRRArenaInfo";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SRRArenaInfo FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SGRBattleInfo") == 0)
	{
		SGRBattleInfoPtr pStruct(new SGRBattleInfo);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SGRBattleInfo";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SGRBattleInfo FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SGRLevelInfo") == 0)
	{
		SGRLevelInfoPtr pStruct(new SGRLevelInfo);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SGRLevelInfo";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SGRLevelInfo FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else
	{
		LOG_CRI << "Invalid name: " << pszName << "!";
		return false;
	}
	return true;
}

bool SuperToXML(const SRankInfo& s, TiXmlElement& rElement)
{
	switch(s.GetClassType())
	{
	case eType_SRankInfo:
		return ToXML((SRankInfo&)s, rElement);
	case eType_SRoleHeadInfo:
		return ToXML((SRoleHeadInfo&)s, rElement);
	case eType_SRoleRankInfo:
		return ToXML((SRoleRankInfo&)s, rElement);
	case eType_SGuildRankInfo:
		return ToXML((SGuildRankInfo&)s, rElement);
	case eType_SRRBattlePointInfo:
		return ToXML((SRRBattlePointInfo&)s, rElement);
	case eType_SRRLevelInfo:
		return ToXML((SRRLevelInfo&)s, rElement);
	case eType_SRRFormationInfo:
		return ToXML((SRRFormationInfo&)s, rElement);
	case eType_SRRHeroFighterInfo:
		return ToXML((SRRHeroFighterInfo&)s, rElement);
	case eType_SRRTrumpInfo:
		return ToXML((SRRTrumpInfo&)s, rElement);
	case eType_SRRArenaInfo:
		return ToXML((SRRArenaInfo&)s, rElement);
	case eType_SGRBattleInfo:
		return ToXML((SGRBattleInfo&)s, rElement);
	case eType_SGRLevelInfo:
		return ToXML((SGRLevelInfo&)s, rElement);
	default:
		LOG_CRI << "Invalid type: " << s.GetClassType();
		return false;
	}
}

bool VectorFromXML(TiXmlElement& rElement, TVecRankInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SRankInfoPtr p;
		if(!SuperFromXML(*pElemMember, p))
		{
			LOG_CRI << "SuperFromXML fails!";
			return false;
		}
		vec.push_back(p);
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecRankInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SRankInfo"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!SuperToXML(*vec[i], *pElemMember))
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

SRoleHeadInfo::SRoleHeadInfo() : eType((ERankType)0), qwRoleID(0), wID(0), wPlayerFighterID(0), byQuality(0), 
			byInfoQuality(0) { }

SRoleHeadInfo::SRoleHeadInfo(SRoleHeadInfo&& src) : SRankInfo(src), eType(src.eType), qwRoleID(src.qwRoleID), strName(move(src.strName)), wID(src.wID), wPlayerFighterID(src.wPlayerFighterID), 
			byQuality(src.byQuality), byInfoQuality(src.byInfoQuality), strGuildName(move(src.strGuildName)) { }

SRoleHeadInfo& SRoleHeadInfo::operator=(SRoleHeadInfo&& rhs)
{
	if(this != &rhs)
	{
		this->~SRoleHeadInfo();
		new (this) SRoleHeadInfo(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SRoleHeadInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (SRankInfo&)s;
	src >> (UINT8&)s.eType;
	src >> s.qwRoleID;
	src >> s.strName;
	src >> s.wID;
	src >> s.wPlayerFighterID;
	src >> s.byQuality;
	src >> s.byInfoQuality;
	src >> s.strGuildName;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SRoleHeadInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const SRankInfo&)s;
	src << (UINT8&)s.eType;
	src << s.qwRoleID;
	src << s.strName;
	src << s.wID;
	src << s.wPlayerFighterID;
	src << s.byQuality;
	src << s.byInfoQuality;
	src << s.strGuildName;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecRoleHeadInfo& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SRoleHeadInfoPtr p(new SRoleHeadInfo);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecRoleHeadInfo& vec)
{
	if(vec.size() > 0x7FFF)
		throw "Vector Size Too Large!";
	UINT16 wSize = (UINT16)vec.size();
	src.WriteContainerSize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
		src << *vec[i];
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SRoleHeadInfo& s)
{
	if(strcmp(rElement.Value(), "SRoleHeadInfo") != 0)
	{
		LOG_CRI << "rElement is not SRoleHeadInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for SRankInfo is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (SRankInfo&)s))
	{
		LOG_CRI << "FromXML for: SRankInfo fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "ERankType") != 0)
	{
		LOG_CRI << "pElemChild is not ERankType!";
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
		LOG_CRI << "pElemChild for wID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wID") != 0)
	{
		LOG_CRI << "Attribute: name is not wID!";
		return false;
	}
	const char* pszVal_wID = pElemChild->Attribute("value");
	if(pszVal_wID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wID, s.wID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wPlayerFighterID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wPlayerFighterID") != 0)
	{
		LOG_CRI << "Attribute: name is not wPlayerFighterID!";
		return false;
	}
	const char* pszVal_wPlayerFighterID = pElemChild->Attribute("value");
	if(pszVal_wPlayerFighterID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wPlayerFighterID, s.wPlayerFighterID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byQuality is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byQuality") != 0)
	{
		LOG_CRI << "Attribute: name is not byQuality!";
		return false;
	}
	const char* pszVal_byQuality = pElemChild->Attribute("value");
	if(pszVal_byQuality == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byQuality, s.byQuality))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byInfoQuality is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byInfoQuality") != 0)
	{
		LOG_CRI << "Attribute: name is not byInfoQuality!";
		return false;
	}
	const char* pszVal_byInfoQuality = pElemChild->Attribute("value");
	if(pszVal_byInfoQuality == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byInfoQuality, s.byInfoQuality))
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
	return true;
}

bool ToXML(const SRoleHeadInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SRoleHeadInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("魁首榜"));
	unique_ptr<TiXmlElement> pElem_SRankInfo(new TiXmlElement("SRankInfo"));
	if(pElem_SRankInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const SRankInfo&)s, *pElem_SRankInfo))
	{
		LOG_CRI << "SRankInfo ToXML fails!";
		return false;
	}
	pElem_SRankInfo->SetAttribute("type", ToUTF8Ptr("排名信息"));
	pElem_SRankInfo->SetAttribute("comment", ToUTF8Ptr("父类SRankInfo部分"));
	if(rElement.LinkEndChild(pElem_SRankInfo.get()) != NULL)
		pElem_SRankInfo.release();
	unique_ptr<TiXmlElement> pElem_eType(new TiXmlElement("ERankType"));
	if(pElem_eType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eType->SetAttribute("name", "eType");
	const char* pszEnum_eType = EnumValToStr(s.eType);
	if(pszEnum_eType == NULL)
	{
		LOG_CRI << "EnumValToStr for ERankType fails!";
		return false;
	}
	pElem_eType->SetAttribute("value", pszEnum_eType);
	pElem_eType->SetAttribute("comment", ToUTF8Ptr("排行榜类型"));
	if(rElement.LinkEndChild(pElem_eType.get()) != NULL)
		pElem_eType.release();
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
	pElem_strName->SetAttribute("comment", ToUTF8Ptr("玩家姓名"));
	if(rElement.LinkEndChild(pElem_strName.get()) != NULL)
		pElem_strName.release();
	unique_ptr<TiXmlElement> pElem_wID(new TiXmlElement("UINT16"));
	if(pElem_wID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wID->SetAttribute("name", "wID");
	pElem_wID->SetAttribute("value", NumberToString(s.wID).c_str());
	pElem_wID->SetAttribute("comment", ToUTF8Ptr("对应ID"));
	if(rElement.LinkEndChild(pElem_wID.get()) != NULL)
		pElem_wID.release();
	unique_ptr<TiXmlElement> pElem_wPlayerFighterID(new TiXmlElement("UINT16"));
	if(pElem_wPlayerFighterID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wPlayerFighterID->SetAttribute("name", "wPlayerFighterID");
	pElem_wPlayerFighterID->SetAttribute("value", NumberToString(s.wPlayerFighterID).c_str());
	pElem_wPlayerFighterID->SetAttribute("comment", ToUTF8Ptr("主将ID"));
	if(rElement.LinkEndChild(pElem_wPlayerFighterID.get()) != NULL)
		pElem_wPlayerFighterID.release();
	unique_ptr<TiXmlElement> pElem_byQuality(new TiXmlElement("UINT8"));
	if(pElem_byQuality == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byQuality->SetAttribute("name", "byQuality");
	pElem_byQuality->SetAttribute("value", NumberToString(s.byQuality).c_str());
	pElem_byQuality->SetAttribute("comment", ToUTF8Ptr("主将品质(颜色)"));
	if(rElement.LinkEndChild(pElem_byQuality.get()) != NULL)
		pElem_byQuality.release();
	unique_ptr<TiXmlElement> pElem_byInfoQuality(new TiXmlElement("UINT8"));
	if(pElem_byInfoQuality == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byInfoQuality->SetAttribute("name", "byInfoQuality");
	pElem_byInfoQuality->SetAttribute("value", NumberToString(s.byInfoQuality).c_str());
	pElem_byInfoQuality->SetAttribute("comment", ToUTF8Ptr("魁首品质(颜色)"));
	if(rElement.LinkEndChild(pElem_byInfoQuality.get()) != NULL)
		pElem_byInfoQuality.release();
	unique_ptr<TiXmlElement> pElem_strGuildName(new TiXmlElement("string"));
	if(pElem_strGuildName == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strGuildName->SetAttribute("name", "strGuildName");
	pElem_strGuildName->SetAttribute("value", s.strGuildName.c_str());
	pElem_strGuildName->SetAttribute("comment", ToUTF8Ptr("帮派名字"));
	if(rElement.LinkEndChild(pElem_strGuildName.get()) != NULL)
		pElem_strGuildName.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecRoleHeadInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SRoleHeadInfoPtr p(new SRoleHeadInfo);
		if(!FromXML(*pElemMember, *p))
		{
			LOG_CRI << "FromXML fails!";
			return false;
		}
		vec.push_back(p);
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecRoleHeadInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SRoleHeadInfo"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!ToXML(*vec[i], *pElemMember))
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

SRoleRankInfo::SRoleRankInfo() : qwRoleID(0), wPlayerFighterID(0), byQuality(0), byVIPLevel(0) { }

SRoleRankInfo::SRoleRankInfo(SRoleRankInfo&& src) : SRankInfo(src), qwRoleID(src.qwRoleID), strName(move(src.strName)), wPlayerFighterID(src.wPlayerFighterID), byQuality(src.byQuality), byVIPLevel(src.byVIPLevel), 
			vecPlatforms(move(src.vecPlatforms)) { }

SRoleRankInfo& SRoleRankInfo::operator=(SRoleRankInfo&& rhs)
{
	if(this != &rhs)
	{
		this->~SRoleRankInfo();
		new (this) SRoleRankInfo(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SRoleRankInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (SRankInfo&)s;
	src >> s.qwRoleID;
	src >> s.strName;
	src >> s.wPlayerFighterID;
	src >> s.byQuality;
	src >> s.byVIPLevel;
	src >> s.vecPlatforms;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SRoleRankInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const SRankInfo&)s;
	src << s.qwRoleID;
	src << s.strName;
	src << s.wPlayerFighterID;
	src << s.byQuality;
	src << s.byVIPLevel;
	src << s.vecPlatforms;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, SRoleRankInfo_Wrapper& rWrapper)
{
	EType_SRankInfo eType = eType_SRankInfo;
	src >> (UINT8&)eType;
	switch(eType)
	{
	case eType_SRoleRankInfo:
		{
			rWrapper.ptr.reset(new SRoleRankInfo);
			src >> (SRoleRankInfo&)*rWrapper.ptr;
		}
		break;
	case eType_SRRBattlePointInfo:
		{
			rWrapper.ptr.reset(new SRRBattlePointInfo);
			src >> (SRRBattlePointInfo&)*rWrapper.ptr;
		}
		break;
	case eType_SRRLevelInfo:
		{
			rWrapper.ptr.reset(new SRRLevelInfo);
			src >> (SRRLevelInfo&)*rWrapper.ptr;
		}
		break;
	case eType_SRRFormationInfo:
		{
			rWrapper.ptr.reset(new SRRFormationInfo);
			src >> (SRRFormationInfo&)*rWrapper.ptr;
		}
		break;
	case eType_SRRHeroFighterInfo:
		{
			rWrapper.ptr.reset(new SRRHeroFighterInfo);
			src >> (SRRHeroFighterInfo&)*rWrapper.ptr;
		}
		break;
	case eType_SRRTrumpInfo:
		{
			rWrapper.ptr.reset(new SRRTrumpInfo);
			src >> (SRRTrumpInfo&)*rWrapper.ptr;
		}
		break;
	case eType_SRRArenaInfo:
		{
			rWrapper.ptr.reset(new SRRArenaInfo);
			src >> (SRRArenaInfo&)*rWrapper.ptr;
		}
		break;
	default:
		throw "Unknown value for EType_SRankInfo";
		break;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SRoleRankInfo_Wrapper& rWrapper)
{
	if(rWrapper.ptr != NULL)
	{
		src << (UINT8)rWrapper.ptr->GetClassType();
		switch(rWrapper.ptr->GetClassType())
		{
		case eType_SRoleRankInfo:
			src << (SRoleRankInfo&)*rWrapper.ptr;
			break;
		case eType_SRRBattlePointInfo:
			src << (SRRBattlePointInfo&)*rWrapper.ptr;
			break;
		case eType_SRRLevelInfo:
			src << (SRRLevelInfo&)*rWrapper.ptr;
			break;
		case eType_SRRFormationInfo:
			src << (SRRFormationInfo&)*rWrapper.ptr;
			break;
		case eType_SRRHeroFighterInfo:
			src << (SRRHeroFighterInfo&)*rWrapper.ptr;
			break;
		case eType_SRRTrumpInfo:
			src << (SRRTrumpInfo&)*rWrapper.ptr;
			break;
		case eType_SRRArenaInfo:
			src << (SRRArenaInfo&)*rWrapper.ptr;
			break;
		default:
			throw "Unknown value for EType_SRankInfo";
			break;
		}
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecRoleRankInfo& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SRoleRankInfo_Wrapper wrapper;
		src >> wrapper;
		vec[i] = wrapper.ptr;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecRoleRankInfo& vec)
{
	if(vec.size() > 0x7FFF)
		throw "Vector Size Too Large!";
	UINT16 wSize = (UINT16)vec.size();
	src.WriteContainerSize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SRoleRankInfo_Wrapper wrapper;
		wrapper.ptr = vec[i];
		src << wrapper;
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SRoleRankInfo& s)
{
	if(strcmp(rElement.Value(), "SRoleRankInfo") != 0)
	{
		LOG_CRI << "rElement is not SRoleRankInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for SRankInfo is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (SRankInfo&)s))
	{
		LOG_CRI << "FromXML for: SRankInfo fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
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
		LOG_CRI << "pElemChild for wPlayerFighterID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wPlayerFighterID") != 0)
	{
		LOG_CRI << "Attribute: name is not wPlayerFighterID!";
		return false;
	}
	const char* pszVal_wPlayerFighterID = pElemChild->Attribute("value");
	if(pszVal_wPlayerFighterID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wPlayerFighterID, s.wPlayerFighterID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byQuality is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byQuality") != 0)
	{
		LOG_CRI << "Attribute: name is not byQuality!";
		return false;
	}
	const char* pszVal_byQuality = pElemChild->Attribute("value");
	if(pszVal_byQuality == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byQuality, s.byQuality))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byVIPLevel is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byVIPLevel") != 0)
	{
		LOG_CRI << "Attribute: name is not byVIPLevel!";
		return false;
	}
	const char* pszVal_byVIPLevel = pElemChild->Attribute("value");
	if(pszVal_byVIPLevel == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byVIPLevel, s.byVIPLevel))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecPlatforms is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "ProtoCommon::TVecPlatformParam") != 0)
	{
		LOG_CRI << "pElemChild is not ProtoCommon::TVecPlatformParam!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecPlatforms") != 0)
	{
		LOG_CRI << "Attribute: name is not vecPlatforms!";
		return false;
	}
	if(!NProtoCommon::VectorFromXML(*pElemChild, s.vecPlatforms))
	{
		LOG_CRI << "VectorFromXML for vecPlatforms fails!";
		return false;
	}
	return true;
}

bool ToXML(const SRoleRankInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SRoleRankInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("玩家相关排名信息"));
	unique_ptr<TiXmlElement> pElem_SRankInfo(new TiXmlElement("SRankInfo"));
	if(pElem_SRankInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const SRankInfo&)s, *pElem_SRankInfo))
	{
		LOG_CRI << "SRankInfo ToXML fails!";
		return false;
	}
	pElem_SRankInfo->SetAttribute("type", ToUTF8Ptr("排名信息"));
	pElem_SRankInfo->SetAttribute("comment", ToUTF8Ptr("父类SRankInfo部分"));
	if(rElement.LinkEndChild(pElem_SRankInfo.get()) != NULL)
		pElem_SRankInfo.release();
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
	pElem_strName->SetAttribute("comment", ToUTF8Ptr("玩家姓名"));
	if(rElement.LinkEndChild(pElem_strName.get()) != NULL)
		pElem_strName.release();
	unique_ptr<TiXmlElement> pElem_wPlayerFighterID(new TiXmlElement("UINT16"));
	if(pElem_wPlayerFighterID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wPlayerFighterID->SetAttribute("name", "wPlayerFighterID");
	pElem_wPlayerFighterID->SetAttribute("value", NumberToString(s.wPlayerFighterID).c_str());
	pElem_wPlayerFighterID->SetAttribute("comment", ToUTF8Ptr("主将ID"));
	if(rElement.LinkEndChild(pElem_wPlayerFighterID.get()) != NULL)
		pElem_wPlayerFighterID.release();
	unique_ptr<TiXmlElement> pElem_byQuality(new TiXmlElement("UINT8"));
	if(pElem_byQuality == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byQuality->SetAttribute("name", "byQuality");
	pElem_byQuality->SetAttribute("value", NumberToString(s.byQuality).c_str());
	pElem_byQuality->SetAttribute("comment", ToUTF8Ptr("散仙品质(颜色)"));
	if(rElement.LinkEndChild(pElem_byQuality.get()) != NULL)
		pElem_byQuality.release();
	unique_ptr<TiXmlElement> pElem_byVIPLevel(new TiXmlElement("UINT8"));
	if(pElem_byVIPLevel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byVIPLevel->SetAttribute("name", "byVIPLevel");
	pElem_byVIPLevel->SetAttribute("value", NumberToString(s.byVIPLevel).c_str());
	pElem_byVIPLevel->SetAttribute("comment", ToUTF8Ptr("玩家VIP等级"));
	if(rElement.LinkEndChild(pElem_byVIPLevel.get()) != NULL)
		pElem_byVIPLevel.release();
	unique_ptr<TiXmlElement> pElem_vecPlatforms(new TiXmlElement("ProtoCommon::TVecPlatformParam"));
	if(pElem_vecPlatforms == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecPlatforms->SetAttribute("name", "vecPlatforms");
	if(!NProtoCommon::VectorToXML(s.vecPlatforms, *pElem_vecPlatforms))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecPlatforms->SetAttribute("comment", ToUTF8Ptr("平台信息"));
	if(rElement.LinkEndChild(pElem_vecPlatforms.get()) != NULL)
		pElem_vecPlatforms.release();
	return true;
}

bool SuperFromXML(TiXmlElement& rElement, SRoleRankInfoPtr& p)
{
	const char* pszName = rElement.Value();
	if(pszName == NULL)
	{
		LOG_CRI << "Element Name is empty!";
		return false;
	}
	if(strcmp(pszName, "SRoleRankInfo") == 0)
	{
		SRoleRankInfoPtr pStruct(new SRoleRankInfo);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SRoleRankInfo";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SRoleRankInfo FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SRRBattlePointInfo") == 0)
	{
		SRRBattlePointInfoPtr pStruct(new SRRBattlePointInfo);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SRRBattlePointInfo";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SRRBattlePointInfo FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SRRLevelInfo") == 0)
	{
		SRRLevelInfoPtr pStruct(new SRRLevelInfo);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SRRLevelInfo";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SRRLevelInfo FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SRRFormationInfo") == 0)
	{
		SRRFormationInfoPtr pStruct(new SRRFormationInfo);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SRRFormationInfo";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SRRFormationInfo FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SRRHeroFighterInfo") == 0)
	{
		SRRHeroFighterInfoPtr pStruct(new SRRHeroFighterInfo);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SRRHeroFighterInfo";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SRRHeroFighterInfo FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SRRTrumpInfo") == 0)
	{
		SRRTrumpInfoPtr pStruct(new SRRTrumpInfo);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SRRTrumpInfo";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SRRTrumpInfo FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SRRArenaInfo") == 0)
	{
		SRRArenaInfoPtr pStruct(new SRRArenaInfo);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SRRArenaInfo";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SRRArenaInfo FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else
	{
		LOG_CRI << "Invalid name: " << pszName << "!";
		return false;
	}
	return true;
}

bool SuperToXML(const SRoleRankInfo& s, TiXmlElement& rElement)
{
	switch(s.GetClassType())
	{
	case eType_SRoleRankInfo:
		return ToXML((SRoleRankInfo&)s, rElement);
	case eType_SRRBattlePointInfo:
		return ToXML((SRRBattlePointInfo&)s, rElement);
	case eType_SRRLevelInfo:
		return ToXML((SRRLevelInfo&)s, rElement);
	case eType_SRRFormationInfo:
		return ToXML((SRRFormationInfo&)s, rElement);
	case eType_SRRHeroFighterInfo:
		return ToXML((SRRHeroFighterInfo&)s, rElement);
	case eType_SRRTrumpInfo:
		return ToXML((SRRTrumpInfo&)s, rElement);
	case eType_SRRArenaInfo:
		return ToXML((SRRArenaInfo&)s, rElement);
	default:
		LOG_CRI << "Invalid type: " << s.GetClassType();
		return false;
	}
}

bool VectorFromXML(TiXmlElement& rElement, TVecRoleRankInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SRoleRankInfoPtr p;
		if(!SuperFromXML(*pElemMember, p))
		{
			LOG_CRI << "SuperFromXML fails!";
			return false;
		}
		vec.push_back(p);
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecRoleRankInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SRoleRankInfo"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!SuperToXML(*vec[i], *pElemMember))
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

SRRBattlePointInfo::SRRBattlePointInfo() : dwBattlePoint(0) { }

SRRBattlePointInfo::SRRBattlePointInfo(SRRBattlePointInfo&& src) : SRoleRankInfo(src), dwBattlePoint(src.dwBattlePoint), strGuildName(move(src.strGuildName)) { }

SRRBattlePointInfo& SRRBattlePointInfo::operator=(SRRBattlePointInfo&& rhs)
{
	if(this != &rhs)
	{
		this->~SRRBattlePointInfo();
		new (this) SRRBattlePointInfo(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SRRBattlePointInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (SRoleRankInfo&)s;
	src >> s.dwBattlePoint;
	src >> s.strGuildName;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SRRBattlePointInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const SRoleRankInfo&)s;
	src << s.dwBattlePoint;
	src << s.strGuildName;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecRRBattlePointInfo& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SRRBattlePointInfoPtr p(new SRRBattlePointInfo);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecRRBattlePointInfo& vec)
{
	if(vec.size() > 0x7FFF)
		throw "Vector Size Too Large!";
	UINT16 wSize = (UINT16)vec.size();
	src.WriteContainerSize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
		src << *vec[i];
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SRRBattlePointInfo& s)
{
	if(strcmp(rElement.Value(), "SRRBattlePointInfo") != 0)
	{
		LOG_CRI << "rElement is not SRRBattlePointInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for SRoleRankInfo is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (SRoleRankInfo&)s))
	{
		LOG_CRI << "FromXML for: SRoleRankInfo fails!";
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
	return true;
}

bool ToXML(const SRRBattlePointInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SRRBattlePointInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("战力信息"));
	unique_ptr<TiXmlElement> pElem_SRoleRankInfo(new TiXmlElement("SRoleRankInfo"));
	if(pElem_SRoleRankInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const SRoleRankInfo&)s, *pElem_SRoleRankInfo))
	{
		LOG_CRI << "SRoleRankInfo ToXML fails!";
		return false;
	}
	pElem_SRoleRankInfo->SetAttribute("type", ToUTF8Ptr("玩家相关排名信息"));
	pElem_SRoleRankInfo->SetAttribute("comment", ToUTF8Ptr("父类SRoleRankInfo部分"));
	if(rElement.LinkEndChild(pElem_SRoleRankInfo.get()) != NULL)
		pElem_SRoleRankInfo.release();
	unique_ptr<TiXmlElement> pElem_dwBattlePoint(new TiXmlElement("UINT32"));
	if(pElem_dwBattlePoint == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwBattlePoint->SetAttribute("name", "dwBattlePoint");
	pElem_dwBattlePoint->SetAttribute("value", NumberToString(s.dwBattlePoint).c_str());
	pElem_dwBattlePoint->SetAttribute("comment", ToUTF8Ptr("战斗力"));
	if(rElement.LinkEndChild(pElem_dwBattlePoint.get()) != NULL)
		pElem_dwBattlePoint.release();
	unique_ptr<TiXmlElement> pElem_strGuildName(new TiXmlElement("string"));
	if(pElem_strGuildName == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strGuildName->SetAttribute("name", "strGuildName");
	pElem_strGuildName->SetAttribute("value", s.strGuildName.c_str());
	pElem_strGuildName->SetAttribute("comment", ToUTF8Ptr("帮派名称"));
	if(rElement.LinkEndChild(pElem_strGuildName.get()) != NULL)
		pElem_strGuildName.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecRRBattlePointInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SRRBattlePointInfoPtr p(new SRRBattlePointInfo);
		if(!FromXML(*pElemMember, *p))
		{
			LOG_CRI << "FromXML fails!";
			return false;
		}
		vec.push_back(p);
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecRRBattlePointInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SRRBattlePointInfo"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!ToXML(*vec[i], *pElemMember))
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

SRRLevelInfo::SRRLevelInfo() : wLevel(0), qwExp(0) { }

CInArchive& operator>>(CInArchive& src, SRRLevelInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (SRoleRankInfo&)s;
	src >> s.wLevel;
	src >> s.qwExp;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SRRLevelInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const SRoleRankInfo&)s;
	src << s.wLevel;
	src << s.qwExp;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecRRLevelInfo& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SRRLevelInfoPtr p(new SRRLevelInfo);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecRRLevelInfo& vec)
{
	if(vec.size() > 0x7FFF)
		throw "Vector Size Too Large!";
	UINT16 wSize = (UINT16)vec.size();
	src.WriteContainerSize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
		src << *vec[i];
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SRRLevelInfo& s)
{
	if(strcmp(rElement.Value(), "SRRLevelInfo") != 0)
	{
		LOG_CRI << "rElement is not SRRLevelInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for SRoleRankInfo is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (SRoleRankInfo&)s))
	{
		LOG_CRI << "FromXML for: SRoleRankInfo fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wLevel is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wLevel") != 0)
	{
		LOG_CRI << "Attribute: name is not wLevel!";
		return false;
	}
	const char* pszVal_wLevel = pElemChild->Attribute("value");
	if(pszVal_wLevel == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wLevel, s.wLevel))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwExp is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwExp") != 0)
	{
		LOG_CRI << "Attribute: name is not qwExp!";
		return false;
	}
	const char* pszVal_qwExp = pElemChild->Attribute("value");
	if(pszVal_qwExp == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwExp, s.qwExp))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SRRLevelInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SRRLevelInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("等级信息"));
	unique_ptr<TiXmlElement> pElem_SRoleRankInfo(new TiXmlElement("SRoleRankInfo"));
	if(pElem_SRoleRankInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const SRoleRankInfo&)s, *pElem_SRoleRankInfo))
	{
		LOG_CRI << "SRoleRankInfo ToXML fails!";
		return false;
	}
	pElem_SRoleRankInfo->SetAttribute("type", ToUTF8Ptr("玩家相关排名信息"));
	pElem_SRoleRankInfo->SetAttribute("comment", ToUTF8Ptr("父类SRoleRankInfo部分"));
	if(rElement.LinkEndChild(pElem_SRoleRankInfo.get()) != NULL)
		pElem_SRoleRankInfo.release();
	unique_ptr<TiXmlElement> pElem_wLevel(new TiXmlElement("UINT16"));
	if(pElem_wLevel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wLevel->SetAttribute("name", "wLevel");
	pElem_wLevel->SetAttribute("value", NumberToString(s.wLevel).c_str());
	pElem_wLevel->SetAttribute("comment", ToUTF8Ptr("等级"));
	if(rElement.LinkEndChild(pElem_wLevel.get()) != NULL)
		pElem_wLevel.release();
	unique_ptr<TiXmlElement> pElem_qwExp(new TiXmlElement("UINT64"));
	if(pElem_qwExp == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwExp->SetAttribute("name", "qwExp");
	pElem_qwExp->SetAttribute("value", NumberToString(s.qwExp).c_str());
	pElem_qwExp->SetAttribute("comment", ToUTF8Ptr("经验值"));
	if(rElement.LinkEndChild(pElem_qwExp.get()) != NULL)
		pElem_qwExp.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecRRLevelInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SRRLevelInfoPtr p(new SRRLevelInfo);
		if(!FromXML(*pElemMember, *p))
		{
			LOG_CRI << "FromXML fails!";
			return false;
		}
		vec.push_back(p);
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecRRLevelInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SRRLevelInfo"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!ToXML(*vec[i], *pElemMember))
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

SRRFormationInfo::SRRFormationInfo() : dwBattlePoint(0), wID(0) { }

SRRFormationInfo::SRRFormationInfo(SRRFormationInfo&& src) : SRoleRankInfo(src), dwBattlePoint(src.dwBattlePoint), strGuildName(move(src.strGuildName)), wID(src.wID) { }

SRRFormationInfo& SRRFormationInfo::operator=(SRRFormationInfo&& rhs)
{
	if(this != &rhs)
	{
		this->~SRRFormationInfo();
		new (this) SRRFormationInfo(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SRRFormationInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (SRoleRankInfo&)s;
	src >> s.dwBattlePoint;
	src >> s.strGuildName;
	src >> s.wID;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SRRFormationInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const SRoleRankInfo&)s;
	src << s.dwBattlePoint;
	src << s.strGuildName;
	src << s.wID;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecRRFormationInfo& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SRRFormationInfoPtr p(new SRRFormationInfo);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecRRFormationInfo& vec)
{
	if(vec.size() > 0x7FFF)
		throw "Vector Size Too Large!";
	UINT16 wSize = (UINT16)vec.size();
	src.WriteContainerSize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
		src << *vec[i];
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SRRFormationInfo& s)
{
	if(strcmp(rElement.Value(), "SRRFormationInfo") != 0)
	{
		LOG_CRI << "rElement is not SRRFormationInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for SRoleRankInfo is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (SRoleRankInfo&)s))
	{
		LOG_CRI << "FromXML for: SRoleRankInfo fails!";
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
		LOG_CRI << "pElemChild for wID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wID") != 0)
	{
		LOG_CRI << "Attribute: name is not wID!";
		return false;
	}
	const char* pszVal_wID = pElemChild->Attribute("value");
	if(pszVal_wID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wID, s.wID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SRRFormationInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SRRFormationInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("阵灵信息"));
	unique_ptr<TiXmlElement> pElem_SRoleRankInfo(new TiXmlElement("SRoleRankInfo"));
	if(pElem_SRoleRankInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const SRoleRankInfo&)s, *pElem_SRoleRankInfo))
	{
		LOG_CRI << "SRoleRankInfo ToXML fails!";
		return false;
	}
	pElem_SRoleRankInfo->SetAttribute("type", ToUTF8Ptr("玩家相关排名信息"));
	pElem_SRoleRankInfo->SetAttribute("comment", ToUTF8Ptr("父类SRoleRankInfo部分"));
	if(rElement.LinkEndChild(pElem_SRoleRankInfo.get()) != NULL)
		pElem_SRoleRankInfo.release();
	unique_ptr<TiXmlElement> pElem_dwBattlePoint(new TiXmlElement("UINT32"));
	if(pElem_dwBattlePoint == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwBattlePoint->SetAttribute("name", "dwBattlePoint");
	pElem_dwBattlePoint->SetAttribute("value", NumberToString(s.dwBattlePoint).c_str());
	pElem_dwBattlePoint->SetAttribute("comment", ToUTF8Ptr("战斗力"));
	if(rElement.LinkEndChild(pElem_dwBattlePoint.get()) != NULL)
		pElem_dwBattlePoint.release();
	unique_ptr<TiXmlElement> pElem_strGuildName(new TiXmlElement("string"));
	if(pElem_strGuildName == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strGuildName->SetAttribute("name", "strGuildName");
	pElem_strGuildName->SetAttribute("value", s.strGuildName.c_str());
	pElem_strGuildName->SetAttribute("comment", ToUTF8Ptr("帮派名称"));
	if(rElement.LinkEndChild(pElem_strGuildName.get()) != NULL)
		pElem_strGuildName.release();
	unique_ptr<TiXmlElement> pElem_wID(new TiXmlElement("UINT16"));
	if(pElem_wID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wID->SetAttribute("name", "wID");
	pElem_wID->SetAttribute("value", NumberToString(s.wID).c_str());
	pElem_wID->SetAttribute("comment", ToUTF8Ptr("阵灵配置表ID，同monster"));
	if(rElement.LinkEndChild(pElem_wID.get()) != NULL)
		pElem_wID.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecRRFormationInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SRRFormationInfoPtr p(new SRRFormationInfo);
		if(!FromXML(*pElemMember, *p))
		{
			LOG_CRI << "FromXML fails!";
			return false;
		}
		vec.push_back(p);
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecRRFormationInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SRRFormationInfo"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!ToXML(*vec[i], *pElemMember))
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

SRRHeroFighterInfo::SRRHeroFighterInfo() : dwBattlePoint(0), wID(0), byInfoQuality(0) { }

SRRHeroFighterInfo::SRRHeroFighterInfo(SRRHeroFighterInfo&& src) : SRoleRankInfo(src), dwBattlePoint(src.dwBattlePoint), strGuildName(move(src.strGuildName)), wID(src.wID), byInfoQuality(src.byInfoQuality) { }

SRRHeroFighterInfo& SRRHeroFighterInfo::operator=(SRRHeroFighterInfo&& rhs)
{
	if(this != &rhs)
	{
		this->~SRRHeroFighterInfo();
		new (this) SRRHeroFighterInfo(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SRRHeroFighterInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (SRoleRankInfo&)s;
	src >> s.dwBattlePoint;
	src >> s.strGuildName;
	src >> s.wID;
	src >> s.byInfoQuality;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SRRHeroFighterInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const SRoleRankInfo&)s;
	src << s.dwBattlePoint;
	src << s.strGuildName;
	src << s.wID;
	src << s.byInfoQuality;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecRRHeroFighterInfo& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SRRHeroFighterInfoPtr p(new SRRHeroFighterInfo);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecRRHeroFighterInfo& vec)
{
	if(vec.size() > 0x7FFF)
		throw "Vector Size Too Large!";
	UINT16 wSize = (UINT16)vec.size();
	src.WriteContainerSize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
		src << *vec[i];
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SRRHeroFighterInfo& s)
{
	if(strcmp(rElement.Value(), "SRRHeroFighterInfo") != 0)
	{
		LOG_CRI << "rElement is not SRRHeroFighterInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for SRoleRankInfo is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (SRoleRankInfo&)s))
	{
		LOG_CRI << "FromXML for: SRoleRankInfo fails!";
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
		LOG_CRI << "pElemChild for wID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wID") != 0)
	{
		LOG_CRI << "Attribute: name is not wID!";
		return false;
	}
	const char* pszVal_wID = pElemChild->Attribute("value");
	if(pszVal_wID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wID, s.wID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byInfoQuality is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byInfoQuality") != 0)
	{
		LOG_CRI << "Attribute: name is not byInfoQuality!";
		return false;
	}
	const char* pszVal_byInfoQuality = pElemChild->Attribute("value");
	if(pszVal_byInfoQuality == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byInfoQuality, s.byInfoQuality))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SRRHeroFighterInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SRRHeroFighterInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("散仙信息"));
	unique_ptr<TiXmlElement> pElem_SRoleRankInfo(new TiXmlElement("SRoleRankInfo"));
	if(pElem_SRoleRankInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const SRoleRankInfo&)s, *pElem_SRoleRankInfo))
	{
		LOG_CRI << "SRoleRankInfo ToXML fails!";
		return false;
	}
	pElem_SRoleRankInfo->SetAttribute("type", ToUTF8Ptr("玩家相关排名信息"));
	pElem_SRoleRankInfo->SetAttribute("comment", ToUTF8Ptr("父类SRoleRankInfo部分"));
	if(rElement.LinkEndChild(pElem_SRoleRankInfo.get()) != NULL)
		pElem_SRoleRankInfo.release();
	unique_ptr<TiXmlElement> pElem_dwBattlePoint(new TiXmlElement("UINT32"));
	if(pElem_dwBattlePoint == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwBattlePoint->SetAttribute("name", "dwBattlePoint");
	pElem_dwBattlePoint->SetAttribute("value", NumberToString(s.dwBattlePoint).c_str());
	pElem_dwBattlePoint->SetAttribute("comment", ToUTF8Ptr("战斗力"));
	if(rElement.LinkEndChild(pElem_dwBattlePoint.get()) != NULL)
		pElem_dwBattlePoint.release();
	unique_ptr<TiXmlElement> pElem_strGuildName(new TiXmlElement("string"));
	if(pElem_strGuildName == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strGuildName->SetAttribute("name", "strGuildName");
	pElem_strGuildName->SetAttribute("value", s.strGuildName.c_str());
	pElem_strGuildName->SetAttribute("comment", ToUTF8Ptr("帮派名称"));
	if(rElement.LinkEndChild(pElem_strGuildName.get()) != NULL)
		pElem_strGuildName.release();
	unique_ptr<TiXmlElement> pElem_wID(new TiXmlElement("UINT16"));
	if(pElem_wID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wID->SetAttribute("name", "wID");
	pElem_wID->SetAttribute("value", NumberToString(s.wID).c_str());
	pElem_wID->SetAttribute("comment", ToUTF8Ptr("散仙类型"));
	if(rElement.LinkEndChild(pElem_wID.get()) != NULL)
		pElem_wID.release();
	unique_ptr<TiXmlElement> pElem_byInfoQuality(new TiXmlElement("UINT8"));
	if(pElem_byInfoQuality == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byInfoQuality->SetAttribute("name", "byInfoQuality");
	pElem_byInfoQuality->SetAttribute("value", NumberToString(s.byInfoQuality).c_str());
	pElem_byInfoQuality->SetAttribute("comment", ToUTF8Ptr("散仙品质(颜色)"));
	if(rElement.LinkEndChild(pElem_byInfoQuality.get()) != NULL)
		pElem_byInfoQuality.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecRRHeroFighterInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SRRHeroFighterInfoPtr p(new SRRHeroFighterInfo);
		if(!FromXML(*pElemMember, *p))
		{
			LOG_CRI << "FromXML fails!";
			return false;
		}
		vec.push_back(p);
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecRRHeroFighterInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SRRHeroFighterInfo"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!ToXML(*vec[i], *pElemMember))
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

SRRTrumpInfo::SRRTrumpInfo() : dwBattlePoint(0), wID(0) { }

SRRTrumpInfo::SRRTrumpInfo(SRRTrumpInfo&& src) : SRoleRankInfo(src), dwBattlePoint(src.dwBattlePoint), strGuildName(move(src.strGuildName)), wID(src.wID) { }

SRRTrumpInfo& SRRTrumpInfo::operator=(SRRTrumpInfo&& rhs)
{
	if(this != &rhs)
	{
		this->~SRRTrumpInfo();
		new (this) SRRTrumpInfo(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SRRTrumpInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (SRoleRankInfo&)s;
	src >> s.dwBattlePoint;
	src >> s.strGuildName;
	src >> s.wID;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SRRTrumpInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const SRoleRankInfo&)s;
	src << s.dwBattlePoint;
	src << s.strGuildName;
	src << s.wID;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecRRTrumpInfo& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SRRTrumpInfoPtr p(new SRRTrumpInfo);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecRRTrumpInfo& vec)
{
	if(vec.size() > 0x7FFF)
		throw "Vector Size Too Large!";
	UINT16 wSize = (UINT16)vec.size();
	src.WriteContainerSize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
		src << *vec[i];
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SRRTrumpInfo& s)
{
	if(strcmp(rElement.Value(), "SRRTrumpInfo") != 0)
	{
		LOG_CRI << "rElement is not SRRTrumpInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for SRoleRankInfo is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (SRoleRankInfo&)s))
	{
		LOG_CRI << "FromXML for: SRoleRankInfo fails!";
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
		LOG_CRI << "pElemChild for wID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wID") != 0)
	{
		LOG_CRI << "Attribute: name is not wID!";
		return false;
	}
	const char* pszVal_wID = pElemChild->Attribute("value");
	if(pszVal_wID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wID, s.wID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SRRTrumpInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SRRTrumpInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("法宝信息"));
	unique_ptr<TiXmlElement> pElem_SRoleRankInfo(new TiXmlElement("SRoleRankInfo"));
	if(pElem_SRoleRankInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const SRoleRankInfo&)s, *pElem_SRoleRankInfo))
	{
		LOG_CRI << "SRoleRankInfo ToXML fails!";
		return false;
	}
	pElem_SRoleRankInfo->SetAttribute("type", ToUTF8Ptr("玩家相关排名信息"));
	pElem_SRoleRankInfo->SetAttribute("comment", ToUTF8Ptr("父类SRoleRankInfo部分"));
	if(rElement.LinkEndChild(pElem_SRoleRankInfo.get()) != NULL)
		pElem_SRoleRankInfo.release();
	unique_ptr<TiXmlElement> pElem_dwBattlePoint(new TiXmlElement("UINT32"));
	if(pElem_dwBattlePoint == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwBattlePoint->SetAttribute("name", "dwBattlePoint");
	pElem_dwBattlePoint->SetAttribute("value", NumberToString(s.dwBattlePoint).c_str());
	pElem_dwBattlePoint->SetAttribute("comment", ToUTF8Ptr("战斗力"));
	if(rElement.LinkEndChild(pElem_dwBattlePoint.get()) != NULL)
		pElem_dwBattlePoint.release();
	unique_ptr<TiXmlElement> pElem_strGuildName(new TiXmlElement("string"));
	if(pElem_strGuildName == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strGuildName->SetAttribute("name", "strGuildName");
	pElem_strGuildName->SetAttribute("value", s.strGuildName.c_str());
	pElem_strGuildName->SetAttribute("comment", ToUTF8Ptr("帮派名称"));
	if(rElement.LinkEndChild(pElem_strGuildName.get()) != NULL)
		pElem_strGuildName.release();
	unique_ptr<TiXmlElement> pElem_wID(new TiXmlElement("UINT16"));
	if(pElem_wID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wID->SetAttribute("name", "wID");
	pElem_wID->SetAttribute("value", NumberToString(s.wID).c_str());
	pElem_wID->SetAttribute("comment", ToUTF8Ptr("法宝ID"));
	if(rElement.LinkEndChild(pElem_wID.get()) != NULL)
		pElem_wID.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecRRTrumpInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SRRTrumpInfoPtr p(new SRRTrumpInfo);
		if(!FromXML(*pElemMember, *p))
		{
			LOG_CRI << "FromXML fails!";
			return false;
		}
		vec.push_back(p);
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecRRTrumpInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SRRTrumpInfo"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!ToXML(*vec[i], *pElemMember))
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

SRRArenaInfo::SRRArenaInfo() : dwBattlePoint(0) { }

SRRArenaInfo::SRRArenaInfo(SRRArenaInfo&& src) : SRoleRankInfo(src), dwBattlePoint(src.dwBattlePoint), strGuildName(move(src.strGuildName)) { }

SRRArenaInfo& SRRArenaInfo::operator=(SRRArenaInfo&& rhs)
{
	if(this != &rhs)
	{
		this->~SRRArenaInfo();
		new (this) SRRArenaInfo(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SRRArenaInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (SRoleRankInfo&)s;
	src >> s.dwBattlePoint;
	src >> s.strGuildName;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SRRArenaInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const SRoleRankInfo&)s;
	src << s.dwBattlePoint;
	src << s.strGuildName;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecRRArenaInfo& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SRRArenaInfoPtr p(new SRRArenaInfo);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecRRArenaInfo& vec)
{
	if(vec.size() > 0x7FFF)
		throw "Vector Size Too Large!";
	UINT16 wSize = (UINT16)vec.size();
	src.WriteContainerSize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
		src << *vec[i];
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SRRArenaInfo& s)
{
	if(strcmp(rElement.Value(), "SRRArenaInfo") != 0)
	{
		LOG_CRI << "rElement is not SRRArenaInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for SRoleRankInfo is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (SRoleRankInfo&)s))
	{
		LOG_CRI << "FromXML for: SRoleRankInfo fails!";
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
	return true;
}

bool ToXML(const SRRArenaInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SRRArenaInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("斗剑信息"));
	unique_ptr<TiXmlElement> pElem_SRoleRankInfo(new TiXmlElement("SRoleRankInfo"));
	if(pElem_SRoleRankInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const SRoleRankInfo&)s, *pElem_SRoleRankInfo))
	{
		LOG_CRI << "SRoleRankInfo ToXML fails!";
		return false;
	}
	pElem_SRoleRankInfo->SetAttribute("type", ToUTF8Ptr("玩家相关排名信息"));
	pElem_SRoleRankInfo->SetAttribute("comment", ToUTF8Ptr("父类SRoleRankInfo部分"));
	if(rElement.LinkEndChild(pElem_SRoleRankInfo.get()) != NULL)
		pElem_SRoleRankInfo.release();
	unique_ptr<TiXmlElement> pElem_dwBattlePoint(new TiXmlElement("UINT32"));
	if(pElem_dwBattlePoint == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwBattlePoint->SetAttribute("name", "dwBattlePoint");
	pElem_dwBattlePoint->SetAttribute("value", NumberToString(s.dwBattlePoint).c_str());
	pElem_dwBattlePoint->SetAttribute("comment", ToUTF8Ptr("战斗力"));
	if(rElement.LinkEndChild(pElem_dwBattlePoint.get()) != NULL)
		pElem_dwBattlePoint.release();
	unique_ptr<TiXmlElement> pElem_strGuildName(new TiXmlElement("string"));
	if(pElem_strGuildName == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strGuildName->SetAttribute("name", "strGuildName");
	pElem_strGuildName->SetAttribute("value", s.strGuildName.c_str());
	pElem_strGuildName->SetAttribute("comment", ToUTF8Ptr("帮派名称"));
	if(rElement.LinkEndChild(pElem_strGuildName.get()) != NULL)
		pElem_strGuildName.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecRRArenaInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SRRArenaInfoPtr p(new SRRArenaInfo);
		if(!FromXML(*pElemMember, *p))
		{
			LOG_CRI << "FromXML fails!";
			return false;
		}
		vec.push_back(p);
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecRRArenaInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SRRArenaInfo"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!ToXML(*vec[i], *pElemMember))
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

SGuildRankInfo::SGuildRankInfo() : qwGuildID(0), wLevel(0), qwRoleID(0), byQuality(0), wPlayerFighterID(0) { }

SGuildRankInfo::SGuildRankInfo(SGuildRankInfo&& src) : SRankInfo(src), qwGuildID(src.qwGuildID), strName(move(src.strName)), wLevel(src.wLevel), strGuildName(move(src.strGuildName)), qwRoleID(src.qwRoleID), 
			byQuality(src.byQuality), wPlayerFighterID(src.wPlayerFighterID) { }

SGuildRankInfo& SGuildRankInfo::operator=(SGuildRankInfo&& rhs)
{
	if(this != &rhs)
	{
		this->~SGuildRankInfo();
		new (this) SGuildRankInfo(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SGuildRankInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (SRankInfo&)s;
	src >> s.qwGuildID;
	src >> s.strName;
	src >> s.wLevel;
	src >> s.strGuildName;
	src >> s.qwRoleID;
	src >> s.byQuality;
	src >> s.wPlayerFighterID;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SGuildRankInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const SRankInfo&)s;
	src << s.qwGuildID;
	src << s.strName;
	src << s.wLevel;
	src << s.strGuildName;
	src << s.qwRoleID;
	src << s.byQuality;
	src << s.wPlayerFighterID;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, SGuildRankInfo_Wrapper& rWrapper)
{
	EType_SRankInfo eType = eType_SRankInfo;
	src >> (UINT8&)eType;
	switch(eType)
	{
	case eType_SGuildRankInfo:
		{
			rWrapper.ptr.reset(new SGuildRankInfo);
			src >> (SGuildRankInfo&)*rWrapper.ptr;
		}
		break;
	case eType_SGRBattleInfo:
		{
			rWrapper.ptr.reset(new SGRBattleInfo);
			src >> (SGRBattleInfo&)*rWrapper.ptr;
		}
		break;
	case eType_SGRLevelInfo:
		{
			rWrapper.ptr.reset(new SGRLevelInfo);
			src >> (SGRLevelInfo&)*rWrapper.ptr;
		}
		break;
	default:
		throw "Unknown value for EType_SRankInfo";
		break;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SGuildRankInfo_Wrapper& rWrapper)
{
	if(rWrapper.ptr != NULL)
	{
		src << (UINT8)rWrapper.ptr->GetClassType();
		switch(rWrapper.ptr->GetClassType())
		{
		case eType_SGuildRankInfo:
			src << (SGuildRankInfo&)*rWrapper.ptr;
			break;
		case eType_SGRBattleInfo:
			src << (SGRBattleInfo&)*rWrapper.ptr;
			break;
		case eType_SGRLevelInfo:
			src << (SGRLevelInfo&)*rWrapper.ptr;
			break;
		default:
			throw "Unknown value for EType_SRankInfo";
			break;
		}
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecGuildRankInfo& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SGuildRankInfo_Wrapper wrapper;
		src >> wrapper;
		vec[i] = wrapper.ptr;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecGuildRankInfo& vec)
{
	if(vec.size() > 0x7FFF)
		throw "Vector Size Too Large!";
	UINT16 wSize = (UINT16)vec.size();
	src.WriteContainerSize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SGuildRankInfo_Wrapper wrapper;
		wrapper.ptr = vec[i];
		src << wrapper;
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SGuildRankInfo& s)
{
	if(strcmp(rElement.Value(), "SGuildRankInfo") != 0)
	{
		LOG_CRI << "rElement is not SGuildRankInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for SRankInfo is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (SRankInfo&)s))
	{
		LOG_CRI << "FromXML for: SRankInfo fails!";
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
		LOG_CRI << "pElemChild for wLevel is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wLevel") != 0)
	{
		LOG_CRI << "Attribute: name is not wLevel!";
		return false;
	}
	const char* pszVal_wLevel = pElemChild->Attribute("value");
	if(pszVal_wLevel == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wLevel, s.wLevel))
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
		LOG_CRI << "pElemChild for byQuality is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byQuality") != 0)
	{
		LOG_CRI << "Attribute: name is not byQuality!";
		return false;
	}
	const char* pszVal_byQuality = pElemChild->Attribute("value");
	if(pszVal_byQuality == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byQuality, s.byQuality))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wPlayerFighterID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wPlayerFighterID") != 0)
	{
		LOG_CRI << "Attribute: name is not wPlayerFighterID!";
		return false;
	}
	const char* pszVal_wPlayerFighterID = pElemChild->Attribute("value");
	if(pszVal_wPlayerFighterID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wPlayerFighterID, s.wPlayerFighterID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SGuildRankInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SGuildRankInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("帮派相关排名信息"));
	unique_ptr<TiXmlElement> pElem_SRankInfo(new TiXmlElement("SRankInfo"));
	if(pElem_SRankInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const SRankInfo&)s, *pElem_SRankInfo))
	{
		LOG_CRI << "SRankInfo ToXML fails!";
		return false;
	}
	pElem_SRankInfo->SetAttribute("type", ToUTF8Ptr("排名信息"));
	pElem_SRankInfo->SetAttribute("comment", ToUTF8Ptr("父类SRankInfo部分"));
	if(rElement.LinkEndChild(pElem_SRankInfo.get()) != NULL)
		pElem_SRankInfo.release();
	unique_ptr<TiXmlElement> pElem_qwGuildID(new TiXmlElement("UINT64"));
	if(pElem_qwGuildID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwGuildID->SetAttribute("name", "qwGuildID");
	pElem_qwGuildID->SetAttribute("value", NumberToString(s.qwGuildID).c_str());
	pElem_qwGuildID->SetAttribute("comment", ToUTF8Ptr("帮派ID"));
	if(rElement.LinkEndChild(pElem_qwGuildID.get()) != NULL)
		pElem_qwGuildID.release();
	unique_ptr<TiXmlElement> pElem_strName(new TiXmlElement("string"));
	if(pElem_strName == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strName->SetAttribute("name", "strName");
	pElem_strName->SetAttribute("value", s.strName.c_str());
	pElem_strName->SetAttribute("comment", ToUTF8Ptr("帮主姓名"));
	if(rElement.LinkEndChild(pElem_strName.get()) != NULL)
		pElem_strName.release();
	unique_ptr<TiXmlElement> pElem_wLevel(new TiXmlElement("UINT16"));
	if(pElem_wLevel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wLevel->SetAttribute("name", "wLevel");
	pElem_wLevel->SetAttribute("value", NumberToString(s.wLevel).c_str());
	pElem_wLevel->SetAttribute("comment", ToUTF8Ptr("帮派等级"));
	if(rElement.LinkEndChild(pElem_wLevel.get()) != NULL)
		pElem_wLevel.release();
	unique_ptr<TiXmlElement> pElem_strGuildName(new TiXmlElement("string"));
	if(pElem_strGuildName == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strGuildName->SetAttribute("name", "strGuildName");
	pElem_strGuildName->SetAttribute("value", s.strGuildName.c_str());
	pElem_strGuildName->SetAttribute("comment", ToUTF8Ptr("帮派姓名"));
	if(rElement.LinkEndChild(pElem_strGuildName.get()) != NULL)
		pElem_strGuildName.release();
	unique_ptr<TiXmlElement> pElem_qwRoleID(new TiXmlElement("UINT64"));
	if(pElem_qwRoleID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwRoleID->SetAttribute("name", "qwRoleID");
	pElem_qwRoleID->SetAttribute("value", NumberToString(s.qwRoleID).c_str());
	pElem_qwRoleID->SetAttribute("comment", ToUTF8Ptr("帮主ID"));
	if(rElement.LinkEndChild(pElem_qwRoleID.get()) != NULL)
		pElem_qwRoleID.release();
	unique_ptr<TiXmlElement> pElem_byQuality(new TiXmlElement("UINT8"));
	if(pElem_byQuality == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byQuality->SetAttribute("name", "byQuality");
	pElem_byQuality->SetAttribute("value", NumberToString(s.byQuality).c_str());
	pElem_byQuality->SetAttribute("comment", ToUTF8Ptr("主将品质(颜色)"));
	if(rElement.LinkEndChild(pElem_byQuality.get()) != NULL)
		pElem_byQuality.release();
	unique_ptr<TiXmlElement> pElem_wPlayerFighterID(new TiXmlElement("UINT16"));
	if(pElem_wPlayerFighterID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wPlayerFighterID->SetAttribute("name", "wPlayerFighterID");
	pElem_wPlayerFighterID->SetAttribute("value", NumberToString(s.wPlayerFighterID).c_str());
	pElem_wPlayerFighterID->SetAttribute("comment", ToUTF8Ptr("主将ID"));
	if(rElement.LinkEndChild(pElem_wPlayerFighterID.get()) != NULL)
		pElem_wPlayerFighterID.release();
	return true;
}

bool SuperFromXML(TiXmlElement& rElement, SGuildRankInfoPtr& p)
{
	const char* pszName = rElement.Value();
	if(pszName == NULL)
	{
		LOG_CRI << "Element Name is empty!";
		return false;
	}
	if(strcmp(pszName, "SGuildRankInfo") == 0)
	{
		SGuildRankInfoPtr pStruct(new SGuildRankInfo);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SGuildRankInfo";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SGuildRankInfo FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SGRBattleInfo") == 0)
	{
		SGRBattleInfoPtr pStruct(new SGRBattleInfo);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SGRBattleInfo";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SGRBattleInfo FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SGRLevelInfo") == 0)
	{
		SGRLevelInfoPtr pStruct(new SGRLevelInfo);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SGRLevelInfo";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SGRLevelInfo FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else
	{
		LOG_CRI << "Invalid name: " << pszName << "!";
		return false;
	}
	return true;
}

bool SuperToXML(const SGuildRankInfo& s, TiXmlElement& rElement)
{
	switch(s.GetClassType())
	{
	case eType_SGuildRankInfo:
		return ToXML((SGuildRankInfo&)s, rElement);
	case eType_SGRBattleInfo:
		return ToXML((SGRBattleInfo&)s, rElement);
	case eType_SGRLevelInfo:
		return ToXML((SGRLevelInfo&)s, rElement);
	default:
		LOG_CRI << "Invalid type: " << s.GetClassType();
		return false;
	}
}

bool VectorFromXML(TiXmlElement& rElement, TVecGuildRankInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SGuildRankInfoPtr p;
		if(!SuperFromXML(*pElemMember, p))
		{
			LOG_CRI << "SuperFromXML fails!";
			return false;
		}
		vec.push_back(p);
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecGuildRankInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SGuildRankInfo"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!SuperToXML(*vec[i], *pElemMember))
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

SGRBattleInfo::SGRBattleInfo() : dwBattleScore(0) { }

CInArchive& operator>>(CInArchive& src, SGRBattleInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (SGuildRankInfo&)s;
	src >> s.dwBattleScore;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SGRBattleInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const SGuildRankInfo&)s;
	src << s.dwBattleScore;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecGRBattleInfo& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SGRBattleInfoPtr p(new SGRBattleInfo);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecGRBattleInfo& vec)
{
	if(vec.size() > 0x7FFF)
		throw "Vector Size Too Large!";
	UINT16 wSize = (UINT16)vec.size();
	src.WriteContainerSize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
		src << *vec[i];
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SGRBattleInfo& s)
{
	if(strcmp(rElement.Value(), "SGRBattleInfo") != 0)
	{
		LOG_CRI << "rElement is not SGRBattleInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for SGuildRankInfo is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (SGuildRankInfo&)s))
	{
		LOG_CRI << "FromXML for: SGuildRankInfo fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwBattleScore is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwBattleScore") != 0)
	{
		LOG_CRI << "Attribute: name is not dwBattleScore!";
		return false;
	}
	const char* pszVal_dwBattleScore = pElemChild->Attribute("value");
	if(pszVal_dwBattleScore == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwBattleScore, s.dwBattleScore))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SGRBattleInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SGRBattleInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("帮派战排名"));
	unique_ptr<TiXmlElement> pElem_SGuildRankInfo(new TiXmlElement("SGuildRankInfo"));
	if(pElem_SGuildRankInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const SGuildRankInfo&)s, *pElem_SGuildRankInfo))
	{
		LOG_CRI << "SGuildRankInfo ToXML fails!";
		return false;
	}
	pElem_SGuildRankInfo->SetAttribute("type", ToUTF8Ptr("帮派相关排名信息"));
	pElem_SGuildRankInfo->SetAttribute("comment", ToUTF8Ptr("父类SGuildRankInfo部分"));
	if(rElement.LinkEndChild(pElem_SGuildRankInfo.get()) != NULL)
		pElem_SGuildRankInfo.release();
	unique_ptr<TiXmlElement> pElem_dwBattleScore(new TiXmlElement("UINT32"));
	if(pElem_dwBattleScore == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwBattleScore->SetAttribute("name", "dwBattleScore");
	pElem_dwBattleScore->SetAttribute("value", NumberToString(s.dwBattleScore).c_str());
	pElem_dwBattleScore->SetAttribute("comment", ToUTF8Ptr("帮派战积分"));
	if(rElement.LinkEndChild(pElem_dwBattleScore.get()) != NULL)
		pElem_dwBattleScore.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecGRBattleInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SGRBattleInfoPtr p(new SGRBattleInfo);
		if(!FromXML(*pElemMember, *p))
		{
			LOG_CRI << "FromXML fails!";
			return false;
		}
		vec.push_back(p);
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecGRBattleInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SGRBattleInfo"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!ToXML(*vec[i], *pElemMember))
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

SGRLevelInfo::SGRLevelInfo() : wLevel2(0) { }

CInArchive& operator>>(CInArchive& src, SGRLevelInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (SGuildRankInfo&)s;
	src >> s.wLevel2;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SGRLevelInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const SGuildRankInfo&)s;
	src << s.wLevel2;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecGRLevelInfo& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SGRLevelInfoPtr p(new SGRLevelInfo);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecGRLevelInfo& vec)
{
	if(vec.size() > 0x7FFF)
		throw "Vector Size Too Large!";
	UINT16 wSize = (UINT16)vec.size();
	src.WriteContainerSize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
		src << *vec[i];
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SGRLevelInfo& s)
{
	if(strcmp(rElement.Value(), "SGRLevelInfo") != 0)
	{
		LOG_CRI << "rElement is not SGRLevelInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for SGuildRankInfo is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (SGuildRankInfo&)s))
	{
		LOG_CRI << "FromXML for: SGuildRankInfo fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wLevel2 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wLevel2") != 0)
	{
		LOG_CRI << "Attribute: name is not wLevel2!";
		return false;
	}
	const char* pszVal_wLevel2 = pElemChild->Attribute("value");
	if(pszVal_wLevel2 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wLevel2, s.wLevel2))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SGRLevelInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SGRLevelInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("帮派等级排名"));
	unique_ptr<TiXmlElement> pElem_SGuildRankInfo(new TiXmlElement("SGuildRankInfo"));
	if(pElem_SGuildRankInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const SGuildRankInfo&)s, *pElem_SGuildRankInfo))
	{
		LOG_CRI << "SGuildRankInfo ToXML fails!";
		return false;
	}
	pElem_SGuildRankInfo->SetAttribute("type", ToUTF8Ptr("帮派相关排名信息"));
	pElem_SGuildRankInfo->SetAttribute("comment", ToUTF8Ptr("父类SGuildRankInfo部分"));
	if(rElement.LinkEndChild(pElem_SGuildRankInfo.get()) != NULL)
		pElem_SGuildRankInfo.release();
	unique_ptr<TiXmlElement> pElem_wLevel2(new TiXmlElement("UINT16"));
	if(pElem_wLevel2 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wLevel2->SetAttribute("name", "wLevel2");
	pElem_wLevel2->SetAttribute("value", NumberToString(s.wLevel2).c_str());
	pElem_wLevel2->SetAttribute("comment", ToUTF8Ptr("帮派等级"));
	if(rElement.LinkEndChild(pElem_wLevel2.get()) != NULL)
		pElem_wLevel2.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecGRLevelInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SGRLevelInfoPtr p(new SGRLevelInfo);
		if(!FromXML(*pElemMember, *p))
		{
			LOG_CRI << "FromXML fails!";
			return false;
		}
		vec.push_back(p);
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecGRLevelInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SGRLevelInfo"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!ToXML(*vec[i], *pElemMember))
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

SDBAdoreInfo::SDBAdoreInfo() : qwRoleID(0), dwCount(0), dwUpdateTime(0) { }

SDBAdoreInfo::SDBAdoreInfo(UINT64 qwRoleID_, UINT32 dwCount_, UINT32 dwUpdateTime_) : qwRoleID(qwRoleID_), dwCount(dwCount_), dwUpdateTime(dwUpdateTime_) { }

CInArchive& operator>>(CInArchive& src, SDBAdoreInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwRoleID;
	src >> s.dwCount;
	src >> s.dwUpdateTime;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SDBAdoreInfo& s)
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
	src << s.dwCount;
	src << s.dwUpdateTime;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SDBAdoreInfo& s)
{
	if(strcmp(rElement.Value(), "SDBAdoreInfo") != 0)
	{
		LOG_CRI << "rElement is not SDBAdoreInfo!";
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
		LOG_CRI << "pElemChild for dwUpdateTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwUpdateTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwUpdateTime!";
		return false;
	}
	const char* pszVal_dwUpdateTime = pElemChild->Attribute("value");
	if(pszVal_dwUpdateTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwUpdateTime, s.dwUpdateTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SDBAdoreInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SDBAdoreInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("崇拜数据库信息"));
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
	unique_ptr<TiXmlElement> pElem_dwCount(new TiXmlElement("UINT32"));
	if(pElem_dwCount == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwCount->SetAttribute("name", "dwCount");
	pElem_dwCount->SetAttribute("value", NumberToString(s.dwCount).c_str());
	pElem_dwCount->SetAttribute("comment", ToUTF8Ptr("被崇拜数量"));
	if(rElement.LinkEndChild(pElem_dwCount.get()) != NULL)
		pElem_dwCount.release();
	unique_ptr<TiXmlElement> pElem_dwUpdateTime(new TiXmlElement("UINT32"));
	if(pElem_dwUpdateTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwUpdateTime->SetAttribute("name", "dwUpdateTime");
	pElem_dwUpdateTime->SetAttribute("value", NumberToString(s.dwUpdateTime).c_str());
	pElem_dwUpdateTime->SetAttribute("comment", ToUTF8Ptr("更新时间"));
	if(rElement.LinkEndChild(pElem_dwUpdateTime.get()) != NULL)
		pElem_dwUpdateTime.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecDBAdoreInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SDBAdoreInfo s;
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

bool VectorToXML(const TVecDBAdoreInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SDBAdoreInfo"));
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

} //namespace NRankProt
