/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    MiscProt.cpp
//  Purpose:      不好归类的小协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "MiscProt.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NMiscProt
{

#ifdef PROT_USE_XML

const char* EnumValToStr(EBuyActionRet e)
{
	switch(e)
	{
	case eBuyActionRet_Sucess:
		return "eBuyActionRet_Sucess";
	case eBuyActionRet_MaxAction:
		return "eBuyActionRet_MaxAction";
	case eBuyActionRet_MoneyLimit:
		return "eBuyActionRet_MoneyLimit";
	case eBuyActionRet_CountLimit:
		return "eBuyActionRet_CountLimit";
	case eBuyActionRet_VIPCFGError:
		return "eBuyActionRet_VIPCFGError";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EBuyActionRet& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EBuyActionRet> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eBuyActionRet_Sucess", eBuyActionRet_Sucess));
		mapStr2Val.insert(make_pair("eBuyActionRet_MaxAction", eBuyActionRet_MaxAction));
		mapStr2Val.insert(make_pair("eBuyActionRet_MoneyLimit", eBuyActionRet_MoneyLimit));
		mapStr2Val.insert(make_pair("eBuyActionRet_CountLimit", eBuyActionRet_CountLimit));
		mapStr2Val.insert(make_pair("eBuyActionRet_VIPCFGError", eBuyActionRet_VIPCFGError));
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

const char* EnumValToStr(EMiscOptRes e)
{
	switch(e)
	{
	case eMiscOptRes_Sucess:
		return "eMiscOptRes_Sucess";
	case eMiscOptRes_Error:
		return "eMiscOptRes_Error";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EMiscOptRes& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EMiscOptRes> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eMiscOptRes_Sucess", eMiscOptRes_Sucess));
		mapStr2Val.insert(make_pair("eMiscOptRes_Error", eMiscOptRes_Error));
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

const char* EnumValToStr(ELotteryRes e)
{
	switch(e)
	{
	case eLotteryRes_Sucess:
		return "eLotteryRes_Sucess";
	case eLotteryRes_PackFul:
		return "eLotteryRes_PackFul";
	case eLotteryRes_LackMoney:
		return "eLotteryRes_LackMoney";
	case eLotteryRes_Error:
		return "eLotteryRes_Error";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, ELotteryRes& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, ELotteryRes> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eLotteryRes_Sucess", eLotteryRes_Sucess));
		mapStr2Val.insert(make_pair("eLotteryRes_PackFul", eLotteryRes_PackFul));
		mapStr2Val.insert(make_pair("eLotteryRes_LackMoney", eLotteryRes_LackMoney));
		mapStr2Val.insert(make_pair("eLotteryRes_Error", eLotteryRes_Error));
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

const char* EnumValToStr(EEveryDayReChargeAward e)
{
	switch(e)
	{
	case eEveryDayReChargeAward_Sucess:
		return "eEveryDayReChargeAward_Sucess";
	case eEveryDayReChargeAward_LowMoney:
		return "eEveryDayReChargeAward_LowMoney";
	case eEveryDayReChargeAward_HasDone:
		return "eEveryDayReChargeAward_HasDone";
	case eEveryDayReChargeAward_NoAward:
		return "eEveryDayReChargeAward_NoAward";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EEveryDayReChargeAward& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EEveryDayReChargeAward> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eEveryDayReChargeAward_Sucess", eEveryDayReChargeAward_Sucess));
		mapStr2Val.insert(make_pair("eEveryDayReChargeAward_LowMoney", eEveryDayReChargeAward_LowMoney));
		mapStr2Val.insert(make_pair("eEveryDayReChargeAward_HasDone", eEveryDayReChargeAward_HasDone));
		mapStr2Val.insert(make_pair("eEveryDayReChargeAward_NoAward", eEveryDayReChargeAward_NoAward));
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

SGodChestInfo::SGodChestInfo() : byState(0), byRount(0), dwTime(0), dwEnd(0) { }

SGodChestInfo::SGodChestInfo(UINT8 byState_, UINT8 byRount_, UINT32 dwTime_, UINT32 dwEnd_) : byState(byState_), byRount(byRount_), dwTime(dwTime_), dwEnd(dwEnd_) { }

CInArchive& operator>>(CInArchive& src, SGodChestInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.byState;
	src >> s.byRount;
	src >> s.dwTime;
	src >> s.dwEnd;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SGodChestInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.byState;
	src << s.byRount;
	src << s.dwTime;
	src << s.dwEnd;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SGodChestInfo& s)
{
	if(strcmp(rElement.Value(), "SGodChestInfo") != 0)
	{
		LOG_CRI << "rElement is not SGodChestInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byState is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byState") != 0)
	{
		LOG_CRI << "Attribute: name is not byState!";
		return false;
	}
	const char* pszVal_byState = pElemChild->Attribute("value");
	if(pszVal_byState == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byState, s.byState))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byRount is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byRount") != 0)
	{
		LOG_CRI << "Attribute: name is not byRount!";
		return false;
	}
	const char* pszVal_byRount = pElemChild->Attribute("value");
	if(pszVal_byRount == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byRount, s.byRount))
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
		LOG_CRI << "pElemChild for dwEnd is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwEnd") != 0)
	{
		LOG_CRI << "Attribute: name is not dwEnd!";
		return false;
	}
	const char* pszVal_dwEnd = pElemChild->Attribute("value");
	if(pszVal_dwEnd == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwEnd, s.dwEnd))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SGodChestInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SGodChestInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("刷宝箱信息"));
	unique_ptr<TiXmlElement> pElem_byState(new TiXmlElement("UINT8"));
	if(pElem_byState == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byState->SetAttribute("name", "byState");
	pElem_byState->SetAttribute("value", NumberToString(s.byState).c_str());
	pElem_byState->SetAttribute("comment", ToUTF8Ptr("状态"));
	if(rElement.LinkEndChild(pElem_byState.get()) != NULL)
		pElem_byState.release();
	unique_ptr<TiXmlElement> pElem_byRount(new TiXmlElement("UINT8"));
	if(pElem_byRount == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byRount->SetAttribute("name", "byRount");
	pElem_byRount->SetAttribute("value", NumberToString(s.byRount).c_str());
	pElem_byRount->SetAttribute("comment", ToUTF8Ptr("回合数"));
	if(rElement.LinkEndChild(pElem_byRount.get()) != NULL)
		pElem_byRount.release();
	unique_ptr<TiXmlElement> pElem_dwTime(new TiXmlElement("UINT32"));
	if(pElem_dwTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwTime->SetAttribute("name", "dwTime");
	pElem_dwTime->SetAttribute("value", NumberToString(s.dwTime).c_str());
	pElem_dwTime->SetAttribute("comment", ToUTF8Ptr("倒计时数"));
	if(rElement.LinkEndChild(pElem_dwTime.get()) != NULL)
		pElem_dwTime.release();
	unique_ptr<TiXmlElement> pElem_dwEnd(new TiXmlElement("UINT32"));
	if(pElem_dwEnd == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwEnd->SetAttribute("name", "dwEnd");
	pElem_dwEnd->SetAttribute("value", NumberToString(s.dwEnd).c_str());
	pElem_dwEnd->SetAttribute("comment", ToUTF8Ptr("活动结束时间"));
	if(rElement.LinkEndChild(pElem_dwEnd.get()) != NULL)
		pElem_dwEnd.release();
	return true;
}

#endif

SLotteryInfo::SLotteryInfo() : dwLotteryID(0) { }

SLotteryInfo::SLotteryInfo(const std::string& strName_, UINT32 dwLotteryID_) : strName(strName_), dwLotteryID(dwLotteryID_) { }

SLotteryInfo::SLotteryInfo(SLotteryInfo&& src) : strName(move(src.strName)), dwLotteryID(src.dwLotteryID) { }

SLotteryInfo& SLotteryInfo::operator=(SLotteryInfo&& rhs)
{
	if(this != &rhs)
	{
		this->~SLotteryInfo();
		new (this) SLotteryInfo(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SLotteryInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.strName;
	src >> s.dwLotteryID;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SLotteryInfo& s)
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
	src << s.dwLotteryID;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SLotteryInfo& s)
{
	if(strcmp(rElement.Value(), "SLotteryInfo") != 0)
	{
		LOG_CRI << "rElement is not SLotteryInfo!";
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
		LOG_CRI << "pElemChild for dwLotteryID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwLotteryID") != 0)
	{
		LOG_CRI << "Attribute: name is not dwLotteryID!";
		return false;
	}
	const char* pszVal_dwLotteryID = pElemChild->Attribute("value");
	if(pszVal_dwLotteryID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwLotteryID, s.dwLotteryID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SLotteryInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SLotteryInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("抽奖信息"));
	unique_ptr<TiXmlElement> pElem_strName(new TiXmlElement("string"));
	if(pElem_strName == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strName->SetAttribute("name", "strName");
	pElem_strName->SetAttribute("value", s.strName.c_str());
	pElem_strName->SetAttribute("comment", ToUTF8Ptr("玩家"));
	if(rElement.LinkEndChild(pElem_strName.get()) != NULL)
		pElem_strName.release();
	unique_ptr<TiXmlElement> pElem_dwLotteryID(new TiXmlElement("UINT32"));
	if(pElem_dwLotteryID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwLotteryID->SetAttribute("name", "dwLotteryID");
	pElem_dwLotteryID->SetAttribute("value", NumberToString(s.dwLotteryID).c_str());
	pElem_dwLotteryID->SetAttribute("comment", ToUTF8Ptr("奖励ID(对应配置表)"));
	if(rElement.LinkEndChild(pElem_dwLotteryID.get()) != NULL)
		pElem_dwLotteryID.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecLotteryInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SLotteryInfo s;
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

bool VectorToXML(const TVecLotteryInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SLotteryInfo"));
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

} //namespace NMiscProt
