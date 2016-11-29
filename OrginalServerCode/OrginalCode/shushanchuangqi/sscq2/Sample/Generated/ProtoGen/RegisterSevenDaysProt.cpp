/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    RegisterSevenDays.cpp
//  Purpose:      注册七天目标协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "RegisterSevenDaysProt.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NRegisterSevenDaysProt
{

#ifdef PROT_USE_XML

const char* EnumValToStr(ERegisterSevenDaysResult e)
{
	switch(e)
	{
	case eSucceed:
		return "eSucceed";
	case eFailed:
		return "eFailed";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, ERegisterSevenDaysResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, ERegisterSevenDaysResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eSucceed", eSucceed));
		mapStr2Val.insert(make_pair("eFailed", eFailed));
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

const char* EnumValToStr(EBuyStatus e)
{
	switch(e)
	{
	case eNoBuy:
		return "eNoBuy";
	case eCanBuy:
		return "eCanBuy";
	case eAlreadyBuy:
		return "eAlreadyBuy";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EBuyStatus& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EBuyStatus> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eNoBuy", eNoBuy));
		mapStr2Val.insert(make_pair("eCanBuy", eCanBuy));
		mapStr2Val.insert(make_pair("eAlreadyBuy", eAlreadyBuy));
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

} //namespace NRegisterSevenDaysProt
