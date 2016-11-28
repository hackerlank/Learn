/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    DBProt.cpp
//  Purpose:      数据库查询协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "DBProt.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NDBProt
{

#ifdef PROT_USE_XML

const char* EnumValToStr(EParamType e)
{
	switch(e)
	{
	case eTypeINT8:
		return "eTypeINT8";
	case eTypeUINT8:
		return "eTypeUINT8";
	case eTypeINT16:
		return "eTypeINT16";
	case eTypeUINT16:
		return "eTypeUINT16";
	case eTypeINT32:
		return "eTypeINT32";
	case eTypeUINT32:
		return "eTypeUINT32";
	case eTypeINT64:
		return "eTypeINT64";
	case eTypeUINT64:
		return "eTypeUINT64";
	case eTypeFloat:
		return "eTypeFloat";
	case eTypeDouble:
		return "eTypeDouble";
	case eTypeString:
		return "eTypeString";
	case eTypeBlob:
		return "eTypeBlob";
	case eTypeDateTime:
		return "eTypeDateTime";
	case eTypeDate:
		return "eTypeDate";
	case eTypeTime:
		return "eTypeTime";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EParamType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EParamType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eTypeINT8", eTypeINT8));
		mapStr2Val.insert(make_pair("eTypeUINT8", eTypeUINT8));
		mapStr2Val.insert(make_pair("eTypeINT16", eTypeINT16));
		mapStr2Val.insert(make_pair("eTypeUINT16", eTypeUINT16));
		mapStr2Val.insert(make_pair("eTypeINT32", eTypeINT32));
		mapStr2Val.insert(make_pair("eTypeUINT32", eTypeUINT32));
		mapStr2Val.insert(make_pair("eTypeINT64", eTypeINT64));
		mapStr2Val.insert(make_pair("eTypeUINT64", eTypeUINT64));
		mapStr2Val.insert(make_pair("eTypeFloat", eTypeFloat));
		mapStr2Val.insert(make_pair("eTypeDouble", eTypeDouble));
		mapStr2Val.insert(make_pair("eTypeString", eTypeString));
		mapStr2Val.insert(make_pair("eTypeBlob", eTypeBlob));
		mapStr2Val.insert(make_pair("eTypeDateTime", eTypeDateTime));
		mapStr2Val.insert(make_pair("eTypeDate", eTypeDate));
		mapStr2Val.insert(make_pair("eTypeTime", eTypeTime));
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

const char* EnumValToStr(EQueryType e)
{
	switch(e)
	{
	case eQueryNormal:
		return "eQueryNormal";
	case eQuerySave0:
		return "eQuerySave0";
	case eQuerySave1:
		return "eQuerySave1";
	case eQuerySave2:
		return "eQuerySave2";
	case eQuerySave3:
		return "eQuerySave3";
	case eQuerySaveMax:
		return "eQuerySaveMax";
	case eQueryMail:
		return "eQueryMail";
	case eQueryArena:
		return "eQueryArena";
	case eQueryGuild:
		return "eQueryGuild";
	case eQueryRank:
		return "eQueryRank";
	case eQueryRecharge:
		return "eQueryRecharge";
	case eQueryEnd:
		return "eQueryEnd";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EQueryType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EQueryType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eQueryNormal", eQueryNormal));
		mapStr2Val.insert(make_pair("eQuerySave0", eQuerySave0));
		mapStr2Val.insert(make_pair("eQuerySave1", eQuerySave1));
		mapStr2Val.insert(make_pair("eQuerySave2", eQuerySave2));
		mapStr2Val.insert(make_pair("eQuerySave3", eQuerySave3));
		mapStr2Val.insert(make_pair("eQuerySaveMax", eQuerySaveMax));
		mapStr2Val.insert(make_pair("eQueryMail", eQueryMail));
		mapStr2Val.insert(make_pair("eQueryArena", eQueryArena));
		mapStr2Val.insert(make_pair("eQueryGuild", eQueryGuild));
		mapStr2Val.insert(make_pair("eQueryRank", eQueryRank));
		mapStr2Val.insert(make_pair("eQueryRecharge", eQueryRecharge));
		mapStr2Val.insert(make_pair("eQueryEnd", eQueryEnd));
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

SParam::SParam() : eType((EParamType)0) { }

SParam::SParam(EParamType eType_, const std::string& strVal_) : eType(eType_), strVal(strVal_) { }

SParam::SParam(SParam&& src) : eType(src.eType), strVal(move(src.strVal)) { }

SParam& SParam::operator=(SParam&& rhs)
{
	if(this != &rhs)
	{
		this->~SParam();
		new (this) SParam(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SParam& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (UINT8&)s.eType;
	src >> s.strVal;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SParam& s)
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
	src << s.strVal;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SParam& s)
{
	if(strcmp(rElement.Value(), "SParam") != 0)
	{
		LOG_CRI << "rElement is not SParam!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "EParamType") != 0)
	{
		LOG_CRI << "pElemChild is not EParamType!";
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
		LOG_CRI << "pElemChild for strVal is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strVal") != 0)
	{
		LOG_CRI << "Attribute: name is not strVal!";
		return false;
	}
	const char* pszVal_strVal = pElemChild->Attribute("value");
	if(pszVal_strVal == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strVal = pszVal_strVal;
	return true;
}

bool ToXML(const SParam& s, TiXmlElement& rElement)
{
	rElement.SetValue("SParam");
	rElement.SetAttribute("type", ToUTF8Ptr("查询的参数"));
	unique_ptr<TiXmlElement> pElem_eType(new TiXmlElement("EParamType"));
	if(pElem_eType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eType->SetAttribute("name", "eType");
	const char* pszEnum_eType = EnumValToStr(s.eType);
	if(pszEnum_eType == NULL)
	{
		LOG_CRI << "EnumValToStr for EParamType fails!";
		return false;
	}
	pElem_eType->SetAttribute("value", pszEnum_eType);
	pElem_eType->SetAttribute("comment", ToUTF8Ptr("类型"));
	if(rElement.LinkEndChild(pElem_eType.get()) != NULL)
		pElem_eType.release();
	unique_ptr<TiXmlElement> pElem_strVal(new TiXmlElement("string"));
	if(pElem_strVal == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strVal->SetAttribute("name", "strVal");
	pElem_strVal->SetAttribute("value", s.strVal.c_str());
	pElem_strVal->SetAttribute("comment", ToUTF8Ptr("序列化后的值"));
	if(rElement.LinkEndChild(pElem_strVal.get()) != NULL)
		pElem_strVal.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecParam& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SParam s;
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

bool VectorToXML(const TVecParam& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SParam"));
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

SQuery::SQuery() : bHasResult(false) { }

SQuery::SQuery(const std::string& strQuery_, const TVecParam& vecParam_, bool bHasResult_) : strQuery(strQuery_), vecParam(vecParam_), bHasResult(bHasResult_) { }

SQuery::SQuery(SQuery&& src) : strQuery(move(src.strQuery)), vecParam(move(src.vecParam)), bHasResult(src.bHasResult) { }

SQuery& SQuery::operator=(SQuery&& rhs)
{
	if(this != &rhs)
	{
		this->~SQuery();
		new (this) SQuery(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SQuery& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.strQuery;
	src >> s.vecParam;
	src >> s.bHasResult;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SQuery& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.strQuery;
	src << s.vecParam;
	src << s.bHasResult;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SQuery& s)
{
	if(strcmp(rElement.Value(), "SQuery") != 0)
	{
		LOG_CRI << "rElement is not SQuery!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strQuery is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strQuery") != 0)
	{
		LOG_CRI << "Attribute: name is not strQuery!";
		return false;
	}
	const char* pszVal_strQuery = pElemChild->Attribute("value");
	if(pszVal_strQuery == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strQuery = pszVal_strQuery;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecParam is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecParam") != 0)
	{
		LOG_CRI << "pElemChild is not TVecParam!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecParam") != 0)
	{
		LOG_CRI << "Attribute: name is not vecParam!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecParam))
	{
		LOG_CRI << "VectorFromXML for vecParam fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for bHasResult is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "bool") != 0)
	{
		LOG_CRI << "pElemChild is not bool!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "bHasResult") != 0)
	{
		LOG_CRI << "Attribute: name is not bHasResult!";
		return false;
	}
	const char* pszVal_bHasResult = pElemChild->Attribute("value");
	if(pszVal_bHasResult == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_bHasResult, s.bHasResult))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SQuery& s, TiXmlElement& rElement)
{
	rElement.SetValue("SQuery");
	rElement.SetAttribute("type", ToUTF8Ptr("查询"));
	unique_ptr<TiXmlElement> pElem_strQuery(new TiXmlElement("string"));
	if(pElem_strQuery == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strQuery->SetAttribute("name", "strQuery");
	pElem_strQuery->SetAttribute("value", s.strQuery.c_str());
	pElem_strQuery->SetAttribute("comment", ToUTF8Ptr("查询字符串"));
	if(rElement.LinkEndChild(pElem_strQuery.get()) != NULL)
		pElem_strQuery.release();
	unique_ptr<TiXmlElement> pElem_vecParam(new TiXmlElement("TVecParam"));
	if(pElem_vecParam == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecParam->SetAttribute("name", "vecParam");
	if(!VectorToXML(s.vecParam, *pElem_vecParam))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecParam->SetAttribute("comment", ToUTF8Ptr("参数列表"));
	if(rElement.LinkEndChild(pElem_vecParam.get()) != NULL)
		pElem_vecParam.release();
	unique_ptr<TiXmlElement> pElem_bHasResult(new TiXmlElement("bool"));
	if(pElem_bHasResult == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_bHasResult->SetAttribute("name", "bHasResult");
	pElem_bHasResult->SetAttribute("value", NumberToString(s.bHasResult).c_str());
	pElem_bHasResult->SetAttribute("comment", ToUTF8Ptr("是否有结果集"));
	if(rElement.LinkEndChild(pElem_bHasResult.get()) != NULL)
		pElem_bHasResult.release();
	return true;
}

#endif

SRes::SRes() { }

SRes::SRes(const std::string& strVal_) : strVal(strVal_) { }

SRes::SRes(SRes&& src) : strVal(move(src.strVal)) { }

SRes& SRes::operator=(SRes&& rhs)
{
	if(this != &rhs)
	{
		this->~SRes();
		new (this) SRes(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SRes& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.strVal;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SRes& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.strVal;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SRes& s)
{
	if(strcmp(rElement.Value(), "SRes") != 0)
	{
		LOG_CRI << "rElement is not SRes!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strVal is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strVal") != 0)
	{
		LOG_CRI << "Attribute: name is not strVal!";
		return false;
	}
	const char* pszVal_strVal = pElemChild->Attribute("value");
	if(pszVal_strVal == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strVal = pszVal_strVal;
	return true;
}

bool ToXML(const SRes& s, TiXmlElement& rElement)
{
	rElement.SetValue("SRes");
	rElement.SetAttribute("type", ToUTF8Ptr("查询的一个属性的结果"));
	unique_ptr<TiXmlElement> pElem_strVal(new TiXmlElement("string"));
	if(pElem_strVal == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strVal->SetAttribute("name", "strVal");
	pElem_strVal->SetAttribute("value", s.strVal.c_str());
	pElem_strVal->SetAttribute("comment", ToUTF8Ptr("序列化后的值"));
	if(rElement.LinkEndChild(pElem_strVal.get()) != NULL)
		pElem_strVal.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecRes& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SRes s;
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

bool VectorToXML(const TVecRes& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SRes"));
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

SRow::SRow() { }

SRow::SRow(const TVecRes& vecRes_) : vecRes(vecRes_) { }

SRow::SRow(SRow&& src) : vecRes(move(src.vecRes)) { }

SRow& SRow::operator=(SRow&& rhs)
{
	if(this != &rhs)
	{
		this->~SRow();
		new (this) SRow(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SRow& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.vecRes;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SRow& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.vecRes;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

SRes& SRow::operator[](size_t index)
{
	return const_cast<SRes&>(static_cast<const SRow&>(*this)[index]);
}

const SRes& SRow::operator[](size_t index) const
{
	if(index >= vecRes.size())
	{
		static SRes s;
		return s;
	}
	return vecRes[index];
}

bool SRow::Empty() const { return vecRes.empty(); }

size_t SRow::Size() const { return vecRes.size(); }

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SRow& s)
{
	if(strcmp(rElement.Value(), "SRow") != 0)
	{
		LOG_CRI << "rElement is not SRow!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecRes is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecRes") != 0)
	{
		LOG_CRI << "pElemChild is not TVecRes!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecRes") != 0)
	{
		LOG_CRI << "Attribute: name is not vecRes!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecRes))
	{
		LOG_CRI << "VectorFromXML for vecRes fails!";
		return false;
	}
	return true;
}

bool ToXML(const SRow& s, TiXmlElement& rElement)
{
	rElement.SetValue("SRow");
	rElement.SetAttribute("type", ToUTF8Ptr("查询的一行结果集"));
	unique_ptr<TiXmlElement> pElem_vecRes(new TiXmlElement("TVecRes"));
	if(pElem_vecRes == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecRes->SetAttribute("name", "vecRes");
	if(!VectorToXML(s.vecRes, *pElem_vecRes))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecRes->SetAttribute("comment", ToUTF8Ptr("属性结果的列表"));
	if(rElement.LinkEndChild(pElem_vecRes.get()) != NULL)
		pElem_vecRes.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecRow& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SRow s;
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

bool VectorToXML(const TVecRow& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SRow"));
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

STable::STable() : byIndex(0), bMore(false) { }

STable::STable(UINT8 byIndex_, bool bMore_, const TVecRow& vecRow_) : byIndex(byIndex_), bMore(bMore_), vecRow(vecRow_) { }

STable::STable(STable&& src) : byIndex(src.byIndex), bMore(src.bMore), vecRow(move(src.vecRow)) { }

STable& STable::operator=(STable&& rhs)
{
	if(this != &rhs)
	{
		this->~STable();
		new (this) STable(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, STable& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.byIndex;
	src >> s.bMore;
	src >> s.vecRow;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const STable& s)
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
	src << s.bMore;
	src << s.vecRow;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

SRow& STable::operator[](size_t index)
{
	return const_cast<SRow&>(static_cast<const STable&>(*this)[index]);
}

const SRow& STable::operator[](size_t index) const
{
	if(index >= vecRow.size())
	{
		static SRow s;
		return s;
	}
	return vecRow[index];
}

bool STable::Empty() const { return vecRow.empty(); }

size_t STable::Size() const { return vecRow.size(); }

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, STable& s)
{
	if(strcmp(rElement.Value(), "STable") != 0)
	{
		LOG_CRI << "rElement is not STable!";
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
		LOG_CRI << "pElemChild for bMore is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "bool") != 0)
	{
		LOG_CRI << "pElemChild is not bool!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "bMore") != 0)
	{
		LOG_CRI << "Attribute: name is not bMore!";
		return false;
	}
	const char* pszVal_bMore = pElemChild->Attribute("value");
	if(pszVal_bMore == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_bMore, s.bMore))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecRow is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecRow") != 0)
	{
		LOG_CRI << "pElemChild is not TVecRow!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecRow") != 0)
	{
		LOG_CRI << "Attribute: name is not vecRow!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecRow))
	{
		LOG_CRI << "VectorFromXML for vecRow fails!";
		return false;
	}
	return true;
}

bool ToXML(const STable& s, TiXmlElement& rElement)
{
	rElement.SetValue("STable");
	rElement.SetAttribute("type", ToUTF8Ptr("查询的多行结果组成的一张表"));
	unique_ptr<TiXmlElement> pElem_byIndex(new TiXmlElement("UINT8"));
	if(pElem_byIndex == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byIndex->SetAttribute("name", "byIndex");
	pElem_byIndex->SetAttribute("value", NumberToString(s.byIndex).c_str());
	pElem_byIndex->SetAttribute("comment", ToUTF8Ptr("结果表对应查询中SQL语句的索引(从0开始)"));
	if(rElement.LinkEndChild(pElem_byIndex.get()) != NULL)
		pElem_byIndex.release();
	unique_ptr<TiXmlElement> pElem_bMore(new TiXmlElement("bool"));
	if(pElem_bMore == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_bMore->SetAttribute("name", "bMore");
	pElem_bMore->SetAttribute("value", NumberToString(s.bMore).c_str());
	pElem_bMore->SetAttribute("comment", ToUTF8Ptr("是否有更多的结果"));
	if(rElement.LinkEndChild(pElem_bMore.get()) != NULL)
		pElem_bMore.release();
	unique_ptr<TiXmlElement> pElem_vecRow(new TiXmlElement("TVecRow"));
	if(pElem_vecRow == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecRow->SetAttribute("name", "vecRow");
	if(!VectorToXML(s.vecRow, *pElem_vecRow))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecRow->SetAttribute("comment", ToUTF8Ptr("所有行结果的列表"));
	if(rElement.LinkEndChild(pElem_vecRow.get()) != NULL)
		pElem_vecRow.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecTable& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		STable s;
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

bool VectorToXML(const TVecTable& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("STable"));
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

} //namespace NDBProt
