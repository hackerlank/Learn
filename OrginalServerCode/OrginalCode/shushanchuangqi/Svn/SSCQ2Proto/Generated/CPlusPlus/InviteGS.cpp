/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    InviteGS.cpp
//  Purpose:      邀请好友相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "InviteGS.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NInviteGS
{

#ifdef PROT_USE_XML

const char* EnumValToStr(EInviteResult e)
{
	switch(e)
	{
	case eInvite_Success:
		return "eInvite_Success";
	case eInvite_Failed:
		return "eInvite_Failed";
	case eInvite_ErrorUserID:
		return "eInvite_ErrorUserID";
	case eInvite_ErrorCFGID:
		return "eInvite_ErrorCFGID";
	case eInvite_TaskInit:
		return "eInvite_TaskInit";
	case eInvite_TaskTakedPrize:
		return "eInvite_TaskTakedPrize";
	case eInvite_ServerBusy:
		return "eInvite_ServerBusy";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EInviteResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EInviteResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eInvite_Success", eInvite_Success));
		mapStr2Val.insert(make_pair("eInvite_Failed", eInvite_Failed));
		mapStr2Val.insert(make_pair("eInvite_ErrorUserID", eInvite_ErrorUserID));
		mapStr2Val.insert(make_pair("eInvite_ErrorCFGID", eInvite_ErrorCFGID));
		mapStr2Val.insert(make_pair("eInvite_TaskInit", eInvite_TaskInit));
		mapStr2Val.insert(make_pair("eInvite_TaskTakedPrize", eInvite_TaskTakedPrize));
		mapStr2Val.insert(make_pair("eInvite_ServerBusy", eInvite_ServerBusy));
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

const char* EnumValToStr(EInvitedTask e)
{
	switch(e)
	{
	case eInvitedTask_Init:
		return "eInvitedTask_Init";
	case eInvitedTask_Finish:
		return "eInvitedTask_Finish";
	case eInvitedTask_TakePrized:
		return "eInvitedTask_TakePrized";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EInvitedTask& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EInvitedTask> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eInvitedTask_Init", eInvitedTask_Init));
		mapStr2Val.insert(make_pair("eInvitedTask_Finish", eInvitedTask_Finish));
		mapStr2Val.insert(make_pair("eInvitedTask_TakePrized", eInvitedTask_TakePrized));
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

SInvitedFriendDB::SInvitedFriendDB() : qwUserID(0), qwInviteID(0), byColor(0), byJob(0), bySex(0), 
			byLevel(0), byVIPLevel(0), dwTotalRecharge(0) { }

SInvitedFriendDB::SInvitedFriendDB(UINT64 qwUserID_, UINT64 qwInviteID_, const std::string& strName_, UINT8 byColor_, UINT8 byJob_, 
			UINT8 bySex_, UINT8 byLevel_, UINT8 byVIPLevel_, UINT32 dwTotalRecharge_)
			: qwUserID(qwUserID_), qwInviteID(qwInviteID_), strName(strName_), byColor(byColor_), byJob(byJob_), 
			bySex(bySex_), byLevel(byLevel_), byVIPLevel(byVIPLevel_), dwTotalRecharge(dwTotalRecharge_) { }

SInvitedFriendDB::SInvitedFriendDB(SInvitedFriendDB&& src) : qwUserID(src.qwUserID), qwInviteID(src.qwInviteID), strName(move(src.strName)), byColor(src.byColor), byJob(src.byJob), 
			bySex(src.bySex), byLevel(src.byLevel), byVIPLevel(src.byVIPLevel), dwTotalRecharge(src.dwTotalRecharge) { }

SInvitedFriendDB& SInvitedFriendDB::operator=(SInvitedFriendDB&& rhs)
{
	if(this != &rhs)
	{
		this->~SInvitedFriendDB();
		new (this) SInvitedFriendDB(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SInvitedFriendDB& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwUserID;
	src >> s.qwInviteID;
	src >> s.strName;
	src >> s.byColor;
	src >> s.byJob;
	src >> s.bySex;
	src >> s.byLevel;
	src >> s.byVIPLevel;
	src >> s.dwTotalRecharge;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SInvitedFriendDB& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.qwUserID;
	src << s.qwInviteID;
	src << s.strName;
	src << s.byColor;
	src << s.byJob;
	src << s.bySex;
	src << s.byLevel;
	src << s.byVIPLevel;
	src << s.dwTotalRecharge;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SInvitedFriendDB& s)
{
	if(strcmp(rElement.Value(), "SInvitedFriendDB") != 0)
	{
		LOG_CRI << "rElement is not SInvitedFriendDB!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwUserID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwUserID") != 0)
	{
		LOG_CRI << "Attribute: name is not qwUserID!";
		return false;
	}
	const char* pszVal_qwUserID = pElemChild->Attribute("value");
	if(pszVal_qwUserID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwUserID, s.qwUserID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwInviteID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwInviteID") != 0)
	{
		LOG_CRI << "Attribute: name is not qwInviteID!";
		return false;
	}
	const char* pszVal_qwInviteID = pElemChild->Attribute("value");
	if(pszVal_qwInviteID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwInviteID, s.qwInviteID))
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
		LOG_CRI << "pElemChild for byColor is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byColor") != 0)
	{
		LOG_CRI << "Attribute: name is not byColor!";
		return false;
	}
	const char* pszVal_byColor = pElemChild->Attribute("value");
	if(pszVal_byColor == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byColor, s.byColor))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byJob is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byJob") != 0)
	{
		LOG_CRI << "Attribute: name is not byJob!";
		return false;
	}
	const char* pszVal_byJob = pElemChild->Attribute("value");
	if(pszVal_byJob == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byJob, s.byJob))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for bySex is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "bySex") != 0)
	{
		LOG_CRI << "Attribute: name is not bySex!";
		return false;
	}
	const char* pszVal_bySex = pElemChild->Attribute("value");
	if(pszVal_bySex == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_bySex, s.bySex))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byLevel is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byLevel") != 0)
	{
		LOG_CRI << "Attribute: name is not byLevel!";
		return false;
	}
	const char* pszVal_byLevel = pElemChild->Attribute("value");
	if(pszVal_byLevel == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byLevel, s.byLevel))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byVIPLevel is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byVIPLevel") != 0)
	{
		LOG_CRI << "Attribute: name is not byVIPLevel!";
		return false;
	}
	const char* pszVal_byVIPLevel = pElemChild->Attribute("value");
	if(pszVal_byVIPLevel == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byVIPLevel, s.byVIPLevel))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwTotalRecharge is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwTotalRecharge") != 0)
	{
		LOG_CRI << "Attribute: name is not dwTotalRecharge!";
		return false;
	}
	const char* pszVal_dwTotalRecharge = pElemChild->Attribute("value");
	if(pszVal_dwTotalRecharge == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwTotalRecharge, s.dwTotalRecharge))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SInvitedFriendDB& s, TiXmlElement& rElement)
{
	rElement.SetValue("SInvitedFriendDB");
	rElement.SetAttribute("type", ToUTF8Ptr("被邀请好友db信息"));
	unique_ptr<TiXmlElement> pElem_qwUserID(new TiXmlElement("UINT64"));
	if(pElem_qwUserID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwUserID->SetAttribute("name", "qwUserID");
	pElem_qwUserID->SetAttribute("value", NumberToString(s.qwUserID).c_str());
	pElem_qwUserID->SetAttribute("comment", ToUTF8Ptr("帐号ID"));
	if(rElement.LinkEndChild(pElem_qwUserID.get()) != NULL)
		pElem_qwUserID.release();
	unique_ptr<TiXmlElement> pElem_qwInviteID(new TiXmlElement("UINT64"));
	if(pElem_qwInviteID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwInviteID->SetAttribute("name", "qwInviteID");
	pElem_qwInviteID->SetAttribute("value", NumberToString(s.qwInviteID).c_str());
	pElem_qwInviteID->SetAttribute("comment", ToUTF8Ptr("邀请账号ID"));
	if(rElement.LinkEndChild(pElem_qwInviteID.get()) != NULL)
		pElem_qwInviteID.release();
	unique_ptr<TiXmlElement> pElem_strName(new TiXmlElement("string"));
	if(pElem_strName == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strName->SetAttribute("name", "strName");
	pElem_strName->SetAttribute("value", s.strName.c_str());
	pElem_strName->SetAttribute("comment", ToUTF8Ptr("名字"));
	if(rElement.LinkEndChild(pElem_strName.get()) != NULL)
		pElem_strName.release();
	unique_ptr<TiXmlElement> pElem_byColor(new TiXmlElement("UINT8"));
	if(pElem_byColor == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byColor->SetAttribute("name", "byColor");
	pElem_byColor->SetAttribute("value", NumberToString(s.byColor).c_str());
	pElem_byColor->SetAttribute("comment", ToUTF8Ptr("职业"));
	if(rElement.LinkEndChild(pElem_byColor.get()) != NULL)
		pElem_byColor.release();
	unique_ptr<TiXmlElement> pElem_byJob(new TiXmlElement("UINT8"));
	if(pElem_byJob == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byJob->SetAttribute("name", "byJob");
	pElem_byJob->SetAttribute("value", NumberToString(s.byJob).c_str());
	pElem_byJob->SetAttribute("comment", ToUTF8Ptr("职业"));
	if(rElement.LinkEndChild(pElem_byJob.get()) != NULL)
		pElem_byJob.release();
	unique_ptr<TiXmlElement> pElem_bySex(new TiXmlElement("UINT8"));
	if(pElem_bySex == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_bySex->SetAttribute("name", "bySex");
	pElem_bySex->SetAttribute("value", NumberToString(s.bySex).c_str());
	pElem_bySex->SetAttribute("comment", ToUTF8Ptr("性别"));
	if(rElement.LinkEndChild(pElem_bySex.get()) != NULL)
		pElem_bySex.release();
	unique_ptr<TiXmlElement> pElem_byLevel(new TiXmlElement("UINT8"));
	if(pElem_byLevel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byLevel->SetAttribute("name", "byLevel");
	pElem_byLevel->SetAttribute("value", NumberToString(s.byLevel).c_str());
	pElem_byLevel->SetAttribute("comment", ToUTF8Ptr("等级"));
	if(rElement.LinkEndChild(pElem_byLevel.get()) != NULL)
		pElem_byLevel.release();
	unique_ptr<TiXmlElement> pElem_byVIPLevel(new TiXmlElement("UINT8"));
	if(pElem_byVIPLevel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byVIPLevel->SetAttribute("name", "byVIPLevel");
	pElem_byVIPLevel->SetAttribute("value", NumberToString(s.byVIPLevel).c_str());
	pElem_byVIPLevel->SetAttribute("comment", ToUTF8Ptr("VIP等级"));
	if(rElement.LinkEndChild(pElem_byVIPLevel.get()) != NULL)
		pElem_byVIPLevel.release();
	unique_ptr<TiXmlElement> pElem_dwTotalRecharge(new TiXmlElement("UINT32"));
	if(pElem_dwTotalRecharge == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwTotalRecharge->SetAttribute("name", "dwTotalRecharge");
	pElem_dwTotalRecharge->SetAttribute("value", NumberToString(s.dwTotalRecharge).c_str());
	pElem_dwTotalRecharge->SetAttribute("comment", ToUTF8Ptr("总充值"));
	if(rElement.LinkEndChild(pElem_dwTotalRecharge.get()) != NULL)
		pElem_dwTotalRecharge.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecInvitedFriendDB& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SInvitedFriendDB s;
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

bool VectorToXML(const TVecInvitedFriendDB& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SInvitedFriendDB"));
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

SInvitedFriend::SInvitedFriend() : qwUserID(0), byJob(0), bySex(0), byLevel(0), byVIPLevel(0), 
			dwTotalRecharge(0) { }

SInvitedFriend::SInvitedFriend(UINT64 qwUserID_, const std::string& strName_, UINT8 byJob_, UINT8 bySex_, UINT8 byLevel_, 
			UINT8 byVIPLevel_, UINT32 dwTotalRecharge_, const NProtoCommon::TVecPlatformParam& vecPlatforms_)
			: qwUserID(qwUserID_), strName(strName_), byJob(byJob_), bySex(bySex_), byLevel(byLevel_), 
			byVIPLevel(byVIPLevel_), dwTotalRecharge(dwTotalRecharge_), vecPlatforms(vecPlatforms_) { }

SInvitedFriend::SInvitedFriend(SInvitedFriend&& src) : qwUserID(src.qwUserID), strName(move(src.strName)), byJob(src.byJob), bySex(src.bySex), byLevel(src.byLevel), 
			byVIPLevel(src.byVIPLevel), dwTotalRecharge(src.dwTotalRecharge), vecPlatforms(move(src.vecPlatforms)) { }

SInvitedFriend& SInvitedFriend::operator=(SInvitedFriend&& rhs)
{
	if(this != &rhs)
	{
		this->~SInvitedFriend();
		new (this) SInvitedFriend(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SInvitedFriend& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwUserID;
	src >> s.strName;
	src >> s.byJob;
	src >> s.bySex;
	src >> s.byLevel;
	src >> s.byVIPLevel;
	src >> s.dwTotalRecharge;
	src >> s.vecPlatforms;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SInvitedFriend& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.qwUserID;
	src << s.strName;
	src << s.byJob;
	src << s.bySex;
	src << s.byLevel;
	src << s.byVIPLevel;
	src << s.dwTotalRecharge;
	src << s.vecPlatforms;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SInvitedFriend& s)
{
	if(strcmp(rElement.Value(), "SInvitedFriend") != 0)
	{
		LOG_CRI << "rElement is not SInvitedFriend!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwUserID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwUserID") != 0)
	{
		LOG_CRI << "Attribute: name is not qwUserID!";
		return false;
	}
	const char* pszVal_qwUserID = pElemChild->Attribute("value");
	if(pszVal_qwUserID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwUserID, s.qwUserID))
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
		LOG_CRI << "pElemChild for byJob is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byJob") != 0)
	{
		LOG_CRI << "Attribute: name is not byJob!";
		return false;
	}
	const char* pszVal_byJob = pElemChild->Attribute("value");
	if(pszVal_byJob == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byJob, s.byJob))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for bySex is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "bySex") != 0)
	{
		LOG_CRI << "Attribute: name is not bySex!";
		return false;
	}
	const char* pszVal_bySex = pElemChild->Attribute("value");
	if(pszVal_bySex == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_bySex, s.bySex))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byLevel is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byLevel") != 0)
	{
		LOG_CRI << "Attribute: name is not byLevel!";
		return false;
	}
	const char* pszVal_byLevel = pElemChild->Attribute("value");
	if(pszVal_byLevel == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byLevel, s.byLevel))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byVIPLevel is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byVIPLevel") != 0)
	{
		LOG_CRI << "Attribute: name is not byVIPLevel!";
		return false;
	}
	const char* pszVal_byVIPLevel = pElemChild->Attribute("value");
	if(pszVal_byVIPLevel == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byVIPLevel, s.byVIPLevel))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwTotalRecharge is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwTotalRecharge") != 0)
	{
		LOG_CRI << "Attribute: name is not dwTotalRecharge!";
		return false;
	}
	const char* pszVal_dwTotalRecharge = pElemChild->Attribute("value");
	if(pszVal_dwTotalRecharge == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwTotalRecharge, s.dwTotalRecharge))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecPlatforms is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "ProtoCommon::TVecPlatformParam") != 0)
	{
		LOG_CRI << "pElemChild is not ProtoCommon::TVecPlatformParam!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecPlatforms") != 0)
	{
		LOG_CRI << "Attribute: name is not vecPlatforms!";
		return false;
	}
	if(!NProtoCommon::VectorFromXML(*pElemChild, s.vecPlatforms))
	{
		LOG_CRI << "VectorFromXML for vecPlatforms fails!";
		return false;
	}
	return true;
}

