/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    LingShanProt.cpp
//  Purpose:      灵山（改名秘境）寻宝
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "LingShanProt.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NLingShanProt
{

#ifdef PROT_USE_XML

const char* EnumValToStr(ELingShanOP e)
{
	switch(e)
	{
	case eLingShanOP_Sucess:
		return "eLingShanOP_Sucess";
	case eLingShanOP_Fail:
		return "eLingShanOP_Fail";
	case eLingShanOP_Cd:
		return "eLingShanOP_Cd";
	case eLingShanOP_ErrorPath:
		return "eLingShanOP_ErrorPath";
	case eLingShanOP_NoMove:
		return "eLingShanOP_NoMove";
	case eLingShanOP_NoOpen:
		return "eLingShanOP_NoOpen";
	case eLingShanOP_NoReg:
		return "eLingShanOP_NoReg";
	case eLingShanOP_ErrorRoomId:
		return "eLingShanOP_ErrorRoomId";
	case eLingShanOP_MoveCd:
		return "eLingShanOP_MoveCd";
	case eLingShanOP_MapCFG:
		return "eLingShanOP_MapCFG";
	case eLingShanOP_NotInRoom:
		return "eLingShanOP_NotInRoom";
	case eLingShanOP_ErrorModelID:
		return "eLingShanOP_ErrorModelID";
	case eLingShanOP_ErrorCondID:
		return "eLingShanOP_ErrorCondID";
	case eLingShanOP_ActEnded:
		return "eLingShanOP_ActEnded";
	case eLingShanOP_ChatCD:
		return "eLingShanOP_ChatCD";
	case eLingShanOP_End:
		return "eLingShanOP_End";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, ELingShanOP& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, ELingShanOP> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eLingShanOP_Sucess", eLingShanOP_Sucess));
		mapStr2Val.insert(make_pair("eLingShanOP_Fail", eLingShanOP_Fail));
		mapStr2Val.insert(make_pair("eLingShanOP_Cd", eLingShanOP_Cd));
		mapStr2Val.insert(make_pair("eLingShanOP_ErrorPath", eLingShanOP_ErrorPath));
		mapStr2Val.insert(make_pair("eLingShanOP_NoMove", eLingShanOP_NoMove));
		mapStr2Val.insert(make_pair("eLingShanOP_NoOpen", eLingShanOP_NoOpen));
		mapStr2Val.insert(make_pair("eLingShanOP_NoReg", eLingShanOP_NoReg));
		mapStr2Val.insert(make_pair("eLingShanOP_ErrorRoomId", eLingShanOP_ErrorRoomId));
		mapStr2Val.insert(make_pair("eLingShanOP_MoveCd", eLingShanOP_MoveCd));
		mapStr2Val.insert(make_pair("eLingShanOP_MapCFG", eLingShanOP_MapCFG));
		mapStr2Val.insert(make_pair("eLingShanOP_NotInRoom", eLingShanOP_NotInRoom));
		mapStr2Val.insert(make_pair("eLingShanOP_ErrorModelID", eLingShanOP_ErrorModelID));
		mapStr2Val.insert(make_pair("eLingShanOP_ErrorCondID", eLingShanOP_ErrorCondID));
		mapStr2Val.insert(make_pair("eLingShanOP_ActEnded", eLingShanOP_ActEnded));
		mapStr2Val.insert(make_pair("eLingShanOP_ChatCD", eLingShanOP_ChatCD));
		mapStr2Val.insert(make_pair("eLingShanOP_End", eLingShanOP_End));
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

const char* EnumValToStr(ELingShanStatus e)
{
	switch(e)
	{
	case eLingShanStatus_Init:
		return "eLingShanStatus_Init";
	case eLingShanStatus_Wait:
		return "eLingShanStatus_Wait";
	case eLingShanStatus_Move:
		return "eLingShanStatus_Move";
	case eLingShanStatus_PlayMovie:
		return "eLingShanStatus_PlayMovie";
	case eLingShanStatus_End:
		return "eLingShanStatus_End";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, ELingShanStatus& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, ELingShanStatus> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eLingShanStatus_Init", eLingShanStatus_Init));
		mapStr2Val.insert(make_pair("eLingShanStatus_Wait", eLingShanStatus_Wait));
		mapStr2Val.insert(make_pair("eLingShanStatus_Move", eLingShanStatus_Move));
		mapStr2Val.insert(make_pair("eLingShanStatus_PlayMovie", eLingShanStatus_PlayMovie));
		mapStr2Val.insert(make_pair("eLingShanStatus_End", eLingShanStatus_End));
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

const char* EnumValToStr(ELingShanObjType e)
{
	switch(e)
	{
	case eLingShanObjType_Invalid:
		return "eLingShanObjType_Invalid";
	case eLingShanObjType_Player:
		return "eLingShanObjType_Player";
	case eLingShanObjType_Box:
		return "eLingShanObjType_Box";
	case eLingShanObjType_Monster:
		return "eLingShanObjType_Monster";
	case eObjType_End:
		return "eObjType_End";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, ELingShanObjType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, ELingShanObjType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eLingShanObjType_Invalid", eLingShanObjType_Invalid));
		mapStr2Val.insert(make_pair("eLingShanObjType_Player", eLingShanObjType_Player));
		mapStr2Val.insert(make_pair("eLingShanObjType_Box", eLingShanObjType_Box));
		mapStr2Val.insert(make_pair("eLingShanObjType_Monster", eLingShanObjType_Monster));
		mapStr2Val.insert(make_pair("eObjType_End", eObjType_End));
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

const char* EnumValToStr(ELingShanPrizeType e)
{
	switch(e)
	{
	case eLingShanPrizeType_Invalid:
		return "eLingShanPrizeType_Invalid";
	case eLingShanPrizeType_PickNormalBox:
		return "eLingShanPrizeType_PickNormalBox";
	case eLingShanPrizeType_PickGodBox:
		return "eLingShanPrizeType_PickGodBox";
	case eLingShanPrizeType_MoveByGodBox:
		return "eLingShanPrizeType_MoveByGodBox";
	case eLingShanPrizeType_Win:
		return "eLingShanPrizeType_Win";
	case eLingShanPrizeType_Fail:
		return "eLingShanPrizeType_Fail";
	case eLingShanPrizeType_End:
		return "eLingShanPrizeType_End";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, ELingShanPrizeType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, ELingShanPrizeType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eLingShanPrizeType_Invalid", eLingShanPrizeType_Invalid));
		mapStr2Val.insert(make_pair("eLingShanPrizeType_PickNormalBox", eLingShanPrizeType_PickNormalBox));
		mapStr2Val.insert(make_pair("eLingShanPrizeType_PickGodBox", eLingShanPrizeType_PickGodBox));
		mapStr2Val.insert(make_pair("eLingShanPrizeType_MoveByGodBox", eLingShanPrizeType_MoveByGodBox));
		mapStr2Val.insert(make_pair("eLingShanPrizeType_Win", eLingShanPrizeType_Win));
		mapStr2Val.insert(make_pair("eLingShanPrizeType_Fail", eLingShanPrizeType_Fail));
		mapStr2Val.insert(make_pair("eLingShanPrizeType_End", eLingShanPrizeType_End));
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

const char* EnumValToStr(ECollideType e)
{
	switch(e)
	{
	case eCollideType_Invalid:
		return "eCollideType_Invalid";
	case eCollideType_Path:
		return "eCollideType_Path";
	case eCollideType_Grid:
		return "eCollideType_Grid";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, ECollideType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, ECollideType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eCollideType_Invalid", eCollideType_Invalid));
		mapStr2Val.insert(make_pair("eCollideType_Path", eCollideType_Path));
		mapStr2Val.insert(make_pair("eCollideType_Grid", eCollideType_Grid));
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

STakePrizeLog::STakePrizeLog() : eType((ELingShanPrizeType)0), wTakeBoxCount(0), qwReportID(0), fHPRate(0), dwSuiYuan(0), 
			eCollideType((ECollideType)0) { }

STakePrizeLog::STakePrizeLog(ELingShanPrizeType eType_, UINT16 wTakeBoxCount_, const std::string& strFailName_, UINT64 qwReportID_, float fHPRate_, 
			UINT32 dwSuiYuan_, ECollideType eCollideType_)
			: eType(eType_), wTakeBoxCount(wTakeBoxCount_), strFailName(strFailName_), qwReportID(qwReportID_), fHPRate(fHPRate_), 
			dwSuiYuan(dwSuiYuan_), eCollideType(eCollideType_) { }

STakePrizeLog::STakePrizeLog(STakePrizeLog&& src) : eType(src.eType), wTakeBoxCount(src.wTakeBoxCount), strFailName(move(src.strFailName)), qwReportID(src.qwReportID), fHPRate(src.fHPRate), 
			dwSuiYuan(src.dwSuiYuan), eCollideType(src.eCollideType) { }

STakePrizeLog& STakePrizeLog::operator=(STakePrizeLog&& rhs)
{
	if(this != &rhs)
	{
		this->~STakePrizeLog();
		new (this) STakePrizeLog(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, STakePrizeLog& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (UINT8&)s.eType;
	src >> s.wTakeBoxCount;
	src >> s.strFailName;
	src >> s.qwReportID;
	src >> s.fHPRate;
	src >> s.dwSuiYuan;
	src >> (UINT8&)s.eCollideType;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const STakePrizeLog& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (UINT8&)s.eType;
	src << s.wTakeBoxCount;
	src << s.strFailName;
	src << s.qwReportID;
	src << s.fHPRate;
	src << s.dwSuiYuan;
	src << (UINT8&)s.eCollideType;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, STakePrizeLog& s)
{
	if(strcmp(rElement.Value(), "STakePrizeLog") != 0)
	{
		LOG_CRI << "rElement is not STakePrizeLog!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "ELingShanPrizeType") != 0)
	{
		LOG_CRI << "pElemChild is not ELingShanPrizeType!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eType") != 0)
	{
		LOG_CRI << "Attribute: name is not eType!";
		return false;
	}
	const char* pszVal_eType = pElemChild->Attribute("value");
	if(pszVal_eType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!EnumStrToVal(pszVal_eType, s.eType))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wTakeBoxCount is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wTakeBoxCount") != 0)
	{
		LOG_CRI << "Attribute: name is not wTakeBoxCount!";
		return false;
	}
	const char* pszVal_wTakeBoxCount = pElemChild->Attribute("value");
	if(pszVal_wTakeBoxCount == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wTakeBoxCount, s.wTakeBoxCount))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strFailName is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strFailName") != 0)
	{
		LOG_CRI << "Attribute: name is not strFailName!";
		return false;
	}
	const char* pszVal_strFailName = pElemChild->Attribute("value");
	if(pszVal_strFailName == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strFailName = pszVal_strFailName;
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
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for fHPRate is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "float") != 0)
	{
		LOG_CRI << "pElemChild is not float!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "fHPRate") != 0)
	{
		LOG_CRI << "Attribute: name is not fHPRate!";
		return false;
	}
	const char* pszVal_fHPRate = pElemChild->Attribute("value");
	if(pszVal_fHPRate == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_fHPRate, s.fHPRate))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwSuiYuan is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwSuiYuan") != 0)
	{
		LOG_CRI << "Attribute: name is not dwSuiYuan!";
		return false;
	}
	const char* pszVal_dwSuiYuan = pElemChild->Attribute("value");
	if(pszVal_dwSuiYuan == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwSuiYuan, s.dwSuiYuan))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eCollideType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "ECollideType") != 0)
	{
		LOG_CRI << "pElemChild is not ECollideType!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eCollideType") != 0)
	{
		LOG_CRI << "Attribute: name is not eCollideType!";
		return false;
	}
	const char* pszVal_eCollideType = pElemChild->Attribute("value");
	if(pszVal_eCollideType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!EnumStrToVal(pszVal_eCollideType, s.eCollideType))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const STakePrizeLog& s, TiXmlElement& rElement)
{
	rElement.SetValue("STakePrizeLog");
	rElement.SetAttribute("type", ToUTF8Ptr("玩家获取奖励记录"));
	unique_ptr<TiXmlElement> pElem_eType(new TiXmlElement("ELingShanPrizeType"));
	if(pElem_eType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eType->SetAttribute("name", "eType");
	const char* pszEnum_eType = EnumValToStr(s.eType);
	if(pszEnum_eType == NULL)
	{
		LOG_CRI << "EnumValToStr for ELingShanPrizeType fails!";
		return false;
	}
	pElem_eType->SetAttribute("value", pszEnum_eType);
	pElem_eType->SetAttribute("comment", ToUTF8Ptr("奖励类型"));
	if(rElement.LinkEndChild(pElem_eType.get()) != NULL)
		pElem_eType.release();
	unique_ptr<TiXmlElement> pElem_wTakeBoxCount(new TiXmlElement("UINT16"));
	if(pElem_wTakeBoxCount == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wTakeBoxCount->SetAttribute("name", "wTakeBoxCount");
	pElem_wTakeBoxCount->SetAttribute("value", NumberToString(s.wTakeBoxCount).c_str());
	pElem_wTakeBoxCount->SetAttribute("comment", ToUTF8Ptr("获得宝箱数量"));
	if(rElement.LinkEndChild(pElem_wTakeBoxCount.get()) != NULL)
		pElem_wTakeBoxCount.release();
	unique_ptr<TiXmlElement> pElem_strFailName(new TiXmlElement("string"));
	if(pElem_strFailName == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strFailName->SetAttribute("name", "strFailName");
	pElem_strFailName->SetAttribute("value", s.strFailName.c_str());
	pElem_strFailName->SetAttribute("comment", ToUTF8Ptr("敌对玩家"));
	if(rElement.LinkEndChild(pElem_strFailName.get()) != NULL)
		pElem_strFailName.release();
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
	unique_ptr<TiXmlElement> pElem_fHPRate(new TiXmlElement("float"));
	if(pElem_fHPRate == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_fHPRate->SetAttribute("name", "fHPRate");
	pElem_fHPRate->SetAttribute("value", NumberToString(s.fHPRate).c_str());
	pElem_fHPRate->SetAttribute("comment", ToUTF8Ptr("最终血量"));
	if(rElement.LinkEndChild(pElem_fHPRate.get()) != NULL)
		pElem_fHPRate.release();
	unique_ptr<TiXmlElement> pElem_dwSuiYuan(new TiXmlElement("UINT32"));
	if(pElem_dwSuiYuan == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwSuiYuan->SetAttribute("name", "dwSuiYuan");
	pElem_dwSuiYuan->SetAttribute("value", NumberToString(s.dwSuiYuan).c_str());
	pElem_dwSuiYuan->SetAttribute("comment", ToUTF8Ptr("增加的随缘值"));
	if(rElement.LinkEndChild(pElem_dwSuiYuan.get()) != NULL)
		pElem_dwSuiYuan.release();
	unique_ptr<TiXmlElement> pElem_eCollideType(new TiXmlElement("ECollideType"));
	if(pElem_eCollideType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eCollideType->SetAttribute("name", "eCollideType");
	const char* pszEnum_eCollideType = EnumValToStr(s.eCollideType);
	if(pszEnum_eCollideType == NULL)
	{
		LOG_CRI << "EnumValToStr for ECollideType fails!";
		return false;
	}
	pElem_eCollideType->SetAttribute("value", pszEnum_eCollideType);
	pElem_eCollideType->SetAttribute("comment", ToUTF8Ptr("碰撞类型"));
	if(rElement.LinkEndChild(pElem_eCollideType.get()) != NULL)
		pElem_eCollideType.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecTakePrizeLog& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		STakePrizeLog s;
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

bool VectorToXML(const TVecTakePrizeLog& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("STakePrizeLog"));
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

SBoxInfo::SBoxInfo() : wPos(0), dwModelID(0) { }

SBoxInfo::SBoxInfo(UINT16 wPos_, UINT16 dwModelID_) : wPos(wPos_), dwModelID(dwModelID_) { }

CInArchive& operator>>(CInArchive& src, SBoxInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.wPos;
	src >> s.dwModelID;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SBoxInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.wPos;
	src << s.dwModelID;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SBoxInfo& s)
{
	if(strcmp(rElement.Value(), "SBoxInfo") != 0)
	{
		LOG_CRI << "rElement is not SBoxInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wPos is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wPos") != 0)
	{
		LOG_CRI << "Attribute: name is not wPos!";
		return false;
	}
	const char* pszVal_wPos = pElemChild->Attribute("value");
	if(pszVal_wPos == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wPos, s.wPos))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwModelID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwModelID") != 0)
	{
		LOG_CRI << "Attribute: name is not dwModelID!";
		return false;
	}
	const char* pszVal_dwModelID = pElemChild->Attribute("value");
	if(pszVal_dwModelID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwModelID, s.dwModelID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SBoxInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SBoxInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("地图箱子信息"));
	unique_ptr<TiXmlElement> pElem_wPos(new TiXmlElement("UINT16"));
	if(pElem_wPos == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wPos->SetAttribute("name", "wPos");
	pElem_wPos->SetAttribute("value", NumberToString(s.wPos).c_str());
	pElem_wPos->SetAttribute("comment", ToUTF8Ptr("当前所在地图位置"));
	if(rElement.LinkEndChild(pElem_wPos.get()) != NULL)
		pElem_wPos.release();
	unique_ptr<TiXmlElement> pElem_dwModelID(new TiXmlElement("UINT16"));
	if(pElem_dwModelID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwModelID->SetAttribute("name", "dwModelID");
	pElem_dwModelID->SetAttribute("value", NumberToString(s.dwModelID).c_str());
	pElem_dwModelID->SetAttribute("comment", ToUTF8Ptr("物品id"));
	if(rElement.LinkEndChild(pElem_dwModelID.get()) != NULL)
		pElem_dwModelID.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecBoxInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SBoxInfo s;
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

bool VectorToXML(const TVecBoxInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SBoxInfo"));
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

SRoomPlayInfo::SRoomPlayInfo() : qwRoleID(0), dwModelID(0), dwKillCnt(0), bGodBox(false), wPos(0) { }

SRoomPlayInfo::SRoomPlayInfo(UINT64 qwRoleID_, UINT32 dwModelID_, UINT16 dwKillCnt_, bool bGodBox_, UINT16 wPos_)
			: qwRoleID(qwRoleID_), dwModelID(dwModelID_), dwKillCnt(dwKillCnt_), bGodBox(bGodBox_), wPos(wPos_) { }

CInArchive& operator>>(CInArchive& src, SRoomPlayInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwRoleID;
	src >> s.dwModelID;
	src >> s.dwKillCnt;
	src >> s.bGodBox;
	src >> s.wPos;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SRoomPlayInfo& s)
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
	src << s.dwModelID;
	src << s.dwKillCnt;
	src << s.bGodBox;
	src << s.wPos;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SRoomPlayInfo& s)
{
	if(strcmp(rElement.Value(), "SRoomPlayInfo") != 0)
	{
		LOG_CRI << "rElement is not SRoomPlayInfo!";
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
		LOG_CRI << "pElemChild for dwModelID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwModelID") != 0)
	{
		LOG_CRI << "Attribute: name is not dwModelID!";
		return false;
	}
	const char* pszVal_dwModelID = pElemChild->Attribute("value");
	if(pszVal_dwModelID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwModelID, s.dwModelID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwKillCnt is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwKillCnt") != 0)
	{
		LOG_CRI << "Attribute: name is not dwKillCnt!";
		return false;
	}
	const char* pszVal_dwKillCnt = pElemChild->Attribute("value");
	if(pszVal_dwKillCnt == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwKillCnt, s.dwKillCnt))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for bGodBox is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "bool") != 0)
	{
		LOG_CRI << "pElemChild is not bool!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "bGodBox") != 0)
	{
		LOG_CRI << "Attribute: name is not bGodBox!";
		return false;
	}
	const char* pszVal_bGodBox = pElemChild->Attribute("value");
	if(pszVal_bGodBox == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_bGodBox, s.bGodBox))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wPos is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wPos") != 0)
	{
		LOG_CRI << "Attribute: name is not wPos!";
		return false;
	}
	const char* pszVal_wPos = pElemChild->Attribute("value");
	if(pszVal_wPos == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wPos, s.wPos))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SRoomPlayInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SRoomPlayInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("比赛的玩家信息"));
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
	unique_ptr<TiXmlElement> pElem_dwModelID(new TiXmlElement("UINT32"));
	if(pElem_dwModelID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwModelID->SetAttribute("name", "dwModelID");
	pElem_dwModelID->SetAttribute("value", NumberToString(s.dwModelID).c_str());
	pElem_dwModelID->SetAttribute("comment", ToUTF8Ptr("模型id"));
	if(rElement.LinkEndChild(pElem_dwModelID.get()) != NULL)
		pElem_dwModelID.release();
	unique_ptr<TiXmlElement> pElem_dwKillCnt(new TiXmlElement("UINT16"));
	if(pElem_dwKillCnt == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwKillCnt->SetAttribute("name", "dwKillCnt");
	pElem_dwKillCnt->SetAttribute("value", NumberToString(s.dwKillCnt).c_str());
	pElem_dwKillCnt->SetAttribute("comment", ToUTF8Ptr("击杀人数"));
	if(rElement.LinkEndChild(pElem_dwKillCnt.get()) != NULL)
		pElem_dwKillCnt.release();
	unique_ptr<TiXmlElement> pElem_bGodBox(new TiXmlElement("bool"));
	if(pElem_bGodBox == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_bGodBox->SetAttribute("name", "bGodBox");
	pElem_bGodBox->SetAttribute("value", NumberToString(s.bGodBox).c_str());
	pElem_bGodBox->SetAttribute("comment", ToUTF8Ptr("是否带有大宝箱"));
	if(rElement.LinkEndChild(pElem_bGodBox.get()) != NULL)
		pElem_bGodBox.release();
	unique_ptr<TiXmlElement> pElem_wPos(new TiXmlElement("UINT16"));
	if(pElem_wPos == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wPos->SetAttribute("name", "wPos");
	pElem_wPos->SetAttribute("value", NumberToString(s.wPos).c_str());
	pElem_wPos->SetAttribute("comment", ToUTF8Ptr("当前所在地图位置"));
	if(rElement.LinkEndChild(pElem_wPos.get()) != NULL)
		pElem_wPos.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecRoomPlayInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SRoomPlayInfo s;
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

bool VectorToXML(const TVecRoomPlayInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SRoomPlayInfo"));
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

SRoomMonsterInfo::SRoomMonsterInfo() : dwMonsterID(0), dwKillCnt(0), wPos(0) { }

SRoomMonsterInfo::SRoomMonsterInfo(UINT32 dwMonsterID_, UINT16 dwKillCnt_, UINT16 wPos_) : dwMonsterID(dwMonsterID_), dwKillCnt(dwKillCnt_), wPos(wPos_) { }

CInArchive& operator>>(CInArchive& src, SRoomMonsterInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.dwMonsterID;
	src >> s.dwKillCnt;
	src >> s.wPos;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SRoomMonsterInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.dwMonsterID;
	src << s.dwKillCnt;
	src << s.wPos;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SRoomMonsterInfo& s)
{
	if(strcmp(rElement.Value(), "SRoomMonsterInfo") != 0)
	{
		LOG_CRI << "rElement is not SRoomMonsterInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwMonsterID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwMonsterID") != 0)
	{
		LOG_CRI << "Attribute: name is not dwMonsterID!";
		return false;
	}
	const char* pszVal_dwMonsterID = pElemChild->Attribute("value");
	if(pszVal_dwMonsterID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwMonsterID, s.dwMonsterID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwKillCnt is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwKillCnt") != 0)
	{
		LOG_CRI << "Attribute: name is not dwKillCnt!";
		return false;
	}
	const char* pszVal_dwKillCnt = pElemChild->Attribute("value");
	if(pszVal_dwKillCnt == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwKillCnt, s.dwKillCnt))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wPos is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wPos") != 0)
	{
		LOG_CRI << "Attribute: name is not wPos!";
		return false;
	}
	const char* pszVal_wPos = pElemChild->Attribute("value");
	if(pszVal_wPos == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wPos, s.wPos))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SRoomMonsterInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SRoomMonsterInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("地图的怪物信息"));
	unique_ptr<TiXmlElement> pElem_dwMonsterID(new TiXmlElement("UINT32"));
	if(pElem_dwMonsterID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwMonsterID->SetAttribute("name", "dwMonsterID");
	pElem_dwMonsterID->SetAttribute("value", NumberToString(s.dwMonsterID).c_str());
	pElem_dwMonsterID->SetAttribute("comment", ToUTF8Ptr("怪物组id"));
	if(rElement.LinkEndChild(pElem_dwMonsterID.get()) != NULL)
		pElem_dwMonsterID.release();
	unique_ptr<TiXmlElement> pElem_dwKillCnt(new TiXmlElement("UINT16"));
	if(pElem_dwKillCnt == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwKillCnt->SetAttribute("name", "dwKillCnt");
	pElem_dwKillCnt->SetAttribute("value", NumberToString(s.dwKillCnt).c_str());
	pElem_dwKillCnt->SetAttribute("comment", ToUTF8Ptr("击杀人数"));
	if(rElement.LinkEndChild(pElem_dwKillCnt.get()) != NULL)
		pElem_dwKillCnt.release();
	unique_ptr<TiXmlElement> pElem_wPos(new TiXmlElement("UINT16"));
	if(pElem_wPos == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wPos->SetAttribute("name", "wPos");
	pElem_wPos->SetAttribute("value", NumberToString(s.wPos).c_str());
	pElem_wPos->SetAttribute("comment", ToUTF8Ptr("当前所在地图位置"));
	if(rElement.LinkEndChild(pElem_wPos.get()) != NULL)
		pElem_wPos.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecRoomMonsterInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SRoomMonsterInfo s;
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

bool VectorToXML(const TVecRoomMonsterInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SRoomMonsterInfo"));
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

SPlayerMoveInfo::SPlayerMoveInfo() : qwRoleID(0), wSrcPos(0), wDstPos(0) { }

SPlayerMoveInfo::SPlayerMoveInfo(UINT64 qwRoleID_, UINT16 wSrcPos_, UINT16 wDstPos_) : qwRoleID(qwRoleID_), wSrcPos(wSrcPos_), wDstPos(wDstPos_) { }

CInArchive& operator>>(CInArchive& src, SPlayerMoveInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwRoleID;
	src >> s.wSrcPos;
	src >> s.wDstPos;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SPlayerMoveInfo& s)
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
	src << s.wSrcPos;
	src << s.wDstPos;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SPlayerMoveInfo& s)
{
	if(strcmp(rElement.Value(), "SPlayerMoveInfo") != 0)
	{
		LOG_CRI << "rElement is not SPlayerMoveInfo!";
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
		LOG_CRI << "pElemChild for wSrcPos is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wSrcPos") != 0)
	{
		LOG_CRI << "Attribute: name is not wSrcPos!";
		return false;
	}
	const char* pszVal_wSrcPos = pElemChild->Attribute("value");
	if(pszVal_wSrcPos == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wSrcPos, s.wSrcPos))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wDstPos is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wDstPos") != 0)
	{
		LOG_CRI << "Attribute: name is not wDstPos!";
		return false;
	}
	const char* pszVal_wDstPos = pElemChild->Attribute("value");
	if(pszVal_wDstPos == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wDstPos, s.wDstPos))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SPlayerMoveInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SPlayerMoveInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("玩家移动信息"));
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
	unique_ptr<TiXmlElement> pElem_wSrcPos(new TiXmlElement("UINT16"));
	if(pElem_wSrcPos == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wSrcPos->SetAttribute("name", "wSrcPos");
	pElem_wSrcPos->SetAttribute("value", NumberToString(s.wSrcPos).c_str());
	pElem_wSrcPos->SetAttribute("comment", ToUTF8Ptr("当前位置"));
	if(rElement.LinkEndChild(pElem_wSrcPos.get()) != NULL)
		pElem_wSrcPos.release();
	unique_ptr<TiXmlElement> pElem_wDstPos(new TiXmlElement("UINT16"));
	if(pElem_wDstPos == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wDstPos->SetAttribute("name", "wDstPos");
	pElem_wDstPos->SetAttribute("value", NumberToString(s.wDstPos).c_str());
	pElem_wDstPos->SetAttribute("comment", ToUTF8Ptr("目标位置"));
	if(rElement.LinkEndChild(pElem_wDstPos.get()) != NULL)
		pElem_wDstPos.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecPlayerMoveInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SPlayerMoveInfo s;
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

bool VectorToXML(const TVecPlayerMoveInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SPlayerMoveInfo"));
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

SPathCollideInfo::SPathCollideInfo() : wMinPos(0), wMaxtPos(0), qwWinPlayer(0), dwWinKillCnt(0), qwFailPlayer(0) { }

SPathCollideInfo::SPathCollideInfo(UINT16 wMinPos_, UINT16 wMaxtPos_, UINT64 qwWinPlayer_, UINT32 dwWinKillCnt_, UINT64 qwFailPlayer_)
			: wMinPos(wMinPos_), wMaxtPos(wMaxtPos_), qwWinPlayer(qwWinPlayer_), dwWinKillCnt(dwWinKillCnt_), qwFailPlayer(qwFailPlayer_) { }

CInArchive& operator>>(CInArchive& src, SPathCollideInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.wMinPos;
	src >> s.wMaxtPos;
	src >> s.qwWinPlayer;
	src >> s.dwWinKillCnt;
	src >> s.qwFailPlayer;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SPathCollideInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.wMinPos;
	src << s.wMaxtPos;
	src << s.qwWinPlayer;
	src << s.dwWinKillCnt;
	src << s.qwFailPlayer;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SPathCollideInfo& s)
{
	if(strcmp(rElement.Value(), "SPathCollideInfo") != 0)
	{
		LOG_CRI << "rElement is not SPathCollideInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wMinPos is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wMinPos") != 0)
	{
		LOG_CRI << "Attribute: name is not wMinPos!";
		return false;
	}
	const char* pszVal_wMinPos = pElemChild->Attribute("value");
	if(pszVal_wMinPos == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wMinPos, s.wMinPos))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wMaxtPos is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wMaxtPos") != 0)
	{
		LOG_CRI << "Attribute: name is not wMaxtPos!";
		return false;
	}
	const char* pszVal_wMaxtPos = pElemChild->Attribute("value");
	if(pszVal_wMaxtPos == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wMaxtPos, s.wMaxtPos))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwWinPlayer is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwWinPlayer") != 0)
	{
		LOG_CRI << "Attribute: name is not qwWinPlayer!";
		return false;
	}
	const char* pszVal_qwWinPlayer = pElemChild->Attribute("value");
	if(pszVal_qwWinPlayer == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwWinPlayer, s.qwWinPlayer))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwWinKillCnt is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwWinKillCnt") != 0)
	{
		LOG_CRI << "Attribute: name is not dwWinKillCnt!";
		return false;
	}
	const char* pszVal_dwWinKillCnt = pElemChild->Attribute("value");
	if(pszVal_dwWinKillCnt == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwWinKillCnt, s.dwWinKillCnt))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwFailPlayer is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwFailPlayer") != 0)
	{
		LOG_CRI << "Attribute: name is not qwFailPlayer!";
		return false;
	}
	const char* pszVal_qwFailPlayer = pElemChild->Attribute("value");
	if(pszVal_qwFailPlayer == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwFailPlayer, s.qwFailPlayer))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SPathCollideInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SPathCollideInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("玩家路径碰撞信息"));
	unique_ptr<TiXmlElement> pElem_wMinPos(new TiXmlElement("UINT16"));
	if(pElem_wMinPos == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wMinPos->SetAttribute("name", "wMinPos");
	pElem_wMinPos->SetAttribute("value", NumberToString(s.wMinPos).c_str());
	pElem_wMinPos->SetAttribute("comment", ToUTF8Ptr("小编号位置"));
	if(rElement.LinkEndChild(pElem_wMinPos.get()) != NULL)
		pElem_wMinPos.release();
	unique_ptr<TiXmlElement> pElem_wMaxtPos(new TiXmlElement("UINT16"));
	if(pElem_wMaxtPos == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wMaxtPos->SetAttribute("name", "wMaxtPos");
	pElem_wMaxtPos->SetAttribute("value", NumberToString(s.wMaxtPos).c_str());
	pElem_wMaxtPos->SetAttribute("comment", ToUTF8Ptr("大编号位置"));
	if(rElement.LinkEndChild(pElem_wMaxtPos.get()) != NULL)
		pElem_wMaxtPos.release();
	unique_ptr<TiXmlElement> pElem_qwWinPlayer(new TiXmlElement("UINT64"));
	if(pElem_qwWinPlayer == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwWinPlayer->SetAttribute("name", "qwWinPlayer");
	pElem_qwWinPlayer->SetAttribute("value", NumberToString(s.qwWinPlayer).c_str());
	pElem_qwWinPlayer->SetAttribute("comment", ToUTF8Ptr("胜利玩家"));
	if(rElement.LinkEndChild(pElem_qwWinPlayer.get()) != NULL)
		pElem_qwWinPlayer.release();
	unique_ptr<TiXmlElement> pElem_dwWinKillCnt(new TiXmlElement("UINT32"));
	if(pElem_dwWinKillCnt == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwWinKillCnt->SetAttribute("name", "dwWinKillCnt");
	pElem_dwWinKillCnt->SetAttribute("value", NumberToString(s.dwWinKillCnt).c_str());
	pElem_dwWinKillCnt->SetAttribute("comment", ToUTF8Ptr("胜利击杀数目"));
	if(rElement.LinkEndChild(pElem_dwWinKillCnt.get()) != NULL)
		pElem_dwWinKillCnt.release();
	unique_ptr<TiXmlElement> pElem_qwFailPlayer(new TiXmlElement("UINT64"));
	if(pElem_qwFailPlayer == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwFailPlayer->SetAttribute("name", "qwFailPlayer");
	pElem_qwFailPlayer->SetAttribute("value", NumberToString(s.qwFailPlayer).c_str());
	pElem_qwFailPlayer->SetAttribute("comment", ToUTF8Ptr("失败玩家"));
	if(rElement.LinkEndChild(pElem_qwFailPlayer.get()) != NULL)
		pElem_qwFailPlayer.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecPathCollideInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SPathCollideInfo s;
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

bool VectorToXML(const TVecPathCollideInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SPathCollideInfo"));
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

SGridCollideInfo::SGridCollideInfo() : wPos(0), qwWinPlayer(0), dwWinKillCnt(0) { }

SGridCollideInfo::SGridCollideInfo(UINT16 wPos_, UINT64 qwWinPlayer_, UINT32 dwWinKillCnt_, const TVecUINT64& vecFailPlayer_) : wPos(wPos_), qwWinPlayer(qwWinPlayer_), dwWinKillCnt(dwWinKillCnt_), vecFailPlayer(vecFailPlayer_) { }

CInArchive& operator>>(CInArchive& src, SGridCollideInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.wPos;
	src >> s.qwWinPlayer;
	src >> s.dwWinKillCnt;
	src >> s.vecFailPlayer;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SGridCollideInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.wPos;
	src << s.qwWinPlayer;
	src << s.dwWinKillCnt;
	src << s.vecFailPlayer;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SGridCollideInfo& s)
{
	if(strcmp(rElement.Value(), "SGridCollideInfo") != 0)
	{
		LOG_CRI << "rElement is not SGridCollideInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wPos is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wPos") != 0)
	{
		LOG_CRI << "Attribute: name is not wPos!";
		return false;
	}
	const char* pszVal_wPos = pElemChild->Attribute("value");
	if(pszVal_wPos == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wPos, s.wPos))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwWinPlayer is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwWinPlayer") != 0)
	{
		LOG_CRI << "Attribute: name is not qwWinPlayer!";
		return false;
	}
	const char* pszVal_qwWinPlayer = pElemChild->Attribute("value");
	if(pszVal_qwWinPlayer == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwWinPlayer, s.qwWinPlayer))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwWinKillCnt is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwWinKillCnt") != 0)
	{
		LOG_CRI << "Attribute: name is not dwWinKillCnt!";
		return false;
	}
	const char* pszVal_dwWinKillCnt = pElemChild->Attribute("value");
	if(pszVal_dwWinKillCnt == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwWinKillCnt, s.dwWinKillCnt))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecFailPlayer is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecUINT64") != 0)
	{
		LOG_CRI << "pElemChild is not TVecUINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecFailPlayer") != 0)
	{
		LOG_CRI << "Attribute: name is not vecFailPlayer!";
		return false;
	}
	const char* pszText_vecFailPlayer = pElemChild->GetText();
	if(pszText_vecFailPlayer != NULL)
		SplitToNumber(pszText_vecFailPlayer, ",", s.vecFailPlayer);
	return true;
}

bool ToXML(const SGridCollideInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SGridCollideInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("玩家格子碰撞信息"));
	unique_ptr<TiXmlElement> pElem_wPos(new TiXmlElement("UINT16"));
	if(pElem_wPos == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wPos->SetAttribute("name", "wPos");
	pElem_wPos->SetAttribute("value", NumberToString(s.wPos).c_str());
	pElem_wPos->SetAttribute("comment", ToUTF8Ptr("碰撞位置"));
	if(rElement.LinkEndChild(pElem_wPos.get()) != NULL)
		pElem_wPos.release();
	unique_ptr<TiXmlElement> pElem_qwWinPlayer(new TiXmlElement("UINT64"));
	if(pElem_qwWinPlayer == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwWinPlayer->SetAttribute("name", "qwWinPlayer");
	pElem_qwWinPlayer->SetAttribute("value", NumberToString(s.qwWinPlayer).c_str());
	pElem_qwWinPlayer->SetAttribute("comment", ToUTF8Ptr("胜利玩家"));
	if(rElement.LinkEndChild(pElem_qwWinPlayer.get()) != NULL)
		pElem_qwWinPlayer.release();
	unique_ptr<TiXmlElement> pElem_dwWinKillCnt(new TiXmlElement("UINT32"));
	if(pElem_dwWinKillCnt == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwWinKillCnt->SetAttribute("name", "dwWinKillCnt");
	pElem_dwWinKillCnt->SetAttribute("value", NumberToString(s.dwWinKillCnt).c_str());
	pElem_dwWinKillCnt->SetAttribute("comment", ToUTF8Ptr("击杀数目"));
	if(rElement.LinkEndChild(pElem_dwWinKillCnt.get()) != NULL)
		pElem_dwWinKillCnt.release();
	unique_ptr<TiXmlElement> pElem_vecFailPlayer(new TiXmlElement("TVecUINT64"));
	if(pElem_vecFailPlayer == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecFailPlayer->SetAttribute("name", "vecFailPlayer");
	string strText_vecFailPlayer;
	for(size_t i = 0; i < s.vecFailPlayer.size(); ++i)
	{
		if(i > 0)
			strText_vecFailPlayer += ", ";
		strText_vecFailPlayer += NumberToString(s.vecFailPlayer[i]);
	}
	unique_ptr<TiXmlText> pText_vecFailPlayer(new TiXmlText(strText_vecFailPlayer.c_str()));
	if(pText_vecFailPlayer == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(pElem_vecFailPlayer->LinkEndChild(pText_vecFailPlayer.get()) != NULL)
		pText_vecFailPlayer.release();
	pElem_vecFailPlayer->SetAttribute("comment", ToUTF8Ptr("失败玩家列表"));
	if(rElement.LinkEndChild(pElem_vecFailPlayer.get()) != NULL)
		pElem_vecFailPlayer.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecGridCollideInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SGridCollideInfo s;
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

bool VectorToXML(const TVecGridCollideInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SGridCollideInfo"));
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

SPlayerFighterLog::SPlayerFighterLog() : qwEnemy(0), qwReportID(0), bWin(false) { }

SPlayerFighterLog::SPlayerFighterLog(UINT64 qwEnemy_, UINT64 qwReportID_, bool bWin_) : qwEnemy(qwEnemy_), qwReportID(qwReportID_), bWin(bWin_) { }

CInArchive& operator>>(CInArchive& src, SPlayerFighterLog& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwEnemy;
	src >> s.qwReportID;
	src >> s.bWin;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SPlayerFighterLog& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.qwEnemy;
	src << s.qwReportID;
	src << s.bWin;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SPlayerFighterLog& s)
{
	if(strcmp(rElement.Value(), "SPlayerFighterLog") != 0)
	{
		LOG_CRI << "rElement is not SPlayerFighterLog!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwEnemy is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwEnemy") != 0)
	{
		LOG_CRI << "Attribute: name is not qwEnemy!";
		return false;
	}
	const char* pszVal_qwEnemy = pElemChild->Attribute("value");
	if(pszVal_qwEnemy == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwEnemy, s.qwEnemy))
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
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for bWin is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "bool") != 0)
	{
		LOG_CRI << "pElemChild is not bool!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "bWin") != 0)
	{
		LOG_CRI << "Attribute: name is not bWin!";
		return false;
	}
	const char* pszVal_bWin = pElemChild->Attribute("value");
	if(pszVal_bWin == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_bWin, s.bWin))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SPlayerFighterLog& s, TiXmlElement& rElement)
{
	rElement.SetValue("SPlayerFighterLog");
	rElement.SetAttribute("type", ToUTF8Ptr("玩家战斗信息（目前不需要战斗日志)"));
	unique_ptr<TiXmlElement> pElem_qwEnemy(new TiXmlElement("UINT64"));
	if(pElem_qwEnemy == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwEnemy->SetAttribute("name", "qwEnemy");
	pElem_qwEnemy->SetAttribute("value", NumberToString(s.qwEnemy).c_str());
	pElem_qwEnemy->SetAttribute("comment", ToUTF8Ptr("战斗玩家"));
	if(rElement.LinkEndChild(pElem_qwEnemy.get()) != NULL)
		pElem_qwEnemy.release();
	unique_ptr<TiXmlElement> pElem_qwReportID(new TiXmlElement("UINT64"));
	if(pElem_qwReportID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwReportID->SetAttribute("name", "qwReportID");
	pElem_qwReportID->SetAttribute("value", NumberToString(s.qwReportID).c_str());
	pElem_qwReportID->SetAttribute("comment", ToUTF8Ptr("战斗日志"));
	if(rElement.LinkEndChild(pElem_qwReportID.get()) != NULL)
		pElem_qwReportID.release();
	unique_ptr<TiXmlElement> pElem_bWin(new TiXmlElement("bool"));
	if(pElem_bWin == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_bWin->SetAttribute("name", "bWin");
	pElem_bWin->SetAttribute("value", NumberToString(s.bWin).c_str());
	pElem_bWin->SetAttribute("comment", ToUTF8Ptr("是否胜利"));
	if(rElement.LinkEndChild(pElem_bWin.get()) != NULL)
		pElem_bWin.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecPlayerFighterLog& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SPlayerFighterLog s;
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

bool VectorToXML(const TVecPlayerFighterLog& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SPlayerFighterLog"));
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

SRoomInfo::SRoomInfo() : wRoomID(0), wPlayerCnt(0) { }

SRoomInfo::SRoomInfo(UINT16 wRoomID_, UINT16 wPlayerCnt_) : wRoomID(wRoomID_), wPlayerCnt(wPlayerCnt_) { }

CInArchive& operator>>(CInArchive& src, SRoomInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.wRoomID;
	src >> s.wPlayerCnt;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SRoomInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.wRoomID;
	src << s.wPlayerCnt;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SRoomInfo& s)
{
	if(strcmp(rElement.Value(), "SRoomInfo") != 0)
	{
		LOG_CRI << "rElement is not SRoomInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wRoomID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wRoomID") != 0)
	{
		LOG_CRI << "Attribute: name is not wRoomID!";
		return false;
	}
	const char* pszVal_wRoomID = pElemChild->Attribute("value");
	if(pszVal_wRoomID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wRoomID, s.wRoomID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wPlayerCnt is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wPlayerCnt") != 0)
	{
		LOG_CRI << "Attribute: name is not wPlayerCnt!";
		return false;
	}
	const char* pszVal_wPlayerCnt = pElemChild->Attribute("value");
	if(pszVal_wPlayerCnt == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wPlayerCnt, s.wPlayerCnt))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SRoomInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SRoomInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("房间信息"));
	unique_ptr<TiXmlElement> pElem_wRoomID(new TiXmlElement("UINT16"));
	if(pElem_wRoomID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wRoomID->SetAttribute("name", "wRoomID");
	pElem_wRoomID->SetAttribute("value", NumberToString(s.wRoomID).c_str());
	pElem_wRoomID->SetAttribute("comment", ToUTF8Ptr("房间编号"));
	if(rElement.LinkEndChild(pElem_wRoomID.get()) != NULL)
		pElem_wRoomID.release();
	unique_ptr<TiXmlElement> pElem_wPlayerCnt(new TiXmlElement("UINT16"));
	if(pElem_wPlayerCnt == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wPlayerCnt->SetAttribute("name", "wPlayerCnt");
	pElem_wPlayerCnt->SetAttribute("value", NumberToString(s.wPlayerCnt).c_str());
	pElem_wPlayerCnt->SetAttribute("comment", ToUTF8Ptr("房间人数"));
	if(rElement.LinkEndChild(pElem_wPlayerCnt.get()) != NULL)
		pElem_wPlayerCnt.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecRoomInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SRoomInfo s;
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

bool VectorToXML(const TVecRoomInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SRoomInfo"));
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

SPlayMovieInfo::SPlayMovieInfo() { }

SPlayMovieInfo::SPlayMovieInfo(const TVecPlayerMoveInfo& vecPlayerMoveInfo_, const TVecPathCollideInfo& vecPathCollideInfo_, const TVecGridCollideInfo& vecGridCollideInfo_, const TVecRoomPlayInfo& vecRoomPlayInfo_) : vecPlayerMoveInfo(vecPlayerMoveInfo_), vecPathCollideInfo(vecPathCollideInfo_), vecGridCollideInfo(vecGridCollideInfo_), vecRoomPlayInfo(vecRoomPlayInfo_) { }

SPlayMovieInfo::SPlayMovieInfo(SPlayMovieInfo&& src) : vecPlayerMoveInfo(move(src.vecPlayerMoveInfo)), vecPathCollideInfo(move(src.vecPathCollideInfo)), vecGridCollideInfo(move(src.vecGridCollideInfo)), vecRoomPlayInfo(move(src.vecRoomPlayInfo)) { }

SPlayMovieInfo& SPlayMovieInfo::operator=(SPlayMovieInfo&& rhs)
{
	if(this != &rhs)
	{
		this->~SPlayMovieInfo();
		new (this) SPlayMovieInfo(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SPlayMovieInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.vecPlayerMoveInfo;
	src >> s.vecPathCollideInfo;
	src >> s.vecGridCollideInfo;
	src >> s.vecRoomPlayInfo;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SPlayMovieInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.vecPlayerMoveInfo;
	src << s.vecPathCollideInfo;
	src << s.vecGridCollideInfo;
	src << s.vecRoomPlayInfo;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SPlayMovieInfo& s)
{
	if(strcmp(rElement.Value(), "SPlayMovieInfo") != 0)
	{
		LOG_CRI << "rElement is not SPlayMovieInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecPlayerMoveInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecPlayerMoveInfo") != 0)
	{
		LOG_CRI << "pElemChild is not TVecPlayerMoveInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecPlayerMoveInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not vecPlayerMoveInfo!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecPlayerMoveInfo))
	{
		LOG_CRI << "VectorFromXML for vecPlayerMoveInfo fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecPathCollideInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecPathCollideInfo") != 0)
	{
		LOG_CRI << "pElemChild is not TVecPathCollideInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecPathCollideInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not vecPathCollideInfo!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecPathCollideInfo))
	{
		LOG_CRI << "VectorFromXML for vecPathCollideInfo fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecGridCollideInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecGridCollideInfo") != 0)
	{
		LOG_CRI << "pElemChild is not TVecGridCollideInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecGridCollideInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not vecGridCollideInfo!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecGridCollideInfo))
	{
		LOG_CRI << "VectorFromXML for vecGridCollideInfo fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecRoomPlayInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecRoomPlayInfo") != 0)
	{
		LOG_CRI << "pElemChild is not TVecRoomPlayInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecRoomPlayInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not vecRoomPlayInfo!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecRoomPlayInfo))
	{
		LOG_CRI << "VectorFromXML for vecRoomPlayInfo fails!";
		return false;
	}
	return true;
}

bool ToXML(const SPlayMovieInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SPlayMovieInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("动画播放信息"));
	unique_ptr<TiXmlElement> pElem_vecPlayerMoveInfo(new TiXmlElement("TVecPlayerMoveInfo"));
	if(pElem_vecPlayerMoveInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecPlayerMoveInfo->SetAttribute("name", "vecPlayerMoveInfo");
	if(!VectorToXML(s.vecPlayerMoveInfo, *pElem_vecPlayerMoveInfo))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecPlayerMoveInfo->SetAttribute("comment", ToUTF8Ptr("玩家移动路径"));
	if(rElement.LinkEndChild(pElem_vecPlayerMoveInfo.get()) != NULL)
		pElem_vecPlayerMoveInfo.release();
	unique_ptr<TiXmlElement> pElem_vecPathCollideInfo(new TiXmlElement("TVecPathCollideInfo"));
	if(pElem_vecPathCollideInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecPathCollideInfo->SetAttribute("name", "vecPathCollideInfo");
	if(!VectorToXML(s.vecPathCollideInfo, *pElem_vecPathCollideInfo))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecPathCollideInfo->SetAttribute("comment", ToUTF8Ptr("路径碰撞"));
	if(rElement.LinkEndChild(pElem_vecPathCollideInfo.get()) != NULL)
		pElem_vecPathCollideInfo.release();
	unique_ptr<TiXmlElement> pElem_vecGridCollideInfo(new TiXmlElement("TVecGridCollideInfo"));
	if(pElem_vecGridCollideInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecGridCollideInfo->SetAttribute("name", "vecGridCollideInfo");
	if(!VectorToXML(s.vecGridCollideInfo, *pElem_vecGridCollideInfo))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecGridCollideInfo->SetAttribute("comment", ToUTF8Ptr("格子碰撞"));
	if(rElement.LinkEndChild(pElem_vecGridCollideInfo.get()) != NULL)
		pElem_vecGridCollideInfo.release();
	unique_ptr<TiXmlElement> pElem_vecRoomPlayInfo(new TiXmlElement("TVecRoomPlayInfo"));
	if(pElem_vecRoomPlayInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecRoomPlayInfo->SetAttribute("name", "vecRoomPlayInfo");
	if(!VectorToXML(s.vecRoomPlayInfo, *pElem_vecRoomPlayInfo))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecRoomPlayInfo->SetAttribute("comment", ToUTF8Ptr("玩家信息"));
	if(rElement.LinkEndChild(pElem_vecRoomPlayInfo.get()) != NULL)
		pElem_vecRoomPlayInfo.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecPlayMovieInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SPlayMovieInfo s;
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

bool VectorToXML(const TVecPlayMovieInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SPlayMovieInfo"));
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

} //namespace NLingShanProt
