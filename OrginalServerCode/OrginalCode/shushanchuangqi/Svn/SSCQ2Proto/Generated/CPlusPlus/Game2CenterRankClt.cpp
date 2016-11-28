/************************************************************************
//  工具自动生成的客户端协议代码(UTF-8 With BOM)
//  File Name:    Game2CenterRank.cpp
//  Purpose:      排行榜相关内部协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "Game2CenterRankClt.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NGame2CenterRank
{

CGame2CenterRankClt::THandleFunc CGame2CenterRankClt::_HandleFuncs[] =
{
	&CGame2CenterRankClt::_DoRecv_GetFeature, //FuncID: 1
};

bool CGame2CenterRankClt::HandleMessage(const char* pBuf, UINT32 dwLen)
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

//发送：更新排名信息
bool CGame2CenterRankClt::Send_UpdateRankInfo(
	NRankProt::ERankType eType, //更新类型
	UINT64 qwInstID, //唯一ID(玩家ID/帮派ID)
	const NRankProt::TVecRankInfo& vecRankInfo //玩家信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eType << qwInstID << vecRankInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 81, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterRankClt::SendSvr_UpdateRankInfo(const UINT32* pSvrID_, UINT8 byCnt_,
	NRankProt::ERankType eType, //更新类型
	UINT64 qwInstID, //唯一ID(玩家ID/帮派ID)
	const NRankProt::TVecRankInfo& vecRankInfo //玩家信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eType << qwInstID << vecRankInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 81, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGame2CenterRankClt::BuildPkg_UpdateRankInfo(
	NRankProt::ERankType eType, //更新类型
	UINT64 qwInstID, //唯一ID(玩家ID/帮派ID)
	const NRankProt::TVecRankInfo& vecRankInfo //玩家信息
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eType << qwInstID << vecRankInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 81, Function: 1";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：更新所有待更新的等级信息
bool CGame2CenterRankClt::Send_UpdateAllLevelInfo(
	const TVecUINT64& vecRoleID, //玩家ID
	const NRankProt::TVecRankInfo& vecRankInfo //玩家信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << vecRoleID << vecRankInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 81, Function: 2";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterRankClt::SendSvr_UpdateAllLevelInfo(const UINT32* pSvrID_, UINT8 byCnt_,
	const TVecUINT64& vecRoleID, //玩家ID
	const NRankProt::TVecRankInfo& vecRankInfo //玩家信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << vecRoleID << vecRankInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 81, Function: 2";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGame2CenterRankClt::BuildPkg_UpdateAllLevelInfo(
	const TVecUINT64& vecRoleID, //玩家ID
	const NRankProt::TVecRankInfo& vecRankInfo //玩家信息
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << vecRoleID << vecRankInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 81, Function: 2";
		_strPkg.clear();
	}
	return _strPkg;
}

CGame2CenterRankClt::SGetFeatureAck::SGetFeatureAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID), 
			byError(0), wLevel(0) { }

void CGame2CenterRankClt::SGetFeatureAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -1;
	NBattleGS::SFeatureBase_Wrapper pFeature_RetWrapper;
	pFeature_RetWrapper.ptr = pFeature;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << byError << strName << wLevel << pFeature_RetWrapper;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 81, Function: 1";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CGame2CenterRankClt::_DoRecv_GetFeature(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 81, Function: 1";
		return false;
	}
	shared_func<SGetFeatureAck> fnAck_(new SGetFeatureAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetFeature(qwRoleID, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

} //namespace NGame2CenterRank
