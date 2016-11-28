/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    SittingProt.h
//  Purpose:      打坐协议
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
#include "ItemProt.h"
#include "MapProt.h"

namespace NSittingProt
{

/////////////////////以下为类型定义/////////////////////
//请求的结果
enum ESittingResult
{
	eSittingSucceed, //成功
	eSittingTogether, //没有找到双修的人
	eHasSitting, //您已经在打坐
	eNotInCity, //主城才能打坐
	eLevelLow, //等级不足
	eSittingErrOther //其它错误
};

#ifdef PROT_USE_XML
const char* EnumValToStr(ESittingResult);
bool EnumStrToVal(const char*, ESittingResult&);
#endif //PROT_USE_XML


} //namespace NSittingProt
