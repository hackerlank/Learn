/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    LoginProt.h
//  Purpose:      登陆LoginServer的协议
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

namespace NLoginProt
{

/////////////////////以下为类型定义/////////////////////
//登陆结果
enum ELoginResult
{
	eLoginSucceed, //登陆成功
	eVersionLess, //客户端版本号低于服务器
	eNotActivated, //帐号未激活此区服
	eAccountInvalid, //帐号错误
	ePasswordInvalid, //密码错误
	eAccPwdErr, //账号不存在或密码错误
	eUsrStateErr, //帐号状态异常
	eAccountFreeze, //帐号冻结
	eAccountLogin, //帐号正在登陆中
	eReqOverTime, //请求超时
	eReqTooFreqent, //请求太频繁
	eServerFull, //服务器已满
	eRoleOnline, //已有角色在线
	eKickWait, //踢帐号等待
	eLeaveWait, //下线等待
	eEnterTooFreqent, //请求太频繁
	eLoginServerErr, //服务器内部错误
	eServerInitErr, //服务器未启动完毕
	eLoginOtherErr //系统错误
};

#ifdef PROT_USE_XML
const char* EnumValToStr(ELoginResult);
bool EnumStrToVal(const char*, ELoginResult&);
#endif //PROT_USE_XML
const char* GetDescription(ELoginResult);


} //namespace NLoginProt
