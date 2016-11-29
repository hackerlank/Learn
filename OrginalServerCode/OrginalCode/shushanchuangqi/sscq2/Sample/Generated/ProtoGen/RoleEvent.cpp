/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    RoleEvent.cpp
//  Purpose:      玩家在GameServer的消息处理
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "RoleEvent.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NRoleEvent
{

#ifdef PROT_USE_XML

const char* EnumValToStr(ECritType e)
{
	switch(e)
	{
	case ePetCrit:
		return "ePetCrit";
	case eHorseCrit:
		return "eHorseCrit";
	case eFashionCrit:
		return "eFashionCrit";
	case eTrumpCrit:
		return "eTrumpCrit";
	case eDujieCrit:
		return "eDujieCrit";
	case eMoneyTreeCrit:
		return "eMoneyTreeCrit";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, ECritType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, ECritType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("ePetCrit", ePetCrit));
		mapStr2Val.insert(make_pair("eHorseCrit", eHorseCrit));
		mapStr2Val.insert(make_pair("eFashionCrit", eFashionCrit));
		mapStr2Val.insert(make_pair("eTrumpCrit", eTrumpCrit));
		mapStr2Val.insert(make_pair("eDujieCrit", eDujieCrit));
		mapStr2Val.insert(make_pair("eMoneyTreeCrit", eMoneyTreeCrit));
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

const char* EnumValToStr(ECritMultiple e)
{
	switch(e)
	{
	case eTwoMultipleCrit:
		return "eTwoMultipleCrit";
	case eFiveMultipleCrit:
		return "eFiveMultipleCrit";
	case eTenMultipleCrit:
		return "eTenMultipleCrit";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, ECritMultiple& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, ECritMultiple> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eTwoMultipleCrit", eTwoMultipleCrit));
		mapStr2Val.insert(make_pair("eFiveMultipleCrit", eFiveMultipleCrit));
		mapStr2Val.insert(make_pair("eTenMultipleCrit", eTenMultipleCrit));
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

SFighterSpecInfo::SFighterSpecInfo() { }

SFighterSpecInfo::SFighterSpecInfo(SFighterSpecInfo&& src) : oEquips(move(src.oEquips)), oFighterInfo(move(src.oFighterInfo)) { }

SFighterSpecInfo& SFighterSpecInfo::operator=(SFighterSpecInfo&& rhs)
{
	if(this != &rhs)
	{
		this->~SFighterSpecInfo();
		new (this) SFighterSpecInfo(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SFighterSpecInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.oEquips;
	src >> s.oFighterInfo;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SFighterSpecInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.oEquips;
	src << s.oFighterInfo;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SFighterSpecInfo& s)
{
	if(strcmp(rElement.Value(), "SFighterSpecInfo") != 0)
	{
		LOG_CRI << "rElement is not SFighterSpecInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for oEquips is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "ItemProt::TVecItem") != 0)
	{
		LOG_CRI << "pElemChild is not ItemProt::TVecItem!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "oEquips") != 0)
	{
		LOG_CRI << "Attribute: name is not oEquips!";
		return false;
	}
	if(!NItemProt::VectorFromXML(*pElemChild, s.oEquips))
	{
		LOG_CRI << "VectorFromXML for oEquips fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for oFighterInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "FighterProt::SFighterInfo") != 0)
	{
		LOG_CRI << "pElemChild is not FighterProt::SFighterInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "oFighterInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not oFighterInfo!";
		return false;
	}
	if(!FromXML(*pElemChild, s.oFighterInfo))
	{
		LOG_CRI << "FromXML for: oFighterInfo fails!";
		return false;
	}
	return true;
}

bool ToXML(const SFighterSpecInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SFighterSpecInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("面板散仙信息"));
	unique_ptr<TiXmlElement> pElem_oEquips(new TiXmlElement("ItemProt::TVecItem"));
	if(pElem_oEquips == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_oEquips->SetAttribute("name", "oEquips");
	if(!NItemProt::VectorToXML(s.oEquips, *pElem_oEquips))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_oEquips->SetAttribute("comment", ToUTF8Ptr("散仙所有装备信息"));
	if(rElement.LinkEndChild(pElem_oEquips.get()) != NULL)
		pElem_oEquips.release();
	unique_ptr<TiXmlElement> pElem_oFighterInfo(new TiXmlElement("FighterProt::SFighterInfo"));
	if(pElem_oFighterInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_oFighterInfo->SetAttribute("name", "oFighterInfo");
	if(!ToXML(s.oFighterInfo, *pElem_oFighterInfo))
	{
		LOG_CRI << "oFighterInfo ToXML fails!";
		return false;
	}
	pElem_oFighterInfo->SetAttribute("comment", ToUTF8Ptr("散仙基本信息"));
	if(rElement.LinkEndChild(pElem_oFighterInfo.get()) != NULL)
		pElem_oFighterInfo.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecFighterSpecInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SFighterSpecInfo s;
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

bool VectorToXML(const TVecFighterSpecInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SFighterSpecInfo"));
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

SRoleFighterStream::SRoleFighterStream() { }

SRoleFighterStream::SRoleFighterStream(const SFighterSpecInfo& oMainFighter_, const TVecFighterSpecInfo& oFighters_) : oMainFighter(oMainFighter_), oFighters(oFighters_) { }

SRoleFighterStream::SRoleFighterStream(SRoleFighterStream&& src) : oMainFighter(move(src.oMainFighter)), oFighters(move(src.oFighters)) { }

SRoleFighterStream& SRoleFighterStream::operator=(SRoleFighterStream&& rhs)
{
	if(this != &rhs)
	{
		this->~SRoleFighterStream();
		new (this) SRoleFighterStream(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SRoleFighterStream& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.oMainFighter;
	src >> s.oFighters;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SRoleFighterStream& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.oMainFighter;
	src << s.oFighters;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SRoleFighterStream& s)
{
	if(strcmp(rElement.Value(), "SRoleFighterStream") != 0)
	{
		LOG_CRI << "rElement is not SRoleFighterStream!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for oMainFighter is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "SFighterSpecInfo") != 0)
	{
		LOG_CRI << "pElemChild is not SFighterSpecInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "oMainFighter") != 0)
	{
		LOG_CRI << "Attribute: name is not oMainFighter!";
		return false;
	}
	if(!FromXML(*pElemChild, s.oMainFighter))
	{
		LOG_CRI << "FromXML for: oMainFighter fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for oFighters is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecFighterSpecInfo") != 0)
	{
		LOG_CRI << "pElemChild is not TVecFighterSpecInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "oFighters") != 0)
	{
		LOG_CRI << "Attribute: name is not oFighters!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.oFighters))
	{
		LOG_CRI << "VectorFromXML for oFighters fails!";
		return false;
	}
	return true;
}

bool ToXML(const SRoleFighterStream& s, TiXmlElement& rElement)
{
	rElement.SetValue("SRoleFighterStream");
	rElement.SetAttribute("type", ToUTF8Ptr("散仙信息"));
	unique_ptr<TiXmlElement> pElem_oMainFighter(new TiXmlElement("SFighterSpecInfo"));
	if(pElem_oMainFighter == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_oMainFighter->SetAttribute("name", "oMainFighter");
	if(!ToXML(s.oMainFighter, *pElem_oMainFighter))
	{
		LOG_CRI << "oMainFighter ToXML fails!";
		return false;
	}
	pElem_oMainFighter->SetAttribute("comment", ToUTF8Ptr("主散仙的信息"));
	if(rElement.LinkEndChild(pElem_oMainFighter.get()) != NULL)
		pElem_oMainFighter.release();
	unique_ptr<TiXmlElement> pElem_oFighters(new TiXmlElement("TVecFighterSpecInfo"));
	if(pElem_oFighters == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_oFighters->SetAttribute("name", "oFighters");
	if(!VectorToXML(s.oFighters, *pElem_oFighters))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_oFighters->SetAttribute("comment", ToUTF8Ptr("所有散仙的信息"));
	if(rElement.LinkEndChild(pElem_oFighters.get()) != NULL)
		pElem_oFighters.release();
	return true;
}

#endif

SRoleStream::SRoleStream() { }

SRoleStream::SRoleStream(const SFighterSpecInfo& oMainFighter_) : oMainFighter(oMainFighter_) { }

SRoleStream::SRoleStream(SRoleStream&& src) : oMainFighter(move(src.oMainFighter)) { }

SRoleStream& SRoleStream::operator=(SRoleStream&& rhs)
{
	if(this != &rhs)
	{
		this->~SRoleStream();
		new (this) SRoleStream(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SRoleStream& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.oMainFighter;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SRoleStream& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.oMainFighter;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SRoleStream& s)
{
	if(strcmp(rElement.Value(), "SRoleStream") != 0)
	{
		LOG_CRI << "rElement is not SRoleStream!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for oMainFighter is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "SFighterSpecInfo") != 0)
	{
		LOG_CRI << "pElemChild is not SFighterSpecInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "oMainFighter") != 0)
	{
		LOG_CRI << "Attribute: name is not oMainFighter!";
		return false;
	}
	if(!FromXML(*pElemChild, s.oMainFighter))
	{
		LOG_CRI << "FromXML for: oMainFighter fails!";
		return false;
	}
	return true;
}

bool ToXML(const SRoleStream& s, TiXmlElement& rElement)
{
	rElement.SetValue("SRoleStream");
	rElement.SetAttribute("type", ToUTF8Ptr("面板散仙信息"));
	unique_ptr<TiXmlElement> pElem_oMainFighter(new TiXmlElement("SFighterSpecInfo"));
	if(pElem_oMainFighter == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_oMainFighter->SetAttribute("name", "oMainFighter");
	if(!ToXML(s.oMainFighter, *pElem_oMainFighter))
	{
		LOG_CRI << "oMainFighter ToXML fails!";
		return false;
	}
	pElem_oMainFighter->SetAttribute("comment", ToUTF8Ptr("主散仙的信息"));
	if(rElement.LinkEndChild(pElem_oMainFighter.get()) != NULL)
		pElem_oMainFighter.release();
	return true;
}

#endif

} //namespace NRoleEvent
