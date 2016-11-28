/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    LoginPkgProt.cpp
//  Purpose:      累计登入礼包协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "LoginPkgProt.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NLoginPkgProt
{

#ifdef PROT_USE_XML

const char* EnumValToStr(EResultInLoginProt e)
{
	switch(e)
	{
	case ePkgError:
		return "ePkgError";
	case ePkgGain:
		return "ePkgGain";
	case ePkgFull:
		return "ePkgFull";
	case ePkgSuccess:
		return "ePkgSuccess";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EResultInLoginProt& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EResultInLoginProt> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("ePkgError", ePkgError));
		mapStr2Val.insert(make_pair("ePkgGain", ePkgGain));
		mapStr2Val.insert(make_pair("ePkgFull", ePkgFull));
		mapStr2Val.insert(make_pair("ePkgSuccess", ePkgSuccess));
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

} //namespace NLoginPkgProt
