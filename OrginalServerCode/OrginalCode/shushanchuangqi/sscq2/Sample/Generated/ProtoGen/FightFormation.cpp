/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    FightFormation.cpp
//  Purpose:      新阵型相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "FightFormation.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NFightFormation
{

#ifdef PROT_USE_XML

const char* EnumValToStr(EFightFormationResult e)
{
	switch(e)
	{
	case eFightFormationResult_Succes:
		return "eFightFormationResult_Succes";
	case eFightFormationResult_Fail:
		return "eFightFormationResult_Fail";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EFightFormationResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EFightFormationResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eFightFormationResult_Succes", eFightFormationResult_Succes));
		mapStr2Val.insert(make_pair("eFightFormationResult_Fail", eFightFormationResult_Fail));
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

SBattlePosInfo::SBattlePosInfo() : qwInstID(0), byPos(0) { }

SBattlePosInfo::SBattlePosInfo(UINT64 qwInstID_, INT8 byPos_) : qwInstID(qwInstID_), byPos(byPos_) { }

CInArchive& operator>>(CInArchive& src, SBattlePosInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwInstID;
	src >> s.byPos;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SBattlePosInfo& s)
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
	src << s.byPos;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SBattlePosInfo& s)
{
	if(strcmp(rElement.Value(), "SBattlePosInfo") != 0)
	{
		LOG_CRI << "rElement is not SBattlePosInfo!";
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
		LOG_CRI << "pElemChild for byPos is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "INT8") != 0)
	{
		LOG_CRI << "pElemChild is not INT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byPos") != 0)
	{
		LOG_CRI << "Attribute: name is not byPos!";
		return false;
	}
	const char* pszVal_byPos = pElemChild->Attribute("value");
	if(pszVal_byPos == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byPos, s.byPos))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SBattlePosInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SBattlePosInfo");
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
	unique_ptr<TiXmlElement> pElem_byPos(new TiXmlElement("INT8"));
	if(pElem_byPos == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byPos->SetAttribute("name", "byPos");
	pElem_byPos->SetAttribute("value", NumberToString(s.byPos).c_str());
	pElem_byPos->SetAttribute("comment", ToUTF8Ptr("位置"));
	if(rElement.LinkEndChild(pElem_byPos.get()) != NULL)
		pElem_byPos.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecBattlePosInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SBattlePosInfo s;
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

bool VectorToXML(const TVecBattlePosInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SBattlePosInfo"));
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

FightFormationInfo::FightFormationInfo() : wFormationID(0) { }

FightFormationInfo::FightFormationInfo(UINT16 wFormationID_, const TVecBattlePosInfo& vecBattlePosInfo_) : wFormationID(wFormationID_), vecBattlePosInfo(vecBattlePosInfo_) { }

FightFormationInfo::FightFormationInfo(FightFormationInfo&& src) : wFormationID(src.wFormationID), vecBattlePosInfo(move(src.vecBattlePosInfo)) { }

FightFormationInfo& FightFormationInfo::operator=(FightFormationInfo&& rhs)
{
	if(this != &rhs)
	{
		this->~FightFormationInfo();
		new (this) FightFormationInfo(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, FightFormationInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.wFormationID;
	src >> s.vecBattlePosInfo;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const FightFormationInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.wFormationID;
	src << s.vecBattlePosInfo;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, FightFormationInfo& s)
{
	if(strcmp(rElement.Value(), "FightFormationInfo") != 0)
	{
		LOG_CRI << "rElement is not FightFormationInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wFormationID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wFormationID") != 0)
	{
		LOG_CRI << "Attribute: name is not wFormationID!";
		return false;
	}
	const char* pszVal_wFormationID = pElemChild->Attribute("value");
	if(pszVal_wFormationID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wFormationID, s.wFormationID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecBattlePosInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecBattlePosInfo") != 0)
	{
		LOG_CRI << "pElemChild is not TVecBattlePosInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecBattlePosInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not vecBattlePosInfo!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecBattlePosInfo))
	{
		LOG_CRI << "VectorFromXML for vecBattlePosInfo fails!";
		return false;
	}
	return true;
}

bool ToXML(const FightFormationInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("FightFormationInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("战斗阵型信息"));
	unique_ptr<TiXmlElement> pElem_wFormationID(new TiXmlElement("UINT16"));
	if(pElem_wFormationID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wFormationID->SetAttribute("name", "wFormationID");
	pElem_wFormationID->SetAttribute("value", NumberToString(s.wFormationID).c_str());
	pElem_wFormationID->SetAttribute("comment", ToUTF8Ptr("当前阵形ID"));
	if(rElement.LinkEndChild(pElem_wFormationID.get()) != NULL)
		pElem_wFormationID.release();
	unique_ptr<TiXmlElement> pElem_vecBattlePosInfo(new TiXmlElement("TVecBattlePosInfo"));
	if(pElem_vecBattlePosInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecBattlePosInfo->SetAttribute("name", "vecBattlePosInfo");
	if(!VectorToXML(s.vecBattlePosInfo, *pElem_vecBattlePosInfo))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecBattlePosInfo->SetAttribute("comment", ToUTF8Ptr("位置"));
	if(rElement.LinkEndChild(pElem_vecBattlePosInfo.get()) != NULL)
		pElem_vecBattlePosInfo.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecFightFormationInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		FightFormationInfo s;
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

bool VectorToXML(const TVecFightFormationInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("FightFormationInfo"));
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

FightHeroInfo::FightHeroInfo() : qwInstID(0), dwHP(0), dwMaxHP(0), dwAura(0), dwMaxAura(0) { }

FightHeroInfo::FightHeroInfo(UINT64 qwInstID_, UINT32 dwHP_, UINT32 dwMaxHP_, UINT32 dwAura_, UINT32 dwMaxAura_)
			: qwInstID(qwInstID_), dwHP(dwHP_), dwMaxHP(dwMaxHP_), dwAura(dwAura_), dwMaxAura(dwMaxAura_) { }

CInArchive& operator>>(CInArchive& src, FightHeroInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwInstID;
	src >> s.dwHP;
	src >> s.dwMaxHP;
	src >> s.dwAura;
	src >> s.dwMaxAura;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const FightHeroInfo& s)
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
	src << s.dwHP;
	src << s.dwMaxHP;
	src << s.dwAura;
	src << s.dwMaxAura;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, FightHeroInfo& s)
{
	if(strcmp(rElement.Value(), "FightHeroInfo") != 0)
	{
		LOG_CRI << "rElement is not FightHeroInfo!";
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
		LOG_CRI << "pElemChild for dwMaxHP is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwMaxHP") != 0)
	{
		LOG_CRI << "Attribute: name is not dwMaxHP!";
		return false;
	}
	const char* pszVal_dwMaxHP = pElemChild->Attribute("value");
	if(pszVal_dwMaxHP == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwMaxHP, s.dwMaxHP))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwAura is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwAura") != 0)
	{
		LOG_CRI << "Attribute: name is not dwAura!";
		return false;
	}
	const char* pszVal_dwAura = pElemChild->Attribute("value");
	if(pszVal_dwAura == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwAura, s.dwAura))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwMaxAura is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwMaxAura") != 0)
	{
		LOG_CRI << "Attribute: name is not dwMaxAura!";
		return false;
	}
	const char* pszVal_dwMaxAura = pElemChild->Attribute("value");
	if(pszVal_dwMaxAura == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwMaxAura, s.dwMaxAura))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const FightHeroInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("FightHeroInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("战斗散仙信息"));
	unique_ptr<TiXmlElement> pElem_qwInstID(new TiXmlElement("UINT64"));
	if(pElem_qwInstID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwInstID->SetAttribute("name", "qwInstID");
	pElem_qwInstID->SetAttribute("value", NumberToString(s.qwInstID).c_str());
	pElem_qwInstID->SetAttribute("comment", ToUTF8Ptr("散仙InstID"));
	if(rElement.LinkEndChild(pElem_qwInstID.get()) != NULL)
		pElem_qwInstID.release();
	unique_ptr<TiXmlElement> pElem_dwHP(new TiXmlElement("UINT32"));
	if(pElem_dwHP == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwHP->SetAttribute("name", "dwHP");
	pElem_dwHP->SetAttribute("value", NumberToString(s.dwHP).c_str());
	pElem_dwHP->SetAttribute("comment", ToUTF8Ptr("当前生命值"));
	if(rElement.LinkEndChild(pElem_dwHP.get()) != NULL)
		pElem_dwHP.release();
	unique_ptr<TiXmlElement> pElem_dwMaxHP(new TiXmlElement("UINT32"));
	if(pElem_dwMaxHP == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwMaxHP->SetAttribute("name", "dwMaxHP");
	pElem_dwMaxHP->SetAttribute("value", NumberToString(s.dwMaxHP).c_str());
	pElem_dwMaxHP->SetAttribute("comment", ToUTF8Ptr("最大生命值（可能用到）"));
	if(rElement.LinkEndChild(pElem_dwMaxHP.get()) != NULL)
		pElem_dwMaxHP.release();
	unique_ptr<TiXmlElement> pElem_dwAura(new TiXmlElement("UINT32"));
	if(pElem_dwAura == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwAura->SetAttribute("name", "dwAura");
	pElem_dwAura->SetAttribute("value", NumberToString(s.dwAura).c_str());
	pElem_dwAura->SetAttribute("comment", ToUTF8Ptr("灵气值"));
	if(rElement.LinkEndChild(pElem_dwAura.get()) != NULL)
		pElem_dwAura.release();
	unique_ptr<TiXmlElement> pElem_dwMaxAura(new TiXmlElement("UINT32"));
	if(pElem_dwMaxAura == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwMaxAura->SetAttribute("name", "dwMaxAura");
	pElem_dwMaxAura->SetAttribute("value", NumberToString(s.dwMaxAura).c_str());
	pElem_dwMaxAura->SetAttribute("comment", ToUTF8Ptr("最大灵气值"));
	if(rElement.LinkEndChild(pElem_dwMaxAura.get()) != NULL)
		pElem_dwMaxAura.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecFightHeroInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		FightHeroInfo s;
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

bool VectorToXML(const TVecFightHeroInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("FightHeroInfo"));
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

} //namespace NFightFormation
