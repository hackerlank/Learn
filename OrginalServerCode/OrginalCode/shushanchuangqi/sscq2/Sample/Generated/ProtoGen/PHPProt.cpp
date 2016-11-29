/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    PHPProt.cpp
//  Purpose:      PHP相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "PHPProt.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NPHPProt
{

#ifdef PROT_USE_XML

const char* EnumValToStr(EOptResult e)
{
	switch(e)
	{
	case eOptResultSucc:
		return "eOptResultSucc";
	case eOptResultFailed:
		return "eOptResultFailed";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EOptResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EOptResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eOptResultSucc", eOptResultSucc));
		mapStr2Val.insert(make_pair("eOptResultFailed", eOptResultFailed));
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

const char* EnumValToStr(EOptType e)
{
	switch(e)
	{
	case eOptNone:
		return "eOptNone";
	case eOptLockUser:
		return "eOptLockUser";
	case eOptUnlockUser:
		return "eOptUnlockUser";
	case eOptLockSpeak:
		return "eOptLockSpeak";
	case eOptUnlockSpeak:
		return "eOptUnlockSpeak";
	case eOptSetPlayerVIPLevel:
		return "eOptSetPlayerVIPLevel";
	case eOptAddGrowthValue:
		return "eOptAddGrowthValue";
	case eOptEnd:
		return "eOptEnd";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EOptType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EOptType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eOptNone", eOptNone));
		mapStr2Val.insert(make_pair("eOptLockUser", eOptLockUser));
		mapStr2Val.insert(make_pair("eOptUnlockUser", eOptUnlockUser));
		mapStr2Val.insert(make_pair("eOptLockSpeak", eOptLockSpeak));
		mapStr2Val.insert(make_pair("eOptUnlockSpeak", eOptUnlockSpeak));
		mapStr2Val.insert(make_pair("eOptSetPlayerVIPLevel", eOptSetPlayerVIPLevel));
		mapStr2Val.insert(make_pair("eOptAddGrowthValue", eOptAddGrowthValue));
		mapStr2Val.insert(make_pair("eOptEnd", eOptEnd));
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

const char* EnumValToStr(EPHPTaskType e)
{
	switch(e)
	{
	case ePHPTaskNone:
		return "ePHPTaskNone";
	case ePHPYaMenTask:
		return "ePHPYaMenTask";
	case ePHPShiMenTask:
		return "ePHPShiMenTask";
	case ePHPTaskEnd:
		return "ePHPTaskEnd";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EPHPTaskType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EPHPTaskType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("ePHPTaskNone", ePHPTaskNone));
		mapStr2Val.insert(make_pair("ePHPYaMenTask", ePHPYaMenTask));
		mapStr2Val.insert(make_pair("ePHPShiMenTask", ePHPShiMenTask));
		mapStr2Val.insert(make_pair("ePHPTaskEnd", ePHPTaskEnd));
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

const char* EnumValToStr(ESendTarget e)
{
	switch(e)
	{
	case eSendTargetNone:
		return "eSendTargetNone";
	case eIsOnline:
		return "eIsOnline";
	case eAll:
		return "eAll";
	case eClanMember:
		return "eClanMember";
	case eClanBag:
		return "eClanBag";
	case eSendTargetEnd:
		return "eSendTargetEnd";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, ESendTarget& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, ESendTarget> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eSendTargetNone", eSendTargetNone));
		mapStr2Val.insert(make_pair("eIsOnline", eIsOnline));
		mapStr2Val.insert(make_pair("eAll", eAll));
		mapStr2Val.insert(make_pair("eClanMember", eClanMember));
		mapStr2Val.insert(make_pair("eClanBag", eClanBag));
		mapStr2Val.insert(make_pair("eSendTargetEnd", eSendTargetEnd));
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

const char* EnumValToStr(ETaskOpt e)
{
	switch(e)
	{
	case eTaskOptNone:
		return "eTaskOptNone";
	case eTaskOptComplete:
		return "eTaskOptComplete";
	case eTaskOptCompAndReward:
		return "eTaskOptCompAndReward";
	case eTaskOptReward:
		return "eTaskOptReward";
	case eTaskOptEnd:
		return "eTaskOptEnd";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, ETaskOpt& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, ETaskOpt> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eTaskOptNone", eTaskOptNone));
		mapStr2Val.insert(make_pair("eTaskOptComplete", eTaskOptComplete));
		mapStr2Val.insert(make_pair("eTaskOptCompAndReward", eTaskOptCompAndReward));
		mapStr2Val.insert(make_pair("eTaskOptReward", eTaskOptReward));
		mapStr2Val.insert(make_pair("eTaskOptEnd", eTaskOptEnd));
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

const char* EnumValToStr(ETaskState e)
{
	switch(e)
	{
	case eTaskStateNone:
		return "eTaskStateNone";
	case eTaskStateSuc:
		return "eTaskStateSuc";
	case eTaskStateNoRole:
		return "eTaskStateNoRole";
	case eTaskStateNoComp:
		return "eTaskStateNoComp";
	case eTaskStateSended:
		return "eTaskStateSended";
	case eTaskStateSendErr:
		return "eTaskStateSendErr";
	case eTaskStateParamErr:
		return "eTaskStateParamErr";
	case eTaskStateOtherErr:
		return "eTaskStateOtherErr";
	case eTaskStateEnd:
		return "eTaskStateEnd";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, ETaskState& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, ETaskState> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eTaskStateNone", eTaskStateNone));
		mapStr2Val.insert(make_pair("eTaskStateSuc", eTaskStateSuc));
		mapStr2Val.insert(make_pair("eTaskStateNoRole", eTaskStateNoRole));
		mapStr2Val.insert(make_pair("eTaskStateNoComp", eTaskStateNoComp));
		mapStr2Val.insert(make_pair("eTaskStateSended", eTaskStateSended));
		mapStr2Val.insert(make_pair("eTaskStateSendErr", eTaskStateSendErr));
		mapStr2Val.insert(make_pair("eTaskStateParamErr", eTaskStateParamErr));
		mapStr2Val.insert(make_pair("eTaskStateOtherErr", eTaskStateOtherErr));
		mapStr2Val.insert(make_pair("eTaskStateEnd", eTaskStateEnd));
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

const char* EnumValToStr(EPlatformType e)
{
	switch(e)
	{
	case ePlatformNone:
		return "ePlatformNone";
	case ePlatformTypeQQYellow:
		return "ePlatformTypeQQYellow";
	case ePlatformTypeQQPengyou:
		return "ePlatformTypeQQPengyou";
	case ePlatformTypeQQWeibo:
		return "ePlatformTypeQQWeibo";
	case ePlatformTypeQQPlus:
		return "ePlatformTypeQQPlus";
	case ePlatformTypeQQGame:
		return "ePlatformTypeQQGame";
	case ePlatformTypeQQ3366:
		return "ePlatformTypeQQ3366";
	case ePlatformTypeQQKingxin:
		return "ePlatformTypeQQKingxin";
	case ePlatformTypeKingxin:
		return "ePlatformTypeKingxin";
	case ePlatformTypeEnd:
		return "ePlatformTypeEnd";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EPlatformType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EPlatformType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("ePlatformNone", ePlatformNone));
		mapStr2Val.insert(make_pair("ePlatformTypeQQYellow", ePlatformTypeQQYellow));
		mapStr2Val.insert(make_pair("ePlatformTypeQQPengyou", ePlatformTypeQQPengyou));
		mapStr2Val.insert(make_pair("ePlatformTypeQQWeibo", ePlatformTypeQQWeibo));
		mapStr2Val.insert(make_pair("ePlatformTypeQQPlus", ePlatformTypeQQPlus));
		mapStr2Val.insert(make_pair("ePlatformTypeQQGame", ePlatformTypeQQGame));
		mapStr2Val.insert(make_pair("ePlatformTypeQQ3366", ePlatformTypeQQ3366));
		mapStr2Val.insert(make_pair("ePlatformTypeQQKingxin", ePlatformTypeQQKingxin));
		mapStr2Val.insert(make_pair("ePlatformTypeKingxin", ePlatformTypeKingxin));
		mapStr2Val.insert(make_pair("ePlatformTypeEnd", ePlatformTypeEnd));
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

const char* EnumValToStr(EQQPlatformType e)
{
	switch(e)
	{
	case eQQPlatformTypeNone:
		return "eQQPlatformTypeNone";
	case eQQPlatformTypeYellow:
		return "eQQPlatformTypeYellow";
	case eQQPlatformTypeBlue:
		return "eQQPlatformTypeBlue";
	case eQQPlatformTypeRed:
		return "eQQPlatformTypeRed";
	case eQQPlatformTypeEnd:
		return "eQQPlatformTypeEnd";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EQQPlatformType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EQQPlatformType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eQQPlatformTypeNone", eQQPlatformTypeNone));
		mapStr2Val.insert(make_pair("eQQPlatformTypeYellow", eQQPlatformTypeYellow));
		mapStr2Val.insert(make_pair("eQQPlatformTypeBlue", eQQPlatformTypeBlue));
		mapStr2Val.insert(make_pair("eQQPlatformTypeRed", eQQPlatformTypeRed));
		mapStr2Val.insert(make_pair("eQQPlatformTypeEnd", eQQPlatformTypeEnd));
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

const char* GetDescription(EQQPlatformType e)
{
	switch(e)
	{
	case eQQPlatformTypeNone:
		return "无";
	case eQQPlatformTypeYellow:
		return "黄钻平台";
	case eQQPlatformTypeBlue:
		return "蓝钻平台";
	case eQQPlatformTypeRed:
		return "红钻/VIP平台";
	case eQQPlatformTypeEnd:
		return "结束";
	default:
		return "未知错误";
	}
}

#ifdef PROT_USE_XML

const char* EnumValToStr(EPHPPtType e)
{
	switch(e)
	{
	case ePHPPtTypeNone:
		return "ePHPPtTypeNone";
	case ePHPPtTypeQQYellow:
		return "ePHPPtTypeQQYellow";
	case ePHPPtTypeQQPengyou:
		return "ePHPPtTypeQQPengyou";
	case ePHPPtTypeQQWeibo:
		return "ePHPPtTypeQQWeibo";
	case ePHPPtTypeQQPlus:
		return "ePHPPtTypeQQPlus";
	case ePHPPtTypeQQGame:
		return "ePHPPtTypeQQGame";
	case ePHPPtTypeQQ3366:
		return "ePHPPtTypeQQ3366";
	case ePHPPtTypeQQKingxin:
		return "ePHPPtTypeQQKingxin";
	case ePHPPtTypeKingxin:
		return "ePHPPtTypeKingxin";
	case ePHPPtTypeMax:
		return "ePHPPtTypeMax";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EPHPPtType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EPHPPtType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("ePHPPtTypeNone", ePHPPtTypeNone));
		mapStr2Val.insert(make_pair("ePHPPtTypeQQYellow", ePHPPtTypeQQYellow));
		mapStr2Val.insert(make_pair("ePHPPtTypeQQPengyou", ePHPPtTypeQQPengyou));
		mapStr2Val.insert(make_pair("ePHPPtTypeQQWeibo", ePHPPtTypeQQWeibo));
		mapStr2Val.insert(make_pair("ePHPPtTypeQQPlus", ePHPPtTypeQQPlus));
		mapStr2Val.insert(make_pair("ePHPPtTypeQQGame", ePHPPtTypeQQGame));
		mapStr2Val.insert(make_pair("ePHPPtTypeQQ3366", ePHPPtTypeQQ3366));
		mapStr2Val.insert(make_pair("ePHPPtTypeQQKingxin", ePHPPtTypeQQKingxin));
		mapStr2Val.insert(make_pair("ePHPPtTypeKingxin", ePHPPtTypeKingxin));
		mapStr2Val.insert(make_pair("ePHPPtTypeMax", ePHPPtTypeMax));
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

const char* GetDescription(EPHPPtType e)
{
	switch(e)
	{
	case ePHPPtTypeNone:
		return "无";
	case ePHPPtTypeQQYellow:
		return "QQ黄钻平台/Qzone";
	case ePHPPtTypeQQPengyou:
		return "QQ朋友/校友/黄钻";
	case ePHPPtTypeQQWeibo:
		return "QQ微博平台";
	case ePHPPtTypeQQPlus:
		return "QQ/Q+平台";
	case ePHPPtTypeQQGame:
		return "QQ蓝钻/游戏平台";
	case ePHPPtTypeQQ3366:
		return "QQ蓝钻/3366平台/包子";
	case ePHPPtTypeQQKingxin:
		return "QQ官网平台/QQ会员";
	case ePHPPtTypeKingxin:
		return "恺英官网平台";
	case ePHPPtTypeMax:
		return "最大值";
	default:
		return "未知错误";
	}
}

#ifdef PROT_USE_XML

const char* EnumValToStr(EShowType e)
{
	switch(e)
	{
	case eShowNone:
		return "eShowNone";
	case eChatWindowNotice:
		return "eChatWindowNotice";
	case eAllNotice:
		return "eAllNotice";
	case eShowEnd:
		return "eShowEnd";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EShowType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EShowType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eShowNone", eShowNone));
		mapStr2Val.insert(make_pair("eChatWindowNotice", eChatWindowNotice));
		mapStr2Val.insert(make_pair("eAllNotice", eAllNotice));
		mapStr2Val.insert(make_pair("eShowEnd", eShowEnd));
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

const char* EnumValToStr(ERollType e)
{
	switch(e)
	{
	case eRollNone:
		return "eRollNone";
	case eIsRoll:
		return "eIsRoll";
	case eNoRoll:
		return "eNoRoll";
	case eRollEnd:
		return "eRollEnd";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, ERollType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, ERollType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eRollNone", eRollNone));
		mapStr2Val.insert(make_pair("eIsRoll", eIsRoll));
		mapStr2Val.insert(make_pair("eNoRoll", eNoRoll));
		mapStr2Val.insert(make_pair("eRollEnd", eRollEnd));
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

const char* EnumValToStr(ESendType e)
{
	switch(e)
	{
	case eSendNone:
		return "eSendNone";
	case eIsImmediateSend:
		return "eIsImmediateSend";
	case eNoImmediateSend:
		return "eNoImmediateSend";
	case eSendEnd:
		return "eSendEnd";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, ESendType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, ESendType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eSendNone", eSendNone));
		mapStr2Val.insert(make_pair("eIsImmediateSend", eIsImmediateSend));
		mapStr2Val.insert(make_pair("eNoImmediateSend", eNoImmediateSend));
		mapStr2Val.insert(make_pair("eSendEnd", eSendEnd));
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

const char* EnumValToStr(EDialogType e)
{
	switch(e)
	{
	case eDialogNone:
		return "eDialogNone";
	case eUpdateNoticeDialog:
		return "eUpdateNoticeDialog";
	case eSysDialog:
		return "eSysDialog";
	case eDialogEnd:
		return "eDialogEnd";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EDialogType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EDialogType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eDialogNone", eDialogNone));
		mapStr2Val.insert(make_pair("eUpdateNoticeDialog", eUpdateNoticeDialog));
		mapStr2Val.insert(make_pair("eSysDialog", eSysDialog));
		mapStr2Val.insert(make_pair("eDialogEnd", eDialogEnd));
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

const char* EnumValToStr(EActivityType e)
{
	switch(e)
	{
	case eActivity_None:
		return "eActivity_None";
	case eActivity_WorldBoss:
		return "eActivity_WorldBoss";
	case eActivity_LangHuanBless:
		return "eActivity_LangHuanBless";
	case eActivity_DragonBall:
		return "eActivity_DragonBall";
	case eActivity_SevenConsume:
		return "eActivity_SevenConsume";
	case eActivity_QQCoin:
		return "eActivity_QQCoin";
	case eActivity_Max:
		return "eActivity_Max";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, EActivityType& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, EActivityType> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eActivity_None", eActivity_None));
		mapStr2Val.insert(make_pair("eActivity_WorldBoss", eActivity_WorldBoss));
		mapStr2Val.insert(make_pair("eActivity_LangHuanBless", eActivity_LangHuanBless));
		mapStr2Val.insert(make_pair("eActivity_DragonBall", eActivity_DragonBall));
		mapStr2Val.insert(make_pair("eActivity_SevenConsume", eActivity_SevenConsume));
		mapStr2Val.insert(make_pair("eActivity_QQCoin", eActivity_QQCoin));
		mapStr2Val.insert(make_pair("eActivity_Max", eActivity_Max));
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

SUserIDAndName::SUserIDAndName() : qwUserID(0) { }

SUserIDAndName::SUserIDAndName(UINT64 qwUserID_, const std::string& strName_) : qwUserID(qwUserID_), strName(strName_) { }

SUserIDAndName::SUserIDAndName(SUserIDAndName&& src) : qwUserID(src.qwUserID), strName(move(src.strName)) { }

SUserIDAndName& SUserIDAndName::operator=(SUserIDAndName&& rhs)
{
	if(this != &rhs)
	{
		this->~SUserIDAndName();
		new (this) SUserIDAndName(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SUserIDAndName& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwUserID;
	src >> s.strName;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SUserIDAndName& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.qwUserID;
	src << s.strName;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SUserIDAndName& s)
{
	if(strcmp(rElement.Value(), "SUserIDAndName") != 0)
	{
		LOG_CRI << "rElement is not SUserIDAndName!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwUserID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwUserID") != 0)
	{
		LOG_CRI << "Attribute: name is not qwUserID!";
		return false;
	}
	const char* pszVal_qwUserID = pElemChild->Attribute("value");
	if(pszVal_qwUserID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwUserID, s.qwUserID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strName is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strName") != 0)
	{
		LOG_CRI << "Attribute: name is not strName!";
		return false;
	}
	const char* pszVal_strName = pElemChild->Attribute("value");
	if(pszVal_strName == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strName = pszVal_strName;
	return true;
}

bool ToXML(const SUserIDAndName& s, TiXmlElement& rElement)
{
	rElement.SetValue("SUserIDAndName");
	rElement.SetAttribute("type", ToUTF8Ptr("UserID和Name"));
	unique_ptr<TiXmlElement> pElem_qwUserID(new TiXmlElement("UINT64"));
	if(pElem_qwUserID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwUserID->SetAttribute("name", "qwUserID");
	pElem_qwUserID->SetAttribute("value", NumberToString(s.qwUserID).c_str());
	pElem_qwUserID->SetAttribute("comment", ToUTF8Ptr("用户ID"));
	if(rElement.LinkEndChild(pElem_qwUserID.get()) != NULL)
		pElem_qwUserID.release();
	unique_ptr<TiXmlElement> pElem_strName(new TiXmlElement("string"));
	if(pElem_strName == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strName->SetAttribute("name", "strName");
	pElem_strName->SetAttribute("value", s.strName.c_str());
	pElem_strName->SetAttribute("comment", ToUTF8Ptr("角色名称"));
	if(rElement.LinkEndChild(pElem_strName.get()) != NULL)
		pElem_strName.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecUserIDAndName& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SUserIDAndName s;
		if(!FromXML(*pElemMember, s))
		{
			LOG_CRI << "FromXML fails!";
			return false;
		}
		vec.emplace_back(move(s));
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecUserIDAndName& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SUserIDAndName"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!ToXML(vec[i], *pElemMember))
		{
			LOG_CRI << "ToXML fails!";
			return false;
		}
		if(rElement.LinkEndChild(pElemMember.get()) != NULL)
			pElemMember.release();
	}
	return true;
}

#endif

SNotice::SNotice() : dwNoticeID(0), byNoticeType(0), dwBeginTime(0), dwEndTime(0) { }

SNotice::SNotice(UINT32 dwNoticeID_, UINT8 byNoticeType_, const std::string& strContent_, UINT32 dwBeginTime_, UINT32 dwEndTime_)
			: dwNoticeID(dwNoticeID_), byNoticeType(byNoticeType_), strContent(strContent_), dwBeginTime(dwBeginTime_), dwEndTime(dwEndTime_) { }

SNotice::SNotice(SNotice&& src) : dwNoticeID(src.dwNoticeID), byNoticeType(src.byNoticeType), strContent(move(src.strContent)), dwBeginTime(src.dwBeginTime), dwEndTime(src.dwEndTime) { }

SNotice& SNotice::operator=(SNotice&& rhs)
{
	if(this != &rhs)
	{
		this->~SNotice();
		new (this) SNotice(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SNotice& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.dwNoticeID;
	src >> s.byNoticeType;
	src >> s.strContent;
	src >> s.dwBeginTime;
	src >> s.dwEndTime;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SNotice& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.dwNoticeID;
	src << s.byNoticeType;
	src << s.strContent;
	src << s.dwBeginTime;
	src << s.dwEndTime;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SNotice& s)
{
	if(strcmp(rElement.Value(), "SNotice") != 0)
	{
		LOG_CRI << "rElement is not SNotice!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwNoticeID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwNoticeID") != 0)
	{
		LOG_CRI << "Attribute: name is not dwNoticeID!";
		return false;
	}
	const char* pszVal_dwNoticeID = pElemChild->Attribute("value");
	if(pszVal_dwNoticeID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwNoticeID, s.dwNoticeID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byNoticeType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byNoticeType") != 0)
	{
		LOG_CRI << "Attribute: name is not byNoticeType!";
		return false;
	}
	const char* pszVal_byNoticeType = pElemChild->Attribute("value");
	if(pszVal_byNoticeType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byNoticeType, s.byNoticeType))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strContent is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strContent") != 0)
	{
		LOG_CRI << "Attribute: name is not strContent!";
		return false;
	}
	const char* pszVal_strContent = pElemChild->Attribute("value");
	if(pszVal_strContent == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strContent = pszVal_strContent;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwBeginTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwBeginTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwBeginTime!";
		return false;
	}
	const char* pszVal_dwBeginTime = pElemChild->Attribute("value");
	if(pszVal_dwBeginTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwBeginTime, s.dwBeginTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwEndTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwEndTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwEndTime!";
		return false;
	}
	const char* pszVal_dwEndTime = pElemChild->Attribute("value");
	if(pszVal_dwEndTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwEndTime, s.dwEndTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SNotice& s, TiXmlElement& rElement)
{
	rElement.SetValue("SNotice");
	rElement.SetAttribute("type", ToUTF8Ptr("公告"));
	unique_ptr<TiXmlElement> pElem_dwNoticeID(new TiXmlElement("UINT32"));
	if(pElem_dwNoticeID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwNoticeID->SetAttribute("name", "dwNoticeID");
	pElem_dwNoticeID->SetAttribute("value", NumberToString(s.dwNoticeID).c_str());
	pElem_dwNoticeID->SetAttribute("comment", ToUTF8Ptr("公告ID"));
	if(rElement.LinkEndChild(pElem_dwNoticeID.get()) != NULL)
		pElem_dwNoticeID.release();
	unique_ptr<TiXmlElement> pElem_byNoticeType(new TiXmlElement("UINT8"));
	if(pElem_byNoticeType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byNoticeType->SetAttribute("name", "byNoticeType");
	pElem_byNoticeType->SetAttribute("value", NumberToString(s.byNoticeType).c_str());
	pElem_byNoticeType->SetAttribute("comment", ToUTF8Ptr("公告类型"));
	if(rElement.LinkEndChild(pElem_byNoticeType.get()) != NULL)
		pElem_byNoticeType.release();
	unique_ptr<TiXmlElement> pElem_strContent(new TiXmlElement("string"));
	if(pElem_strContent == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strContent->SetAttribute("name", "strContent");
	pElem_strContent->SetAttribute("value", s.strContent.c_str());
	pElem_strContent->SetAttribute("comment", ToUTF8Ptr("公告内容"));
	if(rElement.LinkEndChild(pElem_strContent.get()) != NULL)
		pElem_strContent.release();
	unique_ptr<TiXmlElement> pElem_dwBeginTime(new TiXmlElement("UINT32"));
	if(pElem_dwBeginTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwBeginTime->SetAttribute("name", "dwBeginTime");
	pElem_dwBeginTime->SetAttribute("value", NumberToString(s.dwBeginTime).c_str());
	pElem_dwBeginTime->SetAttribute("comment", ToUTF8Ptr("公告开始时间"));
	if(rElement.LinkEndChild(pElem_dwBeginTime.get()) != NULL)
		pElem_dwBeginTime.release();
	unique_ptr<TiXmlElement> pElem_dwEndTime(new TiXmlElement("UINT32"));
	if(pElem_dwEndTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwEndTime->SetAttribute("name", "dwEndTime");
	pElem_dwEndTime->SetAttribute("value", NumberToString(s.dwEndTime).c_str());
	pElem_dwEndTime->SetAttribute("comment", ToUTF8Ptr("公告结束"));
	if(rElement.LinkEndChild(pElem_dwEndTime.get()) != NULL)
		pElem_dwEndTime.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecNotice& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SNotice s;
		if(!FromXML(*pElemMember, s))
		{
			LOG_CRI << "FromXML fails!";
			return false;
		}
		vec.emplace_back(move(s));
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecNotice& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SNotice"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!ToXML(vec[i], *pElemMember))
		{
			LOG_CRI << "ToXML fails!";
			return false;
		}
		if(rElement.LinkEndChild(pElemMember.get()) != NULL)
			pElemMember.release();
	}
	return true;
}

#endif

SPlayerInfo::SPlayerInfo() : qwUserID(0), wLevel(0), qwGuildID(0), byJob(0), bySex(0), 
			dwSilver(0), dwGold(0), dwCoupon(0), byForbExpire(0), byLockExpire(0), 
			byVIPLevel(0), dwPrestige(0), dwHonor(0), dwDJ(0), dwHistoryDJ(0), 
			dwCreateTime(0), wShiMenTask(0), wYaMenTaTask(0) { }

SPlayerInfo::SPlayerInfo(SPlayerInfo&& src) : qwUserID(src.qwUserID), strName(move(src.strName)), wLevel(src.wLevel), strGuildName(move(src.strGuildName)), qwGuildID(src.qwGuildID), 
			byJob(src.byJob), bySex(src.bySex), dwSilver(src.dwSilver), dwGold(src.dwGold), dwCoupon(src.dwCoupon), 
			byForbExpire(src.byForbExpire), byLockExpire(src.byLockExpire), byVIPLevel(src.byVIPLevel), dwPrestige(src.dwPrestige), dwHonor(src.dwHonor), 
			dwDJ(src.dwDJ), dwHistoryDJ(src.dwHistoryDJ), dwCreateTime(src.dwCreateTime), wShiMenTask(src.wShiMenTask), wYaMenTaTask(src.wYaMenTaTask) { }

SPlayerInfo& SPlayerInfo::operator=(SPlayerInfo&& rhs)
{
	if(this != &rhs)
	{
		this->~SPlayerInfo();
		new (this) SPlayerInfo(rhs);
	}
	return *this;
}

CInArchive& operator>>(CInArchive& src, SPlayerInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwUserID;
	src >> s.strName;
	src >> s.wLevel;
	src >> s.strGuildName;
	src >> s.qwGuildID;
	src >> s.byJob;
	src >> s.bySex;
	src >> s.dwSilver;
	src >> s.dwGold;
	src >> s.dwCoupon;
	src >> s.byForbExpire;
	src >> s.byLockExpire;
	src >> s.byVIPLevel;
	src >> s.dwPrestige;
	src >> s.dwHonor;
	src >> s.dwDJ;
	src >> s.dwHistoryDJ;
	src >> s.dwCreateTime;
	src >> s.wShiMenTask;
	src >> s.wYaMenTaTask;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SPlayerInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.qwUserID;
	src << s.strName;
	src << s.wLevel;
	src << s.strGuildName;
	src << s.qwGuildID;
	src << s.byJob;
	src << s.bySex;
	src << s.dwSilver;
	src << s.dwGold;
	src << s.dwCoupon;
	src << s.byForbExpire;
	src << s.byLockExpire;
	src << s.byVIPLevel;
	src << s.dwPrestige;
	src << s.dwHonor;
	src << s.dwDJ;
	src << s.dwHistoryDJ;
	src << s.dwCreateTime;
	src << s.wShiMenTask;
	src << s.wYaMenTaTask;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SPlayerInfo& s)
{
	if(strcmp(rElement.Value(), "SPlayerInfo") != 0)
	{
		LOG_CRI << "rElement is not SPlayerInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwUserID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwUserID") != 0)
	{
		LOG_CRI << "Attribute: name is not qwUserID!";
		return false;
	}
	const char* pszVal_qwUserID = pElemChild->Attribute("value");
	if(pszVal_qwUserID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwUserID, s.qwUserID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strName is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strName") != 0)
	{
		LOG_CRI << "Attribute: name is not strName!";
		return false;
	}
	const char* pszVal_strName = pElemChild->Attribute("value");
	if(pszVal_strName == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strName = pszVal_strName;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wLevel is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wLevel") != 0)
	{
		LOG_CRI << "Attribute: name is not wLevel!";
		return false;
	}
	const char* pszVal_wLevel = pElemChild->Attribute("value");
	if(pszVal_wLevel == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wLevel, s.wLevel))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for strGuildName is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "string") != 0)
	{
		LOG_CRI << "pElemChild is not string!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "strGuildName") != 0)
	{
		LOG_CRI << "Attribute: name is not strGuildName!";
		return false;
	}
	const char* pszVal_strGuildName = pElemChild->Attribute("value");
	if(pszVal_strGuildName == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	s.strGuildName = pszVal_strGuildName;
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwGuildID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwGuildID") != 0)
	{
		LOG_CRI << "Attribute: name is not qwGuildID!";
		return false;
	}
	const char* pszVal_qwGuildID = pElemChild->Attribute("value");
	if(pszVal_qwGuildID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwGuildID, s.qwGuildID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byJob is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byJob") != 0)
	{
		LOG_CRI << "Attribute: name is not byJob!";
		return false;
	}
	const char* pszVal_byJob = pElemChild->Attribute("value");
	if(pszVal_byJob == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byJob, s.byJob))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for bySex is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "bySex") != 0)
	{
		LOG_CRI << "Attribute: name is not bySex!";
		return false;
	}
	const char* pszVal_bySex = pElemChild->Attribute("value");
	if(pszVal_bySex == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_bySex, s.bySex))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwSilver is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwSilver") != 0)
	{
		LOG_CRI << "Attribute: name is not dwSilver!";
		return false;
	}
	const char* pszVal_dwSilver = pElemChild->Attribute("value");
	if(pszVal_dwSilver == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwSilver, s.dwSilver))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwGold is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwGold") != 0)
	{
		LOG_CRI << "Attribute: name is not dwGold!";
		return false;
	}
	const char* pszVal_dwGold = pElemChild->Attribute("value");
	if(pszVal_dwGold == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwGold, s.dwGold))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwCoupon is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwCoupon") != 0)
	{
		LOG_CRI << "Attribute: name is not dwCoupon!";
		return false;
	}
	const char* pszVal_dwCoupon = pElemChild->Attribute("value");
	if(pszVal_dwCoupon == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwCoupon, s.dwCoupon))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byForbExpire is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byForbExpire") != 0)
	{
		LOG_CRI << "Attribute: name is not byForbExpire!";
		return false;
	}
	const char* pszVal_byForbExpire = pElemChild->Attribute("value");
	if(pszVal_byForbExpire == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byForbExpire, s.byForbExpire))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byLockExpire is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byLockExpire") != 0)
	{
		LOG_CRI << "Attribute: name is not byLockExpire!";
		return false;
	}
	const char* pszVal_byLockExpire = pElemChild->Attribute("value");
	if(pszVal_byLockExpire == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byLockExpire, s.byLockExpire))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byVIPLevel is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byVIPLevel") != 0)
	{
		LOG_CRI << "Attribute: name is not byVIPLevel!";
		return false;
	}
	const char* pszVal_byVIPLevel = pElemChild->Attribute("value");
	if(pszVal_byVIPLevel == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byVIPLevel, s.byVIPLevel))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwPrestige is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwPrestige") != 0)
	{
		LOG_CRI << "Attribute: name is not dwPrestige!";
		return false;
	}
	const char* pszVal_dwPrestige = pElemChild->Attribute("value");
	if(pszVal_dwPrestige == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwPrestige, s.dwPrestige))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwHonor is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwHonor") != 0)
	{
		LOG_CRI << "Attribute: name is not dwHonor!";
		return false;
	}
	const char* pszVal_dwHonor = pElemChild->Attribute("value");
	if(pszVal_dwHonor == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwHonor, s.dwHonor))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwDJ is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwDJ") != 0)
	{
		LOG_CRI << "Attribute: name is not dwDJ!";
		return false;
	}
	const char* pszVal_dwDJ = pElemChild->Attribute("value");
	if(pszVal_dwDJ == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwDJ, s.dwDJ))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwHistoryDJ is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwHistoryDJ") != 0)
	{
		LOG_CRI << "Attribute: name is not dwHistoryDJ!";
		return false;
	}
	const char* pszVal_dwHistoryDJ = pElemChild->Attribute("value");
	if(pszVal_dwHistoryDJ == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwHistoryDJ, s.dwHistoryDJ))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwCreateTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwCreateTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwCreateTime!";
		return false;
	}
	const char* pszVal_dwCreateTime = pElemChild->Attribute("value");
	if(pszVal_dwCreateTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwCreateTime, s.dwCreateTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wShiMenTask is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wShiMenTask") != 0)
	{
		LOG_CRI << "Attribute: name is not wShiMenTask!";
		return false;
	}
	const char* pszVal_wShiMenTask = pElemChild->Attribute("value");
	if(pszVal_wShiMenTask == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wShiMenTask, s.wShiMenTask))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wYaMenTaTask is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wYaMenTaTask") != 0)
	{
		LOG_CRI << "Attribute: name is not wYaMenTaTask!";
		return false;
	}
	const char* pszVal_wYaMenTaTask = pElemChild->Attribute("value");
	if(pszVal_wYaMenTaTask == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wYaMenTaTask, s.wYaMenTaTask))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SPlayerInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SPlayerInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("玩家信息"));
	unique_ptr<TiXmlElement> pElem_qwUserID(new TiXmlElement("UINT64"));
	if(pElem_qwUserID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwUserID->SetAttribute("name", "qwUserID");
	pElem_qwUserID->SetAttribute("value", NumberToString(s.qwUserID).c_str());
	pElem_qwUserID->SetAttribute("comment", ToUTF8Ptr("用户ID"));
	if(rElement.LinkEndChild(pElem_qwUserID.get()) != NULL)
		pElem_qwUserID.release();
	unique_ptr<TiXmlElement> pElem_strName(new TiXmlElement("string"));
	if(pElem_strName == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strName->SetAttribute("name", "strName");
	pElem_strName->SetAttribute("value", s.strName.c_str());
	pElem_strName->SetAttribute("comment", ToUTF8Ptr("角色名称"));
	if(rElement.LinkEndChild(pElem_strName.get()) != NULL)
		pElem_strName.release();
	unique_ptr<TiXmlElement> pElem_wLevel(new TiXmlElement("UINT16"));
	if(pElem_wLevel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wLevel->SetAttribute("name", "wLevel");
	pElem_wLevel->SetAttribute("value", NumberToString(s.wLevel).c_str());
	pElem_wLevel->SetAttribute("comment", ToUTF8Ptr("等级"));
	if(rElement.LinkEndChild(pElem_wLevel.get()) != NULL)
		pElem_wLevel.release();
	unique_ptr<TiXmlElement> pElem_strGuildName(new TiXmlElement("string"));
	if(pElem_strGuildName == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_strGuildName->SetAttribute("name", "strGuildName");
	pElem_strGuildName->SetAttribute("value", s.strGuildName.c_str());
	pElem_strGuildName->SetAttribute("comment", ToUTF8Ptr("帮派名"));
	if(rElement.LinkEndChild(pElem_strGuildName.get()) != NULL)
		pElem_strGuildName.release();
	unique_ptr<TiXmlElement> pElem_qwGuildID(new TiXmlElement("UINT64"));
	if(pElem_qwGuildID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwGuildID->SetAttribute("name", "qwGuildID");
	pElem_qwGuildID->SetAttribute("value", NumberToString(s.qwGuildID).c_str());
	pElem_qwGuildID->SetAttribute("comment", ToUTF8Ptr("帮派ID"));
	if(rElement.LinkEndChild(pElem_qwGuildID.get()) != NULL)
		pElem_qwGuildID.release();
	unique_ptr<TiXmlElement> pElem_byJob(new TiXmlElement("UINT8"));
	if(pElem_byJob == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byJob->SetAttribute("name", "byJob");
	pElem_byJob->SetAttribute("value", NumberToString(s.byJob).c_str());
	pElem_byJob->SetAttribute("comment", ToUTF8Ptr("职业(1、儒；2、释；3、道；4、墨)"));
	if(rElement.LinkEndChild(pElem_byJob.get()) != NULL)
		pElem_byJob.release();
	unique_ptr<TiXmlElement> pElem_bySex(new TiXmlElement("UINT8"));
	if(pElem_bySex == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_bySex->SetAttribute("name", "bySex");
	pElem_bySex->SetAttribute("value", NumberToString(s.bySex).c_str());
	pElem_bySex->SetAttribute("comment", ToUTF8Ptr("性别(1、男；2、女)"));
	if(rElement.LinkEndChild(pElem_bySex.get()) != NULL)
		pElem_bySex.release();
	unique_ptr<TiXmlElement> pElem_dwSilver(new TiXmlElement("UINT32"));
	if(pElem_dwSilver == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwSilver->SetAttribute("name", "dwSilver");
	pElem_dwSilver->SetAttribute("value", NumberToString(s.dwSilver).c_str());
	pElem_dwSilver->SetAttribute("comment", ToUTF8Ptr("银币"));
	if(rElement.LinkEndChild(pElem_dwSilver.get()) != NULL)
		pElem_dwSilver.release();
	unique_ptr<TiXmlElement> pElem_dwGold(new TiXmlElement("UINT32"));
	if(pElem_dwGold == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwGold->SetAttribute("name", "dwGold");
	pElem_dwGold->SetAttribute("value", NumberToString(s.dwGold).c_str());
	pElem_dwGold->SetAttribute("comment", ToUTF8Ptr("仙石"));
	if(rElement.LinkEndChild(pElem_dwGold.get()) != NULL)
		pElem_dwGold.release();
	unique_ptr<TiXmlElement> pElem_dwCoupon(new TiXmlElement("UINT32"));
	if(pElem_dwCoupon == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwCoupon->SetAttribute("name", "dwCoupon");
	pElem_dwCoupon->SetAttribute("value", NumberToString(s.dwCoupon).c_str());
	pElem_dwCoupon->SetAttribute("comment", ToUTF8Ptr("礼券"));
	if(rElement.LinkEndChild(pElem_dwCoupon.get()) != NULL)
		pElem_dwCoupon.release();
	unique_ptr<TiXmlElement> pElem_byForbExpire(new TiXmlElement("UINT8"));
	if(pElem_byForbExpire == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byForbExpire->SetAttribute("name", "byForbExpire");
	pElem_byForbExpire->SetAttribute("value", NumberToString(s.byForbExpire).c_str());
	pElem_byForbExpire->SetAttribute("comment", ToUTF8Ptr("是否禁言(0、否；1、是)"));
	if(rElement.LinkEndChild(pElem_byForbExpire.get()) != NULL)
		pElem_byForbExpire.release();
	unique_ptr<TiXmlElement> pElem_byLockExpire(new TiXmlElement("UINT8"));
	if(pElem_byLockExpire == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byLockExpire->SetAttribute("name", "byLockExpire");
	pElem_byLockExpire->SetAttribute("value", NumberToString(s.byLockExpire).c_str());
	pElem_byLockExpire->SetAttribute("comment", ToUTF8Ptr("是否封号(0、否；1、是)"));
	if(rElement.LinkEndChild(pElem_byLockExpire.get()) != NULL)
		pElem_byLockExpire.release();
	unique_ptr<TiXmlElement> pElem_byVIPLevel(new TiXmlElement("UINT8"));
	if(pElem_byVIPLevel == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byVIPLevel->SetAttribute("name", "byVIPLevel");
	pElem_byVIPLevel->SetAttribute("value", NumberToString(s.byVIPLevel).c_str());
	pElem_byVIPLevel->SetAttribute("comment", ToUTF8Ptr("VIP等级"));
	if(rElement.LinkEndChild(pElem_byVIPLevel.get()) != NULL)
		pElem_byVIPLevel.release();
	unique_ptr<TiXmlElement> pElem_dwPrestige(new TiXmlElement("UINT32"));
	if(pElem_dwPrestige == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwPrestige->SetAttribute("name", "dwPrestige");
	pElem_dwPrestige->SetAttribute("value", NumberToString(s.dwPrestige).c_str());
	pElem_dwPrestige->SetAttribute("comment", ToUTF8Ptr("声望"));
	if(rElement.LinkEndChild(pElem_dwPrestige.get()) != NULL)
		pElem_dwPrestige.release();
	unique_ptr<TiXmlElement> pElem_dwHonor(new TiXmlElement("UINT32"));
	if(pElem_dwHonor == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwHonor->SetAttribute("name", "dwHonor");
	pElem_dwHonor->SetAttribute("value", NumberToString(s.dwHonor).c_str());
	pElem_dwHonor->SetAttribute("comment", ToUTF8Ptr("荣誉"));
	if(rElement.LinkEndChild(pElem_dwHonor.get()) != NULL)
		pElem_dwHonor.release();
	unique_ptr<TiXmlElement> pElem_dwDJ(new TiXmlElement("UINT32"));
	if(pElem_dwDJ == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwDJ->SetAttribute("name", "dwDJ");
	pElem_dwDJ->SetAttribute("value", NumberToString(s.dwDJ).c_str());
	pElem_dwDJ->SetAttribute("comment", ToUTF8Ptr("斗剑排名"));
	if(rElement.LinkEndChild(pElem_dwDJ.get()) != NULL)
		pElem_dwDJ.release();
	unique_ptr<TiXmlElement> pElem_dwHistoryDJ(new TiXmlElement("UINT32"));
	if(pElem_dwHistoryDJ == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwHistoryDJ->SetAttribute("name", "dwHistoryDJ");
	pElem_dwHistoryDJ->SetAttribute("value", NumberToString(s.dwHistoryDJ).c_str());
	pElem_dwHistoryDJ->SetAttribute("comment", ToUTF8Ptr("历史最高斗剑"));
	if(rElement.LinkEndChild(pElem_dwHistoryDJ.get()) != NULL)
		pElem_dwHistoryDJ.release();
	unique_ptr<TiXmlElement> pElem_dwCreateTime(new TiXmlElement("UINT32"));
	if(pElem_dwCreateTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwCreateTime->SetAttribute("name", "dwCreateTime");
	pElem_dwCreateTime->SetAttribute("value", NumberToString(s.dwCreateTime).c_str());
	pElem_dwCreateTime->SetAttribute("comment", ToUTF8Ptr("创角时间"));
	if(rElement.LinkEndChild(pElem_dwCreateTime.get()) != NULL)
		pElem_dwCreateTime.release();
	unique_ptr<TiXmlElement> pElem_wShiMenTask(new TiXmlElement("UINT16"));
	if(pElem_wShiMenTask == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wShiMenTask->SetAttribute("name", "wShiMenTask");
	pElem_wShiMenTask->SetAttribute("value", NumberToString(s.wShiMenTask).c_str());
	pElem_wShiMenTask->SetAttribute("comment", ToUTF8Ptr("师门任务"));
	if(rElement.LinkEndChild(pElem_wShiMenTask.get()) != NULL)
		pElem_wShiMenTask.release();
	unique_ptr<TiXmlElement> pElem_wYaMenTaTask(new TiXmlElement("UINT16"));
	if(pElem_wYaMenTaTask == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wYaMenTaTask->SetAttribute("name", "wYaMenTaTask");
	pElem_wYaMenTaTask->SetAttribute("value", NumberToString(s.wYaMenTaTask).c_str());
	pElem_wYaMenTaTask->SetAttribute("comment", ToUTF8Ptr("衙门任务"));
	if(rElement.LinkEndChild(pElem_wYaMenTaTask.get()) != NULL)
		pElem_wYaMenTaTask.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecPlayerInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SPlayerInfo s;
		if(!FromXML(*pElemMember, s))
		{
			LOG_CRI << "FromXML fails!";
			return false;
		}
		vec.emplace_back(move(s));
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecPlayerInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SPlayerInfo"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!ToXML(vec[i], *pElemMember))
		{
			LOG_CRI << "ToXML fails!";
			return false;
		}
		if(rElement.LinkEndChild(pElemMember.get()) != NULL)
			pElemMember.release();
	}
	return true;
}

#endif

SPlayerBagInfo::SPlayerBagInfo() : qwInstID(0), wItemID(0), byType(0), wCount(0), byBind(0) { }

SPlayerBagInfo::SPlayerBagInfo(UINT64 qwInstID_, UINT16 wItemID_, UINT8 byType_, UINT16 wCount_, UINT8 byBind_)
			: qwInstID(qwInstID_), wItemID(wItemID_), byType(byType_), wCount(wCount_), byBind(byBind_) { }

CInArchive& operator>>(CInArchive& src, SPlayerBagInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.qwInstID;
	src >> s.wItemID;
	src >> s.byType;
	src >> s.wCount;
	src >> s.byBind;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SPlayerBagInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.qwInstID;
	src << s.wItemID;
	src << s.byType;
	src << s.wCount;
	src << s.byBind;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SPlayerBagInfo& s)
{
	if(strcmp(rElement.Value(), "SPlayerBagInfo") != 0)
	{
		LOG_CRI << "rElement is not SPlayerBagInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for qwInstID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT64") != 0)
	{
		LOG_CRI << "pElemChild is not UINT64!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "qwInstID") != 0)
	{
		LOG_CRI << "Attribute: name is not qwInstID!";
		return false;
	}
	const char* pszVal_qwInstID = pElemChild->Attribute("value");
	if(pszVal_qwInstID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_qwInstID, s.qwInstID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wItemID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wItemID") != 0)
	{
		LOG_CRI << "Attribute: name is not wItemID!";
		return false;
	}
	const char* pszVal_wItemID = pElemChild->Attribute("value");
	if(pszVal_wItemID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wItemID, s.wItemID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byType is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byType") != 0)
	{
		LOG_CRI << "Attribute: name is not byType!";
		return false;
	}
	const char* pszVal_byType = pElemChild->Attribute("value");
	if(pszVal_byType == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byType, s.byType))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wCount is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wCount") != 0)
	{
		LOG_CRI << "Attribute: name is not wCount!";
		return false;
	}
	const char* pszVal_wCount = pElemChild->Attribute("value");
	if(pszVal_wCount == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wCount, s.wCount))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byBind is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byBind") != 0)
	{
		LOG_CRI << "Attribute: name is not byBind!";
		return false;
	}
	const char* pszVal_byBind = pElemChild->Attribute("value");
	if(pszVal_byBind == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byBind, s.byBind))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SPlayerBagInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SPlayerBagInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("玩家背包信息"));
	unique_ptr<TiXmlElement> pElem_qwInstID(new TiXmlElement("UINT64"));
	if(pElem_qwInstID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_qwInstID->SetAttribute("name", "qwInstID");
	pElem_qwInstID->SetAttribute("value", NumberToString(s.qwInstID).c_str());
	pElem_qwInstID->SetAttribute("comment", ToUTF8Ptr("物品唯一ID"));
	if(rElement.LinkEndChild(pElem_qwInstID.get()) != NULL)
		pElem_qwInstID.release();
	unique_ptr<TiXmlElement> pElem_wItemID(new TiXmlElement("UINT16"));
	if(pElem_wItemID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wItemID->SetAttribute("name", "wItemID");
	pElem_wItemID->SetAttribute("value", NumberToString(s.wItemID).c_str());
	pElem_wItemID->SetAttribute("comment", ToUTF8Ptr("物品模板"));
	if(rElement.LinkEndChild(pElem_wItemID.get()) != NULL)
		pElem_wItemID.release();
	unique_ptr<TiXmlElement> pElem_byType(new TiXmlElement("UINT8"));
	if(pElem_byType == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byType->SetAttribute("name", "byType");
	pElem_byType->SetAttribute("value", NumberToString(s.byType).c_str());
	pElem_byType->SetAttribute("comment", ToUTF8Ptr("1；背包，2：仓库"));
	if(rElement.LinkEndChild(pElem_byType.get()) != NULL)
		pElem_byType.release();
	unique_ptr<TiXmlElement> pElem_wCount(new TiXmlElement("UINT16"));
	if(pElem_wCount == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wCount->SetAttribute("name", "wCount");
	pElem_wCount->SetAttribute("value", NumberToString(s.wCount).c_str());
	pElem_wCount->SetAttribute("comment", ToUTF8Ptr("堆叠数"));
	if(rElement.LinkEndChild(pElem_wCount.get()) != NULL)
		pElem_wCount.release();
	unique_ptr<TiXmlElement> pElem_byBind(new TiXmlElement("UINT8"));
	if(pElem_byBind == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byBind->SetAttribute("name", "byBind");
	pElem_byBind->SetAttribute("value", NumberToString(s.byBind).c_str());
	pElem_byBind->SetAttribute("comment", ToUTF8Ptr("0：非绑定，1：绑定"));
	if(rElement.LinkEndChild(pElem_byBind.get()) != NULL)
		pElem_byBind.release();
	return true;
}

bool VectorFromXML(TiXmlElement& rElement, TVecPlayerBagInfo& vec)
{
	TiXmlElement* pElemMember = rElement.FirstChildElement();
	while(pElemMember != NULL)
	{
		SPlayerBagInfo s;
		if(!FromXML(*pElemMember, s))
		{
			LOG_CRI << "FromXML fails!";
			return false;
		}
		vec.emplace_back(move(s));
		pElemMember = pElemMember->NextSiblingElement();
	}
	return true;
}

bool VectorToXML(const TVecPlayerBagInfo& vec, TiXmlElement& rElement)
{
	for(size_t i = 0; i < vec.size(); ++i)
	{
		unique_ptr<TiXmlElement> pElemMember(new TiXmlElement("SPlayerBagInfo"));
		if(pElemMember == NULL)
		{
			LOG_CRI << "Allocate memory fails!";
			return false;
		}
		if(!ToXML(vec[i], *pElemMember))
		{
			LOG_CRI << "ToXML fails!";
			return false;
		}
		if(rElement.LinkEndChild(pElemMember.get()) != NULL)
			pElemMember.release();
	}
	return true;
}

#endif

SChestInfo::SChestInfo() : dwTime(0), byBig(0), byMid(0), bySmall(0), byPeroid(0), 
			wMapID(0) { }

SChestInfo::SChestInfo(UINT32 dwTime_, UINT8 byBig_, UINT8 byMid_, UINT8 bySmall_, UINT8 byPeroid_, 
			UINT16 wMapID_)
			: dwTime(dwTime_), byBig(byBig_), byMid(byMid_), bySmall(bySmall_), byPeroid(byPeroid_), 
			wMapID(wMapID_) { }

CInArchive& operator>>(CInArchive& src, SChestInfo& s)
{
	UINT16 len = 0;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PushEndPos(len);
	}
	src >> s.dwTime;
	src >> s.byBig;
	src >> s.byMid;
	src >> s.bySmall;
	src >> s.byPeroid;
	src >> s.wMapID;
	if(src.IsForDB())
	{
		CDBInArchive& iar = (CDBInArchive&)src;
		iar.PopEndPos();
	}
	return src;
}

COutArchive& operator<<(COutArchive& src, const SChestInfo& s)
{
	UINT16 len = 0;
	size_t pos = 0, start = 0;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		pos = oar.PreWriteLength(len);
		start = oar.GetLength();
	}
	src << s.dwTime;
	src << s.byBig;
	src << s.byMid;
	src << s.bySmall;
	src << s.byPeroid;
	src << s.wMapID;
	if(src.IsForDB())
	{
		CDBOutArchive& oar = (CDBOutArchive&)src;
		len = UINT16(oar.GetLength() - start);
		oar.WriteLength(pos, len);
	}
	return src;
}

#ifdef PROT_USE_XML

bool FromXML(TiXmlElement& rElement, SChestInfo& s)
{
	if(strcmp(rElement.Value(), "SChestInfo") != 0)
	{
		LOG_CRI << "rElement is not SChestInfo!";
		return false;
	}
	TiXmlElement* pElemChild = rElement.FirstChildElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for dwTime is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT32") != 0)
	{
		LOG_CRI << "pElemChild is not UINT32!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "dwTime") != 0)
	{
		LOG_CRI << "Attribute: name is not dwTime!";
		return false;
	}
	const char* pszVal_dwTime = pElemChild->Attribute("value");
	if(pszVal_dwTime == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_dwTime, s.dwTime))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byBig is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byBig") != 0)
	{
		LOG_CRI << "Attribute: name is not byBig!";
		return false;
	}
	const char* pszVal_byBig = pElemChild->Attribute("value");
	if(pszVal_byBig == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byBig, s.byBig))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byMid is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byMid") != 0)
	{
		LOG_CRI << "Attribute: name is not byMid!";
		return false;
	}
	const char* pszVal_byMid = pElemChild->Attribute("value");
	if(pszVal_byMid == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byMid, s.byMid))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for bySmall is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "bySmall") != 0)
	{
		LOG_CRI << "Attribute: name is not bySmall!";
		return false;
	}
	const char* pszVal_bySmall = pElemChild->Attribute("value");
	if(pszVal_bySmall == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_bySmall, s.bySmall))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for byPeroid is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT8") != 0)
	{
		LOG_CRI << "pElemChild is not UINT8!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "byPeroid") != 0)
	{
		LOG_CRI << "Attribute: name is not byPeroid!";
		return false;
	}
	const char* pszVal_byPeroid = pElemChild->Attribute("value");
	if(pszVal_byPeroid == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_byPeroid, s.byPeroid))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	pElemChild = pElemChild->NextSiblingElement();
	if(pElemChild == NULL)
	{
		LOG_CRI << "pElemChild for wMapID is empty!";
		return false;
	}
	if(strcmp(pElemChild->Value(), "UINT16") != 0)
	{
		LOG_CRI << "pElemChild is not UINT16!";
		return false;
	}
	if(strcmp(pElemChild->Attribute("name"), "wMapID") != 0)
	{
		LOG_CRI << "Attribute: name is not wMapID!";
		return false;
	}
	const char* pszVal_wMapID = pElemChild->Attribute("value");
	if(pszVal_wMapID == NULL)
	{
		LOG_CRI << "Attribute: value doesn't exist!";
		return false;
	}
	if(!String2Number(pszVal_wMapID, s.wMapID))
	{
		LOG_CRI << "Read attribute: value fails!";
		return false;
	}
	return true;
}

bool ToXML(const SChestInfo& s, TiXmlElement& rElement)
{
	rElement.SetValue("SChestInfo");
	rElement.SetAttribute("type", ToUTF8Ptr("天赐宝箱活动参数修改"));
	unique_ptr<TiXmlElement> pElem_dwTime(new TiXmlElement("UINT32"));
	if(pElem_dwTime == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_dwTime->SetAttribute("name", "dwTime");
	pElem_dwTime->SetAttribute("value", NumberToString(s.dwTime).c_str());
	pElem_dwTime->SetAttribute("comment", ToUTF8Ptr("开启时间"));
	if(rElement.LinkEndChild(pElem_dwTime.get()) != NULL)
		pElem_dwTime.release();
	unique_ptr<TiXmlElement> pElem_byBig(new TiXmlElement("UINT8"));
	if(pElem_byBig == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byBig->SetAttribute("name", "byBig");
	pElem_byBig->SetAttribute("value", NumberToString(s.byBig).c_str());
	pElem_byBig->SetAttribute("comment", ToUTF8Ptr("大宝箱个数"));
	if(rElement.LinkEndChild(pElem_byBig.get()) != NULL)
		pElem_byBig.release();
	unique_ptr<TiXmlElement> pElem_byMid(new TiXmlElement("UINT8"));
	if(pElem_byMid == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byMid->SetAttribute("name", "byMid");
	pElem_byMid->SetAttribute("value", NumberToString(s.byMid).c_str());
	pElem_byMid->SetAttribute("comment", ToUTF8Ptr("中宝箱个数"));
	if(rElement.LinkEndChild(pElem_byMid.get()) != NULL)
		pElem_byMid.release();
	unique_ptr<TiXmlElement> pElem_bySmall(new TiXmlElement("UINT8"));
	if(pElem_bySmall == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_bySmall->SetAttribute("name", "bySmall");
	pElem_bySmall->SetAttribute("value", NumberToString(s.bySmall).c_str());
	pElem_bySmall->SetAttribute("comment", ToUTF8Ptr("小宝箱个数"));
	if(rElement.LinkEndChild(pElem_bySmall.get()) != NULL)
		pElem_bySmall.release();
	unique_ptr<TiXmlElement> pElem_byPeroid(new TiXmlElement("UINT8"));
	if(pElem_byPeroid == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_byPeroid->SetAttribute("name", "byPeroid");
	pElem_byPeroid->SetAttribute("value", NumberToString(s.byPeroid).c_str());
	pElem_byPeroid->SetAttribute("comment", ToUTF8Ptr("活动持续时间"));
	if(rElement.LinkEndChild(pElem_byPeroid.get()) != NULL)
		pElem_byPeroid.release();
	unique_ptr<TiXmlElement> pElem_wMapID(new TiXmlElement("UINT16"));
	if(pElem_wMapID == NULL)
	{
		LOG_CRI << "Allocate memory fails!";
		return false;
	}
	pElem_wMapID->SetAttribute("name", "wMapID");
	pElem_wMapID->SetAttribute("value", NumberToString(s.wMapID).c_str());
	pElem_wMapID->SetAttribute("comment", ToUTF8Ptr("宝箱刷新地图"));
	if(rElement.LinkEndChild(pElem_wMapID.get()) != NULL)
		pElem_wMapID.release();
	return true;
}

#endif

} //namespace NPHPProt
