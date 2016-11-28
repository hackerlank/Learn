/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    TripodProt.cpp
//  Purpose:      九疑鼎相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "TripodProt.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NTripodProt
{

#ifdef PROT_USE_XML

const char* EnumValToStr(ETripodType e)
{
	switch(e)
	{
	case eTripodSucc:
		return "eTripodSucc";
	case eTripodFailed:
		return "eTripodFailed";
	case eTripodCondIDErr:
		return "eTripodCondIDErr";
	case eTripodItemErr:
		return "eTripodItemErr";
	case eTripodNotFire:
		return "eTripodNotFire";
	case eTripodNoEnoughCnt:
		return "eTripodNoEnoughCnt";
	case eTripodYuanqiNotFull:
		return "eTripodYuanqiNotFull";
	case eTripodYuanqiFull:
		return "eTripodYuanqiFull";
	case eTripodNotTime:
		return "eTripodNotTime";
	case eTripodShanfengFull:
		return "eTripodShanfengFull";
	case eTripodHelpTimesFull:
		return "eTripodHelpTimesFull";
	case eTripodNotHelp:
		return "eTripodNotHelp";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, ETripodType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, ETripodType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eTripodSucc", eTripodSucc));
		mapStr2Val.insert(make_pair("eTripodFailed", eTripodFailed));
		mapStr2Val.insert(make_pair("eTripodCondIDErr", eTripodCondIDErr));
		mapStr2Val.insert(make_pair("eTripodItemErr", eTripodItemErr));
		mapStr2Val.insert(make_pair("eTripodNotFire", eTripodNotFire));
		mapStr2Val.insert(make_pair("eTripodNoEnoughCnt", eTripodNoEnoughCnt));
		mapStr2Val.insert(make_pair("eTripodYuanqiNotFull", eTripodYuanqiNotFull));
		mapStr2Val.insert(make_pair("eTripodYuanqiFull", eTripodYuanqiFull));
		mapStr2Val.insert(make_pair("eTripodNotTime", eTripodNotTime));
		mapStr2Val.insert(make_pair("eTripodShanfengFull", eTripodShanfengFull));
		mapStr2Val.insert(make_pair("eTripodHelpTimesFull", eTripodHelpTimesFull));
		mapStr2Val.insert(make_pair("eTripodNotHelp", eTripodNotHelp));
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

const char* EnumValToStr(ETripodLogType e)
{
	switch(e)
	{
	case eTripodLogNone:
		return "eTripodLogNone";
	case eTripodLogHelp:
		return "eTripodLogHelp";
	case eTripodLogMax:
		return "eTripodLogMax";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, ETripodLogType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, ETripodLogType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eTripodLogNone", eTripodLogNone));
		mapStr2Val.insert(make_pair("eTripodLogHelp", eTripodLogHelp));
		mapStr2Val.insert(make_pair("eTripodLogMax", eTripodLogMax));
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

STripodInfo::STripodInfo() : byTripodID(0), byLevel(0), dwExp(0), wFireID(0), byFireLvl(0), 
			dwStartTime(0), dwShanfengTime(0), dwSoul(0), dwLine(0) { }

STripodInfo::STripodInfo(UINT8 byTripodID_, UINT8 byLevel_, UINT32 dwExp_, UINT16 wFireID_, UINT8 byFireLvl_, 
			UINT32 dwStartTime_, UINT32 dwShanfengTime_, UINT32 dwSoul_, UINT32 dwLine_)
			: byTripodID(byTripodID_), byLevel(byLevel_), dwExp(dwExp_), wFireID(wFireID_), byFireLvl(byFireLvl_), 
			dwStartTime(dwStartTime_), dwShanfengTime(dwShanfengTime_), dwSoul(dwSoul_), dwLine(dwLine_) { }

CInArchive& operator>>(CInArchive& src, STripodInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.byTripodID;
	src >> s.byLevel;
	src >> s.dwExp;
	src >> s.wFireID;
	src >> s.byFireLvl;
	src >> s.dwStartTime;
	src >> s.dwShanfengTime;
	src >> s.dwSoul;
	src >> s.dwLine;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const STripodInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.byTripodID;
	src << s.byLevel;
	src << s.dwExp;
	src << s.wFireID;
	src << s.byFireLvl;
	src << s.dwStartTime;
	src << s.dwShanfengTime;
	src << s.dwSoul;
	src << s.dwLine;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, STripodInfo& s)
{
	if(strcmp(rElement.Value(), "STripodInfo") != 0)
	{
		LOG_CRI << "rElement is not STripodInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byTripodID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byTripodID") != 0)
	{
		LOG_CRI << "Attribute: name is not byTripodID!";
		return false;
	}
	const char* pszVal_byTripodID = pElemChild->Attribute("value");
	if(pszVal_byTripodID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byTripodID, s.byTripodID))
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
		LOG_CRI << "pElemChild for dwExp is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwExp") != 0)
	{
		LOG_CRI << "Attribute: name is not dwExp!";
		return false;
	}
	const char* pszVal_dwExp = pElemChild->Attribute("value");
	if(pszVal_dwExp == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwExp, s.dwExp))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wFireID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wFireID") != 0)
	{
		LOG_CRI << "Attribute: name is not wFireID!";
		return false;
	}
	const char* pszVal_wFireID = pElemChild->Attribute("value");
	if(pszVal_wFireID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wFireID, s.wFireID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byFireLvl is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byFireLvl") != 0)
	{
		LOG_CRI << "Attribute: name is not byFireLvl!";
		return false;
	}
	const char* pszVal_byFireLvl = pElemChild->Attribute("value");
	if(pszVal_byFireLvl == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byFireLvl, s.byFireLvl))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwStartTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwStartTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwStartTime!";
		return false;
	}
	const char* pszVal_dwStartTime = pElemChild->Attribute("value");
	if(pszVal_dwStartTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwStartTime, s.dwStartTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwShanfengTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwShanfengTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwShanfengTime!";
		return false;
	}
	const char* pszVal_dwShanfengTime = pElemChild->Attribute("value");
	if(pszVal_dwShanfengTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwShanfengTime, s.dwShanfengTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwSoul is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwSoul") != 0)
	{
		LOG_CRI << "Attribute: name is not dwSoul!";
		return false;
	}
	const char* pszVal_dwSoul = pElemChild->Attribute("value");
	if(pszVal_dwSoul == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwSoul, s.dwSoul))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwLine is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwLine") != 0)
	{
		LOG_CRI << "Attribute: name is not dwLine!";
		return false;
	}
	const char* pszVal_dwLine = pElemChild->Attribute("value");
	if(pszVal_dwLine == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwLine, s.dwLine))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const STripodInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("STripodInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("玩家的九疑鼎数据"));
	unique_ptr<TiXmlElement> pElem_byTripodID(new TiXmlElement("UINT8"));
	if(pElem_byTripodID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byTripodID->SetAttribute("name", "byTripodID");
	pElem_byTripodID->SetAttribute("value", NumberToString(s.byTripodID).c_str());
	pElem_byTripodID->SetAttribute("comment", ToUTF8Ptr("九疑鼎ID"));
	if(rElement.LinkEndChild(pElem_byTripodID.get()) != NULL)
		pElem_byTripodID.release();
	unique_ptr<TiXmlElement> pElem_byLevel(new TiXmlElement("UINT8"));
	if(pElem_byLevel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byLevel->SetAttribute("name", "byLevel");
	pElem_byLevel->SetAttribute("value", NumberToString(s.byLevel).c_str());
	pElem_byLevel->SetAttribute("comment", ToUTF8Ptr("九疑鼎等级"));
	if(rElement.LinkEndChild(pElem_byLevel.get()) != NULL)
		pElem_byLevel.release();
	unique_ptr<TiXmlElement> pElem_dwExp(new TiXmlElement("UINT32"));
	if(pElem_dwExp == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwExp->SetAttribute("name", "dwExp");
	pElem_dwExp->SetAttribute("value", NumberToString(s.dwExp).c_str());
	pElem_dwExp->SetAttribute("comment", ToUTF8Ptr("九疑鼎当前经验值"));
	if(rElement.LinkEndChild(pElem_dwExp.get()) != NULL)
		pElem_dwExp.release();
	unique_ptr<TiXmlElement> pElem_wFireID(new TiXmlElement("UINT16"));
	if(pElem_wFireID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wFireID->SetAttribute("name", "wFireID");
	pElem_wFireID->SetAttribute("value", NumberToString(s.wFireID).c_str());
	pElem_wFireID->SetAttribute("comment", ToUTF8Ptr("火种ID"));
	if(rElement.LinkEndChild(pElem_wFireID.get()) != NULL)
		pElem_wFireID.release();
	unique_ptr<TiXmlElement> pElem_byFireLvl(new TiXmlElement("UINT8"));
	if(pElem_byFireLvl == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byFireLvl->SetAttribute("name", "byFireLvl");
	pElem_byFireLvl->SetAttribute("value", NumberToString(s.byFireLvl).c_str());
	pElem_byFireLvl->SetAttribute("comment", ToUTF8Ptr("火种等级(品质)"));
	if(rElement.LinkEndChild(pElem_byFireLvl.get()) != NULL)
		pElem_byFireLvl.release();
	unique_ptr<TiXmlElement> pElem_dwStartTime(new TiXmlElement("UINT32"));
	if(pElem_dwStartTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwStartTime->SetAttribute("name", "dwStartTime");
	pElem_dwStartTime->SetAttribute("value", NumberToString(s.dwStartTime).c_str());
	pElem_dwStartTime->SetAttribute("comment", ToUTF8Ptr("上一次结算时间"));
	if(rElement.LinkEndChild(pElem_dwStartTime.get()) != NULL)
		pElem_dwStartTime.release();
	unique_ptr<TiXmlElement> pElem_dwShanfengTime(new TiXmlElement("UINT32"));
	if(pElem_dwShanfengTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwShanfengTime->SetAttribute("name", "dwShanfengTime");
	pElem_dwShanfengTime->SetAttribute("value", NumberToString(s.dwShanfengTime).c_str());
	pElem_dwShanfengTime->SetAttribute("comment", ToUTF8Ptr("上一次扇风时间(为0未扇风)"));
	if(rElement.LinkEndChild(pElem_dwShanfengTime.get()) != NULL)
		pElem_dwShanfengTime.release();
	unique_ptr<TiXmlElement> pElem_dwSoul(new TiXmlElement("UINT32"));
	if(pElem_dwSoul == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwSoul->SetAttribute("name", "dwSoul");
	pElem_dwSoul->SetAttribute("value", NumberToString(s.dwSoul).c_str());
	pElem_dwSoul->SetAttribute("comment", ToUTF8Ptr("当前已结算的总元气值"));
	if(rElement.LinkEndChild(pElem_dwSoul.get()) != NULL)
		pElem_dwSoul.release();
	unique_ptr<TiXmlElement> pElem_dwLine(new TiXmlElement("UINT32"));
	if(pElem_dwLine == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwLine->SetAttribute("name", "dwLine");
	pElem_dwLine->SetAttribute("value", NumberToString(s.dwLine).c_str());
	pElem_dwLine->SetAttribute("comment", ToUTF8Ptr("产物加成系数（万分比）"));
	if(rElement.LinkEndChild(pElem_dwLine.get()) != NULL)
		pElem_dwLine.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecTripodInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		STripodInfo s;
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

bool VectorToXML(const TVecTripodInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("STripodInfo"));
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

SFighterHelpInfo::SFighterHelpInfo() : wFighterID(0), byPos(0), byColor(0), dwStartTime(0) { }

SFighterHelpInfo::SFighterHelpInfo(UINT16 wFighterID_, UINT8 byPos_, UINT8 byColor_, UINT32 dwStartTime_) : wFighterID(wFighterID_), byPos(byPos_), byColor(byColor_), dwStartTime(dwStartTime_) { }

CInArchive& operator>>(CInArchive& src, SFighterHelpInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.wFighterID;
	src >> s.byPos;
	src >> s.byColor;
	src >> s.dwStartTime;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SFighterHelpInfo& s)
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
	src << s.byPos;
	src << s.byColor;
	src << s.dwStartTime;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SFighterHelpInfo& s)
{
	if(strcmp(rElement.Value(), "SFighterHelpInfo") != 0)
	{
		LOG_CRI << "rElement is not SFighterHelpInfo!";
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
		LOG_CRI << "pElemChild for byPos is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
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
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byColor is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byColor") != 0)
	{
		LOG_CRI << "Attribute: name is not byColor!";
		return false;
	}
	const char* pszVal_byColor = pElemChild->Attribute("value");
	if(pszVal_byColor == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byColor, s.byColor))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwStartTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwStartTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwStartTime!";
		return false;
	}
	const char* pszVal_dwStartTime = pElemChild->Attribute("value");
	if(pszVal_dwStartTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwStartTime, s.dwStartTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SFighterHelpInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SFighterHelpInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("九疑鼎散仙协助"));
	unique_ptr<TiXmlElement> pElem_wFighterID(new TiXmlElement("UINT16"));
	if(pElem_wFighterID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wFighterID->SetAttribute("name", "wFighterID");
	pElem_wFighterID->SetAttribute("value", NumberToString(s.wFighterID).c_str());
	pElem_wFighterID->SetAttribute("comment", ToUTF8Ptr("散仙ID"));
	if(rElement.LinkEndChild(pElem_wFighterID.get()) != NULL)
		pElem_wFighterID.release();
	unique_ptr<TiXmlElement> pElem_byPos(new TiXmlElement("UINT8"));
	if(pElem_byPos == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byPos->SetAttribute("name", "byPos");
	pElem_byPos->SetAttribute("value", NumberToString(s.byPos).c_str());
	pElem_byPos->SetAttribute("comment", ToUTF8Ptr("协助位置(0,1)"));
	if(rElement.LinkEndChild(pElem_byPos.get()) != NULL)
		pElem_byPos.release();
	unique_ptr<TiXmlElement> pElem_byColor(new TiXmlElement("UINT8"));
	if(pElem_byColor == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byColor->SetAttribute("name", "byColor");
	pElem_byColor->SetAttribute("value", NumberToString(s.byColor).c_str());
	pElem_byColor->SetAttribute("comment", ToUTF8Ptr("散仙协助时的品质"));
	if(rElement.LinkEndChild(pElem_byColor.get()) != NULL)
		pElem_byColor.release();
	unique_ptr<TiXmlElement> pElem_dwStartTime(new TiXmlElement("UINT32"));
	if(pElem_dwStartTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwStartTime->SetAttribute("name", "dwStartTime");
	pElem_dwStartTime->SetAttribute("value", NumberToString(s.dwStartTime).c_str());
	pElem_dwStartTime->SetAttribute("comment", ToUTF8Ptr("开始协助的时间"));
	if(rElement.LinkEndChild(pElem_dwStartTime.get()) != NULL)
		pElem_dwStartTime.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecFighterHelpInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SFighterHelpInfo s;
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

bool VectorToXML(const TVecFighterHelpInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SFighterHelpInfo"));
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

SPlayerHelpInfo::SPlayerHelpInfo() : qwRoleID(0), byPos(0), byLevel(0), dwStartTime(0) { }

SPlayerHelpInfo::SPlayerHelpInfo(UINT64 qwRoleID_, UINT8 byPos_, UINT8 byLevel_, UINT32 dwStartTime_, const NArenaGS::SArenaFighter& stPlayer_, 
			const NProtoCommon::TVecPlatformParam& vecPlatforms_)
			: qwRoleID(qwRoleID_), byPos(byPos_), byLevel(byLevel_), dwStartTime(dwStartTime_), stPlayer(stPlayer_), 
			vecPlatforms(vecPlatforms_) { }

SPlayerHelpInfo::SPlayerHelpInfo(SPlayerHelpInfo&& src) : qwRoleID(src.qwRoleID), byPos(src.byPos), byLevel(src.byLevel), dwStartTime(src.dwStartTime), stPlayer(move(src.stPlayer)), 
			vecPlatforms(move(src.vecPlatforms)) { }

SPlayerHelpInfo& SPlayerHelpInfo::operator=(SPlayerHelpInfo&& rhs)
{
	if(this != &rhs)
	{
		this->~SPlayerHelpInfo();
		new (this) SPlayerHelpInfo(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SPlayerHelpInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwRoleID;
	src >> s.byPos;
	src >> s.byLevel;
	src >> s.dwStartTime;
	src >> s.stPlayer;
	src >> s.vecPlatforms;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SPlayerHelpInfo& s)
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
	src << s.byPos;
	src << s.byLevel;
	src << s.dwStartTime;
	src << s.stPlayer;
	src << s.vecPlatforms;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SPlayerHelpInfo& s)
{
	if(strcmp(rElement.Value(), "SPlayerHelpInfo") != 0)
	{
		LOG_CRI << "rElement is not SPlayerHelpInfo!";
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
		LOG_CRI << "pElemChild for byPos is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
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
		LOG_CRI << "pElemChild for dwStartTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwStartTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwStartTime!";
		return false;
	}
	const char* pszVal_dwStartTime = pElemChild->Attribute("value");
	if(pszVal_dwStartTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwStartTime, s.dwStartTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for stPlayer is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "ArenaGS::SArenaFighter") != 0)
	{
		LOG_CRI << "pElemChild is not ArenaGS::SArenaFighter!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "stPlayer") != 0)
	{
		LOG_CRI << "Attribute: name is not stPlayer!";
		return false;
	}
	if(!FromXML(*pElemChild, s.stPlayer))
	{
		LOG_CRI << "FromXML for: stPlayer fails!";
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

bool ToXML(const SPlayerHelpInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SPlayerHelpInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("九疑鼎玩家协助"));
	unique_ptr<TiXmlElement> pElem_qwRoleID(new TiXmlElement("UINT64"));
	if(pElem_qwRoleID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwRoleID->SetAttribute("name", "qwRoleID");
	pElem_qwRoleID->SetAttribute("value", NumberToString(s.qwRoleID).c_str());
	pElem_qwRoleID->SetAttribute("comment", ToUTF8Ptr("协助者(玩家)ID"));
	if(rElement.LinkEndChild(pElem_qwRoleID.get()) != NULL)
		pElem_qwRoleID.release();
	unique_ptr<TiXmlElement> pElem_byPos(new TiXmlElement("UINT8"));
	if(pElem_byPos == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byPos->SetAttribute("name", "byPos");
	pElem_byPos->SetAttribute("value", NumberToString(s.byPos).c_str());
	pElem_byPos->SetAttribute("comment", ToUTF8Ptr("协助位置(0,1,2)"));
	if(rElement.LinkEndChild(pElem_byPos.get()) != NULL)
		pElem_byPos.release();
	unique_ptr<TiXmlElement> pElem_byLevel(new TiXmlElement("UINT8"));
	if(pElem_byLevel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byLevel->SetAttribute("name", "byLevel");
	pElem_byLevel->SetAttribute("value", NumberToString(s.byLevel).c_str());
	pElem_byLevel->SetAttribute("comment", ToUTF8Ptr("玩家协助时的等级"));
	if(rElement.LinkEndChild(pElem_byLevel.get()) != NULL)
		pElem_byLevel.release();
	unique_ptr<TiXmlElement> pElem_dwStartTime(new TiXmlElement("UINT32"));
	if(pElem_dwStartTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwStartTime->SetAttribute("name", "dwStartTime");
	pElem_dwStartTime->SetAttribute("value", NumberToString(s.dwStartTime).c_str());
	pElem_dwStartTime->SetAttribute("comment", ToUTF8Ptr("开始协助的时间"));
	if(rElement.LinkEndChild(pElem_dwStartTime.get()) != NULL)
		pElem_dwStartTime.release();
	unique_ptr<TiXmlElement> pElem_stPlayer(new TiXmlElement("ArenaGS::SArenaFighter"));
	if(pElem_stPlayer == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_stPlayer->SetAttribute("name", "stPlayer");
	if(!ToXML(s.stPlayer, *pElem_stPlayer))
	{
		LOG_CRI << "stPlayer ToXML fails!";
		return false;
	}
	pElem_stPlayer->SetAttribute("comment", ToUTF8Ptr("玩家的基础信息(外观)"));
	if(rElement.LinkEndChild(pElem_stPlayer.get()) != NULL)
		pElem_stPlayer.release();
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

bool VectorFromXML(TiXmlElement& rElement, TVecPlayerHelpInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SPlayerHelpInfo s;
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

bool VectorToXML(const TVecPlayerHelpInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SPlayerHelpInfo"));
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

STripodHelp::STripodHelp() : qwRoleID(0) { }

STripodHelp::STripodHelp(UINT64 qwRoleID_, const TVecFighterHelpInfo& vecFighterHelp_, const TVecPlayerHelpInfo& vecPlayerHelp_) : qwRoleID(qwRoleID_), vecFighterHelp(vecFighterHelp_), vecPlayerHelp(vecPlayerHelp_) { }

STripodHelp::STripodHelp(STripodHelp&& src) : qwRoleID(src.qwRoleID), vecFighterHelp(move(src.vecFighterHelp)), vecPlayerHelp(move(src.vecPlayerHelp)) { }

STripodHelp& STripodHelp::operator=(STripodHelp&& rhs)
{
	if(this != &rhs)
	{
		this->~STripodHelp();
		new (this) STripodHelp(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, STripodHelp& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwRoleID;
	src >> s.vecFighterHelp;
	src >> s.vecPlayerHelp;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const STripodHelp& s)
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
	src << s.vecFighterHelp;
	src << s.vecPlayerHelp;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, STripodHelp& s)
{
	if(strcmp(rElement.Value(), "STripodHelp") != 0)
	{
		LOG_CRI << "rElement is not STripodHelp!";
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
		LOG_CRI << "pElemChild for vecFighterHelp is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecFighterHelpInfo") != 0)
	{
		LOG_CRI << "pElemChild is not TVecFighterHelpInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecFighterHelp") != 0)
	{
		LOG_CRI << "Attribute: name is not vecFighterHelp!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecFighterHelp))
	{
		LOG_CRI << "VectorFromXML for vecFighterHelp fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecPlayerHelp is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecPlayerHelpInfo") != 0)
	{
		LOG_CRI << "pElemChild is not TVecPlayerHelpInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecPlayerHelp") != 0)
	{
		LOG_CRI << "Attribute: name is not vecPlayerHelp!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecPlayerHelp))
	{
		LOG_CRI << "VectorFromXML for vecPlayerHelp fails!";
		return false;
	}
	return true;
}

bool ToXML(const STripodHelp& s, TiXmlElement& rElement)
{
	rElement.SetValue("STripodHelp");
	rElement.SetAttribute("type", ToUTF8Ptr("九疑鼎的协助信息"));
	unique_ptr<TiXmlElement> pElem_qwRoleID(new TiXmlElement("UINT64"));
	if(pElem_qwRoleID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwRoleID->SetAttribute("name", "qwRoleID");
	pElem_qwRoleID->SetAttribute("value", NumberToString(s.qwRoleID).c_str());
	pElem_qwRoleID->SetAttribute("comment", ToUTF8Ptr("九疑鼎的所属玩家的ID"));
	if(rElement.LinkEndChild(pElem_qwRoleID.get()) != NULL)
		pElem_qwRoleID.release();
	unique_ptr<TiXmlElement> pElem_vecFighterHelp(new TiXmlElement("TVecFighterHelpInfo"));
	if(pElem_vecFighterHelp == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecFighterHelp->SetAttribute("name", "vecFighterHelp");
	if(!VectorToXML(s.vecFighterHelp, *pElem_vecFighterHelp))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecFighterHelp->SetAttribute("comment", ToUTF8Ptr("散仙协助信息"));
	if(rElement.LinkEndChild(pElem_vecFighterHelp.get()) != NULL)
		pElem_vecFighterHelp.release();
	unique_ptr<TiXmlElement> pElem_vecPlayerHelp(new TiXmlElement("TVecPlayerHelpInfo"));
	if(pElem_vecPlayerHelp == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecPlayerHelp->SetAttribute("name", "vecPlayerHelp");
	if(!VectorToXML(s.vecPlayerHelp, *pElem_vecPlayerHelp))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecPlayerHelp->SetAttribute("comment", ToUTF8Ptr("玩家协助信息"));
	if(rElement.LinkEndChild(pElem_vecPlayerHelp.get()) != NULL)
		pElem_vecPlayerHelp.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecTripodHelp& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		STripodHelp s;
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

bool VectorToXML(const TVecTripodHelp& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("STripodHelp"));
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

STripodLog::STripodLog() : qwRoleID(0), wMsgID(0), dwTime(0) { }

STripodLog::STripodLog(UINT64 qwRoleID_, UINT16 wMsgID_, const TVecINT64& vecParam_, const TVecString& vecString_, UINT32 dwTime_)
			: qwRoleID(qwRoleID_), wMsgID(wMsgID_), vecParam(vecParam_), vecString(vecString_), dwTime(dwTime_) { }

CInArchive& operator>>(CInArchive& src, STripodLog& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwRoleID;
	src >> s.wMsgID;
	src >> s.vecParam;
	src >> s.vecString;
	src >> s.dwTime;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const STripodLog& s)
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
	src << s.wMsgID;
	src << s.vecParam;
	src << s.vecString;
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

bool FromXML(TiXmlElement& rElement, STripodLog& s)
{
	if(strcmp(rElement.Value(), "STripodLog") != 0)
	{
		LOG_CRI << "rElement is not STripodLog!";
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
		LOG_CRI << "pElemChild for wMsgID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wMsgID") != 0)
	{
		LOG_CRI << "Attribute: name is not wMsgID!";
		return false;
	}
	const char* pszVal_wMsgID = pElemChild->Attribute("value");
	if(pszVal_wMsgID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wMsgID, s.wMsgID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecParam is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecINT64") != 0)
	{
		LOG_CRI << "pElemChild is not TVecINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecParam") != 0)
	{
		LOG_CRI << "Attribute: name is not vecParam!";
		return false;
	}
	const char* pszText_vecParam = pElemChild->GetText();
	if(pszText_vecParam != NULL)
		SplitToNumber(pszText_vecParam, ",", s.vecParam);
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecString is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecString") != 0)
	{
		LOG_CRI << "pElemChild is not TVecString!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecString") != 0)
	{
		LOG_CRI << "Attribute: name is not vecString!";
		return false;
	}
	const char* pszText_vecString = pElemChild->GetText();
	if(pszText_vecString != NULL)
		SplitToText(pszText_vecString, ",", s.vecString);
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

bool ToXML(const STripodLog& s, TiXmlElement& rElement)
{
	rElement.SetValue("STripodLog");
	rElement.SetAttribute("type", ToUTF8Ptr("九疑鼎历史日志"));
	unique_ptr<TiXmlElement> pElem_qwRoleID(new TiXmlElement("UINT64"));
	if(pElem_qwRoleID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwRoleID->SetAttribute("name", "qwRoleID");
	pElem_qwRoleID->SetAttribute("value", NumberToString(s.qwRoleID).c_str());
	pElem_qwRoleID->SetAttribute("comment", ToUTF8Ptr("九疑鼎的所属玩家的ID"));
	if(rElement.LinkEndChild(pElem_qwRoleID.get()) != NULL)
		pElem_qwRoleID.release();
	unique_ptr<TiXmlElement> pElem_wMsgID(new TiXmlElement("UINT16"));
	if(pElem_wMsgID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wMsgID->SetAttribute("name", "wMsgID");
	pElem_wMsgID->SetAttribute("value", NumberToString(s.wMsgID).c_str());
	pElem_wMsgID->SetAttribute("comment", ToUTF8Ptr("对应日志ID（详见Message）"));
	if(rElement.LinkEndChild(pElem_wMsgID.get()) != NULL)
		pElem_wMsgID.release();
	unique_ptr<TiXmlElement> pElem_vecParam(new TiXmlElement("TVecINT64"));
	if(pElem_vecParam == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecParam->SetAttribute("name", "vecParam");
	string strText_vecParam;
	for(size_t i = 0; i < s.vecParam.size(); ++i)
	{
		if(i > 0)
			strText_vecParam += ", ";
		strText_vecParam += NumberToString(s.vecParam[i]);
	}
	unique_ptr<TiXmlText> pText_vecParam(new TiXmlText(strText_vecParam.c_str()));
	if(pText_vecParam == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(pElem_vecParam->LinkEndChild(pText_vecParam.get()) != NULL)
		pText_vecParam.release();
	pElem_vecParam->SetAttribute("comment", ToUTF8Ptr("整型变量"));
	if(rElement.LinkEndChild(pElem_vecParam.get()) != NULL)
		pElem_vecParam.release();
	unique_ptr<TiXmlElement> pElem_vecString(new TiXmlElement("TVecString"));
	if(pElem_vecString == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecString->SetAttribute("name", "vecString");
	string strText_vecString;
	for(size_t i = 0; i < s.vecString.size(); ++i)
	{
		if(i > 0)
			strText_vecString += ", ";
		strText_vecString += s.vecString[i];
	}
	unique_ptr<TiXmlText> pText_vecString(new TiXmlText(strText_vecString.c_str()));
	if(pText_vecString == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(pElem_vecString->LinkEndChild(pText_vecString.get()) != NULL)
		pText_vecString.release();
	pElem_vecString->SetAttribute("comment", ToUTF8Ptr("字符串型变量"));
	if(rElement.LinkEndChild(pElem_vecString.get()) != NULL)
		pElem_vecString.release();
	unique_ptr<TiXmlElement> pElem_dwTime(new TiXmlElement("UINT32"));
	if(pElem_dwTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwTime->SetAttribute("name", "dwTime");
	pElem_dwTime->SetAttribute("value", NumberToString(s.dwTime).c_str());
	pElem_dwTime->SetAttribute("comment", ToUTF8Ptr("日志时间"));
	if(rElement.LinkEndChild(pElem_dwTime.get()) != NULL)
		pElem_dwTime.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecTripodLog& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		STripodLog s;
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

bool VectorToXML(const TVecTripodLog& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("STripodLog"));
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

STripodData::STripodData() : qwRoleID(0) { }

STripodData::STripodData(UINT64 qwRoleID_, const NArenaGS::SArenaFighter& stPlayer_, const STripodHelp& tripodHelpData_, const TVecTripodInfo& vecTripods_, const TVecTripodLog& vecTripodLog_)
			: qwRoleID(qwRoleID_), stPlayer(stPlayer_), tripodHelpData(tripodHelpData_), vecTripods(vecTripods_), vecTripodLog(vecTripodLog_) { }

STripodData::STripodData(STripodData&& src) : qwRoleID(src.qwRoleID), stPlayer(move(src.stPlayer)), tripodHelpData(move(src.tripodHelpData)), vecTripods(move(src.vecTripods)), vecTripodLog(move(src.vecTripodLog)) { }

STripodData& STripodData::operator=(STripodData&& rhs)
{
	if(this != &rhs)
	{
		this->~STripodData();
		new (this) STripodData(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, STripodData& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwRoleID;
	src >> s.stPlayer;
	src >> s.tripodHelpData;
	src >> s.vecTripods;
	src >> s.vecTripodLog;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const STripodData& s)
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
	src << s.stPlayer;
	src << s.tripodHelpData;
	src << s.vecTripods;
	src << s.vecTripodLog;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, STripodData& s)
{
	if(strcmp(rElement.Value(), "STripodData") != 0)
	{
		LOG_CRI << "rElement is not STripodData!";
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
		LOG_CRI << "pElemChild for stPlayer is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "ArenaGS::SArenaFighter") != 0)
	{
		LOG_CRI << "pElemChild is not ArenaGS::SArenaFighter!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "stPlayer") != 0)
	{
		LOG_CRI << "Attribute: name is not stPlayer!";
		return false;
	}
	if(!FromXML(*pElemChild, s.stPlayer))
	{
		LOG_CRI << "FromXML for: stPlayer fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for tripodHelpData is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "STripodHelp") != 0)
	{
		LOG_CRI << "pElemChild is not STripodHelp!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "tripodHelpData") != 0)
	{
		LOG_CRI << "Attribute: name is not tripodHelpData!";
		return false;
	}
	if(!FromXML(*pElemChild, s.tripodHelpData))
	{
		LOG_CRI << "FromXML for: tripodHelpData fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecTripods is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecTripodInfo") != 0)
	{
		LOG_CRI << "pElemChild is not TVecTripodInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecTripods") != 0)
	{
		LOG_CRI << "Attribute: name is not vecTripods!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecTripods))
	{
		LOG_CRI << "VectorFromXML for vecTripods fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecTripodLog is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecTripodLog") != 0)
	{
		LOG_CRI << "pElemChild is not TVecTripodLog!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecTripodLog") != 0)
	{
		LOG_CRI << "Attribute: name is not vecTripodLog!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecTripodLog))
	{
		LOG_CRI << "VectorFromXML for vecTripodLog fails!";
		return false;
	}
	return true;
}

bool ToXML(const STripodData& s, TiXmlElement& rElement)
{
	rElement.SetValue("STripodData");
	rElement.SetAttribute("type", ToUTF8Ptr("玩家九疑鼎信息"));
	unique_ptr<TiXmlElement> pElem_qwRoleID(new TiXmlElement("UINT64"));
	if(pElem_qwRoleID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwRoleID->SetAttribute("name", "qwRoleID");
	pElem_qwRoleID->SetAttribute("value", NumberToString(s.qwRoleID).c_str());
	pElem_qwRoleID->SetAttribute("comment", ToUTF8Ptr("玩家的ID"));
	if(rElement.LinkEndChild(pElem_qwRoleID.get()) != NULL)
		pElem_qwRoleID.release();
	unique_ptr<TiXmlElement> pElem_stPlayer(new TiXmlElement("ArenaGS::SArenaFighter"));
	if(pElem_stPlayer == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_stPlayer->SetAttribute("name", "stPlayer");
	if(!ToXML(s.stPlayer, *pElem_stPlayer))
	{
		LOG_CRI << "stPlayer ToXML fails!";
		return false;
	}
	pElem_stPlayer->SetAttribute("comment", ToUTF8Ptr("九疑鼎所属玩家的基础信息"));
	if(rElement.LinkEndChild(pElem_stPlayer.get()) != NULL)
		pElem_stPlayer.release();
	unique_ptr<TiXmlElement> pElem_tripodHelpData(new TiXmlElement("STripodHelp"));
	if(pElem_tripodHelpData == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_tripodHelpData->SetAttribute("name", "tripodHelpData");
	if(!ToXML(s.tripodHelpData, *pElem_tripodHelpData))
	{
		LOG_CRI << "tripodHelpData ToXML fails!";
		return false;
	}
	pElem_tripodHelpData->SetAttribute("comment", ToUTF8Ptr("玩家九疑鼎的协助数据"));
	if(rElement.LinkEndChild(pElem_tripodHelpData.get()) != NULL)
		pElem_tripodHelpData.release();
	unique_ptr<TiXmlElement> pElem_vecTripods(new TiXmlElement("TVecTripodInfo"));
	if(pElem_vecTripods == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecTripods->SetAttribute("name", "vecTripods");
	if(!VectorToXML(s.vecTripods, *pElem_vecTripods))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecTripods->SetAttribute("comment", ToUTF8Ptr("玩家的所有九疑鼎数据"));
	if(rElement.LinkEndChild(pElem_vecTripods.get()) != NULL)
		pElem_vecTripods.release();
	unique_ptr<TiXmlElement> pElem_vecTripodLog(new TiXmlElement("TVecTripodLog"));
	if(pElem_vecTripodLog == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecTripodLog->SetAttribute("name", "vecTripodLog");
	if(!VectorToXML(s.vecTripodLog, *pElem_vecTripodLog))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecTripodLog->SetAttribute("comment", ToUTF8Ptr("九疑鼎日志"));
	if(rElement.LinkEndChild(pElem_vecTripodLog.get()) != NULL)
		pElem_vecTripodLog.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecTripodData& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		STripodData s;
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

bool VectorToXML(const TVecTripodData& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("STripodData"));
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

SFireInfo::SFireInfo() : wFireID(0), dwSucceed(0), dwRemain(0) { }

SFireInfo::SFireInfo(UINT16 wFireID_, UINT32 dwSucceed_, UINT32 dwRemain_) : wFireID(wFireID_), dwSucceed(dwSucceed_), dwRemain(dwRemain_) { }

CInArchive& operator>>(CInArchive& src, SFireInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.wFireID;
	src >> s.dwSucceed;
	src >> s.dwRemain;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SFireInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.wFireID;
	src << s.dwSucceed;
	src << s.dwRemain;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SFireInfo& s)
{
	if(strcmp(rElement.Value(), "SFireInfo") != 0)
	{
		LOG_CRI << "rElement is not SFireInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wFireID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wFireID") != 0)
	{
		LOG_CRI << "Attribute: name is not wFireID!";
		return false;
	}
	const char* pszVal_wFireID = pElemChild->Attribute("value");
	if(pszVal_wFireID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wFireID, s.wFireID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwSucceed is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwSucceed") != 0)
	{
		LOG_CRI << "Attribute: name is not dwSucceed!";
		return false;
	}
	const char* pszVal_dwSucceed = pElemChild->Attribute("value");
	if(pszVal_dwSucceed == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwSucceed, s.dwSucceed))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwRemain is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwRemain") != 0)
	{
		LOG_CRI << "Attribute: name is not dwRemain!";
		return false;
	}
	const char* pszVal_dwRemain = pElemChild->Attribute("value");
	if(pszVal_dwRemain == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwRemain, s.dwRemain))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SFireInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SFireInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("玩家的九疑鼎火种数据"));
	unique_ptr<TiXmlElement> pElem_wFireID(new TiXmlElement("UINT16"));
	if(pElem_wFireID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wFireID->SetAttribute("name", "wFireID");
	pElem_wFireID->SetAttribute("value", NumberToString(s.wFireID).c_str());
	pElem_wFireID->SetAttribute("comment", ToUTF8Ptr("九疑鼎火种ID"));
	if(rElement.LinkEndChild(pElem_wFireID.get()) != NULL)
		pElem_wFireID.release();
	unique_ptr<TiXmlElement> pElem_dwSucceed(new TiXmlElement("UINT32"));
	if(pElem_dwSucceed == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwSucceed->SetAttribute("name", "dwSucceed");
	pElem_dwSucceed->SetAttribute("value", NumberToString(s.dwSucceed).c_str());
	pElem_dwSucceed->SetAttribute("comment", ToUTF8Ptr("火种祈火成功次数"));
	if(rElement.LinkEndChild(pElem_dwSucceed.get()) != NULL)
		pElem_dwSucceed.release();
	unique_ptr<TiXmlElement> pElem_dwRemain(new TiXmlElement("UINT32"));
	if(pElem_dwRemain == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwRemain->SetAttribute("name", "dwRemain");
	pElem_dwRemain->SetAttribute("value", NumberToString(s.dwRemain).c_str());
	pElem_dwRemain->SetAttribute("comment", ToUTF8Ptr("火种剩余祈火次数"));
	if(rElement.LinkEndChild(pElem_dwRemain.get()) != NULL)
		pElem_dwRemain.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecFireInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SFireInfo s;
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

bool VectorToXML(const TVecFireInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SFireInfo"));
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

STripodStatus::STripodStatus() : qwRoleID(0), byShanfengst(0), byHelpst(0) { }

STripodStatus::STripodStatus(UINT64 qwRoleID_, UINT8 byShanfengst_, UINT8 byHelpst_) : qwRoleID(qwRoleID_), byShanfengst(byShanfengst_), byHelpst(byHelpst_) { }

CInArchive& operator>>(CInArchive& src, STripodStatus& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwRoleID;
	src >> s.byShanfengst;
	src >> s.byHelpst;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const STripodStatus& s)
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
	src << s.byShanfengst;
	src << s.byHelpst;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, STripodStatus& s)
{
	if(strcmp(rElement.Value(), "STripodStatus") != 0)
	{
		LOG_CRI << "rElement is not STripodStatus!";
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
		LOG_CRI << "pElemChild for byShanfengst is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byShanfengst") != 0)
	{
		LOG_CRI << "Attribute: name is not byShanfengst!";
		return false;
	}
	const char* pszVal_byShanfengst = pElemChild->Attribute("value");
	if(pszVal_byShanfengst == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byShanfengst, s.byShanfengst))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byHelpst is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byHelpst") != 0)
	{
		LOG_CRI << "Attribute: name is not byHelpst!";
		return false;
	}
	const char* pszVal_byHelpst = pElemChild->Attribute("value");
	if(pszVal_byHelpst == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byHelpst, s.byHelpst))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const STripodStatus& s, TiXmlElement& rElement)
{
	rElement.SetValue("STripodStatus");
	rElement.SetAttribute("type", ToUTF8Ptr("玩家九疑鼎的扇火、协助状态"));
	unique_ptr<TiXmlElement> pElem_qwRoleID(new TiXmlElement("UINT64"));
	if(pElem_qwRoleID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwRoleID->SetAttribute("name", "qwRoleID");
	pElem_qwRoleID->SetAttribute("value", NumberToString(s.qwRoleID).c_str());
	pElem_qwRoleID->SetAttribute("comment", ToUTF8Ptr("玩家的ID"));
	if(rElement.LinkEndChild(pElem_qwRoleID.get()) != NULL)
		pElem_qwRoleID.release();
	unique_ptr<TiXmlElement> pElem_byShanfengst(new TiXmlElement("UINT8"));
	if(pElem_byShanfengst == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byShanfengst->SetAttribute("name", "byShanfengst");
	pElem_byShanfengst->SetAttribute("value", NumberToString(s.byShanfengst).c_str());
	pElem_byShanfengst->SetAttribute("comment", ToUTF8Ptr("是否可以扇火(1是 0否)"));
	if(rElement.LinkEndChild(pElem_byShanfengst.get()) != NULL)
		pElem_byShanfengst.release();
	unique_ptr<TiXmlElement> pElem_byHelpst(new TiXmlElement("UINT8"));
	if(pElem_byHelpst == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byHelpst->SetAttribute("name", "byHelpst");
	pElem_byHelpst->SetAttribute("value", NumberToString(s.byHelpst).c_str());
	pElem_byHelpst->SetAttribute("comment", ToUTF8Ptr("是否可以协助(1是 0否)"));
	if(rElement.LinkEndChild(pElem_byHelpst.get()) != NULL)
		pElem_byHelpst.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecTripodStatus& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		STripodStatus s;
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

bool VectorToXML(const TVecTripodStatus& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("STripodStatus"));
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

} //namespace NTripodProt
