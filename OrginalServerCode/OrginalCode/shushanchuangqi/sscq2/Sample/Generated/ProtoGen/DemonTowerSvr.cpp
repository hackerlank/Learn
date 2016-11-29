/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    DemonTower.cpp
//  Purpose:      锁妖塔
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "DemonTowerSvr.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NDemonTower
{

CDemonTowerSvr::THandleFunc CDemonTowerSvr::_HandleFuncs[] =
{
	&CDemonTowerSvr::_DoRecv_EnterDemonTower, //FuncID: 1
	&CDemonTowerSvr::_DoRecv_LeaveDemonTower, //FuncID: 2
	&CDemonTowerSvr::_DoRecv_SealMonster, //FuncID: 3
	&CDemonTowerSvr::_DoRecv_UpgradeSoulSpace, //FuncID: 4
	&CDemonTowerSvr::_DoRecv_GetSoulSpace, //FuncID: 5
	&CDemonTowerSvr::_DoRecv_GetAttackedList, //FuncID: 6
	&CDemonTowerSvr::_DoRecv_TakeDayPrize, //FuncID: 7
	&CDemonTowerSvr::_DoRecv_TakeLayerPrize, //FuncID: 8
	&CDemonTowerSvr::_DoRecv_GetTopPrizeLayer, //FuncID: 9
	&CDemonTowerSvr::_DoRecv_ClearFightMonsterCd, //FuncID: 10
	&CDemonTowerSvr::_DoRecv_GetLayerPrized, //FuncID: 11
};

bool CDemonTowerSvr::HandleMessage(const char* pBuf, UINT32 dwLen)
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

//发送：升级魄空间通知
bool CDemonTowerSvr::Send_UpgradeSoulSpaceNotify(
	UINT32 dwSoulSpaceID, //魄空间类型ID(升级结果)
	UINT32 dwSoulSpaceLevel //魄空间等级(升级结果)
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSoulSpaceID << dwSoulSpaceLevel;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 70, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CDemonTowerSvr::SendClt_UpgradeSoulSpaceNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT32 dwSoulSpaceID, //魄空间类型ID(升级结果)
	UINT32 dwSoulSpaceLevel //魄空间等级(升级结果)
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSoulSpaceID << dwSoulSpaceLevel;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 70, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CDemonTowerSvr::BuildPkg_UpgradeSoulSpaceNotify(
	UINT32 dwSoulSpaceID, //魄空间类型ID(升级结果)
	UINT32 dwSoulSpaceLevel //魄空间等级(升级结果)
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSoulSpaceID << dwSoulSpaceLevel;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 70, Function: 1";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：魄空间列表
bool CDemonTowerSvr::Send_SoulSpaceListNotify(
	const TVecSpaceInfo& vecSpaceInfo //魄空间列表
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << vecSpaceInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 70, Function: 2";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CDemonTowerSvr::SendClt_SoulSpaceListNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	const TVecSpaceInfo& vecSpaceInfo //魄空间列表
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << vecSpaceInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 70, Function: 2";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CDemonTowerSvr::BuildPkg_SoulSpaceListNotify(
	const TVecSpaceInfo& vecSpaceInfo //魄空间列表
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << vecSpaceInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 70, Function: 2";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：每日重置奖励通知
bool CDemonTowerSvr::Send_DayPrizeResetNotify(
	UINT32 dwFloorID //层数
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << dwFloorID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 70, Function: 3";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CDemonTowerSvr::SendClt_DayPrizeResetNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT32 dwFloorID //层数
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << dwFloorID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 70, Function: 3";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CDemonTowerSvr::BuildPkg_DayPrizeResetNotify(
	UINT32 dwFloorID //层数
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << dwFloorID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 70, Function: 3";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：被攻击列表通知
bool CDemonTowerSvr::Send_AttackListNotify(
	const TVecDemonToweAttackedInfo& oDemonToweAttackedInfo //被攻击列表
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << oDemonToweAttackedInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 70, Function: 4";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CDemonTowerSvr::SendClt_AttackListNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	const TVecDemonToweAttackedInfo& oDemonToweAttackedInfo //被攻击列表
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << oDemonToweAttackedInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 70, Function: 4";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CDemonTowerSvr::BuildPkg_AttackListNotify(
	const TVecDemonToweAttackedInfo& oDemonToweAttackedInfo //被攻击列表
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << oDemonToweAttackedInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 70, Function: 4";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：被攻击通知(收到通知后拉取被攻击列表)
bool CDemonTowerSvr::Send_AttackChangedNotify(
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 5;
	try
	{
		ar << byProtID_ << byFuncID_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 70, Function: 5";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CDemonTowerSvr::SendClt_AttackChangedNotify(const UINT64* pUsrID_, UINT16 wCnt_
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 5;
	try
	{
		ar << byProtID_ << byFuncID_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 70, Function: 5";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CDemonTowerSvr::BuildPkg_AttackChangedNotify(
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 5;
	try
	{
		ar << byProtID_ << byFuncID_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 70, Function: 5";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：通关协议
bool CDemonTowerSvr::Send_FloorPassNotify(
	UINT32 dwFloorID //通关层数
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 6;
	try
	{
		ar << byProtID_ << byFuncID_ << dwFloorID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 70, Function: 6";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CDemonTowerSvr::SendClt_FloorPassNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT32 dwFloorID //通关层数
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 6;
	try
	{
		ar << byProtID_ << byFuncID_ << dwFloorID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 70, Function: 6";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CDemonTowerSvr::BuildPkg_FloorPassNotify(
	UINT32 dwFloorID //通关层数
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 6;
	try
	{
		ar << byProtID_ << byFuncID_ << dwFloorID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 70, Function: 6";
		_strPkg.clear();
	}
	return _strPkg;
}

CDemonTowerSvr::SEnterDemonTowerAck::SEnterDemonTowerAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			dwRet(0) { }

void CDemonTowerSvr::SEnterDemonTowerAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -1;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << dwRet;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 70, Function: 1";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CDemonTowerSvr::_DoRecv_EnterDemonTower(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT32 dwFloorID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> dwFloorID;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 70, Function: 1";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SEnterDemonTowerAck> fnAck_(new SEnterDemonTowerAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_EnterDemonTower(dwFloorID, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CDemonTowerSvr::SLeaveDemonTowerAck::SLeaveDemonTowerAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			dwRet(0) { }

void CDemonTowerSvr::SLeaveDemonTowerAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -2;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << dwRet;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 70, Function: 2";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CDemonTowerSvr::_DoRecv_LeaveDemonTower(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 70, Function: 2";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SLeaveDemonTowerAck> fnAck_(new SLeaveDemonTowerAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_LeaveDemonTower(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CDemonTowerSvr::SSealMonsterAck::SSealMonsterAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			dwRet(0) { }

void CDemonTowerSvr::SSealMonsterAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -3;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << dwRet;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 70, Function: 3";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CDemonTowerSvr::_DoRecv_SealMonster(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT32 dwFloorID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> dwFloorID;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 70, Function: 3";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SSealMonsterAck> fnAck_(new SSealMonsterAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_SealMonster(dwFloorID, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CDemonTowerSvr::SUpgradeSoulSpaceAck::SUpgradeSoulSpaceAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			dwRet(0) { }

void CDemonTowerSvr::SUpgradeSoulSpaceAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -4;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << dwRet;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 70, Function: 4";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CDemonTowerSvr::_DoRecv_UpgradeSoulSpace(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT32 dwSoulSpaceID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> dwSoulSpaceID;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 70, Function: 4";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SUpgradeSoulSpaceAck> fnAck_(new SUpgradeSoulSpaceAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_UpgradeSoulSpace(dwSoulSpaceID, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

bool CDemonTowerSvr::_DoRecv_GetSoulSpace(const char* pBuf_, UINT32 dwLen_)
{
	OnRecv_GetSoulSpace();
	return true;
}

bool CDemonTowerSvr::_DoRecv_GetAttackedList(const char* pBuf_, UINT32 dwLen_)
{
	OnRecv_GetAttackedList();
	return true;
}

CDemonTowerSvr::STakeDayPrizeAck::STakeDayPrizeAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			dwRet(0) { }

void CDemonTowerSvr::STakeDayPrizeAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -5;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << dwRet;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 70, Function: 7";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CDemonTowerSvr::_DoRecv_TakeDayPrize(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 70, Function: 7";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<STakeDayPrizeAck> fnAck_(new STakeDayPrizeAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_TakeDayPrize(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CDemonTowerSvr::STakeLayerPrizeAck::STakeLayerPrizeAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			dwRet(0), dwFloorID(0) { }

void CDemonTowerSvr::STakeLayerPrizeAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -6;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << dwRet << dwFloorID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 70, Function: 8";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CDemonTowerSvr::_DoRecv_TakeLayerPrize(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT32 dwFloorID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> dwFloorID;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 70, Function: 8";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<STakeLayerPrizeAck> fnAck_(new STakeLayerPrizeAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_TakeLayerPrize(dwFloorID, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CDemonTowerSvr::SGetTopPrizeLayerAck::SGetTopPrizeLayerAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			dwFloorID(0) { }

void CDemonTowerSvr::SGetTopPrizeLayerAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -7;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << dwFloorID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 70, Function: 9";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CDemonTowerSvr::_DoRecv_GetTopPrizeLayer(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 70, Function: 9";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SGetTopPrizeLayerAck> fnAck_(new SGetTopPrizeLayerAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetTopPrizeLayer(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CDemonTowerSvr::SClearFightMonsterCdAck::SClearFightMonsterCdAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			bRet(0) { }

void CDemonTowerSvr::SClearFightMonsterCdAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -8;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << bRet;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 70, Function: 10";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CDemonTowerSvr::_DoRecv_ClearFightMonsterCd(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 70, Function: 10";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SClearFightMonsterCdAck> fnAck_(new SClearFightMonsterCdAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_ClearFightMonsterCd(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CDemonTowerSvr::SGetLayerPrizedAck::SGetLayerPrizedAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID) { }

void CDemonTowerSvr::SGetLayerPrizedAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -9;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << vecFloorID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 70, Function: 11";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CDemonTowerSvr::_DoRecv_GetLayerPrized(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 70, Function: 11";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SGetLayerPrizedAck> fnAck_(new SGetLayerPrizedAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetLayerPrized(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

} //namespace NDemonTower
