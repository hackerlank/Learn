/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    ShushanBattleProt.cpp
//  Purpose:      蜀山论剑相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "ShushanBattleProt.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NShushanBattleProt
{

#ifdef PROT_USE_XML

const char* EnumValToStr(ESSBattleStatus e)
{
	switch(e)
	{
	case eSSBattle_ENTER:
		return "eSSBattle_ENTER";
	case eSSBattle_QUIT:
		return "eSSBattle_QUIT";
	case eSSBattle_JOINBYE:
		return "eSSBattle_JOINBYE";
	case eSSBattle_FIGHTING:
		return "eSSBattle_FIGHTING";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, ESSBattleStatus& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, ESSBattleStatus> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eSSBattle_ENTER", eSSBattle_ENTER));
		mapStr2Val.insert(make_pair("eSSBattle_QUIT", eSSBattle_QUIT));
		mapStr2Val.insert(make_pair("eSSBattle_JOINBYE", eSSBattle_JOINBYE));
		mapStr2Val.insert(make_pair("eSSBattle_FIGHTING", eSSBattle_FIGHTING));
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

const char* EnumValToStr(ESSBattleResult e)
{
	switch(e)
	{
	case eSSBattle_Suc:
		return "eSSBattle_Suc";
	case eSSBattle_NotRuning:
		return "eSSBattle_NotRuning";
	case eSSBattle_CDTime:
		return "eSSBattle_CDTime";
	case eSSBattle_LevelLimit:
		return "eSSBattle_LevelLimit";
	case eSSBattle_LackMoney:
		return "eSSBattle_LackMoney";
	case eSSBattle_NotEnter:
		return "eSSBattle_NotEnter";
	case eSSBattle_Full:
		return "eSSBattle_Full";
	case eSSBattle_NotEnough:
		return "eSSBattle_NotEnough";
	case eSSBattle_Used:
		return "eSSBattle_Used";
	case eSSBattle_OtherErr:
		return "eSSBattle_OtherErr";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, ESSBattleResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, ESSBattleResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eSSBattle_Suc", eSSBattle_Suc));
		mapStr2Val.insert(make_pair("eSSBattle_NotRuning", eSSBattle_NotRuning));
		mapStr2Val.insert(make_pair("eSSBattle_CDTime", eSSBattle_CDTime));
		mapStr2Val.insert(make_pair("eSSBattle_LevelLimit", eSSBattle_LevelLimit));
		mapStr2Val.insert(make_pair("eSSBattle_LackMoney", eSSBattle_LackMoney));
		mapStr2Val.insert(make_pair("eSSBattle_NotEnter", eSSBattle_NotEnter));
		mapStr2Val.insert(make_pair("eSSBattle_Full", eSSBattle_Full));
		mapStr2Val.insert(make_pair("eSSBattle_NotEnough", eSSBattle_NotEnough));
		mapStr2Val.insert(make_pair("eSSBattle_Used", eSSBattle_Used));
		mapStr2Val.insert(make_pair("eSSBattle_OtherErr", eSSBattle_OtherErr));
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

SBattleTaskData::SBattleTaskData() : byTaskID(0), byAward(0), byComplete(0) { }

SBattleTaskData::SBattleTaskData(UINT8 byTaskID_, UINT8 byAward_, UINT8 byComplete_) : byTaskID(byTaskID_), byAward(byAward_), byComplete(byComplete_) { }

CInArchive& operator>>(CInArchive& src, SBattleTaskData& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.byTaskID;
	src >> s.byAward;
	src >> s.byComplete;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SBattleTaskData& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.byTaskID;
	src << s.byAward;
	src << s.byComplete;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SBattleTaskData& s)
{
	if(strcmp(rElement.Value(), "SBattleTaskData") != 0)
	{
		LOG_CRI << "rElement is not SBattleTaskData!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byTaskID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byTaskID") != 0)
	{
		LOG_CRI << "Attribute: name is not byTaskID!";
		return false;
	}
	const char* pszVal_byTaskID = pElemChild->Attribute("value");
	if(pszVal_byTaskID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byTaskID, s.byTaskID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byAward is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byAward") != 0)
	{
		LOG_CRI << "Attribute: name is not byAward!";
		return false;
	}
	const char* pszVal_byAward = pElemChild->Attribute("value");
	if(pszVal_byAward == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byAward, s.byAward))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byComplete is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byComplete") != 0)
	{
		LOG_CRI << "Attribute: name is not byComplete!";
		return false;
	}
	const char* pszVal_byComplete = pElemChild->Attribute("value");
	if(pszVal_byComplete == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byComplete, s.byComplete))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SBattleTaskData& s, TiXmlElement& rElement)
{
	rElement.SetValue("SBattleTaskData");
	rElement.SetAttribute("type", ToUTF8Ptr("任务数据结构"));
	unique_ptr<TiXmlElement> pElem_byTaskID(new TiXmlElement("UINT8"));
	if(pElem_byTaskID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byTaskID->SetAttribute("name", "byTaskID");
	pElem_byTaskID->SetAttribute("value", NumberToString(s.byTaskID).c_str());
	pElem_byTaskID->SetAttribute("comment", ToUTF8Ptr("任务ID"));
	if(rElement.LinkEndChild(pElem_byTaskID.get()) != NULL)
		pElem_byTaskID.release();
	unique_ptr<TiXmlElement> pElem_byAward(new TiXmlElement("UINT8"));
	if(pElem_byAward == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byAward->SetAttribute("name", "byAward");
	pElem_byAward->SetAttribute("value", NumberToString(s.byAward).c_str());
	pElem_byAward->SetAttribute("comment", ToUTF8Ptr("荣誉奖励值"));
	if(rElement.LinkEndChild(pElem_byAward.get()) != NULL)
		pElem_byAward.release();
	unique_ptr<TiXmlElement> pElem_byComplete(new TiXmlElement("UINT8"));
	if(pElem_byComplete == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byComplete->SetAttribute("name", "byComplete");
	pElem_byComplete->SetAttribute("value", NumberToString(s.byComplete).c_str());
	pElem_byComplete->SetAttribute("comment", ToUTF8Ptr("是否完成(0否,1是)"));
	if(rElement.LinkEndChild(pElem_byComplete.get()) != NULL)
		pElem_byComplete.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecTaskData& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SBattleTaskData s;
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

bool VectorToXML(const TVecTaskData& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SBattleTaskData"));
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

SSSBattleReport::SSSBattleReport() : byRound(0), qwRoleA(0), qwRoleB(0), byResult(0), qwBattleID(0), 
			byCurrKill(0), wHonor(0) { }

SSSBattleReport::SSSBattleReport(UINT8 byRound_, const std::string& strNameA_, UINT64 qwRoleA_, const std::string& strNameB_, UINT64 qwRoleB_, 
			UINT8 byResult_, UINT64 qwBattleID_, UINT8 byCurrKill_, UINT16 wHonor_)
			: byRound(byRound_), strNameA(strNameA_), qwRoleA(qwRoleA_), strNameB(strNameB_), qwRoleB(qwRoleB_), 
			byResult(byResult_), qwBattleID(qwBattleID_), byCurrKill(byCurrKill_), wHonor(wHonor_) { }

SSSBattleReport::SSSBattleReport(SSSBattleReport&& src) : byRound(src.byRound), strNameA(move(src.strNameA)), qwRoleA(src.qwRoleA), strNameB(move(src.strNameB)), qwRoleB(src.qwRoleB), 
			byResult(src.byResult), qwBattleID(src.qwBattleID), byCurrKill(src.byCurrKill), wHonor(src.wHonor) { }

SSSBattleReport& SSSBattleReport::operator=(SSSBattleReport&& rhs)
{
	if(this != &rhs)
	{
		this->~SSSBattleReport();
		new (this) SSSBattleReport(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SSSBattleReport& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.byRound;
	src >> s.strNameA;
	src >> s.qwRoleA;
	src >> s.strNameB;
	src >> s.qwRoleB;
	src >> s.byResult;
	src >> s.qwBattleID;
	src >> s.byCurrKill;
	src >> s.wHonor;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SSSBattleReport& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.byRound;
	src << s.strNameA;
	src << s.qwRoleA;
	src << s.strNameB;
	src << s.qwRoleB;
	src << s.byResult;
	src << s.qwBattleID;
	src << s.byCurrKill;
	src << s.wHonor;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SSSBattleReport& s)
{
	if(strcmp(rElement.Value(), "SSSBattleReport") != 0)
	{
		LOG_CRI << "rElement is not SSSBattleReport!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byRound is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byRound") != 0)
	{
		LOG_CRI << "Attribute: name is not byRound!";
		return false;
	}
	const char* pszVal_byRound = pElemChild->Attribute("value");
	if(pszVal_byRound == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byRound, s.byRound))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strNameA is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strNameA") != 0)
	{
		LOG_CRI << "Attribute: name is not strNameA!";
		return false;
	}
	const char* pszVal_strNameA = pElemChild->Attribute("value");
	if(pszVal_strNameA == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strNameA = pszVal_strNameA;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwRoleA is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwRoleA") != 0)
	{
		LOG_CRI << "Attribute: name is not qwRoleA!";
		return false;
	}
	const char* pszVal_qwRoleA = pElemChild->Attribute("value");
	if(pszVal_qwRoleA == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwRoleA, s.qwRoleA))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strNameB is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strNameB") != 0)
	{
		LOG_CRI << "Attribute: name is not strNameB!";
		return false;
	}
	const char* pszVal_strNameB = pElemChild->Attribute("value");
	if(pszVal_strNameB == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strNameB = pszVal_strNameB;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwRoleB is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwRoleB") != 0)
	{
		LOG_CRI << "Attribute: name is not qwRoleB!";
		return false;
	}
	const char* pszVal_qwRoleB = pElemChild->Attribute("value");
	if(pszVal_qwRoleB == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwRoleB, s.qwRoleB))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byResult is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byResult") != 0)
	{
		LOG_CRI << "Attribute: name is not byResult!";
		return false;
	}
	const char* pszVal_byResult = pElemChild->Attribute("value");
	if(pszVal_byResult == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byResult, s.byResult))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
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
		LOG_CRI << "pElemChild for byCurrKill is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byCurrKill") != 0)
	{
		LOG_CRI << "Attribute: name is not byCurrKill!";
		return false;
	}
	const char* pszVal_byCurrKill = pElemChild->Attribute("value");
	if(pszVal_byCurrKill == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byCurrKill, s.byCurrKill))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wHonor is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wHonor") != 0)
	{
		LOG_CRI << "Attribute: name is not wHonor!";
		return false;
	}
	const char* pszVal_wHonor = pElemChild->Attribute("value");
	if(pszVal_wHonor == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wHonor, s.wHonor))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SSSBattleReport& s, TiXmlElement& rElement)
{
	rElement.SetValue("SSSBattleReport");
	rElement.SetAttribute("type", ToUTF8Ptr("战斗战报数据结构"));
	unique_ptr<TiXmlElement> pElem_byRound(new TiXmlElement("UINT8"));
	if(pElem_byRound == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byRound->SetAttribute("name", "byRound");
	pElem_byRound->SetAttribute("value", NumberToString(s.byRound).c_str());
	pElem_byRound->SetAttribute("comment", ToUTF8Ptr("当前轮次"));
	if(rElement.LinkEndChild(pElem_byRound.get()) != NULL)
		pElem_byRound.release();
	unique_ptr<TiXmlElement> pElem_strNameA(new TiXmlElement("string"));
	if(pElem_strNameA == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strNameA->SetAttribute("name", "strNameA");
	pElem_strNameA->SetAttribute("value", s.strNameA.c_str());
	pElem_strNameA->SetAttribute("comment", ToUTF8Ptr("攻方玩家名字"));
	if(rElement.LinkEndChild(pElem_strNameA.get()) != NULL)
		pElem_strNameA.release();
	unique_ptr<TiXmlElement> pElem_qwRoleA(new TiXmlElement("UINT64"));
	if(pElem_qwRoleA == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwRoleA->SetAttribute("name", "qwRoleA");
	pElem_qwRoleA->SetAttribute("value", NumberToString(s.qwRoleA).c_str());
	pElem_qwRoleA->SetAttribute("comment", ToUTF8Ptr("攻方玩家ID"));
	if(rElement.LinkEndChild(pElem_qwRoleA.get()) != NULL)
		pElem_qwRoleA.release();
	unique_ptr<TiXmlElement> pElem_strNameB(new TiXmlElement("string"));
	if(pElem_strNameB == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strNameB->SetAttribute("name", "strNameB");
	pElem_strNameB->SetAttribute("value", s.strNameB.c_str());
	pElem_strNameB->SetAttribute("comment", ToUTF8Ptr("守方玩家名字"));
	if(rElement.LinkEndChild(pElem_strNameB.get()) != NULL)
		pElem_strNameB.release();
	unique_ptr<TiXmlElement> pElem_qwRoleB(new TiXmlElement("UINT64"));
	if(pElem_qwRoleB == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwRoleB->SetAttribute("name", "qwRoleB");
	pElem_qwRoleB->SetAttribute("value", NumberToString(s.qwRoleB).c_str());
	pElem_qwRoleB->SetAttribute("comment", ToUTF8Ptr("守方玩家ID"));
	if(rElement.LinkEndChild(pElem_qwRoleB.get()) != NULL)
		pElem_qwRoleB.release();
	unique_ptr<TiXmlElement> pElem_byResult(new TiXmlElement("UINT8"));
	if(pElem_byResult == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byResult->SetAttribute("name", "byResult");
	pElem_byResult->SetAttribute("value", NumberToString(s.byResult).c_str());
	pElem_byResult->SetAttribute("comment", ToUTF8Ptr("结果(0是攻方胜利,1是守方胜利,2是攻方逃跑,3守方逃跑,4攻方轮空)"));
	if(rElement.LinkEndChild(pElem_byResult.get()) != NULL)
		pElem_byResult.release();
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
	unique_ptr<TiXmlElement> pElem_byCurrKill(new TiXmlElement("UINT8"));
	if(pElem_byCurrKill == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byCurrKill->SetAttribute("name", "byCurrKill");
	pElem_byCurrKill->SetAttribute("value", NumberToString(s.byCurrKill).c_str());
	pElem_byCurrKill->SetAttribute("comment", ToUTF8Ptr("当前连杀数(若个人战报即表明个人连杀数,若全部战报即表明攻方连杀数)"));
	if(rElement.LinkEndChild(pElem_byCurrKill.get()) != NULL)
		pElem_byCurrKill.release();
	unique_ptr<TiXmlElement> pElem_wHonor(new TiXmlElement("UINT16"));
	if(pElem_wHonor == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wHonor->SetAttribute("name", "wHonor");
	pElem_wHonor->SetAttribute("value", NumberToString(s.wHonor).c_str());
	pElem_wHonor->SetAttribute("comment", ToUTF8Ptr("当场获得荣誉值(若个人战报即表明个人获得荣誉值,若全部战报即表明攻方获得荣誉值)"));
	if(rElement.LinkEndChild(pElem_wHonor.get()) != NULL)
		pElem_wHonor.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecSSBattleReport& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SSSBattleReport s;
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

bool VectorToXML(const TVecSSBattleReport& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SSSBattleReport"));
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

SOtherPlayer::SOtherPlayer() : qwRoleIDOther(0), byCurrKillOther(0), wHonorOther(0), wSkillFlagsOther(0), dwMaxHpOther(0), 
			dwCurHpOther(0), dwBattlePowerOther(0) { }

SOtherPlayer::SOtherPlayer(UINT64 qwRoleIDOther_, UINT8 byCurrKillOther_, UINT16 wHonorOther_, UINT16 wSkillFlagsOther_, UINT32 dwMaxHpOther_, 
			UINT32 dwCurHpOther_, UINT32 dwBattlePowerOther_, const NMapProt::SPlayerAppear& rPlayerAppear_)
			: qwRoleIDOther(qwRoleIDOther_), byCurrKillOther(byCurrKillOther_), wHonorOther(wHonorOther_), wSkillFlagsOther(wSkillFlagsOther_), dwMaxHpOther(dwMaxHpOther_), 
			dwCurHpOther(dwCurHpOther_), dwBattlePowerOther(dwBattlePowerOther_), rPlayerAppear(rPlayerAppear_) { }

SOtherPlayer::SOtherPlayer(SOtherPlayer&& src) : qwRoleIDOther(src.qwRoleIDOther), byCurrKillOther(src.byCurrKillOther), wHonorOther(src.wHonorOther), wSkillFlagsOther(src.wSkillFlagsOther), dwMaxHpOther(src.dwMaxHpOther), 
			dwCurHpOther(src.dwCurHpOther), dwBattlePowerOther(src.dwBattlePowerOther), rPlayerAppear(move(src.rPlayerAppear)) { }

SOtherPlayer& SOtherPlayer::operator=(SOtherPlayer&& rhs)
{
	if(this != &rhs)
	{
		this->~SOtherPlayer();
		new (this) SOtherPlayer(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SOtherPlayer& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwRoleIDOther;
	src >> s.byCurrKillOther;
	src >> s.wHonorOther;
	src >> s.wSkillFlagsOther;
	src >> s.dwMaxHpOther;
	src >> s.dwCurHpOther;
	src >> s.dwBattlePowerOther;
	src >> s.rPlayerAppear;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SOtherPlayer& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.qwRoleIDOther;
	src << s.byCurrKillOther;
	src << s.wHonorOther;
	src << s.wSkillFlagsOther;
	src << s.dwMaxHpOther;
	src << s.dwCurHpOther;
	src << s.dwBattlePowerOther;
	src << s.rPlayerAppear;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SOtherPlayer& s)
{
	if(strcmp(rElement.Value(), "SOtherPlayer") != 0)
	{
		LOG_CRI << "rElement is not SOtherPlayer!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwRoleIDOther is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwRoleIDOther") != 0)
	{
		LOG_CRI << "Attribute: name is not qwRoleIDOther!";
		return false;
	}
	const char* pszVal_qwRoleIDOther = pElemChild->Attribute("value");
	if(pszVal_qwRoleIDOther == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwRoleIDOther, s.qwRoleIDOther))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byCurrKillOther is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byCurrKillOther") != 0)
	{
		LOG_CRI << "Attribute: name is not byCurrKillOther!";
		return false;
	}
	const char* pszVal_byCurrKillOther = pElemChild->Attribute("value");
	if(pszVal_byCurrKillOther == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byCurrKillOther, s.byCurrKillOther))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wHonorOther is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wHonorOther") != 0)
	{
		LOG_CRI << "Attribute: name is not wHonorOther!";
		return false;
	}
	const char* pszVal_wHonorOther = pElemChild->Attribute("value");
	if(pszVal_wHonorOther == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wHonorOther, s.wHonorOther))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wSkillFlagsOther is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wSkillFlagsOther") != 0)
	{
		LOG_CRI << "Attribute: name is not wSkillFlagsOther!";
		return false;
	}
	const char* pszVal_wSkillFlagsOther = pElemChild->Attribute("value");
	if(pszVal_wSkillFlagsOther == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wSkillFlagsOther, s.wSkillFlagsOther))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwMaxHpOther is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwMaxHpOther") != 0)
	{
		LOG_CRI << "Attribute: name is not dwMaxHpOther!";
		return false;
	}
	const char* pszVal_dwMaxHpOther = pElemChild->Attribute("value");
	if(pszVal_dwMaxHpOther == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwMaxHpOther, s.dwMaxHpOther))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwCurHpOther is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwCurHpOther") != 0)
	{
		LOG_CRI << "Attribute: name is not dwCurHpOther!";
		return false;
	}
	const char* pszVal_dwCurHpOther = pElemChild->Attribute("value");
	if(pszVal_dwCurHpOther == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwCurHpOther, s.dwCurHpOther))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwBattlePowerOther is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwBattlePowerOther") != 0)
	{
		LOG_CRI << "Attribute: name is not dwBattlePowerOther!";
		return false;
	}
	const char* pszVal_dwBattlePowerOther = pElemChild->Attribute("value");
	if(pszVal_dwBattlePowerOther == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwBattlePowerOther, s.dwBattlePowerOther))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for rPlayerAppear is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "MapProt::SPlayerAppear") != 0)
	{
		LOG_CRI << "pElemChild is not MapProt::SPlayerAppear!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "rPlayerAppear") != 0)
	{
		LOG_CRI << "Attribute: name is not rPlayerAppear!";
		return false;
	}
	if(!FromXML(*pElemChild, s.rPlayerAppear))
	{
		LOG_CRI << "FromXML for: rPlayerAppear fails!";
		return false;
	}
	return true;
}

bool ToXML(const SOtherPlayer& s, TiXmlElement& rElement)
{
	rElement.SetValue("SOtherPlayer");
	rElement.SetAttribute("type", ToUTF8Ptr("对方玩家数据结构"));
	unique_ptr<TiXmlElement> pElem_qwRoleIDOther(new TiXmlElement("UINT64"));
	if(pElem_qwRoleIDOther == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwRoleIDOther->SetAttribute("name", "qwRoleIDOther");
	pElem_qwRoleIDOther->SetAttribute("value", NumberToString(s.qwRoleIDOther).c_str());
	pElem_qwRoleIDOther->SetAttribute("comment", ToUTF8Ptr("对方玩家ID"));
	if(rElement.LinkEndChild(pElem_qwRoleIDOther.get()) != NULL)
		pElem_qwRoleIDOther.release();
	unique_ptr<TiXmlElement> pElem_byCurrKillOther(new TiXmlElement("UINT8"));
	if(pElem_byCurrKillOther == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byCurrKillOther->SetAttribute("name", "byCurrKillOther");
	pElem_byCurrKillOther->SetAttribute("value", NumberToString(s.byCurrKillOther).c_str());
	pElem_byCurrKillOther->SetAttribute("comment", ToUTF8Ptr("对方当前连杀数"));
	if(rElement.LinkEndChild(pElem_byCurrKillOther.get()) != NULL)
		pElem_byCurrKillOther.release();
	unique_ptr<TiXmlElement> pElem_wHonorOther(new TiXmlElement("UINT16"));
	if(pElem_wHonorOther == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wHonorOther->SetAttribute("name", "wHonorOther");
	pElem_wHonorOther->SetAttribute("value", NumberToString(s.wHonorOther).c_str());
	pElem_wHonorOther->SetAttribute("comment", ToUTF8Ptr("对方总荣誉值"));
	if(rElement.LinkEndChild(pElem_wHonorOther.get()) != NULL)
		pElem_wHonorOther.release();
	unique_ptr<TiXmlElement> pElem_wSkillFlagsOther(new TiXmlElement("UINT16"));
	if(pElem_wSkillFlagsOther == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wSkillFlagsOther->SetAttribute("name", "wSkillFlagsOther");
	pElem_wSkillFlagsOther->SetAttribute("value", NumberToString(s.wSkillFlagsOther).c_str());
	pElem_wSkillFlagsOther->SetAttribute("comment", ToUTF8Ptr("对方技能使用位域,对应位表示技能是否已使用(低8位)"));
	if(rElement.LinkEndChild(pElem_wSkillFlagsOther.get()) != NULL)
		pElem_wSkillFlagsOther.release();
	unique_ptr<TiXmlElement> pElem_dwMaxHpOther(new TiXmlElement("UINT32"));
	if(pElem_dwMaxHpOther == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwMaxHpOther->SetAttribute("name", "dwMaxHpOther");
	pElem_dwMaxHpOther->SetAttribute("value", NumberToString(s.dwMaxHpOther).c_str());
	pElem_dwMaxHpOther->SetAttribute("comment", ToUTF8Ptr("对方总血量"));
	if(rElement.LinkEndChild(pElem_dwMaxHpOther.get()) != NULL)
		pElem_dwMaxHpOther.release();
	unique_ptr<TiXmlElement> pElem_dwCurHpOther(new TiXmlElement("UINT32"));
	if(pElem_dwCurHpOther == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwCurHpOther->SetAttribute("name", "dwCurHpOther");
	pElem_dwCurHpOther->SetAttribute("value", NumberToString(s.dwCurHpOther).c_str());
	pElem_dwCurHpOther->SetAttribute("comment", ToUTF8Ptr("对方当前血量"));
	if(rElement.LinkEndChild(pElem_dwCurHpOther.get()) != NULL)
		pElem_dwCurHpOther.release();
	unique_ptr<TiXmlElement> pElem_dwBattlePowerOther(new TiXmlElement("UINT32"));
	if(pElem_dwBattlePowerOther == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwBattlePowerOther->SetAttribute("name", "dwBattlePowerOther");
	pElem_dwBattlePowerOther->SetAttribute("value", NumberToString(s.dwBattlePowerOther).c_str());
	pElem_dwBattlePowerOther->SetAttribute("comment", ToUTF8Ptr("对方总战斗力"));
	if(rElement.LinkEndChild(pElem_dwBattlePowerOther.get()) != NULL)
		pElem_dwBattlePowerOther.release();
	unique_ptr<TiXmlElement> pElem_rPlayerAppear(new TiXmlElement("MapProt::SPlayerAppear"));
	if(pElem_rPlayerAppear == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_rPlayerAppear->SetAttribute("name", "rPlayerAppear");
	if(!ToXML(s.rPlayerAppear, *pElem_rPlayerAppear))
	{
		LOG_CRI << "rPlayerAppear ToXML fails!";
		return false;
	}
	pElem_rPlayerAppear->SetAttribute("comment", ToUTF8Ptr("对方玩家的外观"));
	if(rElement.LinkEndChild(pElem_rPlayerAppear.get()) != NULL)
		pElem_rPlayerAppear.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecOtherPlayer& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SOtherPlayer s;
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

bool VectorToXML(const TVecOtherPlayer& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SOtherPlayer"));
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

SSSBattlePairInfo::SSSBattlePairInfo() : byRound(0), wTimeLeft(0), byCurrKill(0), byMaxKill(0), byTotalWin(0), 
			byTotalLose(0), wHonor(0), byDomineer(0), byAnger(0), wSkillFlags(0), 
			dwMaxHp(0), dwCurHp(0), dwBattlePower(0) { }

SSSBattlePairInfo::SSSBattlePairInfo(SSSBattlePairInfo&& src) : byRound(src.byRound), wTimeLeft(src.wTimeLeft), byCurrKill(src.byCurrKill), byMaxKill(src.byMaxKill), byTotalWin(src.byTotalWin), 
			byTotalLose(src.byTotalLose), wHonor(src.wHonor), byDomineer(src.byDomineer), byAnger(src.byAnger), wSkillFlags(src.wSkillFlags), 
			vecTaskData(move(src.vecTaskData)), dwMaxHp(src.dwMaxHp), dwCurHp(src.dwCurHp), dwBattlePower(src.dwBattlePower), vecOtherPlayer(move(src.vecOtherPlayer)) { }

SSSBattlePairInfo& SSSBattlePairInfo::operator=(SSSBattlePairInfo&& rhs)
{
	if(this != &rhs)
	{
		this->~SSSBattlePairInfo();
		new (this) SSSBattlePairInfo(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SSSBattlePairInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.byRound;
	src >> s.wTimeLeft;
	src >> s.byCurrKill;
	src >> s.byMaxKill;
	src >> s.byTotalWin;
	src >> s.byTotalLose;
	src >> s.wHonor;
	src >> s.byDomineer;
	src >> s.byAnger;
	src >> s.wSkillFlags;
	src >> s.vecTaskData;
	src >> s.dwMaxHp;
	src >> s.dwCurHp;
	src >> s.dwBattlePower;
	src >> s.vecOtherPlayer;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SSSBattlePairInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.byRound;
	src << s.wTimeLeft;
	src << s.byCurrKill;
	src << s.byMaxKill;
	src << s.byTotalWin;
	src << s.byTotalLose;
	src << s.wHonor;
	src << s.byDomineer;
	src << s.byAnger;
	src << s.wSkillFlags;
	src << s.vecTaskData;
	src << s.dwMaxHp;
	src << s.dwCurHp;
	src << s.dwBattlePower;
	src << s.vecOtherPlayer;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SSSBattlePairInfo& s)
{
	if(strcmp(rElement.Value(), "SSSBattlePairInfo") != 0)
	{
		LOG_CRI << "rElement is not SSSBattlePairInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byRound is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byRound") != 0)
	{
		LOG_CRI << "Attribute: name is not byRound!";
		return false;
	}
	const char* pszVal_byRound = pElemChild->Attribute("value");
	if(pszVal_byRound == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byRound, s.byRound))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wTimeLeft is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wTimeLeft") != 0)
	{
		LOG_CRI << "Attribute: name is not wTimeLeft!";
		return false;
	}
	const char* pszVal_wTimeLeft = pElemChild->Attribute("value");
	if(pszVal_wTimeLeft == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wTimeLeft, s.wTimeLeft))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byCurrKill is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byCurrKill") != 0)
	{
		LOG_CRI << "Attribute: name is not byCurrKill!";
		return false;
	}
	const char* pszVal_byCurrKill = pElemChild->Attribute("value");
	if(pszVal_byCurrKill == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byCurrKill, s.byCurrKill))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byMaxKill is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byMaxKill") != 0)
	{
		LOG_CRI << "Attribute: name is not byMaxKill!";
		return false;
	}
	const char* pszVal_byMaxKill = pElemChild->Attribute("value");
	if(pszVal_byMaxKill == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byMaxKill, s.byMaxKill))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byTotalWin is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byTotalWin") != 0)
	{
		LOG_CRI << "Attribute: name is not byTotalWin!";
		return false;
	}
	const char* pszVal_byTotalWin = pElemChild->Attribute("value");
	if(pszVal_byTotalWin == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byTotalWin, s.byTotalWin))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byTotalLose is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byTotalLose") != 0)
	{
		LOG_CRI << "Attribute: name is not byTotalLose!";
		return false;
	}
	const char* pszVal_byTotalLose = pElemChild->Attribute("value");
	if(pszVal_byTotalLose == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byTotalLose, s.byTotalLose))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wHonor is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wHonor") != 0)
	{
		LOG_CRI << "Attribute: name is not wHonor!";
		return false;
	}
	const char* pszVal_wHonor = pElemChild->Attribute("value");
	if(pszVal_wHonor == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wHonor, s.wHonor))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byDomineer is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byDomineer") != 0)
	{
		LOG_CRI << "Attribute: name is not byDomineer!";
		return false;
	}
	const char* pszVal_byDomineer = pElemChild->Attribute("value");
	if(pszVal_byDomineer == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byDomineer, s.byDomineer))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byAnger is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byAnger") != 0)
	{
		LOG_CRI << "Attribute: name is not byAnger!";
		return false;
	}
	const char* pszVal_byAnger = pElemChild->Attribute("value");
	if(pszVal_byAnger == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byAnger, s.byAnger))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wSkillFlags is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wSkillFlags") != 0)
	{
		LOG_CRI << "Attribute: name is not wSkillFlags!";
		return false;
	}
	const char* pszVal_wSkillFlags = pElemChild->Attribute("value");
	if(pszVal_wSkillFlags == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wSkillFlags, s.wSkillFlags))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecTaskData is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecTaskData") != 0)
	{
		LOG_CRI << "pElemChild is not TVecTaskData!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecTaskData") != 0)
	{
		LOG_CRI << "Attribute: name is not vecTaskData!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecTaskData))
	{
		LOG_CRI << "VectorFromXML for vecTaskData fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwMaxHp is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwMaxHp") != 0)
	{
		LOG_CRI << "Attribute: name is not dwMaxHp!";
		return false;
	}
	const char* pszVal_dwMaxHp = pElemChild->Attribute("value");
	if(pszVal_dwMaxHp == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwMaxHp, s.dwMaxHp))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwCurHp is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwCurHp") != 0)
	{
		LOG_CRI << "Attribute: name is not dwCurHp!";
		return false;
	}
	const char* pszVal_dwCurHp = pElemChild->Attribute("value");
	if(pszVal_dwCurHp == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwCurHp, s.dwCurHp))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwBattlePower is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwBattlePower") != 0)
	{
		LOG_CRI << "Attribute: name is not dwBattlePower!";
		return false;
	}
	const char* pszVal_dwBattlePower = pElemChild->Attribute("value");
	if(pszVal_dwBattlePower == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwBattlePower, s.dwBattlePower))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecOtherPlayer is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecOtherPlayer") != 0)
	{
		LOG_CRI << "pElemChild is not TVecOtherPlayer!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecOtherPlayer") != 0)
	{
		LOG_CRI << "Attribute: name is not vecOtherPlayer!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecOtherPlayer))
	{
		LOG_CRI << "VectorFromXML for vecOtherPlayer fails!";
		return false;
	}
	return true;
}

bool ToXML(const SSSBattlePairInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SSSBattlePairInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("论剑场玩家的配对信息，也是发给前端用的信息"));
	unique_ptr<TiXmlElement> pElem_byRound(new TiXmlElement("UINT8"));
	if(pElem_byRound == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byRound->SetAttribute("name", "byRound");
	pElem_byRound->SetAttribute("value", NumberToString(s.byRound).c_str());
	pElem_byRound->SetAttribute("comment", ToUTF8Ptr("当前轮次"));
	if(rElement.LinkEndChild(pElem_byRound.get()) != NULL)
		pElem_byRound.release();
	unique_ptr<TiXmlElement> pElem_wTimeLeft(new TiXmlElement("UINT16"));
	if(pElem_wTimeLeft == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wTimeLeft->SetAttribute("name", "wTimeLeft");
	pElem_wTimeLeft->SetAttribute("value", NumberToString(s.wTimeLeft).c_str());
	pElem_wTimeLeft->SetAttribute("comment", ToUTF8Ptr("距离下一场【或者开始】时间(秒)"));
	if(rElement.LinkEndChild(pElem_wTimeLeft.get()) != NULL)
		pElem_wTimeLeft.release();
	unique_ptr<TiXmlElement> pElem_byCurrKill(new TiXmlElement("UINT8"));
	if(pElem_byCurrKill == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byCurrKill->SetAttribute("name", "byCurrKill");
	pElem_byCurrKill->SetAttribute("value", NumberToString(s.byCurrKill).c_str());
	pElem_byCurrKill->SetAttribute("comment", ToUTF8Ptr("当前连杀数"));
	if(rElement.LinkEndChild(pElem_byCurrKill.get()) != NULL)
		pElem_byCurrKill.release();
	unique_ptr<TiXmlElement> pElem_byMaxKill(new TiXmlElement("UINT8"));
	if(pElem_byMaxKill == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byMaxKill->SetAttribute("name", "byMaxKill");
	pElem_byMaxKill->SetAttribute("value", NumberToString(s.byMaxKill).c_str());
	pElem_byMaxKill->SetAttribute("comment", ToUTF8Ptr("最高连杀数"));
	if(rElement.LinkEndChild(pElem_byMaxKill.get()) != NULL)
		pElem_byMaxKill.release();
	unique_ptr<TiXmlElement> pElem_byTotalWin(new TiXmlElement("UINT8"));
	if(pElem_byTotalWin == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byTotalWin->SetAttribute("name", "byTotalWin");
	pElem_byTotalWin->SetAttribute("value", NumberToString(s.byTotalWin).c_str());
	pElem_byTotalWin->SetAttribute("comment", ToUTF8Ptr("胜利场数"));
	if(rElement.LinkEndChild(pElem_byTotalWin.get()) != NULL)
		pElem_byTotalWin.release();
	unique_ptr<TiXmlElement> pElem_byTotalLose(new TiXmlElement("UINT8"));
	if(pElem_byTotalLose == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byTotalLose->SetAttribute("name", "byTotalLose");
	pElem_byTotalLose->SetAttribute("value", NumberToString(s.byTotalLose).c_str());
	pElem_byTotalLose->SetAttribute("comment", ToUTF8Ptr("失败场数"));
	if(rElement.LinkEndChild(pElem_byTotalLose.get()) != NULL)
		pElem_byTotalLose.release();
	unique_ptr<TiXmlElement> pElem_wHonor(new TiXmlElement("UINT16"));
	if(pElem_wHonor == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wHonor->SetAttribute("name", "wHonor");
	pElem_wHonor->SetAttribute("value", NumberToString(s.wHonor).c_str());
	pElem_wHonor->SetAttribute("comment", ToUTF8Ptr("总荣誉值"));
	if(rElement.LinkEndChild(pElem_wHonor.get()) != NULL)
		pElem_wHonor.release();
	unique_ptr<TiXmlElement> pElem_byDomineer(new TiXmlElement("UINT8"));
	if(pElem_byDomineer == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byDomineer->SetAttribute("name", "byDomineer");
	pElem_byDomineer->SetAttribute("value", NumberToString(s.byDomineer).c_str());
	pElem_byDomineer->SetAttribute("comment", ToUTF8Ptr("霸气值"));
	if(rElement.LinkEndChild(pElem_byDomineer.get()) != NULL)
		pElem_byDomineer.release();
	unique_ptr<TiXmlElement> pElem_byAnger(new TiXmlElement("UINT8"));
	if(pElem_byAnger == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byAnger->SetAttribute("name", "byAnger");
	pElem_byAnger->SetAttribute("value", NumberToString(s.byAnger).c_str());
	pElem_byAnger->SetAttribute("comment", ToUTF8Ptr("怒气值"));
	if(rElement.LinkEndChild(pElem_byAnger.get()) != NULL)
		pElem_byAnger.release();
	unique_ptr<TiXmlElement> pElem_wSkillFlags(new TiXmlElement("UINT16"));
	if(pElem_wSkillFlags == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wSkillFlags->SetAttribute("name", "wSkillFlags");
	pElem_wSkillFlags->SetAttribute("value", NumberToString(s.wSkillFlags).c_str());
	pElem_wSkillFlags->SetAttribute("comment", ToUTF8Ptr("技能使用位域,对应位表示技能是否已使用(低8位)"));
	if(rElement.LinkEndChild(pElem_wSkillFlags.get()) != NULL)
		pElem_wSkillFlags.release();
	unique_ptr<TiXmlElement> pElem_vecTaskData(new TiXmlElement("TVecTaskData"));
	if(pElem_vecTaskData == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecTaskData->SetAttribute("name", "vecTaskData");
	if(!VectorToXML(s.vecTaskData, *pElem_vecTaskData))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecTaskData->SetAttribute("comment", ToUTF8Ptr("任务数据vec"));
	if(rElement.LinkEndChild(pElem_vecTaskData.get()) != NULL)
		pElem_vecTaskData.release();
	unique_ptr<TiXmlElement> pElem_dwMaxHp(new TiXmlElement("UINT32"));
	if(pElem_dwMaxHp == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwMaxHp->SetAttribute("name", "dwMaxHp");
	pElem_dwMaxHp->SetAttribute("value", NumberToString(s.dwMaxHp).c_str());
	pElem_dwMaxHp->SetAttribute("comment", ToUTF8Ptr("自己总血量"));
	if(rElement.LinkEndChild(pElem_dwMaxHp.get()) != NULL)
		pElem_dwMaxHp.release();
	unique_ptr<TiXmlElement> pElem_dwCurHp(new TiXmlElement("UINT32"));
	if(pElem_dwCurHp == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwCurHp->SetAttribute("name", "dwCurHp");
	pElem_dwCurHp->SetAttribute("value", NumberToString(s.dwCurHp).c_str());
	pElem_dwCurHp->SetAttribute("comment", ToUTF8Ptr("自己当前血量"));
	if(rElement.LinkEndChild(pElem_dwCurHp.get()) != NULL)
		pElem_dwCurHp.release();
	unique_ptr<TiXmlElement> pElem_dwBattlePower(new TiXmlElement("UINT32"));
	if(pElem_dwBattlePower == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwBattlePower->SetAttribute("name", "dwBattlePower");
	pElem_dwBattlePower->SetAttribute("value", NumberToString(s.dwBattlePower).c_str());
	pElem_dwBattlePower->SetAttribute("comment", ToUTF8Ptr("自己总战斗力"));
	if(rElement.LinkEndChild(pElem_dwBattlePower.get()) != NULL)
		pElem_dwBattlePower.release();
	unique_ptr<TiXmlElement> pElem_vecOtherPlayer(new TiXmlElement("TVecOtherPlayer"));
	if(pElem_vecOtherPlayer == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecOtherPlayer->SetAttribute("name", "vecOtherPlayer");
	if(!VectorToXML(s.vecOtherPlayer, *pElem_vecOtherPlayer))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecOtherPlayer->SetAttribute("comment", ToUTF8Ptr("对方玩家数据"));
	if(rElement.LinkEndChild(pElem_vecOtherPlayer.get()) != NULL)
		pElem_vecOtherPlayer.release();
	return true;
}

#endif

SSSBattleUseSkill::SSSBattleUseSkill() : qwRoleID(0), wHonor(0), wSkillFlags(0), dwCurHp(0) { }

SSSBattleUseSkill::SSSBattleUseSkill(UINT64 qwRoleID_, UINT16 wHonor_, UINT16 wSkillFlags_, UINT32 dwCurHp_) : qwRoleID(qwRoleID_), wHonor(wHonor_), wSkillFlags(wSkillFlags_), dwCurHp(dwCurHp_) { }

CInArchive& operator>>(CInArchive& src, SSSBattleUseSkill& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwRoleID;
	src >> s.wHonor;
	src >> s.wSkillFlags;
	src >> s.dwCurHp;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SSSBattleUseSkill& s)
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
	src << s.wHonor;
	src << s.wSkillFlags;
	src << s.dwCurHp;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SSSBattleUseSkill& s)
{
	if(strcmp(rElement.Value(), "SSSBattleUseSkill") != 0)
	{
		LOG_CRI << "rElement is not SSSBattleUseSkill!";
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
		LOG_CRI << "pElemChild for wHonor is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wHonor") != 0)
	{
		LOG_CRI << "Attribute: name is not wHonor!";
		return false;
	}
	const char* pszVal_wHonor = pElemChild->Attribute("value");
	if(pszVal_wHonor == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wHonor, s.wHonor))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wSkillFlags is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wSkillFlags") != 0)
	{
		LOG_CRI << "Attribute: name is not wSkillFlags!";
		return false;
	}
	const char* pszVal_wSkillFlags = pElemChild->Attribute("value");
	if(pszVal_wSkillFlags == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wSkillFlags, s.wSkillFlags))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwCurHp is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwCurHp") != 0)
	{
		LOG_CRI << "Attribute: name is not dwCurHp!";
		return false;
	}
	const char* pszVal_dwCurHp = pElemChild->Attribute("value");
	if(pszVal_dwCurHp == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwCurHp, s.dwCurHp))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SSSBattleUseSkill& s, TiXmlElement& rElement)
{
	rElement.SetValue("SSSBattleUseSkill");
	rElement.SetAttribute("type", ToUTF8Ptr("蜀山论剑场玩家使用技能返回的数据结构"));
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
	unique_ptr<TiXmlElement> pElem_wHonor(new TiXmlElement("UINT16"));
	if(pElem_wHonor == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wHonor->SetAttribute("name", "wHonor");
	pElem_wHonor->SetAttribute("value", NumberToString(s.wHonor).c_str());
	pElem_wHonor->SetAttribute("comment", ToUTF8Ptr("总荣誉值"));
	if(rElement.LinkEndChild(pElem_wHonor.get()) != NULL)
		pElem_wHonor.release();
	unique_ptr<TiXmlElement> pElem_wSkillFlags(new TiXmlElement("UINT16"));
	if(pElem_wSkillFlags == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wSkillFlags->SetAttribute("name", "wSkillFlags");
	pElem_wSkillFlags->SetAttribute("value", NumberToString(s.wSkillFlags).c_str());
	pElem_wSkillFlags->SetAttribute("comment", ToUTF8Ptr("技能使用位域,对应位表示技能是否已使用(低8位)"));
	if(rElement.LinkEndChild(pElem_wSkillFlags.get()) != NULL)
		pElem_wSkillFlags.release();
	unique_ptr<TiXmlElement> pElem_dwCurHp(new TiXmlElement("UINT32"));
	if(pElem_dwCurHp == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwCurHp->SetAttribute("name", "dwCurHp");
	pElem_dwCurHp->SetAttribute("value", NumberToString(s.dwCurHp).c_str());
	pElem_dwCurHp->SetAttribute("comment", ToUTF8Ptr("当前血量"));
	if(rElement.LinkEndChild(pElem_dwCurHp.get()) != NULL)
		pElem_dwCurHp.release();
	return true;
}

#endif

} //namespace NShushanBattleProt
