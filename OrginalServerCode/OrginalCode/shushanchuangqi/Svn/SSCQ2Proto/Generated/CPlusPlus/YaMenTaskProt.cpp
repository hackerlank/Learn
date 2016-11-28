/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    YaMenTaskProt.cpp
//  Purpose:      衙门任务协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "YaMenTaskProt.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NYaMenTaskProt
{

#ifdef PROT_USE_XML

const char* EnumValToStr(EYaMenTaskResult e)
{
	switch(e)
	{
	case eYaMenTaskSucceed:
		return "eYaMenTaskSucceed";
	case eYaMenTaskLowMoney:
		return "eYaMenTaskLowMoney";
	case eBuyTimesUpLimit:
		return "eBuyTimesUpLimit";
	case eYaMenSaveTimesUpLimit:
		return "eYaMenSaveTimesUpLimit";
	case eYaMenAwardPackFull:
		return "eYaMenAwardPackFull";
	case eYaMenTaskErrOther:
		return "eYaMenTaskErrOther";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EYaMenTaskResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EYaMenTaskResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eYaMenTaskSucceed", eYaMenTaskSucceed));
		mapStr2Val.insert(make_pair("eYaMenTaskLowMoney", eYaMenTaskLowMoney));
		mapStr2Val.insert(make_pair("eBuyTimesUpLimit", eBuyTimesUpLimit));
		mapStr2Val.insert(make_pair("eYaMenSaveTimesUpLimit", eYaMenSaveTimesUpLimit));
		mapStr2Val.insert(make_pair("eYaMenAwardPackFull", eYaMenAwardPackFull));
		mapStr2Val.insert(make_pair("eYaMenTaskErrOther", eYaMenTaskErrOther));
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

const char* EnumValToStr(EYaMenStudyState e)
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

bool EnumStrToVal(const char* pszEnumStr, EYaMenStudyState& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EYaMenStudyState> mapStr2Val;
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

const char* EnumValToStr(EYaMenTaskState e)
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

bool EnumStrToVal(const char* pszEnumStr, EYaMenTaskState& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EYaMenTaskState> mapStr2Val;
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

SYaMenTask::SYaMenTask() : dwTaskId(0), eYaMenTaskState((EYaMenTaskState)0) { }

SYaMenTask::SYaMenTask(UINT32 dwTaskId_, EYaMenTaskState eYaMenTaskState_) : dwTaskId(dwTaskId_), eYaMenTaskState(eYaMenTaskState_) { }

CInArchive& operator>>(CInArchive& src, SYaMenTask& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.dwTaskId;
	src >> (UINT8&)s.eYaMenTaskState;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SYaMenTask& s)
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
	src << (UINT8&)s.eYaMenTaskState;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SYaMenTask& s)
{
	if(strcmp(rElement.Value(), "SYaMenTask") != 0)
	{
		LOG_CRI << "rElement is not SYaMenTask!";
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
		LOG_CRI << "pElemChild for eYaMenTaskState is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "EYaMenTaskState") != 0)
	{
		LOG_CRI << "pElemChild is not EYaMenTaskState!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eYaMenTaskState") != 0)
	{
		LOG_CRI << "Attribute: name is not eYaMenTaskState!";
		return false;
	}
	const char* pszVal_eYaMenTaskState = pElemChild->Attribute("value");
	if(pszVal_eYaMenTaskState == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!EnumStrToVal(pszVal_eYaMenTaskState, s.eYaMenTaskState))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SYaMenTask& s, TiXmlElement& rElement)
{
	rElement.SetValue("SYaMenTask");
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
	unique_ptr<TiXmlElement> pElem_eYaMenTaskState(new TiXmlElement("EYaMenTaskState"));
	if(pElem_eYaMenTaskState == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eYaMenTaskState->SetAttribute("name", "eYaMenTaskState");
	const char* pszEnum_eYaMenTaskState = EnumValToStr(s.eYaMenTaskState);
	if(pszEnum_eYaMenTaskState == NULL)
	{
		LOG_CRI << "EnumValToStr for EYaMenTaskState fails!";
		return false;
	}
	pElem_eYaMenTaskState->SetAttribute("value", pszEnum_eYaMenTaskState);
	pElem_eYaMenTaskState->SetAttribute("comment", ToUTF8Ptr("当前刷的任务信息"));
	if(rElement.LinkEndChild(pElem_eYaMenTaskState.get()) != NULL)
		pElem_eYaMenTaskState.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecYaMenTask& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SYaMenTask s;
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

bool VectorToXML(const TVecYaMenTask& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SYaMenTask"));
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

SYaMenTaskInfoForClient::SYaMenTaskInfoForClient() : eStudyState((EYaMenStudyState)0), dwYaMenRepute(0), dwYaMenLevel(0), byFinishTask(0), byAcceptTaskTimes(0), 
			byBuyTimesToday(0), byVIPTaskTimes(0), byFlushTask(0), byStudyAward(0) { }

SYaMenTaskInfoForClient::SYaMenTaskInfoForClient(EYaMenStudyState eStudyState_, UINT32 dwYaMenRepute_, UINT8 dwYaMenLevel_, UINT8 byFinishTask_, UINT8 byAcceptTaskTimes_, 
			UINT8 byBuyTimesToday_, UINT8 byVIPTaskTimes_, UINT8 byFlushTask_, UINT8 byStudyAward_, const TVecYaMenTask& vecTask_)
			: eStudyState(eStudyState_), dwYaMenRepute(dwYaMenRepute_), dwYaMenLevel(dwYaMenLevel_), byFinishTask(byFinishTask_), byAcceptTaskTimes(byAcceptTaskTimes_), 
			byBuyTimesToday(byBuyTimesToday_), byVIPTaskTimes(byVIPTaskTimes_), byFlushTask(byFlushTask_), byStudyAward(byStudyAward_), vecTask(vecTask_) { }

SYaMenTaskInfoForClient::SYaMenTaskInfoForClient(SYaMenTaskInfoForClient&& src) : eStudyState(src.eStudyState), dwYaMenRepute(src.dwYaMenRepute), dwYaMenLevel(src.dwYaMenLevel), byFinishTask(src.byFinishTask), byAcceptTaskTimes(src.byAcceptTaskTimes), 
			byBuyTimesToday(src.byBuyTimesToday), byVIPTaskTimes(src.byVIPTaskTimes), byFlushTask(src.byFlushTask), byStudyAward(src.byStudyAward), vecTask(move(src.vecTask)) { }

SYaMenTaskInfoForClient& SYaMenTaskInfoForClient::operator=(SYaMenTaskInfoForClient&& rhs)
{
	if(this != &rhs)
	{
		this->~SYaMenTaskInfoForClient();
		new (this) SYaMenTaskInfoForClient(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SYaMenTaskInfoForClient& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (UINT8&)s.eStudyState;
	src >> s.dwYaMenRepute;
	src >> s.dwYaMenLevel;
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

COutArchive& operator<<(COutArchive& src, const SYaMenTaskInfoForClient& s)
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
	src << s.dwYaMenRepute;
	src << s.dwYaMenLevel;
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

bool FromXML(TiXmlElement& rElement, SYaMenTaskInfoForClient& s)
{
	if(strcmp(rElement.Value(), "SYaMenTaskInfoForClient") != 0)
	{
		LOG_CRI << "rElement is not SYaMenTaskInfoForClient!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eStudyState is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "EYaMenStudyState") != 0)
	{
		LOG_CRI << "pElemChild is not EYaMenStudyState!";
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
		LOG_CRI << "pElemChild for dwYaMenRepute is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwYaMenRepute") != 0)
	{
		LOG_CRI << "Attribute: name is not dwYaMenRepute!";
		return false;
	}
	const char* pszVal_dwYaMenRepute = pElemChild->Attribute("value");
	if(pszVal_dwYaMenRepute == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwYaMenRepute, s.dwYaMenRepute))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwYaMenLevel is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwYaMenLevel") != 0)
	{
		LOG_CRI << "Attribute: name is not dwYaMenLevel!";
		return false;
	}
	const char* pszVal_dwYaMenLevel = pElemChild->Attribute("value");
	if(pszVal_dwYaMenLevel == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwYaMenLevel, s.dwYaMenLevel))
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
	if(strcmp(pElemChild->Value(), "TVecYaMenTask") != 0)
	{
		LOG_CRI << "pElemChild is not TVecYaMenTask!";
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

bool ToXML(const SYaMenTaskInfoForClient& s, TiXmlElement& rElement)
{
	rElement.SetValue("SYaMenTaskInfoForClient");
	rElement.SetAttribute("type", ToUTF8Ptr("衙门任务信息"));
	unique_ptr<TiXmlElement> pElem_eStudyState(new TiXmlElement("EYaMenStudyState"));
	if(pElem_eStudyState == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eStudyState->SetAttribute("name", "eStudyState");
	const char* pszEnum_eStudyState = EnumValToStr(s.eStudyState);
	if(pszEnum_eStudyState == NULL)
	{
		LOG_CRI << "EnumValToStr for EYaMenStudyState fails!";
		return false;
	}
	pElem_eStudyState->SetAttribute("value", pszEnum_eStudyState);
	pElem_eStudyState->SetAttribute("comment", ToUTF8Ptr("清修状态"));
	if(rElement.LinkEndChild(pElem_eStudyState.get()) != NULL)
		pElem_eStudyState.release();
	unique_ptr<TiXmlElement> pElem_dwYaMenRepute(new TiXmlElement("UINT32"));
	if(pElem_dwYaMenRepute == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwYaMenRepute->SetAttribute("name", "dwYaMenRepute");
	pElem_dwYaMenRepute->SetAttribute("value", NumberToString(s.dwYaMenRepute).c_str());
	pElem_dwYaMenRepute->SetAttribute("comment", ToUTF8Ptr("声望"));
	if(rElement.LinkEndChild(pElem_dwYaMenRepute.get()) != NULL)
		pElem_dwYaMenRepute.release();
	unique_ptr<TiXmlElement> pElem_dwYaMenLevel(new TiXmlElement("UINT8"));
	if(pElem_dwYaMenLevel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwYaMenLevel->SetAttribute("name", "dwYaMenLevel");
	pElem_dwYaMenLevel->SetAttribute("value", NumberToString(s.dwYaMenLevel).c_str());
	pElem_dwYaMenLevel->SetAttribute("comment", ToUTF8Ptr("声望等级"));
	if(rElement.LinkEndChild(pElem_dwYaMenLevel.get()) != NULL)
		pElem_dwYaMenLevel.release();
	unique_ptr<TiXmlElement> pElem_byFinishTask(new TiXmlElement("UINT8"));
	if(pElem_byFinishTask == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byFinishTask->SetAttribute("name", "byFinishTask");
	pElem_byFinishTask->SetAttribute("value", NumberToString(s.byFinishTask).c_str());
	pElem_byFinishTask->SetAttribute("comment", ToUTF8Ptr("今日完成的衙门任务数"));
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
	unique_ptr<TiXmlElement> pElem_vecTask(new TiXmlElement("TVecYaMenTask"));
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

bool VectorFromXML(TiXmlElement& rElement, TVecYaMenTaskInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SYaMenTaskInfoForClient s;
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

bool VectorToXML(const TVecYaMenTaskInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SYaMenTaskInfoForClient"));
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

} //namespace NYaMenTaskProt
