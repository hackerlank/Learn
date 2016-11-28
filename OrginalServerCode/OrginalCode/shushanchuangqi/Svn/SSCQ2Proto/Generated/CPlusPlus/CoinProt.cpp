/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    CoinProt.cpp
//  Purpose:      888礼券协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "CoinProt.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NCoinProt
{

#ifdef PROT_USE_XML

const char* EnumValToStr(EResultInCoinProt e)
{
	switch(e)
	{
	case eCoinError:
		return "eCoinError";
	case eCoinGain:
		return "eCoinGain";
	case eCoinSuccess:
		return "eCoinSuccess";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EResultInCoinProt& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EResultInCoinProt> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eCoinError", eCoinError));
		mapStr2Val.insert(make_pair("eCoinGain", eCoinGain));
		mapStr2Val.insert(make_pair("eCoinSuccess", eCoinSuccess));
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

} //namespace NCoinProt
