/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    AnswerProt.cpp
//  Purpose:      答题协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "AnswerProt.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NAnswerProt
{

#ifdef PROT_USE_XML

const char* EnumValToStr(EAnswerResult e)
{
	switch(e)
	{
	case EAnswerResult_Suc:
		return "EAnswerResult_Suc";
	case EAnswerResult_Lack:
		return "EAnswerResult_Lack";
	case EAnswerResult_No:
		return "EAnswerResult_No";
	case EAnswerResult_Err:
		return "EAnswerResult_Err";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EAnswerResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EAnswerResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("EAnswerResult_Suc", EAnswerResult_Suc));
		mapStr2Val.insert(make_pair("EAnswerResult_Lack", EAnswerResult_Lack));
		mapStr2Val.insert(make_pair("EAnswerResult_No", EAnswerResult_No));
		mapStr2Val.insert(make_pair("EAnswerResult_Err", EAnswerResult_Err));
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

const char* EnumValToStr(EAnswerSkill e)
{
	switch(e)
	{
	case EAnswerSkill_NONE:
		return "EAnswerSkill_NONE";
	case EAnswerSkill_1:
		return "EAnswerSkill_1";
	case EAnswerSkill_2:
		return "EAnswerSkill_2";
	case EAnswerSkill_3:
		return "EAnswerSkill_3";
	case EAnswerSkill_END:
		return "EAnswerSkill_END";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EAnswerSkill& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EAnswerSkill> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("EAnswerSkill_NONE", EAnswerSkill_NONE));
		mapStr2Val.insert(make_pair("EAnswerSkill_1", EAnswerSkill_1));
		mapStr2Val.insert(make_pair("EAnswerSkill_2", EAnswerSkill_2));
		mapStr2Val.insert(make_pair("EAnswerSkill_3", EAnswerSkill_3));
		mapStr2Val.insert(make_pair("EAnswerSkill_END", EAnswerSkill_END));
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

SAnswerTime::SAnswerTime() : dwReadTime(0), dwAnswerTime(0), dwResultTime(0), dwEndTime(0) { }

SAnswerTime::SAnswerTime(UINT32 dwReadTime_, UINT32 dwAnswerTime_, UINT32 dwResultTime_, UINT32 dwEndTime_) : dwReadTime(dwReadTime_), dwAnswerTime(dwAnswerTime_), dwResultTime(dwResultTime_), dwEndTime(dwEndTime_) { }

CInArchive& operator>>(CInArchive& src, SAnswerTime& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.dwReadTime;
	src >> s.dwAnswerTime;
	src >> s.dwResultTime;
	src >> s.dwEndTime;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SAnswerTime& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.dwReadTime;
	src << s.dwAnswerTime;
	src << s.dwResultTime;
	src << s.dwEndTime;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SAnswerTime& s)
{
	if(strcmp(rElement.Value(), "SAnswerTime") != 0)
	{
		LOG_CRI << "rElement is not SAnswerTime!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwReadTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwReadTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwReadTime!";
		return false;
	}
	const char* pszVal_dwReadTime = pElemChild->Attribute("value");
	if(pszVal_dwReadTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwReadTime, s.dwReadTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwAnswerTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwAnswerTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwAnswerTime!";
		return false;
	}
	const char* pszVal_dwAnswerTime = pElemChild->Attribute("value");
	if(pszVal_dwAnswerTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwAnswerTime, s.dwAnswerTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwResultTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwResultTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwResultTime!";
		return false;
	}
	const char* pszVal_dwResultTime = pElemChild->Attribute("value");
	if(pszVal_dwResultTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwResultTime, s.dwResultTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwEndTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwEndTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwEndTime!";
		return false;
	}
	const char* pszVal_dwEndTime = pElemChild->Attribute("value");
	if(pszVal_dwEndTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwEndTime, s.dwEndTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SAnswerTime& s, TiXmlElement& rElement)
{
	rElement.SetValue("SAnswerTime");
	rElement.SetAttribute("type", ToUTF8Ptr("答题时间控制"));
	unique_ptr<TiXmlElement> pElem_dwReadTime(new TiXmlElement("UINT32"));
	if(pElem_dwReadTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwReadTime->SetAttribute("name", "dwReadTime");
	pElem_dwReadTime->SetAttribute("value", NumberToString(s.dwReadTime).c_str());
	pElem_dwReadTime->SetAttribute("comment", ToUTF8Ptr("玩家阅读时间"));
	if(rElement.LinkEndChild(pElem_dwReadTime.get()) != NULL)
		pElem_dwReadTime.release();
	unique_ptr<TiXmlElement> pElem_dwAnswerTime(new TiXmlElement("UINT32"));
	if(pElem_dwAnswerTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwAnswerTime->SetAttribute("name", "dwAnswerTime");
	pElem_dwAnswerTime->SetAttribute("value", NumberToString(s.dwAnswerTime).c_str());
	pElem_dwAnswerTime->SetAttribute("comment", ToUTF8Ptr("玩家答题时间"));
	if(rElement.LinkEndChild(pElem_dwAnswerTime.get()) != NULL)
		pElem_dwAnswerTime.release();
	unique_ptr<TiXmlElement> pElem_dwResultTime(new TiXmlElement("UINT32"));
	if(pElem_dwResultTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwResultTime->SetAttribute("name", "dwResultTime");
	pElem_dwResultTime->SetAttribute("value", NumberToString(s.dwResultTime).c_str());
	pElem_dwResultTime->SetAttribute("comment", ToUTF8Ptr("玩家显示结果时间"));
	if(rElement.LinkEndChild(pElem_dwResultTime.get()) != NULL)
		pElem_dwResultTime.release();
	unique_ptr<TiXmlElement> pElem_dwEndTime(new TiXmlElement("UINT32"));
	if(pElem_dwEndTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwEndTime->SetAttribute("name", "dwEndTime");
	pElem_dwEndTime->SetAttribute("value", NumberToString(s.dwEndTime).c_str());
	pElem_dwEndTime->SetAttribute("comment", ToUTF8Ptr("玩家答题结束时间"));
	if(rElement.LinkEndChild(pElem_dwEndTime.get()) != NULL)
		pElem_dwEndTime.release();
	return true;
}

#endif

SAnswerSkill::SAnswerSkill() : eSkillType((EAnswerSkill)0), byRemain(0) { }

SAnswerSkill::SAnswerSkill(EAnswerSkill eSkillType_, UINT8 byRemain_) : eSkillType(eSkillType_), byRemain(byRemain_) { }

CInArchive& operator>>(CInArchive& src, SAnswerSkill& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (UINT8&)s.eSkillType;
	src >> s.byRemain;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SAnswerSkill& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (UINT8&)s.eSkillType;
	src << s.byRemain;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SAnswerSkill& s)
{
	if(strcmp(rElement.Value(), "SAnswerSkill") != 0)
	{
		LOG_CRI << "rElement is not SAnswerSkill!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eSkillType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "EAnswerSkill") != 0)
	{
		LOG_CRI << "pElemChild is not EAnswerSkill!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eSkillType") != 0)
	{
		LOG_CRI << "Attribute: name is not eSkillType!";
		return false;
	}
	const char* pszVal_eSkillType = pElemChild->Attribute("value");
	if(pszVal_eSkillType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!EnumStrToVal(pszVal_eSkillType, s.eSkillType))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byRemain is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byRemain") != 0)
	{
		LOG_CRI << "Attribute: name is not byRemain!";
		return false;
	}
	const char* pszVal_byRemain = pElemChild->Attribute("value");
	if(pszVal_byRemain == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byRemain, s.byRemain))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SAnswerSkill& s, TiXmlElement& rElement)
{
	rElement.SetValue("SAnswerSkill");
	rElement.SetAttribute("type", ToUTF8Ptr("答题技能信息"));
	unique_ptr<TiXmlElement> pElem_eSkillType(new TiXmlElement("EAnswerSkill"));
	if(pElem_eSkillType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eSkillType->SetAttribute("name", "eSkillType");
	const char* pszEnum_eSkillType = EnumValToStr(s.eSkillType);
	if(pszEnum_eSkillType == NULL)
	{
		LOG_CRI << "EnumValToStr for EAnswerSkill fails!";
		return false;
	}
	pElem_eSkillType->SetAttribute("value", pszEnum_eSkillType);
	pElem_eSkillType->SetAttribute("comment", ToUTF8Ptr("技能ID"));
	if(rElement.LinkEndChild(pElem_eSkillType.get()) != NULL)
		pElem_eSkillType.release();
	unique_ptr<TiXmlElement> pElem_byRemain(new TiXmlElement("UINT8"));
	if(pElem_byRemain == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byRemain->SetAttribute("name", "byRemain");
	pElem_byRemain->SetAttribute("value", NumberToString(s.byRemain).c_str());
	pElem_byRemain->SetAttribute("comment", ToUTF8Ptr("剩余次数"));
	if(rElement.LinkEndChild(pElem_byRemain.get()) != NULL)
		pElem_byRemain.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecAnswerSkill& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SAnswerSkill s;
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

bool VectorToXML(const TVecAnswerSkill& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SAnswerSkill"));
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

SAnswerTopic::SAnswerTopic() : byIndex(0), dwTopicID(0), byAnswer1(0), byAnswer2(0), byAnswer3(0), 
			byAnswer4(0), dwRemain(0) { }

SAnswerTopic::SAnswerTopic(UINT8 byIndex_, UINT32 dwTopicID_, UINT8 byAnswer1_, UINT8 byAnswer2_, UINT8 byAnswer3_, 
			UINT8 byAnswer4_, const SAnswerTime& sTimeInfo_, UINT32 dwRemain_)
			: byIndex(byIndex_), dwTopicID(dwTopicID_), byAnswer1(byAnswer1_), byAnswer2(byAnswer2_), byAnswer3(byAnswer3_), 
			byAnswer4(byAnswer4_), sTimeInfo(sTimeInfo_), dwRemain(dwRemain_) { }

CInArchive& operator>>(CInArchive& src, SAnswerTopic& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.byIndex;
	src >> s.dwTopicID;
	src >> s.byAnswer1;
	src >> s.byAnswer2;
	src >> s.byAnswer3;
	src >> s.byAnswer4;
	src >> s.sTimeInfo;
	src >> s.dwRemain;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SAnswerTopic& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.byIndex;
	src << s.dwTopicID;
	src << s.byAnswer1;
	src << s.byAnswer2;
	src << s.byAnswer3;
	src << s.byAnswer4;
	src << s.sTimeInfo;
	src << s.dwRemain;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SAnswerTopic& s)
{
	if(strcmp(rElement.Value(), "SAnswerTopic") != 0)
	{
		LOG_CRI << "rElement is not SAnswerTopic!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
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
		LOG_CRI << "pElemChild for dwTopicID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwTopicID") != 0)
	{
		LOG_CRI << "Attribute: name is not dwTopicID!";
		return false;
	}
	const char* pszVal_dwTopicID = pElemChild->Attribute("value");
	if(pszVal_dwTopicID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwTopicID, s.dwTopicID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byAnswer1 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byAnswer1") != 0)
	{
		LOG_CRI << "Attribute: name is not byAnswer1!";
		return false;
	}
	const char* pszVal_byAnswer1 = pElemChild->Attribute("value");
	if(pszVal_byAnswer1 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byAnswer1, s.byAnswer1))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byAnswer2 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byAnswer2") != 0)
	{
		LOG_CRI << "Attribute: name is not byAnswer2!";
		return false;
	}
	const char* pszVal_byAnswer2 = pElemChild->Attribute("value");
	if(pszVal_byAnswer2 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byAnswer2, s.byAnswer2))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byAnswer3 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byAnswer3") != 0)
	{
		LOG_CRI << "Attribute: name is not byAnswer3!";
		return false;
	}
	const char* pszVal_byAnswer3 = pElemChild->Attribute("value");
	if(pszVal_byAnswer3 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byAnswer3, s.byAnswer3))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byAnswer4 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byAnswer4") != 0)
	{
		LOG_CRI << "Attribute: name is not byAnswer4!";
		return false;
	}
	const char* pszVal_byAnswer4 = pElemChild->Attribute("value");
	if(pszVal_byAnswer4 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byAnswer4, s.byAnswer4))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for sTimeInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "SAnswerTime") != 0)
	{
		LOG_CRI << "pElemChild is not SAnswerTime!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "sTimeInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not sTimeInfo!";
		return false;
	}
	if(!FromXML(*pElemChild, s.sTimeInfo))
	{
		LOG_CRI << "FromXML for: sTimeInfo fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwRemain is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwRemain") != 0)
	{
		LOG_CRI << "Attribute: name is not dwRemain!";
		return false;
	}
	const char* pszVal_dwRemain = pElemChild->Attribute("value");
	if(pszVal_dwRemain == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwRemain, s.dwRemain))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SAnswerTopic& s, TiXmlElement& rElement)
{
	rElement.SetValue("SAnswerTopic");
	rElement.SetAttribute("type", ToUTF8Ptr("答题题目信息"));
	unique_ptr<TiXmlElement> pElem_byIndex(new TiXmlElement("UINT8"));
	if(pElem_byIndex == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byIndex->SetAttribute("name", "byIndex");
	pElem_byIndex->SetAttribute("value", NumberToString(s.byIndex).c_str());
	pElem_byIndex->SetAttribute("comment", ToUTF8Ptr("编号"));
	if(rElement.LinkEndChild(pElem_byIndex.get()) != NULL)
		pElem_byIndex.release();
	unique_ptr<TiXmlElement> pElem_dwTopicID(new TiXmlElement("UINT32"));
	if(pElem_dwTopicID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwTopicID->SetAttribute("name", "dwTopicID");
	pElem_dwTopicID->SetAttribute("value", NumberToString(s.dwTopicID).c_str());
	pElem_dwTopicID->SetAttribute("comment", ToUTF8Ptr("题目ID"));
	if(rElement.LinkEndChild(pElem_dwTopicID.get()) != NULL)
		pElem_dwTopicID.release();
	unique_ptr<TiXmlElement> pElem_byAnswer1(new TiXmlElement("UINT8"));
	if(pElem_byAnswer1 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byAnswer1->SetAttribute("name", "byAnswer1");
	pElem_byAnswer1->SetAttribute("value", NumberToString(s.byAnswer1).c_str());
	pElem_byAnswer1->SetAttribute("comment", ToUTF8Ptr("答案1"));
	if(rElement.LinkEndChild(pElem_byAnswer1.get()) != NULL)
		pElem_byAnswer1.release();
	unique_ptr<TiXmlElement> pElem_byAnswer2(new TiXmlElement("UINT8"));
	if(pElem_byAnswer2 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byAnswer2->SetAttribute("name", "byAnswer2");
	pElem_byAnswer2->SetAttribute("value", NumberToString(s.byAnswer2).c_str());
	pElem_byAnswer2->SetAttribute("comment", ToUTF8Ptr("答案2"));
	if(rElement.LinkEndChild(pElem_byAnswer2.get()) != NULL)
		pElem_byAnswer2.release();
	unique_ptr<TiXmlElement> pElem_byAnswer3(new TiXmlElement("UINT8"));
	if(pElem_byAnswer3 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byAnswer3->SetAttribute("name", "byAnswer3");
	pElem_byAnswer3->SetAttribute("value", NumberToString(s.byAnswer3).c_str());
	pElem_byAnswer3->SetAttribute("comment", ToUTF8Ptr("答案3"));
	if(rElement.LinkEndChild(pElem_byAnswer3.get()) != NULL)
		pElem_byAnswer3.release();
	unique_ptr<TiXmlElement> pElem_byAnswer4(new TiXmlElement("UINT8"));
	if(pElem_byAnswer4 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byAnswer4->SetAttribute("name", "byAnswer4");
	pElem_byAnswer4->SetAttribute("value", NumberToString(s.byAnswer4).c_str());
	pElem_byAnswer4->SetAttribute("comment", ToUTF8Ptr("答案4"));
	if(rElement.LinkEndChild(pElem_byAnswer4.get()) != NULL)
		pElem_byAnswer4.release();
	unique_ptr<TiXmlElement> pElem_sTimeInfo(new TiXmlElement("SAnswerTime"));
	if(pElem_sTimeInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_sTimeInfo->SetAttribute("name", "sTimeInfo");
	if(!ToXML(s.sTimeInfo, *pElem_sTimeInfo))
	{
		LOG_CRI << "sTimeInfo ToXML fails!";
		return false;
	}
	pElem_sTimeInfo->SetAttribute("comment", ToUTF8Ptr("题目时间"));
	if(rElement.LinkEndChild(pElem_sTimeInfo.get()) != NULL)
		pElem_sTimeInfo.release();
	unique_ptr<TiXmlElement> pElem_dwRemain(new TiXmlElement("UINT32"));
	if(pElem_dwRemain == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwRemain->SetAttribute("name", "dwRemain");
	pElem_dwRemain->SetAttribute("value", NumberToString(s.dwRemain).c_str());
	pElem_dwRemain->SetAttribute("comment", ToUTF8Ptr("剩余题目数"));
	if(rElement.LinkEndChild(pElem_dwRemain.get()) != NULL)
		pElem_dwRemain.release();
	return true;
}

#endif

SAnswerPlayer::SAnswerPlayer() : qwRoleID(0), bRight(false), dwThisScore(0), dwScore(0), dwRank(0), 
			dwRight(0), dwUntilFail(0) { }

SAnswerPlayer::SAnswerPlayer(UINT64 qwRoleID_, bool bRight_, UINT32 dwThisScore_, UINT32 dwScore_, UINT32 dwRank_, 
			UINT32 dwRight_, UINT32 dwUntilFail_, const TVecAnswerSkill& vecSkillInfo_)
			: qwRoleID(qwRoleID_), bRight(bRight_), dwThisScore(dwThisScore_), dwScore(dwScore_), dwRank(dwRank_), 
			dwRight(dwRight_), dwUntilFail(dwUntilFail_), vecSkillInfo(vecSkillInfo_) { }

SAnswerPlayer::SAnswerPlayer(SAnswerPlayer&& src) : qwRoleID(src.qwRoleID), bRight(src.bRight), dwThisScore(src.dwThisScore), dwScore(src.dwScore), dwRank(src.dwRank), 
			dwRight(src.dwRight), dwUntilFail(src.dwUntilFail), vecSkillInfo(move(src.vecSkillInfo)) { }

SAnswerPlayer& SAnswerPlayer::operator=(SAnswerPlayer&& rhs)
{
	if(this != &rhs)
	{
		this->~SAnswerPlayer();
		new (this) SAnswerPlayer(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SAnswerPlayer& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwRoleID;
	src >> s.bRight;
	src >> s.dwThisScore;
	src >> s.dwScore;
	src >> s.dwRank;
	src >> s.dwRight;
	src >> s.dwUntilFail;
	src >> s.vecSkillInfo;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SAnswerPlayer& s)
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
	src << s.bRight;
	src << s.dwThisScore;
	src << s.dwScore;
	src << s.dwRank;
	src << s.dwRight;
	src << s.dwUntilFail;
	src << s.vecSkillInfo;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SAnswerPlayer& s)
{
	if(strcmp(rElement.Value(), "SAnswerPlayer") != 0)
	{
		LOG_CRI << "rElement is not SAnswerPlayer!";
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
		LOG_CRI << "pElemChild for bRight is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "bool") != 0)
	{
		LOG_CRI << "pElemChild is not bool!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "bRight") != 0)
	{
		LOG_CRI << "Attribute: name is not bRight!";
		return false;
	}
	const char* pszVal_bRight = pElemChild->Attribute("value");
	if(pszVal_bRight == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_bRight, s.bRight))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwThisScore is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwThisScore") != 0)
	{
		LOG_CRI << "Attribute: name is not dwThisScore!";
		return false;
	}
	const char* pszVal_dwThisScore = pElemChild->Attribute("value");
	if(pszVal_dwThisScore == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwThisScore, s.dwThisScore))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwScore is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwScore") != 0)
	{
		LOG_CRI << "Attribute: name is not dwScore!";
		return false;
	}
	const char* pszVal_dwScore = pElemChild->Attribute("value");
	if(pszVal_dwScore == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwScore, s.dwScore))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwRank is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwRank") != 0)
	{
		LOG_CRI << "Attribute: name is not dwRank!";
		return false;
	}
	const char* pszVal_dwRank = pElemChild->Attribute("value");
	if(pszVal_dwRank == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwRank, s.dwRank))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwRight is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwRight") != 0)
	{
		LOG_CRI << "Attribute: name is not dwRight!";
		return false;
	}
	const char* pszVal_dwRight = pElemChild->Attribute("value");
	if(pszVal_dwRight == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwRight, s.dwRight))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwUntilFail is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwUntilFail") != 0)
	{
		LOG_CRI << "Attribute: name is not dwUntilFail!";
		return false;
	}
	const char* pszVal_dwUntilFail = pElemChild->Attribute("value");
	if(pszVal_dwUntilFail == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwUntilFail, s.dwUntilFail))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecSkillInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecAnswerSkill") != 0)
	{
		LOG_CRI << "pElemChild is not TVecAnswerSkill!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecSkillInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not vecSkillInfo!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecSkillInfo))
	{
		LOG_CRI << "VectorFromXML for vecSkillInfo fails!";
		return false;
	}
	return true;
}

bool ToXML(const SAnswerPlayer& s, TiXmlElement& rElement)
{
	rElement.SetValue("SAnswerPlayer");
	rElement.SetAttribute("type", ToUTF8Ptr("玩家信息"));
	unique_ptr<TiXmlElement> pElem_qwRoleID(new TiXmlElement("UINT64"));
	if(pElem_qwRoleID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwRoleID->SetAttribute("name", "qwRoleID");
	pElem_qwRoleID->SetAttribute("value", NumberToString(s.qwRoleID).c_str());
	pElem_qwRoleID->SetAttribute("comment", ToUTF8Ptr("玩家ID"));
	if(rElement.LinkEndChild(pElem_qwRoleID.get()) != NULL)
		pElem_qwRoleID.release();
	unique_ptr<TiXmlElement> pElem_bRight(new TiXmlElement("bool"));
	if(pElem_bRight == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_bRight->SetAttribute("name", "bRight");
	pElem_bRight->SetAttribute("value", NumberToString(s.bRight).c_str());
	pElem_bRight->SetAttribute("comment", ToUTF8Ptr("本次答题是否正确"));
	if(rElement.LinkEndChild(pElem_bRight.get()) != NULL)
		pElem_bRight.release();
	unique_ptr<TiXmlElement> pElem_dwThisScore(new TiXmlElement("UINT32"));
	if(pElem_dwThisScore == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwThisScore->SetAttribute("name", "dwThisScore");
	pElem_dwThisScore->SetAttribute("value", NumberToString(s.dwThisScore).c_str());
	pElem_dwThisScore->SetAttribute("comment", ToUTF8Ptr("本题玩家获得积分"));
	if(rElement.LinkEndChild(pElem_dwThisScore.get()) != NULL)
		pElem_dwThisScore.release();
	unique_ptr<TiXmlElement> pElem_dwScore(new TiXmlElement("UINT32"));
	if(pElem_dwScore == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwScore->SetAttribute("name", "dwScore");
	pElem_dwScore->SetAttribute("value", NumberToString(s.dwScore).c_str());
	pElem_dwScore->SetAttribute("comment", ToUTF8Ptr("玩家积分"));
	if(rElement.LinkEndChild(pElem_dwScore.get()) != NULL)
		pElem_dwScore.release();
	unique_ptr<TiXmlElement> pElem_dwRank(new TiXmlElement("UINT32"));
	if(pElem_dwRank == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwRank->SetAttribute("name", "dwRank");
	pElem_dwRank->SetAttribute("value", NumberToString(s.dwRank).c_str());
	pElem_dwRank->SetAttribute("comment", ToUTF8Ptr("玩家排名"));
	if(rElement.LinkEndChild(pElem_dwRank.get()) != NULL)
		pElem_dwRank.release();
	unique_ptr<TiXmlElement> pElem_dwRight(new TiXmlElement("UINT32"));
	if(pElem_dwRight == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwRight->SetAttribute("name", "dwRight");
	pElem_dwRight->SetAttribute("value", NumberToString(s.dwRight).c_str());
	pElem_dwRight->SetAttribute("comment", ToUTF8Ptr("玩家答对题目数"));
	if(rElement.LinkEndChild(pElem_dwRight.get()) != NULL)
		pElem_dwRight.release();
	unique_ptr<TiXmlElement> pElem_dwUntilFail(new TiXmlElement("UINT32"));
	if(pElem_dwUntilFail == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwUntilFail->SetAttribute("name", "dwUntilFail");
	pElem_dwUntilFail->SetAttribute("value", NumberToString(s.dwUntilFail).c_str());
	pElem_dwUntilFail->SetAttribute("comment", ToUTF8Ptr("连续答对题目数"));
	if(rElement.LinkEndChild(pElem_dwUntilFail.get()) != NULL)
		pElem_dwUntilFail.release();
	unique_ptr<TiXmlElement> pElem_vecSkillInfo(new TiXmlElement("TVecAnswerSkill"));
	if(pElem_vecSkillInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecSkillInfo->SetAttribute("name", "vecSkillInfo");
	if(!VectorToXML(s.vecSkillInfo, *pElem_vecSkillInfo))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecSkillInfo->SetAttribute("comment", ToUTF8Ptr("技能信息"));
	if(rElement.LinkEndChild(pElem_vecSkillInfo.get()) != NULL)
		pElem_vecSkillInfo.release();
	return true;
}

#endif

SAnswerRank::SAnswerRank() : dwRank(0), dwScore(0) { }

SAnswerRank::SAnswerRank(UINT32 dwRank_, const std::string& strName_, UINT32 dwScore_) : dwRank(dwRank_), strName(strName_), dwScore(dwScore_) { }

SAnswerRank::SAnswerRank(SAnswerRank&& src) : dwRank(src.dwRank), strName(move(src.strName)), dwScore(src.dwScore) { }

SAnswerRank& SAnswerRank::operator=(SAnswerRank&& rhs)
{
	if(this != &rhs)
	{
		this->~SAnswerRank();
		new (this) SAnswerRank(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SAnswerRank& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.dwRank;
	src >> s.strName;
	src >> s.dwScore;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SAnswerRank& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.dwRank;
	src << s.strName;
	src << s.dwScore;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SAnswerRank& s)
{
	if(strcmp(rElement.Value(), "SAnswerRank") != 0)
	{
		LOG_CRI << "rElement is not SAnswerRank!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwRank is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwRank") != 0)
	{
		LOG_CRI << "Attribute: name is not dwRank!";
		return false;
	}
	const char* pszVal_dwRank = pElemChild->Attribute("value");
	if(pszVal_dwRank == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwRank, s.dwRank))
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
		LOG_CRI << "pElemChild for dwScore is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwScore") != 0)
	{
		LOG_CRI << "Attribute: name is not dwScore!";
		return false;
	}
	const char* pszVal_dwScore = pElemChild->Attribute("value");
	if(pszVal_dwScore == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwScore, s.dwScore))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SAnswerRank& s, TiXmlElement& rElement)
{
	rElement.SetValue("SAnswerRank");
	rElement.SetAttribute("type", ToUTF8Ptr("排名信息"));
	unique_ptr<TiXmlElement> pElem_dwRank(new TiXmlElement("UINT32"));
	if(pElem_dwRank == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwRank->SetAttribute("name", "dwRank");
	pElem_dwRank->SetAttribute("value", NumberToString(s.dwRank).c_str());
	pElem_dwRank->SetAttribute("comment", ToUTF8Ptr("玩家排名"));
	if(rElement.LinkEndChild(pElem_dwRank.get()) != NULL)
		pElem_dwRank.release();
	unique_ptr<TiXmlElement> pElem_strName(new TiXmlElement("string"));
	if(pElem_strName == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strName->SetAttribute("name", "strName");
	pElem_strName->SetAttribute("value", s.strName.c_str());
	pElem_strName->SetAttribute("comment", ToUTF8Ptr("玩家名字"));
	if(rElement.LinkEndChild(pElem_strName.get()) != NULL)
		pElem_strName.release();
	unique_ptr<TiXmlElement> pElem_dwScore(new TiXmlElement("UINT32"));
	if(pElem_dwScore == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwScore->SetAttribute("name", "dwScore");
	pElem_dwScore->SetAttribute("value", NumberToString(s.dwScore).c_str());
	pElem_dwScore->SetAttribute("comment", ToUTF8Ptr("玩家积分"));
	if(rElement.LinkEndChild(pElem_dwScore.get()) != NULL)
		pElem_dwScore.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecAnswerRank& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SAnswerRank s;
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

bool VectorToXML(const TVecAnswerRank& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SAnswerRank"));
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

} //namespace NAnswerProt