bool ToXML(const SInvitedFriend& s, TiXmlElement& rElement)
{
	rElement.SetValue("SInvitedFriend");
	rElement.SetAttribute("type", ToUTF8Ptr("被邀请好友信息"));
	unique_ptr<TiXmlElement> pElem_qwUserID(new TiXmlElement("UINT64"));
	if(pElem_qwUserID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwUserID->SetAttribute("name", "qwUserID");
	pElem_qwUserID->SetAttribute("value", NumberToString(s.qwUserID).c_str());
	pElem_qwUserID->SetAttribute("comment", ToUTF8Ptr("帐号ID"));
	if(rElement.LinkEndChild(pElem_qwUserID.get()) != NULL)
		pElem_qwUserID.release();
	unique_ptr<TiXmlElement> pElem_strName(new TiXmlElement("string"));
	if(pElem_strName == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strName->SetAttribute("name", "strName");
	pElem_strName->SetAttribute("value", s.strName.c_str());
	pElem_strName->SetAttribute("comment", ToUTF8Ptr("名字"));
	if(rElement.LinkEndChild(pElem_strName.get()) != NULL)
		pElem_strName.release();
	unique_ptr<TiXmlElement> pElem_byJob(new TiXmlElement("UINT8"));
	if(pElem_byJob == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byJob->SetAttribute("name", "byJob");
	pElem_byJob->SetAttribute("value", NumberToString(s.byJob).c_str());
	pElem_byJob->SetAttribute("comment", ToUTF8Ptr("职业"));
	if(rElement.LinkEndChild(pElem_byJob.get()) != NULL)
		pElem_byJob.release();
	unique_ptr<TiXmlElement> pElem_bySex(new TiXmlElement("UINT8"));
	if(pElem_bySex == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_bySex->SetAttribute("name", "bySex");
	pElem_bySex->SetAttribute("value", NumberToString(s.bySex).c_str());
	pElem_bySex->SetAttribute("comment", ToUTF8Ptr("性别"));
	if(rElement.LinkEndChild(pElem_bySex.get()) != NULL)
		pElem_bySex.release();
	unique_ptr<TiXmlElement> pElem_byLevel(new TiXmlElement("UINT8"));
	if(pElem_byLevel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byLevel->SetAttribute("name", "byLevel");
	pElem_byLevel->SetAttribute("value", NumberToString(s.byLevel).c_str());
	pElem_byLevel->SetAttribute("comment", ToUTF8Ptr("等级"));
	if(rElement.LinkEndChild(pElem_byLevel.get()) != NULL)
		pElem_byLevel.release();
	unique_ptr<TiXmlElement> pElem_byVIPLevel(new TiXmlElement("UINT8"));
	if(pElem_byVIPLevel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byVIPLevel->SetAttribute("name", "byVIPLevel");
	pElem_byVIPLevel->SetAttribute("value", NumberToString(s.byVIPLevel).c_str());
	pElem_byVIPLevel->SetAttribute("comment", ToUTF8Ptr("VIP等级"));
	if(rElement.LinkEndChild(pElem_byVIPLevel.get()) != NULL)
		pElem_byVIPLevel.release();
	unique_ptr<TiXmlElement> pElem_dwTotalRecharge(new TiXmlElement("UINT32"));
	if(pElem_dwTotalRecharge == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwTotalRecharge->SetAttribute("name", "dwTotalRecharge");
	pElem_dwTotalRecharge->SetAttribute("value", NumberToString(s.dwTotalRecharge).c_str());
	pElem_dwTotalRecharge->SetAttribute("comment", ToUTF8Ptr("总充值"));
	if(rElement.LinkEndChild(pElem_dwTotalRecharge.get()) != NULL)
		pElem_dwTotalRecharge.release();
	unique_ptr<TiXmlElement> pElem_vecPlatforms(new TiXmlElement("ProtoCommon::TVecPlatformParam"));
	if(pElem_vecPlatforms == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecPlatforms->SetAttribute("name", "vecPlatforms");
	if(!NProtoCommon::VectorToXML(s.vecPlatforms, *pElem_vecPlatforms))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecPlatforms->SetAttribute("comment", ToUTF8Ptr("平台信息"));
	if(rElement.LinkEndChild(pElem_vecPlatforms.get()) != NULL)
		pElem_vecPlatforms.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecInvitedFriend& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SInvitedFriend s;
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

bool VectorToXML(const TVecInvitedFriend& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SInvitedFriend"));
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

SInvitedTask::SInvitedTask() : dwInviteTaskID(0), wTaskType(0), eInvitedTask((EInvitedTask)0) { }

SInvitedTask::SInvitedTask(UINT32 dwInviteTaskID_, UINT16 wTaskType_, EInvitedTask eInvitedTask_) : dwInviteTaskID(dwInviteTaskID_), wTaskType(wTaskType_), eInvitedTask(eInvitedTask_) { }

CInArchive& operator>>(CInArchive& src, SInvitedTask& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.dwInviteTaskID;
	src >> s.wTaskType;
	src >> (UINT8&)s.eInvitedTask;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SInvitedTask& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.dwInviteTaskID;
	src << s.wTaskType;
	src << (UINT8&)s.eInvitedTask;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SInvitedTask& s)
{
	if(strcmp(rElement.Value(), "SInvitedTask") != 0)
	{
		LOG_CRI << "rElement is not SInvitedTask!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwInviteTaskID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwInviteTaskID") != 0)
	{
		LOG_CRI << "Attribute: name is not dwInviteTaskID!";
		return false;
	}
	const char* pszVal_dwInviteTaskID = pElemChild->Attribute("value");
	if(pszVal_dwInviteTaskID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwInviteTaskID, s.dwInviteTaskID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wTaskType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wTaskType") != 0)
	{
		LOG_CRI << "Attribute: name is not wTaskType!";
		return false;
	}
	const char* pszVal_wTaskType = pElemChild->Attribute("value");
	if(pszVal_wTaskType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wTaskType, s.wTaskType))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eInvitedTask is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "EInvitedTask") != 0)
	{
		LOG_CRI << "pElemChild is not EInvitedTask!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eInvitedTask") != 0)
	{
		LOG_CRI << "Attribute: name is not eInvitedTask!";
		return false;
	}
	const char* pszVal_eInvitedTask = pElemChild->Attribute("value");
	if(pszVal_eInvitedTask == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!EnumStrToVal(pszVal_eInvitedTask, s.eInvitedTask))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SInvitedTask& s, TiXmlElement& rElement)
{
	rElement.SetValue("SInvitedTask");
	rElement.SetAttribute("type", ToUTF8Ptr("邀请任务状态"));
	unique_ptr<TiXmlElement> pElem_dwInviteTaskID(new TiXmlElement("UINT32"));
	if(pElem_dwInviteTaskID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwInviteTaskID->SetAttribute("name", "dwInviteTaskID");
	pElem_dwInviteTaskID->SetAttribute("value", NumberToString(s.dwInviteTaskID).c_str());
	pElem_dwInviteTaskID->SetAttribute("comment", ToUTF8Ptr("任务id"));
	if(rElement.LinkEndChild(pElem_dwInviteTaskID.get()) != NULL)
		pElem_dwInviteTaskID.release();
	unique_ptr<TiXmlElement> pElem_wTaskType(new TiXmlElement("UINT16"));
	if(pElem_wTaskType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wTaskType->SetAttribute("name", "wTaskType");
	pElem_wTaskType->SetAttribute("value", NumberToString(s.wTaskType).c_str());
	pElem_wTaskType->SetAttribute("comment", ToUTF8Ptr("任务类型"));
	if(rElement.LinkEndChild(pElem_wTaskType.get()) != NULL)
		pElem_wTaskType.release();
	unique_ptr<TiXmlElement> pElem_eInvitedTask(new TiXmlElement("EInvitedTask"));
	if(pElem_eInvitedTask == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eInvitedTask->SetAttribute("name", "eInvitedTask");
	const char* pszEnum_eInvitedTask = EnumValToStr(s.eInvitedTask);
	if(pszEnum_eInvitedTask == NULL)
	{
		LOG_CRI << "EnumValToStr for EInvitedTask fails!";
		return false;
	}
	pElem_eInvitedTask->SetAttribute("value", pszEnum_eInvitedTask);
	pElem_eInvitedTask->SetAttribute("comment", ToUTF8Ptr("任务状态"));
	if(rElement.LinkEndChild(pElem_eInvitedTask.get()) != NULL)
		pElem_eInvitedTask.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecInvitedTask& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SInvitedTask s;
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

bool VectorToXML(const TVecInvitedTask& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SInvitedTask"));
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

} //namespace NInviteGS
