/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    ProtoVersion.h
//  Purpose:      协议版本号
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

namespace NProtoVersion
{

/////////////////////以下为类型定义/////////////////////
//协议版本
enum EProtoVer
{
	EPROTOVERSION = 14080801 //版本号，年2位(14),月2位(07),日2位，序号2位
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EProtoVer);
bool EnumStrToVal(const char*, EProtoVer&);
#endif //PROT_USE_XML


} //namespace NProtoVersion
