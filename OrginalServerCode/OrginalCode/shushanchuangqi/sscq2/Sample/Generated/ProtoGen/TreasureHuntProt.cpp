/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    TreasureHuntProt.cpp
//  Purpose:      寻宝协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "TreasureHuntProt.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NTreasureHuntProt
{

#ifdef PROT_USE_XML

const char* EnumValToStr(ETHOptResult e)
{
	switch(e)
	{
	case eTHOptResultFailed:
		return "eTHOptResultFailed";
	case eTHOptResultSucc:
		return "eTHOptResultSucc";
	case eTHMaxKillNumDay:
		return "eTHMaxKillNumDay";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, ETHOptResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, ETHOptResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eTHOptResultFailed", eTHOptResultFailed));
		mapStr2Val.insert(make_pair("eTHOptResultSucc", eTHOptResultSucc));
		mapStr2Val.insert(make_pair("eTHMaxKillNumDay", eTHMaxKillNumDay));
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

const char* EnumValToStr(ETHStatus e)
{
	switch(e)
	{
	case eTHNone:
		return "eTHNone";
	case eTHProgress:
		return "eTHProgress";
	case eTHWaitGetAward:
		return "eTHWaitGetAward";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, ETHStatus& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, ETHStatus> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eTHNone", eTHNone));
		mapStr2Val.insert(make_pair("eTHProgress", eTHProgress));
		mapStr2Val.insert(make_pair("eTHWaitGetAward", eTHWaitGetAward));
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

const char* EnumValToStr(ETHNotify e)
{
	switch(e)
	{
	case eTHBegin:
		return "eTHBegin";
	case eTHEnd:
		return "eTHEnd";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, ETHNotify& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, ETHNotify> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eTHBegin", eTHBegin));
		mapStr2Val.insert(make_pair("eTHEnd", eTHEnd));
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

const char* EnumValToStr(ETHLogType e)
{
	switch(e)
	{
	case eTHLogTypeA:
		return "eTHLogTypeA";
	case eTHLogTypeB:
		return "eTHLogTypeB";
	case eTHLogTypeC:
		return "eTHLogTypeC";
	case eTHLogTypeD:
		return "eTHLogTypeD";
	case eTHLogTypeE:
		return "eTHLogTypeE";
	case eTHLogTypeF:
		return "eTHLogTypeF";
	case eTHLogTypeG:
		return "eTHLogTypeG";
	case eTHLogTypeH:
		return "eTHLogTypeH";
	case eTHLogTypeI:
		return "eTHLogTypeI";
	case eTHLogTypeJ:
		return "eTHLogTypeJ";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, ETHLogType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, ETHLogType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eTHLogTypeA", eTHLogTypeA));
		mapStr2Val.insert(make_pair("eTHLogTypeB", eTHLogTypeB));
		mapStr2Val.insert(make_pair("eTHLogTypeC", eTHLogTypeC));
		mapStr2Val.insert(make_pair("eTHLogTypeD", eTHLogTypeD));
		mapStr2Val.insert(make_pair("eTHLogTypeE", eTHLogTypeE));
		mapStr2Val.insert(make_pair("eTHLogTypeF", eTHLogTypeF));
		mapStr2Val.insert(make_pair("eTHLogTypeG", eTHLogTypeG));
		mapStr2Val.insert(make_pair("eTHLogTypeH", eTHLogTypeH));
		mapStr2Val.insert(make_pair("eTHLogTypeI", eTHLogTypeI));
		mapStr2Val.insert(make_pair("eTHLogTypeJ", eTHLogTypeJ));
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

STHBuffInfo::STHBuffInfo() : byBuffID(0), byBuffNum(0), dwBuffCDTime(0) { }

STHBuffInfo::STHBuffInfo(UINT8 byBuffID_, UINT8 byBuffNum_, UINT32 dwBuffCDTime_) : byBuffID(byBuffID_), byBuffNum(byBuffNum_), dwBuffCDTime(dwBuffCDTime_) { }

CInArchive& operator>>(CInArchive& src, STHBuffInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.byBuffID;
	src >> s.byBuffNum;
	src >> s.dwBuffCDTime;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const STHBuffInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.byBuffID;
	src << s.byBuffNum;
	src << s.dwBuffCDTime;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, STHBuffInfo& s)
{
	if(strcmp(rElement.Value(), "STHBuffInfo") != 0)
	{
		LOG_CRI << "rElement is not STHBuffInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byBuffID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byBuffID") != 0)
	{
		LOG_CRI << "Attribute: name is not byBuffID!";
		return false;
	}
	const char* pszVal_byBuffID = pElemChild->Attribute("value");
	if(pszVal_byBuffID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byBuffID, s.byBuffID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byBuffNum is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byBuffNum") != 0)
	{
		LOG_CRI << "Attribute: name is not byBuffNum!";
		return false;
	}
	const char* pszVal_byBuffNum = pElemChild->Attribute("value");
	if(pszVal_byBuffNum == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byBuffNum, s.byBuffNum))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwBuffCDTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwBuffCDTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwBuffCDTime!";
		return false;
	}
	const char* pszVal_dwBuffCDTime = pElemChild->Attribute("value");
	if(pszVal_dwBuffCDTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwBuffCDTime, s.dwBuffCDTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const STHBuffInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("STHBuffInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("寻宝buff信息"));
	unique_ptr<TiXmlElement> pElem_byBuffID(new TiXmlElement("UINT8"));
	if(pElem_byBuffID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byBuffID->SetAttribute("name", "byBuffID");
	pElem_byBuffID->SetAttribute("value", NumberToString(s.byBuffID).c_str());
	pElem_byBuffID->SetAttribute("comment", ToUTF8Ptr("BuffID"));
	if(rElement.LinkEndChild(pElem_byBuffID.get()) != NULL)
		pElem_byBuffID.release();
	unique_ptr<TiXmlElement> pElem_byBuffNum(new TiXmlElement("UINT8"));
	if(pElem_byBuffNum == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byBuffNum->SetAttribute("name", "byBuffNum");
	pElem_byBuffNum->SetAttribute("value", NumberToString(s.byBuffNum).c_str());
	pElem_byBuffNum->SetAttribute("comment", ToUTF8Ptr("今日已使用Buff次数"));
	if(rElement.LinkEndChild(pElem_byBuffNum.get()) != NULL)
		pElem_byBuffNum.release();
	unique_ptr<TiXmlElement> pElem_dwBuffCDTime(new TiXmlElement("UINT32"));
	if(pElem_dwBuffCDTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwBuffCDTime->SetAttribute("name", "dwBuffCDTime");
	pElem_dwBuffCDTime->SetAttribute("value", NumberToString(s.dwBuffCDTime).c_str());
	pElem_dwBuffCDTime->SetAttribute("comment", ToUTF8Ptr("Buff CD 时间"));
	if(rElement.LinkEndChild(pElem_dwBuffCDTime.get()) != NULL)
		pElem_dwBuffCDTime.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecTHBuffInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		STHBuffInfo s;
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

bool VectorToXML(const TVecTHBuffInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("STHBuffInfo"));
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

STHBattleResult::STHBattleResult() : byCopyID(0), dwTotalTimes(0), dwCurBossHP(0), dwCurSilverNUm(0), dwCurItemNum(0), 
			dwCurXFCYNum(0) { }

STHBattleResult::STHBattleResult(UINT8 byCopyID_, UINT32 dwTotalTimes_, UINT32 dwCurBossHP_, UINT32 dwCurSilverNUm_, UINT32 dwCurItemNum_, 
			UINT32 dwCurXFCYNum_)
			: byCopyID(byCopyID_), dwTotalTimes(dwTotalTimes_), dwCurBossHP(dwCurBossHP_), dwCurSilverNUm(dwCurSilverNUm_), dwCurItemNum(dwCurItemNum_), 
			dwCurXFCYNum(dwCurXFCYNum_) { }

CInArchive& operator>>(CInArchive& src, STHBattleResult& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.byCopyID;
	src >> s.dwTotalTimes;
	src >> s.dwCurBossHP;
	src >> s.dwCurSilverNUm;
	src >> s.dwCurItemNum;
	src >> s.dwCurXFCYNum;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const STHBattleResult& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.byCopyID;
	src << s.dwTotalTimes;
	src << s.dwCurBossHP;
	src << s.dwCurSilverNUm;
	src << s.dwCurItemNum;
	src << s.dwCurXFCYNum;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, STHBattleResult& s)
{
	if(strcmp(rElement.Value(), "STHBattleResult") != 0)
	{
		LOG_CRI << "rElement is not STHBattleResult!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byCopyID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byCopyID") != 0)
	{
		LOG_CRI << "Attribute: name is not byCopyID!";
		return false;
	}
	const char* pszVal_byCopyID = pElemChild->Attribute("value");
	if(pszVal_byCopyID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byCopyID, s.byCopyID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwTotalTimes is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwTotalTimes") != 0)
	{
		LOG_CRI << "Attribute: name is not dwTotalTimes!";
		return false;
	}
	const char* pszVal_dwTotalTimes = pElemChild->Attribute("value");
	if(pszVal_dwTotalTimes == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwTotalTimes, s.dwTotalTimes))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwCurBossHP is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwCurBossHP") != 0)
	{
		LOG_CRI << "Attribute: name is not dwCurBossHP!";
		return false;
	}
	const char* pszVal_dwCurBossHP = pElemChild->Attribute("value");
	if(pszVal_dwCurBossHP == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwCurBossHP, s.dwCurBossHP))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwCurSilverNUm is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwCurSilverNUm") != 0)
	{
		LOG_CRI << "Attribute: name is not dwCurSilverNUm!";
		return false;
	}
	const char* pszVal_dwCurSilverNUm = pElemChild->Attribute("value");
	if(pszVal_dwCurSilverNUm == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwCurSilverNUm, s.dwCurSilverNUm))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwCurItemNum is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwCurItemNum") != 0)
	{
		LOG_CRI << "Attribute: name is not dwCurItemNum!";
		return false;
	}
	const char* pszVal_dwCurItemNum = pElemChild->Attribute("value");
	if(pszVal_dwCurItemNum == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwCurItemNum, s.dwCurItemNum))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwCurXFCYNum is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwCurXFCYNum") != 0)
	{
		LOG_CRI << "Attribute: name is not dwCurXFCYNum!";
		return false;
	}
	const char* pszVal_dwCurXFCYNum = pElemChild->Attribute("value");
	if(pszVal_dwCurXFCYNum == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwCurXFCYNum, s.dwCurXFCYNum))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const STHBattleResult& s, TiXmlElement& rElement)
{
	rElement.SetValue("STHBattleResult");
	rElement.SetAttribute("type", ToUTF8Ptr("战斗结果"));
	unique_ptr<TiXmlElement> pElem_byCopyID(new TiXmlElement("UINT8"));
	if(pElem_byCopyID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byCopyID->SetAttribute("name", "byCopyID");
	pElem_byCopyID->SetAttribute("value", NumberToString(s.byCopyID).c_str());
	pElem_byCopyID->SetAttribute("comment", ToUTF8Ptr("副本ID"));
	if(rElement.LinkEndChild(pElem_byCopyID.get()) != NULL)
		pElem_byCopyID.release();
	unique_ptr<TiXmlElement> pElem_dwTotalTimes(new TiXmlElement("UINT32"));
	if(pElem_dwTotalTimes == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwTotalTimes->SetAttribute("name", "dwTotalTimes");
	pElem_dwTotalTimes->SetAttribute("value", NumberToString(s.dwTotalTimes).c_str());
	pElem_dwTotalTimes->SetAttribute("comment", ToUTF8Ptr("寻宝时间"));
	if(rElement.LinkEndChild(pElem_dwTotalTimes.get()) != NULL)
		pElem_dwTotalTimes.release();
	unique_ptr<TiXmlElement> pElem_dwCurBossHP(new TiXmlElement("UINT32"));
	if(pElem_dwCurBossHP == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwCurBossHP->SetAttribute("name", "dwCurBossHP");
	pElem_dwCurBossHP->SetAttribute("value", NumberToString(s.dwCurBossHP).c_str());
	pElem_dwCurBossHP->SetAttribute("comment", ToUTF8Ptr("当前BOSS血量"));
	if(rElement.LinkEndChild(pElem_dwCurBossHP.get()) != NULL)
		pElem_dwCurBossHP.release();
	unique_ptr<TiXmlElement> pElem_dwCurSilverNUm(new TiXmlElement("UINT32"));
	if(pElem_dwCurSilverNUm == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwCurSilverNUm->SetAttribute("name", "dwCurSilverNUm");
	pElem_dwCurSilverNUm->SetAttribute("value", NumberToString(s.dwCurSilverNUm).c_str());
	pElem_dwCurSilverNUm->SetAttribute("comment", ToUTF8Ptr("当前掉落银币数量"));
	if(rElement.LinkEndChild(pElem_dwCurSilverNUm.get()) != NULL)
		pElem_dwCurSilverNUm.release();
	unique_ptr<TiXmlElement> pElem_dwCurItemNum(new TiXmlElement("UINT32"));
	if(pElem_dwCurItemNum == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwCurItemNum->SetAttribute("name", "dwCurItemNum");
	pElem_dwCurItemNum->SetAttribute("value", NumberToString(s.dwCurItemNum).c_str());
	pElem_dwCurItemNum->SetAttribute("comment", ToUTF8Ptr("当前掉落物品数量"));
	if(rElement.LinkEndChild(pElem_dwCurItemNum.get()) != NULL)
		pElem_dwCurItemNum.release();
	unique_ptr<TiXmlElement> pElem_dwCurXFCYNum(new TiXmlElement("UINT32"));
	if(pElem_dwCurXFCYNum == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwCurXFCYNum->SetAttribute("name", "dwCurXFCYNum");
	pElem_dwCurXFCYNum->SetAttribute("value", NumberToString(s.dwCurXFCYNum).c_str());
	pElem_dwCurXFCYNum->SetAttribute("comment", ToUTF8Ptr("当前掉落心法残页数量"));
	if(rElement.LinkEndChild(pElem_dwCurXFCYNum.get()) != NULL)
		pElem_dwCurXFCYNum.release();
	return true;
}

#endif

STHAwardInfo::STHAwardInfo() : wItemID(0), dwCount(0) { }

STHAwardInfo::STHAwardInfo(UINT16 wItemID_, UINT32 dwCount_) : wItemID(wItemID_), dwCount(dwCount_) { }

CInArchive& operator>>(CInArchive& src, STHAwardInfo& s)
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

COutArchive& operator<<(COutArchive& src, const STHAwardInfo& s)
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

bool FromXML(TiXmlElement& rElement, STHAwardInfo& s)
{
	if(strcmp(rElement.Value(), "STHAwardInfo") != 0)
	{
		LOG_CRI << "rElement is not STHAwardInfo!";
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

bool ToXML(const STHAwardInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("STHAwardInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("寻宝奖励信息"));
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

bool VectorFromXML(TiXmlElement& rElement, TVecTHAwardInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		STHAwardInfo s;
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

bool VectorToXML(const TVecTHAwardInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("STHAwardInfo"));
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

STHDBInfo::STHDBInfo() : qwRoleID(0), byCopyID(0), byStatus(0), dwBossCurHP(0), dwLastTime(0), 
			dwTime(0), dwNum(0) { }

STHDBInfo::STHDBInfo(UINT64 qwRoleID_, UINT8 byCopyID_, UINT8 byStatus_, UINT32 dwBossCurHP_, UINT32 dwLastTime_, 
			UINT32 dwTime_, UINT32 dwNum_, const std::string& strAward_)
			: qwRoleID(qwRoleID_), byCopyID(byCopyID_), byStatus(byStatus_), dwBossCurHP(dwBossCurHP_), dwLastTime(dwLastTime_), 
			dwTime(dwTime_), dwNum(dwNum_), strAward(strAward_) { }

STHDBInfo::STHDBInfo(STHDBInfo&& src) : qwRoleID(src.qwRoleID), byCopyID(src.byCopyID), byStatus(src.byStatus), dwBossCurHP(src.dwBossCurHP), dwLastTime(src.dwLastTime), 
			dwTime(src.dwTime), dwNum(src.dwNum), strAward(move(src.strAward)) { }

STHDBInfo& STHDBInfo::operator=(STHDBInfo&& rhs)
{
	if(this != &rhs)
	{
		this->~STHDBInfo();
		new (this) STHDBInfo(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, STHDBInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwRoleID;
	src >> s.byCopyID;
	src >> s.byStatus;
	src >> s.dwBossCurHP;
	src >> s.dwLastTime;
	src >> s.dwTime;
	src >> s.dwNum;
	src >> s.strAward;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const STHDBInfo& s)
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
	src << s.byCopyID;
	src << s.byStatus;
	src << s.dwBossCurHP;
	src << s.dwLastTime;
	src << s.dwTime;
	src << s.dwNum;
	src << s.strAward;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, STHDBInfo& s)
{
	if(strcmp(rElement.Value(), "STHDBInfo") != 0)
	{
		LOG_CRI << "rElement is not STHDBInfo!";
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
		LOG_CRI << "pElemChild for byCopyID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byCopyID") != 0)
	{
		LOG_CRI << "Attribute: name is not byCopyID!";
		return false;
	}
	const char* pszVal_byCopyID = pElemChild->Attribute("value");
	if(pszVal_byCopyID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byCopyID, s.byCopyID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byStatus is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byStatus") != 0)
	{
		LOG_CRI << "Attribute: name is not byStatus!";
		return false;
	}
	const char* pszVal_byStatus = pElemChild->Attribute("value");
	if(pszVal_byStatus == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byStatus, s.byStatus))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwBossCurHP is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwBossCurHP") != 0)
	{
		LOG_CRI << "Attribute: name is not dwBossCurHP!";
		return false;
	}
	const char* pszVal_dwBossCurHP = pElemChild->Attribute("value");
	if(pszVal_dwBossCurHP == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwBossCurHP, s.dwBossCurHP))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwLastTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwLastTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwLastTime!";
		return false;
	}
	const char* pszVal_dwLastTime = pElemChild->Attribute("value");
	if(pszVal_dwLastTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwLastTime, s.dwLastTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
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
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwNum is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwNum") != 0)
	{
		LOG_CRI << "Attribute: name is not dwNum!";
		return false;
	}
	const char* pszVal_dwNum = pElemChild->Attribute("value");
	if(pszVal_dwNum == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwNum, s.dwNum))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strAward is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strAward") != 0)
	{
		LOG_CRI << "Attribute: name is not strAward!";
		return false;
	}
	const char* pszVal_strAward = pElemChild->Attribute("value");
	if(pszVal_strAward == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strAward = pszVal_strAward;
	return true;
}

bool ToXML(const STHDBInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("STHDBInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("寻宝DB信息"));
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
	unique_ptr<TiXmlElement> pElem_byCopyID(new TiXmlElement("UINT8"));
	if(pElem_byCopyID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byCopyID->SetAttribute("name", "byCopyID");
	pElem_byCopyID->SetAttribute("value", NumberToString(s.byCopyID).c_str());
	pElem_byCopyID->SetAttribute("comment", ToUTF8Ptr("副本ID"));
	if(rElement.LinkEndChild(pElem_byCopyID.get()) != NULL)
		pElem_byCopyID.release();
	unique_ptr<TiXmlElement> pElem_byStatus(new TiXmlElement("UINT8"));
	if(pElem_byStatus == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byStatus->SetAttribute("name", "byStatus");
	pElem_byStatus->SetAttribute("value", NumberToString(s.byStatus).c_str());
	pElem_byStatus->SetAttribute("comment", ToUTF8Ptr("寻宝状态（1：正在进行；2：结束，等待领取奖品）"));
	if(rElement.LinkEndChild(pElem_byStatus.get()) != NULL)
		pElem_byStatus.release();
	unique_ptr<TiXmlElement> pElem_dwBossCurHP(new TiXmlElement("UINT32"));
	if(pElem_dwBossCurHP == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwBossCurHP->SetAttribute("name", "dwBossCurHP");
	pElem_dwBossCurHP->SetAttribute("value", NumberToString(s.dwBossCurHP).c_str());
	pElem_dwBossCurHP->SetAttribute("comment", ToUTF8Ptr("Boss当前血量"));
	if(rElement.LinkEndChild(pElem_dwBossCurHP.get()) != NULL)
		pElem_dwBossCurHP.release();
	unique_ptr<TiXmlElement> pElem_dwLastTime(new TiXmlElement("UINT32"));
	if(pElem_dwLastTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwLastTime->SetAttribute("name", "dwLastTime");
	pElem_dwLastTime->SetAttribute("value", NumberToString(s.dwLastTime).c_str());
	pElem_dwLastTime->SetAttribute("comment", ToUTF8Ptr("攻打上一波怪时间"));
	if(rElement.LinkEndChild(pElem_dwLastTime.get()) != NULL)
		pElem_dwLastTime.release();
	unique_ptr<TiXmlElement> pElem_dwTime(new TiXmlElement("UINT32"));
	if(pElem_dwTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwTime->SetAttribute("name", "dwTime");
	pElem_dwTime->SetAttribute("value", NumberToString(s.dwTime).c_str());
	pElem_dwTime->SetAttribute("comment", ToUTF8Ptr("寻宝累计时间"));
	if(rElement.LinkEndChild(pElem_dwTime.get()) != NULL)
		pElem_dwTime.release();
	unique_ptr<TiXmlElement> pElem_dwNum(new TiXmlElement("UINT32"));
	if(pElem_dwNum == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwNum->SetAttribute("name", "dwNum");
	pElem_dwNum->SetAttribute("value", NumberToString(s.dwNum).c_str());
	pElem_dwNum->SetAttribute("comment", ToUTF8Ptr("寻宝累计波数"));
	if(rElement.LinkEndChild(pElem_dwNum.get()) != NULL)
		pElem_dwNum.release();
	unique_ptr<TiXmlElement> pElem_strAward(new TiXmlElement("string"));
	if(pElem_strAward == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strAward->SetAttribute("name", "strAward");
	pElem_strAward->SetAttribute("value", s.strAward.c_str());
	pElem_strAward->SetAttribute("comment", ToUTF8Ptr("寻宝奖励"));
	if(rElement.LinkEndChild(pElem_strAward.get()) != NULL)
		pElem_strAward.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecTHDBInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		STHDBInfo s;
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

bool VectorToXML(const TVecTHDBInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("STHDBInfo"));
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

} //namespace NTreasureHuntProt
