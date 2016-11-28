/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    MiscProt.cpp
//  Purpose:      不好归类的小协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "MiscProtSvr.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NMiscProt
{

CMiscProtSvr::THandleFunc CMiscProtSvr::_HandleFuncs[] =
{
	&CMiscProtSvr::_DoRecv_SetIndulge, //FuncID: 1
	&CMiscProtSvr::_DoRecv_SetIndulgeRate, //FuncID: 2
	&CMiscProtSvr::_DoRecv_BuyAction, //FuncID: 3
	&CMiscProtSvr::_DoRecv_GetBuyActionCount, //FuncID: 4
	&CMiscProtSvr::_DoRecv_GetActionBuff, //FuncID: 5
	&CMiscProtSvr::_DoRecv_SendUdpLog, //FuncID: 6
	&CMiscProtSvr::_DoRecv_GetMoneyList, //FuncID: 7
	&CMiscProtSvr::_DoRecv_TakeActionBuff, //FuncID: 8
	&CMiscProtSvr::_DoRecv_ClientBlankScreenLog, //FuncID: 9
	&CMiscProtSvr::_DoRecv_OnEnter, //FuncID: 10
	&CMiscProtSvr::_DoRecv_GetRount, //FuncID: 11
	&CMiscProtSvr::_DoRecv_Draw, //FuncID: 12
	&CMiscProtSvr::_DoRecv_DrawRet, //FuncID: 13
	&CMiscProtSvr::_DoRecv_SendLottery, //FuncID: 14
	&CMiscProtSvr::_DoRecv_GetEveryDayRechargeAward, //FuncID: 15
	&CMiscProtSvr::_DoRecv_GetEveryDayRecharge, //FuncID: 16
	&CMiscProtSvr::_DoRecv_BuyFenbaoyan, //FuncID: 17
	&CMiscProtSvr::_DoRecv_FenbaoyanTime, //FuncID: 18
};

bool CMiscProtSvr::HandleMessage(const char* pBuf, UINT32 dwLen)
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

//发送：聊天信息通知
bool CMiscProtSvr::Send_IndulgeTimeNotify(
	UINT32 dwIndulgeTime //防沉迷时间(秒)
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << dwIndulgeTime;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 72, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CMiscProtSvr::SendClt_IndulgeTimeNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT32 dwIndulgeTime //防沉迷时间(秒)
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << dwIndulgeTime;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 72, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CMiscProtSvr::BuildPkg_IndulgeTimeNotify(
	UINT32 dwIndulgeTime //防沉迷时间(秒)
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << dwIndulgeTime;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 72, Function: 1";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：聊天信息通知
bool CMiscProtSvr::Send_IndulgeNextLoginTime(
	UINT32 dwTime //可以登陆时间(秒)
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << dwTime;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 72, Function: 2";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CMiscProtSvr::SendClt_IndulgeNextLoginTime(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT32 dwTime //可以登陆时间(秒)
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << dwTime;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 72, Function: 2";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CMiscProtSvr::BuildPkg_IndulgeNextLoginTime(
	UINT32 dwTime //可以登陆时间(秒)
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << dwTime;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 72, Function: 2";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：Buffer中的体力
bool CMiscProtSvr::Send_GetActionBuffNotify(
	UINT32 dwValue, //Buffer中的体力
	UINT32 TakeTime //最近领取时间
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << dwValue << TakeTime;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 72, Function: 3";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CMiscProtSvr::SendClt_GetActionBuffNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT32 dwValue, //Buffer中的体力
	UINT32 TakeTime //最近领取时间
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << dwValue << TakeTime;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 72, Function: 3";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CMiscProtSvr::BuildPkg_GetActionBuffNotify(
	UINT32 dwValue, //Buffer中的体力
	UINT32 TakeTime //最近领取时间
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << dwValue << TakeTime;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 72, Function: 3";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：通知活动开始
bool CMiscProtSvr::Send_OnBegin(
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
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 72, Function: 4";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CMiscProtSvr::SendClt_OnBegin(const UINT64* pUsrID_, UINT16 wCnt_
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
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 72, Function: 4";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CMiscProtSvr::BuildPkg_OnBegin(
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
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 72, Function: 4";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：宝箱下一波公告
bool CMiscProtSvr::Send_SendNotice(
	UINT8 byRount, //剩余波数
	UINT8 byMaxRount //最大波数
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 5;
	try
	{
		ar << byProtID_ << byFuncID_ << byRount << byMaxRount;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 72, Function: 5";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CMiscProtSvr::SendClt_SendNotice(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT8 byRount, //剩余波数
	UINT8 byMaxRount //最大波数
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 5;
	try
	{
		ar << byProtID_ << byFuncID_ << byRount << byMaxRount;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 72, Function: 5";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CMiscProtSvr::BuildPkg_SendNotice(
	UINT8 byRount, //剩余波数
	UINT8 byMaxRount //最大波数
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 5;
	try
	{
		ar << byProtID_ << byFuncID_ << byRount << byMaxRount;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 72, Function: 5";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：通知倒计时
bool CMiscProtSvr::Send_OnCountDown(
	UINT32 dwTime //活动倒计时时间
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 6;
	try
	{
		ar << byProtID_ << byFuncID_ << dwTime;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 72, Function: 6";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CMiscProtSvr::SendClt_OnCountDown(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT32 dwTime //活动倒计时时间
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 6;
	try
	{
		ar << byProtID_ << byFuncID_ << dwTime;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 72, Function: 6";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CMiscProtSvr::BuildPkg_OnCountDown(
	UINT32 dwTime //活动倒计时时间
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 6;
	try
	{
		ar << byProtID_ << byFuncID_ << dwTime;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 72, Function: 6";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：通知活动结束
bool CMiscProtSvr::Send_OnEnd(
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 7;
	try
	{
		ar << byProtID_ << byFuncID_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 72, Function: 7";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CMiscProtSvr::SendClt_OnEnd(const UINT64* pUsrID_, UINT16 wCnt_
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 7;
	try
	{
		ar << byProtID_ << byFuncID_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 72, Function: 7";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CMiscProtSvr::BuildPkg_OnEnd(
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 7;
	try
	{
		ar << byProtID_ << byFuncID_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 72, Function: 7";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：通知宝箱活动剩余轮次
bool CMiscProtSvr::Send_SyncChestInfo(
	const SGodChestInfo& sInfo //宝箱信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 8;
	try
	{
		ar << byProtID_ << byFuncID_ << sInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 72, Function: 8";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CMiscProtSvr::SendClt_SyncChestInfo(const UINT64* pUsrID_, UINT16 wCnt_,
	const SGodChestInfo& sInfo //宝箱信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 8;
	try
	{
		ar << byProtID_ << byFuncID_ << sInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 72, Function: 8";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CMiscProtSvr::BuildPkg_SyncChestInfo(
	const SGodChestInfo& sInfo //宝箱信息
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 8;
	try
	{
		ar << byProtID_ << byFuncID_ << sInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 72, Function: 8";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：通知宝箱活动剩余轮次
bool CMiscProtSvr::Send_SyncLotteryInfo(
	UINT32 dwLottery, //抽奖券
	const TVecLotteryInfo& vecTotalInfo, //总的抽奖信息
	const TVecLotteryInfo& vecSelfInfo //自己抽奖信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 9;
	try
	{
		ar << byProtID_ << byFuncID_ << dwLottery << vecTotalInfo << vecSelfInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 72, Function: 9";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CMiscProtSvr::SendClt_SyncLotteryInfo(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT32 dwLottery, //抽奖券
	const TVecLotteryInfo& vecTotalInfo, //总的抽奖信息
	const TVecLotteryInfo& vecSelfInfo //自己抽奖信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 9;
	try
	{
		ar << byProtID_ << byFuncID_ << dwLottery << vecTotalInfo << vecSelfInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 72, Function: 9";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CMiscProtSvr::BuildPkg_SyncLotteryInfo(
	UINT32 dwLottery, //抽奖券
	const TVecLotteryInfo& vecTotalInfo, //总的抽奖信息
	const TVecLotteryInfo& vecSelfInfo //自己抽奖信息
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 9;
	try
	{
		ar << byProtID_ << byFuncID_ << dwLottery << vecTotalInfo << vecSelfInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 72, Function: 9";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：同步今日冲值仙石总数
bool CMiscProtSvr::Send_SyncRechargeToday(
	UINT32 dwTotalRechargeToday //仙石
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 10;
	try
	{
		ar << byProtID_ << byFuncID_ << dwTotalRechargeToday;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 72, Function: 10";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CMiscProtSvr::SendClt_SyncRechargeToday(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT32 dwTotalRechargeToday //仙石
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 10;
	try
	{
		ar << byProtID_ << byFuncID_ << dwTotalRechargeToday;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 72, Function: 10";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CMiscProtSvr::BuildPkg_SyncRechargeToday(
	UINT32 dwTotalRechargeToday //仙石
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 10;
	try
	{
		ar << byProtID_ << byFuncID_ << dwTotalRechargeToday;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 72, Function: 10";
		_strPkg.clear();
	}
	return _strPkg;
}

bool CMiscProtSvr::_DoRecv_SetIndulge(const char* pBuf_, UINT32 dwLen_)
{
	bool bIndulge = false;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> bIndulge;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 72, Function: 1";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	OnRecv_SetIndulge(bIndulge);
	return true;
}

bool CMiscProtSvr::_DoRecv_SetIndulgeRate(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwIndulgeRate = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwIndulgeRate;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 72, Function: 2";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	OnRecv_SetIndulgeRate(dwIndulgeRate);
	return true;
}

CMiscProtSvr::SBuyActionAck::SBuyActionAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			dwRet(0), dwCount(0), dwPrice(0) { }

void CMiscProtSvr::SBuyActionAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -1;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << dwRet << dwCount << dwPrice;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 72, Function: 3";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CMiscProtSvr::_DoRecv_BuyAction(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 72, Function: 3";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SBuyActionAck> fnAck_(new SBuyActionAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_BuyAction(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CMiscProtSvr::SGetBuyActionCountAck::SGetBuyActionCountAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			dwCount(0), dwPrice(0), dwAction(0) { }

void CMiscProtSvr::SGetBuyActionCountAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -2;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << dwCount << dwPrice << dwAction;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 72, Function: 4";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CMiscProtSvr::_DoRecv_GetBuyActionCount(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 72, Function: 4";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SGetBuyActionCountAck> fnAck_(new SGetBuyActionCountAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetBuyActionCount(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

bool CMiscProtSvr::_DoRecv_GetActionBuff(const char* pBuf_, UINT32 dwLen_)
{
	OnRecv_GetActionBuff();
	return true;
}

bool CMiscProtSvr::_DoRecv_SendUdpLog(const char* pBuf_, UINT32 dwLen_)
{
	std::string strParam1;
	std::string strParam2;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> strParam1 >> strParam2;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 72, Function: 6";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	OnRecv_SendUdpLog(strParam1, strParam2);
	return true;
}

CMiscProtSvr::SGetMoneyListAck::SGetMoneyListAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID) { }

void CMiscProtSvr::SGetMoneyListAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -3;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << vecMoneyCount;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 72, Function: 7";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CMiscProtSvr::_DoRecv_GetMoneyList(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 72, Function: 7";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SGetMoneyListAck> fnAck_(new SGetMoneyListAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetMoneyList(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

bool CMiscProtSvr::_DoRecv_TakeActionBuff(const char* pBuf_, UINT32 dwLen_)
{
	OnRecv_TakeActionBuff();
	return true;
}

bool CMiscProtSvr::_DoRecv_ClientBlankScreenLog(const char* pBuf_, UINT32 dwLen_)
{
	std::string strParam1;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> strParam1;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 72, Function: 9";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	OnRecv_ClientBlankScreenLog(strParam1);
	return true;
}

bool CMiscProtSvr::_DoRecv_OnEnter(const char* pBuf_, UINT32 dwLen_)
{
	OnRecv_OnEnter();
	return true;
}

bool CMiscProtSvr::_DoRecv_GetRount(const char* pBuf_, UINT32 dwLen_)
{
	OnRecv_GetRount();
	return true;
}

CMiscProtSvr::SDrawAck::SDrawAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			wLotteryID(0), eResult((ELotteryRes)0) { }

void CMiscProtSvr::SDrawAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -4;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << wLotteryID << (UINT8&)eResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 72, Function: 12";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CMiscProtSvr::_DoRecv_Draw(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 72, Function: 12";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SDrawAck> fnAck_(new SDrawAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_Draw(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

bool CMiscProtSvr::_DoRecv_DrawRet(const char* pBuf_, UINT32 dwLen_)
{
	OnRecv_DrawRet();
	return true;
}

bool CMiscProtSvr::_DoRecv_SendLottery(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwTotalNum = 0;
	UINT32 dwSelfNum = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwTotalNum >> dwSelfNum;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 72, Function: 14";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	OnRecv_SendLottery(dwTotalNum, dwSelfNum);
	return true;
}

CMiscProtSvr::SGetEveryDayRechargeAwardAck::SGetEveryDayRechargeAwardAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((EEveryDayReChargeAward)0) { }

void CMiscProtSvr::SGetEveryDayRechargeAwardAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -5;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 72, Function: 15";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CMiscProtSvr::_DoRecv_GetEveryDayRechargeAward(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 72, Function: 15";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SGetEveryDayRechargeAwardAck> fnAck_(new SGetEveryDayRechargeAwardAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetEveryDayRechargeAward(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CMiscProtSvr::SGetEveryDayRechargeAck::SGetEveryDayRechargeAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			dwTotalRechargeToday(0) { }

void CMiscProtSvr::SGetEveryDayRechargeAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -6;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << dwTotalRechargeToday;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 72, Function: 16";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CMiscProtSvr::_DoRecv_GetEveryDayRecharge(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 72, Function: 16";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SGetEveryDayRechargeAck> fnAck_(new SGetEveryDayRechargeAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetEveryDayRecharge(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CMiscProtSvr::SBuyFenbaoyanAck::SBuyFenbaoyanAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eRet((EMiscOptRes)0) { }

void CMiscProtSvr::SBuyFenbaoyanAck::SendReturn(bool bRet_)
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
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 72, Function: 17";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CMiscProtSvr::_DoRecv_BuyFenbaoyan(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT16 wNum = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> wNum;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 72, Function: 17";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SBuyFenbaoyanAck> fnAck_(new SBuyFenbaoyanAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_BuyFenbaoyan(wNum, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CMiscProtSvr::SFenbaoyanTimeAck::SFenbaoyanTimeAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			dwBegin(0), dwEnd(0) { }

void CMiscProtSvr::SFenbaoyanTimeAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -8;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << dwBegin << dwEnd;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 72, Function: 18";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CMiscProtSvr::_DoRecv_FenbaoyanTime(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 72, Function: 18";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SFenbaoyanTimeAck> fnAck_(new SFenbaoyanTimeAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_FenbaoyanTime(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

} //namespace NMiscProt
