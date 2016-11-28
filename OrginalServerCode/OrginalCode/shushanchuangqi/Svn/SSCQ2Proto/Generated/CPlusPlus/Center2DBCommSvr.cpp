/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    Center2DBComm.cpp
//  Purpose:      CenterServer到DBServer的通信协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "Center2DBCommSvr.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NCenter2DBComm
{

CCenter2DBCommSvr::THandleFunc CCenter2DBCommSvr::_HandleFuncs[] =
{
	&CCenter2DBCommSvr::_DoRecv_KeepAlive, //FuncID: 1
	&CCenter2DBCommSvr::_DoRecv_GetStatus, //FuncID: 2
	&CCenter2DBCommSvr::_DoRecv_InsertRecharge, //FuncID: 3
	&CCenter2DBCommSvr::_DoRecv_LoadPrepaid, //FuncID: 4
	&CCenter2DBCommSvr::_DoRecv_UpdatePrepaid, //FuncID: 5
	&CCenter2DBCommSvr::_DoRecv_ReplaceUser, //FuncID: 6
	&CCenter2DBCommSvr::_DoRecv_LoadOffLineUserData, //FuncID: 7
	&CCenter2DBCommSvr::_DoRecv_RoleDataUpdate, //FuncID: 8
	&CCenter2DBCommSvr::_DoRecv_GetRankInfo, //FuncID: 9
	&CCenter2DBCommSvr::_DoRecv_RankDataUpdate, //FuncID: 10
	&CCenter2DBCommSvr::_DoRecv_GetAdoreInfo, //FuncID: 11
	&CCenter2DBCommSvr::_DoRecv_AdoreDataUpdate, //FuncID: 12
	&CCenter2DBCommSvr::_DoRecv_UserIDNameReq, //FuncID: 13
	&CCenter2DBCommSvr::_DoRecv_GetUserIDFromName, //FuncID: 14
	&CCenter2DBCommSvr::_DoRecv_GetAllMailList, //FuncID: 15
	&CCenter2DBCommSvr::_DoRecv_SaveMail, //FuncID: 16
	&CCenter2DBCommSvr::_DoRecv_DeleteMail, //FuncID: 17
	&CCenter2DBCommSvr::_DoRecv_SaveSystemMail, //FuncID: 18
	&CCenter2DBCommSvr::_DoRecv_UpdateMailStatus, //FuncID: 19
	&CCenter2DBCommSvr::_DoRecv_DelMailAttach, //FuncID: 20
	&CCenter2DBCommSvr::_DoRecv_GetPrizeStatus, //FuncID: 21
	&CCenter2DBCommSvr::_DoRecv_DelActPrizeData, //FuncID: 22
	&CCenter2DBCommSvr::_DoRecv_GetAllRoleLevel, //FuncID: 23
	&CCenter2DBCommSvr::_DoRecv_UpdatePrizeStatus, //FuncID: 24
	&CCenter2DBCommSvr::_DoRecv_GetRetain, //FuncID: 25
	&CCenter2DBCommSvr::_DoRecv_UpdateRetain, //FuncID: 26
	&CCenter2DBCommSvr::_DoRecv_DelActRetainData, //FuncID: 27
	&CCenter2DBCommSvr::_DoRecv_GetAllUserIDAndName, //FuncID: 28
	&CCenter2DBCommSvr::_DoRecv_GetAllNotice, //FuncID: 29
	&CCenter2DBCommSvr::_DoRecv_AddNotice, //FuncID: 30
	&CCenter2DBCommSvr::_DoRecv_DelNotice, //FuncID: 31
	&CCenter2DBCommSvr::_DoRecv_GetAllArena, //FuncID: 32
	&CCenter2DBCommSvr::_DoRecv_UpdateAllArena, //FuncID: 33
	&CCenter2DBCommSvr::_DoRecv_DelPlayerArena, //FuncID: 34
	&CCenter2DBCommSvr::_DoRecv_GetGameVar, //FuncID: 35
	&CCenter2DBCommSvr::_DoRecv_UpdateGameVar, //FuncID: 36
	&CCenter2DBCommSvr::_DoRecv_AddGameVar, //FuncID: 37
	&CCenter2DBCommSvr::_DoRecv_DelGameVar, //FuncID: 38
	&CCenter2DBCommSvr::_DoRecv_GetArenaFighterByID, //FuncID: 39
	&CCenter2DBCommSvr::_DoRecv_GetDemonTowerInfo, //FuncID: 40
	&CCenter2DBCommSvr::_DoRecv_UpateDemonTowerInfo, //FuncID: 41
	&CCenter2DBCommSvr::_DoRecv_GetCenterData, //FuncID: 42
	&CCenter2DBCommSvr::_DoRecv_UpateCenterData, //FuncID: 43
	&CCenter2DBCommSvr::_DoRecv_GetWhisperInfo, //FuncID: 44
	&CCenter2DBCommSvr::_DoRecv_GetBattleReport, //FuncID: 45
	&CCenter2DBCommSvr::_DoRecv_AddBattleReport, //FuncID: 46
	&CCenter2DBCommSvr::_DoRecv_ReloadTable, //FuncID: 47
	&CCenter2DBCommSvr::_DoRecv_GetAllTripod, //FuncID: 48
	&CCenter2DBCommSvr::_DoRecv_GetAllTripodHelper, //FuncID: 49
	&CCenter2DBCommSvr::_DoRecv_GetAllTripodLog, //FuncID: 50
	&CCenter2DBCommSvr::_DoRecv_UpdateTripod, //FuncID: 51
	&CCenter2DBCommSvr::_DoRecv_UpateTripodHelp, //FuncID: 52
	&CCenter2DBCommSvr::_DoRecv_UpdateTripodLog, //FuncID: 53
	&CCenter2DBCommSvr::_DoRecv_AddOffLineEvent, //FuncID: 54
	&CCenter2DBCommSvr::_DoRecv_FreezePlayer, //FuncID: 55
	&CCenter2DBCommSvr::_DoRecv_ForbitChat, //FuncID: 56
	&CCenter2DBCommSvr::_DoRecv_UpdateLoginIP, //FuncID: 57
	&CCenter2DBCommSvr::_DoRecv_GetPlatformParam, //FuncID: 58
	&CCenter2DBCommSvr::_DoRecv_GetResult2DB, //FuncID: 59
	&CCenter2DBCommSvr::_DoRecv_GetAllShip, //FuncID: 60
	&CCenter2DBCommSvr::_DoRecv_UpdateShip, //FuncID: 61
	&CCenter2DBCommSvr::_DoRecv_DelShip, //FuncID: 62
	&CCenter2DBCommSvr::_DoRecv_AddShipReport, //FuncID: 63
	&CCenter2DBCommSvr::_DoRecv_DelShipReport, //FuncID: 64
	&CCenter2DBCommSvr::_DoRecv_SyncMonsterUserInfo, //FuncID: 65
	&CCenter2DBCommSvr::_DoRecv_GetGodMonsterInfo, //FuncID: 66
	&CCenter2DBCommSvr::_DoRecv_SyncLimitPrizeInfo, //FuncID: 67
	&CCenter2DBCommSvr::_DoRecv_GetLimitPrizeInfo, //FuncID: 68
	&CCenter2DBCommSvr::_DoRecv_SyncActivityCenterInfo, //FuncID: 69
	&CCenter2DBCommSvr::_DoRecv_GetActivityCenterInfo, //FuncID: 70
	&CCenter2DBCommSvr::_DoRecv_AddLadderRobot, //FuncID: 71
	&CCenter2DBCommSvr::_DoRecv_UpdateLadderRobot, //FuncID: 72
};

bool CCenter2DBCommSvr::HandleMessage(const char* pBuf, UINT32 dwLen)
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

//发送：返回查询结果
bool CCenter2DBCommSvr::Send_SendResult2Cent(
	const SBaseCond& sCond, //查询条件
	const SBaseResult& sResult //查询结果
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << sCond << sResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 31, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CCenter2DBCommSvr::SendSvr_SendResult2Cent(const UINT32* pSvrID_, UINT8 byCnt_,
	const SBaseCond& sCond, //查询条件
	const SBaseResult& sResult //查询结果
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << sCond << sResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 31, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CCenter2DBCommSvr::BuildPkg_SendResult2Cent(
	const SBaseCond& sCond, //查询条件
	const SBaseResult& sResult //查询结果
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << sCond << sResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 31, Function: 1";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：返回所有玩家ID和名字
bool CCenter2DBCommSvr::Send_SendAllUserIDAndName(
	UINT32 dwTotalSize, //总条数
	const NPHPProt::TVecUserIDAndName& vecUserIDAndName //玩家ID和名字
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << dwTotalSize << vecUserIDAndName;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 31, Function: 2";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CCenter2DBCommSvr::SendSvr_SendAllUserIDAndName(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT32 dwTotalSize, //总条数
	const NPHPProt::TVecUserIDAndName& vecUserIDAndName //玩家ID和名字
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << dwTotalSize << vecUserIDAndName;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 31, Function: 2";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CCenter2DBCommSvr::BuildPkg_SendAllUserIDAndName(
	UINT32 dwTotalSize, //总条数
	const NPHPProt::TVecUserIDAndName& vecUserIDAndName //玩家ID和名字
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << dwTotalSize << vecUserIDAndName;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 31, Function: 2";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：返回所有公告
bool CCenter2DBCommSvr::Send_SendAllNotice(
	const NPHPProt::TVecNotice& vecNotice //公告内容
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << vecNotice;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 31, Function: 3";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CCenter2DBCommSvr::SendSvr_SendAllNotice(const UINT32* pSvrID_, UINT8 byCnt_,
	const NPHPProt::TVecNotice& vecNotice //公告内容
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << vecNotice;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 31, Function: 3";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CCenter2DBCommSvr::BuildPkg_SendAllNotice(
	const NPHPProt::TVecNotice& vecNotice //公告内容
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << vecNotice;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 31, Function: 3";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：返回请求斗剑信息
bool CCenter2DBCommSvr::Send_SendAllArena(
	UINT32 dwPageSize, //已发送条数
	UINT32 dwTotalSize, //总条数
	const NArenaGS::TVecArenaPlayerData& vecSendDate //更新信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << dwPageSize << dwTotalSize << vecSendDate;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 31, Function: 4";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CCenter2DBCommSvr::SendSvr_SendAllArena(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT32 dwPageSize, //已发送条数
	UINT32 dwTotalSize, //总条数
	const NArenaGS::TVecArenaPlayerData& vecSendDate //更新信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << dwPageSize << dwTotalSize << vecSendDate;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 31, Function: 4";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CCenter2DBCommSvr::BuildPkg_SendAllArena(
	UINT32 dwPageSize, //已发送条数
	UINT32 dwTotalSize, //总条数
	const NArenaGS::TVecArenaPlayerData& vecSendDate //更新信息
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << dwPageSize << dwTotalSize << vecSendDate;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 31, Function: 4";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：返回机器人天梯排行信息
bool CCenter2DBCommSvr::Send_SendAllRobot(
	const NArenaGS::TVecLadderRobot& vecRobot //机器人排行信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 5;
	try
	{
		ar << byProtID_ << byFuncID_ << vecRobot;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 31, Function: 5";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CCenter2DBCommSvr::SendSvr_SendAllRobot(const UINT32* pSvrID_, UINT8 byCnt_,
	const NArenaGS::TVecLadderRobot& vecRobot //机器人排行信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 5;
	try
	{
		ar << byProtID_ << byFuncID_ << vecRobot;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 31, Function: 5";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CCenter2DBCommSvr::BuildPkg_SendAllRobot(
	const NArenaGS::TVecLadderRobot& vecRobot //机器人排行信息
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 5;
	try
	{
		ar << byProtID_ << byFuncID_ << vecRobot;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 31, Function: 5";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：返回请求排行榜数据
bool CCenter2DBCommSvr::Send_RankInitNotify(
	UINT32 dwCurSize, //已发送条数
	UINT32 dwTotalSize, //总条数
	const NRankProt::TVecRankInfo& vecRankInfo //更新信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 6;
	try
	{
		ar << byProtID_ << byFuncID_ << dwCurSize << dwTotalSize << vecRankInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 31, Function: 6";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CCenter2DBCommSvr::SendSvr_RankInitNotify(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT32 dwCurSize, //已发送条数
	UINT32 dwTotalSize, //总条数
	const NRankProt::TVecRankInfo& vecRankInfo //更新信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 6;
	try
	{
		ar << byProtID_ << byFuncID_ << dwCurSize << dwTotalSize << vecRankInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 31, Function: 6";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CCenter2DBCommSvr::BuildPkg_RankInitNotify(
	UINT32 dwCurSize, //已发送条数
	UINT32 dwTotalSize, //总条数
	const NRankProt::TVecRankInfo& vecRankInfo //更新信息
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 6;
	try
	{
		ar << byProtID_ << byFuncID_ << dwCurSize << dwTotalSize << vecRankInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 31, Function: 6";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：返回请求崇拜数据
bool CCenter2DBCommSvr::Send_AdoreInitNotify(
	UINT32 dwCurSize, //已发送条数
	UINT32 dwTotalSize, //总条数
	const NRankProt::TVecDBAdoreInfo& vecAdoreInfo //更新信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 7;
	try
	{
		ar << byProtID_ << byFuncID_ << dwCurSize << dwTotalSize << vecAdoreInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 31, Function: 7";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CCenter2DBCommSvr::SendSvr_AdoreInitNotify(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT32 dwCurSize, //已发送条数
	UINT32 dwTotalSize, //总条数
	const NRankProt::TVecDBAdoreInfo& vecAdoreInfo //更新信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 7;
	try
	{
		ar << byProtID_ << byFuncID_ << dwCurSize << dwTotalSize << vecAdoreInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 31, Function: 7";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CCenter2DBCommSvr::BuildPkg_AdoreInitNotify(
	UINT32 dwCurSize, //已发送条数
	UINT32 dwTotalSize, //总条数
	const NRankProt::TVecDBAdoreInfo& vecAdoreInfo //更新信息
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 7;
	try
	{
		ar << byProtID_ << byFuncID_ << dwCurSize << dwTotalSize << vecAdoreInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 31, Function: 7";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：返回所有九疑鼎信息
bool CCenter2DBCommSvr::Send_SendAllTripod(
	UINT32 dwPageSize, //已发送条数
	UINT32 dwTotalSize, //总条数
	const NTripodProt::TVecTripodData& vecSendData //更新信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 8;
	try
	{
		ar << byProtID_ << byFuncID_ << dwPageSize << dwTotalSize << vecSendData;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 31, Function: 8";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CCenter2DBCommSvr::SendSvr_SendAllTripod(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT32 dwPageSize, //已发送条数
	UINT32 dwTotalSize, //总条数
	const NTripodProt::TVecTripodData& vecSendData //更新信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 8;
	try
	{
		ar << byProtID_ << byFuncID_ << dwPageSize << dwTotalSize << vecSendData;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 31, Function: 8";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CCenter2DBCommSvr::BuildPkg_SendAllTripod(
	UINT32 dwPageSize, //已发送条数
	UINT32 dwTotalSize, //总条数
	const NTripodProt::TVecTripodData& vecSendData //更新信息
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 8;
	try
	{
		ar << byProtID_ << byFuncID_ << dwPageSize << dwTotalSize << vecSendData;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 31, Function: 8";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：返回所有九疑鼎的协助信息
bool CCenter2DBCommSvr::Send_SendAllTripodHelper(
	UINT32 dwPageSize, //已发送条数
	UINT32 dwTotalSize, //总条数
	const NTripodProt::TVecTripodHelp& vecSendData //更新信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 9;
	try
	{
		ar << byProtID_ << byFuncID_ << dwPageSize << dwTotalSize << vecSendData;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 31, Function: 9";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CCenter2DBCommSvr::SendSvr_SendAllTripodHelper(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT32 dwPageSize, //已发送条数
	UINT32 dwTotalSize, //总条数
	const NTripodProt::TVecTripodHelp& vecSendData //更新信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 9;
	try
	{
		ar << byProtID_ << byFuncID_ << dwPageSize << dwTotalSize << vecSendData;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 31, Function: 9";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CCenter2DBCommSvr::BuildPkg_SendAllTripodHelper(
	UINT32 dwPageSize, //已发送条数
	UINT32 dwTotalSize, //总条数
	const NTripodProt::TVecTripodHelp& vecSendData //更新信息
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 9;
	try
	{
		ar << byProtID_ << byFuncID_ << dwPageSize << dwTotalSize << vecSendData;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 31, Function: 9";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：返回所有九疑鼎的动态信息
bool CCenter2DBCommSvr::Send_SendAllTripodLog(
	UINT32 dwPageSize, //已发送条数
	UINT32 dwTotalSize, //总条数
	const NTripodProt::TVecTripodLog& vecSendData //更新信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 10;
	try
	{
		ar << byProtID_ << byFuncID_ << dwPageSize << dwTotalSize << vecSendData;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 31, Function: 10";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CCenter2DBCommSvr::SendSvr_SendAllTripodLog(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT32 dwPageSize, //已发送条数
	UINT32 dwTotalSize, //总条数
	const NTripodProt::TVecTripodLog& vecSendData //更新信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 10;
	try
	{
		ar << byProtID_ << byFuncID_ << dwPageSize << dwTotalSize << vecSendData;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 31, Function: 10";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CCenter2DBCommSvr::BuildPkg_SendAllTripodLog(
	UINT32 dwPageSize, //已发送条数
	UINT32 dwTotalSize, //总条数
	const NTripodProt::TVecTripodLog& vecSendData //更新信息
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 10;
	try
	{
		ar << byProtID_ << byFuncID_ << dwPageSize << dwTotalSize << vecSendData;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 31, Function: 10";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：平台参数加载返回
bool CCenter2DBCommSvr::Send_PlatformParamInfoNotify(
	UINT32 dwCurSize, //已发送条数
	UINT32 dwTotalSize, //总条数
	const TVecUINT64& vecRoleID, //玩家ID
	const NProtoCommon::TVecPlatformParam& vecPlatformParam //更新信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 11;
	try
	{
		ar << byProtID_ << byFuncID_ << dwCurSize << dwTotalSize << vecRoleID << vecPlatformParam;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 31, Function: 11";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CCenter2DBCommSvr::SendSvr_PlatformParamInfoNotify(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT32 dwCurSize, //已发送条数
	UINT32 dwTotalSize, //总条数
	const TVecUINT64& vecRoleID, //玩家ID
	const NProtoCommon::TVecPlatformParam& vecPlatformParam //更新信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 11;
	try
	{
		ar << byProtID_ << byFuncID_ << dwCurSize << dwTotalSize << vecRoleID << vecPlatformParam;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 31, Function: 11";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CCenter2DBCommSvr::BuildPkg_PlatformParamInfoNotify(
	UINT32 dwCurSize, //已发送条数
	UINT32 dwTotalSize, //总条数
	const TVecUINT64& vecRoleID, //玩家ID
	const NProtoCommon::TVecPlatformParam& vecPlatformParam //更新信息
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 11;
	try
	{
		ar << byProtID_ << byFuncID_ << dwCurSize << dwTotalSize << vecRoleID << vecPlatformParam;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 31, Function: 11";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：返回请求金船信息
bool CCenter2DBCommSvr::Send_SendAllShip(
	UINT32 dwPageSize, //已发送条数
	UINT32 dwTotalSize, //总条数
	const NShipProt::TVecPlayerShip& vecSendDate //更新信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 12;
	try
	{
		ar << byProtID_ << byFuncID_ << dwPageSize << dwTotalSize << vecSendDate;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 31, Function: 12";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CCenter2DBCommSvr::SendSvr_SendAllShip(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT32 dwPageSize, //已发送条数
	UINT32 dwTotalSize, //总条数
	const NShipProt::TVecPlayerShip& vecSendDate //更新信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 12;
	try
	{
		ar << byProtID_ << byFuncID_ << dwPageSize << dwTotalSize << vecSendDate;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 31, Function: 12";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CCenter2DBCommSvr::BuildPkg_SendAllShip(
	UINT32 dwPageSize, //已发送条数
	UINT32 dwTotalSize, //总条数
	const NShipProt::TVecPlayerShip& vecSendDate //更新信息
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 12;
	try
	{
		ar << byProtID_ << byFuncID_ << dwPageSize << dwTotalSize << vecSendDate;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 31, Function: 12";
		_strPkg.clear();
	}
	return _strPkg;
}

bool CCenter2DBCommSvr::_DoRecv_KeepAlive(const char* pBuf_, UINT32 dwLen_)
{
	OnRecv_KeepAlive();
	return true;
}

CCenter2DBCommSvr::SGetStatusAck::SGetStatusAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID) { }

void CCenter2DBCommSvr::SGetStatusAck::SendReturn(bool bRet_)
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
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 31, Function: 2";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CCenter2DBCommSvr::_DoRecv_GetStatus(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 31, Function: 2";
		return false;
	}
	shared_func<SGetStatusAck> fnAck_(new SGetStatusAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetStatus(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

bool CCenter2DBCommSvr::_DoRecv_InsertRecharge(const char* pBuf_, UINT32 dwLen_)
{
	NRoleInfoDefine::SRecharge oRecharge;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> oRecharge;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 31, Function: 3";
		return false;
	}
	OnRecv_InsertRecharge(oRecharge);
	return true;
}

CCenter2DBCommSvr::SLoadPrepaidAck::SLoadPrepaidAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID) { }

void CCenter2DBCommSvr::SLoadPrepaidAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -2;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << vecPrepaid;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 31, Function: 4";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CCenter2DBCommSvr::_DoRecv_LoadPrepaid(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 31, Function: 4";
		return false;
	}
	shared_func<SLoadPrepaidAck> fnAck_(new SLoadPrepaidAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_LoadPrepaid(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

bool CCenter2DBCommSvr::_DoRecv_UpdatePrepaid(const char* pBuf_, UINT32 dwLen_)
{
	NProtoCommon::EDataChange eUpdateType = (NProtoCommon::EDataChange)0;
	UINT64 qwRoleID = 0;
	UINT32 dwGold = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> (UINT8&)eUpdateType >> qwRoleID >> dwGold;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 31, Function: 5";
		return false;
	}
	OnRecv_UpdatePrepaid(eUpdateType, qwRoleID, dwGold);
	return true;
}

CCenter2DBCommSvr::SReplaceUserAck::SReplaceUserAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID) { }

void CCenter2DBCommSvr::SReplaceUserAck::SendReturn(bool bRet_)
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
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 31, Function: 6";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CCenter2DBCommSvr::_DoRecv_ReplaceUser(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 31, Function: 6";
		return false;
	}
	shared_func<SReplaceUserAck> fnAck_(new SReplaceUserAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_ReplaceUser(qwUsrID, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CCenter2DBCommSvr::SLoadOffLineUserDataAck::SLoadOffLineUserDataAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID), 
			byRet(0) { }

void CCenter2DBCommSvr::SLoadOffLineUserDataAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -4;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << byRet << RoleData;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 31, Function: 7";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CCenter2DBCommSvr::_DoRecv_LoadOffLineUserData(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 31, Function: 7";
		return false;
	}
	shared_func<SLoadOffLineUserDataAck> fnAck_(new SLoadOffLineUserDataAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_LoadOffLineUserData(qwUsrID, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

bool CCenter2DBCommSvr::_DoRecv_RoleDataUpdate(const char* pBuf_, UINT32 dwLen_)
{
	UINT64 qwRoleId = 0;
	NRoleInfoDefine::EDataType eDataType = (NRoleInfoDefine::EDataType)0;
	NProtoCommon::EDataChange eUpdateType = (NProtoCommon::EDataChange)0;
	std::string strData;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> qwRoleId >> (UINT8&)eDataType >> (UINT8&)eUpdateType >> strData;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 31, Function: 8";
		return false;
	}
	OnRecv_RoleDataUpdate(qwRoleId, eDataType, eUpdateType, strData);
	return true;
}

bool CCenter2DBCommSvr::_DoRecv_GetRankInfo(const char* pBuf_, UINT32 dwLen_)
{
	OnRecv_GetRankInfo();
	return true;
}

bool CCenter2DBCommSvr::_DoRecv_RankDataUpdate(const char* pBuf_, UINT32 dwLen_)
{
	UINT64 qwInstID = 0;
	NRankProt::ERankType eDataType = (NRankProt::ERankType)0;
	NProtoCommon::EDataChange eUpdateType = (NProtoCommon::EDataChange)0;
	std::string strData;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> qwInstID >> (UINT8&)eDataType >> (UINT8&)eUpdateType >> strData;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 31, Function: 10";
		return false;
	}
	OnRecv_RankDataUpdate(qwInstID, eDataType, eUpdateType, strData);
	return true;
}

bool CCenter2DBCommSvr::_DoRecv_GetAdoreInfo(const char* pBuf_, UINT32 dwLen_)
{
	OnRecv_GetAdoreInfo();
	return true;
}

bool CCenter2DBCommSvr::_DoRecv_AdoreDataUpdate(const char* pBuf_, UINT32 dwLen_)
{
	UINT64 qwInstID = 0;
	NProtoCommon::EDataChange eUpdateType = (NProtoCommon::EDataChange)0;
	std::string strData;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> qwInstID >> (UINT8&)eUpdateType >> strData;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 31, Function: 12";
		return false;
	}
	OnRecv_AdoreDataUpdate(qwInstID, eUpdateType, strData);
	return true;
}

bool CCenter2DBCommSvr::_DoRecv_UserIDNameReq(const char* pBuf_, UINT32 dwLen_)
{
	NServerCommon::EUserReqType eType = (NServerCommon::EUserReqType)0;
	UINT64 qwUsrID = 0;
	std::string strName;
	UINT64 qwUsrData = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> (UINT8&)eType >> qwUsrID >> strName >> qwUsrData;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 31, Function: 13";
		return false;
	}
	OnRecv_UserIDNameReq(eType, qwUsrID, strName, qwUsrData);
	return true;
}

CCenter2DBCommSvr::SGetUserIDFromNameAck::SGetUserIDFromNameAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID), 
			qwUsrID(0) { }

void CCenter2DBCommSvr::SGetUserIDFromNameAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -5;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << qwUsrID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 31, Function: 14";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CCenter2DBCommSvr::_DoRecv_GetUserIDFromName(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	std::string strName;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> strName;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 31, Function: 14";
		return false;
	}
	shared_func<SGetUserIDFromNameAck> fnAck_(new SGetUserIDFromNameAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetUserIDFromName(strName, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CCenter2DBCommSvr::SGetAllMailListAck::SGetAllMailListAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID) { }

void CCenter2DBCommSvr::SGetAllMailListAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -6;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << vecMails;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 31, Function: 15";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CCenter2DBCommSvr::_DoRecv_GetAllMailList(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT64 qwRoleID = 0;
	UINT32 dwOverTime = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> qwRoleID >> dwOverTime;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 31, Function: 15";
		return false;
	}
	shared_func<SGetAllMailListAck> fnAck_(new SGetAllMailListAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetAllMailList(qwRoleID, dwOverTime, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CCenter2DBCommSvr::SSaveMailAck::SSaveMailAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID), 
			byRet(0) { }

void CCenter2DBCommSvr::SSaveMailAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -7;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << byRet;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 31, Function: 16";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CCenter2DBCommSvr::_DoRecv_SaveMail(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT64 qwMailID = 0;
	UINT64 qwReceiveID = 0;
	UINT64 qwSenderID = 0;
	std::string strSenderName;
	NMailProt::EMailType eMailType = (NMailProt::EMailType)0;
	NMailProt::EMailState eMailState = (NMailProt::EMailState)0;
	UINT32 dwSendTime = 0;
	std::string strTitle;
	std::string strMsg;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> qwMailID >> qwReceiveID >> qwSenderID >> strSenderName >> (UINT8&)eMailType >> (UINT8&)eMailState >> dwSendTime >> strTitle >> strMsg;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 31, Function: 16";
		return false;
	}
	shared_func<SSaveMailAck> fnAck_(new SSaveMailAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_SaveMail(qwMailID, qwReceiveID, qwSenderID, strSenderName, eMailType, eMailState, dwSendTime, strTitle, strMsg, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CCenter2DBCommSvr::SDeleteMailAck::SDeleteMailAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID), 
			byRet(0) { }

void CCenter2DBCommSvr::SDeleteMailAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -8;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << byRet;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 31, Function: 17";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CCenter2DBCommSvr::_DoRecv_DeleteMail(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT64 qwRoleID = 0;
	TVecMailDelData vecMailIDs;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> qwRoleID >> vecMailIDs;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 31, Function: 17";
		return false;
	}
	shared_func<SDeleteMailAck> fnAck_(new SDeleteMailAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_DeleteMail(qwRoleID, vecMailIDs, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CCenter2DBCommSvr::SSaveSystemMailAck::SSaveSystemMailAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID), 
			byRet(0) { }

void CCenter2DBCommSvr::SSaveSystemMailAck::SendReturn(bool bRet_)
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
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 31, Function: 18";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CCenter2DBCommSvr::_DoRecv_SaveSystemMail(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	TVecSystemMailTargetInfo vecSystemMailTargetInfo;
	SSystemMailInfo rSystemMailInfo;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> vecSystemMailTargetInfo >> rSystemMailInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 31, Function: 18";
		return false;
	}
	shared_func<SSaveSystemMailAck> fnAck_(new SSaveSystemMailAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_SaveSystemMail(vecSystemMailTargetInfo, rSystemMailInfo, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CCenter2DBCommSvr::SUpdateMailStatusAck::SUpdateMailStatusAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID), 
			byRet(0) { }

void CCenter2DBCommSvr::SUpdateMailStatusAck::SendReturn(bool bRet_)
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
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 31, Function: 19";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CCenter2DBCommSvr::_DoRecv_UpdateMailStatus(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT64 qwMailID = 0;
	NMailProt::EMailState eMailState = (NMailProt::EMailState)0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> qwMailID >> (UINT8&)eMailState;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 31, Function: 19";
		return false;
	}
	shared_func<SUpdateMailStatusAck> fnAck_(new SUpdateMailStatusAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_UpdateMailStatus(qwMailID, eMailState, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CCenter2DBCommSvr::SDelMailAttachAck::SDelMailAttachAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID), 
			byRet(0) { }

void CCenter2DBCommSvr::SDelMailAttachAck::SendReturn(bool bRet_)
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
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 31, Function: 20";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CCenter2DBCommSvr::_DoRecv_DelMailAttach(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	MailDelData stDelData;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> stDelData;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 31, Function: 20";
		return false;
	}
	shared_func<SDelMailAttachAck> fnAck_(new SDelMailAttachAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_DelMailAttach(stDelData, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CCenter2DBCommSvr::SGetPrizeStatusAck::SGetPrizeStatusAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID) { }

void CCenter2DBCommSvr::SGetPrizeStatusAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -12;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << vecRet;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 31, Function: 21";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CCenter2DBCommSvr::_DoRecv_GetPrizeStatus(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 31, Function: 21";
		return false;
	}
	shared_func<SGetPrizeStatusAck> fnAck_(new SGetPrizeStatusAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetPrizeStatus(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

bool CCenter2DBCommSvr::_DoRecv_DelActPrizeData(const char* pBuf_, UINT32 dwLen_)
{
	UINT16 wActID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> wActID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 31, Function: 22";
		return false;
	}
	OnRecv_DelActPrizeData(wActID);
	return true;
}

CCenter2DBCommSvr::SGetAllRoleLevelAck::SGetAllRoleLevelAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID), 
			byTypeRet(0) { }

void CCenter2DBCommSvr::SGetAllRoleLevelAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -13;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << byTypeRet << vecRoleLevel;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 31, Function: 23";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CCenter2DBCommSvr::_DoRecv_GetAllRoleLevel(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT8 byType = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> byType;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 31, Function: 23";
		return false;
	}
	shared_func<SGetAllRoleLevelAck> fnAck_(new SGetAllRoleLevelAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetAllRoleLevel(byType, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

bool CCenter2DBCommSvr::_DoRecv_UpdatePrizeStatus(const char* pBuf_, UINT32 dwLen_)
{
	NWonderActivityProt::SWonderPrize2DB sPrize2DB;
	NProtoCommon::EDataChange eUpdateType = (NProtoCommon::EDataChange)0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> sPrize2DB >> (UINT8&)eUpdateType;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 31, Function: 24";
		return false;
	}
	OnRecv_UpdatePrizeStatus(sPrize2DB, eUpdateType);
	return true;
}

CCenter2DBCommSvr::SGetRetainAck::SGetRetainAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID) { }

void CCenter2DBCommSvr::SGetRetainAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -14;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << vecRet;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 31, Function: 25";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CCenter2DBCommSvr::_DoRecv_GetRetain(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 31, Function: 25";
		return false;
	}
	shared_func<SGetRetainAck> fnAck_(new SGetRetainAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetRetain(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

bool CCenter2DBCommSvr::_DoRecv_UpdateRetain(const char* pBuf_, UINT32 dwLen_)
{
	NWonderActivityProt::SRetain sRetain;
	NProtoCommon::EDataChange eUpdateType = (NProtoCommon::EDataChange)0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> sRetain >> (UINT8&)eUpdateType;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 31, Function: 26";
		return false;
	}
	OnRecv_UpdateRetain(sRetain, eUpdateType);
	return true;
}

bool CCenter2DBCommSvr::_DoRecv_DelActRetainData(const char* pBuf_, UINT32 dwLen_)
{
	UINT16 wActID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> wActID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 31, Function: 27";
		return false;
	}
	OnRecv_DelActRetainData(wActID);
	return true;
}

bool CCenter2DBCommSvr::_DoRecv_GetAllUserIDAndName(const char* pBuf_, UINT32 dwLen_)
{
	OnRecv_GetAllUserIDAndName();
	return true;
}

bool CCenter2DBCommSvr::_DoRecv_GetAllNotice(const char* pBuf_, UINT32 dwLen_)
{
	OnRecv_GetAllNotice();
	return true;
}

bool CCenter2DBCommSvr::_DoRecv_AddNotice(const char* pBuf_, UINT32 dwLen_)
{
	NPHPProt::SNotice sNotice;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> sNotice;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 31, Function: 30";
		return false;
	}
	OnRecv_AddNotice(sNotice);
	return true;
}

bool CCenter2DBCommSvr::_DoRecv_DelNotice(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwNoticeID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwNoticeID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 31, Function: 31";
		return false;
	}
	OnRecv_DelNotice(dwNoticeID);
	return true;
}

bool CCenter2DBCommSvr::_DoRecv_GetAllArena(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwPageSize = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwPageSize;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 31, Function: 32";
		return false;
	}
	OnRecv_GetAllArena(dwPageSize);
	return true;
}

bool CCenter2DBCommSvr::_DoRecv_UpdateAllArena(const char* pBuf_, UINT32 dwLen_)
{
	NArenaGS::TVecArenaPlayerBaseDataUpdate vecUpdate;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> vecUpdate;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 31, Function: 33";
		return false;
	}
	OnRecv_UpdateAllArena(vecUpdate);
	return true;
}

bool CCenter2DBCommSvr::_DoRecv_DelPlayerArena(const char* pBuf_, UINT32 dwLen_)
{
	TVecUINT64 vecDel;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> vecDel;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 31, Function: 34";
		return false;
	}
	OnRecv_DelPlayerArena(vecDel);
	return true;
}

CCenter2DBCommSvr::SGetGameVarAck::SGetGameVarAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID) { }

void CCenter2DBCommSvr::SGetGameVarAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -15;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << vecVar;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 31, Function: 35";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CCenter2DBCommSvr::_DoRecv_GetGameVar(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 31, Function: 35";
		return false;
	}
	shared_func<SGetGameVarAck> fnAck_(new SGetGameVarAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetGameVar(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

bool CCenter2DBCommSvr::_DoRecv_UpdateGameVar(const char* pBuf_, UINT32 dwLen_)
{
	NRoleInfoDefine::SGameVarsDBInfo Var;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> Var;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 31, Function: 36";
		return false;
	}
	OnRecv_UpdateGameVar(Var);
	return true;
}

bool CCenter2DBCommSvr::_DoRecv_AddGameVar(const char* pBuf_, UINT32 dwLen_)
{
	NRoleInfoDefine::SGameVarsDBInfo Var;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> Var;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 31, Function: 37";
		return false;
	}
	OnRecv_AddGameVar(Var);
	return true;
}

bool CCenter2DBCommSvr::_DoRecv_DelGameVar(const char* pBuf_, UINT32 dwLen_)
{
	UINT16 wVarID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> wVarID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 31, Function: 38";
		return false;
	}
	OnRecv_DelGameVar(wVarID);
	return true;
}

CCenter2DBCommSvr::SGetArenaFighterByIDAck::SGetArenaFighterByIDAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID) { }

void CCenter2DBCommSvr::SGetArenaFighterByIDAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -16;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << stFighter;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 31, Function: 39";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CCenter2DBCommSvr::_DoRecv_GetArenaFighterByID(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 31, Function: 39";
		return false;
	}
	shared_func<SGetArenaFighterByIDAck> fnAck_(new SGetArenaFighterByIDAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetArenaFighterByID(qwRoleID, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CCenter2DBCommSvr::SGetDemonTowerInfoAck::SGetDemonTowerInfoAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID) { }

void CCenter2DBCommSvr::SGetDemonTowerInfoAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -17;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << vecDemonTowerPlayer;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 31, Function: 40";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CCenter2DBCommSvr::_DoRecv_GetDemonTowerInfo(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 31, Function: 40";
		return false;
	}
	shared_func<SGetDemonTowerInfoAck> fnAck_(new SGetDemonTowerInfoAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetDemonTowerInfo(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

bool CCenter2DBCommSvr::_DoRecv_UpateDemonTowerInfo(const char* pBuf_, UINT32 dwLen_)
{
	NDemonTowerGS::EDemonTowerDB eDbType = (NDemonTowerGS::EDemonTowerDB)0;
	NDemonTowerGS::SDemonTowerPlayer oDemonTowerPlayer;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> (UINT8&)eDbType >> oDemonTowerPlayer;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 31, Function: 41";
		return false;
	}
	OnRecv_UpateDemonTowerInfo(eDbType, oDemonTowerPlayer);
	return true;
}

CCenter2DBCommSvr::SGetCenterDataAck::SGetCenterDataAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID) { }

void CCenter2DBCommSvr::SGetCenterDataAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -18;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << vecCenterData;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 31, Function: 42";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CCenter2DBCommSvr::_DoRecv_GetCenterData(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 31, Function: 42";
		return false;
	}
	shared_func<SGetCenterDataAck> fnAck_(new SGetCenterDataAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetCenterData(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

bool CCenter2DBCommSvr::_DoRecv_UpateCenterData(const char* pBuf_, UINT32 dwLen_)
{
	SCenterData oCenterData;
	bool bDelete = false;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> oCenterData >> bDelete;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 31, Function: 43";
		return false;
	}
	OnRecv_UpateCenterData(oCenterData, bDelete);
	return true;
}

CCenter2DBCommSvr::SGetWhisperInfoAck::SGetWhisperInfoAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID) { }

void CCenter2DBCommSvr::SGetWhisperInfoAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -19;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << whisperInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 31, Function: 44";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CCenter2DBCommSvr::_DoRecv_GetWhisperInfo(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 31, Function: 44";
		return false;
	}
	shared_func<SGetWhisperInfoAck> fnAck_(new SGetWhisperInfoAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetWhisperInfo(qwRoleID, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CCenter2DBCommSvr::SGetBattleReportAck::SGetBattleReportAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID) { }

void CCenter2DBCommSvr::SGetBattleReportAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -20;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << vecReport;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 31, Function: 45";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CCenter2DBCommSvr::_DoRecv_GetBattleReport(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT64 qwRoleID = 0;
	NRoleInfoDefine::EBattleReportType eBattleType = (NRoleInfoDefine::EBattleReportType)0;
	NRoleInfoDefine::EBattleActionType eAction = (NRoleInfoDefine::EBattleActionType)0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> qwRoleID >> (UINT8&)eBattleType >> (UINT8&)eAction;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 31, Function: 45";
		return false;
	}
	shared_func<SGetBattleReportAck> fnAck_(new SGetBattleReportAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetBattleReport(qwRoleID, eBattleType, eAction, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CCenter2DBCommSvr::SAddBattleReportAck::SAddBattleReportAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID) { }

void CCenter2DBCommSvr::SAddBattleReportAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -21;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << vecBattleID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 31, Function: 46";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CCenter2DBCommSvr::_DoRecv_AddBattleReport(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT64 qwRoleID = 0;
	NRoleInfoDefine::SBattleRePort sReport;
	UINT8 byNum = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> qwRoleID >> sReport >> byNum;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 31, Function: 46";
		return false;
	}
	shared_func<SAddBattleReportAck> fnAck_(new SAddBattleReportAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_AddBattleReport(qwRoleID, sReport, byNum, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

bool CCenter2DBCommSvr::_DoRecv_ReloadTable(const char* pBuf_, UINT32 dwLen_)
{
	TVecString vecTableName;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> vecTableName;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 31, Function: 47";
		return false;
	}
	OnRecv_ReloadTable(vecTableName);
	return true;
}

bool CCenter2DBCommSvr::_DoRecv_GetAllTripod(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwPageSize = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwPageSize;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 31, Function: 48";
		return false;
	}
	OnRecv_GetAllTripod(dwPageSize);
	return true;
}

bool CCenter2DBCommSvr::_DoRecv_GetAllTripodHelper(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwPageSize = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwPageSize;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 31, Function: 49";
		return false;
	}
	OnRecv_GetAllTripodHelper(dwPageSize);
	return true;
}

bool CCenter2DBCommSvr::_DoRecv_GetAllTripodLog(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwPageSize = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwPageSize;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 31, Function: 50";
		return false;
	}
	OnRecv_GetAllTripodLog(dwPageSize);
	return true;
}

bool CCenter2DBCommSvr::_DoRecv_UpdateTripod(const char* pBuf_, UINT32 dwLen_)
{
	UINT64 qwRoleID = 0;
	NTripodProt::STripodInfo oTripodInfo;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> qwRoleID >> oTripodInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 31, Function: 51";
		return false;
	}
	OnRecv_UpdateTripod(qwRoleID, oTripodInfo);
	return true;
}

bool CCenter2DBCommSvr::_DoRecv_UpateTripodHelp(const char* pBuf_, UINT32 dwLen_)
{
	NProtoCommon::EDataChange eUpdateType = (NProtoCommon::EDataChange)0;
	NTripodProt::STripodHelp oTripodHelp;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> (UINT8&)eUpdateType >> oTripodHelp;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 31, Function: 52";
		return false;
	}
	OnRecv_UpateTripodHelp(eUpdateType, oTripodHelp);
	return true;
}

bool CCenter2DBCommSvr::_DoRecv_UpdateTripodLog(const char* pBuf_, UINT32 dwLen_)
{
	UINT64 qwRoleID = 0;
	NProtoCommon::EDataChange eUpdateType = (NProtoCommon::EDataChange)0;
	NTripodProt::STripodLog oTripodLog;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> qwRoleID >> (UINT8&)eUpdateType >> oTripodLog;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 31, Function: 53";
		return false;
	}
	OnRecv_UpdateTripodLog(qwRoleID, eUpdateType, oTripodLog);
	return true;
}

bool CCenter2DBCommSvr::_DoRecv_AddOffLineEvent(const char* pBuf_, UINT32 dwLen_)
{
	TVecUINT64 vecRoleID;
	NRoleInfoDefine::SEventOffLine sEventData;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> vecRoleID >> sEventData;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 31, Function: 54";
		return false;
	}
	OnRecv_AddOffLineEvent(vecRoleID, sEventData);
	return true;
}

bool CCenter2DBCommSvr::_DoRecv_FreezePlayer(const char* pBuf_, UINT32 dwLen_)
{
	UINT64 qwRoleID = 0;
	UINT32 dwFreezeTimer = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> qwRoleID >> dwFreezeTimer;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 31, Function: 55";
		return false;
	}
	OnRecv_FreezePlayer(qwRoleID, dwFreezeTimer);
	return true;
}

bool CCenter2DBCommSvr::_DoRecv_ForbitChat(const char* pBuf_, UINT32 dwLen_)
{
	UINT64 qwRoleID = 0;
	UINT32 dwForbitTimer = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> qwRoleID >> dwForbitTimer;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 31, Function: 56";
		return false;
	}
	OnRecv_ForbitChat(qwRoleID, dwForbitTimer);
	return true;
}

bool CCenter2DBCommSvr::_DoRecv_UpdateLoginIP(const char* pBuf_, UINT32 dwLen_)
{
	UINT64 qwUserID = 0;
	std::string strLoginIP;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> qwUserID >> strLoginIP;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 31, Function: 57";
		return false;
	}
	OnRecv_UpdateLoginIP(qwUserID, strLoginIP);
	return true;
}

bool CCenter2DBCommSvr::_DoRecv_GetPlatformParam(const char* pBuf_, UINT32 dwLen_)
{
	OnRecv_GetPlatformParam();
	return true;
}

bool CCenter2DBCommSvr::_DoRecv_GetResult2DB(const char* pBuf_, UINT32 dwLen_)
{
	SBaseCond sBaseCond;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> sBaseCond;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 31, Function: 59";
		return false;
	}
	OnRecv_GetResult2DB(sBaseCond);
	return true;
}

bool CCenter2DBCommSvr::_DoRecv_GetAllShip(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwPageSize = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwPageSize;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 31, Function: 60";
		return false;
	}
	OnRecv_GetAllShip(dwPageSize);
	return true;
}

bool CCenter2DBCommSvr::_DoRecv_UpdateShip(const char* pBuf_, UINT32 dwLen_)
{
	NShipProt::PlayerShip UpdateInfo;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> UpdateInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 31, Function: 61";
		return false;
	}
	OnRecv_UpdateShip(UpdateInfo);
	return true;
}

bool CCenter2DBCommSvr::_DoRecv_DelShip(const char* pBuf_, UINT32 dwLen_)
{
	UINT64 qwInsID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> qwInsID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 31, Function: 62";
		return false;
	}
	OnRecv_DelShip(qwInsID);
	return true;
}

bool CCenter2DBCommSvr::_DoRecv_AddShipReport(const char* pBuf_, UINT32 dwLen_)
{
	UINT64 qwRoleID = 0;
	NShipProt::ShipReport sReport;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> qwRoleID >> sReport;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 31, Function: 63";
		return false;
	}
	OnRecv_AddShipReport(qwRoleID, sReport);
	return true;
}

bool CCenter2DBCommSvr::_DoRecv_DelShipReport(const char* pBuf_, UINT32 dwLen_)
{
	UINT64 qwRoleID = 0;
	UINT64 qwInsID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> qwRoleID >> qwInsID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 31, Function: 64";
		return false;
	}
	OnRecv_DelShipReport(qwRoleID, qwInsID);
	return true;
}

