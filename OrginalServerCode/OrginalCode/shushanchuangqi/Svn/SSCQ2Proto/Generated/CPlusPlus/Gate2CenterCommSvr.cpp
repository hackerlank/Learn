/************************************************************************
//  工具自动生成的服务器协议代码(UTF-8 With BOM)
//  File Name:    Gate2CenterComm.cpp
//  Purpose:      GateServer到CenterServer的通信协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "Gate2CenterCommSvr.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NGate2CenterComm
{

CGate2CenterCommSvr::THandleFunc CGate2CenterCommSvr::_ReturnFuncs[] =
{
	&CGate2CenterCommSvr::_DoReturn_ReplaceUser, //FuncID: -1
};

CGate2CenterCommSvr::THandleFunc CGate2CenterCommSvr::_HandleFuncs[] =
{
	&CGate2CenterCommSvr::_DoRecv_KeepAlive, //FuncID: 1
	&CGate2CenterCommSvr::_DoRecv_UserLoginNtf, //FuncID: 2
	&CGate2CenterCommSvr::_DoRecv_UserLogoutNtf, //FuncID: 3
};

CGate2CenterCommSvr::TTimeOutFunc CGate2CenterCommSvr::_TimeoutFuncs[] =
{
	&CGate2CenterCommSvr::_OnTimeOut_ReplaceUser, //FuncID: 1
};

bool CGate2CenterCommSvr::HandleMessage(const char* pBuf, UINT32 dwLen)
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

void CGate2CenterCommSvr::OnTimeOut(UINT8 byFuncID, UINT32 dwSessionID)
{
	if(byFuncID == 0 || byFuncID > (UINT8)ARRAYSIZE(_TimeoutFuncs))
		return;
	(this->*_TimeoutFuncs[byFuncID - 1])(dwSessionID);
}

//发送：玩家登录通知
bool CGate2CenterCommSvr::Send_UserWantLoginNtf(
	UINT64 qwUsrID, //帐号ID
	UINT32 dwCryptoCode //登录验证码
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << dwCryptoCode;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 6, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGate2CenterCommSvr::SendSvr_UserWantLoginNtf(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwUsrID, //帐号ID
	UINT32 dwCryptoCode //登录验证码
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << dwCryptoCode;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 6, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGate2CenterCommSvr::BuildPkg_UserWantLoginNtf(
	UINT64 qwUsrID, //帐号ID
	UINT32 dwCryptoCode //登录验证码
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << dwCryptoCode;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 6, Function: 1";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：踢玩家下线
bool CGate2CenterCommSvr::Send_KickUserOffLine(
	UINT64 qwUsrID, //帐号ID
	NServerCommon::ELeaveType eLeaveType //下线类型
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << (UINT8&)eLeaveType;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 6, Function: 2";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGate2CenterCommSvr::SendSvr_KickUserOffLine(const UINT32* pSvrID_, UINT8 byCnt_,
	UINT64 qwUsrID, //帐号ID
	NServerCommon::ELeaveType eLeaveType //下线类型
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << (UINT8&)eLeaveType;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 6, Function: 2";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGate2CenterCommSvr::BuildPkg_KickUserOffLine(
	UINT64 qwUsrID, //帐号ID
	NServerCommon::ELeaveType eLeaveType //下线类型
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << qwUsrID << (UINT8&)eLeaveType;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 6, Function: 2";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：替换帐号
bool CGate2CenterCommSvr::Send_ReplaceUser(
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
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwUsrID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 6, Function: 3";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGate2CenterCommSvr::SendSvr_ReplaceUser(const UINT32* pSvrID_, UINT8 byCnt_,
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
	const UINT8 byFuncID_ = 3;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << qwUsrID;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 6, Function: 3";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

bool CGate2CenterCommSvr::_DoRecv_KeepAlive(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwUsrCnt = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwUsrCnt;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 6, Function: 1";
		return false;
	}
	OnRecv_KeepAlive(dwUsrCnt);
	return true;
}

bool CGate2CenterCommSvr::_DoRecv_UserLoginNtf(const char* pBuf_, UINT32 dwLen_)
{
	UINT64 qwUsrID = 0;
	std::string strIPAddr;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> qwUsrID >> strIPAddr;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 6, Function: 2";
		return false;
	}
	OnRecv_UserLoginNtf(qwUsrID, strIPAddr);
	return true;
}

bool CGate2CenterCommSvr::_DoRecv_UserLogoutNtf(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 6, Function: 3";
		return false;
	}
	OnRecv_UserLogoutNtf(qwUsrID, eLeaveType);
	return true;
}

bool CGate2CenterCommSvr::_DoReturn_ReplaceUser(const char* pBuf_, UINT32 dwLen_)
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
		LOG_CRI << "DoReturn exception: " << szExcept << ", Protocol: 6, Function: 3";
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

void CGate2CenterCommSvr::_OnTimeOut_ReplaceUser(UINT32 dwSessionID)
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

} //namespace NGate2CenterComm
