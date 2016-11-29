/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    WonderActivityProt.cpp
//  Purpose:      精彩活动
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "WonderActivityProtSvr.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NWonderActivityProt
{

CWonderActivityProtSvr::THandleFunc CWonderActivityProtSvr::_HandleFuncs[] =
{
	&CWonderActivityProtSvr::_DoRecv_GetConfigTime, //FuncID: 1
	&CWonderActivityProtSvr::_DoRecv_GetAllPrize, //FuncID: 2
	&CWonderActivityProtSvr::_DoRecv_GetActList, //FuncID: 3
	&CWonderActivityProtSvr::_DoRecv_TakePrize, //FuncID: 4
	&CWonderActivityProtSvr::_DoRecv_GetRoleActInfo, //FuncID: 5
	&CWonderActivityProtSvr::_DoRecv_GetRoleAllState, //FuncID: 6
	&CWonderActivityProtSvr::_DoRecv_GetDragonBallAct, //FuncID: 7
	&CWonderActivityProtSvr::_DoRecv_GetSevenConsumeAct, //FuncID: 8
	&CWonderActivityProtSvr::_DoRecv_GetQQCoinAct, //FuncID: 9
	&CWonderActivityProtSvr::_DoRecv_ExChange, //FuncID: 10
};

bool CWonderActivityProtSvr::HandleMessage(const char* pBuf, UINT32 dwLen)
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

//发送：领奖状态通知
bool CWonderActivityProtSvr::Send_SendTakePrizeNtf(
	UINT16 wActID, //活动ID
	UINT32 wCond, //条件ID
	EGainResult eRet //状态
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << wActID << wCond << (UINT8&)eRet;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 199, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CWonderActivityProtSvr::SendClt_SendTakePrizeNtf(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT16 wActID, //活动ID
	UINT32 wCond, //条件ID
	EGainResult eRet //状态
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << wActID << wCond << (UINT8&)eRet;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 199, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CWonderActivityProtSvr::BuildPkg_SendTakePrizeNtf(
	UINT16 wActID, //活动ID
	UINT32 wCond, //条件ID
	EGainResult eRet //状态
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << wActID << wCond << (UINT8&)eRet;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 199, Function: 1";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：达到条件通知
bool CWonderActivityProtSvr::Send_SendReachCondNtf(
	UINT16 wActID, //活动ID
	UINT32 wCond //条件ID
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << wActID << wCond;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 199, Function: 2";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CWonderActivityProtSvr::SendClt_SendReachCondNtf(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT16 wActID, //活动ID
	UINT32 wCond //条件ID
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << wActID << wCond;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 199, Function: 2";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CWonderActivityProtSvr::BuildPkg_SendReachCondNtf(
	UINT16 wActID, //活动ID
	UINT32 wCond //条件ID
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << wActID << wCond;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 199, Function: 2";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：更新七星龙珠活动信息
bool CWonderActivityProtSvr::Send_UpdateDragonBallAct(
	const SDragonBallAct& oDragonBallAct //七星龙珠活动信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << oDragonBallAct;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 199, Function: 3";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CWonderActivityProtSvr::SendClt_UpdateDragonBallAct(const UINT64* pUsrID_, UINT16 wCnt_,
	const SDragonBallAct& oDragonBallAct //七星龙珠活动信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << oDragonBallAct;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 199, Function: 3";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CWonderActivityProtSvr::BuildPkg_UpdateDragonBallAct(
	const SDragonBallAct& oDragonBallAct //七星龙珠活动信息
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << oDragonBallAct;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 199, Function: 3";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：更新七日消费活动信息
bool CWonderActivityProtSvr::Send_UpdateSevenConsumeAct(
	const SSevenConsumeAct& oSevenConsumeAct //七日消费活动信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << oSevenConsumeAct;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 199, Function: 4";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CWonderActivityProtSvr::SendClt_UpdateSevenConsumeAct(const UINT64* pUsrID_, UINT16 wCnt_,
	const SSevenConsumeAct& oSevenConsumeAct //七日消费活动信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << oSevenConsumeAct;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 199, Function: 4";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CWonderActivityProtSvr::BuildPkg_UpdateSevenConsumeAct(
	const SSevenConsumeAct& oSevenConsumeAct //七日消费活动信息
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << oSevenConsumeAct;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 199, Function: 4";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：同步QQ养成信息
bool CWonderActivityProtSvr::Send_SyncQQCoinInfo(
	const SQQCoinActInfo& oQQCoinInfo //Q养成活动信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 5;
	try
	{
		ar << byProtID_ << byFuncID_ << oQQCoinInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 199, Function: 5";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CWonderActivityProtSvr::SendClt_SyncQQCoinInfo(const UINT64* pUsrID_, UINT16 wCnt_,
	const SQQCoinActInfo& oQQCoinInfo //Q养成活动信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 5;
	try
	{
		ar << byProtID_ << byFuncID_ << oQQCoinInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 199, Function: 5";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CWonderActivityProtSvr::BuildPkg_SyncQQCoinInfo(
	const SQQCoinActInfo& oQQCoinInfo //Q养成活动信息
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 5;
	try
	{
		ar << byProtID_ << byFuncID_ << oQQCoinInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 199, Function: 5";
		_strPkg.clear();
	}
	return _strPkg;
}

CWonderActivityProtSvr::SGetConfigTimeAck::SGetConfigTimeAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eRet((EWActResult)0) { }

void CWonderActivityProtSvr::SGetConfigTimeAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -1;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << sTimes << (UINT8&)eRet;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 199, Function: 1";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CWonderActivityProtSvr::_DoRecv_GetConfigTime(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT16 wWActID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> wWActID;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 199, Function: 1";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SGetConfigTimeAck> fnAck_(new SGetConfigTimeAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetConfigTime(wWActID, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CWonderActivityProtSvr::SGetAllPrizeAck::SGetAllPrizeAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			wActID(0), eRet((EWActResult)0) { }

void CWonderActivityProtSvr::SGetAllPrizeAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -2;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << wActID << sFirstPlayer << sSelfPlayer << vecPrizeConfig << (UINT8&)eRet;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 199, Function: 2";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CWonderActivityProtSvr::_DoRecv_GetAllPrize(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT16 wWActID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> wWActID;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 199, Function: 2";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SGetAllPrizeAck> fnAck_(new SGetAllPrizeAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetAllPrize(wWActID, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CWonderActivityProtSvr::SGetActListAck::SGetActListAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eRet((EWActResult)0) { }

void CWonderActivityProtSvr::SGetActListAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -3;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << vecTimes << (UINT8&)eRet;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 199, Function: 3";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CWonderActivityProtSvr::_DoRecv_GetActList(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 199, Function: 3";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SGetActListAck> fnAck_(new SGetActListAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetActList(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CWonderActivityProtSvr::STakePrizeAck::STakePrizeAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			wActIDRet(0), wCondRet(0) { }

void CWonderActivityProtSvr::STakePrizeAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -4;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << wActIDRet << wCondRet;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 199, Function: 4";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CWonderActivityProtSvr::_DoRecv_TakePrize(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT16 wActID = 0;
	UINT32 wCond = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> wActID >> wCond;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 199, Function: 4";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<STakePrizeAck> fnAck_(new STakePrizeAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_TakePrize(wActID, wCond, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CWonderActivityProtSvr::SGetRoleActInfoAck::SGetRoleActInfoAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			wActIDRet(0) { }

void CWonderActivityProtSvr::SGetRoleActInfoAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -5;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << wActIDRet << vecRet;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 199, Function: 5";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CWonderActivityProtSvr::_DoRecv_GetRoleActInfo(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT16 wActID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> wActID;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 199, Function: 5";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SGetRoleActInfoAck> fnAck_(new SGetRoleActInfoAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetRoleActInfo(wActID, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CWonderActivityProtSvr::SGetRoleAllStateAck::SGetRoleAllStateAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID) { }

void CWonderActivityProtSvr::SGetRoleAllStateAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -6;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << vecRet;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 199, Function: 6";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CWonderActivityProtSvr::_DoRecv_GetRoleAllState(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 199, Function: 6";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SGetRoleAllStateAck> fnAck_(new SGetRoleAllStateAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetRoleAllState(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CWonderActivityProtSvr::SGetDragonBallActAck::SGetDragonBallActAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			byRet(0) { }

void CWonderActivityProtSvr::SGetDragonBallActAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -7;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << byRet;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 199, Function: 7";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CWonderActivityProtSvr::_DoRecv_GetDragonBallAct(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 199, Function: 7";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SGetDragonBallActAck> fnAck_(new SGetDragonBallActAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetDragonBallAct(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CWonderActivityProtSvr::SGetSevenConsumeActAck::SGetSevenConsumeActAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			byRet(0) { }

void CWonderActivityProtSvr::SGetSevenConsumeActAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -8;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << byRet;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 199, Function: 8";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CWonderActivityProtSvr::_DoRecv_GetSevenConsumeAct(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 199, Function: 8";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SGetSevenConsumeActAck> fnAck_(new SGetSevenConsumeActAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetSevenConsumeAct(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

bool CWonderActivityProtSvr::_DoRecv_GetQQCoinAct(const char* pBuf_, UINT32 dwLen_)
{
	OnRecv_GetQQCoinAct();
	return true;
}

CWonderActivityProtSvr::SExChangeAck::SExChangeAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((EWActResult)0) { }

void CWonderActivityProtSvr::SExChangeAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -9;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 199, Function: 10";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CWonderActivityProtSvr::_DoRecv_ExChange(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT8 byType = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> byType;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 199, Function: 10";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SExChangeAck> fnAck_(new SExChangeAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_ExChange(byType, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

} //namespace NWonderActivityProt