bool CCenter2DBCommSvr::_DoRecv_SyncMonsterUserInfo(const char* pBuf_, UINT32 dwLen_)
{
	NProtoCommon::EDataChange eUpdateType = (NProtoCommon::EDataChange)0;
	NGodMonsterProt::SGuildUser2DB sUser;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> (UINT8&)eUpdateType >> sUser;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 31, Function: 65";
		return false;
	}
	OnRecv_SyncMonsterUserInfo(eUpdateType, sUser);
	return true;
}

CCenter2DBCommSvr::SGetGodMonsterInfoAck::SGetGodMonsterInfoAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID) { }

void CCenter2DBCommSvr::SGetGodMonsterInfoAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -22;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << vecUser;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 31, Function: 66";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CCenter2DBCommSvr::_DoRecv_GetGodMonsterInfo(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 31, Function: 66";
		return false;
	}
	shared_func<SGetGodMonsterInfoAck> fnAck_(new SGetGodMonsterInfoAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetGodMonsterInfo(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

bool CCenter2DBCommSvr::_DoRecv_SyncLimitPrizeInfo(const char* pBuf_, UINT32 dwLen_)
{
	NProtoCommon::EDataChange eUpdateType = (NProtoCommon::EDataChange)0;
	NGodMonsterProt::SLimitPrize2DB oLimitPrize;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> (UINT8&)eUpdateType >> oLimitPrize;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 31, Function: 67";
		return false;
	}
	OnRecv_SyncLimitPrizeInfo(eUpdateType, oLimitPrize);
	return true;
}

CCenter2DBCommSvr::SGetLimitPrizeInfoAck::SGetLimitPrizeInfoAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID) { }

