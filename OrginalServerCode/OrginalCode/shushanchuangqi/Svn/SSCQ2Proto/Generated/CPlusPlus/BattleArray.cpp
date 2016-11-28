/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    BattleArray.cpp
//  Purpose:      破阵
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "BattleArray.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NBattleArray
{

#ifdef PROT_USE_XML

const char* EnumValToStr(EBattleArrayStatus e)
{
	switch(e)
	{
	case eBattleArrayStatus_Init:
		return "eBattleArrayStatus_Init";
	case eBattleArrayStatus_End:
		return "eBattleArrayStatus_End";
	case eBattleArrayStatus_TakePrized:
		return "eBattleArrayStatus_TakePrized";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EBattleArrayStatus& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EBattleArrayStatus> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eBattleArrayStatus_Init", eBattleArrayStatus_Init));
		mapStr2Val.insert(make_pair("eBattleArrayStatus_End", eBattleArrayStatus_End));
		mapStr2Val.insert(make_pair("eBattleArrayStatus_TakePrized", eBattleArrayStatus_TakePrized));
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

const char* EnumValToStr(EBattleArrayRet e)
{
	switch(e)
	{
	case eBattleArrayRet_Sucess:
		return "eBattleArrayRet_Sucess";
	case eBattleArrayRet_LevelLimit:
		return "eBattleArrayRet_LevelLimit";
	case eBattleArrayRet_PreID:
		return "eBattleArrayRet_PreID";
	case eBattleArrayRet_PosLimit:
		return "eBattleArrayRet_PosLimit";
	case eBattleArrayRet_AttackLimit:
		return "eBattleArrayRet_AttackLimit";
	case eBattleArrayRet_TotalAttackLimit:
		return "eBattleArrayRet_TotalAttackLimit";
	case eBattleArrayRet_ErrorCFG:
		return "eBattleArrayRet_ErrorCFG";
	case eBattleArrayRet_PreLevel:
		return "eBattleArrayRet_PreLevel";
	case eBattleArrayRet_NoPass:
		return "eBattleArrayRet_NoPass";
	case eBattleArrayRet_TakePrized:
		return "eBattleArrayRet_TakePrized";
	case eBattleArrayRet_PackError:
		return "eBattleArrayRet_PackError";
	case eBattleArrayRet_MoneyError:
		return "eBattleArrayRet_MoneyError";
	case eBattleArrayRet_MaxBuyCnt:
		return "eBattleArrayRet_MaxBuyCnt";
	case eBattleArrayRet_AttackCd:
		return "eBattleArrayRet_AttackCd";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EBattleArrayRet& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EBattleArrayRet> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eBattleArrayRet_Sucess", eBattleArrayRet_Sucess));
		mapStr2Val.insert(make_pair("eBattleArrayRet_LevelLimit", eBattleArrayRet_LevelLimit));
		mapStr2Val.insert(make_pair("eBattleArrayRet_PreID", eBattleArrayRet_PreID));
		mapStr2Val.insert(make_pair("eBattleArrayRet_PosLimit", eBattleArrayRet_PosLimit));
		mapStr2Val.insert(make_pair("eBattleArrayRet_AttackLimit", eBattleArrayRet_AttackLimit));
		mapStr2Val.insert(make_pair("eBattleArrayRet_TotalAttackLimit", eBattleArrayRet_TotalAttackLimit));
		mapStr2Val.insert(make_pair("eBattleArrayRet_ErrorCFG", eBattleArrayRet_ErrorCFG));
		mapStr2Val.insert(make_pair("eBattleArrayRet_PreLevel", eBattleArrayRet_PreLevel));
		mapStr2Val.insert(make_pair("eBattleArrayRet_NoPass", eBattleArrayRet_NoPass));
		mapStr2Val.insert(make_pair("eBattleArrayRet_TakePrized", eBattleArrayRet_TakePrized));
		mapStr2Val.insert(make_pair("eBattleArrayRet_PackError", eBattleArrayRet_PackError));
		mapStr2Val.insert(make_pair("eBattleArrayRet_MoneyError", eBattleArrayRet_MoneyError));
		mapStr2Val.insert(make_pair("eBattleArrayRet_MaxBuyCnt", eBattleArrayRet_MaxBuyCnt));
		mapStr2Val.insert(make_pair("eBattleArrayRet_AttackCd", eBattleArrayRet_AttackCd));
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

const char* EnumValToStr(EBattleArrayGain e)
{
	switch(e)
	{
	case eBattleArrayGain_Attack:
		return "eBattleArrayGain_Attack";
	case eBattleArrayGain_Sweep:
		return "eBattleArrayGain_Sweep";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EBattleArrayGain& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EBattleArrayGain> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eBattleArrayGain_Attack", eBattleArrayGain_Attack));
		mapStr2Val.insert(make_pair("eBattleArrayGain_Sweep", eBattleArrayGain_Sweep));
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

SBattleArray::SBattleArray() : wBattleArrayID(0), dwBattleArrayLevelID(0), eBattleArrayStatus((EBattleArrayStatus)0) { }

SBattleArray::SBattleArray(UINT16 wBattleArrayID_, UINT32 dwBattleArrayLevelID_, EBattleArrayStatus eBattleArrayStatus_) : wBattleArrayID(wBattleArrayID_), dwBattleArrayLevelID(dwBattleArrayLevelID_), eBattleArrayStatus(eBattleArrayStatus_) { }

CInArchive& operator>>(CInArchive& src, SBattleArray& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.wBattleArrayID;
	src >> s.dwBattleArrayLevelID;
	src >> (UINT8&)s.eBattleArrayStatus;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SBattleArray& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.wBattleArrayID;
	src << s.dwBattleArrayLevelID;
	src << (UINT8&)s.eBattleArrayStatus;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SBattleArray& s)
{
	if(strcmp(rElement.Value(), "SBattleArray") != 0)
	{
		LOG_CRI << "rElement is not SBattleArray!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wBattleArrayID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wBattleArrayID") != 0)
	{
		LOG_CRI << "Attribute: name is not wBattleArrayID!";
		return false;
	}
	const char* pszVal_wBattleArrayID = pElemChild->Attribute("value");
	if(pszVal_wBattleArrayID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wBattleArrayID, s.wBattleArrayID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwBattleArrayLevelID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwBattleArrayLevelID") != 0)
	{
		LOG_CRI << "Attribute: name is not dwBattleArrayLevelID!";
		return false;
	}
	const char* pszVal_dwBattleArrayLevelID = pElemChild->Attribute("value");
	if(pszVal_dwBattleArrayLevelID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwBattleArrayLevelID, s.dwBattleArrayLevelID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eBattleArrayStatus is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "EBattleArrayStatus") != 0)
	{
		LOG_CRI << "pElemChild is not EBattleArrayStatus!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eBattleArrayStatus") != 0)
	{
		LOG_CRI << "Attribute: name is not eBattleArrayStatus!";
		return false;
	}
	const char* pszVal_eBattleArrayStatus = pElemChild->Attribute("value");
	if(pszVal_eBattleArrayStatus == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!EnumStrToVal(pszVal_eBattleArrayStatus, s.eBattleArrayStatus))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SBattleArray& s, TiXmlElement& rElement)
{
	rElement.SetValue("SBattleArray");
	rElement.SetAttribute("type", ToUTF8Ptr("阵信息"));
	unique_ptr<TiXmlElement> pElem_wBattleArrayID(new TiXmlElement("UINT16"));
	if(pElem_wBattleArrayID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wBattleArrayID->SetAttribute("name", "wBattleArrayID");
	pElem_wBattleArrayID->SetAttribute("value", NumberToString(s.wBattleArrayID).c_str());
	pElem_wBattleArrayID->SetAttribute("comment", ToUTF8Ptr("阵id"));
	if(rElement.LinkEndChild(pElem_wBattleArrayID.get()) != NULL)
		pElem_wBattleArrayID.release();
	unique_ptr<TiXmlElement> pElem_dwBattleArrayLevelID(new TiXmlElement("UINT32"));
	if(pElem_dwBattleArrayLevelID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwBattleArrayLevelID->SetAttribute("name", "dwBattleArrayLevelID");
	pElem_dwBattleArrayLevelID->SetAttribute("value", NumberToString(s.dwBattleArrayLevelID).c_str());
	pElem_dwBattleArrayLevelID->SetAttribute("comment", ToUTF8Ptr("破阵进度(阵图id)"));
	if(rElement.LinkEndChild(pElem_dwBattleArrayLevelID.get()) != NULL)
		pElem_dwBattleArrayLevelID.release();
	unique_ptr<TiXmlElement> pElem_eBattleArrayStatus(new TiXmlElement("EBattleArrayStatus"));
	if(pElem_eBattleArrayStatus == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eBattleArrayStatus->SetAttribute("name", "eBattleArrayStatus");
	const char* pszEnum_eBattleArrayStatus = EnumValToStr(s.eBattleArrayStatus);
	if(pszEnum_eBattleArrayStatus == NULL)
	{
		LOG_CRI << "EnumValToStr for EBattleArrayStatus fails!";
		return false;
	}
	pElem_eBattleArrayStatus->SetAttribute("value", pszEnum_eBattleArrayStatus);
	pElem_eBattleArrayStatus->SetAttribute("comment", ToUTF8Ptr("阵状态"));
	if(rElement.LinkEndChild(pElem_eBattleArrayStatus.get()) != NULL)
		pElem_eBattleArrayStatus.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecBattleArray& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SBattleArray s;
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

bool VectorToXML(const TVecBattleArray& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SBattleArray"));
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

SBattleArrayAttackCnt::SBattleArrayAttackCnt() : dwBattleArrayLevelID(0), wCount(0), wMinTurn(0) { }

SBattleArrayAttackCnt::SBattleArrayAttackCnt(UINT32 dwBattleArrayLevelID_, UINT16 wCount_, UINT16 wMinTurn_) : dwBattleArrayLevelID(dwBattleArrayLevelID_), wCount(wCount_), wMinTurn(wMinTurn_) { }

CInArchive& operator>>(CInArchive& src, SBattleArrayAttackCnt& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.dwBattleArrayLevelID;
	src >> s.wCount;
	src >> s.wMinTurn;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SBattleArrayAttackCnt& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.dwBattleArrayLevelID;
	src << s.wCount;
	src << s.wMinTurn;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SBattleArrayAttackCnt& s)
{
	if(strcmp(rElement.Value(), "SBattleArrayAttackCnt") != 0)
	{
		LOG_CRI << "rElement is not SBattleArrayAttackCnt!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwBattleArrayLevelID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwBattleArrayLevelID") != 0)
	{
		LOG_CRI << "Attribute: name is not dwBattleArrayLevelID!";
		return false;
	}
	const char* pszVal_dwBattleArrayLevelID = pElemChild->Attribute("value");
	if(pszVal_dwBattleArrayLevelID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwBattleArrayLevelID, s.dwBattleArrayLevelID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wCount is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wCount") != 0)
	{
		LOG_CRI << "Attribute: name is not wCount!";
		return false;
	}
	const char* pszVal_wCount = pElemChild->Attribute("value");
	if(pszVal_wCount == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wCount, s.wCount))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wMinTurn is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wMinTurn") != 0)
	{
		LOG_CRI << "Attribute: name is not wMinTurn!";
		return false;
	}
	const char* pszVal_wMinTurn = pElemChild->Attribute("value");
	if(pszVal_wMinTurn == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wMinTurn, s.wMinTurn))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SBattleArrayAttackCnt& s, TiXmlElement& rElement)
{
	rElement.SetValue("SBattleArrayAttackCnt");
	rElement.SetAttribute("type", ToUTF8Ptr("攻击阵图信息"));
	unique_ptr<TiXmlElement> pElem_dwBattleArrayLevelID(new TiXmlElement("UINT32"));
	if(pElem_dwBattleArrayLevelID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwBattleArrayLevelID->SetAttribute("name", "dwBattleArrayLevelID");
	pElem_dwBattleArrayLevelID->SetAttribute("value", NumberToString(s.dwBattleArrayLevelID).c_str());
	pElem_dwBattleArrayLevelID->SetAttribute("comment", ToUTF8Ptr("阵图id"));
	if(rElement.LinkEndChild(pElem_dwBattleArrayLevelID.get()) != NULL)
		pElem_dwBattleArrayLevelID.release();
	unique_ptr<TiXmlElement> pElem_wCount(new TiXmlElement("UINT16"));
	if(pElem_wCount == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wCount->SetAttribute("name", "wCount");
	pElem_wCount->SetAttribute("value", NumberToString(s.wCount).c_str());
	pElem_wCount->SetAttribute("comment", ToUTF8Ptr("次数"));
	if(rElement.LinkEndChild(pElem_wCount.get()) != NULL)
		pElem_wCount.release();
	unique_ptr<TiXmlElement> pElem_wMinTurn(new TiXmlElement("UINT16"));
	if(pElem_wMinTurn == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wMinTurn->SetAttribute("name", "wMinTurn");
	pElem_wMinTurn->SetAttribute("value", NumberToString(s.wMinTurn).c_str());
	pElem_wMinTurn->SetAttribute("comment", ToUTF8Ptr("最小回合数"));
	if(rElement.LinkEndChild(pElem_wMinTurn.get()) != NULL)
		pElem_wMinTurn.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecBattleArrayAttackCnt& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SBattleArrayAttackCnt s;
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

bool VectorToXML(const TVecBattleArrayAttackCnt& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SBattleArrayAttackCnt"));
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

} //namespace NBattleArray
