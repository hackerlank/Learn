/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    MallProt.cpp
//  Purpose:      商城相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "MallProt.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NMallProt
{

#ifdef PROT_USE_XML

const char* EnumValToStr(EMallType e)
{
	switch(e)
	{
	case eMallGold:
		return "eMallGold";
	case eMallFashion:
		return "eMallFashion";
	case eMallVIP:
		return "eMallVIP";
	case eMallPrestige:
		return "eMallPrestige";
	case eMallHonor:
		return "eMallHonor";
	case eMallCoupon:
		return "eMallCoupon";
	case eMallSilver:
		return "eMallSilver";
	case eMallLimit:
		return "eMallLimit";
	case eMallGem:
		return "eMallGem";
	case eMallEnd:
		return "eMallEnd";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EMallType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EMallType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eMallGold", eMallGold));
		mapStr2Val.insert(make_pair("eMallFashion", eMallFashion));
		mapStr2Val.insert(make_pair("eMallVIP", eMallVIP));
		mapStr2Val.insert(make_pair("eMallPrestige", eMallPrestige));
		mapStr2Val.insert(make_pair("eMallHonor", eMallHonor));
		mapStr2Val.insert(make_pair("eMallCoupon", eMallCoupon));
		mapStr2Val.insert(make_pair("eMallSilver", eMallSilver));
		mapStr2Val.insert(make_pair("eMallLimit", eMallLimit));
		mapStr2Val.insert(make_pair("eMallGem", eMallGem));
		mapStr2Val.insert(make_pair("eMallEnd", eMallEnd));
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

const char* EnumValToStr(EMallResult e)
{
	switch(e)
	{
	case eMallResultSucc:
		return "eMallResultSucc";
	case eMallResultFailed:
		return "eMallResultFailed";
	case eMallResultStore:
		return "eMallResultStore";
	case eMallResultStoreAdd:
		return "eMallResultStoreAdd";
	case eMallResultMoney:
		return "eMallResultMoney";
	case eMallResultNoItem:
		return "eMallResultNoItem";
	case eMallResultFashionErr:
		return "eMallResultFashionErr";
	case eMallResultFashionAlready:
		return "eMallResultFashionAlready";
	case eMallPresentSucc:
		return "eMallPresentSucc";
	case eMallPresentNoTarget:
		return "eMallPresentNoTarget";
	case eMallResultDiscountOverTime:
		return "eMallResultDiscountOverTime";
	case eMallResultDiscountFull:
		return "eMallResultDiscountFull";
	case eMallResultDiscountRechargeErr:
		return "eMallResultDiscountRechargeErr";
	case eMallResultDiscountConsumeErr:
		return "eMallResultDiscountConsumeErr";
	case eMallResultItemCount:
		return "eMallResultItemCount";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EMallResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EMallResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eMallResultSucc", eMallResultSucc));
		mapStr2Val.insert(make_pair("eMallResultFailed", eMallResultFailed));
		mapStr2Val.insert(make_pair("eMallResultStore", eMallResultStore));
		mapStr2Val.insert(make_pair("eMallResultStoreAdd", eMallResultStoreAdd));
		mapStr2Val.insert(make_pair("eMallResultMoney", eMallResultMoney));
		mapStr2Val.insert(make_pair("eMallResultNoItem", eMallResultNoItem));
		mapStr2Val.insert(make_pair("eMallResultFashionErr", eMallResultFashionErr));
		mapStr2Val.insert(make_pair("eMallResultFashionAlready", eMallResultFashionAlready));
		mapStr2Val.insert(make_pair("eMallPresentSucc", eMallPresentSucc));
		mapStr2Val.insert(make_pair("eMallPresentNoTarget", eMallPresentNoTarget));
		mapStr2Val.insert(make_pair("eMallResultDiscountOverTime", eMallResultDiscountOverTime));
		mapStr2Val.insert(make_pair("eMallResultDiscountFull", eMallResultDiscountFull));
		mapStr2Val.insert(make_pair("eMallResultDiscountRechargeErr", eMallResultDiscountRechargeErr));
		mapStr2Val.insert(make_pair("eMallResultDiscountConsumeErr", eMallResultDiscountConsumeErr));
		mapStr2Val.insert(make_pair("eMallResultItemCount", eMallResultItemCount));
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

const char* EnumValToStr(EUseMoneyMark e)
{
	switch(e)
	{
	case eUseBindMoney:
		return "eUseBindMoney";
	case eUseNoBindMoney:
		return "eUseNoBindMoney";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EUseMoneyMark& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EUseMoneyMark> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eUseBindMoney", eUseBindMoney));
		mapStr2Val.insert(make_pair("eUseNoBindMoney", eUseNoBindMoney));
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

const char* EnumValToStr(EDiscountLimitType e)
{
	switch(e)
	{
	case eDiscountLimitTypeNO:
		return "eDiscountLimitTypeNO";
	case eDiscountLimitTypeRecharge:
		return "eDiscountLimitTypeRecharge";
	case eDiscountLimitTypeConsume:
		return "eDiscountLimitTypeConsume";
	case eDiscountLimitTypeEnd:
		return "eDiscountLimitTypeEnd";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EDiscountLimitType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EDiscountLimitType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eDiscountLimitTypeNO", eDiscountLimitTypeNO));
		mapStr2Val.insert(make_pair("eDiscountLimitTypeRecharge", eDiscountLimitTypeRecharge));
		mapStr2Val.insert(make_pair("eDiscountLimitTypeConsume", eDiscountLimitTypeConsume));
		mapStr2Val.insert(make_pair("eDiscountLimitTypeEnd", eDiscountLimitTypeEnd));
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

SMallInfo::SMallInfo() : dwInstID(0), wItemID(0), dwItemCount(0), eMoneyType((NProtoCommon::EMoneyType)0), dwPrice(0), 
			byVIP(0), wIcon(0), dwDayCntLimit(0) { }

SMallInfo::SMallInfo(UINT32 dwInstID_, const std::string& strName_, UINT16 wItemID_, UINT32 dwItemCount_, NProtoCommon::EMoneyType eMoneyType_, 
			UINT32 dwPrice_, UINT8 byVIP_, UINT16 wIcon_, UINT32 dwDayCntLimit_)
			: dwInstID(dwInstID_), strName(strName_), wItemID(wItemID_), dwItemCount(dwItemCount_), eMoneyType(eMoneyType_), 
			dwPrice(dwPrice_), byVIP(byVIP_), wIcon(wIcon_), dwDayCntLimit(dwDayCntLimit_) { }

SMallInfo::SMallInfo(SMallInfo&& src) : dwInstID(src.dwInstID), strName(move(src.strName)), wItemID(src.wItemID), dwItemCount(src.dwItemCount), eMoneyType(src.eMoneyType), 
			dwPrice(src.dwPrice), byVIP(src.byVIP), wIcon(src.wIcon), dwDayCntLimit(src.dwDayCntLimit) { }

SMallInfo& SMallInfo::operator=(SMallInfo&& rhs)
{
	if(this != &rhs)
	{
		this->~SMallInfo();
		new (this) SMallInfo(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SMallInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.dwInstID;
	src >> s.strName;
	src >> s.wItemID;
	src >> s.dwItemCount;
	src >> (UINT8&)s.eMoneyType;
	src >> s.dwPrice;
	src >> s.byVIP;
	src >> s.wIcon;
	src >> s.dwDayCntLimit;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SMallInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.dwInstID;
	src << s.strName;
	src << s.wItemID;
	src << s.dwItemCount;
	src << (UINT8&)s.eMoneyType;
	src << s.dwPrice;
	src << s.byVIP;
	src << s.wIcon;
	src << s.dwDayCntLimit;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SMallInfo& s)
{
	if(strcmp(rElement.Value(), "SMallInfo") != 0)
	{
		LOG_CRI << "rElement is not SMallInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwInstID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwInstID") != 0)
	{
		LOG_CRI << "Attribute: name is not dwInstID!";
		return false;
	}
	const char* pszVal_dwInstID = pElemChild->Attribute("value");
	if(pszVal_dwInstID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwInstID, s.dwInstID))
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
		LOG_CRI << "pElemChild for dwItemCount is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwItemCount") != 0)
	{
		LOG_CRI << "Attribute: name is not dwItemCount!";
		return false;
	}
	const char* pszVal_dwItemCount = pElemChild->Attribute("value");
	if(pszVal_dwItemCount == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwItemCount, s.dwItemCount))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eMoneyType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "ProtoCommon::EMoneyType") != 0)
	{
		LOG_CRI << "pElemChild is not ProtoCommon::EMoneyType!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eMoneyType") != 0)
	{
		LOG_CRI << "Attribute: name is not eMoneyType!";
		return false;
	}
	const char* pszVal_eMoneyType = pElemChild->Attribute("value");
	if(pszVal_eMoneyType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!NProtoCommon::EnumStrToVal(pszVal_eMoneyType, s.eMoneyType))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwPrice is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwPrice") != 0)
	{
		LOG_CRI << "Attribute: name is not dwPrice!";
		return false;
	}
	const char* pszVal_dwPrice = pElemChild->Attribute("value");
	if(pszVal_dwPrice == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwPrice, s.dwPrice))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byVIP is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byVIP") != 0)
	{
		LOG_CRI << "Attribute: name is not byVIP!";
		return false;
	}
	const char* pszVal_byVIP = pElemChild->Attribute("value");
	if(pszVal_byVIP == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byVIP, s.byVIP))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wIcon is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wIcon") != 0)
	{
		LOG_CRI << "Attribute: name is not wIcon!";
		return false;
	}
	const char* pszVal_wIcon = pElemChild->Attribute("value");
	if(pszVal_wIcon == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wIcon, s.wIcon))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwDayCntLimit is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwDayCntLimit") != 0)
	{
		LOG_CRI << "Attribute: name is not dwDayCntLimit!";
		return false;
	}
	const char* pszVal_dwDayCntLimit = pElemChild->Attribute("value");
	if(pszVal_dwDayCntLimit == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwDayCntLimit, s.dwDayCntLimit))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SMallInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SMallInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("商城信息"));
	unique_ptr<TiXmlElement> pElem_dwInstID(new TiXmlElement("UINT32"));
	if(pElem_dwInstID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwInstID->SetAttribute("name", "dwInstID");
	pElem_dwInstID->SetAttribute("value", NumberToString(s.dwInstID).c_str());
	pElem_dwInstID->SetAttribute("comment", ToUTF8Ptr("商品编号"));
	if(rElement.LinkEndChild(pElem_dwInstID.get()) != NULL)
		pElem_dwInstID.release();
	unique_ptr<TiXmlElement> pElem_strName(new TiXmlElement("string"));
	if(pElem_strName == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strName->SetAttribute("name", "strName");
	pElem_strName->SetAttribute("value", s.strName.c_str());
	pElem_strName->SetAttribute("comment", ToUTF8Ptr("商品名称"));
	if(rElement.LinkEndChild(pElem_strName.get()) != NULL)
		pElem_strName.release();
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
	unique_ptr<TiXmlElement> pElem_dwItemCount(new TiXmlElement("UINT32"));
	if(pElem_dwItemCount == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwItemCount->SetAttribute("name", "dwItemCount");
	pElem_dwItemCount->SetAttribute("value", NumberToString(s.dwItemCount).c_str());
	pElem_dwItemCount->SetAttribute("comment", ToUTF8Ptr("物品数量"));
	if(rElement.LinkEndChild(pElem_dwItemCount.get()) != NULL)
		pElem_dwItemCount.release();
	unique_ptr<TiXmlElement> pElem_eMoneyType(new TiXmlElement("ProtoCommon::EMoneyType"));
	if(pElem_eMoneyType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eMoneyType->SetAttribute("name", "eMoneyType");
	const char* pszEnum_eMoneyType = NProtoCommon::EnumValToStr(s.eMoneyType);
	if(pszEnum_eMoneyType == NULL)
	{
		LOG_CRI << "EnumValToStr for eMoneyType fails!";
		return false;
	}
	pElem_eMoneyType->SetAttribute("value", pszEnum_eMoneyType);
	pElem_eMoneyType->SetAttribute("comment", ToUTF8Ptr("所需货币类型"));
	if(rElement.LinkEndChild(pElem_eMoneyType.get()) != NULL)
		pElem_eMoneyType.release();
	unique_ptr<TiXmlElement> pElem_dwPrice(new TiXmlElement("UINT32"));
	if(pElem_dwPrice == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwPrice->SetAttribute("name", "dwPrice");
	pElem_dwPrice->SetAttribute("value", NumberToString(s.dwPrice).c_str());
	pElem_dwPrice->SetAttribute("comment", ToUTF8Ptr("价格"));
	if(rElement.LinkEndChild(pElem_dwPrice.get()) != NULL)
		pElem_dwPrice.release();
	unique_ptr<TiXmlElement> pElem_byVIP(new TiXmlElement("UINT8"));
	if(pElem_byVIP == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byVIP->SetAttribute("name", "byVIP");
	pElem_byVIP->SetAttribute("value", NumberToString(s.byVIP).c_str());
	pElem_byVIP->SetAttribute("comment", ToUTF8Ptr("VIP等级限制"));
	if(rElement.LinkEndChild(pElem_byVIP.get()) != NULL)
		pElem_byVIP.release();
	unique_ptr<TiXmlElement> pElem_wIcon(new TiXmlElement("UINT16"));
	if(pElem_wIcon == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wIcon->SetAttribute("name", "wIcon");
	pElem_wIcon->SetAttribute("value", NumberToString(s.wIcon).c_str());
	pElem_wIcon->SetAttribute("comment", ToUTF8Ptr("图标"));
	if(rElement.LinkEndChild(pElem_wIcon.get()) != NULL)
		pElem_wIcon.release();
	unique_ptr<TiXmlElement> pElem_dwDayCntLimit(new TiXmlElement("UINT32"));
	if(pElem_dwDayCntLimit == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwDayCntLimit->SetAttribute("name", "dwDayCntLimit");
	pElem_dwDayCntLimit->SetAttribute("value", NumberToString(s.dwDayCntLimit).c_str());
	pElem_dwDayCntLimit->SetAttribute("comment", ToUTF8Ptr("限购数量"));
	if(rElement.LinkEndChild(pElem_dwDayCntLimit.get()) != NULL)
		pElem_dwDayCntLimit.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecMallInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SMallInfo s;
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

bool VectorToXML(const TVecMallInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SMallInfo"));
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

SDiscountItem::SDiscountItem() : wItemID(0), wOriginalPrice(0), wDiscountPrice(0) { }

SDiscountItem::SDiscountItem(UINT16 wItemID_, UINT16 wOriginalPrice_, UINT16 wDiscountPrice_) : wItemID(wItemID_), wOriginalPrice(wOriginalPrice_), wDiscountPrice(wDiscountPrice_) { }

CInArchive& operator>>(CInArchive& src, SDiscountItem& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.wItemID;
	src >> s.wOriginalPrice;
	src >> s.wDiscountPrice;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SDiscountItem& s)
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
	src << s.wOriginalPrice;
	src << s.wDiscountPrice;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SDiscountItem& s)
{
	if(strcmp(rElement.Value(), "SDiscountItem") != 0)
	{
		LOG_CRI << "rElement is not SDiscountItem!";
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
		LOG_CRI << "pElemChild for wOriginalPrice is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wOriginalPrice") != 0)
	{
		LOG_CRI << "Attribute: name is not wOriginalPrice!";
		return false;
	}
	const char* pszVal_wOriginalPrice = pElemChild->Attribute("value");
	if(pszVal_wOriginalPrice == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wOriginalPrice, s.wOriginalPrice))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wDiscountPrice is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wDiscountPrice") != 0)
	{
		LOG_CRI << "Attribute: name is not wDiscountPrice!";
		return false;
	}
	const char* pszVal_wDiscountPrice = pElemChild->Attribute("value");
	if(pszVal_wDiscountPrice == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wDiscountPrice, s.wDiscountPrice))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SDiscountItem& s, TiXmlElement& rElement)
{
	rElement.SetValue("SDiscountItem");
	rElement.SetAttribute("type", ToUTF8Ptr("商城折扣物品"));
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
	unique_ptr<TiXmlElement> pElem_wOriginalPrice(new TiXmlElement("UINT16"));
	if(pElem_wOriginalPrice == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wOriginalPrice->SetAttribute("name", "wOriginalPrice");
	pElem_wOriginalPrice->SetAttribute("value", NumberToString(s.wOriginalPrice).c_str());
	pElem_wOriginalPrice->SetAttribute("comment", ToUTF8Ptr("原价"));
	if(rElement.LinkEndChild(pElem_wOriginalPrice.get()) != NULL)
		pElem_wOriginalPrice.release();
	unique_ptr<TiXmlElement> pElem_wDiscountPrice(new TiXmlElement("UINT16"));
	if(pElem_wDiscountPrice == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wDiscountPrice->SetAttribute("name", "wDiscountPrice");
	pElem_wDiscountPrice->SetAttribute("value", NumberToString(s.wDiscountPrice).c_str());
	pElem_wDiscountPrice->SetAttribute("comment", ToUTF8Ptr("折扣价"));
	if(rElement.LinkEndChild(pElem_wDiscountPrice.get()) != NULL)
		pElem_wDiscountPrice.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecDiscountItem& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SDiscountItem s;
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

bool VectorToXML(const TVecDiscountItem& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SDiscountItem"));
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

SDiscount::SDiscount() : byPos(0), qwMarkID(0), byLimitType(0), dwLimitValue(0), wLimitCount(0), 
			dwBeginTime(0), dwEndTime(0) { }

SDiscount::SDiscount(UINT8 byPos_, UINT64 qwMarkID_, const TVecDiscountItem& vecDisItems_, UINT8 byLimitType_, UINT32 dwLimitValue_, 
			UINT16 wLimitCount_, UINT32 dwBeginTime_, UINT32 dwEndTime_)
			: byPos(byPos_), qwMarkID(qwMarkID_), vecDisItems(vecDisItems_), byLimitType(byLimitType_), dwLimitValue(dwLimitValue_), 
			wLimitCount(wLimitCount_), dwBeginTime(dwBeginTime_), dwEndTime(dwEndTime_) { }

SDiscount::SDiscount(SDiscount&& src) : byPos(src.byPos), qwMarkID(src.qwMarkID), vecDisItems(move(src.vecDisItems)), byLimitType(src.byLimitType), dwLimitValue(src.dwLimitValue), 
			wLimitCount(src.wLimitCount), dwBeginTime(src.dwBeginTime), dwEndTime(src.dwEndTime) { }

SDiscount& SDiscount::operator=(SDiscount&& rhs)
{
	if(this != &rhs)
	{
		this->~SDiscount();
		new (this) SDiscount(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SDiscount& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.byPos;
	src >> s.qwMarkID;
	src >> s.vecDisItems;
	src >> s.byLimitType;
	src >> s.dwLimitValue;
	src >> s.wLimitCount;
	src >> s.dwBeginTime;
	src >> s.dwEndTime;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SDiscount& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.byPos;
	src << s.qwMarkID;
	src << s.vecDisItems;
	src << s.byLimitType;
	src << s.dwLimitValue;
	src << s.wLimitCount;
	src << s.dwBeginTime;
	src << s.dwEndTime;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SDiscount& s)
{
	if(strcmp(rElement.Value(), "SDiscount") != 0)
	{
		LOG_CRI << "rElement is not SDiscount!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
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
		LOG_CRI << "pElemChild for qwMarkID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwMarkID") != 0)
	{
		LOG_CRI << "Attribute: name is not qwMarkID!";
		return false;
	}
	const char* pszVal_qwMarkID = pElemChild->Attribute("value");
	if(pszVal_qwMarkID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwMarkID, s.qwMarkID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecDisItems is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecDiscountItem") != 0)
	{
		LOG_CRI << "pElemChild is not TVecDiscountItem!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecDisItems") != 0)
	{
		LOG_CRI << "Attribute: name is not vecDisItems!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecDisItems))
	{
		LOG_CRI << "VectorFromXML for vecDisItems fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byLimitType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byLimitType") != 0)
	{
		LOG_CRI << "Attribute: name is not byLimitType!";
		return false;
	}
	const char* pszVal_byLimitType = pElemChild->Attribute("value");
	if(pszVal_byLimitType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byLimitType, s.byLimitType))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwLimitValue is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwLimitValue") != 0)
	{
		LOG_CRI << "Attribute: name is not dwLimitValue!";
		return false;
	}
	const char* pszVal_dwLimitValue = pElemChild->Attribute("value");
	if(pszVal_dwLimitValue == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwLimitValue, s.dwLimitValue))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wLimitCount is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wLimitCount") != 0)
	{
		LOG_CRI << "Attribute: name is not wLimitCount!";
		return false;
	}
	const char* pszVal_wLimitCount = pElemChild->Attribute("value");
	if(pszVal_wLimitCount == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wLimitCount, s.wLimitCount))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwBeginTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwBeginTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwBeginTime!";
		return false;
	}
	const char* pszVal_dwBeginTime = pElemChild->Attribute("value");
	if(pszVal_dwBeginTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwBeginTime, s.dwBeginTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwEndTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwEndTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwEndTime!";
		return false;
	}
	const char* pszVal_dwEndTime = pElemChild->Attribute("value");
	if(pszVal_dwEndTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwEndTime, s.dwEndTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SDiscount& s, TiXmlElement& rElement)
{
	rElement.SetValue("SDiscount");
	rElement.SetAttribute("type", ToUTF8Ptr("商城折扣物品信息"));
	unique_ptr<TiXmlElement> pElem_byPos(new TiXmlElement("UINT8"));
	if(pElem_byPos == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byPos->SetAttribute("name", "byPos");
	pElem_byPos->SetAttribute("value", NumberToString(s.byPos).c_str());
	pElem_byPos->SetAttribute("comment", ToUTF8Ptr("限购位置(0,1,2表示)"));
	if(rElement.LinkEndChild(pElem_byPos.get()) != NULL)
		pElem_byPos.release();
	unique_ptr<TiXmlElement> pElem_qwMarkID(new TiXmlElement("UINT64"));
	if(pElem_qwMarkID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwMarkID->SetAttribute("name", "qwMarkID");
	pElem_qwMarkID->SetAttribute("value", NumberToString(s.qwMarkID).c_str());
	pElem_qwMarkID->SetAttribute("comment", ToUTF8Ptr("栏位版本ID"));
	if(rElement.LinkEndChild(pElem_qwMarkID.get()) != NULL)
		pElem_qwMarkID.release();
	unique_ptr<TiXmlElement> pElem_vecDisItems(new TiXmlElement("TVecDiscountItem"));
	if(pElem_vecDisItems == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecDisItems->SetAttribute("name", "vecDisItems");
	if(!VectorToXML(s.vecDisItems, *pElem_vecDisItems))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecDisItems->SetAttribute("comment", ToUTF8Ptr("限购道具"));
	if(rElement.LinkEndChild(pElem_vecDisItems.get()) != NULL)
		pElem_vecDisItems.release();
	unique_ptr<TiXmlElement> pElem_byLimitType(new TiXmlElement("UINT8"));
	if(pElem_byLimitType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byLimitType->SetAttribute("name", "byLimitType");
	pElem_byLimitType->SetAttribute("value", NumberToString(s.byLimitType).c_str());
	pElem_byLimitType->SetAttribute("comment", ToUTF8Ptr("类型限制(0无条件、1充值限购、2消费限购)"));
	if(rElement.LinkEndChild(pElem_byLimitType.get()) != NULL)
		pElem_byLimitType.release();
	unique_ptr<TiXmlElement> pElem_dwLimitValue(new TiXmlElement("UINT32"));
	if(pElem_dwLimitValue == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwLimitValue->SetAttribute("name", "dwLimitValue");
	pElem_dwLimitValue->SetAttribute("value", NumberToString(s.dwLimitValue).c_str());
	pElem_dwLimitValue->SetAttribute("comment", ToUTF8Ptr("达到的仙石数量限制(0无条件、1充值限购、2消费限购)"));
	if(rElement.LinkEndChild(pElem_dwLimitValue.get()) != NULL)
		pElem_dwLimitValue.release();
	unique_ptr<TiXmlElement> pElem_wLimitCount(new TiXmlElement("UINT16"));
	if(pElem_wLimitCount == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wLimitCount->SetAttribute("name", "wLimitCount");
	pElem_wLimitCount->SetAttribute("value", NumberToString(s.wLimitCount).c_str());
	pElem_wLimitCount->SetAttribute("comment", ToUTF8Ptr("购买道具个数限制"));
	if(rElement.LinkEndChild(pElem_wLimitCount.get()) != NULL)
		pElem_wLimitCount.release();
	unique_ptr<TiXmlElement> pElem_dwBeginTime(new TiXmlElement("UINT32"));
	if(pElem_dwBeginTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwBeginTime->SetAttribute("name", "dwBeginTime");
	pElem_dwBeginTime->SetAttribute("value", NumberToString(s.dwBeginTime).c_str());
	pElem_dwBeginTime->SetAttribute("comment", ToUTF8Ptr("限购开始时间"));
	if(rElement.LinkEndChild(pElem_dwBeginTime.get()) != NULL)
		pElem_dwBeginTime.release();
	unique_ptr<TiXmlElement> pElem_dwEndTime(new TiXmlElement("UINT32"));
	if(pElem_dwEndTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwEndTime->SetAttribute("name", "dwEndTime");
	pElem_dwEndTime->SetAttribute("value", NumberToString(s.dwEndTime).c_str());
	pElem_dwEndTime->SetAttribute("comment", ToUTF8Ptr("限购结束时间"));
	if(rElement.LinkEndChild(pElem_dwEndTime.get()) != NULL)
		pElem_dwEndTime.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecDiscount& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SDiscount s;
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

bool VectorToXML(const TVecDiscount& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SDiscount"));
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

SBuyItemInfo::SBuyItemInfo() : dwInstID(0), dwCount(0) { }

SBuyItemInfo::SBuyItemInfo(UINT32 dwInstID_, UINT32 dwCount_) : dwInstID(dwInstID_), dwCount(dwCount_) { }

CInArchive& operator>>(CInArchive& src, SBuyItemInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.dwInstID;
	src >> s.dwCount;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SBuyItemInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.dwInstID;
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

bool FromXML(TiXmlElement& rElement, SBuyItemInfo& s)
{
	if(strcmp(rElement.Value(), "SBuyItemInfo") != 0)
	{
		LOG_CRI << "rElement is not SBuyItemInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwInstID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwInstID") != 0)
	{
		LOG_CRI << "Attribute: name is not dwInstID!";
		return false;
	}
	const char* pszVal_dwInstID = pElemChild->Attribute("value");
	if(pszVal_dwInstID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwInstID, s.dwInstID))
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

bool ToXML(const SBuyItemInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SBuyItemInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("物品购买信息"));
	unique_ptr<TiXmlElement> pElem_dwInstID(new TiXmlElement("UINT32"));
	if(pElem_dwInstID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwInstID->SetAttribute("name", "dwInstID");
	pElem_dwInstID->SetAttribute("value", NumberToString(s.dwInstID).c_str());
	pElem_dwInstID->SetAttribute("comment", ToUTF8Ptr("实例ID"));
	if(rElement.LinkEndChild(pElem_dwInstID.get()) != NULL)
		pElem_dwInstID.release();
	unique_ptr<TiXmlElement> pElem_dwCount(new TiXmlElement("UINT32"));
	if(pElem_dwCount == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwCount->SetAttribute("name", "dwCount");
	pElem_dwCount->SetAttribute("value", NumberToString(s.dwCount).c_str());
	pElem_dwCount->SetAttribute("comment", ToUTF8Ptr("物品数量"));
	if(rElement.LinkEndChild(pElem_dwCount.get()) != NULL)
		pElem_dwCount.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecBuyItemInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SBuyItemInfo s;
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

bool VectorToXML(const TVecBuyItemInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SBuyItemInfo"));
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

} //namespace NMallProt
