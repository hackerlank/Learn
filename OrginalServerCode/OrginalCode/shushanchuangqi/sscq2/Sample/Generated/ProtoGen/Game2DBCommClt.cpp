/************************************************************************
//  工具自动生成的客户端协议代码(UTF-8 With BOM)
//  File Name:    Game2DBComm.cpp
//  Purpose:      GameServer到DBServer的通信协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "Game2DBCommClt.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NGame2DBComm
{

CGame2DBCommClt::THandleFunc CGame2DBCommClt::_ReturnFuncs[] =
{
	&CGame2DBCommClt::_DoReturn_GetStatus, //FuncID: -1
	&CGame2DBCommClt::_DoReturn_SaveUserDataReq, //FuncID: -2
	&CGame2DBCommClt::_DoReturn_SaveOffLineDgnInfo, //FuncID: -3
	&CGame2DBCommClt::_DoReturn_LoadOffLineUserData, //FuncID: -4
	&CGame2DBCommClt::_DoReturn_LoadWorldBossInfo, //FuncID: -5
	&CGame2DBCommClt::_DoReturn_GetUserIDFromName, //FuncID: -6
	&CGame2DBCommClt::_DoReturn_GetBattleReport, //FuncID: -7
	&CGame2DBCommClt::_DoReturn_AddBattleReport, //FuncID: -8
	&CGame2DBCommClt::_DoReturn_LoadMallDiscount, //FuncID: -9
};

CGame2DBCommClt::THandleFunc CGame2DBCommClt::_HandleFuncs[] =
{
	&CGame2DBCommClt::_DoRecv_UserPackageProxy, //FuncID: 1
	&CGame2DBCommClt::_DoRecv_UserLoginNtf, //FuncID: 2
	&CGame2DBCommClt::_DoRecv_UserReEnterNotify, //FuncID: 3
	&CGame2DBCommClt::_DoRecv_UserLogoutNtf, //FuncID: 4
	&CGame2DBCommClt::_DoRecv_NewOffEventNotice, //FuncID: 5
	&CGame2DBCommClt::_DoRecv_NewGuildBattleHistoryNotify, //FuncID: 6
};

CGame2DBCommClt::TTimeOutFunc CGame2DBCommClt::_TimeoutFuncs[] =
{
	&CGame2DBCommClt::_OnTimeOut_GetStatus, //FuncID: 1
	&CGame2DBCommClt::_OnTimeOut_SaveUserDataReq, //FuncID: 2
	&CGame2DBCommClt::_OnTimeOut_SaveOffLineDgnInfo, //FuncID: 3
	&CGame2DBCommClt::_OnTimeOut_LoadOffLineUserData, //FuncID: 4
	&CGame2DBCommClt::_OnTimeOut_LoadWorldBossInfo, //FuncID: 5
	&CGame2DBCommClt::_OnTimeOut_GetUserIDFromName, //FuncID: 6
	&CGame2DBCommClt::_OnTimeOut_GetBattleReport, //FuncID: 7
	&CGame2DBCommClt::_OnTimeOut_AddBattleReport, //FuncID: 8
	&CGame2DBCommClt::_OnTimeOut_LoadMallDiscount, //FuncID: 9
};

bool CGame2DBCommClt::HandleMessage(const char* pBuf, UINT32 dwLen)
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

void CGame2DBCommClt::OnTimeOut(UINT8 byFuncID, UINT32 dwSessionID)
{
	if(byFuncID == 0 || byFuncID > (UINT8)ARRAYSIZE(_TimeoutFuncs))
		return;
	(this->*_TimeoutFuncs[byFuncID - 1])(dwSessionID);
}

//发送：心跳
bool CGame2DBCommClt::Send_KeepAlive(
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
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 4, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2DBCommClt::SendSvr_KeepAlive(const UINT32* pSvrID_, UINT8 byCnt_
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
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 4, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGame2DBCommClt::BuildPkg_KeepAlive(
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
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 4, Function: 1";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：DBServer状态请求
bool CGame2DBCommClt::Send_GetStatus(
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
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 4, Function: 2";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2DBCommClt::SendSvr_GetStatus(const UINT32* pSvrID_, UINT8 byCnt_,
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
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 4, Function: 2";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

//发送：更新玩家充值仙石信息
bool CGame2DBCommClt::Send_UpdateRecharge(
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
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 4, Function: 3";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2DBCommClt::SendSvr_UpdateRecharge(const UINT32* pSvrID_, UINT8 byCnt_,
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
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 4, Function: 3";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGame2DBCommClt::BuildPkg_UpdateRecharge(
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
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 4, Function: 3";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：一行数据更新
bool CGame2DBCommClt::Send_RoleDataUpdate(
	UINT64 qwRoleId, //角色Id
	NRoleInfoDefine::EDataType eDataType, //更新数据块
	NProtoCommon::EDataChange eUpdateType, //更新类型，增加，删除，修改
	const std::string& strData //更新数据
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << qwRoleId << (UINT8&)eDataType << (UINT8&)eUpdateType << strData;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 4, Function: 4";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2DBCommClt::SendSvr_RoleDataUpdate(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwRoleId, //角色Id
	NRoleInfoDefine::EDataType eDataType, //更新数据块
	NProtoCommon::EDataChange eUpdateType, //更新类型，增加，删除，修改
	const std::string& strData //更新数据
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << qwRoleId << (UINT8&)eDataType << (UINT8&)eUpdateType << strData;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 4, Function: 4";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGame2DBCommClt::BuildPkg_RoleDataUpdate(
	UINT64 qwRoleId, //角色Id
	NRoleInfoDefine::EDataType eDataType, //更新数据块
	NProtoCommon::EDataChange eUpdateType, //更新类型，增加，删除，修改
	const std::string& strData //更新数据
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << qwRoleId << (UINT8&)eDataType << (UINT8&)eUpdateType << strData;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 4, Function: 4";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：请求保存账号数据
bool CGame2DBCommClt::Send_SaveUserDataReq(
	UINT64 qwUsrID, //账号ID
	ESaveType eSaveType, //保存类型
	const NProtoCommon::TVecPlatformParam& vecPlatformParam, //平台参数列表
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT64 qwUsrID, //(本地保存的函数参数)账号ID
		ESaveType eSaveType //(本地保存的函数参数)保存类型
	)> fnOnReturn_ //返回时的回调函数
)
{
	if(_pSessionMgr == NULL)
	{
		LOG_CRI << "_pSessionMgr == NULL";		return false;
	}
	UINT32 dwSessionID_ = _pSessionMgr->GetNewSession(*this, 2);
	typedef std::tuple<decltype(fnOnReturn_), UINT64, ESaveType> TSessData;
	std::shared_ptr<TSessData> pSessData_(new TSessData(fnOnReturn_, qwUsrID, eSaveType));
	_pSessionMgr->StoreData(dwSessionID_, pSessData_);
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 5;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwUsrID << (UINT8&)eSaveType << vecPlatformParam;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 4, Function: 5";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2DBCommClt::SendSvr_SaveUserDataReq(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwUsrID, //账号ID
	ESaveType eSaveType, //保存类型
	const NProtoCommon::TVecPlatformParam& vecPlatformParam, //平台参数列表
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT64 qwUsrID, //(本地保存的函数参数)账号ID
		ESaveType eSaveType //(本地保存的函数参数)保存类型
	)> fnOnReturn_ //返回时的回调函数
)
{
	if(_pSessionMgr == NULL)
	{
		LOG_CRI << "_pSessionMgr == NULL";		return false;
	}
	UINT32 dwSessionID_ = _pSessionMgr->GetNewSession(*this, 2);
	typedef std::tuple<decltype(fnOnReturn_), UINT64, ESaveType> TSessData;
	std::shared_ptr<TSessData> pSessData_(new TSessData(fnOnReturn_, qwUsrID, eSaveType));
	_pSessionMgr->StoreData(dwSessionID_, pSessData_);
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 5;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwUsrID << (UINT8&)eSaveType << vecPlatformParam;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 4, Function: 5";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

//发送：副本结束时候，玩家不在gameserver的数据保存
bool CGame2DBCommClt::Send_SaveOffLineDgnInfo(
	UINT64 qwUsrID, //账号ID
	UINT32 dwDgnType, //副本类型
	UINT8 byIsFail, //0:表示成功保存，1：表示失败保存
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT64 qwUsrID, //(本地保存的函数参数)账号ID
		UINT32 dwDgnType //(本地保存的函数参数)副本类型
	)> fnOnReturn_ //返回时的回调函数
)
{
	if(_pSessionMgr == NULL)
	{
		LOG_CRI << "_pSessionMgr == NULL";		return false;
	}
	UINT32 dwSessionID_ = _pSessionMgr->GetNewSession(*this, 3);
	typedef std::tuple<decltype(fnOnReturn_), UINT64, UINT32> TSessData;
	std::shared_ptr<TSessData> pSessData_(new TSessData(fnOnReturn_, qwUsrID, dwDgnType));
	_pSessionMgr->StoreData(dwSessionID_, pSessData_);
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 6;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwUsrID << dwDgnType << byIsFail;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 4, Function: 6";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2DBCommClt::SendSvr_SaveOffLineDgnInfo(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwUsrID, //账号ID
	UINT32 dwDgnType, //副本类型
	UINT8 byIsFail, //0:表示成功保存，1：表示失败保存
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT64 qwUsrID, //(本地保存的函数参数)账号ID
		UINT32 dwDgnType //(本地保存的函数参数)副本类型
	)> fnOnReturn_ //返回时的回调函数
)
{
	if(_pSessionMgr == NULL)
	{
		LOG_CRI << "_pSessionMgr == NULL";		return false;
	}
	UINT32 dwSessionID_ = _pSessionMgr->GetNewSession(*this, 3);
	typedef std::tuple<decltype(fnOnReturn_), UINT64, UINT32> TSessData;
	std::shared_ptr<TSessData> pSessData_(new TSessData(fnOnReturn_, qwUsrID, dwDgnType));
	_pSessionMgr->StoreData(dwSessionID_, pSessData_);
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 6;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwUsrID << dwDgnType << byIsFail;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 4, Function: 6";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

//发送：加载离线玩家数据
bool CGame2DBCommClt::Send_LoadOffLineUserData(
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
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 4, Function: 7";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2DBCommClt::SendSvr_LoadOffLineUserData(const UINT32* pSvrID_, UINT8 byCnt_,
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
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 4, Function: 7";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

//发送：加载世界BOSS信息请求
bool CGame2DBCommClt::Send_LoadWorldBossInfo(
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		const TVecWBossDBInfo& vecWorldBossInfo //(返回值)世界BOSS信息
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
	const UINT8 byFuncID_ = 8;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 4, Function: 8";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2DBCommClt::SendSvr_LoadWorldBossInfo(const UINT32* pSvrID_, UINT8 byCnt_,
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		const TVecWBossDBInfo& vecWorldBossInfo //(返回值)世界BOSS信息
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
	const UINT8 byFuncID_ = 8;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 4, Function: 8";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

//发送：存储世界BOSS信息
bool CGame2DBCommClt::Send_SaveWorldBossInfo(
	const SWBossDBInfo& sWorldBossInfo //世界BOSS信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 9;
	try
	{
		ar << byProtID_ << byFuncID_ << sWorldBossInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 4, Function: 9";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2DBCommClt::SendSvr_SaveWorldBossInfo(const UINT32* pSvrID_, UINT8 byCnt_,
	const SWBossDBInfo& sWorldBossInfo //世界BOSS信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 9;
	try
	{
		ar << byProtID_ << byFuncID_ << sWorldBossInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 4, Function: 9";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGame2DBCommClt::BuildPkg_SaveWorldBossInfo(
	const SWBossDBInfo& sWorldBossInfo //世界BOSS信息
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 9;
	try
	{
		ar << byProtID_ << byFuncID_ << sWorldBossInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 4, Function: 9";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：根据名字获取ID请求
bool CGame2DBCommClt::Send_GetUserIDFromName(
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
	UINT32 dwSessionID_ = _pSessionMgr->GetNewSession(*this, 6);
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_(new TSessData(fnOnReturn_));
	_pSessionMgr->StoreData(dwSessionID_, pSessData_);
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 10;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << strName;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 4, Function: 10";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2DBCommClt::SendSvr_GetUserIDFromName(const UINT32* pSvrID_, UINT8 byCnt_,
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
	UINT32 dwSessionID_ = _pSessionMgr->GetNewSession(*this, 6);
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_(new TSessData(fnOnReturn_));
	_pSessionMgr->StoreData(dwSessionID_, pSessData_);
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 10;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << strName;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 4, Function: 10";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

//发送：获得玩家战报信息
bool CGame2DBCommClt::Send_GetBattleReport(
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
	UINT32 dwSessionID_ = _pSessionMgr->GetNewSession(*this, 7);
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_(new TSessData(fnOnReturn_));
	_pSessionMgr->StoreData(dwSessionID_, pSessData_);
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 11;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwRoleID << (UINT8&)eBattleType << (UINT8&)eAction;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 4, Function: 11";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2DBCommClt::SendSvr_GetBattleReport(const UINT32* pSvrID_, UINT8 byCnt_,
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
	UINT32 dwSessionID_ = _pSessionMgr->GetNewSession(*this, 7);
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_(new TSessData(fnOnReturn_));
	_pSessionMgr->StoreData(dwSessionID_, pSessData_);
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 11;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwRoleID << (UINT8&)eBattleType << (UINT8&)eAction;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 4, Function: 11";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

//发送：增加玩家战报信息
bool CGame2DBCommClt::Send_AddBattleReport(
	UINT64 qwRoleID, //
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
	UINT32 dwSessionID_ = _pSessionMgr->GetNewSession(*this, 8);
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_(new TSessData(fnOnReturn_));
	_pSessionMgr->StoreData(dwSessionID_, pSessData_);
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 12;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwRoleID << sReport << byNum;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 4, Function: 12";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2DBCommClt::SendSvr_AddBattleReport(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwRoleID, //
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
	UINT32 dwSessionID_ = _pSessionMgr->GetNewSession(*this, 8);
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_(new TSessData(fnOnReturn_));
	_pSessionMgr->StoreData(dwSessionID_, pSessData_);
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 12;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwRoleID << sReport << byNum;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 4, Function: 12";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

//发送：增加离线事件
bool CGame2DBCommClt::Send_AddOffLineEvent(
	const TVecUINT64& vecRoleID, //
	const NRoleInfoDefine::SEventOffLine& sEventData //事件类型
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 13;
	try
	{
		ar << byProtID_ << byFuncID_ << vecRoleID << sEventData;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 4, Function: 13";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2DBCommClt::SendSvr_AddOffLineEvent(const UINT32* pSvrID_, UINT8 byCnt_,
	const TVecUINT64& vecRoleID, //
	const NRoleInfoDefine::SEventOffLine& sEventData //事件类型
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 13;
	try
	{
		ar << byProtID_ << byFuncID_ << vecRoleID << sEventData;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 4, Function: 13";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGame2DBCommClt::BuildPkg_AddOffLineEvent(
	const TVecUINT64& vecRoleID, //
	const NRoleInfoDefine::SEventOffLine& sEventData //事件类型
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 13;
	try
	{
		ar << byProtID_ << byFuncID_ << vecRoleID << sEventData;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 4, Function: 13";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：删除离线事件
bool CGame2DBCommClt::Send_DelOffLineEvent(
	UINT64 qwRoleID, //
	const NRoleInfoDefine::TVecEventOffLine& vecEventType //事件类型
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 14;
	try
	{
		ar << byProtID_ << byFuncID_ << qwRoleID << vecEventType;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 4, Function: 14";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2DBCommClt::SendSvr_DelOffLineEvent(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwRoleID, //
	const NRoleInfoDefine::TVecEventOffLine& vecEventType //事件类型
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 14;
	try
	{
		ar << byProtID_ << byFuncID_ << qwRoleID << vecEventType;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 4, Function: 14";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGame2DBCommClt::BuildPkg_DelOffLineEvent(
	UINT64 qwRoleID, //
	const NRoleInfoDefine::TVecEventOffLine& vecEventType //事件类型
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 14;
	try
	{
		ar << byProtID_ << byFuncID_ << qwRoleID << vecEventType;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 4, Function: 14";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：加载商城限购信息
bool CGame2DBCommClt::Send_LoadMallDiscount(
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		const NMallProt::TVecDiscount& vecDisItems //(返回值)限购道具信息
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
	const UINT8 byFuncID_ = 15;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 4, Function: 15";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2DBCommClt::SendSvr_LoadMallDiscount(const UINT32* pSvrID_, UINT8 byCnt_,
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		const NMallProt::TVecDiscount& vecDisItems //(返回值)限购道具信息
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
	const UINT8 byFuncID_ = 15;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 4, Function: 15";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

//发送：更新商城限购
bool CGame2DBCommClt::Send_UpdateMallDiscount(
	NProtoCommon::EDataChange eUpdateType, //更新类型，增加，删除，修改
	const NMallProt::TVecDiscount& vecDisItems //限购道具
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 16;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eUpdateType << vecDisItems;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 4, Function: 16";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2DBCommClt::SendSvr_UpdateMallDiscount(const UINT32* pSvrID_, UINT8 byCnt_,
	NProtoCommon::EDataChange eUpdateType, //更新类型，增加，删除，修改
	const NMallProt::TVecDiscount& vecDisItems //限购道具
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 16;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eUpdateType << vecDisItems;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 4, Function: 16";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGame2DBCommClt::BuildPkg_UpdateMallDiscount(
	NProtoCommon::EDataChange eUpdateType, //更新类型，增加，删除，修改
	const NMallProt::TVecDiscount& vecDisItems //限购道具
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 16;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eUpdateType << vecDisItems;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 4, Function: 16";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：获取新帮派战历史
bool CGame2DBCommClt::Send_GetNewGuildBattleHistory(
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 17;
	try
	{
		ar << byProtID_ << byFuncID_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 4, Function: 17";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2DBCommClt::SendSvr_GetNewGuildBattleHistory(const UINT32* pSvrID_, UINT8 byCnt_
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 17;
	try
	{
		ar << byProtID_ << byFuncID_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 4, Function: 17";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGame2DBCommClt::BuildPkg_GetNewGuildBattleHistory(
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 17;
	try
	{
		ar << byProtID_ << byFuncID_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 4, Function: 17";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：新增新帮派战历史
bool CGame2DBCommClt::Send_AddNewGuildBattleHistory(
	const TVecDBGuildNewBattleHistoryInfo& vecInfo //更新信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 18;
	try
	{
		ar << byProtID_ << byFuncID_ << vecInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 4, Function: 18";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGame2DBCommClt::SendSvr_AddNewGuildBattleHistory(const UINT32* pSvrID_, UINT8 byCnt_,
	const TVecDBGuildNewBattleHistoryInfo& vecInfo //更新信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 18;
	try
	{
		ar << byProtID_ << byFuncID_ << vecInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 4, Function: 18";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGame2DBCommClt::BuildPkg_AddNewGuildBattleHistory(
	const TVecDBGuildNewBattleHistoryInfo& vecInfo //更新信息
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 18;
	try
	{
		ar << byProtID_ << byFuncID_ << vecInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 4, Function: 18";
		_strPkg.clear();
	}
	return _strPkg;
}

bool CGame2DBCommClt::_DoRecv_UserPackageProxy(const char* pBuf_, UINT32 dwLen_)
{
	UINT64 qwUsrID = 0;
	UINT32 dwGateID = 0;
	TVecString vecPackage;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> qwUsrID >> dwGateID >> vecPackage;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 4, Function: 1";
		return false;
	}
	OnRecv_UserPackageProxy(qwUsrID, dwGateID, vecPackage);
	return true;
}

bool CGame2DBCommClt::_DoRecv_UserLoginNtf(const char* pBuf_, UINT32 dwLen_)
{
	EEnterType eEnterType = (EEnterType)0;
	NProtoCommon::TVecPlatformParam vecPlatformParam;
	TVecString vecEnterString;
	UINT32 dwGateId = 0;
	UINT64 qwUserId = 0;
	NRoleInfoDefine::RoleDataInfo RoleData;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> (UINT8&)eEnterType >> vecPlatformParam >> vecEnterString >> dwGateId >> qwUserId >> RoleData;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 4, Function: 2";
		return false;
	}
	OnRecv_UserLoginNtf(eEnterType, vecPlatformParam, vecEnterString, dwGateId, qwUserId, RoleData);
	return true;
}

bool CGame2DBCommClt::_DoRecv_UserReEnterNotify(const char* pBuf_, UINT32 dwLen_)
{
	UINT64 qwUsrID = 0;
	UINT32 dwGateID = 0;
	NProtoCommon::TVecPlatformParam vecPlatformParam;
	TVecString vecEnterString;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> qwUsrID >> dwGateID >> vecPlatformParam >> vecEnterString;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 4, Function: 3";
		return false;
	}
	OnRecv_UserReEnterNotify(qwUsrID, dwGateID, vecPlatformParam, vecEnterString);
	return true;
}

bool CGame2DBCommClt::_DoRecv_UserLogoutNtf(const char* pBuf_, UINT32 dwLen_)
{
	UINT64 qwUsrID = 0;
	NServerCommon::ELeaveType eLeaveType = (NServerCommon::ELeaveType)0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> qwUsrID >> (UINT8&)eLeaveType;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 4, Function: 4";
		return false;
	}
	OnRecv_UserLogoutNtf(qwUsrID, eLeaveType);
	return true;
}

bool CGame2DBCommClt::_DoRecv_NewOffEventNotice(const char* pBuf_, UINT32 dwLen_)
{
	UINT64 qwUsrID = 0;
	NRoleInfoDefine::SEventOffLine sEventData;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> qwUsrID >> sEventData;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 4, Function: 5";
		return false;
	}
	OnRecv_NewOffEventNotice(qwUsrID, sEventData);
	return true;
}

bool CGame2DBCommClt::_DoRecv_NewGuildBattleHistoryNotify(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwCurSize = 0;
	UINT32 dwTotalSize = 0;
	TVecDBGuildNewBattleHistoryInfo vecInfo;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwCurSize >> dwTotalSize >> vecInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 4, Function: 6";
		return false;
	}
	OnRecv_NewGuildBattleHistoryNotify(dwCurSize, dwTotalSize, vecInfo);
	return true;
}

bool CGame2DBCommClt::_DoReturn_GetStatus(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoReturn exception: " << szExcept << ", Protocol: 4, Function: 2";
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

void CGame2DBCommClt::_OnTimeOut_GetStatus(UINT32 dwSessionID)
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

bool CGame2DBCommClt::_DoReturn_SaveUserDataReq(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoReturn exception: " << szExcept << ", Protocol: 4, Function: 5";
		return false;
	}
	UINT8 byRet_ = 0;
	if(!bRet_)
		byRet_ = 1;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT64 qwUsrID, //(本地保存的函数参数)账号ID
		ESaveType eSaveType //(本地保存的函数参数)保存类型
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_), UINT64, ESaveType> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID_));
	if(pSessData_ == NULL)
		return false;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(byRet_, std::get<1>(*pSessData_), std::get<2>(*pSessData_));
	if(_pSessionMgr != NULL)
		_pSessionMgr->DelSession(dwSessionID_);
	return true;
}

void CGame2DBCommClt::_OnTimeOut_SaveUserDataReq(UINT32 dwSessionID)
{
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT64 qwUsrID, //(本地保存的函数参数)账号ID
		ESaveType eSaveType //(本地保存的函数参数)保存类型
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_), UINT64, ESaveType> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID));
	if(pSessData_ == NULL)
		return;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(2, std::get<1>(*pSessData_), std::get<2>(*pSessData_));
}

bool CGame2DBCommClt::_DoReturn_SaveOffLineDgnInfo(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoReturn exception: " << szExcept << ", Protocol: 4, Function: 6";
		return false;
	}
	UINT8 byRet_ = 0;
	if(!bRet_)
		byRet_ = 1;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT64 qwUsrID, //(本地保存的函数参数)账号ID
		UINT32 dwDgnType //(本地保存的函数参数)副本类型
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_), UINT64, UINT32> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID_));
	if(pSessData_ == NULL)
		return false;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(byRet_, std::get<1>(*pSessData_), std::get<2>(*pSessData_));
	if(_pSessionMgr != NULL)
		_pSessionMgr->DelSession(dwSessionID_);
	return true;
}

void CGame2DBCommClt::_OnTimeOut_SaveOffLineDgnInfo(UINT32 dwSessionID)
{
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		UINT64 qwUsrID, //(本地保存的函数参数)账号ID
		UINT32 dwDgnType //(本地保存的函数参数)副本类型
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_), UINT64, UINT32> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID));
	if(pSessData_ == NULL)
		return;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(2, std::get<1>(*pSessData_), std::get<2>(*pSessData_));
}

bool CGame2DBCommClt::_DoReturn_LoadOffLineUserData(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoReturn exception: " << szExcept << ", Protocol: 4, Function: 7";
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

void CGame2DBCommClt::_OnTimeOut_LoadOffLineUserData(UINT32 dwSessionID)
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

bool CGame2DBCommClt::_DoReturn_LoadWorldBossInfo(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	bool bRet_ = false;
	TVecWBossDBInfo vecWorldBossInfo;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> bRet_ >> vecWorldBossInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoReturn exception: " << szExcept << ", Protocol: 4, Function: 8";
		return false;
	}
	UINT8 byRet_ = 0;
	if(!bRet_)
		byRet_ = 1;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		const TVecWBossDBInfo& vecWorldBossInfo //(返回值)世界BOSS信息
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID_));
	if(pSessData_ == NULL)
		return false;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(byRet_, vecWorldBossInfo);
	if(_pSessionMgr != NULL)
		_pSessionMgr->DelSession(dwSessionID_);
	return true;
}

void CGame2DBCommClt::_OnTimeOut_LoadWorldBossInfo(UINT32 dwSessionID)
{
	TVecWBossDBInfo vecWorldBossInfo;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		const TVecWBossDBInfo& vecWorldBossInfo //(返回值)世界BOSS信息
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID));
	if(pSessData_ == NULL)
		return;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(2, vecWorldBossInfo);
}

bool CGame2DBCommClt::_DoReturn_GetUserIDFromName(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoReturn exception: " << szExcept << ", Protocol: 4, Function: 10";
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

void CGame2DBCommClt::_OnTimeOut_GetUserIDFromName(UINT32 dwSessionID)
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

bool CGame2DBCommClt::_DoReturn_GetBattleReport(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoReturn exception: " << szExcept << ", Protocol: 4, Function: 11";
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

void CGame2DBCommClt::_OnTimeOut_GetBattleReport(UINT32 dwSessionID)
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

bool CGame2DBCommClt::_DoReturn_AddBattleReport(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoReturn exception: " << szExcept << ", Protocol: 4, Function: 12";
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

void CGame2DBCommClt::_OnTimeOut_AddBattleReport(UINT32 dwSessionID)
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

bool CGame2DBCommClt::_DoReturn_LoadMallDiscount(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	bool bRet_ = false;
	NMallProt::TVecDiscount vecDisItems;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> bRet_ >> vecDisItems;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoReturn exception: " << szExcept << ", Protocol: 4, Function: 15";
		return false;
	}
	UINT8 byRet_ = 0;
	if(!bRet_)
		byRet_ = 1;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		const NMallProt::TVecDiscount& vecDisItems //(返回值)限购道具信息
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID_));
	if(pSessData_ == NULL)
		return false;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(byRet_, vecDisItems);
	if(_pSessionMgr != NULL)
		_pSessionMgr->DelSession(dwSessionID_);
	return true;
}

void CGame2DBCommClt::_OnTimeOut_LoadMallDiscount(UINT32 dwSessionID)
{
	NMallProt::TVecDiscount vecDisItems;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		const NMallProt::TVecDiscount& vecDisItems //(返回值)限购道具信息
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_)> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID));
	if(pSessData_ == NULL)
		return;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(2, vecDisItems);
}

} //namespace NGame2DBComm
