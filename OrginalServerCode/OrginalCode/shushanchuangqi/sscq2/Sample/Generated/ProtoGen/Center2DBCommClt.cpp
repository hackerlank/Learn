/************************************************************************
//  工具自动生成的客户端协议代码(UTF-8 With BOM)
//  File Name:    Center2DBComm.cpp
//  Purpose:      CenterServer到DBServer的通信协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "Center2DBCommClt.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NCenter2DBComm
{

CCenter2DBCommClt::THandleFunc CCenter2DBCommClt::_ReturnFuncs[] =
{
	&CCenter2DBCommClt::_DoReturn_GetStatus, //FuncID: -1
	&CCenter2DBCommClt::_DoReturn_LoadPrepaid, //FuncID: -2
	&CCenter2DBCommClt::_DoReturn_ReplaceUser, //FuncID: -3
	&CCenter2DBCommClt::_DoReturn_LoadOffLineUserData, //FuncID: -4
	&CCenter2DBCommClt::_DoReturn_GetUserIDFromName, //FuncID: -5
	&CCenter2DBCommClt::_DoReturn_GetAllMailList, //FuncID: -6
	&CCenter2DBCommClt::_DoReturn_SaveMail, //FuncID: -7
	&CCenter2DBCommClt::_DoReturn_DeleteMail, //FuncID: -8
	&CCenter2DBCommClt::_DoReturn_SaveSystemMail, //FuncID: -9
	&CCenter2DBCommClt::_DoReturn_UpdateMailStatus, //FuncID: -10
	&CCenter2DBCommClt::_DoReturn_DelMailAttach, //FuncID: -11
	&CCenter2DBCommClt::_DoReturn_GetPrizeStatus, //FuncID: -12
	&CCenter2DBCommClt::_DoReturn_GetAllRoleLevel, //FuncID: -13
	&CCenter2DBCommClt::_DoReturn_GetRetain, //FuncID: -14
	&CCenter2DBCommClt::_DoReturn_GetGameVar, //FuncID: -15
	&CCenter2DBCommClt::_DoReturn_GetArenaFighterByID, //FuncID: -16
	&CCenter2DBCommClt::_DoReturn_GetDemonTowerInfo, //FuncID: -17
	&CCenter2DBCommClt::_DoReturn_GetCenterData, //FuncID: -18
	&CCenter2DBCommClt::_DoReturn_GetWhisperInfo, //FuncID: -19
	&CCenter2DBCommClt::_DoReturn_GetBattleReport, //FuncID: -20
	&CCenter2DBCommClt::_DoReturn_AddBattleReport, //FuncID: -21
	&CCenter2DBCommClt::_DoReturn_GetGodMonsterInfo, //FuncID: -22
	&CCenter2DBCommClt::_DoReturn_GetLimitPrizeInfo, //FuncID: -23
	&CCenter2DBCommClt::_DoReturn_GetActivityCenterInfo, //FuncID: -24
};

CCenter2DBCommClt::THandleFunc CCenter2DBCommClt::_HandleFuncs[] =
{
	&CCenter2DBCommClt::_DoRecv_SendResult2Cent, //FuncID: 1
	&CCenter2DBCommClt::_DoRecv_SendAllUserIDAndName, //FuncID: 2
	&CCenter2DBCommClt::_DoRecv_SendAllNotice, //FuncID: 3
	&CCenter2DBCommClt::_DoRecv_SendAllArena, //FuncID: 4
	&CCenter2DBCommClt::_DoRecv_SendAllRobot, //FuncID: 5
	&CCenter2DBCommClt::_DoRecv_RankInitNotify, //FuncID: 6
	&CCenter2DBCommClt::_DoRecv_AdoreInitNotify, //FuncID: 7
	&CCenter2DBCommClt::_DoRecv_SendAllTripod, //FuncID: 8
	&CCenter2DBCommClt::_DoRecv_SendAllTripodHelper, //FuncID: 9
	&CCenter2DBCommClt::_DoRecv_SendAllTripodLog, //FuncID: 10
	&CCenter2DBCommClt::_DoRecv_PlatformParamInfoNotify, //FuncID: 11
	&CCenter2DBCommClt::_DoRecv_SendAllShip, //FuncID: 12
};

CCenter2DBCommClt::TTimeOutFunc CCenter2DBCommClt::_TimeoutFuncs[] =
{
	&CCenter2DBCommClt::_OnTimeOut_GetStatus, //FuncID: 1
	&CCenter2DBCommClt::_OnTimeOut_LoadPrepaid, //FuncID: 2
	&CCenter2DBCommClt::_OnTimeOut_ReplaceUser, //FuncID: 3
	&CCenter2DBCommClt::_OnTimeOut_LoadOffLineUserData, //FuncID: 4
	&CCenter2DBCommClt::_OnTimeOut_GetUserIDFromName, //FuncID: 5
	&CCenter2DBCommClt::_OnTimeOut_GetAllMailList, //FuncID: 6
	&CCenter2DBCommClt::_OnTimeOut_SaveMail, //FuncID: 7
	&CCenter2DBCommClt::_OnTimeOut_DeleteMail, //FuncID: 8
	&CCenter2DBCommClt::_OnTimeOut_SaveSystemMail, //FuncID: 9
	&CCenter2DBCommClt::_OnTimeOut_UpdateMailStatus, //FuncID: 10
	&CCenter2DBCommClt::_OnTimeOut_DelMailAttach, //FuncID: 11
	&CCenter2DBCommClt::_OnTimeOut_GetPrizeStatus, //FuncID: 12
	&CCenter2DBCommClt::_OnTimeOut_GetAllRoleLevel, //FuncID: 13
	&CCenter2DBCommClt::_OnTimeOut_GetRetain, //FuncID: 14
	&CCenter2DBCommClt::_OnTimeOut_GetGameVar, //FuncID: 15
	&CCenter2DBCommClt::_OnTimeOut_GetArenaFighterByID, //FuncID: 16
	&CCenter2DBCommClt::_OnTimeOut_GetDemonTowerInfo, //FuncID: 17
	&CCenter2DBCommClt::_OnTimeOut_GetCenterData, //FuncID: 18
	&CCenter2DBCommClt::_OnTimeOut_GetWhisperInfo, //FuncID: 19
	&CCenter2DBCommClt::_OnTimeOut_GetBattleReport, //FuncID: 20
	&CCenter2DBCommClt::_OnTimeOut_AddBattleReport, //FuncID: 21
	&CCenter2DBCommClt::_OnTimeOut_GetGodMonsterInfo, //FuncID: 22
	&CCenter2DBCommClt::_OnTimeOut_GetLimitPrizeInfo, //FuncID: 23
	&CCenter2DBCommClt::_OnTimeOut_GetActivityCenterInfo, //FuncID: 24
};

bool CCenter2DBCommClt::HandleMessage(const char* pBuf, UINT32 dwLen)
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

void CCenter2DBCommClt::OnTimeOut(UINT8 byFuncID, UINT32 dwSessionID)
{
	if(byFuncID == 0 || byFuncID > (UINT8)ARRAYSIZE(_TimeoutFuncs))
		return;
	(this->*_TimeoutFuncs[byFuncID - 1])(dwSessionID);
}

//发送：心跳
bool CCenter2DBCommClt::Send_KeepAlive(
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
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 31, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CCenter2DBCommClt::SendSvr_KeepAlive(const UINT32* pSvrID_, UINT8 byCnt_
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
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 31, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CCenter2DBCommClt::BuildPkg_KeepAlive(
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
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 31, Function: 1";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：DBServer状态请求
bool CCenter2DBCommClt::Send_GetStatus(
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
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_;
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

bool CCenter2DBCommClt::SendSvr_GetStatus(const UINT32* pSvrID_, UINT8 byCnt_,
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
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_;
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

//发送：插入玩家充值仙石信息(未创角预先充值)
bool CCenter2DBCommClt::Send_InsertRecharge(
	const NRoleInfoDefine::SRecharge& oRecharge //充值仙石的数据
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << oRecharge;
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

bool CCenter2DBCommClt::SendSvr_InsertRecharge(const UINT32* pSvrID_, UINT8 byCnt_,
	const NRoleInfoDefine::SRecharge& oRecharge //充值仙石的数据
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << oRecharge;
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

std::string& CCenter2DBCommClt::BuildPkg_InsertRecharge(
	const NRoleInfoDefine::SRecharge& oRecharge //充值仙石的数据
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << oRecharge;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 31, Function: 3";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：加载玩家未创角预先充值的仙石信息
bool CCenter2DBCommClt::Send_LoadPrepaid(
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		const NRoleInfoDefine::TVecPrepaid& vecPrepaid //(返回值)玩家未创角预先值信息
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
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_;
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

bool CCenter2DBCommClt::SendSvr_LoadPrepaid(const UINT32* pSvrID_, UINT8 byCnt_,
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		const NRoleInfoDefine::TVecPrepaid& vecPrepaid //(返回值)玩家未创角预先值信息
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
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_;
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

//发送：更新玩家未创角预先充值信息
bool CCenter2DBCommClt::Send_UpdatePrepaid(
	NProtoCommon::EDataChange eUpdateType, //更新类型，增加，删除，修改
	UINT64 qwRoleID, //玩家ID
	UINT32 dwGold //仙石数量
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 5;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eUpdateType << qwRoleID << dwGold;
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

bool CCenter2DBCommClt::SendSvr_UpdatePrepaid(const UINT32* pSvrID_, UINT8 byCnt_,
	NProtoCommon::EDataChange eUpdateType, //更新类型，增加，删除，修改
	UINT64 qwRoleID, //玩家ID
	UINT32 dwGold //仙石数量
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 5;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eUpdateType << qwRoleID << dwGold;
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

std::string& CCenter2DBCommClt::BuildPkg_UpdatePrepaid(
	NProtoCommon::EDataChange eUpdateType, //更新类型，增加，删除，修改
	UINT64 qwRoleID, //玩家ID
	UINT32 dwGold //仙石数量
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 5;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eUpdateType << qwRoleID << dwGold;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 31, Function: 5";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：替换帐号
bool CCenter2DBCommClt::Send_ReplaceUser(
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
	UINT32 dwSessionID_ = _pSessionMgr->GetNewSession(*this, 3);
	typedef std::tuple<decltype(fnOnReturn_), UINT64> TSessData;
	std::shared_ptr<TSessData> pSessData_(new TSessData(fnOnReturn_, qwUsrID));
	_pSessionMgr->StoreData(dwSessionID_, pSessData_);
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 6;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwUsrID;
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

bool CCenter2DBCommClt::SendSvr_ReplaceUser(const UINT32* pSvrID_, UINT8 byCnt_,
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
	UINT32 dwSessionID_ = _pSessionMgr->GetNewSession(*this, 3);
	typedef std::tuple<decltype(fnOnReturn_), UINT64> TSessData;
	std::shared_ptr<TSessData> pSessData_(new TSessData(fnOnReturn_, qwUsrID));
	_pSessionMgr->StoreData(dwSessionID_, pSessData_);
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 6;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwUsrID;
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

//发送：加载离线玩家数据
bool CCenter2DBCommClt::Send_LoadOffLineUserData(
	UINT64 qwUsrID, //账号ID
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT8 byRet, //(返回值)0表示成功
		const NRoleInfoDefine::RoleDataInfo& RoleData //(返回值)玩家数据
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
	const UINT8 byFuncID_ = 7;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwUsrID;
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

bool CCenter2DBCommClt::SendSvr_LoadOffLineUserData(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwUsrID, //账号ID
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT8 byRet, //(返回值)0表示成功
		const NRoleInfoDefine::RoleDataInfo& RoleData //(返回值)玩家数据
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
	const UINT8 byFuncID_ = 7;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwUsrID;
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

//发送：一行数据更新
bool CCenter2DBCommClt::Send_RoleDataUpdate(
	UINT64 qwRoleId, //角色Id
	NRoleInfoDefine::EDataType eDataType, //更新数据块
	NProtoCommon::EDataChange eUpdateType, //更新类型，增加，删除，修改
	const std::string& strData //更新数据
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 8;
	try
	{
		ar << byProtID_ << byFuncID_ << qwRoleId << (UINT8&)eDataType << (UINT8&)eUpdateType << strData;
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

bool CCenter2DBCommClt::SendSvr_RoleDataUpdate(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwRoleId, //角色Id
	NRoleInfoDefine::EDataType eDataType, //更新数据块
	NProtoCommon::EDataChange eUpdateType, //更新类型，增加，删除，修改
	const std::string& strData //更新数据
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 8;
	try
	{
		ar << byProtID_ << byFuncID_ << qwRoleId << (UINT8&)eDataType << (UINT8&)eUpdateType << strData;
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

std::string& CCenter2DBCommClt::BuildPkg_RoleDataUpdate(
	UINT64 qwRoleId, //角色Id
	NRoleInfoDefine::EDataType eDataType, //更新数据块
	NProtoCommon::EDataChange eUpdateType, //更新类型，增加，删除，修改
	const std::string& strData //更新数据
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 8;
	try
	{
		ar << byProtID_ << byFuncID_ << qwRoleId << (UINT8&)eDataType << (UINT8&)eUpdateType << strData;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 31, Function: 8";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：获取排名信息
bool CCenter2DBCommClt::Send_GetRankInfo(
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 9;
	try
	{
		ar << byProtID_ << byFuncID_;
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

bool CCenter2DBCommClt::SendSvr_GetRankInfo(const UINT32* pSvrID_, UINT8 byCnt_
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 9;
	try
	{
		ar << byProtID_ << byFuncID_;
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

std::string& CCenter2DBCommClt::BuildPkg_GetRankInfo(
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 9;
	try
	{
		ar << byProtID_ << byFuncID_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 31, Function: 9";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：排行榜数据更新
bool CCenter2DBCommClt::Send_RankDataUpdate(
	UINT64 qwInstID, //唯一ID
	NRankProt::ERankType eDataType, //更新数据类型
	NProtoCommon::EDataChange eUpdateType, //更新方式，增加，删除，修改
	const std::string& strData //更新数据
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 10;
	try
	{
		ar << byProtID_ << byFuncID_ << qwInstID << (UINT8&)eDataType << (UINT8&)eUpdateType << strData;
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

bool CCenter2DBCommClt::SendSvr_RankDataUpdate(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwInstID, //唯一ID
	NRankProt::ERankType eDataType, //更新数据类型
	NProtoCommon::EDataChange eUpdateType, //更新方式，增加，删除，修改
	const std::string& strData //更新数据
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 10;
	try
	{
		ar << byProtID_ << byFuncID_ << qwInstID << (UINT8&)eDataType << (UINT8&)eUpdateType << strData;
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

std::string& CCenter2DBCommClt::BuildPkg_RankDataUpdate(
	UINT64 qwInstID, //唯一ID
	NRankProt::ERankType eDataType, //更新数据类型
	NProtoCommon::EDataChange eUpdateType, //更新方式，增加，删除，修改
	const std::string& strData //更新数据
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 10;
	try
	{
		ar << byProtID_ << byFuncID_ << qwInstID << (UINT8&)eDataType << (UINT8&)eUpdateType << strData;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 31, Function: 10";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：获取崇拜信息
bool CCenter2DBCommClt::Send_GetAdoreInfo(
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 11;
	try
	{
		ar << byProtID_ << byFuncID_;
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

bool CCenter2DBCommClt::SendSvr_GetAdoreInfo(const UINT32* pSvrID_, UINT8 byCnt_
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 11;
	try
	{
		ar << byProtID_ << byFuncID_;
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

std::string& CCenter2DBCommClt::BuildPkg_GetAdoreInfo(
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 11;
	try
	{
		ar << byProtID_ << byFuncID_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 31, Function: 11";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：崇拜数据更新
bool CCenter2DBCommClt::Send_AdoreDataUpdate(
	UINT64 qwInstID, //唯一ID
	NProtoCommon::EDataChange eUpdateType, //更新方式，增加，删除，修改
	const std::string& strData //更新数据
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 12;
	try
	{
		ar << byProtID_ << byFuncID_ << qwInstID << (UINT8&)eUpdateType << strData;
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

bool CCenter2DBCommClt::SendSvr_AdoreDataUpdate(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwInstID, //唯一ID
	NProtoCommon::EDataChange eUpdateType, //更新方式，增加，删除，修改
	const std::string& strData //更新数据
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 12;
	try
	{
		ar << byProtID_ << byFuncID_ << qwInstID << (UINT8&)eUpdateType << strData;
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

std::string& CCenter2DBCommClt::BuildPkg_AdoreDataUpdate(
	UINT64 qwInstID, //唯一ID
	NProtoCommon::EDataChange eUpdateType, //更新方式，增加，删除，修改
	const std::string& strData //更新数据
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 12;
	try
	{
		ar << byProtID_ << byFuncID_ << qwInstID << (UINT8&)eUpdateType << strData;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 31, Function: 12";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：获取账号ID或主角色名请求
bool CCenter2DBCommClt::Send_UserIDNameReq(
	NServerCommon::EUserReqType eType, //类型
	UINT64 qwUsrID, //帐号ID
	const std::string& strName, //主角色名称
	UINT64 qwUsrData //用户数据
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 13;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eType << qwUsrID << strName << qwUsrData;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 31, Function: 13";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CCenter2DBCommClt::SendSvr_UserIDNameReq(const UINT32* pSvrID_, UINT8 byCnt_,
	NServerCommon::EUserReqType eType, //类型
	UINT64 qwUsrID, //帐号ID
	const std::string& strName, //主角色名称
	UINT64 qwUsrData //用户数据
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 13;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eType << qwUsrID << strName << qwUsrData;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 31, Function: 13";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CCenter2DBCommClt::BuildPkg_UserIDNameReq(
	NServerCommon::EUserReqType eType, //类型
	UINT64 qwUsrID, //帐号ID
	const std::string& strName, //主角色名称
	UINT64 qwUsrData //用户数据
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 13;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eType << qwUsrID << strName << qwUsrData;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 31, Function: 13";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：根据名字获取ID请求
bool CCenter2DBCommClt::Send_GetUserIDFromName(
	const std::string& strName, //主角色名称
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT64 qwUsrID //(返回值)用户ID
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
		ar << byProtID_ << byFuncID_ << dwSessionID_ << strName;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 31, Function: 14";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CCenter2DBCommClt::SendSvr_GetUserIDFromName(const UINT32* pSvrID_, UINT8 byCnt_,
	const std::string& strName, //主角色名称
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT64 qwUsrID //(返回值)用户ID
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
		ar << byProtID_ << byFuncID_ << dwSessionID_ << strName;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 31, Function: 14";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

//发送：获得邮件列表
bool CCenter2DBCommClt::Send_GetAllMailList(
	UINT64 qwRoleID, //玩家ID
	UINT32 dwOverTime, //过期时间
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		const NMailProt::TVecMailDetail& vecMails //(返回值)邮件列表
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
	const UINT8 byFuncID_ = 15;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwRoleID << dwOverTime;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 31, Function: 15";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CCenter2DBCommClt::SendSvr_GetAllMailList(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwRoleID, //玩家ID
	UINT32 dwOverTime, //过期时间
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		const NMailProt::TVecMailDetail& vecMails //(返回值)邮件列表
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
	const UINT8 byFuncID_ = 15;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwRoleID << dwOverTime;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 31, Function: 15";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

//发送：保存邮件
bool CCenter2DBCommClt::Send_SaveMail(
	UINT64 qwMailID, //邮件ID
	UINT64 qwReceiveID, //接受者ID
	UINT64 qwSenderID, //发送者ID
	const std::string& strSenderName, //发送者名字
	NMailProt::EMailType eMailType, //邮件类型
	NMailProt::EMailState eMailState, //邮件状态
	UINT32 dwSendTime, //发送时间
	const std::string& strTitle, //标题
	const std::string& strMsg, //邮件内容
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		INT8 byRet //(返回值)非0表示失败
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
	const UINT8 byFuncID_ = 16;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwMailID << qwReceiveID << qwSenderID << strSenderName << (UINT8&)eMailType << (UINT8&)eMailState << dwSendTime << strTitle << strMsg;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 31, Function: 16";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CCenter2DBCommClt::SendSvr_SaveMail(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwMailID, //邮件ID
	UINT64 qwReceiveID, //接受者ID
	UINT64 qwSenderID, //发送者ID
	const std::string& strSenderName, //发送者名字
	NMailProt::EMailType eMailType, //邮件类型
	NMailProt::EMailState eMailState, //邮件状态
	UINT32 dwSendTime, //发送时间
	const std::string& strTitle, //标题
	const std::string& strMsg, //邮件内容
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		INT8 byRet //(返回值)非0表示失败
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
	const UINT8 byFuncID_ = 16;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwMailID << qwReceiveID << qwSenderID << strSenderName << (UINT8&)eMailType << (UINT8&)eMailState << dwSendTime << strTitle << strMsg;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 31, Function: 16";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

//发送：删除邮件
bool CCenter2DBCommClt::Send_DeleteMail(
	UINT64 qwRoleID, //玩家ID
	const TVecMailDelData& vecMailIDs, //邮件ID列表
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		INT8 byRet //(返回值)非0表示失败
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
	const UINT8 byFuncID_ = 17;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwRoleID << vecMailIDs;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 31, Function: 17";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CCenter2DBCommClt::SendSvr_DeleteMail(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwRoleID, //玩家ID
	const TVecMailDelData& vecMailIDs, //邮件ID列表
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		INT8 byRet //(返回值)非0表示失败
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
	const UINT8 byFuncID_ = 17;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwRoleID << vecMailIDs;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 31, Function: 17";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

//发送：保存系统邮件
bool CCenter2DBCommClt::Send_SaveSystemMail(
	const TVecSystemMailTargetInfo& vecSystemMailTargetInfo, //邮件目标
	const SSystemMailInfo& rSystemMailInfo, //系统邮件信息
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		INT8 byRet //(返回值)非0表示失败
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
	const UINT8 byFuncID_ = 18;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << vecSystemMailTargetInfo << rSystemMailInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 31, Function: 18";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CCenter2DBCommClt::SendSvr_SaveSystemMail(const UINT32* pSvrID_, UINT8 byCnt_,
	const TVecSystemMailTargetInfo& vecSystemMailTargetInfo, //邮件目标
	const SSystemMailInfo& rSystemMailInfo, //系统邮件信息
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		INT8 byRet //(返回值)非0表示失败
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
	const UINT8 byFuncID_ = 18;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << vecSystemMailTargetInfo << rSystemMailInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 31, Function: 18";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

//发送：更新邮件状态
bool CCenter2DBCommClt::Send_UpdateMailStatus(
	UINT64 qwMailID, //邮件ID
	NMailProt::EMailState eMailState, //邮件状态
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		INT8 byRet //(返回值)非0表示失败
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
	const UINT8 byFuncID_ = 19;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwMailID << (UINT8&)eMailState;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 31, Function: 19";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CCenter2DBCommClt::SendSvr_UpdateMailStatus(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwMailID, //邮件ID
	NMailProt::EMailState eMailState, //邮件状态
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		INT8 byRet //(返回值)非0表示失败
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
	const UINT8 byFuncID_ = 19;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwMailID << (UINT8&)eMailState;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 31, Function: 19";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

//发送：删除邮件附件
bool CCenter2DBCommClt::Send_DelMailAttach(
	const MailDelData& stDelData, //删除提示
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		INT8 byRet //(返回值)非0表示失败
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
	const UINT8 byFuncID_ = 20;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << stDelData;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 31, Function: 20";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CCenter2DBCommClt::SendSvr_DelMailAttach(const UINT32* pSvrID_, UINT8 byCnt_,
	const MailDelData& stDelData, //删除提示
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		INT8 byRet //(返回值)非0表示失败
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
	const UINT8 byFuncID_ = 20;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << stDelData;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 31, Function: 20";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

//发送：查询玩家奖励状态
bool CCenter2DBCommClt::Send_GetPrizeStatus(
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		const NWonderActivityProt::TVecWonderPrize2DB& vecRet //(返回值)查询结果
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
	const UINT8 byFuncID_ = 21;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 31, Function: 21";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CCenter2DBCommClt::SendSvr_GetPrizeStatus(const UINT32* pSvrID_, UINT8 byCnt_,
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		const NWonderActivityProt::TVecWonderPrize2DB& vecRet //(返回值)查询结果
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
	const UINT8 byFuncID_ = 21;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 31, Function: 21";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

//发送：删除玩家数据
bool CCenter2DBCommClt::Send_DelActPrizeData(
	UINT16 wActID //活动ID
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 22;
	try
	{
		ar << byProtID_ << byFuncID_ << wActID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 31, Function: 22";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CCenter2DBCommClt::SendSvr_DelActPrizeData(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT16 wActID //活动ID
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 22;
	try
	{
		ar << byProtID_ << byFuncID_ << wActID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 31, Function: 22";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CCenter2DBCommClt::BuildPkg_DelActPrizeData(
	UINT16 wActID //活动ID
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 22;
	try
	{
		ar << byProtID_ << byFuncID_ << wActID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 31, Function: 22";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：查询所有玩家信息
bool CCenter2DBCommClt::Send_GetAllRoleLevel(
	UINT8 byType, //类型
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT8 byTypeRet, //(返回值)类型
		const TVecRoleLevel& vecRoleLevel //(返回值)返回玩家等级
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
	const UINT8 byFuncID_ = 23;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << byType;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 31, Function: 23";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CCenter2DBCommClt::SendSvr_GetAllRoleLevel(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT8 byType, //类型
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT8 byTypeRet, //(返回值)类型
		const TVecRoleLevel& vecRoleLevel //(返回值)返回玩家等级
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
	const UINT8 byFuncID_ = 23;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << byType;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 31, Function: 23";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

//发送：更新玩家奖励状态
bool CCenter2DBCommClt::Send_UpdatePrizeStatus(
	const NWonderActivityProt::SWonderPrize2DB& sPrize2DB, //玩家信息
	NProtoCommon::EDataChange eUpdateType //更新方式，增加，删除，修改
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 24;
	try
	{
		ar << byProtID_ << byFuncID_ << sPrize2DB << (UINT8&)eUpdateType;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 31, Function: 24";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CCenter2DBCommClt::SendSvr_UpdatePrizeStatus(const UINT32* pSvrID_, UINT8 byCnt_,
	const NWonderActivityProt::SWonderPrize2DB& sPrize2DB, //玩家信息
	NProtoCommon::EDataChange eUpdateType //更新方式，增加，删除，修改
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 24;
	try
	{
		ar << byProtID_ << byFuncID_ << sPrize2DB << (UINT8&)eUpdateType;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 31, Function: 24";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CCenter2DBCommClt::BuildPkg_UpdatePrizeStatus(
	const NWonderActivityProt::SWonderPrize2DB& sPrize2DB, //玩家信息
	NProtoCommon::EDataChange eUpdateType //更新方式，增加，删除，修改
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 24;
	try
	{
		ar << byProtID_ << byFuncID_ << sPrize2DB << (UINT8&)eUpdateType;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 31, Function: 24";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：查询玩家保留信息
bool CCenter2DBCommClt::Send_GetRetain(
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		const NWonderActivityProt::TVecRetain& vecRet //(返回值)查询结果
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
	const UINT8 byFuncID_ = 25;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 31, Function: 25";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CCenter2DBCommClt::SendSvr_GetRetain(const UINT32* pSvrID_, UINT8 byCnt_,
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		const NWonderActivityProt::TVecRetain& vecRet //(返回值)查询结果
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
	const UINT8 byFuncID_ = 25;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 31, Function: 25";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

//发送：更新玩家保留信息
bool CCenter2DBCommClt::Send_UpdateRetain(
	const NWonderActivityProt::SRetain& sRetain, //玩家保留信息
	NProtoCommon::EDataChange eUpdateType //更新方式，增加，删除，修改
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 26;
	try
	{
		ar << byProtID_ << byFuncID_ << sRetain << (UINT8&)eUpdateType;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 31, Function: 26";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CCenter2DBCommClt::SendSvr_UpdateRetain(const UINT32* pSvrID_, UINT8 byCnt_,
	const NWonderActivityProt::SRetain& sRetain, //玩家保留信息
	NProtoCommon::EDataChange eUpdateType //更新方式，增加，删除，修改
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 26;
	try
	{
		ar << byProtID_ << byFuncID_ << sRetain << (UINT8&)eUpdateType;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 31, Function: 26";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CCenter2DBCommClt::BuildPkg_UpdateRetain(
	const NWonderActivityProt::SRetain& sRetain, //玩家保留信息
	NProtoCommon::EDataChange eUpdateType //更新方式，增加，删除，修改
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 26;
	try
	{
		ar << byProtID_ << byFuncID_ << sRetain << (UINT8&)eUpdateType;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 31, Function: 26";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：删除玩家保留数据
bool CCenter2DBCommClt::Send_DelActRetainData(
	UINT16 wActID //活动ID
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 27;
	try
	{
		ar << byProtID_ << byFuncID_ << wActID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 31, Function: 27";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CCenter2DBCommClt::SendSvr_DelActRetainData(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT16 wActID //活动ID
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 27;
	try
	{
		ar << byProtID_ << byFuncID_ << wActID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 31, Function: 27";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CCenter2DBCommClt::BuildPkg_DelActRetainData(
	UINT16 wActID //活动ID
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 27;
	try
	{
		ar << byProtID_ << byFuncID_ << wActID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 31, Function: 27";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：请求所有UserID和name
bool CCenter2DBCommClt::Send_GetAllUserIDAndName(
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 28;
	try
	{
		ar << byProtID_ << byFuncID_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 31, Function: 28";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CCenter2DBCommClt::SendSvr_GetAllUserIDAndName(const UINT32* pSvrID_, UINT8 byCnt_
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 28;
	try
	{
		ar << byProtID_ << byFuncID_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 31, Function: 28";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CCenter2DBCommClt::BuildPkg_GetAllUserIDAndName(
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 28;
	try
	{
		ar << byProtID_ << byFuncID_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 31, Function: 28";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：请求所有公告
bool CCenter2DBCommClt::Send_GetAllNotice(
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 29;
	try
	{
		ar << byProtID_ << byFuncID_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 31, Function: 29";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CCenter2DBCommClt::SendSvr_GetAllNotice(const UINT32* pSvrID_, UINT8 byCnt_
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 29;
	try
	{
		ar << byProtID_ << byFuncID_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 31, Function: 29";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CCenter2DBCommClt::BuildPkg_GetAllNotice(
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 29;
	try
	{
		ar << byProtID_ << byFuncID_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 31, Function: 29";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：增加公告
bool CCenter2DBCommClt::Send_AddNotice(
	const NPHPProt::SNotice& sNotice //公告内容
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 30;
	try
	{
		ar << byProtID_ << byFuncID_ << sNotice;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 31, Function: 30";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CCenter2DBCommClt::SendSvr_AddNotice(const UINT32* pSvrID_, UINT8 byCnt_,
	const NPHPProt::SNotice& sNotice //公告内容
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 30;
	try
	{
		ar << byProtID_ << byFuncID_ << sNotice;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 31, Function: 30";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CCenter2DBCommClt::BuildPkg_AddNotice(
	const NPHPProt::SNotice& sNotice //公告内容
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 30;
	try
	{
		ar << byProtID_ << byFuncID_ << sNotice;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 31, Function: 30";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：删除公告
bool CCenter2DBCommClt::Send_DelNotice(
	UINT32 dwNoticeID //公告ID
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 31;
	try
	{
		ar << byProtID_ << byFuncID_ << dwNoticeID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 31, Function: 31";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CCenter2DBCommClt::SendSvr_DelNotice(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT32 dwNoticeID //公告ID
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 31;
	try
	{
		ar << byProtID_ << byFuncID_ << dwNoticeID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 31, Function: 31";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CCenter2DBCommClt::BuildPkg_DelNotice(
	UINT32 dwNoticeID //公告ID
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 31;
	try
	{
		ar << byProtID_ << byFuncID_ << dwNoticeID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 31, Function: 31";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：请求斗剑信息
bool CCenter2DBCommClt::Send_GetAllArena(
	UINT32 dwPageSize //发送条数
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 32;
	try
	{
		ar << byProtID_ << byFuncID_ << dwPageSize;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 31, Function: 32";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CCenter2DBCommClt::SendSvr_GetAllArena(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT32 dwPageSize //发送条数
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 32;
	try
	{
		ar << byProtID_ << byFuncID_ << dwPageSize;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 31, Function: 32";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CCenter2DBCommClt::BuildPkg_GetAllArena(
	UINT32 dwPageSize //发送条数
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 32;
	try
	{
		ar << byProtID_ << byFuncID_ << dwPageSize;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 31, Function: 32";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：更新斗剑数据
bool CCenter2DBCommClt::Send_UpdateAllArena(
	const NArenaGS::TVecArenaPlayerBaseDataUpdate& vecUpdate //更新信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 33;
	try
	{
		ar << byProtID_ << byFuncID_ << vecUpdate;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 31, Function: 33";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CCenter2DBCommClt::SendSvr_UpdateAllArena(const UINT32* pSvrID_, UINT8 byCnt_,
	const NArenaGS::TVecArenaPlayerBaseDataUpdate& vecUpdate //更新信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 33;
	try
	{
		ar << byProtID_ << byFuncID_ << vecUpdate;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 31, Function: 33";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CCenter2DBCommClt::BuildPkg_UpdateAllArena(
	const NArenaGS::TVecArenaPlayerBaseDataUpdate& vecUpdate //更新信息
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 33;
	try
	{
		ar << byProtID_ << byFuncID_ << vecUpdate;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 31, Function: 33";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：删除玩家斗剑数据
bool CCenter2DBCommClt::Send_DelPlayerArena(
	const TVecUINT64& vecDel //删除玩家斗剑信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 34;
	try
	{
		ar << byProtID_ << byFuncID_ << vecDel;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 31, Function: 34";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CCenter2DBCommClt::SendSvr_DelPlayerArena(const UINT32* pSvrID_, UINT8 byCnt_,
	const TVecUINT64& vecDel //删除玩家斗剑信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 34;
	try
	{
		ar << byProtID_ << byFuncID_ << vecDel;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 31, Function: 34";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CCenter2DBCommClt::BuildPkg_DelPlayerArena(
	const TVecUINT64& vecDel //删除玩家斗剑信息
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 34;
	try
	{
		ar << byProtID_ << byFuncID_ << vecDel;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 31, Function: 34";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：请求系统Var数据
bool CCenter2DBCommClt::Send_GetGameVar(
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		const NRoleInfoDefine::TVecGameVarsDBInfo& vecVar //(返回值)返回的Var
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
	const UINT8 byFuncID_ = 35;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 31, Function: 35";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CCenter2DBCommClt::SendSvr_GetGameVar(const UINT32* pSvrID_, UINT8 byCnt_,
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		const NRoleInfoDefine::TVecGameVarsDBInfo& vecVar //(返回值)返回的Var
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
	const UINT8 byFuncID_ = 35;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 31, Function: 35";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

//发送：更新系统Var数据
bool CCenter2DBCommClt::Send_UpdateGameVar(
	const NRoleInfoDefine::SGameVarsDBInfo& Var //更新的Var
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 36;
	try
	{
		ar << byProtID_ << byFuncID_ << Var;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 31, Function: 36";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CCenter2DBCommClt::SendSvr_UpdateGameVar(const UINT32* pSvrID_, UINT8 byCnt_,
	const NRoleInfoDefine::SGameVarsDBInfo& Var //更新的Var
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 36;
	try
	{
		ar << byProtID_ << byFuncID_ << Var;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 31, Function: 36";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CCenter2DBCommClt::BuildPkg_UpdateGameVar(
	const NRoleInfoDefine::SGameVarsDBInfo& Var //更新的Var
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 36;
	try
	{
		ar << byProtID_ << byFuncID_ << Var;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 31, Function: 36";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：增加系统Var数据
bool CCenter2DBCommClt::Send_AddGameVar(
	const NRoleInfoDefine::SGameVarsDBInfo& Var //增加的Var
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 37;
	try
	{
		ar << byProtID_ << byFuncID_ << Var;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 31, Function: 37";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CCenter2DBCommClt::SendSvr_AddGameVar(const UINT32* pSvrID_, UINT8 byCnt_,
	const NRoleInfoDefine::SGameVarsDBInfo& Var //增加的Var
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 37;
	try
	{
		ar << byProtID_ << byFuncID_ << Var;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 31, Function: 37";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CCenter2DBCommClt::BuildPkg_AddGameVar(
	const NRoleInfoDefine::SGameVarsDBInfo& Var //增加的Var
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 37;
	try
	{
		ar << byProtID_ << byFuncID_ << Var;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 31, Function: 37";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：删除Var数据
bool CCenter2DBCommClt::Send_DelGameVar(
	UINT16 wVarID //删除的VarID
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 38;
	try
	{
		ar << byProtID_ << byFuncID_ << wVarID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 31, Function: 38";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CCenter2DBCommClt::SendSvr_DelGameVar(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT16 wVarID //删除的VarID
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 38;
	try
	{
		ar << byProtID_ << byFuncID_ << wVarID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 31, Function: 38";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CCenter2DBCommClt::BuildPkg_DelGameVar(
	UINT16 wVarID //删除的VarID
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 38;
	try
	{
		ar << byProtID_ << byFuncID_ << wVarID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 31, Function: 38";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：根据玩家ID获得竞技基本数据
bool CCenter2DBCommClt::Send_GetArenaFighterByID(
	UINT64 qwRoleID, //玩家的ID
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		const NArenaGS::SArenaFighter& stFighter //(返回值)返回的数据
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
	const UINT8 byFuncID_ = 39;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwRoleID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 31, Function: 39";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CCenter2DBCommClt::SendSvr_GetArenaFighterByID(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwRoleID, //玩家的ID
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		const NArenaGS::SArenaFighter& stFighter //(返回值)返回的数据
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
	const UINT8 byFuncID_ = 39;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwRoleID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 31, Function: 39";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

//发送：获取镇妖塔信息（启动预加载调用）
bool CCenter2DBCommClt::Send_GetDemonTowerInfo(
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		const NDemonTowerGS::TVecDemonTowerPlayer& vecDemonTowerPlayer //(返回值)镇妖塔玩家信息
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
	const UINT8 byFuncID_ = 40;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 31, Function: 40";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CCenter2DBCommClt::SendSvr_GetDemonTowerInfo(const UINT32* pSvrID_, UINT8 byCnt_,
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		const NDemonTowerGS::TVecDemonTowerPlayer& vecDemonTowerPlayer //(返回值)镇妖塔玩家信息
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
	const UINT8 byFuncID_ = 40;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 31, Function: 40";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

//发送：更新镇妖塔玩家信息
bool CCenter2DBCommClt::Send_UpateDemonTowerInfo(
	NDemonTowerGS::EDemonTowerDB eDbType, //更新类型
	const NDemonTowerGS::SDemonTowerPlayer& oDemonTowerPlayer //镇妖塔玩家信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 41;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eDbType << oDemonTowerPlayer;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 31, Function: 41";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CCenter2DBCommClt::SendSvr_UpateDemonTowerInfo(const UINT32* pSvrID_, UINT8 byCnt_,
	NDemonTowerGS::EDemonTowerDB eDbType, //更新类型
	const NDemonTowerGS::SDemonTowerPlayer& oDemonTowerPlayer //镇妖塔玩家信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 41;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eDbType << oDemonTowerPlayer;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 31, Function: 41";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CCenter2DBCommClt::BuildPkg_UpateDemonTowerInfo(
	NDemonTowerGS::EDemonTowerDB eDbType, //更新类型
	const NDemonTowerGS::SDemonTowerPlayer& oDemonTowerPlayer //镇妖塔玩家信息
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 41;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eDbType << oDemonTowerPlayer;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 31, Function: 41";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：获取中心服数据
bool CCenter2DBCommClt::Send_GetCenterData(
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		const TVecCenterData& vecCenterData //(返回值)中心服数据
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
	const UINT8 byFuncID_ = 42;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 31, Function: 42";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CCenter2DBCommClt::SendSvr_GetCenterData(const UINT32* pSvrID_, UINT8 byCnt_,
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		const TVecCenterData& vecCenterData //(返回值)中心服数据
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
	const UINT8 byFuncID_ = 42;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 31, Function: 42";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

//发送：更新中心服数据
bool CCenter2DBCommClt::Send_UpateCenterData(
	const SCenterData& oCenterData, //中心服数据
	bool bDelete //删除/更新
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 43;
	try
	{
		ar << byProtID_ << byFuncID_ << oCenterData << bDelete;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 31, Function: 43";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CCenter2DBCommClt::SendSvr_UpateCenterData(const UINT32* pSvrID_, UINT8 byCnt_,
	const SCenterData& oCenterData, //中心服数据
	bool bDelete //删除/更新
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 43;
	try
	{
		ar << byProtID_ << byFuncID_ << oCenterData << bDelete;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 31, Function: 43";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CCenter2DBCommClt::BuildPkg_UpateCenterData(
	const SCenterData& oCenterData, //中心服数据
	bool bDelete //删除/更新
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 43;
	try
	{
		ar << byProtID_ << byFuncID_ << oCenterData << bDelete;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 31, Function: 43";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：查看玩家私聊信息
bool CCenter2DBCommClt::Send_GetWhisperInfo(
	UINT64 qwRoleID, //玩家的ID
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		const NGlobalChatProt::SWhisperInfo& whisperInfo //(返回值)返回的数据
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
	const UINT8 byFuncID_ = 44;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwRoleID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 31, Function: 44";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CCenter2DBCommClt::SendSvr_GetWhisperInfo(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwRoleID, //玩家的ID
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		const NGlobalChatProt::SWhisperInfo& whisperInfo //(返回值)返回的数据
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
	const UINT8 byFuncID_ = 44;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwRoleID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 31, Function: 44";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

//发送：获得玩家战报信息
bool CCenter2DBCommClt::Send_GetBattleReport(
	UINT64 qwRoleID, //玩家的ID
	NRoleInfoDefine::EBattleReportType eBattleType, //战斗类型
	NRoleInfoDefine::EBattleActionType eAction, //战斗的发起
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		const NRoleInfoDefine::TVecBattleRePort& vecReport //(返回值)返回的数据
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
	const UINT8 byFuncID_ = 45;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwRoleID << (UINT8&)eBattleType << (UINT8&)eAction;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 31, Function: 45";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CCenter2DBCommClt::SendSvr_GetBattleReport(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwRoleID, //玩家的ID
	NRoleInfoDefine::EBattleReportType eBattleType, //战斗类型
	NRoleInfoDefine::EBattleActionType eAction, //战斗的发起
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		const NRoleInfoDefine::TVecBattleRePort& vecReport //(返回值)返回的数据
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
	const UINT8 byFuncID_ = 45;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwRoleID << (UINT8&)eBattleType << (UINT8&)eAction;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 31, Function: 45";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

//发送：增加玩家战报信息
bool CCenter2DBCommClt::Send_AddBattleReport(
	UINT64 qwRoleID, //玩家的ID
	const NRoleInfoDefine::SBattleRePort& sReport, //战斗数据
	UINT8 byNum, //超过byNum，返回删除的旧的战报,0表示不删除
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		const TVecUINT64& vecBattleID //(返回值)删除的战报
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
	const UINT8 byFuncID_ = 46;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwRoleID << sReport << byNum;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 31, Function: 46";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CCenter2DBCommClt::SendSvr_AddBattleReport(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwRoleID, //玩家的ID
	const NRoleInfoDefine::SBattleRePort& sReport, //战斗数据
	UINT8 byNum, //超过byNum，返回删除的旧的战报,0表示不删除
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		const TVecUINT64& vecBattleID //(返回值)删除的战报
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
	const UINT8 byFuncID_ = 46;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwRoleID << sReport << byNum;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 31, Function: 46";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

//发送：重新加载表格
bool CCenter2DBCommClt::Send_ReloadTable(
	const TVecString& vecTableName //表格名字
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 47;
	try
	{
		ar << byProtID_ << byFuncID_ << vecTableName;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 31, Function: 47";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CCenter2DBCommClt::SendSvr_ReloadTable(const UINT32* pSvrID_, UINT8 byCnt_,
	const TVecString& vecTableName //表格名字
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 47;
	try
	{
		ar << byProtID_ << byFuncID_ << vecTableName;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 31, Function: 47";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CCenter2DBCommClt::BuildPkg_ReloadTable(
	const TVecString& vecTableName //表格名字
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 47;
	try
	{
		ar << byProtID_ << byFuncID_ << vecTableName;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 31, Function: 47";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：请求所有九疑鼎信息
bool CCenter2DBCommClt::Send_GetAllTripod(
	UINT32 dwPageSize //发送条数
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 48;
	try
	{
		ar << byProtID_ << byFuncID_ << dwPageSize;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 31, Function: 48";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CCenter2DBCommClt::SendSvr_GetAllTripod(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT32 dwPageSize //发送条数
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 48;
	try
	{
		ar << byProtID_ << byFuncID_ << dwPageSize;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 31, Function: 48";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CCenter2DBCommClt::BuildPkg_GetAllTripod(
	UINT32 dwPageSize //发送条数
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 48;
	try
	{
		ar << byProtID_ << byFuncID_ << dwPageSize;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 31, Function: 48";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：请求所有九疑鼎的协助信息
bool CCenter2DBCommClt::Send_GetAllTripodHelper(
	UINT32 dwPageSize //发送条数
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 49;
	try
	{
		ar << byProtID_ << byFuncID_ << dwPageSize;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 31, Function: 49";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CCenter2DBCommClt::SendSvr_GetAllTripodHelper(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT32 dwPageSize //发送条数
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 49;
	try
	{
		ar << byProtID_ << byFuncID_ << dwPageSize;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 31, Function: 49";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CCenter2DBCommClt::BuildPkg_GetAllTripodHelper(
	UINT32 dwPageSize //发送条数
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 49;
	try
	{
		ar << byProtID_ << byFuncID_ << dwPageSize;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 31, Function: 49";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：请求所有九疑鼎的动态信息
bool CCenter2DBCommClt::Send_GetAllTripodLog(
	UINT32 dwPageSize //发送条数
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 50;
	try
	{
		ar << byProtID_ << byFuncID_ << dwPageSize;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 31, Function: 50";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CCenter2DBCommClt::SendSvr_GetAllTripodLog(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT32 dwPageSize //发送条数
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 50;
	try
	{
		ar << byProtID_ << byFuncID_ << dwPageSize;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 31, Function: 50";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CCenter2DBCommClt::BuildPkg_GetAllTripodLog(
	UINT32 dwPageSize //发送条数
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 50;
	try
	{
		ar << byProtID_ << byFuncID_ << dwPageSize;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 31, Function: 50";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：更新玩家九疑鼎信息
bool CCenter2DBCommClt::Send_UpdateTripod(
	UINT64 qwRoleID, //玩家的ID
	const NTripodProt::STripodInfo& oTripodInfo //九疑鼎的数据
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 51;
	try
	{
		ar << byProtID_ << byFuncID_ << qwRoleID << oTripodInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 31, Function: 51";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CCenter2DBCommClt::SendSvr_UpdateTripod(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwRoleID, //玩家的ID
	const NTripodProt::STripodInfo& oTripodInfo //九疑鼎的数据
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 51;
	try
	{
		ar << byProtID_ << byFuncID_ << qwRoleID << oTripodInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 31, Function: 51";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CCenter2DBCommClt::BuildPkg_UpdateTripod(
	UINT64 qwRoleID, //玩家的ID
	const NTripodProt::STripodInfo& oTripodInfo //九疑鼎的数据
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 51;
	try
	{
		ar << byProtID_ << byFuncID_ << qwRoleID << oTripodInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 31, Function: 51";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：更新玩家九疑鼎协助信息
bool CCenter2DBCommClt::Send_UpateTripodHelp(
	NProtoCommon::EDataChange eUpdateType, //更新类型，增加，删除，修改
	const NTripodProt::STripodHelp& oTripodHelp //九疑鼎协助的信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 52;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eUpdateType << oTripodHelp;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 31, Function: 52";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CCenter2DBCommClt::SendSvr_UpateTripodHelp(const UINT32* pSvrID_, UINT8 byCnt_,
	NProtoCommon::EDataChange eUpdateType, //更新类型，增加，删除，修改
	const NTripodProt::STripodHelp& oTripodHelp //九疑鼎协助的信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 52;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eUpdateType << oTripodHelp;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 31, Function: 52";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CCenter2DBCommClt::BuildPkg_UpateTripodHelp(
	NProtoCommon::EDataChange eUpdateType, //更新类型，增加，删除，修改
	const NTripodProt::STripodHelp& oTripodHelp //九疑鼎协助的信息
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 52;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eUpdateType << oTripodHelp;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 31, Function: 52";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：更新玩家九疑鼎动态信息
bool CCenter2DBCommClt::Send_UpdateTripodLog(
	UINT64 qwRoleID, //玩家的ID
	NProtoCommon::EDataChange eUpdateType, //更新类型，增加，删除，修改
	const NTripodProt::STripodLog& oTripodLog //九疑鼎动态的信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 53;
	try
	{
		ar << byProtID_ << byFuncID_ << qwRoleID << (UINT8&)eUpdateType << oTripodLog;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 31, Function: 53";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CCenter2DBCommClt::SendSvr_UpdateTripodLog(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwRoleID, //玩家的ID
	NProtoCommon::EDataChange eUpdateType, //更新类型，增加，删除，修改
	const NTripodProt::STripodLog& oTripodLog //九疑鼎动态的信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 53;
	try
	{
		ar << byProtID_ << byFuncID_ << qwRoleID << (UINT8&)eUpdateType << oTripodLog;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 31, Function: 53";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CCenter2DBCommClt::BuildPkg_UpdateTripodLog(
	UINT64 qwRoleID, //玩家的ID
	NProtoCommon::EDataChange eUpdateType, //更新类型，增加，删除，修改
	const NTripodProt::STripodLog& oTripodLog //九疑鼎动态的信息
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 53;
	try
	{
		ar << byProtID_ << byFuncID_ << qwRoleID << (UINT8&)eUpdateType << oTripodLog;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 31, Function: 53";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：增加离线事件
bool CCenter2DBCommClt::Send_AddOffLineEvent(
	const TVecUINT64& vecRoleID, //玩家的ID
	const NRoleInfoDefine::SEventOffLine& sEventData //事件
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 54;
	try
	{
		ar << byProtID_ << byFuncID_ << vecRoleID << sEventData;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 31, Function: 54";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CCenter2DBCommClt::SendSvr_AddOffLineEvent(const UINT32* pSvrID_, UINT8 byCnt_,
	const TVecUINT64& vecRoleID, //玩家的ID
	const NRoleInfoDefine::SEventOffLine& sEventData //事件
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 54;
	try
	{
		ar << byProtID_ << byFuncID_ << vecRoleID << sEventData;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 31, Function: 54";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CCenter2DBCommClt::BuildPkg_AddOffLineEvent(
	const TVecUINT64& vecRoleID, //玩家的ID
	const NRoleInfoDefine::SEventOffLine& sEventData //事件
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 54;
	try
	{
		ar << byProtID_ << byFuncID_ << vecRoleID << sEventData;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 31, Function: 54";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：对玩家封号
bool CCenter2DBCommClt::Send_FreezePlayer(
	UINT64 qwRoleID, //玩家的ID
	UINT32 dwFreezeTimer //封号
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 55;
	try
	{
		ar << byProtID_ << byFuncID_ << qwRoleID << dwFreezeTimer;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 31, Function: 55";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CCenter2DBCommClt::SendSvr_FreezePlayer(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwRoleID, //玩家的ID
	UINT32 dwFreezeTimer //封号
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 55;
	try
	{
		ar << byProtID_ << byFuncID_ << qwRoleID << dwFreezeTimer;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 31, Function: 55";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CCenter2DBCommClt::BuildPkg_FreezePlayer(
	UINT64 qwRoleID, //玩家的ID
	UINT32 dwFreezeTimer //封号
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 55;
	try
	{
		ar << byProtID_ << byFuncID_ << qwRoleID << dwFreezeTimer;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 31, Function: 55";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：对玩家禁言
bool CCenter2DBCommClt::Send_ForbitChat(
	UINT64 qwRoleID, //玩家的ID
	UINT32 dwForbitTimer //禁言时间
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 56;
	try
	{
		ar << byProtID_ << byFuncID_ << qwRoleID << dwForbitTimer;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 31, Function: 56";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CCenter2DBCommClt::SendSvr_ForbitChat(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwRoleID, //玩家的ID
	UINT32 dwForbitTimer //禁言时间
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 56;
	try
	{
		ar << byProtID_ << byFuncID_ << qwRoleID << dwForbitTimer;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 31, Function: 56";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CCenter2DBCommClt::BuildPkg_ForbitChat(
	UINT64 qwRoleID, //玩家的ID
	UINT32 dwForbitTimer //禁言时间
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 56;
	try
	{
		ar << byProtID_ << byFuncID_ << qwRoleID << dwForbitTimer;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 31, Function: 56";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：将玩家登录时IP写入数据库
bool CCenter2DBCommClt::Send_UpdateLoginIP(
	UINT64 qwUserID, //玩家的ID
	const std::string& strLoginIP //登录时IP
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 57;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUserID << strLoginIP;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 31, Function: 57";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CCenter2DBCommClt::SendSvr_UpdateLoginIP(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwUserID, //玩家的ID
	const std::string& strLoginIP //登录时IP
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 57;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUserID << strLoginIP;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 31, Function: 57";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CCenter2DBCommClt::BuildPkg_UpdateLoginIP(
	UINT64 qwUserID, //玩家的ID
	const std::string& strLoginIP //登录时IP
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 57;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUserID << strLoginIP;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 31, Function: 57";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：请求拉取进入参数
bool CCenter2DBCommClt::Send_GetPlatformParam(
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 58;
	try
	{
		ar << byProtID_ << byFuncID_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 31, Function: 58";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CCenter2DBCommClt::SendSvr_GetPlatformParam(const UINT32* pSvrID_, UINT8 byCnt_
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 58;
	try
	{
		ar << byProtID_ << byFuncID_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 31, Function: 58";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CCenter2DBCommClt::BuildPkg_GetPlatformParam(
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 58;
	try
	{
		ar << byProtID_ << byFuncID_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 31, Function: 58";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：数据库查询
bool CCenter2DBCommClt::Send_GetResult2DB(
	const SBaseCond& sBaseCond //查询条件
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 59;
	try
	{
		ar << byProtID_ << byFuncID_ << sBaseCond;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 31, Function: 59";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CCenter2DBCommClt::SendSvr_GetResult2DB(const UINT32* pSvrID_, UINT8 byCnt_,
	const SBaseCond& sBaseCond //查询条件
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 59;
	try
	{
		ar << byProtID_ << byFuncID_ << sBaseCond;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 31, Function: 59";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CCenter2DBCommClt::BuildPkg_GetResult2DB(
	const SBaseCond& sBaseCond //查询条件
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 59;
	try
	{
		ar << byProtID_ << byFuncID_ << sBaseCond;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 31, Function: 59";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：请求金船信息
bool CCenter2DBCommClt::Send_GetAllShip(
	UINT32 dwPageSize //发送条数
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 60;
	try
	{
		ar << byProtID_ << byFuncID_ << dwPageSize;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 31, Function: 60";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CCenter2DBCommClt::SendSvr_GetAllShip(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT32 dwPageSize //发送条数
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 60;
	try
	{
		ar << byProtID_ << byFuncID_ << dwPageSize;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 31, Function: 60";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CCenter2DBCommClt::BuildPkg_GetAllShip(
	UINT32 dwPageSize //发送条数
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 60;
	try
	{
		ar << byProtID_ << byFuncID_ << dwPageSize;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 31, Function: 60";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：更新金船数据
bool CCenter2DBCommClt::Send_UpdateShip(
	const NShipProt::PlayerShip& UpdateInfo //更新信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 61;
	try
	{
		ar << byProtID_ << byFuncID_ << UpdateInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 31, Function: 61";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CCenter2DBCommClt::SendSvr_UpdateShip(const UINT32* pSvrID_, UINT8 byCnt_,
	const NShipProt::PlayerShip& UpdateInfo //更新信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 61;
	try
	{
		ar << byProtID_ << byFuncID_ << UpdateInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 31, Function: 61";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CCenter2DBCommClt::BuildPkg_UpdateShip(
	const NShipProt::PlayerShip& UpdateInfo //更新信息
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 61;
	try
	{
		ar << byProtID_ << byFuncID_ << UpdateInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 31, Function: 61";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：删除金船数据
bool CCenter2DBCommClt::Send_DelShip(
	UINT64 qwInsID //删除金船信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 62;
	try
	{
		ar << byProtID_ << byFuncID_ << qwInsID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 31, Function: 62";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CCenter2DBCommClt::SendSvr_DelShip(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwInsID //删除金船信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 62;
	try
	{
		ar << byProtID_ << byFuncID_ << qwInsID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 31, Function: 62";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CCenter2DBCommClt::BuildPkg_DelShip(
	UINT64 qwInsID //删除金船信息
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 62;
	try
	{
		ar << byProtID_ << byFuncID_ << qwInsID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 31, Function: 62";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：增加金船报告
bool CCenter2DBCommClt::Send_AddShipReport(
	UINT64 qwRoleID, //报告拥有者
	const NShipProt::ShipReport& sReport //报告内容
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 63;
	try
	{
		ar << byProtID_ << byFuncID_ << qwRoleID << sReport;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 31, Function: 63";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CCenter2DBCommClt::SendSvr_AddShipReport(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwRoleID, //报告拥有者
	const NShipProt::ShipReport& sReport //报告内容
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 63;
	try
	{
		ar << byProtID_ << byFuncID_ << qwRoleID << sReport;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 31, Function: 63";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CCenter2DBCommClt::BuildPkg_AddShipReport(
	UINT64 qwRoleID, //报告拥有者
	const NShipProt::ShipReport& sReport //报告内容
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 63;
	try
	{
		ar << byProtID_ << byFuncID_ << qwRoleID << sReport;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 31, Function: 63";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：删除金船报告
bool CCenter2DBCommClt::Send_DelShipReport(
	UINT64 qwRoleID, //报告拥有者
	UINT64 qwInsID //金船唯一ID
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 64;
	try
	{
		ar << byProtID_ << byFuncID_ << qwRoleID << qwInsID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 31, Function: 64";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CCenter2DBCommClt::SendSvr_DelShipReport(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwRoleID, //报告拥有者
	UINT64 qwInsID //金船唯一ID
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 64;
	try
	{
		ar << byProtID_ << byFuncID_ << qwRoleID << qwInsID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 31, Function: 64";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CCenter2DBCommClt::BuildPkg_DelShipReport(
	UINT64 qwRoleID, //报告拥有者
	UINT64 qwInsID //金船唯一ID
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 64;
	try
	{
		ar << byProtID_ << byFuncID_ << qwRoleID << qwInsID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 31, Function: 64";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：天元神兽同步玩家信息
bool CCenter2DBCommClt::Send_SyncMonsterUserInfo(
	NProtoCommon::EDataChange eUpdateType, //更新类型，增加，删除，修改
	const NGodMonsterProt::SGuildUser2DB& sUser //数据
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 65;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eUpdateType << sUser;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 31, Function: 65";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CCenter2DBCommClt::SendSvr_SyncMonsterUserInfo(const UINT32* pSvrID_, UINT8 byCnt_,
	NProtoCommon::EDataChange eUpdateType, //更新类型，增加，删除，修改
	const NGodMonsterProt::SGuildUser2DB& sUser //数据
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 65;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eUpdateType << sUser;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 31, Function: 65";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CCenter2DBCommClt::BuildPkg_SyncMonsterUserInfo(
	NProtoCommon::EDataChange eUpdateType, //更新类型，增加，删除，修改
	const NGodMonsterProt::SGuildUser2DB& sUser //数据
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 65;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eUpdateType << sUser;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 31, Function: 65";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：获取天元神兽信息（启动预加载调用）
bool CCenter2DBCommClt::Send_GetGodMonsterInfo(
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		const NGodMonsterProt::TVecGuildUser2DB& vecUser //(返回值)天元神兽玩家信息
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
	const UINT8 byFuncID_ = 66;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 31, Function: 66";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CCenter2DBCommClt::SendSvr_GetGodMonsterInfo(const UINT32* pSvrID_, UINT8 byCnt_,
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		const NGodMonsterProt::TVecGuildUser2DB& vecUser //(返回值)天元神兽玩家信息
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
	const UINT8 byFuncID_ = 66;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 31, Function: 66";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

//发送：天元神兽同步玩家限购礼包信息
bool CCenter2DBCommClt::Send_SyncLimitPrizeInfo(
	NProtoCommon::EDataChange eUpdateType, //更新类型，增加，删除，修改
	const NGodMonsterProt::SLimitPrize2DB& oLimitPrize //数据
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 67;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eUpdateType << oLimitPrize;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 31, Function: 67";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CCenter2DBCommClt::SendSvr_SyncLimitPrizeInfo(const UINT32* pSvrID_, UINT8 byCnt_,
	NProtoCommon::EDataChange eUpdateType, //更新类型，增加，删除，修改
	const NGodMonsterProt::SLimitPrize2DB& oLimitPrize //数据
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 67;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eUpdateType << oLimitPrize;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 31, Function: 67";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CCenter2DBCommClt::BuildPkg_SyncLimitPrizeInfo(
	NProtoCommon::EDataChange eUpdateType, //更新类型，增加，删除，修改
	const NGodMonsterProt::SLimitPrize2DB& oLimitPrize //数据
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 67;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eUpdateType << oLimitPrize;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 31, Function: 67";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：获取天元神兽玩家限购礼包信息（启动预加载调用）
bool CCenter2DBCommClt::Send_GetLimitPrizeInfo(
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		const NGodMonsterProt::TVecLimitPrize2DB& vecLimitPrize //(返回值)数据
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
	const UINT8 byFuncID_ = 68;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 31, Function: 68";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CCenter2DBCommClt::SendSvr_GetLimitPrizeInfo(const UINT32* pSvrID_, UINT8 byCnt_,
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		const NGodMonsterProt::TVecLimitPrize2DB& vecLimitPrize //(返回值)数据
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
	const UINT8 byFuncID_ = 68;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 31, Function: 68";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

//发送：运营活动中心同步信息
bool CCenter2DBCommClt::Send_SyncActivityCenterInfo(
	NProtoCommon::EDataChange eUpdateType, //更新类型，增加，删除，修改
	const NProtoCommon::SActivityOpt& oActOpt //数据
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 69;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eUpdateType << oActOpt;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 31, Function: 69";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CCenter2DBCommClt::SendSvr_SyncActivityCenterInfo(const UINT32* pSvrID_, UINT8 byCnt_,
	NProtoCommon::EDataChange eUpdateType, //更新类型，增加，删除，修改
	const NProtoCommon::SActivityOpt& oActOpt //数据
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 69;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eUpdateType << oActOpt;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 31, Function: 69";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CCenter2DBCommClt::BuildPkg_SyncActivityCenterInfo(
	NProtoCommon::EDataChange eUpdateType, //更新类型，增加，删除，修改
	const NProtoCommon::SActivityOpt& oActOpt //数据
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 69;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eUpdateType << oActOpt;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 31, Function: 69";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：运营活动中心操作（启动预加载调用）
bool CCenter2DBCommClt::Send_GetActivityCenterInfo(
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		const NProtoCommon::TVecActivityOpt& vecActOpt //(返回值)数据
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
	const UINT8 byFuncID_ = 70;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 31, Function: 70";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CCenter2DBCommClt::SendSvr_GetActivityCenterInfo(const UINT32* pSvrID_, UINT8 byCnt_,
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		const NProtoCommon::TVecActivityOpt& vecActOpt //(返回值)数据
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
	const UINT8 byFuncID_ = 70;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 31, Function: 70";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

//发送：增加机器人新信息
bool CCenter2DBCommClt::Send_AddLadderRobot(
	const NArenaGS::TVecLadderRobot& vecData //数据
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 71;
	try
	{
		ar << byProtID_ << byFuncID_ << vecData;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 31, Function: 71";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CCenter2DBCommClt::SendSvr_AddLadderRobot(const UINT32* pSvrID_, UINT8 byCnt_,
	const NArenaGS::TVecLadderRobot& vecData //数据
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 71;
	try
	{
		ar << byProtID_ << byFuncID_ << vecData;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 31, Function: 71";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CCenter2DBCommClt::BuildPkg_AddLadderRobot(
	const NArenaGS::TVecLadderRobot& vecData //数据
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 71;
	try
	{
		ar << byProtID_ << byFuncID_ << vecData;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 31, Function: 71";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：增加机器人新信息
bool CCenter2DBCommClt::Send_UpdateLadderRobot(
	const NArenaGS::SLadderRobot& SData //数据
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 72;
	try
	{
		ar << byProtID_ << byFuncID_ << SData;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 31, Function: 72";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CCenter2DBCommClt::SendSvr_UpdateLadderRobot(const UINT32* pSvrID_, UINT8 byCnt_,
	const NArenaGS::SLadderRobot& SData //数据
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 72;
	try
	{
		ar << byProtID_ << byFuncID_ << SData;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 31, Function: 72";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CCenter2DBCommClt::BuildPkg_UpdateLadderRobot(
	const NArenaGS::SLadderRobot& SData //数据
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 72;
	try
	{
		ar << byProtID_ << byFuncID_ << SData;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 31, Function: 72";
		_strPkg.clear();
	}
	return _strPkg;
}

bool CCenter2DBCommClt::_DoRecv_SendResult2Cent(const char* pBuf_, UINT32 dwLen_)
{
	SBaseCond sCond;
	SBaseResult sResult;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> sCond >> sResult;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 31, Function: 1";
		return false;
	}
	OnRecv_SendResult2Cent(sCond, sResult);
	return true;
}

bool CCenter2DBCommClt::_DoRecv_SendAllUserIDAndName(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwTotalSize = 0;
	NPHPProt::TVecUserIDAndName vecUserIDAndName;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwTotalSize >> vecUserIDAndName;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 31, Function: 2";
		return false;
	}
	OnRecv_SendAllUserIDAndName(dwTotalSize, vecUserIDAndName);
	return true;
}

bool CCenter2DBCommClt::_DoRecv_SendAllNotice(const char* pBuf_, UINT32 dwLen_)
{
	NPHPProt::TVecNotice vecNotice;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> vecNotice;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 31, Function: 3";
		return false;
	}
	OnRecv_SendAllNotice(vecNotice);
	return true;
}

bool CCenter2DBCommClt::_DoRecv_SendAllArena(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwPageSize = 0;
	UINT32 dwTotalSize = 0;
	NArenaGS::TVecArenaPlayerData vecSendDate;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwPageSize >> dwTotalSize >> vecSendDate;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 31, Function: 4";
		return false;
	}
	OnRecv_SendAllArena(dwPageSize, dwTotalSize, vecSendDate);
	return true;
}

bool CCenter2DBCommClt::_DoRecv_SendAllRobot(const char* pBuf_, UINT32 dwLen_)
{
	NArenaGS::TVecLadderRobot vecRobot;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> vecRobot;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 31, Function: 5";
		return false;
	}
	OnRecv_SendAllRobot(vecRobot);
	return true;
}

bool CCenter2DBCommClt::_DoRecv_RankInitNotify(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwCurSize = 0;
	UINT32 dwTotalSize = 0;
	NRankProt::TVecRankInfo vecRankInfo;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwCurSize >> dwTotalSize >> vecRankInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 31, Function: 6";
		return false;
	}
	OnRecv_RankInitNotify(dwCurSize, dwTotalSize, vecRankInfo);
	return true;
}

bool CCenter2DBCommClt::_DoRecv_AdoreInitNotify(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwCurSize = 0;
	UINT32 dwTotalSize = 0;
	NRankProt::TVecDBAdoreInfo vecAdoreInfo;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwCurSize >> dwTotalSize >> vecAdoreInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 31, Function: 7";
		return false;
	}
	OnRecv_AdoreInitNotify(dwCurSize, dwTotalSize, vecAdoreInfo);
	return true;
}

bool CCenter2DBCommClt::_DoRecv_SendAllTripod(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwPageSize = 0;
	UINT32 dwTotalSize = 0;
	NTripodProt::TVecTripodData vecSendData;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwPageSize >> dwTotalSize >> vecSendData;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 31, Function: 8";
		return false;
	}
	OnRecv_SendAllTripod(dwPageSize, dwTotalSize, vecSendData);
	return true;
}

bool CCenter2DBCommClt::_DoRecv_SendAllTripodHelper(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwPageSize = 0;
	UINT32 dwTotalSize = 0;
	NTripodProt::TVecTripodHelp vecSendData;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwPageSize >> dwTotalSize >> vecSendData;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 31, Function: 9";
		return false;
	}
	OnRecv_SendAllTripodHelper(dwPageSize, dwTotalSize, vecSendData);
	return true;
}

bool CCenter2DBCommClt::_DoRecv_SendAllTripodLog(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwPageSize = 0;
	UINT32 dwTotalSize = 0;
	NTripodProt::TVecTripodLog vecSendData;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwPageSize >> dwTotalSize >> vecSendData;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 31, Function: 10";
		return false;
	}
	OnRecv_SendAllTripodLog(dwPageSize, dwTotalSize, vecSendData);
	return true;
}

bool CCenter2DBCommClt::_DoRecv_PlatformParamInfoNotify(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwCurSize = 0;
	UINT32 dwTotalSize = 0;
	TVecUINT64 vecRoleID;
	NProtoCommon::TVecPlatformParam vecPlatformParam;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwCurSize >> dwTotalSize >> vecRoleID >> vecPlatformParam;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 31, Function: 11";
		return false;
	}
	OnRecv_PlatformParamInfoNotify(dwCurSize, dwTotalSize, vecRoleID, vecPlatformParam);
	return true;
}

bool CCenter2DBCommClt::_DoRecv_SendAllShip(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwPageSize = 0;
	UINT32 dwTotalSize = 0;
	NShipProt::TVecPlayerShip vecSendDate;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwPageSize >> dwTotalSize >> vecSendDate;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 31, Function: 12";
		return false;
	}
	OnRecv_SendAllShip(dwPageSize, dwTotalSize, vecSendDate);
	return true;
}

bool CCenter2DBCommClt::_DoReturn_GetStatus(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoReturn exception: " << szExcept << ", Protocol: 31, Function: 2";
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

void CCenter2DBCommClt::_OnTimeOut_GetStatus(UINT32 dwSessionID)
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

bool CCenter2DBCommClt::_DoReturn_LoadPrepaid(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	bool bRet_ = false;
	NRoleInfoDefine::TVecPrepaid vecPrepaid;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> bRet_ >> vecPrepaid;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoReturn exception: " << szExcept << ", Protocol: 31, Function: 4";
		return false;
	}
	UINT8 byRet_ = 0;
	if(!bRet_)
		byRet_ = 1;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		const NRoleInfoDefine::TVecPrepaid& vecPrepaid //(返回值)玩家未创角预先值信息
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID_));
	if(pSessData_ == NULL)
		return false;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(byRet_, vecPrepaid);
	if(_pSessionMgr != NULL)
		_pSessionMgr->DelSession(dwSessionID_);
	return true;
}

void CCenter2DBCommClt::_OnTimeOut_LoadPrepaid(UINT32 dwSessionID)
{
	NRoleInfoDefine::TVecPrepaid vecPrepaid;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		const NRoleInfoDefine::TVecPrepaid& vecPrepaid //(返回值)玩家未创角预先值信息
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID));
	if(pSessData_ == NULL)
		return;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(2, vecPrepaid);
}

bool CCenter2DBCommClt::_DoReturn_ReplaceUser(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoReturn exception: " << szExcept << ", Protocol: 31, Function: 6";
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

void CCenter2DBCommClt::_OnTimeOut_ReplaceUser(UINT32 dwSessionID)
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

bool CCenter2DBCommClt::_DoReturn_LoadOffLineUserData(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	bool bRet_ = false;
	UINT8 byRet = 0;
	NRoleInfoDefine::RoleDataInfo RoleData;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> bRet_ >> byRet >> RoleData;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoReturn exception: " << szExcept << ", Protocol: 31, Function: 7";
		return false;
	}
	UINT8 byRet_ = 0;
	if(!bRet_)
		byRet_ = 1;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT8 byRet, //(返回值)0表示成功
		const NRoleInfoDefine::RoleDataInfo& RoleData //(返回值)玩家数据
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID_));
	if(pSessData_ == NULL)
		return false;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(byRet_, byRet, RoleData);
	if(_pSessionMgr != NULL)
		_pSessionMgr->DelSession(dwSessionID_);
	return true;
}

void CCenter2DBCommClt::_OnTimeOut_LoadOffLineUserData(UINT32 dwSessionID)
{
	UINT8 byRet = 0;
	NRoleInfoDefine::RoleDataInfo RoleData;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT8 byRet, //(返回值)0表示成功
		const NRoleInfoDefine::RoleDataInfo& RoleData //(返回值)玩家数据
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID));
	if(pSessData_ == NULL)
		return;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(2, byRet, RoleData);
}

bool CCenter2DBCommClt::_DoReturn_GetUserIDFromName(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	bool bRet_ = false;
	UINT64 qwUsrID = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> bRet_ >> qwUsrID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoReturn exception: " << szExcept << ", Protocol: 31, Function: 14";
		return false;
	}
	UINT8 byRet_ = 0;
	if(!bRet_)
		byRet_ = 1;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT64 qwUsrID //(返回值)用户ID
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID_));
	if(pSessData_ == NULL)
		return false;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(byRet_, qwUsrID);
	if(_pSessionMgr != NULL)
		_pSessionMgr->DelSession(dwSessionID_);
	return true;
}

void CCenter2DBCommClt::_OnTimeOut_GetUserIDFromName(UINT32 dwSessionID)
{
	UINT64 qwUsrID = 0;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT64 qwUsrID //(返回值)用户ID
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID));
	if(pSessData_ == NULL)
		return;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(2, qwUsrID);
}

bool CCenter2DBCommClt::_DoReturn_GetAllMailList(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	bool bRet_ = false;
	NMailProt::TVecMailDetail vecMails;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> bRet_ >> vecMails;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoReturn exception: " << szExcept << ", Protocol: 31, Function: 15";
		return false;
	}
	UINT8 byRet_ = 0;
	if(!bRet_)
		byRet_ = 1;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		const NMailProt::TVecMailDetail& vecMails //(返回值)邮件列表
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID_));
	if(pSessData_ == NULL)
		return false;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(byRet_, vecMails);
	if(_pSessionMgr != NULL)
		_pSessionMgr->DelSession(dwSessionID_);
	return true;
}

void CCenter2DBCommClt::_OnTimeOut_GetAllMailList(UINT32 dwSessionID)
{
	NMailProt::TVecMailDetail vecMails;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		const NMailProt::TVecMailDetail& vecMails //(返回值)邮件列表
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID));
	if(pSessData_ == NULL)
		return;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(2, vecMails);
}

bool CCenter2DBCommClt::_DoReturn_SaveMail(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	bool bRet_ = false;
	INT8 byRet = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> bRet_ >> byRet;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoReturn exception: " << szExcept << ", Protocol: 31, Function: 16";
		return false;
	}
	UINT8 byRet_ = 0;
	if(!bRet_)
		byRet_ = 1;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		INT8 byRet //(返回值)非0表示失败
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

void CCenter2DBCommClt::_OnTimeOut_SaveMail(UINT32 dwSessionID)
{
	INT8 byRet = 0;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		INT8 byRet //(返回值)非0表示失败
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

bool CCenter2DBCommClt::_DoReturn_DeleteMail(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	bool bRet_ = false;
	INT8 byRet = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> bRet_ >> byRet;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoReturn exception: " << szExcept << ", Protocol: 31, Function: 17";
		return false;
	}
	UINT8 byRet_ = 0;
	if(!bRet_)
		byRet_ = 1;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		INT8 byRet //(返回值)非0表示失败
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

void CCenter2DBCommClt::_OnTimeOut_DeleteMail(UINT32 dwSessionID)
{
	INT8 byRet = 0;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		INT8 byRet //(返回值)非0表示失败
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

bool CCenter2DBCommClt::_DoReturn_SaveSystemMail(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	bool bRet_ = false;
	INT8 byRet = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> bRet_ >> byRet;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoReturn exception: " << szExcept << ", Protocol: 31, Function: 18";
		return false;
	}
	UINT8 byRet_ = 0;
	if(!bRet_)
		byRet_ = 1;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		INT8 byRet //(返回值)非0表示失败
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

void CCenter2DBCommClt::_OnTimeOut_SaveSystemMail(UINT32 dwSessionID)
{
	INT8 byRet = 0;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		INT8 byRet //(返回值)非0表示失败
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

bool CCenter2DBCommClt::_DoReturn_UpdateMailStatus(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	bool bRet_ = false;
	INT8 byRet = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> bRet_ >> byRet;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoReturn exception: " << szExcept << ", Protocol: 31, Function: 19";
		return false;
	}
	UINT8 byRet_ = 0;
	if(!bRet_)
		byRet_ = 1;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		INT8 byRet //(返回值)非0表示失败
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

void CCenter2DBCommClt::_OnTimeOut_UpdateMailStatus(UINT32 dwSessionID)
{
	INT8 byRet = 0;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		INT8 byRet //(返回值)非0表示失败
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

bool CCenter2DBCommClt::_DoReturn_DelMailAttach(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	bool bRet_ = false;
	INT8 byRet = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> bRet_ >> byRet;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoReturn exception: " << szExcept << ", Protocol: 31, Function: 20";
		return false;
	}
	UINT8 byRet_ = 0;
	if(!bRet_)
		byRet_ = 1;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		INT8 byRet //(返回值)非0表示失败
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

void CCenter2DBCommClt::_OnTimeOut_DelMailAttach(UINT32 dwSessionID)
{
	INT8 byRet = 0;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		INT8 byRet //(返回值)非0表示失败
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

bool CCenter2DBCommClt::_DoReturn_GetPrizeStatus(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	bool bRet_ = false;
	NWonderActivityProt::TVecWonderPrize2DB vecRet;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> bRet_ >> vecRet;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoReturn exception: " << szExcept << ", Protocol: 31, Function: 21";
		return false;
	}
	UINT8 byRet_ = 0;
	if(!bRet_)
		byRet_ = 1;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		const NWonderActivityProt::TVecWonderPrize2DB& vecRet //(返回值)查询结果
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID_));
	if(pSessData_ == NULL)
		return false;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(byRet_, vecRet);
	if(_pSessionMgr != NULL)
		_pSessionMgr->DelSession(dwSessionID_);
	return true;
}

void CCenter2DBCommClt::_OnTimeOut_GetPrizeStatus(UINT32 dwSessionID)
{
	NWonderActivityProt::TVecWonderPrize2DB vecRet;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		const NWonderActivityProt::TVecWonderPrize2DB& vecRet //(返回值)查询结果
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID));
	if(pSessData_ == NULL)
		return;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(2, vecRet);
}

bool CCenter2DBCommClt::_DoReturn_GetAllRoleLevel(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	bool bRet_ = false;
	UINT8 byTypeRet = 0;
	TVecRoleLevel vecRoleLevel;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> bRet_ >> byTypeRet >> vecRoleLevel;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoReturn exception: " << szExcept << ", Protocol: 31, Function: 23";
		return false;
	}
	UINT8 byRet_ = 0;
	if(!bRet_)
		byRet_ = 1;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT8 byTypeRet, //(返回值)类型
		const TVecRoleLevel& vecRoleLevel //(返回值)返回玩家等级
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID_));
	if(pSessData_ == NULL)
		return false;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(byRet_, byTypeRet, vecRoleLevel);
	if(_pSessionMgr != NULL)
		_pSessionMgr->DelSession(dwSessionID_);
	return true;
}

void CCenter2DBCommClt::_OnTimeOut_GetAllRoleLevel(UINT32 dwSessionID)
{
	UINT8 byTypeRet = 0;
	TVecRoleLevel vecRoleLevel;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT8 byTypeRet, //(返回值)类型
		const TVecRoleLevel& vecRoleLevel //(返回值)返回玩家等级
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID));
	if(pSessData_ == NULL)
		return;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(2, byTypeRet, vecRoleLevel);
}

bool CCenter2DBCommClt::_DoReturn_GetRetain(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	bool bRet_ = false;
	NWonderActivityProt::TVecRetain vecRet;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> bRet_ >> vecRet;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoReturn exception: " << szExcept << ", Protocol: 31, Function: 25";
		return false;
	}
	UINT8 byRet_ = 0;
	if(!bRet_)
		byRet_ = 1;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		const NWonderActivityProt::TVecRetain& vecRet //(返回值)查询结果
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID_));
	if(pSessData_ == NULL)
		return false;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(byRet_, vecRet);
	if(_pSessionMgr != NULL)
		_pSessionMgr->DelSession(dwSessionID_);
	return true;
}

void CCenter2DBCommClt::_OnTimeOut_GetRetain(UINT32 dwSessionID)
{
	NWonderActivityProt::TVecRetain vecRet;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		const NWonderActivityProt::TVecRetain& vecRet //(返回值)查询结果
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID));
	if(pSessData_ == NULL)
		return;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(2, vecRet);
}

bool CCenter2DBCommClt::_DoReturn_GetGameVar(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	bool bRet_ = false;
	NRoleInfoDefine::TVecGameVarsDBInfo vecVar;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> bRet_ >> vecVar;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoReturn exception: " << szExcept << ", Protocol: 31, Function: 35";
		return false;
	}
	UINT8 byRet_ = 0;
	if(!bRet_)
		byRet_ = 1;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		const NRoleInfoDefine::TVecGameVarsDBInfo& vecVar //(返回值)返回的Var
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID_));
	if(pSessData_ == NULL)
		return false;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(byRet_, vecVar);
	if(_pSessionMgr != NULL)
		_pSessionMgr->DelSession(dwSessionID_);
	return true;
}

void CCenter2DBCommClt::_OnTimeOut_GetGameVar(UINT32 dwSessionID)
{
	NRoleInfoDefine::TVecGameVarsDBInfo vecVar;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		const NRoleInfoDefine::TVecGameVarsDBInfo& vecVar //(返回值)返回的Var
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID));
	if(pSessData_ == NULL)
		return;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(2, vecVar);
}

bool CCenter2DBCommClt::_DoReturn_GetArenaFighterByID(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	bool bRet_ = false;
	NArenaGS::SArenaFighter stFighter;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> bRet_ >> stFighter;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoReturn exception: " << szExcept << ", Protocol: 31, Function: 39";
		return false;
	}
	UINT8 byRet_ = 0;
	if(!bRet_)
		byRet_ = 1;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		const NArenaGS::SArenaFighter& stFighter //(返回值)返回的数据
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID_));
	if(pSessData_ == NULL)
		return false;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(byRet_, stFighter);
	if(_pSessionMgr != NULL)
		_pSessionMgr->DelSession(dwSessionID_);
	return true;
}

void CCenter2DBCommClt::_OnTimeOut_GetArenaFighterByID(UINT32 dwSessionID)
{
	NArenaGS::SArenaFighter stFighter;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		const NArenaGS::SArenaFighter& stFighter //(返回值)返回的数据
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID));
	if(pSessData_ == NULL)
		return;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(2, stFighter);
}

bool CCenter2DBCommClt::_DoReturn_GetDemonTowerInfo(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	bool bRet_ = false;
	NDemonTowerGS::TVecDemonTowerPlayer vecDemonTowerPlayer;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> bRet_ >> vecDemonTowerPlayer;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoReturn exception: " << szExcept << ", Protocol: 31, Function: 40";
		return false;
	}
	UINT8 byRet_ = 0;
	if(!bRet_)
		byRet_ = 1;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		const NDemonTowerGS::TVecDemonTowerPlayer& vecDemonTowerPlayer //(返回值)镇妖塔玩家信息
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID_));
	if(pSessData_ == NULL)
		return false;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(byRet_, vecDemonTowerPlayer);
	if(_pSessionMgr != NULL)
		_pSessionMgr->DelSession(dwSessionID_);
	return true;
}

void CCenter2DBCommClt::_OnTimeOut_GetDemonTowerInfo(UINT32 dwSessionID)
{
	NDemonTowerGS::TVecDemonTowerPlayer vecDemonTowerPlayer;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		const NDemonTowerGS::TVecDemonTowerPlayer& vecDemonTowerPlayer //(返回值)镇妖塔玩家信息
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID));
	if(pSessData_ == NULL)
		return;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(2, vecDemonTowerPlayer);
}

bool CCenter2DBCommClt::_DoReturn_GetCenterData(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	bool bRet_ = false;
	TVecCenterData vecCenterData;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> bRet_ >> vecCenterData;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoReturn exception: " << szExcept << ", Protocol: 31, Function: 42";
		return false;
	}
	UINT8 byRet_ = 0;
	if(!bRet_)
		byRet_ = 1;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		const TVecCenterData& vecCenterData //(返回值)中心服数据
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID_));
	if(pSessData_ == NULL)
		return false;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(byRet_, vecCenterData);
	if(_pSessionMgr != NULL)
		_pSessionMgr->DelSession(dwSessionID_);
	return true;
}

void CCenter2DBCommClt::_OnTimeOut_GetCenterData(UINT32 dwSessionID)
{
	TVecCenterData vecCenterData;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		const TVecCenterData& vecCenterData //(返回值)中心服数据
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID));
	if(pSessData_ == NULL)
		return;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(2, vecCenterData);
}

bool CCenter2DBCommClt::_DoReturn_GetWhisperInfo(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	bool bRet_ = false;
	NGlobalChatProt::SWhisperInfo whisperInfo;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> bRet_ >> whisperInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoReturn exception: " << szExcept << ", Protocol: 31, Function: 44";
		return false;
	}
	UINT8 byRet_ = 0;
	if(!bRet_)
		byRet_ = 1;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		const NGlobalChatProt::SWhisperInfo& whisperInfo //(返回值)返回的数据
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID_));
	if(pSessData_ == NULL)
		return false;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(byRet_, whisperInfo);
	if(_pSessionMgr != NULL)
		_pSessionMgr->DelSession(dwSessionID_);
	return true;
}

void CCenter2DBCommClt::_OnTimeOut_GetWhisperInfo(UINT32 dwSessionID)
{
	NGlobalChatProt::SWhisperInfo whisperInfo;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		const NGlobalChatProt::SWhisperInfo& whisperInfo //(返回值)返回的数据
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID));
	if(pSessData_ == NULL)
		return;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(2, whisperInfo);
}

bool CCenter2DBCommClt::_DoReturn_GetBattleReport(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	bool bRet_ = false;
	NRoleInfoDefine::TVecBattleRePort vecReport;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> bRet_ >> vecReport;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoReturn exception: " << szExcept << ", Protocol: 31, Function: 45";
		return false;
	}
	UINT8 byRet_ = 0;
	if(!bRet_)
		byRet_ = 1;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		const NRoleInfoDefine::TVecBattleRePort& vecReport //(返回值)返回的数据
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID_));
	if(pSessData_ == NULL)
		return false;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(byRet_, vecReport);
	if(_pSessionMgr != NULL)
		_pSessionMgr->DelSession(dwSessionID_);
	return true;
}

void CCenter2DBCommClt::_OnTimeOut_GetBattleReport(UINT32 dwSessionID)
{
	NRoleInfoDefine::TVecBattleRePort vecReport;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		const NRoleInfoDefine::TVecBattleRePort& vecReport //(返回值)返回的数据
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID));
	if(pSessData_ == NULL)
		return;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(2, vecReport);
}

bool CCenter2DBCommClt::_DoReturn_AddBattleReport(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	bool bRet_ = false;
	TVecUINT64 vecBattleID;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> bRet_ >> vecBattleID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoReturn exception: " << szExcept << ", Protocol: 31, Function: 46";
		return false;
	}
	UINT8 byRet_ = 0;
	if(!bRet_)
		byRet_ = 1;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		const TVecUINT64& vecBattleID //(返回值)删除的战报
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID_));
	if(pSessData_ == NULL)
		return false;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(byRet_, vecBattleID);
	if(_pSessionMgr != NULL)
		_pSessionMgr->DelSession(dwSessionID_);
	return true;
}

void CCenter2DBCommClt::_OnTimeOut_AddBattleReport(UINT32 dwSessionID)
{
	TVecUINT64 vecBattleID;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		const TVecUINT64& vecBattleID //(返回值)删除的战报
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID));
	if(pSessData_ == NULL)
		return;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(2, vecBattleID);
}

bool CCenter2DBCommClt::_DoReturn_GetGodMonsterInfo(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	bool bRet_ = false;
	NGodMonsterProt::TVecGuildUser2DB vecUser;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> bRet_ >> vecUser;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoReturn exception: " << szExcept << ", Protocol: 31, Function: 66";
		return false;
	}
	UINT8 byRet_ = 0;
	if(!bRet_)
		byRet_ = 1;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		const NGodMonsterProt::TVecGuildUser2DB& vecUser //(返回值)天元神兽玩家信息
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID_));
	if(pSessData_ == NULL)
		return false;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(byRet_, vecUser);
	if(_pSessionMgr != NULL)
		_pSessionMgr->DelSession(dwSessionID_);
	return true;
}

void CCenter2DBCommClt::_OnTimeOut_GetGodMonsterInfo(UINT32 dwSessionID)
{
	NGodMonsterProt::TVecGuildUser2DB vecUser;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		const NGodMonsterProt::TVecGuildUser2DB& vecUser //(返回值)天元神兽玩家信息
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID));
	if(pSessData_ == NULL)
		return;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(2, vecUser);
}

bool CCenter2DBCommClt::_DoReturn_GetLimitPrizeInfo(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	bool bRet_ = false;
	NGodMonsterProt::TVecLimitPrize2DB vecLimitPrize;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> bRet_ >> vecLimitPrize;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoReturn exception: " << szExcept << ", Protocol: 31, Function: 68";
		return false;
	}
	UINT8 byRet_ = 0;
	if(!bRet_)
		byRet_ = 1;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		const NGodMonsterProt::TVecLimitPrize2DB& vecLimitPrize //(返回值)数据
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID_));
	if(pSessData_ == NULL)
		return false;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(byRet_, vecLimitPrize);
	if(_pSessionMgr != NULL)
		_pSessionMgr->DelSession(dwSessionID_);
	return true;
}

void CCenter2DBCommClt::_OnTimeOut_GetLimitPrizeInfo(UINT32 dwSessionID)
{
	NGodMonsterProt::TVecLimitPrize2DB vecLimitPrize;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		const NGodMonsterProt::TVecLimitPrize2DB& vecLimitPrize //(返回值)数据
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID));
	if(pSessData_ == NULL)
		return;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(2, vecLimitPrize);
}

bool CCenter2DBCommClt::_DoReturn_GetActivityCenterInfo(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	bool bRet_ = false;
	NProtoCommon::TVecActivityOpt vecActOpt;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> bRet_ >> vecActOpt;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoReturn exception: " << szExcept << ", Protocol: 31, Function: 70";
		return false;
	}
	UINT8 byRet_ = 0;
	if(!bRet_)
		byRet_ = 1;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		const NProtoCommon::TVecActivityOpt& vecActOpt //(返回值)数据
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID_));
	if(pSessData_ == NULL)
		return false;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(byRet_, vecActOpt);
	if(_pSessionMgr != NULL)
		_pSessionMgr->DelSession(dwSessionID_);
	return true;
}

void CCenter2DBCommClt::_OnTimeOut_GetActivityCenterInfo(UINT32 dwSessionID)
{
	NProtoCommon::TVecActivityOpt vecActOpt;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		const NProtoCommon::TVecActivityOpt& vecActOpt //(返回值)数据
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID));
	if(pSessData_ == NULL)
		return;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(2, vecActOpt);
}

} //namespace NCenter2DBComm
