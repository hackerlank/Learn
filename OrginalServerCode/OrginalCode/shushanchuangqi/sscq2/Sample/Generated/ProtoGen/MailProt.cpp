/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    MailProt.cpp
//  Purpose:      邮件CenterServer通讯协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "MailProt.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NMailProt
{

#ifdef PROT_USE_XML

const char* EnumValToStr(EMailQueryType e)
{
	switch(e)
	{
	case eQueryNew:
		return "eQueryNew";
	case eQueryReaded:
		return "eQueryReaded";
	case eQueryTotal:
		return "eQueryTotal";
	case eQueryPerson:
		return "eQueryPerson";
	case eQuerysysTem:
		return "eQuerysysTem";
	case eQueryAttch:
		return "eQueryAttch";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EMailQueryType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EMailQueryType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eQueryNew", eQueryNew));
		mapStr2Val.insert(make_pair("eQueryReaded", eQueryReaded));
		mapStr2Val.insert(make_pair("eQueryTotal", eQueryTotal));
		mapStr2Val.insert(make_pair("eQueryPerson", eQueryPerson));
		mapStr2Val.insert(make_pair("eQuerysysTem", eQuerysysTem));
		mapStr2Val.insert(make_pair("eQueryAttch", eQueryAttch));
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

const char* EnumValToStr(EMailState e)
{
	switch(e)
	{
	case eStateNew:
		return "eStateNew";
	case eStateReaded:
		return "eStateReaded";
	case eStateDelete:
		return "eStateDelete";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EMailState& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EMailState> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eStateNew", eStateNew));
		mapStr2Val.insert(make_pair("eStateReaded", eStateReaded));
		mapStr2Val.insert(make_pair("eStateDelete", eStateDelete));
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

const char* EnumValToStr(EMailErrorResult e)
{
	switch(e)
	{
	case EMail_SendOk:
		return "EMail_SendOk";
	case EMail_SendFail:
		return "EMail_SendFail";
	case EMail_DeleteOk:
		return "EMail_DeleteOk";
	case EMail_DeleteFail:
		return "EMail_DeleteFail";
	case EMail_OverMaxCount:
		return "EMail_OverMaxCount";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EMailErrorResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EMailErrorResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("EMail_SendOk", EMail_SendOk));
		mapStr2Val.insert(make_pair("EMail_SendFail", EMail_SendFail));
		mapStr2Val.insert(make_pair("EMail_DeleteOk", EMail_DeleteOk));
		mapStr2Val.insert(make_pair("EMail_DeleteFail", EMail_DeleteFail));
		mapStr2Val.insert(make_pair("EMail_OverMaxCount", EMail_OverMaxCount));
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

const char* EnumValToStr(EMailType e)
{
	switch(e)
	{
	case EMAILTYPE_NORMAL:
		return "EMAILTYPE_NORMAL";
	case EMAILTYPE_SYSTEM:
		return "EMAILTYPE_SYSTEM";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EMailType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EMailType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("EMAILTYPE_NORMAL", EMAILTYPE_NORMAL));
		mapStr2Val.insert(make_pair("EMAILTYPE_SYSTEM", EMAILTYPE_SYSTEM));
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

const char* EnumValToStr(EMailAttachType e)
{
	switch(e)
	{
	case ATTACH_ITEM:
		return "ATTACH_ITEM";
	case ATTACH_INSTANCE:
		return "ATTACH_INSTANCE";
	case ATTACH_MAX:
		return "ATTACH_MAX";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EMailAttachType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EMailAttachType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("ATTACH_ITEM", ATTACH_ITEM));
		mapStr2Val.insert(make_pair("ATTACH_INSTANCE", ATTACH_INSTANCE));
		mapStr2Val.insert(make_pair("ATTACH_MAX", ATTACH_MAX));
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

const char* EnumValToStr(EMailDRawResult e)
{
	switch(e)
	{
	case DRAW_SUC:
		return "DRAW_SUC";
	case PACK_FULL:
		return "PACK_FULL";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EMailDRawResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EMailDRawResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("DRAW_SUC", DRAW_SUC));
		mapStr2Val.insert(make_pair("PACK_FULL", PACK_FULL));
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

const char* GetDescription(EMailDRawResult e)
{
	switch(e)
	{
	case DRAW_SUC:
		return "提取成功";
	case PACK_FULL:
		return "包裹满";
	default:
		return "未知错误";
	}
}

SysMailSendTxt::SysMailSendTxt() : dwstrMsgID(0) { }

SysMailSendTxt::SysMailSendTxt(UINT32 dwstrMsgID_, const TVecString& vecParam_) : dwstrMsgID(dwstrMsgID_), vecParam(vecParam_) { }

CInArchive& operator>>(CInArchive& src, SysMailSendTxt& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.dwstrMsgID;
	src >> s.vecParam;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SysMailSendTxt& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.dwstrMsgID;
	src << s.vecParam;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SysMailSendTxt& s)
{
	if(strcmp(rElement.Value(), "SysMailSendTxt") != 0)
	{
		LOG_CRI << "rElement is not SysMailSendTxt!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwstrMsgID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwstrMsgID") != 0)
	{
		LOG_CRI << "Attribute: name is not dwstrMsgID!";
		return false;
	}
	const char* pszVal_dwstrMsgID = pElemChild->Attribute("value");
	if(pszVal_dwstrMsgID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwstrMsgID, s.dwstrMsgID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecParam is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecString") != 0)
	{
		LOG_CRI << "pElemChild is not TVecString!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecParam") != 0)
	{
		LOG_CRI << "Attribute: name is not vecParam!";
		return false;
	}
	const char* pszText_vecParam = pElemChild->GetText();
	if(pszText_vecParam != NULL)
		SplitToText(pszText_vecParam, ",", s.vecParam);
	return true;
}

bool ToXML(const SysMailSendTxt& s, TiXmlElement& rElement)
{
	rElement.SetValue("SysMailSendTxt");
	rElement.SetAttribute("type", ToUTF8Ptr("系统邮件标题，及其内容"));
	unique_ptr<TiXmlElement> pElem_dwstrMsgID(new TiXmlElement("UINT32"));
	if(pElem_dwstrMsgID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwstrMsgID->SetAttribute("name", "dwstrMsgID");
	pElem_dwstrMsgID->SetAttribute("value", NumberToString(s.dwstrMsgID).c_str());
	pElem_dwstrMsgID->SetAttribute("comment", ToUTF8Ptr("消息ID"));
	if(rElement.LinkEndChild(pElem_dwstrMsgID.get()) != NULL)
		pElem_dwstrMsgID.release();
	unique_ptr<TiXmlElement> pElem_vecParam(new TiXmlElement("TVecString"));
	if(pElem_vecParam == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecParam->SetAttribute("name", "vecParam");
	string strText_vecParam;
	for(size_t i = 0; i < s.vecParam.size(); ++i)
	{
		if(i > 0)
			strText_vecParam += ", ";
		strText_vecParam += s.vecParam[i];
	}
	unique_ptr<TiXmlText> pText_vecParam(new TiXmlText(strText_vecParam.c_str()));
	if(pText_vecParam == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(pElem_vecParam->LinkEndChild(pText_vecParam.get()) != NULL)
		pText_vecParam.release();
	pElem_vecParam->SetAttribute("comment", ToUTF8Ptr("参数列表"));
	if(rElement.LinkEndChild(pElem_vecParam.get()) != NULL)
		pElem_vecParam.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecSysMailSendTxt& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SysMailSendTxt s;
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

bool VectorToXML(const TVecSysMailSendTxt& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SysMailSendTxt"));
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

SMailSummary::SMailSummary() : uMailID(0), eMailType((EMailType)0), eMailState((EMailState)0), uSendTime(0), byHasAttachment(0) { }

SMailSummary::SMailSummary(UINT64 uMailID_, EMailType eMailType_, EMailState eMailState_, UINT32 uSendTime_, UINT8 byHasAttachment_, 
			const std::string& strTitle_, const std::string& strSendName_)
			: uMailID(uMailID_), eMailType(eMailType_), eMailState(eMailState_), uSendTime(uSendTime_), byHasAttachment(byHasAttachment_), 
			strTitle(strTitle_), strSendName(strSendName_) { }

SMailSummary::SMailSummary(SMailSummary&& src) : uMailID(src.uMailID), eMailType(src.eMailType), eMailState(src.eMailState), uSendTime(src.uSendTime), byHasAttachment(src.byHasAttachment), 
			strTitle(move(src.strTitle)), strSendName(move(src.strSendName)) { }

SMailSummary& SMailSummary::operator=(SMailSummary&& rhs)
{
	if(this != &rhs)
	{
		this->~SMailSummary();
		new (this) SMailSummary(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SMailSummary& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.uMailID;
	src >> (UINT8&)s.eMailType;
	src >> (UINT8&)s.eMailState;
	src >> s.uSendTime;
	src >> s.byHasAttachment;
	src >> s.strTitle;
	src >> s.strSendName;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SMailSummary& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.uMailID;
	src << (UINT8&)s.eMailType;
	src << (UINT8&)s.eMailState;
	src << s.uSendTime;
	src << s.byHasAttachment;
	src << s.strTitle;
	src << s.strSendName;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SMailSummary& s)
{
	if(strcmp(rElement.Value(), "SMailSummary") != 0)
	{
		LOG_CRI << "rElement is not SMailSummary!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for uMailID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "uMailID") != 0)
	{
		LOG_CRI << "Attribute: name is not uMailID!";
		return false;
	}
	const char* pszVal_uMailID = pElemChild->Attribute("value");
	if(pszVal_uMailID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_uMailID, s.uMailID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eMailType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "EMailType") != 0)
	{
		LOG_CRI << "pElemChild is not EMailType!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eMailType") != 0)
	{
		LOG_CRI << "Attribute: name is not eMailType!";
		return false;
	}
	const char* pszVal_eMailType = pElemChild->Attribute("value");
	if(pszVal_eMailType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!EnumStrToVal(pszVal_eMailType, s.eMailType))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eMailState is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "EMailState") != 0)
	{
		LOG_CRI << "pElemChild is not EMailState!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eMailState") != 0)
	{
		LOG_CRI << "Attribute: name is not eMailState!";
		return false;
	}
	const char* pszVal_eMailState = pElemChild->Attribute("value");
	if(pszVal_eMailState == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!EnumStrToVal(pszVal_eMailState, s.eMailState))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for uSendTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "uSendTime") != 0)
	{
		LOG_CRI << "Attribute: name is not uSendTime!";
		return false;
	}
	const char* pszVal_uSendTime = pElemChild->Attribute("value");
	if(pszVal_uSendTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_uSendTime, s.uSendTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byHasAttachment is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byHasAttachment") != 0)
	{
		LOG_CRI << "Attribute: name is not byHasAttachment!";
		return false;
	}
	const char* pszVal_byHasAttachment = pElemChild->Attribute("value");
	if(pszVal_byHasAttachment == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byHasAttachment, s.byHasAttachment))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strTitle is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strTitle") != 0)
	{
		LOG_CRI << "Attribute: name is not strTitle!";
		return false;
	}
	const char* pszVal_strTitle = pElemChild->Attribute("value");
	if(pszVal_strTitle == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strTitle = pszVal_strTitle;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strSendName is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strSendName") != 0)
	{
		LOG_CRI << "Attribute: name is not strSendName!";
		return false;
	}
	const char* pszVal_strSendName = pElemChild->Attribute("value");
	if(pszVal_strSendName == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strSendName = pszVal_strSendName;
	return true;
}

bool ToXML(const SMailSummary& s, TiXmlElement& rElement)
{
	rElement.SetValue("SMailSummary");
	rElement.SetAttribute("type", ToUTF8Ptr("邮件摘要列表"));
	unique_ptr<TiXmlElement> pElem_uMailID(new TiXmlElement("UINT64"));
	if(pElem_uMailID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_uMailID->SetAttribute("name", "uMailID");
	pElem_uMailID->SetAttribute("value", NumberToString(s.uMailID).c_str());
	pElem_uMailID->SetAttribute("comment", ToUTF8Ptr("邮件ID"));
	if(rElement.LinkEndChild(pElem_uMailID.get()) != NULL)
		pElem_uMailID.release();
	unique_ptr<TiXmlElement> pElem_eMailType(new TiXmlElement("EMailType"));
	if(pElem_eMailType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eMailType->SetAttribute("name", "eMailType");
	const char* pszEnum_eMailType = EnumValToStr(s.eMailType);
	if(pszEnum_eMailType == NULL)
	{
		LOG_CRI << "EnumValToStr for EMailType fails!";
		return false;
	}
	pElem_eMailType->SetAttribute("value", pszEnum_eMailType);
	pElem_eMailType->SetAttribute("comment", ToUTF8Ptr("邮件类型"));
	if(rElement.LinkEndChild(pElem_eMailType.get()) != NULL)
		pElem_eMailType.release();
	unique_ptr<TiXmlElement> pElem_eMailState(new TiXmlElement("EMailState"));
	if(pElem_eMailState == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eMailState->SetAttribute("name", "eMailState");
	const char* pszEnum_eMailState = EnumValToStr(s.eMailState);
	if(pszEnum_eMailState == NULL)
	{
		LOG_CRI << "EnumValToStr for EMailState fails!";
		return false;
	}
	pElem_eMailState->SetAttribute("value", pszEnum_eMailState);
	pElem_eMailState->SetAttribute("comment", ToUTF8Ptr("邮件状态"));
	if(rElement.LinkEndChild(pElem_eMailState.get()) != NULL)
		pElem_eMailState.release();
	unique_ptr<TiXmlElement> pElem_uSendTime(new TiXmlElement("UINT32"));
	if(pElem_uSendTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_uSendTime->SetAttribute("name", "uSendTime");
	pElem_uSendTime->SetAttribute("value", NumberToString(s.uSendTime).c_str());
	pElem_uSendTime->SetAttribute("comment", ToUTF8Ptr("邮件发送时间"));
	if(rElement.LinkEndChild(pElem_uSendTime.get()) != NULL)
		pElem_uSendTime.release();
	unique_ptr<TiXmlElement> pElem_byHasAttachment(new TiXmlElement("UINT8"));
	if(pElem_byHasAttachment == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byHasAttachment->SetAttribute("name", "byHasAttachment");
	pElem_byHasAttachment->SetAttribute("value", NumberToString(s.byHasAttachment).c_str());
	pElem_byHasAttachment->SetAttribute("comment", ToUTF8Ptr("0:没有   1:有"));
	if(rElement.LinkEndChild(pElem_byHasAttachment.get()) != NULL)
		pElem_byHasAttachment.release();
	unique_ptr<TiXmlElement> pElem_strTitle(new TiXmlElement("string"));
	if(pElem_strTitle == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strTitle->SetAttribute("name", "strTitle");
	pElem_strTitle->SetAttribute("value", s.strTitle.c_str());
	pElem_strTitle->SetAttribute("comment", ToUTF8Ptr("邮件标题"));
	if(rElement.LinkEndChild(pElem_strTitle.get()) != NULL)
		pElem_strTitle.release();
	unique_ptr<TiXmlElement> pElem_strSendName(new TiXmlElement("string"));
	if(pElem_strSendName == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strSendName->SetAttribute("name", "strSendName");
	pElem_strSendName->SetAttribute("value", s.strSendName.c_str());
	pElem_strSendName->SetAttribute("comment", ToUTF8Ptr("发送者"));
	if(rElement.LinkEndChild(pElem_strSendName.get()) != NULL)
		pElem_strSendName.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecMailList& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SMailSummary s;
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

bool VectorToXML(const TVecMailList& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SMailSummary"));
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

SMailItemInfo::SMailItemInfo() : qwInstID(0), wItemID(0), eItemQuelity((NItemProt::EItemQuality)0), wCount(0), eBindType((NItemProt::EBindType)0), 
			byExpired(0), dwExpireTime(0), qwOPID(0) { }

SMailItemInfo::SMailItemInfo(UINT64 qwInstID_, UINT32 wItemID_, NItemProt::EItemQuality eItemQuelity_, UINT32 wCount_, NItemProt::EBindType eBindType_, 
			UINT8 byExpired_, UINT32 dwExpireTime_, UINT64 qwOPID_)
			: qwInstID(qwInstID_), wItemID(wItemID_), eItemQuelity(eItemQuelity_), wCount(wCount_), eBindType(eBindType_), 
			byExpired(byExpired_), dwExpireTime(dwExpireTime_), qwOPID(qwOPID_) { }

CInArchive& operator>>(CInArchive& src, SMailItemInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwInstID;
	src >> s.wItemID;
	src >> (UINT8&)s.eItemQuelity;
	src >> s.wCount;
	src >> (UINT8&)s.eBindType;
	src >> s.byExpired;
	src >> s.dwExpireTime;
	src >> s.qwOPID;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SMailItemInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.qwInstID;
	src << s.wItemID;
	src << (UINT8&)s.eItemQuelity;
	src << s.wCount;
	src << (UINT8&)s.eBindType;
	src << s.byExpired;
	src << s.dwExpireTime;
	src << s.qwOPID;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SMailItemInfo& s)
{
	if(strcmp(rElement.Value(), "SMailItemInfo") != 0)
	{
		LOG_CRI << "rElement is not SMailItemInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwInstID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwInstID") != 0)
	{
		LOG_CRI << "Attribute: name is not qwInstID!";
		return false;
	}
	const char* pszVal_qwInstID = pElemChild->Attribute("value");
	if(pszVal_qwInstID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwInstID, s.qwInstID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wItemID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
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
		LOG_CRI << "pElemChild for eItemQuelity is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "ItemProt::EItemQuality") != 0)
	{
		LOG_CRI << "pElemChild is not ItemProt::EItemQuality!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eItemQuelity") != 0)
	{
		LOG_CRI << "Attribute: name is not eItemQuelity!";
		return false;
	}
	const char* pszVal_eItemQuelity = pElemChild->Attribute("value");
	if(pszVal_eItemQuelity == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!NItemProt::EnumStrToVal(pszVal_eItemQuelity, s.eItemQuelity))
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
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
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
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eBindType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "ItemProt::EBindType") != 0)
	{
		LOG_CRI << "pElemChild is not ItemProt::EBindType!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eBindType") != 0)
	{
		LOG_CRI << "Attribute: name is not eBindType!";
		return false;
	}
	const char* pszVal_eBindType = pElemChild->Attribute("value");
	if(pszVal_eBindType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!NItemProt::EnumStrToVal(pszVal_eBindType, s.eBindType))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byExpired is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byExpired") != 0)
	{
		LOG_CRI << "Attribute: name is not byExpired!";
		return false;
	}
	const char* pszVal_byExpired = pElemChild->Attribute("value");
	if(pszVal_byExpired == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byExpired, s.byExpired))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwExpireTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwExpireTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwExpireTime!";
		return false;
	}
	const char* pszVal_dwExpireTime = pElemChild->Attribute("value");
	if(pszVal_dwExpireTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwExpireTime, s.dwExpireTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwOPID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwOPID") != 0)
	{
		LOG_CRI << "Attribute: name is not qwOPID!";
		return false;
	}
	const char* pszVal_qwOPID = pElemChild->Attribute("value");
	if(pszVal_qwOPID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwOPID, s.qwOPID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SMailItemInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SMailItemInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("道具格式"));
	unique_ptr<TiXmlElement> pElem_qwInstID(new TiXmlElement("UINT64"));
	if(pElem_qwInstID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwInstID->SetAttribute("name", "qwInstID");
	pElem_qwInstID->SetAttribute("value", NumberToString(s.qwInstID).c_str());
	pElem_qwInstID->SetAttribute("comment", ToUTF8Ptr("道具类型ID"));
	if(rElement.LinkEndChild(pElem_qwInstID.get()) != NULL)
		pElem_qwInstID.release();
	unique_ptr<TiXmlElement> pElem_wItemID(new TiXmlElement("UINT32"));
	if(pElem_wItemID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wItemID->SetAttribute("name", "wItemID");
	pElem_wItemID->SetAttribute("value", NumberToString(s.wItemID).c_str());
	pElem_wItemID->SetAttribute("comment", ToUTF8Ptr("物品模板"));
	if(rElement.LinkEndChild(pElem_wItemID.get()) != NULL)
		pElem_wItemID.release();
	unique_ptr<TiXmlElement> pElem_eItemQuelity(new TiXmlElement("ItemProt::EItemQuality"));
	if(pElem_eItemQuelity == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eItemQuelity->SetAttribute("name", "eItemQuelity");
	const char* pszEnum_eItemQuelity = NItemProt::EnumValToStr(s.eItemQuelity);
	if(pszEnum_eItemQuelity == NULL)
	{
		LOG_CRI << "EnumValToStr for eItemQuelity fails!";
		return false;
	}
	pElem_eItemQuelity->SetAttribute("value", pszEnum_eItemQuelity);
	pElem_eItemQuelity->SetAttribute("comment", ToUTF8Ptr("物品品质"));
	if(rElement.LinkEndChild(pElem_eItemQuelity.get()) != NULL)
		pElem_eItemQuelity.release();
	unique_ptr<TiXmlElement> pElem_wCount(new TiXmlElement("UINT32"));
	if(pElem_wCount == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wCount->SetAttribute("name", "wCount");
	pElem_wCount->SetAttribute("value", NumberToString(s.wCount).c_str());
	pElem_wCount->SetAttribute("comment", ToUTF8Ptr("道具数量"));
	if(rElement.LinkEndChild(pElem_wCount.get()) != NULL)
		pElem_wCount.release();
	unique_ptr<TiXmlElement> pElem_eBindType(new TiXmlElement("ItemProt::EBindType"));
	if(pElem_eBindType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eBindType->SetAttribute("name", "eBindType");
	const char* pszEnum_eBindType = NItemProt::EnumValToStr(s.eBindType);
	if(pszEnum_eBindType == NULL)
	{
		LOG_CRI << "EnumValToStr for eBindType fails!";
		return false;
	}
	pElem_eBindType->SetAttribute("value", pszEnum_eBindType);
	pElem_eBindType->SetAttribute("comment", ToUTF8Ptr("绑定类型"));
	if(rElement.LinkEndChild(pElem_eBindType.get()) != NULL)
		pElem_eBindType.release();
	unique_ptr<TiXmlElement> pElem_byExpired(new TiXmlElement("UINT8"));
	if(pElem_byExpired == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byExpired->SetAttribute("name", "byExpired");
	pElem_byExpired->SetAttribute("value", NumberToString(s.byExpired).c_str());
	pElem_byExpired->SetAttribute("comment", ToUTF8Ptr("是否时效，>0 时效物品"));
	if(rElement.LinkEndChild(pElem_byExpired.get()) != NULL)
		pElem_byExpired.release();
	unique_ptr<TiXmlElement> pElem_dwExpireTime(new TiXmlElement("UINT32"));
	if(pElem_dwExpireTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwExpireTime->SetAttribute("name", "dwExpireTime");
	pElem_dwExpireTime->SetAttribute("value", NumberToString(s.dwExpireTime).c_str());
	pElem_dwExpireTime->SetAttribute("comment", ToUTF8Ptr("过期时间"));
	if(rElement.LinkEndChild(pElem_dwExpireTime.get()) != NULL)
		pElem_dwExpireTime.release();
	unique_ptr<TiXmlElement> pElem_qwOPID(new TiXmlElement("UINT64"));
	if(pElem_qwOPID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwOPID->SetAttribute("name", "qwOPID");
	pElem_qwOPID->SetAttribute("value", NumberToString(s.qwOPID).c_str());
	pElem_qwOPID->SetAttribute("comment", ToUTF8Ptr("操作ID"));
	if(rElement.LinkEndChild(pElem_qwOPID.get()) != NULL)
		pElem_qwOPID.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecMailItemInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SMailItemInfo s;
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

bool VectorToXML(const TVecMailItemInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SMailItemInfo"));
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

SMailBaseAttachment::SMailBaseAttachment() { }

CInArchive& operator>>(CInArchive& src, SMailBaseAttachment& s)
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

COutArchive& operator<<(COutArchive& src, const SMailBaseAttachment& s)
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

CInArchive& operator>>(CInArchive& src, SMailBaseAttachment_Wrapper& rWrapper)
{
	EType_SMailBaseAttachment eType = eType_SMailBaseAttachment;
	src >> (UINT8&)eType;
	switch(eType)
	{
	case eType_SMailBaseAttachment:
		{
			rWrapper.ptr.reset(new SMailBaseAttachment);
			src >> (SMailBaseAttachment&)*rWrapper.ptr;
		}
		break;
	case eType_SItemAttachment:
		{
			rWrapper.ptr.reset(new SItemAttachment);
			src >> (SItemAttachment&)*rWrapper.ptr;
		}
		break;
	case eType_SItemBaseCT:
		{
			rWrapper.ptr.reset(new SItemBaseCT);
			src >> (SItemBaseCT&)*rWrapper.ptr;
		}
		break;
	default:
		throw "Unknown value for EType_SMailBaseAttachment";
		break;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SMailBaseAttachment_Wrapper& rWrapper)
{
	if(rWrapper.ptr != NULL)
	{
		src << (UINT8)rWrapper.ptr->GetClassType();
		switch(rWrapper.ptr->GetClassType())
		{
		case eType_SMailBaseAttachment:
			src << (SMailBaseAttachment&)*rWrapper.ptr;
			break;
		case eType_SItemAttachment:
			src << (SItemAttachment&)*rWrapper.ptr;
			break;
		case eType_SItemBaseCT:
			src << (SItemBaseCT&)*rWrapper.ptr;
			break;
		default:
			throw "Unknown value for EType_SMailBaseAttachment";
			break;
		}
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecMailAttachment& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SMailBaseAttachment_Wrapper wrapper;
		src >> wrapper;
		vec[i] = wrapper.ptr;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecMailAttachment& vec)
{
	if(vec.size() > 0x7FFF)
		throw "Vector Size Too Large!";
	UINT16 wSize = (UINT16)vec.size();
	src.WriteContainerSize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SMailBaseAttachment_Wrapper wrapper;
		wrapper.ptr = vec[i];
		src << wrapper;
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SMailBaseAttachment& s)
{
	if(strcmp(rElement.Value(), "SMailBaseAttachment") != 0)
	{
		LOG_CRI << "rElement is not SMailBaseAttachment!";
		return false;
	}
	return true;
}

bool ToXML(const SMailBaseAttachment& s, TiXmlElement& rElement)
{
	rElement.SetValue("SMailBaseAttachment");
	rElement.SetAttribute("type", ToUTF8Ptr("邮件附件"));
	return true;
}

bool SuperFromXML(TiXmlElement& rElement, SMailBaseAttachmentPtr& p)
{
	const char* pszName = rElement.Value();
	if(pszName == NULL)
	{
		LOG_CRI << "Element Name is empty!";
		return false;
	}
	if(strcmp(pszName, "SMailBaseAttachment") == 0)
	{
		SMailBaseAttachmentPtr pStruct(new SMailBaseAttachment);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SMailBaseAttachment";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SMailBaseAttachment FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SItemAttachment") == 0)
	{
		SItemAttachmentPtr pStruct(new SItemAttachment);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SItemAttachment";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SItemAttachment FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SItemBaseCT") == 0)
	{
		SItemBaseCTPtr pStruct(new SItemBaseCT);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SItemBaseCT";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SItemBaseCT FromXML fails!";
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

bool SuperToXML(const SMailBaseAttachment& s, TiXmlElement& rElement)
{
	switch(s.GetClassType())
	{
	case eType_SMailBaseAttachment:
		return ToXML((SMailBaseAttachment&)s, rElement);
	case eType_SItemAttachment:
		return ToXML((SItemAttachment&)s, rElement);
	case eType_SItemBaseCT:
		return ToXML((SItemBaseCT&)s, rElement);
	default:
		LOG_CRI << "Invalid type: " << s.GetClassType();
		return false;
	}
}

bool VectorFromXML(TiXmlElement& rElement, TVecMailAttachment& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SMailBaseAttachmentPtr p;
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

bool VectorToXML(const TVecMailAttachment& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SMailBaseAttachment"));
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

SItemAttachment::SItemAttachment() { }

SItemAttachment::SItemAttachment(SItemAttachment&& src) : SMailBaseAttachment(src), vecItemInfo(move(src.vecItemInfo)) { }

SItemAttachment& SItemAttachment::operator=(SItemAttachment&& rhs)
{
	if(this != &rhs)
	{
		this->~SItemAttachment();
		new (this) SItemAttachment(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SItemAttachment& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (SMailBaseAttachment&)s;
	src >> s.vecItemInfo;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SItemAttachment& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const SMailBaseAttachment&)s;
	src << s.vecItemInfo;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SItemAttachment& s)
{
	if(strcmp(rElement.Value(), "SItemAttachment") != 0)
	{
		LOG_CRI << "rElement is not SItemAttachment!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for SMailBaseAttachment is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (SMailBaseAttachment&)s))
	{
		LOG_CRI << "FromXML for: SMailBaseAttachment fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecItemInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecMailItemInfo") != 0)
	{
		LOG_CRI << "pElemChild is not TVecMailItemInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecItemInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not vecItemInfo!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecItemInfo))
	{
		LOG_CRI << "VectorFromXML for vecItemInfo fails!";
		return false;
	}
	return true;
}

bool ToXML(const SItemAttachment& s, TiXmlElement& rElement)
{
	rElement.SetValue("SItemAttachment");
	rElement.SetAttribute("type", ToUTF8Ptr("物品附件"));
	unique_ptr<TiXmlElement> pElem_SMailBaseAttachment(new TiXmlElement("SMailBaseAttachment"));
	if(pElem_SMailBaseAttachment == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const SMailBaseAttachment&)s, *pElem_SMailBaseAttachment))
	{
		LOG_CRI << "SMailBaseAttachment ToXML fails!";
		return false;
	}
	pElem_SMailBaseAttachment->SetAttribute("type", ToUTF8Ptr("邮件附件"));
	pElem_SMailBaseAttachment->SetAttribute("comment", ToUTF8Ptr("父类SMailBaseAttachment部分"));
	if(rElement.LinkEndChild(pElem_SMailBaseAttachment.get()) != NULL)
		pElem_SMailBaseAttachment.release();
	unique_ptr<TiXmlElement> pElem_vecItemInfo(new TiXmlElement("TVecMailItemInfo"));
	if(pElem_vecItemInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecItemInfo->SetAttribute("name", "vecItemInfo");
	if(!VectorToXML(s.vecItemInfo, *pElem_vecItemInfo))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecItemInfo->SetAttribute("comment", ToUTF8Ptr("物品"));
	if(rElement.LinkEndChild(pElem_vecItemInfo.get()) != NULL)
		pElem_vecItemInfo.release();
	return true;
}

#endif

SItemBaseCT::SItemBaseCT() { }

SItemBaseCT::SItemBaseCT(SItemBaseCT&& src) : SMailBaseAttachment(src), vecItems(move(src.vecItems)) { }

SItemBaseCT& SItemBaseCT::operator=(SItemBaseCT&& rhs)
{
	if(this != &rhs)
	{
		this->~SItemBaseCT();
		new (this) SItemBaseCT(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SItemBaseCT& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (SMailBaseAttachment&)s;
	src >> s.vecItems;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SItemBaseCT& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const SMailBaseAttachment&)s;
	src << s.vecItems;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SItemBaseCT& s)
{
	if(strcmp(rElement.Value(), "SItemBaseCT") != 0)
	{
		LOG_CRI << "rElement is not SItemBaseCT!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for SMailBaseAttachment is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (SMailBaseAttachment&)s))
	{
		LOG_CRI << "FromXML for: SMailBaseAttachment fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecItems is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "ItemProt::TVecItem") != 0)
	{
		LOG_CRI << "pElemChild is not ItemProt::TVecItem!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecItems") != 0)
	{
		LOG_CRI << "Attribute: name is not vecItems!";
		return false;
	}
	if(!NItemProt::VectorFromXML(*pElemChild, s.vecItems))
	{
		LOG_CRI << "VectorFromXML for vecItems fails!";
		return false;
	}
	return true;
}

bool ToXML(const SItemBaseCT& s, TiXmlElement& rElement)
{
	rElement.SetValue("SItemBaseCT");
	rElement.SetAttribute("type", ToUTF8Ptr("物品附件:具体物品对象"));
	unique_ptr<TiXmlElement> pElem_SMailBaseAttachment(new TiXmlElement("SMailBaseAttachment"));
	if(pElem_SMailBaseAttachment == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const SMailBaseAttachment&)s, *pElem_SMailBaseAttachment))
	{
		LOG_CRI << "SMailBaseAttachment ToXML fails!";
		return false;
	}
	pElem_SMailBaseAttachment->SetAttribute("type", ToUTF8Ptr("邮件附件"));
	pElem_SMailBaseAttachment->SetAttribute("comment", ToUTF8Ptr("父类SMailBaseAttachment部分"));
	if(rElement.LinkEndChild(pElem_SMailBaseAttachment.get()) != NULL)
		pElem_SMailBaseAttachment.release();
	unique_ptr<TiXmlElement> pElem_vecItems(new TiXmlElement("ItemProt::TVecItem"));
	if(pElem_vecItems == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecItems->SetAttribute("name", "vecItems");
	if(!NItemProt::VectorToXML(s.vecItems, *pElem_vecItems))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecItems->SetAttribute("comment", ToUTF8Ptr("物品"));
	if(rElement.LinkEndChild(pElem_vecItems.get()) != NULL)
		pElem_vecItems.release();
	return true;
}

#endif

SMailDetail::SMailDetail() : qwMailID(0), eMailState((EMailState)0), dwSendTime(0), byGeted(0), eMailType((EMailType)0) { }

SMailDetail::SMailDetail(SMailDetail&& src) : qwMailID(src.qwMailID), eMailState(src.eMailState), dwSendTime(src.dwSendTime), byGeted(src.byGeted), eMailType(src.eMailType), 
			vecMailAttachment(move(src.vecMailAttachment)), strTitle(move(src.strTitle)), strSendName(move(src.strSendName)), strMessage(move(src.strMessage)) { }

SMailDetail& SMailDetail::operator=(SMailDetail&& rhs)
{
	if(this != &rhs)
	{
		this->~SMailDetail();
		new (this) SMailDetail(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SMailDetail& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwMailID;
	src >> (UINT8&)s.eMailState;
	src >> s.dwSendTime;
	src >> s.byGeted;
	src >> (UINT8&)s.eMailType;
	src >> s.vecMailAttachment;
	src >> s.strTitle;
	src >> s.strSendName;
	src >> s.strMessage;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SMailDetail& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.qwMailID;
	src << (UINT8&)s.eMailState;
	src << s.dwSendTime;
	src << s.byGeted;
	src << (UINT8&)s.eMailType;
	src << s.vecMailAttachment;
	src << s.strTitle;
	src << s.strSendName;
	src << s.strMessage;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SMailDetail& s)
{
	if(strcmp(rElement.Value(), "SMailDetail") != 0)
	{
		LOG_CRI << "rElement is not SMailDetail!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwMailID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwMailID") != 0)
	{
		LOG_CRI << "Attribute: name is not qwMailID!";
		return false;
	}
	const char* pszVal_qwMailID = pElemChild->Attribute("value");
	if(pszVal_qwMailID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwMailID, s.qwMailID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eMailState is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "EMailState") != 0)
	{
		LOG_CRI << "pElemChild is not EMailState!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eMailState") != 0)
	{
		LOG_CRI << "Attribute: name is not eMailState!";
		return false;
	}
	const char* pszVal_eMailState = pElemChild->Attribute("value");
	if(pszVal_eMailState == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!EnumStrToVal(pszVal_eMailState, s.eMailState))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwSendTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwSendTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwSendTime!";
		return false;
	}
	const char* pszVal_dwSendTime = pElemChild->Attribute("value");
	if(pszVal_dwSendTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwSendTime, s.dwSendTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byGeted is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byGeted") != 0)
	{
		LOG_CRI << "Attribute: name is not byGeted!";
		return false;
	}
	const char* pszVal_byGeted = pElemChild->Attribute("value");
	if(pszVal_byGeted == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byGeted, s.byGeted))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eMailType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "EMailType") != 0)
	{
		LOG_CRI << "pElemChild is not EMailType!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eMailType") != 0)
	{
		LOG_CRI << "Attribute: name is not eMailType!";
		return false;
	}
	const char* pszVal_eMailType = pElemChild->Attribute("value");
	if(pszVal_eMailType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!EnumStrToVal(pszVal_eMailType, s.eMailType))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecMailAttachment is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecMailAttachment") != 0)
	{
		LOG_CRI << "pElemChild is not TVecMailAttachment!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecMailAttachment") != 0)
	{
		LOG_CRI << "Attribute: name is not vecMailAttachment!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecMailAttachment))
	{
		LOG_CRI << "VectorFromXML for vecMailAttachment fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strTitle is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strTitle") != 0)
	{
		LOG_CRI << "Attribute: name is not strTitle!";
		return false;
	}
	const char* pszVal_strTitle = pElemChild->Attribute("value");
	if(pszVal_strTitle == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strTitle = pszVal_strTitle;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strSendName is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strSendName") != 0)
	{
		LOG_CRI << "Attribute: name is not strSendName!";
		return false;
	}
	const char* pszVal_strSendName = pElemChild->Attribute("value");
	if(pszVal_strSendName == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strSendName = pszVal_strSendName;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strMessage is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strMessage") != 0)
	{
		LOG_CRI << "Attribute: name is not strMessage!";
		return false;
	}
	const char* pszVal_strMessage = pElemChild->Attribute("value");
	if(pszVal_strMessage == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strMessage = pszVal_strMessage;
	return true;
}

bool ToXML(const SMailDetail& s, TiXmlElement& rElement)
{
	rElement.SetValue("SMailDetail");
	rElement.SetAttribute("type", ToUTF8Ptr("邮件详细信息"));
	unique_ptr<TiXmlElement> pElem_qwMailID(new TiXmlElement("UINT64"));
	if(pElem_qwMailID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwMailID->SetAttribute("name", "qwMailID");
	pElem_qwMailID->SetAttribute("value", NumberToString(s.qwMailID).c_str());
	pElem_qwMailID->SetAttribute("comment", ToUTF8Ptr("邮件ID"));
	if(rElement.LinkEndChild(pElem_qwMailID.get()) != NULL)
		pElem_qwMailID.release();
	unique_ptr<TiXmlElement> pElem_eMailState(new TiXmlElement("EMailState"));
	if(pElem_eMailState == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eMailState->SetAttribute("name", "eMailState");
	const char* pszEnum_eMailState = EnumValToStr(s.eMailState);
	if(pszEnum_eMailState == NULL)
	{
		LOG_CRI << "EnumValToStr for EMailState fails!";
		return false;
	}
	pElem_eMailState->SetAttribute("value", pszEnum_eMailState);
	pElem_eMailState->SetAttribute("comment", ToUTF8Ptr("邮件状态"));
	if(rElement.LinkEndChild(pElem_eMailState.get()) != NULL)
		pElem_eMailState.release();
	unique_ptr<TiXmlElement> pElem_dwSendTime(new TiXmlElement("UINT32"));
	if(pElem_dwSendTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwSendTime->SetAttribute("name", "dwSendTime");
	pElem_dwSendTime->SetAttribute("value", NumberToString(s.dwSendTime).c_str());
	pElem_dwSendTime->SetAttribute("comment", ToUTF8Ptr("邮件发送时间"));
	if(rElement.LinkEndChild(pElem_dwSendTime.get()) != NULL)
		pElem_dwSendTime.release();
	unique_ptr<TiXmlElement> pElem_byGeted(new TiXmlElement("UINT8"));
	if(pElem_byGeted == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byGeted->SetAttribute("name", "byGeted");
	pElem_byGeted->SetAttribute("value", NumberToString(s.byGeted).c_str());
	pElem_byGeted->SetAttribute("comment", ToUTF8Ptr("255表示有附件，并且已经领取，其他为按位表示有附件的类型"));
	if(rElement.LinkEndChild(pElem_byGeted.get()) != NULL)
		pElem_byGeted.release();
	unique_ptr<TiXmlElement> pElem_eMailType(new TiXmlElement("EMailType"));
	if(pElem_eMailType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eMailType->SetAttribute("name", "eMailType");
	const char* pszEnum_eMailType = EnumValToStr(s.eMailType);
	if(pszEnum_eMailType == NULL)
	{
		LOG_CRI << "EnumValToStr for EMailType fails!";
		return false;
	}
	pElem_eMailType->SetAttribute("value", pszEnum_eMailType);
	pElem_eMailType->SetAttribute("comment", ToUTF8Ptr("邮件类型"));
	if(rElement.LinkEndChild(pElem_eMailType.get()) != NULL)
		pElem_eMailType.release();
	unique_ptr<TiXmlElement> pElem_vecMailAttachment(new TiXmlElement("TVecMailAttachment"));
	if(pElem_vecMailAttachment == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecMailAttachment->SetAttribute("name", "vecMailAttachment");
	if(!VectorToXML(s.vecMailAttachment, *pElem_vecMailAttachment))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecMailAttachment->SetAttribute("comment", ToUTF8Ptr("附件"));
	if(rElement.LinkEndChild(pElem_vecMailAttachment.get()) != NULL)
		pElem_vecMailAttachment.release();
	unique_ptr<TiXmlElement> pElem_strTitle(new TiXmlElement("string"));
	if(pElem_strTitle == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strTitle->SetAttribute("name", "strTitle");
	pElem_strTitle->SetAttribute("value", s.strTitle.c_str());
	pElem_strTitle->SetAttribute("comment", ToUTF8Ptr("邮件标题"));
	if(rElement.LinkEndChild(pElem_strTitle.get()) != NULL)
		pElem_strTitle.release();
	unique_ptr<TiXmlElement> pElem_strSendName(new TiXmlElement("string"));
	if(pElem_strSendName == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strSendName->SetAttribute("name", "strSendName");
	pElem_strSendName->SetAttribute("value", s.strSendName.c_str());
	pElem_strSendName->SetAttribute("comment", ToUTF8Ptr("发送者"));
	if(rElement.LinkEndChild(pElem_strSendName.get()) != NULL)
		pElem_strSendName.release();
	unique_ptr<TiXmlElement> pElem_strMessage(new TiXmlElement("string"));
	if(pElem_strMessage == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strMessage->SetAttribute("name", "strMessage");
	pElem_strMessage->SetAttribute("value", s.strMessage.c_str());
	pElem_strMessage->SetAttribute("comment", ToUTF8Ptr("信息"));
	if(rElement.LinkEndChild(pElem_strMessage.get()) != NULL)
		pElem_strMessage.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecMailDetail& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SMailDetail s;
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

bool VectorToXML(const TVecMailDetail& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SMailDetail"));
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

} //namespace NMailProt
