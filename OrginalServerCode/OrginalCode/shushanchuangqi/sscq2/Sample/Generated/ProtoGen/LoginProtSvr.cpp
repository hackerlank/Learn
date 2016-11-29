/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    LoginProt.cpp
//  Purpose:      登陆LoginServer的协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "LoginProtSvr.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NLoginProt
{

CLoginProtSvr::THandleFunc CLoginProtSvr::_HandleFuncs[] =
{
	&CLoginProtSvr::_DoRecv_LoginReq, //FuncID: 1
};

bool CLoginProtSvr::HandleMessage(const char* pBuf, UINT32 dwLen)
{
	if(pBuf == NULL || dwLen == 0)
		return false;
	INT8 byFuncID = pBuf[0];
	if(byFuncID == 0 || byFuncID > (INT8)ARRAYSIZE(_HandleFuncs))
	{
#ifdef _DEBUG
		LOG_CRI << "byFuncID is invalid: " << byFuncID;
#endif
		return false;
	}
	pBuf += sizeof(INT8);
	dwLen -= sizeof(INT8);
	if(byFuncID > 0)
	{
		--byFuncID;
		if(_HandleFuncs[static_cast<UINT8>(byFuncID)] != NULL)
			return (this->*_HandleFuncs[static_cast<UINT8>(byFuncID)])(pBuf, dwLen);
	}
	return true;
}

//发送：登陆结果返回
bool CLoginProtSvr::Send_LoginAck(
	ELoginResult eLoginResult, //请求登录结果
	UINT64 qwRoleId, //角色ID
	const std::string& strGateIP, //GateServer的IP
	UINT16 wGatePort, //GateServer端口
	UINT32 dwCryptoCode //登录验证码
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eLoginResult << qwRoleId << strGateIP << wGatePort << dwCryptoCode;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 1, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CLoginProtSvr::SendClt_LoginAck(const UINT64* pUsrID_, UINT16 wCnt_,
	ELoginResult eLoginResult, //请求登录结果
	UINT64 qwRoleId, //角色ID
	const std::string& strGateIP, //GateServer的IP
	UINT16 wGatePort, //GateServer端口
	UINT32 dwCryptoCode //登录验证码
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eLoginResult << qwRoleId << strGateIP << wGatePort << dwCryptoCode;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 1, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CLoginProtSvr::BuildPkg_LoginAck(
	ELoginResult eLoginResult, //请求登录结果
	UINT64 qwRoleId, //角色ID
	const std::string& strGateIP, //GateServer的IP
	UINT16 wGatePort, //GateServer端口
	UINT32 dwCryptoCode //登录验证码
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eLoginResult << qwRoleId << strGateIP << wGatePort << dwCryptoCode;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 1, Function: 1";
		_strPkg.clear();
	}
	return _strPkg;
}

bool CLoginProtSvr::_DoRecv_LoginReq(const char* pBuf_, UINT32 dwLen_)
{
	UINT64 qwUsrID = 0;
	UINT16 usGroupID = 0;
	UINT32 dwVersion = 0;
	std::string strPassword;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> qwUsrID >> usGroupID >> dwVersion >> strPassword;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 1, Function: 1";
		return false;
	}
	OnRecv_LoginReq(qwUsrID, usGroupID, dwVersion, strPassword);
	return true;
}

} //namespace NLoginProt
