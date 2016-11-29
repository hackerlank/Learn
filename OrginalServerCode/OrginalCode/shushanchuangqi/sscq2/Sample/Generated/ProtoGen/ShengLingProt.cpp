/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    ShengLingProt.cpp
//  Purpose:      圣陵协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "ShengLingProt.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NShengLingProt
{

#ifdef PROT_USE_XML

const char* EnumValToStr(EShengLingResult e)
{
	switch(e)
	{
	case EShengLingResultSuc:
		return "EShengLingResultSuc";
	case EShengLingResultPackFul:
		return "EShengLingResultPackFul";
	case EShengLingResultPrizeTaked:
		return "EShengLingResultPrizeTaked";
	case EShengLingResultFailed:
		return "EShengLingResultFailed";
	case EShengLingResultGoldLack:
		return "EShengLingResultGoldLack";
	case EShengLingResultEnterLack:
		return "EShengLingResultEnterLack";
	case EShengLingResultLifeLack:
		return "EShengLingResultLifeLack";
	case EShengLingResultControlDiceLack:
		return "EShengLingResultControlDiceLack";
	case EShengLingResultTurnDiceLack:
		return "EShengLingResultTurnDiceLack";
	case EShengLingResultScoreLack:
		return "EShengLingResultScoreLack";
	case EShengLingResultStepLack:
		return "EShengLingResultStepLack";
	case EShengLingResultNotFinish:
		return "EShengLingResultNotFinish";
	case EShengLingResultTypeError:
		return "EShengLingResultTypeError";
	case EShengLingResultError:
		return "EShengLingResultError";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EShengLingResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EShengLingResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("EShengLingResultSuc", EShengLingResultSuc));
		mapStr2Val.insert(make_pair("EShengLingResultPackFul", EShengLingResultPackFul));
		mapStr2Val.insert(make_pair("EShengLingResultPrizeTaked", EShengLingResultPrizeTaked));
		mapStr2Val.insert(make_pair("EShengLingResultFailed", EShengLingResultFailed));
		mapStr2Val.insert(make_pair("EShengLingResultGoldLack", EShengLingResultGoldLack));
		mapStr2Val.insert(make_pair("EShengLingResultEnterLack", EShengLingResultEnterLack));
		mapStr2Val.insert(make_pair("EShengLingResultLifeLack", EShengLingResultLifeLack));
		mapStr2Val.insert(make_pair("EShengLingResultControlDiceLack", EShengLingResultControlDiceLack));
		mapStr2Val.insert(make_pair("EShengLingResultTurnDiceLack", EShengLingResultTurnDiceLack));
		mapStr2Val.insert(make_pair("EShengLingResultScoreLack", EShengLingResultScoreLack));
		mapStr2Val.insert(make_pair("EShengLingResultStepLack", EShengLingResultStepLack));
		mapStr2Val.insert(make_pair("EShengLingResultNotFinish", EShengLingResultNotFinish));
		mapStr2Val.insert(make_pair("EShengLingResultTypeError", EShengLingResultTypeError));
		mapStr2Val.insert(make_pair("EShengLingResultError", EShengLingResultError));
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

const char* EnumValToStr(ECardType e)
{
	switch(e)
	{
	case ECardType_ControlDice:
		return "ECardType_ControlDice";
	case ECardType_TurnDice:
		return "ECardType_TurnDice";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, ECardType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, ECardType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("ECardType_ControlDice", ECardType_ControlDice));
		mapStr2Val.insert(make_pair("ECardType_TurnDice", ECardType_TurnDice));
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

const char* EnumValToStr(EGridType e)
{
	switch(e)
	{
	case EGridType_None:
		return "EGridType_None";
	case EGridType_Empty:
		return "EGridType_Empty";
	case EGridType_Normal:
		return "EGridType_Normal";
	case EGridType_Elite:
		return "EGridType_Elite";
	case EGridType_Boss:
		return "EGridType_Boss";
	case EGridType_Big:
		return "EGridType_Big";
	case EGridType_Mid:
		return "EGridType_Mid";
	case EGridType_Small:
		return "EGridType_Small";
	case EGridType_Born:
		return "EGridType_Born";
	case EGridType_Random:
		return "EGridType_Random";
	case EGridType_Motu:
		return "EGridType_Motu";
	case EGridType_Pintu:
		return "EGridType_Pintu";
	case EGridType_Zadan:
		return "EGridType_Zadan";
	case EGridType_Go:
		return "EGridType_Go";
	case EGridType_End:
		return "EGridType_End";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EGridType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EGridType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("EGridType_None", EGridType_None));
		mapStr2Val.insert(make_pair("EGridType_Empty", EGridType_Empty));
		mapStr2Val.insert(make_pair("EGridType_Normal", EGridType_Normal));
		mapStr2Val.insert(make_pair("EGridType_Elite", EGridType_Elite));
		mapStr2Val.insert(make_pair("EGridType_Boss", EGridType_Boss));
		mapStr2Val.insert(make_pair("EGridType_Big", EGridType_Big));
		mapStr2Val.insert(make_pair("EGridType_Mid", EGridType_Mid));
		mapStr2Val.insert(make_pair("EGridType_Small", EGridType_Small));
		mapStr2Val.insert(make_pair("EGridType_Born", EGridType_Born));
		mapStr2Val.insert(make_pair("EGridType_Random", EGridType_Random));
		mapStr2Val.insert(make_pair("EGridType_Motu", EGridType_Motu));
		mapStr2Val.insert(make_pair("EGridType_Pintu", EGridType_Pintu));
		mapStr2Val.insert(make_pair("EGridType_Zadan", EGridType_Zadan));
		mapStr2Val.insert(make_pair("EGridType_Go", EGridType_Go));
		mapStr2Val.insert(make_pair("EGridType_End", EGridType_End));
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

const char* EnumValToStr(EBuyType e)
{
	switch(e)
	{
	case EBuyType_ControlDice:
		return "EBuyType_ControlDice";
	case EBuyType_TurnCard:
		return "EBuyType_TurnCard";
	case EBuyType_Life:
		return "EBuyType_Life";
	case EBuyType_Enter:
		return "EBuyType_Enter";
	case EBuyType_Step:
		return "EBuyType_Step";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EBuyType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EBuyType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("EBuyType_ControlDice", EBuyType_ControlDice));
		mapStr2Val.insert(make_pair("EBuyType_TurnCard", EBuyType_TurnCard));
		mapStr2Val.insert(make_pair("EBuyType_Life", EBuyType_Life));
		mapStr2Val.insert(make_pair("EBuyType_Enter", EBuyType_Enter));
		mapStr2Val.insert(make_pair("EBuyType_Step", EBuyType_Step));
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

SGrid::SGrid() : byIndex(0), byLevel(0), eGridType((EGridType)0), wNoteID(0), bFinished(false), 
			bRandom(false) { }

SGrid::SGrid(UINT8 byIndex_, UINT8 byLevel_, EGridType eGridType_, UINT16 wNoteID_, bool bFinished_, 
			bool bRandom_)
			: byIndex(byIndex_), byLevel(byLevel_), eGridType(eGridType_), wNoteID(wNoteID_), bFinished(bFinished_), 
			bRandom(bRandom_) { }

CInArchive& operator>>(CInArchive& src, SGrid& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.byIndex;
	src >> s.byLevel;
	src >> (UINT8&)s.eGridType;
	src >> s.wNoteID;
	src >> s.bFinished;
	src >> s.bRandom;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SGrid& s)
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
	src << s.byLevel;
	src << (UINT8&)s.eGridType;
	src << s.wNoteID;
	src << s.bFinished;
	src << s.bRandom;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SGrid& s)
{
	if(strcmp(rElement.Value(), "SGrid") != 0)
	{
		LOG_CRI << "rElement is not SGrid!";
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
		LOG_CRI << "pElemChild for eGridType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "EGridType") != 0)
	{
		LOG_CRI << "pElemChild is not EGridType!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eGridType") != 0)
	{
		LOG_CRI << "Attribute: name is not eGridType!";
		return false;
	}
	const char* pszVal_eGridType = pElemChild->Attribute("value");
	if(pszVal_eGridType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!EnumStrToVal(pszVal_eGridType, s.eGridType))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wNoteID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wNoteID") != 0)
	{
		LOG_CRI << "Attribute: name is not wNoteID!";
		return false;
	}
	const char* pszVal_wNoteID = pElemChild->Attribute("value");
	if(pszVal_wNoteID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wNoteID, s.wNoteID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for bFinished is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "bool") != 0)
	{
		LOG_CRI << "pElemChild is not bool!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "bFinished") != 0)
	{
		LOG_CRI << "Attribute: name is not bFinished!";
		return false;
	}
	const char* pszVal_bFinished = pElemChild->Attribute("value");
	if(pszVal_bFinished == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_bFinished, s.bFinished))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for bRandom is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "bool") != 0)
	{
		LOG_CRI << "pElemChild is not bool!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "bRandom") != 0)
	{
		LOG_CRI << "Attribute: name is not bRandom!";
		return false;
	}
	const char* pszVal_bRandom = pElemChild->Attribute("value");
	if(pszVal_bRandom == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_bRandom, s.bRandom))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SGrid& s, TiXmlElement& rElement)
{
	rElement.SetValue("SGrid");
	rElement.SetAttribute("type", ToUTF8Ptr("格子数据"));
	unique_ptr<TiXmlElement> pElem_byIndex(new TiXmlElement("UINT8"));
	if(pElem_byIndex == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byIndex->SetAttribute("name", "byIndex");
	pElem_byIndex->SetAttribute("value", NumberToString(s.byIndex).c_str());
	pElem_byIndex->SetAttribute("comment", ToUTF8Ptr("格子ID"));
	if(rElement.LinkEndChild(pElem_byIndex.get()) != NULL)
		pElem_byIndex.release();
	unique_ptr<TiXmlElement> pElem_byLevel(new TiXmlElement("UINT8"));
	if(pElem_byLevel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byLevel->SetAttribute("name", "byLevel");
	pElem_byLevel->SetAttribute("value", NumberToString(s.byLevel).c_str());
	pElem_byLevel->SetAttribute("comment", ToUTF8Ptr("格子所在层"));
	if(rElement.LinkEndChild(pElem_byLevel.get()) != NULL)
		pElem_byLevel.release();
	unique_ptr<TiXmlElement> pElem_eGridType(new TiXmlElement("EGridType"));
	if(pElem_eGridType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eGridType->SetAttribute("name", "eGridType");
	const char* pszEnum_eGridType = EnumValToStr(s.eGridType);
	if(pszEnum_eGridType == NULL)
	{
		LOG_CRI << "EnumValToStr for EGridType fails!";
		return false;
	}
	pElem_eGridType->SetAttribute("value", pszEnum_eGridType);
	pElem_eGridType->SetAttribute("comment", ToUTF8Ptr("格子类型"));
	if(rElement.LinkEndChild(pElem_eGridType.get()) != NULL)
		pElem_eGridType.release();
	unique_ptr<TiXmlElement> pElem_wNoteID(new TiXmlElement("UINT16"));
	if(pElem_wNoteID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wNoteID->SetAttribute("name", "wNoteID");
	pElem_wNoteID->SetAttribute("value", NumberToString(s.wNoteID).c_str());
	pElem_wNoteID->SetAttribute("comment", ToUTF8Ptr("格子记录数据"));
	if(rElement.LinkEndChild(pElem_wNoteID.get()) != NULL)
		pElem_wNoteID.release();
	unique_ptr<TiXmlElement> pElem_bFinished(new TiXmlElement("bool"));
	if(pElem_bFinished == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_bFinished->SetAttribute("name", "bFinished");
	pElem_bFinished->SetAttribute("value", NumberToString(s.bFinished).c_str());
	pElem_bFinished->SetAttribute("comment", ToUTF8Ptr("是否完成"));
	if(rElement.LinkEndChild(pElem_bFinished.get()) != NULL)
		pElem_bFinished.release();
	unique_ptr<TiXmlElement> pElem_bRandom(new TiXmlElement("bool"));
	if(pElem_bRandom == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_bRandom->SetAttribute("name", "bRandom");
	pElem_bRandom->SetAttribute("value", NumberToString(s.bRandom).c_str());
	pElem_bRandom->SetAttribute("comment", ToUTF8Ptr("是否随机格子"));
	if(rElement.LinkEndChild(pElem_bRandom.get()) != NULL)
		pElem_bRandom.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecGrid& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SGrid s;
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

bool VectorToXML(const TVecGrid& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SGrid"));
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

SCard::SCard() : eCardType((ECardType)0), byBuy(0), byUse(0), byBuyForToday(0) { }

SCard::SCard(ECardType eCardType_, UINT8 byBuy_, UINT8 byUse_, UINT8 byBuyForToday_) : eCardType(eCardType_), byBuy(byBuy_), byUse(byUse_), byBuyForToday(byBuyForToday_) { }

CInArchive& operator>>(CInArchive& src, SCard& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (UINT8&)s.eCardType;
	src >> s.byBuy;
	src >> s.byUse;
	src >> s.byBuyForToday;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SCard& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (UINT8&)s.eCardType;
	src << s.byBuy;
	src << s.byUse;
	src << s.byBuyForToday;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SCard& s)
{
	if(strcmp(rElement.Value(), "SCard") != 0)
	{
		LOG_CRI << "rElement is not SCard!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eCardType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "ECardType") != 0)
	{
		LOG_CRI << "pElemChild is not ECardType!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eCardType") != 0)
	{
		LOG_CRI << "Attribute: name is not eCardType!";
		return false;
	}
	const char* pszVal_eCardType = pElemChild->Attribute("value");
	if(pszVal_eCardType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!EnumStrToVal(pszVal_eCardType, s.eCardType))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byBuy is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byBuy") != 0)
	{
		LOG_CRI << "Attribute: name is not byBuy!";
		return false;
	}
	const char* pszVal_byBuy = pElemChild->Attribute("value");
	if(pszVal_byBuy == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byBuy, s.byBuy))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byUse is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byUse") != 0)
	{
		LOG_CRI << "Attribute: name is not byUse!";
		return false;
	}
	const char* pszVal_byUse = pElemChild->Attribute("value");
	if(pszVal_byUse == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byUse, s.byUse))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byBuyForToday is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byBuyForToday") != 0)
	{
		LOG_CRI << "Attribute: name is not byBuyForToday!";
		return false;
	}
	const char* pszVal_byBuyForToday = pElemChild->Attribute("value");
	if(pszVal_byBuyForToday == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byBuyForToday, s.byBuyForToday))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SCard& s, TiXmlElement& rElement)
{
	rElement.SetValue("SCard");
	rElement.SetAttribute("type", ToUTF8Ptr("卡片信息"));
	unique_ptr<TiXmlElement> pElem_eCardType(new TiXmlElement("ECardType"));
	if(pElem_eCardType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eCardType->SetAttribute("name", "eCardType");
	const char* pszEnum_eCardType = EnumValToStr(s.eCardType);
	if(pszEnum_eCardType == NULL)
	{
		LOG_CRI << "EnumValToStr for ECardType fails!";
		return false;
	}
	pElem_eCardType->SetAttribute("value", pszEnum_eCardType);
	pElem_eCardType->SetAttribute("comment", ToUTF8Ptr("卡片类型"));
	if(rElement.LinkEndChild(pElem_eCardType.get()) != NULL)
		pElem_eCardType.release();
	unique_ptr<TiXmlElement> pElem_byBuy(new TiXmlElement("UINT8"));
	if(pElem_byBuy == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byBuy->SetAttribute("name", "byBuy");
	pElem_byBuy->SetAttribute("value", NumberToString(s.byBuy).c_str());
	pElem_byBuy->SetAttribute("comment", ToUTF8Ptr("玩家购买次数"));
	if(rElement.LinkEndChild(pElem_byBuy.get()) != NULL)
		pElem_byBuy.release();
	unique_ptr<TiXmlElement> pElem_byUse(new TiXmlElement("UINT8"));
	if(pElem_byUse == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byUse->SetAttribute("name", "byUse");
	pElem_byUse->SetAttribute("value", NumberToString(s.byUse).c_str());
	pElem_byUse->SetAttribute("comment", ToUTF8Ptr("当日使用次数"));
	if(rElement.LinkEndChild(pElem_byUse.get()) != NULL)
		pElem_byUse.release();
	unique_ptr<TiXmlElement> pElem_byBuyForToday(new TiXmlElement("UINT8"));
	if(pElem_byBuyForToday == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byBuyForToday->SetAttribute("name", "byBuyForToday");
	pElem_byBuyForToday->SetAttribute("value", NumberToString(s.byBuyForToday).c_str());
	pElem_byBuyForToday->SetAttribute("comment", ToUTF8Ptr("当日购买次数"));
	if(rElement.LinkEndChild(pElem_byBuyForToday.get()) != NULL)
		pElem_byBuyForToday.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecCard& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SCard s;
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

bool VectorToXML(const TVecCard& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SCard"));
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

SPlayerInfo::SPlayerInfo() : qwRoleID(0), byCurLevel(0), byCurIndex(0), byPreLevel(0), byPreIndex(0), 
			byBuy(0), byUse(0), byNext(0) { }

SPlayerInfo::SPlayerInfo(UINT64 qwRoleID_, UINT8 byCurLevel_, UINT8 byCurIndex_, UINT8 byPreLevel_, UINT8 byPreIndex_, 
			UINT8 byBuy_, UINT8 byUse_, UINT8 byNext_, const TVecGrid& vecGrid_)
			: qwRoleID(qwRoleID_), byCurLevel(byCurLevel_), byCurIndex(byCurIndex_), byPreLevel(byPreLevel_), byPreIndex(byPreIndex_), 
			byBuy(byBuy_), byUse(byUse_), byNext(byNext_), vecGrid(vecGrid_) { }

SPlayerInfo::SPlayerInfo(SPlayerInfo&& src) : qwRoleID(src.qwRoleID), byCurLevel(src.byCurLevel), byCurIndex(src.byCurIndex), byPreLevel(src.byPreLevel), byPreIndex(src.byPreIndex), 
			byBuy(src.byBuy), byUse(src.byUse), byNext(src.byNext), vecGrid(move(src.vecGrid)) { }

SPlayerInfo& SPlayerInfo::operator=(SPlayerInfo&& rhs)
{
	if(this != &rhs)
	{
		this->~SPlayerInfo();
		new (this) SPlayerInfo(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SPlayerInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwRoleID;
	src >> s.byCurLevel;
	src >> s.byCurIndex;
	src >> s.byPreLevel;
	src >> s.byPreIndex;
	src >> s.byBuy;
	src >> s.byUse;
	src >> s.byNext;
	src >> s.vecGrid;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SPlayerInfo& s)
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
	src << s.byCurLevel;
	src << s.byCurIndex;
	src << s.byPreLevel;
	src << s.byPreIndex;
	src << s.byBuy;
	src << s.byUse;
	src << s.byNext;
	src << s.vecGrid;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SPlayerInfo& s)
{
	if(strcmp(rElement.Value(), "SPlayerInfo") != 0)
	{
		LOG_CRI << "rElement is not SPlayerInfo!";
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
		LOG_CRI << "pElemChild for byCurLevel is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byCurLevel") != 0)
	{
		LOG_CRI << "Attribute: name is not byCurLevel!";
		return false;
	}
	const char* pszVal_byCurLevel = pElemChild->Attribute("value");
	if(pszVal_byCurLevel == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byCurLevel, s.byCurLevel))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byCurIndex is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byCurIndex") != 0)
	{
		LOG_CRI << "Attribute: name is not byCurIndex!";
		return false;
	}
	const char* pszVal_byCurIndex = pElemChild->Attribute("value");
	if(pszVal_byCurIndex == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byCurIndex, s.byCurIndex))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byPreLevel is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byPreLevel") != 0)
	{
		LOG_CRI << "Attribute: name is not byPreLevel!";
		return false;
	}
	const char* pszVal_byPreLevel = pElemChild->Attribute("value");
	if(pszVal_byPreLevel == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byPreLevel, s.byPreLevel))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byPreIndex is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byPreIndex") != 0)
	{
		LOG_CRI << "Attribute: name is not byPreIndex!";
		return false;
	}
	const char* pszVal_byPreIndex = pElemChild->Attribute("value");
	if(pszVal_byPreIndex == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byPreIndex, s.byPreIndex))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byBuy is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byBuy") != 0)
	{
		LOG_CRI << "Attribute: name is not byBuy!";
		return false;
	}
	const char* pszVal_byBuy = pElemChild->Attribute("value");
	if(pszVal_byBuy == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byBuy, s.byBuy))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byUse is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byUse") != 0)
	{
		LOG_CRI << "Attribute: name is not byUse!";
		return false;
	}
	const char* pszVal_byUse = pElemChild->Attribute("value");
	if(pszVal_byUse == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byUse, s.byUse))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byNext is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byNext") != 0)
	{
		LOG_CRI << "Attribute: name is not byNext!";
		return false;
	}
	const char* pszVal_byNext = pElemChild->Attribute("value");
	if(pszVal_byNext == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byNext, s.byNext))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecGrid is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecGrid") != 0)
	{
		LOG_CRI << "pElemChild is not TVecGrid!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecGrid") != 0)
	{
		LOG_CRI << "Attribute: name is not vecGrid!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecGrid))
	{
		LOG_CRI << "VectorFromXML for vecGrid fails!";
		return false;
	}
	return true;
}

bool ToXML(const SPlayerInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SPlayerInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("玩家信息"));
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
	unique_ptr<TiXmlElement> pElem_byCurLevel(new TiXmlElement("UINT8"));
	if(pElem_byCurLevel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byCurLevel->SetAttribute("name", "byCurLevel");
	pElem_byCurLevel->SetAttribute("value", NumberToString(s.byCurLevel).c_str());
	pElem_byCurLevel->SetAttribute("comment", ToUTF8Ptr("玩家当前所在层"));
	if(rElement.LinkEndChild(pElem_byCurLevel.get()) != NULL)
		pElem_byCurLevel.release();
	unique_ptr<TiXmlElement> pElem_byCurIndex(new TiXmlElement("UINT8"));
	if(pElem_byCurIndex == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byCurIndex->SetAttribute("name", "byCurIndex");
	pElem_byCurIndex->SetAttribute("value", NumberToString(s.byCurIndex).c_str());
	pElem_byCurIndex->SetAttribute("comment", ToUTF8Ptr("玩家当前所在层格子ID"));
	if(rElement.LinkEndChild(pElem_byCurIndex.get()) != NULL)
		pElem_byCurIndex.release();
	unique_ptr<TiXmlElement> pElem_byPreLevel(new TiXmlElement("UINT8"));
	if(pElem_byPreLevel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byPreLevel->SetAttribute("name", "byPreLevel");
	pElem_byPreLevel->SetAttribute("value", NumberToString(s.byPreLevel).c_str());
	pElem_byPreLevel->SetAttribute("comment", ToUTF8Ptr("玩家上一次所在层"));
	if(rElement.LinkEndChild(pElem_byPreLevel.get()) != NULL)
		pElem_byPreLevel.release();
	unique_ptr<TiXmlElement> pElem_byPreIndex(new TiXmlElement("UINT8"));
	if(pElem_byPreIndex == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byPreIndex->SetAttribute("name", "byPreIndex");
	pElem_byPreIndex->SetAttribute("value", NumberToString(s.byPreIndex).c_str());
	pElem_byPreIndex->SetAttribute("comment", ToUTF8Ptr("玩家上一次所在层格子ID"));
	if(rElement.LinkEndChild(pElem_byPreIndex.get()) != NULL)
		pElem_byPreIndex.release();
	unique_ptr<TiXmlElement> pElem_byBuy(new TiXmlElement("UINT8"));
	if(pElem_byBuy == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byBuy->SetAttribute("name", "byBuy");
	pElem_byBuy->SetAttribute("value", NumberToString(s.byBuy).c_str());
	pElem_byBuy->SetAttribute("comment", ToUTF8Ptr("玩家购买生命数"));
	if(rElement.LinkEndChild(pElem_byBuy.get()) != NULL)
		pElem_byBuy.release();
	unique_ptr<TiXmlElement> pElem_byUse(new TiXmlElement("UINT8"));
	if(pElem_byUse == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byUse->SetAttribute("name", "byUse");
	pElem_byUse->SetAttribute("value", NumberToString(s.byUse).c_str());
	pElem_byUse->SetAttribute("comment", ToUTF8Ptr("玩家当前使用生命数"));
	if(rElement.LinkEndChild(pElem_byUse.get()) != NULL)
		pElem_byUse.release();
	unique_ptr<TiXmlElement> pElem_byNext(new TiXmlElement("UINT8"));
	if(pElem_byNext == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byNext->SetAttribute("name", "byNext");
	pElem_byNext->SetAttribute("value", NumberToString(s.byNext).c_str());
	pElem_byNext->SetAttribute("comment", ToUTF8Ptr("是否进入下一层"));
	if(rElement.LinkEndChild(pElem_byNext.get()) != NULL)
		pElem_byNext.release();
	unique_ptr<TiXmlElement> pElem_vecGrid(new TiXmlElement("TVecGrid"));
	if(pElem_vecGrid == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecGrid->SetAttribute("name", "vecGrid");
	if(!VectorToXML(s.vecGrid, *pElem_vecGrid))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecGrid->SetAttribute("comment", ToUTF8Ptr("格子数据"));
	if(rElement.LinkEndChild(pElem_vecGrid.get()) != NULL)
		pElem_vecGrid.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecPlayerInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SPlayerInfo s;
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

bool VectorToXML(const TVecPlayerInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SPlayerInfo"));
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

SShengLingInfo::SShengLingInfo() : qwRoleID(0), wPassword(0), byDir(0), byLevel(0), byIndex(0), 
			byBuyLife(0), byUseLife(0), byStep(0), byScore(0), byBit(0), 
			byBuyLifeToday(0), byFirst(0) { }

SShengLingInfo::SShengLingInfo(SShengLingInfo&& src) : qwRoleID(src.qwRoleID), wPassword(src.wPassword), byDir(src.byDir), byLevel(src.byLevel), byIndex(src.byIndex), 
			byBuyLife(src.byBuyLife), byUseLife(src.byUseLife), byStep(src.byStep), byScore(src.byScore), byBit(src.byBit), 
			byBuyLifeToday(src.byBuyLifeToday), byFirst(src.byFirst), vecGrid(move(src.vecGrid)), vecCard(move(src.vecCard)), vecItem(move(src.vecItem)) { }

SShengLingInfo& SShengLingInfo::operator=(SShengLingInfo&& rhs)
{
	if(this != &rhs)
	{
		this->~SShengLingInfo();
		new (this) SShengLingInfo(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SShengLingInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwRoleID;
	src >> s.wPassword;
	src >> s.byDir;
	src >> s.byLevel;
	src >> s.byIndex;
	src >> s.byBuyLife;
	src >> s.byUseLife;
	src >> s.byStep;
	src >> s.byScore;
	src >> s.byBit;
	src >> s.byBuyLifeToday;
	src >> s.byFirst;
	src >> s.vecGrid;
	src >> s.vecCard;
	src >> s.vecItem;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SShengLingInfo& s)
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
	src << s.wPassword;
	src << s.byDir;
	src << s.byLevel;
	src << s.byIndex;
	src << s.byBuyLife;
	src << s.byUseLife;
	src << s.byStep;
	src << s.byScore;
	src << s.byBit;
	src << s.byBuyLifeToday;
	src << s.byFirst;
	src << s.vecGrid;
	src << s.vecCard;
	src << s.vecItem;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SShengLingInfo& s)
{
	if(strcmp(rElement.Value(), "SShengLingInfo") != 0)
	{
		LOG_CRI << "rElement is not SShengLingInfo!";
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
		LOG_CRI << "pElemChild for wPassword is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wPassword") != 0)
	{
		LOG_CRI << "Attribute: name is not wPassword!";
		return false;
	}
	const char* pszVal_wPassword = pElemChild->Attribute("value");
	if(pszVal_wPassword == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wPassword, s.wPassword))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byDir is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byDir") != 0)
	{
		LOG_CRI << "Attribute: name is not byDir!";
		return false;
	}
	const char* pszVal_byDir = pElemChild->Attribute("value");
	if(pszVal_byDir == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byDir, s.byDir))
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
		LOG_CRI << "pElemChild for byBuyLife is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byBuyLife") != 0)
	{
		LOG_CRI << "Attribute: name is not byBuyLife!";
		return false;
	}
	const char* pszVal_byBuyLife = pElemChild->Attribute("value");
	if(pszVal_byBuyLife == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byBuyLife, s.byBuyLife))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byUseLife is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byUseLife") != 0)
	{
		LOG_CRI << "Attribute: name is not byUseLife!";
		return false;
	}
	const char* pszVal_byUseLife = pElemChild->Attribute("value");
	if(pszVal_byUseLife == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byUseLife, s.byUseLife))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byStep is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byStep") != 0)
	{
		LOG_CRI << "Attribute: name is not byStep!";
		return false;
	}
	const char* pszVal_byStep = pElemChild->Attribute("value");
	if(pszVal_byStep == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byStep, s.byStep))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byScore is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byScore") != 0)
	{
		LOG_CRI << "Attribute: name is not byScore!";
		return false;
	}
	const char* pszVal_byScore = pElemChild->Attribute("value");
	if(pszVal_byScore == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byScore, s.byScore))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byBit is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byBit") != 0)
	{
		LOG_CRI << "Attribute: name is not byBit!";
		return false;
	}
	const char* pszVal_byBit = pElemChild->Attribute("value");
	if(pszVal_byBit == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byBit, s.byBit))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byBuyLifeToday is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byBuyLifeToday") != 0)
	{
		LOG_CRI << "Attribute: name is not byBuyLifeToday!";
		return false;
	}
	const char* pszVal_byBuyLifeToday = pElemChild->Attribute("value");
	if(pszVal_byBuyLifeToday == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byBuyLifeToday, s.byBuyLifeToday))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byFirst is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byFirst") != 0)
	{
		LOG_CRI << "Attribute: name is not byFirst!";
		return false;
	}
	const char* pszVal_byFirst = pElemChild->Attribute("value");
	if(pszVal_byFirst == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byFirst, s.byFirst))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecGrid is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecGrid") != 0)
	{
		LOG_CRI << "pElemChild is not TVecGrid!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecGrid") != 0)
	{
		LOG_CRI << "Attribute: name is not vecGrid!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecGrid))
	{
		LOG_CRI << "VectorFromXML for vecGrid fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecCard is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecCard") != 0)
	{
		LOG_CRI << "pElemChild is not TVecCard!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecCard") != 0)
	{
		LOG_CRI << "Attribute: name is not vecCard!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecCard))
	{
		LOG_CRI << "VectorFromXML for vecCard fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecItem is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "ItemProt::TVecItemGenInfo") != 0)
	{
		LOG_CRI << "pElemChild is not ItemProt::TVecItemGenInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecItem") != 0)
	{
		LOG_CRI << "Attribute: name is not vecItem!";
		return false;
	}
	if(!NItemProt::VectorFromXML(*pElemChild, s.vecItem))
	{
		LOG_CRI << "VectorFromXML for vecItem fails!";
		return false;
	}
	return true;
}

bool ToXML(const SShengLingInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SShengLingInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("玩家进入信息"));
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
	unique_ptr<TiXmlElement> pElem_wPassword(new TiXmlElement("UINT16"));
	if(pElem_wPassword == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wPassword->SetAttribute("name", "wPassword");
	pElem_wPassword->SetAttribute("value", NumberToString(s.wPassword).c_str());
	pElem_wPassword->SetAttribute("comment", ToUTF8Ptr("初始密码"));
	if(rElement.LinkEndChild(pElem_wPassword.get()) != NULL)
		pElem_wPassword.release();
	unique_ptr<TiXmlElement> pElem_byDir(new TiXmlElement("UINT8"));
	if(pElem_byDir == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byDir->SetAttribute("name", "byDir");
	pElem_byDir->SetAttribute("value", NumberToString(s.byDir).c_str());
	pElem_byDir->SetAttribute("comment", ToUTF8Ptr("玩家在棋盘中的方向（0表示反向，1表示正向）"));
	if(rElement.LinkEndChild(pElem_byDir.get()) != NULL)
		pElem_byDir.release();
	unique_ptr<TiXmlElement> pElem_byLevel(new TiXmlElement("UINT8"));
	if(pElem_byLevel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byLevel->SetAttribute("name", "byLevel");
	pElem_byLevel->SetAttribute("value", NumberToString(s.byLevel).c_str());
	pElem_byLevel->SetAttribute("comment", ToUTF8Ptr("玩家当前所在层"));
	if(rElement.LinkEndChild(pElem_byLevel.get()) != NULL)
		pElem_byLevel.release();
	unique_ptr<TiXmlElement> pElem_byIndex(new TiXmlElement("UINT8"));
	if(pElem_byIndex == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byIndex->SetAttribute("name", "byIndex");
	pElem_byIndex->SetAttribute("value", NumberToString(s.byIndex).c_str());
	pElem_byIndex->SetAttribute("comment", ToUTF8Ptr("玩家当前所在层格子ID"));
	if(rElement.LinkEndChild(pElem_byIndex.get()) != NULL)
		pElem_byIndex.release();
	unique_ptr<TiXmlElement> pElem_byBuyLife(new TiXmlElement("UINT8"));
	if(pElem_byBuyLife == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byBuyLife->SetAttribute("name", "byBuyLife");
	pElem_byBuyLife->SetAttribute("value", NumberToString(s.byBuyLife).c_str());
	pElem_byBuyLife->SetAttribute("comment", ToUTF8Ptr("玩家购买生命数"));
	if(rElement.LinkEndChild(pElem_byBuyLife.get()) != NULL)
		pElem_byBuyLife.release();
	unique_ptr<TiXmlElement> pElem_byUseLife(new TiXmlElement("UINT8"));
	if(pElem_byUseLife == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byUseLife->SetAttribute("name", "byUseLife");
	pElem_byUseLife->SetAttribute("value", NumberToString(s.byUseLife).c_str());
	pElem_byUseLife->SetAttribute("comment", ToUTF8Ptr("玩家今日使用生命数"));
	if(rElement.LinkEndChild(pElem_byUseLife.get()) != NULL)
		pElem_byUseLife.release();
	unique_ptr<TiXmlElement> pElem_byStep(new TiXmlElement("UINT8"));
	if(pElem_byStep == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byStep->SetAttribute("name", "byStep");
	pElem_byStep->SetAttribute("value", NumberToString(s.byStep).c_str());
	pElem_byStep->SetAttribute("comment", ToUTF8Ptr("玩家在“三消”中剩余步数"));
	if(rElement.LinkEndChild(pElem_byStep.get()) != NULL)
		pElem_byStep.release();
	unique_ptr<TiXmlElement> pElem_byScore(new TiXmlElement("UINT16"));
	if(pElem_byScore == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byScore->SetAttribute("name", "byScore");
	pElem_byScore->SetAttribute("value", NumberToString(s.byScore).c_str());
	pElem_byScore->SetAttribute("comment", ToUTF8Ptr("玩家在“三消”中累计积分"));
	if(rElement.LinkEndChild(pElem_byScore.get()) != NULL)
		pElem_byScore.release();
	unique_ptr<TiXmlElement> pElem_byBit(new TiXmlElement("UINT8"));
	if(pElem_byBit == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byBit->SetAttribute("name", "byBit");
	pElem_byBit->SetAttribute("value", NumberToString(s.byBit).c_str());
	pElem_byBit->SetAttribute("comment", ToUTF8Ptr("玩家在“三消”中奖励领取状态，bit位表示从低到高"));
	if(rElement.LinkEndChild(pElem_byBit.get()) != NULL)
		pElem_byBit.release();
	unique_ptr<TiXmlElement> pElem_byBuyLifeToday(new TiXmlElement("UINT8"));
	if(pElem_byBuyLifeToday == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byBuyLifeToday->SetAttribute("name", "byBuyLifeToday");
	pElem_byBuyLifeToday->SetAttribute("value", NumberToString(s.byBuyLifeToday).c_str());
	pElem_byBuyLifeToday->SetAttribute("comment", ToUTF8Ptr("玩家今天购买生命数"));
	if(rElement.LinkEndChild(pElem_byBuyLifeToday.get()) != NULL)
		pElem_byBuyLifeToday.release();
	unique_ptr<TiXmlElement> pElem_byFirst(new TiXmlElement("UINT8"));
	if(pElem_byFirst == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byFirst->SetAttribute("name", "byFirst");
	pElem_byFirst->SetAttribute("value", NumberToString(s.byFirst).c_str());
	pElem_byFirst->SetAttribute("comment", ToUTF8Ptr("玩家是否第一次进入圣陵"));
	if(rElement.LinkEndChild(pElem_byFirst.get()) != NULL)
		pElem_byFirst.release();
	unique_ptr<TiXmlElement> pElem_vecGrid(new TiXmlElement("TVecGrid"));
	if(pElem_vecGrid == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecGrid->SetAttribute("name", "vecGrid");
	if(!VectorToXML(s.vecGrid, *pElem_vecGrid))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecGrid->SetAttribute("comment", ToUTF8Ptr("格子数据"));
	if(rElement.LinkEndChild(pElem_vecGrid.get()) != NULL)
		pElem_vecGrid.release();
	unique_ptr<TiXmlElement> pElem_vecCard(new TiXmlElement("TVecCard"));
	if(pElem_vecCard == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecCard->SetAttribute("name", "vecCard");
	if(!VectorToXML(s.vecCard, *pElem_vecCard))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecCard->SetAttribute("comment", ToUTF8Ptr("卡片数据"));
	if(rElement.LinkEndChild(pElem_vecCard.get()) != NULL)
		pElem_vecCard.release();
	unique_ptr<TiXmlElement> pElem_vecItem(new TiXmlElement("ItemProt::TVecItemGenInfo"));
	if(pElem_vecItem == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecItem->SetAttribute("name", "vecItem");
	if(!NItemProt::VectorToXML(s.vecItem, *pElem_vecItem))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecItem->SetAttribute("comment", ToUTF8Ptr("获得的奖励数据"));
	if(rElement.LinkEndChild(pElem_vecItem.get()) != NULL)
		pElem_vecItem.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecShengLingInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SShengLingInfo s;
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

bool VectorToXML(const TVecShengLingInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SShengLingInfo"));
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

SShengLingInfo2DB::SShengLingInfo2DB() : qwRoleID(0), byLevel(0), byIndex(0), byType(0), wNoteID(0), 
			byRandom(0), byFinish(0) { }

SShengLingInfo2DB::SShengLingInfo2DB(UINT64 qwRoleID_, UINT8 byLevel_, UINT8 byIndex_, UINT8 byType_, UINT16 wNoteID_, 
			UINT8 byRandom_, UINT8 byFinish_)
			: qwRoleID(qwRoleID_), byLevel(byLevel_), byIndex(byIndex_), byType(byType_), wNoteID(wNoteID_), 
			byRandom(byRandom_), byFinish(byFinish_) { }

CInArchive& operator>>(CInArchive& src, SShengLingInfo2DB& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwRoleID;
	src >> s.byLevel;
	src >> s.byIndex;
	src >> s.byType;
	src >> s.wNoteID;
	src >> s.byRandom;
	src >> s.byFinish;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SShengLingInfo2DB& s)
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
	src << s.byLevel;
	src << s.byIndex;
	src << s.byType;
	src << s.wNoteID;
	src << s.byRandom;
	src << s.byFinish;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SShengLingInfo2DB& s)
{
	if(strcmp(rElement.Value(), "SShengLingInfo2DB") != 0)
	{
		LOG_CRI << "rElement is not SShengLingInfo2DB!";
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
		LOG_CRI << "pElemChild for byType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byType") != 0)
	{
		LOG_CRI << "Attribute: name is not byType!";
		return false;
	}
	const char* pszVal_byType = pElemChild->Attribute("value");
	if(pszVal_byType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byType, s.byType))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wNoteID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wNoteID") != 0)
	{
		LOG_CRI << "Attribute: name is not wNoteID!";
		return false;
	}
	const char* pszVal_wNoteID = pElemChild->Attribute("value");
	if(pszVal_wNoteID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wNoteID, s.wNoteID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byRandom is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byRandom") != 0)
	{
		LOG_CRI << "Attribute: name is not byRandom!";
		return false;
	}
	const char* pszVal_byRandom = pElemChild->Attribute("value");
	if(pszVal_byRandom == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byRandom, s.byRandom))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byFinish is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byFinish") != 0)
	{
		LOG_CRI << "Attribute: name is not byFinish!";
		return false;
	}
	const char* pszVal_byFinish = pElemChild->Attribute("value");
	if(pszVal_byFinish == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byFinish, s.byFinish))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SShengLingInfo2DB& s, TiXmlElement& rElement)
{
	rElement.SetValue("SShengLingInfo2DB");
	rElement.SetAttribute("type", ToUTF8Ptr("数据库信息"));
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
	unique_ptr<TiXmlElement> pElem_byLevel(new TiXmlElement("UINT8"));
	if(pElem_byLevel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byLevel->SetAttribute("name", "byLevel");
	pElem_byLevel->SetAttribute("value", NumberToString(s.byLevel).c_str());
	pElem_byLevel->SetAttribute("comment", ToUTF8Ptr("玩家所在层"));
	if(rElement.LinkEndChild(pElem_byLevel.get()) != NULL)
		pElem_byLevel.release();
	unique_ptr<TiXmlElement> pElem_byIndex(new TiXmlElement("UINT8"));
	if(pElem_byIndex == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byIndex->SetAttribute("name", "byIndex");
	pElem_byIndex->SetAttribute("value", NumberToString(s.byIndex).c_str());
	pElem_byIndex->SetAttribute("comment", ToUTF8Ptr("格子ID"));
	if(rElement.LinkEndChild(pElem_byIndex.get()) != NULL)
		pElem_byIndex.release();
	unique_ptr<TiXmlElement> pElem_byType(new TiXmlElement("UINT8"));
	if(pElem_byType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byType->SetAttribute("name", "byType");
	pElem_byType->SetAttribute("value", NumberToString(s.byType).c_str());
	pElem_byType->SetAttribute("comment", ToUTF8Ptr("格子类型"));
	if(rElement.LinkEndChild(pElem_byType.get()) != NULL)
		pElem_byType.release();
	unique_ptr<TiXmlElement> pElem_wNoteID(new TiXmlElement("UINT16"));
	if(pElem_wNoteID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wNoteID->SetAttribute("name", "wNoteID");
	pElem_wNoteID->SetAttribute("value", NumberToString(s.wNoteID).c_str());
	pElem_wNoteID->SetAttribute("comment", ToUTF8Ptr("格子中记录ID"));
	if(rElement.LinkEndChild(pElem_wNoteID.get()) != NULL)
		pElem_wNoteID.release();
	unique_ptr<TiXmlElement> pElem_byRandom(new TiXmlElement("UINT8"));
	if(pElem_byRandom == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byRandom->SetAttribute("name", "byRandom");
	pElem_byRandom->SetAttribute("value", NumberToString(s.byRandom).c_str());
	pElem_byRandom->SetAttribute("comment", ToUTF8Ptr("是否随机格子"));
	if(rElement.LinkEndChild(pElem_byRandom.get()) != NULL)
		pElem_byRandom.release();
	unique_ptr<TiXmlElement> pElem_byFinish(new TiXmlElement("UINT8"));
	if(pElem_byFinish == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byFinish->SetAttribute("name", "byFinish");
	pElem_byFinish->SetAttribute("value", NumberToString(s.byFinish).c_str());
	pElem_byFinish->SetAttribute("comment", ToUTF8Ptr("是否完成"));
	if(rElement.LinkEndChild(pElem_byFinish.get()) != NULL)
		pElem_byFinish.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecShengLingInfo2DB& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SShengLingInfo2DB s;
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

bool VectorToXML(const TVecShengLingInfo2DB& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SShengLingInfo2DB"));
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

SShengLingPrize2DB::SShengLingPrize2DB() : qwRoleID(0), wItemID(0), wNum(0) { }

SShengLingPrize2DB::SShengLingPrize2DB(UINT64 qwRoleID_, UINT16 wItemID_, UINT16 wNum_) : qwRoleID(qwRoleID_), wItemID(wItemID_), wNum(wNum_) { }

CInArchive& operator>>(CInArchive& src, SShengLingPrize2DB& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwRoleID;
	src >> s.wItemID;
	src >> s.wNum;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SShengLingPrize2DB& s)
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
	src << s.wItemID;
	src << s.wNum;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SShengLingPrize2DB& s)
{
	if(strcmp(rElement.Value(), "SShengLingPrize2DB") != 0)
	{
		LOG_CRI << "rElement is not SShengLingPrize2DB!";
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
		LOG_CRI << "pElemChild for wNum is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wNum") != 0)
	{
		LOG_CRI << "Attribute: name is not wNum!";
		return false;
	}
	const char* pszVal_wNum = pElemChild->Attribute("value");
	if(pszVal_wNum == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wNum, s.wNum))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SShengLingPrize2DB& s, TiXmlElement& rElement)
{
	rElement.SetValue("SShengLingPrize2DB");
	rElement.SetAttribute("type", ToUTF8Ptr("数据库奖励信息"));
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
	unique_ptr<TiXmlElement> pElem_wItemID(new TiXmlElement("UINT16"));
	if(pElem_wItemID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wItemID->SetAttribute("name", "wItemID");
	pElem_wItemID->SetAttribute("value", NumberToString(s.wItemID).c_str());
	pElem_wItemID->SetAttribute("comment", ToUTF8Ptr("物品"));
	if(rElement.LinkEndChild(pElem_wItemID.get()) != NULL)
		pElem_wItemID.release();
	unique_ptr<TiXmlElement> pElem_wNum(new TiXmlElement("UINT16"));
	if(pElem_wNum == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wNum->SetAttribute("name", "wNum");
	pElem_wNum->SetAttribute("value", NumberToString(s.wNum).c_str());
	pElem_wNum->SetAttribute("comment", ToUTF8Ptr("数量"));
	if(rElement.LinkEndChild(pElem_wNum.get()) != NULL)
		pElem_wNum.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecShengLingPrize2DB& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SShengLingPrize2DB s;
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

bool VectorToXML(const TVecShengLingPrize2DB& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SShengLingPrize2DB"));
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

} //namespace NShengLingProt
