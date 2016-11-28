/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    ActivityIDProt.h
//  Purpose:      活动ID统一管理
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

namespace NActivityIDProt
{

/////////////////////以下为类型定义/////////////////////
//活动ID
enum EActivityID
{
	eActivityID_None = 0, //无
	eQQCoinActivity = 1, //汇灵盏
	eOpenActActivity = 2, //七日七天购买礼包
	eSevenConsumeAct = 3, //七日消费活动
	eDragonBallAct = 4, //七龙珠活动
	eActivityID_Max //无
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EActivityID);
bool EnumStrToVal(const char*, EActivityID&);
#endif //PROT_USE_XML


} //namespace NActivityIDProt
