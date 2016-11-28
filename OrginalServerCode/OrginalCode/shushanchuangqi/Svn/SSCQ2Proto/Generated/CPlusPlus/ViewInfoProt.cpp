/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    ViewInfoProt.cpp
//  Purpose:      查看信息协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "ViewInfoProt.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NViewInfoProt
{

SBattleFighterData::SBattleFighterData() : qwInstID(0), wFighterID(0), byFighterLevel(0), byTemplateID(0), byLevel(0) { }

SBattleFighterData::SBattleFighterData(UINT64 qwInstID_, UINT16 wFighterID_, UINT8 byFighterLevel_, UINT8 byTemplateID_, UINT8 byLevel_)
			: qwInstID(qwInstID_), wFighterID(wFighterID_), byFighterLevel(byFighterLevel_), byTemplateID(byTemplateID_), byLevel(byLevel_) { }

CInArchive& operator>>(CInArchive& src, SBattleFighterData& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwInstID;
	src >> s.wFighterID;
	src >> s.byFighterLevel;
	src >> s.byTemplateID;
	src >> s.byLevel;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SBattleFighterData& s)
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
	src << s.wFighterID;
	src << s.byFighterLevel;
	src << s.byTemplateID;
	src << s.byLevel;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SBattleFighterData& s)
{
	if(strcmp(rElement.Value(), "SBattleFighterData") != 0)
	{
		LOG_CRI << "rElement is not SBattleFighterData!";
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
		LOG_CRI << "pElemChild for wFighterID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wFighterID") != 0)
	{
		LOG_CRI << "Attribute: name is not wFighterID!";
		return false;
	}
	const char* pszVal_wFighterID = pElemChild->Attribute("value");
	if(pszVal_wFighterID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wFighterID, s.wFighterID))
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
		LOG_CRI << "pElemChild for byTemplateID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byTemplateID") != 0)
	{
		LOG_CRI << "Attribute: name is not byTemplateID!";
		return false;
	}
	const char* pszVal_byTemplateID = pElemChild->Attribute("value");
	if(pszVal_byTemplateID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byTemplateID, s.byTemplateID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
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
	return true;
}

