/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    TaskProt.cpp
//  Purpose:      任务协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "TaskProt.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NTaskProt
{

#ifdef PROT_USE_XML

const char* EnumValToStr(ETaskResult e)
{
	switch(e)
	{
	case eTaskSucceed:
		return "eTaskSucceed";
	case eTaskNotExist:
		return "eTaskNotExist";
	case eTaskAlreadyAccept:
		return "eTaskAlreadyAccept";
	case eTaskErrFinish:
		return "eTaskErrFinish";
	case eTaskErrGiveUp:
		return "eTaskErrGiveUp";
	case eTaskErrAccept:
		return "eTaskErrAccept";
	case eTaskErrPackFull:
		return "eTaskErrPackFull";
	case eTaskErrRepeat:
		return "eTaskErrRepeat";
	case eTaskErrFull:
		return "eTaskErrFull";
	case eTaskErrSex:
		return "eTaskErrSex";
	case eTaskErrPrepTask:
		return "eTaskErrPrepTask";
	case eTaskErrLevel:
		return "eTaskErrLevel";
	case eTaskErrNoSelOptAward:
		return "eTaskErrNoSelOptAward";
	case eTaskErrMap:
		return "eTaskErrMap";
	case eTaskNoDiamond:
		return "eTaskNoDiamond";
	case eTaskNoGiftCoin:
		return "eTaskNoGiftCoin";
	case eTaskNoFamily:
		return "eTaskNoFamily";
	case eTaskNoGuild:
		return "eTaskNoGuild";
	case eTaskErrCamp:
		return "eTaskErrCamp";
	case eTaskNoRepution:
		return "eTaskNoRepution";
	case eTaskNoJob:
		return "eTaskNoJob";
	case eTaskNoRace:
		return "eTaskNoRace";
	case eTaskNoGold:
		return "eTaskNoGold";
	case eTaskNoSliver:
		return "eTaskNoSliver";
	case eTaskGroupFull:
		return "eTaskGroupFull";
	case eTaskYaMenFull:
		return "eTaskYaMenFull";
	case eTaskCircleFull:
		return "eTaskCircleFull";
	case eTaskErrOther:
		return "eTaskErrOther";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, ETaskResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, ETaskResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eTaskSucceed", eTaskSucceed));
		mapStr2Val.insert(make_pair("eTaskNotExist", eTaskNotExist));
		mapStr2Val.insert(make_pair("eTaskAlreadyAccept", eTaskAlreadyAccept));
		mapStr2Val.insert(make_pair("eTaskErrFinish", eTaskErrFinish));
		mapStr2Val.insert(make_pair("eTaskErrGiveUp", eTaskErrGiveUp));
		mapStr2Val.insert(make_pair("eTaskErrAccept", eTaskErrAccept));
		mapStr2Val.insert(make_pair("eTaskErrPackFull", eTaskErrPackFull));
		mapStr2Val.insert(make_pair("eTaskErrRepeat", eTaskErrRepeat));
		mapStr2Val.insert(make_pair("eTaskErrFull", eTaskErrFull));
		mapStr2Val.insert(make_pair("eTaskErrSex", eTaskErrSex));
		mapStr2Val.insert(make_pair("eTaskErrPrepTask", eTaskErrPrepTask));
		mapStr2Val.insert(make_pair("eTaskErrLevel", eTaskErrLevel));
		mapStr2Val.insert(make_pair("eTaskErrNoSelOptAward", eTaskErrNoSelOptAward));
		mapStr2Val.insert(make_pair("eTaskErrMap", eTaskErrMap));
		mapStr2Val.insert(make_pair("eTaskNoDiamond", eTaskNoDiamond));
		mapStr2Val.insert(make_pair("eTaskNoGiftCoin", eTaskNoGiftCoin));
		mapStr2Val.insert(make_pair("eTaskNoFamily", eTaskNoFamily));
		mapStr2Val.insert(make_pair("eTaskNoGuild", eTaskNoGuild));
		mapStr2Val.insert(make_pair("eTaskErrCamp", eTaskErrCamp));
		mapStr2Val.insert(make_pair("eTaskNoRepution", eTaskNoRepution));
		mapStr2Val.insert(make_pair("eTaskNoJob", eTaskNoJob));
		mapStr2Val.insert(make_pair("eTaskNoRace", eTaskNoRace));
		mapStr2Val.insert(make_pair("eTaskNoGold", eTaskNoGold));
		mapStr2Val.insert(make_pair("eTaskNoSliver", eTaskNoSliver));
		mapStr2Val.insert(make_pair("eTaskGroupFull", eTaskGroupFull));
		mapStr2Val.insert(make_pair("eTaskYaMenFull", eTaskYaMenFull));
		mapStr2Val.insert(make_pair("eTaskCircleFull", eTaskCircleFull));
		mapStr2Val.insert(make_pair("eTaskErrOther", eTaskErrOther));
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

const char* EnumValToStr(ETaskState e)
{
	switch(e)
	{
	case eTaskNone:
		return "eTaskNone";
	case eTaskAccept:
		return "eTaskAccept";
	case eTaskFail:
		return "eTaskFail";
	case eTaskFinish:
		return "eTaskFinish";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, ETaskState& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, ETaskState> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eTaskNone", eTaskNone));
		mapStr2Val.insert(make_pair("eTaskAccept", eTaskAccept));
		mapStr2Val.insert(make_pair("eTaskFail", eTaskFail));
		mapStr2Val.insert(make_pair("eTaskFinish", eTaskFinish));
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

const char* EnumValToStr(ENpcTaskState e)
{
	switch(e)
	{
	case eNpcTaskNone:
		return "eNpcTaskNone";
	case eNpcTaskAccept:
		return "eNpcTaskAccept";
	case eNpcTaskUnfinish:
		return "eNpcTaskUnfinish";
	case eNpcTaskSubmit:
		return "eNpcTaskSubmit";
	case eNpcTaskFuture:
		return "eNpcTaskFuture";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, ENpcTaskState& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, ENpcTaskState> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eNpcTaskNone", eNpcTaskNone));
		mapStr2Val.insert(make_pair("eNpcTaskAccept", eNpcTaskAccept));
		mapStr2Val.insert(make_pair("eNpcTaskUnfinish", eNpcTaskUnfinish));
		mapStr2Val.insert(make_pair("eNpcTaskSubmit", eNpcTaskSubmit));
		mapStr2Val.insert(make_pair("eNpcTaskFuture", eNpcTaskFuture));
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

STaskInfo::STaskInfo() { }

CInArchive& operator>>(CInArchive& src, STaskInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const STaskInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, STaskInfo_Wrapper& rWrapper)
{
	EType_STaskInfo eType = eType_STaskInfo;
	src >> (UINT8&)eType;
	switch(eType)
	{
	case eType_STaskInfo:
		{
			rWrapper.ptr.reset(new STaskInfo);
			src >> (STaskInfo&)*rWrapper.ptr;
		}
		break;
	case eType_STaskCollectInfo:
		{
			rWrapper.ptr.reset(new STaskCollectInfo);
			src >> (STaskCollectInfo&)*rWrapper.ptr;
		}
		break;
	case eType_STaskGatherInfo:
		{
			rWrapper.ptr.reset(new STaskGatherInfo);
			src >> (STaskGatherInfo&)*rWrapper.ptr;
		}
		break;
	case eType_STaskMonsterInfo:
		{
			rWrapper.ptr.reset(new STaskMonsterInfo);
			src >> (STaskMonsterInfo&)*rWrapper.ptr;
		}
		break;
	case eType_STaskTalkInfo:
		{
			rWrapper.ptr.reset(new STaskTalkInfo);
			src >> (STaskTalkInfo&)*rWrapper.ptr;
		}
		break;
	case eType_STaskProbeInfo:
		{
			rWrapper.ptr.reset(new STaskProbeInfo);
			src >> (STaskProbeInfo&)*rWrapper.ptr;
		}
		break;
	case eType_STaskBuildInfo:
		{
			rWrapper.ptr.reset(new STaskBuildInfo);
			src >> (STaskBuildInfo&)*rWrapper.ptr;
		}
		break;
	case eType_STaskScienceInfo:
		{
			rWrapper.ptr.reset(new STaskScienceInfo);
			src >> (STaskScienceInfo&)*rWrapper.ptr;
		}
		break;
	case eType_STaskActionInfo:
		{
			rWrapper.ptr.reset(new STaskActionInfo);
			src >> (STaskActionInfo&)*rWrapper.ptr;
		}
		break;
	case eType_STaskGrowInfo:
		{
			rWrapper.ptr.reset(new STaskGrowInfo);
			src >> (STaskGrowInfo&)*rWrapper.ptr;
		}
		break;
	default:
		throw "Unknown value for EType_STaskInfo";
		break;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const STaskInfo_Wrapper& rWrapper)
{
	if(rWrapper.ptr != NULL)
	{
		src << (UINT8)rWrapper.ptr->GetClassType();
		switch(rWrapper.ptr->GetClassType())
		{
		case eType_STaskInfo:
			src << (STaskInfo&)*rWrapper.ptr;
			break;
		case eType_STaskCollectInfo:
			src << (STaskCollectInfo&)*rWrapper.ptr;
			break;
		case eType_STaskGatherInfo:
			src << (STaskGatherInfo&)*rWrapper.ptr;
			break;
		case eType_STaskMonsterInfo:
			src << (STaskMonsterInfo&)*rWrapper.ptr;
			break;
		case eType_STaskTalkInfo:
			src << (STaskTalkInfo&)*rWrapper.ptr;
			break;
		case eType_STaskProbeInfo:
			src << (STaskProbeInfo&)*rWrapper.ptr;
			break;
		case eType_STaskBuildInfo:
			src << (STaskBuildInfo&)*rWrapper.ptr;
			break;
		case eType_STaskScienceInfo:
			src << (STaskScienceInfo&)*rWrapper.ptr;
			break;
		case eType_STaskActionInfo:
			src << (STaskActionInfo&)*rWrapper.ptr;
			break;
		case eType_STaskGrowInfo:
			src << (STaskGrowInfo&)*rWrapper.ptr;
			break;
		default:
			throw "Unknown value for EType_STaskInfo";
			break;
		}
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecTaskInfo& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		STaskInfo_Wrapper wrapper;
		src >> wrapper;
		vec[i] = wrapper.ptr;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecTaskInfo& vec)
{
	if(vec.size() > 0x7FFF)
		throw "Vector Size Too Large!";
	UINT16 wSize = (UINT16)vec.size();
	src.WriteContainerSize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		STaskInfo_Wrapper wrapper;
		wrapper.ptr = vec[i];
		src << wrapper;
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, STaskInfo& s)
{
	if(strcmp(rElement.Value(), "STaskInfo") != 0)
	{
		LOG_CRI << "rElement is not STaskInfo!";
		return false;
	}
	return true;
}

bool ToXML(const STaskInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("STaskInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("任务信息"));
	return true;
}

bool SuperFromXML(TiXmlElement& rElement, STaskInfoPtr& p)
{
	const char* pszName = rElement.Value();
	if(pszName == NULL)
	{
		LOG_CRI << "Element Name is empty!";
		return false;
	}
	if(strcmp(pszName, "STaskInfo") == 0)
	{
		STaskInfoPtr pStruct(new STaskInfo);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for STaskInfo";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "STaskInfo FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "STaskCollectInfo") == 0)
	{
		STaskCollectInfoPtr pStruct(new STaskCollectInfo);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for STaskCollectInfo";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "STaskCollectInfo FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "STaskGatherInfo") == 0)
	{
		STaskGatherInfoPtr pStruct(new STaskGatherInfo);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for STaskGatherInfo";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "STaskGatherInfo FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "STaskMonsterInfo") == 0)
	{
		STaskMonsterInfoPtr pStruct(new STaskMonsterInfo);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for STaskMonsterInfo";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "STaskMonsterInfo FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "STaskTalkInfo") == 0)
	{
		STaskTalkInfoPtr pStruct(new STaskTalkInfo);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for STaskTalkInfo";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "STaskTalkInfo FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "STaskProbeInfo") == 0)
	{
		STaskProbeInfoPtr pStruct(new STaskProbeInfo);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for STaskProbeInfo";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "STaskProbeInfo FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "STaskBuildInfo") == 0)
	{
		STaskBuildInfoPtr pStruct(new STaskBuildInfo);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for STaskBuildInfo";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "STaskBuildInfo FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "STaskScienceInfo") == 0)
	{
		STaskScienceInfoPtr pStruct(new STaskScienceInfo);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for STaskScienceInfo";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "STaskScienceInfo FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "STaskActionInfo") == 0)
	{
		STaskActionInfoPtr pStruct(new STaskActionInfo);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for STaskActionInfo";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "STaskActionInfo FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "STaskGrowInfo") == 0)
	{
		STaskGrowInfoPtr pStruct(new STaskGrowInfo);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for STaskGrowInfo";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "STaskGrowInfo FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else
	{
		LOG_CRI << "Invalid name: " << pszName << "!";
		return false;
	}
	return true;
}

bool SuperToXML(const STaskInfo& s, TiXmlElement& rElement)
{
	switch(s.GetClassType())
	{
	case eType_STaskInfo:
		return ToXML((STaskInfo&)s, rElement);
	case eType_STaskCollectInfo:
		return ToXML((STaskCollectInfo&)s, rElement);
	case eType_STaskGatherInfo:
		return ToXML((STaskGatherInfo&)s, rElement);
	case eType_STaskMonsterInfo:
		return ToXML((STaskMonsterInfo&)s, rElement);
	case eType_STaskTalkInfo:
		return ToXML((STaskTalkInfo&)s, rElement);
	case eType_STaskProbeInfo:
		return ToXML((STaskProbeInfo&)s, rElement);
	case eType_STaskBuildInfo:
		return ToXML((STaskBuildInfo&)s, rElement);
	case eType_STaskScienceInfo:
		return ToXML((STaskScienceInfo&)s, rElement);
	case eType_STaskActionInfo:
		return ToXML((STaskActionInfo&)s, rElement);
	case eType_STaskGrowInfo:
		return ToXML((STaskGrowInfo&)s, rElement);
	default:
		LOG_CRI << "Invalid type: " << s.GetClassType();
		return false;
	}
}

bool VectorFromXML(TiXmlElement& rElement, TVecTaskInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		STaskInfoPtr p;
		if(!SuperFromXML(*pElemMember, p))
		{
			LOG_CRI << "SuperFromXML fails!";
			return false;
		}
		vec.push_back(p);
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecTaskInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("STaskInfo"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!SuperToXML(*vec[i], *pElemMember))
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

STaskCollectInfo::STaskCollectInfo() : wItemID(0), wItemCount(0) { }

CInArchive& operator>>(CInArchive& src, STaskCollectInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (STaskInfo&)s;
	src >> s.wItemID;
	src >> s.wItemCount;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const STaskCollectInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const STaskInfo&)s;
	src << s.wItemID;
	src << s.wItemCount;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, STaskCollectInfo& s)
{
	if(strcmp(rElement.Value(), "STaskCollectInfo") != 0)
	{
		LOG_CRI << "rElement is not STaskCollectInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for STaskInfo is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (STaskInfo&)s))
	{
		LOG_CRI << "FromXML for: STaskInfo fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wItemID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wItemID") != 0)
	{
		LOG_CRI << "Attribute: name is not wItemID!";
		return false;
	}
	const char* pszVal_wItemID = pElemChild->Attribute("value");
	if(pszVal_wItemID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wItemID, s.wItemID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wItemCount is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wItemCount") != 0)
	{
		LOG_CRI << "Attribute: name is not wItemCount!";
		return false;
	}
	const char* pszVal_wItemCount = pElemChild->Attribute("value");
	if(pszVal_wItemCount == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wItemCount, s.wItemCount))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const STaskCollectInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("STaskCollectInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("收集道具的信息"));
	unique_ptr<TiXmlElement> pElem_STaskInfo(new TiXmlElement("STaskInfo"));
	if(pElem_STaskInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const STaskInfo&)s, *pElem_STaskInfo))
	{
		LOG_CRI << "STaskInfo ToXML fails!";
		return false;
	}
	pElem_STaskInfo->SetAttribute("type", ToUTF8Ptr("任务信息"));
	pElem_STaskInfo->SetAttribute("comment", ToUTF8Ptr("父类STaskInfo部分"));
	if(rElement.LinkEndChild(pElem_STaskInfo.get()) != NULL)
		pElem_STaskInfo.release();
	unique_ptr<TiXmlElement> pElem_wItemID(new TiXmlElement("UINT16"));
	if(pElem_wItemID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wItemID->SetAttribute("name", "wItemID");
	pElem_wItemID->SetAttribute("value", NumberToString(s.wItemID).c_str());
	pElem_wItemID->SetAttribute("comment", ToUTF8Ptr("道具的ID"));
	if(rElement.LinkEndChild(pElem_wItemID.get()) != NULL)
		pElem_wItemID.release();
	unique_ptr<TiXmlElement> pElem_wItemCount(new TiXmlElement("UINT16"));
	if(pElem_wItemCount == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wItemCount->SetAttribute("name", "wItemCount");
	pElem_wItemCount->SetAttribute("value", NumberToString(s.wItemCount).c_str());
	pElem_wItemCount->SetAttribute("comment", ToUTF8Ptr("已搜集道具的数量"));
	if(rElement.LinkEndChild(pElem_wItemCount.get()) != NULL)
		pElem_wItemCount.release();
	return true;
}

#endif

STaskGatherInfo::STaskGatherInfo() : wGatherID(0), wCount(0) { }

CInArchive& operator>>(CInArchive& src, STaskGatherInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (STaskInfo&)s;
	src >> s.wGatherID;
	src >> s.wCount;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const STaskGatherInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const STaskInfo&)s;
	src << s.wGatherID;
	src << s.wCount;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, STaskGatherInfo& s)
{
	if(strcmp(rElement.Value(), "STaskGatherInfo") != 0)
	{
		LOG_CRI << "rElement is not STaskGatherInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for STaskInfo is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (STaskInfo&)s))
	{
		LOG_CRI << "FromXML for: STaskInfo fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wGatherID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wGatherID") != 0)
	{
		LOG_CRI << "Attribute: name is not wGatherID!";
		return false;
	}
	const char* pszVal_wGatherID = pElemChild->Attribute("value");
	if(pszVal_wGatherID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wGatherID, s.wGatherID))
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
	return true;
}

bool ToXML(const STaskGatherInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("STaskGatherInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("采集的信息"));
	unique_ptr<TiXmlElement> pElem_STaskInfo(new TiXmlElement("STaskInfo"));
	if(pElem_STaskInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const STaskInfo&)s, *pElem_STaskInfo))
	{
		LOG_CRI << "STaskInfo ToXML fails!";
		return false;
	}
	pElem_STaskInfo->SetAttribute("type", ToUTF8Ptr("任务信息"));
	pElem_STaskInfo->SetAttribute("comment", ToUTF8Ptr("父类STaskInfo部分"));
	if(rElement.LinkEndChild(pElem_STaskInfo.get()) != NULL)
		pElem_STaskInfo.release();
	unique_ptr<TiXmlElement> pElem_wGatherID(new TiXmlElement("UINT16"));
	if(pElem_wGatherID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wGatherID->SetAttribute("name", "wGatherID");
	pElem_wGatherID->SetAttribute("value", NumberToString(s.wGatherID).c_str());
	pElem_wGatherID->SetAttribute("comment", ToUTF8Ptr("采集的ID"));
	if(rElement.LinkEndChild(pElem_wGatherID.get()) != NULL)
		pElem_wGatherID.release();
	unique_ptr<TiXmlElement> pElem_wCount(new TiXmlElement("UINT16"));
	if(pElem_wCount == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wCount->SetAttribute("name", "wCount");
	pElem_wCount->SetAttribute("value", NumberToString(s.wCount).c_str());
	pElem_wCount->SetAttribute("comment", ToUTF8Ptr("已采集的次数"));
	if(rElement.LinkEndChild(pElem_wCount.get()) != NULL)
		pElem_wCount.release();
	return true;
}

#endif

STaskMonsterInfo::STaskMonsterInfo() : wMonsterID(0), wMonsterCount(0) { }

CInArchive& operator>>(CInArchive& src, STaskMonsterInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (STaskInfo&)s;
	src >> s.wMonsterID;
	src >> s.wMonsterCount;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const STaskMonsterInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const STaskInfo&)s;
	src << s.wMonsterID;
	src << s.wMonsterCount;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, STaskMonsterInfo& s)
{
	if(strcmp(rElement.Value(), "STaskMonsterInfo") != 0)
	{
		LOG_CRI << "rElement is not STaskMonsterInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for STaskInfo is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (STaskInfo&)s))
	{
		LOG_CRI << "FromXML for: STaskInfo fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wMonsterID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wMonsterID") != 0)
	{
		LOG_CRI << "Attribute: name is not wMonsterID!";
		return false;
	}
	const char* pszVal_wMonsterID = pElemChild->Attribute("value");
	if(pszVal_wMonsterID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wMonsterID, s.wMonsterID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wMonsterCount is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wMonsterCount") != 0)
	{
		LOG_CRI << "Attribute: name is not wMonsterCount!";
		return false;
	}
	const char* pszVal_wMonsterCount = pElemChild->Attribute("value");
	if(pszVal_wMonsterCount == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wMonsterCount, s.wMonsterCount))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const STaskMonsterInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("STaskMonsterInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("杀死怪物的信息"));
	unique_ptr<TiXmlElement> pElem_STaskInfo(new TiXmlElement("STaskInfo"));
	if(pElem_STaskInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const STaskInfo&)s, *pElem_STaskInfo))
	{
		LOG_CRI << "STaskInfo ToXML fails!";
		return false;
	}
	pElem_STaskInfo->SetAttribute("type", ToUTF8Ptr("任务信息"));
	pElem_STaskInfo->SetAttribute("comment", ToUTF8Ptr("父类STaskInfo部分"));
	if(rElement.LinkEndChild(pElem_STaskInfo.get()) != NULL)
		pElem_STaskInfo.release();
	unique_ptr<TiXmlElement> pElem_wMonsterID(new TiXmlElement("UINT16"));
	if(pElem_wMonsterID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wMonsterID->SetAttribute("name", "wMonsterID");
	pElem_wMonsterID->SetAttribute("value", NumberToString(s.wMonsterID).c_str());
	pElem_wMonsterID->SetAttribute("comment", ToUTF8Ptr("怪物的ID"));
	if(rElement.LinkEndChild(pElem_wMonsterID.get()) != NULL)
		pElem_wMonsterID.release();
	unique_ptr<TiXmlElement> pElem_wMonsterCount(new TiXmlElement("UINT16"));
	if(pElem_wMonsterCount == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wMonsterCount->SetAttribute("name", "wMonsterCount");
	pElem_wMonsterCount->SetAttribute("value", NumberToString(s.wMonsterCount).c_str());
	pElem_wMonsterCount->SetAttribute("comment", ToUTF8Ptr("已杀怪物的数量"));
	if(rElement.LinkEndChild(pElem_wMonsterCount.get()) != NULL)
		pElem_wMonsterCount.release();
	return true;
}

#endif

STaskTalkInfo::STaskTalkInfo() : wNpcID(0), wTalkCount(0) { }

CInArchive& operator>>(CInArchive& src, STaskTalkInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (STaskInfo&)s;
	src >> s.wNpcID;
	src >> s.wTalkCount;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const STaskTalkInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const STaskInfo&)s;
	src << s.wNpcID;
	src << s.wTalkCount;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, STaskTalkInfo& s)
{
	if(strcmp(rElement.Value(), "STaskTalkInfo") != 0)
	{
		LOG_CRI << "rElement is not STaskTalkInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for STaskInfo is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (STaskInfo&)s))
	{
		LOG_CRI << "FromXML for: STaskInfo fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wNpcID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wNpcID") != 0)
	{
		LOG_CRI << "Attribute: name is not wNpcID!";
		return false;
	}
	const char* pszVal_wNpcID = pElemChild->Attribute("value");
	if(pszVal_wNpcID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wNpcID, s.wNpcID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wTalkCount is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wTalkCount") != 0)
	{
		LOG_CRI << "Attribute: name is not wTalkCount!";
		return false;
	}
	const char* pszVal_wTalkCount = pElemChild->Attribute("value");
	if(pszVal_wTalkCount == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wTalkCount, s.wTalkCount))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const STaskTalkInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("STaskTalkInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("NPC的对话信息"));
	unique_ptr<TiXmlElement> pElem_STaskInfo(new TiXmlElement("STaskInfo"));
	if(pElem_STaskInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const STaskInfo&)s, *pElem_STaskInfo))
	{
		LOG_CRI << "STaskInfo ToXML fails!";
		return false;
	}
	pElem_STaskInfo->SetAttribute("type", ToUTF8Ptr("任务信息"));
	pElem_STaskInfo->SetAttribute("comment", ToUTF8Ptr("父类STaskInfo部分"));
	if(rElement.LinkEndChild(pElem_STaskInfo.get()) != NULL)
		pElem_STaskInfo.release();
	unique_ptr<TiXmlElement> pElem_wNpcID(new TiXmlElement("UINT16"));
	if(pElem_wNpcID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wNpcID->SetAttribute("name", "wNpcID");
	pElem_wNpcID->SetAttribute("value", NumberToString(s.wNpcID).c_str());
	pElem_wNpcID->SetAttribute("comment", ToUTF8Ptr("NPC的ID"));
	if(rElement.LinkEndChild(pElem_wNpcID.get()) != NULL)
		pElem_wNpcID.release();
	unique_ptr<TiXmlElement> pElem_wTalkCount(new TiXmlElement("UINT16"));
	if(pElem_wTalkCount == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wTalkCount->SetAttribute("name", "wTalkCount");
	pElem_wTalkCount->SetAttribute("value", NumberToString(s.wTalkCount).c_str());
	pElem_wTalkCount->SetAttribute("comment", ToUTF8Ptr("0:未完成1:已完成"));
	if(rElement.LinkEndChild(pElem_wTalkCount.get()) != NULL)
		pElem_wTalkCount.release();
	return true;
}

#endif

STaskProbeInfo::STaskProbeInfo() : byIndex(0), bProbed(false) { }

CInArchive& operator>>(CInArchive& src, STaskProbeInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (STaskInfo&)s;
	src >> s.byIndex;
	src >> s.bProbed;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const STaskProbeInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const STaskInfo&)s;
	src << s.byIndex;
	src << s.bProbed;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, STaskProbeInfo& s)
{
	if(strcmp(rElement.Value(), "STaskProbeInfo") != 0)
	{
		LOG_CRI << "rElement is not STaskProbeInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for STaskInfo is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (STaskInfo&)s))
	{
		LOG_CRI << "FromXML for: STaskInfo fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
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
		LOG_CRI << "pElemChild for bProbed is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "bool") != 0)
	{
		LOG_CRI << "pElemChild is not bool!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "bProbed") != 0)
	{
		LOG_CRI << "Attribute: name is not bProbed!";
		return false;
	}
	const char* pszVal_bProbed = pElemChild->Attribute("value");
	if(pszVal_bProbed == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_bProbed, s.bProbed))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const STaskProbeInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("STaskProbeInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("探索区域信息"));
	unique_ptr<TiXmlElement> pElem_STaskInfo(new TiXmlElement("STaskInfo"));
	if(pElem_STaskInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const STaskInfo&)s, *pElem_STaskInfo))
	{
		LOG_CRI << "STaskInfo ToXML fails!";
		return false;
	}
	pElem_STaskInfo->SetAttribute("type", ToUTF8Ptr("任务信息"));
	pElem_STaskInfo->SetAttribute("comment", ToUTF8Ptr("父类STaskInfo部分"));
	if(rElement.LinkEndChild(pElem_STaskInfo.get()) != NULL)
		pElem_STaskInfo.release();
	unique_ptr<TiXmlElement> pElem_byIndex(new TiXmlElement("UINT8"));
	if(pElem_byIndex == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byIndex->SetAttribute("name", "byIndex");
	pElem_byIndex->SetAttribute("value", NumberToString(s.byIndex).c_str());
	pElem_byIndex->SetAttribute("comment", ToUTF8Ptr("探索区域索引"));
	if(rElement.LinkEndChild(pElem_byIndex.get()) != NULL)
		pElem_byIndex.release();
	unique_ptr<TiXmlElement> pElem_bProbed(new TiXmlElement("bool"));
	if(pElem_bProbed == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_bProbed->SetAttribute("name", "bProbed");
	pElem_bProbed->SetAttribute("value", NumberToString(s.bProbed).c_str());
	pElem_bProbed->SetAttribute("comment", ToUTF8Ptr("是否已探索"));
	if(rElement.LinkEndChild(pElem_bProbed.get()) != NULL)
		pElem_bProbed.release();
	return true;
}

#endif

STaskBuildInfo::STaskBuildInfo() : wBuildID(0), wLevel(0) { }

CInArchive& operator>>(CInArchive& src, STaskBuildInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (STaskInfo&)s;
	src >> s.wBuildID;
	src >> s.wLevel;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const STaskBuildInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const STaskInfo&)s;
	src << s.wBuildID;
	src << s.wLevel;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, STaskBuildInfo& s)
{
	if(strcmp(rElement.Value(), "STaskBuildInfo") != 0)
	{
		LOG_CRI << "rElement is not STaskBuildInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for STaskInfo is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (STaskInfo&)s))
	{
		LOG_CRI << "FromXML for: STaskInfo fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wBuildID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wBuildID") != 0)
	{
		LOG_CRI << "Attribute: name is not wBuildID!";
		return false;
	}
	const char* pszVal_wBuildID = pElemChild->Attribute("value");
	if(pszVal_wBuildID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wBuildID, s.wBuildID))
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
	return true;
}

bool ToXML(const STaskBuildInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("STaskBuildInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("建筑的信息"));
	unique_ptr<TiXmlElement> pElem_STaskInfo(new TiXmlElement("STaskInfo"));
	if(pElem_STaskInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const STaskInfo&)s, *pElem_STaskInfo))
	{
		LOG_CRI << "STaskInfo ToXML fails!";
		return false;
	}
	pElem_STaskInfo->SetAttribute("type", ToUTF8Ptr("任务信息"));
	pElem_STaskInfo->SetAttribute("comment", ToUTF8Ptr("父类STaskInfo部分"));
	if(rElement.LinkEndChild(pElem_STaskInfo.get()) != NULL)
		pElem_STaskInfo.release();
	unique_ptr<TiXmlElement> pElem_wBuildID(new TiXmlElement("UINT16"));
	if(pElem_wBuildID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wBuildID->SetAttribute("name", "wBuildID");
	pElem_wBuildID->SetAttribute("value", NumberToString(s.wBuildID).c_str());
	pElem_wBuildID->SetAttribute("comment", ToUTF8Ptr("建筑ID"));
	if(rElement.LinkEndChild(pElem_wBuildID.get()) != NULL)
		pElem_wBuildID.release();
	unique_ptr<TiXmlElement> pElem_wLevel(new TiXmlElement("UINT16"));
	if(pElem_wLevel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wLevel->SetAttribute("name", "wLevel");
	pElem_wLevel->SetAttribute("value", NumberToString(s.wLevel).c_str());
	pElem_wLevel->SetAttribute("comment", ToUTF8Ptr("等级"));
	if(rElement.LinkEndChild(pElem_wLevel.get()) != NULL)
		pElem_wLevel.release();
	return true;
}

#endif

STaskScienceInfo::STaskScienceInfo() : wScienceID(0), wLevel(0) { }

CInArchive& operator>>(CInArchive& src, STaskScienceInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (STaskInfo&)s;
	src >> s.wScienceID;
	src >> s.wLevel;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const STaskScienceInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const STaskInfo&)s;
	src << s.wScienceID;
	src << s.wLevel;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, STaskScienceInfo& s)
{
	if(strcmp(rElement.Value(), "STaskScienceInfo") != 0)
	{
		LOG_CRI << "rElement is not STaskScienceInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for STaskInfo is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (STaskInfo&)s))
	{
		LOG_CRI << "FromXML for: STaskInfo fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wScienceID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wScienceID") != 0)
	{
		LOG_CRI << "Attribute: name is not wScienceID!";
		return false;
	}
	const char* pszVal_wScienceID = pElemChild->Attribute("value");
	if(pszVal_wScienceID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wScienceID, s.wScienceID))
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
	return true;
}

bool ToXML(const STaskScienceInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("STaskScienceInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("科技的信息"));
	unique_ptr<TiXmlElement> pElem_STaskInfo(new TiXmlElement("STaskInfo"));
	if(pElem_STaskInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const STaskInfo&)s, *pElem_STaskInfo))
	{
		LOG_CRI << "STaskInfo ToXML fails!";
		return false;
	}
	pElem_STaskInfo->SetAttribute("type", ToUTF8Ptr("任务信息"));
	pElem_STaskInfo->SetAttribute("comment", ToUTF8Ptr("父类STaskInfo部分"));
	if(rElement.LinkEndChild(pElem_STaskInfo.get()) != NULL)
		pElem_STaskInfo.release();
	unique_ptr<TiXmlElement> pElem_wScienceID(new TiXmlElement("UINT16"));
	if(pElem_wScienceID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wScienceID->SetAttribute("name", "wScienceID");
	pElem_wScienceID->SetAttribute("value", NumberToString(s.wScienceID).c_str());
	pElem_wScienceID->SetAttribute("comment", ToUTF8Ptr("科技ID"));
	if(rElement.LinkEndChild(pElem_wScienceID.get()) != NULL)
		pElem_wScienceID.release();
	unique_ptr<TiXmlElement> pElem_wLevel(new TiXmlElement("UINT16"));
	if(pElem_wLevel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wLevel->SetAttribute("name", "wLevel");
	pElem_wLevel->SetAttribute("value", NumberToString(s.wLevel).c_str());
	pElem_wLevel->SetAttribute("comment", ToUTF8Ptr("等级"));
	if(rElement.LinkEndChild(pElem_wLevel.get()) != NULL)
		pElem_wLevel.release();
	return true;
}

#endif

STaskActionInfo::STaskActionInfo() : wAction(0), wCount(0) { }

CInArchive& operator>>(CInArchive& src, STaskActionInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (STaskInfo&)s;
	src >> s.wAction;
	src >> s.wCount;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const STaskActionInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const STaskInfo&)s;
	src << s.wAction;
	src << s.wCount;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, STaskActionInfo& s)
{
	if(strcmp(rElement.Value(), "STaskActionInfo") != 0)
	{
		LOG_CRI << "rElement is not STaskActionInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for STaskInfo is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (STaskInfo&)s))
	{
		LOG_CRI << "FromXML for: STaskInfo fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wAction is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wAction") != 0)
	{
		LOG_CRI << "Attribute: name is not wAction!";
		return false;
	}
	const char* pszVal_wAction = pElemChild->Attribute("value");
	if(pszVal_wAction == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wAction, s.wAction))
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
	return true;
}

