/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    GroupTaskProt.cpp
//  Purpose:      师门任务协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "GroupTaskProt.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NGroupTaskProt
{

#ifdef PROT_USE_XML

const char* EnumValToStr(EGroupTaskResult e)
{
	switch(e)
	{
	case eGroupTaskSucceed:
		return "eGroupTaskSucceed";
	case eGroupTaskLowMoney:
		return "eGroupTaskLowMoney";
	case eBuyTimesUpLimit:
		return "eBuyTimesUpLimit";
	case eGroupSaveTimesUpLimit:
		return "eGroupSaveTimesUpLimit";
	case eGroupTaskErrOther:
		return "eGroupTaskErrOther";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EGroupTaskResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EGroupTaskResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eGroupTaskSucceed", eGroupTaskSucceed));
		mapStr2Val.insert(make_pair("eGroupTaskLowMoney", eGroupTaskLowMoney));
		mapStr2Val.insert(make_pair("eBuyTimesUpLimit", eBuyTimesUpLimit));
		mapStr2Val.insert(make_pair("eGroupSaveTimesUpLimit", eGroupSaveTimesUpLimit));
		mapStr2Val.insert(make_pair("eGroupTaskErrOther", eGroupTaskErrOther));
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

const char* EnumValToStr(EGroupStudyState e)
{
	switch(e)
	{
	case eCanStudy:
		return "eCanStudy";
	case eStudied:
		return "eStudied";
	case eCanChallenge:
		return "eCanChallenge";
	case eChallenging:
		return "eChallenging";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EGroupStudyState& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EGroupStudyState> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eCanStudy", eCanStudy));
		mapStr2Val.insert(make_pair("eStudied", eStudied));
		mapStr2Val.insert(make_pair("eCanChallenge", eCanChallenge));
		mapStr2Val.insert(make_pair("eChallenging", eChallenging));
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

const char* EnumValToStr(EGroupTaskState e)
{
	switch(e)
	{
	case eNone:
		return "eNone";
	case eAccept:
		return "eAccept";
	case eFinish:
		return "eFinish";
	case eFal:
		return "eFal";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EGroupTaskState& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EGroupTaskState> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eNone", eNone));
		mapStr2Val.insert(make_pair("eAccept", eAccept));
		mapStr2Val.insert(make_pair("eFinish", eFinish));
		mapStr2Val.insert(make_pair("eFal", eFal));
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

SGroupTask::SGroupTask() : dwTaskId(0), eGroupTaskState((EGroupTaskState)0) { }

SGroupTask::SGroupTask(UINT32 dwTaskId_, EGroupTaskState eGroupTaskState_) : dwTaskId(dwTaskId_), eGroupTaskState(eGroupTaskState_) { }

CInArchive& operator>>(CInArchive& src, SGroupTask& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.dwTaskId;
	src >> (UINT8&)s.eGroupTaskState;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SGroupTask& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.dwTaskId;
	src << (UINT8&)s.eGroupTaskState;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SGroupTask& s)
{
	if(strcmp(rElement.Value(), "SGroupTask") != 0)
	{
		LOG_CRI << "rElement is not SGroupTask!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwTaskId is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwTaskId") != 0)
	{
		LOG_CRI << "Attribute: name is not dwTaskId!";
		return false;
	}
	const char* pszVal_dwTaskId = pElemChild->Attribute("value");
	if(pszVal_dwTaskId == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwTaskId, s.dwTaskId))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eGroupTaskState is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "EGroupTaskState") != 0)
	{
		LOG_CRI << "pElemChild is not EGroupTaskState!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eGroupTaskState") != 0)
	{
		LOG_CRI << "Attribute: name is not eGroupTaskState!";
		return false;
	}
	const char* pszVal_eGroupTaskState = pElemChild->Attribute("value");
	if(pszVal_eGroupTaskState == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!EnumStrToVal(pszVal_eGroupTaskState, s.eGroupTaskState))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SGroupTask& s, TiXmlElement& rElement)
{
	rElement.SetValue("SGroupTask");
	rElement.SetAttribute("type", ToUTF8Ptr("挑战的任务状态"));
	unique_ptr<TiXmlElement> pElem_dwTaskId(new TiXmlElement("UINT32"));
	if(pElem_dwTaskId == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwTaskId->SetAttribute("name", "dwTaskId");
	pElem_dwTaskId->SetAttribute("value", NumberToString(s.dwTaskId).c_str());
	pElem_dwTaskId->SetAttribute("comment", ToUTF8Ptr("任务的ID"));
	if(rElement.LinkEndChild(pElem_dwTaskId.get()) != NULL)
		pElem_dwTaskId.release();
	unique_ptr<TiXmlElement> pElem_eGroupTaskState(new TiXmlElement("EGroupTaskState"));
	if(pElem_eGroupTaskState == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eGroupTaskState->SetAttribute("name", "eGroupTaskState");
	const char* pszEnum_eGroupTaskState = EnumValToStr(s.eGroupTaskState);
	if(pszEnum_eGroupTaskState == NULL)
	{
		LOG_CRI << "EnumValToStr for EGroupTaskState fails!";
		return false;
	}
	pElem_eGroupTaskState->SetAttribute("value", pszEnum_eGroupTaskState);
	pElem_eGroupTaskState->SetAttribute("comment", ToUTF8Ptr("当前刷的任务信息"));
	if(rElement.LinkEndChild(pElem_eGroupTaskState.get()) != NULL)
		pElem_eGroupTaskState.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecGroupTask& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SGroupTask s;
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

bool VectorToXML(const TVecGroupTask& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SGroupTask"));
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

SGroupTaskInfoForClient::SGroupTaskInfoForClient() : eStudyState((EGroupStudyState)0), dwGroupRepute(0), dwGroupLevel(0), byFinishTask(0), byAcceptTaskTimes(0), 
			byBuyTimesToday(0), byVIPTaskTimes(0), byFlushTask(0), byStudyAward(0) { }

SGroupTaskInfoForClient::SGroupTaskInfoForClient(EGroupStudyState eStudyState_, UINT32 dwGroupRepute_, UINT8 dwGroupLevel_, UINT8 byFinishTask_, UINT8 byAcceptTaskTimes_, 
			UINT8 byBuyTimesToday_, UINT8 byVIPTaskTimes_, UINT8 byFlushTask_, UINT8 byStudyAward_, const TVecGroupTask& vecTask_)
			: eStudyState(eStudyState_), dwGroupRepute(dwGroupRepute_), dwGroupLevel(dwGroupLevel_), byFinishTask(byFinishTask_), byAcceptTaskTimes(byAcceptTaskTimes_), 
			byBuyTimesToday(byBuyTimesToday_), byVIPTaskTimes(byVIPTaskTimes_), byFlushTask(byFlushTask_), byStudyAward(byStudyAward_), vecTask(vecTask_) { }

SGroupTaskInfoForClient::SGroupTaskInfoForClient(SGroupTaskInfoForClient&& src) : eStudyState(src.eStudyState), dwGroupRepute(src.dwGroupRepute), dwGroupLevel(src.dwGroupLevel), byFinishTask(src.byFinishTask), byAcceptTaskTimes(src.byAcceptTaskTimes), 
			byBuyTimesToday(src.byBuyTimesToday), byVIPTaskTimes(src.byVIPTaskTimes), byFlushTask(src.byFlushTask), byStudyAward(src.byStudyAward), vecTask(move(src.vecTask)) { }

SGroupTaskInfoForClient& SGroupTaskInfoForClient::operator=(SGroupTaskInfoForClient&& rhs)
{
	if(this != &rhs)
	{
		this->~SGroupTaskInfoForClient();
		new (this) SGroupTaskInfoForClient(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SGroupTaskInfoForClient& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (UINT8&)s.eStudyState;
	src >> s.dwGroupRepute;
	src >> s.dwGroupLevel;
	src >> s.byFinishTask;
	src >> s.byAcceptTaskTimes;
	src >> s.byBuyTimesToday;
	src >> s.byVIPTaskTimes;
	src >> s.byFlushTask;
	src >> s.byStudyAward;
	src >> s.vecTask;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SGroupTaskInfoForClient& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (UINT8&)s.eStudyState;
	src << s.dwGroupRepute;
	src << s.dwGroupLevel;
	src << s.byFinishTask;
	src << s.byAcceptTaskTimes;
	src << s.byBuyTimesToday;
	src << s.byVIPTaskTimes;
	src << s.byFlushTask;
	src << s.byStudyAward;
	src << s.vecTask;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SGroupTaskInfoForClient& s)
{
	if(strcmp(rElement.Value(), "SGroupTaskInfoForClient") != 0)
	{
		LOG_CRI << "rElement is not SGroupTaskInfoForClient!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eStudyState is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "EGroupStudyState") != 0)
	{
		LOG_CRI << "pElemChild is not EGroupStudyState!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eStudyState") != 0)
	{
		LOG_CRI << "Attribute: name is not eStudyState!";
		return false;
	}
	const char* pszVal_eStudyState = pElemChild->Attribute("value");
	if(pszVal_eStudyState == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!EnumStrToVal(pszVal_eStudyState, s.eStudyState))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwGroupRepute is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwGroupRepute") != 0)
	{
		LOG_CRI << "Attribute: name is not dwGroupRepute!";
		return false;
	}
	const char* pszVal_dwGroupRepute = pElemChild->Attribute("value");
	if(pszVal_dwGroupRepute == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwGroupRepute, s.dwGroupRepute))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwGroupLevel is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwGroupLevel") != 0)
	{
		LOG_CRI << "Attribute: name is not dwGroupLevel!";
		return false;
	}
	const char* pszVal_dwGroupLevel = pElemChild->Attribute("value");
	if(pszVal_dwGroupLevel == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwGroupLevel, s.dwGroupLevel))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byFinishTask is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byFinishTask") != 0)
	{
		LOG_CRI << "Attribute: name is not byFinishTask!";
		return false;
	}
	const char* pszVal_byFinishTask = pElemChild->Attribute("value");
	if(pszVal_byFinishTask == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byFinishTask, s.byFinishTask))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byAcceptTaskTimes is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byAcceptTaskTimes") != 0)
	{
		LOG_CRI << "Attribute: name is not byAcceptTaskTimes!";
		return false;
	}
	const char* pszVal_byAcceptTaskTimes = pElemChild->Attribute("value");
	if(pszVal_byAcceptTaskTimes == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byAcceptTaskTimes, s.byAcceptTaskTimes))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byBuyTimesToday is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byBuyTimesToday") != 0)
	{
		LOG_CRI << "Attribute: name is not byBuyTimesToday!";
		return false;
	}
	const char* pszVal_byBuyTimesToday = pElemChild->Attribute("value");
	if(pszVal_byBuyTimesToday == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byBuyTimesToday, s.byBuyTimesToday))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byVIPTaskTimes is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byVIPTaskTimes") != 0)
	{
		LOG_CRI << "Attribute: name is not byVIPTaskTimes!";
		return false;
	}
	const char* pszVal_byVIPTaskTimes = pElemChild->Attribute("value");
	if(pszVal_byVIPTaskTimes == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byVIPTaskTimes, s.byVIPTaskTimes))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byFlushTask is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byFlushTask") != 0)
	{
		LOG_CRI << "Attribute: name is not byFlushTask!";
		return false;
	}
	const char* pszVal_byFlushTask = pElemChild->Attribute("value");
	if(pszVal_byFlushTask == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byFlushTask, s.byFlushTask))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byStudyAward is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byStudyAward") != 0)
	{
		LOG_CRI << "Attribute: name is not byStudyAward!";
		return false;
	}
	const char* pszVal_byStudyAward = pElemChild->Attribute("value");
	if(pszVal_byStudyAward == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byStudyAward, s.byStudyAward))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecTask is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecGroupTask") != 0)
	{
		LOG_CRI << "pElemChild is not TVecGroupTask!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecTask") != 0)
	{
		LOG_CRI << "Attribute: name is not vecTask!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecTask))
	{
		LOG_CRI << "VectorFromXML for vecTask fails!";
		return false;
	}
	return true;
}

