/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    NpcProt.cpp
//  Purpose:      NPC相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "NpcProt.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NNpcProt
{

#ifdef PROT_USE_XML

const char* EnumValToStr(ETalkResult e)
{
	switch(e)
	{
	case eTalkSucceed:
		return "eTalkSucceed";
	case eTalkNotExist:
		return "eTalkNotExist";
	case eTalkTooFar:
		return "eTalkTooFar";
	case eTalkScriptFail:
		return "eTalkScriptFail";
	case eTalkOther:
		return "eTalkOther";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, ETalkResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, ETalkResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eTalkSucceed", eTalkSucceed));
		mapStr2Val.insert(make_pair("eTalkNotExist", eTalkNotExist));
		mapStr2Val.insert(make_pair("eTalkTooFar", eTalkTooFar));
		mapStr2Val.insert(make_pair("eTalkScriptFail", eTalkScriptFail));
		mapStr2Val.insert(make_pair("eTalkOther", eTalkOther));
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

SNpcTaskState::SNpcTaskState() : wNpcID(0), eNpcTaskState((NTaskProt::ENpcTaskState)0) { }

SNpcTaskState::SNpcTaskState(UINT16 wNpcID_, NTaskProt::ENpcTaskState eNpcTaskState_) : wNpcID(wNpcID_), eNpcTaskState(eNpcTaskState_) { }

CInArchive& operator>>(CInArchive& src, SNpcTaskState& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.wNpcID;
	src >> (UINT8&)s.eNpcTaskState;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SNpcTaskState& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.wNpcID;
	src << (UINT8&)s.eNpcTaskState;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SNpcTaskState& s)
{
	if(strcmp(rElement.Value(), "SNpcTaskState") != 0)
	{
		LOG_CRI << "rElement is not SNpcTaskState!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
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
		LOG_CRI << "pElemChild for eNpcTaskState is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TaskProt::ENpcTaskState") != 0)
	{
		LOG_CRI << "pElemChild is not TaskProt::ENpcTaskState!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eNpcTaskState") != 0)
	{
		LOG_CRI << "Attribute: name is not eNpcTaskState!";
		return false;
	}
	const char* pszVal_eNpcTaskState = pElemChild->Attribute("value");
	if(pszVal_eNpcTaskState == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!NTaskProt::EnumStrToVal(pszVal_eNpcTaskState, s.eNpcTaskState))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SNpcTaskState& s, TiXmlElement& rElement)
{
	rElement.SetValue("SNpcTaskState");
	rElement.SetAttribute("type", ToUTF8Ptr("NPC的任务状态"));
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
	unique_ptr<TiXmlElement> pElem_eNpcTaskState(new TiXmlElement("TaskProt::ENpcTaskState"));
	if(pElem_eNpcTaskState == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eNpcTaskState->SetAttribute("name", "eNpcTaskState");
	const char* pszEnum_eNpcTaskState = NTaskProt::EnumValToStr(s.eNpcTaskState);
	if(pszEnum_eNpcTaskState == NULL)
	{
		LOG_CRI << "EnumValToStr for eNpcTaskState fails!";
		return false;
	}
	pElem_eNpcTaskState->SetAttribute("value", pszEnum_eNpcTaskState);
	pElem_eNpcTaskState->SetAttribute("comment", ToUTF8Ptr("任务状态"));
	if(rElement.LinkEndChild(pElem_eNpcTaskState.get()) != NULL)
		pElem_eNpcTaskState.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecNpcTask& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SNpcTaskState s;
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

bool VectorToXML(const TVecNpcTask& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SNpcTaskState"));
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

} //namespace NNpcProt
