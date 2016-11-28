/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    CollectionProt.cpp
//  Purpose:      收藏协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "CollectionProt.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NCollectionProt
{

SCollectionInfo::SCollectionInfo() : qwRoleID(0), wCollectionID(0), dwCount(0), dwProcess(0), dwFinishTime(0) { }

SCollectionInfo::SCollectionInfo(UINT64 qwRoleID_, UINT16 wCollectionID_, UINT32 dwCount_, UINT32 dwProcess_, UINT32 dwFinishTime_)
			: qwRoleID(qwRoleID_), wCollectionID(wCollectionID_), dwCount(dwCount_), dwProcess(dwProcess_), dwFinishTime(dwFinishTime_) { }

CInArchive& operator>>(CInArchive& src, SCollectionInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwRoleID;
	src >> s.wCollectionID;
	src >> s.dwCount;
	src >> s.dwProcess;
	src >> s.dwFinishTime;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SCollectionInfo& s)
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
	src << s.wCollectionID;
	src << s.dwCount;
	src << s.dwProcess;
	src << s.dwFinishTime;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SCollectionInfo& s)
{
	if(strcmp(rElement.Value(), "SCollectionInfo") != 0)
	{
		LOG_CRI << "rElement is not SCollectionInfo!";
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
		LOG_CRI << "pElemChild for wCollectionID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wCollectionID") != 0)
	{
		LOG_CRI << "Attribute: name is not wCollectionID!";
		return false;
	}
	const char* pszVal_wCollectionID = pElemChild->Attribute("value");
	if(pszVal_wCollectionID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wCollectionID, s.wCollectionID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwCount is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwCount") != 0)
	{
		LOG_CRI << "Attribute: name is not dwCount!";
		return false;
	}
	const char* pszVal_dwCount = pElemChild->Attribute("value");
	if(pszVal_dwCount == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwCount, s.dwCount))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwProcess is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwProcess") != 0)
	{
		LOG_CRI << "Attribute: name is not dwProcess!";
		return false;
	}
	const char* pszVal_dwProcess = pElemChild->Attribute("value");
	if(pszVal_dwProcess == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwProcess, s.dwProcess))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwFinishTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwFinishTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwFinishTime!";
		return false;
	}
	const char* pszVal_dwFinishTime = pElemChild->Attribute("value");
	if(pszVal_dwFinishTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwFinishTime, s.dwFinishTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SCollectionInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SCollectionInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("EDataType:eTypeCollectionInfo"));
	unique_ptr<TiXmlElement> pElem_qwRoleID(new TiXmlElement("UINT64"));
	if(pElem_qwRoleID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwRoleID->SetAttribute("name", "qwRoleID");
	pElem_qwRoleID->SetAttribute("value", NumberToString(s.qwRoleID).c_str());
	pElem_qwRoleID->SetAttribute("comment", ToUTF8Ptr("角色ID"));
	if(rElement.LinkEndChild(pElem_qwRoleID.get()) != NULL)
		pElem_qwRoleID.release();
	unique_ptr<TiXmlElement> pElem_wCollectionID(new TiXmlElement("UINT16"));
	if(pElem_wCollectionID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wCollectionID->SetAttribute("name", "wCollectionID");
	pElem_wCollectionID->SetAttribute("value", NumberToString(s.wCollectionID).c_str());
	pElem_wCollectionID->SetAttribute("comment", ToUTF8Ptr("收藏ID"));
	if(rElement.LinkEndChild(pElem_wCollectionID.get()) != NULL)
		pElem_wCollectionID.release();
	unique_ptr<TiXmlElement> pElem_dwCount(new TiXmlElement("UINT32"));
	if(pElem_dwCount == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwCount->SetAttribute("name", "dwCount");
	pElem_dwCount->SetAttribute("value", NumberToString(s.dwCount).c_str());
	pElem_dwCount->SetAttribute("comment", ToUTF8Ptr("0是否完成"));
	if(rElement.LinkEndChild(pElem_dwCount.get()) != NULL)
		pElem_dwCount.release();
	unique_ptr<TiXmlElement> pElem_dwProcess(new TiXmlElement("UINT32"));
	if(pElem_dwProcess == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwProcess->SetAttribute("name", "dwProcess");
	pElem_dwProcess->SetAttribute("value", NumberToString(s.dwProcess).c_str());
	pElem_dwProcess->SetAttribute("comment", ToUTF8Ptr("当前进度(持续型事件记录数据)"));
	if(rElement.LinkEndChild(pElem_dwProcess.get()) != NULL)
		pElem_dwProcess.release();
	unique_ptr<TiXmlElement> pElem_dwFinishTime(new TiXmlElement("UINT32"));
	if(pElem_dwFinishTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwFinishTime->SetAttribute("name", "dwFinishTime");
	pElem_dwFinishTime->SetAttribute("value", NumberToString(s.dwFinishTime).c_str());
	pElem_dwFinishTime->SetAttribute("comment", ToUTF8Ptr("完成时间"));
	if(rElement.LinkEndChild(pElem_dwFinishTime.get()) != NULL)
		pElem_dwFinishTime.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecCollectionInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SCollectionInfo s;
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

bool VectorToXML(const TVecCollectionInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SCollectionInfo"));
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

} //namespace NCollectionProt
