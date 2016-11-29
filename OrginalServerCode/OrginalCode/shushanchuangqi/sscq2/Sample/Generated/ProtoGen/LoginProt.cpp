/************************************************************************
//  工具自动生成的协议类型定义代码(UTF-8 With BOM)
//  File Name:    LoginProt.cpp
//  Purpose:      登陆LoginServer的协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "LoginProt.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NLoginProt
{

#ifdef PROT_USE_XML

const char* EnumValToStr(ELoginResult e)
{
	switch(e)
	{
	case eLoginSucceed:
		return "eLoginSucceed";
	case eVersionLess:
		return "eVersionLess";
	case eNotActivated:
		return "eNotActivated";
	case eAccountInvalid:
		return "eAccountInvalid";
	case ePasswordInvalid:
		return "ePasswordInvalid";
	case eAccPwdErr:
		return "eAccPwdErr";
	case eUsrStateErr:
		return "eUsrStateErr";
	case eAccountFreeze:
		return "eAccountFreeze";
	case eAccountLogin:
		return "eAccountLogin";
	case eReqOverTime:
		return "eReqOverTime";
	case eReqTooFreqent:
		return "eReqTooFreqent";
	case eServerFull:
		return "eServerFull";
	case eRoleOnline:
		return "eRoleOnline";
	case eKickWait:
		return "eKickWait";
	case eLeaveWait:
		return "eLeaveWait";
	case eEnterTooFreqent:
		return "eEnterTooFreqent";
	case eLoginServerErr:
		return "eLoginServerErr";
	case eServerInitErr:
		return "eServerInitErr";
	case eLoginOtherErr:
		return "eLoginOtherErr";
	default:
		return NULL;
	}
}

bool EnumStrToVal(const char* pszEnumStr, ELoginResult& e)
{
	if(pszEnumStr == NULL)
	{
		LOG_CRI << "pszEnumStr is NULL!";
		return false;
	}
	static map<string, ELoginResult> mapStr2Val;
	if(mapStr2Val.empty())
	{
		mapStr2Val.insert(make_pair("eLoginSucceed", eLoginSucceed));
		mapStr2Val.insert(make_pair("eVersionLess", eVersionLess));
		mapStr2Val.insert(make_pair("eNotActivated", eNotActivated));
		mapStr2Val.insert(make_pair("eAccountInvalid", eAccountInvalid));
		mapStr2Val.insert(make_pair("ePasswordInvalid", ePasswordInvalid));
		mapStr2Val.insert(make_pair("eAccPwdErr", eAccPwdErr));
		mapStr2Val.insert(make_pair("eUsrStateErr", eUsrStateErr));
		mapStr2Val.insert(make_pair("eAccountFreeze", eAccountFreeze));
		mapStr2Val.insert(make_pair("eAccountLogin", eAccountLogin));
		mapStr2Val.insert(make_pair("eReqOverTime", eReqOverTime));
		mapStr2Val.insert(make_pair("eReqTooFreqent", eReqTooFreqent));
		mapStr2Val.insert(make_pair("eServerFull", eServerFull));
		mapStr2Val.insert(make_pair("eRoleOnline", eRoleOnline));
		mapStr2Val.insert(make_pair("eKickWait", eKickWait));
		mapStr2Val.insert(make_pair("eLeaveWait", eLeaveWait));
		mapStr2Val.insert(make_pair("eEnterTooFreqent", eEnterTooFreqent));
		mapStr2Val.insert(make_pair("eLoginServerErr", eLoginServerErr));
		mapStr2Val.insert(make_pair("eServerInitErr", eServerInitErr));
		mapStr2Val.insert(make_pair("eLoginOtherErr", eLoginOtherErr));
	}
	auto it = mapStr2Val.find(pszEnumStr);
	if(it == mapStr2Val.end())
	{
		LOG_CRI << "Unrecognized enum string: " << pszEnumStr;
		return false;
	}
	e = it->second;
	return true;
}

#endif //PROT_USE_XML

const char* GetDescription(ELoginResult e)
{
	switch(e)
	{
	case eLoginSucceed:
		return "登陆成功";
	case eVersionLess:
		return "客户端版本号低于服务器";
	case eNotActivated:
		return "帐号未激活此区服";
	case eAccountInvalid:
		return "帐号错误";
	case ePasswordInvalid:
		return "密码错误";
	case eAccPwdErr:
		return "账号不存在或密码错误";
	case eUsrStateErr:
		return "帐号状态异常";
	case eAccountFreeze:
		return "帐号冻结";
	case eAccountLogin:
		return "帐号正在登陆中";
	case eReqOverTime:
		return "请求超时";
	case eReqTooFreqent:
		return "请求太频繁";
	case eServerFull:
		return "服务器已满";
	case eRoleOnline:
		return "已有角色在线";
	case eKickWait:
		return "踢帐号等待";
	case eLeaveWait:
		return "下线等待";
	case eEnterTooFreqent:
		return "请求太频繁";
	case eLoginServerErr:
		return "服务器内部错误";
	case eServerInitErr:
		return "服务器未启动完毕";
	case eLoginOtherErr:
		return "系统错误";
	default:
		return "未知错误";
	}
}

} //namespace NLoginProt