void CCenter2DBCommSvr::SGetLimitPrizeInfoAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -23;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << vecLimitPrize;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 31, Function: 68";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CCenter2DBCommSvr::_DoRecv_GetLimitPrizeInfo(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 31, Function: 68";
		return false;
	}
	shared_func<SGetLimitPrizeInfoAck> fnAck_(new SGetLimitPrizeInfoAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetLimitPrizeInfo(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

bool CCenter2DBCommSvr::_DoRecv_SyncActivityCenterInfo(const char* pBuf_, UINT32 dwLen_)
{
	NProtoCommon::EDataChange eUpdateType = (NProtoCommon::EDataChange)0;
	NProtoCommon::SActivityOpt oActOpt;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> (UINT8&)eUpdateType >> oActOpt;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 31, Function: 69";
		return false;
	}
	OnRecv_SyncActivityCenterInfo(eUpdateType, oActOpt);
	return true;
}

CCenter2DBCommSvr::SGetActivityCenterInfoAck::SGetActivityCenterInfoAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID) { }

void CCenter2DBCommSvr::SGetActivityCenterInfoAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -24;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << vecActOpt;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 31, Function: 70";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CCenter2DBCommSvr::_DoRecv_GetActivityCenterInfo(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 31, Function: 70";
		return false;
	}
	shared_func<SGetActivityCenterInfoAck> fnAck_(new SGetActivityCenterInfoAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetActivityCenterInfo(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

bool CCenter2DBCommSvr::_DoRecv_AddLadderRobot(const char* pBuf_, UINT32 dwLen_)
{
	NArenaGS::TVecLadderRobot vecData;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> vecData;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 31, Function: 71";
		return false;
	}
	OnRecv_AddLadderRobot(vecData);
	return true;
}

bool CCenter2DBCommSvr::_DoRecv_UpdateLadderRobot(const char* pBuf_, UINT32 dwLen_)
{
	NArenaGS::SLadderRobot SData;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> SData;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 31, Function: 72";
		return false;
	}
	OnRecv_UpdateLadderRobot(SData);
	return true;
}

} //namespace NCenter2DBComm
