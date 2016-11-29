/************************************************************************
//  工具自动生成的客户端协议代码(UTF-8 With BOM)
//  File Name:    Gate2CenterComm.cpp
//  Purpose:      GateServer到CenterServer的通信协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "Gate2CenterCommClt.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NGate2CenterComm
{

CGate2CenterCommClt::THandleFunc CGate2CenterCommClt::_HandleFuncs[] =
{
	&CGate2CenterCommClt::_DoRecv_UserWantLoginNtf, //FuncID: 1
	&CGate2CenterCommClt::_DoRecv_KickUserOffLine, //FuncID: 2
	&CGate2CenterCommClt::_DoRecv_ReplaceUser, //FuncID: 3
};

bool CGate2CenterCommClt::HandleMessage(const char* pBuf, UINT32 dwLen)
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
bool CGate2CenterCommClt::Send_KeepAlive(
	UINT32 dwUsrCnt //玩家数量
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << dwUsrCnt;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 6, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGate2CenterCommClt::SendSvr_KeepAlive(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT32 dwUsrCnt //玩家数量
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << dwUsrCnt;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 6, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGate2CenterCommClt::BuildPkg_KeepAlive(
	UINT32 dwUsrCnt //玩家数量
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << dwUsrCnt;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 6, Function: 1";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：玩家上线通知
bool CGate2CenterCommClt::Send_UserLoginNtf(
	UINT64 qwUsrID, //帐号ID
	const std::string& strIPAddr //IP地址
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << strIPAddr;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 6, Function: 2";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGate2CenterCommClt::SendSvr_UserLoginNtf(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwUsrID, //帐号ID
	const std::string& strIPAddr //IP地址
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << strIPAddr;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 6, Function: 2";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGate2CenterCommClt::BuildPkg_UserLoginNtf(
	UINT64 qwUsrID, //帐号ID
	const std::string& strIPAddr //IP地址
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << strIPAddr;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 6, Function: 2";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：玩家下线通知
bool CGate2CenterCommClt::Send_UserLogoutNtf(
	UINT64 qwUsrID, //帐号ID
	NServerCommon::ELeaveType eLeaveType //下线类型
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << (UINT8&)eLeaveType;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 6, Function: 3";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGate2CenterCommClt::SendSvr_UserLogoutNtf(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwUsrID, //帐号ID
	NServerCommon::ELeaveType eLeaveType //下线类型
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << (UINT8&)eLeaveType;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 6, Function: 3";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGate2CenterCommClt::BuildPkg_UserLogoutNtf(
	UINT64 qwUsrID, //帐号ID
	NServerCommon::ELeaveType eLeaveType //下线类型
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << (UINT8&)eLeaveType;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 6, Function: 3";
		_strPkg.clear();
	}
	return _strPkg;
}

bool CGate2CenterCommClt::_DoRecv_UserWantLoginNtf(const char* pBuf_, UINT32 dwLen_)
{
	UINT64 qwUsrID = 0;
	UINT32 dwCryptoCode = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> qwUsrID >> dwCryptoCode;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 6, Function: 1";
		return false;
	}
	OnRecv_UserWantLoginNtf(qwUsrID, dwCryptoCode);
	return true;
}

bool CGate2CenterCommClt::_DoRecv_KickUserOffLine(const char* pBuf_, UINT32 dwLen_)
{
	UINT64 qwUsrID = 0;
	NServerCommon::ELeaveType eLeaveType = (NServerCommon::ELeaveType)0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> qwUsrID >> (UINT8&)eLeaveType;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 6, Function: 2";
		return false;
	}
	OnRecv_KickUserOffLine(qwUsrID, eLeaveType);
	return true;
}

CGate2CenterCommClt::SReplaceUserAck::SReplaceUserAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID) { }

void CGate2CenterCommClt::SReplaceUserAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -1;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 6, Function: 3";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CGate2CenterCommClt::_DoRecv_ReplaceUser(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT64 qwUsrID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> qwUsrID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 6, Function: 3";
		return false;
	}
	shared_func<SReplaceUserAck> fnAck_(new SReplaceUserAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_ReplaceUser(qwUsrID, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

} //namespace NGate2CenterComm
