/************************************************************************
//  工具自动生成的客户端协议代码(UTF-8 With BOM)
//  File Name:    Game2CenterDemonTower.cpp
//  Purpose:      GameServer到CenterServer关于镇妖塔的通信协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "Game2CenterDemonTowerClt.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NGame2CenterDemonTower
{

CGame2CenterDemonTowerClt::THandleFunc CGame2CenterDemonTowerClt::_ReturnFuncs[] =
{
	&CGame2CenterDemonTowerClt::_DoReturn_GetAttackedLayerInfo, //FuncID: -1
};

CGame2CenterDemonTowerClt::THandleFunc CGame2CenterDemonTowerClt::_HandleFuncs[] =
{
	&CGame2CenterDemonTowerClt::_DoRecv_EnterDemonTower, //FuncID: 1
	&CGame2CenterDemonTowerClt::_DoRecv_LeaveDemonTower, //FuncID: 2
	&CGame2CenterDemonTowerClt::_DoRecv_TakeDailyPrize, //FuncID: 3
	&CGame2CenterDemonTowerClt::_DoRecv_Attacked, //FuncID: 4
};

CGame2CenterDemonTowerClt::TTimeOutFunc CGame2CenterDemonTowerClt::_TimeoutFuncs[] =
{
	&CGame2CenterDemonTowerClt::_OnTimeOut_GetAttackedLayerInfo, //FuncID: 1
};

bool CGame2CenterDemonTowerClt::HandleMessage(const char* pBuf, UINT32 dwLen)
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

void CGame2CenterDemonTowerClt::OnTimeOut(UINT8 byFuncID, UINT32 dwSessionID)
{
	if(byFuncID == 0 || byFuncID > (UINT8)ARRAYSIZE(_TimeoutFuncs))
		return;
	(this->*_TimeoutFuncs[byFuncID - 1])(dwSessionID);
}

//发送：玩家进入镇妖塔
bool CGame2CenterDemonTowerClt::Send_OnEnterDemonTower(
	const SDemonTowerEnterPlayer& oDemonTowerEnterPlayer //进入镇妖塔玩家信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << oDemonTowerEnterPlayer;
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

bool CGame2CenterDemonTowerClt::SendSvr_OnEnterDemonTower(const UINT32* pSvrID_, UINT8 byCnt_,
	const SDemonTowerEnterPlayer& oDemonTowerEnterPlayer //进入镇妖塔玩家信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << oDemonTowerEnterPlayer;
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

std::string& CGame2CenterDemonTowerClt::BuildPkg_OnEnterDemonTower(
	const SDemonTowerEnterPlayer& oDemonTowerEnterPlayer //进入镇妖塔玩家信息
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << oDemonTowerEnterPlayer;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 73, Function: 1";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：玩家离开镇妖塔
bool CGame2CenterDemonTowerClt::Send_OnLeaveDemonTower(
	UINT64 qwUserID //玩家账号
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUserID;
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

bool CGame2CenterDemonTowerClt::SendSvr_OnLeaveDemonTower(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwUserID //玩家账号
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUserID;
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

std::string& CGame2CenterDemonTowerClt::BuildPkg_OnLeaveDemonTower(
	UINT64 qwUserID //玩家账号
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUserID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 73, Function: 2";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：镇妖塔过关
bool CGame2CenterDemonTowerClt::Send_OnPassDemonTower(
	UINT64 qwUserID, //玩家账号
	UINT16 wFloorID, //过关层数
	UINT16 wMonsterColor, //怪物颜色
	const std::string& strMonsterName //封印怪物
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUserID << wFloorID << wMonsterColor << strMonsterName;
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

bool CGame2CenterDemonTowerClt::SendSvr_OnPassDemonTower(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwUserID, //玩家账号
	UINT16 wFloorID, //过关层数
	UINT16 wMonsterColor, //怪物颜色
	const std::string& strMonsterName //封印怪物
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUserID << wFloorID << wMonsterColor << strMonsterName;
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

std::string& CGame2CenterDemonTowerClt::BuildPkg_OnPassDemonTower(
	UINT64 qwUserID, //玩家账号
	UINT16 wFloorID, //过关层数
	UINT16 wMonsterColor, //怪物颜色
	const std::string& strMonsterName //封印怪物
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUserID << wFloorID << wMonsterColor << strMonsterName;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 73, Function: 3";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：击败锁妖塔怪物
bool CGame2CenterDemonTowerClt::Send_OnKillMonster(
	const SDemonTowerPassPlayer& oDemonTowerPassPlayer //镇妖塔玩家击败怪物信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << oDemonTowerPassPlayer;
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

bool CGame2CenterDemonTowerClt::SendSvr_OnKillMonster(const UINT32* pSvrID_, UINT8 byCnt_,
	const SDemonTowerPassPlayer& oDemonTowerPassPlayer //镇妖塔玩家击败怪物信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << oDemonTowerPassPlayer;
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

std::string& CGame2CenterDemonTowerClt::BuildPkg_OnKillMonster(
	const SDemonTowerPassPlayer& oDemonTowerPassPlayer //镇妖塔玩家击败怪物信息
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << oDemonTowerPassPlayer;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 73, Function: 4";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：19点重置事件
bool CGame2CenterDemonTowerClt::Send_OnPlayerReset(
	UINT64 qwUserID //玩家账号
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 5;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUserID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 73, Function: 5";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterDemonTowerClt::SendSvr_OnPlayerReset(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwUserID //玩家账号
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 5;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUserID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 73, Function: 5";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGame2CenterDemonTowerClt::BuildPkg_OnPlayerReset(
	UINT64 qwUserID //玩家账号
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 5;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUserID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 73, Function: 5";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：玩家进入下一层
bool CGame2CenterDemonTowerClt::Send_OnPlayerEnterNextFloor(
	UINT64 qwUserID //玩家账号
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 6;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUserID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 73, Function: 6";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterDemonTowerClt::SendSvr_OnPlayerEnterNextFloor(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwUserID //玩家账号
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 6;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUserID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 73, Function: 6";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGame2CenterDemonTowerClt::BuildPkg_OnPlayerEnterNextFloor(
	UINT64 qwUserID //玩家账号
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 6;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUserID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 73, Function: 6";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：玩家进入请求
bool CGame2CenterDemonTowerClt::Send_PlayerEnterFloorRequest(
	UINT64 qwUserID, //玩家账号
	UINT32 dwFloorID //层数
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 7;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUserID << dwFloorID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 73, Function: 7";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterDemonTowerClt::SendSvr_PlayerEnterFloorRequest(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwUserID, //玩家账号
	UINT32 dwFloorID //层数
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 7;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUserID << dwFloorID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 73, Function: 7";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGame2CenterDemonTowerClt::BuildPkg_PlayerEnterFloorRequest(
	UINT64 qwUserID, //玩家账号
	UINT32 dwFloorID //层数
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 7;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUserID << dwFloorID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 73, Function: 7";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：获取玩家被攻击信息列表
bool CGame2CenterDemonTowerClt::Send_GetAttackedLayerInfo(
	UINT64 qwUserID, //玩家账号
	const NDemonTower::TVecDemonToweAttackedInfo& oAttackedList, //被攻击列表
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT64 qwUserID, //(返回值)玩家账号
		const NDemonTower::TVecDemonToweAttackedInfo& oAttackedList //(返回值)被攻击列表
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
	const UINT8 byFuncID_ = 8;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwUserID << oAttackedList;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 73, Function: 8";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterDemonTowerClt::SendSvr_GetAttackedLayerInfo(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwUserID, //玩家账号
	const NDemonTower::TVecDemonToweAttackedInfo& oAttackedList, //被攻击列表
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT64 qwUserID, //(返回值)玩家账号
		const NDemonTower::TVecDemonToweAttackedInfo& oAttackedList //(返回值)被攻击列表
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
	const UINT8 byFuncID_ = 8;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwUserID << oAttackedList;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 73, Function: 8";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

bool CGame2CenterDemonTowerClt::_DoRecv_EnterDemonTower(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 73, Function: 1";
		return false;
	}
	OnRecv_EnterDemonTower(qwUserID, dwFloorID);
	return true;
}

bool CGame2CenterDemonTowerClt::_DoRecv_LeaveDemonTower(const char* pBuf_, UINT32 dwLen_)
{
	UINT64 qwUsrID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> qwUsrID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 73, Function: 2";
		return false;
	}
	OnRecv_LeaveDemonTower(qwUsrID);
	return true;
}

CGame2CenterDemonTowerClt::STakeDailyPrizeAck::STakeDailyPrizeAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID) { }

void CGame2CenterDemonTowerClt::STakeDailyPrizeAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -1;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 73, Function: 3";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CGame2CenterDemonTowerClt::_DoRecv_TakeDailyPrize(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT64 qwUsrID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> qwUsrID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 73, Function: 3";
		return false;
	}
	shared_func<STakeDailyPrizeAck> fnAck_(new STakeDailyPrizeAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_TakeDailyPrize(qwUsrID, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

bool CGame2CenterDemonTowerClt::_DoRecv_Attacked(const char* pBuf_, UINT32 dwLen_)
{
	UINT64 qwUsrID = 0;
	NDemonTower::SDemonToweAttackedInfo oAttacker;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> qwUsrID >> oAttacker;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 73, Function: 4";
		return false;
	}
	OnRecv_Attacked(qwUsrID, oAttacker);
	return true;
}

bool CGame2CenterDemonTowerClt::_DoReturn_GetAttackedLayerInfo(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	bool bRet_ = false;
	UINT64 qwUserID = 0;
	NDemonTower::TVecDemonToweAttackedInfo oAttackedList;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> bRet_ >> qwUserID >> oAttackedList;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoReturn exception: " << szExcept << ", Protocol: 73, Function: 8";
		return false;
	}
	UINT8 byRet_ = 0;
	if(!bRet_)
		byRet_ = 1;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT64 qwUserID, //(返回值)玩家账号
		const NDemonTower::TVecDemonToweAttackedInfo& oAttackedList //(返回值)被攻击列表
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID_));
	if(pSessData_ == NULL)
		return false;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(byRet_, qwUserID, oAttackedList);
	if(_pSessionMgr != NULL)
		_pSessionMgr->DelSession(dwSessionID_);
	return true;
}

void CGame2CenterDemonTowerClt::_OnTimeOut_GetAttackedLayerInfo(UINT32 dwSessionID)
{
	UINT64 qwUserID = 0;
	NDemonTower::TVecDemonToweAttackedInfo oAttackedList;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT64 qwUserID, //(返回值)玩家账号
		const NDemonTower::TVecDemonToweAttackedInfo& oAttackedList //(返回值)被攻击列表
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID));
	if(pSessData_ == NULL)
		return;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(2, qwUserID, oAttackedList);
}

} //namespace NGame2CenterDemonTower
