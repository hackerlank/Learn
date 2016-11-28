/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    EquipTrumpProt.cpp
//  Purpose:      道具相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "EquipTrumpProtSvr.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NEquipTrumpProt
{

CEquipTrumpProtSvr::THandleFunc CEquipTrumpProtSvr::_HandleFuncs[] =
{
	&CEquipTrumpProtSvr::_DoRecv_GetAllEquipTrump, //FuncID: 1
	&CEquipTrumpProtSvr::_DoRecv_Wear, //FuncID: 2
	&CEquipTrumpProtSvr::_DoRecv_WearOneKey, //FuncID: 3
	&CEquipTrumpProtSvr::_DoRecv_TakeOff, //FuncID: 4
	&CEquipTrumpProtSvr::_DoRecv_Swap, //FuncID: 5
	&CEquipTrumpProtSvr::_DoRecv_MergeEquipTrump, //FuncID: 6
	&CEquipTrumpProtSvr::_DoRecv_BreakEquipTrump, //FuncID: 7
	&CEquipTrumpProtSvr::_DoRecv_Intensify, //FuncID: 8
	&CEquipTrumpProtSvr::_DoRecv_IntensifyOneKey, //FuncID: 9
	&CEquipTrumpProtSvr::_DoRecv_ShuffleResult, //FuncID: 10
};

bool CEquipTrumpProtSvr::HandleMessage(const char* pBuf, UINT32 dwLen)
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

//发送：当前玩家角色的装备法宝通知
bool CEquipTrumpProtSvr::Send_EquipTrumpNotify(
	UINT64 qwOwnerID, //散仙唯一ID
	EEquipTrumpSlotType eSlotType, //装备法宝位类型
	const NItemProt::TVecEquipTrump& vecEquipTrump //当前装备法宝的列表
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << qwOwnerID << (INT8&)eSlotType << vecEquipTrump;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 30, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CEquipTrumpProtSvr::SendClt_EquipTrumpNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT64 qwOwnerID, //散仙唯一ID
	EEquipTrumpSlotType eSlotType, //装备法宝位类型
	const NItemProt::TVecEquipTrump& vecEquipTrump //当前装备法宝的列表
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << qwOwnerID << (INT8&)eSlotType << vecEquipTrump;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 30, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CEquipTrumpProtSvr::BuildPkg_EquipTrumpNotify(
	UINT64 qwOwnerID, //散仙唯一ID
	EEquipTrumpSlotType eSlotType, //装备法宝位类型
	const NItemProt::TVecEquipTrump& vecEquipTrump //当前装备法宝的列表
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << qwOwnerID << (INT8&)eSlotType << vecEquipTrump;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 30, Function: 1";
		_strPkg.clear();
	}
	return _strPkg;
}

CEquipTrumpProtSvr::SGetAllEquipTrumpAck::SGetAllEquipTrumpAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID) { }

