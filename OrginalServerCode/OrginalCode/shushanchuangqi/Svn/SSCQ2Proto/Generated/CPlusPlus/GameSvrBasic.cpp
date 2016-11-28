/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    GameSvrBasic.cpp
//  Purpose:      GameServer的基本协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "GameSvrBasic.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NGameSvrBasic
{

#ifdef PROT_USE_XML

const char* EnumValToStr(EBreakReason e)
{
	switch(e)
	{
	case eBreakNone:
		return "eBreakNone";
	case eBreakUsrKick:
		return "eBreakUsrKick";
	case eBreakSvrKick:
		return "eBreakSvrKick";
	case eBreakExcept:
		return "eBreakExcept";
	case eBreakOther:
		return "eBreakOther";
	case eBreakIndulgeKick:
		return "eBreakIndulgeKick";
	case eBreakIndulgeTimeKick:
		return "eBreakIndulgeTimeKick";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EBreakReason& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EBreakReason> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eBreakNone", eBreakNone));
		mapStr2Val.insert(make_pair("eBreakUsrKick", eBreakUsrKick));
		mapStr2Val.insert(make_pair("eBreakSvrKick", eBreakSvrKick));
		mapStr2Val.insert(make_pair("eBreakExcept", eBreakExcept));
		mapStr2Val.insert(make_pair("eBreakOther", eBreakOther));
		mapStr2Val.insert(make_pair("eBreakIndulgeKick", eBreakIndulgeKick));
		mapStr2Val.insert(make_pair("eBreakIndulgeTimeKick", eBreakIndulgeTimeKick));
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

SGMCommand::SGMCommand() { }

SGMCommand::SGMCommand(const std::string& strCmd_, const std::string& strName_, const std::string& strDesc_) : strCmd(strCmd_), strName(strName_), strDesc(strDesc_) { }

SGMCommand::SGMCommand(SGMCommand&& src) : strCmd(move(src.strCmd)), strName(move(src.strName)), strDesc(move(src.strDesc)) { }

SGMCommand& SGMCommand::operator=(SGMCommand&& rhs)
{
	if(this != &rhs)
	{
		this->~SGMCommand();
		new (this) SGMCommand(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SGMCommand& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.strCmd;
	src >> s.strName;
	src >> s.strDesc;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SGMCommand& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.strCmd;
	src << s.strName;
	src << s.strDesc;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SGMCommand& s)
{
	if(strcmp(rElement.Value(), "SGMCommand") != 0)
	{
		LOG_CRI << "rElement is not SGMCommand!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strCmd is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strCmd") != 0)
	{
		LOG_CRI << "Attribute: name is not strCmd!";
		return false;
	}
	const char* pszVal_strCmd = pElemChild->Attribute("value");
	if(pszVal_strCmd == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strCmd = pszVal_strCmd;
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
		LOG_CRI << "pElemChild for strDesc is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strDesc") != 0)
	{
		LOG_CRI << "Attribute: name is not strDesc!";
		return false;
	}
	const char* pszVal_strDesc = pElemChild->Attribute("value");
	if(pszVal_strDesc == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strDesc = pszVal_strDesc;
	return true;
}

bool ToXML(const SGMCommand& s, TiXmlElement& rElement)
{
	rElement.SetValue("SGMCommand");
	rElement.SetAttribute("type", ToUTF8Ptr("GM命令"));
	unique_ptr<TiXmlElement> pElem_strCmd(new TiXmlElement("string"));
	if(pElem_strCmd == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strCmd->SetAttribute("name", "strCmd");
	pElem_strCmd->SetAttribute("value", s.strCmd.c_str());
	pElem_strCmd->SetAttribute("comment", ToUTF8Ptr("命令"));
	if(rElement.LinkEndChild(pElem_strCmd.get()) != NULL)
		pElem_strCmd.release();
	unique_ptr<TiXmlElement> pElem_strName(new TiXmlElement("string"));
	if(pElem_strName == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strName->SetAttribute("name", "strName");
	pElem_strName->SetAttribute("value", s.strName.c_str());
	pElem_strName->SetAttribute("comment", ToUTF8Ptr("名称"));
	if(rElement.LinkEndChild(pElem_strName.get()) != NULL)
		pElem_strName.release();
	unique_ptr<TiXmlElement> pElem_strDesc(new TiXmlElement("string"));
	if(pElem_strDesc == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strDesc->SetAttribute("name", "strDesc");
	pElem_strDesc->SetAttribute("value", s.strDesc.c_str());
	pElem_strDesc->SetAttribute("comment", ToUTF8Ptr("描述"));
	if(rElement.LinkEndChild(pElem_strDesc.get()) != NULL)
		pElem_strDesc.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecGMCommand& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SGMCommand s;
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

bool VectorToXML(const TVecGMCommand& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SGMCommand"));
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

} //namespace NGameSvrBasic
