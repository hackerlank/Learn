/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    TreasureHuntProt.cpp
//  Purpose:      寻宝协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "TreasureHuntProtSvr.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NTreasureHuntProt
{

CTreasureHuntProtSvr::THandleFunc CTreasureHuntProtSvr::_HandleFuncs[] =
{
	&CTreasureHuntProtSvr::_DoRecv_ReqTHInfo, //FuncID: 1
	&CTreasureHuntProtSvr::_DoRecv_ReqTHBattlePrepareInfo, //FuncID: 2
	&CTreasureHuntProtSvr::_DoRecv_ReqTHStart, //FuncID: 3
	&CTreasureHuntProtSvr::_DoRecv_ReqTHQuickFinish, //FuncID: 4
	&CTreasureHuntProtSvr::_DoRecv_ReqTHGiveUp, //FuncID: 5
	&CTreasureHuntProtSvr::_DoRecv_ReqUseBuff, //FuncID: 6
	&CTreasureHuntProtSvr::_DoRecv_ReqTHAwardInfo, //FuncID: 7
	&CTreasureHuntProtSvr::_DoRecv_GetTHAward, //FuncID: 8
};

bool CTreasureHuntProtSvr::HandleMessage(const char* pBuf, UINT32 dwLen)
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

//发送：寻宝开始/结束通知
bool CTreasureHuntProtSvr::Send_THNotify(
	ETHNotify eTHNotify, //开始/结束
	UINT8 byKillNum, //今日已击杀BOSS次数
	const TVecTHBuffInfo& vecTHBuffInfo //Buff信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << (INT8&)eTHNotify << byKillNum << vecTHBuffInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 85, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CTreasureHuntProtSvr::SendClt_THNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	ETHNotify eTHNotify, //开始/结束
	UINT8 byKillNum, //今日已击杀BOSS次数
	const TVecTHBuffInfo& vecTHBuffInfo //Buff信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << (INT8&)eTHNotify << byKillNum << vecTHBuffInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 85, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CTreasureHuntProtSvr::BuildPkg_THNotify(
	ETHNotify eTHNotify, //开始/结束
	UINT8 byKillNum, //今日已击杀BOSS次数
	const TVecTHBuffInfo& vecTHBuffInfo //Buff信息
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << (INT8&)eTHNotify << byKillNum << vecTHBuffInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 85, Function: 1";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：战斗结果通知
bool CTreasureHuntProtSvr::Send_THBattleResultNotify(
	const STHBattleResult& sBattleResult //战斗结果
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << sBattleResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 85, Function: 2";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CTreasureHuntProtSvr::SendClt_THBattleResultNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	const STHBattleResult& sBattleResult //战斗结果
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << sBattleResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 85, Function: 2";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CTreasureHuntProtSvr::BuildPkg_THBattleResultNotify(
	const STHBattleResult& sBattleResult //战斗结果
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << sBattleResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 85, Function: 2";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：寻宝掉落通知
bool CTreasureHuntProtSvr::Send_THLootNotify(
	const TVecTHAwardInfo& vecTHAwardInfo //掉落
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << vecTHAwardInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 85, Function: 3";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CTreasureHuntProtSvr::SendClt_THLootNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	const TVecTHAwardInfo& vecTHAwardInfo //掉落
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << vecTHAwardInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 85, Function: 3";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CTreasureHuntProtSvr::BuildPkg_THLootNotify(
	const TVecTHAwardInfo& vecTHAwardInfo //掉落
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << vecTHAwardInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 85, Function: 3";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：日志通知
bool CTreasureHuntProtSvr::Send_THLogNotify(
	ETHLogType eTHLogType, //寻宝日志类型
	UINT32 dwParamA, //参数A
	UINT32 dwParamB, //参数B(注：只对eTHLogTypeF\eTHLogTypeG类型有用,其他类型默认为0)
	UINT64 dwParamC //参数C(注：只对eTHLogTypeG类型有用,其他类型默认为0)
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << (INT8&)eTHLogType << dwParamA << dwParamB << dwParamC;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 85, Function: 4";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CTreasureHuntProtSvr::SendClt_THLogNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	ETHLogType eTHLogType, //寻宝日志类型
	UINT32 dwParamA, //参数A
	UINT32 dwParamB, //参数B(注：只对eTHLogTypeF\eTHLogTypeG类型有用,其他类型默认为0)
	UINT64 dwParamC //参数C(注：只对eTHLogTypeG类型有用,其他类型默认为0)
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << (INT8&)eTHLogType << dwParamA << dwParamB << dwParamC;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 85, Function: 4";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CTreasureHuntProtSvr::BuildPkg_THLogNotify(
	ETHLogType eTHLogType, //寻宝日志类型
	UINT32 dwParamA, //参数A
	UINT32 dwParamB, //参数B(注：只对eTHLogTypeF\eTHLogTypeG类型有用,其他类型默认为0)
	UINT64 dwParamC //参数C(注：只对eTHLogTypeG类型有用,其他类型默认为0)
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << (INT8&)eTHLogType << dwParamA << dwParamB << dwParamC;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 85, Function: 4";
		_strPkg.clear();
	}
	return _strPkg;
}

CTreasureHuntProtSvr::SReqTHInfoAck::SReqTHInfoAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			byCopyID(0), eTHStatus((ETHStatus)0), byKillNum(0), byCurrentID(0) { }

void CTreasureHuntProtSvr::SReqTHInfoAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -1;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << byCopyID << (INT8&)eTHStatus << byKillNum << byCurrentID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 85, Function: 1";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CTreasureHuntProtSvr::_DoRecv_ReqTHInfo(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 85, Function: 1";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SReqTHInfoAck> fnAck_(new SReqTHInfoAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_ReqTHInfo(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CTreasureHuntProtSvr::SReqTHBattlePrepareInfoAck::SReqTHBattlePrepareInfoAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			byKillNum(0), dwCurBossHP(0), dwTotalTimes(0) { }

void CTreasureHuntProtSvr::SReqTHBattlePrepareInfoAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -2;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << byKillNum << dwCurBossHP << dwTotalTimes << vecTHAwardInfo << vecTHBuffInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 85, Function: 2";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CTreasureHuntProtSvr::_DoRecv_ReqTHBattlePrepareInfo(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 85, Function: 2";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SReqTHBattlePrepareInfoAck> fnAck_(new SReqTHBattlePrepareInfoAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_ReqTHBattlePrepareInfo(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CTreasureHuntProtSvr::SReqTHStartAck::SReqTHStartAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eTHOptResult((ETHOptResult)0) { }

void CTreasureHuntProtSvr::SReqTHStartAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -3;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (INT8&)eTHOptResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 85, Function: 3";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CTreasureHuntProtSvr::_DoRecv_ReqTHStart(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT8 byCopyID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> byCopyID;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 85, Function: 3";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SReqTHStartAck> fnAck_(new SReqTHStartAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_ReqTHStart(byCopyID, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CTreasureHuntProtSvr::SReqTHQuickFinishAck::SReqTHQuickFinishAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eTHOptResult((ETHOptResult)0) { }

void CTreasureHuntProtSvr::SReqTHQuickFinishAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -4;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (INT8&)eTHOptResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 85, Function: 4";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CTreasureHuntProtSvr::_DoRecv_ReqTHQuickFinish(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 85, Function: 4";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SReqTHQuickFinishAck> fnAck_(new SReqTHQuickFinishAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_ReqTHQuickFinish(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CTreasureHuntProtSvr::SReqTHGiveUpAck::SReqTHGiveUpAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eTHOptResult((ETHOptResult)0) { }

void CTreasureHuntProtSvr::SReqTHGiveUpAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -5;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (INT8&)eTHOptResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 85, Function: 5";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CTreasureHuntProtSvr::_DoRecv_ReqTHGiveUp(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 85, Function: 5";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SReqTHGiveUpAck> fnAck_(new SReqTHGiveUpAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_ReqTHGiveUp(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CTreasureHuntProtSvr::SReqUseBuffAck::SReqUseBuffAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eTHOptResult((ETHOptResult)0) { }

void CTreasureHuntProtSvr::SReqUseBuffAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -6;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (INT8&)eTHOptResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 85, Function: 6";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CTreasureHuntProtSvr::_DoRecv_ReqUseBuff(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT8 byBuffID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> byBuffID;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 85, Function: 6";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SReqUseBuffAck> fnAck_(new SReqUseBuffAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_ReqUseBuff(byBuffID, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CTreasureHuntProtSvr::SReqTHAwardInfoAck::SReqTHAwardInfoAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			byCopyID(0) { }

void CTreasureHuntProtSvr::SReqTHAwardInfoAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -7;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << byCopyID << vecTHAwardInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 85, Function: 7";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CTreasureHuntProtSvr::_DoRecv_ReqTHAwardInfo(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 85, Function: 7";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SReqTHAwardInfoAck> fnAck_(new SReqTHAwardInfoAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_ReqTHAwardInfo(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CTreasureHuntProtSvr::SGetTHAwardAck::SGetTHAwardAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eTHOptResult((ETHOptResult)0) { }

void CTreasureHuntProtSvr::SGetTHAwardAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -8;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (INT8&)eTHOptResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 85, Function: 8";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CTreasureHuntProtSvr::_DoRecv_GetTHAward(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 85, Function: 8";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SGetTHAwardAck> fnAck_(new SGetTHAwardAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetTHAward(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

} //namespace NTreasureHuntProt