void CEquipTrumpProtSvr::SGetAllEquipTrumpAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -1;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << vecEquipTrump;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 30, Function: 1";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CEquipTrumpProtSvr::_DoRecv_GetAllEquipTrump(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT64 qwOwnerID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> qwOwnerID;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 30, Function: 1";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SGetAllEquipTrumpAck> fnAck_(new SGetAllEquipTrumpAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetAllEquipTrump(qwOwnerID, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CEquipTrumpProtSvr::SWearAck::SWearAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((EEquipTrumpResult)0) { }

void CEquipTrumpProtSvr::SWearAck::SendReturn(bool bRet_)
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
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 30, Function: 2";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CEquipTrumpProtSvr::_DoRecv_Wear(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT64 qwOwnerID = 0;
	UINT64 qwInstID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> qwOwnerID >> qwInstID;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 30, Function: 2";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SWearAck> fnAck_(new SWearAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_Wear(qwOwnerID, qwInstID, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CEquipTrumpProtSvr::SWearOneKeyAck::SWearOneKeyAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((EEquipTrumpResult)0) { }

void CEquipTrumpProtSvr::SWearOneKeyAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -3;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 30, Function: 3";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CEquipTrumpProtSvr::_DoRecv_WearOneKey(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT64 qwOwnerID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> qwOwnerID;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 30, Function: 3";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SWearOneKeyAck> fnAck_(new SWearOneKeyAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_WearOneKey(qwOwnerID, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CEquipTrumpProtSvr::STakeOffAck::STakeOffAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((EEquipTrumpResult)0) { }

void CEquipTrumpProtSvr::STakeOffAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -4;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 30, Function: 4";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CEquipTrumpProtSvr::_DoRecv_TakeOff(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT64 qwInstID = 0;
	INT16 wIndex = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> qwInstID >> wIndex;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 30, Function: 4";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<STakeOffAck> fnAck_(new STakeOffAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_TakeOff(qwInstID, wIndex, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CEquipTrumpProtSvr::SSwapAck::SSwapAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((EEquipTrumpResult)0) { }

void CEquipTrumpProtSvr::SSwapAck::SendReturn(bool bRet_)
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
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 30, Function: 5";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CEquipTrumpProtSvr::_DoRecv_Swap(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT64 qwOwnerID = 0;
	UINT64 qwInstID = 0;
	INT16 wIndex = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> qwOwnerID >> qwInstID >> wIndex;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 30, Function: 5";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SSwapAck> fnAck_(new SSwapAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_Swap(qwOwnerID, qwInstID, wIndex, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CEquipTrumpProtSvr::SMergeEquipTrumpAck::SMergeEquipTrumpAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((EEquipTrumpMergeResult)0) { }

void CEquipTrumpProtSvr::SMergeEquipTrumpAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -6;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eResult << vecItem;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 30, Function: 6";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CEquipTrumpProtSvr::_DoRecv_MergeEquipTrump(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT16 wItemID = 0;
	UINT16 wCount = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> wItemID >> wCount;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 30, Function: 6";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SMergeEquipTrumpAck> fnAck_(new SMergeEquipTrumpAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_MergeEquipTrump(wItemID, wCount, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CEquipTrumpProtSvr::SBreakEquipTrumpAck::SBreakEquipTrumpAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((EEquipTrumpBreakResult)0) { }

void CEquipTrumpProtSvr::SBreakEquipTrumpAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -7;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eResult << vecItem;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 30, Function: 7";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CEquipTrumpProtSvr::_DoRecv_BreakEquipTrump(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	TVecUINT64 vecInstID;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> vecInstID;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 30, Function: 7";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SBreakEquipTrumpAck> fnAck_(new SBreakEquipTrumpAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_BreakEquipTrump(vecInstID, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CEquipTrumpProtSvr::SIntensifyAck::SIntensifyAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			bSucess(false), eResult((EEquipTrumpIntensifyResult)0) { }

void CEquipTrumpProtSvr::SIntensifyAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -8;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << bSucess << (UINT8&)eResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 30, Function: 8";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CEquipTrumpProtSvr::_DoRecv_Intensify(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT64 qwInstID = 0;
	ETIntensifyType eType = (ETIntensifyType)0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> qwInstID >> (INT8&)eType;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 30, Function: 8";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SIntensifyAck> fnAck_(new SIntensifyAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_Intensify(qwInstID, eType, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CEquipTrumpProtSvr::SIntensifyOneKeyAck::SIntensifyOneKeyAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			bSucess(false), dwIntensifyCount(0), eResult((EEquipTrumpIntensifyResult)0) { }

void CEquipTrumpProtSvr::SIntensifyOneKeyAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -9;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << bSucess << dwIntensifyCount << (UINT8&)eResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 30, Function: 9";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CEquipTrumpProtSvr::_DoRecv_IntensifyOneKey(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT64 qwInstID = 0;
	ETIntensifyType eType = (ETIntensifyType)0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> qwInstID >> (INT8&)eType;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 30, Function: 9";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SIntensifyOneKeyAck> fnAck_(new SIntensifyOneKeyAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_IntensifyOneKey(qwInstID, eType, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CEquipTrumpProtSvr::SShuffleResultAck::SShuffleResultAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((EEquipTrumpShuffleResult)0) { }

void CEquipTrumpProtSvr::SShuffleResultAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -10;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 30, Function: 10";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CEquipTrumpProtSvr::_DoRecv_ShuffleResult(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT64 qwInstID = 0;
	UINT32 dwLock = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> qwInstID >> dwLock;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 30, Function: 10";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SShuffleResultAck> fnAck_(new SShuffleResultAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_ShuffleResult(qwInstID, dwLock, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

} //namespace NEquipTrumpProt
