/************************************************************************
//  工具自动生成的客户端协议代码(UTF-8 With BOM)
//  File Name:    GameSvrComm.cpp
//  Purpose:      GameServer之间的通信协议
//  Copyright (c) 2010-2020 上海恺英网络科技有限公司, All rights reserved.
*************************************************************************/

#include "UtilFunc.h"
#include "GameSvrCommClt.h"
#include "SessionMgr.h"

#ifdef _WIN32
#pragma warning(disable:4700)
#endif

namespace NGameSvrComm
{

CGameSvrCommClt::THandleFunc CGameSvrCommClt::_ReturnFuncs[] =
{
	&CGameSvrCommClt::_DoReturn_TestRetFuncReq, //FuncID: -1
};

CGameSvrCommClt::THandleFunc CGameSvrCommClt::_HandleFuncs[] =
{
	&CGameSvrCommClt::_DoRecv_TestFuncAck, //FuncID: 1
};

CGameSvrCommClt::TTimeOutFunc CGameSvrCommClt::_TimeoutFuncs[] =
{
	&CGameSvrCommClt::_OnTimeOut_TestRetFuncReq, //FuncID: 1
};

bool CGameSvrCommClt::HandleMessage(const char* pBuf, UINT32 dwLen)
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

void CGameSvrCommClt::OnTimeOut(UINT8 byFuncID, UINT32 dwSessionID)
{
	if(byFuncID == 0 || byFuncID > (UINT8)ARRAYSIZE(_TimeoutFuncs))
		return;
	(this->*_TimeoutFuncs[byFuncID - 1])(dwSessionID);
}

//发送：测试函数请求
bool CGameSvrCommClt::Send_TestFuncReq(
	const STest& rTest //参数1
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << rTest;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 67, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGameSvrCommClt::SendSvr_TestFuncReq(const UINT32* pSvrID_, UINT8 byCnt_,
	const STest& rTest //参数1
)
{
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << rTest;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 67, Function: 1";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

std::string& CGameSvrCommClt::BuildPkg_TestFuncReq(
	const STest& rTest //参数1
)
{
	COutArchive ar(_strPkg);
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 1;
	try
	{
		ar << byProtID_ << byFuncID_ << rTest;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "BuildPkg exception: " << szExcept << ", Protocol: 67, Function: 1";
		_strPkg.clear();
	}
	return _strPkg;
}

//发送：测试返回函数请求
bool CGameSvrCommClt::Send_TestRetFuncReq(
	const STest& rTest, //参数1
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		const STest& rTest, //(本地保存的函数参数)参数1
		UINT32 dwRetParam //(返回值)返回参数1
	)> fnOnReturn_ //返回时的回调函数
)
{
	if(_pSessionMgr == NULL)
	{
		LOG_CRI << "_pSessionMgr == NULL";		return false;
	}
	UINT32 dwSessionID_ = _pSessionMgr->GetNewSession(*this, 1);
	typedef std::tuple<decltype(fnOnReturn_), STest> TSessData;
	std::shared_ptr<TSessData> pSessData_(new TSessData(fnOnReturn_, rTest));
	_pSessionMgr->StoreData(dwSessionID_, pSessData_);
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << rTest;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "Send exception: " << szExcept << ", Protocol: 67, Function: 2";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->Send(pBuf_, dwLen_);
	return false;
}

bool CGameSvrCommClt::SendSvr_TestRetFuncReq(const UINT32* pSvrID_, UINT8 byCnt_,
	const STest& rTest, //参数1
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		const STest& rTest, //(本地保存的函数参数)参数1
		UINT32 dwRetParam //(返回值)返回参数1
	)> fnOnReturn_ //返回时的回调函数
)
{
	if(_pSessionMgr == NULL)
	{
		LOG_CRI << "_pSessionMgr == NULL";		return false;
	}
	UINT32 dwSessionID_ = _pSessionMgr->GetNewSession(*this, 1);
	typedef std::tuple<decltype(fnOnReturn_), STest> TSessData;
	std::shared_ptr<TSessData> pSessData_(new TSessData(fnOnReturn_, rTest));
	_pSessionMgr->StoreData(dwSessionID_, pSessData_);
	COutArchive ar;
	UINT8 byProtID_ = GetProtID();
	const UINT8 byFuncID_ = 2;
	try
	{
		ar << byProtID_ << byFuncID_ << dwSessionID_ << rTest;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "SendSvr exception: " << szExcept << ", Protocol: 67, Function: 2";
		return false;
	}
	UINT32 dwLen_ = 0;
	char* pBuf_ = ar.GetBuf(dwLen_);
	if(_pConnHandler != NULL)
		return _pConnHandler->SendSvr(pSvrID_, byCnt_, pBuf_, dwLen_);
	return false;
}

bool CGameSvrCommClt::_DoRecv_TestFuncAck(const char* pBuf_, UINT32 dwLen_)
{
	STest rTest;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> rTest;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoRecv exception: " << szExcept << ", Protocol: 67, Function: 1";
		return false;
	}
	OnRecv_TestFuncAck(rTest);
	return true;
}

bool CGameSvrCommClt::_DoReturn_TestRetFuncReq(const char* pBuf_, UINT32 dwLen_)
{
	UINT32 dwSessionID_ = 0;
	bool bRet_ = false;
	UINT32 dwRetParam = 0;
	new (&_oInArchive) CInArchive(pBuf_, dwLen_);
	try
	{
		_oInArchive >> dwSessionID_ >> bRet_ >> dwRetParam;
	}
	catch(const char* szExcept)
	{
		LOG_CRI << "DoReturn exception: " << szExcept << ", Protocol: 67, Function: 2";
		return false;
	}
	UINT8 byRet_ = 0;
	if(!bRet_)
		byRet_ = 1;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		const STest& rTest, //(本地保存的函数参数)参数1
		UINT32 dwRetParam //(返回值)返回参数1
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_), STest> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID_));
	if(pSessData_ == NULL)
		return false;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(byRet_, std::get<1>(*pSessData_), dwRetParam);
	if(_pSessionMgr != NULL)
		_pSessionMgr->DelSession(dwSessionID_);
	return true;
}

void CGameSvrCommClt::_OnTimeOut_TestRetFuncReq(UINT32 dwSessionID)
{
	UINT32 dwRetParam = 0;
	boost::function<void (UINT8 byRet_, //0为成功，1为失败，2为超时
		const STest& rTest, //(本地保存的函数参数)参数1
		UINT32 dwRetParam //(返回值)返回参数1
	)> fnOnReturn_;
	typedef std::tuple<decltype(fnOnReturn_), STest> TSessData;
	std::shared_ptr<TSessData> pSessData_;
	if(_pSessionMgr != NULL)
		pSessData_ = std::static_pointer_cast<TSessData>(_pSessionMgr->GetData(dwSessionID));
	if(pSessData_ == NULL)
		return;
	fnOnReturn_ = std::get<0>(*pSessData_);
	if(fnOnReturn_ != NULL)
		fnOnReturn_(2, std::get<1>(*pSessData_), dwRetParam);
}

} //namespace NGameSvrComm
