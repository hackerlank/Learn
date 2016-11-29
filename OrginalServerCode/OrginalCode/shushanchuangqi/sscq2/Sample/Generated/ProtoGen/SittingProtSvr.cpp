/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    SittingProt.cpp
//  Purpose:      打坐协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "SittingProtSvr.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NSittingProt
{

CSittingProtSvr::THandleFunc CSittingProtSvr::_HandleFuncs[] =
{
	&CSittingProtSvr::_DoRecv_DoSittingTogether, //FuncID: 1
	&CSittingProtSvr::_DoRecv_CancelSitting, //FuncID: 2
};

bool CSittingProtSvr::HandleMessage(const char* pBuf, UINT32 dwLen)
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

//发送：玩家打坐结算
bool CSittingProtSvr::Send_CancelSittingOffLine(
	UINT8 byType, //0,表示单修，1表示双修
	const NItemProt::TVecResource& vecRes, //获得的资源
	UINT32 dwSittingTimer //开始时间
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << byType << vecRes << dwSittingTimer;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 55, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CSittingProtSvr::SendClt_CancelSittingOffLine(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT8 byType, //0,表示单修，1表示双修
	const NItemProt::TVecResource& vecRes, //获得的资源
	UINT32 dwSittingTimer //开始时间
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << byType << vecRes << dwSittingTimer;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 55, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CSittingProtSvr::BuildPkg_CancelSittingOffLine(
	UINT8 byType, //0,表示单修，1表示双修
	const NItemProt::TVecResource& vecRes, //获得的资源
	UINT32 dwSittingTimer //开始时间
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << byType << vecRes << dwSittingTimer;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 55, Function: 1";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：打坐状态变化
bool CSittingProtSvr::Send_UpdateSitting(
	UINT8 byState, //0,表示结束打坐，1 ，开始打坐
	const NMapProt::TVecPlayerAppear& vecOtherApear, //空表示单修，非空表示双修
	UINT32 dwSittingTimer //开始时间
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << byState << vecOtherApear << dwSittingTimer;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 55, Function: 2";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CSittingProtSvr::SendClt_UpdateSitting(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT8 byState, //0,表示结束打坐，1 ，开始打坐
	const NMapProt::TVecPlayerAppear& vecOtherApear, //空表示单修，非空表示双修
	UINT32 dwSittingTimer //开始时间
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << byState << vecOtherApear << dwSittingTimer;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 55, Function: 2";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CSittingProtSvr::BuildPkg_UpdateSitting(
	UINT8 byState, //0,表示结束打坐，1 ，开始打坐
	const NMapProt::TVecPlayerAppear& vecOtherApear, //空表示单修，非空表示双修
	UINT32 dwSittingTimer //开始时间
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << byState << vecOtherApear << dwSittingTimer;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 55, Function: 2";
		_strPkg.clear();
	}
	return _strPkg;
}

CSittingProtSvr::SDoSittingTogetherAck::SDoSittingTogetherAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((ESittingResult)0) { }

void CSittingProtSvr::SDoSittingTogetherAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -1;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 55, Function: 1";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CSittingProtSvr::_DoRecv_DoSittingTogether(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT64 qwOtherID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> qwOtherID;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 55, Function: 1";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SDoSittingTogetherAck> fnAck_(new SDoSittingTogetherAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_DoSittingTogether(qwOtherID, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

bool CSittingProtSvr::_DoRecv_CancelSitting(const char* pBuf_, UINT32 dwLen_)
{
	OnRecv_CancelSitting();
	return true;
}

} //namespace NSittingProt
