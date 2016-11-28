/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    RoleEnterGameProt.cpp
//  Purpose:      角色信息相关操作协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "RoleEnterGameProt.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NRoleEnterGameProt
{

#ifdef PROT_USE_XML

const char* EnumValToStr(EEnterResult e)
{
	switch(e)
	{
	case eEnterSucceed:
		return "eEnterSucceed";
	case eRoleNoExist:
		return "eRoleNoExist";
	case eEnterAlready:
		return "eEnterAlready";
	case eEnterDataErr:
		return "eEnterDataErr";
	case eEnterStateErr:
		return "eEnterStateErr";
	case eEnterFreezErr:
		return "eEnterFreezErr";
	case eEnterOtherErr:
		return "eEnterOtherErr";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EEnterResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EEnterResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eEnterSucceed", eEnterSucceed));
		mapStr2Val.insert(make_pair("eRoleNoExist", eRoleNoExist));
		mapStr2Val.insert(make_pair("eEnterAlready", eEnterAlready));
		mapStr2Val.insert(make_pair("eEnterDataErr", eEnterDataErr));
		mapStr2Val.insert(make_pair("eEnterStateErr", eEnterStateErr));
		mapStr2Val.insert(make_pair("eEnterFreezErr", eEnterFreezErr));
		mapStr2Val.insert(make_pair("eEnterOtherErr", eEnterOtherErr));
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

const char* GetDescription(EEnterResult e)
{
	switch(e)
	{
	case eEnterSucceed:
		return "成功";
	case eRoleNoExist:
		return "角色未创建";
	case eEnterAlready:
		return "已经在游戏中";
	case eEnterDataErr:
		return "角色数据错误";
	case eEnterStateErr:
		return "状态错误";
	case eEnterFreezErr:
		return "帐号被封";
	case eEnterOtherErr:
		return "其它错误";
	default:
		return "未知错误";
	}
}

#ifdef PROT_USE_XML

const char* EnumValToStr(ECreateRoleResult e)
{
	switch(e)
	{
	case eRoleSucceed:
		return "eRoleSucceed";
	case eRoleExist:
		return "eRoleExist";
	case eRoleNameExist:
		return "eRoleNameExist";
	case eRoleNameInvalid:
		return "eRoleNameInvalid";
	case eRoleNameTooLong:
		return "eRoleNameTooLong";
	case eRoleNameTooShort:
		return "eRoleNameTooShort";
	case eRoleStateErr:
		return "eRoleStateErr";
	case eRoleJobErr:
		return "eRoleJobErr";
	case eRoleSexErr:
		return "eRoleSexErr";
	case eRoleOtherErr:
		return "eRoleOtherErr";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, ECreateRoleResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, ECreateRoleResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eRoleSucceed", eRoleSucceed));
		mapStr2Val.insert(make_pair("eRoleExist", eRoleExist));
		mapStr2Val.insert(make_pair("eRoleNameExist", eRoleNameExist));
		mapStr2Val.insert(make_pair("eRoleNameInvalid", eRoleNameInvalid));
		mapStr2Val.insert(make_pair("eRoleNameTooLong", eRoleNameTooLong));
		mapStr2Val.insert(make_pair("eRoleNameTooShort", eRoleNameTooShort));
		mapStr2Val.insert(make_pair("eRoleStateErr", eRoleStateErr));
		mapStr2Val.insert(make_pair("eRoleJobErr", eRoleJobErr));
		mapStr2Val.insert(make_pair("eRoleSexErr", eRoleSexErr));
		mapStr2Val.insert(make_pair("eRoleOtherErr", eRoleOtherErr));
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

const char* GetDescription(ECreateRoleResult e)
{
	switch(e)
	{
	case eRoleSucceed:
		return "成功";
	case eRoleExist:
		return "角色已存在";
	case eRoleNameExist:
		return "角色名已存在";
	case eRoleNameInvalid:
		return "角色名称有非法字符";
	case eRoleNameTooLong:
		return "角色名过长";
	case eRoleNameTooShort:
		return "角色名过短";
	case eRoleStateErr:
		return "状态错误";
	case eRoleJobErr:
		return "职业错误";
	case eRoleSexErr:
		return "性别错误";
	case eRoleOtherErr:
		return "其它错误";
	default:
		return "未知错误";
	}
}

PlayerBaseData::PlayerBaseData() : eCareer((NProtoCommon::ECareerType)0), eSex((NProtoCommon::ESexType)0), byLevel(0), qwExp(0), wBagMax(0), 
			wDepotMax(0), byNation(0), dwGold(0), dwSilver(0), dwCoupon(0), 
			dwSoul(0), dwPrestige(0), dwHonor(0), dwPExp(0), dwSigil(0), 
			dwCentsY(0), dwAction(0), dwSop(0), dwPoten(0), dwReiki(0), 
			dwDemonSoul(0), dwSoulAttack(0), dwSoulHp(0), dwSoulCritical(0), dwSoulCounter(0), 
			dwSoulSpeed(0), dwSoulDefence(0), dwSoulHit(0), dwSoulDodge(0), dwStampHuang(0), 
			dwStampXuan(0), dwStampDi(0), dwStampTian(0), dwStampXing(0), dwStampYue(0), 
			dwStampDi2(0), dwStampXian(0), dwStampSheng(0), dwStampFo(0), dwBTPoint(0), 
			dwBlueFairyFate(0), dwPurpleFairyFate(0), dwOrangeFairyFate(0), dwTotalRecharge(0), byWallow(0), 
			dwDemonTowerFloorID(0), dwDemonTowerPrizeFloorID(0), dwCreateTime(0) { }

PlayerBaseData::PlayerBaseData(PlayerBaseData&& src) : strName(move(src.strName)), eCareer(src.eCareer), eSex(src.eSex), byLevel(src.byLevel), qwExp(src.qwExp), 
			wBagMax(src.wBagMax), wDepotMax(src.wDepotMax), byNation(src.byNation), dwGold(src.dwGold), dwSilver(src.dwSilver), 
			dwCoupon(src.dwCoupon), dwSoul(src.dwSoul), dwPrestige(src.dwPrestige), dwHonor(src.dwHonor), dwPExp(src.dwPExp), 
			dwSigil(src.dwSigil), dwCentsY(src.dwCentsY), dwAction(src.dwAction), dwSop(src.dwSop), dwPoten(src.dwPoten), 
			dwReiki(src.dwReiki), dwDemonSoul(src.dwDemonSoul), dwSoulAttack(src.dwSoulAttack), dwSoulHp(src.dwSoulHp), dwSoulCritical(src.dwSoulCritical), 
			dwSoulCounter(src.dwSoulCounter), dwSoulSpeed(src.dwSoulSpeed), dwSoulDefence(src.dwSoulDefence), dwSoulHit(src.dwSoulHit), dwSoulDodge(src.dwSoulDodge), 
			dwStampHuang(src.dwStampHuang), dwStampXuan(src.dwStampXuan), dwStampDi(src.dwStampDi), dwStampTian(src.dwStampTian), dwStampXing(src.dwStampXing), 
			dwStampYue(src.dwStampYue), dwStampDi2(src.dwStampDi2), dwStampXian(src.dwStampXian), dwStampSheng(src.dwStampSheng), dwStampFo(src.dwStampFo), 
			dwBTPoint(src.dwBTPoint), dwBlueFairyFate(src.dwBlueFairyFate), dwPurpleFairyFate(src.dwPurpleFairyFate), dwOrangeFairyFate(src.dwOrangeFairyFate), dwTotalRecharge(src.dwTotalRecharge), 
			vecOwnTitle(src.vecOwnTitle), vecEquipTitle(src.vecEquipTitle), strGuide(move(src.strGuide)), byWallow(src.byWallow), vecIconAppear(src.vecIconAppear), 
			vecIconDel(src.vecIconDel), dwDemonTowerFloorID(src.dwDemonTowerFloorID), dwDemonTowerPrizeFloorID(src.dwDemonTowerPrizeFloorID), dwCreateTime(src.dwCreateTime) { }

PlayerBaseData& PlayerBaseData::operator=(PlayerBaseData&& rhs)
{
	if(this != &rhs)
	{
		this->~PlayerBaseData();
		new (this) PlayerBaseData(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, PlayerBaseData& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.strName;
	src >> (UINT8&)s.eCareer;
	src >> (UINT8&)s.eSex;
	src >> s.byLevel;
	src >> s.qwExp;
	src >> s.wBagMax;
	src >> s.wDepotMax;
	src >> s.byNation;
	src >> s.dwGold;
	src >> s.dwSilver;
	src >> s.dwCoupon;
	src >> s.dwSoul;
	src >> s.dwPrestige;
	src >> s.dwHonor;
	src >> s.dwPExp;
	src >> s.dwSigil;
	src >> s.dwCentsY;
	src >> s.dwAction;
	src >> s.dwSop;
	src >> s.dwPoten;
	src >> s.dwReiki;
	src >> s.dwDemonSoul;
	src >> s.dwSoulAttack;
	src >> s.dwSoulHp;
	src >> s.dwSoulCritical;
	src >> s.dwSoulCounter;
	src >> s.dwSoulSpeed;
	src >> s.dwSoulDefence;
	src >> s.dwSoulHit;
	src >> s.dwSoulDodge;
	src >> s.dwStampHuang;
	src >> s.dwStampXuan;
	src >> s.dwStampDi;
	src >> s.dwStampTian;
	src >> s.dwStampXing;
	src >> s.dwStampYue;
	src >> s.dwStampDi2;
	src >> s.dwStampXian;
	src >> s.dwStampSheng;
	src >> s.dwStampFo;
	src >> s.dwBTPoint;
	src >> s.dwBlueFairyFate;
	src >> s.dwPurpleFairyFate;
	src >> s.dwOrangeFairyFate;
	src >> s.dwTotalRecharge;
	src >> s.vecOwnTitle;
	src >> s.vecEquipTitle;
	src >> s.strGuide;
	src >> s.byWallow;
	src >> s.vecIconAppear;
	src >> s.vecIconDel;
	src >> s.dwDemonTowerFloorID;
	src >> s.dwDemonTowerPrizeFloorID;
	src >> s.dwCreateTime;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const PlayerBaseData& s)
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
	src << (UINT8&)s.eCareer;
	src << (UINT8&)s.eSex;
	src << s.byLevel;
	src << s.qwExp;
	src << s.wBagMax;
	src << s.wDepotMax;
	src << s.byNation;
	src << s.dwGold;
	src << s.dwSilver;
	src << s.dwCoupon;
	src << s.dwSoul;
	src << s.dwPrestige;
	src << s.dwHonor;
	src << s.dwPExp;
	src << s.dwSigil;
	src << s.dwCentsY;
	src << s.dwAction;
	src << s.dwSop;
	src << s.dwPoten;
	src << s.dwReiki;
	src << s.dwDemonSoul;
	src << s.dwSoulAttack;
	src << s.dwSoulHp;
	src << s.dwSoulCritical;
	src << s.dwSoulCounter;
	src << s.dwSoulSpeed;
	src << s.dwSoulDefence;
	src << s.dwSoulHit;
	src << s.dwSoulDodge;
	src << s.dwStampHuang;
	src << s.dwStampXuan;
	src << s.dwStampDi;
	src << s.dwStampTian;
	src << s.dwStampXing;
	src << s.dwStampYue;
	src << s.dwStampDi2;
	src << s.dwStampXian;
	src << s.dwStampSheng;
	src << s.dwStampFo;
	src << s.dwBTPoint;
	src << s.dwBlueFairyFate;
	src << s.dwPurpleFairyFate;
	src << s.dwOrangeFairyFate;
	src << s.dwTotalRecharge;
	src << s.vecOwnTitle;
	src << s.vecEquipTitle;
	src << s.strGuide;
	src << s.byWallow;
	src << s.vecIconAppear;
	src << s.vecIconDel;
	src << s.dwDemonTowerFloorID;
	src << s.dwDemonTowerPrizeFloorID;
	src << s.dwCreateTime;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, PlayerBaseData& s)
{
	if(strcmp(rElement.Value(), "PlayerBaseData") != 0)
	{
		LOG_CRI << "rElement is not PlayerBaseData!";
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
		LOG_CRI << "pElemChild for eCareer is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "ProtoCommon::ECareerType") != 0)
	{
		LOG_CRI << "pElemChild is not ProtoCommon::ECareerType!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eCareer") != 0)
	{
		LOG_CRI << "Attribute: name is not eCareer!";
		return false;
	}
	const char* pszVal_eCareer = pElemChild->Attribute("value");
	if(pszVal_eCareer == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!NProtoCommon::EnumStrToVal(pszVal_eCareer, s.eCareer))
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
		LOG_CRI << "pElemChild for qwExp is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwExp") != 0)
	{
		LOG_CRI << "Attribute: name is not qwExp!";
		return false;
	}
	const char* pszVal_qwExp = pElemChild->Attribute("value");
	if(pszVal_qwExp == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwExp, s.qwExp))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wBagMax is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wBagMax") != 0)
	{
		LOG_CRI << "Attribute: name is not wBagMax!";
		return false;
	}
	const char* pszVal_wBagMax = pElemChild->Attribute("value");
	if(pszVal_wBagMax == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wBagMax, s.wBagMax))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wDepotMax is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wDepotMax") != 0)
	{
		LOG_CRI << "Attribute: name is not wDepotMax!";
		return false;
	}
	const char* pszVal_wDepotMax = pElemChild->Attribute("value");
	if(pszVal_wDepotMax == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wDepotMax, s.wDepotMax))
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
		LOG_CRI << "pElemChild for dwGold is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwGold") != 0)
	{
		LOG_CRI << "Attribute: name is not dwGold!";
		return false;
	}
	const char* pszVal_dwGold = pElemChild->Attribute("value");
	if(pszVal_dwGold == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwGold, s.dwGold))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwSilver is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwSilver") != 0)
	{
		LOG_CRI << "Attribute: name is not dwSilver!";
		return false;
	}
	const char* pszVal_dwSilver = pElemChild->Attribute("value");
	if(pszVal_dwSilver == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwSilver, s.dwSilver))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwCoupon is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwCoupon") != 0)
	{
		LOG_CRI << "Attribute: name is not dwCoupon!";
		return false;
	}
	const char* pszVal_dwCoupon = pElemChild->Attribute("value");
	if(pszVal_dwCoupon == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwCoupon, s.dwCoupon))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwSoul is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwSoul") != 0)
	{
		LOG_CRI << "Attribute: name is not dwSoul!";
		return false;
	}
	const char* pszVal_dwSoul = pElemChild->Attribute("value");
	if(pszVal_dwSoul == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwSoul, s.dwSoul))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwPrestige is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwPrestige") != 0)
	{
		LOG_CRI << "Attribute: name is not dwPrestige!";
		return false;
	}
	const char* pszVal_dwPrestige = pElemChild->Attribute("value");
	if(pszVal_dwPrestige == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwPrestige, s.dwPrestige))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwHonor is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwHonor") != 0)
	{
		LOG_CRI << "Attribute: name is not dwHonor!";
		return false;
	}
	const char* pszVal_dwHonor = pElemChild->Attribute("value");
	if(pszVal_dwHonor == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwHonor, s.dwHonor))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwPExp is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwPExp") != 0)
	{
		LOG_CRI << "Attribute: name is not dwPExp!";
		return false;
	}
	const char* pszVal_dwPExp = pElemChild->Attribute("value");
	if(pszVal_dwPExp == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwPExp, s.dwPExp))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwSigil is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwSigil") != 0)
	{
		LOG_CRI << "Attribute: name is not dwSigil!";
		return false;
	}
	const char* pszVal_dwSigil = pElemChild->Attribute("value");
	if(pszVal_dwSigil == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwSigil, s.dwSigil))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwCentsY is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwCentsY") != 0)
	{
		LOG_CRI << "Attribute: name is not dwCentsY!";
		return false;
	}
	const char* pszVal_dwCentsY = pElemChild->Attribute("value");
	if(pszVal_dwCentsY == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwCentsY, s.dwCentsY))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwAction is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwAction") != 0)
	{
		LOG_CRI << "Attribute: name is not dwAction!";
		return false;
	}
	const char* pszVal_dwAction = pElemChild->Attribute("value");
	if(pszVal_dwAction == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwAction, s.dwAction))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwSop is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwSop") != 0)
	{
		LOG_CRI << "Attribute: name is not dwSop!";
		return false;
	}
	const char* pszVal_dwSop = pElemChild->Attribute("value");
	if(pszVal_dwSop == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwSop, s.dwSop))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwPoten is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwPoten") != 0)
	{
		LOG_CRI << "Attribute: name is not dwPoten!";
		return false;
	}
	const char* pszVal_dwPoten = pElemChild->Attribute("value");
	if(pszVal_dwPoten == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwPoten, s.dwPoten))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwReiki is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwReiki") != 0)
	{
		LOG_CRI << "Attribute: name is not dwReiki!";
		return false;
	}
	const char* pszVal_dwReiki = pElemChild->Attribute("value");
	if(pszVal_dwReiki == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwReiki, s.dwReiki))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwDemonSoul is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwDemonSoul") != 0)
	{
		LOG_CRI << "Attribute: name is not dwDemonSoul!";
		return false;
	}
	const char* pszVal_dwDemonSoul = pElemChild->Attribute("value");
	if(pszVal_dwDemonSoul == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwDemonSoul, s.dwDemonSoul))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwSoulAttack is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwSoulAttack") != 0)
	{
		LOG_CRI << "Attribute: name is not dwSoulAttack!";
		return false;
	}
	const char* pszVal_dwSoulAttack = pElemChild->Attribute("value");
	if(pszVal_dwSoulAttack == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwSoulAttack, s.dwSoulAttack))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwSoulHp is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwSoulHp") != 0)
	{
		LOG_CRI << "Attribute: name is not dwSoulHp!";
		return false;
	}
	const char* pszVal_dwSoulHp = pElemChild->Attribute("value");
	if(pszVal_dwSoulHp == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwSoulHp, s.dwSoulHp))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwSoulCritical is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwSoulCritical") != 0)
	{
		LOG_CRI << "Attribute: name is not dwSoulCritical!";
		return false;
	}
	const char* pszVal_dwSoulCritical = pElemChild->Attribute("value");
	if(pszVal_dwSoulCritical == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwSoulCritical, s.dwSoulCritical))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwSoulCounter is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwSoulCounter") != 0)
	{
		LOG_CRI << "Attribute: name is not dwSoulCounter!";
		return false;
	}
	const char* pszVal_dwSoulCounter = pElemChild->Attribute("value");
	if(pszVal_dwSoulCounter == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwSoulCounter, s.dwSoulCounter))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwSoulSpeed is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwSoulSpeed") != 0)
	{
		LOG_CRI << "Attribute: name is not dwSoulSpeed!";
		return false;
	}
	const char* pszVal_dwSoulSpeed = pElemChild->Attribute("value");
	if(pszVal_dwSoulSpeed == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwSoulSpeed, s.dwSoulSpeed))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwSoulDefence is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwSoulDefence") != 0)
	{
		LOG_CRI << "Attribute: name is not dwSoulDefence!";
		return false;
	}
	const char* pszVal_dwSoulDefence = pElemChild->Attribute("value");
	if(pszVal_dwSoulDefence == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwSoulDefence, s.dwSoulDefence))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwSoulHit is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwSoulHit") != 0)
	{
		LOG_CRI << "Attribute: name is not dwSoulHit!";
		return false;
	}
	const char* pszVal_dwSoulHit = pElemChild->Attribute("value");
	if(pszVal_dwSoulHit == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwSoulHit, s.dwSoulHit))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwSoulDodge is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwSoulDodge") != 0)
	{
		LOG_CRI << "Attribute: name is not dwSoulDodge!";
		return false;
	}
	const char* pszVal_dwSoulDodge = pElemChild->Attribute("value");
	if(pszVal_dwSoulDodge == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwSoulDodge, s.dwSoulDodge))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwStampHuang is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwStampHuang") != 0)
	{
		LOG_CRI << "Attribute: name is not dwStampHuang!";
		return false;
	}
	const char* pszVal_dwStampHuang = pElemChild->Attribute("value");
	if(pszVal_dwStampHuang == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwStampHuang, s.dwStampHuang))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwStampXuan is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwStampXuan") != 0)
	{
		LOG_CRI << "Attribute: name is not dwStampXuan!";
		return false;
	}
	const char* pszVal_dwStampXuan = pElemChild->Attribute("value");
	if(pszVal_dwStampXuan == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwStampXuan, s.dwStampXuan))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwStampDi is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwStampDi") != 0)
	{
		LOG_CRI << "Attribute: name is not dwStampDi!";
		return false;
	}
	const char* pszVal_dwStampDi = pElemChild->Attribute("value");
	if(pszVal_dwStampDi == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwStampDi, s.dwStampDi))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwStampTian is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwStampTian") != 0)
	{
		LOG_CRI << "Attribute: name is not dwStampTian!";
		return false;
	}
	const char* pszVal_dwStampTian = pElemChild->Attribute("value");
	if(pszVal_dwStampTian == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwStampTian, s.dwStampTian))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwStampXing is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwStampXing") != 0)
	{
		LOG_CRI << "Attribute: name is not dwStampXing!";
		return false;
	}
	const char* pszVal_dwStampXing = pElemChild->Attribute("value");
	if(pszVal_dwStampXing == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwStampXing, s.dwStampXing))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwStampYue is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwStampYue") != 0)
	{
		LOG_CRI << "Attribute: name is not dwStampYue!";
		return false;
	}
	const char* pszVal_dwStampYue = pElemChild->Attribute("value");
	if(pszVal_dwStampYue == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwStampYue, s.dwStampYue))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwStampDi2 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwStampDi2") != 0)
	{
		LOG_CRI << "Attribute: name is not dwStampDi2!";
		return false;
	}
	const char* pszVal_dwStampDi2 = pElemChild->Attribute("value");
	if(pszVal_dwStampDi2 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwStampDi2, s.dwStampDi2))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwStampXian is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwStampXian") != 0)
	{
		LOG_CRI << "Attribute: name is not dwStampXian!";
		return false;
	}
	const char* pszVal_dwStampXian = pElemChild->Attribute("value");
	if(pszVal_dwStampXian == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwStampXian, s.dwStampXian))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwStampSheng is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwStampSheng") != 0)
	{
		LOG_CRI << "Attribute: name is not dwStampSheng!";
		return false;
	}
	const char* pszVal_dwStampSheng = pElemChild->Attribute("value");
	if(pszVal_dwStampSheng == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwStampSheng, s.dwStampSheng))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwStampFo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwStampFo") != 0)
	{
		LOG_CRI << "Attribute: name is not dwStampFo!";
		return false;
	}
	const char* pszVal_dwStampFo = pElemChild->Attribute("value");
	if(pszVal_dwStampFo == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwStampFo, s.dwStampFo))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwBTPoint is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwBTPoint") != 0)
	{
		LOG_CRI << "Attribute: name is not dwBTPoint!";
		return false;
	}
	const char* pszVal_dwBTPoint = pElemChild->Attribute("value");
	if(pszVal_dwBTPoint == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwBTPoint, s.dwBTPoint))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwBlueFairyFate is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwBlueFairyFate") != 0)
	{
		LOG_CRI << "Attribute: name is not dwBlueFairyFate!";
		return false;
	}
	const char* pszVal_dwBlueFairyFate = pElemChild->Attribute("value");
	if(pszVal_dwBlueFairyFate == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwBlueFairyFate, s.dwBlueFairyFate))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwPurpleFairyFate is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwPurpleFairyFate") != 0)
	{
		LOG_CRI << "Attribute: name is not dwPurpleFairyFate!";
		return false;
	}
	const char* pszVal_dwPurpleFairyFate = pElemChild->Attribute("value");
	if(pszVal_dwPurpleFairyFate == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwPurpleFairyFate, s.dwPurpleFairyFate))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwOrangeFairyFate is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwOrangeFairyFate") != 0)
	{
		LOG_CRI << "Attribute: name is not dwOrangeFairyFate!";
		return false;
	}
	const char* pszVal_dwOrangeFairyFate = pElemChild->Attribute("value");
	if(pszVal_dwOrangeFairyFate == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwOrangeFairyFate, s.dwOrangeFairyFate))
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
		LOG_CRI << "pElemChild for vecOwnTitle is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecUINT16") != 0)
	{
		LOG_CRI << "pElemChild is not TVecUINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecOwnTitle") != 0)
	{
		LOG_CRI << "Attribute: name is not vecOwnTitle!";
		return false;
	}
	const char* pszText_vecOwnTitle = pElemChild->GetText();
	if(pszText_vecOwnTitle != NULL)
		SplitToNumber(pszText_vecOwnTitle, ",", s.vecOwnTitle);
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecEquipTitle is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecUINT16") != 0)
	{
		LOG_CRI << "pElemChild is not TVecUINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecEquipTitle") != 0)
	{
		LOG_CRI << "Attribute: name is not vecEquipTitle!";
		return false;
	}
	const char* pszText_vecEquipTitle = pElemChild->GetText();
	if(pszText_vecEquipTitle != NULL)
		SplitToNumber(pszText_vecEquipTitle, ",", s.vecEquipTitle);
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strGuide is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strGuide") != 0)
	{
		LOG_CRI << "Attribute: name is not strGuide!";
		return false;
	}
	const char* pszVal_strGuide = pElemChild->Attribute("value");
	if(pszVal_strGuide == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strGuide = pszVal_strGuide;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byWallow is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byWallow") != 0)
	{
		LOG_CRI << "Attribute: name is not byWallow!";
		return false;
	}
	const char* pszVal_byWallow = pElemChild->Attribute("value");
	if(pszVal_byWallow == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byWallow, s.byWallow))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecIconAppear is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecUINT16") != 0)
	{
		LOG_CRI << "pElemChild is not TVecUINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecIconAppear") != 0)
	{
		LOG_CRI << "Attribute: name is not vecIconAppear!";
		return false;
	}
	const char* pszText_vecIconAppear = pElemChild->GetText();
	if(pszText_vecIconAppear != NULL)
		SplitToNumber(pszText_vecIconAppear, ",", s.vecIconAppear);
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecIconDel is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecUINT16") != 0)
	{
		LOG_CRI << "pElemChild is not TVecUINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecIconDel") != 0)
	{
		LOG_CRI << "Attribute: name is not vecIconDel!";
		return false;
	}
	const char* pszText_vecIconDel = pElemChild->GetText();
	if(pszText_vecIconDel != NULL)
		SplitToNumber(pszText_vecIconDel, ",", s.vecIconDel);
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwDemonTowerFloorID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwDemonTowerFloorID") != 0)
	{
		LOG_CRI << "Attribute: name is not dwDemonTowerFloorID!";
		return false;
	}
	const char* pszVal_dwDemonTowerFloorID = pElemChild->Attribute("value");
	if(pszVal_dwDemonTowerFloorID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwDemonTowerFloorID, s.dwDemonTowerFloorID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwDemonTowerPrizeFloorID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwDemonTowerPrizeFloorID") != 0)
	{
		LOG_CRI << "Attribute: name is not dwDemonTowerPrizeFloorID!";
		return false;
	}
	const char* pszVal_dwDemonTowerPrizeFloorID = pElemChild->Attribute("value");
	if(pszVal_dwDemonTowerPrizeFloorID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwDemonTowerPrizeFloorID, s.dwDemonTowerPrizeFloorID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwCreateTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwCreateTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwCreateTime!";
		return false;
	}
	const char* pszVal_dwCreateTime = pElemChild->Attribute("value");
	if(pszVal_dwCreateTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwCreateTime, s.dwCreateTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const PlayerBaseData& s, TiXmlElement& rElement)
{
	rElement.SetValue("PlayerBaseData");
	rElement.SetAttribute("type", ToUTF8Ptr("查询基础消息"));
	unique_ptr<TiXmlElement> pElem_strName(new TiXmlElement("string"));
	if(pElem_strName == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strName->SetAttribute("name", "strName");
	pElem_strName->SetAttribute("value", s.strName.c_str());
	pElem_strName->SetAttribute("comment", ToUTF8Ptr("玩家名字"));
	if(rElement.LinkEndChild(pElem_strName.get()) != NULL)
		pElem_strName.release();
	unique_ptr<TiXmlElement> pElem_eCareer(new TiXmlElement("ProtoCommon::ECareerType"));
	if(pElem_eCareer == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eCareer->SetAttribute("name", "eCareer");
	const char* pszEnum_eCareer = NProtoCommon::EnumValToStr(s.eCareer);
	if(pszEnum_eCareer == NULL)
	{
		LOG_CRI << "EnumValToStr for eCareer fails!";
		return false;
	}
	pElem_eCareer->SetAttribute("value", pszEnum_eCareer);
	pElem_eCareer->SetAttribute("comment", ToUTF8Ptr("职业"));
	if(rElement.LinkEndChild(pElem_eCareer.get()) != NULL)
		pElem_eCareer.release();
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
	pElem_byLevel->SetAttribute("comment", ToUTF8Ptr("玩家等级"));
	if(rElement.LinkEndChild(pElem_byLevel.get()) != NULL)
		pElem_byLevel.release();
	unique_ptr<TiXmlElement> pElem_qwExp(new TiXmlElement("UINT64"));
	if(pElem_qwExp == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwExp->SetAttribute("name", "qwExp");
	pElem_qwExp->SetAttribute("value", NumberToString(s.qwExp).c_str());
	pElem_qwExp->SetAttribute("comment", ToUTF8Ptr("玩家经验值"));
	if(rElement.LinkEndChild(pElem_qwExp.get()) != NULL)
		pElem_qwExp.release();
	unique_ptr<TiXmlElement> pElem_wBagMax(new TiXmlElement("UINT16"));
	if(pElem_wBagMax == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wBagMax->SetAttribute("name", "wBagMax");
	pElem_wBagMax->SetAttribute("value", NumberToString(s.wBagMax).c_str());
	pElem_wBagMax->SetAttribute("comment", ToUTF8Ptr("背包容量"));
	if(rElement.LinkEndChild(pElem_wBagMax.get()) != NULL)
		pElem_wBagMax.release();
	unique_ptr<TiXmlElement> pElem_wDepotMax(new TiXmlElement("UINT16"));
	if(pElem_wDepotMax == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wDepotMax->SetAttribute("name", "wDepotMax");
	pElem_wDepotMax->SetAttribute("value", NumberToString(s.wDepotMax).c_str());
	pElem_wDepotMax->SetAttribute("comment", ToUTF8Ptr("仓库容量"));
	if(rElement.LinkEndChild(pElem_wDepotMax.get()) != NULL)
		pElem_wDepotMax.release();
	unique_ptr<TiXmlElement> pElem_byNation(new TiXmlElement("UINT8"));
	if(pElem_byNation == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byNation->SetAttribute("name", "byNation");
	pElem_byNation->SetAttribute("value", NumberToString(s.byNation).c_str());
	pElem_byNation->SetAttribute("comment", ToUTF8Ptr("国家"));
	if(rElement.LinkEndChild(pElem_byNation.get()) != NULL)
		pElem_byNation.release();
	unique_ptr<TiXmlElement> pElem_dwGold(new TiXmlElement("UINT32"));
	if(pElem_dwGold == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwGold->SetAttribute("name", "dwGold");
	pElem_dwGold->SetAttribute("value", NumberToString(s.dwGold).c_str());
	pElem_dwGold->SetAttribute("comment", ToUTF8Ptr("仙石"));
	if(rElement.LinkEndChild(pElem_dwGold.get()) != NULL)
		pElem_dwGold.release();
	unique_ptr<TiXmlElement> pElem_dwSilver(new TiXmlElement("UINT32"));
	if(pElem_dwSilver == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwSilver->SetAttribute("name", "dwSilver");
	pElem_dwSilver->SetAttribute("value", NumberToString(s.dwSilver).c_str());
	pElem_dwSilver->SetAttribute("comment", ToUTF8Ptr("银币"));
	if(rElement.LinkEndChild(pElem_dwSilver.get()) != NULL)
		pElem_dwSilver.release();
	unique_ptr<TiXmlElement> pElem_dwCoupon(new TiXmlElement("UINT32"));
	if(pElem_dwCoupon == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwCoupon->SetAttribute("name", "dwCoupon");
	pElem_dwCoupon->SetAttribute("value", NumberToString(s.dwCoupon).c_str());
	pElem_dwCoupon->SetAttribute("comment", ToUTF8Ptr("礼券"));
	if(rElement.LinkEndChild(pElem_dwCoupon.get()) != NULL)
		pElem_dwCoupon.release();
	unique_ptr<TiXmlElement> pElem_dwSoul(new TiXmlElement("UINT32"));
	if(pElem_dwSoul == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwSoul->SetAttribute("name", "dwSoul");
	pElem_dwSoul->SetAttribute("value", NumberToString(s.dwSoul).c_str());
	pElem_dwSoul->SetAttribute("comment", ToUTF8Ptr("魂魄"));
	if(rElement.LinkEndChild(pElem_dwSoul.get()) != NULL)
		pElem_dwSoul.release();
	unique_ptr<TiXmlElement> pElem_dwPrestige(new TiXmlElement("UINT32"));
	if(pElem_dwPrestige == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwPrestige->SetAttribute("name", "dwPrestige");
	pElem_dwPrestige->SetAttribute("value", NumberToString(s.dwPrestige).c_str());
	pElem_dwPrestige->SetAttribute("comment", ToUTF8Ptr("声望"));
	if(rElement.LinkEndChild(pElem_dwPrestige.get()) != NULL)
		pElem_dwPrestige.release();
	unique_ptr<TiXmlElement> pElem_dwHonor(new TiXmlElement("UINT32"));
	if(pElem_dwHonor == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwHonor->SetAttribute("name", "dwHonor");
	pElem_dwHonor->SetAttribute("value", NumberToString(s.dwHonor).c_str());
	pElem_dwHonor->SetAttribute("comment", ToUTF8Ptr("荣誉"));
	if(rElement.LinkEndChild(pElem_dwHonor.get()) != NULL)
		pElem_dwHonor.release();
	unique_ptr<TiXmlElement> pElem_dwPExp(new TiXmlElement("UINT32"));
	if(pElem_dwPExp == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwPExp->SetAttribute("name", "dwPExp");
	pElem_dwPExp->SetAttribute("value", NumberToString(s.dwPExp).c_str());
	pElem_dwPExp->SetAttribute("comment", ToUTF8Ptr("修为"));
	if(rElement.LinkEndChild(pElem_dwPExp.get()) != NULL)
		pElem_dwPExp.release();
	unique_ptr<TiXmlElement> pElem_dwSigil(new TiXmlElement("UINT32"));
	if(pElem_dwSigil == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwSigil->SetAttribute("name", "dwSigil");
	pElem_dwSigil->SetAttribute("value", NumberToString(s.dwSigil).c_str());
	pElem_dwSigil->SetAttribute("comment", ToUTF8Ptr("符印"));
	if(rElement.LinkEndChild(pElem_dwSigil.get()) != NULL)
		pElem_dwSigil.release();
	unique_ptr<TiXmlElement> pElem_dwCentsY(new TiXmlElement("UINT32"));
	if(pElem_dwCentsY == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwCentsY->SetAttribute("name", "dwCentsY");
	pElem_dwCentsY->SetAttribute("value", NumberToString(s.dwCentsY).c_str());
	pElem_dwCentsY->SetAttribute("comment", ToUTF8Ptr("仙元"));
	if(rElement.LinkEndChild(pElem_dwCentsY.get()) != NULL)
		pElem_dwCentsY.release();
	unique_ptr<TiXmlElement> pElem_dwAction(new TiXmlElement("UINT32"));
	if(pElem_dwAction == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwAction->SetAttribute("name", "dwAction");
	pElem_dwAction->SetAttribute("value", NumberToString(s.dwAction).c_str());
	pElem_dwAction->SetAttribute("comment", ToUTF8Ptr("体力"));
	if(rElement.LinkEndChild(pElem_dwAction.get()) != NULL)
		pElem_dwAction.release();
	unique_ptr<TiXmlElement> pElem_dwSop(new TiXmlElement("UINT32"));
	if(pElem_dwSop == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwSop->SetAttribute("name", "dwSop");
	pElem_dwSop->SetAttribute("value", NumberToString(s.dwSop).c_str());
	pElem_dwSop->SetAttribute("comment", ToUTF8Ptr("阅历"));
	if(rElement.LinkEndChild(pElem_dwSop.get()) != NULL)
		pElem_dwSop.release();
	unique_ptr<TiXmlElement> pElem_dwPoten(new TiXmlElement("UINT32"));
	if(pElem_dwPoten == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwPoten->SetAttribute("name", "dwPoten");
	pElem_dwPoten->SetAttribute("value", NumberToString(s.dwPoten).c_str());
	pElem_dwPoten->SetAttribute("comment", ToUTF8Ptr("潜能"));
	if(rElement.LinkEndChild(pElem_dwPoten.get()) != NULL)
		pElem_dwPoten.release();
	unique_ptr<TiXmlElement> pElem_dwReiki(new TiXmlElement("UINT32"));
	if(pElem_dwReiki == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwReiki->SetAttribute("name", "dwReiki");
	pElem_dwReiki->SetAttribute("value", NumberToString(s.dwReiki).c_str());
	pElem_dwReiki->SetAttribute("comment", ToUTF8Ptr("灵力"));
	if(rElement.LinkEndChild(pElem_dwReiki.get()) != NULL)
		pElem_dwReiki.release();
	unique_ptr<TiXmlElement> pElem_dwDemonSoul(new TiXmlElement("UINT32"));
	if(pElem_dwDemonSoul == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwDemonSoul->SetAttribute("name", "dwDemonSoul");
	pElem_dwDemonSoul->SetAttribute("value", NumberToString(s.dwDemonSoul).c_str());
	pElem_dwDemonSoul->SetAttribute("comment", ToUTF8Ptr("锁妖塔魂值"));
	if(rElement.LinkEndChild(pElem_dwDemonSoul.get()) != NULL)
		pElem_dwDemonSoul.release();
	unique_ptr<TiXmlElement> pElem_dwSoulAttack(new TiXmlElement("UINT32"));
	if(pElem_dwSoulAttack == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwSoulAttack->SetAttribute("name", "dwSoulAttack");
	pElem_dwSoulAttack->SetAttribute("value", NumberToString(s.dwSoulAttack).c_str());
	pElem_dwSoulAttack->SetAttribute("comment", ToUTF8Ptr("攻击之魂"));
	if(rElement.LinkEndChild(pElem_dwSoulAttack.get()) != NULL)
		pElem_dwSoulAttack.release();
	unique_ptr<TiXmlElement> pElem_dwSoulHp(new TiXmlElement("UINT32"));
	if(pElem_dwSoulHp == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwSoulHp->SetAttribute("name", "dwSoulHp");
	pElem_dwSoulHp->SetAttribute("value", NumberToString(s.dwSoulHp).c_str());
	pElem_dwSoulHp->SetAttribute("comment", ToUTF8Ptr("生命之魂"));
	if(rElement.LinkEndChild(pElem_dwSoulHp.get()) != NULL)
		pElem_dwSoulHp.release();
	unique_ptr<TiXmlElement> pElem_dwSoulCritical(new TiXmlElement("UINT32"));
	if(pElem_dwSoulCritical == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwSoulCritical->SetAttribute("name", "dwSoulCritical");
	pElem_dwSoulCritical->SetAttribute("value", NumberToString(s.dwSoulCritical).c_str());
	pElem_dwSoulCritical->SetAttribute("comment", ToUTF8Ptr("暴击之魂"));
	if(rElement.LinkEndChild(pElem_dwSoulCritical.get()) != NULL)
		pElem_dwSoulCritical.release();
	unique_ptr<TiXmlElement> pElem_dwSoulCounter(new TiXmlElement("UINT32"));
	if(pElem_dwSoulCounter == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwSoulCounter->SetAttribute("name", "dwSoulCounter");
	pElem_dwSoulCounter->SetAttribute("value", NumberToString(s.dwSoulCounter).c_str());
	pElem_dwSoulCounter->SetAttribute("comment", ToUTF8Ptr("反击之魂"));
	if(rElement.LinkEndChild(pElem_dwSoulCounter.get()) != NULL)
		pElem_dwSoulCounter.release();
	unique_ptr<TiXmlElement> pElem_dwSoulSpeed(new TiXmlElement("UINT32"));
	if(pElem_dwSoulSpeed == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwSoulSpeed->SetAttribute("name", "dwSoulSpeed");
	pElem_dwSoulSpeed->SetAttribute("value", NumberToString(s.dwSoulSpeed).c_str());
	pElem_dwSoulSpeed->SetAttribute("comment", ToUTF8Ptr("身法之魂"));
	if(rElement.LinkEndChild(pElem_dwSoulSpeed.get()) != NULL)
		pElem_dwSoulSpeed.release();
	unique_ptr<TiXmlElement> pElem_dwSoulDefence(new TiXmlElement("UINT32"));
	if(pElem_dwSoulDefence == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwSoulDefence->SetAttribute("name", "dwSoulDefence");
	pElem_dwSoulDefence->SetAttribute("value", NumberToString(s.dwSoulDefence).c_str());
	pElem_dwSoulDefence->SetAttribute("comment", ToUTF8Ptr("防御之魂"));
	if(rElement.LinkEndChild(pElem_dwSoulDefence.get()) != NULL)
		pElem_dwSoulDefence.release();
	unique_ptr<TiXmlElement> pElem_dwSoulHit(new TiXmlElement("UINT32"));
	if(pElem_dwSoulHit == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwSoulHit->SetAttribute("name", "dwSoulHit");
	pElem_dwSoulHit->SetAttribute("value", NumberToString(s.dwSoulHit).c_str());
	pElem_dwSoulHit->SetAttribute("comment", ToUTF8Ptr("命中之魂"));
	if(rElement.LinkEndChild(pElem_dwSoulHit.get()) != NULL)
		pElem_dwSoulHit.release();
	unique_ptr<TiXmlElement> pElem_dwSoulDodge(new TiXmlElement("UINT32"));
	if(pElem_dwSoulDodge == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwSoulDodge->SetAttribute("name", "dwSoulDodge");
	pElem_dwSoulDodge->SetAttribute("value", NumberToString(s.dwSoulDodge).c_str());
	pElem_dwSoulDodge->SetAttribute("comment", ToUTF8Ptr("闪避之魂"));
	if(rElement.LinkEndChild(pElem_dwSoulDodge.get()) != NULL)
		pElem_dwSoulDodge.release();
	unique_ptr<TiXmlElement> pElem_dwStampHuang(new TiXmlElement("UINT32"));
	if(pElem_dwStampHuang == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwStampHuang->SetAttribute("name", "dwStampHuang");
	pElem_dwStampHuang->SetAttribute("value", NumberToString(s.dwStampHuang).c_str());
	pElem_dwStampHuang->SetAttribute("comment", ToUTF8Ptr("黄阶除魔印"));
	if(rElement.LinkEndChild(pElem_dwStampHuang.get()) != NULL)
		pElem_dwStampHuang.release();
	unique_ptr<TiXmlElement> pElem_dwStampXuan(new TiXmlElement("UINT32"));
	if(pElem_dwStampXuan == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwStampXuan->SetAttribute("name", "dwStampXuan");
	pElem_dwStampXuan->SetAttribute("value", NumberToString(s.dwStampXuan).c_str());
	pElem_dwStampXuan->SetAttribute("comment", ToUTF8Ptr("玄阶除魔印"));
	if(rElement.LinkEndChild(pElem_dwStampXuan.get()) != NULL)
		pElem_dwStampXuan.release();
	unique_ptr<TiXmlElement> pElem_dwStampDi(new TiXmlElement("UINT32"));
	if(pElem_dwStampDi == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwStampDi->SetAttribute("name", "dwStampDi");
	pElem_dwStampDi->SetAttribute("value", NumberToString(s.dwStampDi).c_str());
	pElem_dwStampDi->SetAttribute("comment", ToUTF8Ptr("地阶除魔印"));
	if(rElement.LinkEndChild(pElem_dwStampDi.get()) != NULL)
		pElem_dwStampDi.release();
	unique_ptr<TiXmlElement> pElem_dwStampTian(new TiXmlElement("UINT32"));
	if(pElem_dwStampTian == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwStampTian->SetAttribute("name", "dwStampTian");
	pElem_dwStampTian->SetAttribute("value", NumberToString(s.dwStampTian).c_str());
	pElem_dwStampTian->SetAttribute("comment", ToUTF8Ptr("天阶除魔印"));
	if(rElement.LinkEndChild(pElem_dwStampTian.get()) != NULL)
		pElem_dwStampTian.release();
	unique_ptr<TiXmlElement> pElem_dwStampXing(new TiXmlElement("UINT32"));
	if(pElem_dwStampXing == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwStampXing->SetAttribute("name", "dwStampXing");
	pElem_dwStampXing->SetAttribute("value", NumberToString(s.dwStampXing).c_str());
	pElem_dwStampXing->SetAttribute("comment", ToUTF8Ptr("星阶除魔印"));
	if(rElement.LinkEndChild(pElem_dwStampXing.get()) != NULL)
		pElem_dwStampXing.release();
	unique_ptr<TiXmlElement> pElem_dwStampYue(new TiXmlElement("UINT32"));
	if(pElem_dwStampYue == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwStampYue->SetAttribute("name", "dwStampYue");
	pElem_dwStampYue->SetAttribute("value", NumberToString(s.dwStampYue).c_str());
	pElem_dwStampYue->SetAttribute("comment", ToUTF8Ptr("月阶除魔印"));
	if(rElement.LinkEndChild(pElem_dwStampYue.get()) != NULL)
		pElem_dwStampYue.release();
	unique_ptr<TiXmlElement> pElem_dwStampDi2(new TiXmlElement("UINT32"));
	if(pElem_dwStampDi2 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwStampDi2->SetAttribute("name", "dwStampDi2");
	pElem_dwStampDi2->SetAttribute("value", NumberToString(s.dwStampDi2).c_str());
	pElem_dwStampDi2->SetAttribute("comment", ToUTF8Ptr("帝阶除魔印"));
	if(rElement.LinkEndChild(pElem_dwStampDi2.get()) != NULL)
		pElem_dwStampDi2.release();
	unique_ptr<TiXmlElement> pElem_dwStampXian(new TiXmlElement("UINT32"));
	if(pElem_dwStampXian == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwStampXian->SetAttribute("name", "dwStampXian");
	pElem_dwStampXian->SetAttribute("value", NumberToString(s.dwStampXian).c_str());
	pElem_dwStampXian->SetAttribute("comment", ToUTF8Ptr("仙阶除魔印"));
	if(rElement.LinkEndChild(pElem_dwStampXian.get()) != NULL)
		pElem_dwStampXian.release();
	unique_ptr<TiXmlElement> pElem_dwStampSheng(new TiXmlElement("UINT32"));
	if(pElem_dwStampSheng == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwStampSheng->SetAttribute("name", "dwStampSheng");
	pElem_dwStampSheng->SetAttribute("value", NumberToString(s.dwStampSheng).c_str());
	pElem_dwStampSheng->SetAttribute("comment", ToUTF8Ptr("圣阶除魔印"));
	if(rElement.LinkEndChild(pElem_dwStampSheng.get()) != NULL)
		pElem_dwStampSheng.release();
	unique_ptr<TiXmlElement> pElem_dwStampFo(new TiXmlElement("UINT32"));
	if(pElem_dwStampFo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwStampFo->SetAttribute("name", "dwStampFo");
	pElem_dwStampFo->SetAttribute("value", NumberToString(s.dwStampFo).c_str());
	pElem_dwStampFo->SetAttribute("comment", ToUTF8Ptr("佛阶除魔印"));
	if(rElement.LinkEndChild(pElem_dwStampFo.get()) != NULL)
		pElem_dwStampFo.release();
	unique_ptr<TiXmlElement> pElem_dwBTPoint(new TiXmlElement("UINT32"));
	if(pElem_dwBTPoint == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwBTPoint->SetAttribute("name", "dwBTPoint");
	pElem_dwBTPoint->SetAttribute("value", NumberToString(s.dwBTPoint).c_str());
	pElem_dwBTPoint->SetAttribute("comment", ToUTF8Ptr("战斗力"));
	if(rElement.LinkEndChild(pElem_dwBTPoint.get()) != NULL)
		pElem_dwBTPoint.release();
	unique_ptr<TiXmlElement> pElem_dwBlueFairyFate(new TiXmlElement("UINT32"));
	if(pElem_dwBlueFairyFate == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwBlueFairyFate->SetAttribute("name", "dwBlueFairyFate");
	pElem_dwBlueFairyFate->SetAttribute("value", NumberToString(s.dwBlueFairyFate).c_str());
	pElem_dwBlueFairyFate->SetAttribute("comment", ToUTF8Ptr("蓝色仙缘"));
	if(rElement.LinkEndChild(pElem_dwBlueFairyFate.get()) != NULL)
		pElem_dwBlueFairyFate.release();
	unique_ptr<TiXmlElement> pElem_dwPurpleFairyFate(new TiXmlElement("UINT32"));
	if(pElem_dwPurpleFairyFate == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwPurpleFairyFate->SetAttribute("name", "dwPurpleFairyFate");
	pElem_dwPurpleFairyFate->SetAttribute("value", NumberToString(s.dwPurpleFairyFate).c_str());
	pElem_dwPurpleFairyFate->SetAttribute("comment", ToUTF8Ptr("紫色仙缘"));
	if(rElement.LinkEndChild(pElem_dwPurpleFairyFate.get()) != NULL)
		pElem_dwPurpleFairyFate.release();
	unique_ptr<TiXmlElement> pElem_dwOrangeFairyFate(new TiXmlElement("UINT32"));
	if(pElem_dwOrangeFairyFate == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwOrangeFairyFate->SetAttribute("name", "dwOrangeFairyFate");
	pElem_dwOrangeFairyFate->SetAttribute("value", NumberToString(s.dwOrangeFairyFate).c_str());
	pElem_dwOrangeFairyFate->SetAttribute("comment", ToUTF8Ptr("橙色仙缘"));
	if(rElement.LinkEndChild(pElem_dwOrangeFairyFate.get()) != NULL)
		pElem_dwOrangeFairyFate.release();
	unique_ptr<TiXmlElement> pElem_dwTotalRecharge(new TiXmlElement("UINT32"));
	if(pElem_dwTotalRecharge == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwTotalRecharge->SetAttribute("name", "dwTotalRecharge");
	pElem_dwTotalRecharge->SetAttribute("value", NumberToString(s.dwTotalRecharge).c_str());
	pElem_dwTotalRecharge->SetAttribute("comment", ToUTF8Ptr("总充值数"));
	if(rElement.LinkEndChild(pElem_dwTotalRecharge.get()) != NULL)
		pElem_dwTotalRecharge.release();
	unique_ptr<TiXmlElement> pElem_vecOwnTitle(new TiXmlElement("TVecUINT16"));
	if(pElem_vecOwnTitle == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecOwnTitle->SetAttribute("name", "vecOwnTitle");
	string strText_vecOwnTitle;
	for(size_t i = 0; i < s.vecOwnTitle.size(); ++i)
	{
		if(i > 0)
			strText_vecOwnTitle += ", ";
		strText_vecOwnTitle += NumberToString(s.vecOwnTitle[i]);
	}
	unique_ptr<TiXmlText> pText_vecOwnTitle(new TiXmlText(strText_vecOwnTitle.c_str()));
	if(pText_vecOwnTitle == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(pElem_vecOwnTitle->LinkEndChild(pText_vecOwnTitle.get()) != NULL)
		pText_vecOwnTitle.release();
	pElem_vecOwnTitle->SetAttribute("comment", ToUTF8Ptr("拥有称号"));
	if(rElement.LinkEndChild(pElem_vecOwnTitle.get()) != NULL)
		pElem_vecOwnTitle.release();
	unique_ptr<TiXmlElement> pElem_vecEquipTitle(new TiXmlElement("TVecUINT16"));
	if(pElem_vecEquipTitle == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecEquipTitle->SetAttribute("name", "vecEquipTitle");
	string strText_vecEquipTitle;
	for(size_t i = 0; i < s.vecEquipTitle.size(); ++i)
	{
		if(i > 0)
			strText_vecEquipTitle += ", ";
		strText_vecEquipTitle += NumberToString(s.vecEquipTitle[i]);
	}
	unique_ptr<TiXmlText> pText_vecEquipTitle(new TiXmlText(strText_vecEquipTitle.c_str()));
	if(pText_vecEquipTitle == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(pElem_vecEquipTitle->LinkEndChild(pText_vecEquipTitle.get()) != NULL)
		pText_vecEquipTitle.release();
	pElem_vecEquipTitle->SetAttribute("comment", ToUTF8Ptr("装备称号"));
	if(rElement.LinkEndChild(pElem_vecEquipTitle.get()) != NULL)
		pElem_vecEquipTitle.release();
	unique_ptr<TiXmlElement> pElem_strGuide(new TiXmlElement("string"));
	if(pElem_strGuide == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strGuide->SetAttribute("name", "strGuide");
	pElem_strGuide->SetAttribute("value", s.strGuide.c_str());
	pElem_strGuide->SetAttribute("comment", ToUTF8Ptr("新手引导信息"));
	if(rElement.LinkEndChild(pElem_strGuide.get()) != NULL)
		pElem_strGuide.release();
	unique_ptr<TiXmlElement> pElem_byWallow(new TiXmlElement("UINT8"));
	if(pElem_byWallow == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byWallow->SetAttribute("name", "byWallow");
	pElem_byWallow->SetAttribute("value", NumberToString(s.byWallow).c_str());
	pElem_byWallow->SetAttribute("comment", ToUTF8Ptr("防沉迷"));
	if(rElement.LinkEndChild(pElem_byWallow.get()) != NULL)
		pElem_byWallow.release();
	unique_ptr<TiXmlElement> pElem_vecIconAppear(new TiXmlElement("TVecUINT16"));
	if(pElem_vecIconAppear == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecIconAppear->SetAttribute("name", "vecIconAppear");
	string strText_vecIconAppear;
	for(size_t i = 0; i < s.vecIconAppear.size(); ++i)
	{
		if(i > 0)
			strText_vecIconAppear += ", ";
		strText_vecIconAppear += NumberToString(s.vecIconAppear[i]);
	}
	unique_ptr<TiXmlText> pText_vecIconAppear(new TiXmlText(strText_vecIconAppear.c_str()));
	if(pText_vecIconAppear == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(pElem_vecIconAppear->LinkEndChild(pText_vecIconAppear.get()) != NULL)
		pText_vecIconAppear.release();
	pElem_vecIconAppear->SetAttribute("comment", ToUTF8Ptr("Icon开启"));
	if(rElement.LinkEndChild(pElem_vecIconAppear.get()) != NULL)
		pElem_vecIconAppear.release();
	unique_ptr<TiXmlElement> pElem_vecIconDel(new TiXmlElement("TVecUINT16"));
	if(pElem_vecIconDel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecIconDel->SetAttribute("name", "vecIconDel");
	string strText_vecIconDel;
	for(size_t i = 0; i < s.vecIconDel.size(); ++i)
	{
		if(i > 0)
			strText_vecIconDel += ", ";
		strText_vecIconDel += NumberToString(s.vecIconDel[i]);
	}
	unique_ptr<TiXmlText> pText_vecIconDel(new TiXmlText(strText_vecIconDel.c_str()));
	if(pText_vecIconDel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(pElem_vecIconDel->LinkEndChild(pText_vecIconDel.get()) != NULL)
		pText_vecIconDel.release();
	pElem_vecIconDel->SetAttribute("comment", ToUTF8Ptr("Icon关闭"));
	if(rElement.LinkEndChild(pElem_vecIconDel.get()) != NULL)
		pElem_vecIconDel.release();
	unique_ptr<TiXmlElement> pElem_dwDemonTowerFloorID(new TiXmlElement("UINT32"));
	if(pElem_dwDemonTowerFloorID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwDemonTowerFloorID->SetAttribute("name", "dwDemonTowerFloorID");
	pElem_dwDemonTowerFloorID->SetAttribute("value", NumberToString(s.dwDemonTowerFloorID).c_str());
	pElem_dwDemonTowerFloorID->SetAttribute("comment", ToUTF8Ptr("通关镇妖塔层数"));
	if(rElement.LinkEndChild(pElem_dwDemonTowerFloorID.get()) != NULL)
		pElem_dwDemonTowerFloorID.release();
	unique_ptr<TiXmlElement> pElem_dwDemonTowerPrizeFloorID(new TiXmlElement("UINT32"));
	if(pElem_dwDemonTowerPrizeFloorID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwDemonTowerPrizeFloorID->SetAttribute("name", "dwDemonTowerPrizeFloorID");
	pElem_dwDemonTowerPrizeFloorID->SetAttribute("value", NumberToString(s.dwDemonTowerPrizeFloorID).c_str());
	pElem_dwDemonTowerPrizeFloorID->SetAttribute("comment", ToUTF8Ptr("镇妖塔领奖层数"));
	if(rElement.LinkEndChild(pElem_dwDemonTowerPrizeFloorID.get()) != NULL)
		pElem_dwDemonTowerPrizeFloorID.release();
	unique_ptr<TiXmlElement> pElem_dwCreateTime(new TiXmlElement("UINT32"));
	if(pElem_dwCreateTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwCreateTime->SetAttribute("name", "dwCreateTime");
	pElem_dwCreateTime->SetAttribute("value", NumberToString(s.dwCreateTime).c_str());
	pElem_dwCreateTime->SetAttribute("comment", ToUTF8Ptr("玩家创角时间"));
	if(rElement.LinkEndChild(pElem_dwCreateTime.get()) != NULL)
		pElem_dwCreateTime.release();
	return true;
}

#endif

RoleEnterGameData::RoleEnterGameData() : byIsUser(0) { }

RoleEnterGameData::RoleEnterGameData(UINT8 byIsUser_, const PlayerBaseData& sBaseInfo_) : byIsUser(byIsUser_), sBaseInfo(sBaseInfo_) { }

RoleEnterGameData::RoleEnterGameData(RoleEnterGameData&& src) : byIsUser(src.byIsUser), sBaseInfo(move(src.sBaseInfo)) { }

RoleEnterGameData& RoleEnterGameData::operator=(RoleEnterGameData&& rhs)
{
	if(this != &rhs)
	{
		this->~RoleEnterGameData();
		new (this) RoleEnterGameData(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, RoleEnterGameData& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.byIsUser;
	src >> s.sBaseInfo;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const RoleEnterGameData& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.byIsUser;
	src << s.sBaseInfo;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, RoleEnterGameData& s)
{
	if(strcmp(rElement.Value(), "RoleEnterGameData") != 0)
	{
		LOG_CRI << "rElement is not RoleEnterGameData!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byIsUser is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byIsUser") != 0)
	{
		LOG_CRI << "Attribute: name is not byIsUser!";
		return false;
	}
	const char* pszVal_byIsUser = pElemChild->Attribute("value");
	if(pszVal_byIsUser == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byIsUser, s.byIsUser))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for sBaseInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "PlayerBaseData") != 0)
	{
		LOG_CRI << "pElemChild is not PlayerBaseData!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "sBaseInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not sBaseInfo!";
		return false;
	}
	if(!FromXML(*pElemChild, s.sBaseInfo))
	{
		LOG_CRI << "FromXML for: sBaseInfo fails!";
		return false;
	}
	return true;
}

bool ToXML(const RoleEnterGameData& s, TiXmlElement& rElement)
{
	rElement.SetValue("RoleEnterGameData");
	rElement.SetAttribute("type", ToUTF8Ptr("查询角色消息"));
	unique_ptr<TiXmlElement> pElem_byIsUser(new TiXmlElement("UINT8"));
	if(pElem_byIsUser == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byIsUser->SetAttribute("name", "byIsUser");
	pElem_byIsUser->SetAttribute("value", NumberToString(s.byIsUser).c_str());
	pElem_byIsUser->SetAttribute("comment", ToUTF8Ptr("0表示不存在"));
	if(rElement.LinkEndChild(pElem_byIsUser.get()) != NULL)
		pElem_byIsUser.release();
	unique_ptr<TiXmlElement> pElem_sBaseInfo(new TiXmlElement("PlayerBaseData"));
	if(pElem_sBaseInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_sBaseInfo->SetAttribute("name", "sBaseInfo");
	if(!ToXML(s.sBaseInfo, *pElem_sBaseInfo))
	{
		LOG_CRI << "sBaseInfo ToXML fails!";
		return false;
	}
	pElem_sBaseInfo->SetAttribute("comment", ToUTF8Ptr("基础信息"));
	if(rElement.LinkEndChild(pElem_sBaseInfo.get()) != NULL)
		pElem_sBaseInfo.release();
	return true;
}

#endif

SCreateRoleInfo::SCreateRoleInfo() : eCareer((NProtoCommon::ECareerType)0), eSex((NProtoCommon::ESexType)0) { }

SCreateRoleInfo::SCreateRoleInfo(const std::string& strName_, NProtoCommon::ECareerType eCareer_, NProtoCommon::ESexType eSex_, const std::string& strInviteRoleID_, const std::string& strIP_)
			: strName(strName_), eCareer(eCareer_), eSex(eSex_), strInviteRoleID(strInviteRoleID_), strIP(strIP_) { }

SCreateRoleInfo::SCreateRoleInfo(SCreateRoleInfo&& src) : strName(move(src.strName)), eCareer(src.eCareer), eSex(src.eSex), strInviteRoleID(move(src.strInviteRoleID)), strIP(move(src.strIP)) { }

SCreateRoleInfo& SCreateRoleInfo::operator=(SCreateRoleInfo&& rhs)
{
	if(this != &rhs)
	{
		this->~SCreateRoleInfo();
		new (this) SCreateRoleInfo(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SCreateRoleInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.strName;
	src >> (UINT8&)s.eCareer;
	src >> (UINT8&)s.eSex;
	src >> s.strInviteRoleID;
	src >> s.strIP;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SCreateRoleInfo& s)
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
	src << (UINT8&)s.eCareer;
	src << (UINT8&)s.eSex;
	src << s.strInviteRoleID;
	src << s.strIP;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SCreateRoleInfo& s)
{
	if(strcmp(rElement.Value(), "SCreateRoleInfo") != 0)
	{
		LOG_CRI << "rElement is not SCreateRoleInfo!";
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
		LOG_CRI << "pElemChild for eCareer is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "ProtoCommon::ECareerType") != 0)
	{
		LOG_CRI << "pElemChild is not ProtoCommon::ECareerType!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eCareer") != 0)
	{
		LOG_CRI << "Attribute: name is not eCareer!";
		return false;
	}
	const char* pszVal_eCareer = pElemChild->Attribute("value");
	if(pszVal_eCareer == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!NProtoCommon::EnumStrToVal(pszVal_eCareer, s.eCareer))
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
		LOG_CRI << "pElemChild for strInviteRoleID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strInviteRoleID") != 0)
	{
		LOG_CRI << "Attribute: name is not strInviteRoleID!";
		return false;
	}
	const char* pszVal_strInviteRoleID = pElemChild->Attribute("value");
	if(pszVal_strInviteRoleID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strInviteRoleID = pszVal_strInviteRoleID;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strIP is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strIP") != 0)
	{
		LOG_CRI << "Attribute: name is not strIP!";
		return false;
	}
	const char* pszVal_strIP = pElemChild->Attribute("value");
	if(pszVal_strIP == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strIP = pszVal_strIP;
	return true;
}

bool ToXML(const SCreateRoleInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SCreateRoleInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("角色信息"));
	unique_ptr<TiXmlElement> pElem_strName(new TiXmlElement("string"));
	if(pElem_strName == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strName->SetAttribute("name", "strName");
	pElem_strName->SetAttribute("value", s.strName.c_str());
	pElem_strName->SetAttribute("comment", ToUTF8Ptr("角色名"));
	if(rElement.LinkEndChild(pElem_strName.get()) != NULL)
		pElem_strName.release();
	unique_ptr<TiXmlElement> pElem_eCareer(new TiXmlElement("ProtoCommon::ECareerType"));
	if(pElem_eCareer == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eCareer->SetAttribute("name", "eCareer");
	const char* pszEnum_eCareer = NProtoCommon::EnumValToStr(s.eCareer);
	if(pszEnum_eCareer == NULL)
	{
		LOG_CRI << "EnumValToStr for eCareer fails!";
		return false;
	}
	pElem_eCareer->SetAttribute("value", pszEnum_eCareer);
	pElem_eCareer->SetAttribute("comment", ToUTF8Ptr("职业"));
	if(rElement.LinkEndChild(pElem_eCareer.get()) != NULL)
		pElem_eCareer.release();
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
	unique_ptr<TiXmlElement> pElem_strInviteRoleID(new TiXmlElement("string"));
	if(pElem_strInviteRoleID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strInviteRoleID->SetAttribute("name", "strInviteRoleID");
	pElem_strInviteRoleID->SetAttribute("value", s.strInviteRoleID.c_str());
	pElem_strInviteRoleID->SetAttribute("comment", ToUTF8Ptr("好友邀请id"));
	if(rElement.LinkEndChild(pElem_strInviteRoleID.get()) != NULL)
		pElem_strInviteRoleID.release();
	unique_ptr<TiXmlElement> pElem_strIP(new TiXmlElement("string"));
	if(pElem_strIP == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strIP->SetAttribute("name", "strIP");
	pElem_strIP->SetAttribute("value", s.strIP.c_str());
	pElem_strIP->SetAttribute("comment", ToUTF8Ptr("创角时ip"));
	if(rElement.LinkEndChild(pElem_strIP.get()) != NULL)
		pElem_strIP.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecCreateRoleInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SCreateRoleInfo s;
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

bool VectorToXML(const TVecCreateRoleInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SCreateRoleInfo"));
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

SEnterParam::SEnterParam() : byPtType((NProtoCommon::EPtType)0), byQQPtType((NProtoCommon::EQQPtType)0), byQQPtLv(0), byQQPtYearType(0), byQQPtLuxuryType(0) { }

SEnterParam::SEnterParam(NProtoCommon::EPtType byPtType_, NProtoCommon::EQQPtType byQQPtType_, UINT8 byQQPtLv_, UINT8 byQQPtYearType_, UINT8 byQQPtLuxuryType_, 
			const std::string& customPar1_, const std::string& customPar2_, const std::string& strOpenId_, const std::string& strOpenKey_)
			: byPtType(byPtType_), byQQPtType(byQQPtType_), byQQPtLv(byQQPtLv_), byQQPtYearType(byQQPtYearType_), byQQPtLuxuryType(byQQPtLuxuryType_), 
			customPar1(customPar1_), customPar2(customPar2_), strOpenId(strOpenId_), strOpenKey(strOpenKey_) { }

SEnterParam::SEnterParam(SEnterParam&& src) : byPtType(src.byPtType), byQQPtType(src.byQQPtType), byQQPtLv(src.byQQPtLv), byQQPtYearType(src.byQQPtYearType), byQQPtLuxuryType(src.byQQPtLuxuryType), 
			customPar1(move(src.customPar1)), customPar2(move(src.customPar2)), strOpenId(move(src.strOpenId)), strOpenKey(move(src.strOpenKey)) { }

SEnterParam& SEnterParam::operator=(SEnterParam&& rhs)
{
	if(this != &rhs)
	{
		this->~SEnterParam();
		new (this) SEnterParam(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SEnterParam& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (UINT8&)s.byPtType;
	src >> (UINT8&)s.byQQPtType;
	src >> s.byQQPtLv;
	src >> s.byQQPtYearType;
	src >> s.byQQPtLuxuryType;
	src >> s.customPar1;
	src >> s.customPar2;
	src >> s.strOpenId;
	src >> s.strOpenKey;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SEnterParam& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (UINT8&)s.byPtType;
	src << (UINT8&)s.byQQPtType;
	src << s.byQQPtLv;
	src << s.byQQPtYearType;
	src << s.byQQPtLuxuryType;
	src << s.customPar1;
	src << s.customPar2;
	src << s.strOpenId;
	src << s.strOpenKey;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SEnterParam& s)
{
	if(strcmp(rElement.Value(), "SEnterParam") != 0)
	{
		LOG_CRI << "rElement is not SEnterParam!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byPtType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "ProtoCommon::EPtType") != 0)
	{
		LOG_CRI << "pElemChild is not ProtoCommon::EPtType!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byPtType") != 0)
	{
		LOG_CRI << "Attribute: name is not byPtType!";
		return false;
	}
	const char* pszVal_byPtType = pElemChild->Attribute("value");
	if(pszVal_byPtType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!NProtoCommon::EnumStrToVal(pszVal_byPtType, s.byPtType))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byQQPtType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "ProtoCommon::EQQPtType") != 0)
	{
		LOG_CRI << "pElemChild is not ProtoCommon::EQQPtType!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byQQPtType") != 0)
	{
		LOG_CRI << "Attribute: name is not byQQPtType!";
		return false;
	}
	const char* pszVal_byQQPtType = pElemChild->Attribute("value");
	if(pszVal_byQQPtType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!NProtoCommon::EnumStrToVal(pszVal_byQQPtType, s.byQQPtType))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byQQPtLv is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byQQPtLv") != 0)
	{
		LOG_CRI << "Attribute: name is not byQQPtLv!";
		return false;
	}
	const char* pszVal_byQQPtLv = pElemChild->Attribute("value");
	if(pszVal_byQQPtLv == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byQQPtLv, s.byQQPtLv))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byQQPtYearType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byQQPtYearType") != 0)
	{
		LOG_CRI << "Attribute: name is not byQQPtYearType!";
		return false;
	}
	const char* pszVal_byQQPtYearType = pElemChild->Attribute("value");
	if(pszVal_byQQPtYearType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byQQPtYearType, s.byQQPtYearType))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byQQPtLuxuryType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byQQPtLuxuryType") != 0)
	{
		LOG_CRI << "Attribute: name is not byQQPtLuxuryType!";
		return false;
	}
	const char* pszVal_byQQPtLuxuryType = pElemChild->Attribute("value");
	if(pszVal_byQQPtLuxuryType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byQQPtLuxuryType, s.byQQPtLuxuryType))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for customPar1 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "customPar1") != 0)
	{
		LOG_CRI << "Attribute: name is not customPar1!";
		return false;
	}
	const char* pszVal_customPar1 = pElemChild->Attribute("value");
	if(pszVal_customPar1 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.customPar1 = pszVal_customPar1;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for customPar2 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "customPar2") != 0)
	{
		LOG_CRI << "Attribute: name is not customPar2!";
		return false;
	}
	const char* pszVal_customPar2 = pElemChild->Attribute("value");
	if(pszVal_customPar2 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.customPar2 = pszVal_customPar2;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strOpenId is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strOpenId") != 0)
	{
		LOG_CRI << "Attribute: name is not strOpenId!";
		return false;
	}
	const char* pszVal_strOpenId = pElemChild->Attribute("value");
	if(pszVal_strOpenId == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strOpenId = pszVal_strOpenId;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strOpenKey is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strOpenKey") != 0)
	{
		LOG_CRI << "Attribute: name is not strOpenKey!";
		return false;
	}
	const char* pszVal_strOpenKey = pElemChild->Attribute("value");
	if(pszVal_strOpenKey == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strOpenKey = pszVal_strOpenKey;
	return true;
}

bool ToXML(const SEnterParam& s, TiXmlElement& rElement)
{
	rElement.SetValue("SEnterParam");
	rElement.SetAttribute("type", ToUTF8Ptr("角色信息"));
	unique_ptr<TiXmlElement> pElem_byPtType(new TiXmlElement("ProtoCommon::EPtType"));
	if(pElem_byPtType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byPtType->SetAttribute("name", "byPtType");
	const char* pszEnum_byPtType = NProtoCommon::EnumValToStr(s.byPtType);
	if(pszEnum_byPtType == NULL)
	{
		LOG_CRI << "EnumValToStr for byPtType fails!";
		return false;
	}
	pElem_byPtType->SetAttribute("value", pszEnum_byPtType);
	pElem_byPtType->SetAttribute("comment", ToUTF8Ptr("平台类型"));
	if(rElement.LinkEndChild(pElem_byPtType.get()) != NULL)
		pElem_byPtType.release();
	unique_ptr<TiXmlElement> pElem_byQQPtType(new TiXmlElement("ProtoCommon::EQQPtType"));
	if(pElem_byQQPtType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byQQPtType->SetAttribute("name", "byQQPtType");
	const char* pszEnum_byQQPtType = NProtoCommon::EnumValToStr(s.byQQPtType);
	if(pszEnum_byQQPtType == NULL)
	{
		LOG_CRI << "EnumValToStr for byQQPtType fails!";
		return false;
	}
	pElem_byQQPtType->SetAttribute("value", pszEnum_byQQPtType);
	pElem_byQQPtType->SetAttribute("comment", ToUTF8Ptr("QQ平台类型"));
	if(rElement.LinkEndChild(pElem_byQQPtType.get()) != NULL)
		pElem_byQQPtType.release();
	unique_ptr<TiXmlElement> pElem_byQQPtLv(new TiXmlElement("UINT8"));
	if(pElem_byQQPtLv == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byQQPtLv->SetAttribute("name", "byQQPtLv");
	pElem_byQQPtLv->SetAttribute("value", NumberToString(s.byQQPtLv).c_str());
	pElem_byQQPtLv->SetAttribute("comment", ToUTF8Ptr("QQ平台类型等级"));
	if(rElement.LinkEndChild(pElem_byQQPtLv.get()) != NULL)
		pElem_byQQPtLv.release();
	unique_ptr<TiXmlElement> pElem_byQQPtYearType(new TiXmlElement("UINT8"));
	if(pElem_byQQPtYearType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byQQPtYearType->SetAttribute("name", "byQQPtYearType");
	pElem_byQQPtYearType->SetAttribute("value", NumberToString(s.byQQPtYearType).c_str());
	pElem_byQQPtYearType->SetAttribute("comment", ToUTF8Ptr("是否年费"));
	if(rElement.LinkEndChild(pElem_byQQPtYearType.get()) != NULL)
		pElem_byQQPtYearType.release();
	unique_ptr<TiXmlElement> pElem_byQQPtLuxuryType(new TiXmlElement("UINT8"));
	if(pElem_byQQPtLuxuryType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byQQPtLuxuryType->SetAttribute("name", "byQQPtLuxuryType");
	pElem_byQQPtLuxuryType->SetAttribute("value", NumberToString(s.byQQPtLuxuryType).c_str());
	pElem_byQQPtLuxuryType->SetAttribute("comment", ToUTF8Ptr("是否豪华"));
	if(rElement.LinkEndChild(pElem_byQQPtLuxuryType.get()) != NULL)
		pElem_byQQPtLuxuryType.release();
	unique_ptr<TiXmlElement> pElem_customPar1(new TiXmlElement("string"));
	if(pElem_customPar1 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_customPar1->SetAttribute("name", "customPar1");
	pElem_customPar1->SetAttribute("value", s.customPar1.c_str());
	pElem_customPar1->SetAttribute("comment", ToUTF8Ptr("广告主来源"));
	if(rElement.LinkEndChild(pElem_customPar1.get()) != NULL)
		pElem_customPar1.release();
	unique_ptr<TiXmlElement> pElem_customPar2(new TiXmlElement("string"));
	if(pElem_customPar2 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_customPar2->SetAttribute("name", "customPar2");
	pElem_customPar2->SetAttribute("value", s.customPar2.c_str());
	pElem_customPar2->SetAttribute("comment", ToUTF8Ptr("广告次来源"));
	if(rElement.LinkEndChild(pElem_customPar2.get()) != NULL)
		pElem_customPar2.release();
	unique_ptr<TiXmlElement> pElem_strOpenId(new TiXmlElement("string"));
	if(pElem_strOpenId == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strOpenId->SetAttribute("name", "strOpenId");
	pElem_strOpenId->SetAttribute("value", s.strOpenId.c_str());
	pElem_strOpenId->SetAttribute("comment", ToUTF8Ptr("openID"));
	if(rElement.LinkEndChild(pElem_strOpenId.get()) != NULL)
		pElem_strOpenId.release();
	unique_ptr<TiXmlElement> pElem_strOpenKey(new TiXmlElement("string"));
	if(pElem_strOpenKey == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strOpenKey->SetAttribute("name", "strOpenKey");
	pElem_strOpenKey->SetAttribute("value", s.strOpenKey.c_str());
	pElem_strOpenKey->SetAttribute("comment", ToUTF8Ptr("openKey"));
	if(rElement.LinkEndChild(pElem_strOpenKey.get()) != NULL)
		pElem_strOpenKey.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecEnterParam& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SEnterParam s;
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

bool VectorToXML(const TVecEnterParam& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SEnterParam"));
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

} //namespace NRoleEnterGameProt
