/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    ShipProt.cpp
//  Purpose:      元江金船协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "ShipProt.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NShipProt
{

#ifdef PROT_USE_XML

const char* EnumValToStr(EShipBattleSource e)
{
	switch(e)
	{
	case EBS_OPENSHIP:
		return "EBS_OPENSHIP";
	case EBS_ROBWITHOWER:
		return "EBS_ROBWITHOWER";
	case EBS_ROBWITHDEFENSE:
		return "EBS_ROBWITHDEFENSE";
	case EBS_GRABBYOWER:
		return "EBS_GRABBYOWER";
	case EBS_GRABBYDEFENSE:
		return "EBS_GRABBYDEFENSE";
	case EBS_CLOSESHIP:
		return "EBS_CLOSESHIP";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EShipBattleSource& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EShipBattleSource> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("EBS_OPENSHIP", EBS_OPENSHIP));
		mapStr2Val.insert(make_pair("EBS_ROBWITHOWER", EBS_ROBWITHOWER));
		mapStr2Val.insert(make_pair("EBS_ROBWITHDEFENSE", EBS_ROBWITHDEFENSE));
		mapStr2Val.insert(make_pair("EBS_GRABBYOWER", EBS_GRABBYOWER));
		mapStr2Val.insert(make_pair("EBS_GRABBYDEFENSE", EBS_GRABBYDEFENSE));
		mapStr2Val.insert(make_pair("EBS_CLOSESHIP", EBS_CLOSESHIP));
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

const char* EnumValToStr(EShipResult e)
{
	switch(e)
	{
	case EShip_Suc:
		return "EShip_Suc";
	case EShip_NoShip:
		return "EShip_NoShip";
	case EShip_NoFlushShip:
		return "EShip_NoFlushShip";
	case EShip_NoFlushShip2:
		return "EShip_NoFlushShip2";
	case EShip_DeFenseIsAgree:
		return "EShip_DeFenseIsAgree";
	case EShip_DeFenseIsAgree2:
		return "EShip_DeFenseIsAgree2";
	case EShip_DriveHasShip:
		return "EShip_DriveHasShip";
	case EShip_DriveHasShip2:
		return "EShip_DriveHasShip2";
	case EShip_InviteDeFenseOffLine:
		return "EShip_InviteDeFenseOffLine";
	case EShip_InviteDeFenseOffLine2:
		return "EShip_InviteDeFenseOffLine2";
	case EShip_DeFenseAgreeOther:
		return "EShip_DeFenseAgreeOther";
	case EShip_DeFenseAgreeOther2:
		return "EShip_DeFenseAgreeOther2";
	case EShip_DeFenseOtherShip:
		return "EShip_DeFenseOtherShip";
	case EShip_DeFenseOtherShip2:
		return "EShip_DeFenseOtherShip2";
	case EShip_OtherDeFenseTimesOut:
		return "EShip_OtherDeFenseTimesOut";
	case EShip_OtherDeFenseTimesOut2:
		return "EShip_OtherDeFenseTimesOut2";
	case EShip_DeFenseDisAgree:
		return "EShip_DeFenseDisAgree";
	case EShip_DeFenseDisAgree2:
		return "EShip_DeFenseDisAgree2";
	case EShip_DeFenseErrFriend:
		return "EShip_DeFenseErrFriend";
	case EShip_BuyOpenGoldLimit:
		return "EShip_BuyOpenGoldLimit";
	case EShip_BuyRobGoldLimit:
		return "EShip_BuyRobGoldLimit";
	case EShip_RelushGoldLimit:
		return "EShip_RelushGoldLimit";
	case EShip_RelushShipUpLimit:
		return "EShip_RelushShipUpLimit";
	case EShip_DriveOverLimit:
		return "EShip_DriveOverLimit";
	case EShip_DriveGoldLimit:
		return "EShip_DriveGoldLimit";
	case EShip_ROBOverLimit:
		return "EShip_ROBOverLimit";
	case EShip_ROBOverShip:
		return "EShip_ROBOverShip";
	case EShip_ROBDone:
		return "EShip_ROBDone";
	case EShip_ROBSelf:
		return "EShip_ROBSelf";
	case EShip_GRABErrOwer:
		return "EShip_GRABErrOwer";
	case EShip_GRABErr:
		return "EShip_GRABErr";
	case EShip_BattleCool:
		return "EShip_BattleCool";
	case EShip_FinishOneKeyNoGold:
		return "EShip_FinishOneKeyNoGold";
	case EShip_GetShipOneKeyNoGold:
		return "EShip_GetShipOneKeyNoGold";
	case EShip_GetShipOneKeyNoVip:
		return "EShip_GetShipOneKeyNoVip";
	case EShip_OtherErr:
		return "EShip_OtherErr";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EShipResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EShipResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("EShip_Suc", EShip_Suc));
		mapStr2Val.insert(make_pair("EShip_NoShip", EShip_NoShip));
		mapStr2Val.insert(make_pair("EShip_NoFlushShip", EShip_NoFlushShip));
		mapStr2Val.insert(make_pair("EShip_NoFlushShip2", EShip_NoFlushShip2));
		mapStr2Val.insert(make_pair("EShip_DeFenseIsAgree", EShip_DeFenseIsAgree));
		mapStr2Val.insert(make_pair("EShip_DeFenseIsAgree2", EShip_DeFenseIsAgree2));
		mapStr2Val.insert(make_pair("EShip_DriveHasShip", EShip_DriveHasShip));
		mapStr2Val.insert(make_pair("EShip_DriveHasShip2", EShip_DriveHasShip2));
		mapStr2Val.insert(make_pair("EShip_InviteDeFenseOffLine", EShip_InviteDeFenseOffLine));
		mapStr2Val.insert(make_pair("EShip_InviteDeFenseOffLine2", EShip_InviteDeFenseOffLine2));
		mapStr2Val.insert(make_pair("EShip_DeFenseAgreeOther", EShip_DeFenseAgreeOther));
		mapStr2Val.insert(make_pair("EShip_DeFenseAgreeOther2", EShip_DeFenseAgreeOther2));
		mapStr2Val.insert(make_pair("EShip_DeFenseOtherShip", EShip_DeFenseOtherShip));
		mapStr2Val.insert(make_pair("EShip_DeFenseOtherShip2", EShip_DeFenseOtherShip2));
		mapStr2Val.insert(make_pair("EShip_OtherDeFenseTimesOut", EShip_OtherDeFenseTimesOut));
		mapStr2Val.insert(make_pair("EShip_OtherDeFenseTimesOut2", EShip_OtherDeFenseTimesOut2));
		mapStr2Val.insert(make_pair("EShip_DeFenseDisAgree", EShip_DeFenseDisAgree));
		mapStr2Val.insert(make_pair("EShip_DeFenseDisAgree2", EShip_DeFenseDisAgree2));
		mapStr2Val.insert(make_pair("EShip_DeFenseErrFriend", EShip_DeFenseErrFriend));
		mapStr2Val.insert(make_pair("EShip_BuyOpenGoldLimit", EShip_BuyOpenGoldLimit));
		mapStr2Val.insert(make_pair("EShip_BuyRobGoldLimit", EShip_BuyRobGoldLimit));
		mapStr2Val.insert(make_pair("EShip_RelushGoldLimit", EShip_RelushGoldLimit));
		mapStr2Val.insert(make_pair("EShip_RelushShipUpLimit", EShip_RelushShipUpLimit));
		mapStr2Val.insert(make_pair("EShip_DriveOverLimit", EShip_DriveOverLimit));
		mapStr2Val.insert(make_pair("EShip_DriveGoldLimit", EShip_DriveGoldLimit));
		mapStr2Val.insert(make_pair("EShip_ROBOverLimit", EShip_ROBOverLimit));
		mapStr2Val.insert(make_pair("EShip_ROBOverShip", EShip_ROBOverShip));
		mapStr2Val.insert(make_pair("EShip_ROBDone", EShip_ROBDone));
		mapStr2Val.insert(make_pair("EShip_ROBSelf", EShip_ROBSelf));
		mapStr2Val.insert(make_pair("EShip_GRABErrOwer", EShip_GRABErrOwer));
		mapStr2Val.insert(make_pair("EShip_GRABErr", EShip_GRABErr));
		mapStr2Val.insert(make_pair("EShip_BattleCool", EShip_BattleCool));
		mapStr2Val.insert(make_pair("EShip_FinishOneKeyNoGold", EShip_FinishOneKeyNoGold));
		mapStr2Val.insert(make_pair("EShip_GetShipOneKeyNoGold", EShip_GetShipOneKeyNoGold));
		mapStr2Val.insert(make_pair("EShip_GetShipOneKeyNoVip", EShip_GetShipOneKeyNoVip));
		mapStr2Val.insert(make_pair("EShip_OtherErr", EShip_OtherErr));
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

const char* GetDescription(EShipResult e)
{
	switch(e)
	{
	case EShip_Suc:
		return "成功";
	case EShip_NoShip:
		return "船不存在";
	case EShip_NoFlushShip:
		return "你没有刷船";
	case EShip_NoFlushShip2:
		return "邀请你的人没有刷船";
	case EShip_DeFenseIsAgree:
		return "已经有人同意帮你护送";
	case EShip_DeFenseIsAgree2:
		return "已经有人同意帮船主护送";
	case EShip_DriveHasShip:
		return "你的船已开";
	case EShip_DriveHasShip2:
		return "邀请你的人的船已开";
	case EShip_InviteDeFenseOffLine:
		return "你邀请的人不在线";
	case EShip_InviteDeFenseOffLine2:
		return "船主不在线";
	case EShip_DeFenseAgreeOther:
		return "你邀请的人答应护送其他船";
	case EShip_DeFenseAgreeOther2:
		return "你已答应护送其他船";
	case EShip_DeFenseOtherShip:
		return "你邀请的人在护送其他船";
	case EShip_DeFenseOtherShip2:
		return "你在护送其他船";
	case EShip_OtherDeFenseTimesOut:
		return "你邀请的人护送次数用完";
	case EShip_OtherDeFenseTimesOut2:
		return "你的护送次数用完";
	case EShip_DeFenseDisAgree:
		return "邀请的人不同意帮你护送";
	case EShip_DeFenseDisAgree2:
		return "邀请的人不同意帮你护送";
	case EShip_DeFenseErrFriend:
		return "他不是你的护卫";
	case EShip_BuyOpenGoldLimit:
		return "购买运船仙石不足";
	case EShip_BuyRobGoldLimit:
		return "购买抢劫仙石不足";
	case EShip_RelushGoldLimit:
		return "购买刷新次数仙石不足";
	case EShip_RelushShipUpLimit:
		return "刷新次数用完";
	case EShip_DriveOverLimit:
		return "今日开船到达上限";
	case EShip_DriveGoldLimit:
		return "开船金币不足";
	case EShip_ROBOverLimit:
		return "今日抢劫次数到达上限";
	case EShip_ROBOverShip:
		return "这条船被抢劫次数到达上限";
	case EShip_ROBDone:
		return "这条船你已经打劫";
	case EShip_ROBSelf:
		return "这条船被你护卫或者是你的，不可抢劫";
	case EShip_GRABErrOwer:
		return "这条船不是你的或者你不是护卫，不可返抢";
	case EShip_GRABErr:
		return "返抢对手错误";
	case EShip_BattleCool:
		return "战斗冷却";
	case EShip_FinishOneKeyNoGold:
		return "一键完成运船金币不足";
	case EShip_GetShipOneKeyNoGold:
		return "一键召唤Vip金币不足";
	case EShip_GetShipOneKeyNoVip:
		return "一键召唤Vip等级不足";
	case EShip_OtherErr:
		return "其他错误";
	default:
		return "未知错误";
	}
}

PlayerShip::PlayerShip() : qwInsID(0), qwOwer(0), dwOwerPoint(0), byOwerLevel(0), byOwerColor(0), 
			byChannel(0), wShipId(0), qwDefense(0), dwDefensePoint(0), byDefenseLevel(0), 
			byDefenseColor(0), qwRoBId1(0), byRoB1Color(0), dwRoB1Point(0), byRoB1Level(0), 
			qwRoBId2(0), byRoB2Color(0), dwRoB2Point(0), byRoB2Level(0), qwRoBId3(0), 
			byRoB3Color(0), dwRoB3Point(0), byRoB3Level(0), dwBeginTimer(0), dwEndTimer(0), 
			dwAwardRate(0) { }

CInArchive& operator>>(CInArchive& src, PlayerShip& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwInsID;
	src >> s.qwOwer;
	src >> s.dwOwerPoint;
	src >> s.byOwerLevel;
	src >> s.byOwerColor;
	src >> s.byChannel;
	src >> s.wShipId;
	src >> s.qwDefense;
	src >> s.dwDefensePoint;
	src >> s.byDefenseLevel;
	src >> s.byDefenseColor;
	src >> s.qwRoBId1;
	src >> s.byRoB1Color;
	src >> s.dwRoB1Point;
	src >> s.byRoB1Level;
	src >> s.qwRoBId2;
	src >> s.byRoB2Color;
	src >> s.dwRoB2Point;
	src >> s.byRoB2Level;
	src >> s.qwRoBId3;
	src >> s.byRoB3Color;
	src >> s.dwRoB3Point;
	src >> s.byRoB3Level;
	src >> s.dwBeginTimer;
	src >> s.dwEndTimer;
	src >> s.dwAwardRate;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const PlayerShip& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.qwInsID;
	src << s.qwOwer;
	src << s.dwOwerPoint;
	src << s.byOwerLevel;
	src << s.byOwerColor;
	src << s.byChannel;
	src << s.wShipId;
	src << s.qwDefense;
	src << s.dwDefensePoint;
	src << s.byDefenseLevel;
	src << s.byDefenseColor;
	src << s.qwRoBId1;
	src << s.byRoB1Color;
	src << s.dwRoB1Point;
	src << s.byRoB1Level;
	src << s.qwRoBId2;
	src << s.byRoB2Color;
	src << s.dwRoB2Point;
	src << s.byRoB2Level;
	src << s.qwRoBId3;
	src << s.byRoB3Color;
	src << s.dwRoB3Point;
	src << s.byRoB3Level;
	src << s.dwBeginTimer;
	src << s.dwEndTimer;
	src << s.dwAwardRate;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, PlayerShip& s)
{
	if(strcmp(rElement.Value(), "PlayerShip") != 0)
	{
		LOG_CRI << "rElement is not PlayerShip!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwInsID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwInsID") != 0)
	{
		LOG_CRI << "Attribute: name is not qwInsID!";
		return false;
	}
	const char* pszVal_qwInsID = pElemChild->Attribute("value");
	if(pszVal_qwInsID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwInsID, s.qwInsID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwOwer is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwOwer") != 0)
	{
		LOG_CRI << "Attribute: name is not qwOwer!";
		return false;
	}
	const char* pszVal_qwOwer = pElemChild->Attribute("value");
	if(pszVal_qwOwer == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwOwer, s.qwOwer))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwOwerPoint is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwOwerPoint") != 0)
	{
		LOG_CRI << "Attribute: name is not dwOwerPoint!";
		return false;
	}
	const char* pszVal_dwOwerPoint = pElemChild->Attribute("value");
	if(pszVal_dwOwerPoint == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwOwerPoint, s.dwOwerPoint))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byOwerLevel is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byOwerLevel") != 0)
	{
		LOG_CRI << "Attribute: name is not byOwerLevel!";
		return false;
	}
	const char* pszVal_byOwerLevel = pElemChild->Attribute("value");
	if(pszVal_byOwerLevel == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byOwerLevel, s.byOwerLevel))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byOwerColor is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byOwerColor") != 0)
	{
		LOG_CRI << "Attribute: name is not byOwerColor!";
		return false;
	}
	const char* pszVal_byOwerColor = pElemChild->Attribute("value");
	if(pszVal_byOwerColor == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byOwerColor, s.byOwerColor))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byChannel is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byChannel") != 0)
	{
		LOG_CRI << "Attribute: name is not byChannel!";
		return false;
	}
	const char* pszVal_byChannel = pElemChild->Attribute("value");
	if(pszVal_byChannel == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byChannel, s.byChannel))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wShipId is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wShipId") != 0)
	{
		LOG_CRI << "Attribute: name is not wShipId!";
		return false;
	}
	const char* pszVal_wShipId = pElemChild->Attribute("value");
	if(pszVal_wShipId == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wShipId, s.wShipId))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwDefense is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwDefense") != 0)
	{
		LOG_CRI << "Attribute: name is not qwDefense!";
		return false;
	}
	const char* pszVal_qwDefense = pElemChild->Attribute("value");
	if(pszVal_qwDefense == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwDefense, s.qwDefense))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwDefensePoint is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwDefensePoint") != 0)
	{
		LOG_CRI << "Attribute: name is not dwDefensePoint!";
		return false;
	}
	const char* pszVal_dwDefensePoint = pElemChild->Attribute("value");
	if(pszVal_dwDefensePoint == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwDefensePoint, s.dwDefensePoint))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byDefenseLevel is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byDefenseLevel") != 0)
	{
		LOG_CRI << "Attribute: name is not byDefenseLevel!";
		return false;
	}
	const char* pszVal_byDefenseLevel = pElemChild->Attribute("value");
	if(pszVal_byDefenseLevel == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byDefenseLevel, s.byDefenseLevel))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byDefenseColor is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byDefenseColor") != 0)
	{
		LOG_CRI << "Attribute: name is not byDefenseColor!";
		return false;
	}
	const char* pszVal_byDefenseColor = pElemChild->Attribute("value");
	if(pszVal_byDefenseColor == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byDefenseColor, s.byDefenseColor))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwRoBId1 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwRoBId1") != 0)
	{
		LOG_CRI << "Attribute: name is not qwRoBId1!";
		return false;
	}
	const char* pszVal_qwRoBId1 = pElemChild->Attribute("value");
	if(pszVal_qwRoBId1 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwRoBId1, s.qwRoBId1))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byRoB1Color is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byRoB1Color") != 0)
	{
		LOG_CRI << "Attribute: name is not byRoB1Color!";
		return false;
	}
	const char* pszVal_byRoB1Color = pElemChild->Attribute("value");
	if(pszVal_byRoB1Color == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byRoB1Color, s.byRoB1Color))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwRoB1Point is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwRoB1Point") != 0)
	{
		LOG_CRI << "Attribute: name is not dwRoB1Point!";
		return false;
	}
	const char* pszVal_dwRoB1Point = pElemChild->Attribute("value");
	if(pszVal_dwRoB1Point == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwRoB1Point, s.dwRoB1Point))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byRoB1Level is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byRoB1Level") != 0)
	{
		LOG_CRI << "Attribute: name is not byRoB1Level!";
		return false;
	}
	const char* pszVal_byRoB1Level = pElemChild->Attribute("value");
	if(pszVal_byRoB1Level == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byRoB1Level, s.byRoB1Level))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwRoBId2 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwRoBId2") != 0)
	{
		LOG_CRI << "Attribute: name is not qwRoBId2!";
		return false;
	}
	const char* pszVal_qwRoBId2 = pElemChild->Attribute("value");
	if(pszVal_qwRoBId2 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwRoBId2, s.qwRoBId2))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byRoB2Color is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byRoB2Color") != 0)
	{
		LOG_CRI << "Attribute: name is not byRoB2Color!";
		return false;
	}
	const char* pszVal_byRoB2Color = pElemChild->Attribute("value");
	if(pszVal_byRoB2Color == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byRoB2Color, s.byRoB2Color))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwRoB2Point is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwRoB2Point") != 0)
	{
		LOG_CRI << "Attribute: name is not dwRoB2Point!";
		return false;
	}
	const char* pszVal_dwRoB2Point = pElemChild->Attribute("value");
	if(pszVal_dwRoB2Point == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwRoB2Point, s.dwRoB2Point))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byRoB2Level is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byRoB2Level") != 0)
	{
		LOG_CRI << "Attribute: name is not byRoB2Level!";
		return false;
	}
	const char* pszVal_byRoB2Level = pElemChild->Attribute("value");
	if(pszVal_byRoB2Level == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byRoB2Level, s.byRoB2Level))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwRoBId3 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwRoBId3") != 0)
	{
		LOG_CRI << "Attribute: name is not qwRoBId3!";
		return false;
	}
	const char* pszVal_qwRoBId3 = pElemChild->Attribute("value");
	if(pszVal_qwRoBId3 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwRoBId3, s.qwRoBId3))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byRoB3Color is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byRoB3Color") != 0)
	{
		LOG_CRI << "Attribute: name is not byRoB3Color!";
		return false;
	}
	const char* pszVal_byRoB3Color = pElemChild->Attribute("value");
	if(pszVal_byRoB3Color == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byRoB3Color, s.byRoB3Color))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwRoB3Point is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwRoB3Point") != 0)
	{
		LOG_CRI << "Attribute: name is not dwRoB3Point!";
		return false;
	}
	const char* pszVal_dwRoB3Point = pElemChild->Attribute("value");
	if(pszVal_dwRoB3Point == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwRoB3Point, s.dwRoB3Point))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byRoB3Level is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byRoB3Level") != 0)
	{
		LOG_CRI << "Attribute: name is not byRoB3Level!";
		return false;
	}
	const char* pszVal_byRoB3Level = pElemChild->Attribute("value");
	if(pszVal_byRoB3Level == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byRoB3Level, s.byRoB3Level))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwBeginTimer is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwBeginTimer") != 0)
	{
		LOG_CRI << "Attribute: name is not dwBeginTimer!";
		return false;
	}
	const char* pszVal_dwBeginTimer = pElemChild->Attribute("value");
	if(pszVal_dwBeginTimer == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwBeginTimer, s.dwBeginTimer))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwEndTimer is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwEndTimer") != 0)
	{
		LOG_CRI << "Attribute: name is not dwEndTimer!";
		return false;
	}
	const char* pszVal_dwEndTimer = pElemChild->Attribute("value");
	if(pszVal_dwEndTimer == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwEndTimer, s.dwEndTimer))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwAwardRate is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwAwardRate") != 0)
	{
		LOG_CRI << "Attribute: name is not dwAwardRate!";
		return false;
	}
	const char* pszVal_dwAwardRate = pElemChild->Attribute("value");
	if(pszVal_dwAwardRate == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwAwardRate, s.dwAwardRate))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const PlayerShip& s, TiXmlElement& rElement)
{
	rElement.SetValue("PlayerShip");
	rElement.SetAttribute("type", ToUTF8Ptr("金船信息"));
	unique_ptr<TiXmlElement> pElem_qwInsID(new TiXmlElement("UINT64"));
	if(pElem_qwInsID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwInsID->SetAttribute("name", "qwInsID");
	pElem_qwInsID->SetAttribute("value", NumberToString(s.qwInsID).c_str());
	pElem_qwInsID->SetAttribute("comment", ToUTF8Ptr("金船唯一ID"));
	if(rElement.LinkEndChild(pElem_qwInsID.get()) != NULL)
		pElem_qwInsID.release();
	unique_ptr<TiXmlElement> pElem_qwOwer(new TiXmlElement("UINT64"));
	if(pElem_qwOwer == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwOwer->SetAttribute("name", "qwOwer");
	pElem_qwOwer->SetAttribute("value", NumberToString(s.qwOwer).c_str());
	pElem_qwOwer->SetAttribute("comment", ToUTF8Ptr("金船拥有者"));
	if(rElement.LinkEndChild(pElem_qwOwer.get()) != NULL)
		pElem_qwOwer.release();
	unique_ptr<TiXmlElement> pElem_dwOwerPoint(new TiXmlElement("UINT32"));
	if(pElem_dwOwerPoint == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwOwerPoint->SetAttribute("name", "dwOwerPoint");
	pElem_dwOwerPoint->SetAttribute("value", NumberToString(s.dwOwerPoint).c_str());
	pElem_dwOwerPoint->SetAttribute("comment", ToUTF8Ptr("金船拥有者战斗力"));
	if(rElement.LinkEndChild(pElem_dwOwerPoint.get()) != NULL)
		pElem_dwOwerPoint.release();
	unique_ptr<TiXmlElement> pElem_byOwerLevel(new TiXmlElement("UINT8"));
	if(pElem_byOwerLevel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byOwerLevel->SetAttribute("name", "byOwerLevel");
	pElem_byOwerLevel->SetAttribute("value", NumberToString(s.byOwerLevel).c_str());
	pElem_byOwerLevel->SetAttribute("comment", ToUTF8Ptr("拥有者等级"));
	if(rElement.LinkEndChild(pElem_byOwerLevel.get()) != NULL)
		pElem_byOwerLevel.release();
	unique_ptr<TiXmlElement> pElem_byOwerColor(new TiXmlElement("UINT8"));
	if(pElem_byOwerColor == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byOwerColor->SetAttribute("name", "byOwerColor");
	pElem_byOwerColor->SetAttribute("value", NumberToString(s.byOwerColor).c_str());
	pElem_byOwerColor->SetAttribute("comment", ToUTF8Ptr("拥有者颜色"));
	if(rElement.LinkEndChild(pElem_byOwerColor.get()) != NULL)
		pElem_byOwerColor.release();
	unique_ptr<TiXmlElement> pElem_byChannel(new TiXmlElement("UINT8"));
	if(pElem_byChannel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byChannel->SetAttribute("name", "byChannel");
	pElem_byChannel->SetAttribute("value", NumberToString(s.byChannel).c_str());
	pElem_byChannel->SetAttribute("comment", ToUTF8Ptr("航道"));
	if(rElement.LinkEndChild(pElem_byChannel.get()) != NULL)
		pElem_byChannel.release();
	unique_ptr<TiXmlElement> pElem_wShipId(new TiXmlElement("UINT16"));
	if(pElem_wShipId == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wShipId->SetAttribute("name", "wShipId");
	pElem_wShipId->SetAttribute("value", NumberToString(s.wShipId).c_str());
	pElem_wShipId->SetAttribute("comment", ToUTF8Ptr("金船模板"));
	if(rElement.LinkEndChild(pElem_wShipId.get()) != NULL)
		pElem_wShipId.release();
	unique_ptr<TiXmlElement> pElem_qwDefense(new TiXmlElement("UINT64"));
	if(pElem_qwDefense == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwDefense->SetAttribute("name", "qwDefense");
	pElem_qwDefense->SetAttribute("value", NumberToString(s.qwDefense).c_str());
	pElem_qwDefense->SetAttribute("comment", ToUTF8Ptr("护送者ID"));
	if(rElement.LinkEndChild(pElem_qwDefense.get()) != NULL)
		pElem_qwDefense.release();
	unique_ptr<TiXmlElement> pElem_dwDefensePoint(new TiXmlElement("UINT32"));
	if(pElem_dwDefensePoint == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwDefensePoint->SetAttribute("name", "dwDefensePoint");
	pElem_dwDefensePoint->SetAttribute("value", NumberToString(s.dwDefensePoint).c_str());
	pElem_dwDefensePoint->SetAttribute("comment", ToUTF8Ptr("护送者战斗力"));
	if(rElement.LinkEndChild(pElem_dwDefensePoint.get()) != NULL)
		pElem_dwDefensePoint.release();
	unique_ptr<TiXmlElement> pElem_byDefenseLevel(new TiXmlElement("UINT8"));
	if(pElem_byDefenseLevel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byDefenseLevel->SetAttribute("name", "byDefenseLevel");
	pElem_byDefenseLevel->SetAttribute("value", NumberToString(s.byDefenseLevel).c_str());
	pElem_byDefenseLevel->SetAttribute("comment", ToUTF8Ptr("护送者等级"));
	if(rElement.LinkEndChild(pElem_byDefenseLevel.get()) != NULL)
		pElem_byDefenseLevel.release();
	unique_ptr<TiXmlElement> pElem_byDefenseColor(new TiXmlElement("UINT8"));
	if(pElem_byDefenseColor == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byDefenseColor->SetAttribute("name", "byDefenseColor");
	pElem_byDefenseColor->SetAttribute("value", NumberToString(s.byDefenseColor).c_str());
	pElem_byDefenseColor->SetAttribute("comment", ToUTF8Ptr("护送者颜色"));
	if(rElement.LinkEndChild(pElem_byDefenseColor.get()) != NULL)
		pElem_byDefenseColor.release();
	unique_ptr<TiXmlElement> pElem_qwRoBId1(new TiXmlElement("UINT64"));
	if(pElem_qwRoBId1 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwRoBId1->SetAttribute("name", "qwRoBId1");
	pElem_qwRoBId1->SetAttribute("value", NumberToString(s.qwRoBId1).c_str());
	pElem_qwRoBId1->SetAttribute("comment", ToUTF8Ptr("打劫者1"));
	if(rElement.LinkEndChild(pElem_qwRoBId1.get()) != NULL)
		pElem_qwRoBId1.release();
	unique_ptr<TiXmlElement> pElem_byRoB1Color(new TiXmlElement("UINT8"));
	if(pElem_byRoB1Color == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byRoB1Color->SetAttribute("name", "byRoB1Color");
	pElem_byRoB1Color->SetAttribute("value", NumberToString(s.byRoB1Color).c_str());
	pElem_byRoB1Color->SetAttribute("comment", ToUTF8Ptr("打劫者1颜色"));
	if(rElement.LinkEndChild(pElem_byRoB1Color.get()) != NULL)
		pElem_byRoB1Color.release();
	unique_ptr<TiXmlElement> pElem_dwRoB1Point(new TiXmlElement("UINT32"));
	if(pElem_dwRoB1Point == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwRoB1Point->SetAttribute("name", "dwRoB1Point");
	pElem_dwRoB1Point->SetAttribute("value", NumberToString(s.dwRoB1Point).c_str());
	pElem_dwRoB1Point->SetAttribute("comment", ToUTF8Ptr("打劫者1战斗力"));
	if(rElement.LinkEndChild(pElem_dwRoB1Point.get()) != NULL)
		pElem_dwRoB1Point.release();
	unique_ptr<TiXmlElement> pElem_byRoB1Level(new TiXmlElement("UINT8"));
	if(pElem_byRoB1Level == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byRoB1Level->SetAttribute("name", "byRoB1Level");
	pElem_byRoB1Level->SetAttribute("value", NumberToString(s.byRoB1Level).c_str());
	pElem_byRoB1Level->SetAttribute("comment", ToUTF8Ptr("打劫者1等级"));
	if(rElement.LinkEndChild(pElem_byRoB1Level.get()) != NULL)
		pElem_byRoB1Level.release();
	unique_ptr<TiXmlElement> pElem_qwRoBId2(new TiXmlElement("UINT64"));
	if(pElem_qwRoBId2 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwRoBId2->SetAttribute("name", "qwRoBId2");
	pElem_qwRoBId2->SetAttribute("value", NumberToString(s.qwRoBId2).c_str());
	pElem_qwRoBId2->SetAttribute("comment", ToUTF8Ptr("打劫者2"));
	if(rElement.LinkEndChild(pElem_qwRoBId2.get()) != NULL)
		pElem_qwRoBId2.release();
	unique_ptr<TiXmlElement> pElem_byRoB2Color(new TiXmlElement("UINT8"));
	if(pElem_byRoB2Color == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byRoB2Color->SetAttribute("name", "byRoB2Color");
	pElem_byRoB2Color->SetAttribute("value", NumberToString(s.byRoB2Color).c_str());
	pElem_byRoB2Color->SetAttribute("comment", ToUTF8Ptr("打劫者2颜色"));
	if(rElement.LinkEndChild(pElem_byRoB2Color.get()) != NULL)
		pElem_byRoB2Color.release();
	unique_ptr<TiXmlElement> pElem_dwRoB2Point(new TiXmlElement("UINT32"));
	if(pElem_dwRoB2Point == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwRoB2Point->SetAttribute("name", "dwRoB2Point");
	pElem_dwRoB2Point->SetAttribute("value", NumberToString(s.dwRoB2Point).c_str());
	pElem_dwRoB2Point->SetAttribute("comment", ToUTF8Ptr("打劫者2战斗力"));
	if(rElement.LinkEndChild(pElem_dwRoB2Point.get()) != NULL)
		pElem_dwRoB2Point.release();
	unique_ptr<TiXmlElement> pElem_byRoB2Level(new TiXmlElement("UINT8"));
	if(pElem_byRoB2Level == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byRoB2Level->SetAttribute("name", "byRoB2Level");
	pElem_byRoB2Level->SetAttribute("value", NumberToString(s.byRoB2Level).c_str());
	pElem_byRoB2Level->SetAttribute("comment", ToUTF8Ptr("打劫者2等级"));
	if(rElement.LinkEndChild(pElem_byRoB2Level.get()) != NULL)
		pElem_byRoB2Level.release();
	unique_ptr<TiXmlElement> pElem_qwRoBId3(new TiXmlElement("UINT64"));
	if(pElem_qwRoBId3 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwRoBId3->SetAttribute("name", "qwRoBId3");
	pElem_qwRoBId3->SetAttribute("value", NumberToString(s.qwRoBId3).c_str());
	pElem_qwRoBId3->SetAttribute("comment", ToUTF8Ptr("打劫者3"));
	if(rElement.LinkEndChild(pElem_qwRoBId3.get()) != NULL)
		pElem_qwRoBId3.release();
	unique_ptr<TiXmlElement> pElem_byRoB3Color(new TiXmlElement("UINT8"));
	if(pElem_byRoB3Color == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byRoB3Color->SetAttribute("name", "byRoB3Color");
	pElem_byRoB3Color->SetAttribute("value", NumberToString(s.byRoB3Color).c_str());
	pElem_byRoB3Color->SetAttribute("comment", ToUTF8Ptr("打劫者3颜色"));
	if(rElement.LinkEndChild(pElem_byRoB3Color.get()) != NULL)
		pElem_byRoB3Color.release();
	unique_ptr<TiXmlElement> pElem_dwRoB3Point(new TiXmlElement("UINT32"));
	if(pElem_dwRoB3Point == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwRoB3Point->SetAttribute("name", "dwRoB3Point");
	pElem_dwRoB3Point->SetAttribute("value", NumberToString(s.dwRoB3Point).c_str());
	pElem_dwRoB3Point->SetAttribute("comment", ToUTF8Ptr("打劫者3战斗力"));
	if(rElement.LinkEndChild(pElem_dwRoB3Point.get()) != NULL)
		pElem_dwRoB3Point.release();
	unique_ptr<TiXmlElement> pElem_byRoB3Level(new TiXmlElement("UINT8"));
	if(pElem_byRoB3Level == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byRoB3Level->SetAttribute("name", "byRoB3Level");
	pElem_byRoB3Level->SetAttribute("value", NumberToString(s.byRoB3Level).c_str());
	pElem_byRoB3Level->SetAttribute("comment", ToUTF8Ptr("打劫者3等级"));
	if(rElement.LinkEndChild(pElem_byRoB3Level.get()) != NULL)
		pElem_byRoB3Level.release();
	unique_ptr<TiXmlElement> pElem_dwBeginTimer(new TiXmlElement("UINT32"));
	if(pElem_dwBeginTimer == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwBeginTimer->SetAttribute("name", "dwBeginTimer");
	pElem_dwBeginTimer->SetAttribute("value", NumberToString(s.dwBeginTimer).c_str());
	pElem_dwBeginTimer->SetAttribute("comment", ToUTF8Ptr("开船时间"));
	if(rElement.LinkEndChild(pElem_dwBeginTimer.get()) != NULL)
		pElem_dwBeginTimer.release();
	unique_ptr<TiXmlElement> pElem_dwEndTimer(new TiXmlElement("UINT32"));
	if(pElem_dwEndTimer == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwEndTimer->SetAttribute("name", "dwEndTimer");
	pElem_dwEndTimer->SetAttribute("value", NumberToString(s.dwEndTimer).c_str());
	pElem_dwEndTimer->SetAttribute("comment", ToUTF8Ptr("结束时间"));
	if(rElement.LinkEndChild(pElem_dwEndTimer.get()) != NULL)
		pElem_dwEndTimer.release();
	unique_ptr<TiXmlElement> pElem_dwAwardRate(new TiXmlElement("UINT32"));
	if(pElem_dwAwardRate == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwAwardRate->SetAttribute("name", "dwAwardRate");
	pElem_dwAwardRate->SetAttribute("value", NumberToString(s.dwAwardRate).c_str());
	pElem_dwAwardRate->SetAttribute("comment", ToUTF8Ptr("奖励倍率"));
	if(rElement.LinkEndChild(pElem_dwAwardRate.get()) != NULL)
		pElem_dwAwardRate.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecPlayerShip& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		PlayerShip s;
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

bool VectorToXML(const TVecPlayerShip& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("PlayerShip"));
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

ShipReport::ShipReport() : qwInsID(0), eSource((EShipBattleSource)0), qwOwer(0), byOwerColor(0), wShipId(0), 
			qwDefense(0), byDefenseColor(0), qwRoBId(0), byRoBColor(0), qwBattleID(0), 
			dwFinishTimer(0), dwTimer(0), byRobTimes(0), dwAwardRate(0) { }

CInArchive& operator>>(CInArchive& src, ShipReport& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwInsID;
	src >> (UINT8&)s.eSource;
	src >> s.qwOwer;
	src >> s.byOwerColor;
	src >> s.wShipId;
	src >> s.qwDefense;
	src >> s.byDefenseColor;
	src >> s.qwRoBId;
	src >> s.byRoBColor;
	src >> s.qwBattleID;
	src >> s.dwFinishTimer;
	src >> s.dwTimer;
	src >> s.byRobTimes;
	src >> s.dwAwardRate;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const ShipReport& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.qwInsID;
	src << (UINT8&)s.eSource;
	src << s.qwOwer;
	src << s.byOwerColor;
	src << s.wShipId;
	src << s.qwDefense;
	src << s.byDefenseColor;
	src << s.qwRoBId;
	src << s.byRoBColor;
	src << s.qwBattleID;
	src << s.dwFinishTimer;
	src << s.dwTimer;
	src << s.byRobTimes;
	src << s.dwAwardRate;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, ShipReport& s)
{
	if(strcmp(rElement.Value(), "ShipReport") != 0)
	{
		LOG_CRI << "rElement is not ShipReport!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwInsID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwInsID") != 0)
	{
		LOG_CRI << "Attribute: name is not qwInsID!";
		return false;
	}
	const char* pszVal_qwInsID = pElemChild->Attribute("value");
	if(pszVal_qwInsID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwInsID, s.qwInsID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eSource is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "EShipBattleSource") != 0)
	{
		LOG_CRI << "pElemChild is not EShipBattleSource!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eSource") != 0)
	{
		LOG_CRI << "Attribute: name is not eSource!";
		return false;
	}
	const char* pszVal_eSource = pElemChild->Attribute("value");
	if(pszVal_eSource == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!EnumStrToVal(pszVal_eSource, s.eSource))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwOwer is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwOwer") != 0)
	{
		LOG_CRI << "Attribute: name is not qwOwer!";
		return false;
	}
	const char* pszVal_qwOwer = pElemChild->Attribute("value");
	if(pszVal_qwOwer == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwOwer, s.qwOwer))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byOwerColor is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byOwerColor") != 0)
	{
		LOG_CRI << "Attribute: name is not byOwerColor!";
		return false;
	}
	const char* pszVal_byOwerColor = pElemChild->Attribute("value");
	if(pszVal_byOwerColor == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byOwerColor, s.byOwerColor))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wShipId is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wShipId") != 0)
	{
		LOG_CRI << "Attribute: name is not wShipId!";
		return false;
	}
	const char* pszVal_wShipId = pElemChild->Attribute("value");
	if(pszVal_wShipId == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wShipId, s.wShipId))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwDefense is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwDefense") != 0)
	{
		LOG_CRI << "Attribute: name is not qwDefense!";
		return false;
	}
	const char* pszVal_qwDefense = pElemChild->Attribute("value");
	if(pszVal_qwDefense == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwDefense, s.qwDefense))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byDefenseColor is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byDefenseColor") != 0)
	{
		LOG_CRI << "Attribute: name is not byDefenseColor!";
		return false;
	}
	const char* pszVal_byDefenseColor = pElemChild->Attribute("value");
	if(pszVal_byDefenseColor == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byDefenseColor, s.byDefenseColor))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwRoBId is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwRoBId") != 0)
	{
		LOG_CRI << "Attribute: name is not qwRoBId!";
		return false;
	}
	const char* pszVal_qwRoBId = pElemChild->Attribute("value");
	if(pszVal_qwRoBId == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwRoBId, s.qwRoBId))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byRoBColor is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byRoBColor") != 0)
	{
		LOG_CRI << "Attribute: name is not byRoBColor!";
		return false;
	}
	const char* pszVal_byRoBColor = pElemChild->Attribute("value");
	if(pszVal_byRoBColor == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byRoBColor, s.byRoBColor))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwBattleID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwBattleID") != 0)
	{
		LOG_CRI << "Attribute: name is not qwBattleID!";
		return false;
	}
	const char* pszVal_qwBattleID = pElemChild->Attribute("value");
	if(pszVal_qwBattleID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwBattleID, s.qwBattleID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwFinishTimer is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwFinishTimer") != 0)
	{
		LOG_CRI << "Attribute: name is not dwFinishTimer!";
		return false;
	}
	const char* pszVal_dwFinishTimer = pElemChild->Attribute("value");
	if(pszVal_dwFinishTimer == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwFinishTimer, s.dwFinishTimer))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwTimer is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwTimer") != 0)
	{
		LOG_CRI << "Attribute: name is not dwTimer!";
		return false;
	}
	const char* pszVal_dwTimer = pElemChild->Attribute("value");
	if(pszVal_dwTimer == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwTimer, s.dwTimer))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byRobTimes is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byRobTimes") != 0)
	{
		LOG_CRI << "Attribute: name is not byRobTimes!";
		return false;
	}
	const char* pszVal_byRobTimes = pElemChild->Attribute("value");
	if(pszVal_byRobTimes == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byRobTimes, s.byRobTimes))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwAwardRate is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwAwardRate") != 0)
	{
		LOG_CRI << "Attribute: name is not dwAwardRate!";
		return false;
	}
	const char* pszVal_dwAwardRate = pElemChild->Attribute("value");
	if(pszVal_dwAwardRate == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwAwardRate, s.dwAwardRate))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const ShipReport& s, TiXmlElement& rElement)
{
	rElement.SetValue("ShipReport");
	rElement.SetAttribute("type", ToUTF8Ptr("金船战报"));
	unique_ptr<TiXmlElement> pElem_qwInsID(new TiXmlElement("UINT64"));
	if(pElem_qwInsID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwInsID->SetAttribute("name", "qwInsID");
	pElem_qwInsID->SetAttribute("value", NumberToString(s.qwInsID).c_str());
	pElem_qwInsID->SetAttribute("comment", ToUTF8Ptr("金船唯一ID"));
	if(rElement.LinkEndChild(pElem_qwInsID.get()) != NULL)
		pElem_qwInsID.release();
	unique_ptr<TiXmlElement> pElem_eSource(new TiXmlElement("EShipBattleSource"));
	if(pElem_eSource == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eSource->SetAttribute("name", "eSource");
	const char* pszEnum_eSource = EnumValToStr(s.eSource);
	if(pszEnum_eSource == NULL)
	{
		LOG_CRI << "EnumValToStr for EShipBattleSource fails!";
		return false;
	}
	pElem_eSource->SetAttribute("value", pszEnum_eSource);
	pElem_eSource->SetAttribute("comment", ToUTF8Ptr("战斗原因"));
	if(rElement.LinkEndChild(pElem_eSource.get()) != NULL)
		pElem_eSource.release();
	unique_ptr<TiXmlElement> pElem_qwOwer(new TiXmlElement("UINT64"));
	if(pElem_qwOwer == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwOwer->SetAttribute("name", "qwOwer");
	pElem_qwOwer->SetAttribute("value", NumberToString(s.qwOwer).c_str());
	pElem_qwOwer->SetAttribute("comment", ToUTF8Ptr("金船拥有者"));
	if(rElement.LinkEndChild(pElem_qwOwer.get()) != NULL)
		pElem_qwOwer.release();
	unique_ptr<TiXmlElement> pElem_byOwerColor(new TiXmlElement("UINT8"));
	if(pElem_byOwerColor == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byOwerColor->SetAttribute("name", "byOwerColor");
	pElem_byOwerColor->SetAttribute("value", NumberToString(s.byOwerColor).c_str());
	pElem_byOwerColor->SetAttribute("comment", ToUTF8Ptr("拥有者颜色"));
	if(rElement.LinkEndChild(pElem_byOwerColor.get()) != NULL)
		pElem_byOwerColor.release();
	unique_ptr<TiXmlElement> pElem_wShipId(new TiXmlElement("UINT16"));
	if(pElem_wShipId == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wShipId->SetAttribute("name", "wShipId");
	pElem_wShipId->SetAttribute("value", NumberToString(s.wShipId).c_str());
	pElem_wShipId->SetAttribute("comment", ToUTF8Ptr("金船模板"));
	if(rElement.LinkEndChild(pElem_wShipId.get()) != NULL)
		pElem_wShipId.release();
	unique_ptr<TiXmlElement> pElem_qwDefense(new TiXmlElement("UINT64"));
	if(pElem_qwDefense == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwDefense->SetAttribute("name", "qwDefense");
	pElem_qwDefense->SetAttribute("value", NumberToString(s.qwDefense).c_str());
	pElem_qwDefense->SetAttribute("comment", ToUTF8Ptr("护送者ID"));
	if(rElement.LinkEndChild(pElem_qwDefense.get()) != NULL)
		pElem_qwDefense.release();
	unique_ptr<TiXmlElement> pElem_byDefenseColor(new TiXmlElement("UINT8"));
	if(pElem_byDefenseColor == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byDefenseColor->SetAttribute("name", "byDefenseColor");
	pElem_byDefenseColor->SetAttribute("value", NumberToString(s.byDefenseColor).c_str());
	pElem_byDefenseColor->SetAttribute("comment", ToUTF8Ptr("护送者颜色"));
	if(rElement.LinkEndChild(pElem_byDefenseColor.get()) != NULL)
		pElem_byDefenseColor.release();
	unique_ptr<TiXmlElement> pElem_qwRoBId(new TiXmlElement("UINT64"));
	if(pElem_qwRoBId == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwRoBId->SetAttribute("name", "qwRoBId");
	pElem_qwRoBId->SetAttribute("value", NumberToString(s.qwRoBId).c_str());
	pElem_qwRoBId->SetAttribute("comment", ToUTF8Ptr("打劫者"));
	if(rElement.LinkEndChild(pElem_qwRoBId.get()) != NULL)
		pElem_qwRoBId.release();
	unique_ptr<TiXmlElement> pElem_byRoBColor(new TiXmlElement("UINT8"));
	if(pElem_byRoBColor == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byRoBColor->SetAttribute("name", "byRoBColor");
	pElem_byRoBColor->SetAttribute("value", NumberToString(s.byRoBColor).c_str());
	pElem_byRoBColor->SetAttribute("comment", ToUTF8Ptr("打劫者颜色"));
	if(rElement.LinkEndChild(pElem_byRoBColor.get()) != NULL)
		pElem_byRoBColor.release();
	unique_ptr<TiXmlElement> pElem_qwBattleID(new TiXmlElement("UINT64"));
	if(pElem_qwBattleID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwBattleID->SetAttribute("name", "qwBattleID");
	pElem_qwBattleID->SetAttribute("value", NumberToString(s.qwBattleID).c_str());
	pElem_qwBattleID->SetAttribute("comment", ToUTF8Ptr("战报ID"));
	if(rElement.LinkEndChild(pElem_qwBattleID.get()) != NULL)
		pElem_qwBattleID.release();
	unique_ptr<TiXmlElement> pElem_dwFinishTimer(new TiXmlElement("UINT32"));
	if(pElem_dwFinishTimer == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwFinishTimer->SetAttribute("name", "dwFinishTimer");
	pElem_dwFinishTimer->SetAttribute("value", NumberToString(s.dwFinishTimer).c_str());
	pElem_dwFinishTimer->SetAttribute("comment", ToUTF8Ptr("该船到达时间"));
	if(rElement.LinkEndChild(pElem_dwFinishTimer.get()) != NULL)
		pElem_dwFinishTimer.release();
	unique_ptr<TiXmlElement> pElem_dwTimer(new TiXmlElement("UINT32"));
	if(pElem_dwTimer == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwTimer->SetAttribute("name", "dwTimer");
	pElem_dwTimer->SetAttribute("value", NumberToString(s.dwTimer).c_str());
	pElem_dwTimer->SetAttribute("comment", ToUTF8Ptr("发生时间"));
	if(rElement.LinkEndChild(pElem_dwTimer.get()) != NULL)
		pElem_dwTimer.release();
	unique_ptr<TiXmlElement> pElem_byRobTimes(new TiXmlElement("UINT8"));
	if(pElem_byRobTimes == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byRobTimes->SetAttribute("name", "byRobTimes");
	pElem_byRobTimes->SetAttribute("value", NumberToString(s.byRobTimes).c_str());
	pElem_byRobTimes->SetAttribute("comment", ToUTF8Ptr("被抢劫次数"));
	if(rElement.LinkEndChild(pElem_byRobTimes.get()) != NULL)
		pElem_byRobTimes.release();
	unique_ptr<TiXmlElement> pElem_dwAwardRate(new TiXmlElement("UINT32"));
	if(pElem_dwAwardRate == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwAwardRate->SetAttribute("name", "dwAwardRate");
	pElem_dwAwardRate->SetAttribute("value", NumberToString(s.dwAwardRate).c_str());
	pElem_dwAwardRate->SetAttribute("comment", ToUTF8Ptr("奖励倍率"));
	if(rElement.LinkEndChild(pElem_dwAwardRate.get()) != NULL)
		pElem_dwAwardRate.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecShipReport& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		ShipReport s;
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

bool VectorToXML(const TVecShipReport& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("ShipReport"));
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

PlayerShipForClient::PlayerShipForClient() { }

PlayerShipForClient::PlayerShipForClient(const PlayerShip& stInfo_, const std::string& strOwerName_, const std::string& strGuipName_, const std::string& strDefenseName_, const std::string& strRoBIdName1_, 
			const std::string& strRoBIdName2_, const std::string& strRoBIdName3_)
			: stInfo(stInfo_), strOwerName(strOwerName_), strGuipName(strGuipName_), strDefenseName(strDefenseName_), strRoBIdName1(strRoBIdName1_), 
			strRoBIdName2(strRoBIdName2_), strRoBIdName3(strRoBIdName3_) { }

PlayerShipForClient::PlayerShipForClient(PlayerShipForClient&& src) : stInfo(src.stInfo), strOwerName(move(src.strOwerName)), strGuipName(move(src.strGuipName)), strDefenseName(move(src.strDefenseName)), strRoBIdName1(move(src.strRoBIdName1)), 
			strRoBIdName2(move(src.strRoBIdName2)), strRoBIdName3(move(src.strRoBIdName3)) { }

PlayerShipForClient& PlayerShipForClient::operator=(PlayerShipForClient&& rhs)
{
	if(this != &rhs)
	{
		this->~PlayerShipForClient();
		new (this) PlayerShipForClient(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, PlayerShipForClient& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.stInfo;
	src >> s.strOwerName;
	src >> s.strGuipName;
	src >> s.strDefenseName;
	src >> s.strRoBIdName1;
	src >> s.strRoBIdName2;
	src >> s.strRoBIdName3;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const PlayerShipForClient& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.stInfo;
	src << s.strOwerName;
	src << s.strGuipName;
	src << s.strDefenseName;
	src << s.strRoBIdName1;
	src << s.strRoBIdName2;
	src << s.strRoBIdName3;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, PlayerShipForClient& s)
{
	if(strcmp(rElement.Value(), "PlayerShipForClient") != 0)
	{
		LOG_CRI << "rElement is not PlayerShipForClient!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for stInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "PlayerShip") != 0)
	{
		LOG_CRI << "pElemChild is not PlayerShip!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "stInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not stInfo!";
		return false;
	}
	if(!FromXML(*pElemChild, s.stInfo))
	{
		LOG_CRI << "FromXML for: stInfo fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strOwerName is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strOwerName") != 0)
	{
		LOG_CRI << "Attribute: name is not strOwerName!";
		return false;
	}
	const char* pszVal_strOwerName = pElemChild->Attribute("value");
	if(pszVal_strOwerName == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strOwerName = pszVal_strOwerName;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strGuipName is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strGuipName") != 0)
	{
		LOG_CRI << "Attribute: name is not strGuipName!";
		return false;
	}
	const char* pszVal_strGuipName = pElemChild->Attribute("value");
	if(pszVal_strGuipName == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strGuipName = pszVal_strGuipName;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strDefenseName is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strDefenseName") != 0)
	{
		LOG_CRI << "Attribute: name is not strDefenseName!";
		return false;
	}
	const char* pszVal_strDefenseName = pElemChild->Attribute("value");
	if(pszVal_strDefenseName == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strDefenseName = pszVal_strDefenseName;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strRoBIdName1 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strRoBIdName1") != 0)
	{
		LOG_CRI << "Attribute: name is not strRoBIdName1!";
		return false;
	}
	const char* pszVal_strRoBIdName1 = pElemChild->Attribute("value");
	if(pszVal_strRoBIdName1 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strRoBIdName1 = pszVal_strRoBIdName1;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strRoBIdName2 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strRoBIdName2") != 0)
	{
		LOG_CRI << "Attribute: name is not strRoBIdName2!";
		return false;
	}
	const char* pszVal_strRoBIdName2 = pElemChild->Attribute("value");
	if(pszVal_strRoBIdName2 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strRoBIdName2 = pszVal_strRoBIdName2;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strRoBIdName3 is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strRoBIdName3") != 0)
	{
		LOG_CRI << "Attribute: name is not strRoBIdName3!";
		return false;
	}
	const char* pszVal_strRoBIdName3 = pElemChild->Attribute("value");
	if(pszVal_strRoBIdName3 == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strRoBIdName3 = pszVal_strRoBIdName3;
	return true;
}

bool ToXML(const PlayerShipForClient& s, TiXmlElement& rElement)
{
	rElement.SetValue("PlayerShipForClient");
	rElement.SetAttribute("type", ToUTF8Ptr("金船客户端信息"));
	unique_ptr<TiXmlElement> pElem_stInfo(new TiXmlElement("PlayerShip"));
	if(pElem_stInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_stInfo->SetAttribute("name", "stInfo");
	if(!ToXML(s.stInfo, *pElem_stInfo))
	{
		LOG_CRI << "stInfo ToXML fails!";
		return false;
	}
	pElem_stInfo->SetAttribute("comment", ToUTF8Ptr("金船信息"));
	if(rElement.LinkEndChild(pElem_stInfo.get()) != NULL)
		pElem_stInfo.release();
	unique_ptr<TiXmlElement> pElem_strOwerName(new TiXmlElement("string"));
	if(pElem_strOwerName == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strOwerName->SetAttribute("name", "strOwerName");
	pElem_strOwerName->SetAttribute("value", s.strOwerName.c_str());
	pElem_strOwerName->SetAttribute("comment", ToUTF8Ptr("金船拥有者名字"));
	if(rElement.LinkEndChild(pElem_strOwerName.get()) != NULL)
		pElem_strOwerName.release();
	unique_ptr<TiXmlElement> pElem_strGuipName(new TiXmlElement("string"));
	if(pElem_strGuipName == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strGuipName->SetAttribute("name", "strGuipName");
	pElem_strGuipName->SetAttribute("value", s.strGuipName.c_str());
	pElem_strGuipName->SetAttribute("comment", ToUTF8Ptr("金船拥有者帮派"));
	if(rElement.LinkEndChild(pElem_strGuipName.get()) != NULL)
		pElem_strGuipName.release();
	unique_ptr<TiXmlElement> pElem_strDefenseName(new TiXmlElement("string"));
	if(pElem_strDefenseName == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strDefenseName->SetAttribute("name", "strDefenseName");
	pElem_strDefenseName->SetAttribute("value", s.strDefenseName.c_str());
	pElem_strDefenseName->SetAttribute("comment", ToUTF8Ptr("金船护卫名字"));
	if(rElement.LinkEndChild(pElem_strDefenseName.get()) != NULL)
		pElem_strDefenseName.release();
	unique_ptr<TiXmlElement> pElem_strRoBIdName1(new TiXmlElement("string"));
	if(pElem_strRoBIdName1 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strRoBIdName1->SetAttribute("name", "strRoBIdName1");
	pElem_strRoBIdName1->SetAttribute("value", s.strRoBIdName1.c_str());
	pElem_strRoBIdName1->SetAttribute("comment", ToUTF8Ptr("金船抢劫者1名字"));
	if(rElement.LinkEndChild(pElem_strRoBIdName1.get()) != NULL)
		pElem_strRoBIdName1.release();
	unique_ptr<TiXmlElement> pElem_strRoBIdName2(new TiXmlElement("string"));
	if(pElem_strRoBIdName2 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strRoBIdName2->SetAttribute("name", "strRoBIdName2");
	pElem_strRoBIdName2->SetAttribute("value", s.strRoBIdName2.c_str());
	pElem_strRoBIdName2->SetAttribute("comment", ToUTF8Ptr("金船抢劫者2名字"));
	if(rElement.LinkEndChild(pElem_strRoBIdName2.get()) != NULL)
		pElem_strRoBIdName2.release();
	unique_ptr<TiXmlElement> pElem_strRoBIdName3(new TiXmlElement("string"));
	if(pElem_strRoBIdName3 == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strRoBIdName3->SetAttribute("name", "strRoBIdName3");
	pElem_strRoBIdName3->SetAttribute("value", s.strRoBIdName3.c_str());
	pElem_strRoBIdName3->SetAttribute("comment", ToUTF8Ptr("金船抢劫者3名字"));
	if(rElement.LinkEndChild(pElem_strRoBIdName3.get()) != NULL)
		pElem_strRoBIdName3.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecPlayerShipForClient& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		PlayerShipForClient s;
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

bool VectorToXML(const TVecPlayerShipForClient& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("PlayerShipForClient"));
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

PlayerSelfShipData::PlayerSelfShipData() : dwBuyOpenShipTimes(0), dwBuyRoBShipTimes(0), dwBuyReflushShipTimes(0), wReflushShip(0), dwReflushShipTimer(0), 
			qwInviteDefense(0), dwInviteDefenseAgreeTime(0), dwInviteDefensePoint(0), byInviteDefenseLevel(0), byInviteDefenseColor(0), 
			qwAgreeDefenseShipOwer(0), dwAgreeDefenseShipOwerTime(0) { }

CInArchive& operator>>(CInArchive& src, PlayerSelfShipData& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.dwBuyOpenShipTimes;
	src >> s.dwBuyRoBShipTimes;
	src >> s.dwBuyReflushShipTimes;
	src >> s.wReflushShip;
	src >> s.dwReflushShipTimer;
	src >> s.qwInviteDefense;
	src >> s.dwInviteDefenseAgreeTime;
	src >> s.dwInviteDefensePoint;
	src >> s.byInviteDefenseLevel;
	src >> s.byInviteDefenseColor;
	src >> s.qwAgreeDefenseShipOwer;
	src >> s.dwAgreeDefenseShipOwerTime;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const PlayerSelfShipData& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.dwBuyOpenShipTimes;
	src << s.dwBuyRoBShipTimes;
	src << s.dwBuyReflushShipTimes;
	src << s.wReflushShip;
	src << s.dwReflushShipTimer;
	src << s.qwInviteDefense;
	src << s.dwInviteDefenseAgreeTime;
	src << s.dwInviteDefensePoint;
	src << s.byInviteDefenseLevel;
	src << s.byInviteDefenseColor;
	src << s.qwAgreeDefenseShipOwer;
	src << s.dwAgreeDefenseShipOwerTime;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, PlayerSelfShipData& s)
{
	if(strcmp(rElement.Value(), "PlayerSelfShipData") != 0)
	{
		LOG_CRI << "rElement is not PlayerSelfShipData!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwBuyOpenShipTimes is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwBuyOpenShipTimes") != 0)
	{
		LOG_CRI << "Attribute: name is not dwBuyOpenShipTimes!";
		return false;
	}
	const char* pszVal_dwBuyOpenShipTimes = pElemChild->Attribute("value");
	if(pszVal_dwBuyOpenShipTimes == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwBuyOpenShipTimes, s.dwBuyOpenShipTimes))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwBuyRoBShipTimes is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwBuyRoBShipTimes") != 0)
	{
		LOG_CRI << "Attribute: name is not dwBuyRoBShipTimes!";
		return false;
	}
	const char* pszVal_dwBuyRoBShipTimes = pElemChild->Attribute("value");
	if(pszVal_dwBuyRoBShipTimes == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwBuyRoBShipTimes, s.dwBuyRoBShipTimes))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwBuyReflushShipTimes is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwBuyReflushShipTimes") != 0)
	{
		LOG_CRI << "Attribute: name is not dwBuyReflushShipTimes!";
		return false;
	}
	const char* pszVal_dwBuyReflushShipTimes = pElemChild->Attribute("value");
	if(pszVal_dwBuyReflushShipTimes == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwBuyReflushShipTimes, s.dwBuyReflushShipTimes))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wReflushShip is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wReflushShip") != 0)
	{
		LOG_CRI << "Attribute: name is not wReflushShip!";
		return false;
	}
	const char* pszVal_wReflushShip = pElemChild->Attribute("value");
	if(pszVal_wReflushShip == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wReflushShip, s.wReflushShip))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwReflushShipTimer is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwReflushShipTimer") != 0)
	{
		LOG_CRI << "Attribute: name is not dwReflushShipTimer!";
		return false;
	}
	const char* pszVal_dwReflushShipTimer = pElemChild->Attribute("value");
	if(pszVal_dwReflushShipTimer == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwReflushShipTimer, s.dwReflushShipTimer))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwInviteDefense is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwInviteDefense") != 0)
	{
		LOG_CRI << "Attribute: name is not qwInviteDefense!";
		return false;
	}
	const char* pszVal_qwInviteDefense = pElemChild->Attribute("value");
	if(pszVal_qwInviteDefense == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwInviteDefense, s.qwInviteDefense))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwInviteDefenseAgreeTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwInviteDefenseAgreeTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwInviteDefenseAgreeTime!";
		return false;
	}
	const char* pszVal_dwInviteDefenseAgreeTime = pElemChild->Attribute("value");
	if(pszVal_dwInviteDefenseAgreeTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwInviteDefenseAgreeTime, s.dwInviteDefenseAgreeTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwInviteDefensePoint is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwInviteDefensePoint") != 0)
	{
		LOG_CRI << "Attribute: name is not dwInviteDefensePoint!";
		return false;
	}
	const char* pszVal_dwInviteDefensePoint = pElemChild->Attribute("value");
	if(pszVal_dwInviteDefensePoint == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwInviteDefensePoint, s.dwInviteDefensePoint))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byInviteDefenseLevel is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byInviteDefenseLevel") != 0)
	{
		LOG_CRI << "Attribute: name is not byInviteDefenseLevel!";
		return false;
	}
	const char* pszVal_byInviteDefenseLevel = pElemChild->Attribute("value");
	if(pszVal_byInviteDefenseLevel == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byInviteDefenseLevel, s.byInviteDefenseLevel))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byInviteDefenseColor is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byInviteDefenseColor") != 0)
	{
		LOG_CRI << "Attribute: name is not byInviteDefenseColor!";
		return false;
	}
	const char* pszVal_byInviteDefenseColor = pElemChild->Attribute("value");
	if(pszVal_byInviteDefenseColor == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byInviteDefenseColor, s.byInviteDefenseColor))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwAgreeDefenseShipOwer is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwAgreeDefenseShipOwer") != 0)
	{
		LOG_CRI << "Attribute: name is not qwAgreeDefenseShipOwer!";
		return false;
	}
	const char* pszVal_qwAgreeDefenseShipOwer = pElemChild->Attribute("value");
	if(pszVal_qwAgreeDefenseShipOwer == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwAgreeDefenseShipOwer, s.qwAgreeDefenseShipOwer))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwAgreeDefenseShipOwerTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwAgreeDefenseShipOwerTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwAgreeDefenseShipOwerTime!";
		return false;
	}
	const char* pszVal_dwAgreeDefenseShipOwerTime = pElemChild->Attribute("value");
	if(pszVal_dwAgreeDefenseShipOwerTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwAgreeDefenseShipOwerTime, s.dwAgreeDefenseShipOwerTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const PlayerSelfShipData& s, TiXmlElement& rElement)
{
	rElement.SetValue("PlayerSelfShipData");
	rElement.SetAttribute("type", ToUTF8Ptr("玩家数据库信息"));
	unique_ptr<TiXmlElement> pElem_dwBuyOpenShipTimes(new TiXmlElement("UINT32"));
	if(pElem_dwBuyOpenShipTimes == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwBuyOpenShipTimes->SetAttribute("name", "dwBuyOpenShipTimes");
	pElem_dwBuyOpenShipTimes->SetAttribute("value", NumberToString(s.dwBuyOpenShipTimes).c_str());
	pElem_dwBuyOpenShipTimes->SetAttribute("comment", ToUTF8Ptr("购买的运船次数"));
	if(rElement.LinkEndChild(pElem_dwBuyOpenShipTimes.get()) != NULL)
		pElem_dwBuyOpenShipTimes.release();
	unique_ptr<TiXmlElement> pElem_dwBuyRoBShipTimes(new TiXmlElement("UINT32"));
	if(pElem_dwBuyRoBShipTimes == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwBuyRoBShipTimes->SetAttribute("name", "dwBuyRoBShipTimes");
	pElem_dwBuyRoBShipTimes->SetAttribute("value", NumberToString(s.dwBuyRoBShipTimes).c_str());
	pElem_dwBuyRoBShipTimes->SetAttribute("comment", ToUTF8Ptr("购买的抢劫次数"));
	if(rElement.LinkEndChild(pElem_dwBuyRoBShipTimes.get()) != NULL)
		pElem_dwBuyRoBShipTimes.release();
	unique_ptr<TiXmlElement> pElem_dwBuyReflushShipTimes(new TiXmlElement("UINT32"));
	if(pElem_dwBuyReflushShipTimes == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwBuyReflushShipTimes->SetAttribute("name", "dwBuyReflushShipTimes");
	pElem_dwBuyReflushShipTimes->SetAttribute("value", NumberToString(s.dwBuyReflushShipTimes).c_str());
	pElem_dwBuyReflushShipTimes->SetAttribute("comment", ToUTF8Ptr("购买的刷新次数"));
	if(rElement.LinkEndChild(pElem_dwBuyReflushShipTimes.get()) != NULL)
		pElem_dwBuyReflushShipTimes.release();
	unique_ptr<TiXmlElement> pElem_wReflushShip(new TiXmlElement("UINT16"));
	if(pElem_wReflushShip == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wReflushShip->SetAttribute("name", "wReflushShip");
	pElem_wReflushShip->SetAttribute("value", NumberToString(s.wReflushShip).c_str());
	pElem_wReflushShip->SetAttribute("comment", ToUTF8Ptr("刷出来的船"));
	if(rElement.LinkEndChild(pElem_wReflushShip.get()) != NULL)
		pElem_wReflushShip.release();
	unique_ptr<TiXmlElement> pElem_dwReflushShipTimer(new TiXmlElement("UINT32"));
	if(pElem_dwReflushShipTimer == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwReflushShipTimer->SetAttribute("name", "dwReflushShipTimer");
	pElem_dwReflushShipTimer->SetAttribute("value", NumberToString(s.dwReflushShipTimer).c_str());
	pElem_dwReflushShipTimer->SetAttribute("comment", ToUTF8Ptr("刷船的时间"));
	if(rElement.LinkEndChild(pElem_dwReflushShipTimer.get()) != NULL)
		pElem_dwReflushShipTimer.release();
	unique_ptr<TiXmlElement> pElem_qwInviteDefense(new TiXmlElement("UINT64"));
	if(pElem_qwInviteDefense == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwInviteDefense->SetAttribute("name", "qwInviteDefense");
	pElem_qwInviteDefense->SetAttribute("value", NumberToString(s.qwInviteDefense).c_str());
	pElem_qwInviteDefense->SetAttribute("comment", ToUTF8Ptr("邀请的护送者"));
	if(rElement.LinkEndChild(pElem_qwInviteDefense.get()) != NULL)
		pElem_qwInviteDefense.release();
	unique_ptr<TiXmlElement> pElem_dwInviteDefenseAgreeTime(new TiXmlElement("UINT32"));
	if(pElem_dwInviteDefenseAgreeTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwInviteDefenseAgreeTime->SetAttribute("name", "dwInviteDefenseAgreeTime");
	pElem_dwInviteDefenseAgreeTime->SetAttribute("value", NumberToString(s.dwInviteDefenseAgreeTime).c_str());
	pElem_dwInviteDefenseAgreeTime->SetAttribute("comment", ToUTF8Ptr("别人同意护送的时间"));
	if(rElement.LinkEndChild(pElem_dwInviteDefenseAgreeTime.get()) != NULL)
		pElem_dwInviteDefenseAgreeTime.release();
	unique_ptr<TiXmlElement> pElem_dwInviteDefensePoint(new TiXmlElement("UINT32"));
	if(pElem_dwInviteDefensePoint == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwInviteDefensePoint->SetAttribute("name", "dwInviteDefensePoint");
	pElem_dwInviteDefensePoint->SetAttribute("value", NumberToString(s.dwInviteDefensePoint).c_str());
	pElem_dwInviteDefensePoint->SetAttribute("comment", ToUTF8Ptr("护送者战斗力"));
	if(rElement.LinkEndChild(pElem_dwInviteDefensePoint.get()) != NULL)
		pElem_dwInviteDefensePoint.release();
	unique_ptr<TiXmlElement> pElem_byInviteDefenseLevel(new TiXmlElement("UINT8"));
	if(pElem_byInviteDefenseLevel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byInviteDefenseLevel->SetAttribute("name", "byInviteDefenseLevel");
	pElem_byInviteDefenseLevel->SetAttribute("value", NumberToString(s.byInviteDefenseLevel).c_str());
	pElem_byInviteDefenseLevel->SetAttribute("comment", ToUTF8Ptr("护送者等级"));
	if(rElement.LinkEndChild(pElem_byInviteDefenseLevel.get()) != NULL)
		pElem_byInviteDefenseLevel.release();
	unique_ptr<TiXmlElement> pElem_byInviteDefenseColor(new TiXmlElement("UINT8"));
	if(pElem_byInviteDefenseColor == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byInviteDefenseColor->SetAttribute("name", "byInviteDefenseColor");
	pElem_byInviteDefenseColor->SetAttribute("value", NumberToString(s.byInviteDefenseColor).c_str());
	pElem_byInviteDefenseColor->SetAttribute("comment", ToUTF8Ptr("护送者颜色"));
	if(rElement.LinkEndChild(pElem_byInviteDefenseColor.get()) != NULL)
		pElem_byInviteDefenseColor.release();
	unique_ptr<TiXmlElement> pElem_qwAgreeDefenseShipOwer(new TiXmlElement("UINT64"));
	if(pElem_qwAgreeDefenseShipOwer == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwAgreeDefenseShipOwer->SetAttribute("name", "qwAgreeDefenseShipOwer");
	pElem_qwAgreeDefenseShipOwer->SetAttribute("value", NumberToString(s.qwAgreeDefenseShipOwer).c_str());
	pElem_qwAgreeDefenseShipOwer->SetAttribute("comment", ToUTF8Ptr("我同意护送的船"));
	if(rElement.LinkEndChild(pElem_qwAgreeDefenseShipOwer.get()) != NULL)
		pElem_qwAgreeDefenseShipOwer.release();
	unique_ptr<TiXmlElement> pElem_dwAgreeDefenseShipOwerTime(new TiXmlElement("UINT32"));
	if(pElem_dwAgreeDefenseShipOwerTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwAgreeDefenseShipOwerTime->SetAttribute("name", "dwAgreeDefenseShipOwerTime");
	pElem_dwAgreeDefenseShipOwerTime->SetAttribute("value", NumberToString(s.dwAgreeDefenseShipOwerTime).c_str());
	pElem_dwAgreeDefenseShipOwerTime->SetAttribute("comment", ToUTF8Ptr("我同意护送的时间"));
	if(rElement.LinkEndChild(pElem_dwAgreeDefenseShipOwerTime.get()) != NULL)
		pElem_dwAgreeDefenseShipOwerTime.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecPlayerSelfShipData& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		PlayerSelfShipData s;
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

bool VectorToXML(const TVecPlayerSelfShipData& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("PlayerSelfShipData"));
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

PlayerShipForList::PlayerShipForList() : qwInsID(0), qwOwer(0), wShipId(0), byChannel(0), dwBeginTimer(0), 
			dwEndTimer(0) { }

PlayerShipForList::PlayerShipForList(UINT64 qwInsID_, UINT64 qwOwer_, UINT16 wShipId_, UINT8 byChannel_, UINT32 dwBeginTimer_, 
			UINT32 dwEndTimer_)
			: qwInsID(qwInsID_), qwOwer(qwOwer_), wShipId(wShipId_), byChannel(byChannel_), dwBeginTimer(dwBeginTimer_), 
			dwEndTimer(dwEndTimer_) { }

CInArchive& operator>>(CInArchive& src, PlayerShipForList& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwInsID;
	src >> s.qwOwer;
	src >> s.wShipId;
	src >> s.byChannel;
	src >> s.dwBeginTimer;
	src >> s.dwEndTimer;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const PlayerShipForList& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.qwInsID;
	src << s.qwOwer;
	src << s.wShipId;
	src << s.byChannel;
	src << s.dwBeginTimer;
	src << s.dwEndTimer;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, PlayerShipForList& s)
{
	if(strcmp(rElement.Value(), "PlayerShipForList") != 0)
	{
		LOG_CRI << "rElement is not PlayerShipForList!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwInsID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwInsID") != 0)
	{
		LOG_CRI << "Attribute: name is not qwInsID!";
		return false;
	}
	const char* pszVal_qwInsID = pElemChild->Attribute("value");
	if(pszVal_qwInsID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwInsID, s.qwInsID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwOwer is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwOwer") != 0)
	{
		LOG_CRI << "Attribute: name is not qwOwer!";
		return false;
	}
	const char* pszVal_qwOwer = pElemChild->Attribute("value");
	if(pszVal_qwOwer == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwOwer, s.qwOwer))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wShipId is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wShipId") != 0)
	{
		LOG_CRI << "Attribute: name is not wShipId!";
		return false;
	}
	const char* pszVal_wShipId = pElemChild->Attribute("value");
	if(pszVal_wShipId == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wShipId, s.wShipId))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byChannel is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byChannel") != 0)
	{
		LOG_CRI << "Attribute: name is not byChannel!";
		return false;
	}
	const char* pszVal_byChannel = pElemChild->Attribute("value");
	if(pszVal_byChannel == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byChannel, s.byChannel))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwBeginTimer is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwBeginTimer") != 0)
	{
		LOG_CRI << "Attribute: name is not dwBeginTimer!";
		return false;
	}
	const char* pszVal_dwBeginTimer = pElemChild->Attribute("value");
	if(pszVal_dwBeginTimer == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwBeginTimer, s.dwBeginTimer))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwEndTimer is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwEndTimer") != 0)
	{
		LOG_CRI << "Attribute: name is not dwEndTimer!";
		return false;
	}
	const char* pszVal_dwEndTimer = pElemChild->Attribute("value");
	if(pszVal_dwEndTimer == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwEndTimer, s.dwEndTimer))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const PlayerShipForList& s, TiXmlElement& rElement)
{
	rElement.SetValue("PlayerShipForList");
	rElement.SetAttribute("type", ToUTF8Ptr("列表信息"));
	unique_ptr<TiXmlElement> pElem_qwInsID(new TiXmlElement("UINT64"));
	if(pElem_qwInsID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwInsID->SetAttribute("name", "qwInsID");
	pElem_qwInsID->SetAttribute("value", NumberToString(s.qwInsID).c_str());
	pElem_qwInsID->SetAttribute("comment", ToUTF8Ptr("金船唯一ID"));
	if(rElement.LinkEndChild(pElem_qwInsID.get()) != NULL)
		pElem_qwInsID.release();
	unique_ptr<TiXmlElement> pElem_qwOwer(new TiXmlElement("UINT64"));
	if(pElem_qwOwer == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwOwer->SetAttribute("name", "qwOwer");
	pElem_qwOwer->SetAttribute("value", NumberToString(s.qwOwer).c_str());
	pElem_qwOwer->SetAttribute("comment", ToUTF8Ptr("金船拥有者"));
	if(rElement.LinkEndChild(pElem_qwOwer.get()) != NULL)
		pElem_qwOwer.release();
	unique_ptr<TiXmlElement> pElem_wShipId(new TiXmlElement("UINT16"));
	if(pElem_wShipId == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wShipId->SetAttribute("name", "wShipId");
	pElem_wShipId->SetAttribute("value", NumberToString(s.wShipId).c_str());
	pElem_wShipId->SetAttribute("comment", ToUTF8Ptr("船模板"));
	if(rElement.LinkEndChild(pElem_wShipId.get()) != NULL)
		pElem_wShipId.release();
	unique_ptr<TiXmlElement> pElem_byChannel(new TiXmlElement("UINT8"));
	if(pElem_byChannel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byChannel->SetAttribute("name", "byChannel");
	pElem_byChannel->SetAttribute("value", NumberToString(s.byChannel).c_str());
	pElem_byChannel->SetAttribute("comment", ToUTF8Ptr("航道"));
	if(rElement.LinkEndChild(pElem_byChannel.get()) != NULL)
		pElem_byChannel.release();
	unique_ptr<TiXmlElement> pElem_dwBeginTimer(new TiXmlElement("UINT32"));
	if(pElem_dwBeginTimer == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwBeginTimer->SetAttribute("name", "dwBeginTimer");
	pElem_dwBeginTimer->SetAttribute("value", NumberToString(s.dwBeginTimer).c_str());
	pElem_dwBeginTimer->SetAttribute("comment", ToUTF8Ptr("开船时间"));
	if(rElement.LinkEndChild(pElem_dwBeginTimer.get()) != NULL)
		pElem_dwBeginTimer.release();
	unique_ptr<TiXmlElement> pElem_dwEndTimer(new TiXmlElement("UINT32"));
	if(pElem_dwEndTimer == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwEndTimer->SetAttribute("name", "dwEndTimer");
	pElem_dwEndTimer->SetAttribute("value", NumberToString(s.dwEndTimer).c_str());
	pElem_dwEndTimer->SetAttribute("comment", ToUTF8Ptr("结束时间"));
	if(rElement.LinkEndChild(pElem_dwEndTimer.get()) != NULL)
		pElem_dwEndTimer.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecPlayerShipForList& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		PlayerShipForList s;
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

bool VectorToXML(const TVecPlayerShipForList& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("PlayerShipForList"));
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

PlayerSelfView::PlayerSelfView() : dwRobTimes(0), byDefenseTimes(0), dwOpenShipTimes(0), dwReFluseTimes(0), dwBuyRobTimes(0), 
			dwBuyOpenShipTimesToday(0), dwBuyRlushShipTimesToday(0), dwFreezBattleTime(0), dwBeginTimer(0), dwEndTimer(0), 
			qwDefenseShip(0), qwSelfShip(0) { }

PlayerSelfView::PlayerSelfView(PlayerSelfView&& src) : stData(src.stData), dwRobTimes(src.dwRobTimes), byDefenseTimes(src.byDefenseTimes), dwOpenShipTimes(src.dwOpenShipTimes), dwReFluseTimes(src.dwReFluseTimes), 
			dwBuyRobTimes(src.dwBuyRobTimes), dwBuyOpenShipTimesToday(src.dwBuyOpenShipTimesToday), dwBuyRlushShipTimesToday(src.dwBuyRlushShipTimesToday), dwFreezBattleTime(src.dwFreezBattleTime), dwBeginTimer(src.dwBeginTimer), 
			dwEndTimer(src.dwEndTimer), qwDefenseShip(src.qwDefenseShip), qwSelfShip(src.qwSelfShip), strInviteDefenseName(move(src.strInviteDefenseName)) { }

PlayerSelfView& PlayerSelfView::operator=(PlayerSelfView&& rhs)
{
	if(this != &rhs)
	{
		this->~PlayerSelfView();
		new (this) PlayerSelfView(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, PlayerSelfView& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.stData;
	src >> s.dwRobTimes;
	src >> s.byDefenseTimes;
	src >> s.dwOpenShipTimes;
	src >> s.dwReFluseTimes;
	src >> s.dwBuyRobTimes;
	src >> s.dwBuyOpenShipTimesToday;
	src >> s.dwBuyRlushShipTimesToday;
	src >> s.dwFreezBattleTime;
	src >> s.dwBeginTimer;
	src >> s.dwEndTimer;
	src >> s.qwDefenseShip;
	src >> s.qwSelfShip;
	src >> s.strInviteDefenseName;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const PlayerSelfView& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.stData;
	src << s.dwRobTimes;
	src << s.byDefenseTimes;
	src << s.dwOpenShipTimes;
	src << s.dwReFluseTimes;
	src << s.dwBuyRobTimes;
	src << s.dwBuyOpenShipTimesToday;
	src << s.dwBuyRlushShipTimesToday;
	src << s.dwFreezBattleTime;
	src << s.dwBeginTimer;
	src << s.dwEndTimer;
	src << s.qwDefenseShip;
	src << s.qwSelfShip;
	src << s.strInviteDefenseName;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, PlayerSelfView& s)
{
	if(strcmp(rElement.Value(), "PlayerSelfView") != 0)
	{
		LOG_CRI << "rElement is not PlayerSelfView!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for stData is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "PlayerSelfShipData") != 0)
	{
		LOG_CRI << "pElemChild is not PlayerSelfShipData!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "stData") != 0)
	{
		LOG_CRI << "Attribute: name is not stData!";
		return false;
	}
	if(!FromXML(*pElemChild, s.stData))
	{
		LOG_CRI << "FromXML for: stData fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwRobTimes is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwRobTimes") != 0)
	{
		LOG_CRI << "Attribute: name is not dwRobTimes!";
		return false;
	}
	const char* pszVal_dwRobTimes = pElemChild->Attribute("value");
	if(pszVal_dwRobTimes == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwRobTimes, s.dwRobTimes))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byDefenseTimes is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byDefenseTimes") != 0)
	{
		LOG_CRI << "Attribute: name is not byDefenseTimes!";
		return false;
	}
	const char* pszVal_byDefenseTimes = pElemChild->Attribute("value");
	if(pszVal_byDefenseTimes == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byDefenseTimes, s.byDefenseTimes))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwOpenShipTimes is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwOpenShipTimes") != 0)
	{
		LOG_CRI << "Attribute: name is not dwOpenShipTimes!";
		return false;
	}
	const char* pszVal_dwOpenShipTimes = pElemChild->Attribute("value");
	if(pszVal_dwOpenShipTimes == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwOpenShipTimes, s.dwOpenShipTimes))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwReFluseTimes is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwReFluseTimes") != 0)
	{
		LOG_CRI << "Attribute: name is not dwReFluseTimes!";
		return false;
	}
	const char* pszVal_dwReFluseTimes = pElemChild->Attribute("value");
	if(pszVal_dwReFluseTimes == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwReFluseTimes, s.dwReFluseTimes))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwBuyRobTimes is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwBuyRobTimes") != 0)
	{
		LOG_CRI << "Attribute: name is not dwBuyRobTimes!";
		return false;
	}
	const char* pszVal_dwBuyRobTimes = pElemChild->Attribute("value");
	if(pszVal_dwBuyRobTimes == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwBuyRobTimes, s.dwBuyRobTimes))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwBuyOpenShipTimesToday is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwBuyOpenShipTimesToday") != 0)
	{
		LOG_CRI << "Attribute: name is not dwBuyOpenShipTimesToday!";
		return false;
	}
	const char* pszVal_dwBuyOpenShipTimesToday = pElemChild->Attribute("value");
	if(pszVal_dwBuyOpenShipTimesToday == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwBuyOpenShipTimesToday, s.dwBuyOpenShipTimesToday))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwBuyRlushShipTimesToday is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwBuyRlushShipTimesToday") != 0)
	{
		LOG_CRI << "Attribute: name is not dwBuyRlushShipTimesToday!";
		return false;
	}
	const char* pszVal_dwBuyRlushShipTimesToday = pElemChild->Attribute("value");
	if(pszVal_dwBuyRlushShipTimesToday == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwBuyRlushShipTimesToday, s.dwBuyRlushShipTimesToday))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwFreezBattleTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwFreezBattleTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwFreezBattleTime!";
		return false;
	}
	const char* pszVal_dwFreezBattleTime = pElemChild->Attribute("value");
	if(pszVal_dwFreezBattleTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwFreezBattleTime, s.dwFreezBattleTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwBeginTimer is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwBeginTimer") != 0)
	{
		LOG_CRI << "Attribute: name is not dwBeginTimer!";
		return false;
	}
	const char* pszVal_dwBeginTimer = pElemChild->Attribute("value");
	if(pszVal_dwBeginTimer == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwBeginTimer, s.dwBeginTimer))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwEndTimer is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwEndTimer") != 0)
	{
		LOG_CRI << "Attribute: name is not dwEndTimer!";
		return false;
	}
	const char* pszVal_dwEndTimer = pElemChild->Attribute("value");
	if(pszVal_dwEndTimer == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwEndTimer, s.dwEndTimer))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwDefenseShip is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwDefenseShip") != 0)
	{
		LOG_CRI << "Attribute: name is not qwDefenseShip!";
		return false;
	}
	const char* pszVal_qwDefenseShip = pElemChild->Attribute("value");
	if(pszVal_qwDefenseShip == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwDefenseShip, s.qwDefenseShip))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwSelfShip is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwSelfShip") != 0)
	{
		LOG_CRI << "Attribute: name is not qwSelfShip!";
		return false;
	}
	const char* pszVal_qwSelfShip = pElemChild->Attribute("value");
	if(pszVal_qwSelfShip == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwSelfShip, s.qwSelfShip))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strInviteDefenseName is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strInviteDefenseName") != 0)
	{
		LOG_CRI << "Attribute: name is not strInviteDefenseName!";
		return false;
	}
	const char* pszVal_strInviteDefenseName = pElemChild->Attribute("value");
	if(pszVal_strInviteDefenseName == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strInviteDefenseName = pszVal_strInviteDefenseName;
	return true;
}

bool ToXML(const PlayerSelfView& s, TiXmlElement& rElement)
{
	rElement.SetValue("PlayerSelfView");
	rElement.SetAttribute("type", ToUTF8Ptr("玩家信息"));
	unique_ptr<TiXmlElement> pElem_stData(new TiXmlElement("PlayerSelfShipData"));
	if(pElem_stData == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_stData->SetAttribute("name", "stData");
	if(!ToXML(s.stData, *pElem_stData))
	{
		LOG_CRI << "stData ToXML fails!";
		return false;
	}
	pElem_stData->SetAttribute("comment", ToUTF8Ptr("基本信息"));
	if(rElement.LinkEndChild(pElem_stData.get()) != NULL)
		pElem_stData.release();
	unique_ptr<TiXmlElement> pElem_dwRobTimes(new TiXmlElement("UINT32"));
	if(pElem_dwRobTimes == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwRobTimes->SetAttribute("name", "dwRobTimes");
	pElem_dwRobTimes->SetAttribute("value", NumberToString(s.dwRobTimes).c_str());
	pElem_dwRobTimes->SetAttribute("comment", ToUTF8Ptr("抢劫次数"));
	if(rElement.LinkEndChild(pElem_dwRobTimes.get()) != NULL)
		pElem_dwRobTimes.release();
	unique_ptr<TiXmlElement> pElem_byDefenseTimes(new TiXmlElement("UINT8"));
	if(pElem_byDefenseTimes == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byDefenseTimes->SetAttribute("name", "byDefenseTimes");
	pElem_byDefenseTimes->SetAttribute("value", NumberToString(s.byDefenseTimes).c_str());
	pElem_byDefenseTimes->SetAttribute("comment", ToUTF8Ptr("护送次数"));
	if(rElement.LinkEndChild(pElem_byDefenseTimes.get()) != NULL)
		pElem_byDefenseTimes.release();
	unique_ptr<TiXmlElement> pElem_dwOpenShipTimes(new TiXmlElement("UINT32"));
	if(pElem_dwOpenShipTimes == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwOpenShipTimes->SetAttribute("name", "dwOpenShipTimes");
	pElem_dwOpenShipTimes->SetAttribute("value", NumberToString(s.dwOpenShipTimes).c_str());
	pElem_dwOpenShipTimes->SetAttribute("comment", ToUTF8Ptr("开船次数"));
	if(rElement.LinkEndChild(pElem_dwOpenShipTimes.get()) != NULL)
		pElem_dwOpenShipTimes.release();
	unique_ptr<TiXmlElement> pElem_dwReFluseTimes(new TiXmlElement("UINT32"));
	if(pElem_dwReFluseTimes == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwReFluseTimes->SetAttribute("name", "dwReFluseTimes");
	pElem_dwReFluseTimes->SetAttribute("value", NumberToString(s.dwReFluseTimes).c_str());
	pElem_dwReFluseTimes->SetAttribute("comment", ToUTF8Ptr("刷新次数"));
	if(rElement.LinkEndChild(pElem_dwReFluseTimes.get()) != NULL)
		pElem_dwReFluseTimes.release();
	unique_ptr<TiXmlElement> pElem_dwBuyRobTimes(new TiXmlElement("UINT32"));
	if(pElem_dwBuyRobTimes == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwBuyRobTimes->SetAttribute("name", "dwBuyRobTimes");
	pElem_dwBuyRobTimes->SetAttribute("value", NumberToString(s.dwBuyRobTimes).c_str());
	pElem_dwBuyRobTimes->SetAttribute("comment", ToUTF8Ptr("今日购买的抢劫次数"));
	if(rElement.LinkEndChild(pElem_dwBuyRobTimes.get()) != NULL)
		pElem_dwBuyRobTimes.release();
	unique_ptr<TiXmlElement> pElem_dwBuyOpenShipTimesToday(new TiXmlElement("UINT32"));
	if(pElem_dwBuyOpenShipTimesToday == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwBuyOpenShipTimesToday->SetAttribute("name", "dwBuyOpenShipTimesToday");
	pElem_dwBuyOpenShipTimesToday->SetAttribute("value", NumberToString(s.dwBuyOpenShipTimesToday).c_str());
	pElem_dwBuyOpenShipTimesToday->SetAttribute("comment", ToUTF8Ptr("今日购买的运船次数"));
	if(rElement.LinkEndChild(pElem_dwBuyOpenShipTimesToday.get()) != NULL)
		pElem_dwBuyOpenShipTimesToday.release();
	unique_ptr<TiXmlElement> pElem_dwBuyRlushShipTimesToday(new TiXmlElement("UINT32"));
	if(pElem_dwBuyRlushShipTimesToday == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwBuyRlushShipTimesToday->SetAttribute("name", "dwBuyRlushShipTimesToday");
	pElem_dwBuyRlushShipTimesToday->SetAttribute("value", NumberToString(s.dwBuyRlushShipTimesToday).c_str());
	pElem_dwBuyRlushShipTimesToday->SetAttribute("comment", ToUTF8Ptr("今日购买的刷新次数"));
	if(rElement.LinkEndChild(pElem_dwBuyRlushShipTimesToday.get()) != NULL)
		pElem_dwBuyRlushShipTimesToday.release();
	unique_ptr<TiXmlElement> pElem_dwFreezBattleTime(new TiXmlElement("UINT32"));
	if(pElem_dwFreezBattleTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwFreezBattleTime->SetAttribute("name", "dwFreezBattleTime");
	pElem_dwFreezBattleTime->SetAttribute("value", NumberToString(s.dwFreezBattleTime).c_str());
	pElem_dwFreezBattleTime->SetAttribute("comment", ToUTF8Ptr("金船战斗冷却时间"));
	if(rElement.LinkEndChild(pElem_dwFreezBattleTime.get()) != NULL)
		pElem_dwFreezBattleTime.release();
	unique_ptr<TiXmlElement> pElem_dwBeginTimer(new TiXmlElement("UINT32"));
	if(pElem_dwBeginTimer == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwBeginTimer->SetAttribute("name", "dwBeginTimer");
	pElem_dwBeginTimer->SetAttribute("value", NumberToString(s.dwBeginTimer).c_str());
	pElem_dwBeginTimer->SetAttribute("comment", ToUTF8Ptr("自己开船时间"));
	if(rElement.LinkEndChild(pElem_dwBeginTimer.get()) != NULL)
		pElem_dwBeginTimer.release();
	unique_ptr<TiXmlElement> pElem_dwEndTimer(new TiXmlElement("UINT32"));
	if(pElem_dwEndTimer == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwEndTimer->SetAttribute("name", "dwEndTimer");
	pElem_dwEndTimer->SetAttribute("value", NumberToString(s.dwEndTimer).c_str());
	pElem_dwEndTimer->SetAttribute("comment", ToUTF8Ptr("自己船结束时间"));
	if(rElement.LinkEndChild(pElem_dwEndTimer.get()) != NULL)
		pElem_dwEndTimer.release();
	unique_ptr<TiXmlElement> pElem_qwDefenseShip(new TiXmlElement("UINT64"));
	if(pElem_qwDefenseShip == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwDefenseShip->SetAttribute("name", "qwDefenseShip");
	pElem_qwDefenseShip->SetAttribute("value", NumberToString(s.qwDefenseShip).c_str());
	pElem_qwDefenseShip->SetAttribute("comment", ToUTF8Ptr("我护送的船"));
	if(rElement.LinkEndChild(pElem_qwDefenseShip.get()) != NULL)
		pElem_qwDefenseShip.release();
	unique_ptr<TiXmlElement> pElem_qwSelfShip(new TiXmlElement("UINT64"));
	if(pElem_qwSelfShip == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwSelfShip->SetAttribute("name", "qwSelfShip");
	pElem_qwSelfShip->SetAttribute("value", NumberToString(s.qwSelfShip).c_str());
	pElem_qwSelfShip->SetAttribute("comment", ToUTF8Ptr("我自己的船"));
	if(rElement.LinkEndChild(pElem_qwSelfShip.get()) != NULL)
		pElem_qwSelfShip.release();
	unique_ptr<TiXmlElement> pElem_strInviteDefenseName(new TiXmlElement("string"));
	if(pElem_strInviteDefenseName == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strInviteDefenseName->SetAttribute("name", "strInviteDefenseName");
	pElem_strInviteDefenseName->SetAttribute("value", s.strInviteDefenseName.c_str());
	pElem_strInviteDefenseName->SetAttribute("comment", ToUTF8Ptr("同意护送者名字"));
	if(rElement.LinkEndChild(pElem_strInviteDefenseName.get()) != NULL)
		pElem_strInviteDefenseName.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecPlayerSelfView& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		PlayerSelfView s;
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

bool VectorToXML(const TVecPlayerSelfView& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("PlayerSelfView"));
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

ShipReportForClient::ShipReportForClient() : eResult((NBattleGS::EBattleResult)0) { }

ShipReportForClient::ShipReportForClient(const ShipReport& stInfo_, NBattleGS::EBattleResult eResult_, const std::string& strOwerName_, const std::string& strDefenseName_, const std::string& strRoBIdName_)
			: stInfo(stInfo_), eResult(eResult_), strOwerName(strOwerName_), strDefenseName(strDefenseName_), strRoBIdName(strRoBIdName_) { }

ShipReportForClient::ShipReportForClient(ShipReportForClient&& src) : stInfo(src.stInfo), eResult(src.eResult), strOwerName(move(src.strOwerName)), strDefenseName(move(src.strDefenseName)), strRoBIdName(move(src.strRoBIdName)) { }

ShipReportForClient& ShipReportForClient::operator=(ShipReportForClient&& rhs)
{
	if(this != &rhs)
	{
		this->~ShipReportForClient();
		new (this) ShipReportForClient(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, ShipReportForClient& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.stInfo;
	src >> (UINT8&)s.eResult;
	src >> s.strOwerName;
	src >> s.strDefenseName;
	src >> s.strRoBIdName;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const ShipReportForClient& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.stInfo;
	src << (UINT8&)s.eResult;
	src << s.strOwerName;
	src << s.strDefenseName;
	src << s.strRoBIdName;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, ShipReportForClient& s)
{
	if(strcmp(rElement.Value(), "ShipReportForClient") != 0)
	{
		LOG_CRI << "rElement is not ShipReportForClient!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for stInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "ShipReport") != 0)
	{
		LOG_CRI << "pElemChild is not ShipReport!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "stInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not stInfo!";
		return false;
	}
	if(!FromXML(*pElemChild, s.stInfo))
	{
		LOG_CRI << "FromXML for: stInfo fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eResult is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "BattleGS::EBattleResult") != 0)
	{
		LOG_CRI << "pElemChild is not BattleGS::EBattleResult!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "eResult") != 0)
	{
		LOG_CRI << "Attribute: name is not eResult!";
		return false;
	}
	const char* pszVal_eResult = pElemChild->Attribute("value");
	if(pszVal_eResult == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!NBattleGS::EnumStrToVal(pszVal_eResult, s.eResult))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strOwerName is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strOwerName") != 0)
	{
		LOG_CRI << "Attribute: name is not strOwerName!";
		return false;
	}
	const char* pszVal_strOwerName = pElemChild->Attribute("value");
	if(pszVal_strOwerName == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strOwerName = pszVal_strOwerName;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strDefenseName is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strDefenseName") != 0)
	{
		LOG_CRI << "Attribute: name is not strDefenseName!";
		return false;
	}
	const char* pszVal_strDefenseName = pElemChild->Attribute("value");
	if(pszVal_strDefenseName == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strDefenseName = pszVal_strDefenseName;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strRoBIdName is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strRoBIdName") != 0)
	{
		LOG_CRI << "Attribute: name is not strRoBIdName!";
		return false;
	}
	const char* pszVal_strRoBIdName = pElemChild->Attribute("value");
	if(pszVal_strRoBIdName == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strRoBIdName = pszVal_strRoBIdName;
	return true;
}

bool ToXML(const ShipReportForClient& s, TiXmlElement& rElement)
{
	rElement.SetValue("ShipReportForClient");
	rElement.SetAttribute("type", ToUTF8Ptr("金船战报客户端信息"));
	unique_ptr<TiXmlElement> pElem_stInfo(new TiXmlElement("ShipReport"));
	if(pElem_stInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_stInfo->SetAttribute("name", "stInfo");
	if(!ToXML(s.stInfo, *pElem_stInfo))
	{
		LOG_CRI << "stInfo ToXML fails!";
		return false;
	}
	pElem_stInfo->SetAttribute("comment", ToUTF8Ptr("战报信息"));
	if(rElement.LinkEndChild(pElem_stInfo.get()) != NULL)
		pElem_stInfo.release();
	unique_ptr<TiXmlElement> pElem_eResult(new TiXmlElement("BattleGS::EBattleResult"));
	if(pElem_eResult == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eResult->SetAttribute("name", "eResult");
	const char* pszEnum_eResult = NBattleGS::EnumValToStr(s.eResult);
	if(pszEnum_eResult == NULL)
	{
		LOG_CRI << "EnumValToStr for eResult fails!";
		return false;
	}
	pElem_eResult->SetAttribute("value", pszEnum_eResult);
	pElem_eResult->SetAttribute("comment", ToUTF8Ptr(""));
	if(rElement.LinkEndChild(pElem_eResult.get()) != NULL)
		pElem_eResult.release();
	unique_ptr<TiXmlElement> pElem_strOwerName(new TiXmlElement("string"));
	if(pElem_strOwerName == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strOwerName->SetAttribute("name", "strOwerName");
	pElem_strOwerName->SetAttribute("value", s.strOwerName.c_str());
	pElem_strOwerName->SetAttribute("comment", ToUTF8Ptr("金船拥有者名字"));
	if(rElement.LinkEndChild(pElem_strOwerName.get()) != NULL)
		pElem_strOwerName.release();
	unique_ptr<TiXmlElement> pElem_strDefenseName(new TiXmlElement("string"));
	if(pElem_strDefenseName == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strDefenseName->SetAttribute("name", "strDefenseName");
	pElem_strDefenseName->SetAttribute("value", s.strDefenseName.c_str());
	pElem_strDefenseName->SetAttribute("comment", ToUTF8Ptr("金船护卫名字"));
	if(rElement.LinkEndChild(pElem_strDefenseName.get()) != NULL)
		pElem_strDefenseName.release();
	unique_ptr<TiXmlElement> pElem_strRoBIdName(new TiXmlElement("string"));
	if(pElem_strRoBIdName == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strRoBIdName->SetAttribute("name", "strRoBIdName");
	pElem_strRoBIdName->SetAttribute("value", s.strRoBIdName.c_str());
	pElem_strRoBIdName->SetAttribute("comment", ToUTF8Ptr("金船抢劫者名字"));
	if(rElement.LinkEndChild(pElem_strRoBIdName.get()) != NULL)
		pElem_strRoBIdName.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecShipReportForClient& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		ShipReportForClient s;
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

bool VectorToXML(const TVecShipReportForClient& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("ShipReportForClient"));
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

} //namespace NShipProt
