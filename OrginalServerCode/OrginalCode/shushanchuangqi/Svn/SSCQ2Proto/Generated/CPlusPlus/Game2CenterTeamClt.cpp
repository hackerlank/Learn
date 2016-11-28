/************************************************************************
//  工具自动生成的客户端协议代码(UTF-8 With BOM)
//  File Name:    Game2CenterTeam.cpp
//  Purpose:      GameServer到CenterServer关于Team的通信协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "Game2CenterTeamClt.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NGame2CenterTeam
{

CGame2CenterTeamClt::THandleFunc CGame2CenterTeamClt::_HandleFuncs[] =
{
	&CGame2CenterTeamClt::_DoRecv_CanEnterCreateTeam, //FuncID: 1
	&CGame2CenterTeamClt::_DoRecv_SynTeam, //FuncID: 2
	&CGame2CenterTeamClt::_DoRecv_GetFighterFeatureByInsID, //FuncID: 3
	&CGame2CenterTeamClt::_DoRecv_GetPlayerBattleInfo, //FuncID: 4
	&CGame2CenterTeamClt::_DoRecv_StartBattle, //FuncID: 5
	&CGame2CenterTeamClt::_DoRecv_NoticeTeamReport, //FuncID: 6
};

bool CGame2CenterTeamClt::HandleMessage(const char* pBuf, UINT32 dwLen)
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

//发送：同步队伍成员
bool CGame2CenterTeamClt::Send_SynTeamFighter(
	UINT64 qwUsrID, //帐号ID
	const NTeamGS::TVecTeamFighter& vecFighter //战斗对象
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << vecFighter;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 57, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterTeamClt::SendSvr_SynTeamFighter(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwUsrID, //帐号ID
	const NTeamGS::TVecTeamFighter& vecFighter //战斗对象
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << vecFighter;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 57, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGame2CenterTeamClt::BuildPkg_SynTeamFighter(
	UINT64 qwUsrID, //帐号ID
	const NTeamGS::TVecTeamFighter& vecFighter //战斗对象
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << vecFighter;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 57, Function: 1";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：同步增加美女,如果原来有美女，替换
bool CGame2CenterTeamClt::Send_SynTeamAddBeauty(
	UINT64 qwUsrID, //帐号ID
	const NTeamGS::TVecTeamFighter& vecFighter //战斗对象
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << vecFighter;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 57, Function: 2";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterTeamClt::SendSvr_SynTeamAddBeauty(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwUsrID, //帐号ID
	const NTeamGS::TVecTeamFighter& vecFighter //战斗对象
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << vecFighter;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 57, Function: 2";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGame2CenterTeamClt::BuildPkg_SynTeamAddBeauty(
	UINT64 qwUsrID, //帐号ID
	const NTeamGS::TVecTeamFighter& vecFighter //战斗对象
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << vecFighter;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 57, Function: 2";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：同步删除美女
bool CGame2CenterTeamClt::Send_SynTeamDelBeauty(
	UINT64 qwUsrID //帐号ID
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 57, Function: 3";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterTeamClt::SendSvr_SynTeamDelBeauty(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwUsrID //帐号ID
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 57, Function: 3";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGame2CenterTeamClt::BuildPkg_SynTeamDelBeauty(
	UINT64 qwUsrID //帐号ID
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 57, Function: 3";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：同步奖励系数
bool CGame2CenterTeamClt::Send_SynRewardRate(
	UINT32 dwRewardRate //奖励系数万分比
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << dwRewardRate;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 57, Function: 4";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterTeamClt::SendSvr_SynRewardRate(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT32 dwRewardRate //奖励系数万分比
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << dwRewardRate;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 57, Function: 4";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGame2CenterTeamClt::BuildPkg_SynRewardRate(
	UINT32 dwRewardRate //奖励系数万分比
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << dwRewardRate;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 57, Function: 4";
		_strPkg.clear();
	}
	return _strPkg;
}

CGame2CenterTeamClt::SCanEnterCreateTeamAck::SCanEnterCreateTeamAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID), 
			eResult((NTeamGS::ETEAMResult)0) { }

void CGame2CenterTeamClt::SCanEnterCreateTeamAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -1;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eResult << vecFighter;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 57, Function: 1";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CGame2CenterTeamClt::_DoRecv_CanEnterCreateTeam(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT64 qwUsrID = 0;
	UINT8 byHeroNum = 0;
	UINT16 wDgnType = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> qwUsrID >> byHeroNum >> wDgnType;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 57, Function: 1";
		return false;
	}
	shared_func<SCanEnterCreateTeamAck> fnAck_(new SCanEnterCreateTeamAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_CanEnterCreateTeam(qwUsrID, byHeroNum, wDgnType, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

bool CGame2CenterTeamClt::_DoRecv_SynTeam(const char* pBuf_, UINT32 dwLen_)
{
	UINT64 qwUsrID = 0;
	EPlayerTeam eStatus = (EPlayerTeam)0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> qwUsrID >> (UINT8&)eStatus;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 57, Function: 2";
		return false;
	}
	OnRecv_SynTeam(qwUsrID, eStatus);
	return true;
}

CGame2CenterTeamClt::SGetFighterFeatureByInsIDAck::SGetFighterFeatureByInsIDAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID) { }

void CGame2CenterTeamClt::SGetFighterFeatureByInsIDAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -2;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << stFighter;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 57, Function: 3";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CGame2CenterTeamClt::_DoRecv_GetFighterFeatureByInsID(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT64 qwUsrID = 0;
	UINT64 qwFighterID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> qwUsrID >> qwFighterID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 57, Function: 3";
		return false;
	}
	shared_func<SGetFighterFeatureByInsIDAck> fnAck_(new SGetFighterFeatureByInsIDAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetFighterFeatureByInsID(qwUsrID, qwFighterID, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CGame2CenterTeamClt::SGetPlayerBattleInfoAck::SGetPlayerBattleInfoAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID), 
			eResult((NTeamGS::ETEAMResult)0) { }

void CGame2CenterTeamClt::SGetPlayerBattleInfoAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -3;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eResult << vecFighter;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 57, Function: 4";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CGame2CenterTeamClt::_DoRecv_GetPlayerBattleInfo(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT64 qwUsrID = 0;
	UINT8 byPlayerPos = 0;
	TVecUINT64 vecFigther;
	TVecUINT8 vecPos;
	UINT8 byNeedBeauty = 0;
	UINT16 wDgnType = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> qwUsrID >> byPlayerPos >> vecFigther >> vecPos >> byNeedBeauty >> wDgnType;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 57, Function: 4";
		return false;
	}
	shared_func<SGetPlayerBattleInfoAck> fnAck_(new SGetPlayerBattleInfoAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetPlayerBattleInfo(qwUsrID, byPlayerPos, vecFigther, vecPos, byNeedBeauty, wDgnType, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CGame2CenterTeamClt::SStartBattleAck::SStartBattleAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID) { }

void CGame2CenterTeamClt::SStartBattleAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -4;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << stTeamReport;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 57, Function: 5";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CGame2CenterTeamClt::_DoRecv_StartBattle(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT64 qwUsrID = 0;
	UINT16 wDgnType = 0;
	NBattleGS::TVecBattleFighter vecFighter;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> qwUsrID >> wDgnType >> vecFighter;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 57, Function: 5";
		return false;
	}
	shared_func<SStartBattleAck> fnAck_(new SStartBattleAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_StartBattle(qwUsrID, wDgnType, vecFighter, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

bool CGame2CenterTeamClt::_DoRecv_NoticeTeamReport(const char* pBuf_, UINT32 dwLen_)
{
	UINT64 qwUsrID = 0;
	UINT16 wDgnType = 0;
	TeamReport stTeamReport;
	UINT32 dwRewardRate = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> qwUsrID >> wDgnType >> stTeamReport >> dwRewardRate;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 57, Function: 6";
		return false;
	}
	OnRecv_NoticeTeamReport(qwUsrID, wDgnType, stTeamReport, dwRewardRate);
	return true;
}

} //namespace NGame2CenterTeam
