/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    Login2CenterComm.h
//  Purpose:      LoginServer到CenterServer的基本通信协议
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

namespace NLogin2CenterComm
{

/////////////////////以下为类型定义/////////////////////
//登陆请求的结果
enum EReqResult
{
	eReqSucceed, //登陆请求成功
	eReqFull, //玩家数量达到上限
	eReqOnline, //已有角色在线
	eReqKickWait, //踢帐号等待
	eReqLeaveWait, //下线等待
	eReqTooFreqent, //请求太频繁
	eReqNotInited, //服务器未完全启动
	eReqOtherErr //其它错误
};

#ifdef PROT_USE_XML
const char* EnumValToStr(EReqResult);
bool EnumStrToVal(const char*, EReqResult&);
#endif //PROT_USE_XML


} //namespace NLogin2CenterComm
