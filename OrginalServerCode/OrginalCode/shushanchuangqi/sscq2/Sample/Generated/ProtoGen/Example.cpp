/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    Example.cpp
//  Purpose:      通信协议示例
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "Example.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NExample
{

#ifdef PROT_USE_XML

const char* EnumValToStr(EExTest e)
{
	switch(e)
	{
	case eExTest1:
		return "eExTest1";
	case eExTest2:
		return "eExTest2";
	case eExTest3:
		return "eExTest3";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EExTest& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EExTest> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eExTest1", eExTest1));
		mapStr2Val.insert(make_pair("eExTest2", eExTest2));
		mapStr2Val.insert(make_pair("eExTest3", eExTest3));
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

const char* GetDescription(EExTest e)
{
	switch(e)
	{
	case eExTest1:
		return "枚举值1";
	case eExTest2:
		return "枚举值2";
	case eExTest3:
		return "枚举值3";
	default:
		return "未知错误";
	}
}

STest::STest() { }

STest::STest(STest&& src) : vecBase(move(src.vecBase))
{
	pBase.swap(src.pBase);
}

STest& STest::operator=(STest&& rhs)
{
	if(this != &rhs)
	{
		this->~STest();
		new (this) STest(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, STest& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	SExBase_Wrapper pBase_Wrapper;
	src >> pBase_Wrapper;
	src >> s.vecBase;
	s.pBase = pBase_Wrapper.ptr;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const STest& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	SExBase_Wrapper pBase_Wrapper(s.pBase);
	src << pBase_Wrapper;
	src << s.vecBase;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, STest& s)
{
	if(strcmp(rElement.Value(), "STest") != 0)
	{
		LOG_CRI << "rElement is not STest!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for pBase is empty!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "pBase") != 0)
	{
		LOG_CRI << "Attribute: name is not pBase!";
		return false;
	}
	if(!SuperFromXML(*pElemChild, s.pBase))
	{
		LOG_CRI << "FromXML for: pBase fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecBase is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecExBase") != 0)
	{
		LOG_CRI << "pElemChild is not TVecExBase!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecBase") != 0)
	{
		LOG_CRI << "Attribute: name is not vecBase!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecBase))
	{
		LOG_CRI << "VectorFromXML for vecBase fails!";
		return false;
	}
	return true;
}

bool ToXML(const STest& s, TiXmlElement& rElement)
{
	rElement.SetValue("STest");
	rElement.SetAttribute("type", ToUTF8Ptr("前置声明测试"));
	unique_ptr<TiXmlElement> pElem_pBase(new TiXmlElement("SExBase"));
	if(pElem_pBase == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_pBase->SetAttribute("name", "pBase");
	if(s.pBase == NULL)
	{
		LOG_CRI << "pBase is NULL!";
		return false;
	}
	if(!SuperToXML(*s.pBase, *pElem_pBase))
	{
		LOG_CRI << "pBase SuperToXML fails!";
		return false;
	}
	pElem_pBase->SetAttribute("comment", ToUTF8Ptr("父类指针"));
	if(rElement.LinkEndChild(pElem_pBase.get()) != NULL)
		pElem_pBase.release();
	unique_ptr<TiXmlElement> pElem_vecBase(new TiXmlElement("TVecExBase"));
	if(pElem_vecBase == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecBase->SetAttribute("name", "vecBase");
	if(!VectorToXML(s.vecBase, *pElem_vecBase))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecBase->SetAttribute("comment", ToUTF8Ptr("父类指针列表"));
	if(rElement.LinkEndChild(pElem_vecBase.get()) != NULL)
		pElem_vecBase.release();
	return true;
}

#endif

SServer::SServer() : dwValue(0) { }

SServer::SServer(UINT32 dwValue_) : dwValue(dwValue_) { }

CInArchive& operator>>(CInArchive& src, SServer& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.dwValue;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SServer& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.dwValue;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SServer& s)
{
	if(strcmp(rElement.Value(), "SServer") != 0)
	{
		LOG_CRI << "rElement is not SServer!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwValue is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwValue") != 0)
	{
		LOG_CRI << "Attribute: name is not dwValue!";
		return false;
	}
	const char* pszVal_dwValue = pElemChild->Attribute("value");
	if(pszVal_dwValue == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwValue, s.dwValue))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SServer& s, TiXmlElement& rElement)
{
	rElement.SetValue("SServer");
	rElement.SetAttribute("type", ToUTF8Ptr("只在服务器生成"));
	unique_ptr<TiXmlElement> pElem_dwValue(new TiXmlElement("UINT32"));
	if(pElem_dwValue == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwValue->SetAttribute("name", "dwValue");
	pElem_dwValue->SetAttribute("value", NumberToString(s.dwValue).c_str());
	pElem_dwValue->SetAttribute("comment", ToUTF8Ptr("成员"));
	if(rElement.LinkEndChild(pElem_dwValue.get()) != NULL)
		pElem_dwValue.release();
	return true;
}

#endif

SPointer::SPointer() : dwValue(0) { }

SPointer::SPointer(UINT32 dwValue_) : dwValue(dwValue_) { }

CInArchive& operator>>(CInArchive& src, SPointer& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.dwValue;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SPointer& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.dwValue;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SPointer& s)
{
	if(strcmp(rElement.Value(), "SPointer") != 0)
	{
		LOG_CRI << "rElement is not SPointer!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwValue is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwValue") != 0)
	{
		LOG_CRI << "Attribute: name is not dwValue!";
		return false;
	}
	const char* pszVal_dwValue = pElemChild->Attribute("value");
	if(pszVal_dwValue == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwValue, s.dwValue))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SPointer& s, TiXmlElement& rElement)
{
	rElement.SetValue("SPointer");
	rElement.SetAttribute("type", ToUTF8Ptr("按智能指针传递的结构体"));
	unique_ptr<TiXmlElement> pElem_dwValue(new TiXmlElement("UINT32"));
	if(pElem_dwValue == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwValue->SetAttribute("name", "dwValue");
	pElem_dwValue->SetAttribute("value", NumberToString(s.dwValue).c_str());
	pElem_dwValue->SetAttribute("comment", ToUTF8Ptr("成员"));
	if(rElement.LinkEndChild(pElem_dwValue.get()) != NULL)
		pElem_dwValue.release();
	return true;
}

#endif

SExBase::SExBase() : member1(1) { }

CInArchive& operator>>(CInArchive& src, SExBase& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.member1;
	src >> s.vecMember2;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SExBase& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.member1;
	src << s.vecMember2;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, SExBase_Wrapper& rWrapper)
{
	EType_SExBase eType = eType_SExBase;
	src >> (UINT8&)eType;
	switch(eType)
	{
	case eType_SExBase:
		{
			rWrapper.ptr.reset(new SExBase);
			src >> (SExBase&)*rWrapper.ptr;
		}
		break;
	case eType_SExDerived1:
		{
			rWrapper.ptr.reset(new SExDerived1);
			src >> (SExDerived1&)*rWrapper.ptr;
		}
		break;
	case eType_SExDerived2:
		{
			rWrapper.ptr.reset(new SExDerived2);
			src >> (SExDerived2&)*rWrapper.ptr;
		}
		break;
	case eType_SExDescend3:
		{
			rWrapper.ptr.reset(new SExDescend3);
			src >> (SExDescend3&)*rWrapper.ptr;
		}
		break;
	case eType_SExDescend4:
		{
			rWrapper.ptr.reset(new SExDescend4);
			src >> (SExDescend4&)*rWrapper.ptr;
		}
		break;
	default:
		throw "Unknown value for EType_SExBase";
		break;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SExBase_Wrapper& rWrapper)
{
	if(rWrapper.ptr != NULL)
	{
		src << (UINT8)rWrapper.ptr->GetClassType();
		switch(rWrapper.ptr->GetClassType())
		{
		case eType_SExBase:
			src << (SExBase&)*rWrapper.ptr;
			break;
		case eType_SExDerived1:
			src << (SExDerived1&)*rWrapper.ptr;
			break;
		case eType_SExDerived2:
			src << (SExDerived2&)*rWrapper.ptr;
			break;
		case eType_SExDescend3:
			src << (SExDescend3&)*rWrapper.ptr;
			break;
		case eType_SExDescend4:
			src << (SExDescend4&)*rWrapper.ptr;
			break;
		default:
			throw "Unknown value for EType_SExBase";
			break;
		}
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecExBase& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SExBase_Wrapper wrapper;
		src >> wrapper;
		vec[i] = wrapper.ptr;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecExBase& vec)
{
	if(vec.size() > 0x7FFF)
		throw "Vector Size Too Large!";
	UINT16 wSize = (UINT16)vec.size();
	src.WriteContainerSize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SExBase_Wrapper wrapper;
		wrapper.ptr = vec[i];
		src << wrapper;
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SExBase& s)
{
	if(strcmp(rElement.Value(), "SExBase") != 0)
	{
		LOG_CRI << "rElement is not SExBase!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for member1 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "member1") != 0)
	{
		LOG_CRI << "Attribute: name is not member1!";
		return false;
	}
	const char* pszVal_member1 = pElemChild->Attribute("value");
	if(pszVal_member1 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_member1, s.member1))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecMember2 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecString") != 0)
	{
		LOG_CRI << "pElemChild is not TVecString!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecMember2") != 0)
	{
		LOG_CRI << "Attribute: name is not vecMember2!";
		return false;
	}
	const char* pszText_vecMember2 = pElemChild->GetText();
	if(pszText_vecMember2 != NULL)
		SplitToText(pszText_vecMember2, ",", s.vecMember2);
	return true;
}

bool ToXML(const SExBase& s, TiXmlElement& rElement)
{
	rElement.SetValue("SExBase");
	rElement.SetAttribute("type", ToUTF8Ptr("结构体父类型示例"));
	unique_ptr<TiXmlElement> pElem_member1(new TiXmlElement("UINT32"));
	if(pElem_member1 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_member1->SetAttribute("name", "member1");
	pElem_member1->SetAttribute("value", NumberToString(s.member1).c_str());
	pElem_member1->SetAttribute("comment", ToUTF8Ptr("成员1"));
	if(rElement.LinkEndChild(pElem_member1.get()) != NULL)
		pElem_member1.release();
	unique_ptr<TiXmlElement> pElem_vecMember2(new TiXmlElement("TVecString"));
	if(pElem_vecMember2 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecMember2->SetAttribute("name", "vecMember2");
	string strText_vecMember2;
	for(size_t i = 0; i < s.vecMember2.size(); ++i)
	{
		if(i > 0)
			strText_vecMember2 += ", ";
		strText_vecMember2 += s.vecMember2[i];
	}
	unique_ptr<TiXmlText> pText_vecMember2(new TiXmlText(strText_vecMember2.c_str()));
	if(pText_vecMember2 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(pElem_vecMember2->LinkEndChild(pText_vecMember2.get()) != NULL)
		pText_vecMember2.release();
	pElem_vecMember2->SetAttribute("comment", ToUTF8Ptr("成员2"));
	if(rElement.LinkEndChild(pElem_vecMember2.get()) != NULL)
		pElem_vecMember2.release();
	return true;
}

bool SuperFromXML(TiXmlElement& rElement, SExBasePtr& p)
{
	const char* pszName = rElement.Value();
	if(pszName == NULL)
	{
		LOG_CRI << "Element Name is empty!";
		return false;
	}
	if(strcmp(pszName, "SExBase") == 0)
	{
		SExBasePtr pStruct(new SExBase);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SExBase";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SExBase FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SExDerived1") == 0)
	{
		SExDerived1Ptr pStruct(new SExDerived1);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SExDerived1";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SExDerived1 FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SExDerived2") == 0)
	{
		SExDerived2Ptr pStruct(new SExDerived2);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SExDerived2";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SExDerived2 FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SExDescend3") == 0)
	{
		SExDescend3Ptr pStruct(new SExDescend3);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SExDescend3";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SExDescend3 FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SExDescend4") == 0)
	{
		SExDescend4Ptr pStruct(new SExDescend4);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SExDescend4";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SExDescend4 FromXML fails!";
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

bool SuperToXML(const SExBase& s, TiXmlElement& rElement)
{
	switch(s.GetClassType())
	{
	case eType_SExBase:
		return ToXML((SExBase&)s, rElement);
	case eType_SExDerived1:
		return ToXML((SExDerived1&)s, rElement);
	case eType_SExDerived2:
		return ToXML((SExDerived2&)s, rElement);
	case eType_SExDescend3:
		return ToXML((SExDescend3&)s, rElement);
	case eType_SExDescend4:
		return ToXML((SExDescend4&)s, rElement);
	default:
		LOG_CRI << "Invalid type: " << s.GetClassType();
		return false;
	}
}

bool VectorFromXML(TiXmlElement& rElement, TVecExBase& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SExBasePtr p;
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

bool VectorToXML(const TVecExBase& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SExBase"));
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

SExDerived1::SExDerived1() : byMember3(0), qwMember4(0) { }

CInArchive& operator>>(CInArchive& src, SExDerived1& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (SExBase&)s;
	src >> s.byMember3;
	src >> s.qwMember4;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SExDerived1& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const SExBase&)s;
	src << s.byMember3;
	src << s.qwMember4;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, SExDerived1_Wrapper& rWrapper)
{
	EType_SExBase eType = eType_SExBase;
	src >> (UINT8&)eType;
	switch(eType)
	{
	case eType_SExDerived1:
		{
			rWrapper.ptr.reset(new SExDerived1);
			src >> (SExDerived1&)*rWrapper.ptr;
		}
		break;
	case eType_SExDescend3:
		{
			rWrapper.ptr.reset(new SExDescend3);
			src >> (SExDescend3&)*rWrapper.ptr;
		}
		break;
	case eType_SExDescend4:
		{
			rWrapper.ptr.reset(new SExDescend4);
			src >> (SExDescend4&)*rWrapper.ptr;
		}
		break;
	default:
		throw "Unknown value for EType_SExBase";
		break;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SExDerived1_Wrapper& rWrapper)
{
	if(rWrapper.ptr != NULL)
	{
		src << (UINT8)rWrapper.ptr->GetClassType();
		switch(rWrapper.ptr->GetClassType())
		{
		case eType_SExDerived1:
			src << (SExDerived1&)*rWrapper.ptr;
			break;
		case eType_SExDescend3:
			src << (SExDescend3&)*rWrapper.ptr;
			break;
		case eType_SExDescend4:
			src << (SExDescend4&)*rWrapper.ptr;
			break;
		default:
			throw "Unknown value for EType_SExBase";
			break;
		}
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecExDerived1& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SExDerived1_Wrapper wrapper;
		src >> wrapper;
		vec[i] = wrapper.ptr;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecExDerived1& vec)
{
	if(vec.size() > 0x7FFF)
		throw "Vector Size Too Large!";
	UINT16 wSize = (UINT16)vec.size();
	src.WriteContainerSize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SExDerived1_Wrapper wrapper;
		wrapper.ptr = vec[i];
		src << wrapper;
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SExDerived1& s)
{
	if(strcmp(rElement.Value(), "SExDerived1") != 0)
	{
		LOG_CRI << "rElement is not SExDerived1!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for SExBase is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (SExBase&)s))
	{
		LOG_CRI << "FromXML for: SExBase fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byMember3 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byMember3") != 0)
	{
		LOG_CRI << "Attribute: name is not byMember3!";
		return false;
	}
	const char* pszVal_byMember3 = pElemChild->Attribute("value");
	if(pszVal_byMember3 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byMember3, s.byMember3))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwMember4 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "INT64") != 0)
	{
		LOG_CRI << "pElemChild is not INT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwMember4") != 0)
	{
		LOG_CRI << "Attribute: name is not qwMember4!";
		return false;
	}
	const char* pszVal_qwMember4 = pElemChild->Attribute("value");
	if(pszVal_qwMember4 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwMember4, s.qwMember4))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SExDerived1& s, TiXmlElement& rElement)
{
	rElement.SetValue("SExDerived1");
	rElement.SetAttribute("type", ToUTF8Ptr("结构体子类型1示例"));
	unique_ptr<TiXmlElement> pElem_SExBase(new TiXmlElement("SExBase"));
	if(pElem_SExBase == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const SExBase&)s, *pElem_SExBase))
	{
		LOG_CRI << "SExBase ToXML fails!";
		return false;
	}
	pElem_SExBase->SetAttribute("type", ToUTF8Ptr("结构体父类型示例"));
	pElem_SExBase->SetAttribute("comment", ToUTF8Ptr("父类SExBase部分"));
	if(rElement.LinkEndChild(pElem_SExBase.get()) != NULL)
		pElem_SExBase.release();
	unique_ptr<TiXmlElement> pElem_byMember3(new TiXmlElement("UINT16"));
	if(pElem_byMember3 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byMember3->SetAttribute("name", "byMember3");
	pElem_byMember3->SetAttribute("value", NumberToString(s.byMember3).c_str());
	pElem_byMember3->SetAttribute("comment", ToUTF8Ptr("成员3"));
	if(rElement.LinkEndChild(pElem_byMember3.get()) != NULL)
		pElem_byMember3.release();
	unique_ptr<TiXmlElement> pElem_qwMember4(new TiXmlElement("INT64"));
	if(pElem_qwMember4 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwMember4->SetAttribute("name", "qwMember4");
	pElem_qwMember4->SetAttribute("value", NumberToString(s.qwMember4).c_str());
	pElem_qwMember4->SetAttribute("comment", ToUTF8Ptr("成员4"));
	if(rElement.LinkEndChild(pElem_qwMember4.get()) != NULL)
		pElem_qwMember4.release();
	return true;
}

bool SuperFromXML(TiXmlElement& rElement, SExDerived1Ptr& p)
{
	const char* pszName = rElement.Value();
	if(pszName == NULL)
	{
		LOG_CRI << "Element Name is empty!";
		return false;
	}
	if(strcmp(pszName, "SExDerived1") == 0)
	{
		SExDerived1Ptr pStruct(new SExDerived1);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SExDerived1";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SExDerived1 FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SExDescend3") == 0)
	{
		SExDescend3Ptr pStruct(new SExDescend3);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SExDescend3";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SExDescend3 FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SExDescend4") == 0)
	{
		SExDescend4Ptr pStruct(new SExDescend4);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SExDescend4";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SExDescend4 FromXML fails!";
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

bool SuperToXML(const SExDerived1& s, TiXmlElement& rElement)
{
	switch(s.GetClassType())
	{
	case eType_SExDerived1:
		return ToXML((SExDerived1&)s, rElement);
	case eType_SExDescend3:
		return ToXML((SExDescend3&)s, rElement);
	case eType_SExDescend4:
		return ToXML((SExDescend4&)s, rElement);
	default:
		LOG_CRI << "Invalid type: " << s.GetClassType();
		return false;
	}
}

bool VectorFromXML(TiXmlElement& rElement, TVecExDerived1& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SExDerived1Ptr p;
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

bool VectorToXML(const TVecExDerived1& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SExDerived1"));
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

SExDescend3::SExDescend3() { }

SExDescend3::SExDescend3(SExDescend3&& src) : SExDerived1(src), vecExDerive(move(src.vecExDerive)), vecExBase(move(src.vecExBase))
{
	base.swap(src.base);
	s.swap(src.s);
}

SExDescend3& SExDescend3::operator=(SExDescend3&& rhs)
{
	if(this != &rhs)
	{
		this->~SExDescend3();
		new (this) SExDescend3(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SExDescend3& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (SExDerived1&)s;
	SExBase_Wrapper base_Wrapper;
	SExDerived1_Wrapper s_Wrapper;
	src >> base_Wrapper;
	src >> s_Wrapper;
	src >> s.vecExDerive;
	src >> s.vecExBase;
	s.base = base_Wrapper.ptr;
	s.s = s_Wrapper.ptr;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SExDescend3& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const SExDerived1&)s;
	SExBase_Wrapper base_Wrapper(s.base);
	SExDerived1_Wrapper s_Wrapper(s.s);
	src << base_Wrapper;
	src << s_Wrapper;
	src << s.vecExDerive;
	src << s.vecExBase;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecExDescend3& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SExDescend3Ptr p(new SExDescend3);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecExDescend3& vec)
{
	if(vec.size() > 0x7FFF)
		throw "Vector Size Too Large!";
	UINT16 wSize = (UINT16)vec.size();
	src.WriteContainerSize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
		src << *vec[i];
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SExDescend3& s)
{
	if(strcmp(rElement.Value(), "SExDescend3") != 0)
	{
		LOG_CRI << "rElement is not SExDescend3!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for SExDerived1 is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (SExDerived1&)s))
	{
		LOG_CRI << "FromXML for: SExDerived1 fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for base is empty!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "base") != 0)
	{
		LOG_CRI << "Attribute: name is not base!";
		return false;
	}
	if(!SuperFromXML(*pElemChild, s.base))
	{
		LOG_CRI << "FromXML for: base fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for s is empty!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "s") != 0)
	{
		LOG_CRI << "Attribute: name is not s!";
		return false;
	}
	if(!SuperFromXML(*pElemChild, s.s))
	{
		LOG_CRI << "FromXML for: s fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecExDerive is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecExDerived1") != 0)
	{
		LOG_CRI << "pElemChild is not TVecExDerived1!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecExDerive") != 0)
	{
		LOG_CRI << "Attribute: name is not vecExDerive!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecExDerive))
	{
		LOG_CRI << "VectorFromXML for vecExDerive fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecExBase is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecExBase") != 0)
	{
		LOG_CRI << "pElemChild is not TVecExBase!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecExBase") != 0)
	{
		LOG_CRI << "Attribute: name is not vecExBase!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecExBase))
	{
		LOG_CRI << "VectorFromXML for vecExBase fails!";
		return false;
	}
	return true;
}

bool ToXML(const SExDescend3& s, TiXmlElement& rElement)
{
	rElement.SetValue("SExDescend3");
	rElement.SetAttribute("type", ToUTF8Ptr("结构体子类型3示例"));
	unique_ptr<TiXmlElement> pElem_SExDerived1(new TiXmlElement("SExDerived1"));
	if(pElem_SExDerived1 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const SExDerived1&)s, *pElem_SExDerived1))
	{
		LOG_CRI << "SExDerived1 ToXML fails!";
		return false;
	}
	pElem_SExDerived1->SetAttribute("type", ToUTF8Ptr("结构体子类型1示例"));
	pElem_SExDerived1->SetAttribute("comment", ToUTF8Ptr("父类SExDerived1部分"));
	if(rElement.LinkEndChild(pElem_SExDerived1.get()) != NULL)
		pElem_SExDerived1.release();
	unique_ptr<TiXmlElement> pElem_base(new TiXmlElement("SExBase"));
	if(pElem_base == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_base->SetAttribute("name", "base");
	if(s.base == NULL)
	{
		LOG_CRI << "base is NULL!";
		return false;
	}
	if(!SuperToXML(*s.base, *pElem_base))
	{
		LOG_CRI << "base SuperToXML fails!";
		return false;
	}
	pElem_base->SetAttribute("comment", ToUTF8Ptr("成员5"));
	if(rElement.LinkEndChild(pElem_base.get()) != NULL)
		pElem_base.release();
	unique_ptr<TiXmlElement> pElem_s(new TiXmlElement("SExDerived1"));
	if(pElem_s == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_s->SetAttribute("name", "s");
	if(s.s == NULL)
	{
		LOG_CRI << "s is NULL!";
		return false;
	}
	if(!SuperToXML(*s.s, *pElem_s))
	{
		LOG_CRI << "s SuperToXML fails!";
		return false;
	}
	pElem_s->SetAttribute("comment", ToUTF8Ptr("成员6"));
	if(rElement.LinkEndChild(pElem_s.get()) != NULL)
		pElem_s.release();
	unique_ptr<TiXmlElement> pElem_vecExDerive(new TiXmlElement("TVecExDerived1"));
	if(pElem_vecExDerive == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecExDerive->SetAttribute("name", "vecExDerive");
	if(!VectorToXML(s.vecExDerive, *pElem_vecExDerive))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecExDerive->SetAttribute("comment", ToUTF8Ptr("成员7"));
	if(rElement.LinkEndChild(pElem_vecExDerive.get()) != NULL)
		pElem_vecExDerive.release();
	unique_ptr<TiXmlElement> pElem_vecExBase(new TiXmlElement("TVecExBase"));
	if(pElem_vecExBase == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecExBase->SetAttribute("name", "vecExBase");
	if(!VectorToXML(s.vecExBase, *pElem_vecExBase))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecExBase->SetAttribute("comment", ToUTF8Ptr("成员8"));
	if(rElement.LinkEndChild(pElem_vecExBase.get()) != NULL)
		pElem_vecExBase.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecExDescend3& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SExDescend3Ptr p(new SExDescend3);
		if(!FromXML(*pElemMember, *p))
		{
			LOG_CRI << "FromXML fails!";
			return false;
		}
		vec.push_back(p);
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecExDescend3& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SExDescend3"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!ToXML(*vec[i], *pElemMember))
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

SExDescend4::SExDescend4() : wMember5(0), qwMember6(0) { }

SExDescend4::SExDescend4(SExDescend4&& src) : SExDerived1(src), wMember5(src.wMember5), qwMember6(src.qwMember6), vecExDesc(move(src.vecExDesc)) { }

SExDescend4& SExDescend4::operator=(SExDescend4&& rhs)
{
	if(this != &rhs)
	{
		this->~SExDescend4();
		new (this) SExDescend4(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SExDescend4& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (SExDerived1&)s;
	src >> s.wMember5;
	src >> s.qwMember6;
	src >> s.vecExDesc;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SExDescend4& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const SExDerived1&)s;
	src << s.wMember5;
	src << s.qwMember6;
	src << s.vecExDesc;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecExDescend4& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SExDescend4Ptr p(new SExDescend4);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecExDescend4& vec)
{
	if(vec.size() > 0x7FFF)
		throw "Vector Size Too Large!";
	UINT16 wSize = (UINT16)vec.size();
	src.WriteContainerSize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
		src << *vec[i];
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SExDescend4& s)
{
	if(strcmp(rElement.Value(), "SExDescend4") != 0)
	{
		LOG_CRI << "rElement is not SExDescend4!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for SExDerived1 is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (SExDerived1&)s))
	{
		LOG_CRI << "FromXML for: SExDerived1 fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wMember5 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wMember5") != 0)
	{
		LOG_CRI << "Attribute: name is not wMember5!";
		return false;
	}
	const char* pszVal_wMember5 = pElemChild->Attribute("value");
	if(pszVal_wMember5 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wMember5, s.wMember5))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwMember6 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "INT64") != 0)
	{
		LOG_CRI << "pElemChild is not INT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwMember6") != 0)
	{
		LOG_CRI << "Attribute: name is not qwMember6!";
		return false;
	}
	const char* pszVal_qwMember6 = pElemChild->Attribute("value");
	if(pszVal_qwMember6 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwMember6, s.qwMember6))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecExDesc is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecExDescend3") != 0)
	{
		LOG_CRI << "pElemChild is not TVecExDescend3!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecExDesc") != 0)
	{
		LOG_CRI << "Attribute: name is not vecExDesc!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecExDesc))
	{
		LOG_CRI << "VectorFromXML for vecExDesc fails!";
		return false;
	}
	return true;
}

bool ToXML(const SExDescend4& s, TiXmlElement& rElement)
{
	rElement.SetValue("SExDescend4");
	rElement.SetAttribute("type", ToUTF8Ptr("结构体子类型4示例"));
	unique_ptr<TiXmlElement> pElem_SExDerived1(new TiXmlElement("SExDerived1"));
	if(pElem_SExDerived1 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const SExDerived1&)s, *pElem_SExDerived1))
	{
		LOG_CRI << "SExDerived1 ToXML fails!";
		return false;
	}
	pElem_SExDerived1->SetAttribute("type", ToUTF8Ptr("结构体子类型1示例"));
	pElem_SExDerived1->SetAttribute("comment", ToUTF8Ptr("父类SExDerived1部分"));
	if(rElement.LinkEndChild(pElem_SExDerived1.get()) != NULL)
		pElem_SExDerived1.release();
	unique_ptr<TiXmlElement> pElem_wMember5(new TiXmlElement("UINT16"));
	if(pElem_wMember5 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wMember5->SetAttribute("name", "wMember5");
	pElem_wMember5->SetAttribute("value", NumberToString(s.wMember5).c_str());
	pElem_wMember5->SetAttribute("comment", ToUTF8Ptr("成员5"));
	if(rElement.LinkEndChild(pElem_wMember5.get()) != NULL)
		pElem_wMember5.release();
	unique_ptr<TiXmlElement> pElem_qwMember6(new TiXmlElement("INT64"));
	if(pElem_qwMember6 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwMember6->SetAttribute("name", "qwMember6");
	pElem_qwMember6->SetAttribute("value", NumberToString(s.qwMember6).c_str());
	pElem_qwMember6->SetAttribute("comment", ToUTF8Ptr("成员6"));
	if(rElement.LinkEndChild(pElem_qwMember6.get()) != NULL)
		pElem_qwMember6.release();
	unique_ptr<TiXmlElement> pElem_vecExDesc(new TiXmlElement("TVecExDescend3"));
	if(pElem_vecExDesc == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecExDesc->SetAttribute("name", "vecExDesc");
	if(!VectorToXML(s.vecExDesc, *pElem_vecExDesc))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecExDesc->SetAttribute("comment", ToUTF8Ptr("成员7"));
	if(rElement.LinkEndChild(pElem_vecExDesc.get()) != NULL)
		pElem_vecExDesc.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecExDescend4& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SExDescend4Ptr p(new SExDescend4);
		if(!FromXML(*pElemMember, *p))
		{
			LOG_CRI << "FromXML fails!";
			return false;
		}
		vec.push_back(p);
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecExDescend4& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SExDescend4"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!ToXML(*vec[i], *pElemMember))
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

SExDerived2::SExDerived2() : dMember3(0), bMember4(false) { }

CInArchive& operator>>(CInArchive& src, SExDerived2& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (SExBase&)s;
	src >> s.dMember3;
	src >> s.bMember4;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SExDerived2& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const SExBase&)s;
	src << s.dMember3;
	src << s.bMember4;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecExDerived2& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SExDerived2Ptr p(new SExDerived2);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecExDerived2& vec)
{
	if(vec.size() > 0x7FFF)
		throw "Vector Size Too Large!";
	UINT16 wSize = (UINT16)vec.size();
	src.WriteContainerSize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
		src << *vec[i];
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SExDerived2& s)
{
	if(strcmp(rElement.Value(), "SExDerived2") != 0)
	{
		LOG_CRI << "rElement is not SExDerived2!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for SExBase is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (SExBase&)s))
	{
		LOG_CRI << "FromXML for: SExBase fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dMember3 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "double") != 0)
	{
		LOG_CRI << "pElemChild is not double!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dMember3") != 0)
	{
		LOG_CRI << "Attribute: name is not dMember3!";
		return false;
	}
	const char* pszVal_dMember3 = pElemChild->Attribute("value");
	if(pszVal_dMember3 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dMember3, s.dMember3))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for bMember4 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "bool") != 0)
	{
		LOG_CRI << "pElemChild is not bool!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "bMember4") != 0)
	{
		LOG_CRI << "Attribute: name is not bMember4!";
		return false;
	}
	const char* pszVal_bMember4 = pElemChild->Attribute("value");
	if(pszVal_bMember4 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_bMember4, s.bMember4))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SExDerived2& s, TiXmlElement& rElement)
{
	rElement.SetValue("SExDerived2");
	rElement.SetAttribute("type", ToUTF8Ptr("结构体子类型2示例"));
	unique_ptr<TiXmlElement> pElem_SExBase(new TiXmlElement("SExBase"));
	if(pElem_SExBase == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const SExBase&)s, *pElem_SExBase))
	{
		LOG_CRI << "SExBase ToXML fails!";
		return false;
	}
	pElem_SExBase->SetAttribute("type", ToUTF8Ptr("结构体父类型示例"));
	pElem_SExBase->SetAttribute("comment", ToUTF8Ptr("父类SExBase部分"));
	if(rElement.LinkEndChild(pElem_SExBase.get()) != NULL)
		pElem_SExBase.release();
	unique_ptr<TiXmlElement> pElem_dMember3(new TiXmlElement("double"));
	if(pElem_dMember3 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dMember3->SetAttribute("name", "dMember3");
	pElem_dMember3->SetAttribute("value", NumberToString(s.dMember3).c_str());
	pElem_dMember3->SetAttribute("comment", ToUTF8Ptr("成员3"));
	if(rElement.LinkEndChild(pElem_dMember3.get()) != NULL)
		pElem_dMember3.release();
	unique_ptr<TiXmlElement> pElem_bMember4(new TiXmlElement("bool"));
	if(pElem_bMember4 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_bMember4->SetAttribute("name", "bMember4");
	pElem_bMember4->SetAttribute("value", NumberToString(s.bMember4).c_str());
	pElem_bMember4->SetAttribute("comment", ToUTF8Ptr("成员4"));
	if(rElement.LinkEndChild(pElem_bMember4.get()) != NULL)
		pElem_bMember4.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecExDerived2& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SExDerived2Ptr p(new SExDerived2);
		if(!FromXML(*pElemMember, *p))
		{
			LOG_CRI << "FromXML fails!";
			return false;
		}
		vec.push_back(p);
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecExDerived2& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SExDerived2"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!ToXML(*vec[i], *pElemMember))
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

} //namespace NExample
