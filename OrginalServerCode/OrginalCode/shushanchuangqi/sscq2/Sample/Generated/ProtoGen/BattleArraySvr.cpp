/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    BattleArray.cpp
//  Purpose:      破阵
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "BattleArraySvr.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NBattleArray
{

CBattleArraySvr::THandleFunc CBattleArraySvr::_HandleFuncs[] =
{
	&CBattleArraySvr::_DoRecv_GetBattleArray, //FuncID: 1
	&CBattleArraySvr::_DoRecv_AttackBattleArray, //FuncID: 2
	&CBattleArraySvr::_DoRecv_SweepBattleArray, //FuncID: 3
	&CBattleArraySvr::_DoRecv_BattleArrayTakePrize, //FuncID: 4
	&CBattleArraySvr::_DoRecv_GetBuyAtkCountPrice, //FuncID: 5
	&CBattleArraySvr::_DoRecv_BuyAtkCount, //FuncID: 6
};

bool CBattleArraySvr::HandleMessage(const char* pBuf, UINT32 dwLen)
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

//发送：阵信息更新
bool CBattleArraySvr::Send_BattleArrayNotify(
	const SBattleArray& oBattleArray //阵信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << oBattleArray;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 130, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CBattleArraySvr::SendClt_BattleArrayNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	const SBattleArray& oBattleArray //阵信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << oBattleArray;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 130, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CBattleArraySvr::BuildPkg_BattleArrayNotify(
	const SBattleArray& oBattleArray //阵信息
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << oBattleArray;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 130, Function: 1";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：攻击阵图信息
bool CBattleArraySvr::Send_SBattleArrayAttackCntNotify(
	const SBattleArrayAttackCnt& oBattleArrayAttackCnt //攻击阵图信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << oBattleArrayAttackCnt;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 130, Function: 2";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CBattleArraySvr::SendClt_SBattleArrayAttackCntNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	const SBattleArrayAttackCnt& oBattleArrayAttackCnt //攻击阵图信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << oBattleArrayAttackCnt;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 130, Function: 2";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CBattleArraySvr::BuildPkg_SBattleArrayAttackCntNotify(
	const SBattleArrayAttackCnt& oBattleArrayAttackCnt //攻击阵图信息
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << oBattleArrayAttackCnt;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 130, Function: 2";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：总攻击次数
bool CBattleArraySvr::Send_TotleAttackCntNotify(
	UINT32 dwAttackCnt, //总攻击次数
	UINT32 dwBuyCnt //剩余购买数
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << dwAttackCnt << dwBuyCnt;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 130, Function: 3";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CBattleArraySvr::SendClt_TotleAttackCntNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT32 dwAttackCnt, //总攻击次数
	UINT32 dwBuyCnt //剩余购买数
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << dwAttackCnt << dwBuyCnt;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 130, Function: 3";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CBattleArraySvr::BuildPkg_TotleAttackCntNotify(
	UINT32 dwAttackCnt, //总攻击次数
	UINT32 dwBuyCnt //剩余购买数
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << dwAttackCnt << dwBuyCnt;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 130, Function: 3";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：获得物品通知
bool CBattleArraySvr::Send_GainNotify(
	EBattleArrayGain eBattleArrayGain, //类型
	const NItemProt::TVecItemGenInfo& vecItemGenInfo //物品
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eBattleArrayGain << vecItemGenInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 130, Function: 4";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CBattleArraySvr::SendClt_GainNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	EBattleArrayGain eBattleArrayGain, //类型
	const NItemProt::TVecItemGenInfo& vecItemGenInfo //物品
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eBattleArrayGain << vecItemGenInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 130, Function: 4";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CBattleArraySvr::BuildPkg_GainNotify(
	EBattleArrayGain eBattleArrayGain, //类型
	const NItemProt::TVecItemGenInfo& vecItemGenInfo //物品
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eBattleArrayGain << vecItemGenInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 130, Function: 4";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：全部阵信息
bool CBattleArraySvr::Send_GetBattleArrayNotify(
	const TVecBattleArray& vecBattleArray, //阵信息列表
	const TVecBattleArrayAttackCnt& vecBattleArrayAttackCnt, //攻击阵图信息
	UINT32 dwBuyCnt, //可用的次数
	UINT32 dwDayBuyCnt //当天购买次数
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 5;
	try
	{
		ar << byProtID_ << byFuncID_ << vecBattleArray << vecBattleArrayAttackCnt << dwBuyCnt << dwDayBuyCnt;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 130, Function: 5";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CBattleArraySvr::SendClt_GetBattleArrayNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	const TVecBattleArray& vecBattleArray, //阵信息列表
	const TVecBattleArrayAttackCnt& vecBattleArrayAttackCnt, //攻击阵图信息
	UINT32 dwBuyCnt, //可用的次数
	UINT32 dwDayBuyCnt //当天购买次数
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 5;
	try
	{
		ar << byProtID_ << byFuncID_ << vecBattleArray << vecBattleArrayAttackCnt << dwBuyCnt << dwDayBuyCnt;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 130, Function: 5";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CBattleArraySvr::BuildPkg_GetBattleArrayNotify(
	const TVecBattleArray& vecBattleArray, //阵信息列表
	const TVecBattleArrayAttackCnt& vecBattleArrayAttackCnt, //攻击阵图信息
	UINT32 dwBuyCnt, //可用的次数
	UINT32 dwDayBuyCnt //当天购买次数
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 5;
	try
	{
		ar << byProtID_ << byFuncID_ << vecBattleArray << vecBattleArrayAttackCnt << dwBuyCnt << dwDayBuyCnt;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 130, Function: 5";
		_strPkg.clear();
	}
	return _strPkg;
}

CBattleArraySvr::SGetBattleArrayAck::SGetBattleArrayAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			dwBuyCnt(0), dwDayBuyCnt(0), dwFailCd(0) { }

void CBattleArraySvr::SGetBattleArrayAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -1;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << vecBattleArray << vecBattleArrayAttackCnt << dwBuyCnt << dwDayBuyCnt << dwFailCd;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 130, Function: 1";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CBattleArraySvr::_DoRecv_GetBattleArray(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 130, Function: 1";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SGetBattleArrayAck> fnAck_(new SGetBattleArrayAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetBattleArray(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CBattleArraySvr::SAttackBattleArrayAck::SAttackBattleArrayAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eBattleArrayRet((EBattleArrayRet)0), dwFailCd(0) { }

void CBattleArraySvr::SAttackBattleArrayAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -2;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eBattleArrayRet << dwFailCd;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 130, Function: 2";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CBattleArraySvr::_DoRecv_AttackBattleArray(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT32 dwBattleArrayLevelID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> dwBattleArrayLevelID;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 130, Function: 2";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SAttackBattleArrayAck> fnAck_(new SAttackBattleArrayAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_AttackBattleArray(dwBattleArrayLevelID, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CBattleArraySvr::SSweepBattleArrayAck::SSweepBattleArrayAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eBattleArrayRet((EBattleArrayRet)0) { }

void CBattleArraySvr::SSweepBattleArrayAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -3;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eBattleArrayRet;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 130, Function: 3";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CBattleArraySvr::_DoRecv_SweepBattleArray(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT32 dwBattleArrayLevelID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> dwBattleArrayLevelID;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 130, Function: 3";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SSweepBattleArrayAck> fnAck_(new SSweepBattleArrayAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_SweepBattleArray(dwBattleArrayLevelID, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CBattleArraySvr::SBattleArrayTakePrizeAck::SBattleArrayTakePrizeAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eBattleArrayRet((EBattleArrayRet)0) { }

void CBattleArraySvr::SBattleArrayTakePrizeAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -4;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eBattleArrayRet;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 130, Function: 4";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CBattleArraySvr::_DoRecv_BattleArrayTakePrize(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT16 wBattleArrayID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> wBattleArrayID;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 130, Function: 4";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SBattleArrayTakePrizeAck> fnAck_(new SBattleArrayTakePrizeAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_BattleArrayTakePrize(wBattleArrayID, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CBattleArraySvr::SGetBuyAtkCountPriceAck::SGetBuyAtkCountPriceAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			dwPrice(0), dwBuyCount(0) { }

void CBattleArraySvr::SGetBuyAtkCountPriceAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -5;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << dwPrice << dwBuyCount;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 130, Function: 5";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CBattleArraySvr::_DoRecv_GetBuyAtkCountPrice(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT32 dwCount = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> dwCount;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 130, Function: 5";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SGetBuyAtkCountPriceAck> fnAck_(new SGetBuyAtkCountPriceAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetBuyAtkCountPrice(dwCount, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CBattleArraySvr::SBuyAtkCountAck::SBuyAtkCountAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eRet((EBattleArrayRet)0), dwBuyCount(0), dwDayBuyCnt(0) { }

void CBattleArraySvr::SBuyAtkCountAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -6;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eRet << dwBuyCount << dwDayBuyCnt;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 130, Function: 6";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CBattleArraySvr::_DoRecv_BuyAtkCount(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT32 dwCount = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> dwCount;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 130, Function: 6";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SBuyAtkCountAck> fnAck_(new SBuyAtkCountAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_BuyAtkCount(dwCount, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

} //namespace NBattleArray
