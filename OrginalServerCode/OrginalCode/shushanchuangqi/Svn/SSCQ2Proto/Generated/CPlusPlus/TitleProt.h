/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    TitleProt.h
//  Purpose:      称号协议
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
#include "RoleInfoDefine.h"

namespace NTitleProt
{

/////////////////////以下为类型定义/////////////////////
//请求的结果
enum ETitleResult
{
	eTitleSucceed, //成功
	eTitleVIPLevel, //御剑等级不足
	eTitleNoHas, //该称号没有获得
	eTitleErrOther //其它错误
};

#ifdef PROT_USE_XML
const char* EnumValToStr(ETitleResult);
bool EnumStrToVal(const char*, ETitleResult&);
#endif //PROT_USE_XML


} //namespace NTitleProt
