/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    Activity.cpp
//  Purpose:      活力任务协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "ActivityProt.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NActivityProt
{

#ifdef PROT_USE_XML

const char* EnumValToStr(EActivityResult e)
{
	switch(e)
	{
	case eActivitySucceed:
		return "eActivitySucceed";
	case eActivityMin:
		return "eActivityMin";
	case eActivityTotalMin:
		return "eActivityTotalMin";
	case eActivityPackNoSpace:
		return "eActivityPackNoSpace";
	case eActivityHasGet:
		return "eActivityHasGet";
	case eActivityVip:
		return "eActivityVip";
	case eActivityErrOther:
		return "eActivityErrOther";
	case eActivityNotFinish:
		return "eActivityNotFinish";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EActivityResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EActivityResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eActivitySucceed", eActivitySucceed));
		mapStr2Val.insert(make_pair("eActivityMin", eActivityMin));
		mapStr2Val.insert(make_pair("eActivityTotalMin", eActivityTotalMin));
		mapStr2Val.insert(make_pair("eActivityPackNoSpace", eActivityPackNoSpace));
		mapStr2Val.insert(make_pair("eActivityHasGet", eActivityHasGet));
		mapStr2Val.insert(make_pair("eActivityVip", eActivityVip));
		mapStr2Val.insert(make_pair("eActivityErrOther", eActivityErrOther));
		mapStr2Val.insert(make_pair("eActivityNotFinish", eActivityNotFinish));
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

const char* EnumValToStr(EShareStatus e)
{
	switch(e)
	{
	case eShareStatus_Init:
		return "eShareStatus_Init";
	case eShareStatus_Finish:
		return "eShareStatus_Finish";
	case eShareStatus_TakePrize:
		return "eShareStatus_TakePrize";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EShareStatus& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EShareStatus> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eShareStatus_Init", eShareStatus_Init));
		mapStr2Val.insert(make_pair("eShareStatus_Finish", eShareStatus_Finish));
		mapStr2Val.insert(make_pair("eShareStatus_TakePrize", eShareStatus_TakePrize));
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

const char* GetDescription(EShareStatus e)
{
	switch(e)
	{
	case eShareStatus_Init:
		return "未完成";
	case eShareStatus_Finish:
		return "已完成";
	case eShareStatus_TakePrize:
		return "已领奖";
	default:
		return "未知错误";
	}
}

SActivityAward::SActivityAward() : byId(0), byVIP(0) { }

SActivityAward::SActivityAward(UINT8 byId_, UINT8 byVIP_) : byId(byId_), byVIP(byVIP_) { }

CInArchive& operator>>(CInArchive& src, SActivityAward& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.byId;
	src >> s.byVIP;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SActivityAward& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.byId;
	src << s.byVIP;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SActivityAward& s)
{
	if(strcmp(rElement.Value(), "SActivityAward") != 0)
	{
		LOG_CRI << "rElement is not SActivityAward!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byId is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byId") != 0)
	{
		LOG_CRI << "Attribute: name is not byId!";
		return false;
	}
	const char* pszVal_byId = pElemChild->Attribute("value");
	if(pszVal_byId == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byId, s.byId))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byVIP is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byVIP") != 0)
	{
		LOG_CRI << "Attribute: name is not byVIP!";
		return false;
	}
	const char* pszVal_byVIP = pElemChild->Attribute("value");
	if(pszVal_byVIP == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byVIP, s.byVIP))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SActivityAward& s, TiXmlElement& rElement)
{
	rElement.SetValue("SActivityAward");
	rElement.SetAttribute("type", ToUTF8Ptr("每日已领活力奖励"));
	unique_ptr<TiXmlElement> pElem_byId(new TiXmlElement("UINT8"));
	if(pElem_byId == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byId->SetAttribute("name", "byId");
	pElem_byId->SetAttribute("value", NumberToString(s.byId).c_str());
	pElem_byId->SetAttribute("comment", ToUTF8Ptr("奖励ID"));
	if(rElement.LinkEndChild(pElem_byId.get()) != NULL)
		pElem_byId.release();
	unique_ptr<TiXmlElement> pElem_byVIP(new TiXmlElement("UINT8"));
	if(pElem_byVIP == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byVIP->SetAttribute("name", "byVIP");
	pElem_byVIP->SetAttribute("value", NumberToString(s.byVIP).c_str());
	pElem_byVIP->SetAttribute("comment", ToUTF8Ptr("是否VIP"));
	if(rElement.LinkEndChild(pElem_byVIP.get()) != NULL)
		pElem_byVIP.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecActivityAward& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SActivityAward s;
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

bool VectorToXML(const TVecActivityAward& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SActivityAward"));
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

SActivityInfoForClient::SActivityInfoForClient() : dwTotolActivity(0), wActivity(0) { }

SActivityInfoForClient::SActivityInfoForClient(UINT32 dwTotolActivity_, UINT16 wActivity_, const NRoleInfoDefine::TVecActivityTaskInfo& vecActivityTask_, const TVecActivityAward& vecActivityAward_) : dwTotolActivity(dwTotolActivity_), wActivity(wActivity_), vecActivityTask(vecActivityTask_), vecActivityAward(vecActivityAward_) { }

SActivityInfoForClient::SActivityInfoForClient(SActivityInfoForClient&& src) : dwTotolActivity(src.dwTotolActivity), wActivity(src.wActivity), vecActivityTask(move(src.vecActivityTask)), vecActivityAward(move(src.vecActivityAward)) { }

SActivityInfoForClient& SActivityInfoForClient::operator=(SActivityInfoForClient&& rhs)
{
	if(this != &rhs)
	{
		this->~SActivityInfoForClient();
		new (this) SActivityInfoForClient(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SActivityInfoForClient& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.dwTotolActivity;
	src >> s.wActivity;
	src >> s.vecActivityTask;
	src >> s.vecActivityAward;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SActivityInfoForClient& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.dwTotolActivity;
	src << s.wActivity;
	src << s.vecActivityTask;
	src << s.vecActivityAward;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SActivityInfoForClient& s)
{
	if(strcmp(rElement.Value(), "SActivityInfoForClient") != 0)
	{
		LOG_CRI << "rElement is not SActivityInfoForClient!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwTotolActivity is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwTotolActivity") != 0)
	{
		LOG_CRI << "Attribute: name is not dwTotolActivity!";
		return false;
	}
	const char* pszVal_dwTotolActivity = pElemChild->Attribute("value");
	if(pszVal_dwTotolActivity == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwTotolActivity, s.dwTotolActivity))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wActivity is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wActivity") != 0)
	{
		LOG_CRI << "Attribute: name is not wActivity!";
		return false;
	}
	const char* pszVal_wActivity = pElemChild->Attribute("value");
	if(pszVal_wActivity == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wActivity, s.wActivity))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecActivityTask is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "RoleInfoDefine::TVecActivityTaskInfo") != 0)
	{
		LOG_CRI << "pElemChild is not RoleInfoDefine::TVecActivityTaskInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecActivityTask") != 0)
	{
		LOG_CRI << "Attribute: name is not vecActivityTask!";
		return false;
	}
	if(!NRoleInfoDefine::VectorFromXML(*pElemChild, s.vecActivityTask))
	{
		LOG_CRI << "VectorFromXML for vecActivityTask fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecActivityAward is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecActivityAward") != 0)
	{
		LOG_CRI << "pElemChild is not TVecActivityAward!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecActivityAward") != 0)
	{
		LOG_CRI << "Attribute: name is not vecActivityAward!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecActivityAward))
	{
		LOG_CRI << "VectorFromXML for vecActivityAward fails!";
		return false;
	}
	return true;
}

bool ToXML(const SActivityInfoForClient& s, TiXmlElement& rElement)
{
	rElement.SetValue("SActivityInfoForClient");
	rElement.SetAttribute("type", ToUTF8Ptr("活力任务信息"));
	unique_ptr<TiXmlElement> pElem_dwTotolActivity(new TiXmlElement("UINT32"));
	if(pElem_dwTotolActivity == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwTotolActivity->SetAttribute("name", "dwTotolActivity");
	pElem_dwTotolActivity->SetAttribute("value", NumberToString(s.dwTotolActivity).c_str());
	pElem_dwTotolActivity->SetAttribute("comment", ToUTF8Ptr("累计活力值"));
	if(rElement.LinkEndChild(pElem_dwTotolActivity.get()) != NULL)
		pElem_dwTotolActivity.release();
	unique_ptr<TiXmlElement> pElem_wActivity(new TiXmlElement("UINT16"));
	if(pElem_wActivity == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wActivity->SetAttribute("name", "wActivity");
	pElem_wActivity->SetAttribute("value", NumberToString(s.wActivity).c_str());
	pElem_wActivity->SetAttribute("comment", ToUTF8Ptr("当前活力"));
	if(rElement.LinkEndChild(pElem_wActivity.get()) != NULL)
		pElem_wActivity.release();
	unique_ptr<TiXmlElement> pElem_vecActivityTask(new TiXmlElement("RoleInfoDefine::TVecActivityTaskInfo"));
	if(pElem_vecActivityTask == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecActivityTask->SetAttribute("name", "vecActivityTask");
	if(!NRoleInfoDefine::VectorToXML(s.vecActivityTask, *pElem_vecActivityTask))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecActivityTask->SetAttribute("comment", ToUTF8Ptr("活力监测点"));
	if(rElement.LinkEndChild(pElem_vecActivityTask.get()) != NULL)
		pElem_vecActivityTask.release();
	unique_ptr<TiXmlElement> pElem_vecActivityAward(new TiXmlElement("TVecActivityAward"));
	if(pElem_vecActivityAward == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecActivityAward->SetAttribute("name", "vecActivityAward");
	if(!VectorToXML(s.vecActivityAward, *pElem_vecActivityAward))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecActivityAward->SetAttribute("comment", ToUTF8Ptr("已领活力"));
	if(rElement.LinkEndChild(pElem_vecActivityAward.get()) != NULL)
		pElem_vecActivityAward.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecActivityInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SActivityInfoForClient s;
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

bool VectorToXML(const TVecActivityInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SActivityInfoForClient"));
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

SActivityShare::SActivityShare() : dwActivityID(0), eStatus((EShareStatus)0) { }

SActivityShare::SActivityShare(UINT32 dwActivityID_, EShareStatus eStatus_) : dwActivityID(dwActivityID_), eStatus(eStatus_) { }

CInArchive& operator>>(CInArchive& src, SActivityShare& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.dwActivityID;
	src >> (UINT8&)s.eStatus;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SActivityShare& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.dwActivityID;
	src << (UINT8&)s.eStatus;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SActivityShare& s)
{
	if(strcmp(rElement.Value(), "SActivityShare") != 0)
	{
		LOG_CRI << "rElement is not SActivityShare!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwActivityID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwActivityID") != 0)
	{
		LOG_CRI << "Attribute: name is not dwActivityID!";
		return false;
	}
	const char* pszVal_dwActivityID = pElemChild->Attribute("value");
	if(pszVal_dwActivityID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwActivityID, s.dwActivityID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eStatus is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "EShareStatus") != 0)
	{
		LOG_CRI << "pElemChild is not EShareStatus!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eStatus") != 0)
	{
		LOG_CRI << "Attribute: name is not eStatus!";
		return false;
	}
	const char* pszVal_eStatus = pElemChild->Attribute("value");
	if(pszVal_eStatus == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!EnumStrToVal(pszVal_eStatus, s.eStatus))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SActivityShare& s, TiXmlElement& rElement)
{
	rElement.SetValue("SActivityShare");
	rElement.SetAttribute("type", ToUTF8Ptr("活力分享列表"));
	unique_ptr<TiXmlElement> pElem_dwActivityID(new TiXmlElement("UINT32"));
	if(pElem_dwActivityID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwActivityID->SetAttribute("name", "dwActivityID");
	pElem_dwActivityID->SetAttribute("value", NumberToString(s.dwActivityID).c_str());
	pElem_dwActivityID->SetAttribute("comment", ToUTF8Ptr("活跃度ID"));
	if(rElement.LinkEndChild(pElem_dwActivityID.get()) != NULL)
		pElem_dwActivityID.release();
	unique_ptr<TiXmlElement> pElem_eStatus(new TiXmlElement("EShareStatus"));
	if(pElem_eStatus == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eStatus->SetAttribute("name", "eStatus");
	const char* pszEnum_eStatus = EnumValToStr(s.eStatus);
	if(pszEnum_eStatus == NULL)
	{
		LOG_CRI << "EnumValToStr for EShareStatus fails!";
		return false;
	}
	pElem_eStatus->SetAttribute("value", pszEnum_eStatus);
	pElem_eStatus->SetAttribute("comment", ToUTF8Ptr("分享状态"));
	if(rElement.LinkEndChild(pElem_eStatus.get()) != NULL)
		pElem_eStatus.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecActivityShare& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SActivityShare s;
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

bool VectorToXML(const TVecActivityShare& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SActivityShare"));
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

} //namespace NActivityProt
