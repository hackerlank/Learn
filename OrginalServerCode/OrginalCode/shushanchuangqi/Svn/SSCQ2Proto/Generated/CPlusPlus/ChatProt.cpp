/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    ChatProt.cpp
//  Purpose:      聊天协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "ChatProt.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NChatProt
{

#ifdef PROT_USE_XML

const char* EnumValToStr(EChatResult e)
{
	switch(e)
	{
	case eChatSucceed:
		return "eChatSucceed";
	case eChatNotExist:
		return "eChatNotExist";
	case eChatErrStore:
		return "eChatErrStore";
	case eChatErrOther:
		return "eChatErrOther";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EChatResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EChatResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eChatSucceed", eChatSucceed));
		mapStr2Val.insert(make_pair("eChatNotExist", eChatNotExist));
		mapStr2Val.insert(make_pair("eChatErrStore", eChatErrStore));
		mapStr2Val.insert(make_pair("eChatErrOther", eChatErrOther));
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

const char* EnumValToStr(EBubbleResult e)
{
	switch(e)
	{
	case eBRSuccess:
		return "eBRSuccess";
	case eBRFailed:
		return "eBRFailed";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EBubbleResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EBubbleResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eBRSuccess", eBRSuccess));
		mapStr2Val.insert(make_pair("eBRFailed", eBRFailed));
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

} //namespace NChatProt