bool ToXML(const SBattleFighterData& s, TiXmlElement& rElement)
{
	rElement.SetValue("SBattleFighterData");
	rElement.SetAttribute("type", ToUTF8Ptr("出战散仙信息"));
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
	unique_ptr<TiXmlElement> pElem_wFighterID(new TiXmlElement("UINT16"));
	if(pElem_wFighterID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wFighterID->SetAttribute("name", "wFighterID");
	pElem_wFighterID->SetAttribute("value", NumberToString(s.wFighterID).c_str());
	pElem_wFighterID->SetAttribute("comment", ToUTF8Ptr("散仙模版"));
	if(rElement.LinkEndChild(pElem_wFighterID.get()) != NULL)
		pElem_wFighterID.release();
	unique_ptr<TiXmlElement> pElem_byFighterLevel(new TiXmlElement("UINT8"));
	if(pElem_byFighterLevel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byFighterLevel->SetAttribute("name", "byFighterLevel");
	pElem_byFighterLevel->SetAttribute("value", NumberToString(s.byFighterLevel).c_str());
	pElem_byFighterLevel->SetAttribute("comment", ToUTF8Ptr("散仙等级"));
	if(rElement.LinkEndChild(pElem_byFighterLevel.get()) != NULL)
		pElem_byFighterLevel.release();
	unique_ptr<TiXmlElement> pElem_byTemplateID(new TiXmlElement("UINT8"));
	if(pElem_byTemplateID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byTemplateID->SetAttribute("name", "byTemplateID");
	pElem_byTemplateID->SetAttribute("value", NumberToString(s.byTemplateID).c_str());
	pElem_byTemplateID->SetAttribute("comment", ToUTF8Ptr("渡劫模版Id"));
	if(rElement.LinkEndChild(pElem_byTemplateID.get()) != NULL)
		pElem_byTemplateID.release();
	unique_ptr<TiXmlElement> pElem_byLevel(new TiXmlElement("UINT8"));
	if(pElem_byLevel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byLevel->SetAttribute("name", "byLevel");
	pElem_byLevel->SetAttribute("value", NumberToString(s.byLevel).c_str());
	pElem_byLevel->SetAttribute("comment", ToUTF8Ptr("渡劫等级"));
	if(rElement.LinkEndChild(pElem_byLevel.get()) != NULL)
		pElem_byLevel.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecBattleFighterData& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SBattleFighterData s;
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

bool VectorToXML(const TVecBattleFighterData& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SBattleFighterData"));
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

SDujieData::SDujieData() : byTemplateID(0), byLevel(0) { }

SDujieData::SDujieData(UINT8 byTemplateID_, UINT8 byLevel_) : byTemplateID(byTemplateID_), byLevel(byLevel_) { }

CInArchive& operator>>(CInArchive& src, SDujieData& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.byTemplateID;
	src >> s.byLevel;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SDujieData& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.byTemplateID;
	src << s.byLevel;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SDujieData& s)
{
	if(strcmp(rElement.Value(), "SDujieData") != 0)
	{
		LOG_CRI << "rElement is not SDujieData!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byTemplateID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byTemplateID") != 0)
	{
		LOG_CRI << "Attribute: name is not byTemplateID!";
		return false;
	}
	const char* pszVal_byTemplateID = pElemChild->Attribute("value");
	if(pszVal_byTemplateID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byTemplateID, s.byTemplateID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
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
	return true;
}

bool ToXML(const SDujieData& s, TiXmlElement& rElement)
{
	rElement.SetValue("SDujieData");
	rElement.SetAttribute("type", ToUTF8Ptr("渡劫信息"));
	unique_ptr<TiXmlElement> pElem_byTemplateID(new TiXmlElement("UINT8"));
	if(pElem_byTemplateID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byTemplateID->SetAttribute("name", "byTemplateID");
	pElem_byTemplateID->SetAttribute("value", NumberToString(s.byTemplateID).c_str());
	pElem_byTemplateID->SetAttribute("comment", ToUTF8Ptr("渡劫模版Id"));
	if(rElement.LinkEndChild(pElem_byTemplateID.get()) != NULL)
		pElem_byTemplateID.release();
	unique_ptr<TiXmlElement> pElem_byLevel(new TiXmlElement("UINT8"));
	if(pElem_byLevel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byLevel->SetAttribute("name", "byLevel");
	pElem_byLevel->SetAttribute("value", NumberToString(s.byLevel).c_str());
	pElem_byLevel->SetAttribute("comment", ToUTF8Ptr("渡劫等级"));
	if(rElement.LinkEndChild(pElem_byLevel.get()) != NULL)
		pElem_byLevel.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecDujieData& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SDujieData s;
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

bool VectorToXML(const TVecDujieData& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SDujieData"));
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

SCTData::SCTData() : byLianPi(0), byTongJin(0), byQiangJi(0), byDuanGu(0), byHuoLuo(0), 
			byXiSui(0) { }

SCTData::SCTData(UINT8 byLianPi_, UINT8 byTongJin_, UINT8 byQiangJi_, UINT8 byDuanGu_, UINT8 byHuoLuo_, 
			UINT8 byXiSui_)
			: byLianPi(byLianPi_), byTongJin(byTongJin_), byQiangJi(byQiangJi_), byDuanGu(byDuanGu_), byHuoLuo(byHuoLuo_), 
			byXiSui(byXiSui_) { }

CInArchive& operator>>(CInArchive& src, SCTData& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.byLianPi;
	src >> s.byTongJin;
	src >> s.byQiangJi;
	src >> s.byDuanGu;
	src >> s.byHuoLuo;
	src >> s.byXiSui;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SCTData& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.byLianPi;
	src << s.byTongJin;
	src << s.byQiangJi;
	src << s.byDuanGu;
	src << s.byHuoLuo;
	src << s.byXiSui;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SCTData& s)
{
	if(strcmp(rElement.Value(), "SCTData") != 0)
	{
		LOG_CRI << "rElement is not SCTData!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byLianPi is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byLianPi") != 0)
	{
		LOG_CRI << "Attribute: name is not byLianPi!";
		return false;
	}
	const char* pszVal_byLianPi = pElemChild->Attribute("value");
	if(pszVal_byLianPi == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byLianPi, s.byLianPi))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byTongJin is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byTongJin") != 0)
	{
		LOG_CRI << "Attribute: name is not byTongJin!";
		return false;
	}
	const char* pszVal_byTongJin = pElemChild->Attribute("value");
	if(pszVal_byTongJin == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byTongJin, s.byTongJin))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byQiangJi is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byQiangJi") != 0)
	{
		LOG_CRI << "Attribute: name is not byQiangJi!";
		return false;
	}
	const char* pszVal_byQiangJi = pElemChild->Attribute("value");
	if(pszVal_byQiangJi == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byQiangJi, s.byQiangJi))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byDuanGu is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byDuanGu") != 0)
	{
		LOG_CRI << "Attribute: name is not byDuanGu!";
		return false;
	}
	const char* pszVal_byDuanGu = pElemChild->Attribute("value");
	if(pszVal_byDuanGu == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byDuanGu, s.byDuanGu))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byHuoLuo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byHuoLuo") != 0)
	{
		LOG_CRI << "Attribute: name is not byHuoLuo!";
		return false;
	}
	const char* pszVal_byHuoLuo = pElemChild->Attribute("value");
	if(pszVal_byHuoLuo == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byHuoLuo, s.byHuoLuo))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byXiSui is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byXiSui") != 0)
	{
		LOG_CRI << "Attribute: name is not byXiSui!";
		return false;
	}
	const char* pszVal_byXiSui = pElemChild->Attribute("value");
	if(pszVal_byXiSui == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byXiSui, s.byXiSui))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SCTData& s, TiXmlElement& rElement)
{
	rElement.SetValue("SCTData");
	rElement.SetAttribute("type", ToUTF8Ptr("淬体（装备）信息"));
	unique_ptr<TiXmlElement> pElem_byLianPi(new TiXmlElement("UINT8"));
	if(pElem_byLianPi == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byLianPi->SetAttribute("name", "byLianPi");
	pElem_byLianPi->SetAttribute("value", NumberToString(s.byLianPi).c_str());
	pElem_byLianPi->SetAttribute("comment", ToUTF8Ptr("炼皮"));
	if(rElement.LinkEndChild(pElem_byLianPi.get()) != NULL)
		pElem_byLianPi.release();
	unique_ptr<TiXmlElement> pElem_byTongJin(new TiXmlElement("UINT8"));
	if(pElem_byTongJin == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byTongJin->SetAttribute("name", "byTongJin");
	pElem_byTongJin->SetAttribute("value", NumberToString(s.byTongJin).c_str());
	pElem_byTongJin->SetAttribute("comment", ToUTF8Ptr("通筋"));
	if(rElement.LinkEndChild(pElem_byTongJin.get()) != NULL)
		pElem_byTongJin.release();
	unique_ptr<TiXmlElement> pElem_byQiangJi(new TiXmlElement("UINT8"));
	if(pElem_byQiangJi == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byQiangJi->SetAttribute("name", "byQiangJi");
	pElem_byQiangJi->SetAttribute("value", NumberToString(s.byQiangJi).c_str());
	pElem_byQiangJi->SetAttribute("comment", ToUTF8Ptr("强肌"));
	if(rElement.LinkEndChild(pElem_byQiangJi.get()) != NULL)
		pElem_byQiangJi.release();
	unique_ptr<TiXmlElement> pElem_byDuanGu(new TiXmlElement("UINT8"));
	if(pElem_byDuanGu == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byDuanGu->SetAttribute("name", "byDuanGu");
	pElem_byDuanGu->SetAttribute("value", NumberToString(s.byDuanGu).c_str());
	pElem_byDuanGu->SetAttribute("comment", ToUTF8Ptr("锻骨"));
	if(rElement.LinkEndChild(pElem_byDuanGu.get()) != NULL)
		pElem_byDuanGu.release();
	unique_ptr<TiXmlElement> pElem_byHuoLuo(new TiXmlElement("UINT8"));
	if(pElem_byHuoLuo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byHuoLuo->SetAttribute("name", "byHuoLuo");
	pElem_byHuoLuo->SetAttribute("value", NumberToString(s.byHuoLuo).c_str());
	pElem_byHuoLuo->SetAttribute("comment", ToUTF8Ptr("活络"));
	if(rElement.LinkEndChild(pElem_byHuoLuo.get()) != NULL)
		pElem_byHuoLuo.release();
	unique_ptr<TiXmlElement> pElem_byXiSui(new TiXmlElement("UINT8"));
	if(pElem_byXiSui == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byXiSui->SetAttribute("name", "byXiSui");
	pElem_byXiSui->SetAttribute("value", NumberToString(s.byXiSui).c_str());
	pElem_byXiSui->SetAttribute("comment", ToUTF8Ptr("洗髓"));
	if(rElement.LinkEndChild(pElem_byXiSui.get()) != NULL)
		pElem_byXiSui.release();
	return true;
}

#endif

SCittaData::SCittaData() : dwCittaID(0), byLevel(0) { }

SCittaData::SCittaData(UINT32 dwCittaID_, UINT8 byLevel_) : dwCittaID(dwCittaID_), byLevel(byLevel_) { }

CInArchive& operator>>(CInArchive& src, SCittaData& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.dwCittaID;
	src >> s.byLevel;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SCittaData& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.dwCittaID;
	src << s.byLevel;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SCittaData& s)
{
	if(strcmp(rElement.Value(), "SCittaData") != 0)
	{
		LOG_CRI << "rElement is not SCittaData!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwCittaID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwCittaID") != 0)
	{
		LOG_CRI << "Attribute: name is not dwCittaID!";
		return false;
	}
	const char* pszVal_dwCittaID = pElemChild->Attribute("value");
	if(pszVal_dwCittaID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwCittaID, s.dwCittaID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
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
	return true;
}

bool ToXML(const SCittaData& s, TiXmlElement& rElement)
{
	rElement.SetValue("SCittaData");
	rElement.SetAttribute("type", ToUTF8Ptr("心法数据"));
	unique_ptr<TiXmlElement> pElem_dwCittaID(new TiXmlElement("UINT32"));
	if(pElem_dwCittaID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwCittaID->SetAttribute("name", "dwCittaID");
	pElem_dwCittaID->SetAttribute("value", NumberToString(s.dwCittaID).c_str());
	pElem_dwCittaID->SetAttribute("comment", ToUTF8Ptr("心法ID"));
	if(rElement.LinkEndChild(pElem_dwCittaID.get()) != NULL)
		pElem_dwCittaID.release();
	unique_ptr<TiXmlElement> pElem_byLevel(new TiXmlElement("UINT8"));
	if(pElem_byLevel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byLevel->SetAttribute("name", "byLevel");
	pElem_byLevel->SetAttribute("value", NumberToString(s.byLevel).c_str());
	pElem_byLevel->SetAttribute("comment", ToUTF8Ptr("等级"));
	if(rElement.LinkEndChild(pElem_byLevel.get()) != NULL)
		pElem_byLevel.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecCittaData& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SCittaData s;
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

bool VectorToXML(const TVecCittaData& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SCittaData"));
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

SRareTrumpData::SRareTrumpData() : wItemID(0), byTrumpLvl(0), bySelected(0) { }

SRareTrumpData::SRareTrumpData(UINT16 wItemID_, UINT8 byTrumpLvl_, UINT8 bySelected_) : wItemID(wItemID_), byTrumpLvl(byTrumpLvl_), bySelected(bySelected_) { }

CInArchive& operator>>(CInArchive& src, SRareTrumpData& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.wItemID;
	src >> s.byTrumpLvl;
	src >> s.bySelected;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SRareTrumpData& s)
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
	src << s.byTrumpLvl;
	src << s.bySelected;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SRareTrumpData& s)
{
	if(strcmp(rElement.Value(), "SRareTrumpData") != 0)
	{
		LOG_CRI << "rElement is not SRareTrumpData!";
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
		LOG_CRI << "pElemChild for byTrumpLvl is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byTrumpLvl") != 0)
	{
		LOG_CRI << "Attribute: name is not byTrumpLvl!";
		return false;
	}
	const char* pszVal_byTrumpLvl = pElemChild->Attribute("value");
	if(pszVal_byTrumpLvl == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byTrumpLvl, s.byTrumpLvl))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for bySelected is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "bySelected") != 0)
	{
		LOG_CRI << "Attribute: name is not bySelected!";
		return false;
	}
	const char* pszVal_bySelected = pElemChild->Attribute("value");
	if(pszVal_bySelected == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_bySelected, s.bySelected))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SRareTrumpData& s, TiXmlElement& rElement)
{
	rElement.SetValue("SRareTrumpData");
	rElement.SetAttribute("type", ToUTF8Ptr("稀有的法宝信息"));
	unique_ptr<TiXmlElement> pElem_wItemID(new TiXmlElement("UINT16"));
	if(pElem_wItemID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wItemID->SetAttribute("name", "wItemID");
	pElem_wItemID->SetAttribute("value", NumberToString(s.wItemID).c_str());
	pElem_wItemID->SetAttribute("comment", ToUTF8Ptr("法宝模板"));
	if(rElement.LinkEndChild(pElem_wItemID.get()) != NULL)
		pElem_wItemID.release();
	unique_ptr<TiXmlElement> pElem_byTrumpLvl(new TiXmlElement("UINT8"));
	if(pElem_byTrumpLvl == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byTrumpLvl->SetAttribute("name", "byTrumpLvl");
	pElem_byTrumpLvl->SetAttribute("value", NumberToString(s.byTrumpLvl).c_str());
	pElem_byTrumpLvl->SetAttribute("comment", ToUTF8Ptr("法宝等级"));
	if(rElement.LinkEndChild(pElem_byTrumpLvl.get()) != NULL)
		pElem_byTrumpLvl.release();
	unique_ptr<TiXmlElement> pElem_bySelected(new TiXmlElement("UINT8"));
	if(pElem_bySelected == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_bySelected->SetAttribute("name", "bySelected");
	pElem_bySelected->SetAttribute("value", NumberToString(s.bySelected).c_str());
	pElem_bySelected->SetAttribute("comment", ToUTF8Ptr("是否出战"));
	if(rElement.LinkEndChild(pElem_bySelected.get()) != NULL)
		pElem_bySelected.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecRareTrumpData& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SRareTrumpData s;
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

bool VectorToXML(const TVecRareTrumpData& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SRareTrumpData"));
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

SHorseData::SHorseData() : dwHorseID(0), byHorseLvl(0), bySelected(0) { }

SHorseData::SHorseData(UINT32 dwHorseID_, UINT8 byHorseLvl_, UINT8 bySelected_) : dwHorseID(dwHorseID_), byHorseLvl(byHorseLvl_), bySelected(bySelected_) { }

CInArchive& operator>>(CInArchive& src, SHorseData& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.dwHorseID;
	src >> s.byHorseLvl;
	src >> s.bySelected;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SHorseData& s)
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
	src << s.byHorseLvl;
	src << s.bySelected;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SHorseData& s)
{
	if(strcmp(rElement.Value(), "SHorseData") != 0)
	{
		LOG_CRI << "rElement is not SHorseData!";
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
		LOG_CRI << "pElemChild for byHorseLvl is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byHorseLvl") != 0)
	{
		LOG_CRI << "Attribute: name is not byHorseLvl!";
		return false;
	}
	const char* pszVal_byHorseLvl = pElemChild->Attribute("value");
	if(pszVal_byHorseLvl == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byHorseLvl, s.byHorseLvl))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for bySelected is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "bySelected") != 0)
	{
		LOG_CRI << "Attribute: name is not bySelected!";
		return false;
	}
	const char* pszVal_bySelected = pElemChild->Attribute("value");
	if(pszVal_bySelected == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_bySelected, s.bySelected))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SHorseData& s, TiXmlElement& rElement)
{
	rElement.SetValue("SHorseData");
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
	unique_ptr<TiXmlElement> pElem_byHorseLvl(new TiXmlElement("UINT8"));
	if(pElem_byHorseLvl == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byHorseLvl->SetAttribute("name", "byHorseLvl");
	pElem_byHorseLvl->SetAttribute("value", NumberToString(s.byHorseLvl).c_str());
	pElem_byHorseLvl->SetAttribute("comment", ToUTF8Ptr("坐骑等级"));
	if(rElement.LinkEndChild(pElem_byHorseLvl.get()) != NULL)
		pElem_byHorseLvl.release();
	unique_ptr<TiXmlElement> pElem_bySelected(new TiXmlElement("UINT8"));
	if(pElem_bySelected == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_bySelected->SetAttribute("name", "bySelected");
	pElem_bySelected->SetAttribute("value", NumberToString(s.bySelected).c_str());
	pElem_bySelected->SetAttribute("comment", ToUTF8Ptr("0-不跟随 1-跟随"));
	if(rElement.LinkEndChild(pElem_bySelected.get()) != NULL)
		pElem_bySelected.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecHorseData& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SHorseData s;
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

bool VectorToXML(const TVecHorseData& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SHorseData"));
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

SBeautyData::SBeautyData() : wBeautyID(0), byLevel(0) { }

SBeautyData::SBeautyData(UINT16 wBeautyID_, UINT8 byLevel_, const NProtoCommon::TVecFtAttrMod& vecAttr_) : wBeautyID(wBeautyID_), byLevel(byLevel_), vecAttr(vecAttr_) { }

SBeautyData::SBeautyData(SBeautyData&& src) : wBeautyID(src.wBeautyID), byLevel(src.byLevel), vecAttr(move(src.vecAttr)) { }

SBeautyData& SBeautyData::operator=(SBeautyData&& rhs)
{
	if(this != &rhs)
	{
		this->~SBeautyData();
		new (this) SBeautyData(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SBeautyData& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.wBeautyID;
	src >> s.byLevel;
	src >> s.vecAttr;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SBeautyData& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.wBeautyID;
	src << s.byLevel;
	src << s.vecAttr;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SBeautyData& s)
{
	if(strcmp(rElement.Value(), "SBeautyData") != 0)
	{
		LOG_CRI << "rElement is not SBeautyData!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wBeautyID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wBeautyID") != 0)
	{
		LOG_CRI << "Attribute: name is not wBeautyID!";
		return false;
	}
	const char* pszVal_wBeautyID = pElemChild->Attribute("value");
	if(pszVal_wBeautyID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wBeautyID, s.wBeautyID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
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
		LOG_CRI << "pElemChild for vecAttr is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "ProtoCommon::TVecFtAttrMod") != 0)
	{
		LOG_CRI << "pElemChild is not ProtoCommon::TVecFtAttrMod!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecAttr") != 0)
	{
		LOG_CRI << "Attribute: name is not vecAttr!";
		return false;
	}
	if(!NProtoCommon::VectorFromXML(*pElemChild, s.vecAttr))
	{
		LOG_CRI << "VectorFromXML for vecAttr fails!";
		return false;
	}
	return true;
}

bool ToXML(const SBeautyData& s, TiXmlElement& rElement)
{
	rElement.SetValue("SBeautyData");
	rElement.SetAttribute("type", ToUTF8Ptr("出战美女信息"));
	unique_ptr<TiXmlElement> pElem_wBeautyID(new TiXmlElement("UINT16"));
	if(pElem_wBeautyID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wBeautyID->SetAttribute("name", "wBeautyID");
	pElem_wBeautyID->SetAttribute("value", NumberToString(s.wBeautyID).c_str());
	pElem_wBeautyID->SetAttribute("comment", ToUTF8Ptr("美女ID"));
	if(rElement.LinkEndChild(pElem_wBeautyID.get()) != NULL)
		pElem_wBeautyID.release();
	unique_ptr<TiXmlElement> pElem_byLevel(new TiXmlElement("UINT8"));
	if(pElem_byLevel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byLevel->SetAttribute("name", "byLevel");
	pElem_byLevel->SetAttribute("value", NumberToString(s.byLevel).c_str());
	pElem_byLevel->SetAttribute("comment", ToUTF8Ptr("美女等级"));
	if(rElement.LinkEndChild(pElem_byLevel.get()) != NULL)
		pElem_byLevel.release();
	unique_ptr<TiXmlElement> pElem_vecAttr(new TiXmlElement("ProtoCommon::TVecFtAttrMod"));
	if(pElem_vecAttr == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecAttr->SetAttribute("name", "vecAttr");
	if(!NProtoCommon::VectorToXML(s.vecAttr, *pElem_vecAttr))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecAttr->SetAttribute("comment", ToUTF8Ptr("美女属性"));
	if(rElement.LinkEndChild(pElem_vecAttr.get()) != NULL)
		pElem_vecAttr.release();
	return true;
}

#endif

SFashionData::SFashionData() : wItemID(0), byFashionLvl(0), bySelected(0) { }

SFashionData::SFashionData(UINT16 wItemID_, UINT8 byFashionLvl_, UINT8 bySelected_) : wItemID(wItemID_), byFashionLvl(byFashionLvl_), bySelected(bySelected_) { }

CInArchive& operator>>(CInArchive& src, SFashionData& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.wItemID;
	src >> s.byFashionLvl;
	src >> s.bySelected;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SFashionData& s)
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
	src << s.byFashionLvl;
	src << s.bySelected;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SFashionData& s)
{
	if(strcmp(rElement.Value(), "SFashionData") != 0)
	{
		LOG_CRI << "rElement is not SFashionData!";
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
		LOG_CRI << "pElemChild for byFashionLvl is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byFashionLvl") != 0)
	{
		LOG_CRI << "Attribute: name is not byFashionLvl!";
		return false;
	}
	const char* pszVal_byFashionLvl = pElemChild->Attribute("value");
	if(pszVal_byFashionLvl == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byFashionLvl, s.byFashionLvl))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for bySelected is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "bySelected") != 0)
	{
		LOG_CRI << "Attribute: name is not bySelected!";
		return false;
	}
	const char* pszVal_bySelected = pElemChild->Attribute("value");
	if(pszVal_bySelected == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_bySelected, s.bySelected))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SFashionData& s, TiXmlElement& rElement)
{
	rElement.SetValue("SFashionData");
	rElement.SetAttribute("type", ToUTF8Ptr("时装信息"));
	unique_ptr<TiXmlElement> pElem_wItemID(new TiXmlElement("UINT16"));
	if(pElem_wItemID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wItemID->SetAttribute("name", "wItemID");
	pElem_wItemID->SetAttribute("value", NumberToString(s.wItemID).c_str());
	pElem_wItemID->SetAttribute("comment", ToUTF8Ptr("时装模板"));
	if(rElement.LinkEndChild(pElem_wItemID.get()) != NULL)
		pElem_wItemID.release();
	unique_ptr<TiXmlElement> pElem_byFashionLvl(new TiXmlElement("UINT8"));
	if(pElem_byFashionLvl == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byFashionLvl->SetAttribute("name", "byFashionLvl");
	pElem_byFashionLvl->SetAttribute("value", NumberToString(s.byFashionLvl).c_str());
	pElem_byFashionLvl->SetAttribute("comment", ToUTF8Ptr("时装等级"));
	if(rElement.LinkEndChild(pElem_byFashionLvl.get()) != NULL)
		pElem_byFashionLvl.release();
	unique_ptr<TiXmlElement> pElem_bySelected(new TiXmlElement("UINT8"));
	if(pElem_bySelected == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_bySelected->SetAttribute("name", "bySelected");
	pElem_bySelected->SetAttribute("value", NumberToString(s.bySelected).c_str());
	pElem_bySelected->SetAttribute("comment", ToUTF8Ptr("是否选中"));
	if(rElement.LinkEndChild(pElem_bySelected.get()) != NULL)
		pElem_bySelected.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecFashionData& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SFashionData s;
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

bool VectorToXML(const TVecFashionData& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SFashionData"));
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

SCollectionData::SCollectionData() : byCollectionLevel(0), dwAP(0) { }

SCollectionData::SCollectionData(UINT8 byCollectionLevel_, UINT32 dwAP_) : byCollectionLevel(byCollectionLevel_), dwAP(dwAP_) { }

CInArchive& operator>>(CInArchive& src, SCollectionData& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.byCollectionLevel;
	src >> s.dwAP;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SCollectionData& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.byCollectionLevel;
	src << s.dwAP;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SCollectionData& s)
{
	if(strcmp(rElement.Value(), "SCollectionData") != 0)
	{
		LOG_CRI << "rElement is not SCollectionData!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byCollectionLevel is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byCollectionLevel") != 0)
	{
		LOG_CRI << "Attribute: name is not byCollectionLevel!";
		return false;
	}
	const char* pszVal_byCollectionLevel = pElemChild->Attribute("value");
	if(pszVal_byCollectionLevel == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byCollectionLevel, s.byCollectionLevel))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwAP is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwAP") != 0)
	{
		LOG_CRI << "Attribute: name is not dwAP!";
		return false;
	}
	const char* pszVal_dwAP = pElemChild->Attribute("value");
	if(pszVal_dwAP == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwAP, s.dwAP))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SCollectionData& s, TiXmlElement& rElement)
{
	rElement.SetValue("SCollectionData");
	rElement.SetAttribute("type", ToUTF8Ptr("收集信息"));
	unique_ptr<TiXmlElement> pElem_byCollectionLevel(new TiXmlElement("UINT8"));
	if(pElem_byCollectionLevel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byCollectionLevel->SetAttribute("name", "byCollectionLevel");
	pElem_byCollectionLevel->SetAttribute("value", NumberToString(s.byCollectionLevel).c_str());
	pElem_byCollectionLevel->SetAttribute("comment", ToUTF8Ptr("收藏等级"));
	if(rElement.LinkEndChild(pElem_byCollectionLevel.get()) != NULL)
		pElem_byCollectionLevel.release();
	unique_ptr<TiXmlElement> pElem_dwAP(new TiXmlElement("UINT32"));
	if(pElem_dwAP == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwAP->SetAttribute("name", "dwAP");
	pElem_dwAP->SetAttribute("value", NumberToString(s.dwAP).c_str());
	pElem_dwAP->SetAttribute("comment", ToUTF8Ptr("收藏点"));
	if(rElement.LinkEndChild(pElem_dwAP.get()) != NULL)
		pElem_dwAP.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecCollectionData& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SCollectionData s;
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

bool VectorToXML(const TVecCollectionData& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SCollectionData"));
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

STitleData::STitleData() : wTitleID(0), bySelected(0) { }

STitleData::STitleData(UINT16 wTitleID_, UINT8 bySelected_) : wTitleID(wTitleID_), bySelected(bySelected_) { }

CInArchive& operator>>(CInArchive& src, STitleData& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.wTitleID;
	src >> s.bySelected;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const STitleData& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.wTitleID;
	src << s.bySelected;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, STitleData& s)
{
	if(strcmp(rElement.Value(), "STitleData") != 0)
	{
		LOG_CRI << "rElement is not STitleData!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wTitleID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wTitleID") != 0)
	{
		LOG_CRI << "Attribute: name is not wTitleID!";
		return false;
	}
	const char* pszVal_wTitleID = pElemChild->Attribute("value");
	if(pszVal_wTitleID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wTitleID, s.wTitleID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for bySelected is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "bySelected") != 0)
	{
		LOG_CRI << "Attribute: name is not bySelected!";
		return false;
	}
	const char* pszVal_bySelected = pElemChild->Attribute("value");
	if(pszVal_bySelected == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_bySelected, s.bySelected))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const STitleData& s, TiXmlElement& rElement)
{
	rElement.SetValue("STitleData");
	rElement.SetAttribute("type", ToUTF8Ptr("称号信息"));
	unique_ptr<TiXmlElement> pElem_wTitleID(new TiXmlElement("UINT16"));
	if(pElem_wTitleID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wTitleID->SetAttribute("name", "wTitleID");
	pElem_wTitleID->SetAttribute("value", NumberToString(s.wTitleID).c_str());
	pElem_wTitleID->SetAttribute("comment", ToUTF8Ptr("称号ID"));
	if(rElement.LinkEndChild(pElem_wTitleID.get()) != NULL)
		pElem_wTitleID.release();
	unique_ptr<TiXmlElement> pElem_bySelected(new TiXmlElement("UINT8"));
	if(pElem_bySelected == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_bySelected->SetAttribute("name", "bySelected");
	pElem_bySelected->SetAttribute("value", NumberToString(s.bySelected).c_str());
	pElem_bySelected->SetAttribute("comment", ToUTF8Ptr("是否选中"));
	if(rElement.LinkEndChild(pElem_bySelected.get()) != NULL)
		pElem_bySelected.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecTitleData& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		STitleData s;
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

bool VectorToXML(const TVecTitleData& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("STitleData"));
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

SGuildSkillData::SGuildSkillData() : dwGuildSkillID(0), byGuildSkillLvl(0) { }

SGuildSkillData::SGuildSkillData(UINT32 dwGuildSkillID_, UINT8 byGuildSkillLvl_) : dwGuildSkillID(dwGuildSkillID_), byGuildSkillLvl(byGuildSkillLvl_) { }

CInArchive& operator>>(CInArchive& src, SGuildSkillData& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.dwGuildSkillID;
	src >> s.byGuildSkillLvl;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SGuildSkillData& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.dwGuildSkillID;
	src << s.byGuildSkillLvl;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SGuildSkillData& s)
{
	if(strcmp(rElement.Value(), "SGuildSkillData") != 0)
	{
		LOG_CRI << "rElement is not SGuildSkillData!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwGuildSkillID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwGuildSkillID") != 0)
	{
		LOG_CRI << "Attribute: name is not dwGuildSkillID!";
		return false;
	}
	const char* pszVal_dwGuildSkillID = pElemChild->Attribute("value");
	if(pszVal_dwGuildSkillID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwGuildSkillID, s.dwGuildSkillID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byGuildSkillLvl is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byGuildSkillLvl") != 0)
	{
		LOG_CRI << "Attribute: name is not byGuildSkillLvl!";
		return false;
	}
	const char* pszVal_byGuildSkillLvl = pElemChild->Attribute("value");
	if(pszVal_byGuildSkillLvl == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byGuildSkillLvl, s.byGuildSkillLvl))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SGuildSkillData& s, TiXmlElement& rElement)
{
	rElement.SetValue("SGuildSkillData");
	rElement.SetAttribute("type", ToUTF8Ptr("帮派技能信息"));
	unique_ptr<TiXmlElement> pElem_dwGuildSkillID(new TiXmlElement("UINT32"));
	if(pElem_dwGuildSkillID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwGuildSkillID->SetAttribute("name", "dwGuildSkillID");
	pElem_dwGuildSkillID->SetAttribute("value", NumberToString(s.dwGuildSkillID).c_str());
	pElem_dwGuildSkillID->SetAttribute("comment", ToUTF8Ptr("技能id"));
	if(rElement.LinkEndChild(pElem_dwGuildSkillID.get()) != NULL)
		pElem_dwGuildSkillID.release();
	unique_ptr<TiXmlElement> pElem_byGuildSkillLvl(new TiXmlElement("UINT8"));
	if(pElem_byGuildSkillLvl == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byGuildSkillLvl->SetAttribute("name", "byGuildSkillLvl");
	pElem_byGuildSkillLvl->SetAttribute("value", NumberToString(s.byGuildSkillLvl).c_str());
	pElem_byGuildSkillLvl->SetAttribute("comment", ToUTF8Ptr("技能等级"));
	if(rElement.LinkEndChild(pElem_byGuildSkillLvl.get()) != NULL)
		pElem_byGuildSkillLvl.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecGuildSkillData& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SGuildSkillData s;
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

bool VectorToXML(const TVecGuildSkillData& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SGuildSkillData"));
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

SGuildData::SGuildData() : byGuildLvl(0) { }

SGuildData::SGuildData(const std::string& strName_, UINT8 byGuildLvl_, const TVecGuildSkillData& vecGuildSkill_) : strName(strName_), byGuildLvl(byGuildLvl_), vecGuildSkill(vecGuildSkill_) { }

SGuildData::SGuildData(SGuildData&& src) : strName(move(src.strName)), byGuildLvl(src.byGuildLvl), vecGuildSkill(move(src.vecGuildSkill)) { }

SGuildData& SGuildData::operator=(SGuildData&& rhs)
{
	if(this != &rhs)
	{
		this->~SGuildData();
		new (this) SGuildData(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SGuildData& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.strName;
	src >> s.byGuildLvl;
	src >> s.vecGuildSkill;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SGuildData& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.strName;
	src << s.byGuildLvl;
	src << s.vecGuildSkill;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SGuildData& s)
{
	if(strcmp(rElement.Value(), "SGuildData") != 0)
	{
		LOG_CRI << "rElement is not SGuildData!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
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
		LOG_CRI << "pElemChild for byGuildLvl is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byGuildLvl") != 0)
	{
		LOG_CRI << "Attribute: name is not byGuildLvl!";
		return false;
	}
	const char* pszVal_byGuildLvl = pElemChild->Attribute("value");
	if(pszVal_byGuildLvl == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byGuildLvl, s.byGuildLvl))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecGuildSkill is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecGuildSkillData") != 0)
	{
		LOG_CRI << "pElemChild is not TVecGuildSkillData!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecGuildSkill") != 0)
	{
		LOG_CRI << "Attribute: name is not vecGuildSkill!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecGuildSkill))
	{
		LOG_CRI << "VectorFromXML for vecGuildSkill fails!";
		return false;
	}
	return true;
}

bool ToXML(const SGuildData& s, TiXmlElement& rElement)
{
	rElement.SetValue("SGuildData");
	rElement.SetAttribute("type", ToUTF8Ptr("帮派信息"));
	unique_ptr<TiXmlElement> pElem_strName(new TiXmlElement("string"));
	if(pElem_strName == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strName->SetAttribute("name", "strName");
	pElem_strName->SetAttribute("value", s.strName.c_str());
	pElem_strName->SetAttribute("comment", ToUTF8Ptr("帮派名称"));
	if(rElement.LinkEndChild(pElem_strName.get()) != NULL)
		pElem_strName.release();
	unique_ptr<TiXmlElement> pElem_byGuildLvl(new TiXmlElement("UINT8"));
	if(pElem_byGuildLvl == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byGuildLvl->SetAttribute("name", "byGuildLvl");
	pElem_byGuildLvl->SetAttribute("value", NumberToString(s.byGuildLvl).c_str());
	pElem_byGuildLvl->SetAttribute("comment", ToUTF8Ptr("帮派等级"));
	if(rElement.LinkEndChild(pElem_byGuildLvl.get()) != NULL)
		pElem_byGuildLvl.release();
	unique_ptr<TiXmlElement> pElem_vecGuildSkill(new TiXmlElement("TVecGuildSkillData"));
	if(pElem_vecGuildSkill == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecGuildSkill->SetAttribute("name", "vecGuildSkill");
	if(!VectorToXML(s.vecGuildSkill, *pElem_vecGuildSkill))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecGuildSkill->SetAttribute("comment", ToUTF8Ptr("帮派技能"));
	if(rElement.LinkEndChild(pElem_vecGuildSkill.get()) != NULL)
		pElem_vecGuildSkill.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecGuildData& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SGuildData s;
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

bool VectorToXML(const TVecGuildData& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SGuildData"));
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

SSkillData::SSkillData() : dwSkillID(0), bySkillLvl(0), bySkillQuality(0) { }

SSkillData::SSkillData(UINT32 dwSkillID_, UINT8 bySkillLvl_, UINT8 bySkillQuality_) : dwSkillID(dwSkillID_), bySkillLvl(bySkillLvl_), bySkillQuality(bySkillQuality_) { }

CInArchive& operator>>(CInArchive& src, SSkillData& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.dwSkillID;
	src >> s.bySkillLvl;
	src >> s.bySkillQuality;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SSkillData& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.dwSkillID;
	src << s.bySkillLvl;
	src << s.bySkillQuality;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SSkillData& s)
{
	if(strcmp(rElement.Value(), "SSkillData") != 0)
	{
		LOG_CRI << "rElement is not SSkillData!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwSkillID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwSkillID") != 0)
	{
		LOG_CRI << "Attribute: name is not dwSkillID!";
		return false;
	}
	const char* pszVal_dwSkillID = pElemChild->Attribute("value");
	if(pszVal_dwSkillID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwSkillID, s.dwSkillID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for bySkillLvl is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "bySkillLvl") != 0)
	{
		LOG_CRI << "Attribute: name is not bySkillLvl!";
		return false;
	}
	const char* pszVal_bySkillLvl = pElemChild->Attribute("value");
	if(pszVal_bySkillLvl == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_bySkillLvl, s.bySkillLvl))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for bySkillQuality is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "bySkillQuality") != 0)
	{
		LOG_CRI << "Attribute: name is not bySkillQuality!";
		return false;
	}
	const char* pszVal_bySkillQuality = pElemChild->Attribute("value");
	if(pszVal_bySkillQuality == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_bySkillQuality, s.bySkillQuality))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SSkillData& s, TiXmlElement& rElement)
{
	rElement.SetValue("SSkillData");
	rElement.SetAttribute("type", ToUTF8Ptr("参与战斗的技能信息"));
	unique_ptr<TiXmlElement> pElem_dwSkillID(new TiXmlElement("UINT32"));
	if(pElem_dwSkillID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwSkillID->SetAttribute("name", "dwSkillID");
	pElem_dwSkillID->SetAttribute("value", NumberToString(s.dwSkillID).c_str());
	pElem_dwSkillID->SetAttribute("comment", ToUTF8Ptr("技能id"));
	if(rElement.LinkEndChild(pElem_dwSkillID.get()) != NULL)
		pElem_dwSkillID.release();
	unique_ptr<TiXmlElement> pElem_bySkillLvl(new TiXmlElement("UINT8"));
	if(pElem_bySkillLvl == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_bySkillLvl->SetAttribute("name", "bySkillLvl");
	pElem_bySkillLvl->SetAttribute("value", NumberToString(s.bySkillLvl).c_str());
	pElem_bySkillLvl->SetAttribute("comment", ToUTF8Ptr("技能等级"));
	if(rElement.LinkEndChild(pElem_bySkillLvl.get()) != NULL)
		pElem_bySkillLvl.release();
	unique_ptr<TiXmlElement> pElem_bySkillQuality(new TiXmlElement("UINT8"));
	if(pElem_bySkillQuality == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_bySkillQuality->SetAttribute("name", "bySkillQuality");
	pElem_bySkillQuality->SetAttribute("value", NumberToString(s.bySkillQuality).c_str());
	pElem_bySkillQuality->SetAttribute("comment", ToUTF8Ptr("技能品质"));
	if(rElement.LinkEndChild(pElem_bySkillQuality.get()) != NULL)
		pElem_bySkillQuality.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecSkillData& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SSkillData s;
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

bool VectorToXML(const TVecSkillData& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SSkillData"));
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

SBeastSoulData::SBeastSoulData() { }

SBeastSoulData::SBeastSoulData(const NRoleInfoDefine::TVecBeastSoulInfo& vecBeasSoulInfo_, const NProtoCommon::TVecFtAttrMod& vecAttr_) : vecBeasSoulInfo(vecBeasSoulInfo_), vecAttr(vecAttr_) { }

SBeastSoulData::SBeastSoulData(SBeastSoulData&& src) : vecBeasSoulInfo(move(src.vecBeasSoulInfo)), vecAttr(move(src.vecAttr)) { }

SBeastSoulData& SBeastSoulData::operator=(SBeastSoulData&& rhs)
{
	if(this != &rhs)
	{
		this->~SBeastSoulData();
		new (this) SBeastSoulData(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SBeastSoulData& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.vecBeasSoulInfo;
	src >> s.vecAttr;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SBeastSoulData& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.vecBeasSoulInfo;
	src << s.vecAttr;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SBeastSoulData& s)
{
	if(strcmp(rElement.Value(), "SBeastSoulData") != 0)
	{
		LOG_CRI << "rElement is not SBeastSoulData!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecBeasSoulInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "RoleInfoDefine::TVecBeastSoulInfo") != 0)
	{
		LOG_CRI << "pElemChild is not RoleInfoDefine::TVecBeastSoulInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecBeasSoulInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not vecBeasSoulInfo!";
		return false;
	}
	if(!NRoleInfoDefine::VectorFromXML(*pElemChild, s.vecBeasSoulInfo))
	{
		LOG_CRI << "VectorFromXML for vecBeasSoulInfo fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecAttr is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "ProtoCommon::TVecFtAttrMod") != 0)
	{
		LOG_CRI << "pElemChild is not ProtoCommon::TVecFtAttrMod!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecAttr") != 0)
	{
		LOG_CRI << "Attribute: name is not vecAttr!";
		return false;
	}
	if(!NProtoCommon::VectorFromXML(*pElemChild, s.vecAttr))
	{
		LOG_CRI << "VectorFromXML for vecAttr fails!";
		return false;
	}
	return true;
}

bool ToXML(const SBeastSoulData& s, TiXmlElement& rElement)
{
	rElement.SetValue("SBeastSoulData");
	rElement.SetAttribute("type", ToUTF8Ptr("兽魂"));
	unique_ptr<TiXmlElement> pElem_vecBeasSoulInfo(new TiXmlElement("RoleInfoDefine::TVecBeastSoulInfo"));
	if(pElem_vecBeasSoulInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecBeasSoulInfo->SetAttribute("name", "vecBeasSoulInfo");
	if(!NRoleInfoDefine::VectorToXML(s.vecBeasSoulInfo, *pElem_vecBeasSoulInfo))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecBeasSoulInfo->SetAttribute("comment", ToUTF8Ptr("兽魂"));
	if(rElement.LinkEndChild(pElem_vecBeasSoulInfo.get()) != NULL)
		pElem_vecBeasSoulInfo.release();
	unique_ptr<TiXmlElement> pElem_vecAttr(new TiXmlElement("ProtoCommon::TVecFtAttrMod"));
	if(pElem_vecAttr == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecAttr->SetAttribute("name", "vecAttr");
	if(!NProtoCommon::VectorToXML(s.vecAttr, *pElem_vecAttr))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecAttr->SetAttribute("comment", ToUTF8Ptr("兽魂属性"));
	if(rElement.LinkEndChild(pElem_vecAttr.get()) != NULL)
		pElem_vecAttr.release();
	return true;
}

#endif

SCombData::SCombData() : byGroupID(0), byLevel(0), bySelected(0) { }

SCombData::SCombData(UINT8 byGroupID_, UINT8 byLevel_, UINT8 bySelected_) : byGroupID(byGroupID_), byLevel(byLevel_), bySelected(bySelected_) { }

CInArchive& operator>>(CInArchive& src, SCombData& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.byGroupID;
	src >> s.byLevel;
	src >> s.bySelected;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SCombData& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.byGroupID;
	src << s.byLevel;
	src << s.bySelected;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SCombData& s)
{
	if(strcmp(rElement.Value(), "SCombData") != 0)
	{
		LOG_CRI << "rElement is not SCombData!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byGroupID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byGroupID") != 0)
	{
		LOG_CRI << "Attribute: name is not byGroupID!";
		return false;
	}
	const char* pszVal_byGroupID = pElemChild->Attribute("value");
	if(pszVal_byGroupID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byGroupID, s.byGroupID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
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
		LOG_CRI << "pElemChild for bySelected is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "bySelected") != 0)
	{
		LOG_CRI << "Attribute: name is not bySelected!";
		return false;
	}
	const char* pszVal_bySelected = pElemChild->Attribute("value");
	if(pszVal_bySelected == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_bySelected, s.bySelected))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SCombData& s, TiXmlElement& rElement)
{
	rElement.SetValue("SCombData");
	rElement.SetAttribute("type", ToUTF8Ptr("组合"));
	unique_ptr<TiXmlElement> pElem_byGroupID(new TiXmlElement("UINT8"));
	if(pElem_byGroupID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byGroupID->SetAttribute("name", "byGroupID");
	pElem_byGroupID->SetAttribute("value", NumberToString(s.byGroupID).c_str());
	pElem_byGroupID->SetAttribute("comment", ToUTF8Ptr("组合ID"));
	if(rElement.LinkEndChild(pElem_byGroupID.get()) != NULL)
		pElem_byGroupID.release();
	unique_ptr<TiXmlElement> pElem_byLevel(new TiXmlElement("UINT8"));
	if(pElem_byLevel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byLevel->SetAttribute("name", "byLevel");
	pElem_byLevel->SetAttribute("value", NumberToString(s.byLevel).c_str());
	pElem_byLevel->SetAttribute("comment", ToUTF8Ptr("组合等级"));
	if(rElement.LinkEndChild(pElem_byLevel.get()) != NULL)
		pElem_byLevel.release();
	unique_ptr<TiXmlElement> pElem_bySelected(new TiXmlElement("UINT8"));
	if(pElem_bySelected == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_bySelected->SetAttribute("name", "bySelected");
	pElem_bySelected->SetAttribute("value", NumberToString(s.bySelected).c_str());
	pElem_bySelected->SetAttribute("comment", ToUTF8Ptr("是否出战"));
	if(rElement.LinkEndChild(pElem_bySelected.get()) != NULL)
		pElem_bySelected.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecCombData& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SCombData s;
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

bool VectorToXML(const TVecCombData& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SCombData"));
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

SRoleData::SRoleData() : eCareer((NProtoCommon::ECareerType)0), byLevel(0), dwBTPoint(0) { }

SRoleData::SRoleData(SRoleData&& src) : strName(move(src.strName)), eCareer(src.eCareer), byLevel(src.byLevel), dwBTPoint(src.dwBTPoint), vecAttr(move(src.vecAttr)), 
			vecBattleFighter(move(src.vecBattleFighter)), sDujie(src.sDujie), sCuiTi(src.sCuiTi), vecBaoshi(src.vecBaoshi), vecCitta(move(src.vecCitta)), 
			vecTrump(move(src.vecTrump)), vecRareTrump(move(src.vecRareTrump)), sBeauty(move(src.sBeauty)), sBeastSoul(move(src.sBeastSoul)), vecComb(move(src.vecComb)), 
			vecSkill(move(src.vecSkill)), vecHorse(move(src.vecHorse)), vecFashion(move(src.vecFashion)), vecTitle(move(src.vecTitle)), vecGuild(move(src.vecGuild)), 
			vecTianBookAttr(move(src.vecTianBookAttr)) { }

SRoleData& SRoleData::operator=(SRoleData&& rhs)
{
	if(this != &rhs)
	{
		this->~SRoleData();
		new (this) SRoleData(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SRoleData& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.strName;
	src >> (UINT8&)s.eCareer;
	src >> s.byLevel;
	src >> s.dwBTPoint;
	src >> s.vecAttr;
	src >> s.vecBattleFighter;
	src >> s.sDujie;
	src >> s.sCuiTi;
	src >> s.vecBaoshi;
	src >> s.vecCitta;
	src >> s.vecTrump;
	src >> s.vecRareTrump;
	src >> s.sBeauty;
	src >> s.sBeastSoul;
	src >> s.vecComb;
	src >> s.vecSkill;
	src >> s.vecHorse;
	src >> s.vecFashion;
	src >> s.vecTitle;
	src >> s.vecGuild;
	src >> s.vecTianBookAttr;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SRoleData& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.strName;
	src << (UINT8&)s.eCareer;
	src << s.byLevel;
	src << s.dwBTPoint;
	src << s.vecAttr;
	src << s.vecBattleFighter;
	src << s.sDujie;
	src << s.sCuiTi;
	src << s.vecBaoshi;
	src << s.vecCitta;
	src << s.vecTrump;
	src << s.vecRareTrump;
	src << s.sBeauty;
	src << s.sBeastSoul;
	src << s.vecComb;
	src << s.vecSkill;
	src << s.vecHorse;
	src << s.vecFashion;
	src << s.vecTitle;
	src << s.vecGuild;
	src << s.vecTianBookAttr;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SRoleData& s)
{
	if(strcmp(rElement.Value(), "SRoleData") != 0)
	{
		LOG_CRI << "rElement is not SRoleData!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
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
		LOG_CRI << "pElemChild for dwBTPoint is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwBTPoint") != 0)
	{
		LOG_CRI << "Attribute: name is not dwBTPoint!";
		return false;
	}
	const char* pszVal_dwBTPoint = pElemChild->Attribute("value");
	if(pszVal_dwBTPoint == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwBTPoint, s.dwBTPoint))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecAttr is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "ProtoCommon::TVecFtAttrMod") != 0)
	{
		LOG_CRI << "pElemChild is not ProtoCommon::TVecFtAttrMod!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecAttr") != 0)
	{
		LOG_CRI << "Attribute: name is not vecAttr!";
		return false;
	}
	if(!NProtoCommon::VectorFromXML(*pElemChild, s.vecAttr))
	{
		LOG_CRI << "VectorFromXML for vecAttr fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecBattleFighter is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecBattleFighterData") != 0)
	{
		LOG_CRI << "pElemChild is not TVecBattleFighterData!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecBattleFighter") != 0)
	{
		LOG_CRI << "Attribute: name is not vecBattleFighter!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecBattleFighter))
	{
		LOG_CRI << "VectorFromXML for vecBattleFighter fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for sDujie is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "SDujieData") != 0)
	{
		LOG_CRI << "pElemChild is not SDujieData!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "sDujie") != 0)
	{
		LOG_CRI << "Attribute: name is not sDujie!";
		return false;
	}
	if(!FromXML(*pElemChild, s.sDujie))
	{
		LOG_CRI << "FromXML for: sDujie fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for sCuiTi is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "SCTData") != 0)
	{
		LOG_CRI << "pElemChild is not SCTData!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "sCuiTi") != 0)
	{
		LOG_CRI << "Attribute: name is not sCuiTi!";
		return false;
	}
	if(!FromXML(*pElemChild, s.sCuiTi))
	{
		LOG_CRI << "FromXML for: sCuiTi fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecBaoshi is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecUINT32") != 0)
	{
		LOG_CRI << "pElemChild is not TVecUINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecBaoshi") != 0)
	{
		LOG_CRI << "Attribute: name is not vecBaoshi!";
		return false;
	}
	const char* pszText_vecBaoshi = pElemChild->GetText();
	if(pszText_vecBaoshi != NULL)
		SplitToNumber(pszText_vecBaoshi, ",", s.vecBaoshi);
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecCitta is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecCittaData") != 0)
	{
		LOG_CRI << "pElemChild is not TVecCittaData!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecCitta") != 0)
	{
		LOG_CRI << "Attribute: name is not vecCitta!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecCitta))
	{
		LOG_CRI << "VectorFromXML for vecCitta fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecTrump is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "ItemProt::TVecEquipTrump") != 0)
	{
		LOG_CRI << "pElemChild is not ItemProt::TVecEquipTrump!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecTrump") != 0)
	{
		LOG_CRI << "Attribute: name is not vecTrump!";
		return false;
	}
	if(!NItemProt::VectorFromXML(*pElemChild, s.vecTrump))
	{
		LOG_CRI << "VectorFromXML for vecTrump fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecRareTrump is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecRareTrumpData") != 0)
	{
		LOG_CRI << "pElemChild is not TVecRareTrumpData!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecRareTrump") != 0)
	{
		LOG_CRI << "Attribute: name is not vecRareTrump!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecRareTrump))
	{
		LOG_CRI << "VectorFromXML for vecRareTrump fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for sBeauty is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "SBeautyData") != 0)
	{
		LOG_CRI << "pElemChild is not SBeautyData!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "sBeauty") != 0)
	{
		LOG_CRI << "Attribute: name is not sBeauty!";
		return false;
	}
	if(!FromXML(*pElemChild, s.sBeauty))
	{
		LOG_CRI << "FromXML for: sBeauty fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for sBeastSoul is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "SBeastSoulData") != 0)
	{
		LOG_CRI << "pElemChild is not SBeastSoulData!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "sBeastSoul") != 0)
	{
		LOG_CRI << "Attribute: name is not sBeastSoul!";
		return false;
	}
	if(!FromXML(*pElemChild, s.sBeastSoul))
	{
		LOG_CRI << "FromXML for: sBeastSoul fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecComb is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecCombData") != 0)
	{
		LOG_CRI << "pElemChild is not TVecCombData!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecComb") != 0)
	{
		LOG_CRI << "Attribute: name is not vecComb!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecComb))
	{
		LOG_CRI << "VectorFromXML for vecComb fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecSkill is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecSkillData") != 0)
	{
		LOG_CRI << "pElemChild is not TVecSkillData!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecSkill") != 0)
	{
		LOG_CRI << "Attribute: name is not vecSkill!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecSkill))
	{
		LOG_CRI << "VectorFromXML for vecSkill fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecHorse is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecHorseData") != 0)
	{
		LOG_CRI << "pElemChild is not TVecHorseData!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecHorse") != 0)
	{
		LOG_CRI << "Attribute: name is not vecHorse!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecHorse))
	{
		LOG_CRI << "VectorFromXML for vecHorse fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecFashion is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecFashionData") != 0)
	{
		LOG_CRI << "pElemChild is not TVecFashionData!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecFashion") != 0)
	{
		LOG_CRI << "Attribute: name is not vecFashion!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecFashion))
	{
		LOG_CRI << "VectorFromXML for vecFashion fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecTitle is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecTitleData") != 0)
	{
		LOG_CRI << "pElemChild is not TVecTitleData!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecTitle") != 0)
	{
		LOG_CRI << "Attribute: name is not vecTitle!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecTitle))
	{
		LOG_CRI << "VectorFromXML for vecTitle fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecGuild is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecGuildData") != 0)
	{
		LOG_CRI << "pElemChild is not TVecGuildData!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecGuild") != 0)
	{
		LOG_CRI << "Attribute: name is not vecGuild!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecGuild))
	{
		LOG_CRI << "VectorFromXML for vecGuild fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecTianBookAttr is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "ProtoCommon::TVecFtAttrMod") != 0)
	{
		LOG_CRI << "pElemChild is not ProtoCommon::TVecFtAttrMod!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecTianBookAttr") != 0)
	{
		LOG_CRI << "Attribute: name is not vecTianBookAttr!";
		return false;
	}
	if(!NProtoCommon::VectorFromXML(*pElemChild, s.vecTianBookAttr))
	{
		LOG_CRI << "VectorFromXML for vecTianBookAttr fails!";
		return false;
	}
	return true;
}

bool ToXML(const SRoleData& s, TiXmlElement& rElement)
{
	rElement.SetValue("SRoleData");
	rElement.SetAttribute("type", ToUTF8Ptr("主角信息"));
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
	pElem_eCareer->SetAttribute("comment", ToUTF8Ptr("职业"));
	if(rElement.LinkEndChild(pElem_eCareer.get()) != NULL)
		pElem_eCareer.release();
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
	unique_ptr<TiXmlElement> pElem_dwBTPoint(new TiXmlElement("UINT32"));
	if(pElem_dwBTPoint == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwBTPoint->SetAttribute("name", "dwBTPoint");
	pElem_dwBTPoint->SetAttribute("value", NumberToString(s.dwBTPoint).c_str());
	pElem_dwBTPoint->SetAttribute("comment", ToUTF8Ptr("战斗力"));
	if(rElement.LinkEndChild(pElem_dwBTPoint.get()) != NULL)
		pElem_dwBTPoint.release();
	unique_ptr<TiXmlElement> pElem_vecAttr(new TiXmlElement("ProtoCommon::TVecFtAttrMod"));
	if(pElem_vecAttr == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecAttr->SetAttribute("name", "vecAttr");
	if(!NProtoCommon::VectorToXML(s.vecAttr, *pElem_vecAttr))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecAttr->SetAttribute("comment", ToUTF8Ptr("总属性"));
	if(rElement.LinkEndChild(pElem_vecAttr.get()) != NULL)
		pElem_vecAttr.release();
	unique_ptr<TiXmlElement> pElem_vecBattleFighter(new TiXmlElement("TVecBattleFighterData"));
	if(pElem_vecBattleFighter == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecBattleFighter->SetAttribute("name", "vecBattleFighter");
	if(!VectorToXML(s.vecBattleFighter, *pElem_vecBattleFighter))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecBattleFighter->SetAttribute("comment", ToUTF8Ptr("出战的散仙"));
	if(rElement.LinkEndChild(pElem_vecBattleFighter.get()) != NULL)
		pElem_vecBattleFighter.release();
	unique_ptr<TiXmlElement> pElem_sDujie(new TiXmlElement("SDujieData"));
	if(pElem_sDujie == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_sDujie->SetAttribute("name", "sDujie");
	if(!ToXML(s.sDujie, *pElem_sDujie))
	{
		LOG_CRI << "sDujie ToXML fails!";
		return false;
	}
	pElem_sDujie->SetAttribute("comment", ToUTF8Ptr("渡劫"));
	if(rElement.LinkEndChild(pElem_sDujie.get()) != NULL)
		pElem_sDujie.release();
	unique_ptr<TiXmlElement> pElem_sCuiTi(new TiXmlElement("SCTData"));
	if(pElem_sCuiTi == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_sCuiTi->SetAttribute("name", "sCuiTi");
	if(!ToXML(s.sCuiTi, *pElem_sCuiTi))
	{
		LOG_CRI << "sCuiTi ToXML fails!";
		return false;
	}
	pElem_sCuiTi->SetAttribute("comment", ToUTF8Ptr("淬体(装备)"));
	if(rElement.LinkEndChild(pElem_sCuiTi.get()) != NULL)
		pElem_sCuiTi.release();
	unique_ptr<TiXmlElement> pElem_vecBaoshi(new TiXmlElement("TVecUINT32"));
	if(pElem_vecBaoshi == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecBaoshi->SetAttribute("name", "vecBaoshi");
	string strText_vecBaoshi;
	for(size_t i = 0; i < s.vecBaoshi.size(); ++i)
	{
		if(i > 0)
			strText_vecBaoshi += ", ";
		strText_vecBaoshi += NumberToString(s.vecBaoshi[i]);
	}
	unique_ptr<TiXmlText> pText_vecBaoshi(new TiXmlText(strText_vecBaoshi.c_str()));
	if(pText_vecBaoshi == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(pElem_vecBaoshi->LinkEndChild(pText_vecBaoshi.get()) != NULL)
		pText_vecBaoshi.release();
	pElem_vecBaoshi->SetAttribute("comment", ToUTF8Ptr("宝石"));
	if(rElement.LinkEndChild(pElem_vecBaoshi.get()) != NULL)
		pElem_vecBaoshi.release();
	unique_ptr<TiXmlElement> pElem_vecCitta(new TiXmlElement("TVecCittaData"));
	if(pElem_vecCitta == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecCitta->SetAttribute("name", "vecCitta");
	if(!VectorToXML(s.vecCitta, *pElem_vecCitta))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecCitta->SetAttribute("comment", ToUTF8Ptr("心法"));
	if(rElement.LinkEndChild(pElem_vecCitta.get()) != NULL)
		pElem_vecCitta.release();
	unique_ptr<TiXmlElement> pElem_vecTrump(new TiXmlElement("ItemProt::TVecEquipTrump"));
	if(pElem_vecTrump == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecTrump->SetAttribute("name", "vecTrump");
	if(!NItemProt::VectorToXML(s.vecTrump, *pElem_vecTrump))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecTrump->SetAttribute("comment", ToUTF8Ptr("法宝"));
	if(rElement.LinkEndChild(pElem_vecTrump.get()) != NULL)
		pElem_vecTrump.release();
	unique_ptr<TiXmlElement> pElem_vecRareTrump(new TiXmlElement("TVecRareTrumpData"));
	if(pElem_vecRareTrump == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecRareTrump->SetAttribute("name", "vecRareTrump");
	if(!VectorToXML(s.vecRareTrump, *pElem_vecRareTrump))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecRareTrump->SetAttribute("comment", ToUTF8Ptr("稀有(被动）法宝"));
	if(rElement.LinkEndChild(pElem_vecRareTrump.get()) != NULL)
		pElem_vecRareTrump.release();
	unique_ptr<TiXmlElement> pElem_sBeauty(new TiXmlElement("SBeautyData"));
	if(pElem_sBeauty == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_sBeauty->SetAttribute("name", "sBeauty");
	if(!ToXML(s.sBeauty, *pElem_sBeauty))
	{
		LOG_CRI << "sBeauty ToXML fails!";
		return false;
	}
	pElem_sBeauty->SetAttribute("comment", ToUTF8Ptr("美女"));
	if(rElement.LinkEndChild(pElem_sBeauty.get()) != NULL)
		pElem_sBeauty.release();
	unique_ptr<TiXmlElement> pElem_sBeastSoul(new TiXmlElement("SBeastSoulData"));
	if(pElem_sBeastSoul == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_sBeastSoul->SetAttribute("name", "sBeastSoul");
	if(!ToXML(s.sBeastSoul, *pElem_sBeastSoul))
	{
		LOG_CRI << "sBeastSoul ToXML fails!";
		return false;
	}
	pElem_sBeastSoul->SetAttribute("comment", ToUTF8Ptr("魂魄"));
	if(rElement.LinkEndChild(pElem_sBeastSoul.get()) != NULL)
		pElem_sBeastSoul.release();
	unique_ptr<TiXmlElement> pElem_vecComb(new TiXmlElement("TVecCombData"));
	if(pElem_vecComb == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecComb->SetAttribute("name", "vecComb");
	if(!VectorToXML(s.vecComb, *pElem_vecComb))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecComb->SetAttribute("comment", ToUTF8Ptr("组合"));
	if(rElement.LinkEndChild(pElem_vecComb.get()) != NULL)
		pElem_vecComb.release();
	unique_ptr<TiXmlElement> pElem_vecSkill(new TiXmlElement("TVecSkillData"));
	if(pElem_vecSkill == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecSkill->SetAttribute("name", "vecSkill");
	if(!VectorToXML(s.vecSkill, *pElem_vecSkill))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecSkill->SetAttribute("comment", ToUTF8Ptr("技能"));
	if(rElement.LinkEndChild(pElem_vecSkill.get()) != NULL)
		pElem_vecSkill.release();
	unique_ptr<TiXmlElement> pElem_vecHorse(new TiXmlElement("TVecHorseData"));
	if(pElem_vecHorse == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecHorse->SetAttribute("name", "vecHorse");
	if(!VectorToXML(s.vecHorse, *pElem_vecHorse))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecHorse->SetAttribute("comment", ToUTF8Ptr("坐骑"));
	if(rElement.LinkEndChild(pElem_vecHorse.get()) != NULL)
		pElem_vecHorse.release();
	unique_ptr<TiXmlElement> pElem_vecFashion(new TiXmlElement("TVecFashionData"));
	if(pElem_vecFashion == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecFashion->SetAttribute("name", "vecFashion");
	if(!VectorToXML(s.vecFashion, *pElem_vecFashion))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecFashion->SetAttribute("comment", ToUTF8Ptr("已激活的时装"));
	if(rElement.LinkEndChild(pElem_vecFashion.get()) != NULL)
		pElem_vecFashion.release();
	unique_ptr<TiXmlElement> pElem_vecTitle(new TiXmlElement("TVecTitleData"));
	if(pElem_vecTitle == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecTitle->SetAttribute("name", "vecTitle");
	if(!VectorToXML(s.vecTitle, *pElem_vecTitle))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecTitle->SetAttribute("comment", ToUTF8Ptr("已激活的称号"));
	if(rElement.LinkEndChild(pElem_vecTitle.get()) != NULL)
		pElem_vecTitle.release();
	unique_ptr<TiXmlElement> pElem_vecGuild(new TiXmlElement("TVecGuildData"));
	if(pElem_vecGuild == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecGuild->SetAttribute("name", "vecGuild");
	if(!VectorToXML(s.vecGuild, *pElem_vecGuild))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecGuild->SetAttribute("comment", ToUTF8Ptr("帮派"));
	if(rElement.LinkEndChild(pElem_vecGuild.get()) != NULL)
		pElem_vecGuild.release();
	unique_ptr<TiXmlElement> pElem_vecTianBookAttr(new TiXmlElement("ProtoCommon::TVecFtAttrMod"));
	if(pElem_vecTianBookAttr == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecTianBookAttr->SetAttribute("name", "vecTianBookAttr");
	if(!NProtoCommon::VectorToXML(s.vecTianBookAttr, *pElem_vecTianBookAttr))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecTianBookAttr->SetAttribute("comment", ToUTF8Ptr("天书属性"));
	if(rElement.LinkEndChild(pElem_vecTianBookAttr.get()) != NULL)
		pElem_vecTianBookAttr.release();
	return true;
}

#endif

SFighterData::SFighterData() : wFighterID(0), byLevel(0), dwBTPoint(0) { }

SFighterData::SFighterData(UINT16 wFighterID_, UINT8 byLevel_, UINT32 dwBTPoint_, const NProtoCommon::TVecFtAttrMod& vecAttr_, const SDujieData& sDujie_, 
			const TVecSkillData& vecSkill_, const SCTData& sCuiTi_, const TVecUINT32& vecBaoshi_, const TVecCittaData& vecCitta_, const NItemProt::TVecEquipTrump& vecTrump_)
			: wFighterID(wFighterID_), byLevel(byLevel_), dwBTPoint(dwBTPoint_), vecAttr(vecAttr_), sDujie(sDujie_), 
			vecSkill(vecSkill_), sCuiTi(sCuiTi_), vecBaoshi(vecBaoshi_), vecCitta(vecCitta_), vecTrump(vecTrump_) { }

SFighterData::SFighterData(SFighterData&& src) : wFighterID(src.wFighterID), byLevel(src.byLevel), dwBTPoint(src.dwBTPoint), vecAttr(move(src.vecAttr)), sDujie(src.sDujie), 
			vecSkill(move(src.vecSkill)), sCuiTi(src.sCuiTi), vecBaoshi(src.vecBaoshi), vecCitta(move(src.vecCitta)), vecTrump(move(src.vecTrump)) { }

SFighterData& SFighterData::operator=(SFighterData&& rhs)
{
	if(this != &rhs)
	{
		this->~SFighterData();
		new (this) SFighterData(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SFighterData& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.wFighterID;
	src >> s.byLevel;
	src >> s.dwBTPoint;
	src >> s.vecAttr;
	src >> s.sDujie;
	src >> s.vecSkill;
	src >> s.sCuiTi;
	src >> s.vecBaoshi;
	src >> s.vecCitta;
	src >> s.vecTrump;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SFighterData& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.wFighterID;
	src << s.byLevel;
	src << s.dwBTPoint;
	src << s.vecAttr;
	src << s.sDujie;
	src << s.vecSkill;
	src << s.sCuiTi;
	src << s.vecBaoshi;
	src << s.vecCitta;
	src << s.vecTrump;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SFighterData& s)
{
	if(strcmp(rElement.Value(), "SFighterData") != 0)
	{
		LOG_CRI << "rElement is not SFighterData!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wFighterID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wFighterID") != 0)
	{
		LOG_CRI << "Attribute: name is not wFighterID!";
		return false;
	}
	const char* pszVal_wFighterID = pElemChild->Attribute("value");
	if(pszVal_wFighterID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wFighterID, s.wFighterID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
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
		LOG_CRI << "pElemChild for dwBTPoint is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwBTPoint") != 0)
	{
		LOG_CRI << "Attribute: name is not dwBTPoint!";
		return false;
	}
	const char* pszVal_dwBTPoint = pElemChild->Attribute("value");
	if(pszVal_dwBTPoint == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwBTPoint, s.dwBTPoint))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecAttr is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "ProtoCommon::TVecFtAttrMod") != 0)
	{
		LOG_CRI << "pElemChild is not ProtoCommon::TVecFtAttrMod!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecAttr") != 0)
	{
		LOG_CRI << "Attribute: name is not vecAttr!";
		return false;
	}
	if(!NProtoCommon::VectorFromXML(*pElemChild, s.vecAttr))
	{
		LOG_CRI << "VectorFromXML for vecAttr fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for sDujie is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "SDujieData") != 0)
	{
		LOG_CRI << "pElemChild is not SDujieData!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "sDujie") != 0)
	{
		LOG_CRI << "Attribute: name is not sDujie!";
		return false;
	}
	if(!FromXML(*pElemChild, s.sDujie))
	{
		LOG_CRI << "FromXML for: sDujie fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecSkill is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecSkillData") != 0)
	{
		LOG_CRI << "pElemChild is not TVecSkillData!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecSkill") != 0)
	{
		LOG_CRI << "Attribute: name is not vecSkill!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecSkill))
	{
		LOG_CRI << "VectorFromXML for vecSkill fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for sCuiTi is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "SCTData") != 0)
	{
		LOG_CRI << "pElemChild is not SCTData!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "sCuiTi") != 0)
	{
		LOG_CRI << "Attribute: name is not sCuiTi!";
		return false;
	}
	if(!FromXML(*pElemChild, s.sCuiTi))
	{
		LOG_CRI << "FromXML for: sCuiTi fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecBaoshi is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecUINT32") != 0)
	{
		LOG_CRI << "pElemChild is not TVecUINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecBaoshi") != 0)
	{
		LOG_CRI << "Attribute: name is not vecBaoshi!";
		return false;
	}
	const char* pszText_vecBaoshi = pElemChild->GetText();
	if(pszText_vecBaoshi != NULL)
		SplitToNumber(pszText_vecBaoshi, ",", s.vecBaoshi);
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecCitta is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecCittaData") != 0)
	{
		LOG_CRI << "pElemChild is not TVecCittaData!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecCitta") != 0)
	{
		LOG_CRI << "Attribute: name is not vecCitta!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecCitta))
	{
		LOG_CRI << "VectorFromXML for vecCitta fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecTrump is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "ItemProt::TVecEquipTrump") != 0)
	{
		LOG_CRI << "pElemChild is not ItemProt::TVecEquipTrump!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecTrump") != 0)
	{
		LOG_CRI << "Attribute: name is not vecTrump!";
		return false;
	}
	if(!NItemProt::VectorFromXML(*pElemChild, s.vecTrump))
	{
		LOG_CRI << "VectorFromXML for vecTrump fails!";
		return false;
	}
	return true;
}

bool ToXML(const SFighterData& s, TiXmlElement& rElement)
{
	rElement.SetValue("SFighterData");
	rElement.SetAttribute("type", ToUTF8Ptr("散仙信息"));
	unique_ptr<TiXmlElement> pElem_wFighterID(new TiXmlElement("UINT16"));
	if(pElem_wFighterID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wFighterID->SetAttribute("name", "wFighterID");
	pElem_wFighterID->SetAttribute("value", NumberToString(s.wFighterID).c_str());
	pElem_wFighterID->SetAttribute("comment", ToUTF8Ptr("散仙模版"));
	if(rElement.LinkEndChild(pElem_wFighterID.get()) != NULL)
		pElem_wFighterID.release();
	unique_ptr<TiXmlElement> pElem_byLevel(new TiXmlElement("UINT8"));
	if(pElem_byLevel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byLevel->SetAttribute("name", "byLevel");
	pElem_byLevel->SetAttribute("value", NumberToString(s.byLevel).c_str());
	pElem_byLevel->SetAttribute("comment", ToUTF8Ptr("散仙等级"));
	if(rElement.LinkEndChild(pElem_byLevel.get()) != NULL)
		pElem_byLevel.release();
	unique_ptr<TiXmlElement> pElem_dwBTPoint(new TiXmlElement("UINT32"));
	if(pElem_dwBTPoint == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwBTPoint->SetAttribute("name", "dwBTPoint");
	pElem_dwBTPoint->SetAttribute("value", NumberToString(s.dwBTPoint).c_str());
	pElem_dwBTPoint->SetAttribute("comment", ToUTF8Ptr("战斗力"));
	if(rElement.LinkEndChild(pElem_dwBTPoint.get()) != NULL)
		pElem_dwBTPoint.release();
	unique_ptr<TiXmlElement> pElem_vecAttr(new TiXmlElement("ProtoCommon::TVecFtAttrMod"));
	if(pElem_vecAttr == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecAttr->SetAttribute("name", "vecAttr");
	if(!NProtoCommon::VectorToXML(s.vecAttr, *pElem_vecAttr))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecAttr->SetAttribute("comment", ToUTF8Ptr("将属性"));
	if(rElement.LinkEndChild(pElem_vecAttr.get()) != NULL)
		pElem_vecAttr.release();
	unique_ptr<TiXmlElement> pElem_sDujie(new TiXmlElement("SDujieData"));
	if(pElem_sDujie == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_sDujie->SetAttribute("name", "sDujie");
	if(!ToXML(s.sDujie, *pElem_sDujie))
	{
		LOG_CRI << "sDujie ToXML fails!";
		return false;
	}
	pElem_sDujie->SetAttribute("comment", ToUTF8Ptr("渡劫"));
	if(rElement.LinkEndChild(pElem_sDujie.get()) != NULL)
		pElem_sDujie.release();
	unique_ptr<TiXmlElement> pElem_vecSkill(new TiXmlElement("TVecSkillData"));
	if(pElem_vecSkill == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecSkill->SetAttribute("name", "vecSkill");
	if(!VectorToXML(s.vecSkill, *pElem_vecSkill))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecSkill->SetAttribute("comment", ToUTF8Ptr("技能"));
	if(rElement.LinkEndChild(pElem_vecSkill.get()) != NULL)
		pElem_vecSkill.release();
	unique_ptr<TiXmlElement> pElem_sCuiTi(new TiXmlElement("SCTData"));
	if(pElem_sCuiTi == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_sCuiTi->SetAttribute("name", "sCuiTi");
	if(!ToXML(s.sCuiTi, *pElem_sCuiTi))
	{
		LOG_CRI << "sCuiTi ToXML fails!";
		return false;
	}
	pElem_sCuiTi->SetAttribute("comment", ToUTF8Ptr("淬体"));
	if(rElement.LinkEndChild(pElem_sCuiTi.get()) != NULL)
		pElem_sCuiTi.release();
	unique_ptr<TiXmlElement> pElem_vecBaoshi(new TiXmlElement("TVecUINT32"));
	if(pElem_vecBaoshi == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecBaoshi->SetAttribute("name", "vecBaoshi");
	string strText_vecBaoshi;
	for(size_t i = 0; i < s.vecBaoshi.size(); ++i)
	{
		if(i > 0)
			strText_vecBaoshi += ", ";
		strText_vecBaoshi += NumberToString(s.vecBaoshi[i]);
	}
	unique_ptr<TiXmlText> pText_vecBaoshi(new TiXmlText(strText_vecBaoshi.c_str()));
	if(pText_vecBaoshi == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(pElem_vecBaoshi->LinkEndChild(pText_vecBaoshi.get()) != NULL)
		pText_vecBaoshi.release();
	pElem_vecBaoshi->SetAttribute("comment", ToUTF8Ptr("宝石"));
	if(rElement.LinkEndChild(pElem_vecBaoshi.get()) != NULL)
		pElem_vecBaoshi.release();
	unique_ptr<TiXmlElement> pElem_vecCitta(new TiXmlElement("TVecCittaData"));
	if(pElem_vecCitta == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecCitta->SetAttribute("name", "vecCitta");
	if(!VectorToXML(s.vecCitta, *pElem_vecCitta))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecCitta->SetAttribute("comment", ToUTF8Ptr("心法"));
	if(rElement.LinkEndChild(pElem_vecCitta.get()) != NULL)
		pElem_vecCitta.release();
	unique_ptr<TiXmlElement> pElem_vecTrump(new TiXmlElement("ItemProt::TVecEquipTrump"));
	if(pElem_vecTrump == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecTrump->SetAttribute("name", "vecTrump");
	if(!NItemProt::VectorToXML(s.vecTrump, *pElem_vecTrump))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecTrump->SetAttribute("comment", ToUTF8Ptr("法宝"));
	if(rElement.LinkEndChild(pElem_vecTrump.get()) != NULL)
		pElem_vecTrump.release();
	return true;
}

#endif

} //namespace NViewInfoProt
