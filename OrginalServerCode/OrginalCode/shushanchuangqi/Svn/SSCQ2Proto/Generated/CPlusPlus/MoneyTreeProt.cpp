/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    MoneyTree.cpp
//  Purpose:      摇钱树协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "MoneyTreeProt.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NMoneyTreeProt
{

#ifdef PROT_USE_XML

const char* EnumValToStr(EMoneyTreeResult e)
{
	switch(e)
	{
	case Succeed:
		return "Succeed";
	case Error:
		return "Error";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EMoneyTreeResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EMoneyTreeResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("Succeed", Succeed));
		mapStr2Val.insert(make_pair("Error", Error));
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

} //namespace NMoneyTreeProt
