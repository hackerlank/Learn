/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    MoneyTree.h
//  Purpose:      摇钱树协议
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

namespace NMoneyTreeProt
{

/////////////////////以下为类型定义/////////////////////
//操作结果
enum EMoneyTreeResult
{
	Succeed, //成功
	Error //失败
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EMoneyTreeResult);
bool EnumStrToVal(const char*, EMoneyTreeResult&);
#endif //PROT_USE_XML


} //namespace NMoneyTreeProt
