/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    Game2CenterComm.cpp
//  Purpose:      GameServer到CenterServer的通信协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "Game2CenterCommSvr.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NGame2CenterComm
{

CGame2CenterCommSvr::THandleFunc CGame2CenterCommSvr::_ReturnFuncs[] =
{
	&CGame2CenterCommSvr::_DoReturn_ReplaceUser, //FuncID: -1
	&CGame2CenterCommSvr::_DoReturn_GMCmd, //FuncID: -2
	&CGame2CenterCommSvr::_DoReturn_AddTotalRecharge, //FuncID: -3
	&CGame2CenterCommSvr::_DoReturn_AddRechargeMailItem, //FuncID: -4
	&CGame2CenterCommSvr::_DoReturn_AddTotalPrepaid, //FuncID: -5
	&CGame2CenterCommSvr::_DoReturn_AddQQCoinBuyItem, //FuncID: -6
	&CGame2CenterCommSvr::_DoReturn_CheckMailAttch, //FuncID: -7
	&CGame2CenterCommSvr::_DoReturn_FigtherToOther, //FuncID: -8
	&CGame2CenterCommSvr::_DoReturn_CanPushLoot, //FuncID: -9
	&CGame2CenterCommSvr::_DoReturn_ReduceItem, //FuncID: -10
	&CGame2CenterCommSvr::_DoReturn_CanReduceItem, //FuncID: -11
	&CGame2CenterCommSvr::_DoReturn_GetUserUINTProp, //FuncID: -12
	&CGame2CenterCommSvr::_DoReturn_SetUserUINTProp, //FuncID: -13
	&CGame2CenterCommSvr::_DoReturn_UserSubItem, //FuncID: -14
	&CGame2CenterCommSvr::_DoReturn_UserAddItem, //FuncID: -15
	&CGame2CenterCommSvr::_DoReturn_ProcessCond, //FuncID: -16
	&CGame2CenterCommSvr::_DoReturn_UpgradeTripod, //FuncID: -17
	&CGame2CenterCommSvr::_DoReturn_SpeedTripod, //FuncID: -18
	&CGame2CenterCommSvr::_DoReturn_CheckHasFighter, //FuncID: -19
	&CGame2CenterCommSvr::_DoReturn_GetBattlePoint, //FuncID: -20
	&CGame2CenterCommSvr::_DoReturn_SubPlayerMoney, //FuncID: -21
	&CGame2CenterCommSvr::_DoReturn_SetPlayerLevel, //FuncID: -22
	&CGame2CenterCommSvr::_DoReturn_SetPlayerVIPLevel, //FuncID: -23
	&CGame2CenterCommSvr::_DoReturn_SetDayTask, //FuncID: -24
	&CGame2CenterCommSvr::_DoReturn_GetPlayerInfo, //FuncID: -25
	&CGame2CenterCommSvr::_DoReturn_GetPlayerBagInfo, //FuncID: -26
	&CGame2CenterCommSvr::_DoReturn_DelPlayerItem, //FuncID: -27
	&CGame2CenterCommSvr::_DoReturn_GetTaskStateForPlatfrom, //FuncID: -28
	&CGame2CenterCommSvr::_DoReturn_GetLoginDays, //FuncID: -29
	&CGame2CenterCommSvr::_DoReturn_SubGoldOrCoupon, //FuncID: -30
};

CGame2CenterCommSvr::THandleFunc CGame2CenterCommSvr::_HandleFuncs[] =
{
	&CGame2CenterCommSvr::_DoRecv_KeepAlive, //FuncID: 1
	&CGame2CenterCommSvr::_DoRecv_GameSvrInitNft, //FuncID: 2
	&CGame2CenterCommSvr::_DoRecv_GetCenterState, //FuncID: 3
	&CGame2CenterCommSvr::_DoRecv_GameSvrDataSyncReq, //FuncID: 4
	&CGame2CenterCommSvr::_DoRecv_UserLoginNtf, //FuncID: 5
	&CGame2CenterCommSvr::_DoRecv_UserLogoutNtf, //FuncID: 6
	&CGame2CenterCommSvr::_DoRecv_UserReplaceNtf, //FuncID: 7
	&CGame2CenterCommSvr::_DoRecv_UserJumpSvrNtf, //FuncID: 8
	&CGame2CenterCommSvr::_DoRecv_UserSyncPropNtf, //FuncID: 9
	&CGame2CenterCommSvr::_DoRecv_IsFriend, //FuncID: 10
	&CGame2CenterCommSvr::_DoRecv_IsSameGuild, //FuncID: 11
	&CGame2CenterCommSvr::_DoRecv_SendMail, //FuncID: 12
	&CGame2CenterCommSvr::_DoRecv_GetGuildID, //FuncID: 13
	&CGame2CenterCommSvr::_DoRecv_GetGuildName, //FuncID: 14
	&CGame2CenterCommSvr::_DoRecv_NotifyGuildInfo, //FuncID: 15
	&CGame2CenterCommSvr::_DoRecv_SynIconAppear, //FuncID: 16
	&CGame2CenterCommSvr::_DoRecv_AddGuildContribution, //FuncID: 17
	&CGame2CenterCommSvr::_DoRecv_ActiveTripodFire, //FuncID: 18
	&CGame2CenterCommSvr::_DoRecv_UpdatePlatformParam, //FuncID: 19
	&CGame2CenterCommSvr::_DoRecv_UpdateEnterString, //FuncID: 20
	&CGame2CenterCommSvr::_DoRecv_SendWonderType, //FuncID: 21
	&CGame2CenterCommSvr::_DoRecv_SubGuildContribution, //FuncID: 22
	&CGame2CenterCommSvr::_DoRecv_BeautyLotteryLog, //FuncID: 23
	&CGame2CenterCommSvr::_DoRecv_InviteFriend, //FuncID: 24
	&CGame2CenterCommSvr::_DoRecv_NotifyGuildExchangedItemBegin, //FuncID: 25
	&CGame2CenterCommSvr::_DoRecv_SyncGameBuffUseInCenter, //FuncID: 26
	&CGame2CenterCommSvr::_DoRecv_SyncGameActiveParam, //FuncID: 27
	&CGame2CenterCommSvr::_DoRecv_GetSystemVar, //FuncID: 28
	&CGame2CenterCommSvr::_DoRecv_SetSystemVar, //FuncID: 29
};

CGame2CenterCommSvr::TTimeOutFunc CGame2CenterCommSvr::_TimeoutFuncs[] =
{
	&CGame2CenterCommSvr::_OnTimeOut_ReplaceUser, //FuncID: 1
	&CGame2CenterCommSvr::_OnTimeOut_GMCmd, //FuncID: 2
	&CGame2CenterCommSvr::_OnTimeOut_AddTotalRecharge, //FuncID: 3
	&CGame2CenterCommSvr::_OnTimeOut_AddRechargeMailItem, //FuncID: 4
	&CGame2CenterCommSvr::_OnTimeOut_AddTotalPrepaid, //FuncID: 5
	&CGame2CenterCommSvr::_OnTimeOut_AddQQCoinBuyItem, //FuncID: 6
	&CGame2CenterCommSvr::_OnTimeOut_CheckMailAttch, //FuncID: 7
	&CGame2CenterCommSvr::_OnTimeOut_FigtherToOther, //FuncID: 8
	&CGame2CenterCommSvr::_OnTimeOut_CanPushLoot, //FuncID: 9
	&CGame2CenterCommSvr::_OnTimeOut_ReduceItem, //FuncID: 10
	&CGame2CenterCommSvr::_OnTimeOut_CanReduceItem, //FuncID: 11
	&CGame2CenterCommSvr::_OnTimeOut_GetUserUINTProp, //FuncID: 12
	&CGame2CenterCommSvr::_OnTimeOut_SetUserUINTProp, //FuncID: 13
	&CGame2CenterCommSvr::_OnTimeOut_UserSubItem, //FuncID: 14
	&CGame2CenterCommSvr::_OnTimeOut_UserAddItem, //FuncID: 15
	&CGame2CenterCommSvr::_OnTimeOut_ProcessCond, //FuncID: 16
	&CGame2CenterCommSvr::_OnTimeOut_UpgradeTripod, //FuncID: 17
	&CGame2CenterCommSvr::_OnTimeOut_SpeedTripod, //FuncID: 18
	&CGame2CenterCommSvr::_OnTimeOut_CheckHasFighter, //FuncID: 19
	&CGame2CenterCommSvr::_OnTimeOut_GetBattlePoint, //FuncID: 20
	&CGame2CenterCommSvr::_OnTimeOut_SubPlayerMoney, //FuncID: 21
	&CGame2CenterCommSvr::_OnTimeOut_SetPlayerLevel, //FuncID: 22
	&CGame2CenterCommSvr::_OnTimeOut_SetPlayerVIPLevel, //FuncID: 23
	&CGame2CenterCommSvr::_OnTimeOut_SetDayTask, //FuncID: 24
	&CGame2CenterCommSvr::_OnTimeOut_GetPlayerInfo, //FuncID: 25
	&CGame2CenterCommSvr::_OnTimeOut_GetPlayerBagInfo, //FuncID: 26
	&CGame2CenterCommSvr::_OnTimeOut_DelPlayerItem, //FuncID: 27
	&CGame2CenterCommSvr::_OnTimeOut_GetTaskStateForPlatfrom, //FuncID: 28
	&CGame2CenterCommSvr::_OnTimeOut_GetLoginDays, //FuncID: 29
	&CGame2CenterCommSvr::_OnTimeOut_SubGoldOrCoupon, //FuncID: 30
};

bool CGame2CenterCommSvr::HandleMessage(const char* pBuf, UINT32 dwLen)
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

void CGame2CenterCommSvr::OnTimeOut(UINT8 byFuncID, UINT32 dwSessionID)
{
	if(byFuncID == 0 || byFuncID > (UINT8)ARRAYSIZE(_TimeoutFuncs))
		return;
	(this->*_TimeoutFuncs[byFuncID - 1])(dwSessionID);
}

//发送：替换帐号
bool CGame2CenterCommSvr::Send_ReplaceUser(
	UINT64 qwUsrID, //帐号ID
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT64 qwUsrID //(本地保存的函数参数)帐号ID
	)> fnOnReturn_ //返回时的回调函数
)
{
	if(_pSessionMgr == NULL)
	{
		LOG_CRI << "_pSessionMgr == NULL";		return false;
	}
	UINT32 dwSessionID_ = _pSessionMgr->GetNewSession(*this, 1);
	typedef std::tuple<decltype(fnOnReturn_), UINT64> TSessData;
	std::shared_ptr<TSessData> pSessData_(new TSessData(fnOnReturn_, qwUsrID));
	_pSessionMgr->StoreData(dwSessionID_, pSessData_);
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwUsrID;
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

bool CGame2CenterCommSvr::SendSvr_ReplaceUser(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwUsrID, //帐号ID
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT64 qwUsrID //(本地保存的函数参数)帐号ID
	)> fnOnReturn_ //返回时的回调函数
)
{
	if(_pSessionMgr == NULL)
	{
		LOG_CRI << "_pSessionMgr == NULL";		return false;
	}
	UINT32 dwSessionID_ = _pSessionMgr->GetNewSession(*this, 1);
	typedef std::tuple<decltype(fnOnReturn_), UINT64> TSessData;
	std::shared_ptr<TSessData> pSessData_(new TSessData(fnOnReturn_, qwUsrID));
	_pSessionMgr->StoreData(dwSessionID_, pSessData_);
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwUsrID;
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

//发送：GM指令
bool CGame2CenterCommSvr::Send_GMCmd(
	UINT64 qwUsrID, //帐号ID
	const std::string& strInfo, //GM指令信息
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT64 qwUsrID //(本地保存的函数参数)帐号ID
	)> fnOnReturn_ //返回时的回调函数
)
{
	if(_pSessionMgr == NULL)
	{
		LOG_CRI << "_pSessionMgr == NULL";		return false;
	}
	UINT32 dwSessionID_ = _pSessionMgr->GetNewSession(*this, 2);
	typedef std::tuple<decltype(fnOnReturn_), UINT64> TSessData;
	std::shared_ptr<TSessData> pSessData_(new TSessData(fnOnReturn_, qwUsrID));
	_pSessionMgr->StoreData(dwSessionID_, pSessData_);
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwUsrID << strInfo;
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

bool CGame2CenterCommSvr::SendSvr_GMCmd(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwUsrID, //帐号ID
	const std::string& strInfo, //GM指令信息
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT64 qwUsrID //(本地保存的函数参数)帐号ID
	)> fnOnReturn_ //返回时的回调函数
)
{
	if(_pSessionMgr == NULL)
	{
		LOG_CRI << "_pSessionMgr == NULL";		return false;
	}
	UINT32 dwSessionID_ = _pSessionMgr->GetNewSession(*this, 2);
	typedef std::tuple<decltype(fnOnReturn_), UINT64> TSessData;
	std::shared_ptr<TSessData> pSessData_(new TSessData(fnOnReturn_, qwUsrID));
	_pSessionMgr->StoreData(dwSessionID_, pSessData_);
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwUsrID << strInfo;
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

//发送：充值接口
bool CGame2CenterCommSvr::Send_AddTotalRecharge(
	const NRoleInfoDefine::SRecharge& oRecharge, //充值仙石的数据
	const std::string& strUdp1, //udpLog参数1(平台传来的)
	const std::string& strUdp2, //udpLog参数2(平台传来的)
	boost::function<void (UINT8 byRet_ //0为成功，1为失败，2为超时
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
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << oRecharge << strUdp1 << strUdp2;
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

bool CGame2CenterCommSvr::SendSvr_AddTotalRecharge(const UINT32* pSvrID_, UINT8 byCnt_,
	const NRoleInfoDefine::SRecharge& oRecharge, //充值仙石的数据
	const std::string& strUdp1, //udpLog参数1(平台传来的)
	const std::string& strUdp2, //udpLog参数2(平台传来的)
	boost::function<void (UINT8 byRet_ //0为成功，1为失败，2为超时
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
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << oRecharge << strUdp1 << strUdp2;
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

//发送：充值接口(改版:加仙石礼包到邮件)
bool CGame2CenterCommSvr::Send_AddRechargeMailItem(
	const NRoleInfoDefine::SRecharge& oRecharge, //充值仙石的数据
	const std::string& strUdp1, //udpLog参数1(平台传来的)
	const std::string& strUdp2, //udpLog参数2(平台传来的)
	boost::function<void (UINT8 byRet_ //0为成功，1为失败，2为超时
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
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << oRecharge << strUdp1 << strUdp2;
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

bool CGame2CenterCommSvr::SendSvr_AddRechargeMailItem(const UINT32* pSvrID_, UINT8 byCnt_,
	const NRoleInfoDefine::SRecharge& oRecharge, //充值仙石的数据
	const std::string& strUdp1, //udpLog参数1(平台传来的)
	const std::string& strUdp2, //udpLog参数2(平台传来的)
	boost::function<void (UINT8 byRet_ //0为成功，1为失败，2为超时
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
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << oRecharge << strUdp1 << strUdp2;
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

//发送：补偿玩家未创建预先充值的仙石
bool CGame2CenterCommSvr::Send_AddTotalPrepaid(
	UINT64 qwUsrID, //帐号ID
	UINT32 dwGold, //仙石数量
	boost::function<void (UINT8 byRet_ //0为成功，1为失败，2为超时
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
	const UINT8 byFuncID_ = 5;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwUsrID << dwGold;
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

bool CGame2CenterCommSvr::SendSvr_AddTotalPrepaid(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwUsrID, //帐号ID
	UINT32 dwGold, //仙石数量
	boost::function<void (UINT8 byRet_ //0为成功，1为失败，2为超时
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
	const UINT8 byFuncID_ = 5;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwUsrID << dwGold;
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

//发送：Q点直购道具
bool CGame2CenterCommSvr::Send_AddQQCoinBuyItem(
	UINT64 qwUsrID, //帐号ID
	const TVecUserItem& vecUserItem, //物品列表
	boost::function<void (UINT8 byRet_ //0为成功，1为失败，2为超时
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
	const UINT8 byFuncID_ = 6;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwUsrID << vecUserItem;
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

bool CGame2CenterCommSvr::SendSvr_AddQQCoinBuyItem(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwUsrID, //帐号ID
	const TVecUserItem& vecUserItem, //物品列表
	boost::function<void (UINT8 byRet_ //0为成功，1为失败，2为超时
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
	const UINT8 byFuncID_ = 6;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwUsrID << vecUserItem;
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

//发送：询问可否提取附件
bool CGame2CenterCommSvr::Send_CheckMailAttch(
	UINT64 qwUsrID, //帐号ID
	UINT64 qwMailID, //邮件ID
	const NMailProt::TVecMailAttachment& vecItemInfo, //附件
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT8 byCan //(返回值)0表示可以提取
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
	const UINT8 byFuncID_ = 7;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwUsrID << qwMailID << vecItemInfo;
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

bool CGame2CenterCommSvr::SendSvr_CheckMailAttch(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwUsrID, //帐号ID
	UINT64 qwMailID, //邮件ID
	const NMailProt::TVecMailAttachment& vecItemInfo, //附件
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT8 byCan //(返回值)0表示可以提取
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
	const UINT8 byFuncID_ = 7;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwUsrID << qwMailID << vecItemInfo;
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

//发送：发送附件
bool CGame2CenterCommSvr::Send_SendMailAttch(
	UINT64 qwUsrID, //帐号ID
	UINT64 qwMailID, //邮件ID
	const NMailProt::TVecMailAttachment& vecItemInfo //附件
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 8;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << qwMailID << vecItemInfo;
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

bool CGame2CenterCommSvr::SendSvr_SendMailAttch(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwUsrID, //帐号ID
	UINT64 qwMailID, //邮件ID
	const NMailProt::TVecMailAttachment& vecItemInfo //附件
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 8;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << qwMailID << vecItemInfo;
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

std::string& CGame2CenterCommSvr::BuildPkg_SendMailAttch(
	UINT64 qwUsrID, //帐号ID
	UINT64 qwMailID, //邮件ID
	const NMailProt::TVecMailAttachment& vecItemInfo //附件
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 8;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << qwMailID << vecItemInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 12, Function: 8";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：修改签名
bool CGame2CenterCommSvr::Send_SetSign(
	UINT64 qwUsrID, //帐号ID
	const std::string& strSign //签名
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 9;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << strSign;
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

bool CGame2CenterCommSvr::SendSvr_SetSign(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwUsrID, //帐号ID
	const std::string& strSign //签名
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 9;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << strSign;
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

std::string& CGame2CenterCommSvr::BuildPkg_SetSign(
	UINT64 qwUsrID, //帐号ID
	const std::string& strSign //签名
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 9;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << strSign;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 12, Function: 9";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：修改表情
bool CGame2CenterCommSvr::Send_SetMood(
	UINT64 qwUsrID, //帐号ID
	UINT16 wMood //表情
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 10;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << wMood;
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

bool CGame2CenterCommSvr::SendSvr_SetMood(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwUsrID, //帐号ID
	UINT16 wMood //表情
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 10;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << wMood;
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

std::string& CGame2CenterCommSvr::BuildPkg_SetMood(
	UINT64 qwUsrID, //帐号ID
	UINT16 wMood //表情
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 10;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << wMood;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 12, Function: 10";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：请求和他人发起战斗
bool CGame2CenterCommSvr::Send_FigtherToOther(
	UINT64 qwUsrID, //帐号ID
	UINT64 qwOtherID, //他人的ID
	UINT32 dwCost, //花费的游戏币
	NBattleGS::EBattleType eBattleType, //战斗类型
	UINT32 dwBufferID, //临时增加的buffer
	UINT32 dwSkillAttrID, //增加的属性
	UINT32 dwCount, //buffer叠加层数
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT8 byRet, //(返回值)请求结果
		UINT8 bySuc, //(返回值)是否胜利
		UINT64 qwBattleID, //(返回值)战报ID
		UINT32 dwSelfFighterPower, //(返回值)自己的战斗力
		UINT8 bySelfQuality, //(返回值)自己的主将品质
		UINT32 dwOtherFighterPower, //(返回值)他人的战斗力
		UINT8 byOtherQuality, //(返回值)他人的主将品质
		UINT32 dwTurns //(返回值)战斗回合数
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
	const UINT8 byFuncID_ = 11;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwUsrID << qwOtherID << dwCost << (UINT8&)eBattleType << dwBufferID << dwSkillAttrID << dwCount;
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

bool CGame2CenterCommSvr::SendSvr_FigtherToOther(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwUsrID, //帐号ID
	UINT64 qwOtherID, //他人的ID
	UINT32 dwCost, //花费的游戏币
	NBattleGS::EBattleType eBattleType, //战斗类型
	UINT32 dwBufferID, //临时增加的buffer
	UINT32 dwSkillAttrID, //增加的属性
	UINT32 dwCount, //buffer叠加层数
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT8 byRet, //(返回值)请求结果
		UINT8 bySuc, //(返回值)是否胜利
		UINT64 qwBattleID, //(返回值)战报ID
		UINT32 dwSelfFighterPower, //(返回值)自己的战斗力
		UINT8 bySelfQuality, //(返回值)自己的主将品质
		UINT32 dwOtherFighterPower, //(返回值)他人的战斗力
		UINT8 byOtherQuality, //(返回值)他人的主将品质
		UINT32 dwTurns //(返回值)战斗回合数
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
	const UINT8 byFuncID_ = 11;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwUsrID << qwOtherID << dwCost << (UINT8&)eBattleType << dwBufferID << dwSkillAttrID << dwCount;
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

//发送：询问可否放下掉落
bool CGame2CenterCommSvr::Send_CanPushLoot(
	UINT64 qwUsrID, //帐号ID
	UINT32 dwLootId, //掉落的ID
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT8 byRet //(返回值)0,可以，1，没有这个掉落，2，其他错误
	)> fnOnReturn_ //返回时的回调函数
)
{
	if(_pSessionMgr == NULL)
	{
		LOG_CRI << "_pSessionMgr == NULL";		return false;
	}
	UINT32 dwSessionID_ = _pSessionMgr->GetNewSession(*this, 9);
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_(new TSessData(fnOnReturn_));
	_pSessionMgr->StoreData(dwSessionID_, pSessData_);
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 12;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwUsrID << dwLootId;
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

bool CGame2CenterCommSvr::SendSvr_CanPushLoot(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwUsrID, //帐号ID
	UINT32 dwLootId, //掉落的ID
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT8 byRet //(返回值)0,可以，1，没有这个掉落，2，其他错误
	)> fnOnReturn_ //返回时的回调函数
)
{
	if(_pSessionMgr == NULL)
	{
		LOG_CRI << "_pSessionMgr == NULL";		return false;
	}
	UINT32 dwSessionID_ = _pSessionMgr->GetNewSession(*this, 9);
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_(new TSessData(fnOnReturn_));
	_pSessionMgr->StoreData(dwSessionID_, pSessData_);
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 12;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwUsrID << dwLootId;
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

//发送：掉落到玩家包裹
bool CGame2CenterCommSvr::Send_PushLoot(
	UINT64 qwUsrID, //帐号ID
	EOpSource eSource, //原因
	NLogDataDefine::ItemFrom eItemFrom, //道具or资源来源类型
	UINT32 dwLootId //掉落的ID
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 13;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << (UINT8&)eSource << (UINT16&)eItemFrom << dwLootId;
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

bool CGame2CenterCommSvr::SendSvr_PushLoot(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwUsrID, //帐号ID
	EOpSource eSource, //原因
	NLogDataDefine::ItemFrom eItemFrom, //道具or资源来源类型
	UINT32 dwLootId //掉落的ID
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 13;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << (UINT8&)eSource << (UINT16&)eItemFrom << dwLootId;
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

std::string& CGame2CenterCommSvr::BuildPkg_PushLoot(
	UINT64 qwUsrID, //帐号ID
	EOpSource eSource, //原因
	NLogDataDefine::ItemFrom eItemFrom, //道具or资源来源类型
	UINT32 dwLootId //掉落的ID
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 13;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << (UINT8&)eSource << (UINT16&)eItemFrom << dwLootId;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 12, Function: 13";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：扣钱或物品
bool CGame2CenterCommSvr::Send_ReduceItem(
	UINT64 qwUsrID, //帐号ID
	NLogDataDefine::ItemTo eItemTo, //道具or资源消耗类型
	UINT32 dwID, //钱或物品ID
	UINT32 dwCount, //数量
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT8 byRet //(返回值)0,可以,1，不足，2，其他错误
	)> fnOnReturn_ //返回时的回调函数
)
{
	if(_pSessionMgr == NULL)
	{
		LOG_CRI << "_pSessionMgr == NULL";		return false;
	}
	UINT32 dwSessionID_ = _pSessionMgr->GetNewSession(*this, 10);
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_(new TSessData(fnOnReturn_));
	_pSessionMgr->StoreData(dwSessionID_, pSessData_);
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 14;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwUsrID << (UINT16&)eItemTo << dwID << dwCount;
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

bool CGame2CenterCommSvr::SendSvr_ReduceItem(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwUsrID, //帐号ID
	NLogDataDefine::ItemTo eItemTo, //道具or资源消耗类型
	UINT32 dwID, //钱或物品ID
	UINT32 dwCount, //数量
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT8 byRet //(返回值)0,可以,1，不足，2，其他错误
	)> fnOnReturn_ //返回时的回调函数
)
{
	if(_pSessionMgr == NULL)
	{
		LOG_CRI << "_pSessionMgr == NULL";		return false;
	}
	UINT32 dwSessionID_ = _pSessionMgr->GetNewSession(*this, 10);
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_(new TSessData(fnOnReturn_));
	_pSessionMgr->StoreData(dwSessionID_, pSessData_);
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 14;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwUsrID << (UINT16&)eItemTo << dwID << dwCount;
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

//发送：物品/资源数量是否够
bool CGame2CenterCommSvr::Send_CanReduceItem(
	UINT64 qwUsrID, //帐号ID
	UINT32 dwItemID, //物品ID
	UINT32 dwCount, //数量
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT8 byRet //(返回值)0,可以,1，不足，2，其他错误
	)> fnOnReturn_ //返回时的回调函数
)
{
	if(_pSessionMgr == NULL)
	{
		LOG_CRI << "_pSessionMgr == NULL";		return false;
	}
	UINT32 dwSessionID_ = _pSessionMgr->GetNewSession(*this, 11);
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_(new TSessData(fnOnReturn_));
	_pSessionMgr->StoreData(dwSessionID_, pSessData_);
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 15;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwUsrID << dwItemID << dwCount;
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

bool CGame2CenterCommSvr::SendSvr_CanReduceItem(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwUsrID, //帐号ID
	UINT32 dwItemID, //物品ID
	UINT32 dwCount, //数量
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT8 byRet //(返回值)0,可以,1，不足，2，其他错误
	)> fnOnReturn_ //返回时的回调函数
)
{
	if(_pSessionMgr == NULL)
	{
		LOG_CRI << "_pSessionMgr == NULL";		return false;
	}
	UINT32 dwSessionID_ = _pSessionMgr->GetNewSession(*this, 11);
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_(new TSessData(fnOnReturn_));
	_pSessionMgr->StoreData(dwSessionID_, pSessData_);
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 15;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwUsrID << dwItemID << dwCount;
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

//发送：查询玩家属性
bool CGame2CenterCommSvr::Send_GetUserUINTProp(
	UINT64 qwUsrID, //帐号ID
	EPlayerUINTProp eUINTPropType, //属性类型
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT32 dwValue, //(返回值)属性值
		UINT8 byError //(返回值)0 成功, 其他错误
	)> fnOnReturn_ //返回时的回调函数
)
{
	if(_pSessionMgr == NULL)
	{
		LOG_CRI << "_pSessionMgr == NULL";		return false;
	}
	UINT32 dwSessionID_ = _pSessionMgr->GetNewSession(*this, 12);
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_(new TSessData(fnOnReturn_));
	_pSessionMgr->StoreData(dwSessionID_, pSessData_);
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 16;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwUsrID << (UINT8&)eUINTPropType;
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

bool CGame2CenterCommSvr::SendSvr_GetUserUINTProp(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwUsrID, //帐号ID
	EPlayerUINTProp eUINTPropType, //属性类型
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT32 dwValue, //(返回值)属性值
		UINT8 byError //(返回值)0 成功, 其他错误
	)> fnOnReturn_ //返回时的回调函数
)
{
	if(_pSessionMgr == NULL)
	{
		LOG_CRI << "_pSessionMgr == NULL";		return false;
	}
	UINT32 dwSessionID_ = _pSessionMgr->GetNewSession(*this, 12);
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_(new TSessData(fnOnReturn_));
	_pSessionMgr->StoreData(dwSessionID_, pSessData_);
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 16;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwUsrID << (UINT8&)eUINTPropType;
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

//发送：设置玩家属性
bool CGame2CenterCommSvr::Send_SetUserUINTProp(
	UINT64 qwUsrID, //帐号ID
	EPlayerUINTProp eUINTPropType, //属性类型
	UINT32 dwValue, //属性值
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT8 byError //(返回值)0 成功, 其他错误
	)> fnOnReturn_ //返回时的回调函数
)
{
	if(_pSessionMgr == NULL)
	{
		LOG_CRI << "_pSessionMgr == NULL";		return false;
	}
	UINT32 dwSessionID_ = _pSessionMgr->GetNewSession(*this, 13);
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_(new TSessData(fnOnReturn_));
	_pSessionMgr->StoreData(dwSessionID_, pSessData_);
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 17;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwUsrID << (UINT8&)eUINTPropType << dwValue;
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

bool CGame2CenterCommSvr::SendSvr_SetUserUINTProp(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwUsrID, //帐号ID
	EPlayerUINTProp eUINTPropType, //属性类型
	UINT32 dwValue, //属性值
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT8 byError //(返回值)0 成功, 其他错误
	)> fnOnReturn_ //返回时的回调函数
)
{
	if(_pSessionMgr == NULL)
	{
		LOG_CRI << "_pSessionMgr == NULL";		return false;
	}
	UINT32 dwSessionID_ = _pSessionMgr->GetNewSession(*this, 13);
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_(new TSessData(fnOnReturn_));
	_pSessionMgr->StoreData(dwSessionID_, pSessData_);
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 17;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwUsrID << (UINT8&)eUINTPropType << dwValue;
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

//发送：扣除物品/钱币
bool CGame2CenterCommSvr::Send_UserSubItem(
	UINT64 qwUsrID, //帐号ID
	NLogDataDefine::ItemTo eItemTo, //道具or资源消耗类型
	const TVecUserItem& vecUserItem, //物品列表
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT8 byError //(返回值)0 成功, 其他错误
	)> fnOnReturn_ //返回时的回调函数
)
{
	if(_pSessionMgr == NULL)
	{
		LOG_CRI << "_pSessionMgr == NULL";		return false;
	}
	UINT32 dwSessionID_ = _pSessionMgr->GetNewSession(*this, 14);
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_(new TSessData(fnOnReturn_));
	_pSessionMgr->StoreData(dwSessionID_, pSessData_);
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 18;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwUsrID << (UINT16&)eItemTo << vecUserItem;
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

bool CGame2CenterCommSvr::SendSvr_UserSubItem(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwUsrID, //帐号ID
	NLogDataDefine::ItemTo eItemTo, //道具or资源消耗类型
	const TVecUserItem& vecUserItem, //物品列表
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT8 byError //(返回值)0 成功, 其他错误
	)> fnOnReturn_ //返回时的回调函数
)
{
	if(_pSessionMgr == NULL)
	{
		LOG_CRI << "_pSessionMgr == NULL";		return false;
	}
	UINT32 dwSessionID_ = _pSessionMgr->GetNewSession(*this, 14);
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_(new TSessData(fnOnReturn_));
	_pSessionMgr->StoreData(dwSessionID_, pSessData_);
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 18;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwUsrID << (UINT16&)eItemTo << vecUserItem;
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

//发送：添加物品/钱币
bool CGame2CenterCommSvr::Send_UserAddItem(
	UINT64 qwUsrID, //帐号ID
	NLogDataDefine::ItemFrom eItemFrom, //道具or资源来源类型
	const TVecUserItem& vecUserItem, //物品列表
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT8 byError //(返回值)0 成功, 其他错误
	)> fnOnReturn_ //返回时的回调函数
)
{
	if(_pSessionMgr == NULL)
	{
		LOG_CRI << "_pSessionMgr == NULL";		return false;
	}
	UINT32 dwSessionID_ = _pSessionMgr->GetNewSession(*this, 15);
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_(new TSessData(fnOnReturn_));
	_pSessionMgr->StoreData(dwSessionID_, pSessData_);
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 19;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwUsrID << (UINT16&)eItemFrom << vecUserItem;
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

bool CGame2CenterCommSvr::SendSvr_UserAddItem(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwUsrID, //帐号ID
	NLogDataDefine::ItemFrom eItemFrom, //道具or资源来源类型
	const TVecUserItem& vecUserItem, //物品列表
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT8 byError //(返回值)0 成功, 其他错误
	)> fnOnReturn_ //返回时的回调函数
)
{
	if(_pSessionMgr == NULL)
	{
		LOG_CRI << "_pSessionMgr == NULL";		return false;
	}
	UINT32 dwSessionID_ = _pSessionMgr->GetNewSession(*this, 15);
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_(new TSessData(fnOnReturn_));
	_pSessionMgr->StoreData(dwSessionID_, pSessData_);
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 19;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwUsrID << (UINT16&)eItemFrom << vecUserItem;
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

//发送：转发系统消息
bool CGame2CenterCommSvr::Send_SendSysMsg(
	UINT64 qwUsrID, //帐号ID
	UINT16 wMsgID //消息ID
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 20;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << wMsgID;
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

bool CGame2CenterCommSvr::SendSvr_SendSysMsg(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwUsrID, //帐号ID
	UINT16 wMsgID //消息ID
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 20;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << wMsgID;
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

std::string& CGame2CenterCommSvr::BuildPkg_SendSysMsg(
	UINT64 qwUsrID, //帐号ID
	UINT16 wMsgID //消息ID
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 20;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << wMsgID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 12, Function: 20";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：任务事件通知
bool CGame2CenterCommSvr::Send_ActionNotify(
	UINT64 qwUsrID, //帐号ID
	UINT16 wAction //通知类型
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 21;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << wAction;
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

bool CGame2CenterCommSvr::SendSvr_ActionNotify(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwUsrID, //帐号ID
	UINT16 wAction //通知类型
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 21;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << wAction;
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

std::string& CGame2CenterCommSvr::BuildPkg_ActionNotify(
	UINT64 qwUsrID, //帐号ID
	UINT16 wAction //通知类型
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 21;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << wAction;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 12, Function: 21";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：气泡事件通知
bool CGame2CenterCommSvr::Send_BubbleNotify(
	UINT64 qwUsrID, //帐号ID
	NProtoCommon::EDataChange eType, //修改类型
	UINT16 wMsgID, //通知类型
	const TVecINT64& vecParam, //整型变量
	const TVecString& vecString //字符串型变量
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 22;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << (UINT8&)eType << wMsgID << vecParam << vecString;
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

bool CGame2CenterCommSvr::SendSvr_BubbleNotify(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwUsrID, //帐号ID
	NProtoCommon::EDataChange eType, //修改类型
	UINT16 wMsgID, //通知类型
	const TVecINT64& vecParam, //整型变量
	const TVecString& vecString //字符串型变量
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 22;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << (UINT8&)eType << wMsgID << vecParam << vecString;
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

std::string& CGame2CenterCommSvr::BuildPkg_BubbleNotify(
	UINT64 qwUsrID, //帐号ID
	NProtoCommon::EDataChange eType, //修改类型
	UINT16 wMsgID, //通知类型
	const TVecINT64& vecParam, //整型变量
	const TVecString& vecString //字符串型变量
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 22;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << (UINT8&)eType << wMsgID << vecParam << vecString;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 12, Function: 22";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：玩家帮派等级更新
bool CGame2CenterCommSvr::Send_GuildLevelUpdated(
	UINT64 qwRoleID, //玩家ID
	UINT16 wLevel //帮派等级
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 23;
	try
	{
		ar << byProtID_ << byFuncID_ << qwRoleID << wLevel;
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

bool CGame2CenterCommSvr::SendSvr_GuildLevelUpdated(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwRoleID, //玩家ID
	UINT16 wLevel //帮派等级
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 23;
	try
	{
		ar << byProtID_ << byFuncID_ << qwRoleID << wLevel;
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

std::string& CGame2CenterCommSvr::BuildPkg_GuildLevelUpdated(
	UINT64 qwRoleID, //玩家ID
	UINT16 wLevel //帮派等级
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 23;
	try
	{
		ar << byProtID_ << byFuncID_ << qwRoleID << wLevel;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 12, Function: 23";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：玩家帮派名有更新
bool CGame2CenterCommSvr::Send_GuildNameUpdated(
	UINT64 qwRoleID, //玩家ID
	const std::string& strGuildName //帮派名称
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 24;
	try
	{
		ar << byProtID_ << byFuncID_ << qwRoleID << strGuildName;
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

bool CGame2CenterCommSvr::SendSvr_GuildNameUpdated(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwRoleID, //玩家ID
	const std::string& strGuildName //帮派名称
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 24;
	try
	{
		ar << byProtID_ << byFuncID_ << qwRoleID << strGuildName;
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

std::string& CGame2CenterCommSvr::BuildPkg_GuildNameUpdated(
	UINT64 qwRoleID, //玩家ID
	const std::string& strGuildName //帮派名称
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 24;
	try
	{
		ar << byProtID_ << byFuncID_ << qwRoleID << strGuildName;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 12, Function: 24";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：帮派技能属性更新
bool CGame2CenterCommSvr::Send_GuildTechUpdate(
	UINT64 qwRoleID, //玩家唯一ID
	const NProtoCommon::TVecFtAttrMod& vecFtAttr, //玩家的帮派技能属性
	const NGuildProt::TVecGuildTechInfo& vecGuildTech //玩家的帮派技能信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 25;
	try
	{
		ar << byProtID_ << byFuncID_ << qwRoleID << vecFtAttr << vecGuildTech;
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

bool CGame2CenterCommSvr::SendSvr_GuildTechUpdate(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwRoleID, //玩家唯一ID
	const NProtoCommon::TVecFtAttrMod& vecFtAttr, //玩家的帮派技能属性
	const NGuildProt::TVecGuildTechInfo& vecGuildTech //玩家的帮派技能信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 25;
	try
	{
		ar << byProtID_ << byFuncID_ << qwRoleID << vecFtAttr << vecGuildTech;
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

std::string& CGame2CenterCommSvr::BuildPkg_GuildTechUpdate(
	UINT64 qwRoleID, //玩家唯一ID
	const NProtoCommon::TVecFtAttrMod& vecFtAttr, //玩家的帮派技能属性
	const NGuildProt::TVecGuildTechInfo& vecGuildTech //玩家的帮派技能信息
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 25;
	try
	{
		ar << byProtID_ << byFuncID_ << qwRoleID << vecFtAttr << vecGuildTech;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 12, Function: 25";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：重新加载表格
bool CGame2CenterCommSvr::Send_ReloadTable(
	const TVecString& vecTableName //表格名字
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 26;
	try
	{
		ar << byProtID_ << byFuncID_ << vecTableName;
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

bool CGame2CenterCommSvr::SendSvr_ReloadTable(const UINT32* pSvrID_, UINT8 byCnt_,
	const TVecString& vecTableName //表格名字
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 26;
	try
	{
		ar << byProtID_ << byFuncID_ << vecTableName;
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

std::string& CGame2CenterCommSvr::BuildPkg_ReloadTable(
	const TVecString& vecTableName //表格名字
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 26;
	try
	{
		ar << byProtID_ << byFuncID_ << vecTableName;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 12, Function: 26";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：玩家九疑鼎属性更新
bool CGame2CenterCommSvr::Send_TripodAttrUpdate(
	UINT64 qwRoleID, //玩家唯一ID
	const TVecUINT32& vecValue //九疑鼎ID、等级
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 27;
	try
	{
		ar << byProtID_ << byFuncID_ << qwRoleID << vecValue;
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

bool CGame2CenterCommSvr::SendSvr_TripodAttrUpdate(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwRoleID, //玩家唯一ID
	const TVecUINT32& vecValue //九疑鼎ID、等级
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 27;
	try
	{
		ar << byProtID_ << byFuncID_ << qwRoleID << vecValue;
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

std::string& CGame2CenterCommSvr::BuildPkg_TripodAttrUpdate(
	UINT64 qwRoleID, //玩家唯一ID
	const TVecUINT32& vecValue //九疑鼎ID、等级
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 27;
	try
	{
		ar << byProtID_ << byFuncID_ << qwRoleID << vecValue;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 12, Function: 27";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：完成GetCond条件
bool CGame2CenterCommSvr::Send_ProcessCond(
	UINT64 qwUsrID, //玩家ID
	UINT16 wCondID, //条件ID
	NLogDataDefine::ItemTo eItemTo, //道具or资源消耗类型
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT8 byError //(返回值)0 成功, 1 其他错误
	)> fnOnReturn_ //返回时的回调函数
)
{
	if(_pSessionMgr == NULL)
	{
		LOG_CRI << "_pSessionMgr == NULL";		return false;
	}
	UINT32 dwSessionID_ = _pSessionMgr->GetNewSession(*this, 16);
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_(new TSessData(fnOnReturn_));
	_pSessionMgr->StoreData(dwSessionID_, pSessData_);
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 28;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwUsrID << wCondID << (UINT16&)eItemTo;
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

bool CGame2CenterCommSvr::SendSvr_ProcessCond(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwUsrID, //玩家ID
	UINT16 wCondID, //条件ID
	NLogDataDefine::ItemTo eItemTo, //道具or资源消耗类型
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT8 byError //(返回值)0 成功, 1 其他错误
	)> fnOnReturn_ //返回时的回调函数
)
{
	if(_pSessionMgr == NULL)
	{
		LOG_CRI << "_pSessionMgr == NULL";		return false;
	}
	UINT32 dwSessionID_ = _pSessionMgr->GetNewSession(*this, 16);
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_(new TSessData(fnOnReturn_));
	_pSessionMgr->StoreData(dwSessionID_, pSessData_);
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 28;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwUsrID << wCondID << (UINT16&)eItemTo;
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

//发送：玩家升级九疑鼎
bool CGame2CenterCommSvr::Send_UpgradeTripod(
	UINT64 qwUsrID, //玩家ID
	UINT8 byTripodID, //九疑鼎ID
	UINT8 byLevel, //九疑鼎当前等级
	UINT32 dwExp, //九疑鼎当前经验值
	UINT8 byOneKey, //是否一键
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT8 byError, //(返回值)0 成功, 1 其他错误
		UINT8 byLevel, //(返回值)九疑鼎当前等级
		UINT32 dwExp //(返回值)九疑鼎当前经验值
	)> fnOnReturn_ //返回时的回调函数
)
{
	if(_pSessionMgr == NULL)
	{
		LOG_CRI << "_pSessionMgr == NULL";		return false;
	}
	UINT32 dwSessionID_ = _pSessionMgr->GetNewSession(*this, 17);
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_(new TSessData(fnOnReturn_));
	_pSessionMgr->StoreData(dwSessionID_, pSessData_);
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 29;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwUsrID << byTripodID << byLevel << dwExp << byOneKey;
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

bool CGame2CenterCommSvr::SendSvr_UpgradeTripod(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwUsrID, //玩家ID
	UINT8 byTripodID, //九疑鼎ID
	UINT8 byLevel, //九疑鼎当前等级
	UINT32 dwExp, //九疑鼎当前经验值
	UINT8 byOneKey, //是否一键
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT8 byError, //(返回值)0 成功, 1 其他错误
		UINT8 byLevel, //(返回值)九疑鼎当前等级
		UINT32 dwExp //(返回值)九疑鼎当前经验值
	)> fnOnReturn_ //返回时的回调函数
)
{
	if(_pSessionMgr == NULL)
	{
		LOG_CRI << "_pSessionMgr == NULL";		return false;
	}
	UINT32 dwSessionID_ = _pSessionMgr->GetNewSession(*this, 17);
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_(new TSessData(fnOnReturn_));
	_pSessionMgr->StoreData(dwSessionID_, pSessData_);
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 29;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwUsrID << byTripodID << byLevel << dwExp << byOneKey;
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

//发送：加速九疑鼎炼丹(道具入鼎)
bool CGame2CenterCommSvr::Send_SpeedTripod(
	UINT64 qwUsrID, //玩家ID
	UINT32 dwCurSoul, //当前九疑鼎的火种元气值
	UINT32 dwMaxSoul, //当前九疑鼎的火种最大元气值(配置)
	const NItemProt::TVecItemCount& vecItems, //入鼎道具列表
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT8 byError, //(返回值)0 成功, 1 其他错误
		UINT32 dwSoul //(返回值)九疑鼎增加的元气值
	)> fnOnReturn_ //返回时的回调函数
)
{
	if(_pSessionMgr == NULL)
	{
		LOG_CRI << "_pSessionMgr == NULL";		return false;
	}
	UINT32 dwSessionID_ = _pSessionMgr->GetNewSession(*this, 18);
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_(new TSessData(fnOnReturn_));
	_pSessionMgr->StoreData(dwSessionID_, pSessData_);
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 30;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwUsrID << dwCurSoul << dwMaxSoul << vecItems;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 12, Function: 30";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterCommSvr::SendSvr_SpeedTripod(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwUsrID, //玩家ID
	UINT32 dwCurSoul, //当前九疑鼎的火种元气值
	UINT32 dwMaxSoul, //当前九疑鼎的火种最大元气值(配置)
	const NItemProt::TVecItemCount& vecItems, //入鼎道具列表
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT8 byError, //(返回值)0 成功, 1 其他错误
		UINT32 dwSoul //(返回值)九疑鼎增加的元气值
	)> fnOnReturn_ //返回时的回调函数
)
{
	if(_pSessionMgr == NULL)
	{
		LOG_CRI << "_pSessionMgr == NULL";		return false;
	}
	UINT32 dwSessionID_ = _pSessionMgr->GetNewSession(*this, 18);
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_(new TSessData(fnOnReturn_));
	_pSessionMgr->StoreData(dwSessionID_, pSessData_);
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 30;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwUsrID << dwCurSoul << dwMaxSoul << vecItems;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 12, Function: 30";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

//发送：判断玩家是否拥有散仙
bool CGame2CenterCommSvr::Send_CheckHasFighter(
	UINT64 qwUsrID, //玩家ID
	UINT16 wFighterID, //散仙ID
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT8 byError, //(返回值)0 拥有, 1 其他错误
		UINT8 byColor //(返回值)散仙品质
	)> fnOnReturn_ //返回时的回调函数
)
{
	if(_pSessionMgr == NULL)
	{
		LOG_CRI << "_pSessionMgr == NULL";		return false;
	}
	UINT32 dwSessionID_ = _pSessionMgr->GetNewSession(*this, 19);
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_(new TSessData(fnOnReturn_));
	_pSessionMgr->StoreData(dwSessionID_, pSessData_);
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 31;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwUsrID << wFighterID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 12, Function: 31";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterCommSvr::SendSvr_CheckHasFighter(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwUsrID, //玩家ID
	UINT16 wFighterID, //散仙ID
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT8 byError, //(返回值)0 拥有, 1 其他错误
		UINT8 byColor //(返回值)散仙品质
	)> fnOnReturn_ //返回时的回调函数
)
{
	if(_pSessionMgr == NULL)
	{
		LOG_CRI << "_pSessionMgr == NULL";		return false;
	}
	UINT32 dwSessionID_ = _pSessionMgr->GetNewSession(*this, 19);
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_(new TSessData(fnOnReturn_));
	_pSessionMgr->StoreData(dwSessionID_, pSessData_);
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 31;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwUsrID << wFighterID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 12, Function: 31";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

//发送：获取战斗力
bool CGame2CenterCommSvr::Send_GetBattlePoint(
	UINT64 qwUsrID, //玩家ID
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT8 byError, //(返回值)0 成功, 1 其他错误
		UINT32 dwBattlePoint //(返回值)玩家战斗力
	)> fnOnReturn_ //返回时的回调函数
)
{
	if(_pSessionMgr == NULL)
	{
		LOG_CRI << "_pSessionMgr == NULL";		return false;
	}
	UINT32 dwSessionID_ = _pSessionMgr->GetNewSession(*this, 20);
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_(new TSessData(fnOnReturn_));
	_pSessionMgr->StoreData(dwSessionID_, pSessData_);
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 32;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwUsrID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 12, Function: 32";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterCommSvr::SendSvr_GetBattlePoint(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwUsrID, //玩家ID
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT8 byError, //(返回值)0 成功, 1 其他错误
		UINT32 dwBattlePoint //(返回值)玩家战斗力
	)> fnOnReturn_ //返回时的回调函数
)
{
	if(_pSessionMgr == NULL)
	{
		LOG_CRI << "_pSessionMgr == NULL";		return false;
	}
	UINT32 dwSessionID_ = _pSessionMgr->GetNewSession(*this, 20);
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_(new TSessData(fnOnReturn_));
	_pSessionMgr->StoreData(dwSessionID_, pSessData_);
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 32;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwUsrID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 12, Function: 32";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

//发送：玩家发事件中心消息
bool CGame2CenterCommSvr::Send_OnPlayerEvent(
	UINT64 qwUsrID, //玩家ID
	NEventCenter::EventType eEventType, //事件类型
	const TVecINT32& vecParam, //事件参数
	const std::string& strParam, //事件参数
	bool bLog //事件参数
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 33;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << (UINT16&)eEventType << vecParam << strParam << bLog;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 12, Function: 33";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterCommSvr::SendSvr_OnPlayerEvent(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwUsrID, //玩家ID
	NEventCenter::EventType eEventType, //事件类型
	const TVecINT32& vecParam, //事件参数
	const std::string& strParam, //事件参数
	bool bLog //事件参数
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 33;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << (UINT16&)eEventType << vecParam << strParam << bLog;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 12, Function: 33";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGame2CenterCommSvr::BuildPkg_OnPlayerEvent(
	UINT64 qwUsrID, //玩家ID
	NEventCenter::EventType eEventType, //事件类型
	const TVecINT32& vecParam, //事件参数
	const std::string& strParam, //事件参数
	bool bLog //事件参数
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 33;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << (UINT16&)eEventType << vecParam << strParam << bLog;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 12, Function: 33";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：增加或者设置玩家GameVar数值
bool CGame2CenterCommSvr::Send_AddORSetGameVar(
	UINT64 qwUsrID, //玩家ID
	UINT8 byType, //0增加 >0设置
	const TVecUINT16& vecVars, //varID列表
	const TVecUINT64& vecValues //var数值列表(必须与vecVars对应)
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 34;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << byType << vecVars << vecValues;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 12, Function: 34";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterCommSvr::SendSvr_AddORSetGameVar(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwUsrID, //玩家ID
	UINT8 byType, //0增加 >0设置
	const TVecUINT16& vecVars, //varID列表
	const TVecUINT64& vecValues //var数值列表(必须与vecVars对应)
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 34;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << byType << vecVars << vecValues;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 12, Function: 34";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGame2CenterCommSvr::BuildPkg_AddORSetGameVar(
	UINT64 qwUsrID, //玩家ID
	UINT8 byType, //0增加 >0设置
	const TVecUINT16& vecVars, //varID列表
	const TVecUINT64& vecValues //var数值列表(必须与vecVars对应)
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 34;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << byType << vecVars << vecValues;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 12, Function: 34";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：清除玩家GameVar
bool CGame2CenterCommSvr::Send_DeleteGameVar(
	UINT64 qwUsrID, //玩家ID
	const TVecUINT16& vecVars //varID列表
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 35;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << vecVars;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 12, Function: 35";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterCommSvr::SendSvr_DeleteGameVar(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwUsrID, //玩家ID
	const TVecUINT16& vecVars //varID列表
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 35;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << vecVars;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 12, Function: 35";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGame2CenterCommSvr::BuildPkg_DeleteGameVar(
	UINT64 qwUsrID, //玩家ID
	const TVecUINT16& vecVars //varID列表
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 35;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << vecVars;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 12, Function: 35";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：增加商城限购活动
bool CGame2CenterCommSvr::Send_AddMallDiscount(
	const NMallProt::SDiscount& oDiscount //限购道具列表
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 36;
	try
	{
		ar << byProtID_ << byFuncID_ << oDiscount;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 12, Function: 36";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterCommSvr::SendSvr_AddMallDiscount(const UINT32* pSvrID_, UINT8 byCnt_,
	const NMallProt::SDiscount& oDiscount //限购道具列表
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 36;
	try
	{
		ar << byProtID_ << byFuncID_ << oDiscount;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 12, Function: 36";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGame2CenterCommSvr::BuildPkg_AddMallDiscount(
	const NMallProt::SDiscount& oDiscount //限购道具列表
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 36;
	try
	{
		ar << byProtID_ << byFuncID_ << oDiscount;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 12, Function: 36";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：清除商城限购活动
bool CGame2CenterCommSvr::Send_ClearMallDiscount(
	UINT8 byPos //限购道具栏位
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 37;
	try
	{
		ar << byProtID_ << byFuncID_ << byPos;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 12, Function: 37";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterCommSvr::SendSvr_ClearMallDiscount(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT8 byPos //限购道具栏位
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 37;
	try
	{
		ar << byProtID_ << byFuncID_ << byPos;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 12, Function: 37";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGame2CenterCommSvr::BuildPkg_ClearMallDiscount(
	UINT8 byPos //限购道具栏位
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 37;
	try
	{
		ar << byProtID_ << byFuncID_ << byPos;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 12, Function: 37";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：扣除多个玩家钱币/物品
bool CGame2CenterCommSvr::Send_SubPlayerMoney(
	const TVecUINT64& vecUserID, //玩家ID
	const TVecUserItem& vecUserItem, //物品列表
	boost::function<void (UINT8 byRet_ //0为成功，1为失败，2为超时
	)> fnOnReturn_ //返回时的回调函数
)
{
	if(_pSessionMgr == NULL)
	{
		LOG_CRI << "_pSessionMgr == NULL";		return false;
	}
	UINT32 dwSessionID_ = _pSessionMgr->GetNewSession(*this, 21);
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_(new TSessData(fnOnReturn_));
	_pSessionMgr->StoreData(dwSessionID_, pSessData_);
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 38;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << vecUserID << vecUserItem;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 12, Function: 38";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterCommSvr::SendSvr_SubPlayerMoney(const UINT32* pSvrID_, UINT8 byCnt_,
	const TVecUINT64& vecUserID, //玩家ID
	const TVecUserItem& vecUserItem, //物品列表
	boost::function<void (UINT8 byRet_ //0为成功，1为失败，2为超时
	)> fnOnReturn_ //返回时的回调函数
)
{
	if(_pSessionMgr == NULL)
	{
		LOG_CRI << "_pSessionMgr == NULL";		return false;
	}
	UINT32 dwSessionID_ = _pSessionMgr->GetNewSession(*this, 21);
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_(new TSessData(fnOnReturn_));
	_pSessionMgr->StoreData(dwSessionID_, pSessData_);
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 38;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << vecUserID << vecUserItem;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 12, Function: 38";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

//发送：设置玩家等级
bool CGame2CenterCommSvr::Send_SetPlayerLevel(
	UINT64 qwUsrID, //玩家ID
	UINT16 wLevel, //玩家等级
	boost::function<void (UINT8 byRet_ //0为成功，1为失败，2为超时
	)> fnOnReturn_ //返回时的回调函数
)
{
	if(_pSessionMgr == NULL)
	{
		LOG_CRI << "_pSessionMgr == NULL";		return false;
	}
	UINT32 dwSessionID_ = _pSessionMgr->GetNewSession(*this, 22);
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_(new TSessData(fnOnReturn_));
	_pSessionMgr->StoreData(dwSessionID_, pSessData_);
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 39;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwUsrID << wLevel;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 12, Function: 39";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterCommSvr::SendSvr_SetPlayerLevel(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwUsrID, //玩家ID
	UINT16 wLevel, //玩家等级
	boost::function<void (UINT8 byRet_ //0为成功，1为失败，2为超时
	)> fnOnReturn_ //返回时的回调函数
)
{
	if(_pSessionMgr == NULL)
	{
		LOG_CRI << "_pSessionMgr == NULL";		return false;
	}
	UINT32 dwSessionID_ = _pSessionMgr->GetNewSession(*this, 22);
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_(new TSessData(fnOnReturn_));
	_pSessionMgr->StoreData(dwSessionID_, pSessData_);
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 39;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwUsrID << wLevel;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 12, Function: 39";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

//发送：设置玩家VIP等级
bool CGame2CenterCommSvr::Send_SetPlayerVIPLevel(
	UINT64 qwUsrID, //玩家ID
	NPHPProt::EOptType eOptType, //台台操作类型(eOptSetPlayerVIPLevel/eOptAddGrowthValue)
	UINT32 dwLevelOrGrowthValue, //等级or成长值
	boost::function<void (UINT8 byRet_ //0为成功，1为失败，2为超时
	)> fnOnReturn_ //返回时的回调函数
)
{
	if(_pSessionMgr == NULL)
	{
		LOG_CRI << "_pSessionMgr == NULL";		return false;
	}
	UINT32 dwSessionID_ = _pSessionMgr->GetNewSession(*this, 23);
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_(new TSessData(fnOnReturn_));
	_pSessionMgr->StoreData(dwSessionID_, pSessData_);
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 40;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwUsrID << (INT8&)eOptType << dwLevelOrGrowthValue;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 12, Function: 40";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterCommSvr::SendSvr_SetPlayerVIPLevel(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwUsrID, //玩家ID
	NPHPProt::EOptType eOptType, //台台操作类型(eOptSetPlayerVIPLevel/eOptAddGrowthValue)
	UINT32 dwLevelOrGrowthValue, //等级or成长值
	boost::function<void (UINT8 byRet_ //0为成功，1为失败，2为超时
	)> fnOnReturn_ //返回时的回调函数
)
{
	if(_pSessionMgr == NULL)
	{
		LOG_CRI << "_pSessionMgr == NULL";		return false;
	}
	UINT32 dwSessionID_ = _pSessionMgr->GetNewSession(*this, 23);
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_(new TSessData(fnOnReturn_));
	_pSessionMgr->StoreData(dwSessionID_, pSessData_);
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 40;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwUsrID << (INT8&)eOptType << dwLevelOrGrowthValue;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 12, Function: 40";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

//发送：设置日常任务
bool CGame2CenterCommSvr::Send_SetDayTask(
	const TVecUINT64& vecUserID, //玩家ID
	NPHPProt::EPHPTaskType eTaskType, //日常任务类型
	boost::function<void (UINT8 byRet_ //0为成功，1为失败，2为超时
	)> fnOnReturn_ //返回时的回调函数
)
{
	if(_pSessionMgr == NULL)
	{
		LOG_CRI << "_pSessionMgr == NULL";		return false;
	}
	UINT32 dwSessionID_ = _pSessionMgr->GetNewSession(*this, 24);
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_(new TSessData(fnOnReturn_));
	_pSessionMgr->StoreData(dwSessionID_, pSessData_);
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 41;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << vecUserID << (UINT8&)eTaskType;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 12, Function: 41";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterCommSvr::SendSvr_SetDayTask(const UINT32* pSvrID_, UINT8 byCnt_,
	const TVecUINT64& vecUserID, //玩家ID
	NPHPProt::EPHPTaskType eTaskType, //日常任务类型
	boost::function<void (UINT8 byRet_ //0为成功，1为失败，2为超时
	)> fnOnReturn_ //返回时的回调函数
)
{
	if(_pSessionMgr == NULL)
	{
		LOG_CRI << "_pSessionMgr == NULL";		return false;
	}
	UINT32 dwSessionID_ = _pSessionMgr->GetNewSession(*this, 24);
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_(new TSessData(fnOnReturn_));
	_pSessionMgr->StoreData(dwSessionID_, pSessData_);
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 41;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << vecUserID << (UINT8&)eTaskType;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 12, Function: 41";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

//发送：获取玩家信息
bool CGame2CenterCommSvr::Send_GetPlayerInfo(
	UINT64 qwUserID, //玩家ID
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		const NPHPProt::SPlayerInfo& sPlayerInfo //(返回值)返回的数据
	)> fnOnReturn_ //返回时的回调函数
)
{
	if(_pSessionMgr == NULL)
	{
		LOG_CRI << "_pSessionMgr == NULL";		return false;
	}
	UINT32 dwSessionID_ = _pSessionMgr->GetNewSession(*this, 25);
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_(new TSessData(fnOnReturn_));
	_pSessionMgr->StoreData(dwSessionID_, pSessData_);
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 42;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwUserID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 12, Function: 42";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterCommSvr::SendSvr_GetPlayerInfo(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwUserID, //玩家ID
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		const NPHPProt::SPlayerInfo& sPlayerInfo //(返回值)返回的数据
	)> fnOnReturn_ //返回时的回调函数
)
{
	if(_pSessionMgr == NULL)
	{
		LOG_CRI << "_pSessionMgr == NULL";		return false;
	}
	UINT32 dwSessionID_ = _pSessionMgr->GetNewSession(*this, 25);
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_(new TSessData(fnOnReturn_));
	_pSessionMgr->StoreData(dwSessionID_, pSessData_);
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 42;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwUserID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 12, Function: 42";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

//发送：获取玩家背包信息
bool CGame2CenterCommSvr::Send_GetPlayerBagInfo(
	UINT64 qwUserID, //玩家ID
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		const NPHPProt::TVecPlayerBagInfo& vecPlayerBagInfo //(返回值)返回的数据
	)> fnOnReturn_ //返回时的回调函数
)
{
	if(_pSessionMgr == NULL)
	{
		LOG_CRI << "_pSessionMgr == NULL";		return false;
	}
	UINT32 dwSessionID_ = _pSessionMgr->GetNewSession(*this, 26);
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_(new TSessData(fnOnReturn_));
	_pSessionMgr->StoreData(dwSessionID_, pSessData_);
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 43;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwUserID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 12, Function: 43";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterCommSvr::SendSvr_GetPlayerBagInfo(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwUserID, //玩家ID
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		const NPHPProt::TVecPlayerBagInfo& vecPlayerBagInfo //(返回值)返回的数据
	)> fnOnReturn_ //返回时的回调函数
)
{
	if(_pSessionMgr == NULL)
	{
		LOG_CRI << "_pSessionMgr == NULL";		return false;
	}
	UINT32 dwSessionID_ = _pSessionMgr->GetNewSession(*this, 26);
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_(new TSessData(fnOnReturn_));
	_pSessionMgr->StoreData(dwSessionID_, pSessData_);
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 43;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwUserID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 12, Function: 43";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

//发送：删除玩家物品
bool CGame2CenterCommSvr::Send_DelPlayerItem(
	UINT64 qwUserID, //用户ID
	UINT8 byType, //1；背包，2：仓库
	UINT64 qwInstID, //物品唯一ID
	UINT16 wCount, //堆叠数
	boost::function<void (UINT8 byRet_ //0为成功，1为失败，2为超时
	)> fnOnReturn_ //返回时的回调函数
)
{
	if(_pSessionMgr == NULL)
	{
		LOG_CRI << "_pSessionMgr == NULL";		return false;
	}
	UINT32 dwSessionID_ = _pSessionMgr->GetNewSession(*this, 27);
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_(new TSessData(fnOnReturn_));
	_pSessionMgr->StoreData(dwSessionID_, pSessData_);
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 44;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwUserID << byType << qwInstID << wCount;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 12, Function: 44";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterCommSvr::SendSvr_DelPlayerItem(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwUserID, //用户ID
	UINT8 byType, //1；背包，2：仓库
	UINT64 qwInstID, //物品唯一ID
	UINT16 wCount, //堆叠数
	boost::function<void (UINT8 byRet_ //0为成功，1为失败，2为超时
	)> fnOnReturn_ //返回时的回调函数
)
{
	if(_pSessionMgr == NULL)
	{
		LOG_CRI << "_pSessionMgr == NULL";		return false;
	}
	UINT32 dwSessionID_ = _pSessionMgr->GetNewSession(*this, 27);
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_(new TSessData(fnOnReturn_));
	_pSessionMgr->StoreData(dwSessionID_, pSessData_);
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 44;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwUserID << byType << qwInstID << wCount;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 12, Function: 44";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

//发送：给玩家用掉落包发系统邮件
bool CGame2CenterCommSvr::Send_SendSysMailByLootId(
	UINT64 qwUserID, //用户ID
	UINT16 wTitle, //邮件标题
	UINT16 wText, //邮件正文
	const TVecString& vecParam, //邮件参数
	UINT32 dwLootId, //掉落包
	UINT32 dwRate //倍率
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 45;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUserID << wTitle << wText << vecParam << dwLootId << dwRate;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 12, Function: 45";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterCommSvr::SendSvr_SendSysMailByLootId(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwUserID, //用户ID
	UINT16 wTitle, //邮件标题
	UINT16 wText, //邮件正文
	const TVecString& vecParam, //邮件参数
	UINT32 dwLootId, //掉落包
	UINT32 dwRate //倍率
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 45;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUserID << wTitle << wText << vecParam << dwLootId << dwRate;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 12, Function: 45";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGame2CenterCommSvr::BuildPkg_SendSysMailByLootId(
	UINT64 qwUserID, //用户ID
	UINT16 wTitle, //邮件标题
	UINT16 wText, //邮件正文
	const TVecString& vecParam, //邮件参数
	UINT32 dwLootId, //掉落包
	UINT32 dwRate //倍率
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 45;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUserID << wTitle << wText << vecParam << dwLootId << dwRate;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 12, Function: 45";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：任务集市
bool CGame2CenterCommSvr::Send_GetTaskStateForPlatfrom(
	UINT64 qwUserID, //用户ID
	UINT32 dwTaskID, //邮件标题
	UINT8 byStep, //邮件正文
	UINT8 byOpt, //邮件正文
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		NPHPProt::ETaskState eRet //(返回值)返回的数据
	)> fnOnReturn_ //返回时的回调函数
)
{
	if(_pSessionMgr == NULL)
	{
		LOG_CRI << "_pSessionMgr == NULL";		return false;
	}
	UINT32 dwSessionID_ = _pSessionMgr->GetNewSession(*this, 28);
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_(new TSessData(fnOnReturn_));
	_pSessionMgr->StoreData(dwSessionID_, pSessData_);
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 46;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwUserID << dwTaskID << byStep << byOpt;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 12, Function: 46";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterCommSvr::SendSvr_GetTaskStateForPlatfrom(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwUserID, //用户ID
	UINT32 dwTaskID, //邮件标题
	UINT8 byStep, //邮件正文
	UINT8 byOpt, //邮件正文
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		NPHPProt::ETaskState eRet //(返回值)返回的数据
	)> fnOnReturn_ //返回时的回调函数
)
{
	if(_pSessionMgr == NULL)
	{
		LOG_CRI << "_pSessionMgr == NULL";		return false;
	}
	UINT32 dwSessionID_ = _pSessionMgr->GetNewSession(*this, 28);
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_(new TSessData(fnOnReturn_));
	_pSessionMgr->StoreData(dwSessionID_, pSessData_);
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 46;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwUserID << dwTaskID << byStep << byOpt;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 12, Function: 46";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

//发送：同步微信微博人数
bool CGame2CenterCommSvr::Send_SynWeiweiPersonNum(
	UINT64 qwUserID, //玩家ID
	UINT8 byType, //类型
	UINT32 dwCount //人数
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 47;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUserID << byType << dwCount;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 12, Function: 47";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterCommSvr::SendSvr_SynWeiweiPersonNum(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwUserID, //玩家ID
	UINT8 byType, //类型
	UINT32 dwCount //人数
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 47;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUserID << byType << dwCount;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 12, Function: 47";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGame2CenterCommSvr::BuildPkg_SynWeiweiPersonNum(
	UINT64 qwUserID, //玩家ID
	UINT8 byType, //类型
	UINT32 dwCount //人数
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 47;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUserID << byType << dwCount;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 12, Function: 47";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：检测CDK
bool CGame2CenterCommSvr::Send_CheckCDK(
	UINT64 qwUserID, //玩家ID
	const std::string& strCDK //CDK码
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 48;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUserID << strCDK;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 12, Function: 48";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterCommSvr::SendSvr_CheckCDK(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwUserID, //玩家ID
	const std::string& strCDK //CDK码
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 48;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUserID << strCDK;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 12, Function: 48";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGame2CenterCommSvr::BuildPkg_CheckCDK(
	UINT64 qwUserID, //玩家ID
	const std::string& strCDK //CDK码
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 48;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUserID << strCDK;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 12, Function: 48";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：QQAlarm安装
bool CGame2CenterCommSvr::Send_SynQQAlarm(
	UINT64 qwUserID //玩家ID
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 49;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUserID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 12, Function: 49";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterCommSvr::SendSvr_SynQQAlarm(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwUserID //玩家ID
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 49;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUserID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 12, Function: 49";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGame2CenterCommSvr::BuildPkg_SynQQAlarm(
	UINT64 qwUserID //玩家ID
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 49;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUserID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 12, Function: 49";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：运营修改宝箱信息
bool CGame2CenterCommSvr::Send_ModifyChest(
	const NPHPProt::SChestInfo& sChestInfo //信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 50;
	try
	{
		ar << byProtID_ << byFuncID_ << sChestInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 12, Function: 50";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterCommSvr::SendSvr_ModifyChest(const UINT32* pSvrID_, UINT8 byCnt_,
	const NPHPProt::SChestInfo& sChestInfo //信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 50;
	try
	{
		ar << byProtID_ << byFuncID_ << sChestInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 12, Function: 50";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGame2CenterCommSvr::BuildPkg_ModifyChest(
	const NPHPProt::SChestInfo& sChestInfo //信息
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 50;
	try
	{
		ar << byProtID_ << byFuncID_ << sChestInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 12, Function: 50";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：Center2Game活动时间同步
bool CGame2CenterCommSvr::Send_SyncActivityTime(
	const NProtoCommon::SActivityTime& sActTime //信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 51;
	try
	{
		ar << byProtID_ << byFuncID_ << sActTime;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 12, Function: 51";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterCommSvr::SendSvr_SyncActivityTime(const UINT32* pSvrID_, UINT8 byCnt_,
	const NProtoCommon::SActivityTime& sActTime //信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 51;
	try
	{
		ar << byProtID_ << byFuncID_ << sActTime;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 12, Function: 51";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGame2CenterCommSvr::BuildPkg_SyncActivityTime(
	const NProtoCommon::SActivityTime& sActTime //信息
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 51;
	try
	{
		ar << byProtID_ << byFuncID_ << sActTime;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 12, Function: 51";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：请求累计登入天数
bool CGame2CenterCommSvr::Send_GetLoginDays(
	UINT64 qwUserID, //玩家ID
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT32 dwDays //(返回值)天数
	)> fnOnReturn_ //返回时的回调函数
)
{
	if(_pSessionMgr == NULL)
	{
		LOG_CRI << "_pSessionMgr == NULL";		return false;
	}
	UINT32 dwSessionID_ = _pSessionMgr->GetNewSession(*this, 29);
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_(new TSessData(fnOnReturn_));
	_pSessionMgr->StoreData(dwSessionID_, pSessData_);
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 52;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwUserID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 12, Function: 52";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterCommSvr::SendSvr_GetLoginDays(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwUserID, //玩家ID
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT32 dwDays //(返回值)天数
	)> fnOnReturn_ //返回时的回调函数
)
{
	if(_pSessionMgr == NULL)
	{
		LOG_CRI << "_pSessionMgr == NULL";		return false;
	}
	UINT32 dwSessionID_ = _pSessionMgr->GetNewSession(*this, 29);
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_(new TSessData(fnOnReturn_));
	_pSessionMgr->StoreData(dwSessionID_, pSessData_);
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 52;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwUserID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 12, Function: 52";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

//发送：同步活动状态
bool CGame2CenterCommSvr::Send_SyncActState(
	const SActivityState& oInfo, //数据
	bool bNotify //是否通知全服
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 53;
	try
	{
		ar << byProtID_ << byFuncID_ << oInfo << bNotify;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 12, Function: 53";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterCommSvr::SendSvr_SyncActState(const UINT32* pSvrID_, UINT8 byCnt_,
	const SActivityState& oInfo, //数据
	bool bNotify //是否通知全服
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 53;
	try
	{
		ar << byProtID_ << byFuncID_ << oInfo << bNotify;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 12, Function: 53";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGame2CenterCommSvr::BuildPkg_SyncActState(
	const SActivityState& oInfo, //数据
	bool bNotify //是否通知全服
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 53;
	try
	{
		ar << byProtID_ << byFuncID_ << oInfo << bNotify;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 12, Function: 53";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：添加Title
bool CGame2CenterCommSvr::Send_SyncTitle(
	UINT64 qwUserID, //玩家ID
	UINT16 wTitleID //添加Title
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 54;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUserID << wTitleID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 12, Function: 54";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterCommSvr::SendSvr_SyncTitle(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwUserID, //玩家ID
	UINT16 wTitleID //添加Title
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 54;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUserID << wTitleID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 12, Function: 54";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGame2CenterCommSvr::BuildPkg_SyncTitle(
	UINT64 qwUserID, //玩家ID
	UINT16 wTitleID //添加Title
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 54;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUserID << wTitleID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 12, Function: 54";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：扣除礼卷钻石
bool CGame2CenterCommSvr::Send_SubGoldOrCoupon(
	UINT64 qwUsrID, //帐号ID
	NLogDataDefine::ItemTo eItemTo, //道具or资源消耗类型
	UINT32 dwCount, //扣款数量
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT8 byError //(返回值)0 成功, 其他错误
	)> fnOnReturn_ //返回时的回调函数
)
{
	if(_pSessionMgr == NULL)
	{
		LOG_CRI << "_pSessionMgr == NULL";		return false;
	}
	UINT32 dwSessionID_ = _pSessionMgr->GetNewSession(*this, 30);
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_(new TSessData(fnOnReturn_));
	_pSessionMgr->StoreData(dwSessionID_, pSessData_);
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 55;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwUsrID << (UINT16&)eItemTo << dwCount;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 12, Function: 55";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2CenterCommSvr::SendSvr_SubGoldOrCoupon(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwUsrID, //帐号ID
	NLogDataDefine::ItemTo eItemTo, //道具or资源消耗类型
	UINT32 dwCount, //扣款数量
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT8 byError //(返回值)0 成功, 其他错误
	)> fnOnReturn_ //返回时的回调函数
)
{
	if(_pSessionMgr == NULL)
	{
		LOG_CRI << "_pSessionMgr == NULL";		return false;
	}
	UINT32 dwSessionID_ = _pSessionMgr->GetNewSession(*this, 30);
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_(new TSessData(fnOnReturn_));
	_pSessionMgr->StoreData(dwSessionID_, pSessData_);
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 55;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwUsrID << (UINT16&)eItemTo << dwCount;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 12, Function: 55";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

bool CGame2CenterCommSvr::_DoRecv_KeepAlive(const char* pBuf_, UINT32 dwLen_)
{
	OnRecv_KeepAlive();
	return true;
}

bool CGame2CenterCommSvr::_DoRecv_GameSvrInitNft(const char* pBuf_, UINT32 dwLen_)
{
	OnRecv_GameSvrInitNft();
	return true;
}

CGame2CenterCommSvr::SGetCenterStateAck::SGetCenterStateAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID) { }

void CGame2CenterCommSvr::SGetCenterStateAck::SendReturn(bool bRet_)
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

bool CGame2CenterCommSvr::_DoRecv_GetCenterState(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 12, Function: 3";
		return false;
	}
	shared_func<SGetCenterStateAck> fnAck_(new SGetCenterStateAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetCenterState(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

bool CGame2CenterCommSvr::_DoRecv_GameSvrDataSyncReq(const char* pBuf_, UINT32 dwLen_)
{
	ESyncKey eSyncKey = (ESyncKey)0;
	UINT16 wDestGroup = 0;
	UINT8 byDestIndex = 0;
	TVecINT32 vecParam;
	std::string strSyncData;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> (UINT8&)eSyncKey >> wDestGroup >> byDestIndex >> vecParam >> strSyncData;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 12, Function: 4";
		return false;
	}
	OnRecv_GameSvrDataSyncReq(eSyncKey, wDestGroup, byDestIndex, vecParam, strSyncData);
	return true;
}

bool CGame2CenterCommSvr::_DoRecv_UserLoginNtf(const char* pBuf_, UINT32 dwLen_)
{
	UINT64 qwUsrID = 0;
	SUserEnterInfo rUserInfo;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> qwUsrID >> rUserInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 12, Function: 5";
		return false;
	}
	OnRecv_UserLoginNtf(qwUsrID, rUserInfo);
	return true;
}

bool CGame2CenterCommSvr::_DoRecv_UserLogoutNtf(const char* pBuf_, UINT32 dwLen_)
{
	UINT64 qwUsrID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> qwUsrID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 12, Function: 6";
		return false;
	}
	OnRecv_UserLogoutNtf(qwUsrID);
	return true;
}

bool CGame2CenterCommSvr::_DoRecv_UserReplaceNtf(const char* pBuf_, UINT32 dwLen_)
{
	UINT64 qwUsrID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> qwUsrID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 12, Function: 7";
		return false;
	}
	OnRecv_UserReplaceNtf(qwUsrID);
	return true;
}

bool CGame2CenterCommSvr::_DoRecv_UserJumpSvrNtf(const char* pBuf_, UINT32 dwLen_)
{
	UINT64 qwUsrID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> qwUsrID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 12, Function: 8";
		return false;
	}
	OnRecv_UserJumpSvrNtf(qwUsrID);
	return true;
}

bool CGame2CenterCommSvr::_DoRecv_UserSyncPropNtf(const char* pBuf_, UINT32 dwLen_)
{
	UINT64 qwUsrID = 0;
	EUserSyncPropField eField = (EUserSyncPropField)0;
	std::string strVal;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> qwUsrID >> (UINT8&)eField >> strVal;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 12, Function: 9";
		return false;
	}
	OnRecv_UserSyncPropNtf(qwUsrID, eField, strVal);
	return true;
}

CGame2CenterCommSvr::SIsFriendAck::SIsFriendAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID), 
			byRet(0) { }

void CGame2CenterCommSvr::SIsFriendAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -2;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << byRet;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 12, Function: 10";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CGame2CenterCommSvr::_DoRecv_IsFriend(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT64 qwUsrID = 0;
	UINT64 qwFriID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> qwUsrID >> qwFriID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 12, Function: 10";
		return false;
	}
	shared_func<SIsFriendAck> fnAck_(new SIsFriendAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_IsFriend(qwUsrID, qwFriID, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CGame2CenterCommSvr::SIsSameGuildAck::SIsSameGuildAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID), 
			byRet(0) { }

void CGame2CenterCommSvr::SIsSameGuildAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -3;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << byRet;
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

bool CGame2CenterCommSvr::_DoRecv_IsSameGuild(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT64 qwUsrID = 0;
	UINT64 qwOtherID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> qwUsrID >> qwOtherID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 12, Function: 11";
		return false;
	}
	shared_func<SIsSameGuildAck> fnAck_(new SIsSameGuildAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_IsSameGuild(qwUsrID, qwOtherID, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

bool CGame2CenterCommSvr::_DoRecv_SendMail(const char* pBuf_, UINT32 dwLen_)
{
	std::string strSender;
	std::string strTitle;
	NMailProt::SysMailSendTxt strMsgInfo;
	NMailProt::TVecMailAttachment vecItemInfo;
	TVecUINT64 vecTargetIDs;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> strSender >> strTitle >> strMsgInfo >> vecItemInfo >> vecTargetIDs;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 12, Function: 12";
		return false;
	}
	OnRecv_SendMail(strSender, strTitle, strMsgInfo, vecItemInfo, vecTargetIDs);
	return true;
}

CGame2CenterCommSvr::SGetGuildIDAck::SGetGuildIDAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID), 
			qwGuildID(0), byGuildLvl(0) { }

void CGame2CenterCommSvr::SGetGuildIDAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -4;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << qwGuildID << strGuildName << byGuildLvl << strGuildOwnerName;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 12, Function: 13";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CGame2CenterCommSvr::_DoRecv_GetGuildID(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 12, Function: 13";
		return false;
	}
	shared_func<SGetGuildIDAck> fnAck_(new SGetGuildIDAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetGuildID(qwRoleID, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CGame2CenterCommSvr::SGetGuildNameAck::SGetGuildNameAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID), 
			bValid(false), qwGuildID(0), byGuildLvl(0) { }

void CGame2CenterCommSvr::SGetGuildNameAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -5;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << bValid << qwGuildID << strGuildName << byGuildLvl << strGuildOwnerName;
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

bool CGame2CenterCommSvr::_DoRecv_GetGuildName(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT64 qwGuildID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> qwGuildID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 12, Function: 14";
		return false;
	}
	shared_func<SGetGuildNameAck> fnAck_(new SGetGuildNameAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetGuildName(qwGuildID, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

bool CGame2CenterCommSvr::_DoRecv_NotifyGuildInfo(const char* pBuf_, UINT32 dwLen_)
{
	UINT64 qwGuildID = 0;
	TVecUINT64 vecExcpRoleID;
	std::string strData;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> qwGuildID >> vecExcpRoleID >> strData;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 12, Function: 15";
		return false;
	}
	OnRecv_NotifyGuildInfo(qwGuildID, vecExcpRoleID, strData);
	return true;
}

bool CGame2CenterCommSvr::_DoRecv_SynIconAppear(const char* pBuf_, UINT32 dwLen_)
{
	UINT64 qwRoleID = 0;
	std::string szIcon;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> qwRoleID >> szIcon;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 12, Function: 16";
		return false;
	}
	OnRecv_SynIconAppear(qwRoleID, szIcon);
	return true;
}

bool CGame2CenterCommSvr::_DoRecv_AddGuildContribution(const char* pBuf_, UINT32 dwLen_)
{
	UINT64 qwRoleID = 0;
	UINT32 dwContribution = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> qwRoleID >> dwContribution;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 12, Function: 17";
		return false;
	}
	OnRecv_AddGuildContribution(qwRoleID, dwContribution);
	return true;
}

bool CGame2CenterCommSvr::_DoRecv_ActiveTripodFire(const char* pBuf_, UINT32 dwLen_)
{
	UINT64 qwRoleID = 0;
	UINT16 wFireID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> qwRoleID >> wFireID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 12, Function: 18";
		return false;
	}
	OnRecv_ActiveTripodFire(qwRoleID, wFireID);
	return true;
}

bool CGame2CenterCommSvr::_DoRecv_UpdatePlatformParam(const char* pBuf_, UINT32 dwLen_)
{
	UINT64 qwRoleID = 0;
	NProtoCommon::TVecPlatformParam vecPlatform;
	UINT32 dwIndex = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> qwRoleID >> vecPlatform >> dwIndex;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 12, Function: 19";
		return false;
	}
	OnRecv_UpdatePlatformParam(qwRoleID, vecPlatform, dwIndex);
	return true;
}

bool CGame2CenterCommSvr::_DoRecv_UpdateEnterString(const char* pBuf_, UINT32 dwLen_)
{
	UINT64 qwRoleID = 0;
	TVecString vecEnterString;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> qwRoleID >> vecEnterString;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 12, Function: 20";
		return false;
	}
	OnRecv_UpdateEnterString(qwRoleID, vecEnterString);
	return true;
}

bool CGame2CenterCommSvr::_DoRecv_SendWonderType(const char* pBuf_, UINT32 dwLen_)
{
	EWonderActType eActType = (EWonderActType)0;
	UINT64 qwRoleID = 0;
	UINT32 dwCond = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> (UINT8&)eActType >> qwRoleID >> dwCond;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 12, Function: 21";
		return false;
	}
	OnRecv_SendWonderType(eActType, qwRoleID, dwCond);
	return true;
}

CGame2CenterCommSvr::SSubGuildContributionAck::SSubGuildContributionAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID), 
			eResult((NGuildProt::EGuildResult)0) { }

void CGame2CenterCommSvr::SSubGuildContributionAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -6;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 12, Function: 22";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CGame2CenterCommSvr::_DoRecv_SubGuildContribution(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT64 qwRoleID = 0;
	UINT32 dwContribution = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> qwRoleID >> dwContribution;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 12, Function: 22";
		return false;
	}
	shared_func<SSubGuildContributionAck> fnAck_(new SSubGuildContributionAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_SubGuildContribution(qwRoleID, dwContribution, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

bool CGame2CenterCommSvr::_DoRecv_BeautyLotteryLog(const char* pBuf_, UINT32 dwLen_)
{
	NBeautyLogGS::SBeautyLog oBeautyLog;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> oBeautyLog;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 12, Function: 23";
		return false;
	}
	OnRecv_BeautyLotteryLog(oBeautyLog);
	return true;
}

bool CGame2CenterCommSvr::_DoRecv_InviteFriend(const char* pBuf_, UINT32 dwLen_)
{
	UINT64 qwUserID = 0;
	UINT64 qwInvitedUserID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> qwUserID >> qwInvitedUserID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 12, Function: 24";
		return false;
	}
	OnRecv_InviteFriend(qwUserID, qwInvitedUserID);
	return true;
}

bool CGame2CenterCommSvr::_DoRecv_NotifyGuildExchangedItemBegin(const char* pBuf_, UINT32 dwLen_)
{
	TVecLingShanShopData vecLingShanShopData;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> vecLingShanShopData;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 12, Function: 25";
		return false;
	}
	OnRecv_NotifyGuildExchangedItemBegin(vecLingShanShopData);
	return true;
}

bool CGame2CenterCommSvr::_DoRecv_SyncGameBuffUseInCenter(const char* pBuf_, UINT32 dwLen_)
{
	UINT64 qwRoleID = 0;
	UINT16 wBuffID = 0;
	UINT32 dwEndTime = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> qwRoleID >> wBuffID >> dwEndTime;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 12, Function: 26";
		return false;
	}
	OnRecv_SyncGameBuffUseInCenter(qwRoleID, wBuffID, dwEndTime);
	return true;
}

bool CGame2CenterCommSvr::_DoRecv_SyncGameActiveParam(const char* pBuf_, UINT32 dwLen_)
{
	ActiveParam eParam = (ActiveParam)0;
	TVecUINT32 vecParam;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> (UINT8&)eParam >> vecParam;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 12, Function: 27";
		return false;
	}
	OnRecv_SyncGameActiveParam(eParam, vecParam);
	return true;
}

CGame2CenterCommSvr::SGetSystemVarAck::SGetSystemVarAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID) { }

void CGame2CenterCommSvr::SGetSystemVarAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -7;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << vecVars << vecValues;
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

bool CGame2CenterCommSvr::_DoRecv_GetSystemVar(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	TVecUINT16 vecVarID;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> vecVarID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 12, Function: 28";
		return false;
	}
	shared_func<SGetSystemVarAck> fnAck_(new SGetSystemVarAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetSystemVar(vecVarID, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CGame2CenterCommSvr::SSetSystemVarAck::SSetSystemVarAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID) { }

void CGame2CenterCommSvr::SSetSystemVarAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -8;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << vecVarID;
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

bool CGame2CenterCommSvr::_DoRecv_SetSystemVar(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	TVecUINT16 vecVars;
	TVecUINT64 vecValues;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> vecVars >> vecValues;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 12, Function: 29";
		return false;
	}
	shared_func<SSetSystemVarAck> fnAck_(new SSetSystemVarAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_SetSystemVar(vecVars, vecValues, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

bool CGame2CenterCommSvr::_DoReturn_ReplaceUser(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoReturn exception: " << szExcept << ", Protocol: 12, Function: 1";
		return false;
	}
	UINT8 byRet_ = 0;
	if(!bRet_)
		byRet_ = 1;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT64 qwUsrID //(本地保存的函数参数)帐号ID
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_), UINT64> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID_));
	if(pSessData_ == NULL)
		return false;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(byRet_, std::get<1>(*pSessData_));
	if(_pSessionMgr != NULL)
		_pSessionMgr->DelSession(dwSessionID_);
	return true;
}

void CGame2CenterCommSvr::_OnTimeOut_ReplaceUser(UINT32 dwSessionID)
{
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT64 qwUsrID //(本地保存的函数参数)帐号ID
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_), UINT64> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID));
	if(pSessData_ == NULL)
		return;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(2, std::get<1>(*pSessData_));
}

bool CGame2CenterCommSvr::_DoReturn_GMCmd(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoReturn exception: " << szExcept << ", Protocol: 12, Function: 2";
		return false;
	}
	UINT8 byRet_ = 0;
	if(!bRet_)
		byRet_ = 1;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT64 qwUsrID //(本地保存的函数参数)帐号ID
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_), UINT64> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID_));
	if(pSessData_ == NULL)
		return false;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(byRet_, std::get<1>(*pSessData_));
	if(_pSessionMgr != NULL)
		_pSessionMgr->DelSession(dwSessionID_);
	return true;
}

void CGame2CenterCommSvr::_OnTimeOut_GMCmd(UINT32 dwSessionID)
{
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT64 qwUsrID //(本地保存的函数参数)帐号ID
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_), UINT64> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID));
	if(pSessData_ == NULL)
		return;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(2, std::get<1>(*pSessData_));
}

bool CGame2CenterCommSvr::_DoReturn_AddTotalRecharge(const char* pBuf_, UINT32 dwLen_)
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

void CGame2CenterCommSvr::_OnTimeOut_AddTotalRecharge(UINT32 dwSessionID)
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

bool CGame2CenterCommSvr::_DoReturn_AddRechargeMailItem(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoReturn exception: " << szExcept << ", Protocol: 12, Function: 4";
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

void CGame2CenterCommSvr::_OnTimeOut_AddRechargeMailItem(UINT32 dwSessionID)
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

bool CGame2CenterCommSvr::_DoReturn_AddTotalPrepaid(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoReturn exception: " << szExcept << ", Protocol: 12, Function: 5";
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

void CGame2CenterCommSvr::_OnTimeOut_AddTotalPrepaid(UINT32 dwSessionID)
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

bool CGame2CenterCommSvr::_DoReturn_AddQQCoinBuyItem(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoReturn exception: " << szExcept << ", Protocol: 12, Function: 6";
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

void CGame2CenterCommSvr::_OnTimeOut_AddQQCoinBuyItem(UINT32 dwSessionID)
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

bool CGame2CenterCommSvr::_DoReturn_CheckMailAttch(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	bool bRet_ = false;
	UINT8 byCan = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> bRet_ >> byCan;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoReturn exception: " << szExcept << ", Protocol: 12, Function: 7";
		return false;
	}
	UINT8 byRet_ = 0;
	if(!bRet_)
		byRet_ = 1;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT8 byCan //(返回值)0表示可以提取
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID_));
	if(pSessData_ == NULL)
		return false;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(byRet_, byCan);
	if(_pSessionMgr != NULL)
		_pSessionMgr->DelSession(dwSessionID_);
	return true;
}

void CGame2CenterCommSvr::_OnTimeOut_CheckMailAttch(UINT32 dwSessionID)
{
	UINT8 byCan = 0;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT8 byCan //(返回值)0表示可以提取
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID));
	if(pSessData_ == NULL)
		return;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(2, byCan);
}

bool CGame2CenterCommSvr::_DoReturn_FigtherToOther(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	bool bRet_ = false;
	UINT8 byRet = 0;
	UINT8 bySuc = 0;
	UINT64 qwBattleID = 0;
	UINT32 dwSelfFighterPower = 0;
	UINT8 bySelfQuality = 0;
	UINT32 dwOtherFighterPower = 0;
	UINT8 byOtherQuality = 0;
	UINT32 dwTurns = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> bRet_ >> byRet >> bySuc >> qwBattleID >> dwSelfFighterPower >> bySelfQuality >> dwOtherFighterPower >> byOtherQuality >> dwTurns;
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
		UINT8 byRet, //(返回值)请求结果
		UINT8 bySuc, //(返回值)是否胜利
		UINT64 qwBattleID, //(返回值)战报ID
		UINT32 dwSelfFighterPower, //(返回值)自己的战斗力
		UINT8 bySelfQuality, //(返回值)自己的主将品质
		UINT32 dwOtherFighterPower, //(返回值)他人的战斗力
		UINT8 byOtherQuality, //(返回值)他人的主将品质
		UINT32 dwTurns //(返回值)战斗回合数
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID_));
	if(pSessData_ == NULL)
		return false;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(byRet_, byRet, bySuc, qwBattleID, dwSelfFighterPower, bySelfQuality, dwOtherFighterPower, byOtherQuality, dwTurns);
	if(_pSessionMgr != NULL)
		_pSessionMgr->DelSession(dwSessionID_);
	return true;
}

void CGame2CenterCommSvr::_OnTimeOut_FigtherToOther(UINT32 dwSessionID)
{
	UINT8 byRet = 0;
	UINT8 bySuc = 0;
	UINT64 qwBattleID = 0;
	UINT32 dwSelfFighterPower = 0;
	UINT8 bySelfQuality = 0;
	UINT32 dwOtherFighterPower = 0;
	UINT8 byOtherQuality = 0;
	UINT32 dwTurns = 0;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT8 byRet, //(返回值)请求结果
		UINT8 bySuc, //(返回值)是否胜利
		UINT64 qwBattleID, //(返回值)战报ID
		UINT32 dwSelfFighterPower, //(返回值)自己的战斗力
		UINT8 bySelfQuality, //(返回值)自己的主将品质
		UINT32 dwOtherFighterPower, //(返回值)他人的战斗力
		UINT8 byOtherQuality, //(返回值)他人的主将品质
		UINT32 dwTurns //(返回值)战斗回合数
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID));
	if(pSessData_ == NULL)
		return;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(2, byRet, bySuc, qwBattleID, dwSelfFighterPower, bySelfQuality, dwOtherFighterPower, byOtherQuality, dwTurns);
}

bool CGame2CenterCommSvr::_DoReturn_CanPushLoot(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoReturn exception: " << szExcept << ", Protocol: 12, Function: 12";
		return false;
	}
	UINT8 byRet_ = 0;
	if(!bRet_)
		byRet_ = 1;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT8 byRet //(返回值)0,可以，1，没有这个掉落，2，其他错误
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

void CGame2CenterCommSvr::_OnTimeOut_CanPushLoot(UINT32 dwSessionID)
{
	UINT8 byRet = 0;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT8 byRet //(返回值)0,可以，1，没有这个掉落，2，其他错误
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

bool CGame2CenterCommSvr::_DoReturn_ReduceItem(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoReturn exception: " << szExcept << ", Protocol: 12, Function: 14";
		return false;
	}
	UINT8 byRet_ = 0;
	if(!bRet_)
		byRet_ = 1;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT8 byRet //(返回值)0,可以,1，不足，2，其他错误
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

void CGame2CenterCommSvr::_OnTimeOut_ReduceItem(UINT32 dwSessionID)
{
	UINT8 byRet = 0;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT8 byRet //(返回值)0,可以,1，不足，2，其他错误
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

bool CGame2CenterCommSvr::_DoReturn_CanReduceItem(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoReturn exception: " << szExcept << ", Protocol: 12, Function: 15";
		return false;
	}
	UINT8 byRet_ = 0;
	if(!bRet_)
		byRet_ = 1;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT8 byRet //(返回值)0,可以,1，不足，2，其他错误
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

void CGame2CenterCommSvr::_OnTimeOut_CanReduceItem(UINT32 dwSessionID)
{
	UINT8 byRet = 0;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT8 byRet //(返回值)0,可以,1，不足，2，其他错误
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

bool CGame2CenterCommSvr::_DoReturn_GetUserUINTProp(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	bool bRet_ = false;
	UINT32 dwValue = 0;
	UINT8 byError = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> bRet_ >> dwValue >> byError;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoReturn exception: " << szExcept << ", Protocol: 12, Function: 16";
		return false;
	}
	UINT8 byRet_ = 0;
	if(!bRet_)
		byRet_ = 1;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT32 dwValue, //(返回值)属性值
		UINT8 byError //(返回值)0 成功, 其他错误
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID_));
	if(pSessData_ == NULL)
		return false;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(byRet_, dwValue, byError);
	if(_pSessionMgr != NULL)
		_pSessionMgr->DelSession(dwSessionID_);
	return true;
}

void CGame2CenterCommSvr::_OnTimeOut_GetUserUINTProp(UINT32 dwSessionID)
{
	UINT32 dwValue = 0;
	UINT8 byError = 0;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT32 dwValue, //(返回值)属性值
		UINT8 byError //(返回值)0 成功, 其他错误
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID));
	if(pSessData_ == NULL)
		return;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(2, dwValue, byError);
}

bool CGame2CenterCommSvr::_DoReturn_SetUserUINTProp(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	bool bRet_ = false;
	UINT8 byError = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> bRet_ >> byError;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoReturn exception: " << szExcept << ", Protocol: 12, Function: 17";
		return false;
	}
	UINT8 byRet_ = 0;
	if(!bRet_)
		byRet_ = 1;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT8 byError //(返回值)0 成功, 其他错误
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID_));
	if(pSessData_ == NULL)
		return false;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(byRet_, byError);
	if(_pSessionMgr != NULL)
		_pSessionMgr->DelSession(dwSessionID_);
	return true;
}

void CGame2CenterCommSvr::_OnTimeOut_SetUserUINTProp(UINT32 dwSessionID)
{
	UINT8 byError = 0;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT8 byError //(返回值)0 成功, 其他错误
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID));
	if(pSessData_ == NULL)
		return;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(2, byError);
}

bool CGame2CenterCommSvr::_DoReturn_UserSubItem(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	bool bRet_ = false;
	UINT8 byError = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> bRet_ >> byError;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoReturn exception: " << szExcept << ", Protocol: 12, Function: 18";
		return false;
	}
	UINT8 byRet_ = 0;
	if(!bRet_)
		byRet_ = 1;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT8 byError //(返回值)0 成功, 其他错误
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID_));
	if(pSessData_ == NULL)
		return false;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(byRet_, byError);
	if(_pSessionMgr != NULL)
		_pSessionMgr->DelSession(dwSessionID_);
	return true;
}

void CGame2CenterCommSvr::_OnTimeOut_UserSubItem(UINT32 dwSessionID)
{
	UINT8 byError = 0;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT8 byError //(返回值)0 成功, 其他错误
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID));
	if(pSessData_ == NULL)
		return;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(2, byError);
}

bool CGame2CenterCommSvr::_DoReturn_UserAddItem(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	bool bRet_ = false;
	UINT8 byError = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> bRet_ >> byError;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoReturn exception: " << szExcept << ", Protocol: 12, Function: 19";
		return false;
	}
	UINT8 byRet_ = 0;
	if(!bRet_)
		byRet_ = 1;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT8 byError //(返回值)0 成功, 其他错误
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID_));
	if(pSessData_ == NULL)
		return false;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(byRet_, byError);
	if(_pSessionMgr != NULL)
		_pSessionMgr->DelSession(dwSessionID_);
	return true;
}

void CGame2CenterCommSvr::_OnTimeOut_UserAddItem(UINT32 dwSessionID)
{
	UINT8 byError = 0;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT8 byError //(返回值)0 成功, 其他错误
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID));
	if(pSessData_ == NULL)
		return;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(2, byError);
}

bool CGame2CenterCommSvr::_DoReturn_ProcessCond(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	bool bRet_ = false;
	UINT8 byError = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> bRet_ >> byError;
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
		UINT8 byError //(返回值)0 成功, 1 其他错误
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID_));
	if(pSessData_ == NULL)
		return false;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(byRet_, byError);
	if(_pSessionMgr != NULL)
		_pSessionMgr->DelSession(dwSessionID_);
	return true;
}

void CGame2CenterCommSvr::_OnTimeOut_ProcessCond(UINT32 dwSessionID)
{
	UINT8 byError = 0;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT8 byError //(返回值)0 成功, 1 其他错误
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID));
	if(pSessData_ == NULL)
		return;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(2, byError);
}

bool CGame2CenterCommSvr::_DoReturn_UpgradeTripod(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	bool bRet_ = false;
	UINT8 byError = 0;
	UINT8 byLevel = 0;
	UINT32 dwExp = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> bRet_ >> byError >> byLevel >> dwExp;
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
		UINT8 byError, //(返回值)0 成功, 1 其他错误
		UINT8 byLevel, //(返回值)九疑鼎当前等级
		UINT32 dwExp //(返回值)九疑鼎当前经验值
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID_));
	if(pSessData_ == NULL)
		return false;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(byRet_, byError, byLevel, dwExp);
	if(_pSessionMgr != NULL)
		_pSessionMgr->DelSession(dwSessionID_);
	return true;
}

void CGame2CenterCommSvr::_OnTimeOut_UpgradeTripod(UINT32 dwSessionID)
{
	UINT8 byError = 0;
	UINT8 byLevel = 0;
	UINT32 dwExp = 0;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT8 byError, //(返回值)0 成功, 1 其他错误
		UINT8 byLevel, //(返回值)九疑鼎当前等级
		UINT32 dwExp //(返回值)九疑鼎当前经验值
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID));
	if(pSessData_ == NULL)
		return;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(2, byError, byLevel, dwExp);
}

bool CGame2CenterCommSvr::_DoReturn_SpeedTripod(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	bool bRet_ = false;
	UINT8 byError = 0;
	UINT32 dwSoul = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> bRet_ >> byError >> dwSoul;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoReturn exception: " << szExcept << ", Protocol: 12, Function: 30";
		return false;
	}
	UINT8 byRet_ = 0;
	if(!bRet_)
		byRet_ = 1;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT8 byError, //(返回值)0 成功, 1 其他错误
		UINT32 dwSoul //(返回值)九疑鼎增加的元气值
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID_));
	if(pSessData_ == NULL)
		return false;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(byRet_, byError, dwSoul);
	if(_pSessionMgr != NULL)
		_pSessionMgr->DelSession(dwSessionID_);
	return true;
}

void CGame2CenterCommSvr::_OnTimeOut_SpeedTripod(UINT32 dwSessionID)
{
	UINT8 byError = 0;
	UINT32 dwSoul = 0;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT8 byError, //(返回值)0 成功, 1 其他错误
		UINT32 dwSoul //(返回值)九疑鼎增加的元气值
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID));
	if(pSessData_ == NULL)
		return;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(2, byError, dwSoul);
}

bool CGame2CenterCommSvr::_DoReturn_CheckHasFighter(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	bool bRet_ = false;
	UINT8 byError = 0;
	UINT8 byColor = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> bRet_ >> byError >> byColor;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoReturn exception: " << szExcept << ", Protocol: 12, Function: 31";
		return false;
	}
	UINT8 byRet_ = 0;
	if(!bRet_)
		byRet_ = 1;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT8 byError, //(返回值)0 拥有, 1 其他错误
		UINT8 byColor //(返回值)散仙品质
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID_));
	if(pSessData_ == NULL)
		return false;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(byRet_, byError, byColor);
	if(_pSessionMgr != NULL)
		_pSessionMgr->DelSession(dwSessionID_);
	return true;
}

void CGame2CenterCommSvr::_OnTimeOut_CheckHasFighter(UINT32 dwSessionID)
{
	UINT8 byError = 0;
	UINT8 byColor = 0;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT8 byError, //(返回值)0 拥有, 1 其他错误
		UINT8 byColor //(返回值)散仙品质
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID));
	if(pSessData_ == NULL)
		return;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(2, byError, byColor);
}

bool CGame2CenterCommSvr::_DoReturn_GetBattlePoint(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	bool bRet_ = false;
	UINT8 byError = 0;
	UINT32 dwBattlePoint = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> bRet_ >> byError >> dwBattlePoint;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoReturn exception: " << szExcept << ", Protocol: 12, Function: 32";
		return false;
	}
	UINT8 byRet_ = 0;
	if(!bRet_)
		byRet_ = 1;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT8 byError, //(返回值)0 成功, 1 其他错误
		UINT32 dwBattlePoint //(返回值)玩家战斗力
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID_));
	if(pSessData_ == NULL)
		return false;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(byRet_, byError, dwBattlePoint);
	if(_pSessionMgr != NULL)
		_pSessionMgr->DelSession(dwSessionID_);
	return true;
}

void CGame2CenterCommSvr::_OnTimeOut_GetBattlePoint(UINT32 dwSessionID)
{
	UINT8 byError = 0;
	UINT32 dwBattlePoint = 0;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT8 byError, //(返回值)0 成功, 1 其他错误
		UINT32 dwBattlePoint //(返回值)玩家战斗力
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID));
	if(pSessData_ == NULL)
		return;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(2, byError, dwBattlePoint);
}

bool CGame2CenterCommSvr::_DoReturn_SubPlayerMoney(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoReturn exception: " << szExcept << ", Protocol: 12, Function: 38";
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

void CGame2CenterCommSvr::_OnTimeOut_SubPlayerMoney(UINT32 dwSessionID)
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

bool CGame2CenterCommSvr::_DoReturn_SetPlayerLevel(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoReturn exception: " << szExcept << ", Protocol: 12, Function: 39";
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

void CGame2CenterCommSvr::_OnTimeOut_SetPlayerLevel(UINT32 dwSessionID)
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

bool CGame2CenterCommSvr::_DoReturn_SetPlayerVIPLevel(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoReturn exception: " << szExcept << ", Protocol: 12, Function: 40";
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

void CGame2CenterCommSvr::_OnTimeOut_SetPlayerVIPLevel(UINT32 dwSessionID)
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

bool CGame2CenterCommSvr::_DoReturn_SetDayTask(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoReturn exception: " << szExcept << ", Protocol: 12, Function: 41";
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

void CGame2CenterCommSvr::_OnTimeOut_SetDayTask(UINT32 dwSessionID)
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

bool CGame2CenterCommSvr::_DoReturn_GetPlayerInfo(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	bool bRet_ = false;
	NPHPProt::SPlayerInfo sPlayerInfo;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> bRet_ >> sPlayerInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoReturn exception: " << szExcept << ", Protocol: 12, Function: 42";
		return false;
	}
	UINT8 byRet_ = 0;
	if(!bRet_)
		byRet_ = 1;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		const NPHPProt::SPlayerInfo& sPlayerInfo //(返回值)返回的数据
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID_));
	if(pSessData_ == NULL)
		return false;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(byRet_, sPlayerInfo);
	if(_pSessionMgr != NULL)
		_pSessionMgr->DelSession(dwSessionID_);
	return true;
}

void CGame2CenterCommSvr::_OnTimeOut_GetPlayerInfo(UINT32 dwSessionID)
{
	NPHPProt::SPlayerInfo sPlayerInfo;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		const NPHPProt::SPlayerInfo& sPlayerInfo //(返回值)返回的数据
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID));
	if(pSessData_ == NULL)
		return;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(2, sPlayerInfo);
}

bool CGame2CenterCommSvr::_DoReturn_GetPlayerBagInfo(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	bool bRet_ = false;
	NPHPProt::TVecPlayerBagInfo vecPlayerBagInfo;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> bRet_ >> vecPlayerBagInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoReturn exception: " << szExcept << ", Protocol: 12, Function: 43";
		return false;
	}
	UINT8 byRet_ = 0;
	if(!bRet_)
		byRet_ = 1;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		const NPHPProt::TVecPlayerBagInfo& vecPlayerBagInfo //(返回值)返回的数据
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID_));
	if(pSessData_ == NULL)
		return false;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(byRet_, vecPlayerBagInfo);
	if(_pSessionMgr != NULL)
		_pSessionMgr->DelSession(dwSessionID_);
	return true;
}

void CGame2CenterCommSvr::_OnTimeOut_GetPlayerBagInfo(UINT32 dwSessionID)
{
	NPHPProt::TVecPlayerBagInfo vecPlayerBagInfo;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		const NPHPProt::TVecPlayerBagInfo& vecPlayerBagInfo //(返回值)返回的数据
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID));
	if(pSessData_ == NULL)
		return;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(2, vecPlayerBagInfo);
}

bool CGame2CenterCommSvr::_DoReturn_DelPlayerItem(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoReturn exception: " << szExcept << ", Protocol: 12, Function: 44";
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

void CGame2CenterCommSvr::_OnTimeOut_DelPlayerItem(UINT32 dwSessionID)
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

bool CGame2CenterCommSvr::_DoReturn_GetTaskStateForPlatfrom(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	bool bRet_ = false;
	NPHPProt::ETaskState eRet = (NPHPProt::ETaskState)0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> bRet_ >> (UINT8&)eRet;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoReturn exception: " << szExcept << ", Protocol: 12, Function: 46";
		return false;
	}
	UINT8 byRet_ = 0;
	if(!bRet_)
		byRet_ = 1;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		NPHPProt::ETaskState eRet //(返回值)返回的数据
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID_));
	if(pSessData_ == NULL)
		return false;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(byRet_, eRet);
	if(_pSessionMgr != NULL)
		_pSessionMgr->DelSession(dwSessionID_);
	return true;
}

void CGame2CenterCommSvr::_OnTimeOut_GetTaskStateForPlatfrom(UINT32 dwSessionID)
{
	NPHPProt::ETaskState eRet = (NPHPProt::ETaskState)0;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		NPHPProt::ETaskState eRet //(返回值)返回的数据
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID));
	if(pSessData_ == NULL)
		return;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(2, eRet);
}

bool CGame2CenterCommSvr::_DoReturn_GetLoginDays(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	bool bRet_ = false;
	UINT32 dwDays = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> bRet_ >> dwDays;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoReturn exception: " << szExcept << ", Protocol: 12, Function: 52";
		return false;
	}
	UINT8 byRet_ = 0;
	if(!bRet_)
		byRet_ = 1;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT32 dwDays //(返回值)天数
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID_));
	if(pSessData_ == NULL)
		return false;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(byRet_, dwDays);
	if(_pSessionMgr != NULL)
		_pSessionMgr->DelSession(dwSessionID_);
	return true;
}

void CGame2CenterCommSvr::_OnTimeOut_GetLoginDays(UINT32 dwSessionID)
{
	UINT32 dwDays = 0;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT32 dwDays //(返回值)天数
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID));
	if(pSessData_ == NULL)
		return;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(2, dwDays);
}

bool CGame2CenterCommSvr::_DoReturn_SubGoldOrCoupon(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	bool bRet_ = false;
	UINT8 byError = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> bRet_ >> byError;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoReturn exception: " << szExcept << ", Protocol: 12, Function: 55";
		return false;
	}
	UINT8 byRet_ = 0;
	if(!bRet_)
		byRet_ = 1;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT8 byError //(返回值)0 成功, 其他错误
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID_));
	if(pSessData_ == NULL)
		return false;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(byRet_, byError);
	if(_pSessionMgr != NULL)
		_pSessionMgr->DelSession(dwSessionID_);
	return true;
}

void CGame2CenterCommSvr::_OnTimeOut_SubGoldOrCoupon(UINT32 dwSessionID)
{
	UINT8 byError = 0;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT8 byError //(返回值)0 成功, 其他错误
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID));
	if(pSessData_ == NULL)
		return;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(2, byError);
}

} //namespace NGame2CenterComm