bool ToXML(const STaskActionInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("STaskActionInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("行为的信息"));
	unique_ptr<TiXmlElement> pElem_STaskInfo(new TiXmlElement("STaskInfo"));
	if(pElem_STaskInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const STaskInfo&)s, *pElem_STaskInfo))
	{
		LOG_CRI << "STaskInfo ToXML fails!";
		return false;
	}
	pElem_STaskInfo->SetAttribute("type", ToUTF8Ptr("任务信息"));
	pElem_STaskInfo->SetAttribute("comment", ToUTF8Ptr("父类STaskInfo部分"));
	if(rElement.LinkEndChild(pElem_STaskInfo.get()) != NULL)
		pElem_STaskInfo.release();
	unique_ptr<TiXmlElement> pElem_wAction(new TiXmlElement("UINT16"));
	if(pElem_wAction == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wAction->SetAttribute("name", "wAction");
	pElem_wAction->SetAttribute("value", NumberToString(s.wAction).c_str());
	pElem_wAction->SetAttribute("comment", ToUTF8Ptr("行为类型"));
	if(rElement.LinkEndChild(pElem_wAction.get()) != NULL)
		pElem_wAction.release();
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
	return true;
}

#endif

STaskGrowInfo::STaskGrowInfo() : wType(0), wLevel(0) { }

