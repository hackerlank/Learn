/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    LingShanProt.cpp
//  Purpose:      灵山（改名秘境）寻宝
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "LingShanProtSvr.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NLingShanProt
{

CLingShanProtSvr::THandleFunc CLingShanProtSvr::_HandleFuncs[] =
{
	&CLingShanProtSvr::_DoRecv_GetStatus, //FuncID: 1
	&CLingShanProtSvr::_DoRecv_Reg, //FuncID: 2
	&CLingShanProtSvr::_DoRecv_GetMatchInfo, //FuncID: 3
	&CLingShanProtSvr::_DoRecv_GetMathSelInfo, //FuncID: 4
	&CLingShanProtSvr::_DoRecv_ChangeModel, //FuncID: 5
	&CLingShanProtSvr::_DoRecv_MoveSelect, //FuncID: 6
	&CLingShanProtSvr::_DoRecv_GetActInfo, //FuncID: 7
	&CLingShanProtSvr::_DoRecv_Chat, //FuncID: 8
	&CLingShanProtSvr::_DoRecv_GetRoomList, //FuncID: 9
	&CLingShanProtSvr::_DoRecv_EnterVisitRoom, //FuncID: 10
	&CLingShanProtSvr::_DoRecv_LeaveVisitRoom, //FuncID: 11
	&CLingShanProtSvr::_DoRecv_GetPlayMovieInfo, //FuncID: 12
};

bool CLingShanProtSvr::HandleMessage(const char* pBuf, UINT32 dwLen)
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

//发送：玩家个人血量通知
bool CLingShanProtSvr::Send_SelHPRateNotify(
	float fHPRate //血量百分比
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << fHPRate;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 135, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CLingShanProtSvr::SendClt_SelHPRateNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	float fHPRate //血量百分比
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << fHPRate;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 135, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CLingShanProtSvr::BuildPkg_SelHPRateNotify(
	float fHPRate //血量百分比
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << fHPRate;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 135, Function: 1";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：玩家自己当前状态通知
bool CLingShanProtSvr::Send_StatusNotify(
	ELingShanStatus eRet, //当前状态
	UINT32 dwParam, //排队状态－排队编号,移动状态－移动结束时间，播放状态－下一轮时间
	UINT32 dwTime, //服务器时间戳
	UINT16 wRoomID //房间id
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eRet << dwParam << dwTime << wRoomID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 135, Function: 2";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CLingShanProtSvr::SendClt_StatusNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	ELingShanStatus eRet, //当前状态
	UINT32 dwParam, //排队状态－排队编号,移动状态－移动结束时间，播放状态－下一轮时间
	UINT32 dwTime, //服务器时间戳
	UINT16 wRoomID //房间id
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eRet << dwParam << dwTime << wRoomID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 135, Function: 2";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CLingShanProtSvr::BuildPkg_StatusNotify(
	ELingShanStatus eRet, //当前状态
	UINT32 dwParam, //排队状态－排队编号,移动状态－移动结束时间，播放状态－下一轮时间
	UINT32 dwTime, //服务器时间戳
	UINT16 wRoomID //房间id
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eRet << dwParam << dwTime << wRoomID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 135, Function: 2";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：观看房间当前状态通知
bool CLingShanProtSvr::Send_VisitRoomStatusNotify(
	ELingShanStatus eRet, //当前状态
	UINT32 dwParam, //排队状态－排队编号,移动状态－移动结束时间，播放状态－下一轮时间
	UINT32 dwTime //服务器时间戳
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eRet << dwParam << dwTime;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 135, Function: 3";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CLingShanProtSvr::SendClt_VisitRoomStatusNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	ELingShanStatus eRet, //当前状态
	UINT32 dwParam, //排队状态－排队编号,移动状态－移动结束时间，播放状态－下一轮时间
	UINT32 dwTime //服务器时间戳
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eRet << dwParam << dwTime;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 135, Function: 3";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CLingShanProtSvr::BuildPkg_VisitRoomStatusNotify(
	ELingShanStatus eRet, //当前状态
	UINT32 dwParam, //排队状态－排队编号,移动状态－移动结束时间，播放状态－下一轮时间
	UINT32 dwTime //服务器时间戳
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eRet << dwParam << dwTime;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 135, Function: 3";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：玩家移动结果通知
bool CLingShanProtSvr::Send_PlayerMoveNotify(
	const TVecPlayerMoveInfo& vecPlayerMoveInfo, //玩家移动路径
	UINT16 wRoomID //房间id
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << vecPlayerMoveInfo << wRoomID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 135, Function: 4";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CLingShanProtSvr::SendClt_PlayerMoveNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	const TVecPlayerMoveInfo& vecPlayerMoveInfo, //玩家移动路径
	UINT16 wRoomID //房间id
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << vecPlayerMoveInfo << wRoomID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 135, Function: 4";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CLingShanProtSvr::BuildPkg_PlayerMoveNotify(
	const TVecPlayerMoveInfo& vecPlayerMoveInfo, //玩家移动路径
	UINT16 wRoomID //房间id
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << vecPlayerMoveInfo << wRoomID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 135, Function: 4";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：玩家路径碰撞结果通知
bool CLingShanProtSvr::Send_PathCollideNotify(
	const TVecPathCollideInfo& vecPathCollideInfo, //路径碰撞
	UINT16 wRoomID //房间id
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 5;
	try
	{
		ar << byProtID_ << byFuncID_ << vecPathCollideInfo << wRoomID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 135, Function: 5";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CLingShanProtSvr::SendClt_PathCollideNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	const TVecPathCollideInfo& vecPathCollideInfo, //路径碰撞
	UINT16 wRoomID //房间id
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 5;
	try
	{
		ar << byProtID_ << byFuncID_ << vecPathCollideInfo << wRoomID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 135, Function: 5";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CLingShanProtSvr::BuildPkg_PathCollideNotify(
	const TVecPathCollideInfo& vecPathCollideInfo, //路径碰撞
	UINT16 wRoomID //房间id
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 5;
	try
	{
		ar << byProtID_ << byFuncID_ << vecPathCollideInfo << wRoomID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 135, Function: 5";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：玩家格子碰撞结果通知
bool CLingShanProtSvr::Send_GridCollideNotify(
	const TVecGridCollideInfo& vecGridCollideInfo, //格子碰撞
	UINT16 wRoomID //房间id
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 6;
	try
	{
		ar << byProtID_ << byFuncID_ << vecGridCollideInfo << wRoomID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 135, Function: 6";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CLingShanProtSvr::SendClt_GridCollideNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	const TVecGridCollideInfo& vecGridCollideInfo, //格子碰撞
	UINT16 wRoomID //房间id
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 6;
	try
	{
		ar << byProtID_ << byFuncID_ << vecGridCollideInfo << wRoomID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 135, Function: 6";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CLingShanProtSvr::BuildPkg_GridCollideNotify(
	const TVecGridCollideInfo& vecGridCollideInfo, //格子碰撞
	UINT16 wRoomID //房间id
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 6;
	try
	{
		ar << byProtID_ << byFuncID_ << vecGridCollideInfo << wRoomID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 135, Function: 6";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：新玩家进入
bool CLingShanProtSvr::Send_NewPlayerEnterNotify(
	const TVecRoomPlayInfo& vecRoomPlayInfo, //玩家列表
	UINT16 wRoomID //房间id
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 7;
	try
	{
		ar << byProtID_ << byFuncID_ << vecRoomPlayInfo << wRoomID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 135, Function: 7";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CLingShanProtSvr::SendClt_NewPlayerEnterNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	const TVecRoomPlayInfo& vecRoomPlayInfo, //玩家列表
	UINT16 wRoomID //房间id
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 7;
	try
	{
		ar << byProtID_ << byFuncID_ << vecRoomPlayInfo << wRoomID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 135, Function: 7";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CLingShanProtSvr::BuildPkg_NewPlayerEnterNotify(
	const TVecRoomPlayInfo& vecRoomPlayInfo, //玩家列表
	UINT16 wRoomID //房间id
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 7;
	try
	{
		ar << byProtID_ << byFuncID_ << vecRoomPlayInfo << wRoomID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 135, Function: 7";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：新一轮开始
bool CLingShanProtSvr::Send_NewTurnBeginNotify(
	bool bFreshBox, //是否刷新宝箱
	UINT16 wRoomID, //房间id
	UINT32 dwFreshTurn //至宝刷新剩余轮数
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 8;
	try
	{
		ar << byProtID_ << byFuncID_ << bFreshBox << wRoomID << dwFreshTurn;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 135, Function: 8";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CLingShanProtSvr::SendClt_NewTurnBeginNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	bool bFreshBox, //是否刷新宝箱
	UINT16 wRoomID, //房间id
	UINT32 dwFreshTurn //至宝刷新剩余轮数
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 8;
	try
	{
		ar << byProtID_ << byFuncID_ << bFreshBox << wRoomID << dwFreshTurn;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 135, Function: 8";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CLingShanProtSvr::BuildPkg_NewTurnBeginNotify(
	bool bFreshBox, //是否刷新宝箱
	UINT16 wRoomID, //房间id
	UINT32 dwFreshTurn //至宝刷新剩余轮数
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 8;
	try
	{
		ar << byProtID_ << byFuncID_ << bFreshBox << wRoomID << dwFreshTurn;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 135, Function: 8";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：模型修改
bool CLingShanProtSvr::Send_PlayerChangeModelNotify(
	UINT64 qwRoleID, //玩家id
	UINT32 dwModelID, //模型id
	UINT16 wRoomID //房间id
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 9;
	try
	{
		ar << byProtID_ << byFuncID_ << qwRoleID << dwModelID << wRoomID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 135, Function: 9";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CLingShanProtSvr::SendClt_PlayerChangeModelNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT64 qwRoleID, //玩家id
	UINT32 dwModelID, //模型id
	UINT16 wRoomID //房间id
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 9;
	try
	{
		ar << byProtID_ << byFuncID_ << qwRoleID << dwModelID << wRoomID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 135, Function: 9";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CLingShanProtSvr::BuildPkg_PlayerChangeModelNotify(
	UINT64 qwRoleID, //玩家id
	UINT32 dwModelID, //模型id
	UINT16 wRoomID //房间id
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 9;
	try
	{
		ar << byProtID_ << byFuncID_ << qwRoleID << dwModelID << wRoomID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 135, Function: 9";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：玩家奖励log
bool CLingShanProtSvr::Send_PlayerPrizeLogNotify(
	const TVecTakePrizeLog& vecTakePrizeLog //玩家奖励log列表
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 10;
	try
	{
		ar << byProtID_ << byFuncID_ << vecTakePrizeLog;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 135, Function: 10";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CLingShanProtSvr::SendClt_PlayerPrizeLogNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	const TVecTakePrizeLog& vecTakePrizeLog //玩家奖励log列表
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 10;
	try
	{
		ar << byProtID_ << byFuncID_ << vecTakePrizeLog;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 135, Function: 10";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CLingShanProtSvr::BuildPkg_PlayerPrizeLogNotify(
	const TVecTakePrizeLog& vecTakePrizeLog //玩家奖励log列表
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 10;
	try
	{
		ar << byProtID_ << byFuncID_ << vecTakePrizeLog;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 135, Function: 10";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：聊天
bool CLingShanProtSvr::Send_ChatNotify(
	UINT64 qwRoleID, //结果
	const std::string& strChatMsg, //聊天内容
	UINT16 wRoomID //房间id
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 11;
	try
	{
		ar << byProtID_ << byFuncID_ << qwRoleID << strChatMsg << wRoomID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 135, Function: 11";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CLingShanProtSvr::SendClt_ChatNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT64 qwRoleID, //结果
	const std::string& strChatMsg, //聊天内容
	UINT16 wRoomID //房间id
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 11;
	try
	{
		ar << byProtID_ << byFuncID_ << qwRoleID << strChatMsg << wRoomID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 135, Function: 11";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CLingShanProtSvr::BuildPkg_ChatNotify(
	UINT64 qwRoleID, //结果
	const std::string& strChatMsg, //聊天内容
	UINT16 wRoomID //房间id
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 11;
	try
	{
		ar << byProtID_ << byFuncID_ << qwRoleID << strChatMsg << wRoomID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 135, Function: 11";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：玩家数据更新
bool CLingShanProtSvr::Send_PlayerUpdateNotify(
	const TVecRoomPlayInfo& vecRoomPlayInfo, //玩家列表
	UINT16 wRoomID //房间id
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 12;
	try
	{
		ar << byProtID_ << byFuncID_ << vecRoomPlayInfo << wRoomID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 135, Function: 12";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CLingShanProtSvr::SendClt_PlayerUpdateNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	const TVecRoomPlayInfo& vecRoomPlayInfo, //玩家列表
	UINT16 wRoomID //房间id
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 12;
	try
	{
		ar << byProtID_ << byFuncID_ << vecRoomPlayInfo << wRoomID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 135, Function: 12";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CLingShanProtSvr::BuildPkg_PlayerUpdateNotify(
	const TVecRoomPlayInfo& vecRoomPlayInfo, //玩家列表
	UINT16 wRoomID //房间id
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 12;
	try
	{
		ar << byProtID_ << byFuncID_ << vecRoomPlayInfo << wRoomID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 135, Function: 12";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：从观察者房间踢掉
bool CLingShanProtSvr::Send_KickViewNotify(
	UINT16 wRoomID //进入的房间id
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 13;
	try
	{
		ar << byProtID_ << byFuncID_ << wRoomID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 135, Function: 13";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CLingShanProtSvr::SendClt_KickViewNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT16 wRoomID //进入的房间id
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 13;
	try
	{
		ar << byProtID_ << byFuncID_ << wRoomID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 135, Function: 13";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CLingShanProtSvr::BuildPkg_KickViewNotify(
	UINT16 wRoomID //进入的房间id
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 13;
	try
	{
		ar << byProtID_ << byFuncID_ << wRoomID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 135, Function: 13";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：从房间离开
bool CLingShanProtSvr::Send_KickPlayerNotify(
	UINT64 qwRoleID, //进入的房间id
	UINT16 wRoomID //进入的房间id
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 14;
	try
	{
		ar << byProtID_ << byFuncID_ << qwRoleID << wRoomID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 135, Function: 14";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CLingShanProtSvr::SendClt_KickPlayerNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT64 qwRoleID, //进入的房间id
	UINT16 wRoomID //进入的房间id
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 14;
	try
	{
		ar << byProtID_ << byFuncID_ << qwRoleID << wRoomID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 135, Function: 14";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CLingShanProtSvr::BuildPkg_KickPlayerNotify(
	UINT64 qwRoleID, //进入的房间id
	UINT16 wRoomID //进入的房间id
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 14;
	try
	{
		ar << byProtID_ << byFuncID_ << qwRoleID << wRoomID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 135, Function: 14";
		_strPkg.clear();
	}
	return _strPkg;
}

bool CLingShanProtSvr::_DoRecv_GetStatus(const char* pBuf_, UINT32 dwLen_)
{
	OnRecv_GetStatus();
	return true;
}

CLingShanProtSvr::SRegAck::SRegAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eRet((ELingShanOP)0) { }

void CLingShanProtSvr::SRegAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -1;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eRet;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 135, Function: 2";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CLingShanProtSvr::_DoRecv_Reg(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 135, Function: 2";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SRegAck> fnAck_(new SRegAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_Reg(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CLingShanProtSvr::SGetMatchInfoAck::SGetMatchInfoAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eRet((ELingShanOP)0), wRoomID(0), dwFreshTurn(0), eStatus((ELingShanStatus)0), dwParam(0), 
			dwTime(0), dwTurn(0) { }

void CLingShanProtSvr::SGetMatchInfoAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -2;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eRet << vecBoxInfo << vecRoomPlayInfo << vecRoomMonsterInfo << wRoomID << dwFreshTurn << (UINT8&)eStatus << dwParam << dwTime << oPlayMovieInfo << vecTakePrizeLog << dwTurn;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 135, Function: 3";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CLingShanProtSvr::_DoRecv_GetMatchInfo(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 135, Function: 3";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SGetMatchInfoAck> fnAck_(new SGetMatchInfoAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetMatchInfo(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CLingShanProtSvr::SGetMathSelInfoAck::SGetMathSelInfoAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eRet((ELingShanOP)0), eStatus((ELingShanStatus)0), fHPRate(0), dwBoxCnt(0), dwSuiYuan(0), 
			dwRoomID(0), dwFreshTurn(0), dwModelID(0) { }

void CLingShanProtSvr::SGetMathSelInfoAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -3;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eRet << (UINT8&)eStatus << oRoomPlayInfo << fHPRate << dwBoxCnt << dwSuiYuan << dwRoomID << dwFreshTurn << dwModelID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 135, Function: 4";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CLingShanProtSvr::_DoRecv_GetMathSelInfo(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 135, Function: 4";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SGetMathSelInfoAck> fnAck_(new SGetMathSelInfoAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetMathSelInfo(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CLingShanProtSvr::SChangeModelAck::SChangeModelAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eRet((ELingShanOP)0), dwModelID(0) { }

void CLingShanProtSvr::SChangeModelAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -4;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eRet << dwModelID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 135, Function: 5";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CLingShanProtSvr::_DoRecv_ChangeModel(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT32 dwModelID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> dwModelID;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 135, Function: 5";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SChangeModelAck> fnAck_(new SChangeModelAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_ChangeModel(dwModelID, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CLingShanProtSvr::SMoveSelectAck::SMoveSelectAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eRet((ELingShanOP)0), dwCdTime(0) { }

void CLingShanProtSvr::SMoveSelectAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -5;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eRet << dwCdTime;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 135, Function: 6";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CLingShanProtSvr::_DoRecv_MoveSelect(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT16 wPos = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> wPos;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 135, Function: 6";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SMoveSelectAck> fnAck_(new SMoveSelectAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_MoveSelect(wPos, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CLingShanProtSvr::SGetActInfoAck::SGetActInfoAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eRet((ELingShanOP)0), dwBeginTime(0), dwEndTime(0) { }

void CLingShanProtSvr::SGetActInfoAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -6;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eRet << dwBeginTime << dwEndTime;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 135, Function: 7";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CLingShanProtSvr::_DoRecv_GetActInfo(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 135, Function: 7";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SGetActInfoAck> fnAck_(new SGetActInfoAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetActInfo(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CLingShanProtSvr::SChatAck::SChatAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eRet((ELingShanOP)0) { }

void CLingShanProtSvr::SChatAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -7;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eRet;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 135, Function: 8";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CLingShanProtSvr::_DoRecv_Chat(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	std::string strChatMsg;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> strChatMsg;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 135, Function: 8";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SChatAck> fnAck_(new SChatAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_Chat(strChatMsg, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CLingShanProtSvr::SGetRoomListAck::SGetRoomListAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eRet((ELingShanOP)0) { }

void CLingShanProtSvr::SGetRoomListAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -8;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eRet << vecRoomInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 135, Function: 9";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CLingShanProtSvr::_DoRecv_GetRoomList(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 135, Function: 9";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SGetRoomListAck> fnAck_(new SGetRoomListAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetRoomList(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CLingShanProtSvr::SEnterVisitRoomAck::SEnterVisitRoomAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eRet((ELingShanOP)0) { }

void CLingShanProtSvr::SEnterVisitRoomAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -9;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eRet;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 135, Function: 10";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CLingShanProtSvr::_DoRecv_EnterVisitRoom(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT16 wRoomID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> wRoomID;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 135, Function: 10";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SEnterVisitRoomAck> fnAck_(new SEnterVisitRoomAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_EnterVisitRoom(wRoomID, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CLingShanProtSvr::SLeaveVisitRoomAck::SLeaveVisitRoomAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eRet((ELingShanOP)0) { }

void CLingShanProtSvr::SLeaveVisitRoomAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -10;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eRet;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 135, Function: 11";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CLingShanProtSvr::_DoRecv_LeaveVisitRoom(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 135, Function: 11";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SLeaveVisitRoomAck> fnAck_(new SLeaveVisitRoomAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_LeaveVisitRoom(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CLingShanProtSvr::SGetPlayMovieInfoAck::SGetPlayMovieInfoAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eRet((ELingShanOP)0), wRoomID(0), dwTurn(0) { }

void CLingShanProtSvr::SGetPlayMovieInfoAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -11;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eRet << oPlayMovieInfo << vecTakePrizeLog << wRoomID << dwTurn;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 135, Function: 12";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CLingShanProtSvr::_DoRecv_GetPlayMovieInfo(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 135, Function: 12";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SGetPlayMovieInfoAck> fnAck_(new SGetPlayMovieInfoAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetPlayMovieInfo(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

} //namespace NLingShanProt
