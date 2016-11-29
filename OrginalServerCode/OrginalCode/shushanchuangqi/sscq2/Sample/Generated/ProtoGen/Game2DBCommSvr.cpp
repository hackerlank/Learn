/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    Game2DBComm.cpp
//  Purpose:      GameServer到DBServer的通信协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "Game2DBCommSvr.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NGame2DBComm
{

CGame2DBCommSvr::THandleFunc CGame2DBCommSvr::_HandleFuncs[] =
{
	&CGame2DBCommSvr::_DoRecv_KeepAlive, //FuncID: 1
	&CGame2DBCommSvr::_DoRecv_GetStatus, //FuncID: 2
	&CGame2DBCommSvr::_DoRecv_UpdateRecharge, //FuncID: 3
	&CGame2DBCommSvr::_DoRecv_RoleDataUpdate, //FuncID: 4
	&CGame2DBCommSvr::_DoRecv_SaveUserDataReq, //FuncID: 5
	&CGame2DBCommSvr::_DoRecv_SaveOffLineDgnInfo, //FuncID: 6
	&CGame2DBCommSvr::_DoRecv_LoadOffLineUserData, //FuncID: 7
	&CGame2DBCommSvr::_DoRecv_LoadWorldBossInfo, //FuncID: 8
	&CGame2DBCommSvr::_DoRecv_SaveWorldBossInfo, //FuncID: 9
	&CGame2DBCommSvr::_DoRecv_GetUserIDFromName, //FuncID: 10
	&CGame2DBCommSvr::_DoRecv_GetBattleReport, //FuncID: 11
	&CGame2DBCommSvr::_DoRecv_AddBattleReport, //FuncID: 12
	&CGame2DBCommSvr::_DoRecv_AddOffLineEvent, //FuncID: 13
	&CGame2DBCommSvr::_DoRecv_DelOffLineEvent, //FuncID: 14
	&CGame2DBCommSvr::_DoRecv_LoadMallDiscount, //FuncID: 15
	&CGame2DBCommSvr::_DoRecv_UpdateMallDiscount, //FuncID: 16
	&CGame2DBCommSvr::_DoRecv_GetNewGuildBattleHistory, //FuncID: 17
	&CGame2DBCommSvr::_DoRecv_AddNewGuildBattleHistory, //FuncID: 18
};

bool CGame2DBCommSvr::HandleMessage(const char* pBuf, UINT32 dwLen)
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

//发送：帐号协议代理发送请求
bool CGame2DBCommSvr::Send_UserPackageProxy(
	UINT64 qwUsrID, //帐号ID
	UINT32 dwGateID, //所在网关服务器ID
	const TVecString& vecPackage //协议包列表
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << dwGateID << vecPackage;
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

bool CGame2DBCommSvr::SendSvr_UserPackageProxy(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwUsrID, //帐号ID
	UINT32 dwGateID, //所在网关服务器ID
	const TVecString& vecPackage //协议包列表
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << dwGateID << vecPackage;
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

std::string& CGame2DBCommSvr::BuildPkg_UserPackageProxy(
	UINT64 qwUsrID, //帐号ID
	UINT32 dwGateID, //所在网关服务器ID
	const TVecString& vecPackage //协议包列表
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << dwGateID << vecPackage;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 4, Function: 1";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：DB向GameSever推送角色信息/
bool CGame2DBCommSvr::Send_UserLoginNtf(
	EEnterType eEnterType, //进入的类型
	const NProtoCommon::TVecPlatformParam& vecPlatformParam, //平台参数列表
	const TVecString& vecEnterString, //平台相关参数
	UINT32 dwGateId, //网关Id
	UINT64 qwUserId, //用户Id
	const NRoleInfoDefine::RoleDataInfo& RoleData //玩家数据
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eEnterType << vecPlatformParam << vecEnterString << dwGateId << qwUserId << RoleData;
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

bool CGame2DBCommSvr::SendSvr_UserLoginNtf(const UINT32* pSvrID_, UINT8 byCnt_,
	EEnterType eEnterType, //进入的类型
	const NProtoCommon::TVecPlatformParam& vecPlatformParam, //平台参数列表
	const TVecString& vecEnterString, //平台相关参数
	UINT32 dwGateId, //网关Id
	UINT64 qwUserId, //用户Id
	const NRoleInfoDefine::RoleDataInfo& RoleData //玩家数据
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eEnterType << vecPlatformParam << vecEnterString << dwGateId << qwUserId << RoleData;
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

std::string& CGame2DBCommSvr::BuildPkg_UserLoginNtf(
	EEnterType eEnterType, //进入的类型
	const NProtoCommon::TVecPlatformParam& vecPlatformParam, //平台参数列表
	const TVecString& vecEnterString, //平台相关参数
	UINT32 dwGateId, //网关Id
	UINT64 qwUserId, //用户Id
	const NRoleInfoDefine::RoleDataInfo& RoleData //玩家数据
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << (UINT8&)eEnterType << vecPlatformParam << vecEnterString << dwGateId << qwUserId << RoleData;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 4, Function: 2";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：账号重新进入通知
bool CGame2DBCommSvr::Send_UserReEnterNotify(
	UINT64 qwUsrID, //账号ID
	UINT32 dwGateID, //所在网关服务器ID
	const NProtoCommon::TVecPlatformParam& vecPlatformParam, //平台参数列表
	const TVecString& vecEnterString //平台相关参数
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << dwGateID << vecPlatformParam << vecEnterString;
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

bool CGame2DBCommSvr::SendSvr_UserReEnterNotify(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwUsrID, //账号ID
	UINT32 dwGateID, //所在网关服务器ID
	const NProtoCommon::TVecPlatformParam& vecPlatformParam, //平台参数列表
	const TVecString& vecEnterString //平台相关参数
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << dwGateID << vecPlatformParam << vecEnterString;
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

std::string& CGame2DBCommSvr::BuildPkg_UserReEnterNotify(
	UINT64 qwUsrID, //账号ID
	UINT32 dwGateID, //所在网关服务器ID
	const NProtoCommon::TVecPlatformParam& vecPlatformParam, //平台参数列表
	const TVecString& vecEnterString //平台相关参数
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << dwGateID << vecPlatformParam << vecEnterString;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 4, Function: 3";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：账号退出DBServer通知
bool CGame2DBCommSvr::Send_UserLogoutNtf(
	UINT64 qwUsrID, //账号ID
	NServerCommon::ELeaveType eLeaveType //下线类型
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << (UINT8&)eLeaveType;
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

bool CGame2DBCommSvr::SendSvr_UserLogoutNtf(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwUsrID, //账号ID
	NServerCommon::ELeaveType eLeaveType //下线类型
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << (UINT8&)eLeaveType;
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

std::string& CGame2DBCommSvr::BuildPkg_UserLogoutNtf(
	UINT64 qwUsrID, //账号ID
	NServerCommon::ELeaveType eLeaveType //下线类型
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 4;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << (UINT8&)eLeaveType;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 4, Function: 4";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：离线事件通知
bool CGame2DBCommSvr::Send_NewOffEventNotice(
	UINT64 qwUsrID, //账号ID
	const NRoleInfoDefine::SEventOffLine& sEventData //事件类型
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 5;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << sEventData;
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

bool CGame2DBCommSvr::SendSvr_NewOffEventNotice(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwUsrID, //账号ID
	const NRoleInfoDefine::SEventOffLine& sEventData //事件类型
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 5;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << sEventData;
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

std::string& CGame2DBCommSvr::BuildPkg_NewOffEventNotice(
	UINT64 qwUsrID, //账号ID
	const NRoleInfoDefine::SEventOffLine& sEventData //事件类型
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 5;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << sEventData;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 4, Function: 5";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：新帮派战历史记录获取返回
bool CGame2DBCommSvr::Send_NewGuildBattleHistoryNotify(
	UINT32 dwCurSize, //已发送条数
	UINT32 dwTotalSize, //总条数
	const TVecDBGuildNewBattleHistoryInfo& vecInfo //更新信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 6;
	try
	{
		ar << byProtID_ << byFuncID_ << dwCurSize << dwTotalSize << vecInfo;
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

bool CGame2DBCommSvr::SendSvr_NewGuildBattleHistoryNotify(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT32 dwCurSize, //已发送条数
	UINT32 dwTotalSize, //总条数
	const TVecDBGuildNewBattleHistoryInfo& vecInfo //更新信息
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 6;
	try
	{
		ar << byProtID_ << byFuncID_ << dwCurSize << dwTotalSize << vecInfo;
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

std::string& CGame2DBCommSvr::BuildPkg_NewGuildBattleHistoryNotify(
	UINT32 dwCurSize, //已发送条数
	UINT32 dwTotalSize, //总条数
	const TVecDBGuildNewBattleHistoryInfo& vecInfo //更新信息
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 6;
	try
	{
		ar << byProtID_ << byFuncID_ << dwCurSize << dwTotalSize << vecInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 4, Function: 6";
		_strPkg.clear();
	}
	return _strPkg;
}

bool CGame2DBCommSvr::_DoRecv_KeepAlive(const char* pBuf_, UINT32 dwLen_)
{
	OnRecv_KeepAlive();
	return true;
}

CGame2DBCommSvr::SGetStatusAck::SGetStatusAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID) { }

void CGame2DBCommSvr::SGetStatusAck::SendReturn(bool bRet_)
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
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 4, Function: 2";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CGame2DBCommSvr::_DoRecv_GetStatus(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 4, Function: 2";
		return false;
	}
	shared_func<SGetStatusAck> fnAck_(new SGetStatusAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetStatus(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

bool CGame2DBCommSvr::_DoRecv_UpdateRecharge(const char* pBuf_, UINT32 dwLen_)
{
	NRoleInfoDefine::SRecharge oRecharge;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> oRecharge;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 4, Function: 3";
		return false;
	}
	OnRecv_UpdateRecharge(oRecharge);
	return true;
}

bool CGame2DBCommSvr::_DoRecv_RoleDataUpdate(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 4, Function: 4";
		return false;
	}
	OnRecv_RoleDataUpdate(qwRoleId, eDataType, eUpdateType, strData);
	return true;
}

CGame2DBCommSvr::SSaveUserDataReqAck::SSaveUserDataReqAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID) { }

void CGame2DBCommSvr::SSaveUserDataReqAck::SendReturn(bool bRet_)
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
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 4, Function: 5";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CGame2DBCommSvr::_DoRecv_SaveUserDataReq(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT64 qwUsrID = 0;
	ESaveType eSaveType = (ESaveType)0;
	NProtoCommon::TVecPlatformParam vecPlatformParam;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> qwUsrID >> (UINT8&)eSaveType >> vecPlatformParam;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 4, Function: 5";
		return false;
	}
	shared_func<SSaveUserDataReqAck> fnAck_(new SSaveUserDataReqAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_SaveUserDataReq(qwUsrID, eSaveType, vecPlatformParam, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CGame2DBCommSvr::SSaveOffLineDgnInfoAck::SSaveOffLineDgnInfoAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID) { }

void CGame2DBCommSvr::SSaveOffLineDgnInfoAck::SendReturn(bool bRet_)
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
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 4, Function: 6";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CGame2DBCommSvr::_DoRecv_SaveOffLineDgnInfo(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	UINT64 qwUsrID = 0;
	UINT32 dwDgnType = 0;
	UINT8 byIsFail = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> qwUsrID >> dwDgnType >> byIsFail;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 4, Function: 6";
		return false;
	}
	shared_func<SSaveOffLineDgnInfoAck> fnAck_(new SSaveOffLineDgnInfoAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_SaveOffLineDgnInfo(qwUsrID, dwDgnType, byIsFail, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CGame2DBCommSvr::SLoadOffLineUserDataAck::SLoadOffLineUserDataAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID), 
			byRet(0) { }

void CGame2DBCommSvr::SLoadOffLineUserDataAck::SendReturn(bool bRet_)
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
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 4, Function: 7";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CGame2DBCommSvr::_DoRecv_LoadOffLineUserData(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 4, Function: 7";
		return false;
	}
	shared_func<SLoadOffLineUserDataAck> fnAck_(new SLoadOffLineUserDataAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_LoadOffLineUserData(qwUsrID, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CGame2DBCommSvr::SLoadWorldBossInfoAck::SLoadWorldBossInfoAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID) { }

void CGame2DBCommSvr::SLoadWorldBossInfoAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -5;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << vecWorldBossInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 4, Function: 8";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CGame2DBCommSvr::_DoRecv_LoadWorldBossInfo(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 4, Function: 8";
		return false;
	}
	shared_func<SLoadWorldBossInfoAck> fnAck_(new SLoadWorldBossInfoAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_LoadWorldBossInfo(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

bool CGame2DBCommSvr::_DoRecv_SaveWorldBossInfo(const char* pBuf_, UINT32 dwLen_)
{
	SWBossDBInfo sWorldBossInfo;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> sWorldBossInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 4, Function: 9";
		return false;
	}
	OnRecv_SaveWorldBossInfo(sWorldBossInfo);
	return true;
}

CGame2DBCommSvr::SGetUserIDFromNameAck::SGetUserIDFromNameAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID), 
			qwUsrID(0) { }

void CGame2DBCommSvr::SGetUserIDFromNameAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -6;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << qwUsrID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 4, Function: 10";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CGame2DBCommSvr::_DoRecv_GetUserIDFromName(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 4, Function: 10";
		return false;
	}
	shared_func<SGetUserIDFromNameAck> fnAck_(new SGetUserIDFromNameAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetUserIDFromName(strName, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CGame2DBCommSvr::SGetBattleReportAck::SGetBattleReportAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID) { }

void CGame2DBCommSvr::SGetBattleReportAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -7;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << vecReport;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 4, Function: 11";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CGame2DBCommSvr::_DoRecv_GetBattleReport(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 4, Function: 11";
		return false;
	}
	shared_func<SGetBattleReportAck> fnAck_(new SGetBattleReportAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_GetBattleReport(qwRoleID, eBattleType, eAction, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

CGame2DBCommSvr::SAddBattleReportAck::SAddBattleReportAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID) { }

void CGame2DBCommSvr::SAddBattleReportAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -8;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << vecBattleID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 4, Function: 12";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CGame2DBCommSvr::_DoRecv_AddBattleReport(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 4, Function: 12";
		return false;
	}
	shared_func<SAddBattleReportAck> fnAck_(new SAddBattleReportAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_AddBattleReport(qwRoleID, sReport, byNum, fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

bool CGame2DBCommSvr::_DoRecv_AddOffLineEvent(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 4, Function: 13";
		return false;
	}
	OnRecv_AddOffLineEvent(vecRoleID, sEventData);
	return true;
}

bool CGame2DBCommSvr::_DoRecv_DelOffLineEvent(const char* pBuf_, UINT32 dwLen_)
{
	UINT64 qwRoleID = 0;
	NRoleInfoDefine::TVecEventOffLine vecEventType;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> qwRoleID >> vecEventType;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 4, Function: 14";
		return false;
	}
	OnRecv_DelOffLineEvent(qwRoleID, vecEventType);
	return true;
}

CGame2DBCommSvr::SLoadMallDiscountAck::SLoadMallDiscountAck(IProtocol& rProtocol, UINT32 dwSvrID, UINT32 dwSessionID) : 
			CServerFuncAck(rProtocol, dwSvrID, dwSessionID) { }

void CGame2DBCommSvr::SLoadMallDiscountAck::SendReturn(bool bRet_)
{
	UINT8 byProtID_ = _rProtocol.GetProtID();
	const INT8 byFuncID_ = -9;
	COutArchive arOut;
	try
	{
		arOut << byProtID_ << byFuncID_ << _dwSessionID << bRet_ << vecDisItems;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Return exception: " << szExcept << ", Protocol: 4, Function: 15";
		return;
	}
	UINT32 dwLen_ = 0;
	const char* pBuf_ = arOut.GetBuf(dwLen_);
	IConnectionHandler* pConHandler = _rProtocol.GetConnectionHandler();
	if(pConHandler != NULL)
		pConHandler->SendSvr(&_dwSvrID, 1, pBuf_, dwLen_);
	_bReturned = true;
}

bool CGame2DBCommSvr::_DoRecv_LoadMallDiscount(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 4, Function: 15";
		return false;
	}
	shared_func<SLoadMallDiscountAck> fnAck_(new SLoadMallDiscountAck(*this, GetCurSvrID(), dwSessionID_));
	bool bRet_ = OnRecv_LoadMallDiscount(fnAck_);
	if(fnAck_.unique() && !fnAck_->HasReturned())
		fnAck_(bRet_);
	return true;
}

bool CGame2DBCommSvr::_DoRecv_UpdateMallDiscount(const char* pBuf_, UINT32 dwLen_)
{
	NProtoCommon::EDataChange eUpdateType = (NProtoCommon::EDataChange)0;
	NMallProt::TVecDiscount vecDisItems;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> (UINT8&)eUpdateType >> vecDisItems;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 4, Function: 16";
		return false;
	}
	OnRecv_UpdateMallDiscount(eUpdateType, vecDisItems);
	return true;
}

bool CGame2DBCommSvr::_DoRecv_GetNewGuildBattleHistory(const char* pBuf_, UINT32 dwLen_)
{
	OnRecv_GetNewGuildBattleHistory();
	return true;
}

bool CGame2DBCommSvr::_DoRecv_AddNewGuildBattleHistory(const char* pBuf_, UINT32 dwLen_)
{
	TVecDBGuildNewBattleHistoryInfo vecInfo;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> vecInfo;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 4, Function: 18";
		return false;
	}
	OnRecv_AddNewGuildBattleHistory(vecInfo);
	return true;
}

} //namespace NGame2DBComm
