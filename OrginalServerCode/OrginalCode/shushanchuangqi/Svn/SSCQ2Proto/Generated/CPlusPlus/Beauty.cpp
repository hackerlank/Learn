/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    Beauty.cpp
//  Purpose:      美女系统
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "Beauty.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NBeauty
{

#ifdef PROT_USE_XML

const char* EnumValToStr(EBeautyRet e)
{
	switch(e)
	{
	case eBeautyRet_Sucess:
		return "eBeautyRet_Sucess";
	case eBeautyRet_LevelLimit:
		return "eBeautyRet_LevelLimit";
	case eBeautyRet_ErrorCFG:
		return "eBeautyRet_ErrorCFG";
	case eBeautyRet_PackError:
		return "eBeautyRet_PackError";
	case eBeautyRet_MoneyError:
		return "eBeautyRet_MoneyError";
	case eBeautyRet_HeartError:
		return "eBeautyRet_HeartError";
	case eBeautyRet_ErrorID:
		return "eBeautyRet_ErrorID";
	case eBeautyRet_ChatCd:
		return "eBeautyRet_ChatCd";
	case eBeautyRet_LackItem:
		return "eBeautyRet_LackItem";
	case eBeautyRet_ExistBeauty:
		return "eBeautyRet_ExistBeauty";
	case eBeautyRet_GondError:
		return "eBeautyRet_GondError";
	case eBeautyRet_LotterTypeError:
		return "eBeautyRet_LotterTypeError";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EBeautyRet& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EBeautyRet> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eBeautyRet_Sucess", eBeautyRet_Sucess));
		mapStr2Val.insert(make_pair("eBeautyRet_LevelLimit", eBeautyRet_LevelLimit));
		mapStr2Val.insert(make_pair("eBeautyRet_ErrorCFG", eBeautyRet_ErrorCFG));
		mapStr2Val.insert(make_pair("eBeautyRet_PackError", eBeautyRet_PackError));
		mapStr2Val.insert(make_pair("eBeautyRet_MoneyError", eBeautyRet_MoneyError));
		mapStr2Val.insert(make_pair("eBeautyRet_HeartError", eBeautyRet_HeartError));
		mapStr2Val.insert(make_pair("eBeautyRet_ErrorID", eBeautyRet_ErrorID));
		mapStr2Val.insert(make_pair("eBeautyRet_ChatCd", eBeautyRet_ChatCd));
		mapStr2Val.insert(make_pair("eBeautyRet_LackItem", eBeautyRet_LackItem));
		mapStr2Val.insert(make_pair("eBeautyRet_ExistBeauty", eBeautyRet_ExistBeauty));
		mapStr2Val.insert(make_pair("eBeautyRet_GondError", eBeautyRet_GondError));
		mapStr2Val.insert(make_pair("eBeautyRet_LotterTypeError", eBeautyRet_LotterTypeError));
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

const char* EnumValToStr(ELotteryBeautyType e)
{
	switch(e)
	{
	case eLotteryBeautyType_OneSilver:
		return "eLotteryBeautyType_OneSilver";
	case eLotteryBeautyType_OneGold:
		return "eLotteryBeautyType_OneGold";
	case eLotteryBeautyType_OneLoveHeart:
		return "eLotteryBeautyType_OneLoveHeart";
	case eLotteryBeautyType_OneFreeGold:
		return "eLotteryBeautyType_OneFreeGold";
	case eLotteryBeautyType_TenSilver:
		return "eLotteryBeautyType_TenSilver";
	case eLotteryBeautyType_TenGold:
		return "eLotteryBeautyType_TenGold";
	case eLotteryBeautyType_TenLoveHeart:
		return "eLotteryBeautyType_TenLoveHeart";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, ELotteryBeautyType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, ELotteryBeautyType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eLotteryBeautyType_OneSilver", eLotteryBeautyType_OneSilver));
		mapStr2Val.insert(make_pair("eLotteryBeautyType_OneGold", eLotteryBeautyType_OneGold));
		mapStr2Val.insert(make_pair("eLotteryBeautyType_OneLoveHeart", eLotteryBeautyType_OneLoveHeart));
		mapStr2Val.insert(make_pair("eLotteryBeautyType_OneFreeGold", eLotteryBeautyType_OneFreeGold));
		mapStr2Val.insert(make_pair("eLotteryBeautyType_TenSilver", eLotteryBeautyType_TenSilver));
		mapStr2Val.insert(make_pair("eLotteryBeautyType_TenGold", eLotteryBeautyType_TenGold));
		mapStr2Val.insert(make_pair("eLotteryBeautyType_TenLoveHeart", eLotteryBeautyType_TenLoveHeart));
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

SBeauty::SBeauty() : qwRoleID(0), wBeautyID(0), wBeautyLevel(0), dwBeautyExp(0), wDayLoveType(0), 
			dwChatTime(0), dwPrizeExp(0), bFight(false) { }

SBeauty::SBeauty(UINT64 qwRoleID_, UINT16 wBeautyID_, UINT16 wBeautyLevel_, UINT32 dwBeautyExp_, UINT16 wDayLoveType_, 
			UINT32 dwChatTime_, UINT32 dwPrizeExp_, bool bFight_)
			: qwRoleID(qwRoleID_), wBeautyID(wBeautyID_), wBeautyLevel(wBeautyLevel_), dwBeautyExp(dwBeautyExp_), wDayLoveType(wDayLoveType_), 
			dwChatTime(dwChatTime_), dwPrizeExp(dwPrizeExp_), bFight(bFight_) { }

CInArchive& operator>>(CInArchive& src, SBeauty& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwRoleID;
	src >> s.wBeautyID;
	src >> s.wBeautyLevel;
	src >> s.dwBeautyExp;
	src >> s.wDayLoveType;
	src >> s.dwChatTime;
	src >> s.dwPrizeExp;
	src >> s.bFight;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SBeauty& s)
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
	src << s.wBeautyID;
	src << s.wBeautyLevel;
	src << s.dwBeautyExp;
	src << s.wDayLoveType;
	src << s.dwChatTime;
	src << s.dwPrizeExp;
	src << s.bFight;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SBeauty& s)
{
	if(strcmp(rElement.Value(), "SBeauty") != 0)
	{
		LOG_CRI << "rElement is not SBeauty!";
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
		LOG_CRI << "pElemChild for wBeautyLevel is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wBeautyLevel") != 0)
	{
		LOG_CRI << "Attribute: name is not wBeautyLevel!";
		return false;
	}
	const char* pszVal_wBeautyLevel = pElemChild->Attribute("value");
	if(pszVal_wBeautyLevel == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wBeautyLevel, s.wBeautyLevel))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwBeautyExp is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwBeautyExp") != 0)
	{
		LOG_CRI << "Attribute: name is not dwBeautyExp!";
		return false;
	}
	const char* pszVal_dwBeautyExp = pElemChild->Attribute("value");
	if(pszVal_dwBeautyExp == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwBeautyExp, s.dwBeautyExp))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wDayLoveType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wDayLoveType") != 0)
	{
		LOG_CRI << "Attribute: name is not wDayLoveType!";
		return false;
	}
	const char* pszVal_wDayLoveType = pElemChild->Attribute("value");
	if(pszVal_wDayLoveType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wDayLoveType, s.wDayLoveType))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwChatTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwChatTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwChatTime!";
		return false;
	}
	const char* pszVal_dwChatTime = pElemChild->Attribute("value");
	if(pszVal_dwChatTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwChatTime, s.dwChatTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwPrizeExp is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwPrizeExp") != 0)
	{
		LOG_CRI << "Attribute: name is not dwPrizeExp!";
		return false;
	}
	const char* pszVal_dwPrizeExp = pElemChild->Attribute("value");
	if(pszVal_dwPrizeExp == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwPrizeExp, s.dwPrizeExp))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for bFight is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "bool") != 0)
	{
		LOG_CRI << "pElemChild is not bool!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "bFight") != 0)
	{
		LOG_CRI << "Attribute: name is not bFight!";
		return false;
	}
	const char* pszVal_bFight = pElemChild->Attribute("value");
	if(pszVal_bFight == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_bFight, s.bFight))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SBeauty& s, TiXmlElement& rElement)
{
	rElement.SetValue("SBeauty");
	rElement.SetAttribute("type", ToUTF8Ptr("美女信息"));
	unique_ptr<TiXmlElement> pElem_qwRoleID(new TiXmlElement("UINT64"));
	if(pElem_qwRoleID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwRoleID->SetAttribute("name", "qwRoleID");
	pElem_qwRoleID->SetAttribute("value", NumberToString(s.qwRoleID).c_str());
	pElem_qwRoleID->SetAttribute("comment", ToUTF8Ptr("玩家id"));
	if(rElement.LinkEndChild(pElem_qwRoleID.get()) != NULL)
		pElem_qwRoleID.release();
	unique_ptr<TiXmlElement> pElem_wBeautyID(new TiXmlElement("UINT16"));
	if(pElem_wBeautyID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wBeautyID->SetAttribute("name", "wBeautyID");
	pElem_wBeautyID->SetAttribute("value", NumberToString(s.wBeautyID).c_str());
	pElem_wBeautyID->SetAttribute("comment", ToUTF8Ptr("美女id"));
	if(rElement.LinkEndChild(pElem_wBeautyID.get()) != NULL)
		pElem_wBeautyID.release();
	unique_ptr<TiXmlElement> pElem_wBeautyLevel(new TiXmlElement("UINT16"));
	if(pElem_wBeautyLevel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wBeautyLevel->SetAttribute("name", "wBeautyLevel");
	pElem_wBeautyLevel->SetAttribute("value", NumberToString(s.wBeautyLevel).c_str());
	pElem_wBeautyLevel->SetAttribute("comment", ToUTF8Ptr("亲密等级"));
	if(rElement.LinkEndChild(pElem_wBeautyLevel.get()) != NULL)
		pElem_wBeautyLevel.release();
	unique_ptr<TiXmlElement> pElem_dwBeautyExp(new TiXmlElement("UINT32"));
	if(pElem_dwBeautyExp == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwBeautyExp->SetAttribute("name", "dwBeautyExp");
	pElem_dwBeautyExp->SetAttribute("value", NumberToString(s.dwBeautyExp).c_str());
	pElem_dwBeautyExp->SetAttribute("comment", ToUTF8Ptr("亲密度"));
	if(rElement.LinkEndChild(pElem_dwBeautyExp.get()) != NULL)
		pElem_dwBeautyExp.release();
	unique_ptr<TiXmlElement> pElem_wDayLoveType(new TiXmlElement("UINT16"));
	if(pElem_wDayLoveType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wDayLoveType->SetAttribute("name", "wDayLoveType");
	pElem_wDayLoveType->SetAttribute("value", NumberToString(s.wDayLoveType).c_str());
	pElem_wDayLoveType->SetAttribute("comment", ToUTF8Ptr("当天喜欢物品类型"));
	if(rElement.LinkEndChild(pElem_wDayLoveType.get()) != NULL)
		pElem_wDayLoveType.release();
	unique_ptr<TiXmlElement> pElem_dwChatTime(new TiXmlElement("UINT32"));
	if(pElem_dwChatTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwChatTime->SetAttribute("name", "dwChatTime");
	pElem_dwChatTime->SetAttribute("value", NumberToString(s.dwChatTime).c_str());
	pElem_dwChatTime->SetAttribute("comment", ToUTF8Ptr("美女聊天cd(目前是共用cd次字段不用)"));
	if(rElement.LinkEndChild(pElem_dwChatTime.get()) != NULL)
		pElem_dwChatTime.release();
	unique_ptr<TiXmlElement> pElem_dwPrizeExp(new TiXmlElement("UINT32"));
	if(pElem_dwPrizeExp == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwPrizeExp->SetAttribute("name", "dwPrizeExp");
	pElem_dwPrizeExp->SetAttribute("value", NumberToString(s.dwPrizeExp).c_str());
	pElem_dwPrizeExp->SetAttribute("comment", ToUTF8Ptr("已获得爱心的亲密度"));
	if(rElement.LinkEndChild(pElem_dwPrizeExp.get()) != NULL)
		pElem_dwPrizeExp.release();
	unique_ptr<TiXmlElement> pElem_bFight(new TiXmlElement("bool"));
	if(pElem_bFight == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_bFight->SetAttribute("name", "bFight");
	pElem_bFight->SetAttribute("value", NumberToString(s.bFight).c_str());
	pElem_bFight->SetAttribute("comment", ToUTF8Ptr("是否出战"));
	if(rElement.LinkEndChild(pElem_bFight.get()) != NULL)
		pElem_bFight.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecBeauty& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SBeauty s;
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

bool VectorToXML(const TVecBeauty& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SBeauty"));
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

} //namespace NBeauty
