/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    BattleGS.cpp
//  Purpose:      战斗通信协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "BattleGSSvr.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NBattleGS
{

CBattleGSSvr::THandleFunc CBattleGSSvr::_HandleFuncs[] =
{
	&CBattleGSSvr::_DoRecv_BattleReq, //FuncID: 1
	&CBattleGSSvr::_DoRecv_BattleReportReq, //FuncID: 2
	&CBattleGSSvr::_DoRecv_FinishBattleReport, //FuncID: 3
};

bool CBattleGSSvr::HandleMessage(const char* pBuf, UINT32 dwLen)
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

//发送：战斗请求结果
bool CBattleGSSvr::Send_BattleAck(
	EBattleReqResult eResult //返回结果
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 21, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CBattleGSSvr::SendClt_BattleAck(const UINT64* pUsrID_, UINT16 wCnt_,
	EBattleReqResult eResult //返回结果
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 21, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CBattleGSSvr::BuildPkg_BattleAck(
	EBattleReqResult eResult //返回结果
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 21, Function: 1";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：请求战报结果
bool CBattleGSSvr::Send_BattleReportAck(
	EReportReqResult eResult //战报请求结果
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 21, Function: 2";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CBattleGSSvr::SendClt_BattleReportAck(const UINT64* pUsrID_, UINT16 wCnt_,
	EReportReqResult eResult //战报请求结果
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 21, Function: 2";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CBattleGSSvr::BuildPkg_BattleReportAck(
	EReportReqResult eResult //战报请求结果
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 21, Function: 2";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：战报
bool CBattleGSSvr::Send_BattleReportData(
	const std::string& strBattleReport, //战报
	UINT64 qwMasterID, //视角角色ID
	UINT16 wFighterID //主将ID
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << strBattleReport << qwMasterID << wFighterID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 21, Function: 3";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CBattleGSSvr::SendClt_BattleReportData(const UINT64* pUsrID_, UINT16 wCnt_,
	const std::string& strBattleReport, //战报
	UINT64 qwMasterID, //视角角色ID
	UINT16 wFighterID //主将ID
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << strBattleReport << qwMasterID << wFighterID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 21, Function: 3";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CBattleGSSvr::BuildPkg_BattleReportData(
	const std::string& strBattleReport, //战报
	UINT64 qwMasterID, //视角角色ID
	UINT16 wFighterID //主将ID
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << strBattleReport << qwMasterID << wFighterID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 21, Function: 3";
		_strPkg.clear();
	}
	return _strPkg;
}

bool CBattleGSSvr::_DoRecv_BattleReq(const char* pBuf_, UINT32 dwLen_)
{
	UINT64 qwDefenseID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> qwDefenseID;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 21, Function: 1";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	OnRecv_BattleReq(qwDefenseID);
	return true;
}

bool CBattleGSSvr::_DoRecv_BattleReportReq(const char* pBuf_, UINT32 dwLen_)
{
	UINT64 qwReportID = 0;
	UINT64 qwMasterID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> qwReportID >> qwMasterID;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 21, Function: 2";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	OnRecv_BattleReportReq(qwReportID, qwMasterID);
	return true;
}

bool CBattleGSSvr::_DoRecv_FinishBattleReport(const char* pBuf_, UINT32 dwLen_)
{
	UINT64 qwReportID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> qwReportID;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 21, Function: 3";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	OnRecv_FinishBattleReport(qwReportID);
	return true;
}

} //namespace NBattleGS
