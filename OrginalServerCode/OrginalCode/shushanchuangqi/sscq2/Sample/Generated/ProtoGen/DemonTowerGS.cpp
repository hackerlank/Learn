/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    DemonTowerGS.cpp
//  Purpose:      锁妖塔
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "DemonTowerGS.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NDemonTowerGS
{

#ifdef PROT_USE_XML

const char* EnumValToStr(EDemonTower e)
{
	switch(e)
	{
	case eDemonTower_Sucess:
		return "eDemonTower_Sucess";
	case eDemonTower_Error:
		return "eDemonTower_Error";
	case eDemonTower_NotPass:
		return "eDemonTower_NotPass";
	case eDemonTower_NotInTower:
		return "eDemonTower_NotInTower";
	case eDemonTower_Invalid_CFG:
		return "eDemonTower_Invalid_CFG";
	case eDemonTower_Invalid_FloorID:
		return "eDemonTower_Invalid_FloorID";
	case eDemonTower_Invalid_Positoin:
		return "eDemonTower_Invalid_Positoin";
	case eDemonTower_Not_Empty_Positoin:
		return "eDemonTower_Not_Empty_Positoin";
	case eDemonTower_Empty_Positoin:
		return "eDemonTower_Empty_Positoin";
	case eDemonTower_Empty_Prize:
		return "eDemonTower_Empty_Prize";
	case eDemonTower_Invalid_PrizeType:
		return "eDemonTower_Invalid_PrizeType";
	case eDemonTower_Invalid_UserID:
		return "eDemonTower_Invalid_UserID";
	case eDemonTower_FightCD:
		return "eDemonTower_FightCD";
	case eDemonTower_LackMoney:
		return "eDemonTower_LackMoney";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EDemonTower& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EDemonTower> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eDemonTower_Sucess", eDemonTower_Sucess));
		mapStr2Val.insert(make_pair("eDemonTower_Error", eDemonTower_Error));
		mapStr2Val.insert(make_pair("eDemonTower_NotPass", eDemonTower_NotPass));
		mapStr2Val.insert(make_pair("eDemonTower_NotInTower", eDemonTower_NotInTower));
		mapStr2Val.insert(make_pair("eDemonTower_Invalid_CFG", eDemonTower_Invalid_CFG));
		mapStr2Val.insert(make_pair("eDemonTower_Invalid_FloorID", eDemonTower_Invalid_FloorID));
		mapStr2Val.insert(make_pair("eDemonTower_Invalid_Positoin", eDemonTower_Invalid_Positoin));
		mapStr2Val.insert(make_pair("eDemonTower_Not_Empty_Positoin", eDemonTower_Not_Empty_Positoin));
		mapStr2Val.insert(make_pair("eDemonTower_Empty_Positoin", eDemonTower_Empty_Positoin));
		mapStr2Val.insert(make_pair("eDemonTower_Empty_Prize", eDemonTower_Empty_Prize));
		mapStr2Val.insert(make_pair("eDemonTower_Invalid_PrizeType", eDemonTower_Invalid_PrizeType));
		mapStr2Val.insert(make_pair("eDemonTower_Invalid_UserID", eDemonTower_Invalid_UserID));
		mapStr2Val.insert(make_pair("eDemonTower_FightCD", eDemonTower_FightCD));
		mapStr2Val.insert(make_pair("eDemonTower_LackMoney", eDemonTower_LackMoney));
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

const char* GetDescription(EDemonTower e)
{
	switch(e)
	{
	case eDemonTower_Sucess:
		return "成功";
	case eDemonTower_Error:
		return "锁妖塔错误码";
	case eDemonTower_NotPass:
		return "未通关层数，不能进入";
	case eDemonTower_NotInTower:
		return "不在镇妖塔中";
	case eDemonTower_Invalid_CFG:
		return "配置不存在";
	case eDemonTower_Invalid_FloorID:
		return "层数错误";
	case eDemonTower_Invalid_Positoin:
		return "镇守位置错误";
	case eDemonTower_Not_Empty_Positoin:
		return "非空镇守位置";
	case eDemonTower_Empty_Positoin:
		return "空位置没有玩家镇守";
	case eDemonTower_Empty_Prize:
		return "无奖励或奖励已经领取";
	case eDemonTower_Invalid_PrizeType:
		return "错误的领奖类型";
	case eDemonTower_Invalid_UserID:
		return "玩家不在线";
	case eDemonTower_FightCD:
		return "镇守位处在战斗状态中";
	case eDemonTower_LackMoney:
		return "钻石不足";
	default:
		return "未知错误";
	}
}

#ifdef PROT_USE_XML

const char* EnumValToStr(EDemonTowerDB e)
{
	switch(e)
	{
	case eDemonTowerDB_Add:
		return "eDemonTowerDB_Add";
	case eDemonTowerDB_Update:
		return "eDemonTowerDB_Update";
	case eDemonTowerDB_Delete:
		return "eDemonTowerDB_Delete";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EDemonTowerDB& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EDemonTowerDB> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eDemonTowerDB_Add", eDemonTowerDB_Add));
		mapStr2Val.insert(make_pair("eDemonTowerDB_Update", eDemonTowerDB_Update));
		mapStr2Val.insert(make_pair("eDemonTowerDB_Delete", eDemonTowerDB_Delete));
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

const char* GetDescription(EDemonTowerDB e)
{
	switch(e)
	{
	case eDemonTowerDB_Add:
		return "添加";
	case eDemonTowerDB_Update:
		return "更新";
	case eDemonTowerDB_Delete:
		return "删除";
	default:
		return "未知错误";
	}
}

#ifdef PROT_USE_XML

const char* EnumValToStr(EDemonTowerPrize e)
{
	switch(e)
	{
	case eDemonTower_Prize_Fail:
		return "eDemonTower_Prize_Fail";
	case eDemonTower_Prize_Day:
		return "eDemonTower_Prize_Day";
	case eDemonTower_Prize_Seal:
		return "eDemonTower_Prize_Seal";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EDemonTowerPrize& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EDemonTowerPrize> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eDemonTower_Prize_Fail", eDemonTower_Prize_Fail));
		mapStr2Val.insert(make_pair("eDemonTower_Prize_Day", eDemonTower_Prize_Day));
		mapStr2Val.insert(make_pair("eDemonTower_Prize_Seal", eDemonTower_Prize_Seal));
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

const char* GetDescription(EDemonTowerPrize e)
{
	switch(e)
	{
	case eDemonTower_Prize_Fail:
		return "镇守失败奖励";
	case eDemonTower_Prize_Day:
		return "镇守1天收益奖励";
	case eDemonTower_Prize_Seal:
		return "封印每天奖励(改成gmeserver领取)";
	default:
		return "未知错误";
	}
}

MoneyInfo::MoneyInfo() : dwMoneyType(0), dwMoneyValue(0) { }

MoneyInfo::MoneyInfo(UINT32 dwMoneyType_, UINT32 dwMoneyValue_) : dwMoneyType(dwMoneyType_), dwMoneyValue(dwMoneyValue_) { }

CInArchive& operator>>(CInArchive& src, MoneyInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.dwMoneyType;
	src >> s.dwMoneyValue;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const MoneyInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.dwMoneyType;
	src << s.dwMoneyValue;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, MoneyInfo& s)
{
	if(strcmp(rElement.Value(), "MoneyInfo") != 0)
	{
		LOG_CRI << "rElement is not MoneyInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwMoneyType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwMoneyType") != 0)
	{
		LOG_CRI << "Attribute: name is not dwMoneyType!";
		return false;
	}
	const char* pszVal_dwMoneyType = pElemChild->Attribute("value");
	if(pszVal_dwMoneyType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwMoneyType, s.dwMoneyType))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwMoneyValue is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwMoneyValue") != 0)
	{
		LOG_CRI << "Attribute: name is not dwMoneyValue!";
		return false;
	}
	const char* pszVal_dwMoneyValue = pElemChild->Attribute("value");
	if(pszVal_dwMoneyValue == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwMoneyValue, s.dwMoneyValue))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const MoneyInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("MoneyInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("钱币列表"));
	unique_ptr<TiXmlElement> pElem_dwMoneyType(new TiXmlElement("UINT32"));
	if(pElem_dwMoneyType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwMoneyType->SetAttribute("name", "dwMoneyType");
	pElem_dwMoneyType->SetAttribute("value", NumberToString(s.dwMoneyType).c_str());
	pElem_dwMoneyType->SetAttribute("comment", ToUTF8Ptr("钱币类型"));
	if(rElement.LinkEndChild(pElem_dwMoneyType.get()) != NULL)
		pElem_dwMoneyType.release();
	unique_ptr<TiXmlElement> pElem_dwMoneyValue(new TiXmlElement("UINT32"));
	if(pElem_dwMoneyValue == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwMoneyValue->SetAttribute("name", "dwMoneyValue");
	pElem_dwMoneyValue->SetAttribute("value", NumberToString(s.dwMoneyValue).c_str());
	pElem_dwMoneyValue->SetAttribute("comment", ToUTF8Ptr("钱数"));
	if(rElement.LinkEndChild(pElem_dwMoneyValue.get()) != NULL)
		pElem_dwMoneyValue.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecMoneyInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		MoneyInfo s;
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

bool VectorToXML(const TVecMoneyInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("MoneyInfo"));
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

SDemonFloorPlayer::SDemonFloorPlayer() : dwFloorID(0), qwUserID(0), bySex(0), byLevel(0), dwPower(0), 
			dwGuardStartTime(0), dwGuardReduceRate(0) { }

SDemonFloorPlayer::SDemonFloorPlayer(UINT32 dwFloorID_, UINT64 qwUserID_, const std::string& strRoleName_, UINT8 bySex_, UINT16 byLevel_, 
			UINT32 dwPower_, UINT32 dwGuardStartTime_, UINT32 dwGuardReduceRate_, const TVecMoneyInfo& vecSoulPrize_)
			: dwFloorID(dwFloorID_), qwUserID(qwUserID_), strRoleName(strRoleName_), bySex(bySex_), byLevel(byLevel_), 
			dwPower(dwPower_), dwGuardStartTime(dwGuardStartTime_), dwGuardReduceRate(dwGuardReduceRate_), vecSoulPrize(vecSoulPrize_) { }

SDemonFloorPlayer::SDemonFloorPlayer(SDemonFloorPlayer&& src) : dwFloorID(src.dwFloorID), qwUserID(src.qwUserID), strRoleName(move(src.strRoleName)), bySex(src.bySex), byLevel(src.byLevel), 
			dwPower(src.dwPower), dwGuardStartTime(src.dwGuardStartTime), dwGuardReduceRate(src.dwGuardReduceRate), vecSoulPrize(move(src.vecSoulPrize)) { }

SDemonFloorPlayer& SDemonFloorPlayer::operator=(SDemonFloorPlayer&& rhs)
{
	if(this != &rhs)
	{
		this->~SDemonFloorPlayer();
		new (this) SDemonFloorPlayer(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SDemonFloorPlayer& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.dwFloorID;
	src >> s.qwUserID;
	src >> s.strRoleName;
	src >> s.bySex;
	src >> s.byLevel;
	src >> s.dwPower;
	src >> s.dwGuardStartTime;
	src >> s.dwGuardReduceRate;
	src >> s.vecSoulPrize;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SDemonFloorPlayer& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.dwFloorID;
	src << s.qwUserID;
	src << s.strRoleName;
	src << s.bySex;
	src << s.byLevel;
	src << s.dwPower;
	src << s.dwGuardStartTime;
	src << s.dwGuardReduceRate;
	src << s.vecSoulPrize;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SDemonFloorPlayer& s)
{
	if(strcmp(rElement.Value(), "SDemonFloorPlayer") != 0)
	{
		LOG_CRI << "rElement is not SDemonFloorPlayer!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
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
		LOG_CRI << "pElemChild for strRoleName is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strRoleName") != 0)
	{
		LOG_CRI << "Attribute: name is not strRoleName!";
		return false;
	}
	const char* pszVal_strRoleName = pElemChild->Attribute("value");
	if(pszVal_strRoleName == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strRoleName = pszVal_strRoleName;
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
		LOG_CRI << "pElemChild for dwGuardStartTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwGuardStartTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwGuardStartTime!";
		return false;
	}
	const char* pszVal_dwGuardStartTime = pElemChild->Attribute("value");
	if(pszVal_dwGuardStartTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwGuardStartTime, s.dwGuardStartTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwGuardReduceRate is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwGuardReduceRate") != 0)
	{
		LOG_CRI << "Attribute: name is not dwGuardReduceRate!";
		return false;
	}
	const char* pszVal_dwGuardReduceRate = pElemChild->Attribute("value");
	if(pszVal_dwGuardReduceRate == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwGuardReduceRate, s.dwGuardReduceRate))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecSoulPrize is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecMoneyInfo") != 0)
	{
		LOG_CRI << "pElemChild is not TVecMoneyInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecSoulPrize") != 0)
	{
		LOG_CRI << "Attribute: name is not vecSoulPrize!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecSoulPrize))
	{
		LOG_CRI << "VectorFromXML for vecSoulPrize fails!";
		return false;
	}
	return true;
}

bool ToXML(const SDemonFloorPlayer& s, TiXmlElement& rElement)
{
	rElement.SetValue("SDemonFloorPlayer");
	rElement.SetAttribute("type", ToUTF8Ptr("镇守层的玩家信息"));
	unique_ptr<TiXmlElement> pElem_dwFloorID(new TiXmlElement("UINT32"));
	if(pElem_dwFloorID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwFloorID->SetAttribute("name", "dwFloorID");
	pElem_dwFloorID->SetAttribute("value", NumberToString(s.dwFloorID).c_str());
	pElem_dwFloorID->SetAttribute("comment", ToUTF8Ptr("当前所在塔层"));
	if(rElement.LinkEndChild(pElem_dwFloorID.get()) != NULL)
		pElem_dwFloorID.release();
	unique_ptr<TiXmlElement> pElem_qwUserID(new TiXmlElement("UINT64"));
	if(pElem_qwUserID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwUserID->SetAttribute("name", "qwUserID");
	pElem_qwUserID->SetAttribute("value", NumberToString(s.qwUserID).c_str());
	pElem_qwUserID->SetAttribute("comment", ToUTF8Ptr("uid"));
	if(rElement.LinkEndChild(pElem_qwUserID.get()) != NULL)
		pElem_qwUserID.release();
	unique_ptr<TiXmlElement> pElem_strRoleName(new TiXmlElement("string"));
	if(pElem_strRoleName == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strRoleName->SetAttribute("name", "strRoleName");
	pElem_strRoleName->SetAttribute("value", s.strRoleName.c_str());
	pElem_strRoleName->SetAttribute("comment", ToUTF8Ptr("角色名"));
	if(rElement.LinkEndChild(pElem_strRoleName.get()) != NULL)
		pElem_strRoleName.release();
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
	unique_ptr<TiXmlElement> pElem_dwGuardStartTime(new TiXmlElement("UINT32"));
	if(pElem_dwGuardStartTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwGuardStartTime->SetAttribute("name", "dwGuardStartTime");
	pElem_dwGuardStartTime->SetAttribute("value", NumberToString(s.dwGuardStartTime).c_str());
	pElem_dwGuardStartTime->SetAttribute("comment", ToUTF8Ptr("镇守开始时间"));
	if(rElement.LinkEndChild(pElem_dwGuardStartTime.get()) != NULL)
		pElem_dwGuardStartTime.release();
	unique_ptr<TiXmlElement> pElem_dwGuardReduceRate(new TiXmlElement("UINT32"));
	if(pElem_dwGuardReduceRate == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwGuardReduceRate->SetAttribute("name", "dwGuardReduceRate");
	pElem_dwGuardReduceRate->SetAttribute("value", NumberToString(s.dwGuardReduceRate).c_str());
	pElem_dwGuardReduceRate->SetAttribute("comment", ToUTF8Ptr("减弱比例(百分比1为%1)"));
	if(rElement.LinkEndChild(pElem_dwGuardReduceRate.get()) != NULL)
		pElem_dwGuardReduceRate.release();
	unique_ptr<TiXmlElement> pElem_vecSoulPrize(new TiXmlElement("TVecMoneyInfo"));
	if(pElem_vecSoulPrize == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecSoulPrize->SetAttribute("name", "vecSoulPrize");
	if(!VectorToXML(s.vecSoulPrize, *pElem_vecSoulPrize))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecSoulPrize->SetAttribute("comment", ToUTF8Ptr("当前获得魄奖励"));
	if(rElement.LinkEndChild(pElem_vecSoulPrize.get()) != NULL)
		pElem_vecSoulPrize.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecDemonFloorPlayer& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SDemonFloorPlayer s;
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

bool VectorToXML(const TVecDemonFloorPlayer& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SDemonFloorPlayer"));
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

SDemonFloorPage::SDemonFloorPage() : wCurPage(0), wMaxPage(0) { }

SDemonFloorPage::SDemonFloorPage(UINT16 wCurPage_, UINT16 wMaxPage_, const TVecDemonFloorPlayer& vecDemonFloorPlayer_) : wCurPage(wCurPage_), wMaxPage(wMaxPage_), vecDemonFloorPlayer(vecDemonFloorPlayer_) { }

SDemonFloorPage::SDemonFloorPage(SDemonFloorPage&& src) : wCurPage(src.wCurPage), wMaxPage(src.wMaxPage), vecDemonFloorPlayer(move(src.vecDemonFloorPlayer)) { }

SDemonFloorPage& SDemonFloorPage::operator=(SDemonFloorPage&& rhs)
{
	if(this != &rhs)
	{
		this->~SDemonFloorPage();
		new (this) SDemonFloorPage(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SDemonFloorPage& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.wCurPage;
	src >> s.wMaxPage;
	src >> s.vecDemonFloorPlayer;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SDemonFloorPage& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.wCurPage;
	src << s.wMaxPage;
	src << s.vecDemonFloorPlayer;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SDemonFloorPage& s)
{
	if(strcmp(rElement.Value(), "SDemonFloorPage") != 0)
	{
		LOG_CRI << "rElement is not SDemonFloorPage!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wCurPage is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wCurPage") != 0)
	{
		LOG_CRI << "Attribute: name is not wCurPage!";
		return false;
	}
	const char* pszVal_wCurPage = pElemChild->Attribute("value");
	if(pszVal_wCurPage == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wCurPage, s.wCurPage))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wMaxPage is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wMaxPage") != 0)
	{
		LOG_CRI << "Attribute: name is not wMaxPage!";
		return false;
	}
	const char* pszVal_wMaxPage = pElemChild->Attribute("value");
	if(pszVal_wMaxPage == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wMaxPage, s.wMaxPage))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecDemonFloorPlayer is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecDemonFloorPlayer") != 0)
	{
		LOG_CRI << "pElemChild is not TVecDemonFloorPlayer!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecDemonFloorPlayer") != 0)
	{
		LOG_CRI << "Attribute: name is not vecDemonFloorPlayer!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecDemonFloorPlayer))
	{
		LOG_CRI << "VectorFromXML for vecDemonFloorPlayer fails!";
		return false;
	}
	return true;
}

bool ToXML(const SDemonFloorPage& s, TiXmlElement& rElement)
{
	rElement.SetValue("SDemonFloorPage");
	rElement.SetAttribute("type", ToUTF8Ptr("镇守榜分页信息"));
	unique_ptr<TiXmlElement> pElem_wCurPage(new TiXmlElement("UINT16"));
	if(pElem_wCurPage == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wCurPage->SetAttribute("name", "wCurPage");
	pElem_wCurPage->SetAttribute("value", NumberToString(s.wCurPage).c_str());
	pElem_wCurPage->SetAttribute("comment", ToUTF8Ptr("当前页码"));
	if(rElement.LinkEndChild(pElem_wCurPage.get()) != NULL)
		pElem_wCurPage.release();
	unique_ptr<TiXmlElement> pElem_wMaxPage(new TiXmlElement("UINT16"));
	if(pElem_wMaxPage == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wMaxPage->SetAttribute("name", "wMaxPage");
	pElem_wMaxPage->SetAttribute("value", NumberToString(s.wMaxPage).c_str());
	pElem_wMaxPage->SetAttribute("comment", ToUTF8Ptr("最大页码"));
	if(rElement.LinkEndChild(pElem_wMaxPage.get()) != NULL)
		pElem_wMaxPage.release();
	unique_ptr<TiXmlElement> pElem_vecDemonFloorPlayer(new TiXmlElement("TVecDemonFloorPlayer"));
	if(pElem_vecDemonFloorPlayer == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecDemonFloorPlayer->SetAttribute("name", "vecDemonFloorPlayer");
	if(!VectorToXML(s.vecDemonFloorPlayer, *pElem_vecDemonFloorPlayer))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecDemonFloorPlayer->SetAttribute("comment", ToUTF8Ptr("分页信息"));
	if(rElement.LinkEndChild(pElem_vecDemonFloorPlayer.get()) != NULL)
		pElem_vecDemonFloorPlayer.release();
	return true;
}

#endif

SDemonTowerPlayer::SDemonTowerPlayer() : qwUserID(0), qwRoleID(0), bySex(0), byLevel(0), dwFloorID(0), 
			dwGuardFloorID(0), dwGuardPos(0), dwGuardStartTime(0), dwGuardEndTime(0), dwGuardNextPrizeTime(0), 
			dwGuardNextReduceRateTime(0), dwGuardGatherSpeed(0), dwGuardGatherSpeedEndTimer(0), dwGuardReduceRate(0), dwGuardNextAttackTime(0), 
			dwPower(0), dwBuyTime(0), dwTotalTime(0), dwFailFloorID(0), dwFailPos(0), 
			byColor(0) { }

SDemonTowerPlayer::SDemonTowerPlayer(SDemonTowerPlayer&& src) : qwUserID(src.qwUserID), qwRoleID(src.qwRoleID), strRoleName(move(src.strRoleName)), bySex(src.bySex), byLevel(src.byLevel), 
			dwFloorID(src.dwFloorID), dwGuardFloorID(src.dwGuardFloorID), dwGuardPos(src.dwGuardPos), dwGuardStartTime(src.dwGuardStartTime), dwGuardEndTime(src.dwGuardEndTime), 
			dwGuardNextPrizeTime(src.dwGuardNextPrizeTime), dwGuardNextReduceRateTime(src.dwGuardNextReduceRateTime), dwGuardGatherSpeed(src.dwGuardGatherSpeed), dwGuardGatherSpeedEndTimer(src.dwGuardGatherSpeedEndTimer), dwGuardReduceRate(src.dwGuardReduceRate), 
			dwGuardNextAttackTime(src.dwGuardNextAttackTime), dwPower(src.dwPower), dwBuyTime(src.dwBuyTime), vecGatherSoulPrize(move(src.vecGatherSoulPrize)), vecFailSoulPrize(move(src.vecFailSoulPrize)), 
			vecDaySoulPrize(move(src.vecDaySoulPrize)), dwTotalTime(src.dwTotalTime), dwFailFloorID(src.dwFailFloorID), dwFailPos(src.dwFailPos), byColor(src.byColor) { }

SDemonTowerPlayer& SDemonTowerPlayer::operator=(SDemonTowerPlayer&& rhs)
{
	if(this != &rhs)
	{
		this->~SDemonTowerPlayer();
		new (this) SDemonTowerPlayer(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SDemonTowerPlayer& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwUserID;
	src >> s.qwRoleID;
	src >> s.strRoleName;
	src >> s.bySex;
	src >> s.byLevel;
	src >> s.dwFloorID;
	src >> s.dwGuardFloorID;
	src >> s.dwGuardPos;
	src >> s.dwGuardStartTime;
	src >> s.dwGuardEndTime;
	src >> s.dwGuardNextPrizeTime;
	src >> s.dwGuardNextReduceRateTime;
	src >> s.dwGuardGatherSpeed;
	src >> s.dwGuardGatherSpeedEndTimer;
	src >> s.dwGuardReduceRate;
	src >> s.dwGuardNextAttackTime;
	src >> s.dwPower;
	src >> s.dwBuyTime;
	src >> s.vecGatherSoulPrize;
	src >> s.vecFailSoulPrize;
	src >> s.vecDaySoulPrize;
	src >> s.dwTotalTime;
	src >> s.dwFailFloorID;
	src >> s.dwFailPos;
	src >> s.byColor;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SDemonTowerPlayer& s)
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
	src << s.strRoleName;
	src << s.bySex;
	src << s.byLevel;
	src << s.dwFloorID;
	src << s.dwGuardFloorID;
	src << s.dwGuardPos;
	src << s.dwGuardStartTime;
	src << s.dwGuardEndTime;
	src << s.dwGuardNextPrizeTime;
	src << s.dwGuardNextReduceRateTime;
	src << s.dwGuardGatherSpeed;
	src << s.dwGuardGatherSpeedEndTimer;
	src << s.dwGuardReduceRate;
	src << s.dwGuardNextAttackTime;
	src << s.dwPower;
	src << s.dwBuyTime;
	src << s.vecGatherSoulPrize;
	src << s.vecFailSoulPrize;
	src << s.vecDaySoulPrize;
	src << s.dwTotalTime;
	src << s.dwFailFloorID;
	src << s.dwFailPos;
	src << s.byColor;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SDemonTowerPlayer& s)
{
	if(strcmp(rElement.Value(), "SDemonTowerPlayer") != 0)
	{
		LOG_CRI << "rElement is not SDemonTowerPlayer!";
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
		LOG_CRI << "pElemChild for strRoleName is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strRoleName") != 0)
	{
		LOG_CRI << "Attribute: name is not strRoleName!";
		return false;
	}
	const char* pszVal_strRoleName = pElemChild->Attribute("value");
	if(pszVal_strRoleName == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strRoleName = pszVal_strRoleName;
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
		LOG_CRI << "pElemChild for dwGuardFloorID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwGuardFloorID") != 0)
	{
		LOG_CRI << "Attribute: name is not dwGuardFloorID!";
		return false;
	}
	const char* pszVal_dwGuardFloorID = pElemChild->Attribute("value");
	if(pszVal_dwGuardFloorID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwGuardFloorID, s.dwGuardFloorID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwGuardPos is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwGuardPos") != 0)
	{
		LOG_CRI << "Attribute: name is not dwGuardPos!";
		return false;
	}
	const char* pszVal_dwGuardPos = pElemChild->Attribute("value");
	if(pszVal_dwGuardPos == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwGuardPos, s.dwGuardPos))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwGuardStartTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwGuardStartTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwGuardStartTime!";
		return false;
	}
	const char* pszVal_dwGuardStartTime = pElemChild->Attribute("value");
	if(pszVal_dwGuardStartTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwGuardStartTime, s.dwGuardStartTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwGuardEndTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwGuardEndTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwGuardEndTime!";
		return false;
	}
	const char* pszVal_dwGuardEndTime = pElemChild->Attribute("value");
	if(pszVal_dwGuardEndTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwGuardEndTime, s.dwGuardEndTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwGuardNextPrizeTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwGuardNextPrizeTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwGuardNextPrizeTime!";
		return false;
	}
	const char* pszVal_dwGuardNextPrizeTime = pElemChild->Attribute("value");
	if(pszVal_dwGuardNextPrizeTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwGuardNextPrizeTime, s.dwGuardNextPrizeTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwGuardNextReduceRateTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwGuardNextReduceRateTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwGuardNextReduceRateTime!";
		return false;
	}
	const char* pszVal_dwGuardNextReduceRateTime = pElemChild->Attribute("value");
	if(pszVal_dwGuardNextReduceRateTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwGuardNextReduceRateTime, s.dwGuardNextReduceRateTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwGuardGatherSpeed is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwGuardGatherSpeed") != 0)
	{
		LOG_CRI << "Attribute: name is not dwGuardGatherSpeed!";
		return false;
	}
	const char* pszVal_dwGuardGatherSpeed = pElemChild->Attribute("value");
	if(pszVal_dwGuardGatherSpeed == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwGuardGatherSpeed, s.dwGuardGatherSpeed))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwGuardGatherSpeedEndTimer is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwGuardGatherSpeedEndTimer") != 0)
	{
		LOG_CRI << "Attribute: name is not dwGuardGatherSpeedEndTimer!";
		return false;
	}
	const char* pszVal_dwGuardGatherSpeedEndTimer = pElemChild->Attribute("value");
	if(pszVal_dwGuardGatherSpeedEndTimer == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwGuardGatherSpeedEndTimer, s.dwGuardGatherSpeedEndTimer))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwGuardReduceRate is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwGuardReduceRate") != 0)
	{
		LOG_CRI << "Attribute: name is not dwGuardReduceRate!";
		return false;
	}
	const char* pszVal_dwGuardReduceRate = pElemChild->Attribute("value");
	if(pszVal_dwGuardReduceRate == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwGuardReduceRate, s.dwGuardReduceRate))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwGuardNextAttackTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwGuardNextAttackTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwGuardNextAttackTime!";
		return false;
	}
	const char* pszVal_dwGuardNextAttackTime = pElemChild->Attribute("value");
	if(pszVal_dwGuardNextAttackTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwGuardNextAttackTime, s.dwGuardNextAttackTime))
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
		LOG_CRI << "pElemChild for dwBuyTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwBuyTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwBuyTime!";
		return false;
	}
	const char* pszVal_dwBuyTime = pElemChild->Attribute("value");
	if(pszVal_dwBuyTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwBuyTime, s.dwBuyTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecGatherSoulPrize is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecMoneyInfo") != 0)
	{
		LOG_CRI << "pElemChild is not TVecMoneyInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecGatherSoulPrize") != 0)
	{
		LOG_CRI << "Attribute: name is not vecGatherSoulPrize!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecGatherSoulPrize))
	{
		LOG_CRI << "VectorFromXML for vecGatherSoulPrize fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecFailSoulPrize is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecMoneyInfo") != 0)
	{
		LOG_CRI << "pElemChild is not TVecMoneyInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecFailSoulPrize") != 0)
	{
		LOG_CRI << "Attribute: name is not vecFailSoulPrize!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecFailSoulPrize))
	{
		LOG_CRI << "VectorFromXML for vecFailSoulPrize fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecDaySoulPrize is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecMoneyInfo") != 0)
	{
		LOG_CRI << "pElemChild is not TVecMoneyInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecDaySoulPrize") != 0)
	{
		LOG_CRI << "Attribute: name is not vecDaySoulPrize!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecDaySoulPrize))
	{
		LOG_CRI << "VectorFromXML for vecDaySoulPrize fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwTotalTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwTotalTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwTotalTime!";
		return false;
	}
	const char* pszVal_dwTotalTime = pElemChild->Attribute("value");
	if(pszVal_dwTotalTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwTotalTime, s.dwTotalTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwFailFloorID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwFailFloorID") != 0)
	{
		LOG_CRI << "Attribute: name is not dwFailFloorID!";
		return false;
	}
	const char* pszVal_dwFailFloorID = pElemChild->Attribute("value");
	if(pszVal_dwFailFloorID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwFailFloorID, s.dwFailFloorID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwFailPos is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwFailPos") != 0)
	{
		LOG_CRI << "Attribute: name is not dwFailPos!";
		return false;
	}
	const char* pszVal_dwFailPos = pElemChild->Attribute("value");
	if(pszVal_dwFailPos == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwFailPos, s.dwFailPos))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byColor is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byColor") != 0)
	{
		LOG_CRI << "Attribute: name is not byColor!";
		return false;
	}
	const char* pszVal_byColor = pElemChild->Attribute("value");
	if(pszVal_byColor == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byColor, s.byColor))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SDemonTowerPlayer& s, TiXmlElement& rElement)
{
	rElement.SetValue("SDemonTowerPlayer");
	rElement.SetAttribute("type", ToUTF8Ptr("镇守的玩家信息列表"));
	unique_ptr<TiXmlElement> pElem_qwUserID(new TiXmlElement("UINT64"));
	if(pElem_qwUserID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwUserID->SetAttribute("name", "qwUserID");
	pElem_qwUserID->SetAttribute("value", NumberToString(s.qwUserID).c_str());
	pElem_qwUserID->SetAttribute("comment", ToUTF8Ptr("uid"));
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
	pElem_qwRoleID->SetAttribute("comment", ToUTF8Ptr("角色id"));
	if(rElement.LinkEndChild(pElem_qwRoleID.get()) != NULL)
		pElem_qwRoleID.release();
	unique_ptr<TiXmlElement> pElem_strRoleName(new TiXmlElement("string"));
	if(pElem_strRoleName == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strRoleName->SetAttribute("name", "strRoleName");
	pElem_strRoleName->SetAttribute("value", s.strRoleName.c_str());
	pElem_strRoleName->SetAttribute("comment", ToUTF8Ptr("角色名"));
	if(rElement.LinkEndChild(pElem_strRoleName.get()) != NULL)
		pElem_strRoleName.release();
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
	unique_ptr<TiXmlElement> pElem_dwFloorID(new TiXmlElement("UINT32"));
	if(pElem_dwFloorID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwFloorID->SetAttribute("name", "dwFloorID");
	pElem_dwFloorID->SetAttribute("value", NumberToString(s.dwFloorID).c_str());
	pElem_dwFloorID->SetAttribute("comment", ToUTF8Ptr("当前所在塔层"));
	if(rElement.LinkEndChild(pElem_dwFloorID.get()) != NULL)
		pElem_dwFloorID.release();
	unique_ptr<TiXmlElement> pElem_dwGuardFloorID(new TiXmlElement("UINT32"));
	if(pElem_dwGuardFloorID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwGuardFloorID->SetAttribute("name", "dwGuardFloorID");
	pElem_dwGuardFloorID->SetAttribute("value", NumberToString(s.dwGuardFloorID).c_str());
	pElem_dwGuardFloorID->SetAttribute("comment", ToUTF8Ptr("镇守塔层"));
	if(rElement.LinkEndChild(pElem_dwGuardFloorID.get()) != NULL)
		pElem_dwGuardFloorID.release();
	unique_ptr<TiXmlElement> pElem_dwGuardPos(new TiXmlElement("UINT32"));
	if(pElem_dwGuardPos == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwGuardPos->SetAttribute("name", "dwGuardPos");
	pElem_dwGuardPos->SetAttribute("value", NumberToString(s.dwGuardPos).c_str());
	pElem_dwGuardPos->SetAttribute("comment", ToUTF8Ptr("镇守位置"));
	if(rElement.LinkEndChild(pElem_dwGuardPos.get()) != NULL)
		pElem_dwGuardPos.release();
	unique_ptr<TiXmlElement> pElem_dwGuardStartTime(new TiXmlElement("UINT32"));
	if(pElem_dwGuardStartTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwGuardStartTime->SetAttribute("name", "dwGuardStartTime");
	pElem_dwGuardStartTime->SetAttribute("value", NumberToString(s.dwGuardStartTime).c_str());
	pElem_dwGuardStartTime->SetAttribute("comment", ToUTF8Ptr("镇守开始时间"));
	if(rElement.LinkEndChild(pElem_dwGuardStartTime.get()) != NULL)
		pElem_dwGuardStartTime.release();
	unique_ptr<TiXmlElement> pElem_dwGuardEndTime(new TiXmlElement("UINT32"));
	if(pElem_dwGuardEndTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwGuardEndTime->SetAttribute("name", "dwGuardEndTime");
	pElem_dwGuardEndTime->SetAttribute("value", NumberToString(s.dwGuardEndTime).c_str());
	pElem_dwGuardEndTime->SetAttribute("comment", ToUTF8Ptr("镇守结束时间"));
	if(rElement.LinkEndChild(pElem_dwGuardEndTime.get()) != NULL)
		pElem_dwGuardEndTime.release();
	unique_ptr<TiXmlElement> pElem_dwGuardNextPrizeTime(new TiXmlElement("UINT32"));
	if(pElem_dwGuardNextPrizeTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwGuardNextPrizeTime->SetAttribute("name", "dwGuardNextPrizeTime");
	pElem_dwGuardNextPrizeTime->SetAttribute("value", NumberToString(s.dwGuardNextPrizeTime).c_str());
	pElem_dwGuardNextPrizeTime->SetAttribute("comment", ToUTF8Ptr("下次奖励时间"));
	if(rElement.LinkEndChild(pElem_dwGuardNextPrizeTime.get()) != NULL)
		pElem_dwGuardNextPrizeTime.release();
	unique_ptr<TiXmlElement> pElem_dwGuardNextReduceRateTime(new TiXmlElement("UINT32"));
	if(pElem_dwGuardNextReduceRateTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwGuardNextReduceRateTime->SetAttribute("name", "dwGuardNextReduceRateTime");
	pElem_dwGuardNextReduceRateTime->SetAttribute("value", NumberToString(s.dwGuardNextReduceRateTime).c_str());
	pElem_dwGuardNextReduceRateTime->SetAttribute("comment", ToUTF8Ptr("下次减弱时间"));
	if(rElement.LinkEndChild(pElem_dwGuardNextReduceRateTime.get()) != NULL)
		pElem_dwGuardNextReduceRateTime.release();
	unique_ptr<TiXmlElement> pElem_dwGuardGatherSpeed(new TiXmlElement("UINT32"));
	if(pElem_dwGuardGatherSpeed == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwGuardGatherSpeed->SetAttribute("name", "dwGuardGatherSpeed");
	pElem_dwGuardGatherSpeed->SetAttribute("value", NumberToString(s.dwGuardGatherSpeed).c_str());
	pElem_dwGuardGatherSpeed->SetAttribute("comment", ToUTF8Ptr("聚魂速度"));
	if(rElement.LinkEndChild(pElem_dwGuardGatherSpeed.get()) != NULL)
		pElem_dwGuardGatherSpeed.release();
	unique_ptr<TiXmlElement> pElem_dwGuardGatherSpeedEndTimer(new TiXmlElement("UINT32"));
	if(pElem_dwGuardGatherSpeedEndTimer == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwGuardGatherSpeedEndTimer->SetAttribute("name", "dwGuardGatherSpeedEndTimer");
	pElem_dwGuardGatherSpeedEndTimer->SetAttribute("value", NumberToString(s.dwGuardGatherSpeedEndTimer).c_str());
	pElem_dwGuardGatherSpeedEndTimer->SetAttribute("comment", ToUTF8Ptr("加速时间"));
	if(rElement.LinkEndChild(pElem_dwGuardGatherSpeedEndTimer.get()) != NULL)
		pElem_dwGuardGatherSpeedEndTimer.release();
	unique_ptr<TiXmlElement> pElem_dwGuardReduceRate(new TiXmlElement("UINT32"));
	if(pElem_dwGuardReduceRate == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwGuardReduceRate->SetAttribute("name", "dwGuardReduceRate");
	pElem_dwGuardReduceRate->SetAttribute("value", NumberToString(s.dwGuardReduceRate).c_str());
	pElem_dwGuardReduceRate->SetAttribute("comment", ToUTF8Ptr("元神灵力(百分比1为1%)"));
	if(rElement.LinkEndChild(pElem_dwGuardReduceRate.get()) != NULL)
		pElem_dwGuardReduceRate.release();
	unique_ptr<TiXmlElement> pElem_dwGuardNextAttackTime(new TiXmlElement("UINT32"));
	if(pElem_dwGuardNextAttackTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwGuardNextAttackTime->SetAttribute("name", "dwGuardNextAttackTime");
	pElem_dwGuardNextAttackTime->SetAttribute("value", NumberToString(s.dwGuardNextAttackTime).c_str());
	pElem_dwGuardNextAttackTime->SetAttribute("comment", ToUTF8Ptr("镇守可以攻击的时间"));
	if(rElement.LinkEndChild(pElem_dwGuardNextAttackTime.get()) != NULL)
		pElem_dwGuardNextAttackTime.release();
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
	unique_ptr<TiXmlElement> pElem_dwBuyTime(new TiXmlElement("UINT32"));
	if(pElem_dwBuyTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwBuyTime->SetAttribute("name", "dwBuyTime");
	pElem_dwBuyTime->SetAttribute("value", NumberToString(s.dwBuyTime).c_str());
	pElem_dwBuyTime->SetAttribute("comment", ToUTF8Ptr("购买cd(服务器用)"));
	if(rElement.LinkEndChild(pElem_dwBuyTime.get()) != NULL)
		pElem_dwBuyTime.release();
	unique_ptr<TiXmlElement> pElem_vecGatherSoulPrize(new TiXmlElement("TVecMoneyInfo"));
	if(pElem_vecGatherSoulPrize == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecGatherSoulPrize->SetAttribute("name", "vecGatherSoulPrize");
	if(!VectorToXML(s.vecGatherSoulPrize, *pElem_vecGatherSoulPrize))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecGatherSoulPrize->SetAttribute("comment", ToUTF8Ptr("当前聚集的魄奖励"));
	if(rElement.LinkEndChild(pElem_vecGatherSoulPrize.get()) != NULL)
		pElem_vecGatherSoulPrize.release();
	unique_ptr<TiXmlElement> pElem_vecFailSoulPrize(new TiXmlElement("TVecMoneyInfo"));
	if(pElem_vecFailSoulPrize == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecFailSoulPrize->SetAttribute("name", "vecFailSoulPrize");
	if(!VectorToXML(s.vecFailSoulPrize, *pElem_vecFailSoulPrize))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecFailSoulPrize->SetAttribute("comment", ToUTF8Ptr("失败后的魄奖励"));
	if(rElement.LinkEndChild(pElem_vecFailSoulPrize.get()) != NULL)
		pElem_vecFailSoulPrize.release();
	unique_ptr<TiXmlElement> pElem_vecDaySoulPrize(new TiXmlElement("TVecMoneyInfo"));
	if(pElem_vecDaySoulPrize == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecDaySoulPrize->SetAttribute("name", "vecDaySoulPrize");
	if(!VectorToXML(s.vecDaySoulPrize, *pElem_vecDaySoulPrize))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecDaySoulPrize->SetAttribute("comment", ToUTF8Ptr("7点结算的魄奖励"));
	if(rElement.LinkEndChild(pElem_vecDaySoulPrize.get()) != NULL)
		pElem_vecDaySoulPrize.release();
	unique_ptr<TiXmlElement> pElem_dwTotalTime(new TiXmlElement("UINT32"));
	if(pElem_dwTotalTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwTotalTime->SetAttribute("name", "dwTotalTime");
	pElem_dwTotalTime->SetAttribute("value", NumberToString(s.dwTotalTime).c_str());
	pElem_dwTotalTime->SetAttribute("comment", ToUTF8Ptr("镇守时间(服务器用)"));
	if(rElement.LinkEndChild(pElem_dwTotalTime.get()) != NULL)
		pElem_dwTotalTime.release();
	unique_ptr<TiXmlElement> pElem_dwFailFloorID(new TiXmlElement("UINT32"));
	if(pElem_dwFailFloorID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwFailFloorID->SetAttribute("name", "dwFailFloorID");
	pElem_dwFailFloorID->SetAttribute("value", NumberToString(s.dwFailFloorID).c_str());
	pElem_dwFailFloorID->SetAttribute("comment", ToUTF8Ptr("失败镇守塔层"));
	if(rElement.LinkEndChild(pElem_dwFailFloorID.get()) != NULL)
		pElem_dwFailFloorID.release();
	unique_ptr<TiXmlElement> pElem_dwFailPos(new TiXmlElement("UINT32"));
	if(pElem_dwFailPos == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwFailPos->SetAttribute("name", "dwFailPos");
	pElem_dwFailPos->SetAttribute("value", NumberToString(s.dwFailPos).c_str());
	pElem_dwFailPos->SetAttribute("comment", ToUTF8Ptr("失败镇守位置"));
	if(rElement.LinkEndChild(pElem_dwFailPos.get()) != NULL)
		pElem_dwFailPos.release();
	unique_ptr<TiXmlElement> pElem_byColor(new TiXmlElement("UINT8"));
	if(pElem_byColor == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byColor->SetAttribute("name", "byColor");
	pElem_byColor->SetAttribute("value", NumberToString(s.byColor).c_str());
	pElem_byColor->SetAttribute("comment", ToUTF8Ptr("角色颜色"));
	if(rElement.LinkEndChild(pElem_byColor.get()) != NULL)
		pElem_byColor.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecDemonTowerPlayer& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SDemonTowerPlayer s;
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

bool VectorToXML(const TVecDemonTowerPlayer& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SDemonTowerPlayer"));
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

GuardInfo::GuardInfo() : qwUserID(0), qwRoleID(0), dwGuardPos(0), dwLastFightCD(0) { }

GuardInfo::GuardInfo(UINT64 qwUserID_, UINT64 qwRoleID_, UINT32 dwGuardPos_, UINT32 dwLastFightCD_, const SDemonFloorPlayer& oDemonFloorPlayer_)
			: qwUserID(qwUserID_), qwRoleID(qwRoleID_), dwGuardPos(dwGuardPos_), dwLastFightCD(dwLastFightCD_), oDemonFloorPlayer(oDemonFloorPlayer_) { }

GuardInfo::GuardInfo(GuardInfo&& src) : qwUserID(src.qwUserID), qwRoleID(src.qwRoleID), dwGuardPos(src.dwGuardPos), dwLastFightCD(src.dwLastFightCD), oDemonFloorPlayer(move(src.oDemonFloorPlayer)) { }

GuardInfo& GuardInfo::operator=(GuardInfo&& rhs)
{
	if(this != &rhs)
	{
		this->~GuardInfo();
		new (this) GuardInfo(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, GuardInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwUserID;
	src >> s.qwRoleID;
	src >> s.dwGuardPos;
	src >> s.dwLastFightCD;
	src >> s.oDemonFloorPlayer;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const GuardInfo& s)
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
	src << s.dwGuardPos;
	src << s.dwLastFightCD;
	src << s.oDemonFloorPlayer;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, GuardInfo& s)
{
	if(strcmp(rElement.Value(), "GuardInfo") != 0)
	{
		LOG_CRI << "rElement is not GuardInfo!";
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
		LOG_CRI << "pElemChild for dwGuardPos is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwGuardPos") != 0)
	{
		LOG_CRI << "Attribute: name is not dwGuardPos!";
		return false;
	}
	const char* pszVal_dwGuardPos = pElemChild->Attribute("value");
	if(pszVal_dwGuardPos == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwGuardPos, s.dwGuardPos))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwLastFightCD is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwLastFightCD") != 0)
	{
		LOG_CRI << "Attribute: name is not dwLastFightCD!";
		return false;
	}
	const char* pszVal_dwLastFightCD = pElemChild->Attribute("value");
	if(pszVal_dwLastFightCD == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwLastFightCD, s.dwLastFightCD))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for oDemonFloorPlayer is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "SDemonFloorPlayer") != 0)
	{
		LOG_CRI << "pElemChild is not SDemonFloorPlayer!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "oDemonFloorPlayer") != 0)
	{
		LOG_CRI << "Attribute: name is not oDemonFloorPlayer!";
		return false;
	}
	if(!FromXML(*pElemChild, s.oDemonFloorPlayer))
	{
		LOG_CRI << "FromXML for: oDemonFloorPlayer fails!";
		return false;
	}
	return true;
}

bool ToXML(const GuardInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("GuardInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("镇守的玩家信息列表"));
	unique_ptr<TiXmlElement> pElem_qwUserID(new TiXmlElement("UINT64"));
	if(pElem_qwUserID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwUserID->SetAttribute("name", "qwUserID");
	pElem_qwUserID->SetAttribute("value", NumberToString(s.qwUserID).c_str());
	pElem_qwUserID->SetAttribute("comment", ToUTF8Ptr("uid"));
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
	pElem_qwRoleID->SetAttribute("comment", ToUTF8Ptr("角色id"));
	if(rElement.LinkEndChild(pElem_qwRoleID.get()) != NULL)
		pElem_qwRoleID.release();
	unique_ptr<TiXmlElement> pElem_dwGuardPos(new TiXmlElement("UINT32"));
	if(pElem_dwGuardPos == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwGuardPos->SetAttribute("name", "dwGuardPos");
	pElem_dwGuardPos->SetAttribute("value", NumberToString(s.dwGuardPos).c_str());
	pElem_dwGuardPos->SetAttribute("comment", ToUTF8Ptr("封印位置"));
	if(rElement.LinkEndChild(pElem_dwGuardPos.get()) != NULL)
		pElem_dwGuardPos.release();
	unique_ptr<TiXmlElement> pElem_dwLastFightCD(new TiXmlElement("UINT32"));
	if(pElem_dwLastFightCD == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwLastFightCD->SetAttribute("name", "dwLastFightCD");
	pElem_dwLastFightCD->SetAttribute("value", NumberToString(s.dwLastFightCD).c_str());
	pElem_dwLastFightCD->SetAttribute("comment", ToUTF8Ptr("战斗cd 1s"));
	if(rElement.LinkEndChild(pElem_dwLastFightCD.get()) != NULL)
		pElem_dwLastFightCD.release();
	unique_ptr<TiXmlElement> pElem_oDemonFloorPlayer(new TiXmlElement("SDemonFloorPlayer"));
	if(pElem_oDemonFloorPlayer == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_oDemonFloorPlayer->SetAttribute("name", "oDemonFloorPlayer");
	if(!ToXML(s.oDemonFloorPlayer, *pElem_oDemonFloorPlayer))
	{
		LOG_CRI << "oDemonFloorPlayer ToXML fails!";
		return false;
	}
	pElem_oDemonFloorPlayer->SetAttribute("comment", ToUTF8Ptr("玩家信息"));
	if(rElement.LinkEndChild(pElem_oDemonFloorPlayer.get()) != NULL)
		pElem_oDemonFloorPlayer.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecGuardInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		GuardInfo s;
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

bool VectorToXML(const TVecGuardInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("GuardInfo"));
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

SDemonTowerKillMonster::SDemonTowerKillMonster() : qwUserID(0), byColor(0), bySex(0), byCareer(0), byLevel(0), 
			dwRounds(0), dwBattlePoint(0), qwReportID(0) { }

SDemonTowerKillMonster::SDemonTowerKillMonster(UINT64 qwUserID_, const std::string& strName_, UINT8 byColor_, UINT8 bySex_, UINT8 byCareer_, 
			UINT8 byLevel_, UINT32 dwRounds_, UINT32 dwBattlePoint_, UINT64 qwReportID_)
			: qwUserID(qwUserID_), strName(strName_), byColor(byColor_), bySex(bySex_), byCareer(byCareer_), 
			byLevel(byLevel_), dwRounds(dwRounds_), dwBattlePoint(dwBattlePoint_), qwReportID(qwReportID_) { }

SDemonTowerKillMonster::SDemonTowerKillMonster(SDemonTowerKillMonster&& src) : qwUserID(src.qwUserID), strName(move(src.strName)), byColor(src.byColor), bySex(src.bySex), byCareer(src.byCareer), 
			byLevel(src.byLevel), dwRounds(src.dwRounds), dwBattlePoint(src.dwBattlePoint), qwReportID(src.qwReportID) { }

SDemonTowerKillMonster& SDemonTowerKillMonster::operator=(SDemonTowerKillMonster&& rhs)
{
	if(this != &rhs)
	{
		this->~SDemonTowerKillMonster();
		new (this) SDemonTowerKillMonster(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SDemonTowerKillMonster& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwUserID;
	src >> s.strName;
	src >> s.byColor;
	src >> s.bySex;
	src >> s.byCareer;
	src >> s.byLevel;
	src >> s.dwRounds;
	src >> s.dwBattlePoint;
	src >> s.qwReportID;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SDemonTowerKillMonster& s)
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
	src << s.strName;
	src << s.byColor;
	src << s.bySex;
	src << s.byCareer;
	src << s.byLevel;
	src << s.dwRounds;
	src << s.dwBattlePoint;
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

bool FromXML(TiXmlElement& rElement, SDemonTowerKillMonster& s)
{
	if(strcmp(rElement.Value(), "SDemonTowerKillMonster") != 0)
	{
		LOG_CRI << "rElement is not SDemonTowerKillMonster!";
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
		LOG_CRI << "pElemChild for byColor is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byColor") != 0)
	{
		LOG_CRI << "Attribute: name is not byColor!";
		return false;
	}
	const char* pszVal_byColor = pElemChild->Attribute("value");
	if(pszVal_byColor == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byColor, s.byColor))
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
		LOG_CRI << "pElemChild for byCareer is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byCareer") != 0)
	{
		LOG_CRI << "Attribute: name is not byCareer!";
		return false;
	}
	const char* pszVal_byCareer = pElemChild->Attribute("value");
	if(pszVal_byCareer == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byCareer, s.byCareer))
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
		LOG_CRI << "pElemChild for dwRounds is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwRounds") != 0)
	{
		LOG_CRI << "Attribute: name is not dwRounds!";
		return false;
	}
	const char* pszVal_dwRounds = pElemChild->Attribute("value");
	if(pszVal_dwRounds == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwRounds, s.dwRounds))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwBattlePoint is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwBattlePoint") != 0)
	{
		LOG_CRI << "Attribute: name is not dwBattlePoint!";
		return false;
	}
	const char* pszVal_dwBattlePoint = pElemChild->Attribute("value");
	if(pszVal_dwBattlePoint == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwBattlePoint, s.dwBattlePoint))
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

bool ToXML(const SDemonTowerKillMonster& s, TiXmlElement& rElement)
{
	rElement.SetValue("SDemonTowerKillMonster");
	rElement.SetAttribute("type", ToUTF8Ptr("通关信息"));
	unique_ptr<TiXmlElement> pElem_qwUserID(new TiXmlElement("UINT64"));
	if(pElem_qwUserID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwUserID->SetAttribute("name", "qwUserID");
	pElem_qwUserID->SetAttribute("value", NumberToString(s.qwUserID).c_str());
	pElem_qwUserID->SetAttribute("comment", ToUTF8Ptr("账号id"));
	if(rElement.LinkEndChild(pElem_qwUserID.get()) != NULL)
		pElem_qwUserID.release();
	unique_ptr<TiXmlElement> pElem_strName(new TiXmlElement("string"));
	if(pElem_strName == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strName->SetAttribute("name", "strName");
	pElem_strName->SetAttribute("value", s.strName.c_str());
	pElem_strName->SetAttribute("comment", ToUTF8Ptr("名字"));
	if(rElement.LinkEndChild(pElem_strName.get()) != NULL)
		pElem_strName.release();
	unique_ptr<TiXmlElement> pElem_byColor(new TiXmlElement("UINT8"));
	if(pElem_byColor == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byColor->SetAttribute("name", "byColor");
	pElem_byColor->SetAttribute("value", NumberToString(s.byColor).c_str());
	pElem_byColor->SetAttribute("comment", ToUTF8Ptr("角色颜色"));
	if(rElement.LinkEndChild(pElem_byColor.get()) != NULL)
		pElem_byColor.release();
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
	unique_ptr<TiXmlElement> pElem_byCareer(new TiXmlElement("UINT8"));
	if(pElem_byCareer == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byCareer->SetAttribute("name", "byCareer");
	pElem_byCareer->SetAttribute("value", NumberToString(s.byCareer).c_str());
	pElem_byCareer->SetAttribute("comment", ToUTF8Ptr("职业"));
	if(rElement.LinkEndChild(pElem_byCareer.get()) != NULL)
		pElem_byCareer.release();
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
	unique_ptr<TiXmlElement> pElem_dwRounds(new TiXmlElement("UINT32"));
	if(pElem_dwRounds == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwRounds->SetAttribute("name", "dwRounds");
	pElem_dwRounds->SetAttribute("value", NumberToString(s.dwRounds).c_str());
	pElem_dwRounds->SetAttribute("comment", ToUTF8Ptr("通关回合数"));
	if(rElement.LinkEndChild(pElem_dwRounds.get()) != NULL)
		pElem_dwRounds.release();
	unique_ptr<TiXmlElement> pElem_dwBattlePoint(new TiXmlElement("UINT32"));
	if(pElem_dwBattlePoint == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwBattlePoint->SetAttribute("name", "dwBattlePoint");
	pElem_dwBattlePoint->SetAttribute("value", NumberToString(s.dwBattlePoint).c_str());
	pElem_dwBattlePoint->SetAttribute("comment", ToUTF8Ptr("战斗力"));
	if(rElement.LinkEndChild(pElem_dwBattlePoint.get()) != NULL)
		pElem_dwBattlePoint.release();
	unique_ptr<TiXmlElement> pElem_qwReportID(new TiXmlElement("UINT64"));
	if(pElem_qwReportID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwReportID->SetAttribute("name", "qwReportID");
	pElem_qwReportID->SetAttribute("value", NumberToString(s.qwReportID).c_str());
	pElem_qwReportID->SetAttribute("comment", ToUTF8Ptr("战报"));
	if(rElement.LinkEndChild(pElem_qwReportID.get()) != NULL)
		pElem_qwReportID.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecDemonTowerKillMonster& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SDemonTowerKillMonster s;
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

bool VectorToXML(const TVecDemonTowerKillMonster& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SDemonTowerKillMonster"));
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

} //namespace NDemonTowerGS
