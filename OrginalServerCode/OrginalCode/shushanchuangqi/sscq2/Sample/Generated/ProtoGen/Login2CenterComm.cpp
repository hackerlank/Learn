/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    Login2CenterComm.cpp
//  Purpose:      LoginServer到CenterServer的基本通信协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "Login2CenterComm.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NLogin2CenterComm
{

#ifdef PROT_USE_XML

const char* EnumValToStr(EReqResult e)
{
	switch(e)
	{
	case eReqSucceed:
		return "eReqSucceed";
	case eReqFull:
		return "eReqFull";
	case eReqOnline:
		return "eReqOnline";
	case eReqKickWait:
		return "eReqKickWait";
	case eReqLeaveWait:
		return "eReqLeaveWait";
	case eReqTooFreqent:
		return "eReqTooFreqent";
	case eReqNotInited:
		return "eReqNotInited";
	case eReqOtherErr:
		return "eReqOtherErr";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EReqResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EReqResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eReqSucceed", eReqSucceed));
		mapStr2Val.insert(make_pair("eReqFull", eReqFull));
		mapStr2Val.insert(make_pair("eReqOnline", eReqOnline));
		mapStr2Val.insert(make_pair("eReqKickWait", eReqKickWait));
		mapStr2Val.insert(make_pair("eReqLeaveWait", eReqLeaveWait));
		mapStr2Val.insert(make_pair("eReqTooFreqent", eReqTooFreqent));
		mapStr2Val.insert(make_pair("eReqNotInited", eReqNotInited));
		mapStr2Val.insert(make_pair("eReqOtherErr", eReqOtherErr));
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

} //namespace NLogin2CenterComm
