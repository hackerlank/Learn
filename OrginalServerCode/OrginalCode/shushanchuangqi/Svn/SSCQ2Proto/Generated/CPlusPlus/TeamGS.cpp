/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    TeamGS.cpp
//  Purpose:      竞技场协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "TeamGS.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NTeamGS
{

#ifdef PROT_USE_XML

const char* EnumValToStr(EMemberStatus e)
{
	switch(e)
	{
	case EMEMBER_NONE:
		return "EMEMBER_NONE";
	case EMEMBER_READY:
		return "EMEMBER_READY";
	case EMEMBER_ERR:
		return "EMEMBER_ERR";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EMemberStatus& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EMemberStatus> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("EMEMBER_NONE", EMEMBER_NONE));
		mapStr2Val.insert(make_pair("EMEMBER_READY", EMEMBER_READY));
		mapStr2Val.insert(make_pair("EMEMBER_ERR", EMEMBER_ERR));
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

const char* EnumValToStr(TeamListOP e)
{
	switch(e)
	{
	case ETeam_Create:
		return "ETeam_Create";
	case ETeam_UpDate:
		return "ETeam_UpDate";
	case ETeam_Del:
		return "ETeam_Del";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, TeamListOP& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, TeamListOP> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("ETeam_Create", ETeam_Create));
		mapStr2Val.insert(make_pair("ETeam_UpDate", ETeam_UpDate));
		mapStr2Val.insert(make_pair("ETeam_Del", ETeam_Del));
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

const char* EnumValToStr(ETEAMResult e)
{
	switch(e)
	{
	case ETeam_Suc:
		return "ETeam_Suc";
	case ETeam_OtherTeam:
		return "ETeam_OtherTeam";
	case ETeam_NOTInTeam:
		return "ETeam_NOTInTeam";
	case ETeam_PreDgn:
		return "ETeam_PreDgn";
	case ETeam_PackFull:
		return "ETeam_PackFull";
	case ETeam_Full:
		return "ETeam_Full";
	case ETeam_NOLeader:
		return "ETeam_NOLeader";
	case ETeam_NODgnType:
		return "ETeam_NODgnType";
	case ETeam_ErrTeam:
		return "ETeam_ErrTeam";
	case ETeam_NewHeroErr:
		return "ETeam_NewHeroErr";
	case ETeam_MainHero:
		return "ETeam_MainHero";
	case ETeam_NewHeroIn:
		return "ETeam_NewHeroIn";
	case ETeam_NewHeroPosErr:
		return "ETeam_NewHeroPosErr";
	case ETeam_PlayerINReady:
		return "ETeam_PlayerINReady";
	case ETeam_PlayerNOReady:
		return "ETeam_PlayerNOReady";
	case ETeam_MemBerNOReady:
		return "ETeam_MemBerNOReady";
	case ETeam_LowLevel:
		return "ETeam_LowLevel";
	case ETeam_Fighters:
		return "ETeam_Fighters";
	case ETeam_KickSelf:
		return "ETeam_KickSelf";
	case ETeam_KickErr:
		return "ETeam_KickErr";
	case ETeam_PosErr:
		return "ETeam_PosErr";
	case ETeam_InBattle:
		return "ETeam_InBattle";
	case ETeam_MinPerSon:
		return "ETeam_MinPerSon";
	case ETeam_ErrPerSon:
		return "ETeam_ErrPerSon";
	case ETeam_DiffDgn:
		return "ETeam_DiffDgn";
	case ETeam_PetErr:
		return "ETeam_PetErr";
	case ETeam_PassWord:
		return "ETeam_PassWord";
	case ETeam_IsLeader:
		return "ETeam_IsLeader";
	case ETeam_ErrMem:
		return "ETeam_ErrMem";
	case ETeam_OtherErr:
		return "ETeam_OtherErr";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, ETEAMResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, ETEAMResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("ETeam_Suc", ETeam_Suc));
		mapStr2Val.insert(make_pair("ETeam_OtherTeam", ETeam_OtherTeam));
		mapStr2Val.insert(make_pair("ETeam_NOTInTeam", ETeam_NOTInTeam));
		mapStr2Val.insert(make_pair("ETeam_PreDgn", ETeam_PreDgn));
		mapStr2Val.insert(make_pair("ETeam_PackFull", ETeam_PackFull));
		mapStr2Val.insert(make_pair("ETeam_Full", ETeam_Full));
		mapStr2Val.insert(make_pair("ETeam_NOLeader", ETeam_NOLeader));
		mapStr2Val.insert(make_pair("ETeam_NODgnType", ETeam_NODgnType));
		mapStr2Val.insert(make_pair("ETeam_ErrTeam", ETeam_ErrTeam));
		mapStr2Val.insert(make_pair("ETeam_NewHeroErr", ETeam_NewHeroErr));
		mapStr2Val.insert(make_pair("ETeam_MainHero", ETeam_MainHero));
		mapStr2Val.insert(make_pair("ETeam_NewHeroIn", ETeam_NewHeroIn));
		mapStr2Val.insert(make_pair("ETeam_NewHeroPosErr", ETeam_NewHeroPosErr));
		mapStr2Val.insert(make_pair("ETeam_PlayerINReady", ETeam_PlayerINReady));
		mapStr2Val.insert(make_pair("ETeam_PlayerNOReady", ETeam_PlayerNOReady));
		mapStr2Val.insert(make_pair("ETeam_MemBerNOReady", ETeam_MemBerNOReady));
		mapStr2Val.insert(make_pair("ETeam_LowLevel", ETeam_LowLevel));
		mapStr2Val.insert(make_pair("ETeam_Fighters", ETeam_Fighters));
		mapStr2Val.insert(make_pair("ETeam_KickSelf", ETeam_KickSelf));
		mapStr2Val.insert(make_pair("ETeam_KickErr", ETeam_KickErr));
		mapStr2Val.insert(make_pair("ETeam_PosErr", ETeam_PosErr));
		mapStr2Val.insert(make_pair("ETeam_InBattle", ETeam_InBattle));
		mapStr2Val.insert(make_pair("ETeam_MinPerSon", ETeam_MinPerSon));
		mapStr2Val.insert(make_pair("ETeam_ErrPerSon", ETeam_ErrPerSon));
		mapStr2Val.insert(make_pair("ETeam_DiffDgn", ETeam_DiffDgn));
		mapStr2Val.insert(make_pair("ETeam_PetErr", ETeam_PetErr));
		mapStr2Val.insert(make_pair("ETeam_PassWord", ETeam_PassWord));
		mapStr2Val.insert(make_pair("ETeam_IsLeader", ETeam_IsLeader));
		mapStr2Val.insert(make_pair("ETeam_ErrMem", ETeam_ErrMem));
		mapStr2Val.insert(make_pair("ETeam_OtherErr", ETeam_OtherErr));
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

const char* GetDescription(ETEAMResult e)
{
	switch(e)
	{
	case ETeam_Suc:
		return "成功";
	case ETeam_OtherTeam:
		return "在其他房间中";
	case ETeam_NOTInTeam:
		return "不在房间中";
	case ETeam_PreDgn:
		return "前置副本没有通过";
	case ETeam_PackFull:
		return "包裹满";
	case ETeam_Full:
		return "房间满";
	case ETeam_NOLeader:
		return "您不是队长";
	case ETeam_NODgnType:
		return "不存在这个副本";
	case ETeam_ErrTeam:
		return "不存在这个队伍";
	case ETeam_NewHeroErr:
		return "新将不存在";
	case ETeam_MainHero:
		return "主将不可替换";
	case ETeam_NewHeroIn:
		return "新将已在";
	case ETeam_NewHeroPosErr:
		return "新将位置错误";
	case ETeam_PlayerINReady:
		return "玩家已准备";
	case ETeam_PlayerNOReady:
		return "玩家没有准备好";
	case ETeam_MemBerNOReady:
		return "有玩家没有准备好";
	case ETeam_LowLevel:
		return "等级不足，无法进入副本";
	case ETeam_Fighters:
		return "将不足，无法进入副本";
	case ETeam_KickSelf:
		return "不可踢自己";
	case ETeam_KickErr:
		return "被踢不在该队伍中";
	case ETeam_PosErr:
		return "位置不正确";
	case ETeam_InBattle:
		return "战斗中";
	case ETeam_MinPerSon:
		return "人数不足";
	case ETeam_ErrPerSon:
		return "有人不满足条件";
	case ETeam_DiffDgn:
		return "副本人数不一致";
	case ETeam_PetErr:
		return "错误玩家阵灵";
	case ETeam_PassWord:
		return "密码错误";
	case ETeam_IsLeader:
		return "已经是队长";
	case ETeam_ErrMem:
		return "不是房间成员";
	case ETeam_OtherErr:
		return "其他错误";
	default:
		return "未知错误";
	}
}

TeamFighter::TeamFighter() : dwFighterPower(0), byPos(0) { }

CInArchive& operator>>(CInArchive& src, TeamFighter& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	NBattleGS::SFeatureBase_Wrapper pFeature_Wrapper;
	src >> pFeature_Wrapper;
	src >> s.dwFighterPower;
	src >> s.byPos;
	s.pFeature = pFeature_Wrapper.ptr;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TeamFighter& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	NBattleGS::SFeatureBase_Wrapper pFeature_Wrapper(s.pFeature);
	src << pFeature_Wrapper;
	src << s.dwFighterPower;
	src << s.byPos;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TeamFighter_Wrapper& rWrapper)
{
	EType_TeamFighter eType = eType_TeamFighter;
	src >> (UINT8&)eType;
	switch(eType)
	{
	case eType_TeamFighter:
		{
			rWrapper.ptr.reset(new TeamFighter);
			src >> (TeamFighter&)*rWrapper.ptr;
		}
		break;
	case eType_CommonFighter:
		{
			rWrapper.ptr.reset(new CommonFighter);
			src >> (CommonFighter&)*rWrapper.ptr;
		}
		break;
	case eType_FormationFighter:
		{
			rWrapper.ptr.reset(new FormationFighter);
			src >> (FormationFighter&)*rWrapper.ptr;
		}
		break;
	case eType_BeautyFighter:
		{
			rWrapper.ptr.reset(new BeautyFighter);
			src >> (BeautyFighter&)*rWrapper.ptr;
		}
		break;
	default:
		throw "Unknown value for EType_TeamFighter";
		break;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TeamFighter_Wrapper& rWrapper)
{
	if(rWrapper.ptr != NULL)
	{
		src << (UINT8)rWrapper.ptr->GetClassType();
		switch(rWrapper.ptr->GetClassType())
		{
		case eType_TeamFighter:
			src << (TeamFighter&)*rWrapper.ptr;
			break;
		case eType_CommonFighter:
			src << (CommonFighter&)*rWrapper.ptr;
			break;
		case eType_FormationFighter:
			src << (FormationFighter&)*rWrapper.ptr;
			break;
		case eType_BeautyFighter:
			src << (BeautyFighter&)*rWrapper.ptr;
			break;
		default:
			throw "Unknown value for EType_TeamFighter";
			break;
		}
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecTeamFighter& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		TeamFighter_Wrapper wrapper;
		src >> wrapper;
		vec[i] = wrapper.ptr;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecTeamFighter& vec)
{
	if(vec.size() > 0x7FFF)
		throw "Vector Size Too Large!";
	UINT16 wSize = (UINT16)vec.size();
	src.WriteContainerSize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		TeamFighter_Wrapper wrapper;
		wrapper.ptr = vec[i];
		src << wrapper;
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, TeamFighter& s)
{
	if(strcmp(rElement.Value(), "TeamFighter") != 0)
	{
		LOG_CRI << "rElement is not TeamFighter!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for pFeature is empty!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "pFeature") != 0)
	{
		LOG_CRI << "Attribute: name is not pFeature!";
		return false;
	}
	if(!SuperFromXML(*pElemChild, s.pFeature))
	{
		LOG_CRI << "FromXML for: pFeature fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwFighterPower is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwFighterPower") != 0)
	{
		LOG_CRI << "Attribute: name is not dwFighterPower!";
		return false;
	}
	const char* pszVal_dwFighterPower = pElemChild->Attribute("value");
	if(pszVal_dwFighterPower == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwFighterPower, s.dwFighterPower))
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

bool ToXML(const TeamFighter& s, TiXmlElement& rElement)
{
	rElement.SetValue("TeamFighter");
	rElement.SetAttribute("type", ToUTF8Ptr("房间里的战斗对象"));
	unique_ptr<TiXmlElement> pElem_pFeature(new TiXmlElement("BattleGS::SFeatureBase"));
	if(pElem_pFeature == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_pFeature->SetAttribute("name", "pFeature");
	if(s.pFeature == NULL)
	{
		LOG_CRI << "pFeature is NULL!";
		return false;
	}
	if(!SuperToXML(*s.pFeature, *pElem_pFeature))
	{
		LOG_CRI << "pFeature SuperToXML fails!";
		return false;
	}
	pElem_pFeature->SetAttribute("comment", ToUTF8Ptr("外观信息"));
	if(rElement.LinkEndChild(pElem_pFeature.get()) != NULL)
		pElem_pFeature.release();
	unique_ptr<TiXmlElement> pElem_dwFighterPower(new TiXmlElement("UINT32"));
	if(pElem_dwFighterPower == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwFighterPower->SetAttribute("name", "dwFighterPower");
	pElem_dwFighterPower->SetAttribute("value", NumberToString(s.dwFighterPower).c_str());
	pElem_dwFighterPower->SetAttribute("comment", ToUTF8Ptr("战斗力"));
	if(rElement.LinkEndChild(pElem_dwFighterPower.get()) != NULL)
		pElem_dwFighterPower.release();
	unique_ptr<TiXmlElement> pElem_byPos(new TiXmlElement("UINT8"));
	if(pElem_byPos == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byPos->SetAttribute("name", "byPos");
	pElem_byPos->SetAttribute("value", NumberToString(s.byPos).c_str());
	pElem_byPos->SetAttribute("comment", ToUTF8Ptr("在玩家将序列的位置"));
	if(rElement.LinkEndChild(pElem_byPos.get()) != NULL)
		pElem_byPos.release();
	return true;
}

bool SuperFromXML(TiXmlElement& rElement, TeamFighterPtr& p)
{
	const char* pszName = rElement.Value();
	if(pszName == NULL)
	{
		LOG_CRI << "Element Name is empty!";
		return false;
	}
	if(strcmp(pszName, "TeamFighter") == 0)
	{
		TeamFighterPtr pStruct(new TeamFighter);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for TeamFighter";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "TeamFighter FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "CommonFighter") == 0)
	{
		CommonFighterPtr pStruct(new CommonFighter);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for CommonFighter";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "CommonFighter FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "FormationFighter") == 0)
	{
		FormationFighterPtr pStruct(new FormationFighter);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for FormationFighter";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "FormationFighter FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "BeautyFighter") == 0)
	{
		BeautyFighterPtr pStruct(new BeautyFighter);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for BeautyFighter";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "BeautyFighter FromXML fails!";
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

bool SuperToXML(const TeamFighter& s, TiXmlElement& rElement)
{
	switch(s.GetClassType())
	{
	case eType_TeamFighter:
		return ToXML((TeamFighter&)s, rElement);
	case eType_CommonFighter:
		return ToXML((CommonFighter&)s, rElement);
	case eType_FormationFighter:
		return ToXML((FormationFighter&)s, rElement);
	case eType_BeautyFighter:
		return ToXML((BeautyFighter&)s, rElement);
	default:
		LOG_CRI << "Invalid type: " << s.GetClassType();
		return false;
	}
}

bool VectorFromXML(TiXmlElement& rElement, TVecTeamFighter& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		TeamFighterPtr p;
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

bool VectorToXML(const TVecTeamFighter& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("TeamFighter"));
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

CommonFighter::CommonFighter() : qwInstID(0), wFighterID(0), byLevel(0), byMain(0) { }

CInArchive& operator>>(CInArchive& src, CommonFighter& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (TeamFighter&)s;
	src >> s.qwInstID;
	src >> s.wFighterID;
	src >> s.byLevel;
	src >> s.byMain;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const CommonFighter& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const TeamFighter&)s;
	src << s.qwInstID;
	src << s.wFighterID;
	src << s.byLevel;
	src << s.byMain;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecCommonFighter& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		CommonFighterPtr p(new CommonFighter);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecCommonFighter& vec)
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

bool FromXML(TiXmlElement& rElement, CommonFighter& s)
{
	if(strcmp(rElement.Value(), "CommonFighter") != 0)
	{
		LOG_CRI << "rElement is not CommonFighter!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for TeamFighter is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (TeamFighter&)s))
	{
		LOG_CRI << "FromXML for: TeamFighter fails!";
		return false;
	}
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
		LOG_CRI << "pElemChild for byMain is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byMain") != 0)
	{
		LOG_CRI << "Attribute: name is not byMain!";
		return false;
	}
	const char* pszVal_byMain = pElemChild->Attribute("value");
	if(pszVal_byMain == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byMain, s.byMain))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const CommonFighter& s, TiXmlElement& rElement)
{
	rElement.SetValue("CommonFighter");
	rElement.SetAttribute("type", ToUTF8Ptr("普通将"));
	unique_ptr<TiXmlElement> pElem_TeamFighter(new TiXmlElement("TeamFighter"));
	if(pElem_TeamFighter == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const TeamFighter&)s, *pElem_TeamFighter))
	{
		LOG_CRI << "TeamFighter ToXML fails!";
		return false;
	}
	pElem_TeamFighter->SetAttribute("type", ToUTF8Ptr("房间里的战斗对象"));
	pElem_TeamFighter->SetAttribute("comment", ToUTF8Ptr("父类TeamFighter部分"));
	if(rElement.LinkEndChild(pElem_TeamFighter.get()) != NULL)
		pElem_TeamFighter.release();
	unique_ptr<TiXmlElement> pElem_qwInstID(new TiXmlElement("UINT64"));
	if(pElem_qwInstID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwInstID->SetAttribute("name", "qwInstID");
	pElem_qwInstID->SetAttribute("value", NumberToString(s.qwInstID).c_str());
	pElem_qwInstID->SetAttribute("comment", ToUTF8Ptr("将唯一ID"));
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
	pElem_wFighterID->SetAttribute("comment", ToUTF8Ptr("将类型ID"));
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
	unique_ptr<TiXmlElement> pElem_byMain(new TiXmlElement("UINT8"));
	if(pElem_byMain == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byMain->SetAttribute("name", "byMain");
	pElem_byMain->SetAttribute("value", NumberToString(s.byMain).c_str());
	pElem_byMain->SetAttribute("comment", ToUTF8Ptr("是否主将"));
	if(rElement.LinkEndChild(pElem_byMain.get()) != NULL)
		pElem_byMain.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecCommonFighter& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		CommonFighterPtr p(new CommonFighter);
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

bool VectorToXML(const TVecCommonFighter& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("CommonFighter"));
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

FormationFighter::FormationFighter() : wFighterID(0), byPetLevel(0) { }

CInArchive& operator>>(CInArchive& src, FormationFighter& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (TeamFighter&)s;
	src >> s.wFighterID;
	src >> s.byPetLevel;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const FormationFighter& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const TeamFighter&)s;
	src << s.wFighterID;
	src << s.byPetLevel;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecFormationFighter& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		FormationFighterPtr p(new FormationFighter);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecFormationFighter& vec)
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

bool FromXML(TiXmlElement& rElement, FormationFighter& s)
{
	if(strcmp(rElement.Value(), "FormationFighter") != 0)
	{
		LOG_CRI << "rElement is not FormationFighter!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for TeamFighter is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (TeamFighter&)s))
	{
		LOG_CRI << "FromXML for: TeamFighter fails!";
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
		LOG_CRI << "pElemChild for byPetLevel is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byPetLevel") != 0)
	{
		LOG_CRI << "Attribute: name is not byPetLevel!";
		return false;
	}
	const char* pszVal_byPetLevel = pElemChild->Attribute("value");
	if(pszVal_byPetLevel == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byPetLevel, s.byPetLevel))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const FormationFighter& s, TiXmlElement& rElement)
{
	rElement.SetValue("FormationFighter");
	rElement.SetAttribute("type", ToUTF8Ptr("阵灵"));
	unique_ptr<TiXmlElement> pElem_TeamFighter(new TiXmlElement("TeamFighter"));
	if(pElem_TeamFighter == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const TeamFighter&)s, *pElem_TeamFighter))
	{
		LOG_CRI << "TeamFighter ToXML fails!";
		return false;
	}
	pElem_TeamFighter->SetAttribute("type", ToUTF8Ptr("房间里的战斗对象"));
	pElem_TeamFighter->SetAttribute("comment", ToUTF8Ptr("父类TeamFighter部分"));
	if(rElement.LinkEndChild(pElem_TeamFighter.get()) != NULL)
		pElem_TeamFighter.release();
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
	unique_ptr<TiXmlElement> pElem_byPetLevel(new TiXmlElement("UINT8"));
	if(pElem_byPetLevel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byPetLevel->SetAttribute("name", "byPetLevel");
	pElem_byPetLevel->SetAttribute("value", NumberToString(s.byPetLevel).c_str());
	pElem_byPetLevel->SetAttribute("comment", ToUTF8Ptr("阵灵的阶"));
	if(rElement.LinkEndChild(pElem_byPetLevel.get()) != NULL)
		pElem_byPetLevel.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecFormationFighter& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		FormationFighterPtr p(new FormationFighter);
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

bool VectorToXML(const TVecFormationFighter& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("FormationFighter"));
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

BeautyFighter::BeautyFighter() : wFighterID(0) { }

CInArchive& operator>>(CInArchive& src, BeautyFighter& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (TeamFighter&)s;
	src >> s.wFighterID;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const BeautyFighter& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const TeamFighter&)s;
	src << s.wFighterID;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecBeautyFighter& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		BeautyFighterPtr p(new BeautyFighter);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecBeautyFighter& vec)
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

bool FromXML(TiXmlElement& rElement, BeautyFighter& s)
{
	if(strcmp(rElement.Value(), "BeautyFighter") != 0)
	{
		LOG_CRI << "rElement is not BeautyFighter!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for TeamFighter is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (TeamFighter&)s))
	{
		LOG_CRI << "FromXML for: TeamFighter fails!";
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
	return true;
}

bool ToXML(const BeautyFighter& s, TiXmlElement& rElement)
{
	rElement.SetValue("BeautyFighter");
	rElement.SetAttribute("type", ToUTF8Ptr("阵灵"));
	unique_ptr<TiXmlElement> pElem_TeamFighter(new TiXmlElement("TeamFighter"));
	if(pElem_TeamFighter == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const TeamFighter&)s, *pElem_TeamFighter))
	{
		LOG_CRI << "TeamFighter ToXML fails!";
		return false;
	}
	pElem_TeamFighter->SetAttribute("type", ToUTF8Ptr("房间里的战斗对象"));
	pElem_TeamFighter->SetAttribute("comment", ToUTF8Ptr("父类TeamFighter部分"));
	if(rElement.LinkEndChild(pElem_TeamFighter.get()) != NULL)
		pElem_TeamFighter.release();
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
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecBeautyFighter& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		BeautyFighterPtr p(new BeautyFighter);
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

bool VectorToXML(const TVecBeautyFighter& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("BeautyFighter"));
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

TeamMember::TeamMember() : qwRoleID(0), byPos(0), eStatus((EMemberStatus)0), byVIPLevel(0) { }

TeamMember::TeamMember(TeamMember&& src) : qwRoleID(src.qwRoleID), byPos(src.byPos), strName(move(src.strName)), eStatus(src.eStatus), byVIPLevel(src.byVIPLevel), 
			oPlatformParam(src.oPlatformParam), vecFighter(move(src.vecFighter)) { }

TeamMember& TeamMember::operator=(TeamMember&& rhs)
{
	if(this != &rhs)
	{
		this->~TeamMember();
		new (this) TeamMember(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, TeamMember& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwRoleID;
	src >> s.byPos;
	src >> s.strName;
	src >> (UINT8&)s.eStatus;
	src >> s.byVIPLevel;
	src >> s.oPlatformParam;
	src >> s.vecFighter;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TeamMember& s)
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
	src << s.byPos;
	src << s.strName;
	src << (UINT8&)s.eStatus;
	src << s.byVIPLevel;
	src << s.oPlatformParam;
	src << s.vecFighter;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, TeamMember& s)
{
	if(strcmp(rElement.Value(), "TeamMember") != 0)
	{
		LOG_CRI << "rElement is not TeamMember!";
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
		LOG_CRI << "pElemChild for eStatus is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "EMemberStatus") != 0)
	{
		LOG_CRI << "pElemChild is not EMemberStatus!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eStatus") != 0)
	{
		LOG_CRI << "Attribute: name is not eStatus!";
		return false;
	}
	const char* pszVal_eStatus = pElemChild->Attribute("value");
	if(pszVal_eStatus == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!EnumStrToVal(pszVal_eStatus, s.eStatus))
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
		LOG_CRI << "pElemChild for oPlatformParam is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "ProtoCommon::SPlatformParam") != 0)
	{
		LOG_CRI << "pElemChild is not ProtoCommon::SPlatformParam!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "oPlatformParam") != 0)
	{
		LOG_CRI << "Attribute: name is not oPlatformParam!";
		return false;
	}
	if(!FromXML(*pElemChild, s.oPlatformParam))
	{
		LOG_CRI << "FromXML for: oPlatformParam fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecFighter is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecTeamFighter") != 0)
	{
		LOG_CRI << "pElemChild is not TVecTeamFighter!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecFighter") != 0)
	{
		LOG_CRI << "Attribute: name is not vecFighter!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecFighter))
	{
		LOG_CRI << "VectorFromXML for vecFighter fails!";
		return false;
	}
	return true;
}

bool ToXML(const TeamMember& s, TiXmlElement& rElement)
{
	rElement.SetValue("TeamMember");
	rElement.SetAttribute("type", ToUTF8Ptr("队伍玩家"));
	unique_ptr<TiXmlElement> pElem_qwRoleID(new TiXmlElement("UINT64"));
	if(pElem_qwRoleID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwRoleID->SetAttribute("name", "qwRoleID");
	pElem_qwRoleID->SetAttribute("value", NumberToString(s.qwRoleID).c_str());
	pElem_qwRoleID->SetAttribute("comment", ToUTF8Ptr("玩家ID"));
	if(rElement.LinkEndChild(pElem_qwRoleID.get()) != NULL)
		pElem_qwRoleID.release();
	unique_ptr<TiXmlElement> pElem_byPos(new TiXmlElement("UINT8"));
	if(pElem_byPos == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byPos->SetAttribute("name", "byPos");
	pElem_byPos->SetAttribute("value", NumberToString(s.byPos).c_str());
	pElem_byPos->SetAttribute("comment", ToUTF8Ptr("位置"));
	if(rElement.LinkEndChild(pElem_byPos.get()) != NULL)
		pElem_byPos.release();
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
	unique_ptr<TiXmlElement> pElem_eStatus(new TiXmlElement("EMemberStatus"));
	if(pElem_eStatus == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eStatus->SetAttribute("name", "eStatus");
	const char* pszEnum_eStatus = EnumValToStr(s.eStatus);
	if(pszEnum_eStatus == NULL)
	{
		LOG_CRI << "EnumValToStr for EMemberStatus fails!";
		return false;
	}
	pElem_eStatus->SetAttribute("value", pszEnum_eStatus);
	pElem_eStatus->SetAttribute("comment", ToUTF8Ptr("玩家状态"));
	if(rElement.LinkEndChild(pElem_eStatus.get()) != NULL)
		pElem_eStatus.release();
	unique_ptr<TiXmlElement> pElem_byVIPLevel(new TiXmlElement("UINT8"));
	if(pElem_byVIPLevel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byVIPLevel->SetAttribute("name", "byVIPLevel");
	pElem_byVIPLevel->SetAttribute("value", NumberToString(s.byVIPLevel).c_str());
	pElem_byVIPLevel->SetAttribute("comment", ToUTF8Ptr("vip等级"));
	if(rElement.LinkEndChild(pElem_byVIPLevel.get()) != NULL)
		pElem_byVIPLevel.release();
	unique_ptr<TiXmlElement> pElem_oPlatformParam(new TiXmlElement("ProtoCommon::SPlatformParam"));
	if(pElem_oPlatformParam == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_oPlatformParam->SetAttribute("name", "oPlatformParam");
	if(!ToXML(s.oPlatformParam, *pElem_oPlatformParam))
	{
		LOG_CRI << "oPlatformParam ToXML fails!";
		return false;
	}
	pElem_oPlatformParam->SetAttribute("comment", ToUTF8Ptr("qq平台信息"));
	if(rElement.LinkEndChild(pElem_oPlatformParam.get()) != NULL)
		pElem_oPlatformParam.release();
	unique_ptr<TiXmlElement> pElem_vecFighter(new TiXmlElement("TVecTeamFighter"));
	if(pElem_vecFighter == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecFighter->SetAttribute("name", "vecFighter");
	if(!VectorToXML(s.vecFighter, *pElem_vecFighter))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecFighter->SetAttribute("comment", ToUTF8Ptr("战斗对象"));
	if(rElement.LinkEndChild(pElem_vecFighter.get()) != NULL)
		pElem_vecFighter.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecTeamMember& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		TeamMember s;
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

bool VectorToXML(const TVecTeamMember& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("TeamMember"));
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

TeamSetting::TeamSetting() : dwPassWord(0) { }

TeamSetting::TeamSetting(UINT32 dwPassWord_) : dwPassWord(dwPassWord_) { }

CInArchive& operator>>(CInArchive& src, TeamSetting& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.dwPassWord;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TeamSetting& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.dwPassWord;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, TeamSetting& s)
{
	if(strcmp(rElement.Value(), "TeamSetting") != 0)
	{
		LOG_CRI << "rElement is not TeamSetting!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwPassWord is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwPassWord") != 0)
	{
		LOG_CRI << "Attribute: name is not dwPassWord!";
		return false;
	}
	const char* pszVal_dwPassWord = pElemChild->Attribute("value");
	if(pszVal_dwPassWord == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwPassWord, s.dwPassWord))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const TeamSetting& s, TiXmlElement& rElement)
{
	rElement.SetValue("TeamSetting");
	rElement.SetAttribute("type", ToUTF8Ptr("队伍设定"));
	unique_ptr<TiXmlElement> pElem_dwPassWord(new TiXmlElement("UINT32"));
	if(pElem_dwPassWord == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwPassWord->SetAttribute("name", "dwPassWord");
	pElem_dwPassWord->SetAttribute("value", NumberToString(s.dwPassWord).c_str());
	pElem_dwPassWord->SetAttribute("comment", ToUTF8Ptr("队伍密码"));
	if(rElement.LinkEndChild(pElem_dwPassWord.get()) != NULL)
		pElem_dwPassWord.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecTeamSetting& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		TeamSetting s;
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

bool VectorToXML(const TVecTeamSetting& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("TeamSetting"));
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

TeamInfo::TeamInfo() : TeamID(0), DgnType(0), TeamLeader(0), qwPetOwner(0) { }

TeamInfo::TeamInfo(UINT32 TeamID_, UINT16 DgnType_, UINT64 TeamLeader_, UINT64 qwPetOwner_, const TeamSetting& stSetting_, 
			const TVecTeamMember& vecMember_)
			: TeamID(TeamID_), DgnType(DgnType_), TeamLeader(TeamLeader_), qwPetOwner(qwPetOwner_), stSetting(stSetting_), 
			vecMember(vecMember_) { }

TeamInfo::TeamInfo(TeamInfo&& src) : TeamID(src.TeamID), DgnType(src.DgnType), TeamLeader(src.TeamLeader), qwPetOwner(src.qwPetOwner), stSetting(src.stSetting), 
			vecMember(move(src.vecMember)) { }

TeamInfo& TeamInfo::operator=(TeamInfo&& rhs)
{
	if(this != &rhs)
	{
		this->~TeamInfo();
		new (this) TeamInfo(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, TeamInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.TeamID;
	src >> s.DgnType;
	src >> s.TeamLeader;
	src >> s.qwPetOwner;
	src >> s.stSetting;
	src >> s.vecMember;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TeamInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.TeamID;
	src << s.DgnType;
	src << s.TeamLeader;
	src << s.qwPetOwner;
	src << s.stSetting;
	src << s.vecMember;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, TeamInfo& s)
{
	if(strcmp(rElement.Value(), "TeamInfo") != 0)
	{
		LOG_CRI << "rElement is not TeamInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for TeamID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "TeamID") != 0)
	{
		LOG_CRI << "Attribute: name is not TeamID!";
		return false;
	}
	const char* pszVal_TeamID = pElemChild->Attribute("value");
	if(pszVal_TeamID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_TeamID, s.TeamID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for DgnType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "DgnType") != 0)
	{
		LOG_CRI << "Attribute: name is not DgnType!";
		return false;
	}
	const char* pszVal_DgnType = pElemChild->Attribute("value");
	if(pszVal_DgnType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_DgnType, s.DgnType))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for TeamLeader is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "TeamLeader") != 0)
	{
		LOG_CRI << "Attribute: name is not TeamLeader!";
		return false;
	}
	const char* pszVal_TeamLeader = pElemChild->Attribute("value");
	if(pszVal_TeamLeader == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_TeamLeader, s.TeamLeader))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwPetOwner is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwPetOwner") != 0)
	{
		LOG_CRI << "Attribute: name is not qwPetOwner!";
		return false;
	}
	const char* pszVal_qwPetOwner = pElemChild->Attribute("value");
	if(pszVal_qwPetOwner == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwPetOwner, s.qwPetOwner))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for stSetting is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TeamSetting") != 0)
	{
		LOG_CRI << "pElemChild is not TeamSetting!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "stSetting") != 0)
	{
		LOG_CRI << "Attribute: name is not stSetting!";
		return false;
	}
	if(!FromXML(*pElemChild, s.stSetting))
	{
		LOG_CRI << "FromXML for: stSetting fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecMember is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecTeamMember") != 0)
	{
		LOG_CRI << "pElemChild is not TVecTeamMember!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecMember") != 0)
	{
		LOG_CRI << "Attribute: name is not vecMember!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecMember))
	{
		LOG_CRI << "VectorFromXML for vecMember fails!";
		return false;
	}
	return true;
}

bool ToXML(const TeamInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("TeamInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("队伍信息"));
	unique_ptr<TiXmlElement> pElem_TeamID(new TiXmlElement("UINT32"));
	if(pElem_TeamID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_TeamID->SetAttribute("name", "TeamID");
	pElem_TeamID->SetAttribute("value", NumberToString(s.TeamID).c_str());
	pElem_TeamID->SetAttribute("comment", ToUTF8Ptr("队伍ID"));
	if(rElement.LinkEndChild(pElem_TeamID.get()) != NULL)
		pElem_TeamID.release();
	unique_ptr<TiXmlElement> pElem_DgnType(new TiXmlElement("UINT16"));
	if(pElem_DgnType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_DgnType->SetAttribute("name", "DgnType");
	pElem_DgnType->SetAttribute("value", NumberToString(s.DgnType).c_str());
	pElem_DgnType->SetAttribute("comment", ToUTF8Ptr("副本模板"));
	if(rElement.LinkEndChild(pElem_DgnType.get()) != NULL)
		pElem_DgnType.release();
	unique_ptr<TiXmlElement> pElem_TeamLeader(new TiXmlElement("UINT64"));
	if(pElem_TeamLeader == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_TeamLeader->SetAttribute("name", "TeamLeader");
	pElem_TeamLeader->SetAttribute("value", NumberToString(s.TeamLeader).c_str());
	pElem_TeamLeader->SetAttribute("comment", ToUTF8Ptr("队长ID"));
	if(rElement.LinkEndChild(pElem_TeamLeader.get()) != NULL)
		pElem_TeamLeader.release();
	unique_ptr<TiXmlElement> pElem_qwPetOwner(new TiXmlElement("UINT64"));
	if(pElem_qwPetOwner == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwPetOwner->SetAttribute("name", "qwPetOwner");
	pElem_qwPetOwner->SetAttribute("value", NumberToString(s.qwPetOwner).c_str());
	pElem_qwPetOwner->SetAttribute("comment", ToUTF8Ptr("出战阵灵的拥有者"));
	if(rElement.LinkEndChild(pElem_qwPetOwner.get()) != NULL)
		pElem_qwPetOwner.release();
	unique_ptr<TiXmlElement> pElem_stSetting(new TiXmlElement("TeamSetting"));
	if(pElem_stSetting == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_stSetting->SetAttribute("name", "stSetting");
	if(!ToXML(s.stSetting, *pElem_stSetting))
	{
		LOG_CRI << "stSetting ToXML fails!";
		return false;
	}
	pElem_stSetting->SetAttribute("comment", ToUTF8Ptr("队伍设置"));
	if(rElement.LinkEndChild(pElem_stSetting.get()) != NULL)
		pElem_stSetting.release();
	unique_ptr<TiXmlElement> pElem_vecMember(new TiXmlElement("TVecTeamMember"));
	if(pElem_vecMember == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecMember->SetAttribute("name", "vecMember");
	if(!VectorToXML(s.vecMember, *pElem_vecMember))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecMember->SetAttribute("comment", ToUTF8Ptr("队伍成员"));
	if(rElement.LinkEndChild(pElem_vecMember.get()) != NULL)
		pElem_vecMember.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecTeamInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		TeamInfo s;
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

bool VectorToXML(const TVecTeamInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("TeamInfo"));
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

TeamInfoForList::TeamInfoForList() : TeamID(0), DgnType(0), bySize(0) { }

TeamInfoForList::TeamInfoForList(TeamInfoForList&& src) : TeamID(src.TeamID), DgnType(src.DgnType), stSetting(src.stSetting), strLeaderName(move(src.strLeaderName)), 
			bySize(src.bySize)
{
	stLeader.swap(src.stLeader);
}

TeamInfoForList& TeamInfoForList::operator=(TeamInfoForList&& rhs)
{
	if(this != &rhs)
	{
		this->~TeamInfoForList();
		new (this) TeamInfoForList(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, TeamInfoForList& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	TeamFighter_Wrapper stLeader_Wrapper;
	src >> s.TeamID;
	src >> s.DgnType;
	src >> s.stSetting;
	src >> stLeader_Wrapper;
	src >> s.strLeaderName;
	src >> s.bySize;
	s.stLeader = stLeader_Wrapper.ptr;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TeamInfoForList& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	TeamFighter_Wrapper stLeader_Wrapper(s.stLeader);
	src << s.TeamID;
	src << s.DgnType;
	src << s.stSetting;
	src << stLeader_Wrapper;
	src << s.strLeaderName;
	src << s.bySize;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, TeamInfoForList& s)
{
	if(strcmp(rElement.Value(), "TeamInfoForList") != 0)
	{
		LOG_CRI << "rElement is not TeamInfoForList!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for TeamID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "TeamID") != 0)
	{
		LOG_CRI << "Attribute: name is not TeamID!";
		return false;
	}
	const char* pszVal_TeamID = pElemChild->Attribute("value");
	if(pszVal_TeamID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_TeamID, s.TeamID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for DgnType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "DgnType") != 0)
	{
		LOG_CRI << "Attribute: name is not DgnType!";
		return false;
	}
	const char* pszVal_DgnType = pElemChild->Attribute("value");
	if(pszVal_DgnType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_DgnType, s.DgnType))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for stSetting is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TeamSetting") != 0)
	{
		LOG_CRI << "pElemChild is not TeamSetting!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "stSetting") != 0)
	{
		LOG_CRI << "Attribute: name is not stSetting!";
		return false;
	}
	if(!FromXML(*pElemChild, s.stSetting))
	{
		LOG_CRI << "FromXML for: stSetting fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for stLeader is empty!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "stLeader") != 0)
	{
		LOG_CRI << "Attribute: name is not stLeader!";
		return false;
	}
	if(!SuperFromXML(*pElemChild, s.stLeader))
	{
		LOG_CRI << "FromXML for: stLeader fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strLeaderName is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strLeaderName") != 0)
	{
		LOG_CRI << "Attribute: name is not strLeaderName!";
		return false;
	}
	const char* pszVal_strLeaderName = pElemChild->Attribute("value");
	if(pszVal_strLeaderName == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strLeaderName = pszVal_strLeaderName;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for bySize is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "bySize") != 0)
	{
		LOG_CRI << "Attribute: name is not bySize!";
		return false;
	}
	const char* pszVal_bySize = pElemChild->Attribute("value");
	if(pszVal_bySize == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_bySize, s.bySize))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const TeamInfoForList& s, TiXmlElement& rElement)
{
	rElement.SetValue("TeamInfoForList");
	rElement.SetAttribute("type", ToUTF8Ptr("房间列表信息"));
	unique_ptr<TiXmlElement> pElem_TeamID(new TiXmlElement("UINT32"));
	if(pElem_TeamID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_TeamID->SetAttribute("name", "TeamID");
	pElem_TeamID->SetAttribute("value", NumberToString(s.TeamID).c_str());
	pElem_TeamID->SetAttribute("comment", ToUTF8Ptr("队伍ID"));
	if(rElement.LinkEndChild(pElem_TeamID.get()) != NULL)
		pElem_TeamID.release();
	unique_ptr<TiXmlElement> pElem_DgnType(new TiXmlElement("UINT16"));
	if(pElem_DgnType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_DgnType->SetAttribute("name", "DgnType");
	pElem_DgnType->SetAttribute("value", NumberToString(s.DgnType).c_str());
	pElem_DgnType->SetAttribute("comment", ToUTF8Ptr("房间ID"));
	if(rElement.LinkEndChild(pElem_DgnType.get()) != NULL)
		pElem_DgnType.release();
	unique_ptr<TiXmlElement> pElem_stSetting(new TiXmlElement("TeamSetting"));
	if(pElem_stSetting == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_stSetting->SetAttribute("name", "stSetting");
	if(!ToXML(s.stSetting, *pElem_stSetting))
	{
		LOG_CRI << "stSetting ToXML fails!";
		return false;
	}
	pElem_stSetting->SetAttribute("comment", ToUTF8Ptr("队伍设置密码0 或 1，1表示有密码"));
	if(rElement.LinkEndChild(pElem_stSetting.get()) != NULL)
		pElem_stSetting.release();
	unique_ptr<TiXmlElement> pElem_stLeader(new TiXmlElement("TeamFighter"));
	if(pElem_stLeader == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_stLeader->SetAttribute("name", "stLeader");
	if(s.stLeader == NULL)
	{
		LOG_CRI << "stLeader is NULL!";
		return false;
	}
	if(!SuperToXML(*s.stLeader, *pElem_stLeader))
	{
		LOG_CRI << "stLeader SuperToXML fails!";
		return false;
	}
	pElem_stLeader->SetAttribute("comment", ToUTF8Ptr("队长信息"));
	if(rElement.LinkEndChild(pElem_stLeader.get()) != NULL)
		pElem_stLeader.release();
	unique_ptr<TiXmlElement> pElem_strLeaderName(new TiXmlElement("string"));
	if(pElem_strLeaderName == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strLeaderName->SetAttribute("name", "strLeaderName");
	pElem_strLeaderName->SetAttribute("value", s.strLeaderName.c_str());
	pElem_strLeaderName->SetAttribute("comment", ToUTF8Ptr("队长名字"));
	if(rElement.LinkEndChild(pElem_strLeaderName.get()) != NULL)
		pElem_strLeaderName.release();
	unique_ptr<TiXmlElement> pElem_bySize(new TiXmlElement("UINT8"));
	if(pElem_bySize == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_bySize->SetAttribute("name", "bySize");
	pElem_bySize->SetAttribute("value", NumberToString(s.bySize).c_str());
	pElem_bySize->SetAttribute("comment", ToUTF8Ptr("当前人数"));
	if(rElement.LinkEndChild(pElem_bySize.get()) != NULL)
		pElem_bySize.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecTeamInfoForList& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		TeamInfoForList s;
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

bool VectorToXML(const TVecTeamInfoForList& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("TeamInfoForList"));
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

} //namespace NTeamGS
