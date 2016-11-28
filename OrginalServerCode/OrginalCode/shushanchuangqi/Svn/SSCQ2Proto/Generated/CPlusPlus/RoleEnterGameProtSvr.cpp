/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    RoleEnterGameProt.cpp
//  Purpose:      角色信息相关操作协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "RoleEnterGameProtSvr.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NRoleEnterGameProt
{

CRoleEnterGameProtSvr::THandleFunc CRoleEnterGameProtSvr::_HandleFuncs[] =
{
	&CRoleEnterGameProtSvr::_DoRecv_EnterGameReq, //FuncID: 1
	&CRoleEnterGameProtSvr::_DoRecv_CreateRoleReq, //FuncID: 2
	&CRoleEnterGameProtSvr::_DoRecv_PlayerRamdomNameReq, //FuncID: 3
	&CRoleEnterGameProtSvr::_DoRecv_GetUserInfo, //FuncID: 4
};

bool CRoleEnterGameProtSvr::HandleMessage(const char* pBuf, UINT32 dwLen)
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

//发送：请求进入游戏应答
bool CRoleEnterGameProtSvr::Send_EnterGameAck(
	EEnterResult eEnterResult, //登陆结果
	UINT32 dwNowTimer //目前服务器的时间
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eEnterResult << dwNowTimer;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 3, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CRoleEnterGameProtSvr::SendClt_EnterGameAck(const UINT64* pUsrID_, UINT16 wCnt_,
	EEnterResult eEnterResult, //登陆结果
	UINT32 dwNowTimer //目前服务器的时间
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eEnterResult << dwNowTimer;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 3, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CRoleEnterGameProtSvr::BuildPkg_EnterGameAck(
	EEnterResult eEnterResult, //登陆结果
	UINT32 dwNowTimer //目前服务器的时间
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eEnterResult << dwNowTimer;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 3, Function: 1";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：创建角色应答
bool CRoleEnterGameProtSvr::Send_CreateRoleAck(
	ECreateRoleResult eCreateRoleResult //创建结果
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eCreateRoleResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 3, Function: 2";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CRoleEnterGameProtSvr::SendClt_CreateRoleAck(const UINT64* pUsrID_, UINT16 wCnt_,
	ECreateRoleResult eCreateRoleResult //创建结果
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eCreateRoleResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 3, Function: 2";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CRoleEnterGameProtSvr::BuildPkg_CreateRoleAck(
	ECreateRoleResult eCreateRoleResult //创建结果
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eCreateRoleResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 3, Function: 2";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：玩家请求推荐名字返回
bool CRoleEnterGameProtSvr::Send_PlayerRamdomNameAck(
	const std::string& strName //空表示没有得到
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << strName;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 3, Function: 3";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CRoleEnterGameProtSvr::SendClt_PlayerRamdomNameAck(const UINT64* pUsrID_, UINT16 wCnt_,
	const std::string& strName //空表示没有得到
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << strName;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 3, Function: 3";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CRoleEnterGameProtSvr::BuildPkg_PlayerRamdomNameAck(
	const std::string& strName //空表示没有得到
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << strName;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 3, Function: 3";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：角色查询返回
bool CRoleEnterGameProtSvr::Send_GetUserInfoAck(
	const RoleEnterGameData& stRoleEnterInfo //进入信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << stRoleEnterInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 3, Function: 4";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CRoleEnterGameProtSvr::SendClt_GetUserInfoAck(const UINT64* pUsrID_, UINT16 wCnt_,
	const RoleEnterGameData& stRoleEnterInfo //进入信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << stRoleEnterInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 3, Function: 4";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CRoleEnterGameProtSvr::BuildPkg_GetUserInfoAck(
	const RoleEnterGameData& stRoleEnterInfo //进入信息
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << stRoleEnterInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 3, Function: 4";
		_strPkg.clear();
	}
	return _strPkg;
}

bool CRoleEnterGameProtSvr::_DoRecv_EnterGameReq(const char* pBuf_, UINT32 dwLen_)
{
	SEnterParam stEnterParam;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> stEnterParam;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 3, Function: 1";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	OnRecv_EnterGameReq(stEnterParam);
	return true;
}

bool CRoleEnterGameProtSvr::_DoRecv_CreateRoleReq(const char* pBuf_, UINT32 dwLen_)
{
	SCreateRoleInfo stCreateInfo;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> stCreateInfo;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 3, Function: 2";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	OnRecv_CreateRoleReq(stCreateInfo);
	return true;
}

bool CRoleEnterGameProtSvr::_DoRecv_PlayerRamdomNameReq(const char* pBuf_, UINT32 dwLen_)
{
	UINT8 byIsMale = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> byIsMale;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 3, Function: 3";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	OnRecv_PlayerRamdomNameReq(byIsMale);
	return true;
}

bool CRoleEnterGameProtSvr::_DoRecv_GetUserInfo(const char* pBuf_, UINT32 dwLen_)
{
	OnRecv_GetUserInfo();
	return true;
}

} //namespace NRoleEnterGameProt
