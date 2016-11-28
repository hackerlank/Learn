/************************************************************************
//  工具自动生成的客户端协议代码(UTF-8 With BOM)
//  File Name:    Game2CenterComm.cpp
//  Purpose:      GameServer到CenterServer的通信协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "Game2CenterCommClt.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NGame2CenterComm
{

CGame2CenterCommClt::THandleFunc CGame2CenterCommClt::_ReturnFuncs[] =
{
	&CGame2CenterCommClt::_DoReturn_GetCenterState, //FuncID: -1
	&CGame2CenterCommClt::_DoReturn_IsFriend, //FuncID: -2
	&CGame2CenterCommClt::_DoReturn_IsSameGuild, //FuncID: -3
	&CGame2CenterCommClt::_DoReturn_GetGuildID, //FuncID: -4
	&CGame2CenterCommClt::_DoReturn_GetGuildName, //FuncID: -5
	&CGame2CenterCommClt::_DoReturn_SubGuildContribution, //FuncID: -6
	&CGame2CenterCommClt::_DoReturn_GetSystemVar, //FuncID: -7
	&CGame2CenterCommClt::_DoReturn_SetSystemVar, //FuncID: -8
};

CGame2CenterCommClt::THandleFunc CGame2CenterCommClt::_HandleFuncs[] =
{
	&CGame2CenterCommClt::_DoRecv_ReplaceUser, //FuncID: 1
	&CGame2CenterCommClt::_DoRecv_GMCmd, //FuncID: 2
	&CGame2CenterCommClt::_DoRecv_AddTotalRecharge, //FuncID: 3
	&CGame2CenterCommClt::_DoRecv_AddRechargeMailItem, //FuncID: 4
	&CGame2CenterCommClt::_DoRecv_AddTotalPrepaid, //FuncID: 5
	&CGame2CenterCommClt::_DoRecv_AddQQCoinBuyItem, //FuncID: 6
	&CGame2CenterCommClt::_DoRecv_CheckMailAttch, //FuncID: 7
	&CGame2CenterCommClt::_DoRecv_SendMailAttch, //FuncID: 8
	&CGame2CenterCommClt::_DoRecv_SetSign, //FuncID: 9
	&CGame2CenterCommClt::_DoRecv_SetMood, //FuncID: 10
	&CGame2CenterCommClt::_DoRecv_FigtherToOther, //FuncID: 11
	&CGame2CenterCommClt::_DoRecv_CanPushLoot, //FuncID: 12
	&CGame2CenterCommClt::_DoRecv_PushLoot, //FuncID: 13
	&CGame2CenterCommClt::_DoRecv_ReduceItem, //FuncID: 14
	&CGame2CenterCommClt::_DoRecv_CanReduceItem, //FuncID: 15
	&CGame2CenterCommClt::_DoRecv_GetUserUINTProp, //FuncID: 16
	&CGame2CenterCommClt::_DoRecv_SetUserUINTProp, //FuncID: 17
	&CGame2CenterCommClt::_DoRecv_UserSubItem, //FuncID: 18
	&CGame2CenterCommClt::_DoRecv_UserAddItem, //FuncID: 19
	&CGame2CenterCommClt::_DoRecv_SendSysMsg, //FuncID: 20
	&CGame2CenterCommClt::_DoRecv_ActionNotify, //FuncID: 21
	&CGame2CenterCommClt::_DoRecv_BubbleNotify, //FuncID: 22
	&CGame2CenterCommClt::_DoRecv_GuildLevelUpdated, //FuncID: 23
	&CGame2CenterCommClt::_DoRecv_GuildNameUpdated, //FuncID: 24
	&CGame2CenterCommClt::_DoRecv_GuildTechUpdate, //FuncID: 25
	&CGame2CenterCommClt::_DoRecv_ReloadTable, //FuncID: 26
	&CGame2CenterCommClt::_DoRecv_TripodAttrUpdate, //FuncID: 27
	&CGame2CenterCommClt::_DoRecv_ProcessCond, //FuncID: 28
	&CGame2CenterCommClt::_DoRecv_UpgradeTripod, //FuncID: 29
	&CGame2CenterCommClt::_DoRecv_SpeedTripod, //FuncID: 30
	&CGame2CenterCommClt::_DoRecv_CheckHasFighter, //FuncID: 31
	&CGame2CenterCommClt::_DoRecv_GetBattlePoint, //FuncID: 32
	&CGame2CenterCommClt::_DoRecv_OnPlayerEvent, //FuncID: 33
	&CGame2CenterCommClt::_DoRecv_AddORSetGameVar, //FuncID: 34
	&CGame2CenterCommClt::_DoRecv_DeleteGameVar, //FuncID: 35
	&CGame2CenterCommClt::_DoRecv_AddMallDiscount, //FuncID: 36
	&CGame2CenterCommClt::_DoRecv_ClearMallDiscount, //FuncID: 37
	&CGame2CenterCommClt::_DoRecv_SubPlayerMoney, //FuncID: 38
	&CGame2CenterCommClt::_DoRecv_SetPlayerLevel, //FuncID: 39
	&CGame2CenterCommClt::_DoRecv_SetPlayerVIPLevel, //FuncID: 40
	&CGame2CenterCommClt::_DoRecv_SetDayTask, //FuncID: 41
	&CGame2CenterCommClt::_DoRecv_GetPlayerInfo, //FuncID: 42
	&CGame2CenterCommClt::_DoRecv_GetPlayerBagInfo, //FuncID: 43
	&CGame2CenterCommClt::_DoRecv_DelPlayerItem, //FuncID: 44
	&CGame2CenterCommClt::_DoRecv_SendSysMailByLootId, //FuncID: 45
	&CGame2CenterCommClt::_DoRecv_GetTaskStateForPlatfrom, //FuncID: 46
	&CGame2CenterCommClt::_DoRecv_SynWeiweiPersonNum, //FuncID: 47
	&CGame2CenterCommClt::_DoRecv_CheckCDK, //FuncID: 48
	&CGame2CenterCommClt::_DoRecv_SynQQAlarm, //FuncID: 49
	&CGame2CenterCommClt::_DoRecv_ModifyChest, //FuncID: 50
	&CGame2CenterCommClt::_DoRecv_SyncActivityTime, //FuncID: 51
	&CGame2CenterCommClt::_DoRecv_GetLoginDays, //FuncID: 52
	&CGame2CenterCommClt::_DoRecv_SyncActState, //FuncID: 53
	&CGame2CenterCommClt::_DoRecv_SyncTitle, //FuncID: 54
	&CGame2CenterCommClt::_DoRecv_SubGoldOrCoupon, //FuncID: 55
};

CGame2CenterCommClt::TTimeOutFunc CGame2CenterCommClt::_TimeoutFuncs[] =
{
	&CGame2CenterCommClt::_OnTimeOut_GetCenterState, //FuncID: 1
	&CGame2CenterCommClt::_OnTimeOut_IsFriend, //FuncID: 2
	&CGame2CenterCommClt::_OnTimeOut_IsSameGuild, //FuncID: 3
	&CGame2CenterCommClt::_OnTimeOut_GetGuildID, //FuncID: 4
	&CGame2CenterCommClt::_OnTimeOut_GetGuildName, //FuncID: 5
	&CGame2CenterCommClt::_OnTimeOut_SubGuildContribution, //FuncID: 6
	&CGame2CenterCommClt::_OnTimeOut_GetSystemVar, //FuncID: 7
	&CGame2CenterCommClt::_OnTimeOut_SetSystemVar, //FuncID: 8
};

bool CGame2CenterCommClt::HandleMessage(const char* pBuf, UINT32 dwLen)
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

void CGame2CenterCommClt::OnTimeOut(UINT8 byFuncID, UINT32 dwSessionID)
{
	if(byFuncID == 0 || byFuncID > (UINT8)ARRAYSIZE(_TimeoutFuncs))
		return;
	(this->*_TimeoutFuncs[byFuncID - 1])(dwSessionID);
}

//发送：心跳
bool CGame2CenterCommClt::Send_KeepAlive(
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 12, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterCommClt::SendSvr_KeepAlive(const UINT32* pSvrID_, UINT8 byCnt_
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 12, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGame2CenterCommClt::BuildPkg_KeepAlive(
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 12, Function: 1";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：GameServer初始化完成通知
bool CGame2CenterCommClt::Send_GameSvrInitNft(
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 12, Function: 2";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterCommClt::SendSvr_GameSvrInitNft(const UINT32* pSvrID_, UINT8 byCnt_
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 12, Function: 2";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGame2CenterCommClt::BuildPkg_GameSvrInitNft(
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 12, Function: 2";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：CenterServer状态请求
bool CGame2CenterCommClt::Send_GetCenterState(
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
		ar << byProtID_ << byFuncID_ << dwSessionID_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 12, Function: 3";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterCommClt::SendSvr_GetCenterState(const UINT32* pSvrID_, UINT8 byCnt_,
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
		ar << byProtID_ << byFuncID_ << dwSessionID_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 12, Function: 3";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

//发送：GameServer数据同步请求
bool CGame2CenterCommClt::Send_GameSvrDataSyncReq(
	ESyncKey eSyncKey, //同步Key
	UINT16 wDestGroup, //目的服务器组号
	UINT8 byDestIndex, //目的GameServer(0为全部)
	const TVecINT32& vecParam, //同步参数
	const std::string& strSyncData //同步数据
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eSyncKey << wDestGroup << byDestIndex << vecParam << strSyncData;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 12, Function: 4";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterCommClt::SendSvr_GameSvrDataSyncReq(const UINT32* pSvrID_, UINT8 byCnt_,
	ESyncKey eSyncKey, //同步Key
	UINT16 wDestGroup, //目的服务器组号
	UINT8 byDestIndex, //目的GameServer(0为全部)
	const TVecINT32& vecParam, //同步参数
	const std::string& strSyncData //同步数据
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eSyncKey << wDestGroup << byDestIndex << vecParam << strSyncData;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 12, Function: 4";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGame2CenterCommClt::BuildPkg_GameSvrDataSyncReq(
	ESyncKey eSyncKey, //同步Key
	UINT16 wDestGroup, //目的服务器组号
	UINT8 byDestIndex, //目的GameServer(0为全部)
	const TVecINT32& vecParam, //同步参数
	const std::string& strSyncData //同步数据
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eSyncKey << wDestGroup << byDestIndex << vecParam << strSyncData;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 12, Function: 4";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：账号进入游戏通知
bool CGame2CenterCommClt::Send_UserLoginNtf(
	UINT64 qwUsrID, //账号ID
	const SUserEnterInfo& rUserInfo //帐号进入信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 5;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << rUserInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 12, Function: 5";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterCommClt::SendSvr_UserLoginNtf(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwUsrID, //账号ID
	const SUserEnterInfo& rUserInfo //帐号进入信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 5;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << rUserInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 12, Function: 5";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGame2CenterCommClt::BuildPkg_UserLoginNtf(
	UINT64 qwUsrID, //账号ID
	const SUserEnterInfo& rUserInfo //帐号进入信息
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 5;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << rUserInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 12, Function: 5";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：账号退出游戏通知
bool CGame2CenterCommClt::Send_UserLogoutNtf(
	UINT64 qwUsrID //账号ID
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 6;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 12, Function: 6";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterCommClt::SendSvr_UserLogoutNtf(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwUsrID //账号ID
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 6;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 12, Function: 6";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGame2CenterCommClt::BuildPkg_UserLogoutNtf(
	UINT64 qwUsrID //账号ID
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 6;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 12, Function: 6";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：账号替换通知
bool CGame2CenterCommClt::Send_UserReplaceNtf(
	UINT64 qwUsrID //账号ID
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 7;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 12, Function: 7";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterCommClt::SendSvr_UserReplaceNtf(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwUsrID //账号ID
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 7;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 12, Function: 7";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGame2CenterCommClt::BuildPkg_UserReplaceNtf(
	UINT64 qwUsrID //账号ID
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 7;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 12, Function: 7";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：帐号跳GameServer通知
bool CGame2CenterCommClt::Send_UserJumpSvrNtf(
	UINT64 qwUsrID //账号ID
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 8;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 12, Function: 8";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterCommClt::SendSvr_UserJumpSvrNtf(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwUsrID //账号ID
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 8;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 12, Function: 8";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGame2CenterCommClt::BuildPkg_UserJumpSvrNtf(
	UINT64 qwUsrID //账号ID
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 8;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 12, Function: 8";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：玩家同步属性通知
bool CGame2CenterCommClt::Send_UserSyncPropNtf(
	UINT64 qwUsrID, //账号ID
	EUserSyncPropField eField, //同步属性类型
	const std::string& strVal //值序列化字符串
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 9;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << (UINT8&)eField << strVal;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 12, Function: 9";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterCommClt::SendSvr_UserSyncPropNtf(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwUsrID, //账号ID
	EUserSyncPropField eField, //同步属性类型
	const std::string& strVal //值序列化字符串
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 9;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << (UINT8&)eField << strVal;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 12, Function: 9";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGame2CenterCommClt::BuildPkg_UserSyncPropNtf(
	UINT64 qwUsrID, //账号ID
	EUserSyncPropField eField, //同步属性类型
	const std::string& strVal //值序列化字符串
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 9;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << (UINT8&)eField << strVal;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 12, Function: 9";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：是否为好友
bool CGame2CenterCommClt::Send_IsFriend(
	UINT64 qwUsrID, //账号ID
	UINT64 qwFriID, //好友账号ID
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT8 byRet //(返回值)0是好友 1非好友
	)> fnOnReturn_ //返回时的回调函数
)
{
	if(_pSessionMgr == NULL)
	{
		LOG_CRI << "_pSessionMgr == NULL";		return false;
	}
	UINT32 dwSessionID_ = _pSessionMgr->GetNewSession(*this, 2);
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_(new TSessData(fnOnReturn_));
	_pSessionMgr->StoreData(dwSessionID_, pSessData_);
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 10;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwUsrID << qwFriID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 12, Function: 10";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterCommClt::SendSvr_IsFriend(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwUsrID, //账号ID
	UINT64 qwFriID, //好友账号ID
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT8 byRet //(返回值)0是好友 1非好友
	)> fnOnReturn_ //返回时的回调函数
)
{
	if(_pSessionMgr == NULL)
	{
		LOG_CRI << "_pSessionMgr == NULL";		return false;
	}
	UINT32 dwSessionID_ = _pSessionMgr->GetNewSession(*this, 2);
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_(new TSessData(fnOnReturn_));
	_pSessionMgr->StoreData(dwSessionID_, pSessData_);
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 10;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwUsrID << qwFriID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 12, Function: 10";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

//发送：是否在同一个帮派
bool CGame2CenterCommClt::Send_IsSameGuild(
	UINT64 qwUsrID, //账号ID
	UINT64 qwOtherID, //帮派成员ID
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT8 byRet //(返回值)0在同一个帮派 1不在同一个帮派
	)> fnOnReturn_ //返回时的回调函数
)
{
	if(_pSessionMgr == NULL)
	{
		LOG_CRI << "_pSessionMgr == NULL";		return false;
	}
	UINT32 dwSessionID_ = _pSessionMgr->GetNewSession(*this, 3);
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_(new TSessData(fnOnReturn_));
	_pSessionMgr->StoreData(dwSessionID_, pSessData_);
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 11;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwUsrID << qwOtherID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 12, Function: 11";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterCommClt::SendSvr_IsSameGuild(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwUsrID, //账号ID
	UINT64 qwOtherID, //帮派成员ID
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT8 byRet //(返回值)0在同一个帮派 1不在同一个帮派
	)> fnOnReturn_ //返回时的回调函数
)
{
	if(_pSessionMgr == NULL)
	{
		LOG_CRI << "_pSessionMgr == NULL";		return false;
	}
	UINT32 dwSessionID_ = _pSessionMgr->GetNewSession(*this, 3);
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_(new TSessData(fnOnReturn_));
	_pSessionMgr->StoreData(dwSessionID_, pSessData_);
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 11;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwUsrID << qwOtherID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 12, Function: 11";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

//发送：发送系统邮件,自定义字符串
bool CGame2CenterCommClt::Send_SendMail(
	const std::string& strSender, //发送者
	const std::string& strTitle, //标题
	const NMailProt::SysMailSendTxt& strMsgInfo, //内容
	const NMailProt::TVecMailAttachment& vecItemInfo, //物品信息
	const TVecUINT64& vecTargetIDs //接受者IDs
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 12;
	try
	{
		ar << byProtID_ << byFuncID_ << strSender << strTitle << strMsgInfo << vecItemInfo << vecTargetIDs;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 12, Function: 12";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterCommClt::SendSvr_SendMail(const UINT32* pSvrID_, UINT8 byCnt_,
	const std::string& strSender, //发送者
	const std::string& strTitle, //标题
	const NMailProt::SysMailSendTxt& strMsgInfo, //内容
	const NMailProt::TVecMailAttachment& vecItemInfo, //物品信息
	const TVecUINT64& vecTargetIDs //接受者IDs
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 12;
	try
	{
		ar << byProtID_ << byFuncID_ << strSender << strTitle << strMsgInfo << vecItemInfo << vecTargetIDs;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 12, Function: 12";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGame2CenterCommClt::BuildPkg_SendMail(
	const std::string& strSender, //发送者
	const std::string& strTitle, //标题
	const NMailProt::SysMailSendTxt& strMsgInfo, //内容
	const NMailProt::TVecMailAttachment& vecItemInfo, //物品信息
	const TVecUINT64& vecTargetIDs //接受者IDs
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 12;
	try
	{
		ar << byProtID_ << byFuncID_ << strSender << strTitle << strMsgInfo << vecItemInfo << vecTargetIDs;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 12, Function: 12";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：获取帮派ID
bool CGame2CenterCommClt::Send_GetGuildID(
	UINT64 qwRoleID, //玩家ID
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT64 qwGuildID, //(返回值)帮派ID
		const std::string& strGuildName, //(返回值)帮派名称
		UINT8 byGuildLvl, //(返回值)帮派等级
		const std::string& strGuildOwnerName //(返回值)帮主名称
	)> fnOnReturn_ //返回时的回调函数
)
{
	if(_pSessionMgr == NULL)
	{
		LOG_CRI << "_pSessionMgr == NULL";		return false;
	}
	UINT32 dwSessionID_ = _pSessionMgr->GetNewSession(*this, 4);
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_(new TSessData(fnOnReturn_));
	_pSessionMgr->StoreData(dwSessionID_, pSessData_);
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 13;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwRoleID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 12, Function: 13";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterCommClt::SendSvr_GetGuildID(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwRoleID, //玩家ID
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT64 qwGuildID, //(返回值)帮派ID
		const std::string& strGuildName, //(返回值)帮派名称
		UINT8 byGuildLvl, //(返回值)帮派等级
		const std::string& strGuildOwnerName //(返回值)帮主名称
	)> fnOnReturn_ //返回时的回调函数
)
{
	if(_pSessionMgr == NULL)
	{
		LOG_CRI << "_pSessionMgr == NULL";		return false;
	}
	UINT32 dwSessionID_ = _pSessionMgr->GetNewSession(*this, 4);
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_(new TSessData(fnOnReturn_));
	_pSessionMgr->StoreData(dwSessionID_, pSessData_);
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 13;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwRoleID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 12, Function: 13";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

//发送：获取帮派ID
bool CGame2CenterCommClt::Send_GetGuildName(
	UINT64 qwGuildID, //帮派ID
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		bool bValid, //(返回值)是否已经找到
		UINT64 qwGuildID, //(返回值)帮派ID
		const std::string& strGuildName, //(返回值)帮派名称
		UINT8 byGuildLvl, //(返回值)帮派等级
		const std::string& strGuildOwnerName //(返回值)帮主名称
	)> fnOnReturn_ //返回时的回调函数
)
{
	if(_pSessionMgr == NULL)
	{
		LOG_CRI << "_pSessionMgr == NULL";		return false;
	}
	UINT32 dwSessionID_ = _pSessionMgr->GetNewSession(*this, 5);
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_(new TSessData(fnOnReturn_));
	_pSessionMgr->StoreData(dwSessionID_, pSessData_);
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 14;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwGuildID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 12, Function: 14";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterCommClt::SendSvr_GetGuildName(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwGuildID, //帮派ID
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		bool bValid, //(返回值)是否已经找到
		UINT64 qwGuildID, //(返回值)帮派ID
		const std::string& strGuildName, //(返回值)帮派名称
		UINT8 byGuildLvl, //(返回值)帮派等级
		const std::string& strGuildOwnerName //(返回值)帮主名称
	)> fnOnReturn_ //返回时的回调函数
)
{
	if(_pSessionMgr == NULL)
	{
		LOG_CRI << "_pSessionMgr == NULL";		return false;
	}
	UINT32 dwSessionID_ = _pSessionMgr->GetNewSession(*this, 5);
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_(new TSessData(fnOnReturn_));
	_pSessionMgr->StoreData(dwSessionID_, pSessData_);
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 14;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwGuildID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 12, Function: 14";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

//发送：帮派广播
bool CGame2CenterCommClt::Send_NotifyGuildInfo(
	UINT64 qwGuildID, //帮派ID
	const TVecUINT64& vecExcpRoleID, //不需要通知的人ID
	const std::string& strData //具体信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 15;
	try
	{
		ar << byProtID_ << byFuncID_ << qwGuildID << vecExcpRoleID << strData;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 12, Function: 15";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterCommClt::SendSvr_NotifyGuildInfo(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwGuildID, //帮派ID
	const TVecUINT64& vecExcpRoleID, //不需要通知的人ID
	const std::string& strData //具体信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 15;
	try
	{
		ar << byProtID_ << byFuncID_ << qwGuildID << vecExcpRoleID << strData;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 12, Function: 15";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGame2CenterCommClt::BuildPkg_NotifyGuildInfo(
	UINT64 qwGuildID, //帮派ID
	const TVecUINT64& vecExcpRoleID, //不需要通知的人ID
	const std::string& strData //具体信息
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 15;
	try
	{
		ar << byProtID_ << byFuncID_ << qwGuildID << vecExcpRoleID << strData;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 12, Function: 15";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：同步增加icon
bool CGame2CenterCommClt::Send_SynIconAppear(
	UINT64 qwRoleID, //角色ID
	const std::string& szIcon //功能
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 16;
	try
	{
		ar << byProtID_ << byFuncID_ << qwRoleID << szIcon;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 12, Function: 16";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterCommClt::SendSvr_SynIconAppear(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwRoleID, //角色ID
	const std::string& szIcon //功能
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 16;
	try
	{
		ar << byProtID_ << byFuncID_ << qwRoleID << szIcon;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 12, Function: 16";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGame2CenterCommClt::BuildPkg_SynIconAppear(
	UINT64 qwRoleID, //角色ID
	const std::string& szIcon //功能
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 16;
	try
	{
		ar << byProtID_ << byFuncID_ << qwRoleID << szIcon;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 12, Function: 16";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：增加帮派贡献
bool CGame2CenterCommClt::Send_AddGuildContribution(
	UINT64 qwRoleID, //玩家ID
	UINT32 dwContribution //帮派贡献
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 17;
	try
	{
		ar << byProtID_ << byFuncID_ << qwRoleID << dwContribution;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 12, Function: 17";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterCommClt::SendSvr_AddGuildContribution(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwRoleID, //玩家ID
	UINT32 dwContribution //帮派贡献
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 17;
	try
	{
		ar << byProtID_ << byFuncID_ << qwRoleID << dwContribution;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 12, Function: 17";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGame2CenterCommClt::BuildPkg_AddGuildContribution(
	UINT64 qwRoleID, //玩家ID
	UINT32 dwContribution //帮派贡献
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 17;
	try
	{
		ar << byProtID_ << byFuncID_ << qwRoleID << dwContribution;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 12, Function: 17";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：增加玩家九疑鼎火种
bool CGame2CenterCommClt::Send_ActiveTripodFire(
	UINT64 qwRoleID, //玩家ID
	UINT16 wFireID //火种ID
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 18;
	try
	{
		ar << byProtID_ << byFuncID_ << qwRoleID << wFireID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 12, Function: 18";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterCommClt::SendSvr_ActiveTripodFire(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwRoleID, //玩家ID
	UINT16 wFireID //火种ID
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 18;
	try
	{
		ar << byProtID_ << byFuncID_ << qwRoleID << wFireID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 12, Function: 18";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGame2CenterCommClt::BuildPkg_ActiveTripodFire(
	UINT64 qwRoleID, //玩家ID
	UINT16 wFireID //火种ID
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 18;
	try
	{
		ar << byProtID_ << byFuncID_ << qwRoleID << wFireID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 12, Function: 18";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：更新登录参数
bool CGame2CenterCommClt::Send_UpdatePlatformParam(
	UINT64 qwRoleID, //玩家ID
	const NProtoCommon::TVecPlatformParam& vecPlatform, //平台参数列表
	UINT32 dwIndex //当前平台索引
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 19;
	try
	{
		ar << byProtID_ << byFuncID_ << qwRoleID << vecPlatform << dwIndex;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 12, Function: 19";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterCommClt::SendSvr_UpdatePlatformParam(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwRoleID, //玩家ID
	const NProtoCommon::TVecPlatformParam& vecPlatform, //平台参数列表
	UINT32 dwIndex //当前平台索引
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 19;
	try
	{
		ar << byProtID_ << byFuncID_ << qwRoleID << vecPlatform << dwIndex;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 12, Function: 19";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGame2CenterCommClt::BuildPkg_UpdatePlatformParam(
	UINT64 qwRoleID, //玩家ID
	const NProtoCommon::TVecPlatformParam& vecPlatform, //平台参数列表
	UINT32 dwIndex //当前平台索引
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 19;
	try
	{
		ar << byProtID_ << byFuncID_ << qwRoleID << vecPlatform << dwIndex;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 12, Function: 19";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：更新登录其他参数
bool CGame2CenterCommClt::Send_UpdateEnterString(
	UINT64 qwRoleID, //玩家ID
	const TVecString& vecEnterString //平台参数列表
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 20;
	try
	{
		ar << byProtID_ << byFuncID_ << qwRoleID << vecEnterString;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 12, Function: 20";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterCommClt::SendSvr_UpdateEnterString(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwRoleID, //玩家ID
	const TVecString& vecEnterString //平台参数列表
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 20;
	try
	{
		ar << byProtID_ << byFuncID_ << qwRoleID << vecEnterString;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 12, Function: 20";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGame2CenterCommClt::BuildPkg_UpdateEnterString(
	UINT64 qwRoleID, //玩家ID
	const TVecString& vecEnterString //平台参数列表
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 20;
	try
	{
		ar << byProtID_ << byFuncID_ << qwRoleID << vecEnterString;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 12, Function: 20";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：发送全服活动信息
bool CGame2CenterCommClt::Send_SendWonderType(
	EWonderActType eActType, //活动类型
	UINT64 qwRoleID, //玩家ID
	UINT32 dwCond //条件ID
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 21;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eActType << qwRoleID << dwCond;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 12, Function: 21";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterCommClt::SendSvr_SendWonderType(const UINT32* pSvrID_, UINT8 byCnt_,
	EWonderActType eActType, //活动类型
	UINT64 qwRoleID, //玩家ID
	UINT32 dwCond //条件ID
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 21;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eActType << qwRoleID << dwCond;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 12, Function: 21";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGame2CenterCommClt::BuildPkg_SendWonderType(
	EWonderActType eActType, //活动类型
	UINT64 qwRoleID, //玩家ID
	UINT32 dwCond //条件ID
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 21;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eActType << qwRoleID << dwCond;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 12, Function: 21";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：扣除帮贡
bool CGame2CenterCommClt::Send_SubGuildContribution(
	UINT64 qwRoleID, //玩家ID
	UINT32 dwContribution, //帮贡数量
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		NGuildProt::EGuildResult eResult //(返回值)检测结果
	)> fnOnReturn_ //返回时的回调函数
)
{
	if(_pSessionMgr == NULL)
	{
		LOG_CRI << "_pSessionMgr == NULL";		return false;
	}
	UINT32 dwSessionID_ = _pSessionMgr->GetNewSession(*this, 6);
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_(new TSessData(fnOnReturn_));
	_pSessionMgr->StoreData(dwSessionID_, pSessData_);
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 22;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwRoleID << dwContribution;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 12, Function: 22";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterCommClt::SendSvr_SubGuildContribution(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwRoleID, //玩家ID
	UINT32 dwContribution, //帮贡数量
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		NGuildProt::EGuildResult eResult //(返回值)检测结果
	)> fnOnReturn_ //返回时的回调函数
)
{
	if(_pSessionMgr == NULL)
	{
		LOG_CRI << "_pSessionMgr == NULL";		return false;
	}
	UINT32 dwSessionID_ = _pSessionMgr->GetNewSession(*this, 6);
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_(new TSessData(fnOnReturn_));
	_pSessionMgr->StoreData(dwSessionID_, pSessData_);
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 22;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwRoleID << dwContribution;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 12, Function: 22";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

//发送：美女抽奖log
bool CGame2CenterCommClt::Send_BeautyLotteryLog(
	const NBeautyLogGS::SBeautyLog& oBeautyLog //抽奖log
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 23;
	try
	{
		ar << byProtID_ << byFuncID_ << oBeautyLog;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 12, Function: 23";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterCommClt::SendSvr_BeautyLotteryLog(const UINT32* pSvrID_, UINT8 byCnt_,
	const NBeautyLogGS::SBeautyLog& oBeautyLog //抽奖log
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 23;
	try
	{
		ar << byProtID_ << byFuncID_ << oBeautyLog;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 12, Function: 23";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGame2CenterCommClt::BuildPkg_BeautyLotteryLog(
	const NBeautyLogGS::SBeautyLog& oBeautyLog //抽奖log
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 23;
	try
	{
		ar << byProtID_ << byFuncID_ << oBeautyLog;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 12, Function: 23";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：邀请好友成功
bool CGame2CenterCommClt::Send_InviteFriend(
	UINT64 qwUserID, //邀请人
	UINT64 qwInvitedUserID //被邀请人
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 24;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUserID << qwInvitedUserID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 12, Function: 24";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterCommClt::SendSvr_InviteFriend(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwUserID, //邀请人
	UINT64 qwInvitedUserID //被邀请人
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 24;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUserID << qwInvitedUserID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 12, Function: 24";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGame2CenterCommClt::BuildPkg_InviteFriend(
	UINT64 qwUserID, //邀请人
	UINT64 qwInvitedUserID //被邀请人
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 24;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUserID << qwInvitedUserID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 12, Function: 24";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：通知帮派兑换物品开始
bool CGame2CenterCommClt::Send_NotifyGuildExchangedItemBegin(
	const TVecLingShanShopData& vecLingShanShopData //灵山商店数据
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 25;
	try
	{
		ar << byProtID_ << byFuncID_ << vecLingShanShopData;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 12, Function: 25";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterCommClt::SendSvr_NotifyGuildExchangedItemBegin(const UINT32* pSvrID_, UINT8 byCnt_,
	const TVecLingShanShopData& vecLingShanShopData //灵山商店数据
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 25;
	try
	{
		ar << byProtID_ << byFuncID_ << vecLingShanShopData;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 12, Function: 25";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGame2CenterCommClt::BuildPkg_NotifyGuildExchangedItemBegin(
	const TVecLingShanShopData& vecLingShanShopData //灵山商店数据
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 25;
	try
	{
		ar << byProtID_ << byFuncID_ << vecLingShanShopData;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 12, Function: 25";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：同步在Center使用的buff结束时间(待修改完善)
bool CGame2CenterCommClt::Send_SyncGameBuffUseInCenter(
	UINT64 qwRoleID, //玩家ID
	UINT16 wBuffID, //buffID
	UINT32 dwEndTime //结束时间
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 26;
	try
	{
		ar << byProtID_ << byFuncID_ << qwRoleID << wBuffID << dwEndTime;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 12, Function: 26";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterCommClt::SendSvr_SyncGameBuffUseInCenter(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwRoleID, //玩家ID
	UINT16 wBuffID, //buffID
	UINT32 dwEndTime //结束时间
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 26;
	try
	{
		ar << byProtID_ << byFuncID_ << qwRoleID << wBuffID << dwEndTime;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 12, Function: 26";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGame2CenterCommClt::BuildPkg_SyncGameBuffUseInCenter(
	UINT64 qwRoleID, //玩家ID
	UINT16 wBuffID, //buffID
	UINT32 dwEndTime //结束时间
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 26;
	try
	{
		ar << byProtID_ << byFuncID_ << qwRoleID << wBuffID << dwEndTime;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 12, Function: 26";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：同步活动参数
bool CGame2CenterCommClt::Send_SyncGameActiveParam(
	ActiveParam eParam, //参数类型
	const TVecUINT32& vecParam //参数
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 27;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eParam << vecParam;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 12, Function: 27";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterCommClt::SendSvr_SyncGameActiveParam(const UINT32* pSvrID_, UINT8 byCnt_,
	ActiveParam eParam, //参数类型
	const TVecUINT32& vecParam //参数
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 27;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eParam << vecParam;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 12, Function: 27";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGame2CenterCommClt::BuildPkg_SyncGameActiveParam(
	ActiveParam eParam, //参数类型
	const TVecUINT32& vecParam //参数
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 27;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eParam << vecParam;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 12, Function: 27";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：获取全局Var值
bool CGame2CenterCommClt::Send_GetSystemVar(
	const TVecUINT16& vecVarID, //varID列表
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		const TVecUINT16& vecVars, //(返回值)varID列表
		const TVecUINT64& vecValues //(返回值)var数值列表(必须与vecVars对应)
	)> fnOnReturn_ //返回时的回调函数
)
{
	if(_pSessionMgr == NULL)
	{
		LOG_CRI << "_pSessionMgr == NULL";		return false;
	}
	UINT32 dwSessionID_ = _pSessionMgr->GetNewSession(*this, 7);
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_(new TSessData(fnOnReturn_));
	_pSessionMgr->StoreData(dwSessionID_, pSessData_);
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 28;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << vecVarID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 12, Function: 28";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterCommClt::SendSvr_GetSystemVar(const UINT32* pSvrID_, UINT8 byCnt_,
	const TVecUINT16& vecVarID, //varID列表
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		const TVecUINT16& vecVars, //(返回值)varID列表
		const TVecUINT64& vecValues //(返回值)var数值列表(必须与vecVars对应)
	)> fnOnReturn_ //返回时的回调函数
)
{
	if(_pSessionMgr == NULL)
	{
		LOG_CRI << "_pSessionMgr == NULL";		return false;
	}
	UINT32 dwSessionID_ = _pSessionMgr->GetNewSession(*this, 7);
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_(new TSessData(fnOnReturn_));
	_pSessionMgr->StoreData(dwSessionID_, pSessData_);
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 28;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << vecVarID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 12, Function: 28";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

//发送：设置全局Var值
bool CGame2CenterCommClt::Send_SetSystemVar(
	const TVecUINT16& vecVars, //varID列表
	const TVecUINT64& vecValues, //var数值列表(必须与vecVars对应)
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		const TVecUINT16& vecVarID //(返回值)设置成功的varID列表(只是校验用)
	)> fnOnReturn_ //返回时的回调函数
)
{
	if(_pSessionMgr == NULL)
	{
		LOG_CRI << "_pSessionMgr == NULL";		return false;
	}
	UINT32 dwSessionID_ = _pSessionMgr->GetNewSession(*this, 8);
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_(new TSessData(fnOnReturn_));
	_pSessionMgr->StoreData(dwSessionID_, pSessData_);
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 29;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << vecVars << vecValues;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 12, Function: 29";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterCommClt::SendSvr_SetSystemVar(const UINT32* pSvrID_, UINT8 byCnt_,
	const TVecUINT16& vecVars, //varID列表
	const TVecUINT64& vecValues, //var数值列表(必须与vecVars对应)
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		const TVecUINT16& vecVarID //(返回值)设置成功的varID列表(只是校验用)
	)> fnOnReturn_ //返回时的回调函数
)
{
	if(_pSessionMgr == NULL)
	{
		LOG_CRI << "_pSessionMgr == NULL";		return false;
	}
	UINT32 dwSessionID_ = _pSessionMgr->GetNewSession(*this, 8);
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_(new TSessData(fnOnReturn_));
	_pSessionMgr->StoreData(dwSessionID_, pSessData_);
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 29;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << vecVars << vecValues;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 12, Function: 29";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

CGame2CenterCommClt::SReplaceUserAck::SReplaceUserAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID) { }

void CGame2CenterCommClt::SReplaceUserAck::SendReturn(bool bRet_)
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
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 12, Function: 1";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CGame2CenterCommClt::_DoRecv_ReplaceUser(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 12, Function: 1";
		return false;
	}
	shared_func<SReplaceUserAck> fnAck_(new SReplaceUserAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_ReplaceUser(qwUsrID, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CGame2CenterCommClt::SGMCmdAck::SGMCmdAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID) { }

void CGame2CenterCommClt::SGMCmdAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -2;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 12, Function: 2";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CGame2CenterCommClt::_DoRecv_GMCmd(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT64 qwUsrID = 0;
	std::string strInfo;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> qwUsrID >> strInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 12, Function: 2";
		return false;
	}
	shared_func<SGMCmdAck> fnAck_(new SGMCmdAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_GMCmd(qwUsrID, strInfo, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CGame2CenterCommClt::SAddTotalRechargeAck::SAddTotalRechargeAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID) { }

void CGame2CenterCommClt::SAddTotalRechargeAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -3;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 12, Function: 3";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CGame2CenterCommClt::_DoRecv_AddTotalRecharge(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	NRoleInfoDefine::SRecharge oRecharge;
	std::string strUdp1;
	std::string strUdp2;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> oRecharge >> strUdp1 >> strUdp2;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 12, Function: 3";
		return false;
	}
	shared_func<SAddTotalRechargeAck> fnAck_(new SAddTotalRechargeAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_AddTotalRecharge(oRecharge, strUdp1, strUdp2, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CGame2CenterCommClt::SAddRechargeMailItemAck::SAddRechargeMailItemAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID) { }

void CGame2CenterCommClt::SAddRechargeMailItemAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -4;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 12, Function: 4";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CGame2CenterCommClt::_DoRecv_AddRechargeMailItem(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	NRoleInfoDefine::SRecharge oRecharge;
	std::string strUdp1;
	std::string strUdp2;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> oRecharge >> strUdp1 >> strUdp2;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 12, Function: 4";
		return false;
	}
	shared_func<SAddRechargeMailItemAck> fnAck_(new SAddRechargeMailItemAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_AddRechargeMailItem(oRecharge, strUdp1, strUdp2, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CGame2CenterCommClt::SAddTotalPrepaidAck::SAddTotalPrepaidAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID) { }

void CGame2CenterCommClt::SAddTotalPrepaidAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -5;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 12, Function: 5";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CGame2CenterCommClt::_DoRecv_AddTotalPrepaid(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT64 qwUsrID = 0;
	UINT32 dwGold = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> qwUsrID >> dwGold;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 12, Function: 5";
		return false;
	}
	shared_func<SAddTotalPrepaidAck> fnAck_(new SAddTotalPrepaidAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_AddTotalPrepaid(qwUsrID, dwGold, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CGame2CenterCommClt::SAddQQCoinBuyItemAck::SAddQQCoinBuyItemAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID) { }

void CGame2CenterCommClt::SAddQQCoinBuyItemAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -6;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 12, Function: 6";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CGame2CenterCommClt::_DoRecv_AddQQCoinBuyItem(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT64 qwUsrID = 0;
	TVecUserItem vecUserItem;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> qwUsrID >> vecUserItem;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 12, Function: 6";
		return false;
	}
	shared_func<SAddQQCoinBuyItemAck> fnAck_(new SAddQQCoinBuyItemAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_AddQQCoinBuyItem(qwUsrID, vecUserItem, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CGame2CenterCommClt::SCheckMailAttchAck::SCheckMailAttchAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID), 
			byCan(0) { }

void CGame2CenterCommClt::SCheckMailAttchAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -7;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << byCan;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 12, Function: 7";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CGame2CenterCommClt::_DoRecv_CheckMailAttch(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT64 qwUsrID = 0;
	UINT64 qwMailID = 0;
	NMailProt::TVecMailAttachment vecItemInfo;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> qwUsrID >> qwMailID >> vecItemInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 12, Function: 7";
		return false;
	}
	shared_func<SCheckMailAttchAck> fnAck_(new SCheckMailAttchAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_CheckMailAttch(qwUsrID, qwMailID, vecItemInfo, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

bool CGame2CenterCommClt::_DoRecv_SendMailAttch(const char* pBuf_, UINT32 dwLen_)
{
	UINT64 qwUsrID = 0;
	UINT64 qwMailID = 0;
	NMailProt::TVecMailAttachment vecItemInfo;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> qwUsrID >> qwMailID >> vecItemInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 12, Function: 8";
		return false;
	}
	OnRecv_SendMailAttch(qwUsrID, qwMailID, vecItemInfo);
	return true;
}

bool CGame2CenterCommClt::_DoRecv_SetSign(const char* pBuf_, UINT32 dwLen_)
{
	UINT64 qwUsrID = 0;
	std::string strSign;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> qwUsrID >> strSign;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 12, Function: 9";
		return false;
	}
	OnRecv_SetSign(qwUsrID, strSign);
	return true;
}

bool CGame2CenterCommClt::_DoRecv_SetMood(const char* pBuf_, UINT32 dwLen_)
{
	UINT64 qwUsrID = 0;
	UINT16 wMood = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> qwUsrID >> wMood;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 12, Function: 10";
		return false;
	}
	OnRecv_SetMood(qwUsrID, wMood);
	return true;
}

CGame2CenterCommClt::SFigtherToOtherAck::SFigtherToOtherAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID), 
			byRet(0), bySuc(0), qwBattleID(0), dwSelfFighterPower(0), bySelfQuality(0), 
			dwOtherFighterPower(0), byOtherQuality(0), dwTurns(0) { }

void CGame2CenterCommClt::SFigtherToOtherAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -8;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << byRet << bySuc << qwBattleID << dwSelfFighterPower << bySelfQuality << dwOtherFighterPower << byOtherQuality << dwTurns;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 12, Function: 11";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CGame2CenterCommClt::_DoRecv_FigtherToOther(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT64 qwUsrID = 0;
	UINT64 qwOtherID = 0;
	UINT32 dwCost = 0;
	NBattleGS::EBattleType eBattleType = (NBattleGS::EBattleType)0;
	UINT32 dwBufferID = 0;
	UINT32 dwSkillAttrID = 0;
	UINT32 dwCount = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> qwUsrID >> qwOtherID >> dwCost >> (UINT8&)eBattleType >> dwBufferID >> dwSkillAttrID >> dwCount;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 12, Function: 11";
		return false;
	}
	shared_func<SFigtherToOtherAck> fnAck_(new SFigtherToOtherAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_FigtherToOther(qwUsrID, qwOtherID, dwCost, eBattleType, dwBufferID, dwSkillAttrID, dwCount, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CGame2CenterCommClt::SCanPushLootAck::SCanPushLootAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID), 
			byRet(0) { }

void CGame2CenterCommClt::SCanPushLootAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -9;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << byRet;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 12, Function: 12";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CGame2CenterCommClt::_DoRecv_CanPushLoot(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT64 qwUsrID = 0;
	UINT32 dwLootId = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> qwUsrID >> dwLootId;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 12, Function: 12";
		return false;
	}
	shared_func<SCanPushLootAck> fnAck_(new SCanPushLootAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_CanPushLoot(qwUsrID, dwLootId, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

bool CGame2CenterCommClt::_DoRecv_PushLoot(const char* pBuf_, UINT32 dwLen_)
{
	UINT64 qwUsrID = 0;
	EOpSource eSource = (EOpSource)0;
	NLogDataDefine::ItemFrom eItemFrom = (NLogDataDefine::ItemFrom)0;
	UINT32 dwLootId = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> qwUsrID >> (UINT8&)eSource >> (UINT16&)eItemFrom >> dwLootId;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 12, Function: 13";
		return false;
	}
	OnRecv_PushLoot(qwUsrID, eSource, eItemFrom, dwLootId);
	return true;
}

CGame2CenterCommClt::SReduceItemAck::SReduceItemAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID), 
			byRet(0) { }

void CGame2CenterCommClt::SReduceItemAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -10;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << byRet;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 12, Function: 14";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CGame2CenterCommClt::_DoRecv_ReduceItem(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT64 qwUsrID = 0;
	NLogDataDefine::ItemTo eItemTo = (NLogDataDefine::ItemTo)0;
	UINT32 dwID = 0;
	UINT32 dwCount = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> qwUsrID >> (UINT16&)eItemTo >> dwID >> dwCount;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 12, Function: 14";
		return false;
	}
	shared_func<SReduceItemAck> fnAck_(new SReduceItemAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_ReduceItem(qwUsrID, eItemTo, dwID, dwCount, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CGame2CenterCommClt::SCanReduceItemAck::SCanReduceItemAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID), 
			byRet(0) { }

void CGame2CenterCommClt::SCanReduceItemAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -11;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << byRet;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 12, Function: 15";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CGame2CenterCommClt::_DoRecv_CanReduceItem(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT64 qwUsrID = 0;
	UINT32 dwItemID = 0;
	UINT32 dwCount = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> qwUsrID >> dwItemID >> dwCount;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 12, Function: 15";
		return false;
	}
	shared_func<SCanReduceItemAck> fnAck_(new SCanReduceItemAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_CanReduceItem(qwUsrID, dwItemID, dwCount, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CGame2CenterCommClt::SGetUserUINTPropAck::SGetUserUINTPropAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID), 
			dwValue(0), byError(0) { }

void CGame2CenterCommClt::SGetUserUINTPropAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -12;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << dwValue << byError;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 12, Function: 16";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CGame2CenterCommClt::_DoRecv_GetUserUINTProp(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT64 qwUsrID = 0;
	EPlayerUINTProp eUINTPropType = (EPlayerUINTProp)0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> qwUsrID >> (UINT8&)eUINTPropType;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 12, Function: 16";
		return false;
	}
	shared_func<SGetUserUINTPropAck> fnAck_(new SGetUserUINTPropAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetUserUINTProp(qwUsrID, eUINTPropType, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CGame2CenterCommClt::SSetUserUINTPropAck::SSetUserUINTPropAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID), 
			byError(0) { }

void CGame2CenterCommClt::SSetUserUINTPropAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -13;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << byError;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 12, Function: 17";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CGame2CenterCommClt::_DoRecv_SetUserUINTProp(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT64 qwUsrID = 0;
	EPlayerUINTProp eUINTPropType = (EPlayerUINTProp)0;
	UINT32 dwValue = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> qwUsrID >> (UINT8&)eUINTPropType >> dwValue;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 12, Function: 17";
		return false;
	}
	shared_func<SSetUserUINTPropAck> fnAck_(new SSetUserUINTPropAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_SetUserUINTProp(qwUsrID, eUINTPropType, dwValue, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CGame2CenterCommClt::SUserSubItemAck::SUserSubItemAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID), 
			byError(0) { }

void CGame2CenterCommClt::SUserSubItemAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -14;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << byError;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 12, Function: 18";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CGame2CenterCommClt::_DoRecv_UserSubItem(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT64 qwUsrID = 0;
	NLogDataDefine::ItemTo eItemTo = (NLogDataDefine::ItemTo)0;
	TVecUserItem vecUserItem;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> qwUsrID >> (UINT16&)eItemTo >> vecUserItem;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 12, Function: 18";
		return false;
	}
	shared_func<SUserSubItemAck> fnAck_(new SUserSubItemAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_UserSubItem(qwUsrID, eItemTo, vecUserItem, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CGame2CenterCommClt::SUserAddItemAck::SUserAddItemAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID), 
			byError(0) { }

void CGame2CenterCommClt::SUserAddItemAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -15;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << byError;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 12, Function: 19";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CGame2CenterCommClt::_DoRecv_UserAddItem(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT64 qwUsrID = 0;
	NLogDataDefine::ItemFrom eItemFrom = (NLogDataDefine::ItemFrom)0;
	TVecUserItem vecUserItem;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> qwUsrID >> (UINT16&)eItemFrom >> vecUserItem;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 12, Function: 19";
		return false;
	}
	shared_func<SUserAddItemAck> fnAck_(new SUserAddItemAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_UserAddItem(qwUsrID, eItemFrom, vecUserItem, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

bool CGame2CenterCommClt::_DoRecv_SendSysMsg(const char* pBuf_, UINT32 dwLen_)
{
	UINT64 qwUsrID = 0;
	UINT16 wMsgID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> qwUsrID >> wMsgID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 12, Function: 20";
		return false;
	}
	OnRecv_SendSysMsg(qwUsrID, wMsgID);
	return true;
}

bool CGame2CenterCommClt::_DoRecv_ActionNotify(const char* pBuf_, UINT32 dwLen_)
{
	UINT64 qwUsrID = 0;
	UINT16 wAction = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> qwUsrID >> wAction;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 12, Function: 21";
		return false;
	}
	OnRecv_ActionNotify(qwUsrID, wAction);
	return true;
}

bool CGame2CenterCommClt::_DoRecv_BubbleNotify(const char* pBuf_, UINT32 dwLen_)
{
	UINT64 qwUsrID = 0;
	NProtoCommon::EDataChange eType = (NProtoCommon::EDataChange)0;
	UINT16 wMsgID = 0;
	TVecINT64 vecParam;
	TVecString vecString;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> qwUsrID >> (UINT8&)eType >> wMsgID >> vecParam >> vecString;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 12, Function: 22";
		return false;
	}
	OnRecv_BubbleNotify(qwUsrID, eType, wMsgID, vecParam, vecString);
	return true;
}

bool CGame2CenterCommClt::_DoRecv_GuildLevelUpdated(const char* pBuf_, UINT32 dwLen_)
{
	UINT64 qwRoleID = 0;
	UINT16 wLevel = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> qwRoleID >> wLevel;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 12, Function: 23";
		return false;
	}
	OnRecv_GuildLevelUpdated(qwRoleID, wLevel);
	return true;
}

bool CGame2CenterCommClt::_DoRecv_GuildNameUpdated(const char* pBuf_, UINT32 dwLen_)
{
	UINT64 qwRoleID = 0;
	std::string strGuildName;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> qwRoleID >> strGuildName;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 12, Function: 24";
		return false;
	}
	OnRecv_GuildNameUpdated(qwRoleID, strGuildName);
	return true;
}

bool CGame2CenterCommClt::_DoRecv_GuildTechUpdate(const char* pBuf_, UINT32 dwLen_)
{
	UINT64 qwRoleID = 0;
	NProtoCommon::TVecFtAttrMod vecFtAttr;
	NGuildProt::TVecGuildTechInfo vecGuildTech;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> qwRoleID >> vecFtAttr >> vecGuildTech;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 12, Function: 25";
		return false;
	}
	OnRecv_GuildTechUpdate(qwRoleID, vecFtAttr, vecGuildTech);
	return true;
}

bool CGame2CenterCommClt::_DoRecv_ReloadTable(const char* pBuf_, UINT32 dwLen_)
{
	TVecString vecTableName;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> vecTableName;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 12, Function: 26";
		return false;
	}
	OnRecv_ReloadTable(vecTableName);
	return true;
}

bool CGame2CenterCommClt::_DoRecv_TripodAttrUpdate(const char* pBuf_, UINT32 dwLen_)
{
	UINT64 qwRoleID = 0;
	TVecUINT32 vecValue;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> qwRoleID >> vecValue;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 12, Function: 27";
		return false;
	}
	OnRecv_TripodAttrUpdate(qwRoleID, vecValue);
	return true;
}

CGame2CenterCommClt::SProcessCondAck::SProcessCondAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID), 
			byError(0) { }

void CGame2CenterCommClt::SProcessCondAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -16;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << byError;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 12, Function: 28";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CGame2CenterCommClt::_DoRecv_ProcessCond(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT64 qwUsrID = 0;
	UINT16 wCondID = 0;
	NLogDataDefine::ItemTo eItemTo = (NLogDataDefine::ItemTo)0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> qwUsrID >> wCondID >> (UINT16&)eItemTo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 12, Function: 28";
		return false;
	}
	shared_func<SProcessCondAck> fnAck_(new SProcessCondAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_ProcessCond(qwUsrID, wCondID, eItemTo, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CGame2CenterCommClt::SUpgradeTripodAck::SUpgradeTripodAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID), 
			byError(0), byLevel(0), dwExp(0) { }

void CGame2CenterCommClt::SUpgradeTripodAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -17;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << byError << byLevel << dwExp;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 12, Function: 29";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CGame2CenterCommClt::_DoRecv_UpgradeTripod(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT64 qwUsrID = 0;
	UINT8 byTripodID = 0;
	UINT8 byLevel = 0;
	UINT32 dwExp = 0;
	UINT8 byOneKey = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> qwUsrID >> byTripodID >> byLevel >> dwExp >> byOneKey;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 12, Function: 29";
		return false;
	}
	shared_func<SUpgradeTripodAck> fnAck_(new SUpgradeTripodAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_UpgradeTripod(qwUsrID, byTripodID, byLevel, dwExp, byOneKey, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CGame2CenterCommClt::SSpeedTripodAck::SSpeedTripodAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID), 
			byError(0), dwSoul(0) { }

void CGame2CenterCommClt::SSpeedTripodAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -18;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << byError << dwSoul;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 12, Function: 30";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CGame2CenterCommClt::_DoRecv_SpeedTripod(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT64 qwUsrID = 0;
	UINT32 dwCurSoul = 0;
	UINT32 dwMaxSoul = 0;
	NItemProt::TVecItemCount vecItems;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> qwUsrID >> dwCurSoul >> dwMaxSoul >> vecItems;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 12, Function: 30";
		return false;
	}
	shared_func<SSpeedTripodAck> fnAck_(new SSpeedTripodAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_SpeedTripod(qwUsrID, dwCurSoul, dwMaxSoul, vecItems, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CGame2CenterCommClt::SCheckHasFighterAck::SCheckHasFighterAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID), 
			byError(0), byColor(0) { }

void CGame2CenterCommClt::SCheckHasFighterAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -19;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << byError << byColor;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 12, Function: 31";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CGame2CenterCommClt::_DoRecv_CheckHasFighter(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT64 qwUsrID = 0;
	UINT16 wFighterID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> qwUsrID >> wFighterID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 12, Function: 31";
		return false;
	}
	shared_func<SCheckHasFighterAck> fnAck_(new SCheckHasFighterAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_CheckHasFighter(qwUsrID, wFighterID, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CGame2CenterCommClt::SGetBattlePointAck::SGetBattlePointAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID), 
			byError(0), dwBattlePoint(0) { }

void CGame2CenterCommClt::SGetBattlePointAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -20;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << byError << dwBattlePoint;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 12, Function: 32";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CGame2CenterCommClt::_DoRecv_GetBattlePoint(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 12, Function: 32";
		return false;
	}
	shared_func<SGetBattlePointAck> fnAck_(new SGetBattlePointAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetBattlePoint(qwUsrID, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

bool CGame2CenterCommClt::_DoRecv_OnPlayerEvent(const char* pBuf_, UINT32 dwLen_)
{
	UINT64 qwUsrID = 0;
	NEventCenter::EventType eEventType = (NEventCenter::EventType)0;
	TVecINT32 vecParam;
	std::string strParam;
	bool bLog = false;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> qwUsrID >> (UINT16&)eEventType >> vecParam >> strParam >> bLog;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 12, Function: 33";
		return false;
	}
	OnRecv_OnPlayerEvent(qwUsrID, eEventType, vecParam, strParam, bLog);
	return true;
}

bool CGame2CenterCommClt::_DoRecv_AddORSetGameVar(const char* pBuf_, UINT32 dwLen_)
{
	UINT64 qwUsrID = 0;
	UINT8 byType = 0;
	TVecUINT16 vecVars;
	TVecUINT64 vecValues;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> qwUsrID >> byType >> vecVars >> vecValues;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 12, Function: 34";
		return false;
	}
	OnRecv_AddORSetGameVar(qwUsrID, byType, vecVars, vecValues);
	return true;
}

bool CGame2CenterCommClt::_DoRecv_DeleteGameVar(const char* pBuf_, UINT32 dwLen_)
{
	UINT64 qwUsrID = 0;
	TVecUINT16 vecVars;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> qwUsrID >> vecVars;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 12, Function: 35";
		return false;
	}
	OnRecv_DeleteGameVar(qwUsrID, vecVars);
	return true;
}

bool CGame2CenterCommClt::_DoRecv_AddMallDiscount(const char* pBuf_, UINT32 dwLen_)
{
	NMallProt::SDiscount oDiscount;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> oDiscount;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 12, Function: 36";
		return false;
	}
	OnRecv_AddMallDiscount(oDiscount);
	return true;
}

bool CGame2CenterCommClt::_DoRecv_ClearMallDiscount(const char* pBuf_, UINT32 dwLen_)
{
	UINT8 byPos = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> byPos;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 12, Function: 37";
		return false;
	}
	OnRecv_ClearMallDiscount(byPos);
	return true;
}

CGame2CenterCommClt::SSubPlayerMoneyAck::SSubPlayerMoneyAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID) { }

void CGame2CenterCommClt::SSubPlayerMoneyAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -21;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 12, Function: 38";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CGame2CenterCommClt::_DoRecv_SubPlayerMoney(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	TVecUINT64 vecUserID;
	TVecUserItem vecUserItem;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> vecUserID >> vecUserItem;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 12, Function: 38";
		return false;
	}
	shared_func<SSubPlayerMoneyAck> fnAck_(new SSubPlayerMoneyAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_SubPlayerMoney(vecUserID, vecUserItem, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CGame2CenterCommClt::SSetPlayerLevelAck::SSetPlayerLevelAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID) { }

void CGame2CenterCommClt::SSetPlayerLevelAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -22;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 12, Function: 39";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CGame2CenterCommClt::_DoRecv_SetPlayerLevel(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT64 qwUsrID = 0;
	UINT16 wLevel = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> qwUsrID >> wLevel;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 12, Function: 39";
		return false;
	}
	shared_func<SSetPlayerLevelAck> fnAck_(new SSetPlayerLevelAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_SetPlayerLevel(qwUsrID, wLevel, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CGame2CenterCommClt::SSetPlayerVIPLevelAck::SSetPlayerVIPLevelAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID) { }

void CGame2CenterCommClt::SSetPlayerVIPLevelAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -23;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 12, Function: 40";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CGame2CenterCommClt::_DoRecv_SetPlayerVIPLevel(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT64 qwUsrID = 0;
	NPHPProt::EOptType eOptType = (NPHPProt::EOptType)0;
	UINT32 dwLevelOrGrowthValue = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> qwUsrID >> (INT8&)eOptType >> dwLevelOrGrowthValue;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 12, Function: 40";
		return false;
	}
	shared_func<SSetPlayerVIPLevelAck> fnAck_(new SSetPlayerVIPLevelAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_SetPlayerVIPLevel(qwUsrID, eOptType, dwLevelOrGrowthValue, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CGame2CenterCommClt::SSetDayTaskAck::SSetDayTaskAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID) { }

void CGame2CenterCommClt::SSetDayTaskAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -24;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 12, Function: 41";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CGame2CenterCommClt::_DoRecv_SetDayTask(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	TVecUINT64 vecUserID;
	NPHPProt::EPHPTaskType eTaskType = (NPHPProt::EPHPTaskType)0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> vecUserID >> (UINT8&)eTaskType;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 12, Function: 41";
		return false;
	}
	shared_func<SSetDayTaskAck> fnAck_(new SSetDayTaskAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_SetDayTask(vecUserID, eTaskType, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CGame2CenterCommClt::SGetPlayerInfoAck::SGetPlayerInfoAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID) { }

void CGame2CenterCommClt::SGetPlayerInfoAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -25;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << sPlayerInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 12, Function: 42";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CGame2CenterCommClt::_DoRecv_GetPlayerInfo(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 12, Function: 42";
		return false;
	}
	shared_func<SGetPlayerInfoAck> fnAck_(new SGetPlayerInfoAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetPlayerInfo(qwUserID, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CGame2CenterCommClt::SGetPlayerBagInfoAck::SGetPlayerBagInfoAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID) { }

void CGame2CenterCommClt::SGetPlayerBagInfoAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -26;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << vecPlayerBagInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 12, Function: 43";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CGame2CenterCommClt::_DoRecv_GetPlayerBagInfo(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 12, Function: 43";
		return false;
	}
	shared_func<SGetPlayerBagInfoAck> fnAck_(new SGetPlayerBagInfoAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetPlayerBagInfo(qwUserID, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CGame2CenterCommClt::SDelPlayerItemAck::SDelPlayerItemAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID) { }

void CGame2CenterCommClt::SDelPlayerItemAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -27;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 12, Function: 44";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CGame2CenterCommClt::_DoRecv_DelPlayerItem(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT64 qwUserID = 0;
	UINT8 byType = 0;
	UINT64 qwInstID = 0;
	UINT16 wCount = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> qwUserID >> byType >> qwInstID >> wCount;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 12, Function: 44";
		return false;
	}
	shared_func<SDelPlayerItemAck> fnAck_(new SDelPlayerItemAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_DelPlayerItem(qwUserID, byType, qwInstID, wCount, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

bool CGame2CenterCommClt::_DoRecv_SendSysMailByLootId(const char* pBuf_, UINT32 dwLen_)
{
	UINT64 qwUserID = 0;
	UINT16 wTitle = 0;
	UINT16 wText = 0;
	TVecString vecParam;
	UINT32 dwLootId = 0;
	UINT32 dwRate = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> qwUserID >> wTitle >> wText >> vecParam >> dwLootId >> dwRate;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 12, Function: 45";
		return false;
	}
	OnRecv_SendSysMailByLootId(qwUserID, wTitle, wText, vecParam, dwLootId, dwRate);
	return true;
}

CGame2CenterCommClt::SGetTaskStateForPlatfromAck::SGetTaskStateForPlatfromAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID), 
			eRet((NPHPProt::ETaskState)0) { }

void CGame2CenterCommClt::SGetTaskStateForPlatfromAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -28;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eRet;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 12, Function: 46";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CGame2CenterCommClt::_DoRecv_GetTaskStateForPlatfrom(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT64 qwUserID = 0;
	UINT32 dwTaskID = 0;
	UINT8 byStep = 0;
	UINT8 byOpt = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> qwUserID >> dwTaskID >> byStep >> byOpt;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 12, Function: 46";
		return false;
	}
	shared_func<SGetTaskStateForPlatfromAck> fnAck_(new SGetTaskStateForPlatfromAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetTaskStateForPlatfrom(qwUserID, dwTaskID, byStep, byOpt, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

bool CGame2CenterCommClt::_DoRecv_SynWeiweiPersonNum(const char* pBuf_, UINT32 dwLen_)
{
	UINT64 qwUserID = 0;
	UINT8 byType = 0;
	UINT32 dwCount = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> qwUserID >> byType >> dwCount;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 12, Function: 47";
		return false;
	}
	OnRecv_SynWeiweiPersonNum(qwUserID, byType, dwCount);
	return true;
}

bool CGame2CenterCommClt::_DoRecv_CheckCDK(const char* pBuf_, UINT32 dwLen_)
{
	UINT64 qwUserID = 0;
	std::string strCDK;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> qwUserID >> strCDK;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 12, Function: 48";
		return false;
	}
	OnRecv_CheckCDK(qwUserID, strCDK);
	return true;
}

bool CGame2CenterCommClt::_DoRecv_SynQQAlarm(const char* pBuf_, UINT32 dwLen_)
{
	UINT64 qwUserID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> qwUserID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 12, Function: 49";
		return false;
	}
	OnRecv_SynQQAlarm(qwUserID);
	return true;
}

bool CGame2CenterCommClt::_DoRecv_ModifyChest(const char* pBuf_, UINT32 dwLen_)
{
	NPHPProt::SChestInfo sChestInfo;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> sChestInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 12, Function: 50";
		return false;
	}
	OnRecv_ModifyChest(sChestInfo);
	return true;
}

bool CGame2CenterCommClt::_DoRecv_SyncActivityTime(const char* pBuf_, UINT32 dwLen_)
{
	NProtoCommon::SActivityTime sActTime;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> sActTime;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 12, Function: 51";
		return false;
	}
	OnRecv_SyncActivityTime(sActTime);
	return true;
}

CGame2CenterCommClt::SGetLoginDaysAck::SGetLoginDaysAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID), 
			dwDays(0) { }

void CGame2CenterCommClt::SGetLoginDaysAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -29;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << dwDays;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 12, Function: 52";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CGame2CenterCommClt::_DoRecv_GetLoginDays(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 12, Function: 52";
		return false;
	}
	shared_func<SGetLoginDaysAck> fnAck_(new SGetLoginDaysAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetLoginDays(qwUserID, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

bool CGame2CenterCommClt::_DoRecv_SyncActState(const char* pBuf_, UINT32 dwLen_)
{
	SActivityState oInfo;
	bool bNotify = false;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> oInfo >> bNotify;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 12, Function: 53";
		return false;
	}
	OnRecv_SyncActState(oInfo, bNotify);
	return true;
}

bool CGame2CenterCommClt::_DoRecv_SyncTitle(const char* pBuf_, UINT32 dwLen_)
{
	UINT64 qwUserID = 0;
	UINT16 wTitleID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> qwUserID >> wTitleID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 12, Function: 54";
		return false;
	}
	OnRecv_SyncTitle(qwUserID, wTitleID);
	return true;
}

CGame2CenterCommClt::SSubGoldOrCouponAck::SSubGoldOrCouponAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID), 
			byError(0) { }

void CGame2CenterCommClt::SSubGoldOrCouponAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -30;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << byError;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 12, Function: 55";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CGame2CenterCommClt::_DoRecv_SubGoldOrCoupon(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT64 qwUsrID = 0;
	NLogDataDefine::ItemTo eItemTo = (NLogDataDefine::ItemTo)0;
	UINT32 dwCount = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> qwUsrID >> (UINT16&)eItemTo >> dwCount;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 12, Function: 55";
		return false;
	}
	shared_func<SSubGoldOrCouponAck> fnAck_(new SSubGoldOrCouponAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_SubGoldOrCoupon(qwUsrID, eItemTo, dwCount, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

bool CGame2CenterCommClt::_DoReturn_GetCenterState(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoReturn exception: " << szExcept << ", Protocol: 12, Function: 3";
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

void CGame2CenterCommClt::_OnTimeOut_GetCenterState(UINT32 dwSessionID)
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

bool CGame2CenterCommClt::_DoReturn_IsFriend(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	bool bRet_ = false;
	UINT8 byRet = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> bRet_ >> byRet;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoReturn exception: " << szExcept << ", Protocol: 12, Function: 10";
		return false;
	}
	UINT8 byRet_ = 0;
	if(!bRet_)
		byRet_ = 1;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT8 byRet //(返回值)0是好友 1非好友
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID_));
	if(pSessData_ == NULL)
		return false;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(byRet_, byRet);
	if(_pSessionMgr != NULL)
		_pSessionMgr->DelSession(dwSessionID_);
	return true;
}

void CGame2CenterCommClt::_OnTimeOut_IsFriend(UINT32 dwSessionID)
{
	UINT8 byRet = 0;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT8 byRet //(返回值)0是好友 1非好友
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID));
	if(pSessData_ == NULL)
		return;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(2, byRet);
}

bool CGame2CenterCommClt::_DoReturn_IsSameGuild(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	bool bRet_ = false;
	UINT8 byRet = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> bRet_ >> byRet;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoReturn exception: " << szExcept << ", Protocol: 12, Function: 11";
		return false;
	}
	UINT8 byRet_ = 0;
	if(!bRet_)
		byRet_ = 1;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT8 byRet //(返回值)0在同一个帮派 1不在同一个帮派
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID_));
	if(pSessData_ == NULL)
		return false;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(byRet_, byRet);
	if(_pSessionMgr != NULL)
		_pSessionMgr->DelSession(dwSessionID_);
	return true;
}

void CGame2CenterCommClt::_OnTimeOut_IsSameGuild(UINT32 dwSessionID)
{
	UINT8 byRet = 0;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT8 byRet //(返回值)0在同一个帮派 1不在同一个帮派
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID));
	if(pSessData_ == NULL)
		return;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(2, byRet);
}

bool CGame2CenterCommClt::_DoReturn_GetGuildID(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	bool bRet_ = false;
	UINT64 qwGuildID = 0;
	std::string strGuildName;
	UINT8 byGuildLvl = 0;
	std::string strGuildOwnerName;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> bRet_ >> qwGuildID >> strGuildName >> byGuildLvl >> strGuildOwnerName;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoReturn exception: " << szExcept << ", Protocol: 12, Function: 13";
		return false;
	}
	UINT8 byRet_ = 0;
	if(!bRet_)
		byRet_ = 1;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT64 qwGuildID, //(返回值)帮派ID
		const std::string& strGuildName, //(返回值)帮派名称
		UINT8 byGuildLvl, //(返回值)帮派等级
		const std::string& strGuildOwnerName //(返回值)帮主名称
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID_));
	if(pSessData_ == NULL)
		return false;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(byRet_, qwGuildID, strGuildName, byGuildLvl, strGuildOwnerName);
	if(_pSessionMgr != NULL)
		_pSessionMgr->DelSession(dwSessionID_);
	return true;
}

void CGame2CenterCommClt::_OnTimeOut_GetGuildID(UINT32 dwSessionID)
{
	UINT64 qwGuildID = 0;
	std::string strGuildName;
	UINT8 byGuildLvl = 0;
	std::string strGuildOwnerName;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT64 qwGuildID, //(返回值)帮派ID
		const std::string& strGuildName, //(返回值)帮派名称
		UINT8 byGuildLvl, //(返回值)帮派等级
		const std::string& strGuildOwnerName //(返回值)帮主名称
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID));
	if(pSessData_ == NULL)
		return;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(2, qwGuildID, strGuildName, byGuildLvl, strGuildOwnerName);
}

bool CGame2CenterCommClt::_DoReturn_GetGuildName(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	bool bRet_ = false;
	bool bValid = false;
	UINT64 qwGuildID = 0;
	std::string strGuildName;
	UINT8 byGuildLvl = 0;
	std::string strGuildOwnerName;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> bRet_ >> bValid >> qwGuildID >> strGuildName >> byGuildLvl >> strGuildOwnerName;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoReturn exception: " << szExcept << ", Protocol: 12, Function: 14";
		return false;
	}
	UINT8 byRet_ = 0;
	if(!bRet_)
		byRet_ = 1;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		bool bValid, //(返回值)是否已经找到
		UINT64 qwGuildID, //(返回值)帮派ID
		const std::string& strGuildName, //(返回值)帮派名称
		UINT8 byGuildLvl, //(返回值)帮派等级
		const std::string& strGuildOwnerName //(返回值)帮主名称
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID_));
	if(pSessData_ == NULL)
		return false;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(byRet_, bValid, qwGuildID, strGuildName, byGuildLvl, strGuildOwnerName);
	if(_pSessionMgr != NULL)
		_pSessionMgr->DelSession(dwSessionID_);
	return true;
}

void CGame2CenterCommClt::_OnTimeOut_GetGuildName(UINT32 dwSessionID)
{
	bool bValid = false;
	UINT64 qwGuildID = 0;
	std::string strGuildName;
	UINT8 byGuildLvl = 0;
	std::string strGuildOwnerName;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		bool bValid, //(返回值)是否已经找到
		UINT64 qwGuildID, //(返回值)帮派ID
		const std::string& strGuildName, //(返回值)帮派名称
		UINT8 byGuildLvl, //(返回值)帮派等级
		const std::string& strGuildOwnerName //(返回值)帮主名称
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID));
	if(pSessData_ == NULL)
		return;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(2, bValid, qwGuildID, strGuildName, byGuildLvl, strGuildOwnerName);
}

bool CGame2CenterCommClt::_DoReturn_SubGuildContribution(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	bool bRet_ = false;
	NGuildProt::EGuildResult eResult = (NGuildProt::EGuildResult)0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> bRet_ >> (UINT8&)eResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoReturn exception: " << szExcept << ", Protocol: 12, Function: 22";
		return false;
	}
	UINT8 byRet_ = 0;
	if(!bRet_)
		byRet_ = 1;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		NGuildProt::EGuildResult eResult //(返回值)检测结果
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID_));
	if(pSessData_ == NULL)
		return false;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(byRet_, eResult);
	if(_pSessionMgr != NULL)
		_pSessionMgr->DelSession(dwSessionID_);
	return true;
}

void CGame2CenterCommClt::_OnTimeOut_SubGuildContribution(UINT32 dwSessionID)
{
	NGuildProt::EGuildResult eResult = (NGuildProt::EGuildResult)0;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		NGuildProt::EGuildResult eResult //(返回值)检测结果
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID));
	if(pSessData_ == NULL)
		return;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(2, eResult);
}

bool CGame2CenterCommClt::_DoReturn_GetSystemVar(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	bool bRet_ = false;
	TVecUINT16 vecVars;
	TVecUINT64 vecValues;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> bRet_ >> vecVars >> vecValues;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoReturn exception: " << szExcept << ", Protocol: 12, Function: 28";
		return false;
	}
	UINT8 byRet_ = 0;
	if(!bRet_)
		byRet_ = 1;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		const TVecUINT16& vecVars, //(返回值)varID列表
		const TVecUINT64& vecValues //(返回值)var数值列表(必须与vecVars对应)
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID_));
	if(pSessData_ == NULL)
		return false;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(byRet_, vecVars, vecValues);
	if(_pSessionMgr != NULL)
		_pSessionMgr->DelSession(dwSessionID_);
	return true;
}

void CGame2CenterCommClt::_OnTimeOut_GetSystemVar(UINT32 dwSessionID)
{
	TVecUINT16 vecVars;
	TVecUINT64 vecValues;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		const TVecUINT16& vecVars, //(返回值)varID列表
		const TVecUINT64& vecValues //(返回值)var数值列表(必须与vecVars对应)
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID));
	if(pSessData_ == NULL)
		return;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(2, vecVars, vecValues);
}

bool CGame2CenterCommClt::_DoReturn_SetSystemVar(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	bool bRet_ = false;
	TVecUINT16 vecVarID;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> bRet_ >> vecVarID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoReturn exception: " << szExcept << ", Protocol: 12, Function: 29";
		return false;
	}
	UINT8 byRet_ = 0;
	if(!bRet_)
		byRet_ = 1;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		const TVecUINT16& vecVarID //(返回值)设置成功的varID列表(只是校验用)
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID_));
	if(pSessData_ == NULL)
		return false;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(byRet_, vecVarID);
	if(_pSessionMgr != NULL)
		_pSessionMgr->DelSession(dwSessionID_);
	return true;
}

void CGame2CenterCommClt::_OnTimeOut_SetSystemVar(UINT32 dwSessionID)
{
	TVecUINT16 vecVarID;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		const TVecUINT16& vecVarID //(返回值)设置成功的varID列表(只是校验用)
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID));
	if(pSessData_ == NULL)
		return;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(2, vecVarID);
}

} //namespace NGame2CenterComm
