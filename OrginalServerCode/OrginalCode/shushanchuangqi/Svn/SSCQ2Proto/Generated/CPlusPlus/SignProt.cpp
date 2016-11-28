/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    SignProt.cpp
//  Purpose:      签到协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "SignProt.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NSignProt
{

#ifdef PROT_USE_XML

const char* EnumValToStr(ESignResult e)
{
	switch(e)
	{
	case eSignSucceed:
		return "eSignSucceed";
	case eSignHasDone:
		return "eSignHasDone";
	case eSignResignDone:
		return "eSignResignDone";
	case eSignResignErrDate:
		return "eSignResignErrDate";
	case eSignResignOverTimes:
		return "eSignResignOverTimes";
	case eSignAwardHasGet:
		return "eSignAwardHasGet";
	case eSignAwardIdErr:
		return "eSignAwardIdErr";
	case eSignAwardLowDays:
		return "eSignAwardLowDays";
	case eSignAwardPacketFull:
		return "eSignAwardPacketFull";
	case eSignVIP:
		return "eSignVIP";
	case eSignOther:
		return "eSignOther";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, ESignResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, ESignResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eSignSucceed", eSignSucceed));
		mapStr2Val.insert(make_pair("eSignHasDone", eSignHasDone));
		mapStr2Val.insert(make_pair("eSignResignDone", eSignResignDone));
		mapStr2Val.insert(make_pair("eSignResignErrDate", eSignResignErrDate));
		mapStr2Val.insert(make_pair("eSignResignOverTimes", eSignResignOverTimes));
		mapStr2Val.insert(make_pair("eSignAwardHasGet", eSignAwardHasGet));
		mapStr2Val.insert(make_pair("eSignAwardIdErr", eSignAwardIdErr));
		mapStr2Val.insert(make_pair("eSignAwardLowDays", eSignAwardLowDays));
		mapStr2Val.insert(make_pair("eSignAwardPacketFull", eSignAwardPacketFull));
		mapStr2Val.insert(make_pair("eSignVIP", eSignVIP));
		mapStr2Val.insert(make_pair("eSignOther", eSignOther));
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

} //namespace NSignProt
