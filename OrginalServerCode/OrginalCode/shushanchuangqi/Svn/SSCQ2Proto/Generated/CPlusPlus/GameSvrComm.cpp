/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    GameSvrComm.cpp
//  Purpose:      GameServer之间的通信协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "GameSvrComm.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NGameSvrComm
{

STest::STest() : dwParam(0) { }

STest::STest(UINT32 dwParam_) : dwParam(dwParam_) { }

CInArchive& operator>>(CInArchive& src, STest& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.dwParam;
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

bool ToXML(const STest& s, TiXmlElement& rElement)
{
	rElement.SetValue("STest");
	rElement.SetAttribute("type", ToUTF8Ptr("测试结构体"));
	unique_ptr<TiXmlElement> pElem_dwParam(new TiXmlElement("UINT32"));
	if(pElem_dwParam == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwParam->SetAttribute("name", "dwParam");
	pElem_dwParam->SetAttribute("value", NumberToString(s.dwParam).c_str());
	pElem_dwParam->SetAttribute("comment", ToUTF8Ptr("成员1"));
	if(rElement.LinkEndChild(pElem_dwParam.get()) != NULL)
		pElem_dwParam.release();
	return true;
}

#endif

} //namespace NGameSvrComm
