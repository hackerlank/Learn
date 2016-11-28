/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    DungeonProt.cpp
//  Purpose:      副本相关协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "DungeonProtSvr.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NDungeonProt
{

CDungeonProtSvr::THandleFunc CDungeonProtSvr::_HandleFuncs[] =
{
	&CDungeonProtSvr::_DoRecv_Sweeping, //FuncID: 1
	&CDungeonProtSvr::_DoRecv_SweepingSpeedUp, //FuncID: 2
	&CDungeonProtSvr::_DoRecv_CancelSweeping, //FuncID: 3
	&CDungeonProtSvr::_DoRecv_EnterPlayerDungeon, //FuncID: 4
	&CDungeonProtSvr::_DoRecv_LeavePlayerDungeon, //FuncID: 5
	&CDungeonProtSvr::_DoRecv_NotifyAcceptDgnAward, //FuncID: 6
	&CDungeonProtSvr::_DoRecv_GetAllDgnInfo, //FuncID: 7
	&CDungeonProtSvr::_DoRecv_GetDgnSweepingInfo, //FuncID: 8
	&CDungeonProtSvr::_DoRecv_GetDgnProcessAndStar, //FuncID: 9
	&CDungeonProtSvr::_DoRecv_ReliveInDgn, //FuncID: 10
	&CDungeonProtSvr::_DoRecv_GetTeamInfo, //FuncID: 11
	&CDungeonProtSvr::_DoRecv_BuyHeroDgnTimes, //FuncID: 12
	&CDungeonProtSvr::_DoRecv_BuyLiXianDgnTimes, //FuncID: 13
	&CDungeonProtSvr::_DoRecv_GetDgnStarAwardInfo, //FuncID: 14
	&CDungeonProtSvr::_DoRecv_GetDgnStarAward, //FuncID: 15
};

bool CDungeonProtSvr::HandleMessage(const char* pBuf, UINT32 dwLen)
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

//发送：扫荡更新通知
bool CDungeonProtSvr::Send_SweepingUpdateNotify(
	const NItemProt::TVecItemGenInfo& vecItem, //获得物品
	const NItemProt::TVecResource& vecResSource, //获得资源
	UINT16 wCurrCount, //当前次数
	UINT32 dwSweepEndTime //扫荡结束时间
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << vecItem << vecResSource << wCurrCount << dwSweepEndTime;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 59, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CDungeonProtSvr::SendClt_SweepingUpdateNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	const NItemProt::TVecItemGenInfo& vecItem, //获得物品
	const NItemProt::TVecResource& vecResSource, //获得资源
	UINT16 wCurrCount, //当前次数
	UINT32 dwSweepEndTime //扫荡结束时间
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << vecItem << vecResSource << wCurrCount << dwSweepEndTime;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 59, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CDungeonProtSvr::BuildPkg_SweepingUpdateNotify(
	const NItemProt::TVecItemGenInfo& vecItem, //获得物品
	const NItemProt::TVecResource& vecResSource, //获得资源
	UINT16 wCurrCount, //当前次数
	UINT32 dwSweepEndTime //扫荡结束时间
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << vecItem << vecResSource << wCurrCount << dwSweepEndTime;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 59, Function: 1";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：扫荡结束通知
bool CDungeonProtSvr::Send_SweepingEndNotify(
	EDungeonResult eResult //服务器返回结果
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
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 59, Function: 2";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CDungeonProtSvr::SendClt_SweepingEndNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	EDungeonResult eResult //服务器返回结果
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
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 59, Function: 2";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CDungeonProtSvr::BuildPkg_SweepingEndNotify(
	EDungeonResult eResult //服务器返回结果
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
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 59, Function: 2";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：副本地图怪物采集物索引通知
bool CDungeonProtSvr::Send_DungeonMapIdxNotify(
	const TVecUINT8& vecIdx //索引ID
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << vecIdx;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 59, Function: 3";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CDungeonProtSvr::SendClt_DungeonMapIdxNotify(const UINT64* pUsrID_, UINT16 wCnt_,
	const TVecUINT8& vecIdx //索引ID
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << vecIdx;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 59, Function: 3";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CDungeonProtSvr::BuildPkg_DungeonMapIdxNotify(
	const TVecUINT8& vecIdx //索引ID
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << vecIdx;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 59, Function: 3";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：通知通关副本领奖
bool CDungeonProtSvr::Send_NotifyDgnAward(
	UINT64 qwDgnId, //副本唯一实例
	UINT16 wDgnType, //副本类型
	UINT64 qwLastBattleID, //最后战报
	UINT8 byStar, //战斗评级
	const NItemProt::TVecItemGenInfo& vecItem, //获得物品
	const NItemProt::TVecResource& vecResSource //获得资源
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << qwDgnId << wDgnType << qwLastBattleID << byStar << vecItem << vecResSource;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 59, Function: 4";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CDungeonProtSvr::SendClt_NotifyDgnAward(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT64 qwDgnId, //副本唯一实例
	UINT16 wDgnType, //副本类型
	UINT64 qwLastBattleID, //最后战报
	UINT8 byStar, //战斗评级
	const NItemProt::TVecItemGenInfo& vecItem, //获得物品
	const NItemProt::TVecResource& vecResSource //获得资源
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << qwDgnId << wDgnType << qwLastBattleID << byStar << vecItem << vecResSource;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 59, Function: 4";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CDungeonProtSvr::BuildPkg_NotifyDgnAward(
	UINT64 qwDgnId, //副本唯一实例
	UINT16 wDgnType, //副本类型
	UINT64 qwLastBattleID, //最后战报
	UINT8 byStar, //战斗评级
	const NItemProt::TVecItemGenInfo& vecItem, //获得物品
	const NItemProt::TVecResource& vecResSource //获得资源
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << qwDgnId << wDgnType << qwLastBattleID << byStar << vecItem << vecResSource;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 59, Function: 4";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：通告副本进程
bool CDungeonProtSvr::Send_NotifyDgnProcess(
	UINT16 wDgnType, //副本类型
	const TVecMulCond& vecProcess //副本进度
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 5;
	try
	{
		ar << byProtID_ << byFuncID_ << wDgnType << vecProcess;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 59, Function: 5";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CDungeonProtSvr::SendClt_NotifyDgnProcess(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT16 wDgnType, //副本类型
	const TVecMulCond& vecProcess //副本进度
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 5;
	try
	{
		ar << byProtID_ << byFuncID_ << wDgnType << vecProcess;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 59, Function: 5";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CDungeonProtSvr::BuildPkg_NotifyDgnProcess(
	UINT16 wDgnType, //副本类型
	const TVecMulCond& vecProcess //副本进度
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 5;
	try
	{
		ar << byProtID_ << byFuncID_ << wDgnType << vecProcess;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 59, Function: 5";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：通告副本星级
bool CDungeonProtSvr::Send_NotifyDgnStar(
	UINT16 wDgnType, //副本类型
	const TVecMulCond& vecStar //副本星级
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 6;
	try
	{
		ar << byProtID_ << byFuncID_ << wDgnType << vecStar;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 59, Function: 6";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CDungeonProtSvr::SendClt_NotifyDgnStar(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT16 wDgnType, //副本类型
	const TVecMulCond& vecStar //副本星级
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 6;
	try
	{
		ar << byProtID_ << byFuncID_ << wDgnType << vecStar;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 59, Function: 6";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CDungeonProtSvr::BuildPkg_NotifyDgnStar(
	UINT16 wDgnType, //副本类型
	const TVecMulCond& vecStar //副本星级
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 6;
	try
	{
		ar << byProtID_ << byFuncID_ << wDgnType << vecStar;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 59, Function: 6";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：同步领奖记录
bool CDungeonProtSvr::Send_SynTeamAwardRecord(
	const TeamAwardAllRecord& stAward //同步数据
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 7;
	try
	{
		ar << byProtID_ << byFuncID_ << stAward;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 59, Function: 7";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CDungeonProtSvr::SendClt_SynTeamAwardRecord(const UINT64* pUsrID_, UINT16 wCnt_,
	const TeamAwardAllRecord& stAward //同步数据
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 7;
	try
	{
		ar << byProtID_ << byFuncID_ << stAward;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 59, Function: 7";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CDungeonProtSvr::BuildPkg_SynTeamAwardRecord(
	const TeamAwardAllRecord& stAward //同步数据
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 7;
	try
	{
		ar << byProtID_ << byFuncID_ << stAward;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 59, Function: 7";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：队伍战斗结果
bool CDungeonProtSvr::Send_TeamBattleResult(
	UINT16 DgnType, //副本类型
	UINT8 bySuc //0,失败，1成功
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 8;
	try
	{
		ar << byProtID_ << byFuncID_ << DgnType << bySuc;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 59, Function: 8";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CDungeonProtSvr::SendClt_TeamBattleResult(const UINT64* pUsrID_, UINT16 wCnt_,
	UINT16 DgnType, //副本类型
	UINT8 bySuc //0,失败，1成功
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 8;
	try
	{
		ar << byProtID_ << byFuncID_ << DgnType << bySuc;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 59, Function: 8";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CDungeonProtSvr::BuildPkg_TeamBattleResult(
	UINT16 DgnType, //副本类型
	UINT8 bySuc //0,失败，1成功
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 8;
	try
	{
		ar << byProtID_ << byFuncID_ << DgnType << bySuc;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 59, Function: 8";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：更新历险副本信息
bool CDungeonProtSvr::Send_UpdateLiXian(
	const DgnLiXian& sLiXian //历险副本信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 9;
	try
	{
		ar << byProtID_ << byFuncID_ << sLiXian;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 59, Function: 9";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CDungeonProtSvr::SendClt_UpdateLiXian(const UINT64* pUsrID_, UINT16 wCnt_,
	const DgnLiXian& sLiXian //历险副本信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 9;
	try
	{
		ar << byProtID_ << byFuncID_ << sLiXian;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 59, Function: 9";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CDungeonProtSvr::BuildPkg_UpdateLiXian(
	const DgnLiXian& sLiXian //历险副本信息
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 9;
	try
	{
		ar << byProtID_ << byFuncID_ << sLiXian;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 59, Function: 9";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：更新单个副本信息
bool CDungeonProtSvr::Send_UpdateDgnInfo(
	const DgnStar& sDgnStar //副本信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 10;
	try
	{
		ar << byProtID_ << byFuncID_ << sDgnStar;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 59, Function: 10";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CDungeonProtSvr::SendClt_UpdateDgnInfo(const UINT64* pUsrID_, UINT16 wCnt_,
	const DgnStar& sDgnStar //副本信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 10;
	try
	{
		ar << byProtID_ << byFuncID_ << sDgnStar;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 59, Function: 10";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CDungeonProtSvr::BuildPkg_UpdateDgnInfo(
	const DgnStar& sDgnStar //副本信息
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 10;
	try
	{
		ar << byProtID_ << byFuncID_ << sDgnStar;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 59, Function: 10";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：更新所有副本信息
bool CDungeonProtSvr::Send_UpdateDgnInfoForAll(
	const DgnLiXian& sLiXian, //历险副本信息
	const TVecDgnStar& vecStar //副本星级
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 11;
	try
	{
		ar << byProtID_ << byFuncID_ << sLiXian << vecStar;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 59, Function: 11";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CDungeonProtSvr::SendClt_UpdateDgnInfoForAll(const UINT64* pUsrID_, UINT16 wCnt_,
	const DgnLiXian& sLiXian, //历险副本信息
	const TVecDgnStar& vecStar //副本星级
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 11;
	try
	{
		ar << byProtID_ << byFuncID_ << sLiXian << vecStar;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendClt exception: " << szExcept << ", Protocol: 59, Function: 11";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendClt(pUsrID_, wCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CDungeonProtSvr::BuildPkg_UpdateDgnInfoForAll(
	const DgnLiXian& sLiXian, //历险副本信息
	const TVecDgnStar& vecStar //副本星级
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 11;
	try
	{
		ar << byProtID_ << byFuncID_ << sLiXian << vecStar;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 59, Function: 11";
		_strPkg.clear();
	}
	return _strPkg;
}

CDungeonProtSvr::SSweepingAck::SSweepingAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((EDungeonResult)0), dwSweepEndTime(0) { }

void CDungeonProtSvr::SSweepingAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -1;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eResult << dwSweepEndTime;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 59, Function: 1";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CDungeonProtSvr::_DoRecv_Sweeping(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT16 wDgnID = 0;
	UINT16 wCount = 0;
	UINT8 byOptions = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> wDgnID >> wCount >> byOptions;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 59, Function: 1";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SSweepingAck> fnAck_(new SSweepingAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_Sweeping(wDgnID, wCount, byOptions, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CDungeonProtSvr::SSweepingSpeedUpAck::SSweepingSpeedUpAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((EDungeonResult)0) { }

void CDungeonProtSvr::SSweepingSpeedUpAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -2;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 59, Function: 2";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CDungeonProtSvr::_DoRecv_SweepingSpeedUp(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT8 byOptions = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> byOptions;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 59, Function: 2";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SSweepingSpeedUpAck> fnAck_(new SSweepingSpeedUpAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_SweepingSpeedUp(byOptions, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CDungeonProtSvr::SCancelSweepingAck::SCancelSweepingAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((EDungeonResult)0) { }

void CDungeonProtSvr::SCancelSweepingAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -3;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 59, Function: 3";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CDungeonProtSvr::_DoRecv_CancelSweeping(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 59, Function: 3";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SCancelSweepingAck> fnAck_(new SCancelSweepingAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_CancelSweeping(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CDungeonProtSvr::SEnterPlayerDungeonAck::SEnterPlayerDungeonAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((EDungeonResult)0) { }

void CDungeonProtSvr::SEnterPlayerDungeonAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -4;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 59, Function: 4";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CDungeonProtSvr::_DoRecv_EnterPlayerDungeon(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT16 wDgnID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> wDgnID;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 59, Function: 4";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SEnterPlayerDungeonAck> fnAck_(new SEnterPlayerDungeonAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_EnterPlayerDungeon(wDgnID, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CDungeonProtSvr::SLeavePlayerDungeonAck::SLeavePlayerDungeonAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((EDungeonResult)0) { }

void CDungeonProtSvr::SLeavePlayerDungeonAck::SendReturn(bool bRet_)
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
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 59, Function: 5";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CDungeonProtSvr::_DoRecv_LeavePlayerDungeon(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 59, Function: 5";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SLeavePlayerDungeonAck> fnAck_(new SLeavePlayerDungeonAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_LeavePlayerDungeon(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CDungeonProtSvr::SNotifyAcceptDgnAwardAck::SNotifyAcceptDgnAwardAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((EDungeonResult)0) { }

void CDungeonProtSvr::SNotifyAcceptDgnAwardAck::SendReturn(bool bRet_)
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
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 59, Function: 6";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CDungeonProtSvr::_DoRecv_NotifyAcceptDgnAward(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT64 qwDgnID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> qwDgnID;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 59, Function: 6";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SNotifyAcceptDgnAwardAck> fnAck_(new SNotifyAcceptDgnAwardAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_NotifyAcceptDgnAward(qwDgnID, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CDungeonProtSvr::SGetAllDgnInfoAck::SGetAllDgnInfoAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID) { }

void CDungeonProtSvr::SGetAllDgnInfoAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -7;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << sLiXian << vecStar;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 59, Function: 7";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CDungeonProtSvr::_DoRecv_GetAllDgnInfo(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 59, Function: 7";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SGetAllDgnInfoAck> fnAck_(new SGetAllDgnInfoAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetAllDgnInfo(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CDungeonProtSvr::SGetDgnSweepingInfoAck::SGetDgnSweepingInfoAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID) { }

void CDungeonProtSvr::SGetDgnSweepingInfoAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -8;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << oGetSweepInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 59, Function: 8";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CDungeonProtSvr::_DoRecv_GetDgnSweepingInfo(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 59, Function: 8";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SGetDgnSweepingInfoAck> fnAck_(new SGetDgnSweepingInfoAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetDgnSweepingInfo(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

bool CDungeonProtSvr::_DoRecv_GetDgnProcessAndStar(const char* pBuf_, UINT32 dwLen_)
{
	OnRecv_GetDgnProcessAndStar();
	return true;
}

bool CDungeonProtSvr::_DoRecv_ReliveInDgn(const char* pBuf_, UINT32 dwLen_)
{
	OnRecv_ReliveInDgn();
	return true;
}

bool CDungeonProtSvr::_DoRecv_GetTeamInfo(const char* pBuf_, UINT32 dwLen_)
{
	OnRecv_GetTeamInfo();
	return true;
}

CDungeonProtSvr::SBuyHeroDgnTimesAck::SBuyHeroDgnTimesAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((EDungeonResult)0) { }

void CDungeonProtSvr::SBuyHeroDgnTimesAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -9;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 59, Function: 12";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CDungeonProtSvr::_DoRecv_BuyHeroDgnTimes(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT16 wDgnID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> wDgnID;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 59, Function: 12";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SBuyHeroDgnTimesAck> fnAck_(new SBuyHeroDgnTimesAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_BuyHeroDgnTimes(wDgnID, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CDungeonProtSvr::SBuyLiXianDgnTimesAck::SBuyLiXianDgnTimesAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((EDungeonResult)0) { }

void CDungeonProtSvr::SBuyLiXianDgnTimesAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -10;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 59, Function: 13";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CDungeonProtSvr::_DoRecv_BuyLiXianDgnTimes(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 59, Function: 13";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SBuyLiXianDgnTimesAck> fnAck_(new SBuyLiXianDgnTimesAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_BuyLiXianDgnTimes(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CDungeonProtSvr::SGetDgnStarAwardInfoAck::SGetDgnStarAwardInfoAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID) { }

void CDungeonProtSvr::SGetDgnStarAwardInfoAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -11;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << vecAward;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 59, Function: 14";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CDungeonProtSvr::_DoRecv_GetDgnStarAwardInfo(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 59, Function: 14";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SGetDgnStarAwardInfoAck> fnAck_(new SGetDgnStarAwardInfoAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetDgnStarAwardInfo(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CDungeonProtSvr::SGetDgnStarAwardAck::SGetDgnStarAwardAck(IProtocol& rProtocol, UINT64 qwUsrID, UINT32 dwSessionID) : 
			CClientFuncAck(rProtocol, qwUsrID, dwSessionID), 
			eResult((EDungeonResult)0) { }

void CDungeonProtSvr::SGetDgnStarAwardAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -12;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << (UINT8&)eResult << vecAward;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 59, Function: 15";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendClt(&_qwUsrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CDungeonProtSvr::_DoRecv_GetDgnStarAward(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT16 wStarID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> wStarID;
	}
	catch(const char* szExcept)
	{
#ifdef _DEBUG
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 59, Function: 15";
#else
		UNUSED(szExcept);
#endif
		return false;
	}
	shared_func<SGetDgnStarAwardAck> fnAck_(new SGetDgnStarAwardAck(*this, GetCurUsrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetDgnStarAward(wStarID, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

} //namespace NDungeonProt
