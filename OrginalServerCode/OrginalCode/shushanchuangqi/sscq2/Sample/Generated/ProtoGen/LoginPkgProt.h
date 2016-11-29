/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    LoginPkgProt.h
//  Purpose:      累计登入礼包协议
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

namespace NLoginPkgProt
{

/////////////////////以下为类型定义/////////////////////
//操作结果
enum EResultInLoginProt
{
	ePkgError, //错误
	ePkgGain, //已经领取
	ePkgFull, //背包已满
	ePkgSuccess //成功
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EResultInLoginProt);
bool EnumStrToVal(const char*, EResultInLoginProt&);
#endif //PROT_USE_XML


} //namespace NLoginPkgProt
