/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    MapProt.cpp
//  Purpose:      地图相关功能的协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "MapProt.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NMapProt
{

#ifdef PROT_USE_XML

const char* EnumValToStr(EMapResult e)
{
	switch(e)
	{
	case eMapSuccess:
		return "eMapSuccess";
	case eMapNotGhostErr:
		return "eMapNotGhostErr";
	case eMapCoinErr:
		return "eMapCoinErr";
	case eMapNotInDungeonErr:
		return "eMapNotInDungeonErr";
	case eMapOtherErr:
		return "eMapOtherErr";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EMapResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EMapResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eMapSuccess", eMapSuccess));
		mapStr2Val.insert(make_pair("eMapNotGhostErr", eMapNotGhostErr));
		mapStr2Val.insert(make_pair("eMapCoinErr", eMapCoinErr));
		mapStr2Val.insert(make_pair("eMapNotInDungeonErr", eMapNotInDungeonErr));
		mapStr2Val.insert(make_pair("eMapOtherErr", eMapOtherErr));
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

const char* GetDescription(EMapResult e)
{
	switch(e)
	{
	case eMapSuccess:
		return "成功";
	case eMapNotGhostErr:
		return "没处于灵魂状态";
	case eMapCoinErr:
		return "仙石不足";
	case eMapNotInDungeonErr:
		return "不在副本";
	case eMapOtherErr:
		return "其他错误";
	default:
		return "未知错误";
	}
}

#ifdef PROT_USE_XML

const char* EnumValToStr(EMapParam e)
{
	switch(e)
	{
	case eMapParamDemonFloorID:
		return "eMapParamDemonFloorID";
	case eMapParamEnd:
		return "eMapParamEnd";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EMapParam& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EMapParam> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eMapParamDemonFloorID", eMapParamDemonFloorID));
		mapStr2Val.insert(make_pair("eMapParamEnd", eMapParamEnd));
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

const char* EnumValToStr(EAppearState e)
{
	switch(e)
	{
	case eAppearNone:
		return "eAppearNone";
	case eAppearFight:
		return "eAppearFight";
	case eAppearGhost:
		return "eAppearGhost";
	case eAppearDie:
		return "eAppearDie";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EAppearState& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EAppearState> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eAppearNone", eAppearNone));
		mapStr2Val.insert(make_pair("eAppearFight", eAppearFight));
		mapStr2Val.insert(make_pair("eAppearGhost", eAppearGhost));
		mapStr2Val.insert(make_pair("eAppearDie", eAppearDie));
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

const char* EnumValToStr(ESwitcherType e)
{
	switch(e)
	{
	case eSwitcherNone:
		return "eSwitcherNone";
	case eSwitcherJump:
		return "eSwitcherJump";
	case eSwitcherCamp:
		return "eSwitcherCamp";
	case eSwitcherTower:
		return "eSwitcherTower";
	case eSwitcherUpTower:
		return "eSwitcherUpTower";
	case eSwitcherDownTower:
		return "eSwitcherDownTower";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, ESwitcherType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, ESwitcherType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eSwitcherNone", eSwitcherNone));
		mapStr2Val.insert(make_pair("eSwitcherJump", eSwitcherJump));
		mapStr2Val.insert(make_pair("eSwitcherCamp", eSwitcherCamp));
		mapStr2Val.insert(make_pair("eSwitcherTower", eSwitcherTower));
		mapStr2Val.insert(make_pair("eSwitcherUpTower", eSwitcherUpTower));
		mapStr2Val.insert(make_pair("eSwitcherDownTower", eSwitcherDownTower));
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

const char* EnumValToStr(ETreasureResult e)
{
	switch(e)
	{
	case eTreasureSuccess:
		return "eTreasureSuccess";
	case eTreasureFail:
		return "eTreasureFail";
	case eTreasureNoItem:
		return "eTreasureNoItem";
	case eTreasureLackCoin:
		return "eTreasureLackCoin";
	case eTreasureNoInArea:
		return "eTreasureNoInArea";
	case eTreasureDropErr:
		return "eTreasureDropErr";
	case eTreasureDiamond:
		return "eTreasureDiamond";
	case eTreasureBuyInfoSuccess:
		return "eTreasureBuyInfoSuccess";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, ETreasureResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, ETreasureResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eTreasureSuccess", eTreasureSuccess));
		mapStr2Val.insert(make_pair("eTreasureFail", eTreasureFail));
		mapStr2Val.insert(make_pair("eTreasureNoItem", eTreasureNoItem));
		mapStr2Val.insert(make_pair("eTreasureLackCoin", eTreasureLackCoin));
		mapStr2Val.insert(make_pair("eTreasureNoInArea", eTreasureNoInArea));
		mapStr2Val.insert(make_pair("eTreasureDropErr", eTreasureDropErr));
		mapStr2Val.insert(make_pair("eTreasureDiamond", eTreasureDiamond));
		mapStr2Val.insert(make_pair("eTreasureBuyInfoSuccess", eTreasureBuyInfoSuccess));
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

const char* EnumValToStr(EMapOverLoad e)
{
	switch(e)
	{
	case eMapFree:
		return "eMapFree";
	case eMapBusy:
		return "eMapBusy";
	case eMapFull:
		return "eMapFull";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EMapOverLoad& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EMapOverLoad> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eMapFree", eMapFree));
		mapStr2Val.insert(make_pair("eMapBusy", eMapBusy));
		mapStr2Val.insert(make_pair("eMapFull", eMapFull));
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

MapOverLoad::MapOverLoad() : byIndex(0), eLoadState((EMapOverLoad)0) { }

MapOverLoad::MapOverLoad(UINT8 byIndex_, EMapOverLoad eLoadState_) : byIndex(byIndex_), eLoadState(eLoadState_) { }

CInArchive& operator>>(CInArchive& src, MapOverLoad& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.byIndex;
	src >> (UINT8&)s.eLoadState;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const MapOverLoad& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.byIndex;
	src << (UINT8&)s.eLoadState;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, MapOverLoad& s)
{
	if(strcmp(rElement.Value(), "MapOverLoad") != 0)
	{
		LOG_CRI << "rElement is not MapOverLoad!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byIndex is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byIndex") != 0)
	{
		LOG_CRI << "Attribute: name is not byIndex!";
		return false;
	}
	const char* pszVal_byIndex = pElemChild->Attribute("value");
	if(pszVal_byIndex == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byIndex, s.byIndex))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eLoadState is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "EMapOverLoad") != 0)
	{
		LOG_CRI << "pElemChild is not EMapOverLoad!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eLoadState") != 0)
	{
		LOG_CRI << "Attribute: name is not eLoadState!";
		return false;
	}
	const char* pszVal_eLoadState = pElemChild->Attribute("value");
	if(pszVal_eLoadState == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!EnumStrToVal(pszVal_eLoadState, s.eLoadState))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const MapOverLoad& s, TiXmlElement& rElement)
{
	rElement.SetValue("MapOverLoad");
	rElement.SetAttribute("type", ToUTF8Ptr("地图负载情况"));
	unique_ptr<TiXmlElement> pElem_byIndex(new TiXmlElement("UINT8"));
	if(pElem_byIndex == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byIndex->SetAttribute("name", "byIndex");
	pElem_byIndex->SetAttribute("value", NumberToString(s.byIndex).c_str());
	pElem_byIndex->SetAttribute("comment", ToUTF8Ptr("地图序号"));
	if(rElement.LinkEndChild(pElem_byIndex.get()) != NULL)
		pElem_byIndex.release();
	unique_ptr<TiXmlElement> pElem_eLoadState(new TiXmlElement("EMapOverLoad"));
	if(pElem_eLoadState == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eLoadState->SetAttribute("name", "eLoadState");
	const char* pszEnum_eLoadState = EnumValToStr(s.eLoadState);
	if(pszEnum_eLoadState == NULL)
	{
		LOG_CRI << "EnumValToStr for EMapOverLoad fails!";
		return false;
	}
	pElem_eLoadState->SetAttribute("value", pszEnum_eLoadState);
	pElem_eLoadState->SetAttribute("comment", ToUTF8Ptr("负载状况"));
	if(rElement.LinkEndChild(pElem_eLoadState.get()) != NULL)
		pElem_eLoadState.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecMapOverLoad& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		MapOverLoad s;
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

bool VectorToXML(const TVecMapOverLoad& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("MapOverLoad"));
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

SPosition::SPosition() : fX(0), fY(0) { }

SPosition::SPosition(float fX_, float fY_) : fX(fX_), fY(fY_) { }

CInArchive& operator>>(CInArchive& src, SPosition& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.fX;
	src >> s.fY;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SPosition& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.fX;
	src << s.fY;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SPosition& s)
{
	if(strcmp(rElement.Value(), "SPosition") != 0)
	{
		LOG_CRI << "rElement is not SPosition!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for fX is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "float") != 0)
	{
		LOG_CRI << "pElemChild is not float!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "fX") != 0)
	{
		LOG_CRI << "Attribute: name is not fX!";
		return false;
	}
	const char* pszVal_fX = pElemChild->Attribute("value");
	if(pszVal_fX == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_fX, s.fX))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for fY is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "float") != 0)
	{
		LOG_CRI << "pElemChild is not float!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "fY") != 0)
	{
		LOG_CRI << "Attribute: name is not fY!";
		return false;
	}
	const char* pszVal_fY = pElemChild->Attribute("value");
	if(pszVal_fY == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_fY, s.fY))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SPosition& s, TiXmlElement& rElement)
{
	rElement.SetValue("SPosition");
	rElement.SetAttribute("type", ToUTF8Ptr("地图上物体的位置"));
	unique_ptr<TiXmlElement> pElem_fX(new TiXmlElement("float"));
	if(pElem_fX == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_fX->SetAttribute("name", "fX");
	pElem_fX->SetAttribute("value", NumberToString(s.fX).c_str());
	pElem_fX->SetAttribute("comment", ToUTF8Ptr("X坐标"));
	if(rElement.LinkEndChild(pElem_fX.get()) != NULL)
		pElem_fX.release();
	unique_ptr<TiXmlElement> pElem_fY(new TiXmlElement("float"));
	if(pElem_fY == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_fY->SetAttribute("name", "fY");
	pElem_fY->SetAttribute("value", NumberToString(s.fY).c_str());
	pElem_fY->SetAttribute("comment", ToUTF8Ptr("Y坐标"));
	if(rElement.LinkEndChild(pElem_fY.get()) != NULL)
		pElem_fY.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecPosition& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SPosition s;
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

bool VectorToXML(const TVecPosition& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SPosition"));
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

SPlayerAppear::SPlayerAppear() : eCareer((NProtoCommon::ECareerType)0), eSex((NProtoCommon::ESexType)0), byLevel(0), dwSpeed(0), dwHorseID(0), 
			dwHorseLevel(0), wPetID(0), byPetLevel(0), wBeautyID(0), byBeautyLevel(0), 
			bIsSitting(0), qwOtherSitID(0) { }

SPlayerAppear::SPlayerAppear(SPlayerAppear&& src) : strName(move(src.strName)), eCareer(src.eCareer), eSex(src.eSex), byLevel(src.byLevel), dwSpeed(src.dwSpeed), dwHorseID(src.dwHorseID), dwHorseLevel(src.dwHorseLevel), wPetID(src.wPetID), byPetLevel(src.byPetLevel), 
			wBeautyID(src.wBeautyID), byBeautyLevel(src.byBeautyLevel), bIsSitting(src.bIsSitting), qwOtherSitID(src.qwOtherSitID), vecPlatforms(move(src.vecPlatforms))
{
	pFeature.swap(src.pFeature);
}

SPlayerAppear& SPlayerAppear::operator=(SPlayerAppear&& rhs)
{
	if(this != &rhs)
	{
		this->~SPlayerAppear();
		new (this) SPlayerAppear(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SPlayerAppear& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	NBattleGS::SFeatureBase_Wrapper pFeature_Wrapper;
	src >> s.strName;
	src >> (UINT8&)s.eCareer;
	src >> (UINT8&)s.eSex;
	src >> s.byLevel;
	src >> s.dwSpeed;
	src >> pFeature_Wrapper;
	src >> s.dwHorseID;
	src >> s.dwHorseLevel;
	src >> s.wPetID;
	src >> s.byPetLevel;
	src >> s.wBeautyID;
	src >> s.byBeautyLevel;
	src >> s.bIsSitting;
	src >> s.qwOtherSitID;
	src >> s.vecPlatforms;
	s.pFeature = pFeature_Wrapper.ptr;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SPlayerAppear& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	NBattleGS::SFeatureBase_Wrapper pFeature_Wrapper(s.pFeature);
	src << s.strName;
	src << (UINT8&)s.eCareer;
	src << (UINT8&)s.eSex;
	src << s.byLevel;
	src << s.dwSpeed;
	src << pFeature_Wrapper;
	src << s.dwHorseID;
	src << s.dwHorseLevel;
	src << s.wPetID;
	src << s.byPetLevel;
	src << s.wBeautyID;
	src << s.byBeautyLevel;
	src << s.bIsSitting;
	src << s.qwOtherSitID;
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

bool FromXML(TiXmlElement& rElement, SPlayerAppear& s)
{
	if(strcmp(rElement.Value(), "SPlayerAppear") != 0)
	{
		LOG_CRI << "rElement is not SPlayerAppear!";
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
		LOG_CRI << "pElemChild for dwSpeed is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwSpeed") != 0)
	{
		LOG_CRI << "Attribute: name is not dwSpeed!";
		return false;
	}
	const char* pszVal_dwSpeed = pElemChild->Attribute("value");
	if(pszVal_dwSpeed == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwSpeed, s.dwSpeed))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for pFeature is empty!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "pFeature") != 0)
	{
		LOG_CRI << "Attribute: name is not pFeature!";
		return false;
	}
	if(!SuperFromXML(*pElemChild, s.pFeature))
	{
		LOG_CRI << "FromXML for: pFeature fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
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
		LOG_CRI << "pElemChild for dwHorseLevel is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwHorseLevel") != 0)
	{
		LOG_CRI << "Attribute: name is not dwHorseLevel!";
		return false;
	}
	const char* pszVal_dwHorseLevel = pElemChild->Attribute("value");
	if(pszVal_dwHorseLevel == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwHorseLevel, s.dwHorseLevel))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wPetID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wPetID") != 0)
	{
		LOG_CRI << "Attribute: name is not wPetID!";
		return false;
	}
	const char* pszVal_wPetID = pElemChild->Attribute("value");
	if(pszVal_wPetID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wPetID, s.wPetID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byPetLevel is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byPetLevel") != 0)
	{
		LOG_CRI << "Attribute: name is not byPetLevel!";
		return false;
	}
	const char* pszVal_byPetLevel = pElemChild->Attribute("value");
	if(pszVal_byPetLevel == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byPetLevel, s.byPetLevel))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
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
		LOG_CRI << "pElemChild for byBeautyLevel is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byBeautyLevel") != 0)
	{
		LOG_CRI << "Attribute: name is not byBeautyLevel!";
		return false;
	}
	const char* pszVal_byBeautyLevel = pElemChild->Attribute("value");
	if(pszVal_byBeautyLevel == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byBeautyLevel, s.byBeautyLevel))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for bIsSitting is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "bIsSitting") != 0)
	{
		LOG_CRI << "Attribute: name is not bIsSitting!";
		return false;
	}
	const char* pszVal_bIsSitting = pElemChild->Attribute("value");
	if(pszVal_bIsSitting == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_bIsSitting, s.bIsSitting))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwOtherSitID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwOtherSitID") != 0)
	{
		LOG_CRI << "Attribute: name is not qwOtherSitID!";
		return false;
	}
	const char* pszVal_qwOtherSitID = pElemChild->Attribute("value");
	if(pszVal_qwOtherSitID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwOtherSitID, s.qwOtherSitID))
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

bool ToXML(const SPlayerAppear& s, TiXmlElement& rElement)
{
	rElement.SetValue("SPlayerAppear");
	rElement.SetAttribute("type", ToUTF8Ptr("角色的外观"));
	unique_ptr<TiXmlElement> pElem_strName(new TiXmlElement("string"));
	if(pElem_strName == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strName->SetAttribute("name", "strName");
	pElem_strName->SetAttribute("value", s.strName.c_str());
	pElem_strName->SetAttribute("comment", ToUTF8Ptr("角色名"));
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
	unique_ptr<TiXmlElement> pElem_dwSpeed(new TiXmlElement("UINT32"));
	if(pElem_dwSpeed == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwSpeed->SetAttribute("name", "dwSpeed");
	pElem_dwSpeed->SetAttribute("value", NumberToString(s.dwSpeed).c_str());
	pElem_dwSpeed->SetAttribute("comment", ToUTF8Ptr("速度"));
	if(rElement.LinkEndChild(pElem_dwSpeed.get()) != NULL)
		pElem_dwSpeed.release();
	unique_ptr<TiXmlElement> pElem_pFeature(new TiXmlElement("BattleGS::SFeatureBase"));
	if(pElem_pFeature == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_pFeature->SetAttribute("name", "pFeature");
	if(s.pFeature == NULL)
	{
		LOG_CRI << "pFeature is NULL!";
		return false;
	}
	if(!SuperToXML(*s.pFeature, *pElem_pFeature))
	{
		LOG_CRI << "pFeature SuperToXML fails!";
		return false;
	}
	pElem_pFeature->SetAttribute("comment", ToUTF8Ptr("外观信息"));
	if(rElement.LinkEndChild(pElem_pFeature.get()) != NULL)
		pElem_pFeature.release();
	unique_ptr<TiXmlElement> pElem_dwHorseID(new TiXmlElement("UINT32"));
	if(pElem_dwHorseID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwHorseID->SetAttribute("name", "dwHorseID");
	pElem_dwHorseID->SetAttribute("value", NumberToString(s.dwHorseID).c_str());
	pElem_dwHorseID->SetAttribute("comment", ToUTF8Ptr("坐骑"));
	if(rElement.LinkEndChild(pElem_dwHorseID.get()) != NULL)
		pElem_dwHorseID.release();
	unique_ptr<TiXmlElement> pElem_dwHorseLevel(new TiXmlElement("UINT32"));
	if(pElem_dwHorseLevel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwHorseLevel->SetAttribute("name", "dwHorseLevel");
	pElem_dwHorseLevel->SetAttribute("value", NumberToString(s.dwHorseLevel).c_str());
	pElem_dwHorseLevel->SetAttribute("comment", ToUTF8Ptr("坐骑等级"));
	if(rElement.LinkEndChild(pElem_dwHorseLevel.get()) != NULL)
		pElem_dwHorseLevel.release();
	unique_ptr<TiXmlElement> pElem_wPetID(new TiXmlElement("UINT16"));
	if(pElem_wPetID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wPetID->SetAttribute("name", "wPetID");
	pElem_wPetID->SetAttribute("value", NumberToString(s.wPetID).c_str());
	pElem_wPetID->SetAttribute("comment", ToUTF8Ptr("阵灵ID"));
	if(rElement.LinkEndChild(pElem_wPetID.get()) != NULL)
		pElem_wPetID.release();
	unique_ptr<TiXmlElement> pElem_byPetLevel(new TiXmlElement("UINT8"));
	if(pElem_byPetLevel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byPetLevel->SetAttribute("name", "byPetLevel");
	pElem_byPetLevel->SetAttribute("value", NumberToString(s.byPetLevel).c_str());
	pElem_byPetLevel->SetAttribute("comment", ToUTF8Ptr("阵灵等级"));
	if(rElement.LinkEndChild(pElem_byPetLevel.get()) != NULL)
		pElem_byPetLevel.release();
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
	unique_ptr<TiXmlElement> pElem_byBeautyLevel(new TiXmlElement("UINT8"));
	if(pElem_byBeautyLevel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byBeautyLevel->SetAttribute("name", "byBeautyLevel");
	pElem_byBeautyLevel->SetAttribute("value", NumberToString(s.byBeautyLevel).c_str());
	pElem_byBeautyLevel->SetAttribute("comment", ToUTF8Ptr("美女等级"));
	if(rElement.LinkEndChild(pElem_byBeautyLevel.get()) != NULL)
		pElem_byBeautyLevel.release();
	unique_ptr<TiXmlElement> pElem_bIsSitting(new TiXmlElement("UINT8"));
	if(pElem_bIsSitting == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_bIsSitting->SetAttribute("name", "bIsSitting");
	pElem_bIsSitting->SetAttribute("value", NumberToString(s.bIsSitting).c_str());
	pElem_bIsSitting->SetAttribute("comment", ToUTF8Ptr("是否打坐0,没有打坐，1单修，2双修"));
	if(rElement.LinkEndChild(pElem_bIsSitting.get()) != NULL)
		pElem_bIsSitting.release();
	unique_ptr<TiXmlElement> pElem_qwOtherSitID(new TiXmlElement("UINT64"));
	if(pElem_qwOtherSitID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwOtherSitID->SetAttribute("name", "qwOtherSitID");
	pElem_qwOtherSitID->SetAttribute("value", NumberToString(s.qwOtherSitID).c_str());
	pElem_qwOtherSitID->SetAttribute("comment", ToUTF8Ptr("双修玩家"));
	if(rElement.LinkEndChild(pElem_qwOtherSitID.get()) != NULL)
		pElem_qwOtherSitID.release();
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

bool VectorFromXML(TiXmlElement& rElement, TVecPlayerAppear& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SPlayerAppear s;
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

bool VectorToXML(const TVecPlayerAppear& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SPlayerAppear"));
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

SMonsterAppear::SMonsterAppear() : wMonsterID(0), byLevel(0), dwSpeed(0), dwCurHP(0), dwMaxHP(0), 
			byCamp(0), wGroup(0), bySight(0), bySightAngle(0), byFindEnemy(0) { }

CInArchive& operator>>(CInArchive& src, SMonsterAppear& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	NBattleGS::SFeatureBase_Wrapper pFeature_Wrapper;
	src >> s.wMonsterID;
	src >> s.strName;
	src >> s.byLevel;
	src >> s.dwSpeed;
	src >> s.dwCurHP;
	src >> s.dwMaxHP;
	src >> s.byCamp;
	src >> s.wGroup;
	src >> s.bySight;
	src >> s.bySightAngle;
	src >> s.byFindEnemy;
	src >> pFeature_Wrapper;
	s.pFeature = pFeature_Wrapper.ptr;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SMonsterAppear& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	NBattleGS::SFeatureBase_Wrapper pFeature_Wrapper(s.pFeature);
	src << s.wMonsterID;
	src << s.strName;
	src << s.byLevel;
	src << s.dwSpeed;
	src << s.dwCurHP;
	src << s.dwMaxHP;
	src << s.byCamp;
	src << s.wGroup;
	src << s.bySight;
	src << s.bySightAngle;
	src << s.byFindEnemy;
	src << pFeature_Wrapper;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SMonsterAppear& s)
{
	if(strcmp(rElement.Value(), "SMonsterAppear") != 0)
	{
		LOG_CRI << "rElement is not SMonsterAppear!";
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
		LOG_CRI << "pElemChild for dwSpeed is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwSpeed") != 0)
	{
		LOG_CRI << "Attribute: name is not dwSpeed!";
		return false;
	}
	const char* pszVal_dwSpeed = pElemChild->Attribute("value");
	if(pszVal_dwSpeed == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwSpeed, s.dwSpeed))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwCurHP is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwCurHP") != 0)
	{
		LOG_CRI << "Attribute: name is not dwCurHP!";
		return false;
	}
	const char* pszVal_dwCurHP = pElemChild->Attribute("value");
	if(pszVal_dwCurHP == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwCurHP, s.dwCurHP))
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
		LOG_CRI << "pElemChild for byCamp is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byCamp") != 0)
	{
		LOG_CRI << "Attribute: name is not byCamp!";
		return false;
	}
	const char* pszVal_byCamp = pElemChild->Attribute("value");
	if(pszVal_byCamp == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byCamp, s.byCamp))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wGroup is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
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
		LOG_CRI << "pElemChild for bySight is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "bySight") != 0)
	{
		LOG_CRI << "Attribute: name is not bySight!";
		return false;
	}
	const char* pszVal_bySight = pElemChild->Attribute("value");
	if(pszVal_bySight == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_bySight, s.bySight))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for bySightAngle is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "bySightAngle") != 0)
	{
		LOG_CRI << "Attribute: name is not bySightAngle!";
		return false;
	}
	const char* pszVal_bySightAngle = pElemChild->Attribute("value");
	if(pszVal_bySightAngle == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_bySightAngle, s.bySightAngle))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byFindEnemy is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byFindEnemy") != 0)
	{
		LOG_CRI << "Attribute: name is not byFindEnemy!";
		return false;
	}
	const char* pszVal_byFindEnemy = pElemChild->Attribute("value");
	if(pszVal_byFindEnemy == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byFindEnemy, s.byFindEnemy))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for pFeature is empty!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "pFeature") != 0)
	{
		LOG_CRI << "Attribute: name is not pFeature!";
		return false;
	}
	if(!SuperFromXML(*pElemChild, s.pFeature))
	{
		LOG_CRI << "FromXML for: pFeature fails!";
		return false;
	}
	return true;
}

bool ToXML(const SMonsterAppear& s, TiXmlElement& rElement)
{
	rElement.SetValue("SMonsterAppear");
	rElement.SetAttribute("type", ToUTF8Ptr("怪物的外观"));
	unique_ptr<TiXmlElement> pElem_wMonsterID(new TiXmlElement("UINT16"));
	if(pElem_wMonsterID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wMonsterID->SetAttribute("name", "wMonsterID");
	pElem_wMonsterID->SetAttribute("value", NumberToString(s.wMonsterID).c_str());
	pElem_wMonsterID->SetAttribute("comment", ToUTF8Ptr("怪物ID"));
	if(rElement.LinkEndChild(pElem_wMonsterID.get()) != NULL)
		pElem_wMonsterID.release();
	unique_ptr<TiXmlElement> pElem_strName(new TiXmlElement("string"));
	if(pElem_strName == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strName->SetAttribute("name", "strName");
	pElem_strName->SetAttribute("value", s.strName.c_str());
	pElem_strName->SetAttribute("comment", ToUTF8Ptr("怪物名称"));
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
	pElem_byLevel->SetAttribute("comment", ToUTF8Ptr("等级"));
	if(rElement.LinkEndChild(pElem_byLevel.get()) != NULL)
		pElem_byLevel.release();
	unique_ptr<TiXmlElement> pElem_dwSpeed(new TiXmlElement("UINT32"));
	if(pElem_dwSpeed == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwSpeed->SetAttribute("name", "dwSpeed");
	pElem_dwSpeed->SetAttribute("value", NumberToString(s.dwSpeed).c_str());
	pElem_dwSpeed->SetAttribute("comment", ToUTF8Ptr("移动速度/200"));
	if(rElement.LinkEndChild(pElem_dwSpeed.get()) != NULL)
		pElem_dwSpeed.release();
	unique_ptr<TiXmlElement> pElem_dwCurHP(new TiXmlElement("UINT32"));
	if(pElem_dwCurHP == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwCurHP->SetAttribute("name", "dwCurHP");
	pElem_dwCurHP->SetAttribute("value", NumberToString(s.dwCurHP).c_str());
	pElem_dwCurHP->SetAttribute("comment", ToUTF8Ptr("当前HP"));
	if(rElement.LinkEndChild(pElem_dwCurHP.get()) != NULL)
		pElem_dwCurHP.release();
	unique_ptr<TiXmlElement> pElem_dwMaxHP(new TiXmlElement("UINT32"));
	if(pElem_dwMaxHP == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwMaxHP->SetAttribute("name", "dwMaxHP");
	pElem_dwMaxHP->SetAttribute("value", NumberToString(s.dwMaxHP).c_str());
	pElem_dwMaxHP->SetAttribute("comment", ToUTF8Ptr("最大HP"));
	if(rElement.LinkEndChild(pElem_dwMaxHP.get()) != NULL)
		pElem_dwMaxHP.release();
	unique_ptr<TiXmlElement> pElem_byCamp(new TiXmlElement("UINT8"));
	if(pElem_byCamp == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byCamp->SetAttribute("name", "byCamp");
	pElem_byCamp->SetAttribute("value", NumberToString(s.byCamp).c_str());
	pElem_byCamp->SetAttribute("comment", ToUTF8Ptr("阵营"));
	if(rElement.LinkEndChild(pElem_byCamp.get()) != NULL)
		pElem_byCamp.release();
	unique_ptr<TiXmlElement> pElem_wGroup(new TiXmlElement("UINT16"));
	if(pElem_wGroup == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wGroup->SetAttribute("name", "wGroup");
	pElem_wGroup->SetAttribute("value", NumberToString(s.wGroup).c_str());
	pElem_wGroup->SetAttribute("comment", ToUTF8Ptr("所属的组"));
	if(rElement.LinkEndChild(pElem_wGroup.get()) != NULL)
		pElem_wGroup.release();
	unique_ptr<TiXmlElement> pElem_bySight(new TiXmlElement("UINT8"));
	if(pElem_bySight == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_bySight->SetAttribute("name", "bySight");
	pElem_bySight->SetAttribute("value", NumberToString(s.bySight).c_str());
	pElem_bySight->SetAttribute("comment", ToUTF8Ptr("视野"));
	if(rElement.LinkEndChild(pElem_bySight.get()) != NULL)
		pElem_bySight.release();
	unique_ptr<TiXmlElement> pElem_bySightAngle(new TiXmlElement("UINT8"));
	if(pElem_bySightAngle == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_bySightAngle->SetAttribute("name", "bySightAngle");
	pElem_bySightAngle->SetAttribute("value", NumberToString(s.bySightAngle).c_str());
	pElem_bySightAngle->SetAttribute("comment", ToUTF8Ptr("视野角度"));
	if(rElement.LinkEndChild(pElem_bySightAngle.get()) != NULL)
		pElem_bySightAngle.release();
	unique_ptr<TiXmlElement> pElem_byFindEnemy(new TiXmlElement("UINT8"));
	if(pElem_byFindEnemy == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byFindEnemy->SetAttribute("name", "byFindEnemy");
	pElem_byFindEnemy->SetAttribute("value", NumberToString(s.byFindEnemy).c_str());
	pElem_byFindEnemy->SetAttribute("comment", ToUTF8Ptr("0,无目标：1有目标"));
	if(rElement.LinkEndChild(pElem_byFindEnemy.get()) != NULL)
		pElem_byFindEnemy.release();
	unique_ptr<TiXmlElement> pElem_pFeature(new TiXmlElement("BattleGS::SFeatureBase"));
	if(pElem_pFeature == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_pFeature->SetAttribute("name", "pFeature");
	if(s.pFeature == NULL)
	{
		LOG_CRI << "pFeature is NULL!";
		return false;
	}
	if(!SuperToXML(*s.pFeature, *pElem_pFeature))
	{
		LOG_CRI << "pFeature SuperToXML fails!";
		return false;
	}
	pElem_pFeature->SetAttribute("comment", ToUTF8Ptr("外观信息"));
	if(rElement.LinkEndChild(pElem_pFeature.get()) != NULL)
		pElem_pFeature.release();
	return true;
}

#endif

SNpcAppear::SNpcAppear() : wNpcID(0) { }

SNpcAppear::SNpcAppear(UINT16 wNpcID_, const std::string& strName_) : wNpcID(wNpcID_), strName(strName_) { }

SNpcAppear::SNpcAppear(SNpcAppear&& src) : wNpcID(src.wNpcID), strName(move(src.strName)) { }

SNpcAppear& SNpcAppear::operator=(SNpcAppear&& rhs)
{
	if(this != &rhs)
	{
		this->~SNpcAppear();
		new (this) SNpcAppear(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SNpcAppear& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.wNpcID;
	src >> s.strName;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SNpcAppear& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.wNpcID;
	src << s.strName;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SNpcAppear& s)
{
	if(strcmp(rElement.Value(), "SNpcAppear") != 0)
	{
		LOG_CRI << "rElement is not SNpcAppear!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wNpcID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wNpcID") != 0)
	{
		LOG_CRI << "Attribute: name is not wNpcID!";
		return false;
	}
	const char* pszVal_wNpcID = pElemChild->Attribute("value");
	if(pszVal_wNpcID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wNpcID, s.wNpcID))
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
	return true;
}

bool ToXML(const SNpcAppear& s, TiXmlElement& rElement)
{
	rElement.SetValue("SNpcAppear");
	rElement.SetAttribute("type", ToUTF8Ptr("NPC的外观"));
	unique_ptr<TiXmlElement> pElem_wNpcID(new TiXmlElement("UINT16"));
	if(pElem_wNpcID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wNpcID->SetAttribute("name", "wNpcID");
	pElem_wNpcID->SetAttribute("value", NumberToString(s.wNpcID).c_str());
	pElem_wNpcID->SetAttribute("comment", ToUTF8Ptr("NPC类型ID"));
	if(rElement.LinkEndChild(pElem_wNpcID.get()) != NULL)
		pElem_wNpcID.release();
	unique_ptr<TiXmlElement> pElem_strName(new TiXmlElement("string"));
	if(pElem_strName == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strName->SetAttribute("name", "strName");
	pElem_strName->SetAttribute("value", s.strName.c_str());
	pElem_strName->SetAttribute("comment", ToUTF8Ptr("NPC名称"));
	if(rElement.LinkEndChild(pElem_strName.get()) != NULL)
		pElem_strName.release();
	return true;
}

#endif

SGatherAppear::SGatherAppear() : wGatherID(0), wTotalNum(0), wReserverNum(0), wGatheringNum(0) { }

SGatherAppear::SGatherAppear(UINT16 wGatherID_, UINT16 wTotalNum_, UINT16 wReserverNum_, UINT16 wGatheringNum_) : wGatherID(wGatherID_), wTotalNum(wTotalNum_), wReserverNum(wReserverNum_), wGatheringNum(wGatheringNum_) { }

CInArchive& operator>>(CInArchive& src, SGatherAppear& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.wGatherID;
	src >> s.wTotalNum;
	src >> s.wReserverNum;
	src >> s.wGatheringNum;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SGatherAppear& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.wGatherID;
	src << s.wTotalNum;
	src << s.wReserverNum;
	src << s.wGatheringNum;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SGatherAppear& s)
{
	if(strcmp(rElement.Value(), "SGatherAppear") != 0)
	{
		LOG_CRI << "rElement is not SGatherAppear!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wGatherID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wGatherID") != 0)
	{
		LOG_CRI << "Attribute: name is not wGatherID!";
		return false;
	}
	const char* pszVal_wGatherID = pElemChild->Attribute("value");
	if(pszVal_wGatherID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wGatherID, s.wGatherID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wTotalNum is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wTotalNum") != 0)
	{
		LOG_CRI << "Attribute: name is not wTotalNum!";
		return false;
	}
	const char* pszVal_wTotalNum = pElemChild->Attribute("value");
	if(pszVal_wTotalNum == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wTotalNum, s.wTotalNum))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wReserverNum is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wReserverNum") != 0)
	{
		LOG_CRI << "Attribute: name is not wReserverNum!";
		return false;
	}
	const char* pszVal_wReserverNum = pElemChild->Attribute("value");
	if(pszVal_wReserverNum == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wReserverNum, s.wReserverNum))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wGatheringNum is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wGatheringNum") != 0)
	{
		LOG_CRI << "Attribute: name is not wGatheringNum!";
		return false;
	}
	const char* pszVal_wGatheringNum = pElemChild->Attribute("value");
	if(pszVal_wGatheringNum == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wGatheringNum, s.wGatheringNum))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SGatherAppear& s, TiXmlElement& rElement)
{
	rElement.SetValue("SGatherAppear");
	rElement.SetAttribute("type", ToUTF8Ptr("采集物的外观"));
	unique_ptr<TiXmlElement> pElem_wGatherID(new TiXmlElement("UINT16"));
	if(pElem_wGatherID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wGatherID->SetAttribute("name", "wGatherID");
	pElem_wGatherID->SetAttribute("value", NumberToString(s.wGatherID).c_str());
	pElem_wGatherID->SetAttribute("comment", ToUTF8Ptr("采集物类型ID"));
	if(rElement.LinkEndChild(pElem_wGatherID.get()) != NULL)
		pElem_wGatherID.release();
	unique_ptr<TiXmlElement> pElem_wTotalNum(new TiXmlElement("UINT16"));
	if(pElem_wTotalNum == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wTotalNum->SetAttribute("name", "wTotalNum");
	pElem_wTotalNum->SetAttribute("value", NumberToString(s.wTotalNum).c_str());
	pElem_wTotalNum->SetAttribute("comment", ToUTF8Ptr("采集总次数,特别的为-1表示，采集无数次,以下两个字段始终为0"));
	if(rElement.LinkEndChild(pElem_wTotalNum.get()) != NULL)
		pElem_wTotalNum.release();
	unique_ptr<TiXmlElement> pElem_wReserverNum(new TiXmlElement("UINT16"));
	if(pElem_wReserverNum == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wReserverNum->SetAttribute("name", "wReserverNum");
	pElem_wReserverNum->SetAttribute("value", NumberToString(s.wReserverNum).c_str());
	pElem_wReserverNum->SetAttribute("comment", ToUTF8Ptr("采集剩余次数"));
	if(rElement.LinkEndChild(pElem_wReserverNum.get()) != NULL)
		pElem_wReserverNum.release();
	unique_ptr<TiXmlElement> pElem_wGatheringNum(new TiXmlElement("UINT16"));
	if(pElem_wGatheringNum == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wGatheringNum->SetAttribute("name", "wGatheringNum");
	pElem_wGatheringNum->SetAttribute("value", NumberToString(s.wGatheringNum).c_str());
	pElem_wGatheringNum->SetAttribute("comment", ToUTF8Ptr("正在采集的人次"));
	if(rElement.LinkEndChild(pElem_wGatheringNum.get()) != NULL)
		pElem_wGatheringNum.release();
	return true;
}

#endif

SSwitcherAppear::SSwitcherAppear() : dwSwitcherID(0), eType((ESwitcherType)0), bOpen(false) { }

SSwitcherAppear::SSwitcherAppear(UINT32 dwSwitcherID_, ESwitcherType eType_, bool bOpen_) : dwSwitcherID(dwSwitcherID_), eType(eType_), bOpen(bOpen_) { }

CInArchive& operator>>(CInArchive& src, SSwitcherAppear& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.dwSwitcherID;
	src >> (UINT8&)s.eType;
	src >> s.bOpen;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SSwitcherAppear& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.dwSwitcherID;
	src << (UINT8&)s.eType;
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

bool FromXML(TiXmlElement& rElement, SSwitcherAppear& s)
{
	if(strcmp(rElement.Value(), "SSwitcherAppear") != 0)
	{
		LOG_CRI << "rElement is not SSwitcherAppear!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwSwitcherID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwSwitcherID") != 0)
	{
		LOG_CRI << "Attribute: name is not dwSwitcherID!";
		return false;
	}
	const char* pszVal_dwSwitcherID = pElemChild->Attribute("value");
	if(pszVal_dwSwitcherID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwSwitcherID, s.dwSwitcherID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "ESwitcherType") != 0)
	{
		LOG_CRI << "pElemChild is not ESwitcherType!";
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

bool ToXML(const SSwitcherAppear& s, TiXmlElement& rElement)
{
	rElement.SetValue("SSwitcherAppear");
	rElement.SetAttribute("type", ToUTF8Ptr("传送阵开关的外观"));
	unique_ptr<TiXmlElement> pElem_dwSwitcherID(new TiXmlElement("UINT32"));
	if(pElem_dwSwitcherID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwSwitcherID->SetAttribute("name", "dwSwitcherID");
	pElem_dwSwitcherID->SetAttribute("value", NumberToString(s.dwSwitcherID).c_str());
	pElem_dwSwitcherID->SetAttribute("comment", ToUTF8Ptr("开关配置ID"));
	if(rElement.LinkEndChild(pElem_dwSwitcherID.get()) != NULL)
		pElem_dwSwitcherID.release();
	unique_ptr<TiXmlElement> pElem_eType(new TiXmlElement("ESwitcherType"));
	if(pElem_eType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eType->SetAttribute("name", "eType");
	const char* pszEnum_eType = EnumValToStr(s.eType);
	if(pszEnum_eType == NULL)
	{
		LOG_CRI << "EnumValToStr for ESwitcherType fails!";
		return false;
	}
	pElem_eType->SetAttribute("value", pszEnum_eType);
	pElem_eType->SetAttribute("comment", ToUTF8Ptr("开关类型"));
	if(rElement.LinkEndChild(pElem_eType.get()) != NULL)
		pElem_eType.release();
	unique_ptr<TiXmlElement> pElem_bOpen(new TiXmlElement("bool"));
	if(pElem_bOpen == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_bOpen->SetAttribute("name", "bOpen");
	pElem_bOpen->SetAttribute("value", NumberToString(s.bOpen).c_str());
	pElem_bOpen->SetAttribute("comment", ToUTF8Ptr("开关状态"));
	if(rElement.LinkEndChild(pElem_bOpen.get()) != NULL)
		pElem_bOpen.release();
	return true;
}

#endif

SBlockerAppear::SBlockerAppear() : dwBlockerID(0) { }

SBlockerAppear::SBlockerAppear(UINT32 dwBlockerID_, const TVecPosition& vecPos_) : dwBlockerID(dwBlockerID_), vecPos(vecPos_) { }

SBlockerAppear::SBlockerAppear(SBlockerAppear&& src) : dwBlockerID(src.dwBlockerID), vecPos(move(src.vecPos)) { }

SBlockerAppear& SBlockerAppear::operator=(SBlockerAppear&& rhs)
{
	if(this != &rhs)
	{
		this->~SBlockerAppear();
		new (this) SBlockerAppear(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SBlockerAppear& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.dwBlockerID;
	src >> s.vecPos;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SBlockerAppear& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.dwBlockerID;
	src << s.vecPos;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SBlockerAppear& s)
{
	if(strcmp(rElement.Value(), "SBlockerAppear") != 0)
	{
		LOG_CRI << "rElement is not SBlockerAppear!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwBlockerID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwBlockerID") != 0)
	{
		LOG_CRI << "Attribute: name is not dwBlockerID!";
		return false;
	}
	const char* pszVal_dwBlockerID = pElemChild->Attribute("value");
	if(pszVal_dwBlockerID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwBlockerID, s.dwBlockerID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecPos is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecPosition") != 0)
	{
		LOG_CRI << "pElemChild is not TVecPosition!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecPos") != 0)
	{
		LOG_CRI << "Attribute: name is not vecPos!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecPos))
	{
		LOG_CRI << "VectorFromXML for vecPos fails!";
		return false;
	}
	return true;
}

bool ToXML(const SBlockerAppear& s, TiXmlElement& rElement)
{
	rElement.SetValue("SBlockerAppear");
	rElement.SetAttribute("type", ToUTF8Ptr("阻挡物外观"));
	unique_ptr<TiXmlElement> pElem_dwBlockerID(new TiXmlElement("UINT32"));
	if(pElem_dwBlockerID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwBlockerID->SetAttribute("name", "dwBlockerID");
	pElem_dwBlockerID->SetAttribute("value", NumberToString(s.dwBlockerID).c_str());
	pElem_dwBlockerID->SetAttribute("comment", ToUTF8Ptr("阻挡物类型ID,表格数据"));
	if(rElement.LinkEndChild(pElem_dwBlockerID.get()) != NULL)
		pElem_dwBlockerID.release();
	unique_ptr<TiXmlElement> pElem_vecPos(new TiXmlElement("TVecPosition"));
	if(pElem_vecPos == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecPos->SetAttribute("name", "vecPos");
	if(!VectorToXML(s.vecPos, *pElem_vecPos))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecPos->SetAttribute("comment", ToUTF8Ptr("阻挡物阻挡坐标点"));
	if(rElement.LinkEndChild(pElem_vecPos.get()) != NULL)
		pElem_vecPos.release();
	return true;
}

#endif

SAreaAppear::SAreaAppear() : wAreaID(0) { }

SAreaAppear::SAreaAppear(UINT16 wAreaID_) : wAreaID(wAreaID_) { }

CInArchive& operator>>(CInArchive& src, SAreaAppear& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.wAreaID;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SAreaAppear& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.wAreaID;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SAreaAppear& s)
{
	if(strcmp(rElement.Value(), "SAreaAppear") != 0)
	{
		LOG_CRI << "rElement is not SAreaAppear!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wAreaID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wAreaID") != 0)
	{
		LOG_CRI << "Attribute: name is not wAreaID!";
		return false;
	}
	const char* pszVal_wAreaID = pElemChild->Attribute("value");
	if(pszVal_wAreaID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wAreaID, s.wAreaID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SAreaAppear& s, TiXmlElement& rElement)
{
	rElement.SetValue("SAreaAppear");
	rElement.SetAttribute("type", ToUTF8Ptr("区域外观"));
	unique_ptr<TiXmlElement> pElem_wAreaID(new TiXmlElement("UINT16"));
	if(pElem_wAreaID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wAreaID->SetAttribute("name", "wAreaID");
	pElem_wAreaID->SetAttribute("value", NumberToString(s.wAreaID).c_str());
	pElem_wAreaID->SetAttribute("comment", ToUTF8Ptr("区域类型ID，表格数据"));
	if(rElement.LinkEndChild(pElem_wAreaID.get()) != NULL)
		pElem_wAreaID.release();
	return true;
}

#endif

} //namespace NMapProt
