/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    GlobalChatProt.cpp
//  Purpose:      全局聊天协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "GlobalChatProt.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NGlobalChatProt
{

#ifdef PROT_USE_XML

const char* EnumValToStr(EChatShowResult e)
{
	switch(e)
	{
	case eChatShowSucceed:
		return "eChatShowSucceed";
	case eChatShowNotExist:
		return "eChatShowNotExist";
	case eChatShowErrOther:
		return "eChatShowErrOther";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EChatShowResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EChatShowResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eChatShowSucceed", eChatShowSucceed));
		mapStr2Val.insert(make_pair("eChatShowNotExist", eChatShowNotExist));
		mapStr2Val.insert(make_pair("eChatShowErrOther", eChatShowErrOther));
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

const char* EnumValToStr(EChannelType e)
{
	switch(e)
	{
	case eChannelNone:
		return "eChannelNone";
	case eChannelAll:
		return "eChannelAll";
	case eChannelWorld:
		return "eChannelWorld";
	case eChannelGuild:
		return "eChannelGuild";
	case eChannelSys:
		return "eChannelSys";
	case eChannelTeam:
		return "eChannelTeam";
	case eChannelNoLabelSys:
		return "eChannelNoLabelSys";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EChannelType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EChannelType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eChannelNone", eChannelNone));
		mapStr2Val.insert(make_pair("eChannelAll", eChannelAll));
		mapStr2Val.insert(make_pair("eChannelWorld", eChannelWorld));
		mapStr2Val.insert(make_pair("eChannelGuild", eChannelGuild));
		mapStr2Val.insert(make_pair("eChannelSys", eChannelSys));
		mapStr2Val.insert(make_pair("eChannelTeam", eChannelTeam));
		mapStr2Val.insert(make_pair("eChannelNoLabelSys", eChannelNoLabelSys));
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

const char* EnumValToStr(EChannelSubType e)
{
	switch(e)
	{
	case eSubNone:
		return "eSubNone";
	case eSubBulletin:
		return "eSubBulletin";
	case eSubBroadcast:
		return "eSubBroadcast";
	case eSubHorn:
		return "eSubHorn";
	case eSubSuspension:
		return "eSubSuspension";
	case eSubPrompt:
		return "eSubPrompt";
	case eSubEnd:
		return "eSubEnd";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EChannelSubType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EChannelSubType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eSubNone", eSubNone));
		mapStr2Val.insert(make_pair("eSubBulletin", eSubBulletin));
		mapStr2Val.insert(make_pair("eSubBroadcast", eSubBroadcast));
		mapStr2Val.insert(make_pair("eSubHorn", eSubHorn));
		mapStr2Val.insert(make_pair("eSubSuspension", eSubSuspension));
		mapStr2Val.insert(make_pair("eSubPrompt", eSubPrompt));
		mapStr2Val.insert(make_pair("eSubEnd", eSubEnd));
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

const char* EnumValToStr(EChatShowType e)
{
	switch(e)
	{
	case eShowItem:
		return "eShowItem";
	case eShowRole:
		return "eShowRole";
	case eShowPet:
		return "eShowPet";
	case eShowHorse:
		return "eShowHorse";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EChatShowType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EChatShowType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eShowItem", eShowItem));
		mapStr2Val.insert(make_pair("eShowRole", eShowRole));
		mapStr2Val.insert(make_pair("eShowPet", eShowPet));
		mapStr2Val.insert(make_pair("eShowHorse", eShowHorse));
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

const char* EnumValToStr(EWhisperErrorType e)
{
	switch(e)
	{
	case eWhisperTooFastErr:
		return "eWhisperTooFastErr";
	case eWhisperOfflineErr:
		return "eWhisperOfflineErr";
	case eWhisperLengthErr:
		return "eWhisperLengthErr";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EWhisperErrorType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EWhisperErrorType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eWhisperTooFastErr", eWhisperTooFastErr));
		mapStr2Val.insert(make_pair("eWhisperOfflineErr", eWhisperOfflineErr));
		mapStr2Val.insert(make_pair("eWhisperLengthErr", eWhisperLengthErr));
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

const char* EnumValToStr(ESShowInfoType e)
{
	switch(e)
	{
	case eFlauntGood:
		return "eFlauntGood";
	case eFlauntHero:
		return "eFlauntHero";
	case eFlauntPet:
		return "eFlauntPet";
	case eFlauntHorse:
		return "eFlauntHorse";
	case eShowAchievement:
		return "eShowAchievement";
	case eFlauntFashion:
		return "eFlauntFashion";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, ESShowInfoType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, ESShowInfoType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eFlauntGood", eFlauntGood));
		mapStr2Val.insert(make_pair("eFlauntHero", eFlauntHero));
		mapStr2Val.insert(make_pair("eFlauntPet", eFlauntPet));
		mapStr2Val.insert(make_pair("eFlauntHorse", eFlauntHorse));
		mapStr2Val.insert(make_pair("eShowAchievement", eShowAchievement));
		mapStr2Val.insert(make_pair("eFlauntFashion", eFlauntFashion));
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

SSenderInfo::SSenderInfo() : byVIPType(0), qwUsrID(0), byQuality(0), byNation(0) { }

SSenderInfo::SSenderInfo(UINT8 byVIPType_, UINT64 qwUsrID_, const std::string& strName_, const std::string& strGuildName_, UINT8 byQuality_, 
			UINT8 byNation_, const NProtoCommon::TVecPlatformParam& vecPlatforms_)
			: byVIPType(byVIPType_), qwUsrID(qwUsrID_), strName(strName_), strGuildName(strGuildName_), byQuality(byQuality_), 
			byNation(byNation_), vecPlatforms(vecPlatforms_) { }

SSenderInfo::SSenderInfo(SSenderInfo&& src) : byVIPType(src.byVIPType), qwUsrID(src.qwUsrID), strName(move(src.strName)), strGuildName(move(src.strGuildName)), byQuality(src.byQuality), 
			byNation(src.byNation), vecPlatforms(move(src.vecPlatforms)) { }

SSenderInfo& SSenderInfo::operator=(SSenderInfo&& rhs)
{
	if(this != &rhs)
	{
		this->~SSenderInfo();
		new (this) SSenderInfo(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SSenderInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.byVIPType;
	src >> s.qwUsrID;
	src >> s.strName;
	src >> s.strGuildName;
	src >> s.byQuality;
	src >> s.byNation;
	src >> s.vecPlatforms;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SSenderInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.byVIPType;
	src << s.qwUsrID;
	src << s.strName;
	src << s.strGuildName;
	src << s.byQuality;
	src << s.byNation;
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

bool FromXML(TiXmlElement& rElement, SSenderInfo& s)
{
	if(strcmp(rElement.Value(), "SSenderInfo") != 0)
	{
		LOG_CRI << "rElement is not SSenderInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byVIPType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byVIPType") != 0)
	{
		LOG_CRI << "Attribute: name is not byVIPType!";
		return false;
	}
	const char* pszVal_byVIPType = pElemChild->Attribute("value");
	if(pszVal_byVIPType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byVIPType, s.byVIPType))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwUsrID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwUsrID") != 0)
	{
		LOG_CRI << "Attribute: name is not qwUsrID!";
		return false;
	}
	const char* pszVal_qwUsrID = pElemChild->Attribute("value");
	if(pszVal_qwUsrID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwUsrID, s.qwUsrID))
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
		LOG_CRI << "pElemChild for strGuildName is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strGuildName") != 0)
	{
		LOG_CRI << "Attribute: name is not strGuildName!";
		return false;
	}
	const char* pszVal_strGuildName = pElemChild->Attribute("value");
	if(pszVal_strGuildName == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strGuildName = pszVal_strGuildName;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byQuality is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byQuality") != 0)
	{
		LOG_CRI << "Attribute: name is not byQuality!";
		return false;
	}
	const char* pszVal_byQuality = pElemChild->Attribute("value");
	if(pszVal_byQuality == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byQuality, s.byQuality))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byNation is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byNation") != 0)
	{
		LOG_CRI << "Attribute: name is not byNation!";
		return false;
	}
	const char* pszVal_byNation = pElemChild->Attribute("value");
	if(pszVal_byNation == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byNation, s.byNation))
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

bool ToXML(const SSenderInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SSenderInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("发送者信息"));
	unique_ptr<TiXmlElement> pElem_byVIPType(new TiXmlElement("UINT8"));
	if(pElem_byVIPType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byVIPType->SetAttribute("name", "byVIPType");
	pElem_byVIPType->SetAttribute("value", NumberToString(s.byVIPType).c_str());
	pElem_byVIPType->SetAttribute("comment", ToUTF8Ptr("VIP特权类型"));
	if(rElement.LinkEndChild(pElem_byVIPType.get()) != NULL)
		pElem_byVIPType.release();
	unique_ptr<TiXmlElement> pElem_qwUsrID(new TiXmlElement("UINT64"));
	if(pElem_qwUsrID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwUsrID->SetAttribute("name", "qwUsrID");
	pElem_qwUsrID->SetAttribute("value", NumberToString(s.qwUsrID).c_str());
	pElem_qwUsrID->SetAttribute("comment", ToUTF8Ptr("帐号ID"));
	if(rElement.LinkEndChild(pElem_qwUsrID.get()) != NULL)
		pElem_qwUsrID.release();
	unique_ptr<TiXmlElement> pElem_strName(new TiXmlElement("string"));
	if(pElem_strName == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strName->SetAttribute("name", "strName");
	pElem_strName->SetAttribute("value", s.strName.c_str());
	pElem_strName->SetAttribute("comment", ToUTF8Ptr("发送者名"));
	if(rElement.LinkEndChild(pElem_strName.get()) != NULL)
		pElem_strName.release();
	unique_ptr<TiXmlElement> pElem_strGuildName(new TiXmlElement("string"));
	if(pElem_strGuildName == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strGuildName->SetAttribute("name", "strGuildName");
	pElem_strGuildName->SetAttribute("value", s.strGuildName.c_str());
	pElem_strGuildName->SetAttribute("comment", ToUTF8Ptr("帮派名称"));
	if(rElement.LinkEndChild(pElem_strGuildName.get()) != NULL)
		pElem_strGuildName.release();
	unique_ptr<TiXmlElement> pElem_byQuality(new TiXmlElement("UINT8"));
	if(pElem_byQuality == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byQuality->SetAttribute("name", "byQuality");
	pElem_byQuality->SetAttribute("value", NumberToString(s.byQuality).c_str());
	pElem_byQuality->SetAttribute("comment", ToUTF8Ptr("玩家品质（颜色）"));
	if(rElement.LinkEndChild(pElem_byQuality.get()) != NULL)
		pElem_byQuality.release();
	unique_ptr<TiXmlElement> pElem_byNation(new TiXmlElement("UINT8"));
	if(pElem_byNation == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byNation->SetAttribute("name", "byNation");
	pElem_byNation->SetAttribute("value", NumberToString(s.byNation).c_str());
	pElem_byNation->SetAttribute("comment", ToUTF8Ptr("发送者国家"));
	if(rElement.LinkEndChild(pElem_byNation.get()) != NULL)
		pElem_byNation.release();
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
	pElem_vecPlatforms->SetAttribute("comment", ToUTF8Ptr("平台相关参数"));
	if(rElement.LinkEndChild(pElem_vecPlatforms.get()) != NULL)
		pElem_vecPlatforms.release();
	return true;
}

#endif

SShowInfo::SShowInfo() : qwInstID(0) { }

SShowInfo::SShowInfo(UINT64 qwInstID_, const std::string& strShowInfo_) : qwInstID(qwInstID_), strShowInfo(strShowInfo_) { }

SShowInfo::SShowInfo(SShowInfo&& src) : qwInstID(src.qwInstID), strShowInfo(move(src.strShowInfo)) { }

SShowInfo& SShowInfo::operator=(SShowInfo&& rhs)
{
	if(this != &rhs)
	{
		this->~SShowInfo();
		new (this) SShowInfo(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SShowInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwInstID;
	src >> s.strShowInfo;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SShowInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.qwInstID;
	src << s.strShowInfo;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SShowInfo& s)
{
	if(strcmp(rElement.Value(), "SShowInfo") != 0)
	{
		LOG_CRI << "rElement is not SShowInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwInstID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwInstID") != 0)
	{
		LOG_CRI << "Attribute: name is not qwInstID!";
		return false;
	}
	const char* pszVal_qwInstID = pElemChild->Attribute("value");
	if(pszVal_qwInstID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwInstID, s.qwInstID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strShowInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strShowInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not strShowInfo!";
		return false;
	}
	const char* pszVal_strShowInfo = pElemChild->Attribute("value");
	if(pszVal_strShowInfo == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strShowInfo = pszVal_strShowInfo;
	return true;
}

bool ToXML(const SShowInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SShowInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("炫耀信息"));
	unique_ptr<TiXmlElement> pElem_qwInstID(new TiXmlElement("UINT64"));
	if(pElem_qwInstID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwInstID->SetAttribute("name", "qwInstID");
	pElem_qwInstID->SetAttribute("value", NumberToString(s.qwInstID).c_str());
	pElem_qwInstID->SetAttribute("comment", ToUTF8Ptr("唯一ID"));
	if(rElement.LinkEndChild(pElem_qwInstID.get()) != NULL)
		pElem_qwInstID.release();
	unique_ptr<TiXmlElement> pElem_strShowInfo(new TiXmlElement("string"));
	if(pElem_strShowInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strShowInfo->SetAttribute("name", "strShowInfo");
	pElem_strShowInfo->SetAttribute("value", s.strShowInfo.c_str());
	pElem_strShowInfo->SetAttribute("comment", ToUTF8Ptr("展示信息序列化"));
	if(rElement.LinkEndChild(pElem_strShowInfo.get()) != NULL)
		pElem_strShowInfo.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecShowInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SShowInfo s;
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

bool VectorToXML(const TVecShowInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SShowInfo"));
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

SWhisperInfo::SWhisperInfo() : qwUserID(0), byVIPType(0), wFighterID(0), eSex((NProtoCommon::ESexType)0), byLevel(0), 
			wMood(0), byQuality(0) { }

SWhisperInfo::SWhisperInfo(SWhisperInfo&& src) : qwUserID(src.qwUserID), strName(move(src.strName)), byVIPType(src.byVIPType), strGuildName(move(src.strGuildName)), vecPlatforms(move(src.vecPlatforms)), 
			wFighterID(src.wFighterID), eSex(src.eSex), byLevel(src.byLevel), wMood(src.wMood), strSign(move(src.strSign)), 
			byQuality(src.byQuality) { }

SWhisperInfo& SWhisperInfo::operator=(SWhisperInfo&& rhs)
{
	if(this != &rhs)
	{
		this->~SWhisperInfo();
		new (this) SWhisperInfo(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SWhisperInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwUserID;
	src >> s.strName;
	src >> s.byVIPType;
	src >> s.strGuildName;
	src >> s.vecPlatforms;
	src >> s.wFighterID;
	src >> (UINT8&)s.eSex;
	src >> s.byLevel;
	src >> s.wMood;
	src >> s.strSign;
	src >> s.byQuality;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SWhisperInfo& s)
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
	src << s.byVIPType;
	src << s.strGuildName;
	src << s.vecPlatforms;
	src << s.wFighterID;
	src << (UINT8&)s.eSex;
	src << s.byLevel;
	src << s.wMood;
	src << s.strSign;
	src << s.byQuality;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SWhisperInfo& s)
{
	if(strcmp(rElement.Value(), "SWhisperInfo") != 0)
	{
		LOG_CRI << "rElement is not SWhisperInfo!";
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
		LOG_CRI << "pElemChild for byVIPType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byVIPType") != 0)
	{
		LOG_CRI << "Attribute: name is not byVIPType!";
		return false;
	}
	const char* pszVal_byVIPType = pElemChild->Attribute("value");
	if(pszVal_byVIPType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byVIPType, s.byVIPType))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strGuildName is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strGuildName") != 0)
	{
		LOG_CRI << "Attribute: name is not strGuildName!";
		return false;
	}
	const char* pszVal_strGuildName = pElemChild->Attribute("value");
	if(pszVal_strGuildName == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strGuildName = pszVal_strGuildName;
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
		LOG_CRI << "pElemChild for byQuality is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byQuality") != 0)
	{
		LOG_CRI << "Attribute: name is not byQuality!";
		return false;
	}
	const char* pszVal_byQuality = pElemChild->Attribute("value");
	if(pszVal_byQuality == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byQuality, s.byQuality))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SWhisperInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SWhisperInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("私聊对方信息"));
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
	unique_ptr<TiXmlElement> pElem_byVIPType(new TiXmlElement("UINT8"));
	if(pElem_byVIPType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byVIPType->SetAttribute("name", "byVIPType");
	pElem_byVIPType->SetAttribute("value", NumberToString(s.byVIPType).c_str());
	pElem_byVIPType->SetAttribute("comment", ToUTF8Ptr("VIP特权类型"));
	if(rElement.LinkEndChild(pElem_byVIPType.get()) != NULL)
		pElem_byVIPType.release();
	unique_ptr<TiXmlElement> pElem_strGuildName(new TiXmlElement("string"));
	if(pElem_strGuildName == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strGuildName->SetAttribute("name", "strGuildName");
	pElem_strGuildName->SetAttribute("value", s.strGuildName.c_str());
	pElem_strGuildName->SetAttribute("comment", ToUTF8Ptr("帮派名称"));
	if(rElement.LinkEndChild(pElem_strGuildName.get()) != NULL)
		pElem_strGuildName.release();
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
	pElem_vecPlatforms->SetAttribute("comment", ToUTF8Ptr("平台相关参数"));
	if(rElement.LinkEndChild(pElem_vecPlatforms.get()) != NULL)
		pElem_vecPlatforms.release();
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
	unique_ptr<TiXmlElement> pElem_byQuality(new TiXmlElement("UINT8"));
	if(pElem_byQuality == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byQuality->SetAttribute("name", "byQuality");
	pElem_byQuality->SetAttribute("value", NumberToString(s.byQuality).c_str());
	pElem_byQuality->SetAttribute("comment", ToUTF8Ptr("品质"));
	if(rElement.LinkEndChild(pElem_byQuality.get()) != NULL)
		pElem_byQuality.release();
	return true;
}

#endif

SFlauntSkill::SFlauntSkill() : byIdx(0), dwSkillID(0) { }

SFlauntSkill::SFlauntSkill(UINT8 byIdx_, UINT32 dwSkillID_) : byIdx(byIdx_), dwSkillID(dwSkillID_) { }

CInArchive& operator>>(CInArchive& src, SFlauntSkill& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.byIdx;
	src >> s.dwSkillID;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SFlauntSkill& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.byIdx;
	src << s.dwSkillID;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SFlauntSkill& s)
{
	if(strcmp(rElement.Value(), "SFlauntSkill") != 0)
	{
		LOG_CRI << "rElement is not SFlauntSkill!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byIdx is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byIdx") != 0)
	{
		LOG_CRI << "Attribute: name is not byIdx!";
		return false;
	}
	const char* pszVal_byIdx = pElemChild->Attribute("value");
	if(pszVal_byIdx == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byIdx, s.byIdx))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwSkillID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwSkillID") != 0)
	{
		LOG_CRI << "Attribute: name is not dwSkillID!";
		return false;
	}
	const char* pszVal_dwSkillID = pElemChild->Attribute("value");
	if(pszVal_dwSkillID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwSkillID, s.dwSkillID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SFlauntSkill& s, TiXmlElement& rElement)
{
	rElement.SetValue("SFlauntSkill");
	rElement.SetAttribute("type", ToUTF8Ptr("炫耀参与战斗的技能信息"));
	unique_ptr<TiXmlElement> pElem_byIdx(new TiXmlElement("UINT8"));
	if(pElem_byIdx == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byIdx->SetAttribute("name", "byIdx");
	pElem_byIdx->SetAttribute("value", NumberToString(s.byIdx).c_str());
	pElem_byIdx->SetAttribute("comment", ToUTF8Ptr("技能槽idx"));
	if(rElement.LinkEndChild(pElem_byIdx.get()) != NULL)
		pElem_byIdx.release();
	unique_ptr<TiXmlElement> pElem_dwSkillID(new TiXmlElement("UINT32"));
	if(pElem_dwSkillID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwSkillID->SetAttribute("name", "dwSkillID");
	pElem_dwSkillID->SetAttribute("value", NumberToString(s.dwSkillID).c_str());
	pElem_dwSkillID->SetAttribute("comment", ToUTF8Ptr("技能ID"));
	if(rElement.LinkEndChild(pElem_dwSkillID.get()) != NULL)
		pElem_dwSkillID.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecFlauntSkill& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SFlauntSkill s;
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

bool VectorToXML(const TVecFlauntSkill& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SFlauntSkill"));
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

SFlauntEquip::SFlauntEquip() : wEquipID(0), byStrengthenLevel(0), byPos(0) { }

SFlauntEquip::SFlauntEquip(UINT16 wEquipID_, UINT8 byStrengthenLevel_, UINT8 byPos_) : wEquipID(wEquipID_), byStrengthenLevel(byStrengthenLevel_), byPos(byPos_) { }

CInArchive& operator>>(CInArchive& src, SFlauntEquip& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.wEquipID;
	src >> s.byStrengthenLevel;
	src >> s.byPos;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SFlauntEquip& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.wEquipID;
	src << s.byStrengthenLevel;
	src << s.byPos;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SFlauntEquip& s)
{
	if(strcmp(rElement.Value(), "SFlauntEquip") != 0)
	{
		LOG_CRI << "rElement is not SFlauntEquip!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wEquipID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wEquipID") != 0)
	{
		LOG_CRI << "Attribute: name is not wEquipID!";
		return false;
	}
	const char* pszVal_wEquipID = pElemChild->Attribute("value");
	if(pszVal_wEquipID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wEquipID, s.wEquipID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byStrengthenLevel is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byStrengthenLevel") != 0)
	{
		LOG_CRI << "Attribute: name is not byStrengthenLevel!";
		return false;
	}
	const char* pszVal_byStrengthenLevel = pElemChild->Attribute("value");
	if(pszVal_byStrengthenLevel == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byStrengthenLevel, s.byStrengthenLevel))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byPos is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byPos") != 0)
	{
		LOG_CRI << "Attribute: name is not byPos!";
		return false;
	}
	const char* pszVal_byPos = pElemChild->Attribute("value");
	if(pszVal_byPos == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byPos, s.byPos))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SFlauntEquip& s, TiXmlElement& rElement)
{
	rElement.SetValue("SFlauntEquip");
	rElement.SetAttribute("type", ToUTF8Ptr("炫耀装备信息"));
	unique_ptr<TiXmlElement> pElem_wEquipID(new TiXmlElement("UINT16"));
	if(pElem_wEquipID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wEquipID->SetAttribute("name", "wEquipID");
	pElem_wEquipID->SetAttribute("value", NumberToString(s.wEquipID).c_str());
	pElem_wEquipID->SetAttribute("comment", ToUTF8Ptr("装备TypeID"));
	if(rElement.LinkEndChild(pElem_wEquipID.get()) != NULL)
		pElem_wEquipID.release();
	unique_ptr<TiXmlElement> pElem_byStrengthenLevel(new TiXmlElement("UINT8"));
	if(pElem_byStrengthenLevel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byStrengthenLevel->SetAttribute("name", "byStrengthenLevel");
	pElem_byStrengthenLevel->SetAttribute("value", NumberToString(s.byStrengthenLevel).c_str());
	pElem_byStrengthenLevel->SetAttribute("comment", ToUTF8Ptr("强化等级"));
	if(rElement.LinkEndChild(pElem_byStrengthenLevel.get()) != NULL)
		pElem_byStrengthenLevel.release();
	unique_ptr<TiXmlElement> pElem_byPos(new TiXmlElement("UINT8"));
	if(pElem_byPos == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byPos->SetAttribute("name", "byPos");
	pElem_byPos->SetAttribute("value", NumberToString(s.byPos).c_str());
	pElem_byPos->SetAttribute("comment", ToUTF8Ptr("装备位置"));
	if(rElement.LinkEndChild(pElem_byPos.get()) != NULL)
		pElem_byPos.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecFlauntEquip& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SFlauntEquip s;
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

bool VectorToXML(const TVecFlauntEquip& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SFlauntEquip"));
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

SFlauntHero::SFlauntHero() : qwInstID(0), wFighterID(0), byLevel(0), byQuilty(0), dwPower(0), 
			byDujieLevel(0), byLianPi(0), byTongJin(0), byQiangJi(0), byDuanGu(0), 
			byHuoLuo(0), byXiSui(0) { }

SFlauntHero::SFlauntHero(SFlauntHero&& src) : strName(move(src.strName)), qwInstID(src.qwInstID), wFighterID(src.wFighterID), byLevel(src.byLevel), byQuilty(src.byQuilty), 
			dwPower(src.dwPower), oAttrVec(move(src.oAttrVec)), byDujieLevel(src.byDujieLevel), vActiveSkill(move(src.vActiveSkill)), vPassiveSkill(move(src.vPassiveSkill)), 
			sPeerLessSkill(src.sPeerLessSkill), vecFlauntEquip(move(src.vecFlauntEquip)), byLianPi(src.byLianPi), byTongJin(src.byTongJin), byQiangJi(src.byQiangJi), 
			byDuanGu(src.byDuanGu), byHuoLuo(src.byHuoLuo), byXiSui(src.byXiSui) { }

SFlauntHero& SFlauntHero::operator=(SFlauntHero&& rhs)
{
	if(this != &rhs)
	{
		this->~SFlauntHero();
		new (this) SFlauntHero(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SFlauntHero& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.strName;
	src >> s.qwInstID;
	src >> s.wFighterID;
	src >> s.byLevel;
	src >> s.byQuilty;
	src >> s.dwPower;
	src >> s.oAttrVec;
	src >> s.byDujieLevel;
	src >> s.vActiveSkill;
	src >> s.vPassiveSkill;
	src >> s.sPeerLessSkill;
	src >> s.vecFlauntEquip;
	src >> s.byLianPi;
	src >> s.byTongJin;
	src >> s.byQiangJi;
	src >> s.byDuanGu;
	src >> s.byHuoLuo;
	src >> s.byXiSui;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SFlauntHero& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.strName;
	src << s.qwInstID;
	src << s.wFighterID;
	src << s.byLevel;
	src << s.byQuilty;
	src << s.dwPower;
	src << s.oAttrVec;
	src << s.byDujieLevel;
	src << s.vActiveSkill;
	src << s.vPassiveSkill;
	src << s.sPeerLessSkill;
	src << s.vecFlauntEquip;
	src << s.byLianPi;
	src << s.byTongJin;
	src << s.byQiangJi;
	src << s.byDuanGu;
	src << s.byHuoLuo;
	src << s.byXiSui;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SFlauntHero& s)
{
	if(strcmp(rElement.Value(), "SFlauntHero") != 0)
	{
		LOG_CRI << "rElement is not SFlauntHero!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
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
		LOG_CRI << "pElemChild for qwInstID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwInstID") != 0)
	{
		LOG_CRI << "Attribute: name is not qwInstID!";
		return false;
	}
	const char* pszVal_qwInstID = pElemChild->Attribute("value");
	if(pszVal_qwInstID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwInstID, s.qwInstID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
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
		LOG_CRI << "pElemChild for byQuilty is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byQuilty") != 0)
	{
		LOG_CRI << "Attribute: name is not byQuilty!";
		return false;
	}
	const char* pszVal_byQuilty = pElemChild->Attribute("value");
	if(pszVal_byQuilty == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byQuilty, s.byQuilty))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwPower is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwPower") != 0)
	{
		LOG_CRI << "Attribute: name is not dwPower!";
		return false;
	}
	const char* pszVal_dwPower = pElemChild->Attribute("value");
	if(pszVal_dwPower == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwPower, s.dwPower))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for oAttrVec is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "ProtoCommon::TVecFtAttrMod") != 0)
	{
		LOG_CRI << "pElemChild is not ProtoCommon::TVecFtAttrMod!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "oAttrVec") != 0)
	{
		LOG_CRI << "Attribute: name is not oAttrVec!";
		return false;
	}
	if(!NProtoCommon::VectorFromXML(*pElemChild, s.oAttrVec))
	{
		LOG_CRI << "VectorFromXML for oAttrVec fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byDujieLevel is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byDujieLevel") != 0)
	{
		LOG_CRI << "Attribute: name is not byDujieLevel!";
		return false;
	}
	const char* pszVal_byDujieLevel = pElemChild->Attribute("value");
	if(pszVal_byDujieLevel == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byDujieLevel, s.byDujieLevel))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vActiveSkill is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecFlauntSkill") != 0)
	{
		LOG_CRI << "pElemChild is not TVecFlauntSkill!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vActiveSkill") != 0)
	{
		LOG_CRI << "Attribute: name is not vActiveSkill!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vActiveSkill))
	{
		LOG_CRI << "VectorFromXML for vActiveSkill fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vPassiveSkill is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecFlauntSkill") != 0)
	{
		LOG_CRI << "pElemChild is not TVecFlauntSkill!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vPassiveSkill") != 0)
	{
		LOG_CRI << "Attribute: name is not vPassiveSkill!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vPassiveSkill))
	{
		LOG_CRI << "VectorFromXML for vPassiveSkill fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for sPeerLessSkill is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "SFlauntSkill") != 0)
	{
		LOG_CRI << "pElemChild is not SFlauntSkill!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "sPeerLessSkill") != 0)
	{
		LOG_CRI << "Attribute: name is not sPeerLessSkill!";
		return false;
	}
	if(!FromXML(*pElemChild, s.sPeerLessSkill))
	{
		LOG_CRI << "FromXML for: sPeerLessSkill fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecFlauntEquip is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecFlauntEquip") != 0)
	{
		LOG_CRI << "pElemChild is not TVecFlauntEquip!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecFlauntEquip") != 0)
	{
		LOG_CRI << "Attribute: name is not vecFlauntEquip!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecFlauntEquip))
	{
		LOG_CRI << "VectorFromXML for vecFlauntEquip fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byLianPi is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byLianPi") != 0)
	{
		LOG_CRI << "Attribute: name is not byLianPi!";
		return false;
	}
	const char* pszVal_byLianPi = pElemChild->Attribute("value");
	if(pszVal_byLianPi == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byLianPi, s.byLianPi))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byTongJin is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byTongJin") != 0)
	{
		LOG_CRI << "Attribute: name is not byTongJin!";
		return false;
	}
	const char* pszVal_byTongJin = pElemChild->Attribute("value");
	if(pszVal_byTongJin == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byTongJin, s.byTongJin))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byQiangJi is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byQiangJi") != 0)
	{
		LOG_CRI << "Attribute: name is not byQiangJi!";
		return false;
	}
	const char* pszVal_byQiangJi = pElemChild->Attribute("value");
	if(pszVal_byQiangJi == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byQiangJi, s.byQiangJi))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byDuanGu is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byDuanGu") != 0)
	{
		LOG_CRI << "Attribute: name is not byDuanGu!";
		return false;
	}
	const char* pszVal_byDuanGu = pElemChild->Attribute("value");
	if(pszVal_byDuanGu == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byDuanGu, s.byDuanGu))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byHuoLuo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byHuoLuo") != 0)
	{
		LOG_CRI << "Attribute: name is not byHuoLuo!";
		return false;
	}
	const char* pszVal_byHuoLuo = pElemChild->Attribute("value");
	if(pszVal_byHuoLuo == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byHuoLuo, s.byHuoLuo))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byXiSui is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byXiSui") != 0)
	{
		LOG_CRI << "Attribute: name is not byXiSui!";
		return false;
	}
	const char* pszVal_byXiSui = pElemChild->Attribute("value");
	if(pszVal_byXiSui == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byXiSui, s.byXiSui))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SFlauntHero& s, TiXmlElement& rElement)
{
	rElement.SetValue("SFlauntHero");
	rElement.SetAttribute("type", ToUTF8Ptr("散仙炫耀信息"));
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
	unique_ptr<TiXmlElement> pElem_qwInstID(new TiXmlElement("UINT64"));
	if(pElem_qwInstID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwInstID->SetAttribute("name", "qwInstID");
	pElem_qwInstID->SetAttribute("value", NumberToString(s.qwInstID).c_str());
	pElem_qwInstID->SetAttribute("comment", ToUTF8Ptr("散仙唯一ID"));
	if(rElement.LinkEndChild(pElem_qwInstID.get()) != NULL)
		pElem_qwInstID.release();
	unique_ptr<TiXmlElement> pElem_wFighterID(new TiXmlElement("UINT16"));
	if(pElem_wFighterID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wFighterID->SetAttribute("name", "wFighterID");
	pElem_wFighterID->SetAttribute("value", NumberToString(s.wFighterID).c_str());
	pElem_wFighterID->SetAttribute("comment", ToUTF8Ptr("散仙ID"));
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
	unique_ptr<TiXmlElement> pElem_byQuilty(new TiXmlElement("UINT8"));
	if(pElem_byQuilty == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byQuilty->SetAttribute("name", "byQuilty");
	pElem_byQuilty->SetAttribute("value", NumberToString(s.byQuilty).c_str());
	pElem_byQuilty->SetAttribute("comment", ToUTF8Ptr("品质 0,1,2,3,4,5,6【黑白绿蓝紫黄橙】"));
	if(rElement.LinkEndChild(pElem_byQuilty.get()) != NULL)
		pElem_byQuilty.release();
	unique_ptr<TiXmlElement> pElem_dwPower(new TiXmlElement("UINT32"));
	if(pElem_dwPower == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwPower->SetAttribute("name", "dwPower");
	pElem_dwPower->SetAttribute("value", NumberToString(s.dwPower).c_str());
	pElem_dwPower->SetAttribute("comment", ToUTF8Ptr("散仙战斗力"));
	if(rElement.LinkEndChild(pElem_dwPower.get()) != NULL)
		pElem_dwPower.release();
	unique_ptr<TiXmlElement> pElem_oAttrVec(new TiXmlElement("ProtoCommon::TVecFtAttrMod"));
	if(pElem_oAttrVec == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_oAttrVec->SetAttribute("name", "oAttrVec");
	if(!NProtoCommon::VectorToXML(s.oAttrVec, *pElem_oAttrVec))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_oAttrVec->SetAttribute("comment", ToUTF8Ptr("最终属性"));
	if(rElement.LinkEndChild(pElem_oAttrVec.get()) != NULL)
		pElem_oAttrVec.release();
	unique_ptr<TiXmlElement> pElem_byDujieLevel(new TiXmlElement("UINT8"));
	if(pElem_byDujieLevel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byDujieLevel->SetAttribute("name", "byDujieLevel");
	pElem_byDujieLevel->SetAttribute("value", NumberToString(s.byDujieLevel).c_str());
	pElem_byDujieLevel->SetAttribute("comment", ToUTF8Ptr("散仙渡劫等级"));
	if(rElement.LinkEndChild(pElem_byDujieLevel.get()) != NULL)
		pElem_byDujieLevel.release();
	unique_ptr<TiXmlElement> pElem_vActiveSkill(new TiXmlElement("TVecFlauntSkill"));
	if(pElem_vActiveSkill == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vActiveSkill->SetAttribute("name", "vActiveSkill");
	if(!VectorToXML(s.vActiveSkill, *pElem_vActiveSkill))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vActiveSkill->SetAttribute("comment", ToUTF8Ptr("主动技能"));
	if(rElement.LinkEndChild(pElem_vActiveSkill.get()) != NULL)
		pElem_vActiveSkill.release();
	unique_ptr<TiXmlElement> pElem_vPassiveSkill(new TiXmlElement("TVecFlauntSkill"));
	if(pElem_vPassiveSkill == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vPassiveSkill->SetAttribute("name", "vPassiveSkill");
	if(!VectorToXML(s.vPassiveSkill, *pElem_vPassiveSkill))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vPassiveSkill->SetAttribute("comment", ToUTF8Ptr("被动技能"));
	if(rElement.LinkEndChild(pElem_vPassiveSkill.get()) != NULL)
		pElem_vPassiveSkill.release();
	unique_ptr<TiXmlElement> pElem_sPeerLessSkill(new TiXmlElement("SFlauntSkill"));
	if(pElem_sPeerLessSkill == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_sPeerLessSkill->SetAttribute("name", "sPeerLessSkill");
	if(!ToXML(s.sPeerLessSkill, *pElem_sPeerLessSkill))
	{
		LOG_CRI << "sPeerLessSkill ToXML fails!";
		return false;
	}
	pElem_sPeerLessSkill->SetAttribute("comment", ToUTF8Ptr("无双技能"));
	if(rElement.LinkEndChild(pElem_sPeerLessSkill.get()) != NULL)
		pElem_sPeerLessSkill.release();
	unique_ptr<TiXmlElement> pElem_vecFlauntEquip(new TiXmlElement("TVecFlauntEquip"));
	if(pElem_vecFlauntEquip == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecFlauntEquip->SetAttribute("name", "vecFlauntEquip");
	if(!VectorToXML(s.vecFlauntEquip, *pElem_vecFlauntEquip))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecFlauntEquip->SetAttribute("comment", ToUTF8Ptr("时装"));
	if(rElement.LinkEndChild(pElem_vecFlauntEquip.get()) != NULL)
		pElem_vecFlauntEquip.release();
	unique_ptr<TiXmlElement> pElem_byLianPi(new TiXmlElement("UINT8"));
	if(pElem_byLianPi == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byLianPi->SetAttribute("name", "byLianPi");
	pElem_byLianPi->SetAttribute("value", NumberToString(s.byLianPi).c_str());
	pElem_byLianPi->SetAttribute("comment", ToUTF8Ptr("炼皮"));
	if(rElement.LinkEndChild(pElem_byLianPi.get()) != NULL)
		pElem_byLianPi.release();
	unique_ptr<TiXmlElement> pElem_byTongJin(new TiXmlElement("UINT8"));
	if(pElem_byTongJin == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byTongJin->SetAttribute("name", "byTongJin");
	pElem_byTongJin->SetAttribute("value", NumberToString(s.byTongJin).c_str());
	pElem_byTongJin->SetAttribute("comment", ToUTF8Ptr("通筋"));
	if(rElement.LinkEndChild(pElem_byTongJin.get()) != NULL)
		pElem_byTongJin.release();
	unique_ptr<TiXmlElement> pElem_byQiangJi(new TiXmlElement("UINT8"));
	if(pElem_byQiangJi == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byQiangJi->SetAttribute("name", "byQiangJi");
	pElem_byQiangJi->SetAttribute("value", NumberToString(s.byQiangJi).c_str());
	pElem_byQiangJi->SetAttribute("comment", ToUTF8Ptr("强肌"));
	if(rElement.LinkEndChild(pElem_byQiangJi.get()) != NULL)
		pElem_byQiangJi.release();
	unique_ptr<TiXmlElement> pElem_byDuanGu(new TiXmlElement("UINT8"));
	if(pElem_byDuanGu == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byDuanGu->SetAttribute("name", "byDuanGu");
	pElem_byDuanGu->SetAttribute("value", NumberToString(s.byDuanGu).c_str());
	pElem_byDuanGu->SetAttribute("comment", ToUTF8Ptr("锻骨"));
	if(rElement.LinkEndChild(pElem_byDuanGu.get()) != NULL)
		pElem_byDuanGu.release();
	unique_ptr<TiXmlElement> pElem_byHuoLuo(new TiXmlElement("UINT8"));
	if(pElem_byHuoLuo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byHuoLuo->SetAttribute("name", "byHuoLuo");
	pElem_byHuoLuo->SetAttribute("value", NumberToString(s.byHuoLuo).c_str());
	pElem_byHuoLuo->SetAttribute("comment", ToUTF8Ptr("活络"));
	if(rElement.LinkEndChild(pElem_byHuoLuo.get()) != NULL)
		pElem_byHuoLuo.release();
	unique_ptr<TiXmlElement> pElem_byXiSui(new TiXmlElement("UINT8"));
	if(pElem_byXiSui == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byXiSui->SetAttribute("name", "byXiSui");
	pElem_byXiSui->SetAttribute("value", NumberToString(s.byXiSui).c_str());
	pElem_byXiSui->SetAttribute("comment", ToUTF8Ptr("洗髓"));
	if(rElement.LinkEndChild(pElem_byXiSui.get()) != NULL)
		pElem_byXiSui.release();
	return true;
}

#endif

SFlauntFashion::SFlauntFashion() : wFighterID(0), byLevel(0), byType(0), weaponID(0), armorID(0) { }

SFlauntFashion::SFlauntFashion(UINT16 wFighterID_, UINT8 byLevel_, UINT8 byType_, UINT16 weaponID_, UINT16 armorID_)
			: wFighterID(wFighterID_), byLevel(byLevel_), byType(byType_), weaponID(weaponID_), armorID(armorID_) { }

CInArchive& operator>>(CInArchive& src, SFlauntFashion& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.wFighterID;
	src >> s.byLevel;
	src >> s.byType;
	src >> s.weaponID;
	src >> s.armorID;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SFlauntFashion& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.wFighterID;
	src << s.byLevel;
	src << s.byType;
	src << s.weaponID;
	src << s.armorID;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SFlauntFashion& s)
{
	if(strcmp(rElement.Value(), "SFlauntFashion") != 0)
	{
		LOG_CRI << "rElement is not SFlauntFashion!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
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
		LOG_CRI << "pElemChild for byType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byType") != 0)
	{
		LOG_CRI << "Attribute: name is not byType!";
		return false;
	}
	const char* pszVal_byType = pElemChild->Attribute("value");
	if(pszVal_byType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byType, s.byType))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for weaponID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "weaponID") != 0)
	{
		LOG_CRI << "Attribute: name is not weaponID!";
		return false;
	}
	const char* pszVal_weaponID = pElemChild->Attribute("value");
	if(pszVal_weaponID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_weaponID, s.weaponID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for armorID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "armorID") != 0)
	{
		LOG_CRI << "Attribute: name is not armorID!";
		return false;
	}
	const char* pszVal_armorID = pElemChild->Attribute("value");
	if(pszVal_armorID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_armorID, s.armorID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SFlauntFashion& s, TiXmlElement& rElement)
{
	rElement.SetValue("SFlauntFashion");
	rElement.SetAttribute("type", ToUTF8Ptr("时装炫耀"));
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
	pElem_byLevel->SetAttribute("comment", ToUTF8Ptr("时装等级"));
	if(rElement.LinkEndChild(pElem_byLevel.get()) != NULL)
		pElem_byLevel.release();
	unique_ptr<TiXmlElement> pElem_byType(new TiXmlElement("UINT8"));
	if(pElem_byType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byType->SetAttribute("name", "byType");
	pElem_byType->SetAttribute("value", NumberToString(s.byType).c_str());
	pElem_byType->SetAttribute("comment", ToUTF8Ptr("类型(0武器,1衣服)"));
	if(rElement.LinkEndChild(pElem_byType.get()) != NULL)
		pElem_byType.release();
	unique_ptr<TiXmlElement> pElem_weaponID(new TiXmlElement("UINT16"));
	if(pElem_weaponID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_weaponID->SetAttribute("name", "weaponID");
	pElem_weaponID->SetAttribute("value", NumberToString(s.weaponID).c_str());
	pElem_weaponID->SetAttribute("comment", ToUTF8Ptr("武器ID"));
	if(rElement.LinkEndChild(pElem_weaponID.get()) != NULL)
		pElem_weaponID.release();
	unique_ptr<TiXmlElement> pElem_armorID(new TiXmlElement("UINT16"));
	if(pElem_armorID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_armorID->SetAttribute("name", "armorID");
	pElem_armorID->SetAttribute("value", NumberToString(s.armorID).c_str());
	pElem_armorID->SetAttribute("comment", ToUTF8Ptr("衣服ID"));
	if(rElement.LinkEndChild(pElem_armorID.get()) != NULL)
		pElem_armorID.release();
	return true;
}

#endif

SFlauntPet::SFlauntPet() : qwInstID(0), wFighterID(0), byLevel(0) { }

SFlauntPet::SFlauntPet(UINT64 qwInstID_, UINT16 wFighterID_, UINT8 byLevel_) : qwInstID(qwInstID_), wFighterID(wFighterID_), byLevel(byLevel_) { }

CInArchive& operator>>(CInArchive& src, SFlauntPet& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwInstID;
	src >> s.wFighterID;
	src >> s.byLevel;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SFlauntPet& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.qwInstID;
	src << s.wFighterID;
	src << s.byLevel;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SFlauntPet& s)
{
	if(strcmp(rElement.Value(), "SFlauntPet") != 0)
	{
		LOG_CRI << "rElement is not SFlauntPet!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwInstID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwInstID") != 0)
	{
		LOG_CRI << "Attribute: name is not qwInstID!";
		return false;
	}
	const char* pszVal_qwInstID = pElemChild->Attribute("value");
	if(pszVal_qwInstID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwInstID, s.qwInstID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
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
	return true;
}

bool ToXML(const SFlauntPet& s, TiXmlElement& rElement)
{
	rElement.SetValue("SFlauntPet");
	rElement.SetAttribute("type", ToUTF8Ptr("阵灵炫耀信息"));
	unique_ptr<TiXmlElement> pElem_qwInstID(new TiXmlElement("UINT64"));
	if(pElem_qwInstID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwInstID->SetAttribute("name", "qwInstID");
	pElem_qwInstID->SetAttribute("value", NumberToString(s.qwInstID).c_str());
	pElem_qwInstID->SetAttribute("comment", ToUTF8Ptr("阵灵唯一ID"));
	if(rElement.LinkEndChild(pElem_qwInstID.get()) != NULL)
		pElem_qwInstID.release();
	unique_ptr<TiXmlElement> pElem_wFighterID(new TiXmlElement("UINT16"));
	if(pElem_wFighterID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wFighterID->SetAttribute("name", "wFighterID");
	pElem_wFighterID->SetAttribute("value", NumberToString(s.wFighterID).c_str());
	pElem_wFighterID->SetAttribute("comment", ToUTF8Ptr("阵灵ID"));
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
	return true;
}

#endif

SFlauntHorse::SFlauntHorse() : qwInstID(0), wFighterID(0), byLevel(0) { }

SFlauntHorse::SFlauntHorse(UINT64 qwInstID_, UINT16 wFighterID_, UINT8 byLevel_) : qwInstID(qwInstID_), wFighterID(wFighterID_), byLevel(byLevel_) { }

CInArchive& operator>>(CInArchive& src, SFlauntHorse& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwInstID;
	src >> s.wFighterID;
	src >> s.byLevel;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SFlauntHorse& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.qwInstID;
	src << s.wFighterID;
	src << s.byLevel;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SFlauntHorse& s)
{
	if(strcmp(rElement.Value(), "SFlauntHorse") != 0)
	{
		LOG_CRI << "rElement is not SFlauntHorse!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwInstID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwInstID") != 0)
	{
		LOG_CRI << "Attribute: name is not qwInstID!";
		return false;
	}
	const char* pszVal_qwInstID = pElemChild->Attribute("value");
	if(pszVal_qwInstID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwInstID, s.qwInstID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
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
	return true;
}

bool ToXML(const SFlauntHorse& s, TiXmlElement& rElement)
{
	rElement.SetValue("SFlauntHorse");
	rElement.SetAttribute("type", ToUTF8Ptr("坐骑炫耀信息"));
	unique_ptr<TiXmlElement> pElem_qwInstID(new TiXmlElement("UINT64"));
	if(pElem_qwInstID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwInstID->SetAttribute("name", "qwInstID");
	pElem_qwInstID->SetAttribute("value", NumberToString(s.qwInstID).c_str());
	pElem_qwInstID->SetAttribute("comment", ToUTF8Ptr("阵灵唯一ID"));
	if(rElement.LinkEndChild(pElem_qwInstID.get()) != NULL)
		pElem_qwInstID.release();
	unique_ptr<TiXmlElement> pElem_wFighterID(new TiXmlElement("UINT16"));
	if(pElem_wFighterID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wFighterID->SetAttribute("name", "wFighterID");
	pElem_wFighterID->SetAttribute("value", NumberToString(s.wFighterID).c_str());
	pElem_wFighterID->SetAttribute("comment", ToUTF8Ptr("坐骑ID"));
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
	return true;
}

#endif

SFlauntAchievement::SFlauntAchievement() : qwInstID(0), wAchievementID(0) { }

SFlauntAchievement::SFlauntAchievement(UINT64 qwInstID_, UINT16 wAchievementID_) : qwInstID(qwInstID_), wAchievementID(wAchievementID_) { }

CInArchive& operator>>(CInArchive& src, SFlauntAchievement& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwInstID;
	src >> s.wAchievementID;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SFlauntAchievement& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.qwInstID;
	src << s.wAchievementID;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SFlauntAchievement& s)
{
	if(strcmp(rElement.Value(), "SFlauntAchievement") != 0)
	{
		LOG_CRI << "rElement is not SFlauntAchievement!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwInstID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwInstID") != 0)
	{
		LOG_CRI << "Attribute: name is not qwInstID!";
		return false;
	}
	const char* pszVal_qwInstID = pElemChild->Attribute("value");
	if(pszVal_qwInstID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwInstID, s.qwInstID))
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
	return true;
}

bool ToXML(const SFlauntAchievement& s, TiXmlElement& rElement)
{
	rElement.SetValue("SFlauntAchievement");
	rElement.SetAttribute("type", ToUTF8Ptr("成就炫耀信息"));
	unique_ptr<TiXmlElement> pElem_qwInstID(new TiXmlElement("UINT64"));
	if(pElem_qwInstID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwInstID->SetAttribute("name", "qwInstID");
	pElem_qwInstID->SetAttribute("value", NumberToString(s.qwInstID).c_str());
	pElem_qwInstID->SetAttribute("comment", ToUTF8Ptr("成就唯一ID"));
	if(rElement.LinkEndChild(pElem_qwInstID.get()) != NULL)
		pElem_qwInstID.release();
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
	return true;
}

#endif

} //namespace NGlobalChatProt
