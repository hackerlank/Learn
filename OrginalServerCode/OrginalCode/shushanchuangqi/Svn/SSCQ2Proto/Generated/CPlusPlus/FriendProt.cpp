/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    FriendProt.cpp
//  Purpose:      好友相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "FriendProt.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NFriendProt
{

#ifdef PROT_USE_XML

const char* EnumValToStr(EFriendResult e)
{
	switch(e)
	{
	case eFriendSuccess:
		return "eFriendSuccess";
	case eFriendFailed:
		return "eFriendFailed";
	case eFriendDuplicateErr:
		return "eFriendDuplicateErr";
	case eFriendOtherDuplicateErr:
		return "eFriendOtherDuplicateErr";
	case eFriendMaxNumErr:
		return "eFriendMaxNumErr";
	case eFriendOtherMaxNumErr:
		return "eFriendOtherMaxNumErr";
	case eFriendOfflineErr:
		return "eFriendOfflineErr";
	case eFriendRefuseErr:
		return "eFriendRefuseErr";
	case eFriendNotExistErr:
		return "eFriendNotExistErr";
	case eFriendGroupIDErr:
		return "eFriendGroupIDErr";
	case eFriendOnBlackList:
		return "eFriendOnBlackList";
	case eFriendOnTarBlackList:
		return "eFriendOnTarBlackList";
	case eFriendSign:
		return "eFriendSign";
	case eFriendSignLenErr:
		return "eFriendSignLenErr";
	case eFriendMood:
		return "eFriendMood";
	case eFriendOtherErr:
		return "eFriendOtherErr";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EFriendResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EFriendResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eFriendSuccess", eFriendSuccess));
		mapStr2Val.insert(make_pair("eFriendFailed", eFriendFailed));
		mapStr2Val.insert(make_pair("eFriendDuplicateErr", eFriendDuplicateErr));
		mapStr2Val.insert(make_pair("eFriendOtherDuplicateErr", eFriendOtherDuplicateErr));
		mapStr2Val.insert(make_pair("eFriendMaxNumErr", eFriendMaxNumErr));
		mapStr2Val.insert(make_pair("eFriendOtherMaxNumErr", eFriendOtherMaxNumErr));
		mapStr2Val.insert(make_pair("eFriendOfflineErr", eFriendOfflineErr));
		mapStr2Val.insert(make_pair("eFriendRefuseErr", eFriendRefuseErr));
		mapStr2Val.insert(make_pair("eFriendNotExistErr", eFriendNotExistErr));
		mapStr2Val.insert(make_pair("eFriendGroupIDErr", eFriendGroupIDErr));
		mapStr2Val.insert(make_pair("eFriendOnBlackList", eFriendOnBlackList));
		mapStr2Val.insert(make_pair("eFriendOnTarBlackList", eFriendOnTarBlackList));
		mapStr2Val.insert(make_pair("eFriendSign", eFriendSign));
		mapStr2Val.insert(make_pair("eFriendSignLenErr", eFriendSignLenErr));
		mapStr2Val.insert(make_pair("eFriendMood", eFriendMood));
		mapStr2Val.insert(make_pair("eFriendOtherErr", eFriendOtherErr));
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

const char* EnumValToStr(EFriendGroupType e)
{
	switch(e)
	{
	case eGroupNone:
		return "eGroupNone";
	case eCloseFriend:
		return "eCloseFriend";
	case eCommonFriend:
		return "eCommonFriend";
	case eBlackFriend:
		return "eBlackFriend";
	case eGroupEnd:
		return "eGroupEnd";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EFriendGroupType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EFriendGroupType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eGroupNone", eGroupNone));
		mapStr2Val.insert(make_pair("eCloseFriend", eCloseFriend));
		mapStr2Val.insert(make_pair("eCommonFriend", eCommonFriend));
		mapStr2Val.insert(make_pair("eBlackFriend", eBlackFriend));
		mapStr2Val.insert(make_pair("eGroupEnd", eGroupEnd));
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

const char* GetDescription(EFriendGroupType e)
{
	switch(e)
	{
	case eGroupNone:
		return "无";
	case eCloseFriend:
		return "亲密好友";
	case eCommonFriend:
		return "普通好友";
	case eBlackFriend:
		return "黑名单";
	case eGroupEnd:
		return "结尾";
	default:
		return "未知错误";
	}
}

SFriendDBInfo::SFriendDBInfo() : byGroup(0), qwUserID(0), wFighterID(0), byLevel(0), wMood(0), 
			byVIPLevel(0), byColor(0) { }

SFriendDBInfo::SFriendDBInfo(UINT8 byGroup_, UINT64 qwUserID_, const std::string& strName_, UINT16 wFighterID_, UINT8 byLevel_, 
			UINT16 wMood_, UINT8 byVIPLevel_, const std::string& strSign_, UINT8 byColor_)
			: byGroup(byGroup_), qwUserID(qwUserID_), strName(strName_), wFighterID(wFighterID_), byLevel(byLevel_), 
			wMood(wMood_), byVIPLevel(byVIPLevel_), strSign(strSign_), byColor(byColor_) { }

SFriendDBInfo::SFriendDBInfo(SFriendDBInfo&& src) : byGroup(src.byGroup), qwUserID(src.qwUserID), strName(move(src.strName)), wFighterID(src.wFighterID), byLevel(src.byLevel), 
			wMood(src.wMood), byVIPLevel(src.byVIPLevel), strSign(move(src.strSign)), byColor(src.byColor) { }

SFriendDBInfo& SFriendDBInfo::operator=(SFriendDBInfo&& rhs)
{
	if(this != &rhs)
	{
		this->~SFriendDBInfo();
		new (this) SFriendDBInfo(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SFriendDBInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.byGroup;
	src >> s.qwUserID;
	src >> s.strName;
	src >> s.wFighterID;
	src >> s.byLevel;
	src >> s.wMood;
	src >> s.byVIPLevel;
	src >> s.strSign;
	src >> s.byColor;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SFriendDBInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.byGroup;
	src << s.qwUserID;
	src << s.strName;
	src << s.wFighterID;
	src << s.byLevel;
	src << s.wMood;
	src << s.byVIPLevel;
	src << s.strSign;
	src << s.byColor;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SFriendDBInfo& s)
{
	if(strcmp(rElement.Value(), "SFriendDBInfo") != 0)
	{
		LOG_CRI << "rElement is not SFriendDBInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byGroup is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byGroup") != 0)
	{
		LOG_CRI << "Attribute: name is not byGroup!";
		return false;
	}
	const char* pszVal_byGroup = pElemChild->Attribute("value");
	if(pszVal_byGroup == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byGroup, s.byGroup))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
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
		LOG_CRI << "pElemChild for wFighterID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wFighterID") != 0)
	{
		LOG_CRI << "Attribute: name is not wFighterID!";
		return false;
	}
	const char* pszVal_wFighterID = pElemChild->Attribute("value");
	if(pszVal_wFighterID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wFighterID, s.wFighterID))
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
		LOG_CRI << "pElemChild for wMood is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wMood") != 0)
	{
		LOG_CRI << "Attribute: name is not wMood!";
		return false;
	}
	const char* pszVal_wMood = pElemChild->Attribute("value");
	if(pszVal_wMood == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wMood, s.wMood))
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
		LOG_CRI << "pElemChild for strSign is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strSign") != 0)
	{
		LOG_CRI << "Attribute: name is not strSign!";
		return false;
	}
	const char* pszVal_strSign = pElemChild->Attribute("value");
	if(pszVal_strSign == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strSign = pszVal_strSign;
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
	return true;
}

