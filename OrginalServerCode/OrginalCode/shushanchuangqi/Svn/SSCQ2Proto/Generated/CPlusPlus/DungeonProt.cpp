/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    DungeonProt.cpp
//  Purpose:      副本相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "DungeonProt.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NDungeonProt
{

#ifdef PROT_USE_XML

const char* EnumValToStr(EDungeonResult e)
{
	switch(e)
	{
	case eDungeonSuccess:
		return "eDungeonSuccess";
	case eDungeonSweepingErr:
		return "eDungeonSweepingErr";
	case eDungeonPowerErr:
		return "eDungeonPowerErr";
	case eDungeonNotSweepingErr:
		return "eDungeonNotSweepingErr";
	case eDungeonSweepingSpeedUpErr:
		return "eDungeonSweepingSpeedUpErr";
	case eDungeonTypeNotExist:
		return "eDungeonTypeNotExist";
	case eDungeonInDgn:
		return "eDungeonInDgn";
	case eDungeonLowLevel:
		return "eDungeonLowLevel";
	case eDungeonCreateErrType:
		return "eDungeonCreateErrType";
	case eDungeonPreDgnNotFinish:
		return "eDungeonPreDgnNotFinish";
	case eDungeonPackEmptyMin:
		return "eDungeonPackEmptyMin";
	case eDungeonOutDgn:
		return "eDungeonOutDgn";
	case eDungeonInsNotExist:
		return "eDungeonInsNotExist";
	case eDungeonNotFinish:
		return "eDungeonNotFinish";
	case eDungeonBusy:
		return "eDungeonBusy";
	case eDungeonNotSweeping:
		return "eDungeonNotSweeping";
	case eSpeedUpItemLimit:
		return "eSpeedUpItemLimit";
	case eDungeonTimesLimit:
		return "eDungeonTimesLimit";
	case eDungeonTimesLimitForHero:
		return "eDungeonTimesLimitForHero";
	case eDungeonTimesLimitForLiXian:
		return "eDungeonTimesLimitForLiXian";
	case eDungeonVipBuyHero:
		return "eDungeonVipBuyHero";
	case eDungeonVipBuyLiXian:
		return "eDungeonVipBuyLiXian";
	case eDungeonNOGold:
		return "eDungeonNOGold";
	case eDungeonOtherErr:
		return "eDungeonOtherErr";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EDungeonResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EDungeonResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eDungeonSuccess", eDungeonSuccess));
		mapStr2Val.insert(make_pair("eDungeonSweepingErr", eDungeonSweepingErr));
		mapStr2Val.insert(make_pair("eDungeonPowerErr", eDungeonPowerErr));
		mapStr2Val.insert(make_pair("eDungeonNotSweepingErr", eDungeonNotSweepingErr));
		mapStr2Val.insert(make_pair("eDungeonSweepingSpeedUpErr", eDungeonSweepingSpeedUpErr));
		mapStr2Val.insert(make_pair("eDungeonTypeNotExist", eDungeonTypeNotExist));
		mapStr2Val.insert(make_pair("eDungeonInDgn", eDungeonInDgn));
		mapStr2Val.insert(make_pair("eDungeonLowLevel", eDungeonLowLevel));
		mapStr2Val.insert(make_pair("eDungeonCreateErrType", eDungeonCreateErrType));
		mapStr2Val.insert(make_pair("eDungeonPreDgnNotFinish", eDungeonPreDgnNotFinish));
		mapStr2Val.insert(make_pair("eDungeonPackEmptyMin", eDungeonPackEmptyMin));
		mapStr2Val.insert(make_pair("eDungeonOutDgn", eDungeonOutDgn));
		mapStr2Val.insert(make_pair("eDungeonInsNotExist", eDungeonInsNotExist));
		mapStr2Val.insert(make_pair("eDungeonNotFinish", eDungeonNotFinish));
		mapStr2Val.insert(make_pair("eDungeonBusy", eDungeonBusy));
		mapStr2Val.insert(make_pair("eDungeonNotSweeping", eDungeonNotSweeping));
		mapStr2Val.insert(make_pair("eSpeedUpItemLimit", eSpeedUpItemLimit));
		mapStr2Val.insert(make_pair("eDungeonTimesLimit", eDungeonTimesLimit));
		mapStr2Val.insert(make_pair("eDungeonTimesLimitForHero", eDungeonTimesLimitForHero));
		mapStr2Val.insert(make_pair("eDungeonTimesLimitForLiXian", eDungeonTimesLimitForLiXian));
		mapStr2Val.insert(make_pair("eDungeonVipBuyHero", eDungeonVipBuyHero));
		mapStr2Val.insert(make_pair("eDungeonVipBuyLiXian", eDungeonVipBuyLiXian));
		mapStr2Val.insert(make_pair("eDungeonNOGold", eDungeonNOGold));
		mapStr2Val.insert(make_pair("eDungeonOtherErr", eDungeonOtherErr));
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

const char* GetDescription(EDungeonResult e)
{
	switch(e)
	{
	case eDungeonSuccess:
		return "成功";
	case eDungeonSweepingErr:
		return "正在扫荡中";
	case eDungeonPowerErr:
		return "体力不足";
	case eDungeonNotSweepingErr:
		return "不在扫荡中";
	case eDungeonSweepingSpeedUpErr:
		return "扫荡加速中";
	case eDungeonTypeNotExist:
		return "此副本类型不存在";
	case eDungeonInDgn:
		return "你在副本中";
	case eDungeonLowLevel:
		return "你等级不够";
	case eDungeonCreateErrType:
		return "副本类型不正确，不可以创建副本";
	case eDungeonPreDgnNotFinish:
		return "前置副本未完成";
	case eDungeonPackEmptyMin:
		return "包裹空格子不足";
	case eDungeonOutDgn:
		return "你不在副本中";
	case eDungeonInsNotExist:
		return "副本不存在";
	case eDungeonNotFinish:
		return "副本未完成";
	case eDungeonBusy:
		return "玩家忙";
	case eDungeonNotSweeping:
		return "不在扫荡状态";
	case eSpeedUpItemLimit:
		return "加速道具不足";
	case eDungeonTimesLimit:
		return "进入次数不足";
	case eDungeonTimesLimitForHero:
		return "英雄本进入次数不足";
	case eDungeonTimesLimitForLiXian:
		return "历险本进入次数不足";
	case eDungeonVipBuyHero:
		return "购买英雄副本vip等级不足";
	case eDungeonVipBuyLiXian:
		return "购买历险副本vip等级不足";
	case eDungeonNOGold:
		return "仙石不足";
	case eDungeonOtherErr:
		return "未知错误";
	default:
		return "未知错误";
	}
}

#ifdef PROT_USE_XML

const char* EnumValToStr(EDgnType e)
{
	switch(e)
	{
	case eNoneDgn:
		return "eNoneDgn";
	case ePlayerDgn:
		return "ePlayerDgn";
	case eGatherDgn:
		return "eGatherDgn";
	case eTeamDgn:
		return "eTeamDgn";
	case eDemonTowerDgn:
		return "eDemonTowerDgn";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EDgnType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EDgnType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eNoneDgn", eNoneDgn));
		mapStr2Val.insert(make_pair("ePlayerDgn", ePlayerDgn));
		mapStr2Val.insert(make_pair("eGatherDgn", eGatherDgn));
		mapStr2Val.insert(make_pair("eTeamDgn", eTeamDgn));
		mapStr2Val.insert(make_pair("eDemonTowerDgn", eDemonTowerDgn));
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

const char* GetDescription(EDgnType e)
{
	switch(e)
	{
	case eNoneDgn:
		return "无定义";
	case ePlayerDgn:
		return "单人副本";
	case eGatherDgn:
		return "采集副本";
	case eTeamDgn:
		return "组队副本";
	case eDemonTowerDgn:
		return "镇妖塔副本";
	default:
		return "未知错误";
	}
}

#ifdef PROT_USE_XML

const char* EnumValToStr(EDgnSubType e)
{
	switch(e)
	{
	case eSubCommon:
		return "eSubCommon";
	case eSubHero:
		return "eSubHero";
	case eSubHistory:
		return "eSubHistory";
	case eSubLiXian:
		return "eSubLiXian";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EDgnSubType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EDgnSubType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eSubCommon", eSubCommon));
		mapStr2Val.insert(make_pair("eSubHero", eSubHero));
		mapStr2Val.insert(make_pair("eSubHistory", eSubHistory));
		mapStr2Val.insert(make_pair("eSubLiXian", eSubLiXian));
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

const char* GetDescription(EDgnSubType e)
{
	switch(e)
	{
	case eSubCommon:
		return "普通";
	case eSubHero:
		return "英雄副本";
	case eSubHistory:
		return "史诗副本";
	case eSubLiXian:
		return "历险副本";
	default:
		return "未知错误";
	}
}

#ifdef PROT_USE_XML

const char* EnumValToStr(EDgnCondStatus e)
{
	switch(e)
	{
	case eCondRun:
		return "eCondRun";
	case eCondSuc:
		return "eCondSuc";
	case eCondFal:
		return "eCondFal";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EDgnCondStatus& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EDgnCondStatus> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eCondRun", eCondRun));
		mapStr2Val.insert(make_pair("eCondSuc", eCondSuc));
		mapStr2Val.insert(make_pair("eCondFal", eCondFal));
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

const char* GetDescription(EDgnCondStatus e)
{
	switch(e)
	{
	case eCondRun:
		return "未达成";
	case eCondSuc:
		return "已达成";
	case eCondFal:
		return "已失败";
	default:
		return "未知错误";
	}
}

#ifdef PROT_USE_XML

const char* EnumValToStr(ELogicType e)
{
	switch(e)
	{
	case eLogicNone:
		return "eLogicNone";
	case eLogicOrderMonster:
		return "eLogicOrderMonster";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, ELogicType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, ELogicType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eLogicNone", eLogicNone));
		mapStr2Val.insert(make_pair("eLogicOrderMonster", eLogicOrderMonster));
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

const char* GetDescription(ELogicType e)
{
	switch(e)
	{
	case eLogicNone:
		return "无评价";
	case eLogicOrderMonster:
		return "按顺序杀怪";
	default:
		return "未知错误";
	}
}

DgnSucCond::DgnSucCond() : wCondId(0), eStatus((EDgnCondStatus)0) { }

CInArchive& operator>>(CInArchive& src, DgnSucCond& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.wCondId;
	src >> (UINT8&)s.eStatus;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const DgnSucCond& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.wCondId;
	src << (UINT8&)s.eStatus;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, DgnSucCond_Wrapper& rWrapper)
{
	EType_DgnSucCond eType = eType_DgnSucCond;
	src >> (UINT8&)eType;
	switch(eType)
	{
	case eType_DgnSucCond:
		{
			rWrapper.ptr.reset(new DgnSucCond);
			src >> (DgnSucCond&)*rWrapper.ptr;
		}
		break;
	case eType_SucMonster:
		{
			rWrapper.ptr.reset(new SucMonster);
			src >> (SucMonster&)*rWrapper.ptr;
		}
		break;
	case eType_SucGather:
		{
			rWrapper.ptr.reset(new SucGather);
			src >> (SucGather&)*rWrapper.ptr;
		}
		break;
	case eType_SucTurns:
		{
			rWrapper.ptr.reset(new SucTurns);
			src >> (SucTurns&)*rWrapper.ptr;
		}
		break;
	case eType_SucInTimer:
		{
			rWrapper.ptr.reset(new SucInTimer);
			src >> (SucInTimer&)*rWrapper.ptr;
		}
		break;
	case eType_SucMonsterInTimer:
		{
			rWrapper.ptr.reset(new SucMonsterInTimer);
			src >> (SucMonsterInTimer&)*rWrapper.ptr;
		}
		break;
	case eType_SucGatherInTimer:
		{
			rWrapper.ptr.reset(new SucGatherInTimer);
			src >> (SucGatherInTimer&)*rWrapper.ptr;
		}
		break;
	case eType_SucFightWithMonsterMinTimes:
		{
			rWrapper.ptr.reset(new SucFightWithMonsterMinTimes);
			src >> (SucFightWithMonsterMinTimes&)*rWrapper.ptr;
		}
		break;
	case eType_SucArriveArea:
		{
			rWrapper.ptr.reset(new SucArriveArea);
			src >> (SucArriveArea&)*rWrapper.ptr;
		}
		break;
	default:
		throw "Unknown value for EType_DgnSucCond";
		break;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const DgnSucCond_Wrapper& rWrapper)
{
	if(rWrapper.ptr != NULL)
	{
		src << (UINT8)rWrapper.ptr->GetClassType();
		switch(rWrapper.ptr->GetClassType())
		{
		case eType_DgnSucCond:
			src << (DgnSucCond&)*rWrapper.ptr;
			break;
		case eType_SucMonster:
			src << (SucMonster&)*rWrapper.ptr;
			break;
		case eType_SucGather:
			src << (SucGather&)*rWrapper.ptr;
			break;
		case eType_SucTurns:
			src << (SucTurns&)*rWrapper.ptr;
			break;
		case eType_SucInTimer:
			src << (SucInTimer&)*rWrapper.ptr;
			break;
		case eType_SucMonsterInTimer:
			src << (SucMonsterInTimer&)*rWrapper.ptr;
			break;
		case eType_SucGatherInTimer:
			src << (SucGatherInTimer&)*rWrapper.ptr;
			break;
		case eType_SucFightWithMonsterMinTimes:
			src << (SucFightWithMonsterMinTimes&)*rWrapper.ptr;
			break;
		case eType_SucArriveArea:
			src << (SucArriveArea&)*rWrapper.ptr;
			break;
		default:
			throw "Unknown value for EType_DgnSucCond";
			break;
		}
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecSucCond& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		DgnSucCond_Wrapper wrapper;
		src >> wrapper;
		vec[i] = wrapper.ptr;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecSucCond& vec)
{
	if(vec.size() > 0x7FFF)
		throw "Vector Size Too Large!";
	UINT16 wSize = (UINT16)vec.size();
	src.WriteContainerSize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		DgnSucCond_Wrapper wrapper;
		wrapper.ptr = vec[i];
		src << wrapper;
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, DgnSucCond& s)
{
	if(strcmp(rElement.Value(), "DgnSucCond") != 0)
	{
		LOG_CRI << "rElement is not DgnSucCond!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wCondId is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wCondId") != 0)
	{
		LOG_CRI << "Attribute: name is not wCondId!";
		return false;
	}
	const char* pszVal_wCondId = pElemChild->Attribute("value");
	if(pszVal_wCondId == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wCondId, s.wCondId))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for eStatus is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "EDgnCondStatus") != 0)
	{
		LOG_CRI << "pElemChild is not EDgnCondStatus!";
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
	return true;
}

bool ToXML(const DgnSucCond& s, TiXmlElement& rElement)
{
	rElement.SetValue("DgnSucCond");
	rElement.SetAttribute("type", ToUTF8Ptr("副本条件"));
	unique_ptr<TiXmlElement> pElem_wCondId(new TiXmlElement("UINT16"));
	if(pElem_wCondId == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wCondId->SetAttribute("name", "wCondId");
	pElem_wCondId->SetAttribute("value", NumberToString(s.wCondId).c_str());
	pElem_wCondId->SetAttribute("comment", ToUTF8Ptr("条件ID"));
	if(rElement.LinkEndChild(pElem_wCondId.get()) != NULL)
		pElem_wCondId.release();
	unique_ptr<TiXmlElement> pElem_eStatus(new TiXmlElement("EDgnCondStatus"));
	if(pElem_eStatus == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_eStatus->SetAttribute("name", "eStatus");
	const char* pszEnum_eStatus = EnumValToStr(s.eStatus);
	if(pszEnum_eStatus == NULL)
	{
		LOG_CRI << "EnumValToStr for EDgnCondStatus fails!";
		return false;
	}
	pElem_eStatus->SetAttribute("value", pszEnum_eStatus);
	pElem_eStatus->SetAttribute("comment", ToUTF8Ptr("0,未达成，1表示已达成，2表示已失败"));
	if(rElement.LinkEndChild(pElem_eStatus.get()) != NULL)
		pElem_eStatus.release();
	return true;
}

bool SuperFromXML(TiXmlElement& rElement, DgnSucCondPtr& p)
{
	const char* pszName = rElement.Value();
	if(pszName == NULL)
	{
		LOG_CRI << "Element Name is empty!";
		return false;
	}
	if(strcmp(pszName, "DgnSucCond") == 0)
	{
		DgnSucCondPtr pStruct(new DgnSucCond);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for DgnSucCond";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "DgnSucCond FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SucMonster") == 0)
	{
		SucMonsterPtr pStruct(new SucMonster);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SucMonster";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SucMonster FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SucGather") == 0)
	{
		SucGatherPtr pStruct(new SucGather);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SucGather";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SucGather FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SucTurns") == 0)
	{
		SucTurnsPtr pStruct(new SucTurns);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SucTurns";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SucTurns FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SucInTimer") == 0)
	{
		SucInTimerPtr pStruct(new SucInTimer);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SucInTimer";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SucInTimer FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SucMonsterInTimer") == 0)
	{
		SucMonsterInTimerPtr pStruct(new SucMonsterInTimer);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SucMonsterInTimer";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SucMonsterInTimer FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SucGatherInTimer") == 0)
	{
		SucGatherInTimerPtr pStruct(new SucGatherInTimer);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SucGatherInTimer";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SucGatherInTimer FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SucFightWithMonsterMinTimes") == 0)
	{
		SucFightWithMonsterMinTimesPtr pStruct(new SucFightWithMonsterMinTimes);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SucFightWithMonsterMinTimes";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SucFightWithMonsterMinTimes FromXML fails!";
			return false;
		}
		p = pStruct;
	}
	else if(strcmp(pszName, "SucArriveArea") == 0)
	{
		SucArriveAreaPtr pStruct(new SucArriveArea);
		if(pStruct == NULL)
		{
			LOG_CRI << "Can't allow memory for SucArriveArea";
			return false;
		}
		if(!FromXML(rElement, *pStruct))
		{
			LOG_CRI << "SucArriveArea FromXML fails!";
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

bool SuperToXML(const DgnSucCond& s, TiXmlElement& rElement)
{
	switch(s.GetClassType())
	{
	case eType_DgnSucCond:
		return ToXML((DgnSucCond&)s, rElement);
	case eType_SucMonster:
		return ToXML((SucMonster&)s, rElement);
	case eType_SucGather:
		return ToXML((SucGather&)s, rElement);
	case eType_SucTurns:
		return ToXML((SucTurns&)s, rElement);
	case eType_SucInTimer:
		return ToXML((SucInTimer&)s, rElement);
	case eType_SucMonsterInTimer:
		return ToXML((SucMonsterInTimer&)s, rElement);
	case eType_SucGatherInTimer:
		return ToXML((SucGatherInTimer&)s, rElement);
	case eType_SucFightWithMonsterMinTimes:
		return ToXML((SucFightWithMonsterMinTimes&)s, rElement);
	case eType_SucArriveArea:
		return ToXML((SucArriveArea&)s, rElement);
	default:
		LOG_CRI << "Invalid type: " << s.GetClassType();
		return false;
	}
}

bool VectorFromXML(TiXmlElement& rElement, TVecSucCond& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		DgnSucCondPtr p;
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

bool VectorToXML(const TVecSucCond& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("DgnSucCond"));
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

SucMonster::SucMonster() : wMonsterGroup(0), byTotalNum(0), byCurNum(0) { }

CInArchive& operator>>(CInArchive& src, SucMonster& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (DgnSucCond&)s;
	src >> s.wMonsterGroup;
	src >> s.byTotalNum;
	src >> s.byCurNum;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SucMonster& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const DgnSucCond&)s;
	src << s.wMonsterGroup;
	src << s.byTotalNum;
	src << s.byCurNum;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecSucMonster& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SucMonsterPtr p(new SucMonster);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecSucMonster& vec)
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

bool FromXML(TiXmlElement& rElement, SucMonster& s)
{
	if(strcmp(rElement.Value(), "SucMonster") != 0)
	{
		LOG_CRI << "rElement is not SucMonster!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for DgnSucCond is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (DgnSucCond&)s))
	{
		LOG_CRI << "FromXML for: DgnSucCond fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wMonsterGroup is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wMonsterGroup") != 0)
	{
		LOG_CRI << "Attribute: name is not wMonsterGroup!";
		return false;
	}
	const char* pszVal_wMonsterGroup = pElemChild->Attribute("value");
	if(pszVal_wMonsterGroup == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wMonsterGroup, s.wMonsterGroup))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byTotalNum is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byTotalNum") != 0)
	{
		LOG_CRI << "Attribute: name is not byTotalNum!";
		return false;
	}
	const char* pszVal_byTotalNum = pElemChild->Attribute("value");
	if(pszVal_byTotalNum == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byTotalNum, s.byTotalNum))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byCurNum is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byCurNum") != 0)
	{
		LOG_CRI << "Attribute: name is not byCurNum!";
		return false;
	}
	const char* pszVal_byCurNum = pElemChild->Attribute("value");
	if(pszVal_byCurNum == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byCurNum, s.byCurNum))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SucMonster& s, TiXmlElement& rElement)
{
	rElement.SetValue("SucMonster");
	rElement.SetAttribute("type", ToUTF8Ptr("杀怪条件"));
	unique_ptr<TiXmlElement> pElem_DgnSucCond(new TiXmlElement("DgnSucCond"));
	if(pElem_DgnSucCond == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const DgnSucCond&)s, *pElem_DgnSucCond))
	{
		LOG_CRI << "DgnSucCond ToXML fails!";
		return false;
	}
	pElem_DgnSucCond->SetAttribute("type", ToUTF8Ptr("副本条件"));
	pElem_DgnSucCond->SetAttribute("comment", ToUTF8Ptr("父类DgnSucCond部分"));
	if(rElement.LinkEndChild(pElem_DgnSucCond.get()) != NULL)
		pElem_DgnSucCond.release();
	unique_ptr<TiXmlElement> pElem_wMonsterGroup(new TiXmlElement("UINT16"));
	if(pElem_wMonsterGroup == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wMonsterGroup->SetAttribute("name", "wMonsterGroup");
	pElem_wMonsterGroup->SetAttribute("value", NumberToString(s.wMonsterGroup).c_str());
	pElem_wMonsterGroup->SetAttribute("comment", ToUTF8Ptr("怪物组ID"));
	if(rElement.LinkEndChild(pElem_wMonsterGroup.get()) != NULL)
		pElem_wMonsterGroup.release();
	unique_ptr<TiXmlElement> pElem_byTotalNum(new TiXmlElement("UINT8"));
	if(pElem_byTotalNum == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byTotalNum->SetAttribute("name", "byTotalNum");
	pElem_byTotalNum->SetAttribute("value", NumberToString(s.byTotalNum).c_str());
	pElem_byTotalNum->SetAttribute("comment", ToUTF8Ptr("怪物总数"));
	if(rElement.LinkEndChild(pElem_byTotalNum.get()) != NULL)
		pElem_byTotalNum.release();
	unique_ptr<TiXmlElement> pElem_byCurNum(new TiXmlElement("UINT8"));
	if(pElem_byCurNum == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byCurNum->SetAttribute("name", "byCurNum");
	pElem_byCurNum->SetAttribute("value", NumberToString(s.byCurNum).c_str());
	pElem_byCurNum->SetAttribute("comment", ToUTF8Ptr("当前数量"));
	if(rElement.LinkEndChild(pElem_byCurNum.get()) != NULL)
		pElem_byCurNum.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecSucMonster& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SucMonsterPtr p(new SucMonster);
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

bool VectorToXML(const TVecSucMonster& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SucMonster"));
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

SucGather::SucGather() : wGather(0), byTotalNum(0), byCurNum(0) { }

CInArchive& operator>>(CInArchive& src, SucGather& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (DgnSucCond&)s;
	src >> s.wGather;
	src >> s.byTotalNum;
	src >> s.byCurNum;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SucGather& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const DgnSucCond&)s;
	src << s.wGather;
	src << s.byTotalNum;
	src << s.byCurNum;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecSucGather& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SucGatherPtr p(new SucGather);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecSucGather& vec)
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

bool FromXML(TiXmlElement& rElement, SucGather& s)
{
	if(strcmp(rElement.Value(), "SucGather") != 0)
	{
		LOG_CRI << "rElement is not SucGather!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for DgnSucCond is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (DgnSucCond&)s))
	{
		LOG_CRI << "FromXML for: DgnSucCond fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wGather is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wGather") != 0)
	{
		LOG_CRI << "Attribute: name is not wGather!";
		return false;
	}
	const char* pszVal_wGather = pElemChild->Attribute("value");
	if(pszVal_wGather == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wGather, s.wGather))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byTotalNum is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byTotalNum") != 0)
	{
		LOG_CRI << "Attribute: name is not byTotalNum!";
		return false;
	}
	const char* pszVal_byTotalNum = pElemChild->Attribute("value");
	if(pszVal_byTotalNum == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byTotalNum, s.byTotalNum))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byCurNum is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byCurNum") != 0)
	{
		LOG_CRI << "Attribute: name is not byCurNum!";
		return false;
	}
	const char* pszVal_byCurNum = pElemChild->Attribute("value");
	if(pszVal_byCurNum == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byCurNum, s.byCurNum))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SucGather& s, TiXmlElement& rElement)
{
	rElement.SetValue("SucGather");
	rElement.SetAttribute("type", ToUTF8Ptr("采集条件"));
	unique_ptr<TiXmlElement> pElem_DgnSucCond(new TiXmlElement("DgnSucCond"));
	if(pElem_DgnSucCond == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const DgnSucCond&)s, *pElem_DgnSucCond))
	{
		LOG_CRI << "DgnSucCond ToXML fails!";
		return false;
	}
	pElem_DgnSucCond->SetAttribute("type", ToUTF8Ptr("副本条件"));
	pElem_DgnSucCond->SetAttribute("comment", ToUTF8Ptr("父类DgnSucCond部分"));
	if(rElement.LinkEndChild(pElem_DgnSucCond.get()) != NULL)
		pElem_DgnSucCond.release();
	unique_ptr<TiXmlElement> pElem_wGather(new TiXmlElement("UINT16"));
	if(pElem_wGather == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wGather->SetAttribute("name", "wGather");
	pElem_wGather->SetAttribute("value", NumberToString(s.wGather).c_str());
	pElem_wGather->SetAttribute("comment", ToUTF8Ptr("采集ID"));
	if(rElement.LinkEndChild(pElem_wGather.get()) != NULL)
		pElem_wGather.release();
	unique_ptr<TiXmlElement> pElem_byTotalNum(new TiXmlElement("UINT8"));
	if(pElem_byTotalNum == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byTotalNum->SetAttribute("name", "byTotalNum");
	pElem_byTotalNum->SetAttribute("value", NumberToString(s.byTotalNum).c_str());
	pElem_byTotalNum->SetAttribute("comment", ToUTF8Ptr("采集总数"));
	if(rElement.LinkEndChild(pElem_byTotalNum.get()) != NULL)
		pElem_byTotalNum.release();
	unique_ptr<TiXmlElement> pElem_byCurNum(new TiXmlElement("UINT8"));
	if(pElem_byCurNum == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byCurNum->SetAttribute("name", "byCurNum");
	pElem_byCurNum->SetAttribute("value", NumberToString(s.byCurNum).c_str());
	pElem_byCurNum->SetAttribute("comment", ToUTF8Ptr("当前数量"));
	if(rElement.LinkEndChild(pElem_byCurNum.get()) != NULL)
		pElem_byCurNum.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecSucGather& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SucGatherPtr p(new SucGather);
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

bool VectorToXML(const TVecSucGather& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SucGather"));
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

SucTurns::SucTurns() : byTotalTurns(0), byCurTurns(0) { }

CInArchive& operator>>(CInArchive& src, SucTurns& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (DgnSucCond&)s;
	src >> s.byTotalTurns;
	src >> s.byCurTurns;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SucTurns& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const DgnSucCond&)s;
	src << s.byTotalTurns;
	src << s.byCurTurns;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecSucTurns& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SucTurnsPtr p(new SucTurns);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecSucTurns& vec)
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

bool FromXML(TiXmlElement& rElement, SucTurns& s)
{
	if(strcmp(rElement.Value(), "SucTurns") != 0)
	{
		LOG_CRI << "rElement is not SucTurns!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for DgnSucCond is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (DgnSucCond&)s))
	{
		LOG_CRI << "FromXML for: DgnSucCond fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byTotalTurns is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byTotalTurns") != 0)
	{
		LOG_CRI << "Attribute: name is not byTotalTurns!";
		return false;
	}
	const char* pszVal_byTotalTurns = pElemChild->Attribute("value");
	if(pszVal_byTotalTurns == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byTotalTurns, s.byTotalTurns))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byCurTurns is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byCurTurns") != 0)
	{
		LOG_CRI << "Attribute: name is not byCurTurns!";
		return false;
	}
	const char* pszVal_byCurTurns = pElemChild->Attribute("value");
	if(pszVal_byCurTurns == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byCurTurns, s.byCurTurns))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SucTurns& s, TiXmlElement& rElement)
{
	rElement.SetValue("SucTurns");
	rElement.SetAttribute("type", ToUTF8Ptr("回合数判定"));
	unique_ptr<TiXmlElement> pElem_DgnSucCond(new TiXmlElement("DgnSucCond"));
	if(pElem_DgnSucCond == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const DgnSucCond&)s, *pElem_DgnSucCond))
	{
		LOG_CRI << "DgnSucCond ToXML fails!";
		return false;
	}
	pElem_DgnSucCond->SetAttribute("type", ToUTF8Ptr("副本条件"));
	pElem_DgnSucCond->SetAttribute("comment", ToUTF8Ptr("父类DgnSucCond部分"));
	if(rElement.LinkEndChild(pElem_DgnSucCond.get()) != NULL)
		pElem_DgnSucCond.release();
	unique_ptr<TiXmlElement> pElem_byTotalTurns(new TiXmlElement("UINT8"));
	if(pElem_byTotalTurns == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byTotalTurns->SetAttribute("name", "byTotalTurns");
	pElem_byTotalTurns->SetAttribute("value", NumberToString(s.byTotalTurns).c_str());
	pElem_byTotalTurns->SetAttribute("comment", ToUTF8Ptr("总回合数"));
	if(rElement.LinkEndChild(pElem_byTotalTurns.get()) != NULL)
		pElem_byTotalTurns.release();
	unique_ptr<TiXmlElement> pElem_byCurTurns(new TiXmlElement("UINT8"));
	if(pElem_byCurTurns == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byCurTurns->SetAttribute("name", "byCurTurns");
	pElem_byCurTurns->SetAttribute("value", NumberToString(s.byCurTurns).c_str());
	pElem_byCurTurns->SetAttribute("comment", ToUTF8Ptr("当前回合数"));
	if(rElement.LinkEndChild(pElem_byCurTurns.get()) != NULL)
		pElem_byCurTurns.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecSucTurns& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SucTurnsPtr p(new SucTurns);
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

bool VectorToXML(const TVecSucTurns& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SucTurns"));
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

SucInTimer::SucInTimer() : dwTotalTimer(0), dwBeginTimer(0) { }

CInArchive& operator>>(CInArchive& src, SucInTimer& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (DgnSucCond&)s;
	src >> s.dwTotalTimer;
	src >> s.dwBeginTimer;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SucInTimer& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const DgnSucCond&)s;
	src << s.dwTotalTimer;
	src << s.dwBeginTimer;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecSucInTimer& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SucInTimerPtr p(new SucInTimer);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecSucInTimer& vec)
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

bool FromXML(TiXmlElement& rElement, SucInTimer& s)
{
	if(strcmp(rElement.Value(), "SucInTimer") != 0)
	{
		LOG_CRI << "rElement is not SucInTimer!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for DgnSucCond is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (DgnSucCond&)s))
	{
		LOG_CRI << "FromXML for: DgnSucCond fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwTotalTimer is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwTotalTimer") != 0)
	{
		LOG_CRI << "Attribute: name is not dwTotalTimer!";
		return false;
	}
	const char* pszVal_dwTotalTimer = pElemChild->Attribute("value");
	if(pszVal_dwTotalTimer == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwTotalTimer, s.dwTotalTimer))
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
	return true;
}

bool ToXML(const SucInTimer& s, TiXmlElement& rElement)
{
	rElement.SetValue("SucInTimer");
	rElement.SetAttribute("type", ToUTF8Ptr("时间判定"));
	unique_ptr<TiXmlElement> pElem_DgnSucCond(new TiXmlElement("DgnSucCond"));
	if(pElem_DgnSucCond == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const DgnSucCond&)s, *pElem_DgnSucCond))
	{
		LOG_CRI << "DgnSucCond ToXML fails!";
		return false;
	}
	pElem_DgnSucCond->SetAttribute("type", ToUTF8Ptr("副本条件"));
	pElem_DgnSucCond->SetAttribute("comment", ToUTF8Ptr("父类DgnSucCond部分"));
	if(rElement.LinkEndChild(pElem_DgnSucCond.get()) != NULL)
		pElem_DgnSucCond.release();
	unique_ptr<TiXmlElement> pElem_dwTotalTimer(new TiXmlElement("UINT32"));
	if(pElem_dwTotalTimer == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwTotalTimer->SetAttribute("name", "dwTotalTimer");
	pElem_dwTotalTimer->SetAttribute("value", NumberToString(s.dwTotalTimer).c_str());
	pElem_dwTotalTimer->SetAttribute("comment", ToUTF8Ptr("总计时间"));
	if(rElement.LinkEndChild(pElem_dwTotalTimer.get()) != NULL)
		pElem_dwTotalTimer.release();
	unique_ptr<TiXmlElement> pElem_dwBeginTimer(new TiXmlElement("UINT32"));
	if(pElem_dwBeginTimer == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwBeginTimer->SetAttribute("name", "dwBeginTimer");
	pElem_dwBeginTimer->SetAttribute("value", NumberToString(s.dwBeginTimer).c_str());
	pElem_dwBeginTimer->SetAttribute("comment", ToUTF8Ptr("起始时间"));
	if(rElement.LinkEndChild(pElem_dwBeginTimer.get()) != NULL)
		pElem_dwBeginTimer.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecSucInTimer& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SucInTimerPtr p(new SucInTimer);
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

bool VectorToXML(const TVecSucInTimer& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SucInTimer"));
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

SucMonsterInTimer::SucMonsterInTimer() : dwTotalTimer(0), dwBeginTimer(0), wMonsterGroup(0), byTotalNum(0), byCurNum(0) { }

CInArchive& operator>>(CInArchive& src, SucMonsterInTimer& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (DgnSucCond&)s;
	src >> s.dwTotalTimer;
	src >> s.dwBeginTimer;
	src >> s.wMonsterGroup;
	src >> s.byTotalNum;
	src >> s.byCurNum;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SucMonsterInTimer& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const DgnSucCond&)s;
	src << s.dwTotalTimer;
	src << s.dwBeginTimer;
	src << s.wMonsterGroup;
	src << s.byTotalNum;
	src << s.byCurNum;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecSucMonsterInTimer& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SucMonsterInTimerPtr p(new SucMonsterInTimer);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecSucMonsterInTimer& vec)
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

bool FromXML(TiXmlElement& rElement, SucMonsterInTimer& s)
{
	if(strcmp(rElement.Value(), "SucMonsterInTimer") != 0)
	{
		LOG_CRI << "rElement is not SucMonsterInTimer!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for DgnSucCond is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (DgnSucCond&)s))
	{
		LOG_CRI << "FromXML for: DgnSucCond fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwTotalTimer is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwTotalTimer") != 0)
	{
		LOG_CRI << "Attribute: name is not dwTotalTimer!";
		return false;
	}
	const char* pszVal_dwTotalTimer = pElemChild->Attribute("value");
	if(pszVal_dwTotalTimer == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwTotalTimer, s.dwTotalTimer))
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
		LOG_CRI << "pElemChild for wMonsterGroup is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wMonsterGroup") != 0)
	{
		LOG_CRI << "Attribute: name is not wMonsterGroup!";
		return false;
	}
	const char* pszVal_wMonsterGroup = pElemChild->Attribute("value");
	if(pszVal_wMonsterGroup == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wMonsterGroup, s.wMonsterGroup))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byTotalNum is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byTotalNum") != 0)
	{
		LOG_CRI << "Attribute: name is not byTotalNum!";
		return false;
	}
	const char* pszVal_byTotalNum = pElemChild->Attribute("value");
	if(pszVal_byTotalNum == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byTotalNum, s.byTotalNum))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byCurNum is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byCurNum") != 0)
	{
		LOG_CRI << "Attribute: name is not byCurNum!";
		return false;
	}
	const char* pszVal_byCurNum = pElemChild->Attribute("value");
	if(pszVal_byCurNum == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byCurNum, s.byCurNum))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SucMonsterInTimer& s, TiXmlElement& rElement)
{
	rElement.SetValue("SucMonsterInTimer");
	rElement.SetAttribute("type", ToUTF8Ptr("定时杀怪"));
	unique_ptr<TiXmlElement> pElem_DgnSucCond(new TiXmlElement("DgnSucCond"));
	if(pElem_DgnSucCond == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const DgnSucCond&)s, *pElem_DgnSucCond))
	{
		LOG_CRI << "DgnSucCond ToXML fails!";
		return false;
	}
	pElem_DgnSucCond->SetAttribute("type", ToUTF8Ptr("副本条件"));
	pElem_DgnSucCond->SetAttribute("comment", ToUTF8Ptr("父类DgnSucCond部分"));
	if(rElement.LinkEndChild(pElem_DgnSucCond.get()) != NULL)
		pElem_DgnSucCond.release();
	unique_ptr<TiXmlElement> pElem_dwTotalTimer(new TiXmlElement("UINT32"));
	if(pElem_dwTotalTimer == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwTotalTimer->SetAttribute("name", "dwTotalTimer");
	pElem_dwTotalTimer->SetAttribute("value", NumberToString(s.dwTotalTimer).c_str());
	pElem_dwTotalTimer->SetAttribute("comment", ToUTF8Ptr("总计时间"));
	if(rElement.LinkEndChild(pElem_dwTotalTimer.get()) != NULL)
		pElem_dwTotalTimer.release();
	unique_ptr<TiXmlElement> pElem_dwBeginTimer(new TiXmlElement("UINT32"));
	if(pElem_dwBeginTimer == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwBeginTimer->SetAttribute("name", "dwBeginTimer");
	pElem_dwBeginTimer->SetAttribute("value", NumberToString(s.dwBeginTimer).c_str());
	pElem_dwBeginTimer->SetAttribute("comment", ToUTF8Ptr("起始时间"));
	if(rElement.LinkEndChild(pElem_dwBeginTimer.get()) != NULL)
		pElem_dwBeginTimer.release();
	unique_ptr<TiXmlElement> pElem_wMonsterGroup(new TiXmlElement("UINT16"));
	if(pElem_wMonsterGroup == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wMonsterGroup->SetAttribute("name", "wMonsterGroup");
	pElem_wMonsterGroup->SetAttribute("value", NumberToString(s.wMonsterGroup).c_str());
	pElem_wMonsterGroup->SetAttribute("comment", ToUTF8Ptr("怪物组ID"));
	if(rElement.LinkEndChild(pElem_wMonsterGroup.get()) != NULL)
		pElem_wMonsterGroup.release();
	unique_ptr<TiXmlElement> pElem_byTotalNum(new TiXmlElement("UINT8"));
	if(pElem_byTotalNum == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byTotalNum->SetAttribute("name", "byTotalNum");
	pElem_byTotalNum->SetAttribute("value", NumberToString(s.byTotalNum).c_str());
	pElem_byTotalNum->SetAttribute("comment", ToUTF8Ptr("怪物总数"));
	if(rElement.LinkEndChild(pElem_byTotalNum.get()) != NULL)
		pElem_byTotalNum.release();
	unique_ptr<TiXmlElement> pElem_byCurNum(new TiXmlElement("UINT8"));
	if(pElem_byCurNum == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byCurNum->SetAttribute("name", "byCurNum");
	pElem_byCurNum->SetAttribute("value", NumberToString(s.byCurNum).c_str());
	pElem_byCurNum->SetAttribute("comment", ToUTF8Ptr("当前数量"));
	if(rElement.LinkEndChild(pElem_byCurNum.get()) != NULL)
		pElem_byCurNum.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecSucMonsterInTimer& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SucMonsterInTimerPtr p(new SucMonsterInTimer);
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

bool VectorToXML(const TVecSucMonsterInTimer& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SucMonsterInTimer"));
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

SucGatherInTimer::SucGatherInTimer() : dwTotalTimer(0), dwBeginTimer(0), wGather(0), byTotalNum(0), byCurNum(0) { }

CInArchive& operator>>(CInArchive& src, SucGatherInTimer& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (DgnSucCond&)s;
	src >> s.dwTotalTimer;
	src >> s.dwBeginTimer;
	src >> s.wGather;
	src >> s.byTotalNum;
	src >> s.byCurNum;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SucGatherInTimer& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const DgnSucCond&)s;
	src << s.dwTotalTimer;
	src << s.dwBeginTimer;
	src << s.wGather;
	src << s.byTotalNum;
	src << s.byCurNum;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecSucGatherInTimer& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SucGatherInTimerPtr p(new SucGatherInTimer);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecSucGatherInTimer& vec)
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

bool FromXML(TiXmlElement& rElement, SucGatherInTimer& s)
{
	if(strcmp(rElement.Value(), "SucGatherInTimer") != 0)
	{
		LOG_CRI << "rElement is not SucGatherInTimer!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for DgnSucCond is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (DgnSucCond&)s))
	{
		LOG_CRI << "FromXML for: DgnSucCond fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwTotalTimer is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwTotalTimer") != 0)
	{
		LOG_CRI << "Attribute: name is not dwTotalTimer!";
		return false;
	}
	const char* pszVal_dwTotalTimer = pElemChild->Attribute("value");
	if(pszVal_dwTotalTimer == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwTotalTimer, s.dwTotalTimer))
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
		LOG_CRI << "pElemChild for wGather is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wGather") != 0)
	{
		LOG_CRI << "Attribute: name is not wGather!";
		return false;
	}
	const char* pszVal_wGather = pElemChild->Attribute("value");
	if(pszVal_wGather == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wGather, s.wGather))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byTotalNum is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byTotalNum") != 0)
	{
		LOG_CRI << "Attribute: name is not byTotalNum!";
		return false;
	}
	const char* pszVal_byTotalNum = pElemChild->Attribute("value");
	if(pszVal_byTotalNum == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byTotalNum, s.byTotalNum))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byCurNum is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byCurNum") != 0)
	{
		LOG_CRI << "Attribute: name is not byCurNum!";
		return false;
	}
	const char* pszVal_byCurNum = pElemChild->Attribute("value");
	if(pszVal_byCurNum == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byCurNum, s.byCurNum))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SucGatherInTimer& s, TiXmlElement& rElement)
{
	rElement.SetValue("SucGatherInTimer");
	rElement.SetAttribute("type", ToUTF8Ptr("定时采集"));
	unique_ptr<TiXmlElement> pElem_DgnSucCond(new TiXmlElement("DgnSucCond"));
	if(pElem_DgnSucCond == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const DgnSucCond&)s, *pElem_DgnSucCond))
	{
		LOG_CRI << "DgnSucCond ToXML fails!";
		return false;
	}
	pElem_DgnSucCond->SetAttribute("type", ToUTF8Ptr("副本条件"));
	pElem_DgnSucCond->SetAttribute("comment", ToUTF8Ptr("父类DgnSucCond部分"));
	if(rElement.LinkEndChild(pElem_DgnSucCond.get()) != NULL)
		pElem_DgnSucCond.release();
	unique_ptr<TiXmlElement> pElem_dwTotalTimer(new TiXmlElement("UINT32"));
	if(pElem_dwTotalTimer == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwTotalTimer->SetAttribute("name", "dwTotalTimer");
	pElem_dwTotalTimer->SetAttribute("value", NumberToString(s.dwTotalTimer).c_str());
	pElem_dwTotalTimer->SetAttribute("comment", ToUTF8Ptr("总计时间"));
	if(rElement.LinkEndChild(pElem_dwTotalTimer.get()) != NULL)
		pElem_dwTotalTimer.release();
	unique_ptr<TiXmlElement> pElem_dwBeginTimer(new TiXmlElement("UINT32"));
	if(pElem_dwBeginTimer == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwBeginTimer->SetAttribute("name", "dwBeginTimer");
	pElem_dwBeginTimer->SetAttribute("value", NumberToString(s.dwBeginTimer).c_str());
	pElem_dwBeginTimer->SetAttribute("comment", ToUTF8Ptr("起始时间"));
	if(rElement.LinkEndChild(pElem_dwBeginTimer.get()) != NULL)
		pElem_dwBeginTimer.release();
	unique_ptr<TiXmlElement> pElem_wGather(new TiXmlElement("UINT16"));
	if(pElem_wGather == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wGather->SetAttribute("name", "wGather");
	pElem_wGather->SetAttribute("value", NumberToString(s.wGather).c_str());
	pElem_wGather->SetAttribute("comment", ToUTF8Ptr("采集ID"));
	if(rElement.LinkEndChild(pElem_wGather.get()) != NULL)
		pElem_wGather.release();
	unique_ptr<TiXmlElement> pElem_byTotalNum(new TiXmlElement("UINT8"));
	if(pElem_byTotalNum == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byTotalNum->SetAttribute("name", "byTotalNum");
	pElem_byTotalNum->SetAttribute("value", NumberToString(s.byTotalNum).c_str());
	pElem_byTotalNum->SetAttribute("comment", ToUTF8Ptr("采集总数"));
	if(rElement.LinkEndChild(pElem_byTotalNum.get()) != NULL)
		pElem_byTotalNum.release();
	unique_ptr<TiXmlElement> pElem_byCurNum(new TiXmlElement("UINT8"));
	if(pElem_byCurNum == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byCurNum->SetAttribute("name", "byCurNum");
	pElem_byCurNum->SetAttribute("value", NumberToString(s.byCurNum).c_str());
	pElem_byCurNum->SetAttribute("comment", ToUTF8Ptr("当前数量"));
	if(rElement.LinkEndChild(pElem_byCurNum.get()) != NULL)
		pElem_byCurNum.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecSucGatherInTimer& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SucGatherInTimerPtr p(new SucGatherInTimer);
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

bool VectorToXML(const TVecSucGatherInTimer& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SucGatherInTimer"));
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

SucFightWithMonsterMinTimes::SucFightWithMonsterMinTimes() : wGroup(0), byTotalTimes(0), byCurTimes(0) { }

CInArchive& operator>>(CInArchive& src, SucFightWithMonsterMinTimes& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (DgnSucCond&)s;
	src >> s.wGroup;
	src >> s.byTotalTimes;
	src >> s.byCurTimes;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SucFightWithMonsterMinTimes& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const DgnSucCond&)s;
	src << s.wGroup;
	src << s.byTotalTimes;
	src << s.byCurTimes;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecSucFightWithMonsterMinTimes& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SucFightWithMonsterMinTimesPtr p(new SucFightWithMonsterMinTimes);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecSucFightWithMonsterMinTimes& vec)
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

bool FromXML(TiXmlElement& rElement, SucFightWithMonsterMinTimes& s)
{
	if(strcmp(rElement.Value(), "SucFightWithMonsterMinTimes") != 0)
	{
		LOG_CRI << "rElement is not SucFightWithMonsterMinTimes!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for DgnSucCond is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (DgnSucCond&)s))
	{
		LOG_CRI << "FromXML for: DgnSucCond fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wGroup is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wGroup") != 0)
	{
		LOG_CRI << "Attribute: name is not wGroup!";
		return false;
	}
	const char* pszVal_wGroup = pElemChild->Attribute("value");
	if(pszVal_wGroup == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wGroup, s.wGroup))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byTotalTimes is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byTotalTimes") != 0)
	{
		LOG_CRI << "Attribute: name is not byTotalTimes!";
		return false;
	}
	const char* pszVal_byTotalTimes = pElemChild->Attribute("value");
	if(pszVal_byTotalTimes == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byTotalTimes, s.byTotalTimes))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byCurTimes is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byCurTimes") != 0)
	{
		LOG_CRI << "Attribute: name is not byCurTimes!";
		return false;
	}
	const char* pszVal_byCurTimes = pElemChild->Attribute("value");
	if(pszVal_byCurTimes == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byCurTimes, s.byCurTimes))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SucFightWithMonsterMinTimes& s, TiXmlElement& rElement)
{
	rElement.SetValue("SucFightWithMonsterMinTimes");
	rElement.SetAttribute("type", ToUTF8Ptr("尽量不和怪物发生战斗"));
	unique_ptr<TiXmlElement> pElem_DgnSucCond(new TiXmlElement("DgnSucCond"));
	if(pElem_DgnSucCond == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const DgnSucCond&)s, *pElem_DgnSucCond))
	{
		LOG_CRI << "DgnSucCond ToXML fails!";
		return false;
	}
	pElem_DgnSucCond->SetAttribute("type", ToUTF8Ptr("副本条件"));
	pElem_DgnSucCond->SetAttribute("comment", ToUTF8Ptr("父类DgnSucCond部分"));
	if(rElement.LinkEndChild(pElem_DgnSucCond.get()) != NULL)
		pElem_DgnSucCond.release();
	unique_ptr<TiXmlElement> pElem_wGroup(new TiXmlElement("UINT16"));
	if(pElem_wGroup == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wGroup->SetAttribute("name", "wGroup");
	pElem_wGroup->SetAttribute("value", NumberToString(s.wGroup).c_str());
	pElem_wGroup->SetAttribute("comment", ToUTF8Ptr("怪物"));
	if(rElement.LinkEndChild(pElem_wGroup.get()) != NULL)
		pElem_wGroup.release();
	unique_ptr<TiXmlElement> pElem_byTotalTimes(new TiXmlElement("UINT8"));
	if(pElem_byTotalTimes == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byTotalTimes->SetAttribute("name", "byTotalTimes");
	pElem_byTotalTimes->SetAttribute("value", NumberToString(s.byTotalTimes).c_str());
	pElem_byTotalTimes->SetAttribute("comment", ToUTF8Ptr("总战斗次数"));
	if(rElement.LinkEndChild(pElem_byTotalTimes.get()) != NULL)
		pElem_byTotalTimes.release();
	unique_ptr<TiXmlElement> pElem_byCurTimes(new TiXmlElement("UINT8"));
	if(pElem_byCurTimes == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byCurTimes->SetAttribute("name", "byCurTimes");
	pElem_byCurTimes->SetAttribute("value", NumberToString(s.byCurTimes).c_str());
	pElem_byCurTimes->SetAttribute("comment", ToUTF8Ptr("当前战斗次数"));
	if(rElement.LinkEndChild(pElem_byCurTimes.get()) != NULL)
		pElem_byCurTimes.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecSucFightWithMonsterMinTimes& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SucFightWithMonsterMinTimesPtr p(new SucFightWithMonsterMinTimes);
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

bool VectorToXML(const TVecSucFightWithMonsterMinTimes& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SucFightWithMonsterMinTimes"));
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

SucArriveArea::SucArriveArea() : wAreaID(0) { }

CInArchive& operator>>(CInArchive& src, SucArriveArea& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> (DgnSucCond&)s;
	src >> s.wAreaID;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SucArriveArea& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << (const DgnSucCond&)s;
	src << s.wAreaID;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

CInArchive& operator>>(CInArchive& src, TVecSucArriveArea& vec)
{
	UINT16 wSize = src.ReadContainerSize();
	vec.resize(wSize);
	for(UINT16 i = 0; i < wSize; ++i)
	{
		SucArriveAreaPtr p(new SucArriveArea);
		src >> *p;
		vec[i] = p;
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TVecSucArriveArea& vec)
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

bool FromXML(TiXmlElement& rElement, SucArriveArea& s)
{
	if(strcmp(rElement.Value(), "SucArriveArea") != 0)
	{
		LOG_CRI << "rElement is not SucArriveArea!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for DgnSucCond is empty!";
		return false;
	}
	if(!FromXML(*pElemChild, (DgnSucCond&)s))
	{
		LOG_CRI << "FromXML for: DgnSucCond fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wAreaID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wAreaID") != 0)
	{
		LOG_CRI << "Attribute: name is not wAreaID!";
		return false;
	}
	const char* pszVal_wAreaID = pElemChild->Attribute("value");
	if(pszVal_wAreaID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wAreaID, s.wAreaID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SucArriveArea& s, TiXmlElement& rElement)
{
	rElement.SetValue("SucArriveArea");
	rElement.SetAttribute("type", ToUTF8Ptr("到达某个区域"));
	unique_ptr<TiXmlElement> pElem_DgnSucCond(new TiXmlElement("DgnSucCond"));
	if(pElem_DgnSucCond == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	if(!ToXML((const DgnSucCond&)s, *pElem_DgnSucCond))
	{
		LOG_CRI << "DgnSucCond ToXML fails!";
		return false;
	}
	pElem_DgnSucCond->SetAttribute("type", ToUTF8Ptr("副本条件"));
	pElem_DgnSucCond->SetAttribute("comment", ToUTF8Ptr("父类DgnSucCond部分"));
	if(rElement.LinkEndChild(pElem_DgnSucCond.get()) != NULL)
		pElem_DgnSucCond.release();
	unique_ptr<TiXmlElement> pElem_wAreaID(new TiXmlElement("UINT16"));
	if(pElem_wAreaID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wAreaID->SetAttribute("name", "wAreaID");
	pElem_wAreaID->SetAttribute("value", NumberToString(s.wAreaID).c_str());
	pElem_wAreaID->SetAttribute("comment", ToUTF8Ptr("区域ID"));
	if(rElement.LinkEndChild(pElem_wAreaID.get()) != NULL)
		pElem_wAreaID.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecSucArriveArea& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SucArriveAreaPtr p(new SucArriveArea);
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

bool VectorToXML(const TVecSucArriveArea& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SucArriveArea"));
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

MulCond::MulCond() { }

MulCond::MulCond(MulCond&& src) : vecCond(move(src.vecCond)) { }

MulCond& MulCond::operator=(MulCond&& rhs)
{
	if(this != &rhs)
	{
		this->~MulCond();
		new (this) MulCond(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, MulCond& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.vecCond;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const MulCond& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.vecCond;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, MulCond& s)
{
	if(strcmp(rElement.Value(), "MulCond") != 0)
	{
		LOG_CRI << "rElement is not MulCond!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecCond is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecSucCond") != 0)
	{
		LOG_CRI << "pElemChild is not TVecSucCond!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecCond") != 0)
	{
		LOG_CRI << "Attribute: name is not vecCond!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecCond))
	{
		LOG_CRI << "VectorFromXML for vecCond fails!";
		return false;
	}
	return true;
}

bool ToXML(const MulCond& s, TiXmlElement& rElement)
{
	rElement.SetValue("MulCond");
	rElement.SetAttribute("type", ToUTF8Ptr("多重条件信息"));
	unique_ptr<TiXmlElement> pElem_vecCond(new TiXmlElement("TVecSucCond"));
	if(pElem_vecCond == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecCond->SetAttribute("name", "vecCond");
	if(!VectorToXML(s.vecCond, *pElem_vecCond))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecCond->SetAttribute("comment", ToUTF8Ptr("多重条件"));
	if(rElement.LinkEndChild(pElem_vecCond.get()) != NULL)
		pElem_vecCond.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecMulCond& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		MulCond s;
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

bool VectorToXML(const TVecMulCond& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("MulCond"));
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

DgnStar::DgnStar() : wDgnId(0), byStar(0), dwFinishTimesToday(0), dwBuyTimesToday(0), dwBuyTimes(0), 
			dwCompleteTimes(0) { }

DgnStar::DgnStar(UINT16 wDgnId_, UINT8 byStar_, UINT32 dwFinishTimesToday_, UINT32 dwBuyTimesToday_, UINT32 dwBuyTimes_, 
			UINT32 dwCompleteTimes_)
			: wDgnId(wDgnId_), byStar(byStar_), dwFinishTimesToday(dwFinishTimesToday_), dwBuyTimesToday(dwBuyTimesToday_), dwBuyTimes(dwBuyTimes_), 
			dwCompleteTimes(dwCompleteTimes_) { }

CInArchive& operator>>(CInArchive& src, DgnStar& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.wDgnId;
	src >> s.byStar;
	src >> s.dwFinishTimesToday;
	src >> s.dwBuyTimesToday;
	src >> s.dwBuyTimes;
	src >> s.dwCompleteTimes;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const DgnStar& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.wDgnId;
	src << s.byStar;
	src << s.dwFinishTimesToday;
	src << s.dwBuyTimesToday;
	src << s.dwBuyTimes;
	src << s.dwCompleteTimes;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, DgnStar& s)
{
	if(strcmp(rElement.Value(), "DgnStar") != 0)
	{
		LOG_CRI << "rElement is not DgnStar!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wDgnId is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wDgnId") != 0)
	{
		LOG_CRI << "Attribute: name is not wDgnId!";
		return false;
	}
	const char* pszVal_wDgnId = pElemChild->Attribute("value");
	if(pszVal_wDgnId == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wDgnId, s.wDgnId))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byStar is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byStar") != 0)
	{
		LOG_CRI << "Attribute: name is not byStar!";
		return false;
	}
	const char* pszVal_byStar = pElemChild->Attribute("value");
	if(pszVal_byStar == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byStar, s.byStar))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwFinishTimesToday is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwFinishTimesToday") != 0)
	{
		LOG_CRI << "Attribute: name is not dwFinishTimesToday!";
		return false;
	}
	const char* pszVal_dwFinishTimesToday = pElemChild->Attribute("value");
	if(pszVal_dwFinishTimesToday == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwFinishTimesToday, s.dwFinishTimesToday))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwBuyTimesToday is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwBuyTimesToday") != 0)
	{
		LOG_CRI << "Attribute: name is not dwBuyTimesToday!";
		return false;
	}
	const char* pszVal_dwBuyTimesToday = pElemChild->Attribute("value");
	if(pszVal_dwBuyTimesToday == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwBuyTimesToday, s.dwBuyTimesToday))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwBuyTimes is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwBuyTimes") != 0)
	{
		LOG_CRI << "Attribute: name is not dwBuyTimes!";
		return false;
	}
	const char* pszVal_dwBuyTimes = pElemChild->Attribute("value");
	if(pszVal_dwBuyTimes == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwBuyTimes, s.dwBuyTimes))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwCompleteTimes is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwCompleteTimes") != 0)
	{
		LOG_CRI << "Attribute: name is not dwCompleteTimes!";
		return false;
	}
	const char* pszVal_dwCompleteTimes = pElemChild->Attribute("value");
	if(pszVal_dwCompleteTimes == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwCompleteTimes, s.dwCompleteTimes))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const DgnStar& s, TiXmlElement& rElement)
{
	rElement.SetValue("DgnStar");
	rElement.SetAttribute("type", ToUTF8Ptr("副本星级信息"));
	unique_ptr<TiXmlElement> pElem_wDgnId(new TiXmlElement("UINT16"));
	if(pElem_wDgnId == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wDgnId->SetAttribute("name", "wDgnId");
	pElem_wDgnId->SetAttribute("value", NumberToString(s.wDgnId).c_str());
	pElem_wDgnId->SetAttribute("comment", ToUTF8Ptr("副本ID"));
	if(rElement.LinkEndChild(pElem_wDgnId.get()) != NULL)
		pElem_wDgnId.release();
	unique_ptr<TiXmlElement> pElem_byStar(new TiXmlElement("UINT8"));
	if(pElem_byStar == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byStar->SetAttribute("name", "byStar");
	pElem_byStar->SetAttribute("value", NumberToString(s.byStar).c_str());
	pElem_byStar->SetAttribute("comment", ToUTF8Ptr("星级"));
	if(rElement.LinkEndChild(pElem_byStar.get()) != NULL)
		pElem_byStar.release();
	unique_ptr<TiXmlElement> pElem_dwFinishTimesToday(new TiXmlElement("UINT32"));
	if(pElem_dwFinishTimesToday == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwFinishTimesToday->SetAttribute("name", "dwFinishTimesToday");
	pElem_dwFinishTimesToday->SetAttribute("value", NumberToString(s.dwFinishTimesToday).c_str());
	pElem_dwFinishTimesToday->SetAttribute("comment", ToUTF8Ptr("今日完成次数"));
	if(rElement.LinkEndChild(pElem_dwFinishTimesToday.get()) != NULL)
		pElem_dwFinishTimesToday.release();
	unique_ptr<TiXmlElement> pElem_dwBuyTimesToday(new TiXmlElement("UINT32"));
	if(pElem_dwBuyTimesToday == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwBuyTimesToday->SetAttribute("name", "dwBuyTimesToday");
	pElem_dwBuyTimesToday->SetAttribute("value", NumberToString(s.dwBuyTimesToday).c_str());
	pElem_dwBuyTimesToday->SetAttribute("comment", ToUTF8Ptr("今日购买次数"));
	if(rElement.LinkEndChild(pElem_dwBuyTimesToday.get()) != NULL)
		pElem_dwBuyTimesToday.release();
	unique_ptr<TiXmlElement> pElem_dwBuyTimes(new TiXmlElement("UINT32"));
	if(pElem_dwBuyTimes == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwBuyTimes->SetAttribute("name", "dwBuyTimes");
	pElem_dwBuyTimes->SetAttribute("value", NumberToString(s.dwBuyTimes).c_str());
	pElem_dwBuyTimes->SetAttribute("comment", ToUTF8Ptr("购买的总次数"));
	if(rElement.LinkEndChild(pElem_dwBuyTimes.get()) != NULL)
		pElem_dwBuyTimes.release();
	unique_ptr<TiXmlElement> pElem_dwCompleteTimes(new TiXmlElement("UINT32"));
	if(pElem_dwCompleteTimes == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwCompleteTimes->SetAttribute("name", "dwCompleteTimes");
	pElem_dwCompleteTimes->SetAttribute("value", NumberToString(s.dwCompleteTimes).c_str());
	pElem_dwCompleteTimes->SetAttribute("comment", ToUTF8Ptr("总通关次数"));
	if(rElement.LinkEndChild(pElem_dwCompleteTimes.get()) != NULL)
		pElem_dwCompleteTimes.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecDgnStar& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		DgnStar s;
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

bool VectorToXML(const TVecDgnStar& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("DgnStar"));
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

DgnLiXian::DgnLiXian() : dwFinishTimesToday(0), dwBuyTimesToday(0), dwBuyTimes(0) { }

DgnLiXian::DgnLiXian(UINT32 dwFinishTimesToday_, UINT32 dwBuyTimesToday_, UINT32 dwBuyTimes_) : dwFinishTimesToday(dwFinishTimesToday_), dwBuyTimesToday(dwBuyTimesToday_), dwBuyTimes(dwBuyTimes_) { }

CInArchive& operator>>(CInArchive& src, DgnLiXian& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.dwFinishTimesToday;
	src >> s.dwBuyTimesToday;
	src >> s.dwBuyTimes;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const DgnLiXian& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.dwFinishTimesToday;
	src << s.dwBuyTimesToday;
	src << s.dwBuyTimes;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, DgnLiXian& s)
{
	if(strcmp(rElement.Value(), "DgnLiXian") != 0)
	{
		LOG_CRI << "rElement is not DgnLiXian!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwFinishTimesToday is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwFinishTimesToday") != 0)
	{
		LOG_CRI << "Attribute: name is not dwFinishTimesToday!";
		return false;
	}
	const char* pszVal_dwFinishTimesToday = pElemChild->Attribute("value");
	if(pszVal_dwFinishTimesToday == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwFinishTimesToday, s.dwFinishTimesToday))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwBuyTimesToday is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwBuyTimesToday") != 0)
	{
		LOG_CRI << "Attribute: name is not dwBuyTimesToday!";
		return false;
	}
	const char* pszVal_dwBuyTimesToday = pElemChild->Attribute("value");
	if(pszVal_dwBuyTimesToday == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwBuyTimesToday, s.dwBuyTimesToday))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwBuyTimes is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwBuyTimes") != 0)
	{
		LOG_CRI << "Attribute: name is not dwBuyTimes!";
		return false;
	}
	const char* pszVal_dwBuyTimes = pElemChild->Attribute("value");
	if(pszVal_dwBuyTimes == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwBuyTimes, s.dwBuyTimes))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const DgnLiXian& s, TiXmlElement& rElement)
{
	rElement.SetValue("DgnLiXian");
	rElement.SetAttribute("type", ToUTF8Ptr("历险副本信息"));
	unique_ptr<TiXmlElement> pElem_dwFinishTimesToday(new TiXmlElement("UINT32"));
	if(pElem_dwFinishTimesToday == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwFinishTimesToday->SetAttribute("name", "dwFinishTimesToday");
	pElem_dwFinishTimesToday->SetAttribute("value", NumberToString(s.dwFinishTimesToday).c_str());
	pElem_dwFinishTimesToday->SetAttribute("comment", ToUTF8Ptr("今日完成次数"));
	if(rElement.LinkEndChild(pElem_dwFinishTimesToday.get()) != NULL)
		pElem_dwFinishTimesToday.release();
	unique_ptr<TiXmlElement> pElem_dwBuyTimesToday(new TiXmlElement("UINT32"));
	if(pElem_dwBuyTimesToday == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwBuyTimesToday->SetAttribute("name", "dwBuyTimesToday");
	pElem_dwBuyTimesToday->SetAttribute("value", NumberToString(s.dwBuyTimesToday).c_str());
	pElem_dwBuyTimesToday->SetAttribute("comment", ToUTF8Ptr("今日购买次数"));
	if(rElement.LinkEndChild(pElem_dwBuyTimesToday.get()) != NULL)
		pElem_dwBuyTimesToday.release();
	unique_ptr<TiXmlElement> pElem_dwBuyTimes(new TiXmlElement("UINT32"));
	if(pElem_dwBuyTimes == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwBuyTimes->SetAttribute("name", "dwBuyTimes");
	pElem_dwBuyTimes->SetAttribute("value", NumberToString(s.dwBuyTimes).c_str());
	pElem_dwBuyTimes->SetAttribute("comment", ToUTF8Ptr("购买的总次数"));
	if(rElement.LinkEndChild(pElem_dwBuyTimes.get()) != NULL)
		pElem_dwBuyTimes.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecDgnLiXian& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		DgnLiXian s;
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

bool VectorToXML(const TVecDgnLiXian& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("DgnLiXian"));
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

SSweepInfo::SSweepInfo() : qwRoleID(0), wCurDgnID(0), wCurCount(0), dwReserverTime(0), dwSaveTime(0), 
			wOptions(0), wCount(0) { }

SSweepInfo::SSweepInfo(UINT64 qwRoleID_, UINT16 wCurDgnID_, UINT16 wCurCount_, UINT32 dwReserverTime_, UINT32 dwSaveTime_, 
			UINT16 wOptions_, UINT16 wCount_, const std::string& strVecDgn_)
			: qwRoleID(qwRoleID_), wCurDgnID(wCurDgnID_), wCurCount(wCurCount_), dwReserverTime(dwReserverTime_), dwSaveTime(dwSaveTime_), 
			wOptions(wOptions_), wCount(wCount_), strVecDgn(strVecDgn_) { }

SSweepInfo::SSweepInfo(SSweepInfo&& src) : qwRoleID(src.qwRoleID), wCurDgnID(src.wCurDgnID), wCurCount(src.wCurCount), dwReserverTime(src.dwReserverTime), dwSaveTime(src.dwSaveTime), 
			wOptions(src.wOptions), wCount(src.wCount), strVecDgn(move(src.strVecDgn)) { }

SSweepInfo& SSweepInfo::operator=(SSweepInfo&& rhs)
{
	if(this != &rhs)
	{
		this->~SSweepInfo();
		new (this) SSweepInfo(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SSweepInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwRoleID;
	src >> s.wCurDgnID;
	src >> s.wCurCount;
	src >> s.dwReserverTime;
	src >> s.dwSaveTime;
	src >> s.wOptions;
	src >> s.wCount;
	src >> s.strVecDgn;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SSweepInfo& s)
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
	src << s.wCurDgnID;
	src << s.wCurCount;
	src << s.dwReserverTime;
	src << s.dwSaveTime;
	src << s.wOptions;
	src << s.wCount;
	src << s.strVecDgn;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SSweepInfo& s)
{
	if(strcmp(rElement.Value(), "SSweepInfo") != 0)
	{
		LOG_CRI << "rElement is not SSweepInfo!";
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
		LOG_CRI << "pElemChild for wCurDgnID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wCurDgnID") != 0)
	{
		LOG_CRI << "Attribute: name is not wCurDgnID!";
		return false;
	}
	const char* pszVal_wCurDgnID = pElemChild->Attribute("value");
	if(pszVal_wCurDgnID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wCurDgnID, s.wCurDgnID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wCurCount is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wCurCount") != 0)
	{
		LOG_CRI << "Attribute: name is not wCurCount!";
		return false;
	}
	const char* pszVal_wCurCount = pElemChild->Attribute("value");
	if(pszVal_wCurCount == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wCurCount, s.wCurCount))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwReserverTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwReserverTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwReserverTime!";
		return false;
	}
	const char* pszVal_dwReserverTime = pElemChild->Attribute("value");
	if(pszVal_dwReserverTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwReserverTime, s.dwReserverTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwSaveTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwSaveTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwSaveTime!";
		return false;
	}
	const char* pszVal_dwSaveTime = pElemChild->Attribute("value");
	if(pszVal_dwSaveTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwSaveTime, s.dwSaveTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wOptions is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wOptions") != 0)
	{
		LOG_CRI << "Attribute: name is not wOptions!";
		return false;
	}
	const char* pszVal_wOptions = pElemChild->Attribute("value");
	if(pszVal_wOptions == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wOptions, s.wOptions))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wCount is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wCount") != 0)
	{
		LOG_CRI << "Attribute: name is not wCount!";
		return false;
	}
	const char* pszVal_wCount = pElemChild->Attribute("value");
	if(pszVal_wCount == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wCount, s.wCount))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strVecDgn is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strVecDgn") != 0)
	{
		LOG_CRI << "Attribute: name is not strVecDgn!";
		return false;
	}
	const char* pszVal_strVecDgn = pElemChild->Attribute("value");
	if(pszVal_strVecDgn == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strVecDgn = pszVal_strVecDgn;
	return true;
}

bool ToXML(const SSweepInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SSweepInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("扫荡信息"));
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
	unique_ptr<TiXmlElement> pElem_wCurDgnID(new TiXmlElement("UINT16"));
	if(pElem_wCurDgnID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wCurDgnID->SetAttribute("name", "wCurDgnID");
	pElem_wCurDgnID->SetAttribute("value", NumberToString(s.wCurDgnID).c_str());
	pElem_wCurDgnID->SetAttribute("comment", ToUTF8Ptr("当前扫荡副本"));
	if(rElement.LinkEndChild(pElem_wCurDgnID.get()) != NULL)
		pElem_wCurDgnID.release();
	unique_ptr<TiXmlElement> pElem_wCurCount(new TiXmlElement("UINT16"));
	if(pElem_wCurCount == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wCurCount->SetAttribute("name", "wCurCount");
	pElem_wCurCount->SetAttribute("value", NumberToString(s.wCurCount).c_str());
	pElem_wCurCount->SetAttribute("comment", ToUTF8Ptr("当前剩余扫荡次数"));
	if(rElement.LinkEndChild(pElem_wCurCount.get()) != NULL)
		pElem_wCurCount.release();
	unique_ptr<TiXmlElement> pElem_dwReserverTime(new TiXmlElement("UINT32"));
	if(pElem_dwReserverTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwReserverTime->SetAttribute("name", "dwReserverTime");
	pElem_dwReserverTime->SetAttribute("value", NumberToString(s.dwReserverTime).c_str());
	pElem_dwReserverTime->SetAttribute("comment", ToUTF8Ptr("下次扫荡剩余时间"));
	if(rElement.LinkEndChild(pElem_dwReserverTime.get()) != NULL)
		pElem_dwReserverTime.release();
	unique_ptr<TiXmlElement> pElem_dwSaveTime(new TiXmlElement("UINT32"));
	if(pElem_dwSaveTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwSaveTime->SetAttribute("name", "dwSaveTime");
	pElem_dwSaveTime->SetAttribute("value", NumberToString(s.dwSaveTime).c_str());
	pElem_dwSaveTime->SetAttribute("comment", ToUTF8Ptr("保存时间"));
	if(rElement.LinkEndChild(pElem_dwSaveTime.get()) != NULL)
		pElem_dwSaveTime.release();
	unique_ptr<TiXmlElement> pElem_wOptions(new TiXmlElement("UINT16"));
	if(pElem_wOptions == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wOptions->SetAttribute("name", "wOptions");
	pElem_wOptions->SetAttribute("value", NumberToString(s.wOptions).c_str());
	pElem_wOptions->SetAttribute("comment", ToUTF8Ptr("扫荡类型"));
	if(rElement.LinkEndChild(pElem_wOptions.get()) != NULL)
		pElem_wOptions.release();
	unique_ptr<TiXmlElement> pElem_wCount(new TiXmlElement("UINT16"));
	if(pElem_wCount == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wCount->SetAttribute("name", "wCount");
	pElem_wCount->SetAttribute("value", NumberToString(s.wCount).c_str());
	pElem_wCount->SetAttribute("comment", ToUTF8Ptr("扫荡需求次数"));
	if(rElement.LinkEndChild(pElem_wCount.get()) != NULL)
		pElem_wCount.release();
	unique_ptr<TiXmlElement> pElem_strVecDgn(new TiXmlElement("string"));
	if(pElem_strVecDgn == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strVecDgn->SetAttribute("name", "strVecDgn");
	pElem_strVecDgn->SetAttribute("value", s.strVecDgn.c_str());
	pElem_strVecDgn->SetAttribute("comment", ToUTF8Ptr("未开始扫荡副本"));
	if(rElement.LinkEndChild(pElem_strVecDgn.get()) != NULL)
		pElem_strVecDgn.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecSweepInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SSweepInfo s;
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

bool VectorToXML(const TVecSweepInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SSweepInfo"));
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

SSweepItem::SSweepItem() : wTurn(0) { }

SSweepItem::SSweepItem(UINT16 wTurn_, const NItemProt::TVecItemGenInfo& vecItemGenInfo_, const NItemProt::TVecResource& vecResource_) : wTurn(wTurn_), vecItemGenInfo(vecItemGenInfo_), vecResource(vecResource_) { }

SSweepItem::SSweepItem(SSweepItem&& src) : wTurn(src.wTurn), vecItemGenInfo(move(src.vecItemGenInfo)), vecResource(move(src.vecResource)) { }

SSweepItem& SSweepItem::operator=(SSweepItem&& rhs)
{
	if(this != &rhs)
	{
		this->~SSweepItem();
		new (this) SSweepItem(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SSweepItem& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.wTurn;
	src >> s.vecItemGenInfo;
	src >> s.vecResource;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SSweepItem& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.wTurn;
	src << s.vecItemGenInfo;
	src << s.vecResource;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SSweepItem& s)
{
	if(strcmp(rElement.Value(), "SSweepItem") != 0)
	{
		LOG_CRI << "rElement is not SSweepItem!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wTurn is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wTurn") != 0)
	{
		LOG_CRI << "Attribute: name is not wTurn!";
		return false;
	}
	const char* pszVal_wTurn = pElemChild->Attribute("value");
	if(pszVal_wTurn == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wTurn, s.wTurn))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecItemGenInfo is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "ItemProt::TVecItemGenInfo") != 0)
	{
		LOG_CRI << "pElemChild is not ItemProt::TVecItemGenInfo!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecItemGenInfo") != 0)
	{
		LOG_CRI << "Attribute: name is not vecItemGenInfo!";
		return false;
	}
	if(!NItemProt::VectorFromXML(*pElemChild, s.vecItemGenInfo))
	{
		LOG_CRI << "VectorFromXML for vecItemGenInfo fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecResource is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "ItemProt::TVecResource") != 0)
	{
		LOG_CRI << "pElemChild is not ItemProt::TVecResource!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecResource") != 0)
	{
		LOG_CRI << "Attribute: name is not vecResource!";
		return false;
	}
	if(!NItemProt::VectorFromXML(*pElemChild, s.vecResource))
	{
		LOG_CRI << "VectorFromXML for vecResource fails!";
		return false;
	}
	return true;
}

bool ToXML(const SSweepItem& s, TiXmlElement& rElement)
{
	rElement.SetValue("SSweepItem");
	rElement.SetAttribute("type", ToUTF8Ptr("扫荡日志信息"));
	unique_ptr<TiXmlElement> pElem_wTurn(new TiXmlElement("UINT16"));
	if(pElem_wTurn == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wTurn->SetAttribute("name", "wTurn");
	pElem_wTurn->SetAttribute("value", NumberToString(s.wTurn).c_str());
	pElem_wTurn->SetAttribute("comment", ToUTF8Ptr("当前扫荡轮数"));
	if(rElement.LinkEndChild(pElem_wTurn.get()) != NULL)
		pElem_wTurn.release();
	unique_ptr<TiXmlElement> pElem_vecItemGenInfo(new TiXmlElement("ItemProt::TVecItemGenInfo"));
	if(pElem_vecItemGenInfo == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecItemGenInfo->SetAttribute("name", "vecItemGenInfo");
	if(!NItemProt::VectorToXML(s.vecItemGenInfo, *pElem_vecItemGenInfo))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecItemGenInfo->SetAttribute("comment", ToUTF8Ptr("获得物品"));
	if(rElement.LinkEndChild(pElem_vecItemGenInfo.get()) != NULL)
		pElem_vecItemGenInfo.release();
	unique_ptr<TiXmlElement> pElem_vecResource(new TiXmlElement("ItemProt::TVecResource"));
	if(pElem_vecResource == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecResource->SetAttribute("name", "vecResource");
	if(!NItemProt::VectorToXML(s.vecResource, *pElem_vecResource))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecResource->SetAttribute("comment", ToUTF8Ptr("获得资源"));
	if(rElement.LinkEndChild(pElem_vecResource.get()) != NULL)
		pElem_vecResource.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecSweepItem& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SSweepItem s;
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

bool VectorToXML(const TVecSweepItem& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SSweepItem"));
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

SGetSweepInfo::SGetSweepInfo() : wDgnId(0), dwReserverTimer(0), wCount(0), wMaxCount(0) { }

SGetSweepInfo::SGetSweepInfo(UINT16 wDgnId_, UINT32 dwReserverTimer_, UINT16 wCount_, UINT16 wMaxCount_, const TVecSweepItem& vecSweepItem_)
			: wDgnId(wDgnId_), dwReserverTimer(dwReserverTimer_), wCount(wCount_), wMaxCount(wMaxCount_), vecSweepItem(vecSweepItem_) { }

SGetSweepInfo::SGetSweepInfo(SGetSweepInfo&& src) : wDgnId(src.wDgnId), dwReserverTimer(src.dwReserverTimer), wCount(src.wCount), wMaxCount(src.wMaxCount), vecSweepItem(move(src.vecSweepItem)) { }

SGetSweepInfo& SGetSweepInfo::operator=(SGetSweepInfo&& rhs)
{
	if(this != &rhs)
	{
		this->~SGetSweepInfo();
		new (this) SGetSweepInfo(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SGetSweepInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.wDgnId;
	src >> s.dwReserverTimer;
	src >> s.wCount;
	src >> s.wMaxCount;
	src >> s.vecSweepItem;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SGetSweepInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.wDgnId;
	src << s.dwReserverTimer;
	src << s.wCount;
	src << s.wMaxCount;
	src << s.vecSweepItem;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SGetSweepInfo& s)
{
	if(strcmp(rElement.Value(), "SGetSweepInfo") != 0)
	{
		LOG_CRI << "rElement is not SGetSweepInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wDgnId is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wDgnId") != 0)
	{
		LOG_CRI << "Attribute: name is not wDgnId!";
		return false;
	}
	const char* pszVal_wDgnId = pElemChild->Attribute("value");
	if(pszVal_wDgnId == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wDgnId, s.wDgnId))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwReserverTimer is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwReserverTimer") != 0)
	{
		LOG_CRI << "Attribute: name is not dwReserverTimer!";
		return false;
	}
	const char* pszVal_dwReserverTimer = pElemChild->Attribute("value");
	if(pszVal_dwReserverTimer == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwReserverTimer, s.dwReserverTimer))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wCount is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wCount") != 0)
	{
		LOG_CRI << "Attribute: name is not wCount!";
		return false;
	}
	const char* pszVal_wCount = pElemChild->Attribute("value");
	if(pszVal_wCount == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wCount, s.wCount))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wMaxCount is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wMaxCount") != 0)
	{
		LOG_CRI << "Attribute: name is not wMaxCount!";
		return false;
	}
	const char* pszVal_wMaxCount = pElemChild->Attribute("value");
	if(pszVal_wMaxCount == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wMaxCount, s.wMaxCount))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecSweepItem is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecSweepItem") != 0)
	{
		LOG_CRI << "pElemChild is not TVecSweepItem!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecSweepItem") != 0)
	{
		LOG_CRI << "Attribute: name is not vecSweepItem!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecSweepItem))
	{
		LOG_CRI << "VectorFromXML for vecSweepItem fails!";
		return false;
	}
	return true;
}

bool ToXML(const SGetSweepInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SGetSweepInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("客户段获取的扫荡信息"));
	unique_ptr<TiXmlElement> pElem_wDgnId(new TiXmlElement("UINT16"));
	if(pElem_wDgnId == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wDgnId->SetAttribute("name", "wDgnId");
	pElem_wDgnId->SetAttribute("value", NumberToString(s.wDgnId).c_str());
	pElem_wDgnId->SetAttribute("comment", ToUTF8Ptr("扫荡副本实例"));
	if(rElement.LinkEndChild(pElem_wDgnId.get()) != NULL)
		pElem_wDgnId.release();
	unique_ptr<TiXmlElement> pElem_dwReserverTimer(new TiXmlElement("UINT32"));
	if(pElem_dwReserverTimer == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwReserverTimer->SetAttribute("name", "dwReserverTimer");
	pElem_dwReserverTimer->SetAttribute("value", NumberToString(s.dwReserverTimer).c_str());
	pElem_dwReserverTimer->SetAttribute("comment", ToUTF8Ptr("剩余时间"));
	if(rElement.LinkEndChild(pElem_dwReserverTimer.get()) != NULL)
		pElem_dwReserverTimer.release();
	unique_ptr<TiXmlElement> pElem_wCount(new TiXmlElement("UINT16"));
	if(pElem_wCount == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wCount->SetAttribute("name", "wCount");
	pElem_wCount->SetAttribute("value", NumberToString(s.wCount).c_str());
	pElem_wCount->SetAttribute("comment", ToUTF8Ptr("剩余次数"));
	if(rElement.LinkEndChild(pElem_wCount.get()) != NULL)
		pElem_wCount.release();
	unique_ptr<TiXmlElement> pElem_wMaxCount(new TiXmlElement("UINT16"));
	if(pElem_wMaxCount == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wMaxCount->SetAttribute("name", "wMaxCount");
	pElem_wMaxCount->SetAttribute("value", NumberToString(s.wMaxCount).c_str());
	pElem_wMaxCount->SetAttribute("comment", ToUTF8Ptr("总的扫荡次数"));
	if(rElement.LinkEndChild(pElem_wMaxCount.get()) != NULL)
		pElem_wMaxCount.release();
	unique_ptr<TiXmlElement> pElem_vecSweepItem(new TiXmlElement("TVecSweepItem"));
	if(pElem_vecSweepItem == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecSweepItem->SetAttribute("name", "vecSweepItem");
	if(!VectorToXML(s.vecSweepItem, *pElem_vecSweepItem))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecSweepItem->SetAttribute("comment", ToUTF8Ptr("扫荡日志"));
	if(rElement.LinkEndChild(pElem_vecSweepItem.get()) != NULL)
		pElem_vecSweepItem.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecGetSweepInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SGetSweepInfo s;
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

bool VectorToXML(const TVecGetSweepInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SGetSweepInfo"));
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

TeamAwardRecord::TeamAwardRecord() : wDgnType(0), byAwardTimes(0) { }

TeamAwardRecord::TeamAwardRecord(UINT16 wDgnType_, UINT8 byAwardTimes_) : wDgnType(wDgnType_), byAwardTimes(byAwardTimes_) { }

CInArchive& operator>>(CInArchive& src, TeamAwardRecord& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.wDgnType;
	src >> s.byAwardTimes;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TeamAwardRecord& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.wDgnType;
	src << s.byAwardTimes;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, TeamAwardRecord& s)
{
	if(strcmp(rElement.Value(), "TeamAwardRecord") != 0)
	{
		LOG_CRI << "rElement is not TeamAwardRecord!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wDgnType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wDgnType") != 0)
	{
		LOG_CRI << "Attribute: name is not wDgnType!";
		return false;
	}
	const char* pszVal_wDgnType = pElemChild->Attribute("value");
	if(pszVal_wDgnType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wDgnType, s.wDgnType))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byAwardTimes is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byAwardTimes") != 0)
	{
		LOG_CRI << "Attribute: name is not byAwardTimes!";
		return false;
	}
	const char* pszVal_byAwardTimes = pElemChild->Attribute("value");
	if(pszVal_byAwardTimes == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byAwardTimes, s.byAwardTimes))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const TeamAwardRecord& s, TiXmlElement& rElement)
{
	rElement.SetValue("TeamAwardRecord");
	rElement.SetAttribute("type", ToUTF8Ptr("组队副本领奖记录"));
	unique_ptr<TiXmlElement> pElem_wDgnType(new TiXmlElement("UINT16"));
	if(pElem_wDgnType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wDgnType->SetAttribute("name", "wDgnType");
	pElem_wDgnType->SetAttribute("value", NumberToString(s.wDgnType).c_str());
	pElem_wDgnType->SetAttribute("comment", ToUTF8Ptr("副本模板"));
	if(rElement.LinkEndChild(pElem_wDgnType.get()) != NULL)
		pElem_wDgnType.release();
	unique_ptr<TiXmlElement> pElem_byAwardTimes(new TiXmlElement("UINT8"));
	if(pElem_byAwardTimes == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byAwardTimes->SetAttribute("name", "byAwardTimes");
	pElem_byAwardTimes->SetAttribute("value", NumberToString(s.byAwardTimes).c_str());
	pElem_byAwardTimes->SetAttribute("comment", ToUTF8Ptr("今日领奖次数"));
	if(rElement.LinkEndChild(pElem_byAwardTimes.get()) != NULL)
		pElem_byAwardTimes.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecTeamAwardRecord& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		TeamAwardRecord s;
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

bool VectorToXML(const TVecTeamAwardRecord& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("TeamAwardRecord"));
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

TeamAwardAllRecord::TeamAwardAllRecord() : byAwardTimesToday(0) { }

TeamAwardAllRecord::TeamAwardAllRecord(UINT8 byAwardTimesToday_, const TVecTeamAwardRecord& vecDgn_) : byAwardTimesToday(byAwardTimesToday_), vecDgn(vecDgn_) { }

TeamAwardAllRecord::TeamAwardAllRecord(TeamAwardAllRecord&& src) : byAwardTimesToday(src.byAwardTimesToday), vecDgn(move(src.vecDgn)) { }

TeamAwardAllRecord& TeamAwardAllRecord::operator=(TeamAwardAllRecord&& rhs)
{
	if(this != &rhs)
	{
		this->~TeamAwardAllRecord();
		new (this) TeamAwardAllRecord(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, TeamAwardAllRecord& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.byAwardTimesToday;
	src >> s.vecDgn;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const TeamAwardAllRecord& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.byAwardTimesToday;
	src << s.vecDgn;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, TeamAwardAllRecord& s)
{
	if(strcmp(rElement.Value(), "TeamAwardAllRecord") != 0)
	{
		LOG_CRI << "rElement is not TeamAwardAllRecord!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byAwardTimesToday is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byAwardTimesToday") != 0)
	{
		LOG_CRI << "Attribute: name is not byAwardTimesToday!";
		return false;
	}
	const char* pszVal_byAwardTimesToday = pElemChild->Attribute("value");
	if(pszVal_byAwardTimesToday == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byAwardTimesToday, s.byAwardTimesToday))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for vecDgn is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "TVecTeamAwardRecord") != 0)
	{
		LOG_CRI << "pElemChild is not TVecTeamAwardRecord!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "vecDgn") != 0)
	{
		LOG_CRI << "Attribute: name is not vecDgn!";
		return false;
	}
	if(!VectorFromXML(*pElemChild, s.vecDgn))
	{
		LOG_CRI << "VectorFromXML for vecDgn fails!";
		return false;
	}
	return true;
}

bool ToXML(const TeamAwardAllRecord& s, TiXmlElement& rElement)
{
	rElement.SetValue("TeamAwardAllRecord");
	rElement.SetAttribute("type", ToUTF8Ptr("组队副本总领奖记录"));
	unique_ptr<TiXmlElement> pElem_byAwardTimesToday(new TiXmlElement("UINT8"));
	if(pElem_byAwardTimesToday == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byAwardTimesToday->SetAttribute("name", "byAwardTimesToday");
	pElem_byAwardTimesToday->SetAttribute("value", NumberToString(s.byAwardTimesToday).c_str());
	pElem_byAwardTimesToday->SetAttribute("comment", ToUTF8Ptr("今日领奖次数"));
	if(rElement.LinkEndChild(pElem_byAwardTimesToday.get()) != NULL)
		pElem_byAwardTimesToday.release();
	unique_ptr<TiXmlElement> pElem_vecDgn(new TiXmlElement("TVecTeamAwardRecord"));
	if(pElem_vecDgn == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_vecDgn->SetAttribute("name", "vecDgn");
	if(!VectorToXML(s.vecDgn, *pElem_vecDgn))
	{
		LOG_CRI << "VectorToXML fails!";
		return false;
	}
	pElem_vecDgn->SetAttribute("comment", ToUTF8Ptr("每个副本领奖次数"));
	if(rElement.LinkEndChild(pElem_vecDgn.get()) != NULL)
		pElem_vecDgn.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecTeamAwardAllRecord& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		TeamAwardAllRecord s;
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

bool VectorToXML(const TVecTeamAwardAllRecord& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("TeamAwardAllRecord"));
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

} //namespace NDungeonProt
