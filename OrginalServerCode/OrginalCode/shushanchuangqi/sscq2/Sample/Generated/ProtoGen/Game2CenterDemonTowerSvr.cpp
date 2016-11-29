/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    Game2CenterDemonTower.cpp
//  Purpose:      GameServer到CenterServer关于镇妖塔的通信协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "Game2CenterDemonTowerSvr.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NGame2CenterDemonTower
{

CGame2CenterDemonTowerSvr::THandleFunc CGame2CenterDemonTowerSvr::_ReturnFuncs[] =
{
	&CGame2CenterDemonTowerSvr::_DoReturn_TakeDailyPrize, //FuncID: -1
};

CGame2CenterDemonTowerSvr::THandleFunc CGame2CenterDemonTowerSvr::_HandleFuncs[] =
{
	&CGame2CenterDemonTowerSvr::_DoRecv_OnEnterDemonTower, //FuncID: 1
	&CGame2CenterDemonTowerSvr::_DoRecv_OnLeaveDemonTower, //FuncID: 2
	&CGame2CenterDemonTowerSvr::_DoRecv_OnPassDemonTower, //FuncID: 3
	&CGame2CenterDemonTowerSvr::_DoRecv_OnKillMonster, //FuncID: 4
	&CGame2CenterDemonTowerSvr::_DoRecv_OnPlayerReset, //FuncID: 5
	&CGame2CenterDemonTowerSvr::_DoRecv_OnPlayerEnterNextFloor, //FuncID: 6
	&CGame2CenterDemonTowerSvr::_DoRecv_PlayerEnterFloorRequest, //FuncID: 7
	&CGame2CenterDemonTowerSvr::_DoRecv_GetAttackedLayerInfo, //FuncID: 8
};

CGame2CenterDemonTowerSvr::TTimeOutFunc CGame2CenterDemonTowerSvr::_TimeoutFuncs[] =
{
	&CGame2CenterDemonTowerSvr::_OnTimeOut_TakeDailyPrize, //FuncID: 1
};

bool CGame2CenterDemonTowerSvr::HandleMessage(const char* pBuf, UINT32 dwLen)
{
	if(pBuf == NULL || dwLen == 0)
		return false;
	INT8 byFuncID = pBuf[0];
	if(byFuncID == 0 || byFuncID > (INT8)ARRAYSIZE(_HandleFuncs)
		 || byFuncID < -(INT8)ARRAYSIZE(_ReturnFuncs))
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
	else
	{
		byFuncID = -1 - byFuncID;
		if(_ReturnFuncs[static_cast<UINT8>(byFuncID)] != NULL)
			return (this->*_ReturnFuncs[static_cast<UINT8>(byFuncID)])(pBuf, dwLen);
	}
	return true;
}

void CGame2CenterDemonTowerSvr::OnTimeOut(UINT8 byFuncID, UINT32 dwSessionID)
{
	if(byFuncID == 0 || byFuncID > (UINT8)ARRAYSIZE(_TimeoutFuncs))
		return;
	(this->*_TimeoutFuncs[byFuncID - 1])(dwSessionID);
}

//发送：玩家请求进入镇妖塔
bool CGame2CenterDemonTowerSvr::Send_EnterDemonTower(
	UINT64 qwUserID, //帐号ID
	UINT32 dwFloorID //层数
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUserID << dwFloorID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 73, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterDemonTowerSvr::SendSvr_EnterDemonTower(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwUserID, //帐号ID
	UINT32 dwFloorID //层数
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUserID << dwFloorID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 73, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGame2CenterDemonTowerSvr::BuildPkg_EnterDemonTower(
	UINT64 qwUserID, //帐号ID
	UINT32 dwFloorID //层数
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUserID << dwFloorID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 73, Function: 1";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：玩家请求离开镇妖塔
bool CGame2CenterDemonTowerSvr::Send_LeaveDemonTower(
	UINT64 qwUsrID //帐号ID
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 73, Function: 2";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterDemonTowerSvr::SendSvr_LeaveDemonTower(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwUsrID //帐号ID
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 73, Function: 2";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGame2CenterDemonTowerSvr::BuildPkg_LeaveDemonTower(
	UINT64 qwUsrID //帐号ID
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 73, Function: 2";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：获取每日魂值奖励
bool CGame2CenterDemonTowerSvr::Send_TakeDailyPrize(
	UINT64 qwUsrID, //帐号ID
	boost::function<void (UINT8 byRet_ //0为成功，1为失败，2为超时
	)> fnOnReturn_ //返回时的回调函数
)
{
	if(_pSessionMgr == NULL)
	{
		LOG_CRI << "_pSessionMgr == NULL";		return false;
	}
	UINT32 dwSessionID_ = _pSessionMgr->GetNewSession(*this, 1);
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_(new TSessData(fnOnReturn_));
	_pSessionMgr->StoreData(dwSessionID_, pSessData_);
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwUsrID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 73, Function: 3";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterDemonTowerSvr::SendSvr_TakeDailyPrize(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwUsrID, //帐号ID
	boost::function<void (UINT8 byRet_ //0为成功，1为失败，2为超时
	)> fnOnReturn_ //返回时的回调函数
)
{
	if(_pSessionMgr == NULL)
	{
		LOG_CRI << "_pSessionMgr == NULL";		return false;
	}
	UINT32 dwSessionID_ = _pSessionMgr->GetNewSession(*this, 1);
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_(new TSessData(fnOnReturn_));
	_pSessionMgr->StoreData(dwSessionID_, pSessData_);
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwUsrID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 73, Function: 3";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

//发送：被攻击信息
bool CGame2CenterDemonTowerSvr::Send_Attacked(
	UINT64 qwUsrID, //帐号ID
	const NDemonTower::SDemonToweAttackedInfo& oAttacker //被攻击信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << oAttacker;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 73, Function: 4";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterDemonTowerSvr::SendSvr_Attacked(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwUsrID, //帐号ID
	const NDemonTower::SDemonToweAttackedInfo& oAttacker //被攻击信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << oAttacker;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 73, Function: 4";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGame2CenterDemonTowerSvr::BuildPkg_Attacked(
	UINT64 qwUsrID, //帐号ID
	const NDemonTower::SDemonToweAttackedInfo& oAttacker //被攻击信息
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << oAttacker;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 73, Function: 4";
		_strPkg.clear();
	}
	return _strPkg;
}

bool CGame2CenterDemonTowerSvr::_DoRecv_OnEnterDemonTower(const char* pBuf_, UINT32 dwLen_)
{
	SDemonTowerEnterPlayer oDemonTowerEnterPlayer;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> oDemonTowerEnterPlayer;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 73, Function: 1";
		return false;
	}
	OnRecv_OnEnterDemonTower(oDemonTowerEnterPlayer);
	return true;
}

bool CGame2CenterDemonTowerSvr::_DoRecv_OnLeaveDemonTower(const char* pBuf_, UINT32 dwLen_)
{
	UINT64 qwUserID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> qwUserID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 73, Function: 2";
		return false;
	}
	OnRecv_OnLeaveDemonTower(qwUserID);
	return true;
}

bool CGame2CenterDemonTowerSvr::_DoRecv_OnPassDemonTower(const char* pBuf_, UINT32 dwLen_)
{
	UINT64 qwUserID = 0;
	UINT16 wFloorID = 0;
	UINT16 wMonsterColor = 0;
	std::string strMonsterName;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> qwUserID >> wFloorID >> wMonsterColor >> strMonsterName;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 73, Function: 3";
		return false;
	}
	OnRecv_OnPassDemonTower(qwUserID, wFloorID, wMonsterColor, strMonsterName);
	return true;
}

bool CGame2CenterDemonTowerSvr::_DoRecv_OnKillMonster(const char* pBuf_, UINT32 dwLen_)
{
	SDemonTowerPassPlayer oDemonTowerPassPlayer;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> oDemonTowerPassPlayer;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 73, Function: 4";
		return false;
	}
	OnRecv_OnKillMonster(oDemonTowerPassPlayer);
	return true;
}

bool CGame2CenterDemonTowerSvr::_DoRecv_OnPlayerReset(const char* pBuf_, UINT32 dwLen_)
{
	UINT64 qwUserID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> qwUserID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 73, Function: 5";
		return false;
	}
	OnRecv_OnPlayerReset(qwUserID);
	return true;
}

