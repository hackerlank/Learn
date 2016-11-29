/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    Formation.cpp
//  Purpose:      阵灵相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "FormationProt.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NFormationProt
{

#ifdef PROT_USE_XML

const char* EnumValToStr(EFormationAttr e)
{
	switch(e)
	{
	case eFormAttrNone:
		return "eFormAttrNone";
	case eFormAttrSpeed:
		return "eFormAttrSpeed";
	case eFormAttrHit:
		return "eFormAttrHit";
	case eFormAttrEva:
		return "eFormAttrEva";
	case eFormAttrCrit:
		return "eFormAttrCrit";
	case eFormAttrAntiCrit:
		return "eFormAttrAntiCrit";
	case eFormAttrCount:
		return "eFormAttrCount";
	case eFormAttrAntiCount:
		return "eFormAttrAntiCount";
	case eFormAttrAp:
		return "eFormAttrAp";
	case eFormAttrMax:
		return "eFormAttrMax";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EFormationAttr& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EFormationAttr> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eFormAttrNone", eFormAttrNone));
		mapStr2Val.insert(make_pair("eFormAttrSpeed", eFormAttrSpeed));
		mapStr2Val.insert(make_pair("eFormAttrHit", eFormAttrHit));
		mapStr2Val.insert(make_pair("eFormAttrEva", eFormAttrEva));
		mapStr2Val.insert(make_pair("eFormAttrCrit", eFormAttrCrit));
		mapStr2Val.insert(make_pair("eFormAttrAntiCrit", eFormAttrAntiCrit));
		mapStr2Val.insert(make_pair("eFormAttrCount", eFormAttrCount));
		mapStr2Val.insert(make_pair("eFormAttrAntiCount", eFormAttrAntiCount));
		mapStr2Val.insert(make_pair("eFormAttrAp", eFormAttrAp));
		mapStr2Val.insert(make_pair("eFormAttrMax", eFormAttrMax));
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

const char* EnumValToStr(EFormPetType e)
{
	switch(e)
	{
	case eFormPetSucc:
		return "eFormPetSucc";
	case eFormPetFalied:
		return "eFormPetFalied";
	case eFormPetMainFighterErr:
		return "eFormPetMainFighterErr";
	case eFormPetItemErr:
		return "eFormPetItemErr";
	case eFormPetPetLevelItemErr:
		return "eFormPetPetLevelItemErr";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EFormPetType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EFormPetType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eFormPetSucc", eFormPetSucc));
		mapStr2Val.insert(make_pair("eFormPetFalied", eFormPetFalied));
		mapStr2Val.insert(make_pair("eFormPetMainFighterErr", eFormPetMainFighterErr));
		mapStr2Val.insert(make_pair("eFormPetItemErr", eFormPetItemErr));
		mapStr2Val.insert(make_pair("eFormPetPetLevelItemErr", eFormPetPetLevelItemErr));
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

const char* EnumValToStr(EBeastSoulResult e)
{
	switch(e)
	{
	case eBeastSoulSucces:
		return "eBeastSoulSucces";
	case eBeastSoulFailed:
		return "eBeastSoulFailed";
	case eBeastSoulLackOfMoney:
		return "eBeastSoulLackOfMoney";
	case eBeastSoulRankMax:
		return "eBeastSoulRankMax";
	case eBeastSoulLevelLimit:
		return "eBeastSoulLevelLimit";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EBeastSoulResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EBeastSoulResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eBeastSoulSucces", eBeastSoulSucces));
		mapStr2Val.insert(make_pair("eBeastSoulFailed", eBeastSoulFailed));
		mapStr2Val.insert(make_pair("eBeastSoulLackOfMoney", eBeastSoulLackOfMoney));
		mapStr2Val.insert(make_pair("eBeastSoulRankMax", eBeastSoulRankMax));
		mapStr2Val.insert(make_pair("eBeastSoulLevelLimit", eBeastSoulLevelLimit));
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

SLineup::SLineup() : qwInstID(0), iPos(0) { }

SLineup::SLineup(UINT64 qwInstID_, INT32 iPos_) : qwInstID(qwInstID_), iPos(iPos_) { }

CInArchive& operator>>(CInArchive& src, SLineup& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwInstID;
	src >> s.iPos;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SLineup& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.qwInstID;
	src << s.iPos;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SLineup& s)
{
	if(strcmp(rElement.Value(), "SLineup") != 0)
	{
		LOG_CRI << "rElement is not SLineup!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwInstID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwInstID") != 0)
	{
		LOG_CRI << "Attribute: name is not qwInstID!";
		return false;
	}
	const char* pszVal_qwInstID = pElemChild->Attribute("value");
	if(pszVal_qwInstID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwInstID, s.qwInstID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for iPos is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "INT32") != 0)
	{
		LOG_CRI << "pElemChild is not INT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "iPos") != 0)
	{
		LOG_CRI << "Attribute: name is not iPos!";
		return false;
	}
	const char* pszVal_iPos = pElemChild->Attribute("value");
	if(pszVal_iPos == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_iPos, s.iPos))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SLineup& s, TiXmlElement& rElement)
{
	rElement.SetValue("SLineup");
	rElement.SetAttribute("type", ToUTF8Ptr("阵型信息"));
	unique_ptr<TiXmlElement> pElem_qwInstID(new TiXmlElement("UINT64"));
	if(pElem_qwInstID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwInstID->SetAttribute("name", "qwInstID");
	pElem_qwInstID->SetAttribute("value", NumberToString(s.qwInstID).c_str());
	pElem_qwInstID->SetAttribute("comment", ToUTF8Ptr("散仙唯一ID"));
	if(rElement.LinkEndChild(pElem_qwInstID.get()) != NULL)
		pElem_qwInstID.release();
	unique_ptr<TiXmlElement> pElem_iPos(new TiXmlElement("INT32"));
	if(pElem_iPos == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_iPos->SetAttribute("name", "iPos");
	pElem_iPos->SetAttribute("value", NumberToString(s.iPos).c_str());
	pElem_iPos->SetAttribute("comment", ToUTF8Ptr("位置"));
	if(rElement.LinkEndChild(pElem_iPos.get()) != NULL)
		pElem_iPos.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecSLineup& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SLineup s;
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

bool VectorToXML(const TVecSLineup& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SLineup"));
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

SBeastSoulItem::SBeastSoulItem() : wItemID(0), dwCount(0) { }

SBeastSoulItem::SBeastSoulItem(UINT16 wItemID_, UINT32 dwCount_) : wItemID(wItemID_), dwCount(dwCount_) { }

CInArchive& operator>>(CInArchive& src, SBeastSoulItem& s)
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

COutArchive& operator<<(COutArchive& src, const SBeastSoulItem& s)
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

bool FromXML(TiXmlElement& rElement, SBeastSoulItem& s)
{
	if(strcmp(rElement.Value(), "SBeastSoulItem") != 0)
	{
		LOG_CRI << "rElement is not SBeastSoulItem!";
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

bool ToXML(const SBeastSoulItem& s, TiXmlElement& rElement)
{
	rElement.SetValue("SBeastSoulItem");
	rElement.SetAttribute("type", ToUTF8Ptr("兽魂奖励道具信息"));
	unique_ptr<TiXmlElement> pElem_wItemID(new TiXmlElement("UINT16"));
	if(pElem_wItemID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wItemID->SetAttribute("name", "wItemID");
	pElem_wItemID->SetAttribute("value", NumberToString(s.wItemID).c_str());
	pElem_wItemID->SetAttribute("comment", ToUTF8Ptr("模板ID"));
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
	pElem_dwCount->SetAttribute("comment", ToUTF8Ptr("数量"));
	if(rElement.LinkEndChild(pElem_dwCount.get()) != NULL)
		pElem_dwCount.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecBeastSoulItem& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SBeastSoulItem s;
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

bool VectorToXML(const TVecBeastSoulItem& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SBeastSoulItem"));
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

} //namespace NFormationProt
