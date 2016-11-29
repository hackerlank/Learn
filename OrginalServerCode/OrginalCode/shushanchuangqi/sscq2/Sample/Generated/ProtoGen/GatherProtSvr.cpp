/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    GatherProt.cpp
//  Purpose:      采集协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "GatherProtSvr.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NGatherProt
{

CGatherProtSvr::THandleFunc CGatherProtSvr::_HandleFuncs[] =
{
	&CGatherProtSvr::_DoRecv_GatherReq, //FuncID: 1
	&CGatherProtSvr::_DoRecv_CancelGather, //FuncID: 2
	&CGatherProtSvr::_DoRecv_GetGatherInfo, //FuncID: 3
};

bool CGatherProtSvr::HandleMessage(const char* pBuf, UINT32 dwLen)
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

//发送：采集结束通知
bool CGatherProtSvr::Send_GatherEndNotify(
	EGatherResult eResult //服务器返回结果
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 60, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGatherProtSvr::SendClt_GatherEndNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	EGatherResult eResult //服务器返回结果
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 60, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGatherProtSvr::BuildPkg_GatherEndNotify(
	EGatherResult eResult //服务器返回结果
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 60, Function: 1";
		_strPkg.clear();
	}
	return _strPkg;
}

CGatherProtSvr::SGatherReqAck::SGatherReqAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((EGatherResult)0), dwGatherTimer(0) { }

void CGatherProtSvr::SGatherReqAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -1;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eResult << dwGatherTimer;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 60, Function: 1";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CGatherProtSvr::_DoRecv_GatherReq(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT32 dwGatherId = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> dwGatherId;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 60, Function: 1";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SGatherReqAck> fnAck_(new SGatherReqAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_GatherReq(dwGatherId, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CGatherProtSvr::SCancelGatherAck::SCancelGatherAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((EGatherResult)0) { }

void CGatherProtSvr::SCancelGatherAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -2;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 60, Function: 2";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CGatherProtSvr::_DoRecv_CancelGather(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 60, Function: 2";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SCancelGatherAck> fnAck_(new SCancelGatherAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_CancelGather(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CGatherProtSvr::SGetGatherInfoAck::SGetGatherInfoAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			dwGtatherId(0), dwReserverTimer(0) { }

void CGatherProtSvr::SGetGatherInfoAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -3;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << dwGtatherId << dwReserverTimer;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 60, Function: 3";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CGatherProtSvr::_DoRecv_GetGatherInfo(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 60, Function: 3";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SGetGatherInfoAck> fnAck_(new SGetGatherInfoAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetGatherInfo(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

} //namespace NGatherProt
