/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    CoinProt.h
//  Purpose:      888礼券协议
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
#include "ProtoCommon.h"

namespace NCoinProt
{

/////////////////////以下为类型定义/////////////////////
//操作结果
enum EResultInCoinProt
{
	eCoinError, //错误
	eCoinGain, //已经领取
	eCoinSuccess //成功
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EResultInCoinProt);
bool EnumStrToVal(const char*, EResultInCoinProt&);
#endif //PROT_USE_XML


} //namespace NCoinProt
