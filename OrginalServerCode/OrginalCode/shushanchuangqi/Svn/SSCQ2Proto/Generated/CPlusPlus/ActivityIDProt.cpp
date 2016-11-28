/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    ActivityIDProt.cpp
//  Purpose:      活动ID统一管理
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "ActivityIDProt.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NActivityIDProt
{

#ifdef PROT_USE_XML

const char* EnumValToStr(EActivityID e)
{
	switch(e)
	{
	case eActivityID_None:
		return "eActivityID_None";
	case eQQCoinActivity:
		return "eQQCoinActivity";
	case eOpenActActivity:
		return "eOpenActActivity";
	case eSevenConsumeAct:
		return "eSevenConsumeAct";
	case eDragonBallAct:
		return "eDragonBallAct";
	case eActivityID_Max:
		return "eActivityID_Max";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EActivityID& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EActivityID> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eActivityID_None", eActivityID_None));
		mapStr2Val.insert(make_pair("eQQCoinActivity", eQQCoinActivity));
		mapStr2Val.insert(make_pair("eOpenActActivity", eOpenActActivity));
		mapStr2Val.insert(make_pair("eSevenConsumeAct", eSevenConsumeAct));
		mapStr2Val.insert(make_pair("eDragonBallAct", eDragonBallAct));
		mapStr2Val.insert(make_pair("eActivityID_Max", eActivityID_Max));
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

} //namespace NActivityIDProt
