/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    Game2CenterComm.cpp
//  Purpose:      GameServer到CenterServer的通信协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "Game2CenterComm.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NGame2CenterComm
{

#ifdef PROT_USE_XML

const char* EnumValToStr(ESyncKey e)
{
	switch(e)
	{
	case eSyncNone:
		return "eSyncNone";
	case eSyncGameSvrC2S:
		return "eSyncGameSvrC2S";
	case eSyncGameSvrS2C:
		return "eSyncGameSvrS2C";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, ESyncKey& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, ESyncKey> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eSyncNone", eSyncNone));
		mapStr2Val.insert(make_pair("eSyncGameSvrC2S", eSyncGameSvrC2S));
		mapStr2Val.insert(make_pair("eSyncGameSvrS2C", eSyncGameSvrS2C));
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

const char* EnumValToStr(EUserSyncPropField e)
{
	switch(e)
	{
	case eSyncPropLevel:
		return "eSyncPropLevel";
	case eSyncPropNation:
		return "eSyncPropNation";
	case eSyncPropYellowDiamond:
		return "eSyncPropYellowDiamond";
	case eSyncPropGold:
		return "eSyncPropGold";
	case eSyncPropSilver:
		return "eSyncPropSilver";
	case eSyncPropCoupon:
		return "eSyncPropCoupon";
	case eSyncPropbyTitle:
		return "eSyncPropbyTitle";
	case eSyncPropbyWallow:
		return "eSyncPropbyWallow";
	case eSyncPropVIPLevel:
		return "eSyncPropVIPLevel";
	case eSyncPropQuality:
		return "eSyncPropQuality";
	case eSyncPropPlayerFighterID:
		return "eSyncPropPlayerFighterID";
	case eSyncPropTotalRecharge:
		return "eSyncPropTotalRecharge";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EUserSyncPropField& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EUserSyncPropField> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eSyncPropLevel", eSyncPropLevel));
		mapStr2Val.insert(make_pair("eSyncPropNation", eSyncPropNation));
		mapStr2Val.insert(make_pair("eSyncPropYellowDiamond", eSyncPropYellowDiamond));
		mapStr2Val.insert(make_pair("eSyncPropGold", eSyncPropGold));
		mapStr2Val.insert(make_pair("eSyncPropSilver", eSyncPropSilver));
		mapStr2Val.insert(make_pair("eSyncPropCoupon", eSyncPropCoupon));
		mapStr2Val.insert(make_pair("eSyncPropbyTitle", eSyncPropbyTitle));
		mapStr2Val.insert(make_pair("eSyncPropbyWallow", eSyncPropbyWallow));
		mapStr2Val.insert(make_pair("eSyncPropVIPLevel", eSyncPropVIPLevel));
		mapStr2Val.insert(make_pair("eSyncPropQuality", eSyncPropQuality));
		mapStr2Val.insert(make_pair("eSyncPropPlayerFighterID", eSyncPropPlayerFighterID));
		mapStr2Val.insert(make_pair("eSyncPropTotalRecharge", eSyncPropTotalRecharge));
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

const char* EnumValToStr(EOpSource e)
{
	switch(e)
	{
	case eOpAreaAward:
		return "eOpAreaAward";
	case eOpAreaFlush:
		return "eOpAreaFlush";
	case eOpClearAreaCd:
		return "eOpClearAreaCd";
	case eOpArenaWirship:
		return "eOpArenaWirship";
	case eOpGuildDonate:
		return "eOpGuildDonate";
	case eOpGuildWorship:
		return "eOpGuildWorship";
	case eOpBuyAreaTimes:
		return "eOpBuyAreaTimes";
	case eOpLadderAward:
		return "eOpLadderAward";
	case eOpAreaAwardDays:
		return "eOpAreaAwardDays";
	case eOpClearLadderCd:
		return "eOpClearLadderCd";
	case eOpAdoreAward:
		return "eOpAdoreAward";
	case eOpTripodAward:
		return "eOpTripodAward";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EOpSource& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EOpSource> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eOpAreaAward", eOpAreaAward));
		mapStr2Val.insert(make_pair("eOpAreaFlush", eOpAreaFlush));
		mapStr2Val.insert(make_pair("eOpClearAreaCd", eOpClearAreaCd));
		mapStr2Val.insert(make_pair("eOpArenaWirship", eOpArenaWirship));
		mapStr2Val.insert(make_pair("eOpGuildDonate", eOpGuildDonate));
		mapStr2Val.insert(make_pair("eOpGuildWorship", eOpGuildWorship));
		mapStr2Val.insert(make_pair("eOpBuyAreaTimes", eOpBuyAreaTimes));
		mapStr2Val.insert(make_pair("eOpLadderAward", eOpLadderAward));
		mapStr2Val.insert(make_pair("eOpAreaAwardDays", eOpAreaAwardDays));
		mapStr2Val.insert(make_pair("eOpClearLadderCd", eOpClearLadderCd));
		mapStr2Val.insert(make_pair("eOpAdoreAward", eOpAdoreAward));
		mapStr2Val.insert(make_pair("eOpTripodAward", eOpTripodAward));
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

const char* EnumValToStr(EUpdateError e)
{
	switch(e)
	{
	case eUpdateErrorNoUser:
		return "eUpdateErrorNoUser";
	case eUpdateErrorItemCount:
		return "eUpdateErrorItemCount";
	case eUpdateErrorMoneyCount:
		return "eUpdateErrorMoneyCount";
	case eUpdateErrorUnKown:
		return "eUpdateErrorUnKown";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EUpdateError& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EUpdateError> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eUpdateErrorNoUser", eUpdateErrorNoUser));
		mapStr2Val.insert(make_pair("eUpdateErrorItemCount", eUpdateErrorItemCount));
		mapStr2Val.insert(make_pair("eUpdateErrorMoneyCount", eUpdateErrorMoneyCount));
		mapStr2Val.insert(make_pair("eUpdateErrorUnKown", eUpdateErrorUnKown));
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

const char* EnumValToStr(EPlayerUINTProp e)
{
	switch(e)
	{
	case ePropTopDemonFloorID:
		return "ePropTopDemonFloorID";
	case ePropPrizeDemonFloorID:
		return "ePropPrizeDemonFloorID";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EPlayerUINTProp& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EPlayerUINTProp> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("ePropTopDemonFloorID", ePropTopDemonFloorID));
		mapStr2Val.insert(make_pair("ePropPrizeDemonFloorID", ePropPrizeDemonFloorID));
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

const char* EnumValToStr(EWonderActType e)
{
	switch(e)
	{
	case eActTrump:
		return "eActTrump";
	case eActLevel:
		return "eActLevel";
	case eActFighter:
		return "eActFighter";
	case eActFormation:
		return "eActFormation";
	case eActDungon:
		return "eActDungon";
	case eActBeauty:
		return "eActBeauty";
	case eActHorse:
		return "eActHorse";
	case eActEnd:
		return "eActEnd";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EWonderActType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EWonderActType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eActTrump", eActTrump));
		mapStr2Val.insert(make_pair("eActLevel", eActLevel));
		mapStr2Val.insert(make_pair("eActFighter", eActFighter));
		mapStr2Val.insert(make_pair("eActFormation", eActFormation));
		mapStr2Val.insert(make_pair("eActDungon", eActDungon));
		mapStr2Val.insert(make_pair("eActBeauty", eActBeauty));
		mapStr2Val.insert(make_pair("eActHorse", eActHorse));
		mapStr2Val.insert(make_pair("eActEnd", eActEnd));
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

const char* EnumValToStr(ActiveParam e)
{
	switch(e)
	{
	case eShip:
		return "eShip";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, ActiveParam& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, ActiveParam> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eShip", eShip));
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

SUserItem::SUserItem() : dwTypeID(0), dwCount(0) { }

SUserItem::SUserItem(UINT32 dwTypeID_, UINT32 dwCount_) : dwTypeID(dwTypeID_), dwCount(dwCount_) { }

CInArchive& operator>>(CInArchive& src, SUserItem& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.dwTypeID;
	src >> s.dwCount;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SUserItem& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.dwTypeID;
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

bool FromXML(TiXmlElement& rElement, SUserItem& s)
{
	if(strcmp(rElement.Value(), "SUserItem") != 0)
	{
		LOG_CRI << "rElement is not SUserItem!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwTypeID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwTypeID") != 0)
	{
		LOG_CRI << "Attribute: name is not dwTypeID!";
		return false;
	}
	const char* pszVal_dwTypeID = pElemChild->Attribute("value");
	if(pszVal_dwTypeID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwTypeID, s.dwTypeID))
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

bool ToXML(const SUserItem& s, TiXmlElement& rElement)
{
	rElement.SetValue("SUserItem");
	rElement.SetAttribute("type", ToUTF8Ptr("物品信息"));
	unique_ptr<TiXmlElement> pElem_dwTypeID(new TiXmlElement("UINT32"));
	if(pElem_dwTypeID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwTypeID->SetAttribute("name", "dwTypeID");
	pElem_dwTypeID->SetAttribute("value", NumberToString(s.dwTypeID).c_str());
	pElem_dwTypeID->SetAttribute("comment", ToUTF8Ptr("物品ID/钱币类型"));
	if(rElement.LinkEndChild(pElem_dwTypeID.get()) != NULL)
		pElem_dwTypeID.release();
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

bool VectorFromXML(TiXmlElement& rElement, TVecUserItem& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SUserItem s;
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

bool VectorToXML(const TVecUserItem& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SUserItem"));
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

SUserEnterInfo::SUserEnterInfo() : wHeroID(0), eSex((NProtoCommon::ESexType)0), eCareer((NProtoCommon::ECareerType)0), byLevel(0), byNation(0), 
			byGMLvl(0), dwTotalRecharge(0), dwCreateTime(0), dwLoginTime(0), dwOfflineTime(0), 
			dwLockExpireTime(0), dwForbExpireTime(0), dwGold(0), dwSilver(0), dwCoupon(0), 
			dwSoul(0), dwPrestige(0), dwHonor(0), dwPExp(0), dwSigil(0), 
			dwCentsY(0), dwAction(0), dwSop(0), dwBTPoint(0), byDomain(0), 
			byDomainLvl(0), byDisplayLvl(0), byDomainYear(0), qwInvitedID(0), byWallow(0), 
			byVIPLvl(0), byYDLvl(0), wMood(0), dwFighterPower(0), byQuality(0), 
			wPlayerFighterID(0) { }

CInArchive& operator>>(CInArchive& src, SUserEnterInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.wHeroID;
	src >> (UINT8&)s.eSex;
	src >> (UINT8&)s.eCareer;
	src >> s.strName;
	src >> s.byLevel;
	src >> s.byNation;
	src >> s.byGMLvl;
	src >> s.dwTotalRecharge;
	src >> s.dwCreateTime;
	src >> s.dwLoginTime;
	src >> s.dwOfflineTime;
	src >> s.dwLockExpireTime;
	src >> s.dwForbExpireTime;
	src >> s.dwGold;
	src >> s.dwSilver;
	src >> s.dwCoupon;
	src >> s.dwSoul;
	src >> s.dwPrestige;
	src >> s.dwHonor;
	src >> s.dwPExp;
	src >> s.dwSigil;
	src >> s.dwCentsY;
	src >> s.dwAction;
	src >> s.dwSop;
	src >> s.dwBTPoint;
	src >> s.vecOwnTitle;
	src >> s.vecEquipTitle;
	src >> s.byDomain;
	src >> s.byDomainLvl;
	src >> s.byDisplayLvl;
	src >> s.byDomainYear;
	src >> s.szOpenId;
	src >> s.szOpenKey;
	src >> s.qwInvitedID;
	src >> s.byWallow;
	src >> s.byVIPLvl;
	src >> s.byYDLvl;
	src >> s.strSign;
	src >> s.wMood;
	src >> s.dwFighterPower;
	src >> s.byQuality;
	src >> s.wPlayerFighterID;
	src >> s.vecFriendsInfo;
	src >> s.vecGameVars;
	src >> s.vecArenaInfo;
	src >> s.vecFireInfo;
	src >> s.szIconAppear;
	src >> s.vecPlatform;
	src >> s.vecShipReport;
	src >> s.sShipData;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SUserEnterInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.wHeroID;
	src << (UINT8&)s.eSex;
	src << (UINT8&)s.eCareer;
	src << s.strName;
	src << s.byLevel;
	src << s.byNation;
	src << s.byGMLvl;
	src << s.dwTotalRecharge;
	src << s.dwCreateTime;
	src << s.dwLoginTime;
	src << s.dwOfflineTime;
	src << s.dwLockExpireTime;
	src << s.dwForbExpireTime;
	src << s.dwGold;
	src << s.dwSilver;
	src << s.dwCoupon;
	src << s.dwSoul;
	src << s.dwPrestige;
	src << s.dwHonor;
	src << s.dwPExp;
	src << s.dwSigil;
	src << s.dwCentsY;
	src << s.dwAction;
	src << s.dwSop;
	src << s.dwBTPoint;
	src << s.vecOwnTitle;
	src << s.vecEquipTitle;
	src << s.byDomain;
	src << s.byDomainLvl;
	src << s.byDisplayLvl;
	src << s.byDomainYear;
	src << s.szOpenId;
	src << s.szOpenKey;
	src << s.qwInvitedID;
	src << s.byWallow;
	src << s.byVIPLvl;
	src << s.byYDLvl;
	src << s.strSign;
	src << s.wMood;
	src << s.dwFighterPower;
	src << s.byQuality;
	src << s.wPlayerFighterID;
	src << s.vecFriendsInfo;
	src << s.vecGameVars;
	src << s.vecArenaInfo;
	src << s.vecFireInfo;
	src << s.szIconAppear;
	src << s.vecPlatform;
	src << s.vecShipReport;
	src << s.sShipData;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SUserEnterInfo& s)
{
	if(strcmp(rElement.Value(), "SUserEnterInfo") != 0)
	{
		LOG_CRI << "rElement is not SUserEnterInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wHeroID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wHeroID") != 0)
	{
		LOG_CRI << "Attribute: name is not wHeroID!";
		return false;
	}
	const char* pszVal_wHeroID = pElemChild->Attribute("value");
	if(pszVal_wHeroID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wHeroID, s.wHeroID))
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
		LOG_CRI << "pElemChild for byNation is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byNation") != 0)
	{
		LOG_CRI << "Attribute: name is not byNation!";
		return false;
	}
	const char* pszVal_byNation = pElemChild->Attribute("value");
	if(pszVal_byNation == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byNation, s.byNation))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byGMLvl is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byGMLvl") != 0)
	{
		LOG_CRI << "Attribute: name is not byGMLvl!";
		return false;
	}
	const char* pszVal_byGMLvl = pElemChild->Attribute("value");
	if(pszVal_byGMLvl == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byGMLvl, s.byGMLvl))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwTotalRecharge is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwTotalRecharge") != 0)
	{
		LOG_CRI << "Attribute: name is not dwTotalRecharge!";
		return false;
	}
	const char* pszVal_dwTotalRecharge = pElemChild->Attribute("value");
	if(pszVal_dwTotalRecharge == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwTotalRecharge, s.dwTotalRecharge))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwCreateTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwCreateTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwCreateTime!";
		return false;
	}
	const char* pszVal_dwCreateTime = pElemChild->Attribute("value");
	if(pszVal_dwCreateTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwCreateTime, s.dwCreateTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwLoginTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwLoginTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwLoginTime!";
		return false;
	}
	const char* pszVal_dwLoginTime = pElemChild->Attribute("value");
	if(pszVal_dwLoginTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwLoginTime, s.dwLoginTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwOfflineTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwOfflineTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwOfflineTime!";
		return false;
	}
	const char* pszVal_dwOfflineTime = pElemChild->Attribute("value");
	if(pszVal_dwOfflineTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwOfflineTime, s.dwOfflineTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwLockExpireTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwLockExpireTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwLockExpireTime!";
		return false;
	}
	const char* pszVal_dwLockExpireTime = pElemChild->Attribute("value");
	if(pszVal_dwLockExpireTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwLockExpireTime, s.dwLockExpireTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwForbExpireTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwForbExpireTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwForbExpireTime!";
		return false;
	}
	const char* pszVal_dwForbExpireTime = pElemChild->Attribute("value");
	if(pszVal_dwForbExpireTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwForbExpireTime, s.dwForbExpireTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwGold is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwGold") != 0)
	{
		LOG_CRI << "Attribute: name is not dwGold!";
		return false;
	}
	const char* pszVal_dwGold = pElemChild->Attribute("value");
	if(pszVal_dwGold == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwGold, s.dwGold))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwSilver is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwSilver") != 0)
	{
		LOG_CRI << "Attribute: name is not dwSilver!";
		return false;
	}
	const char* pszVal_dwSilver = pElemChild->Attribute("value");
	if(pszVal_dwSilver == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwSilver, s.dwSilver))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwCoupon is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwCoupon") != 0)
	{
		LOG_CRI << "Attribute: name is not dwCoupon!";
		return false;
	}
	const char* pszVal_dwCoupon = pElemChild->Attribute("value");
	if(pszVal_dwCoupon == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwCoupon, s.dwCoupon))
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
		LOG_CRI << "pElemChild for dwPrestige is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwPrestige") != 0)
	{
		LOG_CRI << "Attribute: name is not dwPrestige!";
		return false;
	}
	const char* pszVal_dwPrestige = pElemChild->Attribute("value");
	if(pszVal_dwPrestige == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwPrestige, s.dwPrestige))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwHonor is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwHonor") != 0)
	{
		LOG_CRI << "Attribute: name is not dwHonor!";
		return false;
	}
	const char* pszVal_dwHonor = pElemChild->Attribute("value");
	if(pszVal_dwHonor == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwHonor, s.dwHonor))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwPExp is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwPExp") != 0)
	{
		LOG_CRI << "Attribute: name is not dwPExp!";
		return false;
	}
	const char* pszVal_dwPExp = pElemChild->Attribute("value");
	if(pszVal_dwPExp == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwPExp, s.dwPExp))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwSigil is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwSigil") != 0)
	{
		LOG_CRI << "Attribute: name is not dwSigil!";
		return false;
	}
	const char* pszVal_dwSigil = pElemChild->Attribute("value");
	if(pszVal_dwSigil == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwSigil, s.dwSigil))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwCentsY is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwCentsY") != 0)
	{
		LOG_CRI << "Attribute: name is not dwCentsY!";
		return false;
	}
	const char* pszVal_dwCentsY = pElemChild->Attribute("value");
	if(pszVal_dwCentsY == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwCentsY, s.dwCentsY))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwAction is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwAction") != 0)
	{
		LOG_CRI << "Attribute: name is not dwAction!";
		return false;
	}
	const char* pszVal_dwAction = pElemChild->Attribute("value");
	if(pszVal_dwAction == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwAction, s.dwAction))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwSop is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwSop") != 0)
	{
		LOG_CRI << "Attribute: name is not dwSop!";
		return false;
	}
	const char* pszVal_dwSop = pElemChild->Attribute("value");
	if(pszVal_dwSop == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwSop, s.dwSop))
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
		LOG_CRI << "pElemChild for vecOwnTitle is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecUINT16") != 0)
	{
		LOG_CRI << "pElemChild is not TVecUINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecOwnTitle") != 0)
	{
		LOG_CRI << "Attribute: name is not vecOwnTitle!";
		return false;
	}
	const char* pszText_vecOwnTitle = pElemChild->GetText();
	if(pszText_vecOwnTitle != NULL)
		SplitToNumber(pszText_vecOwnTitle, ",", s.vecOwnTitle);
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecEquipTitle is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecUINT16") != 0)
	{
		LOG_CRI << "pElemChild is not TVecUINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecEquipTitle") != 0)
	{
		LOG_CRI << "Attribute: name is not vecEquipTitle!";
		return false;
	}
	const char* pszText_vecEquipTitle = pElemChild->GetText();
	if(pszText_vecEquipTitle != NULL)
		SplitToNumber(pszText_vecEquipTitle, ",", s.vecEquipTitle);
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byDomain is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byDomain") != 0)
	{
		LOG_CRI << "Attribute: name is not byDomain!";
		return false;
	}
	const char* pszVal_byDomain = pElemChild->Attribute("value");
	if(pszVal_byDomain == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byDomain, s.byDomain))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byDomainLvl is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byDomainLvl") != 0)
	{
		LOG_CRI << "Attribute: name is not byDomainLvl!";
		return false;
	}
	const char* pszVal_byDomainLvl = pElemChild->Attribute("value");
	if(pszVal_byDomainLvl == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byDomainLvl, s.byDomainLvl))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byDisplayLvl is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byDisplayLvl") != 0)
	{
		LOG_CRI << "Attribute: name is not byDisplayLvl!";
		return false;
	}
	const char* pszVal_byDisplayLvl = pElemChild->Attribute("value");
	if(pszVal_byDisplayLvl == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byDisplayLvl, s.byDisplayLvl))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byDomainYear is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byDomainYear") != 0)
	{
		LOG_CRI << "Attribute: name is not byDomainYear!";
		return false;
	}
	const char* pszVal_byDomainYear = pElemChild->Attribute("value");
	if(pszVal_byDomainYear == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byDomainYear, s.byDomainYear))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for szOpenId is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "szOpenId") != 0)
	{
		LOG_CRI << "Attribute: name is not szOpenId!";
		return false;
	}
	const char* pszVal_szOpenId = pElemChild->Attribute("value");
	if(pszVal_szOpenId == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.szOpenId = pszVal_szOpenId;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for szOpenKey is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "szOpenKey") != 0)
	{
		LOG_CRI << "Attribute: name is not szOpenKey!";
		return false;
	}
	const char* pszVal_szOpenKey = pElemChild->Attribute("value");
	if(pszVal_szOpenKey == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.szOpenKey = pszVal_szOpenKey;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwInvitedID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwInvitedID") != 0)
	{
		LOG_CRI << "Attribute: name is not qwInvitedID!";
		return false;
	}
	const char* pszVal_qwInvitedID = pElemChild->Attribute("value");
	if(pszVal_qwInvitedID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwInvitedID, s.qwInvitedID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byWallow is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byWallow") != 0)
	{
		LOG_CRI << "Attribute: name is not byWallow!";
		return false;
	}
	const char* pszVal_byWallow = pElemChild->Attribute("value");
	if(pszVal_byWallow == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byWallow, s.byWallow))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byVIPLvl is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byVIPLvl") != 0)
	{
		LOG_CRI << "Attribute: name is not byVIPLvl!";
		return false;
	}
	const char* pszVal_byVIPLvl = pElemChild->Attribute("value");
	if(pszVal_byVIPLvl == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byVIPLvl, s.byVIPLvl))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byYDLvl is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byYDLvl") != 0)
	{
		LOG_CRI << "Attribute: name is not byYDLvl!";
		return false;
	}
	const char* pszVal_byYDLvl = pElemChild->Attribute("value");
	if(pszVal_byYDLvl == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byYDLvl, s.byYDLvl))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strSign is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strSign") != 0)
	{
		LOG_CRI << "Attribute: name is not strSign!";
		return false;
	}
	const char* pszVal_strSign = pElemChild->Attribute("value");
	if(pszVal_strSign == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strSign = pszVal_strSign;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wMood is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wMood") != 0)
	{
		LOG_CRI << "Attribute: name is not wMood!";
		return false;
	}
	const char* pszVal_wMood = pElemChild->Attribute("value");
	if(pszVal_wMood == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wMood, s.wMood))
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
		LOG_CRI << "pElemChild for vecFriendsInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "FriendProt::TVecFriendDBInfo") != 0)
	{
		LOG_CRI << "pElemChild is not FriendProt::TVecFriendDBInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecFriendsInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not vecFriendsInfo!";
		return false;
	}
	if(!NFriendProt::VectorFromXML(*pElemChild, s.vecFriendsInfo))
	{
		LOG_CRI << "VectorFromXML for vecFriendsInfo fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecGameVars is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "RoleInfoDefine::TVecVarsDBInfo") != 0)
	{
		LOG_CRI << "pElemChild is not RoleInfoDefine::TVecVarsDBInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecGameVars") != 0)
	{
		LOG_CRI << "Attribute: name is not vecGameVars!";
		return false;
	}
	if(!NRoleInfoDefine::VectorFromXML(*pElemChild, s.vecGameVars))
	{
		LOG_CRI << "VectorFromXML for vecGameVars fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecArenaInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "RoleInfoDefine::TVecRoleArenaInfo") != 0)
	{
		LOG_CRI << "pElemChild is not RoleInfoDefine::TVecRoleArenaInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecArenaInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not vecArenaInfo!";
		return false;
	}
	if(!NRoleInfoDefine::VectorFromXML(*pElemChild, s.vecArenaInfo))
	{
		LOG_CRI << "VectorFromXML for vecArenaInfo fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecFireInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TripodProt::TVecFireInfo") != 0)
	{
		LOG_CRI << "pElemChild is not TripodProt::TVecFireInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecFireInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not vecFireInfo!";
		return false;
	}
	if(!NTripodProt::VectorFromXML(*pElemChild, s.vecFireInfo))
	{
		LOG_CRI << "VectorFromXML for vecFireInfo fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for szIconAppear is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "szIconAppear") != 0)
	{
		LOG_CRI << "Attribute: name is not szIconAppear!";
		return false;
	}
	const char* pszVal_szIconAppear = pElemChild->Attribute("value");
	if(pszVal_szIconAppear == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.szIconAppear = pszVal_szIconAppear;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecPlatform is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "ProtoCommon::TVecPlatformParam") != 0)
	{
		LOG_CRI << "pElemChild is not ProtoCommon::TVecPlatformParam!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecPlatform") != 0)
	{
		LOG_CRI << "Attribute: name is not vecPlatform!";
		return false;
	}
	if(!NProtoCommon::VectorFromXML(*pElemChild, s.vecPlatform))
	{
		LOG_CRI << "VectorFromXML for vecPlatform fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecShipReport is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "ShipProt::TVecShipReport") != 0)
	{
		LOG_CRI << "pElemChild is not ShipProt::TVecShipReport!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecShipReport") != 0)
	{
		LOG_CRI << "Attribute: name is not vecShipReport!";
		return false;
	}
	if(!NShipProt::VectorFromXML(*pElemChild, s.vecShipReport))
	{
		LOG_CRI << "VectorFromXML for vecShipReport fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for sShipData is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "ShipProt::PlayerSelfShipData") != 0)
	{
		LOG_CRI << "pElemChild is not ShipProt::PlayerSelfShipData!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "sShipData") != 0)
	{
		LOG_CRI << "Attribute: name is not sShipData!";
		return false;
	}
	if(!FromXML(*pElemChild, s.sShipData))
	{
		LOG_CRI << "FromXML for: sShipData fails!";
		return false;
	}
	return true;
}

bool ToXML(const SUserEnterInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SUserEnterInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("角色进入游戏信息"));
	unique_ptr<TiXmlElement> pElem_wHeroID(new TiXmlElement("UINT16"));
	if(pElem_wHeroID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wHeroID->SetAttribute("name", "wHeroID");
	pElem_wHeroID->SetAttribute("value", NumberToString(s.wHeroID).c_str());
	pElem_wHeroID->SetAttribute("comment", ToUTF8Ptr("主将ID"));
	if(rElement.LinkEndChild(pElem_wHeroID.get()) != NULL)
		pElem_wHeroID.release();
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
	pElem_eSex->SetAttribute("comment", ToUTF8Ptr("性别"));
	if(rElement.LinkEndChild(pElem_eSex.get()) != NULL)
		pElem_eSex.release();
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
	unique_ptr<TiXmlElement> pElem_byNation(new TiXmlElement("UINT8"));
	if(pElem_byNation == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byNation->SetAttribute("name", "byNation");
	pElem_byNation->SetAttribute("value", NumberToString(s.byNation).c_str());
	pElem_byNation->SetAttribute("comment", ToUTF8Ptr("国家"));
	if(rElement.LinkEndChild(pElem_byNation.get()) != NULL)
		pElem_byNation.release();
	unique_ptr<TiXmlElement> pElem_byGMLvl(new TiXmlElement("UINT8"));
	if(pElem_byGMLvl == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byGMLvl->SetAttribute("name", "byGMLvl");
	pElem_byGMLvl->SetAttribute("value", NumberToString(s.byGMLvl).c_str());
	pElem_byGMLvl->SetAttribute("comment", ToUTF8Ptr("GM权限"));
	if(rElement.LinkEndChild(pElem_byGMLvl.get()) != NULL)
		pElem_byGMLvl.release();
	unique_ptr<TiXmlElement> pElem_dwTotalRecharge(new TiXmlElement("UINT32"));
	if(pElem_dwTotalRecharge == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwTotalRecharge->SetAttribute("name", "dwTotalRecharge");
	pElem_dwTotalRecharge->SetAttribute("value", NumberToString(s.dwTotalRecharge).c_str());
	pElem_dwTotalRecharge->SetAttribute("comment", ToUTF8Ptr("充值金额"));
	if(rElement.LinkEndChild(pElem_dwTotalRecharge.get()) != NULL)
		pElem_dwTotalRecharge.release();
	unique_ptr<TiXmlElement> pElem_dwCreateTime(new TiXmlElement("UINT32"));
	if(pElem_dwCreateTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwCreateTime->SetAttribute("name", "dwCreateTime");
	pElem_dwCreateTime->SetAttribute("value", NumberToString(s.dwCreateTime).c_str());
	pElem_dwCreateTime->SetAttribute("comment", ToUTF8Ptr("创角时间"));
	if(rElement.LinkEndChild(pElem_dwCreateTime.get()) != NULL)
		pElem_dwCreateTime.release();
	unique_ptr<TiXmlElement> pElem_dwLoginTime(new TiXmlElement("UINT32"));
	if(pElem_dwLoginTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwLoginTime->SetAttribute("name", "dwLoginTime");
	pElem_dwLoginTime->SetAttribute("value", NumberToString(s.dwLoginTime).c_str());
	pElem_dwLoginTime->SetAttribute("comment", ToUTF8Ptr("上次登陆时间"));
	if(rElement.LinkEndChild(pElem_dwLoginTime.get()) != NULL)
		pElem_dwLoginTime.release();
	unique_ptr<TiXmlElement> pElem_dwOfflineTime(new TiXmlElement("UINT32"));
	if(pElem_dwOfflineTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwOfflineTime->SetAttribute("name", "dwOfflineTime");
	pElem_dwOfflineTime->SetAttribute("value", NumberToString(s.dwOfflineTime).c_str());
	pElem_dwOfflineTime->SetAttribute("comment", ToUTF8Ptr("上次下线时间"));
	if(rElement.LinkEndChild(pElem_dwOfflineTime.get()) != NULL)
		pElem_dwOfflineTime.release();
	unique_ptr<TiXmlElement> pElem_dwLockExpireTime(new TiXmlElement("UINT32"));
	if(pElem_dwLockExpireTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwLockExpireTime->SetAttribute("name", "dwLockExpireTime");
	pElem_dwLockExpireTime->SetAttribute("value", NumberToString(s.dwLockExpireTime).c_str());
	pElem_dwLockExpireTime->SetAttribute("comment", ToUTF8Ptr("被封禁结束时间"));
	if(rElement.LinkEndChild(pElem_dwLockExpireTime.get()) != NULL)
		pElem_dwLockExpireTime.release();
	unique_ptr<TiXmlElement> pElem_dwForbExpireTime(new TiXmlElement("UINT32"));
	if(pElem_dwForbExpireTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwForbExpireTime->SetAttribute("name", "dwForbExpireTime");
	pElem_dwForbExpireTime->SetAttribute("value", NumberToString(s.dwForbExpireTime).c_str());
	pElem_dwForbExpireTime->SetAttribute("comment", ToUTF8Ptr("被禁言结束时间"));
	if(rElement.LinkEndChild(pElem_dwForbExpireTime.get()) != NULL)
		pElem_dwForbExpireTime.release();
	unique_ptr<TiXmlElement> pElem_dwGold(new TiXmlElement("UINT32"));
	if(pElem_dwGold == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwGold->SetAttribute("name", "dwGold");
	pElem_dwGold->SetAttribute("value", NumberToString(s.dwGold).c_str());
	pElem_dwGold->SetAttribute("comment", ToUTF8Ptr("仙石"));
	if(rElement.LinkEndChild(pElem_dwGold.get()) != NULL)
		pElem_dwGold.release();
	unique_ptr<TiXmlElement> pElem_dwSilver(new TiXmlElement("UINT32"));
	if(pElem_dwSilver == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwSilver->SetAttribute("name", "dwSilver");
	pElem_dwSilver->SetAttribute("value", NumberToString(s.dwSilver).c_str());
	pElem_dwSilver->SetAttribute("comment", ToUTF8Ptr("银币"));
	if(rElement.LinkEndChild(pElem_dwSilver.get()) != NULL)
		pElem_dwSilver.release();
	unique_ptr<TiXmlElement> pElem_dwCoupon(new TiXmlElement("UINT32"));
	if(pElem_dwCoupon == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwCoupon->SetAttribute("name", "dwCoupon");
	pElem_dwCoupon->SetAttribute("value", NumberToString(s.dwCoupon).c_str());
	pElem_dwCoupon->SetAttribute("comment", ToUTF8Ptr("礼券"));
	if(rElement.LinkEndChild(pElem_dwCoupon.get()) != NULL)
		pElem_dwCoupon.release();
	unique_ptr<TiXmlElement> pElem_dwSoul(new TiXmlElement("UINT32"));
	if(pElem_dwSoul == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwSoul->SetAttribute("name", "dwSoul");
	pElem_dwSoul->SetAttribute("value", NumberToString(s.dwSoul).c_str());
	pElem_dwSoul->SetAttribute("comment", ToUTF8Ptr("魂魄"));
	if(rElement.LinkEndChild(pElem_dwSoul.get()) != NULL)
		pElem_dwSoul.release();
	unique_ptr<TiXmlElement> pElem_dwPrestige(new TiXmlElement("UINT32"));
	if(pElem_dwPrestige == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwPrestige->SetAttribute("name", "dwPrestige");
	pElem_dwPrestige->SetAttribute("value", NumberToString(s.dwPrestige).c_str());
	pElem_dwPrestige->SetAttribute("comment", ToUTF8Ptr("声望"));
	if(rElement.LinkEndChild(pElem_dwPrestige.get()) != NULL)
		pElem_dwPrestige.release();
	unique_ptr<TiXmlElement> pElem_dwHonor(new TiXmlElement("UINT32"));
	if(pElem_dwHonor == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwHonor->SetAttribute("name", "dwHonor");
	pElem_dwHonor->SetAttribute("value", NumberToString(s.dwHonor).c_str());
	pElem_dwHonor->SetAttribute("comment", ToUTF8Ptr("荣誉"));
	if(rElement.LinkEndChild(pElem_dwHonor.get()) != NULL)
		pElem_dwHonor.release();
	unique_ptr<TiXmlElement> pElem_dwPExp(new TiXmlElement("UINT32"));
	if(pElem_dwPExp == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwPExp->SetAttribute("name", "dwPExp");
	pElem_dwPExp->SetAttribute("value", NumberToString(s.dwPExp).c_str());
	pElem_dwPExp->SetAttribute("comment", ToUTF8Ptr("修为"));
	if(rElement.LinkEndChild(pElem_dwPExp.get()) != NULL)
		pElem_dwPExp.release();
	unique_ptr<TiXmlElement> pElem_dwSigil(new TiXmlElement("UINT32"));
	if(pElem_dwSigil == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwSigil->SetAttribute("name", "dwSigil");
	pElem_dwSigil->SetAttribute("value", NumberToString(s.dwSigil).c_str());
	pElem_dwSigil->SetAttribute("comment", ToUTF8Ptr("符印"));
	if(rElement.LinkEndChild(pElem_dwSigil.get()) != NULL)
		pElem_dwSigil.release();
	unique_ptr<TiXmlElement> pElem_dwCentsY(new TiXmlElement("UINT32"));
	if(pElem_dwCentsY == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwCentsY->SetAttribute("name", "dwCentsY");
	pElem_dwCentsY->SetAttribute("value", NumberToString(s.dwCentsY).c_str());
	pElem_dwCentsY->SetAttribute("comment", ToUTF8Ptr("仙元"));
	if(rElement.LinkEndChild(pElem_dwCentsY.get()) != NULL)
		pElem_dwCentsY.release();
	unique_ptr<TiXmlElement> pElem_dwAction(new TiXmlElement("UINT32"));
	if(pElem_dwAction == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwAction->SetAttribute("name", "dwAction");
	pElem_dwAction->SetAttribute("value", NumberToString(s.dwAction).c_str());
	pElem_dwAction->SetAttribute("comment", ToUTF8Ptr("体力"));
	if(rElement.LinkEndChild(pElem_dwAction.get()) != NULL)
		pElem_dwAction.release();
	unique_ptr<TiXmlElement> pElem_dwSop(new TiXmlElement("UINT32"));
	if(pElem_dwSop == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwSop->SetAttribute("name", "dwSop");
	pElem_dwSop->SetAttribute("value", NumberToString(s.dwSop).c_str());
	pElem_dwSop->SetAttribute("comment", ToUTF8Ptr("阅历"));
	if(rElement.LinkEndChild(pElem_dwSop.get()) != NULL)
		pElem_dwSop.release();
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
	unique_ptr<TiXmlElement> pElem_vecOwnTitle(new TiXmlElement("TVecUINT16"));
	if(pElem_vecOwnTitle == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecOwnTitle->SetAttribute("name", "vecOwnTitle");
	string strText_vecOwnTitle;
	for(size_t i = 0; i < s.vecOwnTitle.size(); ++i)
	{
		if(i > 0)
			strText_vecOwnTitle += ", ";
		strText_vecOwnTitle += NumberToString(s.vecOwnTitle[i]);
	}
	unique_ptr<TiXmlText> pText_vecOwnTitle(new TiXmlText(strText_vecOwnTitle.c_str()));
	if(pText_vecOwnTitle == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(pElem_vecOwnTitle->LinkEndChild(pText_vecOwnTitle.get()) != NULL)
		pText_vecOwnTitle.release();
	pElem_vecOwnTitle->SetAttribute("comment", ToUTF8Ptr("拥有称号"));
	if(rElement.LinkEndChild(pElem_vecOwnTitle.get()) != NULL)
		pElem_vecOwnTitle.release();
	unique_ptr<TiXmlElement> pElem_vecEquipTitle(new TiXmlElement("TVecUINT16"));
	if(pElem_vecEquipTitle == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecEquipTitle->SetAttribute("name", "vecEquipTitle");
	string strText_vecEquipTitle;
	for(size_t i = 0; i < s.vecEquipTitle.size(); ++i)
	{
		if(i > 0)
			strText_vecEquipTitle += ", ";
		strText_vecEquipTitle += NumberToString(s.vecEquipTitle[i]);
	}
	unique_ptr<TiXmlText> pText_vecEquipTitle(new TiXmlText(strText_vecEquipTitle.c_str()));
	if(pText_vecEquipTitle == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(pElem_vecEquipTitle->LinkEndChild(pText_vecEquipTitle.get()) != NULL)
		pText_vecEquipTitle.release();
	pElem_vecEquipTitle->SetAttribute("comment", ToUTF8Ptr("装备称号"));
	if(rElement.LinkEndChild(pElem_vecEquipTitle.get()) != NULL)
		pElem_vecEquipTitle.release();
	unique_ptr<TiXmlElement> pElem_byDomain(new TiXmlElement("UINT8"));
	if(pElem_byDomain == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byDomain->SetAttribute("name", "byDomain");
	pElem_byDomain->SetAttribute("value", NumberToString(s.byDomain).c_str());
	pElem_byDomain->SetAttribute("comment", ToUTF8Ptr("渠道"));
	if(rElement.LinkEndChild(pElem_byDomain.get()) != NULL)
		pElem_byDomain.release();
	unique_ptr<TiXmlElement> pElem_byDomainLvl(new TiXmlElement("UINT8"));
	if(pElem_byDomainLvl == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byDomainLvl->SetAttribute("name", "byDomainLvl");
	pElem_byDomainLvl->SetAttribute("value", NumberToString(s.byDomainLvl).c_str());
	pElem_byDomainLvl->SetAttribute("comment", ToUTF8Ptr("渠道等级"));
	if(rElement.LinkEndChild(pElem_byDomainLvl.get()) != NULL)
		pElem_byDomainLvl.release();
	unique_ptr<TiXmlElement> pElem_byDisplayLvl(new TiXmlElement("UINT8"));
	if(pElem_byDisplayLvl == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byDisplayLvl->SetAttribute("name", "byDisplayLvl");
	pElem_byDisplayLvl->SetAttribute("value", NumberToString(s.byDisplayLvl).c_str());
	pElem_byDisplayLvl->SetAttribute("comment", ToUTF8Ptr("显示等级"));
	if(rElement.LinkEndChild(pElem_byDisplayLvl.get()) != NULL)
		pElem_byDisplayLvl.release();
	unique_ptr<TiXmlElement> pElem_byDomainYear(new TiXmlElement("UINT8"));
	if(pElem_byDomainYear == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byDomainYear->SetAttribute("name", "byDomainYear");
	pElem_byDomainYear->SetAttribute("value", NumberToString(s.byDomainYear).c_str());
	pElem_byDomainYear->SetAttribute("comment", ToUTF8Ptr("年费"));
	if(rElement.LinkEndChild(pElem_byDomainYear.get()) != NULL)
		pElem_byDomainYear.release();
	unique_ptr<TiXmlElement> pElem_szOpenId(new TiXmlElement("string"));
	if(pElem_szOpenId == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_szOpenId->SetAttribute("name", "szOpenId");
	pElem_szOpenId->SetAttribute("value", s.szOpenId.c_str());
	pElem_szOpenId->SetAttribute("comment", ToUTF8Ptr("szOpenId"));
	if(rElement.LinkEndChild(pElem_szOpenId.get()) != NULL)
		pElem_szOpenId.release();
	unique_ptr<TiXmlElement> pElem_szOpenKey(new TiXmlElement("string"));
	if(pElem_szOpenKey == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_szOpenKey->SetAttribute("name", "szOpenKey");
	pElem_szOpenKey->SetAttribute("value", s.szOpenKey.c_str());
	pElem_szOpenKey->SetAttribute("comment", ToUTF8Ptr("szOpenKey"));
	if(rElement.LinkEndChild(pElem_szOpenKey.get()) != NULL)
		pElem_szOpenKey.release();
	unique_ptr<TiXmlElement> pElem_qwInvitedID(new TiXmlElement("UINT64"));
	if(pElem_qwInvitedID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwInvitedID->SetAttribute("name", "qwInvitedID");
	pElem_qwInvitedID->SetAttribute("value", NumberToString(s.qwInvitedID).c_str());
	pElem_qwInvitedID->SetAttribute("comment", ToUTF8Ptr("邀请"));
	if(rElement.LinkEndChild(pElem_qwInvitedID.get()) != NULL)
		pElem_qwInvitedID.release();
	unique_ptr<TiXmlElement> pElem_byWallow(new TiXmlElement("UINT8"));
	if(pElem_byWallow == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byWallow->SetAttribute("name", "byWallow");
	pElem_byWallow->SetAttribute("value", NumberToString(s.byWallow).c_str());
	pElem_byWallow->SetAttribute("comment", ToUTF8Ptr("防沉迷"));
	if(rElement.LinkEndChild(pElem_byWallow.get()) != NULL)
		pElem_byWallow.release();
	unique_ptr<TiXmlElement> pElem_byVIPLvl(new TiXmlElement("UINT8"));
	if(pElem_byVIPLvl == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byVIPLvl->SetAttribute("name", "byVIPLvl");
	pElem_byVIPLvl->SetAttribute("value", NumberToString(s.byVIPLvl).c_str());
	pElem_byVIPLvl->SetAttribute("comment", ToUTF8Ptr("VIP等级"));
	if(rElement.LinkEndChild(pElem_byVIPLvl.get()) != NULL)
		pElem_byVIPLvl.release();
	unique_ptr<TiXmlElement> pElem_byYDLvl(new TiXmlElement("UINT8"));
	if(pElem_byYDLvl == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byYDLvl->SetAttribute("name", "byYDLvl");
	pElem_byYDLvl->SetAttribute("value", NumberToString(s.byYDLvl).c_str());
	pElem_byYDLvl->SetAttribute("comment", ToUTF8Ptr("黄钻等级"));
	if(rElement.LinkEndChild(pElem_byYDLvl.get()) != NULL)
		pElem_byYDLvl.release();
	unique_ptr<TiXmlElement> pElem_strSign(new TiXmlElement("string"));
	if(pElem_strSign == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strSign->SetAttribute("name", "strSign");
	pElem_strSign->SetAttribute("value", s.strSign.c_str());
	pElem_strSign->SetAttribute("comment", ToUTF8Ptr("签名"));
	if(rElement.LinkEndChild(pElem_strSign.get()) != NULL)
		pElem_strSign.release();
	unique_ptr<TiXmlElement> pElem_wMood(new TiXmlElement("UINT16"));
	if(pElem_wMood == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wMood->SetAttribute("name", "wMood");
	pElem_wMood->SetAttribute("value", NumberToString(s.wMood).c_str());
	pElem_wMood->SetAttribute("comment", ToUTF8Ptr("心情表情"));
	if(rElement.LinkEndChild(pElem_wMood.get()) != NULL)
		pElem_wMood.release();
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
	pElem_byQuality->SetAttribute("comment", ToUTF8Ptr("主将品质"));
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
	unique_ptr<TiXmlElement> pElem_vecFriendsInfo(new TiXmlElement("FriendProt::TVecFriendDBInfo"));
	if(pElem_vecFriendsInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecFriendsInfo->SetAttribute("name", "vecFriendsInfo");
	if(!NFriendProt::VectorToXML(s.vecFriendsInfo, *pElem_vecFriendsInfo))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecFriendsInfo->SetAttribute("comment", ToUTF8Ptr("关系信息"));
	if(rElement.LinkEndChild(pElem_vecFriendsInfo.get()) != NULL)
		pElem_vecFriendsInfo.release();
	unique_ptr<TiXmlElement> pElem_vecGameVars(new TiXmlElement("RoleInfoDefine::TVecVarsDBInfo"));
	if(pElem_vecGameVars == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecGameVars->SetAttribute("name", "vecGameVars");
	if(!NRoleInfoDefine::VectorToXML(s.vecGameVars, *pElem_vecGameVars))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecGameVars->SetAttribute("comment", ToUTF8Ptr("传到center的Var数据"));
	if(rElement.LinkEndChild(pElem_vecGameVars.get()) != NULL)
		pElem_vecGameVars.release();
	unique_ptr<TiXmlElement> pElem_vecArenaInfo(new TiXmlElement("RoleInfoDefine::TVecRoleArenaInfo"));
	if(pElem_vecArenaInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecArenaInfo->SetAttribute("name", "vecArenaInfo");
	if(!NRoleInfoDefine::VectorToXML(s.vecArenaInfo, *pElem_vecArenaInfo))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecArenaInfo->SetAttribute("comment", ToUTF8Ptr("玩家斗剑信息"));
	if(rElement.LinkEndChild(pElem_vecArenaInfo.get()) != NULL)
		pElem_vecArenaInfo.release();
	unique_ptr<TiXmlElement> pElem_vecFireInfo(new TiXmlElement("TripodProt::TVecFireInfo"));
	if(pElem_vecFireInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecFireInfo->SetAttribute("name", "vecFireInfo");
	if(!NTripodProt::VectorToXML(s.vecFireInfo, *pElem_vecFireInfo))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecFireInfo->SetAttribute("comment", ToUTF8Ptr("玩家九疑鼎的火种信息"));
	if(rElement.LinkEndChild(pElem_vecFireInfo.get()) != NULL)
		pElem_vecFireInfo.release();
	unique_ptr<TiXmlElement> pElem_szIconAppear(new TiXmlElement("string"));
	if(pElem_szIconAppear == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_szIconAppear->SetAttribute("name", "szIconAppear");
	pElem_szIconAppear->SetAttribute("value", s.szIconAppear.c_str());
	pElem_szIconAppear->SetAttribute("comment", ToUTF8Ptr("开启的功能"));
	if(rElement.LinkEndChild(pElem_szIconAppear.get()) != NULL)
		pElem_szIconAppear.release();
	unique_ptr<TiXmlElement> pElem_vecPlatform(new TiXmlElement("ProtoCommon::TVecPlatformParam"));
	if(pElem_vecPlatform == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecPlatform->SetAttribute("name", "vecPlatform");
	if(!NProtoCommon::VectorToXML(s.vecPlatform, *pElem_vecPlatform))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecPlatform->SetAttribute("comment", ToUTF8Ptr("平台参数列表"));
	if(rElement.LinkEndChild(pElem_vecPlatform.get()) != NULL)
		pElem_vecPlatform.release();
	unique_ptr<TiXmlElement> pElem_vecShipReport(new TiXmlElement("ShipProt::TVecShipReport"));
	if(pElem_vecShipReport == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecShipReport->SetAttribute("name", "vecShipReport");
	if(!NShipProt::VectorToXML(s.vecShipReport, *pElem_vecShipReport))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecShipReport->SetAttribute("comment", ToUTF8Ptr("金船战报"));
	if(rElement.LinkEndChild(pElem_vecShipReport.get()) != NULL)
		pElem_vecShipReport.release();
	unique_ptr<TiXmlElement> pElem_sShipData(new TiXmlElement("ShipProt::PlayerSelfShipData"));
	if(pElem_sShipData == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_sShipData->SetAttribute("name", "sShipData");
	if(!ToXML(s.sShipData, *pElem_sShipData))
	{
		LOG_CRI << "sShipData ToXML fails!";
		return false;
	}
	pElem_sShipData->SetAttribute("comment", ToUTF8Ptr("自己金船相关信息"));
	if(rElement.LinkEndChild(pElem_sShipData.get()) != NULL)
		pElem_sShipData.release();
	return true;
}

#endif

SLingShanShopData::SLingShanShopData() : qwGuildID(0) { }

SLingShanShopData::SLingShanShopData(UINT64 qwGuildID_, const TVecUINT8& vecLingShanType_) : qwGuildID(qwGuildID_), vecLingShanType(vecLingShanType_) { }

CInArchive& operator>>(CInArchive& src, SLingShanShopData& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwGuildID;
	src >> s.vecLingShanType;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SLingShanShopData& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.qwGuildID;
	src << s.vecLingShanType;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SLingShanShopData& s)
{
	if(strcmp(rElement.Value(), "SLingShanShopData") != 0)
	{
		LOG_CRI << "rElement is not SLingShanShopData!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
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
		LOG_CRI << "pElemChild for vecLingShanType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecUINT8") != 0)
	{
		LOG_CRI << "pElemChild is not TVecUINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecLingShanType") != 0)
	{
		LOG_CRI << "Attribute: name is not vecLingShanType!";
		return false;
	}
	const char* pszText_vecLingShanType = pElemChild->GetText();
	if(pszText_vecLingShanType != NULL)
		SplitToNumber(pszText_vecLingShanType, ",", s.vecLingShanType);
	return true;
}

bool ToXML(const SLingShanShopData& s, TiXmlElement& rElement)
{
	rElement.SetValue("SLingShanShopData");
	rElement.SetAttribute("type", ToUTF8Ptr("灵山商店数据"));
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
	unique_ptr<TiXmlElement> pElem_vecLingShanType(new TiXmlElement("TVecUINT8"));
	if(pElem_vecLingShanType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecLingShanType->SetAttribute("name", "vecLingShanType");
	string strText_vecLingShanType;
	for(size_t i = 0; i < s.vecLingShanType.size(); ++i)
	{
		if(i > 0)
			strText_vecLingShanType += ", ";
		strText_vecLingShanType += NumberToString(s.vecLingShanType[i]);
	}
	unique_ptr<TiXmlText> pText_vecLingShanType(new TiXmlText(strText_vecLingShanType.c_str()));
	if(pText_vecLingShanType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(pElem_vecLingShanType->LinkEndChild(pText_vecLingShanType.get()) != NULL)
		pText_vecLingShanType.release();
	pElem_vecLingShanType->SetAttribute("comment", ToUTF8Ptr("灵山类型"));
	if(rElement.LinkEndChild(pElem_vecLingShanType.get()) != NULL)
		pElem_vecLingShanType.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecLingShanShopData& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SLingShanShopData s;
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

bool VectorToXML(const TVecLingShanShopData& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SLingShanShopData"));
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

SActivityState::SActivityState() : dwActID(0), bOpen(false) { }

SActivityState::SActivityState(UINT32 dwActID_, bool bOpen_) : dwActID(dwActID_), bOpen(bOpen_) { }

CInArchive& operator>>(CInArchive& src, SActivityState& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.dwActID;
	src >> s.bOpen;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SActivityState& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.dwActID;
	src << s.bOpen;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SActivityState& s)
{
	if(strcmp(rElement.Value(), "SActivityState") != 0)
	{
		LOG_CRI << "rElement is not SActivityState!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwActID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwActID") != 0)
	{
		LOG_CRI << "Attribute: name is not dwActID!";
		return false;
	}
	const char* pszVal_dwActID = pElemChild->Attribute("value");
	if(pszVal_dwActID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwActID, s.dwActID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for bOpen is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "bool") != 0)
	{
		LOG_CRI << "pElemChild is not bool!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "bOpen") != 0)
	{
		LOG_CRI << "Attribute: name is not bOpen!";
		return false;
	}
	const char* pszVal_bOpen = pElemChild->Attribute("value");
	if(pszVal_bOpen == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_bOpen, s.bOpen))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SActivityState& s, TiXmlElement& rElement)
{
	rElement.SetValue("SActivityState");
	rElement.SetAttribute("type", ToUTF8Ptr("活动状态数据"));
	unique_ptr<TiXmlElement> pElem_dwActID(new TiXmlElement("UINT32"));
	if(pElem_dwActID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwActID->SetAttribute("name", "dwActID");
	pElem_dwActID->SetAttribute("value", NumberToString(s.dwActID).c_str());
	pElem_dwActID->SetAttribute("comment", ToUTF8Ptr("活动ID"));
	if(rElement.LinkEndChild(pElem_dwActID.get()) != NULL)
		pElem_dwActID.release();
	unique_ptr<TiXmlElement> pElem_bOpen(new TiXmlElement("bool"));
	if(pElem_bOpen == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_bOpen->SetAttribute("name", "bOpen");
	pElem_bOpen->SetAttribute("value", NumberToString(s.bOpen).c_str());
	pElem_bOpen->SetAttribute("comment", ToUTF8Ptr("状态"));
	if(rElement.LinkEndChild(pElem_bOpen.get()) != NULL)
		pElem_bOpen.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecActivityState& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SActivityState s;
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

bool VectorToXML(const TVecActivityState& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SActivityState"));
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

} //namespace NGame2CenterComm
