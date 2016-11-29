/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    Game2CenterGuildBattle.cpp
//  Purpose:      帮派战相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "Game2CenterGuildBattleSvr.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NGame2CenterGuildBattle
{

CGame2CenterGuildBattleSvr::THandleFunc CGame2CenterGuildBattleSvr::_HandleFuncs[] =
{
	&CGame2CenterGuildBattleSvr::_DoRecv_SetState, //FuncID: 1
	&CGame2CenterGuildBattleSvr::_DoRecv_UserSignUp, //FuncID: 2
	&CGame2CenterGuildBattleSvr::_DoRecv_InfoNotify, //FuncID: 3
	&CGame2CenterGuildBattleSvr::_DoRecv_GetAuthority, //FuncID: 4
	&CGame2CenterGuildBattleSvr::_DoRecv_AddScore, //FuncID: 5
	&CGame2CenterGuildBattleSvr::_DoRecv_AddGuildScore, //FuncID: 6
	&CGame2CenterGuildBattleSvr::_DoRecv_AddMemberScore, //FuncID: 7
	&CGame2CenterGuildBattleSvr::_DoRecv_GetPanelInfo, //FuncID: 8
	&CGame2CenterGuildBattleSvr::_DoRecv_SyncGuildRank, //FuncID: 9
	&CGame2CenterGuildBattleSvr::_DoRecv_NewSetState, //FuncID: 10
	&CGame2CenterGuildBattleSvr::_DoRecv_NewGetGuildID, //FuncID: 11
};

bool CGame2CenterGuildBattleSvr::HandleMessage(const char* pBuf, UINT32 dwLen)
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

//发送：帮派等级更新
bool CGame2CenterGuildBattleSvr::Send_GuildLevelChanged(
	UINT64 qwGuildID, //帮派对应ID
	UINT16 wLevel //帮派等级
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << qwGuildID << wLevel;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 77, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterGuildBattleSvr::SendSvr_GuildLevelChanged(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwGuildID, //帮派对应ID
	UINT16 wLevel //帮派等级
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << qwGuildID << wLevel;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 77, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGame2CenterGuildBattleSvr::BuildPkg_GuildLevelChanged(
	UINT64 qwGuildID, //帮派对应ID
	UINT16 wLevel //帮派等级
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << qwGuildID << wLevel;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 77, Function: 1";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：帮主更新
bool CGame2CenterGuildBattleSvr::Send_GuildOwnerChanged(
	UINT64 qwGuildID, //帮派对应ID
	const std::string& strGuildOwnerName //帮主名称
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << qwGuildID << strGuildOwnerName;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 77, Function: 2";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterGuildBattleSvr::SendSvr_GuildOwnerChanged(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwGuildID, //帮派对应ID
	const std::string& strGuildOwnerName //帮主名称
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << qwGuildID << strGuildOwnerName;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 77, Function: 2";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGame2CenterGuildBattleSvr::BuildPkg_GuildOwnerChanged(
	UINT64 qwGuildID, //帮派对应ID
	const std::string& strGuildOwnerName //帮主名称
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << qwGuildID << strGuildOwnerName;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 77, Function: 2";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：帮派解散
bool CGame2CenterGuildBattleSvr::Send_GuildDisband(
	UINT64 qwGuildID //帮派对应ID
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << qwGuildID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 77, Function: 3";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterGuildBattleSvr::SendSvr_GuildDisband(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwGuildID //帮派对应ID
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << qwGuildID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 77, Function: 3";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGame2CenterGuildBattleSvr::BuildPkg_GuildDisband(
	UINT64 qwGuildID //帮派对应ID
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << qwGuildID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 77, Function: 3";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：可以发送新帮派战数据
bool CGame2CenterGuildBattleSvr::Send_ReadyToSendNewGuildBattle(
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 77, Function: 4";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterGuildBattleSvr::SendSvr_ReadyToSendNewGuildBattle(const UINT32* pSvrID_, UINT8 byCnt_
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 77, Function: 4";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGame2CenterGuildBattleSvr::BuildPkg_ReadyToSendNewGuildBattle(
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 77, Function: 4";
		_strPkg.clear();
	}
	return _strPkg;
}

bool CGame2CenterGuildBattleSvr::_DoRecv_SetState(const char* pBuf_, UINT32 dwLen_)
{
	NGuildBattleProt::EGBState eState = (NGuildBattleProt::EGBState)0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> (UINT8&)eState;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 77, Function: 1";
		return false;
	}
	OnRecv_SetState(eState);
	return true;
}

CGame2CenterGuildBattleSvr::SUserSignUpAck::SUserSignUpAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID), 
			qwGuildID(0), wLevel(0), dwScore(0), eResult((NGuildBattleProt::EGBSignUpResult)0) { }

void CGame2CenterGuildBattleSvr::SUserSignUpAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -1;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << qwGuildID << wLevel << strGuildName << dwScore << (UINT8&)eResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 77, Function: 2";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CGame2CenterGuildBattleSvr::_DoRecv_UserSignUp(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 77, Function: 2";
		return false;
	}
	shared_func<SUserSignUpAck> fnAck_(new SUserSignUpAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_UserSignUp(qwRoleID, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

bool CGame2CenterGuildBattleSvr::_DoRecv_InfoNotify(const char* pBuf_, UINT32 dwLen_)
{
	UINT64 qwGuildID = 0;
	UINT16 wMsgID = 0;
	TVecString vecStr;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> qwGuildID >> wMsgID >> vecStr;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 77, Function: 3";
		return false;
	}
	OnRecv_InfoNotify(qwGuildID, wMsgID, vecStr);
	return true;
}

CGame2CenterGuildBattleSvr::SGetAuthorityAck::SGetAuthorityAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID), 
			bHasAuthority(false) { }

void CGame2CenterGuildBattleSvr::SGetAuthorityAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -2;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << bHasAuthority;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 77, Function: 4";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CGame2CenterGuildBattleSvr::_DoRecv_GetAuthority(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 77, Function: 4";
		return false;
	}
	shared_func<SGetAuthorityAck> fnAck_(new SGetAuthorityAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetAuthority(qwRoleID, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

bool CGame2CenterGuildBattleSvr::_DoRecv_AddScore(const char* pBuf_, UINT32 dwLen_)
{
	UINT64 qwGuildID = 0;
	UINT32 dwScore = 0;
	TVecMemberScore vecMemberScore;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> qwGuildID >> dwScore >> vecMemberScore;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 77, Function: 5";
		return false;
	}
	OnRecv_AddScore(qwGuildID, dwScore, vecMemberScore);
	return true;
}

bool CGame2CenterGuildBattleSvr::_DoRecv_AddGuildScore(const char* pBuf_, UINT32 dwLen_)
{
	UINT64 qwGuildID = 0;
	UINT32 dwScore = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> qwGuildID >> dwScore;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 77, Function: 6";
		return false;
	}
	OnRecv_AddGuildScore(qwGuildID, dwScore);
	return true;
}

bool CGame2CenterGuildBattleSvr::_DoRecv_AddMemberScore(const char* pBuf_, UINT32 dwLen_)
{
	UINT64 qwGuildID = 0;
	TVecMemberScore vecMemberScore;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> qwGuildID >> vecMemberScore;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 77, Function: 7";
		return false;
	}
	OnRecv_AddMemberScore(qwGuildID, vecMemberScore);
	return true;
}