bool ToXML(const SFriendDBInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SFriendDBInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("好友条目"));
	unique_ptr<TiXmlElement> pElem_byGroup(new TiXmlElement("UINT8"));
	if(pElem_byGroup == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byGroup->SetAttribute("name", "byGroup");
	pElem_byGroup->SetAttribute("value", NumberToString(s.byGroup).c_str());
	pElem_byGroup->SetAttribute("comment", ToUTF8Ptr("分组ID"));
	if(rElement.LinkEndChild(pElem_byGroup.get()) != NULL)
		pElem_byGroup.release();
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
	pElem_strName->SetAttribute("comment", ToUTF8Ptr("名字 XXX: 如果主将改名需要修改此处"));
	if(rElement.LinkEndChild(pElem_strName.get()) != NULL)
		pElem_strName.release();
	unique_ptr<TiXmlElement> pElem_wFighterID(new TiXmlElement("UINT16"));
	if(pElem_wFighterID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wFighterID->SetAttribute("name", "wFighterID");
	pElem_wFighterID->SetAttribute("value", NumberToString(s.wFighterID).c_str());
	pElem_wFighterID->SetAttribute("comment", ToUTF8Ptr("主将ID"));
	if(rElement.LinkEndChild(pElem_wFighterID.get()) != NULL)
		pElem_wFighterID.release();
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
	unique_ptr<TiXmlElement> pElem_wMood(new TiXmlElement("UINT16"));
	if(pElem_wMood == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wMood->SetAttribute("name", "wMood");
	pElem_wMood->SetAttribute("value", NumberToString(s.wMood).c_str());
	pElem_wMood->SetAttribute("comment", ToUTF8Ptr("心情表情"));
	if(rElement.LinkEndChild(pElem_wMood.get()) != NULL)
		pElem_wMood.release();
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
	unique_ptr<TiXmlElement> pElem_strSign(new TiXmlElement("string"));
	if(pElem_strSign == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strSign->SetAttribute("name", "strSign");
	pElem_strSign->SetAttribute("value", s.strSign.c_str());
	pElem_strSign->SetAttribute("comment", ToUTF8Ptr("签名"));
	if(rElement.LinkEndChild(pElem_strSign.get()) != NULL)
		pElem_strSign.release();
	unique_ptr<TiXmlElement> pElem_byColor(new TiXmlElement("UINT8"));
	if(pElem_byColor == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byColor->SetAttribute("name", "byColor");
	pElem_byColor->SetAttribute("value", NumberToString(s.byColor).c_str());
	pElem_byColor->SetAttribute("comment", ToUTF8Ptr("好友颜色"));
	if(rElement.LinkEndChild(pElem_byColor.get()) != NULL)
		pElem_byColor.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecFriendDBInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SFriendDBInfo s;
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

bool VectorToXML(const TVecFriendDBInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SFriendDBInfo"));
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

SFriendEntry::SFriendEntry() : eGroupType((EFriendGroupType)0), qwUserID(0), wFighterID(0), eSex((NProtoCommon::ESexType)0), byLevel(0), 
			byVIPLevel(0), byColor(0), wMood(0), dwTotalRecharge(0), bOnlineStatus(false) { }

SFriendEntry::SFriendEntry(SFriendEntry&& src) : eGroupType(src.eGroupType), qwUserID(src.qwUserID), strName(move(src.strName)), wFighterID(src.wFighterID), eSex(src.eSex), 
			byLevel(src.byLevel), byVIPLevel(src.byVIPLevel), byColor(src.byColor), wMood(src.wMood), strSign(move(src.strSign)), 
			dwTotalRecharge(src.dwTotalRecharge), bOnlineStatus(src.bOnlineStatus), vecPlatforms(move(src.vecPlatforms)) { }

SFriendEntry& SFriendEntry::operator=(SFriendEntry&& rhs)
{
	if(this != &rhs)
	{
		this->~SFriendEntry();
		new (this) SFriendEntry(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SFriendEntry& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (UINT8&)s.eGroupType;
	src >> s.qwUserID;
	src >> s.strName;
	src >> s.wFighterID;
	src >> (UINT8&)s.eSex;
	src >> s.byLevel;
	src >> s.byVIPLevel;
	src >> s.byColor;
	src >> s.wMood;
	src >> s.strSign;
	src >> s.dwTotalRecharge;
	src >> s.bOnlineStatus;
	src >> s.vecPlatforms;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SFriendEntry& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (UINT8&)s.eGroupType;
	src << s.qwUserID;
	src << s.strName;
	src << s.wFighterID;
	src << (UINT8&)s.eSex;
	src << s.byLevel;
	src << s.byVIPLevel;
	src << s.byColor;
	src << s.wMood;
	src << s.strSign;
	src << s.dwTotalRecharge;
	src << s.bOnlineStatus;
	src << s.vecPlatforms;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecFriendEntry& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SFriendEntryPtr p(new SFriendEntry);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecFriendEntry& vec)
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

bool FromXML(TiXmlElement& rElement, SFriendEntry& s)
{
	if(strcmp(rElement.Value(), "SFriendEntry") != 0)
	{
		LOG_CRI << "rElement is not SFriendEntry!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eGroupType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "EFriendGroupType") != 0)
	{
		LOG_CRI << "pElemChild is not EFriendGroupType!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eGroupType") != 0)
	{
		LOG_CRI << "Attribute: name is not eGroupType!";
		return false;
	}
	const char* pszVal_eGroupType = pElemChild->Attribute("value");
	if(pszVal_eGroupType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!EnumStrToVal(pszVal_eGroupType, s.eGroupType))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
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
		LOG_CRI << "pElemChild for wFighterID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wFighterID") != 0)
	{
		LOG_CRI << "Attribute: name is not wFighterID!";
		return false;
	}
	const char* pszVal_wFighterID = pElemChild->Attribute("value");
	if(pszVal_wFighterID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wFighterID, s.wFighterID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eSex is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "ProtoCommon::ESexType") != 0)
	{
		LOG_CRI << "pElemChild is not ProtoCommon::ESexType!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eSex") != 0)
	{
		LOG_CRI << "Attribute: name is not eSex!";
		return false;
	}
	const char* pszVal_eSex = pElemChild->Attribute("value");
	if(pszVal_eSex == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!NProtoCommon::EnumStrToVal(pszVal_eSex, s.eSex))
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
		LOG_CRI << "pElemChild for wMood is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wMood") != 0)
	{
		LOG_CRI << "Attribute: name is not wMood!";
		return false;
	}
	const char* pszVal_wMood = pElemChild->Attribute("value");
	if(pszVal_wMood == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wMood, s.wMood))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strSign is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strSign") != 0)
	{
		LOG_CRI << "Attribute: name is not strSign!";
		return false;
	}
	const char* pszVal_strSign = pElemChild->Attribute("value");
	if(pszVal_strSign == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strSign = pszVal_strSign;
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
		LOG_CRI << "pElemChild for bOnlineStatus is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "bool") != 0)
	{
		LOG_CRI << "pElemChild is not bool!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "bOnlineStatus") != 0)
	{
		LOG_CRI << "Attribute: name is not bOnlineStatus!";
		return false;
	}
	const char* pszVal_bOnlineStatus = pElemChild->Attribute("value");
	if(pszVal_bOnlineStatus == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_bOnlineStatus, s.bOnlineStatus))
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

bool ToXML(const SFriendEntry& s, TiXmlElement& rElement)
{
	rElement.SetValue("SFriendEntry");
	rElement.SetAttribute("type", ToUTF8Ptr("好友条目"));
	unique_ptr<TiXmlElement> pElem_eGroupType(new TiXmlElement("EFriendGroupType"));
	if(pElem_eGroupType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eGroupType->SetAttribute("name", "eGroupType");
	const char* pszEnum_eGroupType = EnumValToStr(s.eGroupType);
	if(pszEnum_eGroupType == NULL)
	{
		LOG_CRI << "EnumValToStr for EFriendGroupType fails!";
		return false;
	}
	pElem_eGroupType->SetAttribute("value", pszEnum_eGroupType);
	pElem_eGroupType->SetAttribute("comment", ToUTF8Ptr("分组ID"));
	if(rElement.LinkEndChild(pElem_eGroupType.get()) != NULL)
		pElem_eGroupType.release();
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
	pElem_strName->SetAttribute("comment", ToUTF8Ptr("名字 XXX: 如果主将改名需要修改此处"));
	if(rElement.LinkEndChild(pElem_strName.get()) != NULL)
		pElem_strName.release();
	unique_ptr<TiXmlElement> pElem_wFighterID(new TiXmlElement("UINT16"));
	if(pElem_wFighterID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wFighterID->SetAttribute("name", "wFighterID");
	pElem_wFighterID->SetAttribute("value", NumberToString(s.wFighterID).c_str());
	pElem_wFighterID->SetAttribute("comment", ToUTF8Ptr("主将ID"));
	if(rElement.LinkEndChild(pElem_wFighterID.get()) != NULL)
		pElem_wFighterID.release();
	unique_ptr<TiXmlElement> pElem_eSex(new TiXmlElement("ProtoCommon::ESexType"));
	if(pElem_eSex == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eSex->SetAttribute("name", "eSex");
	const char* pszEnum_eSex = NProtoCommon::EnumValToStr(s.eSex);
	if(pszEnum_eSex == NULL)
	{
		LOG_CRI << "EnumValToStr for eSex fails!";
		return false;
	}
	pElem_eSex->SetAttribute("value", pszEnum_eSex);
	pElem_eSex->SetAttribute("comment", ToUTF8Ptr("性别"));
	if(rElement.LinkEndChild(pElem_eSex.get()) != NULL)
		pElem_eSex.release();
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
	unique_ptr<TiXmlElement> pElem_byColor(new TiXmlElement("UINT8"));
	if(pElem_byColor == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byColor->SetAttribute("name", "byColor");
	pElem_byColor->SetAttribute("value", NumberToString(s.byColor).c_str());
	pElem_byColor->SetAttribute("comment", ToUTF8Ptr("好友颜色"));
	if(rElement.LinkEndChild(pElem_byColor.get()) != NULL)
		pElem_byColor.release();
	unique_ptr<TiXmlElement> pElem_wMood(new TiXmlElement("UINT16"));
	if(pElem_wMood == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wMood->SetAttribute("name", "wMood");
	pElem_wMood->SetAttribute("value", NumberToString(s.wMood).c_str());
	pElem_wMood->SetAttribute("comment", ToUTF8Ptr("心情表情"));
	if(rElement.LinkEndChild(pElem_wMood.get()) != NULL)
		pElem_wMood.release();
	unique_ptr<TiXmlElement> pElem_strSign(new TiXmlElement("string"));
	if(pElem_strSign == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strSign->SetAttribute("name", "strSign");
	pElem_strSign->SetAttribute("value", s.strSign.c_str());
	pElem_strSign->SetAttribute("comment", ToUTF8Ptr("签名"));
	if(rElement.LinkEndChild(pElem_strSign.get()) != NULL)
		pElem_strSign.release();
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
	unique_ptr<TiXmlElement> pElem_bOnlineStatus(new TiXmlElement("bool"));
	if(pElem_bOnlineStatus == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_bOnlineStatus->SetAttribute("name", "bOnlineStatus");
	pElem_bOnlineStatus->SetAttribute("value", NumberToString(s.bOnlineStatus).c_str());
	pElem_bOnlineStatus->SetAttribute("comment", ToUTF8Ptr("在线状态"));
	if(rElement.LinkEndChild(pElem_bOnlineStatus.get()) != NULL)
		pElem_bOnlineStatus.release();
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

bool VectorFromXML(TiXmlElement& rElement, TVecFriendEntry& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SFriendEntryPtr p(new SFriendEntry);
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

bool VectorToXML(const TVecFriendEntry& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SFriendEntry"));
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

SFriend::SFriend() : wMood(0) { }

SFriend::SFriend(UINT16 wMood_, const std::string& strSign_, const TVecFriendEntry& vecFriendEntry_) : wMood(wMood_), strSign(strSign_), vecFriendEntry(vecFriendEntry_) { }

SFriend::SFriend(SFriend&& src) : wMood(src.wMood), strSign(move(src.strSign)), vecFriendEntry(move(src.vecFriendEntry)) { }

SFriend& SFriend::operator=(SFriend&& rhs)
{
	if(this != &rhs)
	{
		this->~SFriend();
		new (this) SFriend(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SFriend& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.wMood;
	src >> s.strSign;
	src >> s.vecFriendEntry;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SFriend& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.wMood;
	src << s.strSign;
	src << s.vecFriendEntry;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SFriend& s)
{
	if(strcmp(rElement.Value(), "SFriend") != 0)
	{
		LOG_CRI << "rElement is not SFriend!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wMood is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wMood") != 0)
	{
		LOG_CRI << "Attribute: name is not wMood!";
		return false;
	}
	const char* pszVal_wMood = pElemChild->Attribute("value");
	if(pszVal_wMood == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wMood, s.wMood))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strSign is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strSign") != 0)
	{
		LOG_CRI << "Attribute: name is not strSign!";
		return false;
	}
	const char* pszVal_strSign = pElemChild->Attribute("value");
	if(pszVal_strSign == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strSign = pszVal_strSign;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecFriendEntry is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecFriendEntry") != 0)
	{
		LOG_CRI << "pElemChild is not TVecFriendEntry!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecFriendEntry") != 0)
	{
		LOG_CRI << "Attribute: name is not vecFriendEntry!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecFriendEntry))
	{
		LOG_CRI << "VectorFromXML for vecFriendEntry fails!";
		return false;
	}
	return true;
}

bool ToXML(const SFriend& s, TiXmlElement& rElement)
{
	rElement.SetValue("SFriend");
	rElement.SetAttribute("type", ToUTF8Ptr("好友"));
	unique_ptr<TiXmlElement> pElem_wMood(new TiXmlElement("UINT16"));
	if(pElem_wMood == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wMood->SetAttribute("name", "wMood");
	pElem_wMood->SetAttribute("value", NumberToString(s.wMood).c_str());
	pElem_wMood->SetAttribute("comment", ToUTF8Ptr("我的心情表情"));
	if(rElement.LinkEndChild(pElem_wMood.get()) != NULL)
		pElem_wMood.release();
	unique_ptr<TiXmlElement> pElem_strSign(new TiXmlElement("string"));
	if(pElem_strSign == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strSign->SetAttribute("name", "strSign");
	pElem_strSign->SetAttribute("value", s.strSign.c_str());
	pElem_strSign->SetAttribute("comment", ToUTF8Ptr("我的签名"));
	if(rElement.LinkEndChild(pElem_strSign.get()) != NULL)
		pElem_strSign.release();
	unique_ptr<TiXmlElement> pElem_vecFriendEntry(new TiXmlElement("TVecFriendEntry"));
	if(pElem_vecFriendEntry == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecFriendEntry->SetAttribute("name", "vecFriendEntry");
	if(!VectorToXML(s.vecFriendEntry, *pElem_vecFriendEntry))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecFriendEntry->SetAttribute("comment", ToUTF8Ptr("好友列表"));
	if(rElement.LinkEndChild(pElem_vecFriendEntry.get()) != NULL)
		pElem_vecFriendEntry.release();
	return true;
}

#endif

SreferFriend::SreferFriend() : qwUserID(0), byLevel(0), wHeroID(0) { }

SreferFriend::SreferFriend(UINT64 qwUserID_, UINT8 byLevel_, UINT16 wHeroID_, const std::string& strName_) : qwUserID(qwUserID_), byLevel(byLevel_), wHeroID(wHeroID_), strName(strName_) { }

SreferFriend::SreferFriend(SreferFriend&& src) : qwUserID(src.qwUserID), byLevel(src.byLevel), wHeroID(src.wHeroID), strName(move(src.strName)) { }

SreferFriend& SreferFriend::operator=(SreferFriend&& rhs)
{
	if(this != &rhs)
	{
		this->~SreferFriend();
		new (this) SreferFriend(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SreferFriend& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwUserID;
	src >> s.byLevel;
	src >> s.wHeroID;
	src >> s.strName;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SreferFriend& s)
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
	src << s.byLevel;
	src << s.wHeroID;
	src << s.strName;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SreferFriend& s)
{
	if(strcmp(rElement.Value(), "SreferFriend") != 0)
	{
		LOG_CRI << "rElement is not SreferFriend!";
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
		LOG_CRI << "pElemChild for wHeroID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wHeroID") != 0)
	{
		LOG_CRI << "Attribute: name is not wHeroID!";
		return false;
	}
	const char* pszVal_wHeroID = pElemChild->Attribute("value");
	if(pszVal_wHeroID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wHeroID, s.wHeroID))
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
	return true;
}

bool ToXML(const SreferFriend& s, TiXmlElement& rElement)
{
	rElement.SetValue("SreferFriend");
	rElement.SetAttribute("type", ToUTF8Ptr("推荐好友"));
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
	unique_ptr<TiXmlElement> pElem_wHeroID(new TiXmlElement("UINT16"));
	if(pElem_wHeroID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wHeroID->SetAttribute("name", "wHeroID");
	pElem_wHeroID->SetAttribute("value", NumberToString(s.wHeroID).c_str());
	pElem_wHeroID->SetAttribute("comment", ToUTF8Ptr("主将ID"));
	if(rElement.LinkEndChild(pElem_wHeroID.get()) != NULL)
		pElem_wHeroID.release();
	unique_ptr<TiXmlElement> pElem_strName(new TiXmlElement("string"));
	if(pElem_strName == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strName->SetAttribute("name", "strName");
	pElem_strName->SetAttribute("value", s.strName.c_str());
	pElem_strName->SetAttribute("comment", ToUTF8Ptr("用户名称"));
	if(rElement.LinkEndChild(pElem_strName.get()) != NULL)
		pElem_strName.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecReferFriend& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SreferFriend s;
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

bool VectorToXML(const TVecReferFriend& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SreferFriend"));
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

} //namespace NFriendProt
