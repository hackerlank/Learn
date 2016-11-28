/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    Game2CenterDemonTower.cpp
//  Purpose:      GameServer到CenterServer关于镇妖塔的通信协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "Game2CenterDemonTower.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NGame2CenterDemonTower
{

SDemonTowerEnterPlayer::SDemonTowerEnterPlayer() : qwUserID(0), qwRoleID(0), dwFloorID(0), bySex(0), byLevel(0), 
			dwCareer(0), dwPower(0) { }

SDemonTowerEnterPlayer::SDemonTowerEnterPlayer(UINT64 qwUserID_, UINT64 qwRoleID_, const std::string& strName_, UINT32 dwFloorID_, UINT8 bySex_, 
			UINT16 byLevel_, UINT32 dwCareer_, UINT32 dwPower_)
			: qwUserID(qwUserID_), qwRoleID(qwRoleID_), strName(strName_), dwFloorID(dwFloorID_), bySex(bySex_), 
			byLevel(byLevel_), dwCareer(dwCareer_), dwPower(dwPower_) { }

SDemonTowerEnterPlayer::SDemonTowerEnterPlayer(SDemonTowerEnterPlayer&& src) : qwUserID(src.qwUserID), qwRoleID(src.qwRoleID), strName(move(src.strName)), dwFloorID(src.dwFloorID), bySex(src.bySex), 
			byLevel(src.byLevel), dwCareer(src.dwCareer), dwPower(src.dwPower) { }

SDemonTowerEnterPlayer& SDemonTowerEnterPlayer::operator=(SDemonTowerEnterPlayer&& rhs)
{
	if(this != &rhs)
	{
		this->~SDemonTowerEnterPlayer();
		new (this) SDemonTowerEnterPlayer(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SDemonTowerEnterPlayer& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwUserID;
	src >> s.qwRoleID;
	src >> s.strName;
	src >> s.dwFloorID;
	src >> s.bySex;
	src >> s.byLevel;
	src >> s.dwCareer;
	src >> s.dwPower;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SDemonTowerEnterPlayer& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.qwUserID;
	src << s.qwRoleID;
	src << s.strName;
	src << s.dwFloorID;
	src << s.bySex;
	src << s.byLevel;
	src << s.dwCareer;
	src << s.dwPower;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SDemonTowerEnterPlayer& s)
{
	if(strcmp(rElement.Value(), "SDemonTowerEnterPlayer") != 0)
	{
		LOG_CRI << "rElement is not SDemonTowerEnterPlayer!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwUserID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwUserID") != 0)
	{
		LOG_CRI << "Attribute: name is not qwUserID!";
		return false;
	}
	const char* pszVal_qwUserID = pElemChild->Attribute("value");
	if(pszVal_qwUserID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwUserID, s.qwUserID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
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
		LOG_CRI << "pElemChild for dwFloorID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwFloorID") != 0)
	{
		LOG_CRI << "Attribute: name is not dwFloorID!";
		return false;
	}
	const char* pszVal_dwFloorID = pElemChild->Attribute("value");
	if(pszVal_dwFloorID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwFloorID, s.dwFloorID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for bySex is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "bySex") != 0)
	{
		LOG_CRI << "Attribute: name is not bySex!";
		return false;
	}
	const char* pszVal_bySex = pElemChild->Attribute("value");
	if(pszVal_bySex == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_bySex, s.bySex))
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
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
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
		LOG_CRI << "pElemChild for dwCareer is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwCareer") != 0)
	{
		LOG_CRI << "Attribute: name is not dwCareer!";
		return false;
	}
	const char* pszVal_dwCareer = pElemChild->Attribute("value");
	if(pszVal_dwCareer == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwCareer, s.dwCareer))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwPower is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwPower") != 0)
	{
		LOG_CRI << "Attribute: name is not dwPower!";
		return false;
	}
	const char* pszVal_dwPower = pElemChild->Attribute("value");
	if(pszVal_dwPower == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwPower, s.dwPower))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SDemonTowerEnterPlayer& s, TiXmlElement& rElement)
{
	rElement.SetValue("SDemonTowerEnterPlayer");
	rElement.SetAttribute("type", ToUTF8Ptr("进入镇妖塔玩家信息"));
	unique_ptr<TiXmlElement> pElem_qwUserID(new TiXmlElement("UINT64"));
	if(pElem_qwUserID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwUserID->SetAttribute("name", "qwUserID");
	pElem_qwUserID->SetAttribute("value", NumberToString(s.qwUserID).c_str());
	pElem_qwUserID->SetAttribute("comment", ToUTF8Ptr("账号Id"));
	if(rElement.LinkEndChild(pElem_qwUserID.get()) != NULL)
		pElem_qwUserID.release();
	unique_ptr<TiXmlElement> pElem_qwRoleID(new TiXmlElement("UINT64"));
	if(pElem_qwRoleID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwRoleID->SetAttribute("name", "qwRoleID");
	pElem_qwRoleID->SetAttribute("value", NumberToString(s.qwRoleID).c_str());
	pElem_qwRoleID->SetAttribute("comment", ToUTF8Ptr("角色Id"));
	if(rElement.LinkEndChild(pElem_qwRoleID.get()) != NULL)
		pElem_qwRoleID.release();
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
	unique_ptr<TiXmlElement> pElem_dwFloorID(new TiXmlElement("UINT32"));
	if(pElem_dwFloorID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwFloorID->SetAttribute("name", "dwFloorID");
	pElem_dwFloorID->SetAttribute("value", NumberToString(s.dwFloorID).c_str());
	pElem_dwFloorID->SetAttribute("comment", ToUTF8Ptr("楼层"));
	if(rElement.LinkEndChild(pElem_dwFloorID.get()) != NULL)
		pElem_dwFloorID.release();
	unique_ptr<TiXmlElement> pElem_bySex(new TiXmlElement("UINT8"));
	if(pElem_bySex == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_bySex->SetAttribute("name", "bySex");
	pElem_bySex->SetAttribute("value", NumberToString(s.bySex).c_str());
	pElem_bySex->SetAttribute("comment", ToUTF8Ptr("性别"));
	if(rElement.LinkEndChild(pElem_bySex.get()) != NULL)
		pElem_bySex.release();
	unique_ptr<TiXmlElement> pElem_byLevel(new TiXmlElement("UINT16"));
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
	unique_ptr<TiXmlElement> pElem_dwCareer(new TiXmlElement("UINT32"));
	if(pElem_dwCareer == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwCareer->SetAttribute("name", "dwCareer");
	pElem_dwCareer->SetAttribute("value", NumberToString(s.dwCareer).c_str());
	pElem_dwCareer->SetAttribute("comment", ToUTF8Ptr("职业"));
	if(rElement.LinkEndChild(pElem_dwCareer.get()) != NULL)
		pElem_dwCareer.release();
	unique_ptr<TiXmlElement> pElem_dwPower(new TiXmlElement("UINT32"));
	if(pElem_dwPower == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwPower->SetAttribute("name", "dwPower");
	pElem_dwPower->SetAttribute("value", NumberToString(s.dwPower).c_str());
	pElem_dwPower->SetAttribute("comment", ToUTF8Ptr("战斗力"));
	if(rElement.LinkEndChild(pElem_dwPower.get()) != NULL)
		pElem_dwPower.release();
	return true;
}

#endif

SDemonTowerPassPlayer::SDemonTowerPassPlayer() : dwCurFloorID(0), qwUserID(0), dwPower(0), wTurns(0), qwReportID(0) { }

SDemonTowerPassPlayer::SDemonTowerPassPlayer(UINT32 dwCurFloorID_, UINT64 qwUserID_, UINT32 dwPower_, UINT16 wTurns_, UINT64 qwReportID_)
			: dwCurFloorID(dwCurFloorID_), qwUserID(qwUserID_), dwPower(dwPower_), wTurns(wTurns_), qwReportID(qwReportID_) { }

CInArchive& operator>>(CInArchive& src, SDemonTowerPassPlayer& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.dwCurFloorID;
	src >> s.qwUserID;
	src >> s.dwPower;
	src >> s.wTurns;
	src >> s.qwReportID;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SDemonTowerPassPlayer& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.dwCurFloorID;
	src << s.qwUserID;
	src << s.dwPower;
	src << s.wTurns;
	src << s.qwReportID;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SDemonTowerPassPlayer& s)
{
	if(strcmp(rElement.Value(), "SDemonTowerPassPlayer") != 0)
	{
		LOG_CRI << "rElement is not SDemonTowerPassPlayer!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwCurFloorID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwCurFloorID") != 0)
	{
		LOG_CRI << "Attribute: name is not dwCurFloorID!";
		return false;
	}
	const char* pszVal_dwCurFloorID = pElemChild->Attribute("value");
	if(pszVal_dwCurFloorID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwCurFloorID, s.dwCurFloorID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwUserID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwUserID") != 0)
	{
		LOG_CRI << "Attribute: name is not qwUserID!";
		return false;
	}
	const char* pszVal_qwUserID = pElemChild->Attribute("value");
	if(pszVal_qwUserID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwUserID, s.qwUserID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwPower is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwPower") != 0)
	{
		LOG_CRI << "Attribute: name is not dwPower!";
		return false;
	}
	const char* pszVal_dwPower = pElemChild->Attribute("value");
	if(pszVal_dwPower == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwPower, s.dwPower))
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
		LOG_CRI << "pElemChild for qwReportID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwReportID") != 0)
	{
		LOG_CRI << "Attribute: name is not qwReportID!";
		return false;
	}
	const char* pszVal_qwReportID = pElemChild->Attribute("value");
	if(pszVal_qwReportID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwReportID, s.qwReportID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SDemonTowerPassPlayer& s, TiXmlElement& rElement)
{
	rElement.SetValue("SDemonTowerPassPlayer");
	rElement.SetAttribute("type", ToUTF8Ptr("镇妖塔玩家击败怪物信息"));
	unique_ptr<TiXmlElement> pElem_dwCurFloorID(new TiXmlElement("UINT32"));
	if(pElem_dwCurFloorID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwCurFloorID->SetAttribute("name", "dwCurFloorID");
	pElem_dwCurFloorID->SetAttribute("value", NumberToString(s.dwCurFloorID).c_str());
	pElem_dwCurFloorID->SetAttribute("comment", ToUTF8Ptr("当前楼层"));
	if(rElement.LinkEndChild(pElem_dwCurFloorID.get()) != NULL)
		pElem_dwCurFloorID.release();
	unique_ptr<TiXmlElement> pElem_qwUserID(new TiXmlElement("UINT64"));
	if(pElem_qwUserID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwUserID->SetAttribute("name", "qwUserID");
	pElem_qwUserID->SetAttribute("value", NumberToString(s.qwUserID).c_str());
	pElem_qwUserID->SetAttribute("comment", ToUTF8Ptr("账号Id"));
	if(rElement.LinkEndChild(pElem_qwUserID.get()) != NULL)
		pElem_qwUserID.release();
	unique_ptr<TiXmlElement> pElem_dwPower(new TiXmlElement("UINT32"));
	if(pElem_dwPower == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwPower->SetAttribute("name", "dwPower");
	pElem_dwPower->SetAttribute("value", NumberToString(s.dwPower).c_str());
	pElem_dwPower->SetAttribute("comment", ToUTF8Ptr("战斗力"));
	if(rElement.LinkEndChild(pElem_dwPower.get()) != NULL)
		pElem_dwPower.release();
	unique_ptr<TiXmlElement> pElem_wTurns(new TiXmlElement("UINT16"));
	if(pElem_wTurns == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wTurns->SetAttribute("name", "wTurns");
	pElem_wTurns->SetAttribute("value", NumberToString(s.wTurns).c_str());
	pElem_wTurns->SetAttribute("comment", ToUTF8Ptr("回合数"));
	if(rElement.LinkEndChild(pElem_wTurns.get()) != NULL)
		pElem_wTurns.release();
	unique_ptr<TiXmlElement> pElem_qwReportID(new TiXmlElement("UINT64"));
	if(pElem_qwReportID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwReportID->SetAttribute("name", "qwReportID");
	pElem_qwReportID->SetAttribute("value", NumberToString(s.qwReportID).c_str());
	pElem_qwReportID->SetAttribute("comment", ToUTF8Ptr("战报id"));
	if(rElement.LinkEndChild(pElem_qwReportID.get()) != NULL)
		pElem_qwReportID.release();
	return true;
}

#endif

} //namespace NGame2CenterDemonTower
