/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    AchievementProt.cpp
//  Purpose:      成就相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "AchievementProt.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NAchievementProt
{

#ifdef PROT_USE_XML

const char* EnumValToStr(EAchievementRet e)
{
	switch(e)
	{
	case eAchievementRet_Sucess:
		return "eAchievementRet_Sucess";
	case eAchievementRet_NotFinish:
		return "eAchievementRet_NotFinish";
	case eAchievementRet_TakePrized:
		return "eAchievementRet_TakePrized";
	case eAchievementRet_ErrorCFG:
		return "eAchievementRet_ErrorCFG";
	case eAchievementRet_PackFull:
		return "eAchievementRet_PackFull";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EAchievementRet& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EAchievementRet> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eAchievementRet_Sucess", eAchievementRet_Sucess));
		mapStr2Val.insert(make_pair("eAchievementRet_NotFinish", eAchievementRet_NotFinish));
		mapStr2Val.insert(make_pair("eAchievementRet_TakePrized", eAchievementRet_TakePrized));
		mapStr2Val.insert(make_pair("eAchievementRet_ErrorCFG", eAchievementRet_ErrorCFG));
		mapStr2Val.insert(make_pair("eAchievementRet_PackFull", eAchievementRet_PackFull));
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

const char* GetDescription(EAchievementRet e)
{
	switch(e)
	{
	case eAchievementRet_Sucess:
		return "成功";
	case eAchievementRet_NotFinish:
		return "未完成";
	case eAchievementRet_TakePrized:
		return "已领奖";
	case eAchievementRet_ErrorCFG:
		return "配置错误";
	case eAchievementRet_PackFull:
		return "包满";
	default:
		return "未知错误";
	}
}

#ifdef PROT_USE_XML

const char* EnumValToStr(EAchievementProcess e)
{
	switch(e)
	{
	case eAchievementProcess_Init:
		return "eAchievementProcess_Init";
	case eAchievementProcess_Finish:
		return "eAchievementProcess_Finish";
	case eAchievementProcess_TakePrize:
		return "eAchievementProcess_TakePrize";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EAchievementProcess& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EAchievementProcess> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eAchievementProcess_Init", eAchievementProcess_Init));
		mapStr2Val.insert(make_pair("eAchievementProcess_Finish", eAchievementProcess_Finish));
		mapStr2Val.insert(make_pair("eAchievementProcess_TakePrize", eAchievementProcess_TakePrize));
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

const char* GetDescription(EAchievementProcess e)
{
	switch(e)
	{
	case eAchievementProcess_Init:
		return "未完成";
	case eAchievementProcess_Finish:
		return "已完成";
	case eAchievementProcess_TakePrize:
		return "已领奖";
	default:
		return "未知错误";
	}
}

#ifdef PROT_USE_XML

const char* EnumValToStr(EAchievementShareType e)
{
	switch(e)
	{
	case eAchievementShareType_Invalid:
		return "eAchievementShareType_Invalid";
	case eAchievementShareType_Friend:
		return "eAchievementShareType_Friend";
	case eAchievementShareType_Game:
		return "eAchievementShareType_Game";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EAchievementShareType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EAchievementShareType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eAchievementShareType_Invalid", eAchievementShareType_Invalid));
		mapStr2Val.insert(make_pair("eAchievementShareType_Friend", eAchievementShareType_Friend));
		mapStr2Val.insert(make_pair("eAchievementShareType_Game", eAchievementShareType_Game));
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

const char* GetDescription(EAchievementShareType e)
{
	switch(e)
	{
	case eAchievementShareType_Invalid:
		return "无效类型";
	case eAchievementShareType_Friend:
		return "qq好友分享";
	case eAchievementShareType_Game:
		return "游戏内炫耀";
	default:
		return "未知错误";
	}
}

SAchievementInfo::SAchievementInfo() : qwRoleID(0), wAchievementID(0), dwCount(0), dwProcess(0), dwFinishTime(0) { }

SAchievementInfo::SAchievementInfo(UINT64 qwRoleID_, UINT16 wAchievementID_, UINT32 dwCount_, UINT32 dwProcess_, UINT32 dwFinishTime_)
			: qwRoleID(qwRoleID_), wAchievementID(wAchievementID_), dwCount(dwCount_), dwProcess(dwProcess_), dwFinishTime(dwFinishTime_) { }

CInArchive& operator>>(CInArchive& src, SAchievementInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwRoleID;
	src >> s.wAchievementID;
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

COutArchive& operator<<(COutArchive& src, const SAchievementInfo& s)
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
	src << s.wAchievementID;
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

bool FromXML(TiXmlElement& rElement, SAchievementInfo& s)
{
	if(strcmp(rElement.Value(), "SAchievementInfo") != 0)
	{
		LOG_CRI << "rElement is not SAchievementInfo!";
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
		LOG_CRI << "pElemChild for wAchievementID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wAchievementID") != 0)
	{
		LOG_CRI << "Attribute: name is not wAchievementID!";
		return false;
	}
	const char* pszVal_wAchievementID = pElemChild->Attribute("value");
	if(pszVal_wAchievementID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wAchievementID, s.wAchievementID))
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

bool ToXML(const SAchievementInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SAchievementInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("EDataType:eTypeAchievementInfo"));
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
	unique_ptr<TiXmlElement> pElem_wAchievementID(new TiXmlElement("UINT16"));
	if(pElem_wAchievementID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wAchievementID->SetAttribute("name", "wAchievementID");
	pElem_wAchievementID->SetAttribute("value", NumberToString(s.wAchievementID).c_str());
	pElem_wAchievementID->SetAttribute("comment", ToUTF8Ptr("成就ID"));
	if(rElement.LinkEndChild(pElem_wAchievementID.get()) != NULL)
		pElem_wAchievementID.release();
	unique_ptr<TiXmlElement> pElem_dwCount(new TiXmlElement("UINT32"));
	if(pElem_dwCount == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwCount->SetAttribute("name", "dwCount");
	pElem_dwCount->SetAttribute("value", NumberToString(s.dwCount).c_str());
	pElem_dwCount->SetAttribute("comment", ToUTF8Ptr("EAchievementProcess类型成就完成进度"));
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

bool VectorFromXML(TiXmlElement& rElement, TVecAchievementInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SAchievementInfo s;
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

bool VectorToXML(const TVecAchievementInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SAchievementInfo"));
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

SAchievementShare::SAchievementShare() : wAchievementID(0), eProcess((EAchievementProcess)0) { }

SAchievementShare::SAchievementShare(UINT16 wAchievementID_, EAchievementProcess eProcess_) : wAchievementID(wAchievementID_), eProcess(eProcess_) { }

CInArchive& operator>>(CInArchive& src, SAchievementShare& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.wAchievementID;
	src >> (UINT8&)s.eProcess;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SAchievementShare& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.wAchievementID;
	src << (UINT8&)s.eProcess;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SAchievementShare& s)
{
	if(strcmp(rElement.Value(), "SAchievementShare") != 0)
	{
		LOG_CRI << "rElement is not SAchievementShare!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wAchievementID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wAchievementID") != 0)
	{
		LOG_CRI << "Attribute: name is not wAchievementID!";
		return false;
	}
	const char* pszVal_wAchievementID = pElemChild->Attribute("value");
	if(pszVal_wAchievementID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wAchievementID, s.wAchievementID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eProcess is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "EAchievementProcess") != 0)
	{
		LOG_CRI << "pElemChild is not EAchievementProcess!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eProcess") != 0)
	{
		LOG_CRI << "Attribute: name is not eProcess!";
		return false;
	}
	const char* pszVal_eProcess = pElemChild->Attribute("value");
	if(pszVal_eProcess == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!EnumStrToVal(pszVal_eProcess, s.eProcess))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SAchievementShare& s, TiXmlElement& rElement)
{
	rElement.SetValue("SAchievementShare");
	rElement.SetAttribute("type", ToUTF8Ptr("成就分享列表"));
	unique_ptr<TiXmlElement> pElem_wAchievementID(new TiXmlElement("UINT16"));
	if(pElem_wAchievementID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wAchievementID->SetAttribute("name", "wAchievementID");
	pElem_wAchievementID->SetAttribute("value", NumberToString(s.wAchievementID).c_str());
	pElem_wAchievementID->SetAttribute("comment", ToUTF8Ptr("成就ID"));
	if(rElement.LinkEndChild(pElem_wAchievementID.get()) != NULL)
		pElem_wAchievementID.release();
	unique_ptr<TiXmlElement> pElem_eProcess(new TiXmlElement("EAchievementProcess"));
	if(pElem_eProcess == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eProcess->SetAttribute("name", "eProcess");
	const char* pszEnum_eProcess = EnumValToStr(s.eProcess);
	if(pszEnum_eProcess == NULL)
	{
		LOG_CRI << "EnumValToStr for EAchievementProcess fails!";
		return false;
	}
	pElem_eProcess->SetAttribute("value", pszEnum_eProcess);
	pElem_eProcess->SetAttribute("comment", ToUTF8Ptr("分享状态"));
	if(rElement.LinkEndChild(pElem_eProcess.get()) != NULL)
		pElem_eProcess.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecAchievementShare& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SAchievementShare s;
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

bool VectorToXML(const TVecAchievementShare& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SAchievementShare"));
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

} //namespace NAchievementProt
