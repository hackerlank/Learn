/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    Center2DBGuild.cpp
//  Purpose:      CenterServer到DBServer有关帮派的通信协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "Center2DBGuild.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NCenter2DBGuild
{

SGSWorshipInfo::SGSWorshipInfo() : qwGuildID(0), byWorshipCount(0) { }

SGSWorshipInfo::SGSWorshipInfo(UINT64 qwGuildID_, UINT8 byWorshipCount_, const TVecUINT64& vecMemberID_) : qwGuildID(qwGuildID_), byWorshipCount(byWorshipCount_), vecMemberID(vecMemberID_) { }

CInArchive& operator>>(CInArchive& src, SGSWorshipInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwGuildID;
	src >> s.byWorshipCount;
	src >> s.vecMemberID;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SGSWorshipInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.qwGuildID;
	src << s.byWorshipCount;
	src << s.vecMemberID;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SGSWorshipInfo& s)
{
	if(strcmp(rElement.Value(), "SGSWorshipInfo") != 0)
	{
		LOG_CRI << "rElement is not SGSWorshipInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwGuildID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwGuildID") != 0)
	{
		LOG_CRI << "Attribute: name is not qwGuildID!";
		return false;
	}
	const char* pszVal_qwGuildID = pElemChild->Attribute("value");
	if(pszVal_qwGuildID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwGuildID, s.qwGuildID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byWorshipCount is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byWorshipCount") != 0)
	{
		LOG_CRI << "Attribute: name is not byWorshipCount!";
		return false;
	}
	const char* pszVal_byWorshipCount = pElemChild->Attribute("value");
	if(pszVal_byWorshipCount == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byWorshipCount, s.byWorshipCount))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecMemberID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecUINT64") != 0)
	{
		LOG_CRI << "pElemChild is not TVecUINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecMemberID") != 0)
	{
		LOG_CRI << "Attribute: name is not vecMemberID!";
		return false;
	}
	const char* pszText_vecMemberID = pElemChild->GetText();
	if(pszText_vecMemberID != NULL)
		SplitToNumber(pszText_vecMemberID, ",", s.vecMemberID);
	return true;
}

bool ToXML(const SGSWorshipInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SGSWorshipInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("帮派神像供奉人数信息"));
	unique_ptr<TiXmlElement> pElem_qwGuildID(new TiXmlElement("UINT64"));
	if(pElem_qwGuildID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwGuildID->SetAttribute("name", "qwGuildID");
	pElem_qwGuildID->SetAttribute("value", NumberToString(s.qwGuildID).c_str());
	pElem_qwGuildID->SetAttribute("comment", ToUTF8Ptr("帮派ID"));
	if(rElement.LinkEndChild(pElem_qwGuildID.get()) != NULL)
		pElem_qwGuildID.release();
	unique_ptr<TiXmlElement> pElem_byWorshipCount(new TiXmlElement("UINT8"));
	if(pElem_byWorshipCount == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byWorshipCount->SetAttribute("name", "byWorshipCount");
	pElem_byWorshipCount->SetAttribute("value", NumberToString(s.byWorshipCount).c_str());
	pElem_byWorshipCount->SetAttribute("comment", ToUTF8Ptr("供奉人数"));
	if(rElement.LinkEndChild(pElem_byWorshipCount.get()) != NULL)
		pElem_byWorshipCount.release();
	unique_ptr<TiXmlElement> pElem_vecMemberID(new TiXmlElement("TVecUINT64"));
	if(pElem_vecMemberID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecMemberID->SetAttribute("name", "vecMemberID");
	string strText_vecMemberID;
	for(size_t i = 0; i < s.vecMemberID.size(); ++i)
	{
		if(i > 0)
			strText_vecMemberID += ", ";
		strText_vecMemberID += NumberToString(s.vecMemberID[i]);
	}
	unique_ptr<TiXmlText> pText_vecMemberID(new TiXmlText(strText_vecMemberID.c_str()));
	if(pText_vecMemberID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(pElem_vecMemberID->LinkEndChild(pText_vecMemberID.get()) != NULL)
		pText_vecMemberID.release();
	pElem_vecMemberID->SetAttribute("comment", ToUTF8Ptr("帮派成员ID"));
	if(rElement.LinkEndChild(pElem_vecMemberID.get()) != NULL)
		pElem_vecMemberID.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecGSWorshipInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SGSWorshipInfo s;
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

bool VectorToXML(const TVecGSWorshipInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SGSWorshipInfo"));
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

} //namespace NCenter2DBGuild
