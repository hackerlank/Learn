/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    SittingProt.cpp
//  Purpose:      打坐协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "SittingProt.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NSittingProt
{

#ifdef PROT_USE_XML

const char* EnumValToStr(ESittingResult e)
{
	switch(e)
	{
	case eSittingSucceed:
		return "eSittingSucceed";
	case eSittingTogether:
		return "eSittingTogether";
	case eHasSitting:
		return "eHasSitting";
	case eNotInCity:
		return "eNotInCity";
	case eLevelLow:
		return "eLevelLow";
	case eSittingErrOther:
		return "eSittingErrOther";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, ESittingResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, ESittingResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eSittingSucceed", eSittingSucceed));
		mapStr2Val.insert(make_pair("eSittingTogether", eSittingTogether));
		mapStr2Val.insert(make_pair("eHasSitting", eHasSitting));
		mapStr2Val.insert(make_pair("eNotInCity", eNotInCity));
		mapStr2Val.insert(make_pair("eLevelLow", eLevelLow));
		mapStr2Val.insert(make_pair("eSittingErrOther", eSittingErrOther));
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

} //namespace NSittingProt
