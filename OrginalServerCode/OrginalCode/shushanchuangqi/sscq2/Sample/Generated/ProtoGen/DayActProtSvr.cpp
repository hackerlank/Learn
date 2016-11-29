/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    DayActProt.cpp
//  Purpose:      活动
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "DayActProtSvr.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NDayActProt
{

CDayActProtSvr::THandleFunc CDayActProtSvr::_HandleFuncs[] =
{
	&CDayActProtSvr::_DoRecv_GetActList, //FuncID: 1
	&CDayActProtSvr::_DoRecv_GetFirstRechargeStatus, //FuncID: 2
	&CDayActProtSvr::_DoRecv_GetFirstRechargeAward, //FuncID: 3
	&CDayActProtSvr::_DoRecv_BuyShushanFoundSelf, //FuncID: 4
	&CDayActProtSvr::_DoRecv_BuyShushanFoundFirend, //FuncID: 5
	&CDayActProtSvr::_DoRecv_GetShushanFoundInfo, //FuncID: 6
	&CDayActProtSvr::_DoRecv_GetShushanFoundAward, //FuncID: 7
	&CDayActProtSvr::_DoRecv_GetSecondRechargeStatus, //FuncID: 8
	&CDayActProtSvr::_DoRecv_GetSecondRechargeAward, //FuncID: 9
	&CDayActProtSvr::_DoRecv_GetOpenServerTime, //FuncID: 10
};

bool CDayActProtSvr::HandleMessage(const char* pBuf, UINT32 dwLen)
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

//发送：活动状态改变通知
bool CDayActProtSvr::Send_ActChangeNotify(
	UINT32 dwActType, //活动id
	UINT32 dwActStatus //活动状态
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << dwActType << dwActStatus;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 69, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CDayActProtSvr::SendClt_ActChangeNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT32 dwActType, //活动id
	UINT32 dwActStatus //活动状态
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << dwActType << dwActStatus;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 69, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CDayActProtSvr::BuildPkg_ActChangeNotify(
	UINT32 dwActType, //活动id
	UINT32 dwActStatus //活动状态
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << dwActType << dwActStatus;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 69, Function: 1";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：蜀山基金活动改变通知
bool CDayActProtSvr::Send_ShushanFoundChangeNotify(
	UINT16 wGrowFoundInfo, //成长基金(按低到高顺序,0位表示是否购买[1是0否],第1-7位表示7次的领取信息[1是0否])
	UINT16 wPExpFoundInfo, //修为基金(按低到高顺序,0位表示是否购买[1是0否],第1-7位表示7次的领取信息[1是0否])
	UINT16 wSilverFoundInfo, //银币基金(按低到高顺序,0位表示是否购买[1是0否],第1-7位表示7次的领取信息[1是0否])
	UINT16 wItemFoundInfo, //宝物基金(按低到高顺序,0位表示是否购买[1是0否],第1-7位表示7次的领取信息[1是0否])
	UINT32 dwLoginDays //玩家累计登陆天数(按低到高顺序,成长/修为/银币宝物)
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << wGrowFoundInfo << wPExpFoundInfo << wSilverFoundInfo << wItemFoundInfo << dwLoginDays;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 69, Function: 2";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CDayActProtSvr::SendClt_ShushanFoundChangeNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT16 wGrowFoundInfo, //成长基金(按低到高顺序,0位表示是否购买[1是0否],第1-7位表示7次的领取信息[1是0否])
	UINT16 wPExpFoundInfo, //修为基金(按低到高顺序,0位表示是否购买[1是0否],第1-7位表示7次的领取信息[1是0否])
	UINT16 wSilverFoundInfo, //银币基金(按低到高顺序,0位表示是否购买[1是0否],第1-7位表示7次的领取信息[1是0否])
	UINT16 wItemFoundInfo, //宝物基金(按低到高顺序,0位表示是否购买[1是0否],第1-7位表示7次的领取信息[1是0否])
	UINT32 dwLoginDays //玩家累计登陆天数(按低到高顺序,成长/修为/银币宝物)
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << wGrowFoundInfo << wPExpFoundInfo << wSilverFoundInfo << wItemFoundInfo << dwLoginDays;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 69, Function: 2";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CDayActProtSvr::BuildPkg_ShushanFoundChangeNotify(
	UINT16 wGrowFoundInfo, //成长基金(按低到高顺序,0位表示是否购买[1是0否],第1-7位表示7次的领取信息[1是0否])
	UINT16 wPExpFoundInfo, //修为基金(按低到高顺序,0位表示是否购买[1是0否],第1-7位表示7次的领取信息[1是0否])
	UINT16 wSilverFoundInfo, //银币基金(按低到高顺序,0位表示是否购买[1是0否],第1-7位表示7次的领取信息[1是0否])
	UINT16 wItemFoundInfo, //宝物基金(按低到高顺序,0位表示是否购买[1是0否],第1-7位表示7次的领取信息[1是0否])
	UINT32 dwLoginDays //玩家累计登陆天数(按低到高顺序,成长/修为/银币宝物)
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << wGrowFoundInfo << wPExpFoundInfo << wSilverFoundInfo << wItemFoundInfo << dwLoginDays;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 69, Function: 2";
		_strPkg.clear();
	}
	return _strPkg;
}

CDayActProtSvr::SGetActListAck::SGetActListAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID) { }

void CDayActProtSvr::SGetActListAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -1;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << vecActInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 69, Function: 1";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CDayActProtSvr::_DoRecv_GetActList(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 69, Function: 1";
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

CDayActProtSvr::SGetFirstRechargeStatusAck::SGetFirstRechargeStatusAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			byRet(0) { }

void CDayActProtSvr::SGetFirstRechargeStatusAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -2;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << byRet;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 69, Function: 2";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CDayActProtSvr::_DoRecv_GetFirstRechargeStatus(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 69, Function: 2";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SGetFirstRechargeStatusAck> fnAck_(new SGetFirstRechargeStatusAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetFirstRechargeStatus(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CDayActProtSvr::SGetFirstRechargeAwardAck::SGetFirstRechargeAwardAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			byRet(0) { }

void CDayActProtSvr::SGetFirstRechargeAwardAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -3;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << byRet;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 69, Function: 3";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CDayActProtSvr::_DoRecv_GetFirstRechargeAward(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 69, Function: 3";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SGetFirstRechargeAwardAck> fnAck_(new SGetFirstRechargeAwardAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetFirstRechargeAward(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CDayActProtSvr::SBuyShushanFoundSelfAck::SBuyShushanFoundSelfAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			byRet(0) { }

void CDayActProtSvr::SBuyShushanFoundSelfAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -4;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << byRet;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 69, Function: 4";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CDayActProtSvr::_DoRecv_BuyShushanFoundSelf(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 69, Function: 4";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SBuyShushanFoundSelfAck> fnAck_(new SBuyShushanFoundSelfAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_BuyShushanFoundSelf(byType, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CDayActProtSvr::SBuyShushanFoundFirendAck::SBuyShushanFoundFirendAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			byRet(0) { }

void CDayActProtSvr::SBuyShushanFoundFirendAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -5;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << byRet;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 69, Function: 5";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CDayActProtSvr::_DoRecv_BuyShushanFoundFirend(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT64 qwFriendID = 0;
	UINT8 byType = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> qwFriendID >> byType;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 69, Function: 5";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SBuyShushanFoundFirendAck> fnAck_(new SBuyShushanFoundFirendAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_BuyShushanFoundFirend(qwFriendID, byType, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

bool CDayActProtSvr::_DoRecv_GetShushanFoundInfo(const char* pBuf_, UINT32 dwLen_)
{
	OnRecv_GetShushanFoundInfo();
	return true;
}

CDayActProtSvr::SGetShushanFoundAwardAck::SGetShushanFoundAwardAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			byRet(0) { }

void CDayActProtSvr::SGetShushanFoundAwardAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -6;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << byRet;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 69, Function: 7";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CDayActProtSvr::_DoRecv_GetShushanFoundAward(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT8 byType = 0;
	UINT8 byDay = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> byType >> byDay;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 69, Function: 7";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SGetShushanFoundAwardAck> fnAck_(new SGetShushanFoundAwardAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetShushanFoundAward(byType, byDay, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CDayActProtSvr::SGetSecondRechargeStatusAck::SGetSecondRechargeStatusAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			byRet(0), dwSecondRechargeValue(0) { }

void CDayActProtSvr::SGetSecondRechargeStatusAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -7;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << byRet << dwSecondRechargeValue;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 69, Function: 8";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CDayActProtSvr::_DoRecv_GetSecondRechargeStatus(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 69, Function: 8";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SGetSecondRechargeStatusAck> fnAck_(new SGetSecondRechargeStatusAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetSecondRechargeStatus(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CDayActProtSvr::SGetSecondRechargeAwardAck::SGetSecondRechargeAwardAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			byRet(0) { }

void CDayActProtSvr::SGetSecondRechargeAwardAck::SendReturn(bool bRet_)
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
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 69, Function: 9";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CDayActProtSvr::_DoRecv_GetSecondRechargeAward(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 69, Function: 9";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SGetSecondRechargeAwardAck> fnAck_(new SGetSecondRechargeAwardAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetSecondRechargeAward(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CDayActProtSvr::SGetOpenServerTimeAck::SGetOpenServerTimeAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			dwTime(0) { }

void CDayActProtSvr::SGetOpenServerTimeAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -9;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << dwTime;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 69, Function: 10";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CDayActProtSvr::_DoRecv_GetOpenServerTime(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 69, Function: 10";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SGetOpenServerTimeAck> fnAck_(new SGetOpenServerTimeAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetOpenServerTime(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

} //namespace NDayActProt
