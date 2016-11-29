/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    ArenaGS.cpp
//  Purpose:      竞技场协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "ArenaGSSvr.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NArenaGS
{

CArenaGSSvr::THandleFunc CArenaGSSvr::_HandleFuncs[] =
{
	&CArenaGSSvr::_DoRecv_ArenaInfoReq, //FuncID: 1
	&CArenaGSSvr::_DoRecv_ArenaChallengeReq, //FuncID: 2
	&CArenaGSSvr::_DoRecv_ArenaByChallengeTimes, //FuncID: 3
	&CArenaGSSvr::_DoRecv_ArenaPageUpReq, //FuncID: 4
	&CArenaGSSvr::_DoRecv_ArenaClearCDReq, //FuncID: 5
	&CArenaGSSvr::_DoRecv_ArenaGetRankingRewardReq, //FuncID: 6
	&CArenaGSSvr::_DoRecv_ArenaWorship, //FuncID: 7
	&CArenaGSSvr::_DoRecv_FlushNewEnemy, //FuncID: 8
	&CArenaGSSvr::_DoRecv_GetAllEnemy, //FuncID: 9
	&CArenaGSSvr::_DoRecv_GetAllAward, //FuncID: 10
	&CArenaGSSvr::_DoRecv_GetAllWirship, //FuncID: 11
	&CArenaGSSvr::_DoRecv_GetAllAwardInfo, //FuncID: 12
	&CArenaGSSvr::_DoRecv_ReFluseLadderEnemy, //FuncID: 13
	&CArenaGSSvr::_DoRecv_GetLadderAward, //FuncID: 14
	&CArenaGSSvr::_DoRecv_GetArenaAward, //FuncID: 15
	&CArenaGSSvr::_DoRecv_GetLadderReport, //FuncID: 16
	&CArenaGSSvr::_DoRecv_LadderBattle, //FuncID: 17
	&CArenaGSSvr::_DoRecv_LadderPageUpReq, //FuncID: 18
	&CArenaGSSvr::_DoRecv_ArenaBuyLadderTimes, //FuncID: 19
};

bool CArenaGSSvr::HandleMessage(const char* pBuf, UINT32 dwLen)
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

//发送：通告获得最好天梯排名
bool CArenaGSSvr::Send_UpdateLadderMinRank(
	UINT32 dwLastRank, //前排名,0表示无排名
	UINT32 dwNowRank //现排名
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << dwLastRank << dwNowRank;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 26, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CArenaGSSvr::SendClt_UpdateLadderMinRank(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT32 dwLastRank, //前排名,0表示无排名
	UINT32 dwNowRank //现排名
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << dwLastRank << dwNowRank;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 26, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CArenaGSSvr::BuildPkg_UpdateLadderMinRank(
	UINT32 dwLastRank, //前排名,0表示无排名
	UINT32 dwNowRank //现排名
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << dwLastRank << dwNowRank;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 26, Function: 1";
		_strPkg.clear();
	}
	return _strPkg;
}

CArenaGSSvr::SArenaInfoReqAck::SArenaInfoReqAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((EArenaResult)0) { }

void CArenaGSSvr::SArenaInfoReqAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -1;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eResult << stReturn;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 26, Function: 1";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CArenaGSSvr::_DoRecv_ArenaInfoReq(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 26, Function: 1";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SArenaInfoReqAck> fnAck_(new SArenaInfoReqAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_ArenaInfoReq(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CArenaGSSvr::SArenaChallengeReqAck::SArenaChallengeReqAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((EArenaResult)0), qwBattleID(0), bySuc(0), dwScore(0), dwRanking(0), 
			wChallenge(0), wChallengeBuyTimes(0), dwCDTimer(0) { }

void CArenaGSSvr::SArenaChallengeReqAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -2;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eResult << qwBattleID << bySuc << dwScore << dwRanking << wChallenge << wChallengeBuyTimes << dwCDTimer;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 26, Function: 2";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CArenaGSSvr::_DoRecv_ArenaChallengeReq(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT64 qwDefense = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> qwDefense;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 26, Function: 2";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SArenaChallengeReqAck> fnAck_(new SArenaChallengeReqAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_ArenaChallengeReq(qwDefense, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CArenaGSSvr::SArenaByChallengeTimesAck::SArenaByChallengeTimesAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((EArenaResult)0), wChallenge(0), wChallengeBuyTimes(0) { }

void CArenaGSSvr::SArenaByChallengeTimesAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -3;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eResult << wChallenge << wChallengeBuyTimes;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 26, Function: 3";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CArenaGSSvr::_DoRecv_ArenaByChallengeTimes(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 26, Function: 3";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SArenaByChallengeTimesAck> fnAck_(new SArenaByChallengeTimesAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_ArenaByChallengeTimes(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CArenaGSSvr::SArenaPageUpReqAck::SArenaPageUpReqAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((EArenaResult)0), dwSize(0) { }

void CArenaGSSvr::SArenaPageUpReqAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -4;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eResult << dwSize << vecRankData;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 26, Function: 4";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CArenaGSSvr::_DoRecv_ArenaPageUpReq(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	EArenaLevel eLevel = (EArenaLevel)0;
	UINT32 dwRank = 0;
	UINT8 byNum = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> (UINT8&)eLevel >> dwRank >> byNum;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 26, Function: 4";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SArenaPageUpReqAck> fnAck_(new SArenaPageUpReqAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_ArenaPageUpReq(eLevel, dwRank, byNum, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CArenaGSSvr::SArenaClearCDReqAck::SArenaClearCDReqAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((EArenaResult)0) { }

void CArenaGSSvr::SArenaClearCDReqAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -5;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 26, Function: 5";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CArenaGSSvr::_DoRecv_ArenaClearCDReq(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 26, Function: 5";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SArenaClearCDReqAck> fnAck_(new SArenaClearCDReqAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_ArenaClearCDReq(byType, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CArenaGSSvr::SArenaGetRankingRewardReqAck::SArenaGetRankingRewardReqAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((EArenaResult)0) { }

void CArenaGSSvr::SArenaGetRankingRewardReqAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -6;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 26, Function: 6";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CArenaGSSvr::_DoRecv_ArenaGetRankingRewardReq(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT32 dwLootId = 0;
	EArenaAwardType eType = (EArenaAwardType)0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> dwLootId >> (UINT8&)eType;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 26, Function: 6";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SArenaGetRankingRewardReqAck> fnAck_(new SArenaGetRankingRewardReqAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_ArenaGetRankingRewardReq(dwLootId, eType, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CArenaGSSvr::SArenaWorshipAck::SArenaWorshipAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((EArenaResult)0) { }

void CArenaGSSvr::SArenaWorshipAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -7;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 26, Function: 7";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CArenaGSSvr::_DoRecv_ArenaWorship(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT64 qwRoleID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> qwRoleID;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 26, Function: 7";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SArenaWorshipAck> fnAck_(new SArenaWorshipAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_ArenaWorship(qwRoleID, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CArenaGSSvr::SFlushNewEnemyAck::SFlushNewEnemyAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((EArenaResult)0), wSelfReflush(0), wSelfFreeReflush(0) { }

void CArenaGSSvr::SFlushNewEnemyAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -8;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eResult << wSelfReflush << wSelfFreeReflush;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 26, Function: 8";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CArenaGSSvr::_DoRecv_FlushNewEnemy(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 26, Function: 8";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SFlushNewEnemyAck> fnAck_(new SFlushNewEnemyAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_FlushNewEnemy(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CArenaGSSvr::SGetAllEnemyAck::SGetAllEnemyAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((EArenaResult)0) { }

void CArenaGSSvr::SGetAllEnemyAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -9;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eResult << vecFlushFigter;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 26, Function: 9";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CArenaGSSvr::_DoRecv_GetAllEnemy(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 26, Function: 9";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SGetAllEnemyAck> fnAck_(new SGetAllEnemyAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetAllEnemy(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CArenaGSSvr::SGetAllAwardAck::SGetAllAwardAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((EArenaResult)0) { }

void CArenaGSSvr::SGetAllAwardAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -10;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eResult << vecAwards;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 26, Function: 10";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CArenaGSSvr::_DoRecv_GetAllAward(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 26, Function: 10";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SGetAllAwardAck> fnAck_(new SGetAllAwardAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetAllAward(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CArenaGSSvr::SGetAllWirshipAck::SGetAllWirshipAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((EArenaResult)0) { }

void CArenaGSSvr::SGetAllWirshipAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -11;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eResult << vecWirshipFigter;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 26, Function: 11";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CArenaGSSvr::_DoRecv_GetAllWirship(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 26, Function: 11";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SGetAllWirshipAck> fnAck_(new SGetAllWirshipAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetAllWirship(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CArenaGSSvr::SGetAllAwardInfoAck::SGetAllAwardInfoAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((EArenaResult)0) { }

void CArenaGSSvr::SGetAllAwardInfoAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -12;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eResult << vecAwards;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 26, Function: 12";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CArenaGSSvr::_DoRecv_GetAllAwardInfo(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 26, Function: 12";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SGetAllAwardInfoAck> fnAck_(new SGetAllAwardInfoAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetAllAwardInfo(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CArenaGSSvr::SReFluseLadderEnemyAck::SReFluseLadderEnemyAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((EArenaResult)0) { }

void CArenaGSSvr::SReFluseLadderEnemyAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -13;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eResult << vecFlushFigter;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 26, Function: 13";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CArenaGSSvr::_DoRecv_ReFluseLadderEnemy(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 26, Function: 13";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SReFluseLadderEnemyAck> fnAck_(new SReFluseLadderEnemyAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_ReFluseLadderEnemy(byType, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CArenaGSSvr::SGetLadderAwardAck::SGetLadderAwardAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((EArenaResult)0) { }

void CArenaGSSvr::SGetLadderAwardAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -14;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 26, Function: 14";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CArenaGSSvr::_DoRecv_GetLadderAward(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 26, Function: 14";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SGetLadderAwardAck> fnAck_(new SGetLadderAwardAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetLadderAward(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CArenaGSSvr::SGetArenaAwardAck::SGetArenaAwardAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((EArenaResult)0) { }

void CArenaGSSvr::SGetArenaAwardAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -15;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 26, Function: 15";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CArenaGSSvr::_DoRecv_GetArenaAward(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 26, Function: 15";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SGetArenaAwardAck> fnAck_(new SGetArenaAwardAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetArenaAward(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CArenaGSSvr::SGetLadderReportAck::SGetLadderReportAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((EArenaResult)0) { }

void CArenaGSSvr::SGetLadderReportAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -16;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eResult << vecReport;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 26, Function: 16";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CArenaGSSvr::_DoRecv_GetLadderReport(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 26, Function: 16";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SGetLadderReportAck> fnAck_(new SGetLadderReportAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetLadderReport(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CArenaGSSvr::SLadderBattleAck::SLadderBattleAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((EArenaResult)0), bySuc(0), dwSelfRank(0), dwLadderTimes(0), dwLadderCDTimer(0), 
			dwMinLadderRank(0), dwLadderBuyTimes(0) { }

void CArenaGSSvr::SLadderBattleAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -17;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eResult << bySuc << vecFlushFigter << dwSelfRank << dwLadderTimes << dwLadderCDTimer << dwMinLadderRank << dwLadderBuyTimes;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 26, Function: 17";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CArenaGSSvr::_DoRecv_LadderBattle(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT64 qwEnemyID = 0;
	UINT32 dwEnemyRank = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> qwEnemyID >> dwEnemyRank;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 26, Function: 17";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SLadderBattleAck> fnAck_(new SLadderBattleAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_LadderBattle(qwEnemyID, dwEnemyRank, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CArenaGSSvr::SLadderPageUpReqAck::SLadderPageUpReqAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((EArenaResult)0) { }

void CArenaGSSvr::SLadderPageUpReqAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -18;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eResult << vecRankData;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 26, Function: 18";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CArenaGSSvr::_DoRecv_LadderPageUpReq(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT32 dwRank = 0;
	UINT8 byNum = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> dwRank >> byNum;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 26, Function: 18";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SLadderPageUpReqAck> fnAck_(new SLadderPageUpReqAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_LadderPageUpReq(dwRank, byNum, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CArenaGSSvr::SArenaBuyLadderTimesAck::SArenaBuyLadderTimesAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((EArenaResult)0), dwLadderBuyTimesToday(0), dwLadderBuyTimes(0) { }

void CArenaGSSvr::SArenaBuyLadderTimesAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -19;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eResult << dwLadderBuyTimesToday << dwLadderBuyTimes;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 26, Function: 19";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CArenaGSSvr::_DoRecv_ArenaBuyLadderTimes(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 26, Function: 19";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SArenaBuyLadderTimesAck> fnAck_(new SArenaBuyLadderTimesAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_ArenaBuyLadderTimes(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

} //namespace NArenaGS
