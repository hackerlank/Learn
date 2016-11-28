/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    ProtoVersion.cpp
//  Purpose:      协议版本号
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "ProtoVersion.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NProtoVersion
{

#ifdef PROT_USE_XML

const char* EnumValToStr(EProtoVer e)
{
	switch(e)
	{
	case EPROTOVERSION:
		return "EPROTOVERSION";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EProtoVer& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EProtoVer> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("EPROTOVERSION", EPROTOVERSION));
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

} //namespace NProtoVersion
