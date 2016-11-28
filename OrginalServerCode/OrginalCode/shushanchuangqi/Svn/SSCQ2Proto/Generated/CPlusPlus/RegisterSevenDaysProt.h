/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    RegisterSevenDays.h
//  Purpose:      注册七天目标协议
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

namespace NRegisterSevenDaysProt
{

/////////////////////以下为类型定义/////////////////////
//操作结果
enum ERegisterSevenDaysResult
{
	eSucceed, //成功
	eFailed //失败
};

#ifdef PROT_USE_XML
const char* EnumValToStr(ERegisterSevenDaysResult);
bool EnumStrToVal(const char*, ERegisterSevenDaysResult&);
#endif //PROT_USE_XML

//购买状态
enum EBuyStatus
{
	eNoBuy, //不能购买
	eCanBuy, //能够购买
	eAlreadyBuy //已经购买
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EBuyStatus);
bool EnumStrToVal(const char*, EBuyStatus&);
#endif //PROT_USE_XML


} //namespace NRegisterSevenDaysProt