CGame2CenterGuildBattleSvr::SGetPanelInfoAck::SGetPanelInfoAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID), 
			dwSelfScore(0), dwGuildScore(0), dwGuildRank(0) { }

void CGame2CenterGuildBattleSvr::SGetPanelInfoAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -3;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << dwSelfScore << dwGuildScore << dwGuildRank;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 77, Function: 8";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CGame2CenterGuildBattleSvr::_DoRecv_GetPanelInfo(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 77, Function: 8";
		return false;
	}
	shared_func<SGetPanelInfoAck> fnAck_(new SGetPanelInfoAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetPanelInfo(qwRoleID, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

bool CGame2CenterGuildBattleSvr::_DoRecv_SyncGuildRank(const char* pBuf_, UINT32 dwLen_)
{
	OnRecv_SyncGuildRank();
	return true;
}

bool CGame2CenterGuildBattleSvr::_DoRecv_NewSetState(const char* pBuf_, UINT32 dwLen_)
{
	NNewGuildBattleProt::ENGBState eState = (NNewGuildBattleProt::ENGBState)0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> (UINT8&)eState;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 77, Function: 10";
		return false;
	}
	OnRecv_NewSetState(eState);
	return true;
}

CGame2CenterGuildBattleSvr::SNewGetGuildIDAck::SNewGetGuildIDAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID), 
			qwGuildID(0), byGuildLvl(0) { }

void CGame2CenterGuildBattleSvr::SNewGetGuildIDAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -4;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << qwGuildID << strGuildName << byGuildLvl;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 77, Function: 11";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CGame2CenterGuildBattleSvr::_DoRecv_NewGetGuildID(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 77, Function: 11";
		return false;
	}
	shared_func<SNewGetGuildIDAck> fnAck_(new SNewGetGuildIDAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_NewGetGuildID(qwRoleID, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

} //namespace NGame2CenterGuildBattle
