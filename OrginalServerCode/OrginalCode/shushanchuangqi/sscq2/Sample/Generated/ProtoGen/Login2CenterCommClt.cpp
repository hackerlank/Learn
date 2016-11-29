/************************************************************************
//  工具自动生成的客户端协议代码(UTF-8 With BOM)
//  File Name:    Login2CenterComm.cpp
//  Purpose:      LoginServer到CenterServer的基本通信协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "Login2CenterCommClt.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NLogin2CenterComm
{

CLogin2CenterCommClt::THandleFunc CLogin2CenterCommClt::_HandleFuncs[] =
{
	&CLogin2CenterCommClt::_DoRecv_UserLoginAck, //FuncID: 1
};

bool CLogin2CenterCommClt::HandleMessage(const char* pBuf, UINT32 dwLen)
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

//发送：心跳
bool CLogin2CenterCommClt::Send_KeepAlive(
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 2, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CLogin2CenterCommClt::SendSvr_KeepAlive(const UINT32* pSvrID_, UINT8 byCnt_
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 2, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CLogin2CenterCommClt::BuildPkg_KeepAlive(
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 2, Function: 1";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：玩家请求进入服务器
bool CLogin2CenterCommClt::Send_UserLoginReq(
	UINT64 qwUsrID, //帐号ID
	UINT32 dwSessionID, //会话ID
	UINT8 byAddrType //地址类型
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << dwSessionID << byAddrType;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 2, Function: 2";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CLogin2CenterCommClt::SendSvr_UserLoginReq(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwUsrID, //帐号ID
	UINT32 dwSessionID, //会话ID
	UINT8 byAddrType //地址类型
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << dwSessionID << byAddrType;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 2, Function: 2";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CLogin2CenterCommClt::BuildPkg_UserLoginReq(
	UINT64 qwUsrID, //帐号ID
	UINT32 dwSessionID, //会话ID
	UINT8 byAddrType //地址类型
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << dwSessionID << byAddrType;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 2, Function: 2";
		_strPkg.clear();
	}
	return _strPkg;
}

bool CLogin2CenterCommClt::_DoRecv_UserLoginAck(const char* pBuf_, UINT32 dwLen_)
{
	EReqResult eResult = (EReqResult)0;
	UINT64 qwUsrID = 0;
	UINT32 dwSessionID = 0;
	std::string strGateAddr;
	UINT16 wGatePort = 0;
	UINT32 dwCryptoCode = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> (UINT8&)eResult >> qwUsrID >> dwSessionID >> strGateAddr >> wGatePort >> dwCryptoCode;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 2, Function: 1";
		return false;
	}
	OnRecv_UserLoginAck(eResult, qwUsrID, dwSessionID, strGateAddr, wGatePort, dwCryptoCode);
	return true;
}

} //namespace NLogin2CenterComm