bool CGame2CenterDemonTowerSvr::_DoRecv_OnPlayerEnterNextFloor(const char* pBuf_, UINT32 dwLen_)
{
	UINT64 qwUserID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> qwUserID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 73, Function: 6";
		return false;
	}
	OnRecv_OnPlayerEnterNextFloor(qwUserID);
	return true;
}

bool CGame2CenterDemonTowerSvr::_DoRecv_PlayerEnterFloorRequest(const char* pBuf_, UINT32 dwLen_)
{
	UINT64 qwUserID = 0;
	UINT32 dwFloorID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> qwUserID >> dwFloorID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 73, Function: 7";
		return false;
	}
	OnRecv_PlayerEnterFloorRequest(qwUserID, dwFloorID);
	return true;
}

CGame2CenterDemonTowerSvr::SGetAttackedLayerInfoAck::SGetAttackedLayerInfoAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID), 
			qwUserID(0) { }

void CGame2CenterDemonTowerSvr::SGetAttackedLayerInfoAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -1;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << qwUserID << oAttackedList;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 73, Function: 8";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CGame2CenterDemonTowerSvr::_DoRecv_GetAttackedLayerInfo(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT64 qwUserID = 0;
	NDemonTower::TVecDemonToweAttackedInfo oAttackedList;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> qwUserID >> oAttackedList;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 73, Function: 8";
		return false;
	}
	shared_func<SGetAttackedLayerInfoAck> fnAck_(new SGetAttackedLayerInfoAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetAttackedLayerInfo(qwUserID, oAttackedList, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

bool CGame2CenterDemonTowerSvr::_DoReturn_TakeDailyPrize(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	bool bRet_ = false;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> bRet_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoReturn exception: " << szExcept << ", Protocol: 73, Function: 3";
		return false;
	}
	UINT8 byRet_ = 0;
	if(!bRet_)
		byRet_ = 1;
	boost::function<void (UINT8 byRet_ //0为成功，1为失败，2为超时
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID_));
	if(pSessData_ == NULL)
		return false;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(byRet_);
	if(_pSessionMgr != NULL)
		_pSessionMgr->DelSession(dwSessionID_);
	return true;
}

void CGame2CenterDemonTowerSvr::_OnTimeOut_TakeDailyPrize(UINT32 dwSessionID)
{
	boost::function<void (UINT8 byRet_ //0为成功，1为失败，2为超时
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID));
	if(pSessData_ == NULL)
		return;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(2);
}

} //namespace NGame2CenterDemonTower
