/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    PHPProt.cpp
//  Purpose:      PHP相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "PHPProtSvr.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NPHPProt
{

CPHPProtSvr::THandleFunc CPHPProtSvr::_HandleFuncs[] =
{
	&CPHPProtSvr::_DoRecv_OnUserRecharge, //FuncID: 1
	&CPHPProtSvr::_DoRecv_ModifyActivityIntegral, //FuncID: 2
	&CPHPProtSvr::_DoRecv_GetPlayerInfo, //FuncID: 3
	&CPHPProtSvr::_DoRecv_GetPlayerBagInfo, //FuncID: 4
	&CPHPProtSvr::_DoRecv_DelItem, //FuncID: 5
	&CPHPProtSvr::_DoRecv_GetActList, //FuncID: 6
	&CPHPProtSvr::_DoRecv_OpenAct, //FuncID: 7
	&CPHPProtSvr::_DoRecv_LockOrUnlockUser, //FuncID: 8
	&CPHPProtSvr::_DoRecv_LockOrUnlockSpeak, //FuncID: 9
	&CPHPProtSvr::_DoRecv_GetOnlineNum, //FuncID: 10
	&CPHPProtSvr::_DoRecv_SendItem, //FuncID: 11
	&CPHPProtSvr::_DoRecv_SubMoney, //FuncID: 12
	&CPHPProtSvr::_DoRecv_SendVIPItem, //FuncID: 13
	&CPHPProtSvr::_DoRecv_SendClanItem, //FuncID: 14
	&CPHPProtSvr::_DoRecv_GlobalSendItem, //FuncID: 15
	&CPHPProtSvr::_DoRecv_SendMail, //FuncID: 16
	&CPHPProtSvr::_DoRecv_GlobalSendMail, //FuncID: 17
	&CPHPProtSvr::_DoRecv_GlobalSendNotice, //FuncID: 18
	&CPHPProtSvr::_DoRecv_GlobalDelNotice, //FuncID: 19
	&CPHPProtSvr::_DoRecv_GlobalSendSysDialog, //FuncID: 20
	&CPHPProtSvr::_DoRecv_OpenDiscountActivity, //FuncID: 21
	&CPHPProtSvr::_DoRecv_SetPlayerLevel, //FuncID: 22
	&CPHPProtSvr::_DoRecv_SetPlayerVIPLevel, //FuncID: 23
	&CPHPProtSvr::_DoRecv_TaskManager, //FuncID: 24
	&CPHPProtSvr::_DoRecv_PlatformInfo, //FuncID: 25
	&CPHPProtSvr::_DoRecv_GetTaskState, //FuncID: 26
	&CPHPProtSvr::_DoRecv_SynWeiweiPersonNum, //FuncID: 27
	&CPHPProtSvr::_DoRecv_CheckCDK, //FuncID: 28
	&CPHPProtSvr::_DoRecv_SynQQAlarm, //FuncID: 29
	&CPHPProtSvr::_DoRecv_ModifyChest, //FuncID: 30
	&CPHPProtSvr::_DoRecv_SetPool, //FuncID: 31
	&CPHPProtSvr::_DoRecv_GetLoginDays, //FuncID: 32
	&CPHPProtSvr::_DoRecv_SendQQGroupMsg, //FuncID: 33
	&CPHPProtSvr::_DoRecv_SendTitle, //FuncID: 34
	&CPHPProtSvr::_DoRecv_TestPHP, //FuncID: 35
};

bool CPHPProtSvr::HandleMessage(const char* pBuf, UINT32 dwLen)
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

CPHPProtSvr::SOnUserRechargeAck::SOnUserRechargeAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID), 
			byRet(0) { }

