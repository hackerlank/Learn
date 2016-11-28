/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    SignProt.h
//  Purpose:      签到协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#pragma once
#include <string>
#include <memory>
#include "ServerDefine.h"
#include "Archive.h"
#ifdef PROT_USE_XML
#include "tinyxml.h"
#endif

namespace NSignProt
{

/////////////////////以下为类型定义/////////////////////
//请求的结果
enum ESignResult
{
	eSignSucceed, //成功
	eSignHasDone, //今日已签到
	eSignResignDone, //补签日已签到
	eSignResignErrDate, //补签日期错误
	eSignResignOverTimes, //补签次数用完
	eSignAwardHasGet, //该签到奖励已领
	eSignAwardIdErr, //该签到奖励id不正确
	eSignAwardLowDays, //该签到奖励的签到天数不足
	eSignAwardPacketFull, //签到奖励包裹放不下
	eSignVIP, //提醒开通御剑
	eSignOther //其它错误
};

#ifdef PROT_USE_XML
const char* EnumValToStr(ESignResult);
bool EnumStrToVal(const char*, ESignResult&);
#endif //PROT_USE_XML


} //namespace NSignProt
