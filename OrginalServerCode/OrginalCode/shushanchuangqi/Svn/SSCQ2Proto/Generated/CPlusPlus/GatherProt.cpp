/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    GatherProt.cpp
//  Purpose:      采集协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "GatherProt.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NGatherProt
{

#ifdef PROT_USE_XML

const char* EnumValToStr(EGatherResult e)
{
	switch(e)
	{
	case eGatherSuccess:
		return "eGatherSuccess";
	case eGatherIn:
		return "eGatherIn";
	case eGatherOut:
		return "eGatherOut";
	case eGatherItemLimit:
		return "eGatherItemLimit";
	case eGatherBusy:
		return "eGatherBusy";
	case eGatherPackEmptyMin:
		return "eGatherPackEmptyMin";
	case eGatherVIP:
		return "eGatherVIP";
	case eGatherLevel:
		return "eGatherLevel";
	case eGatherNotExist:
		return "eGatherNotExist";
	case eGatherTooFar:
		return "eGatherTooFar";
	case eGatherNumLimit:
		return "eGatherNumLimit";
	case eGatherTask:
		return "eGatherTask";
	case eGatherCancel:
		return "eGatherCancel";
	case eGatherFinish:
		return "eGatherFinish";
	case eGatherLuaErr:
		return "eGatherLuaErr";
	case eGatherOtherErr:
		return "eGatherOtherErr";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EGatherResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EGatherResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eGatherSuccess", eGatherSuccess));
		mapStr2Val.insert(make_pair("eGatherIn", eGatherIn));
		mapStr2Val.insert(make_pair("eGatherOut", eGatherOut));
		mapStr2Val.insert(make_pair("eGatherItemLimit", eGatherItemLimit));
		mapStr2Val.insert(make_pair("eGatherBusy", eGatherBusy));
		mapStr2Val.insert(make_pair("eGatherPackEmptyMin", eGatherPackEmptyMin));
		mapStr2Val.insert(make_pair("eGatherVIP", eGatherVIP));
		mapStr2Val.insert(make_pair("eGatherLevel", eGatherLevel));
		mapStr2Val.insert(make_pair("eGatherNotExist", eGatherNotExist));
		mapStr2Val.insert(make_pair("eGatherTooFar", eGatherTooFar));
		mapStr2Val.insert(make_pair("eGatherNumLimit", eGatherNumLimit));
		mapStr2Val.insert(make_pair("eGatherTask", eGatherTask));
		mapStr2Val.insert(make_pair("eGatherCancel", eGatherCancel));
		mapStr2Val.insert(make_pair("eGatherFinish", eGatherFinish));
		mapStr2Val.insert(make_pair("eGatherLuaErr", eGatherLuaErr));
		mapStr2Val.insert(make_pair("eGatherOtherErr", eGatherOtherErr));
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

const char* GetDescription(EGatherResult e)
{
	switch(e)
	{
	case eGatherSuccess:
		return "成功";
	case eGatherIn:
		return "正在采集中";
	case eGatherOut:
		return "没有采集中";
	case eGatherItemLimit:
		return "采集所需物品不足";
	case eGatherBusy:
		return "玩家忙";
	case eGatherPackEmptyMin:
		return "采集空格子不足";
	case eGatherVIP:
		return "御剑等级不足";
	case eGatherLevel:
		return "等级不足";
	case eGatherNotExist:
		return "采集物不存在";
	case eGatherTooFar:
		return "采集物太远";
	case eGatherNumLimit:
		return "采集物数量不足";
	case eGatherTask:
		return "需要接相关任务才可以采集";
	case eGatherCancel:
		return "采集中断";
	case eGatherFinish:
		return "采集完成";
	case eGatherLuaErr:
		return "Lua脚本拒绝";
	case eGatherOtherErr:
		return "未知错误";
	default:
		return "未知错误";
	}
}

#ifdef PROT_USE_XML

const char* EnumValToStr(EGatherConType e)
{
	switch(e)
	{
	case eGCT_None:
		return "eGCT_None";
	case eGCT_Level:
		return "eGCT_Level";
	case eGCT_Item:
		return "eGCT_Item";
	case eGCT_VIP:
		return "eGCT_VIP";
	case eGCT_End:
		return "eGCT_End";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EGatherConType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EGatherConType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eGCT_None", eGCT_None));
		mapStr2Val.insert(make_pair("eGCT_Level", eGCT_Level));
		mapStr2Val.insert(make_pair("eGCT_Item", eGCT_Item));
		mapStr2Val.insert(make_pair("eGCT_VIP", eGCT_VIP));
		mapStr2Val.insert(make_pair("eGCT_End", eGCT_End));
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

const char* GetDescription(EGatherConType e)
{
	switch(e)
	{
	case eGCT_None:
		return "无定义";
	case eGCT_Level:
		return "等级";
	case eGCT_Item:
		return "道具，包括仙石等";
	case eGCT_VIP:
		return "VIP宝箱";
	case eGCT_End:
		return "定义完毕";
	default:
		return "未知错误";
	}
}

} //namespace NGatherProt