void CPHPProtSvr::SOnUserRechargeAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -1;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << byRet << strError;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 90, Function: 1";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CPHPProtSvr::_DoRecv_OnUserRecharge(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT16 wServerNo = 0;
	std::string strToken;
	std::string strNo;
	UINT64 qwUserID = 0;
	UINT16 wID = 0;
	UINT32 dwValue = 0;
	std::string strUINT;
	std::string strMoney;
	std::string strParam;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> wServerNo >> strToken >> strNo >> qwUserID >> wID >> dwValue >> strUINT >> strMoney >> strParam;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 90, Function: 1";
		return false;
	}
	shared_func<SOnUserRechargeAck> fnAck_(new SOnUserRechargeAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_OnUserRecharge(wServerNo, strToken, strNo, qwUserID, wID, dwValue, strUINT, strMoney, strParam, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CPHPProtSvr::SModifyActivityIntegralAck::SModifyActivityIntegralAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID), 
			eOptResult((EOptResult)0) { }

void CPHPProtSvr::SModifyActivityIntegralAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -2;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (INT8&)eOptResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 90, Function: 2";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CPHPProtSvr::_DoRecv_ModifyActivityIntegral(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT16 wServerNo = 0;
	UINT64 qwUserID = 0;
	EActivityType eType = (EActivityType)0;
	INT32 dwActCount = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> wServerNo >> qwUserID >> (UINT8&)eType >> dwActCount;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 90, Function: 2";
		return false;
	}
	shared_func<SModifyActivityIntegralAck> fnAck_(new SModifyActivityIntegralAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_ModifyActivityIntegral(wServerNo, qwUserID, eType, dwActCount, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CPHPProtSvr::SGetPlayerInfoAck::SGetPlayerInfoAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID) { }

void CPHPProtSvr::SGetPlayerInfoAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -3;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << vecPlayerInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 90, Function: 3";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CPHPProtSvr::_DoRecv_GetPlayerInfo(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT16 wServerNo = 0;
	std::string strName;
	UINT64 qwUserID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> wServerNo >> strName >> qwUserID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 90, Function: 3";
		return false;
	}
	shared_func<SGetPlayerInfoAck> fnAck_(new SGetPlayerInfoAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetPlayerInfo(wServerNo, strName, qwUserID, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CPHPProtSvr::SGetPlayerBagInfoAck::SGetPlayerBagInfoAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID) { }

void CPHPProtSvr::SGetPlayerBagInfoAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -4;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << vecPlayerBagInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 90, Function: 4";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CPHPProtSvr::_DoRecv_GetPlayerBagInfo(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT16 wServerNo = 0;
	std::string strName;
	UINT64 qwUserID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> wServerNo >> strName >> qwUserID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 90, Function: 4";
		return false;
	}
	shared_func<SGetPlayerBagInfoAck> fnAck_(new SGetPlayerBagInfoAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetPlayerBagInfo(wServerNo, strName, qwUserID, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CPHPProtSvr::SDelItemAck::SDelItemAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID), 
			eOptResult((EOptResult)0) { }

void CPHPProtSvr::SDelItemAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -5;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (INT8&)eOptResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 90, Function: 5";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CPHPProtSvr::_DoRecv_DelItem(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT16 wServerNo = 0;
	std::string strName;
	UINT64 qwUserID = 0;
	UINT8 byType = 0;
	UINT64 qwInstID = 0;
	UINT16 wCount = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> wServerNo >> strName >> qwUserID >> byType >> qwInstID >> wCount;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 90, Function: 5";
		return false;
	}
	shared_func<SDelItemAck> fnAck_(new SDelItemAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_DelItem(wServerNo, strName, qwUserID, byType, qwInstID, wCount, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CPHPProtSvr::SGetActListAck::SGetActListAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID) { }

void CPHPProtSvr::SGetActListAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -6;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << vecIDs;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 90, Function: 6";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CPHPProtSvr::_DoRecv_GetActList(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 90, Function: 6";
		return false;
	}
	shared_func<SGetActListAck> fnAck_(new SGetActListAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetActList(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CPHPProtSvr::SOpenActAck::SOpenActAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID), 
			eOptResult((EOptResult)0) { }

void CPHPProtSvr::SOpenActAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -7;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (INT8&)eOptResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 90, Function: 7";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CPHPProtSvr::_DoRecv_OpenAct(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	EActivityType eType = (EActivityType)0;
	UINT32 dwBegin = 0;
	UINT32 dwEnd = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> (UINT8&)eType >> dwBegin >> dwEnd;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 90, Function: 7";
		return false;
	}
	shared_func<SOpenActAck> fnAck_(new SOpenActAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_OpenAct(eType, dwBegin, dwEnd, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CPHPProtSvr::SLockOrUnlockUserAck::SLockOrUnlockUserAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID), 
			eOptResult((EOptResult)0) { }

void CPHPProtSvr::SLockOrUnlockUserAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -8;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (INT8&)eOptResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 90, Function: 8";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CPHPProtSvr::_DoRecv_LockOrUnlockUser(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT16 wServerNo = 0;
	std::string strName;
	UINT64 qwUserID = 0;
	EOptType eOptType = (EOptType)0;
	UINT32 dwEndTime = 0;
	std::string strArgument;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> wServerNo >> strName >> qwUserID >> (INT8&)eOptType >> dwEndTime >> strArgument;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 90, Function: 8";
		return false;
	}
	shared_func<SLockOrUnlockUserAck> fnAck_(new SLockOrUnlockUserAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_LockOrUnlockUser(wServerNo, strName, qwUserID, eOptType, dwEndTime, strArgument, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CPHPProtSvr::SLockOrUnlockSpeakAck::SLockOrUnlockSpeakAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID), 
			eOptResult((EOptResult)0) { }

void CPHPProtSvr::SLockOrUnlockSpeakAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -9;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (INT8&)eOptResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 90, Function: 9";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CPHPProtSvr::_DoRecv_LockOrUnlockSpeak(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT16 wServerNo = 0;
	std::string strName;
	UINT64 qwUserID = 0;
	EOptType eOptType = (EOptType)0;
	UINT32 dwEndTime = 0;
	std::string strArgument;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> wServerNo >> strName >> qwUserID >> (INT8&)eOptType >> dwEndTime >> strArgument;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 90, Function: 9";
		return false;
	}
	shared_func<SLockOrUnlockSpeakAck> fnAck_(new SLockOrUnlockSpeakAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_LockOrUnlockSpeak(wServerNo, strName, qwUserID, eOptType, dwEndTime, strArgument, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CPHPProtSvr::SGetOnlineNumAck::SGetOnlineNumAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID), 
			dwOnlineNum(0) { }

void CPHPProtSvr::SGetOnlineNumAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -10;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << dwOnlineNum;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 90, Function: 10";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CPHPProtSvr::_DoRecv_GetOnlineNum(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT16 wServerNo = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> wServerNo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 90, Function: 10";
		return false;
	}
	shared_func<SGetOnlineNumAck> fnAck_(new SGetOnlineNumAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetOnlineNum(wServerNo, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CPHPProtSvr::SSendItemAck::SSendItemAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID), 
			eOptResult((EOptResult)0) { }

void CPHPProtSvr::SSendItemAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -11;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (INT8&)eOptResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 90, Function: 11";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CPHPProtSvr::_DoRecv_SendItem(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT16 wServerNo = 0;
	std::string strUserID;
	std::string strName;
	std::string strItem;
	std::string strTitle;
	std::string strContent;
	std::string strArgument;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> wServerNo >> strUserID >> strName >> strItem >> strTitle >> strContent >> strArgument;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 90, Function: 11";
		return false;
	}
	shared_func<SSendItemAck> fnAck_(new SSendItemAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_SendItem(wServerNo, strUserID, strName, strItem, strTitle, strContent, strArgument, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CPHPProtSvr::SSubMoneyAck::SSubMoneyAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID), 
			eOptResult((EOptResult)0) { }

void CPHPProtSvr::SSubMoneyAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -12;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (INT8&)eOptResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 90, Function: 12";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CPHPProtSvr::_DoRecv_SubMoney(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT16 wServerNo = 0;
	std::string strUserID;
	std::string strName;
	std::string strItem;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> wServerNo >> strUserID >> strName >> strItem;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 90, Function: 12";
		return false;
	}
	shared_func<SSubMoneyAck> fnAck_(new SSubMoneyAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_SubMoney(wServerNo, strUserID, strName, strItem, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CPHPProtSvr::SSendVIPItemAck::SSendVIPItemAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID), 
			eOptResult((EOptResult)0) { }

void CPHPProtSvr::SSendVIPItemAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -13;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (INT8&)eOptResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 90, Function: 13";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CPHPProtSvr::_DoRecv_SendVIPItem(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT16 wServerNo = 0;
	UINT8 byVIPMinLevel = 0;
	UINT8 byVIPMaxLevel = 0;
	std::string strItem;
	std::string strTitle;
	std::string strContent;
	std::string strArgument;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> wServerNo >> byVIPMinLevel >> byVIPMaxLevel >> strItem >> strTitle >> strContent >> strArgument;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 90, Function: 13";
		return false;
	}
	shared_func<SSendVIPItemAck> fnAck_(new SSendVIPItemAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_SendVIPItem(wServerNo, byVIPMinLevel, byVIPMaxLevel, strItem, strTitle, strContent, strArgument, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CPHPProtSvr::SSendClanItemAck::SSendClanItemAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID), 
			eOptResult((EOptResult)0) { }

void CPHPProtSvr::SSendClanItemAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -14;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (INT8&)eOptResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 90, Function: 14";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CPHPProtSvr::_DoRecv_SendClanItem(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT16 wServerNo = 0;
	UINT64 qwClanID = 0;
	ESendTarget eTarget = (ESendTarget)0;
	std::string strItem;
	std::string strTitle;
	std::string strContent;
	std::string strArgument;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> wServerNo >> qwClanID >> (UINT8&)eTarget >> strItem >> strTitle >> strContent >> strArgument;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 90, Function: 14";
		return false;
	}
	shared_func<SSendClanItemAck> fnAck_(new SSendClanItemAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_SendClanItem(wServerNo, qwClanID, eTarget, strItem, strTitle, strContent, strArgument, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CPHPProtSvr::SGlobalSendItemAck::SGlobalSendItemAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID), 
			eOptResult((EOptResult)0) { }

void CPHPProtSvr::SGlobalSendItemAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -15;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (INT8&)eOptResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 90, Function: 15";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CPHPProtSvr::_DoRecv_GlobalSendItem(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT16 wServerNo = 0;
	ESendTarget eTarget = (ESendTarget)0;
	std::string strItem;
	std::string strTitle;
	std::string strContent;
	std::string strArgument;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> wServerNo >> (UINT8&)eTarget >> strItem >> strTitle >> strContent >> strArgument;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 90, Function: 15";
		return false;
	}
	shared_func<SGlobalSendItemAck> fnAck_(new SGlobalSendItemAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_GlobalSendItem(wServerNo, eTarget, strItem, strTitle, strContent, strArgument, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CPHPProtSvr::SSendMailAck::SSendMailAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID), 
			eOptResult((EOptResult)0) { }

void CPHPProtSvr::SSendMailAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -16;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (INT8&)eOptResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 90, Function: 16";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CPHPProtSvr::_DoRecv_SendMail(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT16 wServerNo = 0;
	std::string strUserID;
	std::string strName;
	std::string strTitle;
	std::string strContent;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> wServerNo >> strUserID >> strName >> strTitle >> strContent;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 90, Function: 16";
		return false;
	}
	shared_func<SSendMailAck> fnAck_(new SSendMailAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_SendMail(wServerNo, strUserID, strName, strTitle, strContent, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CPHPProtSvr::SGlobalSendMailAck::SGlobalSendMailAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID), 
			eOptResult((EOptResult)0) { }

void CPHPProtSvr::SGlobalSendMailAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -17;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (INT8&)eOptResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 90, Function: 17";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CPHPProtSvr::_DoRecv_GlobalSendMail(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT16 wServerNo = 0;
	ESendTarget eTarget = (ESendTarget)0;
	std::string strTitle;
	std::string strContent;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> wServerNo >> (UINT8&)eTarget >> strTitle >> strContent;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 90, Function: 17";
		return false;
	}
	shared_func<SGlobalSendMailAck> fnAck_(new SGlobalSendMailAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_GlobalSendMail(wServerNo, eTarget, strTitle, strContent, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CPHPProtSvr::SGlobalSendNoticeAck::SGlobalSendNoticeAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID), 
			dwNoticeID(0), eOptResult((EOptResult)0) { }

void CPHPProtSvr::SGlobalSendNoticeAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -18;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << dwNoticeID << (INT8&)eOptResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 90, Function: 18";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CPHPProtSvr::_DoRecv_GlobalSendNotice(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT16 wServerNo = 0;
	std::string strContent;
	EPlatformType ePlatformType = (EPlatformType)0;
	EShowType eShowType = (EShowType)0;
	ERollType eRollType = (ERollType)0;
	ESendType eSendType = (ESendType)0;
	UINT32 dwBeginTime = 0;
	UINT32 dwEndTime = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> wServerNo >> strContent >> (UINT8&)ePlatformType >> (UINT8&)eShowType >> (UINT8&)eRollType >> (UINT8&)eSendType >> dwBeginTime >> dwEndTime;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 90, Function: 18";
		return false;
	}
	shared_func<SGlobalSendNoticeAck> fnAck_(new SGlobalSendNoticeAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_GlobalSendNotice(wServerNo, strContent, ePlatformType, eShowType, eRollType, eSendType, dwBeginTime, dwEndTime, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CPHPProtSvr::SGlobalDelNoticeAck::SGlobalDelNoticeAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID), 
			eOptResult((EOptResult)0) { }

void CPHPProtSvr::SGlobalDelNoticeAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -19;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (INT8&)eOptResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 90, Function: 19";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CPHPProtSvr::_DoRecv_GlobalDelNotice(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT16 wServerNo = 0;
	UINT32 dwNoticeID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> wServerNo >> dwNoticeID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 90, Function: 19";
		return false;
	}
	shared_func<SGlobalDelNoticeAck> fnAck_(new SGlobalDelNoticeAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_GlobalDelNotice(wServerNo, dwNoticeID, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CPHPProtSvr::SGlobalSendSysDialogAck::SGlobalSendSysDialogAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID), 
			eOptResult((EOptResult)0) { }

void CPHPProtSvr::SGlobalSendSysDialogAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -20;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (INT8&)eOptResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 90, Function: 20";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CPHPProtSvr::_DoRecv_GlobalSendSysDialog(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT16 wServerNo = 0;
	EPlatformType ePlatformType = (EPlatformType)0;
	EDialogType eDialogType = (EDialogType)0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> wServerNo >> (UINT8&)ePlatformType >> (UINT8&)eDialogType;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 90, Function: 20";
		return false;
	}
	shared_func<SGlobalSendSysDialogAck> fnAck_(new SGlobalSendSysDialogAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_GlobalSendSysDialog(wServerNo, ePlatformType, eDialogType, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CPHPProtSvr::SOpenDiscountActivityAck::SOpenDiscountActivityAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID), 
			eOptResult((EOptResult)0) { }

void CPHPProtSvr::SOpenDiscountActivityAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -21;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (INT8&)eOptResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 90, Function: 21";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CPHPProtSvr::_DoRecv_OpenDiscountActivity(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT16 wServerNo = 0;
	UINT8 byPos = 0;
	UINT8 byOptType = 0;
	std::string strDisItems;
	UINT8 byLimitType = 0;
	UINT32 dwLimitValue = 0;
	UINT16 wLimitCount = 0;
	UINT32 dwBeginTime = 0;
	UINT32 dwEndTime = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> wServerNo >> byPos >> byOptType >> strDisItems >> byLimitType >> dwLimitValue >> wLimitCount >> dwBeginTime >> dwEndTime;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 90, Function: 21";
		return false;
	}
	shared_func<SOpenDiscountActivityAck> fnAck_(new SOpenDiscountActivityAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_OpenDiscountActivity(wServerNo, byPos, byOptType, strDisItems, byLimitType, dwLimitValue, wLimitCount, dwBeginTime, dwEndTime, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CPHPProtSvr::SSetPlayerLevelAck::SSetPlayerLevelAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID), 
			eOptResult((EOptResult)0) { }

void CPHPProtSvr::SSetPlayerLevelAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -22;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (INT8&)eOptResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 90, Function: 22";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CPHPProtSvr::_DoRecv_SetPlayerLevel(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT16 wServerNo = 0;
	std::string strName;
	UINT64 qwUserID = 0;
	UINT16 wLevel = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> wServerNo >> strName >> qwUserID >> wLevel;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 90, Function: 22";
		return false;
	}
	shared_func<SSetPlayerLevelAck> fnAck_(new SSetPlayerLevelAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_SetPlayerLevel(wServerNo, strName, qwUserID, wLevel, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CPHPProtSvr::SSetPlayerVIPLevelAck::SSetPlayerVIPLevelAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID), 
			eOptResult((EOptResult)0) { }

void CPHPProtSvr::SSetPlayerVIPLevelAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -23;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (INT8&)eOptResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 90, Function: 23";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CPHPProtSvr::_DoRecv_SetPlayerVIPLevel(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT16 wServerNo = 0;
	std::string strName;
	UINT64 qwUserID = 0;
	EOptType eOptType = (EOptType)0;
	UINT32 wLevelOrGrowthValue = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> wServerNo >> strName >> qwUserID >> (INT8&)eOptType >> wLevelOrGrowthValue;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 90, Function: 23";
		return false;
	}
	shared_func<SSetPlayerVIPLevelAck> fnAck_(new SSetPlayerVIPLevelAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_SetPlayerVIPLevel(wServerNo, strName, qwUserID, eOptType, wLevelOrGrowthValue, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CPHPProtSvr::STaskManagerAck::STaskManagerAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID), 
			eOptResult((EOptResult)0) { }

void CPHPProtSvr::STaskManagerAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -24;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (INT8&)eOptResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 90, Function: 24";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CPHPProtSvr::_DoRecv_TaskManager(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT16 wServerNo = 0;
	std::string strUserID;
	std::string strName;
	EPHPTaskType ePHPTaskType = (EPHPTaskType)0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> wServerNo >> strUserID >> strName >> (UINT8&)ePHPTaskType;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 90, Function: 24";
		return false;
	}
	shared_func<STaskManagerAck> fnAck_(new STaskManagerAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_TaskManager(wServerNo, strUserID, strName, ePHPTaskType, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

bool CPHPProtSvr::_DoRecv_PlatformInfo(const char* pBuf_, UINT32 dwLen_)
{
	EPlatformType byPtType = (EPlatformType)0;
	EQQPlatformType byQQPtType = (EQQPlatformType)0;
	UINT8 byQQPtLv = 0;
	UINT8 byQQPtYearType = 0;
	UINT8 byQQPtLuxuryType = 0;
	std::string customPar1;
	std::string customPar2;
	std::string strOpenId;
	std::string strOpenKey;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> (UINT8&)byPtType >> (UINT8&)byQQPtType >> byQQPtLv >> byQQPtYearType >> byQQPtLuxuryType >> customPar1 >> customPar2 >> strOpenId >> strOpenKey;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 90, Function: 25";
		return false;
	}
	OnRecv_PlatformInfo(byPtType, byQQPtType, byQQPtLv, byQQPtYearType, byQQPtLuxuryType, customPar1, customPar2, strOpenId, strOpenKey);
	return true;
}

CPHPProtSvr::SGetTaskStateAck::SGetTaskStateAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID), 
			wServerNo(0), eTaskState((ETaskState)0) { }

