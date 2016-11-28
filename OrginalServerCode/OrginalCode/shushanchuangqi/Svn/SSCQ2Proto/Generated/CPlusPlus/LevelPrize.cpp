/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    LevelPrize.cpp
//  Purpose:      等级奖励
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "LevelPrize.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NLevelPrize
{

#ifdef PROT_USE_XML

const char* EnumValToStr(ELevelActStatus e)
{
	switch(e)
	{
	case eLevleActStatus_Init:
		return "eLevleActStatus_Init";
	case eLevleActStatus_Finish:
		return "eLevleActStatus_Finish";
	case eLevleActStatus_GetPrize:
		return "eLevleActStatus_GetPrize";
	case eLevleActStatus_FullPack:
		return "eLevleActStatus_FullPack";
	case eLevleActStatus_Success:
		return "eLevleActStatus_Success";
	case eLevleActStatus_Error:
		return "eLevleActStatus_Error";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, ELevelActStatus& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, ELevelActStatus> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eLevleActStatus_Init", eLevleActStatus_Init));
		mapStr2Val.insert(make_pair("eLevleActStatus_Finish", eLevleActStatus_Finish));
		mapStr2Val.insert(make_pair("eLevleActStatus_GetPrize", eLevleActStatus_GetPrize));
		mapStr2Val.insert(make_pair("eLevleActStatus_FullPack", eLevleActStatus_FullPack));
		mapStr2Val.insert(make_pair("eLevleActStatus_Success", eLevleActStatus_Success));
		mapStr2Val.insert(make_pair("eLevleActStatus_Error", eLevleActStatus_Error));
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

const char* EnumValToStr(EActState e)
{
	switch(e)
	{
	case eActState_Init:
		return "eActState_Init";
	case eActState_OnAdvance:
		return "eActState_OnAdvance";
	case eActState_OnBegin:
		return "eActState_OnBegin";
	case eActState_OnEnd:
		return "eActState_OnEnd";
	case eActState_OnRetain:
		return "eActState_OnRetain";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EActState& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EActState> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eActState_Init", eActState_Init));
		mapStr2Val.insert(make_pair("eActState_OnAdvance", eActState_OnAdvance));
		mapStr2Val.insert(make_pair("eActState_OnBegin", eActState_OnBegin));
		mapStr2Val.insert(make_pair("eActState_OnEnd", eActState_OnEnd));
		mapStr2Val.insert(make_pair("eActState_OnRetain", eActState_OnRetain));
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

SPrize::SPrize() : byIndex(0), eState((ELevelActStatus)0) { }

SPrize::SPrize(UINT8 byIndex_, ELevelActStatus eState_, const NItemProt::TVecItemGenInfo& vecItem_) : byIndex(byIndex_), eState(eState_), vecItem(vecItem_) { }

SPrize::SPrize(SPrize&& src) : byIndex(src.byIndex), eState(src.eState), vecItem(move(src.vecItem)) { }

SPrize& SPrize::operator=(SPrize&& rhs)
{
	if(this != &rhs)
	{
		this->~SPrize();
		new (this) SPrize(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SPrize& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.byIndex;
	src >> (UINT8&)s.eState;
	src >> s.vecItem;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SPrize& s)
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
	src << (UINT8&)s.eState;
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

bool FromXML(TiXmlElement& rElement, SPrize& s)
{
	if(strcmp(rElement.Value(), "SPrize") != 0)
	{
		LOG_CRI << "rElement is not SPrize!";
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
		LOG_CRI << "pElemChild for eState is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "ELevelActStatus") != 0)
	{
		LOG_CRI << "pElemChild is not ELevelActStatus!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eState") != 0)
	{
		LOG_CRI << "Attribute: name is not eState!";
		return false;
	}
	const char* pszVal_eState = pElemChild->Attribute("value");
	if(pszVal_eState == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!EnumStrToVal(pszVal_eState, s.eState))
	{
		LOG_CRI << "Read attribute: value fails!";
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

bool ToXML(const SPrize& s, TiXmlElement& rElement)
{
	rElement.SetValue("SPrize");
	rElement.SetAttribute("type", ToUTF8Ptr("奖励"));
	unique_ptr<TiXmlElement> pElem_byIndex(new TiXmlElement("UINT8"));
	if(pElem_byIndex == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byIndex->SetAttribute("name", "byIndex");
	pElem_byIndex->SetAttribute("value", NumberToString(s.byIndex).c_str());
	pElem_byIndex->SetAttribute("comment", ToUTF8Ptr("第几个奖"));
	if(rElement.LinkEndChild(pElem_byIndex.get()) != NULL)
		pElem_byIndex.release();
	unique_ptr<TiXmlElement> pElem_eState(new TiXmlElement("ELevelActStatus"));
	if(pElem_eState == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eState->SetAttribute("name", "eState");
	const char* pszEnum_eState = EnumValToStr(s.eState);
	if(pszEnum_eState == NULL)
	{
		LOG_CRI << "EnumValToStr for ELevelActStatus fails!";
		return false;
	}
	pElem_eState->SetAttribute("value", pszEnum_eState);
	pElem_eState->SetAttribute("comment", ToUTF8Ptr("第几个奖状态"));
	if(rElement.LinkEndChild(pElem_eState.get()) != NULL)
		pElem_eState.release();
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
	pElem_vecItem->SetAttribute("comment", ToUTF8Ptr("物品"));
	if(rElement.LinkEndChild(pElem_vecItem.get()) != NULL)
		pElem_vecItem.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecPrize& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SPrize s;
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

bool VectorToXML(const TVecPrize& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SPrize"));
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

SPrize2DB::SPrize2DB() : qwRoleID(0), wActID(0), wLevel(0), wStatus(0) { }

SPrize2DB::SPrize2DB(UINT64 qwRoleID_, UINT16 wActID_, UINT16 wLevel_, UINT16 wStatus_) : qwRoleID(qwRoleID_), wActID(wActID_), wLevel(wLevel_), wStatus(wStatus_) { }

CInArchive& operator>>(CInArchive& src, SPrize2DB& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwRoleID;
	src >> s.wActID;
	src >> s.wLevel;
	src >> s.wStatus;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SPrize2DB& s)
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
	src << s.wActID;
	src << s.wLevel;
	src << s.wStatus;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SPrize2DB& s)
{
	if(strcmp(rElement.Value(), "SPrize2DB") != 0)
	{
		LOG_CRI << "rElement is not SPrize2DB!";
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
		LOG_CRI << "pElemChild for wActID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wActID") != 0)
	{
		LOG_CRI << "Attribute: name is not wActID!";
		return false;
	}
	const char* pszVal_wActID = pElemChild->Attribute("value");
	if(pszVal_wActID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wActID, s.wActID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
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
		LOG_CRI << "pElemChild for wStatus is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wStatus") != 0)
	{
		LOG_CRI << "Attribute: name is not wStatus!";
		return false;
	}
	const char* pszVal_wStatus = pElemChild->Attribute("value");
	if(pszVal_wStatus == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wStatus, s.wStatus))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SPrize2DB& s, TiXmlElement& rElement)
{
	rElement.SetValue("SPrize2DB");
	rElement.SetAttribute("type", ToUTF8Ptr("数据操作"));
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
	unique_ptr<TiXmlElement> pElem_wActID(new TiXmlElement("UINT16"));
	if(pElem_wActID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wActID->SetAttribute("name", "wActID");
	pElem_wActID->SetAttribute("value", NumberToString(s.wActID).c_str());
	pElem_wActID->SetAttribute("comment", ToUTF8Ptr("活动ID"));
	if(rElement.LinkEndChild(pElem_wActID.get()) != NULL)
		pElem_wActID.release();
	unique_ptr<TiXmlElement> pElem_wLevel(new TiXmlElement("UINT16"));
	if(pElem_wLevel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wLevel->SetAttribute("name", "wLevel");
	pElem_wLevel->SetAttribute("value", NumberToString(s.wLevel).c_str());
	pElem_wLevel->SetAttribute("comment", ToUTF8Ptr("奖励NO"));
	if(rElement.LinkEndChild(pElem_wLevel.get()) != NULL)
		pElem_wLevel.release();
	unique_ptr<TiXmlElement> pElem_wStatus(new TiXmlElement("UINT16"));
	if(pElem_wStatus == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wStatus->SetAttribute("name", "wStatus");
	pElem_wStatus->SetAttribute("value", NumberToString(s.wStatus).c_str());
	pElem_wStatus->SetAttribute("comment", ToUTF8Ptr("奖励状态"));
	if(rElement.LinkEndChild(pElem_wStatus.get()) != NULL)
		pElem_wStatus.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecPrize2DB& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SPrize2DB s;
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

bool VectorToXML(const TVecPrize2DB& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SPrize2DB"));
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

STime::STime() : dwAdvTime(0), dwBeginTime(0), dwEndTime(0), dwRetainTime(0) { }

STime::STime(UINT32 dwAdvTime_, UINT32 dwBeginTime_, UINT32 dwEndTime_, UINT32 dwRetainTime_) : dwAdvTime(dwAdvTime_), dwBeginTime(dwBeginTime_), dwEndTime(dwEndTime_), dwRetainTime(dwRetainTime_) { }

CInArchive& operator>>(CInArchive& src, STime& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.dwAdvTime;
	src >> s.dwBeginTime;
	src >> s.dwEndTime;
	src >> s.dwRetainTime;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const STime& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.dwAdvTime;
	src << s.dwBeginTime;
	src << s.dwEndTime;
	src << s.dwRetainTime;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, STime& s)
{
	if(strcmp(rElement.Value(), "STime") != 0)
	{
		LOG_CRI << "rElement is not STime!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwAdvTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwAdvTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwAdvTime!";
		return false;
	}
	const char* pszVal_dwAdvTime = pElemChild->Attribute("value");
	if(pszVal_dwAdvTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwAdvTime, s.dwAdvTime))
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
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwRetainTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwRetainTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwRetainTime!";
		return false;
	}
	const char* pszVal_dwRetainTime = pElemChild->Attribute("value");
	if(pszVal_dwRetainTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwRetainTime, s.dwRetainTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const STime& s, TiXmlElement& rElement)
{
	rElement.SetValue("STime");
	rElement.SetAttribute("type", ToUTF8Ptr("活动配置时间"));
	unique_ptr<TiXmlElement> pElem_dwAdvTime(new TiXmlElement("UINT32"));
	if(pElem_dwAdvTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwAdvTime->SetAttribute("name", "dwAdvTime");
	pElem_dwAdvTime->SetAttribute("value", NumberToString(s.dwAdvTime).c_str());
	pElem_dwAdvTime->SetAttribute("comment", ToUTF8Ptr("活动预告时间"));
	if(rElement.LinkEndChild(pElem_dwAdvTime.get()) != NULL)
		pElem_dwAdvTime.release();
	unique_ptr<TiXmlElement> pElem_dwBeginTime(new TiXmlElement("UINT32"));
	if(pElem_dwBeginTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwBeginTime->SetAttribute("name", "dwBeginTime");
	pElem_dwBeginTime->SetAttribute("value", NumberToString(s.dwBeginTime).c_str());
	pElem_dwBeginTime->SetAttribute("comment", ToUTF8Ptr("活动开始时间"));
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
	pElem_dwEndTime->SetAttribute("comment", ToUTF8Ptr("活动结束时间"));
	if(rElement.LinkEndChild(pElem_dwEndTime.get()) != NULL)
		pElem_dwEndTime.release();
	unique_ptr<TiXmlElement> pElem_dwRetainTime(new TiXmlElement("UINT32"));
	if(pElem_dwRetainTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwRetainTime->SetAttribute("name", "dwRetainTime");
	pElem_dwRetainTime->SetAttribute("value", NumberToString(s.dwRetainTime).c_str());
	pElem_dwRetainTime->SetAttribute("comment", ToUTF8Ptr("活动预留时间"));
	if(rElement.LinkEndChild(pElem_dwRetainTime.get()) != NULL)
		pElem_dwRetainTime.release();
	return true;
}

#endif

SPrizeState::SPrizeState() : byIndex(0), eStatus((ELevelActStatus)0) { }

SPrizeState::SPrizeState(UINT8 byIndex_, ELevelActStatus eStatus_) : byIndex(byIndex_), eStatus(eStatus_) { }

CInArchive& operator>>(CInArchive& src, SPrizeState& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.byIndex;
	src >> (UINT8&)s.eStatus;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SPrizeState& s)
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
	src << (UINT8&)s.eStatus;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SPrizeState& s)
{
	if(strcmp(rElement.Value(), "SPrizeState") != 0)
	{
		LOG_CRI << "rElement is not SPrizeState!";
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
		LOG_CRI << "pElemChild for eStatus is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "ELevelActStatus") != 0)
	{
		LOG_CRI << "pElemChild is not ELevelActStatus!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eStatus") != 0)
	{
		LOG_CRI << "Attribute: name is not eStatus!";
		return false;
	}
	const char* pszVal_eStatus = pElemChild->Attribute("value");
	if(pszVal_eStatus == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!EnumStrToVal(pszVal_eStatus, s.eStatus))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SPrizeState& s, TiXmlElement& rElement)
{
	rElement.SetValue("SPrizeState");
	rElement.SetAttribute("type", ToUTF8Ptr("奖励状态"));
	unique_ptr<TiXmlElement> pElem_byIndex(new TiXmlElement("UINT8"));
	if(pElem_byIndex == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byIndex->SetAttribute("name", "byIndex");
	pElem_byIndex->SetAttribute("value", NumberToString(s.byIndex).c_str());
	pElem_byIndex->SetAttribute("comment", ToUTF8Ptr("领奖"));
	if(rElement.LinkEndChild(pElem_byIndex.get()) != NULL)
		pElem_byIndex.release();
	unique_ptr<TiXmlElement> pElem_eStatus(new TiXmlElement("ELevelActStatus"));
	if(pElem_eStatus == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eStatus->SetAttribute("name", "eStatus");
	const char* pszEnum_eStatus = EnumValToStr(s.eStatus);
	if(pszEnum_eStatus == NULL)
	{
		LOG_CRI << "EnumValToStr for ELevelActStatus fails!";
		return false;
	}
	pElem_eStatus->SetAttribute("value", pszEnum_eStatus);
	pElem_eStatus->SetAttribute("comment", ToUTF8Ptr("奖励状态"));
	if(rElement.LinkEndChild(pElem_eStatus.get()) != NULL)
		pElem_eStatus.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecPrizeState& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SPrizeState s;
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

bool VectorToXML(const TVecPrizeState& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SPrizeState"));
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

} //namespace NLevelPrize
