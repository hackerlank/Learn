/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    ArenaGS.cpp
//  Purpose:      竞技场协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "ArenaGS.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NArenaGS
{

#ifdef PROT_USE_XML

const char* EnumValToStr(EArenaLevel e)
{
	switch(e)
	{
	case EArenaLevel_NONE:
		return "EArenaLevel_NONE";
	case EArenaLevel_IRON:
		return "EArenaLevel_IRON";
	case EArenaLevel_COPPER:
		return "EArenaLevel_COPPER";
	case EArenaLevel_SILVER:
		return "EArenaLevel_SILVER";
	case EArenaLevel_GOLD:
		return "EArenaLevel_GOLD";
	case EArenaLevel_DIAMOND:
		return "EArenaLevel_DIAMOND";
	case EArenaLevel_END:
		return "EArenaLevel_END";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EArenaLevel& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EArenaLevel> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("EArenaLevel_NONE", EArenaLevel_NONE));
		mapStr2Val.insert(make_pair("EArenaLevel_IRON", EArenaLevel_IRON));
		mapStr2Val.insert(make_pair("EArenaLevel_COPPER", EArenaLevel_COPPER));
		mapStr2Val.insert(make_pair("EArenaLevel_SILVER", EArenaLevel_SILVER));
		mapStr2Val.insert(make_pair("EArenaLevel_GOLD", EArenaLevel_GOLD));
		mapStr2Val.insert(make_pair("EArenaLevel_DIAMOND", EArenaLevel_DIAMOND));
		mapStr2Val.insert(make_pair("EArenaLevel_END", EArenaLevel_END));
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

const char* EnumValToStr(EArenaResult e)
{
	switch(e)
	{
	case EArenaR_Suc:
		return "EArenaR_Suc";
	case EArenaR_NoEnter:
		return "EArenaR_NoEnter";
	case EArenaR_CDTime:
		return "EArenaR_CDTime";
	case EArenaR_NoChanllengeTimes:
		return "EArenaR_NoChanllengeTimes";
	case EArenaR_BuyTimesChanllengeTimes:
		return "EArenaR_BuyTimesChanllengeTimes";
	case EArenaR_LackMoney:
		return "EArenaR_LackMoney";
	case EArenaR_EnemyNoExist:
		return "EArenaR_EnemyNoExist";
	case EArenaR_EnemyTimeOut:
		return "EArenaR_EnemyTimeOut";
	case EArenaR_EnemyIsSuc:
		return "EArenaR_EnemyIsSuc";
	case EArenaR_NoReward:
		return "EArenaR_NoReward";
	case EArenaR_RewardHasGet:
		return "EArenaR_RewardHasGet";
	case EArenaR_PackageFull:
		return "EArenaR_PackageFull";
	case EArenaR_AwardTimeOut:
		return "EArenaR_AwardTimeOut";
	case EArenaR_WirShipOverTimes:
		return "EArenaR_WirShipOverTimes";
	case EArenaR_WirShipPlayerOverTimer:
		return "EArenaR_WirShipPlayerOverTimer";
	case EArenaR_BuyTimesMax:
		return "EArenaR_BuyTimesMax";
	case EArenaR_VIPLevel:
		return "EArenaR_VIPLevel";
	case EArenaR_LadderNOOpen:
		return "EArenaR_LadderNOOpen";
	case EArenaR_LadderTimesLimit:
		return "EArenaR_LadderTimesLimit";
	case EArenaR_LadderAwardHasGet:
		return "EArenaR_LadderAwardHasGet";
	case EArenaR_LadderRankErr:
		return "EArenaR_LadderRankErr";
	case EArenaR_LadderRankLimit:
		return "EArenaR_LadderRankLimit";
	case EArenaR_ArenaNoOpen:
		return "EArenaR_ArenaNoOpen";
	case EArenaR_ArenaTimesLimit:
		return "EArenaR_ArenaTimesLimit";
	case EArenaR_ArenaAwardHasGet:
		return "EArenaR_ArenaAwardHasGet";
	case EArenaR_LadderTimesZero:
		return "EArenaR_LadderTimesZero";
	case EArenaR_LadderBuyTimesUp:
		return "EArenaR_LadderBuyTimesUp";
	case EArenaR_OtherErr:
		return "EArenaR_OtherErr";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EArenaResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EArenaResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("EArenaR_Suc", EArenaR_Suc));
		mapStr2Val.insert(make_pair("EArenaR_NoEnter", EArenaR_NoEnter));
		mapStr2Val.insert(make_pair("EArenaR_CDTime", EArenaR_CDTime));
		mapStr2Val.insert(make_pair("EArenaR_NoChanllengeTimes", EArenaR_NoChanllengeTimes));
		mapStr2Val.insert(make_pair("EArenaR_BuyTimesChanllengeTimes", EArenaR_BuyTimesChanllengeTimes));
		mapStr2Val.insert(make_pair("EArenaR_LackMoney", EArenaR_LackMoney));
		mapStr2Val.insert(make_pair("EArenaR_EnemyNoExist", EArenaR_EnemyNoExist));
		mapStr2Val.insert(make_pair("EArenaR_EnemyTimeOut", EArenaR_EnemyTimeOut));
		mapStr2Val.insert(make_pair("EArenaR_EnemyIsSuc", EArenaR_EnemyIsSuc));
		mapStr2Val.insert(make_pair("EArenaR_NoReward", EArenaR_NoReward));
		mapStr2Val.insert(make_pair("EArenaR_RewardHasGet", EArenaR_RewardHasGet));
		mapStr2Val.insert(make_pair("EArenaR_PackageFull", EArenaR_PackageFull));
		mapStr2Val.insert(make_pair("EArenaR_AwardTimeOut", EArenaR_AwardTimeOut));
		mapStr2Val.insert(make_pair("EArenaR_WirShipOverTimes", EArenaR_WirShipOverTimes));
		mapStr2Val.insert(make_pair("EArenaR_WirShipPlayerOverTimer", EArenaR_WirShipPlayerOverTimer));
		mapStr2Val.insert(make_pair("EArenaR_BuyTimesMax", EArenaR_BuyTimesMax));
		mapStr2Val.insert(make_pair("EArenaR_VIPLevel", EArenaR_VIPLevel));
		mapStr2Val.insert(make_pair("EArenaR_LadderNOOpen", EArenaR_LadderNOOpen));
		mapStr2Val.insert(make_pair("EArenaR_LadderTimesLimit", EArenaR_LadderTimesLimit));
		mapStr2Val.insert(make_pair("EArenaR_LadderAwardHasGet", EArenaR_LadderAwardHasGet));
		mapStr2Val.insert(make_pair("EArenaR_LadderRankErr", EArenaR_LadderRankErr));
		mapStr2Val.insert(make_pair("EArenaR_LadderRankLimit", EArenaR_LadderRankLimit));
		mapStr2Val.insert(make_pair("EArenaR_ArenaNoOpen", EArenaR_ArenaNoOpen));
		mapStr2Val.insert(make_pair("EArenaR_ArenaTimesLimit", EArenaR_ArenaTimesLimit));
		mapStr2Val.insert(make_pair("EArenaR_ArenaAwardHasGet", EArenaR_ArenaAwardHasGet));
		mapStr2Val.insert(make_pair("EArenaR_LadderTimesZero", EArenaR_LadderTimesZero));
		mapStr2Val.insert(make_pair("EArenaR_LadderBuyTimesUp", EArenaR_LadderBuyTimesUp));
		mapStr2Val.insert(make_pair("EArenaR_OtherErr", EArenaR_OtherErr));
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

const char* EnumValToStr(EArenaAwardType e)
{
	switch(e)
	{
	case Type_NONE:
		return "Type_NONE";
	case Type_Level:
		return "Type_Level";
	case Type_Rank:
		return "Type_Rank";
	case Type_LadderRank:
		return "Type_LadderRank";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EArenaAwardType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EArenaAwardType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("Type_NONE", Type_NONE));
		mapStr2Val.insert(make_pair("Type_Level", Type_Level));
		mapStr2Val.insert(make_pair("Type_Rank", Type_Rank));
		mapStr2Val.insert(make_pair("Type_LadderRank", Type_LadderRank));
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

SLadderRobot::SLadderRobot() : wMonsterID(0), wRank(0) { }

SLadderRobot::SLadderRobot(UINT16 wMonsterID_, UINT16 wRank_) : wMonsterID(wMonsterID_), wRank(wRank_) { }

CInArchive& operator>>(CInArchive& src, SLadderRobot& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.wMonsterID;
	src >> s.wRank;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SLadderRobot& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.wMonsterID;
	src << s.wRank;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SLadderRobot& s)
{
	if(strcmp(rElement.Value(), "SLadderRobot") != 0)
	{
		LOG_CRI << "rElement is not SLadderRobot!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wMonsterID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wMonsterID") != 0)
	{
		LOG_CRI << "Attribute: name is not wMonsterID!";
		return false;
	}
	const char* pszVal_wMonsterID = pElemChild->Attribute("value");
	if(pszVal_wMonsterID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wMonsterID, s.wMonsterID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wRank is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wRank") != 0)
	{
		LOG_CRI << "Attribute: name is not wRank!";
		return false;
	}
	const char* pszVal_wRank = pElemChild->Attribute("value");
	if(pszVal_wRank == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wRank, s.wRank))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SLadderRobot& s, TiXmlElement& rElement)
{
	rElement.SetValue("SLadderRobot");
	rElement.SetAttribute("type", ToUTF8Ptr("机器人排名信息"));
	unique_ptr<TiXmlElement> pElem_wMonsterID(new TiXmlElement("UINT16"));
	if(pElem_wMonsterID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wMonsterID->SetAttribute("name", "wMonsterID");
	pElem_wMonsterID->SetAttribute("value", NumberToString(s.wMonsterID).c_str());
	pElem_wMonsterID->SetAttribute("comment", ToUTF8Ptr("机器人ID"));
	if(rElement.LinkEndChild(pElem_wMonsterID.get()) != NULL)
		pElem_wMonsterID.release();
	unique_ptr<TiXmlElement> pElem_wRank(new TiXmlElement("UINT16"));
	if(pElem_wRank == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wRank->SetAttribute("name", "wRank");
	pElem_wRank->SetAttribute("value", NumberToString(s.wRank).c_str());
	pElem_wRank->SetAttribute("comment", ToUTF8Ptr("机器人排名"));
	if(rElement.LinkEndChild(pElem_wRank.get()) != NULL)
		pElem_wRank.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecLadderRobot& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SLadderRobot s;
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

bool VectorToXML(const TVecLadderRobot& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SLadderRobot"));
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

SArenaAward::SArenaAward() : eType((EArenaAwardType)0), byDraw(0), dwDrawID(0) { }

SArenaAward::SArenaAward(EArenaAwardType eType_, UINT8 byDraw_, UINT32 dwDrawID_) : eType(eType_), byDraw(byDraw_), dwDrawID(dwDrawID_) { }

CInArchive& operator>>(CInArchive& src, SArenaAward& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (UINT8&)s.eType;
	src >> s.byDraw;
	src >> s.dwDrawID;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SArenaAward& s)
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
	src << s.byDraw;
	src << s.dwDrawID;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SArenaAward& s)
{
	if(strcmp(rElement.Value(), "SArenaAward") != 0)
	{
		LOG_CRI << "rElement is not SArenaAward!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "EArenaAwardType") != 0)
	{
		LOG_CRI << "pElemChild is not EArenaAwardType!";
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
		LOG_CRI << "pElemChild for byDraw is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byDraw") != 0)
	{
		LOG_CRI << "Attribute: name is not byDraw!";
		return false;
	}
	const char* pszVal_byDraw = pElemChild->Attribute("value");
	if(pszVal_byDraw == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byDraw, s.byDraw))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwDrawID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwDrawID") != 0)
	{
		LOG_CRI << "Attribute: name is not dwDrawID!";
		return false;
	}
	const char* pszVal_dwDrawID = pElemChild->Attribute("value");
	if(pszVal_dwDrawID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwDrawID, s.dwDrawID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SArenaAward& s, TiXmlElement& rElement)
{
	rElement.SetValue("SArenaAward");
	rElement.SetAttribute("type", ToUTF8Ptr("玩家奖励信息"));
	unique_ptr<TiXmlElement> pElem_eType(new TiXmlElement("EArenaAwardType"));
	if(pElem_eType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eType->SetAttribute("name", "eType");
	const char* pszEnum_eType = EnumValToStr(s.eType);
	if(pszEnum_eType == NULL)
	{
		LOG_CRI << "EnumValToStr for EArenaAwardType fails!";
		return false;
	}
	pElem_eType->SetAttribute("value", pszEnum_eType);
	pElem_eType->SetAttribute("comment", ToUTF8Ptr("奖励包类型"));
	if(rElement.LinkEndChild(pElem_eType.get()) != NULL)
		pElem_eType.release();
	unique_ptr<TiXmlElement> pElem_byDraw(new TiXmlElement("UINT8"));
	if(pElem_byDraw == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byDraw->SetAttribute("name", "byDraw");
	pElem_byDraw->SetAttribute("value", NumberToString(s.byDraw).c_str());
	pElem_byDraw->SetAttribute("comment", ToUTF8Ptr("0,表示未领取；1，表示已领取"));
	if(rElement.LinkEndChild(pElem_byDraw.get()) != NULL)
		pElem_byDraw.release();
	unique_ptr<TiXmlElement> pElem_dwDrawID(new TiXmlElement("UINT32"));
	if(pElem_dwDrawID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwDrawID->SetAttribute("name", "dwDrawID");
	pElem_dwDrawID->SetAttribute("value", NumberToString(s.dwDrawID).c_str());
	pElem_dwDrawID->SetAttribute("comment", ToUTF8Ptr("掉落包ID"));
	if(rElement.LinkEndChild(pElem_dwDrawID.get()) != NULL)
		pElem_dwDrawID.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecArenaAward& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SArenaAward s;
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

bool VectorToXML(const TVecArenaAward& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SArenaAward"));
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

SArenaFighter::SArenaFighter() : wLevel(0) { }

SArenaFighter::SArenaFighter(const std::string& strName_, UINT16 wLevel_, const NBattleGS::SPlayerFeature& stAppear_) : strName(strName_), wLevel(wLevel_), stAppear(stAppear_) { }

SArenaFighter::SArenaFighter(SArenaFighter&& src) : strName(move(src.strName)), wLevel(src.wLevel), stAppear(move(src.stAppear)) { }

SArenaFighter& SArenaFighter::operator=(SArenaFighter&& rhs)
{
	if(this != &rhs)
	{
		this->~SArenaFighter();
		new (this) SArenaFighter(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SArenaFighter& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.strName;
	src >> s.wLevel;
	src >> s.stAppear;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SArenaFighter& s)
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
	src << s.wLevel;
	src << s.stAppear;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SArenaFighter& s)
{
	if(strcmp(rElement.Value(), "SArenaFighter") != 0)
	{
		LOG_CRI << "rElement is not SArenaFighter!";
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
		LOG_CRI << "pElemChild for stAppear is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "BattleGS::SPlayerFeature") != 0)
	{
		LOG_CRI << "pElemChild is not BattleGS::SPlayerFeature!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "stAppear") != 0)
	{
		LOG_CRI << "Attribute: name is not stAppear!";
		return false;
	}
	if(!FromXML(*pElemChild, s.stAppear))
	{
		LOG_CRI << "FromXML for: stAppear fails!";
		return false;
	}
	return true;
}

bool ToXML(const SArenaFighter& s, TiXmlElement& rElement)
{
	rElement.SetValue("SArenaFighter");
	rElement.SetAttribute("type", ToUTF8Ptr("竞技场玩家信息"));
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
	unique_ptr<TiXmlElement> pElem_stAppear(new TiXmlElement("BattleGS::SPlayerFeature"));
	if(pElem_stAppear == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_stAppear->SetAttribute("name", "stAppear");
	if(!ToXML(s.stAppear, *pElem_stAppear))
	{
		LOG_CRI << "stAppear ToXML fails!";
		return false;
	}
	pElem_stAppear->SetAttribute("comment", ToUTF8Ptr("外观"));
	if(rElement.LinkEndChild(pElem_stAppear.get()) != NULL)
		pElem_stAppear.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecArenaFighter& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SArenaFighter s;
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

bool VectorToXML(const TVecArenaFighter& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SArenaFighter"));
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

SFlushFighter::SFlushFighter() : bySuc(0), qwFighterID(0) { }

SFlushFighter::SFlushFighter(UINT8 bySuc_, UINT64 qwFighterID_) : bySuc(bySuc_), qwFighterID(qwFighterID_) { }

CInArchive& operator>>(CInArchive& src, SFlushFighter& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.bySuc;
	src >> s.qwFighterID;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SFlushFighter& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.bySuc;
	src << s.qwFighterID;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SFlushFighter& s)
{
	if(strcmp(rElement.Value(), "SFlushFighter") != 0)
	{
		LOG_CRI << "rElement is not SFlushFighter!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for bySuc is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "bySuc") != 0)
	{
		LOG_CRI << "Attribute: name is not bySuc!";
		return false;
	}
	const char* pszVal_bySuc = pElemChild->Attribute("value");
	if(pszVal_bySuc == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_bySuc, s.bySuc))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwFighterID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwFighterID") != 0)
	{
		LOG_CRI << "Attribute: name is not qwFighterID!";
		return false;
	}
	const char* pszVal_qwFighterID = pElemChild->Attribute("value");
	if(pszVal_qwFighterID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwFighterID, s.qwFighterID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SFlushFighter& s, TiXmlElement& rElement)
{
	rElement.SetValue("SFlushFighter");
	rElement.SetAttribute("type", ToUTF8Ptr("玩家刷对手信息"));
	unique_ptr<TiXmlElement> pElem_bySuc(new TiXmlElement("UINT8"));
	if(pElem_bySuc == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_bySuc->SetAttribute("name", "bySuc");
	pElem_bySuc->SetAttribute("value", NumberToString(s.bySuc).c_str());
	pElem_bySuc->SetAttribute("comment", ToUTF8Ptr("0,表示未战胜；1，表示已击败"));
	if(rElement.LinkEndChild(pElem_bySuc.get()) != NULL)
		pElem_bySuc.release();
	unique_ptr<TiXmlElement> pElem_qwFighterID(new TiXmlElement("UINT64"));
	if(pElem_qwFighterID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwFighterID->SetAttribute("name", "qwFighterID");
	pElem_qwFighterID->SetAttribute("value", NumberToString(s.qwFighterID).c_str());
	pElem_qwFighterID->SetAttribute("comment", ToUTF8Ptr("对手ID,小于65535为怪物"));
	if(rElement.LinkEndChild(pElem_qwFighterID.get()) != NULL)
		pElem_qwFighterID.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecFlushFither& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SFlushFighter s;
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

bool VectorToXML(const TVecFlushFither& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SFlushFighter"));
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

SArenaPlayerBaseData::SArenaPlayerBaseData() : dwRanking(0), dwScore(0), dwLadderRank(0), eLevel((EArenaLevel)0), dwLastFlushTime(0), 
			dwLastRank(0), eLastLevel((EArenaLevel)0), dwFighterPower(0), byQuality(0), byVIPLevel(0), 
			dwLastLadderRank(0) { }

CInArchive& operator>>(CInArchive& src, SArenaPlayerBaseData& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.dwRanking;
	src >> s.dwScore;
	src >> s.dwLadderRank;
	src >> (UINT8&)s.eLevel;
	src >> s.dwLastFlushTime;
	src >> s.dwLastRank;
	src >> (UINT8&)s.eLastLevel;
	src >> s.dwFighterPower;
	src >> s.byQuality;
	src >> s.byVIPLevel;
	src >> s.dwLastLadderRank;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SArenaPlayerBaseData& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.dwRanking;
	src << s.dwScore;
	src << s.dwLadderRank;
	src << (UINT8&)s.eLevel;
	src << s.dwLastFlushTime;
	src << s.dwLastRank;
	src << (UINT8&)s.eLastLevel;
	src << s.dwFighterPower;
	src << s.byQuality;
	src << s.byVIPLevel;
	src << s.dwLastLadderRank;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SArenaPlayerBaseData& s)
{
	if(strcmp(rElement.Value(), "SArenaPlayerBaseData") != 0)
	{
		LOG_CRI << "rElement is not SArenaPlayerBaseData!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwRanking is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwRanking") != 0)
	{
		LOG_CRI << "Attribute: name is not dwRanking!";
		return false;
	}
	const char* pszVal_dwRanking = pElemChild->Attribute("value");
	if(pszVal_dwRanking == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwRanking, s.dwRanking))
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
		LOG_CRI << "pElemChild for dwLadderRank is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwLadderRank") != 0)
	{
		LOG_CRI << "Attribute: name is not dwLadderRank!";
		return false;
	}
	const char* pszVal_dwLadderRank = pElemChild->Attribute("value");
	if(pszVal_dwLadderRank == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwLadderRank, s.dwLadderRank))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eLevel is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "EArenaLevel") != 0)
	{
		LOG_CRI << "pElemChild is not EArenaLevel!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eLevel") != 0)
	{
		LOG_CRI << "Attribute: name is not eLevel!";
		return false;
	}
	const char* pszVal_eLevel = pElemChild->Attribute("value");
	if(pszVal_eLevel == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!EnumStrToVal(pszVal_eLevel, s.eLevel))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwLastFlushTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwLastFlushTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwLastFlushTime!";
		return false;
	}
	const char* pszVal_dwLastFlushTime = pElemChild->Attribute("value");
	if(pszVal_dwLastFlushTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwLastFlushTime, s.dwLastFlushTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwLastRank is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwLastRank") != 0)
	{
		LOG_CRI << "Attribute: name is not dwLastRank!";
		return false;
	}
	const char* pszVal_dwLastRank = pElemChild->Attribute("value");
	if(pszVal_dwLastRank == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwLastRank, s.dwLastRank))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eLastLevel is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "EArenaLevel") != 0)
	{
		LOG_CRI << "pElemChild is not EArenaLevel!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eLastLevel") != 0)
	{
		LOG_CRI << "Attribute: name is not eLastLevel!";
		return false;
	}
	const char* pszVal_eLastLevel = pElemChild->Attribute("value");
	if(pszVal_eLastLevel == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!EnumStrToVal(pszVal_eLastLevel, s.eLastLevel))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwFighterPower is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwFighterPower") != 0)
	{
		LOG_CRI << "Attribute: name is not dwFighterPower!";
		return false;
	}
	const char* pszVal_dwFighterPower = pElemChild->Attribute("value");
	if(pszVal_dwFighterPower == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwFighterPower, s.dwFighterPower))
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
		LOG_CRI << "pElemChild for dwLastLadderRank is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwLastLadderRank") != 0)
	{
		LOG_CRI << "Attribute: name is not dwLastLadderRank!";
		return false;
	}
	const char* pszVal_dwLastLadderRank = pElemChild->Attribute("value");
	if(pszVal_dwLastLadderRank == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwLastLadderRank, s.dwLastLadderRank))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SArenaPlayerBaseData& s, TiXmlElement& rElement)
{
	rElement.SetValue("SArenaPlayerBaseData");
	rElement.SetAttribute("type", ToUTF8Ptr("竞技场玩家基本信息"));
	unique_ptr<TiXmlElement> pElem_dwRanking(new TiXmlElement("UINT32"));
	if(pElem_dwRanking == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwRanking->SetAttribute("name", "dwRanking");
	pElem_dwRanking->SetAttribute("value", NumberToString(s.dwRanking).c_str());
	pElem_dwRanking->SetAttribute("comment", ToUTF8Ptr("同积分序号"));
	if(rElement.LinkEndChild(pElem_dwRanking.get()) != NULL)
		pElem_dwRanking.release();
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
	unique_ptr<TiXmlElement> pElem_dwLadderRank(new TiXmlElement("UINT32"));
	if(pElem_dwLadderRank == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwLadderRank->SetAttribute("name", "dwLadderRank");
	pElem_dwLadderRank->SetAttribute("value", NumberToString(s.dwLadderRank).c_str());
	pElem_dwLadderRank->SetAttribute("comment", ToUTF8Ptr("天梯排名0表示天梯功未开启，10000表示天梯功能已开启未挑机器人，9999表示已挑战机器人"));
	if(rElement.LinkEndChild(pElem_dwLadderRank.get()) != NULL)
		pElem_dwLadderRank.release();
	unique_ptr<TiXmlElement> pElem_eLevel(new TiXmlElement("EArenaLevel"));
	if(pElem_eLevel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eLevel->SetAttribute("name", "eLevel");
	const char* pszEnum_eLevel = EnumValToStr(s.eLevel);
	if(pszEnum_eLevel == NULL)
	{
		LOG_CRI << "EnumValToStr for EArenaLevel fails!";
		return false;
	}
	pElem_eLevel->SetAttribute("value", pszEnum_eLevel);
	pElem_eLevel->SetAttribute("comment", ToUTF8Ptr("竞技等级"));
	if(rElement.LinkEndChild(pElem_eLevel.get()) != NULL)
		pElem_eLevel.release();
	unique_ptr<TiXmlElement> pElem_dwLastFlushTime(new TiXmlElement("UINT32"));
	if(pElem_dwLastFlushTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwLastFlushTime->SetAttribute("name", "dwLastFlushTime");
	pElem_dwLastFlushTime->SetAttribute("value", NumberToString(s.dwLastFlushTime).c_str());
	pElem_dwLastFlushTime->SetAttribute("comment", ToUTF8Ptr("最近客户端刷新时间"));
	if(rElement.LinkEndChild(pElem_dwLastFlushTime.get()) != NULL)
		pElem_dwLastFlushTime.release();
	unique_ptr<TiXmlElement> pElem_dwLastRank(new TiXmlElement("UINT32"));
	if(pElem_dwLastRank == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwLastRank->SetAttribute("name", "dwLastRank");
	pElem_dwLastRank->SetAttribute("value", NumberToString(s.dwLastRank).c_str());
	pElem_dwLastRank->SetAttribute("comment", ToUTF8Ptr("最近结算排名"));
	if(rElement.LinkEndChild(pElem_dwLastRank.get()) != NULL)
		pElem_dwLastRank.release();
	unique_ptr<TiXmlElement> pElem_eLastLevel(new TiXmlElement("EArenaLevel"));
	if(pElem_eLastLevel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eLastLevel->SetAttribute("name", "eLastLevel");
	const char* pszEnum_eLastLevel = EnumValToStr(s.eLastLevel);
	if(pszEnum_eLastLevel == NULL)
	{
		LOG_CRI << "EnumValToStr for EArenaLevel fails!";
		return false;
	}
	pElem_eLastLevel->SetAttribute("value", pszEnum_eLastLevel);
	pElem_eLastLevel->SetAttribute("comment", ToUTF8Ptr("最近结算之前段位"));
	if(rElement.LinkEndChild(pElem_eLastLevel.get()) != NULL)
		pElem_eLastLevel.release();
	unique_ptr<TiXmlElement> pElem_dwFighterPower(new TiXmlElement("UINT32"));
	if(pElem_dwFighterPower == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwFighterPower->SetAttribute("name", "dwFighterPower");
	pElem_dwFighterPower->SetAttribute("value", NumberToString(s.dwFighterPower).c_str());
	pElem_dwFighterPower->SetAttribute("comment", ToUTF8Ptr("战斗力"));
	if(rElement.LinkEndChild(pElem_dwFighterPower.get()) != NULL)
		pElem_dwFighterPower.release();
	unique_ptr<TiXmlElement> pElem_byQuality(new TiXmlElement("UINT8"));
	if(pElem_byQuality == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byQuality->SetAttribute("name", "byQuality");
	pElem_byQuality->SetAttribute("value", NumberToString(s.byQuality).c_str());
	pElem_byQuality->SetAttribute("comment", ToUTF8Ptr("品质"));
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
	pElem_byVIPLevel->SetAttribute("comment", ToUTF8Ptr("VIP等级"));
	if(rElement.LinkEndChild(pElem_byVIPLevel.get()) != NULL)
		pElem_byVIPLevel.release();
	unique_ptr<TiXmlElement> pElem_dwLastLadderRank(new TiXmlElement("UINT32"));
	if(pElem_dwLastLadderRank == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwLastLadderRank->SetAttribute("name", "dwLastLadderRank");
	pElem_dwLastLadderRank->SetAttribute("value", NumberToString(s.dwLastLadderRank).c_str());
	pElem_dwLastLadderRank->SetAttribute("comment", ToUTF8Ptr("最近结算排名"));
	if(rElement.LinkEndChild(pElem_dwLastLadderRank.get()) != NULL)
		pElem_dwLastLadderRank.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecArenaPlayerBaseData& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SArenaPlayerBaseData s;
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

bool VectorToXML(const TVecArenaPlayerBaseData& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SArenaPlayerBaseData"));
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

SArenaPlayerData::SArenaPlayerData() : qwRoleID(0) { }

SArenaPlayerData::SArenaPlayerData(UINT64 qwRoleID_, const SArenaFighter& stFighter_, const SArenaPlayerBaseData& stBaseData_) : qwRoleID(qwRoleID_), stFighter(stFighter_), stBaseData(stBaseData_) { }

CInArchive& operator>>(CInArchive& src, SArenaPlayerData& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwRoleID;
	src >> s.stFighter;
	src >> s.stBaseData;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SArenaPlayerData& s)
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
	src << s.stFighter;
	src << s.stBaseData;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SArenaPlayerData& s)
{
	if(strcmp(rElement.Value(), "SArenaPlayerData") != 0)
	{
		LOG_CRI << "rElement is not SArenaPlayerData!";
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
		LOG_CRI << "pElemChild for stFighter is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "SArenaFighter") != 0)
	{
		LOG_CRI << "pElemChild is not SArenaFighter!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "stFighter") != 0)
	{
		LOG_CRI << "Attribute: name is not stFighter!";
		return false;
	}
	if(!FromXML(*pElemChild, s.stFighter))
	{
		LOG_CRI << "FromXML for: stFighter fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for stBaseData is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "SArenaPlayerBaseData") != 0)
	{
		LOG_CRI << "pElemChild is not SArenaPlayerBaseData!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "stBaseData") != 0)
	{
		LOG_CRI << "Attribute: name is not stBaseData!";
		return false;
	}
	if(!FromXML(*pElemChild, s.stBaseData))
	{
		LOG_CRI << "FromXML for: stBaseData fails!";
		return false;
	}
	return true;
}

bool ToXML(const SArenaPlayerData& s, TiXmlElement& rElement)
{
	rElement.SetValue("SArenaPlayerData");
	rElement.SetAttribute("type", ToUTF8Ptr("竞技场玩家信息，要进数据库的总信息"));
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
	unique_ptr<TiXmlElement> pElem_stFighter(new TiXmlElement("SArenaFighter"));
	if(pElem_stFighter == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_stFighter->SetAttribute("name", "stFighter");
	if(!ToXML(s.stFighter, *pElem_stFighter))
	{
		LOG_CRI << "stFighter ToXML fails!";
		return false;
	}
	pElem_stFighter->SetAttribute("comment", ToUTF8Ptr("角色基本信息"));
	if(rElement.LinkEndChild(pElem_stFighter.get()) != NULL)
		pElem_stFighter.release();
	unique_ptr<TiXmlElement> pElem_stBaseData(new TiXmlElement("SArenaPlayerBaseData"));
	if(pElem_stBaseData == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_stBaseData->SetAttribute("name", "stBaseData");
	if(!ToXML(s.stBaseData, *pElem_stBaseData))
	{
		LOG_CRI << "stBaseData ToXML fails!";
		return false;
	}
	pElem_stBaseData->SetAttribute("comment", ToUTF8Ptr("基本竞技场信息"));
	if(rElement.LinkEndChild(pElem_stBaseData.get()) != NULL)
		pElem_stBaseData.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecArenaPlayerData& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SArenaPlayerData s;
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

bool VectorToXML(const TVecArenaPlayerData& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SArenaPlayerData"));
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

SArenaPlayerBaseDataUpdate::SArenaPlayerBaseDataUpdate() : qwRoleID(0) { }

SArenaPlayerBaseDataUpdate::SArenaPlayerBaseDataUpdate(UINT64 qwRoleID_, const SArenaPlayerBaseData& stBaseData_) : qwRoleID(qwRoleID_), stBaseData(stBaseData_) { }

CInArchive& operator>>(CInArchive& src, SArenaPlayerBaseDataUpdate& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwRoleID;
	src >> s.stBaseData;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SArenaPlayerBaseDataUpdate& s)
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
	src << s.stBaseData;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SArenaPlayerBaseDataUpdate& s)
{
	if(strcmp(rElement.Value(), "SArenaPlayerBaseDataUpdate") != 0)
	{
		LOG_CRI << "rElement is not SArenaPlayerBaseDataUpdate!";
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
		LOG_CRI << "pElemChild for stBaseData is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "SArenaPlayerBaseData") != 0)
	{
		LOG_CRI << "pElemChild is not SArenaPlayerBaseData!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "stBaseData") != 0)
	{
		LOG_CRI << "Attribute: name is not stBaseData!";
		return false;
	}
	if(!FromXML(*pElemChild, s.stBaseData))
	{
		LOG_CRI << "FromXML for: stBaseData fails!";
		return false;
	}
	return true;
}

bool ToXML(const SArenaPlayerBaseDataUpdate& s, TiXmlElement& rElement)
{
	rElement.SetValue("SArenaPlayerBaseDataUpdate");
	rElement.SetAttribute("type", ToUTF8Ptr("竞技场更新信息"));
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
	unique_ptr<TiXmlElement> pElem_stBaseData(new TiXmlElement("SArenaPlayerBaseData"));
	if(pElem_stBaseData == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_stBaseData->SetAttribute("name", "stBaseData");
	if(!ToXML(s.stBaseData, *pElem_stBaseData))
	{
		LOG_CRI << "stBaseData ToXML fails!";
		return false;
	}
	pElem_stBaseData->SetAttribute("comment", ToUTF8Ptr("基本竞技场信息"));
	if(rElement.LinkEndChild(pElem_stBaseData.get()) != NULL)
		pElem_stBaseData.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecArenaPlayerBaseDataUpdate& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SArenaPlayerBaseDataUpdate s;
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

bool VectorToXML(const TVecArenaPlayerBaseDataUpdate& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SArenaPlayerBaseDataUpdate"));
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

SFlushFitherForClient::SFlushFitherForClient() : wGroup(0), eLevel((EArenaLevel)0), dwFighterPower(0), dwLadderRank(0), dwArenaRank(0) { }

SFlushFitherForClient::SFlushFitherForClient(const SFlushFighter& stFlushFighter_, UINT32 wGroup_, EArenaLevel eLevel_, const SArenaFighter& stFighter_, UINT32 dwFighterPower_, 
			UINT32 dwLadderRank_, UINT32 dwArenaRank_)
			: stFlushFighter(stFlushFighter_), wGroup(wGroup_), eLevel(eLevel_), stFighter(stFighter_), dwFighterPower(dwFighterPower_), 
			dwLadderRank(dwLadderRank_), dwArenaRank(dwArenaRank_) { }

SFlushFitherForClient::SFlushFitherForClient(SFlushFitherForClient&& src) : stFlushFighter(src.stFlushFighter), wGroup(src.wGroup), eLevel(src.eLevel), stFighter(move(src.stFighter)), dwFighterPower(src.dwFighterPower), 
			dwLadderRank(src.dwLadderRank), dwArenaRank(src.dwArenaRank) { }

SFlushFitherForClient& SFlushFitherForClient::operator=(SFlushFitherForClient&& rhs)
{
	if(this != &rhs)
	{
		this->~SFlushFitherForClient();
		new (this) SFlushFitherForClient(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SFlushFitherForClient& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.stFlushFighter;
	src >> s.wGroup;
	src >> (UINT8&)s.eLevel;
	src >> s.stFighter;
	src >> s.dwFighterPower;
	src >> s.dwLadderRank;
	src >> s.dwArenaRank;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SFlushFitherForClient& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.stFlushFighter;
	src << s.wGroup;
	src << (UINT8&)s.eLevel;
	src << s.stFighter;
	src << s.dwFighterPower;
	src << s.dwLadderRank;
	src << s.dwArenaRank;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SFlushFitherForClient& s)
{
	if(strcmp(rElement.Value(), "SFlushFitherForClient") != 0)
	{
		LOG_CRI << "rElement is not SFlushFitherForClient!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for stFlushFighter is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "SFlushFighter") != 0)
	{
		LOG_CRI << "pElemChild is not SFlushFighter!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "stFlushFighter") != 0)
	{
		LOG_CRI << "Attribute: name is not stFlushFighter!";
		return false;
	}
	if(!FromXML(*pElemChild, s.stFlushFighter))
	{
		LOG_CRI << "FromXML for: stFlushFighter fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wGroup is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wGroup") != 0)
	{
		LOG_CRI << "Attribute: name is not wGroup!";
		return false;
	}
	const char* pszVal_wGroup = pElemChild->Attribute("value");
	if(pszVal_wGroup == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wGroup, s.wGroup))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eLevel is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "EArenaLevel") != 0)
	{
		LOG_CRI << "pElemChild is not EArenaLevel!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eLevel") != 0)
	{
		LOG_CRI << "Attribute: name is not eLevel!";
		return false;
	}
	const char* pszVal_eLevel = pElemChild->Attribute("value");
	if(pszVal_eLevel == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!EnumStrToVal(pszVal_eLevel, s.eLevel))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for stFighter is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "SArenaFighter") != 0)
	{
		LOG_CRI << "pElemChild is not SArenaFighter!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "stFighter") != 0)
	{
		LOG_CRI << "Attribute: name is not stFighter!";
		return false;
	}
	if(!FromXML(*pElemChild, s.stFighter))
	{
		LOG_CRI << "FromXML for: stFighter fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwFighterPower is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwFighterPower") != 0)
	{
		LOG_CRI << "Attribute: name is not dwFighterPower!";
		return false;
	}
	const char* pszVal_dwFighterPower = pElemChild->Attribute("value");
	if(pszVal_dwFighterPower == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwFighterPower, s.dwFighterPower))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwLadderRank is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwLadderRank") != 0)
	{
		LOG_CRI << "Attribute: name is not dwLadderRank!";
		return false;
	}
	const char* pszVal_dwLadderRank = pElemChild->Attribute("value");
	if(pszVal_dwLadderRank == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwLadderRank, s.dwLadderRank))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwArenaRank is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwArenaRank") != 0)
	{
		LOG_CRI << "Attribute: name is not dwArenaRank!";
		return false;
	}
	const char* pszVal_dwArenaRank = pElemChild->Attribute("value");
	if(pszVal_dwArenaRank == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwArenaRank, s.dwArenaRank))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SFlushFitherForClient& s, TiXmlElement& rElement)
{
	rElement.SetValue("SFlushFitherForClient");
	rElement.SetAttribute("type", ToUTF8Ptr("客户端竞技场的对手"));
	unique_ptr<TiXmlElement> pElem_stFlushFighter(new TiXmlElement("SFlushFighter"));
	if(pElem_stFlushFighter == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_stFlushFighter->SetAttribute("name", "stFlushFighter");
	if(!ToXML(s.stFlushFighter, *pElem_stFlushFighter))
	{
		LOG_CRI << "stFlushFighter ToXML fails!";
		return false;
	}
	pElem_stFlushFighter->SetAttribute("comment", ToUTF8Ptr("id，小于65535为机器人，读怪物列表"));
	if(rElement.LinkEndChild(pElem_stFlushFighter.get()) != NULL)
		pElem_stFlushFighter.release();
	unique_ptr<TiXmlElement> pElem_wGroup(new TiXmlElement("UINT32"));
	if(pElem_wGroup == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wGroup->SetAttribute("name", "wGroup");
	pElem_wGroup->SetAttribute("value", NumberToString(s.wGroup).c_str());
	pElem_wGroup->SetAttribute("comment", ToUTF8Ptr(""));
	if(rElement.LinkEndChild(pElem_wGroup.get()) != NULL)
		pElem_wGroup.release();
	unique_ptr<TiXmlElement> pElem_eLevel(new TiXmlElement("EArenaLevel"));
	if(pElem_eLevel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eLevel->SetAttribute("name", "eLevel");
	const char* pszEnum_eLevel = EnumValToStr(s.eLevel);
	if(pszEnum_eLevel == NULL)
	{
		LOG_CRI << "EnumValToStr for EArenaLevel fails!";
		return false;
	}
	pElem_eLevel->SetAttribute("value", pszEnum_eLevel);
	pElem_eLevel->SetAttribute("comment", ToUTF8Ptr("段位,无段位表示没有加入竞技场"));
	if(rElement.LinkEndChild(pElem_eLevel.get()) != NULL)
		pElem_eLevel.release();
	unique_ptr<TiXmlElement> pElem_stFighter(new TiXmlElement("SArenaFighter"));
	if(pElem_stFighter == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_stFighter->SetAttribute("name", "stFighter");
	if(!ToXML(s.stFighter, *pElem_stFighter))
	{
		LOG_CRI << "stFighter ToXML fails!";
		return false;
	}
	pElem_stFighter->SetAttribute("comment", ToUTF8Ptr("其他属性"));
	if(rElement.LinkEndChild(pElem_stFighter.get()) != NULL)
		pElem_stFighter.release();
	unique_ptr<TiXmlElement> pElem_dwFighterPower(new TiXmlElement("UINT32"));
	if(pElem_dwFighterPower == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwFighterPower->SetAttribute("name", "dwFighterPower");
	pElem_dwFighterPower->SetAttribute("value", NumberToString(s.dwFighterPower).c_str());
	pElem_dwFighterPower->SetAttribute("comment", ToUTF8Ptr("战斗力"));
	if(rElement.LinkEndChild(pElem_dwFighterPower.get()) != NULL)
		pElem_dwFighterPower.release();
	unique_ptr<TiXmlElement> pElem_dwLadderRank(new TiXmlElement("UINT32"));
	if(pElem_dwLadderRank == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwLadderRank->SetAttribute("name", "dwLadderRank");
	pElem_dwLadderRank->SetAttribute("value", NumberToString(s.dwLadderRank).c_str());
	pElem_dwLadderRank->SetAttribute("comment", ToUTF8Ptr("天梯排名"));
	if(rElement.LinkEndChild(pElem_dwLadderRank.get()) != NULL)
		pElem_dwLadderRank.release();
	unique_ptr<TiXmlElement> pElem_dwArenaRank(new TiXmlElement("UINT32"));
	if(pElem_dwArenaRank == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwArenaRank->SetAttribute("name", "dwArenaRank");
	pElem_dwArenaRank->SetAttribute("value", NumberToString(s.dwArenaRank).c_str());
	pElem_dwArenaRank->SetAttribute("comment", ToUTF8Ptr("历练排名"));
	if(rElement.LinkEndChild(pElem_dwArenaRank.get()) != NULL)
		pElem_dwArenaRank.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecSFlushFitherForClient& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SFlushFitherForClient s;
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

bool VectorToXML(const TVecSFlushFitherForClient& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SFlushFitherForClient"));
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

SLadderReport::SLadderReport() : qwBattleID(0), qwEmemyID(0), dwMonsterId(0), byAttack(0), bySuc(0), 
			dwPreRank(0), dwNowRank(0), dwTimer(0) { }

SLadderReport::SLadderReport(UINT64 qwBattleID_, UINT64 qwEmemyID_, const std::string& strName_, UINT32 dwMonsterId_, UINT8 byAttack_, 
			UINT8 bySuc_, UINT32 dwPreRank_, UINT32 dwNowRank_, UINT32 dwTimer_)
			: qwBattleID(qwBattleID_), qwEmemyID(qwEmemyID_), strName(strName_), dwMonsterId(dwMonsterId_), byAttack(byAttack_), 
			bySuc(bySuc_), dwPreRank(dwPreRank_), dwNowRank(dwNowRank_), dwTimer(dwTimer_) { }

SLadderReport::SLadderReport(SLadderReport&& src) : qwBattleID(src.qwBattleID), qwEmemyID(src.qwEmemyID), strName(move(src.strName)), dwMonsterId(src.dwMonsterId), byAttack(src.byAttack), 
			bySuc(src.bySuc), dwPreRank(src.dwPreRank), dwNowRank(src.dwNowRank), dwTimer(src.dwTimer) { }

SLadderReport& SLadderReport::operator=(SLadderReport&& rhs)
{
	if(this != &rhs)
	{
		this->~SLadderReport();
		new (this) SLadderReport(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SLadderReport& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwBattleID;
	src >> s.qwEmemyID;
	src >> s.strName;
	src >> s.dwMonsterId;
	src >> s.byAttack;
	src >> s.bySuc;
	src >> s.dwPreRank;
	src >> s.dwNowRank;
	src >> s.dwTimer;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SLadderReport& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.qwBattleID;
	src << s.qwEmemyID;
	src << s.strName;
	src << s.dwMonsterId;
	src << s.byAttack;
	src << s.bySuc;
	src << s.dwPreRank;
	src << s.dwNowRank;
	src << s.dwTimer;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SLadderReport& s)
{
	if(strcmp(rElement.Value(), "SLadderReport") != 0)
	{
		LOG_CRI << "rElement is not SLadderReport!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwBattleID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwBattleID") != 0)
	{
		LOG_CRI << "Attribute: name is not qwBattleID!";
		return false;
	}
	const char* pszVal_qwBattleID = pElemChild->Attribute("value");
	if(pszVal_qwBattleID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwBattleID, s.qwBattleID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwEmemyID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwEmemyID") != 0)
	{
		LOG_CRI << "Attribute: name is not qwEmemyID!";
		return false;
	}
	const char* pszVal_qwEmemyID = pElemChild->Attribute("value");
	if(pszVal_qwEmemyID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwEmemyID, s.qwEmemyID))
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
		LOG_CRI << "pElemChild for dwMonsterId is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwMonsterId") != 0)
	{
		LOG_CRI << "Attribute: name is not dwMonsterId!";
		return false;
	}
	const char* pszVal_dwMonsterId = pElemChild->Attribute("value");
	if(pszVal_dwMonsterId == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwMonsterId, s.dwMonsterId))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byAttack is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byAttack") != 0)
	{
		LOG_CRI << "Attribute: name is not byAttack!";
		return false;
	}
	const char* pszVal_byAttack = pElemChild->Attribute("value");
	if(pszVal_byAttack == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byAttack, s.byAttack))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for bySuc is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "bySuc") != 0)
	{
		LOG_CRI << "Attribute: name is not bySuc!";
		return false;
	}
	const char* pszVal_bySuc = pElemChild->Attribute("value");
	if(pszVal_bySuc == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_bySuc, s.bySuc))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwPreRank is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwPreRank") != 0)
	{
		LOG_CRI << "Attribute: name is not dwPreRank!";
		return false;
	}
	const char* pszVal_dwPreRank = pElemChild->Attribute("value");
	if(pszVal_dwPreRank == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwPreRank, s.dwPreRank))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwNowRank is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwNowRank") != 0)
	{
		LOG_CRI << "Attribute: name is not dwNowRank!";
		return false;
	}
	const char* pszVal_dwNowRank = pElemChild->Attribute("value");
	if(pszVal_dwNowRank == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwNowRank, s.dwNowRank))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwTimer is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwTimer") != 0)
	{
		LOG_CRI << "Attribute: name is not dwTimer!";
		return false;
	}
	const char* pszVal_dwTimer = pElemChild->Attribute("value");
	if(pszVal_dwTimer == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwTimer, s.dwTimer))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SLadderReport& s, TiXmlElement& rElement)
{
	rElement.SetValue("SLadderReport");
	rElement.SetAttribute("type", ToUTF8Ptr("战报"));
	unique_ptr<TiXmlElement> pElem_qwBattleID(new TiXmlElement("UINT64"));
	if(pElem_qwBattleID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwBattleID->SetAttribute("name", "qwBattleID");
	pElem_qwBattleID->SetAttribute("value", NumberToString(s.qwBattleID).c_str());
	pElem_qwBattleID->SetAttribute("comment", ToUTF8Ptr("战报ID"));
	if(rElement.LinkEndChild(pElem_qwBattleID.get()) != NULL)
		pElem_qwBattleID.release();
	unique_ptr<TiXmlElement> pElem_qwEmemyID(new TiXmlElement("UINT64"));
	if(pElem_qwEmemyID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwEmemyID->SetAttribute("name", "qwEmemyID");
	pElem_qwEmemyID->SetAttribute("value", NumberToString(s.qwEmemyID).c_str());
	pElem_qwEmemyID->SetAttribute("comment", ToUTF8Ptr("对手ID"));
	if(rElement.LinkEndChild(pElem_qwEmemyID.get()) != NULL)
		pElem_qwEmemyID.release();
	unique_ptr<TiXmlElement> pElem_strName(new TiXmlElement("string"));
	if(pElem_strName == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strName->SetAttribute("name", "strName");
	pElem_strName->SetAttribute("value", s.strName.c_str());
	pElem_strName->SetAttribute("comment", ToUTF8Ptr("对手名字"));
	if(rElement.LinkEndChild(pElem_strName.get()) != NULL)
		pElem_strName.release();
	unique_ptr<TiXmlElement> pElem_dwMonsterId(new TiXmlElement("UINT32"));
	if(pElem_dwMonsterId == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwMonsterId->SetAttribute("name", "dwMonsterId");
	pElem_dwMonsterId->SetAttribute("value", NumberToString(s.dwMonsterId).c_str());
	pElem_dwMonsterId->SetAttribute("comment", ToUTF8Ptr("对手是机器人,机器人ID"));
	if(rElement.LinkEndChild(pElem_dwMonsterId.get()) != NULL)
		pElem_dwMonsterId.release();
	unique_ptr<TiXmlElement> pElem_byAttack(new TiXmlElement("UINT8"));
	if(pElem_byAttack == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byAttack->SetAttribute("name", "byAttack");
	pElem_byAttack->SetAttribute("value", NumberToString(s.byAttack).c_str());
	pElem_byAttack->SetAttribute("comment", ToUTF8Ptr("0,表示挑战别人，1表示别人挑战自己"));
	if(rElement.LinkEndChild(pElem_byAttack.get()) != NULL)
		pElem_byAttack.release();
	unique_ptr<TiXmlElement> pElem_bySuc(new TiXmlElement("UINT8"));
	if(pElem_bySuc == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_bySuc->SetAttribute("name", "bySuc");
	pElem_bySuc->SetAttribute("value", NumberToString(s.bySuc).c_str());
	pElem_bySuc->SetAttribute("comment", ToUTF8Ptr("0,自己失败，1，自己胜利"));
	if(rElement.LinkEndChild(pElem_bySuc.get()) != NULL)
		pElem_bySuc.release();
	unique_ptr<TiXmlElement> pElem_dwPreRank(new TiXmlElement("UINT32"));
	if(pElem_dwPreRank == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwPreRank->SetAttribute("name", "dwPreRank");
	pElem_dwPreRank->SetAttribute("value", NumberToString(s.dwPreRank).c_str());
	pElem_dwPreRank->SetAttribute("comment", ToUTF8Ptr("挑战之前的排名"));
	if(rElement.LinkEndChild(pElem_dwPreRank.get()) != NULL)
		pElem_dwPreRank.release();
	unique_ptr<TiXmlElement> pElem_dwNowRank(new TiXmlElement("UINT32"));
	if(pElem_dwNowRank == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwNowRank->SetAttribute("name", "dwNowRank");
	pElem_dwNowRank->SetAttribute("value", NumberToString(s.dwNowRank).c_str());
	pElem_dwNowRank->SetAttribute("comment", ToUTF8Ptr("挑战之后的排名"));
	if(rElement.LinkEndChild(pElem_dwNowRank.get()) != NULL)
		pElem_dwNowRank.release();
	unique_ptr<TiXmlElement> pElem_dwTimer(new TiXmlElement("UINT32"));
	if(pElem_dwTimer == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwTimer->SetAttribute("name", "dwTimer");
	pElem_dwTimer->SetAttribute("value", NumberToString(s.dwTimer).c_str());
	pElem_dwTimer->SetAttribute("comment", ToUTF8Ptr("战报时间"));
	if(rElement.LinkEndChild(pElem_dwTimer.get()) != NULL)
		pElem_dwTimer.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecLadderReport& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SLadderReport s;
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

bool VectorToXML(const TVecLadderReport& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SLadderReport"));
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

SArenaRank2Client::SArenaRank2Client() : qwRoleID(0), dwRank(0), dwScore(0), dwFighterPower(0), byQuality(0), 
			byVIPLevel(0), dwLadderRank(0) { }

SArenaRank2Client::SArenaRank2Client(UINT64 qwRoleID_, UINT32 dwRank_, UINT32 dwScore_, const SArenaFighter& stFighter_, UINT32 dwFighterPower_, 
			UINT8 byQuality_, UINT8 byVIPLevel_, UINT32 dwLadderRank_)
			: qwRoleID(qwRoleID_), dwRank(dwRank_), dwScore(dwScore_), stFighter(stFighter_), dwFighterPower(dwFighterPower_), 
			byQuality(byQuality_), byVIPLevel(byVIPLevel_), dwLadderRank(dwLadderRank_) { }

SArenaRank2Client::SArenaRank2Client(SArenaRank2Client&& src) : qwRoleID(src.qwRoleID), dwRank(src.dwRank), dwScore(src.dwScore), stFighter(move(src.stFighter)), dwFighterPower(src.dwFighterPower), 
			byQuality(src.byQuality), byVIPLevel(src.byVIPLevel), dwLadderRank(src.dwLadderRank) { }

SArenaRank2Client& SArenaRank2Client::operator=(SArenaRank2Client&& rhs)
{
	if(this != &rhs)
	{
		this->~SArenaRank2Client();
		new (this) SArenaRank2Client(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SArenaRank2Client& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwRoleID;
	src >> s.dwRank;
	src >> s.dwScore;
	src >> s.stFighter;
	src >> s.dwFighterPower;
	src >> s.byQuality;
	src >> s.byVIPLevel;
	src >> s.dwLadderRank;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SArenaRank2Client& s)
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
	src << s.dwRank;
	src << s.dwScore;
	src << s.stFighter;
	src << s.dwFighterPower;
	src << s.byQuality;
	src << s.byVIPLevel;
	src << s.dwLadderRank;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SArenaRank2Client& s)
{
	if(strcmp(rElement.Value(), "SArenaRank2Client") != 0)
	{
		LOG_CRI << "rElement is not SArenaRank2Client!";
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
		LOG_CRI << "pElemChild for stFighter is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "SArenaFighter") != 0)
	{
		LOG_CRI << "pElemChild is not SArenaFighter!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "stFighter") != 0)
	{
		LOG_CRI << "Attribute: name is not stFighter!";
		return false;
	}
	if(!FromXML(*pElemChild, s.stFighter))
	{
		LOG_CRI << "FromXML for: stFighter fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwFighterPower is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwFighterPower") != 0)
	{
		LOG_CRI << "Attribute: name is not dwFighterPower!";
		return false;
	}
	const char* pszVal_dwFighterPower = pElemChild->Attribute("value");
	if(pszVal_dwFighterPower == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwFighterPower, s.dwFighterPower))
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
		LOG_CRI << "pElemChild for dwLadderRank is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwLadderRank") != 0)
	{
		LOG_CRI << "Attribute: name is not dwLadderRank!";
		return false;
	}
	const char* pszVal_dwLadderRank = pElemChild->Attribute("value");
	if(pszVal_dwLadderRank == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwLadderRank, s.dwLadderRank))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SArenaRank2Client& s, TiXmlElement& rElement)
{
	rElement.SetValue("SArenaRank2Client");
	rElement.SetAttribute("type", ToUTF8Ptr("排行信息"));
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
	unique_ptr<TiXmlElement> pElem_dwRank(new TiXmlElement("UINT32"));
	if(pElem_dwRank == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwRank->SetAttribute("name", "dwRank");
	pElem_dwRank->SetAttribute("value", NumberToString(s.dwRank).c_str());
	pElem_dwRank->SetAttribute("comment", ToUTF8Ptr("名次"));
	if(rElement.LinkEndChild(pElem_dwRank.get()) != NULL)
		pElem_dwRank.release();
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
	unique_ptr<TiXmlElement> pElem_stFighter(new TiXmlElement("SArenaFighter"));
	if(pElem_stFighter == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_stFighter->SetAttribute("name", "stFighter");
	if(!ToXML(s.stFighter, *pElem_stFighter))
	{
		LOG_CRI << "stFighter ToXML fails!";
		return false;
	}
	pElem_stFighter->SetAttribute("comment", ToUTF8Ptr("其它信息"));
	if(rElement.LinkEndChild(pElem_stFighter.get()) != NULL)
		pElem_stFighter.release();
	unique_ptr<TiXmlElement> pElem_dwFighterPower(new TiXmlElement("UINT32"));
	if(pElem_dwFighterPower == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwFighterPower->SetAttribute("name", "dwFighterPower");
	pElem_dwFighterPower->SetAttribute("value", NumberToString(s.dwFighterPower).c_str());
	pElem_dwFighterPower->SetAttribute("comment", ToUTF8Ptr("战斗力"));
	if(rElement.LinkEndChild(pElem_dwFighterPower.get()) != NULL)
		pElem_dwFighterPower.release();
	unique_ptr<TiXmlElement> pElem_byQuality(new TiXmlElement("UINT8"));
	if(pElem_byQuality == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byQuality->SetAttribute("name", "byQuality");
	pElem_byQuality->SetAttribute("value", NumberToString(s.byQuality).c_str());
	pElem_byQuality->SetAttribute("comment", ToUTF8Ptr("品质"));
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
	pElem_byVIPLevel->SetAttribute("comment", ToUTF8Ptr("品质"));
	if(rElement.LinkEndChild(pElem_byVIPLevel.get()) != NULL)
		pElem_byVIPLevel.release();
	unique_ptr<TiXmlElement> pElem_dwLadderRank(new TiXmlElement("UINT32"));
	if(pElem_dwLadderRank == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwLadderRank->SetAttribute("name", "dwLadderRank");
	pElem_dwLadderRank->SetAttribute("value", NumberToString(s.dwLadderRank).c_str());
	pElem_dwLadderRank->SetAttribute("comment", ToUTF8Ptr("天梯排名"));
	if(rElement.LinkEndChild(pElem_dwLadderRank.get()) != NULL)
		pElem_dwLadderRank.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecArenaRank2Client& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SArenaRank2Client s;
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

bool VectorToXML(const TVecArenaRank2Client& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SArenaRank2Client"));
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

SArenaPlayerBaseData2Client::SArenaPlayerBaseData2Client() : dwRanking(0), dwScore(0), eLevel((EArenaLevel)0), dwTotalSize(0), ePreLevel((EArenaLevel)0), 
			dwPreRank(0), dwArenaCDTime(0), dwLadderCDTime(0), wChallenge(0), wChallengeBuyTimes(0), 
			wSelfReflush(0), wSelfFreeReflush(0), byArenaWirship(0), dwLastLadderRank(0), dwMinLadderRank(0), 
			dwFighterPower(0), dwLadderRank(0), wLadderChallenge(0), dwArenaAward(0), dwLadderBuyTimes(0), 
			dwLadderBuyTimesToday(0) { }

SArenaPlayerBaseData2Client::SArenaPlayerBaseData2Client(SArenaPlayerBaseData2Client&& src) : dwRanking(src.dwRanking), dwScore(src.dwScore), eLevel(src.eLevel), dwTotalSize(src.dwTotalSize), ePreLevel(src.ePreLevel), 
			dwPreRank(src.dwPreRank), vecAwards(move(src.vecAwards)), dwArenaCDTime(src.dwArenaCDTime), dwLadderCDTime(src.dwLadderCDTime), wChallenge(src.wChallenge), 
			wChallengeBuyTimes(src.wChallengeBuyTimes), wSelfReflush(src.wSelfReflush), wSelfFreeReflush(src.wSelfFreeReflush), byArenaWirship(src.byArenaWirship), dwLastLadderRank(src.dwLastLadderRank), 
			dwMinLadderRank(src.dwMinLadderRank), vecFlushFigter(move(src.vecFlushFigter)), vecWirshipFigter(move(src.vecWirshipFigter)), dwFighterPower(src.dwFighterPower), dwLadderRank(src.dwLadderRank), 
			wLadderChallenge(src.wLadderChallenge), dwArenaAward(src.dwArenaAward), dwLadderBuyTimes(src.dwLadderBuyTimes), dwLadderBuyTimesToday(src.dwLadderBuyTimesToday) { }

SArenaPlayerBaseData2Client& SArenaPlayerBaseData2Client::operator=(SArenaPlayerBaseData2Client&& rhs)
{
	if(this != &rhs)
	{
		this->~SArenaPlayerBaseData2Client();
		new (this) SArenaPlayerBaseData2Client(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SArenaPlayerBaseData2Client& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.dwRanking;
	src >> s.dwScore;
	src >> (UINT8&)s.eLevel;
	src >> s.dwTotalSize;
	src >> (UINT8&)s.ePreLevel;
	src >> s.dwPreRank;
	src >> s.vecAwards;
	src >> s.dwArenaCDTime;
	src >> s.dwLadderCDTime;
	src >> s.wChallenge;
	src >> s.wChallengeBuyTimes;
	src >> s.wSelfReflush;
	src >> s.wSelfFreeReflush;
	src >> s.byArenaWirship;
	src >> s.dwLastLadderRank;
	src >> s.dwMinLadderRank;
	src >> s.vecFlushFigter;
	src >> s.vecWirshipFigter;
	src >> s.dwFighterPower;
	src >> s.dwLadderRank;
	src >> s.wLadderChallenge;
	src >> s.dwArenaAward;
	src >> s.dwLadderBuyTimes;
	src >> s.dwLadderBuyTimesToday;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SArenaPlayerBaseData2Client& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.dwRanking;
	src << s.dwScore;
	src << (UINT8&)s.eLevel;
	src << s.dwTotalSize;
	src << (UINT8&)s.ePreLevel;
	src << s.dwPreRank;
	src << s.vecAwards;
	src << s.dwArenaCDTime;
	src << s.dwLadderCDTime;
	src << s.wChallenge;
	src << s.wChallengeBuyTimes;
	src << s.wSelfReflush;
	src << s.wSelfFreeReflush;
	src << s.byArenaWirship;
	src << s.dwLastLadderRank;
	src << s.dwMinLadderRank;
	src << s.vecFlushFigter;
	src << s.vecWirshipFigter;
	src << s.dwFighterPower;
	src << s.dwLadderRank;
	src << s.wLadderChallenge;
	src << s.dwArenaAward;
	src << s.dwLadderBuyTimes;
	src << s.dwLadderBuyTimesToday;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SArenaPlayerBaseData2Client& s)
{
	if(strcmp(rElement.Value(), "SArenaPlayerBaseData2Client") != 0)
	{
		LOG_CRI << "rElement is not SArenaPlayerBaseData2Client!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwRanking is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwRanking") != 0)
	{
		LOG_CRI << "Attribute: name is not dwRanking!";
		return false;
	}
	const char* pszVal_dwRanking = pElemChild->Attribute("value");
	if(pszVal_dwRanking == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwRanking, s.dwRanking))
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
		LOG_CRI << "pElemChild for eLevel is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "EArenaLevel") != 0)
	{
		LOG_CRI << "pElemChild is not EArenaLevel!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eLevel") != 0)
	{
		LOG_CRI << "Attribute: name is not eLevel!";
		return false;
	}
	const char* pszVal_eLevel = pElemChild->Attribute("value");
	if(pszVal_eLevel == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!EnumStrToVal(pszVal_eLevel, s.eLevel))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwTotalSize is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwTotalSize") != 0)
	{
		LOG_CRI << "Attribute: name is not dwTotalSize!";
		return false;
	}
	const char* pszVal_dwTotalSize = pElemChild->Attribute("value");
	if(pszVal_dwTotalSize == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwTotalSize, s.dwTotalSize))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for ePreLevel is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "EArenaLevel") != 0)
	{
		LOG_CRI << "pElemChild is not EArenaLevel!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "ePreLevel") != 0)
	{
		LOG_CRI << "Attribute: name is not ePreLevel!";
		return false;
	}
	const char* pszVal_ePreLevel = pElemChild->Attribute("value");
	if(pszVal_ePreLevel == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!EnumStrToVal(pszVal_ePreLevel, s.ePreLevel))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwPreRank is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwPreRank") != 0)
	{
		LOG_CRI << "Attribute: name is not dwPreRank!";
		return false;
	}
	const char* pszVal_dwPreRank = pElemChild->Attribute("value");
	if(pszVal_dwPreRank == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwPreRank, s.dwPreRank))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecAwards is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecArenaAward") != 0)
	{
		LOG_CRI << "pElemChild is not TVecArenaAward!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecAwards") != 0)
	{
		LOG_CRI << "Attribute: name is not vecAwards!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecAwards))
	{
		LOG_CRI << "VectorFromXML for vecAwards fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwArenaCDTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwArenaCDTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwArenaCDTime!";
		return false;
	}
	const char* pszVal_dwArenaCDTime = pElemChild->Attribute("value");
	if(pszVal_dwArenaCDTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwArenaCDTime, s.dwArenaCDTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwLadderCDTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwLadderCDTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwLadderCDTime!";
		return false;
	}
	const char* pszVal_dwLadderCDTime = pElemChild->Attribute("value");
	if(pszVal_dwLadderCDTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwLadderCDTime, s.dwLadderCDTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wChallenge is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wChallenge") != 0)
	{
		LOG_CRI << "Attribute: name is not wChallenge!";
		return false;
	}
	const char* pszVal_wChallenge = pElemChild->Attribute("value");
	if(pszVal_wChallenge == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wChallenge, s.wChallenge))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wChallengeBuyTimes is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wChallengeBuyTimes") != 0)
	{
		LOG_CRI << "Attribute: name is not wChallengeBuyTimes!";
		return false;
	}
	const char* pszVal_wChallengeBuyTimes = pElemChild->Attribute("value");
	if(pszVal_wChallengeBuyTimes == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wChallengeBuyTimes, s.wChallengeBuyTimes))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wSelfReflush is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wSelfReflush") != 0)
	{
		LOG_CRI << "Attribute: name is not wSelfReflush!";
		return false;
	}
	const char* pszVal_wSelfReflush = pElemChild->Attribute("value");
	if(pszVal_wSelfReflush == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wSelfReflush, s.wSelfReflush))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wSelfFreeReflush is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wSelfFreeReflush") != 0)
	{
		LOG_CRI << "Attribute: name is not wSelfFreeReflush!";
		return false;
	}
	const char* pszVal_wSelfFreeReflush = pElemChild->Attribute("value");
	if(pszVal_wSelfFreeReflush == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wSelfFreeReflush, s.wSelfFreeReflush))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byArenaWirship is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byArenaWirship") != 0)
	{
		LOG_CRI << "Attribute: name is not byArenaWirship!";
		return false;
	}
	const char* pszVal_byArenaWirship = pElemChild->Attribute("value");
	if(pszVal_byArenaWirship == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byArenaWirship, s.byArenaWirship))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwLastLadderRank is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwLastLadderRank") != 0)
	{
		LOG_CRI << "Attribute: name is not dwLastLadderRank!";
		return false;
	}
	const char* pszVal_dwLastLadderRank = pElemChild->Attribute("value");
	if(pszVal_dwLastLadderRank == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwLastLadderRank, s.dwLastLadderRank))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwMinLadderRank is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwMinLadderRank") != 0)
	{
		LOG_CRI << "Attribute: name is not dwMinLadderRank!";
		return false;
	}
	const char* pszVal_dwMinLadderRank = pElemChild->Attribute("value");
	if(pszVal_dwMinLadderRank == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwMinLadderRank, s.dwMinLadderRank))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecFlushFigter is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecSFlushFitherForClient") != 0)
	{
		LOG_CRI << "pElemChild is not TVecSFlushFitherForClient!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecFlushFigter") != 0)
	{
		LOG_CRI << "Attribute: name is not vecFlushFigter!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecFlushFigter))
	{
		LOG_CRI << "VectorFromXML for vecFlushFigter fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecWirshipFigter is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecArenaRank2Client") != 0)
	{
		LOG_CRI << "pElemChild is not TVecArenaRank2Client!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecWirshipFigter") != 0)
	{
		LOG_CRI << "Attribute: name is not vecWirshipFigter!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecWirshipFigter))
	{
		LOG_CRI << "VectorFromXML for vecWirshipFigter fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwFighterPower is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwFighterPower") != 0)
	{
		LOG_CRI << "Attribute: name is not dwFighterPower!";
		return false;
	}
	const char* pszVal_dwFighterPower = pElemChild->Attribute("value");
	if(pszVal_dwFighterPower == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwFighterPower, s.dwFighterPower))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwLadderRank is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwLadderRank") != 0)
	{
		LOG_CRI << "Attribute: name is not dwLadderRank!";
		return false;
	}
	const char* pszVal_dwLadderRank = pElemChild->Attribute("value");
	if(pszVal_dwLadderRank == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwLadderRank, s.dwLadderRank))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wLadderChallenge is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wLadderChallenge") != 0)
	{
		LOG_CRI << "Attribute: name is not wLadderChallenge!";
		return false;
	}
	const char* pszVal_wLadderChallenge = pElemChild->Attribute("value");
	if(pszVal_wLadderChallenge == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wLadderChallenge, s.wLadderChallenge))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwArenaAward is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwArenaAward") != 0)
	{
		LOG_CRI << "Attribute: name is not dwArenaAward!";
		return false;
	}
	const char* pszVal_dwArenaAward = pElemChild->Attribute("value");
	if(pszVal_dwArenaAward == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwArenaAward, s.dwArenaAward))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwLadderBuyTimes is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwLadderBuyTimes") != 0)
	{
		LOG_CRI << "Attribute: name is not dwLadderBuyTimes!";
		return false;
	}
	const char* pszVal_dwLadderBuyTimes = pElemChild->Attribute("value");
	if(pszVal_dwLadderBuyTimes == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwLadderBuyTimes, s.dwLadderBuyTimes))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwLadderBuyTimesToday is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwLadderBuyTimesToday") != 0)
	{
		LOG_CRI << "Attribute: name is not dwLadderBuyTimesToday!";
		return false;
	}
	const char* pszVal_dwLadderBuyTimesToday = pElemChild->Attribute("value");
	if(pszVal_dwLadderBuyTimesToday == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwLadderBuyTimesToday, s.dwLadderBuyTimesToday))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SArenaPlayerBaseData2Client& s, TiXmlElement& rElement)
{
	rElement.SetValue("SArenaPlayerBaseData2Client");
	rElement.SetAttribute("type", ToUTF8Ptr("竞技场玩家基本信息，也是发给前端用的信息"));
	unique_ptr<TiXmlElement> pElem_dwRanking(new TiXmlElement("UINT32"));
	if(pElem_dwRanking == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwRanking->SetAttribute("name", "dwRanking");
	pElem_dwRanking->SetAttribute("value", NumberToString(s.dwRanking).c_str());
	pElem_dwRanking->SetAttribute("comment", ToUTF8Ptr("本段位排名"));
	if(rElement.LinkEndChild(pElem_dwRanking.get()) != NULL)
		pElem_dwRanking.release();
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
	unique_ptr<TiXmlElement> pElem_eLevel(new TiXmlElement("EArenaLevel"));
	if(pElem_eLevel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eLevel->SetAttribute("name", "eLevel");
	const char* pszEnum_eLevel = EnumValToStr(s.eLevel);
	if(pszEnum_eLevel == NULL)
	{
		LOG_CRI << "EnumValToStr for EArenaLevel fails!";
		return false;
	}
	pElem_eLevel->SetAttribute("value", pszEnum_eLevel);
	pElem_eLevel->SetAttribute("comment", ToUTF8Ptr("段位"));
	if(rElement.LinkEndChild(pElem_eLevel.get()) != NULL)
		pElem_eLevel.release();
	unique_ptr<TiXmlElement> pElem_dwTotalSize(new TiXmlElement("UINT32"));
	if(pElem_dwTotalSize == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwTotalSize->SetAttribute("name", "dwTotalSize");
	pElem_dwTotalSize->SetAttribute("value", NumberToString(s.dwTotalSize).c_str());
	pElem_dwTotalSize->SetAttribute("comment", ToUTF8Ptr("本段位总人数"));
	if(rElement.LinkEndChild(pElem_dwTotalSize.get()) != NULL)
		pElem_dwTotalSize.release();
	unique_ptr<TiXmlElement> pElem_ePreLevel(new TiXmlElement("EArenaLevel"));
	if(pElem_ePreLevel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_ePreLevel->SetAttribute("name", "ePreLevel");
	const char* pszEnum_ePreLevel = EnumValToStr(s.ePreLevel);
	if(pszEnum_ePreLevel == NULL)
	{
		LOG_CRI << "EnumValToStr for EArenaLevel fails!";
		return false;
	}
	pElem_ePreLevel->SetAttribute("value", pszEnum_ePreLevel);
	pElem_ePreLevel->SetAttribute("comment", ToUTF8Ptr("前次结算段位"));
	if(rElement.LinkEndChild(pElem_ePreLevel.get()) != NULL)
		pElem_ePreLevel.release();
	unique_ptr<TiXmlElement> pElem_dwPreRank(new TiXmlElement("UINT32"));
	if(pElem_dwPreRank == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwPreRank->SetAttribute("name", "dwPreRank");
	pElem_dwPreRank->SetAttribute("value", NumberToString(s.dwPreRank).c_str());
	pElem_dwPreRank->SetAttribute("comment", ToUTF8Ptr("前次结算排名"));
	if(rElement.LinkEndChild(pElem_dwPreRank.get()) != NULL)
		pElem_dwPreRank.release();
	unique_ptr<TiXmlElement> pElem_vecAwards(new TiXmlElement("TVecArenaAward"));
	if(pElem_vecAwards == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecAwards->SetAttribute("name", "vecAwards");
	if(!VectorToXML(s.vecAwards, *pElem_vecAwards))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecAwards->SetAttribute("comment", ToUTF8Ptr("奖励包状态"));
	if(rElement.LinkEndChild(pElem_vecAwards.get()) != NULL)
		pElem_vecAwards.release();
	unique_ptr<TiXmlElement> pElem_dwArenaCDTime(new TiXmlElement("UINT32"));
	if(pElem_dwArenaCDTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwArenaCDTime->SetAttribute("name", "dwArenaCDTime");
	pElem_dwArenaCDTime->SetAttribute("value", NumberToString(s.dwArenaCDTime).c_str());
	pElem_dwArenaCDTime->SetAttribute("comment", ToUTF8Ptr("历练冷却到期时间戳"));
	if(rElement.LinkEndChild(pElem_dwArenaCDTime.get()) != NULL)
		pElem_dwArenaCDTime.release();
	unique_ptr<TiXmlElement> pElem_dwLadderCDTime(new TiXmlElement("UINT32"));
	if(pElem_dwLadderCDTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwLadderCDTime->SetAttribute("name", "dwLadderCDTime");
	pElem_dwLadderCDTime->SetAttribute("value", NumberToString(s.dwLadderCDTime).c_str());
	pElem_dwLadderCDTime->SetAttribute("comment", ToUTF8Ptr("天梯冷却到期时间戳"));
	if(rElement.LinkEndChild(pElem_dwLadderCDTime.get()) != NULL)
		pElem_dwLadderCDTime.release();
	unique_ptr<TiXmlElement> pElem_wChallenge(new TiXmlElement("UINT16"));
	if(pElem_wChallenge == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wChallenge->SetAttribute("name", "wChallenge");
	pElem_wChallenge->SetAttribute("value", NumberToString(s.wChallenge).c_str());
	pElem_wChallenge->SetAttribute("comment", ToUTF8Ptr("当前挑战次数，每天0点清0"));
	if(rElement.LinkEndChild(pElem_wChallenge.get()) != NULL)
		pElem_wChallenge.release();
	unique_ptr<TiXmlElement> pElem_wChallengeBuyTimes(new TiXmlElement("UINT16"));
	if(pElem_wChallengeBuyTimes == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wChallengeBuyTimes->SetAttribute("name", "wChallengeBuyTimes");
	pElem_wChallengeBuyTimes->SetAttribute("value", NumberToString(s.wChallengeBuyTimes).c_str());
	pElem_wChallengeBuyTimes->SetAttribute("comment", ToUTF8Ptr("购买的挑战次数"));
	if(rElement.LinkEndChild(pElem_wChallengeBuyTimes.get()) != NULL)
		pElem_wChallengeBuyTimes.release();
	unique_ptr<TiXmlElement> pElem_wSelfReflush(new TiXmlElement("UINT16"));
	if(pElem_wSelfReflush == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wSelfReflush->SetAttribute("name", "wSelfReflush");
	pElem_wSelfReflush->SetAttribute("value", NumberToString(s.wSelfReflush).c_str());
	pElem_wSelfReflush->SetAttribute("comment", ToUTF8Ptr("当前购买刷新次数"));
	if(rElement.LinkEndChild(pElem_wSelfReflush.get()) != NULL)
		pElem_wSelfReflush.release();
	unique_ptr<TiXmlElement> pElem_wSelfFreeReflush(new TiXmlElement("UINT16"));
	if(pElem_wSelfFreeReflush == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wSelfFreeReflush->SetAttribute("name", "wSelfFreeReflush");
	pElem_wSelfFreeReflush->SetAttribute("value", NumberToString(s.wSelfFreeReflush).c_str());
	pElem_wSelfFreeReflush->SetAttribute("comment", ToUTF8Ptr("当前VIP免费刷新次数"));
	if(rElement.LinkEndChild(pElem_wSelfFreeReflush.get()) != NULL)
		pElem_wSelfFreeReflush.release();
	unique_ptr<TiXmlElement> pElem_byArenaWirship(new TiXmlElement("UINT8"));
	if(pElem_byArenaWirship == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byArenaWirship->SetAttribute("name", "byArenaWirship");
	pElem_byArenaWirship->SetAttribute("value", NumberToString(s.byArenaWirship).c_str());
	pElem_byArenaWirship->SetAttribute("comment", ToUTF8Ptr("膜拜次数"));
	if(rElement.LinkEndChild(pElem_byArenaWirship.get()) != NULL)
		pElem_byArenaWirship.release();
	unique_ptr<TiXmlElement> pElem_dwLastLadderRank(new TiXmlElement("UINT32"));
	if(pElem_dwLastLadderRank == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwLastLadderRank->SetAttribute("name", "dwLastLadderRank");
	pElem_dwLastLadderRank->SetAttribute("value", NumberToString(s.dwLastLadderRank).c_str());
	pElem_dwLastLadderRank->SetAttribute("comment", ToUTF8Ptr("上次结算天梯排名，0表示排名"));
	if(rElement.LinkEndChild(pElem_dwLastLadderRank.get()) != NULL)
		pElem_dwLastLadderRank.release();
	unique_ptr<TiXmlElement> pElem_dwMinLadderRank(new TiXmlElement("UINT32"));
	if(pElem_dwMinLadderRank == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwMinLadderRank->SetAttribute("name", "dwMinLadderRank");
	pElem_dwMinLadderRank->SetAttribute("value", NumberToString(s.dwMinLadderRank).c_str());
	pElem_dwMinLadderRank->SetAttribute("comment", ToUTF8Ptr("天梯最好排名,0表示无排名"));
	if(rElement.LinkEndChild(pElem_dwMinLadderRank.get()) != NULL)
		pElem_dwMinLadderRank.release();
	unique_ptr<TiXmlElement> pElem_vecFlushFigter(new TiXmlElement("TVecSFlushFitherForClient"));
	if(pElem_vecFlushFigter == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecFlushFigter->SetAttribute("name", "vecFlushFigter");
	if(!VectorToXML(s.vecFlushFigter, *pElem_vecFlushFigter))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecFlushFigter->SetAttribute("comment", ToUTF8Ptr("最近刷的对手"));
	if(rElement.LinkEndChild(pElem_vecFlushFigter.get()) != NULL)
		pElem_vecFlushFigter.release();
	unique_ptr<TiXmlElement> pElem_vecWirshipFigter(new TiXmlElement("TVecArenaRank2Client"));
	if(pElem_vecWirshipFigter == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecWirshipFigter->SetAttribute("name", "vecWirshipFigter");
	if(!VectorToXML(s.vecWirshipFigter, *pElem_vecWirshipFigter))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecWirshipFigter->SetAttribute("comment", ToUTF8Ptr("膜拜对象列表"));
	if(rElement.LinkEndChild(pElem_vecWirshipFigter.get()) != NULL)
		pElem_vecWirshipFigter.release();
	unique_ptr<TiXmlElement> pElem_dwFighterPower(new TiXmlElement("UINT32"));
	if(pElem_dwFighterPower == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwFighterPower->SetAttribute("name", "dwFighterPower");
	pElem_dwFighterPower->SetAttribute("value", NumberToString(s.dwFighterPower).c_str());
	pElem_dwFighterPower->SetAttribute("comment", ToUTF8Ptr("战斗力"));
	if(rElement.LinkEndChild(pElem_dwFighterPower.get()) != NULL)
		pElem_dwFighterPower.release();
	unique_ptr<TiXmlElement> pElem_dwLadderRank(new TiXmlElement("UINT32"));
	if(pElem_dwLadderRank == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwLadderRank->SetAttribute("name", "dwLadderRank");
	pElem_dwLadderRank->SetAttribute("value", NumberToString(s.dwLadderRank).c_str());
	pElem_dwLadderRank->SetAttribute("comment", ToUTF8Ptr("天梯排名，0表示未参与天梯，9999表示已经与机器战斗，但是不计入排名，否者为真实排名"));
	if(rElement.LinkEndChild(pElem_dwLadderRank.get()) != NULL)
		pElem_dwLadderRank.release();
	unique_ptr<TiXmlElement> pElem_wLadderChallenge(new TiXmlElement("UINT16"));
	if(pElem_wLadderChallenge == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wLadderChallenge->SetAttribute("name", "wLadderChallenge");
	pElem_wLadderChallenge->SetAttribute("value", NumberToString(s.wLadderChallenge).c_str());
	pElem_wLadderChallenge->SetAttribute("comment", ToUTF8Ptr("天梯挑战次数"));
	if(rElement.LinkEndChild(pElem_wLadderChallenge.get()) != NULL)
		pElem_wLadderChallenge.release();
	unique_ptr<TiXmlElement> pElem_dwArenaAward(new TiXmlElement("UINT32"));
	if(pElem_dwArenaAward == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwArenaAward->SetAttribute("name", "dwArenaAward");
	pElem_dwArenaAward->SetAttribute("value", NumberToString(s.dwArenaAward).c_str());
	pElem_dwArenaAward->SetAttribute("comment", ToUTF8Ptr("历练挑战奖励，天梯挑战奖励领取状况，右到左1位历练，2位天梯"));
	if(rElement.LinkEndChild(pElem_dwArenaAward.get()) != NULL)
		pElem_dwArenaAward.release();
	unique_ptr<TiXmlElement> pElem_dwLadderBuyTimes(new TiXmlElement("UINT32"));
	if(pElem_dwLadderBuyTimes == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwLadderBuyTimes->SetAttribute("name", "dwLadderBuyTimes");
	pElem_dwLadderBuyTimes->SetAttribute("value", NumberToString(s.dwLadderBuyTimes).c_str());
	pElem_dwLadderBuyTimes->SetAttribute("comment", ToUTF8Ptr("购买的天梯挑战次数"));
	if(rElement.LinkEndChild(pElem_dwLadderBuyTimes.get()) != NULL)
		pElem_dwLadderBuyTimes.release();
	unique_ptr<TiXmlElement> pElem_dwLadderBuyTimesToday(new TiXmlElement("UINT32"));
	if(pElem_dwLadderBuyTimesToday == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwLadderBuyTimesToday->SetAttribute("name", "dwLadderBuyTimesToday");
	pElem_dwLadderBuyTimesToday->SetAttribute("value", NumberToString(s.dwLadderBuyTimesToday).c_str());
	pElem_dwLadderBuyTimesToday->SetAttribute("comment", ToUTF8Ptr("今日购买的天梯挑战次数"));
	if(rElement.LinkEndChild(pElem_dwLadderBuyTimesToday.get()) != NULL)
		pElem_dwLadderBuyTimesToday.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecArenaPlayerBaseData2Client& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SArenaPlayerBaseData2Client s;
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

bool VectorToXML(const TVecArenaPlayerBaseData2Client& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SArenaPlayerBaseData2Client"));
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

} //namespace NArenaGS