void CPHPProtSvr::SGetTaskStateAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -25;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << wServerNo << (UINT8&)eTaskState;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 90, Function: 26";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CPHPProtSvr::_DoRecv_GetTaskState(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT16 wServerNo = 0;
	UINT64 qwUserID = 0;
	UINT32 dwTaskID = 0;
	UINT8 byStep = 0;
	ETaskOpt eTaskOpt = (ETaskOpt)0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> wServerNo >> qwUserID >> dwTaskID >> byStep >> (UINT8&)eTaskOpt;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 90, Function: 26";
		return false;
	}
	shared_func<SGetTaskStateAck> fnAck_(new SGetTaskStateAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetTaskState(wServerNo, qwUserID, dwTaskID, byStep, eTaskOpt, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CPHPProtSvr::SSynWeiweiPersonNumAck::SSynWeiweiPersonNumAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID), 
			eOptResult((EOptResult)0) { }

void CPHPProtSvr::SSynWeiweiPersonNumAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -26;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (INT8&)eOptResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 90, Function: 27";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CPHPProtSvr::_DoRecv_SynWeiweiPersonNum(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT16 wServerNo = 0;
	UINT64 qwUserID = 0;
	UINT8 byType = 0;
	UINT32 dwCount = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> wServerNo >> qwUserID >> byType >> dwCount;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 90, Function: 27";
		return false;
	}
	shared_func<SSynWeiweiPersonNumAck> fnAck_(new SSynWeiweiPersonNumAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_SynWeiweiPersonNum(wServerNo, qwUserID, byType, dwCount, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CPHPProtSvr::SCheckCDKAck::SCheckCDKAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID), 
			eOptResult((EOptResult)0) { }

void CPHPProtSvr::SCheckCDKAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -27;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (INT8&)eOptResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 90, Function: 28";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CPHPProtSvr::_DoRecv_CheckCDK(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT16 wServerNo = 0;
	UINT64 qwUserID = 0;
	std::string strCDK;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> wServerNo >> qwUserID >> strCDK;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 90, Function: 28";
		return false;
	}
	shared_func<SCheckCDKAck> fnAck_(new SCheckCDKAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_CheckCDK(wServerNo, qwUserID, strCDK, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CPHPProtSvr::SSynQQAlarmAck::SSynQQAlarmAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID), 
			eOptResult((EOptResult)0) { }

void CPHPProtSvr::SSynQQAlarmAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -28;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (INT8&)eOptResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 90, Function: 29";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CPHPProtSvr::_DoRecv_SynQQAlarm(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT16 wServerNo = 0;
	UINT64 qwUserID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> wServerNo >> qwUserID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 90, Function: 29";
		return false;
	}
	shared_func<SSynQQAlarmAck> fnAck_(new SSynQQAlarmAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_SynQQAlarm(wServerNo, qwUserID, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CPHPProtSvr::SModifyChestAck::SModifyChestAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID), 
			eOptResult((EOptResult)0) { }

void CPHPProtSvr::SModifyChestAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -29;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (INT8&)eOptResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 90, Function: 30";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CPHPProtSvr::_DoRecv_ModifyChest(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	SChestInfo sInfo;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> sInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 90, Function: 30";
		return false;
	}
	shared_func<SModifyChestAck> fnAck_(new SModifyChestAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_ModifyChest(sInfo, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CPHPProtSvr::SSetPoolAck::SSetPoolAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID), 
			eOptResult((EOptResult)0) { }

void CPHPProtSvr::SSetPoolAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -30;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (INT8&)eOptResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 90, Function: 31";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CPHPProtSvr::_DoRecv_SetPool(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT8 byType = 0;
	UINT32 dwValue = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> byType >> dwValue;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 90, Function: 31";
		return false;
	}
	shared_func<SSetPoolAck> fnAck_(new SSetPoolAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_SetPool(byType, dwValue, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CPHPProtSvr::SGetLoginDaysAck::SGetLoginDaysAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID), 
			dwDays(0), eOptResult((EOptResult)0) { }

void CPHPProtSvr::SGetLoginDaysAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -31;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << dwDays << (INT8&)eOptResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 90, Function: 32";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CPHPProtSvr::_DoRecv_GetLoginDays(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT16 wServerNo = 0;
	UINT64 qwUserID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> wServerNo >> qwUserID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 90, Function: 32";
		return false;
	}
	shared_func<SGetLoginDaysAck> fnAck_(new SGetLoginDaysAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetLoginDays(wServerNo, qwUserID, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CPHPProtSvr::SSendQQGroupMsgAck::SSendQQGroupMsgAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID), 
			eOptResult((EOptResult)0) { }

void CPHPProtSvr::SSendQQGroupMsgAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -32;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (INT8&)eOptResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 90, Function: 33";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CPHPProtSvr::_DoRecv_SendQQGroupMsg(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT64 qwGroupUserID = 0;
	UINT16 wServerNo = 0;
	UINT64 qwUserID = 0;
	std::string strChatMsg;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> qwGroupUserID >> wServerNo >> qwUserID >> strChatMsg;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 90, Function: 33";
		return false;
	}
	shared_func<SSendQQGroupMsgAck> fnAck_(new SSendQQGroupMsgAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_SendQQGroupMsg(qwGroupUserID, wServerNo, qwUserID, strChatMsg, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CPHPProtSvr::SSendTitleAck::SSendTitleAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID), 
			eOptResult((EOptResult)0) { }

void CPHPProtSvr::SSendTitleAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -33;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (INT8&)eOptResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 90, Function: 34";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CPHPProtSvr::_DoRecv_SendTitle(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT16 wServerNo = 0;
	UINT64 qwUserID = 0;
	UINT16 wTitleID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> wServerNo >> qwUserID >> wTitleID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 90, Function: 34";
		return false;
	}
	shared_func<SSendTitleAck> fnAck_(new SSendTitleAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_SendTitle(wServerNo, qwUserID, wTitleID, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

bool CPHPProtSvr::_DoRecv_TestPHP(const char* pBuf_, UINT32 dwLen_)
{
	OnRecv_TestPHP();
	return true;
}

} //namespace NPHPProt
