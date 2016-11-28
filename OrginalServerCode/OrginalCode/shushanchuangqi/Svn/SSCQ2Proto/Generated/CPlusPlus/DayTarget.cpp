/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    DayTarget.cpp
//  Purpose:      七日目标活动
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "DayTarget.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NDayTarget
{

#ifdef PROT_USE_XML

const char* EnumValToStr(EDayTargetRet e)
{
	switch(e)
	{
	case eDayTargetRet_Sucess:
		return "eDayTargetRet_Sucess";
	case eDayTargetRet_NotFinish:
		return "eDayTargetRet_NotFinish";
	case eDayTargetRet_DayLimit:
		return "eDayTargetRet_DayLimit";
	case eDayTargetRet_TakePrized:
		return "eDayTargetRet_TakePrized";
	case eDayTargetRet_CFGError:
		return "eDayTargetRet_CFGError";
	case eDayTargetRet_PackFull:
		return "eDayTargetRet_PackFull";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EDayTargetRet& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EDayTargetRet> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eDayTargetRet_Sucess", eDayTargetRet_Sucess));
		mapStr2Val.insert(make_pair("eDayTargetRet_NotFinish", eDayTargetRet_NotFinish));
		mapStr2Val.insert(make_pair("eDayTargetRet_DayLimit", eDayTargetRet_DayLimit));
		mapStr2Val.insert(make_pair("eDayTargetRet_TakePrized", eDayTargetRet_TakePrized));
		mapStr2Val.insert(make_pair("eDayTargetRet_CFGError", eDayTargetRet_CFGError));
		mapStr2Val.insert(make_pair("eDayTargetRet_PackFull", eDayTargetRet_PackFull));
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

const char* EnumValToStr(EDayTargeTasktStatus e)
{
	switch(e)
	{
	case eDayTargetTaskStatus_Init:
		return "eDayTargetTaskStatus_Init";
	case eDayTargetTaskStatus_Finish:
		return "eDayTargetTaskStatus_Finish";
	case eDayTargetTaskStatus_TakePrized:
		return "eDayTargetTaskStatus_TakePrized";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EDayTargeTasktStatus& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EDayTargeTasktStatus> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eDayTargetTaskStatus_Init", eDayTargetTaskStatus_Init));
		mapStr2Val.insert(make_pair("eDayTargetTaskStatus_Finish", eDayTargetTaskStatus_Finish));
		mapStr2Val.insert(make_pair("eDayTargetTaskStatus_TakePrized", eDayTargetTaskStatus_TakePrized));
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

SDayTargetTask::SDayTargetTask() : wTaskID(0), eTaskStatus((EDayTargeTasktStatus)0), dwParam(0) { }

SDayTargetTask::SDayTargetTask(UINT16 wTaskID_, EDayTargeTasktStatus eTaskStatus_, UINT32 dwParam_) : wTaskID(wTaskID_), eTaskStatus(eTaskStatus_), dwParam(dwParam_) { }

CInArchive& operator>>(CInArchive& src, SDayTargetTask& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.wTaskID;
	src >> (UINT8&)s.eTaskStatus;
	src >> s.dwParam;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SDayTargetTask& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.wTaskID;
	src << (UINT8&)s.eTaskStatus;
	src << s.dwParam;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SDayTargetTask& s)
{
	if(strcmp(rElement.Value(), "SDayTargetTask") != 0)
	{
		LOG_CRI << "rElement is not SDayTargetTask!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wTaskID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wTaskID") != 0)
	{
		LOG_CRI << "Attribute: name is not wTaskID!";
		return false;
	}
	const char* pszVal_wTaskID = pElemChild->Attribute("value");
	if(pszVal_wTaskID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wTaskID, s.wTaskID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eTaskStatus is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "EDayTargeTasktStatus") != 0)
	{
		LOG_CRI << "pElemChild is not EDayTargeTasktStatus!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eTaskStatus") != 0)
	{
		LOG_CRI << "Attribute: name is not eTaskStatus!";
		return false;
	}
	const char* pszVal_eTaskStatus = pElemChild->Attribute("value");
	if(pszVal_eTaskStatus == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!EnumStrToVal(pszVal_eTaskStatus, s.eTaskStatus))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwParam is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwParam") != 0)
	{
		LOG_CRI << "Attribute: name is not dwParam!";
		return false;
	}
	const char* pszVal_dwParam = pElemChild->Attribute("value");
	if(pszVal_dwParam == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwParam, s.dwParam))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SDayTargetTask& s, TiXmlElement& rElement)
{
	rElement.SetValue("SDayTargetTask");
	rElement.SetAttribute("type", ToUTF8Ptr("任务信息列表"));
	unique_ptr<TiXmlElement> pElem_wTaskID(new TiXmlElement("UINT16"));
	if(pElem_wTaskID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wTaskID->SetAttribute("name", "wTaskID");
	pElem_wTaskID->SetAttribute("value", NumberToString(s.wTaskID).c_str());
	pElem_wTaskID->SetAttribute("comment", ToUTF8Ptr("任务ID"));
	if(rElement.LinkEndChild(pElem_wTaskID.get()) != NULL)
		pElem_wTaskID.release();
	unique_ptr<TiXmlElement> pElem_eTaskStatus(new TiXmlElement("EDayTargeTasktStatus"));
	if(pElem_eTaskStatus == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eTaskStatus->SetAttribute("name", "eTaskStatus");
	const char* pszEnum_eTaskStatus = EnumValToStr(s.eTaskStatus);
	if(pszEnum_eTaskStatus == NULL)
	{
		LOG_CRI << "EnumValToStr for EDayTargeTasktStatus fails!";
		return false;
	}
	pElem_eTaskStatus->SetAttribute("value", pszEnum_eTaskStatus);
	pElem_eTaskStatus->SetAttribute("comment", ToUTF8Ptr("任务状态"));
	if(rElement.LinkEndChild(pElem_eTaskStatus.get()) != NULL)
		pElem_eTaskStatus.release();
	unique_ptr<TiXmlElement> pElem_dwParam(new TiXmlElement("UINT32"));
	if(pElem_dwParam == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwParam->SetAttribute("name", "dwParam");
	pElem_dwParam->SetAttribute("value", NumberToString(s.dwParam).c_str());
	pElem_dwParam->SetAttribute("comment", ToUTF8Ptr("进度"));
	if(rElement.LinkEndChild(pElem_dwParam.get()) != NULL)
		pElem_dwParam.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecDayTargetTask& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SDayTargetTask s;
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

bool VectorToXML(const TVecDayTargetTask& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SDayTargetTask"));
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

} //namespace NDayTarget