CInArchive& operator>>(CInArchive& src, STaskGrowInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (STaskInfo&)s;
	src >> s.wType;
	src >> s.wLevel;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const STaskGrowInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const STaskInfo&)s;
	src << s.wType;
	src << s.wLevel;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, STaskGrowInfo& s)
{
	if(strcmp(rElement.Value(), "STaskGrowInfo") != 0)
	{
		LOG_CRI << "rElement is not STaskGrowInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for STaskInfo is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (STaskInfo&)s))
	{
		LOG_CRI << "FromXML for: STaskInfo fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wType") != 0)
	{
		LOG_CRI << "Attribute: name is not wType!";
		return false;
	}
	const char* pszVal_wType = pElemChild->Attribute("value");
	if(pszVal_wType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wType, s.wType))
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
	return true;
}

bool ToXML(const STaskGrowInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("STaskGrowInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("成长的信息"));
	unique_ptr<TiXmlElement> pElem_STaskInfo(new TiXmlElement("STaskInfo"));
	if(pElem_STaskInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const STaskInfo&)s, *pElem_STaskInfo))
	{
		LOG_CRI << "STaskInfo ToXML fails!";
		return false;
	}
	pElem_STaskInfo->SetAttribute("type", ToUTF8Ptr("任务信息"));
	pElem_STaskInfo->SetAttribute("comment", ToUTF8Ptr("父类STaskInfo部分"));
	if(rElement.LinkEndChild(pElem_STaskInfo.get()) != NULL)
		pElem_STaskInfo.release();
	unique_ptr<TiXmlElement> pElem_wType(new TiXmlElement("UINT16"));
	if(pElem_wType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wType->SetAttribute("name", "wType");
	pElem_wType->SetAttribute("value", NumberToString(s.wType).c_str());
	pElem_wType->SetAttribute("comment", ToUTF8Ptr("成长类型"));
	if(rElement.LinkEndChild(pElem_wType.get()) != NULL)
		pElem_wType.release();
	unique_ptr<TiXmlElement> pElem_wLevel(new TiXmlElement("UINT16"));
	if(pElem_wLevel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wLevel->SetAttribute("name", "wLevel");
	pElem_wLevel->SetAttribute("value", NumberToString(s.wLevel).c_str());
	pElem_wLevel->SetAttribute("comment", ToUTF8Ptr("等级"));
	if(rElement.LinkEndChild(pElem_wLevel.get()) != NULL)
		pElem_wLevel.release();
	return true;
}

#endif

STask::STask() : wTaskID(0), eTaskState((ETaskState)0), dwAcceptTime(0), byRepeat(0) { }

STask::STask(STask&& src) : wTaskID(src.wTaskID), eTaskState(src.eTaskState), dwAcceptTime(src.dwAcceptTime), byRepeat(src.byRepeat), vecTaskInfo(move(src.vecTaskInfo)) { }

STask& STask::operator=(STask&& rhs)
{
	if(this != &rhs)
	{
		this->~STask();
		new (this) STask(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, STask& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.wTaskID;
	src >> (UINT8&)s.eTaskState;
	src >> s.dwAcceptTime;
	src >> s.byRepeat;
	src >> s.vecTaskInfo;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const STask& s)
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
	src << (UINT8&)s.eTaskState;
	src << s.dwAcceptTime;
	src << s.byRepeat;
	src << s.vecTaskInfo;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, STask& s)
{
	if(strcmp(rElement.Value(), "STask") != 0)
	{
		LOG_CRI << "rElement is not STask!";
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
		LOG_CRI << "pElemChild for eTaskState is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "ETaskState") != 0)
	{
		LOG_CRI << "pElemChild is not ETaskState!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eTaskState") != 0)
	{
		LOG_CRI << "Attribute: name is not eTaskState!";
		return false;
	}
	const char* pszVal_eTaskState = pElemChild->Attribute("value");
	if(pszVal_eTaskState == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!EnumStrToVal(pszVal_eTaskState, s.eTaskState))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwAcceptTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwAcceptTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwAcceptTime!";
		return false;
	}
	const char* pszVal_dwAcceptTime = pElemChild->Attribute("value");
	if(pszVal_dwAcceptTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwAcceptTime, s.dwAcceptTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byRepeat is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byRepeat") != 0)
	{
		LOG_CRI << "Attribute: name is not byRepeat!";
		return false;
	}
	const char* pszVal_byRepeat = pElemChild->Attribute("value");
	if(pszVal_byRepeat == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byRepeat, s.byRepeat))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecTaskInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecTaskInfo") != 0)
	{
		LOG_CRI << "pElemChild is not TVecTaskInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecTaskInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not vecTaskInfo!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecTaskInfo))
	{
		LOG_CRI << "VectorFromXML for vecTaskInfo fails!";
		return false;
	}
	return true;
}

bool ToXML(const STask& s, TiXmlElement& rElement)
{
	rElement.SetValue("STask");
	rElement.SetAttribute("type", ToUTF8Ptr("任务的属性"));
	unique_ptr<TiXmlElement> pElem_wTaskID(new TiXmlElement("UINT16"));
	if(pElem_wTaskID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wTaskID->SetAttribute("name", "wTaskID");
	pElem_wTaskID->SetAttribute("value", NumberToString(s.wTaskID).c_str());
	pElem_wTaskID->SetAttribute("comment", ToUTF8Ptr("任务的ID"));
	if(rElement.LinkEndChild(pElem_wTaskID.get()) != NULL)
		pElem_wTaskID.release();
	unique_ptr<TiXmlElement> pElem_eTaskState(new TiXmlElement("ETaskState"));
	if(pElem_eTaskState == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eTaskState->SetAttribute("name", "eTaskState");
	const char* pszEnum_eTaskState = EnumValToStr(s.eTaskState);
	if(pszEnum_eTaskState == NULL)
	{
		LOG_CRI << "EnumValToStr for ETaskState fails!";
		return false;
	}
	pElem_eTaskState->SetAttribute("value", pszEnum_eTaskState);
	pElem_eTaskState->SetAttribute("comment", ToUTF8Ptr("任务的状态"));
	if(rElement.LinkEndChild(pElem_eTaskState.get()) != NULL)
		pElem_eTaskState.release();
	unique_ptr<TiXmlElement> pElem_dwAcceptTime(new TiXmlElement("UINT32"));
	if(pElem_dwAcceptTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwAcceptTime->SetAttribute("name", "dwAcceptTime");
	pElem_dwAcceptTime->SetAttribute("value", NumberToString(s.dwAcceptTime).c_str());
	pElem_dwAcceptTime->SetAttribute("comment", ToUTF8Ptr("接取时间"));
	if(rElement.LinkEndChild(pElem_dwAcceptTime.get()) != NULL)
		pElem_dwAcceptTime.release();
	unique_ptr<TiXmlElement> pElem_byRepeat(new TiXmlElement("UINT8"));
	if(pElem_byRepeat == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byRepeat->SetAttribute("name", "byRepeat");
	pElem_byRepeat->SetAttribute("value", NumberToString(s.byRepeat).c_str());
	pElem_byRepeat->SetAttribute("comment", ToUTF8Ptr("同时接取数"));
	if(rElement.LinkEndChild(pElem_byRepeat.get()) != NULL)
		pElem_byRepeat.release();
	unique_ptr<TiXmlElement> pElem_vecTaskInfo(new TiXmlElement("TVecTaskInfo"));
	if(pElem_vecTaskInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecTaskInfo->SetAttribute("name", "vecTaskInfo");
	if(!VectorToXML(s.vecTaskInfo, *pElem_vecTaskInfo))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecTaskInfo->SetAttribute("comment", ToUTF8Ptr("任务信息列表"));
	if(rElement.LinkEndChild(pElem_vecTaskInfo.get()) != NULL)
		pElem_vecTaskInfo.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecTask& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		STask s;
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

bool VectorToXML(const TVecTask& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("STask"));
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

} //namespace NTaskProt