bool ToXML(const SGroupTaskInfoForClient& s, TiXmlElement& rElement)
{
	rElement.SetValue("SGroupTaskInfoForClient");
	rElement.SetAttribute("type", ToUTF8Ptr("师门任务信息"));
	unique_ptr<TiXmlElement> pElem_eStudyState(new TiXmlElement("EGroupStudyState"));
	if(pElem_eStudyState == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eStudyState->SetAttribute("name", "eStudyState");
	const char* pszEnum_eStudyState = EnumValToStr(s.eStudyState);
	if(pszEnum_eStudyState == NULL)
	{
		LOG_CRI << "EnumValToStr for EGroupStudyState fails!";
		return false;
	}
	pElem_eStudyState->SetAttribute("value", pszEnum_eStudyState);
	pElem_eStudyState->SetAttribute("comment", ToUTF8Ptr("清修状态"));
	if(rElement.LinkEndChild(pElem_eStudyState.get()) != NULL)
		pElem_eStudyState.release();
	unique_ptr<TiXmlElement> pElem_dwGroupRepute(new TiXmlElement("UINT32"));
	if(pElem_dwGroupRepute == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwGroupRepute->SetAttribute("name", "dwGroupRepute");
	pElem_dwGroupRepute->SetAttribute("value", NumberToString(s.dwGroupRepute).c_str());
	pElem_dwGroupRepute->SetAttribute("comment", ToUTF8Ptr("声望"));
	if(rElement.LinkEndChild(pElem_dwGroupRepute.get()) != NULL)
		pElem_dwGroupRepute.release();
	unique_ptr<TiXmlElement> pElem_dwGroupLevel(new TiXmlElement("UINT8"));
	if(pElem_dwGroupLevel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwGroupLevel->SetAttribute("name", "dwGroupLevel");
	pElem_dwGroupLevel->SetAttribute("value", NumberToString(s.dwGroupLevel).c_str());
	pElem_dwGroupLevel->SetAttribute("comment", ToUTF8Ptr("声望等级"));
	if(rElement.LinkEndChild(pElem_dwGroupLevel.get()) != NULL)
		pElem_dwGroupLevel.release();
	unique_ptr<TiXmlElement> pElem_byFinishTask(new TiXmlElement("UINT8"));
	if(pElem_byFinishTask == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byFinishTask->SetAttribute("name", "byFinishTask");
	pElem_byFinishTask->SetAttribute("value", NumberToString(s.byFinishTask).c_str());
	pElem_byFinishTask->SetAttribute("comment", ToUTF8Ptr("今日完成的师门任务数"));
	if(rElement.LinkEndChild(pElem_byFinishTask.get()) != NULL)
		pElem_byFinishTask.release();
	unique_ptr<TiXmlElement> pElem_byAcceptTaskTimes(new TiXmlElement("UINT8"));
	if(pElem_byAcceptTaskTimes == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byAcceptTaskTimes->SetAttribute("name", "byAcceptTaskTimes");
	pElem_byAcceptTaskTimes->SetAttribute("value", NumberToString(s.byAcceptTaskTimes).c_str());
	pElem_byAcceptTaskTimes->SetAttribute("comment", ToUTF8Ptr("剩余可接任务数"));
	if(rElement.LinkEndChild(pElem_byAcceptTaskTimes.get()) != NULL)
		pElem_byAcceptTaskTimes.release();
	unique_ptr<TiXmlElement> pElem_byBuyTimesToday(new TiXmlElement("UINT8"));
	if(pElem_byBuyTimesToday == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byBuyTimesToday->SetAttribute("name", "byBuyTimesToday");
	pElem_byBuyTimesToday->SetAttribute("value", NumberToString(s.byBuyTimesToday).c_str());
	pElem_byBuyTimesToday->SetAttribute("comment", ToUTF8Ptr("今日购买的任务数"));
	if(rElement.LinkEndChild(pElem_byBuyTimesToday.get()) != NULL)
		pElem_byBuyTimesToday.release();
	unique_ptr<TiXmlElement> pElem_byVIPTaskTimes(new TiXmlElement("UINT8"));
	if(pElem_byVIPTaskTimes == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byVIPTaskTimes->SetAttribute("name", "byVIPTaskTimes");
	pElem_byVIPTaskTimes->SetAttribute("value", NumberToString(s.byVIPTaskTimes).c_str());
	pElem_byVIPTaskTimes->SetAttribute("comment", ToUTF8Ptr("购买的可接任务数"));
	if(rElement.LinkEndChild(pElem_byVIPTaskTimes.get()) != NULL)
		pElem_byVIPTaskTimes.release();
	unique_ptr<TiXmlElement> pElem_byFlushTask(new TiXmlElement("UINT8"));
	if(pElem_byFlushTask == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byFlushTask->SetAttribute("name", "byFlushTask");
	pElem_byFlushTask->SetAttribute("value", NumberToString(s.byFlushTask).c_str());
	pElem_byFlushTask->SetAttribute("comment", ToUTF8Ptr("今日刷新任务列表次数"));
	if(rElement.LinkEndChild(pElem_byFlushTask.get()) != NULL)
		pElem_byFlushTask.release();
	unique_ptr<TiXmlElement> pElem_byStudyAward(new TiXmlElement("UINT8"));
	if(pElem_byStudyAward == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byStudyAward->SetAttribute("name", "byStudyAward");
	pElem_byStudyAward->SetAttribute("value", NumberToString(s.byStudyAward).c_str());
	pElem_byStudyAward->SetAttribute("comment", ToUTF8Ptr("今日领取的清修次数"));
	if(rElement.LinkEndChild(pElem_byStudyAward.get()) != NULL)
		pElem_byStudyAward.release();
	unique_ptr<TiXmlElement> pElem_vecTask(new TiXmlElement("TVecGroupTask"));
	if(pElem_vecTask == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecTask->SetAttribute("name", "vecTask");
	if(!VectorToXML(s.vecTask, *pElem_vecTask))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecTask->SetAttribute("comment", ToUTF8Ptr("推的任务列表"));
	if(rElement.LinkEndChild(pElem_vecTask.get()) != NULL)
		pElem_vecTask.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecGroupTaskInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SGroupTaskInfoForClient s;
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

bool VectorToXML(const TVecGroupTaskInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SGroupTaskInfoForClient"));
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

} //namespace NGroupTaskProt
