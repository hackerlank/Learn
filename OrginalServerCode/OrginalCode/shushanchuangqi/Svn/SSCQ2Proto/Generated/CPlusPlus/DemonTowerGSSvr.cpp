/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    DemonTowerGS.cpp
//  Purpose:      锁妖塔
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "DemonTowerGSSvr.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NDemonTowerGS
{

CDemonTowerGSSvr::THandleFunc CDemonTowerGSSvr::_HandleFuncs[] =
{
	&CDemonTowerGSSvr::_DoRecv_EnterDemonTower, //FuncID: 1
	&CDemonTowerGSSvr::_DoRecv_LeaveDemonTower, //FuncID: 2
	&CDemonTowerGSSvr::_DoRecv_SealMonster, //FuncID: 3
	&CDemonTowerGSSvr::_DoRecv_GuardAtk, //FuncID: 4
	&CDemonTowerGSSvr::_DoRecv_AtkPlayer, //FuncID: 5
	&CDemonTowerGSSvr::_DoRecv_TakePrize, //FuncID: 6
	&CDemonTowerGSSvr::_DoRecv_GetTopList, //FuncID: 7
	&CDemonTowerGSSvr::_DoRecv_GetDemonTowerInfo, //FuncID: 8
	&CDemonTowerGSSvr::_DoRecv_GetGuardInfo, //FuncID: 9
	&CDemonTowerGSSvr::_DoRecv_Restore, //FuncID: 10
	&CDemonTowerGSSvr::_DoRecv_AddSpeed, //FuncID: 11
	&CDemonTowerGSSvr::_DoRecv_GetPlayerInfo, //FuncID: 12
	&CDemonTowerGSSvr::_DoRecv_ClearFightCd, //FuncID: 13
	&CDemonTowerGSSvr::_DoRecv_GetPassInfo, //FuncID: 14
};

bool CDemonTowerGSSvr::HandleMessage(const char* pBuf, UINT32 dwLen)
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

//发送：锁妖塔镇守信息
bool CDemonTowerGSSvr::Send_GuardInfoNotify(
	UINT32 dwFloorID, //层数
	const TVecGuardInfo& vecGuardInfo //镇守玩家信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << dwFloorID << vecGuardInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 71, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CDemonTowerGSSvr::SendClt_GuardInfoNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT32 dwFloorID, //层数
	const TVecGuardInfo& vecGuardInfo //镇守玩家信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << dwFloorID << vecGuardInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 71, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CDemonTowerGSSvr::BuildPkg_GuardInfoNotify(
	UINT32 dwFloorID, //层数
	const TVecGuardInfo& vecGuardInfo //镇守玩家信息
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << dwFloorID << vecGuardInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 71, Function: 1";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：锁妖塔镇守信息更新
bool CDemonTowerGSSvr::Send_GuardInfoChangeNotify(
	UINT32 dwFloorID, //层数
	UINT32 dwPos, //镇守玩家信息
	UINT64 qwUserID, //玩家ID 0 表示该位置放弃镇守
	const GuardInfo& oGuardInfo //镇守信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << dwFloorID << dwPos << qwUserID << oGuardInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 71, Function: 2";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CDemonTowerGSSvr::SendClt_GuardInfoChangeNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT32 dwFloorID, //层数
	UINT32 dwPos, //镇守玩家信息
	UINT64 qwUserID, //玩家ID 0 表示该位置放弃镇守
	const GuardInfo& oGuardInfo //镇守信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << dwFloorID << dwPos << qwUserID << oGuardInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 71, Function: 2";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CDemonTowerGSSvr::BuildPkg_GuardInfoChangeNotify(
	UINT32 dwFloorID, //层数
	UINT32 dwPos, //镇守玩家信息
	UINT64 qwUserID, //玩家ID 0 表示该位置放弃镇守
	const GuardInfo& oGuardInfo //镇守信息
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << dwFloorID << dwPos << qwUserID << oGuardInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 71, Function: 2";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：锁妖塔过关通知
bool CDemonTowerGSSvr::Send_PassDemonTowerNotify(
	UINT32 dwFloorID //锁妖塔过关层数
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << dwFloorID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 71, Function: 3";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CDemonTowerGSSvr::SendClt_PassDemonTowerNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT32 dwFloorID //锁妖塔过关层数
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << dwFloorID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 71, Function: 3";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CDemonTowerGSSvr::BuildPkg_PassDemonTowerNotify(
	UINT32 dwFloorID //锁妖塔过关层数
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << dwFloorID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 71, Function: 3";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：锁妖塔镇守攻击cd
bool CDemonTowerGSSvr::Send_DemonTowerAtkCDNotify(
	UINT32 dwGuardNextAttackTime //锁妖塔可攻击最早时间
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << dwGuardNextAttackTime;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 71, Function: 4";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CDemonTowerGSSvr::SendClt_DemonTowerAtkCDNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT32 dwGuardNextAttackTime //锁妖塔可攻击最早时间
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << dwGuardNextAttackTime;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 71, Function: 4";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CDemonTowerGSSvr::BuildPkg_DemonTowerAtkCDNotify(
	UINT32 dwGuardNextAttackTime //锁妖塔可攻击最早时间
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << dwGuardNextAttackTime;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 71, Function: 4";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：镇妖塔玩家信息
bool CDemonTowerGSSvr::Send_DemonTowerPlayerNotify(
	const SDemonTowerPlayer& oDemonTowerPlayerInfo //镇妖塔玩家信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 5;
	try
	{
		ar << byProtID_ << byFuncID_ << oDemonTowerPlayerInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 71, Function: 5";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CDemonTowerGSSvr::SendClt_DemonTowerPlayerNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	const SDemonTowerPlayer& oDemonTowerPlayerInfo //镇妖塔玩家信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 5;
	try
	{
		ar << byProtID_ << byFuncID_ << oDemonTowerPlayerInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 71, Function: 5";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CDemonTowerGSSvr::BuildPkg_DemonTowerPlayerNotify(
	const SDemonTowerPlayer& oDemonTowerPlayerInfo //镇妖塔玩家信息
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 5;
	try
	{
		ar << byProtID_ << byFuncID_ << oDemonTowerPlayerInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 71, Function: 5";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：镇妖塔错误信息
bool CDemonTowerGSSvr::Send_DemonTowerErrorNotify(
	UINT32 dwError //错误码
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 6;
	try
	{
		ar << byProtID_ << byFuncID_ << dwError;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 71, Function: 6";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CDemonTowerGSSvr::SendClt_DemonTowerErrorNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT32 dwError //错误码
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 6;
	try
	{
		ar << byProtID_ << byFuncID_ << dwError;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 71, Function: 6";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CDemonTowerGSSvr::BuildPkg_DemonTowerErrorNotify(
	UINT32 dwError //错误码
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 6;
	try
	{
		ar << byProtID_ << byFuncID_ << dwError;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 71, Function: 6";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：镇守锁妖塔通知
bool CDemonTowerGSSvr::Send_GuardSucessNotify(
	UINT32 dwFloorID, //层数
	UINT32 dwGuardPos //镇守位置
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 7;
	try
	{
		ar << byProtID_ << byFuncID_ << dwFloorID << dwGuardPos;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 71, Function: 7";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CDemonTowerGSSvr::SendClt_GuardSucessNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT32 dwFloorID, //层数
	UINT32 dwGuardPos //镇守位置
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 7;
	try
	{
		ar << byProtID_ << byFuncID_ << dwFloorID << dwGuardPos;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 71, Function: 7";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CDemonTowerGSSvr::BuildPkg_GuardSucessNotify(
	UINT32 dwFloorID, //层数
	UINT32 dwGuardPos //镇守位置
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 7;
	try
	{
		ar << byProtID_ << byFuncID_ << dwFloorID << dwGuardPos;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 71, Function: 7";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：19点重置奖励通知
bool CDemonTowerGSSvr::Send_DemonTowerResetNotify(
	UINT32 dwFloorID, //层数
	UINT32 dwGuardPos, //镇守位置
	const TVecMoneyInfo& vecSoulPrize //获得的魄奖励
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 8;
	try
	{
		ar << byProtID_ << byFuncID_ << dwFloorID << dwGuardPos << vecSoulPrize;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 71, Function: 8";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CDemonTowerGSSvr::SendClt_DemonTowerResetNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT32 dwFloorID, //层数
	UINT32 dwGuardPos, //镇守位置
	const TVecMoneyInfo& vecSoulPrize //获得的魄奖励
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 8;
	try
	{
		ar << byProtID_ << byFuncID_ << dwFloorID << dwGuardPos << vecSoulPrize;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 71, Function: 8";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CDemonTowerGSSvr::BuildPkg_DemonTowerResetNotify(
	UINT32 dwFloorID, //层数
	UINT32 dwGuardPos, //镇守位置
	const TVecMoneyInfo& vecSoulPrize //获得的魄奖励
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 8;
	try
	{
		ar << byProtID_ << byFuncID_ << dwFloorID << dwGuardPos << vecSoulPrize;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 71, Function: 8";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：镇妖塔被抢通知
bool CDemonTowerGSSvr::Send_DemonTowerBeAttackNotify(
	UINT32 dwFloorID, //层数
	UINT32 dwPos, //位置
	UINT64 qwAtkUserID, //抢夺人的Id
	const std::string& strRole, //抢夺人的名字
	const TVecMoneyInfo& vecFailSoulPrize //失败后的魄奖励
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 9;
	try
	{
		ar << byProtID_ << byFuncID_ << dwFloorID << dwPos << qwAtkUserID << strRole << vecFailSoulPrize;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 71, Function: 9";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CDemonTowerGSSvr::SendClt_DemonTowerBeAttackNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT32 dwFloorID, //层数
	UINT32 dwPos, //位置
	UINT64 qwAtkUserID, //抢夺人的Id
	const std::string& strRole, //抢夺人的名字
	const TVecMoneyInfo& vecFailSoulPrize //失败后的魄奖励
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 9;
	try
	{
		ar << byProtID_ << byFuncID_ << dwFloorID << dwPos << qwAtkUserID << strRole << vecFailSoulPrize;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 71, Function: 9";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CDemonTowerGSSvr::BuildPkg_DemonTowerBeAttackNotify(
	UINT32 dwFloorID, //层数
	UINT32 dwPos, //位置
	UINT64 qwAtkUserID, //抢夺人的Id
	const std::string& strRole, //抢夺人的名字
	const TVecMoneyInfo& vecFailSoulPrize //失败后的魄奖励
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 9;
	try
	{
		ar << byProtID_ << byFuncID_ << dwFloorID << dwPos << qwAtkUserID << strRole << vecFailSoulPrize;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 71, Function: 9";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：玩家切层通知
bool CDemonTowerGSSvr::Send_EnterDemonTowerNotify(
	UINT32 dwCurFloorID //当前进入的层数
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 10;
	try
	{
		ar << byProtID_ << byFuncID_ << dwCurFloorID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 71, Function: 10";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CDemonTowerGSSvr::SendClt_EnterDemonTowerNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT32 dwCurFloorID //当前进入的层数
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 10;
	try
	{
		ar << byProtID_ << byFuncID_ << dwCurFloorID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 71, Function: 10";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CDemonTowerGSSvr::BuildPkg_EnterDemonTowerNotify(
	UINT32 dwCurFloorID //当前进入的层数
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 10;
	try
	{
		ar << byProtID_ << byFuncID_ << dwCurFloorID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 71, Function: 10";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：镇妖塔分身崩溃通知
bool CDemonTowerGSSvr::Send_PrizeNotify(
	EDemonTowerPrize eDemonTowerPrize, //魄奖励类型
	UINT32 dwFloorID, //层数
	UINT32 dwGuardPos, //镇守位置
	const TVecMoneyInfo& vecPrize //魄奖励
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 11;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eDemonTowerPrize << dwFloorID << dwGuardPos << vecPrize;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 71, Function: 11";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CDemonTowerGSSvr::SendClt_PrizeNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	EDemonTowerPrize eDemonTowerPrize, //魄奖励类型
	UINT32 dwFloorID, //层数
	UINT32 dwGuardPos, //镇守位置
	const TVecMoneyInfo& vecPrize //魄奖励
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 11;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eDemonTowerPrize << dwFloorID << dwGuardPos << vecPrize;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 71, Function: 11";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CDemonTowerGSSvr::BuildPkg_PrizeNotify(
	EDemonTowerPrize eDemonTowerPrize, //魄奖励类型
	UINT32 dwFloorID, //层数
	UINT32 dwGuardPos, //镇守位置
	const TVecMoneyInfo& vecPrize //魄奖励
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 11;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eDemonTowerPrize << dwFloorID << dwGuardPos << vecPrize;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 71, Function: 11";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：过关信息
bool CDemonTowerGSSvr::Send_PassInfoNotify(
	UINT16 wFloorID, //通关层
	const TVecDemonTowerKillMonster& vecMinRound, //最快通关
	const TVecDemonTowerKillMonster& vecMinBattlePoint //最小战斗力通关
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 12;
	try
	{
		ar << byProtID_ << byFuncID_ << wFloorID << vecMinRound << vecMinBattlePoint;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 71, Function: 12";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CDemonTowerGSSvr::SendClt_PassInfoNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT16 wFloorID, //通关层
	const TVecDemonTowerKillMonster& vecMinRound, //最快通关
	const TVecDemonTowerKillMonster& vecMinBattlePoint //最小战斗力通关
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 12;
	try
	{
		ar << byProtID_ << byFuncID_ << wFloorID << vecMinRound << vecMinBattlePoint;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 71, Function: 12";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CDemonTowerGSSvr::BuildPkg_PassInfoNotify(
	UINT16 wFloorID, //通关层
	const TVecDemonTowerKillMonster& vecMinRound, //最快通关
	const TVecDemonTowerKillMonster& vecMinBattlePoint //最小战斗力通关
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 12;
	try
	{
		ar << byProtID_ << byFuncID_ << wFloorID << vecMinRound << vecMinBattlePoint;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 71, Function: 12";
		_strPkg.clear();
	}
	return _strPkg;
}

CDemonTowerGSSvr::SEnterDemonTowerAck::SEnterDemonTowerAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			dwRet(0) { }

void CDemonTowerGSSvr::SEnterDemonTowerAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -1;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << dwRet;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 71, Function: 1";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CDemonTowerGSSvr::_DoRecv_EnterDemonTower(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT32 dwFloorID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> dwFloorID;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 71, Function: 1";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SEnterDemonTowerAck> fnAck_(new SEnterDemonTowerAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_EnterDemonTower(dwFloorID, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CDemonTowerGSSvr::SLeaveDemonTowerAck::SLeaveDemonTowerAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			dwRet(0) { }

void CDemonTowerGSSvr::SLeaveDemonTowerAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -2;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << dwRet;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 71, Function: 2";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CDemonTowerGSSvr::_DoRecv_LeaveDemonTower(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 71, Function: 2";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SLeaveDemonTowerAck> fnAck_(new SLeaveDemonTowerAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_LeaveDemonTower(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CDemonTowerGSSvr::SSealMonsterAck::SSealMonsterAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			dwRet(0) { }

void CDemonTowerGSSvr::SSealMonsterAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -3;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << dwRet;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 71, Function: 3";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CDemonTowerGSSvr::_DoRecv_SealMonster(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT32 dwFloorID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> dwFloorID;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 71, Function: 3";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SSealMonsterAck> fnAck_(new SSealMonsterAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_SealMonster(dwFloorID, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CDemonTowerGSSvr::SGuardAtkAck::SGuardAtkAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			dwRet(0) { }

void CDemonTowerGSSvr::SGuardAtkAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -4;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << dwRet;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 71, Function: 4";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CDemonTowerGSSvr::_DoRecv_GuardAtk(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT32 dwFloorID = 0;
	UINT32 dwGuardPos = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> dwFloorID >> dwGuardPos;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 71, Function: 4";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SGuardAtkAck> fnAck_(new SGuardAtkAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_GuardAtk(dwFloorID, dwGuardPos, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CDemonTowerGSSvr::SAtkPlayerAck::SAtkPlayerAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			dwRet(0) { }

void CDemonTowerGSSvr::SAtkPlayerAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -5;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << dwRet;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 71, Function: 5";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CDemonTowerGSSvr::_DoRecv_AtkPlayer(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT32 dwFloorID = 0;
	UINT32 dwGuardPos = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> dwFloorID >> dwGuardPos;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 71, Function: 5";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SAtkPlayerAck> fnAck_(new SAtkPlayerAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_AtkPlayer(dwFloorID, dwGuardPos, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CDemonTowerGSSvr::STakePrizeAck::STakePrizeAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			dwRet(0) { }

void CDemonTowerGSSvr::STakePrizeAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -6;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << dwRet;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 71, Function: 6";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CDemonTowerGSSvr::_DoRecv_TakePrize(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	EDemonTowerPrize ePrizeType = (EDemonTowerPrize)0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> (UINT8&)ePrizeType;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 71, Function: 6";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<STakePrizeAck> fnAck_(new STakePrizeAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_TakePrize(ePrizeType, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CDemonTowerGSSvr::SGetTopListAck::SGetTopListAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID) { }

void CDemonTowerGSSvr::SGetTopListAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -7;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << oDemonFloorPage;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 71, Function: 7";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CDemonTowerGSSvr::_DoRecv_GetTopList(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT16 wPage = 0;
	UINT16 wPageItemCount = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> wPage >> wPageItemCount;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 71, Function: 7";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SGetTopListAck> fnAck_(new SGetTopListAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetTopList(wPage, wPageItemCount, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CDemonTowerGSSvr::SGetDemonTowerInfoAck::SGetDemonTowerInfoAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			dwRet(0) { }

void CDemonTowerGSSvr::SGetDemonTowerInfoAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -8;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << dwRet << oDemonTowerPlayer;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 71, Function: 8";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CDemonTowerGSSvr::_DoRecv_GetDemonTowerInfo(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 71, Function: 8";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SGetDemonTowerInfoAck> fnAck_(new SGetDemonTowerInfoAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetDemonTowerInfo(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CDemonTowerGSSvr::SGetGuardInfoAck::SGetGuardInfoAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID) { }

void CDemonTowerGSSvr::SGetGuardInfoAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -9;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << vecGuardInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 71, Function: 9";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CDemonTowerGSSvr::_DoRecv_GetGuardInfo(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT32 dwFloorID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> dwFloorID;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 71, Function: 9";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SGetGuardInfoAck> fnAck_(new SGetGuardInfoAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetGuardInfo(dwFloorID, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

bool CDemonTowerGSSvr::_DoRecv_Restore(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwCount = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwCount;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 71, Function: 10";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	OnRecv_Restore(dwCount);
	return true;
}

bool CDemonTowerGSSvr::_DoRecv_AddSpeed(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwCount = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwCount;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 71, Function: 11";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	OnRecv_AddSpeed(dwCount);
	return true;
}

CDemonTowerGSSvr::SGetPlayerInfoAck::SGetPlayerInfoAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			bRet(0) { }

void CDemonTowerGSSvr::SGetPlayerInfoAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -10;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << bRet << oDemonFloorPlayer;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 71, Function: 12";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CDemonTowerGSSvr::_DoRecv_GetPlayerInfo(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 71, Function: 12";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SGetPlayerInfoAck> fnAck_(new SGetPlayerInfoAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetPlayerInfo(qwUserID, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CDemonTowerGSSvr::SClearFightCdAck::SClearFightCdAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			bRet(0) { }

void CDemonTowerGSSvr::SClearFightCdAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -11;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << bRet;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 71, Function: 13";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CDemonTowerGSSvr::_DoRecv_ClearFightCd(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 71, Function: 13";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SClearFightCdAck> fnAck_(new SClearFightCdAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_ClearFightCd(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CDemonTowerGSSvr::SGetPassInfoAck::SGetPassInfoAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID) { }

void CDemonTowerGSSvr::SGetPassInfoAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -12;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << vecMinRound << vecMinBattlePoint;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 71, Function: 14";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CDemonTowerGSSvr::_DoRecv_GetPassInfo(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT16 wFloorID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> wFloorID;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 71, Function: 14";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SGetPassInfoAck> fnAck_(new SGetPassInfoAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetPassInfo(wFloorID, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

} //namespace NDemonTowerGS
