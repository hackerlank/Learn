/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    TitleProt.cpp
//  Purpose:      称号协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "TitleProt.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NTitleProt
{

#ifdef PROT_USE_XML

const char* EnumValToStr(ETitleResult e)
{
	switch(e)
	{
	case eTitleSucceed:
		return "eTitleSucceed";
	case eTitleVIPLevel:
		return "eTitleVIPLevel";
	case eTitleNoHas:
		return "eTitleNoHas";
	case eTitleErrOther:
		return "eTitleErrOther";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, ETitleResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, ETitleResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eTitleSucceed", eTitleSucceed));
		mapStr2Val.insert(make_pair("eTitleVIPLevel", eTitleVIPLevel));
		mapStr2Val.insert(make_pair("eTitleNoHas", eTitleNoHas));
		mapStr2Val.insert(make_pair("eTitleErrOther", eTitleErrOther));
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

} //namespace NTitleProt
