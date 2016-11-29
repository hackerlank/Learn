/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    TripodProt.cpp
//  Purpose:      九疑鼎相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "TripodProtSvr.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NTripodProt
{

CTripodProtSvr::THandleFunc CTripodProtSvr::_HandleFuncs[] =
{
	&CTripodProtSvr::_DoRecv_GetAllTripods, //FuncID: 1
	&CTripodProtSvr::_DoRecv_GetAllFires, //FuncID: 2
	&CTripodProtSvr::_DoRecv_GetTripodData, //FuncID: 3
	&CTripodProtSvr::_DoRecv_ActiveTripod, //FuncID: 4
	&CTripodProtSvr::_DoRecv_UpgradeTripod, //FuncID: 5
	&CTripodProtSvr::_DoRecv_MakeFireTripod, //FuncID: 6
	&CTripodProtSvr::_DoRecv_ClearFireTripod, //FuncID: 7
	&CTripodProtSvr::_DoRecv_GetTripodAward, //FuncID: 8
	&CTripodProtSvr::_DoRecv_SpeedTripod, //FuncID: 9
	&CTripodProtSvr::_DoRecv_AddTripodExtraSoul, //FuncID: 10
	&CTripodProtSvr::_DoRecv_FighterHelpTripod, //FuncID: 11
	&CTripodProtSvr::_DoRecv_UserHelpTripod, //FuncID: 12
	&CTripodProtSvr::_DoRecv_ShotOffHelpTripod, //FuncID: 13
	&CTripodProtSvr::_DoRecv_GetTripodStatus, //FuncID: 14
};

bool CTripodProtSvr::HandleMessage(const char* pBuf, UINT32 dwLen)
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

//发送：更新玩家的九疑鼎数据
bool CTripodProtSvr::Send_UpdateTripod(
	const STripodData& oTripodData, //九疑鼎数据列表
	UINT8 byShanfeng, //玩家今日已扇风次数
	UINT8 byHelpTimes //玩家今日已协助次数(玩家协助)
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << oTripodData << byShanfeng << byHelpTimes;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 63, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CTripodProtSvr::SendClt_UpdateTripod(const UINT64* pUsrID_, UINT16 wCnt_,
	const STripodData& oTripodData, //九疑鼎数据列表
	UINT8 byShanfeng, //玩家今日已扇风次数
	UINT8 byHelpTimes //玩家今日已协助次数(玩家协助)
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << oTripodData << byShanfeng << byHelpTimes;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 63, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CTripodProtSvr::BuildPkg_UpdateTripod(
	const STripodData& oTripodData, //九疑鼎数据列表
	UINT8 byShanfeng, //玩家今日已扇风次数
	UINT8 byHelpTimes //玩家今日已协助次数(玩家协助)
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << oTripodData << byShanfeng << byHelpTimes;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 63, Function: 1";
		_strPkg.clear();
	}
	return _strPkg;
}

CTripodProtSvr::SGetAllTripodsAck::SGetAllTripodsAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			byShanfeng(0), byHelpTimes(0) { }

void CTripodProtSvr::SGetAllTripodsAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -1;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << oTripodData << byShanfeng << byHelpTimes;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 63, Function: 1";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CTripodProtSvr::_DoRecv_GetAllTripods(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 63, Function: 1";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SGetAllTripodsAck> fnAck_(new SGetAllTripodsAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetAllTripods(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CTripodProtSvr::SGetAllFiresAck::SGetAllFiresAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID) { }

void CTripodProtSvr::SGetAllFiresAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -2;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << vecFires;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 63, Function: 2";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CTripodProtSvr::_DoRecv_GetAllFires(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 63, Function: 2";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SGetAllFiresAck> fnAck_(new SGetAllFiresAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetAllFires(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CTripodProtSvr::SGetTripodDataAck::SGetTripodDataAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID) { }

void CTripodProtSvr::SGetTripodDataAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -3;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << oTripodData;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 63, Function: 3";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CTripodProtSvr::_DoRecv_GetTripodData(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 63, Function: 3";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SGetTripodDataAck> fnAck_(new SGetTripodDataAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetTripodData(qwRoleID, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CTripodProtSvr::SActiveTripodAck::SActiveTripodAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			byTripodID(0), eResult((ETripodType)0) { }

void CTripodProtSvr::SActiveTripodAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -4;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << byTripodID << (UINT8&)eResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 63, Function: 4";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CTripodProtSvr::_DoRecv_ActiveTripod(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT8 byTripodID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> byTripodID;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 63, Function: 4";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SActiveTripodAck> fnAck_(new SActiveTripodAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_ActiveTripod(byTripodID, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CTripodProtSvr::SUpgradeTripodAck::SUpgradeTripodAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((ETripodType)0) { }

void CTripodProtSvr::SUpgradeTripodAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -5;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << vecTripods << (UINT8&)eResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 63, Function: 5";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CTripodProtSvr::_DoRecv_UpgradeTripod(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT8 byTripodID = 0;
	UINT8 byOneKey = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> byTripodID >> byOneKey;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 63, Function: 5";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SUpgradeTripodAck> fnAck_(new SUpgradeTripodAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_UpgradeTripod(byTripodID, byOneKey, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CTripodProtSvr::SMakeFireTripodAck::SMakeFireTripodAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((ETripodType)0) { }

void CTripodProtSvr::SMakeFireTripodAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -6;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << vecTripods << (UINT8&)eResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 63, Function: 6";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CTripodProtSvr::_DoRecv_MakeFireTripod(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT8 byTripodID = 0;
	UINT16 wFireID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> byTripodID >> wFireID;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 63, Function: 6";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SMakeFireTripodAck> fnAck_(new SMakeFireTripodAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_MakeFireTripod(byTripodID, wFireID, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CTripodProtSvr::SClearFireTripodAck::SClearFireTripodAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			byTripodID(0), eResult((ETripodType)0) { }

void CTripodProtSvr::SClearFireTripodAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -7;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << byTripodID << (UINT8&)eResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 63, Function: 7";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CTripodProtSvr::_DoRecv_ClearFireTripod(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT8 byTripodID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> byTripodID;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 63, Function: 7";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SClearFireTripodAck> fnAck_(new SClearFireTripodAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_ClearFireTripod(byTripodID, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CTripodProtSvr::SGetTripodAwardAck::SGetTripodAwardAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((ETripodType)0) { }

void CTripodProtSvr::SGetTripodAwardAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -8;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << vecTripods << (UINT8&)eResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 63, Function: 8";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CTripodProtSvr::_DoRecv_GetTripodAward(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT8 byTripodID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> byTripodID;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 63, Function: 8";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SGetTripodAwardAck> fnAck_(new SGetTripodAwardAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetTripodAward(byTripodID, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CTripodProtSvr::SSpeedTripodAck::SSpeedTripodAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((ETripodType)0) { }

void CTripodProtSvr::SSpeedTripodAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -9;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << vecTripods << (UINT8&)eResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 63, Function: 9";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CTripodProtSvr::_DoRecv_SpeedTripod(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT8 byTripodID = 0;
	NItemProt::TVecItemCount vecItems;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> byTripodID >> vecItems;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 63, Function: 9";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SSpeedTripodAck> fnAck_(new SSpeedTripodAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_SpeedTripod(byTripodID, vecItems, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CTripodProtSvr::SAddTripodExtraSoulAck::SAddTripodExtraSoulAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((ETripodType)0) { }

void CTripodProtSvr::SAddTripodExtraSoulAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -10;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << vecTripods << (UINT8&)eResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 63, Function: 10";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CTripodProtSvr::_DoRecv_AddTripodExtraSoul(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT64 qwRoleID = 0;
	UINT8 byTripodID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> qwRoleID >> byTripodID;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 63, Function: 10";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SAddTripodExtraSoulAck> fnAck_(new SAddTripodExtraSoulAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_AddTripodExtraSoul(qwRoleID, byTripodID, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CTripodProtSvr::SFighterHelpTripodAck::SFighterHelpTripodAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((ETripodType)0) { }

void CTripodProtSvr::SFighterHelpTripodAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -11;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << oFighterHelp << (UINT8&)eResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 63, Function: 11";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CTripodProtSvr::_DoRecv_FighterHelpTripod(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT16 wFighterID = 0;
	UINT8 byPos = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> wFighterID >> byPos;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 63, Function: 11";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SFighterHelpTripodAck> fnAck_(new SFighterHelpTripodAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_FighterHelpTripod(wFighterID, byPos, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CTripodProtSvr::SUserHelpTripodAck::SUserHelpTripodAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((ETripodType)0) { }

void CTripodProtSvr::SUserHelpTripodAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -12;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << oPlayerHelp << (UINT8&)eResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 63, Function: 12";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CTripodProtSvr::_DoRecv_UserHelpTripod(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT64 qwRoleID = 0;
	UINT8 byPos = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> qwRoleID >> byPos;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 63, Function: 12";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SUserHelpTripodAck> fnAck_(new SUserHelpTripodAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_UserHelpTripod(qwRoleID, byPos, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CTripodProtSvr::SShotOffHelpTripodAck::SShotOffHelpTripodAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((ETripodType)0), byPos(0), byType(0) { }

void CTripodProtSvr::SShotOffHelpTripodAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -13;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eResult << byPos << byType;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 63, Function: 13";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CTripodProtSvr::_DoRecv_ShotOffHelpTripod(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT8 byPos = 0;
	UINT8 byType = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> byPos >> byType;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 63, Function: 13";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SShotOffHelpTripodAck> fnAck_(new SShotOffHelpTripodAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_ShotOffHelpTripod(byPos, byType, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CTripodProtSvr::SGetTripodStatusAck::SGetTripodStatusAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID) { }

void CTripodProtSvr::SGetTripodStatusAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -14;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << vecStatus;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 63, Function: 14";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CTripodProtSvr::_DoRecv_GetTripodStatus(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	TVecUINT64 vecRoleID;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> vecRoleID;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 63, Function: 14";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SGetTripodStatusAck> fnAck_(new SGetTripodStatusAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetTripodStatus(vecRoleID, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

} //namespace NTripodProt
