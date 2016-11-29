/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    MapProt.cpp
//  Purpose:      地图相关功能的协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "MapProtSvr.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NMapProt
{

CMapProtSvr::THandleFunc CMapProtSvr::_HandleFuncs[] =
{
	&CMapProtSvr::_DoRecv_PlayerMoveReq, //FuncID: 1
	&CMapProtSvr::_DoRecv_PlayerStopReq, //FuncID: 2
	&CMapProtSvr::_DoRecv_GetPlayerAppear, //FuncID: 3
	&CMapProtSvr::_DoRecv_JumpMap, //FuncID: 4
	&CMapProtSvr::_DoRecv_GetMapOverLoad, //FuncID: 5
};

bool CMapProtSvr::HandleMessage(const char* pBuf, UINT32 dwLen)
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

//发送：通知玩家进入地图
bool CMapProtSvr::Send_UserEnterMapNtf(
	UINT16 wMapID, //地图ID
	UINT64 qwRoleID, //当前的角色ID
	UINT8 byIndex, //地图序号,非主城返回255
	UINT8 byTotal, //同Id地图总数,非主城返回0
	const SPosition& rPosition, //进入位置
	float fDir //方向
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << wMapID << qwRoleID << byIndex << byTotal << rPosition << fDir;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 5, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CMapProtSvr::SendClt_UserEnterMapNtf(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT16 wMapID, //地图ID
	UINT64 qwRoleID, //当前的角色ID
	UINT8 byIndex, //地图序号,非主城返回255
	UINT8 byTotal, //同Id地图总数,非主城返回0
	const SPosition& rPosition, //进入位置
	float fDir //方向
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << wMapID << qwRoleID << byIndex << byTotal << rPosition << fDir;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 5, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CMapProtSvr::BuildPkg_UserEnterMapNtf(
	UINT16 wMapID, //地图ID
	UINT64 qwRoleID, //当前的角色ID
	UINT8 byIndex, //地图序号,非主城返回255
	UINT8 byTotal, //同Id地图总数,非主城返回0
	const SPosition& rPosition, //进入位置
	float fDir //方向
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << wMapID << qwRoleID << byIndex << byTotal << rPosition << fDir;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 5, Function: 1";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：新地图产生，通知同地图玩家
bool CMapProtSvr::Send_NoticeNewMap(
	const TVecMapOverLoad& vecLoad //地图负载
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << vecLoad;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 5, Function: 2";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CMapProtSvr::SendClt_NoticeNewMap(const UINT64* pUsrID_, UINT16 wCnt_,
	const TVecMapOverLoad& vecLoad //地图负载
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << vecLoad;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 5, Function: 2";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CMapProtSvr::BuildPkg_NoticeNewMap(
	const TVecMapOverLoad& vecLoad //地图负载
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << vecLoad;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 5, Function: 2";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：角色(非当前控制)地图信息通知
bool CMapProtSvr::Send_RoleMapInfoNtf(
	UINT64 qwRoleID, //角色的ID
	UINT16 wMapID //地图ID
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << qwRoleID << wMapID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 5, Function: 3";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CMapProtSvr::SendClt_RoleMapInfoNtf(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT64 qwRoleID, //角色的ID
	UINT16 wMapID //地图ID
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << qwRoleID << wMapID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 5, Function: 3";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CMapProtSvr::BuildPkg_RoleMapInfoNtf(
	UINT64 qwRoleID, //角色的ID
	UINT16 wMapID //地图ID
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << qwRoleID << wMapID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 5, Function: 3";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：通知角色移动失败
bool CMapProtSvr::Send_PlayerMoveFail(
	UINT64 qwRoleID, //角色ID
	const SPosition& rLastPosition, //上一个位置
	const TVecPosition& vecPosition //移动位置列表
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << qwRoleID << rLastPosition << vecPosition;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 5, Function: 4";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CMapProtSvr::SendClt_PlayerMoveFail(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT64 qwRoleID, //角色ID
	const SPosition& rLastPosition, //上一个位置
	const TVecPosition& vecPosition //移动位置列表
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << qwRoleID << rLastPosition << vecPosition;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 5, Function: 4";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CMapProtSvr::BuildPkg_PlayerMoveFail(
	UINT64 qwRoleID, //角色ID
	const SPosition& rLastPosition, //上一个位置
	const TVecPosition& vecPosition //移动位置列表
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << qwRoleID << rLastPosition << vecPosition;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 5, Function: 4";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：通知自己的玩家角色出现
bool CMapProtSvr::Send_NotifyAppear(
	UINT64 qwRoleID, //角色ID
	const SPlayerAppear& rPlayerAppear, //玩家的外观
	const SPosition& rPosition, //出现位置
	float fDir, //方向(弧度)
	UINT32 dwAppearState //当前状态(EAppearState按位或的结果)
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 5;
	try
	{
		ar << byProtID_ << byFuncID_ << qwRoleID << rPlayerAppear << rPosition << fDir << dwAppearState;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 5, Function: 5";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CMapProtSvr::SendClt_NotifyAppear(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT64 qwRoleID, //角色ID
	const SPlayerAppear& rPlayerAppear, //玩家的外观
	const SPosition& rPosition, //出现位置
	float fDir, //方向(弧度)
	UINT32 dwAppearState //当前状态(EAppearState按位或的结果)
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 5;
	try
	{
		ar << byProtID_ << byFuncID_ << qwRoleID << rPlayerAppear << rPosition << fDir << dwAppearState;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 5, Function: 5";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CMapProtSvr::BuildPkg_NotifyAppear(
	UINT64 qwRoleID, //角色ID
	const SPlayerAppear& rPlayerAppear, //玩家的外观
	const SPosition& rPosition, //出现位置
	float fDir, //方向(弧度)
	UINT32 dwAppearState //当前状态(EAppearState按位或的结果)
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 5;
	try
	{
		ar << byProtID_ << byFuncID_ << qwRoleID << rPlayerAppear << rPosition << fDir << dwAppearState;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 5, Function: 5";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：通知别的玩家角色出现
bool CMapProtSvr::Send_PlayerAppear(
	UINT64 qwRoleID, //角色ID
	const SPlayerAppear& rPlayerAppear, //玩家的外观
	const SPosition& rPosition, //出现位置
	float fDir, //方向(弧度)
	UINT32 dwAppearState, //当前状态(EAppearState按位或的结果)
	bool bBorn //true为出生，false为进入视野
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 6;
	try
	{
		ar << byProtID_ << byFuncID_ << qwRoleID << rPlayerAppear << rPosition << fDir << dwAppearState << bBorn;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 5, Function: 6";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CMapProtSvr::SendClt_PlayerAppear(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT64 qwRoleID, //角色ID
	const SPlayerAppear& rPlayerAppear, //玩家的外观
	const SPosition& rPosition, //出现位置
	float fDir, //方向(弧度)
	UINT32 dwAppearState, //当前状态(EAppearState按位或的结果)
	bool bBorn //true为出生，false为进入视野
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 6;
	try
	{
		ar << byProtID_ << byFuncID_ << qwRoleID << rPlayerAppear << rPosition << fDir << dwAppearState << bBorn;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 5, Function: 6";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CMapProtSvr::BuildPkg_PlayerAppear(
	UINT64 qwRoleID, //角色ID
	const SPlayerAppear& rPlayerAppear, //玩家的外观
	const SPosition& rPosition, //出现位置
	float fDir, //方向(弧度)
	UINT32 dwAppearState, //当前状态(EAppearState按位或的结果)
	bool bBorn //true为出生，false为进入视野
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 6;
	try
	{
		ar << byProtID_ << byFuncID_ << qwRoleID << rPlayerAppear << rPosition << fDir << dwAppearState << bBorn;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 5, Function: 6";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：通知Creature移动
bool CMapProtSvr::Send_NotifyCreatureMove(
	UINT64 qwCreatureID, //生物ID
	const TVecPosition& vecPosition //移动位置列表
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 7;
	try
	{
		ar << byProtID_ << byFuncID_ << qwCreatureID << vecPosition;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 5, Function: 7";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CMapProtSvr::SendClt_NotifyCreatureMove(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT64 qwCreatureID, //生物ID
	const TVecPosition& vecPosition //移动位置列表
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 7;
	try
	{
		ar << byProtID_ << byFuncID_ << qwCreatureID << vecPosition;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 5, Function: 7";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CMapProtSvr::BuildPkg_NotifyCreatureMove(
	UINT64 qwCreatureID, //生物ID
	const TVecPosition& vecPosition //移动位置列表
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 7;
	try
	{
		ar << byProtID_ << byFuncID_ << qwCreatureID << vecPosition;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 5, Function: 7";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：通知Creature跳点
bool CMapProtSvr::Send_NotifyCreatureJump(
	UINT64 qwCreatureID, //Creature ID
	const SPosition& rPosition, //跳点目的位置
	UINT16 wJumpId //跳点ID
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 8;
	try
	{
		ar << byProtID_ << byFuncID_ << qwCreatureID << rPosition << wJumpId;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 5, Function: 8";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CMapProtSvr::SendClt_NotifyCreatureJump(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT64 qwCreatureID, //Creature ID
	const SPosition& rPosition, //跳点目的位置
	UINT16 wJumpId //跳点ID
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 8;
	try
	{
		ar << byProtID_ << byFuncID_ << qwCreatureID << rPosition << wJumpId;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 5, Function: 8";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CMapProtSvr::BuildPkg_NotifyCreatureJump(
	UINT64 qwCreatureID, //Creature ID
	const SPosition& rPosition, //跳点目的位置
	UINT16 wJumpId //跳点ID
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 8;
	try
	{
		ar << byProtID_ << byFuncID_ << qwCreatureID << rPosition << wJumpId;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 5, Function: 8";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：通知Creature当前状态
bool CMapProtSvr::Send_NotifyCreatureState(
	UINT64 qwCreatureID, //Creature ID
	UINT32 dwAppearState //当前状态(EAppearState按位或的结果)
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 9;
	try
	{
		ar << byProtID_ << byFuncID_ << qwCreatureID << dwAppearState;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 5, Function: 9";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CMapProtSvr::SendClt_NotifyCreatureState(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT64 qwCreatureID, //Creature ID
	UINT32 dwAppearState //当前状态(EAppearState按位或的结果)
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 9;
	try
	{
		ar << byProtID_ << byFuncID_ << qwCreatureID << dwAppearState;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 5, Function: 9";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CMapProtSvr::BuildPkg_NotifyCreatureState(
	UINT64 qwCreatureID, //Creature ID
	UINT32 dwAppearState //当前状态(EAppearState按位或的结果)
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 9;
	try
	{
		ar << byProtID_ << byFuncID_ << qwCreatureID << dwAppearState;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 5, Function: 9";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：通知Creature停止
bool CMapProtSvr::Send_NotifyCreatureStop(
	UINT64 qwCreatureID, //生物ID
	const SPosition& rDestPosition //最终位置
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 10;
	try
	{
		ar << byProtID_ << byFuncID_ << qwCreatureID << rDestPosition;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 5, Function: 10";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CMapProtSvr::SendClt_NotifyCreatureStop(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT64 qwCreatureID, //生物ID
	const SPosition& rDestPosition //最终位置
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 10;
	try
	{
		ar << byProtID_ << byFuncID_ << qwCreatureID << rDestPosition;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 5, Function: 10";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CMapProtSvr::BuildPkg_NotifyCreatureStop(
	UINT64 qwCreatureID, //生物ID
	const SPosition& rDestPosition //最终位置
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 10;
	try
	{
		ar << byProtID_ << byFuncID_ << qwCreatureID << rDestPosition;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 5, Function: 10";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：通知地图上生物消失
bool CMapProtSvr::Send_CreatureDisappear(
	UINT64 qwCreatureID, //生物ID
	bool bDieFade //true为死亡消失，false为移出视野
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 11;
	try
	{
		ar << byProtID_ << byFuncID_ << qwCreatureID << bDieFade;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 5, Function: 11";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CMapProtSvr::SendClt_CreatureDisappear(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT64 qwCreatureID, //生物ID
	bool bDieFade //true为死亡消失，false为移出视野
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 11;
	try
	{
		ar << byProtID_ << byFuncID_ << qwCreatureID << bDieFade;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 5, Function: 11";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CMapProtSvr::BuildPkg_CreatureDisappear(
	UINT64 qwCreatureID, //生物ID
	bool bDieFade //true为死亡消失，false为移出视野
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 11;
	try
	{
		ar << byProtID_ << byFuncID_ << qwCreatureID << bDieFade;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 5, Function: 11";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：通知NPC出现
bool CMapProtSvr::Send_NpcAppear(
	UINT64 qwCreatureID, //生物ID
	const SNpcAppear& rNpcAppear, //NPC外观
	const SPosition& rPosition, //出现位置
	float fDir, //方向(弧度)
	bool bBorn //true为出生，false为进入视野
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 12;
	try
	{
		ar << byProtID_ << byFuncID_ << qwCreatureID << rNpcAppear << rPosition << fDir << bBorn;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 5, Function: 12";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CMapProtSvr::SendClt_NpcAppear(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT64 qwCreatureID, //生物ID
	const SNpcAppear& rNpcAppear, //NPC外观
	const SPosition& rPosition, //出现位置
	float fDir, //方向(弧度)
	bool bBorn //true为出生，false为进入视野
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 12;
	try
	{
		ar << byProtID_ << byFuncID_ << qwCreatureID << rNpcAppear << rPosition << fDir << bBorn;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 5, Function: 12";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CMapProtSvr::BuildPkg_NpcAppear(
	UINT64 qwCreatureID, //生物ID
	const SNpcAppear& rNpcAppear, //NPC外观
	const SPosition& rPosition, //出现位置
	float fDir, //方向(弧度)
	bool bBorn //true为出生，false为进入视野
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 12;
	try
	{
		ar << byProtID_ << byFuncID_ << qwCreatureID << rNpcAppear << rPosition << fDir << bBorn;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 5, Function: 12";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：通知怪物出现
bool CMapProtSvr::Send_MonsterAppear(
	UINT64 qwCreatureID, //生物ID
	const SMonsterAppear& rMonsterAppear, //怪物外观
	const SPosition& rPosition, //出现位置
	float fDir, //方向(弧度)
	UINT32 dwAppearState, //当前状态(EAppearState按位或的结果)
	bool bBorn //true为出生，false为进入视野
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 13;
	try
	{
		ar << byProtID_ << byFuncID_ << qwCreatureID << rMonsterAppear << rPosition << fDir << dwAppearState << bBorn;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 5, Function: 13";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CMapProtSvr::SendClt_MonsterAppear(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT64 qwCreatureID, //生物ID
	const SMonsterAppear& rMonsterAppear, //怪物外观
	const SPosition& rPosition, //出现位置
	float fDir, //方向(弧度)
	UINT32 dwAppearState, //当前状态(EAppearState按位或的结果)
	bool bBorn //true为出生，false为进入视野
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 13;
	try
	{
		ar << byProtID_ << byFuncID_ << qwCreatureID << rMonsterAppear << rPosition << fDir << dwAppearState << bBorn;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 5, Function: 13";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CMapProtSvr::BuildPkg_MonsterAppear(
	UINT64 qwCreatureID, //生物ID
	const SMonsterAppear& rMonsterAppear, //怪物外观
	const SPosition& rPosition, //出现位置
	float fDir, //方向(弧度)
	UINT32 dwAppearState, //当前状态(EAppearState按位或的结果)
	bool bBorn //true为出生，false为进入视野
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 13;
	try
	{
		ar << byProtID_ << byFuncID_ << qwCreatureID << rMonsterAppear << rPosition << fDir << dwAppearState << bBorn;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 5, Function: 13";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：通知开关出现
bool CMapProtSvr::Send_SwitcherAppear(
	UINT32 dwInstID, //唯一实例ID
	const SSwitcherAppear& rSwitcherAppear, //开关外观
	const SPosition& rPosition, //出现位置
	float fDir, //方向(弧度)
	bool bBorn //true为出生，false为进入视野
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 14;
	try
	{
		ar << byProtID_ << byFuncID_ << dwInstID << rSwitcherAppear << rPosition << fDir << bBorn;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 5, Function: 14";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CMapProtSvr::SendClt_SwitcherAppear(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT32 dwInstID, //唯一实例ID
	const SSwitcherAppear& rSwitcherAppear, //开关外观
	const SPosition& rPosition, //出现位置
	float fDir, //方向(弧度)
	bool bBorn //true为出生，false为进入视野
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 14;
	try
	{
		ar << byProtID_ << byFuncID_ << dwInstID << rSwitcherAppear << rPosition << fDir << bBorn;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 5, Function: 14";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CMapProtSvr::BuildPkg_SwitcherAppear(
	UINT32 dwInstID, //唯一实例ID
	const SSwitcherAppear& rSwitcherAppear, //开关外观
	const SPosition& rPosition, //出现位置
	float fDir, //方向(弧度)
	bool bBorn //true为出生，false为进入视野
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 14;
	try
	{
		ar << byProtID_ << byFuncID_ << dwInstID << rSwitcherAppear << rPosition << fDir << bBorn;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 5, Function: 14";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：通知地图上开关消失
bool CMapProtSvr::Send_SwitcherDisappear(
	UINT32 dwInstID //开关唯一ID
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 15;
	try
	{
		ar << byProtID_ << byFuncID_ << dwInstID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 5, Function: 15";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CMapProtSvr::SendClt_SwitcherDisappear(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT32 dwInstID //开关唯一ID
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 15;
	try
	{
		ar << byProtID_ << byFuncID_ << dwInstID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 5, Function: 15";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CMapProtSvr::BuildPkg_SwitcherDisappear(
	UINT32 dwInstID //开关唯一ID
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 15;
	try
	{
		ar << byProtID_ << byFuncID_ << dwInstID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 5, Function: 15";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：通知开关当前状态
bool CMapProtSvr::Send_NotifySwitcherState(
	UINT32 dwInstID, //开关唯一实例ID
	bool bOpen //当前开关是否开启
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 16;
	try
	{
		ar << byProtID_ << byFuncID_ << dwInstID << bOpen;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 5, Function: 16";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CMapProtSvr::SendClt_NotifySwitcherState(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT32 dwInstID, //开关唯一实例ID
	bool bOpen //当前开关是否开启
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 16;
	try
	{
		ar << byProtID_ << byFuncID_ << dwInstID << bOpen;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 5, Function: 16";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CMapProtSvr::BuildPkg_NotifySwitcherState(
	UINT32 dwInstID, //开关唯一实例ID
	bool bOpen //当前开关是否开启
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 16;
	try
	{
		ar << byProtID_ << byFuncID_ << dwInstID << bOpen;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 5, Function: 16";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：通知采集物出现
bool CMapProtSvr::Send_GatherAppear(
	UINT32 dwGatherID, //生物ID
	const SGatherAppear& rGatherAppear, //采集物外观
	const SPosition& rPosition, //出现位置
	float fDir, //方向(弧度)
	bool bBorn //true为出生，false为进入视野
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 17;
	try
	{
		ar << byProtID_ << byFuncID_ << dwGatherID << rGatherAppear << rPosition << fDir << bBorn;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 5, Function: 17";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CMapProtSvr::SendClt_GatherAppear(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT32 dwGatherID, //生物ID
	const SGatherAppear& rGatherAppear, //采集物外观
	const SPosition& rPosition, //出现位置
	float fDir, //方向(弧度)
	bool bBorn //true为出生，false为进入视野
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 17;
	try
	{
		ar << byProtID_ << byFuncID_ << dwGatherID << rGatherAppear << rPosition << fDir << bBorn;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 5, Function: 17";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CMapProtSvr::BuildPkg_GatherAppear(
	UINT32 dwGatherID, //生物ID
	const SGatherAppear& rGatherAppear, //采集物外观
	const SPosition& rPosition, //出现位置
	float fDir, //方向(弧度)
	bool bBorn //true为出生，false为进入视野
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 17;
	try
	{
		ar << byProtID_ << byFuncID_ << dwGatherID << rGatherAppear << rPosition << fDir << bBorn;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 5, Function: 17";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：通知地图上采集物消失
bool CMapProtSvr::Send_GatherDisappear(
	UINT32 dwGatherID, //采集物ID
	bool bDieFade //true为采集后消失，false为移出视野
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 18;
	try
	{
		ar << byProtID_ << byFuncID_ << dwGatherID << bDieFade;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 5, Function: 18";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CMapProtSvr::SendClt_GatherDisappear(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT32 dwGatherID, //采集物ID
	bool bDieFade //true为采集后消失，false为移出视野
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 18;
	try
	{
		ar << byProtID_ << byFuncID_ << dwGatherID << bDieFade;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 5, Function: 18";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CMapProtSvr::BuildPkg_GatherDisappear(
	UINT32 dwGatherID, //采集物ID
	bool bDieFade //true为采集后消失，false为移出视野
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 18;
	try
	{
		ar << byProtID_ << byFuncID_ << dwGatherID << bDieFade;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 5, Function: 18";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：通知地图上采集物改变
bool CMapProtSvr::Send_GatherChange(
	UINT32 dwGatherID, //采集物ID
	const SGatherAppear& rGatherAppear //采集物外观
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 19;
	try
	{
		ar << byProtID_ << byFuncID_ << dwGatherID << rGatherAppear;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 5, Function: 19";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CMapProtSvr::SendClt_GatherChange(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT32 dwGatherID, //采集物ID
	const SGatherAppear& rGatherAppear //采集物外观
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 19;
	try
	{
		ar << byProtID_ << byFuncID_ << dwGatherID << rGatherAppear;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 5, Function: 19";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CMapProtSvr::BuildPkg_GatherChange(
	UINT32 dwGatherID, //采集物ID
	const SGatherAppear& rGatherAppear //采集物外观
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 19;
	try
	{
		ar << byProtID_ << byFuncID_ << dwGatherID << rGatherAppear;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 5, Function: 19";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：阻挡物出现
bool CMapProtSvr::Send_BlockerAppear(
	UINT32 dwInstID, //唯一ID
	const SBlockerAppear& rBlockerAppear, //阻挡物开关
	const SPosition& rPosition, //出现位置
	float fDir, //方向(弧度)
	bool bBorn //true为出生，false为进入视野
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 20;
	try
	{
		ar << byProtID_ << byFuncID_ << dwInstID << rBlockerAppear << rPosition << fDir << bBorn;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 5, Function: 20";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CMapProtSvr::SendClt_BlockerAppear(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT32 dwInstID, //唯一ID
	const SBlockerAppear& rBlockerAppear, //阻挡物开关
	const SPosition& rPosition, //出现位置
	float fDir, //方向(弧度)
	bool bBorn //true为出生，false为进入视野
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 20;
	try
	{
		ar << byProtID_ << byFuncID_ << dwInstID << rBlockerAppear << rPosition << fDir << bBorn;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 5, Function: 20";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CMapProtSvr::BuildPkg_BlockerAppear(
	UINT32 dwInstID, //唯一ID
	const SBlockerAppear& rBlockerAppear, //阻挡物开关
	const SPosition& rPosition, //出现位置
	float fDir, //方向(弧度)
	bool bBorn //true为出生，false为进入视野
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 20;
	try
	{
		ar << byProtID_ << byFuncID_ << dwInstID << rBlockerAppear << rPosition << fDir << bBorn;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 5, Function: 20";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：通知地图上阻挡物消失
bool CMapProtSvr::Send_BlockerDisappear(
	UINT32 dwInstID //阻挡物唯一ID
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 21;
	try
	{
		ar << byProtID_ << byFuncID_ << dwInstID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 5, Function: 21";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CMapProtSvr::SendClt_BlockerDisappear(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT32 dwInstID //阻挡物唯一ID
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 21;
	try
	{
		ar << byProtID_ << byFuncID_ << dwInstID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 5, Function: 21";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CMapProtSvr::BuildPkg_BlockerDisappear(
	UINT32 dwInstID //阻挡物唯一ID
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 21;
	try
	{
		ar << byProtID_ << byFuncID_ << dwInstID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 5, Function: 21";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：通知怪物改变
bool CMapProtSvr::Send_MonsterChange(
	UINT64 qwCreatureID, //生物ID
	const SMonsterAppear& rMonsterAppear //怪物外观
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 22;
	try
	{
		ar << byProtID_ << byFuncID_ << qwCreatureID << rMonsterAppear;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 5, Function: 22";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CMapProtSvr::SendClt_MonsterChange(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT64 qwCreatureID, //生物ID
	const SMonsterAppear& rMonsterAppear //怪物外观
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 22;
	try
	{
		ar << byProtID_ << byFuncID_ << qwCreatureID << rMonsterAppear;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 5, Function: 22";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CMapProtSvr::BuildPkg_MonsterChange(
	UINT64 qwCreatureID, //生物ID
	const SMonsterAppear& rMonsterAppear //怪物外观
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 22;
	try
	{
		ar << byProtID_ << byFuncID_ << qwCreatureID << rMonsterAppear;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 5, Function: 22";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：通知区域出现
bool CMapProtSvr::Send_AreaAppear(
	UINT32 dwAreaID, //区域实例ID
	const SAreaAppear& rAreaAppear, //区域外观
	const SPosition& rPosition //出现位置
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 23;
	try
	{
		ar << byProtID_ << byFuncID_ << dwAreaID << rAreaAppear << rPosition;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 5, Function: 23";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CMapProtSvr::SendClt_AreaAppear(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT32 dwAreaID, //区域实例ID
	const SAreaAppear& rAreaAppear, //区域外观
	const SPosition& rPosition //出现位置
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 23;
	try
	{
		ar << byProtID_ << byFuncID_ << dwAreaID << rAreaAppear << rPosition;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 5, Function: 23";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CMapProtSvr::BuildPkg_AreaAppear(
	UINT32 dwAreaID, //区域实例ID
	const SAreaAppear& rAreaAppear, //区域外观
	const SPosition& rPosition //出现位置
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 23;
	try
	{
		ar << byProtID_ << byFuncID_ << dwAreaID << rAreaAppear << rPosition;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 5, Function: 23";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：通知地图上区域消失
bool CMapProtSvr::Send_AreaDisappear(
	UINT32 dwAreaID //区域实例ID
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 24;
	try
	{
		ar << byProtID_ << byFuncID_ << dwAreaID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 5, Function: 24";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CMapProtSvr::SendClt_AreaDisappear(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT32 dwAreaID //区域实例ID
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 24;
	try
	{
		ar << byProtID_ << byFuncID_ << dwAreaID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 5, Function: 24";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CMapProtSvr::BuildPkg_AreaDisappear(
	UINT32 dwAreaID //区域实例ID
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 24;
	try
	{
		ar << byProtID_ << byFuncID_ << dwAreaID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 5, Function: 24";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：怪物发现敌人
bool CMapProtSvr::Send_MonsterTargetChange(
	UINT64 qwMonsterID, //怪物ID
	UINT64 qwTargetID //目标ID
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 25;
	try
	{
		ar << byProtID_ << byFuncID_ << qwMonsterID << qwTargetID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 5, Function: 25";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CMapProtSvr::SendClt_MonsterTargetChange(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT64 qwMonsterID, //怪物ID
	UINT64 qwTargetID //目标ID
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 25;
	try
	{
		ar << byProtID_ << byFuncID_ << qwMonsterID << qwTargetID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 5, Function: 25";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CMapProtSvr::BuildPkg_MonsterTargetChange(
	UINT64 qwMonsterID, //怪物ID
	UINT64 qwTargetID //目标ID
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 25;
	try
	{
		ar << byProtID_ << byFuncID_ << qwMonsterID << qwTargetID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 5, Function: 25";
		_strPkg.clear();
	}
	return _strPkg;
}

bool CMapProtSvr::_DoRecv_PlayerMoveReq(const char* pBuf_, UINT32 dwLen_)
{
	UINT16 wMapID = 0;
	TVecPosition vecPosition;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> wMapID >> vecPosition;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 5, Function: 1";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	OnRecv_PlayerMoveReq(wMapID, vecPosition);
	return true;
}

bool CMapProtSvr::_DoRecv_PlayerStopReq(const char* pBuf_, UINT32 dwLen_)
{
	UINT16 wMapID = 0;
	SPosition StopPos;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> wMapID >> StopPos;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 5, Function: 2";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	OnRecv_PlayerStopReq(wMapID, StopPos);
	return true;
}

CMapProtSvr::SGetPlayerAppearAck::SGetPlayerAppearAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			byRet(0) { }

void CMapProtSvr::SGetPlayerAppearAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -1;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << byRet << rPlayerAppear;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 5, Function: 3";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CMapProtSvr::_DoRecv_GetPlayerAppear(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT64 qwUserID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> qwUserID;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 5, Function: 3";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SGetPlayerAppearAck> fnAck_(new SGetPlayerAppearAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetPlayerAppear(qwUserID, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CMapProtSvr::SJumpMapAck::SJumpMapAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			byRet(0), wMapID(0), byIndex(0) { }

void CMapProtSvr::SJumpMapAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -2;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << byRet << wMapID << byIndex;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 5, Function: 4";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CMapProtSvr::_DoRecv_JumpMap(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT16 wMapID = 0;
	UINT8 byIndex = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> wMapID >> byIndex;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 5, Function: 4";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SJumpMapAck> fnAck_(new SJumpMapAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_JumpMap(wMapID, byIndex, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CMapProtSvr::SGetMapOverLoadAck::SGetMapOverLoadAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			wMapID(0) { }

void CMapProtSvr::SGetMapOverLoadAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -3;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << wMapID << vecLoad;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 5, Function: 5";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CMapProtSvr::_DoRecv_GetMapOverLoad(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT16 wMapID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> wMapID;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 5, Function: 5";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SGetMapOverLoadAck> fnAck_(new SGetMapOverLoadAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetMapOverLoad(wMapID, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

} //namespace NMapProt
