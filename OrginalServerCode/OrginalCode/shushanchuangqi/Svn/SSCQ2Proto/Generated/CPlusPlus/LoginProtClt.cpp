/************************************************************************
//  工具自动生成的客户端协议代码(UTF-8 With BOM)
//  File Name:    LoginProt.cpp
//  Purpose:      登陆LoginServer的协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "LoginProtClt.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NLoginProt
{

CLoginProtClt::THandleFunc CLoginProtClt::_HandleFuncs[] =
{
	&CLoginProtClt::_DoRecv_LoginAck, //FuncID: 1
};

bool CLoginProtClt::HandleMessage(const char* pBuf, UINT32 dwLen)
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

//发送：登陆请求
bool CLoginProtClt::Send_LoginReq(
	UINT64 qwUsrID, //帐号ID
	UINT16 usGroupID, //区号
	UINT32 dwVersion, //版本号
	const std::string& strPassword //验证key
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << usGroupID << dwVersion << strPassword;
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

bool CLoginProtClt::SendSvr_LoginReq(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwUsrID, //帐号ID
	UINT16 usGroupID, //区号
	UINT32 dwVersion, //版本号
	const std::string& strPassword //验证key
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << usGroupID << dwVersion << strPassword;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 1, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CLoginProtClt::BuildPkg_LoginReq(
	UINT64 qwUsrID, //帐号ID
	UINT16 usGroupID, //区号
	UINT32 dwVersion, //版本号
	const std::string& strPassword //验证key
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << usGroupID << dwVersion << strPassword;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 1, Function: 1";
		_strPkg.clear();
	}
	return _strPkg;
}

bool CLoginProtClt::_DoRecv_LoginAck(const char* pBuf_, UINT32 dwLen_)
{
	ELoginResult eLoginResult = (ELoginResult)0;
	UINT64 qwRoleId = 0;
	std::string strGateIP;
	UINT16 wGatePort = 0;
	UINT32 dwCryptoCode = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> (UINT8&)eLoginResult >> qwRoleId >> strGateIP >> wGatePort >> dwCryptoCode;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 1, Function: 1";
		return false;
	}
	OnRecv_LoginAck(eLoginResult, qwRoleId, strGateIP, wGatePort, dwCryptoCode);
	return true;
}

} //namespace NLoginProt
