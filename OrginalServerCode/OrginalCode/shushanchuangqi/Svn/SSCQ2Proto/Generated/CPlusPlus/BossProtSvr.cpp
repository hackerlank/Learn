/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    BossProt.cpp
//  Purpose:      BOSS相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "BossProtSvr.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NBossProt
{

CBossProtSvr::THandleFunc CBossProtSvr::_HandleFuncs[] =
{
	&CBossProtSvr::_DoRecv_WBAlive, //FuncID: 1
	&CBossProtSvr::_DoRecv_WBStrength, //FuncID: 2
	&CBossProtSvr::_DoRecv_WBAttack, //FuncID: 3
	&CBossProtSvr::_DoRecv_GetTopList, //FuncID: 4
	&CBossProtSvr::_DoRecv_GetSelfInfo, //FuncID: 5
	&CBossProtSvr::_DoRecv_GetBossInfo, //FuncID: 6
	&CBossProtSvr::_DoRecv_EnterMap, //FuncID: 7
	&CBossProtSvr::_DoRecv_LeaveMap, //FuncID: 8
};

bool CBossProtSvr::HandleMessage(const char* pBuf, UINT32 dwLen)
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

//发送：世界BOSS信息通知
bool CBossProtSvr::Send_BossInfoNotify(
	UINT32 dwBoosID, //bossID
	UINT32 dwCurHP, //当前血量
	UINT32 dwMaxHP, //最大血量
	UINT32 dwPlayerCnt //当前地图人数
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << dwBoosID << dwCurHP << dwMaxHP << dwPlayerCnt;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 25, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CBossProtSvr::SendClt_BossInfoNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT32 dwBoosID, //bossID
	UINT32 dwCurHP, //当前血量
	UINT32 dwMaxHP, //最大血量
	UINT32 dwPlayerCnt //当前地图人数
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << dwBoosID << dwCurHP << dwMaxHP << dwPlayerCnt;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 25, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CBossProtSvr::BuildPkg_BossInfoNotify(
	UINT32 dwBoosID, //bossID
	UINT32 dwCurHP, //当前血量
	UINT32 dwMaxHP, //最大血量
	UINT32 dwPlayerCnt //当前地图人数
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << dwBoosID << dwCurHP << dwMaxHP << dwPlayerCnt;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 25, Function: 1";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：排行榜通知
bool CBossProtSvr::Send_TopListNotify(
	const TVecPlayerInfo& vecTopList //排行榜列表
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << vecTopList;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 25, Function: 2";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CBossProtSvr::SendClt_TopListNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	const TVecPlayerInfo& vecTopList //排行榜列表
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << vecTopList;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 25, Function: 2";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CBossProtSvr::BuildPkg_TopListNotify(
	const TVecPlayerInfo& vecTopList //排行榜列表
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << vecTopList;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 25, Function: 2";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：个人信息通知
bool CBossProtSvr::Send_SelfInfoNotify(
	const SPlayerInfo& oSelfInfo, //玩家信息
	UINT32 dwBeginTime, //开始时间
	UINT32 dwEndTime, //结束时间
	UINT32 dwReliveTime, //复活时间
	UINT32 dwSilverBufferCdTime, //银币加持cd
	UINT32 dwSilverBufferCnt, //银币加持次数
	UINT32 dwGoldBufferCnt, //金币加持次数
	UINT32 dwGoldAttackCnt //直接攻击次数
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << oSelfInfo << dwBeginTime << dwEndTime << dwReliveTime << dwSilverBufferCdTime << dwSilverBufferCnt << dwGoldBufferCnt << dwGoldAttackCnt;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 25, Function: 3";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CBossProtSvr::SendClt_SelfInfoNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	const SPlayerInfo& oSelfInfo, //玩家信息
	UINT32 dwBeginTime, //开始时间
	UINT32 dwEndTime, //结束时间
	UINT32 dwReliveTime, //复活时间
	UINT32 dwSilverBufferCdTime, //银币加持cd
	UINT32 dwSilverBufferCnt, //银币加持次数
	UINT32 dwGoldBufferCnt, //金币加持次数
	UINT32 dwGoldAttackCnt //直接攻击次数
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << oSelfInfo << dwBeginTime << dwEndTime << dwReliveTime << dwSilverBufferCdTime << dwSilverBufferCnt << dwGoldBufferCnt << dwGoldAttackCnt;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 25, Function: 3";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CBossProtSvr::BuildPkg_SelfInfoNotify(
	const SPlayerInfo& oSelfInfo, //玩家信息
	UINT32 dwBeginTime, //开始时间
	UINT32 dwEndTime, //结束时间
	UINT32 dwReliveTime, //复活时间
	UINT32 dwSilverBufferCdTime, //银币加持cd
	UINT32 dwSilverBufferCnt, //银币加持次数
	UINT32 dwGoldBufferCnt, //金币加持次数
	UINT32 dwGoldAttackCnt //直接攻击次数
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << oSelfInfo << dwBeginTime << dwEndTime << dwReliveTime << dwSilverBufferCdTime << dwSilverBufferCnt << dwGoldBufferCnt << dwGoldAttackCnt;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 25, Function: 3";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：伤害boss信息
bool CBossProtSvr::Send_AtkInfoNotify(
	UINT32 dwDamage, //本次伤害
	UINT32 dwExp, //本次活动经验值
	UINT32 dwTotalDamage, //总伤害
	UINT32 dwBossMaxHp //boss最大血量
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << dwDamage << dwExp << dwTotalDamage << dwBossMaxHp;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 25, Function: 4";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CBossProtSvr::SendClt_AtkInfoNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT32 dwDamage, //本次伤害
	UINT32 dwExp, //本次活动经验值
	UINT32 dwTotalDamage, //总伤害
	UINT32 dwBossMaxHp //boss最大血量
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << dwDamage << dwExp << dwTotalDamage << dwBossMaxHp;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 25, Function: 4";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CBossProtSvr::BuildPkg_AtkInfoNotify(
	UINT32 dwDamage, //本次伤害
	UINT32 dwExp, //本次活动经验值
	UINT32 dwTotalDamage, //总伤害
	UINT32 dwBossMaxHp //boss最大血量
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << dwDamage << dwExp << dwTotalDamage << dwBossMaxHp;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 25, Function: 4";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：玩家名次变化通知
bool CBossProtSvr::Send_NoChangeNotify(
	UINT32 dwNo //玩家名次
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 5;
	try
	{
		ar << byProtID_ << byFuncID_ << dwNo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 25, Function: 5";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CBossProtSvr::SendClt_NoChangeNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT32 dwNo //玩家名次
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 5;
	try
	{
		ar << byProtID_ << byFuncID_ << dwNo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 25, Function: 5";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CBossProtSvr::BuildPkg_NoChangeNotify(
	UINT32 dwNo //玩家名次
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 5;
	try
	{
		ar << byProtID_ << byFuncID_ << dwNo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 25, Function: 5";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：玩家奖励获取通知
bool CBossProtSvr::Send_PrizeNotify(
	const TVecPlayerPrize& vecPlayerPrize //玩家奖励列表
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 6;
	try
	{
		ar << byProtID_ << byFuncID_ << vecPlayerPrize;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 25, Function: 6";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CBossProtSvr::SendClt_PrizeNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	const TVecPlayerPrize& vecPlayerPrize //玩家奖励列表
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 6;
	try
	{
		ar << byProtID_ << byFuncID_ << vecPlayerPrize;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 25, Function: 6";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CBossProtSvr::BuildPkg_PrizeNotify(
	const TVecPlayerPrize& vecPlayerPrize //玩家奖励列表
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 6;
	try
	{
		ar << byProtID_ << byFuncID_ << vecPlayerPrize;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 25, Function: 6";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：玩家复活时间通知
bool CBossProtSvr::Send_ReliveTimeNotify(
	UINT32 dwReliveTime //复活时间
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 7;
	try
	{
		ar << byProtID_ << byFuncID_ << dwReliveTime;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 25, Function: 7";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CBossProtSvr::SendClt_ReliveTimeNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT32 dwReliveTime //复活时间
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 7;
	try
	{
		ar << byProtID_ << byFuncID_ << dwReliveTime;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 25, Function: 7";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CBossProtSvr::BuildPkg_ReliveTimeNotify(
	UINT32 dwReliveTime //复活时间
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 7;
	try
	{
		ar << byProtID_ << byFuncID_ << dwReliveTime;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 25, Function: 7";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：活动结束通知
bool CBossProtSvr::Send_EndNotify(
	UINT32 dwLeaveTime //离开时间
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 8;
	try
	{
		ar << byProtID_ << byFuncID_ << dwLeaveTime;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 25, Function: 8";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CBossProtSvr::SendClt_EndNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT32 dwLeaveTime //离开时间
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 8;
	try
	{
		ar << byProtID_ << byFuncID_ << dwLeaveTime;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 25, Function: 8";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CBossProtSvr::BuildPkg_EndNotify(
	UINT32 dwLeaveTime //离开时间
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 8;
	try
	{
		ar << byProtID_ << byFuncID_ << dwLeaveTime;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 25, Function: 8";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：玩家直接攻击次数
bool CBossProtSvr::Send_AttackCountNotify(
	UINT16 dwAttackCount //玩家直接攻击次数
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 9;
	try
	{
		ar << byProtID_ << byFuncID_ << dwAttackCount;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 25, Function: 9";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CBossProtSvr::SendClt_AttackCountNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT16 dwAttackCount //玩家直接攻击次数
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 9;
	try
	{
		ar << byProtID_ << byFuncID_ << dwAttackCount;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 25, Function: 9";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CBossProtSvr::BuildPkg_AttackCountNotify(
	UINT16 dwAttackCount //玩家直接攻击次数
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 9;
	try
	{
		ar << byProtID_ << byFuncID_ << dwAttackCount;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 25, Function: 9";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：结算通知
bool CBossProtSvr::Send_GainPrizeNotify(
	UINT32 dwNo, //玩家名次
	UINT32 dwExp, //总共获得经验
	bool bKillBoss //是否击杀boss
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 10;
	try
	{
		ar << byProtID_ << byFuncID_ << dwNo << dwExp << bKillBoss;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 25, Function: 10";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CBossProtSvr::SendClt_GainPrizeNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT32 dwNo, //玩家名次
	UINT32 dwExp, //总共获得经验
	bool bKillBoss //是否击杀boss
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 10;
	try
	{
		ar << byProtID_ << byFuncID_ << dwNo << dwExp << bKillBoss;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 25, Function: 10";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CBossProtSvr::BuildPkg_GainPrizeNotify(
	UINT32 dwNo, //玩家名次
	UINT32 dwExp, //总共获得经验
	bool bKillBoss //是否击杀boss
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 10;
	try
	{
		ar << byProtID_ << byFuncID_ << dwNo << dwExp << bKillBoss;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 25, Function: 10";
		_strPkg.clear();
	}
	return _strPkg;
}

CBossProtSvr::SWBAliveAck::SWBAliveAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			bRet(false) { }

void CBossProtSvr::SWBAliveAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -1;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << bRet;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 25, Function: 1";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CBossProtSvr::_DoRecv_WBAlive(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 25, Function: 1";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SWBAliveAck> fnAck_(new SWBAliveAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_WBAlive(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CBossProtSvr::SWBStrengthAck::SWBStrengthAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			dwSilverBufferCnt(0), dwGoldBufferCnt(0), dwSilverBufferCdTime(0), bRet(false) { }

void CBossProtSvr::SWBStrengthAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -2;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << dwSilverBufferCnt << dwGoldBufferCnt << dwSilverBufferCdTime << bRet;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 25, Function: 2";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CBossProtSvr::_DoRecv_WBStrength(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	EBossBuyType eBuyType = (EBossBuyType)0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> (UINT8&)eBuyType;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 25, Function: 2";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SWBStrengthAck> fnAck_(new SWBStrengthAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_WBStrength(eBuyType, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CBossProtSvr::SWBAttackAck::SWBAttackAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			bRet(false) { }

void CBossProtSvr::SWBAttackAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -3;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << bRet;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 25, Function: 3";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CBossProtSvr::_DoRecv_WBAttack(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 25, Function: 3";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SWBAttackAck> fnAck_(new SWBAttackAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_WBAttack(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

bool CBossProtSvr::_DoRecv_GetTopList(const char* pBuf_, UINT32 dwLen_)
{
	OnRecv_GetTopList();
	return true;
}

bool CBossProtSvr::_DoRecv_GetSelfInfo(const char* pBuf_, UINT32 dwLen_)
{
	OnRecv_GetSelfInfo();
	return true;
}

bool CBossProtSvr::_DoRecv_GetBossInfo(const char* pBuf_, UINT32 dwLen_)
{
	OnRecv_GetBossInfo();
	return true;
}

CBossProtSvr::SEnterMapAck::SEnterMapAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			bRet(false) { }

void CBossProtSvr::SEnterMapAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -4;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << bRet;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 25, Function: 7";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CBossProtSvr::_DoRecv_EnterMap(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 25, Function: 7";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SEnterMapAck> fnAck_(new SEnterMapAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_EnterMap(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CBossProtSvr::SLeaveMapAck::SLeaveMapAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			bRet(false) { }

void CBossProtSvr::SLeaveMapAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -5;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << bRet;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 25, Function: 8";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CBossProtSvr::_DoRecv_LeaveMap(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 25, Function: 8";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SLeaveMapAck> fnAck_(new SLeaveMapAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_LeaveMap(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

} //namespace NBossProt
