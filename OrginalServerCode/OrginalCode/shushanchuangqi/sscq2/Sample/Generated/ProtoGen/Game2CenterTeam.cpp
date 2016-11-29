/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    Game2CenterTeam.cpp
//  Purpose:      GameServer到CenterServer关于Team的通信协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "Game2CenterTeam.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NGame2CenterTeam
{

#ifdef PROT_USE_XML

const char* EnumValToStr(EPlayerTeam e)
{
	switch(e)
	{
	case EPlayerEnterTeam:
		return "EPlayerEnterTeam";
	case EPlayerLeaveTeam:
		return "EPlayerLeaveTeam";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EPlayerTeam& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EPlayerTeam> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("EPlayerEnterTeam", EPlayerEnterTeam));
		mapStr2Val.insert(make_pair("EPlayerLeaveTeam", EPlayerLeaveTeam));
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

BattleReport::BattleReport() : qwBattleID(0), wMonsterGroup(0), bySuc(0) { }

BattleReport::BattleReport(UINT64 qwBattleID_, const std::string& strBattle_, UINT16 wMonsterGroup_, UINT8 bySuc_) : qwBattleID(qwBattleID_), strBattle(strBattle_), wMonsterGroup(wMonsterGroup_), bySuc(bySuc_) { }

BattleReport::BattleReport(BattleReport&& src) : qwBattleID(src.qwBattleID), strBattle(move(src.strBattle)), wMonsterGroup(src.wMonsterGroup), bySuc(src.bySuc) { }

BattleReport& BattleReport::operator=(BattleReport&& rhs)
{
	if(this != &rhs)
	{
		this->~BattleReport();
		new (this) BattleReport(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, BattleReport& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwBattleID;
	src >> s.strBattle;
	src >> s.wMonsterGroup;
	src >> s.bySuc;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const BattleReport& s)
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
	src << s.strBattle;
	src << s.wMonsterGroup;
	src << s.bySuc;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, BattleReport& s)
{
	if(strcmp(rElement.Value(), "BattleReport") != 0)
	{
		LOG_CRI << "rElement is not BattleReport!";
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
		LOG_CRI << "pElemChild for strBattle is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strBattle") != 0)
	{
		LOG_CRI << "Attribute: name is not strBattle!";
		return false;
	}
	const char* pszVal_strBattle = pElemChild->Attribute("value");
	if(pszVal_strBattle == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strBattle = pszVal_strBattle;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wMonsterGroup is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wMonsterGroup") != 0)
	{
		LOG_CRI << "Attribute: name is not wMonsterGroup!";
		return false;
	}
	const char* pszVal_wMonsterGroup = pElemChild->Attribute("value");
	if(pszVal_wMonsterGroup == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wMonsterGroup, s.wMonsterGroup))
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
	return true;
}

bool ToXML(const BattleReport& s, TiXmlElement& rElement)
{
	rElement.SetValue("BattleReport");
	rElement.SetAttribute("type", ToUTF8Ptr("一个战报"));
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
	unique_ptr<TiXmlElement> pElem_strBattle(new TiXmlElement("string"));
	if(pElem_strBattle == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strBattle->SetAttribute("name", "strBattle");
	pElem_strBattle->SetAttribute("value", s.strBattle.c_str());
	pElem_strBattle->SetAttribute("comment", ToUTF8Ptr("战报"));
	if(rElement.LinkEndChild(pElem_strBattle.get()) != NULL)
		pElem_strBattle.release();
	unique_ptr<TiXmlElement> pElem_wMonsterGroup(new TiXmlElement("UINT16"));
	if(pElem_wMonsterGroup == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wMonsterGroup->SetAttribute("name", "wMonsterGroup");
	pElem_wMonsterGroup->SetAttribute("value", NumberToString(s.wMonsterGroup).c_str());
	pElem_wMonsterGroup->SetAttribute("comment", ToUTF8Ptr("怪物组"));
	if(rElement.LinkEndChild(pElem_wMonsterGroup.get()) != NULL)
		pElem_wMonsterGroup.release();
	unique_ptr<TiXmlElement> pElem_bySuc(new TiXmlElement("UINT8"));
	if(pElem_bySuc == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_bySuc->SetAttribute("name", "bySuc");
	pElem_bySuc->SetAttribute("value", NumberToString(s.bySuc).c_str());
	pElem_bySuc->SetAttribute("comment", ToUTF8Ptr("是否胜利"));
	if(rElement.LinkEndChild(pElem_bySuc.get()) != NULL)
		pElem_bySuc.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecBattleReport& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		BattleReport s;
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

bool VectorToXML(const TVecBattleReport& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("BattleReport"));
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

TeamReport::TeamReport() : bySuc(0), wTurns(0), qwLeaderID(0), qwLeaderFighter(0) { }

TeamReport::TeamReport(const TVecBattleReport& vecReport_, UINT8 bySuc_, UINT16 wTurns_, UINT64 qwLeaderID_, UINT64 qwLeaderFighter_)
			: vecReport(vecReport_), bySuc(bySuc_), wTurns(wTurns_), qwLeaderID(qwLeaderID_), qwLeaderFighter(qwLeaderFighter_) { }

TeamReport::TeamReport(TeamReport&& src) : vecReport(move(src.vecReport)), bySuc(src.bySuc), wTurns(src.wTurns), qwLeaderID(src.qwLeaderID), qwLeaderFighter(src.qwLeaderFighter) { }

TeamReport& TeamReport::operator=(TeamReport&& rhs)
{
	if(this != &rhs)
	{
		this->~TeamReport();
		new (this) TeamReport(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, TeamReport& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.vecReport;
	src >> s.bySuc;
	src >> s.wTurns;
	src >> s.qwLeaderID;
	src >> s.qwLeaderFighter;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TeamReport& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.vecReport;
	src << s.bySuc;
	src << s.wTurns;
	src << s.qwLeaderID;
	src << s.qwLeaderFighter;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, TeamReport& s)
{
	if(strcmp(rElement.Value(), "TeamReport") != 0)
	{
		LOG_CRI << "rElement is not TeamReport!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecReport is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecBattleReport") != 0)
	{
		LOG_CRI << "pElemChild is not TVecBattleReport!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecReport") != 0)
	{
		LOG_CRI << "Attribute: name is not vecReport!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecReport))
	{
		LOG_CRI << "VectorFromXML for vecReport fails!";
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
		LOG_CRI << "pElemChild for wTurns is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wTurns") != 0)
	{
		LOG_CRI << "Attribute: name is not wTurns!";
		return false;
	}
	const char* pszVal_wTurns = pElemChild->Attribute("value");
	if(pszVal_wTurns == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wTurns, s.wTurns))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwLeaderID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwLeaderID") != 0)
	{
		LOG_CRI << "Attribute: name is not qwLeaderID!";
		return false;
	}
	const char* pszVal_qwLeaderID = pElemChild->Attribute("value");
	if(pszVal_qwLeaderID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwLeaderID, s.qwLeaderID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwLeaderFighter is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwLeaderFighter") != 0)
	{
		LOG_CRI << "Attribute: name is not qwLeaderFighter!";
		return false;
	}
	const char* pszVal_qwLeaderFighter = pElemChild->Attribute("value");
	if(pszVal_qwLeaderFighter == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwLeaderFighter, s.qwLeaderFighter))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const TeamReport& s, TiXmlElement& rElement)
{
	rElement.SetValue("TeamReport");
	rElement.SetAttribute("type", ToUTF8Ptr("一场战斗结果"));
	unique_ptr<TiXmlElement> pElem_vecReport(new TiXmlElement("TVecBattleReport"));
	if(pElem_vecReport == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecReport->SetAttribute("name", "vecReport");
	if(!VectorToXML(s.vecReport, *pElem_vecReport))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecReport->SetAttribute("comment", ToUTF8Ptr("战报序列"));
	if(rElement.LinkEndChild(pElem_vecReport.get()) != NULL)
		pElem_vecReport.release();
	unique_ptr<TiXmlElement> pElem_bySuc(new TiXmlElement("UINT8"));
	if(pElem_bySuc == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_bySuc->SetAttribute("name", "bySuc");
	pElem_bySuc->SetAttribute("value", NumberToString(s.bySuc).c_str());
	pElem_bySuc->SetAttribute("comment", ToUTF8Ptr("是否胜利"));
	if(rElement.LinkEndChild(pElem_bySuc.get()) != NULL)
		pElem_bySuc.release();
	unique_ptr<TiXmlElement> pElem_wTurns(new TiXmlElement("UINT16"));
	if(pElem_wTurns == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wTurns->SetAttribute("name", "wTurns");
	pElem_wTurns->SetAttribute("value", NumberToString(s.wTurns).c_str());
	pElem_wTurns->SetAttribute("comment", ToUTF8Ptr("总回合数"));
	if(rElement.LinkEndChild(pElem_wTurns.get()) != NULL)
		pElem_wTurns.release();
	unique_ptr<TiXmlElement> pElem_qwLeaderID(new TiXmlElement("UINT64"));
	if(pElem_qwLeaderID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwLeaderID->SetAttribute("name", "qwLeaderID");
	pElem_qwLeaderID->SetAttribute("value", NumberToString(s.qwLeaderID).c_str());
	pElem_qwLeaderID->SetAttribute("comment", ToUTF8Ptr("队长ID"));
	if(rElement.LinkEndChild(pElem_qwLeaderID.get()) != NULL)
		pElem_qwLeaderID.release();
	unique_ptr<TiXmlElement> pElem_qwLeaderFighter(new TiXmlElement("UINT64"));
	if(pElem_qwLeaderFighter == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwLeaderFighter->SetAttribute("name", "qwLeaderFighter");
	pElem_qwLeaderFighter->SetAttribute("value", NumberToString(s.qwLeaderFighter).c_str());
	pElem_qwLeaderFighter->SetAttribute("comment", ToUTF8Ptr("队长主将"));
	if(rElement.LinkEndChild(pElem_qwLeaderFighter.get()) != NULL)
		pElem_qwLeaderFighter.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecTeamReport& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		TeamReport s;
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

bool VectorToXML(const TVecTeamReport& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("TeamReport"));
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

} //namespace NGame2CenterTeam
