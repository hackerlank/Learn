/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    ChatProt.h
//  Purpose:      聊天协议
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
#include "GlobalChatProt.h"
#include "ProtoCommon.h"
#include "RoleInfoDefine.h"

namespace NChatProt
{

/////////////////////以下为类型定义/////////////////////
//聊天结果提示
enum EChatResult
{
	eChatSucceed, //成功
	eChatNotExist, //展示道具不存在
	eChatErrStore, //容器错误
	eChatErrOther //其他错误
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EChatResult);
bool EnumStrToVal(const char*, EChatResult&);
#endif //PROT_USE_XML

//气泡操作失败
enum EBubbleResult
{
	eBRSuccess, //气泡操作成功
	eBRFailed //气泡操作失败
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EBubbleResult);
bool EnumStrToVal(const char*, EBubbleResult&);
#endif //PROT_USE_XML


} //namespace NChatProt
